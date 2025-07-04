#include <iostream>
#include <string>
#include <vector>

const int MAX_WORD_LEN = 20;
const int VALUES = 8;

struct Word_node {
	Word_node* next;
	Word_node* prev;
	std::string word;
	int freq;
	Word_node (const std::string &wr, const int fq) : word (wr), freq (fq), prev (0), next (0) {};
};

struct T9_node {
	Word_node* first;
	std::vector< T9_node* > deep;
	T9_node () : first (0), deep (VALUES) {};
};

class T9 {
	private:
	int words;
	std::vector < T9_node* > dict;
	char one[3];
	int letter[26];
	void delete_deep (T9_node* todelete);
	
	public:
	T9 ();
	~T9 ();
	void insert_word (const std::string &wr, const int fq);
	void process (const std::string &line);
};

T9::T9 () {
	dict.resize (VALUES);
	
	one[0] = '.';
	one[1] = ',';
	one[2] = '?';
	
	letter[0] = 0;
	letter[1] = 0;
	letter[2] = 0;
	letter[3] = 1;
	letter[4] = 1;
	letter[5] = 1;
	letter[6] = 2;
	letter[7] = 2;
	letter[8] = 2;
	letter[9] = 3;
	letter[10] = 3;
	letter[11] = 3;
	letter[12] = 4;
	letter[13] = 4;
	letter[14] = 4;
	letter[15] = 5;
	letter[16] = 5;
	letter[17] = 5;
	letter[18] = 5;
	letter[19] = 6;
	letter[20] = 6;
	letter[21] = 6;
	letter[22] = 7;
	letter[23] = 7;
	letter[24] = 7;
	letter[25] = 7;
}

T9::~T9 () {
	for (int i = 0; i < VALUES; ++i)
		delete_deep (dict[i]);
}

void T9::delete_deep (T9_node* todelete) {
	if (!todelete) return;
	while (todelete->first) {
		Word_node* todelete_word = todelete->first;
		todelete->first = todelete_word->next;
		if (todelete_word->next) todelete_word->next->prev = 0;
		todelete_word->next = 0;
		delete todelete_word;		
	}
	for (int i = 0; i < VALUES; ++i) delete_deep (todelete->deep[i]);
	delete todelete;
}

void T9::insert_word (const std::string &wr, const int fq) {
	// create word node
	Word_node* new_word = new Word_node (wr, fq);
	
	// find where it belongs
	// fist we start with outer storage;
	std::vector < T9_node* >* cur_dict = &dict;
	T9_node* toinsert;
	// find place to insert
	for (unsigned int i = 0; i < wr.size (); ++i) {
		int pos = letter[wr[i] - 'a'];
		// precond: cur_dict not null
		if (!(*cur_dict)[pos]) {
			// need to create
			T9_node* len_node = new T9_node;
			toinsert = len_node;
			(*cur_dict)[pos] = len_node;
			cur_dict = &(toinsert->deep);
		}
		else {
			toinsert = (*cur_dict)[pos];
			cur_dict = &(toinsert->deep);
		}
	}
	
	// we need to insert in into toinsert into appropriate position
	if (!toinsert->first) {
		// no word nodes yet
		toinsert->first = new_word;
		return;
	}
	// highest frequency
	if ((fq > toinsert->first->freq) || (fq == toinsert->first->freq && wr <= toinsert->first->word)) {
		new_word->next = toinsert->first;
		toinsert->first->prev = new_word;
		toinsert->first = new_word;
		return;
	}
	
	Word_node* before = toinsert->first;
	while (before->next) {
		if ((fq == before->freq && fq == before->next->freq && wr < before->next->word) || (fq > before->next->freq)) {
			new_word->next = before->next;
			new_word->prev = before;
			before->next->prev = new_word;
			before->next = new_word;
			return;
		}
		before = before->next;
	}
	// last in the list
	new_word->prev = before;
	before->next = new_word;
}

void T9::process (const std::string &line) {
	// find word node used for print and reinsert
	Word_node* find_word;
	std::vector < T9_node* >* cur_dict;
	T9_node* tofind;
	
	for (unsigned int i = 0; i < line.size (); ++i) {
		// might be some ' ' skip
		while (i < line.size () && line[i] == ' ') {
			std::cout << ' ';
			++i;
		}
		if (i == line.size ()) return;
		
		if (line[i] == '1') {
			int punct = 0;
			++i;
			while (i < line.size () && line[i] == '*') {
				++i;
				++punct;
			}
			std::cout << one[punct];
			if (i < line.size () && line[i] == ' ') std::cout << ' ';
			continue;
		}
		
		// new set of words
		cur_dict = &dict;
		// search for the T9_node
		// find place to insert
		while (i < line.size () && line[i] != '*' && line[i] != '1' && line[i] != ' ') {
			int pos = line[i] - '0' - 2;
			// precond: cur_dict not null
			tofind = (*cur_dict)[pos];
			find_word = tofind->first;
			cur_dict = &(tofind->deep);
			++i;
		}
		
		// ACCESS
		while (i < line.size () && line[i] == '*') {
			find_word = find_word->next;
			++i;
		}
		
		// UPDATE!!!!!!!!!!!
		++find_word->freq;
		// check if update is needed
		if (find_word != tofind->first && find_word->prev->freq <= find_word->freq) { // update needed
			Word_node* before = find_word->prev;
			// remove it from the list
			before->next = find_word->next;
			if (find_word->next) find_word->next->prev = before;
			find_word->next = 0;
			find_word->prev = 0;
			
			// switch with first
			if (find_word->freq >= tofind->first->freq) {
				find_word->next = tofind->first;
				tofind->first->prev = find_word;
				tofind->first = find_word;
				before = 0;
			}
			while (before) {
				if (before->freq > find_word->freq) {
					find_word->prev = before;
					find_word->next = before->next;
					if (before->next) before->next->prev = find_word;
					before->next = find_word;
					break;
				}
				before = before->prev;
			}
		}
		
		// PRINT
		std::cout << find_word->word;
		if (i < line.size () && line[i] == '1') {
			int punct = 0;
			++i;
			while (i < line.size () && line[i] == '*') {
				++i;
				++punct;
			}
			std::cout << one[punct];
		}
		if (i < line.size () && line[i] == ' ') std::cout << ' ';
	}
}

int main () {
	T9 t9;
	int N, fq;
	std::string word;
	
	std::cin >> N;
	for (int i = 0; i < N ; ++i) {
		std::cin >> word >> fq;
		t9.insert_word (word, fq);
	}
	getline (std::cin, word);
	getline (std::cin, word);
	t9.process (word);
	return 0;
}