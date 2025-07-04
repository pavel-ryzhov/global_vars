#include <vector>
#include <iostream>
#include <string.h>

using namespace std;
const int MAXN = 40000;
const int MAXLIST = MAXN * 2;
const int LOG_MAXLIST = 18;
const int SQRT_MAXLIST = 447;
const int MAXBLOCKS = MAXLIST / ((LOG_MAXLIST+1)/2) + 1;

int n, root;
vector< vector<int * > > g;

int h[MAXN];
int hw[MAXN];
vector<int> a;
int a_pos[MAXN];
int block;
int bt[MAXBLOCKS][LOG_MAXLIST+1];
int bhash[MAXBLOCKS];
int brmq[SQRT_MAXLIST][LOG_MAXLIST/2][LOG_MAXLIST/2];
int log2[2*MAXN];

vector<int> names;

void dfs (int v, int curh, int curhw) {
	h[v] = curh;
	hw[v] = curhw;
	a_pos[v] = (int)a.size();
	a.push_back (v);
	for (size_t i=0; i<g[v].size(); ++i)
		if (h[g[v][i][0]] == -1) {
			dfs (g[v][i][0], curh+1, curhw + g[v][i][1]);
			a.push_back (v);
		}
}

int log (int n) {
	int res = 1;
	while (1<<res < n)  ++res;
	return res;
}

inline int min_h (int i, int j) {
	return h[a[i]] < h[a[j]] ? i : j;
}

void build_lca() {
	int sz = (int)a.size();
	block = (log(sz) + 1) / 2;
	int blocks = sz / block + (sz % block ? 1 : 0);

	memset (bt, 255, sizeof bt);
	for (int i=0, bl=0, j=0; i<sz; ++i, ++j) {
		if (j == block)
			j = 0,  ++bl;
		if (bt[bl][0] == -1 || min_h (i, bt[bl][0]) == i)
			bt[bl][0] = i;
	}
	for (int j=1; j<=log(sz); ++j)
		for (int i=0; i<blocks; ++i) {
			int ni = i + (1<<(j-1));
			if (ni >= blocks)
				bt[i][j] = bt[i][j-1];
			else
				bt[i][j] = min_h (bt[i][j-1], bt[ni][j-1]);
		}

	memset (bhash, 0, sizeof bhash);
	for (int i=0, bl=0, j=0; i<sz||j<block; ++i, ++j) {
		if (j == block)
			j = 0,  ++bl;
		if (j > 0 && (i >= sz || min_h (i-1, i) == i-1))
			bhash[bl] += 1<<(j-1);
	}

	memset (brmq, 255, sizeof brmq);
	for (int i=0; i<blocks; ++i) {
		int id = bhash[i];
		if (brmq[id][0][0] != -1)  continue;
		for (int l=0; l<block; ++l) {
			brmq[id][l][l] = l;
			for (int r=l+1; r<block; ++r) {
				brmq[id][l][r] = brmq[id][l][r-1];
				if (i*block+r < sz)
					brmq[id][l][r] =
						min_h (i*block+brmq[id][l][r], i*block+r) - i*block;
			}
		}
	}

	for (int i=0, j=0; i<sz; ++i) {
		if (1<<(j+1) <= i)  ++j;
		log2[i] = j;
	}
}

inline int lca_in_block (int bl, int l, int r) {
	return brmq[bhash[bl]][l][r] + bl*block;
}

int lca (int v1, int v2) {
	int l = a_pos[v1],  r = a_pos[v2];
	if (l > r)  swap (l, r);
	int bl = l/block,  br = r/block;
	if (bl == br)
		return a[lca_in_block(bl,l%block,r%block)];
	int ans1 = lca_in_block(bl,l%block,block-1);
	int ans2 = lca_in_block(br,0,r%block);
	int ans = min_h (ans1, ans2);
	if (bl < br - 1) {
		int pw2 = log2[br-bl-1];
		int ans3 = bt[bl+1][pw2];
		int ans4 = bt[br-(1<<pw2)][pw2];
		ans = min_h (ans, min_h (ans3, ans4));
	}
	return a[ans];
}

int get_index(int vertex)
{
	unsigned int index;
	for(index=0; index < names.size();index++)
		if(names[index]==vertex) break;

	if(index == names.size())
		names.push_back(vertex);

	return index;
}

void free_memory(int N)
{
	for(int i=0; i<N;i++)
	{
		for(unsigned int j=0; j<g[i].size();j++)
		{
			delete[] g[i][j];
			g[i][j]=0;
		}
	}
}

int get_distance(int a,int b)
{
	int lca_a_b = lca(a,b);
	return hw[a] - hw[lca_a_b] + hw[b] - hw[lca_a_b];
}

int main()
{
	 int a,b,w;
	 cin>>n;
	 g.reserve(n);

	 for(unsigned int i=0; i<n; i++)
	 {
		vector<int *> edges_for_vertex;
		g.push_back(edges_for_vertex);
		h[i] = -1;
	 }

	 for(unsigned int i=0;i<n-1;i++)
	 {
		cin>>a>>b>>w;

		int first = get_index(a);
		int second = get_index(b);
		int * edge = new int[2];
		edge[0] = second;
		edge[1] = w;
		g[first].push_back(edge);

		int * edge2 = new int[2];
		edge2[0] = first;
		edge2[1] = w;
		g[second].push_back(edge2);
	 }

	 dfs(0,0,0);
	 build_lca();

	 int M;
	 cin>>M;
	 for(unsigned int i=0; i<M;i++)
	 {
		int a,b;
		cin>>a>>b;
		int first = get_index(a);
		int second = get_index(b);
		cout<<get_distance(first, second)<<endl;
	 }

	 free_memory(n);
	 return 0;
}