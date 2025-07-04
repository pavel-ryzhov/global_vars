#include <iostream>
#include <cstdlib>

#include <vector>
using std::vector;

#include <map>
using std::map;

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

struct Query {
    int First;
    int Second;

    Query () {}

    Query (int first, int second): First(first), Second(second) {}
};

bool operator < (const Query& lhs, const Query& rhs) {
    return (lhs.First < rhs.First) || ((lhs.First == rhs.First) && (lhs.Second < rhs.Second));
}

struct Edge {
    int First;
    int Second;
    int Cost;

    Edge () {}

  	Edge (int first, int second, int cost): First(first), Second(second), Cost(cost) {}
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

    int Calculate (int index, int destination) {
        if (index == destination) {
            return 0;
        }
        return FindInEdgeCost(index) + Calculate(GetAncestor(index), destination);
    }

    int GetMinCost(int first, int second, int lca) {
        return Calculate(first, lca) + Calculate(second, lca);
    }

    void DepthFirstTraverse(DSU* dsu, vector<int>* ancestor, map<Query, int>* result, int index, const vector2& queries) {
        SetVisited(index);
        dsu->MakeSet(index);
        ancestor->at(index - 1) = index;

        for (int i = 0; i < GetDegree(index); ++i) {
            if (GetEdge(index, i).Second == index && !GetVisited(GetEdge(index, i).First)) {
                std::swap(GetEdge(index, i).First, GetEdge(index, i).Second);
            }
            int nextIndex = GetEdge(index, i).Second;
            if (!GetVisited(nextIndex)) {
                SetAncestor(GetEdge(index, i).Second, GetEdge(index, i).First);
                DepthFirstTraverse(dsu, ancestor, result, nextIndex, queries);
                dsu->Unite(index, nextIndex);
                ancestor->at(dsu->Find(index) - 1) = index;
            }
        }

        for (int i = 0; i < queries[index - 1].size(); ++i) {
            if (GetVisited(queries[index - 1][i])) {
                Query newQuery(index, queries[index - 1][i]);
                result->insert(std::make_pair(newQuery, GetMinCost(index, queries[index - 1][i], ancestor->at(dsu->Find(queries[index - 1][i]) - 1))));
                std::swap(newQuery.First, newQuery.Second);
                result->insert(std::make_pair(newQuery, GetMinCost(index, queries[index - 1][i], ancestor->at(dsu->Find(queries[index - 1][i]) - 1))));
            }
        }
    }

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

    void Process (map<Query, int>* result, const vector2& queries) {
        DSU dsu(Size());
        vector<int> ancestor(Size());
        SetAncestor(1, -1);
        DepthFirstTraverse(&dsu, &ancestor, result, 1, queries);
    }
};

//////////////////////////////////////////////////////////////////////////
void InputTree (Tree* tree) {
    int vertexAmount;
    std::cin >> vertexAmount;
    for (int i = 0; i < vertexAmount; ++i) {
        Vertex newVertex(i + 1);
        tree->AddVertex(newVertex);
    }
    for (int i = 1; i < vertexAmount; ++i) {
        Edge newEdge;
        std::cin >> newEdge;
        tree->AddEdge(newEdge);           
    }
}

void InputQueries (vector2* queries, vector<Query>* queriesList) {
    int queriesAmount;
    std::cin >> queriesAmount;
    for (int  i = 0; i < queriesAmount; ++i) {
        int first, second;
        std::cin >> first >> second;
        Query newQuery(first, second);
        queries->at(first - 1).push_back(second);
        queries->at(second - 1).push_back(first);
        queriesList->push_back(newQuery);
    }
}

void Input (Tree* tree, vector2* queries, vector<Query>* queriesList) {
    InputTree(tree);
    queries->resize(tree->Size());
    InputQueries(queries, queriesList);
}

void Output (const vector<Query>& queriesList, const map<Query, int>& result) {
    for (int  i = 0; i < queriesList.size(); ++i) {
        Query newQuery(queriesList[i].First, queriesList[i].Second);
        std::cout << result.at(newQuery) << std::endl;
    }
}

int main () {
    srand(239);
    Tree tree;
    vector2 queries;
    vector<Query> queriesList;
    Input(&tree, &queries, &queriesList);
    
    map<Query, int> result;
    tree.Process(&result, queries);
    
    Output(queriesList, result);

    return 0;
}
