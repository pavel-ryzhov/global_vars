


#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>


#define qwe false


using namespace std;

FILE* fi=stdin;//fopen("t9.in","r");
FILE* fo=stdout;//fopen("t9.out","w");

struct Entry{
    Entry(string w,int f){word=w;freq=f;}
    string word;
    int freq;
    bool operator < (const Entry& e) const {
        if(freq==e.freq) return word<e.word;
        return freq>e.freq;
    }
};

map<string,vector<Entry> > dict;

map<char,char> number_value;
char puncts[]={'.',',','?'};


string str2num(string s){
    string r="";
    for(unsigned int a=0;a<s.size();a++){
        r.append(1,number_value[s[a]]);
    }
    return r;
}

void init(){
    number_value['a']='2';
    number_value['b']='2';
    number_value['c']='2';
    number_value['d']='3';
    number_value['e']='3';
    number_value['f']='3';
    number_value['g']='4';
    number_value['h']='4';
    number_value['i']='4';
    number_value['j']='5';
    number_value['k']='5';
    number_value['l']='5';
    number_value['m']='6';
    number_value['n']='6';
    number_value['o']='6';
    number_value['p']='7';
    number_value['q']='7';
    number_value['r']='7';
    number_value['s']='7';
    number_value['t']='8';
    number_value['u']='8';
    number_value['v']='8';
    number_value['w']='9';
    number_value['x']='9';
    number_value['y']='9';
    number_value['z']='9';
}


ostream& operator<< (ostream& s, Entry e){
    s << e.word << ":" << e.freq << endl;
    return s;
}

template<class T>
ostream& operator<< (ostream& s, vector<T> m){
    unsigned int i;
    for(i=0;i<m.size();i++){
        s << m[i] << " ";
    }
    s << endl;
    return s;
}

template<class T,class TT>
ostream& operator<< (ostream& s, map<T,TT> m){
    typename map<T,TT>::iterator i;
    for(i=m.begin();i!=m.end();i++){
        s << (*i).first << "=" << (*i).second << " ";
    }
    s << endl;
    return s;
}




void promote_word(vector<Entry> &subdict,int pos){
    if(qwe) cout << "Promoting " << subdict[pos] << endl;
    if(qwe) cout << subdict << endl;
    int a;
    Entry e=subdict[pos];
    subdict.erase(subdict.begin()+pos);

    e.freq++;
    for(a=0;a<subdict.size();a++){
        if(e.freq>=subdict[a].freq){
            subdict.insert(subdict.begin()+a,e);
            goto lqwe;
        }
    }
    subdict.insert(subdict.end(),e);

    lqwe:a=a;
    if(qwe) cout << "Done promoting" << endl;
    if(qwe) cout << subdict << endl;
}



char nextChar(){
    char ch;
    fscanf(fi,"%c",&ch);
    return ch;
}


enum{TYPE_WORD,NEXT_WORD,SPACE,PUNCT};



bool is29(char c){return '2'<=c && c<='9';}
bool is1(char c){return '1'==c;}
bool issp(char c){return c==' ';}
bool isast(char c){return c=='*';}
bool isend(char c){return c=='\n';}

string process(){
    char c;
    int state=SPACE;
    string res;
    string current_nword="";
    int punct_no=0;
    int ast_no=0;
    for(;;){
        c=nextChar();
        if(qwe) cout << " Got char <" << c << ">" << endl;
        switch(state){
        case TYPE_WORD:{
                if(is29(c)){
                    current_nword.append(1,c);
                    state=TYPE_WORD;
                }else if(is1(c)){
                    string w;
                    w=dict[current_nword][ast_no].word;
                    promote_word(dict[current_nword],ast_no);
                    res.append(w);
                    ast_no=0;
                    state=PUNCT;
                }else if(issp(c)){
                    string w;
                    w=dict[current_nword][ast_no].word;
                    promote_word(dict[current_nword],ast_no);
                    res.append(w);
                    res.append(" ");
                    ast_no=0;
                    state=SPACE;
                }else if(isast(c)){
                    ast_no++;
                }else if(isend(c)){
                    string w;
                    w=dict[current_nword][ast_no].word;
                    promote_word(dict[current_nword],ast_no);
                    res.append(w);
                    ast_no=0;
                    return res;
                }else{ throw "unexpected char"+string(1,c);}
        }break;
        case SPACE:{
                if(is29(c)){
                    current_nword=string(1,c);
                    state=TYPE_WORD;
                }else if(is1(c)){
                    state=PUNCT;
                }else if(issp(c)){
                    res.append(" ");
                    state=SPACE;
                }else if(isast(c)){
                    throw "asterics unexpected";
                    state=0;
                }else if(isend(c)){
                    return res;
                }else{ throw "unexpected char"+string(1,c);}
        }break;
        case PUNCT:{
                if(is29(c)){
                    res.append(1,puncts[ast_no]);
                    current_nword=string(1,c);
                    ast_no=0;
                    state=TYPE_WORD;
                }else if(is1(c)){
                    res.append(1,puncts[ast_no]);
                    ast_no=0;
                    state=PUNCT;
                }else if(issp(c)){
                    res.append(1,puncts[ast_no]);
                    ast_no=0;
                    res.append(" ");
                    state=SPACE;
                }else if(isast(c)){
                    ast_no++;
                    state=PUNCT;
                }else if(isend(c)){
                    res.append(1,puncts[ast_no]);
                    ast_no=0;
                    return res;
                }else{ throw "unexpected char"+string(1,c);}
        }break;
        }
    }
}






int main(){
    int N;
    int a;
    char buf[32];
    int f;
    init();
    fscanf(fi," %d",&N);
    for(a=0;a<N;a++){
        fscanf(fi,"%s %d",buf,&f);
        if(qwe) cout << buf << " " << f << endl;
        if(qwe) cout << ">>" << str2num(buf) << endl;
        dict[str2num(buf)].push_back(Entry(buf,f));
    }


    for(map<string,vector<Entry> >::iterator i=dict.begin();
        i!=dict.end();
        i++)
    {
        sort(&(*i).second[0],&(*i).second[(*i).second.size()]);
    }

    vector<int> vv;
    vv.push_back(12);
    vv.push_back(23);
    vv.push_back(34);
    if(qwe) cout << vv;
    if(qwe) cout << number_value;
    if(qwe) cout << dict;

    fscanf(fi,"%*c");
    if(qwe) cout<<  "================================\n";
    try{
        cout << process() << endl;
    }catch(string s){
        cout << "error:" << s << endl;
        throw;
    }
}












































