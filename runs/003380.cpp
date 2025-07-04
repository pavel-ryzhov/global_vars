//программа по распознаванию цифр. сырая пробная версия.
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;

typedef vector <vector <char> > TNumber;
bool visited[200][200];
TNumber Number;
int Width, Height;

struct TScan
{
	string v_scan, g_scan;
	float x,y;
	float long_x, long_y; //относительная длина самого длинного отрезка
	float pos_long_x, pos_long_y; //относительная координата самого длинного отрезка
	int rounds;
};

vector<TScan> samples[10];

//функция возвращает конец и изменяет начальный столбец (границы цифры) 
int Get_boundaries(int *begin)
{
	if (*begin>=Width) return 0;
	bool no_black=true;
	bool black_near;
	int end;
	//начнем искать левую границу числа
	while (no_black)
	{
		int j=0;
		black_near=false;
		while ((j<Height)&&(no_black))
		{
			if (Number[j][(*begin)]=='@') no_black=false;
			if ((*begin+1==Width)||(Number[j][(*begin)+1]=='@')) black_near=true;
			j++;
		}
		if (no_black)
		{
			if (black_near) no_black=false;
			*begin+=1;
			if (*begin>=Width) return 0; //мы дошли до конца числа, не нашли небелые ячейки - чисел больше нету.
		}
	}

	//теперь в begin хранится левая граница числа.
	//ищем правую.
	end=*begin+1;
	no_black=false;
	while (!no_black)
	{
		no_black=true;
		int j=0;
		while ((no_black)&&(j<Height))
		{
			if ((end<Width)&&(Number[j][end]=='@')) no_black=false;
			j++;
		}
		end++;
	}
	end-=2;
	return end;

}

void Trim_number(int begin, int end, int* top, int* bottom)
{
	
	bool no_black=true;
	while (no_black)
	{
		int j=begin;
		while ((no_black)&&(j<end))
		{
			if (Number[*top][j]!='.') no_black=false;
			j++;
		}
		if (no_black) *top+=1;
	}
	no_black=true;
	while (no_black)
	{
		int j=begin;
		while ((no_black)&&(j<end))
		{
			if (Number[*bottom][j]!='.') no_black=false;
			j++;
		}
		if (no_black) *bottom-=1;
	}
}

void Get_scan(string* v_scan, string* g_scan, int top, int bottom, int begin, int end)
{
	int g_step=(bottom-top)/7;
	int v_step=(end-begin)/7;
	if (v_step==0) v_step=(end-begin)/3;
	if (v_step==0) v_step=1;
	//горизонтальное сканирование
	for (int i=top; (i<=bottom)&&((*g_scan).length()<8); i=i+g_step)
	{
		int k=0;
		for (int j=begin; j<end; j++)
		{
			if ((Number[i][j]!='.')&&(Number[i][j+1]=='.')) k++;
		}
		if (Number[i][end]!='.') k++; //если последний элемент черный, то тоже переход
		char c= k + '0';
		//if ((*g_scan).length()==0) *g_scan+=c;
		//else if ((*g_scan)[(*g_scan).length()-1]!=c) *g_scan+=c;
		*g_scan+=c;
	}
	//вертикальное сканирование
	for (int j=begin; (j<=end)&&((*v_scan).length()<8); j=j+v_step)
	{
		int k=0;
		for (int i=top; i<bottom; i++)
		{
			if ((Number[i][j]!='.')&&(Number[i+1][j]=='.')) k++;
		}
		if (Number[bottom][j]!='.') k++; //если последний элемент черный, то тоже переход
		char c=k + '0';
		*v_scan+=c;
		if (end-begin<7) *v_scan+=c;
	}

}

int M_function(char x,char y)
{if (x==y) return 0; else return 1; }
 

