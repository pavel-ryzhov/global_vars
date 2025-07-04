#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

vector<string>keyboard;

char char_to_numb(char a)
{
	if(a < 'd') return '2';
	if(a < 'g') return '3';
	if(a < 'j') return '4';
	if(a < 'm') return '5';
	if(a < 'p') return '6';
	if(a < 't') return '7';
	if(a < 'w') return '8';
	else  return '9';
}
string inputstring,outputstring;

struct Node
{
	string word;
	unsigned short raito;
};
Node node;

class Tree
{
private:
	vector<Node> data;
	char Symbol;
	Tree * perent;
	vector<Tree> children;
public:
	vector<char> link;
	Tree(){ perent = NULL; Symbol = 0; link.assign(8,-1); };
	Tree( char S )
	{ 
		perent = this; 
		Symbol = S;
		link.assign(8,-1);
	};
	void add_data(Node);
	void add_children(Tree);
	void set_patern(Tree *);
	Tree * find_chield(string);
	string select_word(string,short);
} Dictionary ,*tempTree;
void Tree::add_data(Node n)
{
	this->data.push_back(n);
	for(int i = this->data.size()-1; i > 0; i--)
	{
		Node temp;
		if(this->data[i].raito > this->data[i-1].raito)
		{
			temp = this->data[i];
			this->data[i] = this->data[i-1];
			this->data[i-1] = temp;
		}else break;
	}
}
void Tree::add_children(Tree t)
{
	this->children.push_back(t);
}
void Tree::set_patern(Tree *t)
{
	this->perent = t;
}

Tree * Tree::find_chield(string str)
{
	if(str.length() == 0)
		return this;
	char a = char_to_numb(str[0]);
	if(link[a-'2']!=-1)
		return this->children[link[a-'2']].find_chield(str.substr(1,str.length() - 1));

	this->link[a-'2']=this->children.size();
	this->add_children( a );
	return this->children[this->children.size()-1].find_chield(str.substr(1,str.length() - 1));
}
string Tree::select_word(string eword,short star)
{
	if(eword.length() == 0)
	{
		this->data[star].raito++;
		for(int i = star; i > 0; i--)
		{
			Node temp;
			if(this->data[i].raito >= this->data[i-1].raito)
			{
				temp = this->data[i];
				this->data[i] = this->data[i-1];
				this->data[i-1] = temp;
				star--;
			}else break;
		}
		return this->data[star].word;
	}
	return this->children[ link[eword[0]-'2'] ].select_word(eword.substr(1,eword.length() - 1),star);

}

void readinput()
{
	keyboard.resize(9);
	keyboard[0] = ",.?";
	keyboard[1] = "abc";
	keyboard[2] = "def";
	keyboard[3] = "ghi";
	keyboard[4] = "jkl";
	keyboard[5] = "mno";
	keyboard[6] = "pqrs";
	keyboard[7] = "tuv";
	keyboard[8] = "wxyz";

	char eword[100002];
	char wordstring[20];
	string str;
	unsigned int numb;
	unsigned int r;
	fscanf (stdin,"%u",&numb);
	for(unsigned int i=0; i<numb; i++)
	{
		fscanf(stdin,"%s %u", wordstring,&r); 
		str.assign(wordstring);
		node.raito = r;
		node.word = str;
		tempTree = Dictionary.find_chield(str);
		tempTree->add_data(node);
	}
	char c;
	c = fgetc(stdin);
	
	while(true)
	{
		fgets(eword,100001,stdin);
		if(feof(stdin))
			break;
		inputstring.insert(inputstring.length(),eword);
	}
}
string button1click(string eword)
{
	if(eword.length() == 1){
		eword.assign(".");	return eword;}
	if(eword.length() == 2){
		eword.assign(",");	return eword;}
	if(eword.length() == 3){
		eword.assign("?");	return eword;}
}
void buildmessage()
{
	outputstring.resize(0);
	while(inputstring.empty() != true)
	{
		if(inputstring[0] == ' ')
		{
			outputstring.insert(outputstring.end(),' ');
			inputstring = inputstring.substr(1, inputstring.length()-1);
		}else if(inputstring[0] == '1')
		{
			int i = 0;
			while(inputstring[i+1] == '*')
				i++;
			outputstring.insert(outputstring.length(),button1click(inputstring.substr(0, i+1)));
			inputstring = inputstring.substr(i+1, inputstring.length()-i+1);
		}else if(inputstring[0] >'1' && inputstring[0] <= '9')
		{
			int i = 0,j;
			while(inputstring[i+1] >'1' && inputstring[i+1] <= '9')
				i++;
			j = i;
			while(inputstring[j+1] == '*')
				j++;
			outputstring.insert(outputstring.length(),Dictionary.select_word(inputstring.substr(0, i+1),j-i));//debug j
			inputstring = inputstring.substr(j+1, inputstring.length()-j+1);	
		}else if(inputstring[0] < 32)
		{
			inputstring = inputstring.substr(1, inputstring.length()-1);
		}
	}
}
void writeoutput()
{
	fprintf(stdout,"%s",outputstring.c_str());
}
int main()
{
	readinput();
	buildmessage();
	writeoutput();
	return 0;
}
