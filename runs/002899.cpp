#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include<limits>
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
T9*t9;
int codeword (char *word)
{
	int code;
	char *buf;
	buf=new char [20];
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
	delete[]buf;
	return code;	
}
void resh (int k,int N,int q)
{
	Sort *ss;
	ss=new Sort();
	int w;
	vector <Sort*>sort;
	T9 *t9tmp;
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
					w=i;
					for(int j=i+1;j<sort.size();j++)
					{
						if (sort[j]->fr>sort[w]->fr){w=j;}
					}
					if (w>0)
					{
						ss=sort[i];
						sort[i]=sort[w];
						sort[w]=ss;	
						w=0;
					}
				}
			}
			while (k>sort.size()-1){k=k-sort.size();}
			//buf=sort[k]->index;
			sort[k]->index->fr=sort[k]->index->fr+1;
			if (sort[k]->index!=t9)
			{
				if (sort[k]->index->nextptr){sort[k]->index->nextptr->predptr=sort[k]->index->predptr;}
				if (sort[k]->index->predptr){sort[k]->index->predptr->nextptr=sort[k]->index->nextptr;}
				t9->predptr=sort[k]->index;
				sort[k]->index->nextptr=t9;
				sort[k]->index->predptr=NULL;
				t9=sort[k]->index;
			}
			cout<<sort[k]->index->word;
			//fprintf(fileout,"%s",sort[k]->index->word);
			delete[]ss;
			sort.clear();
}
int main ()
{
	char fin;
	
	char *wordtmp,*buf,*wordtmp_r,*buf_r;//,*word,*bufword;	
	int N,q;
	T9 *t9tmp,*t9buf;
	int k=0;
	wordtmp=new char[20];
	buf=new char[20];
	wordtmp_r=wordtmp;
	buf_r=buf;

	//FILE *f;
	//if ((f=fopen("task.txt","r"))!=NULL)

	cin>>N;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//fscanf(f,"%d",&N);
	t9=new T9();
	cin>>t9->word;
	cin>>t9->fr;
		//fscanf(f,"%s",&t9->word);
		//fscanf(f,"%d",&t9->fr);
	t9->code=codeword(t9->word);
	t9->nextptr=NULL;
	t9->predptr=NULL;
	t9buf=t9;
	for (int i=1;i<N;i++)
	{
		t9tmp=new T9();
		cin>>t9tmp->word;
		cin>>t9tmp->fr;
		//fscanf(f,"%s",&t9tmp->word);
		//fscanf(f,"%d",&t9tmp->fr);

		t9tmp->code=codeword(t9tmp->word); 
		t9tmp->nextptr=NULL;
		t9tmp->predptr=t9buf;
		t9buf->nextptr=t9tmp;
		t9buf=t9tmp;
	}
	wordtmp[0]=NULL;
	while (true)
	{		
		cin>>buf;
		strcat(wordtmp,buf);
		
		//fscanf(f,"%s",wordtmp);
		buf[0]=NULL;
		while((strlen(wordtmp)>0)&&(wordtmp[0]=='*')){wordtmp=&wordtmp[1];}
		while(strlen(wordtmp)>0)
		{
			for(int i=0;((int)wordtmp[i]<50)&&(i<strlen(wordtmp));i++)
			{
				buf[i]=wordtmp[i];
				buf[i+1]=NULL;
			}
			wordtmp=&wordtmp[strlen(buf)];
					
			while (strlen(buf)>0)
			{
				if (buf[0]=='1')
				{
					k=0;
					int j=1;
					while ((buf[j]=='*')&&(j<strlen(buf)))
					{j++; k=k+1;}	
					while (k>2){k=k-3;}
					switch (k)
					{
						case 0:cout<<".";break;
						case 1:cout<<",";break;
						case 2:cout<<"?";break;
					}
					buf=&buf[j];
				}					
			}					
			buf[0]=NULL;
			
			for(int i=0;((wordtmp[i]!='*')&&(wordtmp[i]!='1')&&(i<strlen(wordtmp)));i++)
			{buf[i]=wordtmp[i];buf[i+1]=NULL;}
			wordtmp=&wordtmp[strlen(buf)];
			k=0;
			for(int i=0;((wordtmp[i]=='*')&&(i<strlen(wordtmp)));i++){k=k+1;}
			wordtmp=&wordtmp[k];
			if (buf[0])
			{
				q=atoi(buf);
				resh(k,N,q);
			}
		}
		wordtmp=wordtmp_r;
		buf=buf_r;
		wordtmp[0]=buf[0]=NULL;
		cin.get(fin);
		while (((int)fin)==32)
		{
			cout<<fin;
			cin.get(fin);
		}
		if(((int)fin)==10){break;}
		else
		{
			wordtmp[0]=fin;
			wordtmp[1]=NULL;
		}
	}
	delete[]wordtmp;
	delete[]buf;
	while (t9->nextptr!=NULL)
	{
		t9tmp=t9;
		t9=t9->nextptr;
		delete[]t9tmp;
	}
	delete[]t9;

	char b;
	cin.get(b);
	return 0;
}