int Levenstein(string s1,string s2)
{
	int m=s1.length();
	int n=s2.length();
	vector <vector <int> > d;
	d.resize(m+1);
	for (int i=0; i<=m; i++) 
		d[i].resize(n+1);
	d[0][0]=0;
	for (int j=1; j<=n; j++)
		d[0][j] = d[0][j-1] + 1;
 	for (int i=1; i<=m; i++)
	{
		d[i][0] =d[i-1][0] + 1;
		for (int j=1; j<=n; j++)
		{
			d[i][j] = min(d[i-1][j] + 1,d[i][j-1] + 1);
			d[i][j]=min(d[i][j],d[i-1][j-1] + M_function(s1[i-1],s2[j-1]));
		}
    }
 return d[m][n];

}

void Weight(float *x, float *y, int begin, int end, int top, int bottom) //считаем центр масс
{
	int mass_x=0, mass_y=0, mass=0;
	map<char,int> w;
	w['.']=0; w['@']=3; w['#']=2; w['%']=1;
	for (int i=top; i<=bottom; i++)
	{
		for (int j=begin; j<=end; j++)
		{
			mass+=w[Number[i][j]];
			mass_x+=(j-begin)*w[Number[i][j]];
			mass_y+=(i-top)*w[Number[i][j]];
		}
	}
	*x=1.0*(mass_x-begin+1)/mass/(end-begin+1);
	*y=1.0*(mass_y-top+1)/mass/(bottom-top+1);
}

void Get_long(TScan* scan, int begin, int end, int top, int bottom)
{
	int max_x=0, max_y=0;
	float pos_x=0.0, pos_y=0.0;
	for (int i=top; i<=bottom; i++)
	{
		int k=0;
		bool count=false;
		int j=begin;
		while (j<=end)
		{
			if (Number[i][j]!='.')
			{
				k++;
				if (!count) count=true;
			}
			else
			{
				if (count)
				{
					count=false;
					if (k>max_x)
					{
						max_x=k;
						pos_x=i;
					}
					k=0;
				}
			}
			j++;
			if ((j>end)&&(count)) 
			{
				if (k>max_x) {max_x=k; pos_x=i;}
			}
		}
	}
	(*scan).long_x=max_x*1.0/(end-begin+1);
	(*scan).pos_long_x=1.0*(pos_x-top+1)/(bottom-top+1);
	for (int j=begin; j<=end; j++)
	{
		int k=0;
		bool count=false;
		int i=top;
		while (i<=bottom)
		{
			if (Number[i][j]!='.')
			{
				k++;
				if (!count) count=true;
			}
			else
			{
				if (count)
				{
					count=false;
					if (k>max_y)
					{
						max_y=k;
						pos_y=j;
					}
					k=0;
				}
			}
			i++;
			if ((i>bottom)&&(count)) 
			{
				if (k>max_y) {max_y=k; pos_y=j;}
			}
		}
	}
	(*scan).long_y=max_y*1.0/(bottom-top+1);
	(*scan).pos_long_y=1.0*(pos_y-begin+1)/(end-begin+1);
}
 
void Add(int num, string v_scan, string g_scan, float x, float y,float long_x, float long_y, float long_pos_x, float long_pos_y, int rounds)
{
	TScan sc;
	sc.g_scan=g_scan;
	sc.v_scan=v_scan;
	sc.x=x;
	sc.y=y;
	sc.long_x=long_x;
	sc.pos_long_x=long_pos_x;
	sc.long_y=long_y;
	sc.pos_long_y=long_pos_y;
	sc.rounds=rounds;
	samples[num].push_back(sc);
}

