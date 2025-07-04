#include <iostream>
//#include <vector>

using namespace std;

int** graph;
int n, maxid;

//set< pair<int, int> > indexes; //first - пересчитанный индекс, second - реальный
int* index_real; //возвращает реальный идекс
int* index_c; //возвращает пересчитанный индекс

void dfs_id(int, int);
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

//v1, v2 - пересчитанные индексы
int way_lca(int v1, int v2)
{
	if(v1 == v2) return 0;
	int w1 = 0, w2 = 0, anc1, anc2, tmp, v;
	
	if(v1 == 0) anc1 = 0;
	else
		for(int i = 0; i < v1; i++)
			if((tmp = graph[index_real[v1]][index_real[i]]) > -1)
			{
				anc1 = i;
				w1 = tmp;
			}
	if(v2 == 0) anc2 = 0;
	else
		for(int i = 0; i < v2; i++)
			if((tmp = graph[index_real[v2]][index_real[i]]) > -1)
			{
				anc2 = i;
				w2 = tmp;
			}

	while(1)
	{
		if(anc1 == anc2) break;
		if(anc1 > anc2)
		{
			v = anc1;
			for(int i = 0; i < v; i++)
				if((tmp = graph[index_real[v]][index_real[i]]) > -1)
				{
					anc1 = i;
					w1 += tmp;
				}
		}
		else
		{
			v = anc2;
			for(int i = 0; i < v; i++)
				if((tmp = graph[index_real[v]][index_real[i]]) > -1)
				{
					anc2 = i;
					w2 += tmp;
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
	dfs_id(0, 0);

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