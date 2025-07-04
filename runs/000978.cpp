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
			v_in.push_back(sum);
			x++;
		}

		sum = 0;
			for(int i = x*wd + start; i<x*wd + start+lastWd; i++)
			{			
				for(int j = y*ht; j<y*ht + ht; j++)
					sum = sum+ picture[j][i];
			}
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
			v_in.push_back(sum);
			x++;
		}

		sum = 0;
			for(int i = x*wd + start; i<x*wd + start+lastWd; i++)
			{			
				for(int j = y*ht; j<y*ht + lastHt; j++)
					sum = sum+ picture[j][i];
			}
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
void learning_neuronet()
{
	char file[100] = "001";
	int answer = 0;
	
	int x = 4, y = 5;
	ws.resize(x*y);
	for(size_t i=0; i<ws.size(); i++) ws[i].resize(10);
	initialize_ws();


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
	read_picture(/*fs*/);
	int pictWidth = picture[0].size();
	int pictHeight = picture.size();

	int digit_wd = pictWidth/3;
	int digit_wdLast = digit_wd + pictWidth%3;


	int wd = digit_wd/4;
	int lastWd = wd + digit_wd%4;
	int ht = pictHeight/5;
	int lastHt = ht + pictHeight%5;

	int step = 0, start = 0, end = 0;
		while(step < 3)
		{
		puts("answer:");
		gets(file);
		answer = atoi(file);

		d.clear();
		d.resize(10, 0);
		d[answer] = 1.;
		v_in.clear();

			switch(step)
			{
			case 2: wd = digit_wdLast/4;
					lastWd = wd + digit_wdLast%4;
					break;
			default: 
					wd = digit_wd/4;
					lastWd = wd + digit_wd%4;
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
{-1.010000, 0.130000, -0.800000, -1.400000, -1.010000, 1.370001, -1.010000, 1.090000, -2.160000, -0.110000, 
-2.299999, -2.059999, -0.770000, -1.279999, -2.669999, 3.220000, -1.519999, -0.019999, -3.139998, -1.160000, 
-2.299999, -0.619998, -0.530000, -0.929999, -3.339999, 0.209999, -0.349999, 0.250001, 0.070004, -0.770000, 
-1.340001, 0.099999, -0.950000, 0.259999, -0.260001, 2.140003, -0.710001, 2.080000, -3.410002, -2.300002, 
-1.550001, -1.550001, -0.290000, -1.970001, -2.280001, 1.880001, -1.550001, -1.940001, 0.510000, 0.729999, 
-1.730000, -1.730000, -0.170000, 0.050000, 0.610001, 2.329998, 0.610000, -1.910000, -3.040002, -1.940000, 
-1.010000, 0.430000, -1.010000, -1.350000, -0.360001, 1.070001, -1.310000, 1.360001, -0.620000, -1.160000, 
-0.260000, 1.180000, 1.779998, 2.390000, 0.540000, -8.549990, -0.980000, 0.190000, 1.949999, 0.069999, 
-1.730000, -0.110000, -1.820000, -1.880000, -1.350000, 3.540000, -0.170000, -1.730000, -1.790000, 1.510000, 
-2.119999, -2.119999, -1.969999, -1.849999, -1.169999, 3.089994, 0.430001, -0.919999, -0.109996, -1.729999, 
-2.269999, -0.829999, -0.829999, -0.459999, -0.749996, -2.630006, -0.769999, -0.049999, -1.419997, -3.109999, 
-1.340001, 0.099999, -0.500001, 1.060000, -0.240001, 0.740004, 1.449999, -2.060001, -2.790001, 0.369998, 
-0.560000, 1.720001, -0.740000, -0.510000, 0.760001, -3.570000, 0.550000, -0.590000, 2.740000, 0.010000, 
-0.110000, 0.130000, 2.079999, -0.460000, 1.560001, -9.419996, 1.270000, 1.750001, -1.800001, 0.849999, 
-1.040000, 0.220000, 1.150000, -1.730000, 1.860002, -4.810000, -1.040000, -0.530000, -4.990005, 0.159999, 
-1.999999, -0.499999, -4.099999, 1.720002, -1.030001, 4.309997, 0.400001, -1.999999, -0.109995, 1.270000, 
-1.670000, -1.130000, 0.610000, -2.440001, -2.040000, 0.509999, -1.850000, -2.060000, -0.150000, 0.370000, 
-2.629998, -2.629998, -0.200001, -0.379998, -2.779998, -0.720001, -0.529998, 0.610002, -1.279995, -1.339999, 
-2.659998, -2.659998, 0.039999, -1.719998, 0.510005, -0.510002, -1.519997, -2.929998, -6.059996, -1.099998, 
-1.040000, -1.040000, 0.849995, -0.970001, 2.360000, -5.419987, 0.219999, -1.880000, 0.100001, -0.170002};

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
int number_recognition()
{
	
	int answer = 0;

	
	
	picture.clear();
	read_picture();
	int pictWidth = picture[0].size();
	int pictHeight = picture.size();

	int digit_wd = pictWidth/3;
	int digit_wdLast = digit_wd + pictWidth%3;


	int wd = digit_wd/4;
	int lastWd = wd + digit_wd%4;
	int ht = pictHeight/5;
	int lastHt = ht + pictHeight%5;

	int step = 0, start = 0, end = 0;
		while(step < 3)
		{

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
					wd = digit_wd/4;
					lastWd = wd + digit_wd%4;
			}

		start = step*digit_wd;
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
		
	
	


	return 10;

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

	int answer = number_recognition();

	return 0;
}
