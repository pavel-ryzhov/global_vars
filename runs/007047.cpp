#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct word
{
	string s;
	int f;
	void set(string st, int fr) {s = st; f = fr;}
	bool operator< (const word & w) {return f < w.f;}
};

typedef vector< vector<int> > tree;
typedef vector< list<word> > vocabulary;

void read_words(tree & t, vocabulary & v)
{
	int n, f;
	cin >> n;
	string s;
	word w;
	int lookup[] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4,
		5, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7};
	vector<int> vec(8);
	t.push_back(vec);
	t.push_back(vec);
	v.resize(1);
	w.set(".", 0);
	v[0].push_back(w);
	w.set(",", 0);
	v[0].push_back(w);
	w.set("?", 0);
	v[0].push_back(w);
	for (int i = 1; i < n + 1; i++)
	{
		cin >> s >> f;
		w.set(s, f);
		int cur_node = 1;
		for (int j = 0; j < s.length(); j++)
		{
			int digit = lookup[s[j]-'a'];
			if (t[cur_node][digit] == 0)
			{
				t.push_back(vec);
				t[cur_node][digit] = t.size() - 1;
			}
			cur_node = t[cur_node][digit];
		}
		if (v.size() <= cur_node)
		{
			v.resize(cur_node + 1);
		}
		list<word>::iterator iter = v[cur_node].begin();
		while (iter != v[cur_node].end() && !(*iter < w))
		{
			iter++;
		}
		v[cur_node].insert(iter, w);
	}
}

void end_of_word(tree & t, vocabulary & v, int & cur_node, list<word>::iterator cur_word, bool & flag)
{
	if (cur_node == 1)
	{
		return;
	}
	if (flag)
	{
		cur_word = v[cur_node].begin();
	}
	cout << cur_word->s;
	if (cur_node != 0)
	{
		cur_word->f++;
		list<word>::iterator tmp = v[cur_node].begin();
		while (*cur_word < *tmp)
		{
			tmp++;
		}
		if (tmp != cur_word)
		{
			v[cur_node].insert(tmp, *cur_word);
			v[cur_node].erase(cur_word);
		}
	}
	cur_node = 1;
	flag = true;
}

int main()
{
	const int LEN = 100001;
	tree t;
	vocabulary v;
	read_words(t, v);
	char s[LEN];
	cin.getline(s, LEN);
	cin.getline(s, LEN);
	int i = 0;
	int cur_node = 1;
	list<word>::iterator cur_word;
	bool flag = true;
	while (s[i] != 0)
	{
		switch (s[i])
		{
		case '1':
			end_of_word(t, v, cur_node, cur_word, flag);
			cur_node = 0;
			break;
		case '*':
			if (flag)
			{
				flag = false;
				cur_word = v[cur_node].begin();
			}
			cur_word++;
			break;
		case ' ':
			end_of_word(t, v, cur_node, cur_word, flag);
			cout << ' ';
			break;
		default:
			cur_node = t[cur_node][s[i] - '0' - 2];
		}
		i++;
	}
	end_of_word(t, v, cur_node, cur_word, flag);
	return 0;
}