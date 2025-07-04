
#include <list>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

int length,M,ansLength;
pair<int,int>* Q;
int* ans;

struct vertex{
	int length;
	int ancestor;
	int number;
	set<int> Q;
};
struct edge{
	int i;
	int j;
	int length;
};

int main(int argc, char* argv[])
{	
	cin>>length;
	int i=0;
	int k=0;
	edge* edges;
	edge t;
	if(length>1){
		edges=new edge[length-1];
	}else{ 
		edges=0;
	}
//----- читаем ребра -----
	for(i=0;i<length-1;i++){
			cin>> t.i >> t.j >>t.length;
			edges[i]=t;
	}
//----- читаем запросы ---
	cin>>ansLength;
	M=ansLength;
	Q=new pair<int,int>[2*M];
	ans=new int[M];
	int l,r;
	int done=0;
	k=0;
	for(i=0;i<M;i++){
		cin>>l>>r;
		ans[i]=0;
		if(l!=r){
		Q[2*k].first=l;
		Q[2*k].second=i;
		Q[2*k+1].first=r;
		Q[2*k+1].second=i;
		k++;
		}else
			done++;

	}
	M-=done;
	M*=2;
//----- прочитали -------
	vertex* graph=new vertex[length];
	vertex* p=graph;
	p->number=1;
	p->length=0;

	int descIndex=1;
	int edgesSize=length-1;
	edge* it;
	vertex** currentDescendant;
	set<int>** setLookupTable=new set<int>*[length];
	while(edgesSize!=0){
		i=p->number;
		it=edges;
		setLookupTable[i-1]=&p->Q;
		while(it<edges+edgesSize){
			k=0;
			if(i==it->i){	
				while(k<M){
					if(Q[k].first==it->j){
						graph[descIndex].Q.insert(Q[k].second);
						Q[k]=Q[--M];
					}else
						k++;
				}
				graph[descIndex].number=it->j;
				graph[descIndex].length=it->length;
				graph[descIndex].ancestor=i;
				*it=*(edges+edgesSize-1);
				edgesSize--;
				descIndex++;
			}else{
				if(i==it->j){
						while(k<M){
							if(Q[k].first==it->i){
								graph[descIndex].Q.insert(Q[k].second);
								Q[k]=Q[--M];
							}else
								k++;
						}
						graph[descIndex].number=it->i;
						graph[descIndex].length=it->length;
						graph[descIndex].ancestor=i;						
						*it=*(edges+edgesSize-1);
						edgesSize--;
						descIndex++;
				}else
					it++;
			}
		}			
		p++;
	}
	for(k=0;k<M;k++)
		graph[0].Q.insert(Q[k].second);

	int anc=0;
	set<int>* ancSet;
	for(i=length-1;i>0;i--){
		vertex& victim=graph[i];
		if(anc!=victim.ancestor){
			anc=victim.ancestor;
			ancSet=setLookupTable[victim.ancestor-1];
		}

		set<int>::iterator q;
		set<int>::iterator qEnd;
		pair<set<int>::iterator,bool> ret;
		q=victim.Q.begin();
		qEnd=victim.Q.end();
		while(q!=qEnd){
			ans[*q]+=victim.length;
			ret=ancSet->insert(*q++);
			if(ret.second==false)//already exist
				ancSet->erase(ret.first);
		}
	}

	for(i=0;i<ansLength;i++){
		cout<<ans[i]<<"\n";
	}
	delete[](graph);
	delete[](setLookupTable);
	delete[](ans);
	delete[](Q);
	delete[](edges);
	return 0;
}

