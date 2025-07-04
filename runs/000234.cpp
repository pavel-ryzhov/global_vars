#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Слово в словаре
class Word
{
public:
	// Слово
	string value;	
	// Частота
	int count;
	// Приоритет в текущем сообщении
	int currMsgPriority;
};

// Функция сравнения слов
bool compareWords_2(Word word1, Word word2)
{
	// Если частоты не равны то приоритетное слово определяется по большей частоте
	if (word1.count != word2.count)
		return word1.count > word2.count;
	
	// Если приоритеты в текущем сообщении не равны то по приоритету
	else if (word1.currMsgPriority != word2.currMsgPriority)
		return word1.currMsgPriority > word2.currMsgPriority;

	// Если длины слов не равны то берем более короткое
	else if (word1.value.length() != word2.value.length())
		return word1.value.length() < word2.value.length();

	// Иначе определяем поалфавиту
	else
		return word1.value < word2.value;
}

// Реализатор алгоритма Т9
class T9
{
public:
	// Словарь
	vector< vector<Word> > dictionary;
	// Количество слов в словаре
	int wordsCount;
	// Список набранных слов (хранятся последовательности набранных цифр, пробелов, звездочек)
	vector<string> wordsList;
	// Возвращает последовательность символов, соответствующих данной кнопке
	string buttonToSymbols(char button)
	{
		switch (button)
		{
			case '1': return ".,?";
			case '2': return "abc";
			case '3': return "def";
			case '4': return "ghi";
			case '5': return "jkl";
			case '6': return "mno";
			case '7': return "pqrs";
			case '8': return "tuv";
			case '9': return "wxyz";
			default : return "";
		}
	}
	
	int symbolToButton(char symbol)
	{
		switch (symbol)
		{
			case '.' : return 1;
			case ',' : return 1;
			case '?' : return 1;

			case 'a' : return 2;
			case 'b' : return 2;
			case 'c' : return 2;

			case 'd' : return 3;
			case 'e' : return 3;
			case 'f' : return 3;

			case 'g' : return 4;
			case 'h' : return 4;
			case 'i' : return 4;

			case 'j' : return 5;
			case 'k' : return 5;
			case 'l' : return 5;

			case 'm' : return 6;
			case 'n' : return 6;
			case 'o' : return 6;

			case 'p' : return 7;
			case 'q' : return 7;
			case 'r' : return 7;
			case 's' : return 7;

			case 't' : return 8;
			case 'u' : return 8;
			case 'v' : return 8;

			case 'w' : return 9;
			case 'x' : return 9;
			case 'y' : return 9;
			case 'z' : return 9;

			default : return -1;
		}
	}

	// Метод чтения входных данных
	void getInputData()
	{
		string s = "";
		char buffer[1024];
		cin.getline(buffer, 1024);
		s = buffer;
		this->wordsCount = atoi(s.data());

		this->dictionary.resize(9);

		// Считываем словарь
		for (int i = 0; i < this->wordsCount; i++)
		{		
			cin.getline(buffer, 1024);
			s = buffer;
			Word word;
			word.value = s.substr(0, s.find_first_of(" "));
			word.count = atoi(s.substr(s.find_first_of(" ") + 1, s.length() - (s.find_first_of(" ") + 1)).data());
			word.currMsgPriority = 0;
			this->dictionary[this->symbolToButton(word.value[0]) - 1].push_back(word);			
		}

		// Добавляем знаки препинания в словарь (как слова с отрицательными частотами)
		Word w;
		w.value = ".";
		w.count = -1;
		w.currMsgPriority  = 0;
		this->dictionary[0].push_back(w);

		w.value = ",";
		w.count = -2;
		w.currMsgPriority = 0;
		this->dictionary[0].push_back(w);

		w.value = "?";
		w.count = -3;
		w.currMsgPriority = 0;
		this->dictionary[0].push_back(w);

		cin.getline(buffer, 1024);
		s = buffer;
		
		string word = "";
		// Считываем набранные символы
		for (int i = 0; i < (int)s.length(); i++)
		{
			if (s[i] == ' ')
			{
				if (word.length() > 0)
					this->wordsList.push_back(word);
				this->wordsList.push_back(" ");
				word = "";
			}
			else if (s[i] == '1')
			{	
				if (word.length() > 0)
					this->wordsList.push_back(word);
				word = "1";
			}
			else 
				word += s[i];
		}
		if (word.length() > 0)
			this->wordsList.push_back(word);
	}
	// Метод разбора строки набранных символов (цифр, звездочек, пробелов)
	void decodeString()
	{
		// Идем по набранным словам
		for (int i = 0; i < (int)this->wordsList.size(); i++)
		{
			// Найден пробел
			if (this->wordsList[i] == " ")
			{
				cout << " ";
				continue;
			}

			// Список допустимых слов (отфильтрованных после нажатия клавиши)
			//vector<Word> relevantWords = this->dictionary;
			int n = this->wordsList[i][0] - 48;
			vector<Word> relevantWords = this->dictionary[n - 1];
			
			// Сортируем допустимые слова
			sort(relevantWords.begin(), relevantWords.end(), compareWords_2);

			int skipCount = 0;
			// Проходим по символам в слове
			for (int j = 0; j < (int)this->wordsList[i].length(); j++)
			{
				// Найдена *
				if (this->wordsList[i][j] == '*')
				{
					skipCount = this->wordsList[i].length() - j;
					break;
				}
				
				// Определяем символы, соответствующие данной кнопк
				string symbols = this->buttonToSymbols(this->wordsList[i][j]);
				int k = 0;

				// Проходим по набраным цифрам одного слова
				while (k < (int)relevantWords.size())
				{
					if ((int)relevantWords[k].value.length() > j)
					{
						bool isPresent = false;
						// Проходим по символам слова
						for (int m = 0; m < (int)symbols.length(); m++)
						{
							if (relevantWords[k].value[j] == symbols[m])
							{
								isPresent = true;
								break;
							}
						}
						if (!isPresent)
							relevantWords.erase(relevantWords.begin() + k);
						else
							k++;
					}
					else
						relevantWords.erase(relevantWords.begin() + k);
				}
			}

			// Пропускаем слова по нажатию *
			if ((int)relevantWords.size() > skipCount)
			{
				// Выводим слово на экран
				cout << relevantWords[skipCount].value;
					
				// Увеличиваем частоту встречаемости
				Word w = relevantWords[skipCount];
				int m = 0;
				while (this->dictionary[n - 1][m].value != w.value)
					m++;
				if (this->dictionary[n - 1][m].count > 0)
				{
					// Увеличиваем частоту встречаемости
					this->dictionary[n - 1][m].count++;
					// Устанавливаем приоритет в текущем сообщении
					this->dictionary[n - 1][m].currMsgPriority = i + 1;
				}
			}
		}
	}
};

int main()
{
	T9 t9;
	t9.getInputData();

	// Разбираем сообщение
	t9.decodeString();
	return 0;
}