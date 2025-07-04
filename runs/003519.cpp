#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>

#define MAXDICT 26          /* Символы от a-z */

using namespace std;

// Вершина в дереве
struct Node 
{
	string word; // слово в результате прохода от корня до текущей вершины
	int modify; // счетчик модификаций вершины, если в ней заканчивается слово
	int freq;  // частота встречаемости слова, если в этой вершине заканчивается
	Node *childs[MAXDICT]; // массив содержащий потомков
};

//Функция для сравнения двух вершин в дереве
bool compare(Node *i, Node* j)
{
	if (i->freq > j->freq)
	{
		return true;
	}
	else
	{
		if (i->freq < j->freq)
		{
			return false;
		}
		else
		{
			if (i->modify > j->modify)
			{
				return true;
			}
			else
			{
				if (i->modify < j->modify)
					return false;
				else
				{
					if (i->word < j->word)
						return true;
					else
						return false;
				}
			}
		}
	}
}

class Trie
{
public:
	/**
	*   Конструктор
	*	Инициализируем корень дерева
	*/
	Trie()
	{
		root = new Node();
		root->freq = 0;
		root->modify = 0;
		root->word = "";
		memset(root->childs, NULL, MAXDICT * sizeof (root->childs[0]));

		dict = "abcdefghijklmnopqrstuvwxyz";
		numbers[0] = ".,?";
		numbers[1] = "abc";
		numbers[2] = "def";
		numbers[3] = "ghi";
		numbers[4] = "jkl";
		numbers[5] = "mno";
		numbers[6] = "pqrs";
		numbers[7] = "tuv";
		numbers[8] = "wxyz";

		modifications = 1;
	}
	
	~Trie()
	{
		delete root;
	}

	
	/**
	*	Вставка нового слова в дерево
	*/
	void InsertWord(string word, int freq)
	{
		Node *node = root;
		for ( size_t i = 0; i < word.size(); i++)
		{
			if (node->childs[getIndexForChar(word[i])] == NULL)
			{
				Node* child = new Node();
				child->word = node->word + word[i];
				child->freq = 0;
				child->modify = 0;
				memset(child->childs, NULL, MAXDICT * sizeof (child->childs[0]));

				node->childs[getIndexForChar(word[i])] = child;
				node = child;
			}
			else
			{
				node = node->childs[getIndexForChar(word[i])];
			}
		}
		node->freq = freq;
		node->modify = 0;
	}
	
	/**
	*	Модификация значения частоты слова в словаре
	*/
	void ModifyWord(string word)
	{
		Node *node = root;
		for ( size_t i = 0; i < word.size(); i++)
		{
			node = node->childs[getIndexForChar(word[i])];
		}
		node->freq += 1;
		node->modify = modifications;
		modifications++;
	}

	/**
	*	Поиск слова в дереве
	*/
	string Search(string word)
	{
		int pos = 0; // количество звездочек после слова 
		vector<Node*> combinations;
		combinations.push_back(root);

		for (size_t i = 0; i < word.size(); i++)
		{
			if (word[i] != '*')
			{
				getVertexesForChar(word[i], combinations);
			}
			else
			{
					pos++;
			}
		}

		sort(combinations.begin(), combinations.end(), compare);
		ModifyWord(combinations[pos]->word);
		return combinations[pos]->word;
	}

	/**
	*	Возвращает знак препинания в зависимости от кол-ва звездочек
	*/
	char GetStop(int &posstop)
	{
		char stop = numbers[0][posstop-1];
		posstop = 0;
		return stop;
	}

private:
	//массив соответсвия цифр буквам
	string numbers[9];
	// массив букв
	string dict;
	// корень дерева
	Node * root; 
	// количество модификаций
	int modifications;

	// Вычисления индекса буквы в массиве
	int getIndexForChar ( char c ) 
	{
		for ( size_t i = 0 ; i < dict.size() ; i++ ) 
		{
			if ( dict[i] == c ) 
			{
				return i;
			}
		}
		return (-1);
	}

	
	// Вычисления потенциальных вершин лежащих в слове
	void getVertexesForChar ( char c, vector<Node*> &parents ) 
	{
		vector<Node*> newParents;
		Node *node;
		string letters = numbers[c - '0' - 1];

		for (size_t j = 0; j < parents.size(); j++)
		{
			node = parents[j];
			for ( size_t i = 0; i < letters.size(); i++)
			{
				if (node->childs[getIndexForChar(letters[i])] != NULL)
				{
					newParents.push_back(node->childs[getIndexForChar(letters[i])]);
				}
			}
		}
		parents.clear();
		parents.swap(newParents);
	}

	

};
int main()
{
	int n = 0;
	string word, text;
	int freq;
	int posstop = 0; // количество звездочек после 1

	Trie tree;

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> word;
		cin >> freq;
		tree.InsertWord(word, freq);
	}
	getline(cin, text); // убераем лишний /n

	getline(cin, text);
	word.clear();
	for (size_t i = 0; i < text.size(); i++)
	{
		if (text[i] != ' ' && text[i] != '1')
		{
			if (posstop > 0)
			{
				if (text[i] == '*')
					posstop ++;
				else
				{
					cout << tree.GetStop(posstop);
					word += text[i];
				}
			}
			else
				word += text[i];
		}
		else
		{
			if (!word.empty())
				cout << tree.Search(word);
			
			if (posstop > 0)
				cout << tree.GetStop(posstop);

			if (text[i] == ' ')
				cout << ' ';
		
			if ( text[i] == '1')
				posstop = 1;
			
			word.clear();
		}
	}
	if (!word.empty())
		cout << tree.Search(word);
	if (posstop > 0)
		cout << tree.GetStop(posstop);
}