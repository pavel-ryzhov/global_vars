#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct record
{
	string s;
	short r;
};

struct node
{
	node *child[10];
	bool filled;
	unsigned short group;
};

int *T9;
node *Head;
vector<record*> Dict[50000];
unsigned short grp_num;

string Word;
unsigned short Rate;

vector<string> Message;
vector<long> Changes;

void merge(vector<record*> *a, long lb, long split, long ub)
{
	long pos1=lb;
	long pos2=split+1;  

	vector<record*> *temp = new vector<record*>;

	while (pos1 <= split && pos2 <= ub) 
	{
		if (a->at(pos1)->r >= a->at(pos2)->r)
			temp->push_back(a->at(pos1++)); 
		else
			temp->push_back(a->at(pos2++)); 	
	}
	
	while (pos1 <= split)
		temp->push_back(a->at(pos1++));
	while (pos2 <= ub)
		temp->push_back(a->at(pos2++)); 

	for (long i=0; i<ub-lb+1; ++i)
		a->at(lb+i) = temp->at(i);

  delete temp;
}

void msort(vector<record*> *a, long lb, long ub)
{ 
  long split;
  if (lb < ub)
  {
    split = (lb + ub)/2;
    msort(a, lb, split);
    msort(a, split+1, ub);
    merge(a, lb, split, ub); 
  }
}

void init()
{
	grp_num = 0;
	Head = new node();
	T9 = new int ['z'];
	T9['a']=T9['b']=T9['c']=2;
	T9['d']=T9['e']=T9['f']=3;
	T9['g']=T9['h']=T9['i']=4;
	T9['j']=T9['k']=T9['l']=5;
	T9['m']=T9['n']=T9['o']=6;
	T9['p']=T9['q']=T9['r']=T9['s']=7;
	T9['t']=T9['u']=T9['v']=8;
	T9['w']=T9['x']=T9['y']=T9['z']=9;
}

void add_word()
{
	node *cur_node = Head;
	for (unsigned short i=0; i<Word.length(); ++i)
	{
		if (cur_node->child[T9[Word[i]]] == NULL)
			cur_node->child[T9[Word[i]]] = new node();
		cur_node = cur_node->child[T9[Word[i]]];
	}
	if (! cur_node->filled)
	{
		cur_node->filled = true;
		cur_node->group = grp_num;
		++grp_num;
	}
	record *tmp = new record(); tmp->s = Word; tmp->r = Rate;
	Dict[cur_node->group].push_back(tmp);
}

void separate()
{
	bool act = false;

	for (unsigned long i=0; i<Word.length(); ++i)
	{
		switch (Word[i])
		{
		case '*':
			if (act) 
				Changes.back() ++;
			else
				Message.back() = (Message.back() == ".") ? "," : (Message.back() == ",") ? "?" : ".";
		break;
		case ' ':
			Message.push_back(" ");
			Changes.push_back(-1);
			act = false;
		break;
		case '1':
			Message.push_back(".");
			Changes.push_back(-1);
			act = false;
		break;
		default:
			if (!act)
			{
				Message.push_back("");
				Changes.push_back(0);
				act = true;
			}
			Message.back() += Word[i];
		}
	}
}

unsigned short find_word()
{
	node *cur_node = Head;
	for (unsigned short i=0; i<Word.length(); ++i)
		cur_node = cur_node->child[Word[i]-'0'];
	return cur_node->group;
}

int main()
{
	unsigned short N;

	init();

	cin>>N;
	for (unsigned short i=0; i<N; ++i)
	{
		cin>>Word>>Rate;
		add_word();
	}

	for (unsigned short i=0; i<grp_num; ++i)
		msort(&Dict[i], 0, Dict[i].size()-1);

	cin.get();
	getline(cin, Word);
	separate();

	long j; unsigned short p, q; record* t;
	for (unsigned long i=0; i<Message.size(); ++i)
	{
		Word = Message[i];
		if (!(Changes[i]<0))
		{
			p = find_word();
			Message[i] = Dict[p][Changes[i]]->s;
			Dict[p][Changes[i]]->r ++;
			
			q=0;
			while (Dict[p][q]->r > Dict[p][Changes[i]]->r) 
				++q;
			t=Dict[p][Changes[i]];
			for (j=Changes[i]; j>q; --j) 
				Dict[p][j] = Dict[p][j-1];
			Dict[p][q] = t;
		}
		cout<<Message[i];
	}
	cout<<'\n';

	return 0;
}
