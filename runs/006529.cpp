/* PROB: T9
   LANG: C++
*/


//#include "stdafx.h"

#include <list>
#include <iostream>
#include <string>


using namespace std;

unsigned long long dstr(char* s) {
	int i=0;
	unsigned long long d=0;
	while(s[i]>='a'&& s[i]<='z') {
		switch (s[i]) {
			case 'a' : d+=2; 
					break;
			case 'b' : d+=2;
					break;
			case 'c' : d+=2;
					break;
			case 'd' : d+=3;
					break;
			case 'e' : d+=3; 
					break;
			case 'f' : d+=3;
					break;
			case 'g' : d+=4;
					break;
			case 'h' : d+=4;
					break;
			case 'i' : d+=4;
					break;
			case 'j' : d+=5;
					break;
			case 'k' : d+=5;
					break;
			case 'l' : d+=5;
					break;
			case 'm' : d+=6;
					break;
			case 'n' : d+=6;
					break;
			case 'o' : d+=6;
					break;
			case 'p' : d+=7;
					break;
			case 'q' : d+=7;
					break;
			case 'r' : d+=7;
					break;
			case 's' : d+=7;
					break;
			case 't' : d+=8;
					break;
			case 'u' : d+=8;
					break;
			case 'v' : d+=8;
					break;
			case 'w' : d+=9;
					break;
			case 'x' : d+=9;
					break;
			case 'y' : d+=9;
					break;
			case 'z' : d+=9;
					break;
						
		}
		i++; 
		if (i==19) return d;
		else d*=10;
	}
 d/=10;   
 return d;
}

struct multimap {
     char s[21]; 
	 unsigned long long d; //dstring 
	 int f; //frequency

	 bool operator < (multimap & v) {
		if ( d < v.d ) return true;
		if ( d == v.d && f > v.f ) return true;
		else return false;
	}
	
};

void push (list <multimap> * L) {
	int n=0, lIndex;
	cin>>n;
	
	for (int i=0; i<n; ++i) {
	multimap * m=new multimap;
		cin>>m->s;
		scanf ("%d",&m->f);
		m->d=dstr(m->s);
		char h=m->s[0];
		lIndex=dstr(&h)-2;
		if (m->d) L[lIndex].push_back(*m);
		L[lIndex].sort();
		delete m;
	}

	        

}


void pop (list <multimap> * L) {
	string s;
	getline(cin,s,'\n');
	int i=0,lIndex=0;
	bool f=1;

	while (s[i]) {
		unsigned long long h=0;
		int k=0;
	
		for (i; (s[i]>='2')&&(s[i]<='9')&&(k<19); i++,k++) {
			h+=(s[i]-'0');  
			if (k==0) lIndex=s[i]-'0'-2;
			if (k<18) h*=10;
		}
		if (k<19) h/=10;  
		
		if (h) {
			list <multimap>::iterator j, g;
			for (j = L[lIndex].begin( ); (j->d!=h && j != L[lIndex].end( )); j++) {};
			
			g=j;
		
			if (k==19) {
				int p=s[i]-'0';
				i++;
				char l=g->s[19];
				while (j->d==g->d && f) {
					while (dstr(&l)!=p) {
						j++; 
						l=j->s[19];
					}
					if (s[i] && s[i]=='*' && dstr(&l)==p) { 
						i++; 
						j++; 
					}
					else f=0;
				}
			}
		
			else {
				while (s[i]&& (j != L[lIndex].end( ))&&(j->d==h)&&(s[i]=='*')) { 
				j++; 
				i++; 
				f=0; 
				}
			}
	    
		
			cout<<j->s;
			j->f+=1;
			if (!f) {
			while (g->f>j->f) 
				g++;
			L[lIndex].insert (g,*j);
			L[lIndex].erase(j);
			}
	
		}

		if (s[i]=='1') { 
			i++;
			k=0;
		
			while (s[i]&&(s[i]=='*')) {
				i++;	
				k++;
			} 
  
			switch(k) {
				case 0 : cout<<'.'; 
						break;
				case 1 : cout<<',';
						break;
				case 2 : cout<<'?';
					break;
			}

		}
	
		if (s[i]==' ') { 
			cout<<" "; 
			i++;
		} 
	
	
	}
	
}

int main()
{   //freopen("t9.in", "r", stdin);
    //freopen("t9.out", "w", stdout);
	
	list <multimap>  L[8];
	push (L);
	
	string s;
	getline (cin, s, '\n'); 

	pop(L);
	
   
	return 0;
}


