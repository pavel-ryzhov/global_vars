#include <iostream>
#include <stdlib.h>
#include <vector>
#include <set>
#include <map>


using	 namespace std;


const int MAXN = 6;
typedef	map <pair<int,int>,int> maps;


	//maps req;
	//vector <pair<int,int> > req_pos;
vector< vector <pair<int, int> > > g;
	//vector< vector <int> >q; // граф и все запросы
	//vector <int> dsu , ancestor;
	//vector <bool> u;
/*
int dsu_get (int v) {
	return v == dsu[v] ? v : dsu[v] = dsu_get (dsu[v]);
}

void dsu_unite (int a, int b, int new_ancestor) {
	a = dsu_get (a),  b = dsu_get (b);
	if (rand() & 1)  swap (a, b);
	dsu[a] = b,  ancestor[b] = new_ancestor;
}

void dfs (int v) {
	dsu[v] = v,  ancestor[v] = v;
	u[v] = true;
	for (size_t i=0; i<g[v].size(); ++i)
		if (!u[g[v][i].first]) {
			dfs (g[v][i].first);
			dsu_unite (v, g[v][i].first, v);
		}
	for (size_t i=0; i<q[v].size(); ++i)
		if (u[q[v][i]]) {
				//	printf ("%d %d -> %d\n", v+1, q[v][i]+1,ancestor[ dsu_get(q[v][i]) ]+1);
			int	a=v+1, b=q[v][i]+1;
			if (a>b) {
				swap(a, b);
			}
			req[make_pair(a, b)]=ancestor[ dsu_get(q[v][i]) ]+1;
		}
}
*/
int findpath (int start, int to, int from) {
	if (start==to) {
		return 0;
	}
	int r=0;
	for (int i=0; i<g[start].size(); ++i) {
			if (g[start][i].first==(to)) {
			return g[start][i].second;
		}
			if (g[start][i].first!=from) {
			r=findpath(g[start][i].first,to,start);
			if (r!=-1) {
					//cout << r<< endl;
				return (g[start][i].second+r);
			}
			}
		}


	
	
	return -1;
}

int main (int argc, char * const argv[]) {
		//чтение графа
	
	int n;
	
	scanf("%d", &n);
	g.resize(n);
/*	q.resize(n);
	dsu.resize(n);
	ancestor.resize(n);
	u.resize(n);
*/
	for (int i = 0; i < (n-1); ++i)
	{
		int a, b, w = 0;
		scanf("%d %d %d", &a, &b, &w);
			//g[a-1][b-1]=1;
			//g[b-1][a-1]=1;
		g[a - 1].push_back(make_pair(b-1, w));
		g[b - 1].push_back(make_pair(a-1, w));
	}
	/*int m;
	scanf("%d", &m);
	for (int j=0; j<m; ++j) {
		int a, b; // текущий запрос
		scanf("%d %d", &a, &b);
		if (a>b) {
			swap(a, b);
		}
		req[make_pair(a, b)]=0;
		req_pos.push_back(make_pair(a, b));
		--a, --b;
		q[a].push_back (b);
		q[b].push_back (a);
	}
	*/
	
		// обход в глубину и ответ на запросы
		//dfs (0);
	/*for (vector <pair<int,int> >::iterator i=req_pos.begin(); i!=req_pos.end(); ++i) {
			//cout << i->first << " " << i->second <<" -> " << req[*i] << endl;
		int a=findpath(req[*i]-1, i->first-1,0);
		int b=findpath(req[*i]-1, i->second-1,0);
			//cout<< a<<" "<<b<<" " <<(a+b) << endl;
			cout << (a+b) << endl;
	}
	 */
	//cout << findpath(0, 1) << endl;
	
	int m=0;
	
	scanf("%d", &m);
	for (int j=0; j<m; ++j) {
		int a, b; // текущий запрос
		scanf("%d %d", &a, &b);
		cout << findpath(a-1, b-1,0)<< endl;
	}
	
	return 0;
}
