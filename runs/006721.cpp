//============================================================================
// Name        : Exercise2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <istream>
using namespace std;


int numbers[10] = {48,49,50,51,52,53,54,55,56,57};
int getInt(int ch){
	for (int i = 0; i<10; i++){
		if(ch == (int)numbers[i])return i;
	}
}


//поиск пути
int findPath(int from,int to,int bad,vector<int*> where,int row,int col){
	int weight = 0;
	if(from==to){
		return 0;
	}
	for(int i = 0; i<row;i++){
		if(i!=bad){
			if((where[i][from]==1)){
				for(int j = 1; j<col;j++){
					if(where[i][j] == 1){
						if(j==to){
							return where[i][0];
						}
						if(j!=from){
							weight += findPath(j,to,i,where,row,col);
						}
						if(weight!=0){
							weight += where[i][0];
							return weight;
						}
					}
				}
			}
		}
	}
	return weight;
}

//вывод в файл
void returnPars(vector<int*> arr1,vector<int*> arr2,int I,int J,int K){
	char ch;
	int from,to,result;
	for(int i = 0;i<K;i++){
		from = arr2[i][0];
		to = arr2[i][1];
		result = findPath(from,to,I+1,arr1,I,J);
		cout<<result;
		cout<<'\n';
	}
}

int getSomething(int result){
	char ch;
	cin>>ch;
	switch(ch){
	case '\n':
		return 1;
	case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
		cin.putback(ch);
		cin>>result;
		return result;
	default:
		if(isalpha(ch)){
			//cin.putback(ch);
			//cin>>*word;
			//return 1;
		}
	}
		return result;
}


int main() {

    //чтение из файла
	istream &in = cin;

	string fileName;


	int  maxVerNumb = 0, pars = 0,links = 0;
	vector<int*> arr1;
	int *row;
	vector<int*> arr2;

	cin>>maxVerNumb;
	links = maxVerNumb-1;
	if(maxVerNumb == 1){
		cout<<0;
	}else if(maxVerNumb>1){
		for(int i = 0;i<links;i++){
			int *in = new int[maxVerNumb+1];
			for (int k = 0; k < maxVerNumb+1; k++)in[k] = 0;
			arr1.push_back(in);
			for (int j = 0; j < 3; j++){
				int result = 0;
				while(cin){
					result = getSomething(result);
					if(result!=0){
						break;
					}
					if(result==1){
						continue;
					}
				}
				if (j<2){
					arr1[i][result] = 1;
				}else{
					arr1[i][0] = result;
				}
			}
		}
	}



	cin>>pars;
	if(pars==0){
		cout<<0;
	}else{
		for(int i = 0;i<pars;i++){
			int *in = new int[2];
			arr2.push_back(in);
			for (int j = 0; j < 2; j++){
				int result = 0;
				while(cin){
					result = getSomething(result);
					if(result!=0){
						break;
					}
					if(result==1){
						continue;
					}
				}
				arr2[i][j] = result;
			}
		}
	}




	//вызов процедуры обработки и вывода
	returnPars(arr1,arr2,links,maxVerNumb+1,pars);




		return 0;

}
