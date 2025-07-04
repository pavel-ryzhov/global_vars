
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>

using std::vector;
using std::cout;
using std::string;
using std::map;
using std::multiset;

const char kSpace = ' ';
const char kPunctuation = '1';
const char kNextSuggest = '*';

const char kPunctuationPeriod = '.';
const char kPunctuationComma = ',';
const char kPunctuationQuestion = '?';

// Punctuation Types in order of suggestion by the system.
const char kPunctuationTypes[] = {
  kPunctuationPeriod, 
  kPunctuationComma, 
  kPunctuationQuestion
};

struct DictionaryItem {
  string word;
  int frequency;
  DictionaryItem() { }
  DictionaryItem(const string& _word, const int _frequency) 
      : word(_word), frequency(_frequency) { }
  ~DictionaryItem() { }
};

const int kMaxQueryLength = 100000;

void Input(vector<DictionaryItem>* dictionary, string* query) {
  int number_of_words = -1;
  std::cin >> number_of_words;
  if (number_of_words > 0) {
    dictionary->resize(number_of_words);
    for (int k = 0; k < number_of_words; ++k) {
      std::cin >> (*dictionary)[k].word
               >> (*dictionary)[k].frequency;
    }
    char buffer[kMaxQueryLength + 1];
    std::cin.ignore();
    std::cin.getline(buffer, kMaxQueryLength);
    query->append(buffer);
  }
}

void Output(const vector<int>& queries_results) {
  vector<int>::const_iterator it = queries_results.begin();
  while (it != queries_results.end()) {
    cout << *it++ << std::endl;
  }
}

void ConvertWordToDigits(const string& word, string* _digits) {
  string& digits = *_digits;
  digits.resize(word.size());
  for (int i = 0; i < static_cast<int>(word.length()); ++i) {
    switch(word[i]) {
      case 'a':
      case 'b':
      case 'c':
        digits[i] = '2';
        break;
      case 'd':
      case 'e':
      case 'f':
        digits[i] = '3';
        break;
      case 'g':
      case 'h':
      case 'i':
        digits[i] = '4';
        break;
      case 'j':
      case 'k':
      case 'l':
        digits[i] = '5';
        break;
      case 'm':
      case 'n':
      case 'o':
        digits[i] = '6';
        break;
      case 'p':
      case 'q':
      case 'r':
      case 's':
        digits[i] = '7';
        break;
      case 't':
      case 'u':
      case 'v':
        digits[i] = '8';
        break;
      case 'w':
      case 'x':
      case 'y':
      case 'z':
        digits[i] = '9';
        break;
    }
  }
}

// Checks c to be a digit that corresponds to a letter
// (all digits except 1).
bool IsDigit(char c) {
  return (isdigit(c) && (c != kPunctuation));
}

// Checks c to be punctuation mark (digit 1).
bool IsPunctuation(char c) {
  return (c == kPunctuation);
}

// Checks c to be suggestion mark (the asterisk).
bool IsSuggestion(char c) {
  return (c == kNextSuggest);
}

// Checks c to be space.
bool IsSpace(char c) {
  return (c == kSpace);
}

// Sort items by frequency.
struct greater_frequency {
  bool operator() (const DictionaryItem& x, const DictionaryItem& y) const {
    return x.frequency > y.frequency;
  } 
};

typedef multiset<DictionaryItem, greater_frequency> SetSortedByFrequency;
typedef map <string, SetSortedByFrequency > DigitDictionary;

