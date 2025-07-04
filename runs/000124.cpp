#include <iostream>
#include <list>
#include <string>

using namespace std;

/*Запись в словаре задаётся:
1. Цифровым ключом (в формате строки)
2. Самим словом
3. Частотой употребления*/
class Entity
{
public:
	string word, code;
	int rank;
	Entity(string ncode, string nword, int nrank) : code(ncode), word(nword), rank(nrank)
	{};
		
};
class DICT : public list<Entity>
{
public:
	void add(string word, int rank);
	iterator updateRank(iterator record);
	iterator findEntity(string code, int rank);
};
DICT Dictionary; //Словарь

string encode(string);
string decode(string);
char nextSymbol(char);
////////////////////////
int main(int argc, char** argv)
{
	int wordCount;
	cin >> wordCount;
	for (int i = 1; i <= wordCount; i++) //Заполнение словаря словами
	{
		string word; int frequency;
		cin >> word >> frequency;
		Dictionary.add(word, frequency);
	}
	string code;
	//Закомментированный элегантный способ не работает в ejudge
	/*cin >> code;
	while (true) //Cчитываем последовательность кодов
	{
		cout << decode(code);
		if (cin >> code)
			cout << " ";
		else
			break;
	}
	cout << endl;*/
	getline(cin,code,'a');
	list<string> codes;
	string tmp = "";
	for (int i = 0; i < code.length(); i++)
	{
		if (code[i] != '\n' && code[i] != ' ')
		{
			tmp += code[i];
		}
		else
		{
			codes.push_back(tmp);
			tmp = "";
		}
	}
	string result = "";
	for(list<string>::iterator i = codes.begin(); i != codes.end(); i++)
	{
		if (*i != "")
			result += decode(*i) + " ";
	}
	cout << result.substr(0,result.length()-1) << endl;
	return 0;
}

////////////////////////
string encode(string word) //Внимание! Нет буквы "p"!
{
	for (int i = 0; i < word.length(); i++)
	{
		switch (word[i])
		{
		case 'a': case 'b': case 'c':
			word[i] = '2';
			break;
		case 'd': case 'e': case 'f':
			word[i] = '3';
			break;
		case 'g': case 'h': case 'i':
			word[i] = '4';
			break;
		case 'j': case 'k': case 'l':
			word[i] = '5';
			break;
		case 'm': case 'n': case 'o':
			word[i] = '6';
			break;
		case 'q': case 'r': case 's':
			word[i] = '7';
			break;
		case 't': case 'u': case 'v':
			word[i] = '8';
			break;
		case 'w': case 'x': case 'y': case 'z':
			word[i] = '9';
			break;
		default:
			break;
		}
	}
	return word;
}
////////////////////////
string decode(string input)
{
	int wordLength = input.length(); //длина слова без управляющих символов "*" и знаков препинания
	string code, symbols; //слово и управляющие символы
	int find1, find2; //первое появление "1" и "*"
	find1 = input.find('1');
	find2 = input.find('*');
	if (find1 != string::npos)
		wordLength = find1;
	if (find2 != string::npos)
	{
		if (find1 == string::npos)
			wordLength = find2;
		else
			wordLength = (find1 < find2) ? find1 : find2;
	}
	symbols = input.substr(wordLength, string::npos);
	code = input.substr(0, wordLength);
	//подсчитываем, какое по счёту слово из словаря нам нужно и какой поставить знак препинания
	bool brank = true; //флаг указывает, что именно мы ищем в последовательности управляющих символов
	int rank = 1;
	char symbol = '\0';
	for (int i = 0; i < symbols.length(); i++)
	{
		if ((symbols[i] != '1') && brank)
			rank++;
		else
		{
			brank = false;
			symbol = nextSymbol(symbol);
		};
	}
	//Ищем слово в словаре
	DICT::iterator bestWord = Dictionary.findEntity(code, rank);
	bestWord = Dictionary.updateRank(bestWord); //повышаем частоту употребления слова
	return bestWord->word + symbol;
}
////////////////////////
char nextSymbol(char symbol)
{
	switch(symbol)
	{
		case '.':
			return ','; break;
		case ',':
			return '?'; break;
		default:
			return '.';
	}
}
////////////////////////
void DICT::add(string word, int rank)
{
	string code = encode(word);
	iterator i = this->begin();
	while (i != this->end())
	{
		if (i->code == code)
			break;
		i++;
	}
	if (i != this->end()) //Если слово найдено
	{
		while (i != this->end() && i->code == code && i->rank > rank)
			i++;
		while(i != this->end() && i->code == code && i->rank == rank && i->word < word)
			i++;
		this->insert(i,Entity(code, word, rank)); //Проверить, как вставить после указателя
	}
	else
	{
		this->push_back(Entity(code, word, rank));
	}
}
////////////////////////
DICT::iterator DICT::updateRank(DICT::iterator record)
{
	record->rank++;
	DICT::reverse_iterator prev(record);	
	DICT::iterator next = record;
	next++;
		
	while (next != this->end() && next->code == record->code && 
		(next->rank > record->rank || (next->rank == record->rank /*&& next->word < record->word*/))
		)
	{
		//Обмен записей значениями
		string tmp1, tmp2; int tmp;
		tmp = record->rank; tmp1 = record->word; tmp2 = record->code;
		record->rank = next->rank; record->word = next->word; record->code = next->code;
		next->rank = tmp; next->word = tmp1; next->code = tmp2;

		record++;
		next++;
	}
	while (prev != this->rend() && prev->code == record->code && 
		(prev->rank < record->rank || (prev->rank == record->rank /*&& prev->word > record->word*/))
		)
	{
		//Обмен записей значениями
		string tmp1, tmp2; int tmp;
		tmp = record->rank; tmp1 = record->word; tmp2 = record->code;
		record->rank = prev->rank; record->word = prev->word; record->code = prev->code;
		prev->rank = tmp; prev->word = tmp1; prev->code = tmp2;
		record--;
		prev++;
	}
	return record;
}
////////////////////////
DICT::iterator DICT::findEntity(string code, int rank)
{
	iterator i = this->begin();
	while (i->code != code) //Считаем, что слово точно нашлось
		i++;
	iterator result = i;
	while (i != this->end() && i->code == code) //Находим слово с макс. частотой
	{
		if (i->rank > result->rank)
			result = i;
		i++;
	}
	for (int j = 1; j < rank; j++) //Если нужно не "лучшее" слово
	{
		result++;
	}
	return result;
}
////////////////////////
