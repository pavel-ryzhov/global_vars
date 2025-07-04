#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>


struct int_strange
{
	int i;
	bool b;
};



int shag(int place,int NN,int_strange* mtr,int end_of_graph,int* path_g,int numb_shag,int *nomer_varianta)
{
int iii;
bool wr_end=false;
int sum=0;   

int ii=*(nomer_varianta+numb_shag);
while ( ( ((*(mtr+(place)*NN+ii)).i==0) && ((*(mtr+(place)*NN+ii)).b==false) ) || (ii==*(path_g+numb_shag-2) ) && (ii<=NN-1) )
	{ii++;};

if (((ii>=NN-1)&&(((*(mtr+(place)*NN+NN-1)).i==0))&&(((*(mtr+(place)*NN+NN-1)).b==false)))||(ii>NN-1)) 
{wr_end=true;};

if ((ii==end_of_graph)&&(wr_end!=true)) 
{
	*(path_g+numb_shag)=ii;
	for (int jjj=0;jjj<numb_shag;jjj++)
	{
	sum=sum+(*(mtr+(*(path_g+jjj)*NN+(*(path_g+jjj+1))))).i; //жесть m[1,2]+m[2,3]
	}
	return sum;
};

if ((wr_end==true))
{
	(*(nomer_varianta+numb_shag))=0;
	(*(nomer_varianta+numb_shag-1))++;
	iii=shag(*(path_g+numb_shag-2),NN,mtr,end_of_graph,path_g,numb_shag-1,nomer_varianta);
}
else 
{
	(*(path_g+numb_shag))=ii;
	*(nomer_varianta+numb_shag)=ii;
	iii=shag(ii,NN,mtr,end_of_graph,path_g,numb_shag+1,nomer_varianta);
};  

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

int_strange * mtrx;
mtrx=(int_strange*)malloc(sizeof(int_strange)*N*N);
for (int j1=0;j1<N*N;j1++)
{
	(*(mtrx+j1)).i=0;
	(*(mtrx+j1)).b=false;
};

for (int j=0;j<N-1;j++)  //заполнили матрицу путешествий
{
   scanf("%d %d %d",&x,&y,&r);
   (*(mtrx+N*(x-1)+(y-1))).i=r;
   (*(mtrx+N*(y-1)+(x-1))).i=r;
   (*(mtrx+N*(x-1)+(y-1))).b=true;
   (*(mtrx+N*(y-1)+(x-1))).b=true;

};

int nachalo_puti=0;
int konec_puti=11;

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
		printf("%d\n",shag(nachalo_puti-1,N,mtrx,konec_puti-1,path_g1,1,n_var));
		//for (int j1111=0;j1111<N;j1111++)
		//	{*(path_g1+j1111)=0;};
		for (int jj11=0;jj11<N;jj11++)
			{*(n_var+jj11)=0;};

	}
	else printf("%d\n",0);
};
return 0;
}