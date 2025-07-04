#include <iostream>
#include <time.h>
#include <stdio.h>


using std::cout;
using std::cin;
using std::endl;

class plate // лист
{
public:
    int weight; // вес связи
    int link; // ссылка

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
};

class tree //дерево
{
private:
    plate *array; // массив дерева
    int *plate1_array; // вспомогательный массив для первого узла
    int *plate2_array; // вспомогательный массив для второго узла
    int *trouble_array;
    int size; // размер
public:
    void initialise () // инициализация
    {
        // инициализация массива
        cin >> size; // ввод количества элементов
        array = new plate[size]; // отводим память
        plate1_array = new int[size]; // отводим память под первый узел
        plate2_array = new int[size]; // отводим память под второй узел
        trouble_array = new int[size * 3];

        // заполнение значений
        int link = 0; // буферная переменная для ссылок
        int weight = 0; // буферная переменная для веса
        int num = 0; // буферная переменная для номера элемента
        int count = 0; // счётчик
        int problem_count = 0; // проблемный счётчик
        int buff = 0;

        for (count = 1; count < size; count ++)
        {
            // ввод
            cin >> link;
            cin >> num;
            cin >> weight;

            link -= 1;
            num -= 1;

            if (input(link, num, weight, problem_count) == 1)
            {
                problem_count += 3;
            }
        }


//        // отладка
//        cout << endl;
//        for (count = 0; count < problem_count; count ++)  // отладка
//        {
//            // ввод
//            link = plate1_array[count];
//            num = plate1_array[count + 1];
//            weight = plate1_array[count + 2];
//
//            if (input(link, num, weight, problem_count) == 1)
//            {
//                problem_count += 3;
//            }
//        }
//        cout << endl;
//        // конец

        while(problem_count > 0)
        {
            buff = problem_count;
            problem_count = 0;
            for (count = 0; count < buff; count += 3)
            {
                // ввод
                link = plate1_array[count];
                num = plate1_array[count + 1];
                weight = plate1_array[count + 2];

                if (input(link, num, weight, problem_count) == 1)
                {
                    problem_count += 3;
                }
            }

        }


//        // отладка
//        for (count = 0; count < size; count ++)
//        {
//            array[count].output();
//            // отладка
//            if (array[array[count].link].link == count)
//                cout << "   ALLLEEEEERT!!!!: "; // цикл
//
//            cout <<"-   "  << count;
//        }
//        cout << endl;
//        // конец отладки
        delete trouble_array; // очистка памяти
    }

    inline int input(int link, int num, int weight, int count = 0)  // ввод элемента
    {
        int buffer = 0; // просто буфер

        // предпросчитанные условия
        bool link_empty = false;
        bool num_empty = false;


        if (array[link].link == -1 && link != 0)
            link_empty = true;

        if (array[num].link == -1 && num != 0)
            num_empty = true;

        if(link_empty && !num_empty) // если линк пуст, а нум определён
        {
            // обмен
            buffer = num;
            num = link;
            link = buffer;
        }

        if (link_empty && num_empty) // если оба элемента неизвестны
        {
            // заносим в массив
            plate1_array[count] = link;
            plate1_array[count + 1] = num;
            plate1_array[count + 2] = weight;

            return 1;
        }

        //cout << "Link: " << link << " Number: " << num << " Weight: " << weight << endl;
        // вброс в листья
        array[num].input(weight, link);
        return 0;
    }

    void parser_search() // парсер и поиск
    {
        // параметры вводимой строки
        int str_size = 0; // размер строки вводимых значений
        //int count = 0; // счётчик


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
        for (int count = 0; count < str_size; count ++)
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
                //cout << endl << "count: " << plate1_count << "buffer: " << buffer << " ---> " << array[buffer].link; //отладка
                plate1_distance += array[buffer].weight; // копим вес
                plate1_array[plate1_count] = buffer; // заносим элемент
                buffer = array[buffer].link; // переключаемся
                plate1_count ++; // инкримент
            }
            while (buffer >= 0);


            buffer = plate2 - 1; // кладём начальное значение
            // внесение ветки во вспомогательный массив для второго узла
            do
            {
                //cout << endl << "count: " << plate2_count << "buffer: " << buffer << " ---> " << array[buffer].link; //отладка
                plate2_distance += array[buffer].weight; // копим вес
                plate2_array[plate2_count] = buffer; // заносим элемент
                buffer = array[buffer].link; // переключаемся
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
//                while(1)
//                    cin.get();


            sum_distance = plate1_distance + plate2_distance;
           // cout << endl<< sum_distance << endl;
            plate2_count --;
            plate1_count --;

            while((plate2_array[plate2_count] == plate1_array[plate1_count]) && plate1_count >= 0 && plate2_count >= 0)
            {
                //cout << endl << plate1_count << "(" << array[plate1_array[plate1_count]].weight << ")";

                sum_distance -= array[plate2_array[plate2_count]].weight;
                sum_distance -= array[plate1_array[plate1_count]].weight;
                plate1_count --;
                plate2_count --;
            }
            cout << sum_distance << endl;
        }
    }

};


int main ()
{

//    // тест времени
//    clock_t start, end;
//    double elapsed;
//    start = clock();

    tree tree9;
    tree9.initialise();
    tree9.parser_search();


//    // тест времени
//    end = clock();
//    elapsed=((double)(end-start))/CLOCKS_PER_SEC;
//    cout << endl << "TIME: " << elapsed;// тест времени
//
//    while(1)
//        cin.get();

    return 0;
}
