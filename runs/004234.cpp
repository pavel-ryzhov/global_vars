#include <iostream>
#include <fstream>
#include<vector>
#include<string>
#include<set>
#include <sstream>

using namespace std;
vector<string> s;
string res;
const int params_size=19;

//POSTERIZE, TRIM===================================================

void trim (vector<string> &s) {

	if (s.empty()) return;
	int w=s[0].size(), h=s.size();
	//is s white?-----
	bool flag=true;
	for (int i=0; i<h; i++) 
		for (int j=0; j<w; j++) 
			if (s[i][j]!='.') {
				flag=false;
				break;
			}
			if (flag) {
				s.clear();
				return;
			}
			//-----
			
			flag=true;

			int l=0, r=s[0].size(), u=0, d=s.size();

			for (int i=h-1; i>=0; i--) { 
				for (int j=0; j<w; j++)
					if (s[i][j]!='.') {
						flag=false;
						d=i;
						break;
					}
					if (!flag) break;
			}

			flag=true;
			for (int i=0; i<h; i++) {
				for (int j=0; j<w; j++) {
					if (s[i][j]!='.') {
						flag=false;
						u=i;
						break;
					}
				}
				if (!flag) break;
			}

			flag=true;
			for (int j=0; j<w; j++) {
				for (int i=0; i<h; i++) {
					if (s[i][j]!='.') {
						flag=false; 
						l=j; 
						break;
					}
				}
				if (!flag) break;
			}

			flag=true;
			for (int j=w-1; j>=0; j--) {
				for (int i=0; i<h; i++) {
					if (s[i][j]!='.') {
						flag=false; 
						r=j; 
						break;
					}
				}
				if (!flag) break;
			}
			s.erase(s.begin()+d+1, s.end());
			s.erase(s.begin(),s.begin()+u);
			for (int i=0; i<s.size(); i++) {
				s[i].erase(s[i].begin()+r+1, s[i].end());
				s[i].erase(s[i].begin(), s[i].begin()+l);
			}
}

void posterize() {
	int w=s[0].size(), h=s.size();
	for (int i=0; i<h; i++) 
		for (int j=0; j<w; j++)
			if (s[i][j]=='#') s[i][j]='@';

	for (int i=1; i<h-1; i++) 
		for (int j=1; j<w-1; j++) 
			if (s[i][j]=='%') 
				if (   ((s[i-1][j]=='.')&&(s[i+1][j]=='.'))   ||  ((s[i][j-1]=='.')&&(s[i][j+1]=='.'))  ) 
					s[i][j]='@';
				else s[i][j]='.';	

				for (int i=0; i<h; i++) { 
					if (s[i][0]=='%')
						if (s[i][1]=='.') s[i][0]='@';
						else s[i][0]='.';
						if (s[i][w-1]=='%')
							if (s[i][w-2]=='.') s[i][w-1]='@';
							else s[i][w-1]='.';
				}

				for (int j=1; j<w-1; j++) {
					if (s[0][j]=='%')
						if (s[1][j]=='.') s[0][j]='@';
						else s[0][j]='.';
						if (s[h-1][j]=='%')
							if (s[h-2][j]=='.') s[h-1][j]='@';
							else s[h-1][j]='.';
				}
				trim(s);
}

//CONNECTED REGIONS functions=================================

vector< vector<int> > array_of_labels;
vector<int>labels_id; //sperva dlya i-oi metki labels[i] = i. Kogda nahodim, chto metka i  ekvivalentna metke j, stavim label[i]=j (ili label[j]=i).
set<int>actual_labels;//zapolnyaetsya posle zameni ekvivalentnih metok

void init_labels() { 
	int h=s.size(), w=s[0].size(); 
	array_of_labels.clear();
	array_of_labels.resize(h); 
	for(int i=0; i<h; i++)
		array_of_labels[i].resize(w,0); 
	labels_id.clear(); 
	labels_id.resize(1,0);
	actual_labels.clear();
}

int up(int i,int j) {
	if (i==0) return 0;
	return array_of_labels[i-1][j]; 
}

int left(int i,int j) {
	if (j==0) return 0;
	return array_of_labels[i][j-1];
}

int left_up (int i, int j) {
	if ((i==0)||(j==0)) return 0;
	return array_of_labels[i-1][j-1];
}

int left_down (int i, int j) {
	if ((i==(array_of_labels.size()-1))||(j==0)) return 0;
	return array_of_labels[i+1][j-1];
}

int new_label() {
	int t=labels_id.size();
	labels_id.push_back(t); //labels_id[t]=t; 
	return t;
}

int get_label(int label) {
	if (label==labels_id[label]) return label;
	return (get_label(labels_id[label]));
}

void add_equiv (int m1, int m2) {
	int a, b;
	a=get_label(m1);
	b=get_label(m2);
	if(a<b)
		labels_id[b]=a;
	else labels_id[a]=b;
}

void add_equiv_if_need (int label, int main_label) {
	if (!label) return;
	if (label!=main_label) add_equiv (label, main_label);
}

void set_label(int i, int j, bool eight_points=false) { 
	int t;
	if (!eight_points) {
		t=up(i,j);
		if(t) {
			add_equiv_if_need(left(i,j),t);
			array_of_labels[i][j]=t;
			return;
		}

		t=left (i,j);
		if (t) { 
			array_of_labels[i][j]=t;
			return;
		}
	}

	else {
		t=left_up(i,j);
		if (t) {
			add_equiv_if_need(left(i,j),t);
			add_equiv_if_need(left_down(i,j),t);
			add_equiv_if_need(up(i,j),t);
			array_of_labels[i][j]=t; 
			return;
		}
		t=left(i,j);
		if (t) {
			add_equiv_if_need(left_down(i,j),t);
			add_equiv_if_need(up(i,j),t);
			array_of_labels[i][j]=t; 
			return;
		}
		t=left_down(i,j);
		if (t) {
			add_equiv_if_need(up(i,j),t);
			array_of_labels[i][j]=t; 
			return;
		}
		t=up(i,j);
		if (t) {
			array_of_labels[i][j]=t; 
			return;
		}
	}
	array_of_labels[i][j]=new_label();
}

void resolve_equiv() { //prohodit po razmechennomu massivu i pomechaet elementi s ekvivalentnimi metkami odnoi metkoi; mnojestvo ostavshihsya metok zapisivaet v aktual_labels
	for (int i=0; i<array_of_labels.size(); i++)
		for (int j=0; j<array_of_labels[i].size(); j++) {
			if (array_of_labels[i][j]) {
				int t=get_label(array_of_labels[i][j]);
				array_of_labels[i][j]=t;
				actual_labels.insert(t);
			}

		}
}

//DIVIDE LETTERS=================================
vector<string> s1, s2, s3;
bool filled1=false, filled2=false, filled3=false; 
bool trash=false;

extern ifstream ans;

extern vector< vector<int> > array_of_labels;
extern set<int>actual_labels;

void copy_labeled_items(vector<string> &sn, int label) {
	for(int i=0; i<s.size(); i++) {
		for (int j=0; j<s[0].size(); j++){
			if(array_of_labels[i][j]==label) {
				sn[i][j]=s[i][j];
				s[i][j]='.';
			}
		}
	}

	if (&sn==&s1) filled1=true; 
	if (&sn==&s2) filled2=true; 
	if (&sn==&s3) filled3=true; 
}

void init_s123() {
	s2.clear();
	s2.resize(s.size());
	for(int i=0; i<s.size();i++) {
		s2[i].resize(s[0].size(),'.');
	}
	if(!filled1) s1=s2;
	if(!filled3) s3=s2;
}

inline int mass(vector<string> &a) {
	int h=a.size(), w=a[0].size(), m=0;
	for(int i=0; i<h; i++)
		for (int j=0; j<w; j++)
			if (a[i][j]!='.') m++;
	return m;
}


vector<int> find_dividing_curve (const vector<string> &left, const vector<string> &right){
	/*для каждой строки: находим последний пиксель из left. Если не находим - движемся вправо, пока right[i][j]=='.'. Движемся влево, пока  s[i][j]!='.'.

	Если находим, движемся вправо, пока 
	1) s[i][j] !='.' (там м.б. % или маленькие связные области) и 
	2) right[i][j] == '.'.
	Граница - пиксель, на котором остановимся.
	*/	
	int w=s[0].size(), h=s.size();
	vector<int> res(h);
	for (int i=0; i<h; i++) {
		int j=w-1;
		while (left[i][j]=='.') {
			j--;
			if (j==-1) break;
		}

		if (j==-1) { //если в какой-то строке нет ничего из каркаса левой части
			j++;
			while(right[i][j]=='.') {
				j++;
				if (j==w) {  //если из каркаса правой части тоже ничего нет
					if (i==0) res[i]=w/2;
					else res[i]=res[i-1];
					break;
				}
			}
			if (res[i]) continue;

			int t=j;  //t - крайний левый пиксель каркаса правой части (пригодится, если все, что левее, непусто)
			while(s[i][j]!='.') {
				j--;
				if (j==-1) {
					res[i]=t;
					break;
				}
			}
			if (res[i]) continue;
			res[i] = j+1;
			continue;
		}

		//j - крайний правый пиксель каркаса левой части 
		while ((s[i][j]!='.')&&(right[i][j]=='.')) {
			j++;
			if (j==w) break;
		}		
		res[i]=j;
	}
	return res;
}

void return_light_gray (vector<string> &left, vector<string> &right) {//  в left и right записаны каркасы (без '%'), в s - все вместе
	int h=s.size();
	vector<int> dividing_curve=find_dividing_curve(left,right);

	for (int i=0; i<h; i++) 
		for (int j=0; j<dividing_curve[i]; j++)
			left[i][j]=s[i][j], s[i][j]='.';
	right=s;
	s.clear();	
}

vector<string> merge(const vector<string> a, const vector<string> b) {
	int w=s[0].size(), h=s.size();
	vector<string> res=a;
	for (int i=0; i<h; i++) 
		for (int j=0; j<w; j++) 
			if (b[i][j]!='.') res[i][j]=b[i][j];
	return res;
}

