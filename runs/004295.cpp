#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <list>
#include <cstdlib>
#include <vector>
#include <fstream>
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
// Mapping character to phone button
//=============================================================
int getNumByChar(char ch)
{
    if(ch=='a' || ch=='b' || ch=='c') return 2;
    else if(ch=='d' || ch=='e' || ch=='f') return 3;
    else if(ch=='g' || ch=='h' || ch=='i') return 4;
    else if(ch=='j' || ch=='k' || ch=='l') return 5;
    else if(ch=='m' || ch=='n' || ch=='o') return 6;
    else if(ch=='q' || ch=='r' || ch=='s' || ch=='p') return 7;
    else if(ch=='t' || ch=='u' || ch=='v') return 8;
    else if(ch=='w' || ch=='x' || ch=='y' || ch=='z') return 9;
}
//--------------------------------------------------------------

//=============================================================
// Mapping word to sequence of phone buttons to push
//=============================================================
int getSignature(const string &str)
{
    int sig=0;

    for(int i=0;i<str.size();++i){
        sig=sig*10+getNumByChar(str[i]);
    }

    return sig;
}
//--------------------------------------------------------------

//=============================================================
// inserting word into mDict
//=============================================================
void insertWord(const string &str, index id,freq f, map<int, list< pair<index,freq> > > &mDict)
{
    int sign=getSignature(str);

    for(int i=0;i<str.size();++i){
        mDict[sign].push_back(make_pair(id,f));
        sign=sign/10;
    }
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
void fillDict(map<int, list< pair<index,freq> > > &mDict, vector<string> &vDict, int N)
{
    string str;
    list< pair<index,freq> > l;
    int f;
    for(int i=0;i<N;++i){
        cin>> str >> f;
        vDict[i]=str;
        insertWord(str,i,f,mDict);
    }

    map<int, list< pair<index,freq> > >::iterator it=mDict.begin();
    for(;it!=mDict.end();++it){
        l=(*it).second;
        //stable_sort((*it).second.begin(),(*it).second.end(),compare);
        //stable_sort(l.begin(),l.end(),compare);
        l.sort(compare);
    }
}
//--------------------------------------------------------------

//=============================================================
// From file
//=============================================================
void fillDictFromFile(map<int, list< pair<index,freq> > > &mDict, vector<string> &vDict, int N,ifstream &file)
{
    string str;
    list< pair<index,freq> > l;
    int f;
    for(int i=0;i<N;++i){
        file>> str >> f;
        vDict[i]=str;
        insertWord(str,i,f,mDict);
    }

    map<int, list< pair<index,freq> > >::iterator it=mDict.begin();
    for(;it!=mDict.end();++it){
        l=(*it).second;
        //stable_sort((*it).second.begin(),(*it).second.end(),compare);
        //stable_sort(l.begin(),l.end(),compare);
        l.sort(compare);
    }
}
//-------------------------------------------------------------

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
//
//=============================================================
void parseQuery(string str, int &sigLen, int &sigStarNum, int &onesNum, int &onesStarNum)
{

    /*int count=0,i=0;
    onesNum=-1;
    sigStarNum=-1;
    while(str[i]!='1' && str[i]!='*' && i<str.size()){
        ++sigLen;
        ++i;
    }
    if(i<str.size()){
        if(str[i]=='1') sigStarNum=0;
        else if(str[i]=='*') onesNum=0;
    }
    else {
        sigStarNum=0;
        onesNum=0;
        onesStarNum=0;
        return;
    }

    if()*/
    basic_string<char>::iterator sigEnd=find(str.begin(),str.end(),'1');
    sigStarNum=static_cast<int>(count(str.begin(),sigEnd,'*'));
    onesNum=static_cast<int>(count(sigEnd,str.end(),'1'));
    onesStarNum=static_cast<int>(count(sigEnd,str.end(),'*'));
    sigLen=sigEnd-str.begin()-sigStarNum;
}
//--------------------------------------------------------------

//=============================================================
//
//=============================================================
void printResults(vector< string > &query,map<int, list< pair<index,freq> > > &mDict,vector<string> &vDict)
{
    int sigLen,sigStarNum,onesNum,onesStarNum;
    int sign;

    for(int i=0;i<query.size();++i){
        parseQuery(query[i],sigLen,sigStarNum,onesNum,onesStarNum);
        sign=atoi(getSubStr(query[i],sigLen).c_str());

//        for(list< pair<index,freq> >::iterator iter=mDict[sign].begin();iter!=mDict[sign].end();++iter){
//            cout<<vDict[(*iter).first]<<" "<<(*iter).second<<endl;
//        }
//cout<<endl;
        list< pair<index,freq> >::iterator it=mDict[sign].begin(),it2;
        for(int l=0;l<sigStarNum;++l) ++it;
        cout<<vDict[(*it).first];
        (*it).second+=1;

//        for(list< pair<index,freq> >::iterator iter=mDict[sign].begin();iter!=mDict[sign].end();++iter){
//            cout<<vDict[(*iter).first]<<" "<<(*iter).second<<endl;
//        }
//cout<<endl;
        F=(*it).second;
        it2=find_if(mDict[sign].begin(),it,pred);
        mDict[sign].insert(it2,*it);
        mDict[sign].erase(it);

//        for(list< pair<index,freq> >::iterator iter=mDict[sign].begin();iter!=mDict[sign].end();++iter){
//            cout<<vDict[(*iter).first]<<" "<<(*iter).second<<endl;
//        }
//        cout<<endl;
        if(onesNum==0) cout<<" ";
        else if(onesNum==1) {
            if(onesStarNum==0) cout<<". ";
            else if(onesStarNum==1) cout<<", ";
            else if(onesStarNum==2) cout<<"?";
        }
        else if(onesNum==3) for(int k=0;k<3;++k) cout<<".";

    }
    cout<<endl;
}
//--------------------------------------------------------------

int main()
{
    map<int, list< pair<index,freq> > > mDict;
    vector<string> vDict;

    int N, f;
#ifndef DEBUG
    cin>>N;
#else
    ifstream file("test4");
    file>>N;
#endif
   // cout<<N<<endl;

    vDict.resize(N);

#ifndef DEBUG
    fillDict(mDict,vDict,N);
#else
    fillDictFromFile(mDict,vDict,N,file);
#endif

    string str="";
    vector< string > query;

#ifndef DEBUG
    while(cin>>str) query.push_back(str);
#else
    while(file>>str) query.push_back(str);
#endif

    printResults(query,mDict,vDict);

    //for(int i=0;i<query.size();i++)
    //cout<<query[i]<<endl;

    //string asd("home");
    //cout<<getSignature(asd)<<endl<<endl;

   // list< pair<index,freq> >    l;
    //l=mDict[2];
    /*for(list< pair<index,freq> >::const_iterator it=l.begin();it!=l.end();++it){
        cout<<vDict[(*it).first]<<endl;
    }*/



   /* int sign,ssn,on,osn;
    parseQuery(string("228111"),sign,ssn,on,osn);
    //cout<<sign<" "<<ssn<<" "<<on<<" "<<osn<<endl;
    cout<<endl<<sign<<endl;
    cout<<ssn<<endl;
    cout<<on<<endl;
    cout<<osn<<endl;*/
    return 0;
}
