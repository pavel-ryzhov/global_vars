#include <iostream>
struct edge
{
    unsigned v1;
    unsigned v2;
    unsigned length;
    edge *next;
    edge *prev;
};
edge *head=NULL;

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
void DFS(unsigned V, unsigned anc, unsigned L, vertex *VT)
{
  edge *graph;
  graph = head;
  visited[V]=true;
  while (graph)
  {
    if ((graph->v1==V)&&(visited[graph->v2]==false))
    {
      DP++;
      VT[graph->v2].pred=V;
      VT[graph->v2].lng=graph->length;
      VT[graph->v2].depth=DP;
      if ((graph->next != NULL)&&(graph->prev != NULL))
      {
	graph->prev->next = graph->next;
	graph->next->prev = graph->prev;
      }
      
      DFS(graph->v2,V,graph->length,VT);
    }
    else if ((graph->v2==V)&&(visited[graph->v1]==false))
    {
      DP++;
      VT[graph->v1].pred=V;
      VT[graph->v1].lng=graph->length;
      VT[graph->v1].depth=DP;
      
      if ((graph->next != NULL)&&(graph->prev != NULL))
      {
	graph->prev->next = graph->next;
	graph->next->prev = graph->prev;
      }      
      DFS(graph->v1,V,graph->length,VT);
    }
    else
    {
      graph=graph->next;
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
  edge *curr;
   
  std::cin >> N;
  edge *tree=new edge[N-1];
  vertex *vert=new vertex[N+1];
  vert[1].pred=1;
  vert[1].lng=0;
  vert[1].depth=0;
  DP=0; 
  for (i=0; i<40000; i++)
    visited[i]=false;  
  
  head = new edge;
  head->next = NULL;
  head->prev = NULL;
//  std::cin >> head->v1 >> head->v2 >> head->length;
  
  curr=head;
  for (i=0; i<N-1; i++)
  {
    edge *tmp = new edge;
    tmp->next = NULL;
    tmp->prev = curr;
    std::cin >> tmp->v1 >> tmp->v2 >> tmp->length;
    curr->next=tmp;
    curr = curr->next;
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
  
  DFS(1,0,0,vert);
  
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
  delete[]curr;
  return 0;
}
