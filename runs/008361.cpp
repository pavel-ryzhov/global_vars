#define max_n 200
#define max_m 500
#define max_obj 100
#define max_neuro 1000
#define d_n 64
#define d_m 48
#define window_n 4
#define window_m 3
#define destroy_rate 0.5
#define signs_n 10

#include <iostream>
#include <string>

using namespace std;
    
    const int dir[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
    const int s_teta = (window_n * window_m) / 2;
    const int a_teta = 0;
    const int  s_elem = (d_n / window_n) * (d_m / window_m);
    const int a_elem = s_elem;
    const int weight[a_elem][signs_n] = {
{0,0,0,2,0,3,0,11,0,0},
{0,0,3,3,0,4,0,18,0,0},
{0,0,3,5,0,12,0,16,1,0},
{1,0,4,7,0,17,0,18,2,2},
{8,0,8,16,3,15,5,18,9,13},
{14,0,15,18,9,12,11,14,13,17},
{17,5,14,21,9,14,15,14,14,17},
{14,9,16,21,8,18,13,14,17,16},
{15,11,14,19,9,19,14,15,19,18},
{18,13,18,24,11,19,14,13,20,20},
{19,10,20,21,12,19,15,14,15,20},
{9,15,13,19,14,19,14,14,11,7},
{3,18,10,11,11,17,6,14,8,1},
{1,16,5,9,6,18,5,17,3,2},
{0,17,3,9,0,18,2,20,3,1},
{0,14,0,7,0,6,1,15,2,0},
{0,2,0,6,0,4,0,12,0,0},
{1,3,5,9,0,6,0,14,3,3},
{9,9,10,16,0,13,4,15,10,16},
{15,12,17,17,0,16,10,17,13,18},
{16,13,14,20,6,19,16,17,14,17},
{19,14,13,19,9,18,16,17,14,15},
{15,14,13,16,10,24,14,17,13,15},
{13,17,13,18,9,21,9,17,13,15},
{10,20,13,18,14,20,10,17,12,17},
{12,21,16,20,16,20,12,22,15,17},
{16,22,16,20,14,23,14,22,14,20},
{20,19,20,22,16,25,14,22,14,22},
{18,19,20,24,12,25,14,22,15,19},
{8,18,16,22,6,24,14,22,13,13},
{2,17,9,12,0,21,5,23,8,5},
{0,13,2,0,0,8,0,18,2,4},
{0,4,3,6,0,4,0,12,1,3},
{9,7,15,10,0,6,5,12,10,17},
{15,8,15,13,0,16,13,14,16,19},
{16,8,12,12,3,17,17,14,17,13},
{18,10,11,14,9,14,15,12,16,15},
{16,13,10,10,10,14,11,12,15,12},
{15,23,10,8,12,19,15,12,15,10},
{10,23,8,7,15,15,13,10,10,8},
{5,24,11,7,13,15,10,15,6,10},
{8,24,12,11,14,14,12,15,8,12},
{12,23,16,14,11,11,8,15,7,14},
{14,20,13,19,15,12,10,15,10,19},
{17,19,20,26,12,10,10,20,13,21},
{20,15,18,17,6,8,12,20,17,22},
{9,13,14,13,0,5,8,18,16,12},
{2,13,7,3,0,0,4,7,3,1},
{6,5,8,6,0,4,4,8,6,15},
{15,7,14,13,0,11,13,9,13,18},
{16,13,15,15,3,16,17,7,15,17},
{18,15,9,7,8,16,16,7,20,14},
{16,18,10,4,10,12,12,6,17,12},
{16,18,8,8,11,12,15,6,17,8},
{10,16,8,5,14,16,15,6,6,3},
{7,18,8,4,12,9,12,9,4,2},
{3,19,6,9,11,6,6,11,2,7},
{5,20,8,10,12,4,6,11,5,11},
{9,21,11,17,12,3,6,12,7,13},
{12,20,12,15,15,2,6,17,10,15},
{13,18,19,20,13,1,6,20,13,20},
{16,13,20,12,6,2,7,18,16,23},
{13,13,18,13,0,1,8,18,16,17},
{7,11,11,2,0,0,3,1,4,6},
{11,6,9,2,0,4,6,5,8,18},
{16,7,13,6,3,12,17,5,13,19},
{17,11,12,8,7,16,17,5,18,19},
{19,7,11,6,9,11,16,4,20,14},
{16,8,10,3,11,9,14,0,16,8},
{13,7,9,2,16,12,14,0,15,4},
{9,9,8,10,14,6,15,0,8,3},
{6,15,7,10,16,5,11,5,5,3},
{2,19,5,14,14,9,4,5,1,4},
{4,19,9,17,16,8,3,12,3,9},
{9,20,12,14,13,6,2,17,6,14},
{10,15,15,18,16,6,3,18,10,15},
{13,14,19,18,12,5,3,16,16,20},
{14,13,23,14,6,2,0,18,16,20},
{20,12,21,9,1,0,0,7,11,20},
{10,10,12,2,1,0,0,0,7,9},
{15,4,3,0,0,5,10,1,5,17},
{17,4,11,0,3,11,17,5,12,19},
{19,4,8,5,8,14,17,4,15,20},
{18,3,8,5,11,12,17,0,19,11},
{16,5,7,5,16,11,16,0,19,8},
{12,6,5,6,13,14,18,0,16,5},
{8,9,9,10,14,7,17,5,9,5},
{5,18,7,15,11,12,10,5,6,6},
{2,19,9,14,16,14,7,12,10,7},
{3,17,10,16,19,13,5,13,11,8},
{8,16,11,17,17,13,8,16,11,15},
{9,16,16,19,17,12,8,17,9,16},
{11,14,22,17,12,5,3,16,17,17},
{14,12,22,15,7,5,3,12,11,19},
{20,11,13,7,1,2,0,0,10,19},
{15,9,6,0,0,0,0,0,4,15},
{16,2,2,0,3,6,17,0,0,18},
{19,2,4,0,8,10,18,0,6,17},
{19,2,3,0,9,13,18,0,11,19},
{18,2,3,0,17,14,14,0,18,17},
{14,5,3,8,14,12,18,0,20,12},
{11,4,3,10,12,17,18,0,19,11},
{8,12,3,16,10,12,14,5,18,7},
{5,16,5,17,10,14,12,10,15,3},
{2,19,9,16,16,16,8,12,15,7},
{3,15,14,19,19,21,10,16,14,12},
{8,15,16,19,16,22,13,17,12,15},
{9,16,20,22,17,20,13,15,13,12},
{11,13,22,21,13,12,10,13,13,16},
{15,12,15,7,7,11,7,7,11,20},
{20,11,8,4,0,5,3,0,4,19},
{15,9,1,0,0,0,0,0,2,18},
{17,2,2,0,7,4,18,0,0,12},
{20,0,3,0,10,14,18,0,7,16},
{19,0,2,4,19,11,20,0,10,19},
{16,0,0,6,18,14,18,0,17,16},
{12,3,1,10,14,14,19,0,19,11},
{11,9,1,12,7,12,18,5,20,11},
{8,12,5,14,5,12,15,11,18,8},
{5,16,13,18,11,13,10,13,20,8},
{2,14,12,19,16,15,8,15,20,13},
{3,15,16,18,19,21,10,17,16,13},
{8,15,20,20,18,20,16,15,15,13},
{9,15,21,17,21,21,17,13,19,15},
{12,13,16,17,17,22,17,12,14,19},
{15,12,9,15,11,20,15,0,8,20},
{17,11,5,6,5,11,13,0,4,18},
{18,9,0,2,5,3,4,0,0,18},
{20,0,0,0,9,4,18,0,7,0},
{20,0,2,0,17,8,21,0,10,10},
{18,0,2,4,22,5,20,0,14,12},
{15,0,2,5,20,5,16,0,15,12},
{13,8,2,6,12,3,14,2,16,13},
{11,9,8,6,6,6,16,10,18,14},
{8,12,11,9,7,3,13,14,14,12},
{5,14,15,6,13,2,6,14,13,15},
{2,14,17,7,16,14,3,16,15,15},
{3,16,18,13,20,19,6,15,14,15},
{8,14,20,17,20,16,8,14,17,16},
{9,15,16,24,21,16,12,12,18,17},
{12,13,9,26,18,21,16,12,19,18},
{15,12,4,19,11,21,17,0,16,19},
{17,8,0,13,5,19,16,0,9,18},
{16,7,0,3,1,12,16,0,4,16},
{20,0,0,0,10,3,19,0,11,0},
{20,0,0,0,15,0,21,0,14,2},
{19,1,0,0,16,0,20,0,19,4},
{14,3,2,0,13,0,17,2,17,6},
{12,8,6,0,7,1,16,9,12,8},
{11,9,13,0,6,1,11,14,10,9},
{8,12,15,0,7,1,7,12,5,13},
{5,12,16,4,12,6,3,11,7,13},
{2,15,15,5,18,8,0,15,7,10},
{3,15,15,9,22,6,4,15,6,8},
{8,14,11,13,17,11,8,13,13,15},
{11,15,8,17,19,17,9,12,15,14},
{12,13,4,21,16,20,17,5,16,16},
{15,12,0,23,11,19,16,0,18,18},
{18,8,0,22,5,19,17,0,18,18},
{12,7,0,15,3,19,16,0,10,14},
{20,0,0,0,13,3,17,0,16,0},
{20,0,0,6,14,1,21,0,17,0},
{18,1,2,6,12,3,21,2,19,0},
{14,5,7,4,10,3,17,6,15,0},
{12,8,12,4,9,1,13,11,9,1},
{11,9,16,2,11,1,10,14,5,1},
{8,9,18,3,14,6,9,10,3,3},
{5,12,13,4,16,6,5,16,4,3},
{2,14,14,9,21,4,2,15,6,4},
{3,17,11,5,23,8,5,14,5,7},
{10,14,5,7,20,17,10,12,9,13},
{11,15,2,12,18,18,10,11,10,13},
{12,13,2,19,15,17,19,0,15,15},
{14,11,3,23,9,18,18,0,17,18},
{15,7,3,24,6,19,19,0,19,16},
{8,7,4,17,7,19,19,0,18,8},
{15,0,0,10,8,10,15,0,19,0},
{20,1,3,10,9,11,23,3,19,0},
{18,5,8,9,6,8,21,6,18,6},
{15,5,12,5,6,6,16,11,14,7},
{13,8,14,7,6,9,15,14,8,5},
{13,9,15,6,7,6,13,12,3,6},
{8,9,15,8,8,2,10,17,0,3},
{5,11,12,0,14,3,4,16,2,3},
{3,14,9,5,20,7,2,13,6,6},
{5,17,7,5,19,9,5,16,7,8},
{10,14,5,9,17,14,8,12,8,13},
{12,15,5,14,17,13,12,11,11,12},
{12,13,3,18,16,16,16,0,15,16},
{12,10,3,23,9,18,18,0,18,16},
{15,7,5,22,6,19,18,0,19,15},
{6,7,7,15,7,17,15,0,18,4},
{8,0,3,11,5,15,13,0,19,2},
{20,3,9,12,5,13,21,6,20,9},
{17,5,12,17,5,14,22,6,17,10},
{16,5,16,13,5,10,16,12,14,8},
{13,8,16,6,5,6,10,12,7,10},
{12,9,14,3,5,4,10,13,7,9},
{11,8,11,1,6,8,11,18,3,12},
{6,11,9,4,12,5,8,15,2,5},
{7,14,11,6,18,8,3,14,5,10},
{8,17,10,11,14,14,6,14,9,9},
{11,14,11,14,14,13,12,11,15,12},
{9,15,8,17,18,13,12,0,15,15},
{12,13,9,21,12,18,17,0,16,16},
{16,10,8,22,9,19,15,0,17,16},
{10,7,11,17,5,18,18,0,18,9},
{5,7,7,9,7,7,5,0,11,3},
{3,2,8,16,0,9,4,5,8,1},
{14,8,17,21,0,22,14,6,22,11},
{19,8,20,19,0,19,21,11,15,13},
{16,8,19,17,0,13,16,10,14,9},
{16,10,18,14,0,14,15,12,13,12},
{14,11,17,9,1,10,13,17,9,12},
{12,10,14,10,2,7,13,16,8,13},
{10,11,14,10,9,7,10,16,8,10},
{8,14,14,11,16,13,7,16,7,11},
{10,17,14,12,15,16,10,13,7,10},
{10,16,12,15,13,15,15,11,10,15},
{12,17,11,18,17,17,16,0,14,16},
{16,16,12,22,12,19,13,0,15,14},
{10,13,14,17,6,18,16,0,18,11},
{5,10,16,8,1,8,8,0,14,3},
{0,10,10,0,1,2,1,0,3,1},
{1,7,14,10,0,11,4,5,3,1},
{4,9,22,16,0,13,4,9,8,4},
{11,9,20,20,0,21,14,9,19,13},
{20,9,20,20,0,19,19,10,19,16},
{20,11,20,16,0,13,19,18,18,14},
{19,12,20,15,1,12,19,18,17,13},
{16,11,20,13,2,11,17,16,15,12},
{15,10,20,13,10,12,14,16,13,12},
{7,14,21,10,16,15,11,16,10,10},
{10,18,20,12,16,16,10,12,10,13},
{15,16,19,19,13,16,14,3,16,14},
{16,18,18,19,16,18,16,0,18,12},
{9,17,18,16,14,15,16,0,16,7},
{5,14,18,8,6,4,7,0,12,3},
{0,11,17,0,1,0,0,0,2,1},
{0,11,8,0,0,0,0,0,0,1},
{0,6,15,4,0,5,0,2,0,0},
{0,9,13,6,0,9,0,9,1,0},
{1,6,14,7,0,10,2,9,2,4},
{1,7,13,11,0,8,2,10,7,5},
{6,11,13,12,0,11,6,10,10,12},
{12,11,11,15,0,11,14,11,13,11},
{13,8,11,17,7,12,13,13,15,14},
{15,9,11,16,14,18,18,14,17,13},
{17,12,11,18,20,18,18,14,16,13},
{11,15,12,14,16,15,12,11,12,5},
{5,15,12,3,14,5,9,0,9,0},
{1,18,12,1,15,0,1,0,4,1},
{0,17,15,1,14,0,0,0,0,0},
{0,15,12,0,11,0,0,0,0,0},
{0,13,14,0,6,0,0,0,0,0},
{0,11,6,0,4,0,0,0,0,0}};

        
    
    int n, m;
    int komp;
    int been[max_n][max_m];
    int dim[max_obj][6];
    string pict[max_n], number[max_n];
    int number_n, number_m;
    int signal[max_neuro];
    string ans;
    
void neuro_view()
{
    int i, j, adr;
    for (i = 0; i < a_elem; i++)
    {
        signal[i] = 0;
    }    

    for (i = 0; i < d_n; i++)
    {
        for (j = 0; j < d_m; j++)
        {
            if (number[i][j] != '.')
            {
                adr = (i/window_n)*(d_m/window_m) + (j/window_m);
                signal[adr]++;
            }
        }
    }                
    for (i = 0; i < s_elem; i++)
    {
        if (signal[i] > s_teta)
        {
            signal[i] = 1;
        }
        else
        {
            signal[i] = 0;
        }
    }
}    

int neuro_recogn()
{
    int i, j, answer;
    int ans_signal[signs_n];
    for (j = 0; j < signs_n; j++)
    {
        ans_signal[j] = 0;
    }    
    
    for (i = 0; i < a_elem; i++)
    {
        if (signal[i] > a_teta)
        {
            for (j = 0; j < signs_n; j++)
            {
                ans_signal[j] += (weight[i][j] * signal[i]);
            }
        }    
    }    
    
    answer = 0;
    for (i = 1; i < 10; i++)
    {
        if (ans_signal[i] > ans_signal[answer])
        {
            answer = i;
        }
    }
    return answer;
}    

void data_read()
{
    n = 0; m = 0;
    while (!cin.eof())
    {
        cin >> pict[n];
        if ((pict[n][0] != '.') && (pict[n][0] != '%')
        && (pict[n][0] != '#') && (pict[n][0] != '@'))
        {
            break;
        }
        else
        {
            n++;
        }    
    }    
    m = pict[0].length();
}

void data_answer_out()
{
    cout << ans;
}    
    
void data_clear_columns()
{
    int i, j, sum;
    for (j = 0; j < m; j++)
    {
        sum = 0;
        for (i = 0; i < n; i++)
        {
            if (pict[i][j] == '@') {sum++;}
            if (pict[i][j] == '#') {sum++;}
        }
        if (sum == 0)
        {
            for (i = 0; i < n; i++)
            {
                pict[i][j] = '.';
            }
        }
    }
}                    

void data_init(string s[], int x, int y)
{
    int i, j;
    for (i = 0; i < x; i++)
    {
        s[i] = "";
        for (j = 0; j < y; j++)
        {
            s[i] += '.';
        }
    }
}            

void data_resize()
{
    int i, j, x, s, p;
    int step, pen;
    string tmp[max_n];

//resize columns || (number_n, number_m) -> (d_n, number_m)
    data_init(tmp, d_n, d_m);
    s = d_n; p = 0;
    for (i = 0; i < number_n; i++)
    {
        for (x = 0; x < (s / number_n); x++)
        {
            for (j = 0; j < number_m; j++)
            {
                tmp[p][j] = number[i][j]; 
            }
            p++;
        }   
        s = (s % number_n) + d_n;
    }     
    
//resize strings = (d_n, number_m) -> (d_n, d_m)    
    data_init(number, d_n, d_m);
    s = d_m; p = 0;
    for (j = 0; j < number_m; j++)
    {
        for (x = 0; x < (s / number_m); x++)
        {
            for (i = 0; i < d_n; i++)
            {
                number[i][p] = tmp[i][j]; 
            }
            p++;
        }   
        s = (s % number_m) + d_m;
    }     
}    

void bfs(int x, int y, int sv)
{
    int stek[max_n*max_m][2];
    int begin, end, a, b, u, i, j;
    begin = 0;
    end = 1;
    stek[0][0] = x;
    stek[0][1] = y;
    been[x][y] = sv;
    //1 - verh, 2 - pravo, 3 - niz, 4 - levo
    dim[sv][0] = 0;
    dim[sv][1] = x;
    dim[sv][2] = y;
    dim[sv][3] = x;
    dim[sv][4] = y;
    dim[sv][5] = 0;
    while (begin < end)
    {
        dim[sv][0]++;
        a = stek[begin][0];
        b = stek[begin][1];
        if (dim[sv][1] > a) {dim[sv][1] = a;}
        if (dim[sv][2] < b) {dim[sv][2] = b;}
        if (dim[sv][3] < a) {dim[sv][3] = a;}
        if (dim[sv][4] > b) {dim[sv][4] = b;}     
        for (u = 0; u < 8; u++)
        {
            i = a + dir[u][0];
            j = b + dir[u][1];
            if ((i >= 0) && (i < n) && (j >= 0) && (j < m))
            {
                if ((pict[i][j] != '.') && (been[i][j] == -1))
                {
                    stek[end][0] = i;
                    stek[end][1] = j;
                    been[i][j] = sv;
                    end++;
                }    
            }    
        }
        begin++;    
    }    
}    

void predproc()
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            been[i][j] = -1;
        }
    }        
    komp = 0;
    
    data_clear_columns();    
    for (j = 0; j < m; j++)
    {
        for (i = 0; i < n; i++)    
        {
            if ((pict[i][j] != '.') && (been[i][j] == -1))
            {
                bfs(i, j, komp);
                komp++;
            }
        }
    }
    
    for (i = 0; i < komp; i++)
    {
        if (dim[i][0] < (destroy_rate*n*m / 100))
        {
            dim[i][5] = 1;
        }    
    }    
    for (i = 0; i < komp; i++)
    {
        for (j = 0; j < komp; j++)
        {
            
            if ((dim[i][1] < dim[j][1]) && (dim[i][2] > dim[j][2])
            && (dim[i][3] > dim[j][3]) && (dim[i][4] < dim[j][4]))
            {
                if (dim[j][5] != 1)
                {
                    dim[i][5] = 1;
                }    
            }
        }
    }            
    
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (pict[i][j] != '.')
            {
                if (dim[been[i][j]][5] == 1)
                {
                    pict[i][j] = '.';
                }    
            }
        }
    }
}    

void get_number_and_go()
{
    int i, j, u, k = 0;
    for (u = 0; u < komp; u++)
    {
        if (dim[u][5] != 1)
        {
            for (i = dim[u][1]; i <= dim[u][3]; i++)
            {
                number[i - dim[u][1]] = "";
                for (j = dim[u][4]; j <= dim[u][2]; j++)
                {
                    
                    if (been[i][j] == u)
                    {
                        number[i - dim[u][1]] += '@';
                    }
                    else
                    {
                        number[i - dim[u][1]] += '.';                        
                    }    
                }
            }
            number_n = dim[u][3] - dim[u][1] + 1;
            number_m = dim[u][2] - dim[u][4] + 1;
            data_resize();
            
            neuro_view();
            ans += (neuro_recogn() + '0');
        }    
    }    
}    

int main()
{
    // 1 - obu4enie, 0 - raspoznavanie
    data_read();
    predproc();
    predproc();
    ans = "";
    get_number_and_go();
    data_answer_out();
    return 0;
}
    
    
