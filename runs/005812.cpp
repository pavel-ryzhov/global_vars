#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define WORD_LEN 21

struct lword
{
	char *word;
	int freq;
	struct lword *next;
	struct lword *prev;
};

struct dict
{
	struct dict *next[8];
	struct lword *lword;
};

struct dict *dict;

int main ()
{	
	/* создаём пустой словарь */
	dict = (struct dict*) malloc (sizeof (struct dict));
	memset (dict, 0, sizeof (struct dict));

	/* заполняем словарь */
	int dict_size;
	scanf ("%i", &dict_size);


	int dig[] = {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,5,6,6,6,7,7,7,7};
	struct dict *cur, *next;
	char *word;
	struct lword *nword, *cword;
	int freq;
	int i, j;
	int c;

	for (i = 0; i < dict_size; i++)
	{
		word = (char *) malloc (WORD_LEN);
		scanf ("%s %i ", word, &freq);
		cur = dict;
		j = 0;
		while (word[j] != '\0')
				/* ищем словарь */
		{
			c = dig [word [j] - 'a'];
			if (cur->next [c] == NULL)
				/* создаём новый словарь */
			{
				next = (struct dict *) malloc (sizeof (struct dict));
				memset (next, 0, sizeof (struct dict));
				nword = (struct lword *) malloc (sizeof (struct lword));
				nword -> freq = -1;
				nword -> prev = (struct lword *) malloc (sizeof (struct lword));
				nword -> prev -> freq = 100000;
				nword -> prev -> next = nword;
				next -> lword = nword -> prev;
				cur -> next [c] = next;
			}
			cur = cur -> next [c];
			j++;
		}	/* cur = искомый словарь */


					/* создаём слово */
		nword = (struct lword *) malloc (sizeof (struct lword));
		nword -> word = word;
		nword -> freq = freq;

					/* ищем место слова в списке */
		cword = cur -> lword;
		while (cword -> freq >= freq)
			cword = cword -> next;

					/* добавляем слово в список */
		nword -> prev = cword -> prev;
		nword -> next = cword;
		cword -> prev = nword;
		nword -> prev -> next = nword;
	}


	char *str = (char *) malloc (35000005 * sizeof (char));
	if (str == NULL) return 0;
	char *s = str;
	gets (str);
	int x = 0;
	c = *s++;

					/* обрабатываем текст */
	while (c != '\0')
	{
		if (c == ' ')
		{
			putchar (' ');
			c = *s++;
		}
		else if (c == '1')
		{
			char *dot = ".,?";
			while ((c = *s++) == '*')
				dot ++;
			putchar (*dot);
		}
		else if (c >= '2' && c <= '9')
		{
			cur = dict;
			while (c >= '2' && c <= '9')
			{
				cur = cur -> next [c - '2'];
				c = *s++;
			}

			cword = cur -> lword -> next;
			while  ( c == '*' )
			{
				cword = cword -> next;
				c = *s++;
			}
						/* cword = искомое слово */
	//printf ("Cicle\n");

			cword -> prev -> next = cword -> next;
			cword -> next -> prev = cword -> prev;
			cword -> freq ++;

	//printf ("Cicle 2\n");
						/* перемещаем найденное слово */
			nword = cword -> prev;
			while (nword -> freq <= cword -> freq)
				nword = nword -> prev;

			cword -> next = nword -> next;
			nword -> next -> prev = cword;
			nword -> next = cword;
			cword -> prev = nword;

			printf ("%s", cword -> word );



		}
		else c = *s++;
	}

	printf ("\n");
	free (str);
}

