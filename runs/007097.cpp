#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


//объект класса WORD содержит слово и необходимую дополнительную информацию (для сортировки и тд);
class WORD
{
public:
	WORD();
	~WORD();
	void SetStr(string *);
	void SetFreq(int);
	void SetPos(ios::pos_type);
	friend bool operator< (WORD,WORD); //перегрузка нужна для сортировки
	string& GetStr();
	int GetFreq();
	ios::pos_type GetPos();
	void Used(); //установка флага, указывающего, что такое слово уже вводилось
	bool WasUsed(); //возвращает значение этого флага
	void SetLast(int c); //устанавливает расстояние до того момента, когда такое слово в последний раз вводилось
	int GetLast();
private:
	string str; //слово
	int freq; //его частота
	ios::pos_type position; //его положение в файле
	int lastmeeting; //расстояние до последнего ввода. конкретно - порядковый номер с конца последнего появления такого слова в векторе UsedWords
	bool used; //флаг, использовалось ли такое слово или нет
};




/* CheckFile()
проверка файла словаря. 
Если файл правильный, возвращает true, в N - количество слов в словаре, в input - последнюю строку файла (ввод пользователя)
Если файл не правильный, возвращает false
*/
bool CheckFile(char *filename, int *N, string *input);

/* IsStrNum()
проверяет, является ли строка целым числом.
*/
bool IsStrNum(string *str);

/* IsCharNum()
проверяет, является ли символ цифрой.
*/
bool IsCharNum(char ch);

/* IsCharButton()
проверяет, находится ли символ ch на кнопке с цифрой b.
Раскладка взята со стандартной клавиатуры Nokia.
2 - a b c
3 - d e f
4 - g h i
5 - j k l 
6 - m n o 
7 - p q r s 
8 - t u v 
9 - w x y z
*/
bool IsCharButton(char ch, int b);

/* FindWords()
записывает в вектор words слова, найденные в файле filename.
Используя информацию о раннее напечатанных словах, соответствующим образом обрабатывает заносимые слова.
*/
void FindWords(char *filename, vector<WORD> *words, vector<int> *buttons, vector<WORD> *used);

/*UpdateFile()
Обновляет в файле filename значение частоты слова word.
*/
bool UpdateFile(char *filename, WORD *word);

/* IsCorrect()
возвращает true, если ch - это либо цифра (1-9), либо символ '*', либо пробел.
*/
bool IsCorrect(char ch);

/* OutputFile()
выводит str в файл.
*/
bool OutputFile(char *filename, string* str);

/*CopyFile()
Копирует содержимое файла fromName в файл toName.
*/
bool CopyFile(char *fromName, char *toName);

