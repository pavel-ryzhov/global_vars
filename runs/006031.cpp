#include <iostream>
#include <stdio.h>



using namespace std;

int main(int argc, char * argv [])
{
int n;
FILE *fp;
FILE * pFile;
pFile = fopen ("output.txt","w");
fp=fopen("in.txt", "r");
fscanf (fp,"%d ",&n);

bool *b=new bool [n];
int *d=new int[n];
int q,i,j,m,v;
int t,p,k,f;

int **a=new int *[n];
for (k=0;k<n;k++)
{
	a[k]=new int[n];}

for (i=0;i<n;i++)
{
	for (j=0;j<n;j++)
	{
		a[i][j]=-1;
	}
}

for(p=0;p<n;p++)
{
a[p][p]=0;
}

for(i=0;i<n-1;i++)
{
fscanf (fp,"%d ",&t);
fscanf (fp,"%d ",&p);
fscanf (fp,"%d ",&k);

a[t-1][p-1]=k;
a[p-1][t-1]=k;
}

fscanf (fp,"%d ",&t);

for (k=0;k<t;k++)
{
	fscanf (fp,"%d ",&q);
	fscanf (fp,"%d ",&f);
	f=f-1;

	for (i=0; i<6;i++)
	{b[i]=false;}

	for (i=0; i<6;i++)
	{d[i]=10000;}

	d[q-1]=0;

	for (i=0;i<n;i++)
	{
		m=1000;
		for(j=0;j<n;j++)
		{
			if ((d[j]<=m) &&(!b[j]))
			{
				m=d[j];
				v=j;
			}
		}
			b[v]=true;
			for(j=0;j<n;j++)
				if ((a[v][j]!=-1)&&((!b[j])&&((d[v]+a[v][j])<d[j])))
					d[j]=d[v]+a[v][j];

		

	}

	
  
     fprintf (pFile, "%d",d[f]);
	fprintf (pFile, "\n");

}
	delete[]b;
	delete[]d;
	delete[]a;
	fclose (fp);
	fclose (pFile);
	return 0;
}



