#include <iostream>
//#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdio.h>
//#include <sstream>

using namespace std;

typedef struct
{
  char v[20];
} str_t;

struct mysort//comparator для сортировки
{
	bool operator () ( const pair<string, int> & a, const pair<string, int> & b )
	{
		return (a.second > b.second);
	}
};



char curr[20];
int high;
int low = 0;
str_t trans(char *);
bool with1(char []);
int stars_after(char []);
int stars_before(char []);
char* itoa(int, char *, int);
bool only1(char *);
//////////////////////////////////////////////////////
typedef struct tnode* Tptr; 
typedef struct tnode*& TAptr; 

typedef struct
{
	char prefix[25];
	int len;
}TreeData_t;


typedef struct tnode
{ 
	char alpha; 
	bool isWord; 
	Tptr left, equal, right, revEqual;
	void* data;//указатель на данные произвольного вида
	int ind;//индекс узла
}Tnode; 

class TernaryTree
{
	public:
		TernaryTree();
		~TernaryTree();
		int N_of_nodes();
		
	public:
		void insert(char *s, void* data);
		int getPrefix(char *f, Tptr* retarr, int max);
		Tptr getExactPrefix(char *f);
		void deletePrefix(char *d);
		void display();
		void displayNode();
		void clean();

	private:
		Tptr head;
		int n_of_nodes;
	private:
		Tptr insert(TAptr p, char *s, void* data);
		void display(Tptr n);
		void displayNode(Tptr n);
		void clean(Tptr n);
		Tptr cleanBack(Tptr c);
		void adjustLefthRightNode(Tptr& current);

};

