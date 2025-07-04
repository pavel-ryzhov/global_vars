#include <iostream>
#include <string>
#include <map>

using namespace std;

struct word {
  string lett;
  int freq;
};

void showMap (multimap<string, word> map1) {
  multimap<string, word>::iterator map_begin = map1.begin();
  multimap<string, word>::iterator map_end = map1.end();
  word coutWord;
  cout << "--------------------------------------------" << endl;
  while (map_begin != map_end) {
    cout << (*map_begin).first << " ";
    coutWord = (*map_begin++).second;
    cout << coutWord.lett << " " << coutWord.freq << endl;
  }
}

string numbWord(string word) {
  string str;
  int numb = 0;
  int size = word.size();
  for (int i = 0; i < size; i++) {
    numb = ((int)(word.at(i)) - 97)/3+50;
    if (word.at(i) == 's') {
      numb = numb-1;
    }
    if (word.at(i) == 'v') {
      numb = numb-1;
    }
    if (word.at(i) > 'x') {
      numb = numb-1;
    }
    str = str+(char)numb;
  }
  return str;
}

int main() {
  multimap<string, word> map1;
  pair<string, word> p;
  multimap<string, word>::iterator map_iter = map1.begin();
  multimap<string, word>::iterator map_iterErase = map1.begin();
  int freqs;
  int count = 0;
  string words;
  int N = 0;
  word sortWord;
  word wordOne[3];
  wordOne[0].lett = ".";
  wordOne[0].freq = 1;
  wordOne[1].lett = ",";
  wordOne[1].freq = 1;
  wordOne[2].lett = "?";
  wordOne[2].freq = 1;
  string one[3] = {"1", "1", "1"};
  for (int i = 0; i < 3; i++) {
    p.first = one[i];
    p.second = wordOne[i];
    map1.insert(p);
  }
  cin >> N;
  word *currentWord;
  currentWord = new word[N];
  word coutWord;
  word findWord;
  string *str;
  str = new string[N];

  cin >> words;
  cin >> freqs;
  currentWord[0].lett = words;
  currentWord[0].freq = freqs;
  str[0] = numbWord(words);
  p.first = str[0];
  p.second = currentWord[0];
  map1.insert(p);

  for (int i = 1; i < N; i++) {
    cin >> words;
    cin >> freqs;
    currentWord[i].lett = words;
    currentWord[i].freq = freqs;
    str[i] = numbWord(words);
    p.first = str[i];
    p.second = currentWord[i];
    map_iter = map1.insert(p);
    map_iterErase = map_iter;
    *map_iter--;
    map1.erase(map_iterErase);
    sortWord = (*map_iter).second;
    while((*map_iter).first > str[i] || (((*map_iter).first == str[i]) && sortWord.freq < freqs)) {
      *map_iter--;
      sortWord = (*map_iter).second;
    }
    *map_iter++;
    map1.insert(map_iter, p);
  }
  delete [] currentWord;
  delete [] str;
  count = 0;
  word testWord;
  string keys;
  string key;
  int change = 0;
  char prevLetter = ' ';
  char letter;
  cin >> letter;
  getline(cin, keys);
  keys = letter+keys;
  int size = keys.size();
  for (int i = 0; i < size; i++) {
    letter = keys.at(i);
    if (letter <= '9' && letter > '1') {
      if (prevLetter == '*' || prevLetter == '1') {
        if (change == 0) {
          cout << ".";
        } else if (change == 1) {
          cout << ",";
        } else if (change == 2) {
          cout << "?";
        }
        key.clear();
        change = 0;
      }
      key = key+letter;
    } else if (letter == '*') {
      change++;
    } else if (letter == ' ') {  // Если пробел
      if (prevLetter == ' ') {  // Если два пробела подряд
        cout << " ";
      } else {
        map_iter = map1.find(key);
        for (int k = 0; k < change; k++) {
          *map_iter++;
        }
        coutWord = (*map_iter).second;
        cout << coutWord.lett << " ";
        if (key != "1") {
          coutWord.freq = coutWord.freq+1;
          map_iterErase = map_iter;
          *map_iter--;
          map1.erase(map_iterErase);
          p.first = key;
          p.second = coutWord;
          bool flagSort = false;
          while(!flagSort) {
            sortWord = (*map_iter).second;
            if ((*map_iter).first != key || sortWord.freq > coutWord.freq) {
              *map_iter++;
              map1.insert(map_iter, p);
              flagSort = true;
            }
            *map_iter--;
          }
        }
        change = 0;
        key.clear();
      }
    } else if (letter == '1') {
      if (!key.empty()) {
        map_iter = map1.find(key);
        for (int k = 0; k < change; k++) {
          *map_iter++;
        }
        coutWord = (*map_iter).second;
        if (key != "1") {
          coutWord.freq = coutWord.freq+1;
          map_iterErase = map_iter;
          *map_iter--;
          map1.erase(map_iterErase);
          p.first = key;
          p.second = coutWord;
          bool flagSort = false;
          while(!flagSort) {
            sortWord = (*map_iter).second;
            if ((*map_iter).first != key || sortWord.freq > coutWord.freq) {
              *map_iter++;
              map1.insert(map_iter, p);
              flagSort = true;
            }
            *map_iter--;
          }
        }
        cout << coutWord.lett;
        change = 0;
        key.clear();
      }
      change = 0;
      key = "1";
    }
    prevLetter = letter;
  }
  if (letter == ' ') {
    cout << " " << endl;
  }
  if (letter == '1') {
    cout << "." << endl;
  }
  if (letter != ' ' && letter != '1') {
    map_iter = map1.find(key);
    for (int k = 0; k < change; k++) {
      *map_iter++;
    }
    coutWord = (*map_iter).second;
    cout << coutWord.lett << endl;
  }
  return 0;
}
