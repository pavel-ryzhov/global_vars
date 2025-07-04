#include <fstream>
#include <vector>

using namespace std;

typedef vector<unsigned short>::const_iterator graph_iterator;

vector<unsigned short> node_height, DFS_list, first, segment_tree;
vector<bool> DFS_used;

struct edge
{
    unsigned short index;
    unsigned short length;
};

class graph
{
public:
    edge prev;
    vector<unsigned short> next;
    graph()
    {
        prev.index = 40001;
    }
};

unsigned short nodes_quantity;
vector< vector<edge> > path;
vector<graph> tree;
edge temp_edge;

void buildTree(unsigned short node_index);
void DFS(unsigned short node_index, unsigned short height);
void prepare(unsigned short root);
void buildSegmentTree(unsigned long i, unsigned short left, unsigned short right);
unsigned short findLCA(unsigned short a, unsigned short b);
unsigned short segmentTreeMin(unsigned long i, unsigned short node_left, unsigned short node_right, unsigned short left, unsigned short right);

int main()
{
    unsigned short start, end, length, node_pairs_quantity, lca_node, pair[2], root = 0;
    unsigned long total_length;

    scanf("%hu", &nodes_quantity);
    tree.resize(nodes_quantity);
    path.resize(nodes_quantity);
    for (unsigned short i = 0; i < nodes_quantity - 1; i++)
    {
        scanf("%hu %hu %hu", &start, &end, &length);
        if (i == 0)
            root = start - 1;
        temp_edge.index = end - 1;
        temp_edge.length = length;
        path[start - 1].push_back(temp_edge);
        temp_edge.index = start - 1;
        path[end - 1].push_back(temp_edge);
    }
    buildTree(root);
    path.clear();
    prepare(root);
    scanf("%hu", &node_pairs_quantity);
    for (unsigned short i = 0; i < node_pairs_quantity; i++)
    {
        scanf("%hu %hu", &pair[0], &pair[1]);
        lca_node = findLCA(--pair[0], --pair[1]);
        total_length = 0;
        for (unsigned short j = 0; j <= 1; j++)
            while (pair[j] != lca_node)
            {
                total_length += tree[pair[j]].prev.length;
                pair[j] = tree[pair[j]].prev.index;
            }
        printf("%lu\n", total_length);
    }
}

void buildTree(unsigned short node_index)
{
    for (unsigned short i = 0; i < path[node_index].size(); i++)
        if (tree[node_index].prev.index != path[node_index][i].index && tree[path[node_index][i].index].prev.index == 40001)
        {
            temp_edge.index = node_index;
            temp_edge.length = path[node_index][i].length;
            tree[node_index].next.push_back(path[node_index][i].index);
            tree[path[node_index][i].index].prev = temp_edge;
            buildTree(path[node_index][i].index);
        }
}

void DFS(unsigned short node_index, unsigned short height = 1)
{
    DFS_used[node_index] = true;
    node_height[node_index] = height;
    DFS_list.push_back(node_index);
    for (unsigned short i = 0; i < tree[node_index].next.size(); i++)
        if (!DFS_used[tree[node_index].next[i]])
        {
            DFS(tree[node_index].next[i], height + 1);
            DFS_list.push_back(node_index);
        }
}

void prepare(unsigned short root)
{
    unsigned short nodes_quantity = tree.size(), node;
    unsigned long DFS_list_size;

    node_height.resize(nodes_quantity);
    DFS_list.reserve(nodes_quantity * 2);
    DFS_used.assign(nodes_quantity, false);
    DFS(root);
    DFS_list_size = DFS_list.size();
    segment_tree.assign(DFS_list_size * 4 + 1, 40001);
    buildSegmentTree(1, 0, DFS_list_size - 1);
    first.assign(nodes_quantity, 40001);
    for (unsigned long i = 0; i < DFS_list_size; i++)
    {
        node = DFS_list[i];
        if (first[node] == 40001)
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
