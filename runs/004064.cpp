#include <iostream>
#include <vector>


using namespace std;


class node // ����
{
private:
    int parent; // ��������
    int weight; // ���
    int depth; // �������
public:
    node(int in_parent = NULL, int in_weight = 0, int in_depth = 0) // ������
    {
        parent = in_parent;
        in_weight = weight;
        depth = in_depth;
    }

    void set_node(int in_parent = 0, int in_weight = 0, int in_depth = 0) // ������
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

class graph // ����
{
private:
    node *array; // ��������� �� ���������� ������
public:
    graph(int size)
    {
        array = new node[size + 1];
        array[1].set_node(); // ����� ������
    }

    int add_chain(int start, int end, int weight) // �������� ����
    {
        // ������ - �� ������?
        if (array[start].get_parent() != NULL || start == 1)
        {
            array[end].set_node(start, weight, (array[start].get_depth() + 1)); // ���������
        }
        else
        {
            if (array[start].get_parent() == NULL && (array[end].get_parent() != NULL || end == 1))
            {
                array[start].set_node(end, weight, (array[end].get_depth() + 1)); // ���������
            }
            else
            {
                return 1; // ������
            }
        }
        return 0; // �� ������
    }

    int distance(int node1, int node2)
    {
        // ����
        int eq_node1 = node1;
        int eq_node2 = node2;
        int distance = 0;

        // ��������������
        while (array[eq_node1].get_depth() >  array[eq_node2].get_depth()) // ���� ������ ������ �������
        {
            distance += array[eq_node1].get_weight();
            eq_node1 = array[eq_node1].get_parent(); // ������������ ��������
        }

        while (array[eq_node1].get_depth() <  array[eq_node2].get_depth()) // ���� ������ ������
        {
            distance += array[eq_node2].get_weight();
            eq_node2 = array[eq_node2].get_parent(); // ������������ ��������
        }
        // ����������������

        // ���� ����������� ������ ������
        while (eq_node1 != eq_node2)
        {
            // ������� ����������
            distance += array[eq_node1].get_weight();
            distance += array[eq_node2].get_weight();

            // �����������
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
    // �������� ����������
    int size = 0;
    int start = 0;
    int end = 0;
    int weight = 0;

    graph *vgraph; // ����
    vector<Trinput> vbuffer; // ������ ��� ������� �����
    Trinput *buffer;

    cin >> size; // ������ ������

    vgraph = new graph(size); // �������������� ����


    for (int i = 1; i < size; ++i) // ������������ ���� ������
    {
        // ����
        cin >> start;
        cin >> end;
        cin >> weight;

        if(vgraph->add_chain(start, end, weight) == 1) // ���� ���� ����� ���������
        {
            buffer = new Trinput(start, end, weight); // ������ ������
            vbuffer.push_back(*buffer); // ������� � ������
            delete buffer; // ������� ������
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

    // ������������ ���� ������ ��� ��������
    cin >> size; // ������ �����

    for (int i = 0; i < size; ++i)
    {
        cin >> start;
        cin >> end;
        cout << vgraph->distance(start, end)<<endl;
    }

    return 0;
}
