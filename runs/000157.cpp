#include <iostream>
#include <list>
#include <string>
#include <stdio.h>

using namespace std;

class Entity //Запись
{
public:
	string word;
	int rank;
	Entity(string nword, int nrank) : word(nword), rank(nrank)
	{};
		
};
class EntityGroup : public list<Entity> //Группа записей с одинаковым кодом
{
public:
	void add(string word, int rank);
	void updateRank(iterator& record);
	iterator findEntity(int rank);
};
class Node : public EntityGroup //Дерево поиска
{
public:
	char symbol;
	list< Node > children;
	Node* findEntityGroup(string code);
	void descent(string code, string word, int rank);
	Node(char s) : symbol(s) {};
	Node() {};
};

Node dictionary;

string encode(string);
string decode(string);
char nextSymbol(char);
////////////////////////
int main(int argc, char** argv)
{
	int wordCount;
	cin >> wordCount;
	string word; int rank;
	for (int i = 1; i <= wordCount; i++) //Заполнение словаря словами
	{
		cin >> word >> rank;
		dictionary.descent(encode(word), word, rank);
	}
	string code;
	cin >> code;
	while (true) //Cчитываем последовательность кодов
	{
		cout << decode(code);
		while (cin.peek() == ' ')
		{
			cin.ignore(1);
			cout << ' ';
		}
		if (!(cin >> code))
			break;
	}
	cout << endl;
	return 0;
}

////////////////////////
string encode(string word) //Внимание! p на цифре 7
{
	int length = word.length();
	for (int i = 0; i < length; i++)
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
		case 'p': case 'q': case 'r': case 's':
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
	char symbol = 's';
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
	if (code != "")
	{
		Node* group = dictionary.findEntityGroup(code);
		EntityGroup::iterator bestWord = group->findEntity(rank);
		group->updateRank(bestWord); //повышаем частоту употребления слова
		
		if (symbol != 's')
			return bestWord->word + symbol;
		else
			return bestWord->word;
	}
	else
	{
		string res(1,symbol);
		return res;
	}
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
void EntityGroup::add(string word, int rank)
{
	iterator i = this->begin();
	while (i != this->end() && i->rank > rank)
		i++;
	while(i != this->end() && i->rank == rank && i->word < word)
		i++;
	this->insert(i,Entity(word, rank));
}
////////////////////////
void EntityGroup::updateRank(EntityGroup::iterator& record)
{
	record->rank++;
	EntityGroup::reverse_iterator prev(record);	
	while (prev != this->rend() && prev->rank <= record->rank)
	{
		//Обмен записей значениями
		int tmp;
		tmp = record->rank;
		record->rank = prev->rank;
		prev->rank = tmp;
		std::swap(record->word, prev->word);
		record--;
		prev++;
	}
	return;
}
////////////////////////
EntityGroup::iterator EntityGroup::findEntity(int rank)
{
	iterator result = this->begin();
	for (int j = 1; j < rank; j++) //Если нужно не "лучшее" слово
		result++;
	return result;
}
////////////////////////
void Node::descent(string code, string word, int rank)
{
	if (code == "")
	{
		this->add(word,rank);
		return;
	}
	for (list<Node>:: iterator it = children.begin(); it != children.end(); it++)
	{
		if (it->symbol == code[0])
		{
			it->descent(code.substr(1), word, rank);
			return;
		}
	}
	children.push_front(Node(code[0]));
	children.begin()->descent(code.substr(1), word, rank);
}
////////////////////////
Node* Node::findEntityGroup(string code)
{
	if (code == "")
		return this;
	for (list<Node>:: iterator it = children.begin(); it != children.end(); it++)
	{
		if (it->symbol == code[0])
		{
			return it->findEntityGroup(code.substr(1));
		}
	}
}
////////////////////////
