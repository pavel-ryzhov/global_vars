#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

struct Node
{
	Node *pred_ptr;
	int s;
};

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
	int i=0;
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
int main()
{
	vector <Node *> node;
	vector <int> otv;
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
			for (int i=0;i<N-1;i++)
			{
				cin>>buf1;
				cin>>buf2;
				cin>>buf3;
				
				//fscanf(file,"%d",&buf1);
				//fscanf(file,"%d",&buf2);
				//fscanf(file,"%d",&buf3);
				node[buf2-1]->pred_ptr=node[buf1-1];
				node[buf2-1]->s=buf3;				
			}
			//fscanf(file,"%d",&M);
			cin>>M;

			for (int i=0;i<M;i++)
				{
					cin>>buf1;
					cin>>buf2;
					//fscanf(file,"%d",&buf1);
					//fscanf(file,"%d",&buf2);
					S=reshadr(node[buf2-1],node[buf1-1]);
					otv.push_back(S);
				
				}
			
			
		}
	
		for (int i=0;i<M;i++){printf("%d\n",otv[i]);}
	node.clear();
	return 0;
}

