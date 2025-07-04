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
-0.393556, -0.441905, -0.397677, -0.383324, -0.472969, -0.420788, -0.426830, -0.332650, -0.413899, -0.394288, 
-0.555647, -0.555703, -0.561141, -0.525120, -0.624385, -0.540170, -0.574371, -0.501500, -0.542531, -0.572388, 
-0.334359, -0.341874, -0.317114, -0.338886, -0.328428, -0.231622, -0.273821, -0.210446, -0.347948, -0.336903, 
-0.268111, -0.237980, -0.291579, -0.261026, -0.326750, -0.294020, -0.271665, -0.234672, -0.269304, -0.254972, 
-0.428670, -0.385364, -0.435989, -0.411099, -0.487821, -0.372455, -0.417117, -0.398593, -0.473279, -0.486163, 
-0.450127, -0.373917, -0.372135, -0.423816, -0.429819, -0.370250, -0.408568, -0.366443, -0.441613, -0.429652, 
-0.388795, -0.418921, -0.348059, -0.365762, -0.399785, -0.368870, -0.375066, -0.308464, -0.396044, -0.404998, 
-0.275453, -0.320278, -0.288835, -0.270776, -0.353847, -0.321534, -0.301218, -0.327266, -0.276156, -0.281965, 
-0.297325, -0.270729, -0.226392, -0.324089, -0.291771, -0.224247, -0.300388, -0.323805, -0.271294, -0.316860, 
-0.229108, -0.151566, -0.196613, -0.222584, -0.157672, -0.194653, -0.195662, -0.235262, -0.198466, -0.188681, 
-0.279502, -0.309186, -0.222663, -0.226022, -0.288244, -0.343473, -0.325938, -0.268834, -0.264424, -0.261700, 
-0.272689, -0.343372, -0.298045, -0.330248, -0.341910, -0.262040, -0.307900, -0.324612, -0.240327, -0.256992, 
-0.314467, -0.292151, -0.287502, -0.359935, -0.284430, -0.201310, -0.322731, -0.356774, -0.275269, -0.294783, 
-0.318986, -0.250127, -0.271595, -0.319120, -0.236461, -0.218103, -0.289235, -0.314663, -0.288333, -0.263971, 
-0.343906, -0.376924, -0.310258, -0.292262, -0.358126, -0.391759, -0.371137, -0.332922, -0.312627, -0.321870, 
-0.146418, -0.227405, -0.239099, -0.215484, -0.226466, -0.223440, -0.164745, -0.222295, -0.151161, -0.142830, 
-0.261936, -0.239461, -0.292753, -0.304986, -0.219780, -0.261476, -0.218210, -0.297312, -0.200671, -0.244113, 
-0.392074, -0.320811, -0.358267, -0.356328, -0.322267, -0.347211, -0.288919, -0.337877, -0.364207, -0.379353, 
-0.361447, -0.399023, -0.344885, -0.329174, -0.375900, -0.341955, -0.377056, -0.383636, -0.376540, -0.334709, 
-0.123485, -0.206920, -0.226376, -0.197206, -0.186394, -0.218641, -0.108909, -0.197569, -0.176043, -0.119213, 
-0.295105, -0.267798, -0.328812, -0.296712, -0.259031, -0.311843, -0.281883, -0.322728, -0.187893, -0.266992, 
-0.536575, -0.456244, -0.472327, -0.440613, -0.471522, -0.509675, -0.482175, -0.448939, -0.411963, -0.496380, 
-0.312269, -0.351555, -0.325284, -0.308422, -0.327414, -0.300248, -0.316193, -0.355135, -0.358887, -0.239922, 
-0.107254, -0.190032, -0.176972, -0.206270, -0.108817, -0.196857, -0.103316, -0.181252, -0.125110, -0.184156, 
-0.330426, -0.305694, -0.331063, -0.357872, -0.335000, -0.379355, -0.313946, -0.346296, -0.273528, -0.211567, 
-0.535303, -0.463496, -0.487222, -0.490655, -0.480292, -0.555458, -0.469634, -0.453187, -0.414277, -0.371543, 
-0.319129, -0.358494, -0.364977, -0.300541, -0.304682, -0.302392, -0.306434, -0.358081, -0.334436, -0.281787, 
-0.160568, -0.238875, -0.198938, -0.264003, -0.139990, -0.203869, -0.178728, -0.233399, -0.135236, -0.287286, 
-0.262616, -0.238715, -0.228841, -0.284549, -0.260826, -0.309719, -0.212335, -0.242204, -0.255464, -0.324171, 
-0.311867, -0.243976, -0.275099, -0.295456, -0.210357, -0.332064, -0.249080, -0.259721, -0.258298, -0.255370, 
-0.320078, -0.349779, -0.389619, -0.277319, -0.300657, -0.300704, -0.308629, -0.348043, -0.279459, -0.290032, 
-0.269449, -0.340124, -0.264020, -0.275123, -0.288776, -0.309933, -0.277325, -0.342590, -0.246610, -0.370506, 
-0.282939, -0.279441, -0.228643, -0.354034, -0.287815, -0.343363, -0.265219, -0.261514, -0.326160, -0.312792, 
-0.191185, -0.129686, -0.192894, -0.183895, -0.097455, -0.211351, -0.201325, -0.166910, -0.144704, -0.135888, 
-0.317893, -0.350731, -0.363944, -0.255088, -0.277062, -0.288259, -0.327100, -0.350959, -0.296294, -0.315556, 
-0.284595, -0.294443, -0.217230, -0.226355, -0.315672, -0.194840, -0.305581, -0.309615, -0.223675, -0.253315, 
-0.449845, -0.444143, -0.453052, -0.484754, -0.555948, -0.455460, -0.395121, -0.422061, -0.492837, -0.503127, 
-0.374218, -0.331119, -0.313596, -0.360339, -0.352997, -0.334851, -0.402538, -0.416593, -0.378920, -0.368390, 
-0.308804, -0.312675, -0.219030, -0.261222, -0.278630, -0.267675, -0.304681, -0.335224, -0.273237, -0.309045};

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
