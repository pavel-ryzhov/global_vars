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
		if(it->number==Left[i]){// ��� ����� �� ����� i-�� ������
			if(right_anc[i]==it->number){//���� ����� �� ������ i-�� ������
				right_anc[i]=0;
			}else{// ��� ������ �� ������ i-�� ������
				left_anc[i]=ancestor;
				ans[i]+=it->length;
			}
		}else if(it->number==Right[i]){// ��� ����� �� ������ i-�� ������
			if(left_anc[i]==it->number){//���� ����� �� ����� i-�� ������
				left_anc[i]=0;
			}else{// ��� ������ �� ����� i-�� ������
				right_anc[i]=ancestor;
				ans[i]+=it->length;
			}
		}else
		if(left_anc[i]==it->number){//���� ����� �� ����� i-�� ������
			if(right_anc[i]==it->number){// � ���� ����� �� ������ i-�� ������
				left_anc[i]=0;
				right_anc[i]=0;
			}else{//���� ����� �� ����� i-�� ������, �� ��� ������ �� ������
				ans[i]+=it->length;
				left_anc[i]=ancestor;
			}
		}else
			if(right_anc[i]==it->number){//���� ����� �� ������ i-�� ������, �� ��� ������ �� �����
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
			///������  �����  �����
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

