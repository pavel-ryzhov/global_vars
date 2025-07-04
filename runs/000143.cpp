#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
	Алгоритм
	При построении дерева - каждой вершине присваеваем глубину в дереве
	При нахождении пути - сначала одну из вершин "подтягиваем" по глубине к другой
	Затем, если мы не пришли в одну точку, поднимаем каждую вершину на уровень выше
	и добавляем счетчик пути
*/

#define MAX 40000 // максимальное кол-во ребер

struct point
{
	int parent;
	int len;
	int pair;
	int level;
} edge;

struct point* tree[MAX];

int createPoint(int x)
{
	if (tree[x]) return 1;
	// alloc memory
	tree[x] = (struct point*)malloc(sizeof(struct point));
	tree[x]->len    = 0;
	tree[x]->level  = 0;
	tree[x]->pair   = 0;
	tree[x]->parent = 0;
	return 0;
}

/** добавление ребра в дерево */
int addEdge(int from, int to, int len)
{
	struct point *pe;
	int id = 0, pair = 0;
	// alloc memory
	createPoint(from);
	createPoint(to);
	// id = free point
	if (tree[from]->pair) { id = to;   pair = from; }
	else            { id = from; pair = to;   }
	pe = tree[id];
	pe->len    = len;
	pe->pair   = pair;
	pe->parent = 0;
	pe->level  = 0;
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

int linkPoints(int numPoints)
{
	int i, numOperations = 0;
	for (i = 1; i <= numPoints; i++)
	{
		// set level to pair
		if (tree[i]->level && tree[i]->pair && !tree[tree[i]->pair]->level)
		{
			tree[tree[i]->pair]->parent = i;
			tree[tree[i]->pair]->level  = tree[i]->level + 1;
			numOperations++;
		}
		else
		// set level to self
		if (!tree[i]->level && tree[i]->pair && tree[tree[i]->pair]->level)
		{
			tree[i]->parent = tree[i]->pair;
			tree[i]->level  = tree[tree[i]->pair]->level + 1;
			numOperations++;
		}
		// set len to pair
		if (tree[i]->level && tree[i]->pair && !tree[tree[i]->pair]->pair)
		if (tree[i]->level < tree[tree[i]->pair]->level)
		{
			tree[tree[i]->pair]->len  = tree[i]->len;
			tree[i]->pair = 0;
			tree[i]->len  = 0;
			numOperations++;
		}
	}
	return numOperations;
}

int main()
{
	int i;
	int N, M;
	int S, E, L; // начало, конец, длина ребра
	FILE *fin = stdin;//fopen("tests/test1.in", "r");
	fscanf(fin, "%d\n", &N); // кол-во вершин в дереве
	memset(tree, 0, sizeof(tree));
	for (i = 0; i < N - 1; i++)
	{
		fscanf(fin, "%d %d %d\n", &S, &E, &L);
		addEdge(S, E, L);
	}
	createPoint(1); tree[1]->level = 1;
	while (linkPoints(N));
	fscanf(fin, "%d\n", &M); // кол-во пар вершин
	for (i = 0; i < M; i++)
	{
		fscanf(fin, "%d %d\n", &S, &E);
		printf("%d\n", calcDistance(S, E));
	}
	return 0;
}
