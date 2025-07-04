/*
 * File:   main.cpp
 * Author: Marx
 *
 * Created on 25 Март 2010 г., 1:26
 */


#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

typedef multimap <int, string> MM;//Все слова на ключ Т9
typedef map <string, MM> M;//карта с ключами в виде Т9
typedef pair <int, string> MMPair;
typedef pair <string, MM> MPair;
typedef MM::iterator MMIt;
typedef M::iterator MIt;

string Word_to_StrT9(string &s){//ф-ция переводящая слово в Т9
    string out;
    for (unsigned int i=0; i<s.length(); i++){
        switch (s[i]) {
            case 'a':out.push_back('2');break;
            case 'b':out.push_back('2');break;
            case 'c':out.push_back('2');break;
            case 'd':out.push_back('3');break;
            case 'e':out.push_back('3');break;
            case 'f':out.push_back('3');break;
            case 'g':out.push_back('4');break;
            case 'h':out.push_back('4');break;
            case 'i':out.push_back('4');break;
            case 'j':out.push_back('5');break;
            case 'k':out.push_back('5');break;
            case 'l':out.push_back('5');break;
            case 'm':out.push_back('6');break;
            case 'n':out.push_back('6');break;
            case 'o':out.push_back('6');break;
            case 'p':out.push_back('7');break;
            case 'q':out.push_back('7');break;
            case 'r':out.push_back('7');break;
            case 's':out.push_back('7');break;
            case 't':out.push_back('8');break;
            case 'u':out.push_back('8');break;
            case 'v':out.push_back('8');break;
            case 'w':out.push_back('9');break;
            case 'x':out.push_back('9');break;
            case 'y':out.push_back('9');break;
            case 'z':out.push_back('9');break;
        }
    }
    return out;
}

string search(M& m,string key, short unsigned int zv){
    string word;
    int rate;
    MMIt p;
    p=m.find(key)->second.begin();
    for (int i = 0; i<zv; i++)p++;
    word=p->second;
    rate=p->first;
    rate--;
    m.find(key)->second.erase(p);
    p=m.find(key)->second.find(rate);
    m.find(key)->second.insert(p,MMPair(rate,word));

    return word;
}



int main() {

M dist;//multimap контейнер со словами с ключом в виде Т9 выражения
int N;//размер словаря

//ввод словаря
cin>>N;
string stmp, key;
int itmp;
MM mmtmp;
for (int i=0; i < N; i++){  
    cin>>stmp>>itmp;
    key = Word_to_StrT9(stmp);
    if(!dist.count(key)){
        mmtmp.insert(MMPair((10000-itmp),stmp));
        dist.insert(MPair(key,mmtmp));
        mmtmp.clear();}
    else
        dist.find(key)->second.insert(MMPair(10000-itmp,stmp));
}


//ввод строки с текстом в виде Т9
string sms;
string m;
cin>>sms;
getline(cin, m);//mingw не хотел есть getline() без cin :(
sms += m;
m.clear();

//анализ строки и вывод обычных слов
string tmp;//строка со словом в Т9 = кеу в multimape
int zv=0;//кол-во звездочек после слова
for  (unsigned int i = 0; i<sms.length(); i++){
    if (sms[i] != ' ' && sms[i] != '1')
        tmp.push_back(sms[i]);
    if (sms[i] == ' '){
        if (tmp.length()>0){
        cout<<search(dist,tmp,zv);//находим все слова по Т9
        tmp.clear();
        zv=0;}
        else cout<<' ';
    }
    if (sms[i] == '1'){
        if (tmp.length()>0){
            cout<<search(dist,tmp,zv);//находим все слова по Т9
            tmp.clear();
            zv=0;}
        if (sms[i+1] != '*')
        cout<<'.',i++;
        else{
            if (sms[i+2] != '*')
            cout<<',',i = i + 2;
            else
            cout<<'?',i = i + 3;
            }
}
    if (sms[i]==' ')cout<<' ';
    if (sms[i] == '*')  zv++,tmp.erase(tmp.length()-1,1);
}
if (tmp.length()>0)cout<<search(dist,tmp,zv);
cout<<endl;

return (0);
}