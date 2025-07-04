#include <stdio.h>
#include <string>
#include <map>
#include <cstdlib>

using namespace std;

class TKey
{
public:
	int freq, pr;
	string val;

	bool operator <(TKey k)
	{
	if (freq>k.freq) return 1;
	if (freq<k.freq) return 0;
	if (pr>k.pr) return 1;
	if (pr<k.pr) return 0;
	if (val<k.val) return 1; //выдаем наименьшую по алфавиту
	return 0;
	}

	bool operator >(TKey k)
	{
	if (freq<k.freq) return 1;
	if (freq>k.freq) return 0;
	if (pr<k.pr) return 1;
	if (pr>k.pr) return 0;
	if (val>k.val) return 1; //выдаем наименьшую по алфавиту
	return 0;
	}

	bool operator ==(TKey k)
	{
		if ((freq==k.freq)&&(pr==k.pr)&&(val==k.val)) return 1;
		else return 0;
	}

};

struct TEl;

typedef TEl* PEl;

struct TEl
{
	TKey key;
	int y;
	PEl l,r;
	int kol; //количество поддеревьев

};

//Инициализация дерева:

PEl Find_stat(PEl root, int num)
{
	int left_kol;
	if ((*root).l==NULL) left_kol=0; else left_kol=(*(*root).l).kol;
	if (root==NULL) return NULL;
	if (left_kol==num-1) return root;
	if (left_kol>num-1) return Find_stat((*root).l, num);
	return Find_stat((*root).r, num-left_kol-1);
}

void Init(PEl* root)
{
	*root=NULL;
}

void Kol_of_childs(PEl p)
{
	if (p==NULL) return;
	(*p).kol=1;
	if ((*p).l!=NULL) (*p).kol+=(*((*p).l)).kol;
	if ((*p).r!=NULL) (*p).kol+=(*((*p).r)).kol;
}

void Split (PEl pt, TKey key, PEl* pl, PEl* pr )
{
	if (pt==NULL)
	{
		*pl=NULL;
		*pr=NULL;
	}
	else if ((*pt).key<key)
	{
		*pl=pt;
		Split((**pl).r, key, &((**pl).r), pr);
	}
	else 
	{
	   *pr=pt;
	   Split((**pr).l, key, pl, &((**pr).l));
	}
	//когда мы разбили дерево на право и лево, надо обновить количество элементов в этих поддеревьях.
	Kol_of_childs(*pr);
	Kol_of_childs(*pl);
}

void Add1 (PEl* p_pointer, PEl* np_pointer)
{

	if (*p_pointer==NULL) 
	*p_pointer=*np_pointer;
	else if ((**np_pointer).y<(**p_pointer).y)
		if ((**np_pointer).key==(**p_pointer).key) return;
		else if (((**np_pointer).key<(**p_pointer).key)) Add1(&((**p_pointer).l),np_pointer);
			 else Add1(&((**p_pointer).r),np_pointer);
	else
	{
		Split(*p_pointer,(**np_pointer).key, &((**np_pointer).l), &((**np_pointer).r));
		*p_pointer=*np_pointer;
	}
	Kol_of_childs(*p_pointer);

}

void Add(PEl* root_pointer, TKey a)
{
	//PEl root=*root_pointer;
	PEl np=new TEl;
	TEl t;
	t.key=a;
	t.y=rand()%50000+1;
	t.l=NULL;
	t.r=NULL;
	*np=t;
	Add1(root_pointer,&np);
	
}

PEl Search(PEl* p, TKey A)
{
	if (*p==NULL) return NULL;
	if (A==(**p).key) return *p;
	if (A<(**p).key) return Search(&((**p).l), A);
	return Search(&((**p).r), A);

}

void Merge(PEl* p, PEl pl, PEl pr)
{
	
	if (pl==NULL) *p=pr;
	else if (pr==NULL) *p=pl;
	else if ((*pl).y<(*pl).y)
	{
		*p=pl;
		Merge(&((**p).r), (**p).r, pr);

	}
	else
	{
		*p=pr;
		Merge(&((**p).l),pl, (**p).l);
	}
	//мы подвесили к p деревья pr и pl, надо бы пересчитать количество деток
	Kol_of_childs(*p);
}

