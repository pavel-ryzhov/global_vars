
#include <iostream>
#include <string>

using namespace std;

struct myword{
char* w;
int k;
} ;

struct myelem{
	myelem** key;
	myword** words;
	int wordcount;
}  ;

int main(int argc, char* argv[])
{
myelem* root=new myelem;
  root->key=new myelem*[8];
  for (int i1=0;i1<8;i1++)root->key[i1]=0;
  root->words=0;

int n;//количество слов в словаре
cin>>n;

char* st=new char[20];
 int r;
myelem* cur=root;

for (int z=0;z<n;z++){      //начало ввода
cur=root;
cin>>st;

cin>>r;
 int i=0;
 int j=-1;

bool f=true;
while (f){
switch (st[i]) {
case 'a':j=0;break;
case 'b':j=0;break;
case 'c':j=0;break;
case 'd':j=1;break;
case 'e':j=1;break;
case 'f':j=1;break;
case 'g':j=2;break;
case 'h':j=2;break;
case 'i':j=2;break;
case 'j':j=3;break;
case 'k':j=3;break;
case 'l':j=3;break;
case 'm':j=4;break;
case 'n':j=4;break;
case 'o':j=4;break;
case 'p':j=5;break;
case 'q':j=5;break;
case 'r':j=5;break;
case 's':j=5;break;
case 't':j=6;break;
case 'u':j=6;break;
case 'v':j=6;break;
case 'w':j=7;break;
case 'x':j=7;break;
case 'y':j=7;break;
case 'z':j=7;break;
default: f=false;
	break;
}
i++;

if (f){
	if (cur->key[j]==NULL){
	cur->key[j]=new myelem;
	cur=cur->key[j];
	cur->key=new myelem*[8];
	for (int i1=0;i1<8;i1++)cur->key[i1]=0;
	cur->words=0;
	}else {cur=cur->key[j];}
}
}
if (cur->words==0){
	cur->words=new myword*[10000];
	cur->wordcount=1;
	cur->words[0]=new myword;
	cur->words[0]->w=new char[20];
	for (int ii=0;ii<i;ii++)cur->words[0]->w[ii]=st[ii];
	cur->words[0]->k=r;
}else{
	cur->words[cur->wordcount]=new myword;
	cur->words[cur->wordcount]->w=new char[20];
	int t=0;
	while ((t<cur->wordcount)&&(r<=(cur->words[t]->k)))t++;
	int tt=0;
	while ((t+tt)<cur->wordcount){
	cur->words[cur->wordcount-tt]=cur->words[cur->wordcount-1-tt] ;
	tt++;
	}
	for (int ii=0;ii<i;ii++)cur->words[t]->w[ii]=st[ii];
	cur->words[t]->k=r;
	cur->wordcount++;
}
}   // конец ввода


  string m,sdf;

	getline(cin,sdf);
   getline(cin,m);
  
  int i=0;
  while (i<m.length()){

	cur=root;
	int sl=0;
	while ((m[i]!=' ')&&(m[i]!='1')){

	switch (m[i]) {
	case '*':sl++;           break;
	case '2':cur=cur->key[0];break;
	case '3':cur=cur->key[1];break;
	case '4':cur=cur->key[2];break;
	case '5':cur=cur->key[3];break;
	case '6':cur=cur->key[4];break;
	case '7':cur=cur->key[5];break;
	case '8':cur=cur->key[6];break;
	case '9':cur=cur->key[7];break;
	default:     break;}
    i++;
	}
	cout<<cur->words[sl]->w;
	cur->words[sl]->k++;
	int kk=cur->words[sl]->k;
	myword* w1=cur->words[sl];
	while ((sl!=0)&&(cur->words[sl]->k<=kk)){
	sl--;
	cur->words[sl+1]=cur->words[sl];
	}
	cur->words[sl]=w1;

	if (m[i]=='1'){
		if (m[i+1]!='*'){
		cout<<'.';
		i++;
		}else{
			if (m[i+2]!='*'){
			cout<<',';
			i=i+2;
			}else{
			cout<<'?';
			i=i+3;
			}
		}
	}
	if (m[i]==' '){
	cout<<' ';
    i++;
	}
  }

	return 0;
}
//---------------------------------------------------------------------------
