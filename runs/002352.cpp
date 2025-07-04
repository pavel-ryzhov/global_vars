/*
 * DONE by Vasily Demidenok
 */

#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <list>
#include <stdexcept>
#include <fstream>

#define MIN_DICT_NUM 3
#define MAX_DICT_NUM 50000
#define MIN_SUPP 1
#define MAX_SUPP 1000

using namespace std;

class Word;

typedef list<Word *> 			Words;
typedef map<int, Words > 		Dict;
typedef list<Word *>::iterator 		WordsIter;
typedef map<int, Words >::iterator 	DictIter;

/*
 * Класс исключения для всех ошибок в программе
 */
class MyExcept
{
public:
	string message;
	MyExcept(string _mess) : message(_mess) {};
};

/*
 * Класс который представляет собой слово в словаре с частотой его появления
 */
class Word
{
private:
	string	_word;		// Само слово
	int 	_supp;		// Частота встречаемости слова
	
public:
	Word(string word, int supp)
	{
		this->_word = word;
		this->_supp = supp;
	}
	string 	returnName() const	{	return this->_word;	}
	int 	returnSupp() const	{	return this->_supp;	}
	void 	increase()			{	this->_supp++;		}
	virtual ~Word()				{}
};
/*
 Класс необходимый для подбора необходимого слова по числовому коду и количеству нажатий звёздочки. Так же
 он изменяет значение частоты слова после его использования, изменяя последовательность в словаре.
 */
class FunctorWords
{
private:
	Dict &_dict;
	
public:
	FunctorWords(Dict &dict): _dict(dict) {};
	
	virtual string operator()(int slovo, int perexod)
	{
		Dict::iterator om = _dict.find(slovo);
		if (om == _dict.end()) 
			throw MyExcept ("Error: Word dictionary with a word code is missing");
		Words &words = om->second;
			
		// Находим позицию нужного нам элемента
		int step = perexod % words.size();
		WordsIter itD = words.begin();
		for (int i = 0; i < step; i++)
			itD++;
			
		// Вырезаем слово и увеличиваем частоту
		Word *word = new Word( **itD );
		word->increase();
		words.erase(itD);
			
		WordsIter itS = words.end(), minMax = words.begin();
			
		/*  Находим куда можно вставить и записываем. Последовательность упорядочена по убыванию 
		 *	ищем минимальный из элементов больших заданного (word) и вставляем после него
		 */			
		if ((minMax != words.end()) && ((*minMax)->returnSupp() <= word->returnSupp()))
			words.push_front(word);
		else 
		{
			while ( minMax != words.end() ) 
			{
				if ((*minMax)->returnSupp() > word->returnSupp())
					itS = ++minMax;
				else
					break;
			}
				
			if (itS != words.end())
				words.insert(itS, word);
			else
				words.push_back(word);	
		}
		return word->returnName();

	};
	virtual ~FunctorWords()	{};
};
/*
 Класс который отвечает за вывод знака препинания. 
 */
class FunctorPunctuat
{
private:
	Dict &_dict;
	
public:
	FunctorPunctuat(Dict &dict): _dict(dict) {};
	
	virtual string operator()(int slovo, int perexod)
	{
		Dict::iterator om = _dict.find(slovo);
		if (om == _dict.end()) 
			throw MyExcept ("Error: Word dictionary with a word code is missing");
		Words &words = om->second;
			
		// Находим позицию нужного нам элемента
		int step = perexod % words.size();
		WordsIter itD = words.begin();
		for (int i = 0; i < step; i++)
			itD++;

		return (*itD)->returnName();
	};
	virtual ~FunctorPunctuat() {};
	
};

/////////////////////////////// Основные фунции

int formComputedWord(map<int, string> &dict, string line)
{
	// Функция вычисляет по слову его цифровой код.
	
	int computedWord = 0;
	
	for (string::iterator it = line.begin(); it != line.end(); it++)
	{
		// Пробегаем по всем клавишам
		for (map<int, string>::iterator itD = dict.begin(); itD != dict.end(); itD++)
		{
			string &tempStr = itD->second;
			if  (string::npos != tempStr.find(*it, 0))
			{
				computedWord = computedWord * 10 + itD->first;
				break;
			}
		}
	}
	
	return computedWord;
}

Word* formWord(string &line)
{
	/*
	 * Вытаскивает из строки слово и его частоту и возвращаем класс слова в словаре.
	 */
	
	size_t probel = line.find_last_of(' ');
	
	if (probel != string::npos)
	{
		string name = line.substr(0, probel);
		int supp 	= atoi(line.substr(probel).c_str());
		if ((supp < MIN_SUPP) || (supp > MAX_SUPP ))
			throw MyExcept("Error: Invalid supp num");
		
		return new Word(name, supp);
	}
	
	return NULL;
}

