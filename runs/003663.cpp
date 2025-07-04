#include <stdio.h> 
#include <stdlib.h>
#include <memory.h>

#define MAX_SIZE	4096		
#define INF			32768

int m[MAX_SIZE][MAX_SIZE], start, end; 

inline void Dijkstra ( int m[MAX_SIZE][MAX_SIZE],  int N,  int M,
					   int start, int end);	
int main() {
	register int i = 0, j = 0, x = 0, y = 0, dist = 0,
	N = 0, M = 0;
	
	scanf( "%d", &N );
	
	for ( i = 0; i < N; ++i )
		for ( j = 0; j < N; ++j ) {
			m[i][j] = INF;						
			m[i][i] = 0;					
		}
	
	for ( i = 0; i < (N - 1); ++i ) { 
		scanf("%d %d %d", &x, &y, &dist);
		m[x - 1][y - 1] = dist;					
		m[y - 1][x - 1] = dist;					
	}	
	
	scanf( "%d", &M );							
	
	for ( i = 0; i < M; ++i ) {
		scanf( "%d %d", &start, &end );	
		Dijkstra ( m, N, M, start, end );
	}											
	return 0;
}


inline void Dijkstra ( int m[MAX_SIZE][MAX_SIZE], int N, int M, 
					   int start, int end ) {
	register int i = 0, k = 0,
	min = 0, minIndex = 0;
	
	int  *minPathLength		= new int[N];		
	bool *usedTops			= new bool[N];	
	
	for ( i = 0; i < N; ++i ) {		
		usedTops[i] = false;
		minPathLength[i] = m[start - 1][i];
	} 
		
	minPathLength[start - 1] = 0;
	minIndex = start - 1;
		
	for ( k = 0; k < N; ++k ) {
		for ( i = 0; i < N; ++i )
			if ( usedTops[i] == false && minPathLength[i] > minPathLength[minIndex] + m[minIndex][i] ) {
				minPathLength[i] = minPathLength[minIndex] + m[minIndex][i];
			}
		min = INF;
		for ( i = 0; i < N; ++i )
			if ( usedTops[i] == false && min > minPathLength[i] ) {
				min = minPathLength[i]; 
				minIndex = i;
			}
		usedTops[minIndex] = true;
		if ( minIndex + 1 == end ) {
			printf( "%i\n", minPathLength[minIndex] ); break;
		}
	}
	delete[] minPathLength;
	delete[] usedTops;
}