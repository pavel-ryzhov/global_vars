#include <vector>
#include <iostream>
#include <utility>

using namespace std;

class Tree
{
public:
    Tree(unsigned numVertex):
      tree(numVertex),
      tin(numVertex),
      tout(numVertex),
      parents(numVertex),
      length(numVertex),
      used(numVertex, false),
      L(1)
    {
        while ((L << 1) < numVertex) ++L;
        for (unsigned i = 0; i < numVertex; ++i)
        {
            parents[i].resize(L + 1);
        }
    }

    void addEdge(unsigned vert1, unsigned vert2, unsigned edgeLength)
    {
        tree[vert1].push_back(make_pair(vert2, edgeLength));
        tree[vert2].push_back(make_pair(vert1, edgeLength));
    }

    // this function must be called after all edges were added
    // and before getting of shortest paths
    void preprocessing()
    {
        timer = 0;
        dfs(0, 0, 0);
    }

    unsigned getShortestPath(unsigned v1, unsigned v2)
    {
        if (is_parent_of(v1, v2)) return length[v2] - length[v1];
        if (is_parent_of(v2, v1)) return length[v1] - length[v2];
        unsigned m = v1;
        for (int i = L; i >= 0; --i)
        {
            if (! is_parent_of(parents[m][i], v2))
                m = parents[m][i];
        }
        return length[v1] + length[v2] - 2*length[parents[m][0]];
    }
private:
    void dfs(unsigned v, unsigned p, unsigned pathLength)
    {
        tin[v] = ++timer;
        length[v] = pathLength;
        parents[v][0] = p;
        used[v] = true;
        for (unsigned i = 1; i <= L; ++i)
        {
            parents[v][i] = parents[parents[v][i - 1]][i - 1];
        }
        for (unsigned i = 0; i < tree[v].size(); ++i)
            if (! used[tree[v][i].first])
                dfs(tree[v][i].first, v, pathLength + tree[v][i].second);
        tout[v] = ++timer;
    }
    bool is_parent_of(unsigned p, unsigned ch)
    {
        return tin[p] <= tin[ch] && tout[p] >= tout[ch];
    }
private:
    unsigned timer, L;

    // tree[i] - vector of pairs : number of vertex, length of edge between i and vertex
    // it contains all vertex (not only child), connected with vertex i
    vector< vector< pair<unsigned, unsigned> > > tree;

    vector<unsigned> tin, tout;                          // times of dfs go in vertex and out from it
    vector< vector<unsigned> > parents;                  // parents[v][i]  --  2^i parent of vertex i
    vector<unsigned> length;                             // length of path from root to vertex i
    vector<bool> used;
};

int main()
{
    unsigned numVertex;
    cin >> numVertex;
    Tree tree(numVertex);
    unsigned v1, v2, length;
    for (unsigned i = 0; i < numVertex - 1; ++i)
    {
        cin >> v1 >> v2 >> length;
        tree.addEdge(v1 - 1, v2 - 1, length);
    }
    tree.preprocessing();

    cin >> numVertex;
    for (unsigned i = 0; i < numVertex; ++i)
    {
        cin >> v1 >> v2;
        cout << tree.getShortestPath(v1 - 1, v2 - 1) << endl;
    }
}
