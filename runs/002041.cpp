#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#define constsize 20
using namespace std;


// Imja faila peredaetsa v kachestve parametra argv[1]

void print();

int numberforletter(char a)
{
    if((int)a<100)
      return 2;
    if(((int)a>99)&&((int)a<103))
      return 3;
    if(((int)a>102)&&((int)a<106))
      return 4;
    if(((int)a>105)&&((int)a<109))
      return 5;
    if(((int)a>108)&&((int)a<112))
      return 6;
    if(((int)a>111)&&((int)a<116))
      return 7;
    if(((int)a>115)&&((int)a<119))
      return 8;
    if(((int)a>118)&&((int)a<123))
      return 9;
          
}


struct item{
      string word;
      int wordlength;
      int rating;
      int *mas;
      item *down;
      item *up;
      item *right;
      item *left;
          }*start;
       


void tomatr( char *word1, int rait, int length)
{            
     item *temp1=start, *temp2=0;
     int *mas1=new int[length];
     for(int i=0;i<length;i++)
       mas1[i]=numberforletter(word1[i]);     
     for(int i=1;i<mas1[0];i++)
       temp1=temp1->down;
     if(temp1->wordlength==0)
     {
       temp1->word=word1;
       temp1->rating=rait;
       temp1->mas=mas1;
       temp1->right=0;
       temp1->left=0;
       temp1->wordlength=length;
       }
     else{
          item *cr= new item();
          cr->word=word1;
          cr->mas=mas1;
          cr->wordlength=length;
          cr->down=0;
          cr->up=0;
          cr->rating=rait;
          while((temp1!=0)&&(temp1->wordlength<length))
          {
              temp2=temp1;
              temp1=temp1->right;
            }  
          if((temp1==0)||(temp1->wordlength>length))
            { 
               if(temp2!=0)
              temp2->right=cr;
              cr->right=temp1;
              cr->left=temp2;
              if(temp1!=0)
              temp1->left=cr;
              if(temp2==0)
              {
                          cr->up=temp1->up;
                          cr->down=temp1->down;
                          temp1->up->down=cr;
                          temp1->down->up=cr;
                          temp1->down=0;
                          temp1->up=0;
              }
            }
          else
          {
              while((temp1!=0)&&(temp1->mas[length-1]<mas1[length-1])&&(temp1->wordlength==length))
              {
               temp2=temp1;
               temp1=temp1->right;
              }
              if((temp1==0)||(temp1->wordlength>length)||(temp1->mas[length-1]>mas1[length-1]))
              { 
                temp2->right=cr;
                cr->right=temp1;
                cr->left=temp2;
                if(temp1!=0)
                temp1->left=cr;
                 if(temp2==0)
              {
                          cr->up=temp1->up;
                          cr->down=temp1->down;
                          temp1->up->down=cr;
                          temp1->down->up=cr;
                          temp1->down=0;
                          temp1->up=0;
              }
              }
              else
              {
                  while((temp1!=0)&&(temp1->rating>=rait)&&(temp1->mas[length-1]==mas1[length-1])&&(temp1->wordlength==length))
                  {
                   temp2=temp1;
                   temp1=temp1->right;
                  }
                  temp2->right=cr;
                  cr->right=temp1;
                  cr->left=temp2;
                  if(temp1!=0)
                  temp1->left=cr;
                   if(temp2==0)
                   {
                          cr->up=temp1->up;
                          cr->down=temp1->down;
                          temp1->up->down=cr;
                          temp1->down->up=cr;
                          temp1->down=0;
                          temp1->up=0;
                   }
              
              }
          }

          }
          
}



int check(int *mas, item *temp, int length)
{
        for(int i=0;i<length;i++)
                if (mas[i]!=temp->mas[i])
                   return 1;
                   
   return 0;     
}

void tofile(ofstream& c, int *mas, int length, int numberofstars)
{
     int flag=1;
     item *temp=start,*temp1,*temp2;
     for(int i=1;i<mas[0];i++)
        temp=temp->down;
         while(flag==1)
     {
        if(length==temp->wordlength)
          {
          if(check(mas,temp,length)==1)
           {temp=temp->right;
           }
          else
           {
            for(int i=0;i<numberofstars;i++)
            temp=temp->right;
             c<<temp->word;
             temp->rating++;
             temp1=temp->left;
             temp2=temp->right;
             if(temp2!=0)
             temp2->left=temp->left;
             if(temp1!=0)
             temp1->right=temp->right;
             else
                  return;
             
             while((temp1!=0)&&(temp1->wordlength==temp->wordlength)&&(temp1->rating<=temp->rating))
             {
               temp2=temp1;
               temp1=temp1->left;
             }
             
             if(temp1!=0)
             temp1->right=temp;
             else{
                  temp->up=temp2->up;
                  temp->down=temp2->down;
                  temp2->up->down=temp;
                  temp2->down->up=temp;
                  temp2->up=0;
                  temp2->down=0;
                  }
             temp->left=temp1;
             temp->right=temp2;
             if(temp2!=0)
             temp2->left=temp;
             
                              
             return;
           }
          }   
        else
             temp=temp->right;
                                            
     }
}


int main(int argc, char *argv[])
{
    
    string filename;
    cout<<"vvedite imja faila"<<endl;
    cin>>filename;
   // if(argc<2) {cout<<"No file has been linked"<<endl; return 1;}
    start=new item();
    item *temp=start;
    for(int i=0;i<8;i++)
    {
      item *a= new item();
      a->down=0;
      a->up=temp;
      a->wordlength=0;
      temp->down=a;
      temp=a;        
    }
    start->word='.';
    temp=new item();
    temp->word=',';
    start->right=temp;
    item *temp2=new item();
    temp2->word='?';
    temp->right=temp2;
    temp2->right=0;
    int numberofwords,j, numberofstars, reit, codeword[constsize];
    char word[constsize], c;
    ifstream fin(filename.c_str());
    if(fin==0) { cout<<"No file has been linked"<<endl; return 1;}
    ofstream fout("result.txt");
    fin>>numberofwords;
    c=fin.get();
     for(int i=0;i<numberofwords;i++)
    {       for(int i=0;i<constsize;i++)
             word[i]='\0';
            j=0;
            reit=0;
            c=fin.get();
            while(c!=' ')
            {
               word[j]=c;
               j++;
               c=fin.get();
            }
            c=fin.get();
            while(c!='\n')
            {
                reit*=10;
                reit+=(int)c-48;
                c=fin.get();
            }
            tomatr(word,reit,j);
            
    }
    
    c=fin.get();
    do{
                j=0;
                numberofstars=0;
                if((c!='1')&&(c!=' '))
                {
                 while(((int)c>49)&&((int)c<58)&&(!fin.eof()))
                   {
                     codeword[j]=c-48;
                     j++;
                     c=fin.get();
                   }
                   
                 while(c=='*')
                 {
                      numberofstars++;
                      c=fin.get();
                 }
                 tofile(fout,codeword,j,numberofstars);
                }
                if((int)c==49)
                {  
                 numberofstars=0;
                 temp=start;
                 c=fin.get();
                 while(c=='*')
                 {
                  temp=temp->right;
                  c=fin.get();
                 }
                  fout<<temp->word;
                }
                if(c==' ')
                {
                  fout<<' ';
                  c=fin.get();
                }             
    }while(!fin.eof());
    fout.close();
    return 0;
}
