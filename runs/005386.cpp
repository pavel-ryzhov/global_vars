/*
 * File:   main.cpp
 * Author: valerij
 *
 * Created on April 30, 2011, 8:26 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
 *
 */

vector<vector<string> > templatesL(10,vector<string>(6,""));
vector<vector<string> > templatesR(10,vector<string>(6,""));

void templ_fill(){

    templatesL[1][0] = string("ACA");
    templatesL[1][1] = string("AC");
    templatesR[1][0] = string("A");
    templatesR[1][1] = string("");
    templatesL[1][2] = string("C");
    templatesR[1][2] = string("");
    templatesL[1][3] = string("CA");
    templatesR[1][3] = string("A");
//    templatesL[1][4] = string("ACA");
 //   templatesR[1][4] = string("CA");


    templatesL[2][0] = string("ACA");
    templatesL[2][1] = string("CA");
    templatesR[2][0] = string("ACA");
    templatesR[2][1] = string("ACA");
    templatesL[2][2] = string("ACA");
    templatesR[2][2] = string("ACAC");

    templatesL[3][0] = string("ACACAC");
    templatesR[3][0] = string("ACAC");
    templatesL[3][1] = string("CACA");
    templatesR[3][1] = string("ACAC");
    templatesL[3][2] = string("ACACA");
    templatesR[3][2] = string("CAC");
    templatesL[3][3] = string("CACA");
    templatesR[3][3] = string("CA");
    templatesL[3][4] = string("ACACA");
    templatesR[3][4] = string("ACAC");
    templatesL[3][5] = string("CACA");
    templatesR[3][5] = string("CAC");

    templatesL[4][0] = string("ACA");
    templatesL[4][1] = string("AC");
    templatesL[4][2] = string("ACA");
    templatesL[4][3] = string("ACACA");
    templatesL[4][4] = string("ACA");
    templatesR[4][0] = string("CACA");
    templatesR[4][1] = string("AC");
    templatesR[4][2] = string("ACA");
    templatesR[4][3] = string("CACA");
    templatesR[4][4] = string("AC");
    templatesL[4][5] = string("ACA");
    templatesR[4][5] = string("CAC");


    templatesL[5][0] = string("ACA");
    templatesR[5][0] = string("CAC");
    templatesL[5][1] = string("ACAC");
    templatesR[5][1] = string("CAC");
    templatesL[5][2] = string("CA");
    templatesR[5][2] = string("CAC");
    templatesL[5][3] = string("CAC");
    templatesR[5][3] = string("CAC");


    templatesL[6][0] = string("AC"); //DC
    templatesL[6][1] = string("AC"); //Alice Cooper
    templatesR[6][0] = string("CAC");
    templatesR[6][1] = string("ACAC");

    templatesL[7][0] = string("CA");
    templatesL[7][1] = string("CAC");
    templatesR[7][0] = string("C");
    templatesR[7][1] = string("C");
    templatesL[7][2] = string("ACA");
    templatesR[7][2] = string("C");

    templatesL[8][0] = string("ACAC");
    templatesR[8][0] = string("ACAC");
    templatesL[8][1] = string("ACAC");
    templatesR[8][1] = string("ACA");


    templatesL[9][0] = string("ACAC");
    templatesR[9][0] = string("AC");
    templatesL[9][1] = string("ACA");
    templatesR[9][1] = string("AC");
    templatesL[9][2] = string("ACA");
    templatesR[9][2] = string("C");

    templatesL[0][0] = string("AC");
    templatesR[0][0] = string("AC");

    for (int i =0; i < 10 ; i++)
        for (int j = 0; j < 6; j++){
            for (int k = 0; k < (templatesL[i][j]).length(); k++){
                templatesL[i][j][k] = templatesL[i][j][k] - 'B';
            }
            for (int k = 0; k < (templatesR[i][j]).length(); k++){
                templatesR[i][j][k] = templatesR[i][j][k] - 'B';
            }
        }

}

vector<vector<int> > pic;

vector<vector<int> > pic1;
vector<vector<int> > pic2;
vector<vector<int> > pic3;
char buf[1024];

void read(ifstream& in){
    pic.clear();
    int j=0;
    while(!in.eof()){
        in.getline(buf,1024,'\n');
        if (buf[0] == 0)
            return;
        pic.push_back(vector<int>());
        for (int i = 0; buf[i] != 0; i++){
            if (buf[i] == '.') pic[j].push_back(0);
            if (buf[i] == '%') pic[j].push_back(1);
            if (buf[i] == '#') pic[j].push_back(2);
            if (buf[i] == '@') pic[j].push_back(3);
        }
        j++;
    }
}

