#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <utility>
using namespace std;

const int INF = 1000000000; //Число символизирующие бесконечность

void Parse(string str, int *numbers); //Функция считывания графа с потока ввода
int Peak_Distance(vector < vector < pair < int, int > > > g, int s = 0, int f = 0); //Функция для нахождения расстояния между двумя вершинами в неорентированном дереве

int main()
{
	string read_line; // строка потока ввода
	int numbers[3]; //масив для хранения чисел, прочитанных с потока ввода
	getline(cin, read_line); 
	Parse(read_line, numbers); // получаем количество вершин
	int n = numbers[0]; //запоминаем количество вершин
	vector < vector < pair < int, int > > > g(n); //граф
	pair < int, int > temp_pair; //временная пара
	int peak; //номер вершины 
	for(int i = 0; i < (n - 1); i++)
	{
		getline(cin, read_line); //Читаем информацию о ребре
		Parse(read_line, numbers);
		peak = numbers[0] - 1; //Запоминаем номер вершины
		temp_pair.first  = numbers[1] - 1; //Запоминаем смежную вершину
		temp_pair.second = numbers[2]; //Запоминаем вес ребра
		g[peak].push_back(temp_pair);
		//Для смежной вершины также запоминаем вес ребра и соседа
		temp_pair.first  = peak;
		temp_pair.second = numbers[2];
		g[numbers[1] - 1].push_back(temp_pair);
	}
	getline(cin, read_line);  //Получаем количество вершин, между которыми нужно рассчитать расстояние
	Parse(read_line, numbers);
	n = numbers[0];
	vector < int > d(n);
	for(int i = 0; i < n; i++)
	{
		getline(cin, read_line); //Читаем информацию о паре вершин
		Parse(read_line, numbers);
		d[i] = Peak_Distance(g, numbers[0] - 1, numbers[1] - 1); //Запоминаем крайтчайшее расстояние между заданными вершинами
	}
	for(int i = 0; i < n; i++)
	{
		cout<<d[i]<<endl; // Выводим вершины
	}
	

	
}

void Parse(string str, int *numbers)
{
	char *ptr, *ch_str;
	ch_str = new char [str.size()+1];
	strcpy(ch_str, str.c_str());
	ptr = strtok(ch_str, " ");
	*(numbers++) = atoi(ptr);
	while (ptr != NULL) 
	{
		ptr = strtok(NULL, " ");
		if(ptr != NULL) *(numbers++) = atoi(ptr);
	}
}

int Peak_Distance(vector < vector < pair < int, int > > > g, int s, int f)
{
	int n = g.size(); //Получим количество вершин
	vector<int> d (n, INF),  p (n); //Массив расстояний и массив предков
	d[s] = 0; //Для стартовой вершина длина пути 0
	vector<char> u (n); //Массив меток
	for (int i=0; i<n; ++i) 
	{
		int v = -1;
		//Находим вершину с минимальным расстоянием
		for (int j=0; j<n; ++j)
			if (!u[j] && (v == -1 || d[j] < d[v]))
				v = j;
		//Если расстояние до выбранной вершины оказывается равным бесконечности, то алгоритм останавливаем
		if (d[v] == INF)
			break;
		//Помечаем вершину как прочитанную
		u[v] = true;
		//Просматриваем все ее ребра
		for (int j=0; j<g[v].size(); ++j) 
		{
			//Пытаемся улучшить расстояние
			int to = g[v][j].first,
			len = g[v][j].second;
			if (d[v] + len < d[to]) 
			{
				d[to] = d[v] + len;
				p[to] = v;
			}
		}
	}
	//Возвращаем расстояние
	return d[f];
}


