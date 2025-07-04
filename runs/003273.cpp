#include <stdio.h>
#include <string>
#include <map>
#include <cstdlib>

using namespace std;

enum {NEW_GROUP, TYPING_WORD, TYPING_SIGN};

class TKey
{
public:
	int freq, pr;
	string val;

	bool operator <(const TKey &k) const
	{
		if (freq>k.freq) return 1;
		if (freq<k.freq) return 0;
		if (pr>k.pr) return 1;
		if (pr<k.pr) return 0;
		if (val<k.val) return 1; //выдаем наименьшую по алфавиту
		return 0;
	}


};

typedef map<TKey,string> words_map;
map <string,words_map> dictionary;

void Print_word(string word, int* number, int k_word)
{
	words_map::iterator iter=dictionary[word].begin();
	for (int i=0; i<k_word; i++)
	{
		iter++;
	}
	printf("%s",(iter->second).c_str());
	TKey temp_key=iter->first;
	dictionary[word].erase(iter);
	(*number)++;
	temp_key.freq++;
	temp_key.pr=*number;
	dictionary[word][temp_key]=temp_key.val;
}

int main()
{
	char s[21];
	string word;
	char signs[3];
	signs[0]='.'; signs[1]=','; signs[2]='?';
	char c;
	map <char,char> t9;
	t9['a']='2'; t9['b']='2'; t9['c']='2'; t9['d']='3'; t9['e']='3'; t9['f']='3'; t9['g']='4'; t9['h']='4'; t9['i']='4'; t9['j']='5';
	t9['k']='5'; t9['l']='5'; t9['m']='6'; t9['n']='6'; t9['o']='6'; t9['p']='7'; t9['q']='7'; t9['r']='7'; t9['s']='7'; t9['t']='8'; t9['u']='8';
	t9['v']='8'; t9['w']='9'; t9['x']='9'; t9['y']='9'; t9['z']='9';
	int n, priority;
	map <string,words_map>::iterator it;

	scanf("%d",&n);
	gets(s);
	for (int i=0; i<n; i++)
	{
		scanf("%s %d", s, &priority);
		word=s;
		gets(s);
		string word_code="";
		for (int j=0; j<word.length(); j++)		
			word_code+=t9[word[j]];
		TKey k;
		k.freq=priority;
		k.pr=0;
		k.val=word;
		it=dictionary.find(word_code);
		if (it==dictionary.end()) //у нас нет еще дерева вариантов для этой комбинации
		{
			words_map *new_map = new words_map;
			dictionary[word_code]=*new_map;
		}
		dictionary[word_code][k]=k.val;
	}
	word="";
	int state=NEW_GROUP;
	int k_word=0, k_sign=0, number=0;
	while (scanf("%c",&c)==1)
	{
		switch (c)
		{
		case ' ':
			if (state==TYPING_WORD) //мы напечатали слово и потом пробел
			{
				//надо вывести это слово, сохраненное в word и изменить его частоту.
				Print_word(word,&number,k_word);
				k_word=0;
				word="";
				printf(" ");
				state=NEW_GROUP; //переводим в состояние ожидания ввода
			}
			else if (state==TYPING_SIGN)
			{
				//тут мы печатали знак препинания, надо его вывести
				printf("%c",signs[k_sign]);
				k_sign=0;
				printf(" ");
				state=NEW_GROUP;
			}
			else printf(" ");
			break;
		case '1':
			if (state==TYPING_WORD)
			{
				//выводим слово
				Print_word(word,&number,k_word);
				k_word=0;
				word="";
				state=TYPING_SIGN;
			}
			else if (state==NEW_GROUP)
			{
				state=TYPING_SIGN;
			}
			else if (state==TYPING_SIGN)
			{
				printf("%c",signs[k_sign]);
				k_sign=0;

			}
			break;
		case '*':
			
			{
				if (state==TYPING_WORD) k_word++;
				else if (state==TYPING_SIGN) k_sign++;
			}
			break;
		case '\n':
		{
			if (state==TYPING_WORD)
			{
				Print_word(word, &number, k_word);

			}
			else if (state==TYPING_SIGN)
			{
				printf("%c",signs[k_sign]);

			}
		}
		break;
		default:
			{
				if (state==TYPING_SIGN)
				{
					printf("%c",signs[k_sign]);
					k_sign=0;
				}
				word+=c;
				state=TYPING_WORD;
			}

		}
	}
	
	return 0;
}