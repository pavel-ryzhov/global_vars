
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
	vector<int> EdgeLens;

	vector<int> Verts1;//vertex pairs;
	vector<int> Verts2;

	vector<vector<int> > Tree;//vertex adjacency
	int** LenMatrix;//edge lengths between vertexes
	vector<int> Order;//DFS walk order
	vector<vector<int> > First;//vertex positions in Order
	vector<int> DFSVisited;//so that DFS does not cycle
	vector<int> Height;
	
	ShortestPath();
	~ShortestPath();
	void Create();//reads data 
	void DFS (int root, int height);
	void FirstFill(); 
	vector<int> FindBestPos(int v1, int v2);//finds closest positions in Order for vertexes v1,v2
	int CountPath(int v1, int v2);//sums up the edges' weights
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

	for(int i=0; i<VertNum; i++)
	{
		vector<int> aux;
		Tree.push_back(aux);
		DFSVisited.push_back(0);
		LenMatrix[i][i]=0;
		Height.push_back(0);
	}

	for(int i=0; i<VertNum-1; i++)
	{
		scanf("%d", &a);
		scanf("%d", &b);
		scanf("%d", &c);

		EdgeBegs.push_back(a);
		EdgeEnds.push_back(b);
		EdgeLens.push_back(c);

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


void ShortestPath::DFS(int root, int height)
{
	vector<vector<int> >::iterator Pos;
	vector<int>::iterator Move;

	Pos = Tree.begin()+(root-1);

	Order.push_back(root);
	Height.at(root-1)=height;

	for (Move = (*Pos).begin(); Move<(*Pos).end(); Move++)
	{
		if(DFSVisited.at((*Move)-1)==0)
		{
			DFSVisited.at((*Move)-1)=1;
			DFS(*Move, height+1);
			Order.push_back(root);
		}

		
	}

}

void ShortestPath::FirstFill()
{
	vector<int>::iterator Move;

	for(int i=0; i<=VertNum; i++)
	{
		vector<int> a;
		First.push_back(a);
	}	
	for(Move=Order.begin(); Move<Order.end(); Move++)
	{
		First.at(*Move).push_back(Move-Order.begin());
		
	}
}

vector<int> ShortestPath::FindBestPos(int v1, int v2)
{
	vector<int> Res;

	vector<int>::iterator MoveV1;
	vector<int>::iterator MoveV2;


	int minDist=std::numeric_limits<int>::max();
	int candDist=std::numeric_limits<int>::max();
	int Pos1=0;
	int Pos2=0;

	for(MoveV1=First.at(v1).begin(); MoveV1<First.at(v1).end(); MoveV1++)
	{
		for(MoveV2=First.at(v2).begin(); MoveV2<First.at(v2).end(); MoveV2++)
		{
			candDist=abs((*MoveV2)-(*MoveV1));
			if(candDist<minDist)
			{
				minDist=candDist;
				Pos1=*MoveV1;
				Pos2=*MoveV2;
			}
		}
	}

	if(Pos1<Pos2)
	{
		Res.push_back(Pos1);
		Res.push_back(Pos2);
	}
	else
	{
		Res.push_back(Pos2);
		Res.push_back(Pos1);
	}

	return Res;
}
int ShortestPath::CountPath(int v1, int v2)
{
	if(v1==v2)
	{
		return 0;
	}
	int Sum1=0;
	int Sum2=0;

	vector<int>::iterator Move;
	vector<int> Aux;
	Aux = FindBestPos(v1,v2);
	int Pos1=Aux.at(0);
	int Pos2=Aux.at(1);

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

	Aux = FindBestPos(v1,LCA);
	Pos1=Aux.at(0);
	Pos2=Aux.at(1);

	for(Move=Order.begin()+Pos1; Move<Order.begin()+Pos2; Move++)
	{
		Sum1=Sum1+LenMatrix[(*Move)-1][*(Move+1)-1];
	}
	Aux = FindBestPos(LCA, v2);
	Pos1=Aux.at(0);
	Pos2=Aux.at(1);

	for(Move=Order.begin()+Pos1; Move<Order.begin()+Pos2; Move++)
	{
		Sum2=Sum2+LenMatrix[(*Move)-1][*(Move+1)-1];
	}

	return Sum1+Sum2;
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
	X.DFS(X.EdgeBegs.at(0), 0);
	X.FirstFill();
	X.ProcessPairs();
	}
	return 0;
}


