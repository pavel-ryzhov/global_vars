#include <iostream>
//#include <conio.h>

#include <set>
#include <algorithm>

#include <string>

#include <ctime>
#include <cstring>

using namespace std;

//#include "t9.h"

/////////////////////////// t9.h - start: ///////////////////
#ifndef _T9__H_
#define _T9__H_

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

class word;

class wordWithCode {
public:
	wordWithCode(string code0) : code(code0) {} ;
	bool operator() (const word &w);
private:
	string code;
};

class word {
public:
	word(string code0, string text0, int weight0) : code(code0), text(text0), weight(weight0), index(word::num) {};
	friend bool operator<(word w1, word w2);
	friend ostream &operator<<(ostream &stream, word w);
	friend bool wordWithCode::operator()(const word &w);
	static bool convertChars(char *inp, char *out);
	inline bool checkCode(char *check) { return !strcmp(code.c_str(),check); };
	inline const char* getText() { return text.c_str(); };
	inline void useIt(set< word >::iterator &i) {
		cout << this->text;
		//cout << text;
		if (code[0]!='1') {
			word::num++;
			word::words.insert(word(this->code,this->text,this->weight+1));
			word::words.erase(i);
		}
		return;
	};
	static set< word > words;
	string code;
	string text;
	int weight;
	static int num;
private:
	int index;
};



#endif
/////////////////////////// t9.h - end //////////////////////

/////////////////////////// t9.cpp - start: /////////////////

//#include "t9.h"

bool operator<(word w1, word w2) {
	if (w1.code == w2.code) {
		if (w1.weight == w2.weight) {
			if (w1.index == w2.index) {
				if (w1.text == w2.text) {
					// ���! ����� ��������� ��������.
					return 0;
				} else return (w1.text < w2.text);	// ���������� �� ������ - �� ��������
			} else return (w1.index > w2.index);	// ���������� �� "���������� ������������" - �� ��������
		} else return (w1.weight > w2.weight);		// ���������� �� ������� ������������ (��� ���� � ���������� ��������������) - �� ��������
	} else return (w1.code < w2.code);				// ���������� �� ��������� ���� - �� ��������
}

ostream &operator<<(ostream &stream, word w)
{
	stream << w.code << ": " << w.text << " [" << w.weight << "] " << w.index << endl;
	return stream;
}

bool word::convertChars(char *inp, char *out) {
	int i = -1;
	while (inp[++i]) {
		if (inp[i] < 97) return 0;
		if (inp[i] < 100) { out[i] = '2'; continue; }
		if (inp[i] < 103) { out[i] = '3'; continue; }
		if (inp[i] < 106) { out[i] = '4'; continue; }
		if (inp[i] < 109) { out[i] = '5'; continue; }
		if (inp[i] < 112) { out[i] = '6'; continue; }
		if (inp[i] < 116) { out[i] = '7'; continue; }
		if (inp[i] < 119) { out[i] = '8'; continue; }
		if (inp[i] < 123) { out[i] = '9'; continue; }
		return 0;
	}
	out[i] = 0;
	return 1;
}

int word::num = 0;
set< word > word::words;

bool wordWithCode::operator()(const word &w) {
	return (w.code == code);
};

/////////////////////////// t9.cpp - end ////////////////////

