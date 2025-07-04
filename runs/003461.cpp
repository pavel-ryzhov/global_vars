
#include <vector>
#include <iostream>

using namespace std;

int length,M,undone;
int* Q;
int* anc;
int* ans;
int* undones;
struct vertex{
	int length;
	int ancestor;
	int number;
	int descendantsCount;
	vertex** descendants;
};
struct edge{
	int i;
	int j;
	int length;
};
void explore(vertex* it){
  	int num;
static int k;
	num=it->number;
	for(int i=0;i<it->descendantsCount;i++){
		explore(it->descendants[i]);
	}

	for(int i=0;i<undone;i++){
		k=2*undones[i];
		if(num==Q[k]){		 
			anc[k]=num;
		}
		if(num==Q[k+1]){
			anc[k+1]=num;
		}
		if(anc[k]==num){
		  if(anc[k+1]==num){
		    undones[i--]=undones[undone-- -1];
		  }else{
		    anc[k]=it->ancestor;
		    ans[k/2]+=it->length;
		  }
		}else{ 
		  if(anc[k+1]==num){
		    anc[k+1]=it->ancestor;
		    ans[k/2]+=it->length;
		  }
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
p->ancestor=-1;
	int maxNesting=0;
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
		int* descendants_count=new int[length]();
		descendants_count[0]=0;
		for(i=1;i<length;i++){
			descendants_count[i]=-1;
		}
		for(i=0;i<length-1;i++){
			descendants_count[edges[i].i-1]++;
			descendants_count[edges[i].j-1]++;
		}

		p->descendantsCount=descendants_count[0];

		vertex** curDes;
		while(edgesSize!=0){
			i=p->number;
			p->descendants=new vertex*[p->descendantsCount]();
			curDes=p->descendants;
			it=edges;
			while(it<edges+edgesSize){
				if(i==it->i){	
					graph[descIndex].descendantsCount=descendants_count[it->j-1];										
					graph[descIndex].number=it->j;
					graph[descIndex].length=it->length;
						graph[descIndex].ancestor=i;
					*curDes++=&graph[descIndex];
					*it=*(edges+edgesSize-1);
					edgesSize--;
					descIndex++;
				}else{
					if(i==it->j){
						graph[descIndex].number=it->i;
						graph[descIndex].length=it->length;
						graph[descIndex].ancestor=i;
						graph[descIndex].descendantsCount=descendants_count[it->i-1];
						*curDes++=&graph[descIndex];						
						*it=*(edges+edgesSize-1);
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
	Q=new int[2*M];
	anc=new int[2*M];
	ans=new int[M];
	undones=new int[M];
	undone=M;
	for(i=0;i<M;i++){
		cin>>Q[2*i]>>Q[2*i+1];
		anc[2*i]=0;
		anc[2*i+1]=0;
		ans[i]=0;
		undones[i]=i;
	}
	explore(graph);
	for(i=0;i<M;i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}

