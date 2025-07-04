#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Cell;
typedef map<string, Cell> dict; //определение типа dict

//-----КЛАСС СЛОВ-----
class Word { 
public:
	Word(string text, int frequency=0) {
		swap(text_,text); 
		frequency_=frequency;
	};
	ifstream& Write(ifstream& file); //заполнение полей слова из потока
	void Write(Word& w) { //заполнение полей слова из слова
		set_text(w.text());
		set_frequency(w.frequency());
	};

	int frequency() { return frequency_; };
	string text() { return text_; };

	void set_frequency(int f) { frequency_=f; };
	void set_text(string t) { swap(text_,t); }
private:
	string text_; //текстовое представление слова
	int frequency_; //частота употребления слова
};

//-----КЛАСС ЯЧЕЕК СЛОВАРЯ-----
class Cell {
public:
	void Add (Word w) {
		if (words.size()!=0) {
			vector<Word>::iterator iter;
			iter=words.begin();
			while ( (iter!=words.end()) && ((iter->frequency()) >= (w.frequency())) ) iter++;
			if (iter!=words.end()) words.insert(iter, w);
			else words.push_back(w);
		} else words.push_back(w);
	};
	string Paste(int shift=0) {
		Word temp( words.at( shift % words.size() ) );
		if ( (temp.text()!=(" ")) && (temp.text()!=".") && (temp.text()!=",") && (temp.text()!="?") ) {
			words.erase( words.begin() + (shift % words.size()) );
			temp.set_frequency( temp.frequency() + 1 );
			if (words.size()!=0) {
				vector<Word>::iterator iter;
				iter=words.begin();
				while ( (iter->frequency() > temp.frequency()) && (iter!=words.end())) iter++;
				if (iter!=words.end()) words.insert(iter, temp);
				else words.push_back(temp);
			} else words.push_back(temp); 
		};
		return temp.text();
	};
private:	
	vector<Word> words;
};


//-----СТРУКТУРА ДЛЯ ХРАНЕНИЯ ЗАПРОСОВ-----
struct Query {
	string code;
	int shift;
};

//-----ОБЪЯВЛЕНИЕ ФУНКЦИЙ-----
char DigitForSymbol(char c) { //определение "клавиши" для символа
	if ((c=='a') || (c=='b') || (c=='c')) return '2';
	else if ((c=='d') || (c=='e') || (c=='f')) return '3';
	else if ((c=='g') || (c=='h') || (c=='i')) return '4';
	else if ((c=='j') || (c=='k') || (c=='l')) return '5';
	else if ((c=='m') || (c=='n') || (c=='o')) return '6';
	else if ((c=='p') || (c=='q') || (c=='r') || (c=='s')) return '7';
	else if ((c=='t') || (c=='u') || (c=='v')) return '8';
	else return '9';
};

void ParseDictionary (dict& d, istream& in) { //анализ "словарной" части входного файла
	Word word(".");
	d["1"].Add(word);
	word=Word(",");
	d["1"].Add(word);
	word=Word("?");
	d["1"].Add(word);
	word=Word(" ");
	d["0"].Add(word);

	string str;
	in >> str;
	int imax=atoi(str.c_str());
	for (int i=0; i<imax; i++) {
		string text;
		string frequency;
		in >> text >> frequency;
		string code;
		for (int p=0; p<static_cast<int>(text.length()); p++)
			code+=DigitForSymbol(text[p]);
		d[code].Add(Word(text, atoi(frequency.c_str())));
	};
};

void ParseQuery (vector<Query>& vec_q, istream& in) { //анализ строк запросов к словарю
	string query;
	char trash;
	in.get(trash);
	getline(in, query, '\n');
	int i=0;
	while (i<static_cast<int>(query.length())) {
		string code;
		while ( (i<static_cast<int>(query.length())) && (query[i]!=' ') && (query[i]!='1') && (query[i]!='*') ) {
			code+=query[i];
			i++;
		}
		int shift=0;
		if ( (i<static_cast<int>(query.length())) && (query[i]=='1') ) {
			if (code!="") {
				Query q;
				swap(q.code,code);
				q.shift=shift;
				vec_q.push_back(q);
			}
			string temp("1");
			swap(temp,code);
			i++;
		}
		while ( (i<static_cast<int>(query.length())) && (query[i]=='*') ) {
			shift++;
			i++;
		}
		Query q;
		swap(q.code,code);
		q.shift=shift;
		vec_q.push_back(q);
		while ( (i<static_cast<int>(query.length())) && (query[i]==' ') ) {
			Query blanc;
			string temp("0");
			swap(blanc.code,temp);
			blanc.shift=0;
			vec_q.push_back(blanc);
			if (i!=(static_cast<int>(query.length())-1)) i++;
		}
	}
};

void DoQueries (dict d, vector<Query>& q, ostream& out) { //выполнение поступивших от пользователя запросов
	vector<Query>::iterator i;
	string temp;
	for (i=q.begin(); i!=q.end(); i++) {
		string code(i->code);
		int shift=i->shift;
		string temp(d[code].Paste(shift));
		out << temp;
	};
};

//-----РАБОЧАЯ ЧАСТЬ-----
int main() {
	dict t9;
	vector<Query> queries;

	ParseDictionary(t9, cin);
	ParseQuery(queries, cin);
	DoQueries(t9, queries, cout);

	return 0;
};