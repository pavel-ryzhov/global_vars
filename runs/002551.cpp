/*
 * В программе используется алгоритм Фарах-Колтона и Бендера
 * Made by Demidenok Vasily
 */

#include <map>
#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

using namespace std;

typedef unsigned short Weight;

class MyExcept
{
public:
	string message;
	MyExcept(string _mess) : message(_mess) {};
};

class Vertex;

class Edge
{
	/*
	 * Класс ребра в графе.
	 */
	Vertex& _one;
	Vertex& _two;

public:
	Weight weight;	// Вес ребра

	Edge(Vertex &one, Vertex &two, Weight weight): _one(one), _two(two), weight(weight) {};
	Vertex & another(const Vertex &vertex)
	{
		// Возвращаем противоположную вершину
		return (&vertex == &_one) ? _two : _one;
	}
	virtual ~Edge(){};
};

class Vertex
{
	/*
	 * Класс вершины в графе.
	 */
public:
	vector<Edge *> edges;				// Связи данной вершины ( в том числе и родительская )
	Edge *parentEdge;					// Родительская связь
	unsigned short valueVertex;			// Номер вершины

	Vertex(unsigned short _valueVertex) : parentEdge(NULL), valueVertex(_valueVertex) {};

	int calculateToParent(unsigned short vertexNum)
	{
		// Считаем путь до вершины VertexNum при условии что это один из родителей. Иначе возвращаем -1.
		if (valueVertex == vertexNum)
			return 0;

		if (parentEdge == NULL)
			throw MyExcept("Error: Doesn't have parent, but is not root.");

		int size = 0;
		Vertex *parentVertex = NULL;
		Weight weight;
		Edge *parent 	= parentEdge;

		while( parent != NULL )
		{
			parentVertex 	= &(parent->another(*this));
			weight 			= parent->weight;
			size += weight;
			if (parentVertex->valueVertex == vertexNum)
				return size;

			parent = parentVertex->parentEdge;
		}
		return -1;
		throw MyExcept("Error: Vertex was not found.");
	}

	virtual ~Vertex() { }
};

void selectThreeArgs(	unsigned short &vertexOne, unsigned short &vertexTwo,
						Weight &edgeWeight, string &line)
{
	/*
	 * Вытаскивает из строки два параметра
	 */

	size_t probel1 = line.find(' ', 0);
	size_t probel2 = line.find(' ', probel1+1);

	if ((probel1 != string::npos) && (probel2 != string::npos))
	{
		vertexOne = atoi(line.substr(0, probel1).c_str());
		vertexTwo = atoi(line.substr(probel1, probel2).c_str());
		edgeWeight = atoi(line.substr(probel2).c_str());
		return;
	}
	throw MyExcept("Error: Could not read parametrs from the string");
}
void selectTwoArgs(	unsigned short &vertexOne, unsigned short &vertexTwo, string &line)
{
	/*
	 * Вытаскивает из строки два параметра
	 */

	size_t probel = line.find_last_of(' ');

	if (probel != string::npos)
	{
		vertexOne = atoi(line.substr(0, probel).c_str());
		vertexTwo = atoi(line.substr(probel).c_str());
		return;
	}
	throw MyExcept("Error: Could not read parametrs from the string");
}
////////////////////////////////////////////////////////////////////////////////		LCA
namespace LCA
{
	const int MAXN = 40000;										// В нашем случае не больше 40 000 N
	const int MAXLIST = MAXN * 2;								// Максимальное количество вершин, которое может появиться в A/
	const int LOG_MAXLIST = 17;									// log2(MAXLIST)
	const int SQRT_MAXLIST = 447;								// sqrt(MAXLIST)
	const int MAXBLOCKS = MAXLIST / ((LOG_MAXLIST+1)/2) + 1;

	unsigned short	*h;											// Высота в дереве
	unsigned short 	*aPos;										// Ближайшая позиция элемента
	vector<unsigned short> 	a;									// Порядок элементов при проходе в глубину
	int block;

	int bt[MAXBLOCKS][LOG_MAXLIST+1]; 							// sparse table on blocks (relative minimum positions in blocks)
	int bhash[MAXBLOCKS]; 										// block hashes
	int brmq[SQRT_MAXLIST][LOG_MAXLIST/2][LOG_MAXLIST/2]; 		// rmq inside each block, indexed by block hash
	int log2[2*MAXN]; 											// precalced logarithms (floored values)

