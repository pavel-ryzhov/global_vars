#include <algorithm>
#include <vector>
#include <cstdio>
#include <string.h>

using namespace std;

#define WORD_MAX_LEN 21
#define SENTENCE_MAX_LEN 100001
#define MAXFREQ 1000
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

vector< vector < vector< myPair > > > Vocabulary;
vector< vector< char > > CodesMas[20][160][21];
vector< unsigned short > CodesMasIndex[20][160][21];
vector < unsigned short > VocabularySizes;

char InLine[SENTENCE_MAX_LEN] = {0};
char Out[SENTENCE_MAX_LEN] = {0};

vector< char > GetCharCode(char str[WORD_MAX_LEN])
{
	vector< char > Result;
	int Tmp1=0;
	for(int i=0;i<WORD_MAX_LEN;i++)
	{
		if(str[i]!='\0')
		{
			Result.push_back((str[i]) - 49);
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
				Result.push_back(0);
				break;
			case 'a':
			case 'b':
			case 'c':
				Result.push_back(1);
				break;
			case 'd':
			case 'e':
			case 'f':
				Result.push_back(2);
				break;
			case 'g':
			case 'h':
			case 'i':
				Result.push_back(3);
				break;
			case 'j':
			case 'k':
			case 'l':
				Result.push_back(4);
				break;
			case 'm':
			case 'n':
			case 'o':
				Result.push_back(5);
				break;
			case 'p':
			case 'q':
			case 'r':
			case 's':
				Result.push_back(6);
				break;
			case 't':
			case 'u':
			case 'v':
				Result.push_back(7);
				break;
			case 'w':
			case 'x':
			case 'y':
			case 'z':
				Result.push_back(8);
				break;
			}
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

int FindInCodes(int size, int CodeSum, vector< char > code,int EvenNum)
{
	for(int i=0;i<CodesMas[size][CodeSum][EvenNum].size();i++)
	{
		if(CodesMas[size][CodeSum][EvenNum][i] == code)
		{
			return i;
		}
	}
	return -1;
}

bool FirstLess(myPair i) 
{
	return (FL>=i.Frequency);
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
		int CodeSize = TmpCode1.size();
		int CodeSum = 0;
		int EvenNum = 0;
		for(int i=0;i<CodeSize;i++)
		{
			CodeSum = CodeSum + TmpCode1[i];
			if( (TmpCode1[i] % 2) == 0  )
			{
				EvenNum++;
			}
		}
		CodeSum--;
		CodeSize--;

		pos = FindInCodes(CodeSize,CodeSum,TmpCode1,EvenNum);

		if( pos == -1)
		{
			CodesMas[CodeSize][CodeSum][EvenNum].push_back(TmpCode1);
			pos = Vocabulary.size();
			CodesMasIndex[CodeSize][CodeSum][EvenNum].push_back(pos);
			Vocabulary.resize(Vocabulary.size()+1);
			VocabularySizes.resize(VocabularySizes.size()+1);
			VocabularySizes[VocabularySizes.size()-1] = 0;
			Vocabulary[pos].resize(10);
		}
		else
		{
			pos = CodesMasIndex[CodeSize][CodeSum][EvenNum][pos];
		}

		TmpPair1.Frequency = TmpFreq1;
		for(int j=0;j<WORD_MAX_LEN;j++)
		{
			TmpPair1.Word[j] = TmpStr1[j];
			if(TmpStr1[j] == '\0')
			{
				break;
			}
		}

		int k = (TmpPair1.Frequency / 100);
		if(k >= 10)
		{
			k=9;
		}
		Vocabulary[pos][k].push_back(TmpPair1);
		VocabularySizes[pos]++;
	}
}

void Up(int Index,int Pos,int Steps)
{
	myPair NewPair;
	if(Pos != 9)
	{

		for(int i=0;i<WORD_MAX_LEN;i++)
		{
			NewPair.Word[i] = Vocabulary[Index][Pos][Steps].Word[i];
		}
		NewPair.Frequency =  Vocabulary[Index][Pos][Steps].Frequency;
		NewPair.Frequency++;
		FL=NewPair.Frequency;
		int NewPos = NewPair.Frequency / 100;
		Vocabulary[Index][Pos].erase(Vocabulary[Index][Pos].begin()+Steps);
		vector<myPair>::iterator it = find_if(Vocabulary[Index][NewPos].begin(),Vocabulary[Index][NewPos].end(),FirstLess);
		Vocabulary[Index][NewPos].insert(it,NewPair);
	}
	else
	{
		myPair TmpWord1;
		for(int i=0;i<WORD_MAX_LEN;i++)
		{
			TmpWord1.Word[i] = Vocabulary[Index][Pos][Steps].Word[i];
			if(Vocabulary[Index][Pos][Steps].Word[i] == '\0')
			{
				break;
			}
		}
		TmpWord1.Frequency =  Vocabulary[Index][Pos][Steps].Frequency;
		Vocabulary[Index][Pos].erase(Vocabulary[Index][Pos].begin()+Steps);
		Vocabulary[Index][Pos].insert(Vocabulary[Index][Pos].begin(),TmpWord1);
	}
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

		if(TmpCode1[0] != 0)
		{
			int CodeSize = TmpCode1.size();
			int CodeSum = 0;
			int EvenNum=0;
			for(int i=0;i<CodeSize;i++)
			{
				CodeSum = CodeSum + TmpCode1[i];
				if( (TmpCode1[i] % 2) == 0  )
				{
					EvenNum++;
				}
			}
			CodeSum--;
			CodeSize--;

			pos = FindInCodes(CodeSize,CodeSum,TmpCode1,EvenNum);
			pos = CodesMasIndex[CodeSize][CodeSum][EvenNum][pos];
		}
		else
		{
			pos = 0;
		}

		if( pos >=0)
		{

			if(steps >=  VocabularySizes[pos])
			{
				steps = steps %  VocabularySizes[pos];
			}

			int p=9;
			while( steps >= Vocabulary[pos][p].size() )
			{
				steps = steps - Vocabulary[pos][p].size();
				p--;
			}

			strcat(Out,Vocabulary[pos][p][steps].Word);

			if(pos != 0)
			{
				Up(pos,p,steps);
			}
		}
	}
}

