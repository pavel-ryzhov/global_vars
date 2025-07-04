#include <iostream>
#include <string>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

class T9Keyboard {
	struct Word {
		Word(const string& txt, int fr): text(txt), freq(fr) {}

		string text;
		int freq;
	};

	static bool compare_freq(const Word& w1, const Word& w2)
	{
		if (w1.freq < w2.freq)
			return true;
		return false;
	}

	void split_terms(string seq, list<string>& words);
	inline string get_punct(string seq);
	string get_word(string seq);

	static const int letter[];
	map<string, list<Word> > dict;
public:
	void add_word(const string& txt, int freq);
	string get(const string& seq);
};

/* numbers of letters from a to z, e.g. letter['d'] == 3 */
const int T9Keyboard::letter[] = {
	2, 2, 2,	3, 3, 3,	4, 4, 4,
	5, 5, 5,	6, 6, 6,	7, 7, 7, 7,
	8, 8, 8,	9, 9, 9, 9
};

void T9Keyboard::add_word(const string& word, int freq)
{
	string seq(word.size(), 0);
	for (size_t i = 0; i < word.size(); ++i) {
		seq[i] = '0' + letter[word[i] - 'a'];
	}

	list<Word>& lst = dict[seq];
	
	// insert word according to its frequency
	Word w(word, freq);
	list<Word>::reverse_iterator i = lower_bound(lst.rbegin(), lst.rend(), w, compare_freq);
	lst.insert(i.base(), w);
}

void T9Keyboard::split_terms(string seq, list<string>& terms)
{	
	size_t pos = 0;

	while (pos != string::npos) {
		seq = seq.substr(pos);
	
		if (seq[0] == '1') { // punctuation mark
			pos = seq.find_first_not_of('*', 1);
		} else { // word
			if ((pos = seq.find_first_of("1*")) != string::npos) {
				if (seq[pos] == '*') {
					pos = seq.find_first_not_of('*', pos);
				}
			}
		}

		terms.push_back(seq.substr(0, pos));		
	}
}

string T9Keyboard::get(const string& seq)
{
	string result;
	list<string> terms;
	split_terms(seq, terms);
	for (list<string>::iterator i = terms.begin(); i != terms.end(); ++i) {
		if ((*i)[0] == '1') // punctuation mark
			result += get_punct(*i);
		else
			result += get_word(*i);
	}
	return result;
}

/* returns punctuation mark according to the asterisks count in a string */
string T9Keyboard::get_punct(string seq)
{
	const char mark[] = ".,?";
	size_t pos = (seq.size()-1) % 3;
	return string(1, mark[pos]);
}

string T9Keyboard::get_word(string seq)
{
	int pos = seq.find('*');
	if (pos == string::npos)
		pos = seq.size();
	
	// get list of words with given combination of digits
	list<Word>& lst = dict[seq.substr(0, pos)];
	if (lst.size() == 0)
		return "";

	// there are only asterisks after digit sequence
	int no_asterisks = seq.substr(pos).size();
	int offset = no_asterisks % lst.size();
	
	// find word with the current offset
	list<Word>::iterator item;
	for (item = lst.begin(); offset > 0; ++item, --offset)
		;
	item->freq++;

	// move the word to the top of its frequency group
	list<Word>::reverse_iterator ritem(item);
	list<Word>::reverse_iterator fst = upper_bound(ritem, lst.rend(), *item, compare_freq);
	if (fst != ritem) {
		item = lst.insert(fst.base(), *item);
		lst.erase(ritem.base());
	}
	
	return item->text;
}

int main()
{
	T9Keyboard t9;
	int N;

	cin >> N;
	for (int i = 0; i < N; ++i) {
		string txt;
		int freq;
		cin >> txt >> freq;
		t9.add_word(txt, freq);
	}
	
	char ch;
	string seq;

	cin >> ch;
	while (!cin.eof()) {
		if (ch == ' ') {
			if (seq.size() != 0) {
				cout << t9.get(seq);
				seq.clear();
			}
			cout << ch;
		} else
			seq += ch;

		cin.get(ch);
	}
	
	if (seq.size() != 0) {
		cout << t9.get(seq);
		seq.clear();
	}

	return 0;
}