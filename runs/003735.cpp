#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <cmath>
using namespace std;

const int data_size = 3680;

double data[data_size] = {
/* 1 */ 0.26, 0.74,    0, 0.62,
/* 2 */ 0.34, 0.59, 0.57, 0.47,
/* 3 */  0.4,  0.6, 0.38, 0.58,
/* 4 */ 0.25, 0.56, 0.44, 0.66,
/* 5 */ 0.64, 0.47, 0.36,  0.5,
/* 6 */ 0.57, 0.47, 0.49, 0.46,
/* 7 */  0.4, 0.76, 0.51, 0.084,
/* 8 */ 0.52,  0.5,  0.5, 0.48,
/* 9 */ 0.48, 0.48, 0.48, 0.56,
/* 0 */ 0.48, 0.52, 0.49, 0.52,
/* 1 */  0.3, 0.77, 0.34, 0.45,
/* 2 */ 0.31,  0.6, 0.61, 0.41,
/* 3 */  0.3, 0.69, 0.37, 0.54,
/* 4 */ 0.18, 0.65, 0.39, 0.63,
/* 5 */ 0.56, 0.55, 0.39, 0.48,
/* 6 */ 0.54, 0.52,  0.5, 0.44,
/* 7 */ 0.47, 0.68, 0.57, 0.0073,
/* 8 */ 0.46, 0.57, 0.52, 0.45,
/* 9 */ 0.42, 0.51, 0.49, 0.57,
/* 0 */ 0.45, 0.53, 0.54, 0.47,
/* 1 */ 0.29, 0.71,    0, 0.64,
/* 2 */ 0.32, 0.56, 0.55, 0.53,
/* 3 */  0.4, 0.59, 0.38, 0.59,
/* 4 */ 0.27, 0.54, 0.47, 0.65,
/* 5 */ 0.56, 0.49, 0.42, 0.52,
/* 6 */ 0.53, 0.42, 0.52, 0.52,
/* 7 */ 0.49, 0.71, 0.49, 0.12,
/* 8 */  0.5, 0.48, 0.52, 0.51,
/* 9 */ 0.53, 0.52, 0.43, 0.51,
/* 0 */ 0.51, 0.49, 0.51, 0.49,
/* 1 */ 0.37, 0.74, 0.34, 0.45,
/* 2 */ 0.28, 0.63, 0.56, 0.46,
/* 3 */ 0.28, 0.65, 0.39, 0.58,
/* 4 */ 0.19, 0.62, 0.47,  0.6,
/* 5 */ 0.54, 0.53, 0.41,  0.5,
/* 6 */ 0.53, 0.48, 0.53, 0.46,
/* 7 */ 0.49, 0.67, 0.55, 0.031,
/* 8 */ 0.43, 0.57, 0.52, 0.47,
/* 9 */ 0.44, 0.54, 0.46, 0.55,
/* 0 */ 0.46, 0.54, 0.54, 0.45,
/* 1 */ 0.34, 0.66, 0.061, 0.67,
/* 2 */ 0.35, 0.56, 0.53, 0.53,
/* 3 */ 0.37, 0.58, 0.37, 0.62,
/* 4 */ 0.27, 0.55, 0.46, 0.64,
/* 5 */ 0.59, 0.48, 0.38, 0.54,
/* 6 */ 0.54, 0.46, 0.49,  0.5,
/* 7 */ 0.49, 0.72, 0.45, 0.21,
/* 8 */ 0.48, 0.49, 0.51, 0.52,
/* 9 */  0.5, 0.51, 0.46, 0.53,
/* 0 */ 0.49, 0.51, 0.49, 0.51,
/* 1 */ 0.39, 0.73, 0.44, 0.34,
/* 2 */ 0.21, 0.67, 0.58, 0.42,
/* 3 */ 0.25, 0.68, 0.46, 0.51,
/* 4 */ 0.16, 0.62, 0.51, 0.57,
/* 5 */ 0.49, 0.59, 0.48, 0.43,
/* 6 */ 0.45, 0.54, 0.58, 0.41,
/* 7 */ 0.45,  0.7, 0.55, 0.03,
/* 8 */ 0.38, 0.58, 0.59, 0.42,
/* 9 */ 0.39,  0.6, 0.53, 0.44,
/* 0 */  0.4, 0.59, 0.58,  0.4,
/* 1 */ 0.34, 0.66, 0.061, 0.67,
/* 2 */ 0.35, 0.56, 0.53, 0.53,
/* 3 */ 0.37, 0.58, 0.37, 0.62,
/* 4 */ 0.27, 0.55, 0.46, 0.64,
/* 5 */ 0.59, 0.48, 0.38, 0.54,
/* 6 */ 0.54, 0.46, 0.49,  0.5,
/* 7 */ 0.49, 0.72, 0.45, 0.21,
/* 8 */ 0.48, 0.49, 0.51, 0.52,
/* 9 */  0.5, 0.51, 0.46, 0.53,
/* 0 */ 0.49, 0.51, 0.49, 0.51,
/* 1 */ 0.39, 0.73, 0.44, 0.34,
/* 2 */ 0.21, 0.67, 0.58, 0.42,
/* 3 */ 0.25, 0.68, 0.46, 0.51,
/* 4 */ 0.16, 0.62, 0.51, 0.57,
/* 5 */ 0.49, 0.59, 0.48, 0.43,
/* 6 */ 0.45, 0.54, 0.58, 0.41,
/* 7 */ 0.45,  0.7, 0.55, 0.03,
/* 8 */ 0.38, 0.58, 0.59, 0.42,
/* 9 */ 0.39,  0.6, 0.53, 0.44,
/* 0 */  0.4, 0.59, 0.58,  0.4,
/* 1 */ 0.48, 0.43, 0.48,  0.6,
/* 2 */ 0.26, 0.61, 0.61, 0.44,
/* 3 */  0.4,  0.6, 0.29, 0.63,
/* 4 */ 0.32, 0.57, 0.41, 0.64,
/* 5 */ 0.62,  0.4, 0.27, 0.62,
/* 6 */ 0.58, 0.37, 0.52, 0.52,
/* 7 */ 0.28,  0.8, 0.46, 0.26,
/* 8 */ 0.49, 0.48,  0.5, 0.52,
/* 9 */ 0.53, 0.54, 0.37, 0.54,
/* 0 */ 0.48, 0.52,  0.5,  0.5,
/* 1 */ 0.12, 0.66, 0.34, 0.66,
/* 2 */ 0.13, 0.67, 0.59, 0.44,
/* 3 */ 0.25, 0.68, 0.33, 0.61,
/* 4 */  0.2, 0.67, 0.39, 0.59,
/* 5 */ 0.54,  0.5, 0.31, 0.59,
/* 6 */ 0.55, 0.41, 0.55, 0.47,
/* 7 */ 0.33, 0.75, 0.57, 0.048,
/* 8 */ 0.42, 0.56, 0.55, 0.45,
/* 9 */ 0.45, 0.62, 0.39, 0.51,
/* 0 */ 0.43, 0.56, 0.55, 0.44,
/* 1 */  0.5, 0.39,  0.5, 0.59,
/* 2 */  0.3, 0.63, 0.56, 0.45,
/* 3 */  0.4, 0.57, 0.35, 0.62,
/* 4 */ 0.33, 0.56, 0.41, 0.64,
/* 5 */ 0.59, 0.42, 0.32, 0.62,
/* 6 */ 0.56, 0.39, 0.54,  0.5,
/* 7 */ 0.36, 0.77, 0.48, 0.24,
/* 8 */ 0.48, 0.49, 0.49, 0.53,
/* 9 */ 0.51, 0.56, 0.39, 0.52,
/* 0 */ 0.48, 0.52,  0.5,  0.5,
/* 1 */ 0.17, 0.64, 0.42, 0.62,
/* 2 */ 0.16, 0.69, 0.54, 0.45,
/* 3 */ 0.28, 0.67, 0.39, 0.57,
/* 4 */ 0.22, 0.65, 0.41,  0.6,
/* 5 */ 0.54, 0.52, 0.38, 0.55,
/* 6 */ 0.49, 0.46, 0.57, 0.47,
/* 7 */ 0.35, 0.73, 0.58,  0.1,
/* 8 */ 0.41, 0.56, 0.55, 0.46,
/* 9 */ 0.47,  0.6, 0.44, 0.47,
/* 0 */ 0.44, 0.56, 0.54, 0.45,
/* 1 */ 0.56, 0.33, 0.57, 0.51,
/* 2 */ 0.23, 0.61, 0.57, 0.51,
/* 3 */ 0.37, 0.59, 0.33, 0.64,
/* 4 */ 0.27, 0.55,  0.3, 0.73,
/* 5 */ 0.62, 0.41, 0.32, 0.58,
/* 6 */ 0.51, 0.34, 0.58, 0.54,
/* 7 */ 0.47, 0.74, 0.46, 0.15,
/* 8 */ 0.51, 0.53, 0.49, 0.47,
/* 9 */ 0.55, 0.61, 0.27, 0.51,
/* 0 */ 0.48, 0.52, 0.52, 0.48,
/* 1 */ 0.091, 0.68, 0.36, 0.63,
/* 2 */ 0.18, 0.64, 0.61, 0.43,
/* 3 */ 0.28, 0.69, 0.38, 0.55,
/* 4 */ 0.19, 0.62, 0.34, 0.68,
/* 5 */ 0.47, 0.52, 0.34, 0.63,
/* 6 */ 0.48, 0.37, 0.56, 0.57,
/* 7 */ 0.47, 0.73,  0.5, 0.029,
/* 8 */ 0.44, 0.55, 0.53, 0.47,
/* 9 */ 0.55, 0.58, 0.36, 0.48,
/* 0 */ 0.45, 0.54, 0.55, 0.44,
/* 1 */ 0.48, 0.46, 0.47, 0.58,
/* 2 */ 0.27, 0.61, 0.55,  0.5,
/* 3 */ 0.35, 0.61, 0.34, 0.63,
/* 4 */ 0.26, 0.56, 0.36,  0.7,
/* 5 */ 0.58,  0.4, 0.34, 0.62,
/* 6 */ 0.51, 0.32, 0.55, 0.57,
/* 7 */ 0.52, 0.73, 0.38, 0.24,
/* 8 */ 0.49, 0.52, 0.49,  0.5,
/* 9 */ 0.55, 0.58,  0.3, 0.53,
/* 0 */ 0.48, 0.52, 0.49, 0.51,
/* 1 */ 0.13, 0.71, 0.34, 0.61,
/* 2 */ 0.18, 0.65, 0.59, 0.44,
/* 3 */ 0.28, 0.66, 0.36, 0.59,
/* 4 */ 0.17, 0.62, 0.44, 0.63,
/* 5 */ 0.47, 0.51,  0.4,  0.6,
/* 6 */ 0.47, 0.41, 0.57, 0.54,
/* 7 */  0.5, 0.71, 0.49, 0.055,
/* 8 */ 0.46, 0.54, 0.53, 0.46,
/* 9 */ 0.55,  0.6, 0.41, 0.42,
/* 0 */ 0.45, 0.55, 0.53, 0.47,
/* 1 */ 0.22, 0.73,    0, 0.64,
/* 2 */ 0.32, 0.59, 0.56, 0.48,
/* 3 */  0.4, 0.69, 0.26, 0.54,
/* 4 */ 0.38, 0.57, 0.34, 0.64,
/* 5 */ 0.66, 0.44, 0.26, 0.55,
/* 6 */ 0.53, 0.34, 0.52, 0.57,
/* 7 */ 0.36, 0.75, 0.53, 0.18,
/* 8 */ 0.49, 0.49, 0.48, 0.54,
/* 9 */ 0.56, 0.58, 0.31, 0.51,
/* 0 */ 0.46, 0.53, 0.53, 0.48,
/* 1 */ 0.22, 0.75,  0.1, 0.62,
/* 2 */  0.2, 0.65, 0.51, 0.53,
/* 3 */ 0.24, 0.75, 0.28, 0.55,
/* 4 */ 0.27, 0.62, 0.34, 0.65,
/* 5 */ 0.56, 0.53, 0.29, 0.57,
/* 6 */ 0.48,  0.4, 0.53, 0.56,
/* 7 */ 0.31, 0.75, 0.57, 0.095,
/* 8 */ 0.42, 0.57, 0.47, 0.53,
/* 9 */ 0.55, 0.59, 0.39, 0.44,
/* 0 */ 0.43, 0.57, 0.53, 0.46,
/* 1 */ 0.24, 0.66, 0.12,  0.7,
/* 2 */ 0.36, 0.58, 0.56, 0.48,
/* 3 */ 0.41, 0.64, 0.28, 0.58,
/* 4 */ 0.32,  0.6, 0.32, 0.67,
/* 5 */ 0.63, 0.45, 0.26, 0.58,
/* 6 */ 0.52, 0.33, 0.57, 0.54,
/* 7 */  0.3, 0.76, 0.54, 0.21,
/* 8 */ 0.48, 0.47,  0.5, 0.55,
/* 9 */ 0.55, 0.61, 0.28, 0.51,
/* 0 */ 0.47, 0.52, 0.51, 0.49,
/* 1 */ 0.34, 0.69,  0.3, 0.56,
/* 2 */ 0.22, 0.65, 0.49, 0.54,
/* 3 */ 0.25, 0.72, 0.28, 0.58,
/* 4 */ 0.28,  0.6, 0.35, 0.66,
/* 5 */ 0.54, 0.53, 0.31, 0.57,
/* 6 */ 0.47, 0.44, 0.54, 0.54,
/* 7 */ 0.29, 0.75, 0.58,  0.1,
/* 8 */ 0.42, 0.55,  0.5, 0.52,
/* 9 */ 0.54, 0.62, 0.34, 0.45,
/* 0 */ 0.45, 0.54, 0.52, 0.48,
/* 1 */ 0.46, 0.48,  0.5, 0.55,
/* 2 */ 0.33,  0.6, 0.63, 0.37,
/* 3 */ 0.39, 0.61, 0.35, 0.59,
/* 4 */ 0.34, 0.55, 0.42, 0.64,
/* 5 */ 0.67, 0.48, 0.33, 0.45,
/* 6 */ 0.54,  0.3, 0.56, 0.55,
/* 7 */ 0.44, 0.78, 0.44, 0.07,
/* 8 */ 0.51, 0.49, 0.49,  0.5,
/* 9 */ 0.51, 0.57, 0.43, 0.48,
/* 0 */ 0.47, 0.52, 0.49, 0.52,
/* 1 */ 0.084,  0.7, 0.65, 0.28,
/* 2 */ 0.16, 0.69, 0.67, 0.22,
/* 3 */ 0.22, 0.75, 0.45, 0.44,
/* 4 */ 0.21, 0.65, 0.44, 0.59,
/* 5 */ 0.54, 0.64, 0.45, 0.33,
/* 6 */  0.3, 0.54, 0.62, 0.49,
/* 7 */ 0.39, 0.77,  0.5, 0.0055,
/* 8 */ 0.35, 0.64, 0.55,  0.4,
/* 9 */  0.4, 0.67, 0.49, 0.39,
/* 0 */ 0.37,  0.6, 0.61, 0.37,
/* 1 */ 0.51, 0.42, 0.52, 0.55,
/* 2 */ 0.33,  0.6, 0.64, 0.36,
/* 3 */ 0.38, 0.62, 0.35, 0.59,
/* 4 */ 0.33, 0.58, 0.38, 0.64,
/* 5 */ 0.66, 0.47, 0.34, 0.47,
/* 6 */ 0.53, 0.37, 0.54, 0.54,
/* 7 */ 0.46, 0.74, 0.49, 0.08,
/* 8 */ 0.51,  0.5,  0.5,  0.5,
/* 9 */ 0.52, 0.56, 0.43, 0.49,
/* 0 */ 0.49,  0.5,  0.5,  0.5,
/* 1 */ 0.12, 0.71, 0.57, 0.38,
/* 2 */ 0.18, 0.67, 0.69, 0.22,
/* 3 */ 0.21, 0.74, 0.46, 0.45,
/* 4 */ 0.22, 0.66, 0.48, 0.53,
/* 5 */ 0.54, 0.61, 0.46, 0.35,
/* 6 */  0.3, 0.57, 0.62, 0.45,
/* 7 */ 0.41, 0.75, 0.52, 0.012,
/* 8 */ 0.35, 0.63, 0.57,  0.4,
/* 9 */ 0.39, 0.65, 0.54, 0.37,
/* 0 */ 0.36, 0.61,  0.6, 0.37,
/* 1 */ 0.42, 0.49, 0.46,  0.6,
/* 2 */ 0.24, 0.56, 0.52, 0.59,
/* 3 */ 0.28, 0.72,  0.2,  0.6,
/* 4 */  0.2, 0.54, 0.39, 0.72,
/* 5 */ 0.56, 0.61, 0.18, 0.54,
/* 6 */  0.5, 0.32, 0.57, 0.56,
/* 7 */ 0.47, 0.73, 0.45,  0.2,
/* 8 */ 0.53, 0.49, 0.46, 0.52,
/* 9 */ 0.55, 0.59, 0.31,  0.5,
/* 0 */ 0.48, 0.53, 0.51, 0.49,
/* 1 */ 0.12, 0.71,  0.4, 0.57,
/* 2 */ 0.16, 0.63, 0.53, 0.55,
/* 3 */ 0.21, 0.78, 0.12, 0.57,
/* 4 */ 0.22, 0.39, 0.46, 0.76,
/* 5 */ 0.41, 0.76, 0.13, 0.49,
/* 6 */ 0.49, 0.36, 0.61, 0.51,
/* 7 */  0.5, 0.71,  0.5, 0.04,
/* 8 */ 0.45, 0.52,  0.5, 0.53,
/* 9 */ 0.55, 0.61, 0.35, 0.45,
/* 0 */ 0.45, 0.56, 0.53, 0.46,
/* 1 */  0.5, 0.47, 0.48, 0.55,
/* 2 */ 0.22, 0.53,  0.6, 0.56,
/* 3 */  0.3, 0.67, 0.19, 0.65,
/* 4 */ 0.15, 0.63, 0.26, 0.72,
/* 5 */ 0.59, 0.55, 0.15, 0.57,
/* 6 */ 0.51,  0.3, 0.56, 0.58,
/* 7 */ 0.59, 0.68,  0.4, 0.16,
/* 8 */  0.5, 0.47, 0.47, 0.56,
/* 9 */ 0.55,  0.6, 0.29, 0.51,
/* 0 */ 0.47, 0.54, 0.49, 0.49,
/* 1 */ 0.19, 0.68, 0.42, 0.57,
/* 2 */ 0.11, 0.56, 0.58, 0.59,
/* 3 */ 0.19, 0.73, 0.19, 0.62,
/* 4 */ 0.22,  0.5,  0.4, 0.73,
/* 5 */ 0.49, 0.66, 0.18, 0.54,
/* 6 */ 0.47, 0.38, 0.59, 0.54,
/* 7 */ 0.55, 0.69, 0.47, 0.064,
/* 8 */ 0.43, 0.51, 0.48, 0.56,
/* 9 */ 0.53,  0.6, 0.37, 0.46,
/* 0 */  0.5,  0.5, 0.51,  0.5,
/* 1 */ 0.43, 0.41, 0.44, 0.67,
/* 2 */ 0.29, 0.55, 0.56, 0.55,
/* 3 */ 0.36, 0.63,  0.3, 0.63,
/* 4 */ 0.47, 0.24, 0.42, 0.74,
/* 5 */ 0.68, 0.39, 0.25, 0.57,
/* 6 */ 0.58, 0.41,  0.5,  0.5,
/* 7 */ 0.32, 0.79,  0.5, 0.14,
/* 8 */  0.5,  0.5, 0.49,  0.5,
/* 9 */  0.5, 0.55, 0.35, 0.57,
/* 0 */ 0.51, 0.49, 0.51, 0.49,
/* 1 */ 0.24, 0.56, 0.43, 0.67,
/* 2 */ 0.19,  0.6, 0.54, 0.55,
/* 3 */ 0.22, 0.71, 0.33, 0.58,
/* 4 */ 0.34, 0.39, 0.45, 0.72,
/* 5 */ 0.59, 0.49, 0.35, 0.54,
/* 6 */ 0.52, 0.43, 0.58, 0.46,
/* 7 */ 0.29, 0.79, 0.53, 0.071,
/* 8 */ 0.44, 0.58, 0.52, 0.44,
/* 9 */ 0.45, 0.64, 0.41, 0.48,
/* 0 */ 0.46, 0.55, 0.53, 0.46,
/* 1 */ 0.51, 0.39, 0.49,  0.6,
/* 2 */  0.3, 0.55, 0.55, 0.55,
/* 3 */ 0.39, 0.62, 0.28, 0.62,
/* 4 */ 0.51, 0.22, 0.39, 0.73,
/* 5 */ 0.63, 0.42, 0.25,  0.6,
/* 6 */ 0.55, 0.38,  0.5, 0.55,
/* 7 */ 0.34, 0.77, 0.51, 0.18,
/* 8 */ 0.52,  0.5, 0.49, 0.49,
/* 9 */ 0.54, 0.56, 0.34, 0.53,
/* 0 */ 0.49,  0.5,  0.5, 0.51,
/* 1 */ 0.34, 0.56, 0.45,  0.6,
/* 2 */  0.2,  0.6, 0.51, 0.58,
/* 3 */ 0.26, 0.71, 0.33, 0.56,
/* 4 */ 0.37, 0.41, 0.44,  0.7,
/* 5 */ 0.58, 0.47, 0.33, 0.58,
/* 6 */ 0.53, 0.42, 0.57, 0.47,
/* 7 */ 0.27, 0.77, 0.57,  0.1,
/* 8 */ 0.43, 0.57, 0.54, 0.44,
/* 9 */ 0.48, 0.64, 0.36, 0.48,
/* 0 */ 0.46, 0.55, 0.54, 0.45,
/* 1 */ 0.53, 0.35, 0.54, 0.54,
/* 2 */ 0.29, 0.56, 0.59,  0.5,
/* 3 */ 0.31, 0.68, 0.29,  0.6,
/* 4 */ 0.28, 0.52, 0.38, 0.71,
/* 5 */ 0.65, 0.45,  0.3, 0.53,
/* 6 */ 0.54, 0.38, 0.62, 0.43,
/* 7 */ 0.37, 0.77, 0.14,  0.5,
/* 8 */ 0.52, 0.55, 0.44, 0.48,
/* 9 */ 0.53, 0.54, 0.37, 0.55,
/* 0 */ 0.49, 0.51,  0.5,  0.5,
/* 1 */ 0.13, 0.63, 0.41, 0.65,
/* 2 */  0.2, 0.64, 0.61, 0.43,
/* 3 */ 0.15, 0.78, 0.35,  0.5,
/* 4 */  0.2, 0.62, 0.46, 0.61,
/* 5 */ 0.54, 0.64, 0.35, 0.42,
/* 6 */ 0.54, 0.42, 0.63, 0.37,
/* 7 */ 0.38, 0.82, 0.39, 0.21,
/* 8 */ 0.45, 0.61, 0.52,  0.4,
/* 9 */ 0.39, 0.65, 0.42,  0.5,
/* 0 */ 0.39, 0.55, 0.58, 0.46,
/* 1 */ 0.55, 0.32, 0.55, 0.55,
/* 2 */ 0.32, 0.55, 0.57, 0.52,
/* 3 */ 0.35, 0.63, 0.34,  0.6,
/* 4 */ 0.29, 0.52, 0.44, 0.67,
/* 5 */ 0.63, 0.45, 0.35, 0.53,
/* 6 */ 0.53, 0.44, 0.53, 0.49,
/* 7 */  0.4, 0.77, 0.18, 0.47,
/* 8 */ 0.49, 0.49, 0.51, 0.51,
/* 9 */ 0.48, 0.52, 0.44, 0.56,
/* 0 */  0.5,  0.5,  0.5,  0.5,
/* 1 */  0.2, 0.59, 0.45, 0.63,
/* 2 */ 0.21, 0.62, 0.61, 0.44,
/* 3 */ 0.23, 0.73, 0.36, 0.53,
/* 4 */ 0.19, 0.62, 0.46,  0.6,
/* 5 */ 0.51, 0.61, 0.36, 0.49,
/* 6 */ 0.51, 0.41, 0.63, 0.42,
/* 7 */ 0.43, 0.76, 0.47, 0.12,
/* 8 */ 0.42, 0.56, 0.56, 0.45,
/* 9 */ 0.41, 0.62, 0.45,  0.5,
/* 0 */ 0.41, 0.58, 0.56, 0.43,
/* 1 */ 0.47, 0.43, 0.52, 0.57,
/* 2 */ 0.36, 0.54, 0.55, 0.53,
/* 3 */ 0.38, 0.59, 0.33, 0.63,
/* 4 */ 0.18, 0.62, 0.29,  0.7,
/* 5 */  0.5, 0.53, 0.31, 0.61,
/* 6 */ 0.52, 0.35, 0.56, 0.55,
/* 7 */ 0.54, 0.73, 0.41, 0.091,
/* 8 */ 0.53, 0.45, 0.47, 0.54,
/* 9 */ 0.57, 0.55, 0.34, 0.51,
/* 0 */  0.5, 0.49,  0.5,  0.5,
/* 1 */ 0.099, 0.68, 0.42,  0.6,
/* 2 */ 0.28, 0.58, 0.56, 0.52,
/* 3 */ 0.33, 0.64, 0.39, 0.57,
/* 4 */ 0.15, 0.63, 0.35, 0.68,
/* 5 */ 0.45, 0.62, 0.38, 0.51,
/* 6 */ 0.45, 0.41, 0.55, 0.57,
/* 7 */ 0.47, 0.78, 0.42, 0.02,
/* 8 */ 0.46, 0.52, 0.52,  0.5,
/* 9 */ 0.54, 0.58, 0.42, 0.44,
/* 0 */ 0.43, 0.56, 0.53, 0.48,
/* 1 */ 0.43, 0.48,  0.5, 0.58,
/* 2 */ 0.36, 0.55, 0.54, 0.53,
/* 3 */ 0.36,  0.6, 0.32, 0.64,
/* 4 */ 0.16, 0.59, 0.36, 0.71,
/* 5 */ 0.44, 0.54, 0.32, 0.64,
/* 6 */ 0.48, 0.29, 0.58, 0.59,
/* 7 */ 0.62, 0.73, 0.27, 0.15,
/* 8 */ 0.51, 0.47, 0.47, 0.54,
/* 9 */ 0.59, 0.57, 0.28, 0.49,
/* 0 */ 0.51,  0.5,  0.5,  0.5,
/* 1 */ 0.15, 0.69,  0.4, 0.59,
/* 2 */ 0.31, 0.58, 0.56, 0.51,
/* 3 */ 0.32, 0.65, 0.37, 0.59,
/* 4 */ 0.14, 0.62, 0.39, 0.67,
/* 5 */ 0.37, 0.61, 0.38,  0.6,
/* 6 */ 0.45, 0.35, 0.58, 0.58,
/* 7 */ 0.56, 0.74, 0.37, 0.027,
/* 8 */ 0.48,  0.5, 0.49, 0.53,
/* 9 */ 0.58, 0.59, 0.36, 0.43,
/* 0 */ 0.48, 0.54, 0.51, 0.47,
/* 1 */ 0.27, 0.66, 0.15, 0.68,
/* 2 */ 0.42, 0.61, 0.53, 0.41,
/* 3 */ 0.42, 0.54, 0.48, 0.56,
/* 4 */ 0.39, 0.56, 0.39, 0.62,
/* 5 */ 0.58, 0.46, 0.39, 0.55,
/* 6 */ 0.52, 0.47, 0.49, 0.52,
/* 7 */ 0.31, 0.74, 0.38, 0.46,
/* 8 */ 0.49, 0.51, 0.49, 0.52,
/* 9 */ 0.49, 0.52, 0.45, 0.54,
/* 0 */ 0.48, 0.51, 0.49, 0.52,
/* 1 */ 0.36, 0.61, 0.69, 0.14,
/* 2 */ 0.21, 0.74, 0.58, 0.28,
/* 3 */ 0.25, 0.66, 0.57, 0.41,
/* 4 */ 0.22, 0.68, 0.57, 0.41,
/* 5 */ 0.44, 0.59, 0.54, 0.41,
/* 6 */  0.4, 0.58, 0.61, 0.38,
/* 7 */ 0.21, 0.76, 0.61, 0.12,
/* 8 */ 0.35, 0.61, 0.61, 0.37,
/* 9 */ 0.38, 0.61, 0.57, 0.39,
/* 0 */ 0.37,  0.6, 0.61, 0.37,
/* 1 */ 0.27, 0.66, 0.15, 0.68,
/* 2 */ 0.43,  0.6, 0.51, 0.43,
/* 3 */ 0.42, 0.54, 0.47, 0.56,
/* 4 */ 0.41, 0.56, 0.39, 0.61,
/* 5 */ 0.59, 0.45,  0.4, 0.54,
/* 6 */ 0.53, 0.46,  0.5,  0.5,
/* 7 */  0.3, 0.73, 0.38, 0.49,
/* 8 */ 0.49,  0.5,  0.5, 0.51,
/* 9 */ 0.51, 0.51, 0.45, 0.53,
/* 0 */  0.5,  0.5,  0.5,  0.5,
/* 1 */ 0.34, 0.62, 0.68, 0.19,
/* 2 */ 0.23, 0.74, 0.57, 0.27,
/* 3 */ 0.27, 0.64, 0.61, 0.39,
/* 4 */ 0.26, 0.68, 0.57, 0.39,
/* 5 */ 0.44, 0.58, 0.55, 0.41,
/* 6 */  0.4, 0.57, 0.61, 0.37,
/* 7 */  0.2, 0.75, 0.62, 0.15,
/* 8 */ 0.36,  0.6, 0.62, 0.36,
/* 9 */ 0.39, 0.62, 0.57, 0.38,
/* 0 */ 0.37,  0.6, 0.61, 0.36,
/* 1 */ 0.57, 0.28, 0.59,  0.5,
/* 2 */ 0.21, 0.67, 0.61, 0.37,
/* 3 */ 0.37, 0.59, 0.27, 0.66,
/* 4 */ 0.31, 0.59,  0.4, 0.63,
/* 5 */ 0.62,  0.4, 0.21, 0.64,
/* 6 */ 0.57, 0.37, 0.53, 0.51,
/* 7 */ 0.37, 0.72, 0.58, 0.069,
/* 8 */  0.5, 0.45,  0.5, 0.55,
/* 9 */ 0.48, 0.56, 0.35, 0.58,
/* 0 */ 0.51, 0.49,  0.5, 0.49,
/* 1 */ 0.052, 0.69, 0.37, 0.62,
/* 2 */ 0.056, 0.72, 0.64, 0.27,
/* 3 */ 0.19, 0.74, 0.36, 0.54,
/* 4 */ 0.16, 0.67, 0.47, 0.56,
/* 5 */ 0.51,  0.6, 0.38, 0.47,
/* 6 */ 0.47, 0.44, 0.65, 0.41,
/* 7 */ 0.23,  0.8, 0.56, 0.022,
/* 8 */ 0.38, 0.58, 0.56, 0.44,
/* 9 */ 0.39, 0.66, 0.43, 0.47,
/* 0 */  0.4, 0.59, 0.58,  0.4,
/* 1 */ 0.54, 0.35, 0.54, 0.54,
/* 2 */  0.2, 0.67, 0.61, 0.37,
/* 3 */ 0.35, 0.59, 0.26, 0.67,
/* 4 */ 0.33,  0.6, 0.37, 0.63,
/* 5 */ 0.63, 0.39,  0.2, 0.64,
/* 6 */ 0.58, 0.32, 0.54, 0.51,
/* 7 */ 0.36, 0.72, 0.59, 0.062,
/* 8 */  0.5, 0.46, 0.51, 0.53,
/* 9 */  0.5, 0.55, 0.33, 0.58,
/* 0 */  0.5,  0.5,  0.5,  0.5,
/* 1 */ 0.063, 0.71, 0.38, 0.59,
/* 2 */ 0.067, 0.74, 0.62, 0.25,
/* 3 */ 0.17, 0.73, 0.34, 0.56,
/* 4 */ 0.17, 0.69, 0.47, 0.53,
/* 5 */ 0.52, 0.59, 0.37,  0.5,
/* 6 */ 0.49, 0.42, 0.65, 0.41,
/* 7 */ 0.21, 0.78, 0.59, 0.037,
/* 8 */ 0.39, 0.58, 0.56, 0.45,
/* 9 */ 0.41, 0.65, 0.42, 0.49,
/* 0 */  0.4, 0.59, 0.57, 0.41,
/* 1 */ 0.22, 0.73,    0, 0.65,
/* 2 */ 0.34, 0.59, 0.57, 0.47,
/* 3 */ 0.37,  0.6, 0.36, 0.61,
/* 4 */ 0.26, 0.56, 0.44, 0.65,
/* 5 */ 0.63, 0.44, 0.37, 0.52,
/* 6 */ 0.59, 0.45, 0.47, 0.48,
/* 7 */ 0.35,  0.8, 0.37, 0.32,
/* 8 */ 0.49, 0.49, 0.51, 0.51,
/* 9 */ 0.48, 0.49, 0.44, 0.58,
/* 0 */  0.5,  0.5,  0.5,  0.5,
/* 1 */  0.4, 0.67, 0.62, 0.065,
/* 2 */ 0.16, 0.67, 0.62, 0.36,
/* 3 */  0.2, 0.72, 0.44, 0.49,
/* 4 */ 0.12, 0.65, 0.53, 0.54,
/* 5 */ 0.55, 0.56,  0.5, 0.38,
/* 6 */ 0.47, 0.56, 0.58, 0.36,
/* 7 */ 0.26,  0.8, 0.54, 0.066,
/* 8 */ 0.38, 0.61, 0.58, 0.39,
/* 9 */ 0.36, 0.59, 0.57, 0.45,
/* 0 */ 0.37,  0.6, 0.61, 0.36,
/* 1 */ 0.22, 0.73,    0, 0.65,
/* 2 */ 0.35, 0.59, 0.56, 0.47,
/* 3 */ 0.37, 0.59, 0.36, 0.62,
/* 4 */ 0.27, 0.58, 0.42, 0.64,
/* 5 */ 0.63, 0.42, 0.36, 0.55,
/* 6 */ 0.58, 0.44, 0.48,  0.5,
/* 7 */ 0.32,  0.8, 0.41,  0.3,
/* 8 */ 0.48,  0.5,  0.5, 0.52,
/* 9 */ 0.48, 0.51, 0.43, 0.58,
/* 0 */ 0.49, 0.51, 0.49, 0.51,
/* 1 */ 0.36, 0.67, 0.64, 0.11,
/* 2 */ 0.18, 0.68, 0.62, 0.34,
/* 3 */ 0.22, 0.71, 0.43, 0.51,
/* 4 */ 0.13, 0.66,  0.5, 0.54,
/* 5 */ 0.56, 0.52, 0.51,  0.4,
/* 6 */ 0.48, 0.54, 0.57, 0.39,
/* 7 */ 0.27, 0.79, 0.55, 0.059,
/* 8 */ 0.38,  0.6, 0.58,  0.4,
/* 9 */ 0.38, 0.58, 0.55, 0.47,
/* 0 */ 0.39,  0.6, 0.59, 0.37,
/* 1 */ 0.43, 0.55, 0.39, 0.59,
/* 2 */ 0.34, 0.65, 0.46,  0.5,
/* 3 */ 0.36, 0.67, 0.31, 0.57,
/* 4 */ 0.16, 0.48, 0.38, 0.78,
/* 5 */ 0.58, 0.62, 0.24, 0.48,
/* 6 */  0.5, 0.32, 0.58, 0.56,
/* 7 */ 0.55, 0.66, 0.51, 0.06,
/* 8 */ 0.55, 0.47, 0.42, 0.55,
/* 9 */ 0.54, 0.59, 0.33,  0.5,
/* 0 */ 0.42, 0.57, 0.49, 0.49,
/* 1 */ 0.15, 0.71, 0.39, 0.57,
/* 2 */ 0.17, 0.75, 0.44, 0.46,
/* 3 */ 0.22, 0.74, 0.27, 0.58,
/* 4 */ 0.13, 0.53, 0.42, 0.72,
/* 5 */ 0.45, 0.59, 0.38, 0.55,
/* 6 */ 0.43, 0.36, 0.63, 0.53,
/* 7 */ 0.34, 0.74, 0.58, 0.062,
/* 8 */  0.4, 0.56, 0.52, 0.51,
/* 9 */ 0.47, 0.64,  0.4, 0.46,
/* 0 */ 0.45, 0.56, 0.55, 0.44,
/* 1 */ 0.45,  0.5, 0.44,  0.6,
/* 2 */ 0.33, 0.64, 0.51, 0.47,
/* 3 */ 0.36, 0.64, 0.32,  0.6,
/* 4 */ 0.19, 0.51, 0.42, 0.73,
/* 5 */ 0.55, 0.51, 0.32, 0.57,
/* 6 */  0.5, 0.35, 0.56, 0.55,
/* 7 */ 0.57, 0.68, 0.45,  0.1,
/* 8 */ 0.51, 0.49, 0.43, 0.56,
/* 9 */ 0.54, 0.62, 0.31, 0.48,
/* 0 */ 0.46, 0.55, 0.51, 0.48,
/* 1 */ 0.14,  0.7, 0.39, 0.58,
/* 2 */ 0.19,  0.7, 0.47,  0.5,
/* 3 */ 0.21, 0.69, 0.24, 0.65,
/* 4 */  0.1, 0.58,  0.4,  0.7,
/* 5 */ 0.45, 0.58, 0.27, 0.63,
/* 6 */ 0.45, 0.32, 0.65, 0.52,
/* 7 */ 0.44, 0.71, 0.55, 0.071,
/* 8 */ 0.46, 0.53, 0.44, 0.56,
/* 9 */  0.5, 0.63, 0.36, 0.47,
/* 0 */ 0.48, 0.51, 0.53, 0.47,
/* 1 */ 0.26, 0.74,    0, 0.62,
/* 2 */ 0.34, 0.59, 0.57, 0.47,
/* 3 */  0.4,  0.6, 0.38, 0.58,
/* 4 */ 0.25, 0.56, 0.44, 0.66,
/* 5 */ 0.64, 0.47, 0.36,  0.5,
/* 6 */ 0.57, 0.47, 0.49, 0.46,
/* 7 */  0.4, 0.76, 0.51, 0.084,
/* 8 */ 0.52,  0.5,  0.5, 0.48,
/* 9 */ 0.48, 0.48, 0.48, 0.56,
/* 0 */ 0.48, 0.52, 0.49, 0.52,
/* 1 */  0.3, 0.77, 0.34, 0.45,
/* 2 */ 0.31,  0.6, 0.61, 0.41,
/* 3 */  0.3, 0.69, 0.37, 0.54,
/* 4 */ 0.18, 0.65, 0.39, 0.63,
/* 5 */ 0.56, 0.55, 0.39, 0.48,
/* 6 */ 0.54, 0.52,  0.5, 0.44,
/* 7 */ 0.47, 0.68, 0.57, 0.0073,
/* 8 */ 0.46, 0.57, 0.52, 0.45,
/* 9 */ 0.42, 0.51, 0.49, 0.57,
/* 0 */ 0.45, 0.53, 0.54, 0.47,
/* 1 */ 0.29, 0.71,    0, 0.64,
/* 2 */ 0.32, 0.56, 0.55, 0.53,
/* 3 */  0.4, 0.59, 0.38, 0.59,
/* 4 */ 0.27, 0.54, 0.47, 0.65,
/* 5 */ 0.56, 0.49, 0.42, 0.52,
/* 6 */ 0.53, 0.42, 0.52, 0.52,
/* 7 */ 0.49, 0.71, 0.49, 0.12,
/* 8 */  0.5, 0.48, 0.52, 0.51,
/* 9 */ 0.53, 0.52, 0.43, 0.51,
/* 0 */ 0.51, 0.49, 0.51, 0.49,
/* 1 */ 0.37, 0.74, 0.34, 0.45,
/* 2 */ 0.28, 0.63, 0.56, 0.46,
/* 3 */ 0.28, 0.65, 0.39, 0.58,
/* 4 */ 0.19, 0.62, 0.47,  0.6,
/* 5 */ 0.54, 0.53, 0.41,  0.5,
/* 6 */ 0.53, 0.48, 0.53, 0.46,
/* 7 */ 0.49, 0.67, 0.55, 0.031,
/* 8 */ 0.43, 0.57, 0.52, 0.47,
/* 9 */ 0.44, 0.54, 0.46, 0.55,
/* 0 */ 0.46, 0.54, 0.54, 0.45,
/* 1 */ 0.26, 0.74,    0, 0.62,
/* 2 */ 0.34, 0.59, 0.57, 0.47,
/* 3 */  0.4,  0.6, 0.38, 0.58,
/* 4 */ 0.25, 0.56, 0.44, 0.66,
/* 5 */ 0.64, 0.47, 0.36,  0.5,
/* 6 */ 0.57, 0.47, 0.49, 0.46,
/* 7 */  0.4, 0.76, 0.51, 0.084,
/* 8 */ 0.52,  0.5,  0.5, 0.48,
/* 9 */ 0.48, 0.48, 0.48, 0.56,
/* 0 */ 0.48, 0.52, 0.49, 0.52,
/* 1 */  0.3, 0.77, 0.34, 0.45,
/* 2 */ 0.31,  0.6, 0.61, 0.41,
/* 3 */  0.3, 0.69, 0.37, 0.54,
/* 4 */ 0.18, 0.65, 0.39, 0.63,
/* 5 */ 0.56, 0.55, 0.39, 0.48,
/* 6 */ 0.54, 0.52,  0.5, 0.44,
/* 7 */ 0.47, 0.68, 0.57, 0.0073,
/* 8 */ 0.46, 0.57, 0.52, 0.45,
/* 9 */ 0.42, 0.51, 0.49, 0.57,
/* 0 */ 0.45, 0.53, 0.54, 0.47,
/* 1 */ 0.29, 0.71,    0, 0.64,
/* 2 */ 0.32, 0.56, 0.55, 0.53,
/* 3 */  0.4, 0.59, 0.38, 0.59,
/* 4 */ 0.27, 0.54, 0.47, 0.65,
/* 5 */ 0.56, 0.49, 0.42, 0.52,
/* 6 */ 0.53, 0.42, 0.52, 0.52,
/* 7 */ 0.49, 0.71, 0.49, 0.12,
/* 8 */  0.5, 0.48, 0.52, 0.51,
/* 9 */ 0.53, 0.52, 0.43, 0.51,
/* 0 */ 0.51, 0.49, 0.51, 0.49,
/* 1 */ 0.37, 0.74, 0.34, 0.45,
/* 2 */ 0.28, 0.63, 0.56, 0.46,
/* 3 */ 0.28, 0.65, 0.39, 0.58,
/* 4 */ 0.19, 0.62, 0.47,  0.6,
/* 5 */ 0.54, 0.53, 0.41,  0.5,
/* 6 */ 0.53, 0.48, 0.53, 0.46,
/* 7 */ 0.49, 0.67, 0.55, 0.031,
/* 8 */ 0.43, 0.57, 0.52, 0.47,
/* 9 */ 0.44, 0.54, 0.46, 0.55,
/* 0 */ 0.46, 0.54, 0.54, 0.45,
/* 1 */ 0.45, 0.52,  0.4, 0.61,
/* 2 */ 0.23, 0.63,  0.5, 0.55,
/* 3 */ 0.32, 0.63, 0.28, 0.66,
/* 4 */ 0.16, 0.52, 0.37, 0.75,
/* 5 */ 0.59, 0.52, 0.16, 0.59,
/* 6 */  0.5, 0.36, 0.52, 0.59,
/* 7 */ 0.48, 0.69, 0.51, 0.19,
/* 8 */ 0.52, 0.46, 0.48, 0.54,
/* 9 */ 0.55, 0.55, 0.31, 0.54,
/* 0 */ 0.45, 0.55, 0.51, 0.47,
/* 1 */ 0.051, 0.76, 0.57, 0.31,
/* 2 */ 0.16, 0.71, 0.58, 0.36,
/* 3 */ 0.17, 0.73, 0.32, 0.58,
/* 4 */ 0.084, 0.62, 0.44, 0.65,
/* 5 */ 0.44, 0.72, 0.24, 0.48,
/* 6 */  0.4, 0.46, 0.63, 0.49,
/* 7 */ 0.35, 0.76, 0.54, 0.045,
/* 8 */ 0.41, 0.57, 0.51,  0.5,
/* 9 */ 0.48, 0.65, 0.42, 0.41,
/* 0 */ 0.39,  0.6, 0.59, 0.38,
/* 1 */ 0.42, 0.55, 0.36, 0.62,
/* 2 */ 0.25, 0.65, 0.49, 0.52,
/* 3 */ 0.33, 0.62,  0.3, 0.65,
/* 4 */ 0.19, 0.55, 0.36, 0.73,
/* 5 */  0.6,  0.5, 0.16,  0.6,
/* 6 */  0.5, 0.35, 0.54, 0.57,
/* 7 */ 0.45,  0.7, 0.52, 0.17,
/* 8 */ 0.51, 0.46, 0.49, 0.54,
/* 9 */ 0.54, 0.58,  0.3, 0.54,
/* 0 */ 0.48, 0.53, 0.52, 0.47,
/* 1 */ 0.046, 0.75, 0.54, 0.37,
/* 2 */ 0.18, 0.71, 0.56, 0.38,
/* 3 */ 0.19, 0.72, 0.33, 0.58,
/* 4 */ 0.12, 0.65, 0.45,  0.6,
/* 5 */ 0.46, 0.68, 0.25, 0.51,
/* 6 */  0.4, 0.45, 0.62,  0.5,
/* 7 */ 0.34, 0.74, 0.57, 0.067,
/* 8 */ 0.41, 0.56, 0.51,  0.5,
/* 9 */ 0.49, 0.64, 0.41, 0.42,
/* 0 */ 0.39,  0.6, 0.58, 0.39,
/* 1 */ 0.26, 0.74,    0, 0.62,
/* 2 */ 0.34, 0.59, 0.57, 0.47,
/* 3 */  0.4,  0.6, 0.38, 0.58,
/* 4 */ 0.25, 0.56, 0.44, 0.66,
/* 5 */ 0.64, 0.47, 0.36,  0.5,
/* 6 */ 0.57, 0.47, 0.49, 0.46,
/* 7 */  0.4, 0.76, 0.51, 0.084,
/* 8 */ 0.52,  0.5,  0.5, 0.48,
/* 9 */ 0.48, 0.48, 0.48, 0.56,
/* 0 */ 0.48, 0.52, 0.49, 0.52,
/* 1 */  0.3, 0.77, 0.34, 0.45,
/* 2 */ 0.31,  0.6, 0.61, 0.41,
/* 3 */  0.3, 0.69, 0.37, 0.54,
/* 4 */ 0.18, 0.65, 0.39, 0.63,
/* 5 */ 0.56, 0.55, 0.39, 0.48,
/* 6 */ 0.54, 0.52,  0.5, 0.44,
/* 7 */ 0.47, 0.68, 0.57, 0.0073,
/* 8 */ 0.46, 0.57, 0.52, 0.45,
/* 9 */ 0.42, 0.51, 0.49, 0.57,
/* 0 */ 0.45, 0.53, 0.54, 0.47,
/* 1 */ 0.29, 0.71,    0, 0.64,
/* 2 */ 0.32, 0.56, 0.55, 0.53,
/* 3 */  0.4, 0.59, 0.38, 0.59,
/* 4 */ 0.27, 0.54, 0.47, 0.65,
/* 5 */ 0.56, 0.49, 0.42, 0.52,
/* 6 */ 0.53, 0.42, 0.52, 0.52,
/* 7 */ 0.49, 0.71, 0.49, 0.12,
/* 8 */  0.5, 0.48, 0.52, 0.51,
/* 9 */ 0.53, 0.52, 0.43, 0.51,
/* 0 */ 0.51, 0.49, 0.51, 0.49,
/* 1 */ 0.37, 0.74, 0.34, 0.45,
/* 2 */ 0.28, 0.63, 0.56, 0.46,
/* 3 */ 0.28, 0.65, 0.39, 0.58,
/* 4 */ 0.19, 0.62, 0.47,  0.6,
/* 5 */ 0.54, 0.53, 0.41,  0.5,
/* 6 */ 0.53, 0.48, 0.53, 0.46,
/* 7 */ 0.49, 0.67, 0.55, 0.031,
/* 8 */ 0.43, 0.57, 0.52, 0.47,
/* 9 */ 0.44, 0.54, 0.46, 0.55,
/* 0 */ 0.46, 0.54, 0.54, 0.45,
/* 1 */ 0.47, 0.42, 0.49,  0.6,
/* 2 */ 0.28, 0.58, 0.61, 0.45,
/* 3 */ 0.35, 0.65,  0.3,  0.6,
/* 4 */  0.3,  0.6, 0.32, 0.67,
/* 5 */ 0.66, 0.45, 0.27, 0.53,
/* 6 */ 0.57, 0.38, 0.51, 0.52,
/* 7 */ 0.33, 0.79, 0.47, 0.22,
/* 8 */ 0.53, 0.48, 0.47, 0.52,
/* 9 */  0.5, 0.53, 0.39, 0.56,
/* 0 */ 0.49, 0.51, 0.49, 0.51,
/* 1 */ 0.044, 0.68, 0.49, 0.54,
/* 2 */ 0.082,  0.7, 0.62, 0.34,
/* 3 */ 0.14, 0.78, 0.38, 0.47,
/* 4 */ 0.22, 0.65, 0.42,  0.6,
/* 5 */ 0.54,  0.6, 0.42, 0.42,
/* 6 */ 0.46, 0.47, 0.62, 0.41,
/* 7 */ 0.22, 0.83, 0.51, 0.079,
/* 8 */ 0.39,  0.6, 0.56, 0.42,
/* 9 */ 0.39, 0.64, 0.48, 0.46,
/* 0 */ 0.38,  0.6, 0.59, 0.38,
/* 1 */ 0.54, 0.36, 0.53, 0.53,
/* 2 */ 0.31,  0.6, 0.53, 0.52,
/* 3 */ 0.39, 0.58,  0.4, 0.59,
/* 4 */  0.3, 0.57, 0.41, 0.65,
/* 5 */ 0.63, 0.43, 0.33, 0.55,
/* 6 */ 0.52, 0.42,  0.5, 0.55,
/* 7 */ 0.37, 0.75, 0.52,  0.2,
/* 8 */ 0.51, 0.48, 0.49, 0.52,
/* 9 */ 0.55,  0.5, 0.42, 0.52,
/* 0 */  0.5,  0.5,  0.5,  0.5,
/* 1 */ 0.13, 0.68, 0.45, 0.56,
/* 2 */ 0.13,  0.7, 0.55, 0.43,
/* 3 */  0.2, 0.72, 0.44,  0.5,
/* 4 */ 0.17, 0.65, 0.49, 0.56,
/* 5 */ 0.49,  0.6, 0.44, 0.45,
/* 6 */ 0.43,  0.5, 0.61, 0.43,
/* 7 */ 0.24, 0.79, 0.55, 0.11,
/* 8 */ 0.39, 0.59, 0.56, 0.43,
/* 9 */ 0.43, 0.62,  0.5, 0.42,
/* 0 */  0.4, 0.58, 0.58,  0.4,
/* 1 */ 0.26, 0.74,    0, 0.62,
/* 2 */ 0.34, 0.59, 0.57, 0.47,
/* 3 */  0.4,  0.6, 0.38, 0.58,
/* 4 */ 0.25, 0.56, 0.44, 0.66,
/* 5 */ 0.64, 0.47, 0.36,  0.5,
/* 6 */ 0.57, 0.47, 0.49, 0.46,
/* 7 */  0.4, 0.76, 0.51, 0.084,
/* 8 */ 0.52,  0.5,  0.5, 0.48,
/* 9 */ 0.48, 0.48, 0.48, 0.56,
/* 0 */ 0.48, 0.52, 0.49, 0.52,
/* 1 */  0.3, 0.77, 0.34, 0.45,
/* 2 */ 0.31,  0.6, 0.61, 0.41,
/* 3 */  0.3, 0.69, 0.37, 0.54,
/* 4 */ 0.18, 0.65, 0.39, 0.63,
/* 5 */ 0.56, 0.55, 0.39, 0.48,
/* 6 */ 0.54, 0.52,  0.5, 0.44,
/* 7 */ 0.47, 0.68, 0.57, 0.0073,
/* 8 */ 0.46, 0.57, 0.52, 0.45,
/* 9 */ 0.42, 0.51, 0.49, 0.57,
/* 0 */ 0.45, 0.53, 0.54, 0.47,
/* 1 */ 0.29, 0.71,    0, 0.64,
/* 2 */ 0.32, 0.56, 0.55, 0.53,
/* 3 */  0.4, 0.59, 0.38, 0.59,
/* 4 */ 0.27, 0.54, 0.47, 0.65,
/* 5 */ 0.56, 0.49, 0.42, 0.52,
/* 6 */ 0.53, 0.42, 0.52, 0.52,
/* 7 */ 0.49, 0.71, 0.49, 0.12,
/* 8 */  0.5, 0.48, 0.52, 0.51,
/* 9 */ 0.53, 0.52, 0.43, 0.51,
/* 0 */ 0.51, 0.49, 0.51, 0.49,
/* 1 */ 0.37, 0.74, 0.34, 0.45,
/* 2 */ 0.28, 0.63, 0.56, 0.46,
/* 3 */ 0.28, 0.65, 0.39, 0.58,
/* 4 */ 0.19, 0.62, 0.47,  0.6,
/* 5 */ 0.54, 0.53, 0.41,  0.5,
/* 6 */ 0.53, 0.48, 0.53, 0.46,
/* 7 */ 0.49, 0.67, 0.55, 0.031,
/* 8 */ 0.43, 0.57, 0.52, 0.47,
/* 9 */ 0.44, 0.54, 0.46, 0.55,
/* 0 */ 0.46, 0.54, 0.54, 0.45,
/* 1 */ 0.22,  0.7,    0, 0.68,
/* 2 */ 0.29, 0.59, 0.61, 0.45,
/* 3 */ 0.32, 0.61, 0.31, 0.66,
/* 4 */ 0.22, 0.56, 0.44, 0.67,
/* 5 */ 0.63, 0.48, 0.26, 0.55,
/* 6 */ 0.55, 0.33, 0.54, 0.54,
/* 7 */ 0.36, 0.77, 0.52,  0.1,
/* 8 */  0.5, 0.49, 0.51, 0.51,
/* 9 */ 0.56, 0.55, 0.33, 0.53,
/* 0 */ 0.48, 0.51, 0.51, 0.49,
/* 1 */ 0.32, 0.71, 0.49, 0.39,
/* 2 */ 0.21, 0.66,  0.6,  0.4,
/* 3 */ 0.16, 0.71, 0.32, 0.61,
/* 4 */ 0.13,  0.6, 0.39, 0.68,
/* 5 */ 0.57, 0.54,  0.3, 0.53,
/* 6 */ 0.44, 0.44, 0.58, 0.52,
/* 7 */ 0.36, 0.73, 0.58, 0.029,
/* 8 */ 0.43, 0.58, 0.52, 0.45,
/* 9 */ 0.54,  0.6, 0.42, 0.42,
/* 0 */ 0.45, 0.54, 0.55, 0.46,
/* 1 */ 0.26, 0.67,    0, 0.69,
/* 2 */  0.3, 0.58, 0.57, 0.51,
/* 3 */ 0.34, 0.62, 0.31, 0.64,
/* 4 */ 0.21, 0.59, 0.39, 0.68,
/* 5 */ 0.65, 0.47, 0.27, 0.54,
/* 6 */ 0.54, 0.34, 0.55, 0.54,
/* 7 */ 0.39, 0.75, 0.53, 0.12,
/* 8 */  0.5, 0.49, 0.49, 0.52,
/* 9 */ 0.54, 0.57, 0.34, 0.52,
/* 0 */ 0.48, 0.51, 0.51,  0.5,
/* 1 */ 0.42, 0.65, 0.53, 0.34,
/* 2 */  0.2, 0.64, 0.57, 0.48,
/* 3 */ 0.18, 0.69, 0.34, 0.61,
/* 4 */ 0.18, 0.62, 0.41, 0.64,
/* 5 */ 0.57, 0.55, 0.34, 0.51,
/* 6 */ 0.44, 0.46,  0.6, 0.49,
/* 7 */ 0.37, 0.71, 0.59, 0.051,
/* 8 */ 0.43, 0.57, 0.51, 0.48,
/* 9 */ 0.52, 0.59, 0.48, 0.39,
/* 0 */ 0.44, 0.55, 0.54, 0.46,
/* 1 */  0.6, 0.26, 0.58, 0.48,
/* 2 */ 0.28, 0.59, 0.61, 0.45,
/* 3 */ 0.36, 0.63, 0.31, 0.62,
/* 4 */ 0.29, 0.56, 0.41, 0.66,
/* 5 */ 0.64, 0.45, 0.28, 0.56,
/* 6 */ 0.57, 0.41,  0.5, 0.51,
/* 7 */ 0.34,  0.8, 0.43, 0.24,
/* 8 */ 0.53, 0.48, 0.47, 0.51,
/* 9 */ 0.52, 0.51,  0.4, 0.55,
/* 0 */  0.5,  0.5,  0.5,  0.5,
/* 1 */  0.1, 0.66, 0.35, 0.66,
/* 2 */ 0.17, 0.66, 0.61, 0.41,
/* 3 */ 0.22, 0.73, 0.34, 0.54,
/* 4 */  0.2, 0.64, 0.39, 0.64,
/* 5 */ 0.58, 0.55, 0.37, 0.48,
/* 6 */  0.5, 0.49, 0.51, 0.49,
/* 7 */  0.3, 0.79, 0.52, 0.083,
/* 8 */ 0.45, 0.57, 0.51, 0.46,
/* 9 */ 0.47, 0.53, 0.51, 0.49,
/* 0 */ 0.43, 0.56, 0.57, 0.43,
/* 1 */ 0.52, 0.38, 0.51, 0.56,
/* 2 */ 0.32, 0.56, 0.56, 0.52,
/* 3 */  0.4, 0.59, 0.37,  0.6,
/* 4 */ 0.29, 0.57, 0.41, 0.65,
/* 5 */ 0.63, 0.47, 0.33, 0.53,
/* 6 */ 0.54, 0.41, 0.52, 0.52,
/* 7 */ 0.39, 0.75, 0.48, 0.22,
/* 8 */ 0.51, 0.48, 0.48, 0.53,
/* 9 */ 0.52, 0.52, 0.41, 0.54,
/* 0 */ 0.49, 0.51, 0.49, 0.51,
/* 1 */ 0.17, 0.65,  0.4, 0.62,
/* 2 */ 0.21, 0.65, 0.55, 0.48,
/* 3 */ 0.29, 0.68,  0.4, 0.55,
/* 4 */ 0.18, 0.64,  0.4, 0.63,
/* 5 */ 0.53, 0.54,  0.4, 0.51,
/* 6 */ 0.47, 0.47, 0.54, 0.51,
/* 7 */  0.3, 0.77, 0.55, 0.12,
/* 8 */ 0.46, 0.52, 0.54, 0.48,
/* 9 */ 0.49, 0.55, 0.45, 0.49,
/* 0 */ 0.45, 0.55, 0.54, 0.45,
/* 1 */ 0.26, 0.74,    0, 0.62,
/* 2 */ 0.34, 0.59, 0.57, 0.47,
/* 3 */  0.4,  0.6, 0.38, 0.58,
/* 4 */ 0.25, 0.56, 0.44, 0.66,
/* 5 */ 0.64, 0.47, 0.36,  0.5,
/* 6 */ 0.57, 0.47, 0.49, 0.46,
/* 7 */  0.4, 0.76, 0.51, 0.084,
/* 8 */ 0.52,  0.5,  0.5, 0.48,
/* 9 */ 0.48, 0.48, 0.48, 0.56,
/* 0 */ 0.48, 0.52, 0.49, 0.52,
/* 1 */  0.3, 0.77, 0.34, 0.45,
/* 2 */ 0.31,  0.6, 0.61, 0.41,
/* 3 */  0.3, 0.69, 0.37, 0.54,
/* 4 */ 0.18, 0.65, 0.39, 0.63,
/* 5 */ 0.56, 0.55, 0.39, 0.48,
/* 6 */ 0.54, 0.52,  0.5, 0.44,
/* 7 */ 0.47, 0.68, 0.57, 0.0073,
/* 8 */ 0.46, 0.57, 0.52, 0.45,
/* 9 */ 0.42, 0.51, 0.49, 0.57,
/* 0 */ 0.45, 0.53, 0.54, 0.47,
/* 1 */ 0.29, 0.71,    0, 0.64,
/* 2 */ 0.32, 0.56, 0.55, 0.53,
/* 3 */  0.4, 0.59, 0.38, 0.59,
/* 4 */ 0.27, 0.54, 0.47, 0.65,
/* 5 */ 0.56, 0.49, 0.42, 0.52,
/* 6 */ 0.53, 0.42, 0.52, 0.52,
/* 7 */ 0.49, 0.71, 0.49, 0.12,
/* 8 */  0.5, 0.48, 0.52, 0.51,
/* 9 */ 0.53, 0.52, 0.43, 0.51,
/* 0 */ 0.51, 0.49, 0.51, 0.49,
/* 1 */ 0.37, 0.74, 0.34, 0.45,
/* 2 */ 0.28, 0.63, 0.56, 0.46,
/* 3 */ 0.28, 0.65, 0.39, 0.58,
/* 4 */ 0.19, 0.62, 0.47,  0.6,
/* 5 */ 0.54, 0.53, 0.41,  0.5,
/* 6 */ 0.53, 0.48, 0.53, 0.46,
/* 7 */ 0.49, 0.67, 0.55, 0.031,
/* 8 */ 0.43, 0.57, 0.52, 0.47,
/* 9 */ 0.44, 0.54, 0.46, 0.55,
/* 0 */ 0.46, 0.54, 0.54, 0.45,
};

