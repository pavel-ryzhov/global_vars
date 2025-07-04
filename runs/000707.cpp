#include<cstdio>
#include<vector>
#include<cstring>
#include<cctype>

#define WORDLEN 21
#define HASHEND 8
#define VOCMIN 3
#define VOCMAX 50000
#define ERRORLEN 100
#define PMIN 1
#define PMAX 1000

using namespace std;

struct rows
{
	char word[WORDLEN];
	short unsigned int probabilaty;
};

struct node
{
	vector<struct rows> words;
	struct node* child[HASHEND];
};

void hash_func(short unsigned int*hash,char*word)
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

int find_place(struct rows row,vector<struct rows>&words,int finish=-1)
{
	int start=0;
	int middle;
	int temp;
	int status=0;
	
	if(finish==-1)
	{
		finish=words.size()-1;
		status=1;
	}

	if(finish==-1)
		return 0;

	while((finish-start)>1)
	{
		middle = (start+finish)/2;
		if(words[middle].probabilaty<=row.probabilaty-status)finish=middle;
		else if(words[middle].probabilaty>row.probabilaty-status)start=middle;
		else
		{
			temp=strcmp(words[middle].word,row.word);
			if(temp<0) finish=middle;
			else if(temp>0) start=middle;
			else finish=start=middle;
		}
	}

	if(words[start].probabilaty<=row.probabilaty-status)
		middle=start;
	else if(words[finish].probabilaty<row.probabilaty-status)
		middle=finish;
	else
		middle=finish+1;
	
	return middle;
}

struct tree
{
	struct node* top;

	void insert_node(struct rows row)
	{
		short unsigned int i,j,hash[WORDLEN];
		struct node* cur_node=this->top;
		vector<struct rows>::iterator it;

		hash_func(hash,row.word);

		for(i=0;hash[i]<HASHEND;++i)
		{
			if(!cur_node->child[hash[i]])
			{
				cur_node->child[hash[i]] = new struct node;
				cur_node=cur_node->child[hash[i]];
				for(j=0;j<8;++j)
					cur_node->child[j]=0;
			}
			else
				cur_node=cur_node->child[hash[i]];
		}
			
		int temp=find_place(row,cur_node->words);
		it = (cur_node->words).begin();
		(cur_node->words).insert(it+find_place(row,cur_node->words),row);
//		printf("%d %s\n",temp,(cur_node->words)[temp].word);
	}

	void find_word(short unsigned int hash[WORDLEN],short unsigned int degree)
	{
		int n,place,i;
		struct rows tmp;
		struct node* cur_node=this->top;

		for(i=0;hash[i]<HASHEND;++i)
		{
			cur_node=cur_node->child[hash[i]];
			if(cur_node==0)
				throw "Sms word was not found in vocabulary\n";
		}
		if((n=(cur_node->words).size())==0)
				throw "Sms word was not found in vocabulary\n";
		degree%=n;
		printf("%s",(cur_node->words)[degree].word);
		strcpy(tmp.word,(cur_node->words)[degree].word);
		tmp.probabilaty=(cur_node->words)[degree].probabilaty+1;
		place=find_place(tmp,cur_node->words,degree);
		if(place!=degree)
		{
			for(i=degree;i>place;--i)
			{
				strcpy((cur_node->words)[i].word,(cur_node->words)[i-1].word);
				(cur_node->words)[i].probabilaty=(cur_node->words)[i-1].probabilaty;
			}
			strcpy((cur_node->words)[place].word,tmp.word);
			(cur_node->words)[place].probabilaty=tmp.probabilaty;
		}
	}

	void clear(struct node* cur_node=0)
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
	//FILE*in=fopen("a.txt","r");
	const char sign[3]={'.',',','?'};
	int i,N,degree=0,status,smsend;
	char prev[WORDLEN];
	short unsigned int hash[WORDLEN];
	char symbol;
	struct rows row;
	struct tree vocabulary;

	/*if(!in)
	{
		printf("File not found\n");
		return 0;
	}*/

	try
	{
		vocabulary.top=new struct node;
		for(i=0;i<8;++i)
			(vocabulary.top)->child[i]=0;

//		status=fscanf(in,"%d", &N);
		status=scanf("%d", &N);
		if(status!=1)
			throw "Invalid input file format\n";
		if((N<VOCMIN)||(N>VOCMAX))
			throw "Incorrect words number in vocabulary\n";

//		status=fscanf(in,"%s %d",row.word,&(row.probabilaty));
		status=scanf("%s %d",row.word,&(row.probabilaty));
		if(status!=2)
			throw "Invalid input file format\n";
		if((row.probabilaty<PMIN)||(row.probabilaty>PMAX))
			throw "Incorrect word probabilaty in vocabulary\n";
		vocabulary.insert_node(row);
		strcpy(prev,row.word);
		
		for(i=1;i<N;++i)
		{
//			status=fscanf(in,"%s %d",row.word,&(row.probabilaty));
			status=scanf("%s %d",row.word,&(row.probabilaty));
			if(status!=2)
				throw "Invalid input file format\n";
			if((row.probabilaty<PMIN)||(row.probabilaty>PMAX))
				throw "Incorrect word probabilaty in vocabulary\n";
			if(strcmp(row.word,prev)<=0)
				throw "Vocabulary words must be ordered\n";
			vocabulary.insert_node(row);
			strcpy(prev,row.word);
		}
	}
	catch(bad_alloc)
	{
		printf("Not enougn memory to store vocabulary\n");
//		fclose(in);
		vocabulary.clear();
		return 0;
	}
	catch(char err[ERRORLEN])
	{
		printf("%s",err);
//		fclose(in);
		vocabulary.clear();
		return 0;
	}
	
	i=0;
	status=1;
	symbol=' ';
	while((status==1)&&isspace(symbol))
		status=scanf("%c",&symbol);
//		status=fscanf(in,"%c",&symbol);
	if(status!=1)
	{
		//fclose(in);
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
					printf("%c ",sign[degree%3]);
				hash[i]=symbol-'2';
				++i;
				status=0;
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
				else
					printf("%c ",sign[degree%3]);
				degree=0;
				smsend=1;

			}
			else if(symbol=='1')
			{
				if(status==0)
				{
					hash[i]=HASHEND;
					vocabulary.find_word(hash,degree);
					i=0;
					status=1;
				}
				else
					printf("%c ",sign[degree%3]);
				degree=0;
					
			}
			else if(symbol=='*')
				degree++;
			else if(symbol=='\r' || symbol=='\n' || symbol == 0)
				break;
			else
				throw "Unknown symbol in sms\n";
		}
		while(scanf("%c",&symbol)==1);
//		while(fscanf(in,"%c",&symbol)==1);
	}
	catch(char err[ERRORLEN])
	{
		printf("%s",err);
		//fclose(in);
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
		else
			printf("%c ",sign[degree%3]);
	}
	
	vocabulary.clear();
//	fclose(in);
	return 0;
}