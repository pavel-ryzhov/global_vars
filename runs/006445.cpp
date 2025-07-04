#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int NKEYS=29;         // �������� �������� ��������

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

// ����� ����� �� �������
class CWord
{
  private:
     vector<char> word;
     vector<char> kword; // ������������������ ������ ��� ������ �����
     int freq;  // ������� ������������� ����� � �������
  public:
     CWord() { freq=0; }
     CWord(vector<char> word, int freq)
     {
        this->word=word;
        this->freq=freq;
     }
     vector<char> GetWord() { return word; }
     void SetWord(vector<char> word) { this->word=word; }

     vector<char> GetKWord() { return kword; }
     void SetKWord(vector<char> kword) { this->kword=kword; }

     int GetFreq() { return freq; }
     void SetFreq(int freq) { this->freq=freq; }

     void WordToT9();

     void PrintWord()
     {
        for(size_t i=0;i<word.size();i++)
           cout<<word[i];
     }
}; // CWord
// --------------------------------------------------------------------------

// ����� ������ ����, ��������������� �������� ���������� ������
class CSetWords
{
  private:
     vector<CWord*> words;
     vector<char> kword; // ������� ��������� ���� � ������
     vector<CWord*> order;  // ������� ������ ����
  public:
  	int i; // ����� ������ � ������� setWords
     CSetWords(CWord *word,int i)
     {
        words.push_back(word);
        kword=word->GetKWord();
        this->i=i;
     }
     void AddWord(CWord *word);
     vector<CWord*> GetWords() { return words; }
     vector<CWord*> GetOrder() { return order; }
     void SetNewOrder(CWord *word,size_t j);
     vector<char> GetKWord() { return kword; }
     void SetOrder();
     void Print()
     {
        cout<<"kword:";
        for(size_t i=0;i<kword.size();i++)
           cout<<kword[i];
        cout<<endl;
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

//     // ����� ������ ������������ ����, ���������� ����� ������� ������
//     li=order.begin();
//     while(li!=order.end())
//     {
//        cout<<(*li)->GetFreq()<<" ";
//        (*li)->PrintWord();
//        cout<<"; ";
//        li++;
//     }
//     cout<<endl;
} /* CSetWords::SetOrder */
/***************************************************************************/

void CSetWords::SetNewOrder(CWord *word,size_t j)
{    vector<CWord*> temp=order;
     vector<CWord*>::iterator li;
     // j - ����� ���������� �����
     // i - ����� ���������������� ����� � �����
     // k - ������ �������� ����� � ������� ������������ order
     size_t i=0,k=j;
	/**********************************************************************/
     if(j)
     {
        while(k!=0 && word->GetFreq()>=order[k-1]->GetFreq())
           k--;
     }
     li=order.begin();
     while(li!=order.end())
     {
        if(i<k || i>j)
           order[i]=temp[i];
        else if(i==k)
           order[i]=temp[j];
        else
           order[i]=temp[i-1];
        i++;
        li++;
     }
} /* CSetWords::SetNewOrder */
/***************************************************************************/

void CSetWords::AddWord(CWord *word)
{
     words.push_back(word);
} /* CSetWords::AddWord */
/***************************************************************************/

// ����� ���������� ���������
class CMessage
{
  private:
     vector< vector<char> > message;
     int nextCount; // ����� �������� '*' ����� �����
  public:
     void AddWord(vector<char> word)
     {
        if(word.size())
           message.push_back(word);
     }
     vector< vector<char> > GetMessage(void) { return message; };
     void DecodeMessage(vector<CWord*> &words,vector<CSetWords*> &setWords);
}; // CMessage
// --------------------------------------------------------------------------

// ������ ���� ������� � ���� ������������������� ������� ������
void CWord::WordToT9(void)
{
     for(size_t i=0;i<word.size();i++)
        for(int k=0;k<NKEYS;k++)
           if(word[i]==key[k])
           {
              kword.push_back(kn[k]+48);
              break;
           }
} /* CWord::WordToT9 */
/***************************************************************************/

void CMessage::DecodeMessage(vector<CWord*> &words,vector<CSetWords*> &setWords)
{    vector<char> cWord; // �������� ����� � ������ �9
	vector<char> word;  // �������� ����� � ������ �9 ��� '*'
     vector<char>::iterator pos;
     CWord *w;
     size_t j;
     int next=0; // ����� �������� '*' � ����� �����
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
           int k=cWord.size()-1; // ����� '*' ����� ������� '1'
           if(k>2) k=2;
           cout<<key[k]; continue;
        }
        word=cWord;

