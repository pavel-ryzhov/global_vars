#include <iostream>
#include <algorithm>
#include <string.h>
#include <time.h>
#include <vector>


//using std::cout;
//using std::cin;
//using std::endl;
using namespace std;

class dict_word // ����� � �������
{
private:
    char word[21]; // �����
    int length; // �����

public:
    int rate; // �������
    int magic; // ������� "���������" ��������
    void input()//char itext[], int ilength, int irate)
    {
        magic = 0; // ������� �������
        cin.get(); // ������� lf
        cin.get(word, 21, ' '); // ���� ����� �� �������
        length = strlen(word); // ��������� ����� �����

        cin >> rate; // ���� �������
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

bool operator<(const dict_word & word1, const dict_word & word2) // ���������
{
    return (word1.rate > word2.rate || (word1.rate == word2.rate && word1.magic > word2.magic));
    //return (word1.rate > word2.rate);
}


class plate // ����
{
public:
    vector <dict_word> vect; // ������
    bool empty; // ������
    bool sort;
    plate *array;

    plate()
    {
        empty = true; // ������
        sort = false; // �� ���������������
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

    inline void sorting(int end = 0) // ����������
    {
        if (end == 0)
            stable_sort (vect.begin(), vect.end()); // ����������� ��
        else
            stable_sort(vect.begin(), vect.begin() + end); // ����������� ������������
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

class dict // �������
{
private:
    plate *first;
    int size; // ������ �������
    int buttons[26]; // ��������� ASC-����� ��� ������
    char characters[3]; // ����� ����������

public:
   void initialise () // ������������� �������
   {
       first = new plate; // ������� ������ ��� ������ �������
       first->initialise(); // ������������ �������
       cin >> size; // ���� �������
       
       plate *buff_plate = first; // �������� ����
       dict_word buffer;
//       int inner_count = 0;

       int count = 0;

       // ���������� ������� � �������� ������
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
       // �����

       for (count = 0; count < size; ++ count)
       {
           buffer.input(); // ���� ����� � ����
           buff_plate = first;
           for (int iter = 0; iter < buffer.return_leigth(); ++ iter) // ������ �� ������
           {
              // cout << endl << iter <<" ("<< buffer.asc_litera(iter) - 97 << " ---> (" << buttons[buffer.asc_litera(iter) - 97] << ")"; // �������
               if(buff_plate->empty) // ���� ���� ������
               {
                   buff_plate->initialise(); // ��������������
               }

               buff_plate = &buff_plate->array[buttons[buffer.asc_litera(iter) - 97]]; // ���������
           }
           buff_plate->push(buffer); // ���������
       }


       // ������������� ������ ����������
       characters[0] = '.';
       characters[1] = ',';
       characters[2] = '?';
       // ����� ������������� ������ ����������
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
           leigth = count; // ���������� ����� �����

           switch(buf)
           {
           case 42: // ������
               {
                   count = 1;
                   while(cin.peek() == 42)
                   {
                       buf = cin.get();
                           count ++;
                   }

                   search(string, leigth, count);// ����� ������� ������
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

   inline void search(int string[], int leigth, int stars = 0) // �����
   {
       static int index = 0; // �����
       index ++; // ���������

       plate *buff_plate = first; // �������� ���������
       int count = 0;

       for (count = 0; count < leigth; ++ count)
       {
           buff_plate = &buff_plate->array[string[count]];
       }
       if (!buff_plate->sort)
           buff_plate->sorting();

       buff_plate->vect[stars].incr(index); // ���������� ����� � �������
       buff_plate->output(stars); // �����

       if (stars != 0)
           buff_plate->sorting(stars);
   }
};


int main()
{
//    // ���� �������
//    clock_t start, end;
//    double elapsed;
//    start = clock();

    dict dict1;
    dict1.initialise();
    //dict1.input();
    dict1.parser();

//    // ���� �������
//    end = clock();
//    elapsed=((double)(end-start))/CLOCKS_PER_SEC;
//    cout << endl << "TIME: " << elapsed;// ���� �������
//
//    while(1)
//    {
//        cin.get();
//    }
    return 0;
}
