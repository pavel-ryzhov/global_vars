#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

class PathFinder {

vector<int> distance_to_root_;
vector<pair<int, int> > vertices_;
vector<int> order_;
vector<int> first_;
vector<int> heights_;
vector<bool> vertices_used_;
vector<pair<int, int> > logarithm_;  
vector<vector<pair<int, int> > > sparse_table_;

void fill_order(int root, const vector<vector<pair<int,int> > > &tree) {
  dfs(root, 1, tree, 0);
}

void dfs(int v, int height, const vector<vector<pair<int, int> > > &tree, int distance_to_root) {
  distance_to_root_[v] = distance_to_root;;
  heights_[v] = height;
  order_.push_back(v);
  first_[v] = order_.size() - 1;
  vertices_used_[v] = true;
  for (int i = 0; i < tree[v].size(); ++i) {
    if (! vertices_used_[(tree[v][i]).first]) {
      dfs(tree[v][i].first, height + 1, tree, distance_to_root_[v] + tree[v][i].second);
      order_.push_back(v);
    }
  }
}

void precount_log(int n) {
  int sz = 0;
  int ri = 2;
  for (int i = 0; i < n - 1; ++i) {
    if (i + 1 == ri) {
      ++sz; 
      ri *= 2;
    }        
    logarithm_.push_back(make_pair(sz, ri / 2));
  }
}

void create_sparse_table(const vector<int> &v) {
  if (v.size() < 2) return;
  sparse_table_.resize(v.size());
  for (int i = 0; i < v.size(); ++i) {
    sparse_table_[i].push_back(make_pair(heights_[v[i]], v[i]));
  }
  int deg = 1;
  for (int j = 1; j < logarithm_[v.size() - 2].first + 1; ++j) {
    deg *= 2;
    for (int i = 0; i < v.size(); ++i) {
      if (i + deg <= v.size()) {
       
        if (sparse_table_[i][j - 1].first < sparse_table_[i + deg / 2][j - 1].first) {
          sparse_table_[i].push_back(make_pair(sparse_table_[i][j - 1].first, sparse_table_[i][j - 1].second)); 
        } else {
          sparse_table_[i].push_back(
          make_pair(sparse_table_[i + deg / 2][j - 1].first, sparse_table_[i + deg / 2][j - 1].second)); 
        }
      }
    }
  }
}

int find_lca(int ind1, int ind2) {
  if (ind1 > ind2) {
    swap(ind1, ind2);
  }
  int sz = logarithm_[ind2 - ind1].first;
  int deg2 = logarithm_[ind2 - ind1].second;
  int v_lca;
  if (sparse_table_[ind1][sz].first < sparse_table_[ind2 - deg2 + 1][sz].first) {
    v_lca = sparse_table_[ind1][sz].second;
  } else {
    v_lca = sparse_table_[ind2 - deg2 + 1][sz].second;
  }
  return v_lca;
}

int find_path_cost(int first, int second) {
  if (first == second) return 0;
  int v_lca = find_lca(first_[first], first_[second]);
  int cost = distance_to_root_[first] - 2 * distance_to_root_[v_lca] + distance_to_root_[second];
  return cost;
}

public:
  PathFinder() {
    //freopen("input.txt", "r", stdin);
    int node_count;
    cin >> node_count;
    vector<vector<pair<int, int> > > tree;
    distance_to_root_.resize(node_count);
    tree.resize(node_count);
    int root = 0;
    map<int, int> ref_map;
    int counter = 0;
    map<int, int>::iterator map_it; 
    for (int i = 0; i < node_count - 1; ++i) {
      int from, to, weight;
      cin >> from >> to >> weight;
      map_it = ref_map.find(from);
      if (map_it == ref_map.end()) {
        ref_map.insert(make_pair(from, counter));
        // XXX
        // cout << from << "->" << counter << endl;
        from = counter;
        ++counter;
      } else {
        from = map_it->second;
      }
      map_it = ref_map.find(to);
      if (map_it == ref_map.end()) {
        ref_map.insert(make_pair(to, counter));
        // XXX
        // cout << to << "->" << counter << endl;
        to = counter;
        ++counter;
      } else {
        to = map_it->second;
      }
      tree[from].push_back(make_pair(to, weight));
      tree[to].push_back(make_pair(from, weight));
    }

    if (node_count == 1) {
        ref_map[1] = 0;
    }

    int pairs_count;
    cin >> pairs_count;
    for (int i = 0; i < pairs_count; ++i) {
      int first, second;
      cin >> first >> second;
      first = ref_map.find(first)->second;
      second = ref_map.find(second)->second;
      vertices_.push_back(make_pair(first, second));
    }
    vertices_used_.resize(node_count, false);
    first_.resize(node_count);
    heights_.resize(node_count);
    fill_order(root, tree);
    
    //XXX
    /*
    for (int i = 0; i < order_.size(); ++i) {
        cout << order_[i] << " ";
    }
    cout << endl;
    */

    precount_log(order_.size());
    create_sparse_table(order_);
}


vector<int> find_paths() {
  vector<int> costs;
  for (int i = 0; i < vertices_.size(); ++i) {
    int cost = find_path_cost(vertices_[i].first, vertices_[i].second);
    costs.push_back(cost);
  }
  return costs;
}
} pathFinder;

int main() {
  vector<int> costs = pathFinder.find_paths();
  for (int i = 0; i < costs.size(); ++i) {
    cout << costs[i] << "\n";  
  }
}

