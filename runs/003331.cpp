#include <iostream>
#include <string.h>
#include <stdio.h>
//#include <conio.h>

using namespace std;

class Word_node//������ ������ ����
{
      friend class Word_list;
      friend class Key_node;
      friend class Key_list;
      public:
             Word_node(char* word,int fr,int length);
             ~Word_node();
      private:
              char* value; //�����
              int freq; //�������
              int length;//?
              Word_node* next; // ����. ��-� ������
              Word_node* prev; // ����. ��-� ������
};

class Word_list //������������� �� ������� ������ ���� �� ������ �����
{
      friend class Word_node;
      friend class Key_node;
      friend class Key_list;
      public:
             Word_list();
             ~Word_list();
             int Add_word(char* word,int freq,int length);
             char* Find_word(int num);
             void show();//������� ��� �������
      private:
              Word_node* start; //������ ��-� ������
};

class Key_node //������ ������ ������
{
      friend class Key_list;
      friend class Word_node;
      friend class Word_list;      
      public:
             Key_node();
             ~Key_node();
      private:

              int* key; //����
              int key_len; //����� �����
              Key_node* prev;
              Key_node* next;
              Word_list list; //������ ���� �� ������� �����
};

class Key_list //������ ������ � ������������������ �������
{
/*�� ����� �� ��� ������� ������, ����� ������� ������ ������, ������ ������ ������ ��������*/      
      friend class Key_node;
      friend class Word_node;
      friend class Word_list; 
      public:
             Key_list();
             ~Key_list();
             int Key_add(char* word,int freq);//���������� �����
             char* Find(int* code,int code_len,int num);//����� ������� ����� �� ����� � ����������� ������ �������
             void print();//���������� ������� ������ ������ ������
      private:
              Key_node *first; //������ ������ ������
              int* compute_key(char* word,int len);//���������� ����� �� �����
};

/*************************************************************/
/*************************************************************/
/*************************************************************/

