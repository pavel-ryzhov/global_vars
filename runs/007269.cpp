
#include <iostream>

#include <algorithm>

#include <iterator>
#include <vector>
#include <string>
#include <list>

typedef std::pair<int, std::string> WordInfo;	//запись об одном слове словар€ и соответствующей ему частоте использовани€
typedef std::list<WordInfo> Page;						//список записей о словах, представленных в словаре одной комбинацией чисел
typedef std::pair<std::string, Page> Data;
typedef std::vector<Data> Glossary;
typedef Glossary::iterator GI;

const int MAX_STRING = 10000;
const int CHAR_INT_DIFF = 48;
const int PREPROC_LVL = 4;

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

bool onlyNines(int x)
{
	++x;
	while (x > 9)
		x %= 10;
	return x == 0;
}



class T9
{
	
	Glossary m_g;
	std::vector<GI> m_preproc;

	void showWord(std::string& s, int& count)			//функци€ принимает строку кода слова (s) и количество звездочек (count), 
	{													//по этим данным выдаЄт в поток вывода нужное слово и производит корректировку данных
		if (s.empty() )
			return;
		int x = 0;  
		int max_index = std::min((int)s.size(), PREPROC_LVL);
		for (int i = 0; i < max_index; ++i)
			x = 10 * x + (s[i] - CHAR_INT_DIFF);
		GI first_iter = m_preproc[x];
		if (onlyNines(x) )
		{
			x = 1;
			for (int i = 0; i < PREPROC_LVL; ++i)
				x *= 10;
			--x;
		}
		else
			++x;
		GI last_iter = m_preproc[x];
		Page& p = std::lower_bound(first_iter, last_iter, s, PairCompare<Data>() )->second;
		Page::reverse_iterator ri = p.rbegin();
		for(int i = 0; i < count; ++i)
			++ri;										//поиск нужного слова в списке

		std::cout << ri->second;
		Page::iterator curr = --(ri.base() );
		p.splice(std::upper_bound(curr, p.end(), ++(ri->first), PairCompare<WordInfo>() ), 
						p, curr);			//поиск нового места дл€ слова с учетом новой частоты использовани€, вставка на это место
		count = 0;
		s.clear();
	}
	void setsymbol(char& c, int& counter, std::istreambuf_iterator<char>& it, std::string& buf_s)
	{
		switch (c)
			{
			case ' ':
				{
					showWord(buf_s, counter);
					std::cout << ' ';
					c = *it;
					break;
				}
			case '*':
				{
					++counter;
					c = *it;
					break;
				}
			case '1':
				{
					showWord(buf_s, counter);
					for (c = *it; c == '*'; c = *(++it) )
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
					c = *it;
				}
			}
	}
	GI fill_preproc(GI iter, GI it_end, int index, char c, int x = 0)
	{
		for(; iter != it_end && iter->first[x] < c; ++iter);
		m_preproc[index] = iter;
		if (x < PREPROC_LVL - 1)
			for (int i = 9; i >= 0; --i)
				it_end = fill_preproc(iter, it_end, 10*index + i, (char)(i + CHAR_INT_DIFF), x + 1); 
		return iter;
	}
	void preprocess()
	{
		int x = 1;
		for (int i = 0; i < PREPROC_LVL; ++i)
			x *= 10;
		GI it_begin = m_g.begin(),
			it_end = m_g.end();
		m_preproc.assign(x, it_end);
				for (int i = 9; i > 0; --i)
			it_end = fill_preproc(it_begin, it_end, i, (char)(i + CHAR_INT_DIFF) );

	}
public:
	void fill()											//заполнение словар€
	{
		int n;
		std::cin >> n;
		m_g.reserve(n);
		
		WordInfo w;
		Data d;
		char old_code = '0';

		std::pair<GI, GI> gip;
		GI  iter,
			find_iter = m_g.begin();
		for (int i = 0; i < n; ++i)
		{
			std::cin >> w.second >> w.first;
			d.first.clear();
			std::transform(w.second.begin(), w.second.end(), back_inserter(d.first), Encode() );
														//ѕреобразовать слово в его цифровой эквивалент “9 и записать в d
			if (d.first.size() < PREPROC_LVL)
				d.first.resize(PREPROC_LVL, '0');
			gip = std::equal_range(find_iter, m_g.end(), d.first, PairCompare<Data>() );
			if (gip.first == gip.second)
				iter = m_g.insert(gip.first, d);
			else
				iter = gip.first;
			iter->second.insert(std::lower_bound(iter->second.begin(), iter->second.end(), w.first, PairCompare<WordInfo>() ),
								w);						//¬ставить запись о очередном слове словар€ в соответствующую страницу, не наруша€ еЄ сортировки
			if (iter->first[0] > old_code)
			{
				old_code = iter->first[0];
				find_iter = iter;
			}
		}
		preprocess();
	}
	void work()
	{
		std::string buf_s;
		std::cin.ignore(std::cin.rdbuf()->in_avail());
														//очистка буфера потока ввод		
		int counter = 0;		
		 std::cin.get();
		std::istreambuf_iterator<char> it (std::cin);
		char c = *it;
		for (; c != '\n';)						//цикл обработки строки сообщени€
		{
			setsymbol(c, counter, ++it, buf_s);
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