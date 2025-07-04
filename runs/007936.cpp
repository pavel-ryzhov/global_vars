#include <iostream>
using namespace std;

struct rebra
{
        int a,b,length;
};

int deikstr(rebra*,int,int,int);

int main()
{
        int N,M,a,b;
        cin>>N;
        rebra *v=new rebra[N-1];
        for (int i=0;i<N-1;i++)
                cin>>v[i].a>>v[i].b>>v[i].length;
        cin>>M;
        int *v1=new int[M];
        for (int i=0;i<M;i++)
        {
                cin>>a>>b;
                v1[i]=deikstr(v,a,b,N);
        }
        for (int i=0;i<M;i++) cout<<v1[i]<<endl;
        delete[] v,v1;
	return 0;
}

int deikstr(rebra* v,int a,int b,int N)
{
        int *l=new int[N+1];
        int min=40001,k=a;
        for (int i=0;i<=N;i++) l[i]=40001;
        l[a]=0;
        for (int i=0;i<N;i++)
        {
                for (int j=0;j<N-1;j++)
                {
                        if (v[j].a==a && l[v[j].b]!=-1 && v[j].length+l[a]<l[v[j].b])
                                l[v[j].b]=v[j].length+l[a];
                        if (v[j].b==a && l[v[j].a]!=-1 && v[j].length+l[a]<l[v[j].a])
                                l[v[j].a]=v[j].length+l[a];
                }
                l[a]=-1;
                for (int j=0;j<=N;j++)
                {
                        if (l[j]<min && l[j]!=-1)
                        {
                                min=l[j];
                                k=j;
                        }
                }
                a=k;
                if (a==b)
                {
                        delete[] l;
                        return min;
                }
                min=40001;
        }
        delete[] l;
        return 0;
}
