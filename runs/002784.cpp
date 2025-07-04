#include <iostream>
#include <vector>
#include <utility>
#include<stdio.h>

using namespace std;

int max_n;	/*���������� ������*/
int amt_q;	/*���������� ��������*/
int x,y,l;	/*�������������� �����*/
vector< vector<int> > graph;	/*������� ���������*/

vector< pair<int,int> > query;	/*�������*/

vector<bool> isUsed;		/*���� ���������������� �������*/




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
	/*�������� ������ ���������� ������� v*/
	for(int i=0;i<max_n;i++){
		/*���� ���� ����� � ��������, ������� ����� �� ����������*/
		if(graph[v][i]!=100000 && !isUsed[i]){	
			/*����������� ���������� �� ���������� ������ �� ������������� �������*/
			for(int j=0; j<max_n;j++){
				if(j!=v)
					if(isUsed[j])
						graph[j][i]=graph[i][j]=graph[v][i]+graph[j][v];			
			}
			/*������� � ���������� �������*/
			dfs(i);
		}
	}
}

int main(){

	/*������ ���������� ������*/
	scanf("%d",&max_n);
	
	/*��������� ������ ��� �������*/
	initGraph();

	/*������ ���������� �����*/
	for(int i = 0; i < max_n-1; i++){
		scanf("%d %d %d",&x,&y,&l);
		--x,--y;
		graph[x][y] = graph[y][x]= l;
	}
	/*������ ���������� ��������*/
	scanf("%d",&amt_q);
	/*��������� ������ ��� ��������*/
	initQuery();

	/*������ ��������*/
	for(int i=0;i<amt_q;i++){
		scanf("%d %d",&x,&y);
		query[i].first=--x;
		query[i].second=--y;
	}

	dfs(0);
	/*���������� ��������*/
	for(int i=0;i<amt_q;i++){
		cout<<graph[query[i].first][query[i].second]<<endl;
	}
	//while(!kbhit());
	return 0;
}
