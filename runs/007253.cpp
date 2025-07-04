
#include <iostream>

#include <algorithm>

#include <iterator>
#include <hash_map>
#include <string>
#include <list>

template <class SomePair>
	class PairCompare			//������� ��� ��������� ���������-��� �� ������� ����
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

typedef std::pair<unsigned int, std::string> WordInfo;	//������ �� ����� ����� ������� � ��������������� ��� ������� �������������
typedef std::list<WordInfo> Page;						//������ ������� � ������, �������������� � ������� ����� ����������� �����
typedef std::pair<std::string, Page> Data;
typedef std::vector<Data> Glossary;

const double OPTIMIZE = 0.2;
const int MAX_STRING = 10000;

class T9
{
	Glossary m_g;

	void showWord(std::string& s, int& count)//������� ��������� ������ ���� ����� (s) � ���������� ��������� (count), 
	{													//�� ���� ������ ����� � ����� ������ ������ ����� � ���������� ������������� ������
		if (s.empty() )
			return;

				//�������
		//std::cout << "I'm trying to show word! It's code is " << s << ";\n";
				//�������

		Page& p = std::lower_bound(m_g.begin(), m_g.end(), s, PairCompare<Data>() )->second;

				//�������
		/*std::cout << "I've found Page, here is info of it:\n";
		for (Page::iterator ii = p.begin(); ii != p.end(); ++ii)
				std::cout << "\tWord: " << ii->second << "\tFrequency: " << ii->first << std::endl;*/
				//�������

		Page::reverse_iterator ri = p.rbegin();
		for(int i = 0; i < count; ++i)
			++ri;										//����� ������� ����� � ������

				//�������
		//std::cout	<< "I've found Word, here is info of it:\n" << "\tWord: " << ri->second << "\tFrequency: " << ri->first << std::endl;
				//�������

		std::cout << ri->second;
		p.splice(std::upper_bound(p.begin(), p.end(), ++(ri->first), PairCompare<WordInfo>() ), 
						p, --(ri.base() ) );			//����� ������ ����� ��� ����� � ������ ����� ������� �������������, ������� �� ��� �����
		count = 0;
		s.clear();
	}
	void setsymbol(char& c, int& counter, std::istreambuf_iterator<char>& it, std::string& buf_s)
	{
				//�������
		//std::cout << "Now I'm setting symbol " << c << "...\n";
				//�������

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
	void fill()											//���������� �������
	{
		int n;
		std::cin >> n;
		m_g.reserve(n);
		
		WordInfo w;
		Data d;

		std::cin >> w.second >> w.first;
		std::transform(w.second.begin(), w.second.end(), back_inserter(d.first), Encode() );	
														//������������� ����� � ��� �������� ���������� �9 � �������� � d
		m_g.push_back(d);

		Glossary::iterator iter = m_g.begin();
		iter->second.insert(std::lower_bound(iter->second.begin(), iter->second.end(), w.first, PairCompare<WordInfo>() ),
							w);							//�������� ������ � ��������� ����� ������� � ��������������� ��������, �� ������� � ����������
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
			Glossary(m_g).swap(m_g);					//��������� ������� ������������������ �����
		
				//�������		
		/*std::cout << "Glossary is full now! It contains:\n";
		for (iter = m_g.begin(); iter != m_g.end(); ++iter)
		{
			std::cout << "\nPage with code: " << iter->first << std::endl;
			for (Page::iterator ii = iter->second.begin(); ii != iter->second.end(); ++ii)
				std::cout << "\tWord: " << ii->second << "\tFrequency: " << ii->first << std::endl;
		}*/
				//�������

	}
	void work()
	{
		std::string buf_s;
		std::cin.ignore(std::cin.rdbuf()->in_avail());
														//������� ������ ������ ����		
		int counter = 0;		
		char c = std::cin.get();
		std::istreambuf_iterator<char> it (std::cin);
		setsymbol(c, counter, it, buf_s);
		for (; c != '\n';)						//���� ��������� ������ ���������
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