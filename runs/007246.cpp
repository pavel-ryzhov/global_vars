
#include <iostream>

#include <algorithm>

#include <iterator>
#include <hash_map>
#include <string>
#include <list>

template <class SomePair>
	class PairCompare			//‘унктор дл€ сравнений элементов-пар по первому полю
{
	bool realCompare(const typename SomePair::first_type& l,
					const typename SomePair::first_type& r) const
	{
		return l < r;
	}
public:
	bool operator()(const SomePair& lhs, 
					const SomePair& rhs) const
	{
		return realCompare(lhs.first, rhs.first);
	}
	bool operator()(const typename SomePair::first_type& k, 
					const SomePair& d) const
	{
		return realCompare(k, d.first);
	}
	bool operator()(const SomePair& d, 
					const typename SomePair::first_type& k) const
	{
		return realCompare(d.first, k);
	}
};

struct Encode
{
	char operator()(char c) const
	{
		if (97 <= c && c <= 114)		// [a; r]
			return ((c - 1) / 3) + 18;
		else if (116 <= c && c <= 121)	// [t; y]
			return ((c - 2) / 3) + 18;
		else if (c == 's')
			return '7';
		else if (c == 122)
			return '9';
		else
			return '1';
	}
};

typedef std::pair<unsigned int, std::string> WordInfo;	//запись об одном слове словар€ и соответствующей ему частоте использовани€
typedef std::list<WordInfo> Page;						//список записей о словах, представленных в словаре одной комбинацией чисел
typedef std::pair<std::string, Page> Data;
typedef std::vector<Data> Glossary;

const double OPTIMIZE = 0.2;
const int MAX_STRING = 10000;

class T9
{
	Glossary m_g;

	void showWord(std::string& s, int& count)//функци€ принимает строку кода слова (s) и количество звездочек (count), 
	{													//по этим данным выдаЄт в поток вывода нужное слово и производит корректировку данных
		if (s.empty() )
			return;
		Page& p = std::lower_bound(m_g.begin(), m_g.end(), s, PairCompare<Data>() )->second;
		Page::reverse_iterator ri = p.rbegin();
		for(int i = 0; i < count; ++i)
			++ri;										//поиск нужного слова в списке
		std::cout << ri->second;
		p.splice(std::upper_bound(p.begin(), p.end(), ++(ri->first), PairCompare<WordInfo>() ), 
						p, --(ri.base() ) );			//поиск нового места дл€ слова с учетом новой частоты использовани€, вставка на это место
		count = 0;
		s.clear();
	}
public:
	void fill()											//заполнение словар€
	{
		int n;
		std::cin >> n;
		m_g.reserve(n);
		
		WordInfo w;
		Data d;

		std::cin >> w.second >> w.first;
		std::transform(w.second.begin(), w.second.end(), back_inserter(d.first), Encode() );	
														//ѕреобразовать слово в его цифровой эквивалент “9 и записать в d
		m_g.push_back(d);

		Glossary::iterator iter = m_g.begin();
		iter->second.insert(std::lower_bound(iter->second.begin(), iter->second.end(), w.first, PairCompare<WordInfo>() ),
							w);							//¬ставить запись о очередном слове словар€ в соответствующую страницу, не наруша€ еЄ сортировки
		for (int i = 1; i < n; ++i)
		{
			std::cin >> w.second >> w.first;
			d.first.clear();
			std::transform(w.second.begin(), w.second.end(), back_inserter(d.first), Encode() );
			if (iter->first != d.first)
			{
				m_g.push_back(d);
				iter++;
			}
			iter->second.insert(std::lower_bound(iter->second.begin(), iter->second.end(), w.first, PairCompare<WordInfo>() ),
								w);	
		}
		if (OPTIMIZE * m_g.capacity() > m_g.size() )
			Glossary(m_g).swap(m_g);					//ќтсечение лишнего зарезервированного места
	}
	void work()
	{
		std::string buf_s;
		std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');
														//очистка буфера потока ввод		
		int counter = 0;				
		std::istreambuf_iterator<char>	it (std::cin);
		for (char c = *it; c != '\n';)
		{												//цикл обработки строки сообщени€
			switch (c)
			{
			case ' ':
				{
					showWord(buf_s, counter);
					std::cout << ' ';
					c = *(++it);
					break;
				}
			case '*':
				{
					++counter;
					c = *(++it);
					break;
				}
			case '1':
				{
					showWord(buf_s, counter);
					for (c = *(++it); c == '*'; c = *(++it) )
						++counter;
					switch (counter)
					{
					case 0:
						{
							std::cout << '.';
							break;
						}
					case 1:
						{
							std::cout << ',';
							break;
						}
					case 2:
						{
							std::cout << '?';
						}
					}
					counter = 0;
					break;
				}
			default:
				{
					buf_s.push_back(c);
					c = *(++it);
				}
			}
		}
		showWord(buf_s, counter);
		
	}
};

int main()
{
	T9 t;
	t.fill();
	t.work();

	return 0;
}
