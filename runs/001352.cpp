#include <iostream>

#include <vector>
#include <algorithm>

#include <string>

#include <ctime>
#include <cstring>

using namespace std;

class word;

class wordWithCode {
public:
	wordWithCode(string code0) : code(code0) {} ;
	bool operator() (const word &w);
private:
	string code;
};

bool wordCompare(const word w1, const word w2);

class word {
public:
	word(string code0, string text0, int weight0) : code(code0), text(text0), weight(weight0), index(word::num) {};
	//friend bool operator<(word w1, word w2);
	friend bool wordCompare(const word w1, const word w2);
	friend ostream &operator<<(ostream &stream, word w);
	friend bool wordWithCode::operator()(const word &w);
	//bool wordCompare(word w1, word w2);
	static bool convertChars(char *inp, char *out);
	inline bool checkCode(char *check) { return !strcmp(code.c_str(),check); };
	inline const char* getText() { return text.c_str(); };
	static void useIt(word &w) {
		cout << w.text;
		if (w.code[0]!='1') {
			w.weight++;
			w.index = ++word::num;
			sort(word::words.begin(), word::words.end(), wordCompare);
		}
	}
/*
	inline void useIt(set< word >::iterator &i) {
		cout << this->text;
		//cout << text;
		if (code[0]!='1') {
			word::num++;
			word::words.insert(word(this->code,this->text,this->weight+1));
			word::words.erase(i);
		}
		return;
	};
*/
	static vector< word > words;
	string code;
private:
	string text;
	int weight;
	static int num;
	int index;	
};

/*
bool operator<(word w1, word w2) {
	if (w1.code == w2.code) {
		if (w1.weight == w2.weight) {
			if (w1.index == w2.index) {
				if (w1.text == w2.text) {
					// Опс! Слова абсолютно идентичы.
					return 0;
				} else return (w1.text < w2.text);	// сортировка по тексту - по алфавиту
			} else return (w1.index > w2.index);	// сортировка по "последнему употреблению" - по убыванию
		} else return (w1.weight > w2.weight);		// сортировка по частоте употребления (для слов с одинаковой встречаемостью) - по убыванию
	} else return (w1.code < w2.code);				// сортировка по цифровому коду - по алфавиту
}
*/

bool wordCompare(const word w1, const word w2) {
	if (w1.code == w2.code) {
		if (w1.weight == w2.weight) {
			if (w1.index == w2.index) {
				if (w1.text == w2.text) {
					// Опс! Слова абсолютно идентичы.
					return 0;
				} else return (w1.text < w2.text);	// сортировка по тексту - по алфавиту
			} else return (w1.index > w2.index);	// сортировка по "последнему употреблению" - по убыванию
		} else return (w1.weight > w2.weight);		// сортировка по частоте употребления (для слов с одинаковой встречаемостью) - по убыванию
	} else return (w1.code < w2.code);				// сортировка по цифровому коду - по алфавиту
}

ostream &operator<<(ostream &stream, word w)
{
	stream << w.code << ": " << w.text << " [" << w.weight << "] " << w.index << endl;
	return stream;
}

bool word::convertChars(char *inp, char *out) {
	int i = -1;
	while (inp[++i]) {
		if (inp[i] < 97) return 0;
		if (inp[i] < 100) { out[i] = '2'; continue; }
		if (inp[i] < 103) { out[i] = '3'; continue; }
		if (inp[i] < 106) { out[i] = '4'; continue; }
		if (inp[i] < 109) { out[i] = '5'; continue; }
		if (inp[i] < 112) { out[i] = '6'; continue; }
		if (inp[i] < 116) { out[i] = '7'; continue; }
		if (inp[i] < 119) { out[i] = '8'; continue; }
		if (inp[i] < 123) { out[i] = '9'; continue; }
		return 0;
	}
	out[i] = 0;
	return 1;
}

int word::num = 0;
vector< word > word::words;

bool wordWithCode::operator()(const word &w) {
	return (w.code == code);
};



