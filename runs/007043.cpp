#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#pragma comment(linker, "/STACK:64777216")


const int maxSize = 80001;
vector<vector<pair<int, int> > > tree;
vector<int> depths;
vector<int> values;
vector<int> order;

void DFS( int prev, int cur, int value, int depth ) {
	order.push_back( cur );
	for( vector<pair<int, int> >::iterator it = tree[cur].begin(); it != tree[cur].end(); ++it ) {
		if( it->first != prev ) {
			depths[it->first] = depth + 1;
			values[it->first] = value + it->second;
			DFS( cur, it->first, value + it->second, depth + 1);
			order.push_back( cur );
		}
	}
}



int main() {
	int n;
	scanf( "%d", &n );
	tree.resize( maxSize );
	depths.resize( maxSize );
	values.resize( maxSize );
	depths[0] = 0;
	values[0] = 0;
	int startVertex = 0;
	for( int i = 0; i < n - 1; ++i ) {
		int from, to, val;
		scanf( "%d %d %d", &from, &to, & val );
		tree[from].push_back( pair<int, int>( to, val ) );
		tree[to].push_back( pair<int, int>( from, val ) );
		startVertex = from;
	}
	DFS( -1, startVertex, 0, 0 );
	vector<int> pos;
	pos.resize( maxSize, -1 );
	for( int i = 0; i < order.size(); ++i ) {
		if( pos[order[i]] == -1 ) {
			pos[order[i]] = i;
		}
	}
	vector<int> sqrtMin;
	int q = sqrt( (double)(order.size()) );
	for( int i = 0; i * q < order.size(); ++i ) {
		int min = i * q;
		for( int j = i * q; j < ( i + 1 ) * q && j <  order.size(); ++j ) {
			if( depths[order[min]] > depths[order[j]] ) {
				min = j;
			}
		}
		sqrtMin.push_back( min );
	}
	scanf( "%d", &n );
	for( int i = 0; i < n; ++i ) {
		int from, to;
		scanf( "%d %d", &from, &to );
		int start = min( pos[from], pos[to] );
		int finish = max( pos[from], pos[to] );
		int res = start;
		for( int j = start; j <= finish;  ) {
			if( j % q == 0 && ( j / q + 1 ) * q <= finish ) {
				if( depths[order[res]] > depths[order[sqrtMin[j / q]]] ) {
					res = sqrtMin[j / q];
				}
				j += q;
			} else {
				if( depths[order[res]] > depths[order[j]] ) {
					res = j;
				}
				++j;
			}
		}
		printf( "%d\n", values[from] + values[to] - 2 * values[order[res]] );
	}
	return 0;
}
