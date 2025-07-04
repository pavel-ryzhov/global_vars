
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string GetButtons(const string &, string &);
int FindIndex(const vector<pair<string,vector<pair<string,unsigned> > > > &, const string &);
string GetString(std::vector<std::pair<string, unsigned> > &, unsigned);
void LoadDict(vector<pair<string,vector<pair<string,unsigned> > > > &) ;
char GetSymbol(unsigned);

int main()
{
	vector<pair<string,vector<pair<string,unsigned> > > > vData; //вектор где хранятся все данные
	//первая пара это последовательность и вектор всех слов, которые относятся к данной последовательности
	//второй вектор так же состоит из пары, само слово и его частота

	LoadDict(vData);//грузим словарь

	cin.get(); //считываем оставшийся 'мусор'

	char chTemp; 
	string strButtons; //введенная последовательность
	bool fComplete = false; //сигнализирует о конце строки с данными
	bool fCompute = false; 
	bool fIsPoint = false; 
	bool fNextPoint = false;	
	unsigned nStarNumb = 0; //количество *
	bool fNeedSpace = false; //если считан пробел

	while(!fComplete)
	{
		fCompute = false;
		fIsPoint = false;

		//посимвольно считываем последнюю строку
		cin.get(chTemp);
		switch(chTemp)
		{
		case '\n':
			fComplete = true;
		case ' ':		
			if(fNextPoint)
			{
				fNextPoint = false;
				fIsPoint = true;
			}
			fNeedSpace = true; //добавляем пробел
			fCompute = true;
			break;
		case '1':
			if(fNextPoint)
			{
				fNextPoint = false;
				fIsPoint = true;
			}
			fNextPoint = true;
			fCompute = true;
			break;
		case '*':
			nStarNumb++;
			break;
		default:
			strButtons += chTemp;
		}

		if(fCompute)
		{
			//обрабатываем введенную последовательность
			if(fIsPoint) //необходимо вывести знак препинания
				cout << GetSymbol(nStarNumb);
			else
			{
				if(strButtons.length() > 0)
				{
					int nIndex = FindIndex(vData, strButtons); //ищем необходимую последовательность
					if(nIndex!=-1)
						cout << GetString(vData[nIndex].second, nStarNumb); //выводим и изменяем частоту
					else
						throw "unknown word";
				}
			}
			if(fNeedSpace && !fComplete)
				cout << " ";

			nStarNumb = 0;
			strButtons.clear();
			fNeedSpace = false;
		}
	}

	return 0;
}

char GetSymbol(unsigned nStarNumb)
{
	//функция возвращает знак препитания, зависящий от количество * (nStarNumb)
	switch(nStarNumb)
	{
	case 0:
		return '.';
	case 1:
		return ',';
	case 2:
		return '?';
	}
	throw "something wrong";
}

string GetString(std::vector<std::pair<string, unsigned> > & vStrings, unsigned nStarNumb)
{
	//функция возвращает 'слово', соответствующие последовательности и частоте
	//а так увеличивает частоту возвращаемого слова и сортирует вектор по частоте
	string strResult = vStrings[nStarNumb].first; 

	//изменияем частоту нажатий + положение в векторе (по частоте)
	pair<string, unsigned> pairTemp(vStrings[nStarNumb]);
	pairTemp.second++; //увеличили частоту на 1

	bool fComplete = false;

	vStrings.erase(vStrings.begin() + nStarNumb);//удалили со старого места обитания

	for(unsigned i=0; i<vStrings.size(); i++) //ищем куда разместить с новой частотой
	{
		if(vStrings[i].second <= pairTemp.second)
		{
			vStrings.insert(vStrings.begin() + i, pairTemp);
			fComplete = true;
			break;
		}
	}
	if(!fComplete) //место для размещения не нашлось
		vStrings.push_back(pairTemp); //размещаем в конце

	return strResult;
}


void LoadDict(vector<pair<string,vector<pair<string,unsigned> > > > & vData)
{
	//функция загружает словарь из файла
	// и сортирует по рейтингу
	unsigned nDictSize; //количество слов в словаре
	cin >> nDictSize;
	
	for(; nDictSize!=0; nDictSize--)
	{
		string strWord; //слово из словаря
		unsigned nRate; //частота встречаемости
		string strButtons; //последовательность кнопок для данного слова

		cin >> strWord;
		cin >> nRate;

		GetButtons(strWord, strButtons); //определяем последовательность

		int nIndex = FindIndex(vData, strButtons); //определяем индекс данной послдеовательности
		if(-1 == nIndex) //такой последовательности раньше не было
		{
			vector<pair<string,unsigned> > vTemp;
			vTemp.push_back(make_pair(strWord, nRate));
			vData.push_back(make_pair(strButtons, vTemp));
		}
		else
		{
			//помещаем слово в начало слов с той же частотой
			bool fComplete = false;
			unsigned i = 0;
			while(!fComplete && i < vData[nIndex].second.size())
			{
				if(nRate > vData[nIndex].second[i].second)
				{
					vData[nIndex].second.insert(vData[nIndex].second.begin() + i, make_pair(strWord, nRate));
					fComplete = true;
				}
				i++;
			}
			if(!fComplete)
				vData[nIndex].second.push_back(make_pair(strWord, nRate));
		}
	}
}


int FindIndex(const vector<pair<string,vector<pair<string,unsigned> > > > & vData, const string & strData)
{
	//возвращает индекс последовательности
	for(unsigned i=0; i<vData.size(); i++)
	{
		if(vData[i].first == strData)
			return i;
	}
	return -1;
}


string GetButtons(const string & strBefore, string & strResult)
{
	//возвращает последовательность, которую надо нажать, что бы получить данное слово (strBefore)
	strResult.clear();
	for(unsigned i=0; i<strBefore.length(); i++)
	{
		switch(strBefore[i])
		{
		case 'a':
		case 'b':
		case 'c':
			strResult.push_back('2');
			break;
		case 'd':
		case 'e':
		case 'f':
			strResult.push_back('3');
			break;
		case 'g':
		case 'h':
		case 'i':
			strResult.push_back('4');
			break;
		case 'j':
		case 'k':
		case 'l':
			strResult.push_back('5');
			break;
		case 'm':
		case 'n':
		case 'o':
			strResult.push_back('6');
			break;
		case 'p':
		case 'q':
		case 'r':
		case 's':
			strResult.push_back('7');
			break;
		case 't':
		case 'u':
		case 'v':
			strResult.push_back('8');
			break;
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			strResult.push_back('9');
			break;
		}
	}
	return strResult;
}