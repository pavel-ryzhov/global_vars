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

int weight[10][256]={31,24,32,-1,8,9,10,3,-5,-4,8,-7,-2,-4,-14,1,17,16,-6,-2,10,-3,-2,-7,-9,0,4,-10,-9,-9,-16,-3,9,0,3,-3,0,11,-4,-12,-7,6,16,-4,10,2,-3,-3,11,5,-4,-15,-2,0,3,-10,-1,9,5,-9,0,-15,3,-15,11,-4,1,13,26,21,3,6,-7,13,14,-3,7,14,14,22,4,-4,10,7,14,6,-4,-3,-5,3,4,2,-4,0,12,15,21,15,19,0,4,-4,-12,-14,-15,-2,-19,-33,-20,-5,8,33,37,16,-6,-20,-5,-7,-4,-14,-20,-19,-13,-12,-13,-24,-12,7,22,16,-7,-17,-6,1,3,-16,-6,0,-2,-16,-5,-14,23,4,21,13,2,-15,-10,-12,-4,-12,-5,-12,-12,-13,-1,4,4,-15,14,34,13,11,3,-2,7,0,-4,-10,-2,-6,7,-8,2,-2,9,10,11,14,5,20,-1,-5,-3,7,-1,-10,0,-5,-18,-9,16,3,6,7,13,11,5,-3,-5,5,8,0,-1,0,12,-26,-3,-2,4,14,6,16,19,12,-11,13,3,-11,-2,-1,-3,-19,9,10,3,-5,5,9,-1,-3,-12,-3,1,-19,-1,10,-2,-12,16,-2,-6,-6,-25,-14,-5,-11,-16,-10,-7,-7,-2,13,-15,-1,10,19,-15,4,-41,-6,-11,0,-24,-7,-7,13,29,27,11,26,-8,29,21,5,-22,-8,-8,-2,-13,-14,0,-8,-12,-17,-5,25,17,13,0,-11,16,5,9,9,-15,8,-5,5,-4,-13,-18,22,20,-29,3,-9,-2,16,23,1,-6,21,-10,-5,-2,-25,-21,13,-8,-11,16,3,8,27,13,28,12,32,5,28,5,3,-5,11,1,4,5,-11,7,13,19,4,8,5,-18,20,-17,-8,6,9,21,26,-4,-11,-1,-16,14,8,-11,14,3,-3,-25,-10,4,20,29,20,9,-7,-23,-20,0,0,-1,-22,-24,-28,-9,-27,-15,20,13,-17,-24,-27,-12,9,-8,5,-7,4,1,4,-14,-18,-6,22,3,-7,-36,-12,13,-16,-8,10,0,14,-5,-29,-3,0,14,4,-7,9,-7,-16,-5,8,5,2,-2,-3,-4,8,11,21,3,-16,-1,-38,-2,-11,-2,14,-10,-15,-4,-7,9,3,12,11,-34,-26,-2,-36,0,-16,14,12,-6,18,7,0,3,32,31,15,0,-34,12,9,-16,-19,-3,-12,6,11,-1,6,4,21,-1,-10,0,-5,10,1,-9,-21,-9,0,6,15,-3,17,-1,18,-2,16,26,29,19,2,17,31,2,-10,-15,-10,3,-24,-12,3,-1,19,26,60,6,-5,10,3,18,5,14,-5,-2,-16,-12,-6,-13,0,2,-11,-4,-4,-9,6,-16,-15,2,2,-5,-3,-13,-5,-3,-5,-20,-3,16,0,12,1,-6,0,-10,-11,-14,-13,1,0,9,-3,-5,-5,5,-4,-6,1,8,0,-6,-12,-8,-10,-4,6,4,2,8,-4,-7,-5,-1,-6,20,10,10,-2,5,-4,3,-3,7,-3,3,13,11,10,10,-1,8,-4,-5,-13,10,-12,-5,-7,-9,0,13,10,7,30,11,-10,6,-4,-21,-3,2,-8,1,-7,8,3,26,8,7,0,-17,-9,1,-10,-21,-20,-5,-16,-1,2,9,16,9,-8,1,6,6,1,5,3,-14,-3,-5,-5,19,4,5,6,-11,-33,3,24,16,5,0,11,4,-2,-6,-3,5,-18,-7,-13,-16,-39,8,0,-9,2,12,1,3,-8,-6,2,2,-12,-18,-16,-32,-38,13,-7,-5,-14,3,5,11,-2,0,6,-8,-9,-3,-19,-7,-4,20,4,-1,-6,14,30,20,1,11,-3,-10,-5,13,-7,7,14,16,-4,-9,3,13,17,24,-9,-1,2,2,-5,1,-14,7,20,15,17,11,10,7,-2,5,-1,10,8,-1,-13,-9,5,17,33,15,36,18,-20,-17,-19,-1,-9,3,0,-3,-4,-3,16,36,18,86,21,67,26,-20,39,0,4,-15,-12,2,-25,-48,-6,-23,-17,16,13,-28,-5,-8,-42,11,0,-32,-6,-18,3,-10,-7,-10,-34,17,24,13,-33,32,26,7,-9,-1,0,-18,-1,1,-5,-13,-24,25,-1,23,-16,16,-7,-16,-4,-25,-2,-9,-15,-8,-27,-34,31,-8,-33,34,-44,35,27,23,-6,-6,23,-3,-13,11,8,60,30,-5,-31,-14,-38,-11,-25,48,36,24,22,19,27,10,26,25,35,36,-34,-53,-74,13,-33,-4,8,-12,-26,-16,9,-16,13,-4,-20,34,-3,-19,-21,18,-15,34,42,-18,-41,3,1,5,2,-35,-51,43,-8,24,-23,-24,-1,12,22,1,16,23,8,7,-3,-3,-10,3,-30,9,-45,-26,-36,12,7,-33,-1,4,3,9,49,39,13,43,19,17,-19,-19,-15,-6,-27,23,-8,24,-22,20,16,82,0,33,-28,-15,-24,5,-6,-2,-30,-18,-26,-7,-21,14,-5,-3,55,49,20,-9,-3,23,16,-13,-49,3,12,33,1,-1,-24,24,8,62,25,-11,6,-17,46,16,-8,-13,2,-3,-48,19,-14,-10,2,50,16,-29,-5,-29,17,11,11,6,2,12,-14,-4,-18,2,-8,72,56,6,-12,-22,8,-24,9,-31,-7,-18,-17,-28,-8,-35,-27,9,9,9,7,-2,-10,-3,5,-4,-15,-7,-1,7,-6,2,-2,5,0,-5,-9,-9,-14,3,-12,-14,-7,0,-12,-2,2,1,1,11,-12,3,-15,-4,-10,-7,-18,-7,0,4,-11,3,1,2,2,12,-2,-9,-15,-6,-11,-11,-21,1,-12,-2,-5,-3,-10,-6,-8,6,-6,-3,0,-10,-2,2,-7,-2,-10,4,7,11,-2,-3,-4,10,-11,-1,-7,0,-2,1,-5,5,-2,9,2,10,-6,-6,-9,1,1,-6,6,-2,5,-4,8,2,5,1,-6,2,-2,-4,-7,0,-2,1,8,6,3,-3,-7,-12,3,-4,-10,4,-5,4,-2,5,10,9,12,17,10,13,0,7,2,6,1,4,4,12,5,15,15,23,16,6,9,6,0,9,7,2,-4,5,6,4,5,2,17,4,16,2,9,13,4,10,15,2,2,5,-8,3,-4,4,13,4,4,6,10,15,9,12,17,8,3,4,-9,11,0,19,7,-17,-3,10,21,4,2,10,12,15,6,-6,4,1,-3,6,-4,-11,-17,-2,-8,-6,-2,0,-6,9,-3,-2,-7,2,1,13,-9,-10,-21,-19,-16,-21,-14,-5,-6,-5,4,-2,-5,3,11,16,6,3,-17,-9,-27,-17,-20,-4,-18,-2,-6,3,11,22,-6,63,0,6,36,24,-3,10,-28,-5,-35,-2,-33,-11,9,52,-17,8,-19,16,23,33,13,4,-26,-14,-48,-24,-40,-29,-19,40,28,-1,7,27,-7,-2,7,18,-15,-34,5,41,41,-19,-49,12,-11,-18,12,-3,3,28,11,0,-45,20,-3,9,-15,6,-37,-11,-39,-54,-2,-45,5,32,-14,3,10,-3,-33,-27,-8,-2,-21,-47,0,36,5,39,7,14,25,26,-30,17,-8,1,-32,10,-19,1,-3,7,24,-19,-1,10,30,1,-19,-6,20,18,-36,-37,3,-3,59,-13,-2,1,32,-24,22,-1,-3,-7,12,24,35,18,7,21,8,54,11,27,35,-36,-18,9,-55,1,-14,-20,3,-19,-21,-45,29,9,-12,-29,-45,6,35,-44,-15,1,2,-6,-42,-8,-3,20,-8,-20,-47,-13,-45,-1,18,-35,-12,15,-32,-23,-23,19,24,-5,18,24,-50,7,9,29,-27,-31,7,18,-3,5,-5,-5,7,-41,-4,23,-9,37,16,-5,25,-7,-2,32,7,12,19,-15,32,26,14,73,22,5,-26,-7,-28,4,15,42,0,24,4,-13,15,22,3,50,33,1,-8,3,-55,-22,7,15,22,-27,35,-1,10,5,-48,32,31,-1,42,-6,-24,-22,-16,-2,16,-11,-20,5,-12,-3,4,33,18,17,-4,-8,9,-9,-18,-9,-13,-18,1,-9,-1,-8,26,12,-9,-22,-12,-6,-8,-5,-5,-18,10,-35,-10,-16,-19,19,-16,2,3,-13,-5,17,2,-1,-7,7,-9,-29,-16,-3,-39,3,40,5,-22,-6,1,4,-9,-19,-19,-7,7,-22,-35,-10,9,-24,18,33,-17,14,1,10,14,10,13,33,-2,-19,-23,-13,7,-15,-1,27,1,-2,6,4,-17,7,-11,9,1,-5,-38,-26,-27,-33,-31,36,28,3,-26,-15,-13,6,5,1,7,5,22,0,1,-10,-24,34,34,-11,-20,1,-11,20,24,-3,12,5,0,7,27,27,-22,16,37,14,0,10,-14,-5,-2,-2,5,3,-4,1,6,22,-18,9,21,17,21,11,-10,6,-17,-18,-5,10,11,5,-5,18,-16,13,48,50,9,16,32,15,-10,-7,-3,13,0,15,6,10,-3,-7,2,13,-14,0,21,7,-9,-3,-7,6,-2,23,-21,-1,-8,4,1,9,-1,-8,13,9,-7,-2,-19,-16,17,22,-23,29,22,3,-14,22,9,32,23,18,-6,8,6,-5,-2,1,3,-6,-2,-8,5,11,3,10,8,13,-13,11,-14,-20,-8,-25,-1,40,29,33,16,14,-4,-13,-4,7,-5,-25,-27,-24,-22,8,17,4,6,20,29,47,28,11,6,-8,-9,-12,-3,-2,-6,-7,-3,7,23,15,5,-1,-5,13,8,7,-14,6,2,4,-17,-16,1,9,23,14,14,15,-3,8,5,6,14,10,-2,-7,-13,-2,0,9,10,-9,17,-3,-11,3,-1,-2,12,6,0,2,-20,-5,8,21,5,23,8,8,-19,8,12,6,-3,10,5,4,-10,4,14,-5,-10,11,3,3,2,4,-4,-6,-17,-9,-12,8,-1,-4,21,10,-7,16,1,-8,-4,-23,1,-12,-9,-9,-8,-3,-22,-8,1,-28,-11,14,10,-15,-9,-21,-11,-4,7,2,0,16,-7,-5,-8,-6,22,7,-5,-13,-17,12,-15,-13,-10,-7,-2,-6,-4,7,-2,-5,-3,1,2,0,4,14,4,-7,-11,-8,-7,-1,-3,-8,-15,-3,-1,12,18,2,-4,16,14,-3,9,14,-11,2,-2,1,-9,3,-9,17,11,-3,7,5,37,25,5,-2,10,2,22,-7,-13,-15,1,11,-2,8,8,16,7,2,-5,-4,3,-2,11,0,-1,-3,-9,3,2,-6,-8,6,5,-7,7,-4,8,2,-8,-3,-17,-13,10,9,0,9,-7,7,-4,2,9,-2,-11,-2,-15,-3,-21,-7,-11,8,-7,8,-27,-25,6,4,-5,-16,-14,-1,-23,-2,-23,-21,-3,48,26,14,27,17,1,21,-19,-26,-9,7,-9,-13,-31,3,-4,23,8,-6,0,-18,-16,-2,-7,-32,-17,-6,-49,-12,-18,-24,-4,4,7,1,0,12,23,-1,-19,-9,-34,-11,-40,4,-32,-1,1,27,-14,29,11,-8,-11,15,-34,12,-11,-7,-32,21,-14,0,-29,1,11,17,-8,11,24,-8,-1,-28,-8,-8,2,4,-13,35,4,2,9,11,13,20,-11,6,-6,-30,-23,0,-3,12,14,44,34,-26,6,3,24,22,59,35,6,34,-2,-7,-32,2,17,3,-14,-15,-53,-22,-13,-13,15,33,-6,-22,0,-18,-19,-8,-38,-1,-63,-18,-8,-9,-32,17,10,-7,20,29,15,8,3,5,3,14,-9,20,3,45,29,37,23,-5,26,19,12,23,1,9,7,3,-25,55,35,33,-16,9,-1,-18,-10,18,17,1,17,7,2,15,-25,17,19,-11,-27,-28,5,-31,-2,1,-11,-1,-12,-22,16,-21,11,44,21,20,-7,-2,12,12,-31,-16,-19,3,-9,-17,15,-11,3,28,9,-1,-26,-1,-2,7,16,-1,3,4,-4,-9,6,-21,10,-2,15,-8,15,4,19,-4,-1,9,-3,-16,-32,-8,3,12,20,46,-11,-27,-11,-22,-26,-12,1,-29,-17,-32,-36,-29,28,-3,-6,19,18,7,-3,10,13,19,-8,-8,9,-3,-8,1,-36,-13,12,32,12,19,-17,-22,-1,-5,-1,2,7,-7,-35,-17,-7,-10,-19,31,13,-3,-6,13,10,2,-3,-24,8,7,0,-7,-11,-2,4,28,4,5,-7,-6,-7,-6,-28,-5,9,3,-4,9,-18,-15,11,13,5,9,-12,14,-2,-17,-2,6,7,12,-24,9,4,3,7,34,17,20,6,3,14,6,3,9,-7,12,9,-4,-15,3,31,29,19,16,9,-2,1,6,-10,-30,-12,15,-4,-13,1,18,32,11,16,26,-10,20,-1,-5,1,-6,-1,-18,-11,11,-5,7,28,-10,3,9,18,0,4,7,-5,-3,9,-26,-1,-1,-3,13,13,-24,-34,-2,9,6,25,28,17,11,-5,1,-19,-7,5,8,-1,5,-18,-23,-35,-10,13,22,6,13,11,2,1,3,10,10,9,-13,-25,2,-17,-1,-10,13,-4,-17,0,-3,6,11,-2,-18,-11,22,-3,8,-7,-7,-10,-16,2,4,11,-7,-1,17,1,12,-23,17,-1,10,-13,-3,-12,-1,2,-18,12,7,-7,5,-6,-19,-19,8,13,0,-4,-5,9,1,-12,-20,-18,-6,-24,-2,-16,3,6,14,0,3,11,1,-1,-2,1,-20,-21,-21,-25,-23,-6,-2,2,};

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
		for (int i=m-1; i>=0; i--){
			int cnt=0;
			for (int j=yleft[k]; j<yright[k]; j++)
				if (matr[i][j]==0) cnt++;
			if (!tf) 
				if (cnt<(yright[k]-yleft[k])) {xbottom[k]=i+1; tf=true; }
			if (tf)
				if (cnt==(yright[k]-yleft[k])) {xtop[k]=i-1; tf=false; break;}
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
				 else if ((yright[0]-yleft[0])>(xbottom[0]-xtop[0])-3) {
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
		case 2 : {if ((yright[0]-yleft[0])>(xbottom[0]-xtop[0])-3) {
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
				 else if ((yright[1]-yleft[1])>(xbottom[1]-xtop[1])-3) {
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

