// PROB:scanner
// LANG:C++
//

//#include "stdafx.h"
#include <queue>
#include <iostream>
#define MaxN 1000

using namespace std; 

queue <int *> Q;

struct Cell {int x; int y; };

Cell XY[17];

int weight[10][256]={17,18,16,1,10,1,0,-3,-3,-4,0,-9,0,2,-8,1,11,10,-4,-4,8,-7,-2,-5,-3,0,2,0,-7,-9,-12,3,7,0,-1,-9,-2,3,2,-6,5,6,14,2,6,-6,-3,-1,9,-1,4,-9,2,2,5,-4,-3,5,7,-3,0,-9,9,-13,3,4,1,-3,22,17,3,8,-7,13,10,3,9,8,10,22,2,-2,8,3,14,2,-2,-3,-9,1,4,0,0,0,14,19,17,5,11,0,4,0,-10,-8,-13,0,-11,-27,-12,-5,4,31,27,8,-4,-12,-5,-3,-4,-14,-18,-17,-15,-12,-11,-12,-4,5,14,4,-1,-11,-8,-1,1,-16,0,0,-4,-16,-7,-6,15,-4,19,9,6,3,-2,-6,-4,-12,-3,-14,-4,-5,-3,8,6,-7,14,16,11,11,5,-2,7,0,-6,-6,4,-2,7,-8,-6,-4,13,4,13,10,7,10,-1,-1,-5,7,3,-10,4,-7,-14,-7,12,-3,2,-3,11,3,5,-3,-9,3,2,0,3,0,4,-14,-3,2,4,4,4,16,15,8,-11,7,-1,-11,2,-5,3,-17,5,2,9,-1,3,7,3,-1,-4,-3,-1,-7,1,8,-8,-14,6,-2,-8,-8,-9,-8,-1,-7,-4,-6,-7,1,0,-1,-9,-1,5,22,-16,-19,-36,-11,-12,-11,-17,2,-4,4,28,24,2,21,-7,30,12,6,-23,-11,-9,5,-12,-5,1,-15,-7,-18,-6,16,18,18,5,0,5,8,16,20,-12,11,0,-4,-3,-12,-15,23,11,-14,6,-6,-11,5,24,12,-3,24,-5,-8,-9,-20,-16,10,-11,2,13,-2,5,16,10,19,7,27,2,17,2,-2,0,12,0,3,6,-14,0,-2,18,1,1,2,-13,13,-14,-3,1,8,16,17,-5,-10,2,-11,13,5,0,11,8,-10,-14,-7,5,21,18,23,8,0,-16,-9,5,1,-2,-15,-21,-15,-12,-16,-10,17,4,-12,-13,-18,-11,6,-1,6,-8,5,-4,-9,-13,-15,1,15,-2,-2,-25,-15,10,-13,-1,7,-3,7,-10,-14,-2,1,7,-3,-12,6,-4,-13,-6,5,8,3,-7,6,-1,3,12,14,2,-11,-8,-31,1,-14,-5,9,-11,-6,-11,2,6,0,11,8,-27,-23,-3,-25,3,-17,13,9,-1,9,-2,3,2,13,30,6,-1,-25,3,2,-15,0,-6,-13,11,0,0,9,1,2,2,-9,-1,-8,-3,6,-12,-14,-14,-3,-3,10,-4,20,-6,3,5,9,21,28,12,17,16,22,-5,1,-10,-13,-4,-7,-11,8,4,12,19,33,15,8,13,4,13,-2,7,-2,-3,-15,-11,-5,-8,1,5,-8,1,-3,-12,-3,-13,-12,-3,-1,-2,0,-8,-6,2,-4,-17,6,9,-1,5,-2,-5,-1,-13,-8,-11,-8,0,-1,6,-4,0,-2,2,-3,-7,2,5,1,1,-11,-11,-9,-7,11,3,1,5,-1,-6,-2,-4,1,9,9,1,5,0,1,-6,0,10,-4,0,8,10,7,9,6,5,-3,-2,-6,1,-15,-8,-4,-2,1,6,9,4,19,8,1,1,-11,-20,-2,-1,-5,-4,-10,5,0,15,-1,2,-3,-10,-10,2,-7,-18,-9,-2,-5,0,7,14,17,2,-7,0,5,5,6,4,4,-19,-2,-2,-4,14,1,6,3,-6,-22,2,13,11,2,5,8,-1,3,-1,0,-2,-19,-6,-10,-15,-32,7,-1,-8,3,7,-6,2,-1,-5,1,-3,-17,-11,-13,-23,-23,6,-6,-6,-11,4,4,0,-3,-1,1,-9,-12,-4,-14,-12,-7,11,1,-2,1,15,21,11,0,8,0,-3,-4,12,0,8,13,5,1,-4,2,10,10,17,-2,-4,11,7,0,4,-7,0,19,10,10,4,5,4,-5,-2,-2,3,3,-4,-6,-2,0,16,26,16,29,15,-9,-8,-12,-4,-8,0,-1,-6,-5,0,15,27,13,59,18,48,7,-17,34,-7,11,-8,-15,-11,-24,-39,-7,-8,-14,15,18,-13,-20,-1,-25,16,7,-9,1,-1,-6,-11,4,-7,-33,24,21,10,-16,27,19,-4,-12,-10,-5,-5,-4,16,-4,-10,-17,12,12,32,-5,3,-16,-25,-15,-14,5,-4,-14,-9,-12,-25,20,-11,-14,27,-23,28,20,24,5,1,16,4,-10,16,11,33,25,-10,-20,-7,-21,-8,-22,23,15,29,3,4,30,15,3,10,18,17,-21,-40,-35,4,-20,-5,-3,-3,-9,9,6,-5,-14,-3,-5,19,4,-16,-14,15,-12,19,23,-21,-32,-4,-14,-8,-7,-36,-18,26,7,5,-26,-9,4,-1,25,4,9,14,21,6,14,6,-27,2,-21,2,-36,-21,-39,15,2,-20,-2,11,8,-4,26,48,14,30,6,0,-6,-16,-20,-3,-2,6,-1,9,-13,5,9,55,17,24,-25,2,-7,4,-9,1,-17,-17,-5,2,0,7,0,18,26,30,27,-18,-6,26,1,-4,-28,-4,7,10,-2,6,-21,15,-1,27,20,-4,-3,-10,33,21,-3,-12,7,-2,-17,10,-31,1,1,31,-1,-10,-4,-32,0,-2,4,5,3,3,3,7,-9,-7,-1,49,29,7,-7,-25,3,-17,-10,-22,-8,-27,-20,-7,5,-30,-26,10,10,10,6,-3,-9,-4,4,-7,-12,-6,-4,8,-5,-1,-1,6,3,-8,-8,-10,-13,2,-11,-15,-4,-1,-15,-1,-1,-4,2,10,-7,2,-12,-5,-13,-6,-13,-8,3,3,-12,2,2,1,1,9,-3,-8,-10,-7,-8,-10,-14,4,-7,-7,-4,-6,-9,-9,-5,7,-3,0,3,-9,1,1,0,-1,-9,3,6,8,-1,-4,-1,11,-8,0,-6,-1,-3,2,-4,4,-1,4,-3,9,-5,-7,-6,4,2,-5,5,-1,4,-1,11,1,6,0,-7,3,-1,-5,-4,1,-1,0,7,3,4,-8,-4,-11,4,-5,-9,3,-4,1,-1,4,5,6,9,12,11,10,3,4,3,5,-2,3,5,9,6,12,14,18,13,1,8,3,1,4,8,3,-7,2,5,3,6,1,18,1,13,3,8,12,7,7,16,3,-1,4,-7,2,-1,5,6,1,-1,5,9,10,8,13,16,5,0,5,-8,4,-3,18,4,-16,-2,9,18,1,5,11,13,12,1,-5,5,0,0,5,-5,-10,-14,-3,-7,-3,3,1,-1,10,-4,-3,-6,-1,0,10,-10,-11,-18,-18,-13,-18,-9,-4,-3,-2,5,-3,-6,2,10,13,7,2,-12,-8,-18,-14,-13,-3,-11,1,-1,0,10,17,-5,16,9,17,19,25,8,-3,-23,6,-18,-9,-26,-6,10,17,-4,3,-6,19,12,16,4,1,-9,-15,-17,-5,-15,-8,-10,7,27,0,-10,18,20,-5,4,5,-4,-15,0,28,16,-10,-22,9,-6,-9,-19,-10,-10,1,12,-15,-22,21,4,18,-28,9,-26,-26,-16,-29,-7,-24,18,13,-3,-4,-7,-6,-18,-12,3,-1,-6,-24,-23,17,8,32,12,5,22,19,-25,10,-3,-2,-23,9,-20,2,-2,16,13,4,6,15,21,8,0,-1,9,7,-3,-28,16,6,12,2,3,-2,1,-7,-9,-16,-2,-4,1,25,8,1,-16,20,-15,35,24,14,24,-11,-11,-10,-28,-4,-7,-7,-12,10,-4,-16,14,10,-7,-12,-14,-3,24,-29,4,-2,-5,-7,-27,-1,4,9,-9,-11,-38,-16,-12,-4,9,-18,-13,16,-7,-10,-4,12,11,4,-5,15,-11,6,-10,30,-16,-8,-2,3,0,0,0,-4,2,-4,5,26,-22,16,11,-8,-2,-14,-1,15,6,9,2,4,1,9,15,50,17,-8,1,0,-11,-7,12,21,11,19,-3,-4,4,7,2,37,36,0,-19,-10,-18,-11,6,6,7,-8,4,4,1,10,-9,19,20,2,35,-11,-19,-11,-21,-9,-7,0,-9,8,-27,0,3,32,19,10,-9,-13,2,-16,-13,-4,-2,-17,12,-2,-6,-11,19,17,-2,-17,-15,-3,-5,2,2,-5,13,-26,-5,-5,-16,12,-11,5,-4,-8,0,8,1,-2,0,14,-6,-14,-15,-18,-30,4,27,8,-29,1,-8,1,-10,-20,-18,-8,6,-15,-30,-3,4,-27,11,24,-10,3,0,7,3,-3,4,20,-5,-12,-22,-8,0,-16,-14,18,-2,-3,5,-3,-16,4,-4,2,-4,2,-25,-17,-14,-24,-22,31,9,-4,-15,-8,-16,3,6,6,4,12,9,1,4,-5,-15,33,19,-8,-9,8,-6,7,9,8,7,2,-7,10,22,14,1,17,16,5,3,7,-13,-10,1,-1,4,6,-13,2,-1,13,-9,10,24,16,18,10,-5,5,-4,-15,-2,5,8,2,0,5,-13,18,33,35,16,5,23,12,-5,-4,0,10,-7,8,1,-3,-2,-4,1,12,-5,-1,10,4,-8,10,-2,9,-3,14,-14,-10,-7,7,0,2,2,-7,8,10,-2,3,-6,-5,6,15,-4,18,13,4,-15,17,2,19,14,7,-5,3,7,6,-1,-2,4,-1,-13,-9,-2,2,-2,11,5,8,-8,6,-13,-15,-9,-12,2,19,8,20,11,5,-9,-4,-1,8,2,-10,-14,-15,-7,19,14,3,11,16,31,39,26,11,6,-10,-9,-14,-5,-8,-8,-5,1,11,19,13,9,5,-3,9,6,7,-10,4,6,4,-9,-16,1,11,21,18,14,13,-3,4,1,2,6,4,-4,-5,-15,-2,-4,7,6,-7,9,-5,-11,3,-5,-8,4,4,4,2,-16,-7,8,19,-3,21,6,6,-13,6,8,6,-3,10,1,-2,-6,8,10,-5,-6,5,-3,3,-2,2,-10,4,-7,-7,-4,12,7,2,19,8,-11,10,1,-8,-4,-21,3,-10,-7,-7,-4,-3,-14,0,-1,-22,-11,10,6,-13,-5,-17,-1,-4,7,4,2,12,1,-5,-8,-6,16,5,-5,-11,-9,14,-15,-7,-8,-5,4,0,-4,5,-4,-3,-3,1,4,0,4,8,0,-3,-5,0,-1,-5,-7,-10,-5,1,3,10,12,0,-4,10,10,-3,7,10,-11,-2,-4,-1,-11,3,-7,11,3,-3,7,3,17,21,3,0,6,0,16,-5,-5,-7,-1,9,-4,4,6,14,7,6,-1,-2,3,2,13,2,-3,-1,-5,3,4,-8,-8,4,3,-5,3,-2,6,4,-8,-3,-9,-7,6,9,4,7,-5,3,-4,0,3,-2,-9,-2,-11,-3,-13,-3,-9,8,-3,6,-23,-23,-2,4,-5,-18,-14,-1,-7,0,-21,-21,-9,24,16,4,11,7,-9,5,-15,-18,-5,-7,-5,-13,-17,-7,-4,17,4,-4,12,0,-8,4,-17,-10,-3,6,-23,-8,-8,-14,-2,8,7,11,-10,2,11,1,-13,-15,-14,-9,-34,4,-20,-1,-3,17,-4,13,3,0,-11,9,-2,2,-11,-1,-8,19,-6,0,-7,3,9,11,-6,11,0,-8,9,-20,-2,-10,4,12,-3,23,8,-4,5,15,1,10,3,20,-2,-18,-5,6,-5,16,6,30,16,-24,2,-1,2,8,31,29,-6,10,-8,-7,-24,-12,-7,-5,-22,-17,-21,2,-13,-3,3,7,-2,-12,4,-12,-7,-4,-22,5,-27,-16,-8,-5,-16,7,4,-3,20,17,9,-6,-5,5,-7,0,-9,6,15,25,29,37,15,-3,12,13,18,21,-1,7,17,11,-19,25,31,17,-2,-3,-9,-22,-12,-2,1,7,11,5,0,19,1,13,7,-7,-11,-14,5,-21,-8,-11,-3,11,-10,-12,-6,-7,7,40,11,-2,-5,-10,6,-6,-3,-12,-3,5,-15,-5,13,5,1,14,17,-3,-6,1,2,3,8,-3,3,10,-10,-7,-2,1,-4,4,3,20,-5,-4,11,-8,-1,-7,-9,-20,-20,0,-5,24,12,22,-5,-13,-3,-12,-6,-6,-5,-15,-15,-20,-16,-23,22,7,-4,14,1,-2,-8,5,12,16,-9,3,6,-2,-5,-4,-21,-12,5,15,9,8,-14,-15,-4,-4,-2,-1,4,-8,-18,-8,-4,-5,-18,24,8,-2,-7,6,7,-1,-4,-11,3,-2,-3,2,-10,-3,3,17,-5,4,-6,7,0,-5,-11,-4,6,12,3,10,-9,-14,4,8,2,2,-7,19,-1,-14,3,9,14,13,-19,8,-1,-6,4,25,16,13,7,-4,3,3,2,0,-8,3,-4,-11,-10,2,18,32,8,13,4,-3,-2,-1,-5,-25,-13,2,-15,-14,0,17,27,12,19,13,-11,11,-4,-6,4,-11,-6,-23,-10,4,-2,0,23,-9,6,6,5,3,3,12,2,4,12,-15,8,6,-6,6,6,-15,-19,-3,6,3,14,17,14,8,-4,6,-2,-4,-2,3,2,6,-13,-20,-22,-9,8,9,5,2,4,3,-2,0,-5,1,2,-8,-18,-5,-16,0,-13,0,-5,-14,-7,-2,-5,8,1,-7,-10,15,-2,3,-2,0,-5,-15,-3,5,14,-6,-4,20,0,9,-20,10,-2,3,-14,-4,-11,-2,-5,-11,5,-2,-4,10,-1,0,-10,9,8,3,-1,0,4,-2,-7,-9,-11,-1,-15,-9,-9,4,-3,11,1,-2,6,2,-8,-13,-4,-7,-16,-18,-16,-18,-9,-5,-3,};