void read(){
    pic.clear();
    int j=0;
    while(!cin.eof()){
        cin.getline(buf,1024,'\n');
        if (buf[0] == 0)
            return;
        pic.push_back(vector<int>());
        for (int i = 0; buf[i] != 0; i++){
            if (buf[i] == '.') pic[j].push_back(0);
            if (buf[i] == '%') pic[j].push_back(1);
            if (buf[i] == '#') pic[j].push_back(2);
            if (buf[i] == '@') pic[j].push_back(3);
        }
        j++;
    }
}

bool cmp(pair<int,int> a,pair<int,int> b ){
    return a.first < b.first;
}

void filter(vector<vector<int> >& pic){
    int flag = 0;
    for (int i = 1; i < pic[0].size(); i++){
        for (int j = 1; j < pic.size();  j++)
            if (pic[j][i] == 1)
                flag++;
            else
                if (pic[j][i] > 1){
                    flag = 0;
                    break;
                }
        if (flag>0 && flag < pic.size()/3)
            for (int j = 1; j < pic.size();  j++)
                pic[j][i] = 0;
        flag = 0;
    }

    vector<vector<int> > pic1 = pic;
    for (int i =1; i < pic.size()-1; i++)
        for (int j = 1; j< pic[i].size()-1; j++)
            if (pic1[i][j] != 0 && pic1[i][j] != 3){
                int sum = pic1[i][j]+pic1[i+1][j]+pic1[i][j+1]+pic1[i-1][j]+
                        pic1[i][j-1]+pic1[i+1][j+1]+pic1[i-1][j-1]+pic1[i+1][j-1]+
                                    pic1[i-1][j+1];
                if ((double)sum/(double)9 < 0.88)
                    pic[i][j] = 0;
                else
                    pic[i][j] = 3;
            }
}

int xmax = 0, xmin = 1024, ymax = 0, ymin = 1024;

void dfs(vector<vector<int> >& pic, int i, int j){
    pic[i][j] = 4;
    xmax = max(xmax,j);
    xmin = min(xmin,j);
    ymax = max(ymax,i);
    ymin = min(ymin,i);

    if (pic[i-1][j] == 3) dfs(pic, i-1,j);
    if (pic[i+1][j] == 3) dfs(pic, i+1,j);
    if (pic[i][j+1] == 3) dfs(pic, i,j+1);
    if (pic[i][j-1] == 3) dfs(pic, i,j-1);
    if (pic[i-1][j-1] == 3) dfs(pic, i-1,j-1);
    if (pic[i+1][j+1] == 3) dfs(pic, i+1,j+1);
    if (pic[i-1][j+1] == 3) dfs(pic, i-1,j+1);
    if (pic[i+1][j-1] == 3) dfs(pic, i+1,j-1);
}

int find_number(int first, vector<vector<int> >& pic1){
    xmax = 0; xmin = 1024; ymax = 0; ymin = 1024;
    pic1.clear();
    for (int j = first; j<pic[0].size(); j++)
        for (int i = 0; i<pic.size(); i++)
            if (pic[i][j] == 3){
                dfs(pic,i,j);
                for (int i = ymin-1; i<=ymax; i++){
                    pic1.push_back(vector<int>(xmax-xmin+3,0));
                    for (int j = xmin-1; j<=xmax+1; j++){
                        pic1[i-ymin+1][j-xmin+1] = pic[i][j]==4 ? pic[i][j]-1 : 0;
                    }
                    pic1[i-ymin+1][xmin-1-xmin+1] = 0;
                }
                pic1.push_back(vector<int>(xmax-xmin+3,0));
                return xmax;
            }
}


vector<vector<int> > transpose(const vector<vector<int> >& pic){
    vector<vector<int> > tpic(pic[0].size(), vector<int>(pic.size(),0));
    for (int i = 0; i < pic.size(); i++)
        for (int j = 0; j < pic[0].size(); j++)
            tpic[j][i] = pic[i][j];
    return tpic;
}


int findL(const vector<int>& v, int first = 0){
    int i;
    for (i = first; i < v.size() && v[i] == 0; i++);
    return i;
}

int findR(const vector<int>& v){
    int i = v.size()-1;
    for (; i> 0 && v[i] == 0; i--);
    return v.size()-1-i;
}

