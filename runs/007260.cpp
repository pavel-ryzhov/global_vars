#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

//#include <conio.h>

using namespace std;


struct SMYWORD
{
	string str; //слово
	int freq; //его частота
	int iter;
	int lastmeeting; //расстояние до последнего ввода. конкретно - порядковый номер с конца последнего появления такого слова в векторе UsedWords
	bool used; //флаг, использовалось ли такое слово или нет
};

struct ITERS
{
	int m[20][9];
};


vector<SMYWORD> vwDict;

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
записывает в вектор words слова, найденные в словаре dict.
Используя информацию о раннее напечатанных словах, соответствующим образом обрабатывает заносимые слова.
*/
void FindWords(vector<int> *words, vector<int> *buttons, ITERS *iters);

/*UpdateDict()
Обновляет в словаре значение частоты слова word.
*/
bool UpdateDict(vector<SMYWORD> *dict, SMYWORD *word);

/* IsCorrect()
возвращает true, если ch - это либо цифра (1-9), либо символ '*', либо пробел.
*/
bool IsCorrect(char ch);

bool cmpf(SMYWORD w1, SMYWORD w2);
bool cmpfi(int w1, int w2);

int main()
{
	bool bTypingWord = true; //bTypingWord == true, если идет ввод слова
	char cSings[] = {'.',',','?'},
		 chTemp;
	int N; //количество слов в словаре
	vector<int> viWord; //содежрит цифры, введение пользователем
	//vector<MYWORD> vwUsedWords; //содержит уже введенные пользователем слова. 
	vector<int> vwWords; //содержит итераторы найденных в словаре слов
	string Text; //сюда производится запись напечатанного пользователем. В конце содержимое этой строки записывается в файл "sms"
	string input;

	ITERS iters;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j<9; j++)
			iters.m[i][j] = -1;

	//Text.clear(); 
	string str;
	char ch;
	int fr;
	SMYWORD wTemp;

	cin>>N;
	for (int i = 0; i<N; i++)
	{
		cin>>str;
		wTemp.str = str;
		cin>>fr;
		wTemp.freq = fr;
		//wTemp.iter = i;
		wTemp.used = false;
		wTemp.lastmeeting = 0;
		vwDict.push_back(wTemp);
	}

	//sort;
	sort(vwDict.begin(), vwDict.end(), cmpf);


	for (int i = 0; i<vwDict.size(); i++)
	{
		cout<<vwDict[i].str<<endl;
	}

	for (int i = 0; i<N; i++)
	{
		vwDict[i].iter = i;
		if ((vwDict[i].str[0] >= 'w') && (vwDict[i].str[0] <= 'z') && (iters.m[vwDict[i].str.length()-1][7] == -1)) iters.m[vwDict[i].str.length()-1][7] = i;
		else
		if ((vwDict[i].str[0] >= 't') && (vwDict[i].str[0] <= 'v') && (iters.m[vwDict[i].str.length()-1][6] == -1)) iters.m[vwDict[i].str.length()-1][6] = i;
		else
		if ((vwDict[i].str[0] >= 'p') && (vwDict[i].str[0] <= 's') && (iters.m[vwDict[i].str.length()-1][5] == -1)) iters.m[vwDict[i].str.length()-1][5] = i;
		else
		if ((vwDict[i].str[0] >= 'm') && (vwDict[i].str[0] <= 'o') && (iters.m[vwDict[i].str.length()-1][4] == -1)) iters.m[vwDict[i].str.length()-1][4] = i;
		else
		if ((vwDict[i].str[0] >= 'j') && (vwDict[i].str[0] <= 'l') && (iters.m[vwDict[i].str.length()-1][3] == -1)) iters.m[vwDict[i].str.length()-1][3] = i;
		else
		if ((vwDict[i].str[0] >= 'g') && (vwDict[i].str[0] <= 'i') && (iters.m[vwDict[i].str.length()-1][2] == -1)) iters.m[vwDict[i].str.length()-1][2] = i;
		else
		if ((vwDict[i].str[0] >= 'd') && (vwDict[i].str[0] <= 'f') && (iters.m[vwDict[i].str.length()-1][1] == -1)) iters.m[vwDict[i].str.length()-1][1] = i;
		else
		if ((vwDict[i].str[0] >= 'a') && (vwDict[i].str[0] <= 'c') && (iters.m[vwDict[i].str.length()-1][0] == -1)) iters.m[vwDict[i].str.length()-1][0] = i;
	}
	iters.m[19][8] = vwDict.size();
	for (int i = 19; i >= 0; i--)
	{
		for (int j = 7; j >= 0; j--)
		{
			if (iters.m[i][j] == -1) iters.m[i][j] = iters.m[i][j+1];
		}
		if (i!=0) iters.m[i-1][8] = iters.m[i][0];
	}
	/*for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 9; j++)
			cout<<iters.m[i][j];
		cout<<endl;
	}*/
	
	ch = getchar();
	input.clear();
	int count = 0;
	while(((ch=getchar())!=10)&&(count++ < 100000))
	{
		input += ch;
	}

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
				FindWords(&vwWords, &viWord, &iters); //в вектор vwWords заносятся слова из файла newDictName,
																		 //соответствующие последовательности цифр viWord.
									//присутвие vwUsedWords необходимо для того, чтобы обработать заносимые слова для последующей правильной сортировки
				sort(vwWords.begin(),vwWords.end(), cmpfi); //сортируются слова (с учетом всех требований). Правильная сортировка обеспечивается
													 //перегруженным в классе WORD оператором <
				/*for (int j = 0; j< vwWords.size(); j++)
				{
					cout<<vwWords[j].GetStr()<<endl;
					cout<<vwWords[j].WasUsed()<<endl;
				}*/
				//если '*' - обрабатываем перебор слов.
				int iWordNumber = 0;
				while (chTemp=='*')
				{
					if (++iWordNumber==vwWords.size()) iWordNumber=0;
					chTemp = input[++k];
				}

				//update
				vwDict[vwWords[iWordNumber]].freq++;
				vwDict[vwWords[iWordNumber]].used = true;
				vwDict[vwWords[iWordNumber]].lastmeeting = k;
				//

				//Text += vwWords[iWordNumber].GetStr(); //добавляем в введенное слово в строку Text. В конце работы программы строка Text будет выведена в файл "sms"
				cout<<vwDict[vwWords[iWordNumber]].str;
				viWord.clear();
			}
			if (chTemp == ' ')
			{
				if (!bFileEndSpace) //если это не тот искуственный пробел, используемый для обработки ситуации, когда после последнего слова
									//не нажат ни пропел, ни знак препинания, ни *
				{
					//Text += ' ';
					cout<<' ';
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
				//Text += cSings[iSignNumber]; //заносим в Text выбранный знак препинания
				cout<<cSings[iSignNumber];
			}
			break;
		default:
			cout<<"wrong symbol"<<endl;
			return 1;
			break;
		}
	} while (k<input.size()); //и так обрабатываем всю строку. 
	//cout<<Text<<endl;
	//_getch();
	return 0;
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

