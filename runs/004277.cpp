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
	
	if (s[h-1][0]=='@') place=102;
	else {
		int i=h-2;
		while (s[i][0]!='@') i--;
		if (i>h/2) place=101;
		else place=100;
	}	
	
	
	int i=h-1;
	
	while (!black_px(i)) i--; //1 т.касания всегда есть
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
const string templates_string="129000009902011119101290000099022112191009902000992029201901099002112102091122220990002099020911291309902020990209212913109020009920012219141190200099200112191409902011000209102215099020110002091122151190200199020011121611902001990200111116099200109902091019072900001099020911291829000010990209122918119020109902021129091190201099022212291912900000990201121910099000009920292019010990021121020921222209900021200209112013099000209902092229131090201201200122121409900011000209102215099220110002091122151190000199020012120609920010990209001907290000111102091120182900001111020912201811900010990202122909129000009922011219101090001099200221190109902010992029211901109022112102021022221090021120020211211210900011100202212013290000211002092220131090201099200122191410902011012001221014099000110002091112151090002110000221211529002001992209111116299020019902091110160992001099020920190710922010990202201907290000111100091220182900000099000912191811902010990202101909119020109902021029091190200099220111191012902000992201121910099020009922292019010990221121020921222209902211210209222222099020212022092120130990201099220922291309922001990209122215290020019922091110161090200199200012111609920010992209201907290020111122091120182900200099222912291829002010992209112909109020109922022129091290000099022111191009900020990209212913099000212002292120131190200099200122191409900011000209112215119020019900201111162900000099020911291829000011210209111018119000109902221129091290000099000111191009900210992209122921099002109920092129210990221120020912221209900021200209212013119020009920022119140990001100020920221511900001990200021216119000019900001212160990201099020910190729000011200209112018119000109902022019091190001099020221290909900210992009112901099002109920091129210990021110020911222209900211200209112222099000211002091120131190201111200122101411902011112001221114099000110000091122151190000199020011121629000011000209112018119000109902021129090990021120020922212209900021200209202023099000212002092211231190201099200222191409920011000209102225099200110002091122252900001111020911211811900010990202102909119000109902021129291290000099000112191009900210992209112921099002110022091212210990021100020911222211900211110202102222290000210002092120131090202100020221211310902011212001221014109020112120022210040990001100020912121509900011000209121115119020019902001212160990201099020920190709902010990009101907290000111002091220182900001101020912211811900010990202112919119020109902021229291290000099220111191012900000992221121910099002009922091129210990220099222921192110902211210202202122109020412022002220132900202099222921291310902000992020221914109220110002001222150992201100020912221529002001992209121216099020019922091211160990000099000902191709900000990009222907290000009902091229182900201099220911291911902010992222112919129000009922010119101290000099200101191009902000992229211901099002009920292119010990021111020922222209900211110209212202099000212022092120131090200099200022191409900011000209221215099000019902092212151190200199220001111611902001992000011116099200109922092119070992001099220921290729002010990209112918290020110002091110181190201099220221190909900010990209111910119000009900011119100990200099022920190109900011200209111112099002112000092122220990202120020920100309902021200209202003099020019900092210141090200099000222191409900011000209101105119020019900001211160990000199000912111609902010990009102907290000110002091110182900001100020911212809900010990009202909099000009900090019100990000099000911190009902000992209201901099020109922292019010990201121020910120209900211210209102222099020211002091012030992002110020921120309902001990009101014109020019900021210140990201100020900221509902011000009102205109020019900001212162900200099020912191829900001990009121018109020109902021019092900201099020920190910902000992001121910099020110122091222110990021101220912212109902011100209112012099020209922092229130990202120220922201309902011000209122125109020019920000210160990201099000920190729002001992209112018290020111122091110181090201099020220190911902000990201111910119020009920011119100990200099202921190109902211210209222012099022112100091220220990202120020911202309902021200209122023099020110002091121150992201100020911212510902001990000021016099020109922091019072900200099220912291810902000990202111909290020009902090119101190200099000111191029902000992229201901109022112102021122122900201121020912221209902021100209201013099020211002092121230990200099000912191409902011000209121215099000019900091212161090202099020020190729002000992009122918119020009902222029091190200099222220190929200000990209111910292000009902092219101290020099220112292109900200992229121921099002112002092022222900021099022922292229000021102229212013109020111120012210142920001111202922101410900011000202101215109000110002021022252920200199020901121629200001990209021216129200109902011019072902001099020920290729900011100209222018292000109902092129091290000099000110191009900010990009101921099000109900091029210990201101000922122209900021100209201013099000210002092010231090201100000122101410902001990001021014099000110002091010150990001100020920102509902010990209001907099200109902091029072900001110020900101829000011200209002018109000112102021010091090000199000210110909900210992009122901099002109920091229210990021121020912222209900021202209222013099000110002091222151190200199000012121611900001990000021216290000110122091220181190001099020210190911902010990202211909099022112102091122220990202120020921201309900021200209212123119020029920012212141190000199020012121629002011110209112018290000112002091220180990021099200921290109900021100209212013290000111002091120180992000099222921190109900211210209112202099002112102092122020990002099020920291309900011000209211215119000019900001211162900001101020911201809900220992209112911099002109920092229210990221121020911221209922011000209102215290020019902091120181190201111200222101411902011112021221014290000111102091110180990021099200902292109900211210209222222099000212002092220130992001100020910221511902001990200011116119020019902000112162900001120000911201811902010990202212909119020009920022219140990001100020910121511900001990000021116119000109902021119091290200099220111191012902000992221111910099020209922091129132900002099222911291310902000992201211914109020009922011119140992201100020911211511902001992200111116290020009922091129182900200099220911191811902010992202112919099020212002091020231090200099200222191409922011000209122225099022112102091222220990002120020921211310902000992001211914119020009920012119142900001101020911211811900010990202212929099000209902091229131290000099002111191009902211210209102222099220110002091022252900001100000911201809900210992209212901099002110122091122210990002100020912212311902011112002221114290000110022091220180990202120020921202310902000992002211914290020009902291219181190201099020211190909900211100209212222099000212002292210231190201099200122191409900011000209102225290000111102091221181190201099020211292909902021202209112023109020009920212219140992201100020911222529002011102209112018290000019902091110181190201099000221190912900000992221111910099002009922092119010990002099220921291329000000992229112918119020009922211119100990020099220912292109902200992229121921099022112102091120221090221121020012202209922021102209112013099220211022291220131090200099222121191410902000992222211914099220110002091221151090200199220011101610902001992220121016290020009922291119181090200099222211290910902010992222112919099022109920292129010990001121020920110209900011110209201202099000210002092010130990001110020921101310902011112002221114099000110002091021150990001100020920201512900001990000111116099200112102091011070992001121020920120711900010990202111919119000109900022129090990001099000920192109900011210009121022099000112100092210220990002120000921101310900020990200201923109000110000021110141090001099000111191409900011000009111115099000110000092211151190000199000001111611900001990000021126099000109902092019272900000099000910191829000000990009011918119000109900021029291190001099000220192911902010990202122919290000109900091229180992001100020911221509900210992209122901290000110002091220180990001100000912121511900021100202212013099022009922291129210992001099020911290711900001992200021216099000110002092222151090200099000201191410902000990002111914099002112102092220220990200099200922191409902011010009221212099000212002092220232900001111000911201809900021200209202013129000109902021029190990021099220922292111900001990200101216099020110002092122151090200299200121121409902011000209111215099000212002092210130990021121000922222211900010990202122919119020109902021229090990021120020910222211900010990002001909099002112100091222221190000199020011111609900210992209122911119020109902021129190990200099220911191411900010990202202909099200211002091020031190000199000011121609900211210209211222119020109920222219141090200099000122191409902011212009012112099000212002092120231190001099020210292909900011000209112225099002109922090229211292020099222121192129000001990209112018129000019902001212161190200199020011120609900200992009121921099002109922091129010992001099020910292711902010990202102929099002112002091122020990020099220911290109900001992209112003109020111120012211140990202110020911222309900000990009201901099000209902092119130990200199000921101411902010990002102909290000009922091129181190000199220012121610902011112001221214109020009922222019090992002110020920211310902001992002221014099000110022091122011092002100020011221509902211212209122122109020109920222219140990201100020912211511902011100000022215290020019902091111162900001099020911191909900020990209202923290000009902091119180990201100020911201511902211210202112122109020019922001211160990002110020920211329002011110209112118099020112100092212222900000199020921101811902010990202202909290020009902092129151090201111220122101409902021000209112103099020112102091112221190000199000011111609902011202209122122119020120102001222180990200099222920191410902000992000121916099000110002091112251290000099020121191009902010990209102907099000109902091029290990001100020920121510902010990001211914290000111000091120180990221121220921200209902211212209202002119020109900021229190990002099022920291309900010990209101927099002111000092122222900201111220912201809902021202209112013290000009900092119180990001121000921112111900012010200112218099020112102090010070990201121020911222209900220992229122913";
const string templates_weight="870979890077788790887097989007718819088008334800843042404800967988788806487780086882007880167078008288200788076707850989660078858790883098966007885179088006398888989074777800639888898907377786095998007588739588609599800758873928800779880088905870880897962007780867088089796200778081708870959880088887450687095988008818715018709798900777881908800853480084304240480096798878880248778008688656788016767800868820078807170785098921127885879188006598888989074777800239888898907377786093998007588759518007798800889018708808979664477808676880897966447780817688709398800888871506870979890017788190811085348008451424048008334800843042404110927988788816187711096798818881648111108681616788176767101868861678807176785098926007885879088509892212788587918800659888898907317711065918189191137171019599800158073928100959980075807391880077988008890387081107198800889138708808979664471808176880897922007180811088709598800888873306870959880088887350681091989001778879088709198900177881908800833480084304240480092798878880248778009279887888023877800828865618807676780082812001880717078002391800989071777101959980015807391881095998001388759288007798800189038708808919664417808676880891922001710817081019598800188074506810959880018881450687097989007718879088008688200788076707800868865678107676783098966007885879088006598888989073777860959980073187392880897922007780867088089796614778086168870939880088187450687097989007178879088008554800845043404800855480084504240480092798818880638718008688656788076767830989660078828190880065988889890147778609399800758815958860939980073887595880011988008890587088089796611778086768870939880088881330687093988008888145068008554800845042404800855480084504240480096798118880648778009679881888064877800868861678801676783098922127885879188309892212788587918800659888891907377786093998007588739588089796611778086768870939880088887450680096798818880238178008688656788071761800868865678807111183098926007882879088002598888989074771800259888898907377180897966447780867188709398800888873506870939880088887450187097989007178819088008554800845042404800855411184504341480096798118880648771109679817888161877101868861678807676711082886167881767178509892212788587918850989221278828791180065988889890711778006598888989071117860959980075887595880011988008890387088001198800819058708808979664177808176880897966147780817188709398800888874501870959880088887150187097989001778879088709798900171881908800855480084504240480083548008430424041109279887888121817110828165618817176710182882001810767078509896600781187908110239888898917177780023988889890717771019599800158075958100959980015807592880017918008190117018001791800819031108808979220077808170810195988001880745018709598800181874501870979890017781790887097989001178179088008334800843042404800855480084304240480096798178880238778009679817888024871800868865618807676785098966007881879088006598888989011177800659180098901117786095998001588139288609599800138813928800779880018903170880077988001890311088089196200778086708808919661177808616887095988001888143061009791900777087908810979890071788790880083348001430424048009619881888064111800967988181802487780082886567880711618008288656788071761100989620018808791885098966001882879088006598888989074111860959980073887592810093998007380759288001198800819058108808979661177808616880897966117780867111009398800818013506100979890071701190810097989007170879018008334800845042404800833480084304240480092198878880611718009679887888061877800828861678801111180016886167880761111009896200188011918850989620018821791880063988889890147778006398888919074771810959980073887595880891922007780811088009792600718081168810959880088887330610195988008880133068109198900117881908800833411184504341180085541118450434148009219811888064811800828820018807170780082886561880717678006398888989071711810959980013881591880011988008190387088089192600178086768808919664417808616881095988008888133068109198900777887908810919890011788790880083348008430424048009279887888023811800927988781806381780082886567880167618008288656788011761800639888898907371780023988889890737118109599800738815918800119880018905870880891922001780817088109591800888874306101919890077701790881091989007178879081008334800843042404110927988788816487110192198878880638718008288616788071167800828861678807671110098966001880179088006398888989071177100939980073807595811011918008891387088089192200118081708870959180088181350687095918001818133061019798900777087908101979890077701190811085548008451434048008554800843043404800967988188802187710196791008810238071018688616181076767850989221278858791810191922127810879181106598888989174177110659888898917477110195998007580139581019399800758015958110779880088915870810177988008890381088009796641778011768101939880088801450687097989007178819088008534800145042404800853480014504240480092198178180231778008688616788071167800868861678807116185098922111885879188509896200188517918800659888898907411780065988889890141118001198800889018708800779880088905810880897966417780111688089796611778011768810939811188887331681093911008188733168008554800845043404800855480084504340480096798878880638778008688656188071767800659888898907177786095998007388759588609399800738815958808979661417808176887093988008888733068709598800888814306800927988788806487780082886567880767678008688656788076711830989610078858791886093998007588759588089196644778086768808979661177808176880085548008450424048008688616788076767808979664177808676880015348008430424048009679887888064871800967988788802487180086882007880717078006598888989013177860939980073887592880897966147780867688008551800845042401800855480084504340480092798878880648718002398888989074777808919260077808676883098922127882879188309892212781587918808979664477808616880085548008450134048009679887888023877800868865678807176780025988889890747778609599800758813928860959980075881395880897966117180867688709598800888814506830989660078828790880065988889890741778609399800738815928870939880088887430687091989001778879088709198900171887908800828820018801670710186882001810167078509896600718581908850989660071851190880023988889890737178609599800158873928808919220017808670880891922001780861088709598800188874501800828865678801176185098966007882879088002398888989071771800927988788806387780086886567880767178509896600788581908830989660078858190880897966147780867188709398800888814501800868820078801170787097989007118879088009279887888061877800239888898907477180897966117180867688008554800845042404800855411184504241480086886167880117118309892212788287918808979661117808176880082886567880767618509896600788281908808919220077108110887095988008888743068009679811888024877800868865678107116183098926007885879088006598888989074771808979664477808171887095988008888745018008288656188016761850989660078158790880023988889890737718089196641178086768808979260077808616887095988008188143068709798900171887908800855480084504240480086882001880767078089792200171086708810919890017188790880085548008450434048008354800843043404800927988788806481711092798878881638178001288616188016767800128861618101176785098966007115819088509896600711281908800239888898907171781095998001588739188109599800151875918808919220017108610881095918001818745068109598800181874501800835480084304240480096198878880211118009619817888021171800868861678807116780086816167880761678509892212788287918800659888898907471780065988889890147178109399800738873928800779811188905871880077981118890387188709398800888874301870939880081881450680085348001450424048009619887818063117800961988781802311780086886567180761671108688200788171101850919221118821191885091926001885119088006598888919073117800659888891901111786093998007388139288609399800738815921800179880088903870180897922007180811088089792200718016108870939880081887350187093988008188133018709598800888871501808979620071808170880025988889890737778008554800845043404808979661177808176880065988889190711771108688616788176767800835480084304240480077988008890511088609399800158815958800659888898901177785098966001882119088509896600188211908800967988788802381710098966007880879088009219817818023171800868865678807176180897966447180867688008688656788071767810939880088887350180085548008450434048609399800758871958800639888898901377785098961007885819188006398888989073177800868865678807116780096798878180238778709398800888871501870959880088887150680096798818880618778709398800818813306800967988781806387786093998007588739288008554800845043401870959880088887450110098966007180119088709398800888813506800168861678801176186093998007388739588009679887888024177830989260078128790885098966001885879088009219887118014811800868865678807676187093988008888735018006598888989073771800855480084501340411015548008431424048089792600778086768810939980075887595886095998007588739518008554800845043404800855480084504240480077988008890581018709598800888873501800967988188806487180085548008450424048008681600188016761850989221278858791880082886167880167118008534800145042404800868820078807610710098962001880819188709598800818873506808979220017808670886093998001588759588509892212788587918810959180018181330680016886167880717178509896200788287918800853411184504241411025918889891737778009279887188063817850989260078128790880063988889890717171106398818919111777101959980075807392810193988008880743018008688200788071701808979220077808610880063988889890737171109279887888164817810959980015887592880086886167880717178089196644778086718800921988781802317780897926007780161688709598800888813506101639110098901370785098922127185879188008288616788016711800921988788806417786093998007388739288009219881188063817110919611477818171810098966007110819088109599100138875908800659888898907317187097989007778179088001198800889058108100939880088807350180065988889890141778509892600188581908808979664171808676880092798871880248118009279887188021811870959880081887150180086882007810717078001798800889058701800967981181802487780891966441780817688008288656188016767808979220071801610880085341111450424141109796114778186718800119811188901871880092198878880648778008618200181011707";
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
		if ((params[6]=='2')&&(dictionary[i].number=='1')) continue;
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
//	load_from_file(221);
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
}
