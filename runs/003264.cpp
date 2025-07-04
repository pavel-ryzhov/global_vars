#include <vector>
#include "math.h"
#include "stdio.h"
#include <cstring>

using namespace std;

const unsigned MAX_VERTEX_COUNT = 40000;
const unsigned MAXLIST = MAX_VERTEX_COUNT * 2;
const unsigned LOG_MAXLIST = 17;
const unsigned SQRT_MAXLIST = 283;
const unsigned MAXBLOCKS = MAXLIST / ((LOG_MAXLIST+1)/2) + 1;

const unsigned magic_num = 65535;
unsigned vertex_count;
unsigned h[MAX_VERTEX_COUNT]; // ve rtex height
unsigned a[MAXLIST]; // dfs list
unsigned a_count;
unsigned a_pos[MAX_VERTEX_COUNT]; // positions in dfs list
unsigned block; // block size = 0.5 log A.size()
unsigned bt[MAXBLOCKS][LOG_MAXLIST+1]; // sparse table on blocks (relative minimum positions in blocks)
unsigned bhash[MAXBLOCKS]; // block hashes
unsigned brmq[SQRT_MAXLIST][LOG_MAXLIST/2][LOG_MAXLIST/2]; // rmq inside each block, indexed by block hash
unsigned logs2[2*MAX_VERTEX_COUNT]; // precalced logarithms (floored values)

unsigned query_verts1[MAX_VERTEX_COUNT];
unsigned query_verts2[MAX_VERTEX_COUNT];	

unsigned short *coherency_matrix;

// walk graph
void dfs(unsigned v = 0, unsigned prev_v = 0, unsigned curh = 0) 
{
	coherency_matrix[v * vertex_count + prev_v] = magic_num;
	h[v] = curh;
	a_pos[v] = a_count;
	a[a_count++] = v;

	for (size_t i = 0; i < vertex_count; ++i)
		if (coherency_matrix[v * vertex_count + i] != magic_num &&  h[i] == (unsigned)-1) 
		{
			dfs(i, v, curh + coherency_matrix[v * vertex_count + i]);
			a[a_count++] = v;
		}
}

inline unsigned log(unsigned n) 
{
	unsigned res = 1;
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
	unsigned sz = a_count;
	block = (log(sz) + 1) / 2;
	unsigned blocks = sz / block + (sz % block ? 1 : 0);

	// precalc in each block and build sparse table
	for (unsigned i=0, bl=0, j=0; i<sz; ++i, ++j) 
	{
		if (j == block)
			j = 0,  ++bl;
		if (bt[bl][0] == -1 || min_h(i, bt[bl][0]) == i)
			bt[bl][0] = i;
	}
	for (unsigned j=1; j<=log(sz); ++j)
		for (unsigned i=0; i<blocks; ++i) 
		{
			unsigned ni = i + (1<<(j-1));
			if (ni >= blocks)
				bt[i][j] = bt[i][j-1];
			else
				bt[i][j] = min_h (bt[i][j-1], bt[ni][j-1]);
		}

	// calc hashes of blocks
	for (unsigned i=0, bl=0, j=0; i<sz||j<block; ++i, ++j) 
	{
		if (j == block)
			j = 0,  ++bl;
		if (j > 0 && (i >= sz || min_h(i-1, i) == i-1))
			bhash[bl] += 1<<(j-1);
	}

	// precalc RMQ inside each unique block

	for (unsigned i=0; i<blocks; ++i) 
	{
		unsigned id = bhash[i];
		if (brmq[id][0][0] != -1)  
			continue;
		for (unsigned l=0; l<block; ++l) 
		{
			brmq[id][l][l] = l;
			for (unsigned r=l+1; r<block; ++r) 
			{
				brmq[id][l][r] = brmq[id][l][r-1];
				if (i*block+r < sz)
					brmq[id][l][r] =
						min_h (i*block+brmq[id][l][r], i*block+r) - i*block;
			}
		}
	}

	// precalc logarithms
	for (unsigned i=0, j=0; i<sz; ++i) 
	{
		if (1<<(j+1) <= i)  ++j;
		logs2[i] = j;
	}
}



// answers minimum distance between vertexes in O(1)
unsigned min_dist(unsigned v1, unsigned v2) 
{
	if (v1 == v2)
		return 0;
	unsigned l = a_pos[v1],  r = a_pos[v2];
	if (l > r)  
		swap(l, r);
	unsigned bl = l/block,  br = r/block;
	if (bl == br)
		return h[v1] + h[v2] - (h[a[lca_in_block(bl,l%block,r%block)]] << 1);
	unsigned ans1 = lca_in_block(bl,l%block,block-1);
	unsigned ans2 = lca_in_block(br,0,r%block);
	unsigned ans = min_h(ans1, ans2);
	if (bl < br - 1) 
	{
		unsigned pw2 = logs2[br-bl-1];
		unsigned ans3 = bt[bl+1][pw2];
		unsigned ans4 = bt[br-(1<<pw2)][pw2];
		ans = min_h (ans, min_h(ans3, ans4));
	}
	return h[v1] + h[v2] - (h[a[ans]] << 1);
}

void lca_prepare()
{
	memset(bt, 255, sizeof bt);
	memset(brmq, 255, sizeof brmq);
	memset(h, 255, sizeof h);

	a_count = 0;

	dfs();
	build_lca();
}

int main(int argc, char* argv[])
{
	unsigned i;
	
	scanf("%i", &vertex_count);
	if (vertex_count > 0)
	{ 
	  coherency_matrix = new unsigned short[vertex_count * vertex_count];	
	  memset(coherency_matrix, 255, vertex_count * vertex_count * 2);

	  for (i = 0; i < vertex_count - 1; i++)
	  {
		  unsigned v1, v2, l;
		  scanf("%i %i %i", &v1, &v2, &l);
		  v1--;
		  v2--;		
		  coherency_matrix[v2 * vertex_count + v1] = l;
		  coherency_matrix[v1 * vertex_count + v2] = l;
	  }

	  lca_prepare();
	  
	  delete coherency_matrix;
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