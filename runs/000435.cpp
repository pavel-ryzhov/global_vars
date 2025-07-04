#include <iostream>
#include <string>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

class T9Keyboard {
		
	class Word_list{
		map<int, list<string*> > words;
		size_t sz;
	public:
			
		class Word {
			friend class Word_list;
			map<int, list<string*> >::reverse_iterator mi;
			list<string*>::iterator li;
		public:
			int freq() const { return mi->first; }
			string* str() const { return *li; }
		};
		
		~Word_list();
		
		size_t size() { return sz; }
		
		Word get(int offset);
		void add(const string& s, int freq);
		void move(const Word& w, int new_freq);
	};
		
	void split_terms(string seq, list<string>& words);
	inline string get_punct(string seq);
	string get_word(string seq);

	static const int letter[];
	map<string, Word_list> dict;
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

T9Keyboard::Word_list::~Word_list()
{
	map<int, list<string*> >::iterator mi;
	for (mi = words.begin(); mi != words.end(); ++mi) {
		list<string*>& lst = mi->second;
		for (list<string*>::iterator li = lst.begin(); li != lst.end(); ++li)
			delete *li;
	}
}

void T9Keyboard::Word_list::add(const string& s, int freq)
{
	words[freq].push_back(new string(s));
	sz++;
}

void T9Keyboard::Word_list::move(const Word& w, int new_freq)
{
	words[new_freq].push_front(w.str());
	w.mi->second.erase(w.li);
}

T9Keyboard::Word_list::Word T9Keyboard::Word_list::get(int offset)
{
	Word w;
	int sz;
	for (w.mi = words.rbegin(); w.mi != words.rend(); ++w.mi, offset -= sz) {
		sz = w.mi->second.size();
		if (sz > offset)
			break;
	}
		
	for (w.li = w.mi->second.begin(); offset > 0; ++w.li, --offset)
		;
	return w;
}

void T9Keyboard::add_word(const string& word, int freq)
{
	string seq;
	for (size_t i = 0; i < word.size(); ++i) {
		seq += '0' + letter[word[i] - 'a'];
	}

	Word_list& wl = dict[seq];
	wl.add(word, freq);
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
	size_t pos = seq.find('*');
	if (pos == string::npos)
		pos = seq.size();
	
	// get list of words with given combination of digits
	Word_list& wl = dict[seq.substr(0, pos)];
	if (wl.size() == 0)
		return "";

	// there are only asterisks after digit sequence
	int no_asterisks = seq.substr(pos).size();
	int offset = no_asterisks % wl.size();
		
	Word_list::Word word = wl.get(offset);
	string *s = word.str();
	wl.move(word, word.freq()+1);

	return *s;
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
		if (!isspace(ch)) {
			cin.unget();
			cin >> seq;
			cout << t9.get(seq);
		} else
			cout << ch;
		cin.get(ch);
	}
	
	return 0;
}