#include <iostream>
#include <string>
#include <map>
#include <list>
#include <algorithm>

typedef struct _Entry {
	std::string word;
	int rate;
	
	bool operator == (const std::string& b);	
	
	_Entry(std::string newword, int newrate);
	_Entry();
} Entry;

class T9 {
public:
	
	void AddWord(const std::string& word, int rate);
	void UpdateList(const std::string& number);
	std::string NextWord();
	std::string CurrentWord();
	void Reset();
	
	T9();
	~T9() {};
private:
	
	void SetKeyboard();
	
	std::list < Entry > current_list;
	std::map< std::string, std::list < Entry > > dictionary;
	
	std::string GetNumber(const std::string &word);
	std::list < Entry >::iterator word_index;
	std::map< char,char > keyboard;
};


bool _Entry::operator == (const std::string& b) {
	return (word.compare(b) == 0);
}

_Entry::_Entry() {
	rate = 0;
}

_Entry::_Entry(std::string newword, int newrate) {
	word = newword;
	rate = newrate;
}



void T9::Reset() {
	word_index = current_list.begin();
}

void T9::AddWord(const std::string& word, int rate = 1) {
	std::list < Entry >::iterator it, it_next;
	std::string number = GetNumber(word);
	UpdateList(number);
	it = std::find(current_list.begin(), current_list.end(), word);
	if (it == current_list.end() ) {
		current_list.push_back(Entry(word,rate));
	}
	else {
		if ((word != ".")&&(word != ",")&&(word != "?")) {
			it->rate += rate;
			if (it != current_list.begin()) {
				it_next = it--;
				while (it->rate <= it_next->rate) {
					std::iter_swap(it,it_next);
					if (it == current_list.begin())
						break;
					it_next = it--;
				}
			}
		}
	}
	word_index = current_list.end();
	dictionary[number] = current_list;
}

std::string T9::GetNumber(const std::string &word) {
	std::string result = word;
	unsigned int i;
	for (i = 0; i<word.length(); ++i) {
		result[i] = keyboard[result[i]];
	}
	return result;
}

void T9::UpdateList(const std::string& number) {
	if (dictionary.find(number) == dictionary.end())
		dictionary[number] = std::list< Entry > ();
	current_list = dictionary[number];
	Reset();	
}

std::string T9::NextWord() {
	if (word_index == current_list.end())
		word_index = current_list.begin();
	++word_index;
	if (!current_list.empty())
		return word_index->word;
	return "";
}

std::string T9::CurrentWord() {
	if (word_index == current_list.end())
		word_index = current_list.begin();
	if (!current_list.empty())
		return word_index->word;
	return "";
}

T9::T9() {
	Reset();
	SetKeyboard();
}

void T9::SetKeyboard() {
	keyboard['a'] = '2';
	keyboard['b'] = '2';
	keyboard['c'] = '2';
	keyboard['d'] = '3';
	keyboard['e'] = '3';
	keyboard['f'] = '3';
	keyboard['g'] = '4';
	keyboard['h'] = '4';
	keyboard['i'] = '4';
	keyboard['j'] = '5';
	keyboard['k'] = '5';
	keyboard['l'] = '5';
	keyboard['m'] = '6';
	keyboard['n'] = '6';
	keyboard['o'] = '6';
	keyboard['p'] = '7';
	keyboard['q'] = '7';
	keyboard['r'] = '7';
	keyboard['s'] = '7';
	keyboard['t'] = '8';
	keyboard['u'] = '8';
	keyboard['v'] = '8';
	keyboard['w'] = '9';
	keyboard['x'] = '9';
	keyboard['y'] = '9';
	keyboard['z'] = '9';
	keyboard['.'] = '1';
	keyboard[','] = '1';
	keyboard['?'] = '1';
	keyboard[' '] = ' ';
	AddWord(".",3);
	AddWord(",",2);
	AddWord("?",1);
}
int main (int argc, char * const argv[]) {
	unsigned int number_of_words;
	Entry new_entry;
	std::string word;
	std::string input;
	char buf[21];
	std::string number;
	int rate;
	T9 t9;
	unsigned int i;
	
	std::cin >> number_of_words;
	for (i = 0; i < number_of_words; ++i) {
		std::cin.getline(buf, 1);
		std::cin.getline(buf, 21, ' ');
		std::cin >> rate;
		word = buf;
		t9.AddWord(word, rate);
	}
	
	std::cin.getline(buf, 1);
	word.clear();
	number.clear();
	
	std::getline(std::cin, input);
	
	char in_char;
	std::string::iterator it = input.begin();
	for (it = input.begin(); it != input.end(); ++it) {
		in_char = (*it);
		switch (in_char) {
			case '*':
				if (number.size()) {
					word = t9.NextWord();
				}
				break;
			case ' ':
				if (number!="1") {
					if (number.size()) {
						if (!word.size())
							word = t9.CurrentWord();
						t9.AddWord(word, 1);
					}
				}
				std::cout << word;
				std::cout << " ";
				word.clear();
				number.clear();
				break;
			case '1':
				if (number!="1") {
					if (number.size()) {
						if (!word.size())
							word = t9.CurrentWord();
						t9.AddWord(word, 1);
					}
				}
				std::cout << word;
				word.clear();
				number = "1";
				t9.UpdateList(number);
				word = t9.CurrentWord();
				//std::cout << word;
				break;
			default:
				number += in_char;
				t9.UpdateList(number);
				break;
		}
	}
	if (word.size())
		std::cout << word;
	else {
		if (number.size()) {
			if (!word.size())
				word = t9.CurrentWord();
			t9.AddWord(word, 1);
		}
		std::cout << word;
	}
	std::cout.flush();
	return 0;
}
