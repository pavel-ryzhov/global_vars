#include <iostream>
#include <string>
#include <vector>
//#include <fstream> //////////////////////////////////////////
#include <math.h> 



using namespace std;
const int test = 0;
void topologator(char, int, int, int, int, vector <vector <char> >&, char );
struct size {
	int up_lim, dw_lim, lf_lim, rt_lim;
	size (int H, int W) {up_lim = 0; dw_lim = H; lf_lim = 0; rt_lim = W;};
};

class image {
private:
	vector <vector <char> > matrix;
public:
	int height, width;
private:
	vector <int> edge1, edge2;
public:
	image();
	image(int,int);
	void intiate();
	void show();
	void resize();
	int digit_score(image);
	void get_number(int,image &, int);
	void divide_and_count(double[10][4]);
};


int main (void)
{

	double ideals[10][4] = {{0.25,0.25,0.25,0.25},{0.05,0.05,0.05,0.05},{0.17,0.33,0.22,0.28},
	{0.15,0.35,0.35,0.15},{0.33,0.34,0.33,0.00},{0.36,0.15,0.35,0.14},{0.29,0.12,0.29,0.30},
	{0.27,0.41,0.02,0.30},{0.25,0.25,0.25,0.25},{0.29,0.3,0.29,0.12},};
	// statistic on number of pixels for quarter 

	image main;
	main.intiate();
//	main.show();
	main.resize();	
	int score =  main.digit_score( main);
	if (test) {
		main.show();
		cout << score << endl;
	}
	
	for (int i = 0; i< score; i++) {
		image figure(main.height, main.width);
		main.get_number(i+1, figure, score);
		figure.resize();
		if (test) {
			figure.show();
		}
		figure.divide_and_count(ideals);
	}
	
	return 0 ;
}
image::image(void) {
	vector <vector <char> > matrix2(300);
	matrix = matrix2;
	height = 0;
	width = 0;
};

image::image(int H, int W)
{
	vector <vector <char> > matrix2(H, vector<char>(W));
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			matrix2[i][j] = '.';
		}
	}
	matrix = matrix2;
	height = H;
	width = W;

}
void image::show(void) {
	cout << endl << "Height=" <<  height << ' ' << "Width=" << width << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << matrix[i][j];
		}
		cout << endl;
	}
};

void image::intiate (void) {
	string test;
	string::iterator it_string;
//	ifstream cin1 ("ttt3.txt");
	bool test2 = 1;
	cin >> test;
	for (int i = 0; cin; i++) {
		it_string = test.begin();
		for (;((it_string) < (test.end()));it_string++) {
			matrix[i].push_back(*it_string);
			if (test2) {
				width++;
			}
		}
		test2 = 0;
		height++;
		cin >> test;
	}
	edge1.assign(height,0);

}

