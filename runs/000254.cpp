#include <iostream>
#include <string.h>


using std::cout;
using std::cin;
using std::endl;

class plate // ����
{
private:
    int weight; // ��� �����
    int link; // ������

public:
    plate() // ����������� �� ���������
    {
        weight = 0;
        link = -1;
    }

    void input(int iweight, int ilink) // ����
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

class tree //������
{
private:
    plate *array; // ������ ������
    int *plate1_array; // ��������������� ������ ��� ������� ����
    int *plate2_array; // ��������������� ������ ��� ������� ����
    int size; // ������
public:
    void initialise () // �������������
    {
        // ������������� �������
        cin >> size; // ���� ���������� ���������
        array = new plate[size]; // ������� ������
        plate1_array = new int[size]; // ������� ������ ��� ������ ����
        plate2_array = new int[size]; // ������� ������ ��� ������ ����


        // ���������� ��������
        int link = 0; // �������� ���������� ��� ������
        int weight = 0; // �������� ���������� ��� ����
        int number = 0; // �������� ���������� ��� ������ ��������
        int count = 0; // �������
        int size_buf = size - 1;

        for (count = 0; count < size_buf; count ++)
        {
            // ���� �������� ����������
            cin >> link;
            cin >> number;
            cin >> weight;

            // ����� � ������
            array[number - 1].input(weight, link - 1);

            // �������
            //array[number - 1].output();
            //cout << " Number: " << number - 1 << endl;
        }

    }

    void parser_search() // ������ � �����
    {
        // ��������� �������� ������
        int str_size = 0; // ������ ������ �������� ��������
        int count = 0; // �������


        // ��������� �����
        int plate1 = 0; // ������ ����
        int plate2 = 0; // ������ ����
        int plate1_count = 0;
        int plate2_count = 0;
        int plate1_distance = 0;
        int plate2_distance = 0;

        // �����
        int sum_distance = 0; // ��������� ���������
        int buffer;


        cin >> str_size; // ���� �������

        // ���� ��������
        for (count = 0; count < str_size; count ++)
        {
            cin >> plate1 >> plate2; // ������ �������� ������� � ������� �����

            buffer = plate1 - 1;
            plate1_distance = 0;
            plate2_distance = 0;

            plate1_count = 0;
            plate2_count = 0;

            // �������� ����� �� ��������������� ������ ��� ������� ����
            do
            {
                // cout << endl << "count: " << plate1_count << "buffer: " << buffer << " ---> " << array[buffer].return_link(); //�������
                plate1_distance += array[buffer].return_weight(); // ����� ���
                plate1_array[plate1_count] = buffer; // ������� �������
                buffer = array[buffer].return_link(); // �������������
                plate1_count ++; // ���������
            }
            while (buffer >= 0);         


            buffer = plate2 - 1; // ����� ��������� ��������
            // �������� ����� �� ��������������� ������ ��� ������� ����
            do
            {
                //cout << endl << "count: " << plate2_count << "buffer: " << buffer << " ---> " << array[buffer].return_link(); //�������
                plate2_distance += array[buffer].return_weight(); // ����� ���
                plate2_array[plate2_count] = buffer; // ������� �������
                buffer = array[buffer].return_link(); // �������������
                plate2_count ++; // ���������
            }
            while (buffer >= 0);

//            // �������
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