bool compareWords(const Word *first, const Word *second)
{
	/*
	 * Функция для сравнения Words. 
	 */
	if (first->returnSupp() == second->returnSupp())
		return (first->returnName() < second->returnName());
	else
		return (first->returnSupp() > second->returnSupp());
}

void parseLine(string &line, FunctorWords &functWord, FunctorPunctuat &functPunct)
{
	/*
	 * Функция парсит строку и выводит на экран разобранное сообщение. Звездочка означает что выбирает следующее слово
	 * или следующий знак препинания, 
	 * 1 - знак пунктуации, остальные цифры - код слова, пробелы ничего не обозначают.
	 */
	
	bool bWord = false, bPunct = false;
	int perexod = 0, compWord = 0;
	
	for (string::iterator it = line.begin(); it != line.end(); it++)
	{
		if ((*it == ' ') || (*it == '1'))
		{
			// Записываем предыдущее слово или знак если есть + пробел
			if (bWord)
			{
				cout << functWord(compWord, perexod);
				perexod = 0; compWord = 0; bWord = false;
			}
			else if (bPunct)
			{
				cout << functPunct(1, perexod);
				perexod = 0; bPunct = false;
			};
			
			if (*it == ' ')
				cout << *it;
			else
				bPunct = true;
		}
		// увеличиваем переход
		else if (*it == '*')
		{
			if (bWord || bPunct) perexod++;
			else throw MyExcept("Error: Asterisk found but there is no Punct or Word");
		}
		else if (isdigit(*it))
		{
			if (bPunct)
			{
				cout << functPunct(1, perexod);
				perexod = 0; bPunct = false;
			};
			
			if (bWord)
				compWord = compWord * 10 + atoi( string(1, *it).c_str() );
			else
			{
				bWord = true;
				compWord = atoi( string(1, *it).c_str() );
			}
		}
		else
			throw MyExcept("Error: Illegal simbol in the line.");
	}
	if (bWord)
		cout << functWord(compWord, perexod);
	else if (bPunct)
		cout << functPunct(1, perexod);
}

int main()
{
	int wordsAmount = 0, wordsCount = 0;
	Dict dictionary;
	string line;

	map<int, string> dict;
	dict[2] = "abc";
	dict[3] = "def";
	dict[4] = "ghi";
	dict[5] = "jkl";
	dict[6] = "mno";
	dict[7] = "pqrs";
	dict[8] = "tuv";
	dict[9] = "wxyz";

	try
	{
		while(cin)
		{
			getline(cin, line);
			
			// Получаем количество слов в словаре.
			if (wordsAmount == 0)
			{
				wordsAmount = atoi(line.c_str());
				if ((wordsAmount < MIN_DICT_NUM) || (wordsAmount > MAX_DICT_NUM))
					throw MyExcept("Error: Invalid value of number of words");

				continue;
			}
			else
			{
				if (wordsCount < wordsAmount)
				{
					// Формируем слово и записываем в соотвествующий словарь
					Word *newWord = formWord(line);
					if (newWord == NULL)
						throw MyExcept("Error: Failed to parse a word");
					
					// Вычисляем цифровой код слова.
					int computedWord = formComputedWord(dict, newWord->returnName());
					
					// Если словарь отсутствует, то создаём его и добавляем.
					DictIter it = dictionary.find(computedWord);
					if (it == dictionary.end())
						dictionary[computedWord] = Words(1, newWord);
					else
						it->second.push_back(newWord);
					
					wordsCount++;
				}
				else
				{
					// Сперва надо упорядочить слова в каждом из подсловарей Words (по частоте и по имени) по убыванию
					for (DictIter sm = dictionary.begin(); sm != dictionary.end(); sm++)
						sm->second.sort(compareWords);
					
					// Заполняем данные по знакам препинания
					Words words;
					words.push_back(new Word(".", 1));
					words.push_back(new Word(",", 1));
					words.push_back(new Word("?", 1));
					dictionary[1] = words;

					// Парсим последнюю строчку файла и выводим в stdout.
					FunctorWords 	*fuW	= new FunctorWords(dictionary);
					FunctorPunctuat *fuP 	= new FunctorPunctuat(dictionary);
					
					parseLine(line,	*fuW, *fuP);
				}
			}
		}
	}
	catch (MyExcept except)
	{
		std::cerr << except.message;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

