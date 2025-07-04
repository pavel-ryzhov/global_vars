#include <iostream>
using namespace std;

void Input_matrix(int n, int** A)
{
	int in, out, weight;
	for(int i = 0; i < n - 1; i++)
	{
		cin >> in >> out >> weight;
		A[in - 1][out - 1] = weight;
		A[out - 1][in - 1] = weight;
	}
}


void Output_all_pairs(int n, int** A)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			cout << A[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void Output_pairs(int n, int** A)
{
	int m, in, out;
	cin >> m;
	for(int i = 0; i < m; i++)
	{
		cin >> in >> out;
		cout << A[in - 1][out - 1] << endl;
	}
}

void Path(int n, int** A)
{
	int** B = new int*[n];
	for(int i = 0; i < n; i++)
	{
		B[i] = new int[n];
		for(int j = 0; j < n; j++)
		{
			B[i][j] = 0;
		}
	}
	for(int k = 0; k < n; k++)
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(k % 2 == 0 && i != j)
				{
					if(A[i][j] != 0)
					{
						B[i][j] = A[i][j];
					}
					else 
					{
						if(i != k && j != k && (A[i][k] == 0 || A[k][j] == 0))
						{							
							B[i][j] = A[i][j];
						}
						else
						{
							B[i][j] = A[i][k] + A[k][j];
						}
					}
				}
				else if(i != j)
				{
					if(B[i][j] != 0)
					{
						A[i][j] = B[i][j];
					}
					else
					{
						if(i != k && j != k && (B[i][k] == 0 || B[k][j] == 0))
						{
							A[i][j] = B[i][j];
						}
						else
						{
							A[i][j] = B[i][k] + B[k][j];
						}
					}
				}
			}
		}
	}

	if(n % 2 == 1)
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				A[i][j] = B[i][j];
			}
		}
	}
}

int main()
{
	int n = 0;
	cin >> n;
	int** A = new int*[n];
	for(int i = 0; i < n; i++) 
	{ 
		A[i] = new int[n];
		for(int j = 0; j < n; j++)
		{
			A[i][j] = 0;  
		}
	}

	Input_matrix(n, A);
	Path(n, A);
	Output_pairs(n, A);
	
	return 0;
}