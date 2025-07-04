#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef unsigned short us;

map < us, map < us, us > > g_Graph;

void add ( us start, us end, us len )
{
	g_Graph[start][end] = len;
	g_Graph[end][start] = len;
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
			}
		}
	}
}

int main ()
{
	int count = 0;

	cin >> count;

	us a, b, l;
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