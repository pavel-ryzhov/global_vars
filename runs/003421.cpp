#include <math.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
#include <stdlib.h>
using namespace std;

vector< vector<string> > sp;  // разделенные цифры
vector<float> vert, hor;      // верт и гор площади
vector< vector< vector<float> > > maskv, maskh;  // маска эталонов

// маска эталонов. Лучше вынести в отдельный файл
void fill_mask()
{
    float tarray [] = {22.1306, 20.8126, 17.7107, 13.2295, 8.5896,  5.04626, 3.05823,  //0
                       13.4453, 18.9443, 23.5732, 26.168,  26.1951, 23.4988, 18.4636,  //1
                       2,       2,       30,      32,      32,      1,       1,        //1
                       31.6621, 31.5567, 31.5195, 31.6059, 31.8604, 32.3113, 32.9562,  //2
                       16.1179, 15.5655, 15.1754, 14.9226, 14.8322, 14.9643, 15.3693,  //2
                       8.26562, 7.35742, 6.625,   6.26172, 6.33594, 6.91406, 8.02148,  //2
                       7.53711, 8.37891, 9.73438, 11.2188, 12.125,  12.0469, 11.3281,  //2
                       11.0834, 11.5641, 11.8241, 11.934,  11.9371, 11.8247, 11.5383,  //2
                       9.42031, 9.49199, 9.49174, 9.37588, 9.16278, 8.96128, 8.92653,  //2
                       10.9038, 10.9481, 11.3248, 11.9039, 12.6882, 13.8207, 15.5058,  //3       
                       3.48438, 2.99023, 2.91016, 3.23633, 4.00195, 5.37695, 7.42969,  //3
                       13.2564, 13.1506, 12.9955, 13.2498, 14.2411, 15.9008, 17.661,   //4
                       2.72363, 3.1543,  4.25195, 6.63379, 10.4297, 14.335,  16.0049,  //4
                       12.2325, 13.0056, 14.5955, 16.811,  19.1798, 21.1194, 22.1446,  //4
                       5.32812, 6.14062, 7.53125, 8.4375,  7.42188, 4.9375,  2.8125,   //4
                       6.57251, 7.25415, 8.23047, 9.33887, 10.0742, 10.1995, 10.189,   //4
                       29.4673, 28.1525, 27.2618, 26.8503, 26.9112, 27.4084, 28.2974,  //5
                       5.46875, 4.66406, 4.25,    4.125,   4.24219, 4.60156, 5.26562,  //5
                       12.1213, 12.4135, 12.8784, 13.4569, 14.1459, 14.9951, 16.0853,  //5
                       5.00195, 4.91797, 4.62305, 4.37891, 4.39648, 4.79102, 5.63672,  //5
                       3.2417,  4.21558, 6.26953, 9.4895,  13.1438, 16.0779, 17.5642,  //5
                       22.5036, 20.4006, 19.0488, 18.5526, 18.7645, 19.4042, 20.2117,  //5
                       10.2657, 10.432,  10.7635, 11.1903, 11.4555, 11.3258, 10.7673,  //5
                       14.865,  14.8135, 14.4433, 13.8724, 13.1273, 12.2307, 11.2665,  //5
                       4.51562, 3.71875, 3.42188, 3.44531, 3.64062, 3.96875, 4.54688,  //6
                       21.9036, 20.7236, 17.7345, 13.3944, 8.91174, 5.47632, 3.51514,  //6
                       15.0977, 13.4289, 12.2174, 11.5085, 11.2499, 11.3796, 11.8519,  //6
                       21.7916, 20.8153, 19.139,  17.3547, 16.0647, 15.541,  15.609,   //6
                       17.3362, 17.6072, 16.9956, 15.9332, 14.7915, 13.7667, 12.9011,  //7
                       5.46875, 4.66406, 4.25,    4.125,   4.24219, 4.60156, 5.26562,  //7
                       12.25,   15.4375, 16.6875, 14.375,  9.375,   5.4375,  4.125,    //7
                       10.873,  12.1523, 13.0371, 13.2285, 12.502,  11.0137, 9.24023,  //7
                       9.33594, 10.5352, 10.5156, 9.74609, 8.80859, 7.92578, 7.07812,  //7
                       4.28125, 5.70312, 6.61719, 6.55469, 5.86719, 5.11719, 4.50781,  //7 
                       12.9122, 12.9736, 13.297,  13.7681, 14.2484, 14.6057, 14.7714,  //8
                       6.36914, 5.83789, 5.42969, 5.17773, 5.11523, 5.25195, 5.65039,  //8
                       18.1831, 15.5484, 13.5655, 12.6568, 12.995,  14.5063, 16.8275,  //8
                       11.2188, 9.375,   7.125,   5.5,     4.59375, 4.40625, 4.8125,   //8
                       11.0812, 11.4013, 11.4933, 11.4294, 11.3385, 11.3286, 11.4251,  //8
                       12.9185, 13.1902, 13.2488, 13.2581, 13.311,  13.383,  13.3414,  //8
                       16.7017, 16.1241, 15.2467, 14.0876, 12.6401, 11.0054, 9.42192,  //8
                       10.5449, 9.66797, 9.19141, 8.99219, 8.96289, 9.22852, 10.0684,  //9
                       7.11719, 5.04883, 3.81641, 3.34375, 3.46289, 4.19922, 5.76562,  //9
                       19.1169, 19.4534, 19.6423, 19.9295, 20.4411, 21.067,  21.4905,  //9
                       14.1788, 13.8981, 13.6283, 13.3737, 13.2229, 13.3246, 13.8481,  //9
                       12.1242, 12.3443, 12.3833, 12.402,  12.5115, 12.7267, 12.9554}; //9
    unsigned int i;
    i=0;
    maskv.resize(10);
        maskv[0].resize(1);
            maskv[0][0].insert(maskv[0][0].begin(), tarray+i,tarray+i+7); i+=7;
        maskv[1].resize(3);
            maskv[1][0].insert(maskv[1][0].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[1][1].insert(maskv[1][1].begin(), tarray+i,tarray+i+7); i+=7;
        maskv[2].resize(6);
            maskv[2][0].insert(maskv[2][0].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[2][1].insert(maskv[2][1].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[2][2].insert(maskv[2][2].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[2][3].insert(maskv[2][3].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[2][4].insert(maskv[2][4].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[2][5].insert(maskv[2][5].begin(), tarray+i,tarray+i+7); i+=7;
        maskv[3].resize(2);
            maskv[3][0].insert(maskv[3][0].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[3][1].insert(maskv[3][1].begin(), tarray+i,tarray+i+7); i+=7;
        maskv[4].resize(5);
            maskv[4][0].insert(maskv[4][0].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[4][1].insert(maskv[4][1].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[4][2].insert(maskv[4][2].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[4][3].insert(maskv[4][3].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[4][4].insert(maskv[4][4].begin(), tarray+i,tarray+i+7); i+=7;
        maskv[5].resize(8);
            maskv[5][0].insert(maskv[5][0].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[5][1].insert(maskv[5][1].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[5][2].insert(maskv[5][2].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[5][3].insert(maskv[5][3].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[5][4].insert(maskv[5][4].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[5][5].insert(maskv[5][5].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[5][6].insert(maskv[5][6].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[5][7].insert(maskv[5][7].begin(), tarray+i,tarray+i+7); i+=7;
        maskv[6].resize(4);
            maskv[6][0].insert(maskv[6][0].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[6][1].insert(maskv[6][1].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[6][2].insert(maskv[6][2].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[6][3].insert(maskv[6][3].begin(), tarray+i,tarray+i+7); i+=7;
        maskv[7].resize(6);
            maskv[7][0].insert(maskv[7][0].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[7][1].insert(maskv[7][1].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[7][2].insert(maskv[7][2].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[7][3].insert(maskv[7][3].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[7][4].insert(maskv[7][4].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[7][5].insert(maskv[7][5].begin(), tarray+i,tarray+i+7); i+=7;
        maskv[8].resize(7);
            maskv[8][0].insert(maskv[8][0].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[8][1].insert(maskv[8][1].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[8][2].insert(maskv[8][2].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[8][3].insert(maskv[8][3].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[8][4].insert(maskv[8][4].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[8][5].insert(maskv[8][5].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[8][6].insert(maskv[8][6].begin(), tarray+i,tarray+i+7); i+=7;
        maskv[9].resize(5);
            maskv[9][0].insert(maskv[9][0].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[9][1].insert(maskv[9][1].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[9][2].insert(maskv[9][2].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[9][3].insert(maskv[9][3].begin(), tarray+i,tarray+i+7); i+=7;
            maskv[9][4].insert(maskv[9][4].begin(), tarray+i,tarray+i+7);
            
}

bool white_string(string s)
{
    for (int i=0; i<s.length()-1; ++i)
        if (s[i] != '.') return false;
    return true;
}

void vert_area(vector<string> s)
{
    vert.clear();
    vert.resize(s[0].length(), 0);
    for (unsigned int i=0; i<s[0].length(); ++i)
        for (unsigned int j=0; j<s.size(); ++j)
            if (s[j][i]=='@') vert[i]++;
}

void hor_area(vector<string> s)
{
    hor.clear();
    hor.resize(s.size(), 0);
    for (unsigned int i=0; i<s.size(); ++i)
        for (unsigned int j=0; j<s[0].length(); ++j)
            if (s[i][j]=='@') hor[i]++;
}

int main(int argc, char* argv[])
{
    vector<string> s,buf;
    vector<float> av,av2;
    string t;
    unsigned int i, j, n, x1, x2;
    
    fill_mask();
    while (!cin.fail())
    {
        getline(cin, t);
        s.push_back(t);
    }
    vert_area(s);
    // удаляем пробелы слева и справа
    x1=0;
    while (vert[x1]==0) ++x1;
    x2=vert.size()-1;
    while (vert[x2]==0) --x2;
    for (i=0; i<s.size()-1; ++i)
        if (!white_string(s[i])) 
            buf.push_back(s[i].substr(x1,x2-x1+1));
    
    // разделяем цифры
    sp.resize(3);
    vert_area(buf);
    if ( count(vert.begin(), vert.end(), 0) > 1 )
    {
        x1=0;
        for (i=0; i<3; ++i)
        {
            while ((x1<vert.size()) && (vert[x1]==0)) ++x1;
            x2=x1;
            while ((x2<vert.size()) && (vert[x2]!=0)) ++x2;
            sp[i].clear();
            for (j=0; j<buf.size(); ++j)
                sp[i].push_back(buf[j].substr(x1,x2-x1));
            x1=x2;
        }
    }
    else
    {
        // если не удалось разделить по пустому месту, делим "на глаз"
        x1=buf[0].length()/2 - 12;
        x2=buf[0].length()/2 + 12;
        for (j=0; j<buf.size(); ++j)
        {
            sp[0].push_back( buf[j].substr(0, x1) );
            sp[1].push_back( buf[j].substr(x1, x2-x1) );
            sp[2].push_back( buf[j].substr(x2) );
        }
    }
    for (i=0; i<3; ++i)
    {
        vert_area(sp[i]);
        hor_area(sp[i]);
        n=0;
        while ((vert.size()-n)>7)
        {
            for (j=0; j<vert.size()-1;++j)
                vert[j]= (vert[j]+vert[j+1])/2; 
            ++n;
        }
        n=0;
        while ((hor.size()-n)>7)
        {
            for (j=0; j<hor.size()-1;++j)
                hor[j]= (hor[j]+hor[j+1])/2; 
            ++n;
        }
        vert.resize(7); hor.resize(7);
       // for (j=0; j< hor.size(); ++j) cout << hor[j] << endl;
       // for (j=0; j< vert.size(); ++j) cout << vert[j] << " ";
        //cout << endl;
        float razn, min1, min2;
        int dig;
        min2=70000;
        for (j=0; j<maskv.size(); ++j)  // цифра
        {
            min1=70000;
            for (x1=0; x1<maskv[j].size(); ++x1) // массив шрифтов
            {
                razn=0;
                for (x2=0; x2<maskv[j][x1].size(); ++x2) // значение
                {
                    razn+= fabs(maskv[j][x1][x2]-vert[x2]); // разность
                }
                razn /= maskv[j][x1].size();
                if (razn < min1) min1=razn;
                // минимум среди шрифтов
            }
            if (min1 < min2) {min2 = min1; dig=j;}
            // минимум среди цифр
        }
        cout << dig;
    }    
    cout << endl;
	return 0;
}
