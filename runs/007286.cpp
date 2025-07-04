#include <iostream>
class edge
{
  public:
    unsigned v1;
    unsigned v2;
    unsigned length;
};

class vertex
{
  public:
    unsigned pred;
    unsigned lng;
    unsigned depth;
};

bool visited[40000];
unsigned N, DP;

//Depth_First_Search
void DFS(unsigned V, unsigned anc, unsigned L, edge *graph, vertex *VT)
{
  visited[V]=true;
  for (unsigned i=0; i<N; i++)
  {
    if ((graph[i].v1==V)&&(visited[graph[i].v2]==false))
    {
      DP++;
      VT[graph[i].v2].pred=V;
      VT[graph[i].v2].lng=graph[i].length;
      VT[graph[i].v2].depth=DP;
      DFS(graph[i].v2,V,graph[i].length,graph,VT);
    }
    else if ((graph[i].v2==V)&&(visited[graph[i].v1]==false))
    {
      DP++;
      VT[graph[i].v1].pred=V;
      VT[graph[i].v1].lng=graph[i].length;
      VT[graph[i].v1].depth=DP;
      DFS(graph[i].v1,V,graph[i].length,graph,VT);
    }
  }
  DP--;
}

int main() 
{
  unsigned i, j, M, vert1, vert2;
  unsigned **paar;
  long *path;
  bool poisk;
  int fl;
  
  std::cin >> N;
  edge *tree=new edge[N-1];
  vertex *vert=new vertex[N+1];
  vert[1].pred=1;
  vert[1].lng=0;
  vert[1].depth=0;
  DP=0; 
  for (i=0; i<40000; i++)
    visited[i]=false;  
  
  for (i=0; i<N-1; i++)
  {
    std::cin >> tree[i].v1 >> tree[i].v2 >> tree[i].length;    
  }
  std::cin >> M;
  paar=new unsigned*[2];
  for (i=0; i<2; i++)
    paar[i]= new unsigned[M];
  path=new long[M];
  for (i=0; i<M; i++)
  {
    std::cin >> paar[0][i] >> paar[1][i];    
  }
  
  DFS(1,0,0,tree,vert);
  
  for (i=0; i<M; i++)
  {
    poisk=true;
    vert1=paar[0][i];
    vert2=paar[1][i];
    path[i]=0;
    if (vert1!=vert2)
    {
      while (poisk)
      {
	if (vert[vert1].depth > vert[vert2].depth)
	{
	  path[i]+=vert[vert1].lng;
	  vert1=vert[vert1].pred;
	}
	else if (vert[vert1].depth < vert[vert2].depth)
	{
	  path[i]+=vert[vert2].lng;
	  vert2=vert[vert2].pred;
	}
	else if (vert[vert1].depth == vert[vert2].depth)
	{
	  path[i]=path[i]+vert[vert1].lng+vert[vert2].lng;
	  vert1=vert[vert1].pred;
	  vert2=vert[vert2].pred;
	}
	if (vert1==vert2)
	{
	  poisk=false;
	}
      }
    }
  }
  for (i=0; i<M; i++)
    std::cout << path[i] <<'\n';  
  
  for (i=0; i<2; i++)
  {
    delete[]paar[i];    
  }
  delete[]paar;
  delete[]path;
  delete[]vert;
  delete[]tree;
  return 0;
}
