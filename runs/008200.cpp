#include <iostream>
using namespace std;
int max(int x, int y)
{
	if(x>=y) return x;
	return y;
}
int main()
{	
	struct node 
	{	
		int info,s;
		struct node *next;
	};
	typedef node *NodePtr;	
	NodePtr *head;
	NodePtr *p;			
	NodePtr *tail;			
		
	int i,tn,tk,dl,n,m,xn,xk, *pt, *fl, j, *rez;
	long sum;
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

	
	pt=new int[n];
	fl=new int[n];

	cin>>m;
	rez=new int[m];
	int k=0;
	for(i=0;i<m;i++)
	{
		cin>>xn>>xk;
		for(j=0;j<n;j++){pt[j]=0; fl[j]=0;}
	

		pt[xn-1]=head[xn-1]->s;
		fl[xn-1]=1;
		k=0;
		while(k==0)
		{

			for(j=0;j<n;j++)
			{
				if((pt[j]!=0 || fl[j]==1)&&fl[j]!=2)
				{p[j]=head[j]; 
					sum=pt[j];
					fl[j]=2;
					while(p[j]!=NULL)
					{	
						if(p[j]->info!=xk)
						{	
						pt[(p[j]->info)-1]=p[j]->s + sum;
						fl[(p[j]->info)-1]=1;
						p[j] = p[j]->next;
						}
						else
						{pt[(p[j]->info)-1]=p[j]->s + sum;
						fl[(p[j]->info)-1]=1;
						rez[i]=pt[(p[j]->info)-1]; k=1; break;
						}
					}
				}
			}
		}
	}
	for(i=0;i<m;i++)cout<<rez[i]<<endl;
	return 0;
}
