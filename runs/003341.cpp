#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

unsigned int n,l;               // кол-во вершин и длина массива для двоичного подъема
unsigned int timer = 0;                     // таймеры для поиска 
vector<unsigned int> tin, tout;             // в глубину
vector< vector<unsigned int> > up, graph, weight;  // данные о весе выделим в отдельный массив            
vector<char> visited;


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
    unsigned int i,j,w;
    unsigned int a,b,sum; 
    cin >> n;                            // Кол-во вершин в дереве
    if (n <= 1)
    {
        cin >> n;                        // 1 вершина - не дерево :p
        for (i=0; i<n; ++i) cout << "0" << endl;
    }
    else
    {
        visited.resize(n);               // устанавливаем размерность массивов
        tin.resize(n); tout.resize(n);
        graph.resize(n); up.resize(n);
        weight.resize(n);
        l=1;
        while ((1<<l) <= n)  ++l;        // находим глубину для двоичного подъема
        for (i=0; i<n-1; ++i)   
        {
            cin >> a;                    // Читаем родителя, предка и вес. Заполняем дерево
            cin >> b;     
            cin >> w;
            graph[a-1].push_back(b-1);
            graph[b-1].push_back(a-1);
            weight[a-1].push_back(w);
            weight[b-1].push_back(w);
            up[i].resize (l+1,-1);       // Заодно устанавливаем размер для массива предков
        }
        up[i].resize (l+1);              // последняя вершина
        dfs(0);
        cin >> n;                      
        for (i = 0; i<n; ++i)
        {
            cin >> a; --a;   
            cin >> b; --b;             
            w = lca(a,b);                // Находим наименьшего общего предка
            sum = 0;
            while (a != w)                          // идем по родителям и прибавляем вес
            {                                       // пока не дойдем но наименьшего общего предка
                for (j=0; j<graph[a].size(); ++j)   
                    if (graph[a][j] == up[a][0])    
                    {
                        sum += weight[a][j];
                        break;
                    }
                a = up[a][0]; 
            }
            while (b != w)                          // и для второй вершины
            {                                       
                for (j=0; j<graph[b].size(); ++j)    
                    if (graph[b][j] == up[b][0])    
                    {
                        sum += weight[b][j];
                        break;
                    }
                b = up[b][0]; 
            }
            cout << sum << endl;
        }
    }
    return 0;
}
