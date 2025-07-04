//
//

//#include "stdafx.h"

#include <cstdlib>
#include <map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef multimap< string, int > VesMap;
vector< int > Tree;
vector< int > MinRasst;
vector< int > Result;
vector< int > Tree1;

VesMap Ves;

string nmbr;

void Prepare(void)
{
	int N, num1, num2, num3, i, Kol, j, l_step, r_step, cop, ip, k; //one_val;
	bool elem_in = false;
	char *str;

	ip = 0;
	Kol = 0;
	j = 0;
	str = new char[30];
	scanf("%s", str);
	N = atoi(str);
	
	Tree.resize(++Kol);	
	for (i = 0; i < (N-1); i++)
	{
		scanf("%s", str);
		num1 = atoi(str);

		scanf("%s", str);
		num2 = atoi(str);

		scanf("%s", str);
		num3 = atoi(str);

		sprintf(str, "%i\0", num1);		// Переводим число в строку
		nmbr = str; 
		nmbr += ' ';
		sprintf(str, "%i\0", num2);
		nmbr += str;
		Ves.insert( VesMap::value_type( nmbr, num3) ); 
		
		sprintf(str, "%i\0", num2);
		nmbr = str; 
		nmbr += ' ';
		sprintf(str, "%i\0", num1);
		nmbr += str;
		Ves.insert( VesMap::value_type( nmbr, num3) ); 

		for (j = 0; j < (Kol - 1); j++)
		{
			if ( Tree.at(j) == num1 )
			{
				elem_in = true;
				break;
			}
		}
		if (!elem_in)		// Если такого элемента не было
		{
			for (j = 0; j < (Kol - 1); j++)
			{
				if ( Tree.at(j) == num2 )
				{
					elem_in = true;

					cop = num1;
					num1 = num2;
					num2 = cop;

					break;
				}
			}
		}
		if ( (elem_in) && (j != Kol-2) )		// Если такой элемент был	
		{										//  и он не является предыдущим
			l_step = Kol - 2; 
			r_step = Kol - 1;
			while ( Tree.at(l_step) != num1 )
			{
				if ( (l_step + 1) != r_step )
				{
					Tree.resize(Kol);
					Tree.at(r_step) = Tree.at(l_step);
					l_step--;
					r_step++;
					
					Kol++;
				}
				else
				{
					l_step--;
				}
			}
			Tree.resize(Kol);
			Tree.at(r_step) = Tree.at(l_step);
			elem_in = false;
			Kol++;

			Tree.resize(Kol);
			Tree.at(++r_step) = num2;
			Kol++;
		}
		else			// Если нет связных элементов
		{
			Tree.resize(Kol);
			if ( (Kol >= 2) && (elem_in) )
			{
				if (Tree.at(Kol-2) != num1)  
				{
					Tree.at(Kol-1) = num1;
				}
				else 
				{
					Tree.at(Kol-1) = num2;
				}
			}
			else if (Kol < 2) 
			{
				Tree.at(Kol-1) = num1;
				Tree.resize(++Kol);
				Tree.at(Kol-1) = num2;
			}
			else if ( (Kol >= 2) && (!elem_in) )
			{
				ip += 2;
				Tree1.resize(ip);
				Tree1.at(ip - 2) = num1;
				Tree1.at(ip - 1) = num2;
				Kol--;
			}
			Kol++;
			elem_in = false;
		}
	}

	int ord;
	for (i = 0; i < (int) Tree1.size() - 2; i += 2)
	{
		if ( Tree1.at(i + 1) != Tree1.at(i + 2) )
		{
			for (j = 0; j < (int) Tree1.size(); j += 2)
			{
				if ( Tree1.at(i + 1) == Tree1.at(j) ) 
				{
					ord = Tree1.at(i + 2);
					Tree1.at(i + 2) = Tree1.at(j);
					Tree1.at(j) = ord;

					ord = Tree1.at(i + 3);
					Tree1.at(i + 3) = Tree1.at(j + 1);
					Tree1.at(j + 1) = ord;

					break;
				}
			}
		}
	}

	while (ip > 0)
	{
		for (k = 0; k < (int) Tree1.size(); k++)
		{
			if (Tree1.at(k) != -1)
			{
				for (j = 0; j < Kol - 1; j++)
				{
					if ( Tree1.at(k) == Tree.at(j) ) 
					{
						elem_in = true;
						break;
					}
				}

				if (elem_in) 	break;
			}
		}
		 
		if ( (k+1) % 2 == 0) 
		{
			num1 = Tree1.at(k);
			num2 = Tree1.at(k - 1);

			Tree1.at(k) = -1;
			Tree1.at(k - 1) = -1;
		}
		else 
		{
			num1 = Tree1.at(k);
			num2 = Tree1.at(k + 1);

			Tree1.at(k) = -1;
			Tree1.at(k + 1) = -1;
		}

		ip -= 2;

		for (j = 0; j < (Kol - 1); j++)
		{
			if ( Tree.at(j) == num1 )
			{
				elem_in = true;
				break;
			}
		}
		if (!elem_in)
		{
			for (j = 0; j < (Kol - 1); j++)
			{
				if ( Tree.at(j) == num2 )
				{
					elem_in = true;

					cop = num1;
					num1 = num2;
					num2 = cop;

					break;
				}
			}
		}
		if ( (elem_in) && (j != Kol-2) )
		{
			l_step = Kol - 2; 
			r_step = Kol - 1;
			while ( Tree.at(l_step) != num1 )
			{
				if ( (l_step + 1) != r_step )
				{
					Tree.resize(Kol);
					Tree.at(r_step) = Tree.at(l_step);
					l_step--;
					r_step++;
					
					Kol++;
				}
				else
				{
					l_step--;
				}
			}
			Tree.resize(Kol);
			Tree.at(r_step) = Tree.at(l_step);
			elem_in = false;
			Kol++;

			Tree.resize(Kol);
			Tree.at(++r_step) = num2;
			Kol++;
		}
		else
		{
			Tree.resize(Kol);
			if ( (Kol >= 2) && (elem_in) )
			{
				if (Tree.at(Kol-2) != num1)  
				{
					Tree.at(Kol-1) = num1;
				}
				else 
				{
					Tree.at(Kol-1) = num2;
				}
			}
			else if (Kol < 2) 
			{
				Tree.at(Kol-1) = num1;
				Tree.resize(++Kol);
				Tree.at(Kol-1) = num2;
			}
			Kol++;
			elem_in = false;
		}
	}
	delete [] str;
}
void Find(void)
{
	int M, i, j, k, num1, num2, indx_num1 = 0, indx_num2 = 0, p, otvet;
	char *str;

	str = new char[30];
	scanf("%s", str);
	M = atoi(str);

	Result.resize(M);
	for (i = 0; i < M; i++)
	{
		scanf("%s", str);
		num1 = atoi(str);

		scanf("%s", str);
		num2 = atoi(str);

		for (j = 0; j < (int) Tree.size(); j++)
		{
			if (Tree.at(j) == num1) 
			{
				indx_num1 = j;
				break;
			}
		}
		for (j = 0; j < (int) Tree.size(); j++)
		{
			if (Tree.at(j) == num2) 
			{
				indx_num2 = j;
				break;
			}
		}

		p = 0;
		if (indx_num2 > indx_num1)
		{
			for (j = indx_num1; j <= indx_num2; j++)
			{
				for (k = j + 1; k <= indx_num2; k++)
				{
					if ( Tree.at(j) == Tree.at(k) ) 
					{
						j = k;
					}
				}
				MinRasst.resize( ++p );
				MinRasst.at(p - 1) = Tree.at(j);
			}
		}
		else 
		{
			for (j = indx_num2; j <= indx_num1; j++)
			{
				for (k = j + 1; k <= indx_num1; k++)
				{
					if ( Tree.at(j) == Tree.at(k) ) 
					{
						j = k;
					}
				}
				MinRasst.resize( ++p );
				MinRasst.at(p - 1) = Tree.at(j);
			}
		}
		
		otvet = 0;
		for (j = 0; (j + 1) < (int) MinRasst.size(); j++)
		{
			sprintf(str, "%i\0", MinRasst.at(j));
			nmbr = str; 
			nmbr += ' ';
			sprintf(str, "%i\0", MinRasst.at(j + 1));
			nmbr += str;

			VesMap::iterator itr = Ves.find(nmbr);
			otvet += itr->second;
		}
		MinRasst.clear();
		Result.at(i) = otvet;
	}
	delete [] str;

	for (i = 0; i < M; i++) 
		printf( "%d\n", Result.at(i) ); 

}
int main(int argc, char* argv[])
{
	Prepare();

	Find();

	return 0;
}