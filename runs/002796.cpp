#include <iostream>
#include <vector>
#include <utility>
#include <stdio.h>

using namespace std;

int max_n;	/*���������� ������*/
int amt_q;	/*���������� ��������*/
int x,y,l;	/*�������������� �����*/
vector< vector<int> > dist;	/*������� ��������� � ������������*/

vector< pair<int,int> > query;	/*�������*/
vector< vector<int> > graph;	/*������� ������*/

vector<bool> isUsed;		/*���� ���������������� �������*/
vector<int> visited;		/*������� ���������� ������*/
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
	/*�������� ������ ���������� ������� v*/
	for(vector<int>::iterator next = graph[v].begin(),end = graph[v].end();next!=end;next++){
		/*���� ���� ����� � ��������, ������� ����� �� ����������*/
		if(!isUsed[*next]){	
			/*����������� ���������� �� ���������� ������ �� ������������� �������*/
			for(vector<int>::iterator wasVisited = visited.begin(),end1=visited.end();wasVisited!=end1;wasVisited++){
				if(*wasVisited!=v)
						dist[*wasVisited][*next]=dist[*next][*wasVisited]=dist[v][*next]+dist[*wasVisited][v];			
			}
			/*������� � ���������� �������*/
			dfs(*next);
		}
	}
}

int main(){


	/*������ ���������� ������*/
	scanf("%d",&max_n);
	
	/*��������� ������ ��� �������*/
	initGraph();

	/*������ ���������� �����*/
	for(int i = 0; i != max_n-1; i++){
		scanf("%d %d %d",&x,&y,&l);
		--x,--y;
		dist[x][y] = dist[y][x]= l;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	/*������ ���������� ��������*/
	scanf("%d",&amt_q);
	/*��������� ������ ��� ��������*/
	initQuery();

	/*������ ��������*/
	for(int i=0;i!=amt_q;i++){
		scanf("%d %d",&x,&y);
		query[i].first=--x;
		query[i].second=--y;
	}

	dfs(0);
	/*���������� ��������*/
	for(int i=0;i!=amt_q;i++){
		if(query[i].first!=query[i].second)
			cout<<dist[query[i].first][query[i].second]<<endl;
		else
			cout<<"0"<<endl;
	}
	//while(!kbhit());
	return 0;
}
