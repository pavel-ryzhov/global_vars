//e-maxx ru/algo/lca_linear

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

typedef vector< pair <long,long long int> >::const_iterator const_graph_iter;

static const long  MAXN = 40001;
static const long MAXLIST = MAXN * 2;
static const long LOG_MAXLIST = 16;
static const long SQRT_MAXLIST = 201;
static const long MAXBLOCKS = MAXLIST / ((LOG_MAXLIST+1)/2) + 1;

static vector< pair <long, long long int> > g[MAXN];
static long h[MAXN]; // vertex height
static long long int h_long[MAXN]; // vertex height
static vector<long> a; // dfs list
static long a_pos[MAXN]; // positions in dfs list
static long block; // block size = 0.5 log A.size()
static long bt[MAXBLOCKS][LOG_MAXLIST+1]; // sparse table on blocks (relative minimum positions in blocks)
static long bhash[MAXBLOCKS]; // block hashes
static long brmq[SQRT_MAXLIST][LOG_MAXLIST/2][LOG_MAXLIST/2]; // rmq inside each block, indexed by block hash
static long log2[2*MAXN]; // precalced logarithms (floored values)

// walk graph
static void dfs (long v, long curh,long long int curh_long) 
{	
	h[v] = curh;   
	h_long[v]=curh_long;
	a_pos[v] = (long)a.size();
	a.push_back (v); 
	for (const_graph_iter i=g[v].begin(); i!=g[v].end(); ++i)      
		if (0 == h[i->first]) 
		{         
			dfs (i->first, curh+1,curh_long+i->second);
			a.push_back (v);
		}
}

static long log (long n) 
{
	long res = 1;
	while (1<<res < n)  ++res;
	return res;
}

// compares two indices in a
static inline long min_h (long i, long j) 
{
	return h[a[i]] < h[a[j]] ? i : j;
}

// O(N) preprocessing
static void build_lca() 
{
	long sz = (long)a.size();
	block = (log(sz) + 1) / 2;
	long blocks = sz / block + (sz % block ? 1 : 0);

	// precalc in each block and build sparse table
	memset (bt, 255, sizeof bt);
	for (long i=0, bl=0, j=0; i<sz; ++i, ++j) 
	{
		if (j == block)
			j = 0,  ++bl;
		if (bt[bl][0] == -1 || min_h (i, bt[bl][0]) == i)
			bt[bl][0] = i;
	}
	for (long j=1; j<=log(sz); ++j)
		for (long i=0; i<blocks; ++i)
		{
			long ni = i + (1<<(j-1));
			if (ni >= blocks)
				bt[i][j] = bt[i][j-1];
			else
				bt[i][j] = min_h (bt[i][j-1], bt[ni][j-1]);
		}

	// calc hashes of blocks
	memset (bhash, 0, sizeof bhash);
	for (long i=0, bl=0, j=0; i<sz||j<block; ++i, ++j)
	{
		if (j == block)
			j = 0,  ++bl;
		if (j > 0 && (i >= sz || min_h (i-1, i) == i-1))
			bhash[bl] += 1<<(j-1);
	}

	// precalc RMQ inside each unique block
	memset (brmq, 255, sizeof brmq);
	for (long i=0; i<blocks; ++i)	
	{
		long id = bhash[i];
		if (brmq[id][0][0] != -1)  continue;
		for (long l=0; l<block; ++l) 
		{
			brmq[id][l][l] = l;
			for (long r=l+1; r<block; ++r) 
			{
				brmq[id][l][r] = brmq[id][l][r-1];
				if (i*block+r < sz)
					brmq[id][l][r] =
						min_h (i*block+brmq[id][l][r], i*block+r) - i*block;
			}
		}
	}

	// precalc logarithms
	for (long i=0, j=0; i<sz; ++i)
	{
		if (1<<(j+1) <= i)  ++j;
		log2[i] = j;
	}
}

// answers RMQ in block #bl [l;r] in O(1)
static inline long lca_in_block (long bl, long l, long r) {
	return brmq[bhash[bl]][l][r] + bl*block;
}

// answers LCA in O(1)
static long lca2 (long v1, long v2)
{
	long l = a_pos[v1],  r = a_pos[v2];
	if (l > r)  swap (l, r);
	long bl = l/block,  br = r/block;
	if (bl == br)
		return a[lca_in_block(bl,l%block,r%block)];

	long ans1 = lca_in_block(bl,l%block,block-1);
	long ans2 = lca_in_block(br,0,r%block);
	long ans = min_h (ans1, ans2);
	if (bl < br - 1) 
	{
		long pw2 = log2[br-bl-1];
		long ans3 = bt[bl+1][pw2];
		long ans4 = bt[br-(1<<pw2)][pw2];
		ans = min_h (ans, min_h (ans3, ans4));
	}
	return a[ans];
}
//---------------------------------------------------------


int main()
{
   long N,N1,N2,M;
   long long int iH;
   long minPos=MAXN;
   bool bError=false;

   cin>>N;

   if (N>MAXN || N<0)
	   bError=true;

   if (N >=2)
   {
	   for(long i = 0; i < N-1; ++i)
	   {	
		  cin>>N1>>N2>>iH;
		  if (N1!=N2)
		  {
			  minPos=min(N2,min(minPos,N1));
			  g[N1].push_back(pair<long,long long int> (N2,iH));
			  g[N2].push_back(pair<long,long long int> (N1,iH));
		  }
		  if (N1>MAXN || N2>MAXN || iH>MAXN || N1<0 || N2<0 || iH<0)
			  bError=true;
	   }
	      
	   dfs(minPos,1,1);
	   build_lca();
   }

   cin>>M;

   if (M>MAXN || M<0)
	   bError=true;

   if (!bError)
   {

	   for(long i = 0; i < M; ++i)
	   {
		  long v,v1,v2;
		  cin>>v1>>v2;
		  if (N>=2)
		  {	   
			  if (v1>=0 && v2>=0 && v1<=MAXN && v2<=MAXN && v1!=v2 && h_long[v1]!=0 && h_long[v2]!=0 )
			  {
				  v = lca2 (v1, v2); // ответ на запрос   
				  long long int lHt=(h_long[v1]-h_long[v])+(h_long[v2]-h_long[v]);
				  cout << lHt << endl;
			  }
			  else
			  {
				  cout<<0<<endl;
			  }
		  }
		  else
		  {
			  cout<<0<<endl;
		  }
	   }
   }
   else
   {
	   cout<<"ERROR"<<endl;
   }

   return 0;
}