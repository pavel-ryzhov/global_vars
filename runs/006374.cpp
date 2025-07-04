#include <cstdlib>
#include <iostream>
using namespace std;

struct word {
	char s [20];	// само слово
	int freq;		// частота использования слова
	int comb;		// комбнация клавиш (без 1 и *)
	int usedAgo;	// дополнительный признак сортировки, как давно слово использовалось
};

typedef word *wpoint;	// указатель на слово
typedef wpoint *vocab;	// словарь (массив указателей на слова)

// возврат номера клавиши, на которой расположжена цифра
int charToNum (char c) {
	if ( c < 112 )
		return (c - 97)/3 + 2;
	else if ( c > 115 )
		return (c > 118)? 9:8;
	else
		return 7;
}

//считывание словаря из файла
void readVoc (char *filename, int &n, vocab &V, FILE *&currentPoint) {
	FILE *f = fopen (filename, "rb");
	if ( !f ) {
		cout << "FILE DOES NOT EXIST!!!" << '\n';
		n = 0;
		return;
	}
	char c;
	n = 0;
	while ( (c = fgetc (f)) != '\n' ){
		if ( c == 13 )
			continue;
		n = n*10 + c - 48;
	}
	V = new wpoint [n];
	for ( int i=0 ; i<n ; i++ ) {
		int l = 0;
		V[i] = new word;
		V[i]->comb = 0;
		while ( (c = fgetc (f)) != ' ' ) {
			if ( c == 13 )
				continue;
			V[i]->s[l] = c;
			V[i]->comb = V[i]->comb *10 + charToNum (c);
			l++;
		}
		V[i]->s[l] = '\0';
		V[i]->freq = 0;
		while ( (c = fgetc (f)) != '\n' ) {
			if ( c == 13 )
				continue;
			V[i]->freq = V[i]->freq *10 + c - 48;
		}
		V[i]->usedAgo = 0;
	}
	currentPoint = f;		// возвращает указатель на последнюю строку в файле
}

// принимает указатель на последнюю строку в файле, возвращает эту самую строку
char *readTask (FILE *f) {
	char c;
	char *s = new char;
	int i = 0;
	while ( ((c = fgetc (f)) != EOF) && (c != 13) )
		s[i++] = c;
	s[i] = '\0';
	fclose (f);
	return s;
}

// сортировка по частоте использования слова в пределах одной комбинации клавиш
void sortByFreq (vocab &V, int n) {
	if ( n > 1 ) {
		wpoint temp;
		for ( int i=0 ; i<n ; i++ ) {
			//wpoint max = V[i];
			int t = 0;
			int maxIndex = i;
			for ( int j=i+1 ; j<n ; j++ ) {
				if ( (V[j]->freq > V[maxIndex]->freq)||((V[j]->freq == V[maxIndex]->freq)&&(V[maxIndex]->usedAgo > V[j]->usedAgo)) ) {
					//max = V[j];
					t = 1;
					maxIndex = j;
				}
			}
			if ( t ) {
				temp = V[i];
				V[i] = V[maxIndex];
				V[maxIndex] = temp;
			}	// if
		}		// for
	}			// if
}

// выборка из словаря слов, подходящих под набор клавиш
vocab usersWords (int combination, vocab &V, int n, int &len) {
	int first;
	first = len = 0;
	int t, f;
	f = 0;
	for ( int i=0 ; i<n ; i++ ) {
		t = (V[i]->comb == combination)? 1:0;
		if ( t ) {
			len++;
			if ( !f ) {
				first = i;
				f = 1;
			}
		} else if ( f ) {
			break;
		}
	}
	vocab result = new wpoint [len];
	for ( int i=0 ; i<len ; i++ ) {
		result[i] = V[i+first];
	}
	sortByFreq (result, len);
	return result;
}		

// принимает комбинацию клавиш "от проблела до единицы", возвращает слово
char *getWord (char *s, vocab &V, int n) {
	int i = 0;
	int comb = 0;
	while ( s[i] ) {
		if ( (s[i] != '1') && (s[i] != '*') ) {
			comb = comb *10 + s[i] - 48;
			i++;
		} else {
			break;
		}
	}
	int m;
	int j = 0;
	vocab W = usersWords (comb, V, n, m);
	while ( s[i] == '*' ) {
		j++;
		if ( j == m )
			j = 0;
		i++;
	}
	char *result = W[j]->s;
	W[j]->freq += 1;
	for ( i = 0 ; i<m ; i++ )
		W[i]->usedAgo += 1;
	W[j]->usedAgo = 0;
	return result;
}

// принимает строку "от единицы до пробела" и возвращает знак препинания
char getMark (char *s) {
	int i = 1;
	int j = 0;
	while ( s[i] ) {
		j++;
		if ( j == 3 )
			j = 0;
		i++;
	}
	switch (j) {
		case 0:	return '.';
		case 1:	return ',';
		case 2: return '?';
		default: return '.';
	}
}

// возвращает результируюшую строку
char *getResultString (char *s, vocab &V, int n) {
	int i, j;
	i = j = 0;
	char *result = new char;
	while ( s[i] ) {
		int k = 0;
		char *x = new char;
		while ( s[i] &&(s[i] != '1')&&(s[i] != ' ') )
			x[k++] = s[i++];
		x[k] = '\0';
		x = getWord (x, V, n);
		k = 0;
		while ( x[k] )
			result[j++] = x[k++];
		if ( s[i] == '1' ) {
			x = new char;
			k = 0;
			while ( s[i] &&(s[i] != ' ') )
				x[k++] = s[i++];
			x[k] = '\0';
			char ch = getMark (x);
			result[j++] = ch;
		}
		if ( s[i] == ' ' ) {
			result[j++] = ' ';
			i++;
		}
	}
	result[j] = '\0';
	return result;
}

// основная программа
int main() {
	cout << "Enter name of test file: ";
	char *filename = new char;
	cin >> filename;
	FILE *finp;
	vocab V;
	int n;
	readVoc (filename, n, V, finp);
	if ( !n ) {
		system ("pause");
		return 0;
	}
	char * task = readTask (finp);
	char * out = getResultString (task, V, n);
	int len = 0;
	while ( out[len++] ) {}
	FILE *fout = fopen ("outputFile", "wb");
	fwrite (out, sizeof(char), len-1, fout);
	fclose (fout);
	cout << out << '\n';
	system("pause");
}