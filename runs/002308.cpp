// C_T9.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <cstdlib>
#include <map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class WordFreq
{
public:
	string NumWord;				// Набор клавиш
	vector< string > Word;		// Вектор слов
	vector< int >    Freq;		// Вектор частот

	WordFreq() {};
	void Input(string word, int freq)
	{
		Word.resize( Word.size() + 1);
		Freq.resize( Freq.size() + 1);

		Word.at( Word.size() - 1) = word;
		Freq.at( Freq.size() - 1) = freq;
	}
	void Sort()
	{   // Сортировка по частотам 
		int i, j, ord;
		string str;
		for ( i = 0; i < Word.size(); i++)
			for (j = 1; j < Word.size(); j++)
			{
				if ( Freq.at(j - 1) < Freq.at(j) )
				{
					ord = Freq.at(j - 1); 
					Freq.at(j - 1) = Freq.at(j);
					Freq.at(j) = ord;

					str = Word.at(j - 1);
					Word.at(j - 1) = Word.at(j);
					Word.at(j) = str;
				}
			}
	}
};

typedef multimap< string, string > Typing;	
Typing typing;

vector< WordFreq >  WrdFrq;

void Prepare(void)
{
	typing.insert( Typing::value_type(".", "1")); 
	typing.insert( Typing::value_type(",", "1")); 
	typing.insert( Typing::value_type("?", "1"));

	typing.insert( Typing::value_type("a", "2")); 
	typing.insert( Typing::value_type("b", "2")); 
	typing.insert( Typing::value_type("c", "2")); 

	typing.insert( Typing::value_type("d", "3")); 
	typing.insert( Typing::value_type("e", "3")); 
	typing.insert( Typing::value_type("f", "3")); 
	
	typing.insert( Typing::value_type("g", "4")); 
	typing.insert( Typing::value_type("h", "4")); 
	typing.insert( Typing::value_type("i", "4")); 
	
	typing.insert( Typing::value_type("j", "5")); 
	typing.insert( Typing::value_type("k", "5"));
	typing.insert( Typing::value_type("l", "5"));

	typing.insert( Typing::value_type("m", "6")); 
	typing.insert( Typing::value_type("n", "6")); 
	typing.insert( Typing::value_type("o", "6"));

	typing.insert( Typing::value_type("p", "7")); 
	typing.insert( Typing::value_type("q", "7")); 
	typing.insert( Typing::value_type("r", "7"));
	typing.insert( Typing::value_type("s", "7"));

	typing.insert( Typing::value_type("t", "8")); 
	typing.insert( Typing::value_type("u", "8"));
	typing.insert( Typing::value_type("v", "8")); 

	typing.insert( Typing::value_type("w", "9")); 
	typing.insert( Typing::value_type("x", "9"));
	typing.insert( Typing::value_type("y", "9")); 
	typing.insert( Typing::value_type("z", "9")); 
}
void Input(void)
{
	string num;
	string ord; 
	int N, i, j, freq;
	char *str, *word;
	bool in_inic = false;

	str  = new char[30];
	word = new char[30];

	scanf("%s", str);
	N = atoi(str);
	for (i = 0; i < N; i++)
	{
		scanf("%s", word);

		scanf("%s", str);
		freq = atoi(str);

		j = 0;
		num.clear();
		while(word[j] != '\0')
		{
			ord = word[j];
			Typing::iterator itr = typing.find(ord);
			num += itr->second;
			j++;
		}
		ord = word;

		for (j = 0; j < WrdFrq.size(); j++)
		{
			if ( WrdFrq.at(j).NumWord == num ) 
			{
				in_inic = true;
				break;
			}
		}
		if (in_inic) 
		{
			WrdFrq.at(j).Input(ord, freq);
			in_inic = false;
		}
		else
		{
			WrdFrq.resize( (int) WrdFrq.size() + 1 );
			WrdFrq.at( (int) WrdFrq.size() - 1 ).NumWord = num;
			WrdFrq.at( (int) WrdFrq.size() - 1 ).Input(ord, freq);
		}
	}
	delete [] word;
	delete [] str;

	for (j = 0; j < WrdFrq.size(); j++)
	{
		WrdFrq.at(j).Sort();
	}

	// Добавим в вектор еще '1'
	num = "1";
	WrdFrq.resize( (int) WrdFrq.size() + 1 );
	WrdFrq.at( (int) WrdFrq.size() - 1 ).NumWord = num;
	WrdFrq.at( (int) WrdFrq.size() - 1 ).Input(".", 0);
	WrdFrq.at( (int) WrdFrq.size() - 1 ).Input(",", 0);
	WrdFrq.at( (int) WrdFrq.size() - 1 ).Input("?", 0);
}
void WorkText(void)
{
	int i, k, j, KolSm, ord, code, ip;
	char *str, *text;
	string Output, num, str1;
	
	text = new char[10000];
	str  = new char[30];

	getchar();
	gets(text);
	ip = 0;
	Output.clear();
	while(text[ip] != '\0')
	{
		i = 0;
		while( (text[ip] != ' ') && (text[ip] != '\0') ) 
		{
			str[i] = text[ip];
			i++;
			ip++;
		}
		str[i] = '\0';

		// Считываем число
		i = 0;
		num.clear();
		while( (str[i] != '\0') && (str[i] != '*') && (str[i] != '1'))
		{
			num += str[i];
			i++;
		}

		KolSm = 0;				// Количество *
		if(str[i] != '1')	
		{
			// Считаем количество *
			while( (str[i] != '1') && (str[i] != '\0') ) 
			{
				KolSm++;
				i++;
			}

			for (k = 0; k < WrdFrq.size(); k++)
			{
				if ( WrdFrq.at(k).NumWord == num ) 
				{
					Output += WrdFrq.at(k).Word.at(KolSm);
					WrdFrq.at(k).Freq.at(KolSm)++;
					break;
				}
			}

			j = KolSm; 
			while( (j >= 1) && ( WrdFrq.at(k).Freq.at(j-1) <= WrdFrq.at(k).Freq.at(j) ) )
			{
				ord = WrdFrq.at(k).Freq.at(j - 1); 
				WrdFrq.at(k).Freq.at(j - 1) = WrdFrq.at(k).Freq.at(j);
				WrdFrq.at(k).Freq.at(j) = ord;

				str1 = WrdFrq.at(k).Word.at(j - 1);
				WrdFrq.at(k).Word.at(j - 1) = WrdFrq.at(k).Word.at(j);
				WrdFrq.at(k).Word.at(j) = str1;

				j--;
			}

			// Если есть '1'
			if( str[i] == '1' ) 
			{
				i++;
				KolSm = 0;
				while( str[i] != '\0' ) 
				{
					KolSm++;
					i++;
				}
				Output += WrdFrq.at( WrdFrq.size() - 1 ).Word.at(KolSm);
			}
		}
		else if( (str[i] == '1') && (num != "") ) 
		{
			for (k = 0; k < WrdFrq.size(); k++)
			{
				if ( WrdFrq.at(k).NumWord == num ) 
				{
					Output += WrdFrq.at(k).Word.at(0);
					WrdFrq.at(k).Freq.at(0)++;
					break;
				}
			}

			i++;
			KolSm = 0;
			while( str[i] != '\0' ) 
			{
				KolSm++;
				i++;
			}
			Output += WrdFrq.at( WrdFrq.size() - 1 ).Word.at(KolSm);
		}
		else if( (str[i] == '1') && (num == "") )
		{
			i++;
			KolSm = 0;
			while( str[i] != '\0' ) 
			{
				KolSm++;
				i++;
			}
			Output += WrdFrq.at( WrdFrq.size() - 1 ).Word.at(KolSm);
		}
		// Добавляем пробел
		while( text[ip] == ' ' )
		{
			Output += ' ';
			ip++;
		} 
	}
	delete [] str;
	delete [] text;

	for (i = 0; i < ( (int) Output.size() ); i++)
		printf( "%c", Output[i] );
}
int main(int argc, char* argv[])
{
	Prepare();
	Input();
	WorkText();

	return 0;
}

