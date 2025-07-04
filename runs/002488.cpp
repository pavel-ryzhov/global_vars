#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;
char mas[10000][10000];
int maxi=0,maxj=0;
int sum_element[10000];
void formirovanie_mini_massivov(int);
void podschet_sootnosheniya(char[5][7],int);
void o_bd();
void ok(int,string,int);
char mc[35];
char v[5][7];
char v2[2][5][7];
char v3[3][5][7];
char o[86][5][7];
int obraz_cifra[86];
int kol_vo_obrazov;
int sootnoshenie[85];
int sum_black;
double procent_black;
int all_sootnoshenia[7];
int nomer_raspoz_obraza[7];
int main()
{
o_bd();
for(int m=0;m<=20;m++)
{
maxi=60;
string stroka[1000];
int index=0;
for(int i=0;i<maxi;i++)
{
cin>>stroka[index];
index++;
}
maxj=0;
for(int i=0;i<maxi;i++)
{
if(stroka[i].length()>maxj)
maxj=stroka[i].length();
}

for(int i=0;i<maxi;i++)
{
for(int j=0;j<maxj;j++)
{
if(j<stroka[i].length())
{
mas[i][j]=stroka[i][j];
}
else
{
mas[i][j]='.';
}
}
}

kol_vo_obrazov=85;
int i=0,j=0;

for(int i=0;i<=maxi-1;i++)
{
for(int j=0;j<=maxj-1;j++)
{
if(mas[i][j]=='#'){mas[i][j]='@';}
if(mas[i][j]=='%'){mas[i][j]='@';}
}
}
double etalon[100000];
double sum_etalon=0;
index=0;
for(i=0;i<=maxi-1;i++)
{
for(j=0;j<=maxj-1;j++)
{
if(mas[i][j] == '@')
{
etalon[index]=sqrt(pow((double)i,2)+pow((double)j,2));
sum_etalon=sum_etalon + etalon[index];
index++;
}
}
}

int temp,y;
int kol_pustih_podriat=0;
for(i=0; i<maxi; i++)
{
temp=0;
for(j=0; j<maxj-1; j++)
if(mas[i][j]=='@')
{temp=1;kol_pustih_podriat=0;}
if(temp==0){kol_pustih_podriat++;}
if((temp==0)&&(kol_pustih_podriat>=3))
{
for(y=i; y<maxi-2; y++)
for(j=0; j<maxj-1; j++)
mas[y][j]=mas[y+1][j];
maxi--;
i--;
}
}
kol_pustih_podriat=0;
for(i=0; i<maxj; i++)
{
temp=0;
for(j=0; j<maxi-1; j++)
if(mas[j][i]=='@')
{temp=1;kol_pustih_podriat=0;}
if(temp==0){kol_pustih_podriat++;}
if((temp==0)&&(kol_pustih_podriat>=3))
{
for(y=i; y<maxj-2; y++)
for(j=0; j<maxi-1; j++)
mas[j][y]=mas[j][y+1];
maxj--;
i--;
}
}

int k=0; 
sum_black=0;
formirovanie_mini_massivov(3);
formirovanie_mini_massivov(2);
formirovanie_mini_massivov(1);
podschet_sootnosheniya(v,1);
podschet_sootnosheniya(v2[0],2);
podschet_sootnosheniya(v2[1],3);
podschet_sootnosheniya(v3[0],4);
podschet_sootnosheniya(v3[1],5);
podschet_sootnosheniya(v3[2],6);

double sr_2=(all_sootnoshenia[2]+all_sootnoshenia[3])/2;
double sr_3=(all_sootnoshenia[4]+all_sootnoshenia[5]+all_sootnoshenia[6])/3;
if((all_sootnoshenia[1]>sr_2)&&(all_sootnoshenia[1]>sr_3))
{
cout<<obraz_cifra[nomer_raspoz_obraza[1]];
}
if((sr_2>all_sootnoshenia[1])&&(sr_2>sr_3))
{
cout<<obraz_cifra[nomer_raspoz_obraza[2]]<<obraz_cifra[nomer_raspoz_obraza[3]];
}
if((sr_3>all_sootnoshenia[1])&&(sr_3>sr_2))
{
cout<<obraz_cifra[nomer_raspoz_obraza[4]]<<obraz_cifra[nomer_raspoz_obraza[5]]<<obraz_cifra[nomer_raspoz_obraza[6]];
}
}
}

