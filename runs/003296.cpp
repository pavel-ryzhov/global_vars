/*
 * File:   main.cpp
 * Author: Tim
 *
 * Created on 30 Сентябрь 2010 г., 10:12
 */

//#include <ctime>

#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

// DEFINITIONS =================================================================
unsigned long long GetButtonSequence(const string &);
int GetButton(char);

// CLASSES =====================================================================

// WordInfo --------------------------------------------------------------------
class WordInfo {
    friend class RateDictionary;
    friend bool operator > (const WordInfo &, const WordInfo &);
    friend bool operator < (const WordInfo &, const WordInfo &);
    int rate;
    int last_access_time;
    string word;
public:
    WordInfo(const string &_word, int _rate = 0, int _last_access_time = 0):
        rate(_rate), last_access_time(_last_access_time), word(_word) {}
    string GetWord() {
        return word;
    }
};

bool operator < (const WordInfo &lhs, const WordInfo &rhs) {
    return (lhs.rate < rhs.rate) ||
        (lhs.rate == rhs.rate && lhs.last_access_time < rhs.last_access_time) 
        ||
        (lhs.rate == rhs.rate && lhs.last_access_time == rhs.last_access_time &&
        lhs.word > rhs.word);
}

bool operator > (const WordInfo &lhs, const WordInfo &rhs) {
    return (lhs.rate > rhs.rate) ||
        (lhs.rate == rhs.rate && lhs.last_access_time > rhs.last_access_time)
        ||
        (lhs.rate == rhs.rate && lhs.last_access_time == rhs.last_access_time &&
        lhs.word < rhs.word);
}

// LessPWordInfo ---------------------------------------------------------------
// Implement compare function, wich gets arguments as pointers.
class GreaterPWordInfo {
    bool reverse;
public:
    GreaterPWordInfo(const bool& revparam=false) {
        reverse=revparam;
    }

    bool operator() (const WordInfo *const lhs, const WordInfo *const rhs) const
    {
        if (reverse) {
            return (*lhs < *rhs);
        }
        else {
            return (*lhs > *rhs);
        }
    }
};

// RateDictionary --------------------------------------------------------------
class RateDictionary {
    typedef std::map<unsigned long long , std::vector<WordInfo*> > DataMap;
    DataMap data;
public:
    ~RateDictionary() {
        for (DataMap::iterator node = data.begin(); node != data.end(); ++node) {
            for (int j = 0; j < node->second.size(); ++j) {
                delete node->second[j];
            }
        }
    }

    void Insert(const string &word, int rate, int last_access_time = 0) {
        unsigned long long  button_sequence = GetButtonSequence(word);
        DataMap::iterator p_associated_words = data.find(button_sequence);
        if (p_associated_words == data.end()) {
            data.insert(std::make_pair(button_sequence, vector<WordInfo*>(1, new WordInfo(word, rate, last_access_time))));
        }
        else {
            p_associated_words->second.push_back(new WordInfo(word, rate, last_access_time));
        }
    }

    void Sort() {
        for (DataMap::iterator node = data.begin(); node != data.end(); ++node) {
            std::sort(node->second.begin(), node->second.end(), GreaterPWordInfo());
        }
    }

    string Get(unsigned long long  code, int number, int access_time = 0) {
        vector<WordInfo*> &fit_words = data[code];
        number %= fit_words.size();
        fit_words[number]->last_access_time = access_time;
        ++fit_words[number]->rate;
        int i = number;
        while(i > 0 && *fit_words[i - 1] < *fit_words[i]) {
            std::swap(fit_words[i - 1], fit_words[i]);
            --i;
        }
        return fit_words[i]->word;
    }

    void Print () {
        for (DataMap::const_iterator node = data.begin(); node != data.end(); ++node) {
            cout << node->first << ": " << endl;
            for (int j = 0; j < node->second.size(); ++j) {
                cout << "\t" << node->second[j]->rate << " (" << node->second[j]->last_access_time
                        << ") " << node->second[j]->word << endl;
            }
        }
    }
};

// FUNCTIONS ===================================================================

// Gets a letter and returns number of the button, associated with this letter.
// If input is not a correct letter (char from a-z), behavour is undefined.
int GetButton(char letter) {
    string keymap[] = {"abc", "def", "ghi",
        "jkl", "mno", "pqrs", "tuv", "wxyz"};
    int i = 0;
    while (keymap[i].find(letter) == string::npos) {
        ++i;
    }
    return i+1;
}

inline int ForceGetButton(char letter) {
    int keymap[] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
    return keymap[letter - 'a'] - 1;
}

// Gets not empty word and returns button sequence, associated with this word.
unsigned long long  GetButtonSequence(const string &word) {
    long long key = GetButton(word[0]);
    int size = word.size();
    for (int i = 1; i < size; ++i) {
        //if (word[i] != word[i-1]) {
            key = key * 9 + ForceGetButton(word[i]);
        //}
    }
    return key;
}

void FillDictionary (RateDictionary *p_dictionary) {
    int size;
    cin >> size;
    for (int i = 0; i < size; ++i) {
        string word;
        int rate;
        cin >> word >> rate;
        p_dictionary->Insert(word, rate, 0);
    }
    p_dictionary->Sort();
    string get_line_break;
    getline(cin, get_line_break);
}

char GetPunctuationSymbol(int number) {
    const string punctuation_symbols = ".,?";
    return punctuation_symbols[number % (sizeof(punctuation_symbols) - 1)];
}

bool IsKeyCode(char arg) {
    return (arg > '1') && (arg <= '9');
}

int GetKeyCode(char arg) {
    return arg - '0';
}

string Proc(RateDictionary *dictionary, const string& commands) {
    int commands_str_size = commands.size();
    string result;
    int i = 0;
    while (i < commands_str_size) {
        if (commands[i] == ' ') {
            result += ' ';
            ++i;
        }
        else if (commands[i] == '1') {
            int stars_start = i;
            do {
                ++i;
            } while (i < commands_str_size && commands[i] == '*');
            int num_of_stars = i - stars_start - 1;
            result += GetPunctuationSymbol(num_of_stars);
        }
        else if (IsKeyCode(commands[i])){
            unsigned long long  code = 0;
            do {
                code = 9 * code + GetKeyCode(commands[i]) - 1;
                ++i;
            } while (i < commands_str_size && IsKeyCode(commands[i]));
            int stars_start = i;
            while (i < commands_str_size && commands[i] == '*') {
                ++i;
            }
            int num_of_stars = i - stars_start;
            result += dictionary->Get(code, num_of_stars, i);
        }
        else {
            ++i;
        }
    }
    return result;
}

//double Difftime(clock_t lhs, clock_t rhs) {
//    return (double)(lhs - rhs)/CLOCKS_PER_SEC;
//}
//
int main() {
    //clock_t start = clock();
    RateDictionary dictionary;
    FillDictionary(&dictionary);
    //clock_t filled = clock();
    string commands;
    getline(cin, commands);
    string result = Proc(&dictionary, commands);
    //clock_t end = clock();
    cout << result;
    //cout << "\nTime:\n\tFillDict: " << Difftime(filled, start) << "\n\tProc: " << Difftime(end, filled) <<endl;
    return 0;
}
