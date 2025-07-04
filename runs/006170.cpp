// yaTest3.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::vector;
using std::getline;
class Request {
	string start_request;
public:
	vector<pair<string, int> > splited_request;
	int start_space;
	vector<int> spaces;
	void SplitRequest();
	void InputRequest();
};

class Dictionary {
	map<string, multimap<int, string> > code_words;
	void ProcessElementaryRequest(pair<string, int>& elem_request, string* answer); 
public:
	void InputContent();
	void ProcessRequest(Request& request, vector<string>* answer);
	void OutputAnswer(vector<string>& answer);
};

void Request::SplitRequest() {
	string current_code;
	int variant = 0;
	start_space = 0;
	while (start_request[start_space] == ' ') {
		++start_space;
	}
	for (int i = start_space; i < start_request.length(); ++i) {
		if ((start_request[i] <= '9') && (start_request[i] >= '2')) {
			if (current_code.length()) {
				if (current_code[current_code.length() - 1] == '1') {
					splited_request.push_back(pair<string, int>(current_code, variant));
					spaces.push_back(0);
					variant = 0;
					current_code.clear();
				}
			}
			current_code.append(&start_request[i], 1);
		} else if (start_request[i] == '1') {
			if (current_code.length()) {
				splited_request.push_back(pair<string, int>(current_code, variant));
				spaces.push_back(0);
			}
			current_code.clear();
			current_code.append("1");
			variant = 0;
		} else if (start_request[i] == ' ') {
			if (current_code.length()) {
				splited_request.push_back(pair<string, int>(current_code, variant));
				spaces.push_back(1);
			} else {
				++spaces[spaces.size() - 1];
			}
			current_code.clear();
			variant = 0;
		} else if (start_request[i] == '*') {
			++variant;
		}
	}
	if (current_code.length()) {
		splited_request.push_back(pair<string, int>(current_code, variant));
		spaces.push_back(0);
	}

}

void Request::InputRequest() {
	cin.get();
	getline(cin, start_request);
	/*start_request.resize(100001);
	cin.getline((char*)(start_request).c_str(), start_request.size());
	cin.getline((char*)(start_request).c_str(), start_request.size());
	start_request.erase(start_request.find((char)0));*/
}

void Dictionary::ProcessElementaryRequest(pair<string, int>& elem_request, string* answer) {
	map<string, multimap<int, string> >::iterator pointer_to_variants = code_words.find(elem_request.first);
	multimap<int, string>::iterator pointer_to_word = pointer_to_variants->second.begin();
	for (int i = 0; i <= elem_request.second%(pointer_to_variants->second.size()); ++i) {
		*answer = pointer_to_word->second;
		++pointer_to_word;
	}
	
	if (elem_request.first == "1") {
		return;
	}
	--pointer_to_word;
	int new_word_frequency = pointer_to_word->first - 1;
	multimap<int, string>::iterator iterator_for_insert = pointer_to_variants->second.find(new_word_frequency);
	pointer_to_variants->second.erase(pointer_to_word);
	if (iterator_for_insert != pointer_to_variants->second.end()) {
		pointer_to_variants->second.insert(iterator_for_insert, pair<int, string>(new_word_frequency, *answer));
	} else {
		pointer_to_variants->second.insert(pair<int, string>(new_word_frequency, *answer));
	}
}

void Dictionary::ProcessRequest(Request& request, vector<string>* answer) {
	for (int i = 0; i < request.splited_request.size(); ++i) {
		string next_one;
		ProcessElementaryRequest(request.splited_request[i], &next_one);
		string spaces;
		if (i == 0) {
			for (int i_space = 0; i_space < request.start_space; ++i_space) {
				spaces.append(" ");
			}
			next_one = spaces + next_one;
		}		
		for (int i_space = 0; i_space < request.spaces[i]; ++i_space) {
			next_one.append(" ");
		}
		answer->push_back(next_one);
	}
}

void Dictionary::OutputAnswer(vector<string>& answer) {
	for (int i = 0; i < answer.size(); ++i) {
		cout << answer[i];
	}
}
char DetectButton(char symbol) {
	int ascii_code = int(symbol);
	int order_in_alphabet = ascii_code - 'a';
	int button;
	if (order_in_alphabet < 15) {
		button = order_in_alphabet/3 + 2;
	} else if (order_in_alphabet < 19) {
		button = 7;
	} else if (order_in_alphabet < 22) {
		button = 8;
	} else {
		button = 9;
	}

	return button + '0';
}

void DetectCode(string& word, string* code) {
	code->clear();
	for (int i = 0; i < word.length(); ++i) {
		code->resize(code->size() + 1);
		code->at(code->size() - 1) = (char)DetectButton(word[i]);
	}
}

void Dictionary::InputContent() {
	int dictionary_size;
	cin >> dictionary_size;
	for (int i = 0; i < dictionary_size; ++i) {
		string word;
		cin >> word;
		string code;
		DetectCode(word, &code);
		int frequency;
		cin >> frequency;
		map<string, multimap<int, string> >::iterator dict_iter = code_words.find(code);
		pair<int, string> new_word(frequency*(-1), word);
		if (dict_iter == code_words.end()) {
			multimap<int, string> new_multimap;
			new_multimap.insert(new_word);
			code_words.insert(pair<string, multimap<int, string> >(code, new_multimap));
		} else {
			dict_iter->second.insert(new_word);
		}
	}
	multimap<int, string> punctuation;
	punctuation.insert(pair<int, string>(-3, "."));
	punctuation.insert(pair<int, string>(-2, ","));
	punctuation.insert(pair<int, string>(-1, "?"));
	code_words.insert(pair<string, multimap<int, string> >("1", punctuation));

}

void Input(Dictionary* dictionary, Request* request) {
	dictionary->InputContent();
	request->InputRequest();
}

int main()
{
	Dictionary dictionary;
	Request request;
	Input(&dictionary, &request);
	request.SplitRequest();
	vector<string> answer;
	dictionary.ProcessRequest(request, &answer);
	dictionary.OutputAnswer(answer);
	return 0;
}

