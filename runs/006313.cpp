#include <vector>
#include <iostream>

struct Edge {
    Edge(int to_, int length_) : to(to_), length(length_) {};

    int to, length;
};

typedef std::vector< std::vector<Edge> > EdgeList;

class Tree {
  public:
    Tree(const EdgeList& edgeList);

    const std::vector<int>& childs(int vertex) const;
    int parentEdgeLength(int vertex) const;
    int root() const;
    size_t size() const;
  private:
    std::vector< std::vector<int> > childs_;
    std::vector<int> edgeLengths_;

    void buildSubTree(const EdgeList& edgeList, int subtreeRoot, int parent);
};

Tree::Tree(const EdgeList& edgeList)
     : childs_(edgeList.size()), edgeLengths_(edgeList.size()) {
    buildSubTree(edgeList, root(), -1);
}

void Tree::buildSubTree(const EdgeList& edgeList, int subtreeRoot, int parent) {
    for(size_t neighbour = 0; neighbour < edgeList[subtreeRoot].size(); ++neighbour) {
        Edge adjacentEdge = edgeList[subtreeRoot][neighbour];
        if(adjacentEdge.to != parent) {
            childs_[subtreeRoot].push_back(adjacentEdge.to);
            edgeLengths_[adjacentEdge.to] = adjacentEdge.length;

            buildSubTree(edgeList, adjacentEdge.to, subtreeRoot);
        }
    }
}

int Tree::parentEdgeLength(int vertex) const {
    return edgeLengths_[vertex];
}

int Tree::root() const {
    return 0;
}

const std::vector<int>& Tree::childs(int vertex) const {
    return childs_[vertex];
}

size_t Tree::size() const {
    return childs_.size();
}

class LCATree {
  public:
    LCATree(const Tree& tree);
    int findLowestCommonAncestor(int firstVertex, int secondVertex) const;
  private:
    std::vector< std::vector<int> > links_;
    std::vector<int> depth_;

    void buildLinks(const Tree& tree, int vertex);
    int findAncestorAtDepth(int vertex, int depth) const;
};

LCATree::LCATree(const Tree& tree)
    : links_(tree.size()), depth_(tree.size()) {
    buildLinks(tree, tree.root());
}

void LCATree::buildLinks(const Tree& tree, int vertex) {
    if(vertex != tree.root()) {
        for(size_t stepSize = 0, ancestor = links_[vertex][0];
            stepSize < links_[ancestor].size(); ++stepSize) {
            links_[vertex].push_back(links_[ancestor][stepSize]);
            ancestor = links_[ancestor][stepSize];
        }
    }

    const std::vector<int>& childs = tree.childs(vertex);

    for(size_t childIndex = 0; childIndex < childs.size(); ++childIndex) {
        int child = childs[childIndex];
        links_[child].push_back(vertex);
        depth_[child] = depth_[vertex] + 1;

        buildLinks(tree, child);
    }
}

int LCATree::findLowestCommonAncestor(int firstVertex, int secondVertex) const {
    if(depth_[firstVertex] > depth_[secondVertex]) {
        firstVertex = findAncestorAtDepth(firstVertex, depth_[secondVertex]);
    } else {
        secondVertex = findAncestorAtDepth(secondVertex, depth_[firstVertex]);
    }

    if(secondVertex == firstVertex) {
        return firstVertex;
    }

    for(int stepSize = links_[firstVertex].size() - 1; stepSize >= 0; --stepSize) {
        if(stepSize < links_[firstVertex].size() &&
           links_[firstVertex][stepSize] != links_[secondVertex][stepSize]) {
            firstVertex = links_[firstVertex][stepSize];
            secondVertex = links_[secondVertex][stepSize];
        }
    }

    return links_[firstVertex][0];
}

int LCATree::findAncestorAtDepth(int vertex, int depth) const {
    for(int stepSize = links_[vertex].size() - 1; depth_[vertex] != depth; --stepSize) {
        if(stepSize < links_[vertex].size()) {
            int ancestor = links_[vertex][stepSize];
            if(depth_[ancestor] >= depth) {
                vertex = ancestor;
            }
        }
    }

    return vertex;
}

class TreeDistance {
  public:
    TreeDistance(const Tree& tree);
    int distance(int firstVertex, int secondVertex) const;
    int distanceFromRoot(int vertex) const;
  private:
    LCATree lcaTree_;
    std::vector<int> distance_;

    void calculateDistanceFromRoot(const Tree& tree, int subtreeRoot);
};

TreeDistance::TreeDistance(const Tree& tree) : lcaTree_(tree), distance_(tree.size()) {
    calculateDistanceFromRoot(tree, tree.root());
};

int TreeDistance::distanceFromRoot(int vertex) const {
    return distance_[vertex];
}

int TreeDistance::distance(int firstVertex, int secondVertex) const {
    int lca = lcaTree_.findLowestCommonAncestor(firstVertex, secondVertex);

    return (distanceFromRoot(firstVertex) - distanceFromRoot(lca)) +
           (distanceFromRoot(secondVertex) - distanceFromRoot(lca));
}

void TreeDistance::calculateDistanceFromRoot(const Tree& tree, int subtreeRoot) {
    const std::vector<int>& childs = tree.childs(subtreeRoot);

    for(size_t childIndex = 0; childIndex < childs.size(); ++childIndex) {
        int child = childs[childIndex];

        distance_[child] = distance_[subtreeRoot] + tree.parentEdgeLength(child);
        calculateDistanceFromRoot(tree, child);
    }
}

EdgeList ReadTree() {
    int treeSize;
    std::cin >> treeSize;

    EdgeList edgeList(treeSize);

    for(int i = 1; i < treeSize; ++i) {
        int firstVertex, secondVertex, length;
        std::cin >> firstVertex >> secondVertex >> length;

        edgeList[firstVertex - 1].push_back(Edge(secondVertex - 1, length));
        edgeList[secondVertex - 1].push_back(Edge(firstVertex - 1, length));
    }

    return edgeList;
}

void AnswerQueries(const TreeDistance& treeDistance) {
    int numberOfQueries;

    std::cin >> numberOfQueries;

    for(int i = 0; i < numberOfQueries; ++i) {
        int firstVertex, secondVertex;

        std::cin >> firstVertex >> secondVertex;

        std::cout << treeDistance.distance(firstVertex - 1, secondVertex - 1) << std::endl;
    }
}

int main() {
    EdgeList edgeList = ReadTree();
    Tree tree(edgeList);
    TreeDistance distanceTree(tree);

    AnswerQueries(distanceTree);

    return 0;
}
