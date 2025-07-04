#include <stdio.h>
#include <limits.h>
//FILE * T=fopen("T20.txt","r");
		int v = -1;

struct li
{
	int n1;
	int n2;
	int length;
};
void Complines(li * &lines, int n, int nodes[])
{
	int hn=n/2;
	//for(int i=0; i<hn; i++)
	//{
	//	lines[n-i-1].n1=lines[i].n2;
	//	lines[n-i-1].n2=lines[i].n2;
	//	lines[n-i-1].length=lines[i].length;
	//}
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
		//i=j;
		//for(j=hn; j<n; j++)
		//	if(node_num==lines[j].n1)
		//	{
		//		res[m].n1=lines[j].n1;
		//		res[m].n2=lines[j].n2;
		//		res[m].length=lines[j].length;
		//		m++;
		//	}
		nodes[i*2+1]=m;
	}
	delete lines;
	lines=res;
}

void prep(int M[],bool b[],int const &n)
{
	for(int i=0;i<n;i++)
	{
		M[i]=INT_MAX;
		b[i]=false;
	}
}
void searchWay(li lines[], int dist[], bool act[],int nodes[],li &goal ,int const &cnt )
{
	prep(dist, act,cnt);
	dist[goal.n1]=0;
	int j=0;
	int to=0;
	int cWay=0;
	for (int i=0; i<cnt; i++)
	{
		v = -1;
//for(int z=0;z<cnt;z++)
//	fprintf(stdout,"%d ",dist[z]);
//puts("\n");
		for (j=0; j<cnt; j++)
		{
			if (!act[j] && (v==-1 || dist[j] < dist[v]))
				v = j;
		}
		if ((v==goal.n2)||(dist[v]==INT_MAX))
			break;

		act[v] = true;

			for(j=nodes[v*2]; j<(nodes[v*2+1]);j++)
			{
				//if (lines[j].n2==v)
				//{
					to = lines[j].n2;
					cWay = lines[j].length;

					if ((cWay + dist[v]) < dist[to])
						dist[to] = cWay + dist[v];
				//}
				//else
				//if(lines[j].n1==(v+1))
				//{
				//	to = lines[j].n2;
				//	cWay = lines[j].length;

				//	if ((cWay + dist[v]) < dist[to])
				//			dist[to] = cWay + dist[v];
				//}
			}
	}
	goal.length=dist[goal.n2];
}
void prlines (li * lines, int n)
{
	for(int i=0;i<n;i++)
		fprintf(stdout,"%d %d %d\n",lines[i].n1,lines[i].n2,lines[i].length);
}
void getDate()
{
	int n=0;
	fscanf (stdin,"%d",&n);
	int * nodes=new int[n*2];
	int nl=n-1;
	li * R= new li[nl*2];
	int i=0;
	while (i<nl)
	{
		fscanf(stdin,"%d %d %d",&R[i].n1,&R[i].n2,&R[i].length);
		R[i].n1--;
		R[i].n2--;

		

		R[nl*2-i-1].n1=R[i].n2;
		R[nl*2-i-1].n2=R[i].n1;
		R[nl*2-i-1].length=R[i].length;
		i++;
	}
//prlines(R,nl*2);
	Complines(R, nl*2, nodes);
//	puts("\n");
//prlines(R,nl*2);
	int wn=0;
	fscanf (stdin,"%d", &wn);

	li * ways= new li[wn];

	i=0;
	int * dist=new int[n];
	bool * act=new bool[n];
	while (i<wn)
	{
		fscanf (stdin,"%d %d", &ways[i].n1,&ways[i].n2);
		ways[i].n1--;
		ways[i].n2--;
		searchWay(R,dist,act,nodes,ways[i],n);
		i++;
	}


	for(i=0;i<wn;i++)
		fprintf(stdout,"%d\n",ways[i].length);

}

int main()
{
	getDate();
//	fclose(T);
	return 0;
}