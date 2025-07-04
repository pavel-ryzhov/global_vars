#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using std :: cin;
using std :: cout;
using std :: endl;

const int MAXN = 40000;	// max number of vertices in graph

int N, M;

std::vector<int>	g[MAXN],	// each list - neighbours of g[i]
					w[MAXN],	// weights of edges
					s[MAXN],	// straight questions list
					q[MAXN],	// questions (path(a, b))
					ind[MAXN];
int dsu[MAXN],
	ancestor[MAXN];
bool u[MAXN];
int d[MAXN];


inline int dsu_get (int v);
void dsu_unite (int a, int b, int new_ancestor);
void dfs (int v);
inline void swap(int &a, int &b);
void find_d(int v);

int main(void)
{
	// initialize random seed
	srand ( time(NULL) );
	
	// reading graph
	cin >> N;
	int a, b, weight;
	
	for (int i = 0; i < N; ++i)
		u[i] = false;
	
	for (int i = 0; i < N - 1; ++i)
	{
		cin >> a >> b >> weight;
		--a;
		--b;
		g[a].push_back(b);
		g[b].push_back(a);
		w[a].push_back(weight);
		w[b].push_back(weight);
	}
	
	cin >> M;
	
	// reading questions
	for (int i = 0; i < M; ++i)
	{
		cin >> a; // next question
		cin >> b;
		--a, --b;
		q[a].push_back (b);
		q[b].push_back (a);
		s[i].push_back (a);
		s[i].push_back (b);
		ind[a].push_back(b);
		ind[a].push_back(i);
	}

	// depth-first traversal: depth calculating
	d[0] = 0;
	for (int i = 1; i < N; ++i)
		d[i] = -1;
	find_d(0);
	
/*
	for (int i = 0; i < N; ++i)
		cout << i + 1 << " - " << d[i] << endl;
	return 0;
*/

	// depth-first traversal and answering
	dfs (0);

	for (int i = 0; i < M; ++i)
	{
		cout << s[i][2] << endl;
	}
	
	return 0;
}


inline int dsu_get (int v)
{
	return v == dsu[v] ? v : dsu[v] = dsu_get (dsu[v]);
}

void dsu_unite (int a, int b, int new_ancestor)
{
	a = dsu_get (a);
	b = dsu_get (b);
	
	//if (rand() & 1) 
	//	swap (a, b);

	dsu[a] = b;
	ancestor[b] = new_ancestor;

}

void dfs (int v)
{
	dsu[v] = v;
	ancestor[v] = v;
	
	u[v] = true;
	
	//for (int i = 0; i < N; ++i)
	//	cout << u[v] << " ";
	//cout << endl;
	
	for (int i = 0; i < g[v].size(); ++i)
		if (!u[g[v][i]])
		{
			dfs (g[v][i]);
			dsu_unite (v, g[v][i], v);
		}
		
	for (int i = 0; i < q[v].size(); ++i)
		if (u[q[v][i]])
		{
			int quest = -1;
			
			for (int j = 0; j < ind[v].size(); j += 2)
				if (ind[v][j] == q[v][i])
				{
					quest = ind[v][j + 1];
				}
			if ((quest == -1) || (s[quest].size() == 3))	
				for (int j = 0; j < ind[q[v][i]].size(); j += 2)
					if (ind[q[v][i]][j] == v)
					{
						quest = ind[q[v][i]][j + 1];
					}	
				
			if (s[quest].size() == 2)
				s[quest].push_back(d[v] + d[q[v][i]] - 2*d[ancestor[ dsu_get(q[v][i]) ]]);
			
			/*
			for (int j = 0; j < M; ++j)
				if ((s[j][0] == v && s[j][1] == q[v][i]) || (s[j][0] == q[v][i] && s[j][1] == v) )
				{
					if (s[j].size() == 3)
						break;
						
					s[j].push_back(d[v] + d[q[v][i]] - 2*d[ancestor[ dsu_get(q[v][i]) ]]);
					continue;
				}
			*/
				
			//cout << "TT " << d[v] << " " << d[q[v][i]]  << " " << d[ancestor[ dsu_get(q[v][i]) ]] << endl;
			//cout <<  v + 1 << " " << q[v][i] + 1 << " " << d[v] + d[q[v][i]] - 2*d[ancestor[ dsu_get(q[v][i]) ]] << " " << ancestor[ dsu_get(q[v][i]) ] + 1 << endl;
		}
}

inline void swap(int &a, int &b)
{
	int c = a;
	a = b;
	b = a;
}

void find_d(int v)
{
	for (int i = 0; i < g[v].size(); ++i)
		// if neighbour is not root or parent:
		if ( (g[v][i] != 0) && (d[g[v][i]] == -1) )
		{
			d[g[v][i]] = d[v] + w[v][i];
			find_d(g[v][i]);
		}
}
