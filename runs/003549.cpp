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
int N,		// Количество магазинов
	L,		// Количество необходимых метров ткани 
	maxF,	// Максимальное количество метров ткани среди магазинов
	schtch; 
int Cost(int kolmetr, Shop *ptr)
{
	// Функция возвращающая цену текущего магазина
	//  за kolmetr (количество метров)

	if (kolmetr >= ptr->R)
			return (kolmetr * ptr->Q);
	else return (kolmetr * ptr->P);
}
int min(int a, int b)
{
	// Функция возвращающая минимальное из двух чисел
	if (a > b) return b;
	else return a;
}
int Calc(int S, Shop *ptr)
{
	// S - метры ткани
	// K - номер магазина

	int  minres = -1, t, upln, res;
	if (ptr->prev == NULL)			
	{
		// Завершаем рекурсию
		if (firstShop->F >= S) 
			 return Cost(S, firstShop);
		else return -1; 
	}
	else 
	{
		upln = min( ptr->F, S );
		for (t = 0; t <= upln; t++)
		{
			// Рекурсивный вызов
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
	// Процедура обработки входного потока
	//

	int i;
	char *str;
	Shop *ptrCopy;

	str  = new char[20];

	scanf("%s", str);
	N = atoi(str);			// Количество магазинов
	scanf("%s", str);
	L = atoi(str);			// Количество метров ткани, которое необходимо купить
	
	maxF = 0;				// Максимальное количество ткани в некотором магазине
	
	// Создаем список магазинов
	endShop = new Shop;

	scanf("%s", str);
	endShop->P = atoi(str);	// Цена за 1 метр (без скидки)
	scanf("%s", str);
	endShop->R = atoi(str);	// Количество метров, больше которых даётся скидка
	scanf("%s", str);
	endShop->Q = atoi(str);	// Цена за 1 метр (со скидкой)
	scanf("%s", str);
	endShop->F = atoi(str);	// Наличие в магазине количества метров ткани
	if (endShop->F > maxF) maxF = endShop->F;	

	endShop->prev = NULL;

	// Проверяем количество магазинов
	if (N > 1) 
	{
		ptrShop = new Shop;
		endShop->prev = ptrShop;

		scanf("%s", str);
		ptrShop->P = atoi(str);		// Цена за 1 метр (без скидки)
		scanf("%s", str);
		ptrShop->R = atoi(str);		// Количество метров, больше которых даётся скидка
		scanf("%s", str);
		ptrShop->Q = atoi(str);		// Цена за 1 метр (со скидкой)
		scanf("%s", str);
		ptrShop->F = atoi(str);		// Наличие в магазине количества метров ткани
		if(ptrShop->F > maxF) maxF = ptrShop->F;

		ptrShop->prev = NULL;

		for (i = 0; i < N-2; i++)
		{
			ptrCopy = ptrShop;
			ptrShop = new Shop;
			ptrCopy->prev = ptrShop;

			scanf("%s", str);
			ptrShop->P = atoi(str);		// Цена за 1 метр (без скидки)
			scanf("%s", str);
			ptrShop->R = atoi(str);		// Количество метров, больше которых даётся скидка
			scanf("%s", str);
			ptrShop->Q = atoi(str);		// Цена за 1 метр (со скидкой)
			scanf("%s", str);
			ptrShop->F = atoi(str);		// Наличие в магазине количества метров ткани
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



