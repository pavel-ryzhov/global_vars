#include <iostream>
#include <vector>
//#include <conio.h>

using namespace std;

const int NKEYS=29;          // �������� �������� ��������

const char key[NKEYS]={'.', ',', '?',
                       'a', 'b', 'c',
                       'd', 'e', 'f',
                       'g', 'h', 'i',
                       'j', 'k', 'l',
                       'm', 'n', 'o',
                       'p', 'q', 'r', 's',
                       't', 'u', 'v',
                       'w', 'x', 'y', 'z'};

const int kn[NKEYS]={1, 1, 1,
                     2, 2, 2,
                     3, 3, 3,
                     4, 4, 4,
                     5, 5, 5,
                     6, 6, 6,
                     7, 7, 7, 7,
                     8, 8, 8,
                     9, 9, 9, 9};

// ����� ������
struct SStr
{
     char* str;
     int size;
     SStr(char* str,int size)
     {
        this->str=str;
        this->size=size;
     }
     ~SStr() { delete[] str; };
}; // SStr
// --------------------------------------------------------------------------

bool IsStringsEqual(SStr* s1, SStr* s2)
{
     if(s1->size!=s2->size)
        return false;
     for(int i=0;i<s1->size;i++)
        if(s1->str[i]!=s2->str[i])
           return false;
     return true;
} /* IsStringsEqual */
/***************************************************************************/

// ����� ����� �� �������
class CWord
{
  private:
     SStr* word;
     SStr* kword; // ������������������ ������ ��� ������ �����

     int freq;  // ������� ������������� ����� � �������
  public:
     CWord(SStr* word, int wordSize, int freq)
     {
        this->word=word;
        this->freq=freq;
        kword=new SStr(new char[wordSize],wordSize);
     }
     ~CWord()
     {
        delete word;
        delete kword;
     }
     SStr* GetWord() { return word; }
     SStr* GetKWord() { return kword; }

     int GetFreq() { return freq; }
     void SetFreq(int freq) { this->freq=freq; }

     void WordToT9();

     void PrintWord()
     {
        for(int i=0;i<word->size;i++)
           cout<<word->str[i];
     }
}; // CWord
// --------------------------------------------------------------------------

// ����� �������
class CGlossary
{
  private:
     vector<CWord*> words;
     int size;
  public:
     CGlossary() { size=0; }
     ~CGlossary()
     {
        for(int i=0;i<size;i++)
           delete words[i];
     }
     void AddWord(CWord *word)
     {
        words.push_back(word);
        size++;
     }
     vector<CWord*>& GetGlossary() { return words; }
     int GetSize() { return size; }
     void PrintGlossary()
     {
        for(int i=0;i<size;i++)
        {
           words[i]->PrintWord();
           cout<<" "<<words[i]->GetFreq()<<endl;
        }
     }
}; // CGlossary
// --------------------------------------------------------------------------

// ����� ������ ����, ��������������� �������� ���������� ������
class CSetWords
{
  private:
     //vector<CWord*> words;
     CWord** words;
     int size; // ����� ���� � ������

     SStr* kword; // ������� ��������� ���� � ������
     int wordSize;

     CWord** order; // ������� ������ ����
     int orderSize;
  public:
     CSetWords(CWord *word,int size_)
     {
        words=new CWord* [size_];
        words[0]=word;
        //words.push_back(word);
        kword=word->GetKWord();
        wordSize=word->GetWord()->size;
        size=1;
        orderSize=0;
     }
     ~CSetWords() { delete[] words; delete[] order; }
     void AddWord(CWord *word)
     {
        words[size]=word;
        //words.push_back(word);
        size++;
     }

     CWord** GetOrder() { return order; }
     //vector<CWord*>& GetOrder() { return order; }
     void SetNewOrder(CWord *word,int j);

     SStr* GetKWord() { return kword; }
     int GetWordSize() { return wordSize; }
     int GetOrderSize() { return orderSize; }

