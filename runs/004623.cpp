#include <iostream>
using namespace std;
class voc{
private:
	struct item{
		char *word;
		int freq;
		item *next;
		item *prev;
	};

	struct olap{
		olap *mas[8];
		item *list;
		olap(){
			mas[0] = NULL;
			mas[1] = NULL;
			mas[2] = NULL;
			mas[3] = NULL;
			mas[4] = NULL;
			mas[5] = NULL;
			mas[6] = NULL;
			mas[7] = NULL;
			list = NULL;
		}
	} *cube;
	
	int chk_l(char c){
		if(c - 100 < 0)
			return 0;
		else
			if(c - 103 < 0)
				return 1;
			else
				if(c - 106 < 0)
					return 2;
				else
					if(c - 109 < 0)
						return 3;
					else
						if(c - 112 < 0)
							return 4;
						else
							if(c - 116 < 0)
								return 5;
							else
								if(c - 119 < 0 )
									return 6;
								else
									return 7;
	}
	void inc(item *elt, item *first){
		elt->freq += 1;
		
		if(first->freq <= elt->freq){
			item *ptrI = new item;
			ptrI->word = first->word;
			ptrI->freq = first->freq;
			ptrI->next = first->next;
			ptrI->prev = first;
			first->word = elt->word;
			first->freq = elt->freq;
			first->next = ptrI;
			first->prev = NULL;
			elt->prev->next = elt->next;
			elt->next->prev = elt->prev;
			delete elt;
			return;
		}
		item *cur = first->next;
		cur = first->next;
		do{
			if(cur == NULL || cur->freq <= elt->freq){
				elt->prev->next = elt->next;
				elt->next->prev = elt->prev;
				cur->prev->next = elt;
				elt->prev = cur->prev;
				cur->prev = elt;
				elt->next = cur;
				return;
			}
			cur = cur->next;
		}while(1);
	}
public:
	voc(){
		cube = new olap();
	}

	void add(char *word, int freq){
		olap *ptr = cube;
		for(int i=0;word[i];i++)
			if(ptr->mas[chk_l(word[i])]){
				ptr = ptr->mas[chk_l(word[i])];
			}
			else{
				ptr->mas[chk_l(word[i])] = new olap();
				ptr = ptr->mas[chk_l(word[i])];
			}
		
		if(!ptr->list){
			ptr->list = new item;
			ptr->list->word = word;
			ptr->list->freq = freq;
			ptr->list->next = NULL;
			ptr->list->prev = NULL;
			return;
		}
		if(ptr->list->freq < freq){
			item *ptrI = new item;
			ptrI->word = word;
			ptrI->freq = freq;
			ptrI->next = ptr->list;
			ptrI->prev = NULL;
			ptr->list = ptrI;
			return;
		}
		item *curI = ptr->list->next, *prevI = ptr->list;
		
		do{
			if(curI == NULL || curI->freq < freq){
				item *ptrI = new item;
				ptrI->word = word;
				ptrI->freq = freq;
				ptrI->next = curI;
				ptrI->prev = prevI;
				if(curI){
					curI->prev->next = ptrI;
					curI->prev = ptrI;
				}
				return;
			}
			prevI = curI;
			curI = curI->next;
		}while(curI);

	}



	void find(char word[]){
		olap *ptr = cube;
		int i = 0;
		if(word[i] == '1'){
			char zn = '.';
			int j;
			for(j = 1 ;word[j + i] == '*';j++);
			if(j == 2 )
				zn = ',';
			if(j == 3)
				zn = '?';
			cout<<zn;
			if(*(word+i+j))
				this->find(word+i+j);
			return;
		}
		for(i=0;word[i] && word[i] != '1' && word[i] != ' ' && word[i] != '*';i++)
			ptr = ptr->mas[word[i] - 50];
		if(!word[i]){//\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0
			ptr->list->freq += 1;
			cout<<ptr->list->word;
			return;
		}
		if(word[i] == '1'){//11111111111111111111111111111111111111111111111111111111111111111111111111111111111111
			char zn = '.';
			int j;
			for(j = 1 ;word[j + i] == '*';j++);
			if(j == 2 )
				zn = ',';
			if(j == 3)
				zn = '?';
			ptr->list->freq += 1;
			cout<<ptr->list->word<<zn;
			if(*(word+i+j))
				this->find(word+i+j);
			return;
		}
		if(word[i] == '*'){//*****************************************************************************************
			item *curI = ptr->list;
			int j;
			for(j = i ;word[j] && word[j] != ' ' && word[j] != '1';j++)
				curI = curI->next;
			if(!word[j]){//\0\0\0\0\0\0\0
				cout<<curI->word;
				inc(curI,  ptr->list);
				return;
			}
			if(word[j] == '1'){//1111111111111111
				char zn = '.';
				int jj;
				for(jj = 1 ;word[j + jj] == '*';jj++);
				if(jj == 2 )
					zn = ',';
				if(jj == 3)
					zn = '?';
				cout<<curI->word<<zn;
				inc(curI,  ptr->list);
				if(*(word+j+jj))
					this->find(word+j+jj);
				return;
			}
		}

	}
};

int main(){
	unsigned int n;
	cin>>n;
	voc *v = new voc();

	for(unsigned int i=0;i<n;i++){
		char *str = new char[25];
		int freq;
		cin>>str>>freq;
		v->add(str, freq);
	}
	char *p = new char[100];
	while(cin>>p){
		v->find(p);
		while(cin.peek() == ' '){
			cout<<' ';
			cin.ignore(1);
		}
		p = new char[100];
	}
	return 0;
}

