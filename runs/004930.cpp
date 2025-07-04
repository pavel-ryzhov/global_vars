#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int INF = 400000;

int n, m;
int** graph;
//int** dist;
int way_find(int, int);

int way_find(int st, int end)
{
	vector<int> d(n, INF);
	d[st] = 0;
	
	set < pair<int, int> > q;
	q.insert(make_pair(d[st], st));

	while(!q.empty())
	{
		int v = q.begin()->second;
		q.erase(q.begin());

		for(int i = 0; i < n; i++)
		{	
			int v2 = i, r = graph[v][i];
			if(r > -1)
			{
				if(d[v] + r < d[v2])
				{
					q.erase(make_pair(d[v2], v2));
					d[v2] = d[v] + r;
					q.insert(make_pair(d[v2], v2));
				}
				if(v2 == end) return d[v2];
			}
		}
	}
	
	return d[end];
}

int main()
{
	int v1, v2, r;
	cin >> n;
	
	graph = new int*[n];
	//dist = new int*[n];
	
	for(int i = 0; i < n; i++)
	{
		graph[i] = new int[n];
		//dist[i] = new int[n];
		for(int j = 0; j < n; j++)
		{graph[i][j] = -1; 
		//dist[i][j] = -1;
		}
	}
	
	for(int i = 0; i < n-1; i++)
	{
		cin >> v1 >> v2 >> r;
		graph[v1 - 1][v2 - 1] = r;
		graph[v2 - 1][v1 - 1] = r;
	}
	
	int test_num, vs1, vs2, res;
	cin >> test_num;
	//int* res = new int[test_num];

	for(int i = 0; i < test_num; i++)
	{
		cin >> vs1 >> vs2;
		res = way_find(vs1 - 1, vs2 - 1);
		if(res == -1) res = 0;
		cout << res;
	}
	
	return 0;
}

/* ALG
const int INF = 1000000000;
 
int main() {
	int n;
	... чтение n ...
	vector < vector < pair<int,int> > > g (n);
	... чтение графа ...
	int s = ...; // стартовая вершина
 
	vector<int> d (n, INF),  p (n);
	d[s] = 0;
	set < pair<int,int> > q;
	q.insert (make_pair (d[s], s));
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase (q.begin());
 
		for (size_t j=0; j<g[v].size(); ++j) {
			int to = g[v][j].first,
				len = g[v][j].second;
			if (d[v] + len < d[to]) {
				q.erase (make_pair (d[to], to));
				d[to] = d[v] + len;
				p[to] = v;
				q.insert (make_pair (d[to], to));
			}
		}
	}
}

*/