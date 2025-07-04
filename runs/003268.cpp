// Problem2.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib>


#define MAXN 40000											//Максимальное число вершин в графе
#define FILENAMESIZE 256									//Максимальная длина имени файла

//Структура для представления графа
typedef struct Adjacency
{
	int Vertex_Num;
	int Edge_Weight;
	Adjacency(int a, int b) {Vertex_Num = a; Edge_Weight = b;};
} Adj;

//Структура для представления запросов
typedef struct Question
{
	int Vertex_Num;
	int Quest_Num;
	Question(int a, int b) {Vertex_Num = a; Quest_Num = b;};
} Quest;

typedef std::pair<const int, Quest> make_pair;

std::vector <std::vector<Adj> > Graph;					//Граф
std::multimap <int, Quest> Questions;					//Запросы
std::vector <int> question_answer;						//Ответы на запросы

//Система непересекающихся множеств
class DSU
{
private:
	std::vector <int> P;
	std::vector <int> ancestor;
	void Init_DSU (int N);
public:
	DSU(){Init_DSU(0);};
	DSU(int N) {Init_DSU(N);};
	~DSU(){};

	int Return_Ancestor(int i);
	void Make_Set(int X);
	int Find_Set(int X);
	void Unite(int X, int Y, int new_ancestor);
};
int DSU::Return_Ancestor(int i)
{
	return ancestor[i];
}
void DSU::Init_DSU (int N)
{
	P.resize(N);
	ancestor.resize(N);
	for (int i = 0; i < N; i++)
		P[i] = i;
}

void DSU::Make_Set(int X)
{
	P[X] = X;
}

int DSU::Find_Set(int X)
{
	if (P[X] == X) return X;
	return P[X] = Find_Set(P[X]);
}

void DSU::Unite(int X, int Y, int new_ancestor)
{
	X = Find_Set(X);
	Y = Find_Set(Y);

	if (rand() & 1)
	{
		P[Y] = X;
		ancestor[X] = new_ancestor;
	}
	else
	{
		P[X] = Y;
		ancestor[Y] = new_ancestor;
	}
}

//Поиск в глубину
void DFS(int v, int v_weight, std::vector < int > &color, std::vector < int > &vertexes, DSU &lca_dsu)
{
	lca_dsu.Make_Set(v);									//Добавляем вершину в СНМ
	color[v] = 1;											//Отмечаем, что вершина посещена
	
	for (size_t i = 0; i < Graph[v].size(); i++)
		if (!color[Graph[v][i].Vertex_Num]) 
		{
			//Счиаем вес вершины - длину пути до нее от корня
			vertexes[Graph[v][i].Vertex_Num] = v_weight + Graph[v][i].Edge_Weight;
			DFS(Graph[v][i].Vertex_Num, vertexes[Graph[v][i].Vertex_Num], color, vertexes, lca_dsu);
			lca_dsu.Unite(v, Graph[v][i].Vertex_Num, v);	//Добавляем вершину в множество её предка
		}

	size_t iCount_Limit = Questions.count(v);
	std::multimap <int, Quest>::iterator it = Questions.find(v);
	for (size_t i = 0; i < iCount_Limit; i++)
		if (color[it->second.Vertex_Num] && question_answer[it->second.Quest_Num] == -1) 
		{
			int LCA = lca_dsu.Return_Ancestor(lca_dsu.Find_Set(it->second.Vertex_Num));
			//Ответ(a,b) = w(a) - w(LCA(a,b)) + w(b) - w(LCA(a,b))
			question_answer[it->second.Quest_Num] = vertexes[v] + vertexes[it->second.Vertex_Num] - 2*vertexes[LCA];
			it++;
		}
}

int main(int argc, char* argv[])
{
	int N = 0;												//Число вершин в графе
	int Q = 0;												//Число запросов

	std::cin>>N;											//Ввод количества вершин в графе

	//Инициализация графа
	std::vector <int> color(N);								//Посетил ли алгоритм DFS вершину (1) или нет (0)		
	std::vector <int> vertexes(N);							//Вес пути до вершины от предка
	DSU lca_dsu(N);											//Система непересекающихся множеств

	color.empty();											//Заполнение массивов
	vertexes.empty();										//нулями
	
	Graph.resize(N);				
	for (int i = 0; i < N - 1; i++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		Graph[a - 1].push_back(Adj(b - 1,c));
		Graph[b - 1].push_back(Adj(a - 1,c));
	}

	std::cin>>Q;											//Ввод количества запросов

	//Инициализация запросов
	question_answer.resize(Q);								//Массив ответов на запросы
	question_answer.empty();

	for (int i = 0; i < Q; i++)
	{
		int a, b;
		std::cin >> a >> b;
		question_answer[i] = -1;
		Questions.insert( make_pair(a - 1,Quest(b - 1, i)));
		Questions.insert( make_pair(b - 1,Quest(a - 1, i)));
	}


	DFS(0, 0, color, vertexes, lca_dsu);

	//Вывод результата
	for (int i = 0; i < Q; i++)
		std::cout<<question_answer[i]<<std::endl;

	return 0;
}