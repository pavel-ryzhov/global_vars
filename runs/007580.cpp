// Problem C of Yandex lab entrance test
//
// (c) Andrei Anufriev, 2011.
//----------------------------------------------------------------------------
// Solution:
// 
// this is not an actual T9 algorithm
// but simplified one to solve exact problem specified (problem C)
// actual T9 algorith do the job for every key pressed;
// but here process word as a whole
//----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
//#include <exception>
//----------------------------------------------------------------------------
namespace p3 
{
//----------------------------------------------------------------------------
// if there is no assert by compiller
#ifndef _ASSERT
#define _ASSERT(a) {if (!(a)) {LE("Error! _ASSERT failed at line: "); LE(__LINE__);}}
#endif

// strict sizeof to arrays only, avoid pointers
template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];
#define arraysize(array) (sizeof(ArraySizeHelper(array)))
//----------------------------------------------------------------------------
// global types	
typedef std::string aStr;
typedef char aCh;

typedef aStr aWord;							// 1 <= word length <= 20
													// word: [a-z]

typedef std::map<aCh, aCh> MapLetterToKey;	// <letter, its key>

// TODO: rewrite to pointers to speedup
typedef std::list<aWord> ListOfWords;		// sorted on usage: last used will be in front

// <frequency, and list of words with this frequency>
// 0 <= frequency <= 1000
// sorted from 0 to 1000
typedef std::map<unsigned int, ListOfWords> MapFreqToWords;

// hash set is preferable here: <ext/hash_set> or <unordered_map>; not used for compatibility
// problem descriptioin states that always there will be at least one word for given keys;
// every word has the only one combination of keys
typedef std::map<aStr, MapFreqToWords> MapKeysToWord;
//----------------------------------------------------------------------------
// global consts
static const unsigned int gc_MaxFrequency = 1000;
static const aCh gc_PunctuationMarks [] = {'.', ',', '?'};
static const unsigned int gc_PunctMarksCount = arraysize(gc_PunctuationMarks);
//----------------------------------------------------------------------------
// global variables

// TODO: use Singleton design pattern if construction order does matter

static unsigned int g_NumberOfWords = 0;	// 3 <= N <= 50 000

static aStr g_CommandStr;					// the commands sequence; length <= 100 000

static MapLetterToKey g_LetterKey;			// <letter, its key>
static bool g_IsLetterKeyFilled = false;	// its guard for lean

