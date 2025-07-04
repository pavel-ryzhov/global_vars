#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOCATE_SIZE 3

static inline int compare (int *a, int *b)
{
  if (a[0] > b[0])
    return 1;
  else if (a[0] < b[0])
    return -1;
  else
    {
      if (a[1] > b[1])
        return 1;
      else if (a[1] < b[1])
        return -1;
    }
  return 0;
}

void replace (int *&a, int *&b)
{
  int *temp = a;
  a = b;
  b = temp;
}

int find_position_and_reverse (int **array, unsigned int n, int *x)
{
  int **a, **b;
  unsigned int i, j;

  a = array;          // borders
  b = array + n - 1;

  i = 0;
  j = n - 1;

  while (i <= j)
    {
      while ((i < n - 1) && (compare (*a, x) < 0))
        {
          a++;
          i++;
        }
      while ((j > 0) && (compare (*b, x) > 0))
        {
          b--;
          j--;
        }
      if (i <= j)
        {
          replace (*a, *b);
          a++;
          i++;
          b--;
          j--;
        }
    }
  return i;
}

void quick_sort (int **a, unsigned int n)
{
  int i, p, k;

  k = n;
  while (k > 2)
    {
      p = (unsigned int) k >> 1;
      i = find_position_and_reverse (a, k, a[p]);

      if (i == k)
        {
          replace (a[p], a[k - 1]);
          i--;
        }

      if (i > k - i)
        {
          quick_sort (a + i, k - i);
          k = i;
        }
      else
        {
          quick_sort (a, i);
          k = k - i;
          a = a + i;
        }
    }

    if (k == 2)
      {
        if (compare (a[0], a[1]) > 0)
          replace (a[0], a[1]);
      }
}

void reallocate (int *&a, unsigned int size, unsigned int new_size)
{
  int *temp = new int [new_size];
  memcpy (temp, a, size * sizeof (int));
  delete [] a;
  a = temp;
}

unsigned int read_graph (int **&g, int *&sizes, int **&weights)
{
  unsigned int n; // vertex count
  unsigned int i;
  int v1, v2;     // vertexes

  scanf ("%u", &n);

  g = new int* [n];
  for (i = 0; i < n; i++)
    g[i] = new int [ALLOCATE_SIZE];

  sizes = new int [n];
  memset (sizes, 0, n * sizeof (int));

  weights = new int * [n-1];
  for (i = 0; i < n - 1; i++)
    weights[i] = new int [3];

  for (i = 0; i < n - 1; i++) // number of couples
    {
      scanf ("%i %i %i\n", &v1, &v2, &weights[i][2]);
      v1--;
      v2--;
      if (v1 > v2)
        {
          int temp = v1;
          v1 = v2;
          v2 = temp;
        }

      weights[i][0] = v1;
      weights[i][1] = v2;

      if (!(sizes[v1] % ALLOCATE_SIZE) && (sizes[v1]))
        reallocate (g[v1], sizes[v1], sizes[v1] + ALLOCATE_SIZE);
      if (!(sizes[v2] % ALLOCATE_SIZE) && (sizes[v2]))
        reallocate (g[v2], sizes[v2], sizes[v2] + ALLOCATE_SIZE);

      g[v1][sizes[v1]++] = v2;
      g[v2][sizes[v2]++] = v1;
    }
  quick_sort (weights, n - 1);

  return n;
}

unsigned int prepare_p (int **&children, unsigned int n)
{
  unsigned int l, i;
  for (l = 1; ((1 << l) <= n); l++) ;

  children = new int* [n];
  for (i = 0; i < n; i++)
    children[i] = new int [l + 1];

  return l;
}

void dfs (int **children, int **g, int *sizes, bool *used, int *time_in, int *time_out, int &timer, unsigned int l, int v = 0, int p = 0)
{
  used[v] = true;
  time_in[v] = timer++;
  children[v][0] = p;

  for (unsigned int i = 1; i <= l; i++)
    children[v][i] = children[children[v][i-1]][i-1];

  for (int i = 0; i < sizes[v]; i++)
    {
      int to = g[v][i];
      if (!used[to])
        dfs (children, g, sizes, used, time_in, time_out, timer, l, to, v);
    }
  time_out[v] = timer++;
}