     void SetOrder();
     void Print()
     {
        cout<<"kword:";
        for(int i=0;i<wordSize;i++)
           cout<<kword->str[i];
        cout<<endl;
        for(int i=0;i<size;i++)
        {
           words[i]->PrintWord();
           cout<<"|";
        }
        cout<<endl;
     } /* CSetWords::Print */
}; // CSetWords
// --------------------------------------------------------------------------

class CSets
{
  private:
     CSetWords **sets;
     int size;
  public:
     CSets(int size_)
     {
        size=0;
        sets=new CSetWords* [size_];
     }
     ~CSets()
     {
        for(int i=0;i<size;i++)
           delete sets[i];
        delete[] sets;
     }
     void AddSet(CSetWords *set)
     {
        sets[size]=set;
        size++;
     }
     CSetWords** GetSets() { return sets; }
     int GetSize() { return size; }
}; // CSets

void CSetWords::SetOrder(void)
{
     order=new CWord* [size];
     for(int i=0;i<size;i++)
     {
        if(!i)
           order[i]=words[i];
        else
        {
           int j=0;
           while(j<orderSize && order[j]->GetFreq()>=words[i]->GetFreq())
              j++;
           for(int k=orderSize; k>j; k--)
              order[k]=order[k-1];
           order[j]=words[i];
        }
        orderSize++;
     } /* i */
} /* CSetWords::SetOrder */
/***************************************************************************/

void CSetWords::SetNewOrder(CWord *word,int j)
{    // j - ����� ���������� �����
     // i - ����� ���������������� ����� � �����
     // k - ������ �������� ����� � ������� ������������ order
     int k=j;
	/**********************************************************************/
     CWord** temp=new CWord* [orderSize]; // ����� ������ order
     for(int i=0;i<orderSize;i++)
        temp[i]=order[i];

     if(k)
     {
        while(k>0 && word->GetFreq()>=order[k-1]->GetFreq())
           k--;
     }

     for(int i=0;i<orderSize;i++)
     {
        if(i==k)
           order[i]=temp[j];
        else if(i<k || i>j)
           order[i]=temp[i];
        else
           order[i]=temp[i-1];
     }

     delete[] temp;
} /* CSetWords::SetNewOrder */
/////***************************************************************************/

// ����� ���������� ���������
class CMessage
{
  private:
     //vector< vector<char> > message;
     //SStr* message[MAXMESSAGE];
     vector<SStr*> message;
     int size;
     int nextCount; // ����� �������� '*' ����� �����
  public:
     CMessage() { size=0; }
     ~CMessage()
     {
        for(int i=0;i<size;i++)
           delete message[i];
     }
     void AddWord(vector<char> curWord)
     {
        int curSize=curWord.size();
        if(curSize)
        {
           char* newWord=new char[curSize];
           for(int j=0;j<curSize;j++)
              newWord[j]=curWord[j];
           //message[size]=new SStr(newWord,curSize);
           SStr *str=new SStr(newWord,curSize);
           message.push_back(str);
           size++;
        }
     }
     //SStr** GetMessage(void) { return message; };
     vector<SStr*>& GetMessage(void) { return message; };
     int GetSize() { return size; }
     void DecodeMessage(CGlossary &glossary,CSets* setWords);
}; // CMessage
// --------------------------------------------------------------------------

// ������ ���� ������� � ���� ������������������� ������� ������
void CWord::WordToT9(void)
{
     for(int i=0;i<word->size;i++)
        for(int k=0;k<NKEYS;k++)
           if(word->str[i]==key[k])
           {
              kword->str[i]=kn[k]+48;
              break;
           }
} /* CWord::WordToT9 */
/////***************************************************************************/

