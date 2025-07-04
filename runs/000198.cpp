#include <iostream>
#include <string.h>
#include <time.h>


using std::cout;
using std::cin;
using std::endl;

class dict_word // ����� � �������
{
private:
    char word[21]; // �����
    int length; // �����
    int rate; // �������
    int magic; // ������� "���������" ��������

public:
    void input()//char itext[], int ilength, int irate)
    {
        magic = 0; // ������� �������
        cin.get(word, 22, ' '); // ���� ����� �� �������
        length = strlen(word); // ��������� ����� �����

        cin >> rate; // ���� �������
     }

    void output()
    {

        for (int i = 1; i < length; i++)
        {
            cout << word[i];
        }
    }

    void incr(int index)
    {
        magic = index;
       // cout << endl << "MAGIC:  " << magic << endl;
        rate ++;
    }

    int return_rate()
    {
        return rate;
    }

    int return_magic()
    {
        return magic;
    }

    int return_leigth()
    {
        return length;
    }

    int asc_litera(int num)
    {

            return word[num];
    }
};

struct list // ������ "��������"
{
    int index; // ������ ��������
    list *next; // ������ �� ��������� ������� ������

    list()
    {
        index = -1;
        next = NULL;
    }
};

class dict // �������
{
private:
    dict_word *array; // �������
    int size; // ������ �������
    int contents[8]; // ���������� �� �������
    int buttons[8]; // ��������� ASC-����� ��� ������
    char characters[3]; // ����� ����������

public:
   void initialise () // ������������� �������
   {
       cin >> size; // ���� �������
       array = new dict_word[size]; // ��������� ������

       int asc2 = 97;
       int count = 0;
       while (count < 8)
       {
           buttons[count] = asc2;
           contents[count] = -1;
           count ++;
           if (count == 6)
               asc2 += 4;
           else
               asc2 += 3;
       }

       // ������������� ������ ����������
       characters[0] = '.';
       characters[1] = ',';
       characters[2] = '?';
       // ����� ������������� ������ ����������
   }

   void input()// ���������� �������
   {
       int count = 0; // �������
       int button_count = 0; // ������� ����������

       for (count = 0; count < size; count ++)
       {
           array[count].input(); // ����

           while(button_count < 8)
           {
              if(array[count].asc_litera(1) >= buttons[button_count]) // ���� ������ ����� ����� �������� � ������������ ������
              {
                  if(button_count == 7 || array[count].asc_litera(1) < buttons[button_count + 1])
                  {
                      if(contents[button_count] == -1) // ���� ������ � ���������� �� ������
                        contents[button_count] = count;
                      break;
                  }
              }              
              button_count ++;
          }
       }

 /*      count = 0;
       cout << endl;
       while (count < 8)
       {
           cout << "Button " << count + 1 << ":  " << buttons[count] << endl;
           count ++;
       }

       count = 0;
       cout << endl;
       while (count < 8)
       {
           cout << "Button " << count + 1 << ":  " << contents[count] << endl;
           count ++;
       }*/
   }

   void parser()
   {
       int count = 0; // �������
       char buf = 0;

       int leigth = 0; // ����� �����
       int string[20]; // ������ ������

       if (cin.peek() == 10)
        buf = cin.get();

       while(1)
       {
           for (count = 0; count <= 20; count++)
           {
                buf = cin.get();
                //cout << (int)buf;
                if (buf > 49 && buf < 58)
                {
                    string[count] = buf - 50;
                    //cout << string[count];
                }
                else
                {
                    break;
                }
           }

           leigth = count; // ���������� ����� �����

           switch(buf)
           {
           case 42:
               {
                   count = 1;
                   while(cin.peek() == 42)
                   {
                       buf = cin.get();
                           count ++;
                   }

                   search(string, leigth, count + 1);// ����� ������� ������
                   break;
               }
           case 49: // ��� ������ ����������
               {
                   if (count != 0)
                    search(string, leigth);// ����� ������� ������
                   count = 0;

                       while(cin.peek() == 42)
                       {
                           buf = cin.get();
                           count ++;
                           if (count == 3)
                           {
                               count = 0;
                           }
                       }

                   cout << characters[count];
                   break;
               }
           case 32: // ��� �������
               {
                   if (count != 0)
                    search(string, leigth);// ����� ������� ������
                   cout << " ";
                   break;
               }
           default:
               {
                   if (count != 0)
                    search(string, leigth);// ����� ������� ������
                   return;
                   break;
               }
           } // ����� ������
       } // ����� while(1)
   }


