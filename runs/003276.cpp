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


	//unsigned short int many=50000;
	unsigned short int predel=40000;
	unsigned short int kol_vershin, kol_par;
	unsigned int i, j;
	unsigned short int X[40000], Y[40000], L[40000], V1[40000], V2[40000];

	char str[18];

	unsigned int k; // номер считываемой тройки, начиная с нулевого значения
	short int b, dl;
	char s[6];

	ifstream in("file2.txt");
	if (!in){cout << "File is not exist.\n";return 1;}

	for (i=0; i<6; i++)//посимвольное считывание количества вершин
	{
		in.get(str[i]);
		if (str[i]=='\n')
		{
			for (j=0; j<i; j++) {s[j]=str[j];}
			s[i]='\0';
			kol_vershin=atoi(s);
			if (kol_vershin>predel){cout << "The third number is too big.\n";return 1;}
			i=strlen(str);
		}
		else if ((str[i]==' ')||(str[i]<'0')||(str[i]>'9')){cout << "The number is uncorrected.\n";return 1;}
	}

	//считывание Первая_вершина-Вторая_вершина-Длина_ребра
	for (k=0; k<(kol_vershin-1); k++)
	{
		dl=0; //вспомогательная переменная
		b=0; // считает количество чисел в строке, начиная с нуля
		for (i=0; i<strlen(str); i++) // i - номер считываемого символа в строке
		{
			in.get(str[i]);
			if ((str[i]==' ')&&((i-dl)<=5))
			{
				if (b==0)
				{
				for (j=0; j<(i-dl); j++)
				{
					s[j]=str[(dl+j)];
				}
				s[i-dl]='\0';
				X[k]=atoi(s);
				if (X[k]>predel){cout << "The first number is too big.\n";return 1;}

				dl=i+1;
				b++;
				}
				else if (b==1)
				{
				for (j=0; j<(i-dl); j++)
				{
					s[j]=str[(dl+j)];
				}
				s[i-dl]='\0';
				Y[k]=atoi(s);
				if (Y[k]>predel)
				{
					cout << "The second number is too big.\n";
					return 1;
				}
				dl=i+1;
				b++;
				}
			}
			else if ((str[i]==' ')&&((i-dl)>5))
			{
				cout << "One of the entered numbers is too big.\n";
				return 1;
			}
			if ((str[i]=='\n')&&(b==2))
			{
				for (j=0; j<(i-dl); j++)
				{
					s[j]=str[(dl+j)];
				}
				s[i-dl]='\0';
				L[k]=atoi(s);
				if (L[k]>predel)
				{
					cout << "The third number is too big.\n";
					return 1;
				}
				i=strlen(str);
			}
			else if ((str[i]=='\0')&&(b!=2)){cout << "It must be three numbers in the line.\n";return 1;}
		}

	}

	//считываем число пар вершин, расстояние между которыми надо определить
	for (i=0; i<6; i++)
	{
		in.get(str[i]);
		if (str[i]=='\n')
		{
			for (j=0; j<i; j++) {s[j]=str[j];}
			s[i]='\0';
			kol_par=atoi(s); //cout << kol_par << "\n";
			if (kol_par>predel)
			{
				cout << "The third number is too big.\n";
				return 1;
			}
			i=strlen(str);
		}
		else if ((str[i]==' ')||(str[i]<'0')||(str[i]>'9'))
		{
			cout << "The number is uncorrected.\n";
			return 1;
		}
	}

	//считываем Первая_вершина-Вторая_вершина
	for (k=0; k<(kol_par); k++)
	{
		dl=0; //вспомогательная переменная
		b=0; // считает количество чисел в строке, начиная с нуля
		for (i=0; i<strlen(str); i++) // i - номер считываемого символа в строке
		{
			in.get(str[i]);
			if ((str[i]==' ')&&((i-dl)<=5))
			{
				if (b==0)
				{
				for (j=0; j<(i-dl); j++)
				{
					s[j]=str[(dl+j)];
				}
				s[i-dl]='\0';
				V1[k]=atoi(s);
				if (V1[k]>predel)
				{
					cout << "The first number is too big.\n";
					return 1;
				}
				dl=i+1;
				b++;
				}
			}
			else if ((str[i]==' ')&&((i-dl)>5))
			{
				cout << "One of the entered numbers is too big.\n";
				return 1;
			}
			if ((str[i]=='\n')&&(b==1))
			{
				for (j=0; j<(i-dl); j++)
				{
					s[j]=str[(dl+j)];
				}
				s[i-dl]='\0';
				V2[k]=atoi(s); //cout << V2[k] << "\n";
				if (V2[k]>predel)
				{
					cout << "The third number is too big.\n";
					return 1;
				}
				i=strlen(str);
			}
			else if ((str[i]=='\0')&&(b!=1))
			{
				cout << "It must be three numbers in the line.\n";
				return 1;
			}
		}
	}

//================================================================
//==================ЧАСТЬ 1. КОНЕЦ.===============================
//================================================================
	in.close();
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


	
	ofstream out("res2.txt");
	if (!out)
	{
		cout << "File is not exist.\n";
		return 1;
	}
	

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

	out << summa << "\n";//запись результата
	}

	out.close();
//================================================================
//==================ЧАСТЬ 4. КОНЕЦ.===============================
//================================================================

	return 0;
}