int main()
{
	vector < vector < pair < string, int> > > dict;
	int N = 0;
	char buf [25];
	char word[25];
	TernaryTree tree;
	TreeData_t d[50001];//50000 - максимальное количество слов
	cin >> N;
	dict.resize(N);//инициализация
	cout << N << " ";
	for(int i = 0; i < N ; i++)
	{
		cin >> buf;
		cout << buf << " ";
		d[i].len = 0;
		strcpy(word, buf);
		strcpy(d[i].prefix, trans(buf).v);
		Tptr x = NULL;
		x = tree.getExactPrefix(d[i].prefix);//адрес ключа
		if (!(x))//нет ключа x в дереве
		{
			tree.insert(d[i].prefix, (void*)&d[i]);
			cin >> buf;//считываем частоту
			dict[tree.getExactPrefix(d[i].prefix)->ind - 1].push_back(make_pair(word, atoi(buf)));
			//cout << dict[tree.getExactPrefix(d[i].prefix)->ind - 1].first;
		}
		else// есть ключ x в дереве
		{
			cin >> buf;//считываем частоту
			dict[tree.getExactPrefix(d[i].prefix)->ind - 1].push_back(make_pair(word, atoi(buf)));
		}
		//упорядочиваем dict
		high = dict[tree.getExactPrefix(d[i].prefix)->ind - 1].size() - 1;
		sort(dict[tree.getExactPrefix(d[i].prefix)->ind - 1].begin(), dict[tree.getExactPrefix(d[i].prefix)->ind - 1].end(), mysort());
	}
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	tree.display();
	char q[100002];//последняя строка с запросом
	int index = 0;
	cin.getline(q, 100000);
	while(q[index] != '\0')
		index++;
	q[index] = (char)32;//индикатор последнего слова
	q[index + 1] = '\0';
	int pos = 0;
	int ind = 0;
	while (q[ind] != '\0')//+
	{
		if (q[ind] == (char)32)
		{
			buf[pos] = '\0';//обязательно символ конца строки
			if(buf[0] != '\0')
			{	//обработка запроса
				//вывод слова из словаря
				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				if(!with1(buf))//нет 1 в слове.
				{
					if (stars_before(buf) != 0)//есть звезды, слов несколько
					{
						int j = 0;
						while(isdigit(buf[j])/* != '*' */)
						{
							curr[j] = buf[j];
							j++;
						}
						curr[j] = '\0';
						cout << dict[tree.getExactPrefix(curr)->ind - 1][stars_before(buf)].first;
						dict[tree.getExactPrefix(curr)->ind - 1][stars_before(buf)].second += 1;//обновление частоты встречаемости
						
						pair<string, int> p;
						int b = stars_before(buf);
						int a = tree.getExactPrefix(curr)->ind - 1;
						while((b != 0) && (dict[a][b].second >= dict[a][b - 1].second))
						{
							p.first = dict[a][b].first;
							p.second = dict[a][b].second;
							dict[a][b].first = dict[a][b - 1].first;
							dict[a][b].second = dict[a][b - 1].second;
							dict[a][b - 1].first = p.first;
							dict[a][b - 1].second = p.second;
							b--;
						}
						
					}
					else//нет звезд, значит и слово всего одно.
					{
							cout << dict[tree.getExactPrefix(buf)->ind - 1][0].first;
							dict[tree.getExactPrefix(buf)->ind - 1][0].second += 1;//обновление частоты встречаемости
					} 
				}
				else //есть 1 в слове используем функции stars_before для поиска слова и stars_after для знака препинания
				{
					//добавить обработку слов вида 1**, то есть просто знаков препинания
					if (only1(buf))
					{
						if(stars_after(buf) == 0)
							cout << ".";
						if(stars_after(buf) == 1)
							cout << ",";
						if(stars_after(buf) == 2)
							cout << "?";
					}
					else
					{
						if ((stars_before(buf) == 0))//для слов вида 2341**
						{
							int i = 0;
							while(buf[i] != '1')
							{
								curr[i] = buf[i];
								i++;
							}
							curr[i] = '\0';
							if (stars_after(buf) == 0)
							{
								cout << dict[tree.getExactPrefix(curr)->ind - 1][0].first << ".";
								dict[tree.getExactPrefix(curr)->ind - 1][0].second += 1;
							}
							if (stars_after(buf) == 1)
							{
								cout << dict[tree.getExactPrefix(curr)->ind - 1][0].first << ",";
								dict[tree.getExactPrefix(curr)->ind - 1][0].second += 1;
							}
							if (stars_after(buf) == 2)
							{
								cout << dict[tree.getExactPrefix(curr)->ind - 1][0].first << "?";
								dict[tree.getExactPrefix(curr)->ind - 1][0].second += 1;
							}
						}

						if ((stars_before(buf) != 0))//для слов вида 234**1** или 234**1
						{
							int i = 0;
							while(buf[i] != '*')
							{
								curr[i] = buf[i];
								i++;
							}
							curr[i] = '\0';
							if (stars_after(buf) == 0)
							{
								cout << dict[tree.getExactPrefix(curr)->ind - 1][stars_before(buf)].first << ".";
								dict[tree.getExactPrefix(curr)->ind - 1][stars_before(buf)].second += 1;
								
								pair<string, int> p;
								int b = stars_before(buf);
								int a = tree.getExactPrefix(curr)->ind - 1;
								while((b != 0) && (dict[a][b].second >= dict[a][b - 1].second))
								{
									p.first = dict[a][b].first;
									p.second = dict[a][b].second;
									dict[a][b].first = dict[a][b - 1].first;
									dict[a][b].second = dict[a][b - 1].second;
									dict[a][b - 1].first = p.first;
									dict[a][b - 1].second = p.second;
									b--;
								}
							}
							if (stars_after(buf) == 1)
							{
								cout << dict[tree.getExactPrefix(curr)->ind - 1][stars_before(buf)].first << ",";
								dict[tree.getExactPrefix(curr)->ind - 1][stars_before(buf)].second += 1;
								
								pair<string, int> p;
								int b = stars_before(buf);
								int a = tree.getExactPrefix(curr)->ind - 1;
								while((b != 0) && (dict[a][b].second >= dict[a][b - 1].second))
								{
									p.first = dict[a][b].first;
									p.second = dict[a][b].second;
									dict[a][b].first = dict[a][b - 1].first;
									dict[a][b].second = dict[a][b - 1].second;
									dict[a][b - 1].first = p.first;
									dict[a][b - 1].second = p.second;
									b--;
								}
							}
							if (stars_after(buf) == 2)
							{
								cout << dict[tree.getExactPrefix(curr)->ind - 1][stars_before(buf)].first << "?";
								dict[tree.getExactPrefix(curr)->ind - 1][stars_before(buf)].second += 1;
								
								pair<string, int> p;
								int b = stars_before(buf);
								int a = tree.getExactPrefix(curr)->ind - 1;
								while((b != 0) && (dict[a][b].second >= dict[a][b - 1].second))
								{
									p.first = dict[a][b].first;
									p.second = dict[a][b].second;
									dict[a][b].first = dict[a][b - 1].first;
									dict[a][b].second = dict[a][b - 1].second;
									dict[a][b - 1].first = p.first;
									dict[a][b - 1].second = p.second;
									b--;
								}
							}
						}
					}
				}
				//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

				cout << " ";//пробел между словами
				pos = 0;//обнуляем позицию индекса
				memset(buf, 0, sizeof(buf));//очистка буфера
			}
			else//то есть buf пусто
			{
				cout << " ";//выводим пробел
			}
		}//if symb == (char)32

		else//if symb != (char)32
		{
			buf[pos] = q[ind];
			pos++;
		}
		ind++;//следующий символ строки
	}
	ind = 0;	

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	tree.clean();
	return 0;
}
// TST //////////////////////////////////////////////
TernaryTree::TernaryTree()
{
	head = NULL;
	n_of_nodes = 0;
}


