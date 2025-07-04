#include <vector>
#include <iostream>
#include <cstdlib>

using std::vector;
using std::pair;
using std::cin;
using std::cout;

struct Link {
	int to;
	int length;
};

struct DoubleLink {
	int begin;
	int end;
	int length;
};

class Tree {
	int l;	// ceiling integer part of log(tree.size)
	vector < vector<Link> > tree;
	// times for DFS
	int timer;
	vector<bool> used;
	vector<int> t_in, t_out;
	// up[i][j] is 2^j-th parent of node i
	vector < vector<int> > up;
	// length of the way from a node to the root
	vector <int> root_length;

	void DFS (int node, int parent = 0, int parent_length = 0);
	bool Upper (int a, int b) const;
	int LCA (int a, int b) const;
public:
	Tree(const vector<DoubleLink>& links);
	int GetLength(int a, int b) const;
};

Tree::Tree(const vector<DoubleLink>& links) {
	int size = 1 + links.size();
	l = 1;
	while ((1 << l) <= size) {
		++l;
	}
	tree.resize(size);
	used.resize(size, false);
	t_in.resize(size);
	t_out.resize(size);
	up.resize(size);
	root_length.resize(size, 0);
	for (int i = 0; i < size; ++i) {
		up[i].resize(l + 1, 0);
	}
	for (int i = 0; i < links.size(); ++i) {
		Link current;
		current.length = links[i].length, current.to = links[i].end;
		tree[links[i].begin].push_back(current);
		current.to = links[i].begin;
		tree[links[i].end].push_back(current);
	}
	timer = 0;
	DFS(0);
}

void Tree::DFS (int node, int parent, int parent_length) {
	used[node] = true;
	root_length[node] = root_length[parent] + parent_length;
	t_in[node] = ++timer;
	up[node][0] = parent;
	for (int i = 1; i <= l; ++i) {
		up[node][i] = up[up[node][i-1]][i-1];
	}
	for (int i = 0; i < tree[node].size(); ++i) {
		int son = tree[node][i].to;
		if (!used[son]) {
			DFS (son, node, tree[node][i].length);
		}
	}
	t_out[node] = ++timer;
}

bool Tree::Upper (int a, int b) const {
	return (t_in[a] <= t_in[b]) && (t_out[a] >= t_out[b]);
}

int Tree::LCA (int a, int b) const {
	if (Upper (a, b)) {
		return a;
	}
	if (Upper (b, a)) {
		return b;
	}
	for (int i = l; i >= 0; --i) {
		if (! Upper(up[a][i], b)) {
			a = up[a][i];
		}
	}
	return up[a][0];
}

int Tree::GetLength(int a, int b) const {
	int parent = LCA(a, b);
	return root_length[a] + root_length[b] - 2 * root_length[parent];
}

vector<DoubleLink> ReadLinks() {
	vector<DoubleLink> output;
	int size;
	cin >> size;
	for (int i = 1; i < size; ++i) {
		DoubleLink current;
		cin >> current.begin >> current.end >> current.length;
		--current.begin, --current.end;
		output.push_back(current);
	}
	return output;
}

vector< pair<int, int> > ReadRequests() {
	vector< pair<int, int> > output;
	int size;
	cin >> size;
	for (int i = 0; i < size; ++i) {
		pair<int, int> current;
		cin >> current.first >> current.second;
		--current.first, --current.second;
		output.push_back(current);
	}
	return output;
}

vector<int> ProcessRequests(const vector< pair<int, int> >& requests, const Tree& tree) {
	vector<int> output;
	for (int i = 0; i < requests.size(); ++i) {
		output.push_back(tree.GetLength(requests[i].first, requests[i].second));
	}
	return output;
}

void Print(const vector<int>& data) {
	for (int i = 0; i < data.size(); ++i) {
		cout << data[i] << '\n';
	}
}

void RandomInput(vector<DoubleLink>* links, vector< pair<int, int> >* requests) {
	const int MAX_SIZE = 4000;
	const int MAX_REQUESTS = 4000;
	const int MAX_LENGTH = 1000;
	links->clear();
	requests->clear();
	int size = rand() % MAX_SIZE + 1;
	for (int i = 1; i < size; ++i) {
		DoubleLink current;
		current.end = i;
		current.begin = rand() % i;
		current.length = rand() % MAX_LENGTH + 1;
		links->push_back(current);
	}
	int req_size = rand() % MAX_REQUESTS + 1;
	for (int i = 0; i < req_size; ++i) {
		int a = rand() % size;
		int b = rand() % size;
		requests->push_back(pair<int, int> (a, b));
	}
}

void Mark(const vector < vector<Link> >& tree, int a, vector<int>* output, vector<bool>* used) {
	for (int i = 0; i < tree[a].size(); ++i) {
		if ( ! used->at(tree[a][i].to) ) {
			output->at(tree[a][i].to) = output->at(a) + tree[a][i].length;
			used->at(tree[a][i].to) = true;
			Mark(tree, tree[a][i].to, output, used);
		}
	}
}

vector<int> SolveSimple(const vector<DoubleLink>& links, const vector< pair<int, int> >& requests) {
	vector < vector<Link> > tree;
	tree.resize(links.size() + 1);
	for (int i = 0; i < links.size(); ++i) {
		Link current;
		current.length = links[i].length, current.to = links[i].end;
		tree[links[i].begin].push_back(current);
		current.to = links[i].begin;
		tree[links[i].end].push_back(current);
	}
	vector<int> output;
	for (int i = 0; i < requests.size(); ++i) {
		int a = requests[i].first;
		int b = requests[i].second;
		vector<int> marked;
		vector<bool> used;
		marked.resize(tree.size(), 0);
		used.resize(tree.size(), false);
		used[a] = true;
		Mark(tree, a, &marked, &used);
		output.push_back(marked[b]);
	}
	return output;
}

void StressTest(int sr) {
	vector<DoubleLink> links;
	vector< pair<int, int> > requests;
	vector<int> results, simple_results;
	srand(sr);
	int step = 0;
	do {
		cout << step << " OK" << '\n';
		++step;
		RandomInput(&links, &requests);
		Tree tree(links);
		results = ProcessRequests(requests, tree);
		simple_results = SolveSimple(links, requests);
	} while (results == simple_results);
	cout << "ERROR" << '\n';
	//print links and requests
}

int main() {
	//StressTest(239);
	vector<DoubleLink> links = ReadLinks();
	vector< pair<int, int> > requests = ReadRequests();
	Tree tree(links);
	vector<int> results = ProcessRequests(requests, tree);
	Print(results);
	return 0;
}