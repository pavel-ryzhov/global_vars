#include <iostream>
#include <vector>

#define MX 40000

using namespace std;

vector<unsigned short> Graph[MX], Spans[MX], Quest[MX], Order[MX];
unsigned short DSU[MX], Ancestor[MX];
unsigned long Path[MX], Answer[MX];
bool Used[MX];

unsigned short find (unsigned short v)
{
	return v == DSU[v] ? v : DSU[v] = find (DSU[v]);
}
 
void unite (unsigned short a, unsigned short b, unsigned short c)
{
	a = find(a); 
	b = find(b);
	DSU[a] = b;
	Ancestor[b] = c;
}
 
void graph_scan(unsigned short v = 0, unsigned long h = 0)
{
	DSU[v] = v; 
	Ancestor[v] = v;
	Used[v] = true;
	Path[v] = h;

	for (unsigned short i=0; i<Graph[v].size(); ++i)
		if (!Used[Graph[v][i]])
		{
			graph_scan(Graph[v][i], h+Spans[v][i]);
			unite(v, Graph[v][i], v);
		}

	for (unsigned short i=0; i<Quest[v].size(); ++i)
		if (Used[Quest[v][i]])
		{
			h = Path[Ancestor[find(Quest[v][i])]];
			Answer[Order[v][i]] = (Path[v]-h)+(Path[Quest[v][i]]-h);
		}
}

int main()
{
	unsigned short N, M, start, stop, length;

	cin>>N;
	for (unsigned short i=0; i<N-1; ++i)
	{
		cin>>start>>stop>>length;
		--start; --stop;
		Graph[start].push_back(stop);
		Spans[start].push_back(length);
		Graph[stop].push_back(start);
		Spans[stop].push_back(length);
	}
	
	cin>>M;
	for (unsigned short i=0; i<M; ++i)
	{
		cin>>start>>stop;
		--start; --stop;
		Quest[start].push_back(stop);
		Quest[stop].push_back(start);
		Order[start].push_back(i);
		Order[stop].push_back(i);
	}

	graph_scan();

	for (unsigned short i=0; i<M; ++i) 
		cout<<Answer[i]<<'\n';

	return 0;
}
