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


vector<vector<float> > picture; /*изображение*/

vector<vector<float> > ws; //веса
vector<float> v_in; // входной вектор
vector<float> d; // желаемый вектор
float eta = 0.1; // скорость обучени€
float numE = 2.718; // число e

int neuro_wid = 10;
vector<int> borders;//вертикальн. границы цифры
vector<int> h_borders;//горизонт. гр-цы

/*******************/
/* Learning neuro_net*/
/*******************/

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
				for(int j = y*ht + h_borders[0]; j<y*ht + h_borders[0] + ht; j++)
					sum = sum+ picture[j][i];
			}
			sum = sum/(wd*ht);
			v_in.push_back(sum);
			x++;
		}

		sum = 0;
			for(int i = x*wd + start; i<x*wd + start+lastWd; i++)
			{			
				for(int j = y*ht + h_borders[0]; j<y*ht + h_borders[0] + ht; j++)
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
				for(int j = y*ht + h_borders[0]; j<y*ht + h_borders[0] + lastHt; j++)
					sum = sum+ picture[j][i];
			}
			sum = sum/(wd*lastHt);
			v_in.push_back(sum);
			x++;
		}

		sum = 0;
			for(int i = x*wd + start; i<x*wd + start+lastWd; i++)
			{			
				for(int j = y*ht + h_borders[0]; j<y*ht + h_borders[0] + lastHt; j++)
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


bool weight_correction(vector<float> v, vector<float> d)
{
	
	for(size_t i=0; i<v.size(); i++)
	{
		for(size_t j=0; j<ws.size(); j++)
		ws[j][i] = ws[j][i] + eta*(d[i]-v[i])*v[i]*(1-v[i])*v_in[j];

		
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
	fputs("\n\n/************/", fs);
	fclose(fs);

}


int get_answer(vector<float> v);

void find_horiz_borders(int left, int right)
{
	bool up = false;
	bool down = false;
	size_t j=0;
	int sum = 0;
   for(; j<picture.size(); j++)
	{
		for(int i=left; i<right; i++)
		{
		
				if(picture[j][i] != 0)
				{
					sum++;

				}
		}
		
		if(/*sum != (right-left) && */sum>0)
		{
					h_borders.push_back(j);
					j++;
					break;
		}
   }

   for(; j<picture.size(); j++)
   {	
	   sum = 0;
	   for(int i=left; i<right; i++)
		{
				if(picture[j][i] != 0)
					sum++;		
		}
	   if(sum == 0)
	   {
		   h_borders.push_back(j);
					return;
	   }
	}
   h_borders.push_back(picture.size());
}
/***************************************/
void learning_neuronet()
{
	char file[100] = "001";
	int answer = 0;
	/*
	int x = 4, y = neuro_wid;
	ws.resize(x*y);
	for(size_t i=0; i<ws.size(); i++) ws[i].resize(10);
	initialize_ws();*/

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

		h_borders.clear();
		find_horiz_borders(borders[2*step], borders[2*step+1]);

			int ht = (h_borders[1]-h_borders[0])/neuro_wid;
	        int lastHt = ht + (h_borders[1]-h_borders[0])%neuro_wid;

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
{-0.115678, -0.126339, -0.128004, -0.134228, -0.146043, -0.121224, -0.092092, -0.014691, -0.104813, -0.086289, 
-0.395624, -0.444886, -0.400400, -0.380485, -0.475060, -0.422960, -0.429060, -0.335465, -0.416283, -0.396788, 
-0.560018, -0.557082, -0.566799, -0.524240, -0.628992, -0.545465, -0.579040, -0.506792, -0.547703, -0.577856, 
-0.348623, -0.327655, -0.335210, -0.355491, -0.344178, -0.251581, -0.288893, -0.225208, -0.365330, -0.355446, 
-0.268963, -0.239208, -0.292700, -0.259857, -0.327611, -0.294914, -0.272583, -0.235831, -0.270286, -0.256001, 
-0.433041, -0.386743, -0.441647, -0.410219, -0.492429, -0.377750, -0.421786, -0.403885, -0.478451, -0.491631, 
-0.466127, -0.362529, -0.392523, -0.437696, -0.447312, -0.391985, -0.425515, -0.383612, -0.460988, -0.450281, 
-0.404387, -0.405304, -0.367878, -0.381909, -0.416928, -0.390411, -0.391558, -0.324858, -0.414992, -0.425195, 
-0.283697, -0.314935, -0.299349, -0.277382, -0.362840, -0.332657, -0.309954, -0.336182, -0.286124, -0.292574, 
-0.311570, -0.255089, -0.244436, -0.342170, -0.307556, -0.244386, -0.315428, -0.338355, -0.288692, -0.335432, 
-0.244156, -0.136590, -0.215704, -0.240076, -0.174287, -0.215705, -0.211562, -0.250838, -0.216802, -0.208241, 
-0.295743, -0.296504, -0.243336, -0.241278, -0.306043, -0.365696, -0.343129, -0.286111, -0.284120, -0.282681, 
-0.288318, -0.327757, -0.317872, -0.348478, -0.359169, -0.283913, -0.324414, -0.340782, -0.259373, -0.277310, 
-0.323189, -0.282575, -0.298550, -0.371005, -0.294094, -0.213640, -0.331939, -0.365682, -0.285921, -0.306154, 
-0.322986, -0.247280, -0.276692, -0.322590, -0.240834, -0.223537, -0.293472, -0.318955, -0.293177, -0.269128, 
-0.360147, -0.364242, -0.330931, -0.307518, -0.375925, -0.413982, -0.388328, -0.350199, -0.332323, -0.342851, 
-0.147872, -0.225809, -0.240940, -0.217329, -0.228077, -0.225495, -0.166280, -0.223780, -0.152936, -0.144725, 
-0.261936, -0.239461, -0.292753, -0.304986, -0.219780, -0.261476, -0.218210, -0.297312, -0.200671, -0.244113, 
-0.395396, -0.318709, -0.362505, -0.358937, -0.325889, -0.351686, -0.292439, -0.341476, -0.368222, -0.383626, 
-0.377688, -0.386341, -0.365558, -0.344431, -0.393699, -0.364178, -0.394247, -0.400913, -0.396236, -0.355690, 
-0.123485, -0.206920, -0.226376, -0.197206, -0.186394, -0.218641, -0.108909, -0.197569, -0.176043, -0.119213, 
-0.295105, -0.267798, -0.328812, -0.296712, -0.259031, -0.311843, -0.281883, -0.322728, -0.187893, -0.266992, 
-0.539897, -0.454142, -0.476565, -0.443222, -0.475144, -0.514150, -0.485695, -0.452538, -0.415978, -0.500653, 
-0.327861, -0.337938, -0.345103, -0.324569, -0.344557, -0.321789, -0.332685, -0.371529, -0.377835, -0.260119, 
-0.107254, -0.190032, -0.176972, -0.206270, -0.108817, -0.196857, -0.103316, -0.181252, -0.125110, -0.184156, 
-0.330426, -0.305694, -0.331063, -0.357872, -0.335000, -0.379355, -0.313946, -0.346296, -0.273528, -0.211567, 
-0.538868, -0.461744, -0.491780, -0.492930, -0.484160, -0.560188, -0.473417, -0.457118, -0.418573, -0.376110, 
-0.334559, -0.344643, -0.384582, -0.316911, -0.321661, -0.323763, -0.322751, -0.374254, -0.353197, -0.301788, 
-0.160568, -0.238875, -0.198938, -0.264003, -0.139990, -0.203869, -0.178728, -0.233399, -0.135236, -0.287286, 
-0.263224, -0.239592, -0.229642, -0.283714, -0.261441, -0.310358, -0.212991, -0.243032, -0.256165, -0.324906, 
-0.317014, -0.244504, -0.281739, -0.295560, -0.215824, -0.338455, -0.254568, -0.265805, -0.264417, -0.261849, 
-0.334697, -0.334759, -0.408156, -0.294802, -0.316816, -0.321223, -0.324072, -0.363112, -0.297285, -0.309052, 
-0.269449, -0.340124, -0.264020, -0.275123, -0.288776, -0.309933, -0.277325, -0.342590, -0.246610, -0.370506, 
-0.284764, -0.282071, -0.231045, -0.351529, -0.289660, -0.345280, -0.267186, -0.263998, -0.328264, -0.314998, 
-0.196332, -0.130214, -0.199534, -0.183999, -0.102922, -0.217742, -0.206813, -0.172994, -0.150823, -0.142367, 
-0.334134, -0.338049, -0.384617, -0.270344, -0.294861, -0.310482, -0.344291, -0.368236, -0.315990, -0.336537, 
-0.285158, -0.295254, -0.217971, -0.225583, -0.316241, -0.195431, -0.306188, -0.310381, -0.224324, -0.253995, 
-0.450256, -0.444735, -0.453593, -0.484190, -0.556363, -0.455891, -0.395564, -0.422620, -0.493310, -0.503623, 
-0.377540, -0.329017, -0.317834, -0.362948, -0.356619, -0.339326, -0.406058, -0.420192, -0.382935, -0.372663, 
-0.324700, -0.299496, -0.239249, -0.276952, -0.296080, -0.289536, -0.321501, -0.352032, -0.292536, -0.329610};

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

		start = borders[2*step];
		wd = (borders[2*step+1] - start)/4;
		lastWd = wd + (borders[2*step+1] - start)%4;
	
		h_borders.clear();
		find_horiz_borders(borders[2*step], borders[2*step+1]);

			int ht = (h_borders[1]-h_borders[0])/neuro_wid;
	        int lastHt = ht + (h_borders[1]-h_borders[0])%neuro_wid;

		v_in.clear();
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
