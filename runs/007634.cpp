#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

#define MAXN 50000
#define MAXF 2000
#define MAX_WORD_LENGTH 20

using namespace std;

vector < string > dict;
vector < string >::iterator it1;
vector <int> F;
vector <int>::iterator it2;
string button[10]={" ", ".,?", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
int i,j,n,f;

void edit_dic(vector < string > pw, vector <int> pwf, string word, int f)
{
  bool flag=true;
  string tmp=word;
  int tmpf=f;
  vector < string >::iterator pos;
  for(it1=dict.begin(), it2=F.begin(), pos=pw.begin(); flag && it1!=dict.end(); it1++, it2++)
  {
    if(*it1==*pos && *it2==tmpf)
    {
      if(*it1==word) {swap(tmp,*it1); swap(tmpf,*it2); flag=false;}
      else
      {
        swap(tmp,*it1);
        swap(tmpf, *it2);
      }
      pos++;
    }
  }
  for(it1=dict.begin(), it2=F.begin(); flag && it1!=dict.end(); it1++, it2++)
    if(*it1==word) (*it2)++;
  tmpf=f+1;
  for(it1=dict.begin(), it2=F.begin(), pos=pw.begin(); flag && it1!=dict.end(); it1++, it2++)
  {
    if(*it1==*pos && *it2==tmpf)
    {
      if(*it1==word)
      {
        swap(tmp,*it1); swap(tmpf,*it2);
        flag=false;
      }
      else
      {
        swap(tmp,*it1); swap(tmpf, *it2);
      }
      pos++;
    }
  }
}


void wordsearch(string w)
{
  vector < string > pw;                                //possible words
  vector <int> pwf;
  string word;
  unsigned int li, lj, flag;
  int num;
  string::iterator it;
  string::iterator pos;
  unsigned int asterisk=0;
  if (w.empty()) return;
  for(it=w.begin();it!=w.end(); it++)
  {
    if (*it=='*')
    {
      for(asterisk=0, pos=it; pos!=w.end(); pos++, asterisk++);
      w.erase(it,w.end());it--;
    }
  }
  for(it1=dict.begin(), it2=F.begin(); it1!=dict.end(); it1++, it2++)
  {
    word=*it1;
    flag=0;

    for(li=0;li<word.size() && flag==li;li++)
    {
      num=(int)w[li]-48;
      for(lj=0;lj<button[num].size(); lj++)
      {
        if(word[li]==button[num][lj]) flag++;
      }

    }
    if(flag==word.size())
    {  pw.push_back(word); pwf.push_back(*it2);  }
  }
  it1=pw.begin();
  it2=pwf.begin();
  if(asterisk)
  {
    asterisk%=pw.size();
    it1+=asterisk;
    it2+=asterisk;
  }
  printf("%s", it1->c_str());
  edit_dic(pw, pwf, *it1, *it2);
}

void partition(string w)
{
  int m=w.size();
  if (w.empty()) return;
  for(i=0;i<m; ++i)
  {
    if (w[i]=='1' && i)
    {
      string word(w.begin(),w.begin()+i);
      wordsearch(word);
      w.erase(w.begin(),w.begin()+i); m-=i; i=-1;
    }
    else
      if (w[i]=='1' && !i)
      {
        if (m<=1) {printf("."); return;}
        else if(w[i+1]=='1') {printf("."); w.erase(w.begin(),w.begin()+1); m--; i=-1;}
             else
             {
               int asterisk=0;
               for(i=i+1; w[i]=='*'; i++, asterisk++);
               w.erase(w.begin(),w.begin()+asterisk+1);
               m-=i;i=-1;
               printf("%c",button[1][asterisk%3]);
             }
      }
  }
  if(m!=0) wordsearch(w);
}


int main()
{
  FILE *in=stdin;
  char tmp[21];
  fscanf(in, "%d",&n);
  for(i=0; i<n; i++)
  {
    fscanf(in, "%s", tmp);
    fscanf(in, "%d",&f);
    dict.push_back(tmp);
    F.push_back(f);
  }
  while(fscanf(in, "%s", tmp)!=EOF)
  {
    string s(tmp);
    partition(tmp);
    printf(" ");
  }
  return 0;
}







