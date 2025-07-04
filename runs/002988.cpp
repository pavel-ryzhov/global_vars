#include <algorithm>
#include <vector>
#include <cstdio>

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
vector< vector< char > > CodesMas[20][160];
vector< unsigned short > CodesMasIndex[20][160];

char InLine[SENTENCE_MAX_LEN] = {0};

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


int FindInCodes(int size, int CodeSum, vector< char > code)
{
	for(int i=0;i<CodesMas[size][CodeSum].size();i++)
	{
		if(CodesMas[size][CodeSum][i] == code)
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

bool FirstLessNew(myPair i) 
{
	return (FL>i.Frequency);
}

void InsertNewWord(int Index,myPair NewPair)
{	
	FL=NewPair.Frequency;
	vector<myPair>::iterator it = find_if(Vocabulary[Index].begin(),Vocabulary[Index].end(),FirstLessNew);
	Vocabulary[Index].insert(it,NewPair);
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
		for(int i=0;i<CodeSize;i++)
		{
			CodeSum = CodeSum + TmpCode1[i];
		}
		CodeSum--;
		CodeSize--;

		pos = FindInCodes(CodeSize,CodeSum,TmpCode1);

		if( pos == -1)
		{
			CodesMas[CodeSize][CodeSum].push_back(TmpCode1);
			pos = Vocabulary.size();
			CodesMasIndex[CodeSize][CodeSum].push_back(pos);
			Vocabulary.resize(Vocabulary.size()+1);
		}
		else
		{
			pos = CodesMasIndex[CodeSize][CodeSum][pos];
		}

		TmpPair1.Frequency = TmpFreq1;
		for(int j=0;j<WORD_MAX_LEN;j++)
		{
			TmpPair1.Word[j] = TmpStr1[j];
		}
		InsertNewWord(pos,TmpPair1);
	}
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
		if(TmpCode1[0] != 0)
		{
			int CodeSize = TmpCode1.size();
			int CodeSum = 0;
			for(int i=0;i<CodeSize;i++)
			{
				CodeSum = CodeSum + TmpCode1[i];
			}
			CodeSum--;
			CodeSize--;

			pos = FindInCodes(CodeSize,CodeSum,TmpCode1);
			pos = CodesMasIndex[CodeSize][CodeSum][pos];
		}
		else
		{
			pos = 0;
		}

		if( pos >=0)
		{
			if(steps >=  Vocabulary[pos].size())
			{
				steps = steps % Vocabulary[pos].size();
			}

			printf("%s",&(Vocabulary[pos][steps].Word));
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