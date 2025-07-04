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


class Dict
{
public:
	vector<Word> words;
	vector<Dict> dicts;
	void setDict(vector<Word> wordsList, int length)
	{
		vector< vector<Word> > tmp;
		for (int i = 0; i < 9; i++)
		{
			vector<Word> tmp2;
			tmp.push_back(tmp2);
		}

		for (int i = 0; i <(int)wordsList.size(); i++)
		{
			if (wordsList[i].value.length() == length)
				this->words.push_back(wordsList[i]);
			else if ((int)wordsList[i].value.length() > length)
			{
				int n = symbolToButton(wordsList[i].value[length - 1]);
				tmp[n - 1].push_back(wordsList[i]);
			}
		}
		for (int i = 0; i < 9; i++)
		{
			Dict d;
			this->dicts.push_back(d);
			if (tmp[i].size() > 0)
			{
				length++;
				this->dicts[i].setDict(tmp[i], length);
			}
		}
	}
	vector<Word> getDict()
	{
		vector<Word> result = this->words;
		for (int i = 0; i < 10; i++)
		{
			vector<Word> r = this->dicts[i].getDict();
			for (int j = 0; j < (int)r.size(); j++)
				result.push_back(r[j]);	
		}
		return result;
	}
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
	//vector< vector< vector< vector <vector<Word> > > > > dictionary;
	//vector< vector<Word> > dictionary;
	vector<Word>* dictionary;

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
	
	// Метод чтения входных данных
	void getInputData()
	{
		string s = "";
		char buffer[4096 * 128];
		cin.getline(buffer, sizeof(buffer) - 1);
		s = buffer;
		this->wordsCount = atoi(s.data());
		
		this->dictionary = new vector<Word>[1000000 * 20];

		// Считываем словарь
		for (int i = 0; i < this->wordsCount; i++)
		{		
			cin.getline(buffer, sizeof(buffer) - 1);
			s = buffer;
			Word word;
			word.value = s.substr(0, s.find_first_of(" "));
			word.count = atoi(s.substr(s.find_first_of(" ") + 1, s.length() - (s.find_first_of(" ") + 1)).data());
			word.currMsgPriority = 0;

			int l = word.value.length();
			int first = symbolToButton(word.value[0]);
			int second = 0;
			int third = 0;
			int forth = 0;
			int fifth = 0;
			int sixth = 0;
			if (word.value.length() > 1)
			{
				second = symbolToButton(word.value[1]);
				if (word.value.length() > 2)
				{
					third = symbolToButton(word.value[2]);
					if (word.value.length() > 3)
					{
						forth = symbolToButton(word.value[3]);
						if (word.value.length() > 4)
						{
							fifth = symbolToButton(word.value[4]);
							if (word.value.length() > 5)
								sixth = symbolToButton(word.value[5]);
						}
					}
				}
			}

			//this->dictionary[first][second][third][l - 1].push_back(word);
			int index = first * 1000000 + second * 100000 + third * 10000 + forth * 1000 + fifth * 100 + sixth * 10 + l - 1;
			this->dictionary[index].push_back(word);
		}

		// Добавляем знаки препинания в словарь (как слова с отрицательными частотами)
		Word w;
		w.value = ".";
		w.count = -1;
		w.currMsgPriority  = 0;
		//this->dictionary[1][0][0][0].push_back(w);
		this->dictionary[1000000].push_back(w);

		w.value = ",";
		w.count = -2;
		w.currMsgPriority = 0;
		//this->dictionary[1][0][0][0].push_back(w);
		this->dictionary[1000000].push_back(w);

		w.value = "?";
		w.count = -3;
		w.currMsgPriority = 0;
		//this->dictionary[1][0][0][0].push_back(w);
		this->dictionary[1000000].push_back(w);

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
			int forth = 0;
			int fifth = 0;
			int sixth = 0;
			int l2 = 1;
			if (l > 1)
			{
				second = wordsList[i][1] - 48;
				l2 = 2;
				if (l > 2)
				{
					third = wordsList[i][2] - 48;
					l2 = 3;
					if (l > 3)
					{
						forth = wordsList[i][3] - 48;
						l2 = 4;
						if (l > 4)
						{
							fifth = wordsList[i][4] - 48;
							l2 = 5;
							if (l > 5)
							{
								l2 = 6;
								sixth = wordsList[i][5] - 48;
							}
						}
					}

				}
			}
			int index = first * 1000000 + second * 100000 + third * 10000 + forth * 1000 + fifth * 100 + sixth * 10 + l - 1;
			//vector<Word> relevantWords = this->dictionary[first][second][third][l - 1];
			vector<Word> relevantWords = this->dictionary[index];

			// Сортируем допустимые слова
			sort(relevantWords.begin(), relevantWords.end(), compareWords_2);
			
			int skipCount = this->wordsList[i].length() - l;
			// Проходим по символам в слове
			if (l > 6)
			{
			for (int j = 6; j < l; j++)
			{
				// Определяем символы, соответствующие данной кнопк
				string symbols = this->buttonToSymbols(this->wordsList[i][j]);

				// Проходим по набраным цифрам одного слова
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
			//while (this->dictionary[first][second][third][l - 1][m].value != w.value)
			while (this->dictionary[index][m].value != w.value)
				m++;
			//if (this->dictionary[first][second][third][l - 1][m].count > 0)
			if (this->dictionary[index][m].count > 0)
			{
				// Увеличиваем частоту встречаемости
				//this->dictionary[first][second][third][l - 1][m].count++;
				this->dictionary[index][m].count++;
				// Устанавливаем приоритет в текущем сообщении
				//this->dictionary[first][second][third][l - 1][m].currMsgPriority = i + 1;
				this->dictionary[index][m].currMsgPriority = i + 1;
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