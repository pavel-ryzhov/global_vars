/*	Author: Bychkov Ivan
 *
 *	Note: comments was written on English for the sake of font compatibility
 *
 *	Requested path is defined before the program run so
 *	we can use Tarjan's off-line lca algoritm
 */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair <long, long> pll;	

class LCA {	
	//tree, data structure: vertex1 -> (verex2, edge length)
	vector <vector <pll> > &graph;		
	//requests, data structure: vertex1 -> (vertex2, number of request)
	vector <vector <pll> > &request;	
	vector <long> &result;				
	vector <long> parent, ancestor, rank;	
	vector <long> range;				//path length from root vertex
	vector <bool> isChecked;

	long find_set (long v) {
		if (v != parent[v]) 
			parent[v] = find_set (parent[v]);
		return parent[v];
	}

	void union_vertex (long v1, long v2) {
		v1 = find_set (v1);
		v2 = find_set (v2);

		if (rank[v1] > rank[v2])
			parent[v2] = v1;
		else {
			parent[v1] = v2;
			if (rank[v2] = rank[v1]) rank[v2]++;
		}
	}

	//Solution based on dfs (Deep-First search) algorithm
	void go (long v, long r) {
		parent[v] = v; rank[v] = 0;	
		ancestor[find_set(v)] = v;
		range[v] = r;
		isChecked[v] = true;
		for (long i=0; i<graph[v].size(); i++) {
			long v2 = graph[v][i].first;
			if (!isChecked[v2]) {
				go (v2, r+graph[v][i].second);
				union_vertex (v, v2);
				ancestor[find_set(v)] = v;
			}
		}
		for (long i=0; i<request[v].size(); i++) {
			long v2 = request[v][i].first;		
			if (isChecked[v2]) {
				long va = ancestor[find_set(v2)];
				result[request[v][i].second] = abs (range[v]+range[v2]-2*range[va]);
			}
		}
	}

public:
	LCA (vector <vector <pll> > & g, vector <vector <pll> > & req, vector <long> & res) 
	: graph (g), request (req), result (res) {
		long N = g.size(), M = req.size();
		parent = vector <long> (N);
		range = vector <long> (N);
		rank = vector <long> (N);
		ancestor = vector <long> (N);
		isChecked = vector <bool> (N, false);
		result.resize (M);
	}

	void solve () {
		long root = 0;		
		go (root, 0);		
	}
};

int main (int argc, char* argv[])
{	
	long N, M;	

	//build graph from input stream
	cin >> N;
	vector <vector <pll> > graph (N, vector <pll>());	
	for (long i=1; i<N; i++) {
		long v1, v2, l;
		cin >> v1 >> v2 >> l;
		v1--; v2--;
		graph[v1].push_back (make_pair (v2, l));
		graph[v2].push_back (make_pair (v1, l));
	}

	//read request	
	cin >> M;
	vector <vector <pll> > request (N, vector <pll>());	
	for (long i=0; i<M; i++) {
		long v1, v2;
		cin >> v1 >> v2;
		v1--; v2--;
		request[v1].push_back (make_pair (v2,i));
		request[v2].push_back (make_pair (v1,i));
	}
	
	//solve problem
	vector <long> result;
	LCA lca (graph, request, result);
	lca.solve();

	//output result
	for (long i=0; i<M; i++)
		cout << result[i] << endl;

	return 0;
}

