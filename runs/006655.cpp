//============================================================================
// Name        : 2.cpp
// Author      : alexandr
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

class LCA {
private:
	int **tree;
	int numb_nodes;
	int *depths;

	~LCA();
	int get_parent(int child);
public:
	LCA(int numb_nodes);
	void dfs(int node, int depth);
	int get_distance(int node1, int node2);
	void fill_tree(int *arch) { tree[arch[0]][arch[1]] = tree[arch[1]][arch[0]] = arch[2] + 1; }
};

LCA::LCA(int numb_nodes) {
	this->numb_nodes = numb_nodes;
	depths = new int[numb_nodes];
	tree = new int*[numb_nodes];
	for (int i = 0; i < numb_nodes; i++) {
		depths[i] = -1;
		tree[i] = new int[numb_nodes];
		for (int j = 0; j < numb_nodes; j++) {
			tree[i][j] = 0;
		}
	}
}

LCA::~LCA() {
	for (int i = 0; i < numb_nodes; i++) {
		delete[] tree[i];
	}
	delete[] tree;
	delete[] depths;
}

void LCA::dfs(int node, int depth) {
	depths[node] = depth;
	for (int i = 0; i < numb_nodes; i++) {
		if (node != i && tree[node][i] && depths[i] == -1) {
			dfs(i, depth + 1);
		}
	}
}

int LCA::get_parent(int child) {
	for (int i = 0; i < numb_nodes; i++) {
			if (tree[child][i] && depths[child] > depths[i]) {
				return i;
			}
		}

		return 0;
}

int LCA::get_distance(int node1, int node2) {
	int d1 = depths[node1];
	int d2 = depths[node2];
	int parent, dist = 0;

	while (d1 != d2) {
		if (d1 > d2) {
			parent = get_parent(node1);
			dist += tree[parent][node1];
			node1 = parent;
			d1--;
		} else {
			parent = get_parent(node2);
			dist += tree[parent][node2];
			node2 = parent;
			d2--;
		}
	}

	while (node1 != node2) {
		parent = get_parent(node1);
		dist += tree[parent][node1];
		node1 = parent;

		parent = get_parent(node2);
		dist += tree[parent][node2];
		node2 = parent;
	}

	return dist;
}

/**/

int main(int argc, char *argv[]) {
	ifstream in;
	ofstream out;
	int arch[3];
	char buf[20], *p;
	LCA *lca;

	if (argc > 1) {
		in.open(argv[1]);
	} else {
		in.open("input");
	}

	if (in.is_open()) {
		in.getline(buf, 5);
		lca = new LCA(atoi(buf));

		int temp;
		while (!in.eof()) {
			in.getline(buf, 20);
			if (strlen(buf) > 1) {
				p = strtok(buf, " ");
				temp = 0;
				while (p) {
					arch[temp] = atoi(p) - 1;
					temp++;
					p = strtok(NULL, " ");
				}
				lca->fill_tree(arch);
			} else {
				if (argc > 2) {
					out.open(argv[2]);
				} else {
					out.open("output");
				}

				lca->dfs(0, 0);

				while (!in.eof()) {
					in.getline(buf, 20);
					p = strtok(buf, " ");
					if (p) {
						temp = 0;
						while (p) {
							arch[temp] = atoi(p) - 1;
							temp++;
							p = strtok(NULL, " ");
						}
						out << lca->get_distance(arch[0], arch[1]) << endl;
					}
				}
			}
		}

		in.close();
		out.close();
	}

	return 0;
}
