#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int dlina;
int visota;
int mass[100]; //хранятся числа используемые в массиве для нариcовки числа и колво такого цвета
//kus(int **chastj,int i,int perv,int vtor,int kusok);
//chislo(char **risunok,int **chastj,int i, int perv, int vtor);
//chisloser(char **risunok,int **chastj,int i, int perv, int vtor,int cvet2);
//net_soedin(int **chastj);
//soedin(int **chastj,int cvet1,int cvet2);

//-----процедура возвращает все, если не удалось объединить-------
int net_soedin(int **chastj)
{
  for (int i=0;i<visota;i++)
  {
      for (int j=0;j<dlina;j++)
      {
          if (chastj[i][j]==102) chastj[i][j]=100;
      }
  }
  return 0;
}
//------------------------------------------------------------------

//------процедура закрашивает одним цветои то что удалось соединить------
int soedin(int **chastj,int cvet1,int cvet2)
{
  for (int i=0;i<visota;i++)
  {
      for (int j=0;j<dlina;j++)
      {
          if ((chastj[i][j]==cvet2)||(chastj[i][j]==102)) chastj[i][j]=cvet1;
      }
  }
  return 0;
}
//----------------------------------------------------------------------

//-----процедура вводит в массив цифры для различнения кусков разных цифр--
int kus(int **chastj,int i,int perv,int vtor,int kusok)
{
        //--- Смотрим серый для объединения кусков----
    if (kusok==102)
    {
       for (int j=perv;j<vtor+1;j++) chastj[i][j]=kusok;
        return 0;
    }
    //---------------------------------------------
    int cvet=chastj[i][perv];
    if (chastj[i][perv]==kusok) return 0;
     if (chastj[i][perv]!=0)
     {
         mass[kusok]=mass[kusok]+mass[cvet];
         mass[cvet]=0;
         for (int n=0;n<visota;n++)
           {
               for (int m=0;m<dlina;m++)
               {
                 if (chastj[n][m]==cvet) chastj[n][m]=kusok;
               }
           }
           return 0;
     }
    for (int j=perv;j<vtor+1;j++)
    {
        if (chastj[i][j]==0)
        {chastj[i][j]=kusok; //если еще не проходили это место
        mass[kusok]++;
        }
    }
    return 0;
}
//--------------------------------------------------------------------------

//--процедура пытающаяся объединить 2 куска одной цифры (рассматриваем светло серый)--
int chisloser(char **risunok,int **chastj,int i, int perv, int vtor,int cvet2)
{
    // risunok-массив-рисунок, chasti -массив где раскрашено по цифрам, i-номер строки, perv-начало блока vtor-конец блока,цвет 2 до которого идем
    int q=vtor;
    int istina=0,perv2,vtor2;
    int polu4ilosj=0;
    //int a;
    int nado;
    if (chastj[i+1][vtor+1]==cvet2) return 1; //т.е. есть путь по серому
    if (risunok[i+1][vtor+1]=='%') // идет распространения в право относительно прошлого ряда
   {
       istina=1;
       while ((istina==1)&&(q<dlina))
       {
           q++;
           if (risunok[i+1][q]=='%') istina=1;
           if (risunok[i+1][q]!='%') istina=0;
       }
    vtor2=q-1; // заключительный серый в полоске
    q=vtor;
    istina=1;
    while ((istina==1)&&(q>0))
       {
           q--;
           if (risunok[i+1][q]=='%') istina=1;
           if (risunok[i+1][q]!='%') istina=0;
       }
       if (chastj[i+1][q]==cvet2) return 1;

       perv2=q+1;// первый черный в правом куске
  //  cout<<perv2<<" "<<vtor2<<" ; "<<endl;
  //     for (int p=0;p<visota;p++)
  //  {
  //      for (int o=0;o<dlina;o++) cout<<chastj[p][o];
  //      cout<<endl;
  // }
 //  cin>>a;
     if (chastj[i+1][perv2]==100) nado=0;
     kus(chastj,i+1,perv2,vtor2,102);
     if (nado==0)
     {polu4ilosj=chisloser(risunok,chastj,i+1,perv2,vtor2,cvet2);
     if (polu4ilosj=1) return 1;
     }
   }

   istina=0;
   if (chastj[i+1][q]==cvet2) return 1;
    while ((istina==1)||!(q<perv-1))
    {
        //cout<<((risunok[i+1][q]=='#')||(risunok[i+1][q]=='@'))<<" i "<<q<<endl;
        if (risunok[i+1][q]=='%')
        {
            if (istina==0)
            {
                vtor2=q;
            }
            istina=1;
        }
        if (risunok[i+1][q]!='%')
        {
            if (istina==1)
            {
                if (chastj[i+1][q]==cvet2) return 1;
                perv2=q+1;
  //          cout<<"!!!"<<perv2<<" "<<vtor2<<endl;
 //   for (int p=0;p<visota;p++)
 //   {
 //       for (int o=0;o<dlina;o++) cout<<chastj[p][o];
 //       cout<<endl;
 //  }
   // cin>>a;
                if (chastj[i+1][perv2]==100) nado=0;
                kus(chastj,i+1,perv2,vtor2,102);
                if (nado==0) {
                polu4ilosj=chisloser (risunok,chastj,i+1,perv2,vtor2,cvet2);
                if (polu4ilosj=1) return 1;
                }
            }
            istina=0;
        }
        q--;
    }
    return 0;
}
//------------------------------------------------------------------
//--процедура находящая облать в которой расположена отдельная цифра-- (светло серый не рассматриваем(буквы сольются))
int chislo(char **risunok,int **chastj,int i, int perv, int vtor)
{
    // risunok-массив-рисунок, dlina-длина строки, i-номер строки, k-начало блока l-конец блока
    int q=vtor;
    int istina=0,perv2,vtor2;
    //int a;
    int nado;

   if ((risunok[i+1][vtor+1]=='#')||(risunok[i+1][vtor+1]=='@')) // идет распространения в право относительно прошлого ряда
   {
       istina=1;
       while ((istina==1)&&(q<dlina))
       {
           q++;
           if ((risunok[i+1][q]=='#')||(risunok[i+1][q]=='@')) istina=1;
           if ((risunok[i+1][q]!='#')&&(risunok[i+1][q]!='@')) istina=0;
       }
    vtor2=q-1; // заключительный черный(темно-серый) в полоске
    q=vtor+1; // на случай сдвига вправо
    istina=1;
    while ((istina==1)&&(q>0))
       {
           q--;
           if ((risunok[i+1][q]=='#')||(risunok[i+1][q]=='@')) istina=1;
           if ((risunok[i+1][q]!='#')&&(risunok[i+1][q]!='@')) istina=0;
       }

       perv2=q+1;// первый черный в правом куске
  //  cout<<perv2<<" "<<vtor2<<" ; "<<chastj[i+1][perv2]<<endl;
  //     for (int p=0;p<visota;p++)
  //  {
  //      for (int o=0;o<dlina;o++) cout<<chastj[p][o];
  //      cout<<endl;
  // }
 //  cin>>a;

     nado=chastj[i+1][perv2];
     kus(chastj,i+1,perv2,vtor2,chastj[i][perv]);
     if (nado==0) chislo(risunok,chastj,i+1,perv2,vtor2);
   }

   istina=0;
    while ((istina==1)||!(q<perv-1)) //поправила на -1 чтобы один шаг влево то же смотрел
    {
        //cout<<((risunok[i+1][q]=='#')||(risunok[i+1][q]=='@'))<<" i "<<q<<endl;
        if ((risunok[i+1][q]=='#')||(risunok[i+1][q]=='@'))
        {
            if (istina==0)
            {
                vtor2=q;
            }
            istina=1;
        }
        if ((risunok[i+1][q]!='#')&(risunok[i+1][q]!='@'))
        {
            if (istina==1)
            {
                perv2=q+1;
//              cout<<"!!!"<<perv2<<" "<<vtor2<<" ; "<<chastj[i+1][perv2]<<endl;
 //   for (int p=0;p<visota;p++)
 //   {
 //       for (int o=0;o<dlina;o++) cout<<chastj[p][o];
 //       cout<<endl;
 //  }
   // cin>>a;
                nado=chastj[i+1][perv2];
                kus(chastj,i+1,perv2,vtor2,chastj[i][perv]);
                if (nado==0) chislo (risunok,chastj,i+1,perv2,vtor2);
            }
            istina=0;
        }
        q--;
    }
    return 0;
}
//------------------------------------------------------------------




