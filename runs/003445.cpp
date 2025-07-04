
#include <iostream>
#include <string>
#include <list>
using namespace std;

struct tree{
	tree* child[8];//2-9 -> 0-7
	list<pair<string,int> >* words;

	void add(string word, int rank){
	int i=0;
	char c;
	tree* ptr=this;
	string digits;
	digits.resize(word.length()+1);
	for(unsigned int i=0;i< word.length();i++){// переводим буквы в цифры
		if(word[i]<'d')
			digits[i]='2';
		else if(word[i]<'g')
			digits[i]='3';
		else if(word[i]<'j')
			digits[i]='4';
		else if(word[i]<'m')
			digits[i]='5';
		else if(word[i]<'p')
			digits[i]='6';
		else if(word[i]<'t')
			digits[i]='7';
		else if(word[i]<'w')
			digits[i]='8';
		else if(word[i]<='z')
			digits[i]='9';
		else digits[i]=0;
	}
	i=0;
	while(c=digits[i],c!=0){//перемещаемся в нужную вершину
		if(ptr->child[c-50]==0){//если нужно, создаем вершину
			ptr->child[c-50]=new tree();
		}
		ptr=ptr->child[c-50];
		i++;
	}
	if(ptr->words==0){//это первое слово в этой вершине
		ptr->words=new list<pair<string,int> >;
		ptr->words->push_back(pair<string,int>(word,rank));
		return;
	}
	list<pair<string,int> >::iterator it;
	it=ptr->words->begin();
	while(it!=ptr->words->end()){//находим нужное место
		if(it->second<rank)//сначала по рангу
			break;
		if(it->second==rank)//затем по алфавиту
			if(it->first.compare(word)>=0)
				break;
		it++;
	}
	ptr->words->insert(it,pair<string,int>(word,rank));

	}
	/// по числовому коду возвращает слово.
	string T9me(string word){
		char c;
		int i=0;
		tree* ptr=this;
		string ans="";
		c=word[i];
		if(c!='1'){// знак препинания после пробела?
			while(c=word[i],c!='1'&&c!='*'&&c!=' '&&c!=0){//находим нужную вершину
				ptr=ptr->child[c-50];
				i++;
			}
			list<pair<string,int> >::iterator it=ptr->words->begin();
			if(c==' '||c==0){//если после слова пробел - выходим
				it->second++;
				return it->first;
			}
			while(word[i]=='*'){//если * - перебираем варианты
				it++;
				i++;
			}
			it->second++;
			{//поставим это слово первым среди равных по рангу
				list<pair<string,int> >::iterator there=it;
				while(there->second<=it->second&&ptr->words->begin()!=there){
					there--;
				}
				ptr->words->insert(there,*it);//вставим на новое место
			}
			ans=it->first;
			ptr->words->erase(it);// уберем в старом месте
		}
		while(c=word[i],c!=0){//если есть '1'
			if(c=='1'){
				int times=0;
				i++;
				while(word[i]=='*'){
					times++;
					i++;
				}
				times%=3;//кажется это лишнее
				switch (times){
					case 0: ans+='.';
						break;
					case 1: ans+=',';
						break;
					case 2: ans+='?';
				}
			}
		}
		return ans;


	}
	tree(){
		for(int i=0;i<8;i++){
			child[i]=0;
		}
		words=0;
	}
	~tree(){
		for(int i=0;i<8;i++){
			delete(child[i]);
		}
		delete(words);
	}
};

int main(int argc, char* argv[])
{
	int wordCount;
	cin>>wordCount;
	tree root;
	string word;
	int rank;

	for(int i=0;i<wordCount;i++){
		cin>>word>>rank;
		root.add(word,rank);
	}
	string outBuf="";

	char str[100001];
	cin.get();
	cin.getline(str,100001);
	char* c=str;
	word="";
	while(*c!=0){
		if(*c!=' '&&*c!=0){
			word+=*c;
		}
		c++;
		if(*c==' '||*c==0){
			if(word.length()!=0)
				outBuf+=root.T9me(word);
			word="";
			outBuf+=*c;
		}
	}
	cout<<outBuf;

	return 0;
}