	void 	initializeTree(Vertex* parentVertex, Vertex &vertex, unsigned short glubina);
	void 	initializeLca (unsigned short vertexAmount, Vertex &root);
	int 	lcaAsk (unsigned short v1, unsigned short v2);
	int 	lcaInBlock (int bl, int l, int r);
	int  	log (int n);
	int 	min_h (int i, int j);

}

void LCA::initializeTree(Vertex* parentVertex, Vertex &vertex, unsigned short glubina)
{
	// Проходим по графу и выставляем там где надо родительские связи
	// Обход в глубину.

	LCA::h[vertex.valueVertex] 		= glubina;				//	Записали глубину вершины
	LCA::aPos[vertex.valueVertex] 	= LCA::a.size();		// 	Записали первое появление в списке
	LCA::a.push_back(vertex.valueVertex);					//  Добавили в порядок обхода

	for(vector<Edge *>::iterator it = vertex.edges.begin(); it != vertex.edges.end(); it++)
	{
		Vertex &child = (*it)->another(vertex);
		if (&child == parentVertex)			// Если связь с родителем
		{
			vertex.parentEdge = (*it);
			continue;
		}

		initializeTree(&vertex, child, glubina+1);
		LCA::a.push_back(vertex.valueVertex);	// Добавили в порядок обхода
		}
}

void LCA::initializeLca(unsigned short vertexAmount, Vertex &root)
{
	h 		= new unsigned short[vertexAmount];
	aPos 	= new unsigned short[vertexAmount];

	// Формируем дерево из связного графа
	initializeTree(NULL, root, 0);

	int sz = a.size();
	block = (log(sz) + 1) / 2;
	int blocks = sz / block + (sz % block ? 1 : 0);

	// Рассчитываем sparse таблицу
	memset (bt, 255, sizeof bt);
	for (int i=0, bl=0, j=0; i<sz; ++i, ++j)
	{
		if (j == block)
			j = 0,  ++bl;
		if (bt[bl][0] == -1 || min_h (i, bt[bl][0]) == i)
			bt[bl][0] = i;
	}
	for (int j=1; j<=log(sz); ++j)
		for (int i=0; i<blocks; ++i)
		{
			int ni = i + (1<<(j-1));
			if (ni >= blocks)
				bt[i][j] = bt[i][j-1];
			else
				bt[i][j] = min_h (bt[i][j-1], bt[ni][j-1]);
		}

	// Рассчитываем хеш
	memset (bhash, 0, sizeof bhash);
	for (int i=0, bl=0, j=0; i<sz||j<block; ++i, ++j)
	{
		if (j == block)
			j = 0,  ++bl;
		if (j > 0 && (i >= sz || min_h (i-1, i) == i-1))
			bhash[bl] += 1<<(j-1);
	}

	// Расчитываем RMQ внутри каждого уникального блока
	memset (brmq, 255, sizeof brmq);
	for (int i=0; i<blocks; ++i)
	{
		int id = bhash[i];
		if (brmq[id][0][0] != -1)  continue;
		for (int l=0; l<block; ++l)
		{
			brmq[id][l][l] = l;
			for (int r=l+1; r<block; ++r)
			{
				brmq[id][l][r] = brmq[id][l][r-1];
				if (i*block+r < sz)
					brmq[id][l][r] = min_h (i*block+brmq[id][l][r], i*block+r) - i*block;
			}
		}
	}

	// precalc logarithms
	for (int i=0, j=0; i<sz; ++i)
	{
		if (1<<(j+1) <= i)
			++j;
		log2[i] = j;
	}
}

int LCA::log(int n)
{
	int res = 1;
	while (1<<res < n)
		++res;
	return res;
}

inline int LCA::min_h (int i, int j)
{
	return h[a[i]] < h[a[j]] ? i : j;
}

inline int LCA::lcaInBlock (int bl, int l, int r)
{
	// Находим соответствующее RMQ
	return brmq[bhash[bl]][l][r] + bl*block;
}

