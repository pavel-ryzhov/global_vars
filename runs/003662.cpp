/* 
 * ���� dijsktra.cpp
 * ������ B: ���������� � ������
 */

#include <stdio.h> 
#include <stdlib.h>
#include <memory.h>

#define MAX_SIZE	4096		
#define INF			32768

int m[MAX_SIZE][MAX_SIZE], start[MAX_SIZE], end[MAX_SIZE];			// m[][] - ������� ����������, 
																	// start[] � end[] - ������� ����� � ������ ������� �����
inline void Dijkstra ( int m[MAX_SIZE][MAX_SIZE],  int N,  int M,	// �-��� � ����������� ��������� ��������
					   int start[MAX_SIZE], int end[MAX_SIZE] );	

int main() {
	register int i = 0, j = 0, x = 0, y = 0, dist = 0,
				 N = 0, M = 0;

	scanf( "%d", &N );							// ��������� N
	
	for ( i = 0; i < N; ++i )
		for ( j = 0; j < N; ++j ) {
			m[i][j] = INF;						// ��������� m[][] �� ��������� 0,
		m[i][i] = 0;							// ��������� �������� ������� ����� "�������������"
	}

	for ( i = 0; i < (N - 1); ++i ) { 
		scanf("%d %d %d", &x, &y, &dist);
		m[x - 1][y - 1] = dist;					// ��������� ������� ���������
		m[y - 1][x - 1] = dist;					// ������ ����� "��������������� �� ��� �������"
	}	
	
	scanf( "%d", &M );							// ��������� M

	for ( j = 0; j < M; ++j ) {
		scanf( "%d %d", &start[j], &end[j] );	// ��������� ������� "�����" � "������"
	}											// ������� �����

	Dijkstra ( m, N, M, start, end );			// ��������� ��������
	return 0;
}

/* --- ������� � ����������� ��������� �������� ---
 * ��������� �������� ��������� http://en.wikipedia.org/wiki/Dijkstra's_algorithm
 */
inline void Dijkstra ( int m[MAX_SIZE][MAX_SIZE], int N, int M, 
					   int start[MAX_SIZE], int end[MAX_SIZE] ) {
	register int i = 0, j = 0, k = 0,
				 min = 0, minIndex = 0;
	
	int  *minPathLength	= new int[N];		// ������ � ����� ���������� ����������� ����
	bool *usedTops		= new bool[N];		// ������ "���������������" ������

	for ( j = 0; j < M; ++j ) {
		
		for ( i = 0; i < N; ++i ) {			// �������������
			usedTops[i] = false;
			minPathLength[i] = m[start[j] - 1][i];
		} 

		minPathLength[start[j] - 1] = 0;
		minIndex = start[j] - 1;
		
		// ��� ��������
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
				if ( minIndex + 1 == end[j] ) {
					printf( "%i\n", minPathLength[minIndex] ); break;
			}
		}
	}

	delete[] minPathLength;
	delete[] usedTops;
}

/* 
 * ����� ���� dijsktra.cpp
 */