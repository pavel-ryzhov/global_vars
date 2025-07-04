#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<vector>
using namespace std;


void transfStr(char s[])
{
	if( s[strlen(s)-1] == '\n')
			s[strlen(s)-1] = '\0';
}


vector<vector<float> > picture; /*картинка*/
vector<vector<float> > ws;
vector<float> v_in; // входной вектор
vector<float> d; // желаемый вектор
float eta = 1; // скорость обучени€
float numE = 2.718; // число e

vector<float> errorMax;// пороговое значение ошибки
vector<float> errorSum; // ошибка накоплени€


int neuro_wid = 10;
vector<int> borders;


/**********************/
/* Learning neuro_net */
/*********************/
void initialize_errorSum()
{
	for(size_t i=0; i<10;i++)
		errorSum.push_back(0);
}
void initialize_ws()
{
	for(size_t i=0; i<ws.size();i++)
	{
		vector<float> w1;
		for(size_t j=0;j<ws[i].size();j++)
		   w1.push_back(0.1);//(rand()/1000.);
	ws[i] = w1;
	}
}


void initialize_vector_in(int start, int wd, int lastWd, int ht, int lastHt)
{

	int y=0, x=0;
	float sum = 0;
	while(y<neuro_wid-1)
	{
		x=0;
		while(x<3)
		{
			sum = 0;
			for(int i = x*wd + start; i<x*wd + start+wd; i++)
			{			
				for(int j = y*ht; j<y*ht + ht; j++)
					sum = sum+ picture[j][i];
			}
			sum = sum/(wd*ht);
			v_in.push_back(sum);
			x++;
		}

		sum = 0;
			for(int i = x*wd + start; i<x*wd + start+lastWd; i++)
			{			
				for(int j = y*ht; j<y*ht + ht; j++)
					sum = sum+ picture[j][i];
			}
			sum = sum/(lastWd*ht);
			v_in.push_back(sum);

		y++;
	}


	x=0;
	while(x<3)
		{
			sum = 0;
			for(int i = x*wd + start; i<x*wd + start+wd; i++)
			{			
				for(int j = y*ht; j<y*ht + lastHt; j++)
					sum = sum+ picture[j][i];
			}
			sum = sum/(wd*lastHt);
			v_in.push_back(sum);
			x++;
		}

		sum = 0;
			for(int i = x*wd + start; i<x*wd + start+lastWd; i++)
			{			
				for(int j = y*ht; j<y*ht + lastHt; j++)
					sum = sum+ picture[j][i];
			}
			sum = sum/(lastWd*lastHt);
			v_in.push_back(sum);

}


void scalar_product(vector<float>& v)
{
	float sum = 0;
	for(size_t i=0; i<ws[0].size(); i++)
	{
		sum = 0;
		for(size_t j=0; j<v_in.size(); j++)
		sum = sum + v_in[j]*ws[j][i];

		v.push_back(sum);
	}
}


void func_activation(vector<float>& v)
{
	for(size_t i=0; i<v.size(); i++)
	{
		v[i] = 1/(1+(float)pow(numE, -v[i]));
	}
}

void get_errorVector(vector<float> v, vector<float> d, vector<float>& v_err)
{
	float res;
	for(size_t i=0; i<v.size(); i++)
	{
		res = -(d[i]-v[i])*(v[i]*(1-v[i]));
		v_err.push_back(res);
	}
	
}

bool weight_correction(vector<float> v, vector<float> d)
{
	for(size_t i=0; i<v.size(); i++)
	{
		for(size_t j=0; j<ws.size(); j++)
		ws[j][i] = ws[j][i] + eta*(d[i]-v[i])*v[i]*(1-v[i])*v_in[j];

		
	}
		return true;
}

void calculate_errorSum(vector<float> v, vector<float> d)
{
	for(size_t i=0; i<errorSum.size(); i++)
	{
		errorSum[i] = errorSum[i] + 0.5*(d[i] - v[i])*(d[i]-v[i]);
	}
}

bool check_errorSum()
{
	for(size_t i=0; i<errorSum.size(); i++)
	{
		if(errorSum[i] > errorMax[i])
			return false;
	}

	return true;
}

