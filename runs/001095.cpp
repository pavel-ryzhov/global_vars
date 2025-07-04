#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

struct point{
int x;
int y;
};

class claster{
private:
    point* maspoint;
    int lab;
    int n;
    int left;
    int right;
    int top;
    int bot;
    int** tabl;
public:
    claster();
    claster(int l);
    ~claster();
    void addpoint(int a,int b);
    int getlab();
    int getn();
    int getl();
    void merge(claster* c, int** t);
    void totabl();
    void raspozn();
};
claster::claster(){maspoint=0;lab=0;n=0;left=-1;right=-1;top=-1;bot=-1;}
claster::claster(int l){maspoint=new point[2500];n=0;lab=l;left=-1;right=-1;top=-1;bot=-1;}
claster::~claster(){delete[] maspoint;};
void claster::addpoint(int b,int a){
		maspoint[n].x=a;
		maspoint[n].y=b;
		n++;
		if (a<left||left==-1)left=a;
		if (a>right||right==-1)right=a;
		if (b>top||top==-1)top=b;
		if (b<bot||bot==-1)bot=b;
		}
int claster::getlab(){return lab;};
int claster::getn(){if (lab>0&&((top-bot)!=(right-left))){return n;}else {return 0;}}
int claster::getl(){return left;}
void claster::merge(claster* c,int** t){
		if (c->lab>0&&n>1&&c->lab>2){
		if (left>c->left)left=c->left;
		if (right<c->right)right=c->right;
		if (bot>c->bot)bot=c->bot;
		if (top<c->top)top=c->top;
		for (int i=n;i<n+c->n;i++){
			maspoint[i].x=c->maspoint[i-n].x;
			maspoint[i].y=c->maspoint[i-n].y;
			t[maspoint[i].y][maspoint[i].x]=lab;
		}
		n=n+c->n;
		c->lab=0;}
}


void claster::totabl(){
    if (n>20){
		tabl=new int* [top-bot+1];
		for (int i=0;i<top-bot+1;i++){
			tabl[i]=new int[3];
			tabl[i][0]=0;
			tabl[i][1]=-1;
			tabl[i][2]=-1;
		}
		for (int i=0;i<n;i++){
			int h=top-maspoint[i].y;
			tabl[h][0]=tabl[h][0]+1;
			if (tabl[h][1]==-1||tabl[h][1]>maspoint[i].x)tabl[h][1]=maspoint[i].x;
			if (tabl[h][2]==-1||tabl[h][2]<maspoint[i].x)tabl[h][2]=maspoint[i].x;

		}
    }
}

void claster::raspozn(){
    if (n>20){
	bool ansv[10];
	for (int i=0;i<10;i++)ansv[i]=false;
	bool b1=false,b2=false,b3=false,b4=false;
	int s=(right-left)/6;
	int t1=0;int t2=0;
	int t3=0;int t4=0;
	int h=(top-bot)/6;

	for (int i=0;i<top-bot;i++){
	if (tabl[i][2]-tabl[i][1]+1>tabl[i][0])t1++;
	}
	if (t1==0&&(tabl[0][0]>=tabl[top-bot-1][0])&&tabl[5*h][2]-tabl[h][2]<2){cout<<"1";return;}

		t1=0;
		
	b4=true;
	for (int i=h-1;i<4*h;i++){		
	if (tabl[i+1][2]-tabl[i][2]>0&&tabl[i][1]-tabl[i+1][1]>s){b2=true;t1=i;}	
	}
	for (int i=0;i<t1;i++){
	if (tabl[i][2]-tabl[i][1]+1>tabl[i][0])b4=false;	
	}



	 for (int i=4*h;i<top-bot;i++){
		if ((tabl[i+1][2]-tabl[i][2])>s/2)b3=true;
	 }

	
	 if (b2&&b4){cout<<"4";return;}
	b2=false;
	for (int i=0;i<(top-bot+1)/3;i++){
		 if (tabl[i][2]-tabl[i+1][2]>2*s)ansv[2]=true;
		if  (tabl[i][2]-tabl[i][1]>tabl[i][0])b2=true;
	}
t3=0;	
for (int i=2;i<(top-bot+1)/2;i++){
		if (abs(tabl[i+1][1]-tabl[i][1])>s){ansv[9]=true;t3=i;}

	}
	b1=false;
t4=0;
	for (int i=(top-bot)/2;i<top-bot;i++){
		if (tabl[i][1]-tabl[i+1][1]>s){ansv[7]=true;t4=i;}
		if (tabl[i][0]>2*tabl[0][0]) b1=true;
	}
		for (int i=(top-bot)/2;i<3*(top-bot)/4;i++){

		if ((abs(tabl[i+1][2]-tabl[i][2])>s&&s>1)||(abs(tabl[i+1][2]-tabl[i][2]))>2&&s==1)ansv[6]=true;
				}

for (int i=h*4;i<top-bot;i++){

if ((tabl[i+1][2]-tabl[i][2]>s&&s>1)||(tabl[i+1][2]-tabl[i][2]>2))ansv[5]=true;
}



	for (int i=3*(top-bot)/4;i<(top-bot);i++){

		if (tabl[i+1][2]-tabl[i][2]>s&&s>1)ansv[6]=true;
	}


	
	if (ansv[2]){
	if (!b2&&tabl[5*h][2]-tabl[h][2]<2){cout<<"1";return;}
	else{cout<<"2";return;}
	}

	if (t4==t3+1&&!ansv[5]){cout<<"8";return;}
	if (ansv[9]&&ansv[5]){cout<<"5";return;}
	if (ansv[9]&&ansv[7]){cout<<"3";return;}

	if (ansv[7]){
	if (b1&&(tabl[19*(top-bot)/20][2]-tabl[0][2])>2&&t4-t3>2){cout<<"7";return;}
		else{cout<<"1";return;}
	}

	if (ansv[6]){cout<<"6";return;}
	if (ansv[9]){cout<<"9";return;}


	 t1=-1; t2=0;
	  t3=-1; t4=0;
	for (int i=0;i<top-bot-1;i++){
		if (t1*tabl[i][1]>t1*tabl[i+1][1]){t2++;t1=t1*(-1);}
		if (t3*tabl[i][2]<t3*tabl[i+1][2]){t4++;t3=t3*(-1);}
	}

	if (t4+t2>3){cout<<"8";return;}

	cout<<"0";
	return;
    }

}


 int ring(int** mas, int a,int b,int c){
	if (mas[b-1][a-1]>1){
		mas[b][a]=mas[b-1][a-1];
		return c;
	}
	if (mas[b-1][a]>1){
		mas[b][a]=mas[b-1][a];
		return c;
	}
	if (mas[b-1][a+1]>1){
		mas[b][a]=mas[b-1][a+1];
		return c;
	}
	if (mas[b][a-1]>1){
		mas[b][a]=mas[b][a-1];
		return c;
	}
	mas[b][a]=c;
	return c+1;
 }

