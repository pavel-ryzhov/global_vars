#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <string>
#include <map>
#include <list>
#include <utility>
#include <algorithm>
#include <vector>

extern long long Hashcode(const std::string& str);

typedef std::vector<std::pair<std::string, int> > WordsWithFrequences;

class Dictionary {
  public:
    Dictionary(const WordsWithFrequences& words);

    std::string word(long long hash, int number);

  private:
    // (hash, frequency) -> list of words
    std::map<std::pair<long long, int>, std::list<std::string> > words_;
};

#endif /* _DICTIONARY_H_ */

using std::map;
using std::list;
using std::pair;
using std::string;
using std::vector;

class SymbolCode {
  public:
    SymbolCode() {
        for(int i = 0; i < TABLE_SIZE; ++i) {
            switch(i - TABLE_SIZE / 2) {
              case 'a': case 'b': case 'c':
                table_[i] = 0;
                break;
              case 'd': case 'e': case 'f':
                table_[i] = 1;
                break;
              case 'g': case 'h': case 'i':
                table_[i] = 2;
                break;
              case 'j': case 'k': case 'l':
                table_[i] = 3;
                break;
              case 'm': case 'n': case 'o':
                table_[i] = 4;
                break;
              case 'p': case 'q': case 'r': case 's':
                table_[i] = 5;
                break;
              case 't': case 'u': case 'v':
                table_[i] = 6;
                break;
              case 'w': case 'x': case 'y': case 'z':
                table_[i] = 7;
                break;
              default:
                table_[i] = -1;
                break;
            }
        }
    }

    inline int code(char symbol) const {
        return table_[symbol + TABLE_SIZE / 2];
    }

  private:
    static const int TABLE_SIZE = 256;
    char table_[TABLE_SIZE];
};

const SymbolCode symbolCode;

long long Hashcode(const string& str) {
    long long hash = 0;

    for(size_t i = 0; i < str.length(); ++i) {
        hash += symbolCode.code(str[i]) << 3 * (str.length() - i - 1);
    }

    hash += 1 << str.length() * 3;

    return hash;
}

Dictionary::Dictionary(const WordsWithFrequences& words) {
    for(size_t i = 0; i < words.size(); ++i) {
        words_[std::make_pair(Hashcode(words[i].first), words[i].second)].push_back(words[i].first);
    }

    for(map<pair<long long, int>, list<string> >::iterator i = words_.begin(); i != words_.end(); ++i) {
        i->second.sort();
    }
}

string Dictionary::word(long long hash, int number) {
    map<pair<long long, int>, list<string> >::iterator i =
        words_.lower_bound(std::make_pair(hash + 1, 0));

    while((--i)->second.size() <= number) {
        number -= i->second.size();
    }

    list<string>::iterator word = i->second.begin();
    std::advance(word, number);
    string w = *word;
    i->second.erase(word);

    words_[std::make_pair(hash, i->first.second + 1)].push_front(w);

    if(i->second.empty()) {
        words_.erase(i);
    }

    return w;
}
#include <iostream>
#include <utility>
#include <cctype>


Dictionary ReadDictionary() {
    WordsWithFrequences wordlist;
    int numberOfWords;

    std::cin >> numberOfWords;

    for(int i = 0; i < numberOfWords; ++i) {
        std::string word;
        int frequency;
        std::cin >> word >> frequency;
        wordlist.push_back(std::make_pair(word, frequency));
    }

    return Dictionary(wordlist);
}

bool isLetterKey(char key) {
    return std::isdigit(key) && key != '0' && key != '1';
}

bool isPunctuationKey(char key) {
    return '1' == key;
}

std::string::const_iterator CountStars(std::string::const_iterator key, int * count) {
    *count = 0;

    while('*' == *key) {
        ++key;
        ++(*count);
    }

    return key;
}

std::string::const_iterator WriteWord(Dictionary& dictionary,
                                      std::string::const_iterator key) {
    long long hash = 1;
    int wordNumber = 0;

    while(isLetterKey(*key)) {
        hash <<= 3;
        hash += *(key++) - '2';
    }

    key = CountStars(key, &wordNumber);

    std::cout << dictionary.word(hash, wordNumber);

    return key;
}

std::string::const_iterator WritePunctuationCharacter(std::string::const_iterator key) {
    int punctuationType;
    ++key;

    key = CountStars(key, &punctuationType);

    switch(punctuationType) {
      case 0:
        std::cout << '.';
        break;
      case 1:
        std::cout << ',';
        break;
      case 2:
        std::cout << '?';
        break;
    }

    return key;
}

void WriteMessage(Dictionary& dictionary) {
    std::string command;

    std::cin >> std::ws;

    std::getline(std::cin, command);

    for(std::string::const_iterator key = command.begin(); key != command.end();) {
        if(isLetterKey(*key)) {
            key = WriteWord(dictionary, key);
        } else if(isPunctuationKey(*key)) {
            key = WritePunctuationCharacter(key);
        } else if(std::isspace(*key)) {
            std::cout << *(key++);
        }
    }
}

int main() {
    Dictionary dictionary = ReadDictionary();

    WriteMessage(dictionary);

    return 0;
}
