#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using std::stringstream;
using std::istream;
using std::vector;
using std::list;
using std::map;
using std::string;
using std::find;
using std::copy;
using std::advance;
using std::mem_fun_ref;

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

const int kMaxWordLength = 20;
const int kMaxMessageSize = 100000;

class Dictionary {
 // sub-structures
 private:
  struct WordPtrWithFrequency {
    vector<string>::const_iterator word_it_;
    int frequency_;

    WordPtrWithFrequency(vector<string>::const_iterator word_it, int frequency)
        : word_it_(word_it)
        , frequency_(frequency)
        {
    }

    WordPtrWithFrequency(const WordPtrWithFrequency &rhs)
        : word_it_(rhs.word_it_)
        , frequency_(rhs.frequency_)
        {
    }

    ~WordPtrWithFrequency() {
    }

    // like operator>
    bool GenerateIndexOrder(const WordPtrWithFrequency &rhs) const {
      if (frequency_ > rhs.frequency_) {
        return true;
      } else if (rhs.frequency_ > frequency_) {
        return false;
      }
      return *word_it_ < *rhs.word_it_;
    }
  };

  
  struct T9WordAndShift {
    string word_;
    int count_star_key_;

    T9WordAndShift(const T9WordAndShift &rhs)
        : word_(rhs.word_)
        , count_star_key_(rhs.count_star_key_)
        {
    }

    T9WordAndShift(const string &input) {
      string::const_iterator it = find(input.begin(), input.end(), '*');
      count_star_key_ = static_cast<int>(input.end() - it);
      word_.resize(static_cast<int>(it - input.begin()));
      copy(input.begin(), it, word_.begin());
    }
  };

 // class for catch/throw
 public:
  struct BadFormat {
    string word_;
    BadFormat(const string &word) : word_(word) {
    }
  };

 // variables
 private:
  vector<string> words_;

  // use only before generating index
  vector<int> input_frequences_;

  // "235" may contain "adj" and "bel"
  map<string, list<WordPtrWithFrequency> > t9_map_;

 // functions
 private:
  string GetT9NumericPresentation(const string &word) {
    string numeric_presentaion;
    numeric_presentaion.resize(word.size());

    string::const_iterator symbol_it = word.begin();
    string::iterator numeric_symbol_it = numeric_presentaion.begin();
    for (
        ; symbol_it != word.end()
        ; ++symbol_it, ++numeric_symbol_it
        ) {
      switch (*symbol_it) {
        case 'a':
        case 'b':
        case 'c':
          *numeric_symbol_it = '2';
          break;
        case 'd':
        case 'e':
        case 'f':
          *numeric_symbol_it = '3';
          break;
        case 'g':
        case 'h':
        case 'i':
          *numeric_symbol_it = '4';
          break;
        case 'j':
        case 'k':
        case 'l':
          *numeric_symbol_it = '5';
          break;
        case 'm':
        case 'n':
        case 'o':
          *numeric_symbol_it = '6';
          break;
        case 'p':
        case 'q':
        case 'r':
        case 's':
          *numeric_symbol_it = '7';
          break;
        case 't':
        case 'u':
        case 'v':
          *numeric_symbol_it = '8';
          break;
        case 'w':
        case 'x':
        case 'y':
        case 'z':
          *numeric_symbol_it = '9';
          break;
        default:
          throw BadFormat(word);
      }
    }
    return numeric_presentaion;
  }

 public:
  Dictionary() {
  }

  ~Dictionary() {
  }

  void SetDictionarySize(int size) {
    words_.reserve(size);
    input_frequences_.reserve(size);
  }

  void AddWordFithFrequencyToDictionary(const string &word, int frequence) {
    words_.push_back(word);
    input_frequences_.push_back(frequence);
  }

  void GenerateIndex() {
    vector<string>::const_iterator word_it = words_.begin();
    vector<int>::const_iterator frequency_it = input_frequences_.begin();
    for (
        ; word_it != words_.end()
        ; ++word_it, ++frequency_it
        ) {
      WordPtrWithFrequency word_with_frequency(word_it, *frequency_it);
      string t9_numeric_presentation = GetT9NumericPresentation(*word_it);

      // don't use find (if this list doesn't exist, it will be created)
      t9_map_[t9_numeric_presentation].push_back(word_with_frequency);
    }

    for (map<string, list<WordPtrWithFrequency> >::iterator map_it = t9_map_.begin()
        ; map_it != t9_map_.end()
        ; ++map_it
        ) {
      (*map_it).second.sort(mem_fun_ref(&WordPtrWithFrequency::GenerateIndexOrder));
    }
  }

  void TranslateWords(const vector<string> &input_words, vector<string> *output_words) {
    for (vector<string>::const_iterator input_word_it = input_words.begin()
        ; input_word_it != input_words.end()
        ; ++input_word_it
        ) {
      T9WordAndShift word_with_shift(*input_word_it);

      if (word_with_shift.word_ == "1") {
        switch (word_with_shift.count_star_key_ % 3) {
          case 0:
            output_words->push_back(".");
            break;
          case 1:
            output_words->push_back(",");
            break;
          case 2:
            output_words->push_back("?");
            break;
        }
      } else if (word_with_shift.word_[0] == ' ') {
        output_words->push_back(word_with_shift.word_);
      } else {
        list<WordPtrWithFrequency> *list_ptr = &t9_map_[word_with_shift.word_];
        // fix SpeedTest(), try to get not existent word
        // if (list_ptr->size() == 0) {
        //   continue;
        // }
        word_with_shift.count_star_key_ %= list_ptr->size();

        list<WordPtrWithFrequency>::iterator list_it = list_ptr->begin();
        advance(list_it, word_with_shift.count_star_key_);
        WordPtrWithFrequency modified_word = *list_it;
        modified_word.frequency_++;
        output_words->push_back(*modified_word.word_it_);

        list_it = list_ptr->erase(list_it);
        list<WordPtrWithFrequency>::reverse_iterator reverse_list_it(list_it);
        while (reverse_list_it != list_ptr->rend() 
            && (*reverse_list_it).frequency_ <= modified_word.frequency_
            ) {
          ++reverse_list_it;
        }
        list_ptr->insert(reverse_list_it.base(), modified_word);
      }
    }
  }
};