   inline void search(int string[], int leigth, int stars = 1) // ����� �����
   {
       // ������ �� �������
       list *query; // ������ �����������
       query = new list; // ��������� ������
       list * buff = query; // �����
       list *buff2; // ������ �����

       int count;

       for (count = 0; count < stars; count++) // �������� ������
       {
           buff->next = new list; //��������� ������
           buff = buff->next; // ������� � ���������� ��������
       }

       // ������ � �����������
       int start = contents[string[0]]; // ��������� ����� ������
       int end = -1; // �������� �����

       for (count = 1; count <= (7 - string[0]); count++ )  // ����� �����
       {
           if(contents[string[0] + count] != -1) // ���� ������� ��������
           {
               end = contents[string[0] + count];
               break;
           }
       }
       if(end == -1)
           end = size;


       //������ �� �������
       bool it;
       static int magic = 0;
       magic ++;

       for (start; start < end; start ++)
       {
           it = false;
           if (array[start].return_leigth() == leigth + 1)
           {
               //cout << endl;
               //array[start].output();
               //cout << ":  ";
               if(leigth == 1) // ���� ���� �����
               {
                   it = true;
               }
               else
               {
                   for (count = leigth - 1; count > 0; count --) // ������������� ����� � ����
                   {
                       it = false;
                       //cout << endl << "   Button: " << buttons[string[count]] << " <= " << array[start].asc_litera(count + 1);
                       if (buttons[string[count]] <= array[start].asc_litera(count + 1))
                       {
                           if(string[count] == 7 || buttons[string[count] + 1] > array[start].asc_litera(count + 1))
                           {
                               it = true;
                           }
                       } // ����� ��������� ��������

                       if (!it)
                           break;
                   } // ����� �����
               }
           }
           if (!it) // ���� ����� �������
           {
               continue;
           }
           else
           {
             buff = query;

             for (count = 0; count < stars; count ++)
             {
                 if(buff->index == -1)
                 {
                     buff->index = start;
                     //cout << endl << start << "   " << buff->index << endl;
                     break;
                 }
                 else
                 {
                     if((array[buff->index].return_rate() < array[start].return_rate()) || (array[buff->index].return_rate() == array[start].return_rate() && array[buff->index].return_magic() < array[start].return_magic()))
                     {
                        // cout << endl << array[buff->index].return_rate() << " < " << array[start].return_rate();
                         buff2 = new list; // ������ �������� �������
                         buff2->index = buff->index; // �������� ���� ��������
                         buff2->next = buff->next;

                         buff->next = buff2; //���������
                         buff->index = start;
                         break;
                     }
                 }
                 buff = buff->next;
             }
           }
       } // ����� ����� ������� �� �������

      // count = 0;
       buff = query;
       for (count = 0; count < stars - 1; count ++)
       {
           buff = buff->next;
       }
       array[buff->index].output(); // �����
       array[buff->index].incr(magic); // ���������� �������
       //cout << endl << endl; // �������
       //cout << "Pezd: " << stars << endl << endl; // �������
   }
};


int main()
{
    // ���� �������
//    clock_t start, end;
//    double elapsed;
//    start = clock();

    dict dict1;
    dict1.initialise();
    dict1.input();
    dict1.parser();

//    // ���� �������
//    end = clock();
//    elapsed=((double)(end-start))/CLOCKS_PER_SEC;
//    cout << endl << "TIME: " << elapsed;// ���� �������
//
//    while(1)
//    {
//        cin.get();
//    }
//    return 0;
}
