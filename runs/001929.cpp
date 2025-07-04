#include <iostream>
#include <fstream>
using namespace std;
/* --------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------- */

int min( int[] );                               /* Функция поиска минимального расстояния */
int **Graf;                                     /* Матрица смежности */
int *Label;                                     /* Массив меток */
int *Active;                                    /* Массив пройденных вершин */

int i, j, k;
int Start, N, M, V, Last, v_1, v_2;

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
		if( V == 0 )
		{
			Graf[i - 1][j - 1] = Graf[j - 1][i - 1] = V;
			v_1 = i; v_2 = j;
		}
		else
		{
			if( v_1 == i )
			{
				Graf[i - 1][j - 1] = Graf[j - 1][i - 1] = V;
				Graf[v_2 - 1][j - 1] = Graf[j - 1][v_2 - 1] = V;
			}
			if( v_1 == j )
			{
				Graf[i - 1][j - 1] = Graf[j - 1][i - 1] = V;
				Graf[i - 1][v_2 - 1] = Graf[v_2 - 1][i - 1] = V;
			}
			if( v_2 == i )
			{
				Graf[i - 1][j - 1] = Graf[j - 1][i - 1] = V;
				Graf[v_1 - 1][j - 1] = Graf[j - 1][v_1 - 1] = V;
			}
			if( v_2 == j )
			{
				Graf[i - 1][j - 1] = Graf[j - 1][i - 1] = V;
				Graf[i - 1][v_1 - 1] = Graf[v_1 - 1][i - 1] = V;
			}
			if( v_1 != i && v_1 != j && v_2 != i && v_2 != j )
			{
				Graf[i - 1][j - 1] = Graf[j - 1][i - 1] = V;
			}
		}
	}
	cin >> M;                                   /* Считываем количество расстояний */
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
			i = min( Label );                   /* Возвращает номер вершины с минимальной меткой */
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
	/* Находим минимальный элемент в массиве и его позицию */
	for( k = 0; k < N - 1; k ++ )
	{
		if( arr[k] < minim && Active[k] == 1)
		{
			minim = arr[k];
			min_pos = k;
		}
	}
	return min_pos;                             /* Вертаем позицию минимального элемента */
}
/* --------------------------------------------------------------------------------- */