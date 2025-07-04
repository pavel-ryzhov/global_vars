
#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<math.h>

using std::cout;
using std::cin;
using std::vector;
using std::list;
using std::string;
using std::pair;

//                          a    b    c    d    e    f    g    h    i    j    k    l    m    n      
const char ALPHABET[26] = {'2', '2', '2', '3', '3', '3', '4', '4', '4', '5', '5', '5', '6', '6', 
    '6', '7', '7', '7', '7', '8', '8', '8', '9', '9', '9', '9'};
//   o    p    q    r    s    t    u    v    w    x    y    z

const int PRIME_MOD = 50021;


// hash_number^pow(mod 2^32).  hash_number = 11, pow = 0..19
const unsigned int HASH_NUMBER_IN_POW[20] = {1, 11, 121, 1331, 14641, 161051, 1771561, 19487171, 
    214358881, 2357947691, 167620825, 1843829075, 3102250641, 4059985979, 1710172809, 1632031715, 
    772479681, 4202309195, 3275728185, 1673271667};


struct Word {
    string word;
    int priority;

    bool operator< (const Word &rhs) {
        return priority < rhs.priority 
            || (priority == rhs.priority && std::lexicographical_compare(word.begin(), word.end(), 
            rhs.word.begin(), rhs.word.end()));
    }
};

typedef list<pair<string, vector<Word> > > hash_table_type;

bool CompareWord(const Word &lhs, const Word &rhs) {
    return lhs.priority > rhs.priority || (lhs.priority == rhs.priority && 
        std::lexicographical_compare(lhs.word.begin(), lhs.word.end(),
        rhs.word.begin(), rhs.word.end()));
}

struct Query {
    enum {punctuation, space, wd} attribute;
    string text;
    int shift;

    Query() 
        :shift(0), text(), attribute()
    {;}
};

string WordToDigits(const string &word) {
    string result;
    for(string::const_iterator it = word.begin(); it != word.end(); ++it) {
        result.push_back(ALPHABET[*it - 'a']);
    }
    return result;
}

void Input(vector<Word> *dictionary, string *query_string) {
    int count_words;
    cin >> count_words;
    dictionary->resize(count_words);
    for(size_t number_word = 0; number_word < count_words; ++number_word) {
        cin >> (*dictionary)[number_word].word;
        cin >> (*dictionary)[number_word].priority;
    }
    cin.ignore(1);
    std::getline(cin, *query_string);
}

void BuildDigitsT9Input(const vector<Word> &dictionary, vector<string> *digitsT9) {
        for(size_t number = 0; number < dictionary.size(); ++number) {
            (*digitsT9)[number] = WordToDigits(dictionary[number].word);
        }
}

int GetHash(const string &digits) {
    unsigned int hash = 0;
    for(size_t digit = 0; digit < digits.size(); ++digit) {
        hash += (digits[digit] - 48) * HASH_NUMBER_IN_POW[digit];
    }
    return hash % PRIME_MOD;
}

void SortByPriority(vector<hash_table_type*> *hash_table) {
    for(vector<hash_table_type*>::iterator it = hash_table->begin(); 
        it != hash_table->end(); 
        ++it) {
            if (*it != NULL) {
                for(hash_table_type::iterator it_list = (*it)->begin(); 
                    it_list != (*it)->end();
                    ++it_list) {
                        std::sort(it_list->second.begin(), it_list->second.end(), CompareWord);
                }
                
            }
            
    }
}

void BuildHashTable(const vector<Word> &dictionary, const vector<string> &digitsT9, 
    vector<hash_table_type*> *hash_table) {
        for (size_t word_number = 0; word_number < dictionary.size(); ++word_number) {
            int position = GetHash(digitsT9[word_number]);
            if ((*hash_table)[position] == NULL) {
                (*hash_table)[position] = new hash_table_type();
            }
            hash_table_type::iterator insert_position = (*hash_table)[position]->begin();
            while (insert_position != (*hash_table)[position]->end()
                && insert_position->first != digitsT9[word_number]) {
                    ++insert_position;
            }
            if (insert_position != (*hash_table)[position]->end()) {
                insert_position->second.push_back(dictionary[word_number]);
            }
            else {
                (*hash_table)[position]->push_back(
                    std::make_pair(digitsT9[word_number], vector<Word>()));
                (*hash_table)[position]->back().second.push_back(dictionary[word_number]);
            }
        }
        SortByPriority(hash_table);
}