void read_picture()
{
	char s[100000];
	int k=0, n = 0;
	while(k<5)
	{
		gets(s);
		k++;
	}

	size_t len = 0;
	k = 0;
	while(1)
	{
		gets(s);
		transfStr(s);
		len = strlen(s);
		vector<float> v;
		k = 0;
			for(size_t i=5; i<len-5; i++)
			{
				switch(s[i])
				{
				case '.': k++; v.push_back(0); break;
				case '%': k = 0; v.push_back(0.5); break;
				case '#': k = 0; v.push_back(0.7); break;
				case '@': k = 0; v.push_back(1); break;
				}				
			}

			if(k == len-10)
			{
				n++;
				if(n == 5)
				break;
			}

     picture.push_back(v);

	}

	k=0;
	while(k<4)
	{
		picture.pop_back();
		k++;
	}

}




void write_weights_in_file()
{
	FILE*fs = fopen("weights.txt","a");
	fputs("\n\n/****XXX********/\n\n", fs);
	for(size_t i=0; i<ws.size(); i++)
	{
		for(size_t j=0; j<ws[i].size(); j++)
		{
			fprintf(fs, "%f, ", ws[i][j]);
		}
		fprintf(fs, "\n");
	}
	fputs("\n/************/", fs);
	fclose(fs);

}

int get_answer(vector<float> v);
int check_digit_amount()
{
	int x = 0;
	bool flagDigit = false;
	bool flagBorder = false;
	bool flagPrevious = true;
	size_t len = picture[0].size();
	borders.push_back(0);
	for(size_t j=4; j<len-4; j++)
	{
		flagDigit = false;
		for(size_t i = 0; i<picture.size(); i++)
		{
			if(picture[i][j] == 1.)
			{ flagDigit = true; 
			if(!flagPrevious) borders.push_back(j);
			flagPrevious = true;}
		}
		if(!flagDigit)
		{	//flagBorder = true;
			if(flagPrevious) 
			{x++; flagPrevious = false;
			 borders.push_back(j);}
		}
	}
	borders.push_back(len);
	
	return x+1;

}

void read_picture(FILE*fs)
{
	char s[100000];
	int k=0;
	while(k<5)
	{
		fgets(s,999,fs);
		k++;
	}

	size_t len = 0;
	while(fgets(s,999,fs) != NULL)
	{
		transfStr(s);
		len = strlen(s);
		vector<float> v;
			for(size_t i=5; i<len-5; i++)
			{
				switch(s[i])
				{
				case '.': v.push_back(0); break;
				case '%': v.push_back(0.5); break;
				case '#': v.push_back(0.7); break;
				case '@': v.push_back(1.); break;
				}				
			}
     picture.push_back(v);

	}

	k=0;
	while(k<5)
	{
		picture.pop_back();
		k++;
	}

}

void learning_neuronet()
{
	char file[100] = "001";
	int answer = 0;
	
	int x = 4, y = neuro_wid;
	ws.resize(x*y);
	for(size_t i=0; i<ws.size(); i++) ws[i].resize(10);
	initialize_ws();

	while(1)
	{
	puts("\nwrite file (q - to exit, w - to save weights in file):");
	gets(file);
	if(strcmp(file, "q") == 0) break;
	if(strcmp(file, "w") == 0) { write_weights_in_file(); continue;}

	FILE*fs = fopen(file,"r");
	if(fs == 0)
	{
		printf("File %s can't be opened!", file);
		continue;
	}
	
	picture.clear();
	read_picture(fs);
	int pictWidth = picture[0].size();
	int pictHeight = picture.size();

	int digit_wd = 0, digit_wdLast = 0, wd = 0, lastWd = 0;

	borders.clear();
	int dg_num = check_digit_amount();
	if(dg_num == 1 && pictWidth>70)
	{ 
	dg_num = 3;
	
	digit_wd = pictWidth/dg_num;
	digit_wdLast = digit_wd + pictWidth%dg_num;
	borders.clear();
	borders.push_back(0);
	borders.push_back(digit_wd);
	borders.push_back(digit_wd);
	borders.push_back(2*digit_wd);
	borders.push_back(2*digit_wd);
	borders.push_back(2*digit_wd+digit_wdLast);
	}

	int ht = pictHeight/neuro_wid;
	int lastHt = ht + pictHeight%neuro_wid;

	int step = 0, start = 0, end = 0;
		while(step < dg_num)
		{
		puts("answer:");
		gets(file);
		answer = atoi(file);

		d.clear();
		d.resize(10, -1);
		d[answer] = 1;
		v_in.clear();

		start = borders[2*step];
		wd = (borders[2*step+1] - start)/4;
		lastWd = wd + (borders[2*step+1] - start)%4;
		initialize_vector_in(start, wd, lastWd, ht, lastHt); 

		while(1)
			{
			vector<float> v_temp;
			scalar_product(v_temp);
			func_activation(v_temp);
			int ans = get_answer(v_temp);
			if(ans == answer) break;
			else puts("error...");

			bool res = weight_correction(v_temp, d);
			}
		step++;
		}
	
	}
	//write_weights_in_file();
}

