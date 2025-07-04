#include <vector>
#include <map>
#include <fstream>
#include <limits.h>

// Проверяется - все ли точки пройдены
bool hasUnvisitedNodes(std::vector<bool> *visit)
{
	for(int i = 0; i < visit->size(); i++)
	{
		if((*visit)[i] == false)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	std::ifstream in;
	std::ofstream out;
	int numberNodes, startEdge, endEdge, lengthEdge, numberPairs, startPair, endPair;

	in.open("Input.txt");

	if(!in.is_open()) return -1;

	in >> numberNodes;

	if(numberNodes == 1)
	{
		out.open("Output.txt");
		if(!out.is_open()) return -1;
		else out << 0;
		out.close();
		return 0;
	}

	std::vector<std::map<int, int> > tree(numberNodes);	// Само дерево
	std::vector<bool> visitNodes(numberNodes);			// Массив для хранения информации о пройденных точках
	std::vector<int> distances(numberNodes, INT_MAX);	// Массив расстояний до точек

	// Заполнение дерева
	for(int i = 0; i < numberNodes-1; i++)
	{
		in >> startEdge >> endEdge >> lengthEdge;
		tree[startEdge-1].insert(std::pair<int, int>(lengthEdge, endEdge));
		tree[endEdge-1].insert(std::pair<int, int>(lengthEdge, startEdge));
	}

	in >> numberPairs;

	if(numberPairs < 1) return -1;

	std::vector<std::pair<int, int> > pairs(numberPairs);	// Массив, хранящий пары для поиска

	// Заполнения массива пар для поиска
	for(int i = 0; i < numberPairs; i++)
	{
		in >> startPair >> endPair;
		pairs[i].first = startPair;
		pairs[i].second = endPair;
	}

	in.close();

	int indexMinNode = 0;
	int maxValue = INT_MAX;

	out.open("Output.txt");

	if(!out.is_open()) return -1;

	bool exit;

	for(int j = 0; j < pairs.size(); j++)
	{
		
		distances[pairs[j].first-1] = 0;	// Задание точки для поиска

		do
		{
			exit = true;

			// Цикл поиска следующего узла для обработки
			for(int i = 0; i < distances.size(); i++)
			{
				if(distances[i] < maxValue && visitNodes[i] == false) indexMinNode = i;
			}

			// Помечаем узел как проверенный
			visitNodes[indexMinNode] = true;

			// Цикл поиска расстояний до заданной точки
			for(std::map<int, int>::iterator p = tree[indexMinNode].begin(); p != tree[indexMinNode].end(); p++)
			{
				int indexNode = (*p).second-1;
				lengthEdge = (*p).first;
				if(visitNodes[indexNode] != true && (distances[indexNode] > (distances[indexMinNode] + lengthEdge))) 
					distances[indexNode] = distances[indexMinNode] + lengthEdge;
			}

		}while(hasUnvisitedNodes(&visitNodes));

		// Вывод в файл длины пути
		out << distances[pairs[j].second-1] << std::endl;

		// Подготовка массивов расстояний и посещения для следующего поиска
		for(int i = 0; i < numberNodes; i++)
		{
			visitNodes[i] = false;
			distances[i] = INT_MAX;
		}
	}

	out.close();

	return 0;
}