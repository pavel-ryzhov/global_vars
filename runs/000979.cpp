/*
 * File:   main.cpp
 * Author: Marx
 *
 * Created on 21 Март 2010 г., 0:06
 */


#include <vector>
#include <iostream>
using namespace std;

typedef unsigned short int myint;
typedef std::vector<myint> Line;
typedef std::vector<Line> Matrix;


myint minv(myint k, Line l, Line s){
	myint rez=65535;
	for (myint j=0;j<k;j++){
		if ((l[j]+s[j])<rez) rez=(l[j]+s[j]);
	}
	return rez;
};




int main(int argc, char* argv[])
{

myint N;//количество вершин
cin>>N;
Matrix c (N, Line(N));

for (myint i=0;i<N;i++) {
    for (myint j=0;j<N;j++) {c[i][j]=65535; }
    c[i][i]=0;
}

//заполнение матрицы переходов
myint i, j, s;      
for (myint k=0;k<N-1;k++){
	cin>>i>>j>>s;
        c[i-1][j-1]=s;
        c[j-1][i-1]=s;
}


myint M;//количество пар вершин
cin>>M;

Line ansv (M);//надобы повысить до лонга
for (myint k=0;k<M;k++){
	myint v1, v2;
	cin>>v1;   //начало
	cin>>v2;   //конец

	Matrix ves (N, Line(N));
	for (myint i = 0; i < N; i++)ves[0][i]=65535;
	ves[0][v1-1]=0;

	for (myint i=1;i<N;i++){
		for (myint j=0;j<N;j++)
                ves[i][j]=minv(N,ves[i-1],c[j]);
	}
	ansv[k]=ves[N-1][v2-1];
}

//вывод результатов
for (myint i=0;i<M;i++){
cout<<ansv[i]<<endl;
}

return 0;

}
//---------------------------------------------------------------------------