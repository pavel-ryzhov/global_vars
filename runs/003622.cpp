#include <iostream>
#include <vector>

using namespace std;

class Tree
{
public:
	Tree () {}
	Tree (int s);
	void fillTree (int, int, int);
	void dfs (int, int, int);
	void lca (int, int);
private:
	vector <vector <pair<int, int> > > g;
	vector <vector <pair<int, int> > >::iterator itr;
	vector <pair <int, int> > vp;
	pair <int, int> p;
	vector <bool> used;
	int way;
	int way_bin;
	int *deph;
	int *parent;
	int *deph_bin;
	bool run;	
	int counter;
};

Tree::Tree (int size) : way (0), way_bin(0), run (true)
{
	for (int i = 0; i < size; i++)
	{
		used.push_back(false);
	}
	p = make_pair(0,0);
	vp.push_back(p);
	g.push_back(vp);	
	deph = new int[size];
	parent = new int[size];
	deph_bin = new int[size];
}

void Tree::fillTree (int a, int b, int w)
{	
	vector <pair <int, int> > vp,vp1;
	pair <int, int> p,p1;
	p = make_pair(b, w);
	p1 = make_pair(a, w);
	vp.push_back(p);	
	if (!g[a].empty())
	{
		g[a].push_back(p);						
		vp.clear();		
	}				
	g.push_back(vp);	
	vp.clear();	
}

void Tree::dfs (int v, int last, int from)
{	
	used[v] = true;
	parent[v] = from;
	deph[v] = way;
	deph_bin[v] = way_bin;
	for (int i = 0; i < g[v].size(); i++)
	{
		int currentNode = g[v][i].first;
		int currentLenght = g[v][i].second;
		if (!used[currentNode])
		{
			way += g[v][i].second;
			way_bin++;
			dfs (currentNode, currentLenght, v);
		}
	} 	
		way_bin--;
		way -= last;	
}

void Tree::lca (int aa, int bb)
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

int p1(0), p2(0), w(0);

int main ()
{
	int size;
	int counter;
	cin >> size;
	Tree ctree(size);		
	for (int index = 0; index < size; index++)
	{
		cin >> p1 >> p2 >> w;		
		ctree.fillTree (p1, p2, w);
	}
	ctree.dfs (1, 0, 0);
	cin >> counter;
	for (int i = 0; i < counter; i++)
	{
		cin >> p1 >> p2;
		ctree.lca (p1, p2);	
	}
	return 0;
}



