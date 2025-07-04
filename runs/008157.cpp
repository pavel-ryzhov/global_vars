#include <vector>
#include <iostream>

using namespace std;

//так как эта задача является следствием задачи LCA
//код для решение задачи LCA был позаимствован с сайта http://e-maxx.ru
//проверен и совсем чуть чуть переделан

typedef vector < vector<int> > graph;
typedef vector<int>::const_iterator const_graph_iter;

vector<int> lca_h, lca_dfs_list, lca_first, lca_tree;
vector<char> lca_dfs_used;

void lca_dfs (const graph & g, int v, int h = 1)
{
	//поиск в глубину
	lca_dfs_used[v] = true;
	lca_h[v] = h; //уровень каждой вершины
	lca_dfs_list.push_back (v); //помещаем в список на входе 
	for (const_graph_iter i = g[v].begin(); i != g[v].end(); ++i)
		if (!lca_dfs_used[*i])
		{
			lca_dfs (g, *i, h+1);
			lca_dfs_list.push_back (v); //помещаем в список на выходе
		}
}

void lca_build_tree (int i, int l, int r)
{
	//построение дерева отрезков (см http://e-maxx.ru/algo/segment_tree)
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
	//препроцессинг (см http://e-maxx.ru/algo/lca)
	int n = (int) g.size();
	lca_h.resize (n);
	lca_dfs_list.clear(); //так как глобальная переменная, чистим для каждого нового значнеия
	lca_dfs_list.reserve (n*2); 
	lca_dfs_used.assign (n, 0); 

	lca_dfs (g, root); //depth-first search

	//построение дерева отрезков
	int m = (int) lca_dfs_list.size();
	lca_tree.assign (lca_dfs_list.size() * 4 + 1, -1);
	lca_build_tree (1, 0, m-1);

	//создание массива First
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
	//нахождения минимума в дереве отрезков
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
	//возвращает вершину с наименьшей высотой
	int left = lca_first[a],
		right = lca_first[b];
	if (left > right)  swap (left, right);
	return lca_tree_min (1, 0, (int)lca_dfs_list.size()-1, left, right);
}

int way_size(const graph & g, const graph & s, int v1, int v2, int vn, int vl)
{
	//v1 вершина от которой надо найти кратчайший путь
	//v2 конечноя вершина при нахождения кратчайшего пути
	//vn текущая вершина
	//vl прошлая вершина

	if(vn == v2)
		return 0;

	//проходимся по все вершинам соединенными с данной
	int nResult = -1;
	for(unsigned i=0; i<g[vn].size(); i++)
	{
		if(g[vn][i] != vl) //что бы не вернутся обратно
		{
			//проверяем что бы данная вершина была по пути
			//т.е. если вершина находится на пути от v1 и v2 она будет их общим предком
			lca_prepare (g, g[vn][i]);
			if(lca(v1, v2) == g[vn][i])
			{
				nResult = way_size(g, s, v1, v2, g[vn][i], vn);
				if(nResult != -1) //
					nResult += s[vn][i];
				return nResult; //так как у нас дерево (остальные нес смысла проверять)
			}
		}
	}
	return nResult; 
}

int main()
{
	graph g, s;
	//s - копия графа g только хранит длины ребер от соответствующий вершин
	
	//строим граф
	unsigned nSize;

	cin >> nSize;
	g.reserve(nSize); 

	vector<int> t;
	for(unsigned i=0; i<nSize; i++)
	{
		g.push_back(t);
		s.push_back(t);
	}

	for(unsigned i=0; i<nSize-1; i++)
	{
		unsigned nT0, nT1, nT2;
		cin >> nT0 >> nT1 >> nT2;

		g[--nT0].push_back(--nT1);
		g[nT1].push_back(nT0);
		s[nT0].push_back(nT2);
		s[nT1].push_back(nT2);

	}

	//вычисляем расстояния
	cin >> nSize;

	for (unsigned i=0; i<nSize; i++)
	{
		int v1, v2; // поступил запрос
		cin >> v1 >> v2;
		int v = way_size(g, s, --v1, --v2, v1, v1);
		cout << v << endl;
	}
	return 0;
}