class Neuron {

	int* w;
	int s;
	int m;

public:

	Neuron (int m=256) : m(m), s(50) {
		w=new int [m];
	}

	~Neuron() {
		delete[] w;
	}

	void changeWeight(int d, int * x) {
		for (int i=0; i<m; i++)
			w[i]+=(d*x[i]);
	}

	int adder (int * x) {
		int nec=0;
		for (int i=0; i<m; i++)
			nec+=(x[i]*w[i]);
		return nec;
	}

	int activator (int nec) {
		return 1 ? (nec>=s) : 0; 
	}

	int transfer (int *x) {
		return activator (adder (x));
	}


	friend class Perceptron;
};

class Perceptron {
	
	Neuron * neurons;
	int n,m;

	bool equal (int *a, int *b){
		for (int i=0; i<n; i++) {
			if (a[i]!=b[i]) return false;
		}
	return true;
	}

public:

	Perceptron (int n=10, int m=256) : n(n), m(m) {
		neurons = new Neuron[n];
	}

	~ Perceptron () {
		delete[] neurons;
	}

	int* recognize (int * x) {
		int * y=new int[10];
		for (int i=0; i<n; i++)
			y[i]=neurons[i].transfer(x);
		return y;
	}

	void initWeight() {
		for (int i=0; i<n; i++)
			for (int j=0; j<m; j++)
			neurons[i].w[j]=weight[i][j];
	}

