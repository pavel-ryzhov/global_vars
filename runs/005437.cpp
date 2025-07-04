#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <algorithm>
#include <iterator>

class Word {
public:
  Word() {}
  Word(const std::string& w, int f): word_(w), frequency_(f) {}

  int frequency() const {return frequency_;}
  std::string word() const {return word_;}
  void increment_frequency() {frequency_++;}

  bool operator<(const Word& w)
  {
    if (frequency_ < w.frequency())
      return false;
    else if (frequency_ == w.frequency()) {
      if (word_ < w.word())
        return true;
      else
        return false;
    }
    else
      return true;
  }

  bool operator==(const Word& w)
  {
    if ((w.word() == word_ && w.frequency() == frequency_) ||
      (word_ == "" && w.frequency() == frequency_) ||
      (w.word() == "" && w.frequency() == frequency_))
      return true;
    else
      return false;
  }

private:
  std::string word_;
  int frequency_;
};

struct Dictionary {
  Dictionary() 
  {
    for (int index = 0; index < 8; index++)
      level[index] = 0;
    level_sorted = false;
  }

  void change_node_list(std::list<Word>::iterator& it)
  {
    Word w = *it;
    w.increment_frequency();
    std::list<Word>::iterator search_it = std::find(words.begin(), it, Word("", w.frequency()));
    if (search_it == it)
      search_it = std::find(words.begin(), it, Word("", w.frequency() - 1));
    *it = w;
    if (search_it != words.end())
      words.splice(search_it, words, it);
    else
      words.splice(words.begin(), words, it);
  }
  
  bool level_sorted;
  Dictionary *level[8];
  std::list<Word> words;
};

int char2int(char c)
{
  switch (c) {
  case 'a': case 'b': case 'c':
    return 2;
  case 'd': case 'e': case 'f':
    return 3;
  case 'g': case 'h': case 'i':
    return 4;
  case 'j': case 'k': case 'l':
    return 5;
  case 'm': case 'n': case 'o':
    return 6;
  case 'p': case 'q': case 'r': case 's':
    return 7;
  case 't': case 'u': case 'v':
    return 8;
  case 'w': case 'x': case 'y': case 'z':
    return 9;
  default:
    return -1;
  }
}

int main(int argc, char *argv[])
{

  std::list<char> punctuation_char;
  punctuation_char.push_back('.');
  punctuation_char.push_back(',');
  punctuation_char.push_back('?');

  // Необходимые переменные
  int N = 0;
  std::string str;        // Строка из словаря
  std::string::iterator it;
  std::string word;       // Словарное слово
  int frq = 0;            // Частота встречаемости слова
  int char_idx;           // Индекс текущего символа (соответствующее число)
  Dictionary *root_dict = new Dictionary();  // Словарь (общий)
  Dictionary *current_dict;                  // Текущая ветка словаря

  std::getline(std::cin, str);
  N = std::atoi(str.c_str());
  for (int index = 0; index < N; index++) {
    current_dict = root_dict;
    std::getline(std::cin, str);
    std::istringstream iss(str);
    iss >> word;
    iss >> frq;
    for (it = word.begin(); it != word.end(); it++) {
      char_idx = char2int(*it) - 2;
      if (current_dict->level[char_idx] == 0)
        current_dict->level[char_idx] = new Dictionary();
      current_dict = current_dict->level[char_idx];
    }
    current_dict->words.push_back(Word(word, frq));
  }
  std::list<Word>::iterator list_it;
  std::list<char>::const_iterator punctuation_it;
  std::string inputstring;
  int word_deep;
  std::map<int, int> punctuation_deep;
  std::string punc_str;
  int punctuation_num;
  std::getline(std::cin, inputstring);
  std::string::iterator input_it = inputstring.begin();
  std::string result = "";
  std::ostreambuf_iterator<char> out(std::cout);

  while (input_it != inputstring.end()) {
    str = "";
    punc_str = "";
    // Считали слово до пробела или знака препинания
    while (*input_it != ' ' && *input_it != '1') {
      str += *input_it++;
      if (input_it == inputstring.end())
        break;
    }
    if (str.empty() && *input_it != '1')
      *input_it++;
    else {
      while (input_it != inputstring.end() && (*input_it == '1' || *input_it == '*')) {
        punc_str += *input_it++;
      }
    }

    current_dict = root_dict;
    word_deep = 0;
    for (it = str.begin(); it != str.end(); it++) {
      if (*it != '*')
        current_dict = current_dict->level[(int)(*it) - 50];
      else
        ++word_deep;
    }

    if (str.empty() && punc_str.empty()) {
      result += " ";
      continue;
    }
    else if (current_dict->words.size() != 0 && !str.empty()) {
      if (!current_dict->level_sorted) {
        current_dict->level_sorted = true;
        current_dict->words.sort();
      }
      // Выводим считанное слово (если оно есть в словаре) и изменяем параметры его встречаемости
      list_it = current_dict->words.begin();
      word_deep %= current_dict->words.size();
      for (int i = 0; i < word_deep; i++)
        ++list_it;
      result += (*list_it).word();
      current_dict->change_node_list(list_it); 
    }

    // Выводим знак препинания
    punctuation_deep.clear();
    punctuation_num = -1;
    for (it = punc_str.begin(); it != punc_str.end(); it++) {
      if (*it == '1')
        punctuation_deep[++punctuation_num] = 0;
      if (*it == '*')
        ++punctuation_deep[punctuation_num];
    }
    for (std::map<int, int>::iterator p_it = punctuation_deep.begin(); p_it != punctuation_deep.end(); p_it++) {
      punctuation_it = punctuation_char.begin();
      (*p_it).second %= 3;
      for (int i = 0; i < (*p_it).second; i++)
        ++punctuation_it;
      result += *punctuation_it;
    }
  }
  std::copy(result.begin(), result.end(), out);
  return 0;
}
