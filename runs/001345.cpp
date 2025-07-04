#include <iostream>
#include <vector>

using namespace std;

int n, l;
vector < vector<int> > g;
vector<char> used;
vector<int> tin, tout;
int timer;
vector < vector<int> > up;
vector < vector<int> > lngs;

void dfs (int v, int p = 0) {
	used[v] = true;
	tin[v] = ++timer;
	up[v][0] = p;
	for (int i=1; i<=l; ++i)
		up[v][i] = up[up[v][i-1]][i-1];
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
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
			lng += lngs[a][up[a][0]];
			a = up[a][0];
		} while (a != vertex);
	}
	if (b != vertex) {
		do {
			lng += lngs[b][up[b][0]];
			b = up[b][0];
		} while (b != vertex);
	}
	return lng;
}

int main() {
	cin >> n;
	g.resize(n);
	lngs.resize(n);
	for (int i=0; i<n; i++) lngs[i].resize(n);
	
	vector <int> ghlp;
	ghlp.resize(n);
	for (int i=0; i<n; i++) ghlp[i] = -1;

	for (int i=0; i<n-1; i++) {
		int v1,v2,lng;
		cin >> v1 >> v2 >> lng;
		v1--;
		v2--;

		if (ghlp[v1] == -1 && ghlp[v2] != -1) {
			g[v2].push_back(v1);
			ghlp[v1] = 1;
			ghlp[v2] = 1;
		} else {
			g[v1].push_back(v2);
			ghlp[v1] = 1;
			ghlp[v2] = 1;
		}
		lngs[v1][v2] = lng;
		lngs[v2][v1] = lng;
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
//		cout << "lca = "<< lca(a,b) << "; length = " << length(v,a,b) << endl;
		cout << length(v,a,b) << endl;
	}

	return 0;
}