#include <cstdlib>
#include <iostream>

using namespace std;

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
	void sortByFreq (int first, int last);						// сортировка по частоте и последовательности использования слов
	void selectByComb (char comb[20],int &first, int &last);	// выборка границ индексов слов с одинаковой комбинацией клавиш
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

void CVocabulary::sortByFreq(int first, int last) {
	if ( first == last )
		return;
	for ( int i=first ; i<=last ; i++ ) {
		int max = i;
		int t = 0;
		for ( int j=i+1 ; j<=last ; j++ ) {
			if ( (wordArray[j].freq > wordArray[max].freq) || ((wordArray[j].freq == wordArray[max].freq)&&(wordArray[j].usedAgo < wordArray[max].usedAgo)) ) {
				max = j;
				t = 1;
			}
		}
		if ( t ) {
			word temp = wordArray[i];
			wordArray[i] = wordArray[max];
			wordArray[max] = temp;
		}
	}
}

void CVocabulary::selectByComb(char comb[20], int &first, int &last) {
	int t, f;
	f = 0;
	for ( int i=0 ; i<wordAmount ; i++ ) {
		t = 1;
		int j = 0;
		while ( comb[j] ) {
			if ( comb[j] != wordArray[i].comb[j] ) {
				t = 0;
				break;
			}
			j++;
		}
		if ( t && !f ) {
			first = i;
			f = 1;
		}
		if ( f && !t ) {
			last = i-1;
			return;
		}
	}
	last = wordAmount-1;
}

void CVocabulary::getWord (char *inp, char &mark, char *out) {
	char comb[20];
	int i = 0;
	while ( inp[i] && (inp[i] != '*') && (inp[i] != '1') )
		comb[i] = inp[i++];
	comb[i] = '\0';
	int first, last;
	selectByComb (comb, first, last);
	sortByFreq (first, last);
	int j = first;
	while ( inp[i] == '*' ) {
		j++;
		if ( j > last )
			j = first;
		i++;
	}
	int k = 0;
	while (wordArray[j].s[k])
		out[k++] = wordArray[j].s[k];
	out[k] = '\0';
	wordArray[j].freq += 1;
	for ( int k=first ; k<=last ; k++ )
		wordArray[k].usedAgo += 1;
	wordArray[j].usedAgo = 0;
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
	char *task = new char;						// объявление строки с заданием (символы, набранные пользователем)
	cin.ignore();								// игнорирование знаков \n, для правильного расположения каретки
	cin.getline (task, 100000, '\n');			// считывание строки-задания
	char *out = V.getResultString (task);	// объявление строки с ответом и запись ответа
	cout << out << '\n';						// вывод ответа на экран
	system ("pause");
}