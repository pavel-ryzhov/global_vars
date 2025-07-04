#include <iostream>
#include <fstream>
#include <string.h>

struct TListData{
  char* word;// word in our dictionary
  int freq;//frequency of this word
 };// struct TListData

/*-----------Basic functions-------------*/
int MyMax(int a,int b)// returns a maximum of 2 elements
 {
  if (a>b) return a;else return b;
 }// end MyMax

char* MyStrCopy(const char* s)
 {
  int i;
  char* s1;
  s1=new char[strlen(s)+1];
  for(i=0;s[i]!='\0';i++) s1[i]=s[i];
  s1[i]='\0';
  return s1;
 }// MyStrCopy

/*-----------struct TTree----------------*/

struct TListElem{
  TListData  data;// data field
  TListElem* next;// a pointer to a next element
  // methods
  TListElem() {data.word=NULL;data.freq=0;next=NULL;}
 };// struct TListElem

struct TList{
  TListElem* list;// a pointer to a begining of our list
  // methods
  TList(){list=NULL;}
  void AddElem(TListData elem);// adds an element to list
  void PrintList(){PrintListElem(list);}
  void PrintListElem(TListElem* elem);
 };// struct TList

/*---------------Struct TList---------------------------*/
void TList::AddElem(TListData elem)
 {
  TListElem *p1,*NewElem;

  if(list!=NULL)
   {
    // creating a new element
    NewElem=new TListElem;
    NewElem->data.word=MyStrCopy(elem.word);
    NewElem->data.freq=elem.freq;
    // Now we will find a place for this element
    if(elem.freq>list->data.freq || (elem.freq==list->data.freq && (strcmp(elem.word,list->data.word)<0)))
     {// this element must be inserted before first element
      NewElem->next=list;
      list=NewElem;
     }
    else
     {// searching the place
      p1=list;
      while(p1->next!=NULL && (elem.freq<p1->next->data.freq || (elem.freq==p1->next->data.freq 
            &&(strcmp(elem.word,p1->next->data.word)>0)))) p1=p1->next;
      // now we found a place so inserting
      NewElem->next=p1->next;
      p1->next=NewElem;
     }
   }// if p1!=NULL
  else// this is the first element in list
   {
    list=new TListElem;
    list->data.word=MyStrCopy(elem.word);
    list->data.freq=elem.freq;
   }// else
 }// end AddElem()
/*---------------Struct TList---------------------------*/
struct TNode{
  char* key;// key of elem --- string of 20 characters from "2" to "9";
  TList data;// data of elem --- list of words
  int LeftSubHeight,RightSubHeight;// heights of left and right subtrees of our tree
  TNode* left,* right;// left and right subtrees
  // methods
  TNode(){ LeftSubHeight=RightSubHeight=0;left=right=NULL;data.list=NULL;key=NULL;}
  ~TNode(){delete key;}// destructor TNode
 };

struct TTree{
  TNode* root;
  // methods
  TTree();// constructor
  ~TTree();// destructor
  void AddElem(char* key1,TListData data1);// adding an element to our tree
  TNode* AddElement(TNode* subtree,char* key1,TListData data1);// adds element to subtree
  TNode* Balance(TNode* subtree,int bal);// balance a subtree
  /*------Turns for balancing-------------*/
  TNode* MakeLeftSmallTurn(TNode* subtree);
  TNode* MakeLeftBigTurn(TNode* subtree);
  TNode* MakeRightBigTurn(TNode* subtree);
  TNode* MakeRightSmallTurn(TNode* subtree);
  TNode* GetNodeFromTree(char* key){return GetNodeFromSubTree(root,key);}
  TNode* GetNodeFromSubTree(TNode* subtree,char* key);
  void Print();// prints a tree to a screen
  void PrintSubTree(TNode* subtree);
  void MyDelete(TNode* subtree);// removes subtree from memory
 };


TTree::TTree()
 {
  root=NULL;
 }// constructor TTree

TTree::~TTree()
 {// we need recursivly delete memory
  MyDelete(root);
 }// destructor TTree

void TTree::MyDelete(TNode* root)
 {
  if(root!=NULL)
   {
    MyDelete(root->left);
    MyDelete(root->right);
    delete root;
   }// end if root!=NULL
 }// end MyDelete

/*--------Print()-----------------------*/
void TTree::Print()
 {
  PrintSubTree(root);
 }// end Print

