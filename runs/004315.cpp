#include "stdio.h"
#include <iostream>
#include "stdlib.h"
#include <cstddef>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;
typedef multimap<string,multimap<int,string> >::const_iterator CI1;
typedef multimap<int,string>:: const_iterator CI2;
 typedef multimap<int,string>:: iterator NCI2;
 void display ( pair <int,string> b)

{
    cout<<b.first<<' '<<b.second<<'\n';

}
void onecountout(int a)
{
    switch(a%3)
{
    case 0: cout<<'?'; break;
    case 1: cout<<'.';break;
    case 2: cout<<',';break;
};
}
void display2(pair<string, multimap < int,string> > as)
{
 for_each (as.second.begin(),as.second.end(),display);
}

string transform_1(string a) //стандарт не гарантирует того, что буквы идут подряд. На всякий случай приходится извращаться с проверкой.
{
    string res="";
for (int i=0;i<a.length();i++)
{
switch (a[i]){
case 'a':case 'b':case 'c': res+='2'; break;
case 'd':case 'e':case 'f': res+='3'; break;
case 'g':case 'h':case 'i': res+='4'; break;
case 'j':case 'k':case 'l': res+='5'; break;
 case 'm':case 'n':case 'o': res+='6'; break;
 case 'p':case 'q':case 'r': case 's': res+='7'; break;
 case 't':case 'u':case 'v': res+='8'; break;
 case 'w': case 'x': case 'y': case 'z': res+='9'; break;
}
}
    return res;
}
void rework (multimap <int,string>   *a, int counter,string key)
{
    CI2 i2; int save=0;
    pair<CI2,CI2> aa=make_pair(a->begin(),a->end());
    i2=aa.first;
    pair<NCI2,NCI2> ab=make_pair(a->begin(),a->end());
    NCI2 temp_serv=ab.first;

    int f=0; CI2 serv=i2;
    if(counter)
    {
    for(serv=aa.first;serv!=aa.second;serv++,f++) if(f>counter) break;
   if(f)counter %=f;

      save=counter;
    while (counter)
    {
        counter--;i2++; temp_serv++;
    }
    }
    pair<int,string> pa=make_pair((*i2).first-1,(*i2).second);
    cout<<pa.second;
    pair<int,string> pa2=make_pair((*i2).first-1,pa.second);
    a->erase(temp_serv);

    a->insert(a->lower_bound(pa2.first),pa2);

}

int main()
{ char c=EOF;
   map <string, multimap <int,string> >  a [20];

int m; cin>>m;
string b1=""; int k;
for (int i=0; i<m; i++)
 {string c; cin>>c;int i1=0;
    b1+=c;
    cin>>k;
    pair <int,string> l2 (100000-k,b1);
a[b1.length()-1][transform_1(b1)].insert(l2);

   b1="";
 }
string s,s1,s2;
s2=" ";
int l=0;
do
{ while(cin.peek()==' ')
{
    s2+=' ';cin.get();
}
if (l!=0)cout<<s2; l=1;cin>>s; s1=""; //cout<<s;
int starcounter=0; int onecounter=0; int onenumber=0;
for(int f=0;f<s.length();f++)
{
  switch (s[f])
  {
      case '1':onecounter+=1; onenumber+=1;
      if(s1!="")
{
  rework (&a[s1.length()-1][s1],starcounter,s1); s1="";starcounter=0;
} if(onenumber>1)
{
    onecountout(onecounter-1); onenumber=1;onecounter=1;
}
break;
      case'*': if(onecounter) onecounter+=1; else starcounter+=1; break;
      default:s1+=s[f]; if(onecounter)onecountout(onecounter);onecounter=0;onenumber=0;
  }

}
if(s1!="")
{
  rework (&a[s1.length()-1][s1],starcounter,s1);
}
if(onecounter) switch(onecounter%3)
{
    case 0: cout<<'?'; break;
    case 1: cout<<'.';break;
    case 2: cout<<',';break;
};
 if(cin.peek()!='\n'&&cin.peek()!=EOF) ; if(cin.peek()==' ') cin.get(); s2=" ";
} while (cin.peek()!='\n'&&cin.peek()!=EOF);
}


