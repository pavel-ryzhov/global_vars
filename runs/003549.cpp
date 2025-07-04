// 2_Mascarad.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <cstdlib>

using namespace std;

struct Shop 
{	
	int P, R, Q, F;	
	Shop *prev;	
};

Shop *firstShop, *ptrShop, *endShop;
int N,		// ���������� ���������
	L,		// ���������� ����������� ������ ����� 
	maxF,	// ������������ ���������� ������ ����� ����� ���������
	schtch; 
int Cost(int kolmetr, Shop *ptr)
{
	// ������� ������������ ���� �������� ��������
	//  �� kolmetr (���������� ������)

	if (kolmetr >= ptr->R)
			return (kolmetr * ptr->Q);
	else return (kolmetr * ptr->P);
}
int min(int a, int b)
{
	// ������� ������������ ����������� �� ���� �����
	if (a > b) return b;
	else return a;
}
int Calc(int S, Shop *ptr)
{
	// S - ����� �����
	// K - ����� ��������

	int  minres = -1, t, upln, res;
	if (ptr->prev == NULL)			
	{
		// ��������� ��������
		if (firstShop->F >= S) 
			 return Cost(S, firstShop);
		else return -1; 
	}
	else 
	{
		upln = min( ptr->F, S );
		for (t = 0; t <= upln; t++)
		{
			// ����������� �����
			res = Calc(S - t, ptr->prev);
			if ( res != -1) 
			{
				res += Cost(t, ptr);
				if ( res < minres) minres = res;
				else if (minres == -1) minres = res;
			}
 		}
		return minres;
	}
}
void Input(void)
{
	// ��������� ��������� �������� ������
	//

	int i;
	char *str;
	Shop *ptrCopy;

	str  = new char[20];

	scanf("%s", str);
	N = atoi(str);			// ���������� ���������
	scanf("%s", str);
	L = atoi(str);			// ���������� ������ �����, ������� ���������� ������
	
	maxF = 0;				// ������������ ���������� ����� � ��������� ��������
	
	// ������� ������ ���������
	endShop = new Shop;

	scanf("%s", str);
	endShop->P = atoi(str);	// ���� �� 1 ���� (��� ������)
	scanf("%s", str);
	endShop->R = atoi(str);	// ���������� ������, ������ ������� ����� ������
	scanf("%s", str);
	endShop->Q = atoi(str);	// ���� �� 1 ���� (�� �������)
	scanf("%s", str);
	endShop->F = atoi(str);	// ������� � �������� ���������� ������ �����
	if (endShop->F > maxF) maxF = endShop->F;	

	endShop->prev = NULL;

	// ��������� ���������� ���������
	if (N > 1) 
	{
		ptrShop = new Shop;
		endShop->prev = ptrShop;

		scanf("%s", str);
		ptrShop->P = atoi(str);		// ���� �� 1 ���� (��� ������)
		scanf("%s", str);
		ptrShop->R = atoi(str);		// ���������� ������, ������ ������� ����� ������
		scanf("%s", str);
		ptrShop->Q = atoi(str);		// ���� �� 1 ���� (�� �������)
		scanf("%s", str);
		ptrShop->F = atoi(str);		// ������� � �������� ���������� ������ �����
		if(ptrShop->F > maxF) maxF = ptrShop->F;

		ptrShop->prev = NULL;

		for (i = 0; i < N-2; i++)
		{
			ptrCopy = ptrShop;
			ptrShop = new Shop;
			ptrCopy->prev = ptrShop;

			scanf("%s", str);
			ptrShop->P = atoi(str);		// ���� �� 1 ���� (��� ������)
			scanf("%s", str);
			ptrShop->R = atoi(str);		// ���������� ������, ������ ������� ����� ������
			scanf("%s", str);
			ptrShop->Q = atoi(str);		// ���� �� 1 ���� (�� �������)
			scanf("%s", str);
			ptrShop->F = atoi(str);		// ������� � �������� ���������� ������ �����
			if(ptrShop->F > maxF) maxF =ptrShop->F;

			ptrShop->prev = NULL;
		}

		firstShop = ptrShop;
	}
	else firstShop = endShop;
	delete [] str;
}
int main(int argc, char* argv[])
{
	int minres = -1, res;

	Input();
	
	for (int i = L; i <= ( L + maxF - 1 ); i++)
	{
		res = Calc(i, endShop);
		if ( res != -1) 
		{
			if (res < minres ) minres = res;
			else if (minres == -1) minres = res;
		}
	}
	printf("\n%d\n", minres);
	scanf("\n");
	return 0;
}



