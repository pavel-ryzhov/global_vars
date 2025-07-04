/**
 * \file pathfinder.cpp
 * \brief Программа для поиска наикратчайшего пути между двумя вершинами в дереве
 * \author Кутуков Денис
 */

#include <iostream>
#include <vector>

//=======================================================================

typedef unsigned int uint;

typedef struct TEdge
{
    uint vertex_to;
    uint weight;
} Edge;

typedef struct TQuery
{
    uint vertex_to;
    uint index;
} Query;

//================= Объявление класса Vertex =================================

class Vertex
{
public:
    Vertex();
    virtual ~Vertex();

    void addEdge(uint to, uint weight);
    void addQuery(uint to, uint index);
    void visit(uint index, uint rootDistance);

    inline bool isVisited() const { return _visited; }
    inline uint getEdgesCount() const { return _edges.size(); }
    inline uint getQueriesCount() const { return _queries.size(); }
    inline uint getAncestor() const { return _ancestor; }
    inline void setAncestor(uint ancestor) { _ancestor = ancestor; }
    inline uint getRootDistance() const { return _rootDistance; }
    inline uint getEdgeTo(int i) const { return _edges[i].vertex_to; }
    inline uint getEdgeWeight(int i) const { return _edges[i].weight; }
    inline uint getQueryTo(int i) const { return _queries[i].vertex_to; }
    inline uint getQueryIndex(int i) const { return _queries[i].index; }

private:
    std::vector<Edge> _edges;
    std::vector<Query> _queries;
    uint _index;
    uint _ancestor;
    uint _rootDistance;
    bool _visited;
};

//================== Реализация класса Vertex ===============================

Vertex::Vertex()
{
    _ancestor = 0;
    _visited = false;
    _rootDistance = 0;
}

Vertex::~Vertex()
{
    _edges.clear();
    _queries.clear();
}

void Vertex::addEdge(uint to, uint weight)
{
    Edge edge = {to, weight};
    _edges.push_back(edge);
}

void Vertex::addQuery(uint to, uint index)
{
    Query query = {to, index};
    _queries.push_back(query);
}

void Vertex::visit(uint index, uint rootDistance)
{
    _ancestor = index;
    _rootDistance = rootDistance;
    _visited = true;
}

//==================== Объявление класса Tree ===============================

class Tree
{
public:
    Tree(uint vertexCount);
    virtual ~Tree();

    void addEdge(uint from, uint to, uint weight);
    void setQueriesCount(uint queriesCount);
    void addQuery(uint from, uint to);
    void solve();
    inline uint getAnswer(uint index) const { return _answers[index]; }

private:
    void depthFirstSearch(uint vertex, uint rootDistance);
    uint dsuGet(uint vertex);
    void dsuUnite(uint vertex1, uint vertex2, uint ancestor);

    uint _vertexCount;
    uint _queriesCount;
    uint _addedQueriesCount;
    uint* _dsu;
    uint *_answers;

    Vertex *_vertices;
};

//================= Реализация класса Tree ===================================

Tree::Tree(uint vertexCount)
{
    _vertexCount = vertexCount;
    _queriesCount = 0;
    _addedQueriesCount = 0;

    if (_vertexCount > 0)
    {
        _dsu = new uint[_vertexCount];
        _answers = NULL;
        _vertices = new Vertex[_vertexCount];
    }
}

Tree::~Tree()
{
    delete[] _dsu;
    delete[] _answers;
    delete[] _vertices;
}

void Tree::setQueriesCount(uint queriesCount)
{
    _queriesCount = queriesCount;
    _addedQueriesCount = 0;
    if (_queriesCount > 0)
        _answers = new uint[_queriesCount];
}

void Tree::addEdge(uint from, uint to, uint weight)
{
    if (from < _vertexCount)
    {
        _vertices[from].addEdge(to, weight);
        if (from != to)
        {
            _vertices[to].addEdge(from, weight);
        }
    }
}

void Tree::addQuery(uint from, uint to)
{
    if (from < _vertexCount && to < _vertexCount)
    {
        _vertices[from].addQuery(to, _addedQueriesCount);
        if (from != to)
        {
            _vertices[to].addQuery(from, _addedQueriesCount);
        }
        _addedQueriesCount++;
    }
}

void Tree::solve()
{
    if (_vertexCount > 0 && _queriesCount > 0 && _addedQueriesCount > 0)
        depthFirstSearch(0, 0);
}

void Tree::depthFirstSearch(uint vertexIndex, uint rootDistance)
{
    _dsu[vertexIndex] = vertexIndex;
    Vertex *vertex = &_vertices[vertexIndex];
    vertex->visit(vertexIndex, rootDistance);

    for (uint i = 0; i < vertex->getEdgesCount(); i++)
    {
        uint vertexTo = vertex->getEdgeTo(i);
        if (!_vertices[vertexTo].isVisited())
        {
            depthFirstSearch(vertexTo, rootDistance + vertex->getEdgeWeight(i));
            dsuUnite(vertexIndex, vertexTo, vertexIndex);
        }
    }

    // отвечаем на запросы
    for (uint i = 0; i < vertex->getQueriesCount(); i++)
    {
        uint vertexTo = vertex->getQueryTo(i);
        if (_vertices[vertexTo].isVisited())
        {
            uint dsu = dsuGet(vertexTo);
            uint ancestor = _vertices[dsu].getAncestor();
            uint dist = vertex->getRootDistance() + _vertices[vertexTo].getRootDistance() -
                    2 * _vertices[ancestor].getRootDistance();
            _answers[vertex->getQueryIndex(i)] = dist;
        }
    }
}

uint Tree::dsuGet(uint vertex)
{
    return vertex == _dsu[vertex] ? vertex : _dsu[vertex] = dsuGet(_dsu[vertex]);
}

void Tree::dsuUnite(uint vertex1, uint vertex2, uint ancestor)
{
    vertex1 = dsuGet(vertex1);
    vertex2 = dsuGet(vertex2);
    _dsu[vertex1] = vertex2;
    _vertices[vertex2].setAncestor(ancestor);
}

//================= Главная функция ==========================================

int main(int argc, char** argv)
{
    uint vertexesCount = 0;
    std::cin >> vertexesCount;
    Tree *tree = new Tree(vertexesCount);
    for (uint i = 0; i < vertexesCount - 1; i++)
    {
        uint from, to, weight;
        std::cin >> from >> to >> weight;
        tree->addEdge(from-1, to-1, weight);
    }

    uint queriesCount = 0;
    std::cin >> queriesCount;
    tree->setQueriesCount(queriesCount);
    for (uint i = 0; i < queriesCount; i++)
    {
        uint from, to;
        std::cin >> from >> to;
        tree->addQuery(from-1, to-1);
    }

    tree->solve();
    for (uint i = 0; i < queriesCount; i++)
    {
        std::cout << tree->getAnswer(i) << std::endl;
    }

    delete tree;
    return 0;
}
