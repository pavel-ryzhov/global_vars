#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

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

// Вершина
class Vertex
{
public:
	int number;
	int level;
	int parentNumber;
	int wayToParent;
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

	// Список вершин
	vector<Vertex> _vertexes;

	// Список путей
	vector<Way> _ways;
public:
	// Шаг на верх
	void step_2(int &vertex, int &weight)
	{
		Vertex v = this->_vertexes[vertex - 1];
		weight += this->_vertexes[v.number - 1].wayToParent;
		vertex = this->_vertexes[v.number - 1].parentNumber;
	}

	// Присваиваем количество вершин
	void setVertexCount(int vertexCount)
	{
		this->_vertexCount = vertexCount;
	}


	// Шаг
	void step(int previous, int current, vector<Vertex> &vertexes, int &level)
	{
		level++;
		for  (int i = 0; i < (int)this->_content.size(); i++)
		{			
			Edge e = this->_content[i];
			if ((e.beginVertex == current) && (e.endVertex != previous))
			{
				Vertex v;
				v.number = e.endVertex;
				v.level = level;
				v.parentNumber = e.beginVertex;
				v.wayToParent = e.weight;
				vertexes[v.number - 1] = v;
				step(current, v.number, vertexes, level);
			}
			else if ((e.endVertex == current) && (e.beginVertex != previous))
			{
				Vertex v;
				v.number = e.beginVertex;
				v.level = level;
				v.parentNumber = e.endVertex;
				v.wayToParent = e.weight;
				vertexes[v.number - 1] = v;
				step(current, v.number, vertexes, level);
			}
		}
		level--;
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

		// Переобозначаем вершины
		this->_vertexes.resize(this->_vertexCount);
		int level = 1;
		Vertex v;
		v.level = 1;
		v.number = this->_content[0].beginVertex;
		v.parentNumber = -1;
		v.wayToParent = -1;

		this->_vertexes[v.number - 1] = v;
		this->step(-1, v.number, this->_vertexes, level);
		
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
			Vertex vb = this->_vertexes[this->_ways[i].beginVertex - 1];
			Vertex ve = this->_vertexes[this->_ways[i].endVertex - 1];
			int weight = 0;
			while (vb.number != ve.number)
			{				
				if (vb.level < ve.level)
				{
					int n = ve.number;
					this->step_2(n, weight);
					ve = this->_vertexes[n - 1];
				}
				else
				{
					int n = vb.number;
					this->step_2(n, weight);
					vb = this->_vertexes[n - 1];
				}
			}
			cout << weight << endl;
		}
	}
};

int main(void)
{
	Graph g;
	g.getInputData();
	g.calculateWays();
	return 0;
}