#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

int shag(int NN,int* mtr,int beg_of_graph,int end_of_graph,int *path_g,int *nomer_varianta)
{
int ii;
int sum=0;   
int numb_shag=0,place=beg_of_graph;
while (!(place==end_of_graph))
{
	numb_shag++;
	ii=*(nomer_varianta+numb_shag);
    while (  ((*(mtr+(place)*NN+ii))==-1) || (ii==*(path_g+numb_shag-2) ) && (ii<=NN-1) )
		{ii++;};
	if ( ( (ii>=NN-1) && ((*(mtr+(place)*NN+NN-1))==-1) ) || (ii>NN-1) )
	{
		place=*(path_g+numb_shag-2);
		(*(nomer_varianta+numb_shag))=0;
	    (*(nomer_varianta+numb_shag-1))++;
		numb_shag-=2;
	}
	else 
	{
		place=ii;
		(*(path_g+numb_shag))=ii;
		*(nomer_varianta+numb_shag)=ii;
	};
};
for (int jjj=0;jjj<numb_shag;jjj++)
	{sum=sum+(*(mtr+(*(path_g+jjj)*NN+(*(path_g+jjj+1)))));};
return sum;
};




int main()
{
 
int N; //chislo wershin
 
scanf("%d",&N);

int x,y,r;

if (N==1) 
{
	scanf("%d",&x);
	scanf("%d %d",&r,&y);
	if ((r==y)&&(y==x)) {printf("0"); return 0;}
	else return -1;
};

int* mtrx;
mtrx=(int*)malloc(sizeof(int)*N*N);
for (int j1=0;j1<N*N;j1++)
{*(mtrx+j1)=-1;};

for (int j=0;j<N-1;j++)  //заполнили матрицу путешествий
{
   scanf("%d %d %d",&x,&y,&r);
   (*(mtrx+N*(x-1)+(y-1)))=r;
   (*(mtrx+N*(y-1)+(x-1)))=r;
};

int nachalo_puti;
int konec_puti;

int *path_g1;
path_g1=(int*)(malloc(N*sizeof(int)));
for (int j111=0;j111<N;j111++)
{*(path_g1+j111)=0;};
 
int *n_var;
n_var=(int*)(malloc(N*sizeof(int)));
for (int j11=0;j11<N;j11++)
{*(n_var+j11)=0;};

int chislo_putey=0;
scanf("%d",&chislo_putey);
for (int iij=0;iij<chislo_putey;iij++)
{
	scanf("%d %d",&nachalo_puti,&konec_puti);
	if (nachalo_puti!=konec_puti)
	{
		*path_g1=nachalo_puti-1;
		printf("%d\n",shag(N,mtrx,nachalo_puti-1,konec_puti-1,path_g1,n_var));
		for (int jj11=0;jj11<N;jj11++)
			{*(n_var+jj11)=0;};

	}
	else printf("%d\n",0);
};
return 0;
}