void MyPrintStr(const char* s)
 {
  int i;

  for(i=0;s[i]!='\0';i++) std::cout<<s[i];
 }// MyPrintStr;

void TList::PrintListElem(TListElem* elem)
 {
  if(elem!=NULL)
   {
    std::cout<<"Word:";MyPrintStr(elem->data.word);std::cout<<".Frequency "<<elem->data.freq<<".\n";
    PrintListElem(elem->next);// printing next element
   }// end if elem!=NULL
 }// end PrintList

void TTree::PrintSubTree(TNode* subtree)
 {
  if(subtree!=NULL)
   {
    if(subtree->left==NULL && subtree->right==NULL) std::cout<<"Leaf ";else std::cout<<"Node ";
    MyPrintStr(subtree->key);std::cout<<" ";
    std::cout<<"LeftSubHeight: "<<subtree->LeftSubHeight<<" RightSubHeight: "<<subtree->RightSubHeight<<" !\n";
    subtree->data.PrintList();
    if(subtree->left!=NULL)
     {
      std::cout<<"Left SubTree:\n";
      PrintSubTree(subtree->left);
     }
    if(subtree->right!=NULL)
     {
      std::cout<<"RightSubtree:\n";
      PrintSubTree(subtree->right);
     }
   }
  }// end print Subtree
/*--------Print()-----------------------*/

/*---------------Add Elem()-----------------*/
void TTree::AddElem(char* key1,TListData data1)// add element tp our tree
 {// begin AddElem
  root=AddElement(root,key1,data1);
 }// end   AddElem
/*---------------Add Elem()-----------------*/

/*-------------AddElement()----------------*/
TNode* TTree::AddElement(TNode* subtree,char* key1,TListData data1)
 {// adds element to subtree of our tree
  int bal,rez;// balance
  TNode* NewSubTree;

  if (subtree==NULL) 
   {// this is first element in this subtree
    NewSubTree=new TNode;// creating a new element of our tree
    NewSubTree->key=MyStrCopy(key1);
    NewSubTree->data.AddElem(data1);
    return NewSubTree;
   }// end if subtree==NULL
  else
   {// This is not first element.
    rez=strcmp(key1,subtree->key);// comparing key and key1
//    std::cout<<"This is function add elem:\n";
//    MyPrintStr(key1);std::cout<<'\n';MyPrintStr(subtree->key);std::cout<<'\n';
    if(rez<0) subtree->left=AddElement(subtree->left,key1,data1);
    else if(rez>0) subtree->right=AddElement(subtree->right,key1,data1);
    else // we need to add element to this list
     subtree->data.AddElem(data1);
    // Now we added the element.We need to renew our heights
    if(subtree->left!=NULL) subtree->LeftSubHeight=MyMax(subtree->left->LeftSubHeight,subtree->left->RightSubHeight)+1;
    else subtree->LeftSubHeight=0;
    if(subtree->right!=NULL) subtree->RightSubHeight=MyMax(subtree->right->LeftSubHeight,subtree->right->RightSubHeight)+1;
    else subtree->RightSubHeight=0;
    // Heights are setted.Now we need to check that tree is balanced
    bal=subtree->RightSubHeight-subtree->LeftSubHeight;
    if(bal<-1 || bal>1) return Balance(subtree,bal);// we need to balance it
    return subtree;
   }// end else
 }// end AddElement
/*------------Add Element()-----------------*/

/*-------------Balance()--------------------*/
TNode* TTree::Balance(TNode* subtree,int bal) // we use this function for balancing subtree
 {// begin Balance
  TNode* LeftSubTree,* RightSubTree,* NewSubTree;

  LeftSubTree=subtree->left; RightSubTree=subtree->right;
  if(bal<0)
   {// left subtree is more than right sub tree
    if(LeftSubTree->LeftSubHeight>=LeftSubTree->RightSubHeight) NewSubTree=MakeLeftSmallTurn(subtree);
    else NewSubTree=MakeLeftBigTurn(subtree);
   }// end if bal<0
  else // right subtree is more than left subtree
   if(RightSubTree->RightSubHeight>=RightSubTree->LeftSubHeight) NewSubTree=MakeRightSmallTurn(subtree);
   else NewSubTree=MakeRightBigTurn(subtree);
   return NewSubTree;
 }//  end Balance
/*-------------Balance()--------------------*/

