#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <list>

using std::multimap;
using std::map;
using std::cout;
using std::cin;
using std::pair;
using std::string;
using std::vector;
using std::list;

struct classcomp {
  bool operator() (const int& left, const int& right) const {
	  return left > right;
  }
};

void Input(map<string, int>* hash, vector<multimap<int, string,classcomp> > * dictionary, string * combination) {
	map<char, char> T9;
	T9['a'] = '2'; T9['b'] = '2'; T9['c'] = '2';
	T9['d'] = '3'; T9['e'] = '3'; T9['f'] = '3';
	T9['g'] = '4'; T9['h'] = '4'; T9['i'] = '4';
	T9['j'] = '5'; T9['k'] = '5'; T9['l'] = '5';
	T9['m'] = '6'; T9['n'] = '6'; T9['o'] = '6';
	T9['p'] = '7'; T9['q'] = '7'; T9['r'] = '7'; T9['s'] = '7';
	T9['t'] = '8'; T9['u'] = '8'; T9['v'] = '8';
	T9['w'] = '9'; T9['x'] = '9'; T9['y'] = '9'; T9['z'] = '9';


	int count_words;
	cin >> count_words;
	int number_cell = 0;
	
	while(count_words > 0) {
		string word;
		int frequency;
		cin >> word;
		cin >> frequency;
		int number_letter = 0;
		string buttons = "";
		while(number_letter < word.length()) { 
			buttons += T9[word[number_letter]];
			++number_letter;
		}
		if(hash->count(buttons) > 0) {
			(*dictionary)[(*hash)[buttons]].insert(pair<int,string>(frequency, word));
		} else {
			multimap<int, string, classcomp> new_combinations;
			new_combinations.insert(pair<int,string>(frequency, word));
			dictionary->push_back(new_combinations);
			(*hash)[buttons] = number_cell;
			++number_cell;
		}
		--count_words;
	}

	string input;
	std::getline(cin, input);
	std::getline(cin, input);

	*combination = input; 	
}


void IncreaseFrequency(multimap<int, string, classcomp> * dictionary, multimap<int, string,classcomp>::iterator * word) {
	pair<int, string> new_element((*word)->first + 1, (*word)->second);
	dictionary->erase(*word);
	dictionary->insert(dictionary->lower_bound(new_element.first),new_element);
}


void Parsing(map<string, int>& hash, vector<multimap<int, string, classcomp> >* dictionary,
			 const string& combination, string* result) {
	
	// . , ?
	list<char> punctuation_signs;
	punctuation_signs.push_back('.');
	punctuation_signs.push_back(',');
	punctuation_signs.push_back('?');


	string buttons = "";
	*result == "";
	multimap<int, string,classcomp>::iterator word;
	
	int letter = 0;
	while(letter < combination.length()) {
		// abc*
		if(combination[letter] == '*') {
			int number_cell = hash[buttons];
			word = (*dictionary)[number_cell].begin();

			while(combination[letter] == '*') {
				++letter;
				++word;		
				if(letter == combination.length()) {
					*result += word->second;
					return;
				}
				if(word == (*dictionary)[number_cell].end()) {
					word = (*dictionary)[number_cell].begin();
				}
			}

			*result += word->second;
			IncreaseFrequency(&(*dictionary)[number_cell], &word);
			buttons = "";
		}
		
		// abc abc
		if(combination[letter] == ' ') {
			if(buttons == "") {
				*result += " ";
			} else {
				int number_cell = hash[buttons];
				word = (*dictionary)[number_cell].begin();
				*result += word->second;
				*result += " ";
				IncreaseFrequency(&(*dictionary)[number_cell], &word);
				buttons = "";
			}

			++letter;
			if(letter == combination.length()) {
				return;
			}
		} 

		// . , ?
		if(combination[letter] == '1') {
			if(buttons != "") {
				int number_cell = hash[buttons];
				word = (*dictionary)[number_cell].begin();
				*result += word->second;				
				IncreaseFrequency(&(*dictionary)[number_cell], &word);
				buttons = "";
			} 

			list<char>::const_iterator sign = punctuation_signs.begin();
			++letter;			
			if(letter == combination.length()) {
				*result += *sign;
				return;
			}

			while(combination[letter] == '*') {
				++sign;
				if(sign == punctuation_signs.end()) {
					sign = punctuation_signs.begin();
				}
				++letter;			
				if(letter == combination.length()) {
					*result += *sign;
					return;
				}
			}
			*result += *sign;			
		}

		// abc
		if(combination[letter] != '1' && combination[letter] != ' ' && combination[letter] != '*') { 
			buttons += combination[letter];
			++letter;
		}
	}

	if(buttons != "") {
		int number_cell = hash[buttons];
		word = (*dictionary)[number_cell].begin();
		*result += word->second;
	}
}

void Output(const string& result) {
	cout << result;
}

int main() {
	string combination;
	map<string, int> hash; 
	vector<multimap<int, string,classcomp> > dictionary;
	Input(&hash, &dictionary, &combination);

	string result;
	Parsing(hash, &dictionary, combination, &result);

	Output(result);

	return 0;
}