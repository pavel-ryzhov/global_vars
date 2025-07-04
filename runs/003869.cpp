#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<algorithm>

using namespace std;

int MaxNumber = 0;

struct Node2
{
	vector<Node2*> NodeList;
	vector<int> WeightList;
	int NodeListSize;
	int Number;
};

void init(Node2* N)
{
	N->NodeListSize = 0; N->Number = 0;
}
struct Pair
{
     int Start; int End;
};

Node2* Tree2;
int Count;

Pair* AllPairs;
int PairCount;

bool IsNULL(Node2* N)
{
	return (N==NULL || N==(Node2*)0xbaadf00d || N->Number<0 || N->Number>MaxNumber);
}

Node2* Find2(Node2* Start, Node2* Parent, Node2* Cur, int N)
{
	if(Cur==NULL)
		Cur=Start;
	if(Cur->Number==N)
		return Cur;
	Node2* Result = NULL;
	for(int i=0;i<Cur->NodeListSize;i++)
	{
		if((Node2*)Cur->NodeList[i]!=Start && (Node2*)Cur->NodeList[i]!=Parent)
		{
			Result = Find2(Start, Cur, (Node2*)Cur->NodeList[i], N);
			if(!IsNULL(Result))
				return Result;
		}
	}
	return NULL;
}

void Read3()
{
     cin>>Count;
     //cout<<"\n"<<Count;
     MaxNumber = Count;
     int i=0;
     Tree2 = new Node2;
	 init(Tree2);
	 if(Count!=1)
	 {
		 Node2* Child = new Node2;
		 init(Child);
		 Child->NodeList.push_back(Tree2);
		 Tree2->NodeList.push_back(Child);
		 Tree2->NodeListSize++;
		 Child->NodeListSize++;
		 int weight = 0;
		 cin>>Tree2->Number>>Child->Number>>weight;
		 Tree2->WeightList.push_back(weight);
		 Child->WeightList.push_back(weight);
	 }
	 else
	 {
		 //f>>Tree->Number;
		 Tree2->Number=1;
	 }
     //cout<<"\n"<<Tree->Number<<Tree->LeftLen;
     for(i=2;i<Count;i++)
     {
         //Node2* N = new Node2;
         int begin; cin>>begin;
         int end; cin>>end;
         int len; cin>>len;
         //N->Number = end;
         Node2* Start = Find2(Tree2, NULL, Tree2, begin);
         Node2* End = Find2(Tree2, NULL, Tree2, end);
		 if(!IsNULL(Start) && !IsNULL(End))
		 {
			 int j = 0;
			 for(j=0;j<Start->NodeListSize;j++)
			 {
				 if((Node2*)Start->NodeList[j] == End)
				 {
					 for(int k = 0;k<End->NodeListSize;k++)
					 {
						 if((Node2*)End->NodeList[k] == Start)
						 {
							 Start->WeightList[j] = End->WeightList[k] = len;
							 break;
						 }
					 }
					 break;
				 }
			 }
		 }
		 else
		 {
			 if(IsNULL(Start))
			 {
				 Start = new Node2;
				 init(Start);
				 Start->NodeList.push_back(End);
				 Start->WeightList.push_back(len);
				 End->NodeList.push_back(Start);
				 End->WeightList.push_back(len);
				 Start->NodeListSize++;
				 End->NodeListSize++;
				 Start->Number = begin;
			 }
			 else
			 {
				 //End is NULL
				 End = new Node2;
				 init(End);
				 Start->NodeList.push_back(End);
				 Start->WeightList.push_back(len);
				 End->NodeList.push_back(Start);
				 End->WeightList.push_back(len);
				 Start->NodeListSize++;
				 End->NodeListSize++;
				 End->Number = end;
			 }
		 }
     }
     cin>>PairCount;
     AllPairs = new Pair[PairCount];
     for(i=0;i<PairCount;i++)
     {cin>>AllPairs[i].Start>>AllPairs[i].End;}
}

int FindRoute2(Node2* Start, Node2* Cur, Node2* Parent, Node2* ToFind, int& dist, int& min)
{
	if(Cur==Start)
		return -1;
	if(IsNULL(Cur))
		Cur = Start;
	if(Cur==ToFind)
		return dist;
    /*cout<<"\nCur = "<<Cur<<"\tStart = "<<Start<<"\tParent = "<<Parent<<"\tToFind = "<<ToFind;
    if(!IsNULL(Cur))
        cout<<"\n"<<Cur->Number;
    else
        cout<<"\nNULL";
    if(!IsNULL(Start))
        cout<<"\t"<<Start->Number;
    else
        cout<<"\tNULL";
    if(!IsNULL(Parent))
        cout<<"\t"<<Parent->Number;
    else
        cout<<"\tNULL";
    if(!IsNULL(ToFind))
        cout<<"\t"<<ToFind->Number;
    else
        cout<<"\tNULL";*/
	for(int i=0;i<Cur->NodeListSize;i++)
	{
		Node2* Child = (Node2*)Cur->NodeList[i];
		//cout<<"\nChild "<<i<<": "<<Child<<"\tdist = "<<dist;
		if(Child!=Start && Child!=Parent)
		{
			int dist1 = dist + (int)Cur->WeightList[i];
			int res = FindRoute2(Start, Child, Cur, ToFind, dist1, min);
			if(res>=0)
			{
				if(min<0)
					min = res;
				else
				{
					if(res<min)
						min = res;
				}
				//cout<<"\tres = "<<res;
			}
		}
	}
	return -1;
}

int FindMinRoute2(int From, int To)
{
      Node2* N1 = Find2(Tree2, NULL, NULL, From);
      Node2* N2 = Find2(Tree2, NULL, NULL, To);
      int dist = 0;
      int min = -1;
	  if(From==To)
		  return 0;
	  else
		FindRoute2(N1, NULL, NULL, N2, dist, min);
	  return min;
}

void FindAll3()
{
    int i=0;
    for(i=0;i<PairCount;i++)
    {
         int res = FindMinRoute2(AllPairs[i].Start, AllPairs[i].End);
		 cout<<res<<"\n";
    }
}

int main(int argc, char* argv[])
{
	/*ifstream file;
	int j=0;
	int i=0;
	char *in; char* out;
	//printf("\n%d\n", argc);
	if(argc==3)
	{
		while(argv[1][j]!='\0')
		{
		printf("%c", argv[1][j]);
		j++;
		}
		printf("\n");
		in = (char*)calloc(j, sizeof(char));
		for(i=0;i<j;i++)
		{
			in[i] = argv[1][i];
		}
		in[i] = '\0';
		j = 0;
		while(argv[2][j]!='\0')
		{
		printf("%c", argv[2][j]);
        j++;
		}
		printf("\n");
		out = (char*)calloc(j, sizeof(char));
		for(i=0;i<j;i++)
		{
			out[i] = argv[2][i];
		}
		out[i] = '\0';
	}
	file.open(in);
	if(!file) return 0;
	cout<<"\nReading";
    Read(file);
	file.close();
	//Read2();
	//printf("\nFind Start");
	//FindAll();
	ofstream outfile;
	outfile.open(out);
	cout<<"\nFindAll";*/
	Read3();
    FindAll3();
    //outfile.close();
    //char c; cin>>c;
	return 0;
}