/*-------------Turns------------------------*/
TNode* TTree::MakeLeftSmallTurn(TNode* subtree)
 {
  TNode* t;
  int a;

  a=subtree->left->RightSubHeight;
  t=subtree->left;
  subtree->left=t->right;
  t->right=subtree;
  subtree->LeftSubHeight=a;// height changed
  t->RightSubHeight=MyMax(a,subtree->RightSubHeight)+1;
  return t;
 }// end MakeLeftSmallTurn

TNode* TTree::MakeLeftBigTurn(TNode* subtree)
 {
  TNode* t;
  int a,b;

  t=subtree->left->right;
  // saving heights
  a=t->LeftSubHeight;b=t->RightSubHeight;
  //making changes
  subtree->left->right=t->left;
  t->left=subtree->left;
  subtree->left=t->right;
  t->right=subtree;
  // getting new heights
  t->left->RightSubHeight=a;
  subtree->LeftSubHeight=b;
  t->LeftSubHeight=MyMax(t->left->LeftSubHeight,a)+1;
  t->RightSubHeight=MyMax(b,subtree->RightSubHeight);
  return t;
 }// end MakeLeftBigTurn

TNode* TTree::MakeRightBigTurn(TNode* subtree)
 {
  TNode* t=subtree->right->left;
  int a,b;

  //saving heights
  a=t->LeftSubHeight;b=t->RightSubHeight;
  //making changes
  subtree->right->left=t->right;
  t->right=subtree->right;
  subtree->right=t->left;
  t->left=subtree;
  // setting heights
  subtree->RightSubHeight=a;
  t->right->LeftSubHeight=b;
  t->LeftSubHeight=MyMax(subtree->LeftSubHeight,a)+1;
  t->RightSubHeight=MyMax(b,t->right->RightSubHeight)+1;
  return t;
 }// end MakeRightBigTurn

TNode* TTree::MakeRightSmallTurn(TNode* subtree)
 {
  TNode* t=subtree->right;
  int a;

  a=t->LeftSubHeight;
  //making changes
  subtree->right=t->left;
  t->left=subtree;
  // setting heigts
  subtree->RightSubHeight=a;
  t->LeftSubHeight=MyMax(subtree->LeftSubHeight,a)+1;
  return t;
 }// end MakeRightSmallTurn
/*-------------Turns------------------------*/

/*-------------Get Node---------------------*/
TNode* TTree::GetNodeFromSubTree(TNode* subtree,char* key)
 {
  int a;

  if(subtree!=NULL)
   {
    a=strcmp(subtree->key,key);// comparing keys
    if(a==0) return subtree;
    if(a<0) return GetNodeFromSubTree(subtree->right,key);
    if(a>0) return GetNodeFromSubTree(subtree->left,key);
   }// end if subtree!=NULL
  else std::cerr<<"This word isn't in the dictionary!\n";
 }// end GetNodeFromSubTree
/*-------------Get Node---------------------*/

/*-----------struct TTree----------------*/
/*-----------global variables------------*/
TTree* mytree;// a pointer to a tree
char* Letters;// special array
//std::ifstream myin("test.txt");

void Init()
 {
  int i;

  Letters=new char[26];
  Letters[0]='2';Letters[1]='2';Letters[2]='2';Letters[3]='3';Letters[4]='3';
  Letters[5]='3';Letters[6]='4';Letters[7]='4';Letters[8]='4';Letters[9]='5';
  Letters[10]='5';Letters[11]='5';Letters[12]='6';Letters[13]='6';Letters[14]='6';
  Letters[15]='7';Letters[16]='7';Letters[17]='7';Letters[18]='7';Letters[19]='8';
  Letters[20]='8';Letters[21]='8';Letters[22]='9';Letters[23]='9';Letters[24]='9';
  Letters[25]='9';
 }// Init

void GetNumberStringFromWord(char* Word,int LengthOfWord,char* key)
 {// making a number string of this word
  int i;
  char c;

  key[LengthOfWord]='\0';
  for(i=0;i<LengthOfWord;i++) key[i]=Letters[Word[i]-'a'];// getting a number string
 }// end GetNumberStringFromWord

