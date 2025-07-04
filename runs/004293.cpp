#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

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
	// last_update == -1 means never updated
	Word(const string& word, int freq, int last_upd = -1);
	void Print() const;
	bool operator < (const Word& right) const;
};

void Word::Print() const {
	cout << word << ' ' << frequency << ' ' << last_update << '\n';
}

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
	void Print() const;
	WordBase(const vector<Word>& dictionary);
	string GetWord(const string& code, int shift, int step);
};

void WordBase::Print() const {
	cout << "WordBasePrint" << '\n';
	for (map<string, set<Word> >::const_iterator it = Map.begin(); it != Map.end(); ++it) {
		for (set<Word>::iterator set_it = it->second.begin(); set_it != it->second.end(); ++set_it) {
			set_it->Print();
		}
	}
}

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
	//
	if (it == Map.end()) {
		cout << "GetWord Error" << '\n';
		cout << "Unexpected string: '" << code << "'" << '\n';
		abort();
	}
	//
	set<Word>::iterator set_it = it->second.begin();
	for (int i = 0; i < shift; ++i) {
		++set_it;
		if (set_it == it->second.end()) {
			set_it = it->second.begin();
		}
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

void DistinguishWord(const string& code, size_t* position, vector<pair<string, int> >* output) {
	// in pair<string, int> int is the number of spaces after the word
	if (code[*position] == '1') {
		size_t found = code.find_first_not_of('*', *position + 1);
		if (found != string::npos) {
			string current(code.begin() + *position, code.begin() + found);
			size_t found_not_space = code.find_first_not_of(' ', found);
			if (found_not_space != string::npos) {
				output->push_back(pair<string, int>(current, found_not_space - found));
				*position = found_not_space;
			} else {
				output->push_back(pair<string, int>(current, code.size() - found));
				*position = string::npos;
			}
		} else {
			string current(code.begin() + *position, code.end());
			output->push_back(pair<string, int>(current, 0));
			*position = string::npos;
		}
	} else {
		size_t found = code.find_first_of("1 ", *position);
		if (found != string::npos) {
			string current(code.begin() + *position, code.begin() + found);
			if (code[found] == '1') {
				output->push_back(pair<string, int>(current, 0));
				*position = found;
			}
			if (code[found] == ' ') {
				size_t found_not_space = code.find_first_not_of(' ', found);
				if (found_not_space != string::npos) {
					output->push_back(pair<string, int>(current, found_not_space - found));
					*position = found_not_space;
				} else {
					output->push_back(pair<string, int>(current, code.size() - found));
					*position = string::npos;
				}
			}
		} else {
			string current(code.begin() + *position, code.end());
			output->push_back(pair<string, int>(current, 0));
			*position = string::npos;
		}
	}
}

vector<pair<string, int> > Distinguish(const string& code) {
	vector<pair<string, int> > output;
	size_t position = 0;
	while (position != string::npos) {
		DistinguishWord(code, &position, &output);
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

void StressTestForWordDistinguishing(int sr) {
	srand(sr);
	const string abc = "*23456789";
	const int MAX_WORDS = 30;
	const int MAX_SPACES = 10;
	const int MAX_WORD_LENGTH = 30;
	string T9code;
	vector<pair<string, int> > true_codes, codes;
	int step = 0;
	do {
		cout << step++ << " OK\n";
		true_codes.clear();
		T9code.clear();
		int words = rand() % MAX_WORDS + 1;
		for (int i = 0; i < words; ++i) {
			pair<string, int> current;
			current.second = rand() % MAX_SPACES;
			int length = rand() % MAX_WORD_LENGTH + 1;
			if (rand() % 2 == 0) {
				char first = abc[rand() % 8 + 1];
				current.first += first;
				T9code += first;
				for (int j = 1; j < length; ++j) {
					char cur = abc[rand() % 9];
					current.first += cur;
					T9code += cur;
				}
				// number of spaces can't be 0 here
				++current.second;
				for (int j = 0; j < current.second; ++j) {
					T9code += ' ';
				}
			} else {
				// after punctuation mark number of spaces can be 0
				T9code += '1';
				current.first += '1';
				for (int j = 1; j < length; ++j) {
					T9code += '*';
					current.first += '*';
				}
				for (int j = 0; j < current.second; ++j) {
					T9code += ' ';
				}
			}
			true_codes.push_back(current);
		}
		codes = Distinguish(T9code);

	} while (codes == true_codes);
	cout << "ERROR\n";
	cout << T9code << "//" << '\n';
	for (int i = 0; i < codes.size(); ++i) {
		cout << codes[i].first << '\n';
	}
	cout << '\n';
	for (int i = 0; i < true_codes.size(); ++i) {
		cout << true_codes[i].first << '\n';
	}
}

int main () {
	vector<Word> dictionary = ReadDictionary();
	string code = ReadT9Code();
	WordBase base(dictionary);

	vector<pair<string, int> > codes = Distinguish(code);
	string original = GetOriginalString(codes, &base);
	cout << original;
	return 0;
}