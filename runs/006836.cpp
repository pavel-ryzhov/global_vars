//============================================================================
// Name        : Exercise3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>


using namespace std;

class Word{
public:
	string word;
	int wordSize;
	int frequency;
	int posInSlovar;
	void setSize(int size){
		wordSize = size;
	}
	int getSize(){
		return wordSize;
	}
};




class Finder{
private:
	string textSMS;
	string lastWord;
	int wordPosInSlovT9;
	vector<Word*> slovar;
	vector<Word*> *slovarT9;
	int slovarT9Count;
	string buttons[10];
	int wordCount;
	map<char,int> number;

	//упорядочивание слов в соответствии с частотой
	void slovarT9Sort(){
		Word  *word1 = new Word();
		Word  *word2 = new Word();

		if(wordPosInSlovT9 == 0){
			for (int i = 0; i < slovarT9->size(); i++){
				for(int j = i+1 ; j<slovarT9->size(); j++){
					if(slovarT9->at(i)->frequency < slovarT9->at(j)->frequency) {
						*word1 = *slovarT9->at(i);
						*word2 = *slovarT9->at(j);
						slovarT9->at(i) = word2;
						slovarT9->at(j) = word1;
						int t ;


					}
				}
			}
		}
	}


	//заполнение параметров Word;
	int setSomething(string* word,int*  freq){
		int res = 0;
		char ch;
		cin>>ch;
		switch(ch){
		case '\n':
			return 2;
		case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
			cin.putback(ch);
			cin>>*freq;
			return 2;
		default:
			if(isalpha(ch)){
				cin.putback(ch);
				cin>>*word;
				return 1;
			}
		}
			return res;
	}
	//создание нового Word, элемента словаря
	void setWord(string* word,int*  freq){
		char ch;
		int result = 0;
		while(cin){
			result = setSomething(word,freq);
			if(result==0){
				break;
			}
			if(result==1){
				continue;
			}
			if(result==2){
				return;
			}
		}
	}


	void setFreq(){
		slovarT9->at(wordPosInSlovT9)->frequency+=1;
		for ( int i = 0; i < slovar.size(); i++){
			if(slovar.at(i)->frequency <= slovarT9->at(wordPosInSlovT9)->frequency){
				slovar.insert(slovar.begin()+i,slovarT9->at(wordPosInSlovT9));
				slovar.erase(slovar.begin()+slovarT9->at(wordPosInSlovT9)->posInSlovar+1);
				break;
			}
		}
	}

	//заполнение параметров Word;
	void getWordFromSlovar(string ch){
		int res = 0,numb = 0;

		for(int i = 0; i < ch.size();i++){
			switch(ch[i]){
			case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
				numb = number[ch[i]];
				slovarT9Bilder(numb);

				break;
				//return 1;
			case '*':
				if(lastWord == "."){
					lastWord = ",";
				}else if(lastWord == ","){
					lastWord = "?";
				}else if(lastWord == "?"){
					lastWord = ".";
				}else{

					if(wordPosInSlovT9 == slovarT9->size()-1){
						wordPosInSlovT9 = 0;
						lastWord = slovarT9->at(wordPosInSlovT9)->word;
					}else{
						wordPosInSlovT9++;
						lastWord = slovarT9->at(wordPosInSlovT9)->word;
					}
				}
				break;
			case '1':
				textSMS.append(lastWord);
				if((lastWord!= ".") || (lastWord!=",") || (lastWord!="?") || (lastWord!=" ")){
					setFreq();
				}
				lastWord = ".";
				break;
			case ' ':
				textSMS.append(lastWord);
				lastWord = " ";
				if((lastWord!= ".") || (lastWord!=",") || (lastWord!="?") || (lastWord!=" ")){
					setFreq();
				}
				textSMS.append(lastWord);
				wordPosInSlovT9 = 0;
				slovarT9Count = 0;
				break;
			}

		}
		textSMS.append(lastWord);
		cout<<textSMS;
	}


	//заполнить словарь словами
	void setSlovar(){
		Word * word;
		for (int i = 0;i<wordCount;i++)	{
			word = new Word();
			setWord(&word->word,&word->frequency);
			word->setSize(word->word.size());
			word->posInSlovar = i;
			slovar.push_back(word);
		}
	}


	//построение вспомогательного словаря
	void slovarT9Bilder(int numb){
		wordPosInSlovT9 = 0;
		if(slovarT9Count == 0){
			slovarT9 = new vector<Word*>();
			for(int j = 0;j<slovar.size();j++){
				for(int i = 0;i<buttons[numb].size();i++){
					if(slovarT9Count<=slovar.at(j)->word.size()-1){
						if(buttons[numb][i]==slovar.at(j)->word[slovarT9Count]){
							slovar.at(j)->posInSlovar = j;
							slovarT9->push_back(slovar.at(j));
						}
					}
				}
			}
		}else{
			int i = 0;
			while(i != slovarT9->size()){
				int col = 0;
				if(slovarT9->at(i)->word.size()<slovarT9Count+1){
					slovarT9->erase(slovarT9->begin()+i);
					continue;
				}
				for(int j = 0;j<buttons[numb].size();j++){
					if(buttons[numb][j] == slovarT9->at(i)->word[slovarT9Count])col++;
				}
				if(col==0){
					slovarT9->erase(slovarT9->begin()+i);
					continue;
				}
				i++;
			}

		}
			//slovarT9Sort();


		slovarT9Count++;
		wordPosInSlovT9 = 0;
		lastWord = slovarT9->at(wordPosInSlovT9)->word;
	}

	int getString(string *str){
		string s;
		char ch;
		cin.get(ch);

		if(ch == '\n')return 1;
		if(isspace(ch)){
			s = " ";
			str->append(s);
			return 0;
		}
		else{
			cin.putback(ch);
			cin>>s;
			str->append(s);
			return 0;
		}
	}

	void getText(){
		int res = 0;
		string ch;
		cin>>ch;
		while(cin){
			res = getString(&ch);
			if(res == 0)continue;
			if(res == 1)break;
		}
		getWordFromSlovar(ch);
	}
public:

	Finder(int count){
		wordPosInSlovT9 = 0;
		slovarT9Count = 0;
		wordCount = count;
		buttons[0] = " ";
		buttons[1] = ".,?";
		buttons[2] = "abc";
		buttons[3] = "def";
		buttons[4] = "ghi";
		buttons[5] = "jkl";
		buttons[6] = "mno";
		buttons[7] = "pqrs";
		buttons[8] = "tuv";
		buttons[9] = "wxyz";

		number['2'] = 2;
		number['3'] = 3;
		number['4'] = 4;
		number['5'] = 5;
		number['6'] = 6;
		number['7'] = 7;
		number['8'] = 8;
		number['9'] = 9;
		setSlovar();
		getText();

	}
	~Finder(){
		for(int i = 0; i < slovar.size(); i++){
			delete slovar[i];
		}
		for (int i = 0; i < slovarT9->size();i++){
			delete slovarT9->at(i);
		}
		delete slovarT9;

	}

};






int main() {
	vector<Word> vas;
	int count;

	cin>>count;
	Finder *finder = new Finder(count);


//	cout<< "end";



	return 0;
}
