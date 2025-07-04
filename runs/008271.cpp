#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
 
using std::vector;
using std::cin;
using std::cout;
using std::string;
using std::sort;

const int NumberPhoneKeys = 8;
const int MaxLengthCommandLine = 100003;

int TranslateLetterIntoNumber (char letter) {
  if ( (letter == 'a') || (letter == 'b') || (letter == 'c') ) {
    return 0;
  }
  if ( (letter == 'd') || (letter == 'e') || (letter == 'f') ) {
    return 1;
  }
  if ( (letter == 'g') || (letter == 'h') || (letter == 'i') ) {
    return 2;
  }
  if ( (letter == 'j') || (letter == 'k') || (letter == 'l') ) {
    return 3;
  }
  if ( (letter == 'm') || (letter == 'n') || (letter == 'o') ) {
    return 4;
  }
  if ( (letter == 'p') || (letter == 'q') || (letter == 'r') || (letter == 's') ) {
    return 5;
  }
  if ( (letter == 't') || (letter == 'u') || (letter == 'v') ) {
    return 6;
  }
  if ( (letter == 'w') || (letter == 'x') || (letter == 'y') || (letter == 'z') ){
    return 7;
  }
}

class Word {
  public:
    string word;
    int frequency;
    Word(string word_ = 0, int frequency_ = 0) {
      word = word_;
      frequency = frequency_;
    }
    ~Word() {
      word = "";
      frequency = 0;
    }
};

class Vertex {
  public:
    vector<Word> words_equal_T9code;
    vector<Vertex*> children;
    Vertex() {
      children.resize(NumberPhoneKeys);
    }
    ~Vertex() {
      words_equal_T9code.clear();
      children.clear();
    }
};

Vertex* ReadAlphabetAndBuildTree() {
  Vertex* root = new Vertex;
  int number_alphabet_words;
  cin >> number_alphabet_words;
  for (int word_index = 0; word_index < number_alphabet_words; ++word_index) {
    string new_word;
    int frequency_new_word;
    cin >> new_word >> frequency_new_word;
    Vertex* current_vertex = root;
    for (int letter_index = 0; letter_index < static_cast<int>(new_word.length()) - 1; ++letter_index){
      if (current_vertex -> children[ TranslateLetterIntoNumber(new_word[letter_index]) ] == 0) {
        Vertex* new_vertex = new Vertex;
        current_vertex -> children[ TranslateLetterIntoNumber(new_word[letter_index]) ] =
          new_vertex;
        current_vertex = current_vertex ->
          children[ TranslateLetterIntoNumber(new_word[letter_index]) ];
      }
      else
        current_vertex = current_vertex ->
          children[TranslateLetterIntoNumber(new_word[letter_index])];
    }
    if (current_vertex ->
      children[ TranslateLetterIntoNumber(new_word[new_word.length() - 1]) ] == 0) {
      Vertex* new_vertex = new Vertex;
      current_vertex -> children[ TranslateLetterIntoNumber(new_word[new_word.length() - 1]) ] =
        new_vertex;
    }
    current_vertex -> children[ TranslateLetterIntoNumber(new_word[new_word.length() - 1]) ] ->
      words_equal_T9code.push_back( Word(new_word, frequency_new_word) );
  }
  return root;
}

bool CompareWords (const Word first_word, const Word second_word) {
  if (first_word.frequency < second_word.frequency){
    return false;
  }
  else if (first_word.frequency > second_word.frequency){
    return true;
  }
  else{
    if (strcmp(first_word.word.c_str(), second_word.word.c_str()) < 0) {
      return true;
    }
    else {
      return false;
    }
  }
}

void SortWordsInTreeVertexes(Vertex* root) {
  if (root != 0) {
    sort(root -> words_equal_T9code.begin(), root -> words_equal_T9code.end(), CompareWords);
    for (int child_index = 0; child_index < NumberPhoneKeys; ++child_index) {
      SortWordsInTreeVertexes(root -> children[child_index]);
    }
  }
}

