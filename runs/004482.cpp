#include <list>
#include <iostream>
#include <fstream>

using namespace std;

struct Node;
struct Edge;

struct Edge {
    Node* node1;
    Node* node2;
    int legth;
    bool wasSetup;
};

struct Node {
    Node* parent;
    int distanceToParent;
    int nestingLevel;
    list<Edge*> edges;
};

void setupChildrens(Node* node) {
    list<Edge*>* edges = &(node->edges);
    for (list<Edge*>::iterator edgeIter = edges->begin();
            edgeIter != edges->end();
            edgeIter++)
    {
        Edge* edge = *edgeIter;

        if (edge->wasSetup) continue;

        Node* child;
        if (edge->node1 == node) child = edge->node2;
        else child = edge->node1;

        edge->wasSetup = true;
        child->parent = node;
        child->nestingLevel = node->nestingLevel + 1;
        child->distanceToParent = edge->legth;

        setupChildrens(child);
    }
}

int findDistance(Node* node1, Node* node2) {
    if (node1 == node2) return 0;
    if (node2->parent == node1) return node2->distanceToParent;
    if (node1->parent == node2) return node1->distanceToParent;

    int distance1 = 0, distance2 = 0;

    if (node1->nestingLevel > node2->nestingLevel) // поднимаемся до высоты node2
    {
        do {
            distance1 += node1->distanceToParent;
            node1 = node1->parent;
        } while (node1->nestingLevel > node2->nestingLevel);
    } else if (node2->nestingLevel > node1->nestingLevel) // поднимаемся до высоты node1
    {
        do {
            distance2 += node2->distanceToParent;
            node2 = node2->parent;
        } while (node2->nestingLevel > node1->nestingLevel);
    }

    // после этого оба узла находятся на одном уровне вложенности

    while (node1->nestingLevel >= 0) {
        if (node1 == node2) return distance1 + distance2;
        else {
            distance1 += node1->distanceToParent;
            distance2 += node2->distanceToParent;

            node1 = node1->parent;
            node2 = node2->parent;
        }
    }

    return 0;
}

int main(int argc, char** argv)
{



    int nodesNumber;
    cin >> nodesNumber;
    
    if(nodesNumber < 2) 
    {
        cout << 0;
        return 0;
    }
    
    Node* nodes = new Node[nodesNumber];

    for(int i = 0; i < nodesNumber; i++)
    {
        nodes[i].distanceToParent = 0;
        nodes[i].nestingLevel = 0;
        nodes[i].parent = 0;
        nodes[i].edges = list<Edge*>();
    }

    int node1, node2, len;
    for(int i = 0; i < nodesNumber-1; i++)
    {
        cin >> node1 >> node2 >> len;
        
        Edge* edge = new Edge;
        edge->legth = len;
        edge->node1 = &nodes[node1-1];
        edge->node2 = &nodes[node2-1];
        edge->wasSetup = false;
        
        nodes[node1-1].edges.push_back(edge);
        nodes[node2-1].edges.push_back(edge);
    }

    setupChildrens(&nodes[0]);

    int answersNumber;
    cin >> answersNumber;
    int* answers = new int[answersNumber];

    for(int i = 0; i < answersNumber; i++)
    {
        cin >> node1 >> node2;
        answers[i] = findDistance(&nodes[node1-1], &nodes[node2-1]);
    }

    for(int i = 0; i < answersNumber; i++)
    {
        cout << answers[i] << endl;
    }

    delete [] answers;
    delete [] nodes;
    return 0;
}

