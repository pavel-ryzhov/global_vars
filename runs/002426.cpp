#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;
void poisk_sviazey_vniz(int,int,int);
void poisk_sviazey_vverh(int,int,int);
short int kol_tochek;
short int kol_otvet;
short int *mas_otvet_i;
short int *mas_otvet_j;
short int mas_putey[1500][1500];
int mas_reber[1500][1500];
short int mas_otvet_yes[1500];
bool mas_ok[1500];
int tek_summa[50000];
short int kol_etapov[10000];
short int index_sum;

int main()
{
index_sum=0;
cin>>kol_tochek;

short int i,j;
for(i=1;i<=kol_tochek;i++){for(j=1;j<=kol_tochek;j++){mas_reber[i][j]=-1;}}
if(kol_tochek>1)
{
for (i=1;i<=kol_tochek-1;i++)
	{
	int int_z[3];
	cin>>int_z[0]>>int_z[1]>>int_z[2];
	mas_reber[int_z[0]][int_z[1]] = mas_reber[int_z[1]][int_z[0]] = int_z[2];
	}
}

cin>>kol_otvet;
mas_otvet_i = new short int[kol_otvet+1];
mas_otvet_j = new short int[kol_otvet+1];

for(i=1;i<=kol_tochek;i++)
{
	mas_otvet_yes[i]=0;
	for(j=1;j<=kol_tochek;j++)
		{
		(mas_reber[i][j]!=-1)?mas_putey[i][j]=mas_reber[i][j]:mas_putey[i][j]=0;
		}
}

for (i=1;i<=kol_otvet;i++)
	{
	cin>>mas_otvet_i[i]>>mas_otvet_j[i];
	mas_otvet_yes[mas_otvet_i[i]]=1;
	}

index_sum=0;
for(i=1;i<=kol_tochek;i++)
	{
	if(mas_otvet_yes[i]==1)
		{
		for(j=1;j<=kol_tochek;j++)(i==j)?mas_ok[j]=true:mas_ok[j]=false;
		kol_etapov[index_sum]=tek_summa[index_sum]=0;
		poisk_sviazey_vniz(i,i,index_sum);
		index_sum++;
		}
	}

if(kol_tochek > 0)
{
for(i=1;i<=kol_otvet;i++)
{
cout<<mas_putey[mas_otvet_i[i]][mas_otvet_j[i]]<<endl;
}
}

delete []mas_otvet_i;delete []mas_otvet_j;

int key;
cin>>key;
}

void poisk_sviazey_vniz(int ot,int tek_do,int index)
	{
		short int i,j;
		short int kolichestvo_perehodov = 0;
		kol_etapov[index]++;
		for(j=1;j<=kol_tochek;j++)
			{
			if(mas_ok[j]==false)if(mas_reber[tek_do][j]!=-1)
				{
				kolichestvo_perehodov++;
				mas_ok[j]=true;
				index_sum++;
				kol_etapov[index_sum]=kol_etapov[index];
				tek_summa[index_sum]=tek_summa[index];
				if(kol_etapov[index_sum]>1)
					mas_putey[ot][tek_do] = tek_summa[index_sum];
				tek_summa[index_sum]=tek_summa[index_sum]+mas_reber[tek_do][j];
				poisk_sviazey_vniz(ot,j,index_sum);
				}
			}
		if(kolichestvo_perehodov==0)
		{
			if(kol_etapov[index]>1)if(mas_putey[ot][tek_do]==0)
			mas_putey[ot][tek_do]=tek_summa[index];
		}
	}