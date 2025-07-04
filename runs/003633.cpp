#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

const int NB = 8;
const int FB = 2;

int gmem = 0;

struct PriWord{
	string s;
	int freq;
	int ord_in_text;
	
	PriWord(string s, int freq){
		this->s = s; 
		this->freq = freq;
		this->ord_in_text = 0;
	}
	PriWord(string s, int freq, int ord_in_text){
		this->s = s; 
		this->freq = freq;
		this->ord_in_text = ord_in_text;
	}
	
	bool operator<(PriWord &b){
		if (this->freq != b.freq)
			return this->freq > b.freq;
		else if (this->ord_in_text != b.ord_in_text)
			return this->ord_in_text > b.ord_in_text;
		else
			return this->s < b.s;
	}
	
};

void print_wlist(list <PriWord> &w){
	for (list <PriWord>::iterator i=w.begin(); i!=w.end(); i++)
		cout << i->freq << i->s << " ";
	cout << endl;
}

class Trie{

	struct TrieNode{
		bool exist_item;
		TrieNode *next[NB];
		list <PriWord> wlist;
		
		TrieNode(){
			this->exist_item = false;
			for (int i=0;i<NB;i++)
				this->next[i] = NULL;
		}
	} *m_arr[NB];
	
	int get_num_letter(char c){
		if ('a' <= c && c <= 'c') return 0;
		if ('d' <= c && c <= 'f') return 1;
		if ('g' <= c && c <= 'i') return 2;
		if ('j' <= c && c <= 'l') return 3;
		if ('m' <= c && c <= 'o') return 4;
		if ('p' <= c && c <= 's') return 5;
		if ('t' <= c && c <= 'v') return 6;
		if ('w' <= c && c <= 'z') return 7;
	}
	
	void dfs_disp(TrieNode *t){
		if (!t) return;
		for (int i=0; i<NB; i++)
			dfs_disp(t->next[i]);
		//if (t->wlist) delete t->wlist;
		delete t;
		gmem-=sizeof(TrieNode);
	}
	
	void dfs_dump(TrieNode *t, string fullpath){
		if (!t) return;
		for (int i=0; i<NB; i++)
			dfs_dump(t->next[i], fullpath + char('2' + i));
		if (t->exist_item){
			cout << fullpath << ":" << endl;
			print_wlist(t->wlist);
		}
	}
	
	public:
	
	Trie(){
		for (int i=0; i<NB; i++){
			m_arr[i] = new TrieNode();
			gmem+=sizeof(TrieNode);
		}
	}
	
	void full_dump(){
		for (int i=0; i<NB; i++){
			string tmp = "a"; tmp[0]=+i;
			dfs_dump(this->m_arr[i], tmp);
		}
		for (int i=20;i;--i)
			cout << "-";
		cout << endl;
	}
	
	void add_item(string s, int x){
		TrieNode *t = m_arr[get_num_letter(s[0])];
		for (int i=1; i<s.length(); i++){
			int ind = get_num_letter(s[i]);
			if (!t->next[ind]){
				t->next[ind] = new TrieNode();
				gmem+=sizeof(TrieNode);
			}
			t = t->next[ind];
		}
		if (!t->exist_item){
			t->exist_item = true;
			t->wlist.push_back(PriWord(s, x));
		} else {
			PriWord tp(s, x);
			list <PriWord> tlist(1, tp);
			t->wlist.merge(tlist);
			//print_wlist(t->wlist);
		}
	}
	
	string request(string s, int x, int ordnung){
		TrieNode *t = m_arr[s[0] - '2'];
			for (int i=1; i<s.length(); i++){
				t = t->next[s[i] - '2'];
			}
		if (!t->exist_item){
			cerr << "No word in dictionary" << endl;
			abort();
		}
		x = x % t->wlist.size();
		list <PriWord>::iterator place = t->wlist.begin();
		for (; x; ++place, --x);
		PriWord tp(place->s, place->freq + 1, ordnung);
		list <PriWord> tlist(1, tp);
		t->wlist.erase(place);
		t->wlist.merge(tlist);
		return tp.s;
	}

	void dispose(){
		for (int i=0; i<NB; i++)
			dfs_disp(m_arr[i]);
	}
};

int main(int argc, char **argv){
	/*
	fstream istr;
	if (argc > 1){
		istr.open(argv[1], fstream::in);
	} else {
		istr.open("con", fstream::in);
	}
	*/
	Trie t9;
	char punc[3] = {'.', ',', '?'};
	
	int tsize;
	cin >> tsize;
	for (int i=0; i<tsize; i++){
		string s;
		int x;
		cin >> s >> x;
		t9.add_item(s, x);
		//t9.full_dump();
	}
	
	string gs, ts;
	getline(cin, gs);
	if (gs == "\r" || gs == "")
		getline(cin, gs);
	gs += '!';
	
	int state = 0, nstars = 0, ordnung = 0;
	//0 - reading a word
	for (int i=0; i<gs.length(); i++){
		if ('2' <= gs[i] && gs[i] <= '9'){
			if (state == 2){
				cout << punc[nstars];
				nstars = 0;
				state = 0;
			}
			state = 0;
			ts += gs[i];
		} else if (gs[i] == '*'){
			nstars++;
		} else if (gs[i] == '1'){
			if (state == 0){
				cout << t9.request(ts, nstars, ++ordnung);
				ts.clear();
				nstars = 0;
			} else if (state == 2){
				cout << punc[nstars];
				nstars = 0;
				state = 2;
			}
			state = 2; //reading a punc
		} else if (gs[i] == ' ' || gs[i] == '!'){
			if (state == 0){
				cout << t9.request(ts, nstars, ++ordnung);
				ts.clear();
				nstars = 0;
			} else if (state == 2){
				cout << punc[nstars % 3];
				nstars = 0;
			}
			if (gs[i] == ' ')
				cout << ' ';
			state = 1;
		}
	}
	
	//cout << "Memory used: " << gmem << "bytes" << endl;
	t9.dispose();
	//cout << gmem << endl;
	
	return 0;
}


