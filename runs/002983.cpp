#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

const int inf = 500000;

struct Edge 
{
	int v; 
	int weight;
	Edge(int to, int w) : v(to), weight(w) {};
};

vector< list<Edge> > edgeslist; 
/* for every vertex U in graph, list of edges incidented to U is stored                       *
 * Thus, for edge (U, V) we don't have to store original U - only V and edge weight is needed */
vector< pair<int, int> > for_rmq; // pairs of depth and vertex with such depth
vector<int> first; // first[i] is the first occurence of i-th vertex in for_rmq[].second
vector<int> dist; // dist[i] is the distance from root vertex to i-th one

class Rmq
{
	public:
		Rmq(const vector< pair<int, int> > array);
		pair<int, int> query(int left, int right);
	private:
		vector< pair<int, int> > rmq_tree_;
};

Rmq::Rmq(const vector< pair<int, int> > array) : rmq_tree_(2 * array.size()) 
{
	size_t size = array.size();

	for (size_t i = 0; i < size; i++)
		rmq_tree_[size + i] = array[i];
	for (size_t i = size - 1; i > 0; i--)
		rmq_tree_[i] = min(rmq_tree_[2 * i + 1], rmq_tree_[2 * i]);
}

pair<int, int> Rmq::query(int left, int right) // [left..right] 
{
	if (left > right) return pair<int, int> (0, 0); // this should never happen
	
	int size = rmq_tree_.size() / 2;
	left += size;
	right += size;

	pair<int, int> minimum(inf, 0);
	while(true)
	{
		if (left % 2 == 1) // means that "left" vertex is a right son of its parent
		{
			minimum = min(minimum, rmq_tree_[left]);
			left++;
		}
		if (right % 2 == 0) // similarly, means that "right" vertex is a left son of its parent
		{
			minimum = min(minimum, rmq_tree_[right]);
			right--;
		}
		
		if (left > right) break; // after next 2 lines left may become equal to right 

		left /= 2;
		right /= 2;
	}
//	minimum = min(minimum, rmq_tree_[left]); // right == left now

	return minimum;
}

void dfs(int parent, int current_v, int depth) 
{
	for_rmq.push_back(pair<int, int>(depth, current_v));
	first[current_v] = for_rmq.size() - 1;

	for (list<Edge>::iterator iter = edgeslist[current_v].begin(); iter != edgeslist[current_v].end(); ++iter)
		if (iter->v != parent)
		{
			dist[iter->v] = dist[current_v] + iter->weight;
			dfs(current_v, iter->v, depth + 1);
			for_rmq.push_back(pair<int, int>(depth, current_v));
		}
}

int vertex_num;
int inquiries_num;

int main()
{
	cin >> vertex_num;
	
	edgeslist.resize(vertex_num + 1); // vertex numbering starts from 1

	for (int i = 0; i < vertex_num - 1; i++)
	{
		int u, v, w;
		
		cin >> u >> v >> w;
		edgeslist[u].push_back(Edge(v,w));
		edgeslist[v].push_back(Edge(u,w));
	}
	
	first.resize(vertex_num + 1);
	dist.resize(vertex_num + 1);

	dfs(0, 1, 0);

	Rmq rmq(for_rmq);

	cin >> inquiries_num;
	for (int i = 0; i < inquiries_num; i++)
	{
		int f,s;
		
		cin >> f >> s;

		pair <int, int> lca;
		if (first[s] < first[f]) lca = rmq.query(first[s], first[f]);
		else lca = rmq.query(first[f], first[s]);

		cout << dist[s] + dist[f] - 2 * dist[lca.second] << endl;

	}
}
