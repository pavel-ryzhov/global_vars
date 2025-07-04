#include <iostream>
#include <algorithm>
#include <vector>
#define TOOMAX 50000
using namespace std;


typedef struct{
	unsigned v1;   // |ends 
	unsigned v2;   // |of the edge
	unsigned l;    // length
	unsigned up;   // direction
}edge_t;


typedef struct{
	unsigned up_v;             // upper vertex of the tree, TOOMAX for root
	unsigned up_l;             // length of edge to this upper vertex, 0 for root
	vector <edge_t*> edge;     // edges from this vertex 
	char visited;              // '*' if visited, ' ' if not     
}vertex_t;

void dfs(vector<vertex_t> &graph, unsigned i)   // i - number of vertex
{
	graph[i].visited='*';
	unsigned l=graph[i].up_l;
	int flag=0;
	switch(graph[i].edge.size())
	{
	case 1: return;
	case 2: flag=1;
	default:
		for(unsigned k=0;k<graph[i].edge.size();k++){
			// v - other end of the current edge:
			unsigned v=(graph[i].edge[k]->v1==i) ? graph[i].edge[k]->v2 : graph[i].edge[k]->v1;
			if (v!=TOOMAX){
				if (graph[v].visited==' '){
					// visit it:
					graph[i].edge[k]->up=i;
					graph[v].up_v=flag*(graph[i].up_v)+(1-flag)*i;  // parent = parent of i, if i has 1 child
																	//  or i, if i has more children
					graph[v].up_l=l*flag+graph[i].edge[k]->l;		// the same with length
					dfs(graph, v);
				}
			}
		}
	}

	return;
}

unsigned lca(vector<vertex_t> &graph, unsigned i, unsigned j)
{
	vector <vertex_t*> way_i, way_j;   // way upwards for i and j
	int length_i=0;
	int length_j=0;
	int k=i;
	do{
		way_i.push_back(&graph[k]);
		length_i+=graph[k].up_l;
		k=graph[k].up_v;
	} while (k!=TOOMAX);
	k=j;
	do{
		way_j.push_back(&graph[k]);
		length_j+=graph[k].up_l;
		k=graph[k].up_v;
	} while (k!=TOOMAX);
	i=way_i.size();
	j=way_j.size();
	unsigned size=min(i,j);
	i-=size;
	j-=size;
	for(k=size-1;k>=0;--k){
		if(way_i[k+i]!=way_j[k+j]) break;
		length_i-=2*(way_i[k+i]->up_l);
	}
	return length_i+length_j;
}

	

int main(void){
	vector <vertex_t> graph;
	edge_t *edges;

	unsigned N,M;   // see the task
	unsigned i,k;

	std::cin >> N;

	edges = new edge_t[N];
	graph.resize(N);

	for(i=0;i<N-1;++i){
		int _v1, _v2;
		std::cin >> _v1;
		std::cin >> _v2;
		std::cin >> edges[i].l;
		edges[i].v1=--_v1;
		edges[i].v2=--_v2;
		graph[_v1].edge.push_back(&edges[i]);
		graph[_v2].edge.push_back(&edges[i]);
	}

	//init:
	graph[0].up_v=TOOMAX;
	graph[0].up_l=0;
	edges[N-1].l=0;
	edges[N-1].up=TOOMAX;
	edges[N-1].v1=TOOMAX;
	edges[N-1].v2=0;
	graph[0].edge.push_back(&edges[N-1]);
	for(i=0;i<N;i++) {
		graph[i].visited=' ';
	}

	dfs(graph, 0);
	
	std::cin >> M;
	for(i=0;i<M;i++){
		unsigned v1,v2;
		std::cin >> v1;
		std::cin >> v2;
		std::cout << lca(graph,--v1,--v2) << std::endl;
	}

	delete[] edges;
	return 0;
}


