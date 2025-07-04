/*
 * файл Floyd-Vorshell.cpp
 * Задача 2: Расстояние в дереве
 */

#include <stdio.h>
#include <memory.h> 

#define MAX_SIZE	3000		// максимальное число вершин в графе
#define INF			100000000	// "бесконечность"(число много большее длинны любого из отрезков)


int  N = 0, M = 0;

int  m[MAX_SIZE][MAX_SIZE], start[MAX_SIZE],						// m[][] - матрица смежности,
	 end[MAX_SIZE];												// start[] и end[] - матрицы "начал" и "концов" искомых путей

inline void InitValues		( int N );									// ф-ция для начальной инициализации данных массивов
inline void Floid_Uorshell	( int m[MAX_SIZE][MAX_SIZE], int N, int M, 
					  int start[MAX_SIZE], int end[MAX_SIZE] );	// ф-ция реализации алгоритма Флойда — Уоршелла(далее Ф-У)

int main() {
	int register i, j, x = 0, y = 0, dist = 0;

	scanf( "%d", &N );							// считываем N
	
	InitValues (N);								// инициализируем m[][], start[], end[]
	
	for ( i = 0; i < (N - 1); i++ ) { 
		scanf("%d %d %d", &x, &y, &dist);
		m[x - 1][y - 1] = dist;					// заполняем матрицу смежности
		m[y - 1][x - 1] = dist;					// т.к. алгоримт работает только для ориентрованного графа, 
												// делаем ребра "ориентироваными во все стороны"
	}	
	
	scanf( "%d", &M );							// считываем M

	for ( j = 0; j < M; j++ ) {
		scanf( "%d %d", &start[j], &end[j] );	// заполняем матрицы "начал" и "концов"
	}											// искомых путей
	
	Floid_Uorshell( m, N, M, start, end );		// запускаем алгоримт Ф-У

	return 0;
}

/* --- реализация функции для инициализации m[][], start[], end[] --- */
inline void InitValues ( int N ) {
int register i, j;	 
	for ( i = 0; i < N; i++ )
		for ( j = 0; j < N; j++ ) {
			if ( i == j ) m[i][j] = 0;		// заполняем m[][] по диагонали 0,
			else m[i][j] = INF;				// остальные элементы матрицы равны "бесконечности"
		
		}

	memset( start,	0,	sizeof(start) );
	memset( end,	0,	sizeof(end) );
}

/* --- реализация функции c алгоритмом Ф-У ---
 * подробное описание алгоритма на http://habrahabr.ru/blogs/algorithm/105825/
 * или http://e-maxx.ru/algo/floyd_warshall_algorithm 
 */
inline void Floid_Uorshell( int m[MAX_SIZE][MAX_SIZE], int N, int M, int start[MAX_SIZE], int end[MAX_SIZE] ) {
	
	int register i, j, k;

	for ( k = 0; k < N; k++ )
		for ( i = 0; i < N; i++ )
			for ( j = 0; j < N; j++ ) {
					if ( m[i][j] > ( m[i][k] + m[k][j] ) )
						 m[i][j] =	 m[i][k] + m[k][j];				// преобразуем матрицу смежности в матрицу достижимости
			}
			for ( k = 0; k < M; k++ ) 
				printf ( "%d\n", m[start[k] - 1][end[k] - 1] );		// выводим интересующие нас расстояния
}

/*
 * конец файла 
 * Floyd-Vorshell.cpp
 */