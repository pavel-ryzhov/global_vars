#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

template<class T, class K, class Key, class Action> 
void build_range_tree_iter(const vector<T>& arr, vector<K>& tree,
                           Key key, Action action,
                           size_t l, size_t r, size_t i)
{
  if (r - l == 1)
    tree[i] = key(arr[l]);
  else {
    size_t m = (l + r) / 2;
    build_range_tree_iter(arr, tree, key, action, l, m, i*2+1);
    build_range_tree_iter(arr, tree, key, action, m, r, i*2+2);
    tree[i] = action(tree[i*2+1], tree[i*2+2]);
  }
}

template<class T, class K, class Key, class Action> 
void build_range_tree(const vector<T>& arr, vector<K>& tree, Key key, Action act)
{
  build_range_tree_iter(arr, tree, key, act, 0, arr.size(), 0);
}

template<class K, class Action>
K range_tree_search_iter(const vector<K>& tree, Action action,
                           size_t l, size_t r, size_t cl, size_t cr, size_t i)
{
  if (l == cl && r == cr)
    return tree[i];
  size_t cm = (cl + cr) / 2;
  if (r <= cm)
    return range_tree_search_iter(tree, action, l, r, cl, cm, i*2 + 1);
  if (l >= cm)
    return range_tree_search_iter(tree, action, l, r, cm, cr, i*2 + 2);
  return action(range_tree_search_iter(tree, action, l, cm, cl, cm, i*2 + 1),
                range_tree_search_iter(tree, action, cm, r, cm, cr, i*2 + 2));
}

template<class K, class Action>
K range_tree_search(const vector<K>& tree, Action action, size_t l, size_t r)
{
  return range_tree_search_iter(tree, action, l, r, 0, tree.size() / 4, 0);
}

/****************************************************************/
/****************************************************************/

typedef vector< vector<pair <int, int> > > tree;

template<class T>
class Weight {
  const vector<T>& w;
public:
  Weight(const vector<T>& w): w(w) {}
  T operator() (size_t x) { return w[x]; }
};

template<class T>
class Get_min {
public:
  const T& operator()(const T& x, const T& y) { if (x < y) return x; return y;}
};


void dfs_iter(const tree& t, vector<int>& order, vector<int>& w,
              vector<int>& first, vector<bool>& visited, int v, int cw)
{
  visited[v] = true;
  w[v] = cw;
  order.push_back(v);
  if (first[v] == -1)
    first[v] = order.size() - 1;
  for (vector<pair<int, int> >::const_iterator i = t[v].begin();
       i != t[v].end(); ++i) {
    if (!visited[i->first]) {
      dfs_iter(t, order, w, first, visited, i->first, cw + i->second);
      order.push_back(v);
    }
  }
}

void dfs(const tree& t, vector<int>& order, vector<int>& w, vector<int>& first)
{
  vector<bool> visited;
  visited.resize(t.size());
  dfs_iter(t, order, w, first, visited, 0, 0);
}

void read_tree(tree& t)
{
  size_t n;
  cin >> n;
  t.resize(n);
  int from, to, weight;
  for (size_t i = 0; i != n - 1; ++i) {
    cin >> from >> to >> weight;
    --from; --to;
    t[from].push_back(make_pair(to, weight));
    t[to].push_back(make_pair(from, weight));
  }
}

ostream& operator<<(ostream& os, const vector<int>& v)
{
  for (vector<int>::const_iterator i = v.begin(); i != v.end(); ++i)
    os << *i << " ";
  return os;
}

int main()
{
  tree t;
  read_tree(t);
  size_t n = t.size();
  vector<int> order;
  vector<int> weights(n);
  vector<int> first(n, -1);
  dfs(t, order, weights, first); // заполнить массивы при обходе в глубину
  vector<int> range_tree(order.size()*4, -1); // дерево отрезков
  build_range_tree(order, range_tree, Weight<int>(weights), Get_min<int>());
  size_t m, from, to;
  cin >> m;
  for (size_t i = 0; i != m; ++i) {
    cin >> from >> to;
    int left_pos = first[--from];
    int right_pos = first[--to];
    if (left_pos > right_pos) swap(left_pos, right_pos);
    int h = range_tree_search(range_tree, Get_min<int>(), 
                              left_pos, right_pos + 1);
    cout << weights[from] + weights[to] - 2*h << endl;
  }
}
