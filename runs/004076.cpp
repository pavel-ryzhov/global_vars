#include <stdio.h>

const int TEXT_LEN = 21;
const int MAX = 50000;


struct TWord
{
  char Text[TEXT_LEN];
  char TextK[TEXT_LEN]; 
  int F;
  int L; // Length
  int LastNumber;
};

int arrlen[8] = {3, 3, 3, 3, 3, 4, 3, 4 };
char arr[8][5] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };


char dev[4] = ".,?";

TWord Words[MAX];
int WordsCount = 0;

TWord * ValidWords[MAX];
int ValidCount = 0;

int Index = 0; // Текущий символ
int Len; // Длина текущего слова

int Choice = -1;


bool Slovo = false;
bool Devider = false;


int WordNumber = 1; // Номер текущего слова


char NewWord[TEXT_LEN];


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


void GenArr()
{
  if(Slovo)
  {
    int i, j, q, a;
    bool flag;
    bool Valid;

    ValidCount = 0;

    for(i = 0; i < WordsCount; i++)
      if(Words[i].L == Len)
      {
         flag = true;

         for(j = 0; j < Len; j++)
           if (Words[i].TextK[j] != NewWord[j])
           {
             flag = false;
             break;
           }

         if(flag)
         {
          // Вставляем в valid массив
          if(ValidCount == 0)
          {
            ValidWords[0] = &Words[i];
            Choice = 0;
          }
          else
          {

            for( q = 0; q < ValidCount; q++)
            {
              if ( (Words[i].F > ValidWords[q]->F) ||
                   ((Words[i].F == ValidWords[q]->F) && (Words[i].LastNumber > ValidWords[q]->LastNumber)) ) { break; }
            }

            for(a = ValidCount+1; a > q; a--)
              ValidWords[a] = ValidWords[a-1];

            ValidWords[q] = &Words[i];

          }

          ValidCount++;
        }
      }


    Slovo = false;

  } // if Slovo

}

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
      printf("%s", ValidWords[Choice]->Text);

      ValidWords[Choice]->F++;
      ValidWords[Choice]->LastNumber = WordNumber;

      WordNumber++;

      ValidCount = 0;
    }

    Choice = -1;
  }
}


int main()
{

  char c;

  scanf("%d", &WordsCount);

  int i;
  for(i = 0; i < WordsCount; i++)
  {
    getchar();
    Words[i].L = 0;
    while ((c = getchar()) != ' ')
    {
      Words[i].Text[Words[i].L] = c;
      Words[i].TextK[Words[i].L] = GetKey(c);
      
      Words[i].L++;
    }

    scanf("%d", &Words[i].F);
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
      }

      GenArr();

      switch(c)
      {
        case '1':
        {
          AddWord();

          Devider = true;
          Choice = 0;
          ValidCount = 3;

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
          if(Choice > -1)
          {
            Choice++;
            if(Choice >= ValidCount) Choice = 0;
          }
          break;
        }
      }


    } // else

  }

  if(Choice == -1)
    GenArr();

  AddWord();

  return 0;
}


