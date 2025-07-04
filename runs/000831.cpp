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
			
			kvo_z=0;
			mes_code=0;
		}
		else if(mes[i]=='1'){
			
			kvo_z=0;
			mes_code=0;
		}
		else if(i>=max_len || mes[i]==0){
			
			break;
		}
		else{
			printf("ne dopustimy simvol %c\n",mes[i]);
		}	
	}

	fclose(file_r);
	delete [] mes;
	delete [] w;
	//book.clear();
}

int main(void){
	read_write();
	return 0;
}
