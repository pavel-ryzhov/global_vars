#include <stdio.h>
#include <string.h>
#include <time.h>
#include <vector>

#define US unsigned short
#define UI unsigned int

#define WORD_LENGTH 20
#define KEYS_LENGTH 100000

using namespace std;

struct Node
{
	Node *node[8];
	vector<US> word;
};

struct Word
{
	char word[WORD_LENGTH + 1];
	US freq, order;
	
	/*bool operator >(const Word &right) const
	{
		return (freq > right.freq) || ((freq == right.freq) && (order > right.order));
	}
	
	bool operator <(const Word &right) const
	{
		return (freq < right.freq) || ((freq == right.freq) && (order < right.order));
	}
	
	bool operator <=(const Word &right) const
	{
		return (freq < right.freq) || ((freq == right.freq) && (order <= right.order));
	}
	
	bool operator ==(const Word &right) const
	{
		return (freq == right.freq) && (order == right.order);
	}*/
};

#define M(A, B) ((A.freq > B.freq) || ((A.freq == B.freq) && (A.order > B.order)))
#define L(A, B) ((A.freq < B.freq) || ((A.freq == B.freq) && (A.order < B.order)))
#define LE(A, B) ((A.freq < B.freq) || ((A.freq == B.freq) && (A.order <= B.order)))
#define E(A, B) ((A.freq == B.freq) && (A.order == B.order))

const char a[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};

Node * InsertNode(Node *root, char *value, US wId)
{
	if (!root)
		root = new Node;
	if (!*value)
	{
		root->word.push_back(wId);
		return root;
	}
	char c = a[*value - 'a'] - 2;
	root->node[c] = InsertNode(root->node[c], value + 1, wId);
	return root;
}

void FreeNode(Node *root)
{
	if (root)
	{
		for (char i = 0; i < 8; i++)
			FreeNode(root->node[i]);
		delete root;
	}
}

US *t, tCount = 0, order = 0, tCountPrev = 0;

Node * Search(Node *root, char *value, US depth = 0)
{
	if (*(value + depth) == 0)
		return root;
	return Search(root->node[*(value + depth) - '2'], value, depth + 1);
}

void SearchInit(Word *w, Node *root, char *k, int wStart, int wEnd)
{
	k[wEnd - tCount + 1] = 0;
	Node *node = Search(root, &k[wStart]);
	US wId, wCount = node->word.size(), i;
	if (wCount == 0)
		return;
	if (wCount == 1)
		wId = node->word[0];
	else
	{
		US max = node->word[0], min = node->word[0], ceil, maxI, minI, ceilI;
		for (i = 1; i < wCount; i++)
		{
			US curId = node->word[i];
			//if (w[curId] > w[max])
			if (M(w[curId], w[max]))
			{
				max = curId;
				maxI = i;
			}
			else
				//if (w[curId] <= w[min])
				if (LE(w[curId], w[min]))
				{
					min = curId;
					minI = i;
				}
		}
		wId = max;
		for (int j = 0; j < tCount - 1; j++)
		{
			ceil = max;
			ceilI = maxI;
			wId = max = min;
			maxI = minI;
			for (i = 0; i < wCount; i++)
			{
				US curId = node->word[i];
				fprintf(stderr, "[%s-%s]", w[curId].word, w[max].word);
				//if (((w[curId] < w[ceil]) || ((w[curId] == w[ceil]) && (i > ceilI))) && ((w[curId] > w[max]) || ((w[curId] == w[max]) && (i < maxI))))
				if ((L(w[curId], w[ceil]) || (E(w[curId], w[ceil]) && (i > ceilI))) && (M(w[curId], w[max]) || (E(w[curId], w[max]) && (i < maxI))))
				{
					max = curId;
					maxI = i;
					if ((j + 1) == (tCount - 1))
						wId = curId;
				}
			}
		}
	}
	printf("%s", w[wId].word);
	w[wId].freq++;
	w[wId].order = ++order;
}

int main(int argc, char **argv)
{
	US wCount;
	unsigned int i, kLen;
	Node *root;
	char k[KEYS_LENGTH + 1], p[] = {'.', ',', '?'};
	
	clock_t startTime = clock();
	
	scanf("%hu", &wCount);
	Word *w = new Word[wCount];
	fprintf(stderr, "Words: %hu\n", wCount);
	for (i = 0; i < wCount; i++)
	{
		scanf("%s %hu", w[i].word, &w[i].freq);
		root = InsertNode(root, w[i].word, i);
	}
	fprintf(stderr, "Words loaded\n");
	scanf("\n");
	fgets(k, KEYS_LENGTH + 1, stdin);
	kLen = strlen(k);
	if (k[kLen - 1] == '\n')
	{
		k[kLen - 1] = 0;
		kLen--;
	}

	fprintf(stderr, "Keys length: %u\n", (unsigned int)strlen(k));
	fprintf(stderr, "Loaded: %f\n", (float)(clock() - startTime) / CLOCKS_PER_SEC);
	
	char parseState = 0;
	unsigned int wStart;
	for (i = 0; i < kLen; i++)
	{
		switch (parseState)
		{
			case 0:
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
						tCount = 1;
				}
				break;
			case 1:
				switch (k[i])
				{
					case ' ':
						SearchInit(w, root, k, wStart, i);
						printf(" ");
						parseState = 0;
						break;
					case '1':
						SearchInit(w, root, k, wStart, i);
						parseState = 2;
						wStart = i;
						break;
					case '*':
						tCount++;
						break;
				}
				break;
			case 2:
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
						tCount = 1;
				}
				break;
		}
	}
	if (parseState == 2)
		printf("%c", p[i - wStart - 1]);
	if (parseState == 1)
		SearchInit(w, root, k, wStart, i);
	
	FreeNode(root);
	delete[] w;

	return 0;
}
