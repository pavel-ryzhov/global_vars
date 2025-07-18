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

int weight[10][256]={31,24,32,-1,8,9,10,3,-5,-4,8,-7,-2,-4,-14,1,17,16,-6,-2,10,-3,-2,-7,-9,0,4,-10,-9,-9,-16,-3,9,0,3,-3,0,11,-4,-12,-7,6,16,-4,10,2,-3,-3,11,5,-4,-15,-2,0,3,-10,-1,9,5,-9,0,-15,3,-15,11,-4,1,13,26,21,3,6,-7,13,14,-3,7,14,14,22,4,-4,10,7,14,6,-4,-3,-5,3,4,2,-4,0,12,15,21,15,19,0,4,-4,-12,-14,-15,-2,-19,-33,-20,-5,8,33,37,16,-6,-20,-5,-7,-4,-14,-20,-19,-13,-12,-13,-24,-12,7,22,16,-7,-17,-6,1,3,-16,-6,0,-2,-16,-5,-14,23,4,21,13,2,-15,-10,-12,-4,-12,-5,-12,-12,-13,-1,4,4,-15,14,34,13,11,3,-2,7,0,-4,-10,-2,-6,7,-8,2,-2,9,10,11,14,5,20,-1,-5,-3,7,-1,-10,0,-5,-18,-9,16,3,6,7,13,11,5,-3,-5,5,8,0,-1,0,12,-26,-3,-2,4,14,6,16,19,12,-11,13,3,-11,-2,-1,-3,-19,9,10,3,-5,5,9,-1,-3,-12,-3,1,-19,-1,10,-2,-12,16,-2,-6,-6,-25,-14,-5,-11,-16,-10,-7,-7,-2,13,-15,-1,11,22,-12,5,-40,-5,-10,-1,-25,-8,-8,10,30,32,14,29,-7,34,24,10,-23,-3,-5,-3,-12,-11,3,-9,-11,-20,-4,26,22,22,5,-10,15,4,12,6,-14,7,-2,6,-1,-14,-21,23,23,-24,2,-10,-3,15,24,2,-5,20,-7,-12,-1,-32,-26,10,-9,-10,15,0,5,22,14,25,13,33,4,23,6,-4,-8,8,-2,5,4,-18,4,10,18,9,9,2,-21,17,-16,-13,3,16,20,29,-3,-14,0,-19,13,5,-10,13,4,-2,-24,-11,3,17,30,19,10,-10,-22,-25,1,11,-2,-23,-23,-27,-8,-26,-18,15,14,-16,-23,-28,-15,6,-7,6,-8,5,0,-1,-11,-23,-7,25,4,-4,-35,-15,10,-19,-9,13,-3,7,-8,-34,-2,1,19,7,-8,10,-6,-19,-4,3,4,-5,-3,-8,-5,13,16,20,4,-17,-2,-39,-1,-14,-3,11,-9,-8,-5,-6,12,8,15,12,-33,-27,-3,-39,3,-19,13,7,-5,13,8,-5,4,29,36,18,3,-33,11,6,-17,-24,-6,-15,7,14,0,1,3,18,2,-9,-1,-8,7,-6,-10,-26,-12,-5,7,16,-4,12,-2,15,1,11,25,24,20,1,18,28,-1,-15,-16,-9,2,-25,-11,0,2,16,27,59,7,-4,11,4,19,6,13,-6,-3,-19,-11,-5,-12,1,3,-10,-3,-3,-8,1,-21,-20,1,3,-12,-4,-18,-6,-6,-6,-21,-2,19,1,11,2,-7,1,-13,-8,-17,-14,0,-3,6,-8,-8,-4,8,-7,-9,4,5,5,-9,-9,-7,-7,-5,7,5,-1,7,-3,-6,-8,-6,-9,19,11,5,-1,6,-1,2,0,8,-2,0,10,12,9,7,0,7,-3,-10,-10,11,-7,-4,0,-6,1,12,7,8,29,10,-9,7,-1,-22,2,3,-7,4,-4,9,2,27,7,6,-3,-16,-6,2,-11,-22,-23,-4,-19,0,-3,8,11,10,-11,0,5,7,2,6,0,-15,-4,-8,-8,18,5,4,7,-8,-34,4,25,17,6,1,8,3,1,-7,-2,4,-17,-6,-14,-15,-38,9,1,-6,5,13,6,4,-5,-9,3,3,-13,-19,-15,-29,-37,16,-8,-6,-11,6,8,12,1,-3,3,-9,-12,-6,-18,-4,-1,21,5,0,-1,15,31,19,2,8,-2,-13,-4,12,-4,8,15,17,3,-10,10,16,24,27,-6,-4,5,3,2,2,-13,10,21,18,22,12,13,4,-3,4,0,7,11,-2,-10,-12,4,14,34,16,41,19,-21,-20,-22,-2,-12,-4,-3,-6,-1,-4,15,39,19,91,24,68,29,-17,40,3,-3,-12,-13,11,-26,-59,-9,-26,-22,13,12,-35,-6,-7,-33,12,-5,-37,-9,-17,2,-9,-6,-5,-41,12,15,16,-32,39,21,10,-6,0,-3,-29,0,-2,0,-16,-29,22,-12,22,-19,21,-16,-15,-7,-28,-13,-4,-16,-7,-28,-17,30,-9,-36,41,-45,44,34,26,-7,-9,32,2,-2,14,5,59,31,-4,-36,-19,-51,-22,-36,51,31,19,27,28,32,9,17,26,36,39,-35,-52,-81,14,-40,-7,7,-19,-23,-11,12,-15,12,1,-11,45,2,-14,-22,19,-20,35,35,-15,-38,12,4,2,5,-36,-52,48,-5,27,-20,-25,-8,7,19,6,23,24,7,2,-4,2,-7,6,-35,12,-48,-29,-39,13,0,-26,2,9,-2,6,48,30,16,44,20,24,-20,-18,-20,-5,-30,26,-15,23,-23,23,15,85,-1,24,-15,-16,-1,8,-3,-3,-45,-17,-29,-8,4,11,-12,-10,56,48,17,-6,-6,28,15,-14,-54,4,9,34,4,-2,-23,33,9,65,24,-8,9,-12,47,17,-23,-14,-7,-4,-49,24,-15,-17,-1,47,7,-28,-10,-32,14,16,-2,3,1,15,-19,-3,-23,3,-19,81,71,9,-3,-31,15,-13,4,-38,2,-21,-18,-35,-11,-44,-30,9,9,9,7,-2,-10,-3,5,-4,-15,-7,-1,7,-6,2,-2,5,0,-5,-9,-9,-14,3,-12,-14,-7,0,-12,-2,2,1,1,11,-12,3,-15,-4,-10,-7,-18,-7,0,4,-11,3,1,2,2,12,-2,-9,-15,-6,-11,-11,-21,1,-12,-2,-5,-3,-10,-6,-8,6,-6,-3,0,-10,-2,2,-7,-2,-10,4,7,11,-2,-3,-4,10,-11,-1,-7,0,-2,1,-5,5,-2,9,2,10,-6,-6,-9,1,1,-6,6,-2,5,-4,8,2,5,1,-6,2,-2,-4,-7,0,-2,1,8,6,3,-3,-7,-12,3,-4,-10,4,-5,4,-2,5,10,9,12,17,10,13,0,7,2,6,1,4,4,12,5,15,15,23,16,6,9,6,0,9,7,2,-4,5,6,4,5,2,17,4,16,2,9,13,4,10,15,2,2,5,-8,3,-4,4,13,4,4,6,10,15,9,12,17,8,3,4,-9,11,0,19,7,-17,-3,10,21,4,2,10,12,15,6,-6,4,1,-3,6,-4,-11,-17,-2,-8,-6,-2,0,-6,9,-3,-2,-7,2,1,13,-9,-10,-21,-19,-16,-21,-14,-5,-6,-5,4,-2,-5,3,11,16,6,3,-17,-9,-27,-17,-20,-4,-18,-2,-6,3,11,22,-6,71,2,12,40,28,-3,14,-34,-3,-45,2,-31,-5,15,50,-25,8,-33,14,17,37,23,2,-18,-16,-46,-26,-36,-27,-13,40,32,-5,3,23,-13,0,17,12,-7,-36,11,41,39,-19,-55,6,-11,-20,4,-5,17,34,11,-6,-43,22,1,9,-13,12,-39,-15,-37,-54,-8,-43,13,30,-6,-3,22,1,-27,-31,-6,-2,-21,-45,0,42,-5,43,15,12,35,26,-22,17,-2,-5,-28,8,-13,15,3,7,18,-23,-1,4,40,9,-27,-2,14,16,-42,-35,-7,-13,49,-13,-6,3,48,-18,30,-9,-1,-7,8,18,39,22,11,29,0,52,11,29,51,-42,-12,1,-53,-11,-6,-22,9,-21,-21,-43,37,3,-10,-29,-35,-6,37,-52,-23,7,4,-4,-56,-8,-7,22,-16,-22,-35,-25,-47,-7,24,-29,-18,19,-32,-17,-35,21,26,-3,18,26,-54,3,17,23,-21,-29,-1,22,-7,11,-17,-5,17,-39,-8,23,-7,25,20,-7,33,-7,8,32,11,10,27,-21,34,32,16,79,28,-3,-24,-11,-18,0,17,40,4,18,10,-13,9,22,-3,52,43,-5,2,-3,-53,-26,13,11,32,-35,41,-1,8,7,-48,36,27,-3,48,-8,-20,-26,-14,0,16,-17,-16,9,-20,-1,-8,28,11,14,-7,-9,10,-10,-21,-8,-12,-21,0,-6,-2,-7,21,7,-16,-23,-15,-7,-11,-4,-6,-17,11,-30,-11,-13,-26,20,-23,-3,0,-16,-4,18,3,0,-4,10,-2,-32,-21,-2,-48,-8,37,-2,-27,-7,2,5,-8,-20,-20,-4,6,-29,-42,-13,6,-33,31,34,-16,15,-2,11,13,11,10,38,-5,-22,-26,-14,8,-18,-4,30,2,-3,5,5,-20,4,-14,18,6,2,-37,-25,-22,-32,-34,41,29,4,-27,-12,-16,3,0,6,10,10,25,5,4,-7,-29,31,31,-12,-25,2,-18,21,21,-4,13,10,-5,4,20,30,-29,15,42,17,-11,3,-21,-6,-5,-5,10,8,-9,-4,1,13,-23,12,20,12,12,4,-15,5,-18,-25,0,15,12,4,-8,13,-23,18,51,53,4,17,31,16,-13,-10,-8,14,1,18,9,7,-10,4,3,14,3,-3,22,6,-12,0,-10,7,-3,24,-24,0,-11,5,4,10,-4,-13,14,8,-6,-3,-18,-19,18,23,-26,30,25,0,-17,27,36,37,20,21,-7,11,5,-6,-7,4,6,-11,-9,-15,0,14,4,15,5,14,-14,14,-9,-13,-11,-32,-4,45,28,34,7,15,-3,-16,-9,6,8,-26,-36,-25,-17,7,10,-3,-3,20,29,47,28,11,6,-8,-9,-12,-3,-2,-6,-7,-3,7,23,15,5,-1,-5,13,8,7,-14,6,2,4,-17,-16,1,9,23,14,14,15,-3,8,5,6,14,10,-2,-7,-13,-2,0,9,10,-9,17,-3,-11,3,-1,-2,12,6,0,2,-20,-5,8,21,5,23,8,8,-19,8,12,6,-3,10,5,4,-10,4,14,-5,-10,11,3,3,2,4,-4,-6,-17,-9,-12,8,-1,-4,21,10,-7,16,1,-8,-4,-23,1,-12,-9,-9,-8,-3,-22,-8,1,-28,-11,14,10,-15,-9,-21,-11,-4,7,2,0,16,-7,-5,-8,-6,22,7,-5,-13,-17,12,-15,-13,-10,-7,-2,-6,-4,7,-2,-5,-3,1,2,0,4,14,4,-7,-11,-8,-7,-1,-3,-8,-15,-3,-1,12,18,2,-4,16,14,-3,9,14,-11,2,-2,1,-9,3,-9,17,11,-3,7,5,37,25,5,-2,10,2,22,-7,-13,-15,1,11,-2,8,8,16,7,2,-5,-4,3,-2,11,0,-1,-3,-9,3,2,-6,-8,6,5,-7,7,-4,8,2,-8,-3,-17,-13,10,9,0,9,-7,7,-4,2,9,-2,-11,-2,-15,-3,-21,-7,-11,8,-7,8,-27,-25,6,4,-5,-16,-14,-1,-23,-2,-23,-21,-3,50,28,14,25,17,-1,19,-21,-24,-7,7,-9,-15,-33,3,-4,25,8,-4,-2,-20,-16,0,-3,-32,-11,-2,-45,-10,-18,-22,-4,6,9,1,2,12,23,-1,-19,-9,-34,-11,-38,8,-28,-3,5,29,-16,31,13,-8,-13,13,-34,10,-11,-7,-34,23,-12,0,-29,3,13,17,-6,9,24,-10,1,-28,-4,-6,0,4,-15,35,6,2,13,11,15,20,-11,6,-4,-30,-19,2,-5,10,14,46,34,-26,8,3,24,22,59,37,8,34,0,-5,-34,2,17,3,-12,-15,-53,-20,-11,-11,21,37,-4,-22,4,-14,-19,-8,-34,-1,-63,-18,-8,-9,-30,19,14,-7,20,27,17,8,5,5,7,14,-9,18,3,47,31,37,21,-5,26,17,14,21,1,7,7,3,-25,57,35,35,-14,9,-1,-18,-12,16,19,-1,17,7,6,17,-23,21,23,-9,-25,-28,5,-29,-4,-1,-11,-1,-10,-22,18,-19,13,46,27,22,-3,-2,12,14,-31,-18,-21,3,-7,-17,15,-9,9,28,13,3,-22,-1,-2,9,14,-3,3,4,-2,-9,8,-17,18,0,19,-6,21,6,19,-2,-3,9,-5,-16,-30,-6,7,14,24,48,-11,-29,-11,-20,-22,-10,3,-29,-15,-30,-34,-29,30,-5,-6,17,20,5,1,14,15,21,-8,-8,11,-1,-4,9,-40,-19,8,34,14,21,-19,-24,1,-9,-5,-2,5,-3,-43,-19,-9,-16,-31,33,15,-3,0,15,12,6,1,-26,4,3,4,-7,-13,-4,2,32,10,9,-7,-8,-7,0,-46,-5,7,1,-10,11,-28,-19,15,13,5,13,-12,14,-4,-17,-2,6,3,10,-28,7,2,9,7,40,11,24,2,5,8,0,-13,11,-9,14,1,-8,-17,5,25,29,23,18,13,2,5,8,-4,-32,-10,15,-10,-17,-1,16,30,13,12,30,-16,24,-3,-3,-5,-4,-1,-22,-19,11,-11,1,26,-10,1,13,24,0,4,7,-5,3,5,-26,-3,-5,-5,11,13,-28,-44,2,11,10,31,30,7,17,-9,1,-21,-3,3,4,-7,3,-22,-25,-37,-10,15,24,12,19,17,4,5,3,14,12,13,-13,-23,6,-15,5,-32,19,-8,-15,4,-3,4,11,-4,-26,-11,28,-1,10,-5,-9,-12,-18,10,6,15,-9,-1,23,1,14,-25,25,1,10,-13,-5,-14,1,0,-16,16,5,-3,7,-6,-23,-21,12,13,-2,-6,-9,9,9,-24,-22,-14,-6,-18,6,-20,3,-4,18,-6,1,5,-3,-25,0,-11,-20,-21,-23,-31,-19,-14,-6,-2,};

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
			default : {matr[l][j]=0; j++; 
						if (k=='.') s++; 
						break;}
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