void FindWords(vector<int> *words, //сюда будут внесены найденные слова
			vector<int> *buttons, //последовательности цифр (2-9) (нажатий кнопок)
			ITERS *iters)
{
	
	words->clear();
	
	for (int i = iters->m[(*buttons).size()-1][(*buttons)[0]-2]; i<iters->m[(*buttons).size()-1][(*buttons)[0]-1]; i++)
	{
		if ((*buttons).size()!=1)
		{
			bool bCoresp = true; //соответствует или нет слово последовательности цифр
			//если длина слова не равна длине последовательности введенных пользователем цифр, то сразу bCoresp = false
			//if ((*dict)[i].str.length() != (*buttons).size()) continue;
	
			//проверяем соответствие слова последовательности цифр
			unsigned int n;
			for (n = 0; (bCoresp)&&(n<vwDict[i].str.length()); n++)
				bCoresp = bCoresp && IsCharButton(vwDict[i].str[n],(*buttons)[n]);
			//n - позиция, в которой не подошло
			//cout<<"n = "<<n<<endl;
			if (bCoresp) //если подходит
			{
				words->push_back(i); //добавляем в вектор words только что заданный объект, соответствующий новому найденному слову
			}
			else
			{
				//cout<<"ne podoshlo "<<vwDict[i].str<<endl;
				int itemp = i;
				bool b = true;
				while (b)
				{
					i++;
					b = i<iters->m[(*buttons).size()-1][(*buttons)[0]-1];
					//cout<<"test "<<vwDict[i].str<<endl;
					for (int h = n-1; b && (h>=0); h--)
					{
						/*cout<<"vwDict[i].str[h] "<<vwDict[i].str[h]<<endl
							<<"vwDict[itemp].str[h] "<<vwDict[itemp].str[h]<<endl;*/
						b = b && (vwDict[i].str[h] == vwDict[itemp].str[h]);
					}
					//if (b) cout<<"propysheno "<<vwDict[i].str<<" "<<i<<endl;
				}
				i--;
			}
		}
		else
		{
			//if ((*dict)[i].str.length() != 1) continue;
			if (IsCharButton(vwDict[i].str[0],(*buttons)[0]))
			{
				words->push_back(i); //добавляем в вектор words только что заданный объект, соответствующий новому найденному слову
			}
				
		}
	}
	
	if (words->size()==0)  //если ничего не нашли. По условию задачи такого быть не может.
	{
		cout<<"ERROR. There are no appropriate words in the dictionary";
		exit(1);
	}
	//_getch();
}

bool IsCorrect(char c)
{
	return (c==' ')||(c=='*')||((c-'0'>=0)&&(c-'0'<=9));
}

bool cmpfi(int w1, int w2)
{
	//cout<<"operator"<<endl;
	if (vwDict[w1].freq != vwDict[w2].freq) //если частоты разные, то просто сравниваем частоты
		return vwDict[w1].freq > vwDict[w2].freq;
	//далее, если частоты одинаковые
	if (vwDict[w1].used && vwDict[w2].used) //если оба слова встречались, то упорядочиваем по тому, какое из них последний раз вводилось позже
		return vwDict[w1].lastmeeting > vwDict[w2].lastmeeting;
	//если встречалось только одно слово, то сравнение в пользу того, которое встречалось
	if (vwDict[w1].used && (!vwDict[w2].used))
		return true;
	if (vwDict[w2].used && (!vwDict[w1].used))
		return false;
	
	//если частоты одинаковые и ни одно из слов не встречалось, то оставляем по алфавиту.
	return (vwDict[w1].str.compare(vwDict[w2].str)<0);
}

bool cmpf(SMYWORD w1, SMYWORD w2)
{
	bool t;
	int l1 = w1.str.length(),
		l2 = w2.str.length();
	if (l1 == l2) return (w1.str.compare(w2.str)<0);
	if (l1 <  l2) return true;
	return false;
}