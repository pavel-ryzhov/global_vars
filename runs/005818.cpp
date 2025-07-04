#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

// edge struct/allocator
struct edge
{
  edge* next;
  int b;
  int c;
};
int _acount = 0;
edge _apool[65536 * 2];
edge* ealloc ()
{
  return &_apool[_acount++];
}

edge* ve[65536]; // first edge list
int depth[65536]; // node depth
int cost[65536]; // distance from root
int tree[65536 * 4]; // interval tree
int tpos[65536]; // node positions in interval tree
int n;
const int pstart = 65536 * 2;
int pn = 0;

// list nodes in euler's pass
void dfs (int v, int d, int c, int p = -1)
{
  depth[v] = d;
  cost[v] = c;
  tpos[v] = pn;
  tree[pstart + pn++] = v;
  for (edge* e = ve[v]; e; e = e->next)
  {
    if (e->b != p)
    {
      dfs (e->b, d + 1, c + e->c, v);
      tree[pstart + pn++] = v;
    }
  }
}

int main()
{
  //freopen ("input.txt", "rt", stdin);
  //freopen ("output.txt", "wt", stdout);

  memset (_apool, 0, sizeof _apool);
  memset (ve, 0, sizeof ve);
  memset (tree, 0, sizeof tree);

  // read graph (tree)
  scanf ("%d", &n);
  for (int i = 1; i < n; i++)
  {
    int a, b, c;
    scanf ("%d %d %d", &a, &b, &c);
    a--, b--;
    edge* e1 = ealloc ();
    e1->b = b;
    e1->c = c;
    e1->next = ve[a];
    ve[a] = e1;
    edge* e2 = ealloc ();
    e2->b = a;
    e2->c = c;
    e2->next = ve[b];
    ve[b] = e2;
  }
  // do euler's pass
  dfs (0, 0, 0);
  // build interval tree
  for (int i = pstart - 1; i > 0; i--)
    tree[i] = (depth[tree[i + i]] < depth[tree[i + i + 1]] ? tree[i + i] : tree[i + i + 1]);

  // process queries
  int m;
  scanf ("%d", &m);
  for (int i = 0; i < m; i++)
  {
    int a, b;
    scanf ("%d %d", &a, &b);
    a--, b--;
    // find minimum using interval tree
    int l = (tpos[a] < tpos[b] ? tpos[a] : tpos[b]) + pstart;
    int r = (tpos[a] > tpos[b] ? tpos[a] : tpos[b]) + pstart;
    int res = (depth[a] < depth[b] ? a : b);
    while (l < r - 1)
    {
      if (!(l & 1) && depth[tree[l + 1]] < depth[res])
        res = tree[l + 1];
      if ((r & 1) && depth[tree[r - 1]] < depth[res])
        res = tree[r - 1];
      l >>= 1;
      r >>= 1;
    }
    printf ("%d\n", cost[a] + cost[b] - cost[res] - cost[res]);
  }

  return 0;
}
