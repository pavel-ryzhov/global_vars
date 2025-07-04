#include <iostream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

class Digit
{
	public:
	vector<string> raws;
	int num_of_good_pixels;
};



int max_x=-1, min_x=2000000, max_y=-1, min_y=2000000;

void recursive_traversing_without_light_color(vector<string> & B, int x, int y, char num_of_digit)
{
	if(x <0 || x>=B[0].size()) return;
	if(y < 0 || y>=B.size()) return;
	if(B[y][x]=='@'||B[y][x]=='#')
	{
		B[y][x]= num_of_digit;
		if(y > max_y) max_y = y;
		else if(y < min_y) min_y = y;
		if(x>max_x) max_x = x;
		else if(x<min_x) min_x = x;
	}
	else return;
	for(int i=-1;i<2;i+=1)
	{
		for(int j=-1;j<2;j+=1)
		{
			if(i!=0 || j!=0)
			{
				recursive_traversing_without_light_color(B, x+i,y+j, num_of_digit);
			}
		}
	}
}

void recursive_traversing(vector<string> & B, int x, int y, char num_of_digit)
{
	if(x <0 || x>=B[0].size()) return;
	if(y < 0 || y>=B.size()) return;
	if(B[y][x]=='@'||B[y][x]=='#'||B[y][x]=='%')
	{
		B[y][x]= num_of_digit;
		if(y > max_y) max_y = y;
		else if(y < min_y) min_y = y;
		if(x>max_x) max_x = x;
		else if(x<min_x) min_x = x;
	}
	else return;
	for(int i=-1;i<2;i+=1)
	{
		for(int j=-1;j<2;j+=1)
		{
			if(i!=0 || j!=0)
			{
				recursive_traversing(B, x+i,y+j, num_of_digit);
			}
		}
	}
}

int main()
{
		char A[80][220];
		char c;

		//Reading
		int i=0,j=0;
		while (!cin.eof())
		{
			cin.get(c);
			if(c=='\n'||cin.eof())
			{
				A[i][j]='\0';
				i++;
				j=0;
			}
			else
			{
				A[i][j] = c;
				j++;
			}
		}
		int height = i-1;
		int length = strlen(A[0]);


		length-=10;

		vector<string> B;
		for(int i=5; i<height-5;i++)
		{
			string str(A[i]+5,length);
			B.push_back(str);
		}
		height-=10;//obyazatelno tyt

		char num_of_digit='1';
		int y = height / 2;
		int x=0;

		vector<string> B_to_start_with = B;
		vector<string> B_good_result = B;
		bool good_recognition = true;

		while(x<length)
		{
			if(B[y][x]!='@') x++;
			else break;
		}

		vector< Digit > digits;

		while(x<length)
		{
			min_x = x;
			max_x = x;
			min_y = y;
			max_y = y;

			if(good_recognition) recursive_traversing(B_to_start_with, x,y,num_of_digit);
			else
			{
				recursive_traversing_without_light_color(B_to_start_with,x,y,num_of_digit);
				good_recognition = true;
			}

			int area = (max_x - min_x + 1)*(max_y - min_y + 1);

			if(area > length*height/2)
			{
				good_recognition = false;
				min_x = x;
				max_x = x;
				min_y = y;
				max_y = y;
				recursive_traversing_without_light_color(B_good_result,x,y,num_of_digit);
				area = (max_x - min_x + 1)*(max_y - min_y + 1);
			}
			else
			{
				B_good_result = B_to_start_with;
			}
			//Virezaem
			//--------------

			Digit current_digit;
			int num_of_good_pixels = 0;
			for(int i=min_y; i<=max_y;i++)
			{
				string raw;
				for(int j=min_x; j<=max_x;j++)
				{
					if(B_good_result[i][j]==num_of_digit)
					{
						raw.push_back('1');
						num_of_good_pixels++;
					}
					else raw.push_back('.');
				}
				current_digit.raws.push_back(raw);
			}
			current_digit.num_of_good_pixels = num_of_good_pixels;

			digits.push_back(current_digit);
			//--------------

			while(x<length)
			{
				if(B_good_result[y][x]!='@') x++;
				else
				{
					if(good_recognition == false)B_to_start_with = B_good_result;
					break;
				}
			}
			num_of_digit++;
		}

		vector< pair<int*, int> > known_proportions;
		int v0[1] = {578182};
		pair<int*,int> p0(v0,(sizeof v0)/(sizeof v0[0]));
		known_proportions.push_back(p0);

		int v1[3] = {632812, 366606, 1211};
		pair<int*,int> p1(v1,(sizeof v1)/(sizeof v1[0]));
		known_proportions.push_back(p1);

		int v2[6] = {364625, 622797, 351562, 495798, 473214, 294118};
		pair<int*,int> p2(v2,(sizeof v2)/(sizeof v2[0]));
		known_proportions.push_back(p2);

		int v3[2] = {347826, 427536};
		pair<int*,int> p3(v3,(sizeof v3)/(sizeof v3[0]));
		known_proportions.push_back(p3);

		int v4[5] = {448925,252451,415741,282051,419048};
		pair<int*,int> p4(v4,(sizeof v4)/(sizeof v4[0]));
		known_proportions.push_back(p4);

		int v5[8] = {285714,622998,349767,36,441667,445909,31339,284259};
		pair<int*,int> p5(v5,(sizeof v5)/(sizeof v5[0]));
		known_proportions.push_back(p5);

		int v6[5] = {274436,48,483516,66,6576};
		pair<int*,int> p6(v6,(sizeof v6)/(sizeof v6[0]));
		known_proportions.push_back(p6);

		int v7[5] = {258799,217857,298551,418269,550265};
		pair<int*,int> p7(v7,(sizeof v7)/(sizeof v7[0]));
		known_proportions.push_back(p7);

		int v8[7] = {472651,44686,57033,591837,412587,590517,427381};
		pair<int*,int> p8(v8,(sizeof v8)/(sizeof v8[0]));
		known_proportions.push_back(p8);

		int v9[5] = {480978,335938,648148,447773,557809};
		pair<int*,int> p9(v9,(sizeof v9)/(sizeof v9[0]));
		known_proportions.push_back(p9);


		for(int i=0;i<digits.size();i++)
		{
			int proportion_of_areas = (int)1000000*((double)digits[i].num_of_good_pixels) / (digits[i].raws.size()*digits[i].raws[0].size());
			bool okey = true;
			for(int j=0;j<10&&okey;j++)
			{
				for(int k=0;k<known_proportions[j].second;k++)
				{
					if( (proportion_of_areas <= (known_proportions[j].first)[k]+10)&&(proportion_of_areas >= (known_proportions[j].first)[k]-10))
					{
						cout<<j;
						okey = false;
						break;
					}
				}
			}
		}
		cout<<endl;

		return 0;
}