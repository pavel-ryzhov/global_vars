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

int length,M;

int main(int argc, char* argv[])
{	
	cin>>length;
	int i=0;
	int l,r;
	vector<stack<pair<int,int> > > edges;
	edges.resize(length);
//----- читаем ребра -----
	int len;
	for(i=0;i<length-1;i++){
			cin>> l >> r >>len;
			l--;
			r--;
			edges[l].push(pair<int,int>(r,len));
			edges[r].push(pair<int,int>(l,len));
	}
//----- читаем запросы ---
	cin>>M;
	vector<set<int> > requests;
	vector<int> answers;	
	requests.resize(length);
	answers.resize(M);
	for(i=0;i<M;i++){
		cin>>l>>r;
		if(l!=r){// не наддо ничего считать если начало и конец совпадают
			l--;
			r--;
			requests[l].insert(i);
			requests[r].insert(i);
		}
	}
//----- прочитали -------
	vector<trio<int,int,int> > vertexes;
	vertexes.push_back(trio<int,int,int>(0,-1,0));//номер, родитель, длина
	int number;
	int anc;
	pair<int,int> descendant;

	for(i=0;i<length;i++){//сверху-вниз, упорядочиваем ребра
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
	set<int>::iterator q;
	set<int>::iterator qEnd;
	pair<set<int>::iterator,bool> ret;

	for(i=length-1;i>=0;i--){// снизу-вверх, считаем
		number=vertexes[i].first;
		anc=vertexes[i].second;
		len=vertexes[i].third;
		set<int >& rSet=requests[number];
		q=rSet.begin();
		qEnd=rSet.end();
		if(q!=qEnd){
			set<int>& ancSet=requests[anc];
			while(q!=qEnd){
				answers[*q]+=len;
				ret=ancSet.insert(*q++);
				if(ret.second==false)//уже есть
					ancSet.erase(ret.first);//значит нашли
			}
		}
	}
	for(i=0;i<M;i++){
		cout<<answers[i]<<"\n";
	}
	return 0;
}

