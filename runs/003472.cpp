
#include "string.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
using namespace std;

map<string,list<pair<string,int> > > root;
char* T9me(char* word){
		char* c;
		int i=0;
		//string ans="";
		c=word;
		if(*c!='1'){// знак препинания после пробела?
			while(*c!='1'&&*c!='*'&&*c!=' '&&*c!=0){//находим нужную вершину
				i++;
				c++;
			}
			list<pair<string,int> >& l =root.find(string(word,i))->second;
			list<pair<string,int> >::iterator it=l.begin();
			while(*c=='*'){//если * - перебираем варианты
				it++;
				c++;
			}
			it->second++;
			cout<<it->first;
			{//поставим это слово первым среди равных по рангу
				list<pair<string,int> >::iterator there=l.begin();
				while(there->second>it->second){
					there++;
				}
				if(there!=it){
					l.insert(there,*it);//вставим на новое место			
					l.erase(it);// уберем в старом месте
				}
			}
		}
		if(*c==' '||*c==0){//если после слова пробел - выходим
				return c;
		}
		while(*c>40){//если есть '1'
			if(*c=='1'){
				int times=0;
				c++;
				while(*c=='*'){
					times++;
					c++;
				}
				switch (times){
					case 0: cout.put('.');
						break;
					case 1: cout.put(',');
						break;
					case 2: cout.put('?');
				}
			}else{
				break;
			}
		}
	return c;
}
void add(char* word,int rank){
	char digits[21];
	char* end=word+strlen(word);
	char* c=word;
	char* p=digits;
	digits[20]=0;
	while(c<end){// переводим буквы в цифры
		if(*c<'d')
			*p='2';
		else if(*c<'g')
			*p='3';
		else if(*c<'j')
			*p='4';
		else if(*c<'m')
			*p='5';
		else if(*c<'p')
			*p='6';
		else if(*c<'t')
			*p='7';
		else if(*c<'w')
			*p='8';
		else if(*c<='z')
			*p='9';
		else *p=0;
		c++;
		p++;
	}
	*p=0;
	p=digits;
	list<pair<string,int> > l;
	l.push_back(pair<string,int>(string(word),rank));
	pair<map<string,list<pair<string,int> > >::iterator,bool> ret;
	ret=root.insert(pair<string,list<pair<string,int> > >(string(digits),l));
	if(ret.second==false){
			list<pair<string,int> >::iterator it;
			it=ret.first->second.begin();
			while(it!=ret.first->second.end()){//находим нужное место
				if(it->second<rank)//сначала по рангу
					break;
				if(it->second==rank)//затем по алфавиту
					if(it->first.compare(word)>=0)
						break;
				it++;
			}
			ret.first->second.insert(it,pair<string,int>(word,rank));
	}
}

int main(int argc, char* argv[])
{
	int wordCount;
	cin>>wordCount;

	char word[21];
	word[20]=0;
	int rank;
	for(int i=0;i<wordCount;i++){
		cin>>word>>rank;
		add(word,rank);
	}
	char str[100001];
	cin.get();
	cin.getline(str,100001);
	//in.close();
	char* c=str;
	//word="";
	while(*c!=0){
		if(*c!=' '&&*c!=0){
				c=T9me(c);
		}else{
			cout.put(*c);
			c++;
		}
	}
	cout<<endl;

	return 0;
}