	bool teach (int * x, int * y) {
		int dist;
		int * t = recognize(x);
		bool f=false;
		while (!equal (t,y)) {
			for (int i=0; i<n; i++) {
				dist=y[i]-t[i];
				neurons[i].changeWeight(dist,x);
				f=true;
				delete[] t;
				t=recognize(x);
			}
		}
		delete[] t;
		return f;
	}
	
	
};



void CreateImage16x16(bool ** matr,int m, int n){
	int xtop[3]={-1}, xbottom[3]={-1}, yleft[3]={-1}, yright[3]={-1};
	int k=0;
	bool lf=false;
	for (int j=0; j<n; j++){
		int cnt=0;
		for (int i=0; i<m; i++){
			if (matr[i][j]==0) cnt++;}
		if (!lf)
			if (cnt<m-1) { yleft[k]=j; lf=true; }
		if (lf)
			if (cnt==m) {yright[k]=j; lf=false; k++;}
	}
	int N=k;
	for (int k=0; k<N; k++){
		bool tf=false;
		for (int i=0; i<m; i++){
			int cnt=0;
			for (int j=yleft[k]; j<yright[k]; j++)
				if (matr[i][j]==0) cnt++;
			if (!tf) 
				if (cnt<(yright[k]-yleft[k])) {xtop[k]=i; tf=true; }
			if (tf)
				if (cnt==(yright[k]-yleft[k])) {xbottom[k]=i; tf=false; break;}
		}
	}
	switch (N) {
		case 1 : { if ((yright[0]-yleft[0])>2*(xbottom[0]-xtop[0])) {
					int alg=(yright[0]-yleft[0])/3;
					yright[2]=yright[0];
					yright[0]=yleft[0]+alg;
					yleft[1]=yright[0];
					yright[1]=yleft[1]+alg;
					yleft[2]=yright[1];
					xbottom[1]=xbottom[0];
					xbottom[2]=xbottom[0];
					N=3;
					int h=xbottom[0];
					for (int k=0; k<N; k++){
					bool tf=false;
						for (int i=xtop[0]; i<h; i++){
							int cnt=0;
							for (int j=yleft[k]; j<yright[k]; j++)
								if (matr[i][j]==0) cnt++;
							if (!tf) 
								if (cnt<(yright[k]-yleft[k])) {xtop[k]=i; tf=true; }
							if (tf)
								if (cnt==(yright[k]-yleft[k])) {xbottom[k]=i; tf=false; break;}
						}
					}
				 }
				 else if ((yright[0]-yleft[0])>(xbottom[0]-xtop[0])-1) {
					 int alg=(yright[0]-yleft[0])/2;
					 yright[1]=yright[0];
					 yright[0]=yleft[0]+alg;
					 yleft[1]=yright[0];
					 xbottom[1]=xbottom[0];
					 N=2;
					 int h=xbottom[0];
					 for (int k=0; k<N; k++){
					    bool tf=false;
						for (int i=xtop[0]; i<h; i++){
							int cnt=0;
							for (int j=yleft[k]; j<yright[k]; j++)
								if (matr[i][j]==0) cnt++;
							if (!tf) 
								if (cnt<(yright[k]-yleft[k])) {xtop[k]=i; tf=true; }
							if (tf)
								if (cnt==(yright[k]-yleft[k])) {xbottom[k]=i; tf=false; break;}
						}
					 }
				 }
				 break;}
		case 2 : {if ((yright[0]-yleft[0])>(xbottom[0]-xtop[0])-1) {
					int alg=(yright[0]-yleft[0])/2;
					yleft[2]=yleft[1];
					yright[2]=yright[1];
					xbottom[2]=xbottom[1];
					xtop[2]=xtop[1];
					yright[1]=yright[0];
					yright[0]=yleft[0]+alg;
					yleft[1]=yright[0];
					xbottom[1]=xbottom[0];
						N=3;
						int h=xbottom[0];
						for (int k=0; k<2; k++){
							bool tf=false;
							for (int i=xtop[0]; i<h; i++){
								int cnt=0;
								for (int j=yleft[k]; j<yright[k]; j++)
									if (matr[i][j]==0) cnt++;
								if (!tf) 
									if (cnt<(yright[k]-yleft[k])) {xtop[k]=i; tf=true; }
								if (tf)
									if (cnt==(yright[k]-yleft[k])) {xbottom[k]=i; tf=false; break;}
							}
						}
					}
				 else if ((yright[1]-yleft[1])>(xbottom[1]-xtop[1])-1) {
					int alg=(yright[1]-yleft[1])/2;
					yright[2]=yright[1];
					yright[1]=yleft[1]+alg;
					yleft[2]=yright[1];
					xbottom[2]=xbottom[1];
						N=3;
						int h=xbottom[1];
						for (int k=1; k<3; k++){
							bool tf=false;
							for (int i=xtop[1]; i<h; i++){
								int cnt=0;
								for (int j=yleft[k]; j<yright[k]; j++)
									if (matr[i][j]==0) cnt++;
								if (!tf) 
									if (cnt<(yright[k]-yleft[k])) {xtop[k]=i; tf=true; }
								if (tf)
									if (cnt==(yright[k]-yleft[k])) {xbottom[k]=i; tf=false; break;}
							}
						}
					}
				 break;}
		default : break; 
	}

	for (int k=0; k<N; k++) {
		XY[0].x=0;
		XY[16].x=xbottom[k]-xtop[k];
		XY[8].x=XY[16].x/2;
		XY[4].x=XY[8].x/2;
		XY[2].x=XY[4].x/2;
		XY[1].x=XY[2].x/2;
		XY[3].x=(XY[4].x+XY[2].x)/2;
		XY[6].x=(XY[8].x+XY[4].x)/2;
		XY[5].x=(XY[6].x+XY[4].x)/2;
		XY[7].x=(XY[8].x+XY[6].x)/2;
		XY[12].x=(XY[16].x+XY[8].x)/2;
		XY[10].x=(XY[12].x+XY[8].x)/2;
		XY[14].x=(XY[16].x+XY[12].x)/2;
		XY[9].x=(XY[10].x+XY[8].x)/2;
		XY[11].x=(XY[12].x+XY[10].x)/2;
		XY[13].x=(XY[14].x+XY[12].x)/2;
		XY[15].x=(XY[16].x+XY[14].x)/2;
		
		XY[0].y=0;
		XY[16].y=yright[k]-yleft[k];
		XY[8].y=XY[16].y/2;
		XY[4].y=XY[8].y/2;
		XY[2].y=XY[4].y/2;
		XY[1].y=XY[2].y/2;
		XY[3].y=(XY[4].y+XY[2].y)/2;
		XY[6].y=(XY[8].y+XY[4].y)/2;
		XY[5].y=(XY[6].y+XY[4].y)/2;
		XY[7].y=(XY[8].y+XY[6].y)/2;
		XY[12].y=(XY[16].y+XY[8].y)/2;
		XY[10].y=(XY[12].y+XY[8].y)/2;
		XY[14].y=(XY[16].y+XY[12].y)/2;
		XY[9].y=(XY[10].y+XY[8].y)/2;
		XY[11].y=(XY[12].y+XY[10].y)/2;
		XY[13].y=(XY[14].y+XY[12].y)/2;
		XY[15].y=(XY[16].y+XY[14].y)/2;
		
		int* Result=new int [256];
		

		for (int kx=0; kx<16; kx++)
			for (int ky=0; ky<16; ky++){
				int nSymbol=0;
				for (int i=xtop[k]+XY[kx].x; i<xtop[k]+XY[kx+1].x;i++){	
					for (int j=yleft[k]+XY[ky].y; j<yleft[k]+XY[ky+1].y; j++)
						{if (matr[i][j]==1) nSymbol++;}	
				}
				
					if (nSymbol>0) 
						Result[(kx*16)+ky]=1;
					else 
						Result[(kx*16)+ky]=-1;
			}
			
			int sc=0; bool fl=true;
			for (int i=0; i<16; i++){	
				if ((Result[i]==1)&&(Result[i+15*16]==1)) sc++;
				if ((Result[i*16]==1)&&(Result[16*i+15]==1)) sc++;
			}
            
			if (sc==32) { 
				yleft[k]+=XY[1].y;
				yright[k]-=(XY[16].y-XY[15].y);
				xtop[k]+=XY[1].x;
				xbottom[k]-=(XY[16].x-XY[15].x);
				int mm=xbottom[k]-xtop[k]+2;
				int nn=yright[k]-yleft[k]+2;
				bool ** Hell=new bool *[mm];
				for (int i=0; i<xbottom[k]-xtop[k]+2; i++)
					Hell[i]=new bool[nn];
				for (int i=0; i<mm; i++)
					for (int j=0; j<nn; j++)
						Hell[i][j]=0; 
				for (int i=1; i<mm-2; i++)
					for (int j=1; j<nn-2; j++)
						Hell[i][j]=matr[xtop[k]+i-1][yleft[k]+j-1];


				fl=false;
				CreateImage16x16(Hell,mm,nn);
				for (int i=0; i<mm; i++)
					delete[] Hell[i];
				delete[] Hell;

				}
			
			if (fl) {
				Q.push(Result);
			
			}		
			
			
			
			
	}
		
		
}



