//#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;
struct vertex{
	int length;
	int number;
	vector<vertex*> descendants;
};

int* graph_holder;
int length,M;
int* Left;
int* Right;
const int MAXN=4;
int* left_anc;
int* right_anc;
//int* left_leg;
//int* right_leg;
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
	int* graph_holder=new int[3*(length-1)];
	for(i=0;i<length-1;i++){
		///   начало			конец				длина
		cin>>graph_holder[3*i]>>graph_holder[3*i+1]>>graph_holder[3*i+2];
	}
	vertex* p=graph;
	p->number=1;
	p->length=-500;
	int descIndex=1;
	while(p<graph+length){
		i=p->number;
		for(int k=0;k<length-1;k++){
			if(i==graph_holder[3*k]){
				p->descendants.push_back(&graph[descIndex]);
				graph[descIndex].number=graph_holder[3*k+1];
				graph[descIndex].length=graph_holder[3*k+2];
				descIndex++;
			}
		}
		p++;
	}
	delete[](graph_holder);
	cin>>M;
	Left=new int[M];
	Right=new int[M];
	//left_leg=new int[M];
	//right_leg=new int[M];
	left_anc=new int[M];
	right_anc=new int[M];
	ans=new int[M];
	for(i=0;i<M;i++){
		cin>>Left[i]>>Right[i];
//		left_leg[i]=0;
	//	right_leg[i]=0;
		left_anc[i]=0;
		right_anc[i]=0;
		ans[i]=0;
	}
		explore(graph,-1);
	for(i=0;i<M;i++){
			cout<<ans[i]<<endl;
	}
	return 0;
}

