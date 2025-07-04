#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned short us;

struct point
{
	point ( us e, us l, vector < point >* n )
	{
		end = e;
		len = l;
		neighbours = n;
	}
	vector < point >* neighbours;
	us end;
	us len;
};

vector < vector < point > > g_Graph;

void add ( us start, us end, us len )
{
	g_Graph[start].push_back ( point ( end, len, &g_Graph[end] ) );
	g_Graph[end].push_back ( point ( start, len, &g_Graph[start] ) );
}

void find ( vector < point >* node, us start, us end, us ignore, int* result, int len = 0 )
{
	vector < point >::iterator iter = node->begin();
	for ( ; iter != node->end(); ++iter )
	{
		if ( iter->end != ignore )
		{
			if ( end == iter->end )
			{
				*result = len + iter->len;
				return;
			}
			else
			{
				find ( iter->neighbours, iter->end, end, start, result, len + iter->len );
				if ( *result > 0 )
					return;
			}
		}
	}
}

int main ()
{
	int count = 0;
	cin >> count;
	us a, b, l;
	g_Graph.resize ( count + 1 );
	for ( int i = 1; i < count; i++ )
	{
		cin >> a;
		cin >> b;
		cin >> l;
		add ( a, b, l );
	}

	int len;
	cin >> count;
	for ( int i = 1; i <= count; i++ )
	{
		cin >> a;
		cin >> b;
		len = 0;
		find ( &g_Graph[a], a, b, a, &len );
		cout << len << endl;
	}
}