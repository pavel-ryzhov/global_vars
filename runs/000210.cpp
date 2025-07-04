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
};

// Связь
class Link
{
public:
	int endVertex;
	int weight;
};

// Граф
class Graph
{
public:
	// Количество вершин
	int vertexCount;

	// Количество путей
	int waysCount;

	// Список ребер
	vector<Edge> edges;

	// Список вершин
	vector<Vertex> vertexes;

	// Список путей
	vector<Way> ways;

	// Связи вершин друг с другом
	vector< vector<Link> > links;

	// Шаг на верх
	void stepToRoot(int &vertex, int &weight)
	{
		weight += this->vertexes[this->vertexes[vertex - 1].number - 1].wayToParent;
		vertex = this->vertexes[this->vertexes[vertex - 1].number - 1].parentNumber;
	}

	// Шаг
	void step(int previous, int current, vector<Vertex> &vertexes, int &level)
	{
		level++;
		for (int i = 0; i < (int)this->links[current - 1].size(); i++)
		{
			if ((int)this->links[current - 1][i].endVertex != previous)
			{
				Vertex v;
				v.number = (int)this->links[current - 1][i].endVertex;
				v.level = level;
				v.parentNumber = current;
				v.wayToParent = (int)this->links[current - 1][i].weight;
				vertexes[v.number - 1] = v;
				step(current, v.number, vertexes, level);
			}
		}		
		level--;
	}
	// Метод считывания входных данных
	void getInputData()
	{
		char buffer[32];

		// Считываем количество вершин
		cin.getline(buffer, sizeof(buffer) - 1);
		this->vertexCount = atoi(buffer);

		if (this->vertexCount <= 0)
			return;

		this->links.resize(this->vertexCount);

     	// Считываем ребра
		while (cin.getline(buffer, sizeof(buffer) - 1))
		{
			string s = buffer;

			int firstSpacePos = s.find_first_of(" ");
			// Получили все ребра
			if (firstSpacePos <= 0)
			{
				// Определяем число путей
				this->waysCount = atoi(buffer);
				break;
			}

			// Определяем начало ребра, конец ребра и вес ребра
			int lastSpacePos = s.find_last_of(" ");
			int beginVertex = atoi(s.substr(0, firstSpacePos).data());
			int endVertex= atoi(s.substr(firstSpacePos + 1, lastSpacePos -(firstSpacePos + 1)).data());
			int weight = atoi(s.substr(lastSpacePos + 1, s.length() - (lastSpacePos + 1)).data());

			// Инициализируем ребро
			Edge edge;
			edge.beginVertex = beginVertex;
			edge.endVertex = endVertex;
			edge.weight = weight;

			// Заносим связи вершин
			Link l;
			l.endVertex = endVertex;
			l.weight = weight;
			this->links[beginVertex - 1].push_back(l);
			l.endVertex = beginVertex;
			this->links[endVertex - 1].push_back(l);

			// Заносим ребро в список ребер
			this->edges.push_back(edge);
		}

		// Определяем глубину вершин
		this->vertexes.resize(this->vertexCount);
		int level = 1;
		Vertex v;
		v.level = 1;
		if (this->vertexCount > 1)
		{
			v.number = this->edges[0].beginVertex;
			v.parentNumber = -1;
			v.wayToParent = -1;

			this->vertexes[v.number - 1] = v;
			this->step(-1, v.number, this->vertexes, level);
		}
		
		if (this->waysCount <= 0)
			return;

		// Считываем пути
		for (int i = 0; i < this->waysCount; i++)
		{
			cin.getline(buffer, sizeof(buffer) - 1);
			string s = buffer;

			int spacePos = s.find_first_of(" ");
			
			// Определяем начало и конец пути
			Way way;			
			way.beginVertex = atoi(s.substr(0, spacePos).data());
			way.endVertex = atoi(s.substr(spacePos + 1, s.length() - (spacePos + 1)).data());
			way.weight = 0;

			if (way.beginVertex > way.endVertex)
				swap(way.beginVertex, way.endVertex);
			
			// Заносим путь в список путей
			this->ways.push_back(way);
		}
	}

	// Метод вычисления путей
	void calculateWays()
	{
		// Проходим по всем путям в списке
		for (int i = 0; i < this->waysCount; i++)
		{
			if (this->ways[i].beginVertex == this->ways[i].endVertex)
			{
				cout << 0 << endl;
				continue;
			}
			Vertex vb = this->vertexes[this->ways[i].beginVertex - 1];
			Vertex ve = this->vertexes[this->ways[i].endVertex - 1];
			int weight = 0;
			while (vb.number != ve.number)
			{				
				if (vb.level < ve.level)
				{
					int n = ve.number;
					this->stepToRoot(n, weight);
					ve = this->vertexes[n - 1];
				}
				else
				{
					int n = vb.number;
					this->stepToRoot(n, weight);
					vb = this->vertexes[n - 1];
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