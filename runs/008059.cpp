#include <iostream>
#include <vector>
using namespace std;
int n, l;

vector < vector<int> > g;//граф
vector < vector<int> > costG;//Стоимость путей
vector<char> used;	//Использованные вершины
vector<int> tin;	//Время захода в вершину
vector<int> tout;	//Время выхода
int timer;
vector < vector<int> > up;	//Предки
struct PaitOfVertex
{
	int a;
	int b;
};
void dfs (int v, int p = 0) 
{
	used[v] = true;
	tin[v] = ++timer;
	up[v][0] = p;
	for (int i=1; i<=l; ++i)
		up[v][i] = up[up[v][i-1]][i-1];
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (!used[to])
			dfs (to, v);
	}
	tout[v] = ++timer;
}

bool upper (int a, int b) 
{
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b) 
{
	if (upper (a, b))  return a;
	if (upper (b, a))  return b;
	for (int i=l; i>=0; --i)
		if (! upper (up[a][i], b))
			a = up[a][i];
	return up[a][0];
}

int Cost(int Vertex,int A, int B)
{
	
	int cost=0;
	if(A!=Vertex)
	for (int i=l; i>=0; --i)
	{
		cost+=costG[A][up[A][0]];
		if (up[A][0]!=Vertex)
			A = up[A][0];
		else break;
	}
	if(B!=Vertex)
	for (int i=l; i>=0; --i)
	{
		cost+=costG[B][up[B][0]];
		if (up[B][0]!=Vertex)
			B = up[B][0];
		else break;
	}
	return cost;
}
int main(int argc, char* argv[])
{
	cin>>n;	//кол-во вершин
	//Получаем информацию о графе
	g.resize(n);
	costG.resize(n);
	for(int i=0;i<n;i++)
	{
		g[i].resize(n);
		costG[i].resize(n);
	}

	for(int i=0;i<n-1;i++)
	{
		int vA,vB,vC;
		cin>>vA>>vB>>vC;
		g[vA-1][vB-1]=vB-1;
		g[vB-1][vA-1]=vA-1;
		costG[vA-1][vB-1]=vC;
		costG[vB-1][vA-1]=vC;
	}
	//Получаем информацию о запросах
	int M=0;
	cin>>M;
	PaitOfVertex *Vertex=new PaitOfVertex[M];
	for(int i=0;i<M;i++)//Получаем пары вершин, между которыми необходимо найти расстояние
		{
			cin>>Vertex[i].a>>Vertex[i].b;
			Vertex[i].a-=1;
			Vertex[i].b-=1;
		}	
	//Препроцессинг
	used.resize (n),  tin.resize (n),  tout.resize (n),  up.resize (n);
	l = 1;
	while ((1<<l) <= n)  ++l;
	for (int i=0; i<n; ++i)  up[i].resize (l+1);
	dfs (0);

	//Вычисляем  и выводим стоимость пути 
	for(int i=0;i<M;i++)
	{
		int res = lca (Vertex[i].a ,Vertex[i].b);
		cout<<Cost(res,Vertex[i].a ,Vertex[i].b)<<endl;
	}
	return 0;
}