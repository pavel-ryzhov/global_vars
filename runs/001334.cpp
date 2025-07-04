#include <iostream>
#include <vector>

using namespace std;

struct branch {
	int vertex;
	int length;
};

int n, l;
vector < vector<branch> > g;
vector<char> used;
vector<int> tin, tout;
int timer;
vector < vector<int> > up;
vector < int > lngs;

void dfs (int v, int p = 0) {
	used[v] = true;
	tin[v] = ++timer;
	up[v][0] = p;
	for (int i=1; i<=l; ++i)
		up[v][i] = up[up[v][i-1]][i-1];
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i].vertex;
		if (!used[to])
			dfs (to, v);
	}
	tout[v] = ++timer;
}

bool upper (int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b) {
	if (upper (a, b))  return a;
	if (upper (b, a))  return b;
	for (int i=l; i>=0; --i)
		if (! upper (up[a][i], b))
			a = up[a][i];
	return up[a][0];
}


int length(int vertex, int a, int b) {
	int lng = 0;
	if (a != vertex) {
		do {
			lng += lngs[a];
			a = up[a][0];
		} while (a != vertex);
	}
	if (b != vertex) {
		do {
			lng += lngs[b];
			b = up[b][0];
		} while (b != vertex);
	}
	return lng;
}

int main() {
	cin >> n;
	g.resize(n);
	lngs.resize(n);
	
	for (int i=0; i<n-1; i++) {
		int v;
		branch b;
		cin >> v >> b.vertex >> b.length;
		b.vertex--;
		g[v-1].push_back(b);
		lngs[b.vertex] = b.length;
	}

	used.resize (n),  tin.resize (n),  tout.resize (n),  up.resize (n);
	l = 1;
	while ((1<<l) <= n)  ++l;
	for (int i=0; i<n; ++i)  up[i].resize (l+1);
	dfs (0);

	int m,v,a,b;
	cin >> m;
	for (int i = 0; i<m; i++) {
		cin >> a >> b;
		a--; b--;
		v = lca(a,b);
		cout << length(v,a,b) << endl;
	}

	return 0;
}