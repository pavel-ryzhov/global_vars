#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>


struct ChildVertex{
	int Number;
	int Length;
	ChildVertex(int Number_,int Length_=1): Number(Number_),Length(Length_) {}
};

typedef std::vector < std::vector<ChildVertex> > graph;
typedef std::vector<ChildVertex>::const_iterator const_graph_iter;

std::vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
std::vector<char> lca_dfs_used;
std::map<int,int> EqualVertex;

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
	//if(sl == 0 && sr == 0)
	//	return lca_tree[i];
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

void FillGraph(graph & g)
// чтение графа из файла
{
	int VertexCount = 0;
	std::cin >> VertexCount;

	std::vector<ChildVertex> Buff;
	g.assign(VertexCount,Buff);
	int Parent=0,Child=0,Length=0,LastVertex=0;

	for(int i=0;i<VertexCount-1;i++)
	{
		std::cin >> Parent;
		std::cin >> Child;
		std::cin >> Length;

		//if(g.size() < (unsigned int)Child) // по условию номера вершин неотрицательные
		//	g.push_back(Buff);

		Parent--;
		Child--;
		
		if(Length == 0)
		{
			if(Child < Parent)
				std::swap(Child,Parent);
			EqualVertex[Child]=Parent;
			
			if(g[Child].size())
			{
				for(std::vector<ChildVertex>::iterator it = g[Child].begin();it!=g[Child].end();it++) // замена упоминаний о сыне на родителя
					for(std::vector<ChildVertex>::iterator It = g[(*it).Number].begin();It!=g[(*it).Number].end();It++)
						if((*It).Number == Child)
							(*It).Number = Parent;
				

				std::size_t sz = g[Child].size();
				ChildVertex cv(0,0);
				for(std::size_t i=0;i<sz;i++)
					g[Parent].push_back(cv);
				std::copy(g[Child].begin(),g[Child].end(),g[Parent].begin());
				g[Child].clear();
			}
		}
		else
		{
			while(EqualVertex.find(Parent)!=EqualVertex.end())
				Parent=EqualVertex[Parent];
			while(EqualVertex.find(Child)!=EqualVertex.end())
				Child=EqualVertex[Child];

			g[Parent].push_back(ChildVertex(Child,Length));
			std::swap(Child,Parent);
			g[Parent].push_back(ChildVertex(Child,Length));
		}
	}

}

int main(int argc,char *argv[])
{
	graph g;
	int root=0;
	
	FillGraph(g);
	lca_prepare (g, root);

	int Count=0;
	std::cin >> Count;
	for(int i=0;i<Count;i++)
	{
		int v1=0, v2=0;
		std::cin >> v1;
		std::cin >> v2;
		v1--;
		v2--;
		while(EqualVertex.find(v1)!=EqualVertex.end())
			v1=EqualVertex[v1];
		while(EqualVertex.find(v2)!=EqualVertex.end())
			v2=EqualVertex[v2];
		int v = lca (v1, v2); // общий предок
		int h = lca_h[v2]-lca_h[v] + lca_h[v1] - lca_h[v] ; // сумма расстояний от вершин до общего предка
		std::cout << h << std::endl;
	}
	
	return 0;
}
