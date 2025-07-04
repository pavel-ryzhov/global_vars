#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>

using namespace std;


class CTree
{
	public:
		CTree(int n);
		void printWord(const vector<int>& req, int k);
	private:
		class CTreeNode
		{
			public:
                CTreeNode()
                {
                    m_childs.reserve(10);
                }
				unsigned char m_digit;
				vector <int> m_childs;
				map <int, list <int> > m_words;
		};
		vector<vector<bool> > m_words;
		vector<CTreeNode> m_tree;
};

unsigned char table[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
unsigned char toChar[10] = {0, 0, 'a', 'd', 'g', 'j', 'm', 'p', 't', 'w'};
unsigned char shift[26] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 3, 0, 1, 2, 0, 1, 2, 3};


CTree::CTree(int n)
	: m_words(n)
	, m_tree(1)
{
    m_tree.reserve(20);
	m_tree[0].m_digit = -1;
	std::string str;
	int f;
	for (int i = 0; i < n; ++i)
	{
		cin >> str >> f;
		m_words[i].resize(str.length() * 2, 0);
		int cur = 0;
		for (int j = 0; j < str.size(); ++j)
		{
			m_words[i][2 * j] = static_cast<bool>(shift[str[j] - 'a'] / 2);
			m_words[i][2 * j + 1] = static_cast<bool>(shift[str[j] - 'a'] % 2);
			bool nodeExist = false;
			for (int k = 0; k < m_tree[cur].m_childs.size(); ++k)
			{
				if (m_tree[m_tree[cur].m_childs[k]].m_digit == table[str[j] - 'a'])
				{
					cur = m_tree[cur].m_childs[k];
					nodeExist = true;
					break;
				}
			}
			if (!nodeExist)
			{
				m_tree.resize(m_tree.size() + 1);
				m_tree.back().m_digit = table[str[j] - 'a'];
				m_tree[cur].m_childs.push_back(m_tree.size() - 1);
				cur = m_tree.size() - 1;
			}
		}
        m_tree[cur].m_words[-f].push_back(i);
	}

}

void
CTree::printWord(const vector<int>& req, int k)
{
	if (1 == req.size() && 1 == req[0])
	{
		char ans[3] = {'.', ',', '?'};
		cout << ans[k];
	}
	else
	{
		string str;
		str.resize(req.size());
		int cur = 0;
		for (int i = 0; i < str.size(); ++i)
		{
			str[i] = toChar[req[i]];
			for (int j = 0; j < m_tree[cur].m_childs.size(); ++j)
			{
				if (m_tree[m_tree[cur].m_childs[j]].m_digit == req[i])
				{
					cur = m_tree[cur].m_childs[j];
					break;
				}
			}

		}


        map<int, list<int> >::iterator prevIt = m_tree[cur].m_words.begin();
        map<int, list<int> >::iterator curIt = m_tree[cur].m_words.begin();
        //если слов текущим приоритетом меньше, чем кол-во пропускаемых
        while (k >= curIt->second.size())
        {
            prevIt = curIt;
            k -= curIt->second.size();
            //пропускаем всю группу
            ++curIt;
        }
        list<int>::iterator it(curIt->second.begin());
        for (int i = 0; i < k; ++i)
        {
            ++it;
        }
        //если существуют слова с новым преоритетом, вставляем индекс перед ними
        if (prevIt->first == curIt->first - 1)
        {
            prevIt->second.push_front(*it);
        }
        else //иначе заводим новый список с этим приоритетом
        {
            m_tree[cur].m_words[curIt->first - 1].push_front(*it);
        }

        //сдвигаем каждую букву в слове на ее смещение
		for (int i = 0; i < str.size(); ++i)
		{
			str[i] += 2 * m_words[*it][2 * i];
			str[i] += m_words[*it][2 * i + 1];
		}
        curIt->second.erase(it);
		cout << str;
	}
}

int main()
{
	int n(0);
	std::cin >> n;
	CTree tree(n);

	vector <int> req(0);
    req.reserve(20);
	int k = 0;
	string str;
	str.reserve(100000);
	getline(cin, str);
	getline(cin, str);
	for (int i = 0; i < str.length(); ++i)
	{
		int c = str[i];
		
		if (c == '1')
		{
            if (req.size() != 0)
            {
    			tree.printWord(req, k);
            }
			req.resize(1);
			req[0] = 1;
			k = 0;
		}
		if (c == ' ')
		{
			
            if (req.size() != 0)
            {
    			tree.printWord(req, k);
            }
			cout << ' ';
			req.resize(0);
			k = 0;
		}
		if (c == '*')
		{
			++k;
		}

		if ('2' <= c && c <= '9')
		{
            if (req.size() != 0 && req[0] == 1)
            {
    			tree.printWord(req, k);
		    	req.resize(0);
			    k = 0;                
            }
		    req.push_back(c - '0');
		}

	}
	if (0 != req.size())
	{
		tree.printWord(req, k);
	}

		
	return 0;
}