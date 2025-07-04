#include <iostream>
#include <string.h>


using std::cout;
using std::cin;
using std::endl;

class dict_word // слово в словаре
{
private:
    char word[21]; // слово
    int length; // длина
    int rate; // частота
    int magic; // степень "поднятого" элемента

public:
    void input()//char itext[], int ilength, int irate)
    {
        magic = 0; // задание степени
        cin.get(word, 22, ' '); // ввод слова до пробела
        length = strlen(word); // получение длины слова

        cin >> rate; // ввод частоты
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

struct list // список "звёздочек"
{
    int index; // индекс элемента
    list *next; // ссылка на следующий элемент списка

    list()
    {
        index = -1;
        next = NULL;
    }
};

class dict // словарь
{
private:
    dict_word *array; // словарь
    int size; // размер словаря
    int contents[8]; // оглавление по кнопкам
    int buttons[8]; // интервалы ASC-кодов для кнопок
    char characters[3]; // знаки препинания

public:
   void initialise () // инициализация словаря
   {
       cin >> size; // ввод размера
       array = new dict_word[size]; // выделение памяти

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

       // инициализация знаков препинания
       characters[0] = '.';
       characters[1] = ',';
       characters[2] = '?';
       // конец инициализации знаков препинания
   }

   void input()// заполнение словаря
   {
       int count = 0; // счётчик
       int button_count = 0; // счётчик оглавления

       while(count < size)
       {
           array[count].input(); // ввод

           while(button_count < 8)
           {
              if(array[count].asc_litera(1) >= buttons[button_count]) // если первая буква слова попадает в пространство кнопок
              {
                  if(button_count == 7 || array[count].asc_litera(1) < buttons[button_count + 1])
                  {
                      if(contents[button_count] == -1) // если ячейка в оглавлении не занята
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
       int count = 0; // счётчик
       char buf = 0;

       int leigth = 0; // длина слова
       int string[20]; // строка кнопок

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

           leigth = count; // запоминаем длину слова

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

                   search(string, leigth, count + 1);// вызов функции поиска
                   break;
               }
           case 49: // для знаков препинания
               {
                   if (count != 0)
                    search(string, leigth);// вызов функции поиска
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
           case 32: // для пробела
               {
                   if (count != 0)
                    search(string, leigth);// вызов функции поиска
                   cout << " ";
                   break;
               }
           default:
               {
                   if (count != 0)
                    search(string, leigth);// вызов функции поиска
                   return;
                   break;
               }
           } // конец свитча
       } // конец while(1)
   }


   void search(int string[], int leigth, int stars = 1) // поиск слова
   {
       // работа со списком
       list *query; // список результатов
       query = new list; // выделение памяти
       list * buff = query; // буфер
       list *buff2; // второй буфер

       int count = 0;

       while(count < stars) // создание списка
       {
           buff->next = new list; //выделение памяти
           buff = buff->next; // переход к следующему элементу
           count ++; // инкримент
       }

       // работа с оглавлением
       int start = contents[string[0]]; // начальная точка поиска
       int end = -1; // конечная точка

       count = 1;

       while (count <= (7 - string[0]))  // поиск конца
       {
           if(contents[string[0] + count] != -1) // если элемент заполнен
           {
               end = contents[string[0] + count];
               break;
           }
           else
           {
               if(7 - string[0] == 1) // Если предпоследняя кнопка, а значение для последней отсутствует
               {
                   end = size;
                   break;
               }
           }
           count ++;
       }
       if(end == -1)
           end = size;
      // cout << endl << "start: " << start << endl << "end: " << end; // отладка


       //Работа со словарём
       bool it;
       static int magic = 0;
       magic ++;

       while (start < end)
       {
           it = false;
           if (array[start].asc_litera(22) == leigth + 1)
           {
               count = 1;
               while(count < leigth) // сопоставление слова и кода
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
                   } // конец первичной проверки

                   count ++;
               } // конец цикла

               if(leigth == 1)
               {
                   it = true;
               }
           }
           if (it) // если слово совпало
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
                         buff2 = new list; // создаём буферный элемент
                         buff2->index = buff->index; // копируем поля текущего
                         buff2->next = buff->next;

                         buff->next = buff2; //подменяем
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
       } // конец цикла прохода по словарю

       count = 0;
       buff = query;
       while(count < stars - 1)
       {
           //cout << buff->index;
           buff = buff->next;
           count ++;
       }
       array[buff->index].output(); // вывод
       array[buff->index].incr(magic); // увеличение частоты
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
