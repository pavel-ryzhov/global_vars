//============================================================================
// Name        : yandex-derevo-pod.cpp
// Author      : Vladimir Verstov
// Version     :
// Copyright   : @Vladimir Verstov
// Description : yandex-derevo, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

using namespace std;

struct TPair
{
	int start;
	int end;
};
struct Link
{
	int target;
	int weight;
};

vector<TPair> pairs;

int n, l;
vector < vector<Link> > g;
vector<char> used;
vector<int> tin, tout;
int timer;
vector < vector<Link> > up;

void dfs (Link lnk, Link p) {
	used[lnk.target] = true;
	tin[lnk.target] = ++timer;
	up[lnk.target][0] = p;
	for (int i=1; i<=l; ++i)
		up[lnk.target][i] = up[up[lnk.target][i-1].target][i-1];
	for (size_t i=0; i<g[lnk.target].size(); ++i) {
		Link to = g[lnk.target][i];
		lnk.weight = to.weight;
		if (!used[to.target])
			dfs (to, lnk);
	}
	tout[lnk.target] = ++timer;
}

bool upper (int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b) {
	if (upper (a, b))  return a;
	if (upper (b, a))  return b;
	for (int i=l; i>=0; --i)
		if (! upper (up[a][i].target, b))
			a = up[a][i].target;
	return up[a][0].target;
}

int min_way (int b, int e, int way = 0)
{
	if (b == e)
		return way;
	if (upper(b,e))
	{
		way += up[e][0].weight;
		return min_way(b, up[e][0].target, way);
	}
	if (upper(e,b))
	{
		way += up[b][0].weight;
		return min_way(up[b][0].target, e, way);
	}
	int m = b;
	for (int i=l; i>=0; --i)
		if (!upper (up[m][i].target, e))
			m = up[m][i].target;
	m = up[m][0].target;
	return min_way(b,m) + min_way(m,e);
}

int main() {
	int size, i, j, m;
	vector<TPair>::iterator itrPairs;
	TPair pair;
	Link lnk;
	cin >> n;
	g.resize(n);
	for (int k=0; k<n-1; k++)
	{
		cin >> i >> j >> size;
		lnk.target = j-1;
		lnk.weight = size;
		g[i-1].push_back(lnk);
		lnk.target = i-1;
		lnk.weight = size;
		g[j-1].push_back(lnk);
	}
	cin >> m;
	for (int k=0; k<m; k++)
	{
		cin >> pair.start >> pair.end;
		pairs.push_back(pair);
	}
	used.resize (n),  tin.resize (n),  tout.resize (n),  up.resize (n);
	l = 1;
	while ((1<<l) <= n)  ++l;
	for (int i=0; i<n; ++i)  up[i].resize (l+1);
	lnk.target = 0;
	lnk.weight = 0;
	dfs (lnk, lnk);
	itrPairs = pairs.begin();
	while (itrPairs != pairs.end())
	{
		cout << min_way(itrPairs->start-1, itrPairs->end-1) << endl;
		itrPairs++;
	}
}
