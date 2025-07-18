#define max_n 200
#define max_m 500
#define max_obj 100
#define max_neuro 1000
#define d_n 64
#define d_m 48
#define window_n 4
#define window_m 3
#define destroy_rate 1.5
#define signs_n 10

#include <iostream>
#include <string>

using namespace std;
    
    const int dir[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
    const int s_teta = (window_n * window_m) / 2;
    const int a_teta = 0;
    const int  s_elem = (d_n / window_n) * (d_m / window_m);
    const int a_elem = s_elem + 4 + d_n*5 + d_m*5;
    const int weight[a_elem][signs_n] = {
{0,3,4,12,0,10,2,19,1,1},
{0,3,9,16,0,13,2,31,1,1},
{0,4,13,20,1,20,2,28,1,1},
{1,4,18,21,1,26,3,28,4,12},
{17,4,29,34,3,23,8,30,13,20},
{19,8,35,38,15,21,14,25,18,24},
{24,14,35,42,24,25,18,25,28,31},
{24,20,37,42,25,35,19,25,37,33},
{32,23,36,41,22,40,19,32,38,34},
{32,28,36,42,17,36,31,29,41,38},
{32,23,33,35,17,36,33,30,32,37},
{22,31,15,33,22,35,33,30,26,26},
{12,36,13,24,28,30,14,30,17,12},
{7,33,12,25,20,32,14,29,8,10},
{0,32,8,26,17,34,8,33,8,6},
{0,28,0,16,14,16,6,27,6,0},
{2,6,7,14,0,10,3,23,2,1},
{4,4,12,20,0,15,3,27,3,14},
{15,14,23,28,1,24,6,31,11,22},
{21,17,31,33,1,18,11,32,24,29},
{22,21,25,41,13,21,17,32,27,27},
{28,25,23,40,25,23,16,32,33,22},
{32,25,28,39,26,34,15,32,32,23},
{33,27,28,39,25,34,15,32,31,32},
{30,33,27,38,24,33,28,32,30,31},
{28,37,33,41,21,33,27,40,32,30},
{31,44,36,40,27,35,27,40,30,38},
{31,45,38,41,35,39,31,42,32,40},
{29,40,42,43,31,39,32,41,33,37},
{18,35,25,38,24,39,20,43,31,30},
{13,34,14,27,16,34,8,43,18,21},
{0,20,5,7,16,8,2,32,5,9},
{3,10,7,7,0,10,3,21,4,12},
{13,13,27,13,0,15,7,27,19,24},
{20,14,22,16,1,26,16,28,28,31},
{22,16,24,16,7,24,18,22,30,18},
{31,17,17,20,17,22,14,21,37,22},
{32,21,17,24,26,22,13,21,34,25},
{29,38,20,17,27,37,17,21,27,21},
{17,38,20,16,23,29,23,19,14,18},
{12,38,24,22,18,25,21,27,8,23},
{23,39,30,29,27,24,22,27,10,27},
{26,35,34,33,27,16,21,28,13,27},
{30,45,33,42,36,18,21,30,19,26},
{31,42,42,46,31,16,12,37,31,33},
{33,34,41,29,23,14,14,43,38,37},
{20,28,20,19,19,6,12,32,32,29},
{11,16,9,5,16,0,7,6,14,7},
{9,8,10,6,0,12,5,15,7,18},
{20,12,23,16,0,18,16,15,17,30},
{22,14,22,17,6,26,20,12,20,24},
{29,23,18,8,16,23,17,9,31,25},
{32,23,14,6,26,21,14,7,31,25},
{27,24,12,10,24,24,17,7,30,17},
{14,21,12,11,19,33,21,8,16,15},
{10,24,15,13,20,24,22,18,6,11},
{9,33,20,22,25,18,17,18,2,14},
{10,39,25,27,29,10,20,20,3,20},
{18,43,25,34,33,9,20,21,9,17},
{23,44,30,25,31,8,5,30,16,23},
{27,36,40,31,30,7,8,40,24,31},
{27,29,39,22,23,4,11,35,35,42},
{28,17,35,16,16,4,12,26,32,33},
{15,12,19,7,13,0,10,3,18,24},
{17,10,14,1,0,8,8,6,9,30},
{21,12,22,8,6,18,19,6,22,31},
{25,16,20,8,15,20,21,6,28,32},
{38,14,18,8,15,14,19,4,31,30},
{27,12,14,6,27,16,14,0,31,19},
{19,13,14,7,24,32,20,0,25,11},
{13,18,15,17,27,25,24,1,15,10},
{5,28,13,22,27,22,22,12,6,8},
{3,35,13,32,35,25,18,12,2,9},
{9,35,21,32,29,22,15,18,4,20},
{17,40,26,25,32,17,2,31,10,21},
{21,36,33,25,31,16,2,36,18,30},
{27,32,38,25,30,9,2,34,30,33},
{30,29,39,18,20,6,1,29,30,36},
{35,15,36,13,16,0,1,12,26,38},
{21,12,20,7,10,0,1,1,22,25},
{21,10,9,0,3,10,15,2,14,27},
{24,10,15,0,8,18,22,6,20,35},
{37,9,12,4,16,15,21,4,25,33},
{37,8,10,6,27,15,17,0,27,25},
{27,11,10,6,23,17,22,1,31,20},
{16,13,10,13,25,27,25,1,31,11},
{8,19,8,24,24,22,28,10,16,9},
{2,32,6,32,23,26,24,12,14,12},
{2,35,11,30,24,27,20,18,14,14},
{8,42,24,31,27,29,16,26,17,22},
{16,36,28,32,35,27,17,32,21,26},
{20,38,34,30,36,22,17,34,22,31},
{22,32,38,25,31,9,13,27,31,26},
{27,15,38,22,20,9,4,21,21,37},
{38,14,28,11,13,6,1,3,23,38},
{33,11,7,0,10,4,0,1,10,27},
{21,7,7,0,7,13,21,0,8,34},
{37,7,9,0,15,17,23,0,14,31},
{38,7,8,2,18,14,22,0,20,32},
{30,9,8,4,32,19,23,0,31,30},
{18,11,8,15,27,20,26,1,30,19},
{13,6,8,22,23,33,38,2,32,14},
{8,22,4,38,21,28,31,12,32,12},
{2,29,8,35,30,24,32,16,27,9},
{2,35,19,29,21,24,27,25,26,16},
{8,38,29,27,24,38,29,31,30,21},
{16,33,33,31,33,45,30,32,27,23},
{21,38,36,35,36,40,26,30,24,23},
{24,18,37,25,28,29,20,23,22,32},
{31,15,31,12,20,13,15,13,24,39},
{37,14,22,9,13,10,3,1,15,36},
{34,11,3,2,10,5,1,0,3,23},
{23,9,2,3,17,9,23,0,7,27},
{40,4,7,3,20,18,22,0,17,30},
{33,4,7,7,33,18,34,0,20,33},
{27,2,5,10,33,20,32,1,32,26},
{14,4,6,25,26,22,37,2,38,21},
{12,16,6,26,22,17,36,13,32,16},
{8,23,6,28,23,17,25,17,30,14},
{2,29,23,31,32,15,19,23,31,16},
{2,36,24,36,27,19,20,29,35,22},
{8,36,32,35,31,30,22,31,29,25},
{16,34,35,37,38,35,32,31,32,21},
{21,36,36,33,42,41,37,26,34,29},
{25,18,33,30,33,37,36,20,28,35},
{31,15,21,19,23,33,32,3,14,37},
{37,14,13,8,22,19,21,1,8,30},
{29,11,0,2,19,8,6,0,0,21},
{38,4,0,3,13,6,23,0,9,8},
{40,2,7,3,34,7,36,0,18,22},
{28,2,7,7,37,4,35,1,30,24},
{20,2,7,7,39,3,27,2,32,24},
{14,14,8,9,33,3,21,5,34,28},
{12,18,8,8,31,6,22,18,35,23},
{9,23,15,11,28,6,18,22,25,21},
{2,31,26,10,32,5,4,25,26,29},
{2,36,34,10,28,25,2,30,29,27},
{7,38,33,29,29,28,5,31,28,24},
{16,32,34,34,43,27,17,29,33,30},
{21,21,31,45,37,25,19,24,35,36},
{27,18,20,41,34,35,33,18,28,33},
{35,15,13,24,25,33,38,1,22,34},
{37,13,0,17,23,28,36,0,11,23},
{22,11,0,4,16,15,21,0,6,20},
{39,2,0,0,12,5,25,0,19,3},
{40,2,0,7,26,4,35,0,25,10},
{30,4,1,7,27,2,37,1,29,15},
{17,5,7,7,30,3,28,5,29,11},
{13,14,6,7,24,2,22,16,29,16},
{12,19,19,5,24,1,16,21,21,17},
{9,23,31,3,25,1,5,24,18,27},
{2,35,30,9,28,13,2,22,19,19},
{2,36,30,9,29,17,1,31,20,17},
{7,36,30,16,31,10,4,29,18,24},
{17,28,24,29,39,18,7,26,19,30},
{27,21,19,30,37,27,18,19,21,26},
{27,18,12,37,30,33,32,14,24,28},
{35,15,0,39,25,29,37,0,23,22},
{29,13,0,27,15,28,37,0,24,21},
{21,11,0,19,16,24,28,0,20,18},
{37,2,0,7,20,5,32,0,26,3},
{40,2,1,12,23,3,37,1,30,4},
{29,4,2,12,24,4,40,5,32,4},
{17,12,8,10,19,4,23,8,32,6},
{13,17,16,5,19,0,18,20,20,12},
{12,19,32,4,24,0,8,23,14,12},
{9,27,32,9,25,11,6,21,14,14},
{2,35,28,12,31,13,6,32,15,7},
{2,34,31,16,29,7,5,27,19,14},
{8,32,24,9,30,16,7,26,19,27},
{22,20,18,21,37,26,11,24,19,27},
{27,21,11,24,32,29,20,18,16,24},
{31,18,6,27,30,30,36,2,23,20},
{27,14,4,34,23,26,41,0,22,23},
{19,11,4,32,17,25,38,0,25,20},
{13,10,3,25,14,24,34,0,24,11},
{32,2,0,17,9,17,31,1,29,5},
{35,4,2,16,10,16,41,4,31,5},
{31,12,9,15,6,11,37,8,37,7},
{16,12,15,12,5,8,25,18,28,6},
{14,17,28,12,5,12,22,21,18,5},
{14,19,33,12,9,11,12,25,12,14},
{9,30,32,17,9,9,7,31,3,15},
{3,33,30,7,19,5,3,30,7,15},
{6,30,21,14,28,13,2,24,19,20},
{13,32,19,19,30,18,4,29,20,26},
{22,17,14,22,36,22,16,22,18,24},
{32,21,14,24,31,23,24,17,24,18},
{21,18,9,27,28,28,32,0,23,17},
{19,13,9,34,22,22,36,0,24,22},
{21,11,9,32,17,25,35,0,25,18},
{7,10,9,20,13,23,23,0,22,10},
{24,2,2,21,6,25,34,1,34,9},
{33,9,10,23,6,24,42,8,40,12},
{26,12,18,29,5,22,37,8,35,10},
{22,15,30,20,5,21,25,18,26,7},
{18,17,35,16,5,11,15,27,17,15},
{13,18,35,8,7,3,6,27,8,16},
{14,30,29,10,10,9,7,29,4,22},
{8,30,24,19,18,15,5,27,7,16},
{19,30,21,20,28,19,12,24,13,24},
{21,24,17,22,24,22,13,27,22,21},
{31,17,18,24,34,23,19,19,30,17},
{18,21,13,27,29,20,26,2,31,15},
{19,18,17,36,25,20,32,0,24,19},
{20,13,16,32,22,24,32,0,21,20},
{20,10,19,25,17,24,35,0,22,11},
{5,10,15,11,18,11,12,0,15,10},
{14,12,9,27,0,18,14,6,27,9},
{31,19,24,37,0,41,37,9,40,12},
{32,20,33,36,0,34,38,21,30,17},
{23,22,40,33,0,27,28,24,26,13},
{22,20,37,32,0,25,25,25,19,20},
{21,32,31,22,6,19,18,28,18,20},
{23,33,27,21,9,15,17,31,15,23},
{20,26,26,21,19,15,15,26,14,20},
{20,21,26,21,28,23,15,27,18,23},
{32,21,26,25,23,24,18,23,19,17},
{19,22,23,26,27,20,30,18,24,19},
{18,24,17,34,28,19,31,2,28,18},
{17,22,21,32,24,23,25,0,17,15},
{19,19,22,24,17,23,31,0,22,14},
{5,17,25,8,12,13,16,0,19,9},
{2,14,16,2,12,2,3,0,5,5},
{6,17,21,24,0,26,12,6,15,3},
{19,21,37,31,0,32,15,21,27,12},
{25,21,40,40,0,41,35,22,37,16},
{35,23,38,38,0,43,40,24,37,28},
{33,34,39,35,0,29,33,29,29,27},
{37,32,35,29,6,21,32,30,33,24},
{32,29,35,27,10,17,26,29,29,22},
{33,24,36,28,21,21,29,27,25,27},
{18,21,39,28,27,23,29,25,20,21},
{19,25,38,29,25,19,23,21,21,19},
{18,26,38,34,27,18,24,11,19,18},
{22,28,35,29,28,23,25,1,21,16},
{16,28,34,17,26,19,21,0,21,10},
{5,20,34,7,17,6,14,0,13,10},
{2,18,28,0,13,1,3,0,4,8},
{0,17,18,0,12,1,2,0,1,2},
{0,18,26,13,0,11,0,9,2,0},
{0,25,22,18,0,20,0,16,4,3},
{6,22,26,12,0,21,6,19,13,8},
{6,25,26,13,0,16,11,17,21,13},
{17,23,27,23,0,23,22,20,25,23},
{18,25,26,25,2,22,27,21,29,17},
{15,20,26,28,16,23,30,23,31,19},
{20,19,28,29,18,22,32,22,24,17},
{24,26,29,20,27,22,32,21,21,15},
{16,27,30,16,17,19,17,18,18,9},
{6,28,30,7,26,10,14,3,11,6},
{1,21,27,2,26,1,3,1,5,7},
{0,20,30,2,26,1,2,0,1,1},
{0,20,25,0,18,0,0,0,0,0},
{0,19,26,0,15,0,0,0,0,0},
{0,13,17,0,13,0,0,0,0,0},
{23,43,38,37,32,28,16,40,20,33},
{6,16,6,14,20,23,34,3,20,4},
{31,22,25,13,5,14,34,30,28,14},
{15,18,11,18,31,32,18,21,14,35},
{0,2,0,4,0,1,0,14,0,0},
{0,2,0,2,0,2,0,14,0,0},
{0,2,0,8,0,2,2,7,0,1},
{0,2,0,8,0,2,2,7,0,1},
{0,3,0,7,0,6,2,8,1,1},
{0,3,0,2,0,5,0,7,0,0},
{0,5,0,2,0,5,0,9,0,0},
{2,4,0,2,0,5,1,11,0,0},
{2,2,0,0,0,0,1,9,1,3},
{0,2,0,0,0,0,0,2,0,0},
{0,2,0,0,0,0,0,2,0,0},
{0,2,0,0,0,0,0,0,0,0},
{0,2,0,0,0,0,0,0,0,0},
{0,2,0,0,0,0,0,0,0,1},
{0,2,0,0,0,0,0,0,0,1},
{0,3,0,0,0,0,0,0,0,1},
{0,7,0,0,0,0,0,0,0,1},
{0,7,0,0,0,0,0,0,0,0},
{0,7,0,0,0,0,0,0,0,0},
{0,7,0,0,0,0,0,0,0,0},
{0,7,0,0,0,0,0,0,0,0},
{0,7,0,0,0,0,0,0,0,0},
{0,7,0,0,0,0,0,0,0,0},
{0,2,0,0,0,0,0,0,0,0},
{0,2,0,0,0,0,0,0,0,0},
{0,2,0,0,0,1,0,0,0,0},
{0,2,0,0,0,1,1,0,0,0},
{0,2,0,0,0,1,1,0,0,3},
{0,2,0,0,0,1,2,0,0,3},
{0,2,0,0,0,0,4,0,0,1},
{0,2,0,0,0,0,3,0,0,1},
{0,2,0,0,5,0,3,0,0,1},
{0,2,0,0,6,0,3,0,0,1},
{0,2,0,0,5,0,0,0,0,1},
{0,2,0,0,3,0,0,0,0,0},
{0,2,0,0,3,0,0,0,0,0},
{0,2,0,0,3,0,0,0,0,0},
{0,2,0,0,3,0,0,0,0,0},
{0,2,0,0,4,0,0,0,0,0},
{0,2,0,0,2,0,0,0,0,0},
{0,2,0,0,2,0,0,0,0,0},
{0,2,0,0,2,0,0,0,0,0},
{0,2,0,0,3,0,0,0,0,0},
{0,2,0,0,3,0,0,0,0,0},
{0,2,0,0,3,0,0,0,0,0},
{0,2,0,4,2,0,1,0,0,0},
{0,2,0,4,1,0,1,0,0,1},
{0,2,0,2,1,2,1,0,0,1},
{0,2,0,2,5,2,1,0,0,1},
{0,2,0,2,5,0,1,0,0,0},
{0,2,0,0,5,0,0,0,0,0},
{0,2,0,0,1,0,0,0,0,0},
{0,3,0,0,1,0,0,0,0,0},
{0,3,0,0,0,0,0,0,0,0},
{2,3,1,0,0,0,1,0,1,3},
{2,6,0,0,0,0,1,0,0,0},
{0,6,4,0,0,0,0,0,0,0},
{0,5,8,0,0,0,0,0,0,0},
{0,5,7,0,0,1,2,0,1,1},
{0,6,11,0,0,1,2,0,0,1},
{0,3,10,0,0,1,0,0,0,0},
{0,4,15,0,0,0,0,0,0,0},
{0,5,10,0,0,0,0,0,0,0},
{0,5,10,0,0,0,0,0,0,0},
{0,22,4,6,14,11,6,11,2,0},
{0,22,4,19,14,23,8,11,2,0},
{0,31,4,12,14,22,5,24,6,0},
{0,31,12,18,16,24,0,26,6,0},
{0,31,12,17,16,19,2,28,5,0},
{0,22,8,15,16,7,4,26,4,3},
{2,16,7,11,16,7,2,21,3,6},
{2,17,7,11,16,5,2,20,2,8},
{5,14,7,11,16,10,2,13,1,2},
{2,16,2,6,16,10,3,13,2,4},
{2,16,1,3,13,10,3,10,3,9},
{2,8,5,6,13,10,3,8,3,10},
{3,10,6,6,13,10,6,6,3,8},
{4,10,7,9,10,6,5,6,9,7},
{5,9,8,9,10,8,5,7,9,7},
{6,8,9,9,10,8,5,7,2,9},
{7,4,14,9,10,12,5,5,2,11},
{7,4,18,9,10,12,5,5,2,12},
{10,4,17,6,0,8,4,1,2,11},
{10,5,7,0,0,8,6,1,2,9},
{10,5,5,1,0,8,8,1,2,11},
{11,4,5,0,0,12,10,1,2,15},
{11,4,3,0,0,12,9,1,1,17},
{11,9,3,0,0,12,10,1,1,13},
{13,9,3,0,0,10,9,1,1,15},
{18,9,3,2,0,6,5,0,1,16},
{18,9,2,2,0,7,5,0,0,14},
{18,9,2,2,0,7,6,0,0,11},
{18,9,2,5,0,7,8,0,0,7},
{19,9,0,3,1,8,6,0,0,8},
{21,9,0,3,9,10,4,0,3,9},
{21,9,0,4,7,10,4,0,3,9},
{18,9,0,4,6,8,13,0,4,10},
{19,9,0,6,9,10,9,0,1,8},
{15,9,0,7,9,13,8,0,5,4},
{15,9,0,8,4,19,11,0,10,6},
{15,9,0,9,5,17,15,0,12,4},
{15,9,0,10,3,19,16,0,14,6},
{12,9,0,17,3,22,17,0,13,6},
{11,8,0,19,4,23,18,0,15,9},
{11,8,0,20,8,23,17,0,17,10},
{11,8,0,20,7,22,17,0,19,11},
{10,8,0,16,5,22,26,0,20,9},
{10,8,0,18,13,20,16,0,20,9},
{10,8,3,18,13,19,14,0,21,9},
{7,8,3,13,13,17,11,0,16,10},
{7,8,8,12,13,13,10,1,13,9},
{7,8,9,13,13,12,10,1,9,9},
{5,8,6,13,13,12,12,1,12,9},
{4,8,8,13,13,13,12,1,10,10},
{2,8,8,10,12,10,7,1,9,10},
{2,9,8,10,12,6,6,1,4,10},
{2,13,10,8,12,8,4,5,7,5},
{2,13,14,8,12,4,3,5,4,5},
{0,13,18,12,12,7,2,5,4,2},
{0,17,24,15,12,7,2,3,4,5},
{0,17,22,20,12,16,7,3,3,2},
{0,22,15,22,12,17,6,6,5,2},
{0,21,22,21,12,8,4,6,9,3},
{0,19,19,16,12,8,3,7,10,4},
{0,23,19,17,12,6,2,8,2,5},
{0,20,15,12,13,5,0,9,0,1},
{0,21,18,11,13,1,0,5,0,0},
{0,21,18,11,13,1,0,5,0,0},
{40,24,37,35,32,36,38,16,30,42},
{36,24,38,26,31,25,35,14,36,42},
{34,15,36,27,31,28,35,13,34,39},
{33,15,26,21,28,26,37,11,28,35},
{29,12,24,18,25,25,32,6,23,30},
{26,13,28,24,24,34,32,9,25,29},
{21,25,28,25,24,34,32,12,26,23},
{19,24,27,25,24,36,29,11,21,19},
{15,32,25,20,23,37,30,17,14,25},
{17,29,33,27,23,34,32,21,14,22},
{17,29,35,30,26,32,33,28,16,17},
{12,32,29,31,26,35,33,30,18,10},
{13,28,28,32,26,36,33,29,17,16},
{12,28,29,29,28,43,34,30,10,20},
{14,25,27,28,28,39,34,28,14,22},
{14,27,26,28,24,40,34,30,23,20},
{11,25,20,28,21,32,34,33,23,15},
{12,27,17,29,20,32,35,33,23,16},
{13,28,18,35,26,38,36,39,21,21},
{13,31,26,41,24,38,34,39,19,23},
{14,32,32,41,22,36,31,35,14,21},
{21,33,32,43,16,32,28,35,14,15},
{23,31,31,44,15,34,29,35,21,13},
{26,31,30,44,15,31,27,37,26,19},
{16,30,33,44,20,32,30,41,32,18},
{11,31,27,43,20,32,32,42,33,16},
{11,31,30,38,22,28,30,42,34,19},
{11,31,30,38,21,26,29,42,32,19},
{10,31,31,37,21,29,23,42,34,24},
{7,33,33,35,24,33,19,42,34,23},
{7,33,34,43,19,33,23,42,25,23},
{7,33,35,41,19,28,23,42,23,21},
{10,33,36,40,21,31,15,42,22,21},
{9,33,36,38,15,30,22,42,32,22},
{15,33,36,34,18,34,23,39,26,28},
{13,33,36,33,24,27,20,39,20,30},
{20,35,38,34,25,31,19,39,19,32},
{20,35,38,33,27,31,19,39,14,31},
{24,35,35,27,27,28,12,39,15,31},
{22,36,34,25,31,27,12,39,18,28},
{22,36,39,22,29,27,16,39,15,25},
{22,36,39,27,29,29,18,39,14,25},
{22,36,42,31,30,29,7,39,14,30},
{21,36,42,30,22,31,17,39,14,32},
{21,36,39,31,22,33,21,39,13,32},
{20,36,37,29,23,33,22,39,13,29},
{20,36,31,29,29,35,23,38,14,30},
{21,36,29,30,30,32,21,38,16,30},
{20,36,33,27,25,34,18,38,15,29},
{21,36,31,28,25,33,15,38,16,30},
{23,36,30,35,25,33,10,38,17,31},
{23,35,31,28,29,37,15,38,23,29},
{21,27,31,37,30,36,25,34,21,32},
{15,27,26,37,31,35,24,37,25,23},
{14,29,19,31,32,31,23,37,23,27},
{14,24,14,25,32,28,19,39,23,27},
{17,25,13,20,33,20,17,39,21,30},
{21,21,18,11,33,21,20,36,20,31},
{23,22,14,12,33,31,21,36,16,30},
{32,23,12,20,33,31,27,37,20,30},
{32,22,14,21,33,37,36,36,35,33},
{32,23,14,34,33,45,43,35,42,41},
{40,21,16,38,33,51,44,39,43,44},
{40,21,16,38,33,51,44,39,43,44},
{0,2,3,4,0,4,0,3,10,2},
{3,2,2,2,1,2,1,5,5,1},
{5,2,4,2,1,0,2,0,3,4},
{6,2,6,2,2,0,5,0,9,8},
{8,4,7,7,5,2,8,2,13,12},
{11,12,7,7,6,6,8,2,13,11},
{14,4,8,10,6,6,10,2,13,14},
{14,5,9,10,6,6,10,2,19,16},
{15,2,11,17,7,5,9,5,24,13},
{18,3,8,15,7,8,7,8,26,17},
{18,3,7,15,7,10,6,4,23,17},
{22,6,9,11,6,7,6,6,21,23},
{20,8,8,10,5,6,3,9,22,19},
{20,8,6,10,6,3,3,8,23,15},
{17,12,7,11,6,5,3,9,19,13},
{16,10,7,9,10,4,3,7,17,13},
{18,14,8,9,13,8,3,6,16,16},
{17,12,8,7,14,8,2,6,16,16},
{13,11,8,4,18,6,2,4,18,12},
{13,7,10,4,20,6,2,4,20,12},
{13,6,5,3,22,7,3,8,25,12},
{6,6,4,4,28,6,5,8,25,14},
{4,8,7,3,29,4,5,8,19,14},
{1,8,8,4,29,8,6,6,14,11},
{11,9,7,4,24,10,3,2,9,10},
{11,8,13,4,23,13,5,2,8,6},
{11,8,11,9,21,14,4,2,8,9},
{11,8,11,9,17,15,5,2,10,9},
{12,8,10,7,17,12,8,2,8,8},
{14,6,10,11,13,10,12,2,9,11},
{12,6,7,3,15,8,11,2,15,8},
{12,6,6,4,12,11,11,2,17,10},
{12,6,6,5,9,10,10,2,16,8},
{12,6,8,5,12,10,10,2,9,12},
{10,6,8,7,12,1,12,5,10,11},
{12,6,8,8,12,2,12,5,11,7},
{5,4,6,6,12,4,9,5,10,7},
{5,4,6,6,12,2,8,5,14,5},
{4,4,9,5,11,2,14,5,14,6},
{5,4,10,5,8,2,11,5,9,7},
{5,4,5,6,7,2,8,5,10,9},
{5,4,5,1,7,1,6,5,9,8},
{6,4,2,1,7,1,8,5,8,5},
{6,4,2,0,7,1,8,5,9,3},
{6,4,2,0,7,0,6,5,9,3},
{10,4,4,3,6,2,7,5,14,5},
{10,4,4,4,2,4,7,5,16,4},
{9,4,5,3,2,6,9,5,18,4},
{12,4,5,6,2,4,10,5,16,5},
{11,4,5,5,2,4,13,5,16,4},
{11,4,6,3,3,7,24,5,15,3},
{11,4,5,10,3,4,20,5,12,5},
{13,7,3,3,3,3,12,5,9,7},
{19,7,3,3,3,8,16,2,8,16},
{23,5,6,5,2,9,17,2,10,12},
{23,2,5,9,2,17,21,2,12,12},
{22,2,5,8,1,16,19,2,18,12},
{16,2,3,15,1,14,17,2,17,11},
{14,2,1,15,1,12,16,2,16,10},
{7,2,2,13,1,12,12,0,13,9},
{5,2,1,11,1,8,6,0,6,6},
{6,3,0,2,0,2,1,0,1,2},
{0,3,0,0,0,0,0,0,0,0},
{0,3,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0},
{2,0,0,0,0,0,0,0,1,0},
{2,0,0,1,0,0,0,0,1,1},
{0,0,0,1,0,0,0,0,1,0},
{0,0,0,1,0,0,0,0,1,0},
{0,0,0,0,0,0,0,0,3,0},
{0,0,0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,0,0,1,1},
{1,2,0,0,1,0,2,0,1,1},
{1,2,1,0,2,0,2,0,1,1},
{1,2,1,0,2,0,2,0,1,1},
{1,2,1,0,2,0,0,0,1,1},
{1,2,1,2,2,0,0,0,1,1},
{3,0,1,2,1,0,2,0,2,1},
{3,0,0,4,1,0,2,0,1,0},
{3,0,0,4,1,0,2,0,1,0},
{4,0,0,3,1,0,2,0,1,0},
{3,0,1,3,1,1,2,0,1,0},
{2,0,2,1,1,2,1,0,1,0},
{2,0,2,1,1,2,1,0,1,0},
{2,0,2,1,1,1,1,0,1,1},
{0,0,0,1,1,0,2,0,1,1},
{0,0,0,0,2,0,1,0,1,6},
{0,0,0,0,2,1,1,0,1,2},
{0,0,0,0,6,2,0,0,1,1},
{0,0,1,0,7,2,0,0,1,2},
{0,0,1,0,7,0,1,0,0,1},
{0,0,3,0,2,1,3,0,0,3},
{0,0,3,0,2,3,3,0,0,3},
{0,0,2,0,3,3,3,0,0,2},
{0,0,0,0,4,2,3,0,0,1},
{0,0,0,1,3,4,1,0,1,0},
{0,0,0,0,2,4,1,0,2,0},
{0,0,0,0,0,0,1,0,2,1},
{0,0,0,0,0,0,1,0,1,2},
{0,0,0,0,0,0,1,0,0,1},
{2,0,0,0,0,0,3,0,0,0},
{2,0,0,0,0,0,3,0,1,0},
{2,0,0,1,1,0,3,0,1,0},
{0,0,0,1,1,0,2,0,1,0},
{1,0,0,1,1,0,2,0,0,0},
{3,0,0,0,1,0,2,0,0,0},
{0,0,0,0,2,0,2,0,0,0},
{0,0,1,0,0,0,2,0,0,0},
{0,0,1,0,0,0,2,0,0,0},
{0,0,0,0,1,0,2,0,0,0},
{1,0,0,0,1,2,0,0,1,0},
{1,0,0,0,1,2,0,0,2,0},
{1,0,0,0,1,5,0,0,4,0},
{1,0,0,0,0,1,0,0,5,0},
{1,0,1,0,0,1,0,0,5,0},
{0,0,0,0,0,5,0,0,5,0},
{0,1,1,0,0,0,0,0,4,0},
{0,0,0,1,0,0,0,0,1,0},
{2,0,0,1,0,0,0,0,1,0},
{2,0,0,1,0,0,1,0,1,0},
{1,0,0,0,0,0,0,0,0,0},
{3,0,0,0,0,0,0,0,0,0},
{2,0,0,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,2,0,0,0,0,0,0,0,0},
{0,2,0,0,0,0,0,0,0,0},
{0,2,0,0,0,0,0,0,0,0},
{0,2,0,0,0,0,0,0,0,0},
{1,2,1,0,0,0,0,0,0,1},
{1,2,1,0,0,0,0,0,0,0},
{3,2,1,0,0,0,0,0,0,1},
{3,2,1,0,0,0,2,0,0,1},
{3,2,0,1,0,0,4,0,0,1},
{1,2,1,1,0,0,4,0,0,1},
{1,2,1,1,0,0,2,0,0,0},
{2,2,0,1,0,0,0,0,0,0},
{4,2,1,1,0,0,0,0,0,0},
{4,2,1,1,0,0,1,0,0,0},
{4,2,1,1,0,0,3,0,0,0},
{5,2,1,1,0,0,3,0,0,0},
{4,2,1,1,1,0,1,0,0,0},
{5,2,1,0,1,0,1,0,0,0},
{5,2,1,0,1,0,1,0,0,0},
{4,2,1,1,1,0,0,0,1,0},
{3,2,1,1,2,0,0,1,1,0},
{3,3,1,1,2,0,0,1,1,0},
{2,4,1,1,2,0,1,1,1,3},
{2,4,1,0,2,0,1,1,1,3},
{1,4,5,0,2,0,0,3,0,3},
{2,7,4,0,4,0,1,3,0,3},
{1,7,9,0,4,1,3,11,0,3},
{1,8,6,0,5,1,2,10,0,4},
{2,9,5,0,4,1,3,10,0,3},
{2,11,5,0,16,1,0,10,0,0},
{2,12,0,0,16,0,0,10,0,0},
{2,12,0,0,16,0,0,0,0,0},
{2,13,0,0,19,0,0,0,1,2},
{1,13,0,0,20,0,0,0,1,0},
{0,15,0,0,20,0,0,0,1,1},
{0,15,0,0,20,0,0,0,0,1},
{0,14,0,0,20,0,0,0,0,0},
{0,11,0,0,18,0,0,0,0,1},
{0,11,0,0,19,0,0,0,1,1},
{0,10,0,0,19,0,0,0,1,0},
{0,10,0,1,14,0,0,0,0,0},
{0,10,0,0,11,0,0,0,0,0},
{2,10,0,0,10,0,1,0,0,0},
{2,10,0,0,10,0,1,0,0,0},
{0,10,0,0,10,0,1,0,0,0},
{3,10,0,0,10,0,1,0,0,0},
{3,10,0,0,11,0,1,0,0,0},
{3,10,0,1,10,0,1,0,0,0},
{3,12,13,9,0,0,1,15,0,0},
{3,12,11,11,0,10,3,18,2,0},
{3,13,9,11,0,14,3,18,2,0},
{3,17,7,12,0,15,3,24,2,2},
{3,16,5,4,0,15,5,23,3,2},
{3,16,5,4,0,16,3,23,3,0},
{1,13,9,5,0,17,6,22,1,0},
{1,13,9,4,0,13,7,22,0,0},
{1,13,9,4,0,6,4,25,1,1},
{1,15,9,2,0,5,1,25,1,1},
{1,16,9,3,0,5,0,21,3,0},
{0,17,8,1,0,4,0,21,3,0},
{0,11,12,4,0,4,0,16,3,0},
{1,11,12,3,0,1,9,16,3,0},
{2,10,8,3,0,2,0,18,4,0},
{1,10,8,2,0,2,0,18,4,0},
{2,10,8,7,0,4,1,15,4,0},
{3,10,4,7,0,2,2,15,0,0},
{7,11,9,2,10,2,2,14,0,0},
{8,12,4,4,14,4,2,14,0,0},
{8,12,12,2,15,0,1,13,0,0},
{11,16,12,2,15,2,2,13,0,0},
{15,10,12,6,9,2,1,13,0,0},
{17,10,14,2,11,5,1,13,0,0},
{17,13,7,8,11,5,1,11,0,2},
{12,17,9,8,22,4,1,11,0,2},
{10,20,4,8,18,2,0,3,0,2},
{15,19,10,8,18,2,0,4,0,2},
{12,16,9,4,20,2,0,2,0,2},
{10,15,10,9,7,2,0,2,0,5},
{3,15,7,9,7,2,1,3,0,5},
{6,11,7,9,7,2,1,13,0,5},
{8,13,6,9,5,2,0,17,2,4},
{7,8,5,0,5,0,0,17,2,2},
{7,6,5,0,5,0,0,17,0,2},
{5,7,9,0,5,0,0,17,3,0},
{0,9,9,0,4,1,0,20,4,0},
{0,14,4,0,7,1,2,23,6,0},
{0,19,4,0,3,0,2,24,7,0},
{0,19,4,0,3,2,0,21,6,1},
{0,21,4,0,3,4,0,24,6,1},
{0,20,1,0,5,7,0,26,5,0},
{0,20,1,5,5,7,0,24,5,0},
{0,22,0,5,3,7,1,25,5,0},
{0,26,6,5,4,12,4,23,6,0},
{0,22,6,14,4,13,7,23,5,0},
{0,21,11,13,4,12,5,23,2,0},
{0,21,11,13,4,12,5,23,2,0},
{38,32,26,35,45,41,44,29,29,36},
{36,32,25,27,44,31,44,26,23,31},
{36,29,26,25,43,27,44,23,22,31},
{39,25,26,20,43,25,43,17,20,25},
{35,25,28,29,39,29,39,17,18,22},
{28,25,27,28,34,27,39,17,18,23},
{24,25,19,27,32,18,36,18,16,24},
{20,25,19,27,33,19,28,17,13,23},
{26,25,21,27,28,26,22,15,10,16},
{21,21,20,30,29,24,24,15,7,14},
{20,17,20,29,29,20,25,19,7,10},
{20,19,20,24,23,22,25,19,11,10},
{23,21,14,9,23,17,22,18,14,8},
{26,24,14,9,21,19,8,18,14,9},
{25,25,18,14,22,16,18,12,14,9},
{25,27,19,15,19,17,20,12,16,10},
{17,27,18,12,28,14,19,14,18,10},
{14,24,19,15,25,17,17,14,17,13},
{12,27,18,22,17,17,16,12,17,12},
{11,26,22,23,12,14,19,12,21,14},
{11,29,14,26,11,18,20,18,21,17},
{7,21,14,27,12,16,20,17,17,17},
{2,26,14,14,20,14,19,16,18,14},
{0,26,12,18,20,9,19,16,21,14},
{4,28,16,13,21,19,21,17,14,16},
{14,14,15,14,9,9,22,17,12,15},
{19,11,15,13,9,14,14,15,11,18},
{14,13,14,11,9,16,12,15,17,20},
{15,15,15,18,14,13,13,14,18,20},
{14,14,13,11,15,12,13,14,16,20},
{18,13,18,11,18,16,12,13,18,17},
{15,19,17,11,21,16,13,17,16,17},
{16,22,19,7,20,14,11,13,15,17},
{16,27,20,15,20,17,14,13,9,24},
{16,19,22,11,20,18,4,13,11,27},
{18,18,18,11,17,18,5,15,11,30},
{22,24,19,12,17,19,5,14,7,28},
{22,22,23,12,13,22,4,13,7,27},
{24,19,27,14,18,35,5,16,14,28},
{26,20,23,20,20,33,10,22,16,32},
{25,18,27,24,24,31,27,20,19,30},
{25,19,33,27,25,30,27,18,14,36},
{28,19,33,24,22,34,28,20,14,38},
{37,18,31,32,27,39,28,19,17,38},
{36,14,30,35,26,35,25,21,17,38},
{38,17,28,28,28,34,23,21,22,38},
{38,18,25,31,32,38,26,21,27,43},
{38,18,25,31,32,38,26,21,27,43},
{2,4,5,6,1,7,0,0,14,8},
{4,4,8,12,2,11,0,0,19,13},
{4,6,9,13,3,11,0,3,19,13},
{0,6,11,17,2,12,1,3,12,16},
{4,7,10,16,6,11,0,4,12,16},
{4,7,8,17,11,11,0,4,12,16},
{8,10,12,17,12,13,0,4,15,15},
{14,10,12,16,12,16,6,5,27,13},
{13,10,11,14,17,14,11,4,25,18},
{16,10,9,12,16,16,9,4,21,18},
{17,13,8,12,16,19,9,4,19,23},
{16,10,9,14,22,17,9,4,12,27},
{12,14,11,14,22,16,5,10,16,29},
{8,11,9,15,24,17,8,10,17,25},
{8,11,9,15,23,20,11,14,16,24},
{9,9,7,16,26,19,10,11,17,24},
{17,10,8,14,14,19,11,12,19,21},
{19,13,10,8,16,25,15,12,24,18},
{17,10,3,7,16,23,16,18,21,22},
{17,10,4,8,19,26,14,17,17,20},
{18,7,4,9,18,26,13,11,10,17},
{19,10,4,9,15,24,12,13,14,13},
{21,10,10,19,12,24,13,14,13,13},
{21,10,11,16,12,24,13,14,9,13},
{18,5,11,15,12,15,7,10,21,11},
{12,12,9,14,11,26,4,10,15,11},
{10,12,9,15,15,26,13,12,13,11},
{10,10,9,18,15,25,15,15,16,6},
{9,10,7,15,9,27,15,18,14,6},
{12,10,7,13,9,26,7,15,17,6},
{14,10,9,13,6,20,14,15,13,9},
{14,8,11,12,2,23,14,11,10,9},
{7,2,8,12,2,24,18,11,10,10},
{12,2,8,11,1,23,18,14,11,10},
{13,10,9,12,1,21,28,14,14,5},
{13,10,11,20,4,25,25,12,10,0},
{14,3,10,22,5,25,27,10,22,4},
{14,3,12,21,8,23,26,8,20,9},
{11,1,11,28,6,13,26,4,10,8},
{10,1,15,26,4,15,28,1,11,5},
{12,1,12,23,5,15,12,0,10,12},
{13,1,10,20,5,14,12,0,17,7},
{10,1,10,19,9,10,12,0,21,5},
{3,0,12,11,6,5,14,0,20,5},
{2,0,8,8,6,4,13,0,19,6},
{0,1,10,6,4,4,14,0,15,6},
{2,1,8,5,0,1,13,0,14,1},
{2,1,8,5,0,1,13,0,14,1},
{0,0,0,0,0,4,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0},
{1,0,0,0,1,0,0,0,9,1},
{1,0,1,0,1,1,3,0,11,4},
{6,0,4,0,1,2,3,0,11,5},
{6,0,4,0,2,4,3,0,11,5},
{5,0,3,0,1,4,4,0,1,8},
{0,0,2,0,1,1,6,0,4,9},
{0,2,4,1,1,2,9,0,11,10},
{2,2,5,0,0,2,9,0,12,10},
{2,2,4,5,0,5,9,0,15,6},
{2,2,4,13,0,12,14,0,8,6},
{1,2,6,11,0,12,15,0,7,9},
{0,2,6,8,0,11,11,0,8,10},
{0,2,7,7,1,11,10,3,5,9},
{0,1,7,15,4,14,9,3,2,12},
{0,1,9,18,5,7,6,3,1,12},
{0,0,12,17,3,7,6,0,4,9},
{0,0,12,13,0,7,7,1,4,7},
{0,0,12,10,0,7,8,1,11,4},
{0,0,12,9,2,9,8,0,11,10},
{0,0,6,7,3,11,8,0,11,10},
{0,0,5,10,1,13,8,0,12,10},
{0,0,6,10,1,10,13,3,7,8},
{2,0,6,11,1,12,15,3,15,9},
{2,0,6,6,1,9,15,3,18,9},
{2,0,6,5,1,8,15,0,9,12},
{0,0,7,5,0,9,14,0,9,12},
{0,0,8,9,0,11,22,3,9,12},
{0,0,9,9,0,11,15,3,9,12},
{2,0,8,10,1,8,13,3,13,12},
{5,0,10,13,1,7,12,3,11,12},
{0,0,11,13,1,7,9,0,15,8},
{3,0,8,18,1,8,9,0,11,9},
{3,0,6,10,1,8,12,0,14,13},
{3,0,5,11,1,6,9,0,7,11},
{3,0,4,13,1,5,10,0,6,7},
{4,0,1,5,1,3,9,0,7,7},
{3,0,1,2,1,1,4,0,3,6},
{3,0,0,1,0,1,3,0,4,1},
{2,0,0,1,0,0,3,0,3,1},
{2,0,0,0,0,0,2,0,1,1},
{0,0,1,1,0,0,0,0,0,1},
{2,0,0,1,0,0,0,0,0,0},
{2,0,0,1,0,0,0,0,1,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0}};

    
    int n, m;
    int komp;
    int been[max_n][max_m];
    int dim[max_obj][6];
    string pict[max_n], number[max_n];
    int number_n, number_m;
    int signal[max_neuro];
    string ans;
    
void neuro_view()
{
    int i, j, adr;
    for (i = 0; i < a_elem; i++)
    {
        signal[i] = 0;
    }    

    for (i = 0; i < d_n; i++)
    {
        for (j = 0; j < d_m; j++)
        {
            if (number[i][j] != '.')
            {
                adr = (i/window_n)*(d_m/window_m) + (j/window_m);
                signal[adr]++;
            }
        }
    }                
    for (i = 0; i < s_elem; i++)
    {
        if (signal[i] > s_teta)
        {
            signal[i] = 1;
        }
        else
        {
            signal[i] = 0;
        }
    }
    
    for (i = 0; i < d_n; i++)
    {
        for (j = 0; j < d_m; j++)
        {
            adr = (i/window_n)*(d_m/window_m) + (j/window_m);            
            if (i < d_n/2)
            {
                if (j < d_m/2)
                {
                    signal[s_elem + 0] -= signal[adr];
                    signal[s_elem + 3] += signal[adr];
                }    
                else
                {
                    signal[s_elem + 1] -= signal[adr];
                    signal[s_elem + 0] += signal[adr];
                }    
            }
            else
            {
                if (j < d_m/2)
                {
                    signal[s_elem + 3] -= signal[adr];
                    signal[s_elem + 2] += signal[adr];
                }    
                else
                {
                    signal[s_elem + 2] -= signal[adr];
                    signal[s_elem + 1] += signal[adr];
                }    
            }    
        }
    }                
    for (i = 0; i < 4; i++)
    {
        if (signal[s_elem + i] > 0)
        {
            signal[s_elem + i] = signal[s_elem + i] / (window_n * window_m);
        }
        else
        {
            signal[s_elem + i] = 0;
        }
    }            
    
    int x;
    bool white;
    for (i = 0; i < d_n; i++)
    {
        x = 0;
        white = false;
        for (j = 0; j < d_m; j++)
        {
            if (number[i][j] == '.')
            {
                if (!white)
                {
                    white = true;
                    x++;
                }
            }
            else
            {
                white = false;
            }
        }
        signal[s_elem + 4 + d_n*x + i] = 1;
    }                    
    for (j = 0; j < d_m; j++)
    {
        x = 0;
        white = false;
        for (i = 0; i < d_n; i++)
        {
            if (number[i][j] == '.')
            {
                if (!white)
                {
                    white = true;
                    x++;
                }
            }
            else
            {
                white = false;
            }
        }
        signal[s_elem + 4 + d_n*5 + d_m*x + j] = 1;
    }                    
    
}    

int neuro_recogn()
{
    int i, j, answer;
    int ans_signal[signs_n];
    for (j = 0; j < signs_n; j++)
    {
        ans_signal[j] = 0;
    }    
    
    for (i = 0; i < a_elem; i++)
    {
        if (signal[i] > a_teta)
        {
            for (j = 0; j < signs_n; j++)
            {
                ans_signal[j] += (weight[i][j] * signal[i]);
            }
        }    
    }    
    
    answer = 0;
    for (i = 1; i < 10; i++)
    {
        if (ans_signal[i] > ans_signal[answer])
        {
            answer = i;
        }
    }
    return answer;
}    

void data_read()
{
    n = 0; m = 0;
    while (!cin.eof())
    {
        cin >> pict[n];
        if ((pict[n][0] != '.') && (pict[n][0] != '%')
        && (pict[n][0] != '#') && (pict[n][0] != '@'))
        {
            break;
        }
        else
        {
            n++;
        }    
    }    
    m = pict[0].length();
}

void data_answer_out()
{
    cout << ans;
}    
    
void data_clear_columns()
{
    int i, j, sum;
    for (j = 0; j < m; j++)
    {
        sum = 0;
        for (i = 0; i < n; i++)
        {
            if (pict[i][j] == '@') {sum++;}
            if (pict[i][j] == '#') {sum++;}
        }
        if (sum == 0)
        {
            for (i = 0; i < n; i++)
            {
                pict[i][j] = '.';
            }
        }
    }
}                    

void data_init(string s[], int x, int y)
{
    int i, j;
    for (i = 0; i < x; i++)
    {
        s[i] = "";
        for (j = 0; j < y; j++)
        {
            s[i] += '.';
        }
    }
}            

void data_resize()
{
    int i, j, x, s, p;
    int step, pen;
    string tmp[max_n];

//resize columns || (number_n, number_m) -> (d_n, number_m)
    data_init(tmp, d_n, d_m);
    s = d_n; p = 0;
    for (i = 0; i < number_n; i++)
    {
        for (x = 0; x < (s / number_n); x++)
        {
            for (j = 0; j < number_m; j++)
            {
                tmp[p][j] = number[i][j]; 
            }
            p++;
        }   
        s = (s % number_n) + d_n;
    }     
    
//resize strings = (d_n, number_m) -> (d_n, d_m)    
    data_init(number, d_n, d_m);
    s = d_m; p = 0;
    for (j = 0; j < number_m; j++)
    {
        for (x = 0; x < (s / number_m); x++)
        {
            for (i = 0; i < d_n; i++)
            {
                number[i][p] = tmp[i][j]; 
            }
            p++;
        }   
        s = (s % number_m) + d_m;
    }     
}    

void bfs(int x, int y, int sv)
{
    int stek[max_n*max_m][2];
    int begin, end, a, b, u, i, j;
    begin = 0;
    end = 1;
    stek[0][0] = x;
    stek[0][1] = y;
    been[x][y] = sv;
    //1 - verh, 2 - pravo, 3 - niz, 4 - levo
    dim[sv][0] = 0;
    dim[sv][1] = x;
    dim[sv][2] = y;
    dim[sv][3] = x;
    dim[sv][4] = y;
    dim[sv][5] = 0;
    while (begin < end)
    {
        dim[sv][0]++;
        a = stek[begin][0];
        b = stek[begin][1];
        if (dim[sv][1] > a) {dim[sv][1] = a;}
        if (dim[sv][2] < b) {dim[sv][2] = b;}
        if (dim[sv][3] < a) {dim[sv][3] = a;}
        if (dim[sv][4] > b) {dim[sv][4] = b;}     
        for (u = 0; u < 8; u++)
        {
            i = a + dir[u][0];
            j = b + dir[u][1];
            if ((i >= 0) && (i < n) && (j >= 0) && (j < m))
            {
                if ((pict[i][j] != '.') && (been[i][j] == -1))
                {
                    stek[end][0] = i;
                    stek[end][1] = j;
                    been[i][j] = sv;
                    end++;
                }    
            }    
        }
        begin++;    
    }    
}    

void predproc()
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            been[i][j] = -1;
        }
    }        
    komp = 0;
    
    data_clear_columns();    
    for (j = 0; j < m; j++)
    {
        for (i = 0; i < n; i++)    
        {
            if ((pict[i][j] != '.') && (been[i][j] == -1))
            {
                bfs(i, j, komp);
                komp++;
            }
        }
    }
    
    for (i = 0; i < komp; i++)
    {
        if (dim[i][0] < (destroy_rate*n*m / 100))
        {
            dim[i][5] = 1;
        }    
    }    
    for (i = 0; i < komp; i++)
    {
        for (j = 0; j < komp; j++)
        {
            
            if ((dim[i][1] < dim[j][1]) && (dim[i][2] > dim[j][2])
            && (dim[i][3] > dim[j][3]) && (dim[i][4] < dim[j][4]))
            {
                if (dim[j][5] != 1)
                {
                    dim[i][5] = 1;
                }    
            }
        }
    }            
    
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (pict[i][j] != '.')
            {
                if (dim[been[i][j]][5] == 1)
                {
                    pict[i][j] = '.';
                }    
            }
        }
    }
}    

void get_number_and_go()
{
    int i, j, u, k = 0;
    for (u = 0; u < komp; u++)
    {
        if (dim[u][5] != 1)
        {
            for (i = dim[u][1]; i <= dim[u][3]; i++)
            {
                number[i - dim[u][1]] = "";
                for (j = dim[u][4]; j <= dim[u][2]; j++)
                {
                    
                    if (been[i][j] == u)
                    {
                        number[i - dim[u][1]] += '@';
                    }
                    else
                    {
                        number[i - dim[u][1]] += '.';                        
                    }    
                }
            }
            number_n = dim[u][3] - dim[u][1] + 1;
            number_m = dim[u][2] - dim[u][4] + 1;
            data_resize();
            
            neuro_view();
            ans += (neuro_recogn() + '0');
        }    
    }    
}    

int main()
{
    // 1 - obu4enie, 0 - raspoznavanie
    data_read();
    predproc();
    predproc();
    ans = "";
    get_number_and_go();
    data_answer_out();
    return 0;
}
    
    
