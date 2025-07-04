#include <vector>
#include "math.h"
#include "stdio.h"

using namespace std;

struct vertex_distance
{
	int dest_vertex;
	int distance;
};

typedef vector < vector<vertex_distance> > graph;

int n, root;
graph g;
vector<int> h; // vertex height
vector<int> a; // dfs list
vector<int> a_pos; // positions in dfs list
int block; // block size = 0.5 log A.size()
vector<vector<int> > bt; // sparse table on blocks (relative minimum positions in blocks)
vector<int> bhash; // block hashes
int ***brmq; // rmq inside each block, indexed by block hash
vector<int> logs2; // precalced logarithms (floored values)

// walk graph
void dfs(int v, int curh = 0) 
{
	h[v] = curh;
	a_pos[v] = (int)a.size();
	a.push_back (v);
	for (size_t i = 0; i < g[v].size(); ++i)
		if (h[g[v][i].dest_vertex] == -1) 
		{
			dfs(g[v][i].dest_vertex, curh+g[v][i].distance);
			a.push_back (v);
		}
}

int log(int n) 
{
	int res = 1;
	while (1<<res < n)  
		++res;
	return res;
}

// compares two indices in a
inline int min_h(int i, int j) 
{
	return h[a[i]] < h[a[j]] ? i : j;
}

// O(N) preprocessing
void build_lca() 
{
	int sz = (int)a.size();
	block = (log(sz) + 1) / 2;
	int blocks = sz / block + (sz % block ? 1 : 0);

	// precalc in each block and build sparse table
	for (int i=0, bl=0, j=0; i<sz; ++i, ++j) 
	{
		if (j == block)
			j = 0,  ++bl;
		if (bt[bl][0] == -1 || min_h (i, bt[bl][0]) == i)
			bt[bl][0] = i;
	}
	for (int j=1; j<=log(sz); ++j)
		for (int i=0; i<blocks; ++i) 
		{
			int ni = i + (1<<(j-1));
			if (ni >= blocks)
				bt[i][j] = bt[i][j-1];
			else
				bt[i][j] = min_h (bt[i][j-1], bt[ni][j-1]);
		}

	// calc hashes of blocks
	for (int i=0, bl=0, j=0; i<sz||j<block; ++i, ++j) 
	{
		if (j == block)
			j = 0,  ++bl;
		if (j > 0 && (i >= sz || min_h (i-1, i) == i-1))
			bhash[bl] += 1<<(j-1);
	}

	// precalc RMQ inside each unique block
	for (int i=0; i<blocks; ++i) 
	{
		int id = bhash[i];
		if (brmq[id][0][0] != -1)  
			continue;
		for (int l=0; l<block; ++l) 
		{
			brmq[id][l][l] = l;
			for (int r=l+1; r<block; ++r) 
			{
				brmq[id][l][r] = brmq[id][l][r-1];
				if (i*block+r < sz)
					brmq[id][l][r] =
						min_h (i*block+brmq[id][l][r], i*block+r) - i*block;
			}
		}
	}

	// precalc logarithms
	for (int i=0, j=0; i<sz; ++i) 
	{
		if (1<<(j+1) <= i)  ++j;
		logs2[i] = j;
	}
}

// answers RMQ in block #bl [l;r] in O(1)
inline int lca_in_block (int bl, int l, int r) 
{
	return brmq[bhash[bl]][l][r] + bl*block;
}

// answers minimum distance between vertexes in O(1)
int min_dist(int v1, int v2) 
{
	int l = a_pos[v1],  r = a_pos[v2];
	if (l > r)  
		swap(l, r);
	int bl = l/block,  br = r/block;
	if (bl == br)
		return h[v1] + h[v2] - (h[a[lca_in_block(bl,l%block,r%block)]] << 1);
	int ans1 = lca_in_block(bl,l%block,block-1);
	int ans2 = lca_in_block(br,0,r%block);
	int ans = min_h(ans1, ans2);
	if (bl < br - 1) 
	{
		int pw2 = logs2[br-bl-1];
		int ans3 = bt[bl+1][pw2];
		int ans4 = bt[br-(1<<pw2)][pw2];
		ans = min_h (ans, min_h(ans3, ans4));
	}
	return h[v1] + h[v2] - (h[a[ans]] << 1);
}

void lca_prepare()
{
	int vertex_count = g.size();
	int list_count = vertex_count * 2;
	int log_list_count = (int)(log((double)list_count) / log(2.0) + 1.0);
	int sqrt_list_count = (int)(sqrt((double)list_count) + 1.0);
	int max_blocks = list_count / ((log_list_count+1)/2) + 1;

	h.resize(vertex_count, -1);
	a_pos.resize(vertex_count);
	bt.resize(max_blocks);
	for (int i = 0; i < max_blocks; i++)
		bt[i].resize(log_list_count+1, -1);
	bhash.resize(max_blocks, 0);
	
	brmq = new int**[sqrt_list_count];
	for (int i = 0; i < sqrt_list_count; i++)
	{
		brmq[i] = new int*[log_list_count / 2];
		for (int j = 0; j < log_list_count / 2; j++)
			brmq[i][j]= new int[log_list_count / 2];
	}
	logs2.resize(2*vertex_count);

	dfs(0);
	build_lca();
}

int main(int argc, char* argv[])
{		
	int vertex_count;
	int i;

	scanf("%i", &vertex_count);
	if (vertex_count > 0)
	{ 
	  g.resize(vertex_count);

	  vertex_distance vd;
	  for (i = 0; i < vertex_count - 1; i++)
	  {
		  int v1, v2, l;
		  scanf("%i %i %i", &v1, &v2, &l);
		  v1--;
		  v2--;		
		  vd.dest_vertex = v2;
		  vd.distance = l;
		  g[v1].push_back(vd);
	  }

	  lca_prepare();
	}
	else
	  return 1;

	int query_count;
	vector<int> query_verts1;
	vector<int> query_verts2;	
	scanf("%i", &query_count);
	if (query_count > 0)
	{
	  query_verts1.resize(query_count);
	  query_verts2.resize(query_count);
	  for (i = 0; i < query_count; i++)
	  {
		  int v1, v2;
		  scanf("%i %i", &v1, &v2);
		  query_verts1[i] = v1 - 1;
		  query_verts2[i] = v2 - 1;		
	  }

	  for (i = 0; i < query_count; i++)
		  printf("%i\n", min_dist(query_verts1[i], query_verts2[i]));
	}
	else
		return 1;

	return 0;
}