int main() {
/*
	// Для определения скорости
	_getch();
	clock_t ct1 = clock();
*/
	// Введем слова для знаков препинания. Их порядок не будет изменяться.
	word::words.push_back(word("1",".",2));
	word::words.push_back(word("1",",",1));
	word::words.push_back(word("1","?",0));

	int n,weight;
	char *text = new char[21];
	char *code = new char[21];

	cin >> n;

	for (int i=0; i<n; i++) {
		cin >> text >> weight;
		if (!word::convertChars(text,code)) cout << "> Error converting word! (" << text << ")" << endl;
			else word::words.push_back(word(code,text,weight));
	}

	// Итак, словарь готов, теперь разберемся с сообщением.

	char c;

	c = cin.get();
	int i = 0;
	i = 0;
	vector< word >::iterator w;
	do {
		c = cin.get();

		if (c<58 && c>49) { // число от 2 до 9 - буква из нашего слова
			// Может так получиться, что мы как раз хотели вывести знак препинания.
			if (code[0] == '1') {
				// Выведем слово, подкрутим счетчики:
				word::useIt(*w);
				// used...

				i = 0;
			}
			code[i++] = c;
		} else {			// если это не буква - значит, управляющий символ
			if (i>0) { // Если слово не готово...
				code[i] = 0;		// завершим ввод слова
				w = find_if(word::words.begin(), word::words.end(), wordWithCode(code));		// подготовим итератор, указывающий на первое подходящее слово в словаре
				if (w == word::words.end()) cout << "> Word not found! [" << code << "]";	// если ни одного такого слова не нашлось - что-то здесь не так
			}
			// Управляющих символов три: пробел (32), 1 (49) и * (42)
			// (еще есть символ перевода строки 13, который заканчивает ввод)
			switch (c) {
				case 32:	// Начнем с пробела. Очевидно, следует просто вывести текущее слово + сам пробел.
					//if (i) (*w).useIt(w);	// Слово не выведено? Выведем его.
					if (i) {
						// useIt:		
						/*
							cout << w->text;
							if (w->code[0]!='1') {
								word::num++;
								word::words.insert(word(w->code,w->text,w->weight+1));
								word::words.erase(w);
							}
						*/
						word::useIt(*w);
						// used...
					}

					cout << " " ;
					code[0] = 0;
					i = 0;	// Отметим, что слово выведено.
					break;
				case 49:	// Это единица. Нам надо вывести текущее слово (если оно есть, i!=0),
							//  затем сделать "текущим словом" знак препинания.
					if (i) {		// Если слово не было выведено (единица нажата сразу после значащих цифр или после звездочки)
									//	необходимо вывести слово (если единица нажата после пробела - i==0, все уже выведено).
						//(*w).useIt(w);
						// useIt:		
						/*
							cout << w->text;
							if (w->code[0]!='1') {
								word::num++;
								word::words.insert(word(w->code,w->text,w->weight+1));
								word::words.erase(w);
							}
						*/
						word::useIt(*w);
						// used...

					}

					// Сделаем вид, что мы честно ввели единицу.
					w = word::words.begin();
					code[0] = '1';
					code[1] = 0;
					i = 2;	// Слово введено.
					break;
				case 42:	// Это звездочка. Ее задача - пролистывать слова по порядку.
					w++;
					//if (w == word::words.end() || !(*w).checkCode(code)) { // Подходящие слова кончились - надо вернуться к первому.
					if (w == word::words.end() || strcmp(w->code.c_str(),code)) { // Подходящие слова кончились - надо вернуться к первому.
						w = find_if(word::words.begin(), word::words.end(), wordWithCode(code));
						if (w == word::words.end()) cout << "> Word not found! [" << code << "]";	// Ничего не нашли
					}
					i = -1;	// Слово, в принципе, готово (указатель установлен, code заполнен).
					break;
				case 10: case 13:
				default:
					// Пора выходить. При этом надо вывести слово, если оно есть.
					//if (i) (*w).useIt(w);
					if (i) {
						// useIt:		
						/*
							cout << w->text;
							if (w->code[0]!='1') {
								word::num++;
								word::words.insert(word(w->code,w->text,w->weight+1));
								word::words.erase(w);
							}
						*/
						word::useIt(*w);
						// used...
					}
			}
		}
	} while (c != 10 && c != 13);


/*
	// Для определения скорости
	cout << endl << endl << endl << "--------------------------" << endl << "Performance:" << endl;
	clock_t ct2 = clock();
	cout << "Clocks per second: " << CLOCKS_PER_SEC << endl;
	cout << "Execute clocks: " << (ct2-ct1) << endl;
	cout << "Execute time: " << (double)(ct2-ct1)/CLOCKS_PER_SEC << " sec." << endl;
	_getch();
*/
	return 0;
}