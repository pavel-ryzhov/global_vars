// task1.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>


using namespace std;


vector<string> pic;
ifstream in;
ofstream out;
vector<string> rez(8);

vector<int> vertikal(unsigned start, unsigned end)
{
	vector<int> rez(0);
	for(unsigned i=0; i<pic.size();i++)
	{ 
		rez.push_back(0);
		for (unsigned j=start; j<end;j++)
		{
			if(pic[i][j]!='.')	rez[i]++;
		}
	}
	return rez;
}

vector<int> gorizontal()
{
	vector<int> rez(0);
	for(unsigned i=0; i<pic[0].length();i++)
	{ 
		rez.push_back(0);
		for (unsigned j=0; j<pic.size();j++)
		{
			if(pic[j][i]!='.')	rez[i]++;
		}
	}
	return rez;
}

int findMin(vector<int> v)
{
	int min=v[0];
	int imin=0;
	for (unsigned i=1; i<v.size(); i++)
	{
		if (min>v[i]) min=v[i];
	}
	return min;
}
pair<int,int> gor[3];
pair<int,int> ver[3];
void firstAnaliz()
{
	vector<int> g=gorizontal();
	int min=findMin(g);
	unsigned i=0;
	unsigned j=0;
	while ((i<g.size())&&(j<3)) 
	{
		while (g[i]<=min+1) 
			if (i+1<g.size())i++;
			else break;
		gor[j].first=i;
		while(g[i]>min+1) 
			if (i+1<g.size())i++;
			else break;
		gor[j].second=i;
		vector<int> v=vertikal(gor[j].first, gor[j].second);
		int min2=findMin(v);
		unsigned k=0;
		while (v[k]<=min2+1) 
			if (k+1<v.size()) k++;
			else break;
		ver[j].first=k;
		while (v[k]>min2+1) 
			if (k+1<v.size()) k++;
			else break;
		ver[j].second=k;
		j++;
	}
	
}

void convertToSimple(vector<string> pic)
{
	double average=0;
	int count=0;
	for (unsigned i=0; i<pic.size(); i++)
	{
		for (unsigned j=0; j<pic[i].length(); j++)
		{
			switch(pic[i][j])
			{
			case '@': average+=1;
				break;
			case '#': average+=0.75;
				break;
			case '%': average+=0.5;
				break;
			}
			count++;
		}
	}
	average/=count;
	double verticSize =pic.size()/ 8.0;
	double gorSize = pic[0].length()/7.0;
	for (int i=0; i<8; i++)
	{
		rez[i]="       ";
		for (int j=0; j<7; j++)
		{
			double cvet=0;
			count=0;
			for (int k=i*verticSize; k<(i+1)*verticSize; k++)
			{
				for (int l=j*gorSize; l<(j+1)*gorSize; l++)
				{
					switch(pic[k][l])
					{
					case '@': cvet+=1;
						
						break;
					case '#': cvet+=0.75;
						
						break;
					case '%': cvet+=0.5;
						
						break;
					}
					count++;
				}
			}
			cvet/=count;
			if (cvet>1.25*average) rez[i][j]='@';
			else if(cvet>average) rez[i][j]='#';
			else if(cvet>0.75*average) rez[i][j]='%';
			else rez[i][j]='.';
		}

	}
}
double cTi(char c)
{
	if (c=='.') return 0;
	if (c=='%') return 0.5;
	if (c=='#') return 0.75;
	if (c=='@') return 1;
	return 0;
}
double compare(vector<string> n1, vector<string> n2)
{
	double min=0;
	for (int i=0; i<7; i++)
	{
		for (int j=0; j<5; j++)
		{
			min+=fabs(cTi(n1[i][j])-cTi(n2[i][j]));
		}
	}
	return min;
}

