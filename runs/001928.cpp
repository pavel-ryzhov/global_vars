//e-maxx ru/algo/lca_linear

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

typedef vector< pair <int,long long int> >::const_iterator const_graph_iter;

static const int MAXN = 40001;
static const int MAXLIST = MAXN * 2;
static const int LOG_MAXLIST = 16;
static const int SQRT_MAXLIST = 201;
static const int MAXBLOCKS = MAXLIST / ((LOG_MAXLIST+1)/2) + 1;

static vector< pair <int, long long int> > g[MAXN];
static int h[MAXN]; // vertex height
static long long int h_long[MAXN]; // vertex height
static vector<int> a; // dfs list
static int a_pos[MAXN]; // positions in dfs list
static int block; // block size = 0.5 log A.size()
static int bt[MAXBLOCKS][LOG_MAXLIST+1]; // sparse table on blocks (relative minimum positions in blocks)
static int bhash[MAXBLOCKS]; // block hashes
static int brmq[SQRT_MAXLIST][LOG_MAXLIST/2][LOG_MAXLIST/2]; // rmq inside each block, indexed by block hash
static int log2[2*MAXN]; // precalced logarithms (floored values)

// walk graph
static void dfs (int v, int curh,long long int curh_long) 
{	
	h[v] = curh;   
	h_long[v]=curh_long;
	a_pos[v] = (int)a.size();
	a.push_back (v); 
	for (const_graph_iter i=g[v].begin(); i!=g[v].end(); ++i)      
		if (0 == h[i->first]) 
		{         
			dfs (i->first, curh+1,curh_long+i->second);
			a.push_back (v);
		}
}

static int log (int n) 
{
	int res = 1;
	while (1<<res < n)  ++res;
	return res;
}

// compares two indices in a
static inline int min_h (int i, int j) 
{
	return h[a[i]] < h[a[j]] ? i : j;
}

// O(N) preprocessing
static void build_lca() 
{
	int sz = (int)a.size();
	block = (log(sz) + 1) / 2;
	int blocks = sz / block + (sz % block ? 1 : 0);

	// precalc in each block and build sparse table
	memset (bt, 255, sizeof bt);
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
	memset (bhash, 0, sizeof bhash);
	for (int i=0, bl=0, j=0; i<sz||j<block; ++i, ++j)
	{
		if (j == block)
			j = 0,  ++bl;
		if (j > 0 && (i >= sz || min_h (i-1, i) == i-1))
			bhash[bl] += 1<<(j-1);
	}

	// precalc RMQ inside each unique block
	memset (brmq, 255, sizeof brmq);
	for (int i=0; i<blocks; ++i)	
	{
		int id = bhash[i];
		if (brmq[id][0][0] != -1)  continue;
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
		log2[i] = j;
	}
}

// answers RMQ in block #bl [l;r] in O(1)
static inline int lca_in_block (int bl, int l, int r) {
	return brmq[bhash[bl]][l][r] + bl*block;
}

// answers LCA in O(1)
static int lca2 (int v1, int v2)
{
	int l = a_pos[v1],  r = a_pos[v2];
	if (l > r)  swap (l, r);
	int bl = l/block,  br = r/block;
	if (bl == br)
		return a[lca_in_block(bl,l%block,r%block)];

	int ans1 = lca_in_block(bl,l%block,block-1);
	int ans2 = lca_in_block(br,0,r%block);
	int ans = min_h (ans1, ans2);
	if (bl < br - 1) 
	{
		int pw2 = log2[br-bl-1];
		int ans3 = bt[bl+1][pw2];
		int ans4 = bt[br-(1<<pw2)][pw2];
		ans = min_h (ans, min_h (ans3, ans4));
	}
	return a[ans];
}
//---------------------------------------------------------


int main()
{
   int N,N1,N2,M;
   long long int iH;
   int minPos=MAXN;

   cin>>N;

   if (N >=2)
   {
	   for(int i = 0; i < N-1; ++i)
	   {
		  cin>>N1>>N2>>iH;
		  minPos=min(N2,min(minPos,N1));
		  g[N1].push_back(pair<int,long long int> (N2,iH));
		  g[N2].push_back(pair<int,long long int> (N1,iH));
	   }
	      
	   dfs(minPos,1,1);
	   build_lca();
   }

   cin>>M;

   for(int i = 0; i < M; ++i)
   {
      int v,v1,v2;
      cin>>v1>>v2;
	  if (N>=2)
	  {	   
		  v = lca2 (v1, v2); // ответ на запрос      
		  cout << h_long[v1]+h_long[v2]-2*h_long[v]<< endl;
	  }
	  else
	  {
		  cout<<0<<endl;
	  }
   }

   return 0;
}