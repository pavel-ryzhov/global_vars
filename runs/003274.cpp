#include <vector>
#include "math.h"
#include "stdio.h"
#include <cstring>

using namespace std;

typedef unsigned short ushort;

struct vertex_distance
{
	ushort dest_vertex;
	ushort distance;
};

const ushort MAX_VERTEX_COUNT = 40000;
const unsigned MAXLIST = MAX_VERTEX_COUNT * 2;
const ushort LOG_MAXLIST = 16;
const ushort SQRT_MAXLIST = 283;
const ushort MAXBLOCKS = MAXLIST / ((LOG_MAXLIST+1)/2) + 1;
const ushort magic_num = 65535;

vector<vector<vertex_distance> > g;
ushort vertex_count;
unsigned h[MAX_VERTEX_COUNT]; // ve rtex height
ushort a[MAXLIST]; // dfs list
ushort a_count;
ushort a_pos[MAX_VERTEX_COUNT]; // positions in dfs list
ushort block; // block size = 0.5 log A.size()
ushort bt[MAXBLOCKS][LOG_MAXLIST+1]; // sparse table on blocks (relative minimum positions in blocks)
ushort bhash[MAXBLOCKS]; // block hashes ???
ushort brmq[SQRT_MAXLIST][LOG_MAXLIST/2][LOG_MAXLIST/2]; // rmq inside each block, indexed by block hash
ushort logs2[2*MAX_VERTEX_COUNT]; // precalced logarithms (floored values)

ushort query_verts1[MAX_VERTEX_COUNT];
ushort query_verts2[MAX_VERTEX_COUNT];	

// walk graph
void dfs(ushort v = 0, ushort prev_v = 0, unsigned curh = 0) 
{
	for (ushort l = 0; l < g[v].size(); l++)
		if (g[v][l].dest_vertex == prev_v)
		{
			for (ushort k = l; k < g[v].size() - 1; k++)
				g[v][k] = g[v][k+1];
			g[v].pop_back();
		}

	h[v] = curh;
	a_pos[v] = a_count;
	a[a_count++] = v;

	for (size_t i = 0; i < g[v].size(); ++i)
			if (h[g[v][i].dest_vertex] == (unsigned)-1) 
			{
				dfs(g[v][i].dest_vertex, v, curh + g[v][i].distance);
				a[a_count++] = v;
			}
}

inline ushort log(ushort n) 
{
	ushort res = 1;
	while (1<<res < n)  
		++res;
	return res;
}

// compares two indices in a
#define min_h(i, j) ((h[a[i]]) < (h[a[j]]) ? (i) : (j))
// answers RMQ in block #bl [l;r] in O(1)
#define lca_in_block(bl, l, r)  (brmq[bhash[bl]][l][r] + bl*block)

// O(N) preprocessing
void build_lca() 
{
	ushort sz = a_count;
	block = (log(sz) + 1) / 2;
	ushort blocks = sz / block + (sz % block ? 1 : 0);

	// precalc in each block and build sparse table
	for (ushort i=0, bl=0, j=0; i < sz; ++i, ++j) 
	{
		if (j == block)
			j = 0,  ++bl;
		if (bt[bl][0] == 65535 || min_h(i, bt[bl][0]) == i)
			bt[bl][0] = i;
	}
	for (ushort j=1; j<=log(sz); ++j)
		for (ushort i=0; i<blocks; ++i) 
		{
			ushort ni = i + (1<<(j-1));
			if (ni >= blocks)
				bt[i][j] = bt[i][j-1];
			else
				bt[i][j] = min_h (bt[i][j-1], bt[ni][j-1]);
		}

	// calc hashes of blocks
	for (ushort i=0, bl=0, j=0; i<sz||j<block; ++i, ++j) 
	{
		if (j == block)
			j = 0,  ++bl;
		if (j > 0 && (i >= sz || min_h(i-1, i) == i-1))
			bhash[bl] += 1<<(j-1);
	}

	// precalc RMQ inside each unique block

	for (ushort i=0; i<blocks; ++i) 
	{
		ushort id = bhash[i];
		if (brmq[id][0][0] != 65535)  
			continue;
		for (ushort l=0; l<block; ++l) 
		{
			brmq[id][l][l] = l;
			for (ushort r=l+1; r<block; ++r) 
			{
				brmq[id][l][r] = brmq[id][l][r-1];
				if (i*block+r < sz)
					brmq[id][l][r] = min_h (i*block+brmq[id][l][r], i*block+r) - i*block;
			}
		}
	}

	// precalc logarithms
	for (ushort i=0, j=0; i<sz; ++i) 
	{
		if (1<<(j+1) <= i)  ++j;
		logs2[i] = j;
	}
}



// answers minimum distance between vertexes in O(1)
unsigned min_dist(ushort v1, ushort v2) 
{
	if (v1 == v2)
		return 0;
	ushort l = a_pos[v1],  r = a_pos[v2];
	if (l > r)  
		swap(l, r);
	ushort bl = l/block,  br = r/block;
	if (bl == br)
		return h[v1] + h[v2] - (h[a[lca_in_block(bl,l%block,r%block)]] << 1);
	ushort ans1 = lca_in_block(bl,l%block,block-1);
	ushort ans2 = lca_in_block(br,0,r%block);
	unsigned ans = min_h(ans1, ans2);
	if (bl < br - 1) 
	{
		ushort pw2 = logs2[br-bl-1];
		ushort ans3 = bt[bl+1][pw2];
		ushort ans4 = bt[br-(1<<pw2)][pw2];
		ans = min_h (ans, min_h(ans3, ans4));
	}
	return h[v1] + h[v2] - (h[a[ans]] << 1);
}

void lca_prepare()
{	
	a_count = 0;

	memset(bt, 255, sizeof bt);
	memset(brmq, 255, sizeof brmq);
	memset(h, 255, sizeof h);

	dfs();
	build_lca();
}

int main(int argc, char* argv[])
{
	ushort i;
	
	unsigned vc;
	scanf("%i", &vc);
	vertex_count = vc;
	if (vertex_count > 0)
	{ 
	  g.resize(vertex_count);
	  
	  unsigned v1, v2, l;
	  vertex_distance vd;
	  vd.dest_vertex = 0;
	  vd.distance = 0;
	  g[0].push_back(vd);
	  
	  for (i = 0; i < vertex_count - 1; i++)
	  {		  
		  scanf("%i %i %i", &v1, &v2, &l);
		  v1--;
		  v2--;		
		  vd.dest_vertex = v2;
		  vd.distance = l;
		  g[v1].push_back(vd);
		  vd.dest_vertex = v1;
		  vd.distance = l;
		  g[v2].push_back(vd);
	  }

	  lca_prepare();
	}
	else
	  return 1;


	unsigned query_count;
	scanf("%i", &query_count);
	if (query_count > 0)
	{
	  for (i = 0; i < query_count; i++)
	  {
		  unsigned v1, v2;
		  scanf("%i %i", &v1, &v2);
		  query_verts1[i] = v1 - 1;
		  query_verts2[i] = v2 - 1;		
	  }

	  for (i = 0; i < query_count; i++)
		  printf("%i\n", min_dist(query_verts1[i], query_verts2[i]));
	}	

	return 0;
}