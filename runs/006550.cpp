#include <vector>
#include <iostream>
#include <map>
#include <stack>
#define INF  40001 * 40001
#define MAXN  40000

using namespace std;

int n;
vector<int> m,t,first,m_test;

map<int,int> dict;

vector<int> begins;
struct Edge
{
	int to,weight;
	Edge(int To, int Weight)
	{
		to = To;
		weight = Weight;
	}
};

vector< vector<Edge> > g;
int buildRMQ(int l, int r, int index)
{
	if (l == r)
	{
		t[index] = m[l];
	}
	else
	{
		t[index] = min( buildRMQ(l, (l + r) /2, 2*index), buildRMQ( (l + r)/2 + 1, r, 2*index + 1));
	}
	return t[index];
}


int findMinRMQ (int v, int tl, int tr, int l, int r)
{
	if (l > r)
		return INF;
	if (tl == l && tr == r)
		return t[v];
	int tm = (tl + tr) / 2;
	return min ( findMinRMQ(2 * v, tl, tm, l, min (r, tm)), findMinRMQ(2 * v + 1, tm + 1, tr, max(l,tm+1), r));
}

void init()
{
	begins.resize(n,0);
	first.resize(n,-1);
	m_test.reserve(2 * n);
	m.reserve(2 * n);
	
	g.resize(n);
	for (int i(0); i < n; ++i)
		g[i].reserve(max(MAXN / n, 100) );
}

int findInDict (int v)
{
	static int index = 0;
	map<int,int>::iterator it;
	int retval;

	it = dict.find(v);
	if (it == dict.end())
	{
		dict.insert( make_pair(v, index) );
		retval = index++;
	}
	else
	{
		retval = it->second;
	}

	return retval;
}


void input()
{
	
	int from,to,w;

	int index = 0;
	for (int i(0); i < n-1; ++i)
	{
		scanf("%d %d %d",&from, &to, &w);

		from = findInDict(from);
		to	 = findInDict (to);
		
		g[from].push_back( Edge(to, w) );
		g[to].push_back ( Edge(from, w) );
	}
}

void buildDFSTree()
{
	vector<bool> isUsed(2 * n, false);
	int cur = 0;
	
	stack<int> st;
	st.push(0);
	isUsed[0] = true;
	first[0] = 0;
	m.push_back(0);
	int to, w;
	while (!st.empty())
	{
		cur = st.top();
		st.pop();
		m_test.push_back(cur);
		if (m.size() != first[cur] + 1)
			m.push_back(m[first[cur]]);

		vector<Edge> &edges = g[cur];
		for (; begins[cur] < edges.size(); begins[cur]++)
		{
			int i = begins[cur];

			to = edges[i].to;
			w = edges[i].weight;
			if (!isUsed[to])
			{
				isUsed[to] = true;
				first[to] = m.size();
				m.push_back(m[first[cur]] + w);
				st.push(cur);
				st.push(to);
				break;
			}
		}
	}
}
	
int main()
{
	scanf("%d",&n);

	init();
	input();

	buildDFSTree();

	int size = m.size()-1;
	t.resize(4 * (size + 1));
	buildRMQ(0, size, 1);

	int M;
	cin >> M;
	int to,from;
	for (int i(0); i < M; ++i)
	{
		scanf("%d %d", &to, &from);
		to = findInDict(to);
		from = findInDict(from);

		if (first[to] < first[from])
			swap(to,from);
		int d = findMinRMQ ( 1,0, size, first[from], first[to] );
		int d1,d2;
		d1 = m[first[to]] - d;
		d2 = m[first[from]] - d;
		if (d1 < 0)
			d1 *= -1;
		if (d2 < 0)
			d2 *= -1;
		d = d1 + d2;
		printf("%d\n",d);
	}
	//for (int i(0); i < m.size(); ++i)
	//	printf("%d ",m[i]);
	//cout << endl;
	//for (int i(0); i < m_test.size(); ++i)
	//	printf("%d ",m_test[i]);
	//cout << endl;
	//for (int i(0); i < first.size(); ++i)
	//	printf("%d ",first[i]);
	//cout << endl;
	return 0;
}