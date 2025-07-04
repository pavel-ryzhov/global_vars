#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector <int> infile;

int stroka,stolbez,znachenie,ishodnaya,konechnaya,v,z;
    
int main(int argc, char *argv[])
{   
    int infinity=40000;
    int b=0;
    string in,out;
    cout<< "vvedite vhodnoi i vihodnoi file"<<'\n';
    cin>>in>>out;
    cout<<"Vibrannie faili:"<<" "<<in<<" "<<out<<'\n';
    ifstream file1(in.c_str());
    for (int i=0; i<=infile.size() && !file1.eof(); i++)
    {
        infile.resize(infile.size()+1);
        file1 >> infile[i];
    }
    file1.close();
    cout<<"Kolichestvo vershin grafa "<<infile[0]<<'\n';
    int** array= new int* [infile[0]];
    for (int j=0; j<infile[0]; j++)
    array[j]=new int[infile[0]];
    for (int test1=0; test1<infile[0]; test1++)
    for (int test2=0; test2<infile[0]; test2++)
    array[test1][test2]=0;
    for (int k=0; k<infile[0]; k++)
    for (int i=1; i<3*(infile[0]-1); i=i+3)
    {
        stroka=infile[i];
        stolbez=infile[i+1];
        znachenie=infile[i+2];
        array[stroka-1][stolbez-1]=znachenie;
        array[stolbez-1][stroka-1]=znachenie;
    } 
    int* x= new int[infile[0]];
    int* t= new int[infile[0]];
    z=infile[3*infile[0]-2];
    int* o= new int[z];
    for (int i=0; i<z; i++)
    o[i]=0;
    for (int i=3*infile[0]-1; i<infile.size(); i=i+2)
    {
        ishodnaya=infile[i]-1;
        konechnaya=infile[i+1]-1;
   int u;		   
   for (u=0;u<infile[0];u++)
   {
      t[u]=infinity; 
      x[u]=0;        
   }
   t[ishodnaya]=0; 
   x[ishodnaya]=1; 
   v=ishodnaya;    
   while(1)
   {
      for(u=0;u<infile[0];u++)
      {
         if(array[v][u]==0)continue; 
         if(x[u]==0 && t[u]>t[v]+array[v][u])  
         {
            t[u]=t[v]+array[v][u];		
         }
      }
      int w=infinity;  
      v=-1;            
      for(u=0;u<infile[0];u++) 
      {
         if(x[u]==0 && t[u]<w)  
         {
            v=u; 
            w=t[u];
         }
      }
      if(v==-1)
      {
         o[b]=0;
         cout<<"Put iz "<<ishodnaya+1<<" v "<<konechnaya+1<<" ne sushestvuet"<<'\n';
         b++;
         break;
      }
      if(v==konechnaya) 
      {      
       o[b]=t[konechnaya];
       cout<<"Dlina puti iz "<<ishodnaya+1<<" v "<<konechnaya+1<<" "<<t[konechnaya]<<'\n';
       b++;
   	   break;
      }
      x[v]=1;
   }
}
    delete[] array;                                  
    delete[] x;
    delete[] t;
    ofstream file2(out.c_str());
    for (int i=0; i<z; i++)
    file2 << o[i] << '\n';
    file2.close();
    delete[] o;
    cout<<"Resultati zapisani v vail. Programma zavershena"<<'\n';
    cin.get();
    getchar();
}
