#include <iostream>
using namespace std;
class voc{
private:
	struct item{
		char *word;
		int freq;
		item *next;
	};

	struct olap{
		olap *mas[8];
		item *list;
		olap(){
			for(int i=0; i<8; i++)
				mas[i] = NULL;
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
		item *curI = first->next, *prevI = first;
		do{
			if(curI == elt){
				prevI->next = curI->next;
				break;
			}
			prevI = curI;
			curI = curI->next;
		}while(curI);
		if(first->freq <= elt->freq){
			item *ptrI = new item;
			ptrI->word = first->word;
			ptrI->freq = first->freq;
			ptrI->next = first->next;
			first->word = elt->word;
			first->freq = elt->freq;
			first->next = ptrI;
			delete elt;
			return;
		}
		curI = first->next;
		prevI = first;
		do{
			if(curI == NULL || curI->freq <= elt->freq){
				prevI->next = elt;
				elt->next = curI;
				return;
			}
			prevI = curI;
			curI = curI->next;
		}while(1);
	}
public:
	voc(){
		cube = new olap();
	}

	int add(char *word, int freq){
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
			return 1;
		}
		if(ptr->list->freq < freq){
			item *ptrI = new item;
			ptrI->word = word;
			ptrI->freq = freq;
			ptrI->next = ptr->list;
			ptr->list = ptrI;
			return 1;
		}
		item *curI = ptr->list->next, *prevI = ptr->list;
		
		do{
			if(curI == NULL || curI->freq < freq){
				item *ptrI = new item;
				ptrI->word = word;
				ptrI->freq = freq;
				ptrI->next = curI;
				prevI->next = ptrI;
				return 1;
			}
			prevI = curI;
			curI = curI->next;
		}while(1);
	}



	void find(char word[]){
		olap *ptr = cube;
		int i = 0;
		if(word[i] == '1'){
			char zn = '.';
			int j;
			for(j = 1 ;word[j + i] == '*';j++);
				if(j == 1)
					zn = '.';
				else 
					if(j == 2 )
						zn = ',';
					else
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
	/*	if(word[i] == ' '){//--------------------------------------------------------------------------------------
			ptr->list->freq += 1;
			cout<<ptr->list->word<<' ';
			return;
		}*/
		if(word[i] == '1'){//11111111111111111111111111111111111111111111111111111111111111111111111111111111111111
			char zn = '.';
			int j;
			for(j = 1 ;word[j + i] == '*';j++);
				if(j == 1)
					zn = '.';
				else 
					if(j == 2 )
						zn = ',';
					else
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
	/*		if(word[i] == ' '){//-------------
				inc(curI,  ptr->list);
				cout<<curI->word<<' ';
				return;
			}*/
			if(word[j] == '1'){//1111111111111111
				char zn = '.';
				int jj;
				for(jj = 1 ;word[j + jj] == '*';jj++);
					if(jj == 1)
						zn = '.';
					else 
						if(jj == 2 )
							zn = ',';
						else
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

