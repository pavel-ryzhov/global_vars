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
int mas_ok[100];
int tek_summa[10000];
int kol_etapov[10000];
int index_sum;
int main()
{
index_sum=0;
cin>>kol_tochek;
for(int i=1;i<=kol_tochek;i++){for(int j=1;j<=kol_tochek;j++){mas_reber[i][j]=-1;}}
if(kol_tochek>1)
{
for (int i=1;i<=kol_tochek-1;i++)
	{
	int int_z[3];
	cin>>int_z[0]>>int_z[1]>>int_z[2];
	mas_reber[int_z[0]][int_z[1]] = int_z[2];
	mas_reber[int_z[1]][int_z[0]] = int_z[2];
	}
}

cin>>kol_otvet;
for (int i=1;i<=kol_otvet;i++)
	{
	int int_z[2];
	cin>>int_z[0]>>int_z[1];
	mas_otvet_i[i] = int_z[0];
	mas_otvet_j[i] = int_z[1];
	}

for(int i=1;i<=kol_tochek;i++)
{
	for(int j=1;j<=kol_tochek;j++)
		{
		if(mas_reber[i][j]!=-1)
			mas_putey[i][j]=mas_reber[i][j];
			else 
			mas_putey[i][j]=0;
		}
}

index_sum=0;
for(int i=1;i<=kol_tochek;i++)
	{
	for(int j=1;j<=kol_tochek;j++)if(i==j)mas_ok[j]=1;else mas_ok[j]=0;
	kol_etapov[index_sum]=0;
	tek_summa[index_sum]=0;
	poisk_sviazey_vniz(i,i,index_sum);
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
		if(mas_putey[j][i] != 0)
		mas_putey[i][j]=mas_putey[j][i];
		}
	}
}

if(kol_tochek > 0)
{
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
		for(int j=1;j<=kol_tochek;j++)
			{
			if(mas_reber[tek_do][j]>=0)
				{if(mas_ok[j]==0) kolichestvo_perehodov++;}
			}
		
		kol_etapov[index]++;
		switch(kolichestvo_perehodov)
			{
			case 0: 
				if(kol_etapov[index]>1)
					if(mas_putey[ot][tek_do]==0)
						{
						mas_putey[ot][tek_do]=tek_summa[index];
						} 
				break;
			case 1:
				for(int j=1;j<=kol_tochek;j++)
					{
					if(mas_ok[j]==0)
						{
						if(mas_reber[tek_do][j]!=-1)
							{
							mas_ok[j]=1;
							if(kol_etapov[index]>1)if(mas_putey[ot][tek_do]==0)
								mas_putey[ot][tek_do]=tek_summa[index];
							tek_summa[index]=tek_summa[index]+mas_reber[tek_do][j];
							poisk_sviazey_vniz(ot,j,index);
							}
						}
					}
				break;
			default:
				int new_index=0;
				for(int j=1;j<=kol_tochek;j++)
					{
					if(mas_ok[j]==0)
						{
						if(mas_reber[tek_do][j]!=-1)
							{
							mas_ok[j]=1;
							new_index++;
							if(new_index == kolichestvo_perehodov)
								{
								if(kol_etapov[index]>1)if(mas_putey[ot][tek_do]==0)
									{
									mas_putey[ot][tek_do] = tek_summa[index]; 
									}
								tek_summa[index] = tek_summa[index] + mas_reber[tek_do][j];
								poisk_sviazey_vniz(ot,j,index);
								}
								else
								{
								index_sum++;
								kol_etapov[index_sum]=kol_etapov[index];
								tek_summa[index_sum]=tek_summa[index];
								if(kol_etapov[index_sum]>1)
									{
									mas_putey[ot][tek_do] = tek_summa[index_sum];
									}
								tek_summa[index_sum]=tek_summa[index_sum]+mas_reber[tek_do][j];
								poisk_sviazey_vniz(ot,j,index_sum);
								}
							}
						}
					}
				break;
			}
	}