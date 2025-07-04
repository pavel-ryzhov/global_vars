#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LEN 21

struct list_word
{
	int freq;
	struct list_word *next;
	char word[WORD_LEN];
};

struct dict
{
	struct dict *next[8];
	struct list_word *list_word;
};

struct dict *dict;
char wd[WORD_LEN] = "";

void insert_word (int freq)
{
	int i = 0;
	int dig[] = {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,5,6,6,6,7,7,7,7};
	struct dict *cur = dict;
	int c;
	int next;
	struct dict **nxt;
						/* получаем указатель на нужный словарь */
	while ((c = wd[i++]) != 0)
	{
		next = dig[c-'a'];
		nxt = &(cur->next[next]);
		if (*nxt == NULL)
		{
			*nxt = (struct dict*) malloc (sizeof(struct dict));
			memset (*nxt, 0, sizeof (struct dict));
		}
		cur = *nxt;

	}
	if (cur->list_word == NULL || cur->list_word->freq < freq)
						/* добавляем слово в начало списка */
	{
		struct list_word *newwd = (struct list_word*) malloc (sizeof(struct list_word));
		newwd -> next = cur->list_word;
		cur->list_word = newwd;
		memcpy (cur->list_word->word, wd, WORD_LEN);
		newwd -> freq = freq;
	}
	else
						/* ... в середину или конец списка */
	{
		struct list_word *cw = cur->list_word;
		while (cw->next != NULL && cw->next->freq >= freq)
			cw = cw->next;
		struct list_word *x;
		struct list_word *new_word = (struct list_word*) malloc (sizeof(struct list_word));
		memcpy (new_word->word, wd, WORD_LEN);
		new_word->freq = freq;
		x = cw->next;
		cw->next = new_word;
		new_word->next = x;
	}
}

	

int main ()
{
	dict = (struct dict*) malloc (sizeof (struct dict));
	memset (dict, 0, sizeof (struct dict));

	int dict_size;
	scanf ("%i", &dict_size);

	int i;
						/* формируем словарь */
	for (i = 0; i < dict_size; i++)
	{
		int freq;
		scanf ("%s %i ", wd, &freq);
		insert_word (freq);
	}

	int c = getchar();
	int freq;
	struct dict *cur = dict;
	struct list_word *cword, *prev;
						/* обрабатываем строку */
	do
	{
		if (c <= '9' && c >= '2')
		{
			cur = dict->next[c-'2'];
			while ((c = getchar ()) <= '9' && c >= '2')
				cur = cur->next[c-'2'];
			cword = cur->list_word;
			prev = NULL;
			while (c == '*')
			{
				prev = cword;
				cword = cword->next;
				c = getchar();
			}
			if (prev == NULL || cword->next == NULL && cword->freq+1 < prev->freq)
							/* слово не надо перемещать */
				cword->freq++;
			else
			{
							/* перемещаем слово */
				cword->freq++;
				freq = cword->freq;
				struct list_word *x;
				prev->next = cword->next;
				if (freq >= cur->list_word->freq)
							/* в начало */
				{
					cword->next = cur->list_word;
					cur->list_word = cword;
				} 
				else
				{
							/* в середину */
					x = cur->list_word;
					while (x -> next != NULL && x -> next -> freq > freq)
						x = x -> next;
					cword -> next = x -> next;
					x -> next = cword;
				}
			}

				
			printf ("%s", cword->word);
		}
		else if (c == '1')
		{
			char* dot = ".,?";
			while ((c = getchar()) == '*')
				dot++;
			putchar (*dot);
		}
		else if (c == ' ')
		{
			putchar (' ');
			c = getchar ();
		}
		else
			c = getchar ();


	}
	while (c != EOF);
	
	

	printf ("\n");
	return 0;
}
