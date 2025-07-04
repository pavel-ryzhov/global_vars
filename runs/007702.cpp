#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

const int num_words = 50010;
const int num_sym = 21;

struct Word{
    int rate;
    int size;
    char str[num_sym];
    short code[num_sym];

    Word(char *cstr = 0, int s = -1, int n = 0)
    {
        for (int i = 0; i < s + 1; i ++)
            str[i] = cstr[i];
        rate = n; size = s;
        for (int i = 0; i < size; i ++)
        {
            char c = str[i];
            if (c == ',' || c == '.' || c == '?') code[i] = 1;
            if (c == 'a' || c == 'b' || c == 'c') code[i] = 2;
            if (c == 'd' || c == 'e' || c == 'f') code[i] = 3;
            if (c == 'g' || c == 'h' || c == 'i') code[i] = 4;
            if (c == 'j' || c == 'k' || c == 'l') code[i] = 5;
            if (c == 'm' || c == 'n' || c == 'o') code[i] = 6;
            if (c == 'p' || c == 'q' || c == 'r' || c == 's') code[i] = 7;
            if (c == 't' || c == 'u' || c == 'v') code[i] = 8;
            if (c == 'w' || c == 'x' || c == 'y' || c == 'z') code[i] = 9;
        }
    }
};


struct Node{
    Word key;
    int pr; 
    int sum;
    Node * l;
    Node * r;

    Node(Word * new_key, int new_pr)
    {
        key = Word(new_key->str, new_key->size, new_key->rate);
        pr = new_pr;
        sum = 0;
        l = r = NULL;
    }

};

int n;
vector <Word *> voc;
vector <Word *> same_code;
vector <Node *> voc_tree;

short comp_codes(short * c1, short * c2, int n)
{
   int i = 0;
   while (i < n && c1[i] == c2[i]) i ++;
   if (i == n) return 1;
   else
        if (c1[i] < c2[i]) return 2;
        else return 0;
}

bool compare_for_sort(Word * w1, Word * w2)
{
    if (w1->size < w2->size) return true;
    else
        if (w1->size == w2->size && strcmp(w1->str, w2->str) < 0
           && comp_codes(w1->code, w2->code, w2->size) == 1) return true;
        else
             if (w1->size == w2->size
                 && comp_codes(w1->code, w2->code, w2->size) == 2) return true;
             else return false;
}

bool compare(Word * w1, Word * w2)
{
    if (w1->size < w2->size) return true;
    else
        if (w1->size == w2->size
           && comp_codes(w1->code, w2->code, w2->size) == 2) return true;
        else return false;
}

bool comp_rates(Word w1, Word w2)
{
    if (w1.rate >= w2.rate) return true;
    else return false;
}



void split(Node * pnode, Word key, Node * &l, Node * &r)
{
  if (!pnode)
  {
      l = r = NULL;
  }
  else
      if (!comp_rates(key, pnode->key))
      {
         l = pnode;
         split(l->r, key, l->r, r);
      }
      else
      {
         r = pnode;
         split(r->l, key, l, r->l);
      }
  if (l)
  {
      l->sum = 0;
      if (l->l) l->sum = l->l->sum + 1;
      if (l->r) l->sum += (l->r->sum + 1);
  }
  if (r)
  {
      r->sum = 0;
      if (r->l) r->sum = r->l->sum + 1;
      if (r->r) r->sum += (r->r->sum + 1);
  }
}

void merge(Node * pnode1, Node * pnode2, Node * &res)
{
   if (!pnode1)
      res = pnode2;
   else
       if (!pnode2)
           res = pnode1;
       else
           if (pnode1->pr > pnode2->pr)
           {
               res = pnode1;
               res->sum += (pnode2->sum + 1);
               merge(pnode1->r, pnode2, pnode1->r);
           }
           else
           {
               res = pnode2;
               res->sum += (pnode1->sum + 1);
               merge(pnode1, pnode2->l, pnode2->l);
           }
}


