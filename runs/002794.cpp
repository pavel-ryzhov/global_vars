#include <iostream>
#include <vector>
#include <utility>
#include <stdio.h>

using namespace std;

int max_n;	/*���������� ������*/
int amt_q;	/*���������� ��������*/
int x,y,l;	/*�������������� �����*/
vector< vector<int> > dist;	/*������� ���������*/

vector< pair<int,int> > query;	/*�������*/
vector< vector<int> > graph;

vector<bool> isUsed;		/*���� ���������������� �������*/

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
	/*�������� ������ ���������� ������� v*/
	for(vector<int>::iterator it = graph[v].begin(),end = graph[v].end();it!=end;it++){
		/*���� ���� ����� � ��������, ������� ����� �� ����������*/
		if(!isUsed[*it]){	
			/*����������� ���������� �� ���������� ������ �� ������������� �������*/
			for(int j=0; j<max_n;j++){
				if(j!=v)
					if(isUsed[j])
						dist[j][*it]=dist[*it][j]=dist[v][*it]+dist[j][v];			
			}
			/*������� � ���������� �������*/
			dfs(*it);
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
		dist[x][y] = dist[y][x]= l;
		graph[x].push_back(y);
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
		if(query[i].first!=query[i].second)
			cout<<dist[query[i].first][query[i].second]<<endl;
		else
			cout<<"0"<<endl;
	}
	//while(!kbhit());
	return 0;
}