typedef pair<int, int> pii;
typedef vector<vector<char> > vvc;

struct rect {
    int left, right, top, bot;
    rect() : left(-1), right(-1), top(-1), bot(-1) { ; }
};

void resize(rect &r, int i, int j) {
    if(j < r.left || r.left == -1) r.left = j;
    if(j > r.right || r.right == -1) r.right = j;
    if(i < r.top || r.top == -1) r.top = i;
    if(i > r.bot || r.bot == -1) r.bot = i;
}

bool inside(int i, int j, vvc &v) {
	return (i >= 0 && j >= 0) && ((int)v.size() > i && (int)v[i].size() > j);
}

rect fill8(int i, int j, vvc &v, char c) {
	if(!inside(i, j, v) || c == v[i][j]) return rect();
	char old_c = v[i][j];
	stack<pii> s;
	rect r;
	s.push(pii(i, j));
	while(!s.empty()) {
		i = s.top().first, j = s.top().second;
		v[i][j] = c;
		resize(r, i, j);
		s.pop();
		if(inside(i - 1, j - 1, v) && v[i - 1][j - 1] == old_c) s.push(pii(i - 1, j - 1));
		if(inside(i - 1, j, v) && v[i - 1][j] == old_c) s.push(pii(i - 1, j));
		if(inside(i - 1, j + 1, v) && v[i - 1][j + 1] == old_c) s.push(pii(i - 1, j + 1));
		if(inside(i, j - 1, v) && v[i][j - 1] == old_c) s.push(pii(i, j - 1));
		if(inside(i, j + 1, v) && v[i][j + 1] == old_c) s.push(pii(i, j + 1));
		if(inside(i + 1, j - 1, v) && v[i + 1][j - 1] == old_c) s.push(pii(i + 1, j - 1));
		if(inside(i + 1, j, v) && v[i + 1][j] == old_c) s.push(pii(i + 1, j));
		if(inside(i + 1, j + 1, v) && v[i + 1][j + 1] == old_c) s.push(pii(i + 1, j + 1));
	}
	return r;
}

