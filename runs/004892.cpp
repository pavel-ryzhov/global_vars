#include <iostream>
//#include <conio.h>

using namespace std;

int** graph; //граф
int n, m, search_v, way_l = 0;

int way_length(int, int); //определение минимального пути между вершинами
int dfs(int, int); //поиск в глубину с возвращением пути до вершины

int way_length(int v1, int v2)
{
	search_v = v2;
	return dfs(v1, v1);
}

int dfs(int v, int v_sender)
{
	int s;
	for(int i = 0; i<n;i++)
	{
		if(i!=v_sender)
		{
			if(graph[v][i])
			{
				if((s = dfs(i, v)))
					return s + graph[v][i];
				if(i == search_v) return graph[v][i];
			}
		}
	}
	return 0;
}

int main()
{
	int v1, v2, r;
	std::cout<<"Input:"<<endl;
	cin>>n;
	
	graph = new int*[n];
	for(int i = 0; i<n; i++)
	{
		graph[i] = new int[n];
		for(int j = 0; j < n; j++)
			graph[i][j] = 0;
	}
	
	for(int i = 0; i < n-1; i++)
	{
		cin >> v1 >> v2 >> r;
		graph[v1 - 1][v2 - 1] = r;
		graph[v2 - 1][v1 - 1] = r;
	}
	
	int test_num, vs1, vs2;
	cin >> test_num;
	int* res = new int[test_num];

	for(int i = 0; i < test_num; i++)
	{
		cin >> vs1 >> vs2;
		res[i] = way_length(vs1 - 1, vs2 - 1);
	}
	
	cout << "Output:" << endl;
	for(int i = 0; i < test_num; i++)
		cout << res[i] << endl;

	//_getch();
	cin >> r;
	return 0;
}