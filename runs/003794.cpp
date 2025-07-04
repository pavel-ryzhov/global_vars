#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

// направленное ребро
class CEdge
{
public:
// конструктор
// i - узел, на который смотрит данное ребро
// l - длина ребра
	CEdge(int i, int l)
	{
		id = i;
		len = l;
	}

	int id; // узел, на который смотрит данное ребро
	int len; // длина ребра
};

// узел
class CNode : public vector<CEdge>
{
public:
	CNode(){reset();}

// сброс
	void reset()
	{
		x = 0;
		idPrev = -1;
	}

	int x; // расстояние до узла
	int idPrev; // узел, по которому пришел сигнал к данному узлу
};

// граф
class CGraph
{
public:
// конструктор
// N - число узлов
	CGraph(int N)
	{
		Nn = N;
		nodes = new CNode[N];
	}

	~CGraph()
	{
		delete[] nodes;
	}

// добавление двунаправленного ребра
// n1 - начальный узел
// n2 - конечный узел
// len - длина ребра
	void addEdge(int n1, int n2, int len)
	{
		nodes[n1].push_back(CEdge(n2, len));
		nodes[n2].push_back(CEdge(n1, len));
	}

// получение расстояние между узлами
// n1 - начальный узел
// n2 - конечный узел
// return - расстояние между узлами
	int getDistance(int n1, int n2)
	{
		if(n1 == n2) return 0;

		reset();

		queue<int> q; // очередь обработки узлов
		q.push(n1);

		while(!q.empty())
		{
			int v = q.front();
			q.pop();
			for(unsigned int i = 0; i < nodes[v].size(); i++) // сигнал всем дочерним узлам
			{
				int v2 = nodes[v][i].id; // номер дочернего узла
				if(v2 == nodes[v].idPrev) continue; // если совпадает с источником сигнала - пропустить

				nodes[v2].x = nodes[v][i].len + nodes[v].x; // текущее расстояние
				nodes[v2].idPrev = v; // записать источник сигнала

				if(v2 == n2) return nodes[v2].x; // достигнут конечный узел

				q.push(v2); // в очередь обработки
			}
		}

		return 0;
	}

// сброс
	void reset()
	{
		for(int i = 0; i < Nn; i++)
		{
			nodes[i].reset();
		}
	}

private:

	CNode* nodes; // массив узлов
	int Nn; // число узлов
};


int main(int argc, char* argv[])
{
	int i;
	int N = 0;

// число узлов
	scanf("%d", &N);
	if(N <= 0) return 0;

// создание графа
	CGraph gr(N);
	for(i = 0; i < N-1; i++)
	{
		int n1, n2, len;
		scanf("%d %d %d", &n1, &n2, &len);
		gr.addEdge(n1-1, n2-1, len);
	}

// число пар узлов, между которыми требутся определить расстояние
	scanf("%d", &N);

// результат
	vector<int> dist;

// получение расстояния для всех пар узлов
	for(i = 0; i < N; i++ )
	{
		int n1, n2;
		scanf("%d %d", &n1, &n2);
		dist.push_back(gr.getDistance(n1-1, n2-1));
	}

// вывод результата
	for(i = 0; i < N; i++ )
	{
		printf("%d\n", dist[i]);
	}

	return 0;
}

