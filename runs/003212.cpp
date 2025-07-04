#include <iostream>
#include <map>
#include <stdio.h>
#include <string>

using namespace std;
class word
{
	public:
	word * next_word;
	string text;
	int frequency;

	word(const string & txt, int freq)
	{
		text = txt;
		frequency = freq;
		next_word = NULL;
	}
};

struct classcomp
{
	bool operator() (const string & left, const string & right) const
	{
		if (left.compare(right) < 0 ) return true;
		else return false;
	}
};

map<string, word *, classcomp> dictionary;

string get_T9_repr(const string & text_of_word)
{
	string T9_repr;
	for(unsigned int i=0; i<text_of_word.size();i++)
	{
		switch(text_of_word[i])
		{
			case 'a': T9_repr+='2';break;
			case 'b': T9_repr+='2';break;
			case 'c': T9_repr+='2';break;
			case 'd': T9_repr+='3';break;
			case 'e': T9_repr+='3';break;
			case 'f': T9_repr+='3';break;
			case 'g': T9_repr+='4';break;
			case 'h': T9_repr+='4';break;
			case 'i': T9_repr+='4';break;
			case 'j': T9_repr+='5';break;
			case 'k': T9_repr+='5';break;
			case 'l': T9_repr+='5';break;
			case 'm': T9_repr+='6';break;
			case 'n': T9_repr+='6';break;
			case 'o': T9_repr+='6';break;
			case 'p': T9_repr+='7';break;
			case 'q': T9_repr+='7';break;
			case 'r': T9_repr+='7';break;
			case 's': T9_repr+='7';break;
			case 't': T9_repr+='8';break;
			case 'u': T9_repr+='8';break;
			case 'v': T9_repr+='8';break;
			case 'w': T9_repr+='9';break;
			case 'x': T9_repr+='9';break;
			case 'y': T9_repr+='9';break;
			case 'z': T9_repr+='9';
		}	
	}
	return T9_repr;
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

void find_and_print_the_word(const string & number_repr, int num_of_skips)
{
	map<string, word *, classcomp>::iterator it = dictionary.find(number_repr);
	
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
	pair< map<string, word *, classcomp>::iterator, bool> ret;

	cin>>N;
	string text_of_word;
	int frequency_of_word;
	for(int i = 0; i<N;i++)
	{
    	getchar();
		getline(cin,text_of_word,' ');
		cin>>frequency_of_word;

		word * new_word = new word(text_of_word, frequency_of_word);
		string key = get_T9_repr(text_of_word);
		pair<string,word *> dictionary_entry(key,new_word);
		ret = dictionary.insert(dictionary_entry);
		if(ret.second==false) add_word_to_the_list(&(*ret.first).second, new_word);
	}
	getchar();
	string cur_str;
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
				cur_str = cur_char;
				int num_of_skips = 0;
				
				cur_char = getchar();
				while(cur_char == '2' ||
						cur_char == '3' ||
						cur_char == '4' ||
						cur_char == '5' ||
						cur_char == '6' ||
						cur_char == '7' ||
						cur_char == '8' ||
						cur_char == '9')
				{
					cur_str+=cur_char;
					cur_char = getchar();
				}
				
				while(cur_char =='*')
				{
					num_of_skips++;
					cur_char = getchar();
				}
				find_and_print_the_word(cur_str, num_of_skips);
			}
		}
	}
}