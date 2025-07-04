
#include <list>
#include <vector>
#include <iostream>

using namespace std;

int length,M,undone;
/*int* Q;
int* anc;
int* ans;
int* undones;*/

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
};class QA{
public:
	int left;
	int right;
	int la;
	int ra;
	int ans;
	int number;
inline bool operator<(QA& p){
	return number<p.number;
}
int compare(int& num){
	if(num==left){		 
		la=num;
	}
	if(num==right){
		ra=num;
	}
	if(la==num){
		if(ra==num){

			return 2;
		    	//undones[i--]=undones[--undone];			
		}else{
			return 1;
		}
	}else{ 
		  if(ra==num){
			return -1;
		  }
	}
return 0;
}
};

QA* undones;
list<QA> done;

void explore(vertex* it){
  	static int num;
	static int k,i,i2;
vertex** p;
	//for(vector<vertex*>::iterator p=it->descendants.begin();p!=it->descendants.end();p++){
	for(p=it->descendants;p<it->descendants+it->descendantsCount;p++){
		explore(*p);
	}
	num=it->number;
	/*for(int i=0;i<it->descendantsCount;i++){
		explore(it->descendants[i]);
	}*/
	//for(int i=0;i<M;i++){
	for(i=0;i<undone;i++){
		k=undones[i].compare(num);
		if(k!=0)
			if(k==1){
			 undones[i].la=it->ancestor;
		    	 undones[i].ans+=it->length;
		}else 
			if(k==-1){
		    		undones[i].ra=it->ancestor;
		    		undones[i].ans+=it->length;
		}else{
			done.push_back(undones[i]);
			undones[i--]=undones[--undone];
}

	//	i=undones[k];
		//i2=i*2;
	/*	if(num==undones[i].left){		 
			undones[i].la=num;
			//anc[i2]=num;
		}
		if(num==undones[i].right){
			undones[i].ra=num;
			//anc[i2+1]=num;
		}
		if(undones[i].la==num){
		  if(undones[i].ra==num){
			//anc[i2]=anc[i2+1]=0;
			//cout<<"hello\n";
			done.push_back(undones[i]);
		    	undones[i--]=undones[--undone];			
		  }else{
		    undones[i].la=it->ancestor;
		    undones[i].ans+=it->length;
		  }
		}else{ 
		  if(undones[i].ra==num){
		    undones[i].ra=it->ancestor;
		    undones[i].ans+=it->length;
		  }
		}*/
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
					//p->descendants.push_back(&graph[descIndex]);
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
						//p->descendants.push_back(&graph[descIndex]);
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
	//Q=new int[2*M];
	//anc=new int[2*M];
	//ans=new int[M];
	undones=new QA[M];
	//undones=new int[M];
	undone=M;
	QA tmp;
	tmp.la=tmp.ra=tmp.ans=0;
	//QA* backup=new QA[M];
	for(i=0;i<M;i++){
		undones[i]=tmp;
		cin>>undones[i].left>>undones[i].right;//Q[2*i]>>Q[2*i+1];
		//anc[2*i]=anc[2*i+1]=0;
		//undones[i].la=undones[i].ra
	//}
	//for(i=0;i<M;i++){
		//ans[i]=0;
		undones[i].number=i;
		//backup[i]=undones[i];
	}


/*for(int k=0;k<50;k++){
	done.clear();
	for(i=0;i<M;i++){
		undones[i]=backup[i];
		//anc[2*i]=anc[2*i+1]=0;
		//undones[i].number=i;
	}
	undone=M;*/
	explore(graph);
	done.sort();
	for(list<QA>::iterator it=done.begin();it!=done.end();it++)
		cout<<it->ans<<"\n";
	/*for(i=0;i<M;i++){
		cout<<ans[i]<<"\n";
	}*/
//}
	return 0;
}

