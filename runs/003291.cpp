#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;

int main()
{
//================================================================
//==================×ÀÑÒÜ 1. ÂÂÎÄ ÄÀÍÍÛÕ.=========================
//================================================================

	unsigned short int predel=40000, pr;
	unsigned short int kol_vershin, kol_par;
	unsigned int i, j;
	unsigned short int X[40000], Y[40000], L[40000], V1[40000], V2[40000];

	unsigned int k; // íîìåð ñ÷èòûâàåìîé òðîéêè, íà÷èíàÿ ñ íóëåâîãî çíà÷åíèÿ
	
	cin >> kol_vershin;
	k=0;
	while ((kol_vershin==' ')&&(k==0))
	{if (kol_vershin!=32){cin >> kol_vershin;}
	else {k=1;}}
	if ((kol_vershin<0)||(kol_vershin>predel)){cout << "Entered number is too big.";return 1;}


	for (i=0; i<(kol_vershin-1);i++)
	{
		cin >> pr;
		k=0;
		while ((pr==' ')&&(k==0))
		{if (pr!=32){cin >> pr;}
		else {k=1;}}
		if ((pr<0)||(pr>40000)){cout << "X1 is too big.";return 1;}
		else {X[i]=pr;}

		cin >> pr;
		k=0;
		while ((pr==' ')&&(k==0))
		{if (pr!=32){cin >> pr;}
		else {k=1;}}
		if ((pr<0)||(pr>40000)){cout << "Y1 is too big.";return 1;}
		else {Y[i]=pr;}

		cin >> pr;
		k=0;
		while ((pr==' ')&&(k==0))
		{if (pr!=32){cin >> pr;}
		else {k=1;}}
		if ((pr<0)||(pr>40000)){cout << "L1 is too big.";return 1;}
		else {L[i]=pr;}		
	}

	cin >> kol_par;
	k=0;
	while ((pr==' ')&&(k==0))
	{if (pr!=32){cin >> pr;}
	else {k=1;}}
	if ((kol_par<0)||(kol_par>predel)){cout << "Entered number is too big.";return 1;}

	for (i=0; i<kol_par;i++)
	{
		cin >> pr;
		k=0;
		while ((pr==' ')&&(k==0))
		{if (pr!=32){cin >> pr;}
		else {k=1;}}
		if ((pr<0)||(pr>40000)){cout << "V1 is too big.";return 1;}
		else {V1[i]=pr;}

		cin >> pr;
		k=0;
		while ((pr==' ')&&(k==0))
		{if (pr!=32){cin >> pr;}
		else {k=1;}}
		if ((pr<0)||(pr>40000)){cout << "V2 is too big.";return 1;}
		else {V2[i]=pr;}
	}

	
//================================================================
//==================×ÀÑÒÜ 1. ÊÎÍÅÖ.===============================
//================================================================

//================================================================
//==================×ÀÑÒÜ 2. ÏÎÑÒÐÎÅÍÈÅ ÖÅÏÈ.=====================
//================================================================

	short int cep_napr[40000];
	unsigned short int psi, ksi;
	unsigned long int summa;

	// äëÿ âñåõ ââåäåííûõ ïàð
	for (ksi=0; ksi<kol_par; ksi++)
	{
	for (i=0; i<(kol_vershin-1); i++) cep_napr[i]=0;

	if (V1[ksi]!=V2[ksi])
	{
	psi=V1[ksi];
	proverka_po_x:
	// èùåì ñîîòâåòñòâèå ñðåäè X ìàññèâà
	for (i=0; i<(kol_vershin-1); i++)
	{
		if ((X[i]==psi)&&(cep_napr[i]==0))
		{
			cep_napr[i]=1;
			psi=Y[i];
			if (psi==V2[ksi]) goto part3;
			goto proverka_po_x;
		}
	}
	for (j=0; j<(kol_vershin-1); j++)
	{
		if ((Y[j]==psi)&&(cep_napr[j]==0))
		{
			cep_napr[j]=2;
			psi=X[j];
			if (psi==V2[ksi]) goto part3;
			goto proverka_po_x;
		}
	}

	for (i=0; i<(kol_vershin-1); i++)
	{
		if ((X[i]==psi)&&(cep_napr[i]==2))
		{
			cep_napr[i]=3;
			psi=Y[i];
			if (psi==V2[ksi]) goto part3;
			goto proverka_po_x;
		}
	}

	for (j=0; j<(kol_vershin-1); j++)
	{
		if ((Y[j]==psi)&&(cep_napr[j]==1))
		{
			cep_napr[j]=3;
			psi=X[j];
			if (psi==V2[ksi]) goto part3;
			goto proverka_po_x;
		}
	}


	for (i=0; i<(kol_vershin-1); i++)
	{
		if (cep_napr[i]!=3) goto proverka_po_x;
	}

//================================================================
//==================×ÀÑÒÜ 2. ÊÎÍÅÖ.===============================
//================================================================

part3:

//================================================================
//==================×ÀÑÒÜ 4. ÂÛ×ÈÑËÅÍÈÅ ÑÓÌÌÛ.====================
//================================================================

	summa=0;

	for (i=0; i<(kol_vershin-1); i++)
	{
		if ((cep_napr[i]==1)||(cep_napr[i]==2))
		{
			summa=summa+L[i];
		}
	}
	}
	else summa=0;


	cout << summa << "\n";//çàïèñü ðåçóëüòàòà
	}

//================================================================
//==================×ÀÑÒÜ 4. ÊÎÍÅÖ.===============================
//================================================================

	return 0;
}