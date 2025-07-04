#include <set>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <sstream>

using std::string;
using std::set;
using std::map;
using std::vector;
using std::cin;
using std::cout;
using std::greater;
using std::istringstream;
using std::getline;

struct word_entry{
	int rating;
	int request_number;
	string word;

	word_entry()
		: rating(0),
		request_number(0),
		word("") {}

	word_entry(const string& _word, int _rating)
		: rating(_rating),
		request_number(0),
		word(_word) {}
};

bool operator > (const word_entry& lhv, const word_entry& rhv) {
	if (lhv.rating != rhv.rating) {
		return lhv.rating > rhv.rating;
	}

	if (lhv.request_number != rhv.request_number) {
		return lhv.request_number > rhv.request_number;
	}

	return lhv.word < rhv.word;
}

class numerical_combination {
	private:
		int number_of_requests;
		set<word_entry, greater<word_entry> > entries;
		typedef set<word_entry, greater<word_entry> >::iterator word_entry_iterator;

	public:
		numerical_combination()
			: number_of_requests(0) {}

		string get_word(int number_in_rating);
		void insert_entry(const string& word, int rating);
};

void numerical_combination::insert_entry(const string &word, int rating) {
	entries.insert(word_entry(word, rating));
}

string numerical_combination::get_word(int position_in_rating) {
	word_entry_iterator request_entry = entries.begin();
	for (int entry_index = 0; entry_index < position_in_rating; ++entry_index) {
		++request_entry;
	}

	word_entry update_entry(request_entry->word, request_entry->rating);
	entries.erase(request_entry);

	update_entry.request_number = ++number_of_requests;
	++update_entry.rating;
	entries.insert(update_entry);

	return update_entry.word;
}

class T9_dictionary {
	private:
		map<string, numerical_combination> combinations;

	private:
		static string word_to_numerical_combination(const string& word);

	public:
		void insert_word(const string& word, int rating);
		string get_word(string numerical_combination, int position_in_rating);
};

string T9_dictionary::get_word(string numerical_combination, int position_in_rating) { 
	return combinations[numerical_combination].get_word(position_in_rating);
}

void T9_dictionary::insert_word(const string& word, int rating) {
	string numerical_combination = word_to_numerical_combination(word);
	combinations[numerical_combination].insert_entry(word, rating);
}

string T9_dictionary::word_to_numerical_combination(const string& word) {
	string combination;
	for (int character_index = 0; character_index < word.size(); ++character_index) {
		switch(word[character_index]) {
			case 'a': case 'b': case 'c': 
				combination += '2';
				break;
			case 'd': case 'e': case 'f': 
				combination += '3';
				break;
			case 'g': case 'h': case 'i': 
				combination += '4';
				break;
			case 'j': case 'k': case 'l': 
				combination += '5';
				break;
			case 'm': case 'n': case 'o': 
				combination += '6';
				break;
			case 'p': case 'q': case 'r': case 's': 
				combination += '7';
				break;
			case 't': case 'u': case 'v': 
				combination += '8';
				break;
			case 'w': case 'x': case 'y': case 'z': 
				combination += '9';
				break;
			default:
				break;
		};
	}

	return combination;
}

void init_dictionary(T9_dictionary* my_dictionary) {
	int number_of_words;
	cin >> number_of_words;

	for (int word_index = 0; word_index < number_of_words; ++word_index) {
		string word;
		int rating;

		cin >> word >> rating;
		(*my_dictionary).insert_word(word, rating);
	}
}

string get_request_string() {
	cin.get();

	string request_string;
	getline(cin, request_string);

	return request_string;
}

char get_punctuation_mark(const string& request_string,
						  string::iterator& current_symbole) {
	int number_in_rating = 0;
	while (current_symbole != request_string.end() && *current_symbole == '*') {
		++current_symbole;
		++number_in_rating;
	}

	switch (number_in_rating) {
		case 0 : return '.';
		case 1 : return ',';
		case 2 : return '?';
	}
}

int get_numerical_combination(const string& request_string,
							  string::iterator& current_symbole,
							  string* numerical_combination) {

	while (current_symbole != request_string.end() && *current_symbole != '*' && 
		   *current_symbole != '1' && *current_symbole != ' ') {
		*numerical_combination += *current_symbole;
		++current_symbole;
	}

	int position_in_rating = 0;
	while (current_symbole != request_string.end() && *current_symbole == '*') {
		++current_symbole;
		++position_in_rating;
	}

	return position_in_rating;
}

string compute_text_string(T9_dictionary my_dictionary,
						   string request_string) {
	string text_string;
	string::iterator current_symbole = request_string.begin();

	while (current_symbole != request_string.end()) {
		if (*current_symbole == ' ') {
			text_string += " ";
			++current_symbole;
		} else if (*current_symbole == '1'){
			++current_symbole;
			text_string += get_punctuation_mark(request_string, current_symbole);
		} else {
			string numerical_combination;
			int position_in_rating = 
				get_numerical_combination(request_string, current_symbole, &numerical_combination);
			
			text_string += my_dictionary.get_word(numerical_combination, position_in_rating);
		}
	}

	return text_string;
}

void print_text_string(const string& text_string) {
	cout << text_string;
}

int main() {
	T9_dictionary my_dictionary;
	init_dictionary(&my_dictionary);

	string request_string = get_request_string();
	string text_string = compute_text_string(my_dictionary, request_string);
	
	print_text_string(text_string);
	return 0;
}
