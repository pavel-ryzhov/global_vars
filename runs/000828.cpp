#include <stdio.h>

#include <list>
#include <iostream>
using namespace std;

int N;
static int len_word=20;
static int max_len=100001;
static int max_freq=1000;

int letters(char a){
 	if(a=='a' || a=='b' || a=='c' || a=='A' || a=='B' || a=='C'){
		return 2;
	}
	else if(a=='d' || a=='e' || a=='f' || a=='D' || a=='E' || a=='F'){
		return 3;
	}
	else if(a=='g' || a=='h' || a=='i' || a=='G' || a=='H' || a=='I'){
		return 4;
	}
	else if(a=='j' || a=='k' || a=='l' || a=='J' || a=='K' || a=='L'){
		return 5;
	}
	else if(a=='m' || a=='n' || a=='o' || a=='M' || a=='N' || a=='O'){
		return 6;
	}
	else if(a=='p' || a=='q' || a=='r' || a=='s' || a=='S' || a=='P' || a=='Q' || a=='R'){
		return 7;
	}
	else if(a=='t' || a=='u' || a=='v'  || a=='T' || a=='U' || a=='V'){
		return 8;
	}
	else if(a=='x' || a=='y' || a=='z' || a=='w' || a=='W' || a=='X' || a=='Y' || a=='Z'){
		return 9;
	}
	else{
	//cout <<"Bukva ne iz alfavita" <<endl;
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
	if(ar_dic[i].freq <max_freq) ar_dic[i].freq++;
	(*book).erase(qq);
	for(qq=(*book).begin();qq!=(*book).end() &&(*qq)->freq>ar_dic[i].freq;qq++);
	(*book).insert(qq,&(ar_dic[i]));	
	return i;
}

char one_leter(int kvo_z){
	 if(kvo_z%3==0){
		return '.';
	}
	else if(kvo_z%3==1){
		return ',';
	}
	else{
		return '?';
	}
}

void read_write(void){
	FILE *file, *file_r;
	char* w=new char[len_word+1];
	char* mes=new char[max_len+1];
	int f;
	int mes_code=0;
	int kvo_z=0;
 	char space=0;
	file = fopen("file1.txt", "r" );
	fscanf(file,"%d\n",&N);
	int res=0;
	Dictionary* ar_dic=new Dictionary[N];
	list <Dictionary*> book;

	for(int i=0;i<N;i++){
 		for(int j=0;j<len_word;j++){
 			w[j]=0;
		}	
		fscanf(file,"%s %d\n",w,&f);
		ar_dic[i].init(w,f,i);
		list<Dictionary*>::iterator qq= book.begin();
		for(;qq!=book.end() &&(*qq)->freq>=ar_dic[i].freq;qq++);
		book.insert(qq,&(ar_dic[i]));
 	}
	fgets(mes, max_len, file);
	fclose(file);	
	file_r = fopen("res.txt", "w+" );
	
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
				fprintf(file,"%s",ar_dic[res].word);
			}
			fprintf(file_r,"%c",' ');
			kvo_z=0;
			mes_code=0;
		}
		else if(mes[i]=='1'){
			if(mes_code!=0){
			 	res=find_word(&book,mes_code,kvo_z, ar_dic);
				fprintf(file,"%s",ar_dic[res].word);
			}
			kvo_z=0;
			i++;
			for(;i<max_len && mes[i]=='*';i++){
				kvo_z++;
			}
			i--;
			space=one_leter(kvo_z);
			fprintf(file_r,"%c",space);
			kvo_z=0;
			mes_code=0;
		}
		else if(i>=max_len || mes[i]==0){
			if(mes_code!=0){
			 	res=find_word(&book,mes_code,kvo_z, ar_dic);
				fprintf(file,"%s",ar_dic[res].word);
			}
			break;
		}
		else{
			printf("ne dopustimy simvol %c\n",mes[i]);
		}	
	}

	fclose(file_r);
	delete [] mes;
	delete [] w;
	book.clear();
}

int main(void){
	read_write();
	return 0;
}
