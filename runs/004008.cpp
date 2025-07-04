#include <iostream>
#include <vector>
#include <list>
#include <cmath>

using std::vector;
using std::list;
using std::pair;
using std::cin;
using std::cout;
using std::endl;
using std::swap;
using std::sqrt;

const int MAX_SIZE = 1000;
const int MAX_PAIRS = 0;
const int MAX_SQRT = 200;
const int MAX_LOG = 20;
const int N_MAX = 10000;

struct node
{
    int index;
    int distance;

    node() : index(0), distance(0) {}
    node(int x, int y) : index(x), distance(y) {}
};

int log (int n) {
	int res = 1;
	while (1<<res < n)  ++res;
	return res;
}

int Input1 (vector<vector<node> > *children,vector<pair<int,int> > *pairs_of_nodes)
{
    int number_of_nodes;
    int root = 1;
    //cin >> number_of_nodes;
    number_of_nodes = MAX_SIZE;
    children->resize(number_of_nodes);
    for (int i = 0; i < number_of_nodes - 1; i++)
    {
        int a, b, c;
        //cin >> a;
        //cin >> b;
        //cin >> c;
        a = i + 1;
        b = a + 1;
        c = 1;
        children->at(a - 1).push_back(node(b, c));
        children->at(b - 1).push_back(node(a, c));
    }
    
    int number_of_pairs;
    //cin >> number_of_pairs;
    number_of_pairs = MAX_PAIRS;
    pairs_of_nodes->resize(number_of_pairs);
    for (int i = 0; i < number_of_pairs; i++)
    {
        //cin >> pairs_of_knots->at(i).first;
        //cin >> pairs_of_knots->at(i).second;
        pairs_of_nodes->at(i).first = i + 1;
        pairs_of_nodes->at(i).second = number_of_nodes - i;
    }
    return root;
}
int Input2 (vector<vector<node> > *children,vector<pair<int,int> > *pairs_of_nodes)
{
    int number_of_nodes;
    int root = 1;
    cin >> number_of_nodes;
    //number_of_nodes = MAX_SIZE;
    children->resize(number_of_nodes);
    list<int> left_end;
    list<int> right_end;
    list<int> dist;
    vector<int> index;
    index.resize(number_of_nodes);
    for (int i = 0; i < number_of_nodes - 1; i++)
    {
        int a, b, c;
        cin >> a;
        cin >> b;
        cin >> c;
        //a=i+1;
        //b=a+1;
        //c=1;
        left_end.push_back(a);
        right_end.push_back(b);
        dist.push_back(c);
        index[a - 1]++;
        index[b - 1]++;
    }

    int number_of_pairs;
    cin >> number_of_pairs;
    //number_of_pairs = MAX_PAIRS;
    pairs_of_nodes->resize(number_of_pairs);
    for (int i = 0; i < number_of_pairs; i++)
    {
        cin >> pairs_of_nodes->at(i).first;
        cin >> pairs_of_nodes->at(i).second;
        //pairs_of_nodes->at(i).first = i + 1;
        //pairs_of_nodes->at(i).second = number_of_nodes - i;
    }
    
    int s = number_of_nodes;
    while (s > 1)
    {
        list<int>::iterator it1 = left_end.begin();
        list<int>::iterator it2 = right_end.begin();
        list<int>::iterator it3 = dist.begin();
        while (it1 != left_end.end())
        {
            if (s > 1)
            {
                if (index[*it1 - 1] == 1)
                {
                    int parent = *it2;
                    int child = *it1;
                    int distance = *it3;
                    children->at(parent - 1).push_back(node(child, distance));
                    it1 = left_end.erase(it1);
                    it2 = right_end.erase(it2);
                    it3 = dist.erase(it3);
                    index[child - 1]--;
                    index[parent - 1]--;
                    s--;
                    if (s == 1) root = parent;  
                }
                else
                {
                    if (index[*it2 - 1] == 1)
                    {
                        int parent = *it1;
                        int child = *it2;
                        int distance = *it3;
                        children->at(parent - 1).push_back(node(child, distance));
                        it1 = left_end.erase(it1);
                        it2 = right_end.erase(it2);
                        it3 = dist.erase(it3);
                        index[child - 1]--;
                        index[parent - 1]--;
                        s--;
                        if (s == 1) root = parent;  
                    }
                    else
                    {
                        ++it1;
                        ++it2;
                        ++it3;
                    }
                }
            }
            else
            {
                ++it1;
                ++it2;
                ++it3;
            }
        }

    }
    return root;
}

void tree_traverse (vector<int> *order, vector<int> *height, vector<int> *first, vector<int> *dist_to_root, 
                    vector<vector<node> > children, int cur_node, int cur_parent, int cur_height, int cur_dist)
{
    order->push_back(cur_node);
    height->at(cur_node - 1) = cur_height;
    first->at(cur_node - 1) = order->size() - 1;
    dist_to_root->at(cur_node - 1) = cur_dist;
    int n = children[cur_node - 1].size();
    for (int i = 0; i < n; i++)
    {
        int child = children[cur_node - 1][i].index;
        int distance = children[cur_node - 1][i].distance;
        //if (child != cur_parent)
        //{
            tree_traverse (order, height, first, dist_to_root, children, child,
                           cur_node, cur_height + 1, cur_dist + distance);
            order->push_back(cur_node);
        //}
    }
}

