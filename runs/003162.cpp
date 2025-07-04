// task3: T9 Simulation
//

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

struct Node
{
    string wordT9;
    int weight;
    Node *next;
    Node *prev;
};

struct TreeNode
{
    TreeNode()
    {
        lst = NULL;
        for(int i = 0; i < 9; i++)
            a[i] = NULL;
    }
    TreeNode *a[9];
    Node *lst;
};

//it contains some tree
class T9Dictionary
{
public:

    T9Dictionary()
    {
        for(int i = 0; i < 9; i++)
            _data[i] = new TreeNode;
    }

    string GetRelevant(string digits, int shift)
    {
        if (digits.compare("1") == 0)
        {
            switch(shift)
            {
            case 0:
                return ".";
            case 1:
                return ",";
            case 2:
                return "?";
            default:
                return "";
            }
        }
        TreeNode *ptr;
        ptr = _data[(int)digits[0] - 49];
        for(int i = 1; i < digits.length(); i++)
        {
            ptr = ptr->a[(int)digits[i] - 49];
        }
        Node *ptr2 = ptr->lst;
        if(ptr2 == NULL)
            return "";
        for( ;shift > 0 && ptr2->next != NULL; shift--)
            ptr2 = ptr2->next;
        AddWord(ptr2->wordT9, 1, digits);
        return ptr2->wordT9;
    }

    void AddWord(string word, int wordWeight = 1, string digits = "")
    {
        if(digits.length() == 0)
            digits = WordToDigits(word);

        TreeNode *tr;
        Node *ptr;
        int k;
        tr = _data[1];
        k = (int)digits[0] - 49;
        tr = _data[(int)digits[0] - 49];
        for(int i = 1; i < digits.length(); i++)
        {
            k = (int)digits[i] - 49;
            if(tr->a[k] == NULL)
            {
                tr->a[k] = new TreeNode;
            }
            tr = tr->a[k];
        }
        //adds new word to the dictionary (no digital code for it yet)
        if(tr->lst == NULL)
        {
            tr->lst = new Node;
            tr->lst->next = NULL;
            tr->lst->prev = NULL;
            tr->lst->wordT9 = word;
            tr->lst->weight = wordWeight;
        }

        //this code is already in the table
        else
        {
            ptr = tr->lst;

            //is the word already in the dictionary?
            while(ptr->next != NULL && ptr->wordT9.compare(word) != 0)
            {
                ptr = ptr->next;
            }

            //it is!
            if(ptr->wordT9.compare(word) == 0)
            {
                //it's more relevant now
                ptr->weight += wordWeight;
                
                //if(the list should be re-sorted)...
                if(ptr->prev != NULL && ptr->prev->weight <= ptr->weight)
                {
                    Node *ptr2 = ptr;   
                    
                    //let's find a better place for the word
                    while(ptr2 != NULL && ptr2->weight <= ptr->weight)
                    {
                        ptr2 = ptr2->prev;
                    }

                    //cut the list node from the previous place and insert it into new one 
                    ptr->prev->next = ptr->next;
                    if(ptr->next != NULL)
                        ptr->next->prev = ptr->prev;

                    //insert it into the middle of the list if it's not the most relevant and cool word in the list
                    if(ptr2 != NULL)
                    {
                        ptr2->next->prev = ptr;
                        ptr->next = ptr2->next;
                        ptr->prev = ptr2;
                        ptr2->next = ptr;
                    }
                    //otherwise let's make it the head of the list
                    else
                    {
                        ptr->prev = NULL;
                        ptr->next = tr->lst;
                        tr->lst->prev = ptr;
                        tr->lst = ptr;
                    }
                }
            }
            //there is no such word in the list (but there is already its' digital code in the table)
            else
            {
                //find appropriate place for the node and inser it there
                while(ptr != NULL && (ptr->weight < wordWeight || (ptr->weight == wordWeight && 
                    ptr->wordT9.compare(word) > 0)))
                    ptr = ptr->prev;
                Node *newNode = new Node;
                newNode->weight = wordWeight;
                newNode->wordT9 = word;
                if(ptr != NULL)
                {
                    if(ptr->next != NULL)
                        ptr->next->prev = newNode;
                    newNode->next = ptr->next;
                    newNode->prev = ptr;
                    ptr->next = newNode;
                }
                else
                {
                    newNode->prev = NULL;
                    newNode->next = tr->lst;
                    tr->lst->prev = newNode;
                    tr->lst = newNode;
                }
            }
        }
    }
private:
    TreeNode* _data[9];
    string WordToDigits(string word)
    {
        string t9 = "";
        for(int i = 0; i < word.length(); i++)
        {
            switch(word[i]) 
            {
            case '.': case ',': case '?':
                t9 += '1';
                break;
            case 'a': case 'b': case 'c':
                t9 += '2';
                break;
            case 'd': case 'e': case 'f':
                t9 += '3';
                break;
            case 'g': case 'h': case 'i':
                t9 += '4';
                break;
            case 'j': case 'k': case 'l':
                t9 += '5';
                break;
            case 'm': case 'n': case 'o':
                t9 += '6';
                break;
            case 'p': case 'q': case 'r': case 's':
                t9 += '7';
                break;
            case 't': case 'u': case 'v':
                t9 += '8';
                break;
            case 'w': case 'x': case 'y': case 'z':
                t9 += '9';
                break;
            }
        }
        return t9;
    }
};


