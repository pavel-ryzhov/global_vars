#include <iostream>
#include <cstdlib>

#include <vector>
using std::vector;
#include <set>
using std::set;

//////////////////////////////////////////////////////////////////////////
struct OutEdge {
    int Son;
    int Cost;

  	OutEdge(int son, int cost): Son(son), Cost(cost) {}
};

std::istream& operator >> (std::istream& i, OutEdge& edge) {
    return i >> edge.Son >> edge.Cost;
}

struct Vertex {
    int Index;
    int Ancestor;
    bool Visited;
    vector<OutEdge> OutEdges;

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

    bool GetVisited(int index) const {
        return vertices[index - 1].Visited;
    }

    void SetVisited(int index) {
        vertices[index - 1].Visited = true;
    }

    int GetOutEdgesAmount (int index) const {
        return vertices[index - 1].OutEdges.size();
    }

    int GetVertexSon (int index, int edgeIndex) const {
        return vertices[index - 1].OutEdges[edgeIndex].Son;
    }

    void AddEdge (int index, OutEdge newEdge) {
        vertices[index - 1].OutEdges.push_back(newEdge);
        vertices[newEdge.Son - 1].Ancestor = index;
    }

    int FindInEdgeCost (int index) const {
        for (int i = 0; i < GetOutEdgesAmount(vertices[index- 1].Ancestor); ++i) {
            if (vertices[vertices[index - 1].Ancestor - 1].OutEdges[i].Son == index) {
                return vertices[vertices[index - 1].Ancestor - 1].OutEdges[i].Cost;
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

struct Result {
    vector<int> answer;
    vector2 queryNumber;

    void Resize (size_t size1, size_t size2) {
        answer.resize(size1);
        queryNumber.resize(size2);
        for (int i = 0; i < queryNumber.size(); ++i) {
            queryNumber[i].resize(size2);
        }
    }
};

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

    for (int i = 0; i < tree->GetOutEdgesAmount(index); ++i) {
        DepthFirstTraverse(tree, dsu, ancestor, result, tree->GetVertexSon(index, i), queries);
        dsu->Unite(index, tree->GetVertexSon(index, i));
        ancestor->at(dsu->Find(index) - 1) = index;
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
    set<int> already_connected;
    for (int i = 1; i < vertexAmount; ++i) {
        int firstIndex;
        int secondIndex;
        int cost;
        std::cin >> firstIndex >> secondIndex >> cost;
        if (already_connected.find(secondIndex) != already_connected.end()) {
            std::swap(firstIndex, secondIndex);
        }
        OutEdge newEdge(secondIndex, cost);
        tree->AddEdge(firstIndex, newEdge);
        already_connected.insert(firstIndex);
        already_connected.insert(secondIndex);
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
        queriesList->push_back(newQuery);
    }
}

void Output (const vector<Query>& queriesList, const vector2& result) {
    for (int  i = 0; i < queriesList.size(); ++i) {
        std::cout << result[queriesList[i].First - 1][queriesList[i].Second - 1] << std::endl;
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