void framed_copy(vvc &v, vvc &u) {
	u.push_back(vector<char>(v[0].size() + 2, '0'));
	for(int i = 0; i < (int)v.size(); i++) {
		u.push_back(vector<char>());
		u.back().push_back('0');
		for(int j = 0; j < (int)v[i].size(); j++)
			u.back().push_back(v[i][j]);
		u.back().push_back('0');
	}
	u.push_back(vector<char>(v[0].size() + 2, '0'));
}

bool find(vvc &v, char c, int &i, int &j) {
	for(int i1 = 0; i1 < (int)v.size(); i1++) {
		for(int j1 = 0; j1 < (int)v[i1].size(); j1++) {
			if(v[i1][j1] == c) {
				i = i1; j = j1;
				return true;
			}
		}
	}
	return false;
}

int holes(vvc &v, rect &r) {
	vector<vector<char> > u;
	framed_copy(v, u);
	int i = 0, j = 0;
	fill8(i, j, u, '1');
	if(!find(u, '0', i, j)) return 0;
	r = fill8(i, j, u, '1');
	if(!find(u, '0', i, j)) return 1;
	return 2;

}

rect search8(int i, int j, vvc &v, vvc &u) {
	if(!inside(i, j, v)) return rect();
	char old_c = v[i][j];
	stack<pii> s;
	rect r;
	s.push(pii(i, j));
	while(!s.empty()) {
		i = s.top().first, j = s.top().second;
		v[i][j] = '0';
		u[i][j] = '1';
		resize(r, i, j);
		s.pop();
		if(inside(i - 1, j - 1, v) && v[i - 1][j - 1] == old_c) s.push(pii(i - 1, j - 1));
		if(inside(i - 1, j, v) && v[i - 1][j] == old_c) s.push(pii(i - 1, j));
		if(inside(i - 1, j + 1, v) && v[i - 1][j + 1] == old_c) s.push(pii(i - 1, j + 1));
		if(inside(i, j - 1, v) && v[i][j - 1] == old_c) s.push(pii(i, j - 1));
		if(inside(i, j + 1, v) && v[i][j + 1] == old_c) s.push(pii(i, j + 1));
		if(inside(i + 1, j - 1, v) && v[i + 1][j - 1] == old_c) s.push(pii(i + 1, j - 1));
		if(inside(i + 1, j, v) && v[i + 1][j] == old_c) s.push(pii(i + 1, j));
		if(inside(i + 1, j + 1, v) && v[i + 1][j + 1] == old_c) s.push(pii(i + 1, j + 1));
	}
	return r;
}

