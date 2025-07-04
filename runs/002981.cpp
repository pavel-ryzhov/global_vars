#include <vector>
#include <cstdio>

using namespace std;

int N, l, m;
vector <vector< unsigned int > > ParentNodes;
vector <vector< unsigned int > > ParentNodesWeight;
vector <vector< int > > MainGraph;
vector <vector< int > > Weight;
vector < double > Results;

vector< unsigned int > NumberOfIn, NumberOfOut;
vector< bool > Passed;
int StepNumber;

void DFS(int Node, int Parent = 0,int len=0)
{
	ParentNodes[Node][0] = Parent;
	ParentNodesWeight[Node][0]=len;

	NumberOfIn[Node] = StepNumber;
	Passed[Node] = true;
	StepNumber++;
	for (int i=1; i<=l; ++i)
	{
		ParentNodes[Node].push_back(ParentNodes[ParentNodes[Node][i-1]][0]);
		ParentNodesWeight[Node].push_back(ParentNodesWeight[ParentNodes[Node][i-1]][0]);
		if( ParentNodes[ParentNodes[Node][i-1]][0] == 0 )
		{
			break;
		}
	}
	for (int i=0;i<int(MainGraph[Node].size());i++)
	{
		int NextNode = MainGraph[Node][i]; 
		len = Weight[Node][i];
		if (!Passed[NextNode])
		{
			DFS(NextNode, Node, len);
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

	for (vector< unsigned int >::reverse_iterator i=ParentNodes[a].rbegin(); i<ParentNodes[a].rend(); i++)
	{
		int k=*i;
		if (! IsParentLine (k, b))
		{
			return ParentNodes[k][0];
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

	NumberOfOut.resize(N);
	ParentNodes.resize(N);
	NumberOfIn.resize(N);
	MainGraph.resize(N);
	ParentNodesWeight.resize(N);
	Weight.resize(N);
	Passed.resize(N);

	int Start=0;
	int Finish=0;
	int Len=0;
	for(int i=0;i<(N-1);i++)
	{
		scanf ("%d %d %d",&Start,&Finish,&Len);

		Start--;
		Finish--;

		MainGraph[Start].push_back(Finish);
		MainGraph[Finish].push_back(Start);
		Weight[Start].push_back(Len);
		Weight[Finish].push_back(Len);

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

	l = 1;
	while ((1<<l) <= N) 
	{
		l++;
	}

	for (int i=0; i<N;  i++)
	{
		ParentNodesWeight[i].resize(1,0);
		ParentNodes[i].resize(1,0);
	}

	DFS(0);

	int x=0;
	int y=0;
	int c=0;
	Results.resize(m);
	for(int i=0;i<m;i++)
	{
		scanf ("%d %d",&x,&y);
		x--;
		y--;

		c=LCA(x, y);

		int pos=x;
		int Tmp1=0;
		while(pos != c)
		{
			Results[i]=Results[i]+ParentNodesWeight[pos][0];
			pos=ParentNodes[pos][0];
		}
		Tmp1=0;
		pos= y;
		while(pos != c)
		{
			Results[i]=Results[i]+ParentNodesWeight[pos][0];
			pos=ParentNodes[pos][0];
		}
	}

	for(int i=0;i<(m-1);i++)
	{
		printf("%.0f\n",Results[i]);
	}
	printf("%.0f",Results[m-1]);

	return 0;
}