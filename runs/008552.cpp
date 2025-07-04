#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

char char2num(char ch)
{
	switch (ch)
    {
		case 'a':case 'b': case 'c':
			return '2';
        case 'd':case 'e': case 'f':
            return '3';
        case 'g':case 'h': case 'i':
			return '4';
        case 'j':case 'k': case 'l':
            return '5';
        case 'm':case 'n': case 'o':
            return '6';
        case 'p': case'q': case 'r': case 's':
            return '7';
        case 't':case 'u': case 'v':
            return '8';
        case 'w': case'x': case 'y': case 'z':
            return '9';
        default: return '1';
    };
}
class rowDic
{
public:
typedef vector <rowDic> arrayRow;
	char *word;
	int freq;
	rowDic(int k, char *s)
	{
		word=s;
		freq=k;	
	}
};
string getWordByNum(string &str,map<string,rowDic::arrayRow> &vocabulary)
{
	if (str.size()==0)
    {
		return "";
    }
	int indexOne = str.find_first_of('1');
	int firstStar=str.find_first_of('*');
	int lastStar=str.find_last_of('*');
    int wordNum=0;
    string result="";
    string str2="";
    if (indexOne<0)
    {
		if (firstStar>0)
		{
			str2=str.substr(0,firstStar);
			wordNum=lastStar-firstStar+1;
		}
		else
		{
			str2=str;
			wordNum=0;
		}
    }
    else
    {
		if (firstStar>0)
		{
			switch (lastStar-firstStar)
			{
				case 0:return ",";
				case 1:return "?";
			}
		}
		else
		{
			return ".";
		}
	}
	result = vocabulary.find(str2)->second.at(wordNum).word;
	vocabulary.find(str2)->second.at(wordNum).freq++;
    int tmp=wordNum-1;
    while (tmp>=0)
    {
		if(vocabulary.find(str2)->second.at(tmp).freq<=vocabulary.find(str2)->second.at(wordNum).freq)
		{
			tmp--;
		}
		else
			break;
    }
    tmp++;
    if (tmp<wordNum)
    {
		vocabulary.find(str2)->second.insert(vocabulary.find(str2)->second.begin()+tmp, vocabulary.find(str2)->second.at(wordNum));
		vocabulary.find(str2)->second.erase(vocabulary.find(str2)->second.begin()+wordNum + 1);
    }
    return result;
}
int main(int argc, char *argv[])
{
	map< string,vector<rowDic> > myVoc;
	int dicSize;
	cin >> dicSize;
	string message="";
	int freq;
	for (int i=0;i<dicSize;i++)
	{
		char *word=new char[21];
		cin >> word;
		cin >> freq;
		int j=0;
		string result="";
		while (word[j] != '\0' )
		{
			result=result+char2num(word[j]);
			j++;
		}
		if (myVoc.find(result)==myVoc.end())
		{
			myVoc.insert(make_pair(result,vector<rowDic>()));
		}
		myVoc.find(result)->second.push_back(rowDic(freq,word));
		
		int num = myVoc.find(result)->second.size()-1;
		int tmp = num - 1; 
		while (tmp>=0)
		{
			if(myVoc.find(result)->second.at(tmp).freq<myVoc.find(result)->second.at(num).freq)
			{
				tmp--;
			}
			else
				break;
		}
		tmp++;
		if (tmp<num)
		{
			myVoc.find(result)->second.insert(myVoc.find(result)->second.begin()+tmp, myVoc.find(result)->second.at(num));
			myVoc.find(result)->second.erase(myVoc.find(result)->second.begin()+num + 1);
		}
	}
	cin.ignore();
	getline(cin,message);
	bool readWord = false;
    bool readStars = false;
    bool readZp = false;
    int startIndex=-1;
	string line="";
	for (int i=0;i<message.size();i++)
    {
		switch (message.at(i))
        {
             default:
             if (!readWord)
                  {
                       startIndex=i;
                       readWord=true;
                  }
                  if (readStars)
                      readStars=false;
                  if (readZp)
                  {
					  cout<<getWordByNum(line,myVoc);
                      readZp=false;
                  }
                  break;
             case' ':
                if (readWord)
                {
					if (!readStars)
					{
						line=message.substr(startIndex,i-startIndex);
					}
					cout<<getWordByNum(line,myVoc);
                }
                if (readZp)
                {
					if (!readStars)
					{
						line="1";
					}
					cout<<getWordByNum(line,myVoc);
                }
                printf(" ");
                readWord = false;
                readStars = false;
                readZp = false;
                line="";
                break;
             case '1':
                if (readWord)
                {
			 		line=message.substr(startIndex,i-startIndex);
					cout<<getWordByNum(line,myVoc);
					readWord=false;
					readStars=false;
                }
                if (readZp)
                {
					cout<<getWordByNum(line,myVoc);
					readStars=false;
                }
                line="1";
                readZp=true;
                break;
             case '*':
                if (readWord)
                {
					if (!readStars)
					{
						line=message.substr(startIndex,i+1-startIndex);
					}
					else
					{
						line=line+'*';
					}
                }
                if (readZp)
                {
					line=line+'*';
                }
                readStars=true;
                break;
        }		
	}
    if (readWord)
	{ 
		line=message.substr(startIndex);
	}
	cout<<getWordByNum(line,myVoc);
	return 0;
}