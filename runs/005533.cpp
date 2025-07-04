#include <iostream>
#include <vector>

// DFT = depth-first traversal

// ================= Edge =================

class Edge {
private:
	unsigned _indexEndEdge;
	int _weight;
	
public:
	Edge(unsigned _indexEndEdge, int weight);

	unsigned GetIndexEndEdge() const;
	int GetWeight() const;
};

Edge::Edge(unsigned indexEndEdge, int weight) :
	_indexEndEdge(indexEndEdge),
	_weight(weight)
{ }

unsigned Edge::GetIndexEndEdge() const {
	return _indexEndEdge;
}

int Edge::GetWeight() const {
	return _weight;
}

// =========================================

// ================= Node =================
enum ColorNode { white, gray, black };

class Node {
private:
	std::vector<Edge> _edges;
	unsigned _index;

public:
	Node(unsigned index);

	ColorNode color;

	void AddEdge(Edge edge);
	void AddEdge(unsigned index, int weight);
	void AddEdge(Node node, int weight);

	unsigned GetIndex() const;

	std::vector<Edge>::const_iterator beginEdges() const;
	std::vector<Edge>::const_iterator endEdges() const;
};

Node::Node(unsigned index) :
	_index(index)
{ }

unsigned Node::GetIndex() const {
	return _index;
}

void Node::AddEdge(Edge edge) {
	_edges.push_back(edge);
}

void Node::AddEdge(unsigned index, int weight) {
	AddEdge(Edge(index, weight));
}

void Node::AddEdge(Node node, int weight) {
	AddEdge(node.GetIndex(), weight);
}

std::vector<Edge>::const_iterator Node::beginEdges() const {
	return _edges.begin();
}

std::vector<Edge>::const_iterator Node::endEdges() const {
	return _edges.end();
}

// ================= Graph =================

typedef std::vector<unsigned> OrderType;
typedef std::vector< std::vector<unsigned> > IndexOrderType;

class Graph {
private:
    std::vector<Node> _nodes;
    unsigned _countNode;

    void DFS_Visit(unsigned indexNode);
    void AddInOrder(unsigned indexNode);

public:
    OrderType order;
    IndexOrderType indexOrder;

    Graph();
    Graph(unsigned countNode);
    void Resize(unsigned countNode);

    unsigned GetCountNodes() const;
    unsigned GetWeightEdge(unsigned startNode, unsigned endNode) const;

    void AddEdge(unsigned startNode, unsigned endNode, int weight);

    Node GetNode(unsigned indexNode) const;
    Node& GetNode(unsigned indexNode);

    std::vector<unsigned> GetIndexOrder(unsigned indexNode) const;

    std::vector<Node>::const_iterator beginNodes() const;
    std::vector<Node>::const_iterator endNodes() const;

    void DFS();
};

Graph::Graph() :
        _countNode(0) {
    order.clear();
    indexOrder.clear();
}

Graph::Graph(unsigned countNode) :
	_countNode(countNode)
{
    order.clear();
    indexOrder.clear();
    for (unsigned numberNode = 0; numberNode < _countNode; ++numberNode) {
            _nodes.push_back(Node(numberNode));
    }

     indexOrder.resize(_countNode);
}

void Graph::Resize(unsigned countNode) {
    _countNode = countNode;
    order.clear();
    indexOrder.clear();

    for (unsigned numberNode = 0; numberNode < _countNode; ++numberNode) {
            _nodes.push_back(Node(numberNode));
    }

    indexOrder.resize(_countNode);
}

unsigned Graph::GetCountNodes() const {
	return _countNode;
}

unsigned Graph::GetWeightEdge(unsigned startNode, unsigned endNode) const{
	--startNode;
	--endNode;

	if (startNode > endNode) {
		std::swap(startNode, endNode);
	}

	if (startNode >= GetCountNodes()){
		std::cerr << "In GetWeightEdge. startNode = " << startNode << " > count node ( = " << GetCountNodes() << ") in graph." << std::endl;
		throw std::exception();
	}
	const Node& node = GetNode(startNode);
	for(std::vector<Edge>::const_iterator iter = node.beginEdges(); iter != node.endEdges(); ++iter) {
		if (iter->GetIndexEndEdge() == endNode) {
			return iter->GetWeight();
		}
	}

	std::cerr << "In GetWeightEdge. In node = " << startNode << ", in edges not edge wiht endNod = " << endNode << std::endl;
	throw std::exception();
}

Node Graph::GetNode(unsigned indexNode) const {
	return _nodes.at(indexNode);
}

Node& Graph::GetNode(unsigned indexNode) {
	return _nodes.at(indexNode);
}

std::vector<Node>::const_iterator Graph::beginNodes() const {
	return _nodes.begin();
}

