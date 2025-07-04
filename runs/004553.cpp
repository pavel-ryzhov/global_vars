#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ALPH_LENGTH 27
#define WORD_LENGTH 20
#define KEYS_LENGTH 100000

struct Node
{
	unsigned short freq, order;
	Node *node[ALPH_LENGTH];
};

struct Word
{
	char word[WORD_LENGTH + 1];
	Node *node;
};

void FreeNode(Node *root)
{
	if (root)
	{
		for (int i = 0; i < ALPH_LENGTH; i++)
			FreeNode(root->node[i]);
		free(root);
	}
}

Node * InsertNode(Node *root, char *value, unsigned short freq)
{
	if (!root)
	{
		root = (Node *)malloc(sizeof(Node));
		root->order = 0;
		for (int i = 0; i < ALPH_LENGTH; i++)
			root->node[i] = (Node *)0;		
	}
	if (!*value)
	{
		root->freq = freq;
		return root;
	}
	char c = *value - 'a';
	root->node[c] = InsertNode(root->node[c], value + 1, freq);
	return root;
}

int KeyToNum(Node *root, char value, int o)
{
	unsigned short a[] = {0, 3, 6, 9, 12, 15, 19, 22, 26};
	if (o && o >= a[value + 1])
		return -1;
	int e = a[value + 1];
	for (int s = o ? o : a[value]; s < e; s++)
		if (root->node[s])
			return s;
	return -1;
}

Word *t = 0;
unsigned short tCount = 0, order = 0;

void Search(char *buffer, Node *root, unsigned int depth, char *value)
{
	if (*(value + depth) == 0)
	{
		buffer[depth] = 0;
		for (int j = tCount - 1; j >= 0; j--)
			if (t[j].node == 0)
			{
				memcpy(t[j].word, buffer, depth + 1);
				t[j].node = root;
				break;
			}
			else
				if ((root->freq > t[j].node->freq) || ((root->freq == t[j].node->freq) && (root->order > t[j].node->order)))
				{
					memmove(t, &t[1], j * sizeof(Word));
					memcpy(t[j].word, buffer, depth + 1);
					t[j].node = root;
					break;
				}
		return;
	}
	int i = KeyToNum(root, *(value + depth) - '2', 0);
	while (i >= 0)
	{
		buffer[depth] = i + 'a';
		Search(buffer, root->node[i], depth + 1, value);
		i = KeyToNum(root, *(value + depth) - '2', i + 1);
	}
}

void SearchInit(Node *root, char *k, int wStart, int wEnd)
{
	unsigned short starSpan = strcspn(&k[wStart], "*");
	char buffer[WORD_LENGTH + 1];
	tCount = (starSpan < wEnd - wStart) ? wEnd - wStart - starSpan + 1 : 1;
	k[wEnd - tCount + 1] = 0;
	t = (Word *)calloc(tCount, sizeof(Word));
	Search(buffer, root, 0, &k[wStart]);
	printf("%s", t[0].word);
	t[0].node->freq++;
	t[0].node->order = ++order;
	free(t);
}

int main(int argc, char **argv)
{
	unsigned short i, wCount, wFreq;
	char word[WORD_LENGTH + 1], k[KEYS_LENGTH + 1], p[] = {'.', ',', '?'};
	Node *root = 0;
	
	scanf("%hu", &wCount);
	for (i = 0; i < wCount; i++)
	{
		scanf("%s %hu", word, &wFreq);
		root = InsertNode(root, word, wFreq);
	}
	scanf("\n");
	fgets(k, KEYS_LENGTH, stdin);
	k[strlen(k) - 1] = 0;
	fprintf(stderr, "%s\n", k);
	
	char parseState = 0;
	unsigned int wStart, kLen = strlen(k);
	for (i = 0; i < kLen; i++)
	{
		switch (parseState)
		{
			case 0:
				// initial state
				switch (k[i])
				{
					case ' ':
						printf(" ");
						break;
					case '1':
						parseState = 2;
						wStart = i;
						break;
					default:
						parseState = 1;
						wStart = i;
				}
				break;
			case 1:
				// parsing word
				switch (k[i])
				{
					case ' ':
						SearchInit(root, k, wStart, i);
						printf(" ");
						parseState = 0;
						break;
					case '1':
						SearchInit(root, k, wStart, i);
						parseState = 2;
						wStart = i;
						break;
				}
				break;
			case 2:
				// parsing punctuation
				switch (k[i])
				{
					case ' ':
						printf("%c ", p[i - wStart - 1]);
						parseState = 0;
						break;
					case '1':
						printf("%c", p[i - wStart - 1]);
						wStart = i;
						break;
					case '*':
						break;
					default:
						printf("%c", p[i - wStart - 1]);
						parseState = 1;
						wStart = i;
				}
				break;
		}
	}
	if (parseState == 2)
		printf("%c", p[i - wStart - 1]);
	if (parseState == 1)
		SearchInit(root, k, wStart, i);
	
	FreeNode(root);
	
	return 0;
}
