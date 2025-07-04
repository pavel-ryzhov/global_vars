#include <vector>
#include <cstdio>
using namespace std;

int N, l, m;
vector <vector<int> > ParentNodes;

vector <vector<int> > MainGraph;

vector<int> NumberOfIn, NumberOfOut;
vector<bool> Passed;
int StepNumber;

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
vector <double> Results;


vector <myPair> ParentNodeLength;


void DFS(int Node, int Parent = 0)
{
	ParentNodes[Node][0] = Parent;
	NumberOfIn[Node] = StepNumber;
	Passed[Node] = true;
	StepNumber++;

	for (int i=1; i<=l; ++i)
	{
		ParentNodes[Node][i] = ParentNodes[ParentNodes[Node][i-1]][i-1];
	}
	for (int i=0;i<int(MainGraph[Node].size());i++)
	{
		int NextNode = MainGraph[Node][i];
		if (!Passed[NextNode])
		{
			DFS(NextNode, Node);
		}
	}
	NumberOfOut[Node] = StepNumber;
	StepNumber++;
}

bool IsParentLine (int a, int b)
{
	return (NumberOfOut[a] >= NumberOfOut[b]) && (NumberOfIn[a] <= NumberOfIn[b]);
}

int LCA(int a, int b)
{
	if (IsParentLine(a, b))  return a;
	if (IsParentLine(b, a))  return b;
	for (int i=l; i>=0; --i)
	{
		if (! IsParentLine (ParentNodes[a][i], b))
		{
			a = ParentNodes[a][i];
		}
	}
	return ParentNodes[a][0];
}

int main(void)
{
	N=0;
	scanf ("%d",&N); 
	if(N < 0)
	{
		return 0;
	}

	ParentNodeLength.resize(N);
	NumberOfOut.resize(N);
	ParentNodes.resize(N);
	NumberOfIn.resize(N);
	MainGraph.resize(N);
	Passed.resize(N);
	for(int i=0;i<(N-1);i++)
	{
		MainGraph[i].resize(N,0);
	}

	int Start=0;
	int Finish=0;
	int Len=0;
	for(int i=0;i<N-1;i++)
	{
		scanf ("%d %d %d",&Start,&Finish,&Len);

		Start--;
		Finish--;

		MainGraph[Start].push_back(Finish);
		ParentNodeLength[Finish].First=Start;
		ParentNodeLength[Finish].Second=Len;
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

	l = 1;
	while ((1<<l) <= N) 
	{
		l++;
	}
	for (int i=0; i<N; i++)
	{
		ParentNodes[i].resize(l+1);
	}

	DFS(0);

	int c=0;
	Results.resize(m);
	for(int i=0;i<m;i++)
	{
		c=LCA(NodesToSolve[i].First, NodesToSolve[i].Second);

		int pos=NodesToSolve[i].First;
		while(pos != c)
		{
			Results[i]+=ParentNodeLength[pos].Second;
			pos=ParentNodeLength[pos].First;
		}
		pos= NodesToSolve[i].Second;
		while(pos != c)
		{
			Results[i]+=ParentNodeLength[pos].Second;
			pos=ParentNodeLength[pos].First;
		}
	}

	for(int i=0;i<(m-1);i++)
	{
		printf("%.0f\n",Results[i]);
	}
	printf("%.0f",Results[m-1]);
	return 0;
}