std::vector<Node>::const_iterator Graph::endNodes() const {
	return _nodes.end();
}

void Graph::DFS() {
        order.clear();
        indexOrder.resize(GetCountNodes());

	for (std::vector<Node>::iterator iter = _nodes.begin(); iter != _nodes.end(); ++iter) {
		iter->color = white;
	}
	for (std::vector<Node>::iterator iter = _nodes.begin(); iter != _nodes.end(); ++iter) {
		if (iter->color == white) {
			DFS_Visit(iter->GetIndex());
		}
	}
}

void Graph::AddInOrder(unsigned indexNode) {
        order.push_back(indexNode + 1);
        indexOrder[indexNode].push_back(order.size() - 1);
}

void Graph::DFS_Visit(unsigned indexNode) {
	Node& rootNode = _nodes[indexNode];
	rootNode.color = gray;
	AddInOrder(indexNode);
	for (std::vector<Edge>::const_iterator iter = rootNode.beginEdges(); iter != rootNode.endEdges(); ++iter) {
		Node& node = _nodes[iter->GetIndexEndEdge()];
		if (node.color == white) {
			DFS_Visit(node.GetIndex());
		}
		AddInOrder(indexNode);
	}
	rootNode.color = black;
}

void Graph::AddEdge(unsigned startNode, unsigned endNode, int weight) {
	if (startNode > GetCountNodes() || startNode <= 0) {
		std::cerr << "In Graph::AddEdge. (startNode = " << startNode << ") > (countNodes = " << GetCountNodes() << ") of startNode <= 0. endNode = " << endNode << ", weight = " << weight << "." << std::endl;
		throw std::exception();
	}
	
        /*if (startNode > endNode) {
	    std::swap(startNode, endNode);
        }*/
	_nodes.at(startNode - 1).AddEdge(endNode - 1, weight);
        _nodes.at(endNode - 1).AddEdge(startNode - 1, weight);
}
// =========================================

// =============== LengthPath ===============
unsigned GetNextIndex(const IndexOrderType& indexOrder, unsigned indexNode, unsigned indexStartNode, unsigned indexEndNode) {
	const std::vector<unsigned>& indexOrderNode = indexOrder[indexNode];
	unsigned maxNextIndex = std::max(indexOrderNode[0], indexStartNode);
	for (std::vector<unsigned>::const_iterator iter = indexOrderNode.begin(); iter != indexOrderNode.end(); ++iter) {
		if (*iter > indexStartNode && *iter <= indexEndNode) {
			maxNextIndex = *iter;
		}
	}

	return maxNextIndex == indexStartNode ? ++indexStartNode : ++maxNextIndex;
}

unsigned GetLengthPath(const Graph& graph, const OrderType& order, const IndexOrderType& indexOrder, unsigned startNode, unsigned endNode) {
	unsigned startIndex = indexOrder.at(startNode)[0];
	unsigned endIndex = indexOrder.at(endNode)[0];
	if (startIndex > endIndex) {
		return GetLengthPath(graph, order, indexOrder, endNode, startNode);
	}

	unsigned length = 0;
	if (startIndex == endIndex) {
		return length;
	}

	unsigned index = startIndex;
	while(index < endIndex) {
		unsigned nextIndex = GetNextIndex(indexOrder, order[index] - 1, index, endIndex);
		length += graph.GetWeightEdge(order.at(index), order.at(nextIndex));
		index = nextIndex;
	}

	return length;
}

unsigned GetLengthPath(const Graph& graph, unsigned startNode, unsigned endNode) {
        OrderType order = graph.order;
        IndexOrderType indexOrder = graph.indexOrder;
	return GetLengthPath(graph, order, indexOrder, startNode - 1, endNode - 1);
}

// =========================================

// =============== Input ===============
void Input(Graph* graph) {
	unsigned countNodeGraph;
	std::cin >> countNodeGraph;
        graph->Resize(countNodeGraph);

        for (unsigned numberLine = 0; numberLine + 1 < countNodeGraph; ++numberLine) {
		int startNode, endNode, weight;
		std::cin >> startNode >> endNode >> weight;
                graph->AddEdge(startNode, endNode, weight);
	}
}

// =========================================

// =============== Output ===============

void Output(const Graph& graph) {
	unsigned countNodesPair;
	std::cin >> countNodesPair;
        for (unsigned numberLine = 0; numberLine < countNodesPair; ++numberLine) {
                unsigned startNode, endNode;
		std::cin >> startNode >> endNode;
		std::cout << GetLengthPath(graph, startNode, endNode) << std::endl;
	}
}

// =========================================

int main() {
    Graph graph;
    Input(&graph);
    graph.DFS();
    Output(graph);

    return 0;
}