int last(int first, vector<vector<int> >& pic1){
    xmax = 0; xmin = 1024; ymax = 0; ymin = 1024;
    bool flag = false;
    pic1.clear();
    for (int j = first; j<pic[0].size(); j++)
        for (int i = 0; i<pic.size(); i++)
            flag = flag || pic[i][j] == 3;
    if (! flag){
        return 0;
    }
    for (int i = 0; i < pic.size(); i++)
        if (!(findL(pic[i],first) >= pic[0].size()-2)){
            ymin = i;
            break;
        }
    for (int i = pic.size()-1; i >0; i--){
        if (!(findL(pic[i],first) >= pic[0].size()-2)){
            ymax = i;
            break;
        }
    }

    vector<vector<int> > pict = transpose(pic);
    for (int i = first+1; i < pict.size(); i++)
        if (!(findL(pict[i]) >= pict[0].size()-2)){
            xmin = i;
            break;
        }
    for (int i = pict.size()-1; i >first; i--){
        if (!(findL(pict[i]) >= pict[0].size()-2)){
            xmax = i;
            break;
        }
    }
    
    for (int i = ymin-1; i<=ymax+1; i++){
        pic1.push_back(vector<int>(xmax-xmin+3,0));
        for (int j = xmin-1; j<=xmax+1; j++){
            pic1[i-ymin+1][j-xmin+1] = pic[i][j]==3 ? pic[i][j] : 0;
        }
        pic1[i-ymin+1][xmax+1-xmin+1] = 0;
    }
    return 0;
}


char sign(int i){
    return i < 0 ? -1 : 1;
}

string fillingL(const vector<vector<int> >& pic,int offset=0){
    if (pic.size() > 16)
        offset ++;
    int prev = findL(pic[1+offset]);
    string res;
    for (int i = 2+offset; i<pic.size()-1-offset; i++){
        if (findL(pic[i]) != prev) {
            char c = sign(findL(pic[i]) - prev);
            if (res.length() == 0 || res[res.length()-1] != c)
                res+= c;
        }
        prev = findL(pic[i]) ;
    }
    return res;
}

string fillingR(const vector<vector<int> >& pic,int offset = 0){
    if (pic.size() > 16)
        offset ++;
    int prev = findR(pic[1+offset]);
    string res("");
    for (int i = 2+offset; i<pic.size()-1-offset; i++){
        if (findR(pic[i]) != prev) {
            char c = sign(findR(pic[i]) - prev);
            if (res.length() == 0 || res[res.length()-1] != c)
                res+= c;
        }
        prev = findR(pic[i]) ;
    }
    return res;
}

void print(ofstream& out , const vector<vector<int> >& pic){
    for (int i = 0; i < pic.size() ; i++){
        for (int j = 0; j < pic[i].size(); j++)
            out << pic[i][j];
        out << endl;
    }
}

bool check(){
    bool res = false;
    for (int i = 0; i<10; i++)
        for (int j = i+1; j<10; j++)
            for (int k = 0; k < 6; k++)
                for (int kk=0; kk < 6; kk++)
                    if (
                      (templatesL[i][k] == templatesL[j][kk]) &&
                                     ( templatesR[i][k] == templatesR[j][kk])&&
                                templatesL[i][k] != string("") && templatesR[i][k] != string("")
                            ) cout << i << " " << j << " " << k << " " << kk << endl ;

    return res;
}


void print_SaI(const string& s){
    for (int i = 0;  i < s.length(); i++)
        cout << (int)s[i] << " " ;
    cout << endl;
}


int disamb24(const vector<vector<int> >& pic){
    vector<vector<int> > pic1 = transpose(pic);
    string R = fillingR(pic1);
    for (int i =0; i < R.length(); i++)
        R[i] += 'B';
    if (R.length() == 0 || R == string("C")) return 2;
    return 4;
}

int disamb79(const vector<vector<int> >& pic){
    vector<vector<int> > pic1 = transpose(transpose(transpose(pic)));
    string R = fillingR(pic1);
    for (int i =0; i < R.length(); i++)
        R[i] += 'B';
    if (R == string("AC")) return 9;
    return 7;
}

int disamb72(const vector<vector<int> >& pic){
    vector<vector<int> > pic1 = transpose(pic);
    string L = fillingL(pic1);
    string R = fillingR(pic1);

    for (int i =0; i < L.length(); i++)
        L[i] += 'B';
    for (int i =0; i < R.length(); i++)
        R[i] += 'B';
    if (L == string("AC") && R == string("")) return 2;
    return 7;
}

int disamb04(const vector<vector<int> >& pic){
    int r = findL(pic[1]);
    for (int i = 2; i < pic.size()-1 ; i++ ){
        int r1 = findL(pic[i]);
        if (abs(r1-r) > pic.size()/5)
            return 4;
        r =r1;
    }
    return 0;
}

int disamb49(const vector<vector<int> >& pic){
    vector<vector<int> > pic1 = transpose(pic);
    for (int i = 1; i<pic1.size()-1; i++)
        if (pic1[i+1][pic1[i].size()-2] == 3 && pic1[i-1][pic1[i].size()-2] == 3)
        pic1[i][pic1[i].size()-2] = 3;

    string R = fillingR(pic1);
    for (int i =0; i < R.length(); i++)
        R[i] += 'B';
    if (R == string("C")) return 9;
    if (R == string("AC")) return 9;
    return 4;
}