void image::resize(void)
{
	bool stop = false;
	int dw_lim = height;
	int up_lim = 0;
	int rt_lim = width;
	int lf_lim = 0;


	for (int i = 0; i < height; i++) { 
		for (int j = 0; j < width; j++) {
			if ((matrix[i][j] == '@') ||(matrix[i][j] == '%')||(matrix[i][j] == '#')) {
				stop = 1;
			}
		}
		if (!(stop)) {
			up_lim++;
		} else if (stop) {
			break;
		}
	}
	stop = false;

	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			if ((matrix[i][j] == '@')||(matrix[i][j] == '%')||(matrix[i][j] == '#')) {
				stop = 1;
			}
		}
		if (!(stop)) {
			dw_lim--;
		} else if (stop) {
			break;
		}
	}

	stop = false;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if ((matrix[j][i] == '@')||(matrix[j][i] == '%')||(matrix[j][i] == '#')) {
				stop = 1;
			}
		}
		if (!(stop)) {
			lf_lim++;
		} else if (stop) {
			break;
		}
	}

	stop = false;
	for (int i = width - 1; i >= 0; i--) {
		for (int j = 0; j < height; j++) {
			if ((matrix[j][i] == '@')||(matrix[j][i] == '%')||(matrix[j][i] == '#')) {
				stop = 1;
			}
		}
		if (!(stop)) {
			rt_lim--;
		} else if (stop) {
			break;
		}
	}
	vector <vector <char> > matrix2(dw_lim - up_lim, vector<char>(rt_lim - lf_lim));
	for (int i = up_lim; i < dw_lim; i++) {
		for (int l = lf_lim; l < rt_lim; l++) {
			if (matrix[i][l] != '%') {
				matrix2[i - up_lim][l - lf_lim] = matrix[i][l];
			} else {
				int chek = 0;
				if ((matrix[i+1][l] != '.') && (matrix[i+1][l] != '%')) {
					chek++;
				}
				if ((matrix[i-1][l] != '.') && (matrix[i-1][l] != '%')) {
					chek++;
				}
				if ((matrix[i][l+1] != '.') && (matrix[i][l+1] != '%')) {
					chek++;
				}
				if ((matrix[i][l-1] != '.') && (matrix[i][l-1] != '%')) {
					chek++;
				}
				if (chek > 1) {
					matrix2[i - up_lim][l - lf_lim] = '#';
				} else {
					matrix2[i - up_lim][l - lf_lim] = '.';
				}
			}
		}
	}
	matrix = matrix2;
	height = dw_lim - up_lim;
	width = rt_lim - lf_lim;
}
void image::get_number(int mod, image & figure, int count)
{
	edge2.clear();
	if ((mod != count)){
		int j = mod*width/count - 1;
		while ((matrix[0][j] != '.') && ( j != height - 1)) {
			j++;
		}
		edge2.push_back(j);
		for (int i = 1; (i < height); i++) {
			if ((matrix[i][j] != '.')&& (( mod!=3))) {
				if (matrix[i][j+1] == '.') {
					j++;
				} else if (matrix[i][j-1] == '.'){
					j--;
				} else {
					if (matrix[i][j+2] == '.') {
						j+=2;
					} else if (matrix[i][j-2] == '.'){
						j-=2;
					} else {
						if (matrix[i][j+3] == '.') {
							j+=3;
						} else if (matrix[i][j-3] == '.'){
							j-=3;
						} else {
							//
						}
					}
				}
			}
		//	cout << j;
			edge2.push_back(j);
		}
	} else {
		edge2.assign(height,width);
	}
	for (int i = 0; i < height; i++) {
		for (int l = edge1[i]; l < edge2[i]; l++) {
//			cout << i << ' '<< l;
			figure.matrix[i][l] = matrix[i][l];
		}
	}
	edge1 = edge2;
}
int image::digit_score (image  figure)
{
	int score = 0;
	for (int i = 0; i < figure.height; i++) {
		for (int j = 0; j < figure.width; j++) {
			if (figure.matrix[i][j] != '.') {
				figure.matrix[i][j] = 'q';
			}
		}
	}
	int digit_number = 0;

	for (int i = 0; i < figure.height; i++) {
		for (int j = 0; j < figure.width; j++) {
			if (figure.matrix[i][j] == 'q') {
				digit_number++;
				topologator('q', figure.width,figure.height, i, j, figure.matrix, 'd');
			}
		}
	}
	return digit_number;

}
void image::divide_and_count(double ideals[10][4])
{
	vector <vector <char> > topology(height +2, vector<char>(width + 2));
	for (int i = 0; i < height +2; i++) {
		for (int j = 0; j < width + 2; j++) {
			topology[i][j] = '.';
		}
	}

	for (int i = 1; i < height +1; i++) {
		for (int j = 1; j < width + 1; j++) {
			topology[i][j] = matrix[i-1][j-1];
		}
	}
	topologator('.', width +2,height +2, 0, 0, topology, '1');
	int zone_number = 0;
	char brush = '7';

	for (int i = 0; i < height+2; i++) {
		for (int j = 0; j < width+2; j++) {
			if (topology[i][j] == '.') {
				zone_number++;
				topologator('.', width +2,height +2, i, j, topology, '1' + i);
				brush = '1' + i;
			}
		}
	}
	double up = 0, down = 0;
	if (zone_number == 1) {
		for (int i = 0; i < height+2; i++) {
			for (int j = 0; j < width+2; j++) {
				if (topology[i][j] == brush) {
					if (i < height/2 +1) {
						up++;
					} else if ( i > height/2) {
						down++;
					}
				}
			}
		}
	}
	if (test) {
		cout << "number of zones = " << zone_number<< ", up_pixels = " << up << ", down_pixels = " << down << endl;
	}

	int w_mid = width/2, h_mid = height /2;
	double qu_1 =0, qu_2 =0, qu_3 =0, qu_4 =0, total = 0;

	for (int i = 0; i <= h_mid; i++) {
		for (int j = 0; j <= w_mid; j++) {
			if (matrix[i][j] != '.') {
				qu_1++;
			}
		}
	}

	for (int i = 0; i <= h_mid; i++) {
		for (int j = w_mid +1; j < width; j++) {
			if (matrix[i][j] != '.') {
				qu_2++;
			}
		}
	}

	for (int i = h_mid + 1; i < height; i++) {
		for (int j = w_mid +1; j < width; j++) {
			if (matrix[i][j] != '.') {
				qu_3++;
			}
		}
	}

	for (int i = h_mid + 1; i < height; i++) {
		for (int j = 0; j <= w_mid; j++) {
			if (matrix[i][j] != '.') {
				qu_4++;
			}
		}
	}
//	for (int i = 0; i < width; i++) {
//		if (1) {
//		}
//	}


	total = qu_1 + qu_2 + qu_3 + qu_4;
	qu_1/= total;
	qu_2/= total;
	qu_3/= total;
	qu_4/= total;
	if (test) {
		cout << endl << qu_1<< ' ' << qu_2 << ' ' << qu_3 << ' ' << qu_4 << endl;
	}
	double disper = 1, numb = 0, answer = 0;
	for (int i =0; i<10; i++) {
		if ((((zone_number) && ((i==0) || (i==6) || (i==9))) || (!(zone_number)) && (i!=0) && (i!=6) && (i!=9)) && (i!=8)) {
			numb = fabs(ideals[i][0] - qu_1) + fabs(ideals[i][1] - qu_2) + fabs(ideals[i][2] - qu_3) + fabs(ideals[i][3] - qu_4);
			if (test) {
				cout <<"for " << i << " difference is " << numb << endl;
			}
			if (numb < disper) {
				disper = numb;
				answer = i;
			}
		}
	}
	if (zone_number == 1) {
		if ((up/(up+down)) > 0.65) {
			answer = 9;
		} else if ((down/(up+down)) > 0.65) {
			answer = 6;
		} else {
			answer = 0;
		}
	}
	if (zone_number == 2) {
		answer = 8;
	}
	if (((answer == 0) || (answer == 9)) && (qu_4 < 0.15)) {
		answer = 4;
	}
	if ((answer != 0) &&(answer != 9) &&(answer != 6) &&(answer != 8) && (height >= 2*width)) {
		answer = 1;
	}
//	cout << endl << "I THINK IT'S " << answer << endl;
	cout << answer;

}