void cut(vvc &v, rect &r, vvc &u) {
	int i, j;
	for(i = r.top; i <= r.bot; i++) {
		u.push_back(vector<char>());
		for(j = r.left; j <= r.right; j++) {
			u.back().push_back(v[i][j]);
			v[i][j] = '0';
		}
	}
}
void to4connectivity(vvc &v, vvc &u) {
	int i, j, i1, j1, i2, j2, i3, j3;
	for(i = 0; i < (int)v.size(); i++) {
		u.push_back(vector<char>());
		for(j = 0; j < (int)v[i].size(); j++)
			u.back().push_back(v[i][j]);
	}
	for(i = 0; i < (int)v.size(); i++) {
		for(j = 0; j < (int)v[i].size(); j++) {
			if(v[i][j] == '0') {
				// * 1
				// 1 0
				i1 = i, j1 = j - 1;
				i2 = i - 1, j2 = j;
				i3 = i - 1, j3 = j - 1;
				if(inside(i1, j1, v) && inside(i2, j2, v) &&
						v[i1][j1] == '1' && v[i2][j2] == '1' && v[i3][j3] == '0') {
					u[i][j] = '1';
					continue;
				}
				// 1 *
				// 0 1
				i1 = i - 1, j1 = j;
				i2 = i, j2 = j + 1;
				i3 = i - 1, j3 = j + 1;
				if(inside(i1, j1, v) && inside(i2, j2, v) &&
						v[i1][j1] == '1' && v[i2][j2] == '1' && v[i3][j3] == '0') {
					u[i][j] = '1';
					continue;
				}
				// 0 1
				// 1 *
				i1 = i, j1 = j + 1;
				i2 = i + 1, j2 = j;
				i3 = i + 1, j3 = j + 1;
				if(inside(i1, j1, v) && inside(i2, j2, v) &&
						v[i1][j1] == '1' && v[i2][j2] == '1' && v[i3][j3] == '0') {
					u[i][j] = '1';
					continue;
				}
				// 1 0
				// * 1
				i1 = i + 1, j1 = j;
				i2 = i, j2 = j - 1;
				i3 = i + 1, j3 = j - 1;
				if(inside(i1, j1, v) && inside(i2, j2, v) &&
						v[i1][j1] == '1' && v[i2][j2] == '1' && v[i3][j3] == '0') {
					u[i][j] = '1';
				}
			}
		}
	}
}

