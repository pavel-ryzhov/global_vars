#include <iostream>
using namespace std;
struct Item{
	unsigned int key;
	unsigned int f_weight;
	Item *father;
};
Item **tr_vect, *root;
unsigned int fnd;
unsigned long int find(unsigned int bg, unsigned int en){
	unsigned long int res = 0;
	Item *op1 = tr_vect[bg-1], *op2 = tr_vect[en-1];
	do{
		unsigned long int temp_res = 0;
		op2 = tr_vect[en-1];
		while(op2){
			if(op2 == op1)
				return res + temp_res;
			temp_res+=op2->f_weight;
			op2=op2->father;
		}	
		res+= op1->f_weight;
		op1 = op1->father;
	}while(op1);
	return -1;
}

int main(){
	unsigned int n;
	cin>>n;
	tr_vect = new Item*[n];
	tr_vect[0] = root = new Item;
	root->key = 1;
	root->father = NULL;
	root->f_weight = 0;
	for(unsigned int i=1;i<n;i++){
		tr_vect[i] = new Item;
		tr_vect[i]->key = i+1; 
		tr_vect[i]->father = NULL;
	}
	for(unsigned int i=0;i<n-1;i++){
		unsigned int bg, en, wt;
		cin>>bg>>en>>wt;
		tr_vect[bg-1]->father = tr_vect[en-1];
		tr_vect[bg-1]->f_weight = wt;
	}
	unsigned int m;
	cin>>m;
	unsigned long int *res= new unsigned long int[m];
	for(unsigned int i=0;i<m;i++){
		unsigned int bg,en;
		cin>>bg>>en;
		res[i] = find(bg, en);
	}
	for(unsigned int i=0;i<m;i++) cout<<res[i]<<endl;
	return 0;
}