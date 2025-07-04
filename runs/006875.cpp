#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <string.h> 
//#include <ncurses.h>
//#include <conio.h>
//#include <ctype.h>
using namespace std;

// Маски цифр


//Mask\0.txt
int num0[]={0,0,1,1,0,0,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,0,1,0,0,1,0,0,1,1,0};
//Mask\1.txt
int num1[]={0,0,0,1,1,0,0,1,1,1,0,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,1,1,1};
//Mask\2.txt
int num2[]={0,0,1,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1};
//Mask\3.txt
int num3[]={0,0,1,1,0,0,1,0,1,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1,0,0,1,1,0};
//Mask\4.txt
int num4[]={0,0,0,1,0,0,0,1,1,0,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,1,1,1,1,0,0,0,1,0,0,0,0,1,0};
//Mask\5.txt
int num5[]={0,1,1,1,1,0,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,1,0,1,0,0,1,0,0,1,1,0};
//Mask\6.txt
int num6[]={0,0,1,1,1,0,1,1,0,1,0,1,0,0,0,1,0,1,1,0,1,1,0,0,1,1,0,0,0,1,0,1,0,0,1,0,0,1,1,0};
//Mask\7.txt
int num7[]={0,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0};
//Mask\8.txt
int num8[]={0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0,1,1,0,0,0,0,1,1,1,0,1,0,0,1,1,1,0,0,1,0,0,1,1,0};
//Mask\9.txt
int num9[]={0,0,1,1,0,0,1,0,0,1,1,1,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,1,1,0};

//Mask\02.txt
int num02[]={0,0,0,0,0,0,1,1,0,1,0,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0};
//Mask\03.txt
int num03[]={0,0,1,1,0,0,1,0,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,1,0};
//Mask\04.txt
int num04[]={0,0,1,1,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,0,1,1,0};
//Mask\05.txt
int num05[]={0,0,0,1,0,0,0,1,0,1,0,1,1,0,1,0,1,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0,1,1,0,1,0,1,0};
//Mask\06.txt
int num06[]={0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,0,1,1,1,1,0,1,1,1,1};
//Mask\07.txt
int num07[]={0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,1,1,1,1};
int num08[]={0,0,1,1,0,0,1,0,0,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1};

