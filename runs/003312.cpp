#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

class Word_node//запись списка слов
{
      friend class Word_list;
      friend class Key_node;
      friend class Key_list;
      public:
             Word_node(char* word,int fr);
             ~Word_node();
      private:
              char* value; //слово
              int freq; //частота
              int length;//?
              Word_node* next; // след. эл-т списка
              Word_node* prev; // пред. эл-т списка
};

class Word_list //упорядоченный по частоте список слов по одному ключу
{
      friend class Word_node;
      friend class Key_node;
      friend class Key_list;
      public:
             Word_list();
             ~Word_list();
             int Add_word(char* word,int freq);
             char* Find_word(int num);
             void show();//функция для отладки
      private:
              Word_node* start; //первый эл-т списка
};

class Key_node //запись списка ключей
{
      friend class Key_list;
      friend class Word_node;
      friend class Word_list;      
      public:
             Key_node();
             ~Key_node();
      private:

              int* key; //ключ
              int key_len; //длина ключа
              Key_node* prev;
              Key_node* next;
              Word_list list; //список слов по данному ключу
};

class Key_list //список ключей в лексикографическом порядке
{
/*не такие уж тут большие объемы, чтобы строить дерево поиска, список вполне должен работать*/      
      friend class Key_node;
      friend class Word_node;
      friend class Word_list; 
      public:
             Key_list();
             ~Key_list();
             int Key_add(char* word,int freq);//добавление слова
             char* Find(int* code,int code_len,int num);//поиск нужного слова по ключу и порядковому номеру частоты
             void print();//отладочная функция печати списка ключей
      private:
              Key_node *first; //начало списка ключей
              int* compute_key(char* word);//вычисление ключа по слову
};

/*************************************************************/
/*************************************************************/
/*************************************************************/

Word_node::Word_node(char* word,int fr){
   length=strlen(word);
   value=new char[length];
   memcpy(value,word,length);
   freq=fr;
   next=NULL;
   prev=NULL;
}

/*************************************************************/

Word_node::~Word_node(){
   delete []value;
}

/*************************************************************/
/*************************************************************/


Word_list::Word_list(){ start=NULL;}

/*************************************************************/

Word_list::~Word_list(){
   Word_node *A,*B;
   for(A=start;A!=NULL;A=B){
      B=A->next;
      delete A;
   }
}

/*************************************************************/

int Word_list::Add_word(char* word,int freq){
    Word_node *A;
    Word_node *B;
    A=new Word_node(word,freq);
    if(start!=NULL){
         if(start->next==NULL){
              if((*A).freq>(*start).freq){ 
               (*A).next=start;
               start->prev=A;
               start=A;
               return 1;
              }
              start->next=A;
              A->prev=start;
              return 2;                 
         }
         for(B=start;B->next!=NULL;B=B->next){//поиск нужного места в списке
            if((*A).freq>(*B).freq){ 
               if(B->prev!=NULL)(B->prev)->next=A;
               (*A).prev=B->prev;
               (*A).next=B;
               B->prev=A;
               return 3;
            }
         }
         if((*A).freq>(*B).freq){ 
               if(B->prev!=NULL)(B->prev)->next=A;
               (*A).prev=B->prev;
               (*A).next=B;
               B->prev=A;
               return 4;
         }
        (*B).next=A; (*A).prev=B;
    }
    else{
         start=A;
    }
    return 0;                  
}

/*************************************************************/

char* Word_list::Find_word(int num){
     Word_node *Q,*A;
     int i;
     char* ret;
     if(num==1){(*start).freq++;return (*start).value;}
     for(Q=start,i=1;i<num;i++,Q=Q->next);
     ret=(*Q).value;
     (*Q).freq++;//увеличение частоты
     if(Q->prev==NULL)return ret;
     for(A=Q->prev;A!=NULL;A=A->prev){ //поиск нового места слова с учетом изменившейся частоты
        if((*A).freq>(*Q).freq) break;
        else{
           if(A->prev!=NULL)(A->prev)->next=Q;
           if(Q->next!=NULL)(Q->next)->prev=A;
           Q->prev=A->prev; 
           A->next=Q->next;
           A->prev=Q;
           Q->next=A;
           A=Q;
           if(Q->prev==NULL){start=Q;break;}
        }
     }
     return ret;
}

