#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string.h>

using std::cin;
using std::cout;
using std::endl;

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
class STAR
{
public:
	int index;
	int pop;
	int xz;	

public:
	STAR()
	{
		index = -1;
		pop = 1;
		xz = 1;		
	}
};
////////////////////////////////////////////////////////////
class LIB
{
private:
	int length;
	WORD * lib;
	int wordPointer[2][9];
	char punctuation[3];

public:
	LIB()
	{
		cin >> length;
		lib = new WORD[length];
		initwordPtr();
		wordPointer[0][8] = length;
		punctuation[0] = '.'; 
		punctuation[1] = ','; 
		punctuation[2] = '?'; 
	}

	void initwordPtr()
	{
		for(int i = 0; i < 9; i++)
		{
			wordPointer[0][i] = -1;
		}
		
		wordPointer[1][0] = (int)'a';
		wordPointer[1][1] = (int)'d';
		wordPointer[1][2] = (int)'g';
		wordPointer[1][3] = (int)'j';
		wordPointer[1][4] = (int)'m';
		wordPointer[1][5] = (int)'p';
		wordPointer[1][6] = (int)'t';
		wordPointer[1][7] = (int)'w';
		wordPointer[1][8] = (int)'z'+1;
	}

	int getLen()
	{
		return length;
	}

	void fillLib()
	{
		char checker = 10;
		int lastButton = 0;
		cin.get();
		for(int i = 0; i < length; i++)
		{			
			cin.get(lib[i].word, 21, ' ');
			cin >> lib[i].pop;	
			lib[i].xz = 0;
			lib[i].len = strlen(lib[i].word);            					
			
			if(lib[i].word[0] != checker)
			{				
				setwordPtr(i, lib[i].word[0], lastButton);
				checker = lib[i].word[0];
			}

			cin.get();
		}
	}

	inline void setwordPtr(int indWord, char c, int &lastB)
	{			
		for(int i = lastB; i < 8; i++)
		{			
			if(c >= wordPointer[1][i] && c < wordPointer[1][i+1])			
			{   				
				wordPointer[0][i] = indWord;
				lastB = i+1;
				break;
			}			
		}			
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
				buff[i] = cin.get()-48;				
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
		if(numStars != 0)
		{
			numStars++;
		}
		STAR * starArr = new STAR[numStars];
		int lastPutStar = 0;
		STAR maxPop;
		maxPop.pop = 0;
		maxPop.xz = 0;
		maxPop.index = -1;		
		bool checker = true;
		bool firstIn = false;
		int firstN = buff[0]-2;
		int begin = wordPointer[0][firstN];
		int end;
		for(int i = firstN+1; i < 9; i++)
		{			
			if( wordPointer[0][i] != -1)	
			{
				end = wordPointer[0][i];
				break;
			}
		}	

		for(int i = begin; i < end; i++)
		{			
			if(lib[i].len == len)
			{
				for(int j = 0; j < len; j++)
				{					
					if(lib[i].word[j] < wordPointer[1][buff[j]-2] || lib[i].word[j] >= wordPointer[1][buff[j]-1])
					{
						checker = false;
						break;						
					}
				}
				if(!checker)
				{
					checker = true;
					continue;
				}

				if(numStars != 0)
				{
					if(!firstIn)
					{						
						starArr[lastPutStar].index = i;
						starArr[lastPutStar].pop = lib[i].pop;
						starArr[lastPutStar].xz = lib[i].xz;
						firstIn = true;							
						continue;
					}
					else 
					{
						//if(lib[i].pop >= starArr[lastPutStar].pop)
						//{							
							for(int j = lastPutStar; j >= 0; j--)
							{
								if(lib[i].pop < starArr[j].pop || (lib[i].pop == starArr[j].pop && lib[i].xz <= starArr[j].xz))
								{									
									for(int k = lastPutStar; k > j; k--) 
									{
										if(k < numStars - 1)
										{
											starArr[k+1] = starArr[k];
										}										
									}	
									if(lastPutStar < numStars - 1)
									{
										lastPutStar++;
									}
									if( j != numStars - 1)
									{
										starArr[j+1].index = i;
										starArr[j+1].pop = lib[i].pop;
										starArr[j+1].xz = lib[i].xz;
									}	
									break;
								}
								else if(lib[i].pop > starArr[0].pop && j==0)
								{									
									for(int k = lastPutStar; k >= j; k--)
									{
										if(k < numStars - 1)
										{
											starArr[k+1] = starArr[k];
										}										
									}	
									if(lastPutStar < numStars - 1)
									{
										lastPutStar++;
									}
									starArr[j].index = i;
									starArr[j].pop = lib[i].pop;
									starArr[j].xz = lib[i].xz;										
									break;
								}								
							}							
						//}
					}
				}
				else if(lib[i].pop > maxPop.pop || (lib[i].pop == maxPop.pop && lib[i].xz > maxPop.xz))	 
				{								
					maxPop.pop = lib[i].pop;
					maxPop.xz = lib[i].xz;
					maxPop.index = i;					
				}
			}		
		}

		if(numStars == 0)
		{
			printWord(maxPop.index);
			lib[maxPop.index].pop++;
			lib[maxPop.index].xz = xzPP;
			xzPP++;
		}
		else
		{
			printWord(starArr[lastPutStar].index);
			lib[starArr[lastPutStar].index].pop++;
			lib[starArr[lastPutStar].index].xz = xzPP;
			xzPP++;
		}
	}

	inline void printWord(int index)
	{
		cout.write(lib[index].word, lib[index].len);
		/*for(int i = 0; i < lib[index].len; i++)
		{ 
			cout<<lib[index].word[i];			
		}*/
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
	LIB newLib;
	newLib.fillLib();
	newLib.readCommand();	
	return 0;
}