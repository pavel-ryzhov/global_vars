// task2.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>
//#include <fstream>
#include <cstdlib>
#include <string>
#include <string.h>

using namespace std;

//////Bender LCA

const int MAXN = 40000;
const int MAXLIST = MAXN * 2;
const int LOG_MAXLIST = 12;
const int SQRT_MAXLIST = 283;
const int MAXBLOCKS = MAXLIST / ((LOG_MAXLIST+1)/2) + 1; //MAXLIST / ((LOG_MAXLIST+1)/2) + 1;

int n, root;
vector< pair<int, int> > g[MAXN];
int h[MAXN]; // vertex height
vector<int> a; // dfs list
int a_pos[MAXN]; // positions in dfs list
int block; // block size = 0.5 log A.size()
int bt[MAXBLOCKS][LOG_MAXLIST+1]; // sparse table on blocks (relative minimum positions in blocks)
int bhash[MAXBLOCKS]; // block hashes
int brmq[SQRT_MAXLIST][LOG_MAXLIST/2][LOG_MAXLIST/2]; // rmq inside each block, indexed by block hash
int log2[2*MAXN]; // precalced logarithms (floored values)
int depth[MAXN];
int cur_way = 0;

// walk graph
void dfs (int v, int curh, int lgth) {
	h[v] = curh;
	a_pos[v] = (int)a.size();
	a.push_back (v);
    depth[v] = cur_way;
	for (size_t i=0; i<g[v].size(); ++i)
        if (h[g[v][i].first] == -1) {
            cur_way += g[v][i].second;
            dfs (g[v][i].first, curh+1, g[v][i].second);
			a.push_back (v);
		}
    cur_way -= lgth;
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
///


int main(int argc, char* argv[])
{
    //ifstream file("1.txt");
    //ofstream file2("2.txt");
    char tmpbuf[255];
    string buf;
    int pointsNum;
    //file >> pointsNum;
    cin >> pointsNum;
    //getline(file, buf);
    cin.getline(tmpbuf, 255);
    buf.assign(tmpbuf);
    int tmp[3];
    string tmpstr[3];
    for(int i = 0; i < pointsNum; i++)
        h[i] = -1;
    for(int i = 0; i < pointsNum; i++)
        for(int j = 0; j < 12; j++)
            bt[i][j] = -1;
    for(int i = 0; i < 283; i++)
        for(int j = 0; j < LOG_MAXLIST/2; j++)
            for(int l = 0; l < LOG_MAXLIST/2; l++)
                brmq[i][j][l] = -1;
    while(true)
    {
        int numcount = 0;
        //getline(file, buf);
        cin.getline(tmpbuf, 255);
        buf.assign(tmpbuf);
        for(int i = 0; i < buf.length(); i++)
        {
            if(buf[i] != ' ' && buf[i] != '\n')
            {
                tmpstr[numcount] += buf[i];
                if(i == (buf.length() - 1))
                {
                    tmp[numcount] = atoi(tmpstr[numcount].data());
                    tmpstr[numcount] = "";
                    numcount++;
                }
            }
            else if((tmpstr[numcount].length() > 0) && numcount < 3)
            {
                tmp[numcount] = atoi(tmpstr[numcount].data());
                tmpstr[numcount] = "";
                numcount++;
            }
        }
        if(numcount <= 1)
            break;
        pair<int, int> d;
        d.first = tmp[1] - 1;
        d.second = tmp[2];
        g[tmp[0] - 1].push_back(d);
        d.first = tmp[0] - 1;
        g[tmp[1] - 1].push_back(d);       
    }
    dfs(0, 0, 0);
    build_lca();
    pointsNum = tmp[0];
    int la, result;
    for(int i = 0; i < pointsNum; i++)
    {
        //file >> tmp[0];
        //file >> tmp[1];
        cin >> tmp[0];
        cin >> tmp[1];
        la = lca(tmp[0] - 1, tmp[1] - 1);
        result = depth[tmp[0] - 1] + depth[tmp[1] - 1] - 2 * depth[la];
        cout << result <<endl;
    }
    //file2.close();
    //file.close();
    //int k;
    //cin >> k;
	return 0;
}

