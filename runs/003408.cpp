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
/*
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
*/
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
	//int bonus[10];
	//Set_bonus(scan, bonus);
	for (int i=0; i<10; i++)
	{
		vector<TScan>::iterator it;
		for (it=samples[i].begin(); it!=samples[i].end(); it++)
		{
	
			float dist=Levenstein(scan.g_scan,(*it).g_scan)+Levenstein(scan.v_scan,(*it).v_scan)+fabs((*it).x-scan.x)*100+fabs((*it).y-scan.y)*300;
			float dist1=(1.0*fabs((*it).long_x-scan.long_x)+fabs((*it).long_y-scan.long_y)+fabs((*it).pos_long_x-scan.pos_long_x)+fabs((*it).pos_long_y-scan.pos_long_y))*200+abs(scan.rounds-(*it).rounds)*1000;
			dist+=dist1;
			if (dist<min)
			{
				min=dist;
				num=i;
			}
		}
	}

	//если мы нашли число очень похожее на наше в библиотеке, то его и выводим. если нет, то ищем по очевидным признакам
	return num;
	/*min=100000;
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
	return num; */
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
	//calibri
	Add( 0,"11222222","12222221",0.481453,0.487174,0.785714,0.886364,0.113636,0.821429,1);
	Add( 1,"22211111","11111111",0.456525,0.548863,1.000000,1.000000,0.906977,0.458333,0);
	Add( 2,"22233322","12111111",0.506929,0.515575,1.000000,0.581395,0.906977,0.730769,0);
	Add( 3,"23333332","12111121",0.555228,0.499955,0.884615,0.488372,0.116279,0.769231,0);
	Add( 4,"11222111","11222111",0.525947,0.493543,1.000000,1.000000,0.659091,0.700000,1);
	Add( 5,"12233332","11111121",0.476158,0.480690,0.884615,0.500000,0.045455,0.115385,0);
	Add( 6,"11333332","11122221",0.438582,0.514795,0.962963,0.863636,0.500000,0.222222,1);
	Add( 7,"11222221","11111111",0.538689,0.370996,1.000000,0.477273,0.022727,0.807692,0);
	Add( 8,"12333333","12212221",0.482522,0.493112,0.892857,0.454545,0.909091,0.214286,2);
	Add( 9,"12333331","12221111",0.515508,0.459097,0.925926,0.863636,0.522727,0.814815,1);


	
	//bold
	Add( 0,"11122211","11222211",0.487004,0.490359,0.871795,1.000000,0.180000,0.692308,1);
	Add( 1,"11111111","11121111",0.643611,0.455483,1.000000,1.000000,0.265306,0.629630,0);
	Add( 2,"12223322","11211111",0.526993,0.523793,1.000000,0.653061,0.938776,0.700000,0);
	Add( 3,"22233212","11211121",0.567062,0.492364,0.972973,1.000000,0.183673,0.729730,0);
	Add( 4,"11122111","11122111",0.539162,0.525697,1.000000,1.000000,0.632653,0.595238,0);
	Add( 5,"12233322","11111121",0.496314,0.473778,0.948718,0.666667,0.520833,0.692308,0);
	Add( 6,"11133322","11221221",0.471007,0.498385,0.975000,1.000000,0.520833,0.300000,1);
	Add( 7,"11222111","11111111",0.489849,0.363731,1.000000,0.729167,0.020833,0.615385,0);
	Add( 8,"12133212","11211221",0.481491,0.492639,0.948718,1.000000,0.854167,0.230769,1);
	Add( 9,"12233311","11221221",0.502859,0.480825,0.975000,1.000000,0.500000,0.675000,1);

	//double
	Add(0,"11222222","22233222",0.476476,0.477559,0.736842,0.961538,0.923077,0.315789,1);
	Add( 1,"23322222","11111111",0.485323,0.489858,1.000000,0.923077,1.000000,0.500000,0);
	Add( 2,"33455443","12222112",0.462847,0.473858,1.000000,0.538462,0.884615,0.777778,1);
	Add( 3,"22245322","12221132",0.497713,0.476514,0.833333,0.923077,0.115385,0.777778,1);
	Add( 4,"23346423","11233331",0.469530,0.517040,1.000000,0.730769,0.692308,0.700000,0);
	Add( 5,"12345442","12112232",0.453643,0.472391,0.800000,0.653846,0.038462,0.750000,0);
	Add( 6,"11355332","22212322",0.442342,0.465737,0.789474,0.807692,0.115385,0.210526,1);
	Add( 7,"12444431","12321111",0.456973,0.376003,1.000000,0.607143,0.035714,0.588235,1);
	Add( 8,"12333343","13331232",0.466402,0.505258,0.714286,0.785714,0.500000,0.285714,2);
	Add( 9,"11224331","13232221",0.516046,0.439082,0.894737,0.964286,0.607143,0.789474,1); 

	
	//freaky
	Add( 0,"11333431","12342231",0.463876,0.485701,0.658537,0.824561,0.122807,0.219512,1);
	Add( 1,"11111122","11221111",0.609674,0.430611,1.000000,0.982456,0.105263,0.800000,0);
	Add( 2,"23444321","12421121",0.466605,0.547723,1.000000,0.553571,0.928571,0.638889,0);
	Add( 3,"13233422","11111122",0.542881,0.477033,0.853659,0.607143,0.071429,0.731707,0);
	Add( 4,"13122111","12131221",0.451946,0.500434,0.977273,0.686567,0.567164,0.318182,0);
	Add( 5,"12235422","12112122",0.527655,0.510584,0.769231,0.589286,0.089286,0.358974,0);
	Add( 6,"11245321","11112332",0.465808,0.540740,0.710526,0.642857,0.946429,0.157895,0);
	Add( 7,"12323211","11122221",0.510806,0.402209,1.000000,0.559322,0.084746,0.702703,0);
	Add( 8,"12444321","12213411",0.488850,0.532358,0.894737,0.912281,0.859649,0.763158,2);
	Add( 9,"22222241","22223211",0.607058,0.407315,0.850000,1.000000,0.508772,0.800000,1);
	//narrow
	Add( 0,"11122221","12222221",0.450394,0.481220,0.800000,1.000000,0.103448,0.300000,1);
	Add( 1,"22111111","11111111",0.285271,0.515477,1.000000,1.000000,1.000000,0.500000,0);
	Add( 2,"22222222","12111121",0.437282,0.501402,1.000000,0.620690,0.103448,0.714286,0);
	Add( 3,"23333312","12111121",0.504167,0.490781,0.800000,1.000000,0.068966,0.700000,0);
	Add( 4,"11233111","11123111",0.487273,0.512330,1.000000,1.000000,0.655172,0.600000,1);
	Add( 5,"22233322","21111121",0.443311,0.474783,1.000000,0.655172,0.068966,0.777778,0);
	Add( 6,"11133332","12112221",0.392877,0.498536,0.900000,1.000000,0.413793,0.300000,1);
	Add( 7,"11222311","12111111",0.419172,0.412170,1.000000,0.724138,0.034483,0.555556,0);
	Add( 8,"22133331","12212221",0.448227,0.481617,0.800000,1.000000,0.068966,0.300000,2);
	Add( 9,"22233331","12221121",0.487047,0.461051,0.900000,1.000000,0.586207,0.800000,1);



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
	//FILE* newfile;
	//newfile=fopen("new.txt","w");
	while (end>0)
	{
		Trim_number(begin,end,&top,&bottom);
		TScan scan;
		Get_scan(&scan.v_scan,&scan.g_scan,top,bottom,begin,end);
		Weight(&scan.x,&scan.y,begin,end,top,bottom);
		Get_long(&scan,begin,end,top,bottom);
		Number_of_rounds(&scan,begin,end,top,bottom);
		//fprintf(newfile,"Add( ,\"%s\",\"%s\",%f,%f,%f,%f,%f,%f,%d);\n",scan.v_scan.c_str(), scan.g_scan.c_str(),scan.x,scan.y,scan.long_x, scan.long_y, scan.pos_long_x,scan.pos_long_y,scan.rounds);
		int answer=Recognize(scan);
		printf("%d",answer);
		begin=end+1;
		end=Get_boundaries(&begin);
	}
	//fclose(newfile);
	return 0;
}