#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#define VDIV 5
#define HDIV 3 
#define SAMPLES_NUMBER 11

using namespace std;

const char samples[SAMPLES_NUMBER][VDIV*HDIV+1]={"##_#_####__###_","###_#__#_#__#__","_#_##_##_###_#_","_#_#__##_#_##__","####____#__#_#_","###__#_#_##_###","###__#_##__###_","##_#____##_###_","#__##_#_##_###_","##_##___#__#_#_","##__#__#__#_##_"};
const int samples_ans[SAMPLES_NUMBER]={9,7,4,6,5,2,3,5,6,5,1};

int recognize(vector<string>* pic, int x0, int y0, int x1, int y1){
    //cout<<x0<<' '<<y0<<' '<<x1<<' '<<y1<<endl;
    if (x1==x0||y1==y0) return -1;
    float middle=0;
    int max=0,max_ind=0,matches=0;
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
    for(int i=0;i<VDIV;i++){
        for(int j=0;j<HDIV;j++){
            rezult[i][j]=rezult[i][j]/(h*w);
            middle+=rezult[i][j];
        }
    }
    middle=middle/(VDIV*HDIV);
    for(int k=0;k<SAMPLES_NUMBER;k++){
        matches=0;
        for(int i=0;i<VDIV;i++){
            for(int j=0;j<HDIV;j++){
                if (rezult[i][j]>middle&&samples[k][i*HDIV+j]=='#') matches++;
                //cout<<( rezult[i][j]>middle ? '#':'_' );
            }
            //cout<<endl;
        }
        if (matches>max){
            max=matches;
            max_ind=k;
        }
    }
    /*cout<<endl;
    for(int i=0;i<VDIV;i++){
        for(int j=0;j<HDIV;j++){
            cout<<( rezult[i][j]>middle ? '#':'_' );
        }
        cout<<endl;
    }
    cout<<endl;*/
    return samples_ans[max_ind];
}

int main(int argc, char* argv[]){
    string s="";
    vector<string> pic;
    while(!cin.eof()){
        getline(cin,s);
        pic.push_back(s);
    }
    pic.pop_back();//т.к. обрабатывается последняя пустая строчка
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
       //cout<<"b:"<<begin<<" blank:"<<blank<<" pic: "<<pic.size()<<endl;
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
            //cout<<"i:"<<i<<" b:"<<begin<<" blank:"<<blank<<" pic: "<<v_slice[k+1]-v_slice[k]<<endl;
            if ( (begin && (blank!=v_slice[k+1]-v_slice[k])) || (!begin && (blank==v_slice[k+1]-v_slice[k])) ){
                if ( (h_slice.size()>=k+1) && ((i+1)-h_slice.back()<2) ) //т.е. встретился слишком короткий отрезок
                    h_slice.pop_back();
                else
                    h_slice.push_back(i+1);
                begin=!begin;
            }
        }        
    }
    /*for(int i=0;i<v_slice.size();i++) cout<<v_slice[i]<<" ";
    cout<<endl;
    for(int i=0;i<h_slice.size();i++) cout<<h_slice[i]<<" ";
    cout<<endl;*/
    for(int k=0;k<v_slice.size();k=k+2) {
        cout<<recognize(&pic,v_slice[k],h_slice[k],v_slice[k+1],h_slice[k+1]);
    }
    cout<<endl;
    return 0;
}

