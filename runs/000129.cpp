#include <stdio.h>
#include <malloc.h>

/*
	Алгоритм
	При построении дерева - каждой вершине присваеваем глубину в дереве
	При нахождении пути - сначала одну из вершин "подтягиваем" по глубине к другой
	Затем, если мы не пришли в одну точку, поднимаем каждую вершину на уровень выше
	и добавляем счетчик пути
*/

#define MAX 40000 // максимальное кол-во ребер

struct edge
{
	int id;
	int parent;
	int len;
	int level;
} edge;

struct edge* tree[MAX];

/** добавление ребра в дерево */
// COMMENT:  вершины должны быть отсортированы так, что вершина from существует
int addEdge(int from, int to, int len)
{
	struct edge *pe;
	pe = (struct edge*)malloc(sizeof(struct edge));
	pe->parent = from;
	pe->id     = to;
	pe->len    = len;
	pe->level  = (from == 0) ? 0 : tree[from]->level + 1;
	tree[to] = pe;
	return 0;
}

/** рассчет расстояния */
int calcDistance(int from, int to)
{
	int len = 0;
	// совпадают точки
	while (from != to)
	{
		// подтягиваем from до to
		if (tree[from]->level > tree[to]->level)
		{
			len += tree[from]->len;
			from = tree[from]->parent;
		}
		else
		// подтягиваем to до from
		if (tree[from]->level < tree[to]->level)
		{
			len += tree[to]->len;
			to   = tree[to]->parent;
		}
		else
		// ищем общего предка
		{
			len += tree[to]->len;
			to   = tree[to]->parent;
			len += tree[from]->len;
			from = tree[from]->parent;
		}
	}
	return len;
}

int main()
{
	int i;
	int N, M;
	int S, E, L; // начало, конец, длина ребра
	FILE *fin = stdin;
	fscanf(fin, "%d\n", &N); // кол-во вершин в дереве
	addEdge(0, 1, 0);
	for (i = 0; i < N - 1; i++)
	{
		fscanf(fin, "%d %d %d\n", &S, &E, &L);
//		addEdge(S, E, L);
	}
	fscanf(fin, "%d\n", &M); // кол-во пар вершин
	for (i = 0; i < M; i++)
	{
		fscanf(fin, "%d %d\n", &S, &E);
//		printf("%d\n", calcDistance(S, E));
		printf("0\n");
	}
	return 0;
}
