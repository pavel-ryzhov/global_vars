#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;

#include <algorithm>
#include<vector>
using std::vector;

///////////////////////////////////////////////////////////
class WORD
{
public:
	int pop;
	int xz;
	int len;
	char word[21];	
};
////////////////////////////////////////////////////////////
class TOP
{
public:
	vector <WORD> word;
	TOP * nextT;
	bool empty;
	bool sorted;
	
	TOP()
	{
		empty = true;
		sorted = false;
	}	

	inline void sortV(int end = 0)
	{
		if(end == 0 )
		{
			stable_sort(word.begin(), word.end());			
		}
		else
		{
			end++;
			stable_sort(word.begin(), word.begin() + end);			
		}

	}

	void printW()
	{
		for(int j = 0; j < word.size(); j++)
		{
			for(int i = 0; i <word[j].len; i++)
			{
				cout << word[j].word[i];
			}
			cout<< " " << word[j].pop << " " << word[j].xz;
		}
		cout<<endl;		
	}
};

class LIB
{
private:
	int length;	
	TOP mainTop;
	int toButton[26];
	char punctuation[3];

public:
	LIB()
	{
		vector <WORD>::iterator it;
		mainTop.nextT = new TOP[8];	
		mainTop.empty = false;
		cin >> length;		
		initwordPtr();		
		punctuation[0] = '.'; 
		punctuation[1] = ','; 
		punctuation[2] = '?'; 
	}

	void initwordPtr()
	{
		toButton[0] = 0;
		toButton[1] = 0;
		toButton[2] = 0;
		toButton[3] = 1;
		toButton[4] = 1;
		toButton[5] = 1;
		toButton[6] = 2;
		toButton[7] = 2;
		toButton[8] = 2;
		toButton[9] = 3;
		toButton[10] = 3; 
		toButton[11] = 3;
		toButton[12] = 4;
		toButton[13] = 4;
		toButton[14] = 4;
		toButton[15] = 5;
		toButton[16] = 5;
		toButton[17] = 5;
		toButton[18] = 5;
		toButton[19] = 6;
		toButton[20] = 6;
		toButton[21] = 6;
		toButton[22] = 7;
		toButton[23] = 7;
		toButton[24] = 7;
		toButton[25] = 7;	
	}

	void fillLib()
	{	
		cin.get();
		WORD buffW;
		TOP * buffT;
		
		for(int i = 0; i < length; i++)
		{			
			cin.get(buffW.word, 21, ' ');
			cin >> buffW.pop;	
			buffW.xz = 0;
			buffW.len = strlen(buffW.word);	
			cin.get();

			buffT = &mainTop;	
			
			for(int j = 0; j < buffW.len; j++)
			{
				if(buffT->empty)
				{
					buffT->nextT = new TOP[8];	
					buffT->empty = false;
				}
				//cout<< getButton(buffW.word[j]) << " ";
				buffT = &buffT->nextT[getButton(buffW.word[j])];	
			}
			//cout<<endl;
			buffT->word.push_back(buffW);
			//buffT->printW();
			//cout<< buff.pop << "  " << buff.xz << "  ";			
		}
	}	

	inline int getButton(char c)
	{ 
		return toButton[c - 97];
	}

	void readCommand()
	{		
		int i = 0;
		int numStar = 0;
		int buff[21];
		char cPeek;
		int xzPP = 1;

		while(cin.peek() > 0)
		{
			cPeek = cin.peek();
			if((cPeek == ' ')||(cPeek == '1')||(cPeek == '*')||(cPeek == 10))
			{
				if(i != 0)
				{
					while(cin.peek() == '*')
					{
						cin.get();
						numStar++;
					}					
					findWord(buff, i, numStar, xzPP);
					i = 0;		
					numStar =  0;
					clearBuff(buff);
				}

				if(cPeek == ' ')
				{		
					cout<<' ';
					cin.get();						
				}

				if(cPeek == '1')
				{
					cin.get();
					while(cin.peek() == '*')
					{
						cin.get();
						numStar++;
					}					
					printPunctuation(numStar);
					numStar =  0;
				}	
				if(cin.peek() == 10)
				{
					break;
				}
			}
			else
			{
				buff[i] = cin.get()-50;				
				i++;
			}
		}

		if( i != 0 )
		{
			findWord(buff, i, numStar, xzPP);
			i = 0;		
			numStar =  0;
			clearBuff(buff);
			cin.get();	
		}
	}

	inline void printPunctuation(int numStar)
	{
		cout<<punctuation[numStar];
	}

	inline void findWord(int * buff, int len, int numStars, int &xzPP)
	{
		TOP * seeker = &mainTop;

		for(int i = 0; i < len; ++i)
		{
			seeker = &seeker->nextT[buff[i]];
		}
		if(!seeker->sorted)
		{
			seeker->sortV();
			seeker->sorted = true;
		}
		if(numStars == 0)
		{
			seeker->word[0].pop++;
			seeker->word[0].xz = xzPP;
			xzPP++;
			printWord(seeker->word[0]);
		}
		else
		{
			seeker->word[numStars].pop++;
			seeker->word[numStars].xz = xzPP;
			xzPP++;
			printWord(seeker->word[numStars]);
			seeker->sortV(numStars);			
		}
		
	}

	inline void printWord(WORD w)
	{
		cout.write(w.word, w.len);		
	}

	inline void clearBuff(int * b)
	{
		for(int i = 0; i < 21; i++)
		{
			b[i] = 0;
		}
	}
};
////////////////////////////////////////////////////////////
int main()
{ 	
	/*clock_t end1;
	clock_t end2;
	double time1;
	double time2;
	clock_t begin1;
	clock_t begin2;

	begin1 = clock();*/
	LIB newLib;
	newLib.fillLib();
	/*end1 = clock();

	begin2 = clock();*/
	newLib.readCommand();
	/*end2 = clock();
			
	system("pause");
	time1=((double)(end1-begin1))/CLOCKS_PER_SEC;
	time2=((double)(end2-begin2))/CLOCKS_PER_SEC;
	cout<<endl<<"input T: "<<time1<<"  "<<"Pars. T: "<<time2<<endl;*/
	//system("pause");
	return 0;
}

bool operator<(const WORD &w1, const WORD &w2)
	{
		return (w1.pop > w2.pop || ( w1.pop == w2.pop &&  w1.xz > w2.xz));
	}