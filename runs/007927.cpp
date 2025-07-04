#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <memory.h>

using namespace std;

const int MAXN = 100*1000;
const int MAXLIST = MAXN * 2;
const int LOG_MAXLIST = 18;
const int SQRT_MAXLIST = 447;
const int MAXBLOCKS = MAXLIST / ((LOG_MAXLIST+1)/2) + 1;
typedef map <set<int>, int> edges_type;

int n, root;
//vector<int> g[MAXN];
vector< vector<int> > g(MAXN,vector<int>(0));
vector<int> h(MAXN, -1);
vector<int> abs_h(MAXN,0);
//int h[MAXN]; // vertex height
vector<int> a; // dfs list
int a_pos[MAXN]; // positions in dfs list
int block; // block size = 0.5 log A.size()
int bt[MAXBLOCKS][LOG_MAXLIST+1]; // sparse table on blocks (relative minimum positions in blocks)
int bhash[MAXBLOCKS]; // block hashes
int brmq[SQRT_MAXLIST][LOG_MAXLIST/2][LOG_MAXLIST/2]; // rmq inside each block, indexed by block hash
int log2[2*MAXN]; // precalced logarithms (floored values)

// walk graph
void dfs (int v, int curh, int h2, edges_type e) {
	h[v] = curh;
	abs_h[v] = h2;
	a_pos[v] = (int)a.size();
	a.push_back (v);
	for (size_t i=0; i<g[v].size(); ++i)
		if (h[g[v].at(i)] == -1) {
			set<int> buff;
			buff.insert(g[v].at(i));
			buff.insert(v);
			dfs (g[v].at(i), curh+1, h2+e.find(buff)->second, e);
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

void g_input(edges_type &e, vector<int> &t)
{
	//чтение графа
/*	int init[42] = {9,
					1, 2, 0,
					2, 9, 5,
					3, 9, 0,
					4, 9, 8,
					5, 9, 7,
					6, 8, 2,
					7, 5, 0,
					8, 7, 1,
					8,
					6, 5,
					2, 3,
					3, 3,
					4, 1,
					3, 7,
					3, 6,
					5, 7,
					8, 2};
	vector<int> input(init, init+42);*/
	vector<int> input;
	vector<int>::iterator it_input;
	copy(istream_iterator<int>(cin),istream_iterator<int>(), back_inserter(input));
	int i = 0;
	int n =  *input.begin();
/*	for(;i<n;i++)
		g[i].push_back(vector<int>());*/
	
	for (i=1;i<=*(input.begin());i++) { //здесь точки заполняются связями
		g[i-1].push_back(i-1);

		set<int> buff;
		buff.insert(input.at((i-1)*3+1)-1);
		buff.insert(input.at((i-1)*3+2)-1);
		e.insert(pair<set<int>, int>(buff,
									 input.at((i-1)*3+3)));

		for (it_input = input.begin()+1; it_input < input.begin()+(n-1)*3; it_input = it_input + 3) {
			if (*it_input==i)
				g[i-1].push_back(*(it_input+1)-1);
			else
				if(*(it_input+1)==i)
					g[i-1].push_back(*it_input-1);
		}
	} //заполнились

	t.resize(*(input.begin()+3*(n-1)+1)*2);
	copy(input.begin()+3*(n-1)+2, input.end(), t.begin());
}

int main()
{
	edges_type e;
	vector<int> t;

	
	g_input(e, t);
	dfs(0,0,0,e);
	build_lca();

	
	for(vector<int>::iterator i = t.begin(); i-t.begin() < t.size(); i=i+2) {
		cout << abs_h[*i-1] + abs_h[*(i+1)-1] - 2*abs_h[lca(*i-1, *(i+1)-1)] << endl;
	}
	return 0;
}