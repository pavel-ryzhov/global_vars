#include <stdio.h>

#include <list>
#include <iostream>
using namespace std;

int N;
static int len_word=20;
static int max_len=100001;
static int max_freq=1000;

int letters(char a){
 	if(a=='a' || a=='b' || a=='c'){
		return 2;
	}
	else if(a=='d' || a=='e' || a=='f'){
		return 3;
	}
	else if(a=='g' || a=='h' || a=='i' ){
		return 4;
	}
	else if(a=='j' || a=='k' || a=='l'){
		return 5;
	}
	else if(a=='m' || a=='n' || a=='o'){
		return 6;
	}
	else if(a=='p' || a=='q' || a=='r' || a=='s'){
		return 7;
	}
	else if(a=='t' || a=='u' || a=='v'){
		return 8;
	}
	else if(a=='x' || a=='y' || a=='z' || a=='w'){
		return 9;
	}
	else{
	return 0;
	}
}



class Dictionary{
 public:
	Dictionary(){
		word=new char[len_word];
		freq=0;
		code=0;
		index=0;
	}
	~Dictionary(){
		delete [] word;
	}
	char* word;
	int freq;
	int code;
	int index;

	void init(char* w, int f,int in){
		for(int i=0;i<len_word;i++){
		word[i]=w[i];
		}
		freq=f;
		codes(word);
		index=in;
	}

	void codes(char* w){
		int c=0;
 		for(int i=0;i<len_word && w[i]!=0;i++){
			c*=10;	
			c+=letters(w[i]);
		}
		code=c;
	}

};



int find_word(list<Dictionary*> *book,int mes_code,int kvo_z, Dictionary* ar_dic){

	list<Dictionary*>::iterator qq= (*book).begin();
	list<Dictionary*>::iterator ss= (*book).begin();
	int k=0;
	for(;qq!=(*book).end();qq++){
		if((*qq)->code==mes_code){
			if(kvo_z==k){
				break;
			}
			else{
				k++;
			}
		}
	}
	int i=(*qq)->index;
	 
	ss=qq;
	if(qq!=(*book).begin()) ss--;
	if(ar_dic[i].freq <max_freq) ar_dic[i].freq++;
	(*book).erase(qq);
	for(;ss!=(*book).begin() &&(*ss)->freq<=ar_dic[i].freq;ss--);
	(*book).insert(ss,&(ar_dic[i]));	
	return i;
}

char one_leter(int kvo_z){

	 if(kvo_z==0){
		return '.';
	}
	else if(kvo_z==1){
		return ',';
	}
	else{
		return '?';
	}
}

void read_write(void){
	char* w=new char[len_word+1];
	char* mes=new char[max_len+1];
	int f;
	int mes_code=0;
	int kvo_z=0;
 	char space=0;
	scanf("%d\n",&N);
	
	int res=0;
	Dictionary* ar_dic=new Dictionary[N];
	list <Dictionary*> book;
	
	for(int i=0;i<N;i++){
 		/*for(int j=0;j<len_word;j++){
 			w[j]=0;
		}*/	
		scanf("%s %d\n",w,&f);
		ar_dic[i].init(w,f,i);
		list<Dictionary*>::iterator qq= book.begin();
		for(;qq!=book.end() &&(*qq)->freq>=ar_dic[i].freq;qq++);
		book.insert(qq,&(ar_dic[i]));
 	}
	fgets(mes, max_len,stdin);
	
	
	for(int i=0;;i++){
		if(mes[i]>'1' &&mes[i]<='9'){
			mes_code*=10; 
			mes_code+=(mes[i]-48);
		}
		else if(mes[i]=='*'){
			kvo_z++;
		}
		else if(mes[i]==' '){
			if(mes_code!=0){
			 	res=find_word(&book,mes_code,kvo_z, ar_dic);
				printf("%s",ar_dic[res].word);
			}
			printf("%c",' ');
			kvo_z=0;
			mes_code=0;
		}
		else if(mes[i]=='1'){
			if(mes_code!=0){
			 	res=find_word(&book,mes_code,kvo_z, ar_dic);
				printf("%s",ar_dic[res].word);
			}
			kvo_z=0;
			i++;
			for(;i<max_len && mes[i]=='*';i++){
				kvo_z++;
			}
			i--;
			space=one_leter(kvo_z);
			printf("%c",space);
			kvo_z=0;
			mes_code=0;
		}
		else if(i>=max_len || mes[i]==0){
			if(mes_code!=0){
			 	res=find_word(&book,mes_code,kvo_z, ar_dic);
				printf("%s",ar_dic[res].word);
			}
			break;
		}
		else{
			//printf("ne dopustimy simvol %c\n",mes[i]);
		}	
	}

	delete [] mes;
	delete [] w;
	book.clear();
}

int main(void){
	read_write();
	return 0;
}
