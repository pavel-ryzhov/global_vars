#include <cstdio>
#include <cstring>
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

bool letter_button(char letter, char button)
{
	if((letter == 'a' || letter == 'b' || letter == 'c') && button == '2' || (letter == 'd' || letter == 'e' || letter == 'f') && button == '3' || 
		(letter == 'g' || letter == 'h' || letter == 'i') && button == '4' || (letter == 'j' || letter == 'k' || letter == 'l') && button == '5' ||
		(letter == 'm' || letter == 'n' || letter == 'o') && button == '6' || (letter == 'p' || letter == 'q' || letter == 'r' || letter == 's') && button == '7' || 
		(letter == 't' || letter == 'u' || letter == 'v') && button == '8' || (letter == 'x' || letter == 'y' || letter == 'w' || letter == 'z') && button == '9' )
	{
		return true;
	}
	return false;
}

class w_array
{
	int size;
public:
	
	word** dict_elements;

	w_array(int s, word** archive, int button, int code_numb)
	{
		size = 0;
		for(int i = 0; i < s; i++)
		{
			if( code_numb < (*(archive[i])).get_n() && (*(archive[i]))[code_numb] == button)
			{
				size++;
			}
		}

		if(size != 0)
		{	
			dict_elements = new word*[size];
			int count = 0;
			for(int i = 0; i < s; i++)
			{
				if(code_numb < (*(archive[i])).get_n() && (*(archive[i]))[code_numb] == button)
				{
					dict_elements[count++] = archive[i];
				}
			}
		}
	}
	int get_size()
	{
		return size;
	}
	void print_array()
	{
		for(int i = 0; i < size; i++)
		{
			printf("\n");
			dict_elements[i]->print_key();
			printf(" ");
			dict_elements[i]->print_word();
		}
	}
	void replace(word* w, int place)
	{
		word* help;
		for(int i = place - 1; i >= 0; i--)
		{
			if(dict_elements[i]->key <= w->key + 1)
			{
				help = dict_elements[i + 1];
				dict_elements[i + 1] = dict_elements[i];
				dict_elements[i] = help;
			}
			else
			{
				break;
			}
		}
	}
	void search_word(word* w, int begin, int part_size)
	{
		int half = (int)((part_size + begin)/2);
		if(dict_elements[half]->key < w->key)
		{
			search_word(w, 0, half);
		}
		else if(dict_elements[half]->key > w->key)
		{
			search_word(w, half, size);
		}
		else
		{
			if(dict_elements[half] == w)
			{
				replace(w, half);
			}
			else
			{	
				int j = half;
				while(j != 0 && dict_elements[j] != w && dict_elements[j]->key == w->key)
				{
					j--;
				}
				if(dict_elements[j] == w)
				{
					replace(w, j);
				}
				else
				{
					int j = half;
					while(j < size && dict_elements[j] != w && dict_elements[j]->key == w->key)
					{
						j++;
					}
					replace(w, j);
				}
			}
		}
	}
	void plusadin(word* w)
	{
		search_word(w, 0, size);
	}
};

class button_node
{
	int button;
	button_node* child_buttons[8];
public:
	
	w_array sorted_words;

	button_node(w_array w, int but, int code_numb) : sorted_words(w.get_size(), w.dict_elements, but, code_numb)
	{
		if(sorted_words.get_size() != 0)
		{
			button = but;
			for(int i = 2; i <= 9; i++)
			{
				child_buttons[i - 2] = new button_node(sorted_words, i, code_numb + 1);
			}
		}
		else
		{
			button = 0;
			for(int i = 0; i < 8; i++)
			{
				child_buttons[i] = NULL;
			}
		}
	}
	void plusadin(word* w, int level)
	{
		sorted_words.plusadin(w);
		if(level + 1 < w->get_n())
		{
			child_buttons[w->str_code[level + 1] - 2]->plusadin(w, level + 1);
		}
	}
	void print_node(int* code_array, int level)
	{
		if(button != 0)
		{
			printf("\n\n");
			code_array[level] = button;
			for(int i = 0; i <= level; i++)
			{
				printf("%i", code_array[i]);
			}
			sorted_words.print_array();
			for(int i = 0; i < 8; i++)
			{
				child_buttons[i]->print_node(code_array, level + 1);
			}
		}
	}
	word* get_word(int* code, int code_size, int numb, int level)
	{
		if(level == code_size - 1)
		{
			return sorted_words.dict_elements[numb];
		}
		else
		{
			return child_buttons[code[level + 1] - 2]->get_word(code, code_size, numb, level + 1);
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
		for(int i = 2; i <= 9; i++)
		{
			upper_buttons[i - 2] = new button_node(w_array::w_array(dsize, Dict, i, 0), i, 0);
		}
	}
	void plusadin(word* w)
	{
		upper_buttons[w->str_code[0] - 2]->plusadin(w, 0);
		w->key++;
	}
	void print_tree()
	{
		int codes[21];
		for(int i = 0; i < 8; i++)
		{
			upper_buttons[i]->print_node(codes, 0);
		}
	}
	void print_button(int i)
	{
		if(i >= 2 && i <= 9)
		{
			upper_buttons[i - 2]->sorted_words.print_array();
		}
	}
	void get_word(int* code, int code_size, int numb)
	{
		word* w = upper_buttons[code[0] - 2]->get_word(code, code_size, numb, 0);
		w->print_word();
		plusadin(w);
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
			Tree9.get_word(code, size, i);
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
