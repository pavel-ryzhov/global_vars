#include <vector>
#include <list>
#include <stack>
#include <iostream>

using std::vector;
using std::list;
using std::stack;
using std::cin;
using std::cout;
using std::endl;

//Required bit magic

typedef unsigned int uint;

uint lsb(uint k)
//Returns an integer where only the least significant set bit of k is set
{
    return k & -k;
};

uint msb(uint k)
//Returns an integer where only the most significant set bit of k is set
{
    if (k == 0)
        return 0;

    int s = 8*sizeof(uint) >> 1;
    uint l = 1, h = 1 << s;
    do {
        if (k >= h)
            l = h;
        else
            h = l;
        s >>= 1;
        h <<= s;
    } while (s);
    return l;
};

uint bintree_compute(uint x, uint y)
//Returns an integer from the segment [x, y] with maximum number of trailing zero bits
{
    if (y < x) {
        uint tmp = x;
        x = y;
        y = tmp; 
    }
    return y & (1 + ~msb(y & -x));
}

class LCATree
{
public:
    struct Node;
    struct Edge;
    typedef vector<Node>::iterator node_iterator;
private:
    struct LCAInfo
    {
        uint order;
        uint exp_height;
        uint max_in_subtree;
        uint run_tail;
        uint run_head;
        uint ancestor_mask;
    };
    vector<Node> nodes_;
    vector<node_iterator> dfs_order_;
    uint enter_node(uint run_exp_height, node_iterator node);
public:
    struct Node
    {
        list<Edge> out_edges;
        node_iterator parent;
        int dist_from_root;
        bool visited;
        LCAInfo data;
        Node();
    };
    struct Edge
    {
        node_iterator endpoint;
        int length;
        Edge(node_iterator to, int length);
    };

    LCATree(int size);
    ~LCATree();

    void AddEdge(node_iterator node1, node_iterator node2, int length);
    
    node_iterator begin();
    node_iterator end();
    node_iterator node(int index);

    void Preprocess();
    node_iterator LCA(node_iterator node1, node_iterator node2);
    int Distance(node_iterator node1, node_iterator node2);

    void Print_Info();
};

LCATree::LCATree(int size): nodes_(size), dfs_order_(size)
{}

LCATree::~LCATree()
{}

LCATree::Node::Node():visited(false)
{}

LCATree::Edge::Edge(node_iterator to, int length): endpoint(to), length(length)
{}

void LCATree::AddEdge(LCATree::node_iterator node1, LCATree::node_iterator node2, int length)
{
    node1->out_edges.push_back(Edge(node2, length));
    node2->out_edges.push_back(Edge(node1, length));
}
    
LCATree::node_iterator LCATree::begin()
{
    return nodes_.begin();
}

LCATree::node_iterator LCATree::end()
{
    return nodes_.end();
}

LCATree::node_iterator LCATree::node(int index)
{
    return nodes_.begin() + index - 1;
}

//The following tho methods implement Schieber-Vishkin algorithm for LCA finding
//see D.Gusfield, "Algorithms on Strings, Trees and Sequences ..." for a detailed explanation

void LCATree::Preprocess()
{
    stack<node_iterator> stack;
    node_iterator node = begin();
    node->dist_from_root = 0;
    stack.push(node);
    uint index = 1;
    while (!stack.empty()) {
        node = stack.top();
        if (node->visited) {
            //Bottom-up traversal
            //Computing run_tail's
            stack.pop();
            uint max = node->data.order;
            for (list<Edge>::iterator edge = node->out_edges.begin(); edge != node->out_edges.end(); edge++) {
                node_iterator child = edge->endpoint;
                if (child->data.order > max)
                    max = child->data.max_in_subtree;
            }
            node->data.max_in_subtree = max;
            node->data.run_tail = bintree_compute(node->data.order, max);
        }
        else {
            //Top-down traversal
            //Transformation into directed tree
            //Computing DFS order and distances from the root
            node->visited = true;
            node->data.order = index;
            node->data.exp_height = lsb(index);
            dfs_order_[index - 1] = node;
            index++;
            for (list<Edge>::iterator edge = node->out_edges.begin(); edge != node->out_edges.end(); edge++) {
                node_iterator child = edge->endpoint;
                if (child->visited) {
                    //Remove edge going to parent
                    edge = node->out_edges.erase(edge);
                    edge--;
                }
                else {
                    child->parent = node;
                    child->dist_from_root = node->dist_from_root + edge->length;
                    stack.push(child);
                }
            }
        }
    }
    node = nodes_.begin();
    node->data.ancestor_mask = lsb(node->data.run_tail);
    stack.push(node);
    while (!stack.empty()) {
    //Second top-down traversal
    //Computing run_head's and ancestor_mask's
        node = stack.top();
        stack.pop();
        for (list<Edge>::iterator edge = node->out_edges.begin(); edge != node->out_edges.end(); edge++) {
            node_iterator child = edge->endpoint;
            child->data.ancestor_mask = node->data.ancestor_mask | lsb(child->data.run_tail);
            if (child->data.run_tail != node->data.run_tail) {
                dfs_order_[child->data.run_tail - 1]->data.run_head = child->data.order;
            }
            stack.push(child);
        }
    }
    dfs_order_[nodes_.begin()->data.run_tail - 1]->data.run_head = 1;
}

uint LCATree::enter_node(uint run_exp_height, node_iterator node)
{
    if (run_exp_height == lsb(node->data.ancestor_mask)) {
        return node->data.order;
    }
    else {
        uint k = msb(node->data.ancestor_mask & (run_exp_height - 1));
        uint run = node->data.run_tail & ~(k - 1) | k;
        uint sub = dfs_order_[run - 1]->data.run_head;
        return dfs_order_[sub - 1]->parent->data.order;
    }
}

LCATree::node_iterator LCATree::LCA(LCATree::node_iterator node1, LCATree::node_iterator node2)
{
    uint bintree_lca = bintree_compute(node1->data.run_tail, node2->data.run_tail);
    uint run_exp_height = lsb(~(lsb(bintree_lca) - 1) & node1->data.ancestor_mask & node2->data.ancestor_mask);
    uint x = enter_node(run_exp_height, node1);
    uint y = enter_node(run_exp_height, node2);
    uint lca_index = (x < y) ? x : y;
    return dfs_order_[lca_index-1];
}

int LCATree::Distance(LCATree::node_iterator node1, LCATree::node_iterator node2)
{
    node_iterator lca = LCA(node1, node2);
    return node1->dist_from_root + node2->dist_from_root - 2*lca->dist_from_root;
}

int main()
{
    int n;
    cin >> n;
    LCATree tree(n);

    int from, to, dist;
    for (int i = 0; i < n-1; i++) {
        cin >> from >> to >> dist;
        tree.AddEdge(tree.node(from), tree.node(to), dist);
    }

    tree.Preprocess();

    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> from >> to;
        cout << tree.Distance(tree.node(from), tree.node(to)) << endl;
    }
}

