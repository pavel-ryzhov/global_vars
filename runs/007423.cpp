#include <string>
#include <set>
#include <map>
#include <vector>
#include <utility>

using std::string;
using std::set;
using std::map;
using std::vector;
using std::pair;
using std::make_pair;

const int MAX_LENGTH_OF_CODE_MESSAGE = 100000;
const int MAX_LENGTH_OF_WORD = 20;
const int MIN_SECOND_FREQUANCY = 60000;


const int SIZE_OF_ALPHABET = 26;
const char FIRST_SYMBOL_IN_ALPHABET = 'a';

const string PUNCTUATION_MARK_CODE = "1";
const int COUNT_PUNCTUATION_MARK = 3;
const char PUNCTUATION_MARKS[COUNT_PUNCTUATION_MARK] = {'.', ',', '?'}; 

struct Word {
    pair<int, int> frequency;
    string text;
    bool operator < (const Word& right_word) const {
       return (frequency > right_word.frequency);
    }
};

void Code_Message(const string& message, 
                  const map<char, char>& telephone_map,
                  string* code_message) {
    *code_message = "";
    for (int position = 0; position < message.length(); ++position) {
          char word_char = message.at(position);
          char code_char = telephone_map.find(word_char)->second;
          code_message->push_back(code_char);
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

    char buffer[MAX_LENGTH_OF_CODE_MESSAGE + 1];
    scanf("%[1-9* ]", buffer);
    *input_string = buffer; 
}

void Output(const string& result) {
    printf("%s", result.c_str());
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
    for (int index = 0; index < COUNT_PUNCTUATION_MARK; ++index) {
            Word word;
            word.frequency.first = COUNT_PUNCTUATION_MARK - index;
            word.frequency.second = MIN_SECOND_FREQUANCY;
            word.text = PUNCTUATION_MARKS[index];
            punctuation_mark.insert(word);
    }
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
        Code_Message(word.text, telephone_map, &code_word);
        if (dictionary->find(code_word) == dictionary->end()) {
            set<Word> set_word;
            dictionary->insert(make_pair(code_word, set_word));
        }
        dictionary->find(code_word)->second.insert(word);
    }
}

void Decode_Message(const vector<Word>& words,
                    const string& code_message, 
                    string* decode_message) {
    map<string, set<Word> > dictionary;
    Create_Dictionary(words, &dictionary);

    *decode_message = "";
    string code_word = "";
    int current_second_frequancy = MIN_SECOND_FREQUANCY;  

    for (int position = 0; position < code_message.length(); ++position) {           
            if (code_message.at(position) >= '2' && code_message.at(position) <= '9') {
                 code_word.push_back(code_message.at(position)); 
            } else {
                 if (code_word == "" && code_message.at(position) == '1') {
                      code_word = PUNCTUATION_MARK_CODE;
                      ++position;
                 }

                 set<Word>* words = &dictionary.find(code_word)->second;
                 set<Word>::iterator word = words->begin();
                 while (position < code_message.length() && code_message.at(position) == '*') {
                         ++word;
                         if (word == words->end()) {
                                word = words->begin();
                         }
                         ++position;
                 }

                 (*decode_message) += word->text; 

                 if (code_word != PUNCTUATION_MARK_CODE) {
                      Word modify_word;
                      ++current_second_frequancy;
                      modify_word.frequency = make_pair(word->frequency.first + 1, current_second_frequancy);
                      modify_word.text = word->text;
                      words->erase(word);
                      words->insert(modify_word);
                 }

                 code_word = "";

                 while (position < code_message.length() && code_message.at(position) == ' ') {
                         ++position;
                         decode_message->push_back(' ');
                 }
                 --position;
              }
    }

    if (code_word != "") {
        (*decode_message) += dictionary.find(code_word)->second.begin()->text;
    }
}

int main() {
    vector<Word> words;
    string code_message;
    Input(&words, &code_message);
    string decode_message;
    Decode_Message(words, code_message, &decode_message);
    Output(decode_message);
    return 0;
}
