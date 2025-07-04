#include <iostream>
#include <vector>
#include <cstdlib>

using std::cin;
using std::cout;
using std::vector;
using std::swap;

struct EdgeParameters {
    int finalNode;
    int lengthEdge;
};

struct Inquiry {
    int node;
    int inquiryIndex;
};

void InputGraphParameters(int& numberNodes) {     
    cin >> numberNodes;
} 

void InputEdges(const int numberEdges, vector< vector<EdgeParameters> >* edges) {      
    int initialNode, finalNode, lengthEdge, initialNodeIndex, finalNodeIndex;    
    EdgeParameters currentEdge, reversedCurrentEdge;
    
    for (int edgeIndex = 0; edgeIndex < numberEdges; ++edgeIndex) {
        scanf("%d %d %d\n", &initialNode, &finalNode, &lengthEdge);
        
        initialNodeIndex = initialNode - 1;
        finalNodeIndex = finalNode - 1;
        
        currentEdge.lengthEdge = lengthEdge;
        currentEdge.finalNode = finalNodeIndex;
        edges->at(initialNodeIndex).push_back(currentEdge);
        
        reversedCurrentEdge.lengthEdge = lengthEdge;
        reversedCurrentEdge.finalNode = initialNodeIndex;
        edges->at(finalNodeIndex).push_back(reversedCurrentEdge);
    }
} 

void InputInquiries(vector< vector<Inquiry> >* inquiries, int& numberInquiries) {     
    int firstNode, secondNode, firstNodeIndex, secondNodeIndex;
    Inquiry currentInquiry;
    
    cin >> numberInquiries;
    
    for (int inquiryIndex = 0; inquiryIndex < numberInquiries; ++inquiryIndex) {
        scanf("%d %d", &firstNode, &secondNode);
        
        firstNodeIndex = firstNode - 1;
        secondNodeIndex = secondNode - 1;
        
        currentInquiry.node = secondNodeIndex;
        currentInquiry.inquiryIndex = inquiryIndex;
        inquiries->at(firstNodeIndex).push_back(currentInquiry);
        
        currentInquiry.node = firstNodeIndex;
        inquiries->at(secondNodeIndex).push_back(currentInquiry);
    }
}  

int FindSet(const int node, vector<int>* disjointSetUnion) {
    if (node == disjointSetUnion->at(node)) {
        return node;
    } else {
        return disjointSetUnion->at(node) = FindSet(disjointSetUnion->at(node), disjointSetUnion);
    }
}

void UniteSets(const int firstNode, const int secondNode, const int newAncestor, vector<int>* disjointSetUnion, vector<int>* ancestor) {
    int firstNodeAncestor = FindSet(firstNode, disjointSetUnion);
    int secondNodeAncestor = FindSet(secondNode, disjointSetUnion);
    
    if (rand() & 1) {
        swap(firstNodeAncestor, secondNodeAncestor);
    };
    
    disjointSetUnion->at(firstNodeAncestor) = secondNodeAncestor;
    ancestor->at(secondNodeAncestor) = newAncestor;
}

void DepthFirstSearch(const int currentNode, const int currentHeight, const vector< vector<EdgeParameters> >& edges, 
                         const vector< vector<Inquiry> >& inquiries, vector<bool>* isVisitedNode, vector<int>* disjointSetUnion, 
                         vector<int>* ancestor, vector<int>* nodeHeight, vector<int>* lengthesOfShortestPathes) {   
    disjointSetUnion->at(currentNode) = currentNode;
    ancestor->at(currentNode) = currentNode;
    isVisitedNode->at(currentNode) = true;
    nodeHeight->at(currentNode) = currentHeight;
    
    int finalNode, nextHeight;
    int numberEdges = edges[currentNode].size();
    for(int currentEdgeIndex = 0; currentEdgeIndex < numberEdges; ++currentEdgeIndex) {
        if (!isVisitedNode->at(edges[currentNode][currentEdgeIndex].finalNode)) {
            finalNode = edges[currentNode][currentEdgeIndex].finalNode;
            nextHeight = currentHeight + edges[currentNode][currentEdgeIndex].lengthEdge;
            
            DepthFirstSearch(finalNode, nextHeight, edges, inquiries, isVisitedNode, disjointSetUnion, ancestor, nodeHeight, lengthesOfShortestPathes);
            UniteSets(currentNode, finalNode, currentNode, disjointSetUnion, ancestor);
        };        
    };

    int numberInquiries = inquiries[currentNode].size(), lengthToLeastCommonAncestor, leastCommonAncestor;
    for(int currentInquiryIndex = 0; currentInquiryIndex < numberInquiries; ++currentInquiryIndex) {
        if (isVisitedNode->at(inquiries[currentNode][currentInquiryIndex].node)) {
            leastCommonAncestor = ancestor->at(FindSet(inquiries[currentNode][currentInquiryIndex].node, disjointSetUnion));
            lengthToLeastCommonAncestor = nodeHeight->at(leastCommonAncestor);
            lengthesOfShortestPathes->at(inquiries[currentNode][currentInquiryIndex].inquiryIndex) = 
                (nodeHeight->at(currentNode) - lengthToLeastCommonAncestor) + 
                (nodeHeight->at(inquiries[currentNode][currentInquiryIndex].node) - lengthToLeastCommonAncestor);
        }       
    }
}

vector<int> GetLengthesOfShortestPathes(const vector< vector<EdgeParameters> >& edges, const int numberInquiries, const vector< vector<Inquiry> >& newInquiries) {
    int numberNodes = edges.size();
	srand(numberNodes);
	
    vector<bool> isVisitedNode(numberNodes, false);
	vector<int> lengthesOfShortestPathes(numberInquiries), disjointSetUnion(numberNodes), ancestor(numberNodes), nodeHeight(numberNodes);
	int rootNode = 0, rootHeight = 0;
	DepthFirstSearch(rootNode, rootHeight, edges, newInquiries, &isVisitedNode, &disjointSetUnion, &ancestor, &nodeHeight, &lengthesOfShortestPathes);
	
	return lengthesOfShortestPathes;
}

void Output(const vector<int>& lengthesOfShortestPathes) {
    int numberInquiries = lengthesOfShortestPathes.size();
    for (int inquiryIndex = 0; inquiryIndex < numberInquiries; ++inquiryIndex) {
        printf("%d\n", lengthesOfShortestPathes[inquiryIndex]);
    }
}

int main() {
    int numberNodes;    
    InputGraphParameters(numberNodes);

    vector< vector<EdgeParameters> > edges(numberNodes);
    int numberEdges = numberNodes - 1;
    InputEdges(numberEdges, &edges);
    
    vector< vector<Inquiry> > inquiries(numberNodes);
    int numberInquiries;
    InputInquiries(&inquiries, numberInquiries);

    vector<int> lengthesOfShortestPathes = GetLengthesOfShortestPathes(edges, numberInquiries, inquiries);
    
    Output(lengthesOfShortestPathes);
    
    return 0;
}
