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
//-----------------------------------------
class EntityRankGroup : public list<Entity> //Группа записей с одинаковыми кодом и частотой встречаемости
//typedef не сделан, т.к. предполагалась более широкая функциональность
{
public:
	EntityRankGroup() : list<Entity>() {};
	EntityRankGroup(int i, Entity e) : list<Entity>(i, e) {};
};
//-----------------------------------------
class EntityGroup : public list<EntityRankGroup> //Группа записей с одинаковым кодом
{
public:
	void add(const string& word, const int& rank);
	void updateRank(const EntityRankGroup::iterator& record);
	EntityRankGroup::iterator findEntity(int rank);
};
//-----------------------------------------
class Node : public EntityGroup //Дерево поиска групп записей по коду
{
private:
	void realDescentIterative(string::const_iterator& codeCurr, const string::const_iterator& codeLast, const string& word, const int& rank);
	Node* realFindEntityGroupIterative(string::const_iterator& codeCurr, const string::const_iterator& codeLast);
	static list<Node>::iterator iter; //создан для ускорения работы поиска. Быстрее, т.к. не создается для каждого объекта
public:
	Node* children[8];
	Node* findEntityGroup(const string& code);
	void descent(const string& code, const string& word, const int& rank);
	Node();
};
list<Node>::iterator Node::iter;

Node dictionary;


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
	cerr << "analysis starts." << endl << flush;
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
	symbols = input.substr(wordLength, string::npos); //управляющие символы + возможно, что-то ещё
	code = input.substr(0, wordLength); //код слова

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
		EntityRankGroup::iterator bestWord = group->findEntity(rank);
		string word = bestWord->word;
		group->updateRank(bestWord); //повышаем частоту употребления слова
		if (symbol != 's')
			return word + symbol + addition;
		else
			return word + addition;
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
			return '.'; 
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
	//word не проверяется, т.к. во входном потоке слова расположены по алфавиту
	iterator i = this->begin();
	while (i != this->end() && i->begin()->rank > rank)
		i++;
	if (i != this->end() && i->begin()->rank == rank) // Если найден список, отвечающий данной частоте встречаемости
		i->push_back( Entity(word, rank) );
	else
		this->insert(i, EntityRankGroup(1, Entity(word, rank) ) );
}
////////////////////////
void EntityGroup::updateRank(const EntityRankGroup::iterator& record)
{
	int tmp;
	record->rank++;
	iterator i = this->begin();
	while (i->begin()->rank > record->rank)
		i++;
	if (i->begin()->rank == record->rank) // Если найден список, отвечающий данной частоте встречаемости
	{
		i->push_front(Entity(record->word, record->rank));
		i++;
		i->erase(record);
	}
	else
	{
		this->insert(i, EntityRankGroup(1,Entity(record->word,record->rank)));
		i++;
		i->erase(record);
	}
	return; //В идеале, нужно возвращать новое значение record. Но, в целях быстродействия, этого не сделано
}
////////////////////////
EntityRankGroup::iterator EntityGroup::findEntity(int rank)
{
	iterator rankGroup = this->begin();
	EntityRankGroup::iterator result = rankGroup->begin();
	while (rank > 1) //Поскольку слово точно найдётся, нет никаких дополнительных проверок
	{
		result++;
		rank--;
		if (result == rankGroup->end())
		{
			rankGroup++;
			result = rankGroup->begin();
		}
	}
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
void Node::realDescentIterative(string::const_iterator& codeCurr, const string::const_iterator& codeLast, const string& word, const int& rank)
{
	Node* currNode = this;
	char index;
	for (; codeCurr != codeLast; codeCurr++)
	{
		index = *codeCurr - '2';
		if (currNode->children[index] != NULL) //Найдено
			currNode = currNode->children[index];
		else
		{
			currNode->children[index] = new Node;
			currNode = currNode->children[index];
		}
	}
	currNode->add(word, rank);
}
////////////////////////
Node* Node::realFindEntityGroupIterative(string::const_iterator& codeCurr, const string::const_iterator& codeLast)
{
	Node* currNode = this;
	for (; codeCurr != codeLast; codeCurr++)
	{
		currNode = currNode->children[*codeCurr - '2'];
	}
	return currNode;
}
////////////////////////
Node::Node()
{
	for (int i = 0; i <= 7; i++)
		children[i] = NULL;
}
