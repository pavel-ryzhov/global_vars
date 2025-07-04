#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <string.h>


#define WORD_LENGTH_LIMIT 20

typedef struct{
	char str[WORD_LENGTH_LIMIT];
	unsigned rank;   // see the task
}word_t;

typedef struct{
	std::vector<word_t> entries;
}entry_t;


char alphabet[26]=
{
	'2','2','2',
	'3','3','3',
	'4','4','4',
	'5','5','5',
	'6','6','6',
	'7','7','7','7',
	'8','8','8',
	'9','9','9','9'
};

std::map<std::string, entry_t> dictionary;


std::istream& operator >> (std::istream& is, word_t &word){
	char c;
	std::string str;

	std::cin >> c;
	if(is.bad()) return is;

	while(c!=' '){
		if( (c>='a') && (c<='z') ){
			str.push_back(c);
			std::cin.get(c);
		}
	}

	strcpy(word.str, str.c_str());

	unsigned rank;
	is >> rank;
	word.rank=rank;

	return is;
}

bool word_comparison_function(word_t word1, word_t word2){
	if(word1.rank==word2.rank) return 
		std::lexicographical_compare(&word1.str[0],&word1.str[20],&word2.str[0],&word2.str[20]);  //strcmp :) 
	return (word2.rank<word1.rank);
}

std::string *generate_key(std::string str){
	std::string *key=new std::string;
	for(unsigned i=0;i<str.size();i++){
		key->push_back(alphabet[str[i]-'a']);
	}
	return key;
}

int main(void){

	unsigned N;
	std::map<std::string, entry_t>::iterator d_it;  //iterator for dictionary

	std::cin >> N;

	for(unsigned i=0; i<N; ++i){
		word_t word;
		std::string *key;
		std::cin >> word;
		key=generate_key(word.str);
		d_it=dictionary.find(*key);
		// not found:
		if(d_it==dictionary.end()){
			entry_t temp;
			temp.entries.resize(0);
			temp.entries.push_back(word);
			dictionary.insert(std::pair<std::string, entry_t> (*key, temp));
		// found:
		} else {
			(*d_it).second.entries.push_back(word);
		}
		delete key;
	}

	for(d_it=dictionary.begin();d_it!=dictionary.end();++d_it){
		std::sort((*d_it).second.entries.begin(),(*d_it).second.entries.end(), word_comparison_function);
	}
	
	// now read the input string:
	char c;
	std::string key;
	char punctuation[3]={'.',',','?'};
	int counter; // * counter 
	std::cin >> c;
	while(  ((c>='1')&&(c<='9'))||(c==' ')||(c=='*')&&(!std::cin.eof())  ){
		char state;   //'c' - cypher, 'p' - punctuation, 's' - space

		if (('2'<=c)&&(c<='9')) state = 'c';
		else if (c=='1') state = 'p';
		else if (c==' ') state = 's';
		else break;

		switch(state){
			case 's':
				std::cout << ' ';
				std::cin.get(c);
				break;

			case 'c':
				counter=0;
				key.resize(0);
				while(1){
					if(c!='*') key.push_back(c);
					std::cin.get(c);
					if( ((c<='1')||(c>='9'))&&(c!=' ')&&(c!='*')||std::cin.eof() ){
						d_it = dictionary.find(key);
						std::cout << (*d_it).second.entries[counter].str;
						break;
					}

					if( (c<'2')||(c>'9')){
						if(c=='*'){
							counter++;
						} else {
							d_it = dictionary.find(key);
							std::cout << (*d_it).second.entries[counter].str;
							(*d_it).second.entries[counter].rank++;
							while(counter!=0){
								if( (*d_it).second.entries[counter-1].rank <=
									(*d_it).second.entries[counter].rank ) {
										--counter;
										std::swap((*d_it).second.entries[counter],(*d_it).second.entries[counter+1]);
								} else break;
							}							
							break;
						}
					}
				}
				break;

			case 'p':
				counter=0;
				while(1){
					std::cin.get(c);
					if( ((c<='1')||(c>='9'))&&(c!=' ')&&(c!='*')||std::cin.eof() ){
						std::cout << punctuation[counter%3];
						break;
					}

					if(c=='*'){
						counter++;
					} else {
						std::cout << punctuation[counter%3];
						break;
					}
				}
				break;

			default:
				break;
		}

	}

	return 0;
}
				
				










