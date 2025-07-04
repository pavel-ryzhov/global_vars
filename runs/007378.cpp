#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int chisla[3];

//-----функция для расчитвания из какой вершины можно в данную вершину попасть, уровень вершины относительно корня и расстояние между соседними вершинами
//
int urov(int nomer, int kolvo,int s4et4ik, int **uroven,int **mass) //nomer issleduemoj verwini
{
	if (s4et4ik==0)
	{
	    uroven[nomer][0]=0;//вводим все для корня дерева
	    uroven[nomer][1]=0;
	    uroven[nomer][2]=0;
	}
    for (int i=0;i<kolvo;i++)
    {
        for (int j=0;j<2;j++)
        {
            if (mass[i][j]-1==nomer)
            {
              if ((j==1)&&(uroven[mass[i][0]-1][0]==-1))
                {
                    uroven[mass[i][0]-1][0]=nomer;     //из какой вершины в данную попадаем
                    uroven[mass[i][0]-1][2]=s4et4ik+1; //уровень вершины относительно корня
                    uroven[mass[i][0]-1][1]=mass[i][2];//расстояние между данными вершинами
                    urov(mass[i][0]-1,kolvo, s4et4ik+1, uroven, mass);
                }
                if ((j==0)&&(uroven[mass[i][1]-1][0]==-1))
                {
                    uroven[mass[i][1]-1][0]=nomer;     //из какой вершины в данную попадаем
                    uroven[mass[i][1]-1][1]=mass[i][2];//расстояние между данными вершинами
                    uroven[mass[i][1]-1][2]=s4et4ik+1; //уровень вершины относительно корня
                    urov(mass[i][1]-1, kolvo, s4et4ik+1, uroven, mass);
                }
            }
        }
    }
    return 0;
}

//----функция для поиска оптимального пути между двумя вершинами--------------------------
/*сначала сравниваем уровни и исходных вершин, далее поднимаемся к корню от вершины которая
расположена ниже(уровень больше), далее одновременно поднимаемся к корню от двух вершин
пока не пути не пересекутся (все время поднимания мы расчитываем пройденный путь)
*/
int poisk(int **uroven,int ver1,int ver2, int **dlja_poiska)
{
int dlina=0;
int na4_ver1=ver1,na4_ver2=ver2;
    if (uroven[ver1][2]>uroven[ver2][2])
    {
        while (uroven[ver1][2]!=uroven[ver2][2])
        {
            dlina=dlina+uroven[ver1][1];//прибавляем пройденный путь
            ver1=uroven[ver1][0];// поднимаемся на уровень выше
            if ((ver1>na4_ver1)&&(dlja_poiska[ver1][na4_ver1]==-1)) dlja_poiska[ver1][na4_ver1]=dlina;
            if ((!(ver1>na4_ver1))&&(dlja_poiska[na4_ver1][ver1]==-1)) dlja_poiska[na4_ver1][ver1]=dlina;
            if ((ver1>ver2)&&(dlja_poiska[ver1][ver2]!=-1)) return dlja_poiska[ver1][ver2]+dlina ; //случай если этот путь уже просчитан
            if ((!(ver1>ver2))&&(dlja_poiska[ver2][ver1]!=-1)) return dlja_poiska[ver2][ver1]+dlina ;
        }
    }
    if (uroven[ver1][2]<uroven[ver2][2])
    {
         while (uroven[ver1][2]!=uroven[ver2][2])
        {
            dlina=dlina+uroven[ver2][1];//прибавляем пройденный путь
            ver2=uroven[ver2][0];// поднимаемся на уровень выше
            if ((ver2>na4_ver2)&&(dlja_poiska[ver2][na4_ver2]==-1)) dlja_poiska[ver2][na4_ver2]=dlina;
            if ((!(ver2>na4_ver2))&&(dlja_poiska[na4_ver2][ver2]==-1)) dlja_poiska[na4_ver2][ver2]=dlina;
            if ((ver1>ver2)&&(dlja_poiska[ver1][ver2]!=-1)) return dlja_poiska[ver1][ver2]+dlina ; //случай если этот путь уже просчитан
            if ((!(ver1>ver2))&&(dlja_poiska[ver2][ver1]!=-1)) return dlja_poiska[ver2][ver1]+dlina ;
        }
    }
       while (ver1!=ver2)
    {
        if ((ver1>ver2)&&(dlja_poiska[ver1][ver2]!=-1)) return dlja_poiska[ver1][ver2]+dlina ; //случай если этот путь уже просчитан
        if ((!(ver1>ver2))&&(dlja_poiska[ver2][ver1]!=-1)) return dlja_poiska[ver2][ver1]+dlina ;
        dlina=dlina+uroven[ver1][1];//прибавляем пройденный путь
        dlina=dlina+uroven[ver2][1];//прибавляем пройденный путь
        ver1=uroven[ver1][0];// поднимаемся на уровень выше
        ver2=uroven[ver2][0];// поднимаемся на уровень выше
    }
    return dlina;
}
//----------------------------------------------------------------------------------------

 int stroka(int kol_chisel)
 {
  extern int chisla[3];
  char string[128];
   int o=0,chislo=0,povtor=-1;
   while (povtor!=0) //проверка корректности ввода
  {
      for (int i=0;i<3;i++) chisla[i]=0;
       povtor=-1;
    //cout << "vvedute dannie" << endl;
    cin.getline(string, sizeof(string));
    strcat(string,"  ");
    chislo=-1;
        for (int k=0;k<strlen(string)-1;k++)
        {
            if ((string[k]>'/')&&(string[k]<':'))
            {
                if (chislo==-1) chislo=0;
                chislo=chislo*10+int(string[k]-48);
            }
            if (!((string[k]>'/')&&(string[k]<':')))
            {
                if (chislo!=-1)
                {
                chisla[o]=chislo;
                chislo=-1;
                o++;
                }
            }
        }
        for (int k=0;k<kol_chisel;k++)
        {
           // cout<<chisla[k];
            if ((chisla[k]<0)||(chisla[k]>40000)) { povtor=1; cout<<"zanovo";}
        }
        if (povtor==-1) povtor=0;
   }
    return povtor;
 }