void CMessage::DecodeMessage(CGlossary &glossary,CSets* setWords)
{    SStr* cWord; // �������� ����� � ������ �9
     CWord *w;
     int j;
     int next=0; // ����� �������� '*' � ����� �����
	/**********************************************************************/
     for(int i=0;i<size;i++)
     {
        cWord=message[i];
        if(cWord->str[0]==' ')
        {
           cout<<' '; continue;
        }
        if(cWord->str[0]=='1')
        {
           int k=cWord->size-1; // ����� '*' ����� ������� '1'
           if(k>2) k=2;
           cout<<key[k]; continue;
        }

        j=cWord->size-1; next=0;
        while(cWord->str[j]=='*')
        {
           next++; j--;
        }
        char* s=new char[cWord->size-next];
        for(j=0;j<cWord->size-next;j++)
           s[j]=cWord->str[j];
        // �������� ����� � ������ �9 ��� '*'
        SStr* word=new SStr(s,cWord->size-next);

        CSetWords *set=NULL;
        for(j=0;j<setWords->GetSize();j++)
           if(IsStringsEqual(setWords->GetSets()[j]->GetKWord(),word)==true)
           {
              set=setWords->GetSets()[j]; break;
           }
           
        if(next>=set->GetOrderSize())
           next=set->GetOrderSize()-1;
        w=set->GetOrder()[next];
        w->PrintWord();
        // ��������� ������� ����� � �������
        int freq=w->GetFreq()+1;
        w->SetFreq(freq);
        // ����������������� ����������� ������ ����
        set->SetNewOrder(w,next);

        delete word;
     } /* i */
} /* CMessage::DecodeMessage */
/***************************************************************************/

int main()
{    int n; // ����� ���� � �������
     CGlossary glossary; // �������
     CMessage *message;  // �������� ��������� � ������� �9
     CSets *setWords;

     CWord *tempWord;
     SStr *str;

     int curSize;
     char c,*newWord;
     vector<char> curWord;
     /**********************************************************************/
     // ������ ����, ������ � ������� words
     cin>>n;
     for(int i=0;i<n;i++)
     {
        int curFreq=0;
        curWord.clear();
        cin.get(); // ������� ������� �������� ������
        while((c=cin.get())!=' ')
           curWord.push_back(c);
        cin>>curFreq;

        curSize=curWord.size();
        newWord=new char[curSize];
        for(int j=0;j<curSize;j++)
           newWord[j]=curWord[j];
        str=new SStr(newWord,curSize);
        CWord *w=new CWord(str,curSize,curFreq);
        glossary.AddWord(w);
     } /* i */
     //glossary.PrintGlossary();

     setWords=new CSets(glossary.GetSize());
     for(int i=0;i<glossary.GetSize();i++)
     {
        tempWord=glossary.GetGlossary()[i]; // words[i]
        // ������ ���� ������� � ���� ������������������� ������� ������
        tempWord->WordToT9();
        // ������������� ���� �������
        int nset=-1;
        SStr *kword=tempWord->GetKWord();
        for(int j=0;j<setWords->GetSize();j++)
           if(IsStringsEqual(kword,setWords->GetSets()[j]->GetKWord())==true)
           {
              nset=j; break;
           }
        if(nset==-1)
        {
           CSetWords *set=new CSetWords(tempWord,glossary.GetSize());
           setWords->AddSet(set);
        }
        else
           setWords->GetSets()[nset]->AddWord(tempWord);
     } /* i */

     for(int i=0;i<setWords->GetSize();i++)
        setWords->GetSets()[i]->SetOrder();

     // ������ ��������� � ������ �9
     message=new CMessage();
     cin.get();  // ������� ������� �������� ������
     curWord.clear();
     while((c=cin.get())!='\n')
     {
        if(c=='*' && curWord.size()==0)
           continue; // ������� ��������� �������� '*'
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

     // ����������� ���������
     message->DecodeMessage(glossary,setWords);

     delete setWords;
     delete message;
     //getch();
     return 0;
} /* main */
/***************************************************************************/
