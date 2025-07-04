#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>

#define MAXDICT 8          /* Символы от 2-9 */

using namespace std;

// Структура для сохранения о данных о слове в словаре
struct Word
{
	string word;
	int freq;
	int modify;
};

// Вершина в дереве
struct Node 
{
	vector<Word*> words; // слова в текущей вершине
	Node *childs[MAXDICT]; // массив содержащий потомков
	bool sorted;
};

//Функция для сравнения двух вершин в дереве
bool compare(Word *i, Word* j)
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
		memset(root->childs, NULL, MAXDICT * sizeof (root->childs[0]));
		root->sorted = false;

		memset(dict, 0, 256 * sizeof (int));
		dict['a'] = 0;
		dict['b'] = 0;
		dict['c'] = 0;
		dict['d'] = 1;
		dict['e'] = 1;
		dict['f'] = 1;
		dict['g'] = 2;
		dict['h'] = 2;
		dict['i'] = 2;
		dict['j'] = 3;
		dict['k'] = 3;
		dict['l'] = 3;
		dict['m'] = 4;
		dict['n'] = 4;
		dict['o'] = 4;
		dict['p'] = 5;
		dict['q'] = 5;
		dict['r'] = 5;
		dict['s'] = 5;
		dict['t'] = 6;
		dict['u'] = 6;
		dict['v'] = 6;
		dict['w'] = 7;
		dict['x'] = 7;
		dict['y'] = 7;
		dict['z'] = 7;

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
		Word * newWord;
		for ( size_t i = 0; i < word.size(); i++)
		{
			if (node->childs[dict[word[i]]] == NULL)
			{
				Node* child = new Node();
				memset(child->childs, NULL, MAXDICT * sizeof (child->childs[0]));
				child->sorted = false;

				node->childs[dict[word[i]]] = child;
				node = child;
			}
			else
			{
				node = node->childs[dict[word[i]]];
			}
		}

		newWord = new Word();
		newWord->freq = freq;
		newWord->modify = 0;
		newWord->word = word;

		node->words.push_back(newWord);
	}
	
	/**
	*	Модификация значения частоты слова в словаре
	*/
	void ModifyWord(Node *node, int pos)
	{
		Word *tmp = node->words[pos]; // переменная для временного хранения указателя на слово
		int j = pos;
		node->words[pos]->freq += 1;
		node->words[pos]->modify = modifications;
		modifications++;
		
			
		while (j>0 && compare(tmp, node->words[j-1]))
		{
			node->words[j] = node->words[j-1];
			j--;
		}
		if (j != pos)
			node->words[j] = tmp;
	}

	/**
	*	Поиск слова в дереве
	*/
	string Search(string word)
	{
		int pos = 0; // количество звездочек после слова 
		string result;
		Node * node = root;

		for (size_t i = 0; i < word.size(); i++)
		{
			if (word[i] != '*')
			{
				node = node->childs[word[i] - '2'];
			}
			else
			{
					pos++;
			}
		}
		
		if (!node->sorted)
		{
			sort(node->words.begin(), node->words.end(), compare);
			node->sorted = true;
		}

		result = node->words[pos]->word;
		ModifyWord(node, pos);
		return result;
	}

	/**
	*	Возвращает знак препинания в зависимости от кол-ва звездочек
	*/
	char GetStop(int &posstop)
	{
		char stop;
		switch(posstop)
		{
			case 1:
				stop = '.';
				break;
			case 2:
				stop = ',';
				break;
			case 3:
				stop = '?';
				break;
		}
		posstop = 0;
		return stop;
	}


private:
	// массив букв
	int dict[256];
	// корень дерева
	Node * root; 
	// количество модификаций
	int modifications;
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