#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

//-----------------------------------------------------------------------------
// Определения типов и проч.

typedef unsigned int  uint;

const uint MAXN      = 40000;
const uint UNDEFINED = ((uint)-1);
const uint ROOT_NODE = 0;

typedef uint size_t;
typedef uint dist_t;

//-----------------------------------------------------------------------------
// Определения классов и структур

// Номер узла и расстояние до него
struct Node
{
	size_t number;
	dist_t distance;

	Node(size_t nodeNumber, dist_t distanceFromParent)
	{
		this->number   = nodeNumber;
		this->distance = distanceFromParent;
	}
};

// Запрос до узла и порядковый номер запроса
struct Query
{
	size_t nodeNumber;
	size_t orderNumber;

	Query(size_t nodeNumber, size_t orderNumber)
	{
		this->nodeNumber  = nodeNumber;
		this->orderNumber = orderNumber;
	}
};

// Класс Disjoint-set union (DSU) для объединения узлов
class DisjointSet
{
public:
    DisjointSet(size_t elementsCount)
    : _elements(elementsCount) {
        for(size_t i = 0; i < _elements.size(); ++i) {
            _elements[i] = i;
        }
    }

    size_t unite(size_t a, size_t b)
    {
        a = find(a); b = find(b);

        if (rand() & 1) swap(a, b);
        return ( _elements[a] = b );
    }

    size_t find(size_t v) {
        return ( v == _elements[v] ? v : _elements[v] = find(_elements[v]) );
    }

private:
    vector<size_t> _elements;
};


// Класс запросов дистанций между вершинами
class QueryList
{
public:
    QueryList(istream&, size_t);

    vector<Query>* getNodeQueries(size_t);
    size_t         getQueryCount();

private:
    size_t                 _queryCount;
    vector<vector<Query> > _queries;
};


// Граф (дерево)
class Graph
{
public:
    Graph(istream&);
    ~Graph();
    size_t getNodesCount();
    vector<dist_t>* lca(QueryList*, size_t);

protected:
    void dfsForLca(size_t);

private:
    size_t                  _nodesCount;
    size_t                  _edgesCount;
    size_t                  _queriesProcessed;

    vector<dist_t>          _dist;
    vector<dist_t>          _result;
    vector<vector<Node> >   _nodes;
    vector<size_t>          _ancestor;
    vector<bool>            _visited;

    DisjointSet*            _dsu;
    QueryList*              _queries;
};


//-----------------------------------------------------------------------------
// Реализация классов

// Создание нового графа из потока ввода
Graph::Graph(istream& input)
{
    input >> _nodesCount;

    _dist.assign(_nodesCount, 0);
    _ancestor.assign(_nodesCount, 0);
    _visited.assign(_nodesCount, false);
    _nodes.assign(_nodesCount, vector<Node>());

    _dsu = new DisjointSet(_nodesCount);

    size_t nodeA, nodeB;
    dist_t length;

    _edgesCount = _nodesCount - 1;
    for (size_t i = 0; i < _edgesCount; i++)
    {
        input >> nodeA >> nodeB >> length;

        --nodeA, --nodeB;

        _nodes[nodeA].push_back(Node(nodeB,length));
        _nodes[nodeB].push_back(Node(nodeA,length));
    }
}

Graph::~Graph()
{
    delete _dsu;
}

// Количество вершин в графе
size_t Graph::getNodesCount()
{
    return (_nodesCount);
}

// Создание списка запросов расстояний между вершинами
QueryList::QueryList(istream& input, size_t nodesCount)
{
    input >> _queryCount;

    _queries.assign(nodesCount, vector<Query>());
    
    size_t nodeA, nodeB;
    for(size_t ord = 0; ord < _queryCount; ord++)
    {
        input >> nodeA >> nodeB;

        --nodeA, --nodeB;

        _queries[nodeA].push_back(Query(nodeB, ord));
        _queries[nodeB].push_back(Query(nodeA, ord));
    }
}

// Возвращает вектор запросов для вершины
vector<Query>* QueryList::getNodeQueries(size_t nodeNumber)
{
    return ( &_queries[nodeNumber] );
}

// Количество запросов в очереди
size_t QueryList::getQueryCount()
{
    return ( _queryCount );
}

// Запуск алгоритма Least Common Ancestor
vector<dist_t>* Graph::lca(QueryList* queries, size_t rootNode = ROOT_NODE)
{
    _queries = queries;
    _queriesProcessed = 0;
    _result.assign(_queries->getQueryCount(), UNDEFINED);

    dfsForLca(rootNode);

    return (&_result);
}

// Обход графа в глубину с обработкой запросов LCA
void Graph::dfsForLca(size_t currentNode)
{
    _ancestor[currentNode] = currentNode;
    _visited [currentNode] = true;

	size_t childNode, edgeLength;
    vector<Node> neighbours = _nodes[currentNode];
	for (vector<Node>::iterator child = neighbours.begin(); child != neighbours.end(); ++child)
    {	
		childNode  = child->number;
		edgeLength = child->distance;

		if ( !_visited[childNode] )
        {
            _dist[childNode] = _dist[currentNode] + edgeLength;

            dfsForLca(childNode); // recursion

            size_t    commonNode  = _dsu->unite(currentNode, childNode);
            _ancestor[commonNode] = currentNode;
        }
    }
    
    vector<Query>* nodeQueries = _queries->getNodeQueries(currentNode);
	for (vector<Query>::iterator q = nodeQueries->begin(); q != nodeQueries->end(); ++q)
    {
		size_t destinationNode = q->nodeNumber;
		size_t queryOrder      = q->orderNumber;

        if ( _visited[destinationNode] && _result[queryOrder] == UNDEFINED )
        {
            size_t ancestorNode = _ancestor[ _dsu->find(destinationNode) ];
            
            dist_t distBetween =
                  _dist[currentNode] 
                + _dist[destinationNode]
                -(_dist[ancestorNode] * 2);

            _result[queryOrder] = distBetween;
            _queriesProcessed++;
        }
    }
}

//-----------------------------------------------------------------------------
// Entry point:
int main()
{
    // ifstream input("input.txt");
    // ofstream output("output.txt");
    
    Graph     graph(cin);
    QueryList queries(cin, graph.getNodesCount());

    vector<dist_t>* result = graph.lca(&queries);
	for(vector<dist_t>::iterator i = result->begin(); i != result->end(); ++i) 
    {
        cout << *i << endl;
    }

    // input.close();
    // output.close();

	return 0;
}