#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
calculating a code for each word on startup and using a hashmap
was probably better but first thought was about realtime complete
so tree was used(ln(length) is small
*/

enum t9{
	abc,def,ghi,
	jkl,mno,pqrs,
	tuv,wxyz 
};

class node{
	t9 character;
	int position;//on which position thic character is placed
	std::vector<std::pair<std::string,int> > words; // sorted vec of words with [0] beeing most freqently used
	std::vector<node*>  next; //pointers to nodes containing words with length 1 bigger and
							//accses by character t9 code like this next[abc]->getword
							//TODO think about pointers

	struct _comparator {//for sorting according to frequency with most freuqent beeing [0]
  			bool operator() (std::pair<std::string,int> left,
				std::pair<std::string,int> right) { 
					return (left.second > right.second);
			}
	} comparator;


public:
	node(t9 _character,int _position):character(_character),position(_position){
	}

	static t9 char_to_digit(char _ch) {
		char ch = tolower(_ch);
		//if(ch < 'a')throw std::exception("wrong argument of char to digit,not a correct char");
		if(ch < 'd') return abc; 
		else if(ch < 'g') return def; 
		else if(ch < 'j') return ghi; 
		else if(ch < 'm') return jkl; 
		else if(ch < 'p') return mno; 
		else if(ch < 't') return pqrs;
		else if(ch < 'w') return tuv; 
		else return wxyz;
		//else throw std::exception("wrong argument of char_to_digit,not a correct char");
	}

	std::string get_word(std::string _word,int _attempt){
		if(_word.length() == position){
			std::string result = words[_attempt].first;
			words[_attempt].second++;
			int i = _attempt ;
			while((i > 0) && (words[i].second <= words[_attempt].second)){//find all words which are needed to be ssuffled
				i--;
			}
			words[_attempt].second++;//for a new word to outweight others
			std::stable_sort(&words[i],&words[_attempt]+1,comparator);//unoptimal?
			int  q =0;
			while(words[q].first != result){
				q++;
			}

			words[q].second--;//set it back
			//std::cout << "   1111  "  << words[i].first;
			//std::rotate(&words[i],&words[_attempt],&words[_attempt]+1);
			return result;
		}
		else{
			return next[ (_word[position] - '2')]->get_word( _word, _attempt);
		}
	}

	void add_word(std::string _word,int _frequency){
		if(_word.length() == position)words.push_back(
			std::pair<std::string,int>(_word,_frequency));
		else if(next.size() < 8){//fill on first use
			for(int i = 0;i < wxyz + 1;++i)next.push_back(  new node((t9)i , position + 1));
			next[ char_to_digit(_word[position]) ]->add_word( _word, _frequency);
		}
		else next[ char_to_digit(_word[position]) ]->add_word( _word, _frequency);//try to add to child node with 
																				//coressponding character 
	}

	void on_all_wors_added(){//added for not sorting words on creation of dictionary,each time the word is added
		std::stable_sort(words.begin(),words.end(),comparator);
		if(next.size() > 0)for(int i = 0;i < wxyz + 1;++i)next[i]->on_all_wors_added();
	}
};


class t9tree{
	node root;
public:
	t9tree():root((t9)1,0) {//no arguments,because cin is used as input
		int dictsize;
		std::cin >> dictsize;
		for(int i = 0;i < dictsize;++i){
			std::string word;
			int freq;
			std::cin >> word >> freq;
			root.add_word(word,freq);
		}
		root.on_all_wors_added();
		int digit = -1;
		int attempt = 0; 
		int punctuation_attempt = -1;
		bool space_flag = false;
		std::string word;
		while(!isdigit(digit = std::cin.get()));//skip unnesacesey
		while(std::cin.good()){
			if(isdigit(digit) && (digit != '1')){
				if(punctuation_attempt != -1){
					if( 0 == punctuation_attempt ) {std::cout << "." ;}
					else if(1 == punctuation_attempt) {std::cout << "," ;}
					else {std::cout << "?" ;}
					punctuation_attempt = -1;
				}
				word.push_back(digit);//normal letter add to the word
				space_flag = false;
			}
			else if(isspace(digit) &&  (-1 == punctuation_attempt)  && ! space_flag){//output of (maybe modified) word
				try{
					std::cout << root.get_word(word,attempt) << " ";
				}
				catch (std::exception e){
					std::cerr << e.what();//logging error
				}  
				attempt = 0;
				word.clear();
				space_flag = true;
			}
			else if('1' == digit){//prepare to output punctiaution mark
				if( punctuation_attempt != -1 ){
					if( 0 == punctuation_attempt ) {std::cout << "." ;}
					else if(1 == punctuation_attempt) {std::cout << "," ;}
					else {std::cout << "?" ;}
				}//check for previous 1
				punctuation_attempt = 0;
				try{
					if(word.size() )std::cout << root.get_word(word,attempt) ;
					
				}
				catch (std::exception e){
					std::cerr << e.what();//logging error
				}
				attempt = 0;
				word.clear();
				space_flag = false;
			}
			else if(isspace(digit)  && space_flag){
				std::cout << " ";
			}
			else if(isspace(digit)){//output mark(see above for word)) or space
				if( 0 == punctuation_attempt ) {std::cout << ". " ;}
				else if(1 == punctuation_attempt) {std::cout << ", " ;}
				else if(2 == punctuation_attempt){std::cout << "? " ;}
				else std::cout << " ";
				punctuation_attempt = -1;
				space_flag = true;
			}
			else if(('*'  == digit ) && ( punctuation_attempt > -1 )){//previosly was 1 and some *
				punctuation_attempt++;
			}
			else if('*'  == digit ){
				attempt++;
			}
			else{
				if(-1 == punctuation_attempt && word.size() != 0)std::cout << root.get_word(word,attempt);
				else if(punctuation_attempt != -1){
					if( 0 == punctuation_attempt ) {std::cout << "." ;}
					else if(1 == punctuation_attempt) {std::cout << "," ;}
					else {std::cout << "?" ;}
					punctuation_attempt = -1;
				}  
				
			}//end of finite state machine
			digit = std::cin.get();//get next is hear because first get is from previous loop
		}//finisfing
	}
};


int main(int argc,char* argv[])
{
	t9tree singleton;
	return 0;
}

