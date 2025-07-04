#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>

using std::map;
using std::cout;
using std::cin;
using std::pair;

class word
{
	public:
	word * NextWord;
	char text[21];

	word(const char txt[21])
	{
		strcpy(text,txt);
		NextWord = NULL;
	}
};

class WordSequence
{
	public:
	int frequency;
	int WordCount;
	word * first;
	word * last;
	WordSequence * next_block;

	WordSequence(word * word_to_initialize, int freq, WordSequence * next_blk = NULL )
	{
		frequency = freq;
		WordCount = 1;
		first = word_to_initialize;
		last = word_to_initialize;
		next_block =  next_blk;
	}
	WordSequence(){}
};

struct ClassComparison
{
	bool operator() (const char left[21], const char right[21]) const
	{
		if (strcmp(left, right) < 0 ) return true;
		else return false;
	}
};

map <char *, WordSequence *, ClassComparison> dictionary;

void GetTView(char * text_of_word)
{
	for(int i=0; text_of_word[i]!='\0';i++)
	{
		if(text_of_word[i] < 115)
		{
			text_of_word[i] = ((text_of_word[i] - 97) / 3) + 50;
			continue;
		}
		else
		{
			switch(text_of_word[i])
			{
             	case 's': text_of_word[i]='7';break;
				case 't': text_of_word[i]='8';break;
				case 'u': text_of_word[i]='8';break;
				case 'v': text_of_word[i]='8';break;
				case 'w': text_of_word[i]='9';break;
				case 'x': text_of_word[i]='9';break;
				case 'y': text_of_word[i]='9';break;
				case 'z': text_of_word[i]='9';
            }
		}
	}
}

void AddWordToWordSequences(WordSequence ** pt_ancestor, WordSequence * block_to_add)
{
	int Currentfreq = block_to_add->frequency;

	if( (*pt_ancestor)->frequency < Currentfreq )
	{
		block_to_add->next_block = (*pt_ancestor);
		(*pt_ancestor) = block_to_add;
		return;
	}

	WordSequence * ancestor_WordSequence = (*pt_ancestor);

	if( Currentfreq == ancestor_WordSequence->frequency)
	{
		ancestor_WordSequence->last->NextWord = block_to_add->first;
		ancestor_WordSequence->WordCount++;
		ancestor_WordSequence->last = block_to_add->first;
		return;
    }

	while(ancestor_WordSequence->next_block != NULL)
	{
		if(ancestor_WordSequence->next_block->frequency == Currentfreq)
		{
			ancestor_WordSequence->next_block->last->NextWord = block_to_add->first;
			ancestor_WordSequence->next_block->WordCount++;
			ancestor_WordSequence->next_block->last = block_to_add->first;
			return;
		}
		if(ancestor_WordSequence->next_block->frequency < Currentfreq) break;
		ancestor_WordSequence = ancestor_WordSequence->next_block;
	}

	block_to_add->next_block = ancestor_WordSequence->next_block;
	ancestor_WordSequence->next_block = block_to_add;
}

void AddAtCertain(WordSequence** prev_block, word * word_to_add, int freq)
{
	WordSequence * new_WordSequence = new WordSequence(word_to_add,freq,(*prev_block));
	word_to_add->NextWord = NULL;
	(*prev_block) = new_WordSequence;
}

