#include <iostream>
#include <time.h>
#include <stdio.h>


using std::cout;
using std::cin;
using std::endl;

class plate // ����
{
public:
    int weight; // ��� �����
    int link; // ������

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
};

class tree //������
{
private:
    plate *array; // ������ ������
    int *plate1_array; // ��������������� ������ ��� ������� ����
    int *plate2_array; // ��������������� ������ ��� ������� ����
    int *trouble_array;
    int size; // ������
public:
    void initialise () // �������������
    {
        // ������������� �������
        cin >> size; // ���� ���������� ���������
        array = new plate[size]; // ������� ������
        plate1_array = new int[size]; // ������� ������ ��� ������ ����
        plate2_array = new int[size]; // ������� ������ ��� ������ ����
        trouble_array = new int[size * 3];

        // ���������� ��������
        int link = 0; // �������� ���������� ��� ������
        int weight = 0; // �������� ���������� ��� ����
        int num = 0; // �������� ���������� ��� ������ ��������
        int count = 0; // �������
        int problem_count = 0; // ���������� �������
        int buff = 0;

        for (count = 1; count < size; count ++)
        {
            // ����
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


//        // �������
//        cout << endl;
//        for (count = 0; count < problem_count; count ++)  // �������
//        {
//            // ����
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
//        // �����

        while(problem_count > 0)
        {
            buff = problem_count;
            problem_count = 0;
            for (count = 0; count < buff; count += 3)
            {
                // ����
                link = plate1_array[count];
                num = plate1_array[count + 1];
                weight = plate1_array[count + 2];

                if (input(link, num, weight, problem_count) == 1)
                {
                    problem_count += 3;
                }
            }

        }


//        // �������
//        for (count = 0; count < size; count ++)
//        {
//            array[count].output();
//            // �������
//            if (array[array[count].link].link == count)
//                cout << "   ALLLEEEEERT!!!!: "; // ����
//
//            cout <<"-   "  << count;
//        }
//        cout << endl;
//        // ����� �������
        delete trouble_array; // ������� ������
    }

    inline int input(int link, int num, int weight, int count = 0)  // ���� ��������
    {
        int buffer = 0; // ������ �����

        // ���������������� �������
        bool link_empty = false;
        bool num_empty = false;


        if (array[link].link == -1 && link != 0)
            link_empty = true;

        if (array[num].link == -1 && num != 0)
            num_empty = true;

        if(link_empty && !num_empty) // ���� ���� ����, � ��� ��������
        {
            // �����
            buffer = num;
            num = link;
            link = buffer;
        }

        if (link_empty && num_empty) // ���� ��� �������� ����������
        {
            // ������� � ������
            plate1_array[count] = link;
            plate1_array[count + 1] = num;
            plate1_array[count + 2] = weight;

            return 1;
        }

        //cout << "Link: " << link << " Number: " << num << " Weight: " << weight << endl;
        // ����� � ������
        array[num].input(weight, link);
        return 0;
    }

    void parser_search() // ������ � �����
    {
        // ��������� �������� ������
        int str_size = 0; // ������ ������ �������� ��������
        //int count = 0; // �������


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
        for (int count = 0; count < str_size; count ++)
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
                //cout << endl << "count: " << plate1_count << "buffer: " << buffer << " ---> " << array[buffer].link; //�������
                plate1_distance += array[buffer].weight; // ����� ���
                plate1_array[plate1_count] = buffer; // ������� �������
                buffer = array[buffer].link; // �������������
                plate1_count ++; // ���������
            }
            while (buffer >= 0);


            buffer = plate2 - 1; // ����� ��������� ��������
            // �������� ����� �� ��������������� ������ ��� ������� ����
            do
            {
                //cout << endl << "count: " << plate2_count << "buffer: " << buffer << " ---> " << array[buffer].link; //�������
                plate2_distance += array[buffer].weight; // ����� ���
                plate2_array[plate2_count] = buffer; // ������� �������
                buffer = array[buffer].link; // �������������
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

//    // ���� �������
//    clock_t start, end;
//    double elapsed;
//    start = clock();

    tree tree9;
    tree9.initialise();
    tree9.parser_search();


//    // ���� �������
//    end = clock();
//    elapsed=((double)(end-start))/CLOCKS_PER_SEC;
//    cout << endl << "TIME: " << elapsed;// ���� �������
//
//    while(1)
//        cin.get();

    return 0;
}
