#include <iostream>
#include <string>
#include <set>

using std::string;
using std::set;

const char SIX_LAST_SYMBOL = 'o';
const char EIGHT_FIRST_SYMBOL = 't';
const char EIGHT_LAST_SYMBOL = 'v';
const char TWO = '2';
const char SEVEN = '7';
const char EIGHT = '8';
const char NINE = '9';
const char FIST_ALPHABET_SYMBOL = 'a';
const char SPACE_BUTTON = ' ';
const char SPACE_SYMBOL = ' ';
const char CHANGE_WORD_BUTTON = '*';
const char PUNCTUATION_BUTTON = '1';

const char PUNCTUATION_SYMBOLS[] = {
    '.',
    ',',
    '?'
};

const int INFINITE_FREQUENCY = 2000000;

struct DictionaryWord {
    string button_sequence;
    int frequency;
    int user_priority;
    string word;

    DictionaryWord(
        const string& new_button_sequence,
        int new_frequency,
        const string& new_word):
            button_sequence(new_button_sequence),
            frequency(new_frequency),
            word(new_word),
            user_priority(0) {
    }

    bool operator< (const DictionaryWord& dictonary_word) const {
        if (button_sequence.size() < dictonary_word.button_sequence.size()) {
            return true;
        }
        else if (button_sequence.size() == dictonary_word.button_sequence.size()) {
            if (button_sequence < dictonary_word.button_sequence) {
                return true;
            }
            else if (button_sequence == dictonary_word.button_sequence){
                if (frequency < dictonary_word.frequency) {
                    return true;
                }
                else if (frequency == dictonary_word.frequency) {
                    if (user_priority < dictonary_word.user_priority) {
                        return true;
                    }
                    else if (user_priority == dictonary_word.user_priority && 
                             word > dictonary_word.word) {
                                 return true;
                    }
                }
            }
        }
        return false;
    }
};

char GetButtonNumber(char letter) {
    char result_char;
    if (letter <= SIX_LAST_SYMBOL) {
        int number = (letter - FIST_ALPHABET_SYMBOL) / 3;
        result_char = static_cast<char>(TWO + number);
    } else {
        if (letter < EIGHT_FIRST_SYMBOL) {
            result_char = SEVEN;
        }
        else if (letter > EIGHT_LAST_SYMBOL) {
            result_char = NINE;
        }
        else {
            result_char = EIGHT;
        }
    }
    return result_char;
}

string GetButtonSequence(const string& word) {
    string button_sequence;
    for (int index = 0; index < word.size(); ++index) {
        button_sequence.push_back(GetButtonNumber(word[index]));
    }
    return button_sequence;
}

void InputData(set<DictionaryWord>& dictionary, string& message_buttons) {
    int words_count;
    std::cin >> words_count;
    for (int index = 0; index < words_count; ++index) {
        string word;
        int frequency;
        std::cin >> word >> frequency;
        dictionary.insert(
            DictionaryWord(GetButtonSequence(word), frequency, word));
    }
    string empty_string;
    std::getline(std::cin, empty_string);
    std::getline(std::cin, message_buttons);
}

void GetNextWord(
    set<DictionaryWord>& dictionary,
    const string& word_buttons,
    set<DictionaryWord>::iterator& word_iterator) {

    if (word_iterator == dictionary.end()) {
        word_iterator = dictionary.upper_bound(
                    DictionaryWord(word_buttons, INFINITE_FREQUENCY, ""));
        
    }
    --word_iterator;
}

void PrintWord(
    set<DictionaryWord>& dictionary,
    string& word_buttons,
    set<DictionaryWord>::iterator& word_iterator,
    string& message,
    int& user_priority) {

    if (word_buttons.empty()) {
        return;
    }

    if (word_iterator == dictionary.end()) {
        GetNextWord(dictionary, word_buttons, word_iterator);
    }
    message.append(word_iterator->word);
    DictionaryWord updated_word(*word_iterator);
    ++(updated_word.frequency);
    ++user_priority;
    updated_word.user_priority = user_priority;
    dictionary.erase(word_iterator);
    dictionary.insert(updated_word);
    word_iterator = dictionary.end();
    word_buttons.clear();
}

string GetMessage(set<DictionaryWord>& dictionary, const string& message_buttons) {
    set<DictionaryWord>::iterator word_iterator = dictionary.end();
    int punctuation_index = 0;
    int user_priority = 0;
    bool is_punctuation = false;
    string word_buttons;
    string message;
    message.reserve(message_buttons.size());
    for (int index = 0; index < message_buttons.size(); ++index) {
        const char button = message_buttons[index];
        if (button == SPACE_BUTTON) {
            PrintWord(dictionary, word_buttons, word_iterator, message, user_priority); 
            if (is_punctuation) {
                message.push_back(PUNCTUATION_SYMBOLS[punctuation_index]);
                is_punctuation = false;
            }
            message.push_back(SPACE_SYMBOL);
        }
        else if (button == PUNCTUATION_BUTTON) {
            PrintWord(dictionary, word_buttons, word_iterator, message, user_priority);
            if (is_punctuation) {
                message.push_back(PUNCTUATION_SYMBOLS[punctuation_index]);
            }
            is_punctuation = true;
            punctuation_index = 0;
        }
        else if (button == CHANGE_WORD_BUTTON) {
            if (is_punctuation) {
                ++punctuation_index;
            }
            else {
                if (word_iterator == dictionary.end()) {
                    GetNextWord(dictionary, word_buttons, word_iterator);
                }
                GetNextWord(dictionary, word_buttons, word_iterator);
            }
        }
        else {
            if (is_punctuation) {
                message.push_back(PUNCTUATION_SYMBOLS[punctuation_index]);
                is_punctuation = false;
            }
            word_buttons.push_back(button);
        }
    }
    PrintWord(dictionary, word_buttons, word_iterator, message, user_priority);
    if (is_punctuation) {
        message.push_back(PUNCTUATION_SYMBOLS[punctuation_index]);
    }
    return message;
}

void OutputMessage(const string& message) {
    std::cout << message << std::endl;
}

int main() {
    set<DictionaryWord> dictionary;
    string message_buttons;
    InputData(dictionary, message_buttons);
    string message = GetMessage(dictionary, message_buttons);
    OutputMessage(message);
    return 0;
}