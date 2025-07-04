#include <vector>
#include <cstdio>
using namespace std;

int N,m;

vector < vector<int> > MainGraph;
vector< vector<int> > Graph1, Matrix1, Matrix2;

struct myPair
{
	int First;
	int Second;
	myPair()
	{
		First=0;
		Second=0;
	}
};

vector <myPair> NodesToSolve;

const int INF = 100000000;

int main()
{
	N=0;
	scanf ("%d",&N); 
	if(N < 0)
	{
		return 0;
	}

	MainGraph.resize(N);
	for(int i=0;i<N;i++)
	{
		MainGraph[i].resize(N,INF);
	}

	int Start=0;
	int Finish=0;
	int Len=0;
	for(int i=0;i<N-1;i++)
	{
		scanf ("%d %d %d",&Start,&Finish,&Len);

		Start--;
		Finish--;

		MainGraph[Start][Finish]=Len;
		MainGraph[Finish][Start]=Len;
	}

	m=0;
	scanf ("%d",&m);
	if(m < 1)
	{
		return 0;
	}
	if(N < 1)
	{
		return 0;
	}

	NodesToSolve.resize(m);
	for(int i=0;i<m;i++)
	{
		scanf ("%d %d",&(NodesToSolve[i].First),&(NodesToSolve[i].Second));
		NodesToSolve[i].First--;
		NodesToSolve[i].Second--;
	}

	Graph1.resize(MainGraph.size());
	for (int i=0; i<N; i++)
	{
		Graph1[i].resize(MainGraph.size());
		for(int j=0; j<N; j++)
		{
			Graph1[i][j]=MainGraph[i][j];
		}
	}

	
	Matrix2.resize(Graph1.size());
	for(int i=0; i<N; i++)
	{
		Matrix2[i].resize(Graph1[i].size());
		for(int j=0; j<N; j++)
		{
			Matrix2[i][j] = Graph1[i][j];
		}
	}

	Matrix1.resize(MainGraph.size());
	for(int i=0; i<N; i++)
	{
		Matrix1[i].resize (N+1);
	}

	for(int k=0; k<N; k++)
	{
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
			{
				Matrix1[i][j] = min (Matrix2[i][j], Matrix2[i][k]+Matrix2[k][j]);
			}
		}
		Matrix1.swap(Matrix2);
	}
	Matrix1.swap(Matrix2);
	

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(i == j)
			{
				Matrix1[i][j] = 0;
			}
		}
	}

	int a=0;
	int b=0;
	for(int i=0;i<(m-1);i++)
	{
		a=NodesToSolve[i].First;
		b=NodesToSolve[i].Second;
		printf("%d\n",(Matrix1[a][b]<INF ? Matrix1[a][b] : 0));
	}
	a=NodesToSolve[m-1].First;
	b=NodesToSolve[m-1].Second;
	printf("%d",(Matrix1[a][b]<INF ? Matrix1[a][b] : 0));

	return 0;
}