void IncreaseWordFrequency(Vertex* vertex, const int variant_number) {
  vertex -> words_equal_T9code[variant_number].frequency++;
}

void NormalizeFrequency(Vertex* current_vertex, const int variant_number) {
  int current_frequency = current_vertex -> words_equal_T9code[variant_number].frequency;
  int new_place = variant_number;
  for (int index = variant_number - 1; index >= 0; --index) {
    if (current_vertex -> words_equal_T9code[index].frequency <= current_frequency) new_place =
      index;
  }
  Word temp_word = current_vertex -> words_equal_T9code[variant_number];
  for (int index = 0; index < variant_number - new_place; ++index) {
    current_vertex -> words_equal_T9code[variant_number - index] = current_vertex ->
      words_equal_T9code[variant_number - index - 1];
  }
  current_vertex -> words_equal_T9code[new_place] = temp_word;
}

void PrintPunctuationSign(int& variant_number, int& flag_punctuation_sign) {
  if (variant_number == 0) {
    cout << ".";
  }
  if (variant_number == 1) {
    cout << ",";
  }
  if (variant_number == 2) {
    cout << "?";
  }
  variant_number = 0;
  flag_punctuation_sign = 0;
}

void PrintMessageWord(Vertex* current_vertex, int& flag_word, const int variant_number) {
  cout << current_vertex -> words_equal_T9code[variant_number].word;
  flag_word = 0;
}

void ReadT9CodeAndPrintAnswer(Vertex* root) {
  char command[MaxLengthCommandLine];
  cin.getline(command, MaxLengthCommandLine);
  cin.getline(command, MaxLengthCommandLine);
  Vertex* current_vertex = root;
  int variant_number = 0;
  int index = 0;
  int flag_punctuation_sign = 0;
  int flag_word = 0;
  while (command[index] != '\0') {
    if (command[index] == '1') {
      if (flag_punctuation_sign != 0) {
        PrintPunctuationSign(variant_number, flag_punctuation_sign);
      }
      if (flag_word != 0) {
        PrintMessageWord(current_vertex, flag_word, variant_number);
        IncreaseWordFrequency(current_vertex, variant_number);
        NormalizeFrequency(current_vertex, variant_number);
        variant_number = 0;
        current_vertex = root;
      }
      flag_punctuation_sign = 1;
    }
    else if (command[index] == '*') {
      variant_number++;
    }
    else if (command[index] == ' ') {
      if (flag_punctuation_sign != 0) {
        PrintPunctuationSign(variant_number, flag_punctuation_sign);
        cout << " ";
      }
      else if (flag_word != 0) {
        PrintMessageWord(current_vertex, flag_word, variant_number);
        IncreaseWordFrequency(current_vertex, variant_number);
        cout << " ";
        NormalizeFrequency(current_vertex, variant_number);
        variant_number = 0;
        current_vertex = root;
      }
      else {
        cout << " ";
      }
    }
    else {
      if (flag_punctuation_sign != 0) {
        PrintPunctuationSign(variant_number, flag_punctuation_sign);
      }
      current_vertex = current_vertex -> children[((int)command[index]) - 50];
      flag_word = 1;
    }
    ++index;
  }
  if (flag_punctuation_sign != 0) {
    PrintPunctuationSign(variant_number, flag_punctuation_sign);
  }
  if (flag_word != 0) {
    PrintMessageWord(current_vertex, flag_word, variant_number);
    IncreaseWordFrequency(current_vertex, variant_number);
    NormalizeFrequency(current_vertex, variant_number);
    variant_number = 0;
    current_vertex = root;
  }
}

int main(void) {
  Vertex* root = ReadAlphabetAndBuildTree();
  SortWordsInTreeVertexes(root);
  ReadT9CodeAndPrintAnswer(root);
  return 0;
}
