
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

TWord Words[MAX];
int WordsCount = 0;

TWord * ValidWords[MAX];
int ValidCount = 0;

int Index; // ������� ������
int Len; // ����� �������� �����

int Choice = -1;

bool Slovo = false;
bool Devider = false;

char Result[1000000];  // ����� ���������

int WordNumber = 1; // ����� �������� �����



void GenArr()
{
  int j, q, a;
  
  // ���� ���� ��������� �����
  if(Slovo)
  {
    ValidCount = 0;

    // ��������� ������ �� ������������� ���������� ����
    for(j = 0; j < WordsCount; j++)
      if ((Words[j].Valid) && (strlen(Words[j].Text) == Len+1))
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
    Words[i].LastNumber = 0;
  }

  char t[100000];

  cin.getline(t, 100000);

  cin.getline(t, 100000);


  int q, j;

  for(Index = 0; Index < strlen(t); Index++)
  {
    if ( (t[Index] >= '2') && (t[Index] <= '9') )
    {
      if(!Slovo)
      {

        AddWord();

        // �������� �������� ����� �����
        Slovo = true;
        Len = 0;

        // ���� �������� ���� �������
        for(i = 0; i < WordsCount; i++)
          Words[i].Valid = true;

      }
      else
        Len++;

      bool flag;

      char * c = arr[ t[Index] - 50 ];

      // ���������� �����, ������� �� ��������
      for(j = 0; j < WordsCount; j++)
        if (Words[j].Valid)
        {
          flag = false;

          for(q = 0; ((q < 5)&&(c[q] != '\0')); q++)
            if( Words[j].Text[Len] == c[q] )
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


  GenArr();

  AddWord();

  cout << Result;

  return 0;
}