void divide_by_connected_regions(bool second_time=false) { 
	const double trash_coef=11.0/31;
	init_labels();
	init_s123();
	//find connected regions----------------------------------
	for (int j=0; j<s[0].size(); j++) {
		for(int i=0; i<s.size(); i++) {
			if (s[i][j]!='.')
				if (!(second_time&&(s[i][j]=='%')))
					set_label(i,j,true);
		}
	}

	resolve_equiv();
	//--------------------------------------------------------

	if (actual_labels.size()==1) return;

	vector< vector<string> > crs; //cr - connected regions
	vector<string> s_copy=s;


	vector<string> cr=s2; //s2 is an empty one
	for (set<int>::iterator iter=actual_labels.begin(); iter!=actual_labels.end(); iter++) {
		copy_labeled_items(cr, *iter);
		crs.push_back(cr);
		cr=s2;
	}
	//now each connected region is an item of vector crs;

	int hmin=s.size(), hmax=0, h;

	//delete trash
	vector< vector<string> > crs_copy=crs; //у crs_copy не будем делать trim

	for (int i=0; i<crs.size(); i++) {
		trim(crs[i]);
		h=crs[i].size();
		if (h>=hmax) hmax=h;
		if (h<=hmin) hmin=h;
	}

	if (hmin<=(trash_coef*hmax)) trash=true;

	if (trash) {
		for (int i=0; i<crs.size(); i++) {
			if (crs[i].size()<=(trash_coef*hmax)) {
				crs.erase(crs.begin()+i);
				crs_copy.erase(crs_copy.begin()+i);
				i--;
			}
		}
	}

	//delete borders
	bool border=false;

	if ((!second_time) && (crs.size()%2==0) ) {
		border=true;
		int delta=(int)((double)hmax/15), t;		
		for (int i=0; i<crs.size(); i+=2) {
			t=crs[i].size()-crs[i][0].size();
			if (t<0) t=-t;
			if (t>delta) {
				border=false;
				break;
			}
		}

		if (border) {
			const double border_h_to_nonborder_h=1.2;
			int hmax2=crs[1].size();
			for (int i=1; i<crs.size(); i+=2) 
				if (crs[i].size()<hmax2) hmax2=crs[i].size();
			if (border_h_to_nonborder_h*hmax2>=hmax) border=false;

			if (border) {
				for (int i=crs.size()-2; i>=0; i-=2)
					crs_copy.erase(crs_copy.begin()+i);		
			}
		}
	}

	crs=crs_copy;

	if (second_time) s=s_copy; //понадобится для return_light_gray

	if (crs.size()==3) {
		if ((!filled1)&&(!filled2)&&(!filled3)) {
			s1=crs[0], s2=crs[1], s3=crs[2];
			filled1=true, filled2=true, filled3=true;
			if (second_time) {
				vector<string> merged=merge(s2,s3);
				return_light_gray(s1,merged);
				s=merged;
				return_light_gray(s2,s3);
			}
			return;
		}
		s=s_copy;
		return;
	}

	if (crs.size()==1) {
		if (border) {
			s2=crs[0];
			filled2=true;
		}
		else
			if (second_time) s=s_copy;
			else s=crs[0]; //в s_copy остались маленькие связные области,в crs[0] - нет.
			return;
	}

	if (crs.size()==2) {
		if (border) {
			s1=crs[0], s2=crs[1];
			filled1=true, filled2=true;
			return;
		}

		if (filled1) {
			s2=crs[0], s3=crs[1];
			filled2=true, filled3=true;

			if (second_time) 
				return_light_gray(s2,s3);

			return;
		}

		if (filled3) {
			s1=crs[0], s2=crs[1];
			filled1=true, filled2=true;

			if (second_time) return_light_gray(s1,s2);
			return;
		}		

		//if !(filled1||filled2||filled3)
		if (mass(crs[0])>mass(crs[1])){
			filled3=true;			
			if (second_time) return_light_gray(crs[0],crs[1]);
			s=crs[0], s3=crs[1];
			return;
		}
		else {
			filled1=true;
			if (second_time) return_light_gray(crs[0],crs[1]);
			s1=crs[0], s=crs[1];
			return;
		}	
	}

	//if (crs.size()>3)
	s=s_copy;
}

void find_min_weight(int &min, int&minnum, const vector<int>&weight, int min_number_wide) {
	min=999, minnum=0;


	int i=min_number_wide-1;
	while (i<(weight.size()-min_number_wide)) {
		if (weight[i]<min) 
			min=weight[i], minnum=i;
		i++;
	}
}

vector<int> find_lines_with_min_weight(vector<int> &weight, int max_weight) {
	int min, minnum;	
	vector<int> res;
	int min_number_wide=s[0].size()/5;  //считаем, что цифра занимает по крайней мере 1/5 от ширины трех цифр
	if (min_number_wide<4) min_number_wide=5;

	find_min_weight(min,minnum, weight, min_number_wide);
	if (min>max_weight) return res;
	res.push_back(minnum+1);

	if (filled1||filled3) return res;

	int t=weight.size()/3;
	if (minnum<t)  
		for (int i=0; i<=minnum; i++)
			weight[i]=max_weight+1;
	else if (minnum>=(2*t))
		for (int i=minnum+1; i<weight.size(); i++) weight[i]=max_weight+1;

	int min2, minnum2;
	while (true) {
		find_min_weight(min2,minnum2, weight, min_number_wide);
		if (min2>max_weight) return res;
		t=minnum2-minnum;
		if(t<0) t=-t;
		if (t>min_number_wide) break;
		weight[minnum2]=max_weight+1;
	}
	res.push_back(minnum2+1);

	return res;
}

void fill(vector<string>&sn, int a, int b) {
	for (int i=0; i<s.size(); i++)
		for (int j=a; j<b; j++) {
			sn[i][j]=s[i][j];
			s[i][j]='.';
		}

}

void fill_sn(vector<int> &minlines) {
	if (minlines.size()==0) {
		s2=s;
		filled2=true;
		return;
	}
	if (minlines.size()==1) {
		if (filled1) {
			fill(s2,0,minlines[0]);
			s3=s;
			filled2=true, filled3=true;
			return;
		}
		if ( (filled3) || (minlines[0]<(s[0].size()/2))) {
			fill(s1,0,minlines[0]);
			s2=s;
			filled1=true, filled2=true;
			return;
		}

		fill(s2,0,minlines[0]);
		s3=s;
		filled2=true, filled3=true;
	}
	if (minlines.size()==2) {
		fill(s1,0,minlines[0]);
		fill(s2,minlines[0],minlines[1]);
		s3=s;
		s.clear();
		filled1=true; filled2=true, filled3=true;
	}
}

void divide_by_special_line() {
	const int max_weight=20;

	init_s123();
	int w=s[0].size(), h=s.size(), count;
	vector<int> weight(w-1, 0);

	for (int j=1; j<w; j++) {
		count=0;
		for (int i=0; i<h; i++) {
			if (count>max_weight) break;
			char a=s[i][j-1], b=s[i][j];
			if ((a=='@')&&(b=='@')) {
				weight[j-1]=99;
				break;
			}
			if ((a=='.')||(b=='.')) 
				continue;
			if ((a=='%')&&(b=='%')) {
				count++;
				continue;
			}
			if ((a=='#')&&(b=='#')) {
				count+=3;
				continue;
			}
			if ((a=='%')||(b=='%')) {
				count+=2;
				continue;
			}
			count+=4;
		}
		weight[j-1]+=count;
	}

	vector<int> minlines=find_lines_with_min_weight(weight, max_weight);

	fill_sn(minlines);
}

void divide() {
	trim(s);
	divide_by_connected_regions();
	trim(s);

	if (!s.empty()) {
		divide_by_connected_regions(true);
		trim(s);
	}

	if (!s.empty()) {
		divide_by_special_line();
		trim(s);
	}
}

//DEFINE PARAMETERS: WHITE REGIONS (find white regions and modify letter a bit)=================================

extern vector< vector<int> > array_of_labels;
extern vector<int>labels_id; //sperva dlya i-oi metki labels[i] = i. Kogda nahodim, chto metka i  ekvivalentna metke j, stavim label[i]=j (ili label[j]=i).
extern set<int>actual_labels;

bool remove_short_horizontal_lines () {
	const double hole_min_w=3.0/30;
	const double narrow=1.57;
	int w=array_of_labels[0].size(),h=array_of_labels.size();
	if (w<=10) return false;

	int max_w=(int)(hole_min_w*h);
	if (((double)h/(double)w)>=narrow) 
		max_w=1;

	bool res=false;

	int j, j1, j2;

	for (int i=0; i<h; i++) {
		j=0;
		while (j<w-1) {
			while ((array_of_labels[i][j])&&(j<w-1))
				j++;
			if (array_of_labels[i][j]) break;
			while ((!array_of_labels[i][j])&&(j<w-1)) 
				j++;
			if (!array_of_labels[i][j]) break;
			j1=j;
			while ((array_of_labels[i][j])&&(j<w-1))
				j++;
			if (array_of_labels[i][j]) break;
			j2=j;
			if ((j2-j1)<=(max_w)) {
				res=true;
				for (j=j1; j<j2; j++) {
					s[i][j]='@';
					array_of_labels[i][j]=0;
				}
			}
		}

	}
	return res;
}

bool remove_short_vertical_lines () {
	const double hole_min_h=0.9/14;
	int w=array_of_labels[0].size(),h=array_of_labels.size();
	if (w<=10) return false;

	int min_h=(int)(hole_min_h*(double)h);
	bool res=false;

	if (((double)h/w)>=32.0/16) {
		if (w<=16) return false;
		else min_h=1; 
	}

	int i, i1, i2;

	for (int j=0; j<w; j++) {
		i=0;
		while (i<h-1) {
			while ((array_of_labels[i][j])&&(i<h-1))
				i++;
			if (array_of_labels[i][j]) break;
			while ((!array_of_labels[i][j])&&(i<h-1)) 
				i++;
			if (!array_of_labels[i][j]) break;
			i1=i;
			while ((array_of_labels[i][j])&&(i<h-1))
				i++;
			if (array_of_labels[i][j]) break;
			i2=i;

			if ((i2-i1)<=min_h) {
				res=true;
				for (i=i1; i<i2; i++) {
					s[i][j]='@';
					array_of_labels[i][j]=0;
				}
			}
		}

	}
	return res;
}

inline bool white_pix (int i, int j) {
	if ((i<=-1)||(i>=s.size())||(j<=-1)||(j>=s[0].size())) return false;
	if ((s[i][j]=='.')||(s[i][j]=='%')) return true;
	return false;
}

inline bool black_pix (int i, int j) {
	if ((i<=-1)||(i>=s.size())||(j<=-1)||(j>=s[0].size())) return false;
	if ((s[i][j]=='#')||(s[i][j]=='@')) return true;
	return false;
}

bool remove_short_diag_lines () {
	const double rec_min_w=7.0/46;
	const double rec_min_h=2.0/11;
	const double narrow=1.57;
	int w=s[0].size(), h=s.size();
	if (((double)h/w)>=narrow) return false;
	bool flag, res=false;

	for (int min_w=3; (min_w<=rec_min_w*h)||(min_w<=3); min_w++) {
		for (int min_h=2; min_h<=rec_min_h*h; min_h++) 
			if (min_h==2) 	{
				for (int i=0; i<h; i++)				
					for (int j=0; j<w; j++) 
					{
						if (black_pix(i,j)&&black_pix(i+min_h-1, j+min_w-1)) {
							flag=true;

							for (int m=0; m<min_h; m++)
								for (int n=0; n<min_w; n++) {
									if ( ((m==0)&&(n==0)) || ((m==min_h-1)&&(n==min_w-1))  ) continue;
									if (!white_pix(i+m,j+n)) {
										flag=false;
										break;
									}
								}


								if (flag) {
									for (int n=1; n<min_w; n++)
										s[i] [j+n] ='@';
									for (int m=0; m<min_h-1; m++)
										s[i+m][j+min_w-1]='@';
									res=true;
								}
						}


						//то же для
						//....@
						//@....

						if (black_pix(i+min_h-1,j)&&black_pix(i, j+min_w-1)) {
							flag=true;

							for (int m=0; m<min_h; m++)
								for (int n=0; n<min_w; n++) {
									if ( ((m==0)&&(n==min_w-1)) || ((m==min_h-1)&&(n==0))  ) continue;
									if (!white_pix(i+m,j+n)) {
										flag=false;
										break;
									}
								}


								if (flag) {
									for (int n=0; n<min_w-1; n++) {
										s[i] [j+n] ='@';
										array_of_labels[i][j+n]=0;
									}
									for (int m=0; m<min_h-1; m++) {
										s[i+m][j]='@';
										array_of_labels[i+m][j]=0;
									}
									res=true;
								}
						}

					}
			}
	}
	return res;
}

bool whites_around (int i, int j) {
	int w=s[0].size(), h=s.size();
	if (white_pix(i-1,j)||
		white_pix(i+1,j)||
		white_pix(i,j-1)||
		white_pix(i,j+1))
		return true;

	if (!(  ((i==0)||(i==h-1))  &&  ((j==0)||(j==w-1))  ))
		s[i][j]='@';
	return false;
}

void fill_array_of_labels() { 
	int w=s[0].size(), h=s.size();
	init_labels();

	for (int j=0; j<w; j++) 
		for(int i=0; i<h; i++) {
			if ((s[i][j]=='.')||(s[i][j]=='%'))
				if (whites_around(i,j)) //не добавляем метку белой области, если она размером 1 px
					set_label(i,j);
		}
		resolve_equiv();

}

void remove_border_labels() {
	int w=s[0].size(), h=s.size();
	for (int i=0; i<h; i++) {
		actual_labels.erase(array_of_labels[i][0]);
		actual_labels.erase(array_of_labels[i][w-1]);
	}

	for (int j=0; j<w; j++) {
		actual_labels.erase(array_of_labels[0][j]);
		actual_labels.erase(array_of_labels[h-1][j]);
	}
}

