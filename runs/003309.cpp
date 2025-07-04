#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// CONSTANTS ===========================================================================================================

const int BAD_NODE = -1;
const int UNSET_VALUE = -1;

// STRUCTs and CLASSES =================================================================================================

struct Node {
    int parent;
    int distance_to_parent;
    vector<int> childs;
};

struct Link {
    int link;
    int length;
};

typedef vector<Node> Tree;

class DistanceFinder {
    const int tree_size;
    vector<int> distances_to_root;
    vector<int> first;
    vector<int> order;
    vector<int> order_tree;

    void BuildOrderTree(int root, int left, int right);
    void FillOrderAndDistances(const Tree& tree, int subtree_root);
    int FindCommonParentInOrderVector(int piece_in_tree, int piece_left, int piece_right, int left, int right);

public:
    DistanceFinder(const Tree& tree);
    int Distance(int a, int b);
};

DistanceFinder::DistanceFinder(const Tree& tree):
    tree_size(tree.size()),
    distances_to_root(tree_size)
{
    order.reserve(tree_size * 2);
    distances_to_root[0] = 0;
    FillOrderAndDistances(tree, 0);

    int order_size = order.size();
    first.assign(tree_size, UNSET_VALUE);
    for (int i = 0; i < order_size; ++i) {
        if (first[order[i]] == UNSET_VALUE) {
            first[order[i]] = i;
        }
    }

    order_tree.assign(order_size * 4 + 1, UNSET_VALUE);
    BuildOrderTree(1, 0, order_size - 1);
}

int DistanceFinder::Distance(int a, int b) {
    int left = first[a];
    int right = first[b];
    if (left > right) {
        std::swap(left, right);
    }
    int common_parent = FindCommonParentInOrderVector(1, 0, order.size() - 1, left, right);
    return distances_to_root[a] + distances_to_root[b] - 2 * distances_to_root[common_parent];
}

void DistanceFinder::BuildOrderTree(int root, int left, int right) {
    if (left == right)
        order_tree[root] = order[left];
    else
    {
        int middle = (left + right) / 2;
        BuildOrderTree(root * 2, left, middle);
        BuildOrderTree(root * 2 + 1, middle + 1, right);
        order_tree[root] = (distances_to_root[order_tree[root * 2]] < distances_to_root[order_tree[root * 2 + 1]]) ?
            order_tree[root * 2] : order_tree[root * 2 + 1];
    }
}

void DistanceFinder::FillOrderAndDistances(const Tree& tree, int subtree_root) {
    order.push_back(subtree_root);
    for (int i = 0; i < tree[subtree_root].childs.size(); ++i) {
        int child = tree[subtree_root].childs[i];
        distances_to_root[child] = distances_to_root[subtree_root] + tree[child].distance_to_parent;
        FillOrderAndDistances(tree, child);
        order.push_back(subtree_root);
    }
}

int DistanceFinder::FindCommonParentInOrderVector(int piece_in_tree, int piece_left, int piece_right, int left, int right) {
    if (piece_left == left && piece_right == right)
        return order_tree[piece_in_tree];
    int piece_middle = (piece_left + piece_right) / 2;
    if (right <= piece_middle) {
        return FindCommonParentInOrderVector(piece_in_tree * 2, piece_left, piece_middle, left, right);
    }
    else if (left > piece_middle) {
        return FindCommonParentInOrderVector(piece_in_tree * 2 + 1, piece_middle + 1, piece_right, left, right);
    }
    else {
        int ans1 = FindCommonParentInOrderVector(piece_in_tree * 2, piece_left, piece_middle, left, piece_middle);
        int ans2 = FindCommonParentInOrderVector(piece_in_tree * 2 + 1, piece_middle + 1, piece_right,
            piece_middle + 1, right);
        return distances_to_root[ans1] < distances_to_root[ans2] ? ans1 : ans2;
    }
}

// FUNCTIONS ===========================================================================================================

void MakeSubTree(Tree* tree, const vector<vector<Link> > &links, int node) {
    for (vector<Link>::const_iterator link = links[node].begin(); link != links[node].end(); ++link) {
        if (link->link != (*tree)[node].parent) {
            (*tree)[node].childs.push_back(link->link);
            (*tree)[link->link].parent = node;
            (*tree)[link->link].distance_to_parent = link->length;

            MakeSubTree(tree, links, link->link);
        }
    }
}

void MakeTree(Tree* tree, const vector<vector<Link> > &links) {
    tree->resize(links.size());
    (*tree)[0].parent = BAD_NODE;
    (*tree)[0].distance_to_parent = 0;

    MakeSubTree(tree, links, 0);
}

void FillTree(Tree *tree) {
    int tree_size;
    cin >> tree_size;

    vector<vector<Link> > links(tree_size);
    for (int i = 0; i < tree_size - 1; ++i) {
        int first_node, second_node, edge_length;
        cin >> first_node >> second_node >> edge_length;
        --first_node;
        --second_node;

        Link first_link, second_link;
        first_link.link = second_node;
        second_link.link = first_node;
        second_link.length = first_link.length = edge_length;
        links[first_node].push_back(first_link);
        links[second_node].push_back(second_link);
    }
    MakeTree(tree, links);
}

long long SlowGetDistance(const Tree &tree, int first_node, int second_node) {
    vector<long long> distances_to_first(tree.size(), UNSET_VALUE);
    distances_to_first[first_node] = 0;
    int node = first_node;
    while (tree[node].parent != BAD_NODE) {
        distances_to_first[tree[node].parent] = distances_to_first[node] + tree[node].distance_to_parent;
        node = tree[node].parent;
    }

    long long distance_to_second = 0;
    node = second_node;
    while (distances_to_first[node] == UNSET_VALUE && tree[node].parent != BAD_NODE) {
        distance_to_second += tree[node].distance_to_parent;
        node = tree[node].parent;
    }

    return distances_to_first[node] + distance_to_second;
}

void SlowProc() {
    Tree tree;
    FillTree(&tree);
    int num_of_questions;
    cin >> num_of_questions;
    for (int i = 0; i < num_of_questions; ++i) {
        int node1, node2;
        cin >> node1 >> node2;
        --node1;
        --node2;
        cout << SlowGetDistance(tree, node1, node2) << endl;
    }
}

void Proc() {
    Tree tree;
    FillTree(&tree);
    DistanceFinder distance_finder(tree);

    int num_of_questions;
    cin >> num_of_questions;
    for (int i = 0; i < num_of_questions; ++i) {
        int node1, node2;
        cin >> node1 >> node2;
        //cerr << i << " " << node1 << " " << node2 <<endl;
        --node1;
        --node2;
        cout << distance_finder.Distance(node1, node2) << "\n";
    }
    cout.flush();
    //cerr << "Proc OK" << endl;
}

int Test() {
    Tree tree;
    FillTree(&tree);
    DistanceFinder distance_finder(tree);
    
    int num_of_questions;
    cin >> num_of_questions;
    for (int i = 0; i < num_of_questions; ++i) {
        int node1, node2;
        cin >> node1 >> node2;
        //cout << node1 << node2 << endl;
        --node1;
        --node2;
        int dist1 = distance_finder.Distance(node1, node2);
        int dist2 = SlowGetDistance(tree, node1, node2);
        if (dist1 != dist2) {
            cout << dist1 << " " << dist2 << endl;
            cerr << "ERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR" << endl;
            return 1;
        }
        //cout << dist1 << " " << dist2 << endl;
    }
    return 0;
}

int main(int argc, char** argv) {
    //cout<< Test();
    //return Test();
    Proc();
    return 0;
}
