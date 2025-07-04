#include <stdio.h>

typedef unsigned short int rast;
typedef unsigned int puti;
rast **M_smeg, *flag;
puti *l;
#define oo 1600000000 //40000*40000 

int min(int n)
{
	int i, result;
	for(i=0;i<n;i++)
		if(!(flag[i])) result=i;
	for(i=0;i<n;i++)
		if((l[result]>l[i])&&(!flag[i])) result=i;
	return result;
}
unsigned int minim(puti x, puti y)
{
	if(x<y) return x;
	return y;
}
int main(int argc, char * argv[])
{
	int i, j, n, p, xn, xk, M;
	int beg, en, len; //начало конец и длина ребра

	scanf("%d\n",&n);
			
	flag = new rast[n]; 
	l = new puti[n];
	M_smeg =  new rast *[n];
	for(i = 0; i < n; i++) 
	{
		M_smeg[i] = new rast[n]; 
		for(j=0;j<n;j++)
			if (i==j) M_smeg[i][j]=0;
			else M_smeg[i][j]=65535;//бесконечность	
	}	

	for(i=1;i<n;i++)
	{	
	    scanf("%d %d %d\n", &beg, &en, &len); 
		beg--; 	en--;
		M_smeg[beg][en]=len;
		M_smeg[en][beg]=len;
	}
		
	scanf("%d\n",&M);
	for (rast nz = 0; nz<M; nz++)
	{
		scanf("%d %d\n", &xn, &xk); 
		if(xn==xk){
			printf("%d\n", 0);
			continue;
		}
		
		xk--;	xn--;
		for(i=0;i<n;i++)
		{
			flag[i]=0;//вершины не помечены
			l[i]= oo;//путь до каждой не известен
		}
		l[xn]=0;
		flag[xn]=1;
		p=xn;
		do
		{
			for(i=0;i<n;i++)
				if((M_smeg[p][i]!=65535)&&(!flag[i])&&(i!=p))
					l[i]=minim(l[i],l[p]+M_smeg[p][i]);
			p=min(n);
			flag[p]=1;
		}
		while(p!=xk);
		printf("%d\n", l[p]);
	}
	
	for(i = 0; i < n; i++ ) 
		delete[] M_smeg[i]; 
	delete[] M_smeg;
	delete[] l;
	delete[] flag;

	return 0;
}