int main(int argc, char* argv[])
{
    int startime = time(0);
    string fileData;
    int spacePos;
    string word;
    int weight;
    T9Dictionary dict;
    string sms = "";   
    //if(argc > 1)
        //filename = argv[1];
    //ifstream file("1.txt");
    //ofstream file2("2.txt");
    //getline( file, fileData);
	int wordCount;
    cin >> wordCount;
    //wordCount = atoi(fileData.data());
    char buf[100050] = "";
    cin.getline(buf, 255);
    int position;
    //file2 << startime - time(0) << endl;
    for(int i = 0; i < wordCount; i++)
    {
        //getline(file, fileData);
        cin.getline(buf, 255);
        fileData.assign(buf);
        //file2 << i << ") " << startime - time(0) << endl;
        position = fileData.find_first_not_of(' ');
        spacePos = fileData.find(' ', position);
        word = fileData.substr(position, spacePos);
        weight = atoi(fileData.substr(spacePos + 1, fileData.length() - spacePos - 1).data());
        position = word.find(' ');
        while (position != string::npos) 
        {
            word.replace(position, 1, "");
            position = word.find(' ');
        } 
        //file2 << startime - time(0) << endl;
        dict.AddWord(word, weight);
        //file2 << startime - time(0) << endl;
    }
    //getline(file, fileData);
    //file.close();
    cin.getline(buf, 100050);
    fileData.assign(buf);
    word = "";
    bool whitespace = false;
    int asterixCount = 0;
    //file2 << startime - time(0) << endl;
    //int d;
    //char ch;
    
    //ofstream output("out.txt");
//    try
 //   {
    for(int i = 0; i < fileData.length(); i++)
    {
        //output << i << endl;
        //ch = fileData[i];
        //cout << sms << endl; cin >> d;

        if(fileData[i] == '*')
        {
            asterixCount++;
            //file2 << i << ")* " << startime - time(0) << endl; 
        }
        else if(fileData[i] == ' ')
        {
            if(whitespace)
            {
                sms += ' ';
            }
            if(word.length() > 0)
                sms += dict.GetRelevant(word, asterixCount);
            asterixCount = 0;
            word = "";
            whitespace = true;
            //file2 << i << ")' ' " << startime - time(0) << endl;
        }
        else if(fileData[i] == '1')
        {
            if(whitespace)
            {
                sms += ' ';
                whitespace = false;
            }
            if(word.length() > 0)
                sms += dict.GetRelevant(word, asterixCount);
            asterixCount = 0;
            word = "1";
            //file2 << i << ")w " << startime - time(0) << endl;
        }
        else
        {
            if(asterixCount > 0 || word.compare("1") == 0)
            {
                if(whitespace)
                {
                    whitespace = false;
                    sms += ' ';
                }
                if(word.length() > 0)
                    sms += dict.GetRelevant(word, asterixCount);
                asterixCount = 0;
                word = "";
            }
            word += fileData[i];
            //file2 << i << ")w2 " << startime - time(0) << endl;
        }
    }
//    }
//    catch(int a)
//    {
//        output.close();
//    }
    if(whitespace)
                sms += ' ';
    if(word.length() > 0)
        sms += dict.GetRelevant(word, asterixCount);
    //file2 << "last " << startime - time(0) << endl;
    //ofstream output("out.txt");
    cout << sms;
    //output.close();
    //int k;
    //cin >> k;
    return 0;
}

