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
#include <stdio.h>
#include <string.h>



using namespace std;



class Word
{
	string str;
	int priority;
public:
	Word(){str="";priority=0;}
	Word(string str,int p):str(str),priority(p){}
	string GetWord() {return str;}
	int GetPrior() {return priority;}
	void SetPrior(int n){ priority=n;} 
	void PriorUp(){ priority++;} 
	bool operator>(const Word &w) const
	{
		return priority<w.priority;
	}
	bool operator<(const Word &w) const
	{
		return priority>w.priority;
	}
	bool operator()(Word a,Word b)
	{
		return a.priority>b.priority;
	}
	bool operator!=(Word &w)
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
		deque<Word>::iterator crent_word;
		int N;
		Node *leaf[9];
		Node(int n)
		{
			N=n;
			//leaf=new Node*[9]; 
			for(int i=0;i<9;i++) leaf[i]=NULL;
		}
		~Node() 
		{ 
			/*for(deque<Word*>::iterator i=words.begin();i!=words.end();++i) 
			delete *i;
			*/
			for(int i=0;i<9;i++)
				if(leaf[i]==NULL) delete leaf[i];
			//delete []leaf;
		}
	};
	Node *root;
	Node *curent_leaft;
public:
	Tree()
	{
		root = new Node(-1);
		curent_leaft=root;
	}
	~Tree() {delete root;}

	void Digits(string s,vector<int> &D)
	{
		char key[9][5]=
		{".,?" , "abc" , "def",		  // 1 2 3
		"ghi" , "jkl" , "mno",		  // 4 5 6	
		"pqrs", "tuv" , "wxyz"};	  // 7 8 9	
		for(int n=0;n<s.length();n++)
			for (int i=0;i<9;i++)
			{
				for(int j=0;j<strlen(key[i]);j++)
				{
					if(key[i][j]==s[n])
						D.push_back(i);
				}
			}
	}

	void GotoWord(int n)
	{
		//cout<<n<<endl;
		n--;
		Node *p=curent_leaft;
		if(p->leaf[n] == NULL) "no leaf";
			p = p->leaf[ n ];
		if( p == NULL ) throw "no word";
		curent_leaft=p;	
		if( curent_leaft->words.size()!=0 )
			curent_leaft->crent_word = curent_leaft->words.begin();
	}
	void Next()
	{
		if(curent_leaft->N == -1) return;
		++curent_leaft->crent_word;
		if(curent_leaft->crent_word == curent_leaft->words.end())
			curent_leaft->crent_word = curent_leaft->words.begin();
	}

	string GetWord()
	{
		string temp="";
		Word wd = *(curent_leaft->crent_word);
		curent_leaft->words.erase(curent_leaft->crent_word);
		curent_leaft->crent_word=curent_leaft->words.begin();
		wd.PriorUp();
		temp = wd.GetWord();
		curent_leaft->words.push_front(wd);
		sort(curent_leaft->words.begin(),curent_leaft->words.end(),Word());

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
				p->leaf[*i] = new Node( (*i) );
			}	
			p=p->leaf[*i];

		}	
		p->words.push_back(w);
		sort(p->words.begin(),p->words.end(),Word());
	}
};

int main()
{
	try
	{
		int N=0;	//Количество строк
		Tree tree;

			cin>>N;
			for (int i=0;i<N;i++)
			{
				int p;
				string str;
				cin>>str>>p;
				tree.Insert( Word(str,p));
			}	

			/**/
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
			string temp="";
			if(n.size()==0) return 0;
			//for(int i=0;i<n.size()-1;i++) cout<<n[i]<<endl;
			for(int i=0;i<n.size()-1;i++)
			{
				//cout<<n[i]<<endl;
				int a=n[i];
				switch(a)
				{
				case -2:// ' '
					{
						temp=tree.GetWord();
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
						temp=tree.GetWord();
						cout<<temp;
						tree.GotoWord( 1 );
					}
					break;
				default:
					{
						//cout<<a<<endl;
						tree.GotoWord( a );
					}
					break;
				}
			}	
			temp=tree.GetWord();
			cout<<temp;
			/**/
	/*	t.tree.Insert( Word("act",1));
		t.tree.Insert( Word("bat",1));	
		t.tree.Insert( Word("cat",1));
		t.tree.GotoWord( 2 );
		t.tree.GotoWord( 2 );
		t.tree.GotoWord( 8 );
		t.tree.Next();
		cout<<t.tree.GetWord()<<" ";
		t.tree.GotoWord( 2 );
		t.tree.GotoWord( 2 );
		t.tree.GotoWord( 8 );
		t.tree.Next();
		t.tree.Next();
		cout<<t.tree.GetWord()<<" ";
		t.tree.GotoWord( 2 );
		t.tree.GotoWord( 2 );
		t.tree.GotoWord( 8 );
		t.tree.Next();
		t.tree.Next();
		cout<<t.tree.GetWord()<<" ";
		t.tree.GotoWord( 2 );
		t.tree.GotoWord( 2 );
		t.tree.GotoWord( 8 );
		t.tree.Next();
		t.tree.Next();
		cout<<t.tree.GetWord()<<" ";
		t.tree.GotoWord( 1 );
		cout<<t.tree.GetWort();
		cout<<endl<<"END"<<endl;
		*/
	}
	catch (char* badnews)
	{
		cout<<"Error "<<badnews<<endl;
	}
	return 0;
}