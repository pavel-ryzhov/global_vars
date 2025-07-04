#include <map>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

struct Node
{
	map <pair <int, int>, int> m;
	int next[10];

	Node()
	{
		memset (next, -1, 10 * sizeof(int));
	}
};

const int MAXN = 50001;
const int MAXLEN = 21;

map <string, map <pair <int, int>, int> > m;

int n;
char dict[MAXN][MAXLEN + 1];
char signs[] = {'.',',','?'};
char CtoI['z'+1];
int t(0);

void init()
{
	CtoI[0] = 0;
	CtoI['a'] = '2';
	CtoI['b'] = '2';
	CtoI['c'] = '2';

	CtoI['d'] = '3';
	CtoI['e'] = '3';
	CtoI['f'] = '3';

	CtoI['g'] = '4';
	CtoI['h'] = '4';
	CtoI['i'] = '4';

	CtoI['j'] = '5';
	CtoI['k'] = '5';
	CtoI['l'] = '5';

	CtoI['m'] = '6';
	CtoI['n'] = '6';
	CtoI['o'] = '6';

	CtoI['p'] = '7';
	CtoI['q'] = '7';
	CtoI['r'] = '7';
	CtoI['s'] = '7';

	CtoI['t'] = '8';
	CtoI['u'] = '8';
	CtoI['v'] = '8';


	CtoI['w'] = '9';
	CtoI['x'] = '9';
	CtoI['y'] = '9';
	CtoI['z'] = '9';
}


void input()
{

	scanf("%d\n", &n);
	
	map <string, map <pair <int, int>, int> >::iterator it;
	int freq(0);
	
	string s;
	s.reserve(MAXLEN);

	for (t = 0; t < n; ++t)
	{
		s.clear();
		
		scanf("%s %d\n", dict[t], &freq);

		for (int i(0); dict[t][i] != 0; ++i)
			s.push_back( (int)CtoI[ dict[t][i] ] );

		
		
		it = m.find(s);

		if (it == m.end())
		{
			map <pair <int, int>, int> m1;
			m1.insert (make_pair (make_pair(freq, n - t), t ) );
			m.insert( make_pair (s, m1) );
		}
		else
		{
			(*it).second.insert(make_pair (make_pair(freq,n - t), t ) );
		}
	}
}

void update(map <pair <int, int>, int> &m1, map <pair <int, int>, int>::iterator &it1)
{
	int freq = it1->first.first;
	int word = it1->second;

	m1.erase(it1);
	m1.insert(make_pair (make_pair (freq+1, t++), word) );
}


void printWord(int &count, string &s)
{
	map <pair <int, int>, int> &m1 = m.find(s)->second;
	map <pair <int, int>, int>::iterator it1 = m.find(s)->second.end();
	it1--;

	for (int i(0); i < count; ++i)
	{
		if ( it1 != m1.begin())
			it1--;
		else
		{
			it1 = m1.end();
			it1--;
		}
	}

	printf("%s", dict [it1->second] );
	update (m1, it1);
	count = 0;
	s.clear();
}

void solve()
{
	char c;

	string s;
	s.reserve(MAXLEN);

	

	bool isFirst = true;

	int sign = -1;

	int count = 0;

	while (scanf("%c", &c) != EOF)
	{
		if (c >= '2' && c <= '9')
		{
			s.push_back(c);
		}
		else
		{
			switch (c)
			{
			case ' ':
				if (sign > -1)
				{
					printf("%c ", signs[(sign+count)%3]);
					sign = -1;
					count = 0;
				}
				else
				{
					if (s.size() > 0)
					{
						printWord(count, s);
						
						s.clear();
					}
					printf(" ");
				}
				break;
			case '1':
				if (sign > -1)
				{
					printf("%c", signs[(sign+count)%3]);
					sign = -1;
					count = 0;
				}
				sign++;
				if (s.size() > 0)
				{
					printWord(count, s);
				}
				break;
			case '*':
				count++;
				break;
			default:
				break;
			}
		}
	}
	if (sign > -1)
		printf("%c", signs[(sign+count)%3]);
	else
		if (s.size() > 0)
			printWord(count, s);
	
	printf("\n");
}


int main()
{
	init();
	input();
	solve();
	return 0;
}