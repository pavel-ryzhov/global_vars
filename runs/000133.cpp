#include <iostream>
#include <string.h>


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
        int i = 1;
        //cout << endl << "Flinna^ " << length << endl;
        while (i < length)
        {
            cout << word[i];
            i ++;
        }
       // cout << " (" << magic << ")";
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

    int asc_litera(int num)
    {
        if (num == 22)
        {
            return length;
        }
        else
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

       while(count < size)
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

           count ++;
       }
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
           count = 0;
           while (count < 20)
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

                count ++;
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


   void search(int string[], int leigth, int stars = 1) // ����� �����
   {
       // ������ �� �������
       list *query; // ������ �����������
       query = new list; // ��������� ������
       list * buff = query; // �����
       list *buff2; // ������ �����

       int count = 0;

       while(count < stars) // �������� ������
       {
           buff->next = new list; //��������� ������
           buff = buff->next; // ������� � ���������� ��������
           count ++; // ���������
       }

       // ������ � �����������
       int start = contents[string[0]]; // ��������� ����� ������
       int end = -1; // �������� �����

       count = 1;

       while (count <= (7 - string[0]))  // ����� �����
       {
           if(contents[string[0] + count] != -1) // ���� ������� ��������
           {
               end = contents[string[0] + count];
               break;
           }
           else
           {
               if(7 - string[0] == 1) // ���� ������������� ������, � �������� ��� ��������� �����������
               {
                   end = size;
                   break;
               }
           }
           count ++;
       }
       if(end == -1)
           end = size;
      // cout << endl << "start: " << start << endl << "end: " << end; // �������


       //������ �� �������
       bool it;
       static int magic = 0;
       magic ++;

       while (start < end)
       {
           it = false;
           if (array[start].asc_litera(22) == leigth + 1)
           {
               count = 1;
               while(count < leigth) // ������������� ����� � ����
               {
                   if (buttons[string[count]] <= array[start].asc_litera(count + 1))
                   {
                       if(string[count] == 7)
                       {
                           it = true;
                       }
                       else
                       {
                           if (buttons[string[count] + 1] >= array[start].asc_litera(count + 1))
                           {
                               it = true;
                           }
                       }
                   } // ����� ��������� ��������

                   count ++;
               } // ����� �����

               if(leigth == 1)
               {
                   it = true;
               }
           }
           if (it) // ���� ����� �������
           {
             count = 0;
             buff = query;
             while(count < stars)
             {
                 if(buff->index == -1)
                 {
                     buff->index = start;
                     //cout << endl << start << "   " << buff->index;
                     break;
                 }
                 else
                 {
                     if((array[buff->index].return_rate() < array[start].return_rate()) || (array[buff->index].return_rate() == array[start].return_rate() && array[buff->index].return_magic() < array[start].return_magic()))
                     {
                         //cout << endl << array[buff->index].return_rate() << " < " << array[start].return_rate();
                         buff2 = new list; // ������ �������� �������
                         buff2->index = buff->index; // �������� ���� ��������
                         buff2->next = buff->next;

                         buff->next = buff2; //���������
                         buff->index = start;
                         buff = buff->next;
                         break;
                     }
                 }
                 buff = buff->next;
                 count ++;
             }
           }
           start ++;
       } // ����� ����� ������� �� �������

       count = 0;
       buff = query;
       while(count < stars - 1)
       {
           //cout << buff->index;
           buff = buff->next;
           count ++;
       }
       array[buff->index].output(); // �����
       array[buff->index].incr(magic); // ���������� �������
   }
};


int main()
{
    dict dict1;
    dict1.initialise();
    dict1.input();
    dict1.parser();

    int i;
    cin >> i;
    cin >> i;
    cin >> i;

    return 0;
}