int main()
{
  int** map;
  string st;
  cin>>st;
  int len=st.length() ;
  map=new int*[len];
  for (int i=0;i<len;i++){map[i]=new int[len];}
  int j=0;
  int k1=0;
  int k2=0;
  int k3=0;
  int k4=0;

  bool f=true;
  while (f){
  int kk=0;

  for (int i=0;i<len;i++){
	switch (st[i]) {
	 case '.':map[j][i]=1;k1++;kk++;break;
	 case '%':map[j][i]=2;k2++;break;
	 case '#':map[j][i]=4;k3++;break;
	 case '@':map[j][i]=4;k4++;break;
	 default:break;
	 }
  }
  j++;
  if ((k4>0)&&(kk==len)){
  f=false;
  }else{cin>>st;}
  }

  	for (int q=1;q<j;q++){
		for (int qq=1;qq<len;qq++){
		if (map[q][qq]!=4&&
			map[q][qq]!=map[q-1][qq-1]&&
			map[q][qq]!=map[q-1][qq]&&
			map[q][qq]!=map[q-1][qq+1]&&
			map[q][qq]!=map[q][qq+1]&&
			map[q][qq]!=map[q+1][qq+1]&&
			map[q][qq]!=map[q+1][qq]&&
			map[q][qq]!=map[q+1][qq-1]&&
			map[q][qq]!=map[q][qq-1]){
		map[q][qq]=1;}
		if (k2>k3&&map[q][qq]==2){map[q][qq]=1;}
		}
	}

  int label=5;
  int labelmax=0;
  for (int q=1;q<j-1;q++){
  for (int qq=1;qq<len-1;qq++){
  if (map[q][qq]>1){  label=ring(map,qq,q,label);}
  }
  }
  labelmax=label;
  label=5;
  claster** mc=new claster*[labelmax-5];
  for (int q=0;q<labelmax-5;q++)
  mc[q]=new claster(q+5);

  for (int q=1;q<j-1;q++){
	for (int qq=1;qq<len-1;qq++){
		if (map[q][qq]>1) mc[(map[q][qq]-5)]->addpoint(q,qq);
	}
  }

  for (int q=1;q<j-1;q++){
	for (int qq=1;qq<len-2;qq++){
		if (map[q][qq]>1&&map[q][qq-1]>1&&map[q][qq]!=map[q][qq-1]){
			 mc[map[q][qq]-5]->merge(mc[map[q][qq-1]-5],map);
		}
	}
  }
 claster* c1=0;
 claster* c2=0;
 claster* c3=0;
 claster* c4=0;
 int t1=0;
 int t2=0;
 int t3=0;

 for (int qqq=0;qqq<labelmax-5;qqq++){

	if (mc[qqq]->getn()>t1){
		t1=mc[qqq]->getn();c3=c2;c2=c1;c1=mc[qqq];
	}else{
		if (mc[qqq]->getn()>t2){
			t2=mc[qqq]->getn();c3=c2;c2=mc[qqq];
		}else{
			if (mc[qqq]->getn()>t3){t3=mc[qqq]->getn();c3=mc[qqq];}
		}
	}
 }
 /*cout<<endl<<endl<<"ffffffffffffffffff"<<endl;
 cout<<c1->getn();
 cout<<endl<<c2->getn();
 cout<<endl<<c3->getn()<<endl;*/


if (c2==0){
	c1->totabl();
 	c1->raspozn();
}
if (c3==0){
	if (c1->getl()>c2->getl()){
		c4=c1;c1=c2;c2=c4;
	}
c1->totabl();
 c1->raspozn();
 c2->totabl();
 c2->raspozn();

}

if (c3!=0){ 
if (c1->getl()>c2->getl()){
	if (c2->getl()>c3->getl()){
		c4=c1;c1=c3;c3=c4;
	}else{
		if (c1->getl()>c3->getl()){
			c4=c1;c1=c2;c2=c3;c3=c4;
		}else{c4=c1;c1=c2;c2=c4;}
	}
 }else{
	if (c2->getl()>c3->getl()){
		if (c1->getl()>c3->getl()){
			c4=c1;c1=c3;c3=c2;c2=c4;
		}else{c4=c2;c2=c3;c3=c4;}
	}
 }
c1->totabl();
 c1->raspozn();
 c2->totabl();
 c2->raspozn();
 c3->totabl();
 c3->raspozn();
}

 
  // system("pause");
	return 0;
}
  