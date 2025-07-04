#include <iostream>
#include <cstdio>
#include <map>
#include <list>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::map;
using std::list;
using std::vector;
using std::string;

typedef string PhoneFormOfWord;

const int KEY_BY_LETTER[26] = {'2', '2', '2', '3', '3', '3', '4', '4', '4', '5', '5', '5', '6', '6', '6', '7', '7', '7', '7', '8', '8', '8', '9', '9', '9', '9'};
const char KEY_FOR_PUNCTUATION_MARKS = '1';
const char KEY_TO_CHOOSE_NEXT = '*';
const char SPACE_KEY = ' ';
const char PUNCTUATION_MARKS[3] = {'.', ',', '?'};

char GetKeyByLetter(const char letter) {
    return KEY_BY_LETTER[letter - 'a'];
}

bool KeyIsLetter(const char key) {
    return isdigit(key) && key != KEY_FOR_PUNCTUATION_MARKS;
}

struct T9Word {
    string word;
    int frequency;
    
    T9Word(const string& word_, const int initial_frequency_) {
        word = word_;
        frequency = initial_frequency_;
    }

    explicit T9Word(const string& word_) {
        word = word_;
        frequency = 0;
    }

    bool operator<(const T9Word& rhs) const {
        return ((frequency > rhs.frequency) || ((frequency == rhs.frequency) && (word < rhs.word)));
    }

    void IncreaseFrequency() {
        ++frequency;
    }
};

class T9Dictionary {
private: 

    typedef map<PhoneFormOfWord, list<T9Word> > TDictionary;

    TDictionary dictionary;

public: 

    T9Dictionary() {
    }

    void Initialize(const vector<T9Word>& words_in_dictionary) {
        dictionary.clear();
        for (vector<T9Word>::const_iterator current_word = words_in_dictionary.begin(); current_word != words_in_dictionary.end(); ++current_word) {
            string current_word_by_keys;
            for (string::const_iterator current_char = current_word->word.begin(); current_char != current_word->word.end(); ++current_char) {
                current_word_by_keys.push_back(GetKeyByLetter(*current_char));
            }
            dictionary[current_word_by_keys].push_back(*current_word);
        }
        for (TDictionary::iterator it = dictionary.begin(); it != dictionary.end(); ++it) {
            it->second.sort();	
        }
    }

    void GetTypedMessage(const string& keystrokes, string& message) {
        message.clear();
        int current_char_index = 0;
        int number_of_strokes = static_cast<int>(keystrokes.length());
        while (current_char_index < number_of_strokes) {
            string current_word_in_phone_form;
            while ((current_char_index < number_of_strokes) && (keystrokes[current_char_index] == SPACE_KEY)) {
                ++current_char_index;
                message.push_back(SPACE_KEY);
            }
            while ((current_char_index < number_of_strokes) && (KeyIsLetter(keystrokes[current_char_index]))) {
                current_word_in_phone_form.push_back(keystrokes[current_char_index]);
                ++current_char_index;
            }
            if (!current_word_in_phone_form.empty()) {
                list<T9Word>::iterator current_word = dictionary[current_word_in_phone_form].begin();
                list<T9Word>::iterator position_for_current_word_to_move = dictionary[current_word_in_phone_form].begin();
                while ((current_char_index < number_of_strokes) && (keystrokes[current_char_index] == KEY_TO_CHOOSE_NEXT)) {
                    ++current_word;
                    while (position_for_current_word_to_move->frequency > current_word->frequency + 1) {
                        ++position_for_current_word_to_move;
                    }
                    ++current_char_index;
                }
                current_word->IncreaseFrequency();
                dictionary[current_word_in_phone_form].splice(position_for_current_word_to_move, dictionary[current_word_in_phone_form], current_word);
                message.append(current_word->word);
            }
            if (current_char_index == number_of_strokes) {
                break;
            }
            if (keystrokes[current_char_index] == KEY_FOR_PUNCTUATION_MARKS) {
                int current_puntuation_mark = 0;
                ++current_char_index;
                while ((current_char_index < number_of_strokes) && (keystrokes[current_char_index] == KEY_TO_CHOOSE_NEXT)) {
                    ++current_puntuation_mark;
                    ++current_char_index;
                }
                message.push_back(PUNCTUATION_MARKS[current_puntuation_mark]);
            }
        }
    }

};

void Read(vector<T9Word>& words_in_dictionary, string& keystrokes) {
    words_in_dictionary.clear();
    int number_of_words;
    cin >> number_of_words;
    for (int current_word_index = 0; current_word_index < number_of_words; ++current_word_index) {
        string current_word;
        cin >> current_word;
        int frequency_of_current_word;
        cin >> frequency_of_current_word;
        words_in_dictionary.push_back(T9Word(current_word, frequency_of_current_word));
    }
    string end_of_line;
    getline(cin, end_of_line);
    getline(cin, keystrokes);
}

void Print(const string& message) {
    cout << message << "\n";
}

int main() {
    vector<T9Word> words_in_dictionary;
    string keystrokes;
    Read(words_in_dictionary, keystrokes);
    T9Dictionary phone_dictionary;
    phone_dictionary.Initialize(words_in_dictionary);
    string message;
    phone_dictionary.GetTypedMessage(keystrokes, message);
    Print(message);
    return 0;
}
