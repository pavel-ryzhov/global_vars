#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

vector < string > dt;

string vertCrossing(vector< vector<char> > & digit)
{
	int height = digit.size();
	int width = digit[0].size();	

	vector<int> vert;
	vert.push_back(0);
	vert.push_back((int)(width / 4));	
	vert.push_back((int)(width / 2));
	vert.push_back((int)(width / 4) + (int)(width / 2));
	vert.push_back(width - 1);	

	vector<int> vertCrossingCount(5, 0);	
	vector<bool> colorIsWhite(5, true);
	
	for (int i = 0; i < height; i++)
	{		
		for (int j = 0; j < 5; j++)
		{
			if ((digit[i][vert[j]] != '.') && colorIsWhite[j]) 
			{
				colorIsWhite[j] = false;
				vertCrossingCount[j]++;
			}
			else if (digit[i][vert[j]] == '.') colorIsWhite[j] = true;
		}		
	}

	string cross;
	for (int j = 0; j < 5; j++)
	{
		cross += (char)(vertCrossingCount[j] + 48);
	}
	return cross;
}

string horCrossing(vector< vector<char> > & d)
{
	vector< vector<char> > digit;	

	// провдим определение высоты цифры (разные цифры могут иметь разную высоту)
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

	vector<int> hor;
	hor.push_back(0);
	hor.push_back((int)(height / 4));	
	hor.push_back((int)(height / 2));
	hor.push_back((int)(height / 4) + (int)(height / 2));
	hor.push_back(height - 1);	

	vector<int> horCrossingCount(5, 0);	
	vector<bool> colorIsWhite(5, true);

	for (int i = 0; i < width; i++)
	{		
		for (int j = 0; j < 5; j++)
		{
			if ((digit[hor[j]][i] != '.') && colorIsWhite[j]) 
			{
				colorIsWhite[j] = false;
				horCrossingCount[j]++;
			}
			else if (digit[hor[j]][i] == '.') colorIsWhite[j] = true;
		}		
	}
	
	string cross;
	for (int j = 0; j < 5; j++)
	{
		cross += (char)(horCrossingCount[j] + 48);
	}
	return cross;
}

int main(int argc, char *argv[])
{	
	dt.push_back("1222112221"); //0
	dt.push_back("1111111111"); //1
 	dt.push_back("1433212121"); //2
	dt.push_back("1233112121"); //3
	dt.push_back("1221111211"); //4
	dt.push_back("1233211111"); //5
	dt.push_back("1333111221"); //6
	dt.push_back("1122111111"); //7
	dt.push_back("2332212121"); //8
	dt.push_back("2333112211"); //9


	dt.push_back("1121112221"); //0
	dt.push_back("1211111111"); //1
 	dt.push_back("1232212111"); //2
	dt.push_back("1343212211"); //3
	dt.push_back("1231112211"); //4
	dt.push_back("1232111221"); //5
	dt.push_back("1113111221"); //6
	dt.push_back("1222112111"); //7
	dt.push_back("2334212121"); //8
	dt.push_back("1433112321"); //9

	dt.push_back("1112112221"); //0
	dt.push_back("2111111111"); //1
 	dt.push_back("1233212111"); //2
	dt.push_back("1233112121"); //3
	dt.push_back("1221111211"); //4
	dt.push_back("1333111121"); //5
	dt.push_back("1111111111"); //6
	dt.push_back("1222111111"); //7
	dt.push_back("2332212121"); //8
	dt.push_back("2333112211"); //9

	dt.push_back("1121112221"); //0
	dt.push_back("1211111111"); //1
 	dt.push_back("1233212111"); //2
	dt.push_back("1233112121"); //3
	dt.push_back("1221111211"); //4
	dt.push_back("1333111111"); //5
	dt.push_back("1111111111"); //6
	dt.push_back("1122112111"); //7
	dt.push_back("2332212121"); //8
	dt.push_back("2333112211"); //9

	dt.push_back("1121112221"); //0
	dt.push_back("1211111111"); //1
 	dt.push_back("1233212111"); //2
	dt.push_back("1233112121"); //3
	dt.push_back("1221111211"); //4
	dt.push_back("1233211211"); //5
	dt.push_back("1111111111"); //6
	dt.push_back("2222112111"); //7
	dt.push_back("2332212121"); //8
	dt.push_back("2333112211"); //9

	dt.push_back("1121112221"); //0
	dt.push_back("1211111111"); //1
 	dt.push_back("1233212111"); //2
	dt.push_back("1233112121"); //3
	dt.push_back("1221111211"); //4
	dt.push_back("1322112221"); //5
	dt.push_back("1111111111"); //6
	dt.push_back("2222112111"); //7
	dt.push_back("2332212121"); //8
	dt.push_back("2333112211"); //9
	
	char value = 0;
	FILE *file;

	vector< vector<char> > arrayData, digit1, digit2, digit3;
	vector<char> str;
	vector < vector< vector<char> > > digits;
	
	/*file = fopen("C:\\taskATests\\010","r");
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
			if (arrayData[i][j] == '.' || arrayData[i][j] == '%') numOfWhitePixels++;						
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

	int numOfDigits = 1;
	if (borders[1].first != 0 && borders[1].second != 0) numOfDigits = 2;
	if (borders[2].first != 0 && borders[2].second != 0) numOfDigits = 3;

	for (int k = 0; k < numOfDigits; k++)
	{
		for (int i = 0; i <  arrayData.size() - 1; i++)
		{
			for (int j = borders[k].first; j <= borders[k].second; j++)
			{
				str.push_back(arrayData[i][j]);
			}
			digit1.push_back(str);
			str.clear();
		}
		digits.push_back(digit1);
		digit1.clear();
	}

	/*for (int k = 0; k < numOfDigits; k++)
	{
		for (int i = 0; i < digits[k].size(); i++)
		{
			for (int j = 0; j < digits[k][i].size(); j++)
			{
				cout << digits[k][i][j];
			}
			cout << endl;
		}
		cout << endl;
	}*/
	
	vector <string> cross;


	for (int k = 0; k < numOfDigits; k++)
	{
		string a = vertCrossing(digits[k]);
		string b = horCrossing(digits[k]);
		a += b;
		cross.push_back(a);
	}

	vector <int> resDigits(numOfDigits, 0);
	for (int k = 0; k < numOfDigits; k++)
	{
		for (int i = 0; i < 60; i++)
		{
			if (dt[i].compare(cross[k]) == 0) { resDigits[k] = i; break; }
		}
	}
	
	for (int k = 0; k < numOfDigits; k++)
	{
		if (resDigits[k] > 9 && resDigits[k] < 20) resDigits[k] -= 10;
		else if (resDigits[k] > 19 && resDigits[k] < 30) resDigits[k] -= 20;
		else if (resDigits[k] > 29 && resDigits[k] < 40) resDigits[k] -= 30;
		else if (resDigits[k] > 39 && resDigits[k] < 50) resDigits[k] -= 40;
		else if (resDigits[k] > 49 && resDigits[k] < 60) resDigits[k] -= 50;
	}
	
	switch(numOfDigits)
	{
	case 1:
		cout << resDigits[0] << endl;
		break;
	case 2:
		cout << resDigits[0]*10 + resDigits[1] << endl;
		break;
	case 3:
		cout << resDigits[0]*100 + resDigits[1]*10 + resDigits[2] << endl;
		break;
	}
    
    //system("PAUSE");
    return 0;
}
