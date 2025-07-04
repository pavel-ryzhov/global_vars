#include <iostream>
#include <vector>
#include <utility>
#include<stdio.h>

using namespace std;

int max_n;	/*Количество вершин*/
int amt_q;	/*Количество запросов*/
int x,y,l;	/*Характеристика ребра*/
vector< vector<int> > graph;	/*Матрица смежности*/

vector< pair<int,int> > query;	/*Запросы*/

vector<bool> isUsed;		/*Флаг использованности вершины*/




void initGraph(){
	graph.resize(max_n);
	isUsed.resize(max_n,false);
	for(int i=0;i<max_n;i++){
		graph[i].resize(max_n,100000);
	}
}

void initQuery(){
	query.resize(amt_q);
}
void dfs(int v){
	isUsed[v] = true;
	/*Просмотр связей конкретной вершины v*/
	for(int i=0;i<max_n;i++){
		/*Если есть связь с вершиной, которая ранее не посещалась*/
		if(graph[v][i]!=100000 && !isUsed[i]){	
			/*Простановка расстояний от посещенных вершин до непосещенного потомка*/
			for(int j=0; j<max_n;j++){
				if(j!=v)
					if(isUsed[j])
						graph[j][i]=graph[i][j]=graph[v][i]+graph[j][v];			
			}
			/*Переход в очередного потомка*/
			dfs(i);
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
		graph[x][y] = graph[y][x]= l;
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
		cout<<graph[query[i].first][query[i].second]<<endl;
	}
	//while(!kbhit());
	return 0;
}
