#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void dfs (int, int, int);
vector < vector <pair<int, int> > > tree;
vector <bool> used;
vector<int> depth;
vector<int> depth_bin;
vector<int> parent;
int way = 0, way_bin = 0;




int main(int argc, char* argv[])
{



    /////////////////////////////////////////////////////////////////////////////
    //                                 ПЕРЕМЕННЫЕ
    /////////////////////////////////////////////////////////////////////////////

    //N - число вершин, M - число пар
    int N, M;

    //n, n1, n2 - для ввода данных
    int n, n1, n2;

    //Nodes - массив пар
    vector <pair <int, int>  > Nodes;

    /////////////////////////////////////////////////////////////////////////////
    //                              ФОРМИР-Е ДЕРЕВА
    /////////////////////////////////////////////////////////////////////////////

    cin >> N;

    //формир-е пустого дерева
    for (int i = 0; i < N; i++)
    {
        vector <pair<int, int> > v;
        tree.push_back(v);

        used.push_back(false);
        depth.push_back(0);
        depth_bin.push_back(0);
        parent.push_back(0);
    }

    //формирование дерева
    for (int i = 0; i < N - 1; i++)
    {
        cin >> n1;
        cin >> n2;
        cin >> n;
        pair<int, int> pair1(n1-1, n);
        pair<int, int> pair2(n2-1, n);
        tree[n2-1].push_back(pair1);
        tree[n1-1].push_back(pair2);
    }

    /////////////////////////////////////////////////////////////////////////////
    //                              ФОРМИР-Е ПАР ВЕРШИН
    /////////////////////////////////////////////////////////////////////////////

    cin >> M;

    for (int i = 0; i < M; i++)
    {
        cin >> n1;
        cin >> n2;
        pair <int, int> pair(n1-1, n2-1);
        Nodes.push_back(pair);
    }

    /////////////////////////////////////////////////////////////////////////////
    //                              DFS
    /////////////////////////////////////////////////////////////////////////////

    dfs(0, 0, 0);

    /*
    cout << endl << "depth:";
    for (int i = 0; i < N; i++)
    {
        cout << depth[i] << " ";
    }
    cout << endl << "depth_bin:";
    for (int i = 0; i < N; i++)
    {
        cout << depth_bin[i] << " ";
    }
    */
    /////////////////////////////////////////////////////////////////////////////
    //                              LCA + ВЫВОД РЕЗУЛЬТАТОВ
    /////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < M; i++)
    {
        int a = Nodes[i].first;
        int b = Nodes[i].second;

        int lca = a;
        int lcb = b;

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

        int way_ab = depth[lca] + depth[lcb] - 2*depth[a];

        cout << way_ab << endl ;

    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////
//                              КОНЕЦ
/////////////////////////////////////////////////////////////////////////////


void dfs (int v, int lastleng, int from)
{
    used[v] = true;
    parent[v] = from;
    depth[v] = way;
    depth_bin[v] = way_bin;

    for (int i = 0; i < tree[v].size(); i++)
    {
        int CurrentNode = tree[v][i].first;
        int CurrentLen = tree[v][i].second;
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
