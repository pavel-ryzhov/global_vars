#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

char * strncpy ( char * destination, const char * source, size_t num );
size_t strlen ( const char * str );

using namespace std;

int binary_find(long long hash, vector<pair<long long,string> >& hw)
{
	int n = int(hw.size());
	int i = -1;
	int tmp;
	while (n>0) {
		tmp = (n+1)/2;
		n -= tmp;
		if (hw[i+tmp].first < hash)
			i+=tmp;
	}
	return (i+1);
}

int binary_find_word(string str, vector<pair<string,pair<int, int> > >& words)
{
	int n = int(words.size());
	int i = -1;
	int tmp;
	while (n>0) {
		tmp = (n+1)/2;
		n -= tmp;
		if (words[i+tmp].first.compare(str) < 0)
			i+=tmp;
	}
	return (i+1);
}

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
	if (size > 50000)
		return 0;
	vector<pair<string,pair<int, int> > >ws(size);
	vector<pair<long long,string> >hwords(size);
	vector<pair<pair<int,int>,string> >pairs(size);
	while (count < size) {
		hash = 0;
		cin >> s;
		cin >> s2;
		ws[count].first = s;
		ws[count].second.first = atoi(s2.c_str());
		ws[count].second.second = 0;
		l = int(s.size());
		strncpy(buf,s.c_str(),l);
		for (i = 0; i < int(l); i++) {
			hash *= 8;
			hash += ch[buf[i] - 'a'];
		}
		hash++;
		for (i = int(l); i < 20; i++)
			hash *= 8;
		hwords[count].first = hash;
		hwords[count].second = s;
		count++;
	}
	cin.ignore(); // remove whitespace from input stream
	getline(cin,s);
	sort(hwords.begin(),hwords.end());
	int pos, wpos;
	size_t word_len;
	char signs[3] = {'.',',','?'};
	l = int(strlen(s.c_str()));
	buf = new char [l+1];
	strncpy(buf,s.c_str(),l);
	buf[l] = '\0';
	count = 0;
	while (count < int(l)) {
		if (buf[count]>'1' && buf[count]<='9') {
			hash = 0;
			i = 0;
			word_len = 0;
			while (buf[count]>'1' && buf[count]<='9') {
				hash *= 8;
				hash += (buf[count] - '2');
				i++;
				word_len++;
				count++;
			}
			hash++;
			for (;i<20;i++)
				hash *= 8;
			i = 0;
			pos = binary_find(hash,hwords);
			while (hwords[pos].first == hash) {
				if (strlen(hwords[pos].second.c_str()) == word_len) {
					pairs[i].second = hwords[pos].second;
					wpos = binary_find_word(hwords[pos].second,ws);
					pairs[i].first.first = -ws[wpos].second.first; // '-' to sort in reverse oder
					pairs[i].first.second = -ws[wpos].second.second;
					i++;
				}
				pos++;
				if(pos >= int(hwords.size()))
					break;						// out of range
			}
			sort(pairs.begin(),pairs.begin()+i);
			pos = 0;
			while (buf[count]=='*') {
				pos++;
				count++;
			}
			cout << pairs[pos].second;
			wpos = binary_find_word(pairs[pos].second,ws);
			ws[wpos].second.first++;
			ws[wpos].second.second = last_call;
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
