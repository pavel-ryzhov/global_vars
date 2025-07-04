#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int main()
{
//================================================================
//==================×ÀÑÒÜ 1. ÂÂÎÄ ÄÀÍÍÛÕ.=========================
//================================================================

	unsigned short int predel=40000, pr;
	unsigned short int kol_vershin, kol_par;
	unsigned int i, j, k;
	unsigned short int X[40000], Y[40000], L[40000], V1[40000], V2[40000];
	
	cin >> kol_vershin;

	while (kol_vershin=='\0'){cin >> kol_vershin;}
	if ((kol_vershin<0)||(kol_vershin>predel)){cout << "Entered number is too big.";return 1;}


	for (i=0; i<(kol_vershin-1);i++)
	{
		cin >> pr;
		while (pr=='\0'){cin >> pr;}
		if ((pr<0)||(pr>40000)){cout << "X1 is too big.";return 1;}
		else {X[i]=pr;}

		cin >> pr;
		while (pr=='\0'){cin >> pr;}
		if ((pr<0)||(pr>40000)){cout << "Y1 is too big.";return 1;}
		else {Y[i]=pr;}

		cin >> pr;
		while (pr=='\0'){cin >> pr;}
		if ((pr<0)||(pr>40000)){cout << "L1 is too big.";return 1;}
		else {L[i]=pr;}		
	}

	cin >> kol_par;
	while (pr=='\0'){cin >> pr;}
	if ((kol_par<0)||(kol_par>predel)){cout << "Entered number is too big.";return 1;}

	for (i=0; i<kol_par;i++)
	{
		cin >> pr;
		while (pr=='\0'){cin >> pr;}
		if ((pr<0)||(pr>40000)){cout << "V1 is too big.";return 1;}
		else {V1[i]=pr;}

		cin >> pr;
		while (pr=='\0'){cin >> pr;}
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
		if (cep_napr[i]==0)
		{
		if (X[i]==psi)
		{
			cep_napr[i]=1;
			psi=Y[i];
			if (psi==V2[ksi]) goto part3;
			goto proverka_po_x;
		}
		if (Y[i]==psi)
		{
			cep_napr[i]=2;
			psi=X[i];
			if (psi==V2[ksi]) goto part3;
			goto proverka_po_x;
		}
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
		if ((Y[i]==psi)&&(cep_napr[i]==1))
		{
			cep_napr[i]=3;
			psi=X[i];
			if (psi==V2[ksi]) goto part3;
			goto proverka_po_x;
		}
	}

	for (i=0; i<(kol_vershin-1); i++){if (cep_napr[i]!=3) goto proverka_po_x;}

//================================================================
//==================×ÀÑÒÜ 2. ÊÎÍÅÖ.===============================
//================================================================

part3:

//================================================================
//==================×ÀÑÒÜ 4. ÂÛ×ÈÑËÅÍÈÅ ÑÓÌÌÛ.====================
//================================================================

	summa=0;

	for (i=0; i<(kol_vershin-1); i++){if ((cep_napr[i]==1)||(cep_napr[i]==2)){summa=summa+L[i];}}
	}
	else summa=0;

	cout << summa << "\n";//çàïèñü ðåçóëüòàòà
	}

//================================================================
//==================×ÀÑÒÜ 4. ÊÎÍÅÖ.===============================
//================================================================

	return 0;
}