/*************************************************************/

void Word_list::show(){
     Word_node *A;
     int i;
     for(A=start;A->next!=NULL;A=A->next){
        for(i=0;i<(*A).length;i++)cout<<(*A).value[i];cout<<endl;
     }
     for(i=0;i<(*A).length;i++)cout<<(*A).value[i];cout<<endl;
}

/*************************************************************/
/*************************************************************/

Key_node::Key_node(){
                      next=NULL;
                      prev=NULL;
                      key=NULL;
                      key_len=0;
}

/*************************************************************/

Key_node::~Key_node(){
    if(key!=NULL) delete []key;
}

/*************************************************************/
/*************************************************************/

Key_list::Key_list(){
                      first=NULL;
}

/*************************************************************/

Key_list::~Key_list(){
   Key_node *X,*Y;
   for(X=first;X!=NULL;X=Y){
      Y=X->next;
      delete X;
   }
}

/*************************************************************/

int Key_list::Key_add(char* word,int freq){ 
    Key_node *X;
    Key_node *Y;
    X=new Key_node;
    (*X).key_len=strlen(word);
    (*X).key=compute_key(word);
    if(first!=NULL){
          if(first->next==NULL){
             if(((*first).key_len==(*X).key_len)&&(memcmp((*X).key,(*first).key,(*X).key_len*sizeof(int))==0)){
                (*first).list.Add_word(word,freq);
                delete X;
                return 4;
             }
            (*X).prev=Y; 
            first->next=X;
            (*X).list.Add_word(word,freq);
            return 4;
          }
          for(Y=first;Y->next!=NULL;Y=Y->next){
             if(((*Y).key_len==(*X).key_len)&&(memcmp((*X).key,(*Y).key,(*X).key_len*sizeof(int))==0)){
                (*Y).list.Add_word(word,freq);
                delete X;
                return 1;
             }
          }
            if(((*Y).key_len==(*X).key_len)&&(memcmp((*X).key,(*Y).key,(*X).key_len*sizeof(int))==0)){
                (*Y).list.Add_word(word,freq);
                delete X;
                return 1;
             }
            (*X).prev=Y; 
            Y->next=X;
            (*X).list.Add_word(word,freq);
            return 2;
    }
    else{
         (*X).list.Add_word(word,freq);
         first=X;
         return 3;
    }
    return 0;
}

/*************************************************************/

int* Key_list::compute_key(char* word){ 
     int len;
     len=strlen(word);
     int* res;
     res=new int[len];
     for(int i=0;i<len;i++){
        switch(word[i]){
           case 'a': res[i]=2;
           break;
           case 'b': res[i]=2;
           break;
           case 'c': res[i]=2;
           break;
           case 'd': res[i]=3;
           break;
           case 'e': res[i]=3;
           break;
           case 'f': res[i]=3;
           break;
           case 'g': res[i]=4;
           break;
           case 'h': res[i]=4;
           break;
           case 'i': res[i]=4;
           break;
           case 'j': res[i]=5;
           break;
           case 'k': res[i]=5;
           break;
           case 'l': res[i]=5;
           break;
           case 'm': res[i]=6;
           break;
           case 'n': res[i]=6;
           break;
           case 'o': res[i]=6;
           break;
           case 'p': res[i]=7;
           break;
           case 'q': res[i]=7;
           break;
           case 'r': res[i]=7;
           break;
           case 's': res[i]=7;
           break;
           case 't': res[i]=8;
           break;
           case 'u': res[i]=8;
           break;
           case 'v': res[i]=8;
           break;
           case 'w': res[i]=9;
           break;
           case 'x': res[i]=9;
           break;
           case 'y': res[i]=9;
           break;
           case 'z': res[i]=9;
           break;
           case '.': res[i]=1;
           break;
           case ',': res[i]=1;
           break;
           case '?': res[i]=1;
           break;
        }
     }
     return res;
}

