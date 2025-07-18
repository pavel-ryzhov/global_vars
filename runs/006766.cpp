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

int weight[10][256]={29,22,32,-1,4,7,12,3,-3,-6,8,-9,-2,-4,-16,-1,15,16,-8,0,10,-5,-8,-13,-11,-2,4,-14,-11,-11,-18,-5,9,0,7,-3,0,9,-6,-14,-9,4,18,-4,12,2,-5,-3,11,9,0,-15,-4,0,3,-16,1,7,5,-13,0,-17,3,-17,13,-6,1,9,28,23,3,10,-7,15,16,-1,5,12,16,24,4,-8,10,7,16,6,-6,-5,-5,-1,2,0,-4,-4,12,15,19,15,21,2,8,-2,-10,-12,-13,-4,-23,-35,-20,-3,8,35,35,18,-6,-22,-3,-13,0,-12,-22,-23,-13,-14,-13,-28,-16,7,24,16,-7,-19,-6,1,3,-16,-6,0,-4,-16,-5,-14,25,2,23,15,2,-17,-12,-16,-4,-10,-5,-10,-14,-13,-1,2,4,-17,18,38,13,9,3,-6,7,0,-4,-8,0,-6,7,-8,2,-2,15,8,9,14,1,16,-1,-3,-3,11,1,-10,0,-9,-18,-9,20,3,6,7,11,11,7,-1,-5,7,8,2,-1,4,16,-28,-5,-4,6,14,6,18,23,16,-11,17,3,-9,2,-1,-5,-21,7,10,5,-3,5,11,1,-3,-12,-3,5,-13,1,8,-4,-12,14,-6,-8,-8,-23,-14,-3,-9,-14,-10,-7,-11,-2,13,-17,-3,8,17,-15,2,-55,-8,-13,0,-24,-17,-9,7,37,39,19,26,-18,25,25,9,-34,0,-2,-4,-27,-18,-4,-22,-18,-17,-7,21,21,33,16,-9,8,17,11,-1,-23,6,-11,1,-2,-21,-24,26,24,-21,9,-11,2,22,39,-13,-4,27,-2,-15,0,-41,-39,15,-12,-15,18,-3,6,31,21,30,12,40,-1,22,15,-11,-9,7,-15,12,3,-17,3,21,17,10,8,3,-32,16,-11,-20,6,23,15,40,-8,-5,-3,-14,18,6,-13,18,-3,-5,-25,-4,2,24,23,14,15,-17,-27,-24,4,14,1,-34,-30,-42,-11,-37,-15,12,9,-19,-24,-31,-20,15,-8,11,-7,16,3,2,-8,-30,-6,26,-3,-1,-48,-26,-3,-26,0,20,-8,18,-5,-35,-1,2,26,4,-17,13,-3,-30,-11,4,9,-8,-8,-9,-2,16,15,29,9,-18,-7,-48,0,-7,-8,-2,-6,7,-2,3,15,13,10,19,-28,-26,-4,-50,12,-14,14,8,-6,10,9,-12,1,34,41,27,6,-42,10,11,-14,-23,-7,-6,8,27,1,4,4,21,7,-8,-2,-13,12,-3,-1,-29,-15,-2,16,17,-13,15,5,16,-2,18,36,27,25,0,23,29,-4,-40,-13,-32,-1,-36,-18,-15,-9,13,38,70,13,0,11,-2,13,-2,13,-6,3,-17,-13,-13,-22,-7,-1,-14,-1,-3,-10,5,-23,-18,7,5,-14,-2,-18,4,-2,-12,-29,-2,17,-9,7,6,-1,-1,-15,-8,-21,-18,-4,-9,14,-4,-14,-4,10,-7,-7,8,3,7,-7,-11,-9,-15,-5,7,11,-1,11,-5,-2,0,-4,-7,19,13,9,-1,10,-1,2,-2,8,-2,-2,12,20,13,5,-2,11,-1,-6,-8,15,-7,0,-2,0,3,16,5,10,35,12,-11,1,-1,-20,0,-1,-9,6,-6,9,-2,33,7,10,-1,-18,-4,0,-17,-20,-27,-2,-19,0,-7,4,5,12,-13,0,3,5,0,2,-4,-13,-4,-2,-12,18,3,6,3,-10,-38,4,25,17,6,7,14,9,-1,-5,-6,2,-17,-4,-16,-13,-36,11,-1,-8,11,17,6,4,-11,-13,-5,3,-11,-19,-17,-25,-37,18,-12,-6,-13,0,4,12,-1,3,5,1,-12,-4,-18,-4,3,25,3,-6,-5,11,25,17,-2,12,2,-13,-8,20,-6,8,11,23,1,-12,8,14,24,33,-8,-2,5,5,4,2,-17,12,23,16,22,10,15,4,-3,6,6,13,17,-6,-10,-16,4,10,40,12,43,23,-15,-16,-18,0,-10,0,-3,-8,1,-4,17,43,21,107,34,80,31,-15,46,3,-9,-12,-11,15,-24,-63,-11,-30,-26,17,12,-39,-4,-13,-37,10,-3,-43,-11,-15,10,-5,2,-17,-47,18,21,22,-32,43,21,16,-2,-4,3,-31,-4,0,-4,-18,-37,26,-8,26,-17,17,-18,3,-25,-30,-15,2,-18,-7,-38,-9,20,-9,-38,41,-55,46,36,40,1,-19,34,0,-6,20,-1,59,35,4,-34,-17,-47,-24,-44,61,29,17,23,20,36,13,19,28,28,47,-31,-60,-89,20,-38,-11,11,-21,-23,-15,14,-15,22,-9,-17,53,12,-14,-30,19,-22,35,35,-19,-46,8,4,-4,7,-36,-62,54,-11,23,-26,-31,-12,13,17,6,25,30,5,-2,2,6,-7,8,-55,6,-50,-27,-45,9,2,-26,6,11,-2,2,58,28,14,38,10,24,-30,-22,-18,-7,-34,28,-9,23,-21,25,17,89,-7,36,-13,-26,5,18,-29,3,-47,-13,-31,-12,14,11,-14,-8,64,64,19,-16,-8,36,15,-22,-58,2,5,32,6,-4,-21,33,11,81,28,0,5,-10,55,23,-33,-14,-15,-10,-51,20,-13,-23,5,39,1,-32,0,-42,10,22,-6,19,7,13,-21,-3,-27,9,-13,85,83,5,7,-37,-9,-13,-6,-46,6,-27,-32,-37,-17,-54,-28,9,9,9,7,-2,-10,-3,5,-4,-15,-7,-1,7,-6,2,-2,5,0,-5,-9,-9,-14,3,-12,-14,-7,0,-12,-2,2,1,1,11,-12,3,-15,-4,-10,-7,-18,-7,0,4,-11,3,1,2,2,12,-2,-9,-15,-6,-11,-11,-21,1,-12,-2,-5,-3,-10,-6,-8,6,-6,-3,0,-10,-2,2,-7,-2,-10,4,7,11,-2,-3,-4,10,-11,-1,-7,0,-2,1,-5,5,-2,9,2,10,-6,-6,-9,1,1,-6,6,-2,5,-4,8,2,5,1,-6,2,-2,-4,-7,0,-2,1,8,6,3,-3,-7,-12,3,-4,-10,4,-5,4,-2,5,10,9,12,17,10,13,0,7,2,6,1,4,4,12,5,15,15,23,16,6,9,6,0,9,7,2,-4,5,6,4,5,2,17,4,16,2,9,13,4,10,15,2,2,5,-8,3,-4,4,13,4,4,6,10,15,9,12,17,8,3,4,-9,11,0,19,7,-17,-3,10,21,4,2,10,12,15,6,-6,4,1,-3,6,-4,-11,-17,-2,-8,-6,-2,0,-6,9,-3,-2,-7,2,1,13,-9,-10,-21,-19,-16,-21,-14,-5,-6,-5,4,-2,-5,3,11,16,6,3,-17,-9,-27,-17,-20,-4,-18,-2,-6,3,11,22,-6,86,-5,19,37,31,-10,9,-39,-4,-54,3,-36,-16,4,51,-20,11,-38,49,24,20,28,17,-7,-29,-57,-31,-33,-28,-10,43,35,-2,8,30,-28,-13,2,15,-2,-47,16,34,42,-2,-44,15,-12,-17,-1,4,16,37,14,-3,-40,11,-10,14,-24,11,-60,-22,-42,-51,-7,-46,14,23,-19,2,29,-10,-26,-32,7,13,-16,-52,-1,45,-4,52,16,15,38,13,-33,4,-7,-10,-23,15,-16,28,2,10,19,-18,6,1,57,20,-26,9,25,21,-51,-44,-18,-12,50,-10,-15,12,57,-25,19,-12,-4,-2,13,17,34,17,4,12,-1,63,6,16,38,-51,-9,0,-60,-2,-3,-23,18,-16,-26,-46,36,6,1,-36,-38,-11,48,-61,-24,18,11,-7,-65,7,-18,21,-15,-41,-28,-26,-44,-4,45,-36,-29,10,-39,-14,-36,40,27,-8,27,21,-57,14,26,12,-32,-36,-8,21,-6,16,-12,-2,12,-50,-11,28,2,26,31,-16,30,-14,-3,35,12,3,10,-22,39,35,21,78,17,-4,-21,-14,-5,3,24,49,5,-1,-5,-12,0,27,0,47,40,-2,3,-12,-60,-5,20,0,37,-30,50,-12,3,18,-63,35,20,0,47,-15,-25,-31,-13,-7,11,-20,-19,10,-15,-14,-17,30,13,12,-9,-9,12,-10,-23,-10,-16,-23,-4,-6,-2,-5,21,7,-16,-23,-15,-7,-13,-8,-12,-19,9,-32,-13,-13,-26,22,-21,-3,0,-14,-6,14,-1,-4,-4,12,-4,-30,-19,-2,-46,-6,39,-2,-29,-9,-2,-1,-14,-22,-24,-2,14,-31,-42,-11,6,-35,35,36,-18,15,-2,9,13,11,10,38,-5,-22,-24,-14,8,-22,-4,32,0,-5,5,9,-22,6,-14,18,8,2,-35,-25,-24,-36,-32,43,29,2,-23,-16,-18,-3,-4,2,6,6,23,3,2,-13,-29,35,31,-12,-23,0,-16,19,19,-4,13,8,-5,2,12,24,-29,17,40,19,-9,-1,-25,-8,-7,-5,14,10,-1,2,5,11,-25,12,20,12,12,2,-19,3,-16,-19,4,21,16,10,-4,19,-23,14,49,53,4,11,25,18,-11,-4,-4,12,1,18,13,11,-10,2,3,16,3,-11,22,8,-8,0,-12,3,-9,18,-24,-2,-13,5,4,12,-6,-19,14,8,-10,-7,-22,-21,16,23,-22,34,29,-2,-19,25,38,31,22,25,-9,11,5,-10,-5,4,8,-11,-5,-15,-4,18,4,17,5,16,-12,18,-5,-11,-9,-28,0,45,30,32,5,13,-3,-16,-11,2,8,-26,-40,-27,-13,5,8,-1,-5,20,29,47,28,11,6,-8,-9,-12,-3,-2,-6,-7,-3,7,23,15,5,-1,-5,13,8,7,-14,6,2,4,-17,-16,1,9,23,14,14,15,-3,8,5,6,14,10,-2,-7,-13,-2,0,9,10,-9,17,-3,-11,3,-1,-2,12,6,0,2,-20,-5,8,21,5,23,8,8,-19,8,12,6,-3,10,5,4,-10,4,14,-5,-10,11,3,3,2,4,-4,-6,-17,-9,-12,8,-1,-4,21,10,-7,16,1,-8,-4,-23,1,-12,-9,-9,-8,-3,-22,-8,1,-28,-11,14,10,-15,-9,-21,-11,-4,7,2,0,16,-7,-5,-8,-6,22,7,-5,-13,-17,12,-15,-13,-10,-7,-2,-6,-4,7,-2,-5,-3,1,2,0,4,14,4,-7,-11,-8,-7,-1,-3,-8,-15,-3,-1,12,18,2,-4,16,14,-3,9,14,-11,2,-2,1,-9,3,-9,17,11,-3,7,5,37,25,5,-2,10,2,22,-7,-13,-15,1,11,-2,8,8,16,7,2,-5,-4,3,-2,11,0,-1,-3,-9,3,2,-6,-8,6,5,-7,7,-4,8,2,-8,-3,-17,-13,10,9,0,9,-7,7,-4,2,9,-2,-11,-2,-15,-3,-21,-7,-11,8,-7,8,-27,-25,6,4,-5,-16,-14,-1,-23,-2,-23,-21,-3,52,26,12,29,17,3,17,-23,-22,-9,7,-11,-9,-33,1,-4,29,10,-6,-2,-18,-20,-10,-5,-26,-9,0,-43,-14,-22,-28,-2,10,9,-1,-4,14,27,1,-17,-7,-36,-11,-36,10,-24,-7,5,33,-22,31,15,-4,-7,11,-36,10,-11,-9,-28,29,-6,4,-33,1,13,15,-6,13,24,-16,-1,-34,-8,-6,-2,2,-11,37,8,6,15,11,15,16,-19,4,-8,-32,-21,0,-5,6,18,44,28,-22,8,3,26,18,57,37,6,32,-2,-7,-38,2,23,3,-6,-15,-51,-16,-9,-9,25,43,-14,-22,8,-16,-25,-12,-34,-3,-63,-20,-8,-11,-36,17,10,-7,22,31,21,6,-1,1,1,12,-11,18,3,45,29,33,21,-1,24,21,18,23,3,3,3,1,-27,57,35,31,-16,13,5,-16,-16,18,21,3,19,9,4,13,-29,19,25,-7,-17,-24,13,-35,-12,1,-9,1,-12,-22,22,-17,13,52,29,24,-7,-10,8,10,-29,-16,-21,1,-11,-23,19,-7,9,32,15,-5,-28,-11,-10,7,6,1,3,2,-2,-13,12,-17,18,2,23,0,23,4,21,0,-5,15,-3,-18,-28,-8,9,20,18,54,-5,-23,-7,-14,-20,-8,1,-31,-17,-32,-36,-31,32,-3,-6,20,23,6,6,17,18,24,-7,-9,16,2,1,4,-45,-16,17,37,11,24,-20,-29,-2,-8,-2,-3,10,-2,-44,-24,-8,-15,-26,36,8,-6,-1,10,7,5,2,-31,7,8,5,-8,-18,-5,3,37,5,12,-2,-9,0,1,-49,-4,10,10,-7,12,-33,-20,8,18,-2,18,-13,23,-5,-18,5,9,6,11,-31,10,-1,10,8,37,8,25,1,4,11,5,-8,16,-4,17,2,-15,-18,8,24,28,20,19,18,5,8,11,-3,-33,-11,14,-5,-14,8,21,31,12,11,27,-23,27,-2,-2,-6,-7,0,-23,-14,16,0,4,31,-11,0,14,23,9,9,10,-6,0,4,-23,2,-6,-2,18,20,-27,-43,3,8,3,24,37,10,14,-4,0,-22,0,4,7,-2,4,-25,-36,-42,-13,16,23,3,14,18,5,-4,-2,11,11,18,-10,-26,3,-14,0,-39,20,1,-8,5,-10,-7,6,-11,-23,-10,27,0,11,-6,-8,-9,-13,11,9,14,-16,0,16,0,17,-24,26,6,13,-8,4,-11,-2,1,-19,15,0,-6,8,-5,-20,-18,9,16,-1,-5,-10,4,6,-27,-31,-21,-1,-15,9,-19,8,-3,19,-13,0,-2,-2,-28,3,-18,-23,-20,-22,-32,-24,-17,-11,-7,};

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
	bool pe=false;
	for (int j=0; j<n; j++){
		int cnt=0;
		for (int i=0; i<m; i++){
			if (matr[i][j]==0) cnt++;}
		if (!lf)
			if (cnt<m-1) { yleft[k]=j; lf=true; }
		if (lf) {
			if (cnt==m) {yright[k]=j; lf=false; k++;}
			if (cnt<m-6) pe=true;
		}
		
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
		case 1 : { if ((yright[0]-yleft[0])>2*(xbottom[0]-xtop[0])&&pe) {
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
				 else if ((yright[0]-yleft[0])>(xbottom[0]-xtop[0])-1&&pe) {
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
		case 2 : {if ((yright[0]-yleft[0])>(xbottom[0]-xtop[0])-3&&pe) {
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
				 else if ((yright[1]-yleft[1])>(xbottom[1]-xtop[1])-3&&pe) {
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

