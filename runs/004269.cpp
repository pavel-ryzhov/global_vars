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
			//-----------------
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

void set_label(int i, int j, bool eight_points=false){
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

void copy_labeled_items(vector<string> &sn, int label) {
	for(int i=0; i<s.size(); i++) 
		for (int j=0; j<s[0].size(); j++)
			if(array_of_labels[i][j]==label) {
				sn[i][j]=s[i][j];
				s[i][j]='.';
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
			weight[i]=max_weight+100;
	else if (minnum>=(2*t))
		for (int i=minnum+1; i<weight.size(); i++) weight[i]=max_weight+100;

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
	if (res[0]>res[1]) swap(res[0],res[1]);
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
	const int max_weight=35;

	init_s123();
	int w=s[0].size(), h=s.size(), count;
	vector<int> weight(w-1, 0);

	for (int j=1; j<w; j++) {
		count=0;
		for (int i=0; i<h; i++) {
			if (count>max_weight) break;
			char a=s[i][j-1], b=s[i][j];
			if ((a=='@')&&(b=='@')) {
				weight[j-1]=max_weight+100;
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

/*
1. Выделяем дырки. Не считаем дырки единичной площади, их закрашиваем.

2. Обрабатываем дырки: 
а) удаляем гор/верт. полоски маленькой длины  по очереди до тех пор, пока удаляются - внутри дырок!

3. Делаем левую-правую заливку копии.
Выделяем связные (белые) области.
Если площадь равна 1 - закрашиваем на оригинале.
Смотрим, сколько осталось белых областей, возвращаем их число.
*/

bool remove_short_horizontal_lines () {
	const double hole_min_w=3.0/30;
	const double narrow=1.57;
	int w=array_of_labels[0].size(),h=array_of_labels.size();
	if (w<=11) return false;

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
	if (w<=11) return false;

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
const string templates_string="129000009902011119101290000099022112191009902000992029201901099002112102091122120990002099020911291309902020990209212913109020009920012219141190200099200112191409902011000209102215099020110002091122151190200199020011121611902001990200111116099200109902091019072900001099020911291829000010990209122918119020109902021129191190201099022212291912900000990201121910099000009920292019010990021121020921221209900021200209112013099000209902092229131090201201200122121409900011000209102215099220110002091122151190000199020012121609920010990209001907290000111102091120182900001111020912201811900010990202122919129000009922011219101090001099200221190109902010992029211901109022112102021022121090021120020211211210900011100202212013290000211002092220131090201099200122191410902011012001221014099000110002091112151090002110000221211529002001992209111116299020019902091110160992001099020920190710922010990202201907290000111100091220182900000099000912191811902010990202101909119020109902021029191190200099220111191012902000992201121910099020009922292019010990221121020921221209902211210209222212099020212022092120130990201099220922291309922001990209122215290020019922091110161090200199200012111609920010992209201907290020111122091120182900200099222912291829002010992209112919109020109922022129191290000099022111191009900020990209212913099000212002292120131190200099200122191409900011000209112215119020019900201111162900000099020911291829000011210209111018119000109902221129191290000099000111191009900210992209122911099002109920092129110990221120020912221209900021200209212013119020009920022119140990001100020920221511900001990200021216119000019900001212160990201099020910190729000011200209112018119000109902022019191190001099020221291909900210992009112911099002111002091122120990021120020911221209900021100209112013119020111120012210141190201111200122111409900011000009112215119000019902001112162900001100020911201811900010990202112919099002112002092221120990002120020920201309900021200209221113119020109920022219140992001100020910221509920011000209112215290000111102091121181190001099020210291912900000990001121910099002109922091129110990021100220912121109900211000209112212119002111102021022122900002100020921201310902021000202212113109020112120012210141090201121200222100409900011000209121215099000110002091211151190200199020012121609902010990209201907099020109900091019072900001110020912201829000011010209122118119020109902021229191290000099220111191012900000992221121910099002009922091129110990220099222921191110902211210202202112109020412022002220132900202099222921291310902000992020221914109220110002001222150992201100020912221529002001992209121216099020019922091211160990000099000902191709900000990009222917290000009902091229181190201099222211291912900000992201011910129000009920010119100990200099222921190109900200992029211911099002111102092222120990021111020921221209900021202209212013109020009920002219140990001100020922121509900001990209221215119020019922000111161190200199200001111609920010992209211907099200109922092129172900201099020911291829002011000209111018119020109922022119191190201099220221190909900010990209111910119000009900011119100990200099022920190109900011200209111112099002112000092122120990202120020920100309902021200209202003099020019900092210141090200099000222191409900011000209101105119020019900001211160990000199000912111609902010990009102917290000110002091110182900001100020911211809900010990009202919099000009900090019100990000099000911191009902000992209201901099020109922292019010990201121020910120209900211210209102212099020211002091012030992002110020921120309902001990009101014109020019900021210140990201100020900221509902011000009102215109020019900001212162900200099020912191829900001990009121018109020109902021019092900201099020920190910902000992001121910099020110122091222110990021101220912211109902011100209112012099020209922092229130990202120220922201309902011000209122115109020019920000210160990201099000920190729002001992209112018290020111122091110181090201099020220190911902000990201111910119020009920011119100990200099202921190109902211210209222012099022112100091220120990202120020911201309902021200209122013099020110002091121150992201100020911211510902001990000021016099020109922091019072900200099220912291810902000990202111919290020009902090119101190200099000111191029902000992229201901109022112102021122122900201121020912221209902021100209201013099020211002092121130990200099000912191409902011000209121215099000019900091212161090202099020020190729002000992009122918119020009902222029091190200099222220190929200000990209111910292000009902092219101290020099220112291109900200992229121911099002112002092022122900021099022922291229000021102229212013109020111120012210142920001111202922101410900011000202101215109000110002021022152920200199020901121629200001990209021216129200109902011019072902001099020920291729900011100209222018292000109902092129191290000099000110191009900010990009101911099000109900091029110990201101000922121209900021100209201013099000210002092010131090201100000122101410902001990001021014099000110002091010150990001100020920101509902010990209001907099200109902091029172900001110020900101829000011200209002018109000112102021010091090000199000210110909900210992009122911099002112102091222120990002120220922201309900011000209122215119020019900001212161190000199000002121629000011012209122018119000109902021019091190201099020221191909902211210209112212099020212002092120130990002120020921211311902002992001221214290020111102091120182900001120020912201809900021100209212013290000111002091120181190001099020220190909920000992229211901099000209902092029130990001100020921121511900001990000121116290000110102091120180990022099220911291109900210992009222911099220110002091022152900200199020911201811902011112002221014119020111120212210142900001111020911101809900210992009022911099002112102092222120990002120020922201311902001990200011116119020019902000112162900001120000911201811902010990202212919119020009920022219140990001100020910121511900001990000021116119020109902021019191190001099020211191912902000992201111910129020009922211119100990202099220911291329000020992229112913109020009922012119141090200099220111191411902001992200111116290020009922091129182900200099220911191811902010992202112919099020212002091020131090200099200222191409902211210209122212109020009920012119141190200099200121191429000011010209112118099000209902091229131290000099002111191009902211210209102212290000110000091120180990021099220921291109900211012209112211099000210002091221131190201111200222111429000011002209122018109020009920022119142900200099022912191811902010990202111909119020109902021119190990021110020921221209900021200229221013119020109920012219142900001111020912211809902021202209112013109020009920212219142900201110220911201829000001990209111018119020109900022119191290000099222111191009900200992209211901099000209922092129132900000099222911291811902000992221111910099002009922091229110990220099222912191109902211210209112012109022112102001220120992202110220911201309922021102229122013109020009922212119141090200099222221191409922011000209122115109020019922001110161090200199222012101629002000992229111918109020009922221129191090201099222211291909902210992029212911099000112102092011020990001111020920120209900011100209211013109020111120022211140990001100020910211509900011000209202015129000019900001111160992001121020910110709920011210209201207119000109900022129190990001099000920191109900011210009121012099000112100092210120990002120000921101310900020990200201913109000110000021110141090001099000111191409900011000009111115099000110000092211151190000199000001111609900010990209201917290000009900091019182900000099000901191811900010990002102919119000109900022019192900001099000912291829000011000209122018099000110000091212151190002110020221201309902200992229112911099200109902091129171190000199220002121609900011000209222215109020009900020119141090200099000211191410902010990202101919099002112102092220120990200099200922191411902000990222202919290000111100091120181290001099020210291909900210992209222911119000019902001012160990201100020921221510902002992001211214099020110002091112150990002120020922101309900211210009222212099002112002091022121190001099000200190909900211210009122212119000019902001111160990200099220911191411900010990202202919099200211002091020131190000199000011121609900211210209211212119020109920222219141090200099000122191409902011212009012112099002109922090229111292020099222121191129000001990209112018129000019902001212160990020099200912191111900010990202111909099000019922091120131090201111200122111409902021100209112213099000009900092019010990002099020921191309902001990009211014119020109900021029192900000099220911291811900001992200121216109020111120012212141090200099222220190909920021100209202113109020019920022210140990001100220911221110920021000200112215099022112122091221121090201099202222191411902011100000022215290020019902091111162900001099020911191929000000990209111918099020110002091120151190221121020211211210902001992200121116099000211002092021132900201111020911211809902011210009221212290000019902092110181190201099020220291929002000990209212915109020111122012210140990202100020911211309902011210209111212119000019900001111160990201120220912211211902012010200122218099020009922292019141090200099200012191612900000990201211910099020109902091029170990001099020910291909900011000209201215109020109900012119142900001110000911201809902211212209212012099022112122092020121190201099000212291909900020990229202913099000109902091019170990021110000921221229002011112209122018";
const string templates_weight="870979890077788790987097989007718819098008334800843042303800967988788806487880086981007880167088008298100788076708850989660078858790883098966007885179088006398888989074778800639888898907377886095998007588739698609599800758873929800779880088905870680897962007780867098089796200778081709870959880088887450687095988008818715068709798900777881909800853480084304230380096798878880248788008698756788016768800869810078807170885098921127885879188006598888989074778800239888898907377886093998007588759698007798800889018706808979664477808676980897966447780817698709398800888871506870979890017788190911085348008451423038008334800843042303110927988788816187811096798818881648181108691716788176768101869871678807176885098926007885879088509892212788587918800659888898907317811065918189191137181019599800158073929100959980075807391980077988008890387061107198800889138706808979664471808176980897922007180811098709598800888873302870959880088887350681091989001778879098709198900177881909800833480084304230380092798878880248788009279887888023878800829875618807676880082911001880717088002391800989071778101959980015807391981095998001388759298007798800189038706808919664417808676980891922001710817091019598800188074506810959880018881450687097989007718879098008698100788076708800869875678107676883098966007885879088006598888989073778860959980073187392980897922007780867098089796614778086169870939880088187450687097989007178879098008554800845043505800855480084504250580092798818880638788008698756788076768830989660078828190880065988889890147788609399800758815969860939980073887596980011988008890587068089796611778086769870939880088881330687093988008888145068008554800845042505800967981188806487880096798818880648788008698716788016768830989221278858791883098922127885879188006598888919073778860939980075887396980897966117780867698709398800888874506800967988188802381880086987567880717688008698756788071118830989260078828790880025988889890747788002598888989073778808979664477808671987093988008888735068709798900717881909800855480084504250580085541118450433158009679811888064878110967981788816187810186987167880767681108298716788176718850989221278858791885098922127882879118006598888989071178800659888898907111886095998007588759698001198800889038706800119880081905870680897966417780817698089796614778081719870959880088887150687097989001778879098709798900171881909800855480084504250580083548008430423051109279887888121818110829175618817176810182981001810767088509896600781187908110239888898917177880023988889890717781019599800158075969100959980015807592980017918008190117028001791800819031102808979220077808170987095988001818745068709798900177817909870979890011781790980083348008430423038008554800843042305800967981788802387880096798178880248788008698756188076768850989660078818790880065988889890111788006591800989011178860959980015881392986095998001388139298007798800189031706800779880018903110280891962007780867098089196611778086169870959880018881430687095988001888143021009791900777087909810979890071788790980083348001430423038009619881888064118800967988181802487880082987567880711618008298756788071761100989620018808791885098966001882879088006598888989074111860959980073887592910093998007380759298001198800819058102808979661177808616980897966117780867191009398800818013506100979890071701190910097989007170879098008334800845042303800833480084304230380092198878880611718009679887888061878800829871678801111180016987167880761111009896200188011918850989620018821791880063988889890147788006398888919074778810959980073887596980891922007780811098009792600718081169810959880088887330210195988008880133028109198900117881909800833411184504351580085541118450435158009219811888064818800829810018807170880082987561880717688006398888989071718810959980013881591980011988008190387068089192600178086769808919664417808616981095988008888133028109198900777887909810919890011788790980083348008430423038009279887888023818800927988781806381880082987567880167688008298756788011768800639888898907371880023988889890737188109599800738815919800119880018905870680891922001780817098109591800888874306101919890077701790981091989007178879091008334800843042303110927988788816487810192198878880638788008298716788071168800829871678807671810098966001880179088006398888989071178100939980073807596911011918008891387068089192200118081709870959180088181350287095918001818133021019798900777087909101979890077701190911085548008451435058008554800843043305800967988188802187810196791008810238081018698716181076768850989221278858791810191922127810879181106598888989174178110659888898917477810195998007580139691019399800758015969110779880088915870610177988008890381028009796641778011769101939880088801450687097989007178819098008534800145042305800853480014504250580092198178180231788008698716788071168800869871678807116885098922111885879188509896200188517918800659888898907411880065988889890141188001198800889018706800779880088905810280897966417780111698089796611778011769810939811188887331281093911008188733128008554800845043505800967988788806387880086987561880717688006598888989071778860959980073887596986093998007388159698089796614178081769870939880088887330287095988008888143068009279887888064878800829875678807676880086987567880767188309896100788587918808919664477808676980897966117780817698008698716788076768808979664177808676987093988008888133028001534800843042303800869810078807170880065988889890131788609399800738875929808979661477808676980085518008450425058008554800845043505800239888898907477880891926007780867698309892212788287918830989221278158791880897966447780861698008554800845013505800967988788802387880086987567880717688609599800758813929860959980075881396980897966117180867698709598800888814506830989660078828790880065988889890741788609399800738815929870959880088887330687093988008888743068709198900177887909870919890017188790980082981001880167081018698100181016708850989660071858190885098966007185119088609599800158873929808919220017808670980891922001780861098709598800188874506800829875678801176885098966007882879088009279887888063878850989660078858190883098966007885819088089796614778086719800869810078801170887097989007118879098009279887888061878808979661171808676980085548008450425058008554111845042515800869871678801171883098922127882879188089796611178081769850989660078828190880891922007710811098709598800888874302870959880088887430680096798118880248788008698756781071168830989260078858790880897966447780817198008298756188016768850989660078158790880891966411780867698089792600778086169870959880081881430687097989001718879098008554800845042303800869810018807670880897922001710867098109198900171887909800855480084504350580083548008430433058009279887888064818110927988788816381880012987161880167688001298716181011768850989660071158190885098966007112819088002398888989071718810959980015887391981095998001518759198089192200171086109810959180018187450681095988001818745068008354800843042505800961988788802111180096198178880211718008691716788076168850989221278828791880065988889890747188006598888989014718810939980073887392980077981118890587168007798111889038716870939880081881450680085348001450423058009619887818063118800961988781802311880086987567180761681108698100788171108850919221118821191885091926001885119088006598888919073118800659888891901111886093998007388139298001798800889038702808979220071808110980897922007180161098709398800818873506870939880081881330680897962007180817098089796611778081769800659888891907117811086987167881767688008354800843042505800779880088905110286093998001588159698006598888989011778850989660018821190885098966001882119088109598800888873306800967988788802381810098966007880879088709591800881813506808979664471808676981093988008888735068008554800845043505860939980075887196980063988889890137788509896100788581918800639888898907317880086987567880711688009679887818023878800967988188806187887093988008188133028009679887818063878860939980075887392910098966007180119088709398800888813506800169871678801176886093998007388739698009679887888024178830989260078128790885098966001885879088009219887118014818800855480084501350511015548008431423058089792600778086769810939980075887596980085548008450433058709398800888874302800869170018801676885098922127885879188008298716788016718800853480014504230380086981007880761081009896200188081918870959880081887350680897922001780867098609399800158875969850989221278858791881095918001818133028001698716788071718850989620078828791880085341118450425151102591888989173778800927988718806381885098926007812879081106398818919111778101959980075807392910193988008880743068089792200778086109800639888898907371811092798878881648188109599800158875929800869871678807171880891966447780867198009219887818023178808979260077801616987095988008888135061016391100989013708850989221271858791880082987167880167188009219887888064178860939980073887392980092198811880638181109196114778181719100989660071108190881095991001388759098709798900777817909800119880088905810210093988008880735068006598888989014178850989260018858190880897966417180867698009279887188024818800927988718802181887095988008188715068008698100781071708800179880088905870280096798118180248788089196644178081769";
	int one_letter_size=params_size+1;
	for (int i=0;(one_letter_size*i)<templates_string.size();i++) {
		string params(templates_string.begin()+(i*one_letter_size), templates_string.begin()+(i*one_letter_size)+params_size);
		char number=templates_string[(i*one_letter_size)+params_size];
		vector<int>weight(params_size);
		for (int j=0; j<params_size; j++)
			weight[j]=(templates_weight[(params_size*i)+j]-'0');
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
	//load_from_file(217);
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

int main() {
	import_letters();
	process();
//	system("pause");
}
