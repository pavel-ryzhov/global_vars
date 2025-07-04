#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

struct vertCross
{
	int left;
	int center;
	int right;
};

struct horCross
{
	int up;
	int center;
	int down;
};

vector < vector<int> > dt;

vertCross vertCrossing(vector< vector<char> > & digit)
{
	int height = digit.size();
	int width = digit[0].size();
	vertCross vertCrossingCount;
	
	int vertCenter = (int)(width / 2);
	int vertLeft = (int)(vertCenter - vertCenter / 1.1);
	int vertRight = (int)(vertCenter + vertCenter / 1.1);
 
	vertCrossingCount.left = 0;
	vertCrossingCount.center = 0;
	vertCrossingCount.right = 0;

	bool leftColorIsWhite = true;
	bool centerColorIsWhite = true;
	bool rightColorIsWhite = true;
	for (int i = 0; i < height; i++)
	{		
		if ((digit[i][vertLeft] != '.') && leftColorIsWhite) 
		{
			leftColorIsWhite = false;
			vertCrossingCount.left++;
		}
		else if (digit[i][vertLeft] == '.') leftColorIsWhite = true;


		if ((digit[i][vertCenter] != '.') && centerColorIsWhite) 
		{
			centerColorIsWhite = false;
			vertCrossingCount.center++;
		}
		else if (digit[i][vertCenter] == '.') centerColorIsWhite = true;


		if ((digit[i][vertRight] != '.') && rightColorIsWhite) 
		{
			rightColorIsWhite = false;
			vertCrossingCount.right++;
		}
		else if (digit[i][vertRight] == '.') rightColorIsWhite = true;
		
	}
	return vertCrossingCount;
}
horCross horCrossing(vector< vector<char> > & d)
{
	vector< vector<char> > digit;	

	// ??????? ??????????? ?????? ????? (?????? ????? ????? ????? ?????? ??????)
	bool lookingForWhiteStr = false;
	bool lookingForBlackStr = true;
	int upBorder = 0;
	int downBorder = 0;
	for (int i = 0; i < d.size() - 1; i++)
	{
		int numOfWhitePixels = 0;
		for (int j = 0; j < d[i].size(); j++)
		{
			if (d[i][j] == '.') numOfWhitePixels++;						
		}
		if (lookingForBlackStr && numOfWhitePixels != d[i].size())
		{
			upBorder = i; 
			lookingForWhiteStr = true;
			lookingForBlackStr = false;
		}
		else if (lookingForWhiteStr && numOfWhitePixels == d[i].size())
		{
			downBorder = i - 1; 
			lookingForWhiteStr = false;
			lookingForBlackStr = true;
		}
	}

	vector <char> str;
	for (int i = upBorder; i <= downBorder; i++)
	{
		for (int j = 0; j < d[0].size(); j++)
		{
			str.push_back(d[i][j]);
		}
		digit.push_back(str);
		str.clear();
	}

	int height = digit.size();
	int width = digit[0].size();
	horCross horCrossingCount;
	
	int horCenter = (int)(height / 2);
	int horUp = horCenter - horCenter / 2;
	int horDown = horCenter + horCenter / 2;
 
	horCrossingCount.up = 0;
	horCrossingCount.center = 0;
	horCrossingCount.down = 0;

	bool upColorIsWhite = true;
	bool centerColorIsWhite = true;
	bool downColorIsWhite = true;


	for (int i = 0; i < width; i++)
	{		
		if ((digit[horUp][i] != '.') && upColorIsWhite) 
		{
			upColorIsWhite = false;
			horCrossingCount.up++;
		}
		else if (digit[horUp][i] == '.') upColorIsWhite = true;


		if ((digit[horCenter][i] != '.') && centerColorIsWhite) 
		{
			centerColorIsWhite = false;
			horCrossingCount.center++;
		}
		else if (digit[horCenter][i] == '.') centerColorIsWhite = true;


		if ((digit[horDown][i] != '.') && downColorIsWhite) 
		{
			downColorIsWhite = false;
			horCrossingCount.down++;
		}
		else if (digit[horDown][i] == '.') downColorIsWhite = true;
		
	}
	return horCrossingCount;
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 30; i++) dt.push_back(vector<int>(6, 1));
	
	dt[0][0] = 1; dt[0][1] = 2; dt[0][2] = 1; dt[0][3] = 1; dt[0][4] = 2; dt[0][5] = 1;
	dt[1][0] = 1; dt[1][1] = 1; dt[1][2] = 1; dt[1][3] = 1; dt[1][4] = 1; dt[1][5] = 1;
	dt[2][0] = 2; dt[2][1] = 3; dt[2][2] = 2; dt[2][3] = 2; dt[2][4] = 1; dt[2][5] = 1; //
	dt[3][0] = 2; dt[3][1] = 3; dt[3][2] = 2; dt[3][3] = 2; dt[3][4] = 1; dt[3][5] = 2;
	dt[4][0] = 1; dt[4][1] = 2; dt[4][2] = 1; dt[4][3] = 2; dt[4][4] = 2; dt[4][5] = 1; //
	dt[5][0] = 2; dt[5][1] = 3; dt[5][2] = 2; dt[5][3] = 1; dt[5][4] = 1; dt[5][5] = 1; //
	dt[6][0] = 1; dt[6][1] = 3; dt[6][2] = 2; dt[6][3] = 1; dt[6][4] = 1; dt[6][5] = 1;
	dt[7][0] = 1; dt[7][1] = 2; dt[7][2] = 1; dt[7][3] = 1; dt[7][4] = 1; dt[7][5] = 1;
	dt[8][0] = 2; dt[8][1] = 3; dt[8][2] = 2; dt[8][3] = 2; dt[8][4] = 1; dt[8][5] = 2;
	dt[9][0] = 2; dt[9][1] = 3; dt[9][2] = 1; dt[9][3] = 2; dt[9][4] = 2; dt[9][5] = 1; //

	dt[10][0] = 1; dt[10][1] = 2; dt[10][2] = 1; dt[10][3] = 1; dt[10][4] = 2; dt[10][5] = 1;
	dt[11][0] = 1; dt[11][1] = 1; dt[11][2] = 1; dt[11][3] = 1; dt[11][4] = 1; dt[11][5] = 1;
	dt[12][0] = 1; dt[12][1] = 3; dt[12][2] = 2; dt[12][3] = 2; dt[12][4] = 1; dt[12][5] = 2; //
	dt[13][0] = 2; dt[13][1] = 3; dt[13][2] = 2; dt[13][3] = 2; dt[13][4] = 1; dt[13][5] = 2;
	dt[14][0] = 1; dt[14][1] = 3; dt[14][2] = 2; dt[14][3] = 2; dt[14][4] = 2; dt[14][5] = 1; //
	dt[15][0] = 1; dt[15][1] = 3; dt[15][2] = 1; dt[15][3] = 1; dt[15][4] = 2; dt[15][5] = 2; //
	dt[16][0] = 1; dt[16][1] = 3; dt[16][2] = 2; dt[16][3] = 1; dt[16][4] = 1; dt[16][5] = 1;
	dt[17][0] = 1; dt[17][1] = 2; dt[17][2] = 1; dt[17][3] = 2; dt[17][4] = 1; dt[17][5] = 1;
	dt[18][0] = 2; dt[18][1] = 3; dt[18][2] = 2; dt[18][3] = 2; dt[18][4] = 1; dt[18][5] = 2;
	dt[19][0] = 2; dt[19][1] = 3; dt[19][2] = 1; dt[19][3] = 1; dt[19][4] = 1; dt[19][5] = 1; //

	dt[20][0] = 1; dt[20][1] = 2; dt[20][2] = 1; dt[20][3] = 1; dt[20][4] = 2; dt[20][5] = 1;
	dt[21][0] = 1; dt[21][1] = 1; dt[21][2] = 1; dt[21][3] = 1; dt[21][4] = 1; dt[21][5] = 1;
	dt[22][0] = 2; dt[22][1] = 3; dt[22][2] = 2; dt[22][3] = 2; dt[22][4] = 1; dt[22][5] = 1;
	dt[23][0] = 2; dt[23][1] = 3; dt[23][2] = 2; dt[23][3] = 2; dt[23][4] = 1; dt[23][5] = 2;
	dt[24][0] = 1; dt[24][1] = 2; dt[24][2] = 1; dt[24][3] = 2; dt[24][4] = 2; dt[24][5] = 1;
	dt[25][0] = 1; dt[25][1] = 3; dt[25][2] = 1; dt[25][3] = 1; dt[25][4] = 1; dt[25][5] = 2; //
	dt[26][0] = 1; dt[26][1] = 3; dt[26][2] = 2; dt[26][3] = 1; dt[26][4] = 1; dt[26][5] = 1;
	dt[27][0] = 1; dt[27][1] = 2; dt[27][2] = 1; dt[27][3] = 1; dt[27][4] = 1; dt[27][5] = 1;
	dt[28][0] = 2; dt[28][1] = 3; dt[28][2] = 2; dt[28][3] = 2; dt[28][4] = 1; dt[28][5] = 2;
	dt[29][0] = 1; dt[29][1] = 3; dt[29][2] = 1; dt[29][3] = 2; dt[29][4] = 3; dt[29][5] = 2; //


	char value = 0;
	FILE *file;

	vector< vector<char> > arrayData, digit1, digit2, digit3;
	vector<char> str;

	
	/*file = fopen("C:\\taskATests\\005","r");
	while (!feof(file)) 
	{
		for(;;)
		{
			fscanf(file, "%c", &value);
			if (value == '.' || value == '%' || value == '#' || value == '@') str.push_back(value);
			else break;
		}
		arrayData.push_back(str);
		str.clear();
	}
	fclose(file);*/
	
	for(;;) 
	{
		for(;;)
		{
			scanf("%c", &value);
			if (value == '.' || value == '%' || value == '#' || value == '@') str.push_back(value);
			else break;
		}
		if (str.size() == 0) break;
		arrayData.push_back(str);
		str.clear();
	}	

	/*for (int i = 0; i < arrayData.size(); i++)
	{
		for (int j = 0; j < arrayData[i].size(); j++)
		{
			cout << arrayData[i][j];
		}
		cout << endl;
	}*/

	bool lookingForWhiteColumn = false;
	bool lookingForBlackColumn = true;
	vector <pair<int, int> > borders (3, pair<int, int>(0, 0));	
	int curDigit = 1;

	for (int j = 0; j < arrayData[0].size(); j++)
	{
		int numOfWhitePixels = 0;		
		for (int i = 0; i < arrayData.size() - 1; i++)
		{
			if (arrayData[i][j] == '.') numOfWhitePixels++;						
		}
		if (lookingForBlackColumn && numOfWhitePixels != arrayData.size()- 1)
		{
			borders[curDigit - 1].first = j; 
			lookingForWhiteColumn = true;
			lookingForBlackColumn = false;
		}
		else if (lookingForWhiteColumn && numOfWhitePixels == arrayData.size() - 1)
		{
			borders[curDigit - 1].second = j - 1; 
			lookingForWhiteColumn = false;
			lookingForBlackColumn = true;
			curDigit++;
			if (curDigit == 4) break;
		}
	}

	for (int i = 0; i <  arrayData.size() - 1; i++)
	{
		for (int j = borders[0].first; j <= borders[0].second; j++)
		{
			str.push_back(arrayData[i][j]);
		}
		digit1.push_back(str);
		str.clear();
	}

	for (int i = 0; i < arrayData.size() - 1; i++)
	{
		for (int j = borders[1].first; j <= borders[1].second; j++)
		{
			str.push_back(arrayData[i][j]);
		}
		digit2.push_back(str);
		str.clear();
	}

	for (int i = 0; i < arrayData.size() - 1; i++)
	{
		for (int j = borders[2].first; j <= borders[2].second; j++)
		{
			str.push_back(arrayData[i][j]);
		}
		digit3.push_back(str);
		str.clear();
	}

	/*
    for (int i = 0; i < digit1.size(); i++)
	{
		for (int j = 0; j < digit1[i].size(); j++)
		{
			cout << digit1[i][j];
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < digit2.size(); i++)
	{
		for (int j = 0; j < digit2[i].size(); j++)
		{
			cout << digit2[i][j];
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < digit3.size(); i++)
	{
		for (int j = 0; j < digit3[i].size(); j++)
		{
			cout << digit3[i][j];
		}
		cout << endl;
	}

	cout << endl;*/
	
	/*cout << vertCrossing(digit1).left << " " << vertCrossing(digit1).center << " " << vertCrossing(digit1).right << endl;
	cout << vertCrossing(digit2).left << " " << vertCrossing(digit2).center << " " << vertCrossing(digit2).right << endl;
	cout << vertCrossing(digit3).left << " " << vertCrossing(digit3).center << " " << vertCrossing(digit3).right << endl;
	cout << endl;
	cout << horCrossing(digit1).up << " " << horCrossing(digit1).center << " " << horCrossing(digit1).down << endl;
	cout << horCrossing(digit2).up << " " << horCrossing(digit2).center << " " << horCrossing(digit2).down << endl;
	cout << horCrossing(digit3).up << " " << horCrossing(digit3).center << " " << horCrossing(digit3).down << endl;
	*/

	vertCross vc1 = vertCrossing(digit1);
	vertCross vc2 = vertCrossing(digit2);
	vertCross vc3 = vertCrossing(digit3);

	horCross hc1 = horCrossing(digit1);
	horCross hc2 = horCrossing(digit2);
	horCross hc3 = horCrossing(digit3);
	
	vector<int> d1(6, 1);
	vector<int> d2(6, 1);
	vector<int> d3(6, 1);

	int first = 0, second = 0, third = 0;

	d1[0] = vc1.left; d1[1] = vc1.center; d1[2] = vc1.right; d1[3] = hc1.up; d1[4] = hc1.center; d1[5] = hc1.down; 
	for (int i = 0; i < 30; i++)
	{
		if (dt[i] == d1) { first = i; break; }
	}

	d2[0] = vc2.left; d2[1] = vc2.center; d2[2] = vc2.right; d2[3] = hc2.up; d2[4] = hc2.center; d2[5] = hc2.down; 
	for (int i = 0; i < 30; i++)
	{
		if (dt[i] == d2) { second = i; break; }
	}
	
	d3[0] = vc3.left; d3[1] = vc3.center; d3[2] = vc3.right; d3[3] = hc3.up; d3[4] = hc3.center; d3[5] = hc3.down; 
	for (int i = 0; i < 30; i++)
	{
		if (dt[i] == d3) { third = i; break; }
	}

	if (first > 9 && first < 20) first -= 10;
	else if (first > 19 && first < 30) first -= 20;

	if (second > 9 && second < 20) second -= 10;
	else if (second > 19 && second < 30) second -= 20;

	if (third > 9 && third < 20) third -= 10;
	else if (third > 19 && third < 30) third -= 20;

	cout << first*100 + second*10 + third << endl;
    //system("PAUSE");
    return 0;
}
