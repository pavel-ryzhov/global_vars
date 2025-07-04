#include "string.h"
#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class T9
{
public:
	int WordNum;
	vector<string> Words;
	vector<int> Freqs;
	string Sequence;
	string Printed;
	string SpaceBuffer; //to preserve the exact number of spaces the user printed

	vector<vector<char> > Keyboard;

	vector<int> SuitableF;
	vector<int> PositionInWords;
	vector<int> BasicPositions;

	T9();
	~T9();
	void Create();
	void FillKeyboard();
	void MarkSuitableLetter(int Key, int Pos, int len);
	void MarkSuitableWord(int Pos1, int Pos2);
	void FindWord(int stars);
	void BiteOutWords();
	void SortSymbol(int stars);
	int MoveDigits(int Pos);
	vector<int> MoveWordStars(int Pos);
	int MoveSymbolStars(int Pos);
	
};

T9::T9(){}
T9::~T9(){}

void T9::FillKeyboard()
{
	vector<char> v1;
	v1.push_back('.');
	v1.push_back(',');
	v1.push_back('?');
	vector<char> v2;
	v2.push_back('a');
	v2.push_back('b');
	v2.push_back('c');
	vector<char> v3;
	v3.push_back('d');
	v3.push_back('e');
	v3.push_back('f');
	vector<char> v4;
	v4.push_back('g');
	v4.push_back('h');
	v4.push_back('i');
	vector<char> v5;
	v5.push_back('j');
	v5.push_back('k');
	v5.push_back('l');
	vector<char> v6;
	v6.push_back('m');
	v6.push_back('n');
	v6.push_back('o');
	vector<char> v7;
	v7.push_back('p');
	v7.push_back('q');
	v7.push_back('r');
	v7.push_back('s');
	vector<char> v8;
	v8.push_back('t');
	v8.push_back('u');
	v8.push_back('v');
	vector<char> v9;
	v9.push_back('w');
	v9.push_back('x');
	v9.push_back('y');
	v9.push_back('z');

	Keyboard.push_back(v1);
	Keyboard.push_back(v2);
	Keyboard.push_back(v3);
	Keyboard.push_back(v4);
	Keyboard.push_back(v5);
	Keyboard.push_back(v6);
	Keyboard.push_back(v7);
	Keyboard.push_back(v8);
	Keyboard.push_back(v9);
	
	
}
void T9::Create()
{
	FillKeyboard();
	
	vector<int>::iterator InsPos;
	char a[21];
	char s[100001];
	int b;

	scanf("%d", &WordNum);

	for(int i=0; i<WordNum; i++)
	{
		scanf("%s", &a);
		scanf("%d\n", &b);

		string t(a);

		for(InsPos=Freqs.begin(); InsPos<Freqs.end(); InsPos++)
		{
			if (*InsPos<b)
				break;
				
		}
		
		Words.insert((Words.begin()+(InsPos-Freqs.begin())), t);
		Freqs.insert(InsPos,b);
	}
		
	fgets(s, 100001, stdin);

	string seq(s);

	Sequence = seq;

	SuitableF=Freqs;
	

	for(int i=0;i<Words.size();i++)
	{
		BasicPositions.push_back(i);
	}

	PositionInWords=BasicPositions;

}

void T9::MarkSuitableLetter(int Key, int Pos, int len)
{
	vector<int>::iterator PosMove;
	vector<char>::iterator KeyMove;
	bool Take = false;
	vector<int> tempFr;
	vector<int> posInWords;
	int Fr=0;

	
	for(PosMove=PositionInWords.begin(); PosMove<PositionInWords.end(); PosMove++)
	{
		if((Words.at(*PosMove)).length()>=Pos+1)
		{
		

		for(KeyMove=Keyboard.at(Key-1).begin(); KeyMove<Keyboard.at(Key-1).end(); KeyMove++)
		{
			if((Words.at(*PosMove)).at(Pos)==*KeyMove&&(Words.at(*PosMove)).length()==len)
			{
				Take=true;
				break;
			}
		}

		}
		
		if (Take)
		{
			Take=false;
			tempFr.push_back(SuitableF.at(PosMove-PositionInWords.begin()));
			posInWords.push_back(PositionInWords.at(PosMove-PositionInWords.begin()));
		
		}
		
	}

	
	SuitableF=tempFr;
	PositionInWords=posInWords;

}

void T9::MarkSuitableWord(int Pos1, int Pos2)
{
	string::iterator Move;
	int i=0;
	int a=0;
	int len = Pos2-Pos1+1;
	
	for(Move = Sequence.begin()+Pos1;Move<=Sequence.begin()+Pos2; Move++)
	{
		string d="";//a clumsy conversion
		d.insert(d.begin(),(*Move));		
		a = atoi(d.c_str());
		MarkSuitableLetter(a,i,len);
		i++;
	}

}

