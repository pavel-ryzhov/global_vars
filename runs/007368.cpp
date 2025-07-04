#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::map;
using std::string;
using std::pair;
using std::multimap;
using std::vector;



class T9 {
	public:
		T9() {
			InitializeRuleOfLetterConversion();	
		}
		
		void Input();
		void FindOriginalMessage(); 
		friend void OutputOriginalMessage(const T9 & );

	private:
		map<string, multimap<int, string> > vocabulary;
		map<char, char> letter_to_button_number;
		vector<pair <string, int> > word_and_frequency_buffer;
		string input_digital_message;
		vector<string> parsed_words;
		vector<int> changes_number;
		vector<string> original_message;

		map<string, multimap<int, string> >::iterator iter;
		multimap<int, string>::reverse_iterator reverse_iter;

		void InitializeRuleOfLetterConversion();
		string ConvertWordToDigits(const string & word);
		void ConstructDictionary();
		void ParseDigitalMessage();
};



void T9::InitializeRuleOfLetterConversion() {
		
	for (int ascii_number = 97; ascii_number <= 122; ++ascii_number) {
		if (ascii_number >= 97 && ascii_number <= 99 ) {
			letter_to_button_number.insert(pair<char, int> ((char)ascii_number, '2'));
		}
		
		if (ascii_number >= 100 && ascii_number <= 102 ) {
			letter_to_button_number.insert(pair<char, int> ((char)ascii_number, '3'));
		}

		if (ascii_number >= 103 && ascii_number <= 105 ) {
			letter_to_button_number.insert(pair<char, int> ((char)ascii_number, '4'));
		}

		if (ascii_number >= 106 && ascii_number <= 108 ) {
			letter_to_button_number.insert(pair<char, int> ((char)ascii_number, '5'));
		}

		if (ascii_number >= 109 && ascii_number <= 111 ) {
			letter_to_button_number.insert(pair<char, int> ((char)ascii_number, '6'));
		}

		if (ascii_number >= 112 && ascii_number <= 115 ) {
			letter_to_button_number.insert(pair<char, int> ((char)ascii_number, '7'));
		}

		if (ascii_number >= 116 && ascii_number <= 118 ) {
			letter_to_button_number.insert(pair<char, int> ((char)ascii_number, '8'));
		}

		if (ascii_number >= 119 && ascii_number <= 122 ) {
			letter_to_button_number.insert(pair<char, int> ((char)ascii_number, '9'));
		}
	}
}



void T9::Input() {

	int vocabulary_size;
	cin >> vocabulary_size;
	word_and_frequency_buffer.resize(vocabulary_size);

	string current_word;
	int current_frequency;

	for (int word_index = 0; word_index < vocabulary_size; ++word_index) {
		cin >> current_word >> current_frequency;
		word_and_frequency_buffer[word_index] = pair<string, int> (current_word, current_frequency);
	}
	
	ConstructDictionary();

	cin.get();
	getline(cin, input_digital_message);
	ParseDigitalMessage();
}



string T9::ConvertWordToDigits(const string& word) {

	string digits = "";

	for (int index = 0; index < word.length(); ++index) {
		digits += letter_to_button_number[word[index]];
	}

	return digits;
}



void T9::ConstructDictionary() {

	vector<pair <string, int> >::reverse_iterator pair_iter;
	string current_word;
	int current_frequency;

	for (pair_iter = word_and_frequency_buffer.rbegin() ; pair_iter != word_and_frequency_buffer.rend(); ++pair_iter) {
		current_word = pair_iter->first;
		current_frequency = pair_iter->second;

		string digital_analog_of_current_word = ConvertWordToDigits(current_word);
		iter = vocabulary.find(digital_analog_of_current_word);

		if (iter != vocabulary.end()) {

			vocabulary[digital_analog_of_current_word].insert(pair<int, string> (current_frequency, current_word));

		} else { 

			multimap<int, string> tmp_map;
			tmp_map.insert(pair<int, string> (current_frequency, current_word));
			vocabulary.insert(pair<string, multimap<int, string > > (digital_analog_of_current_word, tmp_map));

		}
	}

	word_and_frequency_buffer.clear();
}



void T9::ParseDigitalMessage() {
	string current_word = "";
	string current_symbol, previous_symbol = "";
	int current_changes_number = 0;


	for (int index = 0; index < input_digital_message.length(); ++index) {
		current_symbol = input_digital_message[index];

		if (index > 0) {

			previous_symbol = input_digital_message[index - 1];
		}

		if (current_symbol != "1" && current_symbol != "*" && current_symbol != " ") {

			if (previous_symbol != "1" && previous_symbol != "*") {

				current_word += current_symbol;

			} else {

				parsed_words.push_back(current_word);
				changes_number.push_back(current_changes_number);
				current_word = current_symbol;
				current_changes_number = 0;
			}

		} else {

			if (current_symbol == "*") {

				++current_changes_number;
			}

			if (current_symbol == "1") {

				if (current_word != "") {

					parsed_words.push_back(current_word);
					changes_number.push_back(current_changes_number);

				} 
					current_word = "1";
					current_changes_number = 0;
			}

			if (current_symbol == " ") {

				if (current_word != "") {

					parsed_words.push_back(current_word);
					changes_number.push_back(current_changes_number);
					current_word = "";
					current_changes_number = 0;
				}

				parsed_words.push_back(current_symbol);
				changes_number.push_back(0);
				continue;
			}
		}
	}


	if (current_word != "") {

		parsed_words.push_back(current_word);
		changes_number.push_back(current_changes_number);

	}
}



void T9::FindOriginalMessage() {

	for (int index = 0; index < parsed_words.size(); ++index) {

		string current_word = parsed_words[index];
		int current_word_changes_number = changes_number[index];

		if (current_word == " ") {

			original_message.push_back(" ");
			continue;
		}

		if (current_word == "1") {
			switch (current_word_changes_number) {
				case 0 : original_message.push_back("."); break;
				case 1 : original_message.push_back(","); break;
				case 2 : original_message.push_back("?"); break;
			}
			continue;
		}

		reverse_iter =  vocabulary[current_word].rbegin();

		for (int changes_counter = 0; changes_counter < current_word_changes_number; ++changes_counter) {
		 	++reverse_iter;
		}
		
		original_message.push_back(reverse_iter->second);

		int current_frequency = reverse_iter->first;
		string current_original_word = reverse_iter->second;

		vocabulary[current_word].erase((++reverse_iter).base());
		vocabulary[current_word].insert(pair<int, string>(current_frequency + 1, current_original_word));
		
	}
}



void OutputOriginalMessage(const T9 & my_t9) {

	for (int index = 0; index < my_t9.original_message.size(); ++index) {
		cout << my_t9.original_message[index];
	}
}

int main() {

	T9 my_t9;
	my_t9.Input();
	my_t9.FindOriginalMessage();
	OutputOriginalMessage(my_t9);
	
	return 0;
}