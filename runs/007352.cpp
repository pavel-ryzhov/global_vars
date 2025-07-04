
#include <iostream>

#include <algorithm>

#include <iterator>
#include <vector>
#include <string>
#include <list>
#include <map>

typedef std::pair<int, std::string> WordInfo;			//������ �� ����� ����� ������� � ��������������� ��� ������� �������������
typedef std::list<WordInfo> Page;						//������ ������� � ������, �������������� � ������� ����� ����������� �����
typedef std::vector<Page::iterator> Contents;			//���������� ����� ��������;
struct PageInfo
{
	Contents first;
	Page second;
};
typedef std::map<std::string, PageInfo> Chapter;		//��������� �������, ����������������� ���������� ��������� ����
typedef std::vector<Chapter> Glossary;					//���� ������� ��� ����� �������� �� ���� ��������� ���������

const int CHAR_INT_DIFF = 48;
const int PREPROC_LVL = 2;
const int LVL_DEGREE = 100;

class PairCompare			//������� ��� ��������� ���������-��� �� ������� ����
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
/*
struct Encode
{
	char operator()(char c) const
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
*/
inline char Encode(char c) 
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



class T9
{
	
	Glossary m_g;

	void showWord(std::string& s, int& count)			//������� ��������� ������ ���� ����� (s) � ���������� ��������� (count), 
	{													//�� ���� ������ ����� � ����� ������ ������ ����� � ���������� ������������� ������
		if (s.empty() )
			return;
		std::string::iterator	s_it = s.begin(), 
								s_end = s.end();
		int preproc_code = 0;
		for (int i = 0; ++i <= PREPROC_LVL && s_it != s_end; ++s_it)
			preproc_code = 10 * preproc_code + (*s_it - CHAR_INT_DIFF);

		Page& p = (m_g[preproc_code].find(s) )->second.second;
		Page::reverse_iterator ri = p.rbegin();
		for(int i = 0; i < count; ++i)
			++ri;										//����� ������� ����� � ������
		std::cout << ri->second;
		Page::iterator curr = --(ri.base() );
		p.splice(std::upper_bound(curr, p.end(), ++(ri->first), PairCompare() ), 
						p, curr);			//����� ������ ����� ��� ����� � ������ ����� ������� �������������, ������� �� ��� �����
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
	void fill()											//���������� �������
	{
		int n, x;
		std::cin >> n;

		m_g.resize(LVL_DEGREE);

		WordInfo w;
		std::string coded_s;
		int preproc_code;
		Page::iterator ip, new_ip, end_ip;
													//�������
													/*
													srand(n);
													w.second = "aaaaaaaa";
													coded_s = "22222222";
													int s_size = 8;
													*/
													//�������
		std::istreambuf_iterator<char> i_it;
		std::string::iterator s_it, s_end;
		for (int i = 0; i < n; ++i)
		{
			std::cin.ignore(std::cin.rdbuf()->in_avail() );
			std::cin.get();

			w.second.clear();
			coded_s.clear();
			preproc_code = 0;
			i_it = std::cin;
			for(; *i_it != ' '; ++i_it)
			{
				w.second.push_back(*i_it);
				coded_s.push_back(Encode(*i_it) );
			}
			std::cin >> w.first;



													//�������
													/*
													w.first = rand() % 1000;
													if (i % 1000 == 0)
														std::cout << "Thousand #" << i / 1000 << "...\n";
													
													if (w.second[5] == 'f')
														if (w.second[4] == 'f')
															if (w.second[3] == 'f')
																if (w.second[2] == 'f')
																	if (w.second[1] == 'f')
																	{
																		++w.second[0];
																		w.second[1] = 'a';
																		w.second[2] = 'a';
																		w.second[3] = 'a';
																		w.second[4] = 'a';
																		w.second[5] = 'a';
																	}
																	else
																	{
																		++w.second[1];
																		w.second[2] = 'a';
																		w.second[3] = 'a';
																		w.second[4] = 'a';
																		w.second[5] = 'a';
																	}
																else 
																{
																	++w.second[2];	
																	w.second[3] = 'a';
																	w.second[4] = 'a';
																	w.second[5] = 'a';
																}
															else 
															{
																++w.second[3];
																w.second[4] = 'a';
																w.second[5] = 'a';
															}
														else
														{
															++w.second[4];
															w.second[5] = 'a';
														}
													else
														++w.second[5];

													
													for(int j = 0; j < 8; ++j)
														coded_s[j] = Encode(w.second[j]);
													*/
													//�������
			
			s_it = coded_s.begin(); 
			s_end = coded_s.end();
			preproc_code = 0;
			for (int i = 0; ++i <= PREPROC_LVL && s_it != s_end; ++s_it)
				preproc_code = 10 * preproc_code + (*s_it - CHAR_INT_DIFF);

			PageInfo& rpi = m_g[preproc_code][coded_s];
			end_ip = rpi.second.end();
			if (rpi.first.empty() )
				rpi.first.assign(11, end_ip);
			x = w.first / 100;
			ip = rpi.first[x];	
			new_ip = rpi.second.insert(std::lower_bound(ip, end_ip, w.first, PairCompare() ),
								w);						//�������� ������ � ��������� ����� ������� � ��������������� ��������, �� ������� � ����������
			if (++new_ip == ip)
			{
				--new_ip;
				for (; x >= 0 && (rpi.first[x] == end_ip || rpi.first[x]->first >= new_ip->first); --x)
					rpi.first[x] = new_ip;
			}

		}
	}
	void work()
	{
		std::string buf_s;
		std::cin.ignore(std::cin.rdbuf()->in_avail());
														//������� ������ ������ ����		
		int counter = 0;		
		std::cin.get();
		std::istreambuf_iterator<char> it (std::cin);
		char c = *it;
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
