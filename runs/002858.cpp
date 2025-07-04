#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

int **graf;
int N;

int resh (int begin,int end, int **mask)
{
	int s=-1;
	for(int j=0;j<N;j++)
	{
		if (begin==end){s=0;return s;}
		if(mask[begin][j]>0)
		{
			if (j!=end)
			{
				mask[begin][j]=mask[j][begin]=0;
				s=resh(j,end,mask);
			}
			else {s=graf[begin][j];mask[begin][j]=mask[j][begin]=1;return s;}
			if (s!=-1){s=s+graf[begin][j];mask[begin][j]=mask[j][begin]=1;return s;}
			mask[begin][j]=mask[j][begin]=1;
		}
	}
	
	return s;
}

int main()
{
	int**mask;
	vector <int> otv;
	//int mask[R][R];
		int M,S=0;
		int buf1,buf2,buf3;
		cin>>N;
		if (N>0)
		{	
			graf=new int*[N];
			mask=new int*[N];

			for (int q=0;q<N;q++)
			{
				graf[q]=new int[N];
				mask[q]=new int[N];
			}
			for (int i=0;i<N;i++)
			{
				for (int j=0;j<N;j++)
				{
					graf[i][j]=-1;
					mask[i][j]=0;
				}
			}
			for (int i=0;i<N-1;i++)
			{
				cin>>buf1;
				cin>>buf2;
				cin>>buf3;
				graf[buf1-1][buf2-1]=buf3;
				graf[buf2-1][buf1-1]=buf3;
				mask[buf1-1][buf2-1]=1;
				mask[buf2-1][buf1-1]=1;						
			}
			cin>>M;

				for (int i=0;i<M;i++)
				{
					cin>>buf1;
					cin>>buf2;
					S=resh(buf1-1,buf2-1,mask);
					cout<<S<<endl;
					//otv.push_back(S);
					
				}		
		}
		//for (int i=0;i<M;i++){cout<<otv[i]<<endl;}
		cin>>buf1;

	return 0;
}

