#include <stdio.h>
#include <limits.h>

struct li
{
	int n1;
	int n2;
	int length;
};
void prep(int const value,int M[],bool b[],int const n)
{
	for(int i=0;i<n;i++)
	{
		M[i]=value;
		b[i]=false;
	}
}
void searchWay(li lines[], int dist[], bool act[], li &goal ,int const cnt )
{
	prep(INT_MAX, dist, act,cnt);
	dist[goal.n1-1]=0;
	for (int i=0; i<cnt; i++)
	{
		//for (int t=0;t<cnt;t++)
		//	fprintf(stdout,"%d ", dist[t]);
		//fprintf(stdout,"\n");
		int v = -1;

		for (int j=0; j<cnt; j++)
		{
			if (!act[j] && (v==-1 || dist[j] < dist[v]))
				v = j;
		}
		if (v==goal.n2-1)
			break;


			act[v] = true;

			int s=0;
			while((lines[s].n1!=(v+1))&&(s<cnt-1))
				s++;

			if(s<cnt-1)
				for(s; lines[s].n1==(v+1);s++)
				{
					int to = lines[s].n2-1;
					int cWay = lines[s].length;

					if ((cWay + dist[v]) < dist[to])
					dist[to] = cWay + dist[v];
				}
				for(s=0; s<(cnt-1);s++)
				{
					if (lines[s].n2==(v+1))
					{
						int to = lines[s].n1-1;
						int cWay = lines[s].length;

						if ((cWay + dist[v]) < dist[to])
						dist[to] = cWay + dist[v];
					}
				}
	}
	goal.length=dist[goal.n2-1];
}

void getDate()
{
	int n=0;
	fscanf (stdin,"%d",&n);
	li * R= new li[n-1];
	int i=0;
	while (i<n-1)
	{
		fscanf(stdin,"%d %d %d",&R[i].n1,&R[i].n2,&R[i].length);
		i++;
	}
	int wn=0;
	fscanf (stdin,"%d", &wn);

	li * ways= new li[wn];

	i=0;
	int * dist=new int[n];
	bool * act=new bool[n];
	while (i<wn)
	{
		fscanf (stdin,"%d %d", &ways[i].n1,&ways[i].n2);
		searchWay(R,dist,act,ways[i],n);
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