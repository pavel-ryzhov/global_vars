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

struct mysort//comparator ��� ����������
{
	bool operator () ( const pair<string, int> & a, const pair<string, int> & b )
	{
		return (a.second > b.second);//������������� �� ��������
	}
};

struct mysorts//comparator ��� ���������� �� ������
{
	bool operator () ( const pair<string, int> & a, const pair<string, int> & b )
	{
		char cha[25], chb[25];
		for(int i = 0; i < 25; i++)
		{
			cha[i] = a.first[i];
			chb[i] = b.first[i];
		}
		cha[24] = '\0';
		chb[24] = '\0';
		return (strcmp(cha, chb) < 0);//������������� �� �����������
	}
};

vector < vector < pair < string, int> > > dict;
vector <string> subs;

char curr[20];
int high;
int low = 0;
str_t trans(char *);
bool with1(char []);
int stars_after(char []);
int stars_before(char []);
char* itoa(int, char *, int);
bool only1(char *);
int howmuch1(char *);
//////////////////////////////////////////////////////
typedef struct tnode* Tptr; 
typedef struct tnode*& TAptr; 

typedef struct//�������� �� vector<pair>
{
	char prefix[25];
	int len;
}TreeData_t;


typedef struct tnode
{ 
	char alpha; 
	bool isWord; 
	Tptr left, equal, right, revEqual;
	void* data;//��������� �� ������ ������������� ����
	int ind;//������ ����
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
	int N = 0;
	char buf [25];
	char word[25];
	int bufs = 0;//���������� ���� � ������ q
	TernaryTree tree;
	TreeData_t d[50001];//50000 - ������������ ���������� ����
	cin >> N;
	dict.resize(N);//�������������
	for(int i = 0; i < N ; i++)
	{
		cin >> buf;
		d[i].len = 0;
		strcpy(word, buf);
		strcpy(d[i].prefix, trans(buf).v);
		Tptr x = NULL;
		x = tree.getExactPrefix(d[i].prefix);//����� �����
		if (!(x))//��� ����� x � ������
		{
			tree.insert(d[i].prefix, (void*)&d[i]);
			cin >> buf;//��������� �������	
			dict[tree.getExactPrefix(d[i].prefix)->ind - 1].push_back(make_pair(word, atoi(buf)));
		}
		else// ���� ���� x � ������
		{
			cin >> buf;//��������� �������
			dict[tree.getExactPrefix(d[i].prefix)->ind - 1].push_back(make_pair(word, atoi(buf)));
		}
		//������������� dict �� �������
		high = dict[tree.getExactPrefix(d[i].prefix)->ind - 1].size() - 1;
		sort(dict[tree.getExactPrefix(d[i].prefix)->ind - 1].begin(), dict[tree.getExactPrefix(d[i].prefix)->ind - 1].end(), mysort());//���� �� �������
		int pos = 0;
		int a = 0;
		//������������� dict �� ������
		for(vector<pair<string, int> >::iterator itda = dict[tree.getExactPrefix(d[i].prefix)->ind - 1].begin(); itda != dict[tree.getExactPrefix(d[i].prefix)->ind - 1].end(); ++itda)
		{
			if(itda->second == (itda+1)->second)
			{
				//cout << itda->second << " = " << (itda + 1)->second << endl;
				pos++;
				a++;
			}
			else
			{
				//cout << itda->second << " <> " << (itda + 1)->second << " a = " << a << endl;
				sort(itda - a, itda + 1, mysorts());
				pos++;
				a = 0;
			}
		}
	}

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	cin.get();//
	char q[100002];//��������� ������ � ��������
	string qst;
	int index = 0;
	cin.getline(q, 100000);
	while(q[index] != '\0')
		index++;
	q[index] = (char)32;//��������� ���������� �����
	q[index + 1] = '\0';
	int pos = 0;
	int ind = 0;
	int z = 0;
	//��������� �������
	//���������� ����� buf � ������ q
	while(q[z] != '\0')
	{	
		if(q[z] == (char)32)
			bufs++;
		z++;
	}
	subs.resize(bufs);//������������ subs
	while (q[ind] != '\0')
	{
		if (q[ind] == (char)32)
		{
			buf[pos] = '\0';//����������� ������ ����� ������
			if(buf[0] != '\0')
			{
				//�������� buf �� subs
				int k = 0;
				int a = 0, b = 0;
				int n = 0;
				char sub[25];
				while(buf[k] != 0)
				{
					//cout << "buf = " << buf << endl;
					if( ((buf[k] == '1') && (isdigit(buf[k + 1])) && (buf[k + 1] != '1')) ||
						((buf[k] == '*') && (isdigit(buf[k + 1]))) ||
						((isdigit(buf[k])) && (buf[k] != '1') && (buf[k + 1] == '1')) ||
						((isdigit(buf[k])) && (buf[k + 1] == 0 )) ||
						((buf[k] == '*') && (buf[k + 1] == 0)) ||
						((buf[k] == '1') && (buf[k + 1] == '1')) )
					{
						b = k;
						//cout << "b = " << b << " a = " << a << " n = " << b - a + 1 << endl;
						n = b - a + 1;
						for(int j = 0; j < n; j++)
						{
							sub[j] = buf[j + a];
							//cout << buf[j + a] << endl;
						}
						sub[n] = '\0';
						//cout << sub;

						//����� ����� �� �������
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

						if (stars_before(sub) != 0)//���� ������, ���� ���������
						{
							int j = 0;
							while(isdigit(sub[j])/* != '*' */)
							{
								curr[j] = sub[j];
								j++;
							}
							curr[j] = '\0';
							cout << dict[tree.getExactPrefix(curr)->ind - 1][stars_before(sub)].first;
							dict[tree.getExactPrefix(curr)->ind - 1][stars_before(sub)].second += 1;//���������� ������� �������������
							
							pair<string, int> p;
							int b = stars_before(sub);
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
						else//��� �����, ������ � ����� ����� ����. ��� �� ��������� � ����� ����������, ��� ��� ��� ��� sb = 0
						{
							if(sub[0] == '1')//���� ����������
							{
								if(stars_after(sub) == 0)
									cout << '.';
								else if(stars_after(sub) == 1)
									cout << ',';
								else if(stars_after(sub) > 1)
									cout << '?';
							}
							else//�����
							{
								cout << dict[tree.getExactPrefix(sub)->ind - 1][0].first;
								dict[tree.getExactPrefix(sub)->ind - 1][0].second += 1;//���������� ������� �������������	
							}	
						}
						

						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

						//subs.push_back(sub);
						memset(sub, 0, sizeof(sub));
						index = 0;
						a = b + 1;
						k++;
					}
					else
						k++;		
				}
				{

				}
				
				cout << " ";//������ ����� �������
				pos = 0;//�������� ������� �������
				memset(buf, 0, sizeof(buf));
			}
			else//�� ���� buf �����
			{
				cout << " ";//������� ������
			}
		}//if symb == (char)32
		else//if symb != (char)32
		{
			buf[pos] = q[ind];
			pos++;
		}
		ind++;//��������� ������ ������
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
			p->ind = n_of_nodes;//������ � ind ����� ������ �����
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
			cout << (char*)((TreeData_t*)n->data)->prefix << endl;
			//foutd<<(char*)((TreeData_t*)n->data)->prefix << endl;
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

int howmuch1(char* ch)
{
	int ones = 0;
	int i = 0;
	while(ch[i] != 0)
	{
		if(ch[i] == '1')
		{
			ones++;
		}
			i++;
	}
	return ones;
}