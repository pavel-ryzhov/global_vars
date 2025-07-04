#include <iostream>
#include <vector>
#include <utility>
#include <stdio.h>

using namespace std;

int max_n;	/*Количество вершин*/
int amt_q;	/*Количество запросов*/
int x,y,l;	/*Характеристика ребра*/
vector< vector<int> > dist;	/*Матрица смежности*/

vector< pair<int,int> > query;	/*Запросы*/
vector< vector<int> > graph;

vector<bool> isUsed;		/*Флаг использованности вершины*/

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
	/*Просмотр связей конкретной вершины v*/
	for(vector<int>::iterator it = graph[v].begin(),end = graph[v].end();it!=end;it++){
		/*Если есть связь с вершиной, которая ранее не посещалась*/
		if(!isUsed[*it]){	
			/*Простановка расстояний от посещенных вершин до непосещенного потомка*/
			for(int j=0; j<max_n;j++){
				if(j!=v)
					if(isUsed[j])
						dist[j][*it]=dist[*it][j]=dist[v][*it]+dist[j][v];			
			}
			/*Переход в очередного потомка*/
			dfs(*it);
		}
	}
}

int main(){

	
	/*Чтение количества вершин*/
	scanf("%d",&max_n);
	
	/*Выделение памяти для матрицы*/
	initGraph();

	/*Чтение параметров ребер*/
	for(int i = 0; i < max_n-1; i++){
		scanf("%d %d %d",&x,&y,&l);
		--x,--y;
		dist[x][y] = dist[y][x]= l;
		graph[x].push_back(y);
	}
	/*Чтение количества запросов*/
	scanf("%d",&amt_q);
	/*Выделение памяти для запросов*/
	initQuery();

	/*Чтение запросов*/
	for(int i=0;i<amt_q;i++){
		scanf("%d %d",&x,&y);
		query[i].first=--x;
		query[i].second=--y;
	}

	dfs(0);
	/*Выполнение запросов*/
	for(int i=0;i<amt_q;i++){
		if(query[i].first!=query[i].second)
			cout<<dist[query[i].first][query[i].second]<<endl;
		else
			cout<<"0"<<endl;
	}
	//while(!kbhit());
	return 0;
}