/***************************************/
double arr_weights[] = 
{-0.113525, -0.124421, -0.125485, -0.131975, -0.144245, -0.119901, -0.089554, -0.012286, -0.106955, -0.083192, 
-0.371452, -0.420907, -0.370776, -0.359987, -0.454463, -0.396532, -0.401871, -0.336373, -0.409280, -0.366898, 
-0.531105, -0.532344, -0.531266, -0.499249, -0.603878, -0.512630, -0.546792, -0.507570, -0.535577, -0.542346, 
-0.317196, -0.325727, -0.296752, -0.319183, -0.314719, -0.210214, -0.255523, -0.225579, -0.334577, -0.318221, 
-0.256917, -0.227650, -0.278166, -0.249587, -0.317403, -0.283510, -0.258872, -0.230524, -0.272936, -0.240167, 
-0.410268, -0.367344, -0.413210, -0.391502, -0.472337, -0.349372, -0.396591, -0.411421, -0.459295, -0.464903, 
-0.431325, -0.356128, -0.349676, -0.404559, -0.414600, -0.347477, -0.388421, -0.379557, -0.428041, -0.408754, 
-0.368288, -0.399314, -0.323119, -0.342971, -0.382796, -0.344420, -0.352278, -0.319244, -0.385706, -0.380837, 
-0.262964, -0.307843, -0.272738, -0.257398, -0.342611, -0.308273, -0.285941, -0.324033, -0.277465, -0.264645, 
-0.291884, -0.265284, -0.219574, -0.317154, -0.287153, -0.217336, -0.294185, -0.329395, -0.265674, -0.310711, 
-0.228644, -0.151069, -0.196016, -0.222778, -0.157225, -0.194586, -0.195107, -0.234678, -0.197924, -0.188090, 
-0.268597, -0.298449, -0.208770, -0.215499, -0.278536, -0.332152, -0.312835, -0.265270, -0.265639, -0.246752, 
-0.257674, -0.328441, -0.278853, -0.312476, -0.328668, -0.244647, -0.289901, -0.327080, -0.237434, -0.237273, 
-0.314433, -0.291802, -0.287088, -0.359497, -0.284093, -0.201485, -0.322231, -0.356375, -0.274730, -0.294322, 
-0.318619, -0.249727, -0.271104, -0.319426, -0.236099, -0.217898, -0.288810, -0.314186, -0.287929, -0.263496, 
-0.331421, -0.364545, -0.294266, -0.279612, -0.347026, -0.377691, -0.356200, -0.331518, -0.312228, -0.305075, 
-0.140153, -0.220585, -0.230061, -0.207317, -0.219954, -0.217998, -0.155562, -0.213716, -0.157838, -0.131757, 
-0.261795, -0.239006, -0.292222, -0.304425, -0.219349, -0.261802, -0.217568, -0.296796, -0.199979, -0.243524, 
-0.391435, -0.320139, -0.357480, -0.356321, -0.321667, -0.347391, -0.288132, -0.337101, -0.363415, -0.378552, 
-0.348890, -0.386422, -0.328635, -0.316251, -0.364590, -0.328049, -0.361806, -0.381980, -0.375804, -0.317627, 
-0.115925, -0.199040, -0.215936, -0.187802, -0.178893, -0.212372, -0.098335, -0.187651, -0.184148, -0.106404, 
-0.291997, -0.264925, -0.325070, -0.293330, -0.256339, -0.310162, -0.278069, -0.319149, -0.190611, -0.262418, 
-0.533848, -0.453877, -0.469281, -0.438627, -0.469335, -0.508377, -0.479164, -0.446011, -0.413652, -0.492771, 
-0.303163, -0.342050, -0.313030, -0.298478, -0.318831, -0.290247, -0.304556, -0.353142, -0.358370, -0.226917, 
-0.101085, -0.183402, -0.168151, -0.198332, -0.102481, -0.191241, -0.094397, -0.172886, -0.132071, -0.173324, 
-0.323298, -0.299587, -0.322972, -0.350712, -0.329271, -0.374497, -0.305891, -0.338582, -0.281431, -0.201563, 
-0.528440, -0.457766, -0.479664, -0.485049, -0.474950, -0.550857, -0.462253, -0.445966, -0.421034, -0.362351, 
-0.311036, -0.349615, -0.353680, -0.290937, -0.296852, -0.292000, -0.295931, -0.361147, -0.328988, -0.270713, 
-0.158630, -0.235848, -0.194885, -0.260286, -0.137031, -0.201068, -0.174558, -0.229580, -0.137560, -0.282347, 
-0.254020, -0.231343, -0.219069, -0.276681, -0.253916, -0.303555, -0.202722, -0.232887, -0.264669, -0.312189, 
-0.304292, -0.237446, -0.266528, -0.290921, -0.204285, -0.326589, -0.240914, -0.251523, -0.264350, -0.245232, 
-0.314131, -0.343065, -0.381175, -0.269251, -0.294868, -0.292239, -0.300873, -0.353828, -0.272348, -0.282318, 
-0.269986, -0.339400, -0.263095, -0.274141, -0.288015, -0.309683, -0.276219, -0.341730, -0.245410, -0.369467, 
-0.275145, -0.272189, -0.219100, -0.347809, -0.281012, -0.337429, -0.255919, -0.252408, -0.332882, -0.301379, 
-0.181563, -0.121345, -0.181921, -0.177230, -0.089679, -0.204403, -0.190763, -0.156423, -0.153051, -0.122782, 
-0.311590, -0.343761, -0.355098, -0.248971, -0.270892, -0.280452, -0.318946, -0.352197, -0.291786, -0.306892, 
-0.278741, -0.289338, -0.210507, -0.221086, -0.310896, -0.190919, -0.298941, -0.303196, -0.229374, -0.245127, 
-0.448025, -0.441485, -0.449588, -0.482044, -0.553393, -0.453709, -0.391552, -0.418771, -0.493777, -0.499024, 
-0.366281, -0.323114, -0.303333, -0.351207, -0.345867, -0.326164, -0.392843, -0.416965, -0.377342, -0.357763, 
-0.298842, -0.303388, -0.207045, -0.252073, -0.270290, -0.258019, -0.293426, -0.332511, -0.274464, -0.296187};

