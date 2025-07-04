#include <vector>
#include <iostream>
#include <map>
#include <string.h>

const int MAXN = 4000*1000;
const int MAXLIST = MAXN * 2;
const int LOG_MAXLIST = 18;
const int SQRT_MAXLIST = 447;
const int MAXBLOCKS = MAXLIST / ((LOG_MAXLIST+1)/2) + 1;

int n, root;
//std::vector<int> g[MAXN];

struct ChildVertex{
	int Number;
	int Length;
	ChildVertex(int Number_,int Length_=1): Number(Number_),Length(Length_) {}
};

typedef std::vector < std::vector<ChildVertex> > graph;
graph g;
std::map<int,int> EqualVertex;

int h[MAXN]; // vertex height
std::vector<int> a; // dfs list
int a_pos[MAXN]; // positions in dfs list
int block; // block size = 0.5 log A.size()
int bt[MAXBLOCKS][LOG_MAXLIST+1]; // sparse table on blocks (relative minimum positions in blocks)
int bhash[MAXBLOCKS]; // block hashes
int brmq[SQRT_MAXLIST][LOG_MAXLIST/2][LOG_MAXLIST/2]; // rmq inside each block, indexed by block hash
int log2[2*MAXN]; // precalced logarithms (floored values)

// walk graph
void dfs (int v, int curh) {
	h[v] = curh;
	a_pos[v] = (int)a.size();
	a.push_back (v);
	for (size_t i=0; i<g[v].size(); ++i)
		if (h[g[v][i].Number] == -1) {
			dfs (g[v][i].Number, curh+g[v][i].Length);
			a.push_back (v);
		}
}

int log (int n) {
	int res = 1;
	while (1<<res < n)  ++res;
	return res;
}

// compares two indices in a
inline int min_h (int i, int j) {
	return h[a[i]] < h[a[j]] ? i : j;
}

// O(N) preprocessing
void build_lca() {
	int sz = (int)a.size();
	block = (log(sz) + 1) / 2;
	int blocks = sz / block + (sz % block ? 1 : 0);

	// precalc in each block and build sparse table
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

	// calc hashes of blocks
	memset (bhash, 0, sizeof bhash);
	for (int i=0, bl=0, j=0; i<sz||j<block; ++i, ++j) {
		if (j == block)
			j = 0,  ++bl;
		if (j > 0 && (i >= sz || min_h (i-1, i) == i-1))
			bhash[bl] += 1<<(j-1);
	}

	// precalc RMQ inside each unique block
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

	// precalc logarithms
	for (int i=0, j=0; i<sz; ++i) {
		if (1<<(j+1) <= i)  ++j;
		log2[i] = j;
	}
}

// answers RMQ in block #bl [l;r] in O(1)
inline int lca_in_block (int bl, int l, int r) {
	return brmq[bhash[bl]][l][r] + bl*block;
}

// answers LCA in O(1)
int lca (int v1, int v2) {
	int l = a_pos[v1],  r = a_pos[v2];
	if (l > r)  std::swap (l, r);
	int bl = l/block,  br = r/block;
	if (bl == br)
		return a[lca_in_block(bl,l%block,r%block)];
	int ans1 = lca_in_block(bl,l%block,block-1);
	int ans2 = lca_in_block(br,0,r%block);
	int ans = min_h (ans1, ans2);
	if (bl < br  - 1) {
		int pw2 = log2[br-bl-1];
		int ans3 = bt[bl+1][pw2];
		int ans4 = bt[br-(1<<pw2)][pw2];
		ans = min_h (ans, min_h (ans3, ans4));
	}
	return a[ans];
}

void FillGraph()
// чтение графа из файла
{
	int VertexCount = 0;
	std::cin >> VertexCount;

	std::vector<ChildVertex> Buff;
	g.assign(VertexCount,Buff);
	int Parent=0,Child=0,Length=0,LastVertex=0;

	for(int i=0;i<VertexCount-1;i++)
	{
		std::cin >> Parent;
		std::cin >> Child;
		std::cin >> Length;

		//if(g.size() < (unsigned int)Child) // по условию номера вершин неотрицательные
		//	g.push_back(Buff);

		Parent--;
		Child--;
		
		if(Length == 0)
		{
			if(Child < Parent)
				std::swap(Child,Parent);
			EqualVertex[Child]=Parent;
			
			if(g[Child].size())
			{
				for(std::vector<ChildVertex>::iterator it = g[Child].begin();it!=g[Child].end();it++) // замена упоминаний о сыне на родителя
					for(std::vector<ChildVertex>::iterator It = g[(*it).Number].begin();It!=g[(*it).Number].end();It++)
						if((*It).Number == Child)
							(*It).Number = Parent;
				

				std::size_t sz = g[Child].size();
				ChildVertex cv(0,0);
				for(std::size_t i=0;i<sz;i++)
					g[Parent].push_back(cv);
				std::copy(g[Child].begin(),g[Child].end(),g[Parent].begin());
				g[Child].clear();
			}
		}
		else
		{
			while(EqualVertex.find(Parent)!=EqualVertex.end())
				Parent=EqualVertex[Parent];
			while(EqualVertex.find(Child)!=EqualVertex.end())
				Child=EqualVertex[Child];

			if(g.size()<=Parent)
				g.size();
			g[Parent].push_back(ChildVertex(Child,Length));
			std::swap(Child,Parent);
			g[Parent].push_back(ChildVertex(Child,Length));
		}
	}

}

int main()
{
	FillGraph();
	root=0;
	n=0;
	memset(h,-1,MAXN);
	dfs(root,1);
	build_lca();
	int count = 0;
	std::cin >> count;
	int v1=0,v2=0;
	for(int i=0;i<count;i++)
	{
		std::cin >> v1;
		std::cin >> v2;
		v1--;
		v2--;
		while(EqualVertex.find(v1)!=EqualVertex.end())
			v1=EqualVertex[v1];
		while(EqualVertex.find(v2)!=EqualVertex.end())
			v2=EqualVertex[v2];
		int v = lca (v1, v2); // общий предок
		int H = h[v2]-h[v] + h[v1] - h[v] ; // сумма расстояний от вершин до общего предка
		std::cout << H << std::endl;

	}
}