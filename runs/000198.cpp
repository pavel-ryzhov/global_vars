#include <iostream>
#include <string.h>
#include <time.h>


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

       for (count = 0; count < size; count ++)
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
       int count = 0; // счётчик
       char buf = 0;

       int leigth = 0; // длина слова
       int string[20]; // строка кнопок

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


   inline void search(int string[], int leigth, int stars = 1) // поиск слова
   {
       // работа со списком
       list *query; // список результатов
       query = new list; // выделение памяти
       list * buff = query; // буфер
       list *buff2; // второй буфер

       int count;

       for (count = 0; count < stars; count++) // создание списка
       {
           buff->next = new list; //выделение памяти
           buff = buff->next; // переход к следующему элементу
       }

       // работа с оглавлением
       int start = contents[string[0]]; // начальная точка поиска
       int end = -1; // конечная точка

       for (count = 1; count <= (7 - string[0]); count++ )  // поиск конца
       {
           if(contents[string[0] + count] != -1) // если элемент заполнен
           {
               end = contents[string[0] + count];
               break;
           }
       }
       if(end == -1)
           end = size;


       //Работа со словарём
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
               if(leigth == 1) // если одна буква
               {
                   it = true;
               }
               else
               {
                   for (count = leigth - 1; count > 0; count --) // сопоставление слова и кода
                   {
                       it = false;
                       //cout << endl << "   Button: " << buttons[string[count]] << " <= " << array[start].asc_litera(count + 1);
                       if (buttons[string[count]] <= array[start].asc_litera(count + 1))
                       {
                           if(string[count] == 7 || buttons[string[count] + 1] > array[start].asc_litera(count + 1))
                           {
                               it = true;
                           }
                       } // конец первичной проверки

                       if (!it)
                           break;
                   } // конец цикла
               }
           }
           if (!it) // если слово совпало
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
                         buff2 = new list; // создаём буферный элемент
                         buff2->index = buff->index; // копируем поля текущего
                         buff2->next = buff->next;

                         buff->next = buff2; //подменяем
                         buff->index = start;
                         break;
                     }
                 }
                 buff = buff->next;
             }
           }
       } // конец цикла прохода по словарю

      // count = 0;
       buff = query;
       for (count = 0; count < stars - 1; count ++)
       {
           buff = buff->next;
       }
       array[buff->index].output(); // вывод
       array[buff->index].incr(magic); // увеличение частоты
       //cout << endl << endl; // отладка
       //cout << "Pezd: " << stars << endl << endl; // отладка
   }
};


int main()
{
    // тест времени
//    clock_t start, end;
//    double elapsed;
//    start = clock();

    dict dict1;
    dict1.initialise();
    dict1.input();
    dict1.parser();

//    // тест времени
//    end = clock();
//    elapsed=((double)(end-start))/CLOCKS_PER_SEC;
//    cout << endl << "TIME: " << elapsed;// тест времени
//
//    while(1)
//    {
//        cin.get();
//    }
//    return 0;
}
