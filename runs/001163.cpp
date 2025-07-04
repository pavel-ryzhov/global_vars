#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <deque>
#include <map>

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

    deque<Word>* di = &e[key];

    if(index==0){
        (*di)[0].weight++;
        return (*di)[0].text;
    }

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

    for(map<string,deque<Word> >::iterator p=e.begin();p!=e.end();++p){
        stable_sort(p->second.begin(),p->second.end(),compare);
    }


    string str;
    stringstream s("");

    cin.ignore(1,'\n');
    getline(cin,str);

    int ln = str.length();

    bool mode = true;
    string key = ""; int cnt = 0;

    for(int i=0;i<ln;i++) {
        if(str[i]==' ') {
            if(key.length() != 0) s << fetch(key,cnt);
            s << " ";
            key = "";
            cnt = 0;
            mode = true;
            continue;
        }
        if(mode)
        {
            if(str[i] == '1'){
                if(key.length() != 0) s << fetch(key,cnt);
                key = '1';
                cnt = 0;
                mode = false;
                continue;
            }

            if(str[i] == '*'){
                cnt = 1;
                mode = false;
                continue;
            }

            key += str[i];
        }
        else
        {
            if(str[i] != '*'){
                s << fetch(key,cnt);
                key = "";
                cnt = 0;
                i--;
                mode = true;
                continue;
            }

            cnt++;
        }
    }

    if(key.length() != 0) s << fetch(key,cnt);
    cout << s.str();

    return 0;
}
