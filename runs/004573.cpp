#include <iostream>

using namespace std;

const int INF = 100000; // "Ѕесконечность"

int main(int argc,char* argv[])
{
        int N;
	cin >> N;
	if(N==1)
	{
		cout << 0;
		return 0;
	}
        int **mat; // матрица смежности дерева
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

        for(int i = 0; i< M ; i++)
        {
                int a,b;
		cin >> a >> b;
		cout << mat[a-1][b-1] << endl;

        }
//        file.close();
  //      fl.close();
        return 0;
}