void Set_bonus(TScan scan, int bonus[10])
{
	for (int i=0; i<10; i++) bonus[i]=0;
	//зададим прибавку или вычитание к дистанции в зависимости от особенности числа.
	if (scan.long_y>0.7) //если имеется длинный отрезок по вертикали
	{
		if (scan.long_y>0.98) { bonus[1]-=100; bonus[4]-=100;}
		//в любом случае в таком случае надо увеличить бонусы для 1 и 0
		bonus[1]-=100;
		bonus[0]-=100;
		bonus[5]-=100;
		int sign=1;
		if (scan.pos_long_y<0.5)
		{
			sign=-1;
		}
		//если вертикальный отрезок находится слева, то это
		//5,6 - вероятно
		//2,3,4,7,9
		bonus[6]+=sign*100;
		bonus[2]+=-sign*100;
		bonus[3]+=-sign*100;
		bonus[4]+=-sign*100;
		bonus[7]+=-sign*100;
		bonus[9]+=-sign*100;
	}
	if (scan.long_x>0.9) //если есть длинный отрезок по горизонтали
	{
		if (scan.pos_long_x<0.25)  //самый длинный отрезок в числе находится в верхней четверти числа. 
		{
			//это могут быть 5 или 7
			bonus[7]+=-100;
		}
		else 
		{
			bonus[7]+=100;
		}
		if (scan.pos_long_x>0.75)
		{
			//самый длинный горизонтальный отрезок в нижней четверти числа
			//это может быть 1,2,4,
			bonus[1]+=-100;
			bonus[2]+=-100;
			bonus[4]+=-100;
		}
		else
		{
			bonus[1]+=100; bonus[2]+=100;
		}
	}
	switch (scan.rounds)
	{
	case 0:
		bonus[1]+=-100;
		bonus[2]+=-100;
		bonus[3]+=-100;
		bonus[4]+=-100;
		bonus[5]+=-100;
		bonus[7]+=-100;
		break;
	case 1:
		bonus[4]+=-100;
		bonus[6]+=-100;
		bonus[9]+=-100;
		bonus[0]+=-100;
		break;
	case 2:
		bonus[8]+=-100;
		break;
	}

}

int Find_components(int* square,int i, int j, int begin, int end, int top, int bottom)
{
	visited[i][j]=true; 
	(*square)+=1;
	if ((j==begin)||(j==end)||(i==top)||(i==bottom)) return 0;
	int answer=1;
	if ((Number[i][j+1]=='.')&&(!visited[i][j+1]))
	{
		answer*=Find_components(square,i,j+1,begin,end,top,bottom); 
	}
	if ((Number[i][j-1]=='.')&&(!visited[i][j-1]))
	{
		answer*=Find_components(square,i,j-1,begin,end,top,bottom);
	}
	if ((Number[i+1][j]=='.')&&(!visited[i+1][j]))
	{
		answer*=Find_components(square,i+1,j,begin,end,top,bottom);
	}
	if ((Number[i-1][j]=='.')&&(!visited[i-1][j]))
	{
		answer*=Find_components(square,i-1,j,begin,end,top,bottom);
	}
	return answer;
}

void Number_of_rounds(TScan* scan, int begin, int end, int top, int bottom)
{
	for (int i=top; i<=bottom; i++)
		for (int j=begin; j<=end; j++)
			visited[i][j]=false;
	int k=0;
	for (int i=top; i<=bottom; i++)
	{
		for (int j=begin; j<=end; j++)
		{
			int square_all=(end-begin+1)*(bottom-top+1),square=0, is_component=0;
			if ((!visited[i][j])&&(Number[i][j]=='.')&&(j>begin)&&(Number[i][j-1]!='.')) 
			{
				is_component=Find_components(&square,i,j,begin,end,top,bottom);
				if ((is_component==1)&&(1.0*square/square_all>0.05)) k++;
			}
		}
	}
	(*scan).rounds=k;
}


