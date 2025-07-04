#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


struct Data
{
	char Word[21];
	int Freq;
};
struct ListElem
{
	ListElem* Next;
	ListElem* Prev;
	Data* Words;
};


class List
{
private:
	bool IsEmpty();
	void DestructList(ListElem* first);
public:
	ListElem* First;
	ListElem* Last;
	List(void);
	~List(void);
	void AddData(ListElem* elem, Data* data);
};


bool List::IsEmpty()
{
	return (First->Words == NULL);
}
void List::DestructList(ListElem* first)
{
	if (first->Next)
		DestructList(first->Next);
	delete first->Words;
	delete first;
}
List::List(void)
{
	First = new ListElem();
	Last = First;
}
List::~List(void)
{
	DestructList(First);
}
void List::AddData(ListElem* elem, Data* data)
{
	if (IsEmpty())
		First->Words = data;
	else if (Last->Words->Freq >= data->Freq)
	{
		ListElem* newElem = new ListElem();
		newElem->Words = data;
		newElem->Prev = Last;
		Last->Next = newElem;
		Last = newElem;
	}
	else if (elem->Words->Freq < data->Freq)
	{
		ListElem* newElem = new ListElem();
		newElem->Words = data;
		if (elem == First)
		{
			newElem->Next = elem;
			elem->Prev = newElem;
			First = newElem;
		}
		else
		{
			newElem->Next = elem;
			newElem->Prev = elem->Prev;
			elem->Prev->Next = newElem;
			elem->Prev = newElem;
		}
	}
	else
		AddData(elem->Next, data);
}


struct Node
{
	Node* Descendants[8];
	List* WordsList;
	int WordsNumber;
};


class Tree
{
private:
	bool ChildrenExist(Node* node, int index);
	void DestructTree(Node* node);
public:
	Node* Root;
	Node* LastNode;
	int* LastPath;
	Tree(void);
	~Tree(void);
	char* GetWordAndUpdatePriority(Node* root, int path[], int index);
	Node* NewData(Node* root, Data* data, int path[]);
};


bool Tree::ChildrenExist(Node* node, int index)
{
	if (!node->Descendants[index])
		return false;
	return true;
}
void Tree::DestructTree(Node* root)
{
	for (int i = 0; i < 8; i++)
		if (ChildrenExist(root, i))
			DestructTree(root->Descendants[i]);
		else
			continue;
	delete(root->WordsList);
	delete(root);
}
Tree::Tree(void)
{
	Root = new Node();
	Root->WordsList = new List();
	LastPath = (int*)calloc(1, sizeof(int));
	LastPath[0] = -1;
}
Tree::~Tree(void)
{
	DestructTree(Root);
}
char* Tree::GetWordAndUpdatePriority(Node* root, int path[], int index)
{
	if (path[0] == -1)
	{
		if (index == 0)
		{
			root->WordsList->First->Words->Freq++;
			return root->WordsList->First->Words->Word;
		}
		ListElem* listElem1 = new ListElem();
		if (index % root->WordsNumber <= root->WordsNumber / 2)
		{
			listElem1 = root->WordsList->First;
			for (int i = 0; i < index % root->WordsNumber; i++)
				listElem1 = listElem1->Next;
		}
		else
		{
			listElem1 = root->WordsList->Last;
			for (int i = root->WordsNumber - 1; i > index % root->WordsNumber; i--)
				listElem1 = listElem1->Prev;
		}
		listElem1->Words->Freq++;
		ListElem* listElem2 = listElem1;
		while (listElem2->Prev && listElem2->Prev->Words->Freq <= listElem1->Words->Freq)
			listElem2 = listElem2->Prev;
		if (listElem1 == listElem2)
			return listElem1->Words->Word;
		if (listElem1->Next)
		{
			listElem1->Next->Prev = listElem1->Prev;
			listElem1->Prev->Next = listElem1->Next;
		}
		else
		{
			listElem1->Prev->Next = NULL;			
			root->WordsList->Last = listElem1->Prev;
		}
		if (listElem2->Prev)
		{
			listElem1->Next = listElem2;
			listElem1->Prev = listElem2->Prev;
			listElem2->Prev->Next = listElem1;
			listElem2->Prev = listElem1;
		}
		else
		{
			listElem1->Next = listElem2;
			listElem1->Prev = NULL;
			listElem2->Prev = listElem1;
			root->WordsList->First = listElem1;
		}
		return listElem1->Words->Word;
	}
	else
		return GetWordAndUpdatePriority(root->Descendants[path[0]], path + 1, index);
}
Node* Tree::NewData(Node* root, Data* data, int path[])
{
	if (path[0] != -1)
	{
		if (!ChildrenExist(root, path[0]))
		{
			Node* node = new Node();
			node->WordsList = new List();
			root->Descendants[path[0]] = NewData(node, data, path + 1);
		}
		else
			NewData(root->Descendants[path[0]], data, path + 1);
	}
	else
	{
		root->WordsNumber++;
		LastNode = root;
		root->WordsList->AddData(root->WordsList->First, data);
	}
	return root;
}


