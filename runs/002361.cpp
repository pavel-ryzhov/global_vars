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
void obrazi_bd();
char mini_copy[35];
char vhod[5][7];
char vhod_2[2][5][7];
char vhod_3[3][5][7];
char obrazi[86][5][7];
int obraz_cifra[86];
int kol_vo_obrazov;
int sootnoshenie[85];
int sum_black;
double procent_black;
int all_sootnoshenia[7];
int nomer_raspoz_obraza[7];
int main()
{
obrazi_bd();
for(int m=0;m<=20;m++)
{
maxi = 60;
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
			maxj = stroka[i].length();
		}

for(int i=0;i<maxi;i++)
	{
		for(int j=0;j<maxj;j++)
			{
			if(j<stroka[i].length())
				{
				mas[i][j] = stroka[i][j];
				}
				else
				{
				mas[i][j] = '.';
				}
			}
	}

//ifstream f("018.txt");
kol_vo_obrazov = 85;
int i=0,j=0;
//Caa?ocea ecia?a?aiey ec oaeea!
/*
while (true)
	{
	string v;
	f >> v;
	if (!f.eof())
		{
		cout << v << endl;
		for(j=0;j<=v.length();j++)
			{
			mas[i][j] = v[j];
			if(j>maxj)maxj=j;
			}	
		if(i>maxi)maxi=i;
		i++;
		}
		else
		{
		break;
		}
	}
*/
//maxi++;

for(int i=0;i<=maxi-1;i++)
{
	for(int j=0;j<=maxj-1;j++)
	{
		if(mas[i][j]=='#'){mas[i][j]='@';}
		if(mas[i][j]=='%'){mas[i][j]='@';}
	}
}
double etalon[100000];
double sum_etalon = 0;
index = 0;
for(i=0;i<=maxi-1;i++)
{
	for(j=0;j<=maxj-1;j++)
	{
		if(mas[i][j] == '@')
			{
			etalon[index] = sqrt(pow((double)i,2)+pow((double)j,2));
			sum_etalon = sum_etalon + etalon[index];
			index++;
			}
		}
}

int temp,y;
int kol_pustih_podriat = 0;
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
cout<<endl;
kol_pustih_podriat = 0;
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


int k = 0; 
sum_black = 0;

formirovanie_mini_massivov(3);
formirovanie_mini_massivov(2);
formirovanie_mini_massivov(1);
podschet_sootnosheniya(vhod,1);
podschet_sootnosheniya(vhod_2[0],2);
podschet_sootnosheniya(vhod_2[1],3);
podschet_sootnosheniya(vhod_3[0],4);
podschet_sootnosheniya(vhod_3[1],5);
podschet_sootnosheniya(vhod_3[2],6);

double sr_2 = (all_sootnoshenia[2]+all_sootnoshenia[3])/2;
double sr_3 = (all_sootnoshenia[4]+all_sootnoshenia[5]+all_sootnoshenia[6])/3;
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
int test;
cin >> test;
}

void formirovanie_mini_massivov(int kol_vo_simvolov)
	{
		double shirina = (double)(((maxj)/5)/kol_vo_simvolov)+0.5;
		int visota =  (int)((maxi)/7);
		double koef_sh = double(shirina*5*kol_vo_simvolov)/double(maxj+2);
		for(int kol=0;kol<=kol_vo_simvolov-1;kol++)
		{
		int index = 0;
		for(int i=0;i<7;i++)
			{
				for(int j=0;j<5;j++)
				{
					int kogobolshe = 0;
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
						mini_copy[index] = '?';
						}
					if(kogobolshe < int(((shirina*visota)/2)*((-1)*(1-procent_black))))
						{
						mini_copy[index] = '.';
						}
					if(kogobolshe > int(((shirina*visota)/2)*((-1)*(1-procent_black))))
						{
						mini_copy[index] = '@';
						}
					index++;
				}
			}
		if(kol_vo_simvolov == 1)
			{
			vhod[0][0]=mini_copy[0];vhod[1][0]=mini_copy[1];vhod[2][0]=mini_copy[2];vhod[3][0]=mini_copy[3];vhod[4][0]=mini_copy[4];
			vhod[0][1]=mini_copy[5];vhod[1][1]=mini_copy[6];vhod[2][1]=mini_copy[7];vhod[3][1]=mini_copy[8];vhod[4][1]=mini_copy[9];
			vhod[0][2]=mini_copy[10];vhod[1][2]=mini_copy[11];vhod[2][2]=mini_copy[12];vhod[3][2]=mini_copy[13];vhod[4][2]=mini_copy[14];
			vhod[0][3]=mini_copy[15];vhod[1][3]=mini_copy[16];vhod[2][3]=mini_copy[17];vhod[3][3]=mini_copy[18];vhod[4][3]=mini_copy[19];
			vhod[0][4]=mini_copy[20];vhod[1][4]=mini_copy[21];vhod[2][4]=mini_copy[22];vhod[3][4]=mini_copy[23];vhod[4][4]=mini_copy[24];
			vhod[0][5]=mini_copy[25];vhod[1][5]=mini_copy[26];vhod[2][5]=mini_copy[27];vhod[3][5]=mini_copy[28];vhod[4][5]=mini_copy[29];
			vhod[0][6]=mini_copy[30];vhod[1][6]=mini_copy[31];vhod[2][6]=mini_copy[32];vhod[3][6]=mini_copy[33];vhod[4][6]=mini_copy[34];
			}
		if(kol_vo_simvolov == 2)
			{
			vhod_2[kol][0][0]=mini_copy[0];vhod_2[kol][1][0]=mini_copy[1];vhod_2[kol][2][0]=mini_copy[2];vhod_2[kol][3][0]=mini_copy[3];vhod_2[kol][4][0]=mini_copy[4];
			vhod_2[kol][0][1]=mini_copy[5];vhod_2[kol][1][1]=mini_copy[6];vhod_2[kol][2][1]=mini_copy[7];vhod_2[kol][3][1]=mini_copy[8];vhod_2[kol][4][1]=mini_copy[9];
			vhod_2[kol][0][2]=mini_copy[10];vhod_2[kol][1][2]=mini_copy[11];vhod_2[kol][2][2]=mini_copy[12];vhod_2[kol][3][2]=mini_copy[13];vhod_2[kol][4][2]=mini_copy[14];
			vhod_2[kol][0][3]=mini_copy[15];vhod_2[kol][1][3]=mini_copy[16];vhod_2[kol][2][3]=mini_copy[17];vhod_2[kol][3][3]=mini_copy[18];vhod_2[kol][4][3]=mini_copy[19];
			vhod_2[kol][0][4]=mini_copy[20];vhod_2[kol][1][4]=mini_copy[21];vhod_2[kol][2][4]=mini_copy[22];vhod_2[kol][3][4]=mini_copy[23];vhod_2[kol][4][4]=mini_copy[24];
			vhod_2[kol][0][5]=mini_copy[25];vhod_2[kol][1][5]=mini_copy[26];vhod_2[kol][2][5]=mini_copy[27];vhod_2[kol][3][5]=mini_copy[28];vhod_2[kol][4][5]=mini_copy[29];
			vhod_2[kol][0][6]=mini_copy[30];vhod_2[kol][1][6]=mini_copy[31];vhod_2[kol][2][6]=mini_copy[32];vhod_2[kol][3][6]=mini_copy[33];vhod_2[kol][4][6]=mini_copy[34];
			}
		if(kol_vo_simvolov == 3)
			{
			vhod_3[kol][0][0]=mini_copy[0];vhod_3[kol][1][0]=mini_copy[1];vhod_3[kol][2][0]=mini_copy[2];vhod_3[kol][3][0]=mini_copy[3];vhod_3[kol][4][0]=mini_copy[4];
			vhod_3[kol][0][1]=mini_copy[5];vhod_3[kol][1][1]=mini_copy[6];vhod_3[kol][2][1]=mini_copy[7];vhod_3[kol][3][1]=mini_copy[8];vhod_3[kol][4][1]=mini_copy[9];
			vhod_3[kol][0][2]=mini_copy[10];vhod_3[kol][1][2]=mini_copy[11];vhod_3[kol][2][2]=mini_copy[12];vhod_3[kol][3][2]=mini_copy[13];vhod_3[kol][4][2]=mini_copy[14];
			vhod_3[kol][0][3]=mini_copy[15];vhod_3[kol][1][3]=mini_copy[16];vhod_3[kol][2][3]=mini_copy[17];vhod_3[kol][3][3]=mini_copy[18];vhod_3[kol][4][3]=mini_copy[19];
			vhod_3[kol][0][4]=mini_copy[20];vhod_3[kol][1][4]=mini_copy[21];vhod_3[kol][2][4]=mini_copy[22];vhod_3[kol][3][4]=mini_copy[23];vhod_3[kol][4][4]=mini_copy[24];
			vhod_3[kol][0][5]=mini_copy[25];vhod_3[kol][1][5]=mini_copy[26];vhod_3[kol][2][5]=mini_copy[27];vhod_3[kol][3][5]=mini_copy[28];vhod_3[kol][4][5]=mini_copy[29];
			vhod_3[kol][0][6]=mini_copy[30];vhod_3[kol][1][6]=mini_copy[31];vhod_3[kol][2][6]=mini_copy[32];vhod_3[kol][3][6]=mini_copy[33];vhod_3[kol][4][6]=mini_copy[34];
			}
		}
	}
