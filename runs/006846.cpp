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
// Realizes priority queue sorted according to keys.
// Supports operation GetMax(int rank) returning iterator to n-th max element.
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

    typedef map<Key, list<T>, Less<Key> > MapT;

    MapT queue_;

    class QueueIterator;

    public:

    typedef QueueIterator iterator;
    typedef typename list<T>::value_type value_type;
    typedef typename list<T>::pointer pointer;
    typedef typename list<T>::const_pointer const_pointer;
    typedef typename list<T>::reference reference;
    typedef typename list<T>::const_reference const_reference;
    typedef typename list<T>::size_type size_type;


    //TODO: Return iterator to inserted element
    void Insert(const T& value, const Key & key_value, bool on_top = false) {
        if (on_top) {
            queue_[key_value].push_front(value);
        }
        else {
            queue_[key_value].push_back(value);
        }
    }

    void Remove(iterator iter) {
        iter.Remove();
    }

    iterator GetMax(int rank = 0) {

        iterator iter = Begin();
        for (int current_rank = 0; current_rank < rank; ++current_rank, ++iter) ;

        return iter;
    }

    void UpdatePriority(iterator iter, Key new_key, bool on_top) {
        T value = *iter;
        Remove(iter);
        Insert(value, new_key, on_top);
    }

    iterator Begin() {
        return QueueIterator(queue_, queue_.begin(), queue_.begin()->second.begin());
    }

    iterator End() {
        return QueueIterator(queue_, queue_.end(), (--(queue_.rbegin().base()))->second.end());
    }


    private:

    class QueueIterator : public std::iterator<std::forward_iterator_tag, list<T>, ptrdiff_t> {

        MapT* queue_ptr_;
        typename MapT::iterator iter_queue_;
        typename list<T>::iterator iter_;

        public:

           QueueIterator(MapT& ptr,
                   const typename MapT::iterator& it_map,
                   const typename list<T>::iterator& it) :
                       queue_ptr_(&ptr), iter_queue_(it_map), iter_(it) {}

           bool operator == (const QueueIterator& x) const {
               return iter_ == x.iter_ && iter_queue_ == x.iter_queue_;
           }
           bool operator != (const QueueIterator& x) const {
               return iter_ != x.iter_ && iter_queue_ != x.iter_queue_;
           }
           typename list<T>::const_reference operator * () const {
               return *iter_;
           }
           typename list<T>::reference operator * () {
               return *iter_;
           }
           typename list<T>::const_pointer operator -> () const {
               return &(*iter_);
           }
           typename list<T>::pointer operator -> () {
               return &(*iter_);
           }

           QueueIterator& operator ++ () {

               ++iter_;

               if (iter_ == iter_queue_->second.end()) {
                   ++iter_queue_;

                   if (iter_queue_ == queue_ptr_->end()) {
                       return *this;
                   }
                   iter_ = iter_queue_->second.begin();
               }

               while (iter_->empty()) {
                   ++iter_queue_;

                   if (iter_queue_ == queue_ptr_->end()) {
                       return *this;
                   }
                   iter_ = iter_queue_->second.begin();
               }

               return *this;
           }

           QueueIterator operator ++ (int) {
               QueueIterator tmp = *this;
               ++*this;
               return tmp;
           }

           QueueIterator Remove() {

               typename list<T>::iterator new_iter = iter_queue_->second.erase(iter_);

               if (iter_queue_->second.empty()) {

                   queue_ptr_->erase(iter_queue_++);

                   if (iter_queue_ == queue_ptr_->end()) {
                       return *this;
                   }
                   new_iter = iter_queue_->second.begin();
               }

               return QueueIterator(*queue_ptr_, iter_queue_, new_iter);
           }

           const Key& GetKey() {
               return iter_queue_->first;
           }
    };
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
        InsertWord(words_queue_head_->children_[next], new_word, priority, 1);
    }

    //TODO: return const Word& here
    Word GetWord(const string& key, int rank) {
        int next = KeyToIndex(key[0]);
        return GetWord(words_queue_head_->children_[next], key, rank, 1);
    }

    void InsertPunctuation(const Word& symbol) {
        punctuation_.push_back(symbol);
    }

    Word GetPunctuation(int rank) {
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
            InsertWord(h->children_[next], new_word, priority, position + 1);
        }
    }

    //TODO: Return const Word& here rather than a new copy of inserted word
    //For this purpose return iterator from Queue Insert method.
    Word GetWord(Link& h, const string& key, int rank, int position) {

        if (position == key.size()) {

            MultiPriorityQueue<Frequency, Word>::iterator iter = h->words_queue_.GetMax(rank);

            Word queried_word =  *iter;
            Frequency old_freq = iter.GetKey();

            h->words_queue_.Remove(iter);
            h->words_queue_.Insert(queried_word, old_freq + 1, true);

            return queried_word;

        } else {
            int next = KeyToIndex(key[position]);
            return GetWord(h->children_[next], key, rank, position + 1);
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

        ParserState state = WordState;

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
                    *output += " ";
                    state = SpaceState;
                    break;

                case Digit:

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
                    current_key_ = "1";
                    state = PunctuationState;
                    break;

                case Unrecognized:
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
        *output += dictionary_->GetWord(current_key_, current_rank_);
        current_key_.clear();
        current_rank_ = 0;
    }

    void PutPunctuation(string* output) {
        *output += dictionary_->GetPunctuation(current_rank_);
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

void Input(T9Dictionary* dictionary, string* query);
void Output(const string& message);


int main() {

    T9Dictionary dictionary;
    string query;
    Input(&dictionary, &query);

    T9Processor processor(&dictionary);
    string message;
    processor.ParseMessage(query, &message);

    Output(message);

    return 0;
}

//===========================================================================

void Input(T9Dictionary* dictionary, string* query) {

    int dictionary_size;
    cin >> dictionary_size;

    for (int i = 0; i < dictionary_size; ++i) {
        string new_word;
        int frequency;
        cin >> new_word >> frequency;
        dictionary->InsertWord(new_word, frequency);
    }

    dictionary->InsertPunctuation(".");
    dictionary->InsertPunctuation(",");
    dictionary->InsertPunctuation("?");

    cin.ignore(1);
    getline(cin, *query);
}

//===========================================================================

void Output(const string& message) {

    cout << message << endl;
}
