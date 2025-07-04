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
float eta = 1; // скорость обучения
float numE = 2.718; // число e
vector<float> identityMtx;// единичная матрица
vector<float> errorMax;// пороговое значение ошибки
vector<float> errorSum; // ошибка накопления


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
	while(y<4)
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
	float res;
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
	bool flag = false;
	
		vector<float> v_err;
		v_err.clear();
		get_errorVector(v, d, v_err);
	
	for(size_t i=0; i<ws.size(); i++)
	{
	for(size_t j=0; j<ws[i].size(); j++)
		ws[i][j] = ws[i][j] - eta*v_err[j]*v_in[i];
	}
		return flag;
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
	for(size_t i=0; i<ws.size(); i++)
	{
		for(size_t j=0; j<ws[i].size(); j++)
		{
			fprintf(fs, "%f, ", ws[i][j]);
		}
		fprintf(fs, "\n");
	}
	fputs("/************/", fs);

}

int get_answer(vector<float> v);
int check_digit_amount()
{
	int x = 0;
	bool flagDigit = false;
	bool flagBorder = false;
	bool flagPrevious = true;
	size_t len = picture[0].size();
	for(size_t j=4; j<len-4; j++)
	{
		flagDigit = false;
		for(size_t i = 0; i<picture.size(); i++)
		{
			if(picture[i][j] == 1.)
			{ flagDigit = true; flagPrevious = true;}
		}
		if(!flagDigit)
		{	//flagBorder = true;
			if(flagPrevious) {x++; flagPrevious = false;}
		}
	}

	
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
	
	/*int x = 4, y = 5;
	ws.resize(x*y);
	for(size_t i=0; i<ws.size(); i++) ws[i].resize(10);
	initialize_ws();*/


	for(size_t i=0; i<10;i++)
		errorMax.push_back(0.1);

	initialize_errorSum();

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
		return;
	}
	
	picture.clear();
	read_picture(fs);
	int pictWidth = picture[0].size();
	int pictHeight = picture.size();


	int dg_num = check_digit_amount();
	if(dg_num == 1 && pictWidth>70) dg_num = 3;
	/*printf("%d\n", dg_num);
	continue;*/

	int digit_wd = pictWidth/dg_num;
	int digit_wdLast = digit_wd + pictWidth%dg_num;


	int wd = digit_wd/4;
	int lastWd = wd + digit_wd%4;
	int ht = pictHeight/5;
	int lastHt = ht + pictHeight%5;

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

			switch(step)
			{
			case 2: wd = digit_wdLast/4;
					lastWd = wd + digit_wdLast%4;
					break;
			default: 
				if(dg_num == 2)
				{wd = digit_wdLast/4;
				lastWd = wd + digit_wdLast%4;}
				else{
					wd = digit_wd/4;
					lastWd = wd + digit_wd%4;}
			}

		start = step*digit_wd;
		initialize_vector_in(start, wd, lastWd, ht, lastHt); 

		int ans = -1; //get_answer(v_temp);
		while(1)//ans != answer)
			{
			vector<float> v_temp;
			scalar_product(v_temp);
			func_activation(v_temp);


			ans = get_answer(v_temp);

			bool res = weight_correction(v_temp, d);
		
			calculate_errorSum(v_temp, d);
			bool check_res = check_errorSum();
			if(!check_res) puts("error is higher errorMax...");
			/*else*/ break;

			}
		step++;
		}
	
	}
	write_weights_in_file();
}

