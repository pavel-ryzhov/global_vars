#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>

using namespace std;

map<char, int> t9map;
map<unsigned long long, multimap<int,char*> > words_map;

typedef multimap<int,char*>::reverse_iterator multiIter;

long long wordToInt(char* word)
{
    unsigned long long result = 1;
    unsigned int len = strlen(word);
    for(unsigned int i = 0; i<len; i++)
        result = ( result << 3 ) + t9map[word[i]];
    return result;
}

int main(int argc, char *argv[])
{
    t9map['a'] = 0;
    t9map['b'] = 0;
    t9map['c'] = 0;
    t9map['d'] = 1;
    t9map['e'] = 1;
    t9map['f'] = 1;
    t9map['g'] = 2;
    t9map['h'] = 2;
    t9map['i'] = 2;
    t9map['j'] = 3;
    t9map['k'] = 3;
    t9map['l'] = 3;
    t9map['m'] = 4;
    t9map['n'] = 4;
    t9map['o'] = 4;
    t9map['p'] = 5;
    t9map['q'] = 5;
    t9map['r'] = 5;
    t9map['s'] = 5;
    t9map['t'] = 6;
    t9map['u'] = 6;
    t9map['v'] = 6;
    t9map['w'] = 7;
    t9map['x'] = 7;
    t9map['y'] = 7;
    t9map['z'] = 7;

    int dict_size;
    scanf("%i", &dict_size);
    cerr << "Dict size = " << dict_size;
    for(int i = 0; i<dict_size; i++)
    {
        char *word = new char[21];
        int priority;
        scanf("%s %i",word,&priority);
        unsigned long long t9int = wordToInt(word);
        words_map[t9int].insert(words_map[t9int].lower_bound(priority),make_pair(priority,word));
    }
    cerr << "Dict build OK";
    char ch;
    unsigned long long hash = 1;
    int offset = 0;
    getchar();
    do
    {
        ch = getchar();
        switch(ch){
        case '*':
            offset++;
            break;
        case '\n':
        case ' ':
        case '1':
            if(hash == 0)
            {
				int sign = offset % 3;
				if(sign == 0)
                    cout << '.';
                else if(sign == 1)
                    cout << ',';
                else
                    cout << '?';
            }
            else if(hash != 1)
            {
                multiIter it = words_map[hash].rbegin();
                int count = words_map[hash].size();
                if(count == 0)
                {
					cerr << endl << "Word not found! " << hash << " " << endl;
				}
				else
				{
					for(int i = 0; i<offset%count; i++)
						it++;
					char* word = (*it).second;
					int priority = (*it).first + 1;
					cout << word;
					words_map[hash].erase(--(it.base()));
					words_map[hash].insert(make_pair(priority,word));
				}
            }
            offset = 0;
            if(ch == ' ')
            {
                hash = 1;
                cout << ' ';
            }
            else
                hash = 0;
            break;
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if(hash == 0)
            {
				int sign = offset % 3;
				if(sign == 0)
                    cout << '.';
                else if(sign == 1)
                    cout << ',';
                else
                    cout << '?';
                hash = 1;
            }
            hash = (hash << 3) + (int(ch)-50);
            break;
        default:
			cerr << "Unknown symbol: " << ch;
			break;
        }
    } while(ch != '\n');
    return 0;
}
