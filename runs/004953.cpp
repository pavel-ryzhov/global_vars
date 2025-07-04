#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include <stdio.h>

using namespace std;

string eng(int a){
	string b[9] = {".,?","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
	return b[--a];
}

string eng(char a){
	int tmp = atoi(&a);
	string b[9] = {".,?","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"}; 
	return b[--tmp];
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

char get_mark(string::iterator &it,string *query,string (*get_key) (int)){
	string tmp = (get_key(1));
	it++;
	int mark = 0;
	while(it!=query->end()){
		if(*it != '*') break; 
		mark++;
		it++;
	}
	return tmp[mark];
}

string get_word(set<element> *dictionary ,string::iterator &it,string *query, string (*get_key) (char)){
	static int iteration=0;
	string result,l_bound,u_bound,tmp;
	char tmp_;
	vector<element> words;
	vector<element>::iterator v_it;
	do {
		if(*it=='*' || *it=='1' || *it==' ') break;
		tmp = get_key(*it);
		l_bound+=(*tmp.begin());
		u_bound+=(*tmp.rbegin());
	} while( ++it!=query->end());
	words = search_words(dictionary,l_bound,u_bound);
	sort(words.begin(),words.end(),sort_by_weight);
	v_it = words.begin();
	if(it!=query->end()){
	do {
		if(*it!='*') break;
		v_it++;
	}while( ++it!=query->end());
	}
	element a = *v_it;
	a.weight++;
	a.iteration = iteration;
	dictionary->erase(*v_it);
	dictionary->insert(a);
	result+= a.word;
	iteration++;
	return result;
}

string process(set<element> *dictionary ,string query){
	string::iterator it = query.begin();
	string result="";
	while(it != query.end()){
		if(*it == ' '){ 
			result+=' ';
			it++;
			continue;
		}
		if(*it=='1'){
			result +=get_mark(it,&query,eng);
			continue;
		}
		result += get_word(dictionary,it,&query,eng);
	}
	return result;
}

int main(){
	set<element> dictionary;
	vector<string> query;
	int num,weight;
	string tmp,buf;
	string::iterator it;
	cin >> num;
	for (int i = 0; i<num;i++){
		cin >> tmp >> weight;
		dictionary.insert(element(tmp,weight));
	}
	getchar();
	getline(cin,tmp);
	cout << process(&dictionary,tmp);
	return 0;
}