#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

class Word
{
	string str;
	int priority;
public:
	Word(){}
	Word(string str,int p):str(str),priority(p){}
	string GetWord() {return str;}
	int GetPrior() {return priority;}
	void SetPrior(int n){ priority=n;} 
	void PriorUp(){ priority++;} 
	bool operator>(const Word w) const
	{
		return priority<w.priority;
	}
	bool operator<(const Word w) const
	{
		return priority>w.priority;
	}
	bool operator!=(Word w)
	{
		return priority!=w.priority;
	}
};

class Tree
{
	class Node 
	{
	public: 
		deque<Word> words;	
		stack<Word> Swords;
		int N;
		Node **leaf;
		Node()
		{
			leaf=new Node*[9]; 
			for(int i=0;i<9;i++)
				leaf[i]=NULL;
		}
		~Node() 
		{ 
			for(int i=0;i<9;i++)
				delete leaf[i];
			delete []leaf;
		}
	};
	Node *root;
	Node *curent_leaft;
public:
	Tree()
	{
		root = new Node();
		root->N=-1;
		curent_leaft=root;
	}
	~Tree() {delete root;}

	void Digits(string s,vector<int> &D)
	{
		char *key[9]=
		{".,?" , "abc" , "def",		  // 1 2 3
		"ghi" , "jkl" , "mno",		  // 4 5 6	
		"pqrs", "tuv" , "wxyz"};	  // 7 8 9	
		for(int n=0;n<s.length();n++)
			for (int i=0;i<9;i++)
			{
				for(int j=0;j<3;j++)
				{
					if(key[i][j]==s[n])
						D.push_back(i+1);
				}
			}
	}
	void show()
	{
		cout<<"{ "<<endl;
		for(deque<Word>::iterator i=curent_leaft->words.begin();i!=curent_leaft->words.end();++i)
		{
			cout<<(*i).GetWord()<<" p:"<<(*i).GetPrior()<<endl;
		}
		cout<<"}"<<endl;
	}

	void GotoWord(int n)
	{
		Node *p=curent_leaft;

		p = p->leaf[ n ];
		if( p == NULL ) throw "no word";

		curent_leaft=p;	
	}
	void Next()
	{
		if(curent_leaft->N == -1) return;
		curent_leaft->Swords.push( curent_leaft->words.front() );
		curent_leaft->words.pop_front();
	}

	string GetWort()
	{
		string temp;

		Word wd = curent_leaft->words.front();
		temp=wd.GetWord();
		curent_leaft->words.pop_front();
		wd.PriorUp();

		while(!curent_leaft->Swords.empty())
		{
			curent_leaft->words.push_front(curent_leaft->Swords.top());
			curent_leaft->Swords.pop();
		}
		curent_leaft->words.push_front(wd);
		sort(curent_leaft->words.begin(),curent_leaft->words.end());
		curent_leaft=root;
		return temp;
	}

	void Insert( Word w)
	{
		Node *p=root;
		vector<int> num;
		Digits(w.GetWord(),num);
		for(vector<int>::iterator i=num.begin();i!=num.end();++i)
		{
			if( p->leaf[*i] == NULL )
			{
				p->leaf[*i] = new Node();
				p->leaf[*i]->N = *i;
			}	
			p=p->leaf[*i];
		}	
		p->words.push_back(w);
		sort(p->words.begin(),p->words.end());
	}
};

class T9
{
	int N;	//Количество строк
public:
	Tree tree;
	T9()
	{
		cin>>N;
		for (int i=0;i<N;i++)
		{
			int p;
			string str;
			cin>>str>>p;
			tree.Insert( Word(str,p));
		}		
		tree.Insert( Word(",",2));
		tree.Insert( Word("?",1));
		tree.Insert( Word(".",3));

		vector<int> n;
		getchar();
		char ch=0;
		while(ch!=10)
		{
			ch=getchar();
			if( ch==32 ) n.push_back(-2);
			else if( ch=='*' ) n.push_back(-1);
			else n.push_back( atoi(&ch) );
		}

		string temp;
		for(int i=0;i<n.size()-1;i++)
		{
			switch(n[i])
			{
			case -2:// ' '
				{
					temp=tree.GetWort();
					cout<<temp<<" ";
				}
				break;
			case -1://*
				{
					tree.Next();
				}
				break;
			case 1: 
				{
					temp=tree.GetWort();
					cout<<temp;
					tree.GotoWord( 1 );
				}
				break;
			default:
				{
					tree.GotoWord( n[i] );
				}
				break;
			}
		}	
		temp=tree.GetWort();
		cout<<temp;
	/**/
	}
};

int main(int argc, char *argv[])
{
	try
	{
		while(true)
		{
			T9 t;
			cout<<endl;
		}
	}
	catch (char* badnews)
	{
		cout<<"Error "<<badnews<<endl;
	}
	return 0;
}