#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>
#include <vector>
#include <list>
#include <stdio.h>
#include <string.h>

typedef unsigned int uint;

//элемент списка смежности
struct half_rib;
//вершина
struct vertex;
/*контейнер списка смежности. Напротив номеров вершин (индекс массива)
располагаются пары со связными вершинами и ценой перехода к ним (rib)*/
typedef std::vector<std::list<half_rib> > connectionContainer;
//контейнер для вершин. Индексы - номера вершин
typedef std::vector<vertex>				 vertexContainer;
//создать список смежности
void setConnectionInfo(connectionContainer& connectionList, std::istream& input, uint N);
/*
по списку смежности выстроить дерево
в котором у каждой вершины только один родитель,
и где каждая вершина располагается на определённом "уровне"
*/
void setVertexInfo(connectionContainer& connectionList, vertexContainer& vertArr, uint i = 0);
//расположить две вершины на одном уровне
uint getEven(vertexContainer& vertArr, uint& from, uint& to);
//поднять обе вершины на уровень
uint climbUp(vertexContainer& vertArr, uint& from, uint& to);

/*
	Алгоритм поднимает (с увеличением суммарной стоимости) нижестоящую по уровню вершину 
	до уровня вышестоящей, затем обе последовательно поднимаются вверх до тех пор, 
	пока не "встретятся" в общей вершине.
*/


const uint maxLineLen = 20;
//операции чтения, использующие С-функции для повышения быстродействия
void getRib(uint& id1, uint& id2, uint& cost, std::istream& input);
void getVertPair(uint& one, uint& two, std::istream& input);
void getInt(uint& i, std::istream& input);

struct vertex
{
	int parentId;			//номер родителя
	uint parentTravelCost;	//цена путешествия до родителя
	uint level;				//уровень
	vertex()
	{
		parentId = -1;
	}
};
int main()
{
	uint N = 0;
	std::istream& input(std::cin);
	//считать количество вершин
	::getInt(N,input);
	vertexContainer vertArr(N);
	//сформировать дерево. 
	{//после того как дерево будет сформировано, освобождаем память списка смежности
		connectionContainer connectionList(N);	
		setConnectionInfo(connectionList,input,N);
		setVertexInfo(connectionList,vertArr);
	}
	
	//считать количество пар вершин
	::getInt(N,input);
	uint from = 0;
	uint to = 0;
	while(N--)
	{
		::getVertPair(from,to,input);

		uint sum = 0;
		//сравнять уровни
		sum += getEven(vertArr,from,to);
		//поднять до общей вершины
		sum += climbUp(vertArr,from,to);
		//вывести результат
		printf("%u\n",sum);
	}
	return 0;
}

struct half_rib
{
	uint id;
	uint cost;
};



uint getEven(vertexContainer& vertArr, uint& from, uint& to)
{
	uint sum = 0;
	//определить, кто ниже; работать с ним
	uint& lowerOne = (vertArr[from].level < vertArr[to].level) ? to : from;
	while(vertArr[from].level != vertArr[to].level)
	{
			//увеличить стоимость пути
			sum += vertArr[lowerOne].parentTravelCost;
			//поднять
			lowerOne = vertArr[lowerOne].parentId;
	}
	return sum;
}


uint climbUp(vertexContainer& vertArr, uint& from, uint& to)
{
	uint sum = 0;
	while(from != to)
	{
		//увеличить суммарную стоимость
		sum += vertArr[from].parentTravelCost;
		sum += vertArr[to].parentTravelCost;
		//поднять обоих
		from = vertArr[from].parentId;
		to = vertArr[to].parentId;
	}
	return sum;
}

void setConnectionInfo(connectionContainer& connectionList, std::istream& input, uint N)
{
	for(uint i=0; i<N-1; i++)
	{
		//для каждого считанного ребра создать по элементу в списке смежности
		//для каждой из двух вершин
		half_rib first;
		half_rib second;
		uint cost = 0;
		::getRib(first.id,second.id,cost,input);
		first.cost = second.cost = cost;
		connectionList[first.id].push_back(second);
		connectionList[second.id].push_back(first);
	}
}

void setVertexInfo(connectionContainer& connectionList, vertexContainer& vertArr, uint i)
{	
	if(i==0)
	{
		vertArr[0].parentId = 0;
		vertArr[0].level = 0;
	}
	for(std::list<half_rib>::iterator it = connectionList[i].begin(); it != connectionList[i].end(); it++)
	{
		//последовательно спускаясь по списку смежности, ..
		if(vertArr[it->id].parentId==-1)					//если только вершина ещё не была обработана
		{
			vertArr[it->id].parentId = i;					//расставляем родительские отношения у вершин
			vertArr[it->id].parentTravelCost = it->cost;	//присваиваем стоимости путешествия до родителя
			vertArr[it->id].level = vertArr[i].level+1;		//увеличиваем уровень в дереве
			setVertexInfo(connectionList,vertArr,it->id);	//проделываем тоже самое с нижестоящими вершинами
		}
	}
}

void getRib(uint& id1, uint& id2, uint& cost, std::istream& input)
{
	static char buf[maxLineLen];
	input.getline(buf,maxLineLen);
	id1 = atoi(strtok(buf," "));
	id2 = atoi(strtok(NULL," "));
	id1--;
	id2--;
	cost = atoi(strtok(NULL," "));
}

void getVertPair(uint& one, uint& two, std::istream& input)
{
	static char buf[maxLineLen];
	input.getline(buf,maxLineLen);
	one = atoi(strtok(buf," "));
	two = atoi(strtok(NULL," "));
	one--;
	two--;
}

void getInt(uint& i, std::istream& input)
{
	static char buf[maxLineLen];
	input.getline(buf,maxLineLen);
	i = atoi(buf);
}
