#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

// word structure/allocator
struct word
{
  char w[32];
  int f;
  word* next;
  word* prev;
};
int _wcount = 0;
word _wpool[65536];
word* walloc ()
{
  return &_wpool[_wcount++];
}

word* first = NULL;
word* last = NULL;
void addword (word* w)
{
  w->prev = last;
  if (last)
    last->next = w;
  else
    first = w;
  last = w;
}

// node structure/allocator
struct node
{
  word* w;
  node* c[10];
};
int _ncount = 0;
node _npool[65536];
node* nalloc ()
{
  return &_npool[_ncount++];
}
node* root = nalloc ();

int keys[256]; // map characters to keys

char text[131072];

int main()
{
  //freopen ("input.txt", "rt", stdin);
  //freopen ("output.txt", "wt", stdout);

  memset (_wpool, 0, sizeof _wpool);
  memset (_npool, 0, sizeof _npool);
  memset (keys, 0, sizeof keys);

  keys['.'] = keys[','] = keys['?'] = 1;
  keys['a'] = keys['b'] = keys['c'] = 2;
  keys['d'] = keys['e'] = keys['f'] = 3;
  keys['g'] = keys['h'] = keys['i'] = 4;
  keys['j'] = keys['k'] = keys['l'] = 5;
  keys['m'] = keys['n'] = keys['o'] = 6;
  keys['p'] = keys['q'] = keys['r'] = keys['s'] = 7;
  keys['t'] = keys['u'] = keys['v'] = 8;
  keys['w'] = keys['x'] = keys['y'] = keys['z'] = 9;

  // read dictionary
  int n;
  scanf ("%d", &n);
  for (int i = 0; i < n; i++)
  {
    word* w = walloc ();
    scanf ("%s %d", w->w, &w->f);
    addword (w);
  }
  // add punctuation
  word* punct1 = walloc ();
  strcpy (punct1->w, ".");
  addword (punct1);
  word* punct2 = walloc ();
  strcpy (punct2->w, ",");
  addword (punct2);
  word* punct3 = walloc ();
  strcpy (punct3->w, "?");
  addword (punct3);
  // merge sort
  for (int l = 1; l < n; l *= 2)
  {
    word* nfirst = NULL;
    word* nlast = NULL;
    word* acur = first;
    while (acur)
    {
      word* aend = acur;
      for (int x = 0; x < l && aend; x++)
        aend = aend->next;
      word* bcur = aend;
      word* bend = bcur;
      for (int x = 0; x < l && bend; x++)
        bend = bend->next;
      while (acur != aend || bcur != bend)
      {
        word* choice = acur;
        if (acur == aend || (bcur != bend && bcur->f > acur->f))
        {
          choice = bcur;
          bcur = bcur->next;
        }
        else
          acur = acur->next;
        choice->prev = nlast;
        if (nlast)
          nlast->next = choice;
        else
          nfirst = choice;
        nlast = choice;
      }
      acur = bend;
    }
    nlast->next = NULL;
    first = nfirst;
    last = nlast;
  }

  // place words in tree
  while (last)
  {
    word* cur = last;
    last = last->prev;
    node* n = root;
    for (int i = 0; cur->w[i]; i++)
    {
      int k = keys[cur->w[i]];
      if (n->c[k] == NULL)
        n->c[k] = nalloc ();
      n = n->c[k];
    }
    cur->next = n->w;
    if (n->w)
      n->w->prev = cur;
    n->w = cur;
    cur->prev = NULL;
  }

  // first gets is to skip linebreak after last entry
  gets (text);
  gets (text);
  node* cn = root;
  word* cw = NULL;
  // process text
  for (int i = 0; (text[i] >= '1' && text[i] <= '9') ||
    text[i] == ' ' || text[i] == '*'; i++)
  {
    if (text[i] == ' ' || text[i] == '1')
    {
      // print current word if there is one
      if (cw)
      {
        printf ("%s", cw->w);
        // if its not punctuation mark, increase its frequency
        if (keys[cw->w[0]] != 1)
        {
          cw->f++;
          while (cw->prev && cw->prev->f <= cw->f)
          {
            cw->prev->next = cw->next;
            if (cw->next)
              cw->next->prev = cw->prev;
            cw->next = cw->prev;
            if (cw->prev->prev)
              cw->prev->prev->next = cw;
            cw->prev = cw->prev->prev;
            cw->next->prev = cw;
          }
          if (cw->prev == NULL)
            cn->w = cw;
        }
      }
      cw = NULL;
      cn = root;
      if (text[i] == ' ')
        printf (" ");
      else
      {
        cn = root->c[1];
        cw = cn->w;
      }
    }
    else if (text[i] >= '1' && text[i] <= '9')
    {
      int k = int (text[i] - '0');
      if (cn->c[k])
        cn = cn->c[k];
      cw = cn->w;
    }
    else if (text[i] == '*')
    {
      if (cw->next)
        cw = cw->next;
      else
        cw = cn->w;
    }
  }
  // print last word if there is one
  if (cw)
    printf ("%s", cw->w);

  return 0;
}

