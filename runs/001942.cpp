#include <iostream>
using namespace std;
/* --------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------- */

int min( int[] );                               /* Функция поиска минимального расстояния */
int **Graf;                                     /* Матрица смежности */
int *Label;                                     /* Массив меток */
int *Active;                                    /* Массив пройденных вершин */
int *Temp;                                      /* Массив совпадающих вершин */ 

int i, j, k;
int Start, N, M, V, Last;

/* --------------------------------------------------------------------------------- */
int main()
{
	cin >> N;  
	Graf = new int *[N]; 
	Temp = new int [N];
	for( i = 0; i < N; i ++ )
	{
		Graf[i] = new int [N];
		Temp[i] = 0;
	}
	for( i = 0; i < N; i ++ )
		for( j = 0; j < N; j ++ )
			Graf[i][j] = 0;
	for( k = 0; k < N - 1; k ++ )
	{
		cin >> i >> j >> V;
		if( V == 0 )
		{
			Temp[i - 1] = Temp[j - 1] = 1;
		}
		if( V != 0 )
		{
			Graf[i - 1][j - 1] = Graf[j - 1][i - 1] = V;
		}
	}
	for( i = 0; i < N - 1; i ++ )
	{
		for( j = i + 1; j < N - 1; j ++ )
		{
				if( Temp[i] == Temp[j] && Temp[j] == 1 )
				{
					for( k = 0; k < N; k ++ )
					{
						if( Graf[i][k] != 0 ){ Graf[j][k] = Graf[k][j] = Graf[i][k]; }
						if( Graf[j][k] != 0 ){ Graf[i][k] = Graf[k][i] = Graf[j][k]; }
					}
				}
		}
		i = ++ j;
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