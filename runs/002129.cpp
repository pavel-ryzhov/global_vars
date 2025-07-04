// A_Scaner.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Определяем структуру
typedef multimap< string, string > VesMap;
vector< vector< char > > Input;		// Матрица изображения

string UniNum,				// Уникальный для каждой цифры номер
	   NUMBER = "";			// Определенное число	

VesMap Ves;

int H,			// Высота в пикселях
	W,			// Ширина в пикселях
	numV,
	numH,
	WhtNmb , 
	rez;

float KolWht,	 // Кол-во светлых пикселей
	  KolBlk,	 // Кол-во тёмных пикселей
	  Plot;	 // Плотность цифр на изображении, т.е. "вес" черного пикселя

void Teach(void)
{
	// Процедура обучения системы

	Ves.insert( VesMap::value_type("1110111100000000","0")); // 010
	Ves.insert( VesMap::value_type("1110101110011111","0")); // 021 
	Ves.insert( VesMap::value_type("1110101110011110","0")); // 026 
	Ves.insert( VesMap::value_type("1110100110011110","0")); // 026(2)
	Ves.insert( VesMap::value_type("1110100110011011","0")); // 027 
	Ves.insert( VesMap::value_type("1110100110011111","0")); // 027(2)
	Ves.insert( VesMap::value_type("1110000010001110","0")); // 030 
	Ves.insert( VesMap::value_type("1111100110011110","0")); // 030(2)
	Ves.insert( VesMap::value_type("0110111111110110","0")); // 033
	Ves.insert( VesMap::value_type("1110111011101110","0")); // 036
	Ves.insert( VesMap::value_type("1111100110011111","0")); // 055
	Ves.insert( VesMap::value_type("1110100110000110","0")); // 0
	Ves.insert( VesMap::value_type("1111101110011111","0")); // 0
	Ves.insert( VesMap::value_type("1110000110011110","0")); // 0
	Ves.insert( VesMap::value_type("1110100110111110","0")); // 0

	Ves.insert( VesMap::value_type("0000111011100000","1")); // 007
	Ves.insert( VesMap::value_type("1110111111110000","1")); // 009
	Ves.insert( VesMap::value_type("1000111111110000","1")); // 020
	Ves.insert( VesMap::value_type("0000011111110000","1")); // 024
	Ves.insert( VesMap::value_type("0000000011110000","1")); // 024(2)
	Ves.insert( VesMap::value_type("0000011011110000","1")); // 024(3)
	Ves.insert( VesMap::value_type("0100100010001111","1")); // 025
	Ves.insert( VesMap::value_type("0000000010001111","1")); // 025(2)
	Ves.insert( VesMap::value_type("0000100011111111","1")); // 028
	Ves.insert( VesMap::value_type("0000111111110000","1")); // 029
	Ves.insert( VesMap::value_type("0000111111110001","1")); // 029(2)
	Ves.insert( VesMap::value_type("1000111011111111","1")); // 032
	Ves.insert( VesMap::value_type("0000111111100000","1")); // 044
	Ves.insert( VesMap::value_type("1000100011111111","1")); // 045
	Ves.insert( VesMap::value_type("0101110111110001","1")); // 0
	Ves.insert( VesMap::value_type("1000100010001111","1")); // 0
	Ves.insert( VesMap::value_type("1001100111110001","1")); // 0
	Ves.insert( VesMap::value_type("0000100011101111","1")); // 0
	Ves.insert( VesMap::value_type("1111111111111111","1")); // 0
	Ves.insert( VesMap::value_type("1000100011101111","1")); // 0
	Ves.insert( VesMap::value_type("1001111111110001","1")); // 0
	Ves.insert( VesMap::value_type("1010111011100010","1")); // 0
	Ves.insert( VesMap::value_type("1000111111110001","1")); // 0
	Ves.insert( VesMap::value_type("1000111111111001","1")); // 0
	Ves.insert( VesMap::value_type("0000100111111111","1")); // 0
	Ves.insert( VesMap::value_type("0100110010001111","1")); // 0
	Ves.insert( VesMap::value_type("0100010001111110","1")); // 0
	
	Ves.insert( VesMap::value_type("1001000100011101","2")); // 006
	Ves.insert( VesMap::value_type("1001101110101100","2")); // 004
	Ves.insert( VesMap::value_type("0001101110111101","2")); // 003
	Ves.insert( VesMap::value_type("1001101011100111","2")); // 014
	Ves.insert( VesMap::value_type("0010101010001010","2")); // 018
	Ves.insert( VesMap::value_type("0000001011100000","2")); // 017
	Ves.insert( VesMap::value_type("1101000100111101","2")); // 029
	Ves.insert( VesMap::value_type("1001001100011101","2")); // 031
	Ves.insert( VesMap::value_type("1001001100111101","2")); // 031(2)
	Ves.insert( VesMap::value_type("1101001111111101","2")); // 031(3)
	Ves.insert( VesMap::value_type("1001001111010100","2")); // 033
	Ves.insert( VesMap::value_type("1001001111010101","2")); // 033(2)
	Ves.insert( VesMap::value_type("1011101111011101","2")); // 039
	Ves.insert( VesMap::value_type("1011101111111101","2")); // 039(2)
	Ves.insert( VesMap::value_type("1001001111011101","2")); // 041
	Ves.insert( VesMap::value_type("1001101111011101","2")); // 041(2)
	Ves.insert( VesMap::value_type("0010001011001100","2")); // 042
	Ves.insert( VesMap::value_type("1010111011101110","2")); // 042(2)
	Ves.insert( VesMap::value_type("1001101110111101","2")); // 045
	Ves.insert( VesMap::value_type("1001101111111101","2")); // 047
	Ves.insert( VesMap::value_type("1010101011101100","2")); // 049
	Ves.insert( VesMap::value_type("1011101111111111","2")); // 049(2)
	Ves.insert( VesMap::value_type("1011101110011101","2")); // 051
	Ves.insert( VesMap::value_type("1010101011101110","2")); // 053
	Ves.insert( VesMap::value_type("1101101110111101","2")); // 0
	Ves.insert( VesMap::value_type("1001101111111111","2")); // 0
	Ves.insert( VesMap::value_type("1001101111111100","2")); // 0
	Ves.insert( VesMap::value_type("1001100111111101","2")); // 0
	Ves.insert( VesMap::value_type("1001101000101100","2")); // 0
	Ves.insert( VesMap::value_type("1001101110011101","2")); // 0
	Ves.insert( VesMap::value_type("0001001110001100","2")); // 0
	Ves.insert( VesMap::value_type("0001101111111101","2")); // 0
	Ves.insert( VesMap::value_type("0000101111111101","2")); // 0
	Ves.insert( VesMap::value_type("0001101110111100","2")); // 0
	Ves.insert( VesMap::value_type("1001000110111101","2")); // 0
	Ves.insert( VesMap::value_type("1001100111011101","2")); // 0
	Ves.insert( VesMap::value_type("1001101111011100","2")); // 0
	Ves.insert( VesMap::value_type("1101001111011101","2")); // 0
	Ves.insert( VesMap::value_type("1001101111110101","2")); // 0
	Ves.insert( VesMap::value_type("0001101110101100","2")); // 0
	Ves.insert( VesMap::value_type("1001101110111111","2")); // 0
	Ves.insert( VesMap::value_type("1001100110011101","2")); // 0
	Ves.insert( VesMap::value_type("1101101111111101","2")); // 0
	Ves.insert( VesMap::value_type("1001100110111101","2")); // 0
	Ves.insert( VesMap::value_type("1011101011001101","2")); // 0

	Ves.insert( VesMap::value_type("1001100111011110","3")); // 004
	Ves.insert( VesMap::value_type("0101110001011110","3")); // 008
	Ves.insert( VesMap::value_type("1001110111011111","3")); // 023
	Ves.insert( VesMap::value_type("1001100111001111","3")); // 024
	Ves.insert( VesMap::value_type("1001000111001111","3")); // 024(2)
	Ves.insert( VesMap::value_type("1011100111011111","3")); // 027
	Ves.insert( VesMap::value_type("1001110111011110","3")); // 032
	Ves.insert( VesMap::value_type("1101110111111111","3")); // 032(2)
	Ves.insert( VesMap::value_type("1001100111011111","3")); // 037
	Ves.insert( VesMap::value_type("0001100111011111","3")); // 043
	Ves.insert( VesMap::value_type("0000000011011010","3")); // 048
	Ves.insert( VesMap::value_type("0000110111011010","3")); // 048(2)
	Ves.insert( VesMap::value_type("1000110111011010","3")); // 048(3)
	Ves.insert( VesMap::value_type("0001110111010010","3")); // 0
	Ves.insert( VesMap::value_type("1001100111111111","3")); // 0
	Ves.insert( VesMap::value_type("1011110111011111","3")); // 0
	Ves.insert( VesMap::value_type("1001000011011111","3")); // 0
	Ves.insert( VesMap::value_type("1011100111011110","3")); // 0
	Ves.insert( VesMap::value_type("0001110111011111","3")); // 0
	Ves.insert( VesMap::value_type("1001010011110010","3")); // 0
	Ves.insert( VesMap::value_type("1001100111001110","3")); // 0
	Ves.insert( VesMap::value_type("1001110111011101","3")); // 0
	Ves.insert( VesMap::value_type("1011000011011111","3")); // 0
	Ves.insert( VesMap::value_type("0000100111011110","3")); // 0
	Ves.insert( VesMap::value_type("1011100101001111","3")); // 0
	Ves.insert( VesMap::value_type("1011100111111111","3")); // 0
	Ves.insert( VesMap::value_type("1001100111111010","3")); // 0
	Ves.insert( VesMap::value_type("1000100111111010","3")); // 0
	Ves.insert( VesMap::value_type("0001100111011110","3")); // 0

	Ves.insert( VesMap::value_type("0000000011100010","4")); // 006
	Ves.insert( VesMap::value_type("0010011001110000","4")); // 002
	Ves.insert( VesMap::value_type("0110001001100000","4")); // 011
	Ves.insert( VesMap::value_type("0100110011100100","4")); // 012
	Ves.insert( VesMap::value_type("0010011011110010","4")); // 014
	Ves.insert( VesMap::value_type("0010010011101111","4")); // 021 
	Ves.insert( VesMap::value_type("0010011011101111","4")); // 022
	Ves.insert( VesMap::value_type("0010000011110000","4")); // 0
	Ves.insert( VesMap::value_type("0010010011111111","4")); // 034 
	Ves.insert( VesMap::value_type("0110000011110000","4")); // 035
	Ves.insert( VesMap::value_type("0110001011110010","4")); // 035(2)
	Ves.insert( VesMap::value_type("0010010011101110","4")); // 036
	Ves.insert( VesMap::value_type("0010011011101110","4")); // 036(2)
	Ves.insert( VesMap::value_type("0010010011110010","4")); // 040
	Ves.insert( VesMap::value_type("0110011011110010","4")); // 040(2)
	Ves.insert( VesMap::value_type("0010011011111111","4")); // 043
	Ves.insert( VesMap::value_type("0110011010101111","4")); // 046
	Ves.insert( VesMap::value_type("0110011011101111","4")); // 046(2)
	Ves.insert( VesMap::value_type("0010011010101111","4")); // 050
	Ves.insert( VesMap::value_type("0010011010111111","4")); // 055
	Ves.insert( VesMap::value_type("0010010010111111","4")); // 055(2)
	Ves.insert( VesMap::value_type("0010011011111110","4")); // 0
	Ves.insert( VesMap::value_type("0110111111110011","4")); // 0
	Ves.insert( VesMap::value_type("0110111011110010","4")); // 0
	Ves.insert( VesMap::value_type("1100110001111111","4")); // 0
	Ves.insert( VesMap::value_type("1100100001111111","4")); // 0
	Ves.insert( VesMap::value_type("0010011011100010","4")); // 0
	Ves.insert( VesMap::value_type("0010001011111110","4")); // 0
	Ves.insert( VesMap::value_type("0110111010111111","4")); // 0
	Ves.insert( VesMap::value_type("0010011011111010","4")); // 0
	Ves.insert( VesMap::value_type("0110111010101111","4")); // 0
	Ves.insert( VesMap::value_type("0010111010101111","4")); // 0
	Ves.insert( VesMap::value_type("0110101000111110","4")); // 0
	Ves.insert( VesMap::value_type("0110101011110010","4")); // 0

	Ves.insert( VesMap::value_type("0100110111011010","5")); // 003
	Ves.insert( VesMap::value_type("1010100010001100","5")); // 005
	Ves.insert( VesMap::value_type("1100110011011110","5")); // 007
	Ves.insert( VesMap::value_type("0011110010011110","5")); // 008
	Ves.insert( VesMap::value_type("0000000001110110","5")); // 010
	Ves.insert( VesMap::value_type("0000110000010010","5")); // 015
	Ves.insert( VesMap::value_type("0001110011000001","5")); // 016
	Ves.insert( VesMap::value_type("0000110011000010","5")); // 018
	Ves.insert( VesMap::value_type("0101110111011110","5")); // 021	
	Ves.insert( VesMap::value_type("1101110111011110","5")); // 022	
	Ves.insert( VesMap::value_type("1110110101010110","5")); // 028
	Ves.insert( VesMap::value_type("1110110111011111","5")); // 028(2)
	Ves.insert( VesMap::value_type("1110100010001111","5")); // 030
	Ves.insert( VesMap::value_type("1111100010001111","5")); // 030(2)
	Ves.insert( VesMap::value_type("1111100011011111","5")); // 030(3)
	Ves.insert( VesMap::value_type("1101110111110110","5")); // 032
	Ves.insert( VesMap::value_type("1101110111111110","5")); // 032(2)
	Ves.insert( VesMap::value_type("1101100011011110","5")); // 034
	Ves.insert( VesMap::value_type("1101110111010110","5")); // 039
	Ves.insert( VesMap::value_type("1101110011001111","5")); // 040
	Ves.insert( VesMap::value_type("1101110111011111","5")); // 040(2)
	Ves.insert( VesMap::value_type("1110100011010010","5")); // 044
	Ves.insert( VesMap::value_type("1110100011010110","5")); // 044(2)
	Ves.insert( VesMap::value_type("1101110111011011","5")); // 047
	Ves.insert( VesMap::value_type("1111110111010011","5")); // 055
	Ves.insert( VesMap::value_type("1111000101010011","5")); // 055(2)
	Ves.insert( VesMap::value_type("0101110111001111","5")); // 0
	Ves.insert( VesMap::value_type("1111100011011110","5")); // 0
	Ves.insert( VesMap::value_type("1111110111011110","5")); // 0
	Ves.insert( VesMap::value_type("0001110011010010","5")); // 0
	Ves.insert( VesMap::value_type("1101110001010011","5")); // 0
	Ves.insert( VesMap::value_type("1100110001010011","5")); // 0
	Ves.insert( VesMap::value_type("1101110111010111","5")); // 0
	Ves.insert( VesMap::value_type("0101110111011111","5")); // 0
	Ves.insert( VesMap::value_type("1101110111011010","5")); // 0
	Ves.insert( VesMap::value_type("0001110111011010","5")); // 0
	
	Ves.insert( VesMap::value_type("0110000000000100","6")); // 005
	Ves.insert( VesMap::value_type("0110111100000000","6")); // 010   
	Ves.insert( VesMap::value_type("0110011101000110","6")); // 011
	Ves.insert( VesMap::value_type("0110111001100110","6")); // 013
	Ves.insert( VesMap::value_type("1110000000001110","6")); // 030
	Ves.insert( VesMap::value_type("1110110100001111","6")); // 030(2)
	Ves.insert( VesMap::value_type("1110100100001111","6")); // 030(3)
	Ves.insert( VesMap::value_type("1111110111011011","6")); // 037
	Ves.insert( VesMap::value_type("1110111001001110","6")); // 038
	Ves.insert( VesMap::value_type("1110111011011110","6")); // 038(2)
	Ves.insert( VesMap::value_type("0110110001000110","6")); // 041
	Ves.insert( VesMap::value_type("0110110111010111","6")); // 041(2)
	Ves.insert( VesMap::value_type("0110110111000110","6")); // 041(3)
	Ves.insert( VesMap::value_type("1110100010001010","6")); // 044
	Ves.insert( VesMap::value_type("1110110111011101","6")); // 057
	Ves.insert( VesMap::value_type("0111110111010011","6")); // 058
	Ves.insert( VesMap::value_type("0111110111011111","6")); // 0
	Ves.insert( VesMap::value_type("1111110111011101","6")); // 0
	Ves.insert( VesMap::value_type("0110110111011111","6")); // 0
	Ves.insert( VesMap::value_type("0110111011011110","6")); // 0
	Ves.insert( VesMap::value_type("0110110111010010","6")); // 0
	Ves.insert( VesMap::value_type("1111110101011111","6")); // 0
	Ves.insert( VesMap::value_type("1110110101011111","6")); // 0
	Ves.insert( VesMap::value_type("0110110100001111","6")); // 0
	Ves.insert( VesMap::value_type("0110110111011011","6")); // 0
	Ves.insert( VesMap::value_type("0110100111010111","6")); // 0
	Ves.insert( VesMap::value_type("0110111100001111","6")); // 0
	Ves.insert( VesMap::value_type("1110110110011111","6")); // 0
	Ves.insert( VesMap::value_type("1110110011010110","6")); // 0
	Ves.insert( VesMap::value_type("0111110111010010","6")); // 0
	Ves.insert( VesMap::value_type("0111110111010111","6")); // 0
	Ves.insert( VesMap::value_type("0110110110000100","6")); // 0
	Ves.insert( VesMap::value_type("0111110100000011","6")); // 0
	Ves.insert( VesMap::value_type("0111110111000111","6")); // 0
	Ves.insert( VesMap::value_type("0110010110111011","6")); // 0
	Ves.insert( VesMap::value_type("1111111100001011","6")); // 0

	Ves.insert( VesMap::value_type("1000101011101000","7")); // 005
	Ves.insert( VesMap::value_type("0000001111001000","7")); // 004
	Ves.insert( VesMap::value_type("1000101111001000","7")); // 001
	Ves.insert( VesMap::value_type("1011101111001000","7")); // 009
	Ves.insert( VesMap::value_type("1000111011101000","7")); // 014
	Ves.insert( VesMap::value_type("1000101111101000","7")); // 021 
	Ves.insert( VesMap::value_type("1000101111101100","7")); // 021(2)
	Ves.insert( VesMap::value_type("1000100111101100","7")); // 022
	Ves.insert( VesMap::value_type("1000101011001000","7")); // 046
	Ves.insert( VesMap::value_type("1000111011001000","7")); // 046(2)
	Ves.insert( VesMap::value_type("1000111111001000","7")); // 046(3)
	Ves.insert( VesMap::value_type("1000100011111100","7")); // 052
	Ves.insert( VesMap::value_type("1000100111111100","7")); // 052(2)
	Ves.insert( VesMap::value_type("0000000111101000","7")); // 058
	Ves.insert( VesMap::value_type("1001101111101100","7")); // 059
	Ves.insert( VesMap::value_type("1000100010111110","7")); // 0
	Ves.insert( VesMap::value_type("1001101011001000","7")); // 0
	Ves.insert( VesMap::value_type("1000100010101100","7")); // 0
	Ves.insert( VesMap::value_type("1000100111101000","7")); // 0
	Ves.insert( VesMap::value_type("1000100110111110","7")); // 0
	Ves.insert( VesMap::value_type("1000001111101100","7")); // 0
	Ves.insert( VesMap::value_type("1000101111111000","7")); // 0
	Ves.insert( VesMap::value_type("1011111011001000","7")); // 0
	Ves.insert( VesMap::value_type("1000100110111100","7")); // 0
	Ves.insert( VesMap::value_type("1010111010001000","7")); // 0
	
	Ves.insert( VesMap::value_type("0111110111100111","8")); // 002
	Ves.insert( VesMap::value_type("0110010001001110","8")); // 008
	Ves.insert( VesMap::value_type("0111011111101010","8")); // 011
	Ves.insert( VesMap::value_type("0111110001010010","8")); // 016
	Ves.insert( VesMap::value_type("0010111011101000","8")); // 018
	Ves.insert( VesMap::value_type("0000011001100000","8")); // 017
	Ves.insert( VesMap::value_type("1110110001001110","8")); // 021
	Ves.insert( VesMap::value_type("1111110111101111","8")); // 022
	Ves.insert( VesMap::value_type("1111110111111111","8")); // 023
	Ves.insert( VesMap::value_type("1111110111001110","8")); // 024
	Ves.insert( VesMap::value_type("1110111111011111","8")); // 026
	Ves.insert( VesMap::value_type("0010110001100010","8")); // 033
	Ves.insert( VesMap::value_type("1110110001101010","8")); // 033(2)
	Ves.insert( VesMap::value_type("1111010001001110","8")); // 034
	Ves.insert( VesMap::value_type("1111110001001111","8")); // 034(2)
	Ves.insert( VesMap::value_type("1111010001001111","8")); // 035
	Ves.insert( VesMap::value_type("1111110111001111","8")); // 035(2)
	Ves.insert( VesMap::value_type("1111110111011111","8")); // 035(3)
	Ves.insert( VesMap::value_type("1110110011001110","8")); // 036
	Ves.insert( VesMap::value_type("1110110011101110","8")); // 036(2)
	Ves.insert( VesMap::value_type("1110110011011110","8")); // 036(3)
	Ves.insert( VesMap::value_type("1110111111011110","8")); // 038
	Ves.insert( VesMap::value_type("1110110111011110","8")); // 051
	Ves.insert( VesMap::value_type("1111110101001111","8")); // 056
	Ves.insert( VesMap::value_type("1110110100001101","8")); // 0
	Ves.insert( VesMap::value_type("1110110000001101","8")); // 0
	Ves.insert( VesMap::value_type("1111110001011110","8")); // 0
	Ves.insert( VesMap::value_type("1111110111011010","8")); // 0
	Ves.insert( VesMap::value_type("1010110111011010","8")); // 0
	Ves.insert( VesMap::value_type("1111110111111011","8")); // 0
	Ves.insert( VesMap::value_type("1111010011001110","8")); // 0
	Ves.insert( VesMap::value_type("1111010001001011","8")); // 0
	Ves.insert( VesMap::value_type("1110010001001110","8")); // 0
	Ves.insert( VesMap::value_type("1111010011101111","8")); // 0
	Ves.insert( VesMap::value_type("1111010011111111","8")); // 0
	Ves.insert( VesMap::value_type("1111110011011010","8")); // 0
	Ves.insert( VesMap::value_type("1111010101001111","8")); // 0
	Ves.insert( VesMap::value_type("1111111100001111","8")); // 0
								  
	Ves.insert( VesMap::value_type("1101101110111110","9")); // 001
	Ves.insert( VesMap::value_type("0100111111110110","9")); // 013
	Ves.insert( VesMap::value_type("0000011011100000","9")); // 017
	Ves.insert( VesMap::value_type("1101101110111111","9")); // 025
	Ves.insert( VesMap::value_type("1101000000001110","9")); // 029
	Ves.insert( VesMap::value_type("1101100000001110","9")); // 029(2)
	Ves.insert( VesMap::value_type("1101001000001110","9")); // 031
	Ves.insert( VesMap::value_type("1101001100111110","9")); // 031(2)
	Ves.insert( VesMap::value_type("1101001100111111","9")); // 031(3)
	Ves.insert( VesMap::value_type("1100100110111110","9")); // 040
	Ves.insert( VesMap::value_type("1100100111111110","9")); // 040(2)
	Ves.insert( VesMap::value_type("1100110110011110","9")); // 041
	Ves.insert( VesMap::value_type("1100110111011110","9")); // 042
	Ves.insert( VesMap::value_type("1100110111111110","9")); // 042(2)
	Ves.insert( VesMap::value_type("1100101110101100","9")); // 045
	Ves.insert( VesMap::value_type("1100101110101110","9")); // 045(2)
	Ves.insert( VesMap::value_type("1100111110101110","9")); // 045(3)
	Ves.insert( VesMap::value_type("1111101110111111","9")); // 050
	Ves.insert( VesMap::value_type("1110111110011110","9")); // 051
	Ves.insert( VesMap::value_type("1100111011101110","9")); // 054
	Ves.insert( VesMap::value_type("1100111110111111","9")); // 0	
	Ves.insert( VesMap::value_type("1101100110111110","9")); // 0
	Ves.insert( VesMap::value_type("1110110110011110","9")); // 0
	Ves.insert( VesMap::value_type("1100100110011110","9")); // 0
	Ves.insert( VesMap::value_type("1100101111111110","9")); // 0
	Ves.insert( VesMap::value_type("1101000000001111","9")); // 0
	Ves.insert( VesMap::value_type("1100100100111110","9")); // 0
	Ves.insert( VesMap::value_type("1100101110111110","9")); // 0
	Ves.insert( VesMap::value_type("1100100111101110","9")); // 0
	Ves.insert( VesMap::value_type("1100110110101110","9")); // 0
	Ves.insert( VesMap::value_type("1100100111011110","9")); // 0
	Ves.insert( VesMap::value_type("1101100110011110","9")); // 0
	Ves.insert( VesMap::value_type("1100000000011110","9")); // 0
	Ves.insert( VesMap::value_type("1100100110101110","9")); // 0
	Ves.insert( VesMap::value_type("1101111110111111","9")); // 0
	Ves.insert( VesMap::value_type("1101000000011110","9")); // 0
	Ves.insert( VesMap::value_type("0100001110110110","9")); // 0
	Ves.insert( VesMap::value_type("1100101010011111","9")); // 0
	Ves.insert( VesMap::value_type("1100001010101110","9")); // 0
	Ves.insert( VesMap::value_type("1101001100011110","9")); // 0
	Ves.insert( VesMap::value_type("1100101111101100","9")); // 0
}
void OprPar(void)
{
	// Процедура определения основных значений
	//

	int i = 0, j, code; 
	float otn;

	// Заносим в матрицу все изображение
	char *str;
	str = new char[200];
	code = scanf("%s", str);
	W = 0;
	while (str[W] != '\0') W++;		// Определяем ширину файла

	while (code != EOF)
	{
		Input.resize(i + 1);
		Input[ i ].resize(W);
		j = 0;
		while (str[j] != '\0')
		{
			Input[ i ].at(j) = str[j];  
			j++;
		}
		i++;
		code = scanf("%s", str);
	}
	delete [] str;
	
	KolWht = 0.0;
	KolBlk = 0.0;

	// Определяем плотность цифр 
	for (i = 0; i < Input.size(); i++)
		for (j = 0; j < Input[i].size(); j++)
		{
			switch(Input[ i ].at(j))
			{
				case '.':  KolWht += 1.0; break;
				case '%':  KolWht += 0.5; break;
				case '#':  KolBlk += 0.5; break;
				case '@':  KolBlk += 1.0; break;
			}
		}

	otn = KolWht / KolBlk;	
	
	if (otn < 1.0) Plot = 0.3;
	if ( (otn > 1.0) && (otn < 1.5) ) Plot = 0.5;
	if ( (otn > 1.5) && (otn < 2.0) ) Plot = 0.7;
	if ( (otn > 2.0) && (otn < 2.5) ) Plot = 1.0;
	if ( (otn > 2.5) && (otn < 2.87) ) Plot = 1.2;
	if ( (otn > 2.87) && (otn < 2.873) ) Plot = 1.0;
	if ( (otn > 2.873) && (otn < 2.913) ) Plot = 1.2;
	if ( (otn > 2.913) && (otn < 2.914) ) Plot = 1.0;
	if ( (otn > 2.914) && (otn < 3.0) ) Plot = 1.2;
	if ( (otn > 3.0) && (otn < 3.193) ) Plot = 1.4;
	if ( (otn > 3.193) && (otn < 3.194) ) Plot = 1.0;
	if ( (otn > 3.194) && (otn < 3.5) ) Plot = 1.4;
	if ( (otn > 3.5) && (otn < 4.04) ) Plot = 1.39;
	if ( (otn > 4.04) && (otn < 4.42) ) Plot = 2.2;
	if ( (otn > 4.42) && (otn < 4.43) ) Plot = 1.2;
	if ( (otn > 4.43) && (otn < 4.5) ) Plot = 2.2;
	if ( (otn > 4.5) && (otn < 4.94) ) Plot = 1.91;
	if ( (otn > 4.94) && (otn < 4.95) ) Plot = 1;
	if ( (otn > 4.95) && (otn < 5.0) ) Plot = 1.91;
	if ( (otn > 5.0) && (otn < 5.336) ) Plot = 2.7;

	if ( (otn > 5.336) && (otn < 5.337) ) Plot = 1.5;
	if ( (otn > 5.337) && (otn < 5.5) ) Plot = 2.7;

	if ( (otn > 5.5) && (otn < 6.0) ) Plot = 3.0;
	if ( (otn > 6.0) && (otn < 6.05) ) Plot = 1.5;
	if ( (otn > 6.05) && (otn < 6.5) ) Plot = 3.5;
	if ( (otn > 6.5) && (otn < 7.19) ) Plot = 4.0;
	if ( (otn > 7.19) && (otn < 7.196) ) Plot = 2.5;

	if ( (otn > 7.196) && (otn < 7.456) ) Plot = 4.0;
	if ( (otn > 7.456) && (otn < 7.457) ) Plot = 2.5;
	if (otn > 7.457) Plot = 4.0;

	//Plot = otn * 0.49;

	H = Input.size();
}
int WhiteRow(int numV)
{
	// Процедура добавления к существующему числу
	//  ширины число, означающее количество пробельных
	//  мест

	bool end_cycle = false;
	int i = 0;
	while (numV < W)
	{
		while ( (!end_cycle) && (i < H) )
		{
			if( Input[ i ].at(numV) == '@' ) 
			{
				end_cycle = true;
				return numV;
			}
			i++;
		}
		numV++;
		i = 0;
	}
	return numV;
}
int RasstNum(int numV)
{
	// Функция, определяющая расстояние 
	//  между двумя пробельными местами
	//

	int i = 0, 
		numV_copy = numV;

	bool end_cycle = false,
		 b = true;

	while ( (numV <= W ) && (!end_cycle) )
	{
		while (i < H)
		{
			if( Input[ i ].at(numV) == '@' ) 
			{
				b = false;
				break;
			}
			i++;
		}
		if (b) end_cycle = true;
		else b = true;
		i = 0;
		numV++;
	}
	return (numV - numV_copy);
}
void OprNUM(void)
{	
	// Главная процедура, она определяет само число 
	//

	int i, j, k, g;
	
	KolWht = 0;
	KolBlk = 0;
	
	numV = WhiteRow(numV);			// Проход мимо пробела
	
	while (numV < W)
	{
		WhtNmb = RasstNum(numV);	// Ширина цифры

		if (WhtNmb > 2*(W - 10)/ 3 - 1) WhtNmb = (W - 10) / 3;   // Если не будет пробельного места
		
		for (g = 0; g < 4; g++)			// Цикл по столбцам
		{
			numH = 5;
			for (k = 0; k < 4; k++)			// Цикл по строкам (кол-во повторений)
			{
				for (i = numH; i < ( numH + (H-10) / 4 + 1 ); i++)		// Цикл по строкам 
				{	
					for (j = numV; j < ( numV + (WhtNmb / 4) ); j++)		    // Цикл по столбцам по символьно 
					{	
						switch( Input[ i ].at(j))
						{
							case '.': KolWht += 0.7; break;
							case '%': KolBlk += 0.2; break;
							case '#': KolBlk += 0.7; break;
							case '@': KolBlk += 1.0; break;
						}
						//printf("%c", Input[ i ].at(j));
					}
					//printf("\n");
				}
				//printf("\n");
				KolBlk *= Plot;
				if (KolWht > KolBlk) UniNum += '0' ;
				else UniNum += '1';
			
				KolWht = 0;
				KolBlk = 0;
				
				numH += ( (H-10) / 4 + 1 );
			}
			rez = (WhtNmb / 4);
			numV += rez;
		}
		numV = numV - 4*rez + WhtNmb;
		VesMap::iterator itr = Ves.find(UniNum);		// Поиск по уникальному ключу

		if ( itr != Ves.end() ) NUMBER += itr->second;
		else NUMBER += "!";
		UniNum.clear();

		numV = WhiteRow(numV);			// Проход мимо пробела
	}
}
int main(int argc, char* argv[])
{
	Teach();		// Обучение системы

	OprPar();		// Определяем основные параметры файла
	OprNUM();				// Определяем число	
	
    for(int i = 0; i < NUMBER.length(); i++) 
		printf("%c", NUMBER[i] ); 

	getchar();
	return 0;
}