#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

const int INF = 2000000000;

int min(int a, int b) {

	if (a < b) return a;
	else return b;
}

int main() {

	int n, begin, end, length;
	vector< vector<int> > d;
	vector<int> row;

	cin >> n;
	
	for (int i = 0; i < n; i++)
		row.push_back(INF);
	
	for (int i = 0; i < n; i++)
		d.push_back(row);
	
	for (int i = 0; i < n; i++)
		d[i][i] = 0;

	for (int i = 0; i < n - 1; i++) {
		cin >> begin;
		cin >> end;
		cin >> length;
		d[begin - 1][end - 1] = length;
		d[end - 1][begin - 1] = length;
	}

	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (d[i][k] < INF && d[j][k] < INF)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

	cin >> n;
	
	for (int i = 0; i < n; i++) {
		cin >> begin;
		cin >> end;
		cout << d[begin - 1][end - 1] << endl;
	}

	return (EXIT_SUCCESS);
}

