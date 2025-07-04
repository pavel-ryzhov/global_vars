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
	int frequency;

	word(const char txt[21], int freq)
	{
		strcpy(text,txt);
		frequency = freq;
		next_word = NULL;
	}
};

struct classcomp
{
	bool operator() (const char left[21], const char right[21]) const
	{
		if (strcmp(left, right) < 0 ) return true;
		else return false;
	}
};

map<char *, word *, classcomp> dictionary;

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

void add_word_to_the_list(word ** pt_ancestor, word * word_to_add)
{
	int cur_freq = word_to_add->frequency;

	if( (*pt_ancestor)->frequency < cur_freq )
	{
		word_to_add->next_word = (*pt_ancestor);
		(*pt_ancestor) = word_to_add;
		return;
	}

	word * ancestor_word = (*pt_ancestor);
	while(ancestor_word->next_word != NULL)
	{
		if(ancestor_word->next_word->frequency < cur_freq) break;		
		ancestor_word = ancestor_word->next_word;
	}
	
	word_to_add->next_word = ancestor_word->next_word;
	ancestor_word->next_word = word_to_add;
}

void change_word_position(word ** pt_ancestor, word * word_to_change)
{
	int cur_freq = word_to_change->frequency;

	if( (*pt_ancestor)->frequency <= cur_freq )
	{
		word_to_change->next_word = (*pt_ancestor);
		(*pt_ancestor) = word_to_change;
		return;
	}

	word * ancestor_word = (*pt_ancestor);
	while(ancestor_word->next_word != NULL)
	{
		if(ancestor_word->next_word->frequency <= cur_freq) break;		
		ancestor_word = ancestor_word->next_word;
	}
	
	word_to_change->next_word = ancestor_word->next_word;
	ancestor_word->next_word = word_to_change;
}

void find_and_print_the_word(char number_repr[21], int num_of_skips)
{
	map<char *, word *, classcomp>::iterator it = dictionary.find(number_repr);
	
	word * cur_word = it->second;

	if(num_of_skips == 0)
	{
		cout<<cur_word->text;
		cur_word->frequency++;
		return;
	}

	for(int i=0; i<num_of_skips - 1; i++) cur_word = cur_word->next_word;
	word * word_to_print = cur_word->next_word;
	cout<<word_to_print->text;

	if( cur_word->frequency - word_to_print->frequency > 1)
	{
		word_to_print->frequency++;
		return;
	}

	cur_word->next_word = word_to_print->next_word;

	word_to_print->frequency++;
	word_to_print->next_word = NULL;

	change_word_position(&(it->second), word_to_print);
}


int main()
{
	int N;
	pair< map<char *, word *, classcomp>::iterator, bool> ret;

	cin>>N;
	char text_of_word[21];
	int frequency_of_word;
	for(int i = 0; i<N;i++)
	{
		getchar();
		cin.getline(text_of_word,21,' ');
		cin>>frequency_of_word;

		word * new_word = new word(text_of_word, frequency_of_word);
		get_T9_repr(text_of_word); // now contains number

		char * number_repr = new char[21];
		strcpy(number_repr, text_of_word);

		pair<char *, word *> dictionary_entry(number_repr, new_word);

		ret = dictionary.insert(dictionary_entry);
		if(ret.second==false) add_word_to_the_list(&(*ret.first).second, new_word);
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