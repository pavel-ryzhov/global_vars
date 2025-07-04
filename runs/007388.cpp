#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


  struct slovarj
    {
        char word[64];
        int chastota;
    };
    slovarj *slovar;
    char t9[9][4];



 int slova(int kolvo_slov,int chislo,int length,int zvezd,slovarj *slovar)
{
int j=0,k=0,l=0;
int verno=1;
int chislo1;
struct spisok // включает в себя слово с частотой повторения и номер в словаре
{
    slovarj slovo;
    int nomer_v_massive;
};
slovarj el_slovar;
spisok stroka;
spisok mass[1000];//массив подходящих слов
//------------поиск всех подходящих под шаблон слов----
    for (int i=0;i<kolvo_slov;i++)
    {
    if (strlen(slovar[i].word)==length) // Подходит ли по длине слова
        {
            chislo1=chislo;
             verno=1;
             j=0;
            while ((j<length)&&(verno==1)) //проверяем побуквенно, начиная с хвоста
            {
              if ((t9[chislo1%10][0]>slovar[i].word[length-j-1])||(t9[chislo1%10][3]<slovar[i].word[length-j-1])) verno=0;
              chislo1=(chislo1-(chislo1%10))/10;
              j++;
            }
            if (verno==1)//слово удовлетворяет условиям
            {
                stroka.slovo=slovar[i];
                stroka.nomer_v_massive=i;
               //для удобства делаем отсортированный список
               l=0;
               while ((stroka.slovo.chastota>mass[l].slovo.chastota)&&(l<k)) l++;
               int n=0;
               if (l>0)
               {
                   for( n=0;n<k-l+1;n++)
                   {
                      mass[k-n]=mass[k-n-1];
                   }
               }
                mass[k-n]=stroka;
                k++;
            }
        }
    }
 //  for (i=0;i<k;i++)
 //   {
 //       cout<<mass[i].slovo.word;
 //   }
 //   cout<<endl;
//-------------------------------------------------------
//---Поиск подходящего слова учитывая звездочки----------
 cout<<mass[zvezd].slovo.word;
//-------------------------------------------------------

//----------Увеличиваем частоту и перемещаем данное слово в массиве--
int i=mass[zvezd].nomer_v_massive;
if (slovar[i].chastota<1000) slovar[i].chastota++; // условие, что частота меньше 1000
int koeff=1;

for (j=0;j<length-1;j++) koeff=koeff*10;
i--;
while (((slovar[i].word[0]>t9[chislo/koeff][0])||(slovar[i].word[0]==t9[chislo/koeff][0]))&&(i>-1))
{
    el_slovar=slovar[i];
    slovar[i]=slovar[i+1];
    slovar[i+1]=el_slovar;
    i--;
}
//-------------------------------------------------------------------
  return 0;
}



int main()
{
    ifstream f("file1.txt");
    //char word[64] ;
    int kolvo_slov,cifra,chislo,length,zvezd,cifra1;
    char string[64];
//-------------ввод исходных данных и перевод словаря в массив----
  extern char t9[9][4];
    t9[0][0]='.';t9[0][1]=',';t9[0][2]='?';t9[0][3]='?';
    t9[1][0]='a';t9[1][1]='b';t9[1][2]='c';t9[1][3]='c';
    t9[2][0]='d';t9[2][1]='e';t9[2][2]='f';t9[2][3]='f';
    t9[3][0]='g';t9[3][1]='h';t9[3][2]='i';t9[3][3]='i';
    t9[4][0]='j';t9[4][1]='k';t9[4][2]='l';t9[4][3]='l';
    t9[5][0]='m';t9[5][1]='n';t9[5][2]='o';t9[5][3]='o';
    t9[6][0]='p';t9[6][1]='q';t9[6][2]='r';t9[6][3]='s';
    t9[7][0]='t';t9[7][1]='u';t9[7][2]='v';t9[7][3]='v';
    t9[8][0]='w';t9[8][1]='x';t9[8][2]='y';t9[8][3]='z';

  //  f>>kolvo_slov;
    cin>>kolvo_slov;
    slovarj *slovar= new slovarj[kolvo_slov];
    for (int i=0;i<kolvo_slov;i++)
    {
      cin.getline(string,sizeof(string)); //не прочли символ перевода строки getline на случай доп пробелов
      cin>>slovar[i].word;
      cin>>slovar[i].chastota;
    }
//---------------------------------------------------------------
length=0;
zvezd=0;
cifra1=0;
chislo=0;
cin.getline(string,sizeof(string)); //не прочли символ перевода строки getline на случай доп пробелов
while (cifra!=10)
    {
        cifra = cin.get();

        if ((cifra<58)&&(cifra>49)) //цифра 2-9
        {
            length++;
            chislo=chislo*10+cifra-48-1; //-1 так как в массиве все сдвинулось на 1
            zvezd=0;
            cifra1=0;
        }
        if (cifra==49) //цифра 1
        {
            if (chislo!=0) slova(kolvo_slov,chislo,length,zvezd,slovar);
            cifra1=1;
            zvezd=0;
            length=0;
            chislo=0;
        }
        if (cifra==32) //пробел
        {
            if (cifra1!=1) slova(kolvo_slov,chislo,length,zvezd,slovar);
            if (cifra1==1) cout<< t9[0][zvezd];
            cout<<" ";
            cifra1=0;
            zvezd=0;
            length=0;
            chislo=0;
        }
        if (cifra==42) //звездочка
        {
            zvezd++;
        }

    }
    if (cifra1!=1) slova(kolvo_slov,chislo,length,zvezd,slovar);
    if (cifra1==1) cout<< t9[0][zvezd];
}

