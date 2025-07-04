#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
void poisk_sviazey_vniz(int,int,int);
void poisk_sviazey_vverh(int,int,int);
int	kol_tochek;
int kol_otvet;
int mas_otvet_i[100];
int mas_otvet_j[100];
int mas_putey[100][100];
int mas_reber[100][100];
int tek_summa[10000];
int kol_etapov[10000];
int index_sum;
int main()
{

for(int kol_raz=0;kol_raz<=100;kol_raz++)
{
index_sum=0;
cin>>kol_tochek;
string tek_znachenie="";
for (int i=1;i<=kol_tochek-1;i++)
	{
	int int_z[3];
	cin>>int_z[0]>>int_z[1]>>int_z[2];
	mas_reber[int_z[0]][int_z[1]] = int_z[2];
	mas_reber[int_z[1]][int_z[0]] = int_z[2];
	}

cin>>kol_otvet;
int index_otv=0;
for (int i=1;i<=kol_otvet;i++)
	{
	int int_z[2];
	cin>>int_z[0]>>int_z[1];
	index_otv++;
	mas_otvet_i[index_otv] = int_z[0];
	mas_otvet_j[index_otv] = int_z[1];
	}
for(int i=1;i<=kol_tochek;i++){for(int j=1;j<=kol_tochek;j++){mas_putey[i][j]=mas_reber[i][j];}}
index_sum=0;
for(int i=1;i<=kol_tochek;i++)
	{
	kol_etapov[index_sum]=0;
	tek_summa[index_sum]=0;
	poisk_sviazey_vniz(i,i,index_sum);
	index_sum++;
	}
index_sum = 0;
for(int i=kol_tochek;i>=1;i--)
	{
	kol_etapov[index_sum]=0;
	tek_summa[index_sum]=0;
	poisk_sviazey_vverh(i,i,index_sum);
	index_sum++;
	}
for(int i=1;i<=kol_tochek;i++)
{
	for(int j=1;j<=kol_tochek;j++)
	{
		if(i==j)
		{
		mas_putey[i][j]=0;
		}
		if(i>j)
		{
		mas_putey[i][j]=mas_putey[j][i];
		}
	}
}

for(int i=1;i<=kol_otvet;i++)
{
	cout<<mas_putey[mas_otvet_i[i]][mas_otvet_j[i]]<<endl;
}
}
int key;
cin>>key;
}

void poisk_sviazey_vniz(int ot,int tek_do,int index)
	{
		int kolichestvo_perehodov = 0;
		for(int j=tek_do;j<=kol_tochek;j++)
			{
			if(mas_reber[tek_do][j]!=0)
				{
				kolichestvo_perehodov++;
				}
			}
		switch(kolichestvo_perehodov)
			{
			case 0: 
				kol_etapov[index]++; 
				if(kol_etapov[index]>1)
					if(mas_putey[ot][tek_do]==0)
					{
					tek_summa[index] = tek_summa[index] + mas_reber[ot][tek_do];
					mas_putey[ot][tek_do]=tek_summa[index];
					} 
				break;
			case 1:
				kol_etapov[index]++;
				for(int j=tek_do;j<=kol_tochek;j++)
					{
					if(mas_reber[tek_do][j]!=0)
						{
						if(kol_etapov[index]>1)if(mas_putey[ot][tek_do]==0){mas_putey[ot][tek_do] = tek_summa[index];} 
						tek_summa[index] = tek_summa[index] + mas_reber[tek_do][j];
						poisk_sviazey_vniz(ot,j,index);
						}
					}
				break;
			default:
				kol_etapov[index]++;
				int new_index=0;
				for(int j=tek_do;j<=kol_tochek;j++)
					{
					if(mas_reber[tek_do][j]!=0)
						{
						new_index++;
						if(new_index == kolichestvo_perehodov)
							{
							if(kol_etapov[index]>1)if(mas_putey[ot][tek_do]==0){mas_putey[ot][tek_do] = tek_summa[index];}
							tek_summa[index] = tek_summa[index] + mas_reber[tek_do][j];
							poisk_sviazey_vniz(ot,j,index);
							}
							else
							{
							index_sum++;
							kol_etapov[index_sum]=kol_etapov[index];
							tek_summa[index_sum]=tek_summa[index];
							tek_summa[index_sum] = tek_summa[index_sum] + mas_reber[tek_do][j];
							if(kol_etapov[index_sum]>1)if(mas_putey[ot][tek_do]==0){mas_putey[ot][tek_do] = tek_summa[index_sum];} 
							poisk_sviazey_vniz(ot,j,index_sum);
							}
						}
					}
				break;
			}
	}

void poisk_sviazey_vverh(int ot,int tek_do,int index)
	{
		int kolichestvo_perehodov = 0;
		for(int j=1;j<=tek_do;j++)
			{
			if(mas_reber[tek_do][j]!=0)
				{
				kolichestvo_perehodov++;
				}
			}
		switch(kolichestvo_perehodov)
			{
			case 0: 
				kol_etapov[index]++; 
				if(kol_etapov[index]>1)
					if(mas_putey[ot][tek_do]==0)
					{
					tek_summa[index] = tek_summa[index] + mas_reber[ot][tek_do];
					mas_putey[ot][tek_do]=tek_summa[index];
					} 
				break;
			case 1:
				kol_etapov[index]++;
				for(int j=1;j<=tek_do;j++)
					{
					if(mas_reber[tek_do][j]!=0)
						{
						if(kol_etapov[index]>1)if(mas_putey[ot][tek_do]==0){mas_putey[ot][tek_do] = tek_summa[index];} 
						tek_summa[index] = tek_summa[index] + mas_reber[tek_do][j];
						poisk_sviazey_vniz(ot,j,index);
						}
					}
				break;
			default:
				kol_etapov[index]++;
				int new_index=0;
				for(int j=1;j<=tek_do;j++)
					{
					if(mas_reber[tek_do][j]!=0)
						{
						new_index++;
						if(new_index == kolichestvo_perehodov)
							{
							if(kol_etapov[index]>1)if(mas_putey[ot][tek_do]==0){mas_putey[ot][tek_do] = tek_summa[index];}
							tek_summa[index] = tek_summa[index] + mas_reber[tek_do][j];
							poisk_sviazey_vniz(ot,j,index);
							}
							else
							{
							index_sum++;
							kol_etapov[index_sum]=kol_etapov[index];
							tek_summa[index_sum]=tek_summa[index];
							tek_summa[index_sum] = tek_summa[index_sum] + mas_reber[tek_do][j];
							if(kol_etapov[index_sum]>1)if(mas_putey[ot][tek_do]==0){mas_putey[ot][tek_do] = tek_summa[index_sum];} 
							poisk_sviazey_vniz(ot,j,index_sum);
							}
						}
					}
				break;
			}
	}