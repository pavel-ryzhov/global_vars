#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

typedef vector < vector<int> > vector_2;

class LCA
{
	vector_2 vertexes;
	vector<int> height, weight, vertex_order, first, tree;
	vector<int> dfs_used;
	public:
		LCA(int n)
		{
			vertexes.resize(n);
			weight.resize(n);
			height.resize(n);
		}
		void push_vertex(int i, int vertex);
		int get_weight(int i);
		void dfs(int v, const vector_2 &aWeight, int, int);
		void build_tree (int node, int l, int r);
		void prepare (int root, const vector_2 &aWeight);
		int find_min (int i, int sl, int sr, int l, int r);
		int get_lca (int v1, int v2);
};

void 
LCA::push_vertex(int i, int vertex)
{
	vertexes[i].push_back(vertex);
}

int 
LCA::get_weight(int i)
{
	return weight[i];
}

void 
LCA::dfs(int v, const vector_2 &aWeight, int h = 1, int w = 0)
{
	dfs_used[v] = true;
	height[v] = h;
	weight[v] = w;
	vertex_order.push_back (v);
	vector<int>::const_iterator cur_weight = aWeight[v].begin();
	vector<int>::const_iterator end = vertexes[v].end();
	for (vector<int>::const_iterator i = vertexes[v].begin(); i != end; ++i, ++cur_weight)
		if (!dfs_used[*i])
		{
			dfs(*i, aWeight, h+1, w + *cur_weight);
			vertex_order.push_back (v);
		}
}

void 
LCA::build_tree (int node, int left, int right)
{
	if (left == right)
		tree[node] = vertex_order[left];
	else
	{
		int m = (left + right) >> 1;
		build_tree (2*node, left, m);
		build_tree (2*node+1, m+1, right);
		if (height[tree[2*node]] < height[tree[2*node+1]])
			tree[node] = tree[2*node];
		else
			tree[node] = tree[2*node+1];
	}
}

void 
LCA::prepare (int root, const vector_2 &aWeight)
{
	int n = static_cast<int> (vertexes.size());
	
	vertex_order.reserve(n*2);
	dfs_used.assign(n, 0);

	dfs(root, aWeight);

	int m = static_cast<int> (vertex_order.size());
	tree.assign (vertex_order.size() * 4 + 1, -1);
	build_tree (1, 0, m-1);
	first.assign (n, -1);
	for (int i = 0; i < m; ++i)
	{
		int v = vertex_order[i];
		if (first[v] == -1)
			first[v] = i;
	}
}

int 
LCA::find_min (int node, int Left, int Right, int left, int right)
{
	if (Left == left && Right == right)
		return tree[node];
	int middle = (Left + Right) >> 1;
	if (right <= middle)
		return find_min (node+node, Left, middle, left, right);
	if (left > middle)
		return find_min (2*node+1, middle+1, Right, left, right);
	int min1 = find_min (2*node, Left, middle, left, middle);
	int min2 = find_min (2*node+1, middle+1, Right, middle+1, right);
	return height[min1] < height[min2] ? min1 : min2;
}

int 
LCA::get_lca (int v1, int v2)
{
	int left = first[v1],
		right = first[v2];
	if (left > right)  swap (left, right);
	return find_min (1, 0, static_cast<int> (vertex_order.size())-1, left, right);
}


int main() {
	int n, m;
	cin >> n;
	LCA *graph = new LCA(n);
	vector_2 weight(n);
	for(int i = 0; i < n - 1; ++i) {
		int v1;
		int v2;
		int w;
		cin >> v1 >> v2 >> w;
		graph -> push_vertex(v1 - 1, v2 - 1);
		graph -> push_vertex(v2 - 1, v1 - 1);
		weight[v2-1].push_back(w);
		weight[v1-1].push_back(w);
	}
	graph -> prepare(0, weight);
	cin >> m;
	for(int i = 0; i < m; ++i) {
		int v1;
		int v2;
		cin >> v1 >> v2;
		cout << graph -> get_weight(v1 - 1) +
        		graph -> get_weight(v2 - 1) -
				2 * graph -> get_weight( graph -> get_lca(v1 - 1, v2 - 1)) << endl;
	}
	
	delete graph;
	
	return 0;
}
