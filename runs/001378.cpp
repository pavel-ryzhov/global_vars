#include <iostream>
using namespace std;

void func(int **a,int **b,int n,int m)
{
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
        {
            if ((a[i][j]<=a[m][i]+a[j][m])&&(a[i][j]!=-1))
                           b[i][j]=a[i][j];
            else {
                if ((a[m][i]!=-1)&&(a[j][m]!=-1)) b[i][j]=a[m][i]+a[j][m];
                else { b[i][j]=a[i][j];}
                       }
        if (i==j) b[i][j]=0;
        }
}
                    





int main()
{ 
    int n,i,t;
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
            a[i][j]=-1;
            b[i][j]=-1;
        }
    
    for (k=0;k<n-1;k++)
    {
        cin>>i>>j>>c;
        a[i-1][j-1]=c;
        a[j-1][i-1]=c;
    }
    for (i=0;i<n-1;i++)

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
         if (a[i][j]==-1)   a[i][j]=0;
         if (b[i][j]==-1)   b[i][j]=0;
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

