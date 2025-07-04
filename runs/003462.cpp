#include <cstdio>
#include <vector>
#include <string.h>
#include <string>
#include <cmath>
#include <memory.h>
#include <iostream>
using namespace std;

vector<vector<bool> > pic;
vector<double> res;
vector<vector<bool> > picture;

vector<double> GetStatistic(vector<vector<bool> > &);
vector<double> GetStatisticHalf(vector<vector<bool> > &);
vector<pair<int,int> > borders;

double prob[10][4] = 
{
{0.239 ,0.256 ,0.248 ,0.256},
{0.235 ,0.260 ,0.226 ,0.279},
{0.183 ,0.282 ,0.274 ,0.260},
{0.197 ,0.320 ,0.190 ,0.293},
{0.092 ,0.310 ,0.207 ,0.390},
{0.272 ,0.258 ,0.179 ,0.291},
{0.311 ,0.155 ,0.307 ,0.228},
{0.250 ,0.373 ,0.281 ,0.095},
{0.256 ,0.237 ,0.242 ,0.265},
{0.264 ,0.255 ,0.225 ,0.255}
};


void output()
{
	for(int i=0;i<pic.size();++i)
	{  
		for(int j=0;j<pic[i].size();++j)
			if (pic[i][j]) 
				cout << "@";
			else 
				cout << ".";
		cout << endl;
	}

}

vector<double> GetStatistic(vector<vector<bool> > & pic)
{
	int y = pic.size();
	int x = pic[0].size();
	int midX = x / 2;
	int midY = y / 2;
	int mas[4];
	memset(mas,0,sizeof(mas));
	for(int i=0;i<=midY;i++)
		for(int j=0;j<=midX;j++)
			if (pic[i][j] == 1)
				mas[0]++;
	for(int i=0;i<=midY;i++)
		for(int j=midX;j<x;j++)
			if (pic[i][j] == 1)
				mas[1]++;
	for(int i=midY;i<y;i++)
		for(int j=0;j<=midX;j++)
			if (pic[i][j] == 1)
				mas[2]++;
	for(int i=midY;i<y;i++)
		for(int j=midX;j<x;j++)
			if (pic[i][j] == 1)
				mas[3]++;
	int sum = mas[0]+mas[1]+mas[2]+mas[3];
	vector<double> res(4);
	for(int i=0;i<4;i++)
		res[i] = mas[i] * 1.0 / sum;
	return res;
}

vector<double> GetStatisticHalf()
{
	int y = pic.size();
	int x = pic[0].size();
	int midY = y / 2;
	int mas[2];
	memset(mas,0,sizeof(mas));
	for(int i=0;i<=midY;i++)
		for(int j=0;j<x;j++)
			if (pic[i][j] == 1)
				mas[0]++;
	for(int i=midY;i<y;i++)
		for(int j=0;j<x;j++)
			if (pic[i][j] == 1)
				mas[1]++;
	int sum = mas[0]+mas[1];
	vector<double> res(2);
	for(int i=0;i<2;i++)
		res[i] = mas[i] * 1.0 / sum;
	return res;
}

int amount = 0;
void dfs(int x,int y, vector<vector<bool> > & t)
{
	if (x < 0 || y < 0 || x >= t.size() || y >= t[0].size()) return;
	if (t[x][y] == 1) return;
	amount ++;
	t[x][y] = 1;
	dfs(x+1,y,t);
	dfs(x,y+1,t);
	dfs(x-1,y,t);
	dfs(x,y-1,t);
}
vector<int> GetHoles(vector<vector<bool> > & pic)
{
	vector<vector<bool> > tmp(pic.size() + 2, vector<bool>(pic[0].size()+2,0));
	for(int i=0;i<pic.size();i++)
		for(int j=0;j<pic[0].size();j++)
			tmp[i+1][j+1] = pic[i][j];

	dfs(0,0,tmp);
	vector<int> answer;
	for(int i=0;i<tmp.size();++i)
		for(int j=0;j<tmp[i].size();j++)
			if (tmp[i][j] == 0)
			{
				amount = 0;
				dfs(i,j,tmp);
				if (amount  >= 10) 
					answer.push_back(amount);
			}
			return answer;
}

int Recognize(vector<vector<bool> > & picture, int left, int right)
{
	vector<vector<bool> > pic;
	int upper, lower;
	for(int i=0;i<picture.size();++i)
	{
		bool intersect = false;
		for(int j=left;j<=right;++j)
			if (picture[i][j])
			{
				intersect = true;
				upper = i;
				break;
			}
		if (intersect) break;
	}
	for(int i=picture.size()-1;i>=0;--i)
	{
		bool intersect = false;
		for(int j=left;j<=right;++j)
			if (picture[i][j])
			{
				intersect = true;
				lower = i;
				break;
			}
		if (intersect) break;
	}

	pic.resize(lower-upper+1);
	for(int i=upper;i<=lower;i++)
	{	
		pic[i-upper].resize(right-left+1);
		for(int j=left;j<=right;j++)
			pic[i-upper][j-left] = picture[i][j];
	}

	string tmp;
	vector<int> holes = GetHoles(pic);
	vector<double> r = GetStatistic(pic);
	int pos =0;
	double best = 1000000;
	for(int i=0;i<=9;i++)
	{
		if ((i==1 || i==2 || i==3||i==5||i==7) && holes.size()> 0) continue;
		if (holes.size() > 1 && i != 8) continue;
		if ((i==9||i==0||i==6) && holes.size() == 0) continue;
		if (i==8 && holes.size() != 2) continue;
		double diff = 0;	
		for(int j=0;j<4;j++)
			diff += fabs(prob[i][j]-r[j]);

		if (diff < best)
		{
			best = diff;
			pos = i;
		}
	}
	return pos;
}

void ReadNumbers()
{
	string tmp;
	vector<bool> row;
	while(getline(cin,tmp))
	{
		row.clear();
		row.resize(tmp.length());
		for(int i=0;i<tmp.length();++i)
			if (tmp[i] == '@' || tmp[i] == '#')
				row[i] = true;
			else 
				row[i] = false;
		picture.push_back(row);
	}
}

void SeparateNumbers()
{
	enum State
	{
		in,
		out
	};
	State cur = out;
	int before = 0;
	for(int i=0;i<picture[0].size();i++) // scan with vertical line
	{
		bool intersect = false;
		for(int j=0;j<picture.size();j++)
			if (picture[j][i] == 1)
			{
				intersect = true;
				break;
			}
			if (!intersect)
			{
				if (cur == in)
				{
					borders.push_back(make_pair(before,i-1));
					cur = out;
				}
			}
			else
			{
				if (cur == out)
				{
					cur = in;
					before = i;
				}
			}
	}
}

void PrintLetters()
{
	for(int i=0;i<borders.size();i++)
	{
		int left = borders[i].first;
		int right = borders[i].second;
		for(int j=0;j<picture.size();j++)
		{	
			for(int k=left;k<=right;k++)
				if (picture[j][k] == 1)
					cout << "@";
				else cout << ".";
				cout << endl;
		}
		cout << endl;
	}

}
int main()
{
	ReadNumbers();
	SeparateNumbers();
	//PrintLetters();
	int res = 0;
	for(int i=0;i<borders.size();i++)
	{
		res = res * 10 + Recognize(picture, borders[i].first,borders[i].second);
	}
	cout << res;
	return 0;
} 
