#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef pair<string, int> psi;

int f[26] = { 2,2,2, 3,3,3, 4,4,4, 5,5,5, 6,6,6, 7,7,7,7, 8,8,8, 9,9,9,9 };

class tree {
public:
    vector<psi> v;
    tree *sub[8];
    tree() { for(int i = 0; i < 8; sub[i++] = NULL) ; }
};

bool F_cmp(const psi &p1, const psi &p2) {
    if(p1.second != p2.second)
        return p1.second > p2.second;
    return p1.first < p2.first;
}

void sort(tree *r) {
    for(int i = 0; i < 8; i++)
        if(r->sub[i]) sort(r->sub[i]);
    if(r->v.size() > 1) sort(r->v.begin(), r->v.end(), F_cmp);
}

void del(tree *&r) {
    for(int i = 0; i < 8; i++)
        if(r->sub[i]) del(r->sub[i]);    
    delete r;
    r = NULL;
}

void increase(vector<psi> &v, int i) {
    v[i].second++;
    for( ; i > 0 && v[i].second >= v[i - 1].second; i--)
        swap(v[i], v[i - 1]);
}

string get(string &s, int &stars, tree *r) {
    tree *t = r;
    for(int i = 0; i < s.size(); i++)
        t = t->sub[(s[i] - '0') - 2];
    string res = t->v[stars].first;
    increase(t->v, stars);
    return res;
}

void print_mark(int stars) {
    switch(stars) {
        case 0: cout << "."; break;
        case 1: cout << ","; break;
        case 2: cout << "?"; break;
    }
}

void print(string &s, int &stars, tree *r) {
    if(s != "") {
        if(s == ".") print_mark(stars);
        else cout << get(s, stars, r);
        s = "";
        stars = 0;
    }
}

int main() {
    int N, F, i, j, n;
    string s;
    cin >> N;
    tree *r = new tree(), *t; //r - root
    for(i = 0; i < N; i++) {
        cin >> s >> F;
        t = r;
        for(j = 0; j < s.size(); j++) {
            n = f[s[j] - 'a'] - 2;
            if(!t->sub[n]) t->sub[n] = new tree();
            t = t->sub[n];
        }
        t->v.push_back(psi(s, F));
    }   
    sort(r);
    s = "";
    int stars = 0;
    char c;
    cin.get(c); // '\n'
    while(true) {
        if(!cin.get(c)) {
            print(s, stars, r);
            break;
        }
        switch(c) {
            case 10:
                print(s, stars, r);
                cout << "\n";
                break;
            case ' ':
                print(s, stars, r);
                cout << " ";
                break;
            case '1':
                print(s, stars, r);
                s = ".";
                break;
            case '*':
                stars++;
                break;
            default:
                if(s == ".") print(s, stars, r);
                s += c;
        }
    }
    del(r);
    return 0;
}
