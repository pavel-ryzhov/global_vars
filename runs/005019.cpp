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

string make_key(char a){
	switch (a){
	case 'a':
	case 'b':
	case 'c':
		return "2";
	case 'd':
	case 'e':
	case 'f':
		return "3";
	case 'g':
	case 'h':
	case 'i':
		return "4";
	case 'j':
	case 'k':
	case 'l':
		return "5";
	case 'm':
	case 'n':
	case 'o':
		return "6";
	case 'p':
	case 'q':
	case 'r':
	case 's':
		return "7";
	case 't':
	case 'u':
	case 'v':
		return "8";
	case 'w':
	case 'x':
	case 'y':
	case 'z':
		return "9";
	}
	return NULL;
}

class element{ //Элемент словаря
public:
	string word; //Слово
	int weight; //Его "вес"
	int iteration;//В какой итерации использовалось в последний раз
	double key;//Как слово набирается
	element (string wo,int we){ //Основной конструктор
		word = wo;
		weight = we;
		iteration = 0;
		string tmp;
		for(string::iterator it = word.begin();it != word.end();++it){
			tmp += make_key(*it);
		}
		std::istringstream iss(tmp);
		iss >> key;
	}
	element (string mask){ //Конструктор для сравнения
		std::istringstream iss(mask);
		iss >> key;
	}
	void iterate(int a){
		iteration = a;
		weight++;
	}
};


ostream &operator <<(ostream &stream, element a){
	stream << a.word;
	return stream;
}

bool operator<(element a,element b){
	return a.key < b.key;
}

bool operator==(element a,element b){
	return a.word == b.word;
}

bool sort_by_weight(element a,element b){
	return a.weight!=b.weight ? a.weight>b.weight : a.iteration!=b.iteration ? a.iteration>b.iteration : a.word<b.word;
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

string get_word(multiset<element> *dictionary ,string::iterator &it,string *query, string (*get_key) (char)){
	static int iteration=0;
	string tmp;
	char tmp_;
	vector<element> words;
	multiset<element>::iterator l_bound,u_bound;
	vector<element>::iterator v_it;
	++iteration;
	do {
		if(*it=='*' || *it=='1' || *it==' ') break;
		tmp += *it;
	} while( ++it!=query->end());
	l_bound = dictionary->lower_bound(element(tmp));
	u_bound = dictionary->upper_bound(element(tmp));
	words.insert(words.begin(),l_bound,u_bound);
	sort(words.begin(),words.end(),sort_by_weight);
	v_it = words.begin();
	if(it!=query->end()){
	do {
		if(*it!='*') break;
		v_it++;
	}while( ++it!=query->end());
	}
	dictionary->erase(l_bound,u_bound);
	v_it->iterate(iteration);
	dictionary->insert(words.begin(),words.end());
	return v_it->word;
}

string process(multiset<element> *dictionary ,string query){
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
	multiset<element> dictionary;
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