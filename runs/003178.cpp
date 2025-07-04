#include <stdlib.h>
#include <stdio.h>


struct Data
{
	char Word[21];
	int Freq;
};
struct Node
{
	Node* Descendants[8];
	Data** Dataa;
	int WordsNumber;
};


class Tree
{
private:
	void AddData(Node* node, Data* data);
	bool ChildrenExist(Node* node, int index);
	void DestructTree(Node* node);
public:
	Node* Root;

	Tree(void);
	~Tree(void);
	Node* GetNode(Node* root, int path[]);
	void UpdatePriority(Data** data, int oldIndex);
	Node* NewData(Node* root, Data* data, int path[]);
};


void Tree::AddData(Node* node, Data* data)
{
	if (node->WordsNumber == 0)
	{
		node->Dataa = (Data**)malloc(sizeof(Data));
		node->Dataa[0] = data;
		node->WordsNumber++;
	}
	else
	{
		node->Dataa = (Data**)realloc(node->Dataa, (node->WordsNumber + 1) * sizeof(Data));
		int index = 0;
		while (index < node->WordsNumber && data->Freq <= node->Dataa[index]->Freq)
			index++;
		for (int j = node->WordsNumber; j > index; j--)
			node->Dataa[j] = node->Dataa[j-1];
		node->Dataa[index] = data;
		node->WordsNumber++;
	}
}
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
	free(root->Dataa);
	delete(root);
}
Tree::Tree(void)
{
	Root = new Node();
	Root->Dataa = (Data**)new Data();
}
Tree::~Tree(void)
{
	DestructTree(Root);
}
Node* Tree::GetNode(Node* root, int path[])
{
	if (path[0] == -1)
		return root;
	else
		return GetNode(root->Descendants[path[0]], path + 1);
}
void Tree::UpdatePriority(Data** data, int oldIndex)
{
	data[oldIndex]->Freq++;
	int newIndex = oldIndex;
	while (newIndex > 0 && data[newIndex - 1]->Freq <= data[oldIndex]->Freq)
		newIndex--;
	Data* temp = data[oldIndex];
	for (int i = oldIndex; i > newIndex; i--)
		data[i] = data[i - 1];
	data[newIndex] = temp;

}
Node* Tree::NewData(Node* root, Data* data, int path[])
{
	if (path[0] != -1)
	{
		if (!ChildrenExist(root, path[0]))
			root->Descendants[path[0]] = NewData(new Node(), data, path + 1);
		else
			NewData(root->Descendants[path[0]], data, path + 1);
	}
	else
	{
		AddData(root, data);
	}
	return root;
}


int main ()
{
	//input[30] -- введенная последовательность цифр
	//punctMarks[3] -- массив знаков препинания
	char input[100002], punctMarks[3] = {'.', ',', '?'};
	//path -- "путь" к вершине дерева
	//starsNumberPunct и starsNumberWord -- количество введенных звездочек
	//wordLength -- длина слова
	//wordsNumber -- количесто слов в словаре
	int *path, starsNumberPunct, starsNumberWord, wordLength, wordsNumber;
	Node* node = new Node();
	Tree* tree = new Tree();
	//считывание количества слов в словаре
	scanf("%d", &wordsNumber);
	//цикл заполнения дерева словами
	for (int i = 0; i < wordsNumber; i++)
	{
		//считывание очередного слова
		Data* data = new Data();
		scanf("%s", &data->Word);
		scanf("%d", &data->Freq);
		//определение длины слова
		wordLength = 0;
		while (data->Word[wordLength])
			wordLength++;
		path = (int*)calloc(wordLength + 1, sizeof(int));
		//цикл преобразования букв слова в номера соответсвующих им клавиш
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
		//добавление слова в дерево
		tree->NewData(tree->Root, data, path);
	}
	char ws;
	scanf("%c", &ws);
	while (ws==10 || ws==32)
	{
		if (ws==32)
			printf(" ");
		scanf("%c", &ws);
	}
	char fullInput[100001];
	fullInput[0]=ws;
	//scanf(" %[^\n]s", &fullInput[1]);
	fgets(&fullInput[1], 10000, stdin);
	bool isLast = false;
	int index = 0;
	bool flag2 = false;
	char symbol;
	while (!isLast)
	{
		//считывание введенного слова
		int index2 = 0;
		if (flag2)
		{
			index2 = 1;
			input[0]=symbol;
			index++;
		} 
		symbol = fullInput[index];
		flag2 = false;
		while (symbol != 10 && symbol != 32)
		{
			if (symbol==49)
				flag2 = true;
			if ('2' <= symbol && symbol <= '9' && flag2)
			{
				break;
			}
			input[index2]=symbol;
			index2++;
			index++;
			symbol = fullInput[index];
		}
		if (symbol == 10)
			isLast = true;
		input[index2]=0;
		//index++;
		//определение длины слова
		wordLength = 0;
		while (input[wordLength] <= '9' && input[wordLength] >= '2')
			wordLength++;
		//определение "пути" к вершине дерева, где хранится необходимое слово
		path = (int*)calloc(wordLength + 1, sizeof(int));
		for (int j = 0; j < wordLength; j++)
			path[j] = (int)input[j] - 50;
		path[wordLength] = -1;
		do
		{
			starsNumberPunct = 0;
			starsNumberWord = 0;
			if (input[wordLength] == 0)
			{
				//считываем узел с необходимыми словами
				node = tree->GetNode(tree->Root, path);
				//выводим на экран наиболее приоритетное слово
				printf("%s", node->Dataa[0]->Word);
				//изменяем приоритет слова
				tree->UpdatePriority(node->Dataa, 0);
			}
			else if (input[wordLength] == '1')
			{
				//считаем звездочки после 1
				starsNumberPunct = 0;
				while (input[wordLength + starsNumberPunct + 1] == '*')
					starsNumberPunct++;
				//если знак препинания служит в качестве подтверждения введенного слова
				if (input[wordLength - 1] <= '9' && input[wordLength - 1] >= '2')
				{
					//считываем узел с необходимыми словами
					node = tree->GetNode(tree->Root, path);
					//выводим на экран наиболее приоритетное слово и выбранный знак препинания
					printf("%s%c", node->Dataa[0], punctMarks[starsNumberPunct % 3]);
					//изменяем приоритет слова
					tree->UpdatePriority(node->Dataa, 0);
				}
				//в противном случае
				else
					//выводим на экран только выбранный знак препинания
					printf("%c", punctMarks[starsNumberPunct % 3]);
				wordLength++;
			}
			else if (input[wordLength] == '*')
			{	
				//считаем звездочки после слова
				starsNumberWord = 1;
				while (input[wordLength + starsNumberWord] == '*')
					starsNumberWord++;
				//считываем узел с необходимыми словами
				node = tree->GetNode(tree->Root, path);
				//выводим на экран выбранное слово
				printf("%s", node->Dataa[starsNumberWord % node->WordsNumber]->Word);
				//изменяем приоритет слова
				tree->UpdatePriority(node->Dataa, starsNumberWord % node->WordsNumber);
			}
			wordLength += starsNumberPunct + starsNumberWord;
		}
		while (input[wordLength]);
		while (symbol==32)
		{
			printf(" ");
			index++;
			symbol = fullInput[index];
		}
		if (symbol == 10)
			isLast = true;
	}	
	delete(tree);
	return 0;
}