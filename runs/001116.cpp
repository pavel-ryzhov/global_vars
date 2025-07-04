#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <string.h>

char * strncpy ( char * destination, const char * source, size_t num );
size_t strlen ( const char * str );

using namespace std;

int main ()
{
	string s, s2;
	int count = 0;
	int last_call = 1;
	int size, l;
	int i;
	long long hash = 0;
	long long ch[26] = {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,5,6,6,6,7,7,7,7};
	char* buf = new char [20];
	cin >> s;
	size = atoi(s.c_str());
	map<long long,list<pair<pair<int,int>,string> >* >words;
	//list<pair<pair<int,int>,string> >* lp;
	map<long long,list<pair<pair<int,int>,string> >* >::iterator mIt;
	list<pair<pair<int,int>,string> >::iterator lIt;
	list<pair<pair<int,int>,string> >::iterator lIt2;
	pair<pair<int,int>,string>tmp_pair;
	while (count < size) {
		hash = 0;
		cin >> s;
		cin >> s2;
		l = int(s.size());
		strncpy(buf,s.c_str(),l);
		for (i = 0; i < int(l); i++) {
			hash *= 8;
			hash += ch[buf[i] - 'a'];
		}
		hash++;
		for (i = int(l); i < 20; i++)
			hash *= 8;
		if (words[hash]==NULL)
			words[hash] = new list<pair<pair<int,int>,string> >;
		words[hash][0].push_back(make_pair(make_pair(-atoi(s2.c_str()),0),s));
		count++;
	}
	cin.ignore(); // remove whitespace from input stream
	getline(cin,s);
	// sort words
	for (mIt = words.begin(); mIt != words.end(); ++mIt)
		mIt->second[0].sort();
	l = int(strlen(s.c_str()));
	buf = new char [l+1];
	strncpy(buf,s.c_str(),l);
	buf[l] = '\0';
	count = 0;
	int pos = 0;
	char signs[3] = {'.',',','?'};
	while (count < int(l)) {
		if (buf[count]>'1' && buf[count]<='9') {
			hash = 0;
			i = 0;
			while (buf[count]>'1' && buf[count]<='9') {
				hash *= 8;
				hash += (buf[count] - '2');
				count++;
				i++;
			}
			hash++;
			for (;i<20;i++)
				hash *= 8;
			//lp = words[hash];
			lIt = words[hash]->begin();
			i = 0;
			while (buf[count]=='*') {
				lIt++;
				count++;
				i++;
			}
			cout << lIt->second;
			lIt->first.first--;
			lIt->first.second = -last_call;
			// sort list
			lIt2 = lIt;
			while(i>0) {
				lIt2--;
				i--;
				if (lIt->first.first > lIt2->first.first) {
					lIt2++;
					if (lIt != lIt2) {	// replace
						tmp_pair.first.first = lIt->first.first;
						tmp_pair.first.second = lIt->first.second;
						tmp_pair.second = lIt->second;
						words[hash]->erase(lIt);
						words[hash]->insert(lIt2,tmp_pair);
					}
					break;
				}
				if (i==0) {
					tmp_pair.first.first = lIt->first.first;
					tmp_pair.first.second = lIt->first.second;
					tmp_pair.second = lIt->second;
					words[hash]->erase(lIt);
					words[hash]->insert(lIt2,tmp_pair);
				}
			}
			last_call++;
		}
		while (buf[count]=='1') {
			count++;
			i = 0;
			while (buf[count]=='*') {
				i++;
				count++;
			}
			cout << signs[i%3];
		}
		while(buf[count]==' ') {
			cout << ' ';
			count++;
		}
	}
	return 0;
}