int Recognize(TScan scan)
{
	float min=100000;
	int num=0;
	int bonus[10];
	Set_bonus(scan, bonus);
	for (int i=0; i<10; i++)
	{
		vector<TScan>::iterator it;
		for (it=samples[i].begin(); it!=samples[i].end(); it++)
		{
	
			float dist=Levenstein(scan.g_scan,(*it).g_scan)+Levenstein(scan.v_scan,(*it).v_scan)+fabs((*it).x-scan.x)*100+fabs((*it).y-scan.y)*100;
			float dist1=(1.0*fabs((*it).long_x-scan.long_x)+fabs((*it).long_y-scan.long_y)+fabs((*it).pos_long_x-scan.pos_long_x)+fabs((*it).pos_long_y-scan.pos_long_y))*100;
			dist+=dist1;
			if (dist<min)
			{
				min=dist;
				num=i;
			}
		}
	}

	//если мы нашли число очень похожее на наше в библиотеке, то его и выводим. если нет, то ищем по очевидным признакам
	if (min<10) return num;
	min=100000;
	num=0;
	for (int i=0; i<10; i++)
	{
		vector<TScan>::iterator it;
		for (it=samples[i].begin(); it!=samples[i].end(); it++)
		{
	
			float dist=Levenstein(scan.g_scan,(*it).g_scan)+Levenstein(scan.v_scan,(*it).v_scan)+fabs((*it).x-scan.x)*700+fabs((*it).y-scan.y)*700;
			float dist1=(1.0*fabs((*it).long_x-scan.long_x)+fabs((*it).long_y-scan.long_y)+fabs((*it).pos_long_x-scan.pos_long_x)+fabs((*it).pos_long_y-scan.pos_long_y))*100+abs(scan.rounds-(*it).rounds)*5;
			dist+=dist1;
			dist+=bonus[i];
			if (dist<min)
			{
				min=dist;
				num=i;
			}
		}
	}
	return num;
}


int main()
{
	Add(1,"22111111","11111111",0.4259,0.4963,1,1,1,0.4286,0);
	
	Add(2,"12223222","11211111",0.5247,0.5154,1,0.6444,0.9556,0.7027,0); Add(2,"12333332","12211111",0.5021, 0.5228, 1, 0.4762, 0.9524, 0.8696,0);
	
	Add(3,"12233332","12111122",0.5698,0.5, 0.6956, 0.4762, 0.9524,0.8696,0);

	Add(4,"11122211","11222111",0.4767, 0.5193, 1, 0.7428, 0.5714, 0.75,1); 
	
	Add(5,"12233322","11112121",0.5077,0.4691,0.8947,0.6522,0.5,0.7105,0); 	Add(5,"13233222","11212222",0.5837,0.5363,0.7368,0.7983,0.041,0.5265,0); Add(5,"12333333","11112112",0.4658, 0.4592, 0.8571, 0.4, 0.1, 0.1428, 0);
	
	Add(6,"11111133","12112222",0.3555,0.4936,0.85,1,0.4,0.45,1); Add(6,"11123311","11112222",0.4515,0.5934,0.7333,0.6428,0.8571,0.2917,1);

	Add(7,"11222211","11111111",0.4572,0.3320,1,0.3478,0.0434,0.4667,0); Add(7,"22222222","12211111",0.3937,0.4636,1,0.5625,1,0.0313,0); Add(7,"11222221","11111111",0.4882, 0.3507,1,0.4286,0.0238,0.3913,0);

	Add(8,"22233222","12221222",0.4726,0.4959,0.75,0.9143,0.4857,0.3333,2);
	
	Add(9,"22333331","12221121",0.4783,0.4873,0.875,0.7826,0.5662,0.8750,1);

	Add(0,"11111122","22222222",0.3457,0.4704,0.55,1,0.25, 0.4,1); 
	
	int i=0, j;
	Number.resize(200);
	for (int k=0; k<200; k++)
	{
		Number[k].resize(200);
	}
	char c;
	while (scanf("%c",&c)==1)
	{
		j=0;
		while (c!='\n')
		{
			Number[i][j]=c;
			j++;
			scanf("%c",&c);
		}
		i++;
	}
	Height=i;
	Width=j;
	int top=0, bottom=Height-1;
	int begin=0, end=Get_boundaries(&begin);
	while (end>0)
	{
		Trim_number(begin,end,&top,&bottom);
		TScan scan;
		Get_scan(&scan.v_scan,&scan.g_scan,top,bottom,begin,end);
		Weight(&scan.x,&scan.y,begin,end,top,bottom);
		Get_long(&scan,begin,end,top,bottom);
		Number_of_rounds(&scan,begin,end,top,bottom);
		int answer=Recognize(scan);
		printf("%d",answer);
		begin=end+1;
		end=Get_boundaries(&begin);
	}
	return 0;
}