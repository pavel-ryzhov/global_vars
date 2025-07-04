/*
 * файл “9.cpp
 * «адача 3: “9 
 */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#define MAX_STRING_NUMBER 100				// максимальное число слов в словаре
#define MAX_STRING_LENGHT 20				// максимальна€ длинна слова
#define MAX_ENTRY_LENGHT  100000			// максимальна€ длинна входной строки набора T9			

int  i, j, k, N, number, max_rate, j_max;	// переменные счетчики(i, j, k), N - число слов в словаре, max_rate - миксимальна€ частота, j_max - идекс max_rate в массиве.
char ch;									// переменна€ дл€ считывани€ символов входной строки “9

int  rate[MAX_STRING_NUMBER], priority[MAX_STRING_NUMBER];	// массивы частот и приоритетов
char dict[MAX_STRING_NUMBER][MAX_STRING_LENGHT],			// массив содержащий словарь
	 entry[MAX_ENTRY_LENGHT], word[MAX_STRING_LENGHT],		// массив входной строки “9
	 intDict[MAX_STRING_NUMBER][MAX_STRING_LENGHT];			// массив содержащий словарь в численном виде

char const punct[4] = ".,?";								// массив знаков препинани€

bool used[MAX_STRING_NUMBER];								// массив использованности данного слова

void Init	( void );																// ф-ци€ инициализации переменных
void T9		( char dict[MAX_STRING_NUMBER][MAX_STRING_LENGHT], 
			  int  rate[MAX_STRING_NUMBER], char entry[MAX_ENTRY_LENGHT] , int N);	// алгоритм “9
 
int main() {

	scanf( "%d", &N );							// считываем N
	
	Init();										// инициализируем переменные
	
	for ( i = 0; i < N; i++ )
		scanf( "%s %d", dict[i], &rate[i] );	// считываем словарь
	
	i = 0;
	getchar();
	
	// считываем строку ввода “9
	while ( ( ch = getchar() ) != EOF ) { 
		if ( ch == '\n' || i >= MAX_ENTRY_LENGHT ) break;
	entry[i] = ch;
	i++;
	}
	entry[i] = '\0';							// "закрываем" массив

	T9 ( dict, rate, entry, N );				// запускаем “9
	return 0;
}

/*--- ф-ци€ инициализации переменных ---*/
void Init ( void ) {
	for ( i = 0; i < MAX_STRING_NUMBER; i++ ) {
		dict[i][0]	 =	'\0'; 
		intDict[i][0]=	'\0'; 
		rate[i]		 =	0; 
		priority[i]	 =	0;
		used[i]		 =	false;
	}
	
	entry[0]	=	'\0';
	word[0]		=	'\0';
	ch			=	' ';
	number		=	0;
	max_rate	=	0;
}

/*--- ф-ци€ реализации эмул€тор “9 ---
 * подробное описание “9: http://en.wikipedia.org/wiki/T9_(predictive_text)
 * подробное описание алгоритма см.ниже
 */
void T9	( char dict[MAX_STRING_NUMBER][MAX_STRING_LENGHT], 
		  int  rate[MAX_STRING_NUMBER], char entry[MAX_ENTRY_LENGHT], int N ) {
	 for( i = 0; i < N; i++) {
		j = 0;
		// заполн€ем массив intDict числама 
		// соответсвущим буквам в словах в нашем словаре dict
		// пример: Ivan -> 4826
		while( dict[i][j] != '\0' ) {
			if ( dict[i][j] == 'a' || dict[i][j] == 'b' || dict[i][j] == 'c' )
				intDict[i][j] = '2';
			if ( dict[i][j] == 'd' || dict[i][j] == 'e' || dict[i][j] == 'f' )
				intDict[i][j] = '3';
			if ( dict[i][j] == 'g' || dict[i][j] == 'h' || dict[i][j] == 'i' )
				intDict[i][j] = '4';
			if ( dict[i][j] == 'j' || dict[i][j] == 'k' || dict[i][j] == 'l' )
				intDict[i][j] = '5';
			if ( dict[i][j] == 'm' || dict[i][j] == 'n' || dict[i][j] == 'o' )
				intDict[i][j] = '6';
			if ( dict[i][j] == 'p' || dict[i][j] == 'q' || dict[i][j] == 'r' || dict[i][j] == 's' )
				intDict[i][j] = '7';
			if ( dict[i][j] == 't' || dict[i][j] == 'u' || dict[i][j] == 'v' )
				intDict[i][j] = '8';
			if ( dict[i][j] == 'w' || dict[i][j] == 'x' || dict[i][j] == 'y' || dict[i][j] == 'z' )
				intDict[i][j] = '9';
			j++;
		}
	}

	i = 0;
	j = 0;
	
	// алгоритм эмул€тора “9
	while ( entry[i] != '\0' ) {
		//считываем по одному слову из строки ввода “9
		while ( entry[i] != ' ' && entry[i] != '*' && entry[i] != '1' ) { 
			word[j] = entry[i];
			j++;
			i++;
		}
		j = 0;
		number = atoi( word );
		i--;
		//ищем нужное слово в словаре
		do {
			while ( rate[j] != 0 )	{
				if ( number == atoi(intDict[j]) )	{
					if ( max_rate <= rate[j] && priority[j_max] < priority[j] && used[j] == false ) {
						max_rate = rate[j]; 
						j_max = j;
					}
					if ( max_rate < rate[j] && used[j] == false ) {	
						max_rate = rate[j]; 
						j_max = j;
					}
				} 
				j++;
			}
			i++;
			j = 0;
			max_rate = 0;
			used[j_max] = true;		// если слово уже находили, пропускаем его и переходим к следующему если нужно.
		} while ( entry[i] == '*' );
		
		k = 0;
		// выводим слово, если встретили "пробел" 
		// или дошли до конца строки ввода
		if ( entry[i] == ' ' || entry[i] == '\0') {
			printf( "%s ", dict[j_max] );
			rate[j_max]++;			// увеличиваем частоту
			priority[j_max] = i;	// увеличиваем приоритет, тк 
									// слово должно идти первое по списку 
									// среди слов с такой же частотой
			i++;
		}

		// аналогично, если встретили знак препинани€
		if ( entry[i] == '1' ) {
			printf( "%s", dict[j_max] );
			rate[j_max]++;
			priority[j_max] += i;
			i++;

			while ( entry[i] == '*' && entry[i] != ' ' && entry[i] != '\0' ) { k++; i++; }	// выбираем нужный знак препинани€
			printf( "%c", punct[k] );
		}

		// обнул€ем массивы и переменные
		for ( k = 0; k < N; k++ ) used[k] = false;
		number = 0;
		j_max  = 0;
		memset( word,		0,	sizeof(word) );
	}
}