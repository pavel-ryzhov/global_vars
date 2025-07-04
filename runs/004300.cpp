#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
//#define DEBUG
using namespace std;
typedef unsigned int freq;
typedef unsigned int index;

//=============================================================
// Globals
//=============================================================
static int F;
//=============================================================
// Mapping character to phone buttons
//=============================================================
string getNumByChar(char ch)
{
    if(ch=='a' || ch=='b' || ch=='c') return "2";
    else if(ch=='d' || ch=='e' || ch=='f') return "3";
    else if(ch=='g' || ch=='h' || ch=='i') return "4";
    else if(ch=='j' || ch=='k' || ch=='l') return "5";
    else if(ch=='m' || ch=='n' || ch=='o') return "6";
    else if(ch=='q' || ch=='r' || ch=='s' || ch=='p') return "7";
    else if(ch=='t' || ch=='u' || ch=='v') return "8";
    else if(ch=='w' || ch=='x' || ch=='y' || ch=='z') return "9";
}
//--------------------------------------------------------------

//=============================================================
// Mapping word to sequence of phone buttons to push
//=============================================================
string getSignature(const string &str)
{
    string sig="";

    for(int i=0;i<str.size();++i){
        sig+=getNumByChar(str[i]);
    }

    return sig;
}
//--------------------------------------------------------------

//=============================================================
// comp for sorting list
//=============================================================
bool compare(pair<index,freq> a, pair<index,freq> b)
{
    return a.second>b.second;
}
//--------------------------------------------------------------

//=============================================================
// pred for find_if
//=============================================================
bool pred(pair<index,freq> a)
{
    return a.second<=F;
}
//--------------------------------------------------------------

//=============================================================
// Mapping word to sequence of phone buttons to push
//=============================================================
void fillDict(map<string, list< pair<index,freq> > > &mDict, vector<string> &vDict, int N)
{
    string str;
    list< pair<index,freq> > l;
    int f;
    for(int i=0;i<N;++i){
        cin>> str >> f;
        vDict[i]=str;
        mDict[getSignature(str)].push_back(make_pair(i,f));
     }

    //sorting all lists in mDict by frequency
    for(map<string, list< pair<index,freq> > >::iterator it=mDict.begin(); it!=mDict.end(); ++it)
        (*it).second.sort(compare);

 }
//--------------------------------------------------------------

//=============================================================
// substr("abcde",3)=="abc"
//=============================================================
string getSubStr(string &str,int size)
{
    string sub="";
    for(int i=0;i<size;++i){
        sub+=str[i];
    }
    return sub;
}
//--------------------------------------------------------------

//=============================================================
// getting signature lenth, number of "*" to choose
// a word, filling onesStarNum
// For example: 1**1*1*** ->  onesStarNum: 2,1,3
//=============================================================
void parseQuery(string str, int &sigLen, int &sigStarNum, vector<int> &onesStarNum)
{
    basic_string<char>::iterator sigEnd=find(str.begin(),str.end(),'1'),it;
    sigStarNum=static_cast<int>(count(str.begin(),sigEnd,'*'));

    onesStarNum.resize(0);
    for(it=sigEnd;it!=str.end();++it){
        if(*it=='1') onesStarNum.push_back(0);
        if(*it=='*') ++(onesStarNum.back());
    }

    sigLen=sigEnd-str.begin()-sigStarNum;
}
//--------------------------------------------------------------

//=============================================================
//
//=============================================================
void printResults(vector< string > &query,map<string, list< pair<index,freq> > > &mDict,vector<string> &vDict)
{
    int sigLen,sigStarNum;
    string sign;
    vector<int> punctStarNum;

    for(int i=0;i<query.size();++i){
        parseQuery(query[i],sigLen,sigStarNum,punctStarNum);
        sign=getSubStr(query[i],sigLen);

        //finding appropriate word
        list< pair<index,freq> >::iterator it=mDict[sign].begin(),it2;
        for(int l=0;l<sigStarNum;++l) ++it; //pushing "*" is equivalent to iterating the list
        cout<<vDict[(*it).first];
        (*it).second+=1; //correcting frequency

        //inserting the word to its place
        F=(*it).second;
        it2=find_if(mDict[sign].begin(),it,pred);
        mDict[sign].insert(it2,*it);
        mDict[sign].erase(it);

        //printing punctuation mark
        if(punctStarNum.size()==0) cout<<" ";
        else{
            for(vector<int>::const_iterator it=punctStarNum.begin(); it!=punctStarNum.end(); ++it){
                if(*it==0) cout<<". ";
                else if(*it==1) cout<<", ";
                else if(*it==2) cout<<"? ";
            }
        }
    }
    cout<<endl;
}
//--------------------------------------------------------------

int main()
{
    map<string, list< pair<index,freq> > > mDict;
    vector<string> vDict;

    int N, f;

    cin>>N;
    vDict.resize(N);

    fillDict(mDict,vDict,N);

    //reading query line
    string str;
    vector< string > query;
    while(cin>>str) query.push_back(str);

    printResults(query,mDict,vDict);

    return 0;
}
