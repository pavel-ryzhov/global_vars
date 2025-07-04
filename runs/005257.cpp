#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <algorithm>

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
    for (int index = 0; index < 10; index++)
      level[index] = 0;
  }

  void change_node_list(std::list<Word>::iterator& it)
  {
    Word w = *it;
    w.increment_frequency();
    std::list<Word>::iterator search_it = std::find(words.begin(), words.end(), Word("", w.frequency()));
    if (search_it == words.end())
      search_it = std::find(words.begin(), words.end(), Word("", w.frequency() - 1));
    *it = w;
    if (search_it != words.end())
      words.splice(search_it, words, it);
    else
      words.splice(words.begin(), words, it);
  }

  Dictionary *level[10];
  std::list<Word> words;
};

int char2int(char c, const std::map<char, int>& tr)
{
  std::map<char, int>::const_iterator tr_it;
  tr_it = tr.find(c);
  return tr_it->second;
}

int main(int argc, char *argv[])
{
  std::map<char, int> transform;
  transform['a'] = 2; transform['b'] = 2; transform['c'] = 2;
  transform['d'] = 3; transform['e'] = 3; transform['f'] = 3;
  transform['g'] = 4; transform['h'] = 4; transform['i'] = 4;
  transform['j'] = 5; transform['k'] = 5; transform['l'] = 5;
  transform['m'] = 6; transform['n'] = 6; transform['o'] = 6;
  transform['p'] = 7; transform['q'] = 7; transform['r'] = 7; transform['s'] = 7;
  transform['t'] = 8; transform['u'] = 8; transform['v'] = 8;
  transform['w'] = 9; transform['x'] = 9; transform['y'] = 9; transform['z'] = 9;

  std::list<char> punctuation_char;
  punctuation_char.push_back('.');
  punctuation_char.push_back(',');
  punctuation_char.push_back('?');

  // Необходимые переменные
  int N = 0;
  std::string str;        // Строка из словаря
  std::string word;       // Словарное слово
  std::string frq_str;    // Строка, содержащая частоту встречаемости слова
  bool b_frq;             // признак того, считали словарное слово
  int frq = 0;            // Частота встречаемости слова
  int char_idx;           // Индекс текущего символа (соответствующее число)
  Dictionary *root_dict = new Dictionary();  // Словарь (общий)
  Dictionary *current_dict;                  // Текущая ветка словаря
 
//	try {
	std::getline(std::cin, str);
	N = std::atoi(str.c_str());
	for (int index = 0; index < N; index++) {
	  current_dict = root_dict;
	  std::getline(std::cin, str);
	  b_frq = false; frq_str = ""; word = "";
	  for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
		if (b_frq) {
		  frq_str += *it;
		  continue;
		}
		if (*it == ' ') {
		  b_frq = true;
		  continue;
		}
		word += *it;
		char_idx = char2int(*it, transform);
		if (current_dict->level[char_idx] == 0)
		  current_dict->level[char_idx] = new Dictionary();
		current_dict = current_dict->level[char_idx];
	  }
	  frq = std::atoi(frq_str.c_str());
	  current_dict->words.push_back(Word(word, frq));
    current_dict->words.sort();
	} 
//	} catch(T9_Error e) {/
//	std::cerr << "\nT9 error: " << e.message() << '\n';
//	return 1;
//	}

  std::string::iterator it;
  std::list<Word>::iterator list_it;
  std::list<char>::const_iterator punctuation_it;
  std::string inputstring;
  int word_deep;
  std::map<int, int> punctuation_deep;
  std::string punc_str;
  int punctuation_num;
  std::getline(std::cin, inputstring);
  std::istringstream iss(inputstring);
  std::string::iterator input_it = inputstring.begin();
 
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
          current_dict = current_dict->level[(int)(*it) - 48];
        else
          ++word_deep;
      }

      if (str.empty() && punc_str.empty()) {
        std::cout << ' ';
        continue;
      }
      else if (current_dict->words.size() != 0 && !str.empty()) {
        // Выводим считанное слово (если оно есть в словаре) и изменяем параметры его встречаемости
        list_it = current_dict->words.begin();
        word_deep %= current_dict->words.size();
        for (int i = 0; i < word_deep; i++)
          ++list_it;
        std::cout << (*list_it).word();
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
        std::cout << *punctuation_it;
      }
  }
 
  return 0;
}
