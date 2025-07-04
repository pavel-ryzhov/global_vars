
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

bool IsLetterDigit(char c) {
    return (isdigit(c) && (c != kPunctuation));
}

struct greater_frequency {
    bool operator() (const DictionaryItem& x, const DictionaryItem& y) const {
        return x.frequency > y.frequency;
    } 
};


void InterpretQuery(const vector<DictionaryItem>& dictionary, const string& query, 
                    string* message) {
    typedef multiset<DictionaryItem, greater_frequency> SetSortedByFrequency;
    typedef map <string, SetSortedByFrequency > DigitDictionary;
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


    int i = 0;
    while (i < static_cast<int>(query.length())) {
        // Words
        string current_word;
        while ((i < static_cast<int>(query.length())) && IsLetterDigit(query[i])) {
            current_word.append(1, query[i]);
            i++;
        } 
        if (!current_word.empty()) {
            int suggestion = 0;
            while ((i < static_cast<int>(query.length())) && (query[i] == kNextSuggest)) {
                suggestion++;
                i++;
            }
            // search and output word
            
            DigitDictionary::iterator dict_it = digit_dictionary.find(current_word);
            SetSortedByFrequency& items = dict_it->second;
            SetSortedByFrequency::iterator set_it = items.begin();
            while (suggestion > 0) {
                set_it++;
                suggestion--;
            }
            message->append(set_it->word);

            DictionaryItem item = *set_it;
            item.frequency++;

            items.erase(set_it);
            set_it = items.find(item);
            items.insert(set_it, item);

            current_word.clear();
        }

        // Punctuation
        string punctuation;
        if (query[i] == kPunctuation) {
            while ((i + 1 < static_cast<int>(query.length())) && (query[i+1] == kPunctuation)) {
                punctuation.append(1, kPunctuationPeriod);
                i++;
            }
            if ((i + 1 < static_cast<int>(query.length())) && (query[i+1] == kNextSuggest)) {
                if ((i + 2 < static_cast<int>(query.length()) && (query[i+2] == kNextSuggest))) {
                    punctuation.append(1, kPunctuationQuestion);
                    i += 3;
                } else {
                    punctuation.append(1, kPunctuationComma);
                    i += 2;
                }
            } else {
                punctuation.append(1, kPunctuationPeriod);
                i++;
            }
            message->append(punctuation);
            punctuation.clear();
        }

        while((i < static_cast<int>(query.length())) && query[i] == kSpace) {
            message->append(1, kSpace);
            i++;
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
    cout << message;

    return 0;
}