void topologator(char target,int left, int down, int i,int j, vector <vector <char> >& imba, char teg)
{
	//children cry from my recursion. improve it!
	imba[i][j] = teg;
	if (target == 'q') {
		int n = i +1, m = j +1;
		if (((m < left)&& (m >= 0) && (n < down)&&(n >= 0))) {
			if (imba[n][m] == target) {
				topologator(target, left, down, n,m,imba, teg);
			}
		}
		n = i - 1, m = j -1;
		if (((m < left)&& (m >= 0) && (n < down)&&(n >= 0))) {
			if (imba[n][m] == target) {
				topologator(target, left, down,n,m,imba, teg);
			}
		}
		n = i - 1, m = j+1;
		if (((m < left)&& (m >= 0) && (n < down)&&(n >= 0))) {
			if (imba[n][m] == target) {
				topologator(target, left, down,n,m,imba, teg);
			}
		}
		n = i + 1, m = j-1;
		if (((m < left)&& (m >= 0) && (n < down)&&(n >= 0))) {
			if (imba[n][m] == target) {
				topologator(target, left, down,n,m,imba, teg);
			}
		}
	}

	int n = i +1, m = j;
	if (((m < left)&& (m >= 0) && (n < down)&&(n >= 0))) {
		if (imba[n][m] == target) {
			topologator(target, left, down, n,m,imba, teg);
		}
	}
	n = i - 1, m = j;
	if (((m < left)&& (m >= 0) && (n < down)&&(n >= 0))) {
		if (imba[n][m] == target) {
			topologator(target, left, down,n,m,imba, teg);
		}
	}
	n = i, m = j+1;
	if (((m < left)&& (m >= 0) && (n < down)&&(n >= 0))) {
		if (imba[n][m] == target) {
			topologator(target, left, down,n,m,imba, teg);
		}
	}
	n = i, m = j-1;
	if (((m < left)&& (m >= 0) && (n < down)&&(n >= 0))) {
		if (imba[n][m] == target) {
			topologator(target, left, down,n,m,imba, teg);
		}
	}

}