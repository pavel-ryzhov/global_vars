#include <stdlib.h>
#include <stdio.h>
#include <iostream>
//#include <fstream>
#include <vector>
#include <map>
using namespace std;


struct request{
    int ii;
    int jj;
};

struct rib
{
	int weight;
	int num;
}
;

class vertex
{
	//number of ribs
	public:	
	vector<rib> r;
	//vector<rib>::iterator it;
	int height;
	int parent;
	int num;
	int s;
	int k; 

	vertex()
	{
		k=0;
		height=0;
		parent=0;
	}
	
	 void add_new(int i, int w)
	{
		rib temp;
		temp.weight=w;
		temp.num=i;
		r.push_back(temp);
		k++;
		//cout<<i<<" "<<w<<endl;
		//cout<<k<<endl;
	}
	void add_p_and_h_and_s(int p, int h,int s1)
	{
		parent=p;
		height=h;
		s=s1;
		
	}
	int return_num()
	{
		return num;
	}

}
;


vertex *Tree;

void dfs(int parent, int h, int num, int s)
{
	//parent - num of parent, h=height, num- number of current element, s- summ of weights from the root
	int i;
        vertex *temp=&Tree[num];
        rib *R;
	temp->add_p_and_h_and_s(parent,h+1,s);
	i=temp->k;
	
	for (int j=0;j<i;j++)
	{
            R=&(temp->r[j]);
            if(R->num!=parent)
		dfs(num,h+1,R->num,R->weight+s); 
	}	
			

	
	
}

int find_s(int u, int v)
{
    int h1, h2,temp=0;
    h1=Tree[v].height;
    h2=Tree[u].height;
    temp=Tree[v].s+Tree[u].s;
    if(h2>h1)
    {
        for(int k=0;k<h2-h1;k++)
        {
            u=Tree[u].parent;
        }

    }
    if(h1>h2)
    {
        for(int k=0;k<h1-h2;k++)
        {
            v=Tree[v].parent;
        }

    }
    h1=Tree[v].height;
    h2=Tree[u].height;
    if (h1!=h2) cout<<"error!"<<endl;
    while (u!=v)
    {
        u=Tree[u].parent;
        v=Tree[v].parent;
    }
    return temp-2*Tree[v].s;
}





int main(int argc,char* argv[] )
{

   
int N, M, j, k, w;
request *REQ;


cin>>N;

Tree=new vertex[N+1];
for (int i=1;i<N;i++)
{
	cin>>j;
	cin>>k;
	cin>>w;

	Tree[j].add_new(k,w);
	Tree[k].add_new(j,w);
	
}
//int i;
cin>>M;
REQ=new request[M];
for(int it=0;it<M;it++)
{
        cin>>REQ[it].ii;
        cin>>REQ[it].jj;
        
        
}



dfs(1,0,1,0);

for(int it=0;it<M;it++)
{
        
        cout<<find_s(REQ[it].ii,REQ[it].jj)<<endl;
}

return 0;


}
