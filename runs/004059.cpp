
#include <iostream>
#include <string.h>

using namespace std;


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

void GenArr()
{
  int j, q, a;
  
  // Если есть набранное слово
  if(Slovo)
  {
    ValidCount = 0;

    // Формируем массив из сортированных подходящих слов
    for(j = 0; j < WordsCount; j++)
      if ((Words[j].Valid) && (Words[j].L == Len+1))
      {
        if(ValidCount == 0)
        {
          ValidWords[0] = &Words[j];
        }
        else
        {

          for( q = 0; q < ValidCount; q++)
          {
            if (Words[j].F > ValidWords[q]->F) { break; }

            if ((Words[j].F == ValidWords[q]->F) && (Words[j].LastNumber > ValidWords[q]->LastNumber)) { break; }
          }

          for(a = ValidCount+1; a > q; a--)
            ValidWords[a] = ValidWords[a-1];

          ValidWords[q] = &Words[j];

      }

      ValidCount++;
    }

    if(ValidCount > 0)
      Choice = 0;
  }
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
      for(i = 0; ValidWords[Choice]->Text[i] != '\0'; i++)
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

  cin >> WordsCount;

  int i;
  for(i = 0; i < WordsCount; i++)
  {
    cin >> Words[i].Text >> Words[i].F;
    Words[i].L = strlen(Words[i].Text);
    Words[i].LastNumber = 0;
  }

  char c;

  int q, j;

  while(cin.get(c))
  {
    if ( (c >= '2') && (c <= '9') )
    {
      if(!Slovo)
      {

        AddWord();

        // Начинаем набирать новое слово
        Slovo = true;
        Len = 0;

        // Пока подходит весь словарь
        for(i = 0; i < WordsCount; i++)
          Words[i].Valid = true;

      }
      else
        Len++;

      bool flag;

      char * Key = arr[ c - 50 ];

      // Обозначаем слова, которые не подходят
      for(j = 0; j < WordsCount; j++)
        if (Words[j].Valid)
        {
          flag = false;

          for(q = 0; (Key[q] != '\0'); q++)
            if( Words[j].Text[Len] == Key[q] )
            {
              flag = true;
              break;
            }

          Words[j].Valid = flag;
        }

    }
    else
    {

      GenArr();

      Slovo = false;

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

    Index++; 
  }


  GenArr();

  AddWord();

  for(i = 0; i < ResLen; i++)
    cout.put(Result[i]);

  return 0;
}


