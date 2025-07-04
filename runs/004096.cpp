#include <iostream>
#include <cstdlib>

#include <vector>
using std::vector;

//////////////////////////////////////////////////////////////////////////
struct Edge {
    int First;
    int Second;
    int Cost;

  	Edge(int first, int second, int cost): First(first), Second(second), Cost(cost) {}
};

std::istream& operator >> (std::istream& i, Edge& edge) {
    return i >> edge.First >> edge.Second >> edge.Cost;
}

struct Vertex {
    int Index;
    int Ancestor;
    bool Visited;
    vector<Edge> Edges;

    Vertex(int index): Index(index), Ancestor(-1), Visited(false) {}
};

class Tree {
private:
    vector<Vertex> vertices;
public:
    void AddVertex(Vertex newVertex) {
        vertices.push_back(newVertex);
    }

    int GetAncestor(int index) const {
        return vertices[index - 1].Ancestor;
    }

    void SetAncestor(int index, int newAncestor) {
        vertices[index - 1].Ancestor = newAncestor;
    }

    bool GetVisited(int index) const {
        return vertices[index - 1].Visited;
    }

    void SetVisited(int index) {
        vertices[index - 1].Visited = true;
    }

    int GetDegree (int index) const {
        return vertices[index - 1].Edges.size();
    }

    Edge& GetEdge (int index, int edgeIndex) {
        return vertices[index - 1].Edges[edgeIndex];
    }

    void AddEdge (Edge newEdge) {
        vertices[newEdge.First - 1].Edges.push_back(newEdge);
        vertices[newEdge.Second - 1].Edges.push_back(newEdge);
        vertices[newEdge.Second - 1].Ancestor = newEdge.First;
    }

    int FindInEdgeCost (int index) const {
        for (int i = 0; i < GetDegree(vertices[index- 1].Ancestor); ++i) {
            if (vertices[vertices[index - 1].Ancestor - 1].Edges[i].Second == index) {
                return vertices[vertices[index - 1].Ancestor - 1].Edges[i].Cost;
            }
        }
    }

    int Size() const {
        return vertices.size();
    }
};

//////////////////////////////////////////////////////////////////////////
class DSU {
private:
    vector<int> data;

public:
    DSU (int N) {
        data.resize(N);
    }

    void MakeSet (int x) {
        data[x - 1] = x;
    }

    int Find (int x) {
        if (data[x - 1] == x) {
            return x;
        }
        data[x - 1] = Find(data[x - 1]);
        return data[x - 1];
    }

    void Unite (int x, int y)
    {
	    x = Find(x);
	    y = Find(y);
	    if (rand() % 2) {
		    data[y - 1] = x;
        }
	    else {
		    data[x - 1] = y;
        }
    }
};

typedef vector < vector<int> > vector2;

//////////////////////////////////////////////////////////////////////////
int Calculate (Tree* tree, int index, int destination) {
    if (index == destination) {
        return 0;
    }
    return tree->FindInEdgeCost(index) + Calculate(tree, tree->GetAncestor(index), destination);
}

int GetMinCost(Tree* tree, int first, int second, int lca) {
    return Calculate(tree, first, lca) + Calculate(tree, second, lca);
}

void DepthFirstTraverse(Tree* tree, DSU* dsu, vector<int>* ancestor, vector2* result, int index, const vector2& queries) {
    tree->SetVisited(index);
    dsu->MakeSet(index);
    ancestor->at(index - 1) = index;

    for (int i = 0; i < tree->GetDegree(index); ++i) {
        if (tree->GetEdge(index, i).Second == index && !tree->GetVisited(tree->GetEdge(index, i).First)) {
            std::swap(tree->GetEdge(index, i).First, tree->GetEdge(index, i).Second);
        }
        int nextIndex = tree->GetEdge(index, i).Second;
        if (!tree->GetVisited(nextIndex)) {
            tree->SetAncestor(tree->GetEdge(index, i).Second, tree->GetEdge(index, i).First);
            DepthFirstTraverse(tree, dsu, ancestor, result, nextIndex, queries);
            dsu->Unite(index, nextIndex);
            ancestor->at(dsu->Find(index) - 1) = index;
        }
    }

    for (int i = 0; i < queries[index - 1].size(); ++i) {
        if (tree->GetVisited(queries[index - 1][i])) {
            result->at(index - 1)[queries[index - 1][i] - 1] 
                = GetMinCost(tree, index, queries[index - 1][i], ancestor->at(dsu->Find(queries[index - 1][i]) - 1));
        }
    }
}

void Process (Tree* tree, vector2* result, const vector2& queries) {
    DSU dsu(tree->Size());
    vector<int> ancestor(tree->Size());
    tree->SetAncestor(1, -1);
    DepthFirstTraverse(tree, &dsu, &ancestor, result, 1, queries);
}

//////////////////////////////////////////////////////////////////////////
void InputTree (Tree* tree) {
    int vertexAmount;
    std::cin >> vertexAmount;
    for (int i = 0; i < vertexAmount; ++i) {
        Vertex newVertex(i + 1);
        tree->AddVertex(newVertex);
    }
    for (int i = 1; i < vertexAmount; ++i) {
        int firstIndex;
        int secondIndex;
        int cost;
        std::cin >> firstIndex >> secondIndex >> cost;
        Edge newEdge(firstIndex, secondIndex, cost);
        tree->AddEdge(newEdge);           
    }
}

struct Query {
    int First;
    int Second;

    Query () {}

    Query (int first, int second): First(first), Second(second) {}
};

void InputQueries (vector2* queries, vector<Query>* queriesList) {
    int queriesAmount;
    std::cin >> queriesAmount;
    for (int  i = 0; i < queriesAmount; ++i) {
        int first, second;
        std::cin >> first >> second;
        if (first < second) {
            std::swap(first, second);
        }
        Query newQuery(first, second);
        queries->at(first - 1).push_back(second);
        queries->at(second - 1).push_back(first);
        queriesList->push_back(newQuery);
    }
}

void Output (const vector<Query>& queriesList, const vector2& result) {
    for (int  i = 0; i < queriesList.size(); ++i) {
        int answer = result[queriesList[i].First - 1][queriesList[i].Second - 1];
        if (answer == 0) {
            answer = result[queriesList[i].Second - 1][queriesList[i].First - 1];;
        }
        std::cout << answer << std::endl;
    }
}

int main () {
    srand(239);
    Tree tree;
    InputTree(&tree);
    vector2 queries(tree.Size());
    vector<Query> queriesList;
    vector2 result(tree.Size(), vector<int>(tree.Size(), 0));
    InputQueries(&queries, &queriesList);

    Process(&tree, &result, queries);
    Output(queriesList, result);

    return 0;
}