TernaryTree::~TernaryTree()
{
	clean();
}


void TernaryTree::insert(char *s, void* data)
{
	insert(head, s, data);
}

Tptr TernaryTree::insert(TAptr p, char *s, void* data)
{
	if (p == 0) 
	{ 
		p = new Tnode; 
		p->alpha = *s; 
		p->left = p->equal = p->right = p->revEqual= 0;

		if (head == NULL)
			head = p;
	}
	
	if (*s < p->alpha) 
		p->left = insert(p->left, s, data); 
	else if (*s == p->alpha) 
	{ 
		if (*++s != 0)
		{
			p->equal = insert(p->equal, s, data);
			p->equal->revEqual = p;
		}
		else
		{
			p->isWord = true;
			p->data = data;
			n_of_nodes++;
			p->ind = n_of_nodes;//теперь в ind лежит индекс слова
		}
	} 
	else 
		p->right = insert(p->right, s, data); 
	
	return p; 
} 

int TernaryTree::getPrefix(char *f, Tptr* retarr, int max)
{
	if ( max < 1 )
		return 0;

	int ret = 0;
	Tptr p = head;

	if (*f == 0)
		return ret;

	while (*f && p)
	{
		if (ret >= max)
			return max;

		if (*f > p->alpha)
			p = p->right;
		else if (*f < p->alpha)
			p = p->left;
		else
		{
			if (*f++ == p->alpha)
			{
				if (p->isWord == true)
				{
					if (ret<max)
						retarr[ret++] = p;
				}
				p = p->equal;
			}
		}
	}
	return ret;
}

Tptr TernaryTree::getExactPrefix(char *f)
{
	Tptr p = head;

	if (*f == 0)
		return NULL;

	while (*f && p)
	{
		if (*f > p->alpha)
			p = p->right;
		else if (*f < p->alpha)
			p = p->left;
		else
		{
			if (*f++ == p->alpha)
			{
				if (p->isWord == true && *f == 0)
				{
					//cout << "Prefix: " << (char*)((TreeData_t*)p->data)->prefix << " present!. " << (void*)p->data << endl;
					return p;
				}
				p = p->equal;
			}
		}
	}
	return NULL;
}

