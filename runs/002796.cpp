#include <iostream>
#include <vector>
#include <utility>
#include <stdio.h>

using namespace std;

int max_n;	/*Количество вершин*/
int amt_q;	/*Количество запросов*/
int x,y,l;	/*Характеристика ребра*/
vector< vector<int> > dist;	/*Матрица смежности с расстояниями*/

vector< pair<int,int> > query;	/*Запросы*/
vector< vector<int> > graph;	/*Матрица связей*/

vector<bool> isUsed;		/*Флаг использованности вершины*/
vector<int> visited;		/*Индексы посещенных вершин*/
time_t aTime;




void initGraph(){
	dist.resize(max_n);
	graph.resize(max_n);
	isUsed.resize(max_n,false);
	for(int i=0;i<max_n;i++){
		dist[i].resize(max_n,-1);
	}
}

void initQuery(){
	query.resize(amt_q);
}
void dfs(int v){
	isUsed[v] = true;
	visited.push_back(v);
	/*Просмотр связей конкретной вершины v*/
	for(vector<int>::iterator next = graph[v].begin(),end = graph[v].end();next!=end;next++){
		/*Если есть связь с вершиной, которая ранее не посещалась*/
		if(!isUsed[*next]){	
			/*Простановка расстояний от посещенных вершин до непосещенного потомка*/
			for(vector<int>::iterator wasVisited = visited.begin(),end1=visited.end();wasVisited!=end1;wasVisited++){
				if(*wasVisited!=v)
						dist[*wasVisited][*next]=dist[*next][*wasVisited]=dist[v][*next]+dist[*wasVisited][v];			
			}
			/*Переход в очередного потомка*/
			dfs(*next);
		}
	}
}

int main(){


	/*Чтение количества вершин*/
	scanf("%d",&max_n);
	
	/*Выделение памяти для матрицы*/
	initGraph();

	/*Чтение параметров ребер*/
	for(int i = 0; i != max_n-1; i++){
		scanf("%d %d %d",&x,&y,&l);
		--x,--y;
		dist[x][y] = dist[y][x]= l;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	/*Чтение количества запросов*/
	scanf("%d",&amt_q);
	/*Выделение памяти для запросов*/
	initQuery();

	/*Чтение запросов*/
	for(int i=0;i!=amt_q;i++){
		scanf("%d %d",&x,&y);
		query[i].first=--x;
		query[i].second=--y;
	}

	dfs(0);
	/*Выполнение запросов*/
	for(int i=0;i!=amt_q;i++){
		if(query[i].first!=query[i].second)
			cout<<dist[query[i].first][query[i].second]<<endl;
		else
			cout<<"0"<<endl;
	}
	//while(!kbhit());
	return 0;
}
