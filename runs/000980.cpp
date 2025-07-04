
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
int n;//количество вершин
cin>>n;
int** c;//матрица переходов
c=new int*[n];
for (int i=0;i<n;i++) c[i]=new int[n];

for (int i=0;i<n;i++) {
for (int j=0;j<n;j++) {c[i][j]=50000; }
c[i][i]=0;
}

int i, j, s;      //заполнение матрицы переходов
for (int k=0;k<n-1;k++){
	cin>>i;
	cin>>j;
	cin>>s;
c[i-1][j-1]=s;
c[j-1][i-1]=s;
}
int m;//количество пар вершин
cin>>m;

int* ansv=new int[m];
for (int k=0;k<m;k++){
	int v1, v2;
	cin>>v1;   //начало
	cin>>v2;   //конец
	int put=0;
   while (v1!=v2){
	if (v1<v2){
		int vv2=0;
		while (c[v2-1][vv2]==50000)vv2++;
		put=put+c[v2-1][vv2];
		v2=vv2+1;
	}else{
		int vv1=0;
		while (c[v1-1][vv1]==50000)vv1++;
		put=put+c[v1-1][vv1];
		v1=vv1+1;
	}
   }
   ansv[k]=put;
  }

for (int i=0;i<m;i++){
cout<<ansv[i]<<endl;
}
return 0;
}
//---------------------------------------------------------------------------