void TernaryTree::deletePrefix(char *d)
{
	Tptr current = head;
	Tptr currParent = NULL;

	while(*d && current)
	{
		if (*d > current->alpha)
		{
			currParent = current;
			current = current->right;
		}
		else if (*d < current->alpha)
		{
			currParent = current;
			current = current->left;
		}
		else
		{
			if ((current->alpha == *(d++)) && (*d == 0) )
			{
				if (current->isWord == true)
				{
					if ( current->equal )
					{
						current->isWord = false;
					}
					else if ( current->right && !current->left )
					{
						if(currParent)
						{
							if (currParent->equal == current)
							{
								currParent->equal = current->right;
								currParent->equal->revEqual = currParent;
							}
							else if (currParent->right == current)
								currParent->right = current->right;
							else
								currParent->left = current->right;
						}
						else
							head = current->right;
						
						delete current;
						current = NULL;
					}
					else if ( current->left && !current->right )
					{
						if(currParent)
						{
							if (currParent->equal == current)
							{
								currParent->equal = current->left;
								currParent->equal->revEqual = currParent;
							}
							else if (currParent->right == current)
								currParent->right = current->left;
							else
								currParent->left = current->left;
						}
						else
							head = current->left;

						delete current;
						current = NULL;
					}
					else if (  current->right && current->left ) 
					{
						if ( current->left->right )
						{
							adjustLefthRightNode(current);
							if (currParent)
							{
								currParent->equal = current->left;
								currParent->equal->right = current->right;
							}
							else
							{
								head = current->left;
								head->right = current->right;
							}

							delete current;
							current = NULL;
						}
						/*else if ( current->right->left )
						{
							//TODO:its either of above
						}*/
						else
						{
							if (currParent && currParent->equal)
							{
								currParent->equal = current->left;
								currParent->equal->right = current->right;
							}
							else if (currParent && (currParent->left == current))
							{
								currParent->left = current->left;
								currParent->left->right = current->right;
							}
							else if (currParent && (currParent->right == current))
							{
								currParent->right = current->left;
								currParent->right->right = current->right;
							}
							else
							{
								head = current->left;
								head->right = current->right;
							}
							delete current;
							current = NULL;
						}
					}
					else //was only word
					{
						if (currParent && (currParent->left == current))
						{
							currParent->left = NULL;
						}
						else if (currParent && (currParent->right == current))
						{
							currParent->right = NULL;
						}
						else
						{
							if (currParent)
							{
								Tptr cp = cleanBack(current);
								if ( cp && cp->isWord == false)
								{
									if (cp->left)
									{
										if (  cp->left->right && cp->right )
											adjustLefthRightNode(cp);

										Tptr cpLeft = cp->left;

										cp->isWord = cp->left->isWord;
										cp->alpha = cp->left->alpha;
										cp->data = cp->left->data;
										if (cp->left->equal)
										{
											cp->equal = cp->left->equal;
											cp->equal->revEqual = cp;
										}
										if (cp->left->revEqual)
											cp->revEqual = cp->left->revEqual;

										if (cp->left->right)
											cp->right = cp->left->right;

										if (cp->left->left)
											cp->left = cp->left->left;
										else
											cp->left = NULL;

										delete cpLeft;
										cpLeft = NULL;
									}
								}
							}
						}
						delete current;
						if (current == head)
							head = NULL;
						current = NULL;
					}
				}
			}
			else
			{
				currParent = current;
				current = current->equal;
			}
		}
	}
}

void TernaryTree::adjustLefthRightNode(Tptr& current)
{
	Tptr clr = current->left->right; //one to be moved
	Tptr cr = current->right;
	Tptr pcr = NULL; 
	while(cr)
	{
		pcr = cr;
		cr = cr->left;
	}
	pcr->left = clr;
	current->left->right = NULL;
}


