#include <iostream>

using namespace std;

int ** graph;

#define INF 99999;

void search(int size);

int main()
{
	int size, x, y, lenth;
	cin >> size;
	graph = new int*[size];

	for(int i = 0; i < size; i++)
		graph[i] = new int[size];

	for(int y = 0; y < size; y++)
		for(int x = 0; x < size; x++)
			graph[y][x] = INF;

	for(int i = 0; i < size-1; i++)
	{
		cin >> x >> y >> lenth;
		graph[x-1][y-1] = lenth;
		graph[y-1][x-1] = lenth;
	}

	cin >> lenth;
	int *start = new int[lenth];
	int *end = new int[lenth];

	search(size);

	for(int i = 0; i < lenth; i++)
		cin >> start[i] >> end[i];

	for(int i = 0; i < lenth; i++)
		cout << graph[start[i]-1][end[i]-1];

	delete [] graph;
	delete [] start;
	delete [] end;
	return 1;
}


void search(int size)
{
for (int k = 0; k < size; k++)
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			graph[i][j] = min<int>(graph[i][j], graph[i][k] + graph[k][j]);
}
