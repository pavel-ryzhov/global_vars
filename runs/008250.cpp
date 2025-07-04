#define max_n 50000
#define max_s 100000
#define max_w 20
#define stoped -1

#include <iostream> 
#include <string>

using namespace std;

    int n, codes_n;
    string dict[max_n];
    string codes[max_n];
    string codes_list[max_n];
    int root_index[max_n];
    int c2d[max_n];
    int w[max_n];
    int parent[max_n], son[max_n];    

    
bool str_less(string a_s, int a_l, string b_s, int b_l)
{
    if (a_s < b_s) {return true;}
    if (a_s > b_s) {return false;}
    if (w[a_l] > w[b_l]) {return true;}
    if (w[a_l] < w[b_l]) {return false;}
    if (a_l < b_l) {return true;}
    if (a_l > b_l) {return false;}
    return false;
}    

void str_qsort(int l, int r)
{
    int i, j;
    string mid_s, swap_s;
    int mid_l, swap_l;
    i = l; j = r; 
    mid_s = codes[(l + r)/2];
    mid_l = c2d[(l + r)/2];
    do
    {
        while (str_less(codes[i], c2d[i], mid_s, mid_l))
        {
            i++;
        }
        while (str_less(mid_s, mid_l, codes[j], c2d[j]))
        {
            j--;
        }
        if (i <= j)
        {
            swap(codes[i], codes[j]);
            swap(c2d[i], c2d[j]);
            i++;
            j--;
        }    
    } while (i <= j);    
    if (l < j)
    {
        str_qsort(l, j);
    }
    if (i < r) 
    {
        str_qsort(i, r);
    }        
}    

int bin_search(string a)
{
    int i, j, x;
    i = 0; j = codes_n - 1;
    while (i < j)
    {
        x = (i + j)/2;
        if (a > codes_list[x])
        {
            i = x + 1;
        }    
        else 
        {
            if (a < codes_list[x])
            {
                j = x;
            }
            else
            {
                return x;
            }        
        }    
    }    
    return i;
}    

void print_symb(int &a)
{
    switch (a)
    {
        case 0: cout << '.'; break;
        case 1: cout << ','; break;
        case 2: cout << '?'; break;
    }    
    a = stoped;
}    

void print_word(int &a, int root_adr)
{
    cout << dict[c2d[a]];
    int p_n = parent[a];
    w[c2d[a]]++;
    if (p_n == a)
    {
        a = stoped;
        return;
    }    
    while ((w[c2d[p_n]] <= w[c2d[a]]) && (p_n != parent[p_n]))
    {
            p_n = parent[p_n];
    }    
    if (w[c2d[p_n]] > w[c2d[a]])
    {
        if (son[a] == a)
        {
            son[parent[a]] = parent[a];
        }    
        else
        {
            son[parent[a]] = son[a];
            parent[son[a]] = parent[a];
        }
        parent[a] = p_n;
        if (son[p_n] == p_n)
        {
            son[p_n] = a;
            son[a] = a;
        }
        else
        {
            son[a] = son[p_n];
            parent[son[p_n]] = a;
            son[p_n] = a;
        }        
    }    
    else
    {
        if (son[a] == a)
        {
            son[parent[a]] = parent[a];
        }    
        else
        {
            son[parent[a]] = son[a];
            parent[son[a]] = parent[a];
        }
        parent[p_n] = a;
        parent[a] = a;
        son[a] = p_n;
        root_index[root_adr] = a;
    }    
    a = stoped;
}    

void t9_onfly()
{
    int i, j, k;
    char c;
    string tmp;
    
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cin >> dict[i];
        cin >> w[i];
    }
    
    for (i = 0; i < n; i++)
    {
        c2d[i] = i;
        k = dict[i].length();
        codes[i] = "";
        for (j = 0; j < k; j++)
        {
            c = (dict[i][j] - 'a')/3 + '2';
            if (dict[i][j] == 's') {c = '7';}
            if (dict[i][j] == 'v') {c = '8';}
            if (dict[i][j] == 'y') {c = '9';}
            if (dict[i][j] == 'z') {c = '9';}
            codes[i] += c;
        }    
    }    
    
    str_qsort(0, n-1);
    
    tmp = "";
    codes_n = 0;
    for (i = 0; i < n; i++)
    {
        if (codes[i] != tmp)
        {
            codes_list[codes_n] = codes[i];
            root_index[codes_n] = i;
            parent[i] = i;
            son[i] = i;
            codes_n++;
            tmp = codes[i];
        }    
        else
        {
            son[i - 1] = i;
            parent[i] = i - 1;
            son[i] = i;
        }    
    }    
    
    getline(cin, tmp);
    tmp = "";
    int symb_i = stoped, word_i = stoped, root_adr;
    while (cin.get(c))
    {
        if ((c >= '2') && (c <= '9'))//+
        {
            if (symb_i != stoped)
            {
                print_symb(symb_i);
            }
            else 
            {
                if (word_i != stoped)
                {
                    print_word(word_i, root_adr);
                    tmp = "";
                }
                else
                {
                }        
            }    
            tmp += c;
        }
        if (c == '*')//+
        {
            if (symb_i != stoped)
            {
                symb_i++;
            }
            else 
            {
                if (word_i != stoped)
                {
                }
                else
                {
                    root_adr = bin_search(tmp);
                    word_i = root_index[root_adr];
                }   
                word_i = son[word_i];
            }    
        }
        if (c == '1')//+
        {
            if (symb_i != stoped)
            {
                print_symb(symb_i);
            }    
            else
            {
                if (tmp != "")
                {
                    if (word_i != stoped)
                    {
                        print_word(word_i, root_adr);
                        tmp = "";
                    }
                    else
                    {
                        root_adr = bin_search(tmp);
                        word_i = root_index[root_adr];
                        print_word(word_i, root_adr);
                        tmp = "";
                    }
                }    
            }
            symb_i = 0;
        }            
        if (c == ' ')//+
        {
            if (symb_i != stoped)
            {
                print_symb(symb_i);
            }    
            else
            {
                if (tmp != "")
                {
                    if (word_i != stoped)
                    {
                        print_word(word_i, root_adr);
                        tmp = "";
                    }
                    else
                    {
                        root_adr = bin_search(tmp);
                        word_i = root_index[root_adr];
                        print_word(word_i, root_adr);
                        tmp = "";
                    }
                }        
            }   
            cout << ' '; 
        }    
    }    
    if (symb_i != stoped)
    {
        print_symb(symb_i);
    }
    else
    {
        if (tmp != "")
        {
            if (word_i != stoped)
            {
                print_word(word_i, root_adr);
            }
            else
            {
                root_adr = bin_search(tmp);
                word_i = root_index[root_adr];
                print_word(word_i, root_adr);
                tmp = "";
            }
        }
    }            

}    


int main()
{
    t9_onfly();
    return 0;
}

