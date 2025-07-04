#include <stdio.h>
#include <string.h>
#include <stdlib.h>
enum {
  MAX_WORD_SIZE = 20, 
  NUM_BTNS = 8
};

typedef struct word_list_item {
  int frequency;
  char word[MAX_WORD_SIZE+1];
  struct word_list_item * next;
  struct word_list_item * prev;
} word_list_item;


typedef struct dic_entry {
  struct word_list_item * list;
  struct dic_entry * next_level[NUM_BTNS];
} dic_entry;

enum{
  BTN2 = 0,
  BTN3,
  BTN4,
  BTN5,
  BTN6,
  BTN7,
  BTN8,
  BTN9,
};

/*
 * That looks nasty, but is actually fast. Memory is(almost)  unlimited, time is limited.
 * Also, it assumes that we use ASCII
 */
int buttons[] = {
  BTN2, BTN2, BTN2, 
  BTN3, BTN3, BTN3, 
  BTN4, BTN4, BTN4, 
  BTN5, BTN5, BTN5,  
  BTN6, BTN6, BTN6,  
  BTN7, BTN7, BTN7, BTN7,
  BTN8, BTN8, BTN8,  
  BTN9, BTN9, BTN9, BTN9
};

inline int which_button(char c){
  return buttons[c-'a'];
}

inline int word_cmp(word_list_item * first, word_list_item * second){
  if(first->frequency != second->frequency)
    return (first->frequency - second->frequency);
  return strncmp(second->word, first->word, MAX_WORD_SIZE);  
}

void free_list( word_list_item * first){
  if(!first){
    return;
  }
  word_list_item * cur = first->next;
  while(cur!=first){
    word_list_item * tmp = cur;
    cur = cur->next;
    free(tmp);
  }
  free(first);
}

void free_dic(dic_entry * dic){
  if(!dic){
    return;
  }
  for(int i=BTN2;i<=BTN9; i++){
    free_dic(dic->next_level[i]);
  }
  free_list(dic->list);
  free(dic);
}

void add_to_dic(dic_entry * dic, char * word, int wordlen, int start, int freq){
  if(!dic || ! word){    
    return;
  }
  if(wordlen > MAX_WORD_SIZE){
    wordlen = MAX_WORD_SIZE; // Truncate long words.
  }
  if( start < wordlen){
    if(!dic->next_level[ which_button(word[start]) ])
      if(! (dic->next_level[ which_button(word[start]) ] = (dic_entry * ) calloc(1,sizeof(*dic))) ){
	fprintf(stderr,"Memory allocation error!\n");
	exit(1);
      }
    add_to_dic(dic->next_level[ which_button(word[start]) ], word, wordlen, start+1,freq);
  }else{
    word_list_item * item = (word_list_item * )calloc(1,sizeof(* item));
    if(!item){
      fprintf(stderr,"Memory allocation error!\n");
      exit(1);
    }
    item->frequency = freq;
    memcpy(item->word, word, wordlen*sizeof(char)); 
    item->next = item->prev = item;     
    if(!dic->list){
      dic->list = item;
    }else{
      word_list_item * cur = dic->list, * prev = dic->list->prev;
      while(cur != dic->list && word_cmp(item, cur) < 0){
	prev = cur;
	cur = cur->next;
      }
      prev->next = item;
      item->prev = prev;
      item->next = cur;
      cur->prev = item; 
    }
  }  
}

const char Punctuation [] = {'.',',','?'};

void parse(dic_entry * root_dic){
  dic_entry * cur_dic;
  int c = getchar();
  while(c != EOF){
    if(c>='2'&& c<='9'){
      cur_dic = root_dic;
      while(c>= '2' && c<='9'){
	cur_dic = cur_dic->next_level[c - '2'];
	c = getchar();
      }
      word_list_item * item = cur_dic->list;
      if(!item){
	fprintf(stderr, "Unrecognized word!\n");
	exit(1);
      }
      word_list_item * test = cur_dic->list;
      while(c == '*'){	
	item = item->next;
	c = getchar();
      }
      item->frequency++;
      if(item != cur_dic->list){
	word_list_item * prev = item->prev;
	prev->next = item->next;
	item->next->prev = prev;
	while(prev->frequency <= item->frequency 
	      && prev->next !=cur_dic->list){
	  prev = prev->prev;
	}
	word_list_item * cur = prev->next;
	prev->next = item;
	item->prev = prev;
	item->next = cur;
	cur->prev = item; 
	if(cur_dic->list == cur)
	  cur_dic->list = item;

	test = cur_dic->list;
      }
      printf("%s",item->word);      
    }else if(c=='1'){
      int count = -1;
      do{
	count ++;
	c = getchar();
      }while(c=='*');
      putchar(Punctuation[count % sizeof(Punctuation)]);
    }else if(c==' '){
      putchar(' ');
      c = getchar();
    }else{
      c = getchar();
    }
  } 
}

int main(void){
  dic_entry * root_dic;
  if (!(root_dic= (dic_entry * ) calloc(1,sizeof(*root_dic)))){
    fprintf(stderr,"Memory allocation error!\n");
    exit(1);
  }
  int n,freq;
  char word[21];
  if(scanf("%d", &n)!=1){
    fprintf(stderr,"Preliminary EOF!!!\n");
    exit(1);
  }
  for(int i=0;i<n;i++){
    if(scanf("%20s%d",word,&freq)==2){
      add_to_dic(root_dic, word, strlen(word), 0, freq);
    } else {
      fprintf(stderr, "Preliminary EOF\n");
      exit(1);
    }
  }
  parse(root_dic);
  printf("\n");
  free_dic(root_dic);
  return 0;
}
