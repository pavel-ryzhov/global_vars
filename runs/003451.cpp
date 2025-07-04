//#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;
struct vertex{
	int length;
	int number;
	vector<vertex*> descendants;
};
struct edge{
	int i;
	int j;
	int length;
};

int length,M;
int* Left;
int* Right;
const int MAXN=4;
int* left_anc;
int* right_anc;
int* ans;
void explore(vertex* it,int ancestor){
	for(vector<vertex*>::iterator descendant=it->descendants.begin();
		descendant<it->descendants.end();descendant++){
			explore(*descendant,it->number);
	}
	for(int i=0;i<M;i++){
		if(it->number==Left[i]){// это ответ на левый i-ый запрос
			if(right_anc[i]==it->number){//есть ответ на правый i-ый запрос
				right_anc[i]=0;
			}else{// нет ответа на правый i-ый запрос
				left_anc[i]=ancestor;
				ans[i]+=it->length;
			}
		}else if(it->number==Right[i]){// это ответ на правый i-ый запрос
			if(left_anc[i]==it->number){//есть ответ на левый i-ый запрос
				left_anc[i]=0;
			}else{// нет ответа на левый i-ый запрос
				right_anc[i]=ancestor;
				ans[i]+=it->length;
			}
		}else
		if(left_anc[i]==it->number){//есть ответ на левый i-ый запрос
			if(right_anc[i]==it->number){// и есть ответ на правый i-ый запрос
				left_anc[i]=0;
				right_anc[i]=0;
			}else{//есть ответ на левый i-ый запрос, но нет ответа на правый
				ans[i]+=it->length;
				left_anc[i]=ancestor;
			}
		}else
			if(right_anc[i]==it->number){//есть ответ на правый i-ый запрос, но нет ответа на левый
				ans[i]+=it->length;
				right_anc[i]=ancestor;
			}
	}

}

int main(int argc, char* argv[])
{	
	cin>>length;
	int i=0;
	vertex* graph=new vertex[length];
	edge* edges;
	edge t;
	vertex* p=graph;
	p->number=1;
	p->length=0;

	if(length>1){
		edges=new edge[length-1];
		for(i=0;i<length-1;i++){
			///начало  конец  длина
			cin>> t.i >> t.j >>t.length;
			edges[i]=t;
		}
		int descIndex=1;
		int edgesSize=length-1;
		edge* it;

		while(edgesSize!=0){
			i=p->number;
			it=edges;
			while(it<=edges+edgesSize){
				if(i==it->i){
					p->descendants.push_back(graph+descIndex);
					graph[descIndex].number=it->j;
					graph[descIndex].length=it->length;
					*it=*(edges+edgesSize);
					edgesSize--;
					descIndex++;
				}else{
					if(i==it->j){
						p->descendants.push_back(graph+descIndex);
						graph[descIndex].number=it->i;
						graph[descIndex].length=it->length;
						*it=*(edges+edgesSize);
						edgesSize--;
						descIndex++;
					}else
						it++;
				}
			}
			p++;
		}
		delete[](edges);
	}
	cin>>M;
	Left=new int[M];
	Right=new int[M];
	left_anc=new int[M];
	right_anc=new int[M];
	ans=new int[M];
	for(i=0;i<M;i++){
		cin>>Left[i]>>Right[i];
		left_anc[i]=0;
		right_anc[i]=0;
		ans[i]=0;
	}
		explore(graph,-1);
	for(i=0;i<M;i++){
			cout<<ans[i]<<"\n";
	}
	return 0;
}

