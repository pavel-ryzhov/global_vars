#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

class Edge
{
	//������ �������, �� ������� ������� �����
	long v;
	//������ �������, � ������� ������ �����
	long w;
	//��� �����
	long weight;
public:
	Edge(long v, long w, long t): v(v) , w(w) ,weight(t){}
	//����� ������ �������, �� ������� ������� �����
	long V() const { return v; }
	//����� ������ �������, � ������� ������ �����
	long W() const { return w; }
	long WT() const {return weight; }
	//����� �������� ������ ����� �� ������� v,
	bool from(long pv) const { return v == pv; }
	bool operator==(Edge ob){ return v==ob.v && w==ob.w;	}
	bool operator<(Edge *ob) {return v<ob->V();}
};

class Vertex
{
	//long v;
	long parent;
	long depth;
public:
	vector<long> ch;
public:
	Vertex(long parent):parent(parent){}
	Vertex():parent(-1),depth(-1){}
	//long Get() { return v; }
	long Parent() { return parent; }
	void Parent(long p){ parent = p;}
	long GetDepth() {return depth;}
	void PutDeptp(long d) {depth=d;}
	void Insert(long c) 
	{
		ch.push_back(c);
	}
};



class Graph
{
	long Vcnt;//����� ������
	long Ecnt;//����� ����
	vector< vector < Edge* > > adj;
	vector<Vertex> vertex;

	vector<int> st;
	vector<int> ord;
	int cnt;
	//ofstream out;
public:

	Graph(int V) : Vcnt( V ),vertex( V ), Ecnt( 0 ), adj(V)
	{ 
		for (int i=0;i<V;i++)
		{
			st.push_back(-1);
		}
		for (int i=0;i<V;i++)
		{
			ord.push_back(-1);
		}
		cnt=0;
		//out.open("out.txt");
		//if(!out) throw "no file";
	}
	Graph() : Vcnt( 0 ), Ecnt( 0 )
	{ 

		//out.open("out.txt"); 
		//if(!out) throw "no file";
	}
	~Graph()
	{
		for(vector< vector<Edge*> >::iterator i=adj.begin();i!=adj.end();++i)
			for (vector<Edge*>::iterator j=(*i).begin();j!=(*i).end();++j)
			{
				delete *j;
			}
	}
	void ShowST()
	{
		for(int i=0;i<Vcnt;i++)
		{
			cout<<i<<" "<<st[i]<<endl;
		}
		cout<<endl;
	}
	void ShowOrd()
	{
		for(int i=0;i<Vcnt;i++)
		{
			cout<<i<<" "<<ord[i]<<endl;
		}
		cout<<endl;
	}
	void BFS()
	{
		queue<Edge*> q;
		Edge *e=new Edge(0,0,0);
		q.push( e );
		cnt=0;
		ord[e->W()]=cnt++;
		while( !q.empty() )
		{
			e=q.front();
			q.pop();
			st[e->W()]=e->V();
			for(vector<Edge*>::iterator a=adj[e->W()].begin();a!=adj[e->W()].end();a++)
			{
				if(ord[ (*a)->W() ]==-1)
				{
					q.push( new Edge(e->W(),(*a)->W(),0) );
					ord[ (*a)->W() ] = cnt++;
				}
			}
		}
		delete e;
	}


	void insert(Edge *e)
	{
		int v = e->V();
		int w = e->W();
		if(v==w) return;
		adj[v].push_back(e);
		adj[w].push_back( new Edge(w,v,e->WT()) );
	}




	long edge(int v, int w)
	{
		for(vector<Edge*>::iterator j=adj[v].begin(); j!=adj[v].end(); j++)
			if( (*j)->W()==w ) return (*j)->WT();		
	}

	long depth(long vert)
	{
		long d=0;
		long curent_vert=vert;
		while(curent_vert!=0)
		{
			curent_vert=parent(curent_vert);
			d++;
		}
		return d-1;
	}
	long parent(long vert)
	{
		//return vertex[vert].Parent();
		return st[vert];
	}

	long LCA(int u, int v)
	{		
		if(u==v)
		{
			cout<<"0\n";
			return 0;
		}
		int h1=depth(u);
		int h2=depth(v);

		int l=0;
		while (h1!=h2)
		{
			if(h1>h2)
			{
				int u2=parent(u);
				l+=edge(u2,u);
				u=u2;
				h1--;
			}
			else
			{
				int v2=parent(v);
				l+=edge(v2,v);
				v=v2;	
				h2--;
			}
		}

		while(u!=v)
		{			
			int u2=parent(u);
			int v2=parent(v);
			l+=edge(u2,u);
			l+=edge(v2,v);
			u=u2;
			v=v2;
		}
		cout<<l<<"\n";
		//out<<l<<"\n";
		return l;
	}
	void Show()
	{
		cout<<"����� ������:"<<Vcnt<<"\n";
		for(int i=0;i < Vcnt;i++)
		{
			cout<<i+1<<":";
			for(vector<Edge*>::iterator j=adj[i].begin(); j!=adj[i].end(); ++j)
				cout<<(*j)->W()+1<<" ";
			cout<<"\n";
		}
		cout<<"\n";
		for(int i=0;i < Vcnt;i++)
		{
			cout<<i+1<<":";
			for(vector<long>::iterator j=vertex[i].ch.begin(); j!=vertex[i].ch.end(); ++j)
				cout<<(*j)+1<<" ";
			cout<<" Parent:"<<vertex[i].Parent()+1;
			cout<<"\n";			
		}
		cout<<"\n";
	}
};


int main(int argc, char *argv[])
{
	try
	{

	/*	Graph g(9);
		g.insert( new Edge((1)-1,(2)-1, 0));
		g.insert( new Edge((2)-1,(9)-1, 5));
		g.insert( new Edge((3)-1,(9)-1, 0));	
		g.insert( new Edge((4)-1,(9)-1, 8));	
		g.insert( new Edge((5)-1,(9)-1, 7));	
		g.insert( new Edge((6)-1,(8)-1, 2));
		g.insert( new Edge((7)-1,(5)-1, 0));
		g.insert( new Edge((8)-1,(7)-1, 1));
		g.BFS();
		//g.ShowST();
		//cout<<endl;
		g.LCA( (6)-1, (5)-1 );// 3
		g.LCA( (2)-1, (3)-1 );// 5	
		g.LCA( (3)-1, (3)-1 );// 0
		g.LCA( (4)-1, (1)-1 );// 13
		g.LCA( (3)-1, (7)-1 );// 7	
		g.LCA( (3)-1, (6)-1 );// 10
		g.LCA( (5)-1, (7)-1 );// 0
		g.LCA( (8)-1, (2)-1 );// 13
		cout<<endl;
*/


		long u,v,w;
		int Vcnt;
		cin>>Vcnt;
		//adj.resize(Vcnt);
		//vertex.resize(Vcnt);
		Graph g(Vcnt);

		for(int i=0;i<Vcnt-1;i++)
		{
			cin>>u>>v>>w;
			g.insert( new Edge(u-1,v-1,w));
		}

		int n;
		vector<int> par;
		cin>>n;
		for(int i=0;i<n;i++)
		{
			cin>>u>>v;	
			par.push_back(u);
			par.push_back(v);
		}		
		g.BFS();
		for(vector<int>::iterator i=par.begin();i!=par.end();i+=2)	
		{ 
			g.LCA( (*i)-1, (*(i+1))-1 );
		}	
		
	}
	catch(char *badnews)
	{
		cout<<badnews<<endl;
	}
	return 0;
}