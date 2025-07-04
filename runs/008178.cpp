#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector< vector<int> > graph;
typedef map <set<int>, int> edges_type;
typedef map <multiset<int>, int> answer_type;
typedef vector< multiset<int> > task_type;

const int MAXN = 100000;//максимальное число вершин в графе;
graph g, q; // граф и все запросы
int dsu[MAXN], ancestor[MAXN], dfs_h[MAXN];
bool u[MAXN];
 
int dsu_get (int v)
{
	return v == dsu[v] ? v : dsu[v] = dsu_get (dsu[v]);
}
 
void dsu_unite (int a, int b, int new_ancestor)
{
	a = dsu_get (a),  b = dsu_get (b);
	if (rand() & 1)  swap (a, b);
	dsu[a] = b,  ancestor[b] = new_ancestor;
}
 
void dfs (int v, const edges_type &e, answer_type &answer, int h)
{
	dsu[v] = v,  ancestor[v] = v;
	u[v] = true;
	dfs_h[v] = h;
	for (size_t i=0; i<g[v].size(); ++i)
		if (!u[g[v][i]])
		{
			set<int> buff;
			buff.insert(g[v][i]);
			buff.insert(v);
			dfs (g[v][i], e, answer, h + e.find(buff)->second);
			dsu_unite (v, g[v][i], v);
		}
	for (size_t i=0; i<q[v].size(); ++i)
		if (u[q[v][i]])
		{
			multiset<int> buff;
			buff.insert(v+1);
			buff.insert(q[v][i]+1);
			answer.insert(pair<multiset<int>, int>(buff,
									 dfs_h[v]+dfs_h[q[v][i]]-2*dfs_h[ancestor[ dsu_get(q[v][i]) ]]));
/*			printf ("%d %d -> %d\n", v+1, q[v][i]+1,
				dfs_h[v]+dfs_h[q[v][i]]-2*dfs_h[ancestor[ dsu_get(q[v][i]) ]]);*/
		}
}

void g_input(edges_type &e, task_type &ts)
{
/*	//чтение графа
		int init[42] = {9,
					1, 2, 0,
					2, 9, 5,
					3, 9, 0,
					4, 9, 8,
					5, 9, 7,
					6, 8, 2,
					7, 5, 0,
					8, 7, 1,
					8,
					6, 5,
					2, 3,
					3, 3,
					4, 1,
					3, 7,
					3, 6,
					5, 7,
					8, 2};
	vector<int> input(init, init+42);*/
	vector<int> input;
	vector<int>::iterator it_input;
	copy(istream_iterator<int>(cin),istream_iterator<int>(), back_inserter(input));
	int i = 0;
	int n = input[0];
	int m = input[(n-1)*3+1];
	for(;i<n;i++)
	{
		g.push_back(vector<int>());
		q.push_back(vector<int>());
	}
	
	for (i=1;i<=*(input.begin());i++) { //здесь точки заполняются связями
		g[i-1].push_back(i-1);

		set<int> buff;
		buff.insert(input.at((i-1)*3+1)-1);
		buff.insert(input.at((i-1)*3+2)-1);
		e.insert(pair<set<int>, int>(buff,
									 input.at((i-1)*3+3)));

		for (it_input = input.begin()+1; it_input < input.begin()+(n-1)*3; it_input = it_input + 3)
		{
			if (*it_input==i)
				g[i-1].push_back(*(it_input+1)-1);
			else
				if(*(it_input+1)==i)
					g[i-1].push_back(*it_input-1);
		}
	} //заполнились*/
	for (i=(n-1)*3+2; i<=input.size()-2; i=i+2)
	{
		q[input[i]-1].push_back(input[i+1]-1);
		q[input[i+1]-1].push_back(input[i]-1);
		multiset<int> ts_buff;
		ts_buff.insert(input[i]);
		ts_buff.insert(input[i+1]);
		ts.push_back(ts_buff);
	}
}

int main()
{
	edges_type e;
	answer_type answer;
	task_type ts;
	task_type::iterator ts_iter;

	g_input(e, ts);
	dfs(0, e, answer, 0);

	for(ts_iter=ts.begin(); ts_iter!=ts.end(); ++ts_iter)
		cout << answer.find(*ts_iter)->second << endl;
	
	return 0;
}