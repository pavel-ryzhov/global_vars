#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct int2 
{
	int f;
	int p;
	int2(int fr, int ptr){f = fr; p = ptr;}
	bool operator< (const int2 & i) const {return (f == i.f) ? (p < i.p) : (f > i.f);}
};

typedef vector< vector<int> > tree;
typedef vector< vector<int2> > vocabulary;

void read_words(tree & t, vocabulary & v, vector<string> & w)
{
	int n, f, nnodes, nwords;
	cin >> n;
	int lookup[] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4,
		5, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7};
	vector<int> vec(8);
	t.resize(n * 20, vec);
	nnodes = 1;
	v.resize(n * 20);
	w.resize(n + 3);
	w[0] = ".";
	w[1] = ",";
	w[2] = "?";
	nwords = 2;
	v[0].push_back(int2(0, 0));
	v[0].push_back(int2(0, 1));
	v[0].push_back(int2(0, 2));
	for (int i = 1; i < n + 1; i++)
	{
		cin >> w[++nwords] >> f;
		int cur_node = 1;
		for (int j = 0; j < w[nwords].length(); j++)
		{
			int digit = lookup[w[nwords][j]-'a'];
			if (t[cur_node][digit] == 0)
			{
				nnodes++;
				t[cur_node][digit] = nnodes;
			}
			cur_node = t[cur_node][digit];
		}
		v[cur_node].push_back(int2(f, nwords));
	}
	for (int i = 1; i <= nnodes; i++)
	{
		if (!v[i].empty())
			sort(v[i].begin(), v[i].end());
	}
}

void end_of_word(vocabulary & v, const vector<string> & w, int & cur_node, vector<int2>::iterator cur_word, bool & flag)
{
	if (cur_node == 1)
	{
		return;
	}
	if (flag)
	{
		cur_word = v[cur_node].begin();
	}
	cout << w[cur_word->p];
	if (cur_node != 0)
	{
		cur_word->f++;
		while (cur_word != v[cur_node].begin() && ((cur_word-1)->f <= cur_word->f))
		{
			swap(*(cur_word-1), *cur_word);
			cur_word--;
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
	vector<string> w;
	read_words(t, v, w);
	char s[LEN];
	cin.getline(s, LEN);
	cin.getline(s, LEN);
	int i = 0;
	int cur_node = 1;
	vector<int2>::iterator cur_word;
	bool flag = true;
	while (s[i] != 0)
	{
		switch (s[i])
		{
		case '1':
			end_of_word(v, w, cur_node, cur_word, flag);
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
			end_of_word(v, w, cur_node, cur_word, flag);
			cout << ' ';
			break;
		default:
			if (cur_node == 0)
			{
				end_of_word(v, w, cur_node, cur_word, flag);
			}
			cur_node = t[cur_node][s[i] - '0' - 2];
		}
		i++;
	}
	end_of_word(v, w, cur_node, cur_word, flag);
	return 0;
}