#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;

// Модуль word.h
#ifndef WORD_H
#define WORD_H

// Слово в словаре Т9
class Word {
public:
	Word() : m_relativePriority(0), m_isTopUse(false), m_word()  {}
	Word(string value) : m_relativePriority(0), m_isTopUse(false), m_word(value)  {}
	~Word() {}

	int getPriority() { return m_relativePriority; }
	void setPriority(int value) { m_relativePriority = value; }
	void incPriority() { m_relativePriority++; }

	bool isTopUse() { return m_isTopUse; }
	void setIsTopUse(bool value) { m_isTopUse = value; }

	string& toString() { return m_word; }
	void SetWord(string value) { m_word = value; }

private:
	int m_relativePriority;
	bool m_isTopUse;
	string m_word;
};

#endif

// Модуль wordFunctor.h
#ifndef WORD_FUNCTOR_H
#define WORD_FUNCTOR_H

struct word_alphavit_sort_functor : public binary_function<Word, Word, bool>
{
public:
	bool operator()(Word* _lhs, Word* _rhs) const	{
		if (_lhs->getPriority() == _rhs->getPriority()) {
			if (_lhs->isTopUse()) return true;
			if (_rhs->isTopUse()) return false;
			return _lhs->toString().compare(_rhs->toString()) < 0;
		}
		else {
			return _lhs->getPriority() > _rhs->getPriority();
		}
	}
};

struct word_sort_functor : public binary_function<Word, Word, bool>
{
public:
	bool operator()(Word* _lhs, Word* _rhs) const	{
		if (_lhs->getPriority() == _rhs->getPriority()) {
			if (_lhs->isTopUse()) return true;
			if (_rhs->isTopUse()) return false;
		}
		return _lhs->getPriority() > _rhs->getPriority();
	}
};

struct word_less : public binary_function<Word, Word, bool>
{
public:
	bool operator()(Word& _lhs, Word& _rhs) const	{
		return _lhs.toString().compare(_rhs.toString()) < 0;
	}
};

struct word_equal : public unary_function<Word, bool> {
public:
	word_equal(string value) : arg(value) {}

	bool operator() (Word _val) const {
		return _val.toString().compare(arg) == 0;
	}
private:
	string arg;
};

struct word_free {
public:
	void operator() (const Word* ptr) const {
		delete ptr;
	}
};

#endif

// Модуль wordNest.h
#ifndef WORD_NEST_H
#define WORD_NEST_H

class WordNest : public vector<Word*> {
public:
	WordNest() {}
	~WordNest() {}

//	Word* getTopUseWord() { return m_TopUseWord; }
//	void setTopUseWord(Word* value) { m_TopUseWord = value; }

	void sort() {
		std::stable_sort(begin(), end(), word_sort_functor());
	}

	void alphavit_sort() {
		std::sort(begin(), end(), word_alphavit_sort_functor());
	}

	void add(Word* word) {
		push_back(word);
	}
//
//private:
//	Word* m_TopUseWord;
};

struct word_nest_less : public binary_function<string, string, bool>
{
public:
	bool operator()(const string& _lhs, const string& _rhs) const	{
		return _lhs.compare(_rhs) < 0;
	}
};


#endif

#ifndef WORKKEY_TREE_H
#define WORKKEY_TREE_H

class WordKeyTree_layer;
class WordKeyTree_node {
public:	WordKeyTree_node(): m_NextLayer(0) {}
public:
	WordNest m_WordNest;
	WordKeyTree_layer* m_NextLayer;
};

class WordKeyTree_layer {
public:
	WordKeyTree_layer() {}
	~WordKeyTree_layer() {}

	WordKeyTree_node m_WordKeyTreeNodes[8];
};

class WordKeyTree {
public:
	WordKeyTree() {
		m_Root = new WordKeyTree_layer();
		m_LayerPos = 0;
		m_NestPos = 0;
		m_CurrentNode = 0;
		m_CurrentLayer = 0;
	}
	~WordKeyTree() {
		free_layer(m_Root);
	}
public:
	void beginPath() {
		m_LayerPos = 0;
		m_NestPos = 0;
		m_CurrentLayer = m_Root;
		m_CurrentNode = &m_CurrentLayer->m_WordKeyTreeNodes[0];
	}

