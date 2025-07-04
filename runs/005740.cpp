// T9.cpp: Реализация Т9
// добавить быстрый поиск

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

#define WORD_LENGTH 20


struct Word { //слово
	string word;
	int P; //общая частота встречаемости
	int P_now; //каким по счёту был вызван (default: 0, при каждом вызове +1 от максимума в этом же списке)
};

typedef multimap<int, Word> Dictionary;  //словарь


char numLit (char lit) {
	if (lit >= 'm') {
		if (lit >= 't') {
			if (lit >= 'w')
				return '9';
			else return '8';
		} else {
			if (lit >= 'p')
				return '7';
			else return '6';
		}
	} else {
		if (lit >= 'g') {
			if (lit >= 'j')
				return '5';
			else return '4';
		} else {
			if (lit >= 'd')
				return '3';
			else return '2';
		}		
	}
}





typedef Dictionary::iterator It;

int main(){

	It it; //итератор
    //char* line;
	char* c_word;
	char ch;
	c_word = "";
	string tmp_word;
	string tmp;
	int P; //частота встречаемости
	int k, i, j;
	bool first = true;
	int Nwords; //количество слов
	char input; //ввода пользователем цифр
	int Nstars = 0; //количество нажатых звездочек.
	Dictionary Dic;
	int key;
	Word word;
	int size; //размер слова при вводе
	int size_stars; 
	int size_1;
	int max;

	//СЧИТЫВАНИЕ СЛОВ В СЛОВАРЬ
	
	
	cin>>Nwords;
	
	for (i = 0; i < Nwords; i++) {
		cin>>tmp_word>>P;
		size = tmp_word.length();
		c_word = (char*)calloc(sizeof(char),size);
		for (j = 0; j < size; j++) 
			c_word[j] = numLit(tmp_word.c_str()[j]);
		key = atoi(c_word);
		word.P = P;
		word.P_now = 1;
		word.word = tmp_word;
		Dic.insert(make_pair(key, word));
		//cout<<tmp_word<<P<<key<<endl;
	}	

	//СЧИТЫВАНИЕ НАБОРА T9	
	int countSp; //количество пробелов
	ch = ' ';	
	
	cin >> noskipws;
	while (cin) {
		tmp_word = "";
		if (ch != ' ')
			tmp_word += ch;
		countSp = 0;
		
		cin >> ch;
		while (ch != ' ' )
		{
			tmp_word += ch;
			if (!(cin >> ch))
				break;
		}
		countSp++;
		cin >> ch;
		while (ch == ' ')
		{
			countSp++;
			cin >> ch;
		}
	
		size = -1;
		Nstars = 0;
		//парсинг одного слова
		size_1 = tmp_word.find_first_of('1');		
		size_stars = tmp_word.find_first_of('*'); 
			if (size_stars > 0) 
				if (size_1 > size_stars)
					Nstars = tmp_word.length() - size_stars - (tmp_word.length() - size_1); //если есть после звёзд '1'
				else if (size_1 == -1)
					Nstars = tmp_word.length() - size_stars;//подсчёт количество нажатных звёздочек

		if (size_1 > -1)
			size = tmp_word.length() - Nstars - (tmp_word.length() - size_1);
		if (size == -1) 
			size = tmp_word.length() - Nstars;
		if (size_1 != 0) {
			tmp = tmp_word.substr(0,size);
			key = atoi(tmp.c_str()); //ключ
			switch (Dic.count(key)) //поиск значений ключа в словаре
			{
			case 1: {			//если найдено 1 значение
				it = Dic.find(key);
				cout<<it->second.word;			
				break;
			default:		//если найдено > 1 значения
				{
					pair<It,It> pos; //текущее слово, следующее слово отличающееся по комбинации кнопок
					vector<It> it_array; //отсортированный массив элементов словаря 
					vector<It>::iterator it_arrayIter;
					bool insert = false; 
					max = 0;

					pos = Dic.equal_range(key);				
					//сортировка слов
					for (; pos.first != pos.second; pos.first++) {
						if (pos.first->second.P_now > max) //для учёта порядка вставки строк в текущем сообщении
							max = pos.first->second.P_now;

						insert = false;
						for(i = 0; i < it_array.size(); i++) { ///по максимальной частоте						
							if (pos.first->second.P > it_array[i]->second.P) {
								it_arrayIter = it_array.begin();
								it_arrayIter = it_arrayIter + i;
								it_array.insert(it_arrayIter, pos.first);
								insert = true;
								break;						
							} else if (pos.first->second.P == it_array[i]->second.P) { //по порядку вызовов
								if (pos.first->second.P_now > it_array[i]->second.P_now) {
									it_arrayIter = it_array.begin();
									it_arrayIter = it_arrayIter + i;
									it_array.insert(it_arrayIter, pos.first); 
									insert = true;
									break;	
								}
							}
						}
						if (!insert) { //если самая маленькая частота
							it_array.push_back(pos.first);				
						}												
					}
					cout<<it_array[Nstars]->second.word; //вывод слова
					it_array[Nstars]->second.P_now += max; //учёт порядка выдачи слов
					it_array[Nstars]->second.P++; //увеличение частоты				
				}
			}
		}
		}
	//вывод знаков препинания
	if (size_1 != -1) 
		for (i = 0; i < tmp_word.substr(size_1).length(); i++) {
			if (tmp_word.substr(size_1).c_str()[i] == '*') {			
				if (i-k == 1 && i == tmp_word.substr(size_1).length() - 1)
					cout<<',';
				else if (tmp_word.substr(size_1)[i+1] == '1')
					cout<<',';
				else {
					cout<<'?';
				i++;
				}
			}

			if (tmp_word.substr(size_1).c_str()[i] == '1')  {
				if (i == tmp_word.substr(size_1).length() - 1) 
					cout<<'.';
				else if (tmp_word.substr(size_1)[i+1] == '1')
					cout<<'.';
				else 
					k = i;
			}
		 }
		while (countSp) {
			cout<<" ";
			countSp--;
		}
	}
   
	return 0;

}

