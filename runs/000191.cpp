#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Метод поиска вершины в списке пройденных вершин
bool isPresent(int value, vector<int> values)
{
	return (find(values.begin(), values.end(), value) != values.end());
}

// Ребро
class Edge
{
public:
	// Начало ребра
	int beginVertex;

	// Конец ребра
	int endVertex;

	// Вес ребра
	int weight;

	// Метод, который меняет вершины в ребре местами
	void swapBeginEnd()
	{
		swap(this->beginVertex, this->endVertex);
	}
};

// Путь в дереве
class Way
{
public:
	// Начальная вершина пути
	int beginVertex;

	// Конечная вершина пути
	int endVertex;

	// Длина пути
	int weight;

	// Флаг, показывающий, вычислена длина пути или нет
	bool isCalculated;
};

// Граф
class Graph
{
private:
	// Количество вершин
	int _vertexCount;

	// Количество путей
	int _waysCount;

	// Список ребер
	vector<Edge> _content;

	// Список путей
	vector<Way> _ways;

	// Движение по графу
	void step(Way &way, Edge edge, vector<int> &vertexes)
	{
		// Увеличиваем длину пути
		way.weight += edge.weight;
		vertexes.push_back(edge.endVertex);

		// Проверяем конец пути
		if (edge.endVertex == way.endVertex)
		{
			way.isCalculated = true;
			return;
		}

		// Просматриваем последующие ребра
		for (int i = 0; i < (int)this->_content.size(); i++)
		{
			Edge tmpEdge;
			if (edge.endVertex == this->_content[i].beginVertex)
			{
				tmpEdge = this->_content[i];
				if (!isPresent(tmpEdge.endVertex, vertexes))
					this->step(way, tmpEdge, vertexes);
				if (way.isCalculated)
					return;
			}
			else if (edge.endVertex == this->_content[i].endVertex)
			{
				tmpEdge = this->_content[i];
				tmpEdge.swapBeginEnd();	
				if (!isPresent(tmpEdge.endVertex, vertexes))
					this->step(way, tmpEdge, vertexes);
				if (way.isCalculated)
					return;
			}
			
		}

		way.weight -= edge.weight;
	}
public:
	// Присваиваем количество вершин
	void setVertexCount(int vertexCount)
	{
		this->_vertexCount = vertexCount;
	}

	// Метод считывания входных данных
	void getInputData()
	{
		char buffer[1024];

		// Считываем количество вершин
		cin.getline(buffer, sizeof(buffer) - 1);
		this->_vertexCount = atoi(buffer);
		if (this->_vertexCount <= 0)
			return;

		// Считываем ребра
		while (cin.getline(buffer, sizeof(buffer) - 1))
		{
			string s = buffer;

			int firstSpacePos = s.find_first_of(" ");
			// Получили все ребра
			if (firstSpacePos <= 0)
			{
				// Определяем число путей
				this->_waysCount = atoi(buffer);
				break;
			}

			// Определяем начало ребра, конец ребра и вес ребра
			int lastSpacePos = s.find_last_of(" ");
			int beginVertex = atoi(s.substr(0, firstSpacePos).data());
			int endVertex= atoi(s.substr(firstSpacePos + 1, lastSpacePos -(firstSpacePos + 1)).data());
			int weight = atoi(s.substr(lastSpacePos + 1, s.length() - (lastSpacePos + 1)).data());

			if (beginVertex > endVertex)
				swap(beginVertex, endVertex);

			Edge edge;
			edge.beginVertex = beginVertex;
			edge.endVertex = endVertex;
			edge.weight = weight;

			// Заносим ребро в список ребер
			this->_content.push_back(edge);
		}

		if (this->_waysCount <= 0)
			return;

		// Считываем пути
		for (int i = 0; i < this->_waysCount; i++)
		{
			cin.getline(buffer, sizeof(buffer) - 1);
			string s = buffer;

			int spacePos = s.find_first_of(" ");
			Way way;

			// Определяем начало и конец пути
			way.beginVertex = atoi(s.substr(0, spacePos).data());
			way.endVertex = atoi(s.substr(spacePos + 1, s.length() - (spacePos + 1)).data());
			way.weight = 0;
			way.isCalculated = false;

			if (way.beginVertex > way.endVertex)
				swap(way.beginVertex, way.endVertex);
			
			// Заносим путь в список путей
			this->_ways.push_back(way);
		}
	}

	// Метод вычисления путей
	void calculateWays()
	{
		// Проходим по всем путям в списке
		for (int i = 0; i < this->_waysCount; i++)
		{
			// Создаем фиктивное ребро
			Edge emptyEdge;
			emptyEdge.beginVertex = -1;
			emptyEdge.endVertex = this->_ways[i].beginVertex;
			emptyEdge.weight = 0;
			
			vector<int> vertexes;
			// Запускаем процедуру обхода графа
			this->step(this->_ways[i], emptyEdge, vertexes);

			// Выводим результат
			cout << this->_ways[i].weight << endl;
		}
	}
};

int main(void)
{
	Graph g;
	g.getInputData();
	system("cls");

	g.calculateWays();
	return 0;
}