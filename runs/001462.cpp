#include <iostream>
#include <vector>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::swap;


struct GraphNode {
  vector <int> IndexOfNextNode;
  vector <int> Distance;
  int DistanceFromRoot;
  vector<int> WaysToFindDistance;
};

struct TwoNodesAndLeastCommonAncestor {
  int First;
  int Second;
  int LeastCommonAncestor;
};

void Input(vector<GraphNode> *AllGraphNodes, vector<TwoNodesAndLeastCommonAncestor> *NodesToCalculateDistanceLength) {
  int NodesCount;
  cin >> NodesCount;
  //NodesCount=40000;
  
  AllGraphNodes->resize(NodesCount);
  for (int index = 0; index < NodesCount - 1; ++index) {
    int Node;
    int NextNode;
    int Distance;
    cin >> Node >> NextNode >> Distance;
    //Node =  index+1;
    //NextNode = index + 2;
    //Distance=40000;
    
    AllGraphNodes->at(Node - 1).IndexOfNextNode.push_back(NextNode - 1);
    AllGraphNodes->at(Node - 1).Distance.push_back(Distance);

    AllGraphNodes->at(NextNode - 1).IndexOfNextNode.push_back(Node - 1);
    AllGraphNodes->at(NextNode - 1).Distance.push_back(Distance);
    
  }

  int NodesToCalculateCount;
  cin >> NodesToCalculateCount;
  //NodesToCalculateCount=40000;
  
  NodesToCalculateDistanceLength->resize(NodesToCalculateCount);
  for (int index = 0; index < NodesToCalculateCount; ++index) {
    int from;
    int to;
    cin >> from >> to;
    //from = index + 1;
    //to = NodesCount - 2;
    NodesToCalculateDistanceLength->at(index).First = from - 1;
    NodesToCalculateDistanceLength->at(index).Second = to - 1;
    NodesToCalculateDistanceLength->at(index).LeastCommonAncestor = -1;
    
    AllGraphNodes->at(from - 1).WaysToFindDistance.push_back(index);
    AllGraphNodes->at(to - 1).WaysToFindDistance.push_back(index);
  }
}

int DisjointSetUnionGetValue (int NodeIndex, vector<int> *DisjointSetUnion) {
  return NodeIndex == DisjointSetUnion->at(NodeIndex) ? NodeIndex : DisjointSetUnion->at(NodeIndex) = DisjointSetUnionGetValue(DisjointSetUnion->at(NodeIndex), DisjointSetUnion);
}
 
void DisjointSetUnionUnite (int First, int Second, int NewAncestor, vector<int> *DisjointSetUnion, vector<int> *Ancestor) {
  First = DisjointSetUnionGetValue(First, DisjointSetUnion);
  Second = DisjointSetUnionGetValue(Second, DisjointSetUnion);
  if (rand() & 1)  
    swap(First, Second);
  DisjointSetUnion->at(First) = Second;
  Ancestor->at(Second) = NewAncestor;
}

void CalculateDistancesFromCurrentNode(int NodeIndex, vector<TwoNodesAndLeastCommonAncestor> *NodesToCalculateDistanceLength, vector<int> *DisjointSetUnion, const vector<GraphNode> *AllGraphNodes, const vector<int> *Ancestor, const vector<bool> *Visited, vector<int> *DistanceLength) {
  for (int index = 0; index < AllGraphNodes->at(NodeIndex).WaysToFindDistance.size(); ++index) {
    int WayIndex = AllGraphNodes->at(NodeIndex).WaysToFindDistance[index];
    if (NodesToCalculateDistanceLength->at(WayIndex).LeastCommonAncestor == -1) {
      int WayToNode = 0;
      if (NodesToCalculateDistanceLength->at(WayIndex).First == NodeIndex) {
        WayToNode = NodesToCalculateDistanceLength->at(WayIndex).Second;
      } else {
        WayToNode = NodesToCalculateDistanceLength->at(WayIndex).First;
      }
      if (Visited->at(WayToNode)) 
        NodesToCalculateDistanceLength->at(WayIndex).LeastCommonAncestor = Ancestor->at(DisjointSetUnionGetValue(WayToNode, DisjointSetUnion));
    }
  }
}

void dfs (int NodeIndex, vector<TwoNodesAndLeastCommonAncestor> *NodesToCalculateDistanceLength, vector<GraphNode> *AllGraphNodes, vector<int> *DisjointSetUnion, vector<int> *Ancestor, vector<bool> *Visited, vector<int> *DistanceLength) {
  DisjointSetUnion->at(NodeIndex) = NodeIndex;
  Ancestor->at(NodeIndex) = NodeIndex;
  Visited->at(NodeIndex) = true;
  for (int index = 0; index < (int)AllGraphNodes->at(NodeIndex).IndexOfNextNode.size(); ++index) {
    if (!Visited->at(AllGraphNodes->at(NodeIndex).IndexOfNextNode[index])) {
      AllGraphNodes->at(AllGraphNodes->at(NodeIndex).IndexOfNextNode[index]).DistanceFromRoot = AllGraphNodes->at(NodeIndex).DistanceFromRoot + AllGraphNodes->at(NodeIndex).Distance[index];
      dfs(AllGraphNodes->at(NodeIndex).IndexOfNextNode[index], NodesToCalculateDistanceLength, AllGraphNodes, DisjointSetUnion, Ancestor, Visited, DistanceLength);
      DisjointSetUnionUnite (NodeIndex, AllGraphNodes->at(NodeIndex).IndexOfNextNode[index], NodeIndex, DisjointSetUnion, Ancestor);
    }
  }
    
  CalculateDistancesFromCurrentNode(NodeIndex, NodesToCalculateDistanceLength, DisjointSetUnion, AllGraphNodes, Ancestor, Visited, DistanceLength);
}


void CalculateDistancesLengthOfWays(vector<TwoNodesAndLeastCommonAncestor> *NodesToCalculateDistanceLength, vector<GraphNode> *AllGraphNodes, vector<int> *DistanceLength) {
  vector<int> DisjointSetUnion((int)AllGraphNodes->size());
  vector<int> Ancestor((int)AllGraphNodes->size());
  vector<bool> Visited((int)AllGraphNodes->size(), false);
  dfs(0, NodesToCalculateDistanceLength, AllGraphNodes, &DisjointSetUnion, &Ancestor, &Visited, DistanceLength);
  
  for (int index = 0; index < (int)DistanceLength->size(); ++index)
    DistanceLength->at(index) = AllGraphNodes->at(NodesToCalculateDistanceLength->at(index).First).DistanceFromRoot +
                                AllGraphNodes->at(NodesToCalculateDistanceLength->at(index).Second).DistanceFromRoot -
                                2 * AllGraphNodes->at(NodesToCalculateDistanceLength->at(index).LeastCommonAncestor).DistanceFromRoot;
}

int main() {
  vector<GraphNode> AllGraphNodes;
  vector<TwoNodesAndLeastCommonAncestor> NodesToCalculateDistanceLength;
  Input(&AllGraphNodes, &NodesToCalculateDistanceLength);
  
  vector<int> DistanceLength((int)NodesToCalculateDistanceLength.size());
  CalculateDistancesLengthOfWays(&NodesToCalculateDistanceLength, &AllGraphNodes, &DistanceLength);
  for (int index = 0; index < (int)DistanceLength.size(); ++index)
    cout << DistanceLength[index] << endl;
  
  return 0;
}