int main() {
/*
int x;
	char c1;
	c1 = cin.get();
	//scanf("%c",&c1);

	x = 0;
	c1 = cin.get();
	//scanf("%c",&c1);
	x = 1;
	c1 = cin.get();
	//scanf("%",&c1);
	x = 2;

	return 0;
*/
/*
	char c1;
	scanf("%1c",&c1);
	cout << "char = " << (int)c1;
	cout << "yo!";
	return 0;
*/
/*
	// ��� ����������� ��������
	_getch();
	clock_t ct1 = clock();
*/
	// ������ ����� ��� ������ ����������. �� ������� �� ����� ����������.
	word::words.insert(word("1",".",2));
	word::words.insert(word("1",",",1));
	word::words.insert(word("1","?",0));

	int n,weight;
	char *text = new char[21];
	char *code = new char[21];

	cin >> n;

	for (int i=0; i<n; i++) {
		//scanf("%20s %d",text,&weight);
		cin >> text >> weight;
		if (!word::convertChars(text,code)) cout << "> Error converting word! (" << text << ")" << endl;
			else word::words.insert(word(code,text,weight));
	}

	// ����, ������� �����, ������ ���������� � ����������.

	char c;

	//scanf("%1c",&c);
	c = cin.get();
	int i = 0;
	i = 0;
	set< word >::iterator w;
	//char inp[100000];
	//int inpn = 0;
	//scanf("%100000s",&inp);
	do {

		//c = _getch();
		//scanf("%1c",&c);
		//c = (int)inp[inpn++];
		c = cin.get();

		if (c<58 && c>49) { // ����� �� 2 �� 9 - ����� �� ������ �����
			// ����� ��� ����������, ��� �� ��� ��� ������ ������� ���� ����������.
			if (code[0] == '1') {
				//(*w).useIt(w);
				// useIt:		
					cout << w->text;
					if (w->code[0]!='1') {
						word::num++;
						word::words.insert(word(w->code,w->text,w->weight+1));
						word::words.erase(w);
					}
				// used...

				i = 0;
			}
			code[i++] = c;
		} else {			// ���� ��� �� ����� - ������, ����������� ������
			if (i>0) { // ���� ����� �� ������...
				code[i] = 0;		// �������� ���� �����
				w = find_if(word::words.begin(), word::words.end(), wordWithCode(code));		// ���������� ��������, ����������� �� ������ ���������� ����� � �������
				if (w == word::words.end()) cout << "> Word not found! [" << code << "]";	// ���� �� ������ ������ ����� �� ������� - ���-�� ����� �� ���
			}
			// ����������� �������� ���: ������ (32), 1 (49) � * (42)
			// (��� ���� ������ �������� ������ 13, ������� ����������� ����)
			switch (c) {
				case 32:	// ������ � �������. ��������, ������� ������ ������� ������� ����� + ��� ������.
					//if (i) (*w).useIt(w);	// ����� �� ��������? ������� ���.
					// useIt:		
						cout << w->text;
						if (w->code[0]!='1') {
							word::num++;
							word::words.insert(word(w->code,w->text,w->weight+1));
							word::words.erase(w);
						}
					// used...

					cout << " " ;
					code[0] = 0;
					i = 0;	// �������, ��� ����� ��������.
					break;
				case 49:	// ��� �������. ��� ���� ������� ������� ����� (���� ��� ����, i!=0),
							//  ����� ������� "������� ������" ���� ����������.
					if (i) {		// ���� ����� �� ���� �������� (������� ������ ����� ����� �������� ���� ��� ����� ���������)
									//	���������� ������� ����� (���� ������� ������ ����� ������� - i==0, ��� ��� ��������).
						//(*w).useIt(w);
						// useIt:		
							cout << w->text;
							if (w->code[0]!='1') {
								word::num++;
								word::words.insert(word(w->code,w->text,w->weight+1));
								word::words.erase(w);
							}
						// used...

					}

					// ������� ���, ��� �� ������ ����� �������.
					w = word::words.begin();
					code[0] = '1';
					code[1] = 0;
					i = 2;	// ����� �������.
					break;
				case 42:	// ��� ���������. �� ������ - ������������ ����� �� �������.
					w++;
					//if (w == word::words.end() || !(*w).checkCode(code)) { // ���������� ����� ��������� - ���� ��������� � �������.
					if (w == word::words.end() || strcmp(w->code.c_str(),code)) { // ���������� ����� ��������� - ���� ��������� � �������.
						w = find_if(word::words.begin(), word::words.end(), wordWithCode(code));
						if (w == word::words.end()) cout << "> Word not found! [" << code << "]";	// ������ �� �����
					}
					i = -1;	// �����, � ��������, ������ (��������� ����������, code ��������).
					break;
				case 10: case 13:
				default:
					// ���� ��������. ��� ���� ���� ������� �����, ���� ��� ����.
					//if (i) (*w).useIt(w);
					if (i) {
						// useIt:		
							cout << w->text;
							if (w->code[0]!='1') {
								word::num++;
								word::words.insert(word(w->code,w->text,w->weight+1));
								word::words.erase(w);
							}
						// used...
					}
			}
		}
	} while (c != 10 && c != 13);


/*
	// ��� ����������� ��������
	cout << endl << endl << endl << "--------------------------" << endl << "Performance:" << endl;
	clock_t ct2 = clock();
	cout << "Clocks per second: " << CLOCKS_PER_SEC << endl;
	cout << "Execute clocks: " << (ct2-ct1) << endl;
	cout << "Execute time: " << (double)(ct2-ct1)/CLOCKS_PER_SEC << " sec." << endl;
	_getch();
*/
	return 0;
}