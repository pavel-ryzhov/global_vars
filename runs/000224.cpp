#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
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

	
	for(unsigned int i = image.size() - 1, count = 0; ; i--, count = 0) {
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
	string TEMP = ".......1111111...........111111111111......11111....111111....11111......111111..1111..........11111.1111..........11111.1111..........11111.1111..........1111111111..........1111111111..........1111111111..........1111111111..........1111111111..........11111.1111..........11111.1111.........111111.11111........111111..111111.....111111....111111111111111........1111111111............111111.................111111111..........1111111111........111111111111......11111111111111....1111111111111111...11111111111111111...11111111111111111..........1111111111..........1111111111..........1111111111..........1111111111..........1111111111..........1111111111..........1111111111..........1111111111..........1111111111..........1111111111..........1111111111..........1111111111..........1111111111....111111111111......1111111111111111...11111111111111111111111111........111111111111........11111...............11111..............111111............11111111..........1111111111........11111111111.......11111111111.......1111111111........1111111111.........111111111...........11111111............1111111............11111111111111111111111111111111111111111111111111111111111111111111111111111111.....11111111111.......111111111111111...11111111111111111111111111......111111111111.......11111111.............111111.............111111...........1111111...........111111111...........1111111111............111111111...............1111111...............11111...............11111...............1111111111..........11111111111........111111.111111111111111111...1111111111111111......11111111111..................11111..............111111............11111111...........111111111..........1111111111.........1111..11111.......11111...11111......11111....11111.....1111......11111....1111.......11111...111.........11111..11111111111111111111111111111111111111111111111111111111111111111111111111111111.............11111...............11111...............11111...............11111...............11111.....1111111111111111...11111111111111111...11111111111111111...11111...............1111...............11111...............1111................1111111111111.......11111111111111111..1111111111111111111.11111........1111111..............111111...............11111...............11111...............1111111111..........11111.11111........111111..1111111111111111......1111111111111.........111111111............111111111........1111111....111....11111111......111..111111111..........11111111............11111111............1111111.............1111111.............1111111.111111111...1111111111111111111.11111111111111111111111111111......111111111111..........1111111111..........1111111111..........11111111111........1111.111111111.....11111..111111111111111111...111111111111111........111111111.....1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111...............11111...............11111.............111111.............111111.............1111111............111111.............111111.............111111.............1111111............1111111.............111111.............1111111.............111111..............111111..............111111................1111111...........11111111111.......111111111111111....11111......111111..111111.......11111..111111.......11111...111111.....11111......1111111111111........1111111111........111111111111111...1111111.....111111.111111.........11111111111.........11111111111.........11111111111.........111111111111.......111111.1111111111111111111..11111111111111111.....1111111111111..........111111..............1111111..........1111111111111......1111111111111111...11111.....1111111..1111..........111111111...........111111111...........111111111...........11111.11111........111111..111111111111111111...11111111111111111..............111111...............11111...............11111...............11111.111..........111111.111.........1111111..1111......111111......1111..111111............1111........";
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
	}	
}

vector<int> recognition(type& image, vector<type>& templates)
{	
	vector<type> figure;
	figure_cut(image, figure);

	vector<int> cmp(10);
	vector<int> result(figure.size());
	for(unsigned int i = 0; i < figure.size(); i++)
	{
		vector<type> templ = templates;
		unsigned int width, height;

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
			int count = 0;
			for(unsigned int row = 0; row < height; row++)
				for(unsigned int col = 0; col < width; col++)
					if(!(templ[t][row][col] ^ figure[i][row][col]))
						count++;
			cmp[t] = (count * 100) / (height * width);
		}

		if(figure[i][0][0] ==  '1' || figure[i][0][figure[i][0].size() - 1] == '1' || figure[i][figure[i].size() - 1][0] == '1' ||
			figure[i][figure[i].size() - 1][figure[i][0].size() - 1] == '1')
			cmp[0] = cmp[3] = cmp[6] = cmp[8] = cmp[9] = 0;
		else if(figure[i][0][0] ==  '0' && figure[i][0][figure[i][0].size() - 1] == '0' && figure[i][figure[i].size() - 1][0] == '0' &&
			figure[i][figure[i].size() - 1][figure[i][0].size() - 1] == '0')
			cmp[1] = cmp[7] = 0;

		/*unsigned int p = 0;
		for(; p < figure[i][0].size() && figure[i][0][p] == '0'; p++){}
		{
		if(p > width / 7 && p < width - width / 7)
		cmp[5] = 0;
		}*/


		int max_cmp = 0;
		for(unsigned int j = 0; j < cmp.size(); j++)
			if(max_cmp < cmp[j]){
				max_cmp = cmp[j];
				result[i] = j;
			}		
	}
	return result;
}