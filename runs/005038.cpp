// attention! Only right-angled pictures are processed normally!
// this algorithm needs teaching (see 'setting empirics').
// i didn't found out, how to use standart fonts in this situation (using only standart libraries)

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

std::istream* in = &std::cin;
std::ifstream fin;
std::ofstream fout;

const int max_digit_height=50, min_digit_height=20;
const std::vector<int> empty(1,0); //used for TPicture constructor
const std::vector<char> ch_empty(1,'.'); //used for TChicture constructor

// some empirical data
std::map <std::string, std::vector<int> > vert_codes;
std::map <std::string, std::vector<int> > horiz_codes;
std::map <std::string, std::vector<int> > redge_codes;
std::map <std::string, std::vector<int> > ledge_codes;

std::map <char,int> pallete; //pallete - turns chars to values
std::map <int,char> rpallete; //reverse pallete - turns values to chars

typedef std::vector< std::vector<int> > TPicture; 
typedef std::vector< std::vector<char> > TChicture; 
typedef std::pair<int,int> TIntpair;


//********************************************************************************
//*********************** particular processing the picture **********************
// calculates the number of colored dots, surrounding 'pic[i][j]'
int sum_black(const TPicture& pic, int i, int j)
{
	 int summ=0;
	 if (pic[i][j+1]) summ++;
     if (pic[i][j-1]) summ++;
	 
     if (pic[i+1][j]) summ++;
	 if (pic[i+1][j+1]) summ++;
	 if (pic[i+1][j-1]) summ++;
	 
     if (pic[i-1][j]) summ++;
	 if (pic[i-1][j+1]) summ++;
	 if (pic[i-1][j-1]) summ++;
	 return summ;  
 }

// sums up colors of dots, surrounding 'pic[i][j]'
int sum_border(const TPicture& pic, int i, int j)
{
	 int summ=0;
	 summ += pic[i][j+1] + pic[i][j-1];
	 summ += pic[i+1][j] + pic[i+1][j+1] + pic[i+1][j-1];
	 summ += pic[i-1][j] + pic[i-1][j+1] + pic[i-1][j-1];
	 return summ;  
 }


//calculates the number of colored dots in 'pic' along 'slice' (row, if 'dim='r'; columns, if 'dim'='c')
int summator_black(const TPicture& pic, int slice, char dim = 'r')
{
	unsigned int rows = pic.size();
    unsigned int cols = pic[0].size();
    int summ=0;
	switch(dim)
	{
	case 'c':               
        for (unsigned int i=0; i<rows; i++) {
            if (pic[i][slice]) summ ++;
        }
		break;
	case 'r':
	    for (unsigned int i=0; i<cols; i++) {
            if (pic[slice][i]) summ++;
        }
		break;
	}
	return summ;
}

//calculates the summ in 'pic' along 'slice' (row, if 'dim='r'; columns, if 'dim'='c')
int summator(const TPicture& pic, int slice, char dim = 'r')
{
	unsigned int rows = pic.size();
    unsigned int cols = pic[0].size();
    int summ=0;
	switch(dim)
	{
	case 'c':               
        for (unsigned int i=0; i<rows; i++) {
            summ += pic[i][slice];
        }
		break;
	case 'r':
	    for (unsigned int i=0; i<cols; i++) {
            summ += pic[slice][i];
        }
		break;
	}
	return summ;
}

// floods 'pic' with black. recursive. My algorithm is not very beatyfull :(
//void flood(TPicture& pic, int i, int j)
//{
//    if (j) {
//        if (pic[i][j-1]!=0) {
//            pic[i][j-1]=3; 
//            flood(pic,i,j-1);
//        }
//        if(i!=0 && pic[i-1][j-1]!=0) {
//            pic[i-1][j-1]=3; 
//            flood(pic,i-1,j-1);
//        }
//    }
//   if (i) {
//       if (pic[i-1][j]!=0) {
//           pic[i-1][j]=3; 
//           flood(pic,i-1,j);
//       }
//       if(j!=pic.size()-1 && pic[i-1][j+1]!=0) {
//            pic[i-1][j+1]=3; 
//            flood(pic,i-1,j+1);
//        }
//   }
//   if (j!=pic.size()-1) {
//        if (pic[i][j+1]!=0) {
//            pic[i][j+1]=3; 
//            flood(pic,i,j+1);
//        }
//        if(i!=pic.size()-1 && pic[i+1][j+1]!=0) {
//            pic[i+1][j+1]=3; 
//            flood(pic,i+1,j+1);
//        }
//   }
//   if (i!=pic.size()-1) {
//        if (pic[i+1][j]!=0) {
//            pic[i+1][j]=3; 
//            flood(pic,i+1,j);
//        }
//        if (j!=0 && pic[i+1][j-1]!=0) {
//            pic[i+1][j-1]=3;
//            flood(pic,i+1,j-1);
//        }
//    }
//}
//
////returns coordinates of the first detected white dot in 'pic'.
//TIntpair white_pos(const TPicture& pic)
//{
//    unsigned int rows = pic.size();
//    unsigned int cols = pic[0].size();
//    TIntpair coords;
//    coords.first = rows;
//    coords.second = cols;
//    for (unsigned int i=0; i<rows; i++) {
//        for (unsigned int j=0; j<cols; j++) {
//            if (pic[i][j]==0) {
//                coords.first = i;
//                coords.second = j;
//                return coords;
//            }
//        }
//    }       
//	return coords;
//}

