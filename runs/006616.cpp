#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const char key[]={'.', ',', '?'};

const int NKEYS=29;         // мощность алфавита телефона
const int kn[NKEYS]={1, 1, 1,
                     2, 2, 2,
                     3, 3, 3,
                     4, 4, 4,
                     5, 5, 5,
                     6, 6, 6,
                     7, 7, 7, 7,
                     8, 8, 8,
                     9, 9, 9, 9};

class CWord;
struct SNode;
class CList;
class CSetWords;
class CNode;
class CTree;
class CMessage;

// Класс слова из словаря
class CWord
{
  private:
     vector<char> word;
     int freq;  // частота встречаемости слова в словаре
  public:
     CWord(vector<char> word, int freq)
     {
        this->word=word;
        this->freq=freq;
     }
     vector<char>& GetWord() { return word; }

     int GetFreq() { return freq; }
     void SetFreq(int freq) { this->freq=freq; }

     void PrintWord()
     {
        for(size_t i=0;i<word.size();i++)
           cout<<word[i];
        //cout<<freq;
     }
}; // CWord
// --------------------------------------------------------------------------

struct SNode
{
     CWord* word;
     SNode* next;
     SNode* prev;
  public:
     SNode() { next=prev=NULL; }
}; // SNode
// --------------------------------------------------------------------------

class CList
{
  private:
     SNode** list;    // список
     SNode* top;      // первый элемент в списке
     SNode* last;     // последний элемент в списке
     unsigned int n;  // размер списка
  public:
     CList(int n)
     {
        this->n=n;
        top=last=NULL;
        list=new SNode* [n];
        for(int i=0;i<n;i++)
        {
           list[i]=NULL;
           list[i]=new SNode;
        } /* i */
     }
     ~CList()
     {
        for(unsigned int i=0;i<n;i++)
           if(list[i]!=NULL)
              delete list[i];
        delete[] list;
     }
     SNode** GetList() { return list; }
     unsigned int GetSize() { return n; }

     SNode* GetNode(int n_)
     {
        SNode* temp=top;
        for(int i=0;i<n_;i++)
           temp=temp->next;
        return temp;
     }

     SNode* GetTop() { return top; }
     void SetTop(SNode* top) { this->top=top; }

     void SetOrder(vector<CWord*>& words)
     {
        for(size_t i=0;i<words.size();i++)
        {
           list[i]->word=words[i];
           if(!i)
           {
              top=last=list[i];
           }
           else
           {
              SNode* temp=top;
              while(temp!=NULL && temp->word->GetFreq()>=words[i]->GetFreq())
                 temp=temp->next;
              if(temp==NULL) // последний элемент
              {
                 list[i]->prev=last;
                 last->next=list[i];
                 last=list[i];
              }
              else
              {
                 list[i]->prev=temp->prev;
                 if(temp->prev!=NULL)
                    temp->prev->next=list[i];
                 list[i]->next=temp;
                 temp->prev=list[i];
              }
              if(list[i]->prev==NULL)
                 top=list[i];
           }
        } /* i */
     }
     
     void Print()
     {
        SNode* temp=top;
        while(temp!=NULL)
        {
           temp->word->PrintWord();
           cout<<"|";//<<temp->word->GetFreq();
           temp=temp->next;
        }
        cout<<endl;
     }
}; // CList
// --------------------------------------------------------------------------

// Класс набора слов, соответствующих заданной комбинации кнопок
class CSetWords
{
  private:
     vector<CWord*> words;
     CList *order;
  public:
     CSetWords(CWord *word) { AddWord(word); }
     ~CSetWords() { delete order; }

     void AddWord(CWord *word) { words.push_back(word); }
     vector<CWord*>& GetWords() { return words; }
     CList* GetOrder() { return order; }
     void SetNewOrder(CWord *word,size_t j);

     void SetOrder()
     {
        order=new CList(words.size());
        order->SetOrder(words);
     }

     void Print()
     {
        for(size_t i=0;i<words.size();i++)
        {
           words[i]->PrintWord();
           cout<<"|";
        }
        cout<<endl;
     } /* CSetWords::Print */
}; // CSetWords
// --------------------------------------------------------------------------

void CSetWords::SetNewOrder(CWord *word,size_t j)
{    SNode *temp,*node;
     // j - номер выбранного слова
     // i - номер просматриваемого слова в цикле
     // k - размер смещения слова в векторе популярности order
     size_t k=j;
	/**********************************************************************/
     temp=order->GetNode(k);
     node=order->GetNode(j);
	if(k)
     {
        while(temp->prev!=NULL && word->GetFreq()>=temp->prev->word->GetFreq())
        {
           k--;
           temp=temp->prev;
        }
     }

     if(temp==NULL)
        temp=order->GetTop();

     if(j!=k)
     {
        // удаление элемента
        if(node->prev!=NULL) node->prev->next=node->next;
        if(node->next!=NULL) node->next->prev=node->prev;

        // вставка элемента
        node->prev=temp->prev;
        if(node->prev!=NULL) node->prev->next=node;
        node->next=temp;
        temp->prev=node;

        if(node->prev==NULL)
           order->SetTop(node);
     }
} /* CSetWords::SetNewOrder */
/***************************************************************************/

