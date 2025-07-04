// исправлена проблема memset was not declarated...
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <assert.h>

using namespace std;

#define InputFile "./input.ini"
#define OutputFile "./output.ini"

#define NewLine "\n"

class SearchPass
{
	unsigned int* MassIndex;
	unsigned int* MassLength;
	int TBuf_Size,CBuf_Size;
	int Length;
	ifstream carrige;

public:

	SearchPass(void);
	~SearchPass(void);

	void Clear_Mass(void);
	int Input_Size(void);
	void Fill_Mass(int);
	void Parse_Search_Length(void);
	void TSearch_Length(int, int);
	void Output_Value(int);

};

SearchPass :: SearchPass()
{
	ofstream file_out; 
	file_out.open(OutputFile,ofstream::out | ofstream::trunc);
	file_out.close();

	Length = 0;

	carrige.open(InputFile, ifstream::in);
	if(!carrige)
	{
		printf("%s\n", "Error opening InputFile...");
		exit(1);
	}
	assert(!carrige.fail());  

	TBuf_Size = Input_Size();
	MassIndex = new unsigned int[TBuf_Size];
	MassLength = new unsigned int[TBuf_Size];
	Clear_Mass();
	Fill_Mass(TBuf_Size);
	CBuf_Size = Input_Size();
}

SearchPass :: ~SearchPass()
{
	carrige.close();
}

void SearchPass :: Clear_Mass()
{
	memset(MassIndex, 0, sizeof(MassIndex));
	memset(MassLength, 0, sizeof(MassLength));
}

int SearchPass :: Input_Size()
{
	int value;
	carrige>>value;
	return 
		value;
}

void SearchPass :: Fill_Mass(int Buf_Size)
{
	int parent,son,value;
	while(Buf_Size-1)
	{
		carrige>>parent>>son>>value;

		MassIndex[son-1] = parent-1;
		MassLength[son-1] = value;

		Buf_Size--;
	}
}

void SearchPass :: Parse_Search_Length()
{
	int first, second;
	while(/*!carrige.eof()*/CBuf_Size)
	{
		carrige>>first>>second;
		(first>=second)?TSearch_Length(second-1, first-1):TSearch_Length(first-1, second-1);
		Output_Value(Length);
		Length = 0;
		CBuf_Size--;
	}
}

void SearchPass :: TSearch_Length(int first, int second) // first < second
{
	if(second > first)
	{
		Length+= MassLength[second];
		TSearch_Length(first,MassIndex[second]);
	}
	else if(second < first)
		TSearch_Length(second,first);

	return;
}

void SearchPass :: Output_Value(int data)
{
	ofstream file_out;
	file_out.open(OutputFile,ofstream::app | ofstream::out);
	file_out<<data<<NewLine;
	file_out.close();
}

int main(int argc, char** argv)
{
	SearchPass sp;
	sp.Parse_Search_Length();
	printf("%s\n","Problem2 success...");
	return 0;
}
