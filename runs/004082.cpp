#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int TEXT_LEN = 21;


char GetKey(char Ch)
{
  switch(Ch)
  {
    case 'a': return '2';
    case 'b': return '2';
    case 'c': return '2';

    case 'd': return '3';
    case 'e': return '3';
    case 'f': return '3';

    case 'g': return '4';
    case 'h': return '4';
    case 'i': return '4';

    case 'j': return '5';
    case 'k': return '5';
    case 'l': return '5';

    case 'm': return '6';
    case 'n': return '6';
    case 'o': return '6';

    case 'p': return '7';
    case 'q': return '7';
    case 'r': return '7';
    case 's': return '7';

    case 't': return '8';
    case 'u': return '8';
    case 'v': return '8';

    case 'w': return '9';
    case 'x': return '9';
    case 'y': return '9';
    case 'z': return '9';
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

    if(p->next == NULL)   // add end
    {
      p->next = newp;
      newp->pv = p;
    }
    else     // insert
    {
      newp->pv = p;
      newp->next = p->next;

      p->next->pv = newp;
      p->next = newp;
    }

    return listp;
  }

}


void freeAll(TItem *listp)
{
  TItem * next;
  for (; listp != NULL; listp = next)
  {
    next = listp->next;
    free(listp->text);
    free(listp);
  }
}

// Hash
const int NHASH  = 2000001;

TItem * symtab[NHASH];


enum {MULTIPLIER = 31};

unsigned int hash(char *str)
{
  unsigned int h;
  unsigned char * p;
  h = 0;
  for(p =(unsigned char *) str; *p != '\0'; p++)
    h = MULTIPLIER * h + *p;

  return h % NHASH;
}

unsigned int hashp(char *str)
{
  unsigned int h;
  unsigned char * p;
  h = 0;
  for(p =(unsigned char *) str; *p != '\0'; p++)
    h = MULTIPLIER * h + GetKey(*p);

  return h % NHASH;
}

TItem * add(char *text, int f)
{
  int h;
  TItem * sym;

  h = hashp(text);

  sym  = newItem(text, f);
  symtab[h] = addItem(symtab[h], sym);

  return sym;
}



TItem * find(char * textp, int ch)
{
  int i = 0;
  int h = hash(textp);
  TItem * sym = symtab[h];

  if(sym == NULL) return NULL;

  while ((sym->next != NULL)&&(i < ch))
  {
    sym = sym->next;
    i++;
  }

  sym->f++;

  if ((sym->pv != NULL) && (sym->pv->f <= sym->f ))
  {
    TItem * pv = sym->pv;
    TItem * next = sym->next;

    pv->next = next;
    if(next != NULL) next->pv = pv;

    TItem *p;

    for(p = sym; ((p->pv != NULL) && (p->pv->f <= sym->f)); p = p->pv)
      ;

    if(p->pv == NULL)   // add end
    {
      p->pv = sym;
      sym->next = p;
      sym->pv = NULL;
      symtab[h] = sym;
    }
    else     // insert
    {
      sym->pv = p->pv;
      sym->next = p;

      p->pv->next = sym;
      p->pv = sym;
    }
  }

  return sym;
}


void freeHash()
{
  for(int i = 0; i < NHASH; i++)
    if (symtab[i] != NULL) freeAll(symtab[i]);
}


char dev[4] = ".,?";

int Index = 0; // Текущий символ
int Len; // Длина текущего слова

int Choice = -1;


bool Slovo = false;
bool Devider = false;

char NewWord[TEXT_LEN];



void AddWord()
{
  if(Choice > -1)
  {

    if(Devider)
    {
      printf("%c", dev[ Choice ]);

      Devider = false;
    }
    else
    {
      TItem * p;

      p = find( NewWord, Choice );

      if(p != NULL)
      {
        printf("%s", p->text);

      }

    }

    Choice = -1;
  }
}





int main()
{

  char c;

  int WordsCount = 0;

  scanf("%d", &WordsCount);

  int i;
  int f;

  for(i = 0; i < WordsCount; i++)
  {
    char * s;
    s = (char *)malloc(sizeof(char[21]));
    scanf("%s", s);
    scanf("%d", &f);

    add(s, f);
  }

  getchar();

  while((c = getchar()) != EOF)
  {

    if ( (c >= '2') && (c <= '9') )
    {
      if(!Slovo) // Начинаем набирать новое слово
      {
        AddWord();

        Slovo = true;

        Len = 0;
      }
      else
        Len++;


      NewWord[Len] = c;

    }
    else
    {
      if(Slovo)
      {
        Len++;

        NewWord[Len] = '\0';

        Slovo = false;

        Choice = 0;
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
          if(Choice > -1) Choice++;
          break;
        }
      }


    } // else

  }

  AddWord();
            

  freeHash();
  
  return 0;
}


