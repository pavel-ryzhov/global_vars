#include "string.h"
#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class PosFreq
{
public:
	int WordPos;
	int Freq;
	int Priority;
	PosFreq(int wordPos, int freq, int priority){WordPos=wordPos;Freq=freq; Priority=priority;}
	~PosFreq(){}
};

bool moreFrequent(PosFreq a, PosFreq b)
{
	if(a.Freq==b.Freq)
	{
		return(a.Priority>b.Priority);
	}
	else
	{
	return(a.Freq>b.Freq);
	}
}


class T9
{
public:
	int WordNum;
	vector<string> Words;
	vector<int> Freqs;
	vector<int> Priority;
	string Sequence;
	string Printed;
	string SpaceBuffer; //to preserve the exact number of spaces the user printed

	vector<vector<char> > Keyboard;
	vector<int> SuitableF;
	vector<int> PositionInWords;
	vector<int> SuitPriority;
	vector<int> BasicPositions;
	int CurrPriority;

	
	int Ind3;
	int Ind4;
	int Ind5;
	int Ind6;
	int Ind7;
	int Ind8;
	int Ind9;

	T9();
	~T9();
	void Create();
	void FillKeyboard();
	void MarkSuitableWord(int Pos1, int Pos2);
	void FindWord(int stars);
	void BiteOutWords();
	void SortSymbol(int stars);
	int MoveDigits(int Pos);
	vector<int> MoveWordStars(int Pos);
	int MoveSymbolStars(int Pos);
	void SuitableFreqSort();
	vector<int> GetIndex(char a);
	void SetSuitable(int Pos1, int Pos2);
	
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
	
	bool Marked2=false;
	bool Marked3=false;
	bool Marked4=false;
	bool Marked5=false;
	bool Marked6=false;
	bool Marked7=false;
	bool Marked8=false;
	bool Marked9=false;
	
	Ind3=0;
	Ind4=0;
	Ind5=0;
	Ind6=0;
	Ind7=0;
	Ind8=0;
	Ind9=0;
	CurrPriority=1;
	
	char a[21];
	char s[100001];
	int b;

	scanf("%d", &WordNum);

	for(int i=0; i<WordNum; i++)
	{
		scanf("%s", &a);
		scanf("%d\n", &b);

		string t(a);
		
		Words.push_back(t);
		Freqs.push_back(b);
		Priority.push_back(0);

		if((t.at(0)=='d'||t.at(0)=='e'||t.at(0)=='f')&&!Marked3)
		{
			Ind3=Words.size()-1;
			Marked3=true;
		}
		if((t.at(0)=='g'||t.at(0)=='h'||t.at(0)=='i')&&!Marked4)
		{
			Ind4=Words.size()-1;
			Marked4=true;
		}
		if((t.at(0)=='j'||t.at(0)=='k'||t.at(0)=='l')&&!Marked5)
		{
			Ind5=Words.size()-1;
			Marked5=true;
		}
		if((t.at(0)=='m'||t.at(0)=='n'||t.at(0)=='o')&&!Marked6)
		{
			Ind6=Words.size()-1;
			Marked6=true;
		}	
		if((t.at(0)=='p'||t.at(0)=='q'||t.at(0)=='r'||t.at(0)=='s')&&!Marked7)
		{
			Ind7=Words.size()-1;
			Marked7=true;
		}
		if((t.at(0)=='t'||t.at(0)=='u'||t.at(0)=='v')&&!Marked8)
		{
			Ind8=Words.size()-1;
			Marked8=true;
		}
		if((t.at(0)=='w'||t.at(0)=='x'||t.at(0)=='y'||t.at(0)=='z')&&!Marked9)
		{
			Ind9=Words.size()-1;
			Marked9=true;
		}
		
	}
		
	fgets(s, 100001, stdin);

	string seq(s);

	Sequence = seq;

	SuitableF=Freqs;
	SuitPriority=Priority;
	

	for(int i=0;i<Words.size();i++)
	{
		BasicPositions.push_back(i);
	}

	PositionInWords=BasicPositions;

}

void T9::MarkSuitableWord(int Pos1, int Pos2)
{
	string::iterator Move;//for Sequence
	vector<int>::iterator MoveInt;//for Converted
	vector<int>::iterator PosMove;//for PositionInWords
	vector<char>::iterator KeyMove;//for Keyboard
	bool Take = false;
	bool MainTake=true;
	vector<int> tempFr;//auxilary 
	vector<int> tempPr;//
	vector<int> posInWords;//vectors	
	int a=0;
	int len = Pos2-Pos1+1;

	vector<int> Interval = GetIndex(Sequence.at(Pos1));
	SetSuitable(Interval.front(), Interval.back());

	vector<int> Converted;
	for(Move = Sequence.begin()+Pos1;Move<=Sequence.begin()+Pos2; Move++)
	{
		string d="";//a clumsy conversion
		d.insert(d.begin(),(*Move));		
		a = atoi(d.c_str());
		Converted.push_back(a);
	}
	

	
	for(PosMove=PositionInWords.begin(); PosMove<PositionInWords.end(); PosMove++)
	{
		if((Words.at(*PosMove)).length()==len)
		{
			for(MoveInt = Converted.begin(); MoveInt<Converted.end(); MoveInt++)
			{
				MainTake=true;
				Take=false;

				for(KeyMove=Keyboard.at((*MoveInt)-1).begin(); KeyMove<Keyboard.at((*MoveInt)-1).end(); KeyMove++)
				{
					if((Words.at(*PosMove)).at(MoveInt-Converted.begin())==*KeyMove)
					{
						Take=true;
						break;
					}
				}
				
				MainTake=MainTake&&Take;
				if(!MainTake)
					break;
			}
		
			if (MainTake)
			{
				Take=false;
				tempFr.push_back(SuitableF.at(PosMove-PositionInWords.begin()));
				posInWords.push_back(PositionInWords.at(PosMove-PositionInWords.begin()));
				tempPr.push_back(SuitPriority.at(PosMove-PositionInWords.begin()));

		
			}
		
		}
	}

	
	SuitableF=tempFr;
	SuitPriority=tempPr;
	PositionInWords=posInWords;

}

