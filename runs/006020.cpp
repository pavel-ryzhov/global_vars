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


int size;

typedef std::vector< std::vector <int> > Vec_veci;

void build_dist (Vec_veci &all_dist) {
	std::vector <int> visit (size);			// unvisited
	visit[0] = 1;
	std::vector <int> vertices_q (size);	// used to fulfill BFS
	int start = 0;
	int end = 0;
	vertices_q[start] = 0;  			 	// enqueue the first element
	
	while (end-start+1) {					// visit all vertices
		// dequeue from the queue
		int cur_node = vertices_q[start++];
				
		for (int i = 0; i < size; ++i) {
			if (all_dist[cur_node][i] < 0 || visit[i]) continue;
			vertices_q[++end] = i;
			visit[i] = 1;
			for (int j = 0; j < size; ++j) {
				if (!visit[j] || all_dist[i][j] >= 0 || i == j || j == cur_node) continue;
				all_dist[i][j] = all_dist[cur_node][j] + all_dist[cur_node][i];
				all_dist[j][i] = all_dist[i][j];
			}
		}
	}
}

int main () {
	// initiate the tree
	std::cin >> size;
	std::vector< std::vector <int> > all_dist (size);
	for (int i = 0; i < size; ++i) all_dist[i].resize (size, -1);
	
	// fill in the tree
	int v1, v2, w;
	for (int i = 0; i < size-1; ++i) {
		std::cin >> v1 >> v2 >> w;
		all_dist[--v1][--v2] = w;
		all_dist[v2][v1] = w;
	}
	build_dist (all_dist);

	std::cin >> w;
	for (int i = 0; i < w; ++i) {
		std::cin >> v1 >> v2;
		std::cout << all_dist[v1-1][v2-1] << '\n';
	}
	return 0;
}