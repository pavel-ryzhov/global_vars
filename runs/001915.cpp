// A_Scaner.cpp : Defines the entry point for the console application.
//

#include <map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ���������� ���������
typedef multimap< string, string > VesMap;
vector< vector< char > > Input;		// ������� �����������

string UniNum,				// ���������� ��� ������ ����� �����
	   NUMBER = "";			// ������������ �����	

VesMap Ves;

int H,			// ������ � ��������
	W,			// ������ � ��������
	numV,
	numH,
	WhtNmb , 
	rez;

float KolWht,	 // ���-�� ������� ��������
	  KolBlk,	 // ���-�� ����� ��������
	  Plot;	 // ��������� ���� �� �����������, �.�. "���" ������� �������

void Teach(void)
{
	// ��������� �������� �������

	Ves.insert( VesMap::value_type("1110111100000000","0")); // 010
	Ves.insert( VesMap::value_type("1110100110011110","0")); // 021 

	Ves.insert( VesMap::value_type("0000111011100000","1")); // 007
	Ves.insert( VesMap::value_type("1110111111110000","1")); // 009
	Ves.insert( VesMap::value_type("1000111111110000","1")); // 020
	
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
	Ves.insert( VesMap::value_type("0010010011101111","4")); // 021 

	Ves.insert( VesMap::value_type("0100110111011010","5")); // 003
	Ves.insert( VesMap::value_type("1010100010001100","5")); // 005
	Ves.insert( VesMap::value_type("1100110011011110","5")); // 007
	Ves.insert( VesMap::value_type("0011110010011110","5")); // 008
	Ves.insert( VesMap::value_type("0000000001110110","5")); // 010
	Ves.insert( VesMap::value_type("0000110000010010","5")); // 015
	Ves.insert( VesMap::value_type("0001110011000001","5")); // 016
	Ves.insert( VesMap::value_type("0000110011000010","5")); // 018
	Ves.insert( VesMap::value_type("0101110111011110","5")); // 021	

	Ves.insert( VesMap::value_type("0110000000000100","6")); // 005
	Ves.insert( VesMap::value_type("0110111100000000","6")); // 010   
	Ves.insert( VesMap::value_type("0110011101000110","6")); // 011
	Ves.insert( VesMap::value_type("0110111001100110","6")); // 013

	Ves.insert( VesMap::value_type("1000101011101000","7")); // 005
	Ves.insert( VesMap::value_type("0000001111001000","7")); // 004
	Ves.insert( VesMap::value_type("1000101111001000","7")); // 001
	Ves.insert( VesMap::value_type("1011101111001000","7")); // 009
	Ves.insert( VesMap::value_type("1000111011101000","7")); // 014
	Ves.insert( VesMap::value_type("1000100111101000","7")); // 021 
	
	Ves.insert( VesMap::value_type("0111110111100111","8")); // 002
	Ves.insert( VesMap::value_type("0110010001001110","8")); // 008
	Ves.insert( VesMap::value_type("0111011111101010","8")); // 011
	Ves.insert( VesMap::value_type("1110111011101110","8")); // 012
	Ves.insert( VesMap::value_type("0111110001010010","8")); // 016
	Ves.insert( VesMap::value_type("0010111011101000","8")); // 018
	Ves.insert( VesMap::value_type("0000011001100000","8")); // 017
	Ves.insert( VesMap::value_type("1110110001001110","8")); // 021

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
void OprPar(void)
{
	// ��������� ����������� �������� ��������
	//

	int i = 0, j, code; 

	// ������� � ������� ��� �����������
	char *str;
	str = new char[200];
	code = scanf("%s", str);
	W = 0;
	while (str[W] != '\0') W++;		// ���������� ������ �����

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

	// ���������� ��������� ���� 
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

	Plot = (KolWht / KolBlk) * 0.34;	

	H = Input.size();
}
int WhiteRow(int numV)
{
	// ��������� ���������� � ������������� �����
	//  ������ �����, ���������� ���������� ����������
	//  ����

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
	// �������, ������������ ���������� 
	//  ����� ����� ����������� �������
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
	// ������� ���������, ��� ���������� ���� ����� 
	//

	int i, j, k, g;
	
	KolWht = 0;
	KolBlk = 0;
	
	numV = WhiteRow(numV);			// ������ ���� �������
	
	while (numV < W)
	{
		WhtNmb = RasstNum(numV);	// ������ �����

		if (WhtNmb > 2*(W - 10)/ 3 - 1) WhtNmb = (W - 10) / 3;   // ���� �� ����� ����������� �����
		
		for (g = 0; g < 4; g++)			// ���� �� ��������
		{
			numH = 5;
			for (k = 0; k < 4; k++)			// ���� �� ������� (���-�� ����������)
			{
				for (i = numH; i < ( numH + (H-10) / 4 + 1 ); i++)		// ���� �� ������� 
				{	
					for (j = numV; j < ( numV + (WhtNmb / 4) ); j++)		    // ���� �� �������� �� ��������� 
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
		VesMap::iterator itr = Ves.find(UniNum);		// ����� �� ����������� �����

		if ( itr != Ves.end() ) NUMBER += itr->second;
		else NUMBER += "!";
		UniNum.clear();

		numV = WhiteRow(numV);			// ������ ���� �������
	}
}
int main(int argc, char* argv[])
{
	Teach();		// �������� �������

	OprPar();		// ���������� �������� ��������� �����
	OprNUM();				// ���������� �����	
	
    for(int i = 0; i < NUMBER.length(); i++) 
		printf("%c", NUMBER[i] ); 

	//getchar();
	return 0;
}