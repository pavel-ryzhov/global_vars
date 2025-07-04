#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
using namespace std;
            
struct Deux {
  long small;
  long big;
  bool operator < (const Deux& two) const{
    if ((*this).big<two.big)
      return true;
    if ((*this).big>two.big)
      return false;
    return (*this).small<two.small;    
  }
};

list <long> pathy; //pathy for full path
list <long> full;//full for current path
set <Deux> ways;
struct Node{
  
      long name;      
      long guest;
      map <long,Node*> nodes;
   void FindPath(long int Root){
    if (name==Root) {guest=Root;}
    guest=Root;
    map<long,Node*>::iterator it;
    it=nodes.begin();
    //cout<<"node is "<<name<<endl;
    //cout<<name;
    pathy.push_back(name);
    if (nodes.size()==1 && Root!=name){return;}
    while (it!=nodes.end()){
      if(it->first==guest){	
	}
             
      else{	
	//cout<<"i'm here!  "<<endl;
	it->second->FindPath(name);
	pathy.push_back(name);
 	//cout<<name;
      }
      ++it;
    }
    //cout<<"node was "<<Root<<endl;
    
    
   }
  void Out () {
   cout<<"pathy is "<<endl;
   list <long>::iterator it;
   it=pathy.begin();   
   while (it!=pathy.end()){
     cout<<(*it);
     ++it;
   }
   
   
  }    
  