int two_whites_on_hor_line() {
	if (actual_labels.size()!=2) return 99;

	int t1, t2;
	for (int i=0; i<s.size(); i++)
		for (int j=0; j<s[0].size(); j++) {
			t1=array_of_labels[i][j];
			if (actual_labels.find(t1)!=actual_labels.end()) {
				for (int k=j+1; k<s[0].size(); k++){
					t2=array_of_labels[i][k];
					if (t2!=t1)
						if (actual_labels.find(t2)!=actual_labels.end())
							return 102;
				}
			}
		}
		return 100;
}

int one_white_high_func() {
	const double one_white_high_const=0.6;
	const double one_white_medium_const=19.0/62;

	if (actual_labels.size()!=1) return 99;

	int count=0;
	int w=s[0].size(), h=s.size();

	for (int i=0; i<h; i++)
		for (int j=0; j<w; j++) 
			if(array_of_labels[i][j]==*actual_labels.begin()) {
				count++;
				break;
			}
			if (count>=(one_white_high_const*h)) return 102;
			if (count>=(one_white_medium_const*h)) return 101;
			return 100;
}

int one_white_top_func() {
	const double almost_equal=2.0/15;

	if (actual_labels.size()!=1) return 99;
	int w=s[0].size(), h=s.size();
	int i=0, i1, i2;
	bool flag=true;

	while (flag&&(i<h)) {
		for (int j=0; j<w; j++)
			if (array_of_labels[i][j]==*actual_labels.begin()) {
				i1=i;
				flag=false;
				break;
			}
			i++;
	}

	i=h-1;
	flag=true;
	while(flag&&(i>0)) {
		for (int j=0; j<w; j++)
			if (array_of_labels[i][j]==*actual_labels.begin()) {
				i2=i;
				flag=false;
				break;
			}
			i--;
	}

	i2=h-i2-1;

	int t=i2-i1;
	if (t<0) t=-t;
	if (t<almost_equal*h) return 101;
	if (i2>i1) return 102;
	else return 100;	

}

bool is_black_(int i, int j) {
	int w=s[0].size(), h=s.size();
	if ( (i<0)||(i>=h)||(j<0)||(j>=w)) return false;
	if (s[i][j]=='@') return true;
	return false;
}

bool is_white_(int i, int j) {
	int w=s[0].size(), h=s.size();
	if ( (i<0)||(i>=h)||(j<0)||(j>=w)) return false;
	if (s[i][j]=='.') return true;
	return false;
}


bool is_alone(int i, int j) {
	
	/*удаляем черные пиксели, окруженные таким образом, как пиксель X:
	@@@
	.X.
	...

	или

	@@
	@@
	.X.
	...

	Возможен поворот рисунка. 
	Черный пиксель рядом с удаляемым обязан присутствовать,  некоторых остальных может не быть в случае если их место за краем массива.
	*/

	if ((!is_black_(i-1,j))&&(!is_black_(i+1,j))) {
		if (is_black_(i,j+1)) 
			if ((!is_black_(i-1,j-1))&&(!is_black_(i,j-1))&&(!is_black_(i+1,j-1))){
				if ((!is_white_(i-1,j+1))&&(!is_white_(i+1,j+1))) return true;
				if (is_black_(i,j+2)) {
					if (is_black_(i-1,j+1)&&is_black_(i-1,j+2)) return true;
					if (is_black_(i+1,j+1)&&is_black_(i+1,j+2)) return true;
				}
			}
			if (is_black_(i,j-1))
				if ((!is_black_(i-1,j+1))&&(!is_black_(i,j+1))&&(!is_black_(i+1,j+1))) {
					if ((!is_white_(i-1,j-1))&&(!is_white_(i+1,j-1))) return true;
					if (is_black_(i,j-2)) {
						if (is_black_(i-1,j-1)&&is_black_(i-1,j-2)) return true;
						if (is_black_(i+1,j-1)&&is_black_(i+1,j-2)) return true;
					}
				}
	}

	if ((!is_black_(i,j-1))&&(!is_black_(i,j+1))) {
		if (is_black_(i+1,j)) 
			if ((!is_black_(i-1,j-1))&&(!is_black_(i-1,j))&&(!is_black_(i-1,j+1))) {
				if ((!is_white_(i+1,j-1))&&(!is_white_(i+1,j+1))) return true;
				if (is_black_(i+2,j)){
					if (is_black_(i+1,j-1)&&is_black_(i+2,j-1)) return true;
					if (is_black_(i+1,j+1)&&is_black_(i+2,j+1)) return true;
				}
			}
			if (is_black_(i-1,j))
				if ((!is_black_(i+1,j-1))&&(!is_black_(i+1,j))&&(!is_black_(i+1,j+1))) {
					if ((!is_white_(i-1,j-1))&&(!is_white_(i-1,j+1))) return true;
					if (is_black_(i-2,j)){
						if (is_black_(i-1,j-1)&&is_black_(i-2,j-1)) return true;
						if (is_black_(i-1,j+1)&&is_black_(i-2,j+1)) return true;
					}
				}
	}

	return false;
}

bool is_very_alone(int i, int j) {
	if (is_black_(i+1,j+1)||is_black_(i+1,j-1)||is_black_(i-1,j+1)||is_black_(i-1,j-1)) {
		int count=0;
		for (int u=i-1; u<=i+1; u++)
			for (int v=j-1; v<=j+1; v++) {
				if ((u==i)&&(v==j)) continue;
				if (!is_black_(u,v)) count++;
			}
			if (count==7) return true;
	}
	return false;
}

bool remove_alone_blacks() {
	int w=s[0].size(), h=s.size();
	bool res=false;

	for (int i=0; i<h; i++) {
		for (int j=0; j<w; j++) {
			if (s[i][j]=='.') continue;
			if(is_very_alone(i,j)) {
				s[i][j]='.';
				res=true;
			}
		}
	}

	if (res) return true;

	if ((w<8)||(h<14)||((double)w/h)<(7.9/26)) 		
			return false;

	for (int i=0; i<h; i++) {
		for (int j=0; j<w; j++) {
			if (s[i][j]=='.') continue;
			if(is_alone(i,j)) {
				s[i][j]='.';
				res=true;
			}
		}
	}
			
	return res;
}

int count_white_connected_regions(int &two_whites_hor, int &one_white_high, int &one_white_top) { //считаем достаточно большие дырки

	fill_array_of_labels();

	bool flag;
	do {
		flag=remove_short_horizontal_lines();
				flag=flag||remove_short_vertical_lines();		
			flag=flag||remove_short_diag_lines();
	
					flag=flag||remove_alone_blacks();
		}
	while(flag);
	fill_array_of_labels();

	remove_border_labels();
	two_whites_hor=two_whites_on_hor_line();
	one_white_high=one_white_high_func();
	one_white_top=one_white_top_func();

	trim(s);

	int t=actual_labels.size();
	if (t>2) t=2; //Если белых областей больше, чем 2, считаем, что их 2.
	return t;
}


//DEFINE PARAMETERS: LINES (horisontal and vertical)=================================

bool is_black(int j) {
	const double bold=4.0/37;
	int t=(int)(bold*(double)s.size());
	if (t==0) t=1;

	for (int i=0; i<t; i++) 
		if (s[i][j]=='@') return true;
	return false;
}

int half_top_line_func() {
	const double half_wide=0.5;
	int w=s[0].size();
	int j=0, count=0;
	while ((!is_black(j))&&(j<w-1)) j++;
	while ((is_black(j))&&(j<w-1)) {
		j++;
		count++;
	}
	if (j==w-1) if (is_black(j)) count++;

	if (count>=(half_wide*w)) return 102; 
	return 100;
}

bool is_line_wide(int i) {
	const double wide=0.83;
	int w=s[0].size();
	int j=0, count=0;

	while((s[i][j]!='@')&&(j<w-1)) j++;

	while ((s[i][j]=='@')&&(j<w-1)) {
		j++;
		count++;
	}

	if (s[i][w-1]=='@') count++;

	if (count>=wide*(double)w) 
		return true;
	return false;
}

int top_hor_line_func() {
	if (is_line_wide(0)) return 102;
	return 100;
}

int bottom_hor_line_func() {
	if (is_line_wide(s.size()-1)) return 102;
	if ((is_line_wide(s.size()-2))&&(s.size()>30)) return 102;
	return 100;
}

int middle_hor_line_func() {
	int h=s.size();

	int i1=0;
	while(is_line_wide(i1)) {
		if (i1==h-1) break;
		i1++;
	}

	int i2=h-1;
	while(is_line_wide(i2)) {
		if (i2==0) break;
		i2--;
	}

	for (int i=i1+1; i<i2; i++) 
		if (is_line_wide(i))
			return 102;
	return 100;
}

int vertical_line_func() {
	double longg=41.0/43;
	int i, w=s[0].size(), h=s.size();
	int max=0;

	for (int j=0; j<w; j++){
		int count=0;
		for (i=0; i<h; i++) 
			if (s[i][j]=='@') count++;
		if (count>max) max=count;
	}
	if (max<(longg*h)) return 100;

	return 102;
}

bool is_black_2 (int i) {
	double bold=2.0/19;
	int w=s[0].size();
	int t=(int)(bold*(double)w);
	if (t<2) t=2;
	for (int j=w-t; j<w; j++)
		if (s[i][j]=='@') return true;
	return false;
}

int vertical_line_near_right_border_func() {
	double high=75.0/88;
	int count=0, h=s.size();
	for (int i=0; i<h; i++) 
		if (is_black_2(i)) count++;
	if (count>=(high*h)) return 102;
	return 100;
}

void lines(int &top, int &bottom, int &middle, int &vertical, int &half_top, int &vertical_line_near_right_border) {
	top=top_hor_line_func();
	bottom=bottom_hor_line_func();
	middle=middle_hor_line_func();
	vertical=vertical_line_func();
	half_top=half_top_line_func();
	vertical_line_near_right_border=vertical_line_near_right_border_func();
}


//FIND LEFT&RIGHT REGIONS=================================

void fill_black(vector<string> &s_copy, bool left) {
	const double narrow=3.0/43;
	int w=s[0].size(), h=s.size(), j;

	if (left) 
		for (int i=0; i<h; i++) {

			j=0;
			while (j<w) {
				if (s[i][j]=='.') j++;
				else break;
			}

			if (j<w) 
				for (int k=j; k<w; k++)
					s_copy[i][k]='@';
		}
	else for (int i=0; i<h; i++) {
		j=w-1;
		while (j>0) {
			if (s[i][j]=='.') j--;
			else break;
		}

		if (j>0) 
			for (int k=0; k<j; k++)
				s_copy[i][k]='@';
	}

	for (int j=0; j<w; j++) {
		int i=0;
		while (i<h) {
			if (s[i][j]=='.') 
				i++;
			else break;
		}
		//	if (i<h) 
		for (int k=0; k<i; k++)
			s_copy[k][j]='@';

		i=h-1;
		while (i>0) {
			if (s[i][j]=='.') i--;
			else break;
		}

		for (int k=i; k<h; k++)
			s_copy[k][j]='@';
	}


	for (int i=0; i<h; i++) {
		int count=0;
		for (int j=0; j<w; j++) {
			if (s_copy[i][j]=='.') count++;
		}
		if (((double)count/h)<=narrow)
			for (int j=0; j<w; j++)
				s_copy[i][j]='@';
	}

}

