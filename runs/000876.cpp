#include <iostream>
#include <vector>
#include <sstream>


using namespace std;

const int INF = 100*1000*1000;

int main(int argc, char** argv) {

    int n;
    cin >> n;
    vector < vector<int> > g (n, vector<int> (n));
    for (int i=0;i<n;i++)
        for (int j=0; j<n; j++)
            g[i][j] = INF;

    for(int i=0;i<n-1;i++) {
        int begin, end, length;
        cin >> begin >> end >> length;
        g[begin-1][end-1] = length; g[end-1][begin-1] = length;
    }
 
    vector<vector<int> > d(n), d2;

    d2 = g;
    for(int i=0;i<n;i++)
        d[i].resize(n+1);

    for(int k=0; k<n; k++) {
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                d[i][j] = min(d2[i][j], d2[i][k]+d2[k][j]);
            d.swap(d2);
    }
    d.swap (d2);
 
    int ans;
    cin >> ans;
    stringstream s;
    for(int i=0;i<ans;i++) {
        int from, to;
        cin >> from >> to;
        s << (from==to?0:(d[from-1][to-1]<INF?d[from-1][to-1]:0)) << endl;
    }
    cout << s.str();

    return 0;
}
