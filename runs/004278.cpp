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
	const string templates_string="1290000099020111191012900000990221121910099020009920292019010990021121020911222209900020990209112913099020209902092129131090200099200122191411902000992001121914099020110002091022150990201100020911221511902001990200111216119020019902001111160992001099020910190729000010990209112918290000109902091229181190201099020211290911902010990222122919129000009902011219100990000099202920190109900211210209212222099000212002091120130990002099020922291310902012012001221214099000110002091022150992201100020911221511900001990200121206099200109902090019072900001111020911201829000011110209122018119000109902021229091290000099220112191010900010992002211901099020109920292119011090221121020210222210900211200202112112109000111002022120132900002110020922201310902010992001221914109020110120012210140990001100020911121510900021100002212115290020019922091111162990200199020911101609920010990209201907109220109902022019072900001111000912201829000000990009121918119020109902021019091190201099020210290911902000992201111910129020009922011219100990200099222920190109902211210209212222099022112102092222220990202120220921201309902010992209222913099220019902091222152900200199220911101610902001992000121116099200109922092019072900201111220911201829002000992229122918290020109922091129091090201099220221290912900000990221111910099000209902092129130990002120022921201311902000992001221914099000110002091122151190200199002011111629000000990209112918290000112102091110181190001099022211290912900000990001111910099002109922091229210990021099200921292109902211200209122212099000212002092120131190200099200221191409900011000209202215119000019902000212161190000199000012121609902010990209101907290000112002091120181190001099020220190911900010990202212909099002109920091129010990021099200911292109900211100209112222099002112002091122220990002110020911201311902011112001221014119020111120012211140990001100000911221511900001990200111216290000110002091120181190001099020211290909900211200209222122099000212002092020230990002120020922112311902010992002221914099200110002091022250992001100020911222529000011110209112118119000109902021029091190001099020211292912900000990001121910099002109922091129210990021100220912122109900211000209112222119002111102021022222900002100020921201310902021000202212113109020112120012210141090201121200222100409900011000209121215099000110002091211151190200199020012121609902010990209201907099020109900091019072900001110020912201829000011010209122118119000109902021129191190201099020212292912900000992201111910129000009922211219100990020099220911292109902200992229211921109022112102022021221090204120220022201329002020992229212913109020009920202219141092201100020012221509922011000209122215290020019922091212160990200199220912111609900000990009021917099000009900092229072900000099020912291829002010992209112919119020109922221129191290000099220101191012900000992001011910099020009922292119010990020099202921190109900211110209222222099002111102092122020990002120220921201310902000992000221914099000110002092212150990000199020922121511902001992200011116119020019920000111160992001099220921190709920010992209212907290020109902091129182900201100020911101811902010992202211909099000109902091119101190000099000111191009902000990229201901099000112002091111120990021120000921222209902021200209201003099020212002092020030990200199000922101410902000990002221914099000110002091011051190200199000012111609900001990009121116099020109900091029072900001100020911101829000011000209112128099000109900092029090990000099000900191009900000990009111900099020009922092019010990201099222920190109902011210209101202099002112102091022220990202110020910120309920021100209211203099020019900091010141090200199000212101409902011000209002215099020110000091022051090200199000012121629002000990209121918299000019900091210181090201099020210190929002010990209201909109020009920011219100990201101220912221109900211012209122121099020111002091120120990202099220922291309902021202209222013099020110002091221251090200199200002101609902010990009201907290020019922091120182900201111220911101810902010990202201909119020009902011119101190200099200111191009902000992029211901099022112102092220120990221121000912202209902021200209112023099020212002091220230990201100020911211509922011000209112125109020019900000210160990201099220910190729002000992209122918109020009902021119092900200099020901191011902000990001111910299020009922292019011090221121020211221229002011210209122212099020211002092010130990202110020921212309902000990009121914099020110002091212150990000199000912121610902020990200201907290020009920091229181190200099022220290911902000992222201909292000009902091119102920000099020922191012900200992201122921099002009922291219210990021120020920222229000210990229222922290000211022292120131090201111200122101429200011112029221014109000110002021012151090001100020210222529202001990209011216292000019902090212161292001099020110190729020010990209202907299000111002092220182920001099020921290912900000990001101910099000109900091019210990001099000910292109902011010009221222099000211002092010130990002100020920102310902011000001221014109020019900010210140990001100020910101509900011000209201025099020109902090019070992001099020910290729000011100209001018290000112002090020181090001121020210100910900001990002101109099002109920091229010990021099200912292109900211210209122222099000212022092220130990001100020912221511902001990000121216119000019900000212162900001101220912201811900010990202101909119020109902022119090990221121020911222209902021200209212013099000212002092121231190200299200122121411900001990200121216290020111102091120182900001120020912201809900210992009212901099000211002092120132900001110020911201809920000992229211901099002112102091122020990021121020921220209900020990209202913099000110002092112151190000199000012111629000011010209112018099002209922091129110990021099200922292109902211210209112212099220110002091022152900200199020911201811902011112002221014119020111120212210142900001111020911101809900210992009022921099002112102092222220990002120020922201309920011000209102215119020019902000111161190200199020001121629000011200009112018119020109902022129091190200099200222191409900011000209101215119000019900000211161190001099020211190912902000992201111910129020009922211119100990202099220911291329000020992229112913109020009922012119141090200099220111191409922011000209112115119020019922001111162900200099220911291829002000992209111918119020109922021129190990202120020910202310902000992002221914099220110002091222250990221121020912222209900021200209212113109020009920012119141190200099200121191429000011010209112118119000109902022129290990002099020912291312900000990021111910099022112102091022220992201100020910222529000011000009112018099002109922092129010990021101220911222109900021000209122123119020111120022211142900001100220912201809902021200209212023109020009920022119142900200099022912191811902010990202111909099002111002092122220990002120022922102311902010992001221914099000110002091022252900001111020912211811902010990202112929099020212022091120231090200099202122191409922011000209112225290020111022091120182900000199020911101811902010990002211909129000009922211119100990020099220921190109900020992209212913290000009922291129181190200099222111191009900200992209122921099022009922291219210990221121020911202210902211210200122022099220211022091120130992202110222912201310902000992221211914109020009922222119140992201100020912211510902001992200111016109020019922201210162900200099222911191810902000992222112909109020109922221129190990221099202921290109900011210209201102099000111102092012020990002100020920101309900011100209211013109020111120022211140990001100020910211509900011000209202015129000019900001111160992001121020910110709920011210209201207119000109902021119191190001099000221290909900010990009201921099000112100091210220990001121000922102209900021200009211013109000209902002019231090001100000211101410900010990001111914099000110000091111150990001100000922111511900001990000011116119000019900000211260990001099020920192729000000990009101918290000009900090119181190001099000210292911900010990002201929119020109902021229192900001099000912291809920011000209112215099002109922091229012900001100020912201809900011000009121215119000211002022120130990220099222911292109920010990209112907119000019922000212160990001100020922221510902000990002011914109020009900021119140990021121020922202209902000992009221914099020110100092212120990002120020922202329000011110009112018099000212002092020131290001099020210291909900210992209222921119000019902001012160990201100020921221510902002992001211214099020110002091112150990002120020922101309900211210009222222119000109902021229191190201099020212290909900211200209102222119000109900020019090990021121000912222211900001990200111116099002109922091229111190201099020211291909902000992209111914119000109902022029090992002110020910200311900001990000111216099002112102092112221190201099202222191410902000990001221914099020112120090121120990002120020921202311900010990202102929099000110002091122250990021099220902292112920200992221211921290000019902091120181290000199020012121611902001990200111206099002009920091219210990021099220911290109920010990209102927119020109902021029290990021120020911220209900200992209112901099000019922091120031090201111200122111409902021100209112223099000009900092019010990002099020921191309902001990009211014119020109900021029092900000099220911291811900001992200121216109020111120012212141090200099222220190909920021100209202113109020019920022210140990001100220911220110920021000200112215099022112122091221221090201099202222191409902011000209122115119020111000000222152900200199020911111629000010990209111919099000209902092029232900000099020911191809902011000209112015119022112102021121221090200199220012111609900021100209202113290020111102091121180990201121000922122229000001990209211018119020109902022029092900200099020921291510902011112201221014099020210002091121030990201121020911122211900001990000111116099020112022091221221190201201020012221809902000992229201914109020009920001219160990001100020911122512900000990201211910099020109902091029070990001099020910292909900011000209201215109020109900012119142900001110000911201809902211212209212002099022112122092020021190201099000212291909900020990229202913099000109902091019270990021110000921222229002011112209122018099020212022091120132900000099000921191809900011210009211121119000120102001122180990201121020900100709902011210209112222099002209922291229130990201121020922211209902011212009122011";
	const string templates_weight="87097989007778879088709798900771881908800833480084304230480096798878880648778008688200788016707800828820078807670785098966007885879088309896600788517908800639888898907477780063988889890737778609599800758873958860959980075887392880077988008890587088089796200778086708808979620077808170887095988008888745068709598800881871501870979890077788190880085348008430423048009679887888024877800868865678801676780086882007880717078509892112788587918800659888898907477780023988889890737778609399800758875951800779880088901870880897966447780867688089796644778081768870939880088887150687097989001778819081108534800845142304800833480084304230411092798878881618771109679881888164811110868161678817676710186886167880717678509892600788587908850989221278858791880065988889890731771106591818919113717101959980015807392810095998007580739188007798800889038708110719880088913870880897966447180817688089792200718081108870959880088887330687095988008888735068109198900177887908870919890017788190880083348008430423048009279887888024877800927988788802387780082886561880767678008281200188071707800239180098907177710195998001580739188109599800138875928800779880018903870880891966441780867688089192200171081708101959880018807450681095988001888145068709798900771887908800868820078807670780086886567810767678309896600788587908800659888898907377786095998007318739288089792200778086708808979661477808616887093988008818745068709798900717887908800855480084504350480085548008450425048009279881888063871800868865678807676783098966007882819088006598888989014777860939980075881595886093998007388759588001198800889058708808979661177808676887093988008888133068709398800888814506800855480084504250480085548008450425048009679811888064877800967988188806487780086886167880167678309892212788587918830989221278858791880065988889190737778609399800758873958808979661177808676887093988008888745068009679881888023817800868865678807176180086886567880711118309892600788287908800259888898907477180025988889890737718089796644778086718870939880088887350687093988008888745018709798900717881908800855480084504250480085541118450433148009679811888064877110967981788816187710186886167880767671108288616788176717850989221278858791885098922127882879118006598888989071177800659888898907111786095998007588759588001198800889038708800119880081905870880897966417780817688089796614778081718870939880088887450187095988008888715018709798900177887908870979890017188190880085548008450425048008354800843042304110927988788812181711082816561881717671018288200181076707850989660078118790811023988889891717778002398888989071777101959980015807595810095998001580759288001791800819011701800179180081903110880897922007780817081019598800188074501870959880018187450187097989001778179088709798900117817908800833480084304230480085548008430423048009679817888023877800967981788802487180086886561880767678509896600788187908800659888898901117780065918009890111778609599800158813928860959980013881392880077988001890317088007798800189031108808919620077808670880891966117780861688709598800188814306100979190077708790881097989007178879088008334800143042304800961988188806411180096798818180248778008288656788071161800828865678807176110098962001880879188509896600188287908800659888898907411186095998007388759281009399800738075928800119880081905810880897966117780861688089796611778086711100939880081801350610097989007170119081009798900717087901800833480084504230480083348008430423048009219887888061171800967988788806187780082886167880111118001688616788076111100989620018801191885098962001882179188006398888989014777800639888891907477181095998007388759588089192200778081108800979260071808116881095988008888733061019598800888013306810919890011788190880083341118450435118008554111845043514800921981188806481180082882001880717078008288656188071767800639888898907171181095998001388159188001198800819038708808919260017808676880891966441780861688109598800888813306810919890077788790881091989001178879088008334800843042304800927988788802381180092798878180638178008288656788016761800828865678801176180063988889890737178002398888989073711810959980073881591880011988001890587088089192200178081708810959180088887430610191989007770179088109198900717887908100833480084304230411092798878881648711019219887888063871800828861678807116780082886167880767111009896600188017908800639888898907117710093998007380759581101191800889138708808919220011808170887095918008818135068709591800181813306101979890077708790810197989007770119081108554800845143504800855480084304330480096798818880218771019679100881023807101868861618107676785098922127885879181019192212781087918110659888898917417711065988889891747711019599800758013958101939980075801595811077988008891587081017798800889038108800979664177801176810193988008880145068709798900717881908800853480014504230480085348001450425048009219817818023177800868861678807116780086886167880711618509892211188587918850989620018851791880065988889890741178006598888989014111800119880088901870880077988008890581088089796641778011168808979661177801176881093981118888733168109391100818873316800855480084504350480085548008450435048009679887888063877800868865618807176780065988889890717778609599800738875958860939980073881595880897966141780817688709398800888873306870959880088881430680092798878880648778008288656788076767800868865678807671183098961007885879188609399800758875958808919664477808676880897966117780817688008554800845042504800868861678807676780897966417780867688001534800843042304800967988788806487180096798878880248718008688200788071707800659888898901317786093998007388759288089796614778086768800855180084504250180085548008450435048009279887888064871800239888898907477780891926007780867688309892212788287918830989221278158791880897966447780861688008554800845013504800967988788802387780086886567880717678002598888989074777860959980075881392886095998007588139588089796611718086768870959880088881450683098966007882879088006598888989074177860939980073881592887093988008888743068709198900177887908870919890017188790880082882001880167071018688200181016707850989660071858190885098966007185119088002398888989073717860959980015887392880891922001780867088089192200178086108870959880018887450180082886567880117618509896600788287908800239888898907177180092798878880638778008688656788076717850989660078858190883098966007885819088089796614778086718870939880088881450180086882007880117078709798900711887908800927988788806187780023988889890747718089796611718086768800855480084504250480085541118450425148008688616788011711830989221278828791880897966111780817688008288656788076761850989660078828190880891922007710811088709598800888874306800967981188802487780086886567810711618309892600788587908800659888898907477180897966447780817188709598800888874501800828865618801676185098966007815879088002398888989073771808919664117808676880897926007780861688709598800818814306870979890017188790880085548008450423048008688200188076707808979220017108670881091989001718879088008554800845043504800835480084304330480092798878880648171109279887888163817800128861618801676780012886161810117678509896600711581908850989660071128190880023988889890717178109599800158873918810959980015187591880891922001710861088109591800181874506810959880018187450180083548008430425048009619887888021111800961981788802117180086886167880711678008681616788076167850989221278828791880065988889890747178006598888989014717810939980073887392880077981118890587188007798111889038718870939880088887430187093988008188145068008534800145042304800961988781806311780096198878180231178008688656718076167110868820078817110185091922111882119188509192600188511908800659888891907311780065988889190111178609399800738813928860939980073881592180017988008890387018089792200718081108808979220071801610887093988008188735018709398800818813301870959880088887150180897962007180817088002598888989073777800855480084504350480897966117780817688006598888919071177110868861678817676780083548008430425048007798800889051108860939980015881595880065988889890117778509896600188211908850989660018821190880096798878880238171009896600788087908800921981781802317180086886567880717618089796644718086768800868865678807176781093988008888735018008554800845043504860939980075887195880063988889890137778509896100788581918800639888898907317780086886567880711678009679887818023877870939880088887150187095988008888715068009679881888061877870939880081881330680096798878180638778609399800758873928800855480084504350187095988008888745011009896600718011908870939880088881350680016886167880117618609399800738873958800967988788802417783098926007812879088509896600188587908800921988711801481180086886567880767618709398800888873501800659888898907377180085548008450135041101554800843142304808979260077808676881093998007588759588609599800758873951800855480084504330480085548008450425048007798800889058101870959880088887350180096798818880648718008554800845042504800868160018801676185098922127885879188008288616788016711800853480014504230480086882007880761071009896200188081918870959880081887350680897922001780867088609399800158875958850989221278858791881095918001818133068001688616788071717850989620078828791880085341118450425141102591888989173777800927988718806381785098926007812879088006398888989071717110639881891911177710195998007580739281019398800888074301800868820078807170180897922007780861088006398888989073717110927988788816481781095998001588759288008688616788071717808919664477808671880092198878180231778089792600778016168870959880088881350610163911009890137078509892212718587918800828861678801671180092198878880641778609399800738873928800921988118806381711091961147781817181009896600711081908810959910013887590880065988889890731718709798900777817908800119880088905810810093988008880735018006598888989014177850989260018858190880897966417180867688009279887188024811800927988718802181187095988008188715018008688200781071707800179880088905870180096798118180248778089196644178081768800828865618801676780897922007180161088008534111145042314110979611477818671880011981118890187188009219887888064877800861820018101170780092198878880238118008334111845043511";
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
//	load_from_file(222);
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
