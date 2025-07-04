#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;

// Dictionary //

int button(char letter)
{
	switch(letter)
	{
	case 'a':
	case 'b':
	case 'c':
		return 2;
	case 'd':
	case 'e':
	case 'f':
		return 3;
	case 'h':
	case 'g':
	case 'i': 
		return 4;
	case 'j':
	case 'k':
	case 'l':
		return 5;
	case 'm':
	case 'n':
	case 'o':
		return 6;
	case 'p':
	case 'q':
	case 'r':
	case 's':
		return 7;
	case 't':
	case 'u':
	case 'v':
		return 8;
	case 'y':
	case 'w':
	case 'x':
	case 'z':
		return 9;
	default:
		return 0;
	}
}


class word
{
	int n;
public:
	
	int key;
	char str[21]; 
	int str_code[21];

	word()
	{
		n = 21;
	}
	int operator[] (int number)
	{
		if(number >= 0 && number <= 20)
		{
			return str_code[number];
		}
		else
		{
			return '\0';
		}
	}
	int get_n()
	{
		return n;
	}
	void print_word()
	{
		printf("%s", str);
	}
	void print_code()
	{
		for(int i = 0; i < n; i++)
		{
			printf("%i", str_code[i]);
		}
	}
	void print_key()
	{
		printf("%i", key);
	}
	void set_word(int n2, int k, char* str2)
	{
		n = n2;
		key = k;
		for(int i = 0; i < n; i++)
		{
			str[i] = str2[i];
			str_code[i] = button(str2[i]);
		}
	}
	void input_word()
	{
		scanf("%s %i", str, &key);
		n = strlen(str);
		for(int i = 0; i < n; i++)
		{
			str_code[i] = button(str[i]);
		}
	}
};

class dict
{
	int size;
public:
	word* archive;

	dict()
	{
		scanf("%i", &size);
		archive = new word[size];
	
		for(int i = 0; i < size; i++)
		{
			archive[i].input_word();
		}
		
	}
	int get_size()
	{
		return size;
	}
	void print_dict()
	{
		for(int i = 0; i < size; i++)
		{
			archive[i].print_word();
			printf(" ");
			archive[i].print_code();
		printf(" ");
			archive[i].print_key();
			printf("\n");
		}
	}
} Dictionary;


// Tree with a sorted lists of words //

class button_node
{
	int button;
	button_node* child_buttons[8];
public:
	int size;
	word** sorted_words;
	button_node(vector<word*> button_list, int but, int code_size)
	{
		int l_size = button_list.size();
		if(l_size != 0)
		{
			button = but + 2;
			vector<word*> help;
			word* help2;
			size = 0;
			for(int i = 0; i < l_size; i++)
			{
				help2 = button_list.back();
				if(help2->get_n() == code_size)
				{
					size++;
				}
				button_list.pop_back();
				help.push_back(help2);
			}
			sorted_words = new word*[size];
			vector<word*> button_arrays[8];
			int count = 0;
			for(int i = 0; i < l_size; i++)
			{
				help2 = help.back();
				help.pop_back();
				if(help2->get_n() == code_size)
				{
					sorted_words[count++] = help2;
				}
				else
				{
					button_arrays[help2->str_code[code_size] - 2].push_back(help2);
				}
			}
			for(int i = 0; i < 8; i++)
			{
				child_buttons[i] = new button_node(button_arrays[i], i, code_size + 1);
			}
		}
		else
		{
			button = 0;
			size = 0;
			sorted_words = NULL;
			for(int i = 0; i < 8; i++)
			{
				child_buttons[i] = NULL;
			}
		}
	}
	void print_node(int* code, int level)
	{
		if(button != 0)
		{
			printf("\n");
			for(int i = 0; i < level; i++)
			{
				printf("%i", code[i] + 2);
			}
			
			printf("\n");
			for(int i = 0; i < size; i++)
			{
				sorted_words[i]->print_key();
				printf(" ");
				sorted_words[i]->print_word();
				printf("\n");
			}
			for(int i = 0; i < 8; i++)
			{
				code[level] = i;
				child_buttons[i]->print_node(code, level + 1);
			}
		}
	}
	void plusadin(int* code, int code_size, int numb, int level)
	{
		if(level != code_size)
		{
			child_buttons[code[level] - 2]->plusadin(code, code_size, numb, level + 1);
		}
		else
		{
			word* w = sorted_words[numb];
			word* help;
			w->print_word();
			w->key++;
			for(int i = numb; i > 0; i--)
			{
				if(sorted_words[i - 1]->key <= w->key)
				{
					help = sorted_words[i - 1];
					sorted_words[i - 1] = sorted_words[i];
					sorted_words[i] = help;
				}
				else
				{
					break;
				}
			}
		}
	}
};

class button_tree
{
public:
	button_node* upper_buttons[8];
	button_tree(dict D)
	{
		int dsize;
		word** Dict = new word*[dsize = D.get_size()];
		for(int i = 0; i < dsize; i++)
		{
			Dict[i] = &(D.archive[i]);
		} 

		word* help = NULL;
		int k1, k2;
		for(int i = 0; i < dsize - 1; i++)
		{
			for(int j = dsize - 1; j > i; j--)
			{
				k1 = Dict[j]->key;
				k2 = Dict[j - 1]->key;
				if(k2 < k1)
				{
					help = Dict[j];
					Dict[j] = Dict[j - 1];
					Dict[j - 1] = help;
				}
			}
		}	
		vector<word*> dict_elements;
		word* help2;
		for(int i = dsize - 1; i >= 0; i--)
		{
			dict_elements.push_back(Dict[i]);
		}

		vector<word*> button_lists[8];
		for(int i = 0; i < dsize; i++)
		{
			help2 = dict_elements.back();
			button_lists[help2->str_code[0] - 2].push_back(help2);
			dict_elements.pop_back();
		}
		for(int i = 0; i < 8; i++)
		{
			upper_buttons[i] = new button_node(button_lists[i], i, 1);
		}
	}
	void print_tree()
	{
		int codes[21];
		for(int i = 0; i < 8; i++)
		{
			codes[0] = i;
			upper_buttons[i]->print_node(codes, 1);
		}
	}
	void plusadin(int* code, int code_size, int numb)
	{
		upper_buttons[code[0] - 2]->plusadin(code, code_size, numb, 1);
	}
} Tree9(Dictionary);

// Parse a string //

void parse()
{
	char c;
	int* code = new int[21];
	do
	{
		scanf("%c", &c);
	}
	while(c != ' ' &&  (c < '1' || c > '9'));
	
 	while(c != EOF && c != 26 && c != 10)
	{
		if(c >= '2' && c <= '9')
		{
			int size = 0;
			int i = 0;
			while(c >= '2' && c <= '9')
			{
				code[size] = c - '0';
				size++;
				scanf("%c", &c);
			}
			while(c == '*')
			{
				i++;
				scanf("%c", &c);
			}
			Tree9.plusadin(code, size, i);
		}
		else if(c == ' ')
		{
			printf("%c", c);
			scanf("%c", &c);
		}
		else if(c == '1')
		{
			int i = 0;
			scanf("%c", &c);
			while(c == '*')
			{
				i++;
				scanf("%c", &c);
			}
			i = i % 3;
			switch(i)
			{
			case 0:
				printf("%c", '.');
				break;
			case 1:
				printf("%c", ',');
				break;
			case 2:
				printf("%c", '?');
				break;
			}
		}
		else
		{
			scanf("%c", &c);
		}
	}
}

int main() 
{
	parse();
	return 0;
}