int left_right_regions_count(bool left, int &upperbound, int &lowerbound, int &rightsmall) {
	const int rightsmall_c1=4, rightsmall_c2=7;

	int w=s[0].size(), h=s.size();

	vector<string> s_copy=s;
	fill_black(s_copy,left);

	//правая область маленькая  по площади (как у 3)?
	if (!left) {
		int count=0;
		for (int i=0; i<h; i++)
			for (int j=0; j<w; j++) 
				if (s_copy[i][j]=='.') count++;
		if (count==0) {
			rightsmall=99;
			return 0;
		}
		int right_to_S=((count*100)/(w*h));
		if (right_to_S<rightsmall_c1) rightsmall=100;
		else if (right_to_S<rightsmall_c2) rightsmall=101;
		else rightsmall=102;
	}

	upperbound=s.size();
	lowerbound=0;
	int maxcount=0, i, count, count_white, t;
	for (int j=0; j<w; j++) {
		i=0, count=0, t=0;

		while ((s_copy[i][j]!='.')&&(i!=h-1)) i++;
		if (s_copy[i][j]=='.')
			if (i<upperbound) upperbound=i;

		while (i!=h-1) {
			count_white=0;
			while (s_copy[i][j]=='.') {
				i++;
				count_white++;
			}
			if (count_white>1) count++; 
			if ((count_white==1)&&(w<=11)) count++;
			while ((s_copy[i][j]!='.')&&(i!=h-1)) i++;
		}
		if (count>maxcount) maxcount=count;


		i=h-1;
		while ((s_copy[i][j]!='.')&&(i!=0)) i--;
		if (s_copy[i][j]=='.')
			if (i>lowerbound) lowerbound=i;

	}
	return maxcount;
}

void left_right(int &left, int &right, int &left_top_higher, int &left_bottom_higher, int &rightsmall) {
	const double minrazn=1.0/15;
	int lu, ru; //left upperbound, right upperbound
	int l_lower, r_lower; //left lowerbound, right lowerbound
	left=left_right_regions_count(true, lu, l_lower,rightsmall);
	right=left_right_regions_count(false, ru, r_lower, rightsmall);

	if (!right) rightsmall=99;
	if (left&&right) {

		int razn=lu-ru;
		if (razn<0) razn=-razn;

		if (razn<=(minrazn*s.size())) left_top_higher=101;
		else if (lu>ru) left_top_higher=100;
		else left_top_higher=102;


		int razn2=l_lower-r_lower;
		if (razn2<0) razn=-razn;

		if (razn2<=(minrazn*s.size())) left_bottom_higher=101;
		else if (l_lower>r_lower) left_bottom_higher=100;
		else left_bottom_higher=102;

	}
	else {
		left_top_higher=99;
		left_bottom_higher=99;
	}
}

//DEFINE PARAMETERS: WEIGHT (where is more black pixels in trimmed letter: bottom/top, left/right)================

int right_havier_func() {
	double C=68.0/78;

	int w=s[0].size(), h=s.size();

	const double narrow=1.4;
	if (((double)h/w)>narrow) C=0.6;


	int count1=0, count2=0;

	for (int i=0; i<h; i++) {
		for (int j=0; j<w/2; j++)		 
			if (s[i][j]=='@') count1++;
		for (int j=w/2; j<w; j++)
			if (s[i][j]=='@') count2++;
	}

	if ((C*count2)>count1) return 102; 
	if (count2<(C*count1)) return 100;
	return 101;
}

int bottom_havier_func() {	
	const double C=68.0/78;
	int w=s[0].size(), h=s.size();
	int count1=0, count2=0;

	for (int j=0; j<w; j++) {
		for (int i=0; i<h/2; i++)		 
			if (s[i][j]=='@') count1++;
		for (int i=h/2; i<h; i++)
			if (s[i][j]=='@') count2++;
	}

	if ((C*count2)>count1) return 102; 
	if (count2<(C*count1)) return 100;
	return 101;
}


//DEFINE PARAMETERS: COUNT POINTS OF CONTACT WITH LEFT BORDER (one or more)=================================


bool black_px(int i) {
	const int narrow=14;
	if (s[0].size()<narrow) return ((s[i][0]=='@')||(s[i][1]=='@'));
	return ((s[i][0]=='@')||(s[i][1]=='@')||(s[i][2]=='@'));
	}


int points_of_contact_with_left_border_func(int &place) { //place=100, если низ нижней т. касания выше середины, 101, если ниже середины, 102 - если совсем внизу
	//вернем 1, если 1 т.касания, 2 - если 2 и больше
	int h=s.size();
	int i=h-1;
	place=0;
	
	if (black_px(i)) place=102;
	while (!black_px(i)) i--; //1 т.касания всегда есть

	if (i>h/2) place=101;
	else place=100;

	while (black_px(i)) {
		i--;
		if (i==-1) return 1;
	}

	while (!black_px(i)) {
		i--;
		if (i==-1) return 1;
	}

	return 2;
	}




//DEFINE PARAMETERS: main function=================================
inline string IntToString(int n) {
   std::ostringstream sin;
   sin<<n;
   return sin.str();
}

string generate_params() {
	
	int whites, two_whites_hor;
	int one_white_high,  one_white_top;
	int top_hor_line, bottom_hor_line,  middle_hor_line,  vertical_line,  half_top, rightsmall;
	int vertical_line_near_right_border;
	int left, right, left_top_higher, left_bottom_higher;
	int right_havier, bottom_havier;
	int points_of_contact_with_left_border;
	int points_place;
	string params;

	posterize();



	whites=count_white_connected_regions(two_whites_hor,one_white_high,one_white_top);

	
	lines(top_hor_line, bottom_hor_line, middle_hor_line, vertical_line, half_top, vertical_line_near_right_border); 
	left_right(left, right,left_top_higher,left_bottom_higher, rightsmall); 
	right_havier=right_havier_func();
	bottom_havier=bottom_havier_func();
	points_of_contact_with_left_border=points_of_contact_with_left_border_func(points_place);


	int params_array[params_size]={whites,one_white_high,two_whites_hor,top_hor_line,middle_hor_line,bottom_hor_line,
		left,right,left_top_higher,left_bottom_higher,
		vertical_line,half_top,vertical_line_near_right_border,one_white_top,
		right_havier,bottom_havier,points_of_contact_with_left_border,rightsmall,points_place};

	for (int i=0; i<params_size; i++) {
		if (params_array[i]<99) 
			if (params_array[i]>8) params_array[i]=8;
		if (params_array[i]==99) params_array[i]=9;
		if (params_array[i]>=100) params_array[i]-=100;
		if (params_array[i]<0) {
			params_array[i]=0;
		}

		params+=IntToString(params_array[i]);
	
	}

	return params;
}

//work with DICTIONARY (a set of preserved parameters and related numbers)=================================
int templates_weight[]={0};

class dictionary_elem{
public:
	string params;
	vector<int>weight;
	char number;
	dictionary_elem(string p,vector<int>w,char n) {
		params=p;
		weight=w;
		number=n;
	}
};

vector<dictionary_elem> dictionary;

