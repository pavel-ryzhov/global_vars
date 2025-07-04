/* Задача B. Расстояние в дереве.
 * Идея решения:
 *	-	граф и все запросы будут сразу известны после считывания данных, поэтому рационально использовать метод Тарьяна для поиска LCA.
 *
 *	-	считываем дерево, по ходу считывания строим массив расстояний от корня до i-ой вершины дерева branch_length,
 *		итоговую длину пути будем вычислять по формуле: L = branch_length[a] + branch_length[b] - 2 * branch_length[LCA(a, b)].
 *
 *	-	LCA(a, b) будет искаться методом Тарьянта: вводится вырожденный однозначный оператор A на множестве вершин дерева,
 *		который разобьет определенным образом все множество на классы (систему непересекающихся подмножеств): dsu[] (за O(n)),
 *		далее за ~O(1) мы будем находить LCA(a, b) и вычислять длину пути во время обхода в глубину нашего графа.
 */

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

typedef pair<int, int> item;
typedef vector<item> requests;			// тип запросов

const int MAX = 40000;
vector<int> G[MAX];						// граф
requests Q[MAX];						// очередь запросов - вектор из векторов из 2-х элементов, что в плане памяти будет достаточно экономно
long branch_length[MAX], ancestor[MAX];	// массивы расстояний до корня и предков
bool u[MAX];
int dsu[MAX];							// dsu - система непересекающихся множеств
long ans[MAX];							// массив ответов


int find(int v) {return v == dsu[v] ? v : dsu[v] = find(dsu[v]); }	// поиск представителя с эвристикой path compression
void unite(int a, int b, int new_ancestor)							// метод, объединяющий подмножества (используется рандомизированная эвристика)
{
	a = find(a); b = find(b);
	if(rand() & 1) swap(a, b);
	dsu[a] = b; ancestor[b] = new_ancestor;
}


// обход графа в глубину с построением соответствующей структуры не пересекающихся множеств и ответом на запросы
void dfs(int v)
{
	int LCA;
	dsu[v] = v; ancestor[v] = v; u[v] = true;

	// идем вглубь, строя dsu
	for ( size_t i = 0; i < G[v].size(); i++ )
		if ( !u[G[v][i]] )
		{
			dfs(G[v][i]);
			unite(v, G[v][i], v);
		}
	// пробегаемся по запросам для v
	for ( size_t i = 0; i < Q[v].size(); i++ )
		if ( u[Q[v][i].first] )
		{
			LCA = ancestor[find(Q[v][i].first)];
			ans[Q[v][i].second] = branch_length[v] + branch_length[Q[v][i].first] - 2 * branch_length[LCA];
		}

}

int main()
{
	// считываем входной граф, заодно вычисляя длины ветвей
	int N; cin >> N;
	int a, b, l;
	branch_length[0] = 0;
	for (int i = 0; i < N-1; i++)
	{
		cin >> a >> b >> l; a--, b--;
		G[a].push_back(b);
		branch_length[b] = branch_length[a] + l;
	}
	// считываем запросы
	int M; cin >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b; a--, b--;
		Q[a].push_back(item(b, i)), Q[b].push_back(item(a, i));	// избытка информации нет, т.к. при проходе вглубину мы не знаем, в какой последовательности какие вершины обойдутся
	}

	// обходим граф в глубину, отвечая на соответствующие запросы
	dfs(0);

	// выводим ответы на запросы в необходимом порядке
	for (int i = 0; i < M; i++)
		cout << ans[i] << endl;

	return 0;
}