#include <list>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int length,M,ansLength;
int* ans;
template<class F,class S,class T> class trio{
public:
	F first;
	S second;
	T third;
	trio(F& f,S& s, T& t){
		first=f;
		second=s;
		third=t;
	}
	trio(){
	}
};
struct vertex{
	int number;
	vector<pair<int,int> > path;
};
struct edge{
	int i;
	int j;
	int length;
};

trio<int,int,int>* Q;

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
	int l,r;
	for(i=0;i<length-1;i++){
			cin>> t.i>>t.j >>t.length;
			edges[i]=t;
	}
//----- читаем запросы ---
	cin>>ansLength;
	M=ansLength;
	Q=new trio<int,int,int>[M];
	ans=new int[M];
	int done=0;
	k=0;
	for(i=0;i<M;i++){
		cin>>l>>r;
		ans[i]=0;
		if(l!=r){
			Q[k].first=i;
			Q[k].second=l;
			Q[k].third=r;
			k++;
		}else
			done++;

	}
	M-=done;
	vertex* graph=new vertex[length];
	pair<int,int>* Qptr=new pair<int,int>[M];
	vertex* p=graph;
	p->number=1;
	int descIndex=1;
	int edgesSize=length-1;
	edge* it;
	while(edgesSize!=0){
		i=p->number;
		it=edges;
		while(it<edges+edgesSize){
			k=0;
			if(i==it->i){	
				while(k<M){
					if(Q[k].second==it->j){
							Qptr[k].first=descIndex;
					}else if(Q[k].third==it->j){
							Qptr[k].second=descIndex;
					}
					k++;
				}			
				graph[descIndex].path=p->path;
				graph[descIndex].path.push_back(pair<int,int>(it->j,it->length));
				graph[descIndex].number=it->j;
				*it=*(edges+edgesSize-1);
				edgesSize--;
				descIndex++;
			}
			else{
				if(i==it->j){
						while(k<M){
							if(Q[k].second==it->i){
								Qptr[k].first=descIndex;
							}else if(Q[k].third==it->i){
								Qptr[k].second=descIndex;
							}
							k++;
						}		
						graph[descIndex].number=it->i;
						graph[descIndex].path=p->path;
						graph[descIndex].path.push_back(pair<int,int>(it->i,it->length));			
						*it=*(edges+edgesSize-1);
						edgesSize--;
						descIndex++;
				}	
				else
					it++;
			}
		}			
		p++;
	}
	for(k=0;k<M;k++){
		if(Q[k].second==1)
			Qptr[k].first=0;
		else if(Q[k].third==1)
			Qptr[k].second=0;
	}
	for(i=0;i<M;i++){
		vertex& f=graph[Qptr[i].first];
		vertex& s=graph[Qptr[i].second];
		k=0;
		int way=0;
		vector<pair<int,int> >::iterator fIt=f.path.begin();
		vector<pair<int,int> >::iterator sIt=s.path.begin();
		while(fIt!=f.path.end()&& sIt!=s.path.end()){
			if(fIt->first!=sIt->first){
				break;
			}
			fIt++;
			sIt++;
		}
		while(fIt!=f.path.end()){
			way+=fIt->second;
			fIt++;
		}
		while(sIt!=s.path.end()){
			way+=sIt->second;
			sIt++;
		}
		ans[Q[i].first]=way;
	}


	for(i=0;i<ansLength;i++){
		cout<<ans[i]<<"\n";
		ans[i]=0;
	}
	delete[](graph);
	delete[](ans);
	delete[](Q);
	delete[](Qptr);
	delete[](edges);
	return 0;
}

