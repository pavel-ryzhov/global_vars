#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
//#include <fstream>
using namespace std;

typedef vector<string> type;
typedef pair <unsigned int, unsigned int> type_pair;
const unsigned int templ_width = 20, templ_height = 20;


void input(type&);
type_pair left_right_cut(type&);
type_pair bot_top_cut(type&, type_pair&);
void templ_input(vector <type>&);
void scope_width(type&, unsigned int);
void scope_height(type&, unsigned int);
void resize_width(type&);
void figure_cut(type&, vector <type>&);
vector<int> recognition(type&, vector<type>&);


int main()
{
	type image;	
	vector <int> result;
	vector <type> templates;

	templ_input(templates);
	input(image);
	result = recognition(image, templates);

	for(unsigned int i = 0; i < result.size(); i++)
		cout << result[i];
	cout << endl;
	return 0;
}

void input(type& image)
{
	//ifstream cin("test.txt", ios::in | ios::app);

	string str;
	while(!cin.eof())
	{
		cin >> str;
		image.push_back(str);
	}	

	for(unsigned int i = 0; i < image.size(); i++)
		for(unsigned int j = 0, count = 0; j < image[i].length(); j++, count = 0)
			if(image[i][j] == '@')
				image[i][j] = '1';
			else
				image[i][j] = '0';

	int count = 0;
	for(unsigned int i = image.size() - 1; ; i--, count = 0) {
		for(unsigned int j = 0; j < image[i].length(); j++)
			if(image[i][j] == '1')
				count++;
		if(count < 4)
			image.erase(image.begin() + i, image.begin() + i + 1);
		if(i == 0) break;
	}
	//cin.close();	
}

type_pair left_right_cut(type& image)
{
	type_pair empty_im;	
	unsigned int i, j;
	empty_im.first = image[0].length();
	empty_im.second = 0;

	for(i = 0; i < image.size(); i++){
		for(j = 0; j < image[i].length() && image[i][j] == '0'; j++) {}
		if(j < empty_im.first)  
			empty_im.first = j;
		for(j = image[i].length() - 1; j > 0 && image[i][j] == '0'; j--) {}
		if(j > empty_im.second)  
			empty_im.second = j;
	}
	return empty_im;
}


type_pair bot_top_cut(type& image, type_pair& border)
{
	unsigned int m_top(image.size()), m_bottom(0), i, j;
	for(j = border.first; j <= border.second; j++)
	{
		for(i = 0; i < image.size() && image[i][j] == '0'; ++i){}
		if(m_top > i) m_top = i;

		for(i = image.size() - 1; i > 0  && image[i][j] == '0'; --i){}
		if(m_bottom < i) m_bottom = i;
	}	
	type_pair ret = make_pair(m_top, m_bottom); 
	return ret;
}

void templ_input(vector <type>& templates)
{
	string TEMP = "........11111............1111...11111......1111.......1111....1111.........1111..1111...........1111.1111...........1111.1111...........1111.1111...........11111111............11111111............11111111............11111111............11111111............1111.111............1111.111...........11111.1111..........11111..1111........1111.....11111.....11111........111...1111.............1111..................11111111...........111111111.........11111111111.......1111111111111.....111111111111111....1111111111111111....1111111111111111...........111111111...........111111111...........111111111...........111111111...........111111111...........111111111...........111111111...........111111111...........111111111...........111111111...........111111111...........111111111..........11111111111....11111111111.......1111111.1111111....1111..........111111111...........111111111...........11111...............11111..............111111............1111111............111111............1111111...........1111111...........1111111...........11111111...........1111111............1111111............1111111.............11111..............11111111...........111111111111111111111111111111111111111111......1111111111........11111111111111....11111.......11111..11111.........1111..111...........1111................1111...............11111............1111111...........11111111............111111111............111111111...............11111................11111...............11111...............11111111............11111.1111.........111111.11111.......11111....1111111111111111......11111111111.................111111.............1111111...........111111111..........1111111111.........11111111111........11111..11111......111111...11111.....111111....11111....11111......11111...11111.......11111...1111........11111..11111111111111111111111111111111111111111111111111111111111111111111111111111111.............11111...............11111...............11111...............11111.............111111111....111111111111111....1111111111111111...11111111111111111...1111................1111................111................1111111111..........11111111111111.......111......11111.................11111................11111................1111.................1111................1111................1111................11111111...........1111..1111........1111......11111..111111..........1111111...............11111111.........11111.....111.....11111........111...1111...............1111................111................1111................1111................111111111111........111111111111111.....11111........111111.1111...........111111111.............1111111.............1111111.............1111111.............111.1111...........1111..11111........11111...111111111111111........111111111.....11111111111111111111111111111111111111111111111111111111111111111111111111111111...............11111...............11111...............1111..............11111..............111111.............11111..............111111.............111111.............111111.............1111111............1111111.............111111.............1111111.............111111..............111111..............111111...............111111111........1111......1111.....1111.........1111..1111..........1111..1111...........111..1111.........11111...11111.......1111......11111....1111........1111111111...........111111111........11111111111111.....11111.....1111111..11111.........1111..1111..........1111111111...........111111111...........1111111111.........1111..111111......111111.....111111111111.........1111111111............1111111..........1111111111111......1111111111111111...11111.....1111111..1111..........111111111...........111111111...........111111111...........11111.11111........111111..111111111111111111...11111111111111111..............111111...............11111...............11111...............11111..............111111.............11111......11......11111........11111111111............1111........";
	templates.resize(10, type(templ_height));
	for(unsigned int i = 0, index = 0; i < 10; i++)
		for(unsigned int j = 0; j < templ_height; j++){
			unsigned int k = index;
			for(; k < index + templ_width; k++)
				if(TEMP[k] == '.')
					templates[i][j] += '0';
				else
					templates[i][j] += '1';
			index = k;
		}
}

