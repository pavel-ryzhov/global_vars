
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <stack>
#include <algorithm>
using namespace std;

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

int length,M,ansLength;

int main(int argc, char* argv[])
{	
	/*fstream in;
	in.open("debug.txt",fstream::in);*/
	cin>>length;
	int i=0;
	int k=0;
	int l,r;
	vector<stack<pair<int,int> > > edges;
	edges.resize(length);
//----- ё…‘Ѕ≈Ќ “≈¬“Ѕ -----
	int len;
	for(i=0;i<length-1;i++){
			cin>> l >> r >>len;
			l--;
			r--;
			edges[l].push(pair<int,int>(r,len));
			edges[r].push(pair<int,int>(l,len));
	}
//----- ё…‘Ѕ≈Ќ ЏЅ–“ѕ”ў ---
	cin>>ansLength;
	M=ansLength;
	vector<pair<int,int> > uniqueRequests;
	vector<int> uniqueAnswers;
	static int zero=0;
	int done=0;
	k=0;	
	uniqueAnswers.resize(M);
	for(i=0;i<M;i++){
		cin>>l>>r;
		if(l!=r){
			l--;
			r--;
			uniqueRequests.push_back(pair<int,int>(i,l));
			uniqueRequests.push_back(pair<int,int>(i,r));
			k++;
		}
	}

	
//----- –“ѕё…‘Ѕћ… -------
	vector<trio<int,int,int> > vertexes;
	vertexes.push_back(trio<int,int,int>(0,-1,0));//номер узла, номер родител€, длина
	int number;
	int anc;
	pair<int,int> descendant;

	for(i=0;i<length;i++){
		number=vertexes[i].first;
		anc=vertexes[i].second;
		stack<pair<int,int> >&descendants=edges[number];
		while(!descendants.empty()){
			descendant=descendants.top();
			if(descendant.first!=anc)
				vertexes.push_back(trio<int,int,int>(descendant.first,number,descendant.second));
			descendants.pop();
		}
	}
	vector<pair<int,int> >::iterator unique;
	set<int>::iterator q;
	set<int>::iterator qEnd;
	set<int>* setTable=new set<int>[length];
	pair<set<int>::iterator,bool> ret;
	for(i=length-1;i>=0;i--){
		number=vertexes[i].first;// [0..length-1]
		anc=vertexes[i].second;
		len=vertexes[i].third;
		unique=uniqueRequests.begin();
		set<int>& vSet=setTable[number];
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
		q=vSet.begin();
		qEnd=vSet.end();
		if(q!=qEnd){
			set<int>& ancSet=setTable[anc];
			while(q!=qEnd){
				uniqueAnswers[*q]+=len;
				ret=ancSet.insert(*q++);
				if(ret.second==false)//already exist
					ancSet.erase(ret.first);
			}
		}
	}
	for(i=0;i<ansLength;i++){
		cout<<uniqueAnswers[i]<<"\n";
	}
	delete[](setTable);
	return 0;
}

