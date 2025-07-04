#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>

using std::cin;
using std::cout;
using std::endl;

class TOP
{
public:
	int timeToOwner;
	int prev;
};

class TREE
{
public:
	int numTop;
	TOP * tree;

public:
	TREE()
	{   
		cin >> numTop;
		tree = new TOP[numTop];
		tree[0].prev = -1;
		tree[0].timeToOwner = 0;
		//cout<<numTop<<endl;
	}

	void buildTree()
	{
		int out;
		int in;
	
		for(int i = 0; i < numTop - 1; ++i)
		{ 
			cin >> out;
			cin >> in;
			cin >> tree[in-1].timeToOwner;
			tree[in - 1].prev = out - 1;

			//cout<<out<<"   "<<in<<"   "<<tree[in-1].timeToOwner<<endl;//<<"  "<<tree[in - 1].prev + 1<<endl;
		}
	}

	void readCmd()
	{
		int from;
		int to;

		int numDist;
		long result;

		cin >> numDist;
		//cout << numDist<<endl;

		for( int i = 0; i < numDist; ++i)
		{
			cin >> from;
			cin >> to;

			//cout<<endl<<from<<"  "<<to<<endl;

			result = getWayTime(from - 1, to - 1);
		}
	}

	inline long getWayTime(int from, int to)
	{
		//cout << from << "  " << to;
		long result = 0;		
		long timeToNull = 0;
        int * chainF = new int[numTop];
		int * chainT = new int[numTop];
		int i;
		int j;

		chainF[0] = from;		
		//cout<<chainF[0]<<"  ";

		for(i = 1; i < numTop; ++i)
		{
			if(tree[chainF[i-1]].prev == -1)
			{
				break;
			}
			chainF[i] = tree[chainF[i-1]].prev;
			timeToNull += tree[chainF[i-1]].timeToOwner;			
			//cout<<"  "<<chainF[i]<<"  ";
		}

		//cout<<endl<<timeToNull<<endl;

		chainT[0] = to;		
		//cout<<chainT[0]<<"  ";

		for(j = 1; j < numTop; ++j)
		{
			if(tree[chainT[j-1]].prev == -1)
			{
				break;
			}
			chainT[j] = tree[chainT[j-1]].prev;
			timeToNull += tree[chainT[j-1]].timeToOwner;
			//cout<<"  "<<chainT[j]<<"  ";
		}
		//cout<<endl<<timeToNull<<endl;

		i--;
		j--;

		//cout<<endl<<chainF[i]<<"  "<<chainT[j]<<endl<<"///////////////////////////"<<endl;		

		while((chainT[j] == chainF[i]) && (i>=0)&&(j>=0))
		{	
			timeToNull -= tree[chainF[i]].timeToOwner;
			timeToNull -= tree[chainT[j]].timeToOwner;		

			i--;
			j--;
		} 		
		
		//cout << chainF[i] << "  " << chainT[j] << endl;
		cout<<timeToNull<< endl;
		return result;
	}

};

int main()
{
	TREE newTree;

	newTree.buildTree();
	newTree.readCmd();	
	
	//system("pause");
	return 0;
}