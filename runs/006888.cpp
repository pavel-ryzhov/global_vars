#include<iostream>
#include<string>
#include<vector>
#include<string>
#include<list>
#include<map>

using std::vector;
using std::list;
using std::map;

using std::cout;
using std::endl;
using std::cin;
using std::string;


typedef int Frequency;
typedef string Word;

const int kNumOfDigits = 8;

const int kKeys[26] = {'2', '2', '2', '3', '3', '3',
                       '4', '4', '4', '5', '5', '5', '6', '6', '6',
                       '7', '7', '7', '7', '8', '8', '8', '9', '9', '9', '9'};

int SymbolToKey(char symbol) {
    int index = symbol - 'a';
    return kKeys[index] - '2';
}

int KeyDigit(const Word& word, int position) {
    return SymbolToKey(word[position]);
}

// class MultiPriorityQueue
// Implements priority queue sorted according to keys.
// Single key can be associated with a list of values.
// In the latter case new value is inserted either to front (assigning highest priority among values with
// similar keys) or to back (assigning lowest priority) of the list.
template<typename Key, typename T>
class MultiPriorityQueue {

    template<typename U>
    struct Less {
        inline bool operator() (U first, U second) const {
            return first > second;
        }
    };

    map<Key, list<T>, Less<Key> > queue_;
    int size_;

    typedef typename map<Key, list<T>, Less<Key> >::iterator QueueIterator;
    typedef typename list<T>::iterator ListIterator;

    public:

    typedef QueueIterator iterator;
    typedef ListIterator list_iterator;

    MultiPriorityQueue() : size_(0) {}

    void Insert(const T& value, const Key & key_value, bool on_top = false) {
        if (on_top) {
            queue_[key_value].push_front(value);
        }
        else {
            queue_[key_value].push_back(value);
        }
        ++size_;
    }

    void Erase(iterator iter_queue, list_iterator iter_list) {

        iter_queue->second.erase(iter_list);

        if (iter_queue->second.empty()) {
            queue_.erase(iter_queue);
        }
        --size_;
    }

    const T& GetMax() {
        return Begin()->second.begin();
    }

    iterator Begin() {
        return queue_.begin();
    }

    iterator End() {
        return queue_.end();
    }

    int size() const {
        return size_;
    }
};


// class T9TDictionary
// Implements a Trie based on keys (words normalized to corresponding T9 numbers)
// Supports inserting word with a given frequency ( = priority) and
// query of a word with specified rank by key.
class T9Dictionary {

    struct Node;
    typedef Node* Link;

    Link words_queue_head_;
    vector<Word> punctuation_;


    public:

    T9Dictionary() {
        words_queue_head_ = new Node();
    }

    ~T9Dictionary() {
        delete words_queue_head_;
    }

    void InsertWord(const Word& new_word, const Frequency& priority) {
        int next = KeyDigit(new_word, 0);
        if (next < 0 || next >= kNumOfDigits) {
            cout << "InsertWord: WordIndex error while converting " << new_word << " 0 " << endl;
        }
        InsertWord(words_queue_head_->children_[next], new_word, priority, 1);
    }

    //TODO: return const Word& here
    Word GetWord(const string& key, int rank) {

        if (key.empty()) {
            cout << "GetWord error: empty key queried" << endl;
            return "";
        }

        int next = KeyToIndex(key[0]);
        if (next < 0 || next >= kNumOfDigits) {
            cout << "KeyIndex error while converting " << key << " 0 " << endl;
        }
        return GetWord(words_queue_head_->children_[next], key, rank, 1);
    }

    void InsertPunctuation(const Word& symbol) {
        punctuation_.push_back(symbol);
    }

    Word GetPunctuation(int rank) {
        if (rank >= punctuation_.size()) {
            return punctuation_.back();
        }

        return punctuation_[rank];
    }


    private:

    struct Node {

        MultiPriorityQueue<Frequency, Word> words_queue_;
        vector<Node*> children_;

        Node() {
            children_.resize(kNumOfDigits, 0);
        }

        ~Node() {
            for (int i = 0; i < children_.size(); ++i) {
                if (children_[i] != 0) {
                    delete children_[i];
                }
            }
        }
    };

    void InsertWord(Link& h, const Word& new_word, const Frequency& priority, int position) {

        if (h == 0) {
            h = new Node();
        }

        if (position == new_word.size()) {
            h->words_queue_.Insert(new_word, priority);

        } else {

            int next = KeyDigit(new_word, position);
            if (next < 0 || next >= kNumOfDigits) {
                cout << "InsertWord: Index error while converting " << new_word << " " << position << endl;
            }
            InsertWord(h->children_[next], new_word, priority, position + 1);
        }
    }

    Word GetWord(Link& h, const string& key, int rank, int position) {

        if (h == 0) {
            cout << "GetWord error: queried word missing " << endl;
            return "";
        }

        if (position == key.size()) {

            if (rank >= h->words_queue_.size()) {
                cout << "GetWord error: max rank exceeded" << endl;
                return "";
            }

            MultiPriorityQueue<Frequency, Word>::iterator iter_queue;
            MultiPriorityQueue<Frequency, Word>::list_iterator iter_list;

            FindWordInQueue(h, key, rank, iter_queue, iter_list);
            Word queried_word =  *iter_list;
            Frequency old_frequency = iter_queue->first;
            h->words_queue_.Erase(iter_queue, iter_list);
            h->words_queue_.Insert(queried_word, old_frequency + 1, true);

            return queried_word;

        } else {
            int next = KeyToIndex(key[position]);

            if (next < 0 || next >= kNumOfDigits) {
                cout << "GetWord: KeyIndex error while converting " << key << "  " << position << endl;
            }

            return GetWord(h->children_[next], key, rank, position + 1);
        }
    }

