
#include <iostream>

#include <algorithm>

#include <iterator>
#include <vector>
#include <string>
#include <list>
#include <map>

typedef std::pair<int, std::string> WordInfo;	//запись об одном слове словаря и соответствующей ему частоте использования
typedef std::list<WordInfo> Page;						//список записей о словах, представленных в словаре одной комбинацией чисел
typedef std::map<int, Page> Chapter;
typedef std::vector<Chapter> Glossary;
typedef Glossary::iterator GI;

const int CHAR_INT_DIFF = 48;
const int PREPROC_LVL = 3;
const int LVL_DEGREE = 1000;

class PairCompare			//Функтор для сравнений элементов-пар по первому полю
{
	bool realCompare(const WordInfo::first_type& l,
					const  WordInfo::first_type& r) const
	{
		return l < r;
	}
public:
	bool operator()(const WordInfo& lhs, 
					const WordInfo& rhs) const
	{
		return realCompare(lhs.first, rhs.first);
	}
	bool operator()(const WordInfo::first_type& k, 
					const WordInfo& d) const
	{
		return realCompare(k, d.first);
	}
	bool operator()(const WordInfo& d, 
					const WordInfo::first_type& k) const
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




class T9
{
	
	Glossary m_g;

	void showWord(std::string& s, int& count)			//функция принимает строку кода слова (s) и количество звездочек (count), 
	{													//по этим данным выдаёт в поток вывода нужное слово и производит корректировку данных
		if (s.empty() )
			return;
		std::string::iterator	s_it = s.begin(), 
								s_end = s.end();
		int code = 0, preproc_code;
		for (int i = 0; i < PREPROC_LVL && s_it != s_end; ++s_it)
		{
			code = 10 * code + (*s_it - CHAR_INT_DIFF);
			++i;
		}
		preproc_code = code;
		for (; s_it != s_end; ++s_it)
			code = 10 * code + (*s_it - CHAR_INT_DIFF);

		Page& p = m_g[preproc_code][code];
		Page::reverse_iterator ri = p.rbegin();
		for(int i = 0; i < count; ++i)
			++ri;										//поиск нужного слова в списке
		std::cout << ri->second;
		Page::iterator curr = --(ri.base() );
		p.splice(std::upper_bound(curr, p.end(), ++(ri->first), PairCompare() ), 
						p, curr);			//поиск нового места для слова с учетом новой частоты использования, вставка на это место
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

public:
	void fill()											//заполнение словаря
	{
		int n;
		std::cin >> n;

		m_g.resize(LVL_DEGREE);

		WordInfo w;
		std::string coded_s;
		int code, preproc_code;

													//ОТЛАДКА
													/*w.first = 42;
													w.second = "aaaaaa";*/
													//ОТЛАДКА

		for (int i = 0; i < n; ++i)
		{
			std::cin >> w.second >> w.first;		

													//ОТЛАДКА
													/*if (i % 100 == 0)
														std::cout << "Hundred #" << i / 100 << "...\n";
													
													if (w.second[3] == 'z')
														if (w.second[2] == 'z')
															if (w.second[1] == 'z')
															{
																++w.second[0];
																w.second[1] = 'a';
																w.second[2] = 'a';
																w.second[3] = 'a';
															}
															else
															{
																++w.second[1];
																w.second[2] = 'a';
																w.second[3] = 'a';
															}
														else 
														{
															++w.second[2];	
															w.second[3] = 'a';
														}
													else 
														++w.second[3];*/
													//ОТЛАДКА
			
			coded_s.clear();
			std::transform(w.second.begin(), w.second.end(), back_inserter(coded_s), Encode() );
			std::string::iterator	s_it = coded_s.begin(), 
									s_end = coded_s.end();
			code = 0;
			for (int i = 0; i < PREPROC_LVL && s_it != s_end; ++s_it)
			{
				code = 10 * code + (*s_it - CHAR_INT_DIFF);
				++i;
			}
			preproc_code = code;
			for (; s_it != s_end; ++s_it)
				code = 10 * code + (*s_it - CHAR_INT_DIFF);

			Page& p = m_g[preproc_code][code];
			p.insert(std::lower_bound(p.begin(), p.end(), w.first, PairCompare() ),
								w);						//Вставить запись о очередном слове словаря в соответствующую страницу, не нарушая её сортировки
		}
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
		for (; c != '\n';)						//цикл обработки строки сообщения
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