//*******************************************************************************************
//********************** some descriptions of picture for empirical processing **************
// reads out, how do the number of black dots changes from column to column in 'pic'
// otherwords - calculates intersections of black lines and vertical section and finds out,
// how their number change from column to column.
// the first in pair - the number of column, the second - the number of intersections in this column 
std::vector<TIntpair> count_intersect_vert(const TPicture& pic)
{
    unsigned int rows = pic.size();
    unsigned int cols = pic[0].size();
    std::vector<TIntpair> lines;
    TIntpair tmp;
    tmp.first = 0; tmp.second = 0;
    lines.push_back(tmp);
    for (unsigned int i=0; i<cols; i++) {
        int num = 0;
        unsigned int j=0;
        while (j<rows) {
            if (pic[j][i]!=0) {
                j++;
                while (j<rows && pic[j][i]!=0) j++;
                num++;
            }
            j++;
        }
        //there are no digits having more, than 4 black lines at each vertical section
        //so, when num>=5 - it's ignored
        if(num!=0 && num<5 && lines.back().second != num) {
            tmp.first = i; tmp.second = num;
            lines.push_back(tmp);
        }
    }
    return lines;
}


// the same as previous, but for horizontal sections.
// OFFTOPIC: 
// possibly, some other way for the 'pic' storage or workaround should let us unite this function and previous?
std::vector<TIntpair> count_intersect_horiz(const TPicture& pic)
{
    unsigned int rows = pic.size();
    unsigned int cols = pic[0].size();
    std::vector<TIntpair> lines;
    TIntpair tmp;
    tmp.first = 0; tmp.second = 0;
    lines.push_back(tmp);
    for (unsigned int i=0; i<rows; i++) {
        int num = 0;
        unsigned int j = 0;
        while (j<cols) {
            if (pic[i][j]!=0) {
                j++;
                while (j<cols && pic[i][j]!=0) j++;
                num++;
            }
            j++;
        }
        //there are no digits having more, than 2 black lines at each vertical section
        //so, when num>=3 - it's ignored
        if(num!=0 && num<3 && lines.back().second != num) {
            tmp.first = i; tmp.second = num;
            lines.push_back(tmp);
        }
    }
    return lines;
}

// reads out the left edge of the digit in 'pic'.
// otherwords - calculates number of white dots from left edge of the 'pic' to the first colored dot
// finds out, how their number change from column to column.
// the first in pair - the number of row, the second - the number of white dots 
std::vector<TIntpair> count_edge_left(const TPicture& pic)
{
    unsigned int rows = pic.size();
    unsigned int cols = pic[0].size();
    std::vector<TIntpair> lines;
    TIntpair tmp;
    for (unsigned int i=0; i<rows; i++) {
        unsigned int j=0;
        while (j<cols && pic[i][j]==0) {
           j++;
        }
        tmp.first = i; tmp.second = j;
        if (lines.size()) {
            if(lines.back().second != j) {
                lines.push_back(tmp);
            }
        }
        else lines.push_back(tmp);
    }
    return lines;
}

// the same as previous, but for right edge.
// OFFTOPIC: 
// possibly, some other way for the 'pic' storage or workaround should let us unite this function and previous?
// possibly, something like lambda-expression could let us unite 2 or 4 last functions?
std::vector<TIntpair> count_edge_right(const TPicture& pic)
{
    unsigned int rows = pic.size();
    unsigned int cols = pic[0].size();
    std::vector<TIntpair> lines;
    TIntpair tmp;
    for (unsigned int i=0; i<rows; i++) {
        int j=cols-1;
        while (j>=0 && pic[i][j]==0) {
           j--;
        }
        tmp.first = i; tmp.second = cols-1-j;
        if (lines.size()) {
            if(lines.back().second != j) {
                lines.push_back(tmp);
            }
        }
        else lines.push_back(tmp);
    }
    return lines;
}

