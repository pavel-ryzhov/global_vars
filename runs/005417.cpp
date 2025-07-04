#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	vector<string> test;
	
	test.push_back("test 1");
	test.push_back("test 2");

	for (int i = 0; i < test.size(); i++)
		cout << test[i] << endl;
}