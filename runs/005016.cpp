#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>

namespace matsuk {
    
using std::vector;
using std::string;
using std::pair;

/******************************************************************************
 * class CartTree -- implementation of cartesian tree
 *****************************************************************************/

template <typename T>
class CartTreeNode {
public:
    typedef CartTreeNode<T> * pNode;

    CartTreeNode (const T & d, int k, int p) : 
        data(d), key(k), priority(p), size(1), left(NULL), right(NULL) {}

    CartTreeNode (const T & d, int k) :
        data(d), key(k), priority(rand()), size(1), left(NULL), right(NULL) {}

    virtual ~CartTreeNode () {
        delete left;
        delete right;
    }

    /*!
     * Get tree size.
     */
    static size_t getSize (const pNode tree) {
        return (tree == NULL) ? 0 : tree->size;
    }

    /*!
     * Merge two trees.
     * All keys in @L must be >= keys in @R.
     * \return New merged tree
     */
    static pNode merge (pNode L, pNode R);

    /*!
     * Split @tree to two parts on key @k.
     * All keys in @tree will be > k after splitting.
     * \return New right tree (all keys <= k)
     */
    static pNode split (int k, pNode & tree);

    /*!
     * Delete element at position @pos.
     * \return The deleted element (if one exists)
     */
    static pNode extract (size_t pos, pNode & tree);

    int getKey() const { return key; }
    void incKey() { ++key; }

    const T * getDataPtr() const { return &data; }

private:
    T data;
    int key;
    int priority;
    size_t size;

    pNode left;
    pNode right;

    /*!
     * Change metadata after tree modification
     */
    static void recalc (pNode tree) {
        if (tree != NULL) {
            tree->size = getSize(tree->left) + getSize(tree->right) + 1;
        }
    }
};

template <typename T>
typename CartTreeNode<T>::pNode 
CartTreeNode<T>::merge (pNode L, pNode R) {
    if (L == NULL) return R;
    if (R == NULL) return L;

    if (R->priority < L->priority) {
        L->right = merge(L->right, R);
        recalc(L);
        return L;
    } else {
        R->left = merge(L, R->left);
        recalc(R);
        return R;
    }
}

template <typename T>
typename CartTreeNode<T>::pNode 
CartTreeNode<T>::split (int k, pNode & tree) {
    if (tree == NULL) return NULL;

    pNode newRight;
    if (tree->key > k) {
        newRight = split(k, tree->right);
        recalc(tree);
    } else {
        newRight = tree;
        pNode newLeft = split(k, tree->left);
        tree = tree->left;
        newRight->left = newLeft;
        recalc(newRight);
    }
    return newRight;
}

template <typename T>
typename CartTreeNode<T>::pNode 
CartTreeNode<T>::extract (size_t pos, pNode & tree) {
    if (tree == NULL || pos >= tree->size) {
        return NULL;
    }
    pNode res;
    size_t leftSize = getSize(tree->left);
    if (leftSize == pos) {
        res = tree;
        tree = merge(tree->left, tree->right);
        res->left = res->right = NULL;
        res->size = 1;
    } else {
        if (leftSize > pos) {
            res = extract(pos, tree->left);
        } else {
            res = extract(pos - leftSize -1, tree->right);
        }
        recalc(tree);
    }
    return res;
}


template <typename T>
class CartTree {
public:
    CartTree () : root(NULL) {}

    virtual ~CartTree () {
        delete root;
    }

    /*!
     * Delete element at position @pos.
     * \return The deleted element (if one exists)
     */
    typename CartTreeNode<T>::pNode extract (size_t pos);

    /*!
     * Insert new element to the tree.
     */
    void add (const T & d, int k, int p);
    void add (const typename CartTreeNode<T>::pNode & elem);

    /*!
     * Insert new element (random priority).
     */
    void add (const T & d, int k) {
        add(d, k, rand());
    }

    /*!
     * Get tree size
     */
    size_t getSize () const { return CartTreeNode<T>::getSize(root); }

    /*!
     * Increment @pos element key
     * \return Element's data
     */
    const T * increment (size_t pos);

private:
    typename CartTreeNode<T>::pNode root;
};

template <typename T>
void CartTree<T>::add (const T & d, int k, int p) {
    // Здесь надо перехватить исключение от new.
    // Обработки исключения не делаю, т.к. боюсь не уложиться в 1 сек.
    typename CartTreeNode<T>::pNode elem(new CartTreeNode<T>(d, k, p));
    add(elem);
}

template <typename T>
void CartTree<T>::add (const typename CartTreeNode<T>::pNode & elem) {
    if (elem == NULL) return;
    typename CartTreeNode<T>::pNode R
        (CartTreeNode<T>::split(elem->getKey(), root));
    R = CartTreeNode<T>::merge(elem, R);
    root = CartTreeNode<T>::merge(root, R);
}

template <typename T>
typename CartTreeNode<T>::pNode CartTree<T>::extract (size_t pos) {
    if (root == NULL) return NULL;
    return CartTreeNode<T>::extract(pos, root);
}

template <typename T>
const T * CartTree<T>::increment (size_t pos) {
    typename CartTreeNode<T>::pNode elem(extract(pos));
    if (elem == NULL) return NULL;
    elem->incKey();
    add(elem);
    return elem->getDataPtr();
}


/******************************************************************************
 * class T9Trie -- trie dictionary implementation for T9
 *****************************************************************************/

class T9Trie {
public:
    typedef CartTree<string> * pTree;

