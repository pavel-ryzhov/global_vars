#include<iostream>
#include<map>
#include<cstring>
#include<vector>
#include<stdlib.h>
unsigned int N;
// Дальше разбор строки! создать массив, в котором будут номера слова в словаре!
struct Word
{
	std::string str;
	unsigned int freq;
	Word(std::string s= "", unsigned int f = 0):str(s), freq(f){};
};
struct Identific
{
	std::string code;
	std::vector<unsigned int> ways;
};
std::map <char,char> buttons;
std::vector <Identific> interp;
std::vector <unsigned int> message;
Word words[50004];
void fillBut()
{
	char i = 'a';
	char j = '2';
	while ( i <= 'c')
	{
		buttons.insert(std::make_pair(i,j));
		i++;
	}
	j++;
	while ( i <= 'f')
	{
		buttons.insert(std::make_pair(i,j));
		i++;
	}
	j++;
	while ( i <= 'i')
	{
		buttons.insert(std::make_pair(i,j));
		i++;
	}
	j++;
	while ( i <= 'l')
	{
		buttons.insert(std::make_pair(i,j));
		i++;
	}
	j++;
	while ( i <= 'o')
	{
		buttons.insert(std::make_pair(i,j));
		i++;
	}
	j++;
	while ( i <= 's')
	{
		buttons.insert(std::make_pair(i,j));
		i++;
	}
	j++;
	while ( i <= 'v')
	{
		buttons.insert(std::make_pair(i,j));
		i++;
	}
	j++;
	while ( i <= 'z')
	{
		buttons.insert(std::make_pair(i,j));
		i++;
	}
	Identific d;
	d.code = "1";
	unsigned int k = 0;
	Word sym( " ", 0 );
	words[k] = sym;
	k++;
	sym.str=".";
	words[k] = sym;
	d.ways.push_back(k);
	k++;
	sym.str=",";
	words[k] = sym;
	d.ways.push_back(k);
	k++;
	sym.str="?";
	words[k] = sym;
	d.ways.push_back(k);
	interp.push_back(d);
}

void getWords()
{
	for( unsigned int i = 0; i < N; i++)
	{
		std::string s="";
		Word w;
		char*c=new char [20];
		std::cin.getline( c, 21, ' ');
		w.str = c;
		for( unsigned int j =0; j < w.str.length(); j++ )
			s.push_back(buttons.find(w.str[j])->second);
		std::cin.getline( c, 5, '\n');
		w.freq = atoi( c );
		words[i+4] = w;
		delete[]c;
		std::vector<Identific>::iterator iter = interp.begin()+1;
		while( iter != interp.end())
			if ( s.compare(iter->code) )
				iter++;
			else 
				break;
		if ( iter != interp.end() )
		{
			std::vector<unsigned int>::iterator w = iter->ways.begin();
			while( w != iter->ways.end() && words[*w].freq >= words[i+4].freq )
				w++;
			if ( w != iter->ways.end() )
				iter->ways.insert( w, i+4 );
			else
				iter->ways.push_back( i+4 );
		}
		else
		{
			Identific d;
			d.code = s;
			d.ways.push_back( i+4 );
			interp.push_back( d );
		}
	}
}


void printMessage()
{
	for( std::vector<unsigned int>::iterator iter = message.begin(); iter != message.end(); iter++ )
		std::cout<< words[*iter].str.c_str();
	std::cout<<std::endl;
}
void getMessage()
{
	char currentChar;
	std::cin.get( currentChar );
	std::string buf = "";
	unsigned int i=0;
	enum State { BEGIN, NUMBER, DELIM, SPACE, STOP, SHIFT, FIND, FINDS, END };
		State currentState = BEGIN;
		bool cond = true;
	while(cond)
		switch(currentState) {
			case BEGIN:
				if ( currentChar >= '2' && currentChar <= '9')
				{
					buf.push_back( currentChar );
					std::cin.get( currentChar );
					currentState = NUMBER;
				}
				else
					currentState = DELIM;
				break;
			case DELIM:
				if ( currentChar == ' ')
				{
					message.push_back(0);
					std::cin.get( currentChar );
					currentState = SPACE;
				}
				else if ( currentChar == '1' )
				{
					std::cin.get( currentChar );
					currentState = STOP;
				}
				else
					currentState = END;
				break;
			case NUMBER:
				if ( currentChar >= '2' && currentChar <= '9' )
				{
					buf.push_back( currentChar );
					std::cin.get( currentChar );
					currentState = NUMBER;
				}
				else if ( currentChar == '*' )
				{
					i++;
					std::cin.get( currentChar );
					currentState = SHIFT;
				}
				else
				{
					currentState = FIND;
				}
				break;
			case SHIFT:
				if ( currentChar == '*' )
				{
					i++;
					std::cin.get( currentChar );
					currentState = SHIFT;
				}
				else
					currentState = FIND;
				break;
			case FIND:
				for(std::vector<Identific>::iterator iter = interp.begin()+1; iter != interp.end(); iter++ )
						if ( !buf.compare( iter->code ) )
						{
							message.push_back( iter->ways[i] );
							words[iter->ways[i]].freq++;
							unsigned int j = i;
							if ( j ) {
								i--;
								while( words[iter->ways[i]].freq <= words[iter->ways[j]].freq )
								{
									if ( i == 0 )
									{
										i--;
										break;
									}
									else
										i--;
								}
								if ( j != i+1 )
								{
									unsigned int t = iter->ways[j];
									for( unsigned int k = j; k > i+1; k--)
										iter->ways[k] = iter->ways[k - 1];
									iter->ways[i+1] = t;
								};
								break;
							}
						};
				i = 0;
				buf = "";
				currentState = DELIM;
				break;
			case SPACE:
				if ( currentChar >= '2' && currentChar <= '9' )
				{
					buf.push_back( currentChar );
					std::cin.get( currentChar );
					currentState = NUMBER;
				}
				else
					currentState = DELIM;
				break;
			case STOP:
				if ( currentChar == '*' )
				{
					i++;
					std::cin.get( currentChar );
					currentState = STOP;
				}
				else currentState = FINDS;
				break;
			case FINDS:
				message.push_back( interp[0].ways[i] );
				i = 0;
				currentState = DELIM;
				break;
			case END:
				cond = false;
				break;
		};
		printMessage();
}
int main()
{
	fillBut();
	std::cin >> N;
	std::cin.ignore( );
	getWords();
	getMessage();
	return 0;
}