#include <iostream>
#include <vector>

using std::vector;
using std::pair;
using std::cin;
using std::cout;
using std::endl;
using std::swap;

struct knot
{
    int index;
    int distance;

    knot() : index(0), distance(0) {}
    knot(int x, int y) : index(x), distance(y) {}
};

int log (int n) {
	int res = 1;
	while (1<<res < n)  ++res;
	return res;
}

int Input (vector<vector<knot> > *children,vector<pair<int,int> > *pairs_of_knots)
{
    int number_of_nodes;
    int root = 1;
    cin >> number_of_nodes;
    children->resize(number_of_nodes);
    for (int i = 0; i < number_of_nodes - 1; i++)
    {
        int a, b, c;
        cin >> a;
        cin >> b;
        cin >> c;
        children->at(a - 1).push_back(knot(b, c));
        children->at(b - 1).push_back(knot(a, c));
    }
    
    int number_of_pairs;
    cin >> number_of_pairs;
    pairs_of_knots->resize(number_of_pairs);
    for (int i = 0; i < number_of_pairs; i++)
    {
        cin >> pairs_of_knots->at(i).first;
        cin >> pairs_of_knots->at(i).second;
    }
    return root;
}

void tree_traverse (vector<int> *order, vector<int> *height, vector<int> *first, vector<int> *dist_to_root, 
                    vector<vector<knot> > children, int cur_knot, int cur_parent, int cur_height, int cur_dist)
{
    order->push_back(cur_knot);
    height->at(cur_knot - 1) = cur_height;
    first->at(cur_knot - 1) = order->size() - 1;
    dist_to_root->at(cur_knot - 1) = cur_dist;
    for (int i = 0; i < children[cur_knot - 1].size(); i++)
    {
        if (children[cur_knot - 1][i].index != cur_parent)
        {
            tree_traverse (order, height, first, dist_to_root, children, children[cur_knot - 1][i].index,
                           cur_knot, cur_height + 1, cur_dist + children[cur_knot - 1][i].distance);
            order->push_back(cur_knot);
        }
    }
}

void fill_sparse_table(vector<vector<int> > *sparse_table, vector<int> order, vector<int> height)
{
    int size = (int)order.size();
    sparse_table->resize(size);
    for (int j = 0; j < size; j++)
    {
        (*sparse_table)[j].resize(log(size) + 1);
        sparse_table->at(j)[0] = order[j];
    }
    for (int i = 1; i < log(size) + 1; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int k = j + (1<<(i - 1));
            if (k >= size)
            {
                (*sparse_table)[j][i] = (*sparse_table)[j][i - 1];
            }
            else
            {
                if (height[(*sparse_table)[j][i - 1] - 1] > height[(*sparse_table)[k][i - 1] - 1])
                    (*sparse_table)[j][i] = (*sparse_table)[k][i - 1];
                else
                    (*sparse_table)[j][i] = (*sparse_table)[j][i - 1];
            }
        }
    }

}

int find_lca (vector<vector<int> > sparse_table, vector<int> height, vector<int> first, vector<int> log2, int knot1, int knot2)
{
    int left = first[knot1 - 1];
    int right = first[knot2 - 1];
    if (left == right) return knot1;
    if (left > right) swap(left, right);
    int s = log2[right - left + 1];
    if (height[sparse_table[left][s] - 1] > height[sparse_table[right - (1<<s) + 1][s] - 1])
    {
        return sparse_table[right - (1<<s) + 1][s];
    }
    else
    {
        return sparse_table[left][s];
    }
}

int main()
{
    vector<vector<knot> > children;
    vector<pair<int, int> > pairs_of_knots;
    int root = Input (&children, &pairs_of_knots);
    int size = (int)children.size();
    vector<int> order;
    vector<int> height;
    vector<int> dist_to_root;
    vector<int> first;
    first.resize(size);
    height.resize(size);
    dist_to_root.resize(size);
    tree_traverse(&order, &height, &first, &dist_to_root, children, root, 0, 0, 0);
    vector<vector<int> > sparse_table;    
    fill_sparse_table(&sparse_table, order, height);
    
    vector<int> log2;
    log2.resize(order.size());
    for (int i=0, j=0; i<order.size(); ++i) {
		if (1<<(j+1) <= i)  ++j;
		log2[i] = j;
	}

    for (int i = 0; i < pairs_of_knots.size(); i++)
    {
        int lca = find_lca(sparse_table, height, first, log2, pairs_of_knots[i].first, pairs_of_knots[i].second);
        int d = dist_to_root[pairs_of_knots[i].first - 1] + dist_to_root[pairs_of_knots[i].second - 1] - 2 * dist_to_root[lca - 1];
        cout << d << endl;
    }

    return 0;

}