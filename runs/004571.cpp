#include <iostream>

using namespace std;

const int INF = 100000; // "Бесконечность"

int main(int argc,char* argv[])
{
        int N;
      //  if(argc<3)
      //          return 1; // Если не указали имена файлов, то выходим
      //  ifstream file(argv[1]); //открываем файл для чтения
      //  ofstream fl(argv[2]);   //открываем файл для записи

//        file >> N;
	cin >> N;
	if(N==1)
	{
	//	fl << 0;
//		file.close();
//		fl.close();
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
//                file >> a>> b >> d;
		cin >> a >> b >> d;
                mat[a-1][b-1] = d;
                mat[b-1][a-1] = d;
        }

        for(int k=0;k<N;k++)
                for(int i = 0; i<N;i++)
                        for(int j = 0; j<N; j++)
                                mat[i][j] = min(mat[i][j],mat[i][k]+mat[k][j]);

        int M;
//        file >> M;
	cin >> M;
        for(int i = 0; i< M ; i++)
        {
                int a,b;
//                file >> a >> b;
			cin >> a >> b;
//                fl << mat[a-1][b-1] << endl;
		cout << mat[a-1][b-1] << endl;

        }
//        file.close();
  //      fl.close();
        return 0;
}