/***************************************/
float arr_weights[] = 
{-0.055714, 0.003929, 0.003929, 0.003929, 0.003929, 0.050119, 0.003929, 0.137679, -0.026310, 0.003929, 
-0.160000, -0.155655, -0.157798, -0.171131, -0.171131, -0.037321, -0.171131, 0.057708, -0.205655, -0.171131, 
-0.202381, -0.129345, -0.131488, -0.177917, -0.177917, -0.130298, -0.177917, -0.015685, -0.210536, -0.177917, 
-0.141490, -0.087612, -0.055889, -0.104143, -0.104143, -0.098111, -0.104143, 0.110796, -0.066274, -0.104143, 
0.075000, 0.023452, 0.026786, 0.023452, 0.023452, 0.040357, 0.023452, 0.004702, 0.039405, 0.023452, 
0.017381, -0.038869, -0.005774, -0.038869, -0.038869, 0.108274, -0.038869, -0.066994, 0.000655, -0.038869, 
0.002381, 0.125417, 0.114702, 0.073750, 0.073750, 0.109226, 0.073750, -0.031042, -0.009821, 0.073750, 
-0.006735, -0.086097, -0.093240, -0.101811, -0.101811, -0.157934, -0.101811, -0.091615, -0.012015, -0.101811, 
0.100000, -0.005000, 0.005714, -0.005000, -0.005000, 0.000714, -0.005000, -0.057500, -0.026667, -0.005000, 
0.018810, -0.025000, 0.004048, -0.025000, -0.025000, -0.049048, -0.025000, -0.052500, 0.105952, -0.025000, 
-0.079524, 0.061905, 0.012857, 0.010238, 0.010238, 0.104286, 0.010238, -0.050595, 0.009286, 0.010238, 
0.059286, -0.064286, -0.080000, -0.080000, -0.080000, -0.094490, -0.080000, -0.115929, -0.080816, -0.080000, 
0.068571, -0.001429, 0.067619, -0.001429, -0.001429, -0.047619, -0.001429, -0.036429, -0.012381, -0.001429, 
0.021190, 0.023333, 0.050238, 0.023333, 0.023333, 0.081190, 0.023333, -0.004167, -0.009524, 0.023333, 
-0.111667, -0.001429, -0.052857, -0.053095, -0.053095, -0.169048, -0.053095, -0.015595, 0.140476, -0.053095, 
0.083286, -0.016536, -0.005583, -0.032250, -0.032250, -0.004223, -0.032250, -0.113304, -0.105855, -0.032250, 
0.060625, 0.048625, 0.065708, 0.048625, 0.048625, 0.116542, 0.048625, 0.042625, 0.066750, 0.048625, 
-0.051125, -0.048268, -0.014875, -0.051125, -0.051125, -0.126690, -0.051125, -0.059506, 0.022000, -0.051125, 
-0.016030, 0.039827, 0.015542, -0.021125, -0.021125, -0.100411, -0.021125, -0.045863, -0.058833, -0.021125, 
0.037219, 0.056709, 0.060159, 0.024464, 0.024464, 0.043846, 0.024464, -0.062526, 0.001806, 0.024464};

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

	int dg_num = check_digit_amount();
	if(dg_num == 1 && pictWidth>70) dg_num = 3;

	int digit_wd = pictWidth/dg_num;
	int digit_wdLast = digit_wd + pictWidth%dg_num;


	int wd = digit_wd/4;
	int lastWd = wd + digit_wd%4;
	int ht = pictHeight/5;
	int lastHt = ht + pictHeight%5;

	int step = 0, start = 0, end = 0;
		while(step < dg_num)
		{

			switch(step)
			{
			case 2: wd = digit_wdLast/4;
					lastWd = wd + digit_wdLast%4;
					break;
			default: 
				if(dg_num == 2 && step == 1)
				{wd = digit_wdLast/4;
				lastWd = wd + digit_wdLast%4;}
				else{
					wd = digit_wd/4;
					lastWd = wd + digit_wd%4;}
			}

		start = step*digit_wd;
		v_in.clear();
		initialize_vector_in(start, wd, lastWd, ht, lastHt); 
		
			vector<float> v_temp;
			scalar_product(v_temp);
			func_activation(v_temp);
			vector<int> answer;
			int ans = get_answer(v_temp);
			/*if(answer.size() == 0) puts("No answer...");
			for(size_t i=0; i<answer.size(); i++)*/
				printf("%d", ans);
			
		step++;
		}
		


}
/***************************************/

int main()
{
	
	int x = 4, y = 5;
	ws.clear();
	ws.resize(x*y);
	for(size_t i=0; i<ws.size(); i++) ws[i].resize(10);

	/* веса (массив arr_weights) получены в результате обучения сети на примерах
	из задания*/
	int k = 0;
	for(size_t i=0; i<ws.size();i++)
	{
		vector<float> w1;
		for(size_t j=0;j<ws[i].size();j++, k++)
		   w1.push_back(arr_weights[k]);
	ws[i] = w1;
	}
	
	//learning_neuronet();

	number_recognition();

	return 0;
}
