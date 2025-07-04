#include <iostream>
#include <map>
#include <list>
#include <string>
#include <math.h>
#include <cstdlib>
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
    map<string, list<Word> > dict; // list for fast insert/remove
    string specials;
    
    
    list<Word>::iterator get_from_position(string, uint);
    
    list<Word>::iterator find_position_to_insert(list<Word>::iterator, string);
    
public:
    string number_from_word(string);
    
    Dictionary() : dict(), specials(".,?") { };
    
    void add_word(string, uint);
    string get_word(string, uint);    
    
    void sort();
    
    /*void e() 
     { 
     cout << "\n : ";
     
     for(list<Word>::iterator i=dict[768].begin(); i != dict[768].end(); ++i) cout << "(" << (*i).get_word() << ", " << (*i).rating << ") ";
     
     cout << endl;
     };*/
    
} dict;


void Dictionary::sort()
{
    for(map<string, list<Word> >::iterator it = dict.begin(); it != dict.end(); it++)
    {
        it->second.sort(compare);
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
        dict[num].push_front(w);
    }
    else dict[num].push_front(w);
}

list<Word>::iterator Dictionary::get_from_position(string num, uint pos)
{
    bool start_from_end = pos > dict[num].size()/2;
    
    list<Word>::iterator it = start_from_end ? dict[num].end() : dict[num].begin();
    
    pos = start_from_end ? (dict[num].size() - pos) : pos;
    uint i = 0;
    
    
    
    while (i < pos && it != dict[num].end())
    {
        i ++;
        start_from_end ? it-- :  it ++;
        
    }
    
    return it;
}

list<Word>::iterator Dictionary::find_position_to_insert(list<Word>::iterator it, string num)
{
    list<Word>::iterator pos = it;
    
    if(dict[num].size() == 2)
    {
        if(pos != dict[num].begin() && (--pos)->rating > it->rating) return ++pos;
    }
    
    
    while ( pos->rating <= it->rating ) 
    {
        if (pos == dict[num].begin()) return dict[num].begin();
        
        pos --;
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
        list<Word>::iterator it = get_from_position(num, pos);
        Word* w = & *it;
        
        string word = (*w).get_word();
        
        uint r = ++ (*w).rating;
        
        if(dict[num].size() > 1)
        {
            
            list<Word>::iterator i_pos = find_position_to_insert(it, num);
            //list<Word>::iterator i_pos = dict[num].begin();
            
            if(it != i_pos)
            {
                dict[num].insert(i_pos, Word(word, num, r));
                dict[num].erase(it);           
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

