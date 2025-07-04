#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

class Edge
{
	//номера вершины, из которой исходит ребро
	long v;
	//номера вершины, в которую входит ребро
	long w;
	//вес ребра
	long weight;
public:
	Edge(long v, long w, long t): v(v) , w(w) ,weight(t){}
	//опрос номера вершины, из которой исходит ребро
	long V() const { return v; }
	//опрос номера вершины, в которую входит ребро
	long W() const { return w; }
	long WT() const {return weight; }
	//опрос признака исхода ребра из вершины v,
	bool from(long pv) const { return v == pv; }
	bool operator==(Edge ob){ return v==ob.v && w==ob.w;	}
	bool operator<(Edge *ob) {return v<ob->V();}
};

class Vertex
{
	//long v;
	long parent;
public:
	vector<long> ch;
public:
	Vertex(long parent):parent(parent){}
	Vertex():parent(-1){}
	//long Get() { return v; }
	long Parent() { return parent; }
	void Parent(long p){ parent = p;}
	void Insert(long c) 
	{
		ch.push_back(c);
	}
};

class Graph
{
	long Vcnt;//числа вершин
	long Ecnt;//числа рёбер
	vector< vector < Edge* > > adj;
	vector<Vertex> vertex;
	//ofstream out;
public:
	Graph(int V) : Vcnt( V ),vertex( V ), Ecnt( 0 ), adj(V) 
	{ 
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

	void insert(Edge *e)
	{
		int v = e->V();
		int w = e->W();
		if(v==w) throw "Петля";
		adj[v].push_back(e);
		vertex[v].Insert(w);
		vertex[w].Parent(v);
		if(vertex[v].Parent()==-1)
		{
			for(int i=0;i < Vcnt;i++)
			{			
				for(vector<long>::iterator j=vertex[i].ch.begin(); j!=vertex[i].ch.end(); ++j)
				{
					if( (*j) == v )
					{
						vertex[v].Parent(i);
						return;
					}
				}		
			}
			vertex[v].Parent(-1);
		}		
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
		while(curent_vert!=-1)
		{
			curent_vert=parent(curent_vert);
			d++;
		}
		return d-1;
	}
	long parent(long vert)
	{
		return vertex[vert].Parent();
	}

	long LCA(int u, int v)
	{		
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
		cout<<"Число вершин:"<<Vcnt<<"\n";
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

	void Load()
	{	
		long u,v,w;
		cin>>Vcnt;
		adj.resize(Vcnt);
		vertex.resize(Vcnt);

		for(int i=0;i<Vcnt-1;i++)
		{
			cin>>u>>v>>w;
			insert( new Edge(u-1,v-1,w));
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
		for(vector<int>::iterator i=par.begin();i!=par.end();i+=2)	
		{ 
			LCA( (*i)-1, (*(i+1))-1 );
		}

	}
};

int main(int argc, char *argv[])
{
	try
	{
			Graph g;
			g.Load();
	}
	catch(char *badnews)
	{
		cout<<badnews<<endl;
	}
	return 0;
}