int LCA::lcaAsk (unsigned short v1, unsigned short v2)
{
	// Вычисляем самого нижнего потомка

	unsigned short l = aPos[v1];
	unsigned short r = aPos[v2];

	if (l > r)
		swap (l, r);

	int bl = l/block,  br = r/block;
	if (bl == br)
		return a[lcaInBlock(bl, l%block, r%block)];

	int ans1 = lcaInBlock(bl,l%block,block-1);
	int ans2 = lcaInBlock(br,0,r%block);
	int ans = min_h (ans1, ans2);

	if (bl < br - 1)
	{
		int pw2 = log2[br-bl-1];
		int ans3 = bt[bl+1][pw2];
		int ans4 = bt[br-(1 << pw2)][pw2];
		ans = min_h (ans, min_h (ans3, ans4));
	}

	return a[ans];
}

/////////////////////////////////////////////////////////////////////////////////

int main()
{
	// Так как не факт что названия вершин идут строго последовательно и максимальный номер вершины не
	// превосходит их количество соединяем входной номер вершины и порядковый номер вершины

	map<unsigned short, Vertex *> 	relativeVertex;		// Связь номеров вершин со входа
	Vertex *root = NULL;								// Корень графа
	vector<Vertex *> 	vertexes;						// Вершины графа

	unsigned short vertexAmount = 0;	// Количество вершин в графе.
	unsigned short stepsAmount = 0;		// Количество шагов вывода
	unsigned short counterVert = 0, counterStep = 0;
	int counter = 0;
	string line;

	try
	{
		while(cin)
		{
			getline(cin, line);

			if (line.empty()) continue;

			if (vertexAmount == 1 && root == NULL)
			{
				Vertex *p_vertexFirst = new Vertex(counter);
				vertexes[counter] = p_vertexFirst;
				relativeVertex[1] = p_vertexFirst;
				root = p_vertexFirst;
			}

			if (vertexAmount == 0)
			{
				vertexAmount = atoi(line.c_str());
				vertexes.resize(vertexAmount);
			}
			else if (counterVert < vertexAmount - 1)
			{
				// Вырезаем из строки вершины и ребро
				unsigned short vertexOne, vertexTwo;
				Weight edgeWeight;
				selectThreeArgs(vertexOne, vertexTwo, edgeWeight, line);

				// Формируем граф

				Vertex *p_vertexFirst = NULL, *p_vertexSecond = NULL;
				if (relativeVertex.find(vertexOne) == relativeVertex.end())
				{
					p_vertexFirst = new Vertex(counter);
					vertexes[counter] 			= p_vertexFirst;
					relativeVertex[vertexOne] 	= p_vertexFirst;
					counter++;
				}
				else
					p_vertexFirst = relativeVertex[vertexOne];

				if (relativeVertex.find(vertexTwo) == relativeVertex.end())
				{
					p_vertexSecond = new Vertex(counter);
					vertexes[counter] = p_vertexSecond;
					relativeVertex[vertexTwo] = p_vertexSecond;
					counter++;
				}
				else
					p_vertexSecond = relativeVertex[vertexTwo];

				Edge   *edge	= new Edge(*p_vertexFirst, *p_vertexSecond, edgeWeight);
				p_vertexFirst->edges.push_back(edge);
				p_vertexSecond->edges.push_back(edge);

				// Первая вершина и есть корень графа
				if (root == NULL)
					root = p_vertexFirst;

				counterVert++;
			}
			else if (stepsAmount == 0)
			{
				// Инициализируем граф и LCA
				stepsAmount = atoi(line.c_str());
				LCA::initializeLca(vertexAmount, *root);
			}
			else if (counterStep < stepsAmount)
			{
				// Отвечаем на вопросы

				unsigned short relVertexOne, relVertexTwo;
				unsigned short vertexOne, vertexTwo;

				selectTwoArgs(relVertexOne, relVertexTwo, line);

				// Вытаскиваем
				vertexOne = (relativeVertex[relVertexOne])->valueVertex;
				vertexTwo = (relativeVertex[relVertexTwo])->valueVertex;

				unsigned short vetrexParent = LCA::lcaAsk(vertexOne, vertexTwo);

				// Расчёт пути
				int weight = 0;
				weight += vertexes[vertexOne]->calculateToParent(vetrexParent);
				weight += vertexes[vertexTwo]->calculateToParent(vetrexParent);
				cout << weight <<endl;
			}

		}
		delete [] LCA::h;
		delete [] LCA::aPos;
	}
	catch (MyExcept except)
	{
		std::cerr << except.message;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}



