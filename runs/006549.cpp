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
     }
}; // CWord
// --------------------------------------------------------------------------

// Класс набора слов, соответствующих заданной комбинации кнопок
class CSetWords
{
  private:
     vector<CWord*> words;
     vector<CWord*> order;  // порядок выдачи слов
  public:
     CSetWords(CWord *word) { AddWord(word); }
     void AddWord(CWord *word) { words.push_back(word); }
     vector<CWord*>& GetWords() { return words; }
     vector<CWord*>& GetOrder() { return order; }
     void SetNewOrder(CWord *word,size_t j);
     void SetOrder();
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

void CSetWords::SetOrder(void)
{    vector<CWord*>::iterator li;
	/**********************************************************************/
     for(size_t i=0;i<words.size();i++)
     {
        if(!i)
           order.push_back(words[i]);
        else
        {
           li=order.begin();
           while(li!=order.end() && (*li)->GetFreq()>=words[i]->GetFreq())
              li++;
           order.insert(li,words[i]);
        }
     }
} /* CSetWords::SetOrder */
/***************************************************************************/

void CSetWords::SetNewOrder(CWord *word,size_t j)
{    vector<CWord*> temp=order;
     vector<CWord*>::iterator li;
     // j - номер выбранного слова
     // i - номер просматриваемого слова в цикле
     // k - размер смещения слова в векторе популярности order
     size_t i=0,k=j;
	/**********************************************************************/
	if(k)
     {
        while(k>0 && word->GetFreq()>=order[k-1]->GetFreq())
           k--;
     }
     li=order.begin();
     while(li!=order.end())
     {
        if(i==k)
           order[i]=temp[j];
        else if(i<k || i>j)
           order[i]=temp[i];
        else
           order[i]=temp[i-1];
        i++;
        li++;
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
           if(next>=set->GetOrder().size())
              next=set->GetOrder().size()-1;
           w=set->GetOrder()[next];
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

