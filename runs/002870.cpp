#include<stdio.h>
#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	Node *pred_ptr;
	int s;
};
struct Verh
{
	//bool flag;
	int verh;
	int s;
};
struct Graf
{
	//bool flag;
	vector <Verh*> verh;
};
vector <Node *> node;
vector <Graf *> graf;


int resh (Node*nodebuf2,Node*nodebuf1)
{
	int s=0;
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
	int s=0;
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

bool route(int begin,int pred)
{
	bool flag=false;
	int y=graf[begin]->verh.size();
	for(int j=0;j<graf[begin]->verh.size();j++)
	{
		y=graf[begin]->verh[j]->verh;
		if(graf[begin]->verh[j]->verh!=pred)
		{
			//mask[begin][j]=mask[j][begin]=0;
			flag=route(graf[begin]->verh[j]->verh,begin);
			node[graf[begin]->verh[j]->verh]->pred_ptr=node[begin];
			node[graf[begin]->verh[j]->verh]->s=graf[begin]->verh[j]->s;
			//mask[begin][j]=mask[j][begin]=1;
		}
	}	
	return flag;
}
int main()
{

	Graf *graf_ptr;
	Verh *verh_ptr;
	int N,M,S=0;
	int buf1,buf2,buf3;
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
			
		for (int i=0;i<N;i++)
		{
			graf_ptr=new Graf();
			graf.push_back(graf_ptr);
		}
		for (int i=0;i<N-1;i++)
		{
			cin>>buf1;
			cin>>buf2;
			cin>>buf3;
				
			verh_ptr=new Verh();
			verh_ptr->verh=buf2-1;
			verh_ptr->s=buf3;
			graf[buf1-1]->verh.push_back(verh_ptr);

			verh_ptr=new Verh();
			verh_ptr->verh=buf1-1;
			verh_ptr->s=buf3;
			graf[buf2-1]->verh.push_back(verh_ptr);
		}

		bool flag=false;
		if (N>1){flag=route(0,0);}
		cin>>M;			
		for (int i=0;i<M;i++)
		{
			cin>>buf1;
			cin>>buf2;
			S=reshadr(node[buf2-1],node[buf1-1]);
			cout<<S<<endl;
		}
	}
	for(int i=0;i<N;i++)
	{
		graf[i]->verh.clear();
	}
	graf.clear();
	node.clear();
	cin>>buf1;
	return 0;
}

