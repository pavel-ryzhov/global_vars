#include <iostream>
#include <string.h>


using std::cout;
using std::cin;
using std::endl;

class plate // лист
{
private:
    int weight; // вес связи
    int link; // ссылка

public:
    plate() // конструктор по умолчанию
    {
        weight = 0;
        link = -1;
    }

    void input(int iweight, int ilink) // ввод
    {
        weight = iweight;
        link = ilink;
    }

    void output()
    {
        cout << endl << " Link: " << link << " Weight: " << weight;
    }

    int return_link()
    {
        return link;
    }

    int return_weight()
    {
        return weight;
    }

};

class tree //дерево
{
private:
    plate *array; // массив дерева
    int *plate1_array; // вспомогательный массив для первого узла
    int *plate2_array; // вспомогательный массив для второго узла
    int size; // размер
public:
    void initialise () // инициализация
    {
        // инициализация массива
        cin >> size; // ввод количества элементов
        array = new plate[size]; // отводим память
        plate1_array = new int[size]; // отводим память под первый узел
        plate2_array = new int[size]; // отводим память под второй узел


        // заполнение значений
        int link = 0; // буферная переменная для ссылок
        int weight = 0; // буферная переменная для веса
        int number = 0; // буферная переменная для номера элемента
        int count = 0; // счётчик
        int size_buf = size - 1;

        for (count = 0; count < size_buf; count ++)
        {
            // ввод основных параметров
            cin >> link;
            cin >> number;
            cin >> weight;

            // вброс в листья
            array[number - 1].input(weight, link - 1);

            // отладка
            //array[number - 1].output();
            //cout << " Number: " << number - 1 << endl;
        }

    }

    void parser_search() // парсер и поиск
    {
        // параметры вводимой строки
        int str_size = 0; // размер строки вводимых значений
        int count = 0; // счётчик


        // параметры узлов
        int plate1 = 0; // первый узел
        int plate2 = 0; // второй узел
        int plate1_count = 0;
        int plate2_count = 0;
        int plate1_distance = 0;
        int plate2_distance = 0;

        // общее
        int sum_distance = 0; // суммарная дистанция
        int buffer;


        cin >> str_size; // ввод размера

        // ввод значений
        for (count = 0; count < str_size; count ++)
        {
            cin >> plate1 >> plate2; // вводим значения первого и второго узлов

            buffer = plate1 - 1;
            plate1_distance = 0;
            plate2_distance = 0;

            plate1_count = 0;
            plate2_count = 0;

            // внесение ветки во вспомогательный массив для первого узла
            do
            {
                // cout << endl << "count: " << plate1_count << "buffer: " << buffer << " ---> " << array[buffer].return_link(); //отладка
                plate1_distance += array[buffer].return_weight(); // копим вес
                plate1_array[plate1_count] = buffer; // заносим элемент
                buffer = array[buffer].return_link(); // переключаемся
                plate1_count ++; // инкримент
            }
            while (buffer >= 0);         


            buffer = plate2 - 1; // кладём начальное значение
            // внесение ветки во вспомогательный массив для второго узла
            do
            {
                //cout << endl << "count: " << plate2_count << "buffer: " << buffer << " ---> " << array[buffer].return_link(); //отладка
                plate2_distance += array[buffer].return_weight(); // копим вес
                plate2_array[plate2_count] = buffer; // заносим элемент
                buffer = array[buffer].return_link(); // переключаемся
                plate2_count ++; // инкримент
            }
            while (buffer >= 0);

//            // отладка
//            plate2_count--;
//            while (plate2_count >= 0)
//            {
//                cout << endl << plate2_count << ": "<< plate2_array[plate2_count];
//                plate2_count --;
//            }
//
//            plate1_count--;
//            while (plate1_count >= 0)
//            {
//                cout << endl << plate1_count << ": "<< plate1_array[plate1_count];
//                plate1_count --;
//            }

            sum_distance = plate1_distance + plate2_distance;
           // cout << endl<< sum_distance << endl;
            plate2_count --;
            plate1_count --;

            while(plate2_array[plate2_count] == plate1_array[plate1_count])
            {
                //cout << endl << plate1_count << "(" << array[plate1_array[plate1_count]].return_weight() << ")";

                sum_distance -= array[plate2_array[plate2_count]].return_weight();
                sum_distance -= array[plate1_array[plate1_count]].return_weight();
                plate1_count --;
                plate2_count --;
            }
            cout << sum_distance << endl;
        }
    }

};


int main ()
{
    tree tree9;
    tree9.initialise();
    tree9.parser_search();

//    while(1)
//        cin.get();
    return 0;
}