void WordSearchPrint(char number_repr[21], int num_of_skips)
{
	map<char *, WordSequence *, ClassComparison>::iterator it = dictionary.find(number_repr);

	WordSequence * CurrentWordSequence = it->second;
	int num_of_words_in_prev_blocks = CurrentWordSequence->WordCount;

	if( num_of_skips < num_of_words_in_prev_blocks)// to est slovo v pervom bloke
	{
		word * Currentword = CurrentWordSequence->first;
		if( CurrentWordSequence->WordCount == 1)
		{
			cout<<Currentword->text;
			CurrentWordSequence->frequency++;
			return;
		}

		if(num_of_skips == 0)
		{
			cout<<Currentword->text;
			CurrentWordSequence->WordCount--;
			CurrentWordSequence->first = Currentword->NextWord;
			AddAtCertain(&(it->second),Currentword,CurrentWordSequence->frequency+1);
			return;
		}
		num_of_skips--;
		while(num_of_skips>0)
		{
			Currentword = Currentword->NextWord;
			num_of_skips--;
		}
		cout<<Currentword->NextWord->text;
		CurrentWordSequence->WordCount--;

		word * word_to_add = Currentword->NextWord;

		Currentword->NextWord = word_to_add->NextWord;
		AddAtCertain(&(it->second),word_to_add,CurrentWordSequence->frequency+1);
		return;
	}

	num_of_words_in_prev_blocks += CurrentWordSequence->next_block->WordCount;

	while( num_of_words_in_prev_blocks  <= num_of_skips )
	{
		CurrentWordSequence = CurrentWordSequence->next_block;
		num_of_words_in_prev_blocks += CurrentWordSequence->next_block->WordCount;
	}
	WordSequence * block_with_word = CurrentWordSequence->next_block;

	num_of_words_in_prev_blocks-=block_with_word->WordCount;

	word * Currentword = block_with_word->first;
	if( block_with_word->WordCount == 1)
	{
		cout<<Currentword->text;
		if(CurrentWordSequence->frequency == block_with_word->frequency + 1)
		{
			Currentword->NextWord = CurrentWordSequence->first;
			CurrentWordSequence->first = Currentword;
			CurrentWordSequence->WordCount++;
			CurrentWordSequence->next_block = block_with_word->next_block;
			return;
		}
		block_with_word->frequency++;
		return;
	}


	if( num_of_words_in_prev_blocks == num_of_skips )
	{
		cout<<Currentword->text;
		block_with_word->WordCount--;
		block_with_word->first = Currentword->NextWord;

		if(CurrentWordSequence->frequency == block_with_word->frequency + 1)
		{
			Currentword->NextWord = CurrentWordSequence->first;
			CurrentWordSequence->first = Currentword;
			CurrentWordSequence->WordCount++;
			return;
		}

		AddAtCertain(&(CurrentWordSequence->next_block),Currentword, block_with_word->frequency+1);
		return;
	}

	num_of_words_in_prev_blocks++;// teper v Currentworde budet predok nujnogo slova
	while( num_of_words_in_prev_blocks < num_of_skips)
	{
		Currentword = Currentword->NextWord;
		num_of_words_in_prev_blocks++;
	}

	word * word_to_add = Currentword->NextWord;

	cout<<word_to_add->text;
	block_with_word->WordCount--;
	Currentword->NextWord = word_to_add->NextWord;

	if(CurrentWordSequence->frequency == block_with_word->frequency + 1)
	{
		word_to_add->NextWord = CurrentWordSequence->first;
		CurrentWordSequence->first = word_to_add;
		CurrentWordSequence->WordCount++;
		return;
	}
	AddAtCertain(&(CurrentWordSequence->next_block),word_to_add, block_with_word->frequency+1);
}


int main()
{
	int N;
	pair< map<char *, WordSequence *, ClassComparison>::iterator, bool> ret;

	cin>>N;
	char text_of_word[21];
	int frequency_of_word;
	for(int i = 0; i<N;i++)
	{
		getchar();
		cin.getline(text_of_word,21,' ');
		cin>>frequency_of_word;

		word * new_word = new word(text_of_word);
		GetTView(text_of_word); // now contains number

		char * number_repr = new char[21];
		strcpy(number_repr, text_of_word);

		WordSequence * new_WordSequence = new WordSequence(new_word, frequency_of_word);

		pair<char *, WordSequence *> dictionary_entry(number_repr, new_WordSequence);

		ret = dictionary.insert(dictionary_entry);
		if(ret.second==false)
			AddWordToWordSequences(&(*ret.first).second, new_WordSequence);
	}
	getchar();

	char slovo[21];

	int Currentchar = getchar();
	while(Currentchar != '\n')
	{
		switch(Currentchar)
		{
			case '1':
			{
				Currentchar = getchar();
				if(Currentchar == '*')
				{
					Currentchar = getchar();
					if(Currentchar == '*')
					{
						cout<<'?';
						Currentchar = getchar();
					}
					else cout<<',';
				}
				else cout<<'.';
				break;
			}
			case ' ':
			{
				cout<<' ';
				Currentchar = getchar();
				break;
			}
			default:
			{
				slovo[0] = Currentchar;
				int num_of_skips = 0;

				Currentchar = getchar();
				int i;
				for(i=1;Currentchar != '1' && Currentchar != ' ' && Currentchar != '\n' && Currentchar != '*';i++)
				{
					slovo[i] = Currentchar;
					Currentchar = getchar();
				}
				slovo[i] = '\0';

				while(Currentchar =='*')
				{
					num_of_skips++;
					Currentchar = getchar();
				}
				WordSearchPrint(slovo, num_of_skips);
			}
		}
	}
	return 0;
}