    void FindWordInQueue(const Link& h, const string& key, int rank,
            MultiPriorityQueue<Frequency, Word>::iterator& iter_queue,
            MultiPriorityQueue<Frequency, Word>::list_iterator& iter_list) {

        iter_queue = h->words_queue_.Begin();
        iter_list = iter_queue->second.begin();

        int current_rank = 0;

        while (1) {

            while (iter_queue->second.empty()) {
                ++iter_queue;
            }

            for (iter_list = iter_queue->second.begin(); iter_list != iter_queue->second.end() &&
                current_rank < rank; ++current_rank, ++iter_list) {
            }

            if (iter_list == iter_queue->second.end()) {
                ++iter_queue;
            }   else {
                break;
            }
        }
    }

    static inline int KeyToIndex(char key) {
        return key - '2';
    }
};


// class T9Processor
// Given a dictionary of words (of type T9Dictionary)
// parses and processes a message typed in T9 form.
class T9Processor {

    typedef enum {WordState, PunctuationState, SpaceState} ParserState;
    typedef enum {Digit, Asterisk, Punctuation, Space, Unrecognized} Symbol;

    T9Dictionary* dictionary_;
    string current_key_;
    int current_rank_;

    public:

    T9Processor(T9Dictionary* dictionary) : dictionary_(dictionary),
        current_key_(""), current_rank_(0) {}

    void ParseMessage(const string& message, string* output) {

        ParserState state = SpaceState;

        for (string::const_iterator symbol = message.begin(); symbol != message.end();
                ++symbol) {

            switch (CharToSymbol(*symbol)) {

                case Space:

                    if (state == WordState) {
                        PutWord(output);
                    }
                    if (state == PunctuationState) {
                        PutPunctuation(output);
                    }
//                    *output += " ";
                    cout << ' ';
                    state = SpaceState;
                    break;

                case Digit:

                    if (state == PunctuationState) {
                        PutPunctuation(output);
                    }

                    current_key_ += *symbol;
                    state = WordState;
                    break;

                case Asterisk:
                    ++current_rank_;
                    break;

                case Punctuation:

                    if (state == WordState) {
                        PutWord(output);
                    }
                    if (state == PunctuationState) {
                        PutPunctuation(output);
                    }

                    current_key_ = "1";
                    state = PunctuationState;
                    break;

                case Unrecognized:
                    cout << "Parser error: unrecognized symbol" << endl;
                    break;
            }
        }

        if (!current_key_.empty()) {
            if (state == WordState) {
                PutWord(output);
            } else
            if (state == PunctuationState) {
                PutPunctuation(output);
            }
        }
    }

    private:

    void PutWord(string* output) {
 //       cout << "Get " << current_key_ << " " <<  current_rank_ << endl;
 //       *output += dictionary_->GetWord(current_key_, current_rank_);
        cout << dictionary_->GetWord(current_key_, current_rank_);
        current_key_.clear();
        current_rank_ = 0;
    }

    void PutPunctuation(string* output) {
  //      *output += dictionary_->GetPunctuation(current_rank_);
        cout << dictionary_->GetPunctuation(current_rank_);
        current_key_.clear();
        current_rank_ = 0;
    }

    static Symbol CharToSymbol(const char& input_char) {

        if (input_char == ' ') {
            return Space;
        } else
        if (input_char >= '2' && input_char <= '9') {
            return Digit;
        } else
        if (input_char == '1') {
            return Punctuation;
        } else
        if (input_char == '*') {
            return Asterisk;
        }

        return Unrecognized;
    }

};



//void Input(T9Dictionary* dictionary, string* query);
void Input(T9Dictionary* dictionary, char* query);
void Output(const string& message);

const int kBufSize = 150000;


int main() {

    char query[kBufSize];
    T9Dictionary dictionary;
//    string query;
    Input(&dictionary, query);

    T9Processor processor(&dictionary);
    string message;
    processor.ParseMessage(query, &message);

    cout << endl;
 //   Output(message);

    return 0;
}

//===========================================================================

//void Input(T9Dictionary* dictionary, string* query) {
void Input(T9Dictionary* dictionary, char* query) {

    int dictionary_size;
    cin >> dictionary_size;
    string new_word;

    for (int i = 0; i < dictionary_size; ++i) {
        int frequency;
        cin >> new_word >> frequency;
        dictionary->InsertWord(new_word, frequency);
    }

    dictionary->InsertPunctuation(".");
    dictionary->InsertPunctuation(",");
    dictionary->InsertPunctuation("?");

    cin.ignore(1);
    cin.getline(query, kBufSize);

    //cin.ignore(1);
    //getline(cin, *query);
}

//===========================================================================

void Output(const string& message) {

    cout << message << endl;
}
