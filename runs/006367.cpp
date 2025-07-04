#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * Word Base
 *
 * Store and get words by frequency
 */
class WordBase
{
    public:
        WordBase()
        {
            // root is not sorted
            base.sorted = false;
        }
        
        void addWord(const string word, int freq)
        {
            TrieNode *t = &base;
            
            // set pointer 't' to the node, that will store 'word'
            for (string::const_iterator iter = word.begin(); iter != word.end(); ++iter) {
                short key = getKeyByChar(*iter);
                
                if (t->nodes.find(key) == t->nodes.end()) {
                    // insert new element
                    TrieNode newNode;
                    newNode.sorted = false;
                    t->nodes[key] = newNode;
                }
                
                t = &(t->nodes[key]);
            }
            
            Word w = {word, freq};
            // initially store words in unsorted order
            t->words.push_back(w);
        }
        
        /**
         * Transform encoded text to word(s)
         * Words can be separated by characters such as '.,?'
         * This function dont support spaces between words!
         */
        string getTextByCode(const string textCode)
        {
            // result of textCode transforming
            string result;
            
            // break text on words by separators key
            int prev = 0;
            for (int next = 0; (next = textCode.find('0' + sepKey, prev)) != -1; prev = next + 1) {
                result += getWordByCode(textCode.substr(prev, next - prev));

                // calculate separator
                int priority = 0;
                for (int i = next + 1; textCode[i] == nextWordChr; ++i) {
                    ++priority;
                }
                
                int sepLastIndex = sizeof(separators) / sizeof(char) - 1;
                int index = priority > sepLastIndex ? sepLastIndex : priority;
                
                result += separators[index];
                next   += priority;
            }
            
            result += getWordByCode(textCode.substr(prev));
            
            return result;
        }
        
        /**
         * Returns word by its code
         * This function dont support spaces and separators
         */
        string getWordByCode(const string wordCode)
        {
            if (wordCode.empty()) {
                return "";
            }
            
            TrieNode *t = &base;
                        
            // search for node that stores words correspond to wordCode
            int priority = 0;
            for (string::const_iterator iter = wordCode.begin(); iter != wordCode.end(); ++iter) {
                short key = *iter;
                
                if (nextWordChr == key) {
                    for (string::const_iterator iterSep = iter; iterSep != wordCode.end(); ++iterSep) {
                        ++priority;
                    }
                    
                    // break outer iteration
                    break;
                }
                
                key = *iter - '0';
                
                if (t->nodes.find(key) == t->nodes.end()) {
                    // it seems word is not in container
                    return "";
                }
                
                t = &(t->nodes[key]);
            }
            
            if (t->words.empty()) {
                // something is wrong, container is empty
                return "";
            }
            
            // sort on demand
            if (!t->sorted) {
                sort(t->words.begin(), t->words.end(), WordBase::compareWords);
                // dont sort in future
                t->sorted = true;
            }
            
            int index = (t->words.size() - 1) - priority;
            
            if (index < 0) {
                index = 0;
            }
            
            Word &result = t->words[index];
            
            ++result.freq;
            string resWord = result.word;
            
            if (priority) {
                moveWordByFreq(t->words, index);
            }
            
            return resWord;
        }
    
    private:

        struct Word {
            string word;
            int freq;
        };
        
        struct TrieNode {
            map<short, TrieNode> nodes;
            vector<Word> words;
            bool sorted;
        };
        
        short getKeyByChar(char c) const
        {
            if (c >= 'a' && c <= 'z') {
                return chrMap[c - 'a'];
            }
            
            return sepKey;
        }
        
        /**
         * Move word with index wordIndex to the end of subvector with
         * the same frequency
         */
        void moveWordByFreq(vector<Word> &seq, int wordIndex)
        {
            for (int i = wordIndex, c = seq.size() - 1; i < c; ++i) {
                if (seq[i].freq < seq[i + 1].freq) {
                    break;
                }
                
                // swapping words
                Word swap  = seq[i + 1];
                seq[i + 1] = seq[i];
                seq[i]     = swap;
            }
        }
        
        /**
         * Returns true if frequency of w1 less then w2's.
         * In case when frequences are equal, w1 and w2 compare lexicography
         */
        static bool compareWords(const Word &w1, const Word &w2)
        {
            return w1.freq == w2.freq ? !lexicographical_compare(w1.word.begin(), w1.word.end(), w2.word.begin(), w2.word.end()) : w1.freq < w2.freq;
        }
        
        /**
         * Prefix tree
         * It is the container of words
         */
        TrieNode base;
        
        /**
         * Mapping from character to mobile keyboard digit
         */
        static const short chrMap[29];
        
        /**
         * Separators are binded with sepKey
         */
        static const char separators[3];
        
        static const char nextWordChr;
        static const short sepKey;
};

const short WordBase::chrMap[29] = {
    2, // a
    2, // b
    2, // c
    3, // d
    3, // e
    3, // f
    4, // g
    4, // h
    4, // i
    5, // j
    5, // k
    5, // l
    6, // m 
    6, // n
    6, // o
    7, // p
    7, // q
    7, // r
    7, // s
    8, // t
    8, // u
    8, // v
    9, // w
    9, // x
    9, // y
    9  // z
};
const char WordBase::separators[3] = {
    '.',
    ',',
    '?'
};
const char WordBase::nextWordChr = '*';
const short WordBase::sepKey = 1;

bool readWordBase(WordBase &base)
{
    int wordsNum = 0;
    
    cin >> wordsNum;
    
    if (wordsNum > 0) {
        for (int i = 0; i < wordsNum; ++i) {
            string word;
            int freq;
            
            cin >> word >> freq;
            base.addWord(word, freq);
        }
        
        cin.get(); // read last EOL
        
        return true;
    }
    
    return false;
}

int main()
{
    WordBase base;
    
    if (readWordBase(base)) {
        string code;
        getline(cin, code);
        
        string currCode;
        for (string::const_iterator iter = code.begin(); iter != code.end(); ++iter) {
            if (' ' == *iter) {
                cout << base.getTextByCode(currCode) << ' ';
                currCode.erase();
            } else {
                currCode += *iter;
            }
        }
        
        cout << base.getTextByCode(currCode) << endl;
    } else {
        return 1;
    }

    return 0;
}