    T9Trie () :
        words(1, pTree(NULL)), transitions(1, vector<int>(ALPHABET_SIZE, 0)) {}

    virtual ~T9Trie () {
        for (size_t i = 0; i < words.size(); ++i) {
            delete words[i];
        }
    }

    /*!
     * Insert new word to the trie
     */
    void AddPattern (const string & pattern, int key);

    /*!
     * Load dictionary from stdin
     */
    void LoadDictionary ();

    /*!
     * Parse user input and print apropriate words
     */
    void ParseInput ();

private:
    vector< pTree > words;
    vector< vector<int> > transitions;

    static const size_t ALPHABET_SIZE = 8;
    static const size_t MAX_WORD_LENGTH = 20;
    static const char marks[];
    static const size_t codeTable[];

    /*!
     * Get character's T9 code
     */
    int encode (char letter) const {
        if (letter < 'a' || letter > 'z') {
            return -1;
        }
        return codeTable[letter - 'a'];
    }

    /*!
     * Get trie state number by word
     */
    size_t getState (const string & pattern) const;

    /*!
     * Increment @pos element key in trie state @state
     * \return Element's data
     */
    const string * hitWord (size_t state, size_t pos);

    /*!
     * Parse codes from input and print corresponding word
     * \return Number of digits read
     */
    int parseWord ();

    /*!
     * Parse and print delimiters in form "[ \.,!]*"
     */
    void parseDelim () const;
};

const char T9Trie::marks[] = {'.', ',', '?'};
const size_t T9Trie::codeTable[] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 
                                    3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 
                                    6, 6, 6, 7, 7, 7, 7};

void T9Trie::AddPattern (const string & pattern, int key) {
    size_t curNode = 0;
    for (size_t pos = 0; pos < pattern.size(); ++pos) {
        int code = encode( pattern[pos] );
        if (code < 0) {
            return;
        }
        if (transitions[ curNode ][ code ] != 0) {
            curNode = transitions[ curNode ][ code ];
        } else {
            transitions[ curNode ][ code ] = transitions.size();
            curNode = transitions.size();
            transitions.push_back( vector<int>(ALPHABET_SIZE, 0) );
            words.push_back(NULL);
        }
    }
    if (words[curNode] == NULL ) {
    // Здесь надо перехватить исключение от new.
    // Обработки исключения не делаю, т.к. боюсь не уложиться в 1 сек.
        words[curNode] = new CartTree<string>();
    }
    words[curNode]->add(pattern, key);
}

void T9Trie::LoadDictionary () {
    char word[MAX_WORD_LENGTH +1];
    int key;
    size_t totalWords;
    if (scanf("%d", &totalWords) < 1) {
        return;
    }

    // Reverse word order
    vector< pair<string, int> > stack;
    for (size_t i = 0; i < totalWords; ++i) {
        if (scanf("%s %d\n", word, &key) > 1) {
            stack.push_back( pair<string, int>(word, key) );
        }
    }
    for (size_t i = stack.size(); i > 0; --i) {
        AddPattern(stack[i-1].first, stack[i-1].second);
    }
}

size_t T9Trie::getState (const string & pattern) const {
    size_t curNode = 0;
    for (size_t pos = 0; pos < pattern.size(); ++pos) {
        int digit = pattern[pos] - '2';
        if (digit < 0) {
            break;
        }
        curNode = transitions[ curNode ][ digit ];
    }
    return curNode;
}

const string * T9Trie::hitWord (size_t state, size_t pos) {
    if (state >= words.size()) {
        return NULL;
    }
    pTree hit = words[state];
    if (hit == NULL) {
        return NULL;
    }
    return hit->increment(pos);
}

int T9Trie::parseWord () {
    char word[MAX_WORD_LENGTH +1];
    word[0] = 0;
    int read = scanf("%[2-9]", word);
    int count = 0;
    scanf("%*[*]%n", &count);
    if (read > 0) {
        size_t state = getState(word);
        const string * data = hitWord(state, count);
        if (data != NULL) {
            printf("%s", data->c_str());
        }
    }
    return read;
}

void T9Trie::parseDelim () const {
    int readSpace = 0;
    int readPunct = 0;
    do {
        int count = 0;
        readPunct = 0;
        scanf("1%n%*[*]%n", &readPunct, &count);
        if (readPunct > 0) {
            count -= (count > 0);
            printf("%c", marks[count]);
        }
        readSpace = 0;
        scanf("%*[ ]%n", &readSpace);
        if (readSpace > 0) {
            printf("%*c", readSpace, ' ');
        }
    } while (readSpace > 0 || readPunct > 0);
}

void T9Trie::ParseInput () {
    int res = 0;
    do {
        parseDelim();
        res = parseWord();
    } while (res > 0);
    printf("\n");
}

}; //namespace matsuk

using namespace matsuk;

int main(int argc, const char *argv[])
{
    T9Trie trie;
    trie.LoadDictionary();
    trie.ParseInput();
    return 0;
}