bool isolate(vvc &pixs, vector<vvc> &connected_regions) {
	int h = pixs.size();
	int w = h ? pixs.back().size() : 0;

	if(!h || !w) return false;

	int i, j;
	vvc connected_region;
	for(i = 0; i < h; i++)
		connected_region.push_back(vector<char>(w, '0'));

	for(j = 0; j < w; j++) {
		for(i = 0; i < h; i++) {
			if(pixs[i][j] == '1') {
				rect r = search8(i, j, pixs, connected_region);
				vvc u, v;
				cut(connected_region, r, u);
				to4connectivity(u, v);
				connected_regions.push_back(v);
			}
		}
	}
	return true;
}

void characterise_p(vector<vector<char> > &pixs, int p, vector<double> &v) {
	int h = pixs.size() / p;
	int w = pixs.size() ? pixs.back().size() / p : 0;

	if(!p || !w) return;

	vector<int> I(p + 1), J(p + 1);
	I[0] = 0, I[p] = pixs.size() - 1;
	J[0] = 0, J[p] = pixs.back().size() - 1;
	int k;
	for(k = 1; k <= p - 1; k++) {
		I[k] = I[k - 1] + h;
		J[k] = J[k - 1] + w;
	}

	vector<pair<int, int> > v1;
	int ki, kj, i, j;
	for(ki = 0; ki < p; ki++) {
		for(kj = 0; kj < p; kj++) {
			v1.push_back(pair<int, int>(0, 0));
			for(i = I[ki]; i <= I[ki + 1]; i++)
				for(j = J[kj]; j <= J[kj + 1]; j++)
					if(pixs[i][j] == '1') {
						v1.back().first++;
					} else v1.back().second++;
		}
	}
	for(unsigned int i = 0; i < v1.size(); i++) {
		v.push_back((double)v1[i].first / (v1[i].first + v1[i].second));
	}

	double mod2 = 0;
	for(unsigned int i = 0; i < v.size(); i++)
		mod2 += v[i] * v[i];

	double mod = sqrt(mod2);
	for(unsigned int i = 0; i < v.size(); i++)
		v[i] /= mod;
}

template<class T>T sqr(T x) {
	return x * x;
}

// k \in {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}
double s(vector<double> &v, int k) {
	int i = ((k) ? (k - 1) : 9) * v.size();
	double min = 100.0;
	for( ; i < data_size; i += v.size() * 10) {
		double d = 0.0;
		for(int j = 0; j < (int)v.size(); j++) {
			d += sqr(v[j] - data[i + j]);
		}
		d = sqrt(d);
		if(d < min) min = d;
	}
	return min;
}

int check(vector<vector<char> > &v) {
	vector<double> vd;
	characterise_p(v, 2, vd);
	double s_[] = { 100.0, s(vd, 1), s(vd, 2), s(vd, 3), s(vd, 4),
						s(vd, 5), s(vd, 6), s(vd, 7), s(vd, 8), s(vd, 9), s(vd, 0) };
	int min_i = 0;
	for(int i = 1; i <= 10; i++)
		if(s_[i] < s_[min_i]) min_i = i;

	return min_i % 10;
}

int recognise(vector<vector<char> > &v) {
	double h = (double)v.size();
	double h1 = 0.33 * h;
	double h2 = 0.67 * h;
	rect r;
	vector<double> vd;
	double s4, s6, s9, s0;
	switch(holes(v, r)) {
	case 2:
		return 8;
	case 1:
		// compare 4 with 6, 9, 0
		characterise_p(v, 2, vd);
		s4 = s(vd, 4);
		s6 = s(vd, 6);
		s9 = s(vd, 9);
		s0 = s(vd, 0);
		if(s4 < s6 && s4 < s9 && s4 < s0) {
			if(4 == check(v)) return 4;
		}

		if(r.top + 1.0 > h1) {
			return 6;
		}
		if(r.bot + 1.0 < h2) {
			return 9;
		}
		if(r.top + 1.0 < h1 && r.bot + 1.0 > h2) {
			return 0;
		}
	case 0:
		// compare 1, 2, 3, 4, 5, 7
		if(!vd.size()) characterise_p(v, 2, vd);
		double s_[] = { 100.0, s(vd, 1), s(vd, 2), s(vd, 3), s(vd, 4),
				s(vd, 5), 100.0/*s(vd, 6)*/, s(vd, 7),
				100.0/*s(vd, 8)*/, 100.0/*s(vd, 9)*/, 100.0/*s(vd, 0)*/ };
		int min_i = 0;
		for(int i = 1; i <= 10; i++)
			if(s_[i] < s_[min_i]) min_i = i;

		return min_i;
	}
	return -1;
}

int main() {
	vector<vector<char> > pixs(1);
	char c;
	while(true) {
		if(!cin.get(c)) break;
		if(c == 10) pixs.push_back(vector<char>());
		else pixs.back().push_back(c == '@' || c == '#' || c == '%' ? '1' : '0');
	}
	while(pixs.size() && !pixs.back().size()) {
		pixs.erase(pixs.end() - 1);
	}

	vector<vector<vector<char> > > connected_regions;
	isolate(pixs, connected_regions);

	for(int k = 0; k < (int)connected_regions.size(); k++)
		cout << recognise(connected_regions[k]);

	return 0;
}
