#include <iostream>
using namespace std;

//метод Флойда-Уоршолла
int main()
{
        int N,M,a,b,s=0,k=1,ci=0,cj=0,q=0;
        cin>>N;
        int *w=new int[N*N+1];    //с одномерным массивом работать быстрее
        int *Ai=new int[N],*Aj=new int[N];
        for (int i=1;i<N*N;i++)
        {
                if ((i-1)%(N+1)==0) w[i]=0;
                else w[i]=40001;
        }
        for (int i=0;i<N-1;i++)
        {
                cin>>a>>b;
                cin>>M;
                w[(a-1)*N+b]=M;
                w[(b-1)*N+a]=M;
        }
        cin>>M;
        int *v=new int[M];
        while (1)
        {
                for (int i=1;i<=N;i++)
                {
                        if (w[(i-1)*N+k]!=40001)
                        {
                                Ai[ci]=i; ci++;
                        }
                        if (w[(k-1)*N+i]!=40001)
                        {
                                Aj[cj]=i; cj++;
                        }
                }
                for (int i=0;i<ci;i++)
                        for (int j=0;j<cj;j++)
                        {
                                if (w[(Ai[i]-1)*N+k]+w[(k-1)*N+Aj[j]]<w[(Ai[i]-1)*N+Aj[j]])
                                {
                                        w[(Ai[i]-1)*N+Aj[j]]=w[(Ai[i]-1)*N+k]+w[(k-1)*N+Aj[j]];
                                        q=1;
                                }
                        }
                if (k<N) {k++;q=0;ci=0;cj=0;continue;}
                if (k==N && q==1) k=1;
                else break;
        }
        for (int i=0;i<M;i++)
        {
                cin>>a>>b;
                v[i]=w[(a-1)*N+b];
        }
        for (int i=0;i<M;i++) cout<<v[i]<<endl;
        delete[] w,v,Ai,Aj;
	return 0;
}

