#include <cstdlib>
#include <iostream>

using namespace std;

struct word {
	char s[20];		// само слово
	int freq;		// частота использования слова
	int comb;		// комбинация клавиш
	int usedAgo;	// дополнительный признак сортировки - как давно слово использовалось
};

typedef word *wpoint;	// указатель на слово
typedef wpoint *vocab;	// словарь, массив указателей на слова

// возврат клавиши, на которой находится буква
int charToNum (char c) {
	if ( c < 112 )
		return (c - 97)/3 + 2;	// первые пять цифр (2 - 6)
	else if ( c > 115 )
		return (c > 118)? 9:8;
	else
		return 7;
}

// считывание словаря
void readVoc (int &n, vocab &V) {
	cin >> n;
	V = new wpoint [n];
	for (int i=0 ; i<n ; i++ ) {
		V[i] = new word;
		cin >> V[i]->s;
		V[i]->comb = 0;
		int k = 0;
		while ( V[i]->s[k] )
			V[i]->comb = V[i]->comb *10 + charToNum (V[i]->s[k++]);
		cin >> V[i]->freq;
		V[i]->usedAgo = 0;
	}
}

// считывание словаря из командной строки
/*void readCL (int &n, vocab &V, char *argv[]) {
	n = 0;
	int i = 0;
	while ( argv[1][i] != '\0' )
		n = n*10 + argv[1][i] - 48;
	V = new wpoint [n];
	for ( int j=0 ; j<n ; j++ ) {
		V[j] = new word;
		i = 0;
		V[j]->comb = 0;
		while ( argv[j+2][i] != ' ') {
			V[j]->comb = V[j]->comb *10 + charToNum (argv[j+2][i]);
			V[j]->s[i] = argv[j+2][i];
			i++;
		}
		V[j]->s[i++] = '\0';
		while ( argv[j+2][i] )
			V[j]->freq = V[j]->freq *10 + argv[j+2][i++] - 48;
		V[j]->usedAgo = 0;
	}
}*/

// сортировка по частоте и последовательности использования в пределах одной комбинации клавиш
void sortByFreq (int n, vocab &V) {
	if ( n < 2 )
		return;
	for ( int i=0 ; i<n ; i++ ) {
		int max = i;
		int t = 0;
		for ( int j=i+1 ; j<n ; j++ ) {
			if ( (V[j]->freq > V[max]->freq) || ((V[j]->freq == V[max]->freq)&&(V[j]->usedAgo < V[max]->usedAgo)) ) {
				max = j;
				t = 1;
			}
		}
		if ( t ) {
			wpoint temp = V[i];
			V[i] = V[max];
			V[max] = temp;
		}
	}
}

// выборка из словаря слов, подходящих под набор клавиш, с сортировкой
vocab usersWords (int combination, int n, vocab V, int &len) {
	len = 0;
	int first, t, f;
	f = 0;
	for ( int i=0 ; i<n ; i++ ) {
		t = (V[i]->comb == combination)? 1:0;
		if ( t ) {
			len++;
			if ( !f ) {
				first = i;
				f = 1;
			}
		} else if ( f )
			break;
	}
	vocab result = new wpoint [len];
	int j = 0;
	for ( int i=0 ; i<len ; i++ )
		result[i] = V[i+first];
	sortByFreq (len, result);
	return result;
}

// возвращает слово по комбинации клавиш "от пробела до пробела"
char *getWord (char *s, int n, vocab V, char &mark) {
	int i = 0;
	int comb = 0;
	while ( s[i] && (s[i] != '*') && (s[i] != '1') ) {
		comb  = comb*10 + s[i] - 48;
		i++;
	}
	int m;
	vocab W = usersWords (comb, n, V, m);
	int j = 0;
	while ( s[i] == '*' ) {
		j++;
		if ( j == m )
			j = 0;
		i++;
	}
	char *result = W[j]->s;
	W[j]->freq += 1;
	for ( int k=0 ; k<m ; k++ )
		W[k]->usedAgo += 1;
	W[j]->usedAgo = 0;
	if ( s[i] == '\0' ) {
		mark = '\0';
		return result;
	} else {
		i++;
	}
	j = 0;
	while ( s[i] == '*' ) {
		j++;
		if ( j == 3 )
			j = 0;
		i++;
	}
	switch ( j ) {
		case 0: {
			mark = '.';
			break;
				}
		case 1: {
			mark = ',';
			break;
				}
		case 2: {
			mark = '?';
			break;
				}
		default: mark = '.';
	}
	return result;
}

// возвращает результирующую строку
char *getResultString (char *s, int n, vocab V) {
	int i, j;
	i = j = 0;
	char *result = new char;
	while ( s[i] ) {
		int k = 0;
		char *temp = new char;
		while ( s[i] && (s[i] != ' ') ) 
			temp[k++] = s[i++];
		temp[k] = '\0';
		char ch;
		temp = getWord (temp, n, V, ch);
		k = 0;
		while ( temp[k] )
			result[j++] = temp[k++];
		if ( ch )
			result[j++] = ch;
		if ( s[i] == ' ' )
			result[j++] = s[i++];
	}
	result[j] = '\0';
	return result;
}

// основная программа
int main(int argc, char *argv[]) {
	vocab V;
	int n;
	char *task;
	/*if ( argc > 1 ) {
		readCL (n, V, argv);
		task = argv[n+2];
	} else {*/
		readVoc (n, V);
		if ( !n )
			return 0;
		task = new char;
		cin.ignore();
		cin.getline (task, 100000, '\n');
	//}	
	char *out = getResultString (task, n, V);
	cout << out << '\n';
	int len = 0;
	while ( out[len] ) { len++; }
	FILE *f = fopen ("outputFile", "wb");
	fwrite (out, sizeof(char), len, f);
	fclose (f);
	system ("pause");
}