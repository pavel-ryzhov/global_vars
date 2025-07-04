#include <iostream>
#include <vector>


using std::vector;
using std::pair;
using std::cin;
using std::cout;
using std::endl;
using std::swap;


const int MAX_SIZE = 40000;
const int MAX_LOG = 20;

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

void Input (vector<vector<knot> > *children,vector<pair<int,int> > *pairs_of_knots)
{
    int size;
    cin >> size;
    children->resize(size);
    for (int i = 0; i < size - 1; i++)
    {
        int parent;
        int child;
        int distance;
        cin >> parent;
        cin >> child;
        cin >> distance;
        children->at(parent - 1).push_back(knot(child, distance));
    }
    int number_of_pairs;
    cin >> number_of_pairs;
    pairs_of_knots->resize(number_of_pairs);
    for (int i = 0; i < number_of_pairs; i++)
    {
        int a, b;
        cin >> a;
        cin >> b;
        if (a > b) swap(a, b);
        pairs_of_knots->at(i).first = a;
        pairs_of_knots->at(i).second = b;
    }
}

void tree_traverse (vector<int> *order, vector<int> *height, vector<int> *first, vector<vector<knot> > children, 
                    int cur_height, int cur_knot)
{
    order->push_back(cur_knot);
    height->at(cur_knot - 1) = cur_height;
    first->at(cur_knot - 1) = order->size() - 1;
    for (int i = 0; i < children[cur_knot - 1].size(); i++)
    {
        tree_traverse (order, height, first, children, cur_height + 1, children[cur_knot - 1][i].index);
        order->push_back(cur_knot);
    }
}

void fill_sparse_table(vector<vector<int> > *sparse_table, vector<int> order, vector<int> height)
{
    //cout << "10\n";
    int size = (int)order.size();
    sparse_table->resize(size);
    //cout << "size " << size << endl;
    //cout << "11\n";
    for (int j = 0; j < size; j++)
    {
        (*sparse_table)[j].resize(log(size) + 1);
        sparse_table->at(j)[0] = order[j];
    }
    //cout << "12\n";
    for (int i = 1; i < log(size) + 1; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int k = j + (1<<(i - 1));
            if (k >= size)
            {
                //cout << "if" << i << j << "\n";
                (*sparse_table)[j][i] = (*sparse_table)[j][i - 1];
            }
            else
            {
                //cout << "else" << i << j <<"\n";
                if (height[(*sparse_table)[j][i - 1] - 1] > height[(*sparse_table)[k][i - 1] - 1])
                    (*sparse_table)[j][i] = (*sparse_table)[k][i - 1];
                else
                    (*sparse_table)[j][i] = (*sparse_table)[j][i - 1];
               // cout << "else" << i << j <<"\n";
            }
        }
    }

}

int find_lca (vector<vector<int> > sparse_table, vector<int> height, vector<int> first, vector<int> log2, int knot1, int knot2)
{
    //cout << "0\n";
    int left = first[knot1 - 1];
    int right = first[knot2 - 1];
    if (left > right) swap(left, right);
    //cout << "1\n";
    int s = log2[right - left + 1];
    //cout << "s " << s << endl;
    if (height[sparse_table[left][s] - 1] > height[sparse_table[right - (1<<s) + 1][s] - 1])
    {
        //cout << "3\n";
        return sparse_table[right - 1<<s + 1][s];
    }
    else
    {
        //cout << "3\n";
        return sparse_table[left][s];
    }
}

int get_distance (int node1, int node2, vector<vector<knot> > children, vector<int> order, vector<int> first, vector<int> height)
{
    if (node1 == node2) return 0;
    vector<int> v;
    int s = 0;
    int i = first[node2 - 1];
    int j = i;
    while (order[j] != node1)
    {
        j--;
    }
    //cout << "i" << i << endl;
    //cout << "j" << j << endl;
    int l = 0;
    v.resize(i - j + 1);
    v.at(l) = order[j];
    l++;
    j++;
    while (j <= i)
    {
        if (height[order[j]-1] > height[order[j - 1] - 1]) 
        {
            v.at(l) = order[j];
            l++;
        }
        else
        {
            while (v[l] != order[j]) l--;
            l++;
        }
        j++;
    }
    j = 0;
    /*cout << "v:" << endl;
    for (int q=0; q<l;q++)
        cout << v[q] << " ";
    cout << endl;*/
    while (j < l - 1)
    {
        int k = 0;
        while (children[v[j] - 1][k].index != v[j + 1]) k++;
        //cout << "k" << k << endl;
        s = s + children[v[j] - 1][k].distance;
        j++;
    }
    return s;    
}

int main()
{
    vector<vector<knot> > children;
    vector<pair<int, int> > pairs_of_knots;
    Input (&children, &pairs_of_knots);
    int size = (int)children.size();
    vector<int> order;
    vector<int> height;
    vector<int> first;
    first.resize(size);
    height.resize(size);
    tree_traverse(&order, &height, &first, children, 0, 1);
    /*cout << "order:" << endl;
    for (int i = 0; i < order.size(); i++)
    {
        cout << order[i] << " ";
    }
    cout << "\n first:" << endl;
    for (int i = 0; i < first.size(); i++)
    {
        cout << first[i] << " ";
    }
    cout << "\n height:" << endl;
    for (int i = 0; i < height.size(); i++)
    {
        cout << height[i] << " ";
    }
    cout << endl;*/
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
        int lca;
        //cout << "i " << i << endl;
        lca = find_lca(sparse_table, height, first, log2, pairs_of_knots[i].first, pairs_of_knots[i].second);
        //cout << "lca " << lca << endl;
        int d1 = get_distance(lca, pairs_of_knots[i].first, children, order, first, height);
        //cout << "d1 " << d1 << endl;
        int d2 = get_distance(lca, pairs_of_knots[i].second, children, order, first, height);
        cout <<d1 + d2 << endl;
    }

    
    return 0;

}