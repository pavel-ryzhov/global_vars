#include <cstdio>
#include <cstring>
#include <cassert>
#include <list>
using namespace std;
 
enum {
  BTN2 = 0, BTN3,  BTN4,  BTN5,  BTN6,  BTN7,  BTN8, BTN9,
  MAX_WORD_SIZE = 20, 
  NUM_BTNS = 8,  
};

typedef list<char *> WordList;

class FreqListItem {
 public:
  int frequency;
  WordList words;
  int numWords;
  FreqListItem(int fr, WordList wrds, int num):frequency(fr),words(wrds),numWords(num){}
};

typedef list<FreqListItem> FreqList;

class DicEntry {
private:
  DicEntry(const DicEntry &d):freqList(),numWords(0){ /* do nothing*/ }
  DicEntry& operator = (const DicEntry &d){ /* do nothing*/ return * this;}
public:
  static const int buttons[26];  
  inline static int whichButton(char c){
    return buttons[c-'a'];
  }
  static const char punctuation[3];
  FreqList freqList;
  int numWords;
  DicEntry * nextLevel[NUM_BTNS];
  
  DicEntry() : freqList(),numWords(0){  
    for(int i=0;i<NUM_BTNS; i++){
      nextLevel[i] = NULL;
    }
  }
  void print(){
    printf("BEGIN %p\n", this);
    if(freqList.size()!=0){
      for(FreqList::iterator it = freqList.begin();it!=freqList.end();it++){ 	
	printf("frequency %d:", (*it).frequency);
	for(WordList::iterator it2 = (*it).words.begin(); it2!=(*it).words.end(); it2++){
	  printf("%s ",(*it2));
	}
	printf("\n");
      }
    }
    for(int i=0;i<NUM_BTNS;i++){
      if(nextLevel[i])
	nextLevel[i]->print();
    }
    printf("END %p\n",this);
  }
  void addToDic(char * word, int wordlen, int start, int freq){
    if(! word){    
      return;
    }
    if(wordlen > MAX_WORD_SIZE){
      wordlen = MAX_WORD_SIZE; // Truncate long words.
    }
    if( start < wordlen){
      int next_button = whichButton(word[start]);
      if(!this->nextLevel[next_button])
	this->nextLevel[next_button] = new DicEntry();
      this->nextLevel[next_button]->addToDic(word, wordlen, start+1,freq);
    }else{
      FreqList::iterator it;
      for(it = freqList.begin();it!=freqList.end();it++){
	if((*it).frequency<=freq){
	  break;
	}
      }
      if(it == freqList.end() || (*it).frequency<freq){
	freqList.insert(it, FreqListItem(freq, WordList(1, word),1));
      }else{
	(*it).words.push_back(word);
	(*it).numWords++;
      }
      numWords++;
    }  
  }
  DicEntry * getNextLevel(int n){
    return nextLevel[n];
  }
  char * getWordAndRefresh(int pos){
    int num_words_skipped=0;
    pos = pos % numWords;
    FreqList::iterator it;
    for(it = freqList.begin();it!=freqList.end();it++){
      if(num_words_skipped + (*it).numWords > pos){
	break;
      }
      num_words_skipped += (*it).numWords;
    }
    pos = pos - num_words_skipped;
    WordList::iterator it2;    
    for(it2 = (*it).words.begin(); it2!=(*it).words.end(); it2++){
      if(pos==0){
	break;
      }
      pos--;
    }
    char * word = (*it2);
    (*it).words.erase(it2);
    (*it).numWords--;    
    int freq = (*it).frequency+1;
    if(it==freqList.begin()){
      freqList.insert(it, FreqListItem(freq, WordList(1, word),1));     
    }else if((*(--it)).frequency != freq){
      freqList.insert(++it, FreqListItem(freq, WordList(1, word),1));     
    }else{
      (*it).words.push_front(word);
      (*it).numWords++;
    }
    return word;    
  }
  void parse(){
    DicEntry * cur_dic;
    int c = getchar();
    while(c != EOF){
      if(c>='2'&& c<='9'){
	cur_dic = this;
	while(c>= '2' && c<='9'){
	  cur_dic = cur_dic->getNextLevel(c - '2');
	  c = getchar();
	}
	int count=0;
	while(c == '*'){
	  count++;
	  c = getchar();
	}
	char * word = cur_dic->getWordAndRefresh(count);	
	printf("%s",word);
      }else if(c=='1'){
	int count = -1;
	do{
	  count ++;
	  c = getchar();
	}while(c=='*');
	putchar(punctuation[count % sizeof(punctuation)]);
      }else if(c==' '){
	putchar(' ');
	c = getchar();
      }else{
	c = getchar();
      }
    } 
  }
};

const int DicEntry::buttons[] = {
  BTN2, BTN2, BTN2, 
  BTN3, BTN3, BTN3, 
  BTN4, BTN4, BTN4, 
  BTN5, BTN5, BTN5,  
  BTN6, BTN6, BTN6,  
  BTN7, BTN7, BTN7, BTN7,
  BTN8, BTN8, BTN8,  
  BTN9, BTN9, BTN9, BTN9
};

const char DicEntry::punctuation[] = {'.',',','?'};

int main(void){
  DicEntry root;
  int n,freq;
  assert(scanf("%d", &n)==1);
  for(int i=0;i<n;i++){
    char * word = new char[MAX_WORD_SIZE+1];
    assert(scanf("%20s%d",word,&freq)==2);
    root.addToDic(word, strlen(word), 0, freq);
    //root.print();
  }
  root.parse();
  printf("\n");
  return 0;
}
