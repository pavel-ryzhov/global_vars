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

const unsigned int INF = 4000001;

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
	
	public:
	Tree (int N) : size (N) {adj_list.resize (N+1);};
	~Tree ();
	void add_edge (int v1, int v2, int w);
	int distance (int v1, int v2);
};

class PQ {
	private:
	struct PQ_elem {
		unsigned int key;
		int vertex;
		PQ_elem* prev;
		PQ_elem* next;
		PQ_elem (int prt, int v) : vertex (v), key (prt), prev (0), next (0) {};
	};
	PQ_elem* top;
	PQ_elem* inf;
	public:
	PQ (int fv, int N);
	~PQ ();
	int get_top ();
	void decrease_key (unsigned int new_key, int v);
	bool empty ();
};
// ----------------------------------------------------------------------------

void Tree::add_edge (int v1, int v2, int w) {
	// add to v1 list
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
	std::vector <unsigned int> dist (size+1);
	for (int i = 1; i <= size; ++i) dist[i] = INF;
	dist[v1] = 0;
	
	PQ pqueue (v1, size);
	while (!pqueue.empty ()) {
		int u = pqueue.get_top ();
		Edge* neigh = adj_list[u];
		while (neigh) {
			int new_dist = dist[u] + neigh->weight;
			if (dist[neigh->connect] > new_dist) {
				dist[neigh->connect] = new_dist;
				pqueue.decrease_key (new_dist, neigh->connect);
			}
			neigh = neigh->next;
		}
	}
	return dist[v2];
}

Tree::~Tree () {
	std::vector<Edge*>::iterator ptr = adj_list.begin () + 1;
	for (; ptr != adj_list.end (); ++ptr) {
		Edge* cur = *ptr;
		while (cur) {
			Edge* todelete = cur;
			cur = cur->next;
			todelete->next = 0;
			delete todelete;
		}
	}
}
// ----------------------------------------------------------------------------

PQ::PQ (int fv, int N) {
	PQ_elem* felem = new PQ_elem (0, fv);
	top = felem;
	inf = 0;
	
	PQ_elem* last = top;
	// insert all the vertices
	for (int i = 1; i <= N; ++i) {
		if (i == fv) continue;
		PQ_elem* elem = new PQ_elem (INF, i);
		if (!inf) inf = elem;
		last->next = elem;
		elem->prev = last;
		last = elem;
	}
}

PQ::~PQ () {
	PQ_elem* cur = top;
	top = 0;
	inf = 0;
	while (cur) {
		PQ_elem* todelete = cur;
		cur = cur->next;
		if (cur) {
			cur->prev = 0;
			todelete->next = 0;
		}
		delete todelete;
	}
}

int PQ::get_top () {
	PQ_elem* felem = top;
	int toreturn = felem->vertex;
	top = top->next;
	if (top) {
		top->prev = 0;
		felem->next = 0;
	}
	else inf = 0;
	delete felem;
	return toreturn;
}

void PQ::decrease_key (unsigned int new_key, int v) {
	if (top->vertex == v) {
		top->key = new_key;
		if (top == inf) inf = inf->next;
		return;
	}
	
	// find the element in the PQ
	PQ_elem* found = top->next;
	while (found->vertex != v) {
		found = found->next;
	}
	// update
	int old_key = found->key;
	found->key = new_key;
	
	// found is not the first
	// all INF
	if (old_key == INF && top == inf) {
		// break old link
		found->prev->next = found->next;
		if (found->next) found->next->prev = found->prev;
		// make new link
		top->prev = found;
		found->next = top;
		found->prev = 0;
		top = found;
		return;
	}
	
	// we know for sure that found is not null and there is at least one non INF element
	PQ_elem* goback = found->prev; // not null
	if (old_key == INF) goback = inf->prev; // not null
	if (found == inf) inf = found->next;
	
	// remove found from its place
	found->prev->next = found->next;
	if (found->next) found->next->prev = found->prev;
	while (goback) {
		if (goback->key < new_key) {
			// place to insert
			found->next = goback->next;
			found->prev = goback;
			if (goback->next) goback->next->prev = found;
			goback->next = found;
			return;
		}
		goback = goback->prev;
	}
	// smallest of all
	found->next = top;
	found->prev = 0;
	top->prev = found;
	top = found;
}

bool PQ::empty () {
	return (top == 0);
}
// ----------------------------------------------------------------------------

int main () {
	// initiate the tree
	int N;
	std::cin >> N;
	Tree t (N);
	
	// fill in the tree
	for (int i = 0; i < N-1; ++i) {
		int v1, v2, w;
		std::cin >> v1 >> v2 >> w;
		t.add_edge (v1, v2, w);
	}
	
	int M;
	std::cin >> M;
	for (int i = 0; i < M; ++i) {
		int v1, v2, d;
		std::cin >> v1 >> v2;
		d = t.distance (v1, v2);
		std::cout << d << '\n';
	}
	
	return 0;
}