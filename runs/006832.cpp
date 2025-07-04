#include <cstdlib>
#include <iostream>

using namespace std;

int strCompare ( char x[], char y[]) {
	int i, j, l1, l2;
	i = j = l1 = l2 = 0;
	while ( x[i++] )
		l1++;
	while ( y[j++] )
		l2++;
	if ( l1 != l2 )
		return (l1 > l2)? 1: -1;
	for ( int k=0 ; k<l1 ; k++ )
		if ( x[k] != y[k] )
			return 1;
	return 0;
}

class CVocabulary {
public:
	/*структура словаря*/
	typedef struct {
		char s[20];
		int freq;
		char comb[20];
		int usedAgo;
	} word;
	typedef word* vocab;
	/* интерфейс*/
	CVocabulary ();						// конструктор
	~CVocabulary ();					// деструктор
	int creationCheck ();				// проверка на наличие слов в словаре
	char *getResultString (char *inp);	// возврат результирующей строки

private:
	/*поля*/
	vocab wordArray;	// сам словарь
	int wordAmount;		// количество слов в словаре
	/*внутренние функции*/
	void sortByFreq (int *arr, int aLen);						// сортировка по частоте и последовательности использования слов
	int *selectByComb (char comb[20], int &aLen);				// выборка индексов слов с одинаковой комбинацией клавиш
	void getWord (char *inp, char &mark, char out[20]);			// возврат слова по набору символов "от пробела до пробела"
	char charToNum (char c);									// возвращает номер клавиши, на которой расположена буква
};

CVocabulary::CVocabulary () {
	cin >> wordAmount;
	wordArray = new word [wordAmount];
	for ( int i=0 ; i<wordAmount ; i++ ) {
		cin >> wordArray[i].s;
		cin >> wordArray[i].freq;
		int j = 0;
		while ( wordArray[i].s[j] ) {
			wordArray[i].comb[j] = charToNum (wordArray[i].s[j]);
			j++;
		}
		wordArray[i].comb[j] = '\0';
		wordArray[i].usedAgo = 0;
	}
}

CVocabulary::~CVocabulary() {
	delete [] wordArray;
}

int CVocabulary::creationCheck() {
	if ( wordAmount )
		return 0;
	return 1;
}

void CVocabulary::sortByFreq(int *arr, int aLen) {
	if ( aLen < 2 )
		return;
	int t = 1;
	int i = 0;
	while ( t ) {
		t = 0;
		for ( int j=0 ; j<aLen-i-1 ; j++ ) {
			if ( (wordArray[arr[j]].freq < wordArray[arr[j+1]].freq) || ((wordArray[arr[j]].freq == wordArray[arr[j+1]].freq)&&(wordArray[arr[j]].usedAgo > wordArray[arr[j+1]].usedAgo)) ) {
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				t = 1;
			}
		}
		i++;
	}
}

int* CVocabulary::selectByComb(char comb[20], int &aLen) {
	int t, f, first;
	t = f = aLen = 0;
	for ( int i=0 ; i<wordAmount ; i++ ) {
		if ( f && (comb[0] != wordArray[i].comb[0]) )
			break;
		if ( strCompare (comb, wordArray[i].comb) )
			continue;
		aLen++;
		if ( !f ) {
			first = i;
			f = 1;
		}
	}
	int *arr = new int [aLen];
	int j = 0;
	for ( int i=first ; i<wordAmount ; i++ ) {
		if ( comb[0] != wordArray[i].comb[0] )
			break;
		if ( strCompare (comb, wordArray[i].comb) )
			continue;
		arr[j++] = i;
	}
	return arr;
}

void CVocabulary::getWord (char *inp, char &mark, char *out) {
	char comb[20];
	int i = 0;
	while ( inp[i] && (inp[i] != '*') && (inp[i] != '1') )
		comb[i] = inp[i++];
	comb[i] = '\0';
	int aLen;
	int *arr = selectByComb (comb, aLen);
	sortByFreq (arr, aLen);
	int j = 0;
	while ( inp[i] == '*' ) {
		j++;
		if ( j > aLen )
			j = 0;
		i++;
	}
	int k = 0;
	while (wordArray[arr[j]].s[k])
		out[k++] = wordArray[arr[j]].s[k];
	out[k] = '\0';
	wordArray[arr[j]].freq += 1;
	for ( int l=0 ; l<aLen ; l++ )
		wordArray[arr[l]].usedAgo += 1;
	wordArray[arr[j]].usedAgo = 0;
	if ( inp[i] == '\0' ) {
		mark = '\0';
		return;
	} else {
		i++;
		j = 0;
	}
	while ( inp[i] == '*' ) {
		j++;
		if ( j == 3 )
			j = 0;
		i++;
	}
	switch ( j ) {
		case 0:	{
			mark = '.';
			break;
				}
		case 1:	{
			mark = ',';
			break;
				}
		case 2:	{
			mark = '?';
			break;
				}
		default: mark = '.';
	}
}

char CVocabulary::charToNum(char c) {
	if ( c < 112 )
		return (c - 97)/3 + 50;	// первые пять цифр (2 - 6)
	else if ( c > 115 )
		return (c > 118)? '9':'8';	
	else
		return '7';
}

char* CVocabulary::getResultString(char *inp) {
	int i, j;
	i = j = 0;
	char *out = new char;
	while ( inp[i] ) {
		int k = 0;
		char *temp1 = new char;
		while ( inp[i] && (inp[i] != ' ') )
			temp1[k++] = inp[i++];
		temp1[k] = '\0';
		char mark;
		char *temp2 = new char;
		getWord (temp1, mark, temp2);
		k = 0;
		while ( temp2[k] )
			out[j++] = temp2[k++];
		if ( mark )
			out[j++] = mark;
		if ( inp[i] == ' ' )
			out[j++] = inp[i++];
	}
	out[j] = '\0';
	return out;
}

// основная программа
int main(int argc, char *argv[]) {
	CVocabulary V;								// объявление словаря
	if ( V.creationCheck() )					// если словарь пуст - завершить исполнение
		return 0;								// --
	char *task = new char [100000];				// объявление строки с заданием (символы, набранные пользователем)
	cin.ignore();								// игнорирование знаков \n, для правильного расположения каретки
	cin.getline (task, 100000, '\n');			// считывание строки-задания
	char *out = V.getResultString (task);	// объявление строки с ответом и запись ответа
	cout << out << '\n';						// вывод ответа на экран
	system ("pause");
}