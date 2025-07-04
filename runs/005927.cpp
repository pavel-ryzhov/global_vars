#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n, nn, m, mm, index1, index2, index3; 
	// n is a number of nodes// m is a number of asking distances // nn is the counter for the cycle while // if input 1 2 4 so index1=1 index2=2 and index3=4

	//*********************************************************************
	// Create the Matrix tree
	//*********************************************************************
	cin >> n;
	vector < vector<int> > tree(n, vector<int>(n,40001)); // Matrix of n nodes
	//*********************************************************************
	// Complete the Matrix tree
	//*********************************************************************
	nn = n-1;
	while(nn!=0 && cin >> index1 >> index2 >> index3)
	{
		nn--;
		tree[index1-1][index2-1]=index3;
		tree[index2-1][index1-1]=index3;
	}

	//*********************************************************************
	// Diagonal = "0" for find a distance
	//*********************************************************************
	for(nn = n-1; nn!=-1; nn--)
	{
		tree[nn][nn]=0;
	}
	/*
	//*********************************************************************
	// Print the tree
	//*********************************************************************
	cout << "You entered: " << " the tree. \n";
	for(int ii=0; ii < n; ii++)
	{
		   for(int jj=0; jj < n; jj++)
			   cout << " " << tree[ii][jj];
		   cout << endl;
	}
	*/

	//*********************************************************************
	// Find a distance between two nodes
	//*********************************************************************
	for (int k=0; k<n; ++k)
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				if (tree[i][k] < 40001 && tree[k][j] < 40001)
					tree[i][j] = min(tree[i][j], tree[i][k] + tree[k][j]);
	/*
	//*********************************************************************
	// Print the new tree
	//*********************************************************************
	cout << "You  changed: " << " the new tree. \n";
	for(int ii=0; ii < n; ii++)
	{
		   for(int jj=0; jj < n; jj++)
			   cout << " " << tree[ii][jj];
		   cout << endl;
	}
	*/

	//*********************************************************************
	// Create the Matrix Mtree of distance and put distances in it 
	//*********************************************************************
	cin >> m;
	vector<int> Mtree(m); // Matrix of m nodes 
	mm = m;
	while(mm!=0 && cin >> index1 >> index2)
	{
		mm--;
		Mtree[mm]=tree[index1-1][index2-1];
	}

	//*********************************************************************
	// Print the Matrix Mtree 
	//*********************************************************************
	for (int i=m-1; i!=-1; i--)
		cout << Mtree[i] << endl;
}

//*********************************************************************
/*
	char c;
	do {
    c=getchar();
	} while (c != '!');
*/