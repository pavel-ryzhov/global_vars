#include <iostream>
#include <vector>

using namespace std;

vector<vector<char> > grayToWhite(vector<vector<char> > in)
{
	vector<vector<char> > out;
	out.resize(in.size());
	for (int i = 0; i < out.size(); i++)
		out[i].resize(in[i].size());
	
	for (int i = 0; i<out.size(); i++)
	{
		for (int j = 0; j<out[i].size(); j++)
		{
			if (in[i][j] == '@')
				out[i][j] = '@';
			else
				out[i][j] = '.';
		}
	}
	return out;
}

void find_simiholes(vector<vector<char> > in, bool &lefthole, bool &righthole)
{
	for (int i = 0; i<in.size(); i++)
		for (int j = 0; j<in[0].size(); j++)
			if (in[i][j] == '.')
			{
				bool down  = false;
				bool up    = false;
				bool left  = false;
				bool right = false;

				for (int i2 = i; i2<in.size(); i2++)
					if (in[i2][j] != '.')
					{
						down = true;
						break;
					}
				for (int i2 = i; i2 > -1; i2--)
					if (in[i2][j] != '.')
					{
						up = true;
						break;
					}
				for (int j2 = j; j2<in[0].size(); j2++)
					if (in[i][j2] != '.')
					{
						right = true;
						break;
					}
				for (int j2 = j; j2 > -1; j2--)
					if (in[i][j2] != '.')
					{
						left = true;
						break;
					}
				if (up && right && down && !left)
					lefthole = true;

				if (up && !right && down && left)
					righthole = true;
				
				if (lefthole && righthole)
					return;
			}
}

bool find_hole(vector<vector<char> > in)
{
	for (int i = 0; i<in.size(); i++)
		for (int j = 0; j<in[0].size(); j++)
			if (in[i][j] == '.')
			{
				bool down  = false;
				bool up    = false;
				bool left  = false;
				bool right = false;

				for (int i2 = i; i2<in.size(); i2++)
					if (in[i2][j] != '.')
						{down = true; break;}

				for (int i2 = i; i2 > -1; i2--)
					if (in[i2][j] != '.')
						{up = true;	break;}

				for (int j2 = j; j2<in[0].size(); j2++)
					if (in[i][j2] != '.')
						{right = true; break;}

				for (int j2 = j; j2 > -1; j2--)
					if (in[i][j2] != '.')
						{left = true; break;}
				
				if (up && right && down && left)
				{
					
					bool isnothole = false;
					int i2 = i;
					int j2 = j;
					while (in[i2-1][j2] == '.')
					{
						if (i2>0)
							i2--;
						else break;
					}
					while (in[i2][j2] == '.')
					{
						right = false;
						left = false;
						for (int j3 = j2; j3<in[0].size(); j3++)
							if (in[i2][j3] != '.')
							{
								right = true;
								break;
							}
						for (int j3 = j2; j3 > -1; j3--)
							if (in[i2][j3] != '.')
							{
								left = true;
								break;
							}
						if (!right)
						{
							isnothole = true;
							break;
						}
						if (!left)
						{
							isnothole = true;
							break;
						}
						if (i2 <in.size())
							i2++;
						else break;
					}
					i2 = i;
					j2 = j;

					while (in[i2][j2-1] == '.')
					{
						if (j2>0)
							j2--;
						else break;
					}
					while (in[i2][j2] == '.')
					{
						right = false;
						left = false;
						for (int j3 = j2; j3<in[0].size(); j3++)
							if (in[i2][j3] != '.')
							{
								right = true;
								break;
							}
						for (int j3 = j2; j3 > -1; j3--)
							if (in[i2][j3] != '.')
							{
								left = true;
								break;
							}
						if (!right)
						{
							isnothole = true;
							break;
						}
						if (!left)
						{
							isnothole = true;
							break;
						}
						if (j2 <in[0].size())
							j2++;
						else break;
					}
					if (!isnothole)
						return true;
				}
			}
}

vector<vector<char> > find_and_delete_white_lines(vector<vector<char> > in)
{
	vector<bool> rows;
	rows.resize(in.size());
	for (int i = 0; i<in.size(); i++)
	{
		bool notWhiteLine = false;
		for (int j = 0; j<in[0].size(); j++)
		{
			if (in[i][j] != '.')
			{
				notWhiteLine = true;
				break;
			}
		}
		if (notWhiteLine)
			rows[i] = true;
		else
			rows[i] = false;
	}

	bool whiteLines = false;
	for (int i = 0; i<rows.size(); i++)
		if (!rows[i])
		{
			whiteLines = true;
			break;
		}
	int maxHeight = 0;
	int max = in.size()-1, min = 0;
	if (whiteLines)
	{
		for (int i = 0; i<rows.size(); i++)
		{
			if (rows[i])
			{
				int j = i;
				while (rows[j]) 
				{
					if (j<rows.size()-1) 
						j++;
					else break;
				}
				if (j-1 - i > maxHeight)
				{
					min = i;
					max = j-1;
					maxHeight = j-1 - i;
				}
			}
		}
	}
	vector<vector<char> > out;
	for (int i = min; i < max+1; i++)
		out.push_back(in[i]);

	return out;
}

vector<vector<vector<char> > > split(vector<vector<char> > in)
{
	vector<vector<char> > separateIn = grayToWhite(in);
	vector<vector<vector<char> > > out;

	vector<bool> columns;
	columns.resize(in[0].size());
	for (int j = 0; j<in[0].size(); j++)
	{
		columns[j] = false;
		for (int i = 0; i<in.size(); i++)
		{
			if (separateIn[i][j] != '.')
				columns[j] = true;
		}
	}

	vector<vector<char> > digitTransponse;
	vector<vector<char> > digit;
	int j = 0;
	
	while(j<columns.size())
	{
		if (!columns[j])
		{
			if (digit.size())
			{
				digitTransponse.resize(digit[0].size());
				for (int dt = 0; dt < digitTransponse.size(); dt++)
					digitTransponse[dt].resize(digit.size());

				for (int ii = 0; ii < digitTransponse.size(); ii++)
					for (int jj = 0; jj < digitTransponse[ii].size(); jj++)
					{
						digitTransponse[ii][jj] = digit[jj][ii];
					}
				out.push_back(digitTransponse);
				digit.clear();
			}
		}
		else
		{
			vector<char> col;
			for (int i = 0; i< in.size(); i++)
				col.push_back(in[i][j]);
			digit.push_back(col);
		}
		j++;
	}
	return out;
}






int main()
{

	vector<vector<char> > in;
	vector<char> str;
	char c;
	while(cin.get(c))
	{
		if (c == '\n')
		{
			int sym = 0;
			while (sym < str.size())
			{
				if (str[sym] != '.')
					break;
				sym++;
			}
			if (sym<str.size())
				in.push_back(str);
			str.clear();
		}
		else
			str.push_back(c);
	}

	vector<vector<vector<char> > > digits;
	digits = split(in);


	for (int k = 0; k<digits.size(); k++)
	{
		
		digits[k] = find_and_delete_white_lines(digits[k]);
		
		bool lefthole = false;
		bool righthole = false;
		bool hole = find_hole(digits[k]);	
		find_simiholes(digits[k], lefthole, righthole);

		if (hole)
		{
			if (lefthole && !righthole)
				cout<<"9";
		}
		else
		{
			if (lefthole)
				cout<<"7";
		}

	}

	return 0;
}

