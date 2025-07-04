#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
/*
Класс, описывающий вершины дерева. Нужен для удобства подсчета расстояния между вершинами.
*/
class Node
{
    public: 
    unsigned int num;      // номер вершины
    Node* parent;          // непосредственный родитель
    unsigned int weight;   // вес до родителя (если есть, иначе 0)
    Node()
    {
        Node::weight = 0; 
    };
    ~Node();
};


vector<Node*> p;                // массив с вершинами
unsigned int n,l;               // кол-во вершин и длина массива для двоичного подъема
unsigned int timer = 0;                     // таймеры для поиска 
vector<unsigned int> tin, tout;             // в глубину
vector< vector<unsigned int> > up, graph;
vector<char> visited;

/*
Функция добавления связей, создает вершины при необходимости
и ставит указатель на родителя.
*/
void addConnection(unsigned int from, unsigned int to, unsigned int w)
{
    if (!p[from]) 
    {
        p[from] = new Node();
        p[from]->num = from;
    }
    if (!p[to]) 
    {
        p[to] = new Node();
        p[to]->num = to;
    }
    p[to]->parent = p[from];            
    p[to]->weight = w;
}

/*
Поиск в глубину с учетом времени захода и выхода из вершины 
(для определения является ли одна вершина предком другой), а
так же составлением "карты" для двоичного подъема
*/
void dfs(unsigned int curr, unsigned int pr = 0)
{
    visited[curr] = true;
    tin[curr] = ++timer;
    up[curr][0] = pr;
    for (unsigned int i = 1; i<=l; ++i)
        up[curr][i] = up[up[curr][i-1]][i-1];         // массив для двоичного подъема
    for (size_t i=0; i<graph[curr].size(); ++i) {     // Переход в след. вершину
		unsigned int next = graph[curr][i];
		if (!visited[next])
			dfs (next, curr);
	}
    tout[curr] = ++timer;
}

// Определение является ли одна вершина предком другой
bool upper(unsigned int a, unsigned int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

// Нахождение общего предка
int lca(unsigned int a, unsigned int b) {
	if (upper (a, b))  return a;
	if (upper (b, a))  return b;
	for (int i=l; i>=0; --i)
		if (!upper (up[a][i], b))
			a = up[a][i];
	return up[a][0];
}

int main(int argc, char* argv[])
{
    unsigned int i,w;
    unsigned int a,b,sum; 
    Node* first;
    Node* second;
    cin >> n;                           // Кол-во вершин в дереве
    if (n <= 1)
    {
        cin >> n;                       // 1 вершина - не дерево :p
        for (i=0; i<n; ++i) cout << "0" << endl;
    }
    else
    {
        p.resize(n); visited.resize(n); // устанавливаем размерность массивов
        tin.resize(n); tout.resize(n);
        graph.resize(n); up.resize(n);
        l=1;
        while ((1<<l) <= n)  ++l;       // находим глубину для двоичного подъема
        for (i=0; i<n-1; ++i)   
        {
            cin >> a;                  // Читаем родителя, предка и вес. Заполняем дерево
            cin >> b;     
            cin >> w;
            addConnection(a-1,b-1,w);
            graph[a-1].push_back(b-1);
            up[i].resize (l+1);         // Заодно устанавливаем размер для массива предков
        }
        up[i].resize (l+1);             // последняя вершина
        dfs(0);
        cin >> n;                      
        for (i = 0; i<n; ++i)
        {
            cin >> a; --a;   
            cin >> b; --b;             
            w = lca(a,b);               // Находим наименьшего общего предка
            sum = 0;
            first = p[a];
            second = p[b];
            while (first->num != w)     // Идем по родителям пока не дойдем до общего предка
            {
                sum += first->weight;
                first = first->parent;
            }
            while (second->num != w)
            {
                sum += second->weight;
                second = second->parent;
            }
            cout << sum << endl;
        }
    }
    return 0;
}
