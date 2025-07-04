#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Node
{
  Node* children[8];
  int num;
  vector <pair <string, unsigned int> > words;
};

Node* create_node()
{
    Node* new_node = new Node;
    for (int i = 0; i < 8; i++)
        new_node->children[i] = NULL;
    new_node->num = 0;
    return new_node;
}

void add_node(Node* curr, int index)
{
    Node* new_node = create_node();
    curr->children[index] = new_node;
}

int letter_to_int (char c)
{
    if ( ( c >= 97) && ( c <= 99))
       return 2;    
    else if ( ( c >= 100) && ( c <= 102))
       return 3;
    else if ( ( c >= 103) && ( c <= 105))
       return 4;
    else if ( ( c >= 106) && ( c <= 108))
       return 5;
    else if ( ( c >= 109) && ( c <= 111))
       return 6;
    else if ( ( c >= 112) && ( c <= 115))
       return 7;
    else if ( ( c >= 116) && ( c <= 118))
       return 8;
    else if ( ( c >= 119) && ( c <= 122))
       return 9;      
      
}

void tree_input(Node* root, string word, unsigned int freq)
{
     Node* curr = root;
     pair <string, unsigned int> tmp;
     int key;
     size_t n;  
     
     for (size_t i = 0; i < word.size(); i++)
     {
         key = letter_to_int(word[i]) - 2;
         
         if (curr->children[key] == NULL)
         {
             add_node(curr, key);
         }
         curr = curr->children[key];
         curr->num = key;
     }
     
     tmp.first = word;
     tmp.second = freq;     
     curr->words.push_back(tmp);     
     n = curr->words.size();
     key = 0;   
     
     if (n > 1)
     {
         for (size_t i = n - 2; i >= 0; i--)
             if (freq > curr->words[i].second)
                 key++;
             else
                 break;
         if (key)
         {            
             curr->words.insert(curr->words.end() - key - 1, curr->words[n-1]);
             curr->words.erase(curr->words.end());
         }
     }   
     
}

string punctuation (string input)
{
    string output;
    string marks = ".,?";
    size_t pos;
    size_t i = 0;
    char curr_sign;
    while (i < input.size()) 
    {
        pos = 0;
        if ( input[i] == '1' )
        {
           if (curr_sign == '1')
              output += marks[0];
           curr_sign = input[i];
           i++;
        }
           
        else
        {
            size_t n = i;
            for (n; n < input.size(); n++)
            {
  
                if (input[n] == '*')
                   pos++;
                else break;
            }  

            pos = pos % marks.size();
            output += marks[pos];
            curr_sign = ' ';
            i = n;
        }
    }
    if (curr_sign == '1')
              output += marks[0];
    return output;  
         
}
void find_word (Node* curr, string command, unsigned int fr_count)
{
     unsigned int num, freq;
     pair <string, unsigned int> tmp;
     for (size_t i = 0; i < command.size(); i++)
     {
         num = (unsigned int)command[i] - 48;
         curr = curr->children[num - 2];        
     }
     
     fr_count = fr_count % curr->words.size();    
     cout << curr->words[fr_count].first; 
     
     if (curr->words[fr_count].second < 1000)     
          curr->words[fr_count].second++;
     
     freq = curr->words[fr_count].second;    
     num = 0;
     
     for (size_t i = fr_count - 1; i >=0; i--)
             if (freq >= curr->words[i].second)
                 num++;
             else
                 break;
     
     if (num)
     {
         tmp = curr->words[fr_count];
         curr->words.erase(curr->words.begin() + fr_count);
         curr->words.insert(curr->words.begin() + fr_count - num, tmp);
     }    
}

void word_proc (Node* root, string input)
{
     string command;
     size_t posit = 0;
     string punct_marks;
     unsigned int fr_count;
     unsigned int index;
     unsigned int space_count = 0;
     string w;
     int num;         
    
     for (size_t i = 0; i < input.size(); i++)
     {
         num = (int)input[i] - 48;
         if ((num > 1) && (num < 10))
            posit++;
         else
            break;
     }  
 
     fr_count = 0;     

     for (size_t n = 0; n < posit; n++)
            command += input[n];            
        
     for (size_t n = posit; n < input.size(); n++)
         if (input[n] != '*')
               break;
         else
         {
             fr_count++; 
             posit++;
         }
    
     for (size_t n = posit; n < input.size(); n++)
         if (input[n] == ' ')
            break;
         else
         {
            punct_marks += input[n];
            posit++;
         }      

     for (size_t n = posit; n < input.size(); n++)
         space_count++;   
         
     if (command.size() != 0)
         find_word(root, command, fr_count);    
     
     cout << punctuation(punct_marks);    
     
     for (unsigned int i = 0; i < space_count; i++)
         cout << " ";
}

int main(int argc, char *argv[])

{
    vector < pair<string, unsigned int> > vocabulary;
    pair <string, unsigned int> temp;
    
    vector <string> cmd_list;
    unsigned int word_count;
	unsigned int curr_freq;
    string curr_word, buf;
    
    Node* root = create_node();
    root->num = -2;

    cin >> word_count;
	
	for (unsigned int i = 0; i < word_count; i++)
	{
        cin >> curr_word >> curr_freq;
        temp.first = curr_word;
        temp.second = curr_freq;
        vocabulary.push_back(temp);
    }
    
    getline(cin, curr_word);
	getline(cin, curr_word);
	
	bool space = false;
	
	for (size_t i = 0; i < curr_word.size(); i++)
	{
        
        if (curr_word[i] != ' ')
        {
           if (!space)
               buf += curr_word[i];
           else
           {
               cmd_list.push_back(buf);
               buf.clear();
               buf += curr_word[i];
               space = false;
           }
        } else {
           buf += curr_word[i];
           space = true;
        }
    }
    cmd_list.push_back(buf);
    
    for (size_t i = 0; i < vocabulary.size(); i++)    
        tree_input(root, vocabulary[i].first, vocabulary[i].second);
    
    for (size_t j = 0; j < cmd_list.size(); j++)          
        word_proc(root, cmd_list[j]);

    return 0;
}
