#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define WORDLEN 20
#define QUERYLEN 100000

typedef struct{
	char word[WORDLEN + 1];
	char digits[WORDLEN + 1];
	int count;
	int history;
} word;

char but1[3] = {'.', ',', '?'}; 
char find_str[WORDLEN + 1];

bool Find(word w)
{
	if (!strcmp(w.digits, find_str))
		return true;
	else
		return false;
};

bool Sort(word* w1, word* w2)
{
	if ( (w1->count > w2->count) || (w1->count == w2->count && w1->history > w2->history) )
		return true;

	return false;
};


char* GetWord(char* p, vector<word*> vanswers, int step)
{
	bool one = false;
	int n = 0;
	char* answer = (char*)malloc(WORDLEN + 2);
	*answer=0;
	vector<word>::iterator it;

	while(!(*p == 0 || *p == 0x0d))
	{
		if(*p == '1')
		{
			if(n>0 && strlen(answer)>0)
				answer[strlen(answer) - 1] = but1[n%3];
			if(vanswers.size()>0)
			{
				strcat(answer, vanswers[n%vanswers.size()]->word);
				vanswers[n%vanswers.size()]->count++;
				vanswers[n%vanswers.size()]->history=step;
			}
			n=0;

			strcat(answer, ".");
			one = true;
		}
		else if(*p == '*')
		{
			n++;
		}
		p++;
	}

	if(n>0)
	{
		if(one)
			answer[strlen(answer) - 1] = but1[n%3];
		else
		{
			strcat(answer, vanswers[n%vanswers.size()]->word);
			vanswers[n%vanswers.size()]->history=step;
			vanswers[n%vanswers.size()]->count++;
		}
	}
	return answer;
}

int main(int argc, char* argv[])
{
	vector<word> words;
	vector<word*> vanswers;
	word newword;
	int nwords = 0;
	int i = 0, j=0;
	char fulltext[QUERYLEN+2];
	char *text;
	char answer[QUERYLEN + 1];
	char *curanswer;
	char comands[WORDLEN];
	vector<word>::iterator it;
	int step=0;
	char *p;
	bool end=false;

	answer[0]=0;
	scanf("%d", &nwords);
	for(i=0;i<nwords;i++)
	{
		scanf("%s %d", newword.word, &newword.count);

		newword.history=0;
		memset(newword.digits, 0, sizeof(newword.digits));
		for(j=0; j < strlen(newword.word); j++)
		{
			switch(newword.word[j])
			{
			case 'a':
			case 'b':
			case 'c':
				newword.digits[j]='2';
				break;
			case 'd':
			case 'e':
			case 'f':
				newword.digits[j]='3';
				break;
			case 'g':
			case 'h':
			case 'i':
				newword.digits[j]='4';
				break;
			case 'j':
			case 'k':
			case 'l':
				newword.digits[j]='5';
				break;
			case 'm':
			case 'n':
			case 'o':
				newword.digits[j]='6';
				break;
			case 'p':
			case 'q':
			case 'r':
			case 's':
				newword.digits[j]='7';
				break;
			case 't':
			case 'u':
			case 'v':
				newword.digits[j]='8';
				break;
			case 'w':
			case 'x':
			case 'y':
			case 'z':
				newword.digits[j]='9';
				break;
			}
		}
		words.push_back(newword);
	}

	memset(fulltext, 0, QUERYLEN+2);
	fread(fulltext, sizeof(char), QUERYLEN+2, stdin);
	strcat(fulltext, " ");
	p=fulltext;
	while(*p!=10)
		p++;
	p++;
	text=p;
	while(*p!=0)
	{

		if(*p != ' ' && *p != 10)
		{
			p++;
			continue;
		}
		if(*p == 10)
			end=true;
		*p=0;
		p++;
		if(strlen(text) == 0)
		{
			printf(" ");
			text = p;
			continue;
		}
		
		step++;
		for(i=0;i<=strlen(text);i++)
		{
			if(text[i] == '1' || text[i] == '*' || text[i] == 0)
			{
				memcpy(find_str, text, i);
				find_str[i]=0;
				vanswers.clear();

				it = words.begin();
				while(true)
				{
					it = find_if(it, words.end(), Find);
					if(it == words.end())
						break;
					vanswers.push_back(&*it);
					it++;
				}

				if(vanswers.size()==0 && text[0] != '1')
					break;
				sort(vanswers.begin(), vanswers.end(), Sort);

				if(text[i] == '1' || text[i] == '*')
				{
					curanswer = GetWord(&text[i], vanswers, step);
					strcat(answer, curanswer);
					free(curanswer);
				}
				else
				{
					strcat(answer, vanswers[0]->word);
					vanswers[0]->count++;
					vanswers[0]->history=step;
				}
				printf("%s ", answer);
				strcpy(answer, "");
				break;
			}
		}
		if(end)
			break;

		text = p;
	}
	return 0;
}
