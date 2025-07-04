#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <map>
#include <algorithm>

struct Word {
  Word(const std::string& w, const int& f): word(w), frq(f) {}
  std::string word;
  int frq;
  void increment_frequency() {++frq;}
};

bool operator<(const Word& w1, const Word& w2) {
  if (w1.frq < w2.frq)
    return false;
  else if (w1.frq == w2.frq)
    return w1.word < w2.word;
  else
    return true;
}

bool operator==(const Word& w1, const Word& w2) {
  return w1.frq == w2.frq;
}

struct Dictionary {
  Dictionary() {
    sorted = false;
    for (int i = 0; i < 8; i++)
      level[i] = 0;
  }

  void change_node_list(const std::vector<Word>::iterator& it)
  {
    Word w = *it;
    w.increment_frequency();
    std::vector<Word>::iterator search_it = std::find(words.begin(), it, w);
    if (search_it == it)
      search_it = std::find(words.begin(), it, *it);
//    if (search_it != it) {
      words.erase(it);
      words.insert(search_it, w);
//    }
//    else {
//      words.erase(it);
//      words.insert(words.begin(), w);
//    }
  }

  Dictionary *level[8];
  std::vector<Word> words;
  bool sorted;
};

int char2int(const char c) {
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
    return 1;
  }
}

int main(int argc, char *argv[]) {

  Dictionary *root = new Dictionary();
  Dictionary *current;

  std::cin >> std::noskipws;
  std::istreambuf_iterator<char> begin(std::cin);
  std::istreambuf_iterator<char> end;
  std::ostreambuf_iterator<char> out(std::cout);
  std::string input_str(begin, end);

  int N;  // Число слов в словаре
  std::string word; // Текущее слово
  std::string frq_str;
  int frq; // Частота встречаемости
  int char_idx;
  std::string::const_iterator input_it = input_str.begin();
  std::string str;
  while (isdigit(*input_it))
    str += *input_it++;
  N = std::atoi(str.c_str());

  // Формируем словарь
  for (int index = 0; index < N; index++) {
    word = "";
    frq_str = "";
    current = root;
    while (*input_it == 10 || *input_it == 13)
      ++input_it;
    while (isalpha(*input_it)) {
      char_idx = char2int(*input_it) - 2;
      word += *input_it++;
      if (current->level[char_idx] == 0)
        current->level[char_idx] = new Dictionary();
      current = current->level[char_idx];
    } 
    while (*input_it == ' ')
      input_it++;
    while (isdigit(*input_it)) {
      frq_str += *input_it++;
    }
    frq = std::atoi(frq_str.c_str());
    current->words.push_back(Word(word, frq));
  }

  // Разбираем цифровой код и преобразуем его в строку
  int word_deep;
  const char *punctuation_char[3] = {".", ",", "?"};
  std::string punc_str;
  std::map<int, int> punctuation_deep;
  int punctuation_num;
  std::string s_data;
  std::string result = "";

  while (input_it != input_str.end()) {
    if (*input_it == 10 || *input_it == 13) {
      input_it++;
      continue;
    }
    word = "";
    punc_str = "";
    while (*input_it != '1' && *input_it != ' ' && (*input_it != 10 || *input_it != 13)) {
      word += *input_it++;
      if (input_it == input_str.end())
        break;
    }
    if (word.empty() && *input_it != '1')
      input_it++;
    else {
      while (input_it != input_str.end() && (*input_it == '1' || *input_it == '*'))
        punc_str += *input_it++;
    }

    current = root;
    word_deep = 0;
    for (std::string::iterator it = word.begin(); it != word.end(); it++) {
      if (*it != '*' && *it != 10 && *it != 13)
        current = current->level[(int)(*it) - 50];
      else
        ++word_deep;
    }

    if (word.empty()  && punc_str.empty()) {
      result = " ";
      std::copy(result.begin(), result.end(), out);
      continue;
    } else if(current->words.size() != 0 && !word.empty()) {
      if (!current->sorted) {
        current->sorted = true;
        std::stable_sort(current->words.begin(), current->words.end());
      }

      word_deep %= current->words.size();
      std::vector<Word>::iterator words_it = current->words.begin();
      words_it += word_deep;
      result = (*words_it).word;
      std::copy(result.begin(), result.end(), out);
      current->change_node_list(words_it);
    }

    // Знак препинания
    punctuation_deep.clear();
    punctuation_num = -1;
    for (std::string::iterator it = punc_str.begin(); it != punc_str.end(); it++) {
      if (*it != 10 && *it != 13) {
        if (*it == '1')
          punctuation_deep[++punctuation_num] = 0;
        if (*it == '*')
          ++punctuation_deep[punctuation_num];
      }
    }

    for (std::map<int, int>::iterator p_it = punctuation_deep.begin(); p_it != punctuation_deep.end(); p_it++) {
      (*p_it).second %= 3;
      result = punctuation_char[(*p_it).second];
      std::copy(result.begin(), result.end(), out);
    }
  }

//  std::copy(result.begin(), result.end(), out);

  return 0;
}