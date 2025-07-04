//1.192
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//структура MYWORD представляет слово
struct MYWORD
{
	MYWORD(){};
	string str; //само слово
	int freq; //текущая частота встречаемости
};

int main()
{
	//весь словарь разбит на двадцать частей. В каждой части слова конкретной длины. Каждая часть является ассоциативным массивом(STL).
	//ключ - это последовательность цифр (ввод пользователя). 
	//значение - это упорядоченный вектор подходящих данному ключу слов (точнее, указателей на слова).
	map< vector<int> , vector<MYWORD*> > Dict[20];

	//input - последовательность цифр, вводимая пользователем
	vector<int> input;

	//в позиции [буква - 'a'] стоит номер соответствующей кнопки
	//           a b c  d e f  g h i  j k l  m n o  p q r s  t u v  w x y z
	int mas[] = {2,2,2, 3,3,3, 4,4,4, 5,5,5, 6,6,6, 7,7,7,7, 8,8,8, 9,9,9,9};

	//temp
	vector<MYWORD*> vwTemp;
	//pair< map< vector<int>  ,  vector<MYWORD*>  >::iterator, bool> mp2;
	int N;
	MYWORD *w;

	cin>>N; // узнаем количество слов в словаре
	for (int i = 0; i<N; i++) //и все их заносим в словарь
	{
		MYWORD *w = new MYWORD; //резервируем память для нового слова
		cin>>w->str>>w->freq; //считываем слово и его частоту
		
		unsigned int len = w->str.length(); // len = длина слова
		vector<int> vi; //вектор для последовательности кнопок, соответствующей данному слову
		for (unsigned int i = 0; i < len; i++) //пробегаем по слову
		{
			vi.push_back(mas[w->str[i] - 'a']); //и добавляем в vi номер кнопки, соответствующей очередной букве слова
		}

		//пытаемся найти в той части словаря, которая хранит слова длины len, элемент, ключ которого совпадает с vi. 
		map< vector<int>  ,  vector<MYWORD*>  >::iterator mp = Dict[len-1].find(vi);
		if (mp==Dict[len-1].end()) //если ничего не нашли, значит в словаре еще не было слов с такой последовательностью нажатий кнопок
		{
			vwTemp.clear();
			vwTemp.push_back(w);
			Dict[len-1].insert(pair< vector<int>  , vector<MYWORD*>  > (vi, vwTemp)); //добавляем в карту новый элемент
			//mp2.first->second.push_back(w); //и добавляем в вектор(пока еще пустой) слов этого элемента новое слово.
		}
		else //если удалось найти. mp - 
		{
			vector<MYWORD*>::iterator iwt = mp->second.end();
			while ((iwt!=mp->second.begin())&&((*(iwt-1))->freq < w->freq)) iwt--;
			mp->second.insert(iwt,w);
		}
	}
	
	getchar();
	input.clear();
	bool bTypingWord = true;
	char cSings[] = {'.',',','?'};
	bool bFileEndSpace = false;
	char ch = getchar();
	while (ch != 10)
	{
		if ((ch>='2')&&(ch<='9'))
		{
			bTypingWord = true;
			input.push_back(ch-'0');
			ch = getchar();
		}
		if ((ch==' ')||(ch=='1')||(ch=='*')||(ch==10))
		{
			if (bTypingWord)
			{
				bTypingWord = false;
				map< vector<int>  ,  vector<MYWORD*>  >::iterator mp = Dict[input.size()-1].find(input);
				vector<MYWORD*>::iterator iWordNumber = mp->second.begin();
				int pos = 0;
				while (ch=='*')
				{
					if (++iWordNumber == mp->second.end()) 
					{
						iWordNumber = mp->second.begin();
						pos = 0;
					}
					pos++;
					ch = getchar();
				}
				cout<<(*iWordNumber)->str;
				(*iWordNumber)->freq++;
				if ((mp->second.size() > 1)&&(iWordNumber!=mp->second.begin())&&((*iWordNumber)->freq >= (*(iWordNumber-1))->freq))
				{
					w = *iWordNumber;
					mp->second.erase(iWordNumber);
					iWordNumber = mp->second.begin() + pos;
					while ((iWordNumber!=mp->second.begin())&&((*(iWordNumber-1))->freq <= w->freq)) iWordNumber--;
					mp->second.insert(iWordNumber,w);
				}
				input.clear();
			}
			if (ch == ' ')
			{
				cout<<' ';
				//putchar(' ');
				ch = getchar();
			}
			if (ch == '1')
			{
				int iSignNumber = 0;
				ch = getchar();
				while (ch=='*')
				{
					if (iSignNumber==2) iSignNumber=0;
					else iSignNumber++;
					ch = getchar();
				}
				cout<<cSings[iSignNumber];
				//putchar(cSings[iSignNumber]);
			}
		}
	}
	//_getch();
	return 0;
}