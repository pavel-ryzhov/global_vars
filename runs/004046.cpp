
#include <iostream>
#include <string.h>

using namespace std;


const int TEXT_LEN = 21;
const int MAX = 50000;

struct TWord
{
  char Text[TEXT_LEN];
  int F;
  int LastNumber;
  bool Valid;
};


char arr[8][5] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

char dev[4] = ".,?";

int CharToInt(char c)
{
  switch(c)
  {
    case '0': return 0; break;
    case '1': return 1; break;
    case '2': return 2; break;
    case '3': return 3; break;
    case '4': return 4; break;
    case '5': return 5; break;
    case '6': return 6; break;
    case '7': return 7; break;
    case '8': return 8; break;
    case '9': return 9; break;
  }
}


TWord Words[MAX];
int WordsCount = 0;

TWord * ValidWords[MAX];
int ValidCount = 0;

int Index; // Текущий символ
int Len; // Длина текущего слова

int Choice = -1;

bool Slovo = false;
bool Devider = false;

char Result[1000000];  // Текст результат

int WordNumber = 0; // Номер текущего слова


void AddWord()
{
  if(Choice > -1)
  {

    if(Devider)
    {
      switch(Choice)
      {
        case 0: { strcat(Result, "."); break; }
        case 1: { strcat(Result, ","); break; }
        case 2: { strcat(Result, "?"); break; }
      }
      Devider = false;
    }
    else
    {
      strcat(Result, ValidWords[Choice]->Text);
      ValidWords[Choice]->F++;
      ValidWords[Choice]->LastNumber = WordNumber;

      WordNumber++;

      for(int i = 0; i < ValidCount; i++)
        ValidWords[i] = NULL;

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
  }


  for(i = 0; i < WordsCount; i++)
  {
    Words[i].LastNumber = 0;
  }

  char t[100000];

  cin.getline(t, 100000);

  cin.getline(t, 100000);


  int j, q;

  for(Index = 0; Index < strlen(t); Index++)
  {
    if ( (t[Index] >= '2') && (t[Index] <= '9') )
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

      // Обозначаем слова, которые не подходят
      for(j = 0; j < WordsCount; j++)
        if (Words[j].Valid)
        {
          bool flag = false;

          for(q = 0; q < strlen( arr[ CharToInt(t[Index])-2 ]) ; q++)
          {
            if( Words[j].Text[Len] == arr[ CharToInt(t[Index])-2 ][q] )
              flag = true;
          }

          Words[j].Valid = flag;
        }

    }
    else
    {
      // Если есть набранное слово
      if(Slovo)
      {
        ValidCount = 0;

        // Формируем массив из сортированных подходящих слов
        for(j = 0; j < WordsCount; j++)
          if (Words[j].Valid)
          {
            if(ValidCount == 0)
            {
              ValidWords[0] = &Words[j];
            }
            else
            {

              for(q = 0; q < ValidCount; q++)
              {
                if (Words[j].F > ValidWords[q]->F) { break; }

               if ((Words[j].F == ValidWords[q]->F) && (Words[j].LastNumber > ValidWords[q]->LastNumber)) { break; }
              }

              for(int a = ValidCount+1; a > q; a--)
                ValidWords[a] = ValidWords[a-1];

              ValidWords[q] = &Words[j];

            }

            ValidCount++;
          }

        if(ValidCount > 0)
          Choice = 0;
      }

      Slovo = false;

      switch(t[Index])
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
          strcat(Result, " ");

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

  AddWord();


  cout << Result;

  return 0;
}


