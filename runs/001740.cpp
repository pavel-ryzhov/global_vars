#include <iostream>
#include <vector>

using namespace std; 

int N, M, h;
vector < vector< pair<int, int> > > g;
vector<char> used;
vector<int> tin, tout;
int timer;
vector < vector<int> > up, dist;

void dfs (int v, int l, int p = 0) {
	used[v] = true;
	tin[v] = timer++;
	up[v][0] = p;
	dist[v][0] = l;
	for (int i = 1; i <= h; i++)
	{
		dist[v][i] = dist[up[v][i-1]][i-1] + dist[v][i-1];
		up[v][i] = up[up[v][i-1]][i-1];
	}
	for (size_t i = 0; i < g[v].size(); i++) {
		int to = g[v][i].first;
		if (!used[to])
			dfs (to, g[v][i].second, v);
	}
	tout[v] = timer++;
}

bool upper (int a, int b) {
	return (tin[a] <= tin[b]) && (tout[a] >= tout[b]);
}

int lca (int a, int b) {
	if (a == b) return 0;
	if (upper (a, b)) swap(a, b);

	int l = 0;
	for (int i = h; i >= 0; i--)
		if (! upper (up[a][i], b))
		{
			l += dist[a][i];
			a = up[a][i];
		}

	
	return l + dist[a][0];

}

int main() {
	std::cin >> N;

	g.resize(N);
	used.resize (N);  
	tin.resize (N);  
	tout.resize (N);
	up.resize (N);
	dist.resize (N);
	
	for (int i = 0; i < N - 1; i++)
	{
		int a, b, l;
		std::cin >> a >> b >> l;
		a--;
		b--;
		g[a].push_back(pair<int,int>(b, l));
		g[b].push_back(pair<int,int>(a, l));
	}

	h = 1;
	while ((1 << h) <= N) h++;
	for (int i = 0; i < N; i++)  
	{ 
		up[i].resize (h + 1);
		dist[i].resize (h + 1);
	}

	dfs (0, 0);

	std::cin >> M;
	for (int i = 0; i < M; i++) {
		int a, b;
		std::cin >> a >> b;
		a--;
		b--;
		int res;
		if (upper (a, b) || upper (b, a)) 
				res = lca(a, b);
			else
				res = lca(a, b) + lca(b, a);
		std::cout << res << "\n";
	}
	return 0;
}