#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include <algorithm>

using namespace std;

const char PUNCTUATION[3] = {'.',',','?'};

class word_frequency {
public:
	string word;
	int frequency;
	word_frequency(string s, int ch) {
		word=s;
		frequency=ch;
	}
};

class node {
public:
	node* links[8]; 
	vector<word_frequency> words_frequency_vector;

	void sort(); //sort words_frequency_vector in subtree

	//void print(int level=0);  

	node() {
		for (int i=0; i<8; i++)
			links[i]=NULL;
	}

	~node(){ 
		for(int i=0;i<8;i++)
			if(links[i]) delete links[i];
		words_frequency_vector.clear();
	}

};

class head: public node {
public:
	void importDictionaryLine(istream &in); 
	void importDictionaryToTree(istream &in);
	void parseMessage(istream &in);
};
//NODE MEMBERS and related function--------------------------------------------------------

bool UDgreater(word_frequency w1, word_frequency w2) { //functuon - node::sort() param
	if(w1.frequency==w2.frequency) return (w1.word<w2.word);
	else return (w1.frequency>w2.frequency);
}

void node::sort(){
	for(int i=0; i<8;i++) 
		if(links[i]) (*(links[i])).sort();
	std::sort(words_frequency_vector.begin(),words_frequency_vector.end(), UDgreater);
}

/*void node::print(int level) {

cout<<"Level "<<level<<", words: ";
int k=(int)words_frequency_vector.size();

if(k==0) cout << "-";
else 
for(int i=0;i<k;i++)
cout<<words_frequency_vector[i].word<<" "<<words_frequency_vector[i].frequency<<" ";
cout<<endl;

cout<<"links: ";

bool flag=false;
for(int i=0;i<8; i++)
if (links[i]) {
cout << i<<" ";
flag=true;
}
if(!flag) cout<<"no links";
cout<<endl;

if (flag)
for(int i=0;i<8; i++)
if(links[i]) 
links[i]->print(level+1);
}
*/

//HEAD MEMBERS and related function----------------------------------------------------

void head::importDictionaryToTree(istream &in){
	int n;
	in>>n;
	for(int i=1; i<=n; i++) 
		importDictionaryLine(in);
	sort(); 
}

inline int char_to_link_number(char c) { 
	if ((c>='a')&&(c<='c')) return 0;
	else if ((c>='d')&&(c<='f')) return 1;
	else if ((c>='g')&&(c<='i')) return 2;
	else if ((c>='j')&&(c<='l')) return 3;
	else if ((c>='m')&&(c<='o')) return 4;
	else if ((c>='p')&&(c<='s')) return 5;
	else if ((c>='t')&&(c<='v')) return 6;
	else if ((c>='w')&&(c<='z')) return 7;
	else {
		cout <<"Error in character_to_int"<<endl; 
		return (-1);
	}
}

void head::importDictionaryLine(istream&in) {
	string s;
	int frequency;
	in>>s;
	in>>frequency;

	node* a;
	a=this; 

	int i, k;
	for(i=0;i<(int)s.size();i++) { 
		k=char_to_link_number(s[i]); 
		if (!a->links[k]) 
			a->links[k] = new node();
		a=a->links[k];
	}

	word_frequency q(s,frequency);
	a->words_frequency_vector.push_back(q);
}


void	head::parseMessage(istream&in) {
	char c=in.get();

	while(c!='\n') in.get(c);
	in.get(c);
	if(c=='\r')	in.get(c);

	node* a;
	while((c!='\n')&&(!in.eof())) {
		if ((c>='2')&&(c<='9')) {
			a=this;
			while ((c>='2')&&(c<='9'&&(!in.eof()))) {
				a=a->links[c-'0'-2];
				in.get(c);
			}

			int i=0;
			while (c=='*'&&(!in.eof())) {
				i++;
				in.get(c);
			}
			cout<<a->words_frequency_vector[i].word;
			a->words_frequency_vector[i].frequency++;

			if(a->words_frequency_vector.size()>1){
				word_frequency t=a->words_frequency_vector[i]; 


				while(i-1>=0) {
					if(a->words_frequency_vector[i-1].frequency>t.frequency) break;
					a->words_frequency_vector[i]=a->words_frequency_vector[i-1];
					i--;
				}

				a->words_frequency_vector[i]=t;
			}
		}

		else if(c==' ') {
			cout <<" ";
			in.get(c);
		}

		else if(c=='1') {
			int i=0;
			in.get(c);

			while(c=='*'&&(!in.eof())) {
				i++;	
				in.get(c);
			}
			cout<<PUNCTUATION[i];
		}
	}
}


//MAIN--------------------------------------------------------------------
int main() {
	istream* in;

	//ifstream infile("input.txt"); 
	//in = &infile;
	in = &cin; 

	head treehead;
	treehead.importDictionaryToTree(*in);
	treehead.parseMessage(*in);
	//system("pause");
}
