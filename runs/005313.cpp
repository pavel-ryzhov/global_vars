
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
	
	ShortestPath();
	~ShortestPath();
	void Create();//reads data 
	void DFS (int root);
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
		
	scanf("%d\n", &VertNum);

	LenMatrix=new int*[VertNum];

	for(int i=0;i<VertNum; i++)
	{
		LenMatrix[i]=new int[VertNum];
	}

	for(int i=1; i<=VertNum; i++)
	{
		vector<int> a;
		Tree.push_back(a);
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


void ShortestPath::DFS(int root)
{
	vector<vector<int> >::iterator Pos;
	vector<int>::iterator Move;

	Pos = Tree.begin()+(root-1);

	Order.push_back(root);

	for (Move = (*Pos).begin(); Move<(*Pos).end(); Move++)
	{
		DFS(*Move);

		Order.push_back(root);
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
	int Sum=0;

	vector<int>::iterator Move;
	vector<int> Aux;
	Aux = FindBestPos(v1,v2);
	int Pos1=Aux.at(0);
	int Pos2=Aux.at(1);

	for(Move=Order.begin()+Pos1; Move<Order.begin()+Pos2; Move++)
	{
		Sum=Sum+LenMatrix[(*Move)-1][*(Move+1)-1];
	}

	return Sum;
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
	X.DFS(X.EdgeBegs.at(0));
	X.FirstFill();
	X.ProcessPairs();
	}
	return 0;
}


