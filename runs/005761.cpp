// Программа для решения задачи "Расстояние в дереве" из тестового задания Яндекса
// Основой для алгоритма является структура данных "Система непересекающихся множеств", которая была изобретена Тарьяном (Tarjan)

#include <iostream>
#include <vector>
#include <cstdlib>

using std::cout;
using std::cin;
using std::vector;

typedef vector< vector<long int> > Graph;

class MyGraph
{
public:
	void writeAns()	// Печатает ответы на экран
	{
		for (long int i = 0; i < questList.size()/2; i++)
			cout << ans[questList[2*i]][questList[2*i+1]] << "\n" ;
	}

	void dfs()	// Запускает обход дерева с корня
	{
		dfs(0, 0, 0);
	}
	
	void read(long int nodesPairsNumber)	// Считывает граф
	{
		for (long int i = 0; i < nodesPairsNumber; i++)
		{
			long int node1, node2;
			long int distance;
			cin >> node1 >> node2 >> distance;
			node1--;
			node2--;
			graph[node1].push_back(node2);
			graph[node2].push_back(node1);
			distances[node1].push_back(distance);
			distances[node2].push_back(distance);
		}
	}

	void readQuest(long int numberOfQuestions)	// Считывает запросы
	{
		for (long int i = 0; i < numberOfQuestions; i++)
		{
			long int node1, node2;
			cin >> node1 >> node2;
			node1--;
			node2--;
			questList.push_back(node1);
			questList.push_back(node2);
			if (node1 == node2)
			{
				ans[node1][node2] = 0;
			}
			else
			{
			quest[node1].push_back(node2);
			quest[node2].push_back(node1);
			}
		}
	}

	MyGraph(long int size)
	{
		graph.resize(size);
		distanceToRoot.resize(size);
		distances.resize(size);
		quest.resize(size);
		ans.resize(size);
		dsu.resize(size);
		ancestor.resize(size);
		for (long int i = 0; i < size; i++)
		{
			wasVisited.push_back(false);
			ans[i].resize(size);
		}
	}

private:
	Graph graph;	// Сам граф
	Graph distances;	// distances[i][j] - расстояние между вршинами i+1 и graph[i][g]+1
	vector <long int> distanceToRoot;	// distanceToRoot[i] - расстояние от вершины i+1 до корня
	Graph quest;	// Запросы в виде графа
	vector <long int> questList;	// Запросы в виде списка. Запрос номер i храниться в ячейках 2i и 2i+1
	Graph ans;	// ans[i][j] содержит ответ на запрос i+1, j+1
	vector <bool> wasVisited;	// wasVisited[i] = true, если вершина i+1 была посещена при обходе
	vector <long int> dsu;	// Система непересекающихся множеств
	vector <long int> ancestor;	// ancestor[i] хранит номер наименьшего общего предка класса, характеристическим элементом которого является вешина i+1
	
	long int getFromDsu(long int v) 
	{
		if (v == dsu[v])
			return v;
		else
			return dsu[v] = getFromDsu (dsu[v]);
	}
	
	void uniteUnDsu(long int v1, long int v2, long int newAncestor)
	{
		v1 = getFromDsu(v1);
		v2 = getFromDsu(v2);
		if (rand() & 1)
		{
			long int tmp = v1;
			v1 = v2;
			v2 = tmp;
		}
		dsu[v1] = v2;
		ancestor[v2] = newAncestor;
	}

	// Обход в глубину
	void dfs(long int v,	// Текущая вершина
			 long int lastV,	// Вершина, из которой пришли в текущую	
			 long int lastI)	// v = graph[lastV][lastI]
	{
		dsu[v] = v;
		ancestor[v] = v;
		wasVisited[v] = true;
		if (v == 0)
			distanceToRoot[v] = 0;
		else
			distanceToRoot[v] = distanceToRoot[lastV] + distances[lastV][lastI];
		for (long int i = 0; i < graph[v].size(); i++)
			if (wasVisited[graph[v][i]] == false)
			{
				dfs(graph[v][i], v, i);
				uniteUnDsu(v, graph[v][i], v);
			}
		for (size_t i=0; i<quest[v].size(); ++i)
			if (wasVisited[quest[v][i]])
			{
				ans[v][quest[v][i]] = ans[quest[v][i]][v] = 
					distanceToRoot[v] + distanceToRoot[quest[v][i]]
					- 2*distanceToRoot[ancestor[getFromDsu(quest[v][i])]];
			}
	}
};


int main()
{
	// Чтение графа
	long int n;	// Количество вершин
	cin >> n;
	MyGraph myGraph(n);	// Граф
	myGraph.read(n-1);

	// Чтение запросов
	long int m;	// Количество запросов
	cin >> m;
	myGraph.readQuest(m);
	
	myGraph.dfs();	// Обход графа
	myGraph.writeAns();	// Выписывание расстояний
	return 0;
}