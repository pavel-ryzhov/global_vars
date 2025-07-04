
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
	int descendantsCount;
	vertex** descendants;
	set<int> Q;
	vertex(){
		descendants=0;
	}
	~vertex(){
		for(int i=0;i<descendantsCount;i++){
			descendants[i]=0;
		}
		delete[](descendants);
	}
};
struct edge{
	int i;
	int j;
	int length;
};

void explore(vertex* it){
  	 int num;
	static int k,i,i2,len;
	num=it->number;
	set<int>::iterator q;
	set<int>::iterator qEnd;
	pair<set<int>::iterator,bool> ret;
	vertex* victim;

	for(int i=0;i<it->descendantsCount;i++){
		victim=it->descendants[i];
		explore(victim);
		q=victim->Q.begin();
		qEnd=victim->Q.end();
		while(q!=qEnd){
			ans[*q]+=victim->length;
			ret=it->Q.insert(*q++);
			if(ret.second==false)//already exist
				it->Q.erase(ret.first);
		}
	}
	/*
	for(int i=0;i<M;i++){
		i2=2*i;
		if(num==anc[i2]){
			anc[i2]=num;
		}
		if(num==anc[i2+1]){
			anc[i2+1]=num;
		}
		if(anc[i2]==num&&anc[i2+1]==num){
			anc[i2]=anc[i2+1]=0;		
		}else if(anc[i2]==num){
		    anc[i2]=it->ancestor;
		    ans[i]+=it->length;
		}else if(anc[i2+1]==num){
		    anc[i2+1]=it->ancestor;
		    ans[i]+=it->length;
		  }
	}*/
}

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
//----- узнаем, сколько потомков у узла ----
	int* descendants_count=new int[length]();
	descendants_count[0]=0;
	for(i=1;i<length;i++){
			descendants_count[i]=-1;
	}
	for(i=0;i<length-1;i++){
			descendants_count[edges[i].i-1]++;
			descendants_count[edges[i].j-1]++;
	}
//----- узнали -----
	vertex* graph=new vertex[length];
	vertex* p=graph;
	p->number=1;
	p->length=0;
	p->ancestor=-1;
	p->descendantsCount=descendants_count[0];

	int descIndex=1;
	int edgesSize=length-1;
	edge* it;
	vertex** currentDescendant;
	while(edgesSize!=0){
		i=p->number;
		p->descendants=new vertex*[p->descendantsCount]();
		currentDescendant=p->descendants;
		it=edges;
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
				graph[descIndex].descendantsCount=descendants_count[it->j-1];
				graph[descIndex].number=it->j;
				graph[descIndex].length=it->length;
				graph[descIndex].ancestor=i;
				*currentDescendant++=&graph[descIndex];
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
						graph[descIndex].descendantsCount=descendants_count[it->i-1];
						*currentDescendant++=&graph[descIndex];						
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

	explore(graph);
	for(i=0;i<ansLength;i++){
		cout<<ans[i]<<"\n";
		ans[i]=0;
	}
	delete[](graph);
	delete[](descendants_count);
	delete[](ans);
	delete[](Q);
	delete[](edges);
	return 0;
}

