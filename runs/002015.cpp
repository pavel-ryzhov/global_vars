#include <iostream>
using namespace std;
/* --------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------- */

void quick( int, const int, const int );        /* Функция поиска расстояния */
int **Graf;                                     /* Матрица смежности */
int **Temp;                                     /* Массив совпадающих вершин */ 
int *Label;                                     /* Массив меток */
int *Active;                                    /* Массив пройденных вершин */                                                    

int i, j, k;
int Start, N, M, V, Last;

/* --------------------------------------------------------------------------------- */
int main()
{
	cin >> N;  
	Graf = new int *[N]; 
	Temp = new int *[N];
	for( i = 0; i < N; i ++ )
	{
		Graf[i] = new int [N];
		Temp[i] = new int [N];
	}
	for( i = 0; i < N - 1; i ++ )
		for( j = i; j < N; j ++ )
		{
			Graf[i][j] = Graf[j][i] = 0;
			Temp[i][j] = Temp[j][i] = 0;
		}
	for( k = 1; k < N; k ++ )
	{
		cin >> i >> j >> V;
		if( V == 0 )
		{
			Temp[i - 1][j - 1] = Temp[j - 1][i - 1] = 1;
		}
		if( V != 0 )
		{
			Graf[i - 1][j - 1] = Graf[j - 1][i - 1] = V;
		}
	}
	/*for( i = 0; i < N; i ++ )
	{
		for( j = 0; j < N - 1; j ++ )
		{
			if( Temp[i][j] == 1 )
			{
				for( k = j + 1; k < N; k ++ )
				{
					if( Temp[i][k] == 1 )
					{
						Temp[j][k] = Temp[k][j] = 1;
					}
				}
			}
		}
	}*/
	for( i = 0; i < N; i ++ )
	{
		for( j = 0; j < N; j ++ )
		{
			if( Temp[i][j] == 1 )
			{
				for( k = 0; k < N; k ++ )
				{
					if( Graf[i][k] != 0 ){ Graf[j][k] = Graf[k][j] = Graf[i][k]; }
				}
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
	   	   Label[i] = 0;
		   Active[i] = 0;
		}
		cin >> Start >> Last;
		if( Temp[Start - 1][Last - 1] == 1 || Start == Last )
		{
			cout << "0\n"; 
		}
		if( Graf[Start - 1][Last - 1] != 0 )
		{
			cout << Graf[Start - 1][Last - 1] << endl; 
		}
		if( Graf[Start - 1][Last - 1] == 0 && Temp[Start - 1][Last - 1] != 1 && Start != Last )
		{
			Active[Start - 1] = 1;  
    		quick( Start - 1, N, Last - 1 );
		}
	}
	return 0;
}
/* --------------------------------------------------------------------------------- */
void quick( int temp_i, const int number, const int stop )
{
	int m, h;
	if( temp_i == stop )
	{
		cout << Label[stop] << endl;
	}
	else
	{
		for( m = 0; m < number; m ++ )
		{
			if( Graf[temp_i][m] != 0 && Active[m] != 1 )
			{
				Active[m] = 1;
				Label[m] = Label[temp_i] + Graf[temp_i][m];
				for( h = 0; h < number; h ++ )
				{
					if( Temp[m][h] == 1)
					{
						Active[h] = 1;
					}
				}
				quick( m, number, stop );
			}
		}
	}
}    
/* --------------------------------------------------------------------------------- */