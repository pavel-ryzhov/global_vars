#include <cstdio>
#include <vector>
#include <string.h>
#include <string>
#include <cmath>
#include <memory.h>
#include <iostream>
using namespace std;

vector<vector<int> > pic;
vector<double> res;
vector<vector<int> > picture;

vector<double> GetStatistic(vector<vector<int> > &);
vector<double> GetStatisticHalf(vector<vector<int> > &);
vector<pair<int,int> > borders;

double prob[10][4] = 
{
{0.239 ,0.256 ,0.248 ,0.256},
{0.114 ,0.309 ,0.070 ,0.307},
{0.183 ,0.282 ,0.274 ,0.260},
{0.197 ,0.320 ,0.190 ,0.293},
{0.110 ,0.313 ,0.203 ,0.374},
{0.285 ,0.278 ,0.170 ,0.266},
{0.311 ,0.155 ,0.307 ,0.228},
{0.250 ,0.373 ,0.281 ,0.095},
{0.259 ,0.239 ,0.233 ,0.269},
{0.244 ,0.236 ,0.248 ,0.272}
};

const int dSize = 42;
const int dWidth = 37;
vector<double> GetDistribution(vector<vector<int> > pic)
{
	vector<double> dist;
	dist.resize(pic[0].size());
	double sum = 0;
	for(int i=0;i<pic[0].size();i++) // for all vertial lines
	{
		double tmp = 0;
		for(int j=0;j<pic.size();j++)
			if (pic[j][i]) tmp ++;
		sum += tmp;
		dist[i] = tmp;
	}
	for(int i=0;i<dist.size();i++)
	{
		dist[i] = dist[i] * 100 / sum;
	}
	return dist;
}

