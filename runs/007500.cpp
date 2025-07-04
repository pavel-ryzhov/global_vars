#include <vector>
#include <iostream>
#include <string>
#include <fstream>


struct ChildVertex{
	int Number;
	int Length;
	ChildVertex(int Number_,int Length_=1): Number(Number_),Length(Length_) {}
};

typedef std::vector < std::vector<ChildVertex> > graph;
typedef std::vector<ChildVertex>::const_iterator const_graph_iter;

std::vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
std::vector<char> lca_dfs_used;

void lca_dfs (const graph & g, int v, int h = 1)
{
	lca_dfs_used[v] = true;
	lca_h[v] = h;
	lca_dfs_list.push_back (v);
	for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
		if (!lca_dfs_used[(*i).Number])
		{
			lca_dfs (g, (*i).Number, h+(*i).Length);
			lca_dfs_list.push_back (v);
		}
}

void lca_build_tree (int i, int l, int r)
// построение дерева отрезков
{
	if (l == r)	{
		lca_tree[i] = lca_dfs_list[l];
	}
	else
	{
		int m = (l + r) >> 1;
		lca_build_tree (i+i, l, m);	
		lca_build_tree (i+i+1, m+1, r);
		if (lca_h[lca_tree[i+i]] < lca_h[lca_tree[i+i+1]])
			lca_tree[i] = lca_tree[i+i];
		else
			lca_tree[i] = lca_tree[i+i+1];
	}
}

void lca_prepare (const graph & g, int root)
// препроцессинг
{
	int n = (int) g.size();
	lca_h.resize (n);
	lca_dfs_list.reserve (n*2);
	lca_dfs_used.assign (n, 0);

	lca_dfs (g, root);

	int m = (int) lca_dfs_list.size();
	lca_tree.assign (lca_dfs_list.size() * 4 + 1, -1);
	lca_build_tree (1, 0, m-1);

	lca_first.assign (n, -1);
	for (int i = 0; i < m; ++i)
	{
		int v = lca_dfs_list[i];
		if (lca_first[v] == -1)
			lca_first[v] = i;
	}
}

int lca_tree_min (int i, int sl, int sr, int l, int r)
{
	if (sl == l && sr == r)
		return lca_tree[i];
	int sm = (sl + sr) >> 1;
	if (r <= sm)
		return lca_tree_min (i+i, sl, sm, l, r); // обход левого сына
	if (l > sm)
		return lca_tree_min (i+i+1, sm+1, sr, l, r); //правого сына
	int ans1 = lca_tree_min (i+i, sl, sm, l, sm);
	int ans2 = lca_tree_min (i+i+1, sm+1, sr, sm+1, r);
	return lca_h[ans1] < lca_h[ans2] ? ans1 : ans2;
}

int lca (int a, int b)
// нахождение общего предка
{
	int left = lca_first[a],
		right = lca_first[b];
	if (left > right)  std::swap (left, right);
	return lca_tree_min (1, 0, (int)lca_dfs_list.size()-1, left, right);
}

void FillGraph(std::ifstream& file,graph & g)
// чтение графа из файла
{
	int VertexCount = 0;
	file >> VertexCount;

	std::vector<ChildVertex> Buff;
	g.assign(VertexCount,Buff);
	int Vertex=0,Child=0,Length=0,LastVertex=0;

	for(int i=0;i<VertexCount-1;i++)
	{
		file >> Vertex;
		file >> Child;
		file >> Length;
		Vertex--;
		Child--;
		if(LastVertex != Vertex)
		{
			g[LastVertex]=Buff;
			Buff.clear();
			LastVertex = Vertex;
		}
		Buff.push_back(ChildVertex(Child,Length));
	}
	g[LastVertex]=Buff;
}



int main(int argc,char *argv[])
{
	std::string ifname,ofname;
	if(argc < 3)
	{
		std::cout << "Input file name: ";
		std::getline(std::cin, ifname);
		std::cout << std::endl << "Output file name: ";
		std::getline(std::cin, ofname);
	}
	else
	{
		ifname = argv[1];
		ofname = argv[2];
	}

	graph g;
	std::ifstream file(ifname.c_str(), std::ifstream::in);
	if(!file.good())
	{
		std::cout << "Invalid input file!" << std::endl;
		return 0;
	}
	std::ofstream ofile(ofname.c_str());

	int root=0;
	FillGraph(file,g);
	lca_prepare (g, root);

	int Count=0;
	file >> Count;
	for(int i=0;i<Count;i++)
	{
		int v1=0, v2=0;
		file >> v1;
		file >> v2;
		v1--;
		v2--;
		int v = lca (v1, v2); // общий предок
		int h = lca_h[v2]-lca_h[v] + lca_h[v1] - lca_h[v] ; // сумма расстояний от вершин до общего предка
		ofile << h << std::endl;
	}
}
