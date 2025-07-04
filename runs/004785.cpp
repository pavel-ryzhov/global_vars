#include <string>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <algorithm>

using std::string;
using std::cin;
using std::cout;
using std::pair;
using std::vector;
using std::map;
using std::set;

const int BEGIN_AGE = 0;

int heavisideFunc(int x) {
  return x > 0 ? 1 : 0;
}

int getDigit(int x) {
  if (x >= 97) {
    x -= 97;
    return 2 + heavisideFunc(15 - x)*(x / 3)
            + 5*heavisideFunc(x - 14)*heavisideFunc(19 - x)
            + 6*heavisideFunc(x - 18)*heavisideFunc(22 - x)
            + 7*heavisideFunc(x - 21)*heavisideFunc(26 - x);
  }
}

string getKey(const string& word) {
  string newWord;
  newWord.resize(word.size());
  for (int index = 0; index < word.length(); ++index) {

    newWord[index] = '1' + getDigit((int)word[index]) - 1;

  }
  return newWord;
}

typedef enum { BLACK, RED } nodeColor;


template<typename T, typename INFOTYPE>
struct Node {

    int verSize;
    struct Node<T, INFOTYPE>* left;
    struct Node<T, INFOTYPE>* right;
    struct Node<T, INFOTYPE>* parent;
    nodeColor color;
    T data;
    INFOTYPE* info;
};



class MyString : public string {
public:
  MyString(string str) : string(str) {

  }
  MyString() : string() {}
  bool operator>(const MyString& str) {

    return (((string)(*this)).compare((string)str) == 1) ? true : false;
  }

};

class Key : public pair<int, pair<int, MyString> > {
public:
  Key() : pair<int, pair<int, MyString> >()  {}
  Key(int rating, int age, MyString word) :
    pair<int, pair<int, MyString> >(pair<int, pair<int, MyString> >(rating, pair<int, MyString>(age, word) )) {}

  bool operator>(const Key& y) {
    if (y.first < this->first)
      return true;
    else
      if (y.first > this->first)
        return false;
      else {
        if (y.second.first < this->second.first)
          return true;
        else
          if (y.second.first > this->second.first)
            return false;
          else
            return y.second.second > this->second.second;
      }
  }
    bool operator<(const Key& y) {
    if (y.first > this->first)
      return true;
    else
      if (y.first < this->first)
        return false;
      else {
        if (y.second.first > this->second.first)
          return true;
        else
          if (y.second.first < this->second.first)
            return false;
          else
            return y.second.second < this->second.second;
      }
  }
};

struct lessMy {
  bool operator()(Key x, Key y) {
    return (x < y);
  }
};

bool isSpecial(char x) {
  return x == ' ' || x == ',' || x == '*' || x == '.' || x == '?';
}





string replaceSpecialCh(string mes) {
  string* message = &mes;
  std::string::size_type ind;
  string b = "1**";
  string c = "?";
  while ((ind = message->find(b)) != std::string::npos)
    message->replace(ind, b.size(), c);
  b = "1*";
  c = ",";
  while ((ind = message->find(b)) != std::string::npos)
    message->replace(ind, b.size(), c);
  b = "1 ";
  c = ". ";
  while ((ind = message->find(b)) != std::string::npos)
    message->replace(ind, b.size(), c);
  b = "1";
  c = ".";
  while ((ind = message->find(b)) != std::string::npos)
    message->replace(ind, b.size(), c);
  return mes;
}



