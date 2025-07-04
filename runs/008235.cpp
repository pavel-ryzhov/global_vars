#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
struct adj_v_d{
	int v;
	int dist;
};

typedef vector<adj_v_d> adj_t;
bool r=1;
vector<int> order;
struct vert{
	adj_t adj;
	int parent;
	int dist_from_par;
	char stat;
};

void dfs(vert *myvert, int v)
{
order.push_back(v);
int i;
myvert[v-1].stat = 1;		
for(i=0;i<myvert[v-1].adj.size();i++)
	{
	if(myvert[ myvert[v-1].adj[i].v-1 ].stat == 0)
		{						
		dfs(myvert,myvert[v-1].adj[i].v);		
		order.push_back(v);				
		}
	myvert[ myvert[v-1].adj[i].v-1 ].stat = 2;
	}
}

void printf_vec(vector<int> v, const char *str)
{
int i;
for(i=0;i<v.size();i++)
	cout<<v[i]<<" ";
cout<<str<<endl;
}

void build (int *t, vector<int> a, int v, int tl, int tr) {
	if (tl == tr)
		t[v] = a[tl];
	else {
		int tm = (tl + tr) / 2;
		build (t,a, v*2, tl, tm);
		build (t,a, v*2+1, tm+1, tr);
		t[v] = min (t[v*2], t[v*2+1]);
	}
}
	
int get_min (int *t, int v, int tl, int tr, int l, int r) {
	if (l > r)
		return 9990;
	if (l == tl && r == tr)
		return t[v];
	int tm = (tl + tr) / 2;
	return min( get_min (t, v*2, tl, tm, l, min(r,tm)) , get_min (t, v*2+1, tm+1, tr, max(l,tm+1), r));
}

int lca(int *t, vector<int> order_h, vector<int> order, vector<int> first,int v1, int v2)
{
int minv=get_min(t, 1, 0, order_h.size()-1, min(first[v1-1]-1,first[v2-1]-1), max(first[v2-1]-1,first[v1-1]-1));	
int i;
for(i=min(first[v1-1]-1,first[v2-1]-1); i<max(first[v2-1]-1,first[v1-1]-1); i++)
	if(order_h[i]==minv)
		break;
return order[i];
}


int calc_path(int v1, int v2, vert *myvert, int lca_val)
{
int i,path=0;
i=v1;
while(i != lca_val)
	{
	path += myvert[i-1].dist_from_par;
	i = myvert[i-1].parent;	
	}
i=v2;
while(i != lca_val)
	{
	path += myvert[i-1].dist_from_par;
	i = myvert[i-1].parent;	
	}	
return path;
}

/* main */
int main()
{
adj_v_d adv_tmp;
int v1=8, v2=15,lca_val,path=0;
vert *myvert,tmp_vert;
int num_verts,i,j,sv,dv,dist;
scanf("%d",&num_verts);
myvert = new vert[num_verts];
for(i=0;i<num_verts-1;i++)
	{
	scanf("%d %d %d",&sv,&dv,&dist);
	adv_tmp.v = dv;
	adv_tmp.dist = dist;	
	myvert[sv-1].adj.push_back(adv_tmp);
	adv_tmp.v = sv;		
	myvert[dv-1].adj.push_back(adv_tmp);		
	}


	
	
i=0;
while(myvert[i].parent)
i++;	
dfs(myvert,i+1);

//printf_vec(order,"order");

for(i=1;i<order.size()-1;i++)
	{
	myvert[order[i]-1].parent = order[i+1];	
	j=0;
	while(myvert[order[i]-1].adj[j].v != myvert[order[i]-1].parent)
		j++;
	myvert[order[i]-1].dist_from_par = myvert[order[i]-1].adj[j].dist;		
	}

/*
for(i=0;i<num_verts;i++)
	{
	printf("myvert%d .parent==%d\n",i+1,myvert[i].parent);
	printf("myvert%d .dist_from_par==%d\n",i+1,myvert[i].dist_from_par);
	for(j=0;j<myvert[i].adj.size();j++)
		cout<<myvert[i].adj[j].v<<" ";
	cout<<endl<<endl;
	}	
	*/
	
vector<int> first;
for(i=0;i<num_verts;i++)
	{
	j=0;
	while(order[j++]!=i+1);
	first.push_back(j);
	}
vector<int> v_lowest(num_verts);
vector<int> v_temp;

for(i=0;i<order.size();i++)
	{
		
	v_temp.push_back(order[i]);
		if(!v_lowest[order[i]-1])
			v_lowest[order[i]-1] = v_temp.size();
		
	for(j=0; j<v_temp.size()-1; j++)	
		if(v_temp[j]==order[i])
			{
			//cout<<"v_temp[j]==order[i]\n";	
					
			j=v_temp.size()-j-1;
			while(j--)
				{
					v_temp.pop_back();					
					//printf_vec(v_temp,"poped");
					//cout<<"- removed last"<<endl;
				}
			break;
			}		
	}
//printf_vec(v_lowest,"heights");
//printf_vec(order,"order again");
vector<int> order_h(order.size());
for(i=0;i<order.size();i++)
	order_h[i] = v_lowest[order[i]-1];		
	
//printf_vec(order_h,"order with heights");
int *t = new int[4*order_h.size()];
build(t,order_h, 1, 0,  order.size()-1);
int path_n=0;
scanf("%d",&path_n);
if(!path_n)
	{
	cout<<"path are not defined\n";
	exit(-1);
	}
for(i=0;i<path_n;i++)
	{
	scanf("%d %ds",&v1,&v2);
	if(v1<1 || v1>num_verts || v2<1 || v2>num_verts)
		{
		cout<<"incorrect verticles\n";
		continue;
		}
	lca_val = lca(t, order_h, order, first, v1, v2);
	path = calc_path(v1,v2, myvert, lca_val);	
	cout<<path<<endl;
	}
}