int main(void)
{
	N=0;
	scanf ("%d",&N); 
	if(N < 0)
	{
		return 0;
	}
	Vocabulary.resize(1);
	VocabularySizes.resize(1);
	VocabularySizes[0]=3;

	Vocabulary[0].resize(10);
	myPair TmpCode1; 
	TmpCode1.Word[0] = '.';
	TmpCode1.Frequency=1;
	Vocabulary[0][0].push_back(TmpCode1);
	TmpCode1.Word[0] = ',';
	Vocabulary[0][0].push_back(TmpCode1);
	TmpCode1.Word[0] = '?';
	Vocabulary[0][0].push_back(TmpCode1);

	ReadVocabulary();

	int size=Vocabulary.size();
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<Vocabulary[i].size();j++)
		{
			stable_sort(Vocabulary[i][j].begin(),Vocabulary[i][j].end(),SortPair);
		}
	}

	while (getchar() != '\n');
	scanf("%[^\n]",InLine);

	bool InWord=false;
	bool Stars=false;
	int StepsCount=0;
	int NewWordStart=0;
	int NewWordEnd=0;
	int Pos=0;
	char p=InLine[Pos];
	while(p!='\0' && p!='\n')
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
			strcat(Out," ");
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
		if(Pos == 99999)
		{
			Pos=Pos;
		}
	}

	if(InWord == true)
	{
		if(Stars == false)
		{
			NewWordEnd++;
		}
		GetWord(NewWordStart,NewWordEnd,StepsCount);
	}
	printf(Out);
	return 0;
}