void depth_first_search (int **children, int **g, int *sizes, int *&time_in, int *&time_out, unsigned int n, unsigned int l)
{
  bool *used  = new bool [n];
  int timer = 0;

  time_in  = new int [n];
  time_out = new int [n];

  for (unsigned int i = 0; i < n; i++)
    used[i] = false;

  dfs (children, g, sizes, used, time_in, time_out, timer, l);
  delete [] used;
}

bool upper (int *time_in, int *time_out, int a, int b)
{
  return time_in[a] <= time_in[b] && time_out[a] >= time_out[b];
}

int lca (int **children, int *time_in, int *time_out, unsigned int l, int a, int b)
{
  if (upper (time_in, time_out, a, b))
    return a;
  if (upper (time_in, time_out, b, a))
    return b;
  for (int i = l; i >= 0; i--)
    if (!upper (time_in, time_out, children[a][i], b))
      a = children[a][i];
  return children[a][0];
}

int find_weight (int **weights, int v1, int v2, unsigned int n)
{
  if (v1 == v2)
    return 0;
  else if (v1 > v2)
    {
      int temp = v1;
      v1 = v2;
      v2 = temp;
    }

  unsigned int a = 0,
               b = n - 2,
               m = 0;
  int cmp;

  while (1)
    {
      m = (b + a) >> 1;

      if ((weights[a][0] == v1) && (weights[a][1] == v2))
        return weights[a][2];
      if ((weights[b][0] == v1) && (weights[b][1] == v2))
        return weights[b][2];

      if (weights[m][0] > v1)
        cmp = 1;
      else if (weights[m][0] < v1)
        cmp = -1;
      else
        {
          if (weights[m][1] > v2)
            cmp = 1;
          else if (weights[m][1] < v2)
            cmp = -1;
          else
            cmp = 0;
        }

      if (cmp < 0)
        a = m;
      else if (cmp > 0)
        b = m + 1;
      else
        return weights[m][2];
    }
}

int path (int **weights, int **children, int p, int c, unsigned int n)
{
  int res = 0;
  int curr_vertex = c;
  do
    {
      res += find_weight (weights, curr_vertex, children[curr_vertex][0], n);
      curr_vertex = children[curr_vertex][0];
    }
  while (curr_vertex != p);
  return res;
}

int distance (int **weights, int **children, int *time_in, int *time_out, unsigned int l, unsigned int n, int a, int b)
{
  if (a == b)
    return 0;

  int vertex = lca (children, time_in, time_out, l, a, b);

  if (vertex == a)
    return path (weights, children, a, b, n);
  else if (vertex == b)
    return path (weights, children, b, a, n);
  else
    return path (weights, children, vertex, a, n) + path (weights, children, vertex, b, n);
}

void graph_free (int **g, int *sizes, unsigned int n)
{
  unsigned int i;

  delete [] sizes;
  for (i = 0; i < n; i++)
    delete [] g[i];
  delete [] g;
}


void memory_free (int **weights, int **children, int *time_in, int *time_out, unsigned int n)
{
  unsigned int i;

  for (i = 0; i < n - 1; i++)
    delete [] weights[i];
  delete [] weights;
  for (i = 0; i < n; i++)
    delete [] children[i];
  delete [] children;
  delete [] time_in;
  delete [] time_out;
}

int main()
{
  unsigned int n, l, m;
  int a, b;
  int **g, *sizes, **children, **weights, *time_in, *time_out;

  n = read_graph (g, sizes, weights);
  l = prepare_p (children, n);

  depth_first_search (children, g, sizes, time_in, time_out, n, l);
  graph_free (g, sizes, n);

  scanf ("%i", &m);
  for (unsigned int i = 0; i < m; i++)
    {
      scanf ("%i %i", &a, &b);
      printf ("%i\n", distance (weights, children, time_in, time_out, l, n, a - 1, b - 1));
    }

  memory_free (weights, children, time_in, time_out, n);
  return 0;
}
