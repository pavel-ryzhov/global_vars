#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
using namespace std;

class word
{
	public:
	word * next_word;
	char text[21];

	word(const char txt[21])
	{
		strcpy(text,txt);
		next_word = NULL;
	}
};

class word_block
{
	public:
	int frequency;
	int number_of_words;
	word * first;
	word * last;
	word_block * next_block;

	word_block(word * word_to_initialize, int freq, word_block * next_blk = NULL )
	{
		frequency = freq;
		number_of_words = 1;
		first = word_to_initialize;
		last = word_to_initialize;
		next_block =  next_blk;
	}
	word_block(){}
};

struct classcomp
{
	bool operator() (const char left[21], const char right[21]) const
	{
		if (strcmp(left, right) < 0 ) return true;
		else return false;
	}
};

map<char *, word_block *, classcomp> dictionary;

void get_T9_repr(char * text_of_word)
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

void add_word_to_the_one_of_word_blocks(word_block ** pt_ancestor, word_block * block_to_add)
{
	int cur_freq = block_to_add->frequency;

	if( (*pt_ancestor)->frequency < cur_freq )
	{
		block_to_add->next_block = (*pt_ancestor);
		(*pt_ancestor) = block_to_add;
		return;
	}

	word_block * ancestor_word_block = (*pt_ancestor);

	if( cur_freq == ancestor_word_block->frequency)
	{
		ancestor_word_block->last->next_word = block_to_add->first;
		ancestor_word_block->number_of_words++;
		ancestor_word_block->last = block_to_add->first;
		return;
    }

	while(ancestor_word_block->next_block != NULL)
	{
		if(ancestor_word_block->next_block->frequency == cur_freq)
		{
			ancestor_word_block->next_block->last->next_word = block_to_add->first;
			ancestor_word_block->next_block->number_of_words++;
			ancestor_word_block->last = block_to_add->first;
			return;
		}
		if(ancestor_word_block->next_block->frequency < cur_freq) break;
		ancestor_word_block = ancestor_word_block->next_block;
	}

	block_to_add->next_block = ancestor_word_block->next_block;
	ancestor_word_block->next_block = block_to_add;
}

void add_word_to_certain_position_to_new_block(word_block** prev_block, word * word_to_add, int freq)
{
	word_block * new_word_block = new word_block(word_to_add,freq,(*prev_block));
	word_to_add->next_word = NULL;
	(*prev_block) = new_word_block;
}

