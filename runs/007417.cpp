#include <iostream>
					//#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <deque>
#include <map>
#include <limits>


const int CHAR_INT_DIFF = 48;
const int PREPROC_LVL = 3;
const int LVL_DEGREE = 1000;

					//extern std::string FILE_PATH;

struct Encode
{
	char operator()(char c)
	{
		if (c < 's')
			return (--c / 3) + 18;
		else if (c == 's')
			return '7';
		else if (c < 'w')
			return '8';
		else 
			return '9';
	}
};

typedef std::deque<std::string> OnePriority;			//список слов из одной страницы с одним приоритетом
struct KeyInfo											//Информация о списке слов, необходимая для сортировки
{
	std::string code;
	int priority;
	KeyInfo(): code(), priority(0)
	{}
	KeyInfo(std::string s, int x): code(s), priority(x)
	{}
};
struct MapKeyLess										//Функтор сортировки множества
{
	bool operator()(const KeyInfo& k1, const KeyInfo& k2) const
	{
		return (k1.code < k2.code) || ((k1.code == k2.code) && (k1.priority < k2.priority));
	}
};
typedef std::map<KeyInfo, OnePriority, MapKeyLess> Chapter;
														//множество списков, характеризованных одинаковым префиксом кода
typedef std::vector<Chapter> Glossary;					//весь словарь как набор множеств из всех возможных префиксов


class T9
{
	
	Glossary m_g;
						//std::ifstream inputFile;



	void showWord(std::string& s, int& count)			//функция принимает строку кода слова (s) и количество звездочек (count), 
	{													//по этим данным выдаёт в поток вывода нужное слово и производит корректировку данных
		if (s.empty() )
			return;
		int preproc_code = 0,
			max_length = std::min(PREPROC_LVL, static_cast<int>(s.size() ) );
		for (int i = 0; i < max_length; ++i)
		preproc_code = 10 * preproc_code + (s[i] - CHAR_INT_DIFF);
		KeyInfo key(s, std::numeric_limits<int>::max());
		Chapter::iterator ic = --(m_g[preproc_code].lower_bound(key) );
		while(count >= static_cast<int>(ic->second.size() ) )
		{
				count -= static_cast<int>(ic->second.size() );
				--ic;
		}
		OnePriority::iterator iop = ic->second.begin();
		for(; count > 0; --count)
			++iop;										//поиск нужного слова в списке
		s = *iop;
		ic->second.erase(iop);
		std::cout << s;
		key.priority = ic->first.priority + 1;
		if (ic->second.empty() )
			m_g[preproc_code].erase(ic++);
		else
			++ic;
		if( (ic == m_g[preproc_code].end()) || (MapKeyLess()(key, ic->first) ) )
			ic = m_g[preproc_code].insert(ic, std::make_pair<const KeyInfo, OnePriority>(key, OnePriority() ) );
		ic->second.push_front(s);
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
					{
						++counter;

					}
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
						//T9(): inputFile(FILE_PATH){}
	void fill()											//заполнение словаря
	{

		int n;
		std::cin >> n;

		m_g.resize(LVL_DEGREE);

		KeyInfo key;
		std::string raw_s;
		int preproc_code;
		for (int i = 0; i < n; ++i)
		{
							//if (!(i % 1000) )
							//	std::cout << "Thousand #" << i / 1000 << "...\n";

			std::cin >> raw_s >> key.priority;
			key.code.resize(raw_s.size() );
			std::transform(raw_s.begin(), raw_s.end(), key.code.begin(), Encode() );
			preproc_code = 0;
			int max_length = std::min(PREPROC_LVL, (int)key.code.size() );
			for (int i = 0; i < max_length; ++i)
			preproc_code = 10 * preproc_code + (key.code[i] - CHAR_INT_DIFF);

			OnePriority& op = m_g[preproc_code][key];
			op.push_back(raw_s);
		}
	}
	void work()
	{
		std::string buf_s;
		std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');
														//очистка буфера потока ввода		
		int counter = 0;		
		std::cin.get();
		std::istreambuf_iterator<char> it(std::cin);
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