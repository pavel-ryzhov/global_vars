// A_Scaner.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <map>
#include <iostream>
#include <string>

using namespace std;

// Определяем структуру
typedef multimap<string, string> VesMap;

string UniNum,				// Уникальный для каждой цифры номер
	   NUMBER = "";			// Определенное число	

FILE *NumFile, 		// Файл с изображением
	 *Output;		// Выходной файл		

VesMap Ves;

char symb,
	 *NameFile;
int Height = 0,		// Высота цифры в пикселях
	Weight = 0,		// Ширина всех цифр, включая пробелы
	H = 0,			// Общая высота изображения
	W = 0,			// Общая ширина изображения	
	num = 0, 
	WhtNmb = 0, 
	rez = 0;

float	KolWht = 0.0,	// Кол-во светлых пикселей
		KolBlk = 0.0,	// Кол-во тёмных пикселей

		Plot;			// Плотность цифр на изображении,
						//  т.е. "вес" черного пикселя
void Teach(void)
{
	// Процедура обучения системы

	Ves.insert( VesMap::value_type("1110111100000000","0")); // 010

	Ves.insert( VesMap::value_type("0000111011100000","1")); // 007
	Ves.insert( VesMap::value_type("1110111111110000","1")); // 009
	
	Ves.insert( VesMap::value_type("1001000100011101","2")); // 006
	Ves.insert( VesMap::value_type("1001101110101100","2")); // 004
	Ves.insert( VesMap::value_type("0001101110111101","2")); // 003
	Ves.insert( VesMap::value_type("1001101011100111","2")); // 014
	Ves.insert( VesMap::value_type("0010101010001010","2")); // 018
	Ves.insert( VesMap::value_type("0000001011100000","2")); // 017
	
	Ves.insert( VesMap::value_type("1001100111011110","3")); // 004
	Ves.insert( VesMap::value_type("0101110001011110","3")); // 008
	
	Ves.insert( VesMap::value_type("0000000011100010","4")); // 006
	Ves.insert( VesMap::value_type("0010011001110000","4")); // 002
	Ves.insert( VesMap::value_type("0110001001100000","4")); // 011
	Ves.insert( VesMap::value_type("0100110011100100","4")); // 012
	Ves.insert( VesMap::value_type("0010011011110010","4")); // 014

	Ves.insert( VesMap::value_type("0100110111011010","5")); // 003
	Ves.insert( VesMap::value_type("1010100010001100","5")); // 005
	Ves.insert( VesMap::value_type("1100110011011110","5")); // 007
	Ves.insert( VesMap::value_type("0011110010011110","5")); // 008
	Ves.insert( VesMap::value_type("0000000001110110","5")); // 010
	Ves.insert( VesMap::value_type("0000110000010010","5")); // 015
	Ves.insert( VesMap::value_type("0001110011000001","5")); // 016
	Ves.insert( VesMap::value_type("0000110011000010","5")); // 018

	Ves.insert( VesMap::value_type("0110000000000100","6")); // 005
	Ves.insert( VesMap::value_type("0110111100000000","6")); // 010   
	Ves.insert( VesMap::value_type("0110011101000110","6")); // 011
	Ves.insert( VesMap::value_type("0110111001100110","6")); // 013

	Ves.insert( VesMap::value_type("1000101011101000","7")); // 005
	Ves.insert( VesMap::value_type("0000001111001000","7")); // 004
	Ves.insert( VesMap::value_type("1000101111001000","7")); // 001
	Ves.insert( VesMap::value_type("1011101111001000","7")); // 009
	Ves.insert( VesMap::value_type("1000111011101000","7")); // 014
	
	Ves.insert( VesMap::value_type("0111110111100111","8")); // 002
	Ves.insert( VesMap::value_type("0110010001001110","8")); // 008
	Ves.insert( VesMap::value_type("0111011111101010","8")); // 011
	Ves.insert( VesMap::value_type("1110111011101110","8")); // 012
	Ves.insert( VesMap::value_type("0111110001010010","8")); // 016
	Ves.insert( VesMap::value_type("0010111011101000","8")); // 018
	Ves.insert( VesMap::value_type("0000011001100000","8")); // 017

	Ves.insert( VesMap::value_type("1110000000001110","9")); // 006
	Ves.insert( VesMap::value_type("1101101110111110","9")); // 001
	Ves.insert( VesMap::value_type("0100111111110110","9")); // 013
	Ves.insert( VesMap::value_type("0100100010001111","9")); // 015
	Ves.insert( VesMap::value_type("0000011011100000","9")); // 017

		//979 001!			650 010!
		//484 002!			864 011!
		//552 003!			448 012!
		//723 004!			966 013!
		//576 005!			247 014!
		//294 006!			959 015!
		//551 007!			858 016!
		//853 008!			892 017!
		//117 009!			852 018!
}
void OprPar(FILE *NumFile)
{
	// Определяем плотность цифр 
	rewind(NumFile);
	symb = getc(NumFile);
	while (symb != EOF) 
	{
		switch(symb)
		{
			case '.':  KolWht += 1.0; break;
			case '%':  KolWht += 0.5; break;
			case '#':  KolBlk += 0.5; break;
			case '@':  KolBlk += 1.0; break;
			case '\n': Height++; break;
		}
		symb = getc(NumFile);
	}
	Plot = (KolWht / KolBlk) * 0.34;	
	KolWht = 0.0;
	KolBlk = 0.0;

	// Определяем ширину цифр, включая пробелы
	rewind(NumFile);		// Устанавливаем указатель на начало 
	symb = getc(NumFile);
	while ( (symb != '\n') && (symb != EOF) ) 
	{
		Weight++;
		symb = getc(NumFile);
	}

	// Определяем высоту в пикселях
	W = Weight;
	H = Height;
	Height = Height - 10;		// 10 - это константа, некоторое		
	Weight = Weight - 10;		//  расстояние до цифр

}
int WhiteRow(FILE *NumFile, int num)
{
	int _h = 1;
	rewind(NumFile);
	while (num <= W )
	{
		fseek(NumFile, num, SEEK_SET);
		symb = getc(NumFile);
		while ( (_h < H) && (symb != EOF) )
		{
			if (symb == '@') 
			{
				rewind(NumFile);
				return num;
			}
			fseek(NumFile, W + 1, SEEK_CUR);
			symb = getc(NumFile);
			_h++;
		}
		_h = 0;
		num++;
	}
	rewind(NumFile);
	return num;
}
int RasstNum(FILE *NumFile, int num)
{
	int _h = 1, num_copy = num;
	bool end_cycle = false,
		 b = true;
	rewind(NumFile);
	while ( (num <= W ) && (!end_cycle) )
	{
		fseek(NumFile, num, SEEK_SET);
		symb = getc(NumFile);
		while ( (_h < H) && (symb != EOF) )
		{
			if (symb == '@')
			{
				b = false;
				break;
			}
			fseek(NumFile, W + 1, SEEK_CUR);
			symb = getc(NumFile);
			_h++;
		}
		if (b) end_cycle = true;
		else b = true;
		_h = 0;
		num++;
	}
	rewind(NumFile);
	return (num - num_copy);
}
void OprNUM(void)
{
	for (int r = 0; r < 3; r++)
	{
		rewind(NumFile);					// Устанавливаем указатель на начало
		num = WhiteRow(NumFile, num);		// Проход мимо пробела
		WhtNmb = RasstNum(NumFile, num);	// Ширина цифры

		if (WhtNmb > 2*Weight / 3 - 1) WhtNmb = Weight / 3; // Если не будет пробельного места
		
		for (int g = 0; g < 4; g++)			// Цикл по столбцам
		{
			fseek(NumFile, 5*W + 8, SEEK_SET);
			symb = getc(NumFile);

			for (int k = 0; k < 4; k++)			// Цикл по строкам (кол-во повторений)
			{
				for (int i = 0; i < (Height / 4 + 1); i++)		// Цикл по строкам 
				{	
					fseek(NumFile, num, SEEK_CUR);
					for (int j = 0; j < (WhtNmb / 4); j++)		// Цикл по столбцам по символьно 
					{	
						symb = getc(NumFile);
						switch(symb)
						{
							case '.': KolWht += 0.7; break;
							case '%': KolBlk += 0.2; break;
							case '#': KolBlk += 0.7; break;
							case '@': KolBlk += 1.0; break;
						}
					}
					fseek(NumFile, ( W + 1 - num - (WhtNmb / 4) ) , SEEK_CUR);
					symb = getc(NumFile);
				}
				KolBlk *= Plot;
				if (KolWht > KolBlk) UniNum += '0' ;
				else UniNum += '1';
			
				KolWht = 0;
				KolBlk = 0;
			}
			rez = (WhtNmb / 4);
			num += rez;
		}
		num = num - 4*rez + WhtNmb;
		VesMap::iterator itr = Ves.find(UniNum);		// Поиск по уникальному ключу

		if ( itr != Ves.end() ) NUMBER += itr->second;
		else NUMBER += "!";
		UniNum.clear();
	}
	//cout << NUMBER;
}
int main(int argc, char* argv[])
{
	int LngtNm = 0;
	Teach();		// Обучение системы
	
	puts("Input NAME file:");
	NameFile = new char[20];
	gets(NameFile);

	if ( (NumFile = fopen(NameFile, "r+t")) != NULL )		// Открываем файл
    {  	
		OprPar(NumFile);		// Определяем основные параметры файла
		OprNUM();				// Определяем число	
		fclose(NumFile);		
		
		//strcat(NameFile, ".a");	
		
		while (NameFile[LngtNm] != '\0') LngtNm++;
		NameFile[LngtNm] = '.';
		NameFile[LngtNm + 1] = 'a';
		NameFile[LngtNm + 2] = '\0';

		Output = fopen(NameFile, "w+t");
		for (rez = 0; rez < 3; rez++) putc(NUMBER[rez], Output);
		fclose(Output);
    }
	else puts("Error file or name");
	delete [] NameFile;
	return 0;
}