void T9::FindWord(int stars)
{

	int st = stars%(PositionInWords.size());//the words should cycle; or there'll be error
	string TheWord = Words.at(PositionInWords.at(st));
	Printed.append(TheWord);
	SuitableF.at(st)=SuitableF.at(st)+1;
	int currFreq=SuitableF.at(st);
	int currPos =PositionInWords.at(st);
	
	vector<int>::iterator Move;
	int FreqPos=PositionInWords.at(st);	

	Freqs.at(FreqPos)=Freqs.at(FreqPos)+1;
	Priority.at(FreqPos)=Priority.at(FreqPos)+CurrPriority;
	CurrPriority++;

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
			SuitableFreqSort();
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

void T9::SuitableFreqSort()
{	
	vector<int>::iterator Move;
	vector<PosFreq> SortContainer;
	vector<PosFreq>::iterator PosFreqMove;

	for(Move=PositionInWords.begin(); Move<PositionInWords.end(); Move++)
	{
		PosFreq A(*Move, SuitableF.at(Move-PositionInWords.begin()),SuitPriority.at(Move-PositionInWords.begin()));
		SortContainer.push_back(A);
	}

	std::stable_sort(SortContainer.begin(),SortContainer.end(), moreFrequent);
	PositionInWords.clear();
	SuitableF.clear();
	SuitPriority.clear();

	for(PosFreqMove=SortContainer.begin(); PosFreqMove<SortContainer.end(); PosFreqMove++)
	{
		PositionInWords.push_back((*PosFreqMove).WordPos);
		SuitableF.push_back((*PosFreqMove).Freq);
		SuitPriority.push_back((*PosFreqMove).Priority);
	}
}

vector<int> T9::GetIndex(char a)
{
	vector<int> Res;
	if(a=='2')
	{
		Res.push_back(0);
		(Ind3 ? Res.push_back(Ind3):(Ind4? Res.push_back(Ind4):(Ind5? Res.push_back(Ind5):(Ind6?Res.push_back(Ind6):(Ind7? Res.push_back(Ind7):(Ind8? Res.push_back(Ind8):(Ind9? Res.push_back(Ind9):(Res.push_back(Words.size()-1)))))))));
	}
	if(a=='3')
	{
		Res.push_back(Ind3);
		(Ind4? Res.push_back(Ind4):(Ind5? Res.push_back(Ind5):(Ind6?Res.push_back(Ind6):(Ind7? Res.push_back(Ind7):(Ind8? Res.push_back(Ind8):(Ind9? Res.push_back(Ind9):(Res.push_back(Words.size()-1))))))));
	}
	if(a=='4')
	{
		Res.push_back(Ind4);
		(Ind5? Res.push_back(Ind5):(Ind6?Res.push_back(Ind6):(Ind7? Res.push_back(Ind7):(Ind8? Res.push_back(Ind8):(Ind9? Res.push_back(Ind9):(Res.push_back(Words.size()-1)))))));
	}
	if(a=='5')
	{
		Res.push_back(Ind5);
		(Ind6?Res.push_back(Ind6):(Ind7? Res.push_back(Ind7):(Ind8? Res.push_back(Ind8):(Ind9? Res.push_back(Ind9):(Res.push_back(Words.size()-1))))));
	}
	if(a=='6')
	{
		Res.push_back(Ind6);
        (Ind7? Res.push_back(Ind7):(Ind8? Res.push_back(Ind8):(Ind9? Res.push_back(Ind9):(Res.push_back(Words.size()-1)))));
	}
	if(a=='7')
	{
		Res.push_back(Ind7);
		(Ind8? Res.push_back(Ind8):(Ind9? Res.push_back(Ind9):(Res.push_back(Words.size()-1))));
	}
	if(a=='8')
	{
		Res.push_back(Ind8);
		(Ind9? Res.push_back(Ind9):(Res.push_back(Words.size()-1)));
	}
	if(a=='9')
	{
		Res.push_back(Ind9);
		Res.push_back(Words.size()-1);
	}
return Res;
}

void T9::SetSuitable(int Pos1, int Pos2)
{
	vector<int> tempFr;
	vector<int> tempPos;	
	vector<int> tempPr;
	vector<int>::iterator Move;

	for(Move=BasicPositions.begin()+Pos1; Move<=BasicPositions.begin()+Pos2; Move++)
	{
		tempPos.push_back(*Move);
		tempFr.push_back(Freqs.at(Move-BasicPositions.begin()));
		tempPr.push_back(Priority.at(Move-BasicPositions.begin()));
	}
	
	SuitableF=tempFr;
	PositionInWords=tempPos;
	SuitPriority=tempPr;
}
int main()
{
	T9 X;
	X.Create();
	X.BiteOutWords();
	printf("%s\n", X.Printed.c_str());
	
	return 0;
}