class Dictionary {
public:
  map<MyString, set<Key, lessMy>* > tree;
  void insert(Key z) {
    MyString data = MyString(getKey((string)z.second.second));
    map<MyString, set<Key, lessMy>* >::iterator dataPointer = tree.find(data);
    if (dataPointer == tree.end()) {
      set<Key, lessMy>* setPointer = new set<Key, lessMy>();
      setPointer->insert(z);
      tree.insert(pair<MyString, set<Key, lessMy>* >(data, setPointer));
    }
    else {
      dataPointer->second->insert(z);
    }
  }
  string getWord(MyString code, int numberOfWord, int age) {
    map<MyString, set<Key, lessMy>* >::iterator dataPointer = tree.find(code);
    set<Key, lessMy>::iterator kthElementPointer = dataPointer->second->end();
    for (int pos = 0; pos < numberOfWord; ++pos) {
      --kthElementPointer;
    }
    Key oldKey = *kthElementPointer;
    dataPointer->second->erase(kthElementPointer);
    string word = oldKey.second.second;
    oldKey.first += 1;
    oldKey.second.first = age;
    dataPointer->second->insert(oldKey);
    return word;
  }
};



string getText(string mess, Dictionary* dictionary) {
  string message;
  message.append("?");
  message.append(mess);
  message.append("?");
  string text = "";
  int pos = 0;
  while (pos < message.length()) {
    if ((pos != 0 && isSpecial(message[pos]))) {
      if (message[pos] == '*') {
        int relIndex = 0;
        while (message[relIndex + pos] == '*' && relIndex + pos < message.size()) {
          ++relIndex;
        }
        int backIndex = 0;
        while (!isSpecial(message[pos - backIndex - 1]) && pos - backIndex - 1 >= 0) {
          ++backIndex;
        }

        int starNum = relIndex + 1;
        //cout << message.substr(pos - backIndex -1, backIndex + 1) << " " << starNum << "\n";
        //cout << message.substr(pos - backIndex, backIndex) << " " << starNum << "\n";

        text.append(dictionary->getWord(
          MyString(message.substr(pos - backIndex, backIndex)), starNum, pos));
        pos = pos + relIndex;
        //cout << pos << "\n";
        //cout << pos;
      }
      else {
        if (isSpecial(message[pos])) {
          int backIndex = 0;
          while (!isSpecial(message[pos - backIndex - 1]) && pos - backIndex - 1 >= 0) {
            ++backIndex;
          }

          //cout << message.substr(pos - backIndex -1, backIndex + 1) << " " << starNum << "\n";
          //cout << backIndex;
          if (backIndex != 0) {
            //cout << (message.substr(pos - backIndex, backIndex)) << " " << 1 << "\n";
            text.append(dictionary->getWord(MyString(message.substr(pos - backIndex, backIndex)), 1, pos));
            text.append(message.substr(pos, 1));
          }
          else {
            text.append(message.substr(pos, 1));
          }
          ++pos;

        }
      }
    }
    else {
      if (pos == 0 && isSpecial(message[pos])) {
        text.append(message.substr(pos, 1));

      }
      ++pos;
    }
  }
  return text.substr(1, static_cast<int>(text.size()) - 2);
}
void fillDictionary(Dictionary* dictinary) {
  int numOfWords = 0;
  cin >> numOfWords;
  for (int idOfWord = 0; idOfWord < numOfWords; ++idOfWord) {
    int rating = 0;
    string word;
    cin >> word;
    cin >> rating;
    dictinary->insert(*(new Key(rating, BEGIN_AGE, MyString(word))));
  }
}
void fillDictionaryTest6(Dictionary* dictinary) {
    dictinary->insert(*(new Key(1, BEGIN_AGE, MyString("pnu"))));
    dictinary->insert(*(new Key(3, BEGIN_AGE, MyString("pot"))));
    dictinary->insert(*(new Key(1, BEGIN_AGE, MyString("pov"))));
    dictinary->insert(*(new Key(1, BEGIN_AGE, MyString("qnu"))));
    dictinary->insert(*(new Key(1, BEGIN_AGE, MyString("qot"))));
    dictinary->insert(*(new Key(2, BEGIN_AGE, MyString("qov"))));
    dictinary->insert(*(new Key(1, BEGIN_AGE, MyString("rnu"))));
    dictinary->insert(*(new Key(2, BEGIN_AGE, MyString("rot"))));
    dictinary->insert(*(new Key(2, BEGIN_AGE, MyString("rov"))));
    dictinary->insert(*(new Key(1, BEGIN_AGE, MyString("snu"))));
    dictinary->insert(*(new Key(1, BEGIN_AGE, MyString("sot"))));
    dictinary->insert(*(new Key(2, BEGIN_AGE, MyString("sov"))));
}