// generalize results of previous functions (makes them scale-independed)
// -1 - the edge of digit is closer to left edge of pic;
// 0 - the edge is in the middle;
// 1 - the edge of digit is closer to right edge of pic
std::vector<TIntpair> generalize_edge(const std::vector<TIntpair>& edge) {
    unsigned int len = edge.size();
    int part = len/3;
    std::vector<TIntpair> lines = edge;
    for (unsigned int i=0; i<len; i++) {
        if (lines[i].second < part) {
            lines[i].second = -1;
        }
        else {
            if (lines[i].second < 2*part) {
                lines[i].second = 0;
            }
            else lines[i].second = 1;
        }
    }
    return lines;
}

//*******************************************************************************************
//********************** empirical processing the picture ***********************************

    // just an auxillary function
    void push_possibles(std::map<int,int>& poss, std::vector<int>& line) {
        for (unsigned int i=0; i<line.size(); i++) {
            if ( poss.count(line[i]) ) {
                poss[line[i]]++;
            }
            else poss[ line[i] ] = 1;
        }
    }

// looks for digit with '*_code' in '*_codes'
// if multiple digits (or no digits) were detected in '*_codes' the same number of times - program is confused
// and look_in_codes returns false.
bool look_in_codes(char& digit, std::string& v_code, std::string& h_code, std::string& r_code, std::string& l_code) {
    std::map<int,int> possibles;
    std::vector<int> v_digits = vert_codes[v_code];
    std::vector<int> h_digits = horiz_codes[h_code];
    std::vector<int> r_digits = redge_codes[r_code];
    std::vector<int> l_digits = ledge_codes[l_code];
    
    push_possibles(possibles, v_digits);
    push_possibles(possibles, h_digits);
    push_possibles(possibles, r_digits);
    push_possibles(possibles, l_digits);

    if (possibles.size()) {
       std::map<int,int>::iterator max_possible = possibles.begin();
       std::map<int,int>::iterator i = max_possible;
       int num_max_possible = 1;
       for (i; i != possibles.end(); ++i) {
           if (max_possible->second < i->second) {
               max_possible = i;
               num_max_possible = 1;
           }
           else {
               if (max_possible!=i && max_possible->second == i->second) {
                num_max_possible++;
               }
           }
       }
       if (num_max_possible > 1) return false;
       digit = 48 + max_possible->second;
       return true;
    }
    else return false;
}


    // turns seconds from std::vector<TIntpair> to std::string
    // just an auxillary function
    std::string pair_to_str(std::vector<TIntpair> line) {
        std::string str = "";
        unsigned int len = line.size();
        for (unsigned int i=0; i<len; i++) {
            str += 48+line[i].second;
        }    
        return str;
    }

// tries to identify the digit in 'pic'
// returns false, if no digit was idented.
bool identify(const TPicture& pic, char& idented)
{
    std::vector<TIntpair> vert = count_intersect_vert(pic);
    std::vector<TIntpair> horiz = count_intersect_horiz(pic);
    std::vector<TIntpair> redge = count_edge_right(pic);
    std::vector<TIntpair> ledge = count_edge_left(pic);
    std::vector<TIntpair> g_ledge = generalize_edge(ledge);
    std::vector<TIntpair> g_redge = generalize_edge(redge);
    
    std::string vert_code = pair_to_str(vert);
    std::string horiz_code = pair_to_str(horiz);
    std::string redge_code = pair_to_str(g_redge);
    std::string ledge_code = pair_to_str(g_ledge);
    
    if ( look_in_codes(idented, vert_code, horiz_code, redge_code, ledge_code) ) {
        return true;
    }
    return false;
}


// **********************************************************************************
// ***************************** some general processing ***************
// possibly noise and roughness will disappear from the 'pic'
TPicture smooth_pic(const TPicture& pic)
{
	unsigned int rows = pic.size(), cols = pic[0].size();
    TPicture smooth(rows,empty);
    int summ;
    smooth[0].assign(cols,0);
    smooth[rows-1].assign(cols,0);

	for (unsigned int i=1; i<rows-1; i++) {
		for (unsigned int j=1; j<cols-1; j++) {
			summ = sum_border(pic,i,j);
            if (summ>3) {
                if (pic[i][j]) {
                    smooth[i].push_back(3);
                }
                else {
                    if (summ>5 && sum_black(pic, i,j)>3) {
                        smooth[i].push_back(3);
                    }
                    else smooth[i].push_back(0);
                }
            }
            else smooth[i].push_back(0);
		}
        smooth[i].push_back(0);
	}
	return smooth;
}

// crops white borders (only up and bottom) from picture 'pic'
// possibly the 'pic' will become a little bit smaller
int crop_pic(TPicture& pic)
{
	//crops head
	int head = -1;
    while (summator(pic, head+1, 'r')<=2) head++;
    for (int i=0; i<head; i++) pic.erase(pic.begin());
	//crops bottom
	int bottom = -1, rows=pic.size();
    while (summator(pic, rows-2-bottom, 'r')<=2) bottom++;
    for (int i=0; i<bottom; i++) pic.erase(pic.end()-1);
	return 0;
}


