#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <vector>
#include <valarray>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Cell;
typedef map<int, Cell> dict; //определение типа dict

//-----КЛАСС СЛОВ-----
class Word { 
public:
	Word(char text[20], int frequency=0) {
		strncpy(text_, text, 20); frequency_=frequency;
	};
	ifstream& Write(ifstream& file); //заполнение полей слова из потока
	void Write(Word& w) { //заполнение полей слова из слова
		set_text(w.text());
		set_frequency(w.frequency());
	};

	int frequency() { return frequency_; };
	char* text() { return text_; };

	void set_frequency(int f) { frequency_=f; };
	void set_text(char t[20]) { strncpy(text_, t, 20); }
private:
	char text_[20]; //текстовое представление слова
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
	char* Paste(int shift=0) {
		Word temp( words.at( shift % words.size() ) );
		if ( (strcmp(temp.text()," ")) && (strcmp(temp.text(),".")) && (strcmp(temp.text(),",")) && (strcmp(temp.text(),"?")) ) {
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
	int code;
	int shift;
};

//-----ОБЪЯВЛЕНИЕ ФУНКЦИЙ-----
int DigitForSymbol(char c) { //определение "клавиши" для символа
	if ((c=='a') || (c=='b') || (c=='c')) return 2;
	else if ((c=='d') || (c=='e') || (c=='f')) return 3;
	else if ((c=='g') || (c=='h') || (c=='i')) return 4;
	else if ((c=='j') || (c=='k') || (c=='l')) return 5;
	else if ((c=='m') || (c=='n') || (c=='o')) return 6;
	else if ((c=='p') || (c=='q') || (c=='r') || (c=='s')) return 7;
	else if ((c=='t') || (c=='u') || (c=='v')) return 8;
	else return 9;
};

void ParseDictionary (dict& d, istream& in) { //анализ "словарной" части входного файла
	Word word(static_cast<char*>("."));
	d[1].Add(word);
	word=Word(static_cast<char*>(","));
	d[1].Add(word);
	word=Word(static_cast<char*>("?"));
	d[1].Add(word);
	word=Word(static_cast<char*>(" "));
	d[0].Add(word);

	char str[5];
	in >> str;
	int imax=atoi(str);
	for (int i=0; i<imax; i++) {
		char text[20];
		char frequency[4];
		in >> text >> frequency;
		int code=0, size=0;
		while (text[size]!='\0') size++;
		for (int p=0; p<size; p++)
			code+=DigitForSymbol(text[p])*static_cast<int>(pow((double)10,size-p-1));
		d[code].Add(Word(text, atoi(frequency)));
	};
};

void ParseQuery (dict& d, istream& in, vector<Query>& vec_q) { //анализ строк запросов к словарю
	char query[100000];
	char trash;
	in.get(trash);
	in.getline(query, 100000, '\0');
	int i=0, query_size=0;
	while (query[query_size]!=0) query_size++;
	while (i<query_size) {
		char code[20];
		int shift=0, pos=0;
		while ( (i<query_size) && (query[i]!=' ') && (query[i]!='1') && (query[i]!='*') ) {
			code[pos]=query[i];
			code[pos+1]='\0';
			pos++;
			i++;
		}
		if ( (i<query_size) && (query[i]=='1') ) {
			if (strcmp(code,"")) {
				Query q = { atoi(code), 0 };
				vec_q.push_back(q);
			}
			code[0]='1';
			code[1]='\0';
			i++;
		}
		while ( (i<query_size) && (query[i]=='*') ) {
			shift++;
			i++;
		}
		Query q = { atoi(code), shift };
		vec_q.push_back(q);
		while ( (i<query_size) && (query[i]==' ') ) {
			Query blanc= { 0, 0 };
			vec_q.push_back(blanc);
			if (i!=(query_size-1)) i++;
		}
		code[0]='\0';
	}
};

void DoQueries (dict d, vector<Query>& q, ostream& out) { //выполнение поступивших от пользователя запросов
	vector<Query>::iterator i;
	char temp[20];
	for (i=q.begin(); i!=q.end(); i++) {
		int code=i->code;
		int shift=i->shift;
		strncpy(temp, d[code].Paste(shift), 20);
		out << temp;
	};
};

//-----РАБОЧАЯ ЧАСТЬ-----
int main() {
	dict t9;
	vector<Query> queries;
	ifstream input_file("C.in");
	ofstream output_file("C.out", ios::out);
	if (!input_file) return 0;

	ParseDictionary(t9, input_file);
	ParseQuery(t9, input_file, queries);
	DoQueries(t9, queries, output_file);

	input_file.close();
	output_file.close();

	return 1;
};