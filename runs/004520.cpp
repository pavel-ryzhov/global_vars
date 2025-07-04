/*
 * t9.cpp
 *
 *  Created on: 01.03.2011
 *      Author: cymkuh
 */

#include <iostream>
#include <list>
#include <string>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::list;
using std::map;

typedef unsigned int uint;

// A String List class
// Consists only a list with words ordered by last use or alphabetically.
// Last used (a-endian) are on front.
typedef list <string> TStringList;

// A String Versions class.
// It implemented as map Frequency -> StringList.
// Ordered by frequency - for searching from the highest
class TStringVersion : public map <uint, TStringList* > {
public:
	// Add a new word
	void add(string str, uint freq) {
		TStringList *strlist = find(freq)->second;
		if (strlist == end()->second) { //create new string list for this frequency if doesn't exists
			strlist = new TStringList();
			(*this)[freq] = strlist;
		}
		strlist->push_back(str);
	}

	// Get a word and increase its frequency
	string get(uint ver) {
		// select TStringList where to look (order by frequency)
		TStringVersion::reverse_iterator cur = rbegin();
		while (ver >= cur->second->size()) {
			ver-= cur->second->size();
			cur++;
		}

		// look in TStringList (order by last use or alphabetically)
		TStringList::iterator listIt = cur->second->begin();
		while (ver != 0) {
			ver--;
			listIt++;
		}

		// add +1 to frequency
		// remove from old TStringList
		string result = (*listIt);
		cur->second->erase(listIt);

		// and add to new one
		uint newFreq = cur->first + 1;
		TStringList *strlist = find(newFreq)->second;
		if (strlist == end()->second) {// create new if not consists
			strlist = new TStringList();
			(*this)[newFreq] = strlist;
		}
		strlist->push_front(result);

		return result;
	}

	// construct with the first word
	TStringVersion(string str, uint freq) {
		add(str, freq);
	}

	~TStringVersion() {
		for(TStringVersion::iterator i = begin(); i != end(); i++)
			delete (*i).second;
	}
};

// A dictionary class.
// It implemented as map NumString -> StringVersions
// Ordered by NumString for looking up like on hash.
class TDictionary : public map <string, TStringVersion* > {
private:
	// convert symbol to T9 number
	char toT9 (char from) {
		switch (from) {
		case 'a':
		case 'b':
		case 'c':
			return '2';
		case 'd':
		case 'e':
		case 'f':
			return '3';
		case 'g':
		case 'h':
		case 'i':
			return '4';
		case 'j':
		case 'k':
		case 'l':
			return '5';
		case 'm':
		case 'n':
		case 'o':
			return '6';
		case 'p':
		case 'q':
		case 'r':
		case 's':
			return '7';
		case 't':
		case 'u':
		case 'v':
			return '8';
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			return '9';
		}
		return 0;
	}

	// convert string to T9 string
	string stringToT9(string str) {
		string nstr;
		for (string::iterator c = str.begin(); c != str.end(); c++)
			nstr+= toT9(*c);
		return nstr;
	}

public:
	// add a word
	void add(string str, uint freq) {
		string nstr = stringToT9(str);
		TStringVersion *ver = find(nstr)->second;
		if (ver == end()->second) {
			ver = new TStringVersion(str, freq);
			(*this)[nstr] = ver;
		}
		else
			ver->add(str, freq);
	}

	// get a word and increase its frequency
	string get(string nstr, uint ver) {
		return find(nstr)->second->get(ver);
	}

	void build() {
		uint N; // word count
		cin >> N;
		string str; // string red
		uint freq; // frequency red
		for (uint i = 0; i < N; i++) {
			cin >> str >> freq;
			add(str, freq);
		}
	}

	~TDictionary() {
		for(TDictionary::iterator i = begin(); i != end(); i++)
			delete (*i).second;
	}
};

// A SMS string class.
// Is implemented as string with public parse() method.
// parse() gets symbols from string, looks for finished words and calls TDictionary::get for each word
// Besides parse() calls getSymbol for each found symbol sequence
class TSms : public string {
private:
	uint version;
	string word;
	TDictionary* dictionary;
	bool symbol;

	// for '1' digit - returns '.,?'[ver]
	char getSymbol (uint ver) {
		switch (ver) {
		case 0:
			return '.';
			break;
		case 1:
			return ',';
			break;
		case 2:
			return '?';
			break;
		}
		return 0;
	}

	// print parsed word
	void printWord() {
		// print a symbol
		if (symbol) {
			cout << getSymbol(version);
			symbol = false;
			version = 0;
		}

		// get word from dictionary
		else if (!(word.empty())) {
			cout << dictionary->get(word, version);
			word.clear();
			version = 0;
		}
	}

public:
	// zero init
	TSms() {
		version = 0;
		word.clear();
		symbol = false;
	}

	// read line from cin
	void read() {
		std::getline(cin, (*this));
	}

	// parse cycle, see top
	void parse(TDictionary *dict) {
		dictionary = dict;
		for (string::iterator c = begin(); c != end(); c++)
			switch (*c) {
			case '*':
				version++;
				break;
			case ' ':
				printWord();
				cout << " ";
				break;
			case '1':
				printWord();
				symbol = true;
				break;
			default:
				if (symbol)
					printWord();
				word += (*c);
				break;
			}
		printWord(); // for EOL
		cout << endl; // EOL
	}
};

int main (void) {
	TDictionary dict;
	dict.build();
	cin.get(); // skip EOL before getline()
	TSms sms;
	sms.read();
	sms.parse(&dict);
	return 0;
}
