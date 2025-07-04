#include <iostream>
#include <map>
#include <string>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;

class SmsRecognition {
	map<string, list<pair<string, int> > > words_;
	string sms_;

public:
	SmsRecognition() {		
	  // freopen("input.txt", "r", stdin); 
		int word_count;
		vector<pair<string, int> > words_to_weight;
		cin >> word_count;
		for (int i = 0; i < word_count; ++i) {
			string word;
			int weight;
			cin >> word >> weight;
		  words_to_weight.push_back(make_pair(word, weight));		
		}
		sort(words_to_weight.begin(), words_to_weight.end(), &pair_cmp);
		getline(cin, sms_);
		getline(cin, sms_);
		create_map(words_to_weight);
	}
	
	static bool pair_cmp(const pair<string, int> &le, const pair<string, int> &ri) {
		if (le.second != ri.second) {
			return le.second > ri.second;
		}
		return le.first < ri.first;
	}

	void create_map(const vector<pair<string, int> > &words_to_weight) {
		map<string, list<pair<string, int> > >::iterator it;
		for (int i = 0; i < words_to_weight.size(); ++i) {
			const pair<string, int> &cur_word = words_to_weight[i];
			string number_seq = get_number_seq(cur_word.first);
			it = words_.find(number_seq);
			if (it == words_.end()) {
				list<pair<string, int> > new_list;
				new_list.push_back(cur_word);
				words_.insert(make_pair(number_seq, new_list));
			} else {
				it->second.push_back(cur_word);
			}
		}	
	}

	string get_number_seq(const string &word) {	
		string numbers;
		for (int i = 0; i < word.length(); ++i) {
			switch (word[i]) {
				case 'a':
				case 'b': 
				case 'c': numbers += "2"; break;
				case 'd':
				case 'e':
				case 'f': numbers += "3"; break;
				case 'g':
				case 'h':
				case 'i': numbers += "4"; break;
				case 'j':
				case 'k':
				case 'l': numbers += "5"; break;
				case 'm':
				case 'n':
				case 'o': numbers += "6"; break;
				case 'p':
				case 'q':
				case 'r':
				case 's': numbers += "7"; break;
				case 't':
				case 'u':
				case 'v': numbers += "8"; break;
				case 'w':
				case 'x':
				case 'y':
				case 'z': numbers += "9";
			}
		}
		return numbers;
	}

    inline bool is_word_digit(char ch) {
        return ch >= '2' && ch <= '9';
    }

	string sms_recognize() {
		string out_str;
		int first_pos = 0;
		int change_count = 0;	
		string cur_word;		
		for (int i = 0; i < sms_.length(); ++i) {
			if (sms_[i] == '*') {
				++change_count;
			} else if (sms_[i] == ' ' || sms_[i] == '1') {
				if (first_pos < i - change_count) {
					cur_word = get_word(sms_.substr(first_pos, i - first_pos - change_count), change_count);				
					out_str.append(cur_word);
				} else {
					for (int i = 0; i < change_count; ++i) {
						out_str.append("*");
					}
				}
                if (sms_[i] == ' ') {
				    out_str.append(" ");
				    first_pos = i + 1;
                } else {
                    first_pos = i;
                }
				change_count = 0;
			} else if (is_word_digit(sms_[i]) && i > 0 && !is_word_digit(sms_[i-1])) {
				if (first_pos < i - change_count) {
					cur_word = get_word(sms_.substr(first_pos, i - first_pos - change_count), change_count);				
					out_str.append(cur_word);
				} else {
					for (int i = 0; i < change_count; ++i) {
						out_str.append("*");
					}
				}
                first_pos = i;
                change_count = 0;
            }
		}
		if (sms_[sms_.length() - 1] != ' ') {
			if (first_pos < sms_.length() - change_count) {
				cur_word = get_word(sms_.substr(first_pos, sms_.length() - change_count - first_pos), change_count);
				out_str.append(cur_word);
			} else {
					for (int i = 0; i < change_count; ++i) {
						out_str.append("*");
					}
			}
		}	
		return out_str;
	}

	string get_word(const string &numbers, int change_count) {
		if (numbers[0] == '1') {
			change_count %= 3;
			switch(change_count) {
				case 0: return "."; 
				case 1: return ",";
				case 2: return "?";
			}
		}
		map<string, list<pair<string, int> > >::iterator map_it;
		map_it = words_.find(numbers);
		list<pair<string, int> > &rel_words = map_it->second;
		list<pair<string, int> >::iterator list_it = rel_words.begin();
		if (change_count >= rel_words.size()) {
			change_count %= rel_words.size();
		}
		for (int i = 0; i < change_count; ++i) {
		  ++list_it;			
		}
		//word to return
		string word = list_it->first;
		//update dictionary
		list_it->second = list_it->second + 1;
		list<pair<string, int> >::iterator list_it_to = list_it;
		while (list_it_to != rel_words.begin() && (--list_it_to)->second <= list_it->second);
		if (list_it_to->second > list_it->second) {
			++list_it_to;
		}
		rel_words.splice(list_it_to, rel_words, list_it);
		

		return word;
	}	
} smsRecognizer;

int main() {
	string answer = smsRecognizer.sms_recognize();
  cout << answer;
}
