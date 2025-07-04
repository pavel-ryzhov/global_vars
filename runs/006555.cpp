#include <iostream>
#include <map>
#include <set>
#include <string>
#include <functional>

using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::map;
using std::string;

namespace {
class T9 {
public:
  T9() {
    vocabulary[0].insert(Word(".", 3, 0));
    vocabulary[0].insert(Word(",", 2, 0));
    vocabulary[0].insert(Word("?", 1, 0));
  }

  void AddWord(const string& word, int freq) {
    static int count = 0;
    --count;
    vocabulary[ConvertWordToNumber(word)].insert(Word(word, freq, count));
  }

  const string& FindNthWord(const string& code, size_t n) {
    static int time = 0;
    ++time;
    if (code == "1") {
      Set::iterator it = vocabulary[0].begin();
      advance(it, n);
      return it->word;
    }
    map<unsigned long long, Set>::iterator it = vocabulary.find(ConvertCodeToNumber(code));
    Set::iterator iter = it->second.begin();
    advance(iter, n);
    Word temp(*iter);
    it->second.erase(iter++);
    ++temp.freq;
    temp.time = time;
    return it->second.insert(iter, temp)->word;
  }
private:
  struct Word {
    Word(const string& word, int freq, int time) : freq(freq), time(time), word(word) {}
    bool operator>(const Word& rhs) const {
      if (freq == rhs.freq) {
        return time > rhs.time;
      } 
      return freq > rhs.freq;
    }
    int freq;
    int time;
    string word;
  };
  typedef set<Word, std::greater<Word> > Set;
  map<unsigned long long, Set> vocabulary;

  static unsigned long long ConvertWordToNumber(const string& word) {
    static char symbol[] = {'2', '2', '2', '3', '3', '3', '4', '4', '4', '5', '5', '5',
      '6' ,'6', '6', '7', '7', '7', '7', '8', '8', '8', '9', '9', '9', '9'};
    string code;
    for (size_t i = 0; i < word.size(); ++i) {
      code.push_back(symbol[word[i] - 'a']);
    }
    return ConvertCodeToNumber(code);
  }

  static unsigned long long ConvertCodeToNumber(const string& code) {
    unsigned long long result = 0;
    size_t size = code.size();
    for (size_t i = 0; i < size; ++i) {
      result += (code[i] - '0' - 2) << 3 * (size - 1 - i);
    }
    return result += static_cast<unsigned long long>(size) << 60;
  }
};

void Input(T9* t9) {
  size_t size;
  cin >> size;
  for (size_t i = 0; i < size; ++i) {
    string word;
    int freq;
    cin >> word >> freq;
    t9->AddWord(word, freq);
  }
}

void AppendToResult(string* result, string* code, size_t* n, T9* t9) {
  result->append(t9->FindNthWord(*code, *n));
  *code = "";
  *n = 0;
}

void Process(T9* t9) {
  enum {CODE, SPACE, ASTERISK, ONE} state = SPACE;
  string result;
  result.reserve(100000);
  string code;
  size_t n = 0;
  cin.get();
  char ch = cin.get();
  while (cin.good() && ch != '\n') {
    switch (ch) {
    case ' ':
      if (state != SPACE) {
        AppendToResult(&result, &code, &n, t9);
      }
      result.push_back(' ');
      state = SPACE;
      break;
    case '*':
      ++n;
      state = ASTERISK;
      break;
    case '1':
      if (state != SPACE) {
        AppendToResult(&result, &code, &n, t9);
      }
      code.push_back('1');
      state = ONE;
      break;
    default:
      if (state == ONE) {
        AppendToResult(&result, &code, &n, t9);
      }
      code.push_back(ch);
      state = CODE;
    }
    ch = cin.get();
  }
  if (state != SPACE) {
    AppendToResult(&result, &code, &n, t9);
  }
  cout << result << endl;
}
}

int main() {
  T9 t9;
  Input(&t9);
  Process(&t9);
  return 0;
}