int main()
{
	vector<vector<string> > nums(20);
	vector<string> n0(8);
	n0[0]=".#@@@#.";
	n0[1]="#@...@#";
	n0[2]="@#...#@";
	n0[3]="@#...#@";
	n0[4]="@#...#@";
	n0[5]="@#...#@";
	n0[6]="#@...@#";
	n0[7]=".#@@@#.";
	vector<string> n1(8);
	n1[0]="....#@.";
	n1[1]="...#@@.";
	n1[2]="..#@%@.";
	n1[3]=".%%.%@.";
	n1[4]="....%@.";
	n1[5]="....%@.";
	n1[6]="....%@.";
	n1[7]="....%@.";
	vector<string> n2(8);
	n2[0]=".%@@@%.";
	n2[1]="@#...#@";
	n2[2]=".%..%@%";
	n2[3]="...%@#.";
	n2[4]="..%@#..";
	n2[5]=".%@#...";
	n2[6]="%@#....";
	n2[7]="@@@@@@@";
	vector<string> n3(8);
	n3[0]=".%#@#%.";
	n3[1]="@#...#@";
	n3[2]=".%...#@";
	n3[3]="...#@@%";
	n3[4]="....#@#";
	n3[5]=".....#@";
	n3[6]="@#...#@";
	n3[7]=".%@@@@%";
	vector<string> n4(8);
	n4[0]="#@...#@";
	n4[1]="#@...#@";
	n4[2]="#@...#@";
	n4[3]="#@@@@@@";
	n4[4]="######@";
	n4[5]=".....#@";
	n4[6]=".....#@";
	n4[7]=".....#@";
	vector<string> n5(8);
	n5[0]="#@@@@@@";
	n5[1]="@@%....";
	n5[2]="@#%%%%.";
	n5[3]="@@####.";
	n5[4]=".#####@";
	n5[5]=".....#@";
	n5[6]="##...@@";
	n5[7]=".@@@@@.";
	vector<string> n6(8);
	n6[0]=".%#@#%.";
	n6[1]="#@...##";
	n6[2]="@#.....";
	n6[3]="@#%%%..";
	n6[4]="@@@@@#%";
	n6[5]="@#...@@";
	n6[6]="@#...@@";
	n6[7]="%@@@@#%";
	vector<string> n7(8);
	n7[0]="#@@@@@#";
	n7[1]=".....@#";
	n7[2]="....#@.";
	n7[3]="...#@..";
	n7[4]="..#@...";
	n7[5]="..#@...";
	n7[6]="..#@...";
	n7[7]="..#@...";
	vector<string> n8(8);
	n8[0]=".#@@@#.";
	n8[1]="@#...#@";
	n8[2]="#@...@#";
	n8[3]=".#@@@#.";
	n8[4]="#@%%%@#";
	n8[5]="@#...#@";
	n8[6]="@#...#@";
	n8[7]=".#@@@#.";
	vector<string> n9(8);
	n9[0]="%#@@@%.";
	n9[1]="@@...@#";
	n9[2]="@#...@@";
	n9[3]="@#####@";
	n9[4]=".#####@";
	n9[5]=".....#@";
	n9[6]="#@...#@";
	n9[7]=".#@@@@.";
	vector<string> n10(8);
	n10[0]=".......";
	n10[1]=".......";
	n10[2]=".......";
	n10[3]=".......";
	n10[4]=".......";
	n10[5]=".......";
	n10[6]=".......";
	n10[7]=".......";
	vector<string> n11(8);
	n11[0]=".#@@@..";
	n11[1]="%%@@@..";
	n11[2]="..#@@..";
	n11[3]="..#@@..";
	n11[4]="..#@@..";
	n11[5]="..#@@..";
	n11[6]="..#@@..";
	n11[7]="..@@@%.";
	vector<string> n12(8);
	n12[0]=".......";
	n12[1]=".......";
	n12[2]=".......";
	n12[3]=".......";
	n12[4]=".......";
	n12[5]=".......";
	n12[6]=".......";
	n12[7]=".......";
	vector<string> n13(8);
	n13[0]="%@@@@%.";
	n13[1]="%...@@.";
	n13[2]="...%@#.";
	n13[3]="..#@@%.";
	n13[4]="..%@@@#";
	n13[5]="....@@@";
	n13[6]="....@@#";
	n13[7]="@@##@%.";
	vector<string> n14(8);
	n14[0]="....%@@";
	n14[1]="....@@@";
	n14[2]="...@@@@";
	n14[3]="..@@%@@";
	n14[4]=".@@..@@";
	n14[5]="@@#%@@@";
	n14[6]="....#@@";
	n14[7]=".....@@";
	vector<string> n15(8);
	n15[0]=".#@@@@@";
	n15[1]=".@@###%";
	n15[2]=".@@....";
	n15[3]="%@@@@@.";
	n15[4]="....%@@";
	n15[5]=".....@@";
	n15[6]="#@#.#@%";
	n15[7]=".%@@@%.";
	vector<string> n16(8);
	n16[0]=".......";
	n16[1]=".......";
	n16[2]=".......";
	n16[3]=".......";
	n16[4]=".......";
	n16[5]=".......";
	n16[6]=".......";
	n16[7]=".......";
	vector<string> n17(8);
	n17[0]="@@@@@@@";
	n17[1]="@@%%#@@";
	n17[2]="....#@.";
	n17[3]="....@@.";
	n17[4]="...%@..";
	n17[5]="...@@..";
	n17[6]="...@%..";
	n17[7]="..@@...";

	nums[0]=n0;
	nums[1]=n1;
	nums[2]=n2;
	nums[3]=n3;
	nums[4]=n4;
	nums[5]=n5;
	nums[6]=n6;
	nums[7]=n7;
	nums[8]=n8;
	nums[9]=n9;
	nums[10]=n10;
	nums[11]=n11;
	nums[12]=n12;
	nums[13]=n13;
	nums[14]=n14;
	nums[15]=n15;
	nums[16]=n16;
	nums[17]=n17;
	
	//in.open("in");
	//out.open("out.txt");
	while (!cin.eof())
	{
		string st;
		getline(cin,st);
		if (st=="") break;
		pic.push_back(st);
	}
	vector<int> g=gorizontal();
	firstAnaliz();
	int l=0;
	vector<string> dub;
	while ((l<3)&&(gor[l].first!=gor[l].second))
	{
		dub.clear();
		for (int i=ver[l].first; i<ver[l].second; i++)
		{
			dub.push_back(pic[i].substr(gor[l].first, gor[l].second-gor[l].first));
		}
		convertToSimple(dub);
		/*for (int i=0; i<dub.size(); i++)
		{
			cout<<dub[i].c_str()<<endl;
		}
		
		for (int j=0;j<8;j++)
		{
			out<<rez[j].c_str()<<endl;
		
		}*/
		int mini;
		double min=56;
		for (int i=0; i<18; i++)
		{
			double a=compare(rez, nums[i]);
			if (a<min) {
				min=a;
				mini=i;
			}
		
		}
		l++;
		cout<<(mini%10);
	}
	return 0;
}