static MapKeysToWord g_KeysWord;			// <keys sequence , available words for it>
//----------------------------------------------------------------------------
// helper functions to debug test cases on the ejudge site
static bool g_IsDebugPrint = true;
static void LE(const std::string & str)
{
	if (g_IsDebugPrint)
	{
		std::cerr << str << std::endl << std::flush;
	}
}
static void LE(char * str)
{
	if (g_IsDebugPrint)
	{
		std::cerr << str << std::endl << std::flush;
	}
}
static void LE(int v)
{
	if (g_IsDebugPrint)
	{
		std::cerr << v << std::endl << std::flush;
	}
}
//----------------------------------------------------------------------------
// fill the LetterKey global collection with letter -> key relations
static void FillTheLetterKey()
{
	if (!g_IsLetterKeyFilled)
	{
		g_LetterKey.insert(MapLetterToKey::value_type('a', '2'));
		g_LetterKey.insert(MapLetterToKey::value_type('b', '2'));
		g_LetterKey.insert(MapLetterToKey::value_type('c', '2'));

		g_LetterKey.insert(MapLetterToKey::value_type('d', '3'));
		g_LetterKey.insert(MapLetterToKey::value_type('e', '3'));
		g_LetterKey.insert(MapLetterToKey::value_type('f', '3'));

		g_LetterKey.insert(MapLetterToKey::value_type('g', '4'));
		g_LetterKey.insert(MapLetterToKey::value_type('h', '4'));
		g_LetterKey.insert(MapLetterToKey::value_type('i', '4'));

		g_LetterKey.insert(MapLetterToKey::value_type('j', '5'));
		g_LetterKey.insert(MapLetterToKey::value_type('k', '5'));
		g_LetterKey.insert(MapLetterToKey::value_type('l', '5'));
		
		g_LetterKey.insert(MapLetterToKey::value_type('m', '6'));
		g_LetterKey.insert(MapLetterToKey::value_type('n', '6'));
		g_LetterKey.insert(MapLetterToKey::value_type('o', '6'));
				
		g_LetterKey.insert(MapLetterToKey::value_type('p', '7'));
		g_LetterKey.insert(MapLetterToKey::value_type('q', '7'));
		g_LetterKey.insert(MapLetterToKey::value_type('r', '7'));
		g_LetterKey.insert(MapLetterToKey::value_type('s', '7'));

		g_LetterKey.insert(MapLetterToKey::value_type('t', '8'));
		g_LetterKey.insert(MapLetterToKey::value_type('u', '8'));
		g_LetterKey.insert(MapLetterToKey::value_type('v', '8'));
				
		g_LetterKey.insert(MapLetterToKey::value_type('w', '9'));
		g_LetterKey.insert(MapLetterToKey::value_type('x', '9'));
		g_LetterKey.insert(MapLetterToKey::value_type('y', '9'));
		g_LetterKey.insert(MapLetterToKey::value_type('z', '9'));
		
		g_IsLetterKeyFilled = true;
	}
}
//----------------------------------------------------------------------------
// for given letter return respective key (which is pressed on keyboard)
static aCh KeyFromLetter(aCh letter)
{
	FillTheLetterKey();			// lean; fill on first use
	return g_LetterKey[letter];
}
//----------------------------------------------------------------------------
// auxiliary function: extracted to avoid code dublication via copy-paste
// create a new list for the word and push to freuency - word collectioin
// this function assumes alphabetical order of words according to problem C description
static void PushWordToFreqWords(MapFreqToWords & fw, const aStr & word, unsigned int freq)
{
	ListOfWords tl;		// list of words contains only one word: this new word 

	// problem description states that words in test cases will be in alphabetical order
	// so push_back here is suitable for initial alphabetical order
	tl.push_back(word);
	fw.insert(MapFreqToWords::value_type(freq, tl));
}
//----------------------------------------------------------------------------
// push read word into collections 
// and do some preparations:
// 		* for this word calculate keys sequence
static void PushWord(const aStr & word, unsigned int freq)
{
	aStr Sequence;
	Sequence.reserve(word.length());
	for (unsigned int i = 0; i < word.length(); ++i)
	{
		Sequence += KeyFromLetter(word[i]);
	}

	MapKeysToWord::iterator it = g_KeysWord.find(Sequence);
	if (g_KeysWord.end() == it)	// if new keys sequence
	{
		// every word can has the only one sequence of keys:
		// so create collections
		
		// add new <sequence, words>
		MapFreqToWords fw;	// map Frequency - list of words: the only one word
		PushWordToFreqWords(fw, word, freq);
		g_KeysWord.insert(MapKeysToWord::value_type(Sequence, fw));
	}
	else	// some word(s) for this sequence of keys exist already
	{
		// (*it).second is MapFreqToWords &
		MapFreqToWords & fw = (*it).second;

		// lookup this frequency
		MapFreqToWords::iterator itThisFreq = fw.find(freq);
		if (fw.end() == itThisFreq)	// if there is no word with this frequency before
		{
			// create list of words for this frequency
			PushWordToFreqWords(fw, word, freq);
		}
		else	// there is a list of words for this frequency
		{
			// push this new word to the back of list of words for this frequency: 
			// rely on alphabetical order of input according to Problem C description
			ListOfWords & l = (*itThisFreq).second;
			l.push_back(word);
		}
	}
	
}
//----------------------------------------------------------------------------
// read all the input data to global variables
static void ReadInput()
{
	std::cin >> g_NumberOfWords;							// first line contains N

	aStr currWord;
	unsigned int currFreq;
	for (unsigned int i = 0; i < g_NumberOfWords; ++i)		// next N lines: <word, frequency> pairs
	{
		std::cin >> currWord >> currFreq;
		if (currFreq > gc_MaxFrequency)
		{
			// throw ...
			LE("Input error: Frequency is large than 1000!");
		}	
		PushWord(currWord, currFreq);
	}

	// command line (with spaces)
	while ((!std::cin.fail()) && (g_CommandStr.empty()))	// skip line break before the command line (if any)
		std::getline(std::cin, g_CommandStr);
}
//----------------------------------------------------------------------------
// return suitable word
// for given sequence of keys pressed
// 
// change frequency of this word in the g_KeysWord global collection
//
// according to the Problem C description: there will be always a word for any given sequence of keys
static aStr ProcessWordKeys(const aStr & Keys, unsigned int AsterixCount)
{
	aStr word;
	
	MapKeysToWord::iterator it = g_KeysWord.find(Keys);
	_ASSERT(it != g_KeysWord.end());		// always exists
	if (it != g_KeysWord.end())
	{
		MapFreqToWords & fw = (*it).second;	// all the words for this keys
		// get the largest frequency
		// <unsigned int, ListOfWords>
		MapFreqToWords::reverse_iterator itLargestFreqWords = fw.rbegin();
		_ASSERT(itLargestFreqWords != fw.rend());
		if (itLargestFreqWords != fw.rend())
		{
			unsigned int PrevFreq = (*itLargestFreqWords).first;
			ListOfWords * Words = &(*itLargestFreqWords).second;		// second is ListOfWords &
			_ASSERT(!Words->empty());
			
			// get the right word
			// last used word is first
			ListOfWords::iterator itWord = Words->begin();

			// handle asterisk(s) pressed
			for (unsigned int k = 0; k < AsterixCount; k++)
			{
				++itWord;
				if (Words->end() == itWord)	// cycle from first
				{
					++itLargestFreqWords;
					if (fw.rend() == itLargestFreqWords)
					{
						itLargestFreqWords = fw.rbegin();	// rewind to the largest
					}
					PrevFreq = (*itLargestFreqWords).first;
					Words = &(*itLargestFreqWords).second;	// second is ListOfWords &
					_ASSERT(!Words->empty());
					itWord =Words->begin();
				}
			}
			word = *itWord;
			
			// increment Frequency and move the word
			if (PrevFreq < gc_MaxFrequency)		// do nothing for the upper edge
			{
				Words->erase(itWord);			// remove word from this list
				if (Words->empty())				// check if empty list
				{								// remove the entire list for this previous frequency
					// convert const reverse iterator to forward one 
					MapFreqToWords::iterator itDel = --(itLargestFreqWords.base());
					fw.erase(itDel);
				}

				// push the word to new place respective to the new frequency
				unsigned int NewFreq = PrevFreq + 1;
				MapFreqToWords::iterator itNew = fw.find(NewFreq);
				if (itNew != fw.end())			// if there is already a word with this new frequency
				{
					Words = &(*itNew).second;
					Words->push_front(word);		// used word become the first word for a frequency
				}
				else	// add new collection for this frequency
				{
					PushWordToFreqWords(fw, word, NewFreq);
				}
			}
			else	// gc_MaxFrequency : 1000 is limit
			{
				// just move word within current frequency
				// to the first place
				Words->erase(itWord);
				Words->push_front(word);
			}
		}
	}

	_ASSERT(!word.empty());
	return word;
}
//----------------------------------------------------------------------------
// auxiliary helper function:
// for given id returns respective punctuation mark
static aCh GetPunctuationMark(int id)
{
	_ASSERT(id >= 0);
	_ASSERT(id < (int)gc_PunctMarksCount);
	if (id < 0)				// -1 stands for none
	{
		// throw std::exception("Error in algorithm: GetPunctuationMark(): id < 0");
		LE("Error in algorithm: GetPunctuationMark(): id < 0");
		LE(id);
		return '#';
	}
	return gc_PunctuationMarks[id];
}
//----------------------------------------------------------------------------
// auxiliary helper function:
// for given id return next id (incremented id)
// rewind to 0 in case of the upper edge
// handles case of initial -1 id (stants for none)
static int NextPunctuationMarkId(int id)
{
	_ASSERT(id < (int)gc_PunctMarksCount);
	int newId = id + 1;
	if (newId >= (int)gc_PunctMarksCount)
		newId = 0;
	return newId;
}
//----------------------------------------------------------------------------
// do the job
// for given sequence of keys pressed g_CommandStr 
// produce strings of words according to the Problem C rules
static aStr ProcessCommands()
{
	aStr Res;

	aStr CurrWordKeys;								// buffer to store current keys pressed that represent current word
	unsigned int CurrAsterixCount = 0;
	int idCurrPunctuationMark = -1;					// empty if there is no current punctuation mark
	for (unsigned int k = 0; k < g_CommandStr.length(); k++)	// for each key pressed
	{	
		switch (g_CommandStr[k])
		{
			case ' ':
			{
				if (idCurrPunctuationMark >= 0)		// if space after punctuation mark: push it first
				{									// push current punctuation mark to result
					Res += GetPunctuationMark(idCurrPunctuationMark);	
					idCurrPunctuationMark = -1;		// and clear

					_ASSERT(CurrWordKeys.empty());
				}
				else
				{
					if (!CurrWordKeys.empty())		// if space after a word or {word, asterisk}
					{
						Res += ProcessWordKeys(CurrWordKeys, CurrAsterixCount);
						CurrWordKeys.clear();
						CurrAsterixCount = 0;
					}
				}
				Res += g_CommandStr[k];				// += ' '
				break;
			}	// ...........................................................
			case '1':								// if punctuation mark
			{
				if (idCurrPunctuationMark >= 0)		// if there is previous punctuation mark: push it first
				{									// push current punctuation mark to result
					Res += GetPunctuationMark(idCurrPunctuationMark);	
					idCurrPunctuationMark = -1;

					_ASSERT(CurrWordKeys.empty());
				}
				else
				{
					if (!CurrWordKeys.empty())		// if punctuation mark after a word or {word, asterisk}
					{	// push this word first
						Res += ProcessWordKeys(CurrWordKeys, CurrAsterixCount);
						CurrWordKeys.clear();
						CurrAsterixCount = 0;
					}
				}
				
				// set the first punctuation mark as current
				idCurrPunctuationMark = NextPunctuationMarkId(idCurrPunctuationMark);	// -1 ===> 0
				break;
			}	// ...........................................................
			case '*':
			{
				if (idCurrPunctuationMark >= 0)		// if asterisk after punctuation mark: push it first
				{
					_ASSERT(CurrWordKeys.empty());
					_ASSERT(0 == CurrAsterixCount);
					idCurrPunctuationMark = NextPunctuationMarkId(idCurrPunctuationMark);
				}
				else
				{
					if (!CurrWordKeys.empty())		// if asterisk after a word 
					{
						CurrAsterixCount += 1;
					}
				}
				break;
			}	// ...........................................................


			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			{
				if (CurrAsterixCount > 0)			// if a letter after {word, asterks}
				{
					// this is not the original T9 algorithm!
					// do the job for Problem C

					// push previous word
					_ASSERT(!CurrWordKeys.empty());
					if (!CurrWordKeys.empty())
					{
						Res += ProcessWordKeys(CurrWordKeys, CurrAsterixCount);
					}
					CurrWordKeys.clear();
					CurrAsterixCount = 0;
				}
				
				if (idCurrPunctuationMark >= 0)		// if a letter after punctuation mark: push it first
				{
					_ASSERT(CurrWordKeys.empty());

					// push current pinctuation mark to result
					Res += GetPunctuationMark(idCurrPunctuationMark);
					idCurrPunctuationMark = -1;		// and clear
				}

				CurrWordKeys += g_CommandStr[k];
				break;
			}
			default:	// error!
			{
				aStr s = "Input error: Unknown key pressed! "; s += g_CommandStr[k];
				LE(s);
				break;
			}
		}
	}
	
	// push remains (if any)
	if (!CurrWordKeys.empty())
	{
		Res += ProcessWordKeys(CurrWordKeys, CurrAsterixCount);
		_ASSERT(idCurrPunctuationMark < 0);
	}
	if (idCurrPunctuationMark > -1)					// -1 stands for none
	{
		_ASSERT(CurrWordKeys.empty());
		_ASSERT(CurrAsterixCount == 0);
		Res += GetPunctuationMark(idCurrPunctuationMark);
	}

	return Res;
}
//----------------------------------------------------------------------------
}	// end of namespace p3
//----------------------------------------------------------------------------
int main(int argc, char * argv[])
{
	using namespace p3;

	ReadInput();		// read all the inputs
	aStr Result = ProcessCommands();
	std::cout << Result << std::endl;

	return 0;
}
//----------------------------------------------------------------------------
