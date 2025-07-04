#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

string eng(char a){
	string b;
	switch (a){
	case '1':
		b=".,?";
		return b;
	case '2':
		b="abc";
		return b;
	case '3':
		b="def";
		return b;
	case '4':
		b="ghi";
		return b;
	case '5':
		b="jkl";
		return b;
	case '6':
		b="mno";
		return b;
	case '7':
		b="pqrs";
		return b;
	case '8':
		b="tuv";
		return b;
	case '9':
		b="wxyz";
		return b;
	}
	return NULL;
}

class element{ //Элемент словаря
public:
	string word; //Слово
	int weight; //Его "вес"
	int iteration;//В какой итерации использовалось в последний раз
	element (string wo,int we){ //Основной конструктор
	word = wo;
	weight = we;
	iteration = 0;
	}
	element (string wo){ //Конструктор для сравнения
	word = wo;
	weight = NULL;
	}
};



ostream &operator <<(ostream &stream, element a){
	stream << a.word;
	return stream;
}

bool operator<(element a,element b){
	if(a.word.length() == b.word.length()) return a.word < b.word;
	return a.word.length() < b.word.length();
}

bool sort_by_weight(element a,element b){
	if(a.weight!=b.weight) return a.weight>b.weight;
	return a.iteration>b.iteration;
}

char get_mark(string::iterator it,string *query,string (*get_key) (char)){
	string tmp = (get_key('1'));
	int mark = 0;
	while(it!=query->end()){
		if(*it == '1') tmp=get_key('1');
		if(*it == '*') mark++;
		it++;
	}
	return tmp[mark];
}

string get_word(set<element> *dictionary ,string *query, string (*get_key) (char)){
	static int iteration=0;
	string result,l_bound,u_bound,tmp;
	string::iterator it;
	vector<element> words;
	vector<element>::iterator v_it;
	set<element>::iterator l_bound_it,u_bound_it;
	for (it = query->begin(); it!=query->end();++it){
		if(*it=='*' || *it=='1') break;
		tmp = get_key(*it);
		l_bound+=(*tmp.begin());
		u_bound+=(*tmp.rbegin());
	}
	l_bound_it = dictionary->lower_bound(l_bound);
	u_bound_it = dictionary->upper_bound(u_bound);
	words.insert(words.begin(),l_bound_it,u_bound_it);
	sort(words.begin(),words.end(),sort_by_weight);
	v_it = words.begin();
	while(it!=query->end()){
		if(*it == '1') break;
		if(*it == '*') ++v_it;
		it++;
	}
	element a = *v_it;
	a.weight++;
	a.iteration = iteration;
	dictionary->erase(*v_it);
	dictionary->insert(a);
	result+= a.word;
	if(it!=query->end()) result+=get_mark(it,query,get_key);
	iteration++;
	return result;
}

string process(set<element> *dictionary ,vector<string> query){
	vector<string>::iterator it;
	string result;
	for(it = query.begin();it != query.end(); ++it){
	 result += get_word(dictionary, &*it, eng);
	 if(it+1 != query.end()) result += ' ';
	}
	return result;
}

int main(){
	set<element> dictionary;
	vector<string> query;
	int num,weight;
	string tmp,buf;
	cin >> num;
	for (int i = 0; i<num;i++){
		cin >> tmp >> weight;
		dictionary.insert(element(tmp,weight));
	}
	getchar();
	getline(cin,tmp);
	istringstream ist(tmp);
	while ( ist >> buf ) query.push_back(buf);
	vector<string>::iterator it;
	cout << process(&dictionary,query);
	return 0;
}