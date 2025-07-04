#include <vector>
#include <cstdio>

using namespace std;

unsigned int N, m;
int l;
vector <vector< unsigned int > > ParentNodes;
vector <vector< unsigned int > > ParentNodesWeight;
vector <vector< unsigned int > > MainGraph;
vector <vector< unsigned int > > Weight;
vector < double > Results;

vector< unsigned int > NumberOfIn, NumberOfOut;
vector< bool > Passed;
unsigned int StepNumber;

void DFS(unsigned int Node,unsigned int Parent = 0,unsigned int len=0)
{
	ParentNodes[Node][0] = Parent;
	ParentNodesWeight[Node][0]=len;

	NumberOfIn[Node] = StepNumber;
	Passed[Node] = true;
	StepNumber++;
	for (unsigned int i=1; i<=l; ++i)
	{
		if( (i-1) < ParentNodes[ParentNodes[Node][i-1]].size())
		{
			ParentNodes[Node].push_back(ParentNodes[ParentNodes[Node][i-1]][i-1]);
			ParentNodesWeight[Node].push_back(ParentNodesWeight[ParentNodes[Node][i-1]][i-1]);
			if( ParentNodes[ParentNodes[Node][i-1]][i-1] == 0 )
			{
				break;
			}
		}
		else
		{
			ParentNodes[Node].push_back(ParentNodes[ParentNodes[Node][i-1]].back());
			ParentNodesWeight[Node].push_back(ParentNodesWeight[ParentNodes[Node][i-1]].back());
			if( ParentNodes[ParentNodes[Node][i-1]].back() == 0 )
			{
				break;
			}
		}
	}
	for (unsigned int i=0;i<((unsigned int)MainGraph[Node].size());i++)
	{
		unsigned int NextNode = MainGraph[Node][i]; 
		len = Weight[Node][i];
		if (!Passed[NextNode])
		{
			DFS(NextNode, Node, len);
		}
	}
	NumberOfOut[Node] = StepNumber;
	StepNumber++;
}

bool IsParentLine (unsigned int a,unsigned int b)
{
	return (NumberOfOut[a] >= NumberOfOut[b]) && (NumberOfIn[a] <= NumberOfIn[b]);
}

unsigned int LCA(unsigned int a,unsigned int b)
{
	if (IsParentLine(a, b))  return a;
	if (IsParentLine(b, a))  return b;
	for (int i=l; i>=0; --i)
	{
		if(i >= ParentNodes[a].size())
		{
			i = ParentNodes[a].size()-1;
		}
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

	NumberOfOut.resize(N);
	ParentNodes.resize(N);
	NumberOfIn.resize(N);
	MainGraph.resize(N);
	ParentNodesWeight.resize(N);
	Weight.resize(N);
	Passed.resize(N);

	unsigned int Start=0;
	unsigned int Finish=0;
	unsigned int Len=0;
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

	unsigned int x=0;
	unsigned int y=0;
	unsigned int c=0;
	Results.resize(m);
	for(unsigned int i=0;i<m;i++)
	{
		scanf ("%d %d",&x,&y);
		x--;
		y--;
		c=LCA(x, y);

		unsigned int pos=x;
		unsigned int Tmp1=0;
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

	for(unsigned int i=0;i<(m-1);i++)
	{
		printf("%.0f\n",Results[i]);
	}
	printf("%.0f",Results[m-1]);
	return 0;
}