void ParseQueryString(const string &query_string, vector<Query> *queries) {
    for(string::const_iterator it = query_string.begin(); it != query_string.end(); ++it) {
        switch(*it) {
            case '1': {
                queries->push_back(Query());
                queries->back().attribute = Query::punctuation;
                break;  
            }
            case '*':  {
                ++queries->back().shift;
                break;
            }
            case ' ': {
                queries->push_back(Query());
                queries->back().attribute = Query::space;
                break;
            }
            default:  {
                if (!queries->empty()) {
                    if(queries->back().attribute != Query::wd) {
                        queries->push_back(Query());
                        queries->back().attribute = Query::wd;
                    }
                }
                else {
                    queries->push_back(Query());
                    queries->back().attribute = Query::wd;
                }
                queries->back().text.push_back(*it);
            }
        }
    }
}

hash_table_type::iterator FindTargetDigitsVector(hash_table_type::iterator begin, 
    hash_table_type::iterator end, const string &digits) {
        for ( ; begin != end; ++begin) {
            if (begin->first == digits) {
                break;
            }
        }
        return begin;
}

void CorrectPriority(size_t index_to_correct, hash_table_type::iterator *target_position) {
    Word corrected_word = (*target_position)->second[index_to_correct];
    ++corrected_word.priority;
    size_t index_to_insert = index_to_correct;
    for ( ; index_to_insert > 0 && 
        (*target_position)->second[index_to_insert - 1].priority <= corrected_word.priority;  
        --index_to_insert) {
            (*target_position)->second[index_to_insert] = 
                (*target_position)->second[index_to_insert - 1];
    }
    (*target_position)->second[index_to_insert] = corrected_word;
}

string GetWord(const Query query, vector<hash_table_type*> *hash_table) {
    int hash = GetHash(query.text);
    hash_table_type::iterator target_position = 
        FindTargetDigitsVector((*hash_table)[hash]->begin(), (*hash_table)[hash]->end(), query.text);
    string result;
    if (target_position != (*hash_table)[hash]->end()) {
        result = target_position->second[query.shift % target_position->second.size()].word;
        CorrectPriority(query.shift % target_position->second.size(), &target_position);
    }
    return result;
}

void ComputeResultString(const vector<Query> &queries, vector<hash_table_type*> *hash_table,
    string *result_string) {
        for(vector<Query>::const_iterator it = queries.begin(); it != queries.end(); ++it) {
            switch(it->attribute) {
                case Query::punctuation: {
                    switch(it->shift % 3) {
                        case 0:  {
                            result_string->push_back('.');
                            break;
                        }
                        case 1:  {
                            result_string->push_back(',');
                            break;
                        }
                        case 2:  {
                            result_string->push_back('?');
                            break;
                        }
                    }
                    break;
                }
                case Query::space: {
                    result_string->push_back(' ');
                    break;
                }
                case Query::wd: {
                    *result_string += GetWord(*it, hash_table);
                    break;
                }
            }
        }
}

void Output(string &result_string) {
    cout << result_string << std::endl;
}

void FreeMemory(vector<hash_table_type*> *hash_table) {
    for(size_t index = 0; index < hash_table->size(); ++index) {
        if ((*hash_table)[index] != NULL) {
            delete (*hash_table)[index];
        }
    }
}


int main()
{
    vector<Word> dictionary;
    string query_string;
    Input(&dictionary, &query_string);

    vector<string> digitsT9(dictionary.size());
    BuildDigitsT9Input(dictionary, &digitsT9);

    vector<hash_table_type*> hash_table(PRIME_MOD);
    BuildHashTable(dictionary, digitsT9, &hash_table);

    vector<Query> queries;
    ParseQueryString(query_string, &queries);

    string result_string;
    ComputeResultString(queries, &hash_table, &result_string);
        
    Output(result_string);
    FreeMemory(&hash_table);
    
    return 0;
}