int main ()
{
	char punctMarks[3] = {'.', ',', '?'};
	int *path, wordLength, wordsNumber;
	Node* node = new Node();
	Tree* tree = new Tree();
	scanf("%d", &wordsNumber);
	for (int i = 0; i < wordsNumber; i++)
	{
		Data* data = new Data();
		scanf("%s", &data->Word);
		scanf("%d", &data->Freq);
		wordLength = 0;
		while (data->Word[wordLength])
			wordLength++;
		path = (int*)calloc(wordLength + 1, sizeof(int));
		for (int j = 0; j < wordLength; j++)
			switch (data->Word[j])
			{
				case 'a': path[j] = 0; break; case 'b': path[j] = 0; break;
				case 'c': path[j] = 0; break; case 'd': path[j] = 1; break;
				case 'e': path[j] = 1; break; case 'f': path[j] = 1; break;
				case 'g': path[j] = 2; break; case 'h': path[j] = 2; break;
				case 'i': path[j] = 2; break; case 'j': path[j] = 3; break;
				case 'k': path[j] = 3; break; case 'l': path[j] = 3; break;
				case 'm': path[j] = 4; break; case 'n': path[j] = 4; break;
				case 'o': path[j] = 4; break; case 'p': path[j] = 5; break;
				case 'q': path[j] = 5; break; case 'r': path[j] = 5; break;
				case 's': path[j] = 5; break; case 't': path[j] = 6; break;
				case 'u': path[j] = 6; break; case 'v': path[j] = 6; break;
				case 'w': path[j] = 7; break; case 'x': path[j] = 7; break;
				case 'y': path[j] = 7; break; case 'z': path[j] = 7; break;
			}
		path[wordLength] = -1;
		for (int j = 0; ; j++)
		{
			if (path[j] != tree->LastPath[j])
			{
				tree->LastPath = path;
				tree->NewData(tree->Root, data, path);
				break;
			}
			if (path[j] == -1)
			{
				tree->LastNode->WordsList->AddData(tree->LastNode->WordsList->First, data);
				tree->LastNode->WordsNumber++;
				break;
			}
		}
	}
	char firstSymbols;
	scanf("%c", &firstSymbols);
	scanf("%c", &firstSymbols);
	while (firstSymbols == ' ')
	{
		printf(" ");
		scanf("%c", &firstSymbols);
	}
	bool isLast = false, firstIsOne = false;
	char symbol;
	char input[100001], fullInput[100001];
	int fullIndex = 0, index, starsNumberPunct, starsNumberWord;
	fullInput[0] = firstSymbols;
	fgets(&fullInput[1], 100001, stdin);
	while (!isLast)
	{
		index = 0;
		if (firstIsOne)
		{
			index = 1;
			input[0] = symbol;
			fullIndex++;
		} 
		symbol = fullInput[fullIndex];
		firstIsOne = false;
		while (symbol != 10 && symbol != ' ')
		{
			if (symbol == '1')
				firstIsOne = true;
			if ('2' <= symbol && symbol <= '9' && firstIsOne)
				break;
			input[index++] = symbol;
			symbol = fullInput[++fullIndex];
		}
		if (symbol == 10)
			isLast = true;
		input[index] = 0;
		wordLength = 0;
		while ('2' <= input[wordLength] && input[wordLength] <= '9')
			wordLength++;
		if (wordLength)
		{
			path = (int*)calloc(wordLength + 1, sizeof(int));
			for (int j = 0; j < wordLength; j++)
				path[j] = (int)input[j] - 50;
			path[wordLength] = -1;
		}
		do
		{
			starsNumberPunct = 0;
			starsNumberWord = 0;
			if (input[wordLength] == 0)
				printf("%s", tree->GetWordAndUpdatePriority(tree->Root, path, 0));
			else if (input[wordLength] == '1')
			{
				starsNumberPunct = 0;
				while (input[wordLength + starsNumberPunct + 1] == '*')
					starsNumberPunct++;
				if ('2' <= input[wordLength - 1] && input[wordLength - 1] <= '9')
					printf("%s%c", tree->GetWordAndUpdatePriority(tree->Root, path, 0), punctMarks[starsNumberPunct % 3]);
				else
					printf("%c", punctMarks[starsNumberPunct % 3]);
				wordLength++;
			}
			else if (input[wordLength] == '*')
			{	
				starsNumberWord = 1;
				while (input[wordLength + starsNumberWord] == '*')
					starsNumberWord++;
				printf("%s", tree->GetWordAndUpdatePriority(tree->Root, path, starsNumberWord));
			}
			wordLength += starsNumberPunct + starsNumberWord;
		} while (input[wordLength]);
		while (symbol == 32)
		{
			printf(" ");
			symbol = fullInput[++fullIndex];
		}
		if (symbol == 10)
			isLast = true;
	}	
	//delete(tree);
	return 0;
}