void scope_width(type& image, unsigned int col)
{
	unsigned int len = image[0].length();
	for(unsigned int i = 0; i < image.size(); i++)
	{
		string s;
		unsigned int step = len - col, j = 0;
		while( step > 0 )
		{
			if(j % 2 != 0) 
				s += image[i][j];
			else
				--step;			
			j++;
			if(j >= len) {
				j = 0;
				image[i] = s;
				s = "";
			}
		}
		if(j > 0) {		
			for(; j < image[i].size(); j++)
				s += image[i][j];
			image[i] = s;
		}
	}	
}

void scope_height(type& image, unsigned int row)
{
	unsigned int step = image.size() - row;

	while(step > 0)
	{
		for(unsigned int i = 0; i < image.size(); i++)
		{
			if(i % 4 != 0) {
				image.erase(image.begin() + i, image.begin() + i + 1);
				--step;
				if(step == 0)
					break;
			}
		}
	}
}

void resize_width(type& image)
{	
	for(unsigned int i = 0; i < image.size(); i++) {
		string s;
		for(unsigned int j = 0; j < image[i].length() - 1; j++)
			if(image[i][j] == '0')
				if(image[i][j + 1] == '0')
					s += "00";
				else
					s += "01";
			else if(image[i][j + 1] == '0')
				s += "10";
			else
				s += "11";
			image[i] = s;
	}
}

void figure_cut(type& image, vector <type>& figure)
{
	type_pair empty_im = left_right_cut(image);
	vector <pair <int, unsigned int> > gist;
	unsigned int height = image.size(), index = 0;	

	for(unsigned int i = empty_im.first + 1; i < empty_im.second; i++){
		unsigned int count = 0;
		for(unsigned int j = 0; j < height; j++){
			if(image[j][i] == '0')
				count++;
		}
		if(count < height || (count == height && gist[index - 1].first != 0)){
			gist.push_back(make_pair(height - count, i));
			index ++;
		}
	}	
	sort(gist.begin(), gist.end());

	int k = 0;
	vector<unsigned int> sections;
	sections.push_back(empty_im.first);
	while(!gist[k].first){
		sections.push_back(gist[k++].second);
	}
	sections.push_back(empty_im.second + 1);

	if(k > 0)
	{
		figure.resize(k + 1);
		for(int i = 0; i <= k; i++)
		{
			unsigned int left = sections[i + 1], ii, jj;
			for(ii = 0; ii < image.size(); ii++) {
				for(jj = sections[i]; jj < sections[i + 1] && image[ii][jj] == '0'; jj++) {}
				if(jj < left) left = jj;
			}
			type_pair l_r = make_pair(left, sections[i + 1]);
			type_pair empty_top_bot = bot_top_cut(image, l_r);
			figure[i].resize(empty_top_bot.second - empty_top_bot.first + 1);		

			for(unsigned int j = empty_top_bot.first, ind = 0; j <= empty_top_bot.second; j++)
				figure[i][ind++] = image[j].substr(left, sections[i + 1] - left);

			int count = 0;
			for(unsigned int ii = 0; ii < figure[i][0].size(); ii++)
				if(figure[i][0][ii] == '1') count++;
			if((count < 3 && figure[i].size() < 30) || (count < 4 && figure[i].size() > 30))
				figure[i].erase(figure[i].begin(), figure[i].begin() + 1);


			if(figure[i].size() < templ_width - 2)
				resize_width(figure[i]);

		}
	}
	else
	{
		type_pair l_r = make_pair(empty_im.first, empty_im.second);
		type_pair empty_top_bot = bot_top_cut(image, l_r);
		figure.resize(1);
		figure[0].resize(empty_top_bot.second - empty_top_bot.first + 1);


		for(unsigned int i = empty_top_bot.first; i <= empty_top_bot.second; i++)
			figure[0][k++] = image[i].substr(empty_im.first, empty_im.first - empty_im.second);

		int count = 0;
		for(unsigned int i = 0; i < figure[0][0].size(); i++)
			if(figure[0][0][i] == '1') count++;
		if((count < 3 && figure[0].size() < 30) || (count < 4 && figure[0].size() > 30))
			figure[0].erase(figure[0].begin(), figure[0].begin());

		if(figure[0].size() < templ_width - 2)
			resize_width(figure[0]);


	}	
}