void fillDictionaryTest5(Dictionary* dictinary) {
  vector<string> words5;
  words5.resize(13);
  words5[0] = "and";
  words5[1] = "bat";
  words5[2] = "bats";
  words5[3] = "black";
  words5[4] = "cat";
  words5[5] = "cats";
  words5[6] = "eat";
  words5[7] = "fat";
  words5[8] = "grey";
  words5[9] = "is";
  words5[10] = "likes";
  words5[11] = "my";
  words5[12] = "rats";
  for (int idOfWord = 0; idOfWord < 13; ++idOfWord) {
    dictinary->insert(*(new Key(1, BEGIN_AGE, MyString(words5[idOfWord]))));
  }
}
void fillDictionary2(Dictionary* dictinary) {
    dictinary->insert(*(new Key(1, BEGIN_AGE, MyString("act"))));
    dictinary->insert(*(new Key(1, BEGIN_AGE, MyString("bat"))));
    dictinary->insert(*(new Key(1, BEGIN_AGE, MyString("cat"))));
}

int main() {
  Dictionary dictionary = Dictionary();
  fillDictionary(&dictionary);

  string inputString = "";// = "69 228* 47 252251* 69 228 47 328*1* 69 228 54537 228*1* 228* 47 4739 263 3281* 2287* 328* 2287 263 72871";// = getMegaString();
  getline(cin, inputString);
  getline(cin, inputString);
  //cout << replaceSpecialCh(inputString);
  string message = getText(replaceSpecialCh(inputString), &dictionary);

  cout << message;
  //cout << replaceSpecialCh(inputString);
  //cout << (char)97;
  return 0;
}

int main5() {
  Dictionary dictionary = Dictionary();
  fillDictionaryTest5(&dictionary);

  string inputString = "69 228* 47 252251* 69 228 47 328*1* 69 228 54537 228*1* 228* 47 4739 263 3281* 2287* 328* 2287 263 72871";// = getMegaString();

  string message = getText(replaceSpecialCh(inputString), &dictionary);

  cout << message;
  //cout << replaceSpecialCh(inputString);
  //cout << (char)97;
  return 0;
}


int main6() {
  Dictionary dictionary = Dictionary();
  fillDictionaryTest6(&dictionary);

  string inputString = "768 768* 768** 768*** 768**** 768***** 768****** 768******* 768******** 768********* 768********** 768*********** 768*** 7681";// = getMegaString();

  string message = getText(replaceSpecialCh(inputString), &dictionary);

  cout << message;
  //cout << replaceSpecialCh(inputString);
  //cout << (char)97;
  return 0;
}



int main2() {
  Dictionary dictionary = Dictionary();
  fillDictionary2(&dictionary);

  string inputString = "228* 228** 228** 228**1";// = getMegaString();

  string message = getText(replaceSpecialCh(inputString), &dictionary);

  cout << message;

  //cout << replaceSpecialCh(inputString);
  //cout << (char)97;
  return 0;
}


/*int mainx() {
  set<Key, lessMy, lessMy> wordSet;
  cout << lessMy()(Key(1, 0, MyString("act")), Key(1, 0, MyString("bat")));
  wordSet.insert(Key(1, 0, MyString("act")));
  wordSet.insert(Key(1, 1, MyString("bat")));
  wordSet.insert(Key(2, 0, MyString("cat")));

  set<Key, lessMy, lessMy>::iterator it;
  for (it = wordSet.begin(); it != wordSet.end(); it++)
    cout << it->second.second << " ";
  //cout << (Key(1, 0, MyString("act")) < Key(1, 0, MyString("aat")) ) ;
  
  cout << (Key(1, 0, MyString("act")) > Key(1, 0, MyString("cat")));
  cout << (Key(1, 0, MyString("act")) < Key(1, 0, MyString("cat")));
  
  return 0;
}*/




