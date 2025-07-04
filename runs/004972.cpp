#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "iostream"

// Function that transforms literal presentation of word to
// combination of buttons needed to push to enter this word in T9;
void ToNumeric(char* Word, char* NumericWord)
{
	int i;
	for(i = 0; Word[i] != 0; i++)
	{
		if (Word [i] >= 'm')
			if (Word [i] >= 't')
				if (Word [i] >= 'w')
					NumericWord [i] = '9';
				else
					NumericWord [i] = '8';
			else if (Word [i] >= 'p')
				NumericWord [i] = '7';
			else NumericWord [i] = '6';
		else if (Word [i] >= 'g')
			if (Word [i] >= 'j')
				NumericWord [i] = '5';
			else NumericWord [i] = '4';
		else if (Word [i] >= 'd')
			NumericWord [i] = '3';
		else NumericWord [i] = '2';
	}
	NumericWord [i] = 0;
}

// Function that copyes char form one string to other,
// returns the position of treminal zero in result string;
//long CopyString( char* StringToCopyFrom, char* StringToCopyTo, long Place )
//{
//	int i;
//	for (i = 0; StringToCopyFrom [i] != 0; i++)
//		StringToCopyTo [(long)Place + i] = StringToCopyFrom [i];
//	StringToCopyTo [(long)Place + i] = 0;
//	return (long)Place + i;
//}
// Objects of this class is nodes of doubly-linked list.
// Single node contains literal representation of word,
// Frequency of this found in text
// and pointers to next and previous nodes;
class WordsNode
{
public:
	WordsNode()
	{
		Frequency = 0;
		Word [0] = 0;
	}
	WordsNode(int IncFrequency, char *IncWord, WordsNode *IncNext, WordsNode *IncPrev)
	{
		int i = 0;
		while ( IncWord [i] != NULL )
		{
			Word [i] = IncWord[i];
			++i;
		}
		Word [i] = NULL;
		Prev = IncPrev;
		Next = IncNext;
		Frequency = IncFrequency;
	}
	// Function to add node in to doubly-linked list. Position of new node depends on it's Frequency.
	// Returns pointer to first node of the list; 
	WordsNode *AddNode (int IncFrequency, char *IncWord)
	{
		WordsNode *CurrentNode;
		WordsNode *TempPointer;
		if (this == NULL)
			return new WordsNode(IncFrequency, IncWord, NULL, NULL);
		CurrentNode = this;
		while ( IncFrequency < (CurrentNode -> Frequency) )
		{
			if ( (CurrentNode -> Next) != NULL )
				CurrentNode = CurrentNode -> Next;
			else
			{
				CurrentNode -> Next = new WordsNode(IncFrequency, IncWord, NULL, CurrentNode);
				return this;
			}
		}
		while ( IncFrequency == (CurrentNode -> Frequency) )
		{
			if ( (strcmp(IncWord, CurrentNode -> Word) > 0) && ( (CurrentNode -> Next) != NULL ) )
			{
				if ( (CurrentNode -> Next -> Frequency) == IncFrequency )
					CurrentNode = CurrentNode -> Next;
				else
				{
					TempPointer = new WordsNode(IncFrequency, IncWord, CurrentNode -> Next, CurrentNode);
					CurrentNode -> Next -> Prev = TempPointer;
					CurrentNode -> Next = TempPointer;
					return this;
				}
			}
			else if (strcmp(IncWord, CurrentNode -> Word) > 0)
			{
				TempPointer = new WordsNode(IncFrequency, IncWord, NULL, CurrentNode);
				CurrentNode -> Next = TempPointer;
				return this;
			}
		}
		if ( IncFrequency > (CurrentNode -> Frequency) )
		{
			TempPointer = new WordsNode(IncFrequency, IncWord, CurrentNode, CurrentNode -> Prev);
			if ( CurrentNode -> Prev != NULL )
			{
				CurrentNode -> Prev -> Next = TempPointer;
				CurrentNode -> Prev = TempPointer;
				return this;
			}
			CurrentNode -> Prev = TempPointer;
			return TempPointer;
		}
	}
	WordsNode *Prev;
	WordsNode *Next;
	int Frequency;
	char Word [21];
};

