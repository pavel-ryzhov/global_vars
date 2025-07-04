#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long int ULI32;

const ULI32 maxsize = 40000;
const ULI32 inf = 6553500;
vector < vector <pair<int, int> > > g;
vector< pair<int,int> > nodes;
vector <bool> used;
int depth[maxsize];
int parent[maxsize];
int depth_bin[maxsize];
int way = 0, way_bin = 0;

void dfs (int v, int lastleng, int from)
{
	used[v] = true;
	parent[v] = from;
	depth[v] = way;
	depth_bin[v] = way_bin;

	for (size_t i=0; i<g[v].size(); i++)
	{
		int CurrentNode = g[v][i].first;
		int CurrentLen = g[v][i].second;
		if (!used[CurrentNode])
		{
			way += CurrentLen;
			way_bin++;
			dfs (CurrentNode, CurrentLen, v);
		}
	}
	way_bin--;
	way -= lastleng;
}

void searching()
{
	for (unsigned int i=0; i<nodes.size(); i++)
	{
        int a = nodes[i].first;
        int b = nodes[i].second;

        while (depth_bin[a] != depth_bin[b])
        {
            if (depth_bin[a] > depth_bin[b])
                a = parent[a];
            else
                b = parent[b];
        }

        while (a != b)
        {
            a = parent[a];
            b = parent[b];
        }
        int lca = a;
        int way_ab = depth[nodes[i].first] + depth[nodes[i].second] - 2*depth[lca];
        cout << way_ab << endl;
    }
}

int main()
{
    int v1,v2,len;
    int num, ways;
    pair<int,int> *newWay;
    cin >> num;
    g.resize(num);
    used.resize(num, false);
	--num;
    for(int i = 0; i < num; i++)
    {
        cin >> v1 >> v2 >> len;
		--v1;
		--v2;
        newWay = new pair<int,int>;
        newWay[0].first = v2;
        newWay[0].second = len;
        g[v1].push_back(*newWay);
        newWay = new pair<int,int>;
        newWay[0].first = v1;
        newWay[0].second = len;
        g[v2].push_back(*newWay);
    }
	dfs(0,inf,0);
    cin >> ways;
    for(int i = 0; i < ways; i++)
    {
        cin >> v1 >> v2;
		--v1;
		--v2;
        newWay = new pair<int,int>;
        newWay[0].first = v1;
        newWay[0].second = v2;
        nodes.push_back(*newWay);
    }
    searching();
    return 0;
}
