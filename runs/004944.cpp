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
		return ".,?";
	case '2':
		return "abc";
	case '3':
		return "def";
	case '4':
		return "ghi";
	case '5':
		return "jkl";
	case '6':
		return "mno";
	case '7':
		return "pqrs";
	case '8':
		return "tuv";
	case '9':
		return "wxyz";
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
	return a.word.length() == b.word.length() ? a.word < b.word :  a.word.length() < b.word.length();
}

bool sort_by_weight(element a,element b){
	return a.weight!=b.weight ? a.weight>b.weight : a.iteration>b.iteration;
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

bool l_comparator(string a,string mask){
	for (int i =0; i != a.length();++i){
	if(a[i] < mask[i]) return false;
	}
	return true;
}

bool u_comparator(string a,string mask){
	for (int i =0; i != a.length();++i){
		if(a[i] > mask[i]) return false;
	}
	return true;
}

vector<element> search_words(set<element> *dictionary, string b_mask, string e_mask){
	vector<element> result;
	for(set<element>::iterator it=dictionary->begin();it!=dictionary->end();++it){
		if (it->word.length() == b_mask.length()){
			if(l_comparator(it->word,b_mask) && u_comparator(it->word,e_mask)) result.push_back(*it);
		}
	}
	return result;
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
/*	l_bound_it = dictionary->lower_bound(element(l_bound));
	u_bound_it = dictionary->upper_bound(element(u_bound));
	words.insert(words.begin(),l_bound_it,u_bound_it);*/
	words = search_words(dictionary,l_bound,u_bound);
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