Word_node::Word_node(char* word,int fr,int length){
   //length=strlen(word);
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

inline int Word_list::Add_word(char* word,int freq,int length){
    Word_node *A;
    Word_node *B;
    A=new Word_node(word,freq,length);
    if(start!=NULL){
         if(start->next!=NULL){
              /*if((*A).freq>(*start).freq){ 
               (*A).next=start;
               start->prev=A;
               start=A;
               return 1;
              }
              start->next=A;
              A->prev=start;
              return 2;                 
         }*/
            for(B=start;B->next!=NULL;B=B->next){//����� ������� ����� � ������
               if((*A).freq>(*B).freq){ 
                  if(B->prev!=NULL)(B->prev)->next=A;
                  (*A).prev=B->prev;
                  (*A).next=B;
                  B->prev=A;
                  return 3;
               }
            }
            if((*A).freq>(*B).freq){ 
               /*if(B->prev!=NULL)*/(B->prev)->next=A;
               (*A).prev=B->prev;
               (*A).next=B;
               B->prev=A;
               return 4;
            }
            (*B).next=A; 
            (*A).prev=B;
         }
         else{
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
    }
    else{
         start=A;
    }
    return 0;                  
}

/*************************************************************/

inline char* Word_list::Find_word(int num){
     Word_node *Q,*A;
     int i;
     char* ret;
     if(num==1){(*start).freq++;return (*start).value;}
     for(Q=start,i=1;i<num;i++,Q=Q->next);
     ret=(*Q).value;
     (*Q).freq++;//���������� �������
     if(Q->prev==NULL)return ret;
     for(A=Q->prev;A!=NULL;A=A->prev){ //����� ������ ����� ����� � ������ ������������ �������
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

inline int Key_list::Key_add(char* word,int freq){ 
    Key_node *X;
    Key_node *Y;
    X=new Key_node;
    (*X).key_len=strlen(word);
    (*X).key=compute_key(word,(*X).key_len);
    if(first!=NULL){
          if(first->next!=NULL){/*
             if(((*first).key_len==(*X).key_len)&&(memcmp((*X).key,(*first).key,(*X).key_len*sizeof(int))==0)){
                (*first).list.Add_word(word,freq);
                delete X;
                return 4;
             }
            (*X).prev=first; 
            first->next=X;
            (*X).list.Add_word(word,freq);
            return 4;
          }*/
             for(Y=first;Y->next!=NULL;Y=Y->next){
                if(((*Y).key_len==(*X).key_len)&&(memcmp((*X).key,(*Y).key,(*X).key_len*sizeof(int))==0)){
                   (*Y).list.Add_word(word,freq,(*X).key_len);
                   delete X;
                   return 1;
                }
             }
             if(((*Y).key_len==(*X).key_len)&&(memcmp((*X).key,(*Y).key,(*X).key_len*sizeof(int))==0)){
                (*Y).list.Add_word(word,freq,(*Y).key_len);
                delete X;
                return 1;
             }
             (*X).prev=Y; 
             Y->next=X;
             (*X).list.Add_word(word,freq,(*X).key_len);
             return 2;
          }
          else{
               if(((*first).key_len==(*X).key_len)&&(memcmp((*X).key,(*first).key,(*X).key_len*sizeof(int))==0)){
                  (*first).list.Add_word(word,freq,(*first).key_len);
                  delete X;
                  return 4;
               }
               (*X).prev=first; 
               first->next=X;
               (*X).list.Add_word(word,freq,(*X).key_len);
               return 4;
          }
    }
    else{
         (*X).list.Add_word(word,freq,(*X).key_len);
         first=X;
         return 3;
    }
    return 0;
}

/*************************************************************/

inline int* Key_list::compute_key(char* word,int len){ 
     //int len;
     //len=strlen(word);
     //len=key_len;
     register int i;
     int* res;
     res=new int[len];
     for(i=0;i<len;i++){
        switch(*(word+i)){
           case 'a': *(res+i)=2;
           break;
           case 'b': *(res+i)=2;
           break;
           case 'c': *(res+i)=2;
           break;
           case 'd': *(res+i)=3;
           break;
           case 'e': *(res+i)=3;
           break;
           case 'f': *(res+i)=3;
           break;
           case 'g': *(res+i)=4;
           break;
           case 'h': *(res+i)=4;
           break;
           case 'i': *(res+i)=4;
           break;
           case 'j': *(res+i)=5;
           break;
           case 'k': *(res+i)=5;
           break;
           case 'l': *(res+i)=5;
           break;
           case 'm': *(res+i)=6;
           break;
           case 'n': *(res+i)=6;
           break;
           case 'o': *(res+i)=6;
           break;
           case 'p': *(res+i)=7;
           break;
           case 'q': *(res+i)=7;
           break;
           case 'r': *(res+i)=7;
           break;
           case 's': *(res+i)=7;
           break;
           case 't': *(res+i)=8;
           break;
           case 'u': *(res+i)=8;
           break;
           case 'v': *(res+i)=8;
           break;
           case 'w': *(res+i)=9;
           break;
           case 'x': *(res+i)=9;
           break;
           case 'y': *(res+i)=9;
           break;
           case 'z': *(res+i)=9;
           break;
           case '.': *(res+i)=1;
           break;
           case ',': *(res+i)=1;
           break;
           case '?': *(res+i)=1;
           break;
        }
     }
     return res;
}

/*************************************************************/

inline char* Key_list::Find(int* code,int code_len,int num){ 
   Key_node* X;
   //int i;
   for(X=first/*,i=0*/;X!=NULL;X=X->next/*,i++*/){
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
    register int i,j,k,f,code[20],size;
    int n;
    register char w[20],c,*out;
    register Key_list voc;
    //memset(w,0,20);
    //memset(code,0,20*sizeof(int));
    cin>>n;
    //if(n>15){cout<<n<<endl;}
    if(n>50000){
                cout<<"Error! N is too long!"<<endl;
                return -1;
    }
    if(n<3){
                cout<<"Error! N is too small!"<<endl;
                return -1;
    }
    for(i=0;i<n;i++){
       memset(w,0,20);
       cin>>w;
       cin>>f;
       voc.Key_add(w,f);
    }
    memset(w,0,20);
    *w='.';
    voc.Key_add(w,400000);
    *w=',';
    voc.Key_add(w,200000);
    *w='?';
    voc.Key_add(w,1);
    size=20*sizeof(int);
//    cout<<"read ok!"<<endl;
//    voc.print();
    /*c=getch();*/c=getchar();
    while(true){
       memset(code,0,size);//20*sizeof(int));         
       for(i=0;;i++){
          /*c=getch();*/c=getchar();
          if((c!=' ')&&(c!='1')&&(c!='*')&&(c!='\n')){*(code+i)=c-48;}
          else if(c==' '){
              out=voc.Find(code,i,1);
              for(k=0;k<i;k++)cout<<*(out+k);cout<<' ';
              break;
          }
          else if(c=='1'){
             out=voc.Find(code,i,1);
             for(k=0;k<i;k++)cout<<*(out+k);
label:       memset(code,0,size);//20*sizeof(int));
             *code=1;
             for(j=1;;j++){
                /*c=getch();*/c=getchar();
                if(c==' '){
                   out=voc.Find(code,1,j);
                   cout<<*out<<' ';
                   i=-1;
                   //memset(code,0,20*sizeof(int));
                   break;
                }
                else if(c=='\n'){
                   out=voc.Find(code,1,j);
                   cout<<*out<<endl;
                   return 0;
                }
                else if(c=='1'){out=voc.Find(code,1,j);cout<<*out;goto label;}
                else if(c=='*'){continue;}
                else{*code=c-48;i=0;break;}
             }
          }
          else if(c=='*'){
             for(j=2;;j++){
                /*c=getch();*/c=getchar();
                if(c==' '){
                   out=voc.Find(code,i,j);
                   for(k=0;k<i;k++)cout<<*(out+k);cout<<' ';
                   i=-1;
                   break;
                }
                else if(c=='\n'){
                   out=voc.Find(code,i,j);
                   for(k=0;k<i;k++)cout<<*(out+k);cout<<endl;
                   return 0;
                }
                else if(c=='1'){
                   out=voc.Find(code,i,j);
                   for(k=0;k<i;k++)cout<<*(out+k);
                   //i=-1;
                   goto label;
                }
             }
          }
          else if(c=='\n'){
             out=voc.Find(code,i,1);
             for(k=0;k<i;k++)cout<<*(out+k);cout<<endl;
             return 0;
          }
/*          if((i<20)||(i>-1))code[i]=c-48;
          else*/ if(i>20){
               cout<<"incorrect length!,i="<<i<<endl;
               return -2;
          }
       }
    }
    return 0;
}
