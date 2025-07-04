#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include <map>
#include <list>

using namespace std;
static int len_word=50000;
static int max_len=100001;

inline int letters(char a){
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
inline int codes(string w){
		int c=0;
 		for(int i=0;i<w.length() && w[i]!=0;i++){
			c*=10;	
			c+=letters(w[i]);
		}
		return c;
}


class Dictionary{
	public:
		string word;
		int freq;
};

map <int, list <Dictionary> > words;
int N;

string point[3]={".",",","?"};
inline void find_word(int mes_code,int kvo_z){
		list <Dictionary>::iterator it=(words[mes_code]).begin();
		for(int k=0;it!=(words[mes_code]).end() &&k!=kvo_z;it++,k++);
		Dictionary cur=*it;
		cout<<it->word;
		
		words[mes_code].erase(it);
		it->freq++;
		list <Dictionary>::iterator it1=(words[mes_code]).begin();
		for(;it1!=(words[mes_code]).end()&&(it1->freq)>cur.freq;it1++);
		words[mes_code].insert(it1,cur);
}

int main(void){
	cin>> N;
	for(int i=0;i<N;i++){
		Dictionary new_w;//(w,f); 
		cin>>new_w.word>>new_w.freq;
		int c=codes(new_w.word);
		if(words.count(c)==0){
			list <Dictionary> new_v;
			words[c].push_back(new_w);
		}
		else{	
			//words[c].push_back(new_w);
			list <Dictionary>::iterator it1=(words[c]).begin();
			for(;it1!=(words[c]).end()&&(it1->freq)>=new_w.freq;it1++);
			words[c].insert(it1,new_w);
		}
	}
	char* message=new char[max_len+1];
	while(message[1]==0) fgets(message, max_len,stdin);
		int mes_code=0,kvo_z=0;
		
		int k_point=0;
		int i=0;
		for(;message[i]!=0;i++){

			if(message[i]>'1' && message[i]<='9'){
				mes_code*=10; 
				mes_code+=int(message[i]-48);
			}
			else if(message[i]=='*'){
				kvo_z++;
			}
			else if(message[i]=='1'){
				if(mes_code!=0){
				 	find_word(mes_code,kvo_z);
					mes_code=0,kvo_z=0;
				}
				for(++i;message[i]!=0&&message[i]=='*'; i++,k_point++);
				i--;
				cout<<point[k_point];
				k_point=0;
			}
			else if(message[i]==' '){
				if(mes_code!=0){
				 	find_word(mes_code,kvo_z);
					mes_code=0,kvo_z=0;
				}
				cout<<" ";

			}
			
		}
		if(mes_code!=0) find_word(mes_code,kvo_z);
	return 0;
}