double distrib[dSize][dWidth] = 
{
{8.25688, 11.92661, 15.59633, 7.33945, 2.75229, 1.83486, 1.83486, 1.83486, 3.66972, 7.33945, 15.59633, 13.76147, 8.25688},
{0.49505, 0.99010, 0.99010, 1.48515, 1.98020, 1.98020, 2.47525, 13.86139, 13.86139, 13.86139, 14.35644, 14.35644, 14.35644, 0.99010, 0.99010, 0.99010, 0.99010, 0.49505, 0.49505},
{1.23457, 1.23457, 18.51852, 19.13580, 19.75309, 19.75309, 19.75309, 0.61728},
{0.00000, 1.20482, 2.40964, 1.80723, 1.80723, 1.80723, 3.61446, 19.27711, 19.27711, 19.87952, 19.87952, 4.21687, 2.40964, 1.20482, 0.60241, 0.60241},
{0.00000, 1.76991, 1.47493, 1.76991, 1.47493, 1.76991, 1.76991, 1.76991, 1.76991, 2.06490, 2.06490, 2.06490, 12.68437, 13.27434, 13.56932, 13.56932, 13.56932, 13.56932},
{0.28302, 0.84906, 1.32075, 1.69811, 1.88679, 2.16981, 2.35849, 2.64151, 2.73585, 2.92453, 3.01887, 3.11321, 3.20755, 3.11321, 2.92453, 2.92453, 3.01887, 2.92453, 2.92453, 2.92453, 2.92453, 3.01887, 3.11321, 3.20755, 3.39623, 3.67925, 3.58491, 3.49057, 3.39623, 3.30189, 3.20755, 3.01887, 2.92453, 2.73585, 2.35849, 2.07547, 1.60377},
{0.85470, 2.84900, 4.27350, 5.41311, 6.26781, 5.69801, 4.84330, 4.27350, 3.98860, 3.98860, 3.70370, 3.70370, 3.41880, 3.41880, 3.70370, 3.98860, 4.27350, 4.55840, 5.69801, 6.83761, 5.98291, 4.84330, 3.41880},
{1.48148, 5.92593, 8.14815, 7.40741, 6.66667, 5.92593, 4.44444, 4.44444, 4.44444, 4.44444, 4.44444, 6.66667, 7.40741, 9.62963, 9.62963, 8.88889},
{1.12994, 3.38983, 5.08475, 5.64972, 4.51977, 6.21469, 5.64972, 6.77966, 9.60452, 9.03955, 7.90960, 7.34463, 8.47458, 7.34463, 6.21469, 2.82486, 2.82486},
{4.09357, 7.01754, 8.18713, 7.60234, 5.84795, 7.01754, 6.43275, 6.43275, 6.43275, 7.01754, 5.84795, 8.77193, 8.77193, 7.01754, 3.50877},
{0.89552, 2.38806, 3.88060, 5.37313, 5.37313, 3.88060, 2.98507, 2.38806, 2.08955, 2.08955, 2.68657, 2.68657, 2.68657, 2.68657, 3.58209, 4.17910, 5.37313, 7.16418, 9.25373, 10.44776, 8.95522, 6.26866, 2.68657},
{3.70370, 7.40741, 7.40741, 7.40741, 9.25926, 12.96296, 20.37037, 22.22222, 9.25926},
{1.52672, 3.05344, 6.10687, 7.63359, 7.63359, 3.05344, 3.81679, 3.81679, 3.81679, 3.81679, 3.81679, 4.58015, 7.63359, 12.97710, 12.21374, 9.92366, 4.58015, 0.00000},
{0.97087, 2.91262, 1.94175, 2.91262, 1.94175, 2.91262, 1.94175, 3.88350, 3.88350, 2.91262, 21.35922, 22.33010, 23.30097, 1.94175, 1.94175, 1.94175, 0.97087},
{2.28571, 2.85714, 2.85714, 3.42857, 3.42857, 4.57143, 5.14286, 4.57143, 4.57143, 5.14286, 9.71429, 9.71429, 10.28571, 1.71429, 11.42857, 10.85714, 2.28571, 2.28571, 2.85714},
{2.17391, 4.34783, 3.26087, 4.34783, 3.26087, 4.34783, 4.34783, 3.26087, 21.73913, 22.82609, 22.82609, 1.08696, 1.08696, 1.08696},
{1.25899, 1.43885, 1.79856, 1.97842, 2.15827, 2.51799, 2.51799, 2.33813, 2.51799, 2.51799, 2.33813, 2.33813, 2.51799, 2.33813, 2.33813, 2.51799, 2.33813, 2.33813, 2.51799, 2.51799, 7.91367, 8.09353, 8.09353, 8.09353, 8.09353, 8.09353, 1.07914, 1.07914, 1.07914, 1.07914, 1.07914, 1.07914},
{3.79747, 15.18987, 8.86076, 6.32911, 6.32911, 5.06329, 5.06329, 5.06329, 5.06329, 6.32911, 6.32911, 7.59494, 12.65823, 6.32911},
{0.53191, 1.86170, 3.98936, 5.05319, 5.05319, 3.19149, 3.19149, 2.92553, 2.92553, 3.19149, 3.19149, 3.45745, 3.45745, 3.72340, 3.98936, 3.98936, 4.25532, 4.78723, 5.58511, 6.91489, 6.64894, 6.11702, 5.58511, 4.25532, 2.12766},
{1.85185, 3.70370, 4.62963, 4.62963, 6.48148, 9.25926, 7.40741, 4.62963, 3.70370, 4.62963, 3.70370, 4.62963, 5.55556, 10.18519, 11.11111, 8.33333, 5.55556, 0.00000},
{1.16732, 2.33463, 1.55642, 1.55642, 1.94553, 3.11284, 4.66926, 5.83658, 5.83658, 4.28016, 3.11284, 3.89105, 5.05837, 6.22568, 6.22568, 5.44747, 3.89105, 3.11284, 3.50195, 3.11284, 3.50195, 3.89105, 4.28016, 6.22568, 4.28016, 1.94553},
{1.06383, 4.25532, 6.38298, 8.51064, 8.51064, 8.51064, 8.51064, 7.44681, 8.51064, 9.57447, 13.82979, 11.70213, 3.19149},
{9.58904, 15.06849, 8.21918, 5.47945, 5.47945, 4.10959, 4.10959, 5.47945, 4.10959, 6.84932, 4.10959, 9.58904, 10.95890, 6.84932},
{0.00000, 4.16667, 5.83333, 6.66667, 7.91667, 8.33333, 9.16667, 9.58333, 10.00000, 10.41667, 10.41667, 0.83333, 1.25000, 1.25000, 1.66667, 1.66667, 1.66667, 2.50000, 2.08333, 1.66667, 2.91667},
{0.00000, 2.75482, 3.58127, 4.40771, 5.23416, 5.78512, 6.33609, 6.61157, 6.88705, 6.88705, 5.50964, 4.40771, 3.58127, 3.58127, 4.95868, 4.95868, 4.68320, 4.68320, 4.13223, 3.85675, 3.30579, 2.47934, 1.37741},
{2.91262, 2.91262, 2.91262, 6.79612, 10.67961, 12.62136, 10.67961, 8.73786, 8.73786, 7.76699, 6.79612, 5.82524, 5.82524, 3.88350, 2.91262},
{1.60000, 1.60000, 1.60000, 1.60000, 1.60000, 4.00000, 6.00000, 7.60000, 8.80000, 8.00000, 6.40000, 6.40000, 5.60000, 5.60000, 4.80000, 4.80000, 4.80000, 4.40000, 4.00000, 3.60000, 2.80000, 2.40000, 2.00000},
{5.00000, 5.00000, 3.33333, 3.33333, 8.33333, 13.33333, 13.33333, 10.00000, 8.33333, 8.33333, 6.66667, 6.66667, 5.00000, 3.33333},
{0.00000, 3.57143, 9.82143, 12.50000, 14.28571, 16.07143, 16.96429, 8.03571, 6.25000, 3.57143, 3.57143, 5.35714},
{1.81818, 3.03030, 3.03030, 4.24242, 5.45455, 7.27273, 8.48485, 8.48485, 9.09091, 9.69697, 9.09091, 7.87879, 6.66667, 4.84848, 4.84848, 3.63636, 1.81818, 0.60606},
{1.51515, 4.54545, 4.54545, 4.54545, 4.54545, 9.09091, 12.12121, 12.12121, 12.12121, 12.12121, 12.12121, 7.57576, 3.03030},
{0.00000, 4.24528, 3.30189, 2.35849, 1.88679, 1.88679, 1.88679, 5.66038, 7.07547, 8.49057, 9.43396, 10.37736, 7.07547, 5.66038, 4.71698, 4.24528, 3.77358, 3.30189, 3.77358, 3.30189, 2.83019, 2.35849, 1.41509, 0.94340},
{0.00000, 2.27273, 9.09091, 9.84848, 8.33333, 6.06061, 5.30303, 3.78788, 3.78788, 4.54545, 3.78788, 3.78788, 5.30303, 6.81818, 10.60606, 10.60606, 6.06061, 0.00000},
{1.48883, 2.48139, 3.97022, 3.97022, 4.71464, 3.47395, 2.72953, 2.97767, 2.48139, 2.23325, 1.98511, 3.47395, 4.21836, 4.21836, 2.97767, 3.22581, 2.97767, 2.72953, 3.47395, 3.72208, 4.96278, 4.21836, 3.72208, 2.23325, 2.97767, 2.72953, 3.72208, 3.72208, 3.47395, 2.72953, 1.98511},
{2.85714, 8.57143, 10.95238, 9.52381, 6.19048, 5.23810, 4.28571, 4.28571, 4.28571, 5.71429, 7.14286, 10.95238, 10.47619, 7.14286, 2.38095},
{0.00000, 1.12360, 2.92135, 4.04494, 4.94382, 5.39326, 6.06742, 6.74157, 7.19101, 4.94382, 3.37079, 2.47191, 2.47191, 2.47191, 2.92135, 3.14607, 4.49438, 6.29213, 6.06742, 5.84270, 5.16854, 4.49438, 3.82022, 2.69663, 0.89888},
{2.77778, 16.66667, 13.88889, 11.11111, 6.94444, 6.94444, 8.33333, 13.88889, 15.27778, 4.16667},
{0.00000, 7.27273, 10.90909, 12.72727, 8.18182, 5.45455, 5.45455, 4.54545, 5.45455, 9.09091, 11.81818, 11.81818, 7.27273},
{4.51977, 7.34463, 9.03955, 6.77966, 6.21469, 5.08475, 5.08475, 5.08475, 5.08475, 5.08475, 4.51977, 5.64972, 6.21469, 10.16949, 8.47458, 5.64972},
{3.87597, 10.07752, 13.17829, 9.30233, 5.42636, 3.87597, 2.32558, 2.32558, 2.32558, 2.32558, 3.10078, 3.87597, 6.20155, 13.17829, 11.62791, 6.97674},
{3.36538, 7.69231, 9.61538, 7.21154, 5.76923, 4.80769, 4.32692, 4.32692, 4.32692, 5.28846, 5.76923, 9.13462, 11.53846, 9.61538, 7.21154},
{1.94903, 3.29835, 3.74813, 4.49775, 4.94753, 5.24738, 3.74813, 3.29835, 2.99850, 2.69865, 2.69865, 2.54873, 2.24888, 2.24888, 2.24888, 2.24888, 2.24888, 2.24888, 2.24888, 2.39880, 2.69865, 2.69865, 3.14843, 4.04798, 5.84708, 5.39730, 5.09745, 4.49775, 3.89805, 2.84858, 0.00000}
};

