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

// Модуль list.h
#ifndef PLIST_H
#define PLIST_H

template<typename T>
class List_node {
public:
	List_node() : Instance(0), Next(0), Previous(0) {}
public:
	T Instance;
	List_node* Next;
	List_node* Previous;
};

template<typename _Val>
class List {
public:
	typedef List_node<_Val> list_node;
public:
	List() { m_Head = 0; m_Back = 0; m_Size = 0; }
	~List() { }

	list_node* insert(list_node* pos, _Val value) {
		list_node* node = new list_node();
		node->Instance = value;

		m_Size++;
		if (pos) {	
			list_node* T = pos->Next;
			if (T) { 
				T->Previous = node;
			}
			else {
				m_Back = node;
			}
			pos->Next = node;

			node->Next = T;
			node->Previous = pos;

		}
		else if (!m_Head) {
			m_Head = node;
			m_Back = node;
		}
		return node;
	}
	list_node* insert_before(list_node* pos, _Val value) {
		list_node* node = new list_node();
		node->Instance = value;

		m_Size++;
		if (pos) {
			
			if (pos->Previous) {
				pos->Previous->Next = node;
			}
			else { 
				m_Head = node; 
			}
			node->Previous = pos->Previous;
			node->Next = pos;
			pos->Previous = node;
		}
		else if (!m_Head) {
			m_Head = node;
			m_Back = node;
		}
		return node;
	}
	
	list_node* push_back(_Val value) {
		return insert(m_Back, value);
	}
	list_node* push_front(_Val value) {
		return insert_before(m_Head, value);
	}

	void remove(_Val value) {
		_del(_find(value));
	}

	void _del(list_node* value) {
		if (!value) return;
		if (!m_Head) return;

		m_Size--;

		list_node* node = value;
		if (node == m_Head)
		{
			m_Head = node->Next;
			if (m_Head) m_Head->Previous = 0;
			delete node;
			return;
		}
		list_node* T = m_Head;
		while (T->Next != node)
		{
			T = T->Next;
			if (T == 0) return;
		}
		T->Next = node->Next;
		if (node->Next)	node->Next->Previous = T;
		if (!T->Next) m_Back = T;
		delete node;
	}
	list_node* _find(_Val value)
	{
		if (!value) return 0;
		if (!m_Head) return 0;

		if (value == m_Head->Instance)
		{
			return m_Head;
		}
		list_node* T = m_Head;

		while (T->Next)
		{
			T = T->Next;
			if (T->Instance == value) break;
			if (T->Next == 0) { T = 0; break; }
		}
		return T;
	}

	template<typename _Pred>
	_Val rfind(_Pred pred, list_node* &pos, bool &is_before) {
		_Val res = 0;
		pos = 0;
		list_node* T = m_Back;
		if (T) {
			if (pred(T->Instance)) { 
				res = T->Instance;  return res; 
			}
			else {
				pos = T;
				if (pred < T->Instance) {
					is_before = true; 
				}
				else {
					is_before = false;
					return res;
				}
			}
			while (T->Previous)
			{
				if (pred(T->Instance)) { 
					res = T->Instance;  break; 
				}
				else {
					pos = T;
					if (pred < T->Instance) {
						is_before = true; 
					}
					else {
						is_before = false;
						return res;
					}
				}
				T = T->Previous;
				if (!T->Previous) {
					if (pred(T->Instance)) { 
					res = T->Instance;  break; 
					}
					else {
						pos = T;
						if (pred < T->Instance) {
							is_before = true; 
						}
						else {
							is_before = false;
							return res;
						}
					}
				}
			}
		}
		return res;
	}
	int size() { return m_Size; }

public:
	list_node* m_Back;
	list_node* m_Head;
	int m_Size;
};

#endif

// Модуль wordNest.h
#ifndef WORD_NEST_H
#define WORD_NEST_H

class WordPriorityBasket : public List<Word*> {
public:
	int m_Priority;
};

struct WordPriorityBasket_equal
{
public:
	WordPriorityBasket_equal(int priority) : arg(priority) {}
	bool operator()(WordPriorityBasket* _val) const	{
		return _val->m_Priority == arg;
	}
	template<typename T>
	bool operator<(T _val) const {
		return arg < _val->m_Priority;
	}
private:
	int arg;
};