int main()
{
	char   DictName[] = "dict";
	bool bTypingWord = true; //bTypingWord == true, если идет ввод слова
	char cSings[] = {'.',',','?'},
		 chTemp;
	int N; //количество слов в словаре
	vector<int> viWord; //содежрит цифры, введение пользователем
	vector<WORD> vwUsedWords; //содержит уже введенные пользователем слова. 
	vector<WORD> vwWords; //содержит найденные в файле слова
	string Text; //сюда производится запись напечатанного пользователем. В конце содержимое этой строки записывается в файл "sms"
	string input;


	Text.clear(); 
	//--------------------------
	//подгонка под то требование, что входные данные подаются не в файле словаря, а с клавиатуры
	ofstream fout(DictName);
	if (!fout)
	{
		cout<<"Couldnt create "<<DictName<<endl;
		return 1;
	}
	string str;
	char ch;
	int fr;
	cin>>N;
	fout<<N<<endl;
	for (int i = 0; i<N; i++)
	{
		cin>>str;
		cin>>fr;
		fout<<str<<' '<<fr<<endl;
	}
	ch = getchar();
	str.clear();
	while((ch=getchar())!=10)
	{
		str += ch;
		//if (ch==10) break;
	}

	fout<<str<<endl;
	fout.close();
	//--------------------------

	if (!CheckFile(DictName,&N,&input))
	{
		return 1;
	}
	//сейчас в строке input содержится последовательность символов, соответствующая вводу пользователя
	unsigned int k = 0; //итератор для извлечения очередного символа из строки
	chTemp = input[0];
	bool bFileEndSpace = false;
	do
	{
		switch (chTemp)
		{
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			
			bTypingWord = true; //раз нажата цифра (2-9), значит идет ввод слова, а не знаков препинания, пробелов и тд
			viWord.push_back(chTemp-'0'); //накапливаем в векторе viWord цифры. Когда ввод слова будет закончен, по этой 
										  //последовательности будет произведен поиск слов в словаре.
			chTemp = input[++k]; //извлекаем очередной символ

			//если после последних цифр в строке input ничего не стоит
			//то есть пользователь после последнего слова не нажал пробел, 1 или *, то слово все равно должно быть введено.
			if (k==input.size()) //если конец ввода
			{
				bFileEndSpace = true; 
				chTemp = ' '; //обработаем всё так, будто пользователь ввел пробел. Break'а тут нет, так что из switcha не выходим, а попадаем в case' ':
				//и правильно обрабатываем слово. При этом этот мнимый пробел не выводится в Text благодаря флагу bFileEndSpace.
			}
			else break;
		case ' ':
		case '1':
		case '*':
			if (bTypingWord) //если до этого вводилось слово
			{
				bTypingWord = false; //ввод слова закончен
				FindWords(DictName, &vwWords, &viWord, &vwUsedWords); //в вектор vwWords заносятся слова из файла newDictName,
																		 //соответствующие последовательности цифр viWord.
									//присутвие vwUsedWords необходимо для того, чтобы обработать заносимые слова для последующей правильной сортировки
				sort(vwWords.begin(),vwWords.end()); //сортируются слова (с учетом всех требований). Правильная сортировка обеспечивается
													 //перегруженным в классе WORD оператором <
				
				//если '*' - обрабатываем перебор слов.
				int iWordNumber = 0;
				while (chTemp=='*')
				{
					if (++iWordNumber==vwWords.size()) iWordNumber=0;
					chTemp = input[++k];
				}
				if (!UpdateFile(DictName, &vwWords[iWordNumber])) return 1; //обновляем в файле значение частоты введенного слова
				Text += vwWords[iWordNumber].GetStr(); //добавляем в введенное слово в строку Text. В конце работы программы строка Text будет выведена в файл "sms"
				vwUsedWords.push_back(vwWords[iWordNumber]); //заносим в вектор использованных слов новое только что введенное слово
				viWord.clear();
			}
			if (chTemp == ' ')
			{
				if (!bFileEndSpace) //если это не тот искуственный пробел, используемый для обработки ситуации, когда после последнего слова
									//не нажат ни пропел, ни знак препинания, ни *
				{
					Text += ' ';
					chTemp = input[++k];
				}
				break;
			}
			if (chTemp == '1') //знак препинания
			{
				int iSignNumber = 0;
				chTemp = input[++k]; //извлекаем очередной символ
				while (chTemp=='*') //если (и пока) это '*' - перебираем знаки препинания, хранящиеся в массиве cSings[] = {'.',',','?'}
				{
					if (iSignNumber==2) iSignNumber=0;
					else iSignNumber++;
					chTemp = input[++k];
				}
				Text += cSings[iSignNumber]; //заносим в Text выбранный знак препинания
			}
			break;
		default:
			cout<<"wrong symbol"<<endl;
			return 1;
			break;
		}
	} while (k<input.size()); //и так обрабатываем всю строку. 
	cout<<Text<<endl;
	if (!OutputFile("sms",&Text)) return 1; //выводим текст смс в файл "sms"
	return 0;
}

