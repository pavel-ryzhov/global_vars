//#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<stdlib.h>

using namespace std;

struct Node
{
     Node* Left;
     Node* Right;
     Node* Parent;
     int LeftLen;
     int RightLen;  
     int ParentLen;  
     int Number;
     
     //void init()
	 //{LeftLen = RightLen = ParentLen = 0; Left = Right = Parent = NULL;}  
};

void init(Node N)
{
     N.LeftLen = N.RightLen = N.ParentLen = 0; N.Left = N.Right = N.Parent = NULL;    
}

bool IsNULL(Node *N)
{
     return (N==NULL || N==(Node*)0xbaadf00d);     
}

struct Pair
{
     int Start; int End;     
};

Node* Tree;
int Count;

Pair* AllPairs;
int PairCount;

Node* Find(Node* Start, int N)
{
     if(Start->Number==N)
         return Start;
     if(!IsNULL(Start->Left) && IsNULL(Start->Right))
         return Find(Start->Left, N);
     if(IsNULL(Start->Left) && !IsNULL(Start->Right))
         return Find(Start->Right, N);
     if(IsNULL(Start->Left) && IsNULL(Start->Right))
         return NULL;
     Node *N1 = Find(Start->Left, N);
	 if(IsNULL(N1))
     {N1 = Find(Start->Right, N);}
     return N1;
}

int FindRoute(Node* Start, Node* ToFind, int& dist, int& min, int FindUp)
{
      if(!IsNULL(Start) && !IsNULL(ToFind) && Start->Number==ToFind->Number)
            return dist;
      int l = -1; int r = -1; int p = -1; int dist1;
      if(!IsNULL(Start->Left))
      {
          dist1 = dist + Start->LeftLen; 
          l = FindRoute(Start->Left, ToFind, dist1, min, -1);
      }
      else
          l=-1;
      if(!IsNULL(Start->Right))
      {
          dist1 = dist + Start->RightLen; 
          r = FindRoute(Start->Right, ToFind, dist1, min, -1);
      }
      else
          r = -1;
      if(FindUp>0 && !IsNULL(Start->Parent))
      {
          dist1 = dist + Start->ParentLen; 
          p = FindRoute(Start->Parent, ToFind, dist1, min, 1);
      }
      else
          p = -1;
      if(min<0)
      {
               if(l>=0) min = l;
               else
               {
                    if(r>=0) min = r;
                    else
                    {
                        if(p>=0) min = p;    
                    }    
               }         
      } 
      else
      {      
              if(l>=0 && l<min)
                    min = l;
              if(r>=0 && r<min)
                    min = r;
              if(p>=0 && p<min)
                    min = p;
      }
      return -1;
      //���� ����� ������� �� ����� �� ������ - ���� �� �� ��� ������?!                      
}