// **********************************************************************************
// ***************************** dividing picture in parts **************************
// gets subpic from 'pic'
TPicture subview(TPicture& pic, int begin, int end) {
    unsigned int rows = pic.size();
    TPicture subpic(rows,empty);
    for (unsigned i=0; i<rows; i++) {
        for (int j=begin; j<end+1; j++) {
            subpic[i].push_back(pic[i][j]);
        }
    }
    return subpic;
}

// divides the picture in parts, each of that may contain one digit
// 'divides' contain the begining and the end (in horizontal plane) of each digit in 'pic'
// the end of one digit is the begining of the next.
// suspected, that digits are separated with white columns (or where only 2 colored dots appear)
std::vector<int> divide(const TPicture& pic)
{
	unsigned int cols = pic[0].size();
    std::vector<int> divides;
	divides.push_back(0);
	bool new_digit=false;
	for (unsigned int i=1; i<cols; i++)
	{
		if (summator(pic, i,'c')<3 || summator_black(pic, i, 'c')<2)  
		{	if (new_digit)
			{	divides.push_back(i);
				new_digit = false;}
		}
		else new_digit = true;
	}
	return divides;
}


// **********************************************************************************
// ****************** reading/outputting picture and first processing ***************
// turns picture in char to picture in int
TPicture turn_to_int(TChicture& lines)
{
    TPicture pic;
    for (unsigned int j=0; j<lines.size(); j++) {
        pic.push_back(empty);
        for (unsigned int i=0; i<lines[j].size(); i++) {
	        pic.back().push_back(pallete[ lines[j][i] ]);
        }
    }
    return pic;
}

// reads picture (in char) from '*input'
TChicture read_pic(std::istream *input)
{
	TChicture lines;
    int i=0;
    std::string line="";
    *input >> line;
    int len = line.length();

	while (len) {
	    lines.push_back(ch_empty);
        for (int i=0; i<len; i++) {
            lines.back().push_back(line[i]);
        }
        line="";
        *input >> line;
        len = line.length();
        
    }
	return lines;
}

//outputs 'pic' to 'fout'
int output(const TPicture& pic)
{
	unsigned int rows = pic.size(), cols=pic[0].size();
    for (unsigned int i=0; i<rows; i++)
	{
		for (unsigned int j=0; j<cols; j++)
		{
			fout << rpallete[ pic[i][j] ];
		}
		fout << std::endl;
	}
	return 0;
}

int get_in_out(int n, char* str[])
{
	std::string tmp;
	if (n > 1)
	{
		tmp = std::string(str[1]);
        std::string tmp2 = tmp + ".a";
        std::ifstream ain;
        //ain.open(tmp2.c_str());
        //int answer;
        //ain >> answer;
        //std::cout << "the answer: " << answer << std::endl;
        //ain.close();
        fin.open(tmp.c_str());
		in = &fin;
		//tmp += "result";
		//fout.open(tmp.c_str());
	}
	return 0;
}


// **********************************************************************************
// ***************************** setting empirics ***********************************
int set_pallete()
{
	pallete['.'] = 0;
	pallete['%'] = 1;
	pallete['#'] = 2;
	pallete['@'] = 3;
	rpallete[0] = '.';
	rpallete[1] = '%';
	rpallete[2] = '#';
	rpallete[3] = '@';
	return 0;
}

//sets 'codes'
void set_codes()
{
    return;
}

//*********************************************************************************************
// **************************** MAIN **********************************************************
int main(int argc, char* argv[]) {
    TChicture ch_view; //stores the processed picture in char, never changes since first reading
    TPicture view; //stores the processed picture in int, changes
    std::vector<int> digits; //stores boundaries of supposed digits on the picture
    
    set_pallete(); 
    
    set_codes();
    
    get_in_out(argc, argv);
    // reads the picture from '*in'
	ch_view = read_pic(in); //if(read_dic()) {cout<<err; return 1;}
	
	view = turn_to_int(ch_view);
    
    // gets boundaries fo suspected digits in 'view'
    digits = divide(view);
    
    // each digit is processed separately
    if (digits.size()) {
        for (unsigned int i=0; i<digits.size()-1; i++) {
            char digit;
			TPicture dig_view; //stores an area with processing digit
            dig_view = subview(view,digits[i],digits[i+1]);
            dig_view = smooth_pic(dig_view); 
            crop_pic(dig_view); //crops white borders (only up and bottom)
            if (identify(dig_view, digit)) {
			    std::cout << digit;
            }
            else std::cout << '_'; //identify failed
    //        output(view);
	
        }
    }
    else std::cout << "no digits detected" << std::endl;
            
   return 0;
}
