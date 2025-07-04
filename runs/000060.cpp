#include <iostream>
#include <map>
#include <list>

using namespace std;

typedef pair<int, int> NODE;//вершина характеризуется номером родителя и длиной пути до родителя

int nodeCount;	//количество вершин
NODE* node;		//указатель на массив вершин
bool* childNode; //"Неправильные" вершины (т.е. предки вершины номер)

int shortestDistance(int, int); //расстояние между вершинами
void buildTree();
//////////////////////////////////////////
int main(int argc, char** argv)
{
	cin >> nodeCount;
	node = new NODE[nodeCount];
	childNode = new bool[nodeCount];
	childNode[0] = true;
	for (int i = 1; i < nodeCount; i++)
		childNode[i] = false;
	//Предполагаем, что номера вершин даются без пропусков и не содержат ошибок
	buildTree();

	int testCount; //Количество вычислений расстояний
	cin >> testCount;
	for (int i = 1; i <= testCount; i++)
	{
		int node1, node2;
		cin >> node1 >> node2;
		cout << shortestDistance(node1-1, node2-1) << endl;
	}
	delete [] node;
	delete [] childNode;
	return 0;
}
//////////////////////////////////////////
int shortestDistance(int node1, int node2)
{
	if (node1 == node2)
		return 0;
	list<NODE> parentsList; //список предков вершины node1 и расстояний до них
	
	int tmpDist = 0;
	while (node1 != 0) //заполнение списка
	{
		parentsList.push_back( NODE(node1, tmpDist) );
		tmpDist += node[node1].second;
		node1 = node[node1].first;
	}
	parentsList.push_back( NODE(0, tmpDist) ); //записываем корень дерева в список

	tmpDist = 0;
	while(true)  //Прибавляем расстояние, пока не найдём общего предка вершин node1 и node2
	{
		list<NODE>::iterator i = parentsList.begin();
		while (i != parentsList.end())
		{
			if (i->first == node2)
			{
				return i->second + tmpDist;
			}
			i++;
		}
		tmpDist += node[node2].second;
		node2 = node[node2].first;
	}
}
//////////////////////////////////////////
void buildTree()
{
	for (int i = 1; i < nodeCount; i++)
	{
		int parent, number, distance;
		cin >> parent >> number >> distance;
		number--;
		parent--;
		if (!childNode[number])
		{
			node[number] = NODE(parent, distance);
			childNode[number] = true;
		}
		else
		{
			node[parent] = NODE(number, distance);
		}
	}
}
