#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <utility>
#include <algorithm>

using namespace std;

string Convertintonumb(const string &s) {
	string res("");
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == 'a' || s[i] == 'b' || s[i] == 'c') res += '2';
		else if (s[i] == 'd' || s[i] == 'e' || s[i] == 'f') res += '3';
		else if (s[i] == 'g' || s[i] == 'h' || s[i] == 'i') res += '4';
		else if (s[i] == 'j' || s[i] == 'k' || s[i] == 'l') res += '5';
		else if (s[i] == 'm' || s[i] == 'n' || s[i] == 'o') res += '6';
		else if (s[i] == 'p' || s[i] == 'q' || s[i] == 'r' || s[i] == 's') res += '7';
		else if (s[i] == 't' || s[i] == 'u' || s[i] == 'v') res += '8';
		else if (s[i] == 'w' || s[i] == 'x' || s[i] == 'y' || s[i] == 'z') res += '9';
	}	
	return res;
}

void Read(map <string, vector <pair <string, int> > > &dict, string &message) {
	int n, f;
	//scanf("%d", &n);
	//char s[21];
	cin >> n;
	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		cin >> f;
		dict[Convertintonumb(s)].push_back(make_pair(s, f));
	}
	cin >> s;
	getline(cin, message);
	message = s+message;
}

bool cmp(const pair <string, int> &a, const pair <string, int> &b) {
	if (a.second > b.second) return true;
	else if (a.second < b.second) return false;
	return (a.first < b.first);
}

void start(map <string, vector <pair <string, int> > > &dict, const string &message, string &result) {
	map <string, list <pair <string, int> > > m;
	for (map <string, vector <pair <string, int> > >::iterator i = dict.begin(); i != dict.end(); i++) {
		vector <pair <string, int> > t = i->second;
		sort(t.begin(), t.end(), cmp);
		for (int j = 0; j < t.size(); j++) {
			m[i->first].push_back(t[j]);
		}			
	}

	int cnt = 0;
	while (cnt < message.length()) {
		string word("");
		while ('2' <= message[cnt] && message[cnt] <= '9' && cnt < message.length()) {
			word += message[cnt];
			cnt++;
		}
		if (word != "") {
			list <pair <string, int> >::iterator iter = m[word].begin();
			while (message[cnt] == '*') {
				iter++;
				cnt++;
			}
			pair <string, int> tt;
			tt.first = (*iter).first;
			tt.second = (*iter).second +1;
			m[word].erase(iter);
			list <pair <string, int> >::iterator it = m[word].end();
			it--;
			if ((*it).second > tt.second) m[word].push_back(tt);
			else { 
				it = m[word].begin();
				while (tt.second < (*it).second) it++;
				m[word].insert(it, tt); 
			}
			result += tt.first;
		}
		//cout << cnt << endl;
		if (message[cnt] == '1') {
			cnt++;
			int stars = 0;
			while (message[cnt] == '*') {
				cnt++;
				stars++;
			}
			if (stars == 0) result += '.';
			else if (stars == 1) result += ',';
			else if (stars == 2) result += '?'; 
		}	
		while (message[cnt] == ' ') {
			cnt++;
			result += ' ';
		}
	}
}

int main() {
	map <string, vector <pair <string, int> > > dict;
	string message;
	Read(dict, message);

	string result("");
	start(dict, message, result);
	
	cout << result << endl;	
		
	return 0;
}