void formirovanie_mini_massivov(int kol_vo_simvolov)
{
double shirina=(double)(((maxj)/5)/kol_vo_simvolov)+0.5;
int visota= (int)((maxi)/7);
double koef_sh=double(shirina*5*kol_vo_simvolov)/double(maxj+2);
for(int kol=0;kol<=kol_vo_simvolov-1;kol++)
{
int index=0;
for(int i=0;i<7;i++)
{
for(int j=0;j<5;j++)
{
int kogobolshe=0;
for(int i2=i*visota;i2<(i*visota)+visota;i2++)
for(int j2=(int)(j*shirina+(kol*5*shirina));j2<int((j*shirina)+(kol*5*shirina)+shirina);j2++)
{
if(mas[i2][j2]=='@')
{kogobolshe++;}
else
{kogobolshe--;}
}
if(kogobolshe == int(((shirina*visota)/2)*((-1)*(1-procent_black))))
{
mc[index]='?';
}
if(kogobolshe < int(((shirina*visota)/2)*((-1)*(1-procent_black))))
{
mc[index]='.';
}
if(kogobolshe > int(((shirina*visota)/2)*((-1)*(1-procent_black))))
{
mc[index]='@';
}
index++;
}
}
if(kol_vo_simvolov == 1)
{
v[0][0]=mc[0];v[1][0]=mc[1];v[2][0]=mc[2];v[3][0]=mc[3];v[4][0]=mc[4];
v[0][1]=mc[5];v[1][1]=mc[6];v[2][1]=mc[7];v[3][1]=mc[8];v[4][1]=mc[9];
v[0][2]=mc[10];v[1][2]=mc[11];v[2][2]=mc[12];v[3][2]=mc[13];v[4][2]=mc[14];
v[0][3]=mc[15];v[1][3]=mc[16];v[2][3]=mc[17];v[3][3]=mc[18];v[4][3]=mc[19];
v[0][4]=mc[20];v[1][4]=mc[21];v[2][4]=mc[22];v[3][4]=mc[23];v[4][4]=mc[24];
v[0][5]=mc[25];v[1][5]=mc[26];v[2][5]=mc[27];v[3][5]=mc[28];v[4][5]=mc[29];
v[0][6]=mc[30];v[1][6]=mc[31];v[2][6]=mc[32];v[3][6]=mc[33];v[4][6]=mc[34];
}
if(kol_vo_simvolov == 2)
{
v2[kol][0][0]=mc[0];v2[kol][1][0]=mc[1];v2[kol][2][0]=mc[2];v2[kol][3][0]=mc[3];v2[kol][4][0]=mc[4];
v2[kol][0][1]=mc[5];v2[kol][1][1]=mc[6];v2[kol][2][1]=mc[7];v2[kol][3][1]=mc[8];v2[kol][4][1]=mc[9];
v2[kol][0][2]=mc[10];v2[kol][1][2]=mc[11];v2[kol][2][2]=mc[12];v2[kol][3][2]=mc[13];v2[kol][4][2]=mc[14];
v2[kol][0][3]=mc[15];v2[kol][1][3]=mc[16];v2[kol][2][3]=mc[17];v2[kol][3][3]=mc[18];v2[kol][4][3]=mc[19];
v2[kol][0][4]=mc[20];v2[kol][1][4]=mc[21];v2[kol][2][4]=mc[22];v2[kol][3][4]=mc[23];v2[kol][4][4]=mc[24];
v2[kol][0][5]=mc[25];v2[kol][1][5]=mc[26];v2[kol][2][5]=mc[27];v2[kol][3][5]=mc[28];v2[kol][4][5]=mc[29];
v2[kol][0][6]=mc[30];v2[kol][1][6]=mc[31];v2[kol][2][6]=mc[32];v2[kol][3][6]=mc[33];v2[kol][4][6]=mc[34];
}
if(kol_vo_simvolov == 3)
{
v3[kol][0][0]=mc[0];v3[kol][1][0]=mc[1];v3[kol][2][0]=mc[2];v3[kol][3][0]=mc[3];v3[kol][4][0]=mc[4];
v3[kol][0][1]=mc[5];v3[kol][1][1]=mc[6];v3[kol][2][1]=mc[7];v3[kol][3][1]=mc[8];v3[kol][4][1]=mc[9];
v3[kol][0][2]=mc[10];v3[kol][1][2]=mc[11];v3[kol][2][2]=mc[12];v3[kol][3][2]=mc[13];v3[kol][4][2]=mc[14];
v3[kol][0][3]=mc[15];v3[kol][1][3]=mc[16];v3[kol][2][3]=mc[17];v3[kol][3][3]=mc[18];v3[kol][4][3]=mc[19];
v3[kol][0][4]=mc[20];v3[kol][1][4]=mc[21];v3[kol][2][4]=mc[22];v3[kol][3][4]=mc[23];v3[kol][4][4]=mc[24];
v3[kol][0][5]=mc[25];v3[kol][1][5]=mc[26];v3[kol][2][5]=mc[27];v3[kol][3][5]=mc[28];v3[kol][4][5]=mc[29];
v3[kol][0][6]=mc[30];v3[kol][1][6]=mc[31];v3[kol][2][6]=mc[32];v3[kol][3][6]=mc[33];v3[kol][4][6]=mc[34];
}
}
}
void podschet_sootnosheniya(char v[5][7], int id)
{
for(int k=0;k<=kol_vo_obrazov;k++)
{
sootnoshenie[k]=0;
for(int i=0;i<=6;i++)
{	for(int j=0;j<=4;j++)
{
if(v[j][i] == o[k][j][i])
{
sootnoshenie[k]++;
}
else
{
sootnoshenie[k]--;
}
}
}
}
int max_sootnoshenie=sootnoshenie[0];
for(int k=1;k<=kol_vo_obrazov;k++)
{
if(sootnoshenie[k] > max_sootnoshenie)
{
max_sootnoshenie=sootnoshenie[k];
}
}
for(int k=0;k<=kol_vo_obrazov;k++)
{
if(sootnoshenie[k] == max_sootnoshenie)
{
all_sootnoshenia[id]=sootnoshenie[k];
nomer_raspoz_obraza[id]=k;
}
}
}
void o_bd()
{
ok(0,"....@@@..@@..@@@..@@.@@@@@..@@@....",0);
ok(1,".....@@...@@@..@@@...@@.....@......",1);
ok(2,"......@....@@..@.@.@@@@@..@@@......",2);
ok(3,"......@.....@.@@@.@..@@@@...@......",3);
ok(4,"....@.....@@.@..@@@@.@@@.@.....@...",4);
ok(5,"......@....@@.@@@@...@.@....@......",5);
ok(6,".....@@...@@.@..@@@@.@@..@@.@......",6);
ok(7,".....@@@...@@.@.@....@@.....@......",7);
ok(8,".....@@.@@@@@.@@@@@..@@.....@......",8);
ok(9,"..@..@@.@@@@@.@@@@...@@............",9);
ok(10,"............@@@.@@@@@@@@@...@......",1);
ok(11,"......@.....@@@...@@@@@@@.@@.@.....",2);
ok(12,"......@......@@.@@..@@@@@@@..@.....",3);
ok(13,".....@.....@@...@@....@@@@@@.....@.",4);
ok(14,"........@@@....@@@....@.@@@@.......",5);
ok(15,".@@@@@@...@@...@@@@@@.@@..@@.......",8);
ok(16,".@....@.@....@.@@@@@@..............",0);
ok(17,"@@.....@@.....@@..@@@@@.@@@@@@@....",7);
ok(18,"@@.............@......@@@@@@.......",1);
ok(19,"........@..........@....@@@..@@@...",7);
ok(20,".@......@........@....@@@@@..@@@@@.",3);
ok(21,"........@@.@@...@@....@@@@@..@..@@.",8);
ok(22,"........@......@@@@@@........@@.@@.",1);
ok(23,".@@@@@@@..@..@@@@@@@@.@..@@..?....@",8);
ok(24,".@......@.@?...?@@@@@.....?........",3);
ok(25,".@@@.@.@@@@@@@@...@.@@...@.@.@@@@@.",9);
ok(26,"....@.....@@....@@@...@@@@@@@@@@@@@",4);
ok(27,"....@@..@@@@@@@@@@@@@@@@@..@.@@@@@@",8);
ok(28,"....@@..@@@@@.@@@@@@@@@....@.@@@@@@",0);
ok(29,"......@.@....@@..@...@@.@@.@.@@?@@@",3);
ok(30,"..@.....@.....@@@@@@@.@@@@@@.@@@.@@",1);
ok(31,"@@@@..@@.@...@@..@@@@...@@@...?@.@.",5);
ok(32,"@@@@.@@@.@...@@.@@..@@..@@@@.......",5);

ok(33,"........@......@..@@@.@@@....@@....",7);
ok(34,"..@@....@@@@.@.@...@..@..@@...@@@@@",9);
ok(35,"....@....@@@...@@@@@?..@@@@@.....@.",4);
ok(36,"....?@..@@@@@@.@.@..@@@@@@.@..@.@@.",8);
ok(37,"..........@@...@@@?@...@@@@@.....@.",4);
ok(38,"...@.@.@@@@.@@@@.@..@@@.@@@@....@@.",5);
ok(39,".@@@.@.@@@@.@@@@@@..@@@.@@@@....@..",5);
ok(40,".@...@@@@..@@@@@@@@@@.@@@.@@.......",2);
ok(41,".......@....@@@.@@@..@@@...........",7);
ok(42,".@...@@@...@@@@..@@.@.@@@..@.....@.",2);
ok(43,"@@...@@@..@..@@@@@.@@.@@.@@........",3);
ok(44,".....?..@.@..@.@.?....@.@..?....@@.",5);
ok(45,".@......@...@@.@.@@...@............",7);
ok(46,"..@@?.@.@.?....?.@..@....@@@.......",8);
ok(47,"........@@..@@....@.@...@..@.@@..@@",2);
ok(48,"..@.....@@@.@....@...........@@@@@.",9);
ok(49,"...........@..........@@.@...@@@@@@",4);
ok(50,".?@....@@@....@.@...@@..@..@@..@@@.",5);
ok(51,".?@....@.@....@.@...@@..@@@@@..@@@.",5);
ok(52,".......@@@@@..?@@@@................",1);
ok(53,"..?..@..@@@@@@.?.@....@@@@@@.....@.",8);
ok(54,".....@@.@@@....@.@.@@...@@@......@.",5);
ok(55,".@@@..@.@.@..@.@@@@@.....?.........",3);
ok(56,"........@....?@@@@@@@?@@@@@@.......",1);
ok(57,".@@@@@@@@@@@@@......?@@...@.@...@@@",1);
ok(58,"@..@@@@@.?@...@@...................",7);
ok(59,"...@@...@@@@@.@@@@@@@..@...@...@@@.",6);
ok(60,"...@@@..@@...@..@@@@@..@@@@@...@@@.",5);
ok(61,"..@@@@..@@@@@.@@@@@@@......@.@@@@@.",0);
ok(62,"..?..?@.@@@@@@.@.@@.@.@@@@@@.@@.@@.",8);
ok(63,"....@@...@@@@@.@@?.@@...@@@@...@@@@",6);
ok(64,"....@@....@@@..@@.@@.??@@@@@..@@@@@",4);
ok(65,"...@....?@@...@@@@@@...?@@.....@...",4);
ok(66,"..@@...@@@@?....@@@@....@......@@..",4);
ok(67,".@@@@@.@@.@.@..@@@@@...@.@.........",8);
ok(68,"..@@@....@@@@..@@@@@@.@@@@@@..@@@@@",9);
ok(69,"..@@@...@@@@@.@@@@@@@.@@@@@@..@@@@@",6);
ok(70,"...@@@..?@@@@.@@@@@@@?@@@@@@..@@@@@",6);
ok(71,"........@?...@.@@@@@@.?@@@?@.....@@",2);
ok(72,"...?@@@..@@@@@.@@@@@@.@@??@@.@....@",4);
ok(73,".@@@@@@.@@@@@?.@@..................",7);
ok(74,".@@.....@@@....@..@..@@.@@.?@@@@@@@",9);
ok(75,".....@..@@@.@@.@@@..@.@.@@@@.@.@@@.",5);
ok(76,"..@.....@@@...@@..@..@@.@?..@@@@@@@",9);
ok(77,"....@@..@@@..@@@@@..@@..@@@@.@@@@@@",8);
ok(78,".....@...@...@@@@...@@@....@...@@@.",5);
ok(79,".@@.@@..@@@..@@@@@..@@..@@@@.@@@@@.",8);
ok(80,"................@@@@.....@.........",8);
ok(81,"................@@@@....@..........",9);
ok(82,"................@@@@...............",2);
ok(83,".....@..@@.@@@?@@@@@.@@@.@..@@....@",8);
ok(84,".....@@@@@.@..@.@@...@....@@....?@.",5);
ok(85,".@.@@@..@@..@@@@....@@@...@?.......",2);
}
void ok(int n,string s,int m)
{
o[n][0][0]=s[0];o[n][1][0]=s[7];o[n][2][0]=s[14];o[n][3][0]=s[21];o[n][4][0]=s[28];
o[n][0][1]=s[1];o[n][1][1]=s[8];o[n][2][1]=s[15];o[n][3][1]=s[22];o[n][4][1]=s[29];
o[n][0][2]=s[2];o[n][1][2]=s[9];o[n][2][2]=s[16];o[n][3][2]=s[23];o[n][4][2]=s[30];
o[n][0][3]=s[3];o[n][1][3]=s[10];o[n][2][3]=s[17];o[n][3][3]=s[24];o[n][4][3]=s[31];
o[n][0][4]=s[4];o[n][1][4]=s[11];o[n][2][4]=s[18];o[n][3][4]=s[25];o[n][4][4]=s[32];
o[n][0][5]=s[5];o[n][1][5]=s[12];o[n][2][5]=s[19];o[n][3][5]=s[26];o[n][4][5]=s[33];
o[n][0][6]=s[6];o[n][1][6]=s[13];o[n][2][6]=s[20];o[n][3][6]=s[27];o[n][4][6]=s[34];
obraz_cifra[n]=m;
}
