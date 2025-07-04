#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <utility>
using namespace std;

vector < vector < pair < int, int > > > graph; //граф
vector < int > used_list; //список отмечанных вершин при поиске в глубину
vector < int > depth_list; //список глубин для каждой вершины
vector < pair < int, int > > visited_list; //список посещенных вершин и вес их ребер при обходе в глубину
vector < int > visited_list_pos; //в этом списке для каждой вершины хранится позиция первого вхождения в массиве visited_list

void Parse(string str, int *numbers); //Функция считывания графа с потока ввода
void DeepSearch(int root, int depth = 0, int edge_weight = 0); //Поиск в глубину
void PrepareGraph(int root); //Функция находит глубину графа
int  Peak_Distance(int s = 0, int f = 0); //Функция для нахождения расстояния между двумя вершинами в неорентированном дереве

int main()
{
	string read_line; // строка потока ввода
	int numbers[3]; //масив для хранения чисел, прочитанных с потока ввода
	getline(cin, read_line); 
	Parse(read_line, numbers); // получаем количество вершин
	int n = numbers[0]; //запоминаем количество вершин
	graph.resize(n);
	pair < int, int > temp_pair; //временная пара
	int root = 0; //Корень дерева
	for(int i = 0; i < (n - 1); i++)
	{
		getline(cin, read_line); //Читаем информацию о ребре
		Parse(read_line, numbers);
		if(i == 0) root = numbers[0] - 1; //Запоминаем корень дерева
		temp_pair.first  = numbers[1] - 1; //Запоминаем смежную вершину
		temp_pair.second = numbers[2]; //Запоминаем вес ребра
		graph[ numbers[0] - 1 ].push_back(temp_pair);
		//Для смежной вершины также запоминаем вес ребра и соседа
		temp_pair.first  = numbers[0] - 1;
		temp_pair.second = numbers[2];
		graph[ numbers[1] - 1 ].push_back(temp_pair);
	}
	PrepareGraph(root); //Подготовим граф
	getline(cin, read_line);  //Получаем количество вершин, между которыми нужно рассчитать расстояние
	Parse(read_line, numbers);
	n = numbers[0];
	vector < int > d(n);
	for(int i = 0; i < n; i++)
	{
		getline(cin, read_line); //Читаем информацию о паре вершин
		Parse(read_line, numbers);
		d[i] = Peak_Distance(numbers[0] - 1, numbers[1] - 1); //Запоминаем крайтчайшее расстояние между заданными вершинами
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

int Peak_Distance(int s, int f)
{
	int d1 = depth_list[s], d2 = depth_list[f]; //Получаем глубину 
	int dist = 0; //Расстояние между двумя вершинами
	while (d1 != d2)
	{
		if(d1 > d2) 
		{
			dist += visited_list[ visited_list_pos[s]].second; //Получаем расстояние до родителя вершины
			s = visited_list[ visited_list_pos[s] - 1 ].first; //Получаем номер вершины родителя
			d1--;
		}
		else
		{
			dist += visited_list[ visited_list_pos[f]].second; //Получаем расстояние до родителя вершины
			f = visited_list[ visited_list_pos[f] - 1 ].first; //Получаем номер вершины родителя
			d2--;
		}
	}
	while (s != f)
	{
		dist += visited_list[ visited_list_pos[s]].second;
		dist += visited_list[ visited_list_pos[f]].second;
		s = visited_list[ visited_list_pos[s] - 1 ].first;
		f = visited_list[ visited_list_pos[f] - 1 ].first;
		
	}
	return dist;
}

void PrepareGraph(int root)
{
	used_list.assign(graph.size(), 0);
	depth_list.resize(graph.size());
	DeepSearch(root); //Осуществляем поиск в глубину
	visited_list_pos.assign(graph.size(), -1);
	for (int i = 0; i < visited_list.size(); i++) //Отмечаем позицию в списке первого вхождения вершины
	{
		int peak = visited_list[i].first;
		if(visited_list_pos[peak] == -1) visited_list_pos[peak] = i;
	}
}

void DeepSearch(int root, int depth, int edge_weight)
{
	used_list[root] = 1; //Помечаем вершину
	depth_list[root] = depth; //Сохраняем глубину вершины
	pair < int, int> temp_pair;
	temp_pair.first = root; //Отмечаем номер вершины
	temp_pair.second = edge_weight; //Сохраняем вес ребра от вершины до родителя
	visited_list.push_back(temp_pair);
	for (int i = 0; i<graph[root].size(); i++) 
	{
		if (!used_list[graph[root][i].first]) 
		{
			DeepSearch(graph[root][i].first, depth+1, graph[root][i].second); //Ныряем в потомка
			visited_list.push_back(temp_pair);
		}
	}
}

