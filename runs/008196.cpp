
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <stdlib.h>

#include <fstream>

using namespace std;

const int NIL = -1;

struct vertex
{
	int parent;
	int length;
	int discovered;
	int finished;
	//list <int> children;
	vector <int> ancestors; // O(lgN)
	vector <int> distances; // O(lgN)
	list <int> edges; // total 2*|E| = O(E)
	list <int> lengths; // of edges
};

void dfs(vector <vertex> &graph, int v, int &time)
{
	//cout << time << endl;
	//cout << v << endl;
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

			for ( list<int>::iterator i = graph[v].lengths.begin() , j = graph[v].edges.begin(); i != graph[v].lengths.end(); ++i, ++j )
				if ( graph[ *j ].discovered != NIL )
				{
					graph[v].distances[0] = *i;
					graph[v].lengths.erase(i);
					graph[v].edges  .erase(j);
					break;
				}

			//graph[v].distances[0] = graph[0].lengths.front();
			//graph[0].lengths.pop_front();
		}
		else
		{
			graph[v].ancestors.reserve( graph[graph[v].parent].ancestors.size() + 1);
			graph[v].distances.reserve( graph[graph[v].parent].distances.size() + 1);
			graph[v].ancestors.resize ( graph[graph[v].parent].ancestors.size() );
			graph[v].distances.resize ( graph[graph[v].parent].distances.size() );
			graph[v].ancestors[0] = graph[v].parent; //graph[v].edges.front();
			//graph[v].edges.pop_front();
			for ( list<int>::iterator i = graph[v].lengths.begin() , j = graph[v].edges.begin(); i != graph[v].lengths.end(); ++i, ++j )
				if ( graph[ *j ].discovered != NIL )
				{
					graph[v].distances[0] = *i;
					graph[v].lengths.erase(i);
					graph[v].edges  .erase(j);
					break;
				}
			//graph[v].lengths.pop_front();

			//graph[v].parent = graph[v].ancestors[0];
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
		graph[v].length = graph[v].distances[0];
	}

	//-----

	for ( list <int>::iterator i = graph[v].edges.begin(); i != graph[v].edges.end(); ++i )
	{
		if ( graph[*i].discovered == NIL )
		{
			//cout << v << endl;
			graph[*i].parent = v;
			dfs( graph, *i, time );
		}
	}
	time++;
	graph[v].finished = time;

	//-----

	

	//-----
}

bool ancestor(vector <vertex> &graph, int &v1, int &v2)
{
	return graph[v1].discovered < graph[v2].discovered &&
		   graph[v1].finished   > graph[v2].finished;
}

int main()
{
	int N;
	string line;
	int space1, space2;
	//int parent;
	//int child;
	int first;
	int second;
	int length;

	// input:
	//ifstream *f = new ifstream("C:\\Users\\Public\\Documents\\yandex\\distance\\Debug\\input2.txt");

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

		//graph[child].parent = parent;
		//graph[child].length = length;
		graph [first].discovered = NIL;
		graph [first].finished   = NIL;
		graph[second].discovered = NIL;
		graph[second].finished   = NIL;

		graph [first].edges.push_back(second);
		graph[second].edges.push_back(first );
		graph [first].lengths.push_back(length);
		graph[second].lengths.push_back(length);

		//graph[parent].children.push_back(child);
	}

	int time = 0;
	dfs(graph, 0, time);
	

	// queries:

	int M;
	int v1, v2;
	int lca = NIL;
	getline(cin, line);
	M = atoi( line.c_str() );

	int distance;

	for ( int i = 0 ; i < M; i++ )
	{
		getline(cin, line);
		space1  = line.find(' ');
		v1 = atoi( line.substr(         0,      space1).c_str() ) - 1;
		v2 = atoi( line.substr(space1 + 1,string::npos).c_str() ) - 1;
		//find:
		if ( v1 == v2 )
		{
			cout << 0 << endl;
			continue;
		}
		distance = 0;
		if ( ancestor( graph, v1, v2 ) )
		{
			lca = NIL;
			while (lca == NIL)
			{
				int k;
				for ( k = graph[v2].ancestors.size() - 1; k >= 0; k-- )
				{
					if ( !ancestor( graph, graph[v2].ancestors[k], v1 ) )
					{
						distance += graph[v2].distances[k];
						v2 = graph[v2].ancestors[k];
						break;
					}
				}
				if (k < 0)
					lca = v2;
			}
		}
		else if ( ancestor( graph, v2, v1 ) )
		{
			lca = NIL;
			while (lca == NIL)
			{
				int k;
				for ( k = graph[v1].ancestors.size() - 1; k >= 0; k-- )
				{
					if ( !ancestor( graph, graph[v1].ancestors[k], v2 ) )
					{
						distance += graph[v1].distances[k];
						v1 = graph[v1].ancestors[k];
						break;
					}
				}
				if (k < 0)
					lca = v1;
			}
		}
		else
		{
			lca = NIL;
			while (lca == NIL)
			{
				int k;
				for ( k = graph[v1].ancestors.size() - 1; k >= 0; k-- )
				{
					if ( !ancestor( graph, graph[v1].ancestors[k], v2 ) )
					{
						distance += graph[v1].distances[k];
						v1 = graph[v1].ancestors[k];
						break;
					}
				}
				if (k < 0)
					if ( graph[v1].parent != v2 )
						lca = graph[v1].parent;
					else
						lca = v1;
			}

			if ( graph[v1].parent != v2 )
				distance += graph[v1].length;

			lca = NIL;
			while (lca == NIL)
			{
				int k;
				for ( k = graph[v2].ancestors.size() - 1; k >= 0; k-- )
				{
					if ( !ancestor( graph, graph[v2].ancestors[k], v1 ) )
					{
						distance += graph[v2].distances[k];
						v2 = graph[v2].ancestors[k];
						break;
					}
				}
				if (k < 0)
					if ( graph[v2].parent != v2 )
						lca = graph[v2].parent;
					else
						lca = v2;
			}

			if ( graph[v2].parent != v1 )
				distance += graph[v2].length;
		}

		cout << distance << endl;
	}

	//char ___;
	//cin >> ___;
	return 0;
}