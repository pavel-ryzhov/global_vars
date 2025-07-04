#include <iostream>
#include <vector>
using namespace std;

int compare (char* a, char* b) {
    int i = -1;
    do {
        i++;
        if(a[i] > b[i]) return 1;
        else if(a[i] < b[i]) return -1;
    } while(a[i] && b[i]);
    return 0;
}
char* convert (char* a) {
    char* result = new char[21];
    int i = -1;
    do {
        i++;
        switch(a[i]) {
            case 'a': case 'b': case 'c':
                result[i] = '2';
                break;
            case 'd': case 'e': case 'f':
                result[i] = '3';
                break;
            case 'g': case 'h': case 'i':
                result[i] = '4';
                break;
            case 'j': case 'k': case 'l':
                result[i] = '5';
                break;
            case 'm': case 'n': case 'o':
                result[i] = '6';
                break;
            case 'p': case 'q': case 'r': case 's':
                result[i] = '7';
                break;
            case 't': case 'u': case 'v':
                result[i] = '8';
                break;
            case 'w': case 'x': case 'y': case 'z':
                result[i] = '9';
                break;
            case 0:
                result[i] = 0;
                break;
        }
    } while(a[i]);
    
    return result;
}

struct word {
    char* string;
    unsigned int freq;
    word *next, *prev;
    
    word (const word& b) : string(new char[21]), freq(b.freq) {
        next = prev = 0;
        int i = -1;
        do {
            i++;
            string[i] = b.string[i];
        } while (b.string[i]);
    }
    word (char* str, unsigned int f) : string(new char[21]), freq(f) {
        next = prev = 0;
        int i = -1;
        do {
            i++;
            string[i] = str[i];
        } while(str[i]);
    }
    ~word () {
        delete [] string;
        if(next != 0) delete next;
    }
    
    bool operator > (const word& b) {
        if(freq > b.freq) return true;
        else if(b.freq == freq) return (compare(string, b.string) == -1) ? (true) : (false);
        else return false;
    }
    bool operator < (const word& b) {
        if(freq < b.freq) return true;
        else if(b.freq == freq) return (compare(string, b.string) == 1) ? (true) : (false);
        else return false;
    }
    bool operator == (const word& b) {
        if( (freq == b.freq) && (compare(string, b.string) == 0) ) return true;
        else return false;
    }
};

char points[] = { '.', ',', '?' };
struct wordbook {
    wordbook *next;
    char* digital;
    word* header;
    
    wordbook (char* dig) : digital(new char[21]) {
        header = 0;
        int i; for(i=0; dig[i]; i++)
            digital[i] = dig[i];
        digital[i] = 0;
        next = 0;
    }
    ~wordbook () {
        delete [] digital;
        if(header != 0) delete header;
        if(next != 0) delete next;
    }
    
    void Add (word *w) {
        if(header == 0) {
            header = w;
            return;
        } else {
            if( *header < *w) {
                w->next = header;
                header->prev = w;
                header = w;
                return;
            }
            
            word* current = header;
            while( current->next != 0 && *(current->next) > *w )
                current = current->next;
            
            w->next = current->next;
            if(current->next != 0) (current->next)->prev = w;
            w->prev = current;
            current->next = w;
        }
    }
    char* GetWord (unsigned short n) {
        if(n == 0) {
            header->freq++;
            return header->string;
        }
        word* current = header;
        for(int i=1; i<n; i++)
            current = current->next;
        
        word* need = current->next;
        current->next = need->next;
        if(need->next != 0) (need->next)->prev = current;
        need->freq++;
        
        if(need->freq >= header->freq) {
            header->prev = need;
            need->next = header;
            need->prev = 0;
            header = need;
            
            return need->string;
        }
        
        while( current->freq <= need->freq ) current = current->prev;
        
        need->prev = current;
        need->next = current->next;
        current->next = need;
        if(need->next != 0) (need->next)->prev = need;
        
        return need->string;
    }
    
    void show () {
        word* curr = 0;
        do {
            curr = (curr == 0) ? header : curr->next;
            cout << "{" << curr->string << " " << curr->freq << "}" << endl;
        } while (curr->next != 0);
    }
} *header = 0;
wordbook* GetWordBook (char* dig) {
    if(header == 0) {
        header = new wordbook(dig);
        return header;
    }
    
    wordbook *current = 0;
    do {
        current = (current == 0) ? header : current->next;
        if( compare(current->digital, dig) == 0 ) return current;
    } while(current->next != 0);
    
    current->next = new wordbook(dig);
    return current->next;
}

void filling () {
    int N; cin>>N;
    char* str = new char[21]; unsigned int v;
    for(; N > 0; N--) {
        cin>>str>>v;
        GetWordBook( convert(str) )->Add( new word(str, v) );
    }
}
void parseAndWork(char* str, unsigned char i = 0) {
    char* cmd = new char[21];
    for(int j=0; j<21; j++)
        cmd[j] = 0;
    unsigned int n;
    
    if(str[i] == '1') i++; 
    else {
        for(int j=0; str[i]!='*' && str[i]!='1' && str[i]!=0; i++, j++)
            cmd[j] = str[i];
    }
    
    for(n=0; str[i] == '*'; i++, n++);
    
    if(cmd[0] == 0) cout<<points[n];
    else cout<<GetWordBook(cmd)->GetWord(n);
    
    if(str[i] != 0) parseAndWork(str, i);
    delete [] cmd;
}
void GetPhrase () {
    char* str = new char[21];
    char s; cin.get(s); cin.get(s);
    while(s != 10) {
        if(s == ' ') {
            cout<<" ";
            cin.get(s);
            continue;
        } else {
            for(int i=0; i<21; i++)
                str[i] = 0;
            
            int i = 0;
            do {
                str[i] = s;
                cin.get(s);
                i++;
            } while (s != ' ' && s != 10);
            parseAndWork( str ); 
        }
    }
    delete [] str;
}

int main () {
    filling();
    GetPhrase();
    
    if(header != 0) delete header;
}