void T9::FindWord(int stars)
{
	string Aux;
	int st = stars%(PositionInWords.size());//the words should cycle; or there'll be error
	string TheWord = Words.at(PositionInWords.at(st));
	Printed.append(TheWord);
	SuitableF.at(st)=SuitableF.at(st)+1;
	int currFreq=SuitableF.at(st);
	int currPos =PositionInWords.at(st);
	vector<int>::iterator Move;
	int prevPos;
	prevPos=PositionInWords.at(st);

	int FreqPos=PositionInWords.at(st);	

	Freqs.at(FreqPos)=Freqs.at(FreqPos)+1;


	vector<int> Auxilary;
	bool needsOrder=false;

	for(Move=SuitableF.begin(); Move<SuitableF.end();Move++)
	{
		if((*Move)==currFreq&&PositionInWords.at(Move-SuitableF.begin())<=currPos)
		{	
			if(PositionInWords.at(Move-SuitableF.begin())!=currPos)
			{
				needsOrder=true;
			}
			Auxilary.push_back(PositionInWords.at(Move-SuitableF.begin()));
			//collected Words positions for suitable words of this frequency,
			//but only before current word in Words - the rest needs no ordering anyway
			
		}
	}
	if(needsOrder)
	{
		prevPos=Auxilary.back();//the last is the word which can be the only one in out-of-order position
		Aux=Words.at(Auxilary.back());
		for(Move=Auxilary.end()-1;Move>Auxilary.begin(); Move--)
		{
			Words.at(*Move)=Words.at(*(Move-1));
		}
		Words.at(Auxilary.front())=Aux;
		TheWord = Words.at(Auxilary.back());
	}

	//done interchange: moved TheWord to head, shifting head..pos(TheWord)-1 one position back.
	//Auxilary stays the same. Only words order in Words changes
	
	for (Move=Freqs.begin()+prevPos; Move>Freqs.begin(); Move--)
	{
		if((*(Move-1))>=currFreq)
				break; //found the word's appropriate position
	}

	int newPos = Move-Freqs.begin();

	if(newPos<prevPos)
	{
		Freqs.insert(Freqs.begin()+newPos,currFreq);
		Words.insert(Words.begin()+newPos, TheWord);
		Freqs.erase(Freqs.begin()+prevPos+1);
		Words.erase(Words.begin()+prevPos+1);
	}
	
	SuitableF=Freqs;
	PositionInWords=BasicPositions;
}

int T9::MoveDigits(int Pos)
{
	string::iterator Move;
	Move=Sequence.begin()+Pos;
	int iterPos= Pos;
	while(Move<Sequence.end()&&isdigit(*Move)&&*Move!='1')
	{
		Move++;
		iterPos++;
	}
	int posEnd=iterPos-1;
	
	return posEnd;
}

vector<int> T9::MoveWordStars(int Pos)
{
	vector<int> Res;
	string::iterator Move;
	Move = Sequence.begin()+Pos;
		int iterPos= Pos;
		int wordstars=0;

	while(Move<Sequence.end()&&(!isdigit(*Move)))
		{	
			if((*Move)=='*')
			{
				wordstars++;
			}
			if((*Move)==' ')
			{
				SpaceBuffer.append(" ");
			}
			Move++;
			iterPos++;
		}
	Res.push_back(wordstars);
	Res.push_back(iterPos);

	return Res;
}

int T9::MoveSymbolStars(int Pos)
{
	string::iterator Move;
	Move = Sequence.begin()+Pos;
	int iterPos= Pos;
	int symstars=0;
	
	while(Move<Sequence.end()&&(!isdigit(*Move)||*Move=='1'))
		{
			if ((*Move)=='1')
			{
				Move++;
				iterPos++;
				while(Move<Sequence.end()&&!isdigit(*Move))
				{
					if((*Move)=='*')
					{
						symstars++;
					}
					if((*Move)==' ')
					{
						SpaceBuffer.append(" ");
					}
					Move++;
					iterPos++;
				}
				SortSymbol(symstars);
				symstars=0;
			}
			else
			{
				if((*Move)==' ')
				{
					Printed.append(" ");
				}
				Move++;
				iterPos++;
			}
		}
	return iterPos;
}

void T9::BiteOutWords()
{ 
	int posBeg=0;
	int posEnd=0;
	int iterPos=0;
	int wordstars=0;
	vector<int> temp; 	

	iterPos=MoveSymbolStars(0);//sorted out the .,? in the beginning(if they were there)
	posBeg=iterPos;		

	while(iterPos<Sequence.length()-1)
	{		
		posEnd=MoveDigits(iterPos);//found the end of the word, iterated through digits
		iterPos=posEnd+1;

		temp = MoveWordStars(iterPos);//found wordstars quantity, iterated through wordstars and ' '
		wordstars = temp.front();
		iterPos=temp.back();
		
		if(iterPos<=Sequence.length()) //processed the word considering its stars
		{
			MarkSuitableWord(posBeg, posEnd);
			FindWord(wordstars);
			Printed.append(SpaceBuffer);
			SpaceBuffer="";
			wordstars=0;			
		}
		
		iterPos = MoveSymbolStars(iterPos); //sorted out the .,? if it was here, iterated through
		posBeg=iterPos; //marked the beginning of the new word		
	}

}

void T9::SortSymbol(int stars)
{   
	string Symbol;
	int st =stars%3;

	switch(st)
	{
		case 0: 
			Symbol=".";
			break;
		case 1:
			Symbol = ",";
			break;
		case 2:
			Symbol="?";
			break;
	}

	Printed.append(Symbol);
	Printed.append(SpaceBuffer);
	SpaceBuffer="";
}


int main()
{
	T9 X;
	X.Create();
	X.BiteOutWords();
	printf("%s\n", X.Printed.c_str());
	
	return 0;
}