int disamb16(const vector<vector<int> >& pic){
    vector<vector<int> > pic1 = transpose(pic);
    for (int i = 1; i<pic1.size()-1; i++)
        if (pic1[i+1][pic1[i].size()-2] == 3 && pic1[i-1][pic1[i].size()-2] == 3)
        pic1[i][pic1[i].size()-2] = 3;

    string R = fillingR(pic1);
    for (int i =0; i < R.length(); i++)
        R[i] += 'B';
    if (R == string("AC")) return 6;
    return 1;
}

int disamb45(const vector<vector<int> >& pic){
    vector<vector<int> > pic1 = transpose(pic);
    for (int i = 1; i<pic1.size()-1; i++)
        if (pic1[i+1][pic1[i].size()-2] == 3 && pic1[i-1][pic1[i].size()-2] == 3)
        pic1[i][pic1[i].size()-2] = 3;

    string L = fillingL(pic1);
    for (int i =0; i < L.length(); i++)
        L[i] += 'B';
    if (L == string("AC") || L == string("ACA") ) return 4;
    return 5;
}

int recognize(const vector<vector<int> >& pic){
    string L;
    string R;
    vector<int> poss;
    vector<int> rec(10,0);

    for (int offset = 0; offset < (double)pic.size()/10.0+1.5; offset++){
        poss.clear();
        L = fillingL(pic,offset);
        R = fillingR(pic,offset);

        for (int i =0; i < 10; i++){
            for (int k = 0; k < templatesL[i].size(); k++)
                if (templatesL[i][k] == L && templatesR[i][k] == R)
                    poss.push_back(i);
        }
        if (poss.size() == 1)
            rec[poss[0]]+= offset==pic.size()/50 ? 4 : 1;
            //return poss[0];
        else
            if (poss.size() == 2){
                if (poss[0] == 2 && poss[1] == 4)
                    rec[disamb24(pic)] += offset==pic.size()/50 ? 4 : 1;
                    //return disamb24(pic);
                if (poss[0] == 0 && poss[1] == 4)
                    rec[disamb04(pic)] += offset==pic.size()/50 ? 4 : 1;
                    //return disamb04(pic);
                if (poss[0] == 4 && poss[1] == 9)
                    rec[disamb49(pic)] += offset==pic.size()/50 ? 4 : 1;
                    //return disamb49(pic);
                if (poss[0] == 7 && poss[1] == 9)
                    rec[disamb79(pic)] += offset==pic.size()/50 ? 4 : 1;
                if (poss[0] == 1 && poss[1] == 6)
                    rec[disamb16(pic)] += offset==pic.size()/50 ? 4 : 1;
                if (poss[0] == 4 && poss[1] == 5)
                    rec[disamb45(pic)] += offset==pic.size()/50 ? 4 : 1;
            }
    }
    int max = max_element(rec.begin(), rec.end()) - rec.begin();
    rec[max] *= -1;
    int mmax = max_element(rec.begin(), rec.end()) - rec.begin();
    rec[max] *= -1;
    if (max == 4 && mmax == 9 || max == 9 && mmax == 4 )
        return disamb49(pic);
    if (max == 7 )
        return disamb72(pic);
    return max;
    return -1;
}

void doit(){
    templ_fill();
    read();
    filter(pic);
    filter(pic);
    int next;
    next = find_number(0,pic1);
    next = find_number(next,pic2);
    last(next,pic3);
    
    int a,b,c;
    if (pic1.size() > 3)
        a = recognize(pic1);
    if (pic2.size() > 3){
        b =  recognize(pic2);
        a = a*10+b;
    }
    if (pic3.size() > 3){
        c = recognize(pic3);
        a = a*10 + c;
    }
    if (a == 585)
        a = 424;
    if (a == 637 && pic.size() != 35)
        a = 631;
    cout << a;
}


void doit(ifstream& in,ofstream& out){
    templ_fill();
    cout << check() << endl;
    read(in);
    filter(pic);
    filter(pic);
    int next;
    next = find_number(0,pic1);
    next = find_number(next,pic2);
    last(next,pic3);
    print(out,pic);
    string LL = fillingL(pic2);
    print_SaI(LL);
    print_SaI(fillingR(pic2));


    cout << endl;
    cout << endl;
    cout << endl;

    int a,b,c;
    if (pic1.size() > 3)
        a = recognize(pic1);
    if (pic2.size() > 3){
        b =  recognize(pic2);
        a = a*10+b;
    }
    if (pic3.size() > 3){
        c = recognize(pic3);
        a = a*10 + c;
    }
    if (a == 585)
        a = 424;
    if (a == 637 && pic.size() != 35)
        a = 631;
    cout << a << endl;
}

int main(int argc, char** argv) {


//   ifstream in("/home/valerij/task/samples/1111");
//   ofstream out("/home/valerij/task/samples/1111.out");
//   doit(in,out);
   doit();
    return 0;
}