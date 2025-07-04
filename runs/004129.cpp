#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>

using std::vector;
using std::map;
using std::set;
using std::pair;
using std::string;
using std::cin;
using std::cout;

map<char, char> GetCharCodesTable()
{
	map<char, char> char_codes;
	char_codes['a'] = '2';
	char_codes['b'] = '2';
	char_codes['c'] = '2';
	char_codes['d'] = '3';
	char_codes['e'] = '3';
	char_codes['f'] = '3';
	char_codes['g'] = '4';
	char_codes['h'] = '4';
	char_codes['i'] = '4';
	char_codes['j'] = '5';
	char_codes['k'] = '5';
	char_codes['l'] = '5';
	char_codes['m'] = '6';
	char_codes['n'] = '6';
	char_codes['o'] = '6';
	char_codes['p'] = '7';
	char_codes['q'] = '7';
	char_codes['r'] = '7';
	char_codes['s'] = '7';
	char_codes['t'] = '8';
	char_codes['u'] = '8';
	char_codes['v'] = '8';
	char_codes['w'] = '9';
	char_codes['x'] = '9';
	char_codes['y'] = '9';
	char_codes['z'] = '9';
	return char_codes;
}

const map<char, char> ALPHABET = GetCharCodesTable();

string GetT9Code(const string& str)
{
	string code = str;
	for(int i = 0; i < code.size(); ++i) {
		code[i] = ALPHABET.find(code[i])->second;
	}
	return code;
}

struct Word {
	string word;
	int frequency;
	int last_update;

	Word(const string& word, int freq, int last_upd = 0);
	bool operator < (const Word& right) const;
};

Word::Word(const string& str, int freq, int last_upd) {
	last_update = last_upd;
	word = str;
	frequency = freq;
}

bool Word::operator < (const Word& right) const {
	if (frequency > right.frequency) {
		return true;
	} else if (frequency == right.frequency) {
		if (last_update > right.last_update) {
			return true;
		} else if (last_update == right.last_update) {
			return (word.compare(right.word) < 0);
		} else {
			return false;
		}
	} else {
		return false;
	}
}

class WordBase {
	map<string, set<Word> > Map;
	void Add(const Word& word);
public:
	void Print();
	WordBase(const vector<Word>& dictionary);
	string GetWord(const string& code, int shift, int step);
};

WordBase::WordBase(const vector<Word>& dictionary) {
	for (int i = 0; i < dictionary.size(); ++i) {
		Add(dictionary[i]);
	}
}

void WordBase::Add(const Word& word) {
	string code = GetT9Code(word.word);
	map<string, set<Word> >::iterator it;
	it = Map.find(code);
	if (it != Map.end()) {
		it->second.insert(word);
	} else {
		set<Word> current;
		current.insert(word);
		Map[code] = current;
	}
}

string WordBase::GetWord(const string& code, int shift, int step) {
	map<string, set<Word> >::iterator it;
	it = Map.find(code);
	set<Word>::iterator set_it = it->second.begin();
	for (int i = 0; i < shift; ++i) {
		++set_it;
	}
	Word current_word = *set_it;
	it->second.erase(set_it);
	++current_word.frequency;
	current_word.last_update = step;
	it->second.insert(current_word);
	return current_word.word;
}

Word ReadWord() {
	string current_string;
	int frequency;
	cin >> current_string;
	cin >> frequency;
	Word current_word(current_string, frequency);
	return current_word;
}

vector<Word> ReadDictionary() {
	int length;
	cin >> length;
	vector<Word> dictionary;
	for (int i = 0; i < length; ++i) {
		dictionary.push_back(ReadWord());
	}
	// to read '\n' symbol
	string none;
	getline(cin, none);
	return dictionary;
}

string ReadT9Code() {
	string T9;
	getline(cin, T9);
	return T9;
}

vector<string> LabelOnes(string code) {
	vector<string> output;
	size_t found;
	found = code.find('1');
	while (found != string::npos) {
		if (found != 0) {
			string current(code.begin(), code.begin() + found);
			output.push_back(current);
			code.erase(code.begin(), code.begin() + found);
			found = code.find('1');
		} else {
			found = code.find_first_not_of("1* ");
			if (found != string::npos) {
				string current(code.begin(), code.begin() + found);
				code.erase(code.begin(), code.begin() + found);
				output.push_back(current);
				found = string::npos;
			}
		}
	}
	output.push_back(code);
	return output;
}

vector<pair<string, int> > LabelSpaces(string code) {
	vector<pair<string, int> > output;
	size_t found;
	found = code.find(' ');
	while (found != string::npos) {
		int spaces;
		string current(code.begin(), code.begin() + found);
		code.erase(code.begin(), code.begin() + found);

		found = code.find_first_not_of(' ');
		if (found != string::npos) {
			spaces = found;
			code.erase(code.begin(), code.begin() + found);
		} else {
			spaces = code.size();
			code.clear();
		}
		output.push_back(pair<string, int>(current, spaces));
		found = code.find(' ');
	}

	if (code.size() != 0) {
		output.push_back(pair<string, int>(code, 0));
	}
	return output;
}

vector<pair<string, int> > LabelWords(const string& code) {
	vector<pair<string, int> > output;
	vector<string> ones = LabelOnes(code);
	for (int i = 0; i < ones.size(); ++i) {
		vector<pair<string, int> > current = LabelSpaces(ones[i]);
		for (int j = 0; j < current.size(); ++j) {
			output.push_back(current[j]);
		}
	}
	return output;
}

void CountShift (string* code, int* shift) {
	size_t found;
	found = code->find('*');
	if (found == string::npos) {
		*shift = 0;
	} else {
		*shift = (int)code->size() - found;
		code->erase(code->begin() + found, code->end());
	}
}

string GetOriginalString(const vector<pair<string, int> >& codes, WordBase* dictionary) {
	string output;
	for(int i = 0; i < codes.size(); ++i) {
		string current = codes[i].first;
		int shift;
		CountShift(&current, &shift);
		if (current == "1") {
			shift = shift % 3;
			char ch;
			switch (shift) {
			case 0: ch = '.'; break;
			case 1: ch = ','; break;
			case 2: ch = '?'; break;
			}
			output += ch;
		} else {
			output += dictionary->GetWord(current, shift, i);
		}
		for (int j = 0; j < codes[i].second; ++j) {
			output += ' ';
		}
	}
	return output;
}

int main () {
	vector<Word> dictionary = ReadDictionary();
	string code = ReadT9Code();
	WordBase base(dictionary);
	vector<pair<string, int> > codes = LabelWords(code);
	string original = GetOriginalString(codes, &base);
	cout << original;
	return 0;
}