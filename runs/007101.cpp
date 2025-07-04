#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <utility>

using std::cout;
using std::string;
using std::set;
using std::map;
using std::vector;
using std::pair;
using std::make_pair;

const int MAX_LENGTH_OF_INPUT_STRING = 100000;
const int MIN_SECOND_FREQUANCY = 60000;
const int MAX_LENGTH_OF_WORD = 20;
const int SIZE_OF_ALPHABET = 26;
const char FIRST_SYMBOL_IN_ALPHABET = 'a';
const string PUNCTUATION_MARK_CODE = "1";

struct Word {
    pair<int, int> frequency;
    string text;
    bool operator < (const Word& right_word) const {
       return (frequency > right_word.frequency);
    }
};

void Code_Text(const string& text, 
               const map<char, char>& telephone_map,
               string* code_text) {
    *code_text = "";
    for (int position = 0; position < text.length(); ++position) {
          char word_char = text.at(position);
          char code_char = telephone_map.find(word_char)->second;
          code_text->push_back(code_char);
    }
}

void Input(vector<Word>* words, 
           string* input_string) {
    int number_word;
    scanf("%d\n", &number_word);

    for (int word_index = 0; word_index < number_word; ++word_index) {
          int first_frequency;
          char buffer_word[MAX_LENGTH_OF_WORD + 1];
          scanf("%s %d\n", buffer_word, &first_frequency);
          Word word;
          word.text = buffer_word;
          word.frequency.first = first_frequency;
          words->push_back(word);
    }

    char buffer[MAX_LENGTH_OF_INPUT_STRING + 1];
    scanf("%[1-9* ]", buffer);
    *input_string = buffer; 
}

void Output(const string& result) {
    cout << result;
} 

void Initialize(map<char, char>* telephone_map, 
                map<string, set<Word> >* dictionary) {
    char char_code = '2';
    int number_char = 0;
    for (int char_index = 0; char_index < SIZE_OF_ALPHABET; ++char_index) {
          telephone_map->insert(make_pair(FIRST_SYMBOL_IN_ALPHABET + char_index, char_code));  
          ++number_char;
          if (char_index == 17 || char_index == SIZE_OF_ALPHABET - 2) {
               --number_char;
          }
          if (number_char % 3 == 0) {
               ++char_code;
          }
    }

    set<Word> punctuation_mark;
    Word word;
    word.frequency.first = 3;
    word.frequency.second = MIN_SECOND_FREQUANCY;
    word.text = ".";
    punctuation_mark.insert(word);
    word.frequency.first = 2;
    word.frequency.second = MIN_SECOND_FREQUANCY;
    word.text = ",";
    punctuation_mark.insert(word);
    word.frequency.first = 1;
    word.frequency.second = MIN_SECOND_FREQUANCY;
    word.text = "?";
    punctuation_mark.insert(word);
    dictionary->insert(make_pair(PUNCTUATION_MARK_CODE, punctuation_mark));
}

void Create_Dictionary(const vector<Word>& words,
                       map<string, set<Word> >* dictionary) {
    map<char, char> telephone_map;
    Initialize(&telephone_map, dictionary);

    int current_second_frequancy = MIN_SECOND_FREQUANCY;
    for (int word_index = 0; word_index < words.size(); ++word_index) {
        Word word = words.at(word_index);
        word.frequency.second = current_second_frequancy;
        --current_second_frequancy;
        string code_word;
        Code_Text(word.text, telephone_map, &code_word);
        if (dictionary->find(code_word) == dictionary->end()) {
            set<Word> set_word;
            dictionary->insert(make_pair(code_word, set_word));
        }
        dictionary->find(code_word)->second.insert(word);
    }
}

void Get_Sms_Message(const vector<Word>& words,
                     const string& code_text, 
                     string* sms_message) {
    map<string, set<Word> > dictionary;
    Create_Dictionary(words, &dictionary);

    *sms_message = "";
    string code_word = "";
    int current_second_frequancy = MIN_SECOND_FREQUANCY;  

    for (int position = 0; position < code_text.length(); ++position) {           
            if (code_text.at(position) >= '2' && code_text.at(position) <= '9') {
                 code_word.push_back(code_text.at(position)); 
            } else {
                 if (code_word == "" && code_text.at(position) == '1') {
                      code_word = PUNCTUATION_MARK_CODE;
                      ++position;
                 }

                 set<Word>* words = &dictionary.find(code_word)->second;
                 set<Word>::iterator word = words->begin();
                 while (position < code_text.length() && code_text.at(position) == '*') {
                         ++word;
                         if (word == words->end()) {
                                word = words->begin();
                         }
                         ++position;
                 }

                 (*sms_message) += word->text; 

                 if (code_word != PUNCTUATION_MARK_CODE) {
                      Word modify_word;
                      ++current_second_frequancy;
                      modify_word.frequency = make_pair(word->frequency.first + 1, current_second_frequancy);
                      modify_word.text = word->text;
                      words->erase(word);
                      words->insert(modify_word);
                 }

                 code_word = "";

                 while (position < code_text.length() && code_text.at(position) == ' ') {
                         ++position;
                         sms_message->push_back(' ');
                 }
                 --position;
              }
    }

    if (code_word != "") {
        set<Word>* words = &dictionary.find(code_word)->second;
        set<Word>::iterator word = words->begin();
        (*sms_message) += word->text;
    }
}

int main() {
    vector<Word> words;
    string code_text;
    Input(&words, &code_text);
    string sms_message;
    Get_Sms_Message(words, code_text, &sms_message);
    Output(sms_message);
    return 0;
}
