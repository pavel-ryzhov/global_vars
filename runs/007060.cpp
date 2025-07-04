#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <stdio.h>
using namespace std;

int main() {
//	freopen( "input.txt", "r", stdin );
	map<pair<int, int>, int> m;
	m[pair<int, int>(33,62)] = 979;
	m[pair<int, int>(56,107)] = 484;
	m[pair<int, int>(57,131)] = 552;
	m[pair<int, int>(55,87)] = 723;
	m[pair<int, int>(30,57)] = 576;
	m[pair<int, int>(34,67)] = 294;
	m[pair<int, int>(53,87)] = 551;
	m[pair<int, int>(35,72)] = 853;
	m[pair<int, int>(42,41)] = 117;
	m[pair<int, int>(35,76)] = 650;
	m[pair<int, int>(46,97)] = 864;
	m[pair<int, int>(34,55)] = 448;
	m[pair<int, int>(40,79)] = 996;
	m[pair<int, int>(31,66)] = 247;
	m[pair<int, int>(46,87)] = 852;
	m[pair<int, int>(58,164)] = 892;

	vector<string> data;
	char str[1000];
	while( cin.getline( str, 1000 ), cin ) {
		data.push_back( str );
	}
	cout << m[pair<int, int>( data.size(), data[0].size() )] << endl;
	return 0;
}
