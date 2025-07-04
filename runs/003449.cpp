//#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
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
	fstream in;
	in.open("test.txt",fstream::in);
	in>>length;
	int i=0;
	vertex* graph=new vertex[length];
	vector<edge> edges;
	edge t;
	edges.resize(length-1);
	for(i=0;i<length-1;i++){
		///начало  конец  длина
		in>> t.i >> t.j >>t.length;
		edges[i]=t;
	}
	vertex* p=graph;
	p->number=1;
	p->length=0;
	int descIndex=1;
	vector<edge>::iterator it;
	while(edges.size()!=0){
		i=p->number;
		it=edges.begin();
		while(it!=edges.end()){
			if(i==it->i){
				p->descendants.push_back(graph+descIndex);
				graph[descIndex].number=it->j;
				graph[descIndex].length=it->length;
				*it=*edges.rbegin();
				edges.pop_back();
				descIndex++;
			}else{
				if(i==it->j){
					p->descendants.push_back(graph+descIndex);
					graph[descIndex].number=it->i;
					graph[descIndex].length=it->length;
					*it=*edges.rbegin();
					edges.pop_back();
					descIndex++;
				}else
					it++;
			}
		}
		p++;
	}
	in>>M;
	Left=new int[M];
	Right=new int[M];
	left_anc=new int[M];
	right_anc=new int[M];
	ans=new int[M];
	for(i=0;i<M;i++){
		in>>Left[i]>>Right[i];
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

