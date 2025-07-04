#include <iostream>
#include <algorithm>
#include <string.h>
#include <time.h>
#include <vector>


//using std::cout;
//using std::cin;
//using std::endl;
using namespace std;

class dict_word // слово в словаре
{
private:
    char word[21]; // слово
    int length; // длина

public:
    int rate; // частота
    int magic; // степень "подн€того" элемента
    void input()//char itext[], int ilength, int irate)
    {
        magic = 0; // задание степени
        cin.get(); // сшибаем lf
        cin.get(word, 21, ' '); // ввод слова до пробела
        length = strlen(word); // получение длины слова

        cin >> rate; // ввод частоты
     }

    void output()
    {
            cout << word;
    }

    void incr(int index)
    {
        magic = index;
      //  cout << endl << "MAGIC:  " << magic << endl;
        rate ++;
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

bool operator<(const dict_word & word1, const dict_word & word2) // сравнение
{
    return (word1.rate > word2.rate || (word1.rate == word2.rate && word1.magic > word2.magic));
    //return (word1.rate > word2.rate);
}


class plate // узел
{
public:
    vector <dict_word> vect; // вектор
    bool empty; // пустой
    bool sort;
    plate *array;

    plate()
    {
        empty = true; // пустой
        sort = false; // не отсортированный
    }

    inline void initialise()
    {
        array = new plate[8];
        empty = false;
    }

    inline void push(dict_word iword)
    {
        vect.push_back(iword);
    }

    inline void sorting(int end = 0) // сортировка
    {
        if (end == 0)
            stable_sort (vect.begin(), vect.end()); // сортировать всЄ
        else
            stable_sort(vect.begin(), vect.begin() + end); // сортировать максимальные
    }

    inline void output(int ind)
    {
//        cout << endl << endl;
//        for(int i = 0; i < vect.size(); ++ i)
//        {
//            cout << endl;
//            vect[i].output();
//            cout  << " (" << vect[i].rate << ") ";
//        }
//        cout << endl << ind << " true:  ";
        vect[ind].output();
    }
};

class dict // словарь
{
private:
    plate *first;
    int size; // размер словар€
    int buttons[26]; // интервалы ASC-кодов дл€ кнопок
    char characters[3]; // знаки препинани€

public:
   void initialise () // инициализаци€ словар€
   {
       first = new plate; // отводим пам€ть под первый элемент
       first->initialise(); // иницализаци€ массива
       cin >> size; // ввод размера
       
       plate *buff_plate = first; // буферный узел
       dict_word buffer;
//       int inner_count = 0;

       int count = 0;

       // объ€вление массива с адресами кнопок
       buttons[0] = 0;
       buttons[1] = 0;
       buttons[2] = 0;
       buttons[3] = 1;
       buttons[4] = 1;
       buttons[5] = 1;
       buttons[6] = 2;
       buttons[7] = 2;
       buttons[8] = 2;
       buttons[9] = 3;
       buttons[10] = 3;
       buttons[11] = 3;
       buttons[12] = 4;
       buttons[13] = 4;
       buttons[14] = 4;
       buttons[15] = 5;
       buttons[16] = 5;
       buttons[17] = 5;
       buttons[18] = 5;
       buttons[19] = 6;
       buttons[20] = 6;
       buttons[21] = 6;
       buttons[22] = 7;
       buttons[23] = 7;
       buttons[24] = 7;
       buttons[25] = 7;
       // конец

       for (count = 0; count < size; ++ count)
       {
           buffer.input(); // ввод слова и мощи
           buff_plate = first;
           for (int iter = 0; iter < buffer.return_leigth(); ++ iter) // проход по буквам
           {
              // cout << endl << iter <<" ("<< buffer.asc_litera(iter) - 97 << " ---> (" << buttons[buffer.asc_litera(iter) - 97] << ")"; // отладка
               if(buff_plate->empty) // если узел пустой
               {
                   buff_plate->initialise(); // инициализируем
               }

               buff_plate = &buff_plate->array[buttons[buffer.asc_litera(iter) - 97]]; // переходим
           }
           buff_plate->push(buffer); // вставл€ем
       }


       // инициализаци€ знаков препинани€
       characters[0] = '.';
       characters[1] = ',';
       characters[2] = '?';
       // конец инициализации знаков препинани€
   }

   void parser()
   {
       int count = 0; // счЄтчик
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
           case 42: // звезда
               {
                   count = 1;
                   while(cin.peek() == 42)
                   {
                       buf = cin.get();
                           count ++;
                   }

                   search(string, leigth, count);// вызов функции поиска
                   break;
               }
           case 49: // дл€ знаков препинани€
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
           case 32: // дл€ пробела
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

   inline void search(int string[], int leigth, int stars = 0) // поиск
   {
       static int index = 0; // маги€
       index ++; // инкримент

       plate *buff_plate = first; // буферный указатель
       int count = 0;

       for (count = 0; count < leigth; ++ count)
       {
           buff_plate = &buff_plate->array[string[count]];
       }
       if (!buff_plate->sort)
           buff_plate->sorting();

       buff_plate->vect[stars].incr(index); // увеличение магии и частоты
       buff_plate->output(stars); // вывод

       if (stars != 0)
           buff_plate->sorting(stars);
   }
};


int main()
{
//    // тест времени
//    clock_t start, end;
//    double elapsed;
//    start = clock();

    dict dict1;
    dict1.initialise();
    //dict1.input();
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
    return 0;
}
