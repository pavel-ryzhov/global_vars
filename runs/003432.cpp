#include <stdio.h>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>

using namespace std;

struct gs
{
	float g1, g2;
	void operator = (float s) {g1 = s- 0.05 ;  g2=s+0.05; }
	bool operator==(float s) const {return (s>g1) && (s<g2); }
};
struct g
{
	float p1, p2, p3, p4;
};


struct Chetv
{
	gs c1, c2, c3, c4;
	bool operator==(const g& CH) const 
	{return ( c1== CH.p1) && ( c2== CH.p2) && ( c3== CH.p3)&& ( c4== CH.p4); }
};


int main(void)
{
	freopen("out.txt","w", stdout);
	freopen("1.txt","r", stdin);

	int i, R=0, c = 0;
	vector <vector<char> > MATR(1);
	vector < vector <vector<char> > > Razr(3);
	vector<char> bufv;


	Chetv CIFR [10];
	CIFR[0].c1 = (float)0.24;	CIFR[0].c2 = (float)0.24;	CIFR[0].c3 = (float)0.24;	CIFR[0].c4 = (float)0.25;	
	CIFR[1].c1 = (float)0.2;	CIFR[1].c2 = (float)0.5;	CIFR[1].c3 = (float)0.3;	CIFR[1].c4 = (float)0;	
	CIFR[2].c1 = (float)0.19;	CIFR[2].c2 = (float)0.3;	CIFR[2].c3 = (float)0.21;	CIFR[2].c4 = (float)0.3;
	CIFR[3].c1 = (float)0.15;	CIFR[3].c2 = (float)0.35;	CIFR[3].c3 = (float)0.35;	CIFR[3].c4 = (float)0.15;	
	CIFR[4].c1 = (float)0.2;	CIFR[4].c2 = (float)0.15;	CIFR[4].c3 = (float)0.41;	CIFR[4].c4 = (float)0.2;	
	CIFR[5].c1 = (float)0.316;	CIFR[5].c2 = (float)0.201;	CIFR[5].c3 = (float)0.32;	CIFR[5].c4 = (float)0.15;	
	CIFR[6].c1 = (float)0.29;	CIFR[6].c2 = (float)0.12;	CIFR[6].c3 = (float)0.29;	CIFR[6].c4 = (float)0.3;	
	CIFR[7].c1 = (float)0.20;	CIFR[7].c2 = (float)0.45;	CIFR[7].c3 = (float)0.05;	CIFR[7].c4 = (float)0.29;	
	CIFR[8].c1 = (float)0.21;	CIFR[8].c2 = (float)0.20;	CIFR[8].c3 = (float)0.251;	CIFR[8].c4 = (float)0.316;
	CIFR[9].c1 = (float)0.25;	CIFR[9].c2 = (float)0.19;	CIFR[9].c3 = (float)0.27;	CIFR[9].c4 = (float)0.3;	
	
	bool all_white = true;

	while (all_white)
	{
		MATR[0].clear();
		while ( (c = getc(stdin)) != 10)
		{
			MATR[0].push_back(c);
			if (c == '@') all_white = false;
 		}
	}

	int MATR_size_x = MATR[0].size();
	for (i= 0; i<MATR_size_x; i++)
		switch (MATR[0][i])
		{
			case '.' : // . белый
				MATR[0][i]=0;
				break;
			case '%' : // % св серый
				MATR[0][i]=1;
				break;
			case '#' : 	// # темно серый
				MATR[0][i]=2;
				all_white = false; 
				break;
			case '@' : // @ черный
				MATR[0][i]=3;
				all_white = false; 
				break;
		}

	while (!all_white) 
	{
		R++;
		MATR.resize(R+1);
		all_white = true;
		while ( (c = getc(stdin)) != 10)
		{
			switch (c)
			{
				case '.' : 
					MATR[R].push_back(0);
					break;
				case '%' :
					MATR[R].push_back(1);
					break;
				case '#' : 	
					MATR[R].push_back(2);
					all_white = false; 
					break;
				case '@' : 
					MATR[R].push_back(3);
					all_white = false; 
					break;
			}
 		}
	}
	MATR.pop_back();
/*
	for (i=0;i<MATR.size();i++)
	{
		for (int j=0; j< MATR[i].size();j++)
			printf ("%d",MATR[i][j]);
		printf("\n");
	}*/
	
	int MATR_size_y = MATR.size();
	//удаление правого края
	for(i=MATR_size_x-1; i>0 ; i--)
	{
		all_white =true;
		for (int j=0; j< MATR_size_y; j++)
			if (MATR[j][i]) 
			{
				all_white = false;
				break;
			}
		if (all_white)
			for (int j=0; j< MATR_size_y; j++)
				MATR[j].pop_back() ;		
		else break;
	}
	MATR_size_x = MATR[0].size();
	//удаление левого края
	for(i=0; i< MATR_size_x; i++)
	{
		all_white =true;
		for (int j=0; j< MATR_size_y; j++)
			if (MATR[j][i]) 
			{
				all_white = false;
				break;
			}
		if (!all_white)
		{
			for (int j=0; j< MATR_size_y; j++)
				MATR[j].erase(MATR[j].begin(),MATR[j].begin()+i);		
			break;
		}
	}
	MATR_size_x = MATR[0].size();
	/*
	for (i=0;i<MATR.size();i++)
	{
		for (int j=0; j< MATR[i].size();j++)
			printf ("%d",MATR[i][j]);
		printf("\n");
	}
	*/
		
	int interv_len = (int)MATR_size_y*0.24;
	int sredn_yark = 0;
	vector <int> col_yark(MATR_size_x);
	for(i=0; i< MATR_size_x; i++)
		for (int j=0; j< MATR_size_y; j++)
		{
			col_yark[i]+=MATR[j][i];
			sredn_yark+=MATR[j][i];
		}
			
	sredn_yark/= MATR_size_x;

	int N_interv = MATR_size_x/interv_len;
	int N_gran = N_interv-2;
	vector <int> lok_min(N_gran); 
	int min;
	for(i=1; i<N_interv-1; i++)
	{
		min = col_yark[i*interv_len];
		int gran =  (i+1)*interv_len;
		for (int j= i*interv_len; j< gran; j++)
		{
			if (col_yark[j]<=min) 
			{
				min = col_yark[j];
				lok_min[i-1]= j;
			}
		}

	}

	int porog = sredn_yark/3;
	int l = MATR_size_y/10;
	for (i= 0; i< N_gran; i++)
		if ( (col_yark[ lok_min[i] ] > porog) || ((col_yark[ (lok_min[i]-l) ] < porog) && (col_yark [ (lok_min[i]+l) ] < porog)))
		{
			lok_min.erase(lok_min.begin()+i);
			i--;
			N_gran--;
		}
			
	int min_smeg_rast = interv_len/2;
	for (i= 1; i< N_gran; i++)
		if  (lok_min[i] - lok_min[i-1]  < min_smeg_rast)
		{
			lok_min.erase(lok_min.begin()+i);
			i--;
			N_gran--;
		}
	
	/*printf ("\n");*/
	int k=0;
	int grancr=0;int grancl=0;

	/*while (grancr != MATR_size_x)
	{
		if (k<lok_min.size()) grancr =  lok_min[k];
		else grancr = MATR_size_x;

		
		for (int j=0; j< MATR_size_y; j++)
		{
			for (i= grancl; i< grancr; i++)	
				printf("%d", MATR[j][i]);
			printf ("\n");
		}
			
		if (k<lok_min.size()) grancl = lok_min[k];
		k++;

	}*/
	
	N_gran = lok_min.size();
	int MATR_size_y2 = MATR_size_y/2;
	int grancr2, i2;
	int s1, s2, s3, s4 , S;
	g proc;
	
	
	while (grancr != MATR_size_x)
	{
		s1 = s2= s3 =s4= S= 0;
		if ( k<N_gran )
		{
			grancr =  lok_min[k]+1;
			all_white =true;
			while (all_white)
			{
				grancr--;
				for (int j=0; j< MATR_size_y; j++)
					if (MATR[j][grancr]) 
					{
						all_white = false; 
						break;
					}		
			}		
		}
		else grancr = MATR_size_x;

		
		grancr2=(grancl+grancr)/2;

		for (i= grancl, i2 = grancr-1; i< grancr2; i++, i2--)
		{
			for (int j=0; j< MATR_size_y2; j++)	
			{
				s1 += MATR[j][i];
				s2 += MATR[j][i2];
			}
			s4 += col_yark[i];
			s3 += col_yark[i2];	
		}
		S += s3 + s4;
 		s4 -= s1;
		s3 -= s2; 
		proc.p1= s1/(float)S;
		proc.p2= s2/(float)S;
		proc.p3=s3/(float)S;
		proc.p4= s4/(float)S;
		
		for (i=0; i< 10; i++)
			if (CIFR[i] == proc)
			{
				printf("%d",i); 
				break; 
			}
					
		if ( k<N_gran )
		{
			grancl =  lok_min[k]-1;
			all_white =true;
			while (all_white)
			{
				grancl++;
				for (int j=0; j< MATR_size_y; j++)
					if (MATR[j][grancl]) 
					{
						all_white = false; 
						break;
					}		
			}
		}
			
		k++;

	}
	return 0;
}

