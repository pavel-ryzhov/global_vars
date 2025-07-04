#include <stdio.h>

#include <list>
#include <iostream>
using namespace std;

int N;
static int len_word=20;
static int max_len=100001;
static int max_freq=1000;


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
	

	for(int i=0;i<N;i++){
 		for(int j=0;j<len_word;j++){
 			w[j]=0;
		}	
		fscanf(file,"%s %d\n",w,&f);
		
 	}
	fgets(mes, max_len, file);
	fclose(file);	
	
	delete [] mes;
	delete [] w;
	//book.clear();
}

int main(void){
	read_write();
	return 0;
}