void Read(ifstream& f)
{
     f>>Count;
     //cout<<"\n"<<Count;
     int i=0;
     Tree = new Node;
     init(*Tree);
     Node* Child = new Node;
     init(*Child);
     Child->Parent = Tree;
     Tree->Left = Child;
     f>>Tree->Number>>Child->Number>>Tree->LeftLen;
     Child->ParentLen = Tree->LeftLen;
     //cout<<"\n"<<Tree->Number<<Tree->LeftLen;
     for(i=2;i<Count;i++)
     {
         //printf("\n%d/%d", i, Count);
         Node* N = new Node;
         init(*N);
         int begin; f>>begin;
         int end; f>>end;
         int len; f>>len;
         N->Number = end;
         //printf("\t%d%d%d", begin, end, len);
         Node* Par = Find(Tree, begin);                       
         if(!IsNULL(Par))
         {
              if(!IsNULL(Par->Left) && !IsNULL(Par->Right))
              {
                    //��� �� �������� ������??!!             
              }  
              else
              {
                   bool bHandled = false;
                   if(!IsNULL(Par->Left))
                   {
                        if(Par->LeftLen<len)
                        {
                             Par->Right = N;
                             N->Parent = Par;
                             N->ParentLen = len; Par->RightLen = len;
                        }
                        else
                        {
                             Par->Right = Par->Left;
                             Par->RightLen = Par->Right->ParentLen;
                             Par->Left = N;
                             N->Parent = Par;
                             N->ParentLen = len; Par->LeftLen = len;    
                        }
                        bHandled = true;        
                   }
                   if(!IsNULL(Par->Right) && !bHandled)  
                   {
                         if(Par->RightLen>len)
                         {
                             Par->Left = N;
                             N->Parent = Par;
                             N->ParentLen = len; Par->LeftLen = len;                    
                         } 
                         else
                         {
                             Par->Left = Par->Right;
                             Par->LeftLen = Par->Left->ParentLen;
                             Par->Right = N;
                             N->Parent = Par;
                             N->ParentLen = len; Par->RightLen = len;         
                         }       
                   }
				   if(IsNULL(Par->Left) && IsNULL(Par->Right))
				   {
						Par->Left = new Node;
						Par->Left = N;
						Par->LeftLen = N->ParentLen = len;
						N->Parent = Par;
				   }
              }
              //printf("\tEnded");
         }
         else
         {
             //�������� �� ������. ��������?!    
         }
     }
     f>>PairCount;
     //printf("\n%d", PairCount);
     AllPairs = new Pair[PairCount];
     for(i=0;i<PairCount;i++)
     {f>>AllPairs[i].Start; f>>AllPairs[i].End;}
     //printf("\nRead end");
}

int FindMinRoute(int From, int To)
{
      Node* N1 = Find(Tree, From);
      Node* N2 = Find(Tree, To);
      int dist = 0;
      int min = -1;
      int FindUp = 1;
      if(N1==Tree)
         FindUp = 0;
      FindRoute(N1, N2, dist, min, FindUp);
	  return min;
}

void FindAll()
{
    int i=0;
    for(i=0;i<PairCount;i++)
    {
         int res = FindMinRoute(AllPairs[i].Start, AllPairs[i].End);
         if(res>=0)
             cout<<"\nFrom "<<AllPairs[i].Start<<" To "<<AllPairs[i].End<<" the min distance is "<<res;                        
         else
             cout<<"\nThe route from "<<AllPairs[i].Start<<" To "<<AllPairs[i].End<<"hasn't been found!";    
    } 
}

void FindAll2(ofstream& f)
{
	if(f==NULL)
        return;
    int i=0;
    //printf("\n%d", PairCount);
    for(i=0;i<PairCount;i++)
    {
         int res = FindMinRoute(AllPairs[i].Start, AllPairs[i].End);
         //printf("\n%d", res);
         f<<res; 
         f<<"\n";
    } 
}

int main(int argc, char* argv[])
{
	ifstream file;
	int j=0;
	int i=0;
	char *in; char* out;
	//printf("\n%d\n", argc);
	if(argc==3)
	{
		while(argv[1][j]!='\0')
		{
		//printf("%c", argv[1][j]);
		j++;
		}
		//printf("\n");
		in = (char*)calloc(j, sizeof(char));
		for(i=0;i<j;i++)
		{
			in[i] = argv[1][i];
		}
		in[i] = '\0';
		j = 0;
		while(argv[2][j]!='\0')
		{
		//printf("%c", argv[2][j]);
        j++;
		}
		//printf("\n");
		out = (char*)calloc(j, sizeof(char));
		for(i=0;i<j;i++)
		{
			out[i] = argv[2][i];
		}
		out[i] = '\0';
	}
	file.open(in);
	if(!file) return 0;
    Read(file);
	file.close();
	//printf("\nFind Start");
	//FindAll();
	ofstream outfile;
	outfile.open(out);
    FindAll2(outfile);
    outfile.close();
    char c; cin>>c;
	return 0;
}
