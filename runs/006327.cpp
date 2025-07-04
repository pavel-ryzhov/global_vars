#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
typedef char byte;

class word
{
	char* wrd;
	short frequency;
	word* next;
	word();
public:
	word(char*,short);
	word* getnext();
	void setnext(word*);
	short getfreq() const;
	bool operator==(const word& w) const;
	char* getword();
	~word();
};
class node
{
	class link
    {
		node *lnk;
		byte index;
	public:
		link();
		link(node*,byte);
		byte getindex() const;
		node* getnode();
    };
	int w_amount;
	vector <link*> links;
	word* words;
public:
	node();
	node* exist(byte i);
	void newlink(node*,byte ind);
	void addword(char *,short);
	void sortwords();
	char* getword(int);
	node* move(byte);
};

void scaner(node&);
node* nextword(node&,char*,short);
void punct(node&);
void T9(node*);
byte getbuttonnum(char ch);

int main()
{
	node base;
	scaner(base);
	punct(base);
	T9(&base);
	return 0;
}
void scaner(node& base)
{
	int size;
	cin >> size;
	char iword[21];
	short f; 
	for(int i = 0; i < size; i++)
	{
		cin >> iword >> f;
		nextword(base,iword,f);
	}
}
node* nextword(node& base,char* wrd,short f)
{
	byte len = strlen(wrd);
	node* ptr = &base,*tmp;
	for(byte i = 0; i < len; i++)
	{
		byte ind = getbuttonnum(wrd[i]);
		if((tmp=ptr->exist(ind))==NULL)
		{
			node *newn = new node;
			ptr->newlink(newn,ind);
			tmp = newn;
		}
		ptr = tmp;
	}
	char *wrdtosave = new char[len+1];
	strcpy(wrdtosave,wrd);
	ptr->addword(wrdtosave,f);
	return ptr;
}
void punct(node& base)
{
	node *newn = new node;
	base.newlink(newn,1);
	char *p = new char[2];
	strcpy(p,".");
	newn->addword(p,0);
	strcpy(p,",");
	newn->addword(p,0);
	strcpy(p,"?");
	newn->addword(p,0);
}
void T9(node* base)
{
	char ch;
	unsigned int i = 0;
	bool ready = false;
	bool punct = false;
	node* tmp = base;
	cin.get();
	while(cin.get(ch))
	{
		if(ch == '\n')
			break;
		else if(ch=='*')
		{
			i++;
			continue;
		}
		else if(ch==' ')
		{
			punct = false;
			if(ready)
			{
			ready=false;
			cout << tmp->getword(i);
			tmp = base;
			i = 0;
			}
			cout << ' ';
			continue;
		}
		else if(ch=='1')
		{
			punct=true;
			if(ready)
			{
			ready = false;
			cout << tmp->getword(i);
			tmp = base;
			i = 0;
			}
		}
		else if(punct)
		{
			punct = false;
			cout << tmp->getword(i);
			tmp = base;
			i = 0;
		}
		ready = true;
		tmp = tmp->move(ch-'0');
	}
	if(tmp != base)
	{
		cout << tmp->getword(i);
	}
}
byte getbuttonnum(char ch)
{
	switch(ch)
	{
	case '.':
	case ',':
	case '?':
		return 1;
	case 'a':
	case 'b':
	case 'c':
		return 2;
	case 'd':
	case 'e':
	case 'f':
		return 3;
	case 'g':
	case 'h':
	case 'i':
		return 4;
	case 'j':
	case 'k':
	case 'l':
		return 5;
	case 'm':
	case 'n':
	case 'o':
		return 6;
	case 'p':
	case 'q':
	case 'r':
	case 's':
		return 7;
	case 't':
	case 'u':
	case 'v':
		return 8;
	case 'w':
	case 'x':
	case 'y':
	case 'z':
		return 9;
	default:
		return 0; //))
	}
}


node::node()
{
	w_amount = 0;
}
void node::addword(char *wrd,short f)
{
	word *w = new word(wrd,f),*ptr,*tmp=NULL;
	if(w_amount == 0)
	{
		w_amount++;
		words = w;
		return;
	}
	ptr = words;
	for(int i = 0; i < w_amount; i++)
	{
		if(f <= ptr->getfreq())
		{
			tmp = ptr;
			ptr = ptr->getnext();
		}
		else
			break;
	}
	if(tmp!=NULL)
		tmp->setnext(w);
	else
		words = w;
	w->setnext(ptr);
	w_amount++;
}
void node::newlink(node* n,byte ind)
{
	link* l = new link(n,ind);
	links.push_back(l);
}
node* node::exist(byte index)
{
	for(byte i = 0; i < links.size(); i++)
		if(links[i]->getindex()==index)
			return links[i]->getnode();
	return NULL;
}
node* node::move(byte ind)
{
	for(byte i = 0; i < links.size(); i++)
		if(ind == links[i]->getindex())
			return links[i]->getnode();
	return NULL;
}
char* node::getword(int num)
{
	word *ptr=words,*back=NULL;
	for(int i = 0; i < num; i++)
	{
		back = ptr;
		ptr = ptr->getnext();
	}
	char * result = ptr->getword();
	int fr;
	word *tmp=NULL,*ptr2=NULL;
	if((fr=ptr->getfreq())!=0&&back!=NULL)
	{
		ptr2 = words;
		back->setnext(ptr->getnext());
		for(int i = 0; i < w_amount-1; i++)
		{
			if(fr < ptr2->getfreq())
			{
				tmp = ptr2;
				ptr2 = ptr2->getnext();
			}
			else
				break;
		}
		if(tmp!=NULL)
			tmp->setnext(ptr);
		else
			words = ptr;
		ptr->setnext(ptr2);
	}
	return result;
}
node::link::link()
{
	lnk = NULL;
	index = 0;
}
node::link::link(node* n, byte i)
{
	lnk = n;
	index = i;
}
byte node::link::getindex() const
{
	return index;
}
node* node::link::getnode()
{
	return lnk;
}
word* word::getnext()
{
	return next;
}
void word::setnext(word *nxt)
{
	next = nxt;
}
short word::getfreq() const
{
	return frequency;
}
bool word::operator ==(const word& w) const
{
	return (strcmp(wrd,w.wrd)==0&&frequency==w.frequency);
}
char* word::getword()
{
	frequency = frequency==0?0:frequency+1;
	return wrd;
}
word::word(char *w,short f)
{
	wrd = new char[strlen(w)+1];
	strcpy(wrd,w);
	frequency = f;
	next = NULL;
}
word::~word()
{
	delete[]wrd;
}