void Delete(PEl* p, TKey A)
{
	if (*p==NULL)
	{
		printf("Нет такого элемента.");
	}
	else if (A==(**p).key) Merge(p,(**p).l, (**p).r);
	else if (A<(**p).key) Delete(&((**p).l), A);
	else Delete(&((**p).r),A);
}


int main()
{
	char s[20];
	string slovo;
	char signs[3];
	signs[0]='.'; signs[1]=','; signs[2]='?';
	char c;
	map <char,char> t9;
	t9['a']='2'; t9['b']='2'; t9['c']='2'; t9['d']='3'; t9['e']='3'; t9['f']='3'; t9['g']='4'; t9['h']='4'; t9['i']='4'; t9['j']='5';
	t9['k']='5'; t9['l']='5'; t9['m']='6'; t9['n']='6'; t9['o']='6'; t9['p']='7'; t9['q']='7'; t9['r']='7'; t9['s']='7'; t9['t']='8'; t9['u']='8';
	t9['v']='8'; t9['w']='9'; t9['x']='9'; t9['y']='9'; t9['z']='9';
	int n,priority;
	map <string,PEl> dictionary;
	map <string,PEl>::iterator it;

	scanf("%d",&n);
	for (int i=0; i<n; i++)
	{
		scanf("%s %d", s, &priority);
		slovo=s;
		string kod_slova="";
		for (int j=0; j<slovo.length(); j++)		
			kod_slova+=t9[slovo[j]];
		TKey k;
		k.freq=priority;
		k.pr=0;
		k.val=slovo;
		it=dictionary.find(kod_slova);
		if (it==dictionary.end()) //у нас нет еще дерева вариантов для этой комбинации
		{
			PEl root=new TEl;
			Init(&root);
			dictionary[kod_slova]=root;
		}
		Add(&(dictionary[kod_slova]),k);
		//printf("%s",kod_slova.c_str());
	}
	scanf("\n");
	slovo="";
	string sost;
	sost="new_group";
	int k_slovo=0, k_sign=0, number=0;
	while (scanf("%c",&c)==1)
	{
		switch (c)
		{
		case ' ':
			if (sost=="typing_word") //мы напечатали слово и потом пробел
			{
				//надо вывести это слово, сохраненное в slovo и изменить его частоту.
				PEl needle=new TEl;
				needle=Find_stat(dictionary[slovo],k_slovo+1);
				printf("%s",(*needle).key.val.c_str());
				Delete(&(dictionary[slovo]),(*needle).key);
				number++;
				(*needle).key.freq++;
				(*needle).key.pr=number;
				Add(&(dictionary[slovo]),(*needle).key); //увеличили частоту, изменили приоритет, добавили снова.
				k_slovo=0;
				slovo="";
				printf(" ");
				sost="new_group"; //переводим в состояние ожидания ввода
			}
			else if (sost=="typing_sign")
			{
				//тут мы печатали знак препинания, надо его вывести
				printf("%c",signs[k_sign]);
				k_sign=0;
				printf(" ");
				sost="new_group";
			}
			else printf(" ");
			break;
		case '1':
			if (sost=="typing_word")
			{
				//выводим слово
				PEl needle=new TEl;
				needle=Find_stat(dictionary[slovo],k_slovo+1);
				printf("%s",(*needle).key.val.c_str());
				Delete(&(dictionary[slovo]),(*needle).key);
				number++;
				(*needle).key.freq++;
				(*needle).key.pr=number;
				Add(&(dictionary[slovo]),(*needle).key); //увеличили частоту, изменили приоритет, добавили снова.
				k_slovo=0;
				slovo="";
				sost="typing_sign";
			}
			else if (sost=="new_group")
			{
				sost="typing_sign";
			}
			else if (sost=="typing_sign")
			{
				printf("%c",signs[k_sign]);
				k_sign=0;

			}
			break;
		case '*':
			
			{
				if (sost=="typing_word") k_slovo++;
				else if (sost=="typing_sign") k_sign++;
			}
			break;
		case '\n':
		{
			if (sost=="typing_word")
			{
				//выводим слово
				PEl needle=new TEl;
				needle=Find_stat(dictionary[slovo],k_slovo+1);
				printf("%s",(*needle).key.val.c_str());
			}
			else if (sost=="typing_sign")
			{
				printf("%c",signs[k_sign]);

			}
		}
		break;
		default:
			{
				slovo+=c;
				sost="typing_word";
			}

		}
	}
	
	return 0;
}