	void nextCombKey(char combKey) {
		int combKeyIdx = combKey - 50;

		nextCombIdx(combKeyIdx);
	}

	void nextCombIdx(int combKeyIdx) {
		if (m_LayerPos) {
			if (!m_CurrentNode->m_NextLayer) m_CurrentNode->m_NextLayer = new WordKeyTree_layer();
			m_CurrentLayer = m_CurrentNode->m_NextLayer;
		}
		m_NestPos = combKeyIdx;
		m_CurrentNode = &m_CurrentLayer->m_WordKeyTreeNodes[m_NestPos];

		m_LayerPos++;
	}

	WordNest* endPath() {
		return &m_CurrentNode->m_WordNest;
	}

	void alphavit_sort() {
		alphavit_sort_layer(m_Root);
	}

	void alphavit_sort_layer(WordKeyTree_layer* layer) {
		for (int i = 0; i < 8; i++) {
			if (layer->m_WordKeyTreeNodes[i].m_NextLayer) {
				alphavit_sort_layer(layer->m_WordKeyTreeNodes[i].m_NextLayer);
			}
			layer->m_WordKeyTreeNodes[i].m_WordNest.alphavit_sort();
		}
	}

protected:
	void free_layer(WordKeyTree_layer* layer) {
		for (int i = 0; i < 8; i++) {
			if (layer->m_WordKeyTreeNodes[i].m_NextLayer) {
				free_layer(layer->m_WordKeyTreeNodes[i].m_NextLayer);
			}
		}
		delete layer;
	}

protected:
	WordKeyTree_layer* m_Root;
	int m_LayerPos;
	char m_NestPos;
	WordKeyTree_node* m_CurrentNode;
	WordKeyTree_layer* m_CurrentLayer;
};

#endif

// Модуль t9.h
#ifndef T9_H
#define T9_H

class T9 {
public:
	typedef pair<string, int> word_data;
	typedef vector<word_data> word_data_vector;

	char next_comb;
	char mark_key;
	string mark_key_string;

	char mark_dot;
	char mark_comma;
	char mark_qu;

public:
	T9() {
		m_WordDictinaryItr = 0;
		next_comb = '*';
		mark_key = '1';
		mark_key_string = "1";

		mark_dot = '.';
		mark_comma = ',';
		mark_qu = '?';

		m_keyBoard[0].push_back(mark_dot);
		m_keyBoard[0].push_back(mark_comma);
		m_keyBoard[0].push_back(mark_qu);

		m_keyBoard[1].push_back('a');
		m_keyBoard[1].push_back('b');
		m_keyBoard[1].push_back('c');

		m_keyBoard[2].push_back('d');
		m_keyBoard[2].push_back('e');
		m_keyBoard[2].push_back('f');

		m_keyBoard[3].push_back('g');
		m_keyBoard[3].push_back('h');
		m_keyBoard[3].push_back('i');

		m_keyBoard[4].push_back('j');
		m_keyBoard[4].push_back('k');
		m_keyBoard[4].push_back('l');

		m_keyBoard[5].push_back('m');
		m_keyBoard[5].push_back('n');
		m_keyBoard[5].push_back('o');

		m_keyBoard[6].push_back('p');
		m_keyBoard[6].push_back('q');
		m_keyBoard[6].push_back('r');
		m_keyBoard[6].push_back('s');

		m_keyBoard[7].push_back('t');
		m_keyBoard[7].push_back('u');
		m_keyBoard[7].push_back('v');

		m_keyBoard[8].push_back('w');
		m_keyBoard[8].push_back('x');
		m_keyBoard[8].push_back('y');
		m_keyBoard[8].push_back('z');

		num_c[0] = '1'; 
		num_c[1] = '2';
		num_c[2] = '3';
		num_c[3] = '4';
		num_c[4] = '5';
		num_c[5] = '6';
		num_c[6] = '7';
		num_c[7] = '8';
		num_c[8] = '9';
	}
	~T9() {
		for_each(m_WordDictinary.begin(), m_WordDictinary.end(), word_free()); 
	}

