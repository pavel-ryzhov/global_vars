#include <iostream>
using namespace std;
/* --------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------- */

int min( int[], int[] );                        /* Функция поиска расстояния */
int **Graf;                                     /* Матрица смежности */
int **Temp;                                     /* Массив совпадающих вершин */ 
int *Label_Up;                                  /* Массив меток */
int *Active_Up;                                 /* Массив пройденных вершин */
int *Label_Down;                                /* Массив меток */
int *Active_Down;                               /* Массив пройденных вершин */
                                                    

int i, j, k;
int Start, N, M, V, Last, i_Up, i_Down, temp;

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
		temp = 50002;
		Label_Up = new int [N];
	    Active_Up = new int [N];
		Label_Down = new int [N];
	    Active_Down = new int [N];
	    for( i = 0; i < N; i ++ )
	    {
	   	   Label_Up[i] = 50001;
		   Active_Up[i] = 0;
		   Label_Down[i] = 50001;
		   Active_Down[i] = 0;
    	}
		cin >> Start >> Last;
		if( Temp[Start - 1][Last - 1] == 1 )
		{
			cout << "0\n";
		}
		if( Graf[Start - 1][Last - 1] != 0 )
		{
			cout << Graf[Start - 1][Last - 1] << endl;
		}
		if( Graf[Start - 1][Last - 1] == 0 && Temp[Start - 1][Last - 1] != 1 )
		{
			Active_Up[Start - 1] = 1;  
    		Label_Up[Start - 1] = 0;
			Active_Down[Last - 1] = 1;  
    		Label_Down[Last - 1] = 0;
	    	i_Up = Start - 1;
			i_Down = Last - 1;
		    do
    		{
	    		for( j = 0; j < N; j ++ )
		    	{
					if( Graf[i_Up][j] != 0 && Label_Up[j] > Label_Up[i_Up] + Graf[i_Up][j] )
    				{
						Active_Up[j] = 1; 
		    			Label_Up[j] = Label_Up[i_Up] + Graf[i_Up][j];
					}
					if( Graf[i_Down][j] != 0 && Label_Down[j] > Label_Down[i_Down] + Graf[i_Down][j] )
					{
						Active_Down[j] = 1; 
		    			Label_Down[j] = Label_Down[i_Down] + Graf[i_Down][j];
					}
	        	}
				for( i = 0; i < N; i ++ )
				{
					if( Label_Up[i] + Label_Down[i] < 50001 )
					{
						temp = Label_Up[i] + Label_Down[i];
						break;
					}
				}
			    Active_Up[i_Up] = 0;
				Active_Down[i_Down] = 0;
			    i_Up = min( Label_Up, Active_Up );            /* Возвращает номер вершины с минимальной меткой */
                i_Down = min( Label_Down, Active_Down ); 
			}
    		while( temp == 50002 );
	    	cout << temp << "\n";
		}
	}
	return 0;
}
/* --------------------------------------------------------------------------------- */
int min( int arr[], int act[] )
{
	int minim, k, min_pos = -1;
	minim = 50001;
	/* Находим минимальный элемент в массиве и его позицию */
	for( k = 0; k < N; k ++ )
	{
		if( arr[k] < minim && act[k] == 1)
		{
			minim = arr[k];
			min_pos = k;
		}
	}
	return min_pos;                             /* Вертаем позицию минимального элемента */
}
/* --------------------------------------------------------------------------------- */