// Objects of this class is nodes of doubly-linked list.
// Single node contains: 
// NumericWord [21] - Numeric representation of word, which is numbers of buttons to push to type this word;
// NumberOfWords - Amount of different words, that can be typed by combination of buttons in NumericWord [21];
// *Next, *Prev - Pointers to the next and previous nodes of the list;
// *BeginningOfWordsList - Pointer to the first node of list of all words, 
// that can be typed by combination of buttons in NumericWord [21];
//class NumericWordsNode
//{
//public:
//	NumericWordsNode()
//	{
//		Next = Prev = NULL;
//		BeginningOfWordsList = NULL;
//		NumericWord [0] = 0;
//	}
//	// Destructor of class. Deletes list of literal representation of words;
//	~NumericWordsNode()
//	{
//		WordsNode *CurrentNode;
//		CurrentNode = this -> BeginningOfWordsList;
//		while ( CurrentNode -> Next != NULL)
//		{
//			CurrentNode = CurrentNode -> Next;
//			delete CurrentNode -> Prev;
//		}
//		delete CurrentNode;
//	}
//	NumericWordsNode(char *IncNumericWord, NumericWordsNode *IncNext, 
//		NumericWordsNode *IncPrev, int IncFrequency, char *IncWord)
//	{
//		int i = 0;
//		while ( IncNumericWord [i] != NULL )
//		{
//			NumericWord [i] = IncNumericWord[i];
//			++i;
//		}
//		NumericWord [i] = NULL;
//		Next = IncNext;
//		Prev = IncPrev;
//		BeginningOfWordsList = NULL;
//		NumberOfWords = 0;
//	};
//	// Function to add new node into list of numeric representations of words and make list 
//	// of literal representations of words or if such node exists, to add to existing list;
//	// List is sorted by the increasing of NumericWord[21] field;
//	NumericWordsNode *AddNumericNode (char *IncNumericWord, int IncFrequency, char *IncWord)
//	{
//		NumericWordsNode *CurrentNode;
//		if ( this == NULL )
//		{
//			CurrentNode = new NumericWordsNode(IncNumericWord, NULL, NULL, IncFrequency, IncWord);
//			CurrentNode -> BeginningOfWordsList = CurrentNode -> BeginningOfWordsList -> AddNode(IncFrequency, IncWord);
//			(CurrentNode -> NumberOfWords)++;
//			return CurrentNode;
//		}
//		CurrentNode = this;
//		while ( strcmp(IncNumericWord, CurrentNode -> NumericWord) > 0 )
//		{
//			if ( CurrentNode -> Next != NULL)
//				CurrentNode = CurrentNode -> Next;
//			else 
//			{
//				CurrentNode -> Next = new NumericWordsNode(IncNumericWord, NULL, CurrentNode, IncFrequency, IncWord);
//				CurrentNode -> Next -> BeginningOfWordsList = CurrentNode -> Next -> BeginningOfWordsList -> AddNode(IncFrequency, IncWord);
//				(CurrentNode -> Next -> NumberOfWords)++;
//				return this;
//			}
//		}
//		if( strcmp(IncNumericWord, CurrentNode -> NumericWord) < 0 )
//		{
//			if ( CurrentNode -> Prev == NULL )
//			{
//				CurrentNode -> Prev = new NumericWordsNode(IncNumericWord, CurrentNode, NULL, IncFrequency, IncWord);
//				CurrentNode -> Prev -> BeginningOfWordsList = CurrentNode -> Prev -> BeginningOfWordsList -> AddNode(IncFrequency, IncWord);
//				(CurrentNode -> Prev -> NumberOfWords)++;
//				return CurrentNode -> Prev;
//			}
//			else 
//			{
//				CurrentNode -> Prev -> Next = new NumericWordsNode(IncNumericWord, CurrentNode, CurrentNode -> Prev, IncFrequency, IncWord);
//				CurrentNode -> Prev = CurrentNode -> Prev -> Next;
//				CurrentNode -> Prev -> BeginningOfWordsList = CurrentNode -> Prev -> BeginningOfWordsList -> AddNode(IncFrequency, IncWord);
//				(CurrentNode -> Prev -> NumberOfWords)++;
//				return this;
//			}
//
//		}
//		if (strcmp(IncNumericWord, CurrentNode -> NumericWord) == 0)
//		{
//			(CurrentNode -> BeginningOfWordsList) = (CurrentNode -> BeginningOfWordsList) -> AddNode(IncFrequency, IncWord);
//			(CurrentNode -> NumberOfWords)++;
//			return this;
//		}
//	}
//	// Function that finds node with word, by it's numeric representation and by amount of Stars pushed;
//	// It finds this node, cuts from it's position and pastes into new one.
//	// Function returns pointer to the string Word field of node WordsNode;
//	char* FindWord(char *IncNumericWord, unsigned int NumberOfStars)
//	{
//		NumericWordsNode *CurrentNumericNode = this;
//		NumericWordsNode *FoundNumericNode;
//		WordsNode *CurrentWordsNode;
//		WordsNode *FoundNode;
//		while ( strcmp(IncNumericWord, CurrentNumericNode -> NumericWord) != 0 )
//			CurrentNumericNode = CurrentNumericNode -> Next;
//		if (NumberOfStars > CurrentNumericNode -> NumberOfWords)
//			NumberOfStars = NumberOfStars % (CurrentNumericNode -> NumberOfWords);
//		CurrentWordsNode = CurrentNumericNode -> BeginningOfWordsList;
//		while (NumberOfStars != 0)
//		{
//			if (CurrentWordsNode -> Next != NULL)
//				CurrentWordsNode = CurrentWordsNode -> Next;
//			NumberOfStars --;
//		}
//		FoundNumericNode = CurrentNumericNode;
//		FoundNode = CurrentWordsNode;
//		if (FoundNumericNode -> NumberOfWords == 1)
//		{
//			(FoundNode -> Frequency )++;
//			return FoundNode -> Word;
//		}
//		else if ( FoundNode -> Prev == NULL )
//		{
//			(FoundNode -> Frequency )++;
//			return FoundNode -> Word;
//		}
//		else if ( (FoundNode -> Prev -> Frequency) > ( (FoundNode -> Frequency) + 1 ) )
//		{
//			(FoundNode -> Frequency )++;
//			return FoundNode -> Word;
//		}
//		else 
//		{
//			FoundNode -> Prev -> Next = FoundNode -> Next;
//			if ( FoundNode -> Next != NULL)
//				FoundNode -> Next -> Prev = FoundNode -> Prev;
//			(FoundNode -> Frequency)++;
//			while ( CurrentWordsNode -> Prev != NULL )
//			{
//				if ( ((CurrentWordsNode -> Prev -> Frequency) - 1) < (FoundNode -> Frequency) )
//					CurrentWordsNode = CurrentWordsNode -> Prev;
//				else if ( (CurrentWordsNode -> Prev -> Frequency) >= (FoundNode -> Frequency) )
//					//if (strcmp(CurrentWordsNode -> Prev -> Word, FoundNode -> Word) > 0 )
//					//	CurrentWordsNode = CurrentWordsNode -> Prev;
//					//else
//					{
//						FoundNode -> Next = CurrentWordsNode;
//						FoundNode -> Prev = CurrentWordsNode -> Prev ;
//						CurrentWordsNode -> Prev -> Next = FoundNode;
//						CurrentWordsNode -> Prev = FoundNode;
//						return FoundNode -> Word;
//					}
//			}
//			if ( CurrentWordsNode -> Prev == NULL )
//			{
//				FoundNumericNode -> BeginningOfWordsList -> Prev = FoundNode;
//				FoundNode -> Next = FoundNumericNode -> BeginningOfWordsList;
//				FoundNumericNode -> BeginningOfWordsList = FoundNode;
//				FoundNode -> Prev = NULL;
//				return FoundNode -> Word;
//			}
//		}
//	}
//	char NumericWord [21];
//	unsigned int NumberOfWords;
//	NumericWordsNode *Next;
//	NumericWordsNode *Prev;
//	WordsNode *BeginningOfWordsList;
//};
class NumWordNode
{
public:
	char Num [21];
	WordsNode *BeginningOfWordsList;
	void Prepare()
	{
		Num[0] = 0;
		BeginningOfWordsList = NULL;
	}
	void AddWord(int IncFrequency, char *IncWord)
	{
		BeginningOfWordsList = BeginningOfWordsList -> AddNode(IncFrequency, IncWord);
	}
	char* FindWord (char *IncNumericWord, unsigned int NumberOfStars, NumWordNode *NumElement)
	{
		int i = 0;
		WordsNode *CurrentWordsNode;
		WordsNode *FoundNode;
		while ( strcmp(NumElement[i].Num, IncNumericWord) != 0)
			i++;
		CurrentWordsNode = NumElement[i].BeginningOfWordsList;
		while (NumberOfStars != 0)
		{
			if (CurrentWordsNode -> Next != NULL)
				CurrentWordsNode = CurrentWordsNode -> Next;
			else 
				CurrentWordsNode = NumElement[i].BeginningOfWordsList;
			NumberOfStars --;
		}
		FoundNode = CurrentWordsNode;
		if ( FoundNode -> Prev == NULL )
		{
			(FoundNode -> Frequency )++;
			return FoundNode -> Word;
		}
		else if ( (FoundNode -> Prev -> Frequency) > ( (FoundNode -> Frequency) + 1 ) )
		{
			(FoundNode -> Frequency )++;
			return FoundNode -> Word;
		}
		else 
		{
			FoundNode -> Prev -> Next = FoundNode -> Next;
			if ( FoundNode -> Next != NULL)
				FoundNode -> Next -> Prev = FoundNode -> Prev;
			(FoundNode -> Frequency)++;
			while ( CurrentWordsNode -> Prev != NULL )
			{
				if ( ((CurrentWordsNode -> Prev -> Frequency) - 1) < (FoundNode -> Frequency) )
					CurrentWordsNode = CurrentWordsNode -> Prev;
				else if ( (CurrentWordsNode -> Prev -> Frequency) >= (FoundNode -> Frequency) )
					//if (strcmp(CurrentWordsNode -> Prev -> Word, FoundNode -> Word) > 0 )
					//	CurrentWordsNode = CurrentWordsNode -> Prev;
					//else
				{
					FoundNode -> Next = CurrentWordsNode;
					FoundNode -> Prev = CurrentWordsNode -> Prev ;
					CurrentWordsNode -> Prev -> Next = FoundNode;
					CurrentWordsNode -> Prev = FoundNode;
					return FoundNode -> Word;
				}
			}
			if ( CurrentWordsNode -> Prev == NULL )
			{
				NumElement[i].BeginningOfWordsList -> Prev = FoundNode;
				FoundNode -> Next = NumElement[i].BeginningOfWordsList;
				NumElement[i].BeginningOfWordsList = FoundNode;
				FoundNode -> Prev = NULL;
				return FoundNode -> Word;
			}
		}
	}
};
void NewWord(int IncFrequency, char *IncWord, char *IncNumericWord, NumWordNode *NumElement)
{
	int i = 0;
	bool WordWasntAdded = 1;
	while (NumElement[i].BeginningOfWordsList != NULL)
		if ( strcmp(NumElement[i].Num, IncNumericWord) == NULL )
		{
			NumElement[i].AddWord(IncFrequency, IncWord);

			WordWasntAdded = 0;
			break;
		}
		else
			i++;
	if (WordWasntAdded)
	{
		NumElement[i].AddWord(IncFrequency, IncWord);
		strcpy(NumElement[i].Num, IncNumericWord);
	}
};
int main()
{
	using namespace std;
	unsigned int i;								// Local variable that used to count the number of iteration;
	unsigned int NumberOfWords;
	int Frequency;
	NumWordNode *NumericWordsList;			// Pointer to the first element of numeric representations array;
	char CharWord[21], NumericWord[21], CurrentWord[21]/*, Result[100001]*/;
	char c;
	long NumberOfStars;
	//long CurrentResultPosition;
	scanf("%u", &NumberOfWords);				// Reading amount of words in the dictionary;
	NumericWordsList = (NumWordNode*) malloc (NumberOfWords * sizeof(NumWordNode));
	for(i = 0; i < NumberOfWords; i++)
		NumericWordsList[i].Prepare();
	for(i = 0; i < NumberOfWords; i++)
	{
		scanf("%s%d", CharWord, &Frequency);
		ToNumeric(CharWord, NumericWord);
		NewWord(Frequency, CharWord, NumericWord, NumericWordsList);
	}
	NumberOfStars = 0;
	//CurrentResultPosition = 0;
	i = 0;
	cin.get(c);
	cin.get(c);
	while( c != 13 )
	{
		if (c >= '2' &&  c <= '9')
		{
			CurrentWord [i] = c;
			i++;
			CurrentWord [i] = 0;
		}
		else if ( c  == '*' )
		{
			NumberOfStars = 1;
			cin.get(c);
			while ( c == '*')
			{
				NumberOfStars++;
				cin.get(c);
			}
			cin.putback (c);
			//CurrentResultPosition = CopyString (NumericWordsList -> FindWord(CurrentWord, NumberOfStars), Result, CurrentResultPosition);
			printf("%s", NumericWordsList -> FindWord(CurrentWord, NumberOfStars, NumericWordsList ));
			CurrentWord [0] = 0;
			NumberOfStars = 0;
			i = 0;
		}
		else if ( c == '1' )
		{
			CurrentWord [i] = 0;
			if ( CurrentWord [0] != 0)
				/*CurrentResultPosition = CopyString(NumericWordsList -> FindWord(CurrentWord, 0), Result, CurrentResultPosition);*/
				printf("%s", NumericWordsList -> FindWord(CurrentWord, NumberOfStars, NumericWordsList));
			CurrentWord [0] = 0;
			i = 0;
			cin.get(c);
			while ( c == 42 )
			{
				NumberOfStars++;
				cin.get(c);
			}
			cin.putback (c);			
			switch ( NumberOfStars % 3)
			{
			case 0:
				/*Result [CurrentResultPosition] = '.';
				Result [++CurrentResultPosition] = 0;*/
				printf(".");
				break;
			case 1:
				/*Result [CurrentResultPosition] = ',';
				Result [++CurrentResultPosition] = 0;*/
				printf(",");
				break;
			case 2:
				/*Result [CurrentResultPosition] = '?';
				Result [++CurrentResultPosition] = 0;*/
				printf("?");
				break;
			}
			NumberOfWords = 0;
		}
		else if ( c == 32 || c == 10)
		{
			if ( CurrentWord [0] != 0)
			{
				//CurrentResultPosition = CopyString(NumericWordsList -> FindWord(CurrentWord, NumberOfStars), Result, CurrentResultPosition);
				printf("%s", NumericWordsList -> FindWord(CurrentWord, NumberOfStars, NumericWordsList));
			}
			if (c == 32)
			{
				/*Result [CurrentResultPosition++] = ' ';
				Result [CurrentResultPosition] = 0;*/
				printf(" ");
			}
			NumberOfStars = 0;
			i = 0;
			CurrentWord [0] = 0;
			if (c == 10)
				break;
		}
		cin.get(c);
	}
	/*printf("%s", Result);*/
	//while ( NumericWordsList -> Next != NULL)
	//{
	//	NumericWordsList = NumericWordsList -> Next;
	//	delete NumericWordsList -> Prev;
	//}
	//delete NumericWordsList;
	//NumericWordsList = NULL;
	return 0;
}