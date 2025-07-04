//
//

//#include "stdafx.h"

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

typedef multimap< int, int > VesMap;
vector< int > Tree;
vector< int > MinRasst;
vector< int > Result; 

VesMap Ves;


void Prepare(void)
{
	int N, num1, num2, num3, i, Kol, j, l_step, r_step, cop;
	bool elem_in = false;
	char *str;

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

		Ves.insert( VesMap::value_type( (num1*10 + num2), num3) ); 
		Ves.insert( VesMap::value_type( (num2*10 + num1), num3) ); 
		
		for (j = 0; j < (Kol - 1); j++)
		{
			if ( Tree.at(j) == num1 )
			{
				elem_in = true;
				break;
			}
		}
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
			if ( (Kol - 2) > 0 )
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
			else 
			{
				Tree.at(Kol-1) = num1;
				Tree.resize(++Kol);
				Tree.at(Kol-1) = num2;
			}
			Kol++;
		}
	}
	delete [] str;
}
void Find(void)
{
	int M, i, j, k, num1, num2, indx_num1 = 0, indx_num2 = 0, p, otvet, rebr;
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
			rebr = MinRasst.at(j)*10 + MinRasst.at(j + 1);

			VesMap::iterator itr = Ves.find(rebr);
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