void podschet_sootnosheniya(char vhod[5][7], int id)
	{
		for(int k=0;k<=kol_vo_obrazov;k++)
		{
			sootnoshenie[k] = 0;
			for(int i=0;i<=6;i++)
			{	for(int j=0;j<=4;j++)
				{
					if(vhod[j][i] == obrazi[k][j][i])
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
		int max_sootnoshenie = sootnoshenie[0];
		for(int k=1;k<=kol_vo_obrazov;k++)
			{
			if(sootnoshenie[k] > max_sootnoshenie)
				{
				max_sootnoshenie = sootnoshenie[k];
				}
			}

		for(int k=0;k<=kol_vo_obrazov;k++)
			{
			if(sootnoshenie[k] == max_sootnoshenie)
				{
					all_sootnoshenia[id] = sootnoshenie[k];
					nomer_raspoz_obraza[id] = k;
				}
			}
	}
void obrazi_bd()
{
obrazi[0][0][0]='.';obrazi[0][1][0] ='.';obrazi[0][2][0]='@';obrazi[0][3][0]='@';obrazi[0][4][0]='@';
obrazi[0][0][1]='.';obrazi[0][1][1] ='.';obrazi[0][2][1]='@';obrazi[0][3][1]='@';obrazi[0][4][1]='@';
obrazi[0][0][2]='.';obrazi[0][1][2] ='@';obrazi[0][2][2]='.';obrazi[0][3][2]='@';obrazi[0][4][2]='@';
obrazi[0][0][3]='.';obrazi[0][1][3] ='@';obrazi[0][2][3]='.';obrazi[0][3][3]='@';obrazi[0][4][3]='.';
obrazi[0][0][4]='@';obrazi[0][1][4] ='.';obrazi[0][2][4]='@';obrazi[0][3][4]='@';obrazi[0][4][4]='.';
obrazi[0][0][5]='@';obrazi[0][1][5] ='.';obrazi[0][2][5]='@';obrazi[0][3][5]='.';obrazi[0][4][5]='.';
obrazi[0][0][6]='@';obrazi[0][1][6] ='@';obrazi[0][2][6]='.';obrazi[0][3][6]='.';obrazi[0][4][6]='.';
obraz_cifra[0] = 0;

obrazi[1][0][0]='.';obrazi[1][1][0] ='.';obrazi[1][2][0]='.';obrazi[1][3][0]='@';obrazi[1][4][0]='@';
obrazi[1][0][1]='.';obrazi[1][1][1] ='.';obrazi[1][2][1]='@';obrazi[1][3][1]='@';obrazi[1][4][1]='.';
obrazi[1][0][2]='.';obrazi[1][1][2] ='.';obrazi[1][2][2]='@';obrazi[1][3][2]='.';obrazi[1][4][2]='.';
obrazi[1][0][3]='.';obrazi[1][1][3] ='@';obrazi[1][2][3]='@';obrazi[1][3][3]='.';obrazi[1][4][3]='.';
obrazi[1][0][4]='.';obrazi[1][1][4] ='@';obrazi[1][2][4]='.';obrazi[1][3][4]='.';obrazi[1][4][4]='.';
obrazi[1][0][5]='@';obrazi[1][1][5] ='@';obrazi[1][2][5]='.';obrazi[1][3][5]='.';obrazi[1][4][5]='.';
obrazi[1][0][6]='@';obrazi[1][1][6] ='.';obrazi[1][2][6]='.';obrazi[1][3][6]='.';obrazi[1][4][6]='.';
obraz_cifra[1] = 1;

obrazi[2][0][0]='.';obrazi[2][1][0] ='.';obrazi[2][2][0]='.';obrazi[2][3][0]='@';obrazi[2][4][0]='@';
obrazi[2][0][1]='.';obrazi[2][1][1] ='.';obrazi[2][2][1]='@';obrazi[2][3][1]='@';obrazi[2][4][1]='.';
obrazi[2][0][2]='.';obrazi[2][1][2] ='.';obrazi[2][2][2]='.';obrazi[2][3][2]='@';obrazi[2][4][2]='.';
obrazi[2][0][3]='.';obrazi[2][1][3] ='.';obrazi[2][2][3]='@';obrazi[2][3][3]='.';obrazi[2][4][3]='.';
obrazi[2][0][4]='.';obrazi[2][1][4] ='@';obrazi[2][2][4]='.';obrazi[2][3][4]='.';obrazi[2][4][4]='.';
obrazi[2][0][5]='.';obrazi[2][1][5] ='@';obrazi[2][2][5]='@';obrazi[2][3][5]='@';obrazi[2][4][5]='.';
obrazi[2][0][6]='@';obrazi[2][1][6] ='.';obrazi[2][2][6]='@';obrazi[2][3][6]='@';obrazi[2][4][6]='.';
obraz_cifra[2] = 2;

obrazi[3][0][0]='.';obrazi[3][1][0] ='.';obrazi[3][2][0]='@';obrazi[3][3][0]='@';obrazi[3][4][0]='@';
obrazi[3][0][1]='.';obrazi[3][1][1] ='.';obrazi[3][2][1]='@';obrazi[3][3][1]='@';obrazi[3][4][1]='.';
obrazi[3][0][2]='.';obrazi[3][1][2] ='.';obrazi[3][2][2]='@';obrazi[3][3][2]='@';obrazi[3][4][2]='.';
obrazi[3][0][3]='.';obrazi[3][1][3] ='.';obrazi[3][2][3]='.';obrazi[3][3][3]='@';obrazi[3][4][3]='.';
obrazi[3][0][4]='.';obrazi[3][1][4] ='.';obrazi[3][2][4]='@';obrazi[3][3][4]='.';obrazi[3][4][4]='.';
obrazi[3][0][5]='.';obrazi[3][1][5] ='@';obrazi[3][2][5]='.';obrazi[3][3][5]='.';obrazi[3][4][5]='.';
obrazi[3][0][6]='@';obrazi[3][1][6] ='.';obrazi[3][2][6]='.';obrazi[3][3][6]='.';obrazi[3][4][6]='.';
obraz_cifra[3] = 3;

obrazi[4][0][0]='.';obrazi[4][1][0] ='.';obrazi[4][2][0]='.';obrazi[4][3][0]='@';obrazi[4][4][0]='.';
obrazi[4][0][1]='.';obrazi[4][1][1] ='.';obrazi[4][2][1]='.';obrazi[4][3][1]='@';obrazi[4][4][1]='.';
obrazi[4][0][2]='.';obrazi[4][1][2] ='.';obrazi[4][2][2]='@';obrazi[4][3][2]='@';obrazi[4][4][2]='.';
obrazi[4][0][3]='.';obrazi[4][1][3] ='@';obrazi[4][2][3]='@';obrazi[4][3][3]='.';obrazi[4][4][3]='@';
obrazi[4][0][4]='@';obrazi[4][1][4] ='@';obrazi[4][2][4]='@';obrazi[4][3][4]='@';obrazi[4][4][4]='.';
obrazi[4][0][5]='.';obrazi[4][1][5] ='.';obrazi[4][2][5]='@';obrazi[4][3][5]='.';obrazi[4][4][5]='.';
obrazi[4][0][6]='.';obrazi[4][1][6] ='@';obrazi[4][2][6]='.';obrazi[4][3][6]='.';obrazi[4][4][6]='.';
obraz_cifra[4] = 4;

obrazi[5][0][0]='.';obrazi[5][1][0] ='.';obrazi[5][2][0]='@';obrazi[5][3][0]='@';obrazi[5][4][0]='@';
obrazi[5][0][1]='.';obrazi[5][1][1] ='.';obrazi[5][2][1]='@';obrazi[5][3][1]='.';obrazi[5][4][1]='.';
obrazi[5][0][2]='.';obrazi[5][1][2] ='.';obrazi[5][2][2]='@';obrazi[5][3][2]='@';obrazi[5][4][2]='.';
obrazi[5][0][3]='.';obrazi[5][1][3] ='.';obrazi[5][2][3]='@';obrazi[5][3][3]='.';obrazi[5][4][3]='.';
obrazi[5][0][4]='.';obrazi[5][1][4] ='@';obrazi[5][2][4]='.';obrazi[5][3][4]='.';obrazi[5][4][4]='.';
obrazi[5][0][5]='.';obrazi[5][1][5] ='@';obrazi[5][2][5]='.';obrazi[5][3][5]='.';obrazi[5][4][5]='.';
obrazi[5][0][6]='@';obrazi[5][1][6] ='.';obrazi[5][2][6]='.';obrazi[5][3][6]='.';obrazi[5][4][6]='.';
obraz_cifra[5] = 5;

obrazi[6][0][0]='.';obrazi[6][1][0] ='.';obrazi[6][2][0]='.';obrazi[6][3][0]='@';obrazi[6][4][0]='@';
obrazi[6][0][1]='.';obrazi[6][1][1] ='.';obrazi[6][2][1]='.';obrazi[6][3][1]='@';obrazi[6][4][1]='.';
obrazi[6][0][2]='.';obrazi[6][1][2] ='.';obrazi[6][2][2]='@';obrazi[6][3][2]='.';obrazi[6][4][2]='.';
obrazi[6][0][3]='.';obrazi[6][1][3] ='@';obrazi[6][2][3]='@';obrazi[6][3][3]='.';obrazi[6][4][3]='.';
obrazi[6][0][4]='.';obrazi[6][1][4] ='@';obrazi[6][2][4]='@';obrazi[6][3][4]='@';obrazi[6][4][4]='.';
obrazi[6][0][5]='@';obrazi[6][1][5] ='.';obrazi[6][2][5]='@';obrazi[6][3][5]='@';obrazi[6][4][5]='.';
obrazi[6][0][6]='@';obrazi[6][1][6] ='@';obrazi[6][2][6]='.';obrazi[6][3][6]='.';obrazi[6][4][6]='.';
obraz_cifra[6] = 6;

obrazi[7][0][0]='.';obrazi[7][1][0] ='@';obrazi[7][2][0]='@';obrazi[7][3][0]='@';obrazi[7][4][0]='@';
obrazi[7][0][1]='.';obrazi[7][1][1] ='.';obrazi[7][2][1]='.';obrazi[7][3][1]='@';obrazi[7][4][1]='.';
obrazi[7][0][2]='.';obrazi[7][1][2] ='.';obrazi[7][2][2]='@';obrazi[7][3][2]='.';obrazi[7][4][2]='.';
obrazi[7][0][3]='.';obrazi[7][1][3] ='.';obrazi[7][2][3]='.';obrazi[7][3][3]='.';obrazi[7][4][3]='.';
obrazi[7][0][4]='.';obrazi[7][1][4] ='@';obrazi[7][2][4]='.';obrazi[7][3][4]='.';obrazi[7][4][4]='.';
obrazi[7][0][5]='@';obrazi[7][1][5] ='@';obrazi[7][2][5]='.';obrazi[7][3][5]='.';obrazi[7][4][5]='.';
obrazi[7][0][6]='@';obrazi[7][1][6] ='.';obrazi[7][2][6]='.';obrazi[7][3][6]='.';obrazi[7][4][6]='.';
obraz_cifra[7] = 7;

obrazi[8][0][0]='.';obrazi[8][1][0] ='.';obrazi[8][2][0]='@';obrazi[8][3][0]='@';obrazi[8][4][0]='@';
obrazi[8][0][1]='.';obrazi[8][1][1] ='@';obrazi[8][2][1]='@';obrazi[8][3][1]='@';obrazi[8][4][1]='.';
obrazi[8][0][2]='.';obrazi[8][1][2] ='@';obrazi[8][2][2]='@';obrazi[8][3][2]='.';obrazi[8][4][2]='.';
obrazi[8][0][3]='.';obrazi[8][1][3] ='@';obrazi[8][2][3]='@';obrazi[8][3][3]='.';obrazi[8][4][3]='.';
obrazi[8][0][4]='.';obrazi[8][1][4] ='@';obrazi[8][2][4]='@';obrazi[8][3][4]='.';obrazi[8][4][4]='.';
obrazi[8][0][5]='@';obrazi[8][1][5] ='@';obrazi[8][2][5]='.';obrazi[8][3][5]='.';obrazi[8][4][5]='.';
obrazi[8][0][6]='@';obrazi[8][1][6] ='.';obrazi[8][2][6]='.';obrazi[8][3][6]='.';obrazi[8][4][6]='.';
obraz_cifra[8] = 8;

obrazi[9][0][0]='.';obrazi[9][1][0] ='.';obrazi[9][2][0]='@';obrazi[9][3][0]='@';obrazi[9][4][0]='.';
obrazi[9][0][1]='.';obrazi[9][1][1] ='@';obrazi[9][2][1]='@';obrazi[9][3][1]='@';obrazi[9][4][1]='.';
obrazi[9][0][2]='@';obrazi[9][1][2] ='@';obrazi[9][2][2]='@';obrazi[9][3][2]='.';obrazi[9][4][2]='.';
obrazi[9][0][3]='.';obrazi[9][1][3] ='@';obrazi[9][2][3]='@';obrazi[9][3][3]='.';obrazi[9][4][3]='.';
obrazi[9][0][4]='.';obrazi[9][1][4] ='@';obrazi[9][2][4]='.';obrazi[9][3][4]='.';obrazi[9][4][4]='.';
obrazi[9][0][5]='@';obrazi[9][1][5] ='@';obrazi[9][2][5]='.';obrazi[9][3][5]='.';obrazi[9][4][5]='.';
obrazi[9][0][6]='@';obrazi[9][1][6] ='.';obrazi[9][2][6]='.';obrazi[9][3][6]='.';obrazi[9][4][6]='.';
obraz_cifra[9] = 9;

obrazi[10][0][0]='.';obrazi[10][1][0] ='.';obrazi[10][2][0]='@';obrazi[10][3][0]='@';obrazi[10][4][0]='@';
obrazi[10][0][1]='.';obrazi[10][1][1] ='.';obrazi[10][2][1]='.';obrazi[10][3][1]='@';obrazi[10][4][1]='.';
obrazi[10][0][2]='.';obrazi[10][1][2] ='.';obrazi[10][2][2]='@';obrazi[10][3][2]='@';obrazi[10][4][2]='.';
obrazi[10][0][3]='.';obrazi[10][1][3] ='.';obrazi[10][2][3]='@';obrazi[10][3][3]='@';obrazi[10][4][3]='.';
obrazi[10][0][4]='.';obrazi[10][1][4] ='.';obrazi[10][2][4]='@';obrazi[10][3][4]='.';obrazi[10][4][4]='.';
obrazi[10][0][5]='.';obrazi[10][1][5] ='@';obrazi[10][2][5]='@';obrazi[10][3][5]='.';obrazi[10][4][5]='.';
obrazi[10][0][6]='.';obrazi[10][1][6] ='@';obrazi[10][2][6]='@';obrazi[10][3][6]='.';obrazi[10][4][6]='.';
obraz_cifra[10] = 1;

obrazi[11][0][0]='.';obrazi[11][1][0] ='.';obrazi[11][2][0]='@';obrazi[11][3][0]='@';obrazi[11][4][0]='.';
obrazi[11][0][1]='.';obrazi[11][1][1] ='.';obrazi[11][2][1]='.';obrazi[11][3][1]='@';obrazi[11][4][1]='@';
obrazi[11][0][2]='.';obrazi[11][1][2] ='.';obrazi[11][2][2]='.';obrazi[11][3][2]='@';obrazi[11][4][2]='.';
obrazi[11][0][3]='.';obrazi[11][1][3] ='.';obrazi[11][2][3]='.';obrazi[11][3][3]='@';obrazi[11][4][3]='.';
obrazi[11][0][4]='.';obrazi[11][1][4] ='.';obrazi[11][2][4]='@';obrazi[11][3][4]='.';obrazi[11][4][4]='.';
obrazi[11][0][5]='.';obrazi[11][1][5] ='@';obrazi[11][2][5]='@';obrazi[11][3][5]='@';obrazi[11][4][5]='.';
obrazi[11][0][6]='@';obrazi[11][1][6] ='@';obrazi[11][2][6]='@';obrazi[11][3][6]='@';obrazi[11][4][6]='.';
obraz_cifra[11] = 2;

obrazi[12][0][0]='.';obrazi[12][1][0] ='.';obrazi[12][2][0]='@';obrazi[12][3][0]='@';obrazi[12][4][0]='.';
obrazi[12][0][1]='.';obrazi[12][1][1] ='.';obrazi[12][2][1]='.';obrazi[12][3][1]='@';obrazi[12][4][1]='@';
obrazi[12][0][2]='.';obrazi[12][1][2] ='.';obrazi[12][2][2]='@';obrazi[12][3][2]='@';obrazi[12][4][2]='.';
obrazi[12][0][3]='.';obrazi[12][1][3] ='.';obrazi[12][2][3]='@';obrazi[12][3][3]='@';obrazi[12][4][3]='.';
obrazi[12][0][4]='.';obrazi[12][1][4] ='.';obrazi[12][2][4]='.';obrazi[12][3][4]='@';obrazi[12][4][4]='.';
obrazi[12][0][5]='.';obrazi[12][1][5] ='.';obrazi[12][2][5]='.';obrazi[12][3][5]='@';obrazi[12][4][5]='.';
obrazi[12][0][6]='@';obrazi[12][1][6] ='@';obrazi[12][2][6]='@';obrazi[12][3][6]='.';obrazi[12][4][6]='.';
obraz_cifra[12] = 3;
obrazi[13][0][0]='.';obrazi[13][1][0] ='.';obrazi[13][2][0]='@';obrazi[13][3][0]='@';obrazi[13][4][0]='@';
obrazi[13][0][1]='.';obrazi[13][1][1] ='@';obrazi[13][2][1]='.';obrazi[13][3][1]='.';obrazi[13][4][1]='.';
obrazi[13][0][2]='.';obrazi[13][1][2] ='@';obrazi[13][2][2]='@';obrazi[13][3][2]='.';obrazi[13][4][2]='.';
obrazi[13][0][3]='.';obrazi[13][1][3] ='.';obrazi[13][2][3]='@';obrazi[13][3][3]='@';obrazi[13][4][3]='.';
obrazi[13][0][4]='.';obrazi[13][1][4] ='.';obrazi[13][2][4]='.';obrazi[13][3][4]='@';obrazi[13][4][4]='.';
obrazi[13][0][5]='.';obrazi[13][1][5] ='.';obrazi[13][2][5]='.';obrazi[13][3][5]='@';obrazi[13][4][5]='.';
obrazi[13][0][6]='@';obrazi[13][1][6] ='@';obrazi[13][2][6]='.';obrazi[13][3][6]='.';obrazi[13][4][6]='.';
obraz_cifra[13] = 5;
obrazi[14][0][0]='.';obrazi[14][1][0] ='.';obrazi[14][2][0]='@';obrazi[14][3][0]='@';obrazi[14][4][0]='.';
obrazi[14][0][1]='.';obrazi[14][1][1] ='@';obrazi[14][2][1]='@';obrazi[14][3][1]='.';obrazi[14][4][1]='.';
obrazi[14][0][2]='.';obrazi[14][1][2] ='@';obrazi[14][2][2]='@';obrazi[14][3][2]='@';obrazi[14][4][2]='.';
obrazi[14][0][3]='@';obrazi[14][1][3] ='@';obrazi[14][2][3]='.';obrazi[14][3][3]='@';obrazi[14][4][3]='.';
obrazi[14][0][4]='@';obrazi[14][1][4] ='.';obrazi[14][2][4]='.';obrazi[14][3][4]='@';obrazi[14][4][4]='.';
obrazi[14][0][5]='@';obrazi[14][1][5] ='.';obrazi[14][2][5]='@';obrazi[14][3][5]='@';obrazi[14][4][5]='.';
obrazi[14][0][6]='.';obrazi[14][1][6] ='@';obrazi[14][2][6]='@';obrazi[14][3][6]='.';obrazi[14][4][6]='.';
obraz_cifra[14] = 6;

obrazi[15][0][0]='.';obrazi[15][1][0] ='@';obrazi[15][2][0]='@';obrazi[15][3][0]='@';obrazi[15][4][0]='@';
obrazi[15][0][1]='.';obrazi[15][1][1] ='@';obrazi[15][2][1]='.';obrazi[15][3][1]='@';obrazi[15][4][1]='@';
obrazi[15][0][2]='.';obrazi[15][1][2] ='@';obrazi[15][2][2]='@';obrazi[15][3][2]='@';obrazi[15][4][2]='.';
obrazi[15][0][3]='.';obrazi[15][1][3] ='@';obrazi[15][2][3]='@';obrazi[15][3][3]='@';obrazi[15][4][3]='.';
obrazi[15][0][4]='@';obrazi[15][1][4] ='.';obrazi[15][2][4]='.';obrazi[15][3][4]='@';obrazi[15][4][4]='.';
obrazi[15][0][5]='@';obrazi[15][1][5] ='.';obrazi[15][2][5]='.';obrazi[15][3][5]='@';obrazi[15][4][5]='.';
obrazi[15][0][6]='@';obrazi[15][1][6] ='@';obrazi[15][2][6]='@';obrazi[15][3][6]='.';obrazi[15][4][6]='.';
obraz_cifra[15] = 8;

obrazi[16][0][0]='.';obrazi[16][1][0] ='.';obrazi[16][2][0]='.';obrazi[16][3][0]='.';obrazi[16][4][0]='.';
obrazi[16][0][1]='@';obrazi[16][1][1] ='@';obrazi[16][2][1]='@';obrazi[16][3][1]='.';obrazi[16][4][1]='.';
obrazi[16][0][2]='.';obrazi[16][1][2] ='.';obrazi[16][2][2]='@';obrazi[16][3][2]='.';obrazi[16][4][2]='.';
obrazi[16][0][3]='.';obrazi[16][1][3] ='.';obrazi[16][2][3]='@';obrazi[16][3][3]='.';obrazi[16][4][3]='.';
obrazi[16][0][4]='.';obrazi[16][1][4] ='.';obrazi[16][2][4]='@';obrazi[16][3][4]='.';obrazi[16][4][4]='.';
obrazi[16][0][5]='.';obrazi[16][1][5] ='.';obrazi[16][2][5]='@';obrazi[16][3][5]='.';obrazi[16][4][5]='.';
obrazi[16][0][6]='@';obrazi[16][1][6] ='@';obrazi[16][2][6]='@';obrazi[16][3][6]='.';obrazi[16][4][6]='.';
obraz_cifra[16] = 0;

obrazi[17][0][0]='@';obrazi[17][1][0] ='@';obrazi[17][2][0]='@';obrazi[17][3][0]='@';obrazi[17][4][0]='@';
obrazi[17][0][1]='@';obrazi[17][1][1] ='@';obrazi[17][2][1]='@';obrazi[17][3][1]='@';obrazi[17][4][1]='@';
obrazi[17][0][2]='.';obrazi[17][1][2] ='.';obrazi[17][2][2]='.';obrazi[17][3][2]='.';obrazi[17][4][2]='@';
obrazi[17][0][3]='.';obrazi[17][1][3] ='.';obrazi[17][2][3]='.';obrazi[17][3][3]='@';obrazi[17][4][3]='.';
obrazi[17][0][4]='.';obrazi[17][1][4] ='.';obrazi[17][2][4]='@';obrazi[17][3][4]='@';obrazi[17][4][4]='.';
obrazi[17][0][5]='.';obrazi[17][1][5] ='.';obrazi[17][2][5]='@';obrazi[17][3][5]='@';obrazi[17][4][5]='.';
obrazi[17][0][6]='.';obrazi[17][1][6] ='.';obrazi[17][2][6]='@';obrazi[17][3][6]='@';obrazi[17][4][6]='.';
obraz_cifra[17] = 7;

obrazi[18][0][0]='@';obrazi[18][1][0] ='.';obrazi[18][2][0]='.';obrazi[18][3][0]='.';obrazi[18][4][0]='.';
obrazi[18][0][1]='@';obrazi[18][1][1] ='.';obrazi[18][2][1]='@';obrazi[18][3][1]='@';obrazi[18][4][1]='.';
obrazi[18][0][2]='.';obrazi[18][1][2] ='.';obrazi[18][2][2]='.';obrazi[18][3][2]='@';obrazi[18][4][2]='.';
obrazi[18][0][3]='.';obrazi[18][1][3] ='.';obrazi[18][2][3]='.';obrazi[18][3][3]='@';obrazi[18][4][3]='.';
obrazi[18][0][4]='.';obrazi[18][1][4] ='.';obrazi[18][2][4]='.';obrazi[18][3][4]='@';obrazi[18][4][4]='.';
obrazi[18][0][5]='.';obrazi[18][1][5] ='.';obrazi[18][2][5]='.';obrazi[18][3][5]='@';obrazi[18][4][5]='.';
obrazi[18][0][6]='.';obrazi[18][1][6] ='.';obrazi[18][2][6]='.';obrazi[18][3][6]='@';obrazi[18][4][6]='.';
obraz_cifra[18] = 1;
obraz_cifra[19] = 2;obraz_cifra[20] = 6;obraz_cifra[21] = 9;
obraz_cifra[22] = 5;obraz_cifra[23] = 2;
obraz_cifra[24] = 3;obraz_cifra[25] = 5;
obraz_cifra[26] = 6;obraz_cifra[27] = 7;
obraz_cifra[28] = 8;obraz_cifra[29] = 9;
obraz_cifra[30] = 0;obraz_cifra[31] = 1;
obrazi[33][0][0]='.';obrazi[33][1][0] ='.';obrazi[33][2][0]='.';obrazi[33][3][0]='.';obrazi[33][4][0]='.';
obrazi[33][0][1]='.';obrazi[33][1][1] ='@';obrazi[33][2][1]='@';obrazi[33][3][1]='@';obrazi[33][4][1]='@';
obrazi[33][0][2]='.';obrazi[33][1][2] ='.';obrazi[33][2][2]='.';obrazi[33][3][2]='@';obrazi[33][4][2]='@';
obrazi[33][0][3]='.';obrazi[33][1][3] ='.';obrazi[33][2][3]='.';obrazi[33][3][3]='@';obrazi[33][4][3]='.';
obrazi[33][0][4]='.';obrazi[33][1][4] ='.';obrazi[33][2][4]='@';obrazi[33][3][4]='.';obrazi[33][4][4]='.';
obrazi[33][0][5]='.';obrazi[33][1][5] ='.';obrazi[33][2][5]='@';obrazi[33][3][5]='.';obrazi[33][4][5]='.';
obrazi[33][0][6]='.';obrazi[33][1][6] ='.';obrazi[33][2][6]='@';obrazi[33][3][6]='.';obrazi[33][4][6]='.';
obraz_cifra[33] = 7;
obrazi[34][0][0]='.';obrazi[34][1][0] ='.';obrazi[34][2][0]='.';obrazi[34][3][0]='.';obrazi[34][4][0]='.';
obrazi[34][0][1]='.';obrazi[34][1][1] ='@';obrazi[34][2][1]='@';obrazi[34][3][1]='@';obrazi[34][4][1]='.';
obrazi[34][0][2]='@';obrazi[34][1][2] ='@';obrazi[34][2][2]='.';obrazi[34][3][2]='.';obrazi[34][4][2]='@';
obrazi[34][0][3]='@';obrazi[34][1][3] ='@';obrazi[34][2][3]='.';obrazi[34][3][3]='.';obrazi[34][4][3]='@';
obrazi[34][0][4]='.';obrazi[34][1][4] ='@';obrazi[34][2][4]='.';obrazi[34][3][4]='@';obrazi[34][4][4]='@';
obrazi[34][0][5]='.';obrazi[34][1][5] ='.';obrazi[34][2][5]='@';obrazi[34][3][5]='@';obrazi[34][4][5]='@';
obrazi[34][0][6]='.';obrazi[34][1][6] ='@';obrazi[34][2][6]='.';obrazi[34][3][6]='.';obrazi[34][4][6]='@';
obraz_cifra[34] = 9;
obrazi[35][0][0]='.';obrazi[35][1][0] ='.';obrazi[35][2][0]='.';obrazi[35][3][0]='.';obrazi[35][4][0]='.';
obrazi[35][0][1]='.';obrazi[35][1][1] ='.';obrazi[35][2][1]='@';obrazi[35][3][1]='.';obrazi[35][4][1]='.';
obrazi[35][0][2]='.';obrazi[35][1][2] ='@';obrazi[35][2][2]='@';obrazi[35][3][2]='@';obrazi[35][4][2]='.';
obrazi[35][0][3]='.';obrazi[35][1][3] ='@';obrazi[35][2][3]='@';obrazi[35][3][3]='@';obrazi[35][4][3]='.';
obrazi[35][0][4]='@';obrazi[35][1][4] ='@';obrazi[35][2][4]='@';obrazi[35][3][4]='@';obrazi[35][4][4]='.';
obrazi[35][0][5]='.';obrazi[35][1][5] ='.';obrazi[35][2][5]='@';obrazi[35][3][5]='@';obrazi[35][4][5]='@';
obrazi[35][0][6]='.';obrazi[35][1][6] ='.';obrazi[35][2][6]='?';obrazi[35][3][6]='@';obrazi[35][4][6]='.';
obraz_cifra[35] = 4;
obrazi[36][0][0]='.';obrazi[36][1][0] ='.';obrazi[36][2][0]='.';obrazi[36][3][0]='@';obrazi[36][4][0]='.';
obrazi[36][0][1]='.';obrazi[36][1][1] ='@';obrazi[36][2][1]='@';obrazi[36][3][1]='@';obrazi[36][4][1]='.';
obrazi[36][0][2]='.';obrazi[36][1][2] ='@';obrazi[36][2][2]='.';obrazi[36][3][2]='@';obrazi[36][4][2]='@';
obrazi[36][0][3]='.';obrazi[36][1][3] ='@';obrazi[36][2][3]='@';obrazi[36][3][3]='@';obrazi[36][4][3]='.';
obrazi[36][0][4]='?';obrazi[36][1][4] ='@';obrazi[36][2][4]='.';obrazi[36][3][4]='@';obrazi[36][4][4]='@';
obrazi[36][0][5]='@';obrazi[36][1][5] ='@';obrazi[36][2][5]='.';obrazi[36][3][5]='.';obrazi[36][4][5]='@';
obrazi[36][0][6]='.';obrazi[36][1][6] ='@';obrazi[36][2][6]='@';obrazi[36][3][6]='@';obrazi[36][4][6]='.';
obraz_cifra[36] = 8;
obrazi[37][0][0]='.';obrazi[37][1][0] ='.';obrazi[37][2][0]='.';obrazi[37][3][0]='.';obrazi[37][4][0]='.';
obrazi[37][0][1]='.';obrazi[37][1][1] ='.';obrazi[37][2][1]='@';obrazi[37][3][1]='.';obrazi[37][4][1]='.';
obrazi[37][0][2]='.';obrazi[37][1][2] ='.';obrazi[37][2][2]='@';obrazi[37][3][2]='@';obrazi[37][4][2]='.';
obrazi[37][0][3]='.';obrazi[37][1][3] ='@';obrazi[37][2][3]='@';obrazi[37][3][3]='@';obrazi[37][4][3]='.';
obrazi[37][0][4]='.';obrazi[37][1][4] ='@';obrazi[37][2][4]='?';obrazi[37][3][4]='@';obrazi[37][4][4]='.';
obrazi[37][0][5]='.';obrazi[37][1][5] ='.';obrazi[37][2][5]='@';obrazi[37][3][5]='@';obrazi[37][4][5]='@';
obrazi[37][0][6]='.';obrazi[37][1][6] ='.';obrazi[37][2][6]='.';obrazi[37][3][6]='@';obrazi[37][4][6]='.';
obraz_cifra[37] = 4;
//5(552)(#003)
obrazi[38][0][0]='.';obrazi[38][1][0] ='@';obrazi[38][2][0]='@';obrazi[38][3][0]='@';obrazi[38][4][0]='.';
obrazi[38][0][1]='.';obrazi[38][1][1] ='@';obrazi[38][2][1]='@';obrazi[38][3][1]='@';obrazi[38][4][1]='.';
obrazi[38][0][2]='.';obrazi[38][1][2] ='@';obrazi[38][2][2]='.';obrazi[38][3][2]='.';obrazi[38][4][2]='.';
obrazi[38][0][3]='@';obrazi[38][1][3] ='@';obrazi[38][2][3]='@';obrazi[38][3][3]='@';obrazi[38][4][3]='.';
obrazi[38][0][4]='.';obrazi[38][1][4] ='.';obrazi[38][2][4]='.';obrazi[38][3][4]='@';obrazi[38][4][4]='@';
obrazi[38][0][5]='@';obrazi[38][1][5] ='@';obrazi[38][2][5]='.';obrazi[38][3][5]='@';obrazi[38][4][5]='@';
obrazi[38][0][6]='.';obrazi[38][1][6] ='@';obrazi[38][2][6]='@';obrazi[38][3][6]='@';obrazi[38][4][6]='.';
obraz_cifra[38] = 5;
//5(552)(#003)
obrazi[39][0][0]='.';obrazi[39][1][0] ='@';obrazi[39][2][0]='@';obrazi[39][3][0]='@';obrazi[39][4][0]='.';
obrazi[39][0][1]='@';obrazi[39][1][1] ='@';obrazi[39][2][1]='@';obrazi[39][3][1]='@';obrazi[39][4][1]='.';
obrazi[39][0][2]='@';obrazi[39][1][2] ='@';obrazi[39][2][2]='@';obrazi[39][3][2]='.';obrazi[39][4][2]='.';
obrazi[39][0][3]='@';obrazi[39][1][3] ='@';obrazi[39][2][3]='@';obrazi[39][3][3]='@';obrazi[39][4][3]='.';
obrazi[39][0][4]='.';obrazi[39][1][4] ='.';obrazi[39][2][4]='.';obrazi[39][3][4]='@';obrazi[39][4][4]='@';
obrazi[39][0][5]='@';obrazi[39][1][5] ='@';obrazi[39][2][5]='.';obrazi[39][3][5]='@';obrazi[39][4][5]='.';
obrazi[39][0][6]='.';obrazi[39][1][6] ='@';obrazi[39][2][6]='@';obrazi[39][3][6]='@';obrazi[39][4][6]='.';
obraz_cifra[39] = 5;
//2(552)(#003)
obrazi[40][0][0]='.';obrazi[40][1][0] ='@';obrazi[40][2][0]='@';obrazi[40][3][0]='.';obrazi[40][4][0]='.';
obrazi[40][0][1]='@';obrazi[40][1][1] ='@';obrazi[40][2][1]='@';obrazi[40][3][1]='@';obrazi[40][4][1]='.';
obrazi[40][0][2]='.';obrazi[40][1][2] ='.';obrazi[40][2][2]='@';obrazi[40][3][2]='@';obrazi[40][4][2]='.';
obrazi[40][0][3]='.';obrazi[40][1][3] ='.';obrazi[40][2][3]='@';obrazi[40][3][3]='@';obrazi[40][4][3]='.';
obrazi[40][0][4]='.';obrazi[40][1][4] ='@';obrazi[40][2][4]='@';obrazi[40][3][4]='.';obrazi[40][4][4]='.';
obrazi[40][0][5]='@';obrazi[40][1][5] ='@';obrazi[40][2][5]='@';obrazi[40][3][5]='@';obrazi[40][4][5]='.';
obrazi[40][0][6]='@';obrazi[40][1][6] ='@';obrazi[40][2][6]='@';obrazi[40][3][6]='@';obrazi[40][4][6]='.';
obraz_cifra[40] = 2;
//7(723)(#004)
obrazi[41][0][0]='.';obrazi[41][1][0] ='@';obrazi[41][2][0]='@';obrazi[41][3][0]='@';obrazi[41][4][0]='.';
obrazi[41][0][1]='.';obrazi[41][1][1] ='.';obrazi[41][2][1]='.';obrazi[41][3][1]='@';obrazi[41][4][1]='.';
obrazi[41][0][2]='.';obrazi[41][1][2] ='.';obrazi[41][2][2]='@';obrazi[41][3][2]='@';obrazi[41][4][2]='.';
obrazi[41][0][3]='.';obrazi[41][1][3] ='.';obrazi[41][2][3]='@';obrazi[41][3][3]='.';obrazi[41][4][3]='.';
obrazi[41][0][4]='.';obrazi[41][1][4] ='.';obrazi[41][2][4]='@';obrazi[41][3][4]='.';obrazi[41][4][4]='.';
obrazi[41][0][5]='.';obrazi[41][1][5] ='@';obrazi[41][2][5]='.';obrazi[41][3][5]='.';obrazi[41][4][5]='.';
obrazi[41][0][6]='.';obrazi[41][1][6] ='@';obrazi[41][2][6]='.';obrazi[41][3][6]='.';obrazi[41][4][6]='.';
obraz_cifra[41] = 7;
//2(723)(#004)
obrazi[42][0][0]='.';obrazi[42][1][0] ='@';obrazi[42][2][0]='@';obrazi[42][3][0]='.';obrazi[42][4][0]='.';
obrazi[42][0][1]='@';obrazi[42][1][1] ='.';obrazi[42][2][1]='.';obrazi[42][3][1]='@';obrazi[42][4][1]='.';
obrazi[42][0][2]='.';obrazi[42][1][2] ='.';obrazi[42][2][2]='.';obrazi[42][3][2]='@';obrazi[42][4][2]='.';
obrazi[42][0][3]='.';obrazi[42][1][3] ='.';obrazi[42][2][3]='@';obrazi[42][3][3]='@';obrazi[42][4][3]='.';
obrazi[42][0][4]='.';obrazi[42][1][4] ='@';obrazi[42][2][4]='@';obrazi[42][3][4]='.';obrazi[42][4][4]='.';
obrazi[42][0][5]='@';obrazi[42][1][5] ='@';obrazi[42][2][5]='.';obrazi[42][3][5]='.';obrazi[42][4][5]='@';
obrazi[42][0][6]='@';obrazi[42][1][6] ='@';obrazi[42][2][6]='@';obrazi[42][3][6]='@';obrazi[42][4][6]='.';
obraz_cifra[42] = 2;
obrazi[43][0][0]='@';obrazi[43][1][0] ='@';obrazi[43][2][0]='@';obrazi[43][3][0]='.';obrazi[43][4][0]='.';
obrazi[43][0][1]='@';obrazi[43][1][1] ='.';obrazi[43][2][1]='@';obrazi[43][3][1]='@';obrazi[43][4][1]='.';
obrazi[43][0][2]='.';obrazi[43][1][2] ='.';obrazi[43][2][2]='@';obrazi[43][3][2]='@';obrazi[43][4][2]='.';
obrazi[43][0][3]='.';obrazi[43][1][3] ='@';obrazi[43][2][3]='@';obrazi[43][3][3]='.';obrazi[43][4][3]='.';
obrazi[43][0][4]='.';obrazi[43][1][4] ='.';obrazi[43][2][4]='.';obrazi[43][3][4]='@';obrazi[43][4][4]='.';
obrazi[43][0][5]='@';obrazi[43][1][5] ='.';obrazi[43][2][5]='@';obrazi[43][3][5]='@';obrazi[43][4][5]='.';
obrazi[43][0][6]='@';obrazi[43][1][6] ='@';obrazi[43][2][6]='@';obrazi[43][3][6]='.';obrazi[43][4][6]='.';
obraz_cifra[43] = 3;
obrazi[44][0][0]='.';obrazi[44][1][0] ='.';obrazi[44][2][0]='.';obrazi[44][3][0]='.';obrazi[44][4][0]='.';
obrazi[44][0][1]='.';obrazi[44][1][1] ='@';obrazi[44][2][1]='@';obrazi[44][3][1]='@';obrazi[44][4][1]='.';
obrazi[44][0][2]='.';obrazi[44][1][2] ='.';obrazi[44][2][2]='.';obrazi[44][3][2]='.';obrazi[44][4][2]='.';
obrazi[44][0][3]='.';obrazi[44][1][3] ='@';obrazi[44][2][3]='?';obrazi[44][3][3]='@';obrazi[44][4][3]='.';
obrazi[44][0][4]='.';obrazi[44][1][4] ='.';obrazi[44][2][4]='.';obrazi[44][3][4]='.';obrazi[44][4][4]='@';
obrazi[44][0][5]='?';obrazi[44][1][5] ='.';obrazi[44][2][5]='.';obrazi[44][3][5]='.';obrazi[44][4][5]='@';
obrazi[44][0][6]='.';obrazi[44][1][6] ='@';obrazi[44][2][6]='.';obrazi[44][3][6]='?';obrazi[44][4][6]='.';
obraz_cifra[44] = 5;
obrazi[45][0][0]='.';obrazi[45][1][0] ='.';obrazi[45][2][0]='.';obrazi[45][3][0]='.';obrazi[45][4][0]='.';
obrazi[45][0][1]='@';obrazi[45][1][1] ='@';obrazi[45][2][1]='@';obrazi[45][3][1]='@';obrazi[45][4][1]='.';
obrazi[45][0][2]='.';obrazi[45][1][2] ='.';obrazi[45][2][2]='.';obrazi[45][3][2]='.';obrazi[45][4][2]='.';
obrazi[45][0][3]='.';obrazi[45][1][3] ='.';obrazi[45][2][3]='@';obrazi[45][3][3]='.';obrazi[45][4][3]='.';
obrazi[45][0][4]='.';obrazi[45][1][4] ='.';obrazi[45][2][4]='@';obrazi[45][3][4]='.';obrazi[45][4][4]='.';
obrazi[45][0][5]='.';obrazi[45][1][5] ='@';obrazi[45][2][5]='.';obrazi[45][3][5]='.';obrazi[45][4][5]='.';
obrazi[45][0][6]='.';obrazi[45][1][6] ='@';obrazi[45][2][6]='.';obrazi[45][3][6]='.';obrazi[45][4][6]='.';
obraz_cifra[45] = 7;
obrazi[46][0][0]='.';obrazi[46][1][0] ='.';obrazi[46][2][0]='.';obrazi[46][3][0]='.';obrazi[46][4][0]='.';
obrazi[46][0][1]='.';obrazi[46][1][1] ='@';obrazi[46][2][1]='?';obrazi[46][3][1]='.';obrazi[46][4][1]='.';
obrazi[46][0][2]='@';obrazi[46][1][2] ='.';obrazi[46][2][2]='.';obrazi[46][3][2]='.';obrazi[46][4][2]='.';
obrazi[46][0][3]='@';obrazi[46][1][3] ='?';obrazi[46][2][3]='@';obrazi[46][3][3]='.';obrazi[46][4][3]='.';
obrazi[46][0][4]='?';obrazi[46][1][4] ='.';obrazi[46][2][4]='.';obrazi[46][3][4]='@';obrazi[46][4][4]='.';
obrazi[46][0][5]='.';obrazi[46][1][5] ='.';obrazi[46][2][5]='.';obrazi[46][3][5]='@';obrazi[46][4][5]='.';
obrazi[46][0][6]='@';obrazi[46][1][6] ='.';obrazi[46][2][6]='@';obrazi[46][3][6]='@';obrazi[46][4][6]='.';
obraz_cifra[46] = 8;
obrazi[47][0][0]='.';obrazi[47][1][0] ='.';obrazi[47][2][0]='.';obrazi[47][3][0]='.';obrazi[47][4][0]='.';
obrazi[47][0][1]='.';obrazi[47][1][1] ='@';obrazi[47][2][1]='.';obrazi[47][3][1]='.';obrazi[47][4][1]='@';
obrazi[47][0][2]='.';obrazi[47][1][2] ='@';obrazi[47][2][2]='.';obrazi[47][3][2]='.';obrazi[47][4][2]='@';
obrazi[47][0][3]='.';obrazi[47][1][3] ='.';obrazi[47][2][3]='.';obrazi[47][3][3]='@';obrazi[47][4][3]='.';
obrazi[47][0][4]='.';obrazi[47][1][4] ='.';obrazi[47][2][4]='@';obrazi[47][3][4]='.';obrazi[47][4][4]='.';
obrazi[47][0][5]='.';obrazi[47][1][5] ='@';obrazi[47][2][5]='.';obrazi[47][3][5]='.';obrazi[47][4][5]='@';
obrazi[47][0][6]='.';obrazi[47][1][6] ='@';obrazi[47][2][6]='@';obrazi[47][3][6]='@';obrazi[47][4][6]='@';
obraz_cifra[47] = 2;
obrazi[48][0][0]='.';obrazi[48][1][0] ='.';obrazi[48][2][0]='.';obrazi[48][3][0]='.';obrazi[48][4][0]='.';
obrazi[48][0][1]='.';obrazi[48][1][1] ='@';obrazi[48][2][1]='.';obrazi[48][3][1]='.';obrazi[48][4][1]='@';
obrazi[48][0][2]='@';obrazi[48][1][2] ='@';obrazi[48][2][2]='.';obrazi[48][3][2]='.';obrazi[48][4][2]='@';
obrazi[48][0][3]='.';obrazi[48][1][3] ='@';obrazi[48][2][3]='@';obrazi[48][3][3]='.';obrazi[48][4][3]='@';
obrazi[48][0][4]='.';obrazi[48][1][4] ='.';obrazi[48][2][4]='.';obrazi[48][3][4]='.';obrazi[48][4][4]='@';
obrazi[48][0][5]='.';obrazi[48][1][5] ='@';obrazi[48][2][5]='.';obrazi[48][3][5]='.';obrazi[48][4][5]='@';
obrazi[48][0][6]='.';obrazi[48][1][6] ='.';obrazi[48][2][6]='.';obrazi[48][3][6]='.';obrazi[48][4][6]='.';
obraz_cifra[48] = 9;
obrazi[49][0][0]='.';obrazi[49][1][0] ='.';obrazi[49][2][0]='.';obrazi[49][3][0]='.';obrazi[49][4][0]='.';
obrazi[49][0][1]='.';obrazi[49][1][1] ='.';obrazi[49][2][1]='.';obrazi[49][3][1]='@';obrazi[49][4][1]='@';
obrazi[49][0][2]='.';obrazi[49][1][2] ='.';obrazi[49][2][2]='.';obrazi[49][3][2]='@';obrazi[49][4][2]='@';
obrazi[49][0][3]='.';obrazi[49][1][3] ='.';obrazi[49][2][3]='.';obrazi[49][3][3]='.';obrazi[49][4][3]='@';
obrazi[49][0][4]='.';obrazi[49][1][4] ='@';obrazi[49][2][4]='.';obrazi[49][3][4]='@';obrazi[49][4][4]='@';
obrazi[49][0][5]='.';obrazi[49][1][5] ='.';obrazi[49][2][5]='.';obrazi[49][3][5]='.';obrazi[49][4][5]='@';
obrazi[49][0][6]='.';obrazi[49][1][6] ='.';obrazi[49][2][6]='.';obrazi[49][3][6]='.';obrazi[49][4][6]='@';
obraz_cifra[49] = 4;
obrazi[50][0][0]='.';obrazi[50][1][0] ='@';obrazi[50][2][0]='@';obrazi[50][3][0]='@';obrazi[50][4][0]='@';
obrazi[50][0][1]='?';obrazi[50][1][1] ='@';obrazi[50][2][1]='.';obrazi[50][3][1]='.';obrazi[50][4][1]='.';
obrazi[50][0][2]='@';obrazi[50][1][2] ='@';obrazi[50][2][2]='@';obrazi[50][3][2]='.';obrazi[50][4][2]='.';
obrazi[50][0][3]='.';obrazi[50][1][3] ='.';obrazi[50][2][3]='.';obrazi[50][3][3]='@';obrazi[50][4][3]='@';
obrazi[50][0][4]='.';obrazi[50][1][4] ='.';obrazi[50][2][4]='.';obrazi[50][3][4]='.';obrazi[50][4][4]='@';
obrazi[50][0][5]='.';obrazi[50][1][5] ='.';obrazi[50][2][5]='.';obrazi[50][3][5]='.';obrazi[50][4][5]='@';
obrazi[50][0][6]='.';obrazi[50][1][6] ='.';obrazi[50][2][6]='@';obrazi[50][3][6]='@';obrazi[50][4][6]='.';
obraz_cifra[50] = 5;
obrazi[51][0][0]='.';obrazi[51][1][0] ='@';obrazi[51][2][0]='@';obrazi[51][3][0]='@';obrazi[51][4][0]='@';
obrazi[51][0][1]='?';obrazi[51][1][1] ='.';obrazi[51][2][1]='.';obrazi[51][3][1]='.';obrazi[51][4][1]='.';
obrazi[51][0][2]='@';obrazi[51][1][2] ='@';obrazi[51][2][2]='@';obrazi[51][3][2]='.';obrazi[51][4][2]='.';
obrazi[51][0][3]='.';obrazi[51][1][3] ='.';obrazi[51][2][3]='.';obrazi[51][3][3]='@';obrazi[51][4][3]='@';
obrazi[51][0][4]='.';obrazi[51][1][4] ='.';obrazi[51][2][4]='.';obrazi[51][3][4]='@';obrazi[51][4][4]='@';
obrazi[51][0][5]='.';obrazi[51][1][5] ='.';obrazi[51][2][5]='.';obrazi[51][3][5]='@';obrazi[51][4][5]='@';
obrazi[51][0][6]='.';obrazi[51][1][6] ='.';obrazi[51][2][6]='@';obrazi[51][3][6]='@';obrazi[51][4][6]='.';
obraz_cifra[51] = 5;
obrazi[52][0][0]='.';obrazi[52][1][0] ='@';obrazi[52][2][0]='?';obrazi[52][3][0]='.';obrazi[52][4][0]='.';
obrazi[52][0][1]='.';obrazi[52][1][1] ='@';obrazi[52][2][1]='@';obrazi[52][3][1]='.';obrazi[52][4][1]='.';
obrazi[52][0][2]='.';obrazi[52][1][2] ='@';obrazi[52][2][2]='@';obrazi[52][3][2]='.';obrazi[52][4][2]='.';
obrazi[52][0][3]='.';obrazi[52][1][3] ='@';obrazi[52][2][3]='@';obrazi[52][3][3]='.';obrazi[52][4][3]='.';
obrazi[52][0][4]='.';obrazi[52][1][4] ='@';obrazi[52][2][4]='@';obrazi[52][3][4]='.';obrazi[52][4][4]='.';
obrazi[52][0][5]='.';obrazi[52][1][5] ='.';obrazi[52][2][5]='.';obrazi[52][3][5]='.';obrazi[52][4][5]='.';
obrazi[52][0][6]='.';obrazi[52][1][6] ='.';obrazi[52][2][6]='.';obrazi[52][3][6]='.';obrazi[52][4][6]='.';
obraz_cifra[52] = 1;
obrazi[53][0][0]='.';obrazi[53][1][0] ='.';obrazi[53][2][0]='.';obrazi[53][3][0]='.';obrazi[53][4][0]='.';
obrazi[53][0][1]='.';obrazi[53][1][1] ='@';obrazi[53][2][1]='?';obrazi[53][3][1]='@';obrazi[53][4][1]='.';
obrazi[53][0][2]='?';obrazi[53][1][2] ='@';obrazi[53][2][2]='.';obrazi[53][3][2]='@';obrazi[53][4][2]='.';
obrazi[53][0][3]='.';obrazi[53][1][3] ='@';obrazi[53][2][3]='@';obrazi[53][3][3]='@';obrazi[53][4][3]='.';
obrazi[53][0][4]='.';obrazi[53][1][4] ='@';obrazi[53][2][4]='.';obrazi[53][3][4]='@';obrazi[53][4][4]='.';
obrazi[53][0][5]='@';obrazi[53][1][5] ='@';obrazi[53][2][5]='.';obrazi[53][3][5]='@';obrazi[53][4][5]='@';
obrazi[53][0][6]='.';obrazi[53][1][6] ='@';obrazi[53][2][6]='.';obrazi[53][3][6]='@';obrazi[53][4][6]='.';
obraz_cifra[53] = 8;
obrazi[54][0][0]='.';obrazi[54][1][0] ='.';obrazi[54][2][0]='.';obrazi[54][3][0]='.';obrazi[54][4][0]='.';
obrazi[54][0][1]='.';obrazi[54][1][1] ='@';obrazi[54][2][1]='@';obrazi[54][3][1]='.';obrazi[54][4][1]='.';
obrazi[54][0][2]='.';obrazi[54][1][2] ='@';obrazi[54][2][2]='.';obrazi[54][3][2]='.';obrazi[54][4][2]='.';
obrazi[54][0][3]='.';obrazi[54][1][3] ='@';obrazi[54][2][3]='@';obrazi[54][3][3]='@';obrazi[54][4][3]='.';
obrazi[54][0][4]='.';obrazi[54][1][4] ='.';obrazi[54][2][4]='.';obrazi[54][3][4]='@';obrazi[54][4][4]='.';
obrazi[54][0][5]='@';obrazi[54][1][5] ='.';obrazi[54][2][5]='@';obrazi[54][3][5]='@';obrazi[54][4][5]='@';
obrazi[54][0][6]='@';obrazi[54][1][6] ='.';obrazi[54][2][6]='@';obrazi[54][3][6]='.';obrazi[54][4][6]='.';
obraz_cifra[54] = 5;
obrazi[55][0][0]='.';obrazi[55][1][0] ='.';obrazi[55][2][0]='.';obrazi[55][3][0]='.';obrazi[55][4][0]='.';
obrazi[55][0][1]='@';obrazi[55][1][1] ='@';obrazi[55][2][1]='@';obrazi[55][3][1]='.';obrazi[55][4][1]='.';
obrazi[55][0][2]='@';obrazi[55][1][2] ='.';obrazi[55][2][2]='@';obrazi[55][3][2]='.';obrazi[55][4][2]='.';
obrazi[55][0][3]='@';obrazi[55][1][3] ='@';obrazi[55][2][3]='@';obrazi[55][3][3]='.';obrazi[55][4][3]='.';
obrazi[55][0][4]='.';obrazi[55][1][4] ='.';obrazi[55][2][4]='@';obrazi[55][3][4]='?';obrazi[55][4][4]='.';
obrazi[55][0][5]='.';obrazi[55][1][5] ='.';obrazi[55][2][5]='@';obrazi[55][3][5]='.';obrazi[55][4][5]='.';
obrazi[55][0][6]='@';obrazi[55][1][6] ='@';obrazi[55][2][6]='.';obrazi[55][3][6]='.';obrazi[55][4][6]='.';
obraz_cifra[55] = 3;
obrazi[56][0][0]='.';obrazi[56][1][0] ='.';obrazi[56][2][0]='@';obrazi[56][3][0]='?';obrazi[56][4][0]='.';
obrazi[56][0][1]='.';obrazi[56][1][1] ='@';obrazi[56][2][1]='@';obrazi[56][3][1]='@';obrazi[56][4][1]='.';
obrazi[56][0][2]='.';obrazi[56][1][2] ='.';obrazi[56][2][2]='@';obrazi[56][3][2]='@';obrazi[56][4][2]='.';
obrazi[56][0][3]='.';obrazi[56][1][3] ='.';obrazi[56][2][3]='@';obrazi[56][3][3]='@';obrazi[56][4][3]='.';
obrazi[56][0][4]='.';obrazi[56][1][4] ='.';obrazi[56][2][4]='@';obrazi[56][3][4]='@';obrazi[56][4][4]='.';
obrazi[56][0][5]='.';obrazi[56][1][5] ='.';obrazi[56][2][5]='@';obrazi[56][3][5]='@';obrazi[56][4][5]='.';
obrazi[56][0][6]='.';obrazi[56][1][6] ='?';obrazi[56][2][6]='@';obrazi[56][3][6]='@';obrazi[56][4][6]='.';
obraz_cifra[56] = 1;
obrazi[57][0][0]='.';obrazi[57][1][0] ='@';obrazi[57][2][0]='.';obrazi[57][3][0]='@';obrazi[57][4][0]='@';
obrazi[57][0][1]='@';obrazi[57][1][1] ='@';obrazi[57][2][1]='.';obrazi[57][3][1]='@';obrazi[57][4][1]='.';
obrazi[57][0][2]='@';obrazi[57][1][2] ='@';obrazi[57][2][2]='.';obrazi[57][3][2]='.';obrazi[57][4][2]='.';
obrazi[57][0][3]='@';obrazi[57][1][3] ='@';obrazi[57][2][3]='.';obrazi[57][3][3]='.';obrazi[57][4][3]='.';
obrazi[57][0][4]='@';obrazi[57][1][4] ='@';obrazi[57][2][4]='.';obrazi[57][3][4]='.';obrazi[57][4][4]='@';
obrazi[57][0][5]='@';obrazi[57][1][5] ='@';obrazi[57][2][5]='.';obrazi[57][3][5]='@';obrazi[57][4][5]='@';
obrazi[57][0][6]='@';obrazi[57][1][6] ='@';obrazi[57][2][6]='?';obrazi[57][3][6]='.';obrazi[57][4][6]='@';
obraz_cifra[57] = 1;
obrazi[58][0][0]='@';obrazi[58][1][0] ='@';obrazi[58][2][0]='@';obrazi[58][3][0]='.';obrazi[58][4][0]='.';
obrazi[58][0][1]='.';obrazi[58][1][1] ='.';obrazi[58][2][1]='@';obrazi[58][3][1]='.';obrazi[58][4][1]='.';
obrazi[58][0][2]='.';obrazi[58][1][2] ='?';obrazi[58][2][2]='.';obrazi[58][3][2]='.';obrazi[58][4][2]='.';
obrazi[58][0][3]='@';obrazi[58][1][3] ='@';obrazi[58][2][3]='.';obrazi[58][3][3]='.';obrazi[58][4][3]='.';
obrazi[58][0][4]='@';obrazi[58][1][4] ='.';obrazi[58][2][4]='.';obrazi[58][3][4]='.';obrazi[58][4][4]='.';
obrazi[58][0][5]='@';obrazi[58][1][5] ='.';obrazi[58][2][5]='.';obrazi[58][3][5]='.';obrazi[58][4][5]='.';
obrazi[58][0][6]='@';obrazi[58][1][6] ='.';obrazi[58][2][6]='.';obrazi[58][3][6]='.';obrazi[58][4][6]='.';
obraz_cifra[58] = 7;
obrazi[59][0][0]='.';obrazi[59][1][0] ='.';obrazi[59][2][0]='@';obrazi[59][3][0]='.';obrazi[59][4][0]='.';
obrazi[59][0][1]='.';obrazi[59][1][1] ='@';obrazi[59][2][1]='@';obrazi[59][3][1]='.';obrazi[59][4][1]='.';
obrazi[59][0][2]='.';obrazi[59][1][2] ='@';obrazi[59][2][2]='@';obrazi[59][3][2]='@';obrazi[59][4][2]='.';
obrazi[59][0][3]='@';obrazi[59][1][3] ='@';obrazi[59][2][3]='@';obrazi[59][3][3]='.';obrazi[59][4][3]='@';
obrazi[59][0][4]='@';obrazi[59][1][4] ='@';obrazi[59][2][4]='@';obrazi[59][3][4]='.';obrazi[59][4][4]='@';
obrazi[59][0][5]='.';obrazi[59][1][5] ='@';obrazi[59][2][5]='@';obrazi[59][3][5]='.';obrazi[59][4][5]='@';
obrazi[59][0][6]='.';obrazi[59][1][6] ='.';obrazi[59][2][6]='@';obrazi[59][3][6]='@';obrazi[59][4][6]='.';
obraz_cifra[59] = 6;
obrazi[60][0][0]='.';obrazi[60][1][0] ='.';obrazi[60][2][0]='.';obrazi[60][3][0]='.';obrazi[60][4][0]='.';
obrazi[60][0][1]='.';obrazi[60][1][1] ='@';obrazi[60][2][1]='.';obrazi[60][3][1]='.';obrazi[60][4][1]='.';
obrazi[60][0][2]='.';obrazi[60][1][2] ='@';obrazi[60][2][2]='@';obrazi[60][3][2]='@';obrazi[60][4][2]='.';
obrazi[60][0][3]='@';obrazi[60][1][3] ='.';obrazi[60][2][3]='@';obrazi[60][3][3]='@';obrazi[60][4][3]='@';
obrazi[60][0][4]='@';obrazi[60][1][4] ='.';obrazi[60][2][4]='@';obrazi[60][3][4]='@';obrazi[60][4][4]='@';
obrazi[60][0][5]='@';obrazi[60][1][5] ='.';obrazi[60][2][5]='@';obrazi[60][3][5]='@';obrazi[60][4][5]='@';
obrazi[60][0][6]='.';obrazi[60][1][6] ='@';obrazi[60][2][6]='@';obrazi[60][3][6]='@';obrazi[60][4][6]='.';
obraz_cifra[60] = 5;
obrazi[61][0][0]='.';obrazi[61][1][0] ='.';obrazi[61][2][0]='@';obrazi[61][3][0]='.';obrazi[61][4][0]='.';
obrazi[61][0][1]='.';obrazi[61][1][1] ='@';obrazi[61][2][1]='@';obrazi[61][3][1]='.';obrazi[61][4][1]='@';
obrazi[61][0][2]='@';obrazi[61][1][2] ='@';obrazi[61][2][2]='@';obrazi[61][3][2]='.';obrazi[61][4][2]='@';
obrazi[61][0][3]='@';obrazi[61][1][3] ='@';obrazi[61][2][3]='@';obrazi[61][3][3]='.';obrazi[61][4][3]='@';
obrazi[61][0][4]='@';obrazi[61][1][4] ='@';obrazi[61][2][4]='@';obrazi[61][3][4]='.';obrazi[61][4][4]='@';
obrazi[61][0][5]='@';obrazi[61][1][5] ='@';obrazi[61][2][5]='@';obrazi[61][3][5]='.';obrazi[61][4][5]='@';
obrazi[61][0][6]='.';obrazi[61][1][6] ='.';obrazi[61][2][6]='@';obrazi[61][3][6]='@';obrazi[61][4][6]='.';
obraz_cifra[61] = 0;
obrazi[62][0][0]='.';obrazi[62][1][0] ='.';obrazi[62][2][0]='.';obrazi[62][3][0]='.';obrazi[62][4][0]='.';
obrazi[62][0][1]='.';obrazi[62][1][1] ='@';obrazi[62][2][1]='@';obrazi[62][3][1]='@';obrazi[62][4][1]='@';
obrazi[62][0][2]='?';obrazi[62][1][2] ='@';obrazi[62][2][2]='.';obrazi[62][3][2]='@';obrazi[62][4][2]='@';
obrazi[62][0][3]='.';obrazi[62][1][3] ='@';obrazi[62][2][3]='@';obrazi[62][3][3]='@';obrazi[62][4][3]='.';
obrazi[62][0][4]='.';obrazi[62][1][4] ='@';obrazi[62][2][4]='@';obrazi[62][3][4]='@';obrazi[62][4][4]='@';
obrazi[62][0][5]='?';obrazi[62][1][5] ='@';obrazi[62][2][5]='.';obrazi[62][3][5]='@';obrazi[62][4][5]='@';
obrazi[62][0][6]='@';obrazi[62][1][6] ='@';obrazi[62][2][6]='@';obrazi[62][3][6]='@';obrazi[62][4][6]='.';
obraz_cifra[62] = 8;
obrazi[63][0][0]='.';obrazi[63][1][0] ='.';obrazi[63][2][0]='.';obrazi[63][3][0]='.';obrazi[63][4][0]='.';
obrazi[63][0][1]='.';obrazi[63][1][1] ='.';obrazi[63][2][1]='@';obrazi[63][3][1]='.';obrazi[63][4][1]='.';
obrazi[63][0][2]='.';obrazi[63][1][2] ='@';obrazi[63][2][2]='@';obrazi[63][3][2]='.';obrazi[63][4][2]='.';
obrazi[63][0][3]='.';obrazi[63][1][3] ='@';obrazi[63][2][3]='?';obrazi[63][3][3]='@';obrazi[63][4][3]='@';
obrazi[63][0][4]='@';obrazi[63][1][4] ='@';obrazi[63][2][4]='.';obrazi[63][3][4]='@';obrazi[63][4][4]='@';
obrazi[63][0][5]='@';obrazi[63][1][5] ='@';obrazi[63][2][5]='@';obrazi[63][3][5]='@';obrazi[63][4][5]='@';
obrazi[63][0][6]='.';obrazi[63][1][6] ='@';obrazi[63][2][6]='@';obrazi[63][3][6]='@';obrazi[63][4][6]='@';
obraz_cifra[63] = 6;
obrazi[64][0][0]='.';obrazi[64][1][0] ='.';obrazi[64][2][0]='.';obrazi[64][3][0]='?';obrazi[64][4][0]='.';
obrazi[64][0][1]='.';obrazi[64][1][1] ='.';obrazi[64][2][1]='@';obrazi[64][3][1]='?';obrazi[64][4][1]='.';
obrazi[64][0][2]='.';obrazi[64][1][2] ='.';obrazi[64][2][2]='@';obrazi[64][3][2]='@';obrazi[64][4][2]='@';
obrazi[64][0][3]='.';obrazi[64][1][3] ='@';obrazi[64][2][3]='.';obrazi[64][3][3]='@';obrazi[64][4][3]='@';
obrazi[64][0][4]='@';obrazi[64][1][4] ='@';obrazi[64][2][4]='@';obrazi[64][3][4]='@';obrazi[64][4][4]='@';
obrazi[64][0][5]='@';obrazi[64][1][5] ='@';obrazi[64][2][5]='@';obrazi[64][3][5]='@';obrazi[64][4][5]='@';
obrazi[64][0][6]='.';obrazi[64][1][6] ='.';obrazi[64][2][6]='.';obrazi[64][3][6]='@';obrazi[64][4][6]='@';
obraz_cifra[64] = 4;
obrazi[65][0][0]='.';obrazi[65][1][0] ='.';obrazi[65][2][0]='@';obrazi[65][3][0]='.';obrazi[65][4][0]='.';
obrazi[65][0][1]='.';obrazi[65][1][1] ='?';obrazi[65][2][1]='@';obrazi[65][3][1]='.';obrazi[65][4][1]='.';
obrazi[65][0][2]='.';obrazi[65][1][2] ='@';obrazi[65][2][2]='@';obrazi[65][3][2]='?';obrazi[65][4][2]='.';
obrazi[65][0][3]='@';obrazi[65][1][3] ='@';obrazi[65][2][3]='@';obrazi[65][3][3]='@';obrazi[65][4][3]='@';
obrazi[65][0][4]='.';obrazi[65][1][4] ='.';obrazi[65][2][4]='@';obrazi[65][3][4]='@';obrazi[65][4][4]='.';
obrazi[65][0][5]='.';obrazi[65][1][5] ='.';obrazi[65][2][5]='@';obrazi[65][3][5]='.';obrazi[65][4][5]='.';
obrazi[65][0][6]='.';obrazi[65][1][6] ='.';obrazi[65][2][6]='.';obrazi[65][3][6]='.';obrazi[65][4][6]='.';
obraz_cifra[65] = 4;
obrazi[66][0][0]='.';obrazi[66][1][0] ='@';obrazi[66][2][0]='.';obrazi[66][3][0]='.';obrazi[66][4][0]='.';
obrazi[66][0][1]='.';obrazi[66][1][1] ='@';obrazi[66][2][1]='.';obrazi[66][3][1]='.';obrazi[66][4][1]='.';
obrazi[66][0][2]='@';obrazi[66][1][2] ='@';obrazi[66][2][2]='@';obrazi[66][3][2]='.';obrazi[66][4][2]='.';
obrazi[66][0][3]='@';obrazi[66][1][3] ='@';obrazi[66][2][3]='@';obrazi[66][3][3]='@';obrazi[66][4][3]='@';
obrazi[66][0][4]='.';obrazi[66][1][4] ='?';obrazi[66][2][4]='@';obrazi[66][3][4]='.';obrazi[66][4][4]='@';
obrazi[66][0][5]='.';obrazi[66][1][5] ='.';obrazi[66][2][5]='@';obrazi[66][3][5]='.';obrazi[66][4][5]='.';
obrazi[66][0][6]='.';obrazi[66][1][6] ='.';obrazi[66][2][6]='.';obrazi[66][3][6]='.';obrazi[66][4][6]='.';
obraz_cifra[66] = 4;
obrazi[67][0][0]='.';obrazi[67][1][0] ='@';obrazi[67][2][0]='.';obrazi[67][3][0]='.';obrazi[67][4][0]='.';
obrazi[67][0][1]='@';obrazi[67][1][1] ='@';obrazi[67][2][1]='@';obrazi[67][3][1]='.';obrazi[67][4][1]='.';
obrazi[67][0][2]='@';obrazi[67][1][2] ='.';obrazi[67][2][2]='@';obrazi[67][3][2]='@';obrazi[67][4][2]='.';
obrazi[67][0][3]='@';obrazi[67][1][3] ='@';obrazi[67][2][3]='@';obrazi[67][3][3]='.';obrazi[67][4][3]='.';
obrazi[67][0][4]='@';obrazi[67][1][4] ='.';obrazi[67][2][4]='@';obrazi[67][3][4]='@';obrazi[67][4][4]='.';
obrazi[67][0][5]='@';obrazi[67][1][5] ='@';obrazi[67][2][5]='@';obrazi[67][3][5]='.';obrazi[67][4][5]='.';
obrazi[67][0][6]='.';obrazi[67][1][6] ='.';obrazi[67][2][6]='.';obrazi[67][3][6]='.';obrazi[67][4][6]='.';
obraz_cifra[67] = 8;
obrazi[68][0][0]='.';obrazi[68][1][0] ='.';obrazi[68][2][0]='.';obrazi[68][3][0]='.';obrazi[68][4][0]='.';
obrazi[68][0][1]='.';obrazi[68][1][1] ='.';obrazi[68][2][1]='@';obrazi[68][3][1]='@';obrazi[68][4][1]='.';
obrazi[68][0][2]='@';obrazi[68][1][2] ='@';obrazi[68][2][2]='@';obrazi[68][3][2]='@';obrazi[68][4][2]='@';
obrazi[68][0][3]='@';obrazi[68][1][3] ='@';obrazi[68][2][3]='@';obrazi[68][3][3]='@';obrazi[68][4][3]='@';
obrazi[68][0][4]='@';obrazi[68][1][4] ='@';obrazi[68][2][4]='@';obrazi[68][3][4]='@';obrazi[68][4][4]='@';
obrazi[68][0][5]='.';obrazi[68][1][5] ='@';obrazi[68][2][5]='@';obrazi[68][3][5]='@';obrazi[68][4][5]='@';
obrazi[68][0][6]='.';obrazi[68][1][6] ='.';obrazi[68][2][6]='@';obrazi[68][3][6]='@';obrazi[68][4][6]='@';
obraz_cifra[68] = 9;
obrazi[69][0][0]='.';obrazi[69][1][0] ='.';obrazi[69][2][0]='@';obrazi[69][3][0]='.';obrazi[69][4][0]='.';
obrazi[69][0][1]='.';obrazi[69][1][1] ='@';obrazi[69][2][1]='@';obrazi[69][3][1]='@';obrazi[69][4][1]='.';
obrazi[69][0][2]='@';obrazi[69][1][2] ='@';obrazi[69][2][2]='@';obrazi[69][3][2]='@';obrazi[69][4][2]='@';
obrazi[69][0][3]='@';obrazi[69][1][3] ='@';obrazi[69][2][3]='@';obrazi[69][3][3]='@';obrazi[69][4][3]='@';
obrazi[69][0][4]='@';obrazi[69][1][4] ='@';obrazi[69][2][4]='@';obrazi[69][3][4]='@';obrazi[69][4][4]='@';
obrazi[69][0][5]='.';obrazi[69][1][5] ='@';obrazi[69][2][5]='@';obrazi[69][3][5]='@';obrazi[69][4][5]='@';
obrazi[69][0][6]='.';obrazi[69][1][6] ='.';obrazi[69][2][6]='@';obrazi[69][3][6]='@';obrazi[69][4][6]='@';
obraz_cifra[69] = 6;
obrazi[70][0][0]='.';obrazi[70][1][0] ='.';obrazi[70][2][0]='@';obrazi[70][3][0]='?';obrazi[70][4][0]='.';
obrazi[70][0][1]='.';obrazi[70][1][1] ='?';obrazi[70][2][1]='@';obrazi[70][3][1]='@';obrazi[70][4][1]='.';
obrazi[70][0][2]='.';obrazi[70][1][2] ='@';obrazi[70][2][2]='@';obrazi[70][3][2]='@';obrazi[70][4][2]='@';
obrazi[70][0][3]='@';obrazi[70][1][3] ='@';obrazi[70][2][3]='@';obrazi[70][3][3]='@';obrazi[70][4][3]='@';
obrazi[70][0][4]='@';obrazi[70][1][4] ='@';obrazi[70][2][4]='@';obrazi[70][3][4]='@';obrazi[70][4][4]='@';
obrazi[70][0][5]='@';obrazi[70][1][5] ='@';obrazi[70][2][5]='@';obrazi[70][3][5]='@';obrazi[70][4][5]='@';
obrazi[70][0][6]='.';obrazi[70][1][6] ='.';obrazi[70][2][6]='@';obrazi[70][3][6]='@';obrazi[70][4][6]='@';
obraz_cifra[70] = 6;
obrazi[71][0][0]='.';obrazi[71][1][0] ='.';obrazi[71][2][0]='.';obrazi[71][3][0]='.';obrazi[71][4][0]='.';
obrazi[71][0][1]='.';obrazi[71][1][1] ='@';obrazi[71][2][1]='@';obrazi[71][3][1]='?';obrazi[71][4][1]='.';
obrazi[71][0][2]='.';obrazi[71][1][2] ='?';obrazi[71][2][2]='@';obrazi[71][3][2]='@';obrazi[71][4][2]='.';
obrazi[71][0][3]='.';obrazi[71][1][3] ='.';obrazi[71][2][3]='@';obrazi[71][3][3]='@';obrazi[71][4][3]='.';
obrazi[71][0][4]='.';obrazi[71][1][4] ='.';obrazi[71][2][4]='@';obrazi[71][3][4]='@';obrazi[71][4][4]='.';
obrazi[71][0][5]='.';obrazi[71][1][5] ='.';obrazi[71][2][5]='@';obrazi[71][3][5]='?';obrazi[71][4][5]='@';
obrazi[71][0][6]='.';obrazi[71][1][6] ='@';obrazi[71][2][6]='@';obrazi[71][3][6]='@';obrazi[71][4][6]='@';
obraz_cifra[71] = 2;
obrazi[72][0][0]='.';obrazi[72][1][0] ='.';obrazi[72][2][0]='.';obrazi[72][3][0]='.';obrazi[72][4][0]='.';
obrazi[72][0][1]='.';obrazi[72][1][1] ='.';obrazi[72][2][1]='@';obrazi[72][3][1]='@';obrazi[72][4][1]='@';
obrazi[72][0][2]='.';obrazi[72][1][2] ='@';obrazi[72][2][2]='@';obrazi[72][3][2]='@';obrazi[72][4][2]='.';
obrazi[72][0][3]='?';obrazi[72][1][3] ='@';obrazi[72][2][3]='@';obrazi[72][3][3]='?';obrazi[72][4][3]='.';
obrazi[72][0][4]='@';obrazi[72][1][4] ='@';obrazi[72][2][4]='@';obrazi[72][3][4]='?';obrazi[72][4][4]='.';
obrazi[72][0][5]='@';obrazi[72][1][5] ='@';obrazi[72][2][5]='@';obrazi[72][3][5]='@';obrazi[72][4][5]='.';
obrazi[72][0][6]='@';obrazi[72][1][6] ='@';obrazi[72][2][6]='@';obrazi[72][3][6]='@';obrazi[72][4][6]='@';
obraz_cifra[72] = 4;
obrazi[73][0][0]='.';obrazi[73][1][0] ='.';obrazi[73][2][0]='.';obrazi[73][3][0]='.';obrazi[73][4][0]='.';
obrazi[73][0][1]='@';obrazi[73][1][1] ='@';obrazi[73][2][1]='@';obrazi[73][3][1]='.';obrazi[73][4][1]='.';
obrazi[73][0][2]='@';obrazi[73][1][2] ='@';obrazi[73][2][2]='@';obrazi[73][3][2]='.';obrazi[73][4][2]='.';
obrazi[73][0][3]='@';obrazi[73][1][3] ='@';obrazi[73][2][3]='.';obrazi[73][3][3]='.';obrazi[73][4][3]='.';
obrazi[73][0][4]='@';obrazi[73][1][4] ='@';obrazi[73][2][4]='.';obrazi[73][3][4]='.';obrazi[73][4][4]='.';
obrazi[73][0][5]='@';obrazi[73][1][5] ='@';obrazi[73][2][5]='.';obrazi[73][3][5]='.';obrazi[73][4][5]='.';
obrazi[73][0][6]='@';obrazi[73][1][6] ='?';obrazi[73][2][6]='.';obrazi[73][3][6]='.';obrazi[73][4][6]='.';
obraz_cifra[73] = 7;
obrazi[74][0][0]='.';obrazi[74][1][0] ='.';obrazi[74][2][0]='.';obrazi[74][3][0]='@';obrazi[74][4][0]='@';
obrazi[74][0][1]='@';obrazi[74][1][1] ='@';obrazi[74][2][1]='@';obrazi[74][3][1]='@';obrazi[74][4][1]='@';
obrazi[74][0][2]='@';obrazi[74][1][2] ='@';obrazi[74][2][2]='.';obrazi[74][3][2]='.';obrazi[74][4][2]='@';
obrazi[74][0][3]='.';obrazi[74][1][3] ='@';obrazi[74][2][3]='.';obrazi[74][3][3]='@';obrazi[74][4][3]='@';
obrazi[74][0][4]='.';obrazi[74][1][4] ='.';obrazi[74][2][4]='@';obrazi[74][3][4]='@';obrazi[74][4][4]='@';
obrazi[74][0][5]='.';obrazi[74][1][5] ='.';obrazi[74][2][5]='.';obrazi[74][3][5]='.';obrazi[74][4][5]='@';
obrazi[74][0][6]='.';obrazi[74][1][6] ='.';obrazi[74][2][6]='.';obrazi[74][3][6]='?';obrazi[74][4][6]='@';
obraz_cifra[74] = 9;
obrazi[75][0][0]='.';obrazi[75][1][0] ='.';obrazi[75][2][0]='.';obrazi[75][3][0]='.';obrazi[75][4][0]='.';
obrazi[75][0][1]='.';obrazi[75][1][1] ='@';obrazi[75][2][1]='@';obrazi[75][3][1]='@';obrazi[75][4][1]='@';
obrazi[75][0][2]='.';obrazi[75][1][2] ='@';obrazi[75][2][2]='@';obrazi[75][3][2]='.';obrazi[75][4][2]='.';
obrazi[75][0][3]='.';obrazi[75][1][3] ='@';obrazi[75][2][3]='@';obrazi[75][3][3]='@';obrazi[75][4][3]='@';
obrazi[75][0][4]='.';obrazi[75][1][4] ='.';obrazi[75][2][4]='.';obrazi[75][3][4]='@';obrazi[75][4][4]='@';
obrazi[75][0][5]='@';obrazi[75][1][5] ='@';obrazi[75][2][5]='.';obrazi[75][3][5]='@';obrazi[75][4][5]='@';
obrazi[75][0][6]='.';obrazi[75][1][6] ='@';obrazi[75][2][6]='@';obrazi[75][3][6]='@';obrazi[75][4][6]='.';
obraz_cifra[75] = 5;
obrazi[76][0][0]='.';obrazi[76][1][0] ='.';obrazi[76][2][0]='@';obrazi[76][3][0]='@';obrazi[76][4][0]='@';
obrazi[76][0][1]='.';obrazi[76][1][1] ='@';obrazi[76][2][1]='@';obrazi[76][3][1]='@';obrazi[76][4][1]='@';
obrazi[76][0][2]='@';obrazi[76][1][2] ='@';obrazi[76][2][2]='.';obrazi[76][3][2]='.';obrazi[76][4][2]='@';
obrazi[76][0][3]='.';obrazi[76][1][3] ='@';obrazi[76][2][3]='.';obrazi[76][3][3]='@';obrazi[76][4][3]='@';
obrazi[76][0][4]='.';obrazi[76][1][4] ='.';obrazi[76][2][4]='@';obrazi[76][3][4]='?';obrazi[76][4][4]='@';
obrazi[76][0][5]='.';obrazi[76][1][5] ='.';obrazi[76][2][5]='.';obrazi[76][3][5]='.';obrazi[76][4][5]='@';
obrazi[76][0][6]='.';obrazi[76][1][6] ='.';obrazi[76][2][6]='.';obrazi[76][3][6]='.';obrazi[76][4][6]='@';
obraz_cifra[76] = 9;
obrazi[77][0][0]='.';obrazi[77][1][0] ='.';obrazi[77][2][0]='@';obrazi[77][3][0]='@';obrazi[77][4][0]='.';
obrazi[77][0][1]='.';obrazi[77][1][1] ='@';obrazi[77][2][1]='@';obrazi[77][3][1]='.';obrazi[77][4][1]='@';
obrazi[77][0][2]='.';obrazi[77][1][2] ='@';obrazi[77][2][2]='@';obrazi[77][3][2]='.';obrazi[77][4][2]='@';
obrazi[77][0][3]='.';obrazi[77][1][3] ='@';obrazi[77][2][3]='@';obrazi[77][3][3]='@';obrazi[77][4][3]='@';
obrazi[77][0][4]='@';obrazi[77][1][4] ='.';obrazi[77][2][4]='.';obrazi[77][3][4]='@';obrazi[77][4][4]='@';
obrazi[77][0][5]='@';obrazi[77][1][5] ='.';obrazi[77][2][5]='.';obrazi[77][3][5]='@';obrazi[77][4][5]='@';
obrazi[77][0][6]='.';obrazi[77][1][6] ='@';obrazi[77][2][6]='@';obrazi[77][3][6]='@';obrazi[77][4][6]='@';
obraz_cifra[77] = 8;
obrazi[78][0][0]='.';obrazi[78][1][0] ='.';obrazi[78][2][0]='@';obrazi[78][3][0]='@';obrazi[78][4][0]='.';
obrazi[78][0][1]='.';obrazi[78][1][1] ='.';obrazi[78][2][1]='@';obrazi[78][3][1]='@';obrazi[78][4][1]='.';
obrazi[78][0][2]='.';obrazi[78][1][2] ='@';obrazi[78][2][2]='@';obrazi[78][3][2]='.';obrazi[78][4][2]='.';
obrazi[78][0][3]='.';obrazi[78][1][3] ='.';obrazi[78][2][3]='.';obrazi[78][3][3]='.';obrazi[78][4][3]='@';
obrazi[78][0][4]='.';obrazi[78][1][4] ='.';obrazi[78][2][4]='.';obrazi[78][3][4]='.';obrazi[78][4][4]='@';
obrazi[78][0][5]='@';obrazi[78][1][5] ='.';obrazi[78][2][5]='.';obrazi[78][3][5]='.';obrazi[78][4][5]='@';
obrazi[78][0][6]='.';obrazi[78][1][6] ='@';obrazi[78][2][6]='@';obrazi[78][3][6]='@';obrazi[78][4][6]='.';
obraz_cifra[78] = 5;
obrazi[79][0][0]='.';obrazi[79][1][0] ='.';obrazi[79][2][0]='@';obrazi[79][3][0]='@';obrazi[79][4][0]='.';
obrazi[79][0][1]='@';obrazi[79][1][1] ='@';obrazi[79][2][1]='@';obrazi[79][3][1]='.';obrazi[79][4][1]='@';
obrazi[79][0][2]='@';obrazi[79][1][2] ='@';obrazi[79][2][2]='@';obrazi[79][3][2]='.';obrazi[79][4][2]='@';
obrazi[79][0][3]='.';obrazi[79][1][3] ='@';obrazi[79][2][3]='@';obrazi[79][3][3]='@';obrazi[79][4][3]='@';
obrazi[79][0][4]='@';obrazi[79][1][4] ='.';obrazi[79][2][4]='.';obrazi[79][3][4]='@';obrazi[79][4][4]='@';
obrazi[79][0][5]='@';obrazi[79][1][5] ='.';obrazi[79][2][5]='.';obrazi[79][3][5]='@';obrazi[79][4][5]='@';
obrazi[79][0][6]='.';obrazi[79][1][6] ='@';obrazi[79][2][6]='@';obrazi[79][3][6]='@';obrazi[79][4][6]='.';
obraz_cifra[79] = 8;
obrazi[80][0][0]='.';obrazi[80][1][0] ='.';obrazi[80][2][0]='.';obrazi[80][3][0]='.';obrazi[80][4][0]='.';
obrazi[80][0][1]='.';obrazi[80][1][1] ='.';obrazi[80][2][1]='.';obrazi[80][3][1]='.';obrazi[80][4][1]='.';
obrazi[80][0][2]='.';obrazi[80][1][2] ='.';obrazi[80][2][2]='@';obrazi[80][3][2]='.';obrazi[80][4][2]='.';
obrazi[80][0][3]='.';obrazi[80][1][3] ='.';obrazi[80][2][3]='@';obrazi[80][3][3]='.';obrazi[80][4][3]='.';
obrazi[80][0][4]='.';obrazi[80][1][4] ='.';obrazi[80][2][4]='@';obrazi[80][3][4]='@';obrazi[80][4][4]='.';
obrazi[80][0][5]='.';obrazi[80][1][5] ='.';obrazi[80][2][5]='@';obrazi[80][3][5]='.';obrazi[80][4][5]='.';
obrazi[80][0][6]='.';obrazi[80][1][6] ='.';obrazi[80][2][6]='.';obrazi[80][3][6]='.';obrazi[80][4][6]='.';
obraz_cifra[80] = 8;
obrazi[81][0][0]='.';obrazi[81][1][0] ='.';obrazi[81][2][0]='.';obrazi[81][3][0]='.';obrazi[81][4][0]='.';
obrazi[81][0][1]='.';obrazi[81][1][1] ='.';obrazi[81][2][1]='.';obrazi[81][3][1]='.';obrazi[81][4][1]='.';
obrazi[81][0][2]='.';obrazi[81][1][2] ='.';obrazi[81][2][2]='@';obrazi[81][3][2]='.';obrazi[81][4][2]='.';
obrazi[81][0][3]='.';obrazi[81][1][3] ='.';obrazi[81][2][3]='@';obrazi[81][3][3]='@';obrazi[81][4][3]='.';
obrazi[81][0][4]='.';obrazi[81][1][4] ='.';obrazi[81][2][4]='@';obrazi[81][3][4]='.';obrazi[81][4][4]='.';
obrazi[81][0][5]='.';obrazi[81][1][5] ='.';obrazi[81][2][5]='@';obrazi[81][3][5]='.';obrazi[81][4][5]='.';
obrazi[81][0][6]='.';obrazi[81][1][6] ='.';obrazi[81][2][6]='.';obrazi[81][3][6]='.';obrazi[81][4][6]='.';
obraz_cifra[81] = 9;
obrazi[82][0][0]='.';obrazi[82][1][0] ='.';obrazi[82][2][0]='.';obrazi[82][3][0]='.';obrazi[82][4][0]='.';
obrazi[82][0][1]='.';obrazi[82][1][1] ='.';obrazi[82][2][1]='.';obrazi[82][3][1]='.';obrazi[82][4][1]='.';
obrazi[82][0][2]='.';obrazi[82][1][2] ='.';obrazi[82][2][2]='@';obrazi[82][3][2]='.';obrazi[82][4][2]='.';
obrazi[82][0][3]='.';obrazi[82][1][3] ='.';obrazi[82][2][3]='@';obrazi[82][3][3]='.';obrazi[82][4][3]='.';
obrazi[82][0][4]='.';obrazi[82][1][4] ='.';obrazi[82][2][4]='@';obrazi[82][3][4]='.';obrazi[82][4][4]='.';
obrazi[82][0][5]='.';obrazi[82][1][5] ='.';obrazi[82][2][5]='@';obrazi[82][3][5]='.';obrazi[82][4][5]='.';
obrazi[82][0][6]='.';obrazi[82][1][6] ='.';obrazi[82][2][6]='.';obrazi[82][3][6]='.';obrazi[82][4][6]='.';
obraz_cifra[82] = 2;
obrazi[83][0][0]='.';obrazi[83][1][0] ='.';obrazi[83][2][0]='?';obrazi[83][3][0]='@';obrazi[83][4][0]='@';
obrazi[83][0][1]='.';obrazi[83][1][1] ='@';obrazi[83][2][1]='@';obrazi[83][3][1]='@';obrazi[83][4][1]='@';
obrazi[83][0][2]='.';obrazi[83][1][2] ='@';obrazi[83][2][2]='@';obrazi[83][3][2]='@';obrazi[83][4][2]='.';
obrazi[83][0][3]='.';obrazi[83][1][3] ='.';obrazi[83][2][3]='@';obrazi[83][3][3]='.';obrazi[83][4][3]='.';
obrazi[83][0][4]='.';obrazi[83][1][4] ='@';obrazi[83][2][4]='@';obrazi[83][3][4]='@';obrazi[83][4][4]='.';
obrazi[83][0][5]='@';obrazi[83][1][5] ='@';obrazi[83][2][5]='@';obrazi[83][3][5]='.';obrazi[83][4][5]='.';
obrazi[83][0][6]='.';obrazi[83][1][6] ='@';obrazi[83][2][6]='.';obrazi[83][3][6]='.';obrazi[83][4][6]='@';
obraz_cifra[83] = 8;
obrazi[84][0][0]='.';obrazi[84][1][0] ='@';obrazi[84][2][0]='@';obrazi[84][3][0]='@';obrazi[84][4][0]='.';
obrazi[84][0][1]='.';obrazi[84][1][1] ='@';obrazi[84][2][1]='.';obrazi[84][3][1]='.';obrazi[84][4][1]='.';
obrazi[84][0][2]='.';obrazi[84][1][2] ='@';obrazi[84][2][2]='@';obrazi[84][3][2]='.';obrazi[84][4][2]='.';
obrazi[84][0][3]='.';obrazi[84][1][3] ='.';obrazi[84][2][3]='@';obrazi[84][3][3]='.';obrazi[84][4][3]='.';
obrazi[84][0][4]='.';obrazi[84][1][4] ='@';obrazi[84][2][4]='.';obrazi[84][3][4]='.';obrazi[84][4][4]='?';
obrazi[84][0][5]='@';obrazi[84][1][5] ='.';obrazi[84][2][5]='.';obrazi[84][3][5]='@';obrazi[84][4][5]='@';
obrazi[84][0][6]='@';obrazi[84][1][6] ='.';obrazi[84][2][6]='.';obrazi[84][3][6]='@';obrazi[84][4][6]='.';
obraz_cifra[84] = 5;
obrazi[85][0][0]='.';obrazi[85][1][0] ='.';obrazi[85][2][0]='@';obrazi[85][3][0]='@';obrazi[85][4][0]='.';
obrazi[85][0][1]='@';obrazi[85][1][1] ='@';obrazi[85][2][1]='@';obrazi[85][3][1]='@';obrazi[85][4][1]='.';
obrazi[85][0][2]='.';obrazi[85][1][2] ='@';obrazi[85][2][2]='.';obrazi[85][3][2]='.';obrazi[85][4][2]='.';
obrazi[85][0][3]='@';obrazi[85][1][3] ='.';obrazi[85][2][3]='.';obrazi[85][3][3]='.';obrazi[85][4][3]='.';
obrazi[85][0][4]='@';obrazi[85][1][4] ='.';obrazi[85][2][4]='.';obrazi[85][3][4]='.';obrazi[85][4][4]='.';
obrazi[85][0][5]='@';obrazi[85][1][5] ='@';obrazi[85][2][5]='.';obrazi[85][3][5]='@';obrazi[85][4][5]='.';
obrazi[85][0][6]='.';obrazi[85][1][6] ='@';obrazi[85][2][6]='@';obrazi[85][3][6]='?';obrazi[85][4][6]='.';
obraz_cifra[85] = 2;
}
