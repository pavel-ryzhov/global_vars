#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

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

typedef struct Node_
{
	struct Node_ * left;
	struct Node_ * right;
	struct Node_ * parent;

	char key[21];
	word * first_word;

} Node;

Node * root = NULL;

Node * insertNode(const char * key, word * word_to_insert)
{
	Node * x, * current, * parent;

	current = root;
	parent = 0;
	while (current)
	{
		if (strcmp(key, current->key) == 0) return (current);
		parent = current;
		current = (strcmp(key, current->key)<0)? current->left : current->right;
    }

	x = (Node *)malloc (sizeof(*x));

	strcpy(x->key, key);

	x->parent = parent;
	x->left = NULL;
	x->right = NULL;
	x->first_word = word_to_insert;

	if(parent)
	{
		if(strcmp(x->key, parent->key) < 0) parent->left = x;
		else parent->right = x;
	}
	else
		root = x;

	return NULL;
}

Node * findNode(const char * key)
{
	Node * current = root;
	while(current != NULL)
	{
		if(strcmp(key, current->key)==0)
			return current;
		else
			current = (strcmp(key, current->key) < 0) ? current->left : current->right;
	}
	return NULL;
}

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
	Node * node = findNode(number_repr);

	word * cur_word = node->first_word;

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

	change_word_position(&(node->first_word), word_to_print);
}

int main()
{
	int N;

	cin>>N;
	char text_of_word[21];
	int frequency_of_word;
	Node * node;
	for(int i = 0; i<N;i++)
	{
		getchar();
		cin.getline(text_of_word,21,' ');
		cin>>frequency_of_word;

		word * new_word = new word(text_of_word, frequency_of_word);
		get_T9_repr(text_of_word); // now contains number


		node = insertNode(text_of_word, new_word);
		if(node != NULL) add_word_to_the_list(&(node->first_word), new_word);
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