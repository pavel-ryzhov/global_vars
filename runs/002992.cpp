#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <list>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::map;
using std::list;
using std::vector;

/*
	Вспомогательные функции для работы с символами
*/

static bool isDigit(int keyCode) {
	return keyCode > -1 && keyCode < 9;
}

static char getPunctuation (const std::string &keySequence, int * position) {
	int variant = 0;
	while (keySequence[*position] == '*') {
		++variant;
		++(*position);
	}
	switch (variant) {
		case(0):
			return '.';
		case(1):
			return ',';
		case(2):
			return '?';
	}
}

static int keyCode (char key) {
	return key - '2';
}

/*
	Определение класса Word
*/

typedef std::map<int, list<string>, std::greater<int> > wordBunch;

class Word {
public:
	Word(const string & word, int frequency): word_(word), frequency_(frequency) {}
	void increaseFreaquency() {
		++frequency_;
	}
	const bool operator > (const Word & other) const;
	const bool operator >= (const Word & other) const;
	const string getKeySequence() const {
		return getKeySequence_(word_);
	}
	string getWord() const {
		return word_;
	}
	int getFrequency() const {
		return frequency_;
	}
private:
	string word_;
	int frequency_;
	static char getKey_ (char letter);
	static const string getKeySequence_ (const string & word);
};

const bool Word::operator > (const Word & other) const {
	return frequency_ > other.frequency_;
}

char Word::getKey_ (char letter) {
	int charCode = letter - 'a';
	if (charCode < 3) return '2';
	if (charCode < 6) return '3';
	if (charCode < 9) return '4';
	if (charCode < 12) return '5';
	if (charCode < 15) return '6';
	if (charCode < 19) return '7';
	if (charCode < 22) return '8';
	if (charCode < 26) return '9';
	return ' '; //Входные данные неверны.
}

const string Word::getKeySequence_ (const string & word) {
	string keySequence = "";
	for (int letter = 0; letter < word.size(); ++letter) {
		keySequence += getKey_(word[letter]);
	}
	return keySequence;
}

Word readWord() { 
	string inputWord;
	int inputFrequency;
	cin >> inputWord >> inputFrequency;
    Word newWord(inputWord, inputFrequency);
	return newWord;
} 

/*
	Определение бора числовых последовательностей
*/

class TrieNode {
public:
	TrieNode(): sons_(9), wordBunch_() {}
	void addWord (const Word & word);
	void addSon (char key);
	TrieNode * getSon (char key) const {
		return sons_[keyCode(key)];
	}
	string getWord (int variant);	
	void deleteSubTree();
private:
	vector<TrieNode *> sons_;
	wordBunch wordBunch_;
};


string TrieNode::getWord(int variant) {
	wordBunch::iterator iterWB = wordBunch_.begin();
	int option = 0;
	while (option + iterWB->second.size() <= variant) {
		option += iterWB->second.size();
		++iterWB;
	}
	int position = variant - option;
	list<string>::iterator iterList = iterWB->second.begin();
	for (int i = 0; i < position; ++i) {
		++iterList;
	}
	string wordNeeded = *iterList;
	iterWB->second.erase(iterList);
	wordBunch_[iterWB->first + 1].push_front(wordNeeded);
	if (iterWB->second.size() == 0) {
		wordBunch_.erase(iterWB);
	}
	return wordNeeded;
}

void TrieNode::addSon(char key) {
	sons_[keyCode(key)] = new TrieNode();
}

void TrieNode::addWord(const Word & word) {
	wordBunch_[word.getFrequency()].push_back(word.getWord());
}

void TrieNode::deleteSubTree() {
	for (int son = 0; son < sons_.size(); ++son) {
		if (sons_[son] != NULL) {
			sons_[son]->deleteSubTree();
			delete sons_[son];
		}		
	}
}

class Trie {
public:
	Trie(): root_(new TrieNode()) {}
	~Trie() {
		root_->deleteSubTree();
		delete root_; 
	}
	void add(const Word & word);
	const string findWord (const string & keySequence, int variant) const;
private:
	TrieNode * root_;
};

void Trie::add(const Word & word) {
	string keySequence = word.getKeySequence();
	int key = 0;
	TrieNode * wordPlace = root_;
	while (key < keySequence.size()) {
		if (wordPlace->getSon(keySequence[key]) == NULL) {
			wordPlace->addSon(keySequence[key]);
		}
		wordPlace = wordPlace->getSon(keySequence[key]);
		++key;
	}
	wordPlace->addWord(word);
}

const string Trie::findWord(const std::string & keySequence, int variant) const {
	int key = 0;
	TrieNode * wordPlace = root_;
	while (key < keySequence.size()) {
		wordPlace = wordPlace->getSon(keySequence[key]);
		++key;
	}
	
	return wordPlace->getWord(variant);
}

/*
Определение класса Т9
*/

typedef Trie Vocabulary;

class T9 {
public:
	T9();
	const string processKeySequence(const string & keySequence) const;
	void init();
private:
	Vocabulary vocabulary_;
	bool readNextPart_ (const string & keySequence, int * position, string * nextPart, int * variant, char * punctuation) const;
};


T9::T9(): vocabulary_(Vocabulary()) {}

void T9::init () {
	int vocabularySize = 0;
	cin >> vocabularySize;
	for (int wordNumber = 0; wordNumber < vocabularySize; ++wordNumber) {
		Word newWord = readWord();
		vocabulary_.add(newWord);
	}
}

bool T9::readNextPart_(const std::string &keySequence, int * position, std::string *nextPart, int *variant, char *punctuation) const {
	*nextPart = "";
	*variant = 0;
	*punctuation = ' '; 
	while (isDigit(keyCode(keySequence[*position]))) {
		*nextPart += keySequence[*position];
		++(*position);
	}
	if (keySequence[*position] == '*')  {
		while (keySequence[*position] == '*') {
			++(*variant);
			++(*position);
		}
	}
	if (keySequence[*position] == '1') {
		++*position;
		*punctuation = getPunctuation(keySequence, position);
	}
	++(*position);
	if (*position >= keySequence.size()) {
		return false;
	} else {
		return true;
	}
}

const string T9::processKeySequence(const string& keySequence) const {
	const bool EndOfSequence = false;
	int position = 0;
	string nextPart = "";
	int variant = 0;
	char punctuation = ' ';
	string finalPhrase = "";
	while (readNextPart_(keySequence, &position, &nextPart, &variant, &punctuation) != EndOfSequence) {
		finalPhrase += vocabulary_.findWord(nextPart, variant);
		if (punctuation != ' ') {
			finalPhrase += punctuation;
			finalPhrase += ' ';
		} else {
			finalPhrase += ' ';
		}
	}
	if (nextPart != "") {
		finalPhrase += vocabulary_.findWord(nextPart, variant);
	}
	if (punctuation != ' ') {
		finalPhrase += punctuation;
	}
	return finalPhrase;
}

string readKeySequence() {
	string keySequence;
	cin >> keySequence;
	string temp;
 	getline(cin, temp);
	keySequence += temp;
	return keySequence;
}


int main() {
	T9 T9Device;
	T9Device.init();
	string keySequence = readKeySequence();
	cout << T9Device.processKeySequence(keySequence) << endl;
	return 0;
}