vector<int> recognition(type& image, vector<type>& templates)
{	
	vector<type> figure;
	figure_cut(image, figure);


	vector<int> result(figure.size());
	for(unsigned int i = 0; i < figure.size(); i++)
	{
		vector<int> cmp(10);
		vector<type> templ = templates;
		unsigned int width, height;

		if(figure[i][0][0] ==  '1' || figure[i][figure[i].size() - 1][figure[i][0].size() - 1] == '1' 
			|| figure[i][0][figure[i][0].size() - 1] == '1' || figure[i][figure[i].size() - 1][0] == '1') {
			cmp[0] = cmp[8] = cmp[9] = -1;

			if(figure[i][0][figure[i][0].size() - 1] != '1')
				cmp[6] = -1;
			if(figure[i][figure[i].size() - 1][0] != '1')
				cmp[3]= -1;				
		}

		if(figure[i][0][0] ==  '1' || figure[i][0][figure[i][0].size() - 1] == '1')
			cmp[2] = -1;

		/*if(figure[i][0][0] ==  '0' && figure[i][0][figure[i][0].size() - 1] == '0' && figure[i][figure[i].size() - 1][0] == '0' &&
			figure[i][figure[i].size() - 1][figure[i][0].size() - 1] == '0')
			cmp[1] = cmp[7] = -1;*/

		unsigned int  count_bot = 0, count_top = 0;
		int bal_hor = 0, bal_ver = 0, cmp_3_5 = 0;;

		for(unsigned int t = 0; t < figure[i][0].size(); t++)
			if(figure[i][0][t] == '1') count_top++;
		for(unsigned int t = 0; t < figure[i][0].size(); t++)
			if(figure[i][figure[i].size() - 1][t] == '1') count_bot++;

		if(count_top <= figure[i][0].size() / 2 + 1)
			cmp[5] = cmp[7] = -1;
		else
			cmp[4]  = cmp[6] = cmp[0] = -1;

		if(count_bot < 2 * figure[i][0].size() / 3)		
			cmp[2] = -1;
		else
		{
			if(count_bot > figure[i][0].size() / 2)	
				cmp[7] = -1;
			if(figure[i][figure[i].size() - 1][0] == '1')
				cmp[3] = -1;			
		}


		for(unsigned int row = 0; row < figure[i].size(); row++)
			for(unsigned int col = 0; col < figure[i][0].size(); col++){
				if(row < figure[i].size() / 2 && figure[i][row][col] == '1')
					bal_ver++;
				if(row >= figure[i].size() / 2 && figure[i][row][col] == '1')
					bal_ver--;
				if(col <= figure[i][row].size() / 2 && figure[i][row][col] == '1')
					bal_hor++;
				if(col > figure[i][row].size() / 2 && figure[i][row][col] == '1')
					bal_hor--;
				if(row < figure[i].size() / 2 && col < figure[i][row].size() / 2 && figure[i][row][col] == '1')
					cmp_3_5++;
				if(row < figure[i].size() / 2 && col > figure[i][row].size() / 2 && figure[i][row][col] == '1')
					cmp_3_5--;
			}

			if(bal_ver < -10) cmp[7] = -1;			

			if (bal_hor > 10)
				cmp[4] = cmp[3] = -1;
			else if(bal_hor < -10)
				cmp[6] = -1;
			else if(bal_hor == 0)
				cmp[3] = -1;

			/*if(cmp_3_5 > 10)
				cmp[3] =  -1;
			else if(cmp_3_5 < -10)
				cmp[5] = -1;*/

			bool ok = false;
			unsigned int count_6_9 = 10, i_t = 0;
			for(unsigned int t = 0; t < figure[i].size();) {				
				if(figure[i][t][figure[i][t].size() / 2] == '1')
				{
					ok ^= true;
					while(t < figure[i].size() && figure[i][t][figure[i][t].size() / 2] == '1') ++t;
				}
				++t;
			}

			unsigned int len_min = 0, len_max = 0;
			for(unsigned int t = 2, count = 0; t < figure[i].size() - 2; t++, count = 0) {
				for(unsigned int j = 0; j < figure[i][t].size();){					
					if(figure[i][t][j] == '1')
					{						
						count++;
						while(j < figure[i][t].size() && figure[i][t][j] == '1') ++j;
					}
					++j;					
				}
				if(count == 1)	len_min++;
				if(count > 0 && count <= count_6_9 && t >= figure[i].size() / 6 && t <= figure[i].size() - figure[i].size() / 6 ) {					
					count_6_9 = count;
					i_t = t;
				}
			}
			for(unsigned int t = 2; t < figure[i].size() - 2; t++, len_max = 0) {
				for(unsigned int j = 0; j < figure[i][t].size(); j++){	
					if(figure[i][t][j] == '1')
						len_max++;
				}
				if(len_max == figure[i][t].size())
					cmp[3] = cmp[6] = cmp[8] = cmp[9] = cmp[0] = -1;
			}

			unsigned int count_1_4 = 0;
			for(unsigned int jj = 0; jj < figure[i][0].size(); jj++, count_1_4 = 0){
				for(unsigned int ii = 0; ii < figure[i].size(); ii++)
					if(figure[i][ii][jj] == '1') count_1_4++;
				if(count_1_4 == figure[i].size()) break;
			}

			if(count_1_4 == figure[i].size()) {
				cmp[9] = cmp[6] = cmp[2] = cmp[3] = cmp[5] = -1;
				bool ok = false;
				for(unsigned int ii = figure[i].size() / 3 + figure[i].size() / 10; ii <= 2 * figure[i].size() / 3 + figure[i].size() / 10; ii++){
					if(figure[i][ii][0] == '1') ok = true;
				}
				if(ok)
					cmp[1] = -1;
				else
					cmp[4] = -1;
			}
			else
				cmp[1] = -1;

			if(count_6_9 == 1 && i_t != 0) {
				if(i_t < figure[i].size() / 2)
					cmp[9] = -1;
				else
					cmp[6] = -1;

				if(max(figure[i].size() / 2, i_t) - min(figure[i].size() / 2, i_t) < figure[i].size() / 10 && len_min < figure[i].size() / 3)
					cmp[9] = cmp[6] = -1;
			}

			int top_black = 0, bott_black = 0;
			if(cmp[3] != -1 && cmp[9] != -1)
				for(unsigned int row = 0; row < figure[i].size(); row++)
					for(unsigned int col = 0; col < figure[i][row].size(); col++)
						if(figure[i][row][col] == '1'){
							if(row <= figure[i].size() / 2)
								top_black++;
							else
								bott_black++;
						}

			if(bott_black > 0 && (top_black / bott_black) >= 2)
				cmp[3] = cmp[8] = -1;
			else if(top_black > 0 && bott_black / top_black >= 2)
				cmp[9] = -1;
				
			
			bool ch_7_5 = false;
			for(unsigned int row = figure[i].size() / 2; row < figure[i].size(); row++)
				if(figure[i][row][figure[i][row].size() - 3] == '1' || figure[i][row][figure[i][row].size() - 1] == '1')
					ch_7_5 = true;
			if(ch_7_5)
				cmp[7] = -1;
			else
				cmp[5] = -1;

			if(len_min < figure[i].size() / 3)
				cmp[3] = -1;
			else if(len_min > figure[i].size() / 2)
				cmp[0] = cmp[8] =  -1;

			if(ok)
				cmp[0] = -1;
			else
				cmp[8] = cmp[9] = cmp[6] = -1;

			if(figure[i][0].size() > templ_width)
			{
				scope_width(figure[i], templ_width);
				width = templ_width;
			}
			else
			{
				for(unsigned int j = 0; j < templ.size(); j++)
					scope_width(templ[j], figure[i][0].size());
				width = figure[i][0].size();
			}

			if(figure[i].size() > templ_height)
			{
				scope_height(figure[i], templ_height);
				height = templ_height;
			}
			else
			{
				for(unsigned int j = 0; j < templ.size(); j++)
					scope_height(templ[j], figure[i].size());
				height = figure[i].size();
			}


			for(int t = 0; t < 10; t++){
				if(cmp[t] != -1) {
					int count = 0;
					for(unsigned int row = 0; row < height; row++)
						for(unsigned int col = 0; col < width; col++)
							if(!(templ[t][row][col] ^ figure[i][row][col]))
								count++;
					cmp[t] = count;//(count * 100) / (height * width);
				}
			}	

			int max_cmp = 0;
			for(unsigned int j = 0; j < cmp.size(); j++)
				if(max_cmp < cmp[j]){
					max_cmp = cmp[j];
					result[i] = j;
				}		
	}
	return result;
}