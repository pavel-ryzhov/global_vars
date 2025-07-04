#include<cstdio>
#include<map>
#include<list>
#include<string>
#include<cctype>
#include <iostream>

#define WORDLEN 21
#define HASHEND 8
#define VOCMIN 3
#define VOCMAX 50000
#define ERRORLEN 100
#define PMIN 1
#define PMAX 1000

using namespace std;

class spisok
{
public:
	list<string> words_list;
	int len;

	spisok(){
		this->len=0;
	}
};

class node
{
public:
	map<int,spisok> words;
	int len;
	node* child[HASHEND];
	node(){
		this->len=0;
	}
};

inline void hash_func(short unsigned int*hash,string &word)
{
	short unsigned int i;
	char symbol;
	for(i=0;symbol=word[i];++i)
	{
		if((symbol>='a')&&(symbol<'p'))
			hash[i]=(symbol-'a')/3;
		else if((symbol>'o')&&(symbol<'t'))
			hash[i]=5;
		else if((symbol>'s')&&(symbol<'w'))
			hash[i]=6;
		else if((symbol>'v')&&(symbol<='z'))
			hash[i]=7;
		else 
			throw "Invalid symbol in vocabulary\n";
	};
	hash[i]=HASHEND;
}

struct tree
{
	node* top;

	void insert_node(string word,int probabilaty)
	{
		short unsigned int i,j,hash[WORDLEN];
		node* cur_node=this->top;
		
		hash_func(hash,word);

		for(i=0;hash[i]<HASHEND;++i)
		{
			if(!cur_node->child[hash[i]])
			{
				cur_node->child[hash[i]] = new node;
				cur_node=cur_node->child[hash[i]];
				for(j=0;j<8;++j)
					cur_node->child[j]=0;
			}
			else
				cur_node=cur_node->child[hash[i]];
		}
			
		(cur_node->words)[probabilaty].words_list.push_back(word);
		(cur_node->words)[probabilaty].len++;
		(cur_node->len)++;
	}

	void find_word(short unsigned int hash[WORDLEN],short unsigned int degree)
	{
		int place=0,i,probabilaty;
		node* cur_node=this->top;

		for(i=0;hash[i]<HASHEND;++i)
		{
			cur_node=cur_node->child[hash[i]];
			if(cur_node==0)
				throw "Sms word was not found in vocabulary\n";
		}
		if((cur_node->len)==0)
				throw "Sms word was not found in vocabulary\n";
		degree%=((cur_node->len));
		
		map<int,spisok>::iterator it=(cur_node->words).end();
		do
		{
			--it;
			place+=(*it).second.len;
		} 
		while(place<=degree && it!=(cur_node->words).begin());

		probabilaty=(*it).first;
		place = degree-place+(*it).second.len;

		list<string>::iterator it1=(*it).second.words_list.begin();
		for(i=0;i<place;i++) it1++;

		cout<<(*it1);

		(cur_node->words)[probabilaty+1].words_list.push_front((*it1));
		(cur_node->words)[probabilaty+1].len++;

		(cur_node->words)[probabilaty].words_list.erase(it1);
		(cur_node->words)[probabilaty].len--;
				
	}

	void clear(node* cur_node=0)
	{
		if(!cur_node)
			cur_node=this->top;
		for(int i=0;i<HASHEND;++i)
			if((cur_node->child[i])!=0)
				clear(cur_node->child[i]);
		delete cur_node;
		return;
	}

};

int main()
{
	const char sign[3]={'.',',','?'};
	int i,N,degree=0,status,smsend;
	string prev;
	string word;
	int probabilaty;
	short unsigned int hash[WORDLEN];
	char symbol;
	struct tree vocabulary;

	try
	{
		vocabulary.top=new node;
		for(i=0;i<8;++i)
			(vocabulary.top)->child[i]=0;

		status=scanf("%d", &N);
		if(status!=1)
			throw "Invalid input file format\n";
		if((N<VOCMIN)||(N>VOCMAX))
			throw "Incorrect words number in vocabulary\n";

		//status=scanf("%s %d",word,&probabilaty);
		
		cin >> word >> probabilaty;
		//if(status!=2)
		//	throw "Invalid input file format\n";
		if(probabilaty<PMIN||probabilaty>PMAX)
			throw "Incorrect word probabilaty in vocabulary\n";
		vocabulary.insert_node(word,probabilaty);
		prev=word;
		
		for(i=1;i<N;++i)
		{
	//		status=scanf("%s %d",word,&probabilaty);
			cin >> word >> probabilaty;
//			if(status!=2)
//				throw "Invalid input file format\n";
			if((probabilaty<PMIN)||(probabilaty>PMAX))
				throw "Incorrect word probabilaty in vocabulary\n";
			if(word<=prev)
				throw "Vocabulary words must be ordered\n";
			vocabulary.insert_node(word,probabilaty);
			prev=word;
		}
	}
	catch(bad_alloc)
	{
		printf("Not enougn memory to store vocabulary\n");
		vocabulary.clear();
		return 0;
	}
	catch(char err[ERRORLEN])
	{
		printf("%s",err);
		vocabulary.clear();
		return 0;
	}

	i=0;
	status=1;
	symbol=' ';
	while((status==1)&&isspace(symbol))
		status=scanf("%c",&symbol);
	if(status!=1)
	{
		vocabulary.clear();
		return 0;
	}

	status=0;
	try
	{
		do
		{
			smsend=1;
			if((symbol<='9')&&(symbol>'1'))
			{
				if(status==1)
					printf("%c",sign[degree%3]);
				hash[i]=symbol-'2';
				++i;
				status=0;
				degree=0;
			}
			else if(symbol==' ')
			{
				if(status==0)
				{
					hash[i]=HASHEND;
					vocabulary.find_word(hash,degree);

					i=0;
					printf(" ");
				}
				else if(status == 2) 
					printf(" ");
				else
					printf("%c ",sign[degree%3]);
				degree=0;
				smsend=1;
				status=2;

			}
			else if(symbol=='1')
			{
				if(status==0)
				{
					hash[i]=HASHEND;
					vocabulary.find_word(hash,degree);
					i=0;
				}
				else if(status==1)
					printf("%c",sign[degree%3]);
				degree=0;
				status=1;					
			}
			else if(symbol=='*')
				degree++;
			else if(symbol=='\r' || symbol=='\n' || symbol == 0)
			{
				break;
			}
			else
				throw "Unknown symbol in sms\n";
		}
		while(scanf("%c",&symbol)==1);
	}
	catch(char err[ERRORLEN])
	{
		printf("%s",err);
		vocabulary.clear();
		return 0;
	}
	if(smsend)
	{
		if(status==0)
		{
			hash[i]=HASHEND;
			vocabulary.find_word(hash,degree);
			i=0;
			degree=0;
			status=1;
		}
		else if(status != 2)
			printf("%c",sign[degree%3]);
	}
	
	vocabulary.clear();
	return 0;
}