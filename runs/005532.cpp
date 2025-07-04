
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits>
#include <vector>


using namespace std;

class ShortestPath
{
public:
	int VertNum;//vertex quantity;
	int FindPathNum;//vertex pairs quantity;

	vector<int> EdgeBegs;//edges;
	vector<int> EdgeEnds;

	vector<int> Verts1;//vertex pairs;
	vector<int> Verts2;

	vector<int> Paths;// vertex path length from root in DFS
	vector<vector<int> > Tree;//vertex adjacency
	int** LenMatrix;//edge lengths between vertexes
	int** PathMatrix;//ancestor-descendant paths lengths between vertexes 
	vector<int> Order;//DFS walk order	
	vector<int> First;//first position in DFS
	vector<int> ExtraDFSVisited;//so that DFS does not cycle
	vector<int> Height;//vertex height 
	
	ShortestPath();
	~ShortestPath();
	void Create();//reads data 
	void ExtraDFS(int root, int path, int height,vector<int> branch);//counts ancestor-descendant paths lengths, walk order, heights
	void FirstFill();//counts First
	int CountPath(int v1, int v2);//counts paths for v1, v2
	void ProcessPairs();//counts paths for all pairs and outputs them
};

ShortestPath::ShortestPath(){}
ShortestPath::~ShortestPath()
{
	for(int i=0;i<VertNum; i++)
	{
		delete LenMatrix[i];
	}
	delete LenMatrix;

	for(int i=0;i<VertNum; i++)
	{
		delete PathMatrix[i];
	}
	delete PathMatrix;
}

void ShortestPath::Create()
{
	int a;
	int b;
	int c;

	int e;
	int d;
		
	scanf("%d", &VertNum);

	LenMatrix=new int*[VertNum];

	for(int i=0;i<VertNum; i++)
	{
		LenMatrix[i]=new int[VertNum];
	}
		PathMatrix=new int*[VertNum];

	for(int i=0;i<VertNum; i++)
	{
		PathMatrix[i]=new int[VertNum];
	}

	for(int i=0; i<VertNum; i++)
	{
		vector<int> aux;
		Tree.push_back(aux);

		ExtraDFSVisited.push_back(0);
		LenMatrix[i][i]=0;
		PathMatrix[i][i]=0;
		Height.push_back(0);
		First.push_back(-1);
		Paths.push_back(0);

	}

	for(int i=0; i<VertNum-1; i++)
	{
		scanf("%d", &a);
		scanf("%d", &b);
		scanf("%d", &c);

		EdgeBegs.push_back(a);
		EdgeEnds.push_back(b);

		Tree.at(a-1).push_back(b);
		Tree.at(b-1).push_back(a);
		LenMatrix[a-1][b-1]=c;
		LenMatrix[b-1][a-1]=c;
	}

	scanf("%d", &FindPathNum);

	for(int i=0; i<FindPathNum; i++)
	{
		scanf("%d", &e);
		scanf("%d", &d);
		
		Verts1.push_back(e);
		Verts2.push_back(d);
	}

}

void ShortestPath::ExtraDFS(int root, int path, int height, vector<int> branch)
{	
	vector<vector<int> >::iterator Pos;
	vector<int>::iterator Move;

	Pos = Tree.begin()+(root-1);

	Order.push_back(root);

	Height.at(root-1)=height;
	Paths.at(root-1)=path;	

	for (Move=branch.begin(); Move<branch.end(); Move++)
	{
		PathMatrix[root-1][(*Move)-1]=path-Paths.at((*Move)-1);
		PathMatrix[(*Move)-1][root-1]=path-Paths.at((*Move)-1);
	}

	branch.push_back(root);

	for (Move = (*Pos).begin(); Move<(*Pos).end(); Move++)
	{
		if(ExtraDFSVisited.at((*Move)-1)==0)
		{
			ExtraDFSVisited.at((*Move)-1)=1;
			ExtraDFS(*Move, (path+LenMatrix[root-1][(*Move)-1]), height+1,branch);
			Order.push_back(root);
		}				
	}

}

void ShortestPath::FirstFill()
{
	vector<int>::iterator Move;

	for(Move=Order.begin(); Move<Order.end(); Move++)
	{		
		if(First.at(*Move-1)==-1)
			First.at(*Move-1)=(Move-Order.begin());		
	}
}

void ShortestPath::ProcessPairs()
{
	int Res=0;
		
	for(int i=0; i<FindPathNum; i++)
	{
		Res=CountPath(Verts1.at(i),Verts2.at(i));
		printf("%d\n", Res);
	}
	
}

int ShortestPath::CountPath(int v1,int v2)
{
	vector<int>::iterator Move;
	int Sum1=0;
	int Sum2=0;
	int Pos1;
	int Pos2;
	int x = First.at(v1-1);
	int y = First.at(v2-1);
	if(x<=y)
	{
		Pos1=x;
		Pos2=y;
	}
	else
	{
		Pos1=y;
		Pos2=x;
	}
	
	int min=std::numeric_limits<int>::max();
	int LCA=0;

	for(Move =Order.begin()+Pos1; Move<Order.begin()+Pos2; Move++)
	{
		if(Height.at(*Move-1)<min)
		{
			min = Height.at(*Move-1);
			LCA = *Move;
		}
	}

	if(LCA==v1||LCA==v2||!LCA)
	{
		Sum1=PathMatrix[v1-1][v2-1];
		return(Sum1);
	}
	else
	{
		Sum1=PathMatrix[v1-1][LCA-1];//OtherCountPath(v1,LCA);
		Sum2=PathMatrix[v2-1][LCA-1];//OtherCountPath(v2,LCA);
		return (Sum1+Sum2);
	}	

}


int main()
{
	ShortestPath X;
	X.Create();
	if(X.VertNum<2)
	{
		printf("%d\n",0);
	}
	else
	{
	vector<int> a;
	X.ExtraDFSVisited.at(X.EdgeBegs.at(0)-1)=1;
	X.ExtraDFS(X.EdgeBegs.at(0),0,0,a);
	X.FirstFill();
	X.ProcessPairs();
	}
	return 0;
}