void MakeTreeOfWords()
 {// this procedure creates a tree of words from our dictionary
  int i,NumberOfWords,StringLength,Frequency;
  char c=' ',* CurrentString,* KeyString;
  TListData CurrentData;

  mytree=new TTree;
  CurrentData.word=new char[21];// this is our current word
  KeyString=new char[21];
  std::cin>>NumberOfWords;// get NumberOfWords in dictionary
  for(i=0;i<NumberOfWords;i++)
   {
    c=' ';StringLength=0;// a length of our string
    while(c==' ' || c=='\t' || c=='\n') std::cin.get(c);
    // we think that now c is a first charecter of our word
    while(c!=' ')
     {
      CurrentData.word[StringLength]=c;
      StringLength++;
      std::cin.get(c);// getting next symbol
     }// end while
    CurrentData.word[StringLength]='\0';
    // now we have word in our string
    std::cin>>Frequency;// get Frequency
    CurrentData.freq=Frequency;// setting frequency
    GetNumberStringFromWord(CurrentData.word,StringLength,KeyString);// making a keystring
    mytree->AddElem(KeyString,CurrentData);// adding an element to our tree
   }// for i
  delete KeyString;
 }// end MakeTreeOfWords

char* GetWordFromTree(char* KeyString,int NumberOfWord)
 {//returns a word for this key and number
  TNode* node;
  TListElem* myelem,*p1,*myelem1;
  int i,NewFrequency;
  char* MyWord;

//  std::cout<<"This is function GetWordFromTree:\n";
  node=mytree->GetNodeFromTree(KeyString);// getting node for us
  // finding an element with word
  myelem=node->data.list;
  if(NumberOfWord==1)
   {//the first word
    MyWord=MyStrCopy(myelem->data.word);// getting a word
//    std::cout<<"This is a word from procedure GetWordFromTree: ";MyPrintStr(MyWord);std::cout<<"\n";
    myelem->data.freq++;// inc frequency of this word
   }
  else
   {
    for(i=1;i<NumberOfWord-1;i++) myelem=myelem->next;// finding a previous element
    // getting a word
    MyWord=MyStrCopy(myelem->next->data.word);
//    std::cout<<"Word is got! ";MyPrintStr(MyWord);std::cout<<'\n';
//    node->data.PrintList();
    myelem->next->data.freq++;
    // all changes done
    myelem1=myelem->next;myelem->next=myelem1->next;// we decluded this element from our list
    // we need to insert this element in a new place
    p1=node->data.list;NewFrequency=myelem1->data.freq;
    // we need to check first element
    if(node->data.list->data.freq<=NewFrequency)
     {// we must insert before first element
      myelem1->next=node->data.list;
      node->data.list=myelem1;
     }// end if
    else
     {
      while(p1->next!=NULL && p1->next->data.freq>NewFrequency) p1=p1->next;
      myelem1->next=p1->next;
      p1->next=myelem1;//now we inserted our element to right place
     }
    // we found a place for inserting
   }// end else
  return MyWord;
 }// end GetWordFromTree

void MakingAnswer()// this procedure making answer on our string
 {
  char c,* CurrentString,StringLength,*word;
  int k;

  CurrentString=new char[21];// word can't be more than 20 characters
  c='0';
  while((c<'1' || c>'9') && c!=' ') std::cin.get(c);// getting first symbol
  while(c!='\n')
   {// while string is not ended
    StringLength=0;
//    std::cout<<"Current word!: ";
    while(c>='2' && c<='9') 
     {// while c is in word
      CurrentString[StringLength]=c;// making word
//      std::cout<<c;
      StringLength++;
      std::cin.get(c);// getting new character
     }// end while 2<=c<=9
    // now we got a word
    CurrentString[StringLength]='\0';//std::cout<<'\n';
    k=1;
    while(c=='*') {k++;std::cin.get(c);}// getting a number of word in list
//    std::cout<<"This is k: "<<k<<'\n';
    word=GetWordFromTree(CurrentString,k);// getting a word from dictionary
    MyPrintStr(word);// printing word
    while(c!='\n' && (c<'2' || c>'9'))
     {
     if(c=='1')
      {// we have a point
       k=1;std::cin.get(c);
       while(c=='*') {k++;std::cin.get(c);}
       switch(k)
        {
         case 1:std::cout<<'.';break;
         case 2:std::cout<<',';break;
         default:std::cout<<'?';break;
        }//end switch
      }//end if c=='1'
     if (c==' ') {std::cout<<' ';std::cin.get(c);}
    }// while
   }// while c!='\n'
 }// end Making Answer
int main()
 {
  int n,i,elem; 

  Init();
  MakeTreeOfWords();// making our dictionary
//  mytree->Print();
  // now we need to get an answer for our request
  MakingAnswer();
  std::cout<<'\n';
  //std::cout<<"Hello world!\n";
  return 0;
 }/* main end */
