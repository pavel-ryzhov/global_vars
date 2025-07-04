#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

//word and its frequency
class TWord{
public:
	string value;
	int freq;
	TWord(){freq=0;value="";};
};

vector<TWord> WORDS;						//dictionary
vector< vector<TWord*> > WORDS_of_len;		//words by length

//quick sort
void sort_part(int wof_i, int start, int end){
	if (end-start<1)return;

	long i = 0, j = end-start-1;
	int mid=(int)((end-start)/2 + start);
	int p = WORDS_of_len[wof_i][mid]->freq;

	do{
		while ( WORDS_of_len[wof_i][i+start]->freq > p ) i++;
		while ( WORDS_of_len[wof_i][j+start]->freq < p ) j--;
		if (i <= j) {
			if (WORDS_of_len[wof_i][i+start]->freq != WORDS_of_len[wof_i][j+start]->freq)
				swap(WORDS_of_len[wof_i][i+start], WORDS_of_len[wof_i][j+start]);
			i++; j--;
		}
	} while ( i<=j );

	if ( j > 0 ) sort_part(wof_i, start, j);
	if ( end-start-1 > i ) sort_part(wof_i, start+i, end);// quickSortR(a+i, N-i);
}

//sorting element by frequency in WORDS_of_len[i]
void SORT_wof(int i){
	sort_part(i, 0, WORDS_of_len[i].size()); 
}

bool charOfNum(char c, char num){
	if (num=='2' && (c=='a' || c=='b' || c=='c')) return true;
	if (num=='3' && (c=='d' || c=='e' || c=='f')) return true;
	if (num=='4' && (c=='g' || c=='h' || c=='i')) return true;
	if (num=='5' && (c=='j' || c=='k' || c=='l')) return true;
	if (num=='6' && (c=='m' || c=='n' || c=='o')) return true;
	if (num=='7' && (c=='p' || c=='q' || c=='r' || c=='s')) return true;
	if (num=='8' && (c=='t' || c=='u' || c=='v')) return true;
	if (num=='9' && (c=='w' || c=='x' || c=='y' || c=='z')) return true;
	return false;
}

int digit(char c){
	switch (c){
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default: return -1;
	}
}

string cur_template("");		//current template
string word_template("");		//only current word template
vector<TWord*> current_words;	//appropriate words
int changes = 0;
bool comma = false;

void increase_freq(int wlen, int w){
	WORDS_of_len[wlen][w]->freq++;
	int cur = w-1;
	while (cur>=0 && WORDS_of_len[wlen][cur]->freq <= WORDS_of_len[wlen][w]->freq){
		cur--;
	}
	cur++;

	if (w-cur>0){
		WORDS_of_len[wlen].insert(WORDS_of_len[wlen].begin()+cur, WORDS_of_len[wlen][w]);
		WORDS_of_len[wlen].erase(WORDS_of_len[wlen].begin()+w+1);
	}
}

void getWord(){
	int wordlen = word_template.length();
	if (wordlen<1) return;
	int wsize	= WORDS_of_len[wordlen].size();

	vector<int> matches;
	int match_count=0;
	bool print=false;
	for (int i=0; i<wsize; i++){
		bool match=true;
		for (int j=0; j<wordlen; j++){
			if (! charOfNum( WORDS_of_len[wordlen][i]->value[j], word_template[j] ) )
			{
				match = false;
				break;
			}
		}

		if (match){
			match_count++;
			matches.resize(match_count);
			matches[match_count-1] = i;
		} else continue;

		int printindex=match_count-1;
		print = false;
		print = match_count==changes+1;
		if (print) printindex = i;
		if (i==wsize-1 && match_count>0 && !print)
		{		
			print = changes>=match_count;
			if (print){
				printindex = matches[changes % match_count];
			}
		}

		if (print){
			cout << WORDS_of_len[wordlen][printindex]->value;
			increase_freq(wordlen, printindex);
			break;
		}// end for 2
	}// end for 1

	word_template = "";
	changes=0;
}

void inline ifcomma(){
	if (comma){
		changes = changes % 3 +1;
		switch (changes){
			case 1: cout<<'.';break;
			case 2: cout<<',';break;
			case 3: cout<<'?';break;
		}
		comma = false;
	}
}

void doCommand(char c){
	int n=digit(c);
	bool isdigit = n!=-1;

	if (isdigit && c!='1'){
		word_template += c;
		ifcomma();
		return;
	};

	switch (c){
	case '*':
		if (word_template!="" || comma) changes++;
		return;
	case '1':
		getWord();
		if (comma) cout << '.';
		comma = true;
		return;
	}
}

void searchWords(){
	int template_size = cur_template.length();
	if (template_size<1) return;
	for (int i=0; i<template_size; i++){
		doCommand(cur_template[i]);
	}
	ifcomma();
	getWord();
}

void addWordOfLen(TWord &w){
	int wlen = w.value.length();
	int wsize = WORDS_of_len[wlen].size();
	WORDS_of_len[wlen].resize(wsize+1);
	WORDS_of_len[wlen][wsize] = &w;
}

//*-----  MAIN  -----*//
int main()
{
	WORDS_of_len.resize(21);
	int N;		//number of words
	cin >> N;
	WORDS.resize(N);

	//reading data
	for (int i=0; i<N; i++)
	{
		int start, end, rlen;
		cin >> WORDS[i].value >> WORDS[i].freq;
		addWordOfLen(WORDS[i]);
	}
	
	//sorting
	for (int i=1; i<WORDS_of_len.size(); i++) SORT_wof(i);

	char c[100000];
	cin.ignore(1, '\n');
	cin.getline(c, 100000);
	int slen = strlen(c);

	for (int i=0; i<slen; i++){
		if (c[i]!=' ') cur_template+=c[i];
		if ((c[i]==' ' || i==slen-1) && cur_template!="")
		{
			searchWords();
			cur_template="";
		}
		if (c[i]==' ') cout << ' ';
	}
	cout << endl;
}
