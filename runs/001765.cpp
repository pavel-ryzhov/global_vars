#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>

using std::vector;
using std::list;
using std::pair;
using std::string;
using std::cin;
using std::cout;
using std::map;

struct less_compare {
    bool operator() (int a, int b) {
        return a > b;
    }
};

class Vertex {
public:
    vector <Vertex*> children;
    map <int, list <string>, less_compare > words;
    Vertex() {
        children.resize(8);
    }
};
//Функция возвращает номер кнопки - 2
int FindButtonNumber(char symbol) {
    if(symbol >= 'a' && symbol <= 'c') {
        return 0;
    }
    if(symbol >= 'd' && symbol <= 'f') {
        return 1;
    }
    if(symbol >= 'g' && symbol <= 'i') {
        return 2;
    }
    if(symbol >= 'j' && symbol <= 'l') {
        return 3;
    }
    if(symbol >= 'm' && symbol <= 'o') {
        return 4;
    }
    if(symbol >= 'p' && symbol <= 's') {
        return 5;
    }
    if(symbol >= 't' && symbol <= 'v') {
        return 6;
    }
    if(symbol >= 'w' && symbol <= 'z') {
        return 7;
    }
    if(symbol == ' ' || symbol == '.' || symbol == ',' || symbol == '?') {
        return -1;
    }
}

class Tree {
    Vertex* root;
public:
    Tree() {
        root = new Vertex;
    }
    void AddWord(string word, int frequency) {
        Vertex* current_vertex = root;
        for(int index = 0; index < word.size(); ++index) {
            current_vertex->children.resize(8);
            int button_number = FindButtonNumber(word[index]);
            if(current_vertex->children[button_number] == NULL) {
                Vertex* new_vertex = new Vertex;
                current_vertex->children[button_number] = new_vertex;
            }
            current_vertex = current_vertex->children[button_number];
        }
        current_vertex->words[frequency].push_back(word);
        //current_vertex->words.push_back(make_pair(word, frequency));
    }
    string GetText(const string& query) {
        string answer;
        answer.reserve(query.size());
        Vertex* current_vertex = root;
        for(int index = 0; index < query.size(); ) {
            if(query[index] >= '2' && query[index] <= '9') { //буква
                current_vertex = current_vertex->children[query[index] - '2'];
                ++index;
            }
            else { //конец слова
                map <int, list <string>, less_compare>::iterator one_button_combination_iter = current_vertex->words.begin();
                list <string>::iterator one_frequency_words_iter = one_button_combination_iter->second.begin();
                while(query[index] == '*') {
                    ++index;
                    ++one_frequency_words_iter;
                    if(one_frequency_words_iter == one_button_combination_iter->second.end()) {
                        ++one_button_combination_iter;
                        one_frequency_words_iter = one_button_combination_iter->second.begin();
                    }
                }
                answer = answer + *one_frequency_words_iter;
                int new_frequency = one_button_combination_iter->first + 1;
                current_vertex->words[new_frequency].push_front(*one_frequency_words_iter);
                one_button_combination_iter->second.erase(one_frequency_words_iter);
                if(one_button_combination_iter->second.empty()) {
                    current_vertex->words.erase(one_button_combination_iter);
                }
                if(query[index] == '1') {
                    char token = '.';
                    ++index;
                    while(query[index] == '*') {
                        if(token == '.') {
                            token = ',';
                        }
                        else {
                            if(token == ',') {
                                token = '?';
                            }
                            else {
                                token = '.';
                            }
                        }
                        ++index;
                    }
                    answer = answer + token;
                }
                while(query[index] == ' ') {
                    ++index;
                    answer = answer + ' ';
                }
                current_vertex = root;
            }
        }
        if(current_vertex != root) {
            answer = answer + current_vertex->words.begin()->second.front();
        }
        return answer;
    }   
};
void Input(Tree* tree, string& query) {
    int number_word;
    cin >> number_word;
    for(int i = 0; i < number_word; ++i) {
        string word;
        int frequency;
        cin >> word >> frequency;
        tree->AddWord(word, frequency);
    }
    std::getline(std::cin, query);
    std::getline(std::cin, query);
}
int main() {
    Tree tree;
    string query;
    Input(&tree, query);
    cout << tree.GetText(query);
    return 0;
}



