#include <iostream>
using namespace std;
/* --------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------- */

int **Graf;                                     /* Матрица смежности */
int **Temp;                                     /* Массив совпадающих вершин */ 
int *Label;                                     /* Массив меток */
int *Active;                                    /* Массив пройденных вершин */
                                     

int i, j, k, h;
int Start, N, M, V, Last;
int min_pos;
int minim;

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
	for( i = 0; i < N; i ++ )
		for( j = 0; j < N; j ++ )
		{
			Graf[i][j] = 0;
			Temp[i][j] = 0;
		}
	for( k = 1; k < N; k ++ )
	{
		cin >> i >> j >> V;
		if( V == 0 )
		{
			Temp[i - 1][j - 1] = Temp[j - 1][i - 1] = 1;
		}
		Graf[i - 1][j - 1] = Graf[j - 1][i - 1] = V;
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
	   	   Label[i] = 500001;
		   Active[i] = 0;
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
				min_pos = -1;
				minim = 500001;
			    for( h = 0; h < N; h ++ )
				{
					if( Label[h] < minim && Active[h] == 1)
					{
						minim = Label[h];
						min_pos = h;
					}
				}
				i = min_pos;
			}
    		while( i != -1 );
	    	cout << Label[Last - 1] << "\n";
		}
	}
	return 0;
}
/* --------------------------------------------------------------------------------- */