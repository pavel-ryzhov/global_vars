#include <iostream>
using namespace std;

struct node 
{	
		int info,s;
		struct node *next;
};
typedef node *NodePtr;	
NodePtr *head;
NodePtr *p;			
NodePtr *tail;
int  *fl, xn, xk, i;
long *pt, *rez, sum;
int max(int x, int y)
{
	if(x>=y) return x;
	return y;
}
void poisk(int xn, int xk)
{
	if(xn==xk)
	{
		rez[i]=pt[xk-1];
	}
	else
	{	
		pt[xn-1]=head[xn-1]->s;
		p[xn-1]=head[xn-1];
		fl[xn-1]=1;
		while(p[xn-1]!=NULL)
		{	
			if(fl[p[xn-1]->info-1]!=1)	
			{
				pt[(p[xn-1]->info)-1]=p[xn-1]->s + sum; 
				sum=pt[(p[xn-1]->info)-1];
				poisk(p[xn-1]->info,xk);
				p[xn-1] = p[xn-1]->next;
			}
			else
			{
				p[xn-1] = p[xn-1]->next;
			}
		}
	}
}
int main()
{				
	int tn,tk,dl,n,m, j;
	cin>>n;
	head = new NodePtr[n];
	p= new NodePtr[n];
	tail= new NodePtr[n];
	for(i=0;i<n;i++)
	{
		head[i] = new node;
		head[i]->next=NULL;
		head[i]->info=i+1;
		head[i]->s=0;
		tail[i] = head[i];
	}
	for(i=0;i<n-1;i++)
	{
		cin>>tn>>tk>>dl;
		p[tk-1] = new node;
		p[tk-1]->info = tn;
		p[tk-1]->s = dl;
		tail[tk-1]->next = p[tk-1];		
		p[tk-1]->next = NULL;
		tail[tk-1] = p[tk-1];
		p[tn-1] = new node;
		p[tn-1]->info = tk;
		p[tn-1]->s = dl;
		tail[tn-1]->next = p[tn-1];		
		p[tn-1]->next = NULL;
		tail[tn-1] = p[tn-1];
	}
	pt=new long[n];
	fl=new int[n];
	cin>>m;
	rez=new long[m];
	for(i=0;i<m;i++)
	{
		cin>>xn>>xk;
		for(j=0;j<n;j++){pt[j]=0; fl[j]=0;rez[i]=0;} 
		sum=0;
		poisk(xn,xk);
	}
	for(i=0;i<m;i++)cout<<rez[i]<<endl;
	return 0;
	
}
