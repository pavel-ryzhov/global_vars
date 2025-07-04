#include <iostream>
using namespace std;
struct Item{
	int freq;
	char *word;
};
Item *voc = NULL;
char chk_l(char c){
	if(c - 100 < 0)
		return '2';
	else
		if(c - 103 < 0)
			return '3';
		else
			if(c - 106 < 0)
				return '4';
			else
				if(c - 109 < 0)
					return '5';
				else
					if(c - 112 < 0)
						return '6';
					else
						if(c - 116 < 0)
							return '7';
						else
							if(c - 119 < 0 )
								return '8';
							else
								return '9';
}
Item *max(unsigned int a, unsigned int b, unsigned int st){
	Item **pt = new Item*[b-a+1];
	for(unsigned int i = 0; i <= b-a; i++)
		pt[i] = NULL;
	for(unsigned int i = a; i <= b; i++){
		for(unsigned int j = b-a;j>=0;j--)
			if( j == 0 || ((pt[j-1] != NULL) && (pt[j-1]->freq < voc[i].freq)) ){
				for(unsigned int k = b-a;k>j;k--)
					pt[k] = pt[k-1];
				pt[j] = &voc[i];
				break;
			}
	}
	int freq = pt[b - a]->freq;
	char *word  = pt[b - a]->word;
	pt[b - a]->word = pt[b - a - st]->word;
	pt[b - a]->freq = pt[b - a - st]->freq;
	pt[b - a - st]->word = word;
	pt[b - a - st]->freq = freq;
	pt[b - a]->freq++;
	return pt[b - a];
}
int main(){
	unsigned int n;
	cin>>n;
	voc = new Item[n];
	for(unsigned int k=0;k<n;k++){
		voc[k].word = new char[20];
		cin>>voc[k].word>>voc[k].freq;
	}
	cin.get();
	char p=cin.get();
	unsigned int a = 0, b = n-1, c = 0 , st = 0, res_i = 0;
	int find_word = 0, i = 0;
	while(p != 10){
		if(find_word == 0){
			if(p <='9' && p >='2'){
				find_word = 1;
				i = 0;
				a = 0;
				b = n-1;
				st = 0;
			}
		}
		else
			if(find_word == 1){
				if(p <='9' && p >='2')
					i++;
				else
					if(p == ' '){
						Item *m = max(a, b, st);
						cout<<m->word<<' ';
						find_word = 0;
					}
					else 
						if(p == '1'){
							Item *m = max(a, b, st);
							cout<<m->word;
							find_word = 2;
							st=0;
						}
						else
							if(p == '*')
								st++;
			}
			else
				if(find_word == 2){
					if(p == ' '){
						if(st==0)
							cout<<'.';
						else
							if(st==1)
								cout<<',';
							else
								if(st==2)
									cout<<'?';
					cout<<' ';
					find_word = 0;
					}
					else 
						if(p == '*'){
							st++;
						}
				}
		if(find_word == 1 && st == 0){
			c = a + (b - a)/2; 
			while(chk_l(voc[c].word[i]) != p){
				if (chk_l(voc[c].word[i]) < p)
					a = c + 1;
				else
					b = c - 1;
				c = a + (b - a)/2;
			}
			if(i == 0){
				a = b = c;
				while(a > 0 &&chk_l(voc[a-1].word[i]) == p) a--;
				while(b < n-1 && chk_l(voc[b+1].word[i]) == p) b++;
			}
			else{
				unsigned int a2 = c, b2 = c;
				while(a2 > a && chk_l(voc[a2-1].word[i]) == p) a2--;
				while(b2 < b && chk_l(voc[b2+1].word[i]) == p) b2++;
				a = a2;
				b = b2;
			}
		}
		p=cin.get();
	}
	if(find_word == 1){
		Item *m = max(a, b, st);
		cout<<m->word<<' ';
		find_word = 0;
	}
	else
		if(find_word == 2){
			if(st==0)
				cout<<'.';
			else
				if(st==1)
					cout<<',';
				else
					if(st==2)
						cout<<'?';
		}
	return 0;
}