/***************************************/
int get_answer(vector<float> v)
{
	int max = 0;
	for(size_t i = 0; i<v.size(); i++)
	{
		if(v[i] >= v[max])
			max = i;
	}

	return max;
}
void number_recognition()
{
	
	int answer = 0;
	
	picture.clear();
	read_picture();
	int pictWidth = picture[0].size();
	int pictHeight = picture.size();

	int digit_wd = 0, digit_wdLast = 0, wd = 0, lastWd = 0;

	borders.clear();
	int dg_num = check_digit_amount();
	if(dg_num == 1 && pictWidth>70)
	{ 
	dg_num = 3;

	digit_wd = pictWidth/dg_num;
	digit_wdLast = digit_wd + pictWidth%dg_num;

	borders.clear();
	borders.push_back(0);
	borders.push_back(digit_wd);
	borders.push_back(digit_wd);
	borders.push_back(2*digit_wd);
	borders.push_back(2*digit_wd);
	borders.push_back(2*digit_wd+digit_wdLast);
	}

	int ht = pictHeight/neuro_wid;
	int lastHt = ht + pictHeight%neuro_wid;

	int step = 0, start = 0, end = 0;
		while(step < dg_num)
		{

		d.clear();
		d.resize(10, -1);
		d[answer] = 1;
		v_in.clear();

		start = borders[2*step];
		wd = (borders[2*step+1] - start)/4;
		lastWd = wd + (borders[2*step+1] - start)%4;
	
		initialize_vector_in(start, wd, lastWd, ht, lastHt); 
		
			vector<float> v_temp;
			scalar_product(v_temp);
			func_activation(v_temp);
			
			answer = get_answer(v_temp);
			printf("%d", answer);
			
		step++;
		}
	
	

}
/***************************************/

int main()
{
	
	int x = 4, y = neuro_wid;
	ws.clear();
	ws.resize(x*y);
	for(size_t i=0; i<ws.size(); i++) ws[i].resize(10);

	/* веса (массив arr_weights) получены в результате обучени€ сети на примерах
	из задани€*/
	int k = 0;
	for(size_t i=0; i<ws.size();i++)
	{
		vector<float> w1;
		for(size_t j=0;j<ws[i].size();j++, k++)
		   w1.push_back((float)arr_weights[k]);
	ws[i] = w1;
	}
	
	//learning_neuronet();

	number_recognition();

	return 0;
}
