#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
	 1   2   3
	.,? abc def

	 4   5   6
	ghi jkl mnop

	 7   8   9
	qrs tuv wxyz
*/

#define WLEN 20
#define PLEN 100000


// слово
struct TWORD
{
	int           f;         // частота
	char          w[WLEN+1]; // слово
	struct TWORD *next;
} TWORD;

// буква в словаре
struct TDIC
{
	struct TDIC  *next[9];
	struct TWORD *word;
} TDIC;

// большой массив с предложением исходным
char phrase[PLEN+1];
// словарь
struct TDIC dic = {{0,0,0, 0,0,0, 0,0,0}, 0};

// перевод из букв в цифры
int letterToDigit(char c)
{
	if (c == '.' || c == ',' || c == '?') return c = 1;
	if (c == 'a' || c == 'b' || c == 'c') return c = 2;
	if (c == 'd' || c == 'e' || c == 'f') return c = 3;
	if (c == 'g' || c == 'h' || c == 'i') return c = 4;
	if (c == 'j' || c == 'k' || c == 'l') return c = 5;
	if (c == 'm' || c == 'n' || c == 'o' || c == 'p') return c = 6;
	if (c == 'q' || c == 'r' || c == 's') return c = 7;
	if (c == 't' || c == 'u' || c == 'v') return c = 8;
	if (c == 'w' || c == 'x' || c == 'y' || c == 'z') return c = 9;
	return 0;
}

// генерация слова
int catWord(struct TDIC *d, int star, char *to)
{
	int           s  = star;
	struct TWORD *ww = d->word; // current
	struct TWORD *wp = d->word; // previous
	struct TWORD *w_ = d->word; // prev_freq
	struct TWORD*wp_ = d->word; // previous prev_freq
	// ищем слово
	if (s) while (s--) { wp = ww; ww = ww->next ? ww->next : d->word; }
	// копируем
	strcat(to, ww->w);
	if (!ww->f) return 0;
	// inc freq
	ww->f++;
	if (ww == d->word) return 1;
	// find next freq
	while (w_->next->f > ww->f) { wp_ = w_; w_ = w_->next; }
	// to top
	if (w_ == d->word)
	{
		wp->next = ww->next; // del current
		ww->next = w_;
		if (w_ == d->word)
			d->word = ww;
		else
			wp_->next = ww;
		return 2;
	}
	if (w_->next->next == ww) return 3;
	// swap
	w_->next = ww->next; // del current word
	ww->next = w_->next; // update next
	w_->next = ww;       // update previous

	return 0;
}

// перевод слов
int translateWord(char *from, char *to)
{
	int           i = 0;
	int           c = 0;
	int        star = 0;
	struct TDIC  *d = &dic;
	to[0] = 0;
	// пробегаем до конца слова
	while (from[i])
	{
		c = from[i];
		// vstretitli 1 - sbrasivaem slovo
		if (c == '1')
		{
			catWord(d, star, to);
			star = 0; d = dic.next[0];
		}
		// bila zvezda, prishla ne zvezda
		else if (star && c != '*') // следующее слово
		{
			catWord(d, star, to);
			star = 0; d = &dic;
		}
		// zvezda - perebiraem
		else if (c == '*') star++; // конец слова
		else d = d->next[c - '1'];
		i++;
	}
	// добавляем к слову
	catWord(d, star, to);
	return 0;
}

// добавление слова с словарь
int dicAdd(char *word, int f)
{
	int    i = 0;
	int    c = 0;
	struct TDIC  *d = &dic;
	struct TWORD *w, *ww;

	// ищем место куда добавить это слово в словарь
	while (word[i])
	{
		c = letterToDigit(word[i]);
		if (!c)
		{
			printf("Unknow char: %c!\n", c);
			continue;
		}
		c--;
		if (d->next[c] == 0)
		{
			d->next[c] = (struct TDIC*)malloc(sizeof(TDIC));
			memset(d->next[c], 0, sizeof(TDIC));
		}
		d = (struct TDIC*)d->next[c];
		i++;
	}
	// перебираем слова и вставляем в соответствии с частотой
	w = (struct TWORD*)malloc(sizeof(TWORD));
	strcpy(w->w, word);
	w->f = f;
	w->next = 0;
	if (d->word == 0) d->word = w;
	else
	{
		ww = d->word;
		// меняем первое слово
		if (w->f > d->word->f)
		{
			w->next = d->word;
			d->word = w;
		} else
		// записываем в серединку массива
		while (1)
		{
			// достигли конца
			if (ww->next == 0)
			{
				ww->next = w;
				break;
			}
			// нашли куда вклиниться - если частота текущего слова больше
			// или равна частоте в словаре
			if (w->f > ww->next->f)
			{
				w->next  = ww->next;
				ww->next = w;
				break;
			}
			ww = ww->next;
		}
	}
//	printf("> %s, %d\n", word, f);
	return 0;
}

int main()
{
	int  i;
	int  N; // кол-во слов, 3 <= N <= 50000
	int  F; // частота, 1 <= F <= 1000
	char word[WLEN+1]; // слово в словаре
	int  wBegin;
	int  isEnd;
	char c;
	FILE *f = stdin;//fopen("test1", "r");
	// кол-во слов в словаре
	dicAdd(".", 0);
	dicAdd(",", 0);
	dicAdd("?", 0);
	fscanf(f, "%d\n", &N);
	for (i = 0; i < N; i++)
	{
		fscanf(f, "%s %d\n", word, &F);
		// добавляем в словарь
		dicAdd(word, F);
	}
	// читаем фразу
	fgets(phrase, PLEN, f);
//	printf("%s\n",phrase);
	// обрабатываем
	i = 0; wBegin = 0; isEnd = 0;
	while (!isEnd)
	{
		isEnd = !phrase[i];
		// конец слова
		c = phrase[i];
		if (c == ' ' || c == 0 || c == 13 || c == 10)
		{
			phrase[i] = 0;  // конец слова
			if (wBegin != i)
			{
				translateWord(&phrase[wBegin], word);
				printf("%s%c", word, c);
			}
			wBegin = i + 1; // начало следующего слова
		}
		i++;
	}
	return 0;
}
