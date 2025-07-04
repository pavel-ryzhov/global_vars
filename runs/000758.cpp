#include<cstdio>
#include<vector>

#define MAXNODES 40000
#define MAXERR 100

using namespace std;

struct edge
{
	unsigned int end;
	unsigned int length;
};

struct node
{
	unsigned int a;
	unsigned int b;
	vector<struct edge> neighbours;
};

void init(struct node*graph,int me=0,int from=-1)
{
	int l=graph[me].neighbours.size();
	int i;
	struct edge temp;
	static int a=0;
	graph[me].a=a;
	++a;
	if(me)
	{
		for(i=0;i<l;++i)
			if(graph[me].neighbours[i].end==from)
				break;
		if(i)
		{
			temp=graph[me].neighbours[i];
			graph[me].neighbours[i]=graph[me].neighbours[0];
			graph[me].neighbours[0]=temp;
		}
	}
	for(i=(from==-1)?0:1;i<l;++i)
		init(graph,graph[me].neighbours[i].end,me);
	graph[me].b=a;
	++a;
	return;
}

void find_path(struct node*graph,unsigned int begin,unsigned int end)
{
	long len=0;
	unsigned int temp=begin;
	while(temp!=0&& !((graph[temp].a<=graph[end].a)&&(graph[end].b<=graph[temp].b)))
	{
		len+=graph[temp].neighbours[0].length;
		temp=graph[temp].neighbours[0].end;
	}
	temp=end;
	while(temp!=0&& !((graph[temp].a<=graph[begin].a)&&(graph[begin].b<=graph[temp].b)))
	{
		len+=graph[temp].neighbours[0].length;
		temp=graph[temp].neighbours[0].end;
	}
	printf("%ld\n",len);
	return;
}

int main()
{
	int n,m,status,i;
	unsigned int begin,end,length;
	struct node*graph;
	struct edge temp;
		
	try
	{
		status=scanf("%u",&n);
		if((status!=1)||(n<1)||(n>MAXNODES))
			throw "Invalid N in file\n";
		graph=new struct node[n];
		for(i=0;i<(n-1);++i)
		{
			status=scanf("%u %u %u",&begin,&end,&length);
			if((status<3)||(begin>MAXNODES)||(end>MAXNODES)||(length>MAXNODES))
				throw "Invalid graph edges in file\n";
			temp.end=end-1;
			temp.length=length;
			graph[begin-1].neighbours.push_back(temp);
			temp.end=begin-1;
			graph[end-1].neighbours.push_back(temp);
		}
		
	}
	catch(char err[MAXERR])
	{
		printf("%s",err);
		return 0;
	}
	catch(bad_alloc)
	{
		printf("Not enough memory\n");
		return 0;
	}
		
	init(graph);

	try
	{
		status=scanf("%u",&m);
		if((status!=1)||(m<1)||(m>MAXNODES))
			throw "Invalid M in file\n";
		for(i=0;i<m;++i)
		{
			status=scanf("%u %u",&begin,&end);
			if((status!=2)||(begin>MAXNODES)||(end>MAXNODES))
				throw "Invalid graph nodes in file\n";
			find_path(graph,begin-1,end-1);
		}
		
	}
	catch(char err[MAXERR])
	{
		printf("%s",err);
		return 0;
	}
	
	return 0;
}
