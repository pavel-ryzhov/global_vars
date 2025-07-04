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

typedef std::map< std::string, std::list < Entry > *> Dict;

class T9 {
public:
	
	void AddWord(const std::string& word, int rate);	
	void InitialAdd(const std::string& word, int rate);
	void UpdateList(const std::string& number);
	std::string NextWord();
	std::string CurrentWord();
	void Reset();
	
	T9();
	~T9();
private:
	
	void SetKeyboard();
	
	std::list < Entry > *current_list;
	std::map< unsigned char, Dict *> dictionary;
	
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
	if (current_list)
		word_index = current_list->begin();
}

void T9::AddWord(const std::string& word, int rate = 1) {
	std::list < Entry >::iterator it, it_next;
	std::string number = GetNumber(word);
	Dict *dict = dictionary[number.size()];
	if (dict->find(number) == dict->end())
		(*dict)[number] = current_list = new std::list< Entry > ();
	else
		current_list = (*dict)[number];
	it = std::find(current_list->begin(), current_list->end(), word);
	if (it == current_list->end() ) {
		current_list->push_back(Entry(word,rate));
		it = current_list->end();
		--it;
	}
	else {
		it->rate += rate;
	}
	
	if ((word != ".")&&(word != ",")&&(word != "?")) {
		if (it != current_list->begin()) {
			it_next = it--;
			while (it->rate <= it_next->rate) {
				std::iter_swap(it,it_next);
				if (it == current_list->begin())
					break;
				it_next = it--;
			}
		}
	}
	
	word_index = current_list->begin();
	//	dictionary[number] = current_list;
}

void T9::InitialAdd(const std::string& word, int rate = 1) {
	std::list < Entry >::iterator it, it_next;
	std::string number = GetNumber(word);
	Dict *dict = dictionary[number.size()];
	if (dict->find(number) == dict->end())
		(*dict)[number] = current_list = new std::list< Entry > ();
	else
		current_list = (*dict)[number];
	it = std::find(current_list->begin(), current_list->end(), word);
	if (it == current_list->end() ) {
		current_list->push_back(Entry(word,rate));
		it = current_list->end();
		--it;
	}
	else {
		it->rate += rate;
	}
	
	if ((word != ".")&&(word != ",")&&(word != "?")) {
		if (it != current_list->begin()) {
			it_next = it--;
			while (it->rate < it_next->rate) {
				std::iter_swap(it,it_next);
				if (it == current_list->begin())
					break;
				it_next = it--;
			}
		}
	}
	
	word_index = current_list->begin();
	//	dictionary[number] = current_list;
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
	current_list = (*dictionary[number.size()])[number];
	Reset();
}

std::string T9::NextWord() {
	if (word_index == current_list->end())
		word_index = current_list->begin();
	if (!current_list->empty()) {
		++word_index;
		return word_index->word;
	}
	return "";
}

std::string T9::CurrentWord() {
	if (current_list) {
		if (word_index == current_list->end())
			word_index = current_list->begin();
		if (!current_list->empty())
			return word_index->word;
	}
	return "";
}

T9::T9() {
	for (unsigned char i = 0; i <= 21; ++i) {
		dictionary[i] = new Dict;
	}	
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

T9::~T9() {
	std::map< std::string, std::list < Entry > *>::iterator it;
	Dict *dict;
	for (unsigned char i = 0; i < 21; ++i) {
		dict = dictionary[i];
		for (it = dict->begin(); it != dict->end(); ++it) {
			delete (*it).second;
		}
		delete dict;
	}
}

int main (int argc, char * const argv[]) {
	unsigned int number_of_words;
	Entry new_entry;
	std::string word;
	std::string input;
	char buf[64];
	std::string number;
	int rate;
	bool new_word = true;
	char in_char;
	T9 t9;
	unsigned int i;
	
	std::cin >> number_of_words;
	for (i = 0; i < number_of_words; ++i) {
		std::cin.getline(buf, 1);
		std::cin.getline(buf, 21, ' ');
		std::cin >> rate;
		word = buf;
		t9.InitialAdd(word, rate);
	}
	
	std::cin.getline(buf, 1);
	word.clear();
	number.clear();
	
	//std::cin.read(buf, 100001);
	
	//std::string::iterator it = input.begin();
	//int total = std::cin.gcount();
	while (true){
		std::cin.read(&in_char, 1);
		if ((in_char == '\n')||std::cin.eof()) {
			break;
		}
		switch (in_char) {
			case '*':
				if (new_word) {
					t9.UpdateList(number);
					word = t9.CurrentWord();
					new_word = false;
				}
				if (number.size()) {
					word = t9.NextWord();
				}
				break;
			case ' ':
				if (number!="1") {
					if (number.size()) {
						if (new_word) {
							t9.UpdateList(number);
							word = t9.CurrentWord();
							new_word = false;
						}
						if (!word.size())
							word = t9.CurrentWord();
						t9.AddWord(word, 1);
					}
				}
				if (word.size())
					std::cout << word;
				std::cout << " ";
				word.clear();
				number.clear();
				new_word = true;
				break;
			case '1':
				if (number!="1") {
					if (number.size()) {
						if (new_word) {
							t9.UpdateList(number);
							word = t9.CurrentWord();
							new_word = false;
						}
						if (!word.size())
							word = t9.CurrentWord();
						t9.AddWord(word, 1);
					}
				}
				if (word.size())
					std::cout << word;
				word.clear();
				number.clear();
				new_word = true;
				number = "1";
				t9.UpdateList(number);
				word = t9.CurrentWord();
				break;
			default:
				if (number!="1")
					number += in_char;
				else {
					if (new_word) {
						t9.UpdateList(number);
						word = t9.CurrentWord();
						new_word = false;
					}
					std::cout << word;
					number = in_char;
					new_word = true;
				}
				break;
		}
	}
	if (new_word) {
		t9.UpdateList(number);
		word = t9.CurrentWord();
		new_word = false;
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
