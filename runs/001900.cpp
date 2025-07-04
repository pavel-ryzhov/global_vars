#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

vector < string > inputarray;
vector < vector < string > > letters;
vector < vector < string > > scaledletters;
vector < vector < string > > idealletters;
#define	IDEAL_X		10
#define	IDEAL_Y		15
int readinput()
{
	char c[200];
	string str;
	int y = 1;
	while(!feof(stdin))
	{
		fscanf (stdin,"%s",c);
		str.assign(c);
		inputarray.resize(y);
		inputarray[y-1].resize(str.length());
		inputarray[y-1] = str;
		y++;
	}

	idealletters.resize( IDEAL_X ); //10
	for(int i = 0;i < IDEAL_X; i++)
	{		idealletters[i].resize( IDEAL_Y );	} //15
	idealletters[0][0]  = "...@@@@...";
	idealletters[0][1]  = "..@@@@@@..";
	idealletters[0][2]  = ".@@@..@@@.";
	idealletters[0][3]  = ".@@....@@.";
	idealletters[0][4]  = "@@@....@@@";
	idealletters[0][5]  = "@@@....@@@";
	idealletters[0][6]  = "@@@....@@@";
	idealletters[0][7]  = "@@@....@@@";
	idealletters[0][8]  = "@@@....@@@";
	idealletters[0][9]  = "@@@....@@@";
	idealletters[0][10] = "@@@....@@@";
	idealletters[0][11] = ".@@....@@.";
	idealletters[0][12] = ".@@@..@@@.";
	idealletters[0][13] = "..@@@@@@..";
	idealletters[0][14] = "...@@@@...";

	idealletters[1][0]  = "......@@..";
	idealletters[1][1]  = ".....@@@..";
	idealletters[1][2]  = "....@@@@..";
	idealletters[1][3]  = "...@@@@@..";
	idealletters[1][4]  = "...@..@@..";
	idealletters[1][5]  = "......@@..";
	idealletters[1][6]  = "......@@..";
	idealletters[1][7]  = "......@@..";
	idealletters[1][8]  = "......@@..";
	idealletters[1][9]  = "......@@..";
	idealletters[1][10] = "......@@..";
	idealletters[1][11] = "......@@..";
	idealletters[1][12] = "......@@..";
	idealletters[1][13] = "......@@..";
	idealletters[1][14] = ".@@@@@@@@@";

	idealletters[2][0]  = "..@@@@@@..";
	idealletters[2][1]  = ".@@@@@@@@.";
	idealletters[2][2]  = "@@@...@@@@";
	idealletters[2][3]  = "@@@....@@@";
	idealletters[2][4]  = ".......@@@";
	idealletters[2][5]  = ".......@@@";
	idealletters[2][6]  = "......@@@.";
	idealletters[2][7]  = ".....@@@@.";
	idealletters[2][8]  = "....@@@@..";
	idealletters[2][9]  = "...@@@@...";
	idealletters[2][10] = "..@@@@....";
	idealletters[2][11] = ".@@@@.....";
	idealletters[2][12] = ".@@@......";
	idealletters[2][13] = "@@@@@@@@@@";
	idealletters[2][14] = "@@@@@@@@@@";

	idealletters[3][0]  = "..@@@@@...";
	idealletters[3][1]  = ".@@@@@@@..";
	idealletters[3][2]  = ".@@...@@@.";
	idealletters[3][3]  = "@@@...@@@.";
	idealletters[3][4]  = "......@@@.";
	idealletters[3][5]  = "......@@@.";
	idealletters[3][6]  = "....@@@@..";
	idealletters[3][7]  = "....@@@@..";
	idealletters[3][8]  = "......@@@.";
	idealletters[3][9]  = ".......@@@";
	idealletters[3][10] = ".......@@@";
	idealletters[3][11] = "@@@....@@@";
	idealletters[3][12] = "@@@...@@@.";
	idealletters[3][13] = ".@@@@@@@@.";
	idealletters[3][14] = "..@@@@@...";

	idealletters[4][0]  = ".......@@.";
	idealletters[4][1]  = "......@@@.";
	idealletters[4][2]  = ".....@@@@.";
	idealletters[4][3]  = ".....@@@@.";
	idealletters[4][4]  = "....@@@@@.";
	idealletters[4][5]  = "...@@@.@@.";
	idealletters[4][6]  = "...@@..@@.";
	idealletters[4][7]  = "..@@...@@.";
	idealletters[4][8]  = ".@@@...@@.";
	idealletters[4][9]  = ".@@....@@.";
	idealletters[4][10] = "@@@@@@@@@@";
	idealletters[4][11] = "@@@@@@@@@@";
	idealletters[4][12] = ".......@@.";
	idealletters[4][13] = ".......@@.";
	idealletters[4][14] = ".......@@.";

	idealletters[5][0]  = "..@@@@@@@.";
	idealletters[5][1]  = "..@@@@@@@.";
	idealletters[5][2]  = ".@@@......";
	idealletters[5][3]  = ".@@@......";
	idealletters[5][4]  = ".@@@......";
	idealletters[5][5]  = ".@@@@@@@..";
	idealletters[5][6]  = ".@@@@@@@@.";
	idealletters[5][7]  = "@@@...@@@@";
	idealletters[5][8]  = ".......@@@";
	idealletters[5][9]  = ".......@@@";
	idealletters[5][10] = ".......@@@";
	idealletters[5][11] = "@@@....@@@";
	idealletters[5][12] = "@@@@..@@@.";
	idealletters[5][13] = ".@@@@@@@@.";
	idealletters[5][14] = "..@@@@@...";

	idealletters[6][0]  = "...@@@@@..";
	idealletters[6][1]  = "..@@@@@@@.";
	idealletters[6][2]  = ".@@@..@@@@";
	idealletters[6][3]  = ".@@....@..";
	idealletters[6][4]  = "@@@.......";
	idealletters[6][5]  = "@@@.@@@...";
	idealletters[6][6]  = "@@@@@@@@@.";
	idealletters[6][7]  = "@@@@..@@@.";
	idealletters[6][8]  = "@@@....@@@";
	idealletters[6][9]  = "@@@....@@@";
	idealletters[6][10] = "@@@....@@@";
	idealletters[6][11] = ".@@....@@@";
	idealletters[6][12] = ".@@@..@@@.";
	idealletters[6][13] = "..@@@@@@@.";
	idealletters[6][14] = "...@@@@...";

	idealletters[7][0]  = "@@@@@@@@@@";
	idealletters[7][1]  = "@@@@@@@@@@";
	idealletters[7][2]  = "......@@@.";
	idealletters[7][3]  = "......@@@.";
	idealletters[7][4]  = ".....@@@..";
	idealletters[7][5]  = "....@@@...";
	idealletters[7][6]  = "....@@@...";
	idealletters[7][7]  = "....@@....";
	idealletters[7][8]  = "...@@@....";
	idealletters[7][9]  = "...@@@....";
	idealletters[7][10] = "...@@.....";
	idealletters[7][11] = "..@@@.....";
	idealletters[7][12] = "..@@@.....";
	idealletters[7][13] = "..@@@.....";
	idealletters[7][14] = "..@@@.....";
	
	idealletters[8][0]  = "..@@@@@...";
	idealletters[8][1]  = ".@@@@@@@@.";
	idealletters[8][2]  = ".@@@..@@@.";
	idealletters[8][3]  = "@@@....@@@";
	idealletters[8][4]  = "@@@....@@.";
	idealletters[8][5]  = ".@@@..@@@.";
	idealletters[8][6]  = "..@@@@@@..";
	idealletters[8][7]  = "..@@@@@@..";
	idealletters[8][8]  = ".@@@..@@@.";
	idealletters[8][9]  = "@@@....@@@";
	idealletters[8][10] = "@@@....@@@";
	idealletters[8][11] = "@@@....@@@";
	idealletters[8][12] = "@@@@..@@@.";
	idealletters[8][13] = ".@@@@@@@@.";
	idealletters[8][14] = "...@@@@...";

	idealletters[9][0]  = "..@@@@@...";
	idealletters[9][1]  = ".@@@@@@@..";
	idealletters[9][2]  = "@@@...@@@.";
	idealletters[9][3]  = "@@@...@@@.";
	idealletters[9][4]  = "@@@....@@@";
	idealletters[9][5]  = "@@@....@@@";
	idealletters[9][6]  = "@@@....@@@";
	idealletters[9][7]  = "@@@...@@@@";
	idealletters[9][8]  = ".@@@@@@@@@";
	idealletters[9][9]  = "..@@@@.@@@";
	idealletters[9][10] = ".......@@@";
	idealletters[9][11] = ".......@@.";
	idealletters[9][12] = "@@@...@@@.";
	idealletters[9][13] = ".@@@@@@@..";
	idealletters[9][14] = "..@@@@@...";
	return 0;
}
void clearbottom(vector<string>&pic)
{	
	for(int i = pic.size(); i > 0; i--)
	{
		if(pic[i-1].find_first_of("@#%") != -1)
		{
			pic.resize(i);
			break;
		}
	}
}
void cleartop(vector<string>&pic)
{
	for(int i = 0; i < pic.size(); i++)
	{
		if(pic[i].find_first_of("@#%") != -1)
		{
			pic.erase(pic.begin(),pic.begin()+i);
			break;
		}
	}
}
void clearright(vector<string>&pic)
{
	bool meetnotdot = false;
	int i,j;
	for(i = pic[0].size()-1; i > 0; i--)
	{
		for(j = 0; j < pic.size(); j ++)
		{
			if(pic[j][i]!='.'&&pic[j][i]!=0)
				meetnotdot = true;
		}
		if(meetnotdot)
			break;
	}
	for(j = 0; j < pic.size(); j ++)
		pic[j].resize(i+2);
}
void clearleft(vector<string>&pic)
{
	bool meetnotdot = false;
	int i,j;
	for(i = 0; i < pic[0].size()-1; i++)
	{
		for(j = 0; j < pic.size(); j ++)
		{
			if(pic[j][i]!='.'&&pic[j][i]!='%')
				meetnotdot = true;
		}
		if(meetnotdot)
			break;
	}
	for(j = 0; j < pic.size(); j ++)
		pic[j].erase(pic[j].begin(),pic[j].begin()+i);
}
void convertmonochrome(vector<string>&pic)
{
	bool isnotmono = false;
	for(int x = 0; x < pic[0].size(); x ++)
	{
		if(pic[0][x] == '%')
		{
			pic[0][x] = '.';
			isnotmono = true;
		}
		else if(pic[0][x] == '#')
		{
			pic[0][x] = '@';
			isnotmono = true;
		}
	}
	if(isnotmono == false)
		return;
	for(int y = 1; y < pic.size(); y++)
	{
		for(int x = 0; x < pic[0].size(); x ++)
		{
			if(pic[y][x] == '%')
				pic[y][x] = '.';
			else if(pic[y][x] == '#')
				pic[y][x] = '@';
		}
	}
}
vector < vector < string > > divideintoparts(vector < string > &pic1)
{
	vector < vector < string > > pic2;
	bool meetblack = true, meetblackprev = false;
	int iter = 0;
	int pos = 0,len;
	for(int i = 0; i < pic1[0].size(); i++)
	{
		if(meetblack) meetblackprev = true;
		else meetblackprev = false;
		meetblack = false;
		for(int j = 0; j < pic1.size(); j ++)
		{
			if(pic1[j][i]=='@'||pic1[j][i]=='#')
			{
				meetblack = true;
				break;
			}
		}
		if(meetblack==false && meetblackprev == true)
		{
			iter++;
			if(iter > 3) break;
			pic2.resize(iter);
			pic2[iter-1].resize(pic1.size());
			len = i - pos;
			for(int j = 0; j < pic1.size(); j ++)
			{
				pic2[iter-1][j] = pic1[j].substr(pos,len);
			}
			pos = i;
		}
	}
	return pic2;
}
vector<string> scaleletters(vector<string>&pic1)
{
	vector<string>pic = pic1;
	double scale;
	scale = pic[0].size() / 10.0;
	double avr ,amp ,coef;
	char temp[IDEAL_X];
	for(int y = 0;y < pic.size(); y++)
	{
		for(int x = 0; x< IDEAL_X; x++)
		{
			avr = 0;
			for(int i = 0; i < pic[y].size(); i++)
			{
				if (pic[y][i] == '.')
					amp = 0;
				else if (pic[y][i] == '@')
					amp = 1;
				
				coef = (x+1)*scale - i;                
				if(coef < 0 || coef > scale+1)
					coef = 0;
				else if(coef > scale)
					coef = i+1-scale*x;
				else if(coef > 1)
					coef = 1;
				avr += amp * coef;
	
			}
			avr = avr / scale;
			if(avr < 0.5)
				temp[x] = '.';
			else if(avr >= 0.5)
				temp[x] = '@';
		}
		pic[y].assign(temp);
		pic[y].resize(10);
	}
	char temp1[IDEAL_Y];
	scale = pic.size() / 15.0;
	for(int x = 0; x< IDEAL_X; x++)
	{
		for(int y = 0;y < IDEAL_Y; y++)
		{
			avr = 0;
			for(int i = 0; i < pic.size(); i++)
			{
				if (pic[i][x] == '.')
					amp = 0;
				else if (pic[i][x] == '@')
					amp = 1;
				
				coef = (y+1)*scale - i;                
				if(coef < 0 || coef > scale+1)
					coef = 0;
				else if(coef > scale)
					coef = i+1-scale*y;
				else if(coef > 1)
					coef = 1;
				avr += amp * coef;
			}
			avr = avr / scale;
			if(avr < 0.5)
				temp1[y] = '.';
			else if(avr >= 0.5)
				temp1[y] = '@';
		}
		for(int i = 0; i < IDEAL_Y; i ++)
			pic[i][x] = temp1[i];
	}
	pic.resize(IDEAL_Y);
	return pic;
}
int compare(vector<string>&pic , bool last = false)
{
	int value[10], max = -150,maxi;
	for(int i = 0; i < 10;i++)
	{
		value[i] = 0;
		for(int y = 0; y < IDEAL_Y; y++)
		{
			for(int x = 0; x < IDEAL_X; x++)
			{
				if((pic[y][x] == '.' && idealletters[i][y][x] == '.')||
					(pic[y][x] != '.' && idealletters[i][y][x] != '.'))
					value[i]++;
				else value[i]--;
			}
		}
		if(max < value[i])
		{
			max = value[i];
			maxi = i;
		}
	}
	if(last == false)
	{
		if(value[maxi] > 70)
			return maxi;
		else
			return -1;
	}
	return maxi;
}
vector<string> ErosionDilation(vector<string>&pic1, char target) 
{
	vector<string>pic2 = pic1;
	
	for(int y = 0; y < pic1.size(); y++)
	{
		for(int x = 0; x < pic1[y].size()-1; x ++)
		{
			if(pic1[y][x] == target)
			{
				pic2[y][x] = target;
				continue;
			}
			if(x > 0)
			{
				if(y > 0)
				{
					if(pic1[y-1][x-1] == target)
						pic2[y][x] = target;
				}
				if(pic1[y][x-1] == target)
						pic2[y][x] = target;
				if(y < pic1.size() - 1)
				{
					if(pic1[y+1][x-1] == target)
						pic2[y][x] = target;
				}
			}
			if(y > 0)
			{
				if(pic1[y-1][x] == target)
						pic2[y][x] = target;
				if(x < pic1[0].size() - 1)
					if(pic1[y-1][x+1] == target)
						pic2[y][x] = target;
			}
			if(x < pic1[0].size() - 1)
			{
				if(pic1[y][x+1] == target)
					pic2[y][x] = target;
				if(y < pic1.size() - 1)
				{
					if(pic1[y+1][x+1] == target)
						pic2[y][x] = target;
				}
			}
			if(y < pic1.size() - 1)
				if(pic1[y+1][x] == target)
					pic2[y][x] = target;
		}
	}
	return pic2;
}
int main()
{
	readinput();
	clearbottom(inputarray);
	cleartop(inputarray);
	clearright(inputarray);
	clearleft(inputarray);
	letters = divideintoparts(inputarray);
	scaledletters.resize(letters.size());
	int output;
	for(int i = 0; i < letters.size(); i ++)
	{
		clearbottom(letters[i]);
		cleartop(letters[i]);
		clearright(letters[i]);
		clearleft(letters[i]);
		convertmonochrome(letters[i]);
		scaledletters[i] = scaleletters(letters[i]);		
		output = compare(scaledletters[i]);
		if(output != -1)
		{
			printf("%d",output);
			continue;
		}

		scaledletters[i] = ErosionDilation(letters[i],'@');
		scaledletters[i] = scaleletters(scaledletters[i]);
		output = compare(scaledletters[i]);
		if(output != -1)
		{
			printf("%d",output);
			continue;
		}
		
		scaledletters[i] = ErosionDilation(letters[i],'.');
		scaledletters[i] = ErosionDilation(scaledletters[i],'@');
		clearbottom(scaledletters[i]);
		cleartop(scaledletters[i]);
		clearright(scaledletters[i]);
		clearleft(scaledletters[i]);
		scaledletters[i] = scaleletters(scaledletters[i]);
		output = compare(scaledletters[i]);
		if(output != -1)
		{
			printf("%d",output);
			continue;
		}

		scaledletters[i] = ErosionDilation(letters[i],'@');
		scaledletters[i] = scaleletters(scaledletters[i]);
		output = compare(scaledletters[i], true);
		if(output != -1)
		{
			printf("%d",output);
			continue;
		}
	}
	return 0;
}

