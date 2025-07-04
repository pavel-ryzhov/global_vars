/*
 * файл minPathLCA.cpp
 * Задача B: Расстояние в дереве
 */
#include <stdio.h>

#define MAXSIZE 10000

int path[MAXSIZE], parent[MAXSIZE], pathBin[MAXSIZE];	// path - путь до корня, parent - родитель, pathBin - уровень "глубины" элемента

int main () {
	
	register int i = 0;
	int N = 0, x = 0, y = 0, w = 0, 
		M = 0, a = 0, b = 0, lca = 0, lcb = 0;
	
	path[1]	 = 0;
	pathBin[1] = 1;

	scanf ("%i", &N);
	for ( i = 0; i < N - 1; i++) {
		scanf ("%i %i %i", &x, &y, &w);
		// препроцессинг
		parent[y]	= x;
		path[y]		= path[x] + w;
		pathBin[y]	= pathBin[x] + 1;  
	}

	// LCA + вычисление минимального пути
	scanf ("%i", &M);
	for ( i = 0; i < M; i++) {
		scanf ("%i %i", &a, &b);	
		lca = a;
		lcb = b;
		while (pathBin[a-1] != pathBin[b-1]) {
			if (pathBin[a-1] > pathBin[b-1]) a = parent[a];
			else							 b = parent[b];
		}
	
		while (a != b) {
			a = parent[a];
			b = parent[b];
		}
		
		printf ("%i\n", path[lca] + path[lcb] - 2 * path[a]);	// минимальный путь равен сумме пути от A до корня и  
																// пути от B до корня минус путь от корня до мин.общего предка
	}
}

/*
 * Конец файла minPathLCA.cpp
 */