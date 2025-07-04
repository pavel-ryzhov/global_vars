#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n, l;
vector < vector<int> > g;
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

class Vertex {
public:
	Vertex(int V1, int V2, int L) : v1(V1), v2(V2), length(L) {};
	friend bool operator<(const Vertex &V1, const Vertex &V2);
	int v1;
	int v2;
	int length;
};
bool operator<(const Vertex &V1, const Vertex &V2) {
	return (V1.v1 == V2.v1) ? 
			(V1.v2 < V2.v2)
			: (V1.v1 < V2.v1);
}

int main() {
	cin >> n;
	g.resize(n);
	lngs.resize(n);
	
	vector <int> gIndex;
	int gIndexN = 0;
	gIndex.resize(n+1);
	for (int i=0; i<=n; i++) gIndex[i] = -1;

	set <Vertex> gdata;

	int v1,v2,lng;
/*
	cin >> v1 >> v2 >> lng;
	gIndex[v1] = gIndexN++;
	gIndex[v2] = gIndexN++;
	g[gIndex[v1]].push_back(gIndex[v2]);
	lngs[gIndex[v2]] = lng;
*/
	for (int i=0; i<n-1; i++) {
		cin >> v1 >> v2 >> lng;
		Vertex ins = Vertex(v1,v2,lng);
		gdata.insert(ins);
	}

	// Здесь в наборе gdata исходные данные, обрабатываем:
	
	if (gdata.size())
		gIndex[gdata.begin()->v1] = gIndexN++;
	else
		gIndex[1] = 0;
	while (gdata.size()) {
		for (set<Vertex>::iterator i = gdata.begin(); i != gdata.end(); i++) {
			if (gIndex[i->v1] > -1) {
				if (gIndex[i->v2] == -1) gIndex[i->v2] = gIndexN++;
				g[gIndex[i->v1]].push_back(gIndex[i->v2]);
				lngs[gIndex[i->v2]] = i->length;
				gdata.erase(i);
				break;
			} else if (gIndex[i->v2] > -1) {
				if (gIndex[i->v1] == -1) gIndex[i->v1] = gIndexN++;
				g[gIndex[i->v2]].push_back(gIndex[i->v1]);
				lngs[gIndex[i->v1]] = i->length;
				gdata.erase(i);
				break;
			}
		}
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

		v = lca(gIndex[a],gIndex[b]);
//		cout << "lca = "<< lca(gIndex[a],gIndex[b]) << "; length = " << length(v,gIndex[a],gIndex[b]) << endl;
		cout << length(v,gIndex[a],gIndex[b]) << endl;
	}
//cin.get();
	return 0;
}