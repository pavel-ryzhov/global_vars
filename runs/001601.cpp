#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
typedef vector< vector<int> > mat;

int dist;
void PrintMatrix(mat matrix, int n) {
        for(int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cout << (matrix[i])[j] << " ";
        }
        cout << endl;
    }
}

void ReadGraph(mat::iterator matrix, int n) {
    int a, b, dist, i=0;
    for (i; i<n-1; i++) {
        cin >> a >> b >> dist;
        b = b-1;
        a = a -1;
        matrix[a].erase(matrix[a].begin()+b);
        matrix[a].insert(matrix[a].begin()+b, dist);
        matrix[b].erase(matrix[b].begin()+a);
        matrix[b].insert(matrix[b].begin()+a, dist);
        
    }
}

int FindDist(mat::iterator matrix, int a, int b, int pred) {
    int un;
    if (a > b) { un = a; a = b; b = un; }
    int count = matrix[b].size();
    if ( a == b && a<count && b<count) return 0;
    else if (a>count || b>count) return -1;
    for (int i=0; i<count; i++) {
        if ( matrix[b][i] != 0 && i == pred) break;
        else if ( (matrix[b][i] != 0) && (i == a) ) return dist = matrix[b][i];
        else if ( matrix[b][i] != 0) return dist = matrix[b][i] + FindDist(matrix, a, i, b);
    }
}

void GetPeaks(mat::iterator matrix) {
    int count, a, b;
    cin >> count;
    for (int i = 0; i<count; i++) {
        cin >> a >> b;
        cout << FindDist(matrix, a-1, b-1, -1) << endl;
    }
}


int main(int argc, char** argv) {
    int count_peak;
    cin >> count_peak;
    vector<vector<int> > matrix(count_peak, vector<int>(count_peak, 0));
    mat::iterator ptr = matrix.begin();
    ReadGraph(ptr, count_peak);
    //PrintMatrix(matrix, count_peak);
    GetPeaks(ptr);
    return (EXIT_SUCCESS);

}

