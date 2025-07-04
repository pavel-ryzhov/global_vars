#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const char BUTTONS[256] = 
{
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '0', '0', '0', '0', '0',
	'2', '2', '2', 
	'3', '3', '3',
	'4', '4', '4',
	'5', '5', '5',
	'6', '6', '6', 
	'7', '7', '7', '7',
	'8', '8', '8',
	'9', '9', '9', '9',
	'0', '0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'0', '0', '0', '0', '0', '0' 
};

const string SYMBOLS[58] = 
{
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
	"", "", "", "", "", "", "", 
	".,?", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

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
	vector<Word> dictionary[10][10][10];

	// Количество слов в словаре
	int wordsCount;
	// Список набранных слов (хранятся последовательности набранных цифр, пробелов, звездочек)
	vector<string> wordsList;
	
	// Метод чтения входных данных
	void getInputData()
	{
		string s = "";
		char buffer[4096 * 128];
		cin.getline(buffer, sizeof(buffer) - 1);
		s = buffer;
		this->wordsCount = atoi(s.data());

		// Считываем словарь
		for (int i = 0; i < this->wordsCount; i++)
		{		
			cin.getline(buffer, sizeof(buffer) - 1);
			s = buffer;
			Word word;
			word.value = s.substr(0, s.find_first_of(" "));
			word.count = atoi(s.substr(s.find_first_of(" ") + 1, s.length() - (s.find_first_of(" ") + 1)).data());
			word.currMsgPriority = 0;

			int first = BUTTONS[word.value[0]] - 48;
			int second = 0;
			int third = 0;
			if (word.value.length() > 1)
			{
				second = BUTTONS[word.value[1]] - 48;
				if (word.value.length() > 2)
				{
					third = BUTTONS[word.value[2]] - 48;
				}
			}

			this->dictionary[first][second][third].push_back(word);
		}

		// Добавляем знаки препинания в словарь (как слова с отрицательными частотами)
		Word w;
		w.value = ".";
		w.count = -1;
		w.currMsgPriority  = 0;
		this->dictionary[1][0][0].push_back(w);

		w.value = ",";
		w.count = -2;
		w.currMsgPriority = 0;
		this->dictionary[1][0][0].push_back(w);

		w.value = "?";
		w.count = -3;
		w.currMsgPriority = 0;
		this->dictionary[1][0][0].push_back(w);

		if (cin.eof())
			return;

		cin.getline(buffer, sizeof(buffer) - 1);
		s = buffer;

		if (s.length() <= 0)
		{
			this->wordsList.resize(0);
			return;
		}
		
		string word = "";
		// Считываем набранные символы
		int wordType = 1; // 1 - слово, 2 - знак прпинания
		for (int i = 0; i < (int)s.length(); i++)
		{
			if (s[i] == '1')
			{
				if (word.length() > 0)
					this->wordsList.push_back(word);
				word = '1';
				wordType = 2;
			}
			else if (s[i] == ' ')
			{
				if (word.length() > 0)
					this->wordsList.push_back(word);
				word = "";
				this->wordsList.push_back(" ");
			}
			else if (s[i] == '*')
				word += '*';
			else
			{
				if (wordType == 1)
					word += s[i];
				else
				{
					if (word.length() > 0)
						this->wordsList.push_back(word);
					word = s[i];
				}
				wordType = 1;
			}
		}
		if (word.length() > 0)
			this->wordsList.push_back(word);
	}
	// Метод разбора строки набранных символов (цифр, звездочек, пробелов)
	void decodeString()
	{
		if (wordsList.size() <= 0)
			return;
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
			int l = wordsList[i].find_first_of('*');
			if (l < 0)
				l = wordsList[i].length();
			int first = wordsList[i][0] - 48;
			int second = 0;
			int third = 0;
			if (l > 1)
			{
				second = wordsList[i][1] - 48;
				if (l > 2)
				{
					third = wordsList[i][2] - 48;
				}
			}
			vector<Word> relevantWords = this->dictionary[first][second][third];

			// Сортируем допустимые слова
			sort(relevantWords.begin(), relevantWords.end(), compareWords_2);
			
			int skipCount = this->wordsList[i].length() - l;
			// Проходим по символам в слове
			if (l > 3)
			{
				for (int j = 3; j < l; j++)
				{
					// Определяем символы, соответствующие данной кнопк
					string symbols = SYMBOLS[this->wordsList[i][j]];

					// Проходим по словам
					int k = 0;
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
			}

			// Выводим слово на экран
			cout << relevantWords[skipCount].value;
				
			// Увеличиваем частоту встречаемости
			Word w = relevantWords[skipCount];
			int m = 0;
			while (this->dictionary[first][second][third][m].value != w.value)
				m++;
			if (this->dictionary[first][second][third][m].count > 0)
			{
				// Увеличиваем частоту встречаемости
				this->dictionary[first][second][third][m].count++;
				// Устанавливаем приоритет в текущем сообщении
				this->dictionary[first][second][third][m].currMsgPriority = i + 1;
			}
		}
	}
};

int main()
{
	T9 t9;
	t9.getInputData();
	t9.decodeString();
	return 0;
}