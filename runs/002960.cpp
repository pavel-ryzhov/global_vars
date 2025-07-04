#include <algorithm>
#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

#define WORD_MAX_LEN 21
#define SENTENCE_MAX_LEN 100001
int N, FL;

struct myPair
{
	char Word[WORD_MAX_LEN];
	int Frequency;
	myPair(void)
	{
		for(int i=0;i<WORD_MAX_LEN;i++)
		{
			Word[i]='\0';
		}
		Frequency=0;
	}
};

vector< vector< myPair > > Vocabulary;
vector< vector< char > > CodesMas;

char InLine[SENTENCE_MAX_LEN] = {0};

vector< char > GetCharCode(char str[WORD_MAX_LEN])
{
	vector< char > Result;
	int Tmp1=0;
	for(int i=0;i<WORD_MAX_LEN;i++)
	{
		if(str[i]!='\0')
		{
			Result.push_back(str[i]);
		}
		else
		{
			break;
		}
	}
	return Result;
}

vector< char > GetCode(char str[WORD_MAX_LEN])
{
	vector< char > Result;
	int Tmp1=0;
	for(int i=0;i<WORD_MAX_LEN;i++)
	{
		if(str[i]!='\0')
		{
			switch(str[i])
			{
			case '.':
			case ',':
			case '?':
				Result.push_back('1');//Tmp1=1;
				break;
			case 'a':
			case 'b':
			case 'c':
				Result.push_back('2');//Tmp1=2;
				break;
			case 'd':
			case 'e':
			case 'f':
				Result.push_back('3');//Tmp1=3;
				break;
			case 'g':
			case 'h':
			case 'i':
				Result.push_back('4');//Tmp1=4;
				break;
			case 'j':
			case 'k':
			case 'l':
				Result.push_back('5');//Tmp1=5;
				break;
			case 'm':
			case 'n':
			case 'o':
				Result.push_back('6');//Tmp1=6;
				break;
			case 'p':
			case 'q':
			case 'r':
			case 's':
				Result.push_back('7');//Tmp1=7;
				break;
			case 't':
			case 'u':
			case 'v':
				Result.push_back('8');//Tmp1=8;
				break;
			case 'w':
			case 'x':
			case 'y':
			case 'z':
				Result.push_back('9');//Tmp1=9;
				break;
			}
			/*if(i != 0 )
			{
				Result = Result * 10;
			}
			Result = Result + Tmp1;*/
		}
		else
		{
			break;
		}
	}
	return Result;
}

bool SortPair(myPair a, myPair b)
{ 
	return (a.Frequency>b.Frequency);
}

int FindInCodes(vector< char > code)
{
	for(int i=0;i<CodesMas.size();i++)
	{
		if(CodesMas[i] == code)
		{
			return i;
		}
	}
	return -1;
}

void ReadVocabulary(void)
{
	char TmpStr1[WORD_MAX_LEN] = {'\0'};
	int TmpFreq1=0;
	vector< char > TmpCode1;
	int pos=0;
	myPair TmpPair1;
	for(int i=0;i<N;i++)
	{
		scanf ("%s %d",TmpStr1,&TmpFreq1);
		TmpCode1 = GetCode(TmpStr1);

		pos = FindInCodes(TmpCode1);
		if( pos == -1)
		{
			CodesMas.push_back(TmpCode1);
			pos = CodesMas.size()-1;
			Vocabulary.resize(Vocabulary.size()+1);
		}

		TmpPair1.Frequency = TmpFreq1;
		for(int j=0;j<WORD_MAX_LEN;j++)
		{
			TmpPair1.Word[j] = TmpStr1[j];
		}

		Vocabulary[pos].push_back(TmpPair1);		
	}

	for(int i=0;i<Vocabulary.size();i++)
	{
		sort(Vocabulary[i].begin(),Vocabulary[i].end(),SortPair);
	}
}

bool FirstLess(myPair i) 
{
	return (FL>=i.Frequency);
}

void Up(int Index,int Pos)
{
	if(Pos >=  Vocabulary[Index].size())
	{
		Pos = Pos % Vocabulary[Index].size();
	}
	myPair NewPair;
	NewPair=Vocabulary[Index][Pos];
	NewPair.Frequency++;
	FL=NewPair.Frequency;
	Vocabulary[Index].erase(Vocabulary[Index].begin()+Pos);
	vector<myPair>::iterator it = find_if(Vocabulary[Index].begin(),Vocabulary[Index].end(),FirstLess);
	Vocabulary[Index].insert(it,NewPair);
}