class CTree
{
  private:
     CTree* branch[8];
     CSetWords *set;
  public:
     CTree()
     {
        for(int i=0;i<8;i++)
           branch[i]=NULL;
        set=NULL;
     }
     ~CTree()
     {
        for(int i=0;i<8;i++)
           if(branch[i]!=NULL)
              delete branch[i];
        if(set!=NULL)
           delete set;
     }
     void AddBranch(CWord* word)
     {
        CTree *t=this;
        vector<char> &w=word->GetWord();
        for(unsigned int i=0;i<w.size();i++)
        {
           int j=kn[w[i]-97+3]-2;
           if(t->branch[j]==NULL)
              t->branch[j]=new CTree;
           t=t->branch[j];
        } /* i */
        if(t->set==NULL)
           t->set=new CSetWords(word);
        else
           t->set->AddWord(word);
     }

     CSetWords* GetSet(vector<char>& cword)
     {
        CTree *t=this;
        for(size_t i=0;i<cword.size();i++)
        {
           int i_=cword[i]-48-2;
           t=t->branch[i_];
        }
        return t->set;
     }

     void SetOrder()
     {
        for(int i=0;i<8;i++)
        {
           if(branch[i]!=NULL)
           {
              CTree *t=branch[i];
              if(t->set!=NULL)
                 t->set->SetOrder();
              t->SetOrder();
           }
        } /* i */
     }

     void Print()
     {
        cout<<endl;
        for(int i=0;i<8;i++)
           if(branch[i]!=NULL)
           {
              CTree* t=branch[i];
              cout<<i+2<<" ";
              if(t->set!=NULL)
                 t->set->Print();
              t->Print();
           }
     }
}; // CTree
// --------------------------------------------------------------------------

// Класс текстового сообщения
class CMessage
{
  private:
     vector< vector<char> > message;
  public:
     void AddWord(vector<char> word)
     {
        if(word.size())
           message.push_back(word);
     }
     vector< vector<char> >& GetMessage(void) { return message; };
     void DecodeMessage(CTree& tree);
}; // CMessage
// --------------------------------------------------------------------------

void CMessage::DecodeMessage(CTree& tree)
{    vector<char> cWord; // исходное слово в режиме Т9
	vector<char> word;  // исходное слово в режиме Т9 без '*'
     vector<char>::iterator pos;
     CWord *w;
     unsigned int next=0; // число символов '*' в конце слова
	/**********************************************************************/
     for(size_t i=0;i<message.size();i++)
     {
        cWord=message[i];
        if(cWord[0]==' ')
        {
           cout<<' '; continue;
        }
        if(cWord[0]=='1')
        {
           int k=cWord.size()-1; // число '*' после символа '1'
           if(k>2) k=2;
           cout<<key[k]; continue;
        }
        word=cWord;

        // получение комбинаций кнопок без символов '*'
        pos=remove(word.begin(),word.end(),(char)'*');
        word.erase(pos,word.end());
        next=cWord.size()-word.size();

        CSetWords *set=tree.GetSet(word);
        if(set!=NULL)
        {
           if(next>=set->GetOrder()->GetSize())
              next=set->GetOrder()->GetSize()-1;
           w=set->GetOrder()->GetNode(next)->word;
           w->PrintWord();
           // изменение частоты слова в словаре
           int freq=w->GetFreq()+1;
           w->SetFreq(freq);
           // перераспределение очередности выдачи слов
           set->SetNewOrder(w,next);
        }
     } /* i */
} /* CMessage::DecodeMessage */
/***************************************************************************/

int main()
{    int n; // число слов в словаре
     char c;
     vector<char> curWord;
     CMessage *message;
     CTree tree;
     /**********************************************************************/
     // чтение слов, запись в словарь words
     cin>>n;
     for(int i=0;i<n;i++)
     {
        int curFreq=0;
        curWord.clear();
        cin.get(); // пропуск символа перевода строки
        while((c=cin.get())!=' ')
           curWord.push_back(c);
        cin>>curFreq;

        CWord *w=new CWord(curWord,curFreq);
        tree.AddBranch(w);
     } /* i */
     tree.SetOrder();
     //tree.Print();

     // чтение сообщения в режиме Т9
     message=new CMessage();
     cin.get();  // пропуск символа перевода строки
     curWord.clear();
     while((c=cin.get())!='\n')
     {
        if(c=='*' && curWord.size()==0)
           continue; // пропуск начальных символов '*'
        if(c!=' ' && c!='1')
        {
           if(c!='*' && curWord.size()!=0)
           {
              char c_=curWord.at(curWord.size()-1);
              if(c_=='*' || c_=='1')
              {
                 message->AddWord(curWord);
                 curWord.clear();
              }
           }
           curWord.push_back(c);
        }
        else
        {
           message->AddWord(curWord);
           curWord.clear();
           curWord.push_back(c);
           if(c==' ')
           {
              message->AddWord(curWord);
              curWord.clear();
           }
        }
     }
     if(curWord.size())
        message->AddWord(curWord);

     // расшифровка сообщения
     message->DecodeMessage(tree);

     delete message;
     return 0;
} /* main */
/***************************************************************************/

