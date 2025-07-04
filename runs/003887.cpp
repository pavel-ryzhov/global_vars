#include <stdio.h>
#include <string.h>
#include <map>

typedef const char cchar;
typedef unsigned int uint;
using namespace std;

// ---------------------------------------- WordRecord

struct WordRecord
{
	WordRecord():
		freq(0),
		usageMod(0),
		word(NULL)
	{
	}
	
	WordRecord(int _freq, int _usageMod, cchar* _word):
		freq(_freq),
		usageMod(_usageMod),
		word(_word)
	{
	}
	
	int freq;
	int usageMod;
	cchar* word;
};

bool operator <(const WordRecord& a, const WordRecord& b)
{
	// a less than b <=> a suggested first

	if (a.freq > b.freq) return true;
	if (a.freq < b.freq) return false;
	
	// a.freq == b.freq
	if (a.usageMod > b.usageMod) return true;
	if (a.usageMod < b.usageMod) return false;
	
	// a.freq == b.freq; a.usageMod == b.usageMod
	return (strcmp(a.word, b.word) < 0);	
}

// ----------------------------------------- TrieNode
class TrieNode
{
private:
	typedef map<WordRecord, cchar*> WordMap;
	
	TrieNode* children[9];
	WordMap words;
	int totalUsages;
	
public:
	TrieNode()
	{
		for (int i = 0; i<9; ++i)
			children[i] = NULL;
		totalUsages = 0;
	}
	
	TrieNode* GetChild(int digit)
	{
		if (children[digit-1])
			return children[digit-1];
		else
		{	
			children[digit-1] = new TrieNode;
			return children[digit-1];
		}
	}
	
	void InsertWord(cchar* word, int freq)
	{
		word = strdup(word);
		words[WordRecord(freq, 0, word)] = word;
	}
	
	cchar* GetAndUseWord(int variant)
	{
		// get current record
		WordMap::iterator wordIter = words.begin();
		advance(wordIter, variant);
		cchar* word = wordIter->second;
		// create new record
		WordRecord newRecord(wordIter->first.freq+1, ++totalUsages, wordIter->first.word);
		
		words.erase(wordIter);
		words[newRecord] = word;
		return word;		
	}
};

TrieNode root;

// ------------------------------------------- Walker

cchar* punct[] = {".", ",", "?"};	   
	  
int CharToDigit(char c)
{
	int alphaTable[] = {
		/*.,?*/      2, 2, 2,      3, 3, 3, 	
		4, 4, 4,     5, 5, 5,      6, 6, 6,  
		7, 7, 7, 7,  8, 8, 8,      9, 9, 9, 9
	};
	
	if (c >= 'a' && c <= 'z')
		return alphaTable[c-'a'];
	else
		return 1;
}

void InsertWord(cchar* word, int freq)
{
	TrieNode* node = &root;
	for (cchar* c = word; *c; ++c)
		node = node->GetChild(CharToDigit(*c));
		
	node->InsertWord(word, freq);
}

// RESET_STATE -- internal ExecQuery function
#define RESET_STATE\
	if (wordTyping) \
		printf("%s", node->GetAndUseWord(variant)); \
	if (punctTyping )\
		printf(punct[variant]); \
	wordTyping = false; \
	punctTyping = false; \
	variant = 0; \
	node = &root;
	
void ExecQuery(cchar* query)
{
	TrieNode* node = &root;
	int variant = 0;
	bool wordTyping = false;
	bool punctTyping = false;
	
	for (; *query; ++query)
	{
		switch (*query)
		{
			case '1':
				RESET_STATE;
				punctTyping = true;
				break;
								
			case ' ':
				RESET_STATE;
				printf(" ");
				break;
				
			case '*':
				// choose another variant
				variant++;
				break;
				
			default: /* case 2-9 */
				if (!wordTyping)
				{
					RESET_STATE;					
					wordTyping = true;
				}
				node = node->GetChild(*query-'0');
				break;
		}
	}
	RESET_STATE;
}

#undef RESET_STATE

// --------------------------------------------- Main

char query[100001];

int main()
{
	// read number of words
	int N;
	scanf("%i\n", &N);
	
	for (int i = 0; i<N; ++i)
	{
		// read a word
		char word[21];
		int freq;
		scanf("%s %i\n", word, &freq);
		InsertWord(word, freq);
	}
	
	InsertWord("", 1);
	
	// read and execute the query
	gets(query);
	ExecQuery(query);
	
	return 0;
}