class WordNest {
public:
	WordNest() {}
	~WordNest() {}

	void add(Word* word) {
		int priority = word->getPriority();
		
		bool is_before = false;
		List<WordPriorityBasket*>::list_node* pos = 0;
		WordPriorityBasket* basket = m_Baskets.rfind(WordPriorityBasket_equal(priority), pos, is_before);
		if (!basket) {
			basket = new WordPriorityBasket();
			basket->m_Priority = priority;
			if (is_before)	m_Baskets.insert_before(pos, basket);
			else m_Baskets.insert(pos, basket);
		}
		basket->push_back(word);
	}

	Word* increasePriorityWordComb(int nComb) {

		int idx = nComb;
		List<WordPriorityBasket*>::list_node* back = m_Baskets.m_Back;
		List<Word*>::list_node* back_word = back->Instance->m_Head;

		while (idx) {
			if (idx >= back->Instance->m_Size) {
				idx -= back->Instance->m_Size;
				do {
					back = back->Previous;
					back_word = back->Instance->m_Head;
				}
				while (!back_word && back);
			}
			else if (back_word) {
				back_word = back_word->Next;
				idx--;
			}
		}
		Word* pWord = back_word->Instance;
		
		if (pWord) {
			back->Instance->remove(pWord);
			pWord->incPriority();
			int priority = pWord->getPriority();
			
			bool is_before = false;
			List<WordPriorityBasket*>::list_node* pos = 0;
			WordPriorityBasket* basket = m_Baskets.rfind(WordPriorityBasket_equal(priority), pos, is_before);
			if (!basket) {
				basket = new WordPriorityBasket();
				basket->m_Priority = priority;
				
				if (is_before)	m_Baskets.insert_before(pos, basket);
				else m_Baskets.insert(pos, basket);
			}
			basket->push_front(pWord);
		}

		return pWord;
	}

private:
	List<WordPriorityBasket*> m_Baskets;
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
		m_CurrentNode = 0;
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
	
	void printWord(int nComb) {
		WordNest* pNest = m_WordTree.endPath();
		Word* pWord = pNest->increasePriorityWordComb(nComb);

		//cout << pWord->toString();
		fputs(pWord->toString().c_str(), stdout);		
	}

public:	

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

public:
	WordKeyTree* WordTree() { return &m_WordTree; }

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
	
	// Считывание входного сообщения
	cin.ignore();

	int nCombItr = 0;
	int nComb = 0;
	bool isMark = false;
	
	char key;
	while (cin.get(key)) {
		if (key == '\n') {
			if (isMark) { 

				putchar(t9.getMark(nComb));

				nComb = 0; 
				isMark = false; 
			}
			if (nCombItr) {
						
				t9.printWord(nComb);

				nComb = 0;
				nCombItr = 0;
			}

			putchar('\n');
			break;
		}
		if (key == '\r') {
			putchar('\r');
			continue;
		}
		if (key == ' ') { 
			if (isMark) { 
				putchar(t9.getMark(nComb));

				nComb = 0; 
				isMark = false; 
			}
			if (nCombItr) {
						
				t9.printWord(nComb);

				nComb = 0;
				nCombItr = 0;
			}
			putchar(' ');

			continue; 
		}
		if (key != t9.mark_key) {
			if (key != t9.next_comb) {
				if (isMark) {
					putchar(t9.getMark(nComb));

					nComb = 0;
				}
				if (!nCombItr) { t9.WordTree()->beginPath(); }
				t9.WordTree()->nextCombKey(key);
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
						
					t9.printWord(nComb);

					nComb = 0;
					nCombItr = 0;
				}
			}
			else {
				putchar(t9.getMark(nComb));

				nComb = 0;
			}
			isMark = true;
		}
	}
	if (isMark) {
		putchar(t9.getMark(nComb));

		nComb = 0; 
	}
	if (nCombItr) {
		t9.printWord(nComb);
		nComb = 0; 
	}

//    int x;
//    cin >> x;
	return 0;
}
