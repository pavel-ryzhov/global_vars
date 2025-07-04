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

void Make_arrays(int** A, int* nodes, int* weight, int n, int* pos, int* pos2, int start, int* first_place)
{
	for(int i = 0; i < n; i++)
	{
		if(start != i && A[start][i] >= 0)
		{
			weight[*pos] = A[start][i];
			A[i][start] = -1;
			nodes[*pos] = i;
			first_place[*pos2] = *pos;
			(*pos2)++;
			(*pos)++;
			Make_arrays(A, nodes, weight, n, pos, pos2, i, first_place);
			weight[*pos] = -A[start][i];
			nodes[*pos] = start;
			(*pos)++;
		}
	}
}

void Path(int n, int** A)
{
	int* nodes = new int[2*n - 1];
	int* first_place = new int[n];
	int* weight = new int[2*n - 2];
	int* pos =  new int(1);
	int* pos2 = new int(1);
	nodes[0] = 0;
	first_place[0] = 0;
	weight[0] = 0;
	int collect = 0;
	int fp1, fp2, fp3, n1, n2;
	Make_arrays(A, nodes, weight, n, pos, pos2, 0, first_place); 
	
	for(int i = 0; i < n - 1; i++)
	{
		collect = 0;
		fp1 = first_place[i];
		fp3 = first_place[i + 1];
		for(int j = i; j < n - 1; j++)
		{	
			fp2 = first_place[j + 1];
			for(int k = first_place[j] + 1; k <= fp2; k++)
			{
				collect += weight[k];
			}
			A[n1 = nodes[fp1]][n2 = nodes[fp2]] = collect;
			A[n2][n1] = collect;
		}
		weight[fp3] = 0;
		for(int j = fp1 + 1; j < 2*n - 1; j++)
		{
			if(nodes[j] == nodes[fp3 - 1] && nodes[j - 1] == nodes[fp3])
			{
				weight[j] = 0 - weight[j];
				break;
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
			A[i][j] = -1;  
		}
		A[i][i] = 0;
	}

	Input_matrix(n, A);
	Path(n, A);
	Output_pairs(n, A);
	
	return 0;
}