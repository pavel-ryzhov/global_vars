#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <map>
#include <climits>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::copy;
using std::min;
using std::pair;
using std::map;

const size_t projection_lines_count = 9;
const size_t max_digit_count = 3;
const double italics_incline_tangent = 0.4;

struct WeightMin {
  size_t min_position;
  double incline_tangent;
};

struct LineIndexNLinePoint {
  size_t line_index;
  size_t line_point;
};

struct ImageObject {
  size_t object_area;
  double average_distance_from_center;
  double total_distance_from_center;      //sum of distances from center to each object's point
};

typedef pair<char, ImageObject> CharImageObjPair;
typedef map<char, ImageObject> CharImageObjMap;

inline double GetDistance(size_t first_point_x, size_t first_point_y, 
                          size_t second_point_x, size_t second_point_y) {
  double x1 = static_cast<double>(first_point_x);
  double x2 = static_cast<double>(second_point_x);
  double y1 = static_cast<double>(first_point_y);
  double y2 = static_cast<double>(second_point_y);

  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void InitializeUsualDigitLines(vector<vector<double> >* usual_digits_lines) {
  usual_digits_lines->resize(300);
  int zero_pattern_count = 15;
  double zero_data[] = 
    {0.6957, 0.6087, 0.6087, 0.5833, 0.6667, 0.6154, 0.6923, 0.6538, 0.5385,
     0.5789, 0.5263, 0.5263, 0.6667, 0.5833, 0.5833, 0.5833, 0.5652, 0.6087,
     0.5806, 0.8710, 0.6129, 0.6250, 0.7083, 0.6800, 0.7600, 0.7750, 0.7500,
     0.6316, 0.5789, 0.4737, 0.4545, 0.7273, 0.5000, 0.7500, 0.5455, 0.5909,
     0.7895, 0.6316, 0.6842, 0.6923, 0.7692, 0.7143, 0.7857, 0.6250, 0.5833,
     0.6667, 0.3333, 0.6190, 0.5833, 0.6667, 0.6154, 0.6923, 0.4000, 0.5200,
     0.7097, 0.4194, 0.6774, 0.7273, 0.7727, 0.6957, 0.7826, 0.5385, 0.5385,
     0.6875, 0.4375, 0.6250, 0.6364, 0.7273, 0.7273, 0.7273, 0.5000, 0.4000,
     0.7391, 0.5652, 0.6522, 0.6667, 0.7500, 0.6154, 0.7692, 0.6154, 0.6923,
     0.6667, 0.4583, 0.6250, 0.6875, 0.6875, 0.6471, 0.7647, 0.6207, 0.5517,
     0.7273, 0.4091, 0.6364, 0.6667, 0.7333, 0.6250, 0.7500, 0.5926, 0.5556,
     0.7368, 0.3684, 0.6316, 0.7333, 0.8000, 0.6875, 0.8125, 0.4000, 0.4000,
     0.6842, 0.7368, 0.6316, 0.6000, 0.7000, 0.7000, 0.7000, 0.6818, 0.6818,
     0.6786, 0.6786, 0.6071, 0.7059, 0.7059, 0.7059, 0.7647, 0.8182, 0.7879,
     0.6875, 0.5625, 0.5625, 0.5000, 0.7000, 0.6364, 0.7273, 0.5263, 0.5789};
  vector<double> zero_digit(projection_lines_count);
  for (int pattern_index = 0; 
       pattern_index < zero_pattern_count; 
       ++pattern_index) {
    zero_digit.assign(zero_data + pattern_index * projection_lines_count,
      zero_data + (pattern_index + 1)* projection_lines_count);
    usual_digits_lines->at(pattern_index * 10) = zero_digit;
  }

  int unity_pattern_count = 17;
  double unity_data[] = 
    {0.5500, 0.3000, 0.7000, 0.0714, 0.0000, 0.0000, 0.0667, 0.3200, 0.5200,
     0.5000, 0.5000, 0.8000, 0.2500, 0.5000, 0.2175, 0.5625, 0.5789, 0.5789,
     0.5556, 0.4444, 0.6667, 0.1250, 0.2500, 0.0000, 0.3750, 0.4615, 0.4615,
     0.4000, 0.3000, 0.3000, 0.4348, 0.9130, 0.0870, 0.9130, 0.7097, 0.4194,
     0.5714, 0.5714, 0.5714, 0.4444, 0.7778, 0.4444, 0.7778, 0.5833, 0.5833,
     0.4706, 0.4118, 0.7647, 0.3333, 0.0000, 0.3333, 0.3333, 0.5500, 0.5500,
     0.4545, 0.3636, 0.1818, 0.1250, 0.0000, 0.1250, 0.3750, 0.4286, 0.5714,
     0.4167, 0.2500, 0.4167, 0.1667, 0.0000, 0.0000, 0.0769, 0.2941, 0.2941,
     0.4783, 0.3043, 0.8696, 0.2778, 0.0000, 0.1053, 0.2105, 0.3000, 0.5667,
     0.7273, 0.4545, 0.4545, 0.2667, 0.8667, 0.1333, 0.8667, 0.4211, 0.4211,
     0.5000, 0.3333, 0.3333, 0.4167, 0.8333, 0.1538, 0.8462, 0.5882, 0.3529,
     0.5517, 0.2759, 0.8621, 0.1500, 0.0000, 0.1429, 0.1905, 0.2778, 0.5833,
     0.4706, 0.4118, 0.7647, 0.3333, 0.0000, 0.1000, 0.3000, 0.5500, 0.5500,
     0.7273, 0.3636, 0.3636, 0.1667, 0.8889, 0.1111, 0.8889, 0.4545, 0.4545,
     0.5238, 0.3333, 0.6190, 0.0952, 0.0476, 0.0000, 0.0909, 0.4000, 0.5333,
     0.3333, 0.3333, 0.3333, 0.4000, 0.9000, 0.1000, 0.9000, 0.7037, 0.4444,
     0.6111, 0.3333, 0.7778, 0.1765, 0.0588, 0.0000, 0.1176, 0.3600, 0.3600};
  vector<double> unity_digit(projection_lines_count);
  for (int pattern_index = 0; 
       pattern_index < unity_pattern_count; 
       ++pattern_index) {
    unity_digit.assign(unity_data + pattern_index * projection_lines_count,
      unity_data + (pattern_index + 1)* projection_lines_count);
    usual_digits_lines->at(pattern_index * 10 + 1) = unity_digit;
  }

  int two_pattern_count = 20;
  double two_data[] = 
    {0.6579, 0.7105, 0.9211, 0.3913, 0.6957, 0.6087, 0.4348, 0.7111, 0.7778,
     0.5833, 0.5000, 0.8750, 0.4091, 0.7273, 0.2273, 0.1818, 0.2727, 0.7273,
     0.5882, 0.4118, 0.8235, 0.5000, 0.6667, 0.0833, 0.5833, 0.3810, 0.4286,
     0.4500, 0.6000, 0.8000, 0.2000, 0.4000, 0.0000, 0.5455, 0.5652, 0.6957,
     0.6667, 0.6111, 0.8333, 0.4286, 0.5714, 0.2143, 0.1429, 0.4348, 0.6087,
     0.4167, 0.3333, 0.5278, 0.1176, 0.0000, 0.5294, 0.4118, 0.4750, 0.6000,
     0.2703, 0.5405, 0.5135, 0.0000, 0.1176, 0.4118, 0.3529, 0.5854, 0.6098,
     0.6000, 0.4667, 0.7333, 0.3750, 0.5000, 0.0000, 0.3333, 0.3889, 0.5000,
     0.5833, 0.5833, 0.7500, 0.4286, 0.5714, 0.4286, 0.2857, 0.3571, 0.4286,
     0.6111, 0.3889, 0.7778, 0.2727, 0.4545, 0.0000, 0.3333, 0.3182, 0.5000,
     0.5769, 0.3846, 0.8462, 0.3333, 0.5556, 0.0000, 0.3333, 0.3125, 0.6250,
     0.6970, 0.5152, 0.8788, 0.2609, 0.6087, 0.2917, 0.2083, 0.2683, 0.7073,
     0.6316, 0.4211, 0.7895, 0.0769, 0.5385, 0.0000, 0.2308, 0.2917, 0.5417,
     0.6087, 0.4348, 0.8696, 0.2500, 0.6875, 0.0625, 0.4375, 0.2069, 0.6552,
     0.6250, 0.5417, 0.8750, 0.4375, 0.6250, 0.1875, 0.3750, 0.3793, 0.5172,
     0.7000, 0.6500, 0.8500, 0.5333, 0.7333, 0.1333, 0.2000, 0.6923, 0.7308,
     0.6667, 0.7143, 0.8571, 0.3125, 0.6250, 0.6250, 0.2500, 0.2963, 0.4444,
     0.6250, 0.5625, 0.7500, 0.2500, 0.3750, 0.1250, 0.2500, 0.3333, 0.5556,
     0.6667, 0.6333, 0.8667, 0.5417, 0.6667, 0.5600, 0.4800, 0.6410, 0.6667,
     0.6552, 0.6897, 0.8276, 0.5455, 0.6818, 0.0000, 0.3636, 0.3784, 0.7568};
  vector<double> two_digit(projection_lines_count);
  for (int pattern_index = 0; 
       pattern_index < two_pattern_count; 
       ++pattern_index) {
    two_digit.assign(two_data + pattern_index * projection_lines_count,
      two_data + (pattern_index + 1)* projection_lines_count);
    usual_digits_lines->at(pattern_index * 10 + 2) = two_digit;
  }

  int three_pattern_count = 17;
  double three_data[] = 
    {0.6316, 0.6842, 0.4737, 0.2727, 0.5455, 0.3333, 0.6667, 0.5000, 0.5909,
     0.5833, 0.5000, 0.6250, 0.3636, 0.6364, 0.3043, 0.7826, 0.1818, 0.3333,
     0.5455, 0.7273, 0.6364, 0.3750, 0.5000, 0.1250, 0.6250, 0.2143, 0.2857,
     0.6667, 0.6667, 0.6667, 0.3333, 0.5333, 0.1875, 0.7500, 0.2692, 0.5769,
     0.5455, 0.5455, 0.7273, 0.1250, 0.5000, 0.2500, 0.6875, 0.3214, 0.5714,
     0.6250, 0.5000, 0.6875, 0.5455, 0.5455, 0.4167, 0.6667, 0.3500, 0.5000,
     0.7391, 0.6087, 0.7391, 0.2500, 0.5833, 0.3846, 0.6923, 0.3462, 0.6538,
     0.7692, 0.6923, 0.6154, 0.0000, 0.1429, 0.3750, 0.7500, 0.5333, 0.4667,
     0.6667, 0.7333, 0.7333, 0.2222, 0.5556, 0.3333, 0.6667, 0.3889, 0.6111,
     0.5714, 0.6429, 0.5000, 0.1111, 0.3333, 0.3000, 0.6000, 0.2941, 0.5294,
     0.6818, 0.6818, 0.6818, 0.1765, 0.5882, 0.1765, 0.7059, 0.3214, 0.5000,
     0.6538, 0.7308, 0.7308, 0.1053, 0.5263, 0.0526, 0.6316, 0.3333, 0.3939,
     0.6154, 0.6154, 0.7692, 0.2381, 0.5238, 0.1364, 0.7273, 0.2941, 0.5588,
     0.5833, 0.5000, 0.5833, 0.5714, 0.4286, 0.4286, 0.5714, 0.2857, 0.3571,
     0.6250, 0.6250, 0.6875, 0.2500, 0.4167, 0.0833, 0.6667, 0.2857, 0.4286,
     0.6667, 0.6667, 0.5333, 0.2500, 0.5833, 0.0000, 0.7692, 0.1500, 0.3000,
     0.6000, 0.4800, 0.6800, 0.4000, 0.5500, 0.3333, 0.7143, 0.3333, 0.4545};
  vector<double> three_digit(projection_lines_count);
  for (int pattern_index = 0; 
       pattern_index < three_pattern_count; 
       ++pattern_index) {
    three_digit.assign(three_data + pattern_index * projection_lines_count,
      three_data + (pattern_index + 1)* projection_lines_count);
    usual_digits_lines->at(pattern_index * 10 + 3) = three_digit;
  }

  int four_pattern_count = 20;
  double four_data[] = 
    {0.3750, 0.6563, 0.4688, 0.0000, 0.0000, 0.2778, 0.2778, 0.5676, 0.6216,
     0.1667, 0.3889, 0.5000, 0.0000, 0.0833, 0.2500, 0.1667, 0.3636, 0.4545,
     0.2581, 0.9032, 0.2903, 0.0000, 0.0000, 0.3889, 0.3333, 0.6389, 0.6667,
     0.3750, 0.8750, 0.1250, 0.0000, 0.0000, 0.1667, 0.0000, 0.4762, 0.2857,
     0.2857, 0.7143, 0.4762, 0.0000, 0.3000, 0.5455, 0.5455, 0.6250, 0.7083,
     0.2941, 0.5882, 0.2353, 0.0000, 0.3000, 0.2727, 0.3636, 0.4500, 0.4500,
     0.2857, 0.5714, 0.2000, 0.0000, 0.1364, 0.3913, 0.4348, 0.5714, 0.5952,
     0.3500, 0.5500, 0.6500, 0.0000, 0.1538, 0.3077, 0.3846, 0.5833, 0.5417,
     0.6190, 0.8095, 0.4286, 0.1333, 0.4667, 0.6667, 0.6667, 0.7692, 0.6538,
     0.7059, 0.8824, 0.4118, 0.4444, 0.3889, 0.2222, 0.3333, 0.6800, 0.4000,
     0.4000, 0.6000, 0.4667, 0.0000, 0.5000, 0.2727, 0.6364, 0.5263, 0.5263,
     0.5172, 0.7586, 0.2069, 0.0000, 0.3889, 0.2222, 0.6111, 0.6571, 0.5429,
     0.2500, 0.5500, 0.2000, 0.0000, 0.2667, 0.3125, 0.3750, 0.4615, 0.5000,
     0.3333, 0.7037, 0.3704, 0.0000, 0.2857, 0.4000, 0.4667, 0.5161, 0.7097,
     0.4167, 0.7083, 0.2917, 0.0000, 0.4167, 0.3846, 0.4615, 0.6667, 0.7037,
     0.3333, 0.6667, 0.7222, 0.0000, 0.0000, 0.4167, 0.4167, 0.5909, 0.5455,
     0.3333, 0.6667, 0.2667, 0.0000, 0.2222, 0.4000, 0.3000, 0.5000, 0.6111,
     0.3529, 0.7059, 0.2353, 0.0000, 0.3000, 0.2727, 0.5455, 0.6000, 0.6000,
     0.1875, 0.5625, 0.2500, 0.0000, 0.0000, 0.3000, 0.4000, 0.4211, 0.5263,
     0.4118, 0.7647, 0.4118, 0.0000, 0.5000, 0.4000, 0.5000, 0.6500, 0.7000};
  vector<double> four_digit(projection_lines_count);
  for (int pattern_index = 0; 
       pattern_index < four_pattern_count; 
       ++pattern_index) {
    four_digit.assign(four_data + pattern_index * projection_lines_count,
      four_data + (pattern_index + 1)* projection_lines_count);
    usual_digits_lines->at(pattern_index * 10 + 4) = four_digit;
  }

  int five_pattern_count = 24;
  double five_data[] = 
    {0.7949, 0.8974, 0.6667, 0.4348, 0.3043, 0.2609, 0.6957, 0.8478, 0.8043,
     0.7333, 0.5333, 0.5333, 0.5000, 0.1000, 0.3000, 0.7000, 0.4737, 0.2105,
     0.8077, 0.5769, 0.6923, 0.6667, 0.2857, 0.0000, 0.7273, 0.7059, 0.3824,
     0.3684, 0.7895, 0.4737, 0.0000, 0.0000, 0.3077, 0.6923, 0.6957, 0.5652,
     0.7619, 0.6190, 0.6667, 0.2500, 0.5000, 0.7500, 0.6667, 0.5600, 0.5600,
     0.6585, 0.7073, 0.6585, 0.1481, 0.2222, 0.3571, 0.6786, 0.5400, 0.7400,
     0.6429, 0.6786, 0.7143, 0.0000, 0.0000, 0.2500, 0.7500, 0.6176, 0.4706,
     0.8421, 0.6316, 0.4211, 0.7222, 0.6111, 0.0556, 0.0000, 0.7407, 0.7037,
     0.6429, 0.6429, 0.6429, 0.3000, 0.4000, 0.1818, 0.7273, 0.6667, 0.5000,
     0.7586, 0.9310, 0.6207, 0.6000, 0.0500, 0.3500, 0.7000, 0.6944, 0.5556,
     0.7333, 0.8000, 0.6667, 0.4444, 0.0000, 0.4444, 0.6666, 0.6666, 0.6666,
     0.7368, 0.7895, 0.6842, 0.3333, 0.0000, 0.1538, 0.6923, 0.2174, 0.5217,
     0.8889, 0.8889, 0.6111, 0.8000, 0.0000, 0.4667, 0.8000, 0.3750, 0.3333,
     0.8182, 0.7273, 0.5455, 0.8571, 0.4286, 0.7143, 0.7143, 0.3571, 0.2857,
     0.8182, 0.8636, 0.6364, 0.5000, 0.0625, 0.4375, 0.7500, 0.5714, 0.4286,
     0.7500, 0.7500, 0.6250, 0.2727, 0.2727, 0.2727, 0.7273, 0.4500, 0.3000,
     0.8000, 0.8000, 0.6500, 0.5000, 0.0000, 0.3571, 0.7857, 0.3600, 0.3200,
     0.7500, 0.8000, 0.6000, 0.3846, 0.0000, 0.3077, 0.5385, 0.5000, 0.4167,
     0.7273, 0.6364, 0.6364, 0.3750, 0.0000, 0.5625, 0.6875, 0.7143, 0.5714,
     0.7222, 0.7778, 0.6667, 0.3846, 0.0769, 0.3077, 0.6923, 0.5652, 0.3913,
     0.6667, 0.5556, 0.7037, 0.0476, 0.1905, 0.0952, 0.6667, 0.6857, 0.4000,
     0.8750, 0.8333, 0.7500, 0.7619, 0.1429, 0.1818, 0.7727, 0.6563, 0.6250,
     0.7059, 0.7353, 0.6765, 0.0417, 0.1250, 0.2083, 0.5417, 0.7619, 0.5714,
     0.8333, 0.6667, 0.6667, 0.7500, 0.0000, 0.3750, 0.6250, 0.3333, 0.2667};
  vector<double> five_digit(projection_lines_count);
  for (int pattern_index = 0; 
       pattern_index < five_pattern_count; 
       ++pattern_index) {
    five_digit.assign(five_data + pattern_index * projection_lines_count,
      five_data + (pattern_index + 1)* projection_lines_count);
    usual_digits_lines->at(pattern_index * 10 + 5) = five_digit;
  }

  int six_pattern_count = 15;
  double six_data[] = 
    {0.7333, 0.8667, 0.3333, 0.4444, 0.0000, 0.5000, 0.8000, 0.1111, 0.4444,
     0.6667, 0.8750, 0.5833, 0.5833, 0.0000, 0.5385, 0.6154, 0.6296, 0.5926,
     0.3333, 0.8519, 0.5926, 0.0000, 0.0000, 0.6111, 0.6667, 0.5625, 0.6563,
     0.5200, 0.9200, 0.6400, 0.5833, 0.3333, 0.6154, 0.6923, 0.5000, 0.8214,
     0.6154, 0.8462, 0.5385, 0.0000, 0.0000, 0.5000, 0.6250, 0.4375, 0.5000,
     0.6818, 0.8636, 0.5909, 0.6250, 0.3750, 0.6250, 0.6875, 0.5714, 0.4286,
     0.7391, 0.9130, 0.6522, 0.6471, 0.0588, 0.6111, 0.7222, 0.5172, 0.4828,
     0.7000, 0.8667, 0.6333, 0.5455, 0.1364, 0.5652, 0.7826, 0.6053, 0.4737,
     0.6667, 0.9048, 0.5714, 0.6667, 0.2778, 0.6111, 0.7222, 0.7857, 0.5714,
     0.7188, 0.9063, 0.6875, 0.6818, 0.0000, 0.6522, 0.7391, 0.5385, 0.5128,
     0.7391, 0.7826, 0.6522, 0.5625, 0.0625, 0.5882, 0.6471, 0.4138, 0.4138,
     0.7143, 0.9048, 0.5714, 0.5714, 0.2143, 0.5714, 0.7857, 0.5000, 0.3462,
     0.6552, 0.8966, 0.6552, 0.5455, 0.4091, 0.6818, 0.7273, 0.8378, 0.5676,
     0.5652, 0.9130, 0.6087, 0.1875, 0.0000, 0.6250, 0.8125, 0.5862, 0.4138,
     0.6250, 0.8750, 0.6250, 0.4000, 0.3000, 0.5000, 0.7000, 0.5789, 0.4211};
  vector<double> six_digit(projection_lines_count);
  for (int pattern_index = 0; 
       pattern_index < six_pattern_count; 
       ++pattern_index) {
    six_digit.assign(six_data + pattern_index * projection_lines_count,
      six_data + (pattern_index + 1)* projection_lines_count);
    usual_digits_lines->at(pattern_index * 10 + 6) = six_digit;
  }

  int seven_pattern_count = 17;
  double seven_data[] = 
    {0.8750, 0.3750, 0.1875, 0.2727, 0.5455, 0.0000, 0.0000, 0.2500, 0.3500,
     0.9167, 0.3750, 0.1667, 0.1905, 0.6667, 0.0000, 0.0000, 0.4688, 0.3750,
     0.6667, 0.2667, 0.1333, 0.4000, 0.6000, 0.0000, 0.0000, 0.2632, 0.2105,
     0.8571, 0.4286, 0.4286, 0.5625, 0.6875, 0.3750, 0.0000, 0.2273, 0.5909,
     0.8889, 0.6111, 0.3889, 0.5000, 0.6000, 0.0909, 0.0000, 0.6190, 0.5238,
     0.8462, 0.4231, 0.2692, 0.4706, 0.5882, 0.0000, 0.0000, 0.3750, 0.4063,
     0.8000, 0.2667, 0.2667, 0.4000, 0.5000, 0.0000, 0.0000, 0.2632, 0.4211,
     0.8261, 0.3478, 0.2609, 0.4706, 0.6471, 0.0000, 0.0000, 0.2759, 0.3793,
     0.7297, 0.3784, 0.2162, 0.4348, 0.5652, 0.0000, 0.0000, 0.4318, 0.4318,
     0.9259, 0.3333, 0.2963, 0.5556, 0.6667, 0.0000, 0.0000, 0.3030, 0.4242,
     0.8889, 0.2222, 0.2778, 0.3333, 0.7500, 0.0000, 0.0769, 0.1364, 0.3636,
     0.8824, 0.4118, 0.2353, 0.1667, 0.5833, 0.0000, 0.0000, 0.3810, 0.3810,
     0.7692, 0.3077, 0.3077, 0.5000, 0.6250, 0.0000, 0.1111, 0.3750, 0.4375,
     0.9130, 0.4783, 0.3043, 0.1875, 0.5625, 0.0000, 0.0000, 0.3793, 0.4138,
     0.8235, 0.2941, 0.2353, 0.4167, 0.6667, 0.0000, 0.0000, 0.2857, 0.3333,
     0.8095, 0.2857, 0.2857, 0.4118, 0.7647, 0.0000, 0.0000, 0.2143, 0.4643,
     0.8800, 0.3600, 0.2400, 0.4500, 0.4000, 0.0000, 0.0000, 0.3939, 0.3636};
  vector<double> seven_digit(projection_lines_count);
  for (int pattern_index = 0; 
       pattern_index < seven_pattern_count; 
       ++pattern_index) {
    seven_digit.assign(seven_data + pattern_index * projection_lines_count,
      seven_data + (pattern_index + 1)* projection_lines_count);
    usual_digits_lines->at(pattern_index * 10 + 7) = seven_digit;
  }

  int eight_pattern_count = 26;
  double eight_data[] = 
    {0.2813, 0.7188, 0.6563, 0.2609, 0.3478, 0.5652, 0.6087, 0.6500, 0.5000,
     0.6316, 0.6316, 0.4737, 0.4545, 0.6364, 0.4167, 0.6667, 0.3636, 0.6364,
     0.5926, 0.7407, 0.6296, 0.4118, 0.5294, 0.5000, 0.5556, 0.7188, 0.6875,
     0.4667, 0.8667, 0.6000, 0.2000, 0.6000, 0.6364, 0.7273, 0.5789, 0.6316,
     0.6471, 0.7647, 0.7353, 0.4211, 0.4737, 0.5500, 0.7000, 0.5385, 0.7692,
     0.5556, 0.7222, 0.6667, 0.5000, 0.5714, 0.6000, 0.7333, 0.5652, 0.4348,
     0.8000, 0.4800, 0.5200, 0.3333, 0.4667, 0.0000, 0.3333, 0.6667, 0.5667,
     0.6471, 0.7647, 0.5882, 0.3000, 0.5000, 0.5000, 0.6000, 0.5000, 0.5000,
     0.6667, 0.6667, 0.6667, 0.3636, 0.5455, 0.5000, 0.7500, 0.4091, 0.6364,
     0.6364, 0.5455, 0.5455, 0.5000, 0.5000, 0.5556, 0.6667, 0.3571, 0.5714,
     0.7000, 0.9000, 0.7000, 0.6667, 0.6000, 0.7333, 0.7333, 0.7692, 0.8077,
     0.6667, 0.6667, 0.5833, 0.4286, 0.5714, 0.7143, 0.4286, 0.4286, 0.4286,
     0.6667, 0.7778, 0.7222, 0.4167, 0.5000, 0.6154, 0.7692, 0.5000, 0.5455,
     0.6522, 0.6522, 0.5217, 0.4375, 0.6250, 0.5882, 0.7059, 0.4138, 0.5172,
     0.6364, 0.8182, 0.6364, 0.5333, 0.6000, 0.6000, 0.6667, 0.4444, 0.4074,
     0.6154, 0.7692, 0.6923, 0.5000, 0.5556, 0.5789, 0.6842, 0.5625, 0.5000,
     0.6071, 0.6429, 0.6429, 0.5417, 0.5000, 0.6250, 0.6250, 0.5135, 0.4054,
     0.6250, 0.7500, 0.6250, 0.2727, 0.6364, 0.5455, 0.6364, 0.4500, 0.3500,
     0.5882, 0.7647, 0.5294, 0.5556, 0.5000, 0.6111, 0.6667, 0.5600, 0.4400,
     0.6250, 0.7500, 0.5625, 0.5556, 0.6111, 0.6111, 0.6667, 0.5200, 0.4000,
     0.5714, 0.6429, 0.4286, 0.4444, 0.6667, 0.5000, 0.7000, 0.4118, 0.5882,
     0.6000, 0.8000, 0.6000, 0.3000, 0.6000, 0.5000, 0.7000, 0.3684, 0.3684,
     0.6500, 0.7500, 0.6000, 0.4000, 0.3000, 0.5000, 0.5000, 0.6522, 0.5652,
     0.6667, 0.8000, 0.7000, 0.5417, 0.5833, 0.6000, 0.7600, 0.6667, 0.6410,
     0.6786, 0.8571, 0.6429, 0.4706, 0.5882, 0.5882, 0.7059, 0.7576, 0.8485,
     0.6000, 0.6000, 0.4667, 0.5000, 0.6000, 0.4545, 0.7273, 0.4211, 0.5789};
  vector<double> eight_digit(projection_lines_count);
  for (int pattern_index = 0; 
       pattern_index < eight_pattern_count; 
       ++pattern_index) {
    eight_digit.assign(eight_data + pattern_index * projection_lines_count,
      eight_data + (pattern_index + 1)* projection_lines_count);
    usual_digits_lines->at(pattern_index * 10 + 8) = eight_digit;
  }

  int nine_pattern_count = 23;
  double nine_data[] = 
    {0.7059, 0.8235, 0.6471, 0.6364, 0.7273, 0.2500, 0.7500, 0.3333, 0.6667,
     0.5882, 0.8235, 0.6471, 0.5833, 0.7500, 0.4167, 0.6667, 0.2857, 0.3810,
     0.7500, 0.8750, 0.5000, 0.6923, 0.7692, 0.0000, 0.4286, 0.7500, 0.5714,
     0.5349, 0.8837, 0.2558, 0.5806, 0.7742, 0.0000, 0.8387, 0.8519, 0.4630,
     0.5263, 0.8421, 0.5789, 0.6429, 0.6429, 0.2000, 0.6667, 0.5833, 0.7083,
     0.6250, 0.7917, 0.2917, 0.5789, 0.7368, 0.0000, 0.0000, 0.4839, 0.5806,
     0.6000, 0.8000, 0.6000, 0.5000, 0.8000, 0.3000, 0.7000, 0.3684, 0.4737,
     0.6364, 0.8788, 0.6667, 0.6522, 0.6957, 0.2917, 0.7500, 0.5854, 0.7805,
     0.6207, 0.6552, 0.6552, 0.5909, 0.7273, 0.1818, 0.6818, 0.5135, 0.6486,
     0.6667, 0.8333, 0.5000, 0.5833, 0.8333, 0.0833, 0.6667, 0.5000, 0.2727,
     0.6154, 0.7692, 0.3077, 0.7500, 0.5000, 0.0000, 0.5000, 0.5000, 0.3125,
     0.6471, 0.8235, 0.4706, 0.7273, 0.6364, 0.0000, 0.1818, 0.6190, 0.4762,
     0.7500, 0.8125, 0.6875, 0.7273, 0.8182, 0.0833, 0.7500, 0.4500, 0.7000,
     0.7500, 0.8750, 0.6250, 0.6667, 0.7778, 0.4000, 0.7000, 0.3684, 0.5789,
     0.5769, 0.8846, 0.5769, 0.6111, 0.7778, 0.0556, 0.6111, 0.5625, 0.4375,
     0.6667, 0.8889, 0.6296, 0.7273, 0.7727, 0.3182, 0.7273, 0.6571, 0.6857,
     0.7391, 0.8261, 0.6522, 0.5833, 0.7500, 0.0769, 0.6154, 0.4615, 0.5385,
     0.6522, 0.8696, 0.7391, 0.5833, 0.7500, 0.3077, 0.6923, 0.5769, 0.8077,
     0.6176, 0.8824, 0.6765, 0.6250, 0.7917, 0.2083, 0.6667, 0.5476, 0.6667,
     0.6842, 0.7895, 0.4737, 0.5385, 0.7692, 0.0000, 0.1429, 0.4583, 0.5833,
     0.6522, 0.8261, 0.6087, 0.6000, 0.7333, 0.0625, 0.6250, 0.5714, 0.5714,
     0.6154, 0.7692, 0.6154, 0.5714, 0.7143, 0.1250, 0.5000, 0.4000, 0.6000,
     0.6316, 0.8421, 0.5789, 0.6429, 0.7143, 0.0000, 0.5714, 0.5000, 0.4167};
  vector<double> nine_digit(projection_lines_count);
  for (int pattern_index = 0; 
       pattern_index < nine_pattern_count; 
       ++pattern_index) {
    nine_digit.assign(nine_data + pattern_index * projection_lines_count,
      nine_data + (pattern_index + 1)* projection_lines_count);
    usual_digits_lines->at(pattern_index * 10 + 9) = nine_digit;
  }
}

int RecognizeProjection(const vector<vector<bool> >& digit_circuit_lines, 
                           const vector<vector<double> >& usual_digits_lines) {
  vector<double> digit_lines_fullness;

  size_t lines_count = digit_circuit_lines.size();
  for (size_t line_index = 0; line_index < lines_count; ++line_index) {
    size_t line_size = digit_circuit_lines.at(line_index).size();
    size_t full_points = 0;

    for (size_t point_index = 0; point_index < line_size; ++point_index) {
      if (digit_circuit_lines.at(line_index).at(point_index)) {
        ++full_points;
      }
    }
    if (line_size) {
      digit_lines_fullness.push_back(
          static_cast<double>(full_points) / line_size);
    }
  }

  double min_diff = 100;
  size_t best_fit_digit = 0;

  for (size_t digit_index = 0; 
       digit_index < usual_digits_lines.size(); 
       ++digit_index) {
    double curr_diff = 0;

    if (usual_digits_lines.at(digit_index).size()) {
      for (size_t line_index = 0; line_index < lines_count; ++line_index) {
        curr_diff += fabs(
            usual_digits_lines.at(digit_index).at(line_index) - 
              digit_lines_fullness.at(line_index));
      }
      if (curr_diff < min_diff) {
        best_fit_digit = digit_index;
        min_diff = curr_diff;
      }
    }
  }

  return (best_fit_digit % 10);
}

LineIndexNLinePoint GetNearestLineIndex(size_t x_point, size_t y_point, 
                                        size_t x_size, size_t y_size) {
  LineIndexNLinePoint result;

  size_t reverse_x_point = x_size - x_point - 1;

  double diagonal_size = GetDistance(0, 0, x_size, y_size / 2);
  bool topmost_half = y_point < y_size / 2;
  if (!topmost_half) {
    y_point -= y_size / 2;
  }

  size_t reverse_y_point = y_size / 2 - y_point - 1;
  size_t half_area = x_size * y_size / 2;
  double distance_to_horizontal = static_cast<double>(
    min(y_point, reverse_y_point));
  double distance_to_vertical = static_cast<double>(
    min(x_point, reverse_x_point));
  double distance_to_diagonal;
  bool topmost_triangle = 
    x_point * y_size / 2 + y_point * x_size <= half_area;
  if (topmost_triangle) {
    distance_to_diagonal = 
      (half_area - x_point * y_size / 2 - y_point * x_size) / diagonal_size;
  } else {
    distance_to_diagonal = 
      (half_area - reverse_x_point * y_size / 2 - reverse_y_point * x_size) /
      diagonal_size;
  }
  if (distance_to_horizontal < 
      min(distance_to_vertical, distance_to_diagonal)) {
    if (topmost_half) {
      if (topmost_triangle) {
        result.line_index = 0;
      } else {
        result.line_index = 1;
      }
    } else {
      if (topmost_triangle) {
        result.line_index = 1;
      } else {
        result.line_index = 2;
      }
    }
    result.line_point = x_point;
  } else if (distance_to_vertical < distance_to_diagonal) {
    if (topmost_half) {
      if (topmost_triangle) {
        result.line_index = 3;
      } else {
        result.line_index = 4;
      }
    } else {
      if (topmost_triangle) {
        result.line_index = 5;
      } else {
        result.line_index = 6;
      }
    }
    result.line_point = y_point;
  } else {
    if (topmost_half) {
      result.line_index = 7;
    } else {
      result.line_index = 8;
    }
    if (topmost_triangle) {
      double hypotenuse_square = x_point * x_point + 
        reverse_y_point * reverse_y_point;
      result.line_point = static_cast<size_t>(sqrt(
        hypotenuse_square - distance_to_diagonal * distance_to_diagonal));
    } else {
      double hypotenuse_square = y_point * y_point + 
        reverse_x_point * reverse_x_point;
      result.line_point = static_cast<size_t>(diagonal_size - sqrt(
        hypotenuse_square - distance_to_diagonal * distance_to_diagonal));
    }
  }
  return result;
}

void PaintCharTilWhiteSpace(vector<vector<char> >& image, 
                              size_t x_point, size_t y_point, 
                              char paint_char) {

  size_t image_y_size = image.size();
  size_t image_x_size = image.at(0).size();

  image.at(y_point).at(x_point) = paint_char;

  char current_char;

  if (x_point > 0) {
    current_char = image.at(y_point).at(x_point - 1);
    if (current_char == '@' || current_char == '#' || current_char == '%') {
      PaintCharTilWhiteSpace(image, x_point - 1, y_point, paint_char);
    }
    if (y_point > 0) {
      current_char = image.at(y_point - 1).at(x_point - 1);
      if (current_char == '@' || current_char == '#' || current_char == '%') {
        PaintCharTilWhiteSpace(image, x_point - 1, y_point - 1, paint_char);
      }
      current_char = image.at(y_point - 1).at(x_point);
      if (current_char == '@' || current_char == '#' || current_char == '%') {
        PaintCharTilWhiteSpace(image, x_point, y_point - 1, paint_char);
      }
    }
    if (y_point < image_y_size - 1) {
      current_char = image.at(y_point + 1).at(x_point - 1);
      if (current_char == '@' || current_char == '#' || current_char == '%') {
        PaintCharTilWhiteSpace(image, x_point - 1, y_point + 1, paint_char);
      }
      current_char = image.at(y_point + 1).at(x_point);
      if (current_char == '@' || current_char == '#' || current_char == '%') {
        PaintCharTilWhiteSpace(image, x_point, y_point + 1, paint_char);
      }
    }
  }
  if (x_point < image_x_size - 1) {
    current_char = image.at(y_point).at(x_point + 1);
    if (current_char == '@' || current_char == '#' || current_char == '%') {
      PaintCharTilWhiteSpace(image, x_point + 1, y_point, paint_char);
    }
    if (y_point > 0) {
      current_char = image.at(y_point - 1).at(x_point + 1);
      if (current_char == '@' || current_char == '#' || current_char == '%') {
        PaintCharTilWhiteSpace(image, x_point + 1, y_point - 1, paint_char);
      }
    }
    if (y_point < image_y_size - 1) {
      current_char = image.at(y_point + 1).at(x_point + 1);
      if (current_char == '@' || current_char == '#' || current_char == '%') {
        PaintCharTilWhiteSpace(image, x_point + 1, y_point + 1, paint_char);
      }
    }
  }
}

void AnnihilateNonDigits(vector<vector<char> >& image) {
  vector<vector<char> > image_copy(image);

  size_t image_y_size = image_copy.size();
  if (image_y_size == 0) {
    return;
  }

  size_t image_x_size = image_copy.at(0).size();
  if (image_x_size == 0) {
    return;
  }

  char char_to_use = 'a';

  for (size_t y_point = 0; y_point < image_y_size; ++y_point) {
    for (size_t x_point = 0; x_point < image_x_size; ++x_point) {
      char current_char = image_copy.at(y_point).at(x_point);
      if (current_char == '@' || current_char == '#' || current_char == '%') {
        PaintCharTilWhiteSpace(image_copy, x_point, y_point, char_to_use++);
      }
    }
  }

  size_t image_x_center = image_x_size / 2;
  size_t image_y_center = image_y_size / 2;

  CharImageObjMap image_objects;
  for (size_t y_point = 0; y_point < image_y_size; ++y_point) {
    for (size_t x_point = 0; x_point < image_x_size; ++x_point) {
      char current_char = image_copy.at(y_point).at(x_point);
      if (current_char >= 'a' && current_char <= 'z') {
        ++image_objects[current_char].object_area;
        if (image_objects[current_char].object_area == 1) {
          image_objects[current_char].total_distance_from_center = 0.0;
        }
        image_objects[current_char].total_distance_from_center += 
          GetDistance(x_point, y_point, image_x_center, image_y_center);
      }
    }
  }

  CharImageObjMap::iterator object_iter;
  for (object_iter = image_objects.begin();
       object_iter != image_objects.end();
       ++object_iter) {
    object_iter->second.average_distance_from_center = 
      object_iter->second.total_distance_from_center / 
        object_iter->second.object_area;
  }

  if (image_objects.size() > 1) {
    double max_value;
    char char_of_digit_object = '.';

    for (object_iter = image_objects.begin();
         object_iter != image_objects.end();
         ++object_iter) {
      double object_value = object_iter->second.object_area - 
        object_iter->second.average_distance_from_center * 
          object_iter->second.average_distance_from_center;
      if (char_of_digit_object == '.') {
        char_of_digit_object = object_iter->first;
        max_value = object_value;
      } else if (object_value > max_value) {
        char_of_digit_object = object_iter->first;
        max_value = object_value;
      }
    }

    for (size_t y_point = 0; y_point < image_y_size; ++y_point) {
      for (size_t x_point = 0; x_point < image_x_size; ++x_point) {
        char current_char = image_copy.at(y_point).at(x_point);
        if (current_char != char_of_digit_object) {
          image.at(y_point).at(x_point) = '.';
        }
      }
    }
  }
}

void AnnihilateEmptyRows(vector<vector<char> >& image) {
  vector<vector<char> > image_copy(image);

  size_t image_y_size = image_copy.size();
  if (image_y_size == 0) {
    return;
  }

  size_t image_x_size = image_copy.at(0).size();
  if (image_x_size == 0) {
    return;
  }

  image.clear();

  size_t y_topmost = 0;
  size_t y_bottommost = image_y_size - 1;

  bool found_y_topmost = false;
  bool found_y_bottommost = false;

  while (!found_y_topmost) {
    for (size_t x_point = 0; x_point < image_x_size; ++x_point) {
      if (image_copy.at(y_topmost).at(x_point) != '.') {
        found_y_topmost = true;
        break;
      }
    }
    if (!found_y_topmost) {
      ++y_topmost;
    }
  }
  while (!found_y_bottommost) {
    for (size_t x_point = 0; x_point < image_x_size; ++x_point) {
      if (image_copy.at(y_bottommost).at(x_point) != '.') {
        found_y_bottommost = true;
        break;
      }
    }
    if (!found_y_bottommost) {
      --y_bottommost;
    }
  }

  for (size_t y_point = y_topmost; y_point <= y_bottommost; ++y_point) {
    image.push_back(image_copy.at(y_point));
  }
}

void AnnihilateEmptyColumns(vector<vector<char> >& image) {
  vector<vector<char> > image_copy(image);

  size_t image_y_size = image_copy.size();
  if (image_y_size == 0) {
    return;
  }

  size_t image_x_size = image_copy.at(0).size();
  if (image_x_size == 0) {
    return;
  }

  image.clear();

  size_t x_leftmost = 0;
  size_t x_rightmost = image_x_size - 1;
  bool found_x_leftmost = false;
  bool found_x_rightmost = false;

  while (!found_x_leftmost) {
    for (size_t y_index = 0; y_index < image_y_size; ++y_index) {
      if (image_copy.at(y_index).at(x_leftmost) != '.') {
        found_x_leftmost = true;
        break;
      }
    }
    if (!found_x_leftmost) {
      ++x_leftmost;
    }
  }
  while (!found_x_rightmost) {
    for (size_t y_index = 0; y_index < image_y_size; ++y_index) {
      if (image_copy.at(y_index).at(x_rightmost) != '.') {
        found_x_rightmost = true;
        break;
      }
    }
    if (!found_x_rightmost) {
      --x_rightmost;
    }
  }

  if (x_leftmost > 0) {
    --x_leftmost;
  }
  if (x_rightmost < image_x_size - 2) {
    ++x_rightmost;
  }

  vector<char> temp_line;
  for (size_t y_index = 0; y_index < image_y_size; ++y_index) {
    for (size_t x_index = x_leftmost; x_index <= x_rightmost; ++x_index) {
      temp_line.push_back(image_copy.at(y_index).at(x_index));
    }
    image.push_back(temp_line);
    temp_line.clear();
  }
}

void CalculateWeights(vector<vector<char> >& image, 
                      vector<size_t>* weights,
                      double incline_tangent = 0.0) {
  size_t image_y_size = image.size();
  size_t image_x_size = image.at(0).size();

  for (size_t x_point = 0; x_point < image_x_size; ++x_point) {
    for (size_t y_point = 0; y_point < image_y_size; ++y_point) {
      char curr_char = image.at(y_point).at(x_point);
      size_t inc_value = 0;

      if (curr_char == '@') {
        inc_value = 10;
      } else if (curr_char == '#') {
        inc_value = 2;
      } else if (curr_char == '%') {
        inc_value = 1;
      }

      size_t weight_index = x_point + 
        static_cast<size_t>(y_point * incline_tangent);
      weights->at(weight_index) += inc_value;
    }
  }
}

void CalculateWeightMins(vector<size_t>& weights, 
                         vector<WeightMin>* mins, 
                         double incline_tangent = 0.0) {
  size_t array_size = weights.size();

  int weight_average = 0;
  for (size_t weight_index = 0; weight_index < array_size; ++weight_index) {
    weight_average += weights.at(weight_index);
  }

  if (array_size) {
    weight_average /= array_size;
  }

  size_t mins_count = 0;

  size_t min_value = UINT_MAX;
  int min_position = -1;

  for (size_t weight_index = 0; weight_index < array_size; ++weight_index) {
    size_t current_value = weights.at(weight_index);
    if (current_value < min_value && 
        current_value < (2 * weight_average) / 10) {
      min_value = current_value;
      min_position = weight_index;
    }
    if (min_position >= 0 && min_position < array_size && 
        min_position + array_size / (2 * max_digit_count) <= weight_index) {
      if (mins_count++) {
        WeightMin new_min;
        new_min.min_position = min_position;
        new_min.incline_tangent = incline_tangent;
        mins->push_back(new_min);
      }

      min_value = UINT_MAX;
      min_position = -1;
    }
  }
}

void SplitDigits(vector<vector<char> >& image, 
                 vector<WeightMin>& splitters, 
                 vector<vector<vector<char> > >* digits_array)
{
  size_t image_y_size = image.size();
  size_t image_x_size = image.at(0).size();
  int x_left_bound = 0;
  int x_right_bound = 0;

  WeightMin fiction_min;
  fiction_min.min_position = image_x_size - 1;
  if (!splitters.empty()) {
    fiction_min.incline_tangent = splitters.back().incline_tangent;
    fiction_min.min_position += 
      static_cast<size_t>(image_y_size * fiction_min.incline_tangent);
  } else {
    fiction_min.incline_tangent = 0.0;
  }
  splitters.push_back(fiction_min);

  vector<vector<char> > digit_image;
  for (size_t digit_index = 0; 
       digit_index < splitters.size(); 
       ++digit_index) {
    x_right_bound = splitters.at(digit_index).min_position;

    vector<char> temp_line;
    for (size_t y_index = 0; y_index < image_y_size; ++y_index) {
      bool line_contains_nondot = false;

      int x_shift = static_cast<int>(
        y_index * splitters.at(digit_index).incline_tangent);

      for (int x_index = x_left_bound - x_shift; 
           x_index <= x_right_bound - x_shift;
           ++x_index) {
        char curr_char;
        if (x_index >= 0 && x_index < image_x_size) {
          curr_char = image.at(y_index).at(x_index);
        } else {
          curr_char = '.';
        }
        temp_line.push_back(curr_char);
        if (curr_char != '.') {
          line_contains_nondot = true;
        }
      }
      if (line_contains_nondot) {
        digit_image.push_back(temp_line);
      }
      temp_line.clear();
    }

    digits_array->push_back(digit_image);
    digit_image.clear();

    x_left_bound = splitters.at(digit_index).min_position;
  }

  //deleting auxilary fiction splitter
  splitters.pop_back();
}

int RecognizeDigit(const vector<vector<char> >& digit_image, 
                      const vector<vector<double> >& usual_digits_lines) {
  size_t image_y_size = digit_image.size();
  if (image_y_size == 0) {
    return -1;
  }

  size_t image_x_size = digit_image.at(0).size();
  if (image_x_size == 0) {
    return -1;
  }

  size_t diagonal_size = GetDistance(0, 0, image_x_size, image_y_size / 2);
  vector<vector<bool> > digit_circuit_lines;
  vector<bool> current_line(image_x_size, false);

  digit_circuit_lines.push_back(current_line);	//0
  digit_circuit_lines.push_back(current_line);	//1
  digit_circuit_lines.push_back(current_line);	//2
  current_line.resize(image_y_size / 2);
  digit_circuit_lines.push_back(current_line);	//3
  digit_circuit_lines.push_back(current_line);	//4
  current_line.resize(image_y_size - image_y_size / 2);
  digit_circuit_lines.push_back(current_line);	//5
  digit_circuit_lines.push_back(current_line);	//6
  current_line.resize(diagonal_size + 1);
  digit_circuit_lines.push_back(current_line);	//7
  digit_circuit_lines.push_back(current_line);	//8

  for (size_t y_index = 0; y_index < image_y_size; ++y_index) {
    for (size_t x_index = 0; x_index < image_x_size; ++x_index) {
      if (digit_image.at(y_index).at(x_index) != '.') {
        LineIndexNLinePoint projection = GetNearestLineIndex(
              x_index, y_index, image_x_size, image_y_size);
        digit_circuit_lines.at(projection.line_index).at(
          projection.line_point) = true;
      }
    }
  }

  return RecognizeProjection(digit_circuit_lines, usual_digits_lines);
}

void ReadInputImage(vector<vector<char> >* image) {
    //reading input
    vector<char> row_buffer;
    bool row_contains_nondot = false;

    while(!cin.eof()) {
      char current_char;
      cin.get(current_char);

      if (current_char == '\n' && !row_buffer.empty()) {
        if (row_contains_nondot) {
          image->push_back(row_buffer);
        }
        row_buffer.clear();
        row_contains_nondot = false;
      } else if (current_char == '.' || current_char == '@' || 
                 current_char == '#' || current_char == '%') {
        if (current_char != '.') {
          row_contains_nondot = true;
        }
        row_buffer.push_back(current_char);
      }
    }
    //pushing back last row
    if (!row_buffer.empty()) {
      image->push_back(row_buffer);
    }
}

int main() {
  vector<vector<char> > image;

  ReadInputImage(&image);
  AnnihilateEmptyColumns(image);

  size_t image_x_size = image.at(0).size();
  size_t image_incline_x_size = image.at(0).size() + 
    static_cast<size_t>(image.size() * italics_incline_tangent);

  vector<size_t> straight_column_weights(image_x_size, 0);
  vector<size_t> incline_column_weights(image_incline_x_size, 0);
  vector<WeightMin> straight_weight_mins;
  vector<WeightMin> incline_weight_mins;
  CalculateWeights(image, &straight_column_weights);
  CalculateWeights(image, &incline_column_weights, italics_incline_tangent);
  CalculateWeightMins(straight_column_weights, &straight_weight_mins);
  CalculateWeightMins(incline_column_weights, 
                      &incline_weight_mins, italics_incline_tangent);

  //finding out what splitters to use
  size_t straight_columns_average = 0;
  size_t incline_columns_average = 0;

  for (size_t min_index = 0; 
       min_index < straight_weight_mins.size();
       ++min_index) {
    straight_columns_average += 
      straight_column_weights.at(straight_weight_mins.at(min_index).min_position);
  }
  if (!straight_weight_mins.empty()) {
    straight_columns_average /= straight_weight_mins.size();
  } else {
    straight_columns_average = UINT_MAX;
  }

  for (size_t min_index = 0; 
       min_index < incline_weight_mins.size();
       ++min_index) {
    incline_columns_average += 
      incline_column_weights.at(incline_weight_mins.at(min_index).min_position);
  }
  if (!incline_weight_mins.empty()) {
    incline_columns_average /= incline_weight_mins.size();
  } else {
    incline_columns_average = UINT_MAX;
  }

  vector<vector<vector<char> > > digits;
  if (straight_columns_average <= incline_columns_average) {
    SplitDigits(image, straight_weight_mins, &digits);
  } else {
    SplitDigits(image, incline_weight_mins, &digits);
  }

  vector<vector<double> > usual_digits_lines;
  InitializeUsualDigitLines(&usual_digits_lines);

  for (size_t digit_index = 0; digit_index < digits.size(); ++digit_index) {
    AnnihilateEmptyColumns(digits.at(digit_index));
    AnnihilateNonDigits(digits.at(digit_index));
    AnnihilateEmptyColumns(digits.at(digit_index));
    AnnihilateEmptyRows(digits.at(digit_index));
    int recognized_digit = RecognizeDigit(digits.at(digit_index), usual_digits_lines);
    if (recognized_digit != -1) {
      cout << recognized_digit;
    }
  }

  return 0;
}
