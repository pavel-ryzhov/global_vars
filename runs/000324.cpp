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


// Слово в словаре
class Word
{
public:
	// Слово
	string value;	
	// Набор цифр
	string buttons;
	// Частота
	int count;
	// Приоритет в текущем сообщении
	int currMsgPriority;

	void setButtons()
	{
		int l = (int)this->value.length();
		for (int i = 0; i < l; i++)
			this->buttons += BUTTONS[this->value[i]];
	}
};

bool isRelevant(string buttons, Word word)
{
	int l = buttons.length();
	if (l > (int)word.value.length())
		return false;
	int i = 0;
	while (i < l)
	{
		if (buttons[i] != BUTTONS[word.value[i]])
			return false;
		i++;
	}
	return true;
}

vector<Word> clear(vector<Word> words, string buttons)
{
	int i = 0;
	int l = buttons.length();
	// Чистим по длине
	while (i < (int)words.size())
	{
		if (words[i].value.length() == l)
			break;
		words.erase(words.begin());
	}

	// Чистим снизу
	while (i < (int)words.size())
	{
		if (isRelevant(buttons, words[i]))
			break;
		words.erase(words.begin());
	}

	// Чистим сверху
	i = words.size() - 1;
	while (i > 0)
	{
		if (isRelevant(buttons, words[i]))
			break;
		words.erase(words.begin() + i);
		i--;
	}

	return words;
}

vector<Word> clear2(vector<Word> words, string buttons)
{
	int i = 0;
	while (i < (int)words.size())
	{
		if (isRelevant(buttons, words[i]))
			words.erase(words.begin() + i);
		else
			i++;
	}
	return words;
}

bool compare_1(Word word1, Word word2)
{
	if (word1.value.length() != word2.value.length())
		return word1.value.length() < word2.value.length();

	else
		return word1.value < word2.value;
}

// Функция сравнения слов
bool compare_2(Word word1, Word word2)
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
	vector< vector < vector<Word> > > dictionary;

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
		
		for (int i = 0; i < 9; i++)
		{
			vector< vector<Word> > tmp;
			for (int j = 0; j < 10; j++)
			{
				vector<Word> tmp2;
				tmp.push_back(tmp2);
			}
			this->dictionary.push_back(tmp);
		}

		// Считываем словарь
		for (int i = 0; i < this->wordsCount; i++)
		{		
			cin.getline(buffer, sizeof(buffer) - 1);
			s = buffer;
			Word word;
			word.value = s.substr(0, s.find_first_of(" "));
			word.setButtons();
			word.count = atoi(s.substr(s.find_first_of(" ") + 1, s.length() - (s.find_first_of(" ") + 1)).data());
			word.currMsgPriority = 0;

			int first = BUTTONS[word.value[0]] - 48;
			int second = 0;
			if (word.value.length() > 1)
				second = BUTTONS[word.value[1]] - 48;
			this->dictionary[first - 1][second].push_back(word);
		}

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				sort(this->dictionary[i][j].begin(), this->dictionary[i][j].end(), compare_1);
			}
		}

		// Добавляем знаки препинания в словарь (как слова с отрицательными частотами)
		Word w;
		w.value = ".";
		w.buttons = "1";
		w.count = -1;
		w.currMsgPriority  = 0;
		this->dictionary[0][0].push_back(w);

		w.value = ",";
		w.buttons = "1";
		w.count = -2;
		w.currMsgPriority = 0;
		this->dictionary[0][0].push_back(w);

		w.value = "?";
		w.buttons = "1";
		w.count = -3;
		w.currMsgPriority = 0;
		this->dictionary[0][0].push_back(w);

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
			int l = this->wordsList[i].find_first_of('*');
			if (l < 0)
				l = wordsList[i].length();
			int skipCount = this->wordsList[i].length() - l;
			
			int first = wordsList[i][0] - 48;
			int second = 0;
			if (l > 1)
				second = wordsList[i][1] - 48;
			this->wordsList[i] = this->wordsList[i].substr(0, l);
			vector<Word> relevantWords = this->dictionary[first - 1][second];
			relevantWords = clear(relevantWords, this->wordsList[i]);

			// Сортируем допустимые слова
			sort(relevantWords.begin(), relevantWords.end(), compare_2);

			// Выводим слово на экран
			cout << relevantWords[skipCount].value;
				
			// Увеличиваем частоту встречаемости
			Word w = relevantWords[skipCount];
			int m = 0;
			while (this->dictionary[first - 1][second][m].value != w.value)
				m++;
			if (this->dictionary[first - 1][second][m].count > 0)
			{
				// Увеличиваем частоту встречаемости
				this->dictionary[first - 1][second][m].count++;
				// Устанавливаем приоритет в текущем сообщении
				this->dictionary[first - 1][second][m].currMsgPriority = i + 1;
			}
		}
	}
};

int main()
{
	T9 t9;
	t9.getInputData();
	t9.decodeString();

	/*cout << ".  - " << BUTTONS['.'] << endl;
	cout << ",  - " << BUTTONS[','] << endl;
	cout << "?  - " << BUTTONS['?'] << endl;
	cout << endl;

	cout << "a  - " << BUTTONS['a'] << endl;
	cout << "b  - " << BUTTONS['b'] << endl;
	cout << "c  - " << BUTTONS['c'] << endl;
	cout << endl;

	cout << "d  - " << BUTTONS['d'] << endl;
	cout << "e  - " << BUTTONS['e'] << endl;
	cout << "f  - " << BUTTONS['f'] << endl;
	cout << endl;

	cout << "g  - " << BUTTONS['g'] << endl;
	cout << "h  - " << BUTTONS['h'] << endl;
	cout << "i  - " << BUTTONS['i'] << endl;
	cout << endl;

	cout << "j  - " << BUTTONS['j'] << endl;
	cout << "k  - " << BUTTONS['k'] << endl;
	cout << "l  - " << BUTTONS['l'] << endl;
	cout << endl;

	cout << "m  - " << BUTTONS['m'] << endl;
	cout << "n  - " << BUTTONS['n'] << endl;
	cout << "o  - " << BUTTONS['o'] << endl;
	cout << endl;

	cout << "p  - " << BUTTONS['p'] << endl;
	cout << "q  - " << BUTTONS['q'] << endl;
	cout << "r  - " << BUTTONS['r'] << endl;
	cout << "s  - " << BUTTONS['s'] << endl;
	cout << endl;

	cout << "t  - " << BUTTONS['t'] << endl;
	cout << "u  - " << BUTTONS['u'] << endl;
	cout << "v  - " << BUTTONS['v'] << endl;
	cout << endl;

	cout << "w  - " << BUTTONS['w'] << endl;
	cout << "x  - " << BUTTONS['x'] << endl;
	cout << "y  - " << BUTTONS['y'] << endl;
	cout << "z  - " << BUTTONS['z'] << endl;
	cout << endl;*/

	return 0;
}