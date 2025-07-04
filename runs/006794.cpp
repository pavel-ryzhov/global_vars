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
#include <map>
using namespace std;




class Node{
public:
	int depth;
	Node * parent;
	bool haveParent;
	Node(){
		depth = 0;
		haveParent = 0;
		parent = 0;
	}
};

class List{
private:
	map<int,Node*> list;
	map<int,int> children;
	void addLink(int left, int right, int weight){
		if(list[left] == 0)list[left] = new Node();
		if(list[right] == 0)list[right] = new Node();
		if(!list[left]->haveParent){
			list[left]->parent = list[right];
			list[left]->depth = weight;
			list[left]->haveParent = true;
		}else{
			list[right]->parent = list[left];
			list[right]->depth = weight;
			list[right]->haveParent = true;
		}
	}
	int findLenght(int l, int r){
		if(l == r) return 0;
		Node *left = list[l], *right = list[r];
		Node *parent;
		int depth = 0,dep = 0;
		parent = left;
		while(parent->parent != 0){
			depth += parent->depth;
			if(parent->parent == right){
				return depth;
			}
			parent = parent->parent;
		}
		depth = 0;
		parent = right;
		while(parent->parent != 0){
			depth += parent->depth;
			if(parent->parent == left){
				return depth;
			}
			parent = parent->parent;
		}

		depth = 0;
		parent = left;
		depth = left->depth + right->depth;
		while(parent->parent!=right->parent){
			if(parent->parent == 0){
				parent = left;
				dep += right->depth;
				right = right->parent;
				depth = dep + right->depth+parent->depth;
			}else{
				parent = parent->parent;
				depth += parent->depth;
			}
		}
		return depth;
	}
public:
	~List(){
		for(int i = 0; i < list.size(); i++){
			delete list[i];
		}
	}

	void setTree(int ** arr1, int N){
		for(int i = 0; i < N; i++){
			addLink(arr1[i][0],arr1[i][1],arr1[i][2]);
		}
	}

	void getLinksLength(int** arr2,int N){
		int result;
		for(int i = 0; i<N; i++){
			cout<<findLenght(arr2[i][0],arr2[i][1])<<endl;
		}
	}
};



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
	List *list = new List();

	int  maxVerNumb = 0, pars = 0,links = 0;
	cin>>maxVerNumb;
	links = maxVerNumb-1;
	int** arr1 = new int*[links];
	if(maxVerNumb == 1){
		cout<<0;
	}else if(maxVerNumb>1){
		for(int i = 0;i<links;i++){
			arr1[i] = new int[3];
			for (int j = 0; j < 3; j++){
				int result = 40001;
				while(cin){
					result = getSomething(result);
					if(result!=40001){
						break;
					}
					if(result==-2){
						continue;
					}
				}
				arr1[i][j] = result;
			}
		}
	}



	cin>>pars;
	int** arr2 = new int*[pars];
	if(pars==0){
		cout<<0;
	}else{
		for(int i = 0;i<pars;i++){
			arr2[i] = new int[2];
			for (int j = 0; j < 2; j++){
				int result = 0;
				while(cin){
					result = getSomething(result);
					if(result!=40001){
						break;
					}
				}
				arr2[i][j] = result;
			}
		}
	}

	list->setTree(arr1,links);
	list->getLinksLength(arr2,pars);


	return 0;

}
