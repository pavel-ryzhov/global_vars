#include <iostream>

using namespace std;

const int INF = 100000000; 

int main(int argc,char* argv[])
{
        int N;
	cin >> N;
        int **mat;
        mat = new int*[N];
        for(int i = 0; i<N;i++)
        {
                mat[i] = new int[N];
                for(int j =0; j< N; j++)
                        mat[i][j] = INF;
        }

        for(int i=0;i<N-1;i++)
        {
                int a,b,d;
		cin >> a >> b >> d;
                mat[a-1][b-1] = d;
                mat[b-1][a-1] = d;
        }

        for(int k=0;k<N;k++)
                for(int i = 0; i<N;i++)
                        for(int j = 0; j<N; j++)
                                mat[i][j] = min(mat[i][j],mat[i][k]+mat[k][j]);


	for(int i =0; i< N; i++)
		mat[i][i]=0;

        int M;
	cin >> M;
        int *arr = new int[M];
        for(int i = 0; i< M ; i++)
        {
                int a,b;
		cin >> a >> b;
		arr[i] = mat[a-1][b-1];

        }
        for(int i =0; i< M; i++)
                cout << arr[i] << endl;
        return 0;
}