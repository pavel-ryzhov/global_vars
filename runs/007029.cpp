#include <iostream>
#include <map>
#include <list>
#include <string>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF 100000

using namespace std;

typedef unsigned int uint;


class Word
{
private:
    string word;
    
    
    
public:
    uint rating;
    
    Word(string w, uint r): word(w), rating(r) {}    
    
    string get_word() { return word;   }
    
};

// Comparing function for sorting
bool compare(Word* a, Word* b)
{
    if (a->rating > b->rating) return true;
    else 
    {
        if ((a->rating) == (b->rating) && (a->get_word().compare(b->get_word()) < 0)) 
            return true;
    }
    return false;
}




// <dictTree>

class TreeNode
{
public:
    TreeNode(): words() { for(int i = 2; i < 10; i++) { allocated[i] = false; } };
    
    TreeNode* child[10];
    bool allocated[10];
    list<Word*> words;
};


class DictTree
{
private:
    TreeNode *root, *current_node;
    bool walking;
    list<Word*> to_free;
    
    string number_from_word(string);
    
    list<Word*>::iterator get_from_position();    
    list<Word*>::iterator find_position_to_insert(list<Word*>::iterator);
    void visit(TreeNode*);
public:
    DictTree();
    ~DictTree();
    string get_word();
    void   add_word(string, uint);
    void   walk(char);
    void   restart();
    void   sort(); 
    
    
    uint pos;
    
} tree;

DictTree::DictTree()
{
    walking = false;
    pos = 0;
    
    root = new TreeNode();
    root -> words.push_back(new Word(".", 0));
    root -> words.push_back(new Word(",", 0));
    root -> words.push_back(new Word("?", 0));
    
    current_node = root;
}

DictTree::~DictTree()
{
    for(list<Word*>::iterator it = to_free.begin(); it != to_free.end(); ++ it)
    {
        delete *it;
    }
}


string DictTree::number_from_word(string word)
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

void DictTree::add_word(string word, uint rating)
{
    string num = number_from_word(word);
        
    char buf[2];
    buf[1] = 0;
    
    TreeNode* node = root;
    
    for (int i = 0; i < num.length(); ++i) 
    {
        buf[0] = num[i];
        char n = atoi(buf);
        
        if(!node->allocated[n]) 
        {
            node->child[n] = new TreeNode();
            node->allocated[n] = true;
        }
        
        node = node -> child[n];
    }
    
    Word* w = new Word(word, rating);
    node -> words.push_front(w);
    to_free.push_front(w);
}


string DictTree::get_word()
{    
    if(!walking) return "";
    list<Word*>::iterator it = get_from_position();
    
    Word* w = *it;
    w->rating += 1;
    
    if(current_node -> words.size() > 1 && current_node != root)
    {
        
        list<Word*>::iterator i_pos = find_position_to_insert(it);
        
        if(it != i_pos)
        {
            current_node -> words.insert(i_pos, w);
            current_node -> words.erase(it);
        }
    }
    restart();
    
    return w->get_word();
}

list<Word*>::iterator DictTree::get_from_position()
{
    list<Word*>::iterator it = current_node -> words.begin();
    uint i = 0;
    
    while (i < pos && it != current_node -> words.end())
    {
        ++ i;
        ++ it;
    }
    
    return it;
}


list<Word*>::iterator DictTree::find_position_to_insert(list<Word*>::iterator it)
{
    list<Word*>::iterator pos = it;
    
    if(current_node -> words.size() == 2)
    {
        if(pos != current_node -> words.begin() && (*(--pos))->rating > (*it)->rating) return ++pos;
    }
    
    
    while ( (*pos)->rating <= (*it)->rating ) 
    {
        if (pos == current_node -> words.begin()) return pos;
        
        --pos;
        if ( (*pos) -> rating > (*it) -> rating) return ++pos;
    }
    
    
    return pos;
}



void DictTree::walk(char sym)
{
    char n = atoi(&sym);
    
    if(n == 1) 
    {
        cout << get_word();
    }
    else
    {
        if(walking && current_node == root)
        {
            cout << get_word();
        }
        if(current_node->allocated[n]) current_node = current_node -> child[n];
        else cout << get_word();
    }
    walking = true;
}


void DictTree::restart()
{
    pos = 0;
    walking = false;
    current_node = root;
}

void DictTree::sort()
{
    for(int i = 2; i < 10; i++) if(root->allocated[i]) visit(root->child[i]);
}

void DictTree::visit(TreeNode* n)
{
    n -> words.sort(compare);
    
    for(int i = 2; i < 10; i++) if(n->allocated[i]) visit(n->child[i]);
}


// </dictTree>


int main (int argc, const char * argv[])
{
    uint N;
    cin >> N;
    
    
    string word;
    uint rating;
    for(uint i = 0; i < N; ++i)
    {
        cin >> word >> rating;
        
        tree.add_word(word, rating);
    }
    
    tree.sort();
    
    char str[MAX_BUF];
    
    
    cin.get(); // last \n in from last word
    cin.getline(str, MAX_BUF);
    
    
    cout<<"";
    
    for (int i = 0; i < strlen(str); ++i)
    {
        if (isdigit(str[i]))
        {
            tree.walk(str[i]);
        }
        else if (str[i] == '*') ++ tree.pos;
        else if (str[i] == ' ')
        {
            cout << tree.get_word();
            
            cout<<" ";
        }
    }
    cout << tree.get_word();
    
    return 0;
}
/*
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
bool compare(Word* a, Word* b)
{
    if ((*a).rating > (*b).rating) return true;
    else 
    {
        if((*a).rating == (*b).rating && ((*a).get_word().compare((*b).get_word()) < 0)) return true;
    }
    return false;
}



class Dictionary
{
private:
    map<string, list<Word*> > dict; // list for fast insert/remove
    string specials;
    
    
    list<Word*>::iterator get_from_position(string, uint);
    
    list<Word*>::iterator find_position_to_insert(list<Word*>::iterator, string);
    
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
     };
    
} dict;


void Dictionary::sort()
{
    for(map<string, list<Word*> >::iterator it = dict.begin(); it != dict.end(); it++)
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
    
    dict[num].push_front(new Word(word, num, rating));
}

list<Word*>::iterator Dictionary::get_from_position(string num, uint pos)
{
    list<Word*>::iterator it = dict[num].begin();
    uint i = 0;
    
    while (i < pos && it != dict[num].end())
    {
        ++ i;
        ++ it;
    }
    
    return it;
}

list<Word*>::iterator Dictionary::find_position_to_insert(list<Word*>::iterator it, string num)
{
    list<Word*>::iterator pos = it;
    
    if(dict[num].size() == 2)
    {
        if(pos != dict[num].begin() && (--(*pos))->rating > (*it)->rating) return ++ pos;
    }
    
    
    while ( (*pos)->rating <= (*it)->rating ) 
    {
        if (pos == dict[num].begin()) return dict[num].begin();
        
        -- pos;
        if( (*pos)->rating > (*it)->rating) return ++ pos;
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
        list<Word*>::iterator it = get_from_position(num, pos);
        Word* w = *it;
                
        uint r = ++ (*w).rating;
        
        if(dict[num].size() > 1)
        {
            
            list<Word*>::iterator i_pos = find_position_to_insert(it, num);
            
            if(it != i_pos)
            {
                dict[num].insert(i_pos, w);
                dict[num].erase(it);           
            }
        }
        
        return (*w).get_word();
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
    
    for (int i = 0; i < strlen(str); ++i)
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

*/