/*************************************************************/

char* Key_list::Find(int* code,int code_len,int num){ 
   Key_node* X;
   int i;
   for(X=first,i=0;X!=NULL;X=X->next,i++){
      if((0==memcmp(X->key,code,code_len*sizeof(int)))&&((*X).key_len==code_len)) return (*X).list.Find_word(num);
   }
   return NULL;                 
}

/*************************************************************/

void Key_list::print(){ 
   Key_node* X;
   int k;
   cout<<"key_list:"<<endl;
   for(X=first;X->next!=NULL;X=X->next){
      for(k=0;k<(*X).key_len;k++)cout<<(*X).key[k];cout<<" keylen="<<(*X).key_len<<endl;
      (*X).list.show();
   }
   for(k=0;k<(*X).key_len;k++)cout<<(*X).key[k];cout<<" keylen="<<(*X).key_len<<endl;
   (*X).list.show();
}
/*************************************************************/
/*************************************************************/
/*************************************************************/

int main(void){
    int n,f,i,j,k,code[20];
    char w[20],c,*out;
    Key_list voc;
    memset(w,0,20);
    memset(code,0,20*sizeof(int));
    cin>>n;
    for(i=0;i<n;i++){
       memset(w,0,20);
       cin>>w;
       cin>>f;
       voc.Key_add(w,f);
    }
    memset(w,0,20);
    w[0]='.';
    voc.Key_add(w,200000);
    w[0]=',';
    voc.Key_add(w,100000);
    w[0]='?';
    voc.Key_add(w,1);
//    voc.print();
    c=getchar();
      while(true){
       memset(code,0,20*sizeof(int));         
       for(i=0;;i++){
          c=getchar();
          if(c==' '){
              out=voc.Find(code,i,1);
              for(k=0;k<i;k++)cout<<out[k];cout<<' ';
              break;
          }
          if(c=='1'){
             out=voc.Find(code,i,1);
             for(k=0;k<i;k++)cout<<out[k];
label:       memset(code,0,20*sizeof(int));
             code[0]=1;
             for(j=1;;j++){
                c=getchar();
                if(c==' '){
                   out=voc.Find(code,1,j);
                   cout<<*out<<' ';
                   i=-1;
                   memset(code,0,20*sizeof(int));
                   break;
                }
                if(c=='\n'){
                   out=voc.Find(code,1,j);
                   cout<<*out<<endl;
                   return 0;
                }
                if(c=='1'){out=voc.Find(code,1,j);cout<<*out;goto label;}
                if(c=='*'){continue;}
                else{memset(code,0,20*sizeof(int));code[0]=c-48;i=0;break;}
             }
          }
          if(c=='*'){
             for(j=2;;j++){
                c=getchar();
                if(c==' '){
                   out=voc.Find(code,i,j);
                   for(k=0;k<i;k++)cout<<out[k];cout<<' ';
                   i=-1;
                   break;
                }
                if(c=='\n'){
                   out=voc.Find(code,i,j);
                   for(k=0;k<i;k++)cout<<out[k];cout<<endl;
                   return 0;
                }
                if(c=='1'){
                   out=voc.Find(code,i,j);
                   for(k=0;k<i;k++)cout<<out[k];
                   i=-1;
                   goto label;
                }
             }
          }
          if(c=='\n'){
             out=voc.Find(code,i,1);
             for(k=0;k<i;k++)cout<<out[k];cout<<endl;
             return 0;
          }
          code[i]=c-48;
       }
    }
    return 0;
}
