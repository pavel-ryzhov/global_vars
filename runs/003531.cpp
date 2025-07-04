#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

typedef unsigned short us;

vector < map < us, us > > g_Graph;

void add ( us start, us end, us len )
{
	g_Graph[start].insert ( make_pair ( end, len ) );
	g_Graph[end].insert (  make_pair ( start, len ) );
}

void find ( us start, us end, us ignore, us* result, us len = 0 )
{
	map < us, us >::iterator iter = g_Graph[start].begin();
	for ( ; iter != g_Graph[start].end(); ++iter )
	{
		if ( iter->first != ignore )
		{
			if ( end == iter->first )
			{
				*result = len + iter->second;
				return;
			}
			else
			{
				find ( iter->first, end, start, result, len + iter->second );
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

	cin >> count;
	for ( int i = 1; i <= count; i++ )
	{
		cin >> a;
		cin >> b;
		l = 0;
		find ( a, b, a, &l );
		cout << l << endl;
	}
}