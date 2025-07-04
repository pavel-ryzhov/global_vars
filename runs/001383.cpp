#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string.h>

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
			strcat(answer, vanswers[n%vanswers.size()]->word);
			vanswers[n%vanswers.size()]->count++;
			vanswers[n%vanswers.size()]->history=step;
			n=0;

			strcat(answer, ".");
			one = true;
		}
		if(*p == '*')
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
	int i = 0, j = 0;
	char text[QUERYLEN + 1];
	char answer[QUERYLEN + 1];
	char *curanswer;
	char comands[WORDLEN];
	vector<word>::iterator it;
	int step=0;

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

	while(scanf("%s", text) != EOF)
	{
		step++;
		for(i=0;i<=strlen(text);i++)
		{
			if(text[i] == '1' || text[i] == '*' || text[i] == 0 || text[i] == 0x0d)
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

				if(vanswers.size() == 0)
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
	}
	return 0;
}