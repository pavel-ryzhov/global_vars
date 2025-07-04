// task3: T9 Simulation
//

#include <iostream>
#include <map>
#include <string>
#include <cstdlib>

#define _SECURE_SCL 0

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
        for(int i = 0; i < 64; i++)
            a[i] = NULL;
    }
    

    TreeNode *a[64];
    Node *lst;
};


//it contains some tree
class T9Dictionary
{
public:

    T9Dictionary()
    {
        for(int i = 0; i < 65; i++)
            _data[i] = new TreeNode;
        Node* punct = new Node;
        punct->prev = NULL;
        punct->weight = 0;
        punct->wordT9 = ".";
        punct->next = new Node;
        punct->next->prev = punct;
        punct->next->weight = 0;
        punct->next->wordT9 = ",";
        punct->next->next = new Node;
        punct->next->next->prev = punct->next;
        punct->next->next->weight = 0;
        punct->next->next->wordT9 = "?";
        punct->next->next->next = NULL;
        _data[0] = new TreeNode;
        _data[0]->lst = punct;
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

    TreeNode* GetPosTree(char digits[], TreeNode* curPos)
    { 
        TreeNode *ptr;
        if(curPos == NULL)
            ptr = _data[(digits[0] - 49) * 8 + (digits[1] - 49)];
        else
            ptr = curPos->a[(digits[0] - 49) * 8 + digits[1] - 50];
        //AddWord(ptr2->wordT9, 1, digits);
        return ptr;
    }

    Node* GetPosNode(Node* curPos, TreeNode* treePos = NULL)
    {
        Node *ptr;
        if(curPos == NULL)
            ptr = treePos->lst;
        else
            ptr = curPos->next;
        return ptr;
    }

    void UpdateWordRelevance(Node* ptr, TreeNode* tr)
    {
        if(ptr->wordT9[0] == '.' || ptr->wordT9[0] == ',' || ptr->wordT9[0] == '?')
            return;
        //it's more relevant now
        ptr->weight += 1;
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

    void AddWord(string word, int wordWeight = 1, string digits = "")
    {
        if(digits.length() == 0)
            digits = WordToDigits(word);

        TreeNode *tr;
        Node *ptr;
        int k;
        tr = _data[1];
        k = digits.length();
        if((k % 2) != 0)
        {
            digits = digits.substr(0, k - 1) + "1" + digits[k - 1];
        }
        k = (digits[0] - 49) * 8 + (digits[1] - 49);
        tr = _data[k];
        for(int i = 2; i < digits.length(); i+=2)
        {
            k = (digits[i] - 49) * 8 + (digits[i+1] - 50);
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
            while(ptr->next != NULL)
            {
                ptr = ptr->next;
            }


            //there is no such word in the list (but there is already its' digital code in the table)
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
private:
    TreeNode* _data[65];
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
    string fileData;
    int spacePos;
    string word;
    int weight;
    T9Dictionary dict;
    string sms = "";   
	int wordCount;
    cin >> wordCount;
    char buf[100050] = "";
    cin.getline(buf, 255);
    int position;
    for(int i = 0; i < wordCount; i++)
    {
        cin.getline(buf, 255);
        fileData.assign(buf);
        position = fileData.find_first_not_of(' ');
        spacePos = fileData.find(' ', position);
        word = fileData.substr(position, spacePos - position);
        weight = atoi(fileData.substr(spacePos + 1, fileData.length() - spacePos - 1).data());
        position = word.find(' ');
        while (position != string::npos) 
        {
            word.replace(position, 1, "");
            position = word.find(' ');
        } 
        dict.AddWord(word, weight);
    }
    string word2; 
    word = "";
    bool whitespace = false;
    int asterixCount = 0;
    char ch;
    char ch2[2];
    TreeNode* n1 = NULL;
    Node* n2 = NULL;
    Node* npunct = NULL;
    bool ispunct = false;
    int wlen = 0;
    while(cin.get(ch))
    {
        if(ch == '\n')
            break;
        if(ch == '*')
        {
            if(wlen == 1)
            {
                ch2[1] = ch2[0];
                if(n1 == NULL)
                    ch2[0] = '0';
                else
                    ch2[0] = '1';
                n1 = dict.GetPosTree(ch2, n1);
                n2 = n1->lst;
                wlen = 0;
            }
            n2 = dict.GetPosNode(n2, n1);
        }
        else if(ch == ' ')
        {
            if(whitespace)
            {
                sms += ' ';
            }
            if(word2.length() > 0)
            {
                /*if(n2 == NULL)
                    n2 = n1->lst;*/
                if(wlen == 1)
                {
                    ch2[1] = ch2[0];
                    if(n1 == NULL)
                        ch2[0] = '0';
                    else
                        ch2[0] = '1';
                    n1 = dict.GetPosTree(ch2, n1);
                    n2 = n1->lst;
                    wlen = 0;
                }
                sms += n2->wordT9;
                dict.UpdateWordRelevance(n2, n1);
                n2 = NULL;
                n1 = NULL;
            }
            asterixCount = 0;
            word2 = "";
            whitespace = true;
        }
        else if(ch == '1')
        {
            if(whitespace)
            {
                sms += ' ';
                whitespace = false;
            }
            if(word2.length() > 0)
            {
                /*if(n2 == NULL)
                    n2 = n1->lst;*/
                if(wlen == 1)
                {
                    ch2[1] = ch2[0];
                    if(n1 == NULL)
                        ch2[0] = '0';
                    else
                        ch2[0] = '1';
                    n1 = dict.GetPosTree(ch2, n1);
                    n2 = n1->lst;
                    wlen = 0;
                }
                sms += n2->wordT9;
                dict.UpdateWordRelevance(n2, n1);
                n2 = NULL;
                n1 = NULL;    
                
            }
            ch2[0] = '1';
            ch2[1] = '1';
            n1 = dict.GetPosTree(ch2, n1);
            n2 = n1->lst;
            word2 = "1";
        }
        else
        {
            if(n2 != NULL && word2.compare("1") == 0)
            {
                if(whitespace)
                {
                    whitespace = false;
                    sms += ' ';
                }
                if(word2.length() > 0)
                {
                    /*if(n2 == NULL)
                        n2 = n1->lst;*/
                    if(wlen == 1)
                    {
                        ch2[1] = ch2[0];
                        if(n1 == NULL)
                            ch2[0] = '0';
                        else
                            ch2[0] = '1';
                        n1 = dict.GetPosTree(ch2, n1);
                        n2 = n1->lst;
                        wlen = 0;
                    }
                    sms += n2->wordT9;
                    dict.UpdateWordRelevance(n2, n1);
                    n2 = NULL;
                    n1 = NULL;
                }
                word2 = "";
            }
            ch2[wlen] = ch;
            wlen++;
            if(wlen == 2)
            {
                wlen = 0;
                n1 = dict.GetPosTree(ch2, n1);
                n2 = n1->lst;
            }
            word2 += ch;
        }
    }
    if(whitespace)
        sms += ' ';
    if(word2.length() > 0)
        sms += n2->wordT9;
    cout << sms;
    return 0;
}