void insert(Node * new_node, Node * &pnode)
{
    if (!pnode) pnode = new_node;
    else
        if (pnode->pr > new_node->pr)
        {
            pnode->sum ++;
            if (comp_rates(new_node->key, pnode->key))
              insert(new_node, pnode->l);
            else
              insert(new_node, pnode->r);
        }
        else
        {
            split(pnode, new_node->key, new_node->l, new_node->r);
            new_node->sum = 0;
            if (new_node->l) new_node->sum = (new_node->l->sum + 1);
            if (new_node->r) new_node->sum += (new_node->r->sum + 1);
            pnode = new_node;
        }
}

void erase(Node * &pnode, Word * next_word, int k)
{
  Node *l; Node *r;
  if ((pnode->l && pnode->l->sum + 2 == k) || (!pnode->l && k == 1))
  {
      *next_word = pnode->key;
      l = pnode->l; r = pnode->r;
      delete pnode;
      merge(l, r, pnode);
  }
  else
      if (pnode->l && pnode->l->sum + 1 >= k)
      {
          pnode->sum --;
          erase(pnode->l, next_word, k);
      }
      else
      {
          if (pnode->l) k -= (pnode->l->sum + 2);
          else k --;
          pnode->sum --;
          erase(pnode->r, next_word, k);
      }
}



void build_tree(int from, int to, int count)
{
   for (int i = to - 1; i >= from; i --)
   {
       Node * new_node = new Node(voc[i], rand());
       insert(new_node, voc_tree[count]);
   }
}


int find(Word * next_word, int r)
{
   int l = 0, m = 0;
   while (r - l > 1)
   {
      m = (l + r) / 2;
      if (compare(next_word, same_code[m]))
           r = m;
      else
           l = m;
   }
   return l;
}


void build_fast_voc(int &j)
{
    int k = 0;
    bool res;
    for (int i = 0; i < n; i ++)
    {
       res = compare(voc[k], voc[i]);
       if (res)
       {
           build_tree(k, i, j);
           same_code[j] = new Word(voc[k]->str, voc[k]->size);
           j ++; k = i;
       }
    }
    build_tree(k, n, j);
    same_code[j] = new Word(voc[k]->str, voc[k]->size);
    j ++;
}


void print_sms(int j)
{
    int k = 0;
    char c; bool eof = false;
    scanf("%c", &c);
    while (!eof)
    {
        k = 1;
        Word * next_word = new Word();
        next_word->size = 0;
        while (c == ' ')
        {
           printf("%c", c);
           scanf("%c", &c);
           if (c == '\n')
           {
               eof = true; break;
           }
        }
        if (eof) break;
        if  (c == '1')
        {
            next_word->code[next_word->size] = 1;
            next_word->size ++;
            scanf("%c", &c);
            if (c == '\n') eof = true;
        }
        else
        {
            while (c != ' ' && c != '*' && c != '1')
            {
                next_word->code[next_word->size] = c - '0';
                next_word->size ++;
                scanf("%c", &c);
                if (c == '\n')
                {
                    eof = true; break;
                }
            }
        }
        while (!eof && c == '*')
        {
            k ++;
            scanf("%c", &c);
            if (c == '\n')
            {
                eof = true; break;
            }
        }
        int tree_num = find(next_word, j);
        erase(voc_tree[tree_num], next_word, k);

        printf("%s", next_word->str);

        next_word->rate ++;
        Node * next_node = new Node(next_word, rand());
        insert(next_node, voc_tree[tree_num]);
    }

}


int main(int argc, char *argv[])
{
    srand(time(NULL));

    scanf("%d\n", &n);
    voc.resize(n + 3); same_code.resize(n + 1); voc_tree.resize(n + 1);
    int rate; int size = 0;
    char str[num_sym]; char c;
    scanf("%c", &c);
    voc[0] = new Word((char *) ".\0", 1, 1);
    voc[1] = new Word((char *) ",\0", 1, 1);
    voc[2] = new Word((char *) "?\0", 1, 1);
    for (int i = 3; i < n + 3; i ++)
    {
        while (c != ' ')
        {
          str[size] = c; scanf("%c", &c);  size ++;
        }
        str[size] = '\0';
        scanf("%d\n", &rate);
        if (i < n + 2) scanf("%c", &c);
        voc[i] = new Word(str, size, rate); size = 0;
    }

    sort(voc.begin() + 3, voc.end(), compare_for_sort);
    n += 3;

    int j = 0;
    build_fast_voc(j);

    print_sms(j);
}