int main()
{
int kolvo=0,max,maxnom,kolvopoisk;

//ifstream f("file.txt"); // файл из которого происходит чтение
//f >> kolvo;
stroka(1);
    kolvo=chisla[0];
kolvo--; //перевод в количество строк
// создание массива по исходным данным и поиск вершины с максимальным количеством ребер
int *podc4et = new int[kolvo+1];
for (int j=0;j<kolvo+1;j++)
{
    podc4et[j]=0;
}

int **mass = new int*[kolvo];
for (int i = 0; i < kolvo; i++) mass[i] = new int[3];
for ( int i=0;i<kolvo;i++)
{

stroka(3); //передаем параметр 3 так как в строке 3 числа

   for (int j=0;j<3;j++)
   {
       mass[i][j]=chisla[j];
   }
  // cout<<mass[i][0]<<mass[i][1]<<mass[i][2];
    for (int j=0;j<2;j++)
    {
            if ((i==0) && (j==0))
            {
                max=1;
                maxnom=mass[i][j]-1; //перевод номеров вершин (считаем не от 1 а от 0)
            }
            podc4et[mass[i][j]-1]++;
            if (podc4et[mass[i][j]-1]>max)
            {
                max=podc4et[mass[i][j]-1];
                maxnom=mass[i][j]-1;
            }
    }
}

//--------------------------------------------------
//cout<<maxnom<<"-nomer "<<max <<" -kolvo" ;
//--------вводим массив связывающий номер вершины, из какой вершины мы в нее попадаем, длину пути между вершинами и уровень вершины
//cout<<mass[0][0]<<" "<<mass[0][1]<<" "<<mass[1][0]<<" "<<mass[1][1]<<mass[1][2]<<endl;
int *uroven = new int[kolvo+1];
for (int i=0;i<kolvo+1;i++)
{
    uroven[i]=-1;
}

int **urovenj = new int*[kolvo+1];
for (int i = 0; i < kolvo+1; i++) urovenj[i] = new int[3];
for (int i=0;i<kolvo+1;i++)
{
    for (int j=0;j<3;j++) urovenj[i][j]=-1;
}

urov(maxnom,kolvo, 0, urovenj, mass);

//-------------------------------------------------------------------------------------------------------------------
//--------------занимаемся поиском пути----------------------------------------
//f>>kolvopoisk;
stroka(1);
kolvopoisk=chisla[0];
int result;
int otvet[50000]; //массив для записи полученного результата
int **dlja_poiska=new int*[kolvo+1];
for (int i=0;i<kolvo+1;i++)dlja_poiska[i]=new int [kolvo+1];
for (int i=0;i<kolvo+1;i++)
{
    for (int j=0;j<kolvo+1;j++)
    {if (i!=j) dlja_poiska[i][j]=-1; if (i==j) dlja_poiska[i][j]=0;}
}
for (int i=0;i<kolvopoisk;i++)
{
    result=-1;
    stroka(2);
    if (dlja_poiska[chisla[0]-1][chisla[1]-1]!=-1) result=dlja_poiska[chisla[0]-1][chisla[1]-1];
    if (dlja_poiska[chisla[1]-1][chisla[0]-1]!=-1) result=dlja_poiska[chisla[1]-1][chisla[0]-1];
    if ((dlja_poiska[chisla[0]-1][chisla[1]-1]==-1)&&(dlja_poiska[chisla[1]-1][chisla[0]-1]==-1)) //для не повторения просчета уже просчитанного
    {
        result=poisk(urovenj,chisla[0]-1,chisla[1]-1,dlja_poiska);
        if (chisla[0]>chisla[1]) dlja_poiska[chisla[0]-1][chisla[1]-1]=result;
        if (!(chisla[0]>chisla[1])) dlja_poiska[chisla[1]-1][chisla[0]-1]=result;
    }
    otvet[i]=result;
//for (int i=0;i<kolvo+1;i++)
//{
//    for (int j=0;j<kolvo+1;j++)
//    {cout<<dlja_poiska[i][j];}
//    cout<<endl;
//}
}
//-----------------------------------------------------------------------------
//------------Вывод ответа на экран---------------------------------------------
for (int i=0;i<kolvopoisk;i++)
cout<<otvet[i]<<endl;
//--------------------------------------------------------------------------------
}

