#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Слово в словаре
class Word
{
private:
	// Слово
	string _value;
	
	// Частота
	int _count;

	// Приоритет в текущем сообщении
	int _currMsgPriority;
public:
	// Возвращает слово
	string getValue()
	{
		return this->_value;
	}

	// Присваивает значение слова
	void setValue(string value)
	{
		this->_value = value;
	}

	// Возвращает частоту встречаемости
	int getCount()
	{
		return this->_count;
	}

	// Присваивает значение частоты встречаемости
	void setCount(int count)
	{
		this->_count = count;
	}

	// Возвращает приоритет в текущем сообщении
	int getCurrMsgPriority()
	{
		return this->_currMsgPriority;
	}

	// Устанавливает приоритет в текущем сообщении
	void setCurrMsgPriority(int count)
	{
		this->_currMsgPriority = count;
	}
};

// Функция сравнения слов
bool compareWords_2(Word word1, Word word2)
{
	// Если частоты не равны то приоритетное слово определяется по большей частоте
	if (word1.getCount() != word2.getCount())
		return word1.getCount() > word2.getCount();
	
	// Если приоритеты в текущем сообщении не равны то по приоритету
	else if (word1.getCurrMsgPriority() != word2.getCurrMsgPriority())
		return word1.getCurrMsgPriority() > word2.getCurrMsgPriority();

	// Если длины слов не равны то берем более короткое
	else if (word1.getValue().length() != word2.getValue().length())
		return word1.getValue().length() < word2.getValue().length();

	// Иначе определяем поалфавиту
	else
		return word1.getValue() < word2.getValue();
}

// Реализатор алгоритма Т9
class T9
{
private:
	// Словарь
	vector<Word> _dictionary;

	// Количество слов в словаре
	int _wordsCount;

	// Список набранных слов (хранятся последовательности набранных цифр, пробелов, звездочек)
	vector<string> _wordsList;
public:
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
	// Метод чтения входных данных
	void getInputData()
	{
		string s = "";
		char buffer[1024];
		cin.getline(buffer, 1024);
		s = buffer;
		this->_wordsCount = atoi(s.data());

		// Считываем словарь
		for (int i = 0; i < this->_wordsCount; i++)
		{		
			cin.getline(buffer, 1024);
			s = buffer;
			Word word;
			word.setValue(s.substr(0, s.find_first_of(" ")));
			word.setCount(atoi(s.substr(s.find_first_of(" ") + 1, s.length() - (s.find_first_of(" ") + 1)).data()));
			word.setCurrMsgPriority(0);
			this->_dictionary.push_back(word);
		}

		// Добавляем знаки препинания в словарь (как слова с отрицательными частотами)
		Word w;
		w.setValue(".");
		w.setCount(-1);
		w.setCurrMsgPriority(0);
		this->_dictionary.push_back(w);

		w.setValue(",");
		w.setCount(-2);
		w.setCurrMsgPriority(0);
		this->_dictionary.push_back(w);

		w.setValue("?");
		w.setCount(-3);
		w.setCurrMsgPriority(0);
		this->_dictionary.push_back(w);

		cin.getline(buffer, 1024);
		s = buffer;
		
		string word = "";
		// Считываем набранные символы
		for (int i = 0; i < (int)s.length(); i++)
		{
			if (s[i] == ' ')
			{
				if (word.length() > 0)
					this->_wordsList.push_back(word);
				this->_wordsList.push_back(" ");
				word = "";
			}
			else if (s[i] == '1')
			{	
				if (word.length() > 0)
					this->_wordsList.push_back(word);
				word = "1";
			}
			else 
				word += s[i];
		}
		if (word.length() > 0)
			this->_wordsList.push_back(word);
	}
	// Метод разбора строки набранных символов (цифр, звездочек, пробелов)
	void decodeString()
	{
		// Идем по набранным словам
		for (int i = 0; i < (int)this->_wordsList.size(); i++)
		{
			// Найден пробел
			if (this->_wordsList[i] == " ")
			{
				cout << " ";
				continue;
			}

			// Список допустимых слов (отфильтрованных после нажатия клавиши)
			vector<Word> relevantWords = this->_dictionary;
			
			// Сортируем допустимые слова
			sort(relevantWords.begin(), relevantWords.end(), compareWords_2);

			int skipCount = 0;
			// Проходим по символам в слове
			for (int j = 0; j < (int)this->_wordsList[i].length(); j++)
			{
				// Найдена *
				if (this->_wordsList[i][j] == '*')
				{
					skipCount = this->_wordsList[i].length() - j;
					break;
				}
				
				// Определяем символы, соответствующие данной кнопк
				string symbols = this->buttonToSymbols(this->_wordsList[i][j]);
				int k = 0;

				// Проходим по набраным цифрам одного слова
				while (k < (int)relevantWords.size())
				{
					if ((int)relevantWords[k].getValue().length() > j)
					{
						bool isPresent = false;
						// Проходим по символам слова
						for (int m = 0; m < (int)symbols.length(); m++)
						{
							if (relevantWords[k].getValue()[j] == symbols[m])
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
				cout << relevantWords[skipCount].getValue();
					
				// Увеличиваем частоту встречаемости
				Word w = relevantWords[skipCount];
				int n = 0;
				while (this->_dictionary[n].getValue() != w.getValue())
					n++;
				if (this->_dictionary[n].getCount() > 0)
				{
					// Увеличиваем частоту встречаемости
					this->_dictionary[n].setCount(this->_dictionary[n].getCount() + 1);
					// Устанавливаем приоритет в текущем сообщении
					this->_dictionary[n].setCurrMsgPriority(i + 1);
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