void import_letters() {
const string templates_string="1290000099020111191012900000990221121910099020009920292019010990021121020911221209900020990209112913099020209902092129131090200099200122191411902000992001121914099020110002091022150990201100020911221511902001990200111216119020019902001111160992001099020910190729000010990209112918290000109902091229181190201099020211291911902010990222122919129000009902011219100990000099202920190109900211210209212212099000212002091120130990002099020922291310902012012001221214099000110002091022150992201100020911221511900001990200121216099200109902090019072900001111020911201829000011110209122018119000109902021229191290000099220112191010900010992002211901099020109920292119011090221121020210221210900211200202112112109000111002022120132900002110020922201310902010992001221914109020110120012210140990001100020911121510900021100002212115290020019922091111162990200199020911101609920010990209201907109220109902022019072900001111000912201829000000990009121918119020109902021019091190201099020210291911902000992201111910129020009922011219100990200099222920190109902211210209212212099022112102092222120990202120220921201309902010992209222913099220019902091222152900200199220911101610902001992000121116099200109922092019072900201111220911201829002000992229122918290020109922091129191090201099220221291912900000990221111910099000209902092129130990002120022921201311902000992001221914099000110002091122151190200199002011111629000000990209112918290000112102091110181190001099022211291912900000990001111910099002109922091229110990021099200921291109902211200209122212099000212002092120131190200099200221191409900011000209202215119000019902000212161190000199000012121609902010990209101907290000112002091120181190001099020220191911900010990202212919099002109920091129110990021110020911221209900211200209112212099000211002091120131190201111200122101411902011112001221114099000110000091122151190000199020011121629000011000209112018119000109902021129190990021120020922211209900021200209202013099000212002092211131190201099200222191409920011000209102215099200110002091122152900001111020911211811900010990202102919129000009900011219100990021099220911291109900211002209121211099002110002091122121190021111020210221229000021000209212013109020210002022121131090201121200122101410902011212002221004099000110002091212150990001100020912111511902001990200121216099020109902092019070990201099000910190729000011100209122018290000110102091221181190201099020212291912900000992201111910129000009922211219100990020099220911291109902200992229211911109022112102022021121090204120220022201329002020992229212913109020009920202219141092201100020012221509922011000209122215290020019922091212160990200199220912111609900000990009021917099000009900092229172900000099020912291811902010992222112919129000009922010119101290000099200101191009902000992229211901099002009920292119110990021111020922221209900211110209212212099000212022092120131090200099200022191409900011000209221215099000019902092212151190200199220001111611902001992000011116099200109922092119070992001099220921291729002010990209112918290020110002091110181190201099220221191911902010992202211909099000109902091119101190000099000111191009902000990229201901099000112002091111120990021120000921221209902021200209201003099020212002092020030990200199000922101410902000990002221914099000110002091011051190200199000012111609900001990009121116099020109900091029172900001100020911101829000011000209112118119020109900022029190990000099000900191009900000990009111910099020009922092019010990201099222920190109902011210209101202099002112102091022120990202110020910120309920021100209211203099020019900091010141090200199000212101409902011000209002215099020110000091022151090200199000012121629002000990209121918299000019900091210181090201099020210190929002010990209201909109020009920011219100990201101220912221109900211012209122111099020111002091120120990202099220922291309902021202209222013099020110002091221151090200199200002101609902010990009201907290020019922091120182900201111220911101810902010990202201909119020009902011119101190200099200111191009902000992029211901099022112102092220120990221121000912201209902021200209112013099020212002091220130990201100020911211509922011000209112115109020019900000210160990201099220910190729002000992209122918109020009902021119192900200099020901191011902000990001111910299020009922292019011090221121020211221210902011210202112212099020211002092010130990202110020921211309902000990009121914099020110002091212150990000199000912121610902020990200201907290020009920091229181190200099022220290911902000992222201909292000009902091119102920000099020922191012900200992201122911099002009922291219110990021120020920221229000210990229222912290000211022292120131090201111200122101429200011112029221014109000110002021012151090001100020210221529202001990209011216292000019902090212161292001099020110190729020010990209202917299000111002092220182920001099020921291912900000990001101910099000109900091019110990001099000910291109902011010009221212099000211002092010130990002100020920101310902011000001221014109020019900010210140990001100020910101509900011000209201015099020109902090019070992001099020910291729000011100209001018290000112002090020181090001121020210100910900001990002101109099002109920091229110990021121020912221209900021202209222013099000110002091222151190200199000012121611900001990000021216290000110122091220181190001099020210190911902010990202211919099022112102091122120990202120020921201309900021200209212113119020029920012212142900201111020911201829000011200209122018099000211002092120132900001110020911201811900010990202201909099200009922292119010990002099020920291309900011000209211215119000019900001211162900001101020911201809900220992209112911099002109920092229110992201100020910221529002001990209112018119020111120022210141190201111202122101429000011110209111018099002109920090229110990021121020922221209900021200209222013099200110002090022151190200199020001111611902001990200011216290000112000091120181190201099020221291911902000992002221914099000110002091012151190000199000002111611902010990202101919119000109902021119191290200099220111191012902000992221111910099020209922091129132900002099222911291310902000992201211914109020009922011119141190200199220011111629002000992209112918290020009922091119181190201099220211291909902021200209102013099022112102091222121090200099200121191429000011010209112118099000209902091229131290000099002111191009902211210209102212290000110000091120180990021099220921291109900211012209112211099000210002091221131190201111200222111429000011002209122018109020009920022119141090200099200222191429002000990229121918119020109902021119091190201099020211191909900211100209212212099000212002292210131190201099200122191429000011110209122118099020212022091120131090200099202122191429002011102209112018290000019902091110181190201099000221191912900000992221111910099002009922092119010990002099220921291329000000992229112918119020009922211119100990020099220912291109902200992229121911099022112102091120121090221121020012201209922021102209112013099220211022291220131090200099222121191410902000992222211914099220110002091221151090200199220011101610902001992220121016290020009922291119181090200099222211291910902010992222112919099022109920292129110990001121020920110209900011110209201202099000111002092110131090201111200222111409900011000209102115099000110002092020151290000199000011111609920011210209101107099200112102092012071190001099000221291909900010990009201911099000112100091210120990001121000922101209900021200009211013109000209902002019131090001100000211101410900010990001111914099000110000091111150990001100000922111511900001990000011116099000109902092019172900000099000910191829000000990009011918119000109900021029191190001099000220191929000010990009122918290000110002091220180990001100000912121511900021100202212013099022009922291129110992001099020911291711900001992200021216099000110002092222151090200099000201191410902000990002111914109020109902021019190990021121020922201209902000992009221914119020009902222029192900001111000911201812900010990202102919099002109922092229111190000199020010121609902011000209212215109020029920012112140990201100020911121509900021200209221013099002112100092222120990021120020910221211900010990002001909099002112100091222121190000199020011111609902000992209111914119000109902022029190992002110020910201311900001990000111216099002112102092112121190201099202222191410902000990001221914099020112120090121120990021099220902291112920200992221211911290000019902091120181290000199020012121609900200992009121911119020009920012119141190001099020211190909900001992209112013109020111120012211140990202110020911221309900000990009201901099000209902092119130990200199000921101411902010990002102919290000009922091129181190000199220012121610902011112001221214109020009922222019090992002110020920211310902001992002221014099000110022091122111092002100020011221509902211212209122112290020109920292119141190201110000002221529002001990209111116290000109902091119192900000099020911191809902011000209112015119022112102021121121090200199220012111609900021100209202113290020111102091121180990201121000922121229000001990209211018119020109902022029192900200099020921291510902011112201221014099020210002091121130990201121020911121211900001990000111116099020112022091221121190201201020012221809902000992229201914109020009920001219161290000099020121191009902010990209102917";
const int templates_weight[]={9,8,0,10,8,10,9,10,0,0,8,8,8,9,9,8,10,0,10,9,8,0,10,8,10,9,10,0,0,8,8,2,9,9,2,10,0,10,9,0,0,9,4,4,5,9,0,0,9,5,4,0,5,3,5,0,4,9,0,0,10,7,8,10,9,9,8,9,9,9,0,7,5,9,8,9,9,0,0,9,7,10,9,3,0,0,8,9,9,0,2,7,8,0,9,9,0,0,9,3,10,9,3,0,0,8,9,9,0,8,7,8,0,9,9,6,0,10,9,10,7,7,0,0,8,9,9,6,9,8,10,0,9,9,4,0,10,9,10,7,7,0,0,8,9,9,6,1,8,10,0,9,9,0,0,7,4,10,9,9,9,9,10,9,10,0,8,5,8,8,9,9,0,0,7,4,10,9,9,9,9,10,9,10,0,8,4,8,8,9,9,7,0,10,6,10,10,9,0,0,8,6,9,9,8,4,10,7,10,9,7,0,10,6,10,10,9,0,0,8,6,9,9,8,4,10,3,10,9,0,0,8,8,10,9,9,0,0,9,9,10,0,6,9,8,0,8,9,0,9,10,8,10,7,3,0,0,8,9,9,0,9,7,8,0,10,9,0,9,10,8,10,7,3,0,0,8,9,9,0,9,2,8,0,10,9,8,0,10,6,10,9,9,0,0,9,9,9,9,7,5,6,0,7,9,8,0,10,6,10,9,9,0,0,9,9,1,9,7,1,6,0,7,9,8,0,10,8,10,9,10,0,0,8,8,8,9,9,2,10,0,10,9,0,0,9,6,4,5,9,0,0,9,5,4,0,5,3,5,0,4,9,0,0,10,7,8,10,9,9,8,9,9,9,0,3,5,9,8,9,9,0,0,9,7,10,9,7,6,7,8,9,9,0,2,7,8,7,9,9,0,0,9,7,10,9,3,0,0,8,9,9,0,8,2,8,0,9,9,6,0,10,9,10,3,1,1,3,8,9,9,6,9,8,10,1,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,8,5,8,8,9,9,0,0,3,4,10,9,9,9,9,10,9,10,0,8,4,8,8,9,9,7,0,10,4,10,10,9,0,0,8,6,9,9,8,6,10,7,10,9,0,0,8,8,10,9,9,0,0,9,9,10,0,1,9,8,0,8,9,0,9,10,8,10,7,7,5,6,8,9,9,0,9,7,8,7,10,9,0,9,10,8,10,7,7,5,6,8,9,9,0,9,2,8,7,10,9,8,0,10,4,10,9,9,0,0,9,9,9,9,7,1,6,0,7,9,8,0,10,8,10,9,10,0,0,2,8,8,9,9,2,10,0,10,1,1,0,9,6,4,5,9,0,0,9,5,6,1,5,3,5,0,4,9,0,0,9,4,4,5,9,0,0,9,5,4,0,5,3,5,0,4,1,1,0,10,3,8,10,9,9,8,9,9,9,1,7,1,9,8,9,1,1,0,10,7,8,10,9,9,2,9,9,9,1,7,5,9,1,9,1,1,0,9,7,10,1,7,2,7,8,9,9,1,8,7,8,7,9,1,0,1,9,7,10,9,7,2,7,8,9,9,0,8,2,8,7,9,9,6,0,10,9,10,3,7,0,0,8,9,9,6,9,8,10,0,9,9,6,0,10,9,10,3,3,1,3,8,9,9,6,9,8,10,2,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,8,4,2,8,9,1,1,0,7,6,10,1,9,1,9,10,1,10,1,1,4,8,1,9,1,0,1,10,6,10,10,9,0,0,2,6,9,0,8,4,10,3,10,1,0,0,10,6,10,10,9,0,0,8,6,9,0,8,4,10,1,10,9,0,0,8,8,10,9,9,0,0,9,9,10,0,4,9,8,0,8,1,1,0,8,2,10,9,9,0,0,9,9,10,1,4,9,8,0,8,9,0,9,10,8,10,7,7,5,6,8,1,9,0,9,2,8,7,10,9,0,9,10,8,10,3,3,0,0,8,1,9,0,9,2,2,0,10,9,8,0,10,6,10,9,9,0,0,9,9,9,9,7,4,4,0,3,9,8,0,10,6,10,9,9,0,0,9,9,9,9,7,4,6,0,7,9,1,0,10,2,10,9,10,0,0,2,8,8,9,9,8,10,0,10,9,8,0,10,2,10,9,10,0,0,2,8,8,9,9,2,10,0,10,9,0,0,9,4,4,5,9,0,0,9,5,4,0,5,3,5,0,4,9,0,0,10,3,8,10,9,9,8,9,9,9,0,3,5,9,8,9,9,0,0,10,3,8,10,9,9,8,9,9,9,0,3,4,9,8,9,9,0,0,9,3,10,9,7,6,7,2,9,9,0,8,7,8,7,9,9,0,0,9,3,10,1,3,0,0,2,9,9,0,8,2,8,0,9,9,0,0,3,4,10,1,9,0,0,10,9,10,0,8,2,8,8,9,1,0,1,10,6,10,10,9,0,0,2,6,9,0,8,4,10,1,10,9,2,0,10,6,10,10,9,0,0,2,4,9,9,8,6,10,3,10,9,0,0,8,8,10,9,9,0,0,1,9,10,0,4,9,8,0,8,9,0,9,10,2,10,7,7,5,6,2,9,9,0,9,7,8,7,10,9,0,9,10,2,10,3,3,0,0,2,9,1,0,9,2,8,0,10,1,0,1,10,6,10,9,9,0,0,1,9,9,0,7,5,6,0,7,9,1,0,10,6,10,9,9,0,0,1,9,9,9,2,5,6,0,7,9,8,0,10,8,10,9,10,0,0,8,8,2,9,9,8,10,0,10,9,0,0,9,7,10,9,3,0,0,8,9,9,0,8,7,8,0,9,9,0,0,9,7,10,9,7,6,7,8,9,1,0,8,7,8,7,9,9,4,0,10,9,10,7,7,0,0,8,9,9,6,9,8,10,0,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,8,4,8,8,9,9,7,0,10,6,10,10,9,0,0,8,4,1,9,8,4,10,3,10,9,0,9,10,8,10,3,3,0,0,8,9,9,0,9,7,8,0,10,9,0,9,10,8,10,7,7,1,6,8,9,9,0,9,7,2,7,10,9,8,0,10,4,10,9,9,0,0,9,9,1,9,7,5,6,0,7,9,8,0,10,8,10,9,10,0,0,8,2,8,9,9,8,10,0,10,9,0,0,9,6,6,5,9,0,0,9,5,6,0,5,4,5,0,6,9,0,0,9,6,6,5,9,0,0,9,5,6,0,5,3,5,0,6,9,0,0,10,3,8,10,9,9,2,9,9,9,0,7,4,9,8,9,9,0,0,9,7,10,9,7,6,7,8,9,9,0,8,7,8,7,9,9,4,0,10,9,10,7,7,0,0,8,9,9,2,9,2,10,0,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,1,5,8,8,9,9,7,0,10,4,10,10,9,0,0,8,6,9,9,2,6,10,7,10,9,7,0,10,4,10,10,9,0,0,8,4,9,9,8,6,10,7,10,9,0,0,2,2,10,9,9,0,0,9,9,10,0,6,9,8,0,8,9,0,9,10,8,10,7,7,1,2,8,9,9,0,9,7,8,7,10,9,8,0,10,4,10,9,9,0,0,9,9,9,9,2,4,4,0,7,9,8,0,10,4,10,9,9,0,0,9,9,9,9,2,5,6,0,7,9,0,0,9,6,6,5,9,0,0,9,5,6,0,5,3,5,0,6,9,0,0,10,7,8,10,9,1,2,9,9,9,0,7,5,9,8,9,9,0,0,10,7,8,10,9,9,2,9,9,9,0,7,5,9,8,9,9,0,0,9,7,10,9,7,2,7,8,9,9,0,2,7,8,7,9,9,4,0,10,9,10,3,3,2,3,8,9,9,6,9,8,10,2,9,9,4,0,10,9,10,3,3,2,3,8,9,9,6,9,8,10,1,9,9,0,0,7,6,10,9,9,9,9,10,1,10,0,8,4,8,8,9,9,7,0,10,4,10,10,9,0,0,8,6,9,9,8,4,10,7,10,9,0,9,10,8,10,7,7,2,2,8,9,9,0,9,7,8,7,10,9,8,0,10,4,10,9,9,0,0,9,9,9,9,7,5,6,0,7,9,0,0,10,7,8,10,9,9,2,9,9,9,0,3,4,9,1,9,9,0,0,9,7,10,9,7,6,7,8,9,9,0,8,2,8,7,9,9,0,0,9,7,10,9,7,6,7,8,9,9,0,8,2,2,1,9,9,4,0,10,9,10,3,7,0,0,8,9,9,2,9,8,10,0,9,9,0,0,3,6,10,9,9,9,9,10,9,10,0,8,5,8,8,9,9,0,0,3,6,10,9,9,9,9,10,9,10,0,8,4,8,8,9,9,0,9,10,8,10,7,7,5,6,8,9,9,0,9,7,8,1,10,9,8,0,10,4,10,9,9,0,0,9,9,9,9,7,4,6,0,7,9,8,0,10,8,10,9,10,0,0,8,2,8,9,9,2,10,0,10,9,0,0,9,6,6,5,9,0,0,9,5,6,0,5,3,5,0,6,9,0,0,9,6,6,5,1,1,1,9,5,6,0,5,4,5,1,6,9,0,0,10,7,8,10,9,1,2,9,9,9,0,7,5,9,8,9,1,1,0,10,7,8,10,9,1,8,9,9,9,1,7,1,9,8,9,1,0,1,9,7,10,9,7,1,7,8,9,9,0,8,7,8,7,9,1,1,0,9,3,10,9,7,1,7,8,9,9,1,8,7,8,1,9,9,6,0,10,9,10,3,3,1,3,8,9,9,6,9,8,10,2,9,9,6,0,10,9,10,3,3,1,3,8,9,9,2,9,8,10,2,1,9,0,0,7,6,10,9,9,9,9,10,9,10,0,8,2,2,8,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,8,2,2,1,9,9,7,0,10,6,10,10,9,0,0,8,6,9,9,8,6,10,7,10,9,0,0,2,2,10,9,9,0,0,9,9,10,0,4,9,8,0,8,9,0,0,2,2,10,9,9,0,0,9,1,10,0,6,9,8,0,8,9,0,9,10,8,10,7,7,5,2,8,9,9,0,9,2,8,7,10,9,0,9,10,8,10,7,7,2,6,8,9,9,0,9,2,8,1,10,9,8,0,10,6,10,9,9,0,0,9,9,9,9,7,1,6,0,7,9,8,0,10,8,10,9,10,0,0,2,8,8,9,9,8,10,0,10,9,8,0,10,8,10,9,10,0,0,2,8,2,9,9,2,10,0,10,9,0,0,9,6,6,5,9,0,0,9,5,6,0,5,3,5,0,6,9,0,0,9,4,6,5,9,0,0,9,5,4,0,5,3,5,0,6,1,1,0,10,3,8,10,9,9,8,9,9,9,1,3,1,9,1,9,1,1,0,9,3,10,1,7,6,7,2,9,9,1,8,2,8,7,9,1,0,1,9,3,10,9,3,0,0,2,9,1,0,8,7,8,0,9,9,6,0,10,9,10,7,7,0,0,8,9,1,1,9,8,10,0,9,1,1,0,3,4,10,9,9,9,9,10,9,10,1,8,2,8,8,9,9,0,0,3,4,10,9,9,9,9,10,9,10,0,8,2,8,8,9,1,0,1,10,6,10,10,9,0,0,2,6,9,0,8,6,10,7,10,1,0,0,10,6,10,10,9,0,0,2,6,9,0,8,6,10,3,10,9,0,0,2,8,10,1,9,0,0,9,1,10,0,1,1,8,0,2,9,0,0,2,8,10,1,9,0,0,9,1,10,0,4,1,2,0,2,9,0,9,10,8,10,3,3,0,0,8,9,9,0,9,2,8,0,10,9,8,0,10,6,10,9,9,0,0,1,9,1,9,7,5,6,0,7,9,8,0,10,8,10,9,10,0,0,2,8,8,9,1,8,10,0,10,9,8,0,10,8,10,9,10,0,0,2,2,8,9,1,8,10,0,10,9,0,0,9,4,4,5,9,0,0,9,5,4,0,5,3,5,0,4,9,0,0,9,6,6,5,9,0,0,9,5,4,0,5,3,5,0,6,9,0,0,10,7,8,10,9,1,8,9,9,9,0,3,4,9,8,9,9,0,0,10,7,8,10,9,1,8,9,9,9,0,3,5,9,8,9,9,0,0,9,7,10,9,7,6,7,2,9,9,0,8,7,8,7,9,9,6,0,10,9,10,7,7,0,0,8,9,9,1,9,8,10,0,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,1,2,2,8,9,9,0,0,7,6,10,1,9,0,0,10,9,10,0,1,2,2,8,9,9,7,0,10,6,10,10,9,0,0,2,6,9,9,2,4,10,3,10,9,7,0,10,6,10,10,9,0,0,2,4,9,9,2,4,10,3,10,9,0,0,8,8,10,9,9,0,0,1,9,10,0,4,1,8,0,8,9,0,0,8,8,10,9,9,0,0,1,9,10,0,4,1,2,0,2,9,0,9,10,2,10,7,3,0,0,8,9,9,0,9,7,8,0,10,9,0,9,10,2,10,7,7,2,2,8,9,9,0,9,7,2,7,10,9,8,0,10,6,10,9,9,0,0,1,9,9,9,2,5,4,0,7,9,8,0,10,6,10,9,9,0,0,1,9,9,9,2,5,4,0,3,1,0,0,10,8,10,1,10,0,0,8,8,8,0,9,8,10,0,10,9,1,0,10,8,10,9,10,0,0,8,2,8,9,9,8,10,0,10,9,0,0,9,4,4,5,9,0,0,1,5,4,0,5,3,5,0,4,9,0,0,10,7,2,10,9,9,2,9,9,9,0,7,5,1,1,9,9,0,0,10,7,8,10,9,9,2,9,1,9,0,3,5,9,8,9,9,0,0,9,3,10,9,7,6,7,8,9,9,0,8,2,2,7,1,9,0,0,9,3,10,9,7,6,7,8,9,9,0,8,2,8,7,1,1,0,0,10,9,10,7,3,0,0,2,9,9,0,9,8,10,2,9,9,6,0,10,9,10,7,7,0,0,2,9,9,2,9,8,10,0,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,8,5,2,1,1,9,7,0,10,6,10,10,9,0,0,8,4,9,9,8,6,10,3,10,1,0,0,10,4,10,10,9,0,0,8,4,9,0,8,6,10,3,10,9,0,0,2,2,10,9,9,0,0,9,1,10,0,6,9,2,0,2,9,0,9,10,8,10,7,7,2,2,8,9,9,0,9,7,2,7,10,9,0,9,10,8,10,7,7,2,2,8,9,9,0,9,7,8,1,10,9,8,0,10,6,10,9,9,0,0,9,1,9,9,2,4,6,0,7,1,0,0,10,8,10,9,10,0,0,8,2,8,0,1,1,10,0,10,1,0,0,10,8,10,9,10,0,0,8,2,8,0,9,8,10,0,10,9,0,0,9,4,4,5,9,0,0,9,5,6,0,5,3,5,0,4,9,0,0,9,4,4,5,9,0,0,9,5,4,0,5,3,5,0,4,9,0,0,10,3,2,10,9,9,8,9,9,9,0,7,1,1,8,1,9,0,0,10,7,8,10,9,9,8,9,9,9,0,7,1,9,8,9,9,0,0,9,3,10,9,7,2,7,8,9,9,0,2,2,2,1,1,9,0,0,1,7,10,9,7,2,7,8,9,9,0,8,7,2,1,1,1,0,0,10,9,10,7,3,0,0,2,9,9,0,1,1,10,2,9,9,6,0,10,9,10,7,3,0,0,2,9,9,2,1,8,10,2,9,9,0,0,7,4,10,9,9,9,9,10,9,10,0,1,5,8,8,9,9,0,0,7,4,10,9,9,9,9,10,1,10,0,8,5,8,8,9,9,2,0,10,6,10,10,9,0,0,8,4,9,9,8,6,10,7,10,9,0,9,10,2,10,3,3,0,0,8,9,9,0,9,2,2,0,10,9,0,0,10,8,10,3,7,0,0,8,1,9,0,9,2,2,7,10,9,1,0,10,6,10,9,9,0,0,9,9,9,9,7,4,4,0,3,1,0,1,10,6,10,9,9,0,0,9,9,9,0,2,4,4,0,3,9,1,0,10,2,10,9,10,0,0,2,2,8,9,9,2,10,0,10,9,0,0,9,4,4,5,1,1,1,9,5,6,0,5,4,5,1,6,9,0,0,9,6,6,5,1,1,1,9,5,6,0,5,4,5,1,6,9,0,0,10,3,2,10,9,1,2,9,9,9,0,7,5,9,1,9,9,0,0,9,3,10,9,3,0,0,2,9,9,0,8,2,8,0,9,9,0,0,9,3,10,9,7,6,7,2,9,9,0,8,2,8,7,9,9,0,0,7,4,10,9,9,9,9,10,9,10,0,8,2,8,1,9,9,2,0,10,6,10,10,9,0,0,2,4,9,9,2,6,10,1,10,9,0,0,2,2,10,9,9,0,0,9,1,10,0,4,9,8,0,8,9,0,9,10,2,10,3,7,0,0,2,9,9,0,9,7,8,7,10,9,0,9,10,2,10,7,7,5,6,2,9,9,0,9,7,2,7,10,9,1,0,10,6,10,9,9,0,0,9,9,9,9,2,4,4,0,3,9,1,0,10,2,10,9,10,0,0,8,8,8,9,9,8,10,0,10,9,1,0,10,2,10,9,10,0,0,2,2,8,9,9,8,10,0,10,9,0,0,9,4,4,5,9,0,0,9,5,4,0,5,3,5,0,4,9,0,0,10,3,8,10,9,9,8,9,9,9,0,3,4,9,1,9,9,0,0,10,3,8,10,9,9,8,9,1,9,0,7,4,9,1,9,9,0,0,9,3,10,9,7,6,7,8,9,9,0,2,7,8,7,9,9,0,0,9,3,10,9,7,6,7,8,9,9,0,2,2,8,7,9,9,0,0,7,4,10,9,9,9,9,10,9,10,0,8,4,8,1,9,9,0,0,3,4,10,9,9,9,9,10,9,10,0,8,4,8,1,9,9,2,0,10,6,10,10,9,0,0,8,4,9,9,2,6,10,1,10,9,0,0,2,2,10,9,9,0,0,1,9,10,0,6,9,8,0,8,9,0,9,10,2,10,3,3,0,0,2,9,9,0,9,2,8,0,10,9,1,0,10,6,10,1,9,0,0,9,9,9,9,7,5,4,0,7,1,0,1,10,2,10,9,10,0,0,8,8,8,0,1,8,10,0,10,9,1,0,10,2,10,9,10,0,0,8,2,8,9,9,8,10,0,10,1,0,0,9,4,4,5,9,0,0,9,5,4,0,5,3,5,0,4,1,1,0,10,3,8,10,9,9,8,9,9,9,1,7,5,9,8,9,1,1,0,10,3,2,10,9,9,8,9,9,9,1,7,5,9,8,9,9,0,0,9,3,10,9,7,2,7,8,9,9,0,8,2,2,7,9,9,0,0,9,3,10,9,7,2,7,8,9,9,0,8,7,8,1,9,1,0,0,10,9,10,7,7,0,0,2,9,9,0,1,8,10,0,9,9,0,0,7,4,10,9,9,9,9,10,9,10,0,8,2,2,8,9,1,0,0,10,4,10,10,9,0,0,8,4,9,0,8,6,10,7,10,1,1,0,2,2,10,1,9,0,0,9,9,10,1,4,9,8,0,8,9,0,9,10,2,10,3,3,0,0,2,1,9,0,9,2,8,0,10,9,8,0,10,6,10,1,9,0,0,9,9,1,9,2,4,6,0,3,9,8,0,10,6,10,1,9,0,0,1,9,1,9,2,4,4,0,3,1,0,1,10,8,10,9,10,0,0,8,8,8,0,9,8,10,0,10,1,0,1,10,8,10,9,10,0,0,8,8,8,0,1,2,10,0,10,1,1,0,9,6,6,5,9,0,0,9,5,6,1,5,4,5,0,6,9,0,0,9,6,6,5,9,0,0,9,5,4,0,5,4,5,0,6,9,0,0,10,7,8,10,9,9,2,9,9,9,0,3,1,9,8,9,1,0,1,10,7,8,10,1,0,0,9,9,1,0,3,4,9,0,9,1,0,1,9,7,10,9,7,2,7,2,9,1,0,8,7,8,7,9,9,6,0,10,9,10,3,3,2,3,8,9,9,6,9,8,10,2,9,1,0,1,10,1,10,3,3,2,3,8,9,1,0,9,8,10,2,9,1,1,0,7,6,10,9,9,9,9,10,9,10,1,8,5,2,8,9,1,1,0,7,6,10,9,9,9,9,10,9,10,1,8,5,8,8,9,1,0,1,10,6,10,10,9,0,0,8,6,9,0,2,4,10,7,10,1,0,1,10,4,10,10,9,0,0,8,6,9,0,2,6,10,7,10,1,1,0,8,8,10,9,9,0,0,9,9,10,1,6,9,8,0,8,1,0,1,8,8,10,9,9,0,0,9,9,10,0,4,9,2,0,2,9,0,0,10,8,10,7,7,5,2,8,9,9,0,1,2,8,7,10,1,0,1,10,4,10,9,9,0,0,9,9,9,0,2,5,6,0,7,9,8,0,10,8,10,9,10,0,0,8,2,8,9,9,1,10,0,10,9,0,0,9,6,4,5,9,0,0,1,5,6,0,5,3,5,0,6,9,0,0,9,6,4,5,9,0,0,1,5,6,0,5,3,5,0,6,9,0,0,10,3,2,10,9,1,8,9,1,9,0,3,4,1,8,9,9,0,0,9,7,10,9,7,2,7,8,9,9,0,8,2,2,7,9,9,0,0,9,7,10,9,7,1,7,8,9,9,0,8,2,2,7,9,9,6,0,10,9,10,3,3,1,1,2,9,9,6,9,8,10,2,9,9,6,0,10,9,10,7,3,0,0,2,9,9,6,1,8,10,2,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,8,5,2,1,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,1,5,2,1,9,9,0,0,2,2,10,9,9,0,0,9,9,10,0,1,9,8,0,8,9,0,0,8,8,10,9,9,0,0,9,9,10,0,6,9,2,0,2,9,0,9,10,8,10,7,7,5,2,8,9,9,0,1,1,2,7,10,9,0,9,10,8,10,7,7,1,2,8,9,9,0,1,1,8,7,10,9,1,0,10,4,10,9,1,1,1,9,9,9,9,7,4,4,1,3,9,1,0,10,4,10,1,1,0,0,9,1,9,9,7,4,4,1,3,9,0,0,9,6,6,5,9,0,0,9,5,6,0,5,4,5,0,6,9,0,0,10,7,8,10,9,9,8,9,9,9,0,7,4,9,8,9,9,0,0,9,7,10,9,7,6,7,2,9,9,0,8,2,8,7,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,8,2,8,8,9,9,7,0,10,6,10,10,9,0,0,8,4,9,9,8,6,10,7,10,9,7,0,10,4,10,10,9,0,0,8,4,9,9,2,6,10,7,10,9,0,9,10,8,10,7,7,2,6,2,9,9,0,9,2,8,7,10,9,8,0,10,4,10,9,9,0,0,9,9,9,9,7,4,4,0,3,9,8,0,10,6,10,9,9,0,0,9,9,9,9,2,5,4,0,7,9,0,0,10,3,8,10,9,9,8,9,9,9,0,7,5,9,8,9,9,0,0,9,3,10,9,7,6,7,8,9,9,0,8,7,8,7,9,9,0,0,9,7,10,9,7,6,7,8,9,9,0,8,7,8,1,9,9,4,0,10,9,10,7,1,0,0,8,9,9,6,9,8,10,1,9,9,0,9,10,2,10,7,7,5,6,8,9,9,0,9,7,8,7,10,9,0,9,10,8,10,7,7,1,2,8,9,9,0,9,2,8,7,10,9,0,0,9,7,10,9,7,2,7,8,9,9,0,8,7,8,7,9,9,0,9,10,8,10,7,7,5,2,8,9,9,0,9,7,8,7,10,9,8,0,10,4,10,9,9,0,0,9,9,9,9,2,4,4,0,3,9,0,0,1,6,4,5,9,0,0,9,5,4,0,5,3,5,0,4,9,0,0,9,7,10,9,3,0,0,8,9,9,0,8,2,8,0,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,1,4,2,8,9,9,7,0,10,4,10,10,9,0,0,8,4,9,9,8,6,10,3,10,9,0,9,10,8,10,7,7,2,6,8,9,9,0,9,7,8,7,10,9,0,0,9,6,6,1,9,0,0,9,5,6,0,5,3,5,0,6,9,0,0,9,6,6,5,9,0,0,9,5,6,0,5,4,5,0,6,9,0,0,3,4,10,9,9,9,9,10,9,10,0,8,5,8,8,9,9,0,9,10,2,10,3,7,0,0,8,9,9,0,9,7,8,7,10,9,4,0,10,9,10,3,3,2,3,8,9,9,2,9,8,10,2,9,9,4,0,10,9,10,3,3,2,3,8,9,1,6,9,8,10,2,9,9,0,9,10,8,10,7,7,5,6,8,9,9,0,9,7,2,7,10,9,0,0,9,6,6,5,9,0,0,9,5,6,0,1,4,5,0,6,9,0,0,10,7,8,10,9,9,8,9,9,9,0,3,4,9,8,9,9,0,0,9,7,10,9,7,6,7,8,9,9,0,8,2,8,7,9,9,0,0,3,6,10,9,9,9,9,10,9,10,0,1,5,8,8,9,9,7,0,10,6,10,10,9,0,0,8,6,9,9,2,4,10,3,10,9,7,0,10,6,10,10,9,0,0,8,6,9,9,2,4,10,7,10,9,0,9,10,8,10,7,7,1,2,8,1,9,0,9,7,8,7,10,9,8,0,10,6,10,9,9,0,0,9,9,9,9,2,5,6,0,7,9,4,0,10,9,10,7,7,0,0,8,9,9,2,9,8,10,0,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,8,5,2,8,9,9,7,0,10,4,10,10,9,0,0,8,4,9,9,2,6,10,3,10,9,8,0,10,6,10,9,9,0,0,9,9,9,9,7,4,4,0,7,9,8,0,10,4,10,9,9,0,0,9,9,9,9,7,5,4,0,7,9,8,0,10,2,10,9,10,0,0,2,8,8,9,9,8,10,0,10,9,8,0,10,2,10,9,10,0,0,2,8,2,9,9,8,10,0,10,9,0,0,9,3,10,9,3,0,0,2,9,9,0,2,7,8,0,9,1,0,1,9,7,10,9,3,0,0,2,9,1,0,2,7,8,0,9,9,6,0,10,9,10,7,7,0,0,8,1,9,6,9,2,10,0,9,9,6,0,10,9,10,7,7,0,0,8,1,9,6,1,2,10,0,9,9,7,0,10,6,10,10,9,0,0,2,6,9,9,8,4,10,3,10,9,0,9,10,2,10,3,3,0,0,2,9,9,0,9,7,8,0,10,9,0,9,10,2,10,3,3,0,0,2,9,9,0,9,7,2,0,10,9,8,0,10,6,10,9,9,0,0,1,9,9,9,7,5,6,0,7,9,0,0,9,3,10,9,7,6,7,8,9,9,0,2,2,8,7,9,9,0,0,10,3,8,10,9,9,8,9,9,9,0,7,4,9,8,9,9,6,0,10,9,10,7,7,0,0,8,9,9,6,9,2,10,0,9,9,0,9,10,8,10,7,7,2,6,8,9,9,0,9,7,8,1,10,9,0,0,9,7,10,9,3,0,0,8,9,9,0,2,2,8,0,9,9,8,0,10,8,10,9,10,0,0,8,2,2,9,9,8,10,0,10,9,0,0,10,3,8,10,9,9,8,9,9,9,0,7,1,9,8,9,9,0,9,10,8,10,7,7,2,2,8,1,9,0,9,7,8,7,10,9,0,0,9,6,6,5,9,0,0,9,5,6,0,5,3,5,0,6,9,0,0,9,6,6,5,1,1,1,9,5,6,0,5,3,5,1,6,9,0,0,9,7,10,9,7,1,7,8,9,9,0,2,2,8,1,9,9,4,0,10,9,10,3,3,2,3,8,9,9,2,9,8,10,1,9,9,0,9,10,8,10,7,7,2,2,2,9,9,0,9,2,8,7,10,9,6,0,10,9,10,7,7,0,0,8,9,9,2,9,2,10,0,9,9,6,0,10,9,10,7,7,0,0,8,9,9,2,9,8,10,0,9,9,0,9,10,2,10,3,3,0,0,8,9,1,0,9,2,2,0,10,9,8,0,10,6,10,9,9,0,0,9,9,9,9,7,5,4,0,3,9,8,0,10,6,10,9,9,0,0,9,9,9,9,7,5,4,0,7,9,0,0,10,7,8,10,9,1,2,9,9,9,0,3,5,9,8,9,9,0,0,9,7,10,9,7,6,7,8,9,1,0,8,2,2,7,9,9,4,0,10,9,10,3,7,0,0,8,9,9,6,9,8,10,0,9,9,0,9,10,8,10,7,7,5,6,8,9,9,0,9,2,8,1,10,9,0,0,9,3,10,9,7,6,7,2,9,9,0,2,7,8,7,9,9,6,0,10,9,10,7,7,0,0,8,9,1,6,9,8,10,0,9,9,0,9,10,2,10,7,7,5,2,2,9,9,0,9,7,8,7,10,9,0,9,10,8,10,3,7,0,0,8,9,9,0,9,7,2,7,10,9,8,0,10,6,10,9,9,0,0,9,1,9,9,2,5,4,0,7,9,8,0,10,8,10,9,10,0,0,2,8,2,9,9,8,10,0,10,9,0,0,9,6,6,5,9,0,0,9,5,6,0,5,3,5,0,4,9,0,0,9,7,10,9,3,0,0,2,9,9,0,8,7,8,0,9,9,0,9,10,8,10,3,3,0,0,2,9,1,0,9,7,8,0,10,9,1,0,10,2,10,9,10,0,0,2,8,2,9,9,8,10,0,10,9,0,0,9,6,6,5,9,0,0,9,5,6,0,5,4,5,0,6,9,0,0,9,4,6,5,9,0,0,9,5,4,0,5,4,5,0,6,9,0,0,10,3,8,10,9,9,8,9,9,9,0,7,5,9,1,9,1,1,0,10,3,8,10,9,9,8,9,9,9,1,7,4,9,1,9,9,0,0,1,3,10,9,7,2,7,2,9,9,0,2,7,8,7,9,9,0,0,1,3,10,9,7,2,7,2,9,1,0,2,2,8,7,9,9,6,0,10,9,10,7,7,0,0,8,1,1,6,9,2,10,0,9,9,6,0,10,9,10,7,7,0,0,8,1,1,2,9,2,10,0,9,9,0,0,3,4,10,9,9,9,9,10,9,10,0,8,2,8,1,9,9,2,0,10,6,10,10,9,0,0,2,6,9,9,8,4,10,1,10,9,2,0,10,6,10,10,9,0,0,2,6,1,9,8,6,10,1,10,9,0,9,10,2,10,3,3,0,0,2,9,1,0,9,7,2,0,10,9,1,0,10,6,10,1,9,0,0,1,9,1,9,7,5,6,0,7,9,1,0,10,6,10,9,9,0,0,1,9,1,9,7,5,6,0,7,9,0,0,9,4,6,5,9,0,0,9,5,4,0,5,3,5,0,6,9,0,0,10,7,2,10,9,9,8,9,9,9,0,3,1,1,1,1,9,0,0,10,7,2,10,9,1,8,9,9,9,0,3,1,1,8,1,9,0,0,9,7,10,1,7,2,7,8,9,9,0,8,7,2,7,9,9,6,0,10,9,10,3,3,2,3,8,9,9,2,9,8,10,1,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,8,5,8,1,9,9,0,0,7,6,10,9,9,9,9,10,9,10,0,1,5,8,1,9,9,1,0,10,4,10,10,9,0,0,8,4,9,9,8,4,10,3,10,9,0,0,8,8,10,9,1,1,1,9,9,10,0,6,9,8,1,8,9,0,0,8,8,10,9,1,1,1,9,9,10,0,4,9,8,1,8,9,8,0,10,4,10,9,9,0,0,9,1,9,9,2,5,6,0,7,9,0,0,9,6,4,5,9,0,0,1,5,6,0,5,3,5,0,6,9,0,0,10,7,2,10,9,9,8,9,1,9,0,7,4,1,1,9,9,0,0,10,7,2,10,9,9,8,9,1,9,0,3,4,1,1,9,9,0,0,9,7,10,9,7,6,7,8,1,9,0,8,7,2,7,9,1,1,0,9,7,10,9,3,0,0,8,9,9,1,8,2,2,0,9,9,6,0,10,1,10,3,3,1,1,2,9,9,2,1,2,10,2,9,9,6,0,10,1,10,3,7,0,0,2,9,9,6,1,2,10,0,9,9,0,0,7,6,10,9,9,9,9,10,1,10,0,8,4,2,1,9,9,0,0,7,6,10,9,9,9,9,10,1,10,0,1,2,2,1,9,9,7,0,10,4,10,10,9,0,0,8,4,9,9,2,4,10,3,10,9,0,0,2,8,10,9,9,0,0,9,9,10,0,4,9,8,0,2,9,0,9,10,8,10,3,3,0,0,8,1,9,0,9,1,2,0,10,9,0,9,10,8,10,3,3,0,0,8,1,9,0,1,7,2,0,10,9,8,0,10,4,10,9,9,0,0,9,1,9,9,7,4,6,0,7,9,8,0,10,4,10,9,9,0,0,9,1,9,9,2,4,4,0,7,9,0,9,10,8,10,7,3,0,0,8,1,9,0,9,2,8,0,10,9,0,9,10,8,10,7,7,2,2,8,9,9,0,9,2,8,7,10,9,0,0,7,6,10,9,9,9,9,10,1,10,0,8,2,2,8,9,1,1,0,9,7,10,9,7,2,7,8,9,9,1,8,7,8,7,9,9,0,0,9,4,6,5,9,0,0,9,5,4,0,5,3,5,0,6,9,0,0,8,8,10,9,9,0,0,9,9,10,0,6,1,2,0,2,9,7,0,10,4,10,10,9,0,0,2,6,9,9,2,6,10,7,10,9,0,0,7,6,10,9,9,9,9,10,9,10,0,1,2,8,8,9,9,6,0,10,9,10,7,7,0,0,2,9,9,2,1,2,10,0,9,9,6,0,10,9,10,7,7,0,0,2,9,9,2,1,2,10,0,9,9,1,0,10,6,10,9,9,0,0,9,9,9,9,7,4,4,0,7,9,0,0,10,7,8,10,9,9,8,9,9,9,0,3,4,9,1,9,1,0,0,10,9,10,7,7,0,0,8,9,9,0,9,8,10,0,9,9,8,0,10,6,10,1,9,0,0,9,9,1,9,2,4,6,0,7,9,0,9,10,8,10,7,7,5,6,8,1,9,0,9,7,8,7,10,9,1,0,10,4,10,9,9,0,0,9,9,9,9,7,4,6,0,7,9,0,0,9,6,6,5,9,0,0,9,5,6,0,5,4,5,0,6,9,7,0,10,4,10,10,9,0,0,8,6,9,9,8,1,10,7,10,9,0,0,7,4,10,9,9,9,9,10,9,10,0,1,4,8,8,9,9,6,0,10,9,10,7,1,0,0,8,9,9,6,9,2,10,1,9,9,0,0,7,4,10,9,9,9,9,10,9,10,0,8,4,2,8,9,9,0,0,9,7,10,9,7,6,7,8,9,9,0,8,2,2,7,9,9,0,0,10,7,8,10,9,9,8,9,1,9,0,3,4,9,8,9,9,0,0,10,7,8,10,9,9,2,9,9,9,0,7,1,9,8,9,9,8,0,10,4,10,9,9,0,0,9,1,9,9,1,4,4,0,3,9,0,0,10,7,8,10,9,9,8,9,1,9,0,7,4,9,8,9,9,7,0,10,4,10,10,9,0,0,8,6,9,9,8,4,10,3,10,1,0,0,10,9,10,7,7,0,0,8,1,9,0,1,2,10,0,9,9,8,0,10,4,10,9,9,0,0,9,9,9,9,2,4,6,0,7,9,0,0,1,7,10,9,7,2,7,8,9,9,0,2,2,8,7,9,9,7,0,10,4,10,10,9,0,0,8,4,9,9,8,4,10,7,10,9,0,0,10,7,8,10,9,9,8,9,9,9,0,3,5,1,8,9,9,4,0,10,9,10,3,7,0,0,8,9,1,2,9,8,10,0,9,9,6,0,10,9,10,7,7,0,0,2,9,9,6,9,8,10,0,9,9,0,0,10,3,2,10,9,9,8,1,1,9,0,1,5,9,1,9,9,0,0,9,6,6,5,9,0,0,9,5,6,0,1,4,5,0,6,1,1,0,1,6,6,5,9,0,0,9,5,4,1,5,3,5,0,6,9,0,9,10,8,10,3,7,0,0,8,9,9,0,9,7,8,7,10,9,1,0,10,4,10,10,9,0,0,8,6,9,9,8,6,10,7,10,9,0,0,9,6,6,5,9,0,0,9,5,6,0,5,4,5,0,6,9,4,0,10,9,10,7,7,0,0,8,9,9,6,9,2,10,0,9,9,8,0,10,4,10,9,9,0,0,9,9,9,9,7,5,4,0,3,9,0,0,9,7,10,1,7,0,0,2,9,9,0,2,7,8,7,9,9,6,0,10,9,10,3,3,2,3,8,9,9,6,9,8,10,1,9,9,0,0,9,3,10,9,7,2,7,8,9,9,0,2,7,8,1,9,9,0,0,9,6,4,5,9,0,0,1,5,6,0,5,3,5,0,4,9,0,0,9,7,10,9,3,0,0,8,9,9,0,8,7,2,0,9,1,0,0,10,9,10,7,3,0,0,2,9,9,0,9,2,10,2,9,9,8,0,10,6,10,9,9,0,0,9,1,9,9,7,4,6,0,7,9,0,9,10,8,10,3,3,0,0,2,9,9,0,9,7,8,0,10,9,7,0,10,4,10,10,9,0,0,2,6,9,9,8,6,10,7,10,9,6,0,10,9,10,3,3,2,3,8,9,9,6,9,8,10,1,9,9,1,0,10,6,10,1,9,0,0,1,9,1,9,2,4,4,0,3,9,0,0,1,7,10,9,7,2,7,8,9,9,0,8,2,8,1,9,9,6,0,10,9,10,7,3,0,0,8,9,9,2,9,8,10,2,9,9,0,0,9,6,4,5,1,1,1,9,5,6,0,5,3,5,1,6,1,1,0,3,6,10,1,9,9,9,10,9,10,1,8,4,8,8,9,9,0,0,10,3,8,10,9,9,8,1,9,9,0,7,4,9,1,9,1,0,1,10,9,10,3,7,0,0,8,9,1,0,9,2,10,0,9,1,1,0,7,4,10,9,9,1,9,10,1,10,1,1,2,8,8,9,1,0,1,10,6,10,10,9,0,0,8,6,9,0,8,4,10,3,10,1,0,1,10,4,10,9,9,0,0,9,9,9,0,7,5,4,0,7,9,0,9,10,8,10,3,3,0,0,8,9,9,0,9,7,2,0,10,9,0,0,7,4,10,9,9,9,9,10,9,10,0,8,4,8,1,9,1,1,0,10,3,8,10,9,9,8,9,9,9,1,7,5,9,1,9,9,2,0,10,6,10,10,9,0,0,2,6,9,9,8,6,10,3,10,9,0,0,9,7,10,9,7,2,7,8,9,9,0,8,2,8,1,9,9,0,9,10,2,10,7,7,5,6,8,9,9,0,9,7,8,1,10,9,0,0,10,3,2,10,9,9,8,9,1,9,0,3,4,1,8,9,9,0,9,10,8,10,3,7,0,0,8,9,9,0,1,7,2,7,10,9,8,0,10,6,10,9,9,0,0,9,9,9,9,2,4,6,0,7,1,0,1,7,4,10,1,1,0,0,10,9,10,0,1,4,8,0,9,9,6,0,10,9,10,3,3,2,3,8,1,9,6,9,8,10,2,9,9,0,0,9,3,10,9,7,1,7,8,9,9,0,2,7,8,1,9,9,0,0,10,3,2,10,9,9,8,9,9,9,0,7,5,1,8,9,9,7,0,10,4,10,10,9,0,0,8,4,9,9,8,4,10,3,10,9,0,0,10,3,2,10,9,9,2,1,9,9,0,7,4,9,1,9,1,1,0,10,2,10,7,1,2,6,8,9,9,1,9,2,8,1,10,1,0,0,10,9,10,7,7,0,0,8,1,1,0,9,1,10,0,9,9,2,0,10,6,10,10,1,0,0,2,4,9,9,8,6,10,0,10,9,8,0,10,8,10,9,10,0,0,8,8,8,9,1,8,10,0,10,9,0,0,2,2,10,9,9,0,0,9,9,10,0,6,9,2,0,2};

	int one_letter_size=params_size+1;

	for (int i=0;(one_letter_size*i)<templates_string.size();i++) {
		string params(templates_string.begin()+(i*one_letter_size), templates_string.begin()+(i*one_letter_size)+params_size);
		char number=templates_string[(i*one_letter_size)+params_size];
		vector<int>weight(params_size);
		for (int j=0; j<params_size; j++)
			weight[j]=templates_weight[(params_size*i)+j];

		dictionary_elem t(params,weight,number);
		dictionary.push_back(t);
	}
}