void GetWord(int start,int end,int steps)
{
	int Tmp1=0;
	int pos = 0;
	vector< char > TmpCode1;
	char TmpStr1[WORD_MAX_LEN] = {'\0'};

	if( (end - start) >= 1)
	{
		for(int i=start;i<end;i++)
		{
			TmpStr1[Tmp1] = InLine[i];
			Tmp1++;
		}
		
		TmpCode1 = GetCharCode(TmpStr1);
		pos = FindInCodes(TmpCode1);
	
		if( pos >=0)
		{
			if(steps >=  Vocabulary[pos].size())
			{
				steps = steps % Vocabulary[pos].size();
			}

			printf("%s",&(Vocabulary[pos][steps]));
			if(pos != 0)
			{
				Up(pos,steps);
			}
		}
	}
}

int main(void)
{
	N=0;
	myPair TmpPair1;
	scanf ("%d",&N); 
	if(N < 0)
	{
		return 0;
	}

	vector< char > TmpCode1;
	TmpCode1.push_back('1');
	CodesMas.push_back(TmpCode1);
	Vocabulary.resize(1);
	TmpPair1.Frequency=1;
	TmpPair1.Word[0]='.';
	Vocabulary[0].push_back(TmpPair1);
	TmpPair1.Word[0]=',';
	Vocabulary[0].push_back(TmpPair1);
	TmpPair1.Word[0]='?';
	Vocabulary[0].push_back(TmpPair1);

	ReadVocabulary();

	while (getchar() != '\n');
	scanf("%[^\n]",InLine);
	

	bool InWord=false;
	bool Stars=false;
	int StepsCount=0;
	int NewWordStart=0;
	int NewWordEnd=0;
	int Pos=0;
	char p=InLine[Pos];
	while(p!='\0')
	{
		if(p == ' ')
		{
			if(Stars == true)
			{
				Stars = false;
				InWord=false;
				GetWord(NewWordStart,NewWordEnd,StepsCount);
				NewWordStart=-1;
				NewWordEnd=-1;
				StepsCount=0;
			}
			else
			{
				if(InWord == true)
				{
					InWord=false;
					NewWordEnd=Pos;
					GetWord(NewWordStart,NewWordEnd,StepsCount);
					NewWordStart=-1;
					NewWordEnd=-1;
					StepsCount=0;
				}
			}
			printf(" ");
		}
		else
		{
			if(p == '*')
			{
				if(InWord == true)
				{
					if(Stars == false)
					{
						Stars=true;
						NewWordEnd=Pos;
						StepsCount++;
					}
					else
					{
						StepsCount++;
					}
				}
			}
			else
			{
				if(p == '1')
				{
					if(Stars == true)
					{
						Stars = false;
						InWord=false;
						GetWord(NewWordStart,NewWordEnd,StepsCount);
						NewWordStart=-1;
						NewWordEnd=-1;
						StepsCount=0;
					}
					else
					{
						if(InWord == true)
						{
							InWord=false;
							NewWordEnd=Pos;
							GetWord(NewWordStart,NewWordEnd,StepsCount);
							NewWordStart=-1;
							NewWordEnd=-1;
							StepsCount=0;
						}
					}

					InWord = true;
					NewWordStart=Pos;
					NewWordEnd=Pos;
					Stars=false;
				}
				else
				{
					if(Stars == true)
					{
						Stars = false;
						InWord=false;
						GetWord(NewWordStart,NewWordEnd,StepsCount);
						NewWordStart=-1;
						NewWordEnd=-1;
						StepsCount=0;
					}
					if(InWord == false)
					{
						InWord = true;
						NewWordStart=Pos;
						NewWordEnd=Pos;
						Stars=false;
					}
					else
					{
						if( InLine[NewWordStart] != '1')
						{
							NewWordEnd=Pos;
						}
						else
						{
							NewWordEnd=Pos;
							GetWord(NewWordStart,NewWordEnd,StepsCount);
							NewWordStart=Pos;
							NewWordEnd=Pos;
						}
					}
				}
			}
		}
		Pos++;
		p = InLine[Pos];
	}

	if(InWord == true)
	{
		if(Stars == false)
		{
			NewWordEnd++;
		}
		GetWord(NewWordStart,NewWordEnd,StepsCount);
	}
	return 0;
}