int main()
{  
	
	bool** matr=new bool* [MaxN];
	for (int i=0; i<MaxN; i++)
		matr[i]=new bool[MaxN];

	for(int ii=0; ii<MaxN; ii++)
		for (int jj=0; jj<MaxN; jj++)
			matr[ii][jj]=0;

	

	char k;
	bool fb=true;
	bool fw=true;
	int l=0;
	int j=0;
	int N=0;
	int M=0;
	int s=0;
	while(fw){
		scanf("%c",&k);
		switch(k) {
			case '#' : {matr[l][j]=1; j++; fb=false; break;}
			case '@' : {matr[l][j]=1; j++; fb=false; break;}
			case '\n': {l++; N=j; j=0; s=0; break;}
			default : {matr[l][j]=0; j++; s++; break;}
		}
		if ((s==N)&&(!fb)){M=l; fw=false; }

	}

    	
	CreateImage16x16(matr,++M,N);

	Perceptron P;
	P.initWeight();
	
	while (!Q.empty()) {
		int * e=Q.front();
		int * t=P.recognize(e);
		for (int i=0; i<10; i++){
			if (t[i]==1) {
				cout<<i; i=10; 
			}
		}
		delete[] t;
		Q.pop();
	}
	
	
	for (int i=0; i<MaxN; i++)
		delete[] matr[i];
	delete[] matr;

					
	return 0;
}

