#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <algorithm>
#include <vector>


using std::map;
using std::pair;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::make_pair;
using std::getline;
using std::list;
using std::sort;
using std::copy;
using std::vector;


std::string int_to_str(int tmp) {
	std::ostringstream out;
    out << tmp;
    return out.str();
}

class CompareForPairs {
public:
	bool operator() (pair <int, string> first_pair, pair<int, string> second_pair){
		if (first_pair.first > second_pair.first) {
			return true;
		}
		else {
			if (first_pair.first < second_pair.first) {
				return false;
			}
			else {
				if (first_pair.second < second_pair.second) {
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
};

string word_to_numbers_coder (const string& word) {
	string number_code = "";
	for (int i = 0; i < word.length(); ++i) {
		char current_letter = word[i];
		char current_letter_value = current_letter - 'a';
		int number_to_add;
		if ((current_letter_value / 3) < 6) {
			number_to_add = (int)(current_letter_value/3) + 2;
		}
		else {
			if (current_letter == 's') {
				number_to_add = 7;
			}
			if ('s' < current_letter && current_letter < 'w') {
				number_to_add = 8;
			}
			if (current_letter >= 'w') {
				number_to_add = 9;
			}
		}
		number_code += int_to_str(number_to_add);
	}
	return number_code;
}

string word_decoder (const string& message_in_numbers, map <string, list <pair <int, string> > >* dictionary,
	int begin, int end, int word_variant) {
		string word_in_numbers = message_in_numbers.substr(begin, end - begin);
		list < pair <int, string> >& current_list = (*dictionary)[word_in_numbers];
		list <pair <int, string> >::iterator translation = current_list.begin();

		for (int i = 0; i < word_variant; ++i) {
			++translation;
		}
		pair<int, string> current_word_article = (*translation);
		(*dictionary)[word_in_numbers].erase(translation++);
		++(current_word_article.first);

		if (current_list.empty()) {
			current_list.push_back(current_word_article);
		}
		else {
			while (translation != current_list.begin() && (--translation) -> first <= current_word_article.first) {}
			if (translation -> first > current_word_article.first) {
				++translation;
			}
			current_list.insert(translation, current_word_article);
		}
		return current_word_article.second;
}

string punctuation_decoder (const string& message_in_numbers, int begin, int end) {
	int variant_counter = end - begin - 1;
	switch (variant_counter) {
	case 0:
		return ".";
	case 1:
		return ",";
	case 2:
		return "?";
	}
}
string add_spases (const string& message_in_numbers, int& current_letter) {
	string spaces = "";
	while (current_letter < message_in_numbers.size() && message_in_numbers[current_letter] == ' ') {
		spaces += ' ';
		++current_letter;
	}
	return spaces;
}

string message_parser (const string& message_in_numbers, map <string, list <pair <int, string> > > dictionary) {
	string text_message = "";
	int current_letter = 0;
	while (current_letter < message_in_numbers.size()){
		if (message_in_numbers[current_letter] >= '2' && message_in_numbers[current_letter] <= '9') {
			int current_word_begin = current_letter;
			for (; current_letter < message_in_numbers.size(); ++current_letter) {
				if (message_in_numbers[current_letter] < '2' || message_in_numbers[current_letter] > '9') {
					break;
				}
			}
			int word_variant_counter = 0, current_word_end = current_letter;
			while(current_letter < message_in_numbers.size() && message_in_numbers[current_letter] == '*') {
				++current_letter;
				++word_variant_counter;
			}
			text_message += word_decoder (message_in_numbers, &dictionary, current_word_begin, 
					current_word_end, word_variant_counter);
		}
		if (message_in_numbers[current_letter] == '1') {
			while (current_letter < message_in_numbers.size() && message_in_numbers[current_letter] == '1') {
				int punctuation_start = current_letter;
				++current_letter;
				while (current_letter < message_in_numbers.size() && message_in_numbers[current_letter] == '*') {
					++current_letter;
				}
				text_message += punctuation_decoder(message_in_numbers, punctuation_start, current_letter);
			}
		}
		text_message += add_spases(message_in_numbers, current_letter);
	}
	return text_message;
}

void input (map <string, list <pair <int, string> > >* dictionary, string* message) {
	int dictionary_size;
	cin >> dictionary_size;
	for (int i = 0; i < dictionary_size; ++i) {
		string word, number_code;
		cin >> word;
		number_code = word_to_numbers_coder(word);
		int frequency;
		cin >> frequency;
		(*dictionary)[number_code].push_back(make_pair(frequency, word));
	}
	string al;
	getline (cin, al);
	getline (cin, *message);
}

void sort_dictionary (map <string, list <pair <int, string> > >* dictionary) {
	for (map<string, list <pair <int, string> > >::iterator it = dictionary -> begin(); 
		it != dictionary->end(); ++it) {
			vector <pair <int, string> > temp (it->second.size());
			copy(it->second.begin(), it->second.end(), temp.begin());
			sort(temp.begin(), temp.end(), CompareForPairs());
			copy(temp.begin(),temp.end(),it->second.begin());
	}
}

int main() {
	map <string, list <pair <int, string> > > dictionary;
	string message_in_numbers;
	input (&dictionary, &message_in_numbers);
	sort_dictionary (&dictionary);
	cout << message_parser(message_in_numbers,dictionary) << endl;
	return 0;
}