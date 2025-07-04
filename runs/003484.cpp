
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

struct edge{
	int i;
	int j;
	int length;
};
template<class F,class S,class T> class trio{
public:
	F first;
	S second;
	T third;
	trio(F f,S s,T t){
		first=f;
		second=s;
		third=t;
	}
	trio(){
	}

};

bool comp(trio<int,int,int> c, trio<int,int,int> t){
		if(c.first<t.first){
			return true;
		}else if (c.first>t.first){
			return false;
		}else if(c.second<t.second){
			return true;
		}else if(c.second>t.second){
			return false;
		}else if(c.third<t.third){
			return true;
		}else{
			return false;
		}
	}
int length,M,ansLength;
vector<trio<int,int,int> > requests;
vector<pair<int,int> > uniqueRequests;
int* ans;

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
//----- ЮЙФБЕН ТЕВТБ -----
	for(i=0;i<length-1;i++){
			cin>> t.i >> t.j >>t.length;
			edges[i]=t;
	}
//----- ЮЙФБЕН ЪБРТПУЩ ---
	cin>>ansLength;
	M=ansLength;
	requests.resize(M);
	map<int, int* > requestNumbers;
	static int zero=0;
	int l,r;
	int done=0;
	k=0;
	for(i=0;i<M;i++){
		cin>>l>>r;
		if(l!=r){
			requests[k].third=i;
			if(l<r){
				requests[k].first=l;
				requests[k].second=r;
			}else{
				requests[k].first=r;
				requests[k].second=l;
			}
			k++;
		}else{
			requestNumbers.insert(pair<int,int*>(i,&zero));
			done++;
}

	}
	M-=done;
	requests.resize(M);
	sort(requests.begin(),requests.end(),comp);
	uniqueRequests.reserve(2*M);
	vector<int> uniqueAnswers;
	uniqueAnswers.resize(M);
	l=0;
	r=0;
	k=-1;
	
	for(i=0;i<M;i++){
		if(l!=requests[i].first||r!=requests[i].second){
			k++;
			l=requests[i].first;
			r=requests[i].second;
			uniqueRequests.push_back(pair<int,int>(k,l));
			uniqueRequests.push_back(pair<int,int>(k,r));
		}
		requestNumbers.insert(pair<int,int*>(requests[i].third,&uniqueAnswers[k]));
	}
	M=k+1;
	//requestNumbers.resize(M);
	uniqueAnswers.resize(M);
	M*=2;
//----- РТПЮЙФБМЙ -------
	vector<trio<int,int,int> > vertexes;
	vertexes.push_back(trio<int,int,int>(1,0,0));//номер узла, номер родителя
	edge* edgePtr;
	int edgesSize=length-1;
	int number;
	for(i=0;i<length;i++){
		number=vertexes[i].first;
		edgePtr=edges;
		while(edgePtr<edges+edgesSize){//ищем родителя
			if(number!=edgePtr->i&&number!=edgePtr->j)
				edgePtr++;
			else{
				if(number==edgePtr->i){
					vertexes.push_back(trio<int,int,int>(edgePtr->j,number,edgePtr->length));					
				}
				if(number==edgePtr->j){
					vertexes.push_back(trio<int,int,int>(edgePtr->i,number,edgePtr->length));
				}
				*edgePtr=edges[--edgesSize];
			}
		}
	}
	int anc;
	int len;
	vector<pair<int,int> >::iterator unique;
	set<int>::iterator q;
	set<int>::iterator qEnd;
	set<int>* setTable=new set<int>[length];
	pair<set<int>::iterator,bool> ret;
	for(i=length-1;i>=0;i--){
		number=vertexes[i].first;// [1..length]
		anc=vertexes[i].second;
		len=vertexes[i].third;
		unique=uniqueRequests.begin();
		set<int>& vSet=setTable[number-1];
		while(unique!=uniqueRequests.end()){// есть ли эта вершина в каком-либо запросе?
			if(unique->second==number){
				ret=vSet.insert(unique->first);
				if(ret.second==false)//already exist
					vSet.erase(ret.first);
				if(*unique!=uniqueRequests.back()){
					*unique=uniqueRequests.back();
					uniqueRequests.pop_back();
				}else{
					uniqueRequests.pop_back();
					break;
				}
			}else
				unique++;
		}
		set<int>& ancSet=setTable[anc-1];
		q=vSet.begin();
		qEnd=vSet.end();
		while(q!=qEnd){
			uniqueAnswers[*q]+=len;
			ret=ancSet.insert(*q++);
			if(ret.second==false)//already exist
				ancSet.erase(ret.first);
		}
	}
	for(i=0;i<ansLength;i++){
		cout<<*requestNumbers[i]<<"\n";
	}
	delete[](setTable);
	delete[](ans);
	delete[](edges);
	return 0;
}

