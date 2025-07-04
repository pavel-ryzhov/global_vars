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
    Node()
    {
        next = NULL;
        prev = NULL;
        weight = 0;
        wordT9 = "";
    }
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
        left = NULL;
        right = NULL;
        num = "";
    }
    string num;
    TreeNode *left;
    TreeNode *right;
    Node *lst;
};


//it contains some tree
class T9Dictionary
{
public:

    T9Dictionary()
    {
        for(int i = 0; i < 9; i++)
        {
            _data[i] = new TreeNode;
        }
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
        _data[0]->num = "1";
    }

  string GetRelevant(string digits, int shift)
    {
       TreeNode *ptr;
        ptr = _data[digits[0] - 49];
        int res = ptr->num.compare(digits);
        while(res != 0)
        {
            if(res < 0)
                ptr = ptr->left;
            else
                ptr = ptr->right;
            res = ptr->num.compare(digits);
        }
        Node *ptr2 = ptr->lst;
        if(ptr2 == NULL)
            return "";
        for( ;shift > 0 && ptr2->next != NULL; shift--)
            ptr2 = ptr2->next;
        if(ptr2->wordT9[0] != '1')
            UpdateWordRelevance(ptr2, ptr);
        return ptr2->wordT9;
    }

    /*TreeNode* GetPosTree(string digits)
    { 
        TreeNode *ptr;
        ptr = _data[digits[0] - 49];
        int res = ptr->num.compare(digits);
        while(res != 0)
        {
            if(res < 0)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
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
    }*/

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
        k = digits[0] - 49;
        tr = _data[k];
        if(tr->num.length() <= 0)
        {
            _data[k] = new TreeNode;
            _data[k]->num = digits;
            _data[k]->lst = new Node;
            _data[k]->lst->weight = wordWeight;
            _data[k]->lst->wordT9 = word;
            return;
        }
        int res = tr->num.compare(digits);
        while(res != 0)
        {
            if(res < 0)
            {
                if(tr->left != NULL)
                    tr = tr->left;
                else
                {
                    tr->left = new TreeNode;
                    tr->left->num = digits;
                    tr->left->lst = new Node;
                    tr->left->lst->weight = wordWeight;
                    tr->left->lst->wordT9 = word;
                    return;
                }
            }
            else
            {
                if(tr->right != NULL)
                    tr = tr->right;
                else
                {
                    tr->right = new TreeNode;
                    tr->right->num = digits;
                    tr->right->lst = new Node;
                    tr->right->lst->weight = wordWeight;
                    tr->right->lst->wordT9 = word;
                    return;
                }
            }
            res = tr->num.compare(digits);
        }

        //this code is already in the table
        ptr = tr->lst;

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
    cin.getline(buf, 100050);
    fileData.assign(buf);
    word = "";
    bool whitespace = false;
    int asterixCount = 0;
    for(int i = 0; i < fileData.length(); i++)
    {
        if(fileData[i] == '*')
        {
            asterixCount++;
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
        }
    }

    if(whitespace)
                sms += ' ';
    if(word.length() > 0)
        sms += dict.GetRelevant(word, asterixCount);
    cout << sms;
    return 0;
}

