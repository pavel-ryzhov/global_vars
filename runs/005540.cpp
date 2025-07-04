
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

	vector<int> Verts1;//vertex pairs;
	vector<int> Verts2;

	vector<int> Paths;// vertex path length from root in DFS
	vector<vector<int> > Tree;//vertex adjacency
	int** LenPathMatrix;//triangular ancestor-descendant paths lengths between vertexes and edge lengths also
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
	void CleanAuxilary();
};

ShortestPath::ShortestPath(){}
ShortestPath::~ShortestPath()
{
	for(int i=0;i<VertNum; i++)
	{
		delete LenPathMatrix[i];
	}
	delete LenPathMatrix;
}

void ShortestPath::Create()
{
	int a;
	int b;
	int c;

	int e;
	int d;

	vector<vector<int> >::iterator Move;
		
	scanf("%d", &VertNum);

	LenPathMatrix=new int*[VertNum];

	int Length=1;

	for(int i=0;i<VertNum; i++)
	{
		LenPathMatrix[i]=new int[Length];
		Length++; 
	}

	for(int i=0; i<VertNum; i++)
	{
		vector<int> aux;
		Tree.push_back(aux);

		ExtraDFSVisited.push_back(0);
		LenPathMatrix[i][i]=0;
		Height.push_back(0);
		First.push_back(-1);
		Paths.push_back(0);

	}

	for(int i=0; i<VertNum-1; i++)
	{
		scanf("%d", &a);
		scanf("%d", &b);
		scanf("%d", &c);

		Tree.at(a-1).push_back(b);
		Tree.at(b-1).push_back(a);
		if(a>=b)
		{
			LenPathMatrix[a-1][b-1]=c;
		}
		else
		{
			LenPathMatrix[b-1][a-1]=c;
		}
	}

	scanf("%d", &FindPathNum);

	for(int i=0; i<FindPathNum; i++)
	{
		scanf("%d", &e);
		scanf("%d", &d);
		
		Verts1.push_back(e);
		Verts2.push_back(d);
	}

	Paths.resize(Paths.size());
	Height.resize(Height.size());
	ExtraDFSVisited.resize(ExtraDFSVisited.size());
	First.resize(First.size());

	for(Move=Tree.begin(); Move<Tree.end(); Move++)
	{
		(*Move).resize((*Move).size());
	}

	Tree.resize(Tree.size());

}

void ShortestPath::ExtraDFS(int root, int path, int height, vector<int> branch)
{	
	vector<vector<int> >::iterator Pos;
	vector<int>::iterator Move;

	ExtraDFSVisited.at(root-1)=1;

	Pos = Tree.begin()+(root-1);

	Order.push_back(root);

	Height.at(root-1)=height;
	Paths.at(root-1)=path;	

	for (Move=branch.begin(); Move<branch.end(); Move++)
	{
		if(root>=(*Move))
		{
			LenPathMatrix[root-1][(*Move)-1]=path-Paths.at((*Move)-1);
		}
		else
		{
			LenPathMatrix[(*Move)-1][root-1]=path-Paths.at((*Move)-1);
		}
	}

	branch.push_back(root);

	for (Move = (*Pos).begin(); Move<(*Pos).end(); Move++)
	{
		if(ExtraDFSVisited.at((*Move)-1)==0)
		{	
			if(root>=(*Move))
			{
				ExtraDFS(*Move, (path+LenPathMatrix[root-1][(*Move)-1]), height+1,branch);
			}
			else
			{
				ExtraDFS(*Move, (path+LenPathMatrix[(*Move)-1][root-1]), height+1,branch);
			}
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
		if(v1>=v2)
		{
			Sum1=LenPathMatrix[v1-1][v2-1];
		}
		else
		{
			Sum1=LenPathMatrix[v2-1][v1-1];
		}
		return(Sum1);
	}
	else
	{
		if(v1>=LCA)
		{
			Sum1=LenPathMatrix[v1-1][LCA-1];
		}
		else
		{
			Sum1=LenPathMatrix[LCA-1][v1-1];
		}
		if(v2>=LCA)
		{
			Sum2=LenPathMatrix[v2-1][LCA-1];
		}
		else
		{
			Sum2=LenPathMatrix[LCA-1][v2-1];
		}
		return (Sum1+Sum2);
	}	

}

void ShortestPath::CleanAuxilary()
{
	vector<vector<int> >::iterator Move;
	for(Move=Tree.begin(); Move<Tree.end(); Move++)
	{
		(*Move).~vector();
	}
	Tree.clear();
	ExtraDFSVisited.clear();
	Paths.clear();
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
	X.ExtraDFS((X.Tree.at(0)).at(0),0,0,a);
	X.CleanAuxilary();
	X.FirstFill();
	X.ProcessPairs();
	}
	return 0;
}


