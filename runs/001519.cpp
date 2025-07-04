// сохраняем все вершины и все ребра (ребро - ссылки друг на друга)
// выделяем одну вершину (не важно какую, поэтому возьмем ту у которой больше всего ребер)
// строим расстояния до это вершины и ссылки на родителя

#include <vector>
#include <iostream>
#include <string>
#include <memory>

int parseInt(const std::string& src) {
	int result = src[0] - '0';
	for(size_t x = 1; x < src.length(); x++) {
		result = result*10 + (src[x] - '0');
	}
	return result;
}

typedef std::auto_ptr< std::vector< int > > IntVector;

IntVector separateString(const std::string& src) {
	IntVector result(new std::vector< int >());
	
	size_t off = 0;
	size_t len = src.length();
	while(off != len) {
		for(; off < len && src[off] == ' '; off++);
		size_t off2 = off;
		for(; off2 < len && src[off2] != ' '; off2++);
		result->push_back(parseInt(src.substr(off, off2 - off)));
		off = off2;
	}

	return result;
}

class tree {
public:
	tree(int size);
	void insert(int from, int to, int value);
	long long distance(int from, int to);
	void complete();
	~tree();
private:
	struct node {
		typedef std::pair< node*, int > t_edge;
		typedef std::vector< t_edge > t_edges;

		node* parent;
		int p_distance;
		int depth;
		t_edges edges;

		void complete(node* parent, int weight, int depth);
	};
	std::vector< node* > nodes;
	node* big;
};

int main() {
	// проверку правильности введенных данных не проводим
	tree* all;
	std::vector< std::pair< int, int > > toDo;

	char buffer[1001];
	std::string s_buffer;

	bool first = true;
	int countEdges;
	int totalEdges;
	bool second = true;
	int countDistances;
	int totalDistances;
	while(std::cin.good() && !std::cin.fail()) {
		std::cin.getline(buffer, 1000);
		s_buffer.assign(buffer);
		if(first) {
			IntVector values = separateString(s_buffer);
			countEdges = 0;
			all = new tree(totalEdges = values->at(0));
			first = false;
			continue;
		}
		if(countEdges < totalEdges - 1) {
			IntVector values = separateString(s_buffer);
			all->insert(values->at(0), values->at(1), values->at(2));
			countEdges++;
			continue;
		}
		if(second) {
			all->complete();
			IntVector values = separateString(s_buffer);
			countDistances = 0;
			totalDistances = values->at(0);
			second = false;
			continue;
		}
		if(countDistances < totalDistances) {
			IntVector values = separateString(s_buffer);
			toDo.push_back(std::make_pair(values->at(0), values->at(1)));
			if(++countDistances == totalDistances) {
				break;
			}
			continue;
		}
	}
	for(size_t x = 0; x < toDo.size(); x++) {
		std::cout << all->distance(toDo[x].first, toDo[x].second) << std::endl;
	}
	delete all;

	return 0;
}

tree::tree(int size)
{
	nodes.reserve(size);
	for(int i = 0; i < size; i++) {
		nodes.push_back(new node());
	}
}

void tree::insert(int from, int to, int value) {
	node* t = nodes[from - 1];
	node* w = nodes[to - 1];
	t->edges.push_back(std::make_pair(w, value));
	w->edges.push_back(std::make_pair(t, value));
}

void tree::complete() {
	big = nodes[0];
	int count = big->edges.size();
	// находим вершину с наибольшим числом ребер и ее выбираем как центр
	for(size_t x = 1; x < nodes.size(); x ++) {
		int tmp = nodes[x]->edges.size();
		if(tmp > count) {
			big = nodes[x];
			count = tmp;
		}
	}
	big->complete(NULL, 0, 0);
}

long long tree::distance(int from, int to) {
	node* t = nodes[from - 1];
	node* w = nodes[to - 1];
	long long result = ((long long)t->p_distance) + ((long long)w->p_distance);

	while(true) {
		if(t == w) break;
		if(t->depth > w->depth) {
			t = t->parent;
		} else {
			w = w->parent;
		}
	}

	return result - 2 * ((long long)t->p_distance);
}

tree::~tree() {
	for(size_t x = 0; x < nodes.size(); x ++) {
		delete nodes[x];
	}
}

void tree::node::complete(node* prnt, int weight, int depth) {
	parent = prnt;
	p_distance = weight;
	this->depth = depth;
	for(size_t x = 0; x < edges.size(); x++) {
		if(edges[x].first != prnt) {
			edges[x].first->complete(this, weight + edges[x].second, depth + 1);
		}
	}
}
