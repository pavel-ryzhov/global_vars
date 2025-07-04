
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <stdlib.h>

using namespace std;

const int NIL = -1;

struct edge
{
	int to_vertex;
	int length;
};

struct vertex
{
	int parent;
	int length;
	int discovered;
	int finished;
	vector <int> ancestors; // O(lgN) ancestors
	vector <int> distances; // distances to ancestors
	list <edge> edges; // in total 2*|E| = O(E)
};

void dfs(vector <vertex> &graph, int v, int &time)
{
	time++;
	graph[v].discovered = time;

	//-----
	
	if ( v )
	{
		if ( graph[v].parent == 0 )
		{
			graph[v].ancestors.resize ( 1 );
			graph[v].distances.resize ( 1 );
			graph[v].ancestors[0] = 0;
			graph[v].distances[0] = graph[v].length;
		}
		else
		{
			graph[v].ancestors.reserve( graph[graph[v].parent].ancestors.size() + 1);
			graph[v].distances.reserve( graph[graph[v].parent].distances.size() + 1);
			graph[v].ancestors.resize ( graph[graph[v].parent].ancestors.size() );
			graph[v].distances.resize ( graph[graph[v].parent].distances.size() );
			graph[v].ancestors[0] = graph[v].parent;
			graph[v].distances[0] = graph[v].length;
			
			int i;
			for ( i = 1; i != graph[graph[v].parent].ancestors.size(); i++ )
			{
				graph[v].ancestors[i] = graph[ graph[v].ancestors[i-1] ].ancestors[i-1] ;
				graph[v].distances[i] = graph[ graph[v].ancestors[i-1] ].distances[i-1] + graph[v].distances[i-1]; // O_o
			}
			if ( graph[ graph[v].ancestors[i-1] ].ancestors.size() == i ) // then there is one more
			{
				graph[v].ancestors.resize( graph[v].ancestors.size() + 1 );
				graph[v].ancestors[i] = graph[ graph[v].ancestors[i-1] ].ancestors[i-1];

				graph[v].distances.resize( graph[v].distances.size() + 1 );
				graph[v].distances[i] = graph[v].distances[i-1] + graph[ graph[v].ancestors[i-1] ].distances[i-1];
			}
		}
	}

	//-----

	for ( list <edge>::iterator i = graph[v].edges.begin(); i != graph[v].edges.end(); ++i )
	{
		if ( graph[(*i).to_vertex].discovered == NIL )
		{
			graph[(*i).to_vertex].parent = v;
			graph[(*i).to_vertex].length = (*i).length ;
			dfs( graph, (*i).to_vertex, time );
		}
	}
	time++;
	graph[v].finished = time;
}

bool ancestor(vector <vertex> &graph, int &v1, int &v2) // O(1)
{
	return graph[v1].discovered < graph[v2].discovered &&
		   graph[v1].finished   > graph[v2].finished;
}

int up(vector <vertex> &graph, int &goes_up, int &stays)
{
	int distance = 0;
	bool found = false;
	while ( !found )
		{
			int k;
			for ( k = graph[goes_up].ancestors.size() - 1; k >= 0; k-- )
			{
				if ( !ancestor( graph, graph[goes_up].ancestors[k], stays ) )
				{
					distance += graph[goes_up].distances[k];
					goes_up = graph[goes_up].ancestors[k];
					break;
				}
			}
		found = k > -1 ? found : !found;
		}
	return distance;
}

int main()
{
	int N;
	string line;
	int space1, space2;
	int first;
	int second;
	int length;

	// input:

	getline(cin, line);
	N = atoi( line.c_str() );

	vector <vertex> graph(N);	

	graph[0].parent = NIL;
	graph[0].length = NIL;
	graph[0].discovered = NIL;
	graph[0].finished   = NIL;
	graph[0].ancestors.resize(0);
	graph[0].distances.resize(0);

	for ( int i = 1; i < N; i++ )
	{
		getline(cin, line);
		space1  = line.find(' ');
		first   = atoi( line.substr(0, space1).c_str() ) - 1;
		space2  = line.find(' ', space1 + 1);
		second  = atoi( line.substr(space1 + 1, space2 - space1 - 1).c_str() ) - 1;
		length  = atoi( line.substr(space2 + 1, string::npos ).c_str() );
		//cout << endl << parent << ' ' << child << ' ' << length << endl << endl;

		graph [first].discovered = NIL;
		graph [first].finished   = NIL;
		graph[second].discovered = NIL;
		graph[second].finished   = NIL;

		edge e;
		e.length = length;
		e.to_vertex = second;

		graph [first].edges.push_back(e);
		e.to_vertex = first;
		graph[second].edges.push_back(e);
		
	}

	int time = 0;
	dfs(graph, 0, time);
	
	// queries:

	int M;

	getline(cin, line);
	M = atoi( line.c_str() );

	int distance;
	int A, B; // pair of vertices

	for ( int i = 0 ; i < M; i++ )
	{
		getline(cin, line);
		space1  = line.find(' ');
		A = atoi( line.substr(         0,      space1).c_str() ) - 1;
		B = atoi( line.substr(space1 + 1,string::npos).c_str() ) - 1;
		
		// case 1:
		if ( A == B )
		{
			cout << 0 << endl;
			continue;
		}

		distance = 0;

		// A goes up:
		distance += up(graph, A, B);

		// case 2:
		if ( A == B ) // B is A's ancestor
		{
			cout << distance << endl;
			continue;
		}

		// B goes up:
		distance += up(graph, B, A);

		// case 3:
		if ( A == B ) // A is B's ancestor
			cout << distance << endl;
		// case 4:
		else // new A's parent = new B's parent = LCA of original A and B
		{
			distance += graph[A].length;
			distance += graph[B].length;
			cout << distance << endl;
		}
	}

	//char ___;
	//cin >> ___;
	return 0;
}