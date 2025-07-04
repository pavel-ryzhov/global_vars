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

typedef struct tnode* Tptr; 
typedef struct tnode*& TAptr; 

typedef struct//заменить на vector<pair>
{
	char prefix[20];
	int len;
}TreeData_t;


typedef struct tnode
{ 
	char alpha; 
	bool isWord; 
	Tptr left, equal, right, revEqual;
	void* data;
}Tnode; 

class TernaryTree
{
	public:
		TernaryTree();
		~TernaryTree();

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

	private:
		Tptr insert(TAptr p, char *s, void* data);
		void display(Tptr n);
		void displayNode(Tptr n);
		void clean(Tptr n);
		Tptr cleanBack(Tptr c);
		void adjustLefthRightNode(Tptr& current);

};


ifstream fin;
ofstream fout;
int main(int argc, char** argv)
{
	int N = 0;
	char buf [25];
	fin.open("dictionary.txt");
	fout.open("dictionaryoutt9last.txt");
	TernaryTree tree;

	TreeData_t d[25480] = {0};
	fin >> N;
	//fout << N << endl;
	for(int i = 0; i < 25481; i++)
	{
		fin >> buf;
		//cout << buf << endl;
		d[i].len = 0;
		strcpy(d[i].prefix, buf);
		fout << d[i].prefix << " " << (void*)&d[i] << endl;//норм
		
		tree.insert(d[i].prefix, (void*)&d[i]);
		fin >> buf;//пропускаем частоту пока что
	}
	Tptr nodes[25480] = {NULL};
	/*int ret = tree.getPrefix("aar", (Tptr*)&nodes[3], 5);
	for (int ci = 0; ci < ret; ci++)
		fout << "Matching prefix: " <<(char*)((TreeData_t*)nodes[ci]->data)->prefix << endl;*/

	char findP[20] = "abbreviate";
	Tptr s = NULL;
	s = tree.getExactPrefix(findP);
	if (!s)
		cout << "Prefix: " << findP << " not present!." << endl;
	strcpy(findP, "zygote");
	s = tree.getExactPrefix(findP);
	if (!s)
		cout << "Prefix: " << findP << " not present!." << endl;
	strcpy(findP, "killer");
	s = tree.getExactPrefix(findP);
	if (!s)
		cout << "Prefix: " << findP << " not present!." << endl;
	strcpy(findP, "slayer");
	s = tree.getExactPrefix(findP);
	if (!s)
		cout << "Prefix: " << findP << " not present!." << endl;
	/*char delPre[20] = "abbreviate";
	tree.deletePrefix(delPre);*/
	
	/*tree.display();

	fout << "Nodes:-->" << endl;
	tree.displayNode();*/

	tree.clean();
	/*d[0].len = 9;
	d[1].len = 9;
	d[2].len = 9;
	d[3].len = 9;
	d[4].len = 9;
	strcpy(d[0].prefix, "986");
	strcpy(d[1].prefix, "62");
	strcpy(d[2].prefix, "98");
	strcpy(d[3].prefix, "24");
	strcpy(d[4].prefix, "3");
	
	tree.insert(d[0].prefix, (void*)&d[0]);
	tree.insert(d[1].prefix, (void*)&d[1]);
	tree.insert(d[2].prefix, (void*)&d[2]);
	tree.insert(d[3].prefix, (void*)&d[3]);
	tree.insert(d[4].prefix, (void*)&d[4]);

	Tptr nodes[5] = {NULL};
	int ret = tree.getPrefix("986", (Tptr*)&nodes[0], 5);
	for (int ci = 0; ci<ret; ci++)
		cout<<"Matching prefix: "<<(char*)((TreeData_t*)nodes[ci]->data)->prefix<<endl;

	char findP[20] = "62";
	Tptr s = NULL;
	s = tree.getExactPrefix(findP);
	if (!s)
		cout<<"Prefix: "<<findP<<" not present!."<<endl;

	char delPre[20] = "62";
	tree.deletePrefix(delPre);
	
	tree.display();

	cout<<"Nodes:-->"<<endl;
	tree.displayNode();

	tree.clean();*/

	fin.close();
	fout.close();
	cin.get();
	cin.get();
	return 0;
}

TernaryTree::TernaryTree()
{
	head = NULL;
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
		}
	} 
	else 
		p->right = insert(p->right, s, data); 
	
	return p; 
} 


/* Get all matching prefixes */
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

/*Get the exact prefix/key*/
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
					cout << "Prefix: " << (char*)((TreeData_t*)p->data)->prefix<<" present!. " << &p->data << endl;
					return p;
				}
				p = p->equal;
			}
		}
	}
	return NULL;
}


/*Delete a key from the tree*/
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
			cout<<" "<<(char*)((TreeData_t*)n->data)->prefix<<endl;
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