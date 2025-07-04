#include <vector>
#include <list>
#include <iostream>

using namespace std;

typedef pair<int, int> ipair;

struct TreeNode {
	int parent;
	list<ipair> childs;
	int time_in, time_out, distance_to_root;//Можно было бы обойтись расстоянием при обходе при проходе вверх и вниз, но нам не гарантируют, что оно ненулевое
	bool is_grand_child_for(const TreeNode &node) {
		return node.time_in <= time_in && node.time_out >= time_out;
	}
	TreeNode(void): time_in(0), time_out(0), distance_to_root(0) {
	};
};

class Tree {
	private:
		vector<TreeNode> nodes;
		void print_subtree(const int root, const int depth) {
			for (int j = 0; j < depth; j++) {
				cout << '\t';
			}
			cout << root << " (" << nodes[root].time_in << ", " << nodes[root].time_out << ", " << nodes[root].distance_to_root << ")\n";
			for (list<ipair>::const_iterator i = nodes[root].childs.begin(); i != nodes[root].childs.end(); i++) {
				if (nodes[root].time_in > nodes[i->first].time_in) {
					print_subtree(i->first, depth+1);
				}
			}
		};
		int round_init_subtree(const int root, const int time, const int distance) {
			//cout << root << "\n";
			nodes[root].time_in = nodes[root].time_out = time;
			nodes[root].distance_to_root = distance;
			for (list<ipair>::const_iterator i = nodes[root].childs.begin(); i != nodes[root].childs.end(); i++) {
				if (!nodes[i->first].time_in) {
					nodes[root].time_out = round_init_subtree(i->first, nodes[root].time_out + 1, distance + i->second);
					nodes[i->first].parent = root;
				}
			}
			return nodes[root].time_out;
		};
		int find_first_common_parent(const int from, const int to) {
			int common_parent(from);
			while (!( (nodes[from].is_grand_child_for(nodes[common_parent])) && (nodes[to].is_grand_child_for(nodes[common_parent])) )) {
				common_parent = nodes[common_parent].parent;
			}
			return common_parent;
		}
	public:
		void add_rebro(const int from, const int to, const int weight) {
			nodes[from].childs.push_back(ipair(to, weight));
			nodes[to].childs.push_back(ipair(from, weight));
		};
		void print(void) {
			return print_subtree(0, 0);
		};
		void round_init(void) {
			round_init_subtree(0, 1, 0);
		};
		Tree(int size): nodes(vector<TreeNode> (size)) {
		};
		int distance(const int from, const int to) {
			int common_parent(find_first_common_parent(from, to));
			//cout << from << " " << to << " " << common_parent << " " << nodes[from].distance_to_root << " " << nodes[to].distance_to_root << "\n";
			return nodes[from].distance_to_root + nodes[to].distance_to_root - 2 * nodes[common_parent].distance_to_root;
		};
};

int main(int argc, char *argw[]) {
	int N, M, from, to, weight;
	cin >> N;
	Tree tree(N);
	for (int i = 1; i < N; i++) {
		cin >> from >> to >> weight;
		tree.add_rebro(from-1, to-1, weight);
	}
	tree.round_init();
	//tree.print();
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> from >> to;
		cout << tree.distance(from-1, to-1) << '\n';
	}
	return 0;
}
