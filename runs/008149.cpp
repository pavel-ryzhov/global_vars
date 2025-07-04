#include <iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define word unsigned int
using namespace std; 
int i, j, n, p, xn, xk,k,m;
int *flag;
word  *l, *e;

 
int min(int n)
{
        int i, result;
        for(i=0;i<n;i++)
                if(!(flag[i])) result=i;
        for(i=0;i<n;i++)
                if((l[result]>l[i])&&(!flag[i])) result=i;
        return result;
}
 
word minim(word x, word y)
{
        if(x<y && x>0  && y>0) return x;
        return y;
}
 
int main()
{   cin>>n; 
 flag=new int[n];       
    word **c = new word*[n];
	for(k= 0; k < n; k++)
c[k] = new word[n];
	  l=new word[n];
	 
          for(i=0;i<n-1;i++)
                {cin>>k>>j; cin>>c[k-1][j-1];
                }
        
        
        for(i=0;i<n;i++)
                for(j=0;j<n;j++){
		if(c[i][j]==0)c[i][j]=65535;
				c[j][i]=c[i][j];} 
        cin>>m;
		e =new word[m];
		for(k=0;k<m;k++){
        cin>>xn;
        cin>>xk;
        xk--;
        xn--;
        if(xn==xk)
        {
                cout<<"0"<<endl;
                continue;
        }
 
        for(i=0;i<n;i++)
        {
                flag[i]=0;
                l[i]=65535;
        }
        l[xn]=0;
        flag[xn]=1;
        p=xn;
       
		do
                {
                        for(i=0;i<n;i++)
                                if((c[p][i]!=65535)&&(!flag[i])&&(i!=p))
                                {  
                                        l[i]=minim(l[i],l[p]+c[p][i]);
                                }
                        p=min(n);
                        flag[p]=1;
                }
                while(p!=xk);
      if(l[p]!=65535)
        {              
                e[k]=l[p];
        }
        }
		for(i=0;i<m;i++){cout<<e[i]<<endl;}
		delete[] e;
		delete[] l;
		delete[] flag;
			for(k= 0; k < n; k++)delete[] c[k];
delete[] c;
		
 return 0;   
}

