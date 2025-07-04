#include<stdio.h>
#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	Node *pred_ptr;
	unsigned short int s;
};
vector <Node *> node;
unsigned int N;
unsigned short int**graf; 
bool **mask;

int resh (Node*nodebuf2,Node*nodebuf1)
{
	unsigned int s=0;
	Node*nodetmp=nodebuf2;
		while (nodetmp!=nodebuf1)
		{
			s+=nodetmp->s;
			nodetmp=nodetmp->pred_ptr;		
		}
	return s;
}
int reshadr (Node*nodebuf2,Node*nodebuf1)
{
	unsigned int s=0;
	Node *nodetmp,*nodetmpb2=nodebuf2,*nodetmpb1=nodebuf1;
	while (true)
	{
		while ((nodetmpb2->pred_ptr!=nodetmpb1)&&(nodetmpb2!=nodetmpb1)&&(nodetmpb2->pred_ptr!=NULL))
		{
			nodetmpb2=nodetmpb2->pred_ptr;
		}
		if ((nodetmpb2->pred_ptr==NULL)&&nodetmpb2!=nodetmpb1){nodetmpb2=nodebuf2;nodetmpb1=nodetmpb1->pred_ptr;}
		else {nodetmp=nodetmpb1;break;};
	}
	s=s+resh(nodebuf2,nodetmp)+resh(nodebuf1,nodetmp);
	return s;
}

//bool route(int begin,int N,int graf[R][R],int mask[R][R])
//bool route(unsigned short int begin,unsigned int N,unsigned short int**graf,bool **mask)
bool route(unsigned short int begin)
{
	bool flag=false;
	for(int j=0;j<N;j++)
	{
		if(mask[begin][j])
		{
			mask[begin][j]=mask[j][begin]=0;
			flag=route(j);//,N,graf,mask);
			node[j]->pred_ptr=node[begin];
			node[j]->s=graf[begin][j];
			mask[begin][j]=mask[j][begin]=1;
		}
	}	
	return flag;
}
int main()
{
	//clock_t a,b,c,d;
	//a = clock();
	//unsigned short int **graf;
	//bool **mask;
	//int graf[R][R],int mask[R][R];
	unsigned int M,S=0;
	unsigned short int buf1,buf2,buf3;
	Node *nodetmp;

	cin>>N;

	if (N>0)
	{
		for (int i=0;i<N;i++)
		{
			nodetmp=new Node();
			nodetmp->s=0;
			nodetmp->pred_ptr=NULL;
			node.push_back(nodetmp);
		}
		graf=new unsigned short int*[N];
		mask=new bool*[N];
		for (int i=0;i<N;i++)
		{
			graf[i]=new unsigned short int[N];
			mask[i]=new bool[N];
			for (int j=0;j<N;j++)
			{
				graf[i][j]=0;
				mask[i][j]=0;
			}
		}
		for (int i=0;i<N-1;i++)
		{
			cin>>buf1;
			cin>>buf2;
			cin>>buf3;
			graf[buf1-1][buf2-1]=buf3;
			graf[buf2-1][buf1-1]=buf3;
			mask[buf1-1][buf2-1]=1;
			mask[buf2-1][buf1-1]=1;
		}
			bool flag=false;
			if (N>1){flag=route(0);}//,N,graf,mask);}
			delete[]graf;
			delete[]mask;

			cin>>M;			
			for (int i=0;i<M;i++)
			{
				cin>>buf1;
				cin>>buf2;
				S=reshadr(node[buf2-1],node[buf1-1]);
				cout<<S<<endl;
			}
		}
	node.clear();
	cin>>buf1;
	return 0;
}