void find_and_print_the_word(char number_repr[21], int num_of_skips)
{
	map<char *, word_block *, classcomp>::iterator it = dictionary.find(number_repr);

	word_block * cur_word_block = it->second;
	int num_of_words_in_prev_blocks = cur_word_block->number_of_words;

	if( num_of_skips < num_of_words_in_prev_blocks)// to est slovo v pervom bloke
	{
		word * cur_word = cur_word_block->first;
		if( cur_word_block->number_of_words == 1)
		{
			cout<<cur_word->text;
			cur_word_block->frequency++;
			return;
		}

		if(num_of_skips == 0)
		{
			cout<<cur_word->text;
			cur_word_block->number_of_words--;
			cur_word_block->first = cur_word->next_word;
			add_word_to_certain_position_to_new_block(&(it->second),cur_word,cur_word_block->frequency+1);
			return;
		}
		num_of_skips--;// ishem predka
		while(num_of_skips>0)
		{
			cur_word = cur_word->next_word;
			num_of_skips--;
		}
		cout<<cur_word->next_word->text;
		cur_word_block->number_of_words--;

		word * word_to_add = cur_word->next_word;

		cur_word->next_word = word_to_add->next_word;
		add_word_to_certain_position_to_new_block(&(it->second),word_to_add,cur_word_block->frequency+1);
		return;
	}

	// Nahodim block v kotorom nujmoe slovo
	num_of_words_in_prev_blocks += cur_word_block->next_block->number_of_words;

	while( num_of_words_in_prev_blocks  <= num_of_skips )
	{
		cur_word_block = cur_word_block->next_block;
		num_of_words_in_prev_blocks += cur_word_block->next_block->number_of_words;
	}
	word_block * block_with_word = cur_word_block->next_block;

	num_of_words_in_prev_blocks-=block_with_word->number_of_words;

	word * cur_word = block_with_word->first;
	if( block_with_word->number_of_words == 1)
	{
		cout<<cur_word->text;
		if(cur_word_block->frequency == block_with_word->frequency + 1)
		{
			cur_word->next_word = cur_word_block->first;
			cur_word_block->first = cur_word;
			cur_word_block->number_of_words++;
			cur_word_block->next_block = block_with_word->next_block;
			return;
		}
		block_with_word->frequency++;
		return;
	}


	if( num_of_words_in_prev_blocks == num_of_skips )
	{
		cout<<cur_word->text;
		block_with_word->number_of_words--;
		block_with_word->first = cur_word->next_word;

		if(cur_word_block->frequency == block_with_word->frequency + 1)
		{
			cur_word->next_word = cur_word_block->first;
			cur_word_block->first = cur_word;
			cur_word_block->number_of_words++;
			return;
		}

		add_word_to_certain_position_to_new_block(&(cur_word_block->next_block),cur_word, block_with_word->frequency+1);
		return;
	}

	num_of_words_in_prev_blocks++;// teper v cur_worde budet predok nujnogo slova
	while( num_of_words_in_prev_blocks < num_of_skips)
	{
		cur_word = cur_word->next_word;
		num_of_words_in_prev_blocks++;
	}

	word * word_to_add = cur_word->next_word;

	cout<<word_to_add->text;
	block_with_word->number_of_words--;
	cur_word->next_word = word_to_add->next_word;

	if(cur_word_block->frequency == block_with_word->frequency + 1)
	{
		word_to_add->next_word = cur_word_block->first;
		cur_word_block->first = word_to_add;
		cur_word_block->number_of_words++;
		return;
	}
	add_word_to_certain_position_to_new_block(&(cur_word_block->next_block),word_to_add, block_with_word->frequency+1);
}


int main()
{
	int N;
	pair< map<char *, word_block *, classcomp>::iterator, bool> ret;

	cin>>N;
	char text_of_word[21];
	int frequency_of_word;
	for(int i = 0; i<N;i++)
	{
		getchar();
		cin.getline(text_of_word,21,' ');
		cin>>frequency_of_word;

		word * new_word = new word(text_of_word);
		get_T9_repr(text_of_word); // now contains number

		char * number_repr = new char[21];
		strcpy(number_repr, text_of_word);

		word_block * new_word_block = new word_block(new_word, frequency_of_word);

		pair<char *, word_block *> dictionary_entry(number_repr, new_word_block);

		ret = dictionary.insert(dictionary_entry);
		if(ret.second==false)
			add_word_to_the_one_of_word_blocks(&(*ret.first).second, new_word_block);
	}
	getchar();

	char slovo[21];

	int cur_char = getchar();
	while(cur_char != '\n')
	{
		switch(cur_char)
		{
			case '1':
			{
				cur_char = getchar();
				if(cur_char == '*')
				{
					cur_char = getchar();
					if(cur_char == '*')
					{
						cout<<'?';
						cur_char = getchar();
					}
					else cout<<',';
				}
				else cout<<'.';
				break;
			}
			case ' ':
			{
				cout<<' ';
				cur_char = getchar();
				break;
			}
			default:
			{
				slovo[0] = cur_char;
				int num_of_skips = 0;

				cur_char = getchar();
				int i;
				for(i=1;cur_char != '1' && cur_char != ' ' && cur_char != '\n' && cur_char != '*';i++)
				{
					slovo[i] = cur_char;
					cur_char = getchar();
				}
				slovo[i] = '\0';

				while(cur_char =='*')
				{
					num_of_skips++;
					cur_char = getchar();
				}
				find_and_print_the_word(slovo, num_of_skips);
			}
		}
	}
	return 0;
}