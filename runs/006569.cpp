// PROB:graf
// Lang: C++
//

//#include "stdafx.h"
#include<vector>
#include<iostream>
#include<list>
#include<stack>


using namespace std;

struct Edge {
	int v, w, wt;
	Edge (int v, int w, int wt): v(v), w(w), wt(wt) {}	
};

struct St {
	int v, wt;
};

class Graph
{	

	
	list<Edge>* adj;
	list<Edge>::iterator j;
	int Vcnt;
	int Ecnt;
	

public:
	Graph (int V): Vcnt(V), Ecnt(0) {adj=new list <Edge> [V]; }
	int V() const {return Vcnt; }
	void insert (Edge e) {
		adj[e.v].push_front(e);
		int v=e.w;
		int w=e.v;
		Edge k(v,w,e.wt);
		adj[e.w].push_front(k);
		Ecnt++;
	}

	~ Graph() {delete[] adj; }

	double dist(int a, int b) {
		int cnt=-1;
		vector <St> st(Vcnt);
		vector <int> ord (Vcnt,-1);
		stack <Edge> Q;
		Q.push (Edge(a,a,0));
		ord[a]=++cnt;
		while (!Q.empty()) {
			Edge e=Q.top();
			Q.pop();
			st[e.w].v=e.v; st[e.w].wt=e.wt;
			if (e.w==b) break;
			for (j=adj[e.w].begin(); j!=adj[e.w].end(); j++)
				if (ord[j->w]==-1) {
			    Q.push(*j); ord[j->w]=++cnt;
				}
		}
			
		int i=b; double d=st[i].wt;
		while (st[i].v!=a) {
			i=st[i].v;
			d+=st[i].wt; 
		}

		return d;
	}
	
		



	

};







 
	int main( )
{
   
   //freopen("graf.in","r",stdin);
   //freopen("graf.out","w",stdout);
   int N,a,b,c,M;
   
   
   cin>>N;
   Graph G(N);
   for (int i=0; i<N-1; i++)
   { scanf ("%d%d%d",&a,&b,&c);
	 Edge e(--a,--b,c);
     G.insert(e);
	 
   }

   
   cin>>M;
   for (int i=0; i<M; i++)
   { scanf("%d%d",&a,&b);
    cout<<G.dist(--a,--b)<<endl; }
   


 return 0;
}