int positions[] = {0,1,1,1,1,2,2,2,2,2,3,3,3,4,4,4,4,5,5,5,5,5,6,6,6,7,7,7,7,7,7,7,8,8,8,8,8,8,9,9,9,9};

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

vector<double> GetStatistic(vector<vector<int> > & pic)
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
vector<vector<bool> > used;
void dfs(int x,int y, vector<vector<int> > & t,int amount)
{
	if (x < 0 || y < 0 || x >= t.size() || y >= t[0].size()) return;
	if (used[x][y] || t[x][y]==0) return;
	used[x][y] = 1;
	t[x][y] = amount;
	dfs(x+1,y,t,amount+1);
	dfs(x,y+1,t,amount+1);
	dfs(x-1,y,t,amount+1);
	dfs(x,y-1,t,amount+1);
}
vector<int> GetHoles(vector<vector<int> > & pic)
{
	vector<vector<int> > tmp(pic.size() + 2, vector<int>(pic[0].size()+2,0));
	for(int i=0;i<pic.size();i++)
		for(int j=0;j<pic[0].size();j++)
			tmp[i+1][j+1] = pic[i][j];

	//dfs(0,0,tmp);
	vector<int> answer;
	used = vector<vector<bool> > (tmp.size(), vector<bool>(tmp[0].size(),0));
	for(int i=0;i<tmp.size();++i)
		for(int j=0;j<tmp[i].size();j++)
			if (tmp[i][j] == 1 && !used[i][j])
			{
				amount = 0;
				//dfs(i,j,tmp,1);
				if (amount  >= 10) 
					answer.push_back(amount);
			}
	cout << endl;
	for(int i=0;i<pic.size();i++)
	{
		for(int j=0;j<tmp[i].size();j++)
			cout << 'a' + char(tmp[i][j]);
		cout << endl;
	}
	cout << endl;
	return answer;
}