	void insert(string word, int priority) {
		string comb;

		m_WordTree.beginPath();

		for (string::iterator i = word.begin(); i != word.end(); i++) {
			string::reference ch = (*i);
					
			int key = 0;
			if (ch > 'c') key++; 
			if (ch > 'f') key++;
			if (ch > 'i') key++;
			if (ch > 'l') key++;
			if (ch > 'o') key++;
			if (ch > 's') key++;
			if (ch > 'v') key++;
			
			m_WordTree.nextCombIdx(key);
		}

		Word* w = new Word(word);
		w->setPriority(priority);

		m_WordDictinary[m_WordDictinaryItr] = w; m_WordDictinaryItr++;
		
		m_WordTree.endPath()->add(w);
	}

	void beginDictinary(int size) {
		m_WordDictinary.resize(size);
	}

	void endDictinary() {
		m_WordTree.alphavit_sort();
	}


	void getWord(string& code) {

		int code_size = code.size();

		string buf(code);
		code.clear();

		int nCombItr = 0;
		int nComb = 0;
		bool isMark = false;

		for (int i = 0; i < code_size; i++) {
			char key = buf[i];

			if (key != mark_key) {
				if (key != next_comb) {
					if (isMark) {
						code.push_back(getMark(nComb));
						nComb = 0;
					}
					if (!nCombItr) { m_WordTree.beginPath(); }
					m_WordTree.nextCombKey(key);
					nCombItr++;
					isMark = false;
				}
				else {
					nComb++;
				}
			}
			else {
				if (!isMark) {
					if (nCombItr) {
						
						WordNest* pNest = m_WordTree.endPath();

						if (nComb < pNest->size()) {
							Word* pWord = (*pNest)[nComb];

							pWord->setIsTopUse(true);
							pWord->incPriority();

							code.append(pWord->toString());

							pNest->sort();
							(*pNest)[0]->setIsTopUse(false);
						}


						nComb = 0;
						nCombItr = 0;
					}
				}
				else {
					code.push_back(getMark(nComb));
					nComb = 0;
				}
				isMark = true;
			}
		}
		if (isMark) { code.push_back(getMark(nComb)); nComb = 0; }
		if (nCombItr) {
			WordNest* pNest = m_WordTree.endPath();

			if (nComb < pNest->size()) {
				Word* pWord = (*pNest)[nComb];

				pWord->setIsTopUse(true);
				pWord->incPriority();

				code.append(pWord->toString());

				pNest->sort();
				(*pNest)[0]->setIsTopUse(false);
			}

			nComb = 0; 
		}
	}	

private:	

	char getMark(int nComb) {
		int mark_itr = nComb / 3;
		int mark_type = nComb - mark_itr * 3;
			
		switch (mark_type) {
			case 0: return mark_dot; break;
			case 1: return mark_comma; break;
			case 2: return mark_qu; break;
			default: return '%'; break;
		}
	}

protected:
	//word_map m_WordMap;
	WordKeyTree m_WordTree;
	vector<Word*> m_WordDictinary;
	int m_WordDictinaryItr;

	string m_keyBoard[9];
	char num_c[9];
};

#endif

int main(void)
{
	T9 t9;

	int N = -1; // Кол-во слов в словаре
	cin >> N;

	if (N < 0) {
		cout << 0 << endl;
		return 0;
	}

	// Наполнение словаря
	t9.beginDictinary(N);
	
	for (int i = 0; i < N; i++) {
		string word;
		int nPriority = 0;

		cin >> word >> nPriority;

		if (word.empty() || !nPriority) {
			cout << 0 << endl;
			return 0;
		}
		
		t9.insert(word, nPriority);
	}

	// Перестановка слов в словаре согласно приоритету и по алфавиту
	t9.endDictinary();
	
	// Считывание входного сообщения
	string input;

	cin.ignore();
	getline(cin, input);

	// Вырезание из сообщения кодов
	bool isNextWord = false;
	string::iterator ibegin = input.begin();
	for (string::iterator itr = input.begin(); itr != input.end(); itr++) {
		if ((*itr) == ' ') {
			if (isNextWord) { cout << " "; continue; }
			string code(ibegin, itr);

			// Получение слова по коду из словаря
			t9.getWord(code);
			cout << code;
			cout << " ";

			isNextWord = true;
		}
		else if (isNextWord) {
			ibegin = itr;

			isNextWord = false;
		}
	}
	if (!isNextWord) {
		string tail(ibegin, input.end());
		t9.getWord(tail);
		cout << tail << endl;
	}

//    int x;
//    cin >> x;
	return 0;
}
