/* 
 * File:   T9.cpp
 * Author: aioni
 *
 * Created on October 9, 2011, 9:42 PM
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <list>
#include <string>
using namespace std;


    

class word
{
public:
    string w;
    int frequency;
    
    
    word(string W, int f)
    {
        w=W;
        frequency=f;
      
    }
    
};

map <string, list<word> > Dict;//from Dictionary
map <string, int> Num;

 string return_key(string w)
    {
        string k="";
        int l;
        l=w.length();
        for(int i=0;i<l;i++)
        {
           // k*=10;
            switch (w[i])
            {
                case 'a':
                case 'b':
                case 'c':
                { 
                    k+='2';
                }
                break;
                
                case 'd':
                case 'e':
                case 'f':
                { 
                    k+='3';
                }
                break;
                
                case 'g':
                case 'h':
                case 'i':
                { 
                    k+='4';
                }
                break;
                
                case 'j':
                case 'k':
                case 'l':
                { 
                    k+='5';
                }
                break;
                
                case 'm':
                case 'n':
                case 'o':
                { 
                    k+='6';
                }
                break;
                
                case 'p':
                case 'q':
                case 'r':
                case 's':
                { 
                    k+='7';
                }
                break;
                
                case 't':
                case 'u':
                case 'v':
                { 
                    k+='8';
                }
                break;
                
                case 'w':
                case 'x':
                case 'y':
                case 'z':
                { 
                    k+='9';
                }
                break;
                           
            }
        }
        return k;
    }
    

void print_word(string key,int num_of_stars ) 
{
    //cout<<"key "<<key<<" * "<<num_of_stars<<endl;
    if(key=="") return;
    
    
     
    list<word> *T;
    T=&Dict[key];
    
    list<word>::iterator it1=T->begin(),it=T->begin();
    
    if(Num[key]==1)
        {
        cout<<it1->w;
        (it1->frequency)++;
        return;
    }
    num_of_stars=(num_of_stars)%Num[key];
    //if(num_of_stars==0) num_of_stars=Num[key];
    
    
    if (num_of_stars==0) 
    {
        cout<<it1->w;
        (it1->frequency)++;
        return;
    }
    
    
    
    for(int i=0;i<num_of_stars;i++)
    {
        it++;
    }
    
    word temp=word(it->w, it->frequency+1);
    
    cout<<temp.w;
    //(temp.frequency)++;
    it=T->erase(it);
    
    it--;
        while( it->frequency <= temp.frequency && it!=it1)
                it--;
    if(it==it1 && it1->frequency <= temp.frequency) T->insert(it1,temp);
    else
    {
                it++;
                T->insert(it,temp);
    }
    
}

void print_sign(int k)
{
    if(k==0) cout<<".";
    if(k==1) cout<<",";
    if(k==2) cout<<"?";
}

int main(int argc, char** argv) {

    string temp;
    int N;
    cin>>N;
    string w;
    int f;
    list<word> *T;
    list<word>::iterator it;
    
    for(int i=0;i<N;i++)
    {
        cin>>w>>f;
        temp=return_key(w);
        T=&Dict[temp];
        it=T->begin();
        while ( it!=T->end() && (it->frequency)>=f )
        {
             it++;
        }
        T->insert (it, word(w,f));
        Num[temp]++;
        
    }
    getchar();
    
     
    
    char request[100001];
   
    cin.getline (request,100001);
       
    int k=0;
    temp="";
    int i=0;
    
    while (request[i]!=0)
    {
        //cout<<request[i]<<endl;
        switch (request[i])
        {
            case '*':
            {
                k++;
            }
            break;
            
            case ' ':
            {
                
                    
                        if(temp=="1") print_sign(k);
                        else
                            print_word(temp,k);
                        
                        temp="";
                        k=0;
                        cout<<" ";   
            }
            break;
            
            case '1':
            {
                print_word(temp,k);
                temp="1";
                k=0;
                
            }
            break;
            
            default:
            {
                if(temp=="1")
                {
                    print_sign(k);
                    temp="";
                    k=0;
                }
                
               // cout<<request[i]<<endl;
                temp+=request[i];
                
            }
                    
        }
         
        i++;
    }
    
    if(temp!="")
    {
        if(temp=="1") print_sign(k);
        else print_word(temp,k);
    }   
    
    return 0;
}

