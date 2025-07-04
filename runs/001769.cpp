#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>	
using namespace std;

const int K=8;

int alpha_index(char c)
{
	static const int alpha[]={0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,5,6,6,6,7,7,7,7};
	return alpha[c-'a'];
}

struct word
{
	string s;
	int raiting;

	word(const char *s,int raiting)
	{
		this->s=string(s);
		this->raiting=raiting;
	}

	bool operator<(const word &w) const
	{
		if(raiting>w.raiting)
			return true;
		if(raiting<w.raiting)
			return false;
		return s<w.s;
	}
};

typedef vector<word> wordlist;

void update_wordlist(wordlist &list,int index)
{
	while((index>0)&&(list[index-1].raiting<=list[index].raiting))
	{
		swap(list[index],list[index-1]);
		index--;
	}
}

struct node
{
	node *next[K];
	wordlist words;
	node()
	{
		memset(next,0,sizeof(next));
	}
};

node root;

void read_dictionary()
{
	char s[21];
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int rait;
		scanf("%s%d",s,&rait);
		node *t=&root;
		for(int j=0;s[j];j++)
		{
			node *&nx=t->next[alpha_index(s[j])];
			if(nx==0)
				nx=new node();
			t=nx;
		}
		t->words.push_back(word(s,rait));
	}
	gets(s);
}

void sort_dictionary(node &t)
{
	sort(t.words.begin(),t.words.end());
	for(int i=0;i<K;i++)
		if(t.next[i]!=0)
			sort_dictionary(*t.next[i]);
}

void print_word(node &elem,int stars)
{
	word &w=elem.words[stars];
	printf("%s",w.s.c_str());
	w.raiting++;
	update_wordlist(elem.words,stars);
}

void print_point(int stars)
{
	static const char chars[]={'.',',','?'};
	printf("%c",chars[stars]);
}

void print_state(char state,int stars,node &elem)
{
	if(state==1)
		print_word(elem,stars);
	else if(state==2)
		print_point(stars);
}

void read_text()
{
	char state=0;
	int stars=0;
	node *t=&root;
	char c;
	while(true)
	{
		c=getchar();
		if(c=='1')
		{
			print_state(state,stars,*t);
			state=2;
			stars=0;
		}
		else if(c=='*')
			stars++;
		else if(c==' ')
		{
			print_state(state,stars,*t);
			printf(" ");
			state=0;
		}
		else if(isdigit(c))
		{
			if(state!=1)
			{
				print_state(state,stars,*t);
				t=&root;
				stars=0;
				state=1;
			}
			t=t->next[c-'2'];
		}
		else
			break;
	}
	print_state(state,stars,*t);
}

void destroy_dictionary(node &t)
{
	for(int i=0;i<K;i++)
		if(t.next[i]!=0)
		{
			destroy_dictionary(*t.next[i]);
			t.next[i]=0;
		}
}

int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	read_dictionary();
	sort_dictionary(root);
	read_text();
	destroy_dictionary(root);
	return 0;
}