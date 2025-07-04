/* јлгоритм поиска рассто€ний, основан на нахождении наименьшего общего предка (јлгоритм “арь€на).
\  »значально находим рассто€ни€ от корн€ дерева до всех остальных вершин. 
\  ƒалее, на каждый запрос о рассто€нии между вершинами i и j, беретс€ рассто€ние равное
\  сумме рассто€ний от вершины i до корн€ и вершины j до корн€, за вычетом удвоенного 
\  рассто€ни€ от их наименьшего общего предка до корн€.
*/
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

int root(1), res(0), N(0), M(0);                  ///<«аданный корень дерева (root) и переменна€ дл€ вычислени€ пути в дереве.>
vector < bool > used;							  ///<—писок пройденных вершин дерева (используетс€ при поиске в глубину).>
vector < int > dsu, ancestor, result, dist;		  ///<—писки множеств, предков, результатов и рассто€ний от вершин до корн€.>
vector < vector < pair < int, int > > > tree, qq; ///<ƒерево(tree), хран€щеес€ списком ребер, т.е. i-€ пара содержит номер вершины,>
                                                  ///<с которой соединена i-€ вершина и вес ребра. —писок запросов (qq). >
												  ///<—труктура qq: i-€ пара содержит номер вершины j (запрос на поиск рассто€ни€>
												  ///<между вершинами (i, j)) и пор€дковый номер запроса (дл€ формировани€ результатов).>

void input();									  ///<‘ункци€ чтени€ исходных данных.>
void dfs (int);									  ///<ќбход в глубину и поиск рассто€ний между заданными вершинами.>
void dfs_cost (int);							  ///<¬ычисление путей от корн€ дерева до вершин (на основе обхода в глубину).>
void dsu_unite (int, int, int);					  ///<‘ункци€ объединени€ непересекающихс€ множеств.>
int dsu_get (int);								  ///<»щет множество, которому принадлежит вершина, и возвращает его представител€.>

int main() 
{	
	input();
	dfs_cost(root);
	dfs (root);

	///<¬ывод найденных рассто€ний.>
	for(int i = 0; i < M; i++)
		cout << result[i] << endl;

	return 0;
}

void input() {
	int vertex_1, vertex_2, cost;
	cin >> N;

	unsigned int size = N + 1;
	dsu.resize(size);
	tree.resize(size);
	dist.resize(size);
	used.resize(size, false);
	ancestor.resize(size);

	for(int i = 1; i < N; ++i)
	{
		cin >> vertex_1 >> vertex_2 >> cost;
		tree[vertex_1].push_back(make_pair(vertex_2, cost));
		tree[vertex_2].push_back(make_pair(vertex_1, cost));
	}	

	cin >> M;
	qq.resize(size);
	result.resize(M);
	for(int i = 0; i < M; i++)
	{
		cin >> vertex_1 >> vertex_2;
		qq[vertex_1].push_back(make_pair(vertex_2, i));
		qq[vertex_2].push_back(make_pair(vertex_1, i));
	}

}

int dsu_get (int v) {
	return v == dsu[v] ? v : dsu[v] = dsu_get (dsu[v]);     
}

void dsu_unite (int a, int b, int new_ancestor) {
	a = dsu_get(a),  b = dsu_get(b);
	if (rand() & 1)  
		swap (a, b);
	dsu[a] = b,  ancestor[b] = new_ancestor;
}

void dfs (int v) {
	dsu[v] = v,  ancestor[v] = v;
	used[v] = true;
	for (size_t i = 0; i < tree[v].size(); ++i)
		if (!used[tree[v][i].first]) {
			dfs (tree[v][i].first);
			dsu_unite (v, tree[v][i].first, v);
		}
	for (size_t i = 0; i < qq[v].size(); ++i)
		result[qq[v][i].second] = dist[v] + dist[qq[v][i].first] - 2 * dist[ancestor[dsu_get(qq[v][i].first)]];					
}

void dfs_cost (int v) 
{
	used[v] = true;
	for (vector < pair < int, int > >::iterator iter = tree[v].begin(); iter != tree[v].end(); ++iter)
		if (!used[iter->first]) {
			res += iter->second;
			dist[iter->first] = res;
			dfs_cost (iter->first);
			res -= iter->second;				
		}
		used[v] = false;
}	