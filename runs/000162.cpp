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
	void add(const string& word, const int& rank);
	void updateRank(iterator& record);
	iterator findEntity(const int& rank);
};
class Node : public EntityGroup //Дерево поиска
{
private:
	void realDescent(string::const_iterator& codeCurr, const string::const_iterator& codeLast, const string& word, const int& rank);
	void realDescentIterative(string::const_iterator& codeCurr, const string::const_iterator& codeLast, const string& word, const int& rank); //non-recursive
	Node* realFindEntityGroup(string::const_iterator& codeCurr, const string::const_iterator& codeLast);
	Node* realFindEntityGroupIterative(string::const_iterator& codeCurr, const string::const_iterator& codeLast);
	static list<Node>::iterator iter; //создан для ускорения работы поиска. Быстрее, т.к. не создается для каждого объекта
public:
	char symbol;
	list< Node > children;
	Node* findEntityGroup(const string& code); //const не стоит из-за error'ов
	void descent(const string& code, const string& word, const int& rank);
	Node(char s) : symbol(s) {};
	Node() {};
};

Node dictionary;
list<Node>::iterator Node::iter;

string encode(string);
string decode(string);
char nextSymbol(const char&);
////////////////////////
int main(int argc, char** argv)
{
	int wordCount;
	cin >> wordCount;
	cerr << "word count: " << wordCount << endl;
	string word; int rank;
	for (int i = 1; i <= wordCount; i++) //Заполнение словаря словами
	{
		cin >> word >> rank;
		dictionary.descent(encode(word), word, rank);
	}
	cerr << "analisys starts." << endl;;
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
	for (string::iterator i (word.begin()); i < word.end(); i++)
	{
		switch (*i)
		{
		case 'a': case 'b': case 'c':
			*i = '2';
			break;
		case 'd': case 'e': case 'f':
			*i = '3';
			break;
		case 'g': case 'h': case 'i':
			*i = '4';
			break;
		case 'j': case 'k': case 'l':
			*i = '5';
			break;
		case 'm': case 'n': case 'o':
			*i = '6';
			break;
		case 'p': case 'q': case 'r': case 's':
			*i = '7';
			break;
		case 't': case 'u': case 'v':
			*i = '8';
			break;
		case 'w': case 'x': case 'y': case 'z':
			*i = '9';
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
	string code, symbols; //слово и символы
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
	int onesCount = 0;
	int rank = 1;
	char symbol = 's';
	string addition;
	for (string::iterator i = symbols.begin(); i != symbols.end(); i++)
	{
		if ((*i != '1') && brank)
			rank++;
		else
		{
			if (*i == '1')
				onesCount++;
			if (onesCount > 1 || (*i != '1' && *i != '*'))
			{
				addition = decode(string(i,symbols.end()));
				break;
			}
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
			return bestWord->word + symbol + addition;
		else
			return bestWord->word + addition;
	}
	else
	{
		string res(1,symbol);
		return res + addition;
	}
}
////////////////////////
char nextSymbol(const char& symbol)
{
	switch(symbol)
	{
		case 's':
			return '.'; //Опция введена для быстродействия
		case '.':
			return ',';
		case ',':
			return '?';
		default:
			return '.';
	}
}
////////////////////////
void EntityGroup::add(const string& word, const int& rank)
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
	int tmp;
	record->rank++;
	EntityGroup::reverse_iterator prev(record);	
	while (prev != this->rend() && prev->rank <= record->rank)
	{
		//Обмен записей значениями
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
EntityGroup::iterator EntityGroup::findEntity(const int& rank)
{
	iterator result = this->begin();
	for (int j = 1; j < rank; j++) //Если нужно не "лучшее" слово
		result++;
	return result;
}
////////////////////////
void Node::descent(const string& code, const string& word, const int& rank)
{
	static string::const_iterator coit;
	coit = code.begin();
	static string::const_iterator coend;
	coend = code.end();
	realDescentIterative(coit, coend, word, rank);
}
////////////////////////
Node* Node::findEntityGroup(const string& code)
{
	static string::const_iterator coit;
	coit = code.begin();
	static string::const_iterator coend;
	coend = code.end();
	return realFindEntityGroupIterative(coit, coend);
}
////////////////////////
void Node::realDescent(string::const_iterator& codeCurr, const string::const_iterator& codeLast, const string& word, const int& rank)
{
	if (codeCurr == codeLast) //Если разбор кода прошёл последнюю цифру
	{
		this->add(word, rank);
		return;
	}
	for (iter = children.begin(); iter != children.end(); iter++) //Ищем потомка, отвечающего за след. цифру
	{
		if (iter->symbol == *codeCurr)
		{
			codeCurr++;
			iter->realDescent(codeCurr, codeLast, word, rank); //Передаём управление потомку
			return;
		}
	}
	children.push_front(Node(*codeCurr));
	codeCurr++;
	children.begin()->realDescent(codeCurr, codeLast, word, rank);
}
////////////////////////
void Node::realDescentIterative(string::const_iterator& codeCurr, const string::const_iterator& codeLast, const string& word, const int& rank)
{
	Node* currNode = this;
	for (; codeCurr != codeLast; codeCurr++)
	{
		for (iter = currNode->children.begin(); iter != currNode->children.end(); iter++)
		{
			if (iter->symbol == *codeCurr)
				break;
		}
		if (iter != currNode->children.end()) //Найдено
			currNode = &(*iter);
		else
		{
			currNode->children.push_front(Node(*codeCurr));
			currNode = &(*(currNode->children.begin()));
		}
	}
	currNode->add(word, rank);
}
////////////////////////
Node* Node::realFindEntityGroup(string::const_iterator& codeCurr, const string::const_iterator& codeLast)
{
	if (codeCurr == codeLast) //Если разбор кода прошёл последнюю цифру
		return this;
	for (iter = children.begin(); /*it != children.end()*/; iter++) //Ищем потомка, отвечающего за след. цифру
	//Не проверяем условие, т.к. слово, по условию задачи, всегда найдётся
	{
		if (iter->symbol == *codeCurr)
		{
			codeCurr++;
			return iter->realFindEntityGroup(codeCurr, codeLast); //Передаём управление потомку
		}
	}
}
////////////////////////
Node* Node::realFindEntityGroupIterative(string::const_iterator& codeCurr, const string::const_iterator& codeLast)
{
	Node* currNode = this;
	for (; codeCurr != codeLast; codeCurr++)
	{
		for (iter = currNode->children.begin(); /*iter != currNode->children.end()*/; iter++)
		{
			if (iter->symbol == *codeCurr)
				break;
		}
		currNode = &(*iter);
	}
	return currNode;
}
////////////////////////
