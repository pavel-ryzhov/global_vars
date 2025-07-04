#include <string.h>
#include <iostream>
#include <vector>

#define WORDLEN 20
#define SMSLEN 100000
#define DICTLEN 50000
#define MAXFREQ 1000

using namespace std;

typedef unsigned short ushort;

int wordNum;

struct entry
{
	char  nums[WORDLEN+1];
	char  chars[WORDLEN+1];
	int freq;
};

void set_nums(entry &tempEntry)
{
	int i = 0;
	while (tempEntry.chars[i] != NULL)
	{
		if ( 'a' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'c')
		{
			tempEntry.nums[i] = '2';
		}
		if ( 'd' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'f')
		{
			tempEntry.nums[i] = '3';
		}
		if ( 'g' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'i')
		{
			tempEntry.nums[i] = '4';
		}
		if ( 'j' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'l')
		{
			tempEntry.nums[i] = '5';
		}
		if ( 'm' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'o')
		{
			tempEntry.nums[i] = '6';
		}
		if ( 'p' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 's')
		{
			tempEntry.nums[i] = '7';
		}
		if ( 't' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'v')
		{
			tempEntry.nums[i] = '8';
		}
		if ( 'w' <= tempEntry.chars[i]  && tempEntry.chars[i] <= 'z')
		{
			tempEntry.nums[i] = '9';
		}
		++i;
	}

	while (i<WORDLEN+1)
	{
		tempEntry.nums[i] = NULL;
		++i;
	}

}

void switch_punct(int shift)
{
	switch (shift)
	{
		case 1:	
			{
				printf(".");
				break;
			}
		case 2:	
			{
				printf(",");
				break;
			}
		case 3: 
			{
				printf("?");
				break;
			}
	}
}

void print_puncts(char * punctMarks)
{
	unsigned char shift = 0;
	ushort p = 0;
	while (p < strlen(punctMarks))
	{
		if (punctMarks[p] == '1' && !shift || punctMarks[p]  == '*')
			++shift;
		else 
		{
			switch_punct(shift);
			shift = 1;
		}
		++p;
		if (p == strlen(punctMarks))
			switch_punct(shift);
	}
}


void print_word(char * word, entry * dict)
{
	char letters[WORDLEN+1];
	char * s = word;
	int let = 0;
	while (*s != '*') 
	{
		 if (*s == NULL)
			 break;
		 letters[let] = *s;
		++let;
		++s;
	}
	letters[let] = NULL;
	ushort shift = 0;
	while (*s != NULL) 
	{
		++shift;
		++s;
	}

	for (int i = 0; i < wordNum ; ++i)
	{
		if (!strcmp(letters, dict[i].nums))
		{
			if (!shift)
			{
				printf("%s", dict[i].chars);
				dict[i].freq++;

				entry tempEntry = dict[i]; 
				 
				int j = i;
				while (dict[j].freq <= dict[i].freq && j) 
					j--;
				
				if (!j && dict[i].freq >= dict[0].freq)
					j = -1;

				for (int k = i; k > j+1; --k)
					dict[k] = dict[k-1];

				dict[j+1] = tempEntry;
				
				return;
			}
			else
				--shift;
		}
	}
}


void print_word_or_puncts(char * tempWord, entry * dict)
{
	ushort  i=0;
	if (tempWord[0] == '\n') 
	{
		
		while (tempWord[i] != NULL)
		{
			tempWord[i] = tempWord[i+1];
			i++;
		}
	}
	if (tempWord[i-1] == '\n')
		tempWord[i-1] = NULL;
	
	char  word[DICTLEN+WORDLEN+1] = "";
	char  puncts[SMSLEN] = "";
	i = 0;
	while (tempWord[i] != NULL)
	{
		if (tempWord[i] == '*')
		{
			if (strlen(word))
				strcat(word, "*");
			else
				strcat(puncts, "*");
		}
		else
		{
			if (tempWord[i] == '1')
			{
				if (strlen(word))
				{
					print_word(word, dict);
					for (int l=0; l<strlen(word); ++l)
						word[l] = NULL;
				}
				strcat(puncts, "1");
			}
			else
			{
				if (strlen(puncts))
				{
					print_puncts(puncts);
					for (int l=0; l<strlen(puncts); ++l)
						puncts[l] = NULL;
				}
				int j = 0;
				while (word[j] != NULL)
					++j;
				word[j] = tempWord[i];
			}
		}
		++i;
	}
	if (strlen(puncts))
		print_puncts(puncts);
	if (strlen(word))
		print_word(word, dict);
}



int main()
{
	vector<vector<entry > > dicts;
	dicts.resize(MAXFREQ);

	cin >> wordNum;
	
	entry tempEntry;
	for (ushort i = wordNum; i; --i)
	{
		
		strcpy(tempEntry.nums, "");
		cin >> tempEntry.chars >> tempEntry.freq;
		
		set_nums(tempEntry);
		dicts[tempEntry.freq-1].push_back(tempEntry);
	}



	entry * dict = new entry[wordNum];

	int k=0;
	for (int i = MAXFREQ-1; i > -1; --i)
	{
		for (int j = 0; j <dicts[i].size(); ++j)
		{
			dict[k] = dicts[i][j];
			++k;
		}
	}

	char tempWord[SMSLEN] = "";
	int sym = 0;
	bool isWord = false;
	char c;
	while(cin.get(c))
	{
		if (c != ' ' && c != '\n')
		{
			isWord = true;
			tempWord[sym] = c;
			++sym;
		}
		else 
		{
			if (isWord)
			{
				print_word_or_puncts(tempWord, dict);
				
				for (int l=0; l<sym; ++l)
					tempWord[l] = NULL;
				sym = 0;
				
				isWord = false;
				if (c != '\n')
					printf("%c", c);

			}
			else
				if (c != '\n')
					printf("%c", c);
		}
	} 
	if (tempWord != NULL)
		print_word_or_puncts(tempWord, dict);
	
	return 0;
}