Tptr  TernaryTree::cleanBack(Tptr c)
{
	Tptr cp = c->revEqual;
	Tptr cpp = NULL;

	while(cp)
	{
		if (cp->right == NULL && cp->left == NULL && cp->isWord == false)
		{
			cp->equal = NULL;
			cpp = cp->revEqual;
			if (cp == head)
				head = NULL;
			delete cp;
			cp = cpp;
		}
		else
		{
			cp->equal = NULL;
			break;
		}
	}
	return cp;
}


void TernaryTree::display()
{
	display(head);
}


void TernaryTree::display(Tptr n)
{
	if (n == 0)
		return;
	display(n->left);
	if (n && n->isWord)
			cout<<(char*)((TreeData_t*)n->data)->prefix << endl;
	display(n->equal);
	display(n->right);
}


void TernaryTree::displayNode()
{
	displayNode(head);
}


void TernaryTree::displayNode(Tptr n)
{
	if (n == 0)
		return;
	displayNode(n->left);
	if (n)
		cout<<" "<<n->alpha<<endl;
	displayNode(n->equal);
	displayNode(n->right);
}


void TernaryTree::clean()
{
	clean(head);
	head = NULL;
}

void TernaryTree::clean(Tptr n)
{
	if (n == NULL)
		return;
	clean(n->left);
	if (n && n->isWord)
	{
		delete n;
		n = NULL;
	}
	if (n != NULL)
		clean(n->equal);
	if (n != NULL)
		clean(n->right);
}
int TernaryTree::N_of_nodes()
{
	return n_of_nodes;
}
//////////////////////////////////////////

str_t trans(char *ch)
{
	str_t mas;
	for(int i = 0; i < 20; i++)
	{
		{
		if ((ch[i] == 'a') || (ch[i] == 'b') || (ch[i] == 'c'))
			mas.v[i] = '2';
		if ((ch[i] == 'd') || (ch[i] == 'e') || (ch[i] == 'f'))
			mas.v[i] = '3';
		if ((ch[i] == 'g') || (ch[i] == 'h') || (ch[i] == 'i'))
			mas.v[i] = '4';
		if ((ch[i] == 'j') || (ch[i] == 'k') || (ch[i] == 'l'))
			mas.v[i] = '5';
		if ((ch[i] == 'm') || (ch[i] == 'n') || (ch[i] == 'o'))
			mas.v[i] = '6';
		if ((ch[i] == 'p') || (ch[i] == 'q') || (ch[i] == 'r') || (ch[i] == 's'))
			mas.v[i] = '7';
		if ((ch[i] == 't') || (ch[i] == 'u') || (ch[i] == 'v'))
			mas.v[i] = '8';
		if ((ch[i] == 'w') || (ch[i] == 'x') || (ch[i] == 'y') || (ch[i] == 'z'))
			mas.v[i] = '9';
		else if(!isalpha(ch[i]))
			mas.v[i] = '\0';
		}
	}
	return mas;
}

bool with1(char ch[])
{
	int i = 0;
	bool b = false;
	while (ch[i] != 0)
	{
		if (ch[i] == '1') 
			b = true;
		i++;
	}
	return b;
}

int stars_after(char ch[])
{
	int cnt = 0;
	int i = 0;
	bool is1 = false;
	while (ch[i] != 0)
	{
		if (ch[i] == '1')
			is1 = true;
		if ((is1) && (ch[i] == '*'))
			cnt++;
		i++;
	}
	return cnt;
}

int stars_before(char ch[])
{
	int cnt = 0;
	int i = 0;
	bool is1 = false;
	while (ch[i] != 0)
	{
		if (ch[i] == '1')
			is1 = true;
		if ((!is1) && (ch[i] == '*'))
			cnt++;
		i++;	
	}
	return cnt;
}

char* itoa(int value, char* result, int base) 
{
	// check that the base if valid
	if ((base < 2) || (base > 36)) 
	{ 
		*result = '\0'; 
		return result; 
	}

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do 
	{
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) 
		*ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) 
	{
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

bool only1(char* ch)
{	
	bool is_only1 = false;
	if (ch[0] == '1')
		is_only1 = true;
	return is_only1;
}