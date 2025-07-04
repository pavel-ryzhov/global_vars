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
	unsigned short numb_nodes;
	long *depths;

	~LCA();
	unsigned short get_parent(unsigned short child);
public:
	LCA(unsigned short numb_nodes);
	void dfs(unsigned short node, unsigned long depth);
	unsigned long get_distance(unsigned short node1, unsigned short node2);
	void fill_tree(unsigned short *arch) { tree[arch[0]][arch[1]] = tree[arch[1]][arch[0]] = arch[2] + 1; }
};

LCA::LCA(unsigned short numb_nodes) {
	this->numb_nodes = numb_nodes;
	depths = new long[numb_nodes];
	tree = new int*[numb_nodes];
	for (unsigned short i = 0; i < numb_nodes; i++) {
		depths[i] = -1;
		tree[i] = new int[numb_nodes];
		for (unsigned short j = 0; j < numb_nodes; j++) {
			tree[i][j] = -1;
		}
	}
}

LCA::~LCA() {
	for (unsigned short i = 0; i < numb_nodes; i++) {
		delete[] tree[i];
	}
	delete[] tree;
	delete[] depths;
}

void LCA::dfs(unsigned short node, unsigned long depth) {
	depths[node] = depth;
	for (unsigned short i = 0; i < numb_nodes; i++) {
		if (node != i && tree[node][i] != -1 && depths[i] == -1) {
			dfs(i, depth + 1);
		}
	}
}

unsigned short LCA::get_parent(unsigned short child) {
	for (unsigned short i = 0; i < numb_nodes; i++) {
			if (tree[child][i] != -1 && depths[child] > depths[i]) {
				return i;
			}
		}

		return 0;
}

unsigned long LCA::get_distance(unsigned short node1, unsigned short node2) {
	unsigned long d1 = depths[node1];
	unsigned long d2 = depths[node2];
	unsigned short parent;
	unsigned long dist = 0;

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
	unsigned short arch[3];
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

		unsigned short temp;
		while (!in.eof()) {
			in.getline(buf, 20);
			if (strlen(buf) > 4) {
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
