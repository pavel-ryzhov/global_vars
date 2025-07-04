#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#define SCREEN_SIZE 100000

class Matrix{
public:
	std::string polygon_;

	Matrix(){}
	~Matrix(){}
};

class Scanner{
public:
	Scanner(){}
	~Scanner(){}

	int run();
};


int Scanner::run()
{
	Matrix ma;

	char buffer[SCREEN_SIZE];

	std::cin >> buffer;
	ma.polygon_ = buffer;

	return 0;
}

int main()
{
	Scanner scan;
	scan.run();

	return 0;
}
