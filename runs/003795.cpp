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

	int id;	 // узел, на который смотрит данное ребро
	int len; // длина ребра
};

// узел
class CNode : public vector<CEdge>
{
public:
// конструктор
	CNode()
	{
		x = 0;
		idPar = -1;
		mark = 0;
	}

	int x;		// расстояние до узла
	int idPar;	// узел-родитель
	int mark;	// метка о прохождении через узел
};

// граф 
class CGraph
{
public:
// конструктор
// N - число узлов
	CGraph(int N)
	{
		currMark = 0;
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

// получение расстояния между узлами
// n1 - начальный узел
// n2 - конечный узел
// return - расстояние между узлами
	int getDistance(int n1, int n2)
	{
		if(n1 == n2) return 0;

		currMark++; // новый поиск => другая метка

		gotoRoot(n1);
		int n3 = findRootWay(n2);

		return nodes[n1].x + nodes[n2].x - 2*nodes[n3].x;
	}

// рассчитать расстояния до узлов относительно корня
	void calcRootDistance()
	{
		queue<int> q; // очередь обработки узлов
		q.push(0);

		while(!q.empty())
		{
			int v = q.front();
			q.pop();
			for(unsigned int i = 0; i < nodes[v].size(); i++) // сигнал всем дочерним узлам
			{
				int v2 = nodes[v][i].id; // номер дочернего узла
				if(v2 == nodes[v].idPar) continue; // если совпадает с источником сигнала - продолжить

				nodes[v2].x = nodes[v][i].len + nodes[v].x; // текущее расстояние
				nodes[v2].idPar = v; // записать источник сигнала

				q.push(v2); // в очередь обработки
			}
		}
	}

private:	

// пометить все вершины от заданного узла до корня
// id - исходный узел
	void gotoRoot(int id)
	{
		while(id)
		{
			nodes[id].mark = currMark;
			id = nodes[id].idPar;
		}
	}

// идти к корню, начиная от заданного узла, пока не встретится метка
// id - исходный узел
// return - первый встретившийся узел с меткой
	int findRootWay(int id)
	{
		while(id)
		{
			if(nodes[id].mark == currMark) return id;
			id = nodes[id].idPar;
		}
		return 0;
	}

	CNode* nodes; // массив узлов
	int Nn; // число узлов
	int currMark; // текущее значение метки
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

// измерение расстояний от корня дерева
	gr.calcRootDistance();

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

