// PROB:graf
// Lang: C++
//

//#include "stdafx.h"
#include<vector>
#include<iostream>
#include<list>
#include<stack>
#define MaxN 40000


using namespace std;

int dsu[MaxN];
int anc[MaxN];
double AllPath[MaxN];

bool u[MaxN];


struct Edge {
	int v, w, wt;
	Edge (int v, int w, int wt): v(v), w(w), wt(wt) {}	
};

struct St {
	int v, wt;
	St(int v=-1, int wt=-1): v(v),wt(wt) {}
};

St st[MaxN];
vector <St> q[MaxN];

class Graph
{	

	
	list<Edge>* adj;
	
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

	~ Graph() {
		delete[] adj; 
	}

	int dsu_get (int v) {
		return v==dsu[v] ? v : dsu_get(dsu[v]);
	}

	
	void dsu_unite (int a, int b, int new_anc) {
		a=dsu_get(a);b=dsu_get(b);
		int k=a;
		a=b; b=k;
		dsu[a]=b;
		anc[b]=new_anc;
	}
	
	double path (int a, int b){
		if (a==b) return 0;
		int i=a; double d=st[i].wt;
		while (st[i].v!=b) {
			i=st[i].v;
			d+=st[i].wt;
		}
		return d; 
	}


	void dfs (Edge e) {
		list<Edge>::iterator j;
		dsu[e.w]=e.w;
		anc[e.w]=e.w;
		st[e.w].v=e.v;
		st[e.w].wt=e.wt;
		u[e.w]=true;
		
		for (j=adj[e.w].begin(); j!=adj[e.w].end(); j++)
			if (!u[j->w]) {
			
				dfs(*j);
				dsu_unite (j->v,j->w,j->v);
			}
		for (size_t i=0; i<q[e.w].size(); i++)
			if (u[q[e.w][i].v]) {
				int ancestor=anc[dsu_get(q[e.w][i].v)];
				double d=(path(e.w,ancestor)+path(q[e.w][i].v,ancestor));
				AllPath[q[e.w][i].wt]=d;
			}
	}
	
	
};







 
	int main( )
{
   
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
		--a; --b;
		St s;
		s.v=b; s.wt=i;
		q[a].push_back(s);
		s.v=a;
		q[b].push_back(s);
   } 
   
   G.dfs(Edge(0,0,0));
	for (int i=0; i<M; i++)
		cout<<AllPath[i]<<endl;
  
	
   
   


 return 0;
}

