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
char buttons[8][4] = {	{'a', 'b', 'c', 0}, 
						{'d', 'e', 'f', 0},
						{'g', 'h', 'i', 0},
						{'j', 'k', 'l', 0},
						{'m', 'n', 'o', 0},
						{'p', 'q', 'r', 's'},
						{'t', 'u', 'v', 0},
						{'w', 'x', 'y', 'z'},
};
vector<word> words;
vector<word*> vanswers[1500];
char find_str[WORDLEN + 1];

bool Sort(word* w1, word* w2)
{
	if ( (w1->count > w2->count) || (w1->count == w2->count && w1->history > w2->history) ||  (w1->count == w2->count && w1->history == w2->history && strcmp(w1->word, w2->word)<0) )
		return true;

	return false;
};

int Find(int l, int r, int num, char c)
{
	int i = l-1;
	int j = r + 1;
	int k;

	if(l==r)
	{
		if(words[l].word[num] == c)
			return l;
		else
			return -1;
	}
	while (i < j - 1)
	{
		k = (i + j)/2;
		if (c >= words[k].word[num])
			i = k;
		else
			j = k;
	}
	if ((i >= 0) && (words[i].word[num] == c))
	{
		return i;
	}

	return -1;
}

char *GetAnswer(int n, int step)
{
	int i;
	word *w = NULL;
	for(i=1499; i>=0; i--)
	{
		if(vanswers[i].size() > 0 )
		{
			if(!w)
			{
				if(vanswers[i].size() <= n )
				{
					n-=vanswers[i].size();
				}
				else
				{
					sort(vanswers[i].begin(), vanswers[i].end(), Sort);

					w = vanswers[i][n];
					w->count++;
					w->history = step;
				}
			}
			vanswers[i].clear();
		}
	}
	if(w)
		return w->word;
	else
		return "";
}

char* GetWord(char* p, int step, char** end)
{
	bool one = false;
	int n = 0;
	char* answer = (char*)malloc(WORDLEN + 2);
	*answer=0;
	vector<word>::iterator it;

	while(!(*p == 0 || *p == 10))
	{
		if(*p == '1')
 		{
			if(n>0 && strlen(answer)>0)
				answer[strlen(answer) - 1] = but1[n%3];
			strcat(answer, GetAnswer(n, step));
			n=0;
			strcat(answer, ".");
			one = true;
		}
		else if(*p == '*')
		{
			n++;
		}
		else
		{
			*end = p;
			break;
		}
		p++;
	}

	if(n>0)
	{
		if(one)
			answer[strlen(answer) - 1] = but1[n%3];
		else
		{
			strcat(answer, GetAnswer(n, step));
		}
	}
	*end = p;
	return answer;
}

int main(int argc, char* argv[])
{
	word newword;
	int nwords = 0;
	int i = 0, j=0, k=0, n=0;
	char fulltext[QUERYLEN+2];
	char *text;
	char answer[QUERYLEN + 1];
	char *curanswer;
	vector<word>::iterator it;
	int step=0;
	char *p;
	bool txtend=false;
	int ind[26];
	char prevchar=0;

	newword.history=0;
	answer[0]=0;
	memset(&ind[0], -1, sizeof(int)*26);
	scanf("%d", &nwords);
	for(i=0;i<nwords;i++)
	{
		scanf("%s %d", newword.word, &newword.count);
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
		newword.digits[j]=0;
		if(newword.word[0] != prevchar)
		{
			prevchar=newword.word[0];
			ind[prevchar-'a'] = i;
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
			txtend=true;
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

				int dig=find_str[0]-50;
				int pos;
				for(j=0; j < 4; j++)
				{
					if(buttons[dig][j] == 0)
						break;
					if(ind[buttons[dig][j]-'a'] != -1)
					{
						int end=buttons[dig][j]-'a'+1;
						while(ind[end] == -1 && end<26)
							end++;
						if(end==26)
							end=words.size()-1;
						else
							end=ind[end]-1;

						for(n=0; n < 4; n++)
						{		
							if(find_str[1] == 0)
							{
								if(!strcmp(words[ind[buttons[dig][j]-'a']].digits, find_str))
									vanswers[words[ind[buttons[dig][j]-'a']].count].push_back(&words[ind[buttons[dig][j]-'a']]);
							}
							int dig1=find_str[1]-50;
							if(buttons[dig1][n] == 0)
								break;

							pos = Find(ind[buttons[dig][j]-'a'], end, 1, buttons[dig1][n]);
							if(pos!=-1)
							{
								k=0;
								while(words[pos+k].word[1] == buttons[dig1][n] && (pos+k<=end))
								{
									if(!strcmp(words[pos+k].digits, find_str))
										vanswers[words[pos+k].count].push_back(&words[pos+k]);
									k++;
									if(pos+k >= words.size())
										break;
								}
								if(pos<=0)
									continue;
								k=-1;
								while(words[pos+k].word[1] == buttons[dig1][n] && (pos+k>=ind[buttons[dig][j]-'a']))
								{
									if(!strcmp(words[pos+k].digits, find_str))
										vanswers[words[pos+k].count].push_back(&words[pos+k]);
									k--;
									if(pos+k < 0)
										break;
								}
							}
						}
					}
				}

				if(text[i] == '1' || text[i] == '*')
				{
					curanswer = GetWord(&text[i], step, &text);
					strcat(answer, curanswer);
					free(curanswer);
				}
				else
				{
					strcat(answer, GetAnswer(0, step));
					*text=0;
				}
				printf("%s", answer);
				strcpy(answer, "");
				
				if(strlen(text)==0)
				{
					printf(" ");
					break;
				}
				else
				{
					i=0;
				}
			}
		}
		if(txtend)
			break;

		text = p;
	}
	return 0;
}
