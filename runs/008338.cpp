#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

using std::string;
using std::set;
using std::map;
using std::pair;
using std::vector;

const string star("*");
const string mark("1");

 struct word_entry {
   size_t insert_index;
   size_t frequency;
      string word;

   word_entry(): insert_index(0), word(""), frequency(0) {}
   word_entry(size_t i_i, string w, size_t f): insert_index(i_i), word(w), frequency(f) {}

   bool operator > (const word_entry& rhv) const {
     if (frequency != rhv.frequency) {
		   return frequency > rhv.frequency;
	   }
	   if (insert_index != rhv.insert_index) {
		   return insert_index > rhv.insert_index;
	   }
	   return word < rhv.word;
   }
 };

 typedef set < word_entry, std::greater < word_entry > > dict_entry;
 typedef map < string, dict_entry > dict;

 string get_code(const string& word) {
   string code;
   for (size_t letter_index = 0; letter_index < word.size(); ++letter_index) {
		 switch(word[letter_index]) {
			 case 'a': case 'b': case 'c': 
				 code += '2';
				 break;
			 case 'd': case 'e': case 'f': 
				 code += '3';
				 break;
			 case 'g': case 'h': case 'i': 
				 code += '4';
				 break;
			 case 'j': case 'k': case 'l': 
				 code += '5';
				 break;
			 case 'm': case 'n': case 'o': 
				 code += '6';
				 break;
			 case 'p': case 'q': case 'r': case 's': 
				 code += '7';
				 break;
			 case 't': case 'u': case 'v': 
				 code += '8';
				 break;
			 case 'w': case 'x': case 'y': case 'z': 
				 code += '9';
				 break;
			 default:
		 		 break;
		 };
   }
   return code;
 }

 void input_dictionary (dict* dictionary) {
   size_t word_count = 0;
   std::cin >> word_count;
   for (size_t insert_index = 0; insert_index < word_count; ++insert_index) {
     string word;
     size_t frequency;
     std::cin >> word >> frequency;
     string code(get_code(word));
     word_entry w_e(0, word, frequency);
     if (dictionary->find(code) == dictionary->end()) {
       dict_entry d_e;
       d_e.insert(w_e);
       dictionary->insert(pair < string, dict_entry > (code, d_e));
     } else {
       dictionary->at(code).insert(w_e);
     }
   }
 }

 string get_word(const string& word, size_t index, size_t stars_count, dict* dictionary) {
   dict_entry::iterator beg = dictionary->at(word).begin();
   for (size_t offset= 0; offset < stars_count % dictionary->at(word).size(); ++offset) {
     ++beg;
   }
   word_entry to_update(*beg);
   ++to_update.frequency;
   ++to_update.insert_index = ++index;
   dictionary->at(word).erase(beg);
   dictionary->at(word).insert(to_update);
   return to_update.word;
 }

string get_request_string() {
	std::cin.get();

	string request_string;
	std::getline(std::cin, request_string);

	return request_string;
}

void split_request(const string& sentence, vector < string >* request) {
  string::const_iterator beg = sentence.begin();
  string::const_iterator end = sentence.begin();
  do {
    string whitespace(" ");
    end = std::find_first_of(beg, sentence.end(), whitespace.begin(), whitespace.end());
    request->push_back(string(beg, end));
    if (end != sentence.end()) {
      beg = end + 1;
    } 
  } while (end != sentence.end());
}

inline bool is_not_star(char c) {
  return c != '*';
}

size_t get_stars_count(const string& code) {
  string::const_iterator beg = std::find_first_of(code.begin(), code.end(), star.begin(), star.end());
  string::const_iterator beg_of_mark = std::find_first_of(code.begin(), code.end(), mark.begin(), mark.end());
  if (beg_of_mark < beg) {
    return 0;
  }
  return std::distance(beg, beg_of_mark);
}

char get_punctuation_mark(const string& code) {
  string::const_iterator beg = std::find_first_of(code.begin(), code.end(), mark.begin(), mark.end());
  if (beg != code.end()) {
    size_t mark_index = (std::distance(beg, code.end()) - 1) % 3;
    switch(mark_index) {
      case 0: return '.';
      case 1: return ',';
      case 2: return '?';
    }
  }
  return ' ';
}

string get_end_of_code(const string& code) {
  string::const_iterator firststar = std::find_first_of(code.begin(), code.end(), star.begin(), star.end());
  string::const_iterator firstmark = std::find_first_of(code.begin(), code.end(), mark.begin(), mark.end());
  string::const_iterator end =  std::distance(code.begin(), firststar - 1) < std::distance(code.begin(), firstmark) ? firststar : firstmark;
  return string(code.begin(), end);
}

string get_result(dict* dictionary, const string& request) {
  vector < string > words;
  split_request(request, &words);
  words.pop_back();
  string result;
  for (size_t i = 0; i < words.size(); ++i) {
    string word = get_end_of_code(words[i]);
    size_t stc = get_stars_count(words[i]);
    char p = get_punctuation_mark(words[i]);
    result += get_word(word, i, stc, dictionary) += p;
  }
  return result;
}

void print_string(const string& result) {
  std::cout << result << std::endl;
}

int main() {
  dict dic;
  input_dictionary(&dic);
  string request = get_request_string();
  string result(get_result(&dic, request));
  print_string(result);
  return 0;
}