// Seeks for the end of the current input word. Advances the iterator
// to point to the next character after the word
string ParseWordFromDictionary(const string& query, 
                               string::const_iterator& iter, 
                               DigitDictionary& dictionary) {
  // Mark word beginning. 
  string::const_iterator begin = iter;
  // Seek for end
  while ((iter != query.end()) && IsDigit(*iter)) {
    iter++;
  }
  // Mark word end. 
  string::const_iterator end = iter;

  // Copy range of characters to digits string.
  string digits;
  digits.assign(begin, end);

  // Seek for suggestions.
  while ((iter != query.end()) && IsSuggestion(*iter)) {
    iter++;
  }

  // Search for the digit sequence 
  DigitDictionary::iterator dict_it = dictionary.find(digits);
  SetSortedByFrequency& items = dict_it->second;
  SetSortedByFrequency::iterator item_pointee = items.begin();
  std::advance(item_pointee, std::distance(end, iter));

  // Update the dictionary
  DictionaryItem item = *item_pointee;
  item.frequency++;

  items.erase(item_pointee);
  item_pointee = items.find(item);
  if (item_pointee != items.end()) {
    // Found first item with frequency value of item.frequency
    items.insert(item_pointee, item);
  } else {
    // Found NO item with frequency value of item.frequency
    items.insert(item);
  }
  

  return item.word;
}

// Seeks for the end of the current punctuation mark. Advances the iterator
// to point to the next character after the word.
// NOTE: this function only parses a single punctuation mark!
string ParsePunctuationFromDictionary(const string& query, 
                                      string::const_iterator& iter, 
                                      DigitDictionary& dictionary) {
  // Move to next character (*iter is punctuation mark)
  ++iter;

  const char kPunctuationTypes[] = {
    kPunctuationPeriod, 
    kPunctuationComma, 
    kPunctuationQuestion
  };

  string result;
  // Mark beginning. 
  string::const_iterator begin = iter;
  // Seek for suggestions
  while ((iter != query.end()) && IsSuggestion(*iter)) {
    iter++;
  }
  int character_index = static_cast<int>(std::distance(begin, iter));
  result.append(1, kPunctuationTypes[character_index]);
  return result;
}

// Seeks for the end of spaces. Advances the iterator
// to point to the next character after the spaces (non-space)
string ParseSpacesFromDictionary(const string& query, 
                                 string::const_iterator& iter, 
                                 DigitDictionary& dictionary) {
  string result;
  // Mark beginning. 
  string::const_iterator begin = iter;
  // Seek for the end of spaces
  while ((iter != query.end()) && IsSpace(*iter)) {
    iter++;
  }
  result.assign(begin, iter);
  return result;
}

void InterpretQuery(const vector<DictionaryItem>& dictionary, 
                    const string& query, 
                    string* message) {
  DigitDictionary digit_dictionary;

  vector<DictionaryItem>::const_iterator it;
  for (it = dictionary.begin(); it != dictionary.end(); ++it) {
    string digits;
    ConvertWordToDigits(it->word, &digits);
    DigitDictionary::iterator dict_it;
    if ((dict_it = digit_dictionary.find(digits)) == digit_dictionary.end()) {
      // not found - insert new 
      SetSortedByFrequency items;
      items.insert(*it);
      digit_dictionary.insert(std::pair< string, SetSortedByFrequency >(digits, items));
    } else {
      // found - update 
      SetSortedByFrequency& items = dict_it->second;
      items.insert(*it);
    }
  }

  string::const_iterator iter = query.begin();
  while (iter != query.end()) {
    if (IsDigit(*iter)) {
      string word = ParseWordFromDictionary(query, iter, digit_dictionary);
      message->append(word);
    } else if (IsPunctuation(*iter)){
      string punctuation = ParsePunctuationFromDictionary(query, iter, digit_dictionary);
      message->append(punctuation);
    } else {
      string spaces = ParseSpacesFromDictionary(query, iter, digit_dictionary);
      message->append(spaces);
    }
  }
}

int main(int argc, char* argv[]) {
  vector<DictionaryItem> dictionary;
  string query;
  Input(&dictionary, &query);

  string message;
  if (!dictionary.empty() && (query.length() > 0)) {
    InterpretQuery(dictionary, query, &message);
  }
  cout << message << std::endl;

  return 0;
}
