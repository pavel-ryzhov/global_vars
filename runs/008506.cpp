#include <fstream>
#include <vector>

using namespace std;

typedef vector< vector<int> > graph;
typedef vector<int>::const_iterator graph_iterator;

vector<int> node_height, DFS_list, first, segment_tree;
vector<bool> DFS_used;

class edge
{
public:
    long prev_index;
    unsigned short length;
    edge()
    {
        prev_index = -1;
        length = 0;
    }
};

void DFS(const graph &tree, unsigned short node_index, unsigned short height);
void prepare(const graph &tree, unsigned short root);
void buildSegmentTree(unsigned long i, unsigned short left, unsigned short right);
unsigned short findLCA(unsigned short a, unsigned short b);
unsigned short segmentTreeMin(unsigned long i, unsigned short node_left, unsigned short node_right, unsigned short left, unsigned short right);

int main()
{
    graph tree;
    vector<edge> path;
    unsigned short nodes_quantity, start, end, length, node_pairs_quantity, lca_node, pair[2], root = 0;
    unsigned long total_length;

    scanf("%hu", &nodes_quantity);
    tree.resize(nodes_quantity);
    path.resize(nodes_quantity);
    for (unsigned short i = 0; i < nodes_quantity - 1; i++)
    {
        scanf("%hu %hu %hu", &start, &end, &length);
        if (path[start - 1].prev_index == -1 && i != 0)
            swap(start, end);
        if (i == 0)
            root = start - 1;
        tree[start - 1].push_back(end - 1);
        path[end - 1].prev_index = start - 1;
        path[end - 1].length = length;
    }
    prepare(tree, root);
    scanf("%hu", &node_pairs_quantity);
    for (unsigned short i = 0; i < node_pairs_quantity; i++)
    {
        scanf("%hu %hu", &pair[0], &pair[1]);
        lca_node = findLCA(--pair[0], --pair[1]);
        total_length = 0;
        for (unsigned short j = 0; j <= 1; j++)
            while (pair[j] != lca_node)
            {
                total_length += path[pair[j]].length;
                pair[j] = path[pair[j]].prev_index;
            }
        printf("%lu\n", total_length);
    }
}

void DFS(const graph &tree, unsigned short node_index, unsigned short height = 1)
{
    DFS_used[node_index] = true;
    node_height[node_index] = height;
    DFS_list.push_back(node_index);
    for (graph_iterator i = tree[node_index].begin(); i != tree[node_index].end(); i++)
        if (!DFS_used[*i])
        {
            DFS(tree, *i, height + 1);
            DFS_list.push_back(node_index);
        }
}

void prepare(const graph &tree, unsigned short root)
{
    unsigned short nodes_quantity = tree.size(), node;
    unsigned long DFS_list_size;

    node_height.resize(nodes_quantity);
    DFS_list.reserve(nodes_quantity * 2);
    DFS_used.assign(nodes_quantity, false);
    DFS(tree, root);
    DFS_list_size = DFS_list.size();
    segment_tree.assign(DFS_list_size * 4, -1);
    buildSegmentTree(1, 0, DFS_list_size - 1);
    first.assign(nodes_quantity, -1);
    for (unsigned long i = 0; i < DFS_list_size; i++)
    {
        node = DFS_list[i];
        if (first[node] == -1)
            first[node] = i;
    }
}

void buildSegmentTree(unsigned long i, unsigned short left, unsigned short right)
{
    if (left == right)
        segment_tree[i] = DFS_list[left];
    else
    {
        int mid = (left + right) >> 1;
        buildSegmentTree(i + i, left, mid);
        buildSegmentTree(i + i + 1, mid + 1, right);
        if (node_height[segment_tree[i + i]] < node_height[segment_tree[i + i + 1]])
            segment_tree[i] = segment_tree[i + i];
        else
            segment_tree[i] = segment_tree[i + i + 1];
    }
}

unsigned short findLCA(unsigned short a, unsigned short b)
{
    int left = first[a], right = first[b];
    if (left > right)
        swap(left, right);
    return segmentTreeMin(1, 0, DFS_list.size() - 1, left, right);
}

unsigned short segmentTreeMin(unsigned long i, unsigned short node_left, unsigned short node_right, unsigned short left, unsigned short right)
{
    if (node_left == left && node_right == right)
        return segment_tree[i];
    int mid = (node_left + node_right) >> 1;
    if (right <= mid)
        return segmentTreeMin(i + i, node_left, mid, left, right);
    if (left > mid)
        return segmentTreeMin(i + i + 1, mid + 1, node_right, left, right);
    int ans1 = segmentTreeMin(i + i, node_left, mid, left, mid);
    int ans2 = segmentTreeMin(i + i + 1, mid + 1, node_right, mid + 1, right);
    return node_height[ans1] < node_height[ans2] ? ans1 : ans2;
}
