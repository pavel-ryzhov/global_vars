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

int Input (vector<vector<knot> > *children,vector<pair<int,int> > *pairs_of_knots)
{
    int number_of_nodes;
    int root = 1;
    cin >> number_of_nodes;
    //number_of_nodes = 30;
    children->resize(number_of_nodes);
    vector<int> left_end;
    vector<int> right_end;
    vector<int> dist;
    left_end.resize(number_of_nodes - 1);
    right_end.resize(number_of_nodes - 1);
    dist.resize(number_of_nodes - 1);
    for (int i = 0; i < number_of_nodes - 1; i++)
    {
        cin >> left_end.at(i);
        cin >> right_end.at(i);
        cin >> dist.at(i);
    }
    /*
left_end.at(0)=2;
    right_end.at(0)=9;
    dist.at(0)=8;
left_end.at(1)=3;
    right_end.at(1)=7;
    dist.at(1)=7;
left_end.at(2)=4;
    right_end.at(2)=9;
    dist.at(2)=3;
 left_end.at(3)=5;
    right_end.at(3)=23;
    dist.at(3)=19;
left_end.at(4)=6;
    right_end.at(4)=3;
    dist.at(4)=19;
left_end.at(5)=7;
    right_end.at(5)=9;
    dist.at(5)=8;
 left_end.at(6)=8;
    right_end.at(6)=12;
    dist.at(6)=28;
left_end.at(7)=9;
    right_end.at(7)=1;
    dist.at(7)=21;
left_end.at(8)=10;
    right_end.at(8)=15;
    dist.at(8)=24;
 left_end.at(9)=11;
    right_end.at(9)=7;
    dist.at(9)=6;
left_end.at(10)=12;
    right_end.at(10)=27;
    dist.at(10)=19;
left_end.at(11)=13;
    right_end.at(11)=2;
    dist.at(11)=0;
left_end.at(12)=14;
    right_end.at(12)=17;
    dist.at(12)=18;
left_end.at(13)=15;
    right_end.at(13)=4;
    dist.at(13)=6;
left_end.at(14)=16;
    right_end.at(14)=15;
    dist.at(14)=25;
 left_end.at(15)=17;
    right_end.at(15)=18;
    dist.at(15)=23;
left_end.at(16)=18;
    right_end.at(16)=15;
    dist.at(16)=23;
left_end.at(17)=19;
    right_end.at(17)=23;
    dist.at(17)=24;
 left_end.at(18)=20;
    right_end.at(18)=6;
    dist.at(18)=23;
left_end.at(19)=21;
    right_end.at(19)=17;
    dist.at(19)=27;
left_end.at(20)=22;
    right_end.at(20)=3;
    dist.at(20)=14;
 left_end.at(21)=23;
    right_end.at(21)=4;
    dist.at(21)=8;
left_end.at(22)=24;
    right_end.at(22)=18;
    dist.at(22)=1;
left_end.at(23)=25;
    right_end.at(23)=7;
    dist.at(23)=15;
left_end.at(24)=26;
    right_end.at(24)=15;
    dist.at(24)=9;
left_end.at(25)=27;
    right_end.at(25)=16;
    dist.at(25)=24;
left_end.at(26)=28;
    right_end.at(26)=27;
    dist.at(26)=14;
 left_end.at(27)=29;
    right_end.at(27)=25;
    dist.at(27)=25;
left_end.at(28)=30;
    right_end.at(28)=29;
    dist.at(28)=12;
*/
    int number_of_pairs;
    cin >> number_of_pairs;
    //number_of_pairs = 27;
    pairs_of_knots->resize(number_of_pairs);
    for (int i = 0; i < number_of_pairs; i++)
    {
        cin >> pairs_of_knots->at(i).first;
        cin >> pairs_of_knots->at(i).second;
    }
    /*
pairs_of_knots->at(0).first=1;
pairs_of_knots->at(0).second=20;
pairs_of_knots->at(1).first=8;
pairs_of_knots->at(1).second=11;
pairs_of_knots->at(2).first=20;
pairs_of_knots->at(2).second=19;
pairs_of_knots->at(3).first=5;
pairs_of_knots->at(3).second=27;
pairs_of_knots->at(4).first=5;
pairs_of_knots->at(4).second=14;
pairs_of_knots->at(5).first=14;
pairs_of_knots->at(5).second=20;
pairs_of_knots->at(6).first=4;
pairs_of_knots->at(6).second=25;
pairs_of_knots->at(7).first=1;
pairs_of_knots->at(7).second=2;
pairs_of_knots->at(8).first=23;
pairs_of_knots->at(8).second=25;
pairs_of_knots->at(9).first=3;
pairs_of_knots->at(9).second=27;
pairs_of_knots->at(10).first=14;
pairs_of_knots->at(10).second=20;
pairs_of_knots->at(11).first=22;
pairs_of_knots->at(11).second=21;
pairs_of_knots->at(12).first=5;
pairs_of_knots->at(12).second=6;
pairs_of_knots->at(13).first=23;
pairs_of_knots->at(13).second=21;
pairs_of_knots->at(14).first=2;
pairs_of_knots->at(14).second=25;
pairs_of_knots->at(15).first=2;
pairs_of_knots->at(15).second=27;
pairs_of_knots->at(16).first=1;
pairs_of_knots->at(16).second=13;
pairs_of_knots->at(17).first=6;
pairs_of_knots->at(17).second=13;
pairs_of_knots->at(18).first=25;
pairs_of_knots->at(18).second=5;
pairs_of_knots->at(19).first=18;
pairs_of_knots->at(19).second=16;
pairs_of_knots->at(20).first=18;
pairs_of_knots->at(20).second=6;
pairs_of_knots->at(21).first=7;
pairs_of_knots->at(21).second=23;
pairs_of_knots->at(22).first=3;
pairs_of_knots->at(22).second=3;
pairs_of_knots->at(23).first=1;
pairs_of_knots->at(23).second=22;
pairs_of_knots->at(24).first=13;
pairs_of_knots->at(24).second=5;
pairs_of_knots->at(25).first=19;
pairs_of_knots->at(25).second=17;
pairs_of_knots->at(26).first=3;
pairs_of_knots->at(26).second=25;
   */ //cout << "pairs\n";
    vector<int> index;
    index.resize(number_of_nodes);
    for (int i = 0; i < number_of_nodes - 1; i++)
    {
        index[left_end[i] - 1]++;
        index[right_end[i] - 1]++;
    }
   
    int s = number_of_nodes;

    while (s > 1)
    {
        /*for (int i = 0; i < number_of_nodes; i++)
        {
            if ((index[i] == 1)&&(s > 1))
            {
                //cout << s << endl;
                int k = 0;
                int parent;
                int child = i + 1;
                int distance;
                while ((left_end[k] != child)&&(right_end[k] != child)) k++;
                if (left_end[k] == child)
                {
                    parent = right_end[k];
                    distance = dist[k];
                }
                else
                {
                    parent = left_end[k];
                    distance = dist[k];
                }
                children->at(parent - 1).push_back(knot(child, distance));
                left_end[k] = -1;
                right_end[k] = -1;
                dist[k] = -1;
                index[child - 1]--;
                index[parent - 1]--;
                s--;
                if (s == 1) root = parent;
            }
        }*/
        for (int i = 0; i < number_of_nodes - 1; i++)
        {
            if ((s > 1)&&(dist[i] != -1))
            {
                if (index[left_end[i] - 1] == 1)
                {
                    int parent = right_end[i];
                    int child = left_end[i];
                    int distance = dist[i];
                    children->at(parent - 1).push_back(knot(child, distance));
                    left_end[i] = -1;
                    right_end[i] = -1;
                    dist[i] = -1;
                    index[child - 1]--;
                    index[parent - 1]--;
                    s--;
                    if (s == 1) root = parent;  
                }
                else
                {
                    if (index[right_end[i] - 1] == 1)
                    {
                        int parent = left_end[i];
                        int child = right_end[i];
                        int distance = dist[i];
                        children->at(parent - 1).push_back(knot(child, distance));
                        left_end[i] = -1;
                        right_end[i] = -1;
                        dist[i] = -1;
                        index[child - 1]--;
                        index[parent - 1]--;
                        s--;
                        if (s == 1) root = parent;  
                    }
                }
            }
        }

    }
    return root;
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
    if (left == right) return knot1;
    if (left > right) swap(left, right);
    //cout << "1\n";
    int s = log2[right - left + 1];
    //cout << "s " << s << endl;
    if (height[sparse_table[left][s] - 1] > height[sparse_table[right - (1<<s) + 1][s] - 1])
    {
        //cout << "3\n";
        return sparse_table[right - (1<<s) + 1][s];
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
    int root = Input (&children, &pairs_of_knots);
    //cout << "input\n";
    int size = (int)children.size();
    vector<int> order;
    vector<int> height;
    vector<int> first;
    first.resize(size);
    height.resize(size);
    tree_traverse(&order, &height, &first, children, 0, root);
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
        cout << d1 + d2 << endl;
    }

    
    return 0;

}