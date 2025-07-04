#include <stdio.h>

const int TEXT_LEN = 21;
const int MAX = 50000;

struct TWord
{
  char Text[TEXT_LEN];
  int F;
  int L; // Length
  int LastNumber;
  bool Valid;
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

char Result[1000000];  // Текст результат
int ResLen; // его длина

int WordNumber = 1; // Номер текущего слова


char NewWord[21];



void GenArr()
{
  if(Slovo)
  {
    int i, j, q, a;
    bool flag;

    ValidCount = 0;

    for(i = 0; i < WordsCount; i++)
      if(Words[i].L == Len)
      {
        Words[i].Valid = true;
        for(j = 0; j < Len; j++)
        {
          flag = false;

          for(q = 0; q < arrlen[ NewWord[j]-50]; q++)
          {

            if( Words[i].Text[j] == arr[ NewWord[j] - 50 ][q] )
            {
              flag = true;
              break;
            }
          }


          if(!flag)
          {
            Words[i].Valid = false;
            break;
          }

        } // for

        if(Words[i].Valid)
        {

          // Вставляем в valid массив
          if(ValidCount == 0)
            ValidWords[0] = &Words[i];
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
      else
        Words[i].Valid = false;


    if(ValidCount > 0)
      Choice = 0;

    Slovo = false;

  } // if Slovo

}

void AddWord()
{
  if(Choice > -1)
  {

    if(Devider)
    {
      Result[ResLen] = dev[ Choice ];
      ResLen++;

      Devider = false;
    }
    else
    {
      int i;
      for(i = 0; i < ValidWords[Choice]->L; i++)
        Result[ResLen+i] = ValidWords[Choice]->Text[i];
      ResLen += i;

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
      Len++;

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

          Result[ResLen] = ' ';
          ResLen++;

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

  for(i = 0; i < ResLen; i++)
    printf("%c", Result[i]);

         
  return 0;
}


