#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <vector>

using namespace std;

typedef unsigned short int small_int;

const int bufsize = 100000;

/// Mapping of characters to digital keys
const char char_keys[26] = {'2', '2', '2',
                            '3', '3', '3',
                            '4', '4', '4',
                            '5', '5', '5',
                            '6', '6', '6',
                            '7', '7', '7', '7',
                            '8', '8', '8',
                            '9', '9', '9', '9'};

/// Return full key (a string of digits from 2 to 9) for any
/// given word
const string get_full_key(const string& s)
{
    string res;
    /// Preallocate full string to save cycles
    res.resize(s.length());
    
    for (small_int i = 0; i != s.length(); i++)
        res[i] = char_keys[s[i] - 'a'];

    return res;
}

/// Word with frequency
class Word
{
public:
    const string str;

    /// Word frequency must be increased by 1 after each use only if
    /// this is true
    const bool bumpable;
    
    Word()
        :str(""), bumpable(false)
    {}

    Word(const string &s, const bool &b = true)
        :str(s), bumpable(b)
    {}

    void print()
    {
        cout << str;
    }

    void send(ostream &out)
    {
        out << str;
    }
};

ostream& operator <<(ostream &out, Word &w)
{
    w.send(out);
    return out;
}

typedef list<Word> word_list;

/// @param bump If true, word is inserted in the beginning of list.
///             Otherwise, it's appended after all other items.
///
/// @return List beginning iterator.
word_list::iterator insert_word(word_list *l, const Word &w, bool bump = false)
{
    if (bump)
        l->push_front(w);
    else
        l->push_back(w);
    return l->begin();
}

class Trie
{
    typedef vector<word_list*> freq_vector;
    
private:
    /// Vector of words lists stored in root leaf of trie. Each n-th
    /// element contains list of words with frequency n.
    freq_vector words;

    /// Children tries
    vector<Trie*> children;
    
    /// Add word object under given full key
    void add_word_proc(const char *full_key, const Word &w, const small_int &freq)
    {
        vector<Trie*>::size_type key = (full_key[0] - '1');
     
        if (*full_key == '\0')
        {
            if (words[freq - 1] == NULL)
                words[freq - 1] = new word_list();
        
            insert_word(words[freq - 1], w);
        }
        else
        {
            if (children[key] == NULL)
                children[key] = new Trie();
            children[key]->add_word_proc(full_key + 1, w, freq);
        }
    }

    /// Get freq_vector with words stored in trie under given full
    /// key. We assume that all used words are present in the trie, so
    /// this always succeeds.
    freq_vector& get_leaf(const char *full_key)
    {
        vector<Trie*>::size_type key = (full_key[0] - '1');
        if (*full_key == '\0')
            return words;
        else
        {
            return children[key]->get_leaf(full_key + 1);
        }
    }
public:
    Trie(void)
    {
        /// Preallocate vector for 9 (from 1 to 9) children which may
        /// be added later
        children.resize(9, NULL);
        
        /// 1000 (1 to 1000) frequencies
        words.resize(1000, NULL);
    }

    ~Trie(void)
    {
        /// @todo Rewrite via for_each
        // for (vector<Trie*>::iterator i = children.begin(); i != children.end(); i++)
        //     if (*i != NULL)
        //         delete *i;
        
        // for (freq_vector::iterator i = words.begin(); i != words.end(); i++)
        //     if (*i != NULL)
        //         delete *i;
    }

    /// Public wrapper for add_word_proc
    void add_word(const string &contents, const small_int &freq)
    {
        string fk = get_full_key(contents);
        add_word_proc(fk.c_str(), Word(contents), freq);
    }

    /// Add new punctuation mark under 1
    void add_punctuation(const string &punct)
    {
        add_word_proc("1", Word(punct, false), 1000);
    }

    /// Get n-th word stored in trie under given full key.
    Word& query(string &full_key, int n = 0)
    {
        freq_vector& leaf = get_leaf(full_key.c_str());
        freq_vector::reverse_iterator fv_iter = leaf.rbegin();
        word_list::iterator w_iter, w_enditer;

        do
        {
            /// Skip to next non-empty frequency if needed.
            ///
            /// @todo This takes 999 operations in worst case.
            while (*fv_iter == NULL)
                fv_iter++;

            /// Begin iterating over words with this frequency
            w_iter = (*fv_iter)->begin();
            w_enditer = (*fv_iter)->end();

            /// Try to skip n items (or less)
            while ((w_iter != w_enditer) && n)
            {
                w_iter++;
                n--;
            }
                
            /// End of frequency reached?
            if (w_iter == w_enditer)
                fv_iter++;
            else
                break;
        }
        while (1);

        /// Bump frequency and reinsert word if needed
        if (w_iter->bumpable)
        {
            Word w = Word(w_iter->str);
            /// Remove old word entry
            (*fv_iter)->erase(w_iter);
            
            if (fv_iter == leaf.rbegin())
            {
                /// Max frequency occupied, allocate more
                leaf.push_back(new word_list());
                fv_iter = leaf.rbegin();
            }
            else
            {
                /// Allocate target frequency if needed
                fv_iter--;
                if (*fv_iter == NULL)
                    *fv_iter = new word_list();
            }
            w_iter = insert_word(*fv_iter, w, true);
        }

        return *w_iter;
    }
};

class T9Reader
{
private:
    string full_key;
    bool prev_punct, word_put;
    int skips;
    Trie *trie;

    /// If word selected so far has not been printed yet, do it
    void put_pending(void)
    {
        if (!word_put)
            put_current_word();
    }

public:
    T9Reader(Trie *t)
    {
        trie = t;
        full_key = "";
        word_put = true;
        prev_punct = false;
        skips = 0;
    }

    /// Print word selected so far
    void put_current_word(void)
    {
        trie->query(full_key, skips).print();
        full_key.clear();
        skips = 0;
        word_put = true;
        prev_punct = false;
    }
    
    void read(const string &input)
    {
        for (string::const_iterator i = input.begin(); i != input.end(); i++)
        {
            if (*i == ' ')
            {
                put_pending();
                cout << ' ';
            }
            else
            {
                /// Next character in word key
                if ((*i >= '2') && (*i <= '9'))
                {
                    if (prev_punct)
                        put_pending();
                    full_key += *i;
                    word_put = false;
                }
                else if (*i == '*')
                    skips++;
                /// Punctuation (put word)
                else if (*i == '1')
                {
                    put_pending();
                    full_key = "1";
                    word_put = false;
                    prev_punct = true;
                }
            }
        }
        put_pending();
    }
};

int main(int argc, char* argv[])
{
    int dict_size;
    string dict_word;
    small_int freq;
    Trie tr;
    T9Reader t9 = T9Reader(&tr);
    char buf[bufsize];

    cin >> dict_size;

    tr.add_punctuation(".");
    tr.add_punctuation(",");
    tr.add_punctuation("?");

    /// Populate trie
    for (int i = 0; i < dict_size; i++)
    {
        cin >> dict_word >> freq;
        tr.add_word(dict_word, freq);
    }

    cin.ignore(1);
    cin.getline(buf, bufsize);
    t9.read(buf);
    
    return 0;
}
