
#include "string.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

map<string,vector<pair<string,int> > > root;
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
			vector<pair<string,int> >& v =root.find(string(word,i))->second;
			vector<pair<string,int> >::iterator it=v.begin();
			
			while(*c=='*'){//если * - перебираем варианты
				it++;
				c++;
			}		

			it->second++;
			cout<<it->first;
			{//поставим это слово первым среди равных по рангу
				vector<pair<string,int> >::iterator there=v.begin();
				while(there->second>it->second){
					there++;
				}
				if(there!=it){
					int size=it-there;
					pair<string,int>buffer=*it;
					for(int i=size;i>0;i--){
						there[i]=there[i-1];
					}
					*there=buffer;
					//v.insert(there,*it);//вставим на новое место			
					//v.erase(it);// уберем в старом месте
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
	vector<pair<string,int> > v;
	v.push_back(pair<string,int>(string(word),rank));
	pair<map<string,vector<pair<string,int> > >::iterator,bool> ret;
	ret=root.insert(pair<string,vector<pair<string,int> > >(string(digits),v));
	if(ret.second==false){
			vector<pair<string,int> >& it=ret.first->second;
			it.push_back(pair<string,int>(word,rank));
			/*while(it!=ret.first->second.end()){//находим нужное место
				if(it->second<rank)//сначала по рангу
					break;
				if(it->second==rank)//затем по алфавиту
					if(it->first.compare(word)>=0)
						break;
				it++;
			}
			ret.first->second.insert(it,pair<string,int>(word,rank));*/
	}
}
bool cmp(pair<string,int> a, pair<string,int> b){
	if(a.second==b.second){
		if(a.first.compare(b.first)<=0)
			return true;
		else
			return false;
	}else
		if(a.second>b.second)
			return true;
		else
			return false;
}

void sortThisMess(map<string,vector<pair<string,int> > >::iterator o){
	sort(o->second.begin(),o->second.end(),cmp);
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
	for(map<string,vector<pair<string,int> > >::iterator it=root.begin();
		it!=root.end();it++)
		sortThisMess(it);
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

