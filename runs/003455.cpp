#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;


class CTree
{
	public:
		CTree(int n);
		void printWord(const vector<int>& req, int k);
	private:
		class CWord
		{
			public:
				int m_count;
				vector <bool> m_shift;
		};
		class CTreeNode
		{
			public:
				unsigned char m_digit;
				vector <int> m_childs;
				list <int> m_words;
		};
		vector<CWord> m_words;
		vector<CTreeNode> m_tree;
};

unsigned char table[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
unsigned char toChar[10] = {0, 0, 'a', 'd', 'g', 'j', 'm', 'p', 't', 'w'};
unsigned char shift[26] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 3, 0, 1, 2, 0, 1, 2, 3};


CTree::CTree(int n)
	: m_words(n)
	, m_tree(1)
{
	m_tree[0].m_digit = -1;
	std::string str;
	int f;
	for (int i = 0; i < n; ++i)
	{
		cin >> str >> f;
		m_words[i].m_count = f;
		m_words[i].m_shift.resize(str.length() * 2, 0);
		int cur = 0;
		for (int j = 0; j < str.size(); ++j)
		{
			m_words[i].m_shift[2 * j] = static_cast<bool>(shift[str[j] - 'a'] / 2);
			m_words[i].m_shift[2 * j + 1] = static_cast<bool>(shift[str[j] - 'a'] % 2);
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
		list<int>::iterator it = m_tree[cur].m_words.begin();
		while(it != m_tree[cur].m_words.end() && m_words[*it].m_count >= f)
			++it;
		m_tree[cur].m_words.insert(it, i);


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
		
		list<int>::iterator firstPrev = m_tree[cur].m_words.begin();
		list<int>::iterator firstCur = m_tree[cur].m_words.begin();
		list<int>::iterator prevIt = m_tree[cur].m_words.begin();
		list<int>::iterator curIt = m_tree[cur].m_words.begin();
		for (int i = 0; i < k; ++i)
		{
			prevIt = curIt;
			++curIt;
			if (m_words[*prevIt].m_count != m_words[*curIt].m_count)
			{
				firstPrev = firstCur;
				firstCur = curIt;
			}
		}
		if (m_words[*firstPrev].m_count == m_words[*curIt].m_count + 1)
		{
			m_tree[cur].m_words.insert(firstPrev, *curIt);
			m_words[*curIt].m_count++;
		}
		else
		{
			m_tree[cur].m_words.insert(firstCur, *curIt);
			m_words[*curIt].m_count++;
		}

		for (int i = 0; i < str.size(); ++i)
		{
			str[i] += 2 * m_words[*curIt].m_shift[2 * i];
			str[i] += m_words[*curIt].m_shift[2 * i + 1];
		}
		m_tree[cur].m_words.erase(curIt);
		cout << str;
	}
}

int main()
{
	int n(0);
	std::cin >> n;
	CTree tree(n);

	vector <int> req(0);
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
			req.push_back(c - '0');
		}

	}
	if (0 != req.size())
	{
		tree.printWord(req, k);
	}

		
	return 0;
}