#define LINE 0xFFFF
#define MAX 0xFFFF

#define US unsigned short

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

US **G, *H, *first, *ancestors, *segmentsTree, n;
vector<US> order;
bool *used;

void swap(US *a, US *b)
{
    *a=*a^*b;
    *b=*a^*b;
    *a=*a^*b;
}

void dfsR(US v, US h, US ancestor)
{
    used[v] = true;
    H[v] = h;
    ancestors[v] = ancestor;
    order.push_back(v);
    
    for (US i = 1; i < v; ++i)
	if (!used[i] && G[v][i] != LINE)
	{
	    dfsR(i, h+1, v);
	    order.push_back(v);
	}
	
    for (US i = v + 1; i < n; ++i)
	if (!used[i] && G[i][v] != LINE)
	{
	    dfsR(i, h+1, v);
	    order.push_back(v);
	}
}

void dfs()
{
    used = new bool[n];
    memset(used, 0, n);
    dfsR(1, 0, 0);
    H[0] = MAX;
}

void fillFirst()
{
    US m = order.size();
    for (US i = 0; i < m; ++i)
    {
	US v = order[i];
	if (first[v] == LINE)
	    first[v] = i;
    }
}

US getDistance(US x, US y, US **G)
{
    if (x > y)
	return G[x][y];
    return G[y][x];
}

void buildSegmentsTreeR (US v, US tl, US tr) 
{
	if (tl == tr)
	    segmentsTree[v] = order[tl];
	else 
	{
	    US tm = (tl + tr) / 2;
	    
	    buildSegmentsTreeR (v*2, tl, tm);
	    buildSegmentsTreeR (v*2+1, tm + 1, tr);
	    
	    if ( H[segmentsTree[v*2]] < H[segmentsTree[v*2+1]] )
		segmentsTree[v] = segmentsTree[v*2];
	    else
		segmentsTree[v] = segmentsTree[v*2+1];
	}
}

void buildSegmentsTree()
{
    buildSegmentsTreeR( 1, 0, order.size() - 1 );
    segmentsTree[0] = 0;
}

US minR (US v, US tl, US tr, US l, US r) 
{
    if (l > r)
	return 0;
    
    if (l == tl && r == tr)
    {
	//cout<<segmentsTree[v]<<endl;
	return v;
    }
    
    US tm = (tl + tr) / 2, a, b;
    
    a = minR (v*2, tl, tm, l, min(r,tm) );
    b = minR (v*2+1, tm+1, tr, max(l, (US)(tm + 1) ), r );
    
    if ( H[segmentsTree[a]] < H[segmentsTree[b]] ) 
    {
	//cout<<segmentsTree[a]<<endl;
	return a; 
    }
    //cout<<segmentsTree[b]<<endl;
    return b;
}

inline US lca(US l, US r)
{
    return segmentsTree[minR(1, 0, order.size() - 1, l, r)];
}

int main()
{
    unsigned long long int distance = 0;
    US v, a, v1, v2, l, r; 

    scanf("%hu", &n);
    n++;
    
    H = new US[n];
    ancestors = new US[n];
    first = new US[n];
    
    memset(first, LINE, 2*n);
    //memset(ancestors, LINE, 2*n);
    
    G = new US*[n];
    for (US i = 1 ; i < n; ++i)
    {
	G[i] = new US[i];
	memset(G[i], LINE, 2*i);
    }
    
    US t1,t2,t3;
    for (US i = 2; i < n; ++i)
    {
	scanf("%hu %hu %hu", &t1, &t2, &t3);		
	if (t1 > t2)  
	    G[t1][t2] = t3;
	else
	    G[t2][t1] = t3;
    }
    
    dfs();
    fillFirst();
    
    segmentsTree = new US[ 4*order.size() ];
    memset(segmentsTree, LINE, 8*order.size() );
    
    buildSegmentsTree();
    
    /*for (int i=0;i<n;++i)
	    cout<<H[i]<<' ';
	cout<<endl;
	
    for (int i=0;i<order.size();++i)
	cout<<order[i]<<' ';
    cout<<endl;
    
    cout<<"----"<<endl;
    
    for (int i = 0; i < 4*order.size(); ++i)
	cout<<i<<' '<<segmentsTree[i]<<endl;
    
    cout<<"----"<<endl;*/
    
    US M;
    scanf("%hu",&M);
    
    for (US i = 0; i < M; ++i, distance = 0)
    {
	scanf("%hu %hu", &v1, &v2);
	
	if (v1 == v2)
	    cout<<0<<endl;
	else
	{
	    
	    if (first[v1]<first[v2])
	    {
		l = first[v1];
		r = first[v2];
	    }
	    else
	    {
		r = first[v1];
		l = first[v2];
	    }
	    
	    US v = lca(l, r);
	    //cout<<lca<<endl;
	    
	    for (; v1 != v; v1 = ancestors[v1])
		distance += getDistance(v1, ancestors[v1], G);
	    
	    for (;v2 != v; v2 = ancestors[v2])
		distance += getDistance(v2, ancestors[v2], G);
		
	    //cout<<"---"<<endl;
	    cout<<distance<<endl;
	}
    }
    
    for(US i = 0; i < n; i++)			//?
	delete []G[i];
    delete []G;

    return 0;
}