bool CheckFile(char *filename, int *N, string *input)
{
	ifstream fin(filename);
	if (!fin)
	{
		cout<<"ERROR. Couldn't open file"<<endl;
		return false;
	}
	string strN;
	fin>>strN;
	if (!IsStrNum(&strN)) //в первой строке файла словаря должно быть число
	{
		cout<<"ERROR. Bad file. First string is not a positive number"<<endl;
		//getchar();
		return false;
	}
	fin.seekg(0);
	fin>>*N; //считываем число из первой строки файла. По условию это количество слов в словаре

	for (int i = 0; (!fin.eof())&&(i<*N); i++ )
	{
		fin>>strN; //это слово
		if ((!(fin>>strN))||(!IsStrNum(&strN))) //считываем то, что стоит после слова. и сразу же проверяем, число ли это (а должно быть числом - это частота)
		{
			cout<<"ERROR. Bad file."<<endl<<"String number: "<<i<<endl;
			//getchar();
			return false;
		}
	}
	fin.get(); //переход на новую строку.

	//посимвольно считываем последнюю строку, попутно проверяя, правильные ли там символы
	char ch; 
	while ((!fin.eof())&&(IsCorrect(ch = fin.get())))
	{
		*input += ch;
	}
	//cout<<"input = "<<*input<<endl;
	//cout<<"Good file"<<endl;
	
	fin.close();
	return true;
}

bool IsStrNum(string *str)
{
	bool bTemp = true;
	for (unsigned int i=0; (bTemp) && (i < str->length()); i++ )
	{
		if (!IsCharNum((*str)[i])) bTemp = false;
	}
	return bTemp;
}

bool IsCharNum(char c)
{
	return (c>='0')&&(c<='9');
}

bool IsCharButton(char ch, int b)
{
	switch (b)
	{
	case 2: return (ch=='a')||(ch=='A')||(ch=='b')||(ch=='B')||(ch=='c')||(ch=='C');
	case 3: return (ch=='d')||(ch=='D')||(ch=='e')||(ch=='E')||(ch=='f')||(ch=='F');
	case 4: return (ch=='g')||(ch=='G')||(ch=='h')||(ch=='H')||(ch=='i')||(ch=='I');
	case 5: return (ch=='j')||(ch=='J')||(ch=='k')||(ch=='K')||(ch=='l')||(ch=='L');
	case 6: return (ch=='m')||(ch=='M')||(ch=='n')||(ch=='N')||(ch=='o')||(ch=='O');
	case 7: return (ch=='p')||(ch=='P')||(ch=='q')||(ch=='Q')||(ch=='r')||(ch=='R')||(ch=='s')||(ch=='S');
	case 8: return (ch=='t')||(ch=='T')||(ch=='u')||(ch=='U')||(ch=='v')||(ch=='V');
	case 9: return (ch=='w')||(ch=='W')||(ch=='x')||(ch=='X')||(ch=='y')||(ch=='Y')||(ch=='z')||(ch=='Z');
	}
	return false;
}

void FindWords(char *filename, 
			vector<WORD> *words, //сюда будут внесены найденные слова
			vector<int> *buttons, //последовательности цифр (2-9) (нажатий кнопок)
			vector<WORD> *used) //здесь все введенные ранее слова
{
	ifstream in(filename);
	if (!in)
	{
		cout<<"Couldn't open file. FindWords"<<endl;
		exit(1);
	}
	words->clear();
	
	ios::pos_type posTemp; //позиция в файле, с которой начинается данное слово
	int N;
	in>>N; //N - количество слов в словаре
	string str;
	for (int i = 0; i<N; i++)
	{
		int a;
		WORD wTemp; //объект, хранящий слово (строка string) и необходимую дополнительную информацию
		posTemp = in.tellg(); //запоминаем позицию в файле
		in>>str; //считываем слово
		bool bCoresp = true; //соответствует или нет слово последовательности цифр

		//если длина слова не равна длине последовательности введенных пользователем цифр, то сразу bCoresp = false
		if (str.length() != (*buttons).size()) bCoresp = false;

		//проверяем соответствие слова последовательности цифр
		for (unsigned int i = 0; (bCoresp)&&(i<str.length()); i++)
			bCoresp = bCoresp && IsCharButton(str[i],(*buttons)[i]);
		if (bCoresp) //если подходит
		{
			//проверяем, вводилось ли уже это слово. То есть, ищем его в векторе used.
			for (int i = (*used).size() - 1; i>=0; i--)
			{
				if ((*used)[i].GetStr() == str) //уже вводилось
				{
					wTemp.Used(); //устанавливаем флаг "использовалось". Затем по этому флагу будет определяться способ сортировки
					wTemp.SetLast((*used).size() - i); //сохраняем информацию о том, как давно это слово вводилось. Будет использованно для сортировки
					break;
				}
			}
			wTemp.SetStr(&str); //сохраняем само слово
			in>>a; 
			wTemp.SetFreq(a); //частоту
			wTemp.SetPos(posTemp); //и позицию в файле. Затем будет использованно для обновления частоты в файле
			words->push_back(wTemp); //добавляем в вектор words только что заданный объект, соответствующий новому найденному слову
		}
		else in>>a; //если слово не подошло, считываем частоту, чтобы перевести курсор к следующему слову
	}
	if (words->size()==0)  //если ничего не нашли. По условию задачи такого быть не может.
	{
		cout<<"ERROR. There are no appropriate words in the dictionary";
		exit(1);
	}
	in.close();
}

