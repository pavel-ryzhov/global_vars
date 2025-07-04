#include <iostream>
#include <queue>

using namespace std;

int** graph;
int n, maxid;

//set< pair<int, int> > indexes; //first - пересчитанный индекс, second - реальный
int* index_real; //возвращает реальный идекс
int* index_c; //возвращает пересчитанный индекс

void dfs_id(int, int);
void bfs_id();
int way_lca(int, int);

void dfs_id(int v, int sender)
{
	for(int i = 0; i < n;i++)
	{
		if((i != sender) && (graph[v][i] > -1))
		{
			//indexes.insert(make_pair(maxid++, i));
			index_c[i] = maxid;
			index_real[maxid++] = i;
			dfs_id(i, v);
		}
	}
}

void bfs_id()
{
	queue<int> q;
	q.push(0);
	bool* used = new bool[n];
	used[0] = true;
	for(int i = 1; i < n; i++)
		used[i] = false;

	while(!q.empty())
	{
		int v = q.front();
		q.pop();
		for(size_t i = 1; i < n; i++)
			if(graph[v][i] > -1 && !used[i])
			{
				used[i] = true;
				index_c[i] = maxid;
				index_real[maxid++] = i;
				q.push(i);
			}
	}
}

//v1, v2 - пересчитанные индексы
int way_lca(int v1, int v2)
{
	if(v1 == v2) return 0;
	int w1 = 0, w2 = 0, anc1 = v1, anc2 = v2;
	
	while(1)
	{
		if(anc1 == anc2) break;
		if(anc1 > anc2)
		{
			for(int i = 0; i < anc1; i++)
				if(graph[index_real[anc1]][index_real[i]] > -1)
				{
					w1 += graph[index_real[anc1]][index_real[i]];
					anc1 = i;
				}
		}
		else
		{
			for(int i = 0; i < anc2; i++)
				if(graph[index_real[anc2]][index_real[i]] > -1)
				{
					w2 += graph[index_real[anc2]][index_real[i]];
					anc2 = i;
				}

		}

	}
	return w1 + w2;
}

int main()
{
	int v1, v2, r;
	cin >> n;
	
	graph = new int*[n];
	index_real = new int[n];
	index_c = new int[n];
	for(int i = 0; i<n; i++)
	{
		graph[i] = new int[n];
		for(int j = 0; j < n; j++)
			graph[i][j] = -1;
	}
	
	for(int i = 0; i < n-1; i++)
	{
		cin >> v1 >> v2 >> r;
		graph[v1 - 1][v2 - 1] = r;
		graph[v2 - 1][v1 - 1] = r;
	}
	
	index_real[0] = 0; index_c[0] = 0;
	maxid = 1;
	//indexes.insert(make_pair(0, 0));
	//dfs_id(0, 0);
	bfs_id();
	//for(set< pair<int, int> >::iterator it = indexes.begin(); it != indexes.end(); ++it)
	//{
	//	cout << (*it).second << " -> " << (*it).first << endl;
	//}
	/*for(int i = 0; i < n; i++)
	{
		cout << i << " -> " << indexes[i] << endl;
	}*/
	int test_num, vs1, vs2, res;
	cin >> test_num;

	for(int i = 0; i < test_num; i++)
	{
		cin >> vs1 >> vs2;
		res = way_lca(index_c[vs1 - 1], index_c[vs2 - 1]);
		if(res == -1) res = 0;
		cout << res << endl;
	}
	//cin >> n;
	return 0;
}