//Mask\12.txt
int num12[]={0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1};
//Mask\13.txt
int num13[]={0,0,0,1,1,0,0,0,1,1,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
//Mask\14.txt
int num14[]={0,0,0,0,0,0,0,0,1,1,0,1,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0};
int num15[]={0,0,1,1,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,1};
int num16[]={0,0,0,1,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0};
int num17[]={0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1};

//Mask\32.txt
int num32[]={0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,1,1,1};
//Mask\33.txt
int num33[]={0,0,1,1,0,1,1,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0};
//Mask\34.txt
int num34[]={0,1,1,1,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1};
//Mask\35.txt
int num35[]={0,1,1,1,0,1,1,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0};
//Mask\36.txt
int num36[]={0,0,0,1,0,0,0,1,1,1,0,1,0,0,1,0,0,1,1,0,0,0,0,0,1,0,1,0,0,1,1,1,0,0,1,0,0,1,0,0};
int num37[]={0,0,0,1,0,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,1,0,1,1,0,0,0,1,1,1,0,0,1,0,0,1,1,0};
int num38[]={0,0,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0};
int num39[]={0,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1};
//Mask\52.txt
int num52[]={0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,1,1,0};
//Mask\53.txt
int num53[]={0,1,1,1,1,0,1,1,1,1,0,1,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,1,0,1,0,1,1};
//Mask\54.txt
int num54[]={0,1,1,1,1,0,1,0,0,1,0,1,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,1,1,1,0};
//Mask\55.txt
int num55[]={0,0,0,0,0,1,1,1,1,1,1,0,1,0,0,0,0,1,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0,0};
//Mask\56.txt
//int num56[]={0,0,1,1,1,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,1,1,1,1};
int num56[]={0,0,1,1,1,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1,0,1,1,1,1};
int num57[]={0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,1,0,0};

//Mask\62.txt
int num62[]={0,0,0,1,0,0,0,1,0,1,0,1,1,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0};
//Mask\63.txt
int num63[]={0,0,0,1,1,0,0,1,0,1,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,1,0};
//Mask\64.txt
int num64[]={0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,0,0,1,1,0};
//Mask\65.txt
int num65[]={0,0,0,1,0,0,0,1,1,1,0,1,0,0,0,0,1,0,0,0,1,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,1,1,0};
//Mask\66.txt
int num66[]={0,0,1,1,0,0,1,0,0,1,0,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,1,0,0,1,0,0,1,1,1};
//Mask\67.txt
int num67[]={0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,1,0,0,1,1,1,0,0,1,0,1,0,0,1,0,1,1,0,1};
//Mask\68.txt
int num68[]={0,0,1,1,1,0,1,0,0,1,0,1,0,0,0,1,0,1,1,1,1,0,1,0,1,1,0,0,0,0,0,1,0,0,1,0,0,1,1,0};
int num69[]={0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1};
//Mask\72.txt
int num72[]={0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0};
//Mask\73.txt
int num73[]={0,1,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,1,1,1,0,0,1,1,1,0};
//Mask\74.txt
int num74[]={0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,};
//Mask\75.txt
int num75[]={0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0};

//Mask\82.txt
int num82[]={0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,1,1,1,0,0,1,1,1,0,1,1,0,1,1,0,1,0,0,0,1,0};
//Mask\83.txt
int num83[]={0,0,1,1,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,1,0,1,1,0,1,1,0,0,1,0,1,0,0,0,0,0,1,1,1,1};
//Mask\84.txt
int num84[]={0,0,1,1,0,0,1,0,1,1,0,1,0,0,1,0,1,0,0,1,0,1,0,1,1,1,0,0,0,1,1,1,0,0,1,0,1,1,1,1};
//Mask\85.txt
int num85[]={0,0,1,1,1,0,1,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,1,0,1,0,0,0,1,0,0,0};
//Mask\86.txt
int num86[]={0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,1,0,0,0,1,0,1,0,0,1,0,0,1,1,0};


//Mask\87.txt
int num87[]={0,0,0,1,0,0,0,1,0,1,0,1,1,0,1,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,1,1,0,0,1,0,1,1,1,0};
//Mask\88.txt
int num88[]={0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0,1,1,0,1,0,1,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1};
//Mask\89.txt
int num89[]={0,0,0,0,0,0,0,0,1,1,0,1,0,0,1,0,1,1,1,0,0,0,1,1,1,0,1,0,0,1,1,1,0,0,1,0,1,1,0,0};
//Mask\8_10.txt
int num8_10[]={0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,1,1,1,1,1,0,0,0,1,1,0,0,1,0,1,1,0,1};
//Mask\92.txt
int num92[]={0,0,1,1,0,0,1,0,1,1,1,1,0,0,1,1,1,0,0,1,0,1,0,1,1,0,0,0,0,1,0,1,0,0,1,0,1,1,1,1};
//Mask\93.txt
int num93[]={0,0,0,0,0,0,1,1,1,1,0,1,0,0,1,0,1,0,0,1,0,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
//Mask\94.txt
int num94[]={0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0};
//Mask\95.txt
int num95[]={0,0,1,1,0,0,1,0,0,1,1,1,0,0,0,1,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0};
//Mask\96.txt
int num96[]={0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,1,1,0,1,1,1,0};
//Mask\42.txt
int num42[]={0,0,0,1,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1};
//Mask\43.txt
int num43[]={0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
//Mask\44.txt
int num44[]={0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,1,0,1,0,1,0,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1};
//Mask\45.txt
int num45[]={0,0,0,1,0,0,0,0,1,0,0,0,1,1,0,0,1,0,1,0,1,1,1,1,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1};
int num46[]={0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,1,0,1,0,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1};
//Mask\22.txt
int num22[]={0,1,1,1,0,1,1,0,1,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1};
//Mask\23.txt
int num23[]={0,0,0,1,0,0,0,1,1,1,0,1,0,0,1,1,0,0,0,1,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,1,1,1};
int num24[]={0,0,1,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,1,1,1};
int num25[]={0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0};
//Mask\-1.txt
int num_1[]={0,1,1,1,1,1,0,0,0,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0};
//Mask\97.txt
int num97[]={0,0,1,1,0,0,1,0,0,1,1,1,0,0,1,1,1,0,0,1,0,0,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,0,0,0};


int hashU(vector<int> v)
{
	int M=56;//48//52
	int h=0;
	int a=314515;
	int b=27183;
	for(vector<int>::iterator i=v.begin();i!=v.end();++i)
	{
		h=(a*h+*i)%M;
		a=a*b%(M-1);
	}
	return (h<0) ? (h+M) : h;
}



class Mask
{	
public:
	vector<int> number;
	int N;
	int hash;
	Mask(vector<int> n, int N):number(n),N(N) {}
};

class Masks
{
	vector< Mask > _num;
public:
	Masks()
	{
	
		
		_num.push_back( Mask( vector<int>(num0,num0+40), 0 ) ); // 0
		_num.push_back( Mask( vector<int>(num1,num1+40), 1 ) ); // 1
		_num.push_back( Mask( vector<int>(num2,num2+40), 2 ) ); // 2
		_num.push_back( Mask( vector<int>(num3,num3+40), 3 ) ); // 3
		_num.push_back( Mask( vector<int>(num4,num4+40), 4 ) ); // 4
		_num.push_back( Mask( vector<int>(num5,num5+40), 5 ) ); // 5
		_num.push_back( Mask( vector<int>(num6,num6+40), 6 ) ); // 6
		_num.push_back( Mask( vector<int>(num7,num7+40), 7 ) ); // 7
		_num.push_back( Mask( vector<int>(num8,num8+40), 8 ) ); // 8
		_num.push_back( Mask( vector<int>(num9,num9+40), 9 ) ); // 9

		_num.push_back( Mask( vector<int>(num02,num02+40),0) );// 10
		_num.push_back( Mask( vector<int>(num03,num03+40),0) );// 11
		_num.push_back( Mask( vector<int>(num04,num04+40),0) );// 12
		_num.push_back( Mask( vector<int>(num05,num05+40),0) );// 13

		_num.push_back( Mask( vector<int>(num12,num12+40),1) );// 14
		_num.push_back( Mask( vector<int>(num13,num13+40),1) );// 15
		_num.push_back( Mask( vector<int>(num14,num14+40),1) );// 16

		_num.push_back( Mask( vector<int>(num32,num32+40),3 ) );// 17
		_num.push_back( Mask( vector<int>(num33,num33+40),3 ) );// 18
		_num.push_back( Mask( vector<int>(num34,num34+40),3 ) );// 19

		_num.push_back( Mask( vector<int>(num52,num52+40),5) );// 20
		_num.push_back( Mask( vector<int>(num53,num53+40),5) );// 21
		_num.push_back( Mask( vector<int>(num54,num54+40),5) );// 22
		_num.push_back( Mask( vector<int>(num55,num55+40),5) );// 23
															
		_num.push_back( Mask( vector<int>(num62,num62+40),6) );// 24
		_num.push_back( Mask( vector<int>(num63,num63+40),6) );// 25
		_num.push_back( Mask( vector<int>(num64,num64+40),6) );// 26
		_num.push_back( Mask( vector<int>(num65,num65+40),6) );// 27
		_num.push_back( Mask( vector<int>(num66,num66+40),6) );// 28

		_num.push_back( Mask( vector<int>(num72,num72+40),7) );// 29
		_num.push_back( Mask( vector<int>(num73,num73+40),7) );// 30

		_num.push_back( Mask( vector<int>(num82,num82+40),8) );// 31
		_num.push_back( Mask( vector<int>(num83,num83+40),8) );// 32
		_num.push_back( Mask( vector<int>(num84,num84+40),8) );// 33 
		_num.push_back( Mask( vector<int>(num85,num85+40),8) );// 34
		_num.push_back( Mask( vector<int>(num86,num86+40),8) );// 35
		_num.push_back( Mask( vector<int>(num87,num87+40),8) );// 36
		_num.push_back( Mask( vector<int>(num88,num88+40),8) );// 37
		_num.push_back( Mask( vector<int>(num89,num89+40),8) );// 38
		_num.push_back( Mask( vector<int>(num8_10,num8_10+40),8) );// 39

		_num.push_back( Mask( vector<int>(num92,num92+40),9) );// 40
		_num.push_back( Mask( vector<int>(num93,num93+40),9) );// 42
		_num.push_back( Mask( vector<int>(num94,num94+40),9) );// 43
		_num.push_back( Mask( vector<int>(num95,num95+40),9) );// 44
		_num.push_back( Mask( vector<int>(num96,num96+40),9) );// 45

		_num.push_back( Mask( vector<int>(num42,num42+40),4 ) );// 45
		_num.push_back( Mask( vector<int>(num43,num43+40),4 ) ); // 46

		_num.push_back( Mask( vector<int>(num22,num22+40),2) );// 47

		_num.push_back( Mask( vector<int>(num_1,num_1+40),-1) );// 48

		_num.push_back( Mask( vector<int>(num06,num06+40),0) ); //49

		_num.push_back( Mask( vector<int>(num35,num35+40),3 ) );//50
		_num.push_back( Mask( vector<int>(num67,num67+40),6) );//51
		_num.push_back( Mask( vector<int>(num97,num97+40),9) );//52
		_num.push_back( Mask( vector<int>(num74,num74+40),7) );//53
		_num.push_back( Mask( vector<int>(num07,num07+40),0) );//54
		_num.push_back( Mask( vector<int>(num44,num44+40),4) );//55
		_num.push_back( Mask( vector<int>(num56,num56+40),5) );// 56

		_num.push_back( Mask( vector<int>(num68,num68+40),6) );// 57
		_num.push_back( Mask( vector<int>(num36,num36+40),3) );// 58
		_num.push_back( Mask( vector<int>(num45,num45+40),4) ); // 59

		_num.push_back( Mask( vector<int>(num57,num57+40),5) );// 60
		_num.push_back( Mask( vector<int>(num15,num15+40),1) );// 61

		_num.push_back( Mask( vector<int>(num23,num23+40),2) );// 62
		_num.push_back( Mask( vector<int>(num37,num37+40),3) );// 63
		_num.push_back( Mask( vector<int>(num46,num46+40),4) );// 64
		_num.push_back( Mask( vector<int>(num75,num75+40),7) );// 65
		_num.push_back( Mask( vector<int>(num38,num38+40),3) );// 66
		_num.push_back( Mask( vector<int>(num16,num16+40),1) );// 67
		_num.push_back( Mask( vector<int>(num24,num24+40),2) );// 68
		_num.push_back( Mask( vector<int>(num17,num17+40),1) );// 69
		_num.push_back( Mask( vector<int>(num25,num25+40),2) );// 70
		_num.push_back( Mask( vector<int>(num39,num39+40),3) );// 71
		_num.push_back( Mask( vector<int>(num69,num69+40),6) );// 72
		_num.push_back( Mask( vector<int>(num08,num08+40),0) );// 72

		for(vector<Mask>::iterator i=_num.begin();i!=_num.end();++i)
		{
			(*i).hash=hashU((*i).number);
		}

	
	}
	int Size() { return _num.size(); }
	int compare2(vector<int> v,bool show=false)
	{
		vector<int> num_hash_coin;
		double max=0; // Коэффициент похожести
		vector<Mask>::iterator s;// Для показа найденной маски
		Mask* S;
		int find_number=-1;
		int hash_number=hashU(v);
		//cout<<"hash:"<<hash_number<<endl;

		int nn=0;
		for(vector< Mask >::iterator j = _num.begin(); j!= _num.end(); ++j,++nn )	
		{
			if(hash_number== (*j).hash ) num_hash_coin.push_back( nn );
		}

		// Берем каждую маску
		//for(vector< Mask >::iterator j = _num.begin(); j!= _num.end(); ++j )	
		for( vector<int>::iterator j = num_hash_coin.begin();j != num_hash_coin.end(); ++j )
		{
			//vector< int >::iterator i = begin;
			vector< int >::iterator i = v.begin();
			int coincidence = 0;	// Количество совпадений 
			// Сравниваем
			for(vector<int>::iterator n = _num[*j].number.begin();n != _num[*j].number.end(); ++n, i++)
			{
				if(( ((*i) > 0) && ( (*n) == 1 ) )|| ( ( (*i)==0 ) && ( (*n)==0) )  )
						coincidence++;
			}
			double a=(double)coincidence/(double)40;
			if( max<a )// Сохраняем максимальное совпадение
			{
				max=a;
				S = &_num[*j];
			}
			if(show) cout<<_num[*j].N<<" "<<"s:"<<coincidence<<" ns:"<<(66-coincidence)<<" a:"<<a<<endl;
		}
		if(show) 
		{
			cout<<endl;
			cout<<(*S).N<<endl;
		}

		if(show)
		{
			cout<<"num_hash_coin"<<endl;
			for(vector<int>::iterator i=num_hash_coin.begin();i!=num_hash_coin.end();++i)
				cout<<*i<<"("<<_num[*i].N<<") ";
			cout<<endl<<endl;
		}
		
		return (*S).N;
	}


	
};


//Исходное изображение
class SourceImage
{
	int H;	// Высота
	int W;	// Ширина
	int m,n;
	int km,kn;
	int cur;
	vector< vector<int> > img;
	vector<int> find_outline;
	ifstream file;
	ofstream out_file;
public:
	//SourceImage(){}
	//SourceImage(char *file_name)
	SourceImage()
	{	

		m=0;
		n=0;
		W=0;
		H=0;
		vector<int> p;
		char lastch=0;
		int ch;
		//while( (ch!='@') || (ch!='#') || (ch!='.') || (ch!='%')  )
		
			int j=1;
	
			//for (int i = 0; ((ch = getchar ()) != EOF); i++)
			while(j!=0)
			{
				//ch = getch();
				ch=cin.get();
				
				if( (ch=='@') || (ch=='#') || (ch=='.') || (ch=='%') ) 
				{
					//cout<<"|"<<ch<<"|";
					switch(ch)
					{
					case 46:
						p.push_back( 0 );
						break;
					case '%':
						p.push_back( '%' );
						break;
					case '@':
						p.push_back( 1 );
						break;
					case '#':
						p.push_back( 1 );
						break;
					default:

						break;
					}
				}
				else
				{
				  //cout<<"!"<<ch<<"!"<<endl;
					if( ch==10 ) 
					{
						//cout<<"\n";
						img.push_back(p);
						p.erase(p.begin(),p.end());
					}
					else
					{
						j=1;
						break;
					}
				}
			}
			//cout<<"Input ok"<<endl;

		H=img.size();
		W=img[0].size();

		m=H;
		n=W;
		km=0;
		kn=0;
		cur=1;
		file.close();
		int kh;
		int kw;
		int mh;
		int mw;

		// Немного корректируем исходное изображение (Убираем лишнее)
		for (int i=0;i<m;i++)		
		{
			mh=i-1;
			mw=i+1;

			for(int j=0;j<n;j++)
			{	
				kh = j-1;
				kw = j+1;	
				if( (kh > 0) && (kw < n) )
					if( (mh>0) && (mw<m) )
					{
						
						if( (img[i][j]==1) && ((img[i][kh]==0)) && (img[i][kw]==0) 
							&& (img[mh][j]==0) && (img[mh][kh]==0) && (img[mh][kw]==0) )
						{
							img[i][j]=0;
						}

						if( (img[i][j]==1) && ((img[i][kh]==0)) && (img[i][kw]==0) 
							&& (img[mw][j]==0) && (img[mw][kh]==0) && (img[mw][kw]==0) )
						{
							img[i][j]=0;
						}
					}	

					if( (kh > 0) && (kw < n) )
					{
						if( (img[i][j]=='%') && (img[i][j+1]==1)) 
						{	
							img[i][j]=0;
						}

						if( (img[i][j]=='1') && (img[i][j+1]=='%')) 
						{	
							img[i][j+1]=0;
						}
						if( (img[i][kw]==0) && (img[i][j]==1) && (img[i][kh]==0) )
						{
							img[i][kw]=1;
						}
					}
						
					if( (img[i][j]=='%') )
						{
							img[i][j]=1;
						}
					if( (mh>0) && (mw<m) )
						if((img[mh][j]==0) && (img[mw][j]==0) && (img[i][j]==1) ) 
						{
							img[mh][j]=1;
							img[mw][j]=1;
						}	
			}		
		}
		//ShowImg();
	}

	void ShowFind()
	{
		cout<<"Size:"<<find_outline.size()<<endl;
		for(vector< int >::iterator o = find_outline.begin(); o!= find_outline.end();++o )
		{
			cout<<*o<<" ";
		}
	}
	// Количество найденных объектов
	int Count()
	{
		return find_outline.size();
	}
	// Какой цифрой помечен данный объект
	int GetNumFind(int n)
	{
		return find_outline.at(n);
	}

	//int Cur(){return cur;}

	// Подсчет объектов
	void CountNumbers()
	{
		if(img.size()==0) return;
		cur=1;		//    _
		int A=0;	//  _|C|
		int B=0;	// |B A|
		int C=0;	// 
		for (int i=0;i<m;i++)
		{
			for(int j=0;j<n;j++)
			{			
				if( (img[i][j]==10) || (img[i][j]==13) ) continue;
				kn = j-1;
				if(kn<=0)
				{
					kn=1;
					B = 0;					
				}
				else
					B=img[i][kn];	
				km=i-1;
				if(km<=0)
				{
					km=1;
					C=0;
				}
				else
					C=img[km][j];
				A=img[i][j];
				if(A==0){} // Если в текущем пикселе пусто - то ничего не делаем
				else if( (B==0) && (C==0))//когда помечен только элемент A — в этом случае мы говорим о создании нового объекта
				{
					cur++;
					img[i][j]=cur;
				}
				else if( (B!=0) && (C==0) )//когда помечен элемент элемент B — в этом случае мы помечаем текущий пиксель A меткой, расположенной в B.
				{
					img[i][j]=B;
				}
				else if( (B==0) && (C!=0) )//когда помечен элемент элемент С — в этом случае мы помечаем текущий пиксель A меткой, расположенной в С.
				{
					img[i][j]=C;
				}
				else if((B!=0) && (C!=0) )
				{
					if(B==C)
						img[i][j]=C;
					else
					{
						img[i][j]=B;							
						//int ccc=0;
						int k=i+1;
						if(k<=m)					

						for(int o=0;o<k;o++)
						{
							for (int p=0;p<n;p++)
							{
								if( img[o][p]==B ) img[o][p]=C;
								//ccc++;
							}
						}
					}
				}
			}
		}
		int i=H/2;
		for (vector<int>::iterator j=img[i].begin(); j!=img[i].end(); ++j )
		{
			if(*j!=0)
			{
				if( find_outline.size() == 0 ) find_outline.push_back(*j);
				vector<int>::iterator d =find(find_outline.begin(),find_outline.end(),*j);
				if(d==find_outline.end())
				{
					find_outline.push_back(*j);
				}					
			}		
		}
	}

	void ShowImg()
	{		
		//out_file.open("out.txt");
		for(vector<vector<int> >::iterator i = img.begin(); i!= img.end(); ++i )
		{
			for (vector<int>::iterator j=(*i).begin(); j!=(*i).end(); ++j )
			{
				//if(*j==0) out_file<<".";
				//else out_file<<*j;
				cout<<*j;				
			}
			//out_file<<"\n";
			cout<<"\n";	
		}
	}

/*
// Рекурсивный
	void Labelling()
	{
		int L=1;
		for(int y=0;y<W; ++y)
			for(int x=0;x<H;++x)
				Fill(img,labels,x,y,L++);
	}
	void Fill(vector< vector<int> > &img, vector< vector<int> > labels,int x,int y,int L)
	{
		if( (labels[x][y]==0) && (img[x][y]==1) )
		{
			labels[x][y] = L;
			if(x>0)
				Fill(img,labels,x-1,y,L);
			if(x<W-1) 
				Fill(img,labels,x+1,y,L);
			if(y>0)
				Fill(img,labels,x,y-1,L);
			if(y<H-1)
				Fill(img,labels,x,y+1,L);
		}
	}
*/
	// Берем координаты верхнего левого и нижнего правого
	// num номер объекта
	void GetNum(int num, int &x1,int &y1,int &x2,int &y2)
	{
		x1=x2=y1=y2=0;
		int mx1=0,mx2=0,my1=0,my2=0;
		bool first=true;
		for (int i=0;i<H;i++)		
		{
			for(int j=0;j<W;j++)
			{
				if(img[i][j]==num)
				{
					if(first) 
					{
						x1=j;
						x2=j;
						y1=i;
						y2=i;
						first=false;
						continue;
					}					
					if(x1>j) x1=j;
					if(j>x2) x2=j;
					if(y1>i) y1=i;
					if(i>y2) y2=i;
				}				
			}
		}
	}
	// уменьшаем изображение до new_size_y и new_size_x
	void DeInterpolation3( vector< vector<int> > im, vector< int > &map ,
		int new_size_y,int new_size_x)
	{
		int y=0;
		int x=0;

		for(int i=0;i<new_size_y*new_size_x;i++)
		{
			map.push_back(0);
		}

		for(int i=0;i<new_size_y;i++)
		{
			double yz = (double)im.size()/(double)new_size_y;
			y = i*(yz);
			int ym=y-1;
			int yb=y+1;
			for (int j=0;j<new_size_x;j++)
			{			
				double xz=(double)im[j].size()/(double)new_size_x;
				x = j*(xz);
				int xm=x-1;
				int xb=x+1;
				map[(i*new_size_x)+j] = im[y][x];
			}
		}
	}
	// Копируем объект под номером n в mn
	void GetMasNum(int n,vector< int > &mn)
	{
		int x1=0,y1=0,x2=0,y2=0;
		GetNum(GetNumFind(n),x1,y1,x2,y2);

		x2+=1;
		y2+=3;
		
		int y=y2-y1;
		int x=x2-x1;

		vector< vector<int> > num;
		// Копируем
		for(int i=y1,i2=0;i<y2;i++,i2++)
		{
			num.push_back( vector<int>() );
			for (int j=x1;j<x2;j++)
			{
				if(img[i][j]>0)
					num[i2].push_back(1);
				else 
					num[i2].push_back(0);
			}
		}
		//уменьшаем
		DeInterpolation3(num,mn,8,5);
	}
};


class FineReader
{
public:
	Masks mask;
	bool show;
public:
	FineReader(bool s=false):show(s){}
	// nu сохраняем распознанные цифры
	//void Recognize3(char *file_name,vector<int> &nu)
	void Recognize3(vector<int> &nu)
	{
		//SourceImage ol(file_name);// Исходный фаил с цифрами
		SourceImage ol;
		ol.CountNumbers();		  // Подсчет объектов
		for(int n=0; n<ol.Count(); n++)// Повторяем для каждого найденного объекта
		{
			vector<int> img; // для найденного объекта
			// копируем объект в img
			ol.GetMasNum(n,img);
			int find_number=-1;
			find_number = mask.compare2(img,show);
			nu.push_back(find_number);
		}
	}
};

void Do3(char *name,bool show=false)
{
	clock_t t0 = clock();

	char suf[]={".a"};
	char *newname=new char[strlen(name)+strlen(suf)+2];
	strcpy(newname,name);
	strcat(newname,suf);
	cout<<newname<<endl;

	ifstream proverka(newname,ios::in);
	FineReader fr(show);
	vector<int> numbers;
	//fr.Recognize3(name,numbers);
	int m=1;
	int sum=0;

	for(vector<int>::reverse_iterator i=numbers.rbegin();i!=numbers.rend();i++,m*=10)
	{
		if(*i!=-1)
		sum+=*i*m;
	}
	int p;

	proverka>>p;
	cout<<sum<<endl;
	cout<<p<<endl;
	if(p==sum) cout<<"OK"<<endl;
	else cout<<"*********************************  NOT"<<endl;


	clock_t t1 = clock();
	cout << "time: " << (double)(t1 - t0) / CLOCKS_PER_SEC << endl;
	delete newname;
	//if(show) getchar();
	cout<<endl;
}

int main(int argc, char *argv[])
{
	FineReader fr;
	vector<int> numbers;
	fr.Recognize3(numbers);
	int m=1;
	int sum=0;

	for(vector<int>::reverse_iterator i=numbers.rbegin();i!=numbers.rend();i++)
	{
		if(*i!=-1)
		{
			sum+=*i*m;
			m*=10;
		}
	}
	cout<<sum<<endl;



//	Do2("check\\017");

//	Do3("check\\001",true);
//	Do3("check\\002");

	/*	clock_t t0 = clock();
		Do3("check\\001");
		Do3("check\\002");

		Do3("check\\003");
		Do3("check\\004");

		Do3("check\\005");

		Do3("check\\006");

		Do3("check\\007");
		Do3("check\\008");
		Do3("check\\009");

		Do3("check\\010");
		Do3("check\\011");
		Do3("check\\012");
		Do3("check\\013");
		Do3("check\\014");
		Do3("check\\015");
		Do3("check\\016");
		Do3("check\\018");
		Do3("check\\019");
		clock_t t1 = clock();
		cout << "final time: " << (double)(t1 - t0) / CLOCKS_PER_SEC << endl;
		cout<<endl;
		*/

	
	return 0;

}