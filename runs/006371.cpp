#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct {
	int pnum;	
	int dist;	
} upLink;

typedef upLink *Tree; 

int depth (int node, Tree T) {	
	if ( T[node].pnum == 0 )
		return 0;
	int h = 0;
	int x = node;
	while ( T[x].pnum != 0 ) {
		h++;
		x = T[x].pnum;
	}
	return h;
}

int way (int &x, int &y, Tree T) {	
	int h1 = depth (x, T);
	int h2 = depth (y, T);
	int len1, len2;
	len1 = len2 = 0;
	while ( h1 != h2 ) {
		if ( h1>h2 ) {
			len1 += T[x].dist;
			x = T[x].pnum;
			h1--;
		} else {
			len2 += T[y].dist;
			y = T[y].pnum;
			h2--;
		}
	}
	while ( x != y ) {
		len1 += T[x].dist;
		len2 += T[y].dist;
		x = T[x].pnum;
		y = T[y].pnum;
	}
	return len1 + len2;
}

int main () {
	int n, m;
	Tree T;	
	int *ans;
	cin >> n;
	T = new upLink [n+1];
	for ( int i=0 ; i<n+1 ; i++ )
		T[i].pnum = T[i].dist = 0;
	for ( int i=0; i<n-1 ; i++ ) {
		int a, b, c;
		cin >> a >> b >> c;
		if ( T[b].pnum == 0 ) {
			T[b].pnum = a;
			T[b].dist = c;
		} else {
			T[a].pnum = b;
			T[a].dist = c;
		}
	}
	cin >> m;
	ans = new int [m];
	for ( int i=0 ; i<m ; i++ ) {
		int x, y;
		cin >> x >> y;
		ans[i] = way (x, y, T);
	}
	for ( int i=0 ; i<m ; i++ ) 
		cout << ans[i] << '\n';
	system ("pause");
}