char find_in_dictionary(string params, bool nonzero=false) {
	int d, min_d=999;
	char min_num;
	for (int i=0; i<dictionary.size(); i++) {
		if (nonzero&&(dictionary[i].number=='0')) continue;
		d=0;
		for (int j=0; j<params.size(); j++) {
			int a=params[j], b=dictionary[i].params[j];
			if ((a==b)||(a=='9')||(b=='9')) continue;
			if (a<b) swap(a,b);
			if ((a-b)>=2) d+=(2*dictionary[i].weight[j]);
			else d+=(dictionary[i].weight[j]);
			if (d>min_d) break;
		}
		if (d<min_d) {
			min_d=d;
			min_num=dictionary[i].number;
			if (min_d==0) return min_num;
		}
	}
	return min_num;
}

//PROCESS ONE SAMPLE===========================================

bool load_from_file(int i) {
	string name="000";
	name[0]=(char)(i/100+'0');
	name[1]=(char)((i%100)/10+'0');
	name[2]=(char)(i%10+'0');
	name="C:/nastya/ya/samples/"+name;

	ifstream in(name.data());
	if (!in) return false;
	string a;
	s.clear();
	while(!in.eof()) {
		if(in>>a)
			s.push_back(a);
	}
	return true;
}

void process(int sample=-1) {


	string a;
	while(!cin.eof()) 
		if(cin>>a)
			s.push_back(a);
//	load_from_file(167);

	divide();

	string params;
	char r;		

	if (filled1) {
		s=s1;
		params=generate_params();			
		r=find_in_dictionary(params, (filled2||filled3));
		res.push_back(r);
	}

	if (filled2) {	
		s=s2;
		params=generate_params();
		r=find_in_dictionary(params,(!filled1)&&filled3);
		res.push_back(r);
	}

	if (filled3) {
		s=s3;		
		params=generate_params();		
		r=find_in_dictionary(params, !(filled1||filled2));
		res.push_back(r);
	}
	cout<<res;
}

//===========================================

int main() {
	import_letters();
	process();
	}