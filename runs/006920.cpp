#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <math.h>
#include <cstdlib>
#include <algorithm>
#include <string.h>

#define MAX_BUF 100000

using namespace std;


typedef unsigned int uint;

class Word
{
private:
    string word;
    string number;
    
    
public:
    uint rating;
    
    Word(string w, string num, uint r): word(w), number(num), rating(r) {}    
    
    string get_word() { return word;   }
    
};

// Comparing function for sorting
bool compare(Word a, Word b)
{
    if (a.rating > b.rating) return true;
    else 
    {
        if(a.rating == b.rating && (a.get_word().compare(b.get_word()) < 0)) return true;
    }
    return false;
}



class Dictionary
{
private:
    map<string, vector<Word> > dict; // list for fast insert/remove
    string specials;
    
    
    vector<Word>::iterator get_from_position(string, uint);
    
    vector<Word>::iterator find_position_to_insert(vector<Word>::iterator, string);
    
public:
    string number_from_word(string);
    
    Dictionary() : dict(), specials(".,?") { };
    
    void add_word(string, uint);
    string get_word(string, uint);    
    
    void sort();
    
    void e() 
     { 
     cout << "\n : ";
     
     for(vector<Word>::iterator i=dict["228"].begin(); i != dict["228"].end(); ++i) cout << "(" << (*i).get_word() << ", " << (*i).rating << ") ";
     
     cout << endl;
     };
    
} dict;


void Dictionary::sort()
{
    for(map<string, vector<Word> >::iterator it = dict.begin(); it != dict.end(); it++)
    {
        std::sort(it->second.begin(), it->second.end(), compare);
//        it->second.sort(compare);
    }
}

string Dictionary::number_from_word(string word)
{
    string number = "";
    //uint n = pow(10, word.length() - 1);
    
    for(uint i = 0; i < word.length(); i++)
    {
        switch(word[i])
        {
            case 'a': case 'b': case 'c': 
                number += "2"; break;
                
            case 'd': case 'e': case 'f': 
                number += "3"; break;
                
            case 'g': case 'h': case 'i': 
                number += "4"; break;
                
            case 'j': case 'k': case 'l': 
                number += "5"; break;
                
            case 'm': case 'n': case 'o': 
                number += "6"; break;
                
            case 'p': case 'q': case 'r': case 's': 
                number += "7"; break;
                
            case 't': case 'u': case 'v': 
                number += "8"; break;
                
            case 'w': case 'x': case 'y': case 'z':
                number += "9"; break;
        }
    }
    
    return number;
}

void Dictionary::add_word(string word, uint rating)
{
    string num = number_from_word(word);
    
    Word w = Word(word, num, rating);
    if (dict.count(num) > 0)
    {
        dict[num].push_back(w);
    }
    else dict[num].push_back(w);
}

vector<Word>::iterator Dictionary::get_from_position(string num, uint pos)
{
    return dict[num].begin() + pos;
}

vector<Word>::iterator Dictionary::find_position_to_insert(vector<Word>::iterator it, string num)
{
    vector<Word>::iterator pos = it;
    
    if(dict[num].size() == 2)
    {
        if(pos != dict[num].begin() && (--pos)->rating > it->rating) return ++pos;
    }
    
    
    while ( pos->rating <= it->rating ) 
    {
        if (pos == dict[num].begin()) return dict[num].begin();
        
        -- pos;
        if( pos -> rating > it -> rating) return ++pos;
    }
    
    
    return pos;
}

string Dictionary::get_word(string num, uint pos)
{
    if(num == "1") 
    {
        cout<< specials[pos];
        return ""; 
    }
    else
    {
        vector<Word>::iterator it = get_from_position(num, pos);
        
        string word = it->get_word();
        
        uint r = ++ it->rating;
        
        if(dict[num].size() > 1)
        {
            
            vector<Word>::iterator i_pos = find_position_to_insert(it, num);
            
            if(it != i_pos)
            {
                dict[num].erase(it);
                dict[num].insert(i_pos, Word(word, num, r));
            }
        }
        
        return word;
    }
}




int main (int argc, const char * argv[])
{
    uint N;
    cin >> N;
    
    string word;
    uint rating;
    for(uint i = 0; i < N; i++)
    {
        cin >> word >> rating;
        
        dict.add_word(word, rating);
    }
    
    dict.sort();
    
    char str[MAX_BUF];
    cin.get(); // last \n in from last word
    cin.getline(str, MAX_BUF);
    
    //if (N > 13) cout<<"str: " << str << endl;
    
    string stack("");
    uint pos = 0;
    
    for (int i = 0; i < strlen(str); i++)
    {
        if (isdigit(str[i]))
        {
            if(str[i] != '1') 
            {
                if (stack != "1") stack += str[i];
                else
                {
                    cout << dict.get_word(stack, pos);
                    stack = "";
                    stack += str[i];
                    pos = 0;
                }
            }
            else
            {
                if(!stack.empty()) cout << dict.get_word(stack, pos);
                
                stack = "1";
                pos = 0;
            }
        }
        else if (str[i] == '*') pos++;
        else if (str[i] == ' ')
        {
            if(!stack.empty()) cout << dict.get_word(stack, pos);
            
            cout<<" ";
            
            stack = "";
            pos = 0;
        }
    }
    
    if(!stack.empty())
    {
        cout << dict.get_word(stack, pos) << endl;
    }
    
    
    return 0;
}

