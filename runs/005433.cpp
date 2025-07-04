#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <math.h>

#define VDIV 5
#define HDIV 3 
#define SAMPLES_NUMBER 31
#define SS 33
#define ES 126

using namespace std;

const char samples[SAMPLES_NUMBER][VDIV*HDIV+1]={".)')!,-++'\"++*!", ")), ,!\") )$!(!!","$,!',\"))\"(-)!(%", "#,!,$'*5&*!,('*","/3-0+$*2=+$/*1-", "00.($0\"BF--$10;", ",()$!+ 2%)'!.)'", "+((\"\"* ;.%!***,",",*$(%! !(% ((&!", "'#!)&\"& 2.!)%'\"",")#&( +($./!(&$!",")0!$0!$0R#0!(,%","-')*\"-*\".,#*''\"",")\"(0&&'))' ,&%#", "$)$&$!'\"3*!,)'\"", "(#,(*%!#=1\"-''!",".5!+2!-5 +2!+/\"",",)&,+$!!: \",&(!","-'$4)#4'$3'%((#", "&#!#1(#1261+%*!","/($4'%4'5H'%()\"","!(!+##/)=B#.*.#", "\"'!),\"10@D1#!)!",",(%+\"'/+-.%(*'\"","-)!4.(4-?4,-*.$", "-)!4.'4-NH,-*.$","*-+, ,()I%!.!!+",")(&''&)&2)%&')%","'-)!)\"#+-\"\"*)'!",")&+\"*&\"%5*!++&#","%2!!.! /  .!%.#"};
const int samples_ans[SAMPLES_NUMBER]={9,7,4,8,5,2,2,3,5,6,9,1,0,8,5,3,1,5,6,5,0,6,4,8,6,6,9,8,3,3,1};

int recognize(vector<string>* pic, int x0, int y0, int x1, int y1){
    if (x1==x0||y1==y0) return -1;
    int min_diff=-1,min_ind=0,diff=0;
    float rezult[VDIV][HDIV];
    memset(rezult,0,VDIV*HDIV);
    const int w=x1-x0;
    const int h=y1-y0;
    for(int i=y0;i<y1;i++){
        for(int j=x0;j<x1;j++){
            switch ((*pic)[i][j]){
                case '.':break;
                case '%':rezult[(i-y0)*VDIV/h][(j-x0)*HDIV/w]+=1;break;
                case '#':rezult[(i-y0)*VDIV/h][(j-x0)*HDIV/w]+=2;break;
                case '@':rezult[(i-y0)*VDIV/h][(j-x0)*HDIV/w]+=3;break;
            }
        }
    }
    for(int k=0;k<SAMPLES_NUMBER;k++){
        diff=0;
        for(int i=0;i<VDIV;i++){
            for(int j=0;j<HDIV;j++){
                diff+=fabs(rezult[i][j]*(ES-SS)*1.0/(h*w)+SS-samples[k][i*HDIV+j]);
            }
        }
        if (diff<min_diff||min_diff==-1){
            min_diff=diff;
            min_ind=k;
        }
    }
    return samples_ans[min_ind];
}

int main(int argc, char* argv[]){
    string s="";
    vector<string> pic;
    while(!cin.eof()){
        getline(cin,s);
        pic.push_back(s);
    }
    while(pic.back()=="") pic.pop_back();//т.к. обрабатывается последняя пустая cтрочка
    int blank;
    bool begin=true;
    vector<int> v_slice;
    vector<int> h_slice;
    for(int j=0;j<pic[0].length()-1;j++){//разбиение по вертикали
        blank=0;
        for(int i=0;i<pic.size();i++){
            if(pic[i][j]=='.'||pic[i][j]=='%'){
                blank++;
            } else {
                break;
            }
        }
        if ( (begin && (blank!=pic.size())) || (!begin && (blank==pic.size())) ){
            v_slice.push_back(j+1);
            begin=!begin;
        }
    }
    for(int k=0;k<v_slice.size();k=k+2){//разбиение по горизонтали
        begin=true;
        for(int i=0;i<pic.size();i++){
            blank=0;
            for(int j=v_slice[k];j<v_slice[k+1];j++){
                if(pic[i][j]=='.'||pic[i][j]=='%'){
                    blank++;
                } else {
                    break;
                }
            }
            if ( (begin && (blank!=v_slice[k+1]-v_slice[k])) || (!begin && (blank==v_slice[k+1]-v_slice[k])) ){
                if ( (h_slice.size()>=k+1) && ((i+1)-h_slice.back()<2) ) //т.е. встретился слишком короткий отрезок
                    h_slice.pop_back();
                else
                    h_slice.push_back(i+1);
                begin=!begin;
            }
        }        
    }
    for(int k=0;k<v_slice.size();k=k+2) {
        cout<<recognize(&pic,v_slice[k],h_slice[k],v_slice[k+1],h_slice[k+1]);
    }
    return 0;
}

