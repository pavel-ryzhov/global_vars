#include <stdio.h>
#include <limits.h>

struct li
{
	int n1;
	int n2;
	int length;
};
li * lines=0;
bool * act=0;
int * nodes=0;

void Complines(li * &lines, int n, int nodes[])
{
	int hn=n/2;
	li * res= new li[n];
	int node_num = 0;
	int m=0;
	for(int i=0; i<hn+1; i++)
	{
		int node_num=i;
		nodes[i*2]=m;

		for(int j=0; j<n;j++)
			if(node_num==lines[j].n1)
			{
				res[m].n1=lines[j].n1;
				res[m].n2=lines[j].n2;
				res[m].length=lines[j].length;
				m++;
			}
		nodes[i*2+1]=m;
	}
	delete lines;
	lines=res;
}

void prep(bool b[],int const &n)
{
	for(int i=0;i<n;i++)
		b[i]=false;
}
int dfs(li way) 
{
    act[way.n1] = true;
    for (int i=nodes[2*way.n1]; i < nodes[2*way.n1+1]; i++)
    {
		if (act[way.n2]==true)
			return way.length;
        if ( !act[lines[i].n2])
		{
			li cway;
			cway.n1=lines[i].n2;
			cway.n2=way.n2;
			cway.length=lines[i].length;
			way.length+=dfs(cway);
		}
    }
	if (act[way.n2]==true)
		return way.length;
	return 0;
}

void getDate()
{
	int n=0;
	fscanf (stdin,"%d",&n);
	nodes=new int[n*2];
	int nl=n-1;
	lines= new li[nl*2];
	int i=0;
	while (i<nl)
	{
		fscanf(stdin,"%d %d %d",&lines[i].n1,&lines[i].n2,&lines[i].length);
		lines[i].n1--;
		lines[i].n2--;

		lines[nl*2-i-1].n1=lines[i].n2;
		lines[nl*2-i-1].n2=lines[i].n1;
		lines[nl*2-i-1].length=lines[i].length;
		i++;
	}
	Complines(lines, nl*2, nodes);

	int wn=0;
	fscanf (stdin,"%d", &wn);

	li * ways= new li[wn];

	i=0;
	int * dist=new int[n];
	act=new bool[n];
	while (i<wn)
	{
		fscanf (stdin,"%d %d", &ways[i].n1,&ways[i].n2);
		ways[i].n1--;
		ways[i].n2--;
		ways[i].length=0;
		prep(act,n);
		ways[i].length=dfs(ways[i]);
		i++;
	}


	for(i=0;i<wn;i++)
		fprintf(stdout,"%d\n",ways[i].length);

}

int main()
{
	getDate();

	return 0;
}