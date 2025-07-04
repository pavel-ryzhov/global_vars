#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cctype>

using namespace std;

struct Word
{
  string w;
  int num;
  int fr;

  Word(const string &w, int fr, int num)
  {
    this->w = w;
    this->fr = fr;
    this->num = num;
  }

  bool operator <(const Word &b) const
  {
    const Word &a = *this;
    if (a.fr == b.fr)
      return a.num > b.num;

    return a.fr > b.fr;
  }
};

struct Node
{
  Node *c[10];
  set<Word> words;

  Node()
  {
    for (int i = 0; i < 10; i++)
      c[i] = 0;
  }

  ~Node()
  {
    for (int i = 0; i < 10; i++)
      if (c[i] != 0)
        delete c[i];
  }
};

typedef set<Word>::iterator set_it;

int mp[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
Node *root;
int n, t;

int GetKey(char c)
{
  return mp[c - 'a'];
}

void AddWord(const string &w, int fr, int num)
{
  Node *cur = root;
  for (int i = 0; i < w.size(); i++)
  {
    int key = GetKey(w[i]);
    if (!cur->c[key])
      cur->c[key] = new Node();
    cur = cur->c[key];
  }

  cur->words.insert(Word(w, fr, num));
}

void ReadData()
{
  root = new Node();
  cin >> n;
  t = n + 1;

  for (int i = 0; i < n; i++)
  {
    int fr;
    string w;
    cin >> w >> fr;
    AddWord(w, fr, n - i);
  }
}

void PrintWord(Node *&cur, char c, set_it &it, char &pc)
{
  if (cur != root)
  {
    Word tmp = *it;
    cout << it->w;
    cur->words.erase(it);
    tmp.num = t++;
    tmp.fr++;
    cur->words.insert(tmp);
    cur = root;
  }
  else if (pc != ' ')
    cout << pc;

  if (c == ' ')
  {
    pc = ' ';
    cout << ' ';
  }

  if (c == '1')
    pc = '.';
}

void NextWord(Node *cur, char c, set_it &it, char &pc)
{
  if ((pc == ' ') && (cur != root))
  {
    it++;
    if (it == cur->words.end())
      it = cur->words.begin();
  }
  else if (pc == '.')
    pc = ',';
  else if (pc == ',')
    pc = '?';
  else if (pc == '?')
    pc = '.';
}

void Solve()
{
  Node *cur = root;
  char c = ' ';
  set_it it;
  char pc = ' ';

  while (!cin.fail() && !cin.eof() && !cin.bad())
  {
    c = cin.get();
    if ((c == ' ') || (c == '1'))
      PrintWord(cur, c, it, pc);
    else if (c == '*')
      NextWord(cur, c, it, pc);
    else if (isdigit(c))
    {
      if (pc != ' ')
        cout << pc;
      pc = ' ';
      cur = cur->c[c - '0'];
      it = cur->words.begin();
    }
  }
  PrintWord(cur, c, it, pc);

  delete root;
}

int main()
{
//  freopen("test.in", "r", stdin);
//  freopen("test.out", "w", stdout);
  ReadData();
  Solve();
  return 0;
}
