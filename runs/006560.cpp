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

	bool isTopUse() { return m_isTopUse; }
	void setIsTopUse(bool value) { m_isTopUse = value; }

	string toString() { return m_word; }
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
	bool operator()(Word _lhs, Word _rhs) const	{
		if (_lhs.getPriority() == _rhs.getPriority()) {
			if (_lhs.isTopUse()) return true;
			if (_rhs.isTopUse()) return false;
			return _lhs.toString().compare(_rhs.toString()) < 0;
		}
		else {
			return _lhs.getPriority() > _rhs.getPriority();
		}
	}
};

struct word_sort_functor : public binary_function<Word, Word, bool>
{
public:
	bool operator()(Word _lhs, Word _rhs) const	{
		if (_lhs.getPriority() == _rhs.getPriority()) {
			if (_lhs.isTopUse()) return true;
			if (_rhs.isTopUse()) return false;
		}
		return _lhs.getPriority() > _rhs.getPriority();
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

#endif

// Модуль wordNest.h
#ifndef WORD_NEST_H
#define WORD_NEST_H

class WordNest : public vector<Word> {
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

	void add_unique(Word word) {
		vector<Word>::iterator i = find_if(begin(), end(), word_equal(word.toString()));
		if (i == end()) {
			push_back(word);
		}
	}
//
//private:
//	Word* m_TopUseWord;
};

struct word_nest_less : public binary_function<WordNest, WordNest, bool>
{
public:
	bool operator()(const string& _lhs, const string& _rhs) const	{
		return _lhs.compare(_rhs) < 0;
	}
};


#endif

// Модуль t9.h
#ifndef T9_H
#define T9_H

class T9 {
public:
	typedef multimap<int, char> key_map;
	typedef map<string, WordNest, word_nest_less> word_map;
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
		next_comb = '*';
		mark_key = '1';
		mark_key_string = "1";

		mark_dot = '.';
		mark_comma = ',';
		mark_qu = '?';

		m_keyBoard.insert(make_pair(1, mark_dot));
		m_keyBoard.insert(make_pair(1, mark_comma));
		m_keyBoard.insert(make_pair(1, mark_qu));

		m_keyBoard.insert(make_pair(2, 'a'));
		m_keyBoard.insert(make_pair(2, 'b'));
		m_keyBoard.insert(make_pair(2, 'c'));

		m_keyBoard.insert(make_pair(3, 'd'));
		m_keyBoard.insert(make_pair(3, 'e'));
		m_keyBoard.insert(make_pair(3, 'f'));

		m_keyBoard.insert(make_pair(4, 'g'));
		m_keyBoard.insert(make_pair(4, 'h'));
		m_keyBoard.insert(make_pair(4, 'i'));

		m_keyBoard.insert(make_pair(5, 'j'));
		m_keyBoard.insert(make_pair(5, 'k'));
		m_keyBoard.insert(make_pair(5, 'l'));

		m_keyBoard.insert(make_pair(6, 'm'));
		m_keyBoard.insert(make_pair(6, 'n'));
		m_keyBoard.insert(make_pair(6, 'o'));

		m_keyBoard.insert(make_pair(7, 'p'));
		m_keyBoard.insert(make_pair(7, 'q'));
		m_keyBoard.insert(make_pair(7, 'r'));
		m_keyBoard.insert(make_pair(7, 's'));

		m_keyBoard.insert(make_pair(8, 't'));
		m_keyBoard.insert(make_pair(8, 'u'));
		m_keyBoard.insert(make_pair(8, 'v'));

		m_keyBoard.insert(make_pair(9, 'w'));
		m_keyBoard.insert(make_pair(9, 'x'));
		m_keyBoard.insert(make_pair(9, 'y'));
		m_keyBoard.insert(make_pair(9, 'z'));
	}
	~T9() {}

	void insert(string word, int priority) {
		string comb;
		for (string::iterator i = word.begin(); i != word.end(); i++) {
			string::reference ch = (*i);

			for(T9::key_map::iterator k = m_keyBoard.begin();
				k != m_keyBoard.end(); k++) {
					if ((*k).second == ch) {
						int c = (*k).first;
						stringstream ss;
						ss << c;
						comb.push_back(ss.str()[0]);
						break;
					}
			}
		}

		Word w(word);
		w.setPriority(priority);

		m_WordMap[comb].add_unique(w);
	}

	void endDictinary() {
		for(T9::word_map::iterator i = m_WordMap.begin();
				i != m_WordMap.end(); i++) {
					(*i).second.alphavit_sort();
		}
	}

	string getWord(string code) {
		if (code.empty()) return "";

		string result;
		T9::word_data_vector wordData = getWordData(code);

		T9::word_data_vector::iterator i = wordData.begin(); 
		while (i != wordData.end()) {
			if ((*i).first != mark_key_string) {
				T9::word_data data = *i;

				if (data.second < m_WordMap[data.first].size()) {
					Word* pWord = &m_WordMap[data.first][data.second];

					pWord->setIsTopUse(true);
					pWord->setPriority(pWord->getPriority() + 1);

					result = pWord->toString();

					m_WordMap[data.first].sort();
					m_WordMap[data.first][0].setIsTopUse(false);
				}
				i++;
			}
			else {
				int mark_itr = (*i).second / 3;
				int mark_type = (*i).second - mark_itr * 3;
			
				switch (mark_type) {
					case 0: result.push_back(mark_dot); break;
					case 1: result.push_back(mark_comma); break;
					case 2: result.push_back(mark_qu); break;
					default: result.push_back('%'); break;
				}
				i++;
			}
		}

		return result;
	}

private:
	T9::word_data_vector getWordData(string& code) {
		T9::word_data_vector r;
		string buf;
		int nComb = 0;
		bool isMark = false;
		for (string::iterator i = code.begin(); i != code.end(); i++) {
			if ((*i) != mark_key) {
				if ((*i) != next_comb) {
					if (isMark) {
						r.push_back(pair<string, int>(mark_key_string, nComb));
						nComb = 0;
					}
					buf.push_back(*i);
					isMark = false;
				}
				else {
					nComb++;
				}
			}
			else {
				if (!isMark) {
					if (!buf.empty()) {
						r.push_back(pair<string, int>(buf, nComb));
						nComb = 0;
						buf.clear();
					}
				}
				else {
					r.push_back(pair<string, int>(mark_key_string, nComb));
					nComb = 0;
				}
				isMark = true;
			}
		}
		if (isMark) { r.push_back(pair<string, int>(mark_key_string, nComb)); nComb = 0; }
		if (!buf.empty()) { r.push_back(T9::word_data(buf, nComb)); nComb = 0; }
		return r;
	}

protected:
	key_map m_keyBoard;
	word_map m_WordMap;
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
			cout << t9.getWord(code);
			cout << " ";

			isNextWord = true;
		}
		else if (isNextWord) {
			ibegin = itr;

			isNextWord = false;
		}
	}
	string tail(ibegin, input.end());
	cout << t9.getWord(tail) << endl;

	return 0;
}
