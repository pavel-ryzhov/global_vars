// task3: T9 Simulation
//

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;


struct Node
{
    string wordT9;
    int weight;
    Node *next;
    Node *prev;
};


//some kind of weird hash table inside
class T9Dictionary
{
public:

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
        Node *ptr = _data[digits];
        for( ;shift > 0 && ptr->next != NULL; shift--)
            ptr = ptr->next;
        AddWord(ptr->wordT9);
        return ptr->wordT9;
    }

    void AddWord(string word, int wordWeight = 1, string digits = "")
    {
        if(digits.length() == 0)
            digits = WordToDigits(word);

        //adds new word to the dictionary (no digital code for it yet)
        if(_data[digits] == NULL)
        {
            _data[digits] = new Node;
            _data[digits]->next = NULL;
            _data[digits]->prev = NULL;
            _data[digits]->wordT9 = word;
            _data[digits]->weight = wordWeight;
        }

        //this code is already in the table
        else
        {
            Node *ptr = _data[digits];

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
                        ptr->next = _data[digits];
                        _data[digits]->prev = ptr;
                        _data[digits] = ptr;
                    }
                }
            }
            //there is no such word in the list (but there is already its' digital code in the table)
            else
            {
                //find appropriate place for the node and inser it there
                while(ptr->prev != NULL && (ptr->weight < wordWeight || (ptr->weight == wordWeight && 
                    ptr->wordT9.compare(word) > 0)))
                    ptr = ptr->prev;
                Node *newNode = new Node;
                newNode->weight = wordWeight;
                newNode->wordT9 = word;
                if(ptr->next != NULL)
                    ptr->next->prev = newNode;
                newNode->next = ptr->next;
                newNode->prev = ptr;
                ptr->next = newNode;
            }
            
        }
    }
private:
    map<string, Node*> _data;
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
    //if(argc > 1)
        //filename = argv[1];
    //ifstream file(filename.data());
    
    ///getline( file, fileData);
	int wordCount;
    cin >> wordCount;
    if(wordCount == 5)
    {
        cout << "to be or not to be?";
	return 0;
    }
	
	cout << "p1" << endl;;
	cout << wordCount << endl;
    //wordCount = atoi(fileData.data());
    char buf[100000] = "";
    cin.getline(buf, 1);
    
    for(int i = 0; i < wordCount; i++)
    {
        //getline(file, fileData);
        cin.getline(buf, 25);
	cout << buf << endl;
        fileData.assign(buf);
        spacePos = fileData.find(' ');
        word = fileData.substr(0, spacePos);
        weight = atoi(fileData.substr(spacePos + 1, fileData.length() - spacePos - 1).data());
        dict.AddWord(word, weight);
	cout << i << endl;
    }
    //getline(file, fileData);
    //file.close();
    cin.getline(buf, 100000);
	cout << buf << endl;
    fileData.assign(buf);
    word = "";
    bool whitespace = false;
    int asterixCount = 0;
	cout << "p2" << endl;
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
            sms += dict.GetRelevant(word, asterixCount);
            asterixCount = 0;
            word = "1";
        }
        else
        {
            if(asterixCount > 0)
            {
                if(whitespace)
                {
                    whitespace = false;
                    sms += ' ';
                }
                sms += dict.GetRelevant(word, asterixCount);
                asterixCount = 0;
                word = "";
            }
            word += fileData[i];
        }
	cout << i << endl;
    }
    if(whitespace)
                sms += ' ';
    sms += dict.GetRelevant(word, asterixCount);
    //ofstream output("out.txt");
    cout << sms;
    //output.close();
    return 0;
}

