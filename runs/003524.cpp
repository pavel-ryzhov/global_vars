#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef unsigned short us;

map < us, map < us, us > > g_Graph, g_Tree;

void add ( us start, us end, us len )
{
	g_Graph[start][end] = len;
	g_Graph[end][start] = len;
}

void find ( us start, us target, us ignore = 0, us len = 0 )
{
	map < us, us >::iterator iter = g_Graph[start].begin();
	for ( ; iter != g_Graph[start].end(); ++iter )
	{
		if ( ( iter->first != ignore ) )
		{
			int length = len + iter->second;
			g_Tree[target][iter->first] = length;
			find ( iter->first, target, start, length );
		}
	}
}

void make_tree ()
{
	map < us, map < us, us > >::iterator iter = g_Graph.begin();
	for ( ; iter != g_Graph.end(); ++iter )
	{
		find ( iter->first, iter->first );
	}
}

inline int getlength ( us start, us end )
{
	return g_Tree[start][end];
}

int main ()
{
	int count = 0;
	cin >> count;

	int a, b, l;
	for ( int i = 1; i < count; i++ )
	{
		cin >> a;
		cin >> b;
		cin >> l;
		add ( a, b, l );
	}

	make_tree();

	cin >> count;
	for ( int i = 1; i <= count; i++ )
	{
		cin >> a;
		cin >> b;
		cout << getlength ( a, b ) << endl;
	}
}