bool IsCorrect(char c)
{
	return (c==' ')||(c=='*')||((c-'0'>=0)&&(c-'0'<=9));
}

bool OutputFile(char *filename, string *str)
{
	ofstream fout(filename);
	if (!fout)
	{
		cout<<"Couldn't open file "<<filename<<endl;
		return false;
	}
	fout<<*str;
	fout.close();
	return true;
}

bool UpdateFile(char *filename, WORD *word)
{
	//создаем временный файл "temp", заполняем его с новым значением частоты слова word, удаляем старый файл, а этот переименовываем в dict
	ofstream fout("temp");
	ifstream fin(filename);
	if (!fin)
	{
		cout<<"couldn't open file "<<filename;
		return false;
	}
	if (!fout)
	{
		cout<<"couldn't open file "<<"temp";
		return false;
	}
	string str;
	char ch;
	//В объекте word хранится позиция в файле, в которой находится данное слово. Поэтому просто посимвольно копируем содержимое файла до этой позиции
	while ((!fin.eof())&&(fin.tellg()<=word->GetPos()))
	{
		ch = fin.get();
		fout.put(ch);
	}
	if (!fin.eof())
	{
		fin>>str>>str;
		fout<<word->GetStr()<<' '<<word->GetFreq() + 1; //вводим слово и новую частоту
	}
	else return false;
	//копируем оставшуюся часть файла
	while (!fin.eof())
	{
		ch = fin.get();
		if (!fin.eof())
		fout.put(ch);
	}
	fin.close();
	fout.close();
	if (!(remove(filename)==0)) //удаляем старый
	{
		cout<<"ne ydalen"<<endl;
		return false;
	}
	rename("temp",filename); //переименовываем новый

	return true;
}

WORD::WORD()
{
	str = "";
	freq = -1;
	position = 0;
	used = false; //изначально слово не использовалось
	lastmeeting = 0; //если used == false, значение lastmeeting не имеет значения
}

WORD::~WORD()
{
}

void WORD::SetStr(string *s)
{
	str = *s;
}

void WORD::SetFreq(int f)
{
	freq = f;
}

void WORD::SetPos(ios::pos_type pos)
{
	position = pos;
}

string& WORD::GetStr()
{
	return str;
}

int WORD::GetFreq()
{
	return freq;
}

ios::pos_type WORD::GetPos()
{
	return position;
}

bool operator<(WORD w1, WORD w2)
{
	if (w1.freq != w2.freq) //если частоты разные, то просто сравниваем частоты
		return w1.freq > w2.freq;
	//далее, если частоты одинаковые
	if (w1.used && w2.used) //если оба слова встречались, то упорядочиваем по тому, какое из них последний раз вводилось позже
		return w1.lastmeeting < w2.lastmeeting;
	//если встречалось только одно слово, то сравнение в пользу того, которое встречалось
	if (w1.used && (!w2.used))
		return true;
	if (w2.used && (!w1.used))
		return false;
	
	//если частоты одинаковые и ни одно из слов не встречалось, то оставляем порядок как есть (по алфавиту).
	return w1.freq > w2.freq;
}

void WORD::Used()
{
	used = true;
}

bool WORD::WasUsed()
{
	return used;
}

int WORD::GetLast()
{
	return lastmeeting;
}

void WORD::SetLast (int c)
{
	lastmeeting = c;
}
