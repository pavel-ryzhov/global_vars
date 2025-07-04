#include <stdio.h>
#include <vector>
#include <string>


using namespace std;

struct Node
{
	string word;
	unsigned short raito;
	unsigned char sameraitoorder;
};
Node node1;
vector< vector <Node> >	dict;
vector< vector<unsigned short> > point;
vector<Node>localdict;
vector<string>keyboard;
string minword, maxword;
string inputstring,outputstring;

int readinput()
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

	char eword[100000];
	char wordstring[20];
	string str;
	unsigned int n;
	unsigned int r;
	scanf ("%u",&n);
	dict.resize(21);
	for(unsigned int i=0; i<n; i++)
	{
		scanf("%s %u", wordstring,&r); 
		str.assign(wordstring);
		node1.raito = r;
		node1.word = str;
		node1.sameraitoorder = 0;
		
		dict[str.length()-1].push_back(node1);
	}
	node1.word = '.';
	node1.raito = 1;
	node1.sameraitoorder = 0;
	dict[20].push_back(node1);
	node1.word = ',';
	node1.sameraitoorder = 1;
	dict[20].push_back(node1);
	node1.word = '?';
	node1.sameraitoorder = 2;
	dict[20].push_back(node1);
	gets(eword);  
	gets(eword);
	inputstring.assign(eword);
	
	point.resize(21);
	int jj=0;
	for(int i = 0; i< 20; i++)
	{
		point[i].resize(8);
		jj = 0;
		str = keyboard[jj+1][keyboard[jj+1].length() - 1];
		for(int j = 0; j < dict[i].size(); j ++)
		{
			if(jj > 7)
				break;
			while( str[0]< dict[i][j].word[0] && jj < 7)
			{
				jj++;
				str = keyboard[jj+1][keyboard[jj+1].length() - 1];
			}
			point[i][jj] = j; 
		}
	}
	point[20].resize(8);
	return 0;
}
void writeoutput()
{
	printf("%s",outputstring.c_str());
}
int dictsize;
int n;
int buildlocaldict(string eword)
{
	
	int letters,starsnumb = 0;
	letters = eword.find_first_of('*');
	if(letters != -1)
	{
		starsnumb = eword.length() - letters;
		eword.resize(letters);
	}
	minword.resize(eword.length());
	maxword.resize(eword.length());
	localdict.resize(0);
	
	for(unsigned short i = 0;i < eword.length(); i++)
	{
		n = eword[i] - '1';
		minword[i] = keyboard[n][0];
		maxword[i] = keyboard[n][keyboard[n].length()-1];
	}
	n = eword[0] - '1';
	if(eword == "1") dictsize = 20;
	else dictsize = eword.length()-1;
	for(unsigned short i = point[dictsize][n]; i < dict[dictsize].size(); i++)
	{
		if(dict[dictsize][i].word >= minword && dict[dictsize][i].word <= maxword) 		
			localdict.push_back(dict[dictsize][i]);
		if(dict[dictsize][i].word > maxword)
			break;
	}
	return starsnumb;
}
void updateraito(string wordnew,unsigned short raito)
{
	for(unsigned short i = point[dictsize][n]; i < dict[dictsize].size(); i++)
	{
		
		if(dict[dictsize][i].word>=minword && dict[dictsize][i].word<=maxword)
		{
			if(dict[dictsize][i].raito == raito)
				dict[dictsize][i].sameraitoorder++;
			if(wordnew == dict[dictsize][i].word)
			{
				dict[dictsize][i].raito ++;
				dict[dictsize][i].sameraitoorder = 0;
			}
		}
		if(dict[dictsize][i].word > maxword)
			break;
	}
}
string chooseword(unsigned short starsnumb)
{
	Node tempnode;
	for(unsigned short i = 0; i < localdict.size(); i++)
	{
		for(unsigned short j = 1; j < localdict.size(); j++)
		{
			if((localdict[j].raito > localdict[j-1].raito)||(localdict[j].raito == localdict[j-1].raito &&
				localdict[j].sameraitoorder < localdict[j-1].sameraitoorder))
			{
				tempnode = localdict[j-1];
				localdict[j-1] = localdict[j];
				localdict[j] = tempnode;
			}
		}
	}
	updateraito(localdict[starsnumb].word, localdict[starsnumb].raito+1 );
	return localdict[starsnumb].word;
}

void buildmessage()
{
	
	int meet1, meetSpace, meetWord; 
	string encodeword;
	outputstring.resize(0);
	while(inputstring.empty() != true)
	{
		meet1 = inputstring.find_first_of('1');
		meetSpace = inputstring.find_first_of(' ');
		if((meet1 > meetSpace && meetSpace != -1 && meet1 != -1)||(meet1 == -1 && meetSpace != -1))
			meetWord = meetSpace;
		else if((meet1 < meetSpace) && (meet1 != -1 && meet1 > 0)||(meet1 > 0 && meetSpace == -1))
			meetWord = meet1;
			else meetWord = inputstring.size();
		
		encodeword = inputstring.substr(0, meetWord); 
		inputstring = inputstring.substr(meetWord, inputstring.length()-meetWord);
		if(meetSpace != 0)
			outputstring.insert(outputstring.length(),chooseword(buildlocaldict(encodeword)));
		else
		{
			outputstring.insert(outputstring.end(),' ');
			inputstring = inputstring.substr(1, inputstring.length()-1);
		}
	}
}

int main()
{
	readinput();
	buildmessage();
	writeoutput();
	return 0;
}

