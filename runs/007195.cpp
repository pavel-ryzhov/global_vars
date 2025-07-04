#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


struct SMYWORD
{
	string str; //слово
	int freq; //его частота
	int iter;
	int lastmeeting; //расстояние до последнего ввода. конкретно - порядковый номер с конца последнего появления такого слова в векторе UsedWords
	bool used; //флаг, использовалось ли такое слово или нет
};

struct ITERS2
{
	int m[26][9];
};


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
void FindWords(vector<SMYWORD> *dict, vector<SMYWORD> *words, vector<int> *buttons, int *iters, ITERS2 *iters2);

/*UpdateDict()
Обновляет в словаре значение частоты слова word.
*/
bool UpdateDict(vector<SMYWORD> *dict, SMYWORD *word);

/* IsCorrect()
возвращает true, если ch - это либо цифра (1-9), либо символ '*', либо пробел.
*/
bool IsCorrect(char ch);

int main()
{
	bool bTypingWord = true; //bTypingWord == true, если идет ввод слова
	char cSings[] = {'.',',','?'},
		 chTemp;
	int N; //количество слов в словаре
	vector<int> viWord; //содежрит цифры, введение пользователем
	//vector<MYWORD> vwUsedWords; //содержит уже введенные пользователем слова. 
	vector<SMYWORD> vwWords; //содержит найденные в словаре слова
	vector<SMYWORD> vwDict;
	string Text; //сюда производится запись напечатанного пользователем. В конце содержимое этой строки записывается в файл "sms"
	string input;

	int iters[27];
	ITERS2 iters2;
	for (int i = 0; i<26; i++)
		for (int j = 0; j<9; j++)
			iters2.m[i][j] = -1;

	for (int i = 0; i < 27; i++)
		iters[i] = -1;

	//Text.clear(); 
	string str;
	char ch;
	int fr;
	SMYWORD wTemp;

	cin>>N;
	for (int i = 0; i<N; i++)
	{
		cin>>str;
		if ((iters[(int)(str[0]-'a')] == -1)) iters[(int)(str[0]-'a')] = i;
		wTemp.str = str;
		cin>>fr;
		wTemp.freq = fr;
		wTemp.iter = i;
		wTemp.used = false;
		wTemp.lastmeeting = 0;
		vwDict.push_back(wTemp);
	}
	iters[26] = vwDict.size();
	for (int i = 25; i>=0; i--)
	{
		if (iters[i] == -1) iters[i] = iters[i+1];
	}
	/*for (int i = 0; i < 27; i++)
	{
		cout<<(char)(i+'a')<<iters[i]<<endl;
		//cout<<vwDict[iters[i]].GetStr()<<endl;
	}*/
	
	for (int it1 = 0; it1<26; it1++)
	{
		//cout<<"iters[it1+1]: "<<iters[it1+1]<<"   iters[it1]: "<<iters[it1]<<endl;
		for (int it2 = 0; it2 < iters[it1+1] - iters[it1]; it2++)
		{
			//cout<<"vwDict[iters[it1]+it2].GetStr(): "<<vwDict[iters[it1]+it2].GetStr()<<endl;
			if (vwDict[iters[it1]+it2].str.size() == 1) ;
			else
			{
				if ((vwDict[iters[it1]+it2].str[1] >= 'w') && (vwDict[iters[it1]+it2].str[1] <= 'z') && (iters2.m[it1][7] == -1)) iters2.m[it1][7] = it2;
				if ((vwDict[iters[it1]+it2].str[1] >= 't') && (vwDict[iters[it1]+it2].str[1] <= 'v') && (iters2.m[it1][6] == -1)) iters2.m[it1][6] = it2;
				if ((vwDict[iters[it1]+it2].str[1] >= 'p') && (vwDict[iters[it1]+it2].str[1] <= 's') && (iters2.m[it1][5] == -1)) iters2.m[it1][5] = it2;
				if ((vwDict[iters[it1]+it2].str[1] >= 'm') && (vwDict[iters[it1]+it2].str[1] <= 'o') && (iters2.m[it1][4] == -1)) iters2.m[it1][4] = it2;
				if ((vwDict[iters[it1]+it2].str[1] >= 'j') && (vwDict[iters[it1]+it2].str[1] <= 'l') && (iters2.m[it1][3] == -1)) iters2.m[it1][3] = it2;
				if ((vwDict[iters[it1]+it2].str[1] >= 'g') && (vwDict[iters[it1]+it2].str[1] <= 'i') && (iters2.m[it1][2] == -1)) iters2.m[it1][2] = it2;
				if ((vwDict[iters[it1]+it2].str[1] >= 'd') && (vwDict[iters[it1]+it2].str[1] <= 'f') && (iters2.m[it1][1] == -1)) iters2.m[it1][1] = it2;
				if ((vwDict[iters[it1]+it2].str[1] >= 'a') && (vwDict[iters[it1]+it2].str[1] <= 'c') && (iters2.m[it1][0] == -1)) 
				{
					iters2.m[it1][0] = it2;
				}
			}
		}
		iters2.m[it1][8] = iters[it1+1] - iters[it1];
		for (int i = 7; i>=0; i--)
		{
			if (iters2.m[it1][i] == -1) iters2.m[it1][i] = iters2.m[it1][i+1];
		}
	}
	//cout<<"qqqq"<<endl;
	/*for (int i = 0; i<26; i++)
	{
		for (int j = 0; j<9; j++)
			cout<<iters2.m[i][j]<<' ';
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
				FindWords(&vwDict, &vwWords, &viWord, iters, &iters2); //в вектор vwWords заносятся слова из файла newDictName,
																		 //соответствующие последовательности цифр viWord.
									//присутвие vwUsedWords необходимо для того, чтобы обработать заносимые слова для последующей правильной сортировки
				sort(vwWords.begin(),vwWords.end()); //сортируются слова (с учетом всех требований). Правильная сортировка обеспечивается
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
				vwDict[vwWords[iWordNumber].iter].freq = 1+vwWords[iWordNumber].freq;
				vwDict[vwWords[iWordNumber].iter].used = true;
				vwDict[vwWords[iWordNumber].iter].lastmeeting = k;
				//

				//Text += vwWords[iWordNumber].GetStr(); //добавляем в введенное слово в строку Text. В конце работы программы строка Text будет выведена в файл "sms"
				cout<<vwWords[iWordNumber].str;
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

void FindWords(vector<SMYWORD> *dict, 
			vector<SMYWORD> *words, //сюда будут внесены найденные слова
			vector<int> *buttons, //последовательности цифр (2-9) (нажатий кнопок)
			int *iters, //здесь все введенные ранее слова
			ITERS2 *iters2)
{
	
	words->clear();
	
	
	int its, ite;
	if ((*buttons)[0]==9) its = 22;
	if ((*buttons)[0]==8) its = 19;
	if ((*buttons)[0]==7) its = 15;
	if ((*buttons)[0]<7)  its = 3 * ((*buttons)[0]-2);
	
	if ((*buttons)[0]==9) ite = 26;
	if ((*buttons)[0]==8) ite = 22;
	if ((*buttons)[0]==7) ite = 19;
	if ((*buttons)[0]<7)  ite = 3 * ((*buttons)[0]-1);
	//cout<<"buttons: "<<(*buttons)[0]<<"  its: "<<its<<"  its: "<<ite<<endl;
	for (int i = iters[its]; i<iters[ite]; i++)
	{
		if ((*buttons).size()!=1)
		{
			bool bg1, bg2, bg3 = false, bg0, b79b;
			b79b = ((*buttons)[0] == 7)||((*buttons)[0] == 9);
			bg0 = ( iters[its] + iters2->m[its][(*buttons)[1]-2] <= i) && (i <  iters[its] + iters2->m[its][(*buttons)[1]-1]);
			bg1 = ( iters[its+1] + iters2->m[its+1][(*buttons)[1]-2] <= i) && (i <  iters[its+1] + iters2->m[its+1][(*buttons)[1]-1]);
			bg2 = ( iters[its+2] + iters2->m[its+2][(*buttons)[1]-2] <= i) && (i <  iters[its+2] + iters2->m[its+2][(*buttons)[1]-1]);
			if (b79b) bg3 = ( iters[its+3] + iters2->m[its+3][(*buttons)[1]-2] <= i) && (i <  iters[its+3] + iters2->m[its+3][(*buttons)[1]-1]);
			
			/*cout<<"buttons01: "<<(*buttons)[0]<<(*buttons)[1]<<endl;
			cout<<"i: "<<i<<endl;
			cout<<"iters[its]: "<<iters[its]<<endl;
			cout<<"iters[ite]: "<<iters[ite]<<endl;
			cout<<"iters2->m[its][(*buttons)[1]-2]: "<<iters2->m[its][(*buttons)[1]-2]<<endl;
			cout<<"iters2->m[its+1][(*buttons)[1]-2]: "<<iters2->m[its+1][(*buttons)[1]-2]<<endl;
			cout<<"iters2->m[its+2][(*buttons)[1]-2]: "<<iters2->m[its+2][(*buttons)[1]-2]<<endl;

			cout<<"b79b "<<b79b<<endl;
			cout<<"bg0 "<<bg0<<endl;
			cout<<"bg1 "<<bg1<<endl;
			cout<<"bg2 "<<bg2<<endl;
			cout<<"bg3 "<<bg3<<endl;*/
			if ((b79b&&(bg0||bg1||bg2||bg3))  ||  (!b79b&&(bg0||bg1||bg2)))
			{
				SMYWORD wTemp;
				bool bCoresp = true; //соответствует или нет слово последовательности цифр
				//если длина слова не равна длине последовательности введенных пользователем цифр, то сразу bCoresp = false
				if ((*dict)[i].str.length() != (*buttons).size()) continue;
		
				//проверяем соответствие слова последовательности цифр
				unsigned int n;
				for (n = 0; (bCoresp)&&(n<(*dict)[i].str.length()); n++)
					bCoresp = bCoresp && IsCharButton((*dict)[i].str[n],(*buttons)[n]);
				//cout<<"n = "<<n<<endl;
				//n - позиция в слове, где впервые не совпала цифра и буква.
				if (bCoresp) //если подходит
				{
					wTemp.str = (*dict)[i].str;
					wTemp.freq = (*dict)[i].freq;
					wTemp.iter = (*dict)[i].iter;
					wTemp.used = (*dict)[i].used;
					wTemp.lastmeeting = (*dict)[i].lastmeeting;
					//проверяем, вводилось ли уже это слово. То есть, ищем его в векторе used.
				
					words->push_back(wTemp); //добавляем в вектор words только что заданный объект, соответствующий новому найденному слову
				}
				else
				{
					bool flag = false;
					int itemp = i;
					while ((!flag)&&(i<iters[(*buttons)[0]-1]-1))
					{
						if ((*dict)[i+1].str.size() < n+1) 
						{
							flag = true;
							break;
						}
						for (int h = n; h>=0; h--)
						{
							if ((*dict)[i+1].str[h] != (*dict)[itemp].str[h]) 
							{
								flag = true;
								break;
							}
						}
						if (flag) break;
							i++;
					}	
				}
			}
		}
		else
		{
			if ((*dict)[i].str.length() != 1) continue;
			if (IsCharButton((*dict)[i].str[0],(*buttons)[0]))
			{
				SMYWORD wTemp;
				wTemp.str = (*dict)[i].str;
				wTemp.freq = (*dict)[i].freq;
				wTemp.iter = (*dict)[i].iter;
				wTemp.used = (*dict)[i].used;
				wTemp.lastmeeting = (*dict)[i].lastmeeting;
				//проверяем, вводилось ли уже это слово. То есть, ищем его в векторе used.
				words->push_back(wTemp); //добавляем в вектор words только что заданный объект, соответствующий новому найденному слову
			}
				
		}
	}
	
	if (words->size()==0)  //если ничего не нашли. По условию задачи такого быть не может.
	{
		cout<<"ERROR. There are no appropriate words in the dictionary";
		exit(1);
	}
}

bool IsCorrect(char c)
{
	return (c==' ')||(c=='*')||((c-'0'>=0)&&(c-'0'<=9));
}

bool operator<(SMYWORD w1, SMYWORD w2)
{
	if (w1.freq != w2.freq) //если частоты разные, то просто сравниваем частоты
		return w1.freq > w2.freq;
	//далее, если частоты одинаковые
	if (w1.used && w2.used) //если оба слова встречались, то упорядочиваем по тому, какое из них последний раз вводилось позже
		return w1.lastmeeting > w2.lastmeeting;
	//если встречалось только одно слово, то сравнение в пользу того, которое встречалось
	if (w1.used && (!w2.used))
		return true;
	if (w2.used && (!w1.used))
		return false;
	
	//если частоты одинаковые и ни одно из слов не встречалось, то оставляем по алфавиту.
	return (w1.str.compare(w2.str)<0);
}