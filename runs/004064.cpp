#include <iostream>
#include <vector>


using namespace std;


class node // Узел
{
private:
    int parent; // Родитель
    int weight; // Вес
    int depth; // Глубина
public:
    node(int in_parent = NULL, int in_weight = 0, int in_depth = 0) // создаём
    {
        parent = in_parent;
        in_weight = weight;
        depth = in_depth;
    }

    void set_node(int in_parent = 0, int in_weight = 0, int in_depth = 0) // создаём
    {
        parent = in_parent;
        weight = in_weight;
        depth = in_depth;
    }

    int get_depth()
    {
        return depth;
    }

    int get_weight()
    {
        return weight;
    }

    int get_parent()
    {
        return parent;
    }

};

class graph // граф
{
private:
    node *array; // указатель на одномерный массив
public:
    graph(int size)
    {
        array = new node[size + 1];
        array[1].set_node(); // задаём первый
    }

    int add_chain(int start, int end, int weight) // добавить цепь
    {
        // Задано - не задано?
        if (array[start].get_parent() != NULL || start == 1)
        {
            array[end].set_node(start, weight, (array[start].get_depth() + 1)); // добавляем
        }
        else
        {
            if (array[start].get_parent() == NULL && (array[end].get_parent() != NULL || end == 1))
            {
                array[start].set_node(end, weight, (array[end].get_depth() + 1)); // добавляем
            }
            else
            {
                return 1; // ошибка
            }
        }
        return 0; // всё хорошо
    }

    int distance(int node1, int node2)
    {
        // узлы
        int eq_node1 = node1;
        int eq_node2 = node2;
        int distance = 0;

        // синхронизируем
        while (array[eq_node1].get_depth() >  array[eq_node2].get_depth()) // если первый глубже второго
        {
            distance += array[eq_node1].get_weight();
            eq_node1 = array[eq_node1].get_parent(); // приравниваем родителю
        }

        while (array[eq_node1].get_depth() <  array[eq_node2].get_depth()) // если второй глубже
        {
            distance += array[eq_node2].get_weight();
            eq_node2 = array[eq_node2].get_parent(); // приравниваем родителю
        }
        // синхронизировали

        // ищем наименьшего общего предка
        while (eq_node1 != eq_node2)
        {
            // считаем расстояние
            distance += array[eq_node1].get_weight();
            distance += array[eq_node2].get_weight();

            // поднимаемся
            eq_node1 = array[eq_node1].get_parent();
            eq_node2 = array[eq_node2].get_parent();
        }

        return distance;
    }

};

struct Trinput
{
    int start;
    int end;
    int weight;

    Trinput(int st, int ed, int wht)
    {
        start = st;
        end = ed;
        weight = wht;
    }
};


int main()
{
    // буферные переменные
    int size = 0;
    int start = 0;
    int end = 0;
    int weight = 0;

    graph *vgraph; // граф
    vector<Trinput> vbuffer; // вектор для висящих цепей
    Trinput *buffer;

    cin >> size; // вводим размер

    vgraph = new graph(size); // инициализируем граф


    for (int i = 1; i < size; ++i) // обрабатываем ввод дерева
    {
        // ввод
        cin >> start;
        cin >> end;
        cin >> weight;

        if(vgraph->add_chain(start, end, weight) == 1) // если цепь графа подвешена
        {
            buffer = new Trinput(start, end, weight); // создаём буффер
            vbuffer.push_back(*buffer); // заносим в вектор
            delete buffer; // очищаем память
        }

    }

    while (vbuffer.empty() != 1)
    {
        for (int i = vbuffer.size() - 1; i >= 0 ; --i)
        {
            if(vgraph->add_chain(vbuffer[i].start, vbuffer[i].end, vbuffer[i].weight) == 0)
            {
                vbuffer.pop_back();
            }
        }
    }

    // обрабатываем ввод вершин для рассчёта
    cin >> size; // размер ввода

    for (int i = 0; i < size; ++i)
    {
        cin >> start;
        cin >> end;
        cout << vgraph->distance(start, end)<<endl;
    }

    return 0;
}