void InitDictionary(Dictionary *dictionary) {
  int count_words;
  scanf("%d", &count_words);
  cerr << "Count words in dictionary: " << count_words << endl;

  char word_buffer[kMaxWordLength];

  dictionary->SetDictionarySize(count_words);
  for (int index = 0; index < count_words; ++index) {
    string word;
    int frequence;
    scanf("%s %d", word_buffer, &frequence);
    dictionary->AddWordFithFrequencyToDictionary(word_buffer, frequence);
  }

  try {
    dictionary->GenerateIndex();
  } catch(Dictionary::BadFormat message) {
    cerr << "Can't parse: " << message.word_ << endl;
  }
}

void GenerateStringStream(istream &is, stringstream &ss) {
  // to be sure that last '\0' will be added
  // I'm using 'kMaxMessageSize + 1'
  char buffer[kMaxMessageSize + 1];
  // it may be "\r\n"
  is.ignore(2, '\n');
  // getline(buf, size) extract maximum (size - 1) elements
  is.getline(buffer, kMaxMessageSize + 1);

  // cerr << "buffer size: " << strlen(buffer) << endl;

  ss << buffer;

  // cerr << "stream size: " << ss.str().size() << endl;
}

void InitMessage(stringstream &message_stream, vector<string> *input_words) {  
  char symbol;
  char continue_symbol;
  string encoded_word;
  message_stream.read(&symbol, 1);
  while (message_stream.good()) {
    switch (symbol) {
      case '1':
      case ' ':
        // check first non-alpha input
        if (!encoded_word.empty()) {
          input_words->push_back(encoded_word);
          encoded_word.resize(0);
        }
        encoded_word.push_back(symbol);
        continue_symbol = '*';
        if (symbol == ' ') {
          continue_symbol = ' ';
        }
        while (message_stream.peek() == continue_symbol) {
          message_stream.read(&symbol, 1);
          encoded_word.push_back(symbol);
        }
        input_words->push_back(encoded_word);
        encoded_word.resize(0);
        break;
      default:
        encoded_word.push_back(symbol);
    }
    message_stream.read(&symbol, 1);
  }
  if (!encoded_word.empty()) {
    input_words->push_back(encoded_word);
  }
}

void Output(const vector<string> &output) {
  for (int index = 0; index < output.size(); ++index) {
    cout << output[index];
  }
  cout << endl;
}

void SpeedTest();

int main() {
  float time = clock();

  Dictionary dictionary;
  InitDictionary(&dictionary);

  float time_dict = clock() - time;
  cerr << "Time read dictionary: " << (time_dict / CLOCKS_PER_SEC) << endl;
  
  vector<string> input_words;
  stringstream message_stream;
  GenerateStringStream(cin, message_stream);
  InitMessage(message_stream, &input_words);

  float time_message = clock() - time;
  cerr << "Time read message: " << (time_message / CLOCKS_PER_SEC) << endl;
  cerr << "Count words: " << input_words.size() << endl;

  vector<string> translated_words;
  dictionary.TranslateWords(input_words, &translated_words);

  float time_translate = clock() - time;
  cerr << "Time translate: " << (time_translate / CLOCKS_PER_SEC) << endl;
  cerr << "Count translated: " << translated_words.size() << endl;

  Output(translated_words);

  return 0;
}

// Testing

const int kCountWord = 50000;
const int kMaxFrequence = 1000;
const int kMessageLength = 100000;
const int kWordLength = 20;

void SpeedTest() {
  srand(33);
  float time = clock();

  Dictionary dictionary;
  for (int word_id = 0; word_id < kCountWord; ++word_id) {
    string word;
    word.resize(kWordLength);
    for (int symbol_id = 0; symbol_id < kWordLength; ++symbol_id) {
      word[symbol_id] = 'a' + rand() % 26;
    }
    dictionary.AddWordFithFrequencyToDictionary(word, rand() % kMaxFrequence + 1);
  }
  dictionary.GenerateIndex();

  string message;
  message.resize(kMessageLength);
  bool is_begin_word = true;
  int number_size = 0;
  for (int symbol_id = 0; symbol_id < kMessageLength; ++symbol_id) {
    // int symbol = rand() % (/* digits */ 9 + /* '*', ' ' */ 2);
    int symbol;
    if (number_size < kWordLength) {
      symbol = rand() % 9;
    } else {
      symbol = rand() % 2 + 9;
    }
    switch (symbol) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
        message[symbol_id] = '1' + symbol;
        is_begin_word = false;
        number_size++;
        break;
      case 9:
        if (is_begin_word) {
          message[symbol_id] = ' ';
        } else {
          message[symbol_id] = '*';
        }
        number_size = 0;
        break;
      case 10:
        message[symbol_id] = ' ';
        is_begin_word = true;
        number_size = 0;
        break;
    }
  }

  stringstream message_stream(message);
  vector<string> input_words;
  InitMessage(message_stream, &input_words);

  vector<string> translated_words;
  dictionary.TranslateWords(input_words, &translated_words);
  Output(translated_words);

  time = clock() - time;
  cerr << "Working time: " << (time / CLOCKS_PER_SEC) << endl;
}
