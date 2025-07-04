#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;
struct T9
{
	char word[20];
	int fr;
	int code;
	T9 *nextptr;
	T9 *predptr;

};
struct Sort
{
	int fr;
	T9 *index;
	char word[20];
};
int codeword (const char *word)
{
	int code;
	char buf[20];
	strcpy(buf,word);
	code=strlen(word);
	for (int i=0;buf[i];i++)
	{
		switch (buf[i])
		{
			case 'a':case 'b': case 'c': buf[i]='2';break;
			case 'd':case 'e': case 'f': buf[i]='3';break;
			case 'g':case 'h': case 'i': buf[i]='4';break;
			case 'j':case 'k': case 'l': buf[i]='5';break;
			case 'm':case 'n': case 'o': buf[i]='6';break;
			case 'p':case 'q': case 'r': case 's':buf[i]='7';break;
			case 't':case 'u': case 'v': buf[i]='8';break;
			case 'w':case 'x': case 'y':case 'z': buf[i]='9';break;
		}
	}
	code=atoi(buf);
	return code;	
}
T9* resh (int k,T9* t9,int N,int q)
{
	Sort *ss;
	ss=new Sort();
	int w;
	vector <Sort*>sort;
	T9 *t9tmp,*buf;
	t9tmp=t9;

	
			for(int i=0;i<N;i++)
			{
				if (t9tmp->code==q)
				{
					ss=new Sort();
					ss->index=t9tmp;
					strcpy(ss->word,t9tmp->word);
					ss->fr=t9tmp->fr;
					sort.push_back(ss);
				}
				t9tmp=t9tmp->nextptr;
			}
			w=0;
			if (sort.size()>1)
			{
				for(int i=0;i<sort.size()-1;i++)
				{
					for(int j=i+1;j<sort.size();j++)
					{
						if (sort[i]->fr<sort[j]->fr){w=j;}
					}
					if (w>0)
					{
						ss= sort[i];
						sort[i]=sort[w];
						sort[w]=ss;	
						w=0;
					}
				}
			}
			if (k>sort.size()-1){k=k-sort.size();}
			buf=sort[k]->index;
			sort[k]->index->fr=sort[k]->index->fr+1;
			if (sort[k]->index->nextptr){sort[k]->index->nextptr->predptr=sort[k]->index->predptr;}
			if (sort[k]->index->predptr){sort[k]->index->predptr->nextptr=sort[k]->index->nextptr;}
			t9->predptr=sort[k]->index;
			sort[k]->index->nextptr=t9;
			t9=sort[k]->index;
			printf("%s",sort[k]->index->word);
			delete[]ss;
			sort.clear();
	return t9;
}
int main()
{
	T9*t9,*t9tmp,*t9buf;
	int N,k,q;
	char *wordtmp=new char[20];
	char *buf=new char[20];
	char *bufstr=new char[20];

	bufstr=gets(bufstr);
	sscanf(bufstr,"%d",&N);
	t9=new T9();
	bufstr=gets(bufstr);
	sscanf(bufstr,"%s",&t9->word);
	sscanf(bufstr,"%d",&t9->fr);
	t9->code=codeword(t9->word);
	t9->nextptr=NULL;
	t9->predptr=NULL;
	t9buf=t9;
	for (int i=1;i<N;i++)
	{
		t9tmp=new T9();
		bufstr=gets(bufstr);
		sscanf(bufstr,"%s",&t9tmp->word);
		sscanf(bufstr,"%d",&t9tmp->fr);
		t9tmp->code=codeword(t9tmp->word);
		t9tmp->nextptr=NULL;
		t9tmp->predptr=t9buf;
		t9buf->nextptr=t9tmp;
		t9buf=t9tmp;
	}
	bool flag=false;
	bufstr=gets(bufstr);
	while (strlen(bufstr)>0)
		{
			if(flag){bufstr=&bufstr[1];}
			flag=true;
			sscanf(bufstr,"%s",wordtmp);
			bufstr=&bufstr[strlen(wordtmp)];
				
			while((strlen(wordtmp)>1)&&(wordtmp[0]=='*')){wordtmp=&wordtmp[1];}
			while(strlen(wordtmp)>0)
			{
				int i=0;
				while (((int)wordtmp[i]<50)&&(i<strlen(wordtmp)))
				{
					buf[i]=wordtmp[i];
					i=i+1;
				}
				buf[i]=NULL;
				wordtmp=&wordtmp[i];
					
				while (strlen(buf)>0)
				{
						if (buf[0]=='1')
						{
							k=0;
							int j=1;
							while ((buf[j]=='*')&&(j<strlen(buf)))
							{j++; k=k+1;}	
							if (k>2){k=k-3;}
							switch (k)
							{
								case 0:printf ("%s",".");break;
								case 1:printf ("%s",",");break;
								case 2:printf ("%s","?");break;
							}
							buf=&buf[j];
						}					
				}
				
				buf[0]=NULL;
				i=0;
				while(((wordtmp[i]!='*')&&(wordtmp[i]!='1')&&(i<strlen(wordtmp))))
				{buf[i]=wordtmp[i];buf[i+1]=NULL;i++;}
				wordtmp=&wordtmp[i];
				i=0;
				k=0;
				while(((wordtmp[i]=='*')&&(i<strlen(wordtmp)))){k=k+1;i++;}
				wordtmp=&wordtmp[i];
				if (buf[0])
				{
					q=atoi(buf);
					t9=resh(k,t9,N,q);
				}
				}
				if  (strlen(bufstr)>0){printf("%s"," ");}
			}


	return 0;
}