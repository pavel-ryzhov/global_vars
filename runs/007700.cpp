#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

const int num_vert = 40010;

struct edge{
    int to;
    int weight;
};


list <edge> lst[num_vert];
vector <int> time_in;
vector <int> time_out;
int timer = 0;
int logn;
vector <bool> marked;
vector <int> dist_to_root;
vector <vector <int> > ances;

void dfs(int v, int w, int parent = 0)
{
    marked[v] = true;
    dist_to_root[v] = w;
    time_in[v] = ++ timer;
    list <edge>::const_iterator p = lst[v].begin();
    edge new_edge;
    ances[v][0] = parent;
    for (int i = 1; i <= logn; i ++)
        ances[v][i] = ances[ances[v][i - 1]][i - 1];
    for (; p != lst[v].end(); p ++)
    {
        new_edge = *p;
        if (!marked[new_edge.to])
            dfs(new_edge.to, w + new_edge.weight, v);
    }
    time_out[v] = ++ timer;
}

bool is_ancestor(int anc, int son)
{
    return time_in[anc] <= time_in[son] && time_out[anc] >= time_out[son];
}

int lca(int v1, int v2)
{
   if (is_ancestor(v1, v2)) return v1;
   if (is_ancestor(v2, v1)) return v2;

   for (int i = logn; i >= 0; i --)
       if (!is_ancestor(ances[v1][i], v2))
           v1 = ances[v1][i];

   return ances[v1][0];
}

int main(int argc, char *argv[])
{
    int n;
    cin >> n;

    int v1, v2, w;
    edge e1, e2;
    for (int i = 0; i < n - 1; i ++)
    {
          cin >> v1 >> v2 >> w;
          v1 --; v2 --;
          e1.to = v2; e1.weight = w;
          e2.to = v1; e2.weight = w;
          lst[v1].push_front(e1);
          lst[v2].push_front(e2);
    }

    time_in.resize(n);
    time_out.resize(n);
    marked.resize(n);
    fill(marked.begin(), marked.end(), false);
    dist_to_root.resize(n);
    ances.resize(n);
    logn = 1;
    while ((1 << logn) <= n) logn ++;
    for (int i = 0; i < n; i ++)  ances[i].resize(logn + 1);

    if (n != 0) dfs(0, 0);

    int m;
    cin >> m;

    int v3 = 0;
    vector <int> dists(m);
    for (int i = 0; i < m; i ++)
    {
        cin >> v1 >> v2;
        v1 --; v2 --;
        v3 = lca(v1, v2);
        dists[i] = dist_to_root[v1] - 2*dist_to_root[v3] + dist_to_root[v2];
    }
    for (int i = 0; i < m; i ++)
        cout << dists[i] << endl;
 
}