  bool operator < (const Node& two) const{
    if ((*this).name<two.name)
      return true;
    if ((*this).name>two.name)
      return false;
    return (*this).guest<two.guest;    
  }   
  
};
class Path{
      fstream readem;
      fstream wrtem;
	map < Deux,long > lengths;
	vector <long> fullpath;
	long NumberOfNodes;
	long NumberOfFind;
	long Root;//for first entrance
	map <long,Node*> ArrayOfNodes; 	
	void FillNodes(long one, long two, long three){
	  Node* tmp;	  
	  if (ArrayOfNodes.find(one)==ArrayOfNodes.end()){
	    tmp=new Node[1];
	    tmp->guest=-1;
	    tmp->name=one;
	    ArrayOfNodes.insert(pair <long,Node*>(one,tmp) );
	  }	  	  
	    
	  if (ArrayOfNodes.find(two)==ArrayOfNodes.end()){
	    tmp=new Node[1];
	    tmp->guest=-1;
	    tmp->name=two;
	    ArrayOfNodes.insert(pair <long,Node*>(two,tmp) );
	  }
	  ArrayOfNodes[one]->nodes.insert(pair <long,Node*> (two,ArrayOfNodes[two]));
	  ArrayOfNodes[two]->nodes.insert(pair <long,Node*> (one,ArrayOfNodes[one]));
	  if (one<two){
	    one=two+one;
	    two=one-two;
	    one=one-two;
	  }
	   Deux d;
	   d.big=one;
	   d.small=two;	   
	   
	   lengths.insert(pair<Deux,long>(d,three));	   
	}
	/*void MakePath(){
	  cout<<"root-node is ..."<<Root<<endl;
	  map <long, Node*>::iterator it;
	  it=ArrayOfNodes[Root]->nodes.begin();
	  while (it!=ArrayOfNodes[Root]->nodes.end()){
	    cout<<it->first<<endl;
	    ++it;
	  }	  	    
	}*/
	void MakePath(long int root){
	  ArrayOfNodes[root]->FindPath(root);
	}
	void MakeRoad(long begin, long end){
	  ways.clear();
	  full.clear();
	  list <long>::iterator ti;
	  bool fl=false; //is end>begin?
	  ti=pathy.begin();
	  while (ti!=pathy.end()){	    
	    if (*ti==begin){break;}
	    ++ti;
	  }
	  list <long>::iterator tii;
	  tii=pathy.begin();
	  while (tii!=pathy.end()){
	    if (tii==ti){fl=true;}
	    if (*tii==end){break;}	    
	    ++tii;
	    
	  }
	  if (!fl){
	    list <long>::iterator one;
	    one=ti;
	    ti=tii;
	    tii=one;	    
	  }
	  
	  
	   
	  ++tii;
	  //full.splice(full.begin(),pathy,ti,tii);
	  while(ti!=tii){
	    full.push_back(*ti);
	    ++ti;
	  }
	  //--must delete
	  /*
	  tii=full.begin();
	  
	  while (tii!=full.end()){
	     cout<<*tii;
	    ++tii;
	   }
	   //---delete
	   */
	  tii=full.begin();
	  ti=tii++;
	  Deux D;
	  long long sum=0;
	  long one;
	  long two;
	  while (tii!=full.end()){
	    	   one=*ti;
		   two=*tii;
	    if (one>two){
	      one=two+one;
	      two=one-two;
	      one=one-two;	      	      
	    }
	    D.small=one;
	    D.big=two;
	    if (ways.find(D)!=ways.end()){	     
	     sum-=lengths[D]; 
	    }
 	    else {
	  //    cout<<" way is  "<<D.small<<" -- "<<D.big<<endl; 
	  //    cout<<"lengthsss"<<lengths[D]<<endl;
	      ways.insert(D);
	      sum+=lengths[D];
	    }
	    ++ti;
	    ++tii;
	  }
	    
	    //cout<<"sum is "<<abs(sum)<<endl;
	    cout<<sum<<endl;
	    
	  	  
	}
      public:	
	Path(){}
          void Reader(){	    
		//readem.open(filename.c_str(),fstream::in|fstream::out);
		//wrtem.open (filename2.c_str(),fstream::out|fstream::trunc);     		  
    		//string take;    		  
		//getline(readem,take);
		//cout<<" take is "<<take<<endl;
		//cin>>NumberOfNodes;
    		//NumberOfNodes=atoi(take.c_str());
		cin>>NumberOfNodes;//readem
		//cout<<NumberOfNodes<<endl;				
		long one,two,three;
    		for (int i=1; i<NumberOfNodes;++i){		      		  
		    cin>>one>>two>>three;//readem		      		  
		    if (i==1){Root=one;}
		//    cout<<one<<" "<<two<<" "<<three<<endl;		    
		    FillNodes(one,two,three);		    
		}
		  //MakePath();
		  //Root=2;
		  MakePath(Root);
		  //cout<<endl;
		cin>>NumberOfFind;//readem
		//cout<<NumberOfFind<<endl;
		for (int i=0; i<NumberOfFind;++i){
		  cin>>one>>two; //readem
		//  cout<<one<<" "<<two<<endl;
		  MakeRoad(one,two);
		}
		  //MakeRoad(1,6);
		  //MakeRoad(1,3);
		  //MakeRoad(6,3);
		  //MakeRoad(2,5);
		  //ArrayOfNodes[Root]->Out();
		/*getline(readem,take);
		NumberOfFind=atoi(take.c_str());
		  cout<<NumberOfFind<<endl;
		 
		for (int i=1; i<NumberOfFind;++i){
		  readem>>one>>two;
		  cout<<one<<" "<<two<<endl;
		  
		}
		*/
		/*
    		  string key="";
    		  //make dictionary
    		  for (int i=0; i<NumberOfStrings;++i){
    		    getline(readem,take);
    		    small.Fill(take);		    
    		    small.key=getID(small.word);		    
    		    small.age=0;
    		    //cout<<"word:  "<<small.word<<" count: "<<small.count<<" key: "<<small.key<<endl;
    		    Dictionary[small.key].push_back(small);		    		    		   		    
    		  }
    		  //writer part		    
    		  //parsing function H()		      		  
    		  //using function send() to send data to writer-function
		  */
             }


      };
int main(){
// try{
//   if (argc!=3) throw "not enough arguments";
//    cout<<"input string"<<endl;    
//    string str;
//    str=argv[1];
//    string str2=argv[2];
    Path Pathy;
    Pathy.Reader();
 //}
 //catch (const char* p){cout<<p<<endl;}


    }



/*
 error: no match for ‘operator<’ in ‘it < ((Path*)this)->Path::ArrayOfNodes.
 std::map<_Key, _Tp, _Compare, _Alloc>::operator[] [with _Key = long int, _Tp = Node*,
 _Compare = std::less<long int>, _Alloc = std::allocator<std::pair<const long int, Node*> >]
 (((const long int&)((const long int*)(&((Path*)this)->Path::Root))))->Node::nodes.std::map<_Key, _Tp, _Compare, _Alloc>::end 
 [with _Key = long int, _Tp = Node*, _Compare = std::less<long int>, _Alloc = std::allocator<std::pair<const long int, Node*> >]()’

*/
