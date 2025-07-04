#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int TEXT_LEN = 21;

int GetKey(char Ch)
{
  switch(Ch)
  {
    case 'a': return 0;
    case 'b': return 0;
    case 'c': return 0;

    case 'd': return 1;
    case 'e': return 1;
    case 'f': return 1;

    case 'g': return 2;
    case 'h': return 2;
    case 'i': return 2;

    case 'j': return 3;
    case 'k': return 3;
    case 'l': return 3;

    case 'm': return 4;
    case 'n': return 4;
    case 'o': return 4;

    case 'p': return 5;
    case 'q': return 5;
    case 'r': return 5;
    case 's': return 5;
    
    case 't': return 6;
    case 'u': return 6;
    case 'v': return 6;

    case 'w': return 7;
    case 'x': return 7;
    case 'y': return 7;
    case 'z': return 7;
  }
}


struct TItem
{
  char * text;
  int f;
  TItem * next;
  TItem * pv;
};


TItem *newItem(char *text, int f)
{
  TItem *newp;

  newp = (TItem *) malloc(sizeof(TItem));
  newp->text = text;
  newp->f = f;
  newp->next = NULL;
  newp->pv = NULL;
  return newp;
}

TItem *addItem(TItem *listp, TItem *newp)
{

  TItem *p;

  if(listp == NULL)
  {
    return newp;
  }

  if (newp->f > listp->f)
  {
    // add front
    newp->next = listp;
    newp->pv = NULL;
    return newp;
  }
  else
  {
    for(p = listp; ((p->next != NULL) && (p->next->f >= newp->f)); p = p->next)
      ;

    newp->pv = p;
    newp->next = p->next;

    if(p->next != NULL)   // insert
      p->next->pv = newp;

    p->next = newp;

    return listp;
  }

}


void freeAll(TItem *listp)
{
  TItem * next;
  for (; listp != NULL; listp = next)
  {
    next = listp->next;

    if(listp->text != NULL)
      free(listp->text);

    free(listp);
  }
}


struct TTable
{
  TTable * arr[8];

  TItem * item;
} * root;

TTable * node = NULL;  // current node

TItem * crnt = NULL; // current item


TTable * createTable ()
{
  TTable * newp = (TTable *) malloc(sizeof(TTable));
  for(int i = 0; i < 9; i++)
    newp->arr[i] = NULL;
  newp->item = NULL;

  return newp;
}

void freeTable (TTable *p)
{
  if(p->item != NULL)
    freeAll(p->item);

  for(int i = 0; i < 8; i++)
    if(p->arr[i] != NULL)
      freeTable(p->arr[i]);

  free(p);
}




TTable * addTable(TTable *p, int n)
{
  if (p->arr[n] == NULL)
    p->arr[n] = createTable();

  return p->arr[n];
}


void add(TTable *p, char *s, int f)
{
  TItem * newp = newItem(s, f);
  p->item = addItem(p->item, newp);
}


char dev[4] = ".,?";

int Choice = -1; // for deviders


bool Slovo = false;
bool Devider = false;

char NewWord[TEXT_LEN];


void AddWord()
{

  if(Devider)
  {
    printf("%c", dev[ Choice ]);

    Devider = false;
  }

  else
  if(crnt != NULL)
  {
    printf("%s", crnt->text);

    crnt->f++;

    if(crnt->pv == NULL)
    {
      crnt = NULL;
      return ;
    }
    
    // sort

    TItem *p;

    for(p = crnt; ((p->pv != NULL) && (p->pv->f <= crnt->f)); p = p->pv)
      ;

    TItem * pv = crnt->pv;
    TItem * next = crnt->next;

    pv->next = next;
    if(next != NULL) next->pv = pv;

    crnt->pv = p->pv;
    crnt->next = p;

    if(p->pv == NULL)   // add front
      node->item = crnt;
    else     // insert
      p->pv->next = crnt;

    p->pv = crnt;

    crnt = NULL;
  }

}





int main()
{
  char c;

  int Len; // Длина текущего слова

  root = createTable();

  int WordsCount = 0;

  scanf("%d", &WordsCount);

  int i, f;

  for(i = 0; i < WordsCount; i++)
  {
    char * s;
    TTable * p = root;

    s = (char *)malloc(sizeof(char[21]));

    getchar();
    Len = 0;
    while ((c = getchar()) != ' ')
    {
      s[Len] = c;

      p = addTable(p, GetKey(c));

      Len++;
    }
    s[Len] = '\0';

    scanf("%d", &f);

    add(p, s, f);
  }


  getchar();


  while((c = getchar()) != EOF)
  {

    if ( (c >= '2') && (c <= '9') )
    {
      if(!Slovo) // Начинаем набирать новое слово
      {
        AddWord();

        node = root;

        Slovo = true;

        Len = 0;
      }
      else
        Len++;


      NewWord[Len] = c;

      node = node->arr[c-50];

    }
    else
    {
      if(Slovo)
      {
        crnt = node->item;

        Slovo = false;
      }

      switch(c)
      {
        case '1':
        {
          AddWord();

          Devider = true;
          Choice = 0;

          break;
        }

        case ' ':
        {
          AddWord();

          printf("%c", ' ');

          break;
        }

        case '*':
        {
          Choice++;
          if(!Devider) crnt = crnt->next;

          break;
        }
      }


    } // else

  }

  AddWord();

  freeTable(root);
  
  return 0;
}