int Recognize(vector<vector<int> > & picture, int left, int right)
{
	vector<vector<int> > pic;
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
	vector<int> row;
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

double GetDiff(vector<double> & d, int pos)
{
	vector<double> s;
	for(int i=0;i<dWidth;i++)
		s.push_back(distrib[pos][i]);
	if (s.size() < d.size())
		swap(d,s);
	int steps = s.size() - d.size();
	double bestDiff = 100000000;
	for(int i=0;i<steps;i++) // begin point
	{
		double cDiff = 0;
		for(int j=0;j<d.size();j++)
			cDiff += fabs(s[i+j] - d[j]);
		if (cDiff < bestDiff)
			bestDiff = cDiff;
	}
	return bestDiff;
}

int RecDistrib(vector<vector<int> > picture, int left, int right)
{
	vector<vector<int> > pic;
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

	int answer = 0;
	double diffMin = 1000000;
	vector<double> curDistribution = GetDistribution(pic);
	for(int i=0;i<dSize;i++)
	{
		int curSize = curDistribution.size();
		double diff = GetDiff(curDistribution,i);
		if (diff < diffMin)
		{
			diffMin = diff;
			answer = i;
		}
	}
	return positions[answer];
}

int main()
{
	ReadNumbers();
	SeparateNumbers();
	//PrintLetters();
	int res = 0;
	int second = 0;
	for(int i=0;i<borders.size();i++)
	{
		//res = res * 10 + Recognize(picture, borders[i].first,borders[i].second);
		second = second * 10 + RecDistrib(picture,borders[i].first,borders[i].second);
	}
	cout <<  second;
	return 0;
} 
