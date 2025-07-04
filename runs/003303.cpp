#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int main()
{
//================================================================
//==================ЧАСТЬ 1. ВВОД ДАННЫХ.=========================
//================================================================

	unsigned short int predel=40000, pr;
	unsigned short int kol_vershin, kol_par;
	int i, j, k;
	unsigned short int X[40000], Y[40000], L[40000], V1[40000], V2[40000];
	
	cin >> kol_vershin;

	while (kol_vershin=='\0'){if(kol_vershin!=0){cin >> kol_vershin;}else break;}
	if ((kol_vershin<0)||(kol_vershin>predel)){cout << "Entered number is too big.";return 1;}

	for (i=0; i<(kol_vershin-1);i++)
	{
		cin >> pr;
		while (pr=='\0'){if(pr!=0){cin >> pr;}else break;}
		if ((pr<0)||(pr>40000)){cout << "X1 is too big.";return 1;}
		else {X[i]=pr;}

		cin >> pr;
		while (pr=='\0'){if(pr!=0){cin >> pr;}else break;}
		if ((pr<0)||(pr>40000)){cout << "Y1 is too big.";return 1;}
		else {Y[i]=pr;}

		cin >> pr;
		while (pr=='\0'){if(pr!=0){cin >> pr;}else break;}
		if ((pr<0)||(pr>40000)){cout << "L1 is too big.";return 1;}
		else {L[i]=pr;}		
	}

	cin >> kol_par;
	while (kol_par=='\0'){if(kol_par!=0){cin >> kol_par;}else break;}
	if ((kol_par<0)||(kol_par>predel)){cout << "Entered number is too big.";return 1;}

	for (i=0; i<kol_par;i++)
	{
		cin >> pr;
		while (pr=='\0'){if(pr!=0){cin >> pr;}else break;}
		if ((pr<0)||(pr>40000)){cout << "V1 is too big.";return 1;}
		else {V1[i]=pr;}

		cin >> pr;
		while (pr=='\0'){if(pr!=0){cin >> pr;}else break;}
		if ((pr<0)||(pr>40000)){cout << "V2 is too big.";return 1;}
		else {V2[i]=pr;}
	}

	
//================================================================
//==================ЧАСТЬ 1. КОНЕЦ.===============================
//================================================================

//================================================================
//==================ЧАСТЬ 2. ПОСТРОЕНИЕ ЦЕПИ.=====================
//================================================================


	short int cep_napr[400];
	unsigned short int psi, ksi;
	unsigned long int summa;
	unsigned short int nom_ver[2*(400-1)];
	unsigned short int cep_nom_por[2*(400-1)], mass[2*(400-1)];

	unsigned short int ii, b, e, n_beg, n_end, r, n_c, delta, kk;


	//обходим полностью весь массив, чтобы каждая грань прошлась туда-обратно

	for (i=0; i<(kol_vershin-1); i++) cep_napr[i]=0;

	n_c=0;
	psi=X[0];

	proverka_po_x:
	// ищем соответствие среди X массива
	for (i=0; i<(kol_vershin-1); i++)
	{
		if (cep_napr[i]==0)
		{
			if (X[i]==psi)
			{
				cep_napr[i]=1;
				nom_ver[n_c]=psi;//номер вершины
				psi=Y[i];
				cep_nom_por[n_c]=i;//номер грани, по которой проходим
				n_c++;
				goto proverka_po_x;
			}
			if (Y[i]==psi)
			{
				cep_napr[i]=2;
				nom_ver[n_c]=psi;//номер вершины
				psi=X[i];
				cep_nom_por[n_c]=i;//номер грани, по которой проходим
				n_c++;
				goto proverka_po_x;
			}
		}
	}
	for (i=0; i<(kol_vershin-1); i++)
	{
		if ((X[i]==psi)&&(cep_napr[i]==2))
		{
			cep_napr[i]=3;
			nom_ver[n_c]=psi;//номер вершины
			psi=Y[i];
			cep_nom_por[n_c]=i;//номер грани, по которой проходим
			n_c++;
			goto proverka_po_x;
		}
		if ((Y[i]==psi)&&(cep_napr[i]==1))
		{
			cep_napr[i]=3;
			nom_ver[n_c]=psi;//номер вершины
			psi=X[i];
			cep_nom_por[n_c]=i;//номер грани, по которой проходим
			n_c++;
			goto proverka_po_x;
		}
	}


	for (k=0; k<kol_par; k++)
	{
	if (V1[k]!=V2[k])
	{
		n_beg=0;n_end=0;b=0;e=0;

		for (i=0; i<n_c; i++)
		{
			if (nom_ver[i]==V1[k])
			{
				if (e==1){n_beg=i;i=n_c;}
				else {n_beg=i; b=1;}
			}
			else if (nom_ver[i]==V2[k])
			{
				if (b==1){n_end=i;i=n_c;}
				else {n_end=i; e=1;}
			}
		}
	

		if (n_end<n_beg){r=n_beg;n_beg=n_end;n_end=r;}

	//теперь переписываем часть массива с номера n_beg по n_end для удобной работы

		kk=n_end-n_beg;
		for (i=0; i<kk; i++){mass[i]=cep_nom_por[i+n_beg];}

		//теперь сокращаем кусок записанной цепи
		
		for (i=0; i<(kk-1); i++)
		{
			for (j=(kk-1); j>i; j--)
			{
				if (mass[i]==mass[j])
				{
					//укорачивание цепи за счет сдвига
					delta=(j-i)+1;
					kk=(kk-delta);
					for (ii=i; ii<kk; ii++){mass[ii]=mass[ii+delta];}
					i--;j=i;
				}
			}
		}
		





//================================================================
//==================ЧАСТЬ 2. КОНЕЦ.===============================
//================================================================

part3:

//================================================================
//==================ЧАСТЬ 4. ВЫЧИСЛЕНИЕ СУММЫ.====================
//================================================================

	summa=0;

	for (i=0; i<kk; i++){summa=summa+L[(mass[i])];}
	}
	else summa=0;

	cout << summa << "\n";//запись результата
	}

//================================================================
//==================ЧАСТЬ 4. КОНЕЦ.===============================
//================================================================

	return 0;
}