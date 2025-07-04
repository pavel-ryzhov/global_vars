#include <list>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class T9Phone {
	private:
		struct Word {
			string word;
			int count;
			bool operator< (const Word &x) const {
				return (count > x.count) || ( (count == x.count) && (word < x.word) );
			};
			Word(string _word, int _count): word(_word), count(_count) {
			};
		};
		map<int, list<Word> > words;
		static int translate_to_digits(const string word) {
			int result(0);
			for (string::const_iterator c = word.begin(); c != word.end(); c++) {
				result *= 10;
				switch (*c) {
					case 'a':
					case 'b':
					case 'c':
						result += 2;
						break;
					case 'd':
					case 'e':
					case 'f':
						result += 3;
						break;
					case 'g':
					case 'h':
					case 'i':
						result += 4;
						break;
					case 'j':
					case 'k':
					case 'l':
						result += 5;
						break;
					case 'm':
					case 'n':
					case 'o':
						result += 6;
						break;
					case 'p':
					case 'q':
					case 'r':
					case 's':
						result += 7;
						break;
					case 't':
					case 'u':
					case 'v':
						result += 8;
						break;
					case 'w':
					case 'x':
					case 'y':
					case 'z':
						result += 9;
						break;
				};
			}
			return result;
		};
		string _type_word(const string &word, const int dots_count) {
			//cout << "_: " << word << " " << dots_count << "\n";
			if (word == "1") {
				switch (dots_count) {
					case 0:
						return ".";
						break;
					case 1:
						return ",";
						break;
					case 2:
						return "?";
						break;
				};
			}
			list<Word> &same_words = words[(atoi(word.c_str()))];
			list<Word>::iterator i(same_words.begin());
			for (int j = 0; j < dots_count; j++, i++);
			string result(i->word);
			int count(i->count + 1);
			same_words.erase(i);
			for (i = same_words.begin(); i != same_words.end() && (i->count > count); i++);
			same_words.insert(i, Word(result, count));
			return result;
		};
	public:
		void add_word(const string &word, const int count) {
			list<Word> &same_words = words[translate_to_digits(word)];
			list<Word>::iterator i;
			for (i = same_words.begin(); i != same_words.end() && (i->count > count); i++);
			same_words.insert(i, Word(word, count));
		};

		void prepare(void) {
			for (map<int, list<Word> >::iterator i = words.begin(); i != words.end(); i++) {
				i->second.sort();
			}
		};

		string type_word(const string &word) {
			//cout << "(" << word << ")" << "\n";
			if (word == " ") {
				return " ";
			}
			list<Word> real_words;
			int dots_count(0);
			unsigned int prev_pos, pos;
			//cout << word << "\n";
			for (prev_pos = pos = 0; pos < word.size(); pos++) {
				if (word[pos] == '*') {
					++dots_count;
				}
				else if (pos && (word[pos] == '1' || dots_count)) {//Наткнулись на единицу или (на цифру, а звездочки уже были)
					real_words.push_back(Word(word.substr(prev_pos, pos - prev_pos - dots_count), dots_count));
					prev_pos = pos;
					dots_count = 0;
				}
			}
			//cout << "prev_pos="  << prev_pos <<" " << "pos=" << pos << " dots_count=" << dots_count << "\n";
			real_words.push_back(Word(word.substr(prev_pos, pos - prev_pos - dots_count), dots_count));
			string result("");
			for (list<Word>::const_iterator i = real_words.begin(); i != real_words.end(); i++) {
				result += _type_word(i->word, i->count);
			}
			return result;
		};

		void print_state(void) {
			for (map<int, list<Word> >::iterator i = words.begin(); i != words.end(); i++) {
				for (list<Word>::iterator j = i->second.begin(); j != i->second.end(); j++) {
					cout << j->word << " " << j->count << "\n";
				}
			}
		};
};

int main(int argc, char *argw[]) {
	int N;
	string s;
	int count;
	cin >> N;
	T9Phone phone;
	for (int i = 0; i < N; i++) {
		cin >> s >> count;
		phone.add_word(s, count);
	}
	phone.prepare();
	//phone.print_state();
	string result;
	getline(cin, s);
	getline(cin, s);
	int prev_pos, pos;
	for (prev_pos = -1, pos = 0; pos < s.size(); ++pos) {
		if (s[pos] == ' ') {
			if (prev_pos != -1) {
				//cout << pos << " " << prev_pos << '\n';
				result += phone.type_word(s.substr(prev_pos, pos - prev_pos));
			}
			result += " ";
			prev_pos = -1;
		}
		else {
			if (prev_pos == -1) {	
				prev_pos = pos;
			}
		}
	}
	if (prev_pos) {
		result += phone.type_word(s.substr(prev_pos, pos - prev_pos));
	}
	cout << result << "\n";
	return 0;
}
