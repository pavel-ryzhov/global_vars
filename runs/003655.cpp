#include <iostream>
#include <vector>

using namespace std;

class Tree
{
    public:
    Tree(int);
    ~Tree();
    void fillTree (vector <vector <pair<int, int> > >&, int, int, int);
    void dfs (int, int, int);
    void lca (vector <vector <pair<int, int> > >&, int, int);
    void print (vector <vector <pair<int, int> > >&);
    void getTree (vector <vector <pair<int, int> > > &);
    private:
    vector <bool> used;
    vector <vector <pair<int, int> > > tree;
    int way;
    int way_bin;
    int *deph;
    int *parent;
    int *deph_bin;
    bool run;
};

Tree::Tree (int size) : way(0), way_bin(0), run(true)
{
    deph = new int[size];
    parent = new int[size];
    deph_bin = new int[size];
    used.resize(size, false);
}

Tree::~Tree ()
{
}

void Tree::getTree (vector <vector <pair<int, int> > >& g)
{
    tree = g;
}

void Tree::fillTree (vector <vector <pair<int, int> > >& tree, int a, int b, int w)
{
	vector <pair <int, int> > vp,vp1;
	pair <int, int> p,p1;
	p = make_pair(b, w);
	p1 = make_pair(a, w);
	vp.push_back(p);
		tree[a].push_back(p);
		vp.clear();
}

void Tree::dfs (int v, int last, int from)
{
 	used[v] = true;
	parent[v] = from;
	deph[v] = way;
	deph_bin[v] = way_bin;
	for (int i = 0; i < tree[v].size(); i++)
	{
        int currentNode = tree[v][i].first;
		int currentLenght = tree[v][i].second;
		if (!used[currentNode])
		{
			way += tree[v][i].second;
			way_bin++;
			dfs (currentNode, currentLenght, v);
		}
	}
		way_bin--;
		way -= last;
}

void Tree::lca (vector <vector <pair<int, int> > >& tree, int aa, int bb)
{
	int a = aa;
	int b = bb;
	while (deph_bin[a] != deph_bin[b])
	{
		if (deph_bin[a] > deph_bin[b])
			a = parent[a];
		else
			b = parent[b];
	}
	while (a != b)
	{
		a = parent[a];
		b = parent[b];
	}
	int lca = a;
	int way_ab = deph[aa] + deph[bb] - 2*deph[lca];
	cout << way_ab << '\n';
}

int main ()
{
    int size(0);
    int p1, p2, w;
    vector <vector <pair<int, int> > > g;
    vector <vector <pair<int, int> > >::iterator itr;
    vector <pair <int, int> > vp;
    pair <int, int> p;
	cin >> size;
	Tree tree(size);
	g.resize(size);
	p = make_pair(0,0);
	vp.push_back(p);
	itr = g.begin();
    g.insert(itr, vp);
    if (size > 1)
    {
        for (int index = 0; index < size-1; index++)
        {
            cin >> p1 >> p2 >> w;
            tree.fillTree (g, p1, p2, w);
        }
    }
    else
    {
        tree.fillTree(g, 1, 0, 0);
    }
	tree.getTree(g);
	tree.dfs (1, 0, 0);
	cin >> size;
	for (int i = 0; i < size; i++)
	{
	    cin >> p1 >> p2;
        tree.lca (g, p1, p2);
	}
	return 0;
}
