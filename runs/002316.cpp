#include  <iostream>
#include <stdio.h>
#include  <iterator>
#include  <vector>
#include  <map>
#include  <string>

using namespace std;

vector  <char> signs;
int convert (char c){
	if (c  < 115) return ((c-97)/3)+2;
	if (c  < 121) return ((c-113)/3)+7;
	else return 9;
}

string convert (string word){
	string out = "";
	for (int index = 0; index  < word.length(); index++){
		char temp = convert(word[index])+48;
		//cout  < < temp  < < '\n';
		out += temp;
	}
	return out;
}

void insert (map  <string,map <int,vector <string> > > &words, string &numbers, int freq, string word, bool flagBack){
	//cout  < < numbers  < < '\n';
	map  <string,map <int,vector <string> > >::iterator it = words.find(numbers);
	if (it == words.end()){
		map <int,vector <string> > temp;
		vector <string> tempwords;
		tempwords.push_back(word);
		temp.insert(make_pair(freq,tempwords));
		words.insert (make_pair(numbers,temp));
	} else {
		bool flag = true;
		for (map <int,vector <string> >::iterator iter(it->second.begin()); iter!=it->second.end();iter++){
			if (iter->first == freq) {
				if (flagBack) 
					iter->second.push_back(word);
				else
					iter->second.insert(iter->second.begin(), word);
				flag = false;
			}
			if (flag) {
				vector <string> temp;
				temp.push_back(word);
				it->second.insert(make_pair(freq,temp));
			}
		}
	}
}

void input(map  <string,map <int,vector <string> > > &words, string &request){
	int word_count;
	cin >> word_count;
	for (int index = 0; index  < word_count; index++){
		string word;
		cin >> word;
		int freq;
		cin >> freq;
		freq*=-1;
		string numbers = convert (word);
		insert (words, numbers, freq, word,true);
	}
	getchar();
	getline(cin,request);
}

void numbers2word (map  <string,map <int,vector <string> > > &words, string &out, int numStars, int numStars1, string &numbers, bool one, string sign){
	map <int,vector  <string> > * freqWord = &words.find(numbers)->second;

	map <int,vector  <string> >::iterator it = freqWord->begin();
	vector <string>::iterator iter= it->second.begin();
	string word;
	int freq;
	for (;; iter++){
		if (iter == it->second.end()){
			if (it == freqWord->end())
				it = freqWord->begin();
			else it++;
			iter = it->second.begin();
		} 
		if (numStars == 0){
			word = *iter;
			freq = it->first;
			freq -= 1;	
			out+=word;
			it->second.erase(iter);
			insert (words, numbers, freq, word,false);
			break;
		} 
		numStars--;
	}
	if (one) out+=sign;
}

string T9 (map  <string,map <int,vector <string> > > &words, string &request){
	string out;
	string numbers;
	string sign;
	int numStars = 0; 
	bool one = false;
	int numStars1 = 0;
	for (string::iterator it = request.begin(); it!= request.end(); it++){
		if (*it == ' ') {
			if (numbers != "") { 
				sign+= signs[numStars1%3];
				numbers2word (words, out, numStars, numStars1, numbers, one, sign);
				out += " ";
			}
			numStars = 0;
			one = false;
			numStars1 = 0;
			numbers = "";
			sign = "";
		} else if (*it == '1') {
			if (one) {
				sign+= signs[numStars1%3];
				numStars1 = 0;
			} else 
				one = true;
		} else if (*it == '*') {
			if (one) numStars1++;
			else numStars++;
		} else if (*it > 49 && *it  < 58) numbers += *it;
	}
	if (one) sign+= signs[numStars1%3];
	numbers2word (words, out, numStars, numStars1, numbers, one, sign);
	return out;
}

int main(int argc, char* argv[])
{
	signs.push_back('.');
	signs.push_back(',');
	signs.push_back('?');
	map  <string,map <int,vector <string> > > words;
	string request;
	input(words,request);
	cout << T9(words, request);
	cin >> argc;
	return 0;
}

