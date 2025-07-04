#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <deque>
#include <algorithm>

using namespace std;

struct Word {
    string text;
    int weight;
};
bool compare(const Word& a, const Word& b) {
    return a.weight > b.weight;
};

map<string,deque<Word> > e;

string fetch(string key, int index){
    if(key[0]=='1'){
        string pt = ".,?";
        pt = pt[index];
        return pt;
    }
    if(index==0) return e[key][0].text;
    
    deque<Word>* di = &e[key];
    string tx = (*di)[index].text;
    int i = index;
    int wt = ++(*di)[index].weight;

    while(i>0 && (*di)[i-1].weight<=wt){
        Word w = (*di)[i];
        (*di)[i] = (*di)[i-1];
        (*di)[i-1] = w;
        i--;
    }
    
    return tx;
}

int main() {
    
    int count;
    cin >> count;

    for(int i=0;i<count;i++){
        Word w;
        cin >> w.text >> w.weight;

        int len = w.text.length();
        string key = "";
        for(int j=0;j<len;j++){
            if(w.text[j]=='a' || w.text[j]=='b' || w.text[j]=='c'){ key += "2"; continue; }
            if(w.text[j]=='d' || w.text[j]=='e' || w.text[j]=='f'){ key += "3"; continue; }
            if(w.text[j]=='g' || w.text[j]=='h' || w.text[j]=='i'){ key += "4"; continue; }
            if(w.text[j]=='j' || w.text[j]=='k' || w.text[j]=='l'){ key += "5"; continue; }
            if(w.text[j]=='m' || w.text[j]=='n' || w.text[j]=='o'){ key += "6"; continue; }
            if(w.text[j]=='t' || w.text[j]=='u' || w.text[j]=='v'){ key += "8"; continue; }
            if(w.text[j]=='p' || w.text[j]=='q' || w.text[j]=='r' || w.text[j]=='s'){ key += "7"; continue; }
            if(w.text[j]=='w' || w.text[j]=='x' || w.text[j]=='y' || w.text[j]=='z'){ key += "9"; continue; }
        }
        e[key].push_back(w);
    }

    for(map<string,deque<Word> >::iterator i=e.begin();i!=e.end();++i)
        sort(i->second.begin(),i->second.end(), compare);

    string str;
    stringstream s("");
    while(cin >> str){
        int ln = str.length();
        string item = ""; int index = 0;

        bool mode = true;
        for(int i=0;i<ln;i++){
            if(mode){
                if(str[i]=='1'){
                    s << fetch(item, index);
                    item = "1";
                    mode = false;
                } else if(str[i]=='*'){
                    index++;
                    mode = false;
                } else {
                    item += str[i];
                }
            } else {
                if(str[i]=='1'){
                    s << fetch(item, index);
                    item = "1"; index=0;
                }else if(str[i]!='*'){
                    s << fetch(item, index);
                    item = ""; index=0; i--;
                    mode = true;
                } else
                    index++;
            }
        }
        if(item.length()!=0) s << fetch(item, index);
        if(!cin.eof()) s << " ";
    }

    cout << s.str();
    
    return 0;
}