void fill_sparse_table(vector<vector<int> > *sparse_table, vector<int> a, vector<int> height)
{
    int size = (int)a.size();
    sparse_table->resize(size);
    for (int j = 0; j < size; j++)
    {
        (*sparse_table)[j].resize(log(size) + 1);
        sparse_table->at(j)[0] = a[j];
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

int preprocessing (vector<vector<int> > *sparse_table, vector<vector<vector<int> > > *block_rqm, 
                    vector<int> *block_hash, vector<int> a, vector<int> height)
{
    int size = (int)a.size();
    int size_of_block = (log(size) + 1) / 2;
    int number_of_blocks = size / size_of_block + (size % size_of_block ? 1 : 0);
    vector<int> blocks;
    blocks.resize(number_of_blocks);
    int bl = 0;
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (j == size_of_block)
        {
            j = 0;
            bl++;
        }
        if (j == 0) 
        {
            blocks.at(bl) = a[i];
        }
        else
        {
            if (height[a[i] - 1] < height[blocks[bl] - 1])
                blocks[bl] = a[i];
        }
        j++;
    }
    fill_sparse_table(sparse_table, blocks, height);
    block_hash->resize(number_of_blocks);
    j = 0;
    bl = 0;
    for(int i = 0; i < size; i++)
    {
        if (j == size_of_block)
        {
            j = 0;
            bl++;
        }
        if ((j > 0)&&(height[a[i] - 1] > height[a[i - 1] - 1]))
        {
            (*block_hash)[bl] = (*block_hash)[bl] + (1<<(j - 1));
        }
        j++;
    }
    block_rqm->resize(1<<size_of_block);
    for (int i = 0; i < number_of_blocks; i++)
    {
        int id = (*block_hash)[i];
        if ((*block_rqm)[id].size() == 0)
        {
            (*block_rqm)[id].resize(MAX_LOG);
            for (int l = 0; l < size_of_block; l++)
            {
                (*block_rqm)[id][l].resize(MAX_LOG);
                if (i * size_of_block + l < size) (*block_rqm)[id][l][l] = l;
                for (int r = l + 1; r < size_of_block; r++)
                {
                    if (i * size_of_block + r < size)
                    {
                        if (height[a[i*size_of_block + (*block_rqm)[id][l][r - 1]] - 1] > height[a[i * size_of_block + r] - 1])
                        {
                            (*block_rqm)[id][l][r] = r;
                        }
                        else
                        {
                            (*block_rqm)[id][l][r] = (*block_rqm)[id][l][r - 1];
                        }
                    }
                }
            }
        }
    }
return size_of_block;
}

int find_lca (vector<vector<int> > sparse_table, vector<vector<vector<int> > > block_rqm, vector<int> block_hash, 
              int size_of_block, vector<int> order, vector<int> height, vector<int> first, vector<int> log2, int knot1, int knot2)
{
    int left = first[knot1 - 1];
    int right = first[knot2 - 1];
    if (left == right) return knot1;
    if (left > right) swap(left, right);
    int left_block = left / size_of_block;
    int right_block = right / size_of_block;
    if (left_block == right_block)
    {
        return order[block_rqm[block_hash[left_block]][left % size_of_block][right % size_of_block] + left_block*size_of_block];
    }
    int ans1 = order[block_rqm[block_hash[left_block]][left % size_of_block][size_of_block - 1] + left_block*size_of_block];
    int ans2 = order[block_rqm[block_hash[right_block]][0][right % size_of_block] + right_block*size_of_block];
    int ans;
    if (height[ans1 - 1] > height[ans2 - 1])
        ans = ans2;
    else
        ans = ans1;
    if (left_block < right_block - 1)
    {
		int pw2 = log2[right_block - left_block - 1];
		int ans3 = sparse_table[left_block + 1][pw2];
		int ans4 = sparse_table[right_block - (1<<pw2)][pw2];
        int ans5;
        if (height[ans3 - 1] > height[ans4 - 1])
            ans5 = ans4;
        else
            ans5 = ans3;
        if (height[ans - 1] > height[ans5 - 1])
            ans = ans5;
	}
  return ans;
}

int main()
{
    //int A, B;
    //cin >> A;
   // cin >> B;
    
    vector<vector<node> > children;
    vector<pair<int, int> > pairs_of_knots;
    
    int root = Input2 (&children, &pairs_of_knots);
    
    int size = (int)children.size();
    vector<int> order;
    vector<int> height;
    vector<int> dist_to_root;
    vector<int> first;
    first.resize(size);
    height.resize(size);
    dist_to_root.resize(size);
    
    tree_traverse(&order, &height, &first, &dist_to_root, children, root, 0, 0, 0);
    
   /* cout << "order:\n";
    for (int i = 0; i < order.size(); i++)
        cout << order[i] << " ";
*/
    vector<vector<int> > sparse_table;    
    vector<vector<vector<int> > > block_rqm;
    vector<int> block_hash;
    //fill_sparse_table(&sparse_table, order, height);
    int size_of_block = preprocessing(&sparse_table, &block_rqm, &block_hash, order, height); 
    //cout << "preprocessing\n";
    vector<int> log2;
    int s = order.size() / size_of_block + (order.size() % size_of_block ? 1 : 0);
    log2.resize(s);
    
    for (int i = 0, j = 0; i < s; ++i) {
		if (1<<(j + 1) <= i)  ++j;
		log2[i] = j;
	}
    for (int i = 0; i < pairs_of_knots.size(); i++)
    {
        int lca = find_lca(sparse_table, block_rqm, block_hash, size_of_block, order, height, first, log2, pairs_of_knots[i].first, pairs_of_knots[i].second);
        int d = dist_to_root[pairs_of_knots[i].first - 1] + dist_to_root[pairs_of_knots[i].second - 1] - 2 * dist_to_root[lca - 1];
        cout << d << endl;
    }
  
    
    //cout << A+B;
    return 0;

}