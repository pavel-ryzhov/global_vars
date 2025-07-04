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
{0.011534, -0.070598, -0.066353, -0.054167, -0.049651, 0.046872, -0.066300, 0.221448, 0.038527, 0.094806, 
-0.023327, -0.148461, -0.087833, -0.037791, -0.163862, -0.027184, -0.139025, 0.068029, -0.059912, -0.011398, 
-0.143584, 0.096289, -0.117111, -0.055562, -0.233198, -0.122608, -0.098700, -0.044051, -0.025346, -0.049148, 
-0.044654, -0.102857, -0.081814, 0.064049, -0.036928, -0.056230, -0.061690, 0.165114, -0.070950, -0.111609, 
0.022054, -0.200617, 0.061240, -0.084259, -0.129768, 0.078341, -0.073521, -0.067599, 0.143090, 0.218561, 
0.111982, -0.060444, 0.075947, -0.000231, 0.140836, 0.169027, 0.151909, -0.127318, -0.041875, -0.214265, 
0.052207, 0.366544, -0.092643, -0.034167, 0.110942, 0.119194, 0.055964, -0.157143, 0.058605, -0.042535, 
-0.048960, -0.112116, 0.193666, 0.062392, -0.079004, -0.300383, -0.097607, -0.029102, 0.059392, 0.006171, 
0.064590, -0.206111, -0.111991, -0.111111, -0.028633, -0.038294, 0.104683, -0.067516, -0.080652, 0.170468, 
0.103081, -0.051657, -0.122310, -0.012778, 0.008804, 0.032337, 0.177308, -0.081730, 0.208931, -0.054165, 
-0.138893, 0.087480, -0.090994, -0.012917, -0.025049, 0.000512, -0.000373, -0.036179, 0.061608, -0.207929, 
-0.087404, -0.113740, -0.029766, 0.037583, -0.107043, 0.016518, 0.077423, -0.119208, -0.119782, 0.035384, 
0.062911, -0.148450, -0.101195, -0.021250, 0.121133, 0.001396, 0.059493, -0.005572, 0.147234, -0.103801, 
0.060667, -0.237806, 0.086725, -0.117685, -0.027584, -0.453657, 0.054829, -0.045721, -0.124068, -0.099844, 
-0.163832, -0.077491, -0.022725, -0.193194, 0.059343, -0.111037, -0.178375, -0.111538, -0.128123, 0.025261, 
-0.128940, -0.163815, -0.364721, -0.013355, -0.054683, 0.135396, 0.006381, -0.084244, -0.058192, 0.036175, 
-0.062779, -0.145693, 0.071752, -0.052907, -0.073818, 0.184443, -0.064098, 0.009334, 0.137187, 0.193816, 
-0.014700, -0.145901, -0.002729, 0.040102, -0.221127, -0.041565, 0.103555, 0.052693, -0.066418, -0.063281, 
-0.061786, -0.002521, -0.045337, -0.047056, 0.063938, 0.080140, -0.101196, -0.165809, -0.146404, -0.088309, 
0.018124, -0.005442, 0.160197, 0.019685, 0.006423, -0.069781, -0.005786, -0.096681, 0.006725, 0.062596};

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
