#include <stdlib.h>
#include <iostream>
#include <vector>


using namespace std;
typedef vector< pair<int,int> > graph_line;
typedef graph_line::iterator graph_iter;
typedef vector<graph_line> t_graph;
t_graph graph;


const int maxsize = 40000;
vector <bool> used;
int depth[maxsize], parent[maxsize], depth_bin[maxsize];
int way = 0, way_bin = 0;
vector < pair<int,int> > Nodes;

inline void dfs (int v, int lastleng, int from) {
	used[v] = true;
	parent[v] = from;
	depth[v] = way;
	depth_bin[v] = way_bin;

	for (size_t i=0; i<graph[v].size(); ++i) {
            //cout << v << ":" << graph[v][i].first << " и " << graph[v][i].second << endl;
		int CurrentNode = graph[v][i].first;
		int CurrentLen = graph[v][i].second;
		if (!used[CurrentNode]) {
			way += CurrentLen;
			++way_bin;
			dfs (CurrentNode, CurrentLen, v);
		}
	}
	--way_bin;
	way -= lastleng;
}

inline void FindDist(int n) {
	for (int i=0; i<n; ++i) {
		int a = Nodes[i].first;
		int b = Nodes[i].second;
                int c = a;
		int d = b;

		while (depth_bin[a] != depth_bin[b]) {
			if (depth_bin[a] > depth_bin[b])
				a = parent[a];
			else
				b = parent[b];
		}

		while (a != b) {
			a = parent[a];
			b = parent[b];
		}
		int lca = a;

		int way_ab = depth[c] + depth[d] - 2*depth[lca];
		cout /*<< "Way from " << c << " to " << d << " = " */<< way_ab << endl;
	}
}

inline void ReadGraph(int n) {
    int a, b, dist, i=0;
    for (i; i<n-1; ++i) {
        cin >> a >> b >> dist;
        b -= 1;
        a -= 1;
        graph[a].push_back(make_pair(b, dist));
        graph[b].push_back(make_pair(a, dist));
    }
}

inline void print(int n)
{
        for(int i=0; i<n; ++i) {
            for (int j=0; j<graph[i].size(); ++j) {
            cout << (graph[i])[j].first << ";" << (graph[i])[j].second << " ";
        }
        cout << endl;
    }
}

inline void print_nodes() {
    for (int i=0; i<Nodes.size(); ++i) {
        cout << Nodes[i].first << ";" << Nodes[i].second << endl;
    }
}

inline void GetPeaks(int n) {
    int a, b;
    for (int i=0; i<n; ++i) {
        cin >> a >> b;
        Nodes[i]= make_pair(--a, --b);
    }
}

int main(int argc, char** argv) {
    int count_peak;
    cin >> count_peak; //Количество вершин
    graph.resize(count_peak);
    ReadGraph(count_peak);
    used.resize(count_peak, false);
    dfs(0,0,0);
    cin >> count_peak; //Количество пар для расстояния
    Nodes.resize(count_peak);
    GetPeaks(count_peak);
    //print_nodes();
    FindDist(count_peak);
    //print(count_peak);
    return (EXIT_SUCCESS);
}
