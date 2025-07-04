#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <map>
#include <algorithm>
#include <ctime>
#include <fstream>

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
    for (int i = 0; i < 10; i++)
      level[i] = 0;
  }

/*  void change_node_list(const std::vector<Word>::iterator& it)
  {
    Word w = *it;
    w.increment_frequency();
    words.erase(it);
    std::vector<Word>::iterator words_it;
    for (words_it = words.begin(); words_it != words.end(); words_it++) {
      if ((*words_it).frq <= w.frq)
        break;
    }
    words.insert(words_it, w);
  }*/

  void resort_words(int deep) {
    std::vector<Word>::iterator it = words.begin();
    it += deep;
    Word w = *it;
    w.increment_frequency();
    words.erase(it);
    for (it = words.begin(); it != words.end(); it++) {
      if (w.frq >= (*it).frq)
        break;
    }
    words.insert(it, w);
  }

  Dictionary *level[10];
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
//  clock_t t_start = clock();
  Dictionary *root = new Dictionary();
  Dictionary *current;

  std::cin >> std::noskipws;
  std::istreambuf_iterator<char> begin(std::cin);
  std::istreambuf_iterator<char> end;
  std::ostreambuf_iterator<char> out(std::cout);
  std::string input_str(begin, end);

  int N;  // Число слов в словаре
  std::string word; // Текущее слово
//  std::string frq_str;
  int frq; // Частота встречаемости
  int char_idx;
//  std::string::const_iterator input_it = input_str.begin();
//  while (isdigit(*input_it))
//    word += *input_it++;
//  N = std::atoi(word.c_str());
  std::istringstream iss(input_str);
  iss >> N;
  const char *cword;

  // Формируем словарь
  for (int index = 0; index < N; index++) {
  /*  word = "";
    frq_str = "";
    current = root;
    while (*input_it == 10 || *input_it == 13)
      ++input_it;
    while (isalpha(*input_it)) {
      char_idx = char2int(*input_it);
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
    current->words.push_back(Word(word, frq));*/
    iss >> word;
    iss >> frq;
    cword = word.c_str();
    current = root;
    for (int i = 0; i < word.size(); i++) {
      char_idx = char2int(cword[i]);
      if (current->level[char_idx] == 0)
        current->level[char_idx] = new Dictionary();
      current = current->level[char_idx];
    }
    current->words.push_back(Word(word, frq));
  }
//  clock_t t_end = clock();
  // Разбираем цифровой код и преобразуем его в строку
  int word_deep = 0;
  const char *punctuation_char[3] = {".", ",", "?"};
  std::string punc_str;
  std::map<int, int> punctuation_deep;
  int punctuation_num;
  std::string s_data;
  std::string result = "";
  std::vector<Word>::iterator words_it;

  char c;
  iss.get(c);
  bool b_punc = false;
  int punc_deep = 0;
  current = root;
  iss.get(c);
//  while (input_it != input_str.end()) {
  while (!iss.eof()){
/*    if (*input_it == 10 || *input_it == 13) {
      input_it++;
      continue;
    }*/
/*    while (*input_it != '1' && *input_it != ' ') {
      word += *input_it++;
      if (input_it == input_str.end())
        break;
    }*/
//    while (!iss.eof()) {
//      word += c;
      if (c == ' ') {
        if (current != root) {
        word_deep %= current->words.size();
        if (current->words.size()) {
          result += current->words[word_deep].word;
          current->resort_words(word_deep);
        }
        }
        if (punc_str.empty())
          result += " ";
        else
          result += punc_str;
        current = root;
        word_deep = 0;
        punc_deep = 0;
        punc_str = "";
      }
      else {
        if (c != '1') {
          if (isdigit(c)) {
            current = current->level[(int)c - 48];
            if (!current->sorted) {
              current->sorted = true;
              std::stable_sort(current->words.begin(), current->words.end());
            }
          }
          else if (c == '*')
            ++word_deep;
        }
        else {
          do {
            iss.get(c);
            if (c == '*')
              ++punc_deep;
          } while (c != '1' && c != ' ' && c != 10);
         // if (c == '1') {
            punc_deep %= 3;
            punc_str += punctuation_char[punc_deep];
            if (c == ' ')
              punc_str += " ";
            punc_deep = 0;
     //     }
            continue;
        }
      }
      if (c == 10 || c == 13) {
        iss.get(c);
        continue;
      }
      iss.get(c);
//    }
/*    if (word.empty() && *input_it != '1')
      input_it++;
    else {
      while (input_it != input_str.end() && (*input_it == '1' || *input_it == '*'))
        punc_str += *input_it++;
    }*/
/*    if (word.empty() && c != '1')
      iss.get(c);
    else {
      while (!iss.eof() && (c == '1' || c == '*')) {
        punc_str += c;
        iss.get(c);
      }
    }
    */
/*    current = root;
    word_deep = 0;
    for (std::string::iterator it = word.begin(); it != word.end(); it++) {
      if (*it != '*')
        current = current->level[(int)(*it) - 48];
      else
        ++word_deep;
    }*/

/*    if (word.empty()  && punc_str.empty()) {
      result += " ";
      continue;
    } else if(current->words.size() != 0 && !word.empty()) {
      if (!current->sorted) {
        current->sorted = true;
        std::stable_sort(current->words.begin(), current->words.end());
      }
      word_deep %= current->words.size();
      words_it = current->words.begin();
      words_it += word_deep;
      result += (*words_it).word;
      current->change_node_list(words_it);
    }

    // Знак препинания
    punctuation_deep.clear();
    punctuation_num = -1;
    for (std::string::iterator it = punc_str.begin(); it != punc_str.end(); it++) {
        if (*it == '1')
          punctuation_deep[++punctuation_num] = 0;
        if (*it == '*')
          ++punctuation_deep[punctuation_num];
    }

    for (std::map<int, int>::iterator p_it = punctuation_deep.begin(); p_it != punctuation_deep.end(); p_it++) {
      (*p_it).second %= 3;
      result += punctuation_char[(*p_it).second];
    }*/
  }
  result += current->words[word_deep].word;
  result += punc_str;

  std::copy(result.begin(), result.end(), out);


//  std::cout << (t_end - t_start) << " CLOCKS WITH " << CLOCKS_PER_SEC << std::endl;

  return 0;
}