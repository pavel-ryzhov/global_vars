#include <iostream>
using namespace std;


struct Point {
	int hop;
        int cost;
        Point *next;
};

class Graph{
public:
	int N;
	Point *point[40000];
	bool flag[40000];
	long l[40000];
	
	Graph();
	void Init();
	void AddNewWay(int A, int B, int C);
	void GraphPrint();
	void WayAB(int a, int b);
	void FlushFlag();
	void FillFlag();
	void FlushL();
};

Graph::Graph(){
	for(int i=0; i<40000; i++){
		point[i]= new Point;
		(*point)[i].hop=0;
		(*point)[i].cost=0;
		(*point)[i].next = 0;
	}
}

void Graph::FlushFlag(){ for(int i=1; i<=N; flag[i++]=0);}

void Graph::FillFlag(){ for(int i=1; i<=N; flag[i++]=1);}

void Graph::FlushL() {for(int i=1; i<=N; l[i++]=-1);}

void Graph::AddNewWay(int A, int B, int C){
	Point *runner=point[A];
        while( (*runner).next ) runner=(*runner).next;
        (*runner).hop=B;
        (*runner).cost=C;
        (*runner).next= new Point;
        runner=(*runner).next;
        (*runner).hop=0;
        (*runner).cost=0;
	(*runner).next=0;
}

void Graph::Init(){
	int pa, pb, c;
	cin >> N;
	for(int i=0; i<N-1; i++){
		cin >> pa >> pb >> c;
		AddNewWay(pa, pb, c);
		AddNewWay(pb, pa, c);
	}
}

void Graph::GraphPrint(){
	for(int i=1; i<=N; i++){
		Point *r=point[i];
		while((*r).next){
			cout << i << ' ' << (*r).hop << ' ' << (*r).cost << '\n';
			r=(*r).next;
		}
	}
}

void Graph::WayAB(int a, int b){
	FillFlag();
	flag[a]=0; l[a]=0;
	int i=1; 
	Point *runner;
	while(l[b]<0) {
		if(l[i]>=0) {
			runner=point[i];
			while( (*runner).next ) {
				if (flag[(*runner).hop]) { 
					flag[(*runner).hop]=0;
					l[(*runner).hop]=l[i]+(*runner).cost;
				}
			runner=(*runner).next;
			}
			l[i]=-1;
		}
		if(++i>N) i=1;
	} 
	cout << l[b] << '\n';
}

/*void Graph::WayAB(int a, int b, long c){
	Point *runner=point[a];
	if ( a==b ){  
		cout << c << '\n';
		FillFlag();
	}
	flag[a]=1;
	while( (*runner).next ) {
		if (!flag[(*runner).hop]) { 
//			cout << (*runner).hop << '-';
			WayAB((*runner).hop, b, c+(*runner).cost);
		}
		runner=(*runner).next;
	}
}
*/




int main(){
	int A, B, M;
	Graph graph;

	graph.Init();
//	graph.GraphPrint();

	cin >> M;
	for(int i=1; i<=M; i++){
		cin >> A >> B;
		graph.FlushL();
		graph.WayAB(A, B);
	}
    	return 0;
}
