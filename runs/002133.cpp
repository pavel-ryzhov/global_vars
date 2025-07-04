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

	char eword[1000100];
	char wordstring[20];
	string str;
	unsigned int numb;
	unsigned int r;
	scanf ("%u",&numb);
	dict.resize(20);
	for(unsigned int i=0; i<numb; i++)
	{
		scanf("%s %u", wordstring,&r); 
		str.assign(wordstring);
		node1.raito = r;
		node1.word = str;
		node1.sameraitoorder = 0;
		
		dict[str.length()-1].push_back(node1);
	}
	//fgets(eword,10,stdin);
        //fgets(eword,100100,stdin);
	//inputstring.assign(eword);
	while(!feof(stdin))
	{
		fgets(eword,100100,stdin);
		inputstring.insert(inputstring.length(),eword);
	}
	point.resize(20);
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
			while( str[0]<dict[i][j].word[0] && jj < 7)
			{
				jj++;
				str = keyboard[jj+1][keyboard[jj+1].length() - 1];
				point[i][jj] = j; 
			}		
		}
	}
	return 0;
}
void writeoutput()
{
	printf("%s",outputstring.c_str());
}
int dictsize;
int keynumb;
string button1click(string eword)
{
	if(eword.length() == 1){
		eword.assign(".");	return eword;}
	if(eword.length() == 2){
		eword.assign(",");	return eword;}
	if(eword.length() == 3){
		eword.assign("?");	return eword;}
}
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
		keynumb = eword[i] - '1';
		minword[i] = keyboard[keynumb][0];
		maxword[i] = keyboard[keynumb][keyboard[keynumb].length()-1];
	}
	keynumb = eword[0] - '1';
	dictsize = eword.length()-1;
	for(unsigned short i = point[dictsize][keynumb-1]; i < dict[dictsize].size(); i++)
	{
		int index = 0;
		while( index < maxword.length() )
		{
			if(dict[dictsize][i].word[index] >= minword[index] && dict[dictsize][i].word[index] <= maxword[index])
				index++;
			else break;
		}
		if(index == maxword.length())
			localdict.push_back(dict[dictsize][i]);
		if(dict[dictsize][i].word > maxword)
			break;
	}
	return starsnumb;
}
void updateraito(string wordnew,unsigned short raito)
{
	for(unsigned short i = point[dictsize][keynumb-1]; i < dict[dictsize].size(); i++)
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
	string encodeword;
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
			encodeword = inputstring.substr(0, i+1);
			inputstring = inputstring.substr(i+1, inputstring.length()-i+1);
			outputstring.insert(outputstring.length(),button1click(encodeword));
		}else if(inputstring[0] >'1' && inputstring[0] <= '9')
		{
			int i = 0;
			while((inputstring[i+1] >'1' && inputstring[i+1] <= '9')||(inputstring[i+1] == '*'))
				i++;
			encodeword = inputstring.substr(0, i+1);
			inputstring = inputstring.substr(i+1, inputstring.length()-i+1);
			outputstring.insert(outputstring.length(),chooseword(buildlocaldict(encodeword)));
		}else if(inputstring[0] < 32)
		{
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

