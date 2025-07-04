///////////////////////////////////////////////////////////////
//проверка правильности алгоритма, код написан каряво и некрасиво
//////////////////////////////////////////////////////////////
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

struct DistBetwPoints{
int first;
int second;
int len;
int flag;
};

int main(int argc, char ** argv){

int CountOfPoints;
cin>>CountOfPoints;

DistBetwPoints *tree;
tree = new DistBetwPoints[CountOfPoints-1];

for(int i=0; i<CountOfPoints-1; ++i )
{
    cin>>tree[i].first;
    cin>>tree[i].second;
    cin>>tree[i].len;
    tree[i].flag=0;
}

int PariVersh;
cin>>PariVersh;
int F,S;
int* A;
A = new int[CountOfPoints];
int sum=0;

int ind=0;

for(int k=0; k<PariVersh; ++k)
{
    cin>>F;
    cin>>S;
    ind=0;
    
    for(int i=CountOfPoints-1;i>-1;--i)
    {
	if((F==tree[i].second)&&(F>tree[i].first))
	{  
	    F=tree[i].first;
	    ++tree[i].flag;
	    ++ind;
	}
    }

	for(int i=CountOfPoints-1;i>-1;--i)
	{
	    if((F==tree[i].first)&&(F>tree[i].second))
	    {
		F=tree[i].second;
		++tree[i].flag;
		++ind;
	    }
	}

    for(int i=CountOfPoints-1;i>-1;--i)
    {
	if((S==tree[i].second)&&(S>tree[i].first))
	{
	    S=tree[i].first;
	    ++tree[i].flag;
	    ++ind;
	}
    }
    
    for(int i=CountOfPoints-1;i>-1;--i)
	{
	    if((S==tree[i].first)&&(S>tree[i].second))
	    {
		S=tree[i].second;
		++tree[i].flag;
		++ind;
	    }
	}
/*	
    for(int i=CountOfPoints-1; i>-1;--i)
    {
	if(tree[i].flag==1)
	{
	    sum = sum + tree[i].len;
	}
    }
*/
    if(ind==0)
    {
	    for(int i=CountOfPoints-1;i>-1;--i)
	    {
		if((F==tree[i].second)&&(F<tree[i].first))
		{	  
		    F=tree[i].first;
		    ++tree[i].flag;
		}
	    }

	    for(int i=CountOfPoints-1;i>-1;--i)
	    {
		if((F==tree[i].first)&&(F<tree[i].second))
		{
		    F=tree[i].second;
		    ++tree[i].flag;
		}
	    }

	    for(int i=CountOfPoints-1;i>-1;--i)
	    {
		if((S==tree[i].second)&&(S<tree[i].first))
		{
		    S=tree[i].first;
		    ++tree[i].flag;
		}
	    }
	    
	    for(int i=CountOfPoints-1;i>-1;--i)
	    {
		if((S==tree[i].first)&&(S<tree[i].second))
		{
		    S=tree[i].second;
		    ++tree[i].flag;
		}
	    }
    }	    
	    for(int i=CountOfPoints-1; i>-1;--i)
	    {
		if(tree[i].flag==1)
		{
		    sum = sum + tree[i].len;
		}
	    }
	    	    
    
    



    for(int i=0; i<CountOfPoints-1; ++i)
    {
	cout << tree[i].flag << "  ";
    }
    cout<<endl;
    
    
    
    A[k]=sum;
    sum=0;
    for(int i=0; i<CountOfPoints-1;++i)
    {
	tree[i].flag=0;
    }
    
    
    
}

for(int i=0; i<PariVersh; ++i)
{
    cout<<A[i]<<" ";
}


for(int i=0; i<CountOfPoints; ++i)
{
    cout<<tree[i].first<<" ";
    cout<<tree[i].second<< " ";
    cout<<tree[i].len<<" " ;
    cout<<endl;
}




delete(tree);
return 0;
}