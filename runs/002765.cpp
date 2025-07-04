// T9.cpp : Defines the entry point for the console application.
//
//Bolshakov A.N.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <map>
#include <list>
#include <iostream>
#include <algorithm>

#define N 50000
#define M 100000

using namespace std;
struct t_node{
	string word;
	int freq;
	bool operator <(t_node &t){
		return freq < t.freq;
	}
	bool operator ==(const t_node &t){
		return (word == t.word && freq == t.freq);
	}
};
map<int, list<t_node> > mp_dict; //dictionary
int but [] = {2,2,2,
3,3,3,
4,4,4,
5,5,5,
6,6,6,
7,7,7,7,
8,8,8,
9,9,9,9};
string punkt = ".,?";

void f_sort(pair<int, list<t_node> > t){
	t.second.sort();
}
int main()
{
	int n, m,j=0;
	scanf("%d", &n);
	int t; string ts;
	for(int i=0;i<n;++i){
		cin >> ts >> t;	
		t_node node = {ts, t};
		m=0; j=0; while(j<ts.length())m = m*10 + (but[ts[j++] - 'a']);
		mp_dict[m].push_back(node);
	}
	for_each(mp_dict.begin(), mp_dict.end(), f_sort); //it faster..

	string  res="";
	int stars = 0, tmp=0;
	char msg[M];
	getchar();
	cin.getline(msg, M);
	j=0;while(true){
		if(isdigit(msg[j]) && msg[j]!='1'){
			tmp = tmp*10 + (msg[j] - '0');
		}else if(msg[j]=='*'){
			stars=1;
			while(msg[++j] =='*')++stars;
			continue;
		}else if((isspace(msg[j]) || !msg[j] || msg[j]=='1') && tmp){
			list<t_node>::iterator it = mp_dict[tmp].begin(),n_it;
			while(stars--)it++;
			res += it->word;
			
			it->freq++;
			t_node nod(*it);
			mp_dict[tmp].erase(it);
			n_it = mp_dict[tmp].begin();
			while( (n_it != mp_dict[tmp].end())  &&  ((n_it->freq) > (nod.freq)))n_it++;
			mp_dict[tmp].insert(n_it, nod);			
			tmp=stars=0;
		}
		if(isspace(msg[j])){
			res += ' ';
		}else if(msg[j]=='1'){
			stars=0;while(msg[++j] && msg[j]=='*')++stars;
			res += punkt[stars];
			stars=0;
			continue;
		}
		if(!msg[j])break;
		++j;
	}
	cout << res << endl;

	return 0;
}

