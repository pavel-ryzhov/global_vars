#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

typedef unsigned int dist_t;
typedef size_t node_t;

const dist_t UNDEFINED = (dist_t)(-1);
const node_t ROOT_NODE = 0;

// идея взята из http://e-maxx.ru/algo/lca_linear_offline

struct Node
{
	node_t number;
	dist_t distance;

	Node(node_t nodeNumber, dist_t distanceFromParent)
	{
		this->number   = nodeNumber;
		this->distance = distanceFromParent;
	}
};

struct Query
{
	node_t nodeNumber;
	size_t orderNumber;

	Query(node_t nodeNumber, size_t orderNumber)
	{
		this->nodeNumber  = nodeNumber;
		this->orderNumber = orderNumber;
	}
};

// Tarjan's disjoint-sets union (random type)
class DisjointSet
{
public:
    DisjointSet(node_t elementsCount)
    : _elements(elementsCount) {
        for(node_t i = 0; i < _elements.size(); ++i) {
            _elements[i] = i;
        }
    }

    node_t unite(node_t a, node_t b)
    {
        a = find(a); b = find(b);

        if (rand() & 1) swap(a, b);
        return ( _elements[a] = b );
    }

    node_t find(node_t v) {
        return ( v == _elements[v] ? v : _elements[v] = find(_elements[v]) );
    }

private:
    vector<node_t> _elements;
};


// Класс запросов расстояний между вершинами
class QueryList
{
public:
    QueryList(size_t nodes) { _queries.assign(nodes, vector<Query>()); }

    vector<Query>* getNodeQueries(node_t node) { return &_queries[node]; }
    size_t         getQueryCount()             { return _queryCount; }
    friend istream& operator>>(istream&, QueryList&);
private:
    node_t                 _queryCount;
    vector<vector<Query> > _queries;
};


// Граф (дерево)
class Graph
{
public:
    Graph() { _dsu = NULL; };
    ~Graph();

    node_t getNodesCount() { return (_nodesCount); }
    vector<dist_t>* lca(QueryList*, node_t);

    friend istream& operator>>(istream&, Graph&);

protected:
    void dfs(node_t);

private:
    node_t                  _nodesCount;
    node_t                  _edgesCount;
    node_t                  _queriesProcessed;

    vector<dist_t>          _dist;
    vector<dist_t>          _result;
    vector<vector<Node> >   _nodes;
    vector<node_t>          _ancestor;
    vector<bool>            _visited;

    DisjointSet*            _dsu;
    QueryList*              _queries;
};

istream& operator>>(istream& input, Graph& g)
{
    input >> g._nodesCount;

    g._dist.assign(g._nodesCount, 0);
    g._ancestor.assign(g._nodesCount, 0);
    g._visited.assign(g._nodesCount, false);
    g._nodes.assign(g._nodesCount, vector<Node>());

    g._dsu = new DisjointSet(g._nodesCount);

    node_t nodeA, nodeB;
    dist_t length;

    g._edgesCount = g._nodesCount - 1;
    for (node_t i = 0; i < g._edgesCount; i++)
    {
        input >> nodeA >> nodeB >> length;

        --nodeA, --nodeB;

        g._nodes[nodeA].push_back(Node(nodeB,length));
        g._nodes[nodeB].push_back(Node(nodeA,length));
    }

    return input;
}

Graph::~Graph()
{
    if (_dsu != NULL) delete _dsu;
}

istream& operator>>(istream& input, QueryList& q)
{
    input >> q._queryCount;

    node_t nodeA, nodeB;
    for(size_t orderNumber = 0; orderNumber < q._queryCount; orderNumber++)
    {
        input >> nodeA >> nodeB;
        --nodeA, --nodeB;   // 'cause input starts with node 1, not 0

        q._queries[nodeA].push_back(Query(nodeB, orderNumber));
        q._queries[nodeB].push_back(Query(nodeA, orderNumber));
    }
    return input;
}

vector<dist_t>* Graph::lca(QueryList* queries, node_t rootNode = ROOT_NODE)
{
    _queries = queries;
    _queriesProcessed = 0;
    _result.assign(_queries->getQueryCount(), UNDEFINED);

    dfs(rootNode);

    return (&_result);
}

// deep-first search
void Graph::dfs(node_t currentNode)
{
    _ancestor[currentNode] = currentNode;
    _visited [currentNode] = true;

	node_t childNode, edgeLength;
    vector<Node> neighbours = _nodes[currentNode];
	
    for (vector<Node>::iterator child = neighbours.begin(); \
         child != neighbours.end(); ++child)
    {	
		childNode  = child->number;
		edgeLength = child->distance;

		if ( !_visited[childNode] )
        {
            _dist[childNode] = _dist[currentNode] + edgeLength;

            dfs(childNode); // recursion

            node_t    commonNode  = _dsu->unite(currentNode, childNode);
            _ancestor[commonNode] = currentNode;
        }
    }
    
    vector<Query>* nodeQueries = _queries->getNodeQueries(currentNode);
	for (vector<Query>::iterator q = nodeQueries->begin(); q != nodeQueries->end(); ++q)
    {
		node_t destinationNode = q->nodeNumber;
		node_t queryOrder      = q->orderNumber;

        if (_visited[destinationNode] && _result[queryOrder] == UNDEFINED)
        {
            node_t ancestorNode = _ancestor[ _dsu->find(destinationNode) ];
            
            dist_t distBetween = _dist[currentNode] + _dist[destinationNode] 
                                 -(_dist[ancestorNode] * 2);

            _result[queryOrder] = distBetween;
            _queriesProcessed++;
        }
    }
}

int main()
{
    Graph graph;
    cin >> graph;

    QueryList queries(graph.getNodesCount());
    cin >> queries;

    vector<dist_t>* result = graph.lca(&queries);
	for(vector<dist_t>::iterator i = result->begin(); i != result->end(); ++i) 
        cout << *i << endl;

    return 0;
}
