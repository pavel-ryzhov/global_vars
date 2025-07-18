#include <iostream>
#include <fstream>
using namespace std;
/* --------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------- */

int min( int[] );                               /* ������� ������ ������������ ���������� */
int **Graf;                                     /* ������� ��������� */
int *Label;                                     /* ������ ����� */
int *Active;                                    /* ������ ���������� ������ */

int i, j, k;
int Start, N, M, V, Last;

/* --------------------------------------------------------------------------------- */
int main()
{
	cin >> N;         
	Graf = new int *[N]; 
	for( i = 0; i < N; i ++ )
		Graf[i] = new int [N];
	for( i = 0; i < N; i ++ )
		for( j = 0; j < N; j ++ )
			Graf[i][j] = 0;
	for( k = 0; k < N - 1; k ++ )
	{
		cin >> i >> j >> V;
		Graf[i - 1][j - 1] = Graf[j - 1][i - 1] = V;
	}
	cin >> M;                                   /* ��������� ���������� ���������� */
	for( k = 0; k < M; k ++ )
	{
		Label = new int [N];
	    Active = new int [N];
	    for( i = 0; i < N; i ++ )
	    {
	   	   Label[i] = 50001;
		   Active[i] = 0;
    	}
		cin >> Start >> Last;
		Active[Start - 1] = 1;  
		Label[Start - 1] = 0;
		i = Start - 1;
		do
		{
			for( j = 0; j < N; j ++ )
			{
				if( Graf[i][j] != 0 && Label[j] > Label[i] + Graf[i][j] )
				{
					Active[j] = 1; 
					Label[j] = Label[i] + Graf[i][j];
				}
			}
			Active[i] = 0;
			i = min( Label );                   /* ���������� ����� ������� � ����������� ������ */
		}
		while( i != -1 );
		cout << Label[Last - 1] << "\n";
	}
	return 0;
}
/* --------------------------------------------------------------------------------- */
int min( int arr[] )
{
	int minim, k, min_pos = -1;
	minim = 50001;
	/* ������� ����������� ������� � ������� � ��� ������� */
	for( k = 0; k < N - 1; k ++ )
	{
		if( arr[k] < minim && Active[k] == 1)
		{
			minim = arr[k];
			min_pos = k;
		}
	}
	return min_pos;                             /* ������� ������� ������������ �������� */
}
/* --------------------------------------------------------------------------------- */