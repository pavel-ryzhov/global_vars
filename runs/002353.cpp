#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
    
int main(int argc, char *argv[])
{
    vector <int> infile;
    int stroka,stolbez,znachenie,ishodnaya,konechnaya,v,z,j;
    int infinity=40000;
    int b=0;
    char a[10],q[10];
    
    scanf("%s %s",&a, &q);
    printf("%s %s\n",a,q);      

    ifstream file1(a);
    for (int i=0; i<=infile.size() && !file1.eof(); i++)
    {
        infile.resize(infile.size()+1);
        file1 >> infile[i];
    }
    file1.close();
    int** array= new int* [infile[0]];
    for (j=0; j<infile[0]; j++)
    array[j]=new int[infile[0]];
    for (int i=0; i<infile[0]; i++)
    for (v=0; v<infile[0]; v++)
    array[i][v]=0;
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
         o[b]=40000;
         b++;
         break;
      }
      if(v==konechnaya) 
      {      
       o[b]=t[konechnaya];
       b++;
   	   break;
      }
      x[v]=1;
   }
}

    delete[] array;                                  
    delete[] x;
    delete[] t;
    ofstream file2(q);
    for (int i=0; i<z; i++)
    file2 << o[i] << '\n';
    file2.close();
    delete[] o;
    return 0;
}
