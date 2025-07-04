#include <stdio.h>
#include <vector>
#include <utility>

using namespace std;

const int MAX = 40010;
int l;
vector <vector<pair<int, int> > > g;
vector <int> used;
vector <int> tin, tout;
int timer;
vector <vector<int> > up;
vector <vector<int> > up_len;

void dfs(int v, int p) {
	used[v] = true;
	tin[v] = ++timer;
	up[v][0] = p;
	if (p == v) up_len[v][0] = 0;
	else {
		for (size_t i = 0; i < g[v].size(); i++) 
			if (g[v][i].first == p){
				up_len[v][0] = g[v][i].second;
				break;
			}
	}
	for (int i = 1; i <= l; i++) {
		up[v][i] = up[up[v][i-1]][i-1];
		up_len[v][i] = up_len[v][i-1] + up_len[up[v][i-1]][i-1];
		//printf("up_len[%d][%d] = %d\n", v, i, up_len[v][i]);
	}
	for (size_t i = 0; i < g[v].size(); i++) {
		int to = g[v][i].first;
		if (!used[to])
			dfs(to, v);
	}
	tout[v] = ++timer;
}

bool upper(int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
	if (upper(a, b)) return a;
	if (upper(b, a)) return b;
	for (int i = l; i >= 0; i--)
		if (!upper(up[a][i], b))
			a = up[a][i];
	return up[a][0];
}

int main() {
	int N, M;
	scanf("%d", &N);
	int u, v, len;
	g.resize(MAX);
	for (int i = 0; i < N-1; i++) {
		scanf("%d %d %d", &u, &v, &len);
		g[u].push_back(make_pair(v, len));
		g[v].push_back(make_pair(u, len));
	}
	
	used.resize(MAX);
	tin.resize(MAX);
  tout.resize(MAX);
  up.resize(MAX);
  up_len.resize(MAX);
	l = 1;
	while ((1<<l) <= N)  l++;
	for (int i = 0; i < N+10; i++) {
		up[i].resize(l+2);
		up_len[i].resize(l+2);
	}
	dfs(u, u);

	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		int LCA = lca(a, b);
		//printf("LCA(%d, %d) = %d\n", a, b, LCA);
		int res = 0;
		if (a != LCA) {
			for (int i = l; i >= 0; i--)
				if (!upper(up[a][i], LCA)) {
					res += up_len[a][i];
					a = up[a][i];
				}
			res += up_len[a][0];
		}
		if (b != LCA) {
			for (int i = l; i >= 0; i--)
				if (!upper(up[b][i], LCA)) {
					res += up_len[b][i];
					b = up[b][i];
				}
			res += up_len[b][0];
		}
		printf("%d\n", res);
	}

	return 0;
}