        // ��������� ���������� ������ ��� �������� '*'
        pos=remove(word.begin(),word.end(),(char)'*');
        word.erase(pos,word.end());
        next=cWord.size()-word.size();

        CSetWords *set=NULL;
        for(j=0;j<setWords.size();j++)
           if(setWords[j]->GetKWord()==word)
           {
              set=setWords[j]; break;
           }

	if(set!=NULL)
	{
           if(next>=set->GetOrder().size())
              next=set->GetOrder().size()-1;
           w=set->GetOrder()[next];
           w->PrintWord();
           // ��������� ������� ����� � �������
           int freq=w->GetFreq()+1;
           w->SetFreq(freq);
           // ����������������� ����������� ������ ����
           set->SetNewOrder(w,next);
        }
        //getch();
     } /* i */
} /* CMessage::DecodeMessage */
/***************************************************************************/

int main()
{    int i;
	int n; // ����� ���� � �������
     unsigned int mesSize; // ����� ���� � ��������� (���. ����. � ��. ����.)

     vector<CWord*> words; // �������
     CMessage *message;
     vector<CSetWords*> setWords;

     char c,word[20];
     vector<char> curWord;
     /**********************************************************************/
     // ������ ����, ������ � ������� words
     cin>>n;
     for(i=0;i<n;i++)
     {
        int curFreq=0;
        curWord.clear();
        //fi.get(); // ������� ������� �������� ������
        cin.get();
        while((c=cin.get())!=' ')
           curWord.push_back(c);
        cin>>curFreq;

        CWord *w=new CWord(curWord,curFreq);
        words.push_back(w);
     } /* i */

//     // ����� ���� � ������ �� ������������ � �������
//     for(i=0;i<n;i++)
//     {
//        words[i]->PrintWord();
//        cout<<" "<<words[i]->GetFreq()<<endl;
//     }

     // ������ ���� ������� � ���� ������������������� ������� ������
     // ������������� ���� �������
     for(size_t i=0;i<words.size();i++)
     {
        words[i]->WordToT9();
        int nset=-1;
        vector<char> kword=words[i]->GetKWord();
        for(size_t j=0;j<setWords.size();j++)
           if(kword==setWords[j]->GetKWord())
           {
              nset=j; break;
           }
        if(nset==-1)
        {
           CSetWords *set=new CSetWords(words[i],i);
           setWords.push_back(set);
        }
        else
           setWords[nset]->AddWord(words[i]);
     } /* i */

//     cout<<endl<<"LIST:"<<endl;
     for(size_t i=0;i<setWords.size();i++)
        setWords[i]->SetOrder();

//     cout<<endl<<"SETWORDS:"<<endl;
//     for(size_t i=0;i<setWords.size();i++)
//        setWords[i]->Print();
//     cout<<endl;

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

//     // ����� ����������� ���������� ���������
//     mesSize=message->GetMessage().size();
//     for(size_t i=0;i<mesSize;i++)
//     {
//        for(size_t j=0;j<message->GetMessage()[i].size();j++)
//           cout<<message->GetMessage()[i][j];
//        cout<<";"<<endl;
//     }
//     cout<<endl;

     // ����������� ���������
     message->DecodeMessage(words,setWords);

     delete message;
     return 0;
} /* main */
/***************************************************************************/
