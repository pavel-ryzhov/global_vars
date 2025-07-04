#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cassert>
#include <algorithm>

using std::vector;
using std::string;

struct Node {
  string word;
  int count;

  Node(string word = string(), int count = 0): word(word), count(count) {}
};

class Compare {
 public:
  bool operator()(const Node& left, const Node& right) {
    return left.count > right.count;
  }
};

void Input(vector<Node>* nodes, string* key_strikes) {
  int size;
  std::cin >> size;
  assert(3 <= size && size <= 50000);
  nodes->resize(size);
  for (int i = 0; i < size; ++i) {
    std::cin >> nodes->at(i).word >> nodes->at(i).count;
//надо бы проверить упорядоченность по алфавиту
    assert(1 <= nodes->at(i).count && nodes->at(i).count <= 1000);
    assert(nodes->at(i).word.size() <= 20);
  }
/**/  std::getline(std::cin, *key_strikes);
  std::getline(std::cin, *key_strikes);
//можно добавить проверку корекности нажатий
}

class Dictionary {
  static const int NOT_EXIST = -1;
  struct TreeNode {
    int children[8];
    vector<Node> nodes;

    TreeNode() {
      for (int i = 0; i < 8; ++i) {
        children[i] = NOT_EXIST;
      }
    }
  };

  std::map<char, int> code;
  vector<TreeNode> tree;

  void InitializeCode() {
    code['a'] = 0;
    code['b'] = 0;
    code['c'] = 0;
    code['d'] = 1;
    code['e'] = 1;
    code['f'] = 1;
    code['g'] = 2;
    code['h'] = 2;
    code['i'] = 2;
    code['j'] = 3;
    code['k'] = 3;
    code['l'] = 3;
    code['m'] = 4;
    code['n'] = 4;
    code['o'] = 4;
    code['p'] = 5;
    code['q'] = 5;
    code['r'] = 5;
    code['s'] = 5;
    code['t'] = 6;
    code['u'] = 6;
    code['v'] = 6;
    code['w'] = 7;
    code['x'] = 7;
    code['y'] = 7;
    code['z'] = 7;
  }

  string GetWord(string numbers) {
    int number = 0;
    int pointer = 0;
    while (number < numbers.size() && numbers[number] != '*') {
      assert('2' <= numbers[number] && numbers[number] <= '9');
      pointer = tree[pointer].children[numbers[number++] - '2'];
    }
    int quantity = static_cast<int>(numbers.size()) - number;
    quantity %= tree[pointer].nodes.size();
    vector<Node>::iterator top = tree[pointer].nodes.begin(), low = top + quantity, high = low;
    low->count++;
    while (low != top && low->count >= (--high)->count) {
      std::iter_swap(low--, high);
    }
    return low->word;
  }

 public:

  Dictionary(vector<Node> nodes = vector<Node>()) {
    InitializeCode();
    tree.push_back(TreeNode());
    std::stable_sort(nodes.begin(), nodes.end(), Compare());
    tree[0].nodes.push_back(Node(string(), 0));
    for(int i = 0; i < nodes.size(); ++i) {
      const string& word = nodes[i].word;
      int pointer = 0;
      for (int letter = 0; letter < word.size(); ++letter) {
        assert('a' <= word[letter] && word[letter] <= 'z');
        int child = code[word[letter]];
        int next = tree[pointer].children[child];
        if (next == NOT_EXIST) {
          tree.push_back(TreeNode());
          tree[pointer].children[child] = next = tree.size() - 1;
        }
        pointer = next;
      }
      tree[pointer].nodes.push_back(nodes[i]);
    }
  }

  string GetText(const string& key_strikes) {
    string text;
    int bottom = 0, top = 0, size = key_strikes.size();
    while (bottom < size) {
      if (key_strikes[top] == '1') {
        text += GetWord(key_strikes.substr(bottom, top - bottom));
        bottom = ++top;
        while (key_strikes[top] == '*' && top < size) {
          ++top;
        }
        int sign_number = (top - bottom) % 3;
        char sing;
        switch (sign_number) {
          case 0:
            sing = '.';
            break;
          case 1:
            sing = ',';
            break;
          case 2:
            sing = '?';
        }
        text += sing;
        bottom = top;
        continue;
      }
      if (key_strikes[top] == ' ') {
        text = text + GetWord(key_strikes.substr(bottom, top - bottom)) + ' ';
        bottom = ++top;
        continue;
      }
      assert(key_strikes[top] == '*' || '2' <= key_strikes[top] && key_strikes[top] <= '9');
      ++top;
      if (top == size) {
        text += GetWord(key_strikes.substr(bottom, top - bottom));
        bottom = top;
      }
    }
    return text;
  }
};

int main() {
  vector<Node> nodes;
  string key_strikes;
  Input(&nodes, &key_strikes);
  Dictionary dictionary(nodes);
  string result = dictionary.GetText(key_strikes);
  std::cout << result;

  return 0;
}