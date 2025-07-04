#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;

int main()
{
//================================================================
//==================ЧАСТЬ 1. ВВОД ДАННЫХ.=========================
//================================================================

	unsigned short int predel=40000, pr;
	unsigned short int kol_vershin, kol_par;
	unsigned int i, j;
	unsigned short int X[40000], Y[40000], L[40000], V1[40000], V2[40000];

	unsigned int k; // номер считываемой тройки, начиная с нулевого значения
	
	cin >> kol_vershin;
	while (kol_vershin==' '){cin >> kol_vershin;}
	if ((kol_vershin<0)||(kol_vershin>predel)){cout << "Entered number is too big.";return 1;}


	for (i=0; i<(kol_vershin-1);i++)
	{
		cin >> pr;
		while (pr==' '){cin >> pr;}
		if ((pr<0)||(pr>40000)){cout << "X1 is too big.";return 1;}
		else {X[i]=pr;}

		cin >> pr;
		while (pr==' '){cin >> pr;}
		if ((pr<0)||(pr>40000)){cout << "Y1 is too big.";return 1;}
		else {Y[i]=pr;}

		cin >> pr;
		while (pr==' '){cin >> pr;}
		if ((pr<0)||(pr>40000)){cout << "L1 is too big.";return 1;}
		else {L[i]=pr;}		
	}

	cin >> kol_par;
	while (kol_par==' '){cin >> kol_par;}
	if ((kol_par<0)||(kol_par>predel)){cout << "Entered number is too big.";return 1;}

	for (i=0; i<kol_par;i++)
	{
		cin >> pr;
		while (pr==' '){cin >> pr;}
		if ((pr<0)||(pr>40000)){cout << "V1 is too big.";return 1;}
		else {V1[i]=pr;}

		cin >> pr;
		while (pr==' '){cin >> pr;}
		if ((pr<0)||(pr>40000)){cout << "V2 is too big.";return 1;}
		else {V2[i]=pr;}
	}

	
//================================================================
//==================ЧАСТЬ 1. КОНЕЦ.===============================
//================================================================
	
//================================================================
//==================ЧАСТЬ 2. ПОСТРОЕНИЕ ЦЕПИ.=====================
//================================================================

	short int cep_napr[40000];
	short int cep_nomera_poryadok[2*(40000-1)-1];
	unsigned short int psi, ksi;
	short int n_c;
	unsigned long int summa;
	unsigned short int ii;
	unsigned short int delta;

	// для всех введенных пар
	for (ksi=0; ksi<kol_par; ksi++)
	{
		n_c=0;

	for (i=0; i<(kol_vershin-1); i++) cep_napr[i]=0;


	if (V1[ksi]!=V2[ksi])
	{
	psi=V1[ksi];
	proverka_po_x:
	// ищем соответствие среди X массива
	for (i=0; i<(kol_vershin-1); i++)
	{
		if ((X[i]==psi)&&(cep_napr[i]==0))
		{
			cep_nomera_poryadok[n_c/2]=i;
			cep_napr[i]=1;
			n_c++;
			psi=Y[i];
			n_c++;
			if (psi==V2[ksi]) goto part3;
			goto proverka_po_x;
		}
	}
	for (j=0; j<(kol_vershin-1); j++)
	{
		if ((Y[j]==psi)&&(cep_napr[j]==0))
		{
			cep_nomera_poryadok[n_c/2]=j;
			cep_napr[j]=2;
			n_c++;
			psi=X[j];
			n_c++;
			if (psi==V2[ksi]) goto part3;
			goto proverka_po_x;
		}
	}

	for (i=0; i<(kol_vershin-1); i++)
	{
		if ((X[i]==psi)&&(cep_napr[i]==2))
		{
			cep_nomera_poryadok[n_c/2]=i;
			cep_napr[i]=3;
			n_c++;
			psi=Y[i];
			n_c++;
			if (psi==V2[ksi]) goto part3;
			goto proverka_po_x;
		}
	}

	for (j=0; j<(kol_vershin-1); j++)
	{
		if ((Y[j]==psi)&&(cep_napr[j]==1))
		{
			cep_nomera_poryadok[n_c/2]=j;
			cep_napr[j]=3;
			n_c++;
			psi=X[j];
			n_c++;
			if (psi==V2[ksi]) goto part3;
			goto proverka_po_x;
		}
	}


	for (i=0; i<(kol_vershin-1); i++)
	{
		if (cep_napr[i]!=3) goto proverka_po_x;
	}

//================================================================
//==================ЧАСТЬ 2. КОНЕЦ.===============================
//================================================================

part3:

//================================================================
//==================ЧАСТЬ 3. ПРЕОБРАЗОВАНИЕ ЦЕПИ.=================
//================================================================

	k=((n_c-1)/2);
	for (i=0; i<=k; i++)
	{
		for (j=k; j>i; j--)
		{
			if (cep_nomera_poryadok[i]==cep_nomera_poryadok[j])
			{
				//укорачивание цепи за счет сдвига
				delta=(j-i)+1;
				k=(k-delta);
				for (ii=i; ii<=k; ii++)
				{
					cep_nomera_poryadok[ii]=cep_nomera_poryadok[ii+delta];
				}
			}
		}
	}

//================================================================
//==================ЧАСТЬ 3. КОНЕЦ.===============================
//================================================================

//================================================================
//==================ЧАСТЬ 4. ВЫЧИСЛЕНИЕ СУММЫ.====================
//================================================================

	summa=0;
	for (i=0; i<=k; i++)
	{
		summa=summa+L[(cep_nomera_poryadok[i])]; //cout << summa << "  ";
	}
	}
	else summa=0;

	cout << summa << "\n";//запись результата
	}

//================================================================
//==================ЧАСТЬ 4. КОНЕЦ.===============================
//================================================================

	return 0;
}