int main()
{
    int otvet_got[3][2];
    extern int mass[100];
    extern int dlina;

    extern int visota;
    int i=0,estj=0;//dlina
    int kusok;
    int vsego=0;
    char string[500] ;
    int konec=0;
    int na4alo=0;
   // ifstream f("001"); // file iz kotorogo 4itaem
 //if (f.fail())
 //{
 //   cout << "Ошибка открытия " << endl;
 //   exit(1);
 //}
 for (i=0;i<100;i++) mass[i]=0;
 //-------переписываем рисунок из файла в массив------
    // считаем размер рисунка
    char **risunok= new char*[100];
    cin.getline(string, sizeof(string)) ;
    dlina=strlen(string);
    //int
    visota=1;
    //первая строка пустая поэтому можем ее не записывать
   // while (!f.eof())
   // {
   //     f.getline(string, sizeof(string)) ;
   //     visota++;
   //}
   i=0;
   //считываю до 4 пустой строки
   while (konec!=3)
   {
       cin.getline(string, sizeof(string)) ;

       risunok[i]=new char[dlina];
       estj=0;
       for (int j=0;j<dlina;j++)
       {
           risunok[i][j]=string[j];
          // cout<<string[j];
           if ((string[j]=='%')||(string[j]=='#')||(string[j]=='@')) na4alo=1;
           if ((string[j]=='%')||(string[j]=='#')||(string[j]=='@')) estj=1;
       }
       if ((na4alo==1)&&(estj==0)) konec=konec+1;
          //  cout<<konec<<na4alo<<endl;
       i++;
   }
   estj=0;
   visota=i;
   int j=0;
   //char **risunok= new char*[visota];
    //char *string1=new char[dlina+1];
    //for (int i=0;i<visota;i++) risunok[i]=new char[dlina+1];
    //f.close();
    //ifstream h("001"); // file iz kotorogo 4itaem
    //int j=0;
    //while (!h.eof())
    //{
    //    h.getline(string, sizeof(string)) ;
    //    for (int i=0;i<dlina+1;i++)
    //    {
    //        risunok[j][i]=string[i];
    //    }
    //    j=j+1;;
    //}
  //  for (int i=0;i<visota-1;i++) cout<<risunok[i]<< dlina<<endl;
//-------------------------------------------------------------------------
//---------------выделяем отдельные цифры----------------------------------
    int **chastj= new int*[visota]; // для выделения отдельных цифр
    kusok=0;
    for (int i=0;i<visota;i++) chastj[i]=new int[dlina];
    for (int i=0;i<visota;i++)
    {
        for (j=0;j<dlina;j++) chastj[i][j]=0;
    }
 //   for (int i=0;i<visota;i++)
 //   {
 //       for (int j=0;j<dlina;j++) cout<<chastj[i][j];
 //       cout<<endl;
 //   }
 //   cin>>j;
    int istina=0;
    int perv;
    int vtor;
//int a;

    for (int i=0;i<visota;i++)
    {
        j=0;
        istina=0;
        while (j<dlina)
        {
           if ((risunok[i][j]=='#')||(risunok[i][j]=='@'))
           {
               if(istina==0) perv=j;
               istina=1;
           }
           if ((risunok[i][j]!='#')&&(risunok[i][j]!='@'))
           {
               if(istina==1)
               {
                    vtor=j-1;
                  //  cout<<perv<<" "<<vtor<< "!"<<endl;
 //     for (int p=0;p<visota;p++)
  //  {
  //      for (int o=0;o<dlina;o++) cout<<chastj[p][o];
  //      cout<<endl;
  // }
//cin>>a;
                    if (chastj[i][perv]==0)
                    {
                        kusok++;

                        kus(chastj,i,perv,vtor,kusok);
                        chislo(risunok,chastj,i,perv,vtor);
    //for (int p=0;p<visota;p++)
    //{
    //    for (int o=0;o<dlina;o++) cout<<chastj[p][o];
    //    cout<<endl;
   //}
   // cin>>a;
                    }
               }
               istina=0;
           }
           j++;
        }

    }
    //--- изображение на экран---
   //     for (int p=0;p<visota;p++)
   // {
   //     for (int o=0;o<dlina;o++) cout<<chastj[p][o];
   //     cout<<endl;
   //}
   // cin>>a;
//--------------------------------------------------------------------------
//int mass1[10][2];

//==============ДОРАБОТКА ИЗОБРАЖЕНИЯ=======================================
 for (int l=0;l<100;l++) if (mass[l]<10) mass[l]=0; //убираем все точки
 //------------создаем массив всех используемых чисел------------------------------------------
 //----число, начальная широта, конечная широта, начальная высота, конечная высота------------
  int s4et=0;
  for (int l=0;l<100;l++) if (mass[l]!=0) s4et++;
  int **massnew=new int*[s4et];
  for (int p=0;p<s4et;p++) massnew[p]= new int[5];//число,нач широта, конечная, начальная высота, конечная высота
  s4et=0;
  for (int l=0;l<100;l++) if (mass[l]!=0)
  {
      massnew[s4et][0]=l;
      massnew[s4et][1]=dlina;
      massnew[s4et][2]=0;
      massnew[s4et][3]=visota;
      massnew[s4et][4]=0;
      s4et++;
  }
     for (int p=0;p<visota;p++)
    {
        for (int o=0;o<dlina;o++)
        {
            for (int j=0;j<s4et;j++)
            {
                if (chastj[p][o]==massnew[j][0])
                {
                    if (massnew[j][1]>o) massnew[j][1]=o;
                    if (massnew[j][2]<o) massnew[j][2]=o;
                    if (massnew[j][3]>p) massnew[j][3]=p;
                    if (massnew[j][4]<p) massnew[j][4]=p;
                }
            }
        }
    }
//----------------------------------------------------------------------------------------------------

//----------------------------зальем светло серый цвет как 40--------------------
    for (int p=0;p<visota;p++)
    {
        for (int o=0;o<dlina;o++)
        {
            if (risunok[p][o]=='%') chastj[p][o]=100;
        }
    }
//-------------------------------------------------------------------------------
//----------Удаляем у букв рамочки (если они имеются)--------------------------------------
// если получаем что одан широта, высота внутри другой => рамочка (ее убираем из рассмотрения)
    for (int p=0;p<s4et;p++)
    {
        for (int o=p;o<s4et;o++)
        {
            if ((massnew[o][1]>massnew[p][1])&&(massnew[o][2]<massnew[p][2])&&(massnew[o][3]>massnew[p][3])&&(massnew[o][4]<massnew[p][4])) { //cout <<o<<endl;
                  massnew[p][0]=0;}  //o внутри p
            if ((massnew[p][1]>massnew[o][1])&&(massnew[p][2]<massnew[o][2])&&(massnew[p][3]>massnew[o][3])&&(massnew[p][4]<massnew[o][4])) {// cout <<p<<endl;
                 massnew[o][0]=0;}  //p внутри o
        }
    }
//--------------------------------------------------------------------------
 //for (int p=0;p<s4et;p++)
 //   {
 //      cout<<massnew[p][0]<<" "<<massnew[p][1]<<" "<<massnew[p][2]<<" "<<massnew[p][3]<<" "<<massnew[p][4]<<endl;
 //   }
 //---------объединяем куски одной цифры-------------------------------------
   int polu4ilosj1=0;
    for (int p=0;p<s4et;p++)
    { if (massnew[p][0]!=0){
       // cout<<massnew[p][0]<<endl;
        for (int o=p+1;o<s4et;o++)
        {if (massnew[o][0]!=0){
            //cout<<massnew[o][0]<<endl;
            int max,vi4,visoti;
            if ((massnew[o][2]-massnew[o][1]-(massnew[p][2]-massnew[p][1]))>0) max=massnew[o][2]-massnew[o][1];
            if (!((massnew[o][2]-massnew[o][1]-(massnew[p][2]-massnew[p][1]))>0)) max=massnew[p][2]-massnew[p][1];
            if (massnew[o][2]<massnew[p][2] ) vi4=massnew[o][2]-massnew[p][1];
            if (!(massnew[o][2]<massnew[p][2] )) vi4=massnew[p][2]-massnew[o][1];
            if ( massnew[o][4]<massnew[p][4]) visoti=massnew[o][4]-massnew[p][3];
            if ( !(massnew[o][4]<massnew[p][4])) visoti=massnew[p][4]-massnew[o][3];
          //  cout<<max<<"-max "<<vi4<<"-perese4 "<<massnew[o][4]<<" -visoti- "<<massnew[p][3]<<endl;
            if ( (massnew[p][4]<massnew[o][4])&&((vi4>max/2)))
            {
             istina=0;
             // cout<<massnew[p][0]<<massnew[o][0]<<" "<<o<<" "<<p<<endl;
             int polu4ilosj;
                //пробуем объединить с помощью серого цвета (40)
               for (int l=massnew[p][1];l<massnew[p][2]+2;l++) //прибавляем 2 чтобы прочитать еще следующий знак
               {
                   if (chastj[massnew[p][4]][l]==massnew[p][0])
                   {
                       //cout<<l;
                       if (istina==0) perv=l;
                      istina=1;
                   }
                  // cout<<massnew[p][0]<<massnew[o][0]<<" "<<o<<" "<<p<<"-vot"<<endl;
                   if (chastj[massnew[p][4]][l]!=massnew[p][0])
                   {
                       if (istina==1)
                       {
                           vtor=l-1;
                           // cout<<massnew[p][0]<<massnew[o][0]<<endl;
                          // cout<<perv<<vtor<<endl;
                           polu4ilosj=chisloser(risunok,chastj,massnew[p][4],perv,vtor,massnew[o][0]);
                           //cout<<polu4ilosj<<" "<<massnew[o][0]<<" "<<massnew[p][0]<<endl;
                           if (polu4ilosj==1)
                           {
                               soedin(chastj,massnew[p][0],massnew[o][0]);
                               polu4ilosj1=1;
                               //massnew[o][0]=0;
                               massnew[p][4]=massnew[o][4];// конечная строка
                               if (massnew[p][1]>massnew[o][1]) massnew[p][1]=massnew[o][1];
                               if (massnew[p][2]<massnew[o][2]) massnew[p][2]=massnew[o][2];
                           }
                           if (polu4ilosj==0)  net_soedin(chastj);
                           istina=1;
                           polu4ilosj=0;
                        }

                    }

                }
              if (polu4ilosj1==1)   massnew[o][0]=0;
            }
           polu4ilosj1=0;
            if ( (massnew[p][4]>massnew[o][4])&&((vi4>max/2)))
            {
             istina=0;
             int polu4ilosj;
                //пробуем объединить с помощью серого цвета (100)
               for (int l=massnew[o][1];l<massnew[o][2]+1;l++)
               {
                   if (chastj[massnew[o][4]][l]==massnew[o][0])
                   {
                       if (istina==0) perv=l;
                      istina=1;
                   }
                   if (chastj[massnew[o][4]][l]!=massnew[o][0])
                   {
                       if (istina==1)
                       {
                           vtor=l-1;
                           polu4ilosj=chisloser(risunok,chastj,massnew[o][4],perv,vtor,massnew[p][0]);
                          // cout<<polu4ilosj;
                           if (polu4ilosj==1)
                           {
                               soedin(chastj,massnew[p][0],massnew[o][0]);
                               //massnew[o][0]=0;
                                 polu4ilosj1=1;
                               massnew[p][3]=massnew[o][3]; //начальная строка
                               if (massnew[p][1]>massnew[o][1]) massnew[p][1]=massnew[o][1];
                               if (massnew[p][2]<massnew[o][2]) massnew[p][2]=massnew[o][2];
                           }
                           if (polu4ilosj==0)  net_soedin(chastj);
                           istina=1;
                           polu4ilosj=0;
                        }

                    }

                }
              if (polu4ilosj1==1)  massnew[o][0]=0;
            }
        }}
    }}
 //--------------------------------------------------------------------------

//на случай если цифры сливаются темно серым
int chern_estj=0;
int kolvo_temn_ser=0;
int pomen=0;
int men[10][2];
 for (int p=0;p<s4et;p++)
    { if (massnew[p][0]!=0){
    for (int k=massnew[p][1];k<massnew[p][2]+1;k++)
    {
        kolvo_temn_ser=0;
        chern_estj=0;
        for(int t=massnew[p][3];t<massnew[p][4];t++)
        {
            if ((chastj[t][k]==massnew[p][0])&&(risunok[t][k]=='@')) chern_estj=1;
            if ((chastj[t][k]==massnew[p][0])&&(risunok[t][k]=='#')) kolvo_temn_ser++;
        }
        if (((kolvo_temn_ser<3)&&(chern_estj==0))&&((k-massnew[p][1])>((massnew[p][2]-massnew[p][1])*3/10))&&((k-massnew[p][1])<((massnew[p][2]-massnew[p][1])*7/10))) //цифры слились
        {
          //  cout<<k-massnew[p][1]<<" "<<(massnew[p][2]-massnew[p][1])<<endl;
           // cout<<p<<"-p "<<k<<"-k"<<endl;

        //-----исправление--------
           if (pomen==0)
            {
                men[pomen][0]=p;
            men[pomen][1]=k;
            pomen++;
            }
        //-----------------------

            if (men[pomen-1][1]-k>2){
            men[pomen][0]=p;
            men[pomen][1]=k;
            pomen++;}
        }
    }

 }}
 //cout<<pomen;




 //----сливание чисел (пересечение-одна строка)----------
int kuski_vert[20][2],kuski_vert1[20][2]; // начальная, конечная высота
int g,proshl1=0,vsego1;
for (int p=0;p<s4et;p++)
    { if (massnew[p][0]!=0){
   //     cout<<massnew[p][0]<<"iii"<<endl;
    for (int k=massnew[p][1];k<massnew[p][2]+1;k++)
    {
        kolvo_temn_ser=0;
        chern_estj=0;
        g=0;
        vsego1=0;
        for(int t=massnew[p][3];t<massnew[p][4];t++)
        {
            if ((chastj[t][k]==massnew[p][0])&&(chastj[t-1][k]!=massnew[p][0])) kuski_vert[g][0]=t;
            if ((chastj[t][k]!=massnew[p][0])&&(chastj[t-1][k]==massnew[p][0]))
            {kuski_vert[g][1]=t; g++;}
        }

        if (k>massnew[p][1]){
        for (int h=0;h<g;h++)
        {
            for (int y=0;y<proshl1;y++)
            {
               //cout<<kuski_vert[h][0]<<" "<<kuski_vert[h][1]<<"; "<<kuski_vert1[y][0]<<" "<<kuski_vert1[y][1];
               if (kuski_vert[h][0]<kuski_vert1[y][0] )
               {
                  if (kuski_vert[h][1]<kuski_vert1[y][1])
                  {
                     // cout<<" "<<1<<endl;
                    if((kuski_vert[h][1]-kuski_vert1[y][0]==1)&&(risunok[h][k]=='#')) vsego1++;
                    if(kuski_vert[h][1]-kuski_vert1[y][0]>1) {vsego1=vsego1+10;}
                  }
                   if (!(kuski_vert[h][1]<kuski_vert1[y][1]))
                  {
                       //  cout<<" "<<2<<endl;
                    if((kuski_vert1[y][1]-kuski_vert1[y][0]==1)&&(risunok[h][k]=='#')) vsego1++;
                    if(kuski_vert1[y][1]-kuski_vert1[y][0]>1) {vsego1=vsego1+10;}
                  }
                  //cout<<h<<"-h"<<endl;}

               }
               if (!(kuski_vert[h][0]<kuski_vert1[y][0] ))
               {
                   //cout<<kuski_vert[h][1]<<"-cei4 "<<kuski_vert1[y][0]<<"-prosh"<<endl;
                 if (kuski_vert[h][1]<kuski_vert1[y][1])
                  {
                       //  cout<<" "<<3<<endl;

                    if((kuski_vert[h][1]-kuski_vert[h][0]==1)&&(risunok[h][k]=='#')) vsego1++;
                    if(kuski_vert[h][1]-kuski_vert[h][0]>1) {vsego1=vsego1+10;}
                  }
                   if (!(kuski_vert[h][1]<kuski_vert1[y][1]))
                  {
                        // cout<<" "<<4<<" "<<risunok[kuski_vert[h][0]][k]<<h<<" "<<k<<endl;


                    if((kuski_vert1[y][1]-kuski_vert[h][0]==1)&&(risunok[kuski_vert[h][0]][k]=='#')) vsego1++;
                    if(kuski_vert1[y][1]-kuski_vert[h][0]>1) {vsego1=vsego1+10;}
                  }


               }
            }
        }
      //  cout<<vsego1<<"-vsego"<<k<<"-ctolbec"<<endl;
      //  if (vsego1==1) cout<<((k-massnew[p][1])>((massnew[p][2]-massnew[p][1])*3/10))<<((k-massnew[p][1])<((massnew[p][2]-massnew[p][1])*7/10))<<endl;
        if ((vsego1==1)&&((k-massnew[p][1])>((massnew[p][2]-massnew[p][1])*4/10))&&((k-massnew[p][1])<((massnew[p][2]-massnew[p][1])*6/10))) {men[pomen][0]=p;men[pomen][1]=k-1;pomen++;}
    }
        proshl1=g;
        for (int f=0;f<g;f++) {kuski_vert1[f][0]=kuski_vert[f][0]; kuski_vert1[f][1]=kuski_vert[f][1];}//cout<<kuski_vert[f][1]<<" "<<k<<endl;}

    }

 }}


//----------------------------------------------------------




 int na4_vis,kon_vis;
 for (int t=0;t<pomen;t++)
 {
      na4_vis=massnew[men[t][0]][4];kon_vis=massnew[men[t][0]][3];
      massnew[s4et+t]= new int[5];
         massnew[s4et+t][0]=80+t;
         massnew[s4et+t][1]=men[t][1]+1; //с какого столбца
         massnew[s4et+t][2]=massnew[men[t][0]][2]; // по какой
      //  cout<<men[t][1]<<" "<<men[t][0]<<" "<<massnew[0][0]<<endl;
        for (int u=men[t][1]+1;u<massnew[men[t][0]][2]+1;u++)
            {
               // cout<<u;
               // cout<<massnew[men[t][0]][3]<<" "<<massnew[men[t][0]][4]<<endl;
                for(int h=massnew[men[t][0]][3];h<massnew[men[t][0]][4]+1;h++)
                {
                  //cout<<chastj[h][u];
                 if (chastj[h][u]==massnew[men[t][0]][0])
                  {
                 //   cout<<h<<" "<<u<<";";
                    chastj[h][u]=80+t;
                    if (h>kon_vis) kon_vis=h;
                    if (h<na4_vis) na4_vis=h;
                  }
                }
            }
         massnew[s4et+t][3]=na4_vis; //с какой строки
         massnew[s4et+t][4]=kon_vis; //по какую строку
        // cout<<massnew[s4et+t][0]<<" "<<massnew[s4et+t][1]<<" "<<massnew[s4et+t][2]<<" "<<massnew[s4et+t][3]<<" "<<massnew[s4et+t][4]<<endl;
         na4_vis=massnew[men[t][0]][4];kon_vis=massnew[men[t][0]][3];
            for (int u=massnew[men[t][0]][1];u<men[t][1]+1;u++)
            {
                for(int h=massnew[men[t][0]][3];h<massnew[men[t][0]][4]+1;h++)
                {
                    if (chastj[h][u]==massnew[men[t][0]][0])
                  {

                    if (h>kon_vis) kon_vis=h;
                    if (h<na4_vis) na4_vis=h;
                  }
                }
            }

         massnew[men[t][0]][2]=men[t][1]; //по какой столбец
         massnew[men[t][0]][3]=na4_vis;//с какой строки
         massnew[men[t][0]][4]=kon_vis;//по какую строку
         //cout<< massnew[men[t][0]][0]<<" "<<massnew[men[t][0]][1]<<" "<<massnew[men[t][0]][2]<<" "<<massnew[men[t][0]][3]<<" "<<massnew[men[t][0]][4]<<endl;
 }
 s4et=s4et+pomen;

 //---------объединяем куски одной цифры-------------------------------------
    polu4ilosj1=0;
    for (int p=0;p<s4et;p++)
    { if (massnew[p][0]!=0){
       // cout<<massnew[p][0]<<endl;
        for (int o=p+1;o<s4et;o++)
        {if (massnew[o][0]!=0){
            //cout<<massnew[o][0]<<endl;
            int max,vi4,visoti;
            if ((massnew[o][2]-massnew[o][1]-(massnew[p][2]-massnew[p][1]))>0) max=massnew[o][2]-massnew[o][1];
            if (!((massnew[o][2]-massnew[o][1]-(massnew[p][2]-massnew[p][1]))>0)) max=massnew[p][2]-massnew[p][1];
            if (massnew[o][2]<massnew[p][2] ) vi4=massnew[o][2]-massnew[p][1];
            if (!(massnew[o][2]<massnew[p][2] )) vi4=massnew[p][2]-massnew[o][1];
            if ( massnew[o][4]<massnew[p][4]) visoti=massnew[o][4]-massnew[p][3];
            if ( !(massnew[o][4]<massnew[p][4])) visoti=massnew[p][4]-massnew[o][3];
          //  cout<<max<<"-max "<<vi4<<"-perese4 "<<massnew[o][4]<<" -visoti- "<<massnew[p][3]<<endl;
            if ( (massnew[p][4]<massnew[o][4])&&((vi4>max/2)))
            {
             istina=0;
             // cout<<massnew[p][0]<<massnew[o][0]<<" "<<o<<" "<<p<<endl;
             int polu4ilosj;
                //пробуем объединить с помощью серого цвета (40)
               for (int l=massnew[p][1];l<massnew[p][2]+2;l++) //прибавляем 2 чтобы прочитать еще следующий знак
               {
                   if (chastj[massnew[p][4]][l]==massnew[p][0])
                   {
                       //cout<<l;
                       if (istina==0) perv=l;
                      istina=1;
                   }
                  // cout<<massnew[p][0]<<massnew[o][0]<<" "<<o<<" "<<p<<"-vot"<<endl;
                   if (chastj[massnew[p][4]][l]!=massnew[p][0])
                   {
                       if (istina==1)
                       {
                           vtor=l-1;
                           // cout<<massnew[p][0]<<massnew[o][0]<<endl;
                          // cout<<perv<<vtor<<endl;
                           polu4ilosj=chisloser(risunok,chastj,massnew[p][4],perv,vtor,massnew[o][0]);
                           //cout<<polu4ilosj<<" "<<massnew[o][0]<<" "<<massnew[p][0]<<endl;
                           if (polu4ilosj==1)
                           {
                               soedin(chastj,massnew[p][0],massnew[o][0]);
                               polu4ilosj1=1;
                               //massnew[o][0]=0;
                               massnew[p][4]=massnew[o][4];// конечная строка
                               if (massnew[p][1]>massnew[o][1]) massnew[p][1]=massnew[o][1];
                               if (massnew[p][2]<massnew[o][2]) massnew[p][2]=massnew[o][2];
                           }
                           if (polu4ilosj==0)  net_soedin(chastj);
                           istina=1;
                           polu4ilosj=0;
                        }

                    }

                }
              if (polu4ilosj1==1)   massnew[o][0]=0;
            }
           polu4ilosj1=0;
            if ( (massnew[p][4]>massnew[o][4])&&((vi4>max/2)))
            {
             istina=0;
             int polu4ilosj;
                //пробуем объединить с помощью серого цвета (100)
               for (int l=massnew[o][1];l<massnew[o][2]+1;l++)
               {
                   if (chastj[massnew[o][4]][l]==massnew[o][0])
                   {
                       if (istina==0) perv=l;
                      istina=1;
                   }
                   if (chastj[massnew[o][4]][l]!=massnew[o][0])
                   {
                       if (istina==1)
                       {
                           vtor=l-1;
                           polu4ilosj=chisloser(risunok,chastj,massnew[o][4],perv,vtor,massnew[p][0]);
                          // cout<<polu4ilosj;
                           if (polu4ilosj==1)
                           {
                               soedin(chastj,massnew[p][0],massnew[o][0]);
                               //massnew[o][0]=0;
                                 polu4ilosj1=1;
                               massnew[p][3]=massnew[o][3]; //начальная строка
                               if (massnew[p][1]>massnew[o][1]) massnew[p][1]=massnew[o][1];
                               if (massnew[p][2]<massnew[o][2]) massnew[p][2]=massnew[o][2];
                           }
                           if (polu4ilosj==0)  net_soedin(chastj);
                           istina=1;
                           polu4ilosj=0;
                        }

                    }

                }
              if (polu4ilosj1==1)  massnew[o][0]=0;
            }
        }}
    }}
 //--------------------------------------------------------------------------


 //убираем куски которые не удалось объединить
 for (int p=0;p<s4et;p++)
    { if (massnew[p][0]!=0){
     if (10*(visota-5)/(massnew[p][4]-massnew[p][3])>32  ) massnew[p][0]=0;
    }}


//==============================================================================
//for (int i=0;i<40;i++) if (mass[i]!=0) cout<<mass[i]<<" ";
//рисунок на экран
  //    for (int p=0;p<visota;p++)
  //  {
  //      for (int o=0;o<dlina;o++)
  //     {if (chastj[p][o]!=100) cout<<chastj[p][o]; if (chastj[p][o]==100) cout<<0;}
  //   cout<<endl;
  //}

//=============РАСПОЗНАВАНИЕ==================================================
int w,napravl1=0,proshl=0,s4et4ik=0,prover;
int napravl[40][5]; // 1 направление;2,3- с какой по какую строку; 4,5-с какого по какой столбец
int q,ska4ok,ska4ok3,ska4ok5,ska4ok5_prav,ska4ok4,ska4ok2,ska4ok9,uklon4,ska4ok_lev,ska4ok_ne4;
//левая сторона
int cifr[10][10]; // 10 цифр и разбиваем всю высоту на 10 частей
 cifr[0][0]=-1; cifr[0][1]=-1;  cifr[0][2]=-1;  cifr[0][3]=-1;  cifr[0][4]=-1; cifr[0][5]=1; cifr[0][6]=1; cifr[0][7]=1; cifr[0][8]=1; cifr[0][9]=1;
 cifr[1][0]=-1; cifr[1][1]=-1;  cifr[1][2]=-1;  cifr[1][3]=-1;  cifr[1][4]=-1; cifr[1][5]=-1; cifr[1][6]=-1; cifr[1][7]=-1; cifr[1][8]=-1; cifr[1][9]=-1;
 cifr[2][0]=-1; cifr[2][1]=-1;  cifr[2][2]=-1;  cifr[2][3]=-1;  cifr[2][4]=-1; cifr[2][5]=-1; cifr[2][6]=-1; cifr[2][7]=-1; cifr[2][8]=-1; cifr[2][9]=-1;
 cifr[3][0]=-1; cifr[3][1]=-1;  cifr[3][2]=-1;  cifr[3][3]=-1;  cifr[3][4]=-1; cifr[3][5]=1; cifr[3][6]=1; cifr[3][7]=-1; cifr[3][8]=-1; cifr[3][9]=-1;
 cifr[4][0]=-1; cifr[4][1]=-1;  cifr[4][2]=-1;  cifr[4][3]=-1;  cifr[4][4]=-1; cifr[4][5]=-1; cifr[4][6]=-1; cifr[4][7]=-1; cifr[4][8]=-1; cifr[4][9]=-1;
 cifr[5][0]=-1; cifr[5][1]=-1;  cifr[5][2]=-1;  cifr[5][3]=-1;  cifr[5][4]=-1; cifr[5][5]=1; cifr[5][6]=1; cifr[5][7]=-1; cifr[5][8]=-1; cifr[5][9]=1;
 cifr[6][0]=-1; cifr[6][1]=-1;  cifr[6][2]=-1;  cifr[6][3]=-1;  cifr[6][4]=-1; cifr[6][5]=-1; cifr[6][6]=1; cifr[6][7]=1; cifr[6][8]=1; cifr[6][9]=1;
 cifr[7][0]=-1; cifr[7][1]=-1;  cifr[7][2]=-1;  cifr[7][3]=-1;  cifr[7][4]=-1; cifr[7][5]=-1; cifr[7][6]=-1; cifr[7][7]=-1; cifr[7][8]=-1; cifr[7][9]=-1;
 cifr[8][0]=-1; cifr[8][1]=-1;  cifr[8][2]=-1;  cifr[8][3]=1;  cifr[8][4]=1; cifr[8][5]=-1; cifr[8][6]=-1; cifr[8][7]=-1; cifr[8][8]=1; cifr[8][9]=1;
 cifr[9][0]=-1; cifr[9][1]=-1;  cifr[9][2]=-1;  cifr[9][3]=-1;  cifr[9][4]=1; cifr[9][5]=1; cifr[9][6]=1; cifr[9][7]=-1; cifr[9][8]=-1; cifr[9][9]=1;


//правая сторона
int cifr1[10][10]; // 10 цифр и разбиваем всю высоту на 10 частей
 cifr1[0][0]=1; cifr1[0][1]=1;  cifr1[0][2]=1;  cifr1[0][3]=1;  cifr1[0][4]=1; cifr1[0][5]=-1; cifr1[0][6]=-1; cifr1[0][7]=-1; cifr1[0][8]=-1; cifr1[0][9]=-1;
 cifr1[1][0]=-1; cifr1[1][1]=-1;  cifr1[1][2]=-1;  cifr1[1][3]=-1;  cifr1[1][4]=-1; cifr1[1][5]=-1; cifr1[1][6]=-1; cifr1[1][7]=-1; cifr1[1][8]=-1; cifr1[1][9]=-1;
 cifr1[2][0]=1; cifr1[2][1]=1;  cifr1[2][2]=-1;  cifr1[2][3]=-1;  cifr1[2][4]=-1; cifr1[2][5]=-1; cifr1[2][6]=-1; cifr1[2][7]=-1; cifr1[2][8]=-1; cifr1[2][9]=-1;
 cifr1[3][0]=1; cifr1[3][1]=1;  cifr1[3][2]=-1;  cifr1[3][3]=-1;  cifr1[3][4]=-1; cifr1[3][5]=1; cifr1[3][6]=1; cifr1[3][7]=-1; cifr1[3][8]=-1; cifr1[3][9]=-1;
 cifr1[4][0]=-1; cifr1[4][1]=-1;  cifr1[4][2]=-1;  cifr1[4][3]=-1;  cifr1[4][4]=-1; cifr1[4][5]=-1; cifr1[4][6]=-1; cifr1[4][7]=-1; cifr1[4][8]=-1; cifr1[4][9]=-1;
 cifr1[5][0]=-1; cifr1[5][1]=-1;  cifr1[5][2]=-1;  cifr1[5][3]=1;  cifr1[5][4]=1; cifr1[5][5]=1; cifr1[5][6]=-1; cifr1[5][7]=-1; cifr1[5][8]=-1; cifr1[5][9]=-1;
 cifr1[6][0]=-1; cifr1[6][1]=-1;  cifr1[6][2]=-1;  cifr1[6][3]=-1;  cifr1[6][4]=1; cifr1[6][5]=1; cifr1[6][6]=1; cifr1[6][7]=-1; cifr1[6][8]=-1; cifr1[6][9]=-1;
 cifr1[7][0]=-1; cifr1[7][1]=-1;  cifr1[7][2]=-1;  cifr1[7][3]=-1;  cifr1[7][4]=-1; cifr1[7][5]=-1; cifr1[7][6]=-1; cifr1[7][7]=-1; cifr1[7][8]=-1; cifr1[7][9]=-1;
 cifr1[8][0]=1; cifr1[8][1]=1;  cifr1[8][2]=1;  cifr1[8][3]=-1;  cifr1[8][4]=-1; cifr1[8][5]=1; cifr1[8][6]=1; cifr1[8][7]=1; cifr1[8][8]=-1; cifr1[8][9]=-1;
 cifr1[9][0]=1; cifr1[9][1]=1;  cifr1[9][2]=1;  cifr1[9][3]=1;  cifr1[9][4]=1; cifr1[9][5]=-1; cifr1[9][6]=-1; cifr1[9][7]=-1; cifr1[9][8]=-1; cifr1[9][9]=-1;


//=====================================ЛЕВАЯ СТОРОНА=====================================================================
int min_lev1,min_lev2, max_prav1,max_prav2;
for (int p=0;p<s4et;p++)
 {
     s4et4ik=0;
     if (massnew[p][0]!=0)
     {
         //cout<<massnew[p][0];
         ska4ok=0;
         ska4ok3=0;
         ska4ok5=0;
         ska4ok5_prav=0;
         ska4ok4=0;
         ska4ok2=0;
         ska4ok9=0;
         uklon4=0;
         ska4ok_lev=0;
         ska4ok_ne4=0;
         min_lev1=massnew[p][2];
         min_lev2=massnew[p][2];
         max_prav1=massnew[p][1];
         max_prav2=massnew[p][1];
        w=massnew[p][1];
       // cout<<massnew[p][0]<<endl;
        while ( chastj[massnew[p][3]][w]!=massnew[p][0] ) w++;// отдельно рассматриваем первуцю строку где есть эта цифра
        napravl[s4et4ik][0]=0;
        napravl[s4et4ik][1]=massnew[p][3];
        napravl[s4et4ik][3]=w;
        napravl1=5;
        proshl=w;
        min_lev1=w;
        for ( q=massnew[p][3]+1;q<massnew[p][4]+1;q++)
        {
            if ((100*(q-massnew[p][3]))/(massnew[p][4]-massnew[p][3])<35)
            {
                if (w<min_lev1) min_lev1=w;
            }
             if ((100*(q-massnew[p][3]))/(massnew[p][4]-massnew[p][3])>65)
            {
                if (w<min_lev2) min_lev2=w;
            }
           w=massnew[p][1];
           while ( chastj[q][w]!=massnew[p][0] ) w++; //считываем до первого знака этой цифры
           //cout<<proshl<<"-proshl "<<w<<endl;
           prover=0;
           if (proshl>w)
           {
               if ((napravl1==0)||(napravl1==-1)||(proshl-w>2))
               {
                   napravl[s4et4ik][2]=q-1; //записываем в массив по какую строку
                   napravl[s4et4ik][4]=proshl; //записываем в массив по какой столбец
                   s4et4ik++;
                   napravl[s4et4ik][1]=q;
                   napravl[s4et4ik][3]=w;
                   napravl[s4et4ik][0]=1;
               }
               if (napravl1==5) // если это вторая строка
               {
                  napravl[s4et4ik][0]=1;
               }
               proshl=w;
               napravl1=1;
               prover=1;
           }
           if ((proshl<w)&&(prover==0))
           {
                if ((napravl1==0)||(napravl1==1)||(w-proshl>2))
               {
                   napravl[s4et4ik][2]=q-1; //записываем в массив по какую строку
                   napravl[s4et4ik][4]=proshl; //записываем в массив по какой столбец
                   s4et4ik++;
                   napravl[s4et4ik][1]=q;
                   napravl[s4et4ik][3]=w;
                   napravl[s4et4ik][0]=-1;
               }

               if (napravl1==5) // если это вторая строка
               {
                  napravl[s4et4ik][0]=-1;
               }
                proshl=w;
                napravl1=-1;
                prover=1;
           }
           if ((proshl=w)&&(prover==0))
           {
                if ((napravl1==1)||(napravl1==-1))
               {
                   napravl[s4et4ik][2]=q-1; //записываем в массив по какую строку
                   napravl[s4et4ik][4]=proshl; //записываем в массив по какой столбец
                   s4et4ik++;
                   napravl[s4et4ik][1]=q;
                   napravl[s4et4ik][3]=w;
                   napravl[s4et4ik][0]=0;
               }

               if (napravl1==5) // если это вторая строка
               {
                  napravl[s4et4ik][0]=0;
               }
               proshl=w;
               napravl1=0;
               prover=1;
           }
        }
        //дозаписываем данные в массив из заключительной строки
        napravl[s4et4ik][2]=q; //записываем в массив по какую строку
        napravl[s4et4ik][4]=proshl; //записываем в массив по какой столбец
     //for (int i=0;i<s4et4ik+1;i++) cout<<napravl[i][0]<<" "<<napravl[i][1]<<" "<<napravl[i][2]<<" "<<napravl[i][3]<<" "<<napravl[i][4]<<";";
      //  cout<<endl;

        int napravl_new[40][6]; //направление с какой по какую строку с какого по какой столбец, скачок
        int k=0;
//----------------------------доработка--------------------------------------------------------
        napravl_new[k][0]=napravl[0][0];
        napravl_new[k][1]=napravl[0][1];
        napravl_new[k][2]=napravl[0][2];
        napravl_new[k][3]=napravl[0][3];
        napravl_new[k][4]=napravl[0][4];
        napravl_new[k][5]=0;
        for (int i=1;i<s4et4ik+1;i++)
        {    //если прошлая строка -1 или +1 а эта 0 и если они начинаются рядом объединяем и условие что этот кусок занимает более 2 строк что бы не было путаницы после скачка перехода
            if ((((napravl_new[k][0]==-1)&&(napravl[i][0]==0)) && ((napravl_new[k][4]-napravl[i][3]<2)&&(napravl[i][3]-napravl_new[k][4]<2))) &&(napravl_new[k][5]==0) )//&& ( napravl_new[k][2]-napravl_new[k][1]>1 )  )
            {
             napravl_new[k][2]=napravl[i][2];
            }
            else if ((((napravl_new[k][0]==1)&&(napravl[i][0]==0)) && ((napravl_new[k][4]-napravl[i][3]<2)&&(napravl[i][3]-napravl_new[k][4]<2))) &&(napravl_new[k][5]==0) )//&& ( napravl_new[k][2]-napravl_new[k][1]>1 )  )
            {
               napravl_new[k][2]=napravl[i][2];
            } // если ранее объединили 1(-1) и 0 а теперь опять 1(-1);
            else if (( napravl_new[k][0]==napravl[i][0])&&((napravl_new[k][4]-napravl[i][3]<2)&&(napravl[i][3]-napravl_new[k][4]<2)))
            {
                napravl_new[k][2]=napravl[i][2];
                napravl_new[k][4]=napravl[i][4];
            }
            else
            {
                k++;
                napravl_new[k][0]=napravl[i][0];
                napravl_new[k][1]=napravl[i][1];
                napravl_new[k][2]=napravl[i][2];
                napravl_new[k][3]=napravl[i][3];
                napravl_new[k][4]=napravl[i][4];
               // cout<<napravl[i][3]-napravl_new[k-1][4]<<"cka4ok"<<endl;
                if ((napravl[i][3]-napravl_new[k-1][4]<2)&&(-(napravl[i][3]-napravl_new[k-1][4])<2)) napravl_new[k][5]=0;
                else {
                    napravl_new[k][5]=1;
                    if (((!((napravl[i][3]-napravl_new[k-1][4]<3)&&(-(napravl[i][3]-napravl_new[k-1][4])<3)))&&(((100*(napravl_new[k][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]))>25))&& ((napravl_new[k][3]-napravl_new[k-1][4])>((massnew[p][2]-massnew[p][1])/6))) ska4ok=1;
                    if (((!((napravl[i][3]-napravl_new[k-1][4]<3)&&(-(napravl[i][3]-napravl_new[k-1][4])<3)))&&(((100*(napravl_new[k][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]))>25))&& ((-napravl_new[k][3]+napravl_new[k-1][4])>((massnew[p][2]-massnew[p][1])/6))) ska4ok=1;
                    if (((!((napravl[i][3]-napravl_new[k-1][4]<3)&&(-(napravl[i][3]-napravl_new[k-1][4])<3)))&&(((100*(napravl_new[k][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]))<40))&&(napravl_new[k][0]==-1)&&((napravl_new[k][3]-napravl_new[k-1][4])>((massnew[p][2]-massnew[p][1])/6)))
                     ska4ok3=1;
if ((((!((napravl[i][3]-napravl_new[k-1][4]<3)&&(-(napravl[i][3]-napravl_new[k-1][4])<3)))&&(((100*(napravl_new[k][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]))>60))&&(napravl_new[k][0]==1))&& ((napravl_new[k-1][4]-napravl_new[k][3])>((massnew[p][2]-massnew[p][1])/6))) ska4ok5=1;
if ((((!((napravl[i][3]-napravl_new[k-1][4]<3)&&(-(napravl[i][3]-napravl_new[k-1][4])<3)))&&(((100*(napravl_new[k][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]))>50)&&(((100*(napravl_new[k][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]))<90))&&(napravl_new[k][0]==-1)) && ((napravl_new[k][3]-napravl_new[k-1][4])>((massnew[p][2]-massnew[p][1])/3)))
ska4ok4=1;
if ((((!((napravl[i][3]-napravl_new[k-1][4]<3)&&(-(napravl[i][3]-napravl_new[k-1][4])<3)))&&(((100*(napravl_new[k][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]))>40))&&(((100*(napravl_new[k][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]))<50)&&(napravl_new[k][0]==-1))
&& (((massnew[p][4]-massnew[p][3])/(napravl_new[k][3]-napravl_new[k-1][4]))<3)&&((napravl_new[k][3]-napravl_new[k-1][4])>0)) ska4ok9=1; //отношение к высоте специально
                  //cout<<napravl_new[k-1][4]-napravl_new[k][3]<<" "<<massnew[p][2]-massnew[p][1]<<endl;
      if (((!((napravl[i][3]-napravl_new[k-1][4]<3)&&(-(napravl[i][3]-napravl_new[k-1][4])<3))))&& (((massnew[p][4]-massnew[p][3])/(napravl_new[k][3]-napravl_new[k-1][4]))<4)&&((napravl_new[k][3]-napravl_new[k-1][4])>0)) ska4ok_lev=1; //отношение к высоте специал

 if (((!((napravl[i][3]-napravl_new[k-1][4]<3)&&(-(napravl[i][3]-napravl_new[k-1][4])<3))))&& (((massnew[p][4]-massnew[p][3])/(napravl_new[k-1][4]-napravl_new[k][3]))<4)&&((napravl_new[k][3]-napravl_new[k-1][4])<0)) ska4ok_lev=1;
 if (((!((napravl[i][3]-napravl_new[k-1][4]<3)&&(-(napravl[i][3]-napravl_new[k-1][4])<3))))&& (((massnew[p][4]-massnew[p][3])/(napravl_new[k][3]-napravl_new[k-1][4]))<4)&&((napravl_new[k][3]-napravl_new[k-1][4])>0)&&(((100*(napravl_new[k][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]))<30))
 ska4ok_ne4=1;
                    }
            }
            if ( (10*(massnew[p][4]-massnew[p][3])/(napravl_new[k][1]-napravl_new[k-1][1])<17) && (napravl_new[k-1][0]==1) && ((napravl_new[k-1][1]-massnew[p][3])<3) ) uklon4=1;
        // for (int i=0;i<k+1;i++) cout<<napravl_new[i][0]<<" "<<napravl_new[i][1]<<";";
        // cout<<endl;
        }
        // получили объединенные куски
   //cout<<"novoe:";
   //    for (int i=0;i<k+1;i++) cout<<napravl_new[i][0]<<" "<<napravl_new[i][1]<<" "<<napravl_new[i][2]<<" "<<napravl_new[i][3]<<" "<<napravl_new[i][4]<<" "<<napravl_new[i][5]<<";";
   // cout<<endl;
  //-------если почти вертикально-------------------

     for (int i=0;i<k+1;i++)
       {
          //cout<<(napravl_new[i][2]-napravl_new[i][1])<<" "<<(napravl_new[i][4]-napravl_new[i][3])<<endl;
           if (napravl_new[i][4]-napravl_new[i][3]>0){
              // cout<<(napravl_new[i][2]-napravl_new[i][1])/(napravl_new[i][4]-napravl_new[i][3])<<endl;
           if ( ((napravl_new[i][2]-napravl_new[i][1])/(napravl_new[i][4]-napravl_new[i][3]))>15 ) napravl_new[i][0]=0;
       }}

       //------------------------------
//------------------------------------------------------------------------------------------------
//--------------Смотрим сходство с цифрами--------------------------------------------------------

      int cifra[10]; //в массиве отмечаем сходство
      for (int i=0;i<10;i++) cifra[i]=0;
      int na4_proc,kon_proc; // начальная и конечная часть(от высоты) куска в %
       for (int i=0;i<k+1;i++) //обходим по кускам
       {
           na4_proc=((100*(napravl_new[i][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]));
           kon_proc=((100*(napravl_new[i][2]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]));
           for (int j=na4_proc/10+1;j<kon_proc/10;j++)
           {
               for (int t=0;t<10;t++) //прибавляем где полные куски
               {
                   if (cifr[t][j]==-napravl_new[i][0]) cifra[t]=cifra[t]+10; //- так как перепутаа при вводе массива
               }
           }
            for (int t=0;t<10;t++) //прибавляем где НЕ полные куски
            {
                if (cifr[t][na4_proc/10]==-napravl_new[i][0]) cifra[t]=cifra[t]+na4_proc%10;
                if (cifr[t][kon_proc/10]==-napravl_new[i][0]) cifra[t]=cifra[t]+kon_proc%10;
            }


            //вертикальные полосы не отмечены
            if (napravl_new[i][0]==0)
            {
                cifra[0]=cifra[0]+kon_proc-na4_proc;
                cifra[6]=cifra[6]+kon_proc-na4_proc;
                cifra[1]=cifra[1]+kon_proc-na4_proc;
                if ((kon_proc<60)) cifra[8]=cifra[8]+kon_proc-na4_proc;
                if ((na4_proc>50)) cifra[8]=cifra[8]+kon_proc-na4_proc;
                if ((kon_proc<60)) cifra[3]=cifra[3]+kon_proc-na4_proc;
                if ((kon_proc<60)) cifra[2]=cifra[2]+kon_proc-na4_proc;
                if ((kon_proc<60)) cifra[5]=cifra[5]+kon_proc-na4_proc;
                if ((kon_proc<60)) cifra[7]=cifra[7]+kon_proc-na4_proc;
                if ((kon_proc<60)) cifra[9]=cifra[9]+kon_proc-na4_proc;
                if ((na4_proc>50)) cifra[9]=cifra[9]+kon_proc-na4_proc;
                if ((na4_proc>50)) cifra[3]=cifra[3]+kon_proc-na4_proc;
                if ((na4_proc>50)) cifra[4]=cifra[4]+kon_proc-na4_proc;
                if ((na4_proc>50)) cifra[5]=cifra[5]+kon_proc-na4_proc;
                if ((na4_proc>50)) cifra[7]=cifra[7]+kon_proc-na4_proc;


       }
     //  cout<<endl;
     //          for (int i=0;i<10;i++)
    //   {
    //    cout<<i<<" "<<cifra[i]<<";";
    //   }
    //   cout<<endl;
            }
int s4et4ik_lev=s4et4ik;


//=========================================================================================================================
//==============ПРАВАЯ СТОРОНА============================================================================================
       napravl1=0;proshl=0;s4et4ik=0;
// 1 направление;2,3- с какой по какую строку; 4,5-с какого по какой столбец

               w=massnew[p][2];
        while ( chastj[massnew[p][3]][w]!=massnew[p][0] ) w--;// отдельно рассматриваем первуцю строку где есть эта цифра

        napravl[s4et4ik][0]=0;
        napravl[s4et4ik][1]=massnew[p][3];
        napravl[s4et4ik][3]=w;
        napravl1=5;
        proshl=w;
        max_prav1=w;
        for ( q=massnew[p][3]+1;q<massnew[p][4]+1;q++)
        {
           w=massnew[p][2];
           while ( chastj[q][w]!=massnew[p][0] ) w--; //считываем до первого знака этой цифры
           //cout<<proshl<<"-proshl "<<w<<endl;
           if ((100*(q-massnew[p][3]))/(massnew[p][4]-massnew[p][3])<35)//было 55
            {
                if (w>max_prav1) max_prav1=w;
            }
             if ((100*(q-massnew[p][3]))/(massnew[p][4]-massnew[p][3])>65)
            {
                if (w>max_prav2) max_prav2=w;
            }
           prover=0;
           if (proshl>w)
           {
               if ((napravl1==0)||(napravl1==-1)||(proshl-w>2))
               {
                   napravl[s4et4ik][2]=q-1; //записываем в массив по какую строку
                   napravl[s4et4ik][4]=proshl; //записываем в массив по какой столбец
                   s4et4ik++;
                   napravl[s4et4ik][1]=q;
                   napravl[s4et4ik][3]=w;
                   napravl[s4et4ik][0]=1;
               }
               if (napravl1==5) // если это вторая строка
               {
                  napravl[s4et4ik][0]=1;
               }
               proshl=w;
               napravl1=1;
               prover=1;
           }
           if ((proshl<w)&&(prover==0))
           {
                if ((napravl1==0)||(napravl1==1)||(w-proshl>2))
               {
                   napravl[s4et4ik][2]=q-1; //записываем в массив по какую строку
                   napravl[s4et4ik][4]=proshl; //записываем в массив по какой столбец
                   s4et4ik++;
                   napravl[s4et4ik][1]=q;
                   napravl[s4et4ik][3]=w;
                   napravl[s4et4ik][0]=-1;
               }

               if (napravl1==5) // если это вторая строка
               {
                  napravl[s4et4ik][0]=-1;
               }
                proshl=w;
                napravl1=-1;
                prover=1;
           }
           if ((proshl=w)&&(prover==0))
           {
                if ((napravl1==1)||(napravl1==-1))
               {
                   napravl[s4et4ik][2]=q-1; //записываем в массив по какую строку
                   napravl[s4et4ik][4]=proshl; //записываем в массив по какой столбец
                   s4et4ik++;
                   napravl[s4et4ik][1]=q;
                   napravl[s4et4ik][3]=w;
                   napravl[s4et4ik][0]=0;
               }

               if (napravl1==5) // если это вторая строка
               {
                  napravl[s4et4ik][0]=0;
               }
               proshl=w;
               napravl1=0;
               prover=1;
           }
        }
        //дозаписываем данные в массив из заключительной строки
        napravl[s4et4ik][2]=q; //записываем в массив по какую строку
        napravl[s4et4ik][4]=proshl; //записываем в массив по какой столбец
       // for (int i=0;i<s4et4ik+1;i++) cout<<napravl[i][0]<<" "<<napravl[i][1]<<";";
       // cout<<endl;
        //napravl_new[40][6]; //направление с какой по какую строку с какого по какой столбец, скачок
          k=0;
          int napravl_new1[40][6]; //направление с какой по какую строку с какого по какой столбец, скачок
//----------------------------доработка--------------------------------------------------------
        napravl_new1[k][0]=napravl[0][0];
        napravl_new1[k][1]=napravl[0][1];
        napravl_new1[k][2]=napravl[0][2];
        napravl_new1[k][3]=napravl[0][3];
        napravl_new1[k][4]=napravl[0][4];
        napravl_new1[k][5]=0;
        for (int i=1;i<s4et4ik+1;i++)
        {    //если прошлая строка -1 или +1 а эта 0 и если они начинаются рядом объединяем и условие что этот кусок занимает более 2 строк что бы не было путаницы после скачка перехода
            if ((((napravl_new1[k][0]==-1)&&(napravl[i][0]==0)) && ((napravl_new1[k][4]-napravl[i][3]<2)&&(napravl[i][3]-napravl_new1[k][4]<2))) &&(napravl_new1[k][5]==0) )//&& ( napravl_new[k][2]-napravl_new[k][1]>1 )  )
            {
             napravl_new1[k][2]=napravl[i][2];
            }
            else if ((((napravl_new1[k][0]==1)&&(napravl[i][0]==0)) && ((napravl_new1[k][4]-napravl[i][3]<2)&&(napravl[i][3]-napravl_new1[k][4]<2))) &&(napravl_new1[k][5]==0) )//&& ( napravl_new[k][2]-napravl_new[k][1]>1 )  )
            {
               napravl_new1[k][2]=napravl[i][2];
            } // если ранее объединили 1(-1) и 0 а теперь опять 1(-1);
            else if (( napravl_new1[k][0]==napravl[i][0])&&((napravl_new1[k][4]-napravl[i][3]<2)&&(napravl[i][3]-napravl_new1[k][4]<2)))
            {
                napravl_new1[k][2]=napravl[i][2];
                napravl_new1[k][4]=napravl[i][4];
            }
            else
            {
                k++;
                napravl_new1[k][0]=napravl[i][0];
                napravl_new1[k][1]=napravl[i][1];
                napravl_new1[k][2]=napravl[i][2];
                napravl_new1[k][3]=napravl[i][3];
                napravl_new1[k][4]=napravl[i][4];
                if ((napravl[i][3]-napravl_new1[k-1][4]<3)&&(-(napravl[i][3]-napravl_new1[k-1][4])<2)) napravl_new1[k][5]=0;
                else {napravl_new1[k][5]=1;
                if (((!((napravl[i][3]-napravl_new1[k-1][4]<3)&&(-(napravl[i][3]-napravl_new1[k-1][4])<3))) &&(((100*(napravl_new1[k][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]))>25))&& ((napravl_new1[k][3]-napravl_new1[k-1][4])>((massnew[p][2]-massnew[p][1])/6))) ska4ok=1;
                if (((!((napravl[i][3]-napravl_new1[k-1][4]<3)&&(-(napravl[i][3]-napravl_new1[k-1][4])<3))) &&(((100*(napravl_new1[k][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]))>25))&& ((-napravl_new1[k][3]+napravl_new1[k-1][4])>((massnew[p][2]-massnew[p][1])/6))) ska4ok=1;
                if ((((!((napravl[i][3]-napravl_new1[k-1][4]<3)&&(-(napravl[i][3]-napravl_new1[k-1][4])<3))) &&(((100*(napravl_new1[k][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]))<50))&&(napravl_new1[k][0]==1))&& ((napravl_new1[k-1][4]-napravl_new1[k][3])>((massnew[p][2]-massnew[p][1])/6)))
                 ska4ok5_prav=1;
if ((((!((napravl[i][3]-napravl_new1[k-1][4]<3)&&(-(napravl[i][3]-napravl_new1[k-1][4])<3)))&&(((100*(napravl_new1[k][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]))>60))&&(napravl_new1[k][0]==-1)) && ((napravl_new1[k][3]-napravl_new1[k-1][4])>((massnew[p][2]-massnew[p][1])/5)))
ska4ok2=1;

                }
            }
        // for (int i=0;i<k+1;i++) cout<<napravl_new[i][0]<<" "<<napravl_new[i][1]<<";";
        // cout<<endl;
        }
        // получили объединенные куски
      //  cout<<"novoe:";
      //  for (int i=0;i<k+1;i++) cout<<napravl_new1[i][0]<<" "<<napravl_new1[i][1]<<" "<<napravl_new1[i][2]<<" "<<napravl_new1[i][3]<<" "<<napravl_new1[i][4]<<" "<<napravl_new1[i][5]<<";";
      //  cout<<endl;
      //-------если почти вертикально-------------------
for (int i=0;i<k+1;i++)
       {
           if (napravl_new1[i][4]-napravl_new1[i][3]>0){
           if ( ((napravl_new1[i][2]-napravl_new1[i][1])/(napravl_new1[i][4]-napravl_new1[i][3]))>15 ) napravl_new1[i][0]=0;
       }}
       //------------------------------
//------------------------------------------------------------------------------------------------
//--------------Смотрим сходство с цифрами--------------------------------------------------------
      int cifra_prav[10]; //в массиве отмечаем сходство
      for (int i=0;i<10;i++) cifra_prav[i]=0;
       na4_proc=0;kon_proc=0; // начальная и конечная часть(от высоты) куска в %
       for (int i=0;i<k+1;i++) //обходим по кускам
       {
           na4_proc=((100*(napravl_new1[i][1]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]));
           kon_proc=((100*(napravl_new1[i][2]-massnew[p][3]))/(massnew[p][4]-massnew[p][3]));
          // cout<<massnew[p][4]<<" visota"<<endl;
           for (int j=na4_proc/10+1;j<kon_proc/10;j++)
           {
               for (int t=0;t<10;t++) //прибавляем где полные куски
               {
                   if (cifr1[t][j]==-napravl_new1[i][0]) cifra_prav[t]=cifra_prav[t]+10; //- так как перепутаа при вводе массива
               }
           }
            for (int t=0;t<10;t++) //прибавляем где НЕ полные куски
            {
                if (cifr1[t][na4_proc/10]==-napravl_new1[i][0]) cifra_prav[t]=cifra_prav[t]+na4_proc%10;
                if (cifr1[t][kon_proc/10]==-napravl_new1[i][0]) cifra_prav[t]=cifra_prav[t]+kon_proc%10;
            }
            //вертикальные полосы не отмечены
            if (napravl_new1[i][0]==0)
            {
                cifra_prav[0]=cifra_prav[0]+kon_proc-na4_proc;
                if ((kon_proc<60)) cifra_prav[5]=cifra_prav[5]+kon_proc-na4_proc;
                if ((na4_proc>50)) cifra_prav[5]=cifra_prav[5]+kon_proc-na4_proc;
                if ((kon_proc<60)) cifra_prav[6]=cifra_prav[6]+kon_proc-na4_proc;
                if ((na4_proc>50)) cifra_prav[6]=cifra_prav[6]+kon_proc-na4_proc;
                cifra_prav[1]=cifra_prav[1]+kon_proc-na4_proc;
                cifra_prav[4]=cifra_prav[4]+kon_proc-na4_proc;
                cifra_prav[7]=cifra_prav[7]+kon_proc-na4_proc;
                cifra_prav[9]=cifra_prav[9]+kon_proc-na4_proc;
                if ((kon_proc<60)) cifra_prav[2]=cifra_prav[2]+kon_proc-na4_proc;
                if ((na4_proc>50)) cifra_prav[2]=cifra_prav[2]+kon_proc-na4_proc;
                if ((kon_proc<60)) cifra_prav[3]=cifra_prav[3]+kon_proc-na4_proc;
                if ((na4_proc>50)) cifra_prav[3]=cifra_prav[3]+kon_proc-na4_proc;
                if ((kon_proc<60)) cifra_prav[8]=cifra_prav[8]+kon_proc-na4_proc;
                if ((na4_proc>50)) cifra_prav[8]=cifra_prav[8]+kon_proc-na4_proc;
            }
       }
int cifr_sum[10];
      for (int i=0;i<10;i++)
       {
           cifr_sum[i]=cifra_prav[i]+cifra[i];
     //  cout<<i<<" "<<cifra_prav[i]+cifra[i]<<";";
       }
     // cout<<endl;
      if (ska4ok_ne4==1) {cifr_sum[4]=cifr_sum[4]-15;cifr_sum[3]=cifr_sum[3]+12;}
      if (ska4ok_lev==1) cifr_sum[6]=cifr_sum[6]-45;
      if (ska4ok_lev==0) {cifr_sum[5]=cifr_sum[5]-10;cifr_sum[3]=cifr_sum[3]-10;}
      if (uklon4==1) {cifr_sum[9]=cifr_sum[9]-40;cifr_sum[4]=cifr_sum[4]+15;}
     if (ska4ok9==1) {cifr_sum[9]=cifr_sum[9]+20;cifr_sum[1]=cifr_sum[1]-15;}
     if ((max_prav2-min_lev2)>((max_prav1-min_lev1)*75)/100)
     {cifr_sum[2]=cifr_sum[2]+10;
     cifr_sum[8]=cifr_sum[8]+10;
     cifr_sum[3]=cifr_sum[3]+10;
     cifr_sum[5]=cifr_sum[5]+10;
     cifr_sum[6]=cifr_sum[6]+10;
     cifr_sum[0]=cifr_sum[0]+10;
     cifr_sum[4]=cifr_sum[4]+10;
     cifr_sum[1]=cifr_sum[1]+10; //ggggg
     }
    // cout<<max_prav2-min_lev2<<max_prav1-min_lev1<<endl;
     if ((max_prav2-min_lev2)-(max_prav1-min_lev1)>2) {cifr_sum[8]=cifr_sum[8]+10;cifr_sum[0]=cifr_sum[0]-20;}
     else if ((max_prav2>max_prav1)) cifr_sum[1]=cifr_sum[1]+10;
     else if  ((max_prav2-min_lev2)<(max_prav1-min_lev1)*60/100) cifr_sum[7]=cifr_sum[7]+10;
     if ((ska4ok==0)&&(ska4ok2==0)&&(ska4ok3==0)&&(ska4ok4==0)&&(ska4ok5==0)&&(ska4ok5_prav==0)) { cifr_sum[0]=cifr_sum[0]+10;cifr_sum[8]=cifr_sum[8]+10; cifr_sum[1]=cifr_sum[1]+10;}
     if ((ska4ok==1)||(ska4ok2==1)||(ska4ok3==1)||(ska4ok4==1)||(ska4ok5==1)||(ska4ok5_prav==1)) { cifr_sum[0]=cifr_sum[0]-10;cifr_sum[8]=cifr_sum[8]-10;}

    // if (s4et4ik_lev>3) cifr_sum[1]=cifr_sum[1]-10;
    // cout<<ska4ok2<<"-2 "<<ska4ok3<< "-3 "<<ska4ok4<<"-4 "<<ska4ok5<<"-5"<<ska4ok5_prav<<"-5prav"<<endl;
     if (ska4ok2==1) {cifr_sum[2]=cifr_sum[2]+20; cifr_sum[4]=cifr_sum[4]+10;cifr_sum[9]=cifr_sum[9]-10;}
       if (ska4ok4==1) {cifr_sum[4]=cifr_sum[4]+20; cifr_sum[9]=cifr_sum[9]+10;cifr_sum[2]=cifr_sum[2]-15;cifr_sum[1]=cifr_sum[1]-7;}
     if (ska4ok4==0) cifr_sum[4]=cifr_sum[4]-15;
     if (ska4ok5==1) {cifr_sum[5]=cifr_sum[5]+10; cifr_sum[3]=cifr_sum[3]+10;cifr_sum[9]=cifr_sum[9]+10;}
     if (ska4ok==1) cifr_sum[0]=cifr_sum[0]-20;
     if (ska4ok==1) cifr_sum[8]=cifr_sum[8]-20;
    // if (min_lev1>min_lev2) cifr_sum[4]=cifr_sum[4]+10;
     if (ska4ok3==0) {cifr_sum[3]=cifr_sum[3]-10; cifr_sum[7]=cifr_sum[7]-10;}
     if (ska4ok3==1) {cifr_sum[3]=cifr_sum[3]+10; cifr_sum[7]=cifr_sum[7]+10;cifr_sum[1]=cifr_sum[1]+10;cifr_sum[5]=cifr_sum[5]-10;}
     if (ska4ok5==1) {cifr_sum[6]=cifr_sum[6]-20; cifr_sum[8]=cifr_sum[8]-20; cifr_sum[0]=cifr_sum[0]-20;}
    // cout<< ska4ok5<<endl;
     if ( ska4ok5_prav==1 ) {cifr_sum[5]=cifr_sum[5]+20; cifr_sum[6]=cifr_sum[6]+20;
     cifr_sum[4]=cifr_sum[4]-20;
     cifr_sum[1]=cifr_sum[1]-20;
     cifr_sum[7]=cifr_sum[7]-20;
     cifr_sum[2]=cifr_sum[2]-20;}
     if (ska4ok5_prav==0) {cifr_sum[5]=cifr_sum[5]-10;
     cifr_sum[6]=cifr_sum[6]-10;}
        if (ska4ok5==0) cifr_sum[5]=cifr_sum[5]-15;

  //   if (ska4ok5_prav==0) cifr_sum[5]=cifr_sum[5]-10;
    // cout<<min_lev1<<" "<<min_lev2<<endl;
    int max=0,otvet;
    for (int i=0;i<10;i++)
       {
           if (max<cifr_sum[i]) {max=cifr_sum[i];otvet=i;}
      //cout<<i<<" "<<cifr_sum[i]<<";";
       }
     //  cout<<endl;
       if (vsego>0)
       {
       int t=vsego-1;
       while ((t>-1)&&(otvet_got[t][1]>min_lev1))
       {
           otvet_got[t+1][0]=otvet_got[t][0];
           otvet_got[t+1][1]=otvet_got[t][1];
           t--;
       }
       t++;
       otvet_got[t][0]=otvet;
       otvet_got[t][1]=min_lev1;
       vsego++;
       }
       if (vsego==0)
       {
         otvet_got[vsego][0]=otvet;
       otvet_got[vsego][1]=min_lev1;
       vsego++;
       }
      // for (int t=0;t<vsego;t++) cout<<otvet_got[t][1]<<" ";
     }
 }
for (int t=0;t<vsego;t++) cout<<otvet_got[t][0];
 //---------------------------------------------------------------------------
}

