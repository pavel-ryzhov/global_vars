#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef pair<string, int> t_pair;

struct t_node {
    vector< t_pair > words;
    vector<char> n_one;
    t_node* next2;
    t_node* next3;
    t_node* next4;
    t_node* next5;
    t_node* next6;
    t_node* next7;
    t_node* next8;
    t_node* next9;
    //Конструктор
    t_node() {
        next2 = NULL; next3 = NULL; next4 = NULL; next5 = NULL;
        next6 = NULL; next7 = NULL; next8 = NULL; next9 = NULL;
    }
};

    void push_word(t_node* current, string word, int rate) {
        vector<t_pair>::iterator iter = current->words.begin();
        bool y=false;
        if (current->words.empty()) current->words.push_back(make_pair(word, rate));
        else {for (int i=0; i<current->words.size(); i++) {
            if (rate >= (*iter).second) { y = 1; current->words.insert(iter, make_pair(word, rate)); }
            iter++;
        }}
        if (iter-- == current->words.end()) current->words.push_back(make_pair(word, rate));

    }


void ReadDict(t_node * root) {
    int n, rate;
    //cin >> n; //Считал количество слов в словаре
    string s; //int n;
    cin >> n;
    t_node * current;
    current = root;
    for (int i=0; i<n; i++) {
        cin >> s >> rate;
        //char * ptr = s[0];
        int j =0;
        while (s[j] != '\0') {
            switch(s[j]) {
                case 'a':
                case 'b':
                case 'c' :
                    if (current->next2 == NULL) current->next2 = new t_node();
                    current = current->next2;
                    break;
                case 'd':
                case 'e':
                case 'f' :
                    if (current->next3 == NULL) current->next3 = new t_node();
                    current = current->next3;
                    break;
                case 'g':
                case 'h':
                case 'i' :
                    if (current->next4 == NULL) current->next4 = new t_node();
                    current = current->next4;
                    break;
                case 'j':
                case 'k':
                case 'l' :
                    if (current->next5 == NULL) current->next5 = new t_node();
                    current = current->next5;
                    break;
                case 'm':
                case 'n':
                case 'o' :
                    if (current->next6 == NULL) current->next6 = new t_node();
                    current = current->next6;
                    break;
                case 'p':
                case 'q':
                case 'r':
                case 's':
                    if (current->next7 == NULL) current->next7 = new t_node();
                    current = current->next7;
                    break;
                case 't':
                case 'u':
                case 'v' :
                    if (current->next8 == NULL) current->next8 = new t_node();
                    current = current->next8;
                    break;
                case 'w':
                case 'x':
                case 'y':
                case 'z':
                    if (current->next9 == NULL) current->next9 = new t_node();
                    current = current->next9;
                    break;

            }
            j++;
        }
        push_word(current, s, rate);
        current = root;

    }



}

void PrintTree(t_node* ptr) {
    if (ptr) {
        PrintTree(ptr->next2);
        for (int i=0; i<ptr->words.size(); i++) {
        cout << ptr->words[i].first << " ";
        }
        cout << endl;
        PrintTree(ptr->next3);
        PrintTree(ptr->next4);
        PrintTree(ptr->next5);
        PrintTree(ptr->next6);
        PrintTree(ptr->next7);
        PrintTree(ptr->next8);
        PrintTree(ptr->next9);
    }
}

void PlusRate(t_node * current, int k) {
    vector<t_pair>::iterator iter = current->words.begin();
    //cout << k;
    string s = current->words[k].first;
    int rate = current->words[k].second;
    rate++;
    iter += k;
    current->words.erase(iter);
    iter = current->words.begin();
    if (current->words.empty()) current->words.push_back(make_pair(s, rate));
    else {for (int i=0; i<current->words.size(); i++) {
            if (rate >= (*iter).second) { current->words.insert(iter, make_pair(s, rate)); break; }
            iter++;
        }}
    if (iter-- == current->words.end()) current->words.push_back(make_pair(s, rate));

}

void EncryptPhrase(t_node * root) {
    t_node * current = root;
    char h[100001];
    bool b = false;
    cin.ignore();
    cin.getline(h, sizeof(h));
    int i = 0, k;
    int d = 0;
    while (h[i] != '\0')  {
        k = 0;
        switch(h[i]) {
           
            case '1':
                d = 0;
                if (!b) { cout << current->words[k].first; PlusRate(current, k); } //Не забыть повысить рейтинг для слова
                current = root; //Следующее слово пойдет опять от корня
                while (h[i+1] == '*') {
                    d++; i++;
                }
                cout << root->n_one[d%(root->n_one.size())];
                b = true;
                break;

            case '2':
                current = current->next2;
                break;

            case '3':
                current = current->next3;
                break;

            case '4':
                current = current->next4;
                break;

            case '5':
                current = current->next5;
                break;

            case '6':
                current = current->next6;
                break;

            case '7':
                current = current->next7;
                break;

            case '8':
                current = current->next8;
                break;

            case '9':
                current = current->next9;
                break;

            case ' ':
                if (current == root) cout << " ";
                if (!b) { cout << current->words[k].first << " "; PlusRate(current, k); } //Повысить частоту слова!
                b = false;
                current = root;
                break;

            case '*':
                b = true;
                d = 0;
                while (h[i] == '*') {
                    d++; i++;
                }
                //if (h[i] != '*') break;
                int num;
                num = d%(current->words.size());
                cout << current->words[num].first; //Рейтинг!!!
                PlusRate(current, num);
                current = root;
                i--;
                break;

            case '\0':
                cout << current->words[0].first;
                PlusRate(current, 0);
                break;

        }
        i++;
    }
   if (!b) { cout << current->words[0].first;
    PlusRate(current, 0);// Рейтинг!!!
    current = root; }
}

int main(int argc, char** argv) {
    t_node* root = new t_node();
    root->n_one.push_back('.');
    root->n_one.push_back(',');
    root->n_one.push_back('?');
    //t_node* root = dict_tree;
    ReadDict(root);
    //PrintTree(root);
    EncryptPhrase(root);
    return (EXIT_SUCCESS);
}

