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
       (*dictionary)[code].insert(w_e);
     }
   }
 }

 string get_word(const string& word, size_t index, size_t stars_count, dict* dictionary) {
   dict_entry::iterator beg = (*dictionary)[word].begin();
   for (size_t offset= 0; offset < stars_count % (*dictionary)[word].size(); ++offset) {
     ++beg;
   }
   word_entry to_update(*beg);
   ++to_update.frequency;
   ++to_update.insert_index = ++index;
   (*dictionary)[word].erase(beg);
   (*dictionary)[word].insert(to_update);
   return to_update.word;
 }

string get_request_string() {
	std::cin.get();

	string request_string;
	std::getline(std::cin, request_string);

	return request_string;
}

string get_result(dict* dictionary, const string& request) {
  string result;
  size_t w_i = 0;
  string::const_iterator it = request.begin();
  while (it != request.end()) {
    if (it != request.end() && *it == ' ') {
      result += " ";
      ++it;
    } else if (*it == '1') {
      size_t stars_count = 0;
      while(++it != request.end() && *it == '*') {
        ++stars_count;
      }
      stars_count = stars_count % 3;
      switch (stars_count) {
        case 0: result += ".";
                break;
        case 1: result += ",";
                break;
        case 2: result += "?";
                break;
        default: break;
      }
    } else {
      string::const_iterator beg = it;
      while (it != request.end() && *it != '1' && *it != ' ' && *it != '*') {
        ++it;
      }
      string::const_iterator end = it;
      string word(beg, end);
      size_t stc = 0;
      while(*it == '*') {
        ++stc;
        ++it;
      }
      result += get_word(word, w_i, stc, dictionary);
      ++w_i;
    }
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