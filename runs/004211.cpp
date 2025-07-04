#include <iostream>
#include <vector>
#include <new>
#include <cstdlib>
#include <cmath>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::floor;

inline int color(char c);
const int N[10][20][14] = {
		{ // 0
			{0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 0},
			{0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0},
			{0, 0, 1, 3, 3, 2, 2, 2, 2, 3, 3, 1, 0, 0},
			{0, 1, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 1, 0},
			{0, 3, 3, 2, 0, 0, 0, 0, 0, 0, 2, 3, 3, 0},
			{1, 3, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 3, 1},
			{1, 3, 2, 0, 0, -1, -2, -2, -1, 0, 0, 2, 3, 1},
			{1, 3, 2, 0, 0, -2, -5, -5, -2, 0, 0, 2, 3, 1},
			{1, 3, 2, 0, 0, -2, -5, -5, -2, 0, 0, 2, 3, 1},
			{1, 3, 2, 0, 0, -2, -5, -5, -2, 0, 0, 2, 3, 1},
			{1, 3, 2, 0, 0, -2, -5, -5, -2, 0, 0, 2, 3, 1},
			{1, 3, 2, 0, 0, -1, -4, -4, -1, 0, 0, 2, 3, 1},
			{1, 3, 2, 0, 0, -1, -2, -2, 0, 0, 0, 2, 3, 1},
			{1, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 1},
			{1, 3, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 3, 1},
			{0, 3, 3, 2, 0, 0, 0, 0, 0, 0, 2, 3, 2, 0},
			{0, 1, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 1, 0},
			{0, 0, 1, 3, 2, 2, 2, 2, 2, 2, 3, 1, 0, 0},
			{0, 0, 0, 2, 3, 3, 3, 3, 3, 3, 2, 0, 0, 0},
			{0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 0}
		},
		{ // 1
			{0, 0, 0, 0, 0, 1, 1, 3, 2, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 1, 2, 2, 3, 2, 1, 0, 0, 0, 0},
			{0, 0, 1, 1, 2, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{1, 1, 2, 2, 2, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{-5, -3, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{-5, -3, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{-5, -4, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{-5, -4, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{-5, -5, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{-5, -5, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{-5, -5, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{-5, -5, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{-5, -5, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 1, 2, 3, 3, 2, 1, 0, -1, -5, -5},
			{0, 0, 0, 0, 1, 2, 3, 3, 2, 1, 0, -1, -5, -5},
			{0, 0, 0, 0, 1, 2, 3, 3, 2, 2, 0, 0, 0, 0},
			{0, 1, 1, 2, 2, 3, 3, 3, 3, 2, 2, 1, 1, 0},
		},
		{ // 2
			{0, 0, 0, 0, 1, 2, 2, 3, 2, 1, 0, 0, 0, 0},
			{0, 0, 1, 1, 3, 3, 3, 3, 3, 2, 1, 0, 0, 0},
			{0, 1, 2, 3, 2, 1, 1, 1, 1, 3, 2, 1, 0, 0},
			{1, 2, 3, 1, 1, 0, 0, 0, 0, 1, 3, 2, 1, 0},
			{1, 3, 2, 0, 0, 0, 0, 0, 0, 1, 2, 3, 1, 0},
			{1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 2, 3, 2, 1},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 2},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 2, 1},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 1, 3, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
			{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
			{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
		},
		{ // 3
			{-3, -2, 0, 0, 1, 1, 2, 3, 2, 1, 0, 0, 0, 0},
			{-2, -1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 0, 0, 0},
			{0, 1, 2, 3, 3, 2, 1, 1, 2, 3, 3, 1, 0, 0},
			{1, 3, 3, 1, 1, 0, 0, 0, 0, 1, 3, 3, 1, 0},
			{2, 3, 2, 0, 0, 0, 0, 0, 0, 1, 2, 3, 2, 0},
			{1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 3, 2, 1},
			{0, 0, 0, 0, -3, -3, -1, 0, 0, 0, 2, 3, 1, 0},
			{0, 0, 0, -1, -3, -3, -1, 0, 0, 1, 3, 3, 1, 0},
			{0, 0, 0, -1, -1, 0, 0, 0, 1, 3, 3, 1, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0},
			{-5, -3, -1, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0},
			{-5, -3, -1, 0, 0, 1, 3, 3, 3, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 1, 1, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0},
			{1, 2, 1, 0, 0, -2, -2, 0, 0, 0, 1, 3, 3, 2},
			{2, 3, 2, 0, 0, -2, -3, 0, 0, 0, 1, 3, 3, 2},
			{1, 3, 3, 2, 1, 0, 0, 0, 0, 1, 2, 3, 2, 0},
			{0, 1, 3, 3, 3, 2, 1, 2, 2, 3, 3, 2, 1, 0},
			{0, 0, 1, 1, 3, 3, 3, 3, 3, 2, 1, 1, 0, 0},
			{0, 0, 0, 0, 1, 2, 3, 2, 1, 1, 0, 0, 0, 0}
		},
		{ // 4
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 2, 1, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 2, 1, 0},
			{0, 0, 0, -1, 0, 0, 0, 0, 1, 2, 3, 2, 1, 0},
			{0, 0, 0, -1, 0, 0, 0, 0, 1, 2, 3, 2, 1, 0},
			{0, 0, -1, 0, 0, 0, 0, 1, 3, 2, 3, 2, 1, 0},
			{0, -1, 0, 0, 0, 0, 0, 1, 3, 2, 3, 2, 1, 0},
			{0, 0, 0, 0, 0, 0, 1, 3, 0, 2, 3, 2, 1, 0},
			{0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 3, 2, 1, 0},
			{0, 0, 0, 0, 0, 1, 3, 0, 0, 2, 3, 2, 1, 0},
			{0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 3, 2, 1, 0},
			{0, 0, 0, 0, 1, 3, 0, 0, 0, 2, 3, 2, 1, 0},
			{0, 0, 0, 1, 3, 0, 0, 0, 0, 2, 3, 2, 1, 0},
			{0, 0, 1, 3, 0, 0, 0, 0, 0, 2, 3, 2, 1, 0},
			{0, 1, 2, 1, 1, 1, 1, 1, 1, 2, 3, 2, 1, 0},
			{1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 2, 2, 1},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 0},
			{0, -2, -3, -2, 0, 0, 0, 0, 0, 2, 2, 2, 1, 0},
			{0, -2, -1, -1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1}
		},
		{ // 5
			{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
			{2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2},
			{2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
			{2, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{2, 3, 1, 0, -1, -2, -3, -3, -1, 0, 0, 0, 0, 0},
			{2, 3, 1, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0},
			{2, 3, 1, 0, 1, 1, 3, 3, 3, 1, 1, 0, 0, 0},
			{2, 3, 1, 1, 3, 3, 1, 1, 3, 3, 3, 1, 0, 0},
			{2, 3, 3, 3, 1, 1, 0, 0, 1, 1, 3, 3, 1, 0},
			{2, 3, 3, 1, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0},
			{-1, -1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1},
			{-3, -2, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 2},
			{-3, -2, -1, -1, -2, -2, -2, -1, 0, 0, 0, 1, 3, 3},
			{-1, -1, 0, 0, -1, -3, -3, -1, 0, 0, 0, 1, 3, 2},
			{1, 2, 1, 0, 0, 0, -1, -1, 0, 0, 1, 2, 3, 1},
			{1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1},
			{1, 3, 3, 1, 1, 0, 0, 0, 0, 1, 3, 3, 1, 0},
			{0, 1, 3, 3, 3, 1, 1, 1, 1, 3, 3, 1, 1, 0},
			{0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0},
			{0, 0, 0, 0, 1, 1, 2, 3, 2, 1, 0, 0, 0, 0}
		},
		{ // 6
			{0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 0},
			{0, 0, 0, 1, 1, 3, 3, 3, 3, 1, 1, 0, 0, 0},
			{0, 0, 1, 3, 3, 3, 1, 1, 3, 3, 3, 1, 0, 0},
			{0, 1, 3, 3, 1, 1, 0, 0, 1, 1, 3, 3, 1, 0},
			{0, 1, 3, 1, 0, 0, -1, -1, 0, 0, 1, 3, 3, 0},
			{1, 3, 3, 1, 0, 0, -3, -3, 0, 0, 0, 1, 3, 1},
			{1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
			{2, 3, 1, 0, 1, 1, 2, 2, 1, 1, 0, 0, 0, 0},
			{2, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0},
			{2, 3, 3, 2, 2, 2, 2, 2, 2, 2, 3, 3, 1, 0},
			{2, 3, 2, 1, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1},
			{2, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 2},
			{2, 3, 2, 0, 0, -1, -4, -4, -1, 0, 0, 1, 3, 2},
			{1, 3, 3, 0, 0, -1, -4, -4, -1, 0, 0, 2, 3, 1},
			{0, 1, 3, 1, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0},
			{0, 1, 3, 3, 2, 1, 0, 0, 1, 1, 3, 3, 1, 0},
			{0, 0, 1, 3, 3, 3, 1, 2, 3, 3, 3, 1, 0, 0},
			{0, 0, 0, 1, 1, 3, 3, 3, 3, 1, 1, 0, 0, 0},
			{0, 0, 0, 0, 0, 1, 2, 3, 1, 0, 0, 0, 0, 0}
		},
		{ // 7
			{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
			{2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2},
			{2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 2},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 2, 1},
			{0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 3, 1, 1, 0},
			{0, 0, 0, 0, 0, 0, 1, 2, 3, 3, 1, 0, 0, 0},
			{0, 0, 0, 0, 0, 1, 2, 3, 3, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 1, 2, 3, 1, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 1, 2, 3, 3, 1, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 1, 2, 3, 3, 1, 0, 0, 0, 0, 0},
			{0, 0, 0, 1, 2, 3, 3, 1, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 1, 2, 3, 1, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 1, 2, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 1, 2, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 1, 2, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 1, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 1, 2, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 1, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 2, 3, 2, 1, 0, 0, 0, 0, 0, -2, -2, -2, -2},
			{0, 2, 3, 2, 1, 0, 0, 0, 0, -2, -2, -2, -2, -2}
		},
		{ // 8
			{0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 0},
			{0, 0, 0, 1, 1, 3, 3, 3, 3, 1, 1, 0, 0, 0},
			{0, 0, 1, 2, 3, 3, 2, 2, 3, 3, 3, 1, 0, 0},
			{0, 0, 1, 3, 1, 1, 0, 0, 1, 1, 3, 1, 0, 0},
			{0, 1, 3, 2, 0, 0, 0, 0, 0, 0, 2, 3, 1, 0},
			{0, 2, 3, 2, 0, 0, -4, -4, 0, 0, 2, 3, 2, 0},
			{0, 1, 3, 2, 0, 0, -3, -3, 0, 0, 2, 3, 1, 0},
			{0, 1, 3, 3, 1, 0, 0, 0, 0, 1, 3, 3, 1, 0},
			{0, 0, 1, 3, 2, 1, 0, 0, 1, 2, 3, 1, 0, 0},
			{0, 0, 1, 3, 3, 3, 2, 2, 3, 3, 3, 1, 0, 0},
			{0, 0, 1, 3, 3, 3, 2, 2, 3, 3, 3, 1, 0, 0},
			{0, 1, 3, 3, 3, 1, 0, 0, 1, 2, 3, 3, 1, 0},
			{1, 3, 3, 1, 1, 0, 0, 0, 0, 0, 1, 3, 3, 2},
			{2, 3, 3, 2, 0, 0, -3, -3, 0, 0, 2, 3, 3, 2},
			{1, 3, 3, 2, 0, -2, -5, -5, -2, 0, 2, 3, 3, 1},
			{0, 1, 3, 2, 0, 0, -1, -1, 0, 0, 2, 3, 1, 0},
			{0, 1, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 1, 0},
			{0, 0, 1, 3, 3, 3, 2, 2, 2, 3, 2, 1, 0, 0},
			{0, 0, 0, 1, 1, 3, 3, 3, 3, 1, 1, 0, 0, 0},
			{0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 0}
		},
		{ // 9
			{0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0, 0, 0},
			{0, 0, 0, 1, 1, 3, 3, 3, 3, 1, 1, 0, 0, 0},
			{0, 0, 1, 3, 3, 3, 2, 2, 3, 3, 3, 1, 0, 0},
			{0, 1, 3, 3, 1, 1, 0, 0, 1, 1, 3, 3, 1, 0},
			{0, 1, 3, 2, 0, 0, 0, 0, 0, 0, 2, 3, 1, 0},
			{1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1},
			{1, 3, 3, 0, 0, 0, -2, -2, 0, 0, 0, 2, 3, 1},
			{1, 3, 3, 0, 0, -1, -5, -5, -1, 0, 0, 2, 3, 2},
			{1, 3, 3, 0, 0, 0, -2, -2, 0, 0, 0, 2, 3, 2},
			{0, 1, 3, 1, 0, 0, 0, 0, 0, 0, 1, 3, 3, 2},
			{0, 1, 3, 3, 2, 1, 1, 1, 1, 2, 2, 3, 3, 2},
			{0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2},
			{0, 0, 0, 0, 1, 1, 3, 3, 2, 2, 2, 2, 3, 2},
			{0, 1, 1, 0, 0, 0, 1, 2, 0, 0, 0, 2, 3, 1},
			{2, 3, 3, 1, 0, 0, 0, 0, 0, 0, 1, 3, 2, 1},
			{1, 3, 3, 1, 0, 0, -2, -2, 0, 0, 1, 3, 2, 0},
			{1, 2, 3, 3, 1, 1, 0, 0, 1, 1, 3, 3, 1, 0},
			{0, 1, 2, 3, 3, 2, 1, 1, 2, 3, 3, 1, 0, 0},
			{0, 0, 1, 2, 3, 3, 3, 3, 3, 2, 1, 0, 0, 0},
			{0, 0, 0, 0, 2, 3, 3, 3, 2, 1, 0, 0, 0, 0}
		}
	};

int intersection_vert(vector< vector<int > > &image, int i, int top, int bottom);
int intersection_horiz(vector< vector<int > > &image, int j, int left, int right);
void get_digit(int left_border, int right_border, int top_border, int bottom_border, vector< vector<int> > &image, vector< vector<int> > &digit);
double get_error(vector< vector<int> > &digit, int n);
void scan_digit(vector< vector<int> > &image, vector< vector<int> > &digit);

int main(void)
{
	vector< vector<int> > image;
	vector<int> line;
	char c;
	
	int image_width;
	
	cin.unsetf(std::ios::skipws);
	cout.unsetf(std::ios::skipws);

	while (!cin.eof())
	{
		cin >> c;
		if (cin.eof())
			break;
		while (c == ' ' || c == '\r' || c == '\n')
		{
			if (cin.eof())
				break;
			cin >> c;
		}

		if (cin.eof())
			break;

		while (c != '\n' && c != '\r')
		{
			line.push_back(color(c));
			cin >> c;
			if (cin.eof())
				break;
		}

		image_width = line.size();
		image.push_back(line);

		line.clear();
	}

	// retrieving digits
	
	vector< vector<int> > digit1, digit2, digit3;
	
	//by default, trying to find 3 bounding boxes
	int bar1 = (image_width / 3 + image_width / 10), bar2 = (2*image_width / 3 + image_width / 10);
	
	for (int i = (image_width / 3 - image_width / 10); i < (image_width / 3 + image_width / 10); ++i)
	{
		if (intersection_vert(image, i, 0, image.size() - 1) < intersection_vert(image, bar1, 0, image.size() - 1))
			bar1 = i;
	}

	for (int i = (2*image_width / 3 - image_width / 10); i < (2*image_width / 3 + image_width / 10); ++i)
	{
		if (intersection_vert(image, i, 0, image.size() - 1) < intersection_vert(image, bar2, 0, image.size() - 1))
			bar2 = i;
	}
	
	if (intersection_vert(image, bar1, 0, image.size() - 1) < 8 && intersection_vert(image, bar2, 0, image.size() - 1) < 8) // really 3 digits
	{
		get_digit(0, bar1, 0, image.size() - 1, image, digit1);
		get_digit(bar1, bar2, 0, image.size() - 1, image, digit2);
		get_digit(bar2, image_width - 1, 0, image.size() - 1, image, digit3);
		
		scan_digit(image, digit1);
		scan_digit(image, digit2);
		scan_digit(image, digit3);
	}
	else // finding 2 bboxes
	{
		int bar = (image_width / 2 + image_width / 5);

		for (int i = (image_width / 2 - image_width / 5); i < (image_width / 2 + image_width / 5); ++i)
		{
			if (intersection_vert(image, i, 0, image.size() - 1) < intersection_vert(image, bar, 0, image.size() - 1))
				bar = i;
		}
		
		if (intersection_vert(image, bar, 0, image.size() - 1) < 12) // really 2 digits
		{
			get_digit(0, bar, 0, image.size() - 1, image, digit1);
			get_digit(bar, image_width - 1, 0, image.size() - 1, image, digit2);

			scan_digit(image, digit1);
			scan_digit(image, digit2);
		}
		else // only one digit
		{
			get_digit(0, image_width - 1, 0, image.size() - 1, image, digit1);
			scan_digit(image, digit1);
		}
	}

	cout << endl;
	
	return 0;
}

inline int color(char c)
{
	switch(c)
	{
		case '.': return 0;
		case '%': return 1;
		case '#': return 2;
		case '@': return 3;
	}
	
	return -1;
}

int intersection_vert(vector< vector<int> > &image, int i, int top, int bottom)
{
	int intersect = 0;

	for (int j = top; j <= bottom; ++j)
		intersect += image[j][i];

	return intersect;
}

int intersection_horiz(vector< vector<int> > &image, int j, int left, int right)
{
	int intersect = 0;

	for (int i = left; i <= right; ++i)
		intersect += image[j][i];

	return intersect;
}

void get_digit(int left_border, int right_border, int top_border, int bottom_border, vector< vector<int> > &image, vector< vector<int> > &digit)
{
	while (intersection_vert(image, left_border, top_border, bottom_border) == 0)
		++left_border;
	while (intersection_vert(image, right_border, top_border, bottom_border) == 0)
		--right_border;
	while (intersection_horiz(image, top_border, left_border, right_border) == 0)
		++top_border;
	while (intersection_horiz(image, bottom_border, left_border, right_border) == 0)
		--bottom_border;

	int width = right_border - left_border + 1,
		height = bottom_border - top_border + 1;

	double scale_h, scale_w;

	scale_h = height / 20.0;
	scale_w = width / 14.0;

	vector< vector<int> > count;

	count.resize(20);
	digit.resize(20);

	for (int i = 0; i < 20; ++i)
	{
		digit[i].resize(14);
		count[i].resize(14);
	}

	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
		{
			//cout << "FSE " << image[i + top_border][j + left_border] << endl;
			//cout << i << " " << i / scale_h << " " << (int)round(i / scale_h) << " " << (int)round(j / scale_w) << endl;
			digit[(int)floor(i / scale_h)][(int)floor(j / scale_w)] += image[i + top_border][j + left_border];
			//cout << "FSE2 ";
			count[(int)floor(i / scale_h)][(int)floor(j / scale_w)]++;
			//cout << "FSE3 " << i << " " << j;
		}

	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 14; ++j)
		{
			digit[i][j] /= count[i][j];
			//cout << digit[i][j];
		}
		//cout << endl;
	}
	//cout << endl;
		
	
	//cout << left_border << " " << right_border << " " << top_border << " " << bottom_border << endl;
}

double get_error(vector< vector<int> > &digit, int n)
{	double error = 0;

	for (int i = 0; i < digit.size(); ++i)
		for (int j = 0; j < digit[i].size(); ++j)
		{
			//if (N[n][i][j] >=2 && abs(N[n][i][j] - digit[i][j]) > 1)
			error += (N[n][i][j] - digit[i][j]) * (N[n][i][j] - digit[i][j]);
		}

	return error;
}

void scan_digit(vector< vector<int> > &image, vector< vector<int> > &digit)
{
	double error, min_error;
	int min_error_digit;

	min_error = get_error(digit, 0);
	min_error_digit = 0;
	for (int i = 1; i < 10; ++i)
	{
		error = get_error(digit, i);
		//cout << "error: " << error << " " << i << " " << min_error << endl;
		if (error < min_error)
		{
			min_error_digit = i;
			min_error = error;
		}
	}
	cout << min_error_digit;
}
