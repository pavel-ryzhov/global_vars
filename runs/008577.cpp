#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <string.h>

using std::vector;
using std::string;
using std::map;
using std::cin;

unsigned char alphabet[256];

inline void initAlphabet()
{
    memset(alphabet, 1, 256);

    alphabet['a'] = '2';
    alphabet['b'] = '2';
    alphabet['c'] = '2';

    alphabet['d'] = '3';
    alphabet['e'] = '3';
    alphabet['f'] = '3';

    alphabet['g'] = '4';
    alphabet['h'] = '4';
    alphabet['i'] = '4';

    alphabet['j'] = '5';
    alphabet['k'] = '5';
    alphabet['l'] = '5';

    alphabet['m'] = '6';
    alphabet['n'] = '6';
    alphabet['o'] = '6';

    alphabet['p'] = '7';
    alphabet['q'] = '7';
    alphabet['r'] = '7';
    alphabet['s'] = '7';

    alphabet['t'] = '8';
    alphabet['u'] = '8';
    alphabet['v'] = '8';

    alphabet['w'] = '9';
    alphabet['x'] = '9';
    alphabet['y'] = '9';
    alphabet['z'] = '9';
}

inline char char2num(unsigned char ch)
{
    return alphabet[ch];
}

struct rowDic
{
    char *word;
    int freq;

    rowDic(int k, char *s)
    {
        word = s;
        freq = k;	
    }
};

inline string getWordByNum(string &str, map< string, vector<rowDic> > &vocabulary)
{
    if (str.size() == 0)
    {
        return "";
    }

    int indexOne = str.find_first_of('1');
    int firstStar = str.find_first_of('*');
    int lastStar = str.find_last_of('*');
    int wordNum(0);
    string result("");
    string str2("");

    if (indexOne < 0)
    {
        if (firstStar > 0)
        {
            str2 = str.substr(0, firstStar);
            wordNum = lastStar - firstStar + 1;
        }
        else
        {
            str2 = str;
            wordNum = 0;
        }
    }
    else
    {
        if (firstStar > 0)
        {
            switch (lastStar - firstStar)
            {
            case 0:
                return ",";
            case 1:
                return "?";
            }
        }
        else
        {
            return ".";
        }
    }
    vector<rowDic>::iterator it = vocabulary.find(str2)->second.begin();

    result = (it+wordNum)->word;
    (it+wordNum)->freq++;

    int tmp = wordNum - 1;

    while (tmp >= 0)
    {
        if((it+tmp)->freq <= (it+wordNum)->freq)
        {
            --tmp;
        }
        else
            break;
    }

    ++tmp;

    if (tmp < wordNum)
    {
		map< string, vector<rowDic> >::iterator it1= vocabulary.find(str2); 
		it1->second.insert(it1->second.begin() + tmp, it1->second[wordNum]);
		//it1 = vocabulary.find(str2);
		it1->second.erase(it1->second.begin() + wordNum + 1);
    }
    return result;
}

int main(int argc, char *argv[])
{
    map< string, vector<rowDic> > myVoc;
    int dicSize;
    string message("");
    int freq;

    initAlphabet();

    scanf("%d", &dicSize);

    for (int i = 0; i < dicSize; ++i)
    {
        char *word = new char[21];
        int j(0);
        string result;

        scanf("%s", word);
        scanf("%d", &freq);

        while (word[j] != '\0' )
        {
            result = result + char2num(word[j]);
            ++j;
        }

        if (myVoc.find(result) == myVoc.end())
        {
            myVoc.insert(make_pair(result, vector<rowDic>()));
        }

        myVoc.find(result)->second.push_back(rowDic(freq,word));
		vector<rowDic>::iterator it1 = myVoc.find(result)->second.begin();
        int num = myVoc.find(result)->second.size() - 1;
        int tmp = num - 1;

        while (tmp >= 0)
        {
            if((it1+tmp)->freq<(it1+num)->freq)
            {
                --tmp;
            }
            else
                break;
        }
        ++tmp;
        if (tmp < num)
        {
			map<string, vector<rowDic> >::iterator it = myVoc.find(result);
            it->second.insert(it->second.begin() + tmp, it->second[num]);
            //it = myVoc.find(result);
			it->second.erase(it->second.begin() + num + 1);
        }
    }

    cin.ignore();
    getline(cin,message);
    bool readWord = false;
    bool readStars = false;
    bool readZp = false;
    int startIndex(-1);
    string line("");

    for (int i = 0; i < message.size(); ++i)
    {
        switch (message[i])
        {
        default:
            if (!readWord)
            {
                startIndex = i;
                readWord = true;
            }

            if (readStars)
                readStars = false;

            if (readZp)
            {
                printf("%s", getWordByNum(line,myVoc).c_str());
                readZp = false;
            }
            break;

        case ' ':
            if (readWord)
            {
                if (!readStars)
                {
                    line = message.substr(startIndex, i - startIndex);
                }
                printf("%s", getWordByNum(line, myVoc).c_str());
            }

            if (readZp)
            {
                if (!readStars)
                {
                    line = "1";
                }
                printf("%s", getWordByNum(line, myVoc).c_str());
            }

            printf(" ");
            readWord = false;
            readStars = false;
            readZp = false;
            line = "";
            break;

        case '1':
            if (readWord)
            {
                line = message.substr(startIndex, i - startIndex);
                printf("%s", getWordByNum(line,myVoc).c_str());
                readWord = false;
                readStars = false;
            }

            if (readZp)
            {
                printf("%s", getWordByNum(line,myVoc).c_str());
                readStars = false;
            }

            line = "1";
            readZp = true;
            break;

        case '*':
            if (readWord)
            {
                if (!readStars)
                {
                    line = message.substr(startIndex, i + 1 - startIndex);
                }
                else
                {
                    line += '*';
                }
            }

            if (readZp)
            {
                line += '*';
            }

            readStars=true;
            break;
        }		
    }
    if (readWord)
    { 
        line = message.substr(startIndex);
    }

    printf("%s", getWordByNum(line, myVoc).c_str());

    return 0;
}
