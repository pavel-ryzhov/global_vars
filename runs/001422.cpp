#include <iostream>
using namespace std;

void func(int **a,int **b,int n,int m)
{
    for (int i=0;i<n;i++)
        
        for (int j=i;j<n;j++)
        {   if (i==j) b[i][j]=0;
        else {
            if (a[i][j]<a[m][i]+a[j][m])
            {
                b[i][j]=a[i][j];
                b[j][i]=a[i][j];
            }
            else {
                 b[i][j]=a[m][i]+a[j][m]; b[j][i]=a[m][i]+a[j][m];}
                
                       }
        }
        }

                    





int main()
{ 
    int n,i,t,INF=1000000000;
    cin>>n;
    int **a,**b;
    a=new int *[n];
    b=new int *[n];
    
    for (i=0;i<n;i++)
    {
        a[i]=new int [n];
        b[i]=new int [n];
    }
    int j,k,c,m;
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
        {
            a[i][j]=INF;
            b[i][j]=INF;
        }
    
    for (k=0;k<n-1;k++)
    {
        cin>>i>>j>>c;
        a[i-1][j-1]=c;
        a[j-1][i-1]=c;
    }
    for (i=0;i<n;i++)

        if (i%2==0) {k=0; func(a,b,n,i);} else { k=1; func(b,a,n,i);}
 
    cin>>m;
    int **ab;
    ab=new int *[m];
    for(i=0;i<m;i++)
        ab[i]=new int [2];
    for(t=0;t<m;t++)
    {
        cin>>i>>j;
       ab[t][0]=i-1;
        ab[t][1]=j-1;
    }
 for (i=0;i<n;i++)
        for (j=0;j<n;j++)
        {
         if (a[i][j]==INF)   a[i][j]=0;
         if (b[i][j]==INF)   b[i][j]=0;
        }

    for(t=0;t<m;t++)
    {   
        if (k==0) cout<<b[ab[t][0]][ab[t][1]]<<endl; else  cout<<a[ab[t][0]][ab[t][1]]<<endl;
    }
   
      delete a;
    delete b;
    delete ab;
return 0;
}

