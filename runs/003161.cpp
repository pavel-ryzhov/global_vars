/* 
 * File:   main.cpp
 * Author: Tim
 *
 * Created on 30 Сентябрь 2010 г., 10:12
 */

#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <queue>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

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
        (lhs.rate == rhs.rate && lhs.last_access_time < rhs.last_access_time) ||
        (lhs.rate == rhs.rate && lhs.last_access_time == rhs.last_access_time &&
        lhs.word > rhs.word);
}

bool operator > (const WordInfo &lhs, const WordInfo &rhs) {
    return (lhs.rate > rhs.rate) ||
        (lhs.rate == rhs.rate && lhs.last_access_time > rhs.last_access_time) ||
        (lhs.rate == rhs.rate && lhs.last_access_time == rhs.last_access_time &&
        lhs.word < rhs.word);
}

// LessPWordInfo ---------------------------------------------------------------
// Implement compare function, wich gets arguments as pointers.
class LessPWordInfo {
    bool reverse;
public:
    LessPWordInfo(const bool& revparam=false) {
        reverse=revparam;
    }

    bool operator() (const WordInfo *const lhs, const WordInfo *const rhs) const
    {
        if (reverse) {
            return (*lhs > *rhs);
        }
        else { 
            return (*lhs < *rhs);
        }
    }
};

// RateDictionary --------------------------------------------------------------
class RateDictionary {
    typedef std::priority_queue<WordInfo*, std::vector<WordInfo*>, LessPWordInfo > WordInfoQueue;
    typedef std::map<unsigned long long , WordInfoQueue> DataMap;
    DataMap data;
public:
    ~RateDictionary() {
        for (DataMap::iterator i = data.begin(); i != data.end(); ++i) {
            while (! i->second.empty()) {
                delete i->second.top();
                i->second.pop();
            }
        }
    }

    void Insert(const string &word, int rate, int last_access_time = 0) {
        unsigned long long  button_sequence = GetButtonSequence(word);
        DataMap::iterator p_associated_words = data.find(button_sequence);
        if (p_associated_words == data.end()) {
            data.insert(std::make_pair(button_sequence, WordInfoQueue()));
            data[button_sequence].push(new WordInfo(word, rate, last_access_time));
        }
        else {
            p_associated_words->second.push(new WordInfo(word, rate, last_access_time));
        }
    }

    string Get(unsigned long long  code, int number, int access_time = 0) {
        WordInfoQueue &fit_words = data[code];
        std::stack<WordInfo*> temporary_storage;
        number %= fit_words.size();
        for (int i = 0; i < number; ++i) {
            temporary_storage.push(fit_words.top());
            fit_words.pop();
        }
        string result = fit_words.top()->word;
        ++fit_words.top()->rate;
        fit_words.top()->last_access_time = access_time;
        while (!temporary_storage.empty()) {
            fit_words.push(temporary_storage.top());
            temporary_storage.pop();
        }
        return result;
    }

    void Print () {
        for (DataMap::const_iterator i = data.begin(); i != data.end(); ++i) {
            cout << i->first << ": " << endl;
            WordInfoQueue entry = i->second;
            while (!entry.empty()) {
                cout << "\t" << entry.top()->rate << " (" << entry.top()->last_access_time
                    << ") " << entry.top()->word << endl;
                entry.pop();
            }
            cout << endl;
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

// Gets not empty word and returns button sequence, associated with this word.
unsigned long long  GetButtonSequence(const string &word) {
    long long key = GetButton(word[0]);
    int size = word.size();
    for (int i = 1; i < size; ++i) {
        //if (word[i] != word[i-1]) {
            key = key * 9 + GetButton(word[i]);
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
            } while (commands[i] == '*');
            int num_of_stars = i - stars_start - 1;
            result += GetPunctuationSymbol(num_of_stars);
        }
        else if (IsKeyCode(commands[i])){
            unsigned long long  code = 0;
            do {
                code = 9 * code + GetKeyCode(commands[i]) - 1;
                i++;
            } while (IsKeyCode(commands[i]));
            int stars_start = i;
            while (commands[i] == '*') {
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

int main() {
    RateDictionary dictionary;
    FillDictionary(&dictionary);
    string commands;
    getline(cin, commands);
    string result = Proc(&dictionary, commands);
    cout << result;
    cout.flush();
    return 0;
}
