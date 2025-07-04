/* PROB: T9
   LANG: C++
*/


//#include "stdafx.h"
//#include <conio.h>
#include <list>
#include <iostream>
#include <string>

using namespace std;

unsigned long long dstr(string s) {
	int i=0;
	unsigned long long d=0;
	while(s[i]) {
		switch (s[i]) {
			case 'a' : {d+=2; d*=10;}
			break;
			case 'b' : {d+=2; d*=10;}
			break;
			case 'c' : {d+=2; d*=10;}
			break;
			case 'd' : {d+=3; d*=10;}
			break;
			case 'e' : {d+=3; d*=10;}
			break;
			case 'f' : {d+=3; d*=10;}
			break;
			case 'g' : {d+=4; d*=10;}
			break;
			case 'h' : {d+=4; d*=10;}
			break;
			case 'i' : {d+=4; d*=10;}
			break;
			case 'j' : {d+=5; d*=10;}
			break;
			case 'k' : {d+=5; d*=10;}
			break;
			case 'l' : {d+=5; d*=10;}
			break;
			case 'm' : {d+=6; d*=10;}
			break;
			case 'n' : {d+=6; d*=10;}
			break;
			case 'o' : {d+=6; d*=10;}
			break;
			case 'p' : {d+=7; d*=10;}
			break;
			case 'q' : {d+=7; d*=10;}
			break;
			case 'r' : {d+=7; d*=10;}
			break;
			case 's' : {d+=7; d*=10;}
			break;
			case 't' : {d+=8; d*=10;}
			break;
			case 'u' : {d+=8; d*=10;}
			break;
			case 'v' : {d+=8; d*=10;}
			break;
			case 'w' : {d+=9; d*=10;}
			break;
			case 'x' : {d+=9; d*=10;}
			break;
			case 'y' : {d+=9; d*=10;}
			break;
			case 'z' : {d+=9; d*=10;}
			break;
			default :  {d=0; s=""; i=-1; }
			break; 
			
		}
		i++;
	}
 d/=10;   
 return d;
}

struct multimap {
     string s; 
	 unsigned long long d; //dstring 
	 int f; //frequency

	 bool operator < (multimap & v) {
		if ( d < v.d ) return true;
		if ( d == v.d && f > v.f ) return true;
		if ( d == v.d && f == v.f && s < v.s) return true;
		else return false;
	}

	 bool operator == (multimap & v) {
		if ((s==v.s)&&(f==v.f)&&(d==v.d)) return true;
		else return false;
	 }
	 
	 bool operator != (multimap & v) {
		if ((s==v.s)&&(f==v.f)&&(d==v.d)) return false;
		else return true;
	 }
	
};





bool push (list <multimap> * L) {
	int n=0;
	int result=scanf ("%d",&n);
	if ((result!=1)||(n<3)||(n>50000)) return 1;
	for (int i=0; i<n; ++i) {
		multimap * m=new multimap;
		cin>>m->s;
		result=scanf ("%d",&m->f);
		if ((result!=1)||(m->f<1)||(m->f>1000)) m->f=1;
		m->d=dstr(m->s);
		if (m->d) L->push_back(*m);
		delete m;

	}
	   
	L->sort(); return 0;
}

bool pop (list <multimap> * L) {
	string s;
	getline(cin,s,'\n');
	int i=0;
	while (s[i]) {
	int h=0;
	
	int k=0;
	
	for (i; (s[i]>='2')&&(s[i]<='9'); i++) {
		h+=(s[i]-'0'); h*=10;
	}
	h/=10;  
	if (h) {
		list <multimap>::iterator j, g;
	
		for (j = L->begin( ); (j->d!=h && (*j) != L->back( )); j++) {};
	    if ( (*j)==L->back()&&(j->d!=h)) 
			return 1;
		g=j;
		
		while (s[i]&& ((*j) != L->back( ))&&(j->d==h)&&(s[i]=='*')) { 
			j++; 
			if ((*j)==L->back()&&(s[i+1])&&(s[i+1]=='*')&&(j->d==h)){ j=g; i++; }
			if (j->d!=h) j=g;
			i++;
		}
	    
		
		cout<<j->s;
		j->f+=1;
		for (g = L->begin( ); (g->d!=h && (*g) != L->back( )); g++) {};
		while (g->f>j->f) g++;
		L->insert (g,*j);
		L->erase(j);
	
	}

	if (s[i]=='1') { 
		i++;
		
		while (s[i]&&(s[i]=='*')) {
			i++;	
			k++;
		} 
  
		switch(k%3) {
			case 0 : cout<<'.'; 
				break;
			case 1 : cout<<',';
				break;
			case 2 : cout<<'?';
				break;
			default : break;


		}

	}
	if (s[i]==' ') { cout<<" "; i++;} }
	return 0;

}

int main()
{ //freopen("t9.in", "r", stdin);
  //freopen("t9.out", "w", stdout);
	
	list <multimap> L;
	
	bool flag;
	flag = push (&L);
	if (flag!=0) return 2; 
    
	string s;
	getline (cin, s, '\n'); 
	flag=pop(&L);
	if (flag!=0) return 2;
	
	  
	L.clear();
	//getch();
	return 0;
}

