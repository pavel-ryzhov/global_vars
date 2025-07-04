#include <vector>
#include <iostream>
#include <stdio.h>
#include <cstdlib>

typedef std::vector < std::vector< std::pair<int, int> > > Graph;
typedef std::vector< std::pair<int, int> >::const_iterator CGraphIter;

typedef std::vector< std::pair<int, int> > Request;
typedef std::vector< std::pair<int, int> >::const_iterator CRequestIter;

void Dfs(const Graph& graph
		 , int vertex
		 , int height
		 , int distance
		 , std::vector<char>* visited
		 , std::vector<int>* list
		 , std::vector<int>* heights
		 , std::vector<int>* distances) {	
	(*visited)[vertex] = true;
	(*heights)[vertex] = height;
	list->push_back(vertex);
	for (CGraphIter it = graph[vertex].begin()
		; it != graph[vertex].end(); ++it) {
		if (!(*visited)[it->first]) {
			int current = distance + it->second;
			(*distances)[it->first] = current;
			Dfs(graph
				, it->first
				, height + 1
				, current
				, visited
				, list
				, heights
				, distances);
			list->push_back(vertex);
		}
	}
}

void BuildTree(const std::vector<int>& list
				, const std::vector<int>& heights
				, int i
				, int left
				, int right
				, std::vector<int>* tree) {
	if (left == right) {
		(*tree)[i] = list[left];
	}
	else {
		int middle = (left + right) >> 1;
		BuildTree(list, heights, i+i, left, middle, tree);
		BuildTree(list, heights, i+i+1, middle+1, right, tree);
		if (heights[(*tree)[i+i]] < heights[(*tree)[i+i+1]]) {
			(*tree)[i] = (*tree)[i+i];
		}
		else {
			(*tree)[i] = (*tree)[i+i+1];
		}
	}
}

void Preprocess(const Graph & graph
				, std::vector<int>* list
				, std::vector<int>* heights
				, std::vector<int>* distances
				, std::vector<int>* tree
				, std::vector<int>* first) {
	int n = (int)graph.size();
	std::vector<char> visited(n, false);
	
	list->reserve(n*2);
	heights->resize(n, 0);
	distances->resize(n, 0);

	Dfs(graph, 0, 1, 0, &visited, list, heights, distances);

	int m = (int)list->size();
	tree->resize(list->size() * 4 + 1, -1);
	BuildTree(*list, *heights, 1, 0, m-1, tree);

	first->resize(n, -1);
	for (int i = 0; i < m; ++i)	{
		int vertex = (*list)[i];
		if ((*first)[vertex] < 0) {
			(*first)[vertex] = i;
		}
	}
}

int Lca(int i, int sl, int sr, int l, int r
					, const std::vector<int>& heights
					, const std::vector<int>& tree)
{
	if (sl == l && sr == r)
		return tree[i];
	int sm = (sl + sr) >> 1;
	if (r <= sm)
		return Lca(i+i, sl, sm, l, r, heights, tree);
	if (l > sm)
		return Lca(i+i+1, sm+1, sr, l, r, heights, tree);
	int ans1 = Lca(i+i, sl, sm, l, sm, heights, tree);
	int ans2 = Lca(i+i+1, sm+1, sr, sm+1, r, heights, tree);
	return heights[ans1] < heights[ans2] ? ans1 : ans2;
}


int MinDistance(int start, int end
				, const std::vector<int>& list
				, const std::vector<int>& heights
				, const std::vector<int>& tree
				, const std::vector<int>& first
				, const std::vector<int>& distance) {

	int right = first[end];
	int left = first[start];
	if (left > right) {
		std::swap(left, right);
	}
	int lca = Lca(1, 0, (int)list.size()-1, left, right, heights, tree);
	return distance[start] + distance[end] - 2 * distance[lca];
}

void Load(Graph* graph, Request* request) {
	int n(0);
	scanf("%d", &n);
	graph->resize(n);
	int i(0), j(0), w(0);
	while (--n) {
		int k = scanf("%d %d %d", &i, &j, &w);
		(*graph)[i-1].push_back(std::make_pair(j-1, w));
		(*graph)[j-1].push_back(std::make_pair(i-1, w));
	}
	scanf("%d", &n);
	while (n--) {
		scanf("%d %d", &i, &j);
		request->push_back(std::make_pair(i-1, j-1));
	}	
}

int main() {

	Graph graph;
	Request request;

	//freopen("input1.txt", "r", stdin);

	Load(&graph, &request);

	std::vector<int> list;
	std::vector<int> heights;
	std::vector<int> distances;
	std::vector<int> tree;
	std::vector<int> first;

	Preprocess(graph, &list, &heights, &distances, &tree, &first);

	for (CRequestIter it = request.begin()
		; it != request.end(); ++it) {
		printf("%d\n", MinDistance(it->first
									, it->second
									, list
									, heights
									, tree
									, first
									, distances));
	}

	exit(EXIT_SUCCESS);
}


