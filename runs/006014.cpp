/*
Given: undirected connected weighted tree G = (V, E) w:E->Z (as distance)
To Do: find shortest path length for piven nodes pair.
Dijkstra's algorithm runs in O(N^2 logN) better
Floyd-Walshall runs in O(M + N^3)

Input:
-----
N		// number of nodes
v1 v2 d	// N-1 lines
M		// number of queries
v1 v2	// M lines of queries, where v1 is sourse and v2 is destination

Output:
-------
d		// M lines as answers to queries
*/

#include <iostream>
#include <vector>
#include <queue>

struct Edge {
	Edge* next;
	int connect;
	int weight;
	
	Edge (int cnt, int wgt) : connect (cnt), weight (wgt), next (0) {};
};

class Tree {
	private:
	int size;
	std::vector<Edge*> adj_list;
	std::vector< std::vector <int> > all_dist;
	
	public:
	Tree (int N) : size (N) {all_dist.resize (N+1); adj_list.resize (N+1); for (int i = 1; i <= size; ++i) all_dist[i].resize (size + 1);};
	~Tree ();
	void add_edge (int v1, int v2, int w);
	void build_dist ();
	int distance (int v1, int v2);
};

// ----------------------------------------------------------------------------

Tree::~Tree () {
	/*std::vector<Edge*>::iterator ptr = adj_list.begin () + 1;
	for (; ptr != adj_list.end (); ++ptr) {
		Edge* cur = *ptr;
		while (cur) {
			Edge* todelete = cur;
			cur = cur->next;
			todelete->next = 0;
			delete todelete;
		}
	}*/
}

void Tree::add_edge (int v1, int v2, int w) {
	all_dist[v1][v2] = w;
	all_dist[v2][v1] = w;
	Edge* v1_edge = new Edge (v2, w);
	// inserting edge to empty list
	if (!adj_list[v1]) adj_list[v1] = v1_edge;
	else {
		v1_edge->next = adj_list[v1];
		adj_list[v1] = v1_edge;
	}
	
	// add to v2 list
	Edge* v2_edge = new Edge (v1, w);
	// inserting edge to empty list
	if (!adj_list[v2]) adj_list[v2] = v2_edge;
	else {
		v2_edge->next = adj_list[v2];
		adj_list[v2] = v2_edge;
	}
}

int Tree::distance (int v1, int v2) {
	return all_dist[v1][v2];
}

void Tree::build_dist () {
	std::vector <int> visit (size+1);	// unvisited
	visit[1] = 1;
	std::queue <int> vertices_q;     	// used to fulfill BFS
	vertices_q.push (1);  			 	// enqueue the first element
	
	while (!vertices_q.empty ()) {		// visit all vertices
		// dequeue from the queue
		int cur_node = vertices_q.front ();
		vertices_q.pop ();
		// loop through the edges
		
		Edge* ptr = adj_list[cur_node];
		while (ptr) {
			int i = ptr->connect;
			int edge = ptr->weight;
			ptr = ptr->next;
			if (visit[i]) continue;
			vertices_q.push (i);
			visit[i] = 1;
			for (int j = 1; j <= size; ++j) {
				if (i == j || j == cur_node || !visit[j] || all_dist[i][j]) continue;
				all_dist[i][j] = all_dist[cur_node][j] + edge;
				all_dist[j][i] = all_dist[i][j];
			}
		}
	}
}
// ----------------------------------------------------------------------------

int main () {
	// initiate the tree
	int N;
	std::cin >> N;
	Tree t (N);
	
	// fill in the tree
	int v1, v2, w;
	for (int i = 0; i < N-1; ++i) {
		std::cin >> v1 >> v2 >> w;
		t.add_edge (v1, v2, w);
	}
	t.build_dist ();
	
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> v1 >> v2;
		std::cout << t.distance (v1, v2) << '\n';
	}
	return 0;
}