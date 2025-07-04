/*
 * ���� Floyd-Vorshell.cpp
 * ������ 2: ���������� � ������
 */

#include <stdio.h>
#include <memory.h> 

#define MAX_SIZE	3000		// ������������ ����� ������ � �����
#define INF			100000000	// "�������������"(����� ����� ������� ������ ������ �� ��������)


int  N = 0, M = 0;

int  m[MAX_SIZE][MAX_SIZE], start[MAX_SIZE],						// m[][] - ������� ���������,
	 end[MAX_SIZE];												// start[] � end[] - ������� "�����" � "������" ������� �����

inline void InitValues		( int N );									// �-��� ��� ��������� ������������� ������ ��������
inline void Floid_Uorshell	( int m[MAX_SIZE][MAX_SIZE], int N, int M, 
					  int start[MAX_SIZE], int end[MAX_SIZE] );	// �-��� ���������� ��������� ������ � ��������(����� �-�)

int main() {
	int register i, j, x = 0, y = 0, dist = 0;

	scanf( "%d", &N );							// ��������� N
	
	InitValues (N);								// �������������� m[][], start[], end[]
	
	for ( i = 0; i < (N - 1); i++ ) { 
		scanf("%d %d %d", &x, &y, &dist);
		m[x - 1][y - 1] = dist;					// ��������� ������� ���������
		m[y - 1][x - 1] = dist;					// �.�. �������� �������� ������ ��� ��������������� �����, 
												// ������ ����� "��������������� �� ��� �������"
	}	
	
	scanf( "%d", &M );							// ��������� M

	for ( j = 0; j < M; j++ ) {
		scanf( "%d %d", &start[j], &end[j] );	// ��������� ������� "�����" � "������"
	}											// ������� �����
	
	Floid_Uorshell( m, N, M, start, end );		// ��������� �������� �-�

	return 0;
}

/* --- ���������� ������� ��� ������������� m[][], start[], end[] --- */
inline void InitValues ( int N ) {
int register i, j;	 
	for ( i = 0; i < N; i++ )
		for ( j = 0; j < N; j++ ) {
			if ( i == j ) m[i][j] = 0;		// ��������� m[][] �� ��������� 0,
			else m[i][j] = INF;				// ��������� �������� ������� ����� "�������������"
		
		}

	memset( start,	0,	sizeof(start) );
	memset( end,	0,	sizeof(end) );
}

/* --- ���������� ������� c ���������� �-� ---
 * ��������� �������� ��������� �� http://habrahabr.ru/blogs/algorithm/105825/
 * ��� http://e-maxx.ru/algo/floyd_warshall_algorithm 
 */
inline void Floid_Uorshell( int m[MAX_SIZE][MAX_SIZE], int N, int M, int start[MAX_SIZE], int end[MAX_SIZE] ) {
	
	int register i, j, k;

	for ( k = 0; k < N; k++ )
		for ( i = 0; i < N; i++ )
			for ( j = 0; j < N; j++ ) {
					if ( m[i][j] > ( m[i][k] + m[k][j] ) )
						 m[i][j] =	 m[i][k] + m[k][j];				// ����������� ������� ��������� � ������� ������������
			}
			for ( k = 0; k < M; k++ ) 
				printf ( "%d\n", m[start[k] - 1][end[k] - 1] );		// ������� ������������ ��� ����������
}

/*
 * ����� ����� 
 * Floyd-Vorshell.cpp
 */