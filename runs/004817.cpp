#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <sstream>

using namespace std;

typedef vector < vector<int> > graph;
typedef vector<int>::const_iterator const_graph_iter;
vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
vector<char> lca_dfs_used;
graph edges;  // массив начальных данных о ребрах
map <string, int> e; 

void lca_dfs (const graph & g, int v, int h = 1)
{
	lca_dfs_used[v] = true;
	lca_h[v] = h;
	lca_dfs_list.push_back (v);
	for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
		if (!lca_dfs_used[*i])
		{
			lca_dfs (g, *i, h+1);
			lca_dfs_list.push_back (v);
		}
}

void lca_build_tree (int i, int l, int r)
{
	if (l == r)
		lca_tree[i] = lca_dfs_list[l];
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
		return lca_tree_min (i+i, sl, sm, l, r);
	if (l > sm)
		return lca_tree_min (i+i+1, sm+1, sr, l, r);
	int ans1 = lca_tree_min (i+i, sl, sm, l, sm);
	int ans2 = lca_tree_min (i+i+1, sm+1, sr, sm+1, r);
	return lca_h[ans1] < lca_h[ans2] ? ans1 : ans2;
}

int lca (int a, int b)
{
	int left = lca_first[a],
		right = lca_first[b];
	if (left > right)  swap (left, right);
	return lca_tree_min (1, 0, (int)lca_dfs_list.size()-1, left, right);
}

int lspl_to_lca(int lca, int v) // возвращает длину кратчайшего пути от вершины до ее LCA
{
	int left = lca_first[lca];
	int right = lca_first[v];
	if (left > right)  swap (left, right);

	stack< pair<int, int> > path_stack;
	pair<int, int> p;

	int lspl = 0;
	for (int i = left; i < right; i++)
	{
		p.first = lca_dfs_list[i];
		p.second = lca_dfs_list[i + 1];
		
		if (!path_stack.empty())
		{
			pair<int, int> p2(p.second, p.first);
			if (path_stack.top() == p2) path_stack.pop();
			else path_stack.push(p);
		}
		else path_stack.push(p);
	}	
	while (!path_stack.empty())
	{
		//lspl += edges[path_stack.top().first][path_stack.top().second];
		
		ostringstream stm1, stm2;
		stm1 << path_stack.top().first;
		stm2 << path_stack.top().second;
		lspl += e[stm1.str()+stm2.str()];
		
		path_stack.pop();
	}
	return lspl;
}



int main(int argc, char *argv[])
{
	int v1, v2;
	int i, length;
	
	graph g;  // матрица смежности графа
	int root; // корень дерева
	int n;    // количество вершин в деревe
	//vector<int> e; // длины ребер
	int m; // количество пар вершин, для которых нужно найти длину кратчайшего пути
    graph pairs; // номера вершин, между которыми необходимо вычислить расстояние     
    graph tree;
	// считываем число вершин
    cin >> n;
   
    for (i = 0; i < n; i++) 
	{
		g.push_back(vector<int>(1, -1));
		edges.push_back(vector<int>(n, 0));
	} 
    
    // считываем данные о графе и длине ребер
	if (n > 1)
	{
		for (i = 0; i < n - 1; i++)
		{
			ostringstream stm1, stm2;
			cin >> v1 >> v2 >> length;

			//edges[v1 - 1][v2 - 1] = length;
			//edges[v2 - 1][v1 - 1] = length;

			
			stm1 << v1 - 1;
			stm2 << v2 - 1;

			e[stm1.str()+stm2.str()] = length;
            e[stm2.str()+stm1.str()] = length;
            
			if (g[v1 - 1][0] == -1) g[v1 - 1][0] = v2 - 1;
			else g[v1 - 1].push_back(v2 - 1);
		
			if (g[v2 - 1][0] == -1) g[v2 - 1][0] = v1 - 1;
			else g[v2 - 1].push_back(v1 - 1);
		}
	}
	else 
	{
		g[0][0] = 0;
	}
	
        
     // считываем количество пар вершин, для которых нужно найти длину кратчайшего пути
    cin >> m;

    // заполняем массив pairs размером (m x 2) нулями    
    for (i = 0; i < m; i++) pairs.push_back(vector<int>(2, 0));
    
     // считываем данные о графе и длине ребер
    for (i = 0; i < m; i++)
    {
        cin >> pairs[i][0] >> pairs[i][1];
    }

    root = 0; // номер корневой веришны

	lca_prepare (g, root);
   	
    for (i = 0; i < m; i++)
	{
		int lca_v = lca(pairs[i][0] - 1, pairs[i][1] - 1); // находим LCA для двух вершин
		cout << abs(lspl_to_lca(lca_v, pairs[i][0] - 1) + lspl_to_lca(lca_v, pairs[i][1] - 1)) << endl; 
	}

	//system("PAUSE");
    return EXIT_SUCCESS;
}
