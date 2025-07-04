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
  usual_digits_lines->resize(150);
  double zero_1[projection_lines_count] = 
    {0.6957, 0.6087, 0.6087, 0.5833, 0.6667, 0.6154, 0.6923, 0.6538, 0.5385};
  vector<double> zero_digit(zero_1, zero_1 + projection_lines_count);
  usual_digits_lines->at(0) = zero_digit;        //0 (1 of 1)

  double zero_2[projection_lines_count] = 
    {0.5789, 0.5263, 0.5263, 0.6667, 0.5833, 0.5833, 0.5833, 0.5652, 0.6087};
  zero_digit.assign(zero_2, zero_2 + projection_lines_count);
  usual_digits_lines->at(10) = zero_digit;        //0 (2 of 1)

  double zero_3[projection_lines_count] = 
    {0.5806, 0.8710, 0.6129, 0.6250, 0.7083, 0.6800, 0.7600, 0.7750, 0.7500};
  zero_digit.assign(zero_3, zero_3 + projection_lines_count);
  usual_digits_lines->at(20) = zero_digit;        //0 (2 of 1)

  double unity_1[projection_lines_count] = 
    {0.5500, 0.3000, 0.7000, 0.0714, 0.0000, 0.0000, 0.0667, 0.3200, 0.5200};
  vector<double> unity_digit(unity_1, 
                             unity_1 + projection_lines_count);
  usual_digits_lines->at(1) = unity_digit;      //1 (1 of 3)

  double unity_2[projection_lines_count] = 
    {0.5000, 0.5000, 0.8000, 0.2500, 0.5000, 0.2175, 0.5625, 0.5789, 0.5789};
  unity_digit.assign(unity_2, unity_2 + projection_lines_count);
  usual_digits_lines->at(11) = unity_digit;      //1 (2 of 3)

  double unity_3[projection_lines_count] = 
    {0.5556, 0.4444, 0.6667, 0.1250, 0.2500, 0.0000, 0.3750, 0.4615, 0.4615};
  unity_digit.assign(unity_3, unity_3 + projection_lines_count);
  usual_digits_lines->at(21) = unity_digit;      //1 (3 of 3)

  double unity_4[projection_lines_count] = 
    {0.4000, 0.3000, 0.3000, 0.4348, 0.9130, 0.0870, 0.9130, 0.7097, 0.4194};
  unity_digit.assign(unity_4, unity_4 + projection_lines_count);
  usual_digits_lines->at(31) = unity_digit;      //1 (4 of 3)

  double unity_5[projection_lines_count] = 
    {0.5714, 0.5714, 0.5714, 0.4444, 0.7778, 0.4444, 0.7778, 0.5833, 0.5833};
  unity_digit.assign(unity_5, unity_5 + projection_lines_count);
  usual_digits_lines->at(41) = unity_digit;      //1 (5 of 3)

  double unity_6[projection_lines_count] = 
    {0.4706, 0.4118, 0.7647, 0.3333, 0.0, 0.3333, 0.3333, 0.5500, 0.5500};
  unity_digit.assign(unity_6, unity_6 + projection_lines_count);
  usual_digits_lines->at(51) = unity_digit;      //1 (6 of 3)

  double two_1[projection_lines_count] = 
    {0.6579, 0.7105, 0.9211, 0.3913, 0.6957, 0.6087, 0.4348, 0.7111, 0.7778};
  vector<double> two_digit(two_1, two_1 + projection_lines_count);
  usual_digits_lines->at(2) = two_digit;      //2 (1 of 7)

  double two_2[projection_lines_count] = 
    {0.5833, 0.5000, 0.8750, 0.4091, 0.7273, 0.2273, 0.1818, 0.2727, 0.7273};
  two_digit.assign(two_2, two_2 + projection_lines_count);
  usual_digits_lines->at(12) = two_digit;      //2 (2 of 7)

  double two_3[projection_lines_count] = 
    {0.5882, 0.4118, 0.8235, 0.5000, 0.6667, 0.0833, 0.5833, 0.3810, 0.4286};
  two_digit.assign(two_3, two_3 + projection_lines_count);
  usual_digits_lines->at(22) = two_digit;      //2 (3 of 7)

  double two_4[projection_lines_count] = 
    {0.4500, 0.6000, 0.8000, 0.2000, 0.4000, 0.0000, 0.5455, 0.5652, 0.6957};
  two_digit.assign(two_4, two_4 + projection_lines_count);
  usual_digits_lines->at(32) = two_digit;      //2 (4 of 7)

  double two_5[projection_lines_count] = 
    {0.6667, 0.6111, 0.8333, 0.4286, 0.5714, 0.2143, 0.1429, 0.4348, 0.6087};
  two_digit.assign(two_5, two_5 + projection_lines_count);
  usual_digits_lines->at(42) = two_digit;      //2 (5 of 7)

  double two_6[projection_lines_count] = 
    {0.4167, 0.3333, 0.5278, 0.1176, 0.0000, 0.5294, 0.4118, 0.4750, 0.6000};
  two_digit.assign(two_6, two_6 + projection_lines_count);
  usual_digits_lines->at(52) = two_digit;      //2 (6 of 7)

  double two_7[projection_lines_count] = 
    {0.2703, 0.5405, 0.5135, 0.0000, 0.1176, 0.4118, 0.3529, 0.5854, 0.6098};
  two_digit.assign(two_7, two_7 + projection_lines_count);
  usual_digits_lines->at(62) = two_digit;      //2 (7 of 7)

  double two_8[projection_lines_count] = 
    {0.6000, 0.4667, 0.7333, 0.3750, 0.5000, 0.0000, 0.3333, 0.3889, 0.5000};
  two_digit.assign(two_8, two_8 + projection_lines_count);
  usual_digits_lines->at(72) = two_digit;      //2 (7 of 7)

  double three_1[projection_lines_count] = 
    {0.6316, 0.6842, 0.4737, 0.2727, 0.5455, 0.3333, 0.6667, 0.5000, 0.5909};
  vector<double> three_digit(three_1, three_1 + projection_lines_count);
  usual_digits_lines->at(3) = three_digit;      //3 (1 of 3)

  double three_2[projection_lines_count] = 
    {0.5833, 0.5000, 0.6250, 0.3636, 0.6364, 0.3043, 0.7826, 0.1818, 0.3333};
  three_digit.assign(three_2, three_2 + projection_lines_count);
  usual_digits_lines->at(13) = three_digit;      //3 (2 of 3)

  double three_3[projection_lines_count] = 
    {0.5455, 0.7273, 0.6364, 0.3750, 0.5000, 0.1250, 0.6250, 0.2143, 0.2857};
  three_digit.assign(three_3, three_3 + projection_lines_count);
  usual_digits_lines->at(23) = three_digit;      //3 (3 of 3)

  double three_4[projection_lines_count] = 
    {0.6667, 0.6667, 0.6667, 0.3333, 0.5333, 0.1875, 0.7500, 0.2692, 0.5769};
  three_digit.assign(three_4, three_4 + projection_lines_count);
  usual_digits_lines->at(33) = three_digit;      //3 (4 of 3)

  double three_5[projection_lines_count] = 
    {0.5455, 0.5455, 0.7273, 0.1250, 0.5000, 0.2500, 0.6875, 0.3214, 0.5714};
  three_digit.assign(three_5, three_5 + projection_lines_count);
  usual_digits_lines->at(43) = three_digit;      //3 (4 of 3)

  double three_6[projection_lines_count] = 
    {0.6250, 0.5000, 0.6875, 0.5455, 0.5455, 0.4167, 0.6667, 0.3500, 0.5000};
  three_digit.assign(three_6, three_6 + projection_lines_count);
  usual_digits_lines->at(53) = three_digit;      //3 (4 of 3)

  double four_1[projection_lines_count] = 
    {0.3750, 0.6563, 0.4688, 0.0000, 0.0000, 0.2778, 0.2778, 0.5676, 0.6216};
  vector<double> four_digit(four_1, four_1 + projection_lines_count);
  usual_digits_lines->at(4) = four_digit;     //4 (1 of 5)

  double four_2[projection_lines_count] = 
    {0.1667, 0.3889, 0.5000, 0.0000, 0.0833, 0.2500, 0.1667, 0.3636, 0.4545};
  four_digit.assign(four_2, four_2 + projection_lines_count);
  usual_digits_lines->at(14) = four_digit;     //4 (2 of 5)

  double four_3[projection_lines_count] = 
    {0.2581, 0.9032, 0.2903, 0.0000, 0.0000, 0.3889, 0.3333, 0.6389, 0.6667};
  four_digit.assign(four_3, four_3 + projection_lines_count);
  usual_digits_lines->at(24) = four_digit;     //4 (3 of 5)

  double four_4[projection_lines_count] = 
    {0.3750, 0.8750, 0.1250, 0.0000, 0.0000, 0.1667, 0.0000, 0.4762, 0.2857};
  four_digit.assign(four_4, four_4 + projection_lines_count);
  usual_digits_lines->at(34) = four_digit;     //4 (4 of 5)

  double four_5[projection_lines_count] = 
    {0.2857, 0.7143, 0.4762, 0.0000, 0.3000, 0.5455, 0.5455, 0.6250, 0.7083};
  four_digit.assign(four_5, four_5 + projection_lines_count);
  usual_digits_lines->at(44) = four_digit;     //4 (5 of 5)

  double four_6[projection_lines_count] = 
    {0.2941, 0.5882, 0.2353, 0.0000, 0.3000, 0.2727, 0.3636, 0.4500, 0.4500};
  four_digit.assign(four_6, four_6 + projection_lines_count);
  usual_digits_lines->at(54) = four_digit;     //4 (6 of 5)

  double four_7[projection_lines_count] = 
    {0.2857, 0.5714, 0.2000, 0.0000, 0.1364, 0.3913, 0.4348, 0.5714, 0.5952};
  four_digit.assign(four_7, four_7 + projection_lines_count);
  usual_digits_lines->at(64) = four_digit;     //4 (7 of 5)

  double four_8[projection_lines_count] = 
    {0.3500, 0.5500, 0.6500, 0.0000, 0.1538, 0.3077, 0.3846, 0.5833, 0.5417};
  four_digit.assign(four_8, four_8 + projection_lines_count);
  usual_digits_lines->at(74) = four_digit;     //4 (8 of 5)

  double four_9[projection_lines_count] = 
    {0.6190, 0.8095, 0.4286, 0.1333, 0.4667, 0.6667, 0.6667, 0.7692, 0.6538};
  four_digit.assign(four_9, four_9 + projection_lines_count);
  usual_digits_lines->at(84) = four_digit;     //4 (8 of 5)

  double five_1[projection_lines_count] = 
    {0.7949, 0.8974, 0.6667, 0.4348, 0.3043, 0.2609, 0.6957, 0.8478, 0.8043};
  vector<double> five_digit(five_1, five_1 + projection_lines_count);
  usual_digits_lines->at(5) = five_digit;     //5 (1 of 8)

  double five_2[projection_lines_count] = 
    {0.7333, 0.5333, 0.5333, 0.5000, 0.1000, 0.3000, 0.7000, 0.4737, 0.2105};
  five_digit.assign(five_2, five_2 + projection_lines_count);
  usual_digits_lines->at(15) = five_digit;     //5 (2 of 8)

  double five_3[projection_lines_count] = 
    {0.8077, 0.5769, 0.6923, 0.6667, 0.2857, 0.0000, 0.7273, 0.7059, 0.3824};
  five_digit.assign(five_3, five_3 + projection_lines_count);
  usual_digits_lines->at(25) = five_digit;     //5 (3 of 8)

  double five_4[projection_lines_count] = 
    {0.3684, 0.7895, 0.4737, 0.0000, 0.0000, 0.3077, 0.6923, 0.6957, 0.5652};
  five_digit.assign(five_4, five_4 + projection_lines_count);
  usual_digits_lines->at(35) = five_digit;     //5 (4 of 8)

  double five_5[projection_lines_count] = 
    {0.7619, 0.6190, 0.6667, 0.2500, 0.5000, 0.7500, 0.6667, 0.5600, 0.5600};
  five_digit.assign(five_5, five_5 + projection_lines_count);
  usual_digits_lines->at(45) = five_digit;     //5 (5 of 8)

  double five_6[projection_lines_count] = 
    {0.6585, 0.7073, 0.6585, 0.1481, 0.2222, 0.3571, 0.6786, 0.5400, 0.7400};
  five_digit.assign(five_6, five_6 + projection_lines_count);
  usual_digits_lines->at(55) = five_digit;     //5 (6 of 8)

  double five_7[projection_lines_count] = 
    {0.6429, 0.6786, 0.7143, 0.0000, 0.0000, 0.2500, 0.7500, 0.6176, 0.4706};
  five_digit.assign(five_7, five_7 + projection_lines_count);
  usual_digits_lines->at(65) = five_digit;     //5 (7 of 8)

  double five_8[projection_lines_count] = 
    {0.8421, 0.6316, 0.4211, 0.7222, 0.6111, 0.0556, 0.0000, 0.7407, 0.7037};
  five_digit.assign(five_8, five_8 + projection_lines_count);
  usual_digits_lines->at(75) = five_digit;     //5 (8 of 8)

  double five_9[projection_lines_count] = 
    {0.6429, 0.6429, 0.6429, 0.3000, 0.4000, 0.1818, 0.7273, 0.6667, 0.5000};
  five_digit.assign(five_9, five_9 + projection_lines_count);
  usual_digits_lines->at(85) = five_digit;     //5 (9 of 8)

  double five_10[projection_lines_count] = 
    {0.7586, 0.9310, 0.6207, 0.6000, 0.0500, 0.3500, 0.7000, 0.6944, 0.5556};
  five_digit.assign(five_10, five_10 + projection_lines_count);
  usual_digits_lines->at(95) = five_digit;     //5 (10 of 8)

  double five_11[projection_lines_count] = 
    {0.7333, 0.8000, 0.6667, 0.4444, 0.0000, 0.4444, 0.6666, 0.6666, 0.6666};
  five_digit.assign(five_11, five_11 + projection_lines_count);
  usual_digits_lines->at(105) = five_digit;     //5 (11 of 8)

  double five_12[projection_lines_count] = 
    {0.7368, 0.7895, 0.6842, 0.3333, 0.0000, 0.1538, 0.6923, 0.2174, 0.5217};
  five_digit.assign(five_12, five_12 + projection_lines_count);
  usual_digits_lines->at(115) = five_digit;     //5 (12 of 8)

  double five_13[projection_lines_count] = 
    {0.8889, 0.8889, 0.6111, 0.8000, 0.0000, 0.4667, 0.8000, 0.3750, 0.3333};
  five_digit.assign(five_13, five_13 + projection_lines_count);
  usual_digits_lines->at(125) = five_digit;     //5 (13 of 8)

  double six_1[projection_lines_count] = 
    {0.7333, 0.8667, 0.3333, 0.4444, 0.0000, 0.5000, 0.8000, 0.1111, 0.4444};
  vector<double> six_digit(six_1, six_1 + projection_lines_count);
  usual_digits_lines->at(6) = six_digit;      //6 (1 of 5)

  double six_2[projection_lines_count] = 
    {0.6667, 0.8750, 0.5833, 0.5833, 0.0000, 0.5385, 0.6154, 0.6296, 0.5926};
  six_digit.assign(six_2, six_2 + projection_lines_count);
  usual_digits_lines->at(16) = six_digit;      //6 (2 of 5)

  double six_3[projection_lines_count] = 
    {0.3333, 0.8519, 0.5926, 0.0000, 0.0000, 0.6111, 0.6667, 0.5625, 0.6563};
  six_digit.assign(six_3, six_3 + projection_lines_count);
  usual_digits_lines->at(26) = six_digit;      //6 (3 of 5)

  double six_4[projection_lines_count] = 
    {0.5200, 0.9200, 0.6400, 0.5833, 0.3333, 0.6154, 0.6923, 0.5000, 0.8214};
  six_digit.assign(six_4, six_4 + projection_lines_count);
  usual_digits_lines->at(36) = six_digit;      //6 (4 of 5)

  double six_5[projection_lines_count] = 
    {0.6154, 0.8462, 0.5385, 0.0000, 0.0000, 0.5000, 0.6250, 0.4375, 0.5000};
  six_digit.assign(six_5, six_5 + projection_lines_count);
  usual_digits_lines->at(46) = six_digit;      //6 (5 of 5)

  double six_6[projection_lines_count] = 
    {0.6818, 0.8636, 0.5909, 0.6250, 0.3750, 0.6250, 0.6875, 0.5714, 0.4286};
  six_digit.assign(six_6, six_6 + projection_lines_count);
  usual_digits_lines->at(56) = six_digit;      //6 (6 of 5)

  double six_7[projection_lines_count] = 
    {0.7391, 0.9130, 0.6522, 0.6471, 0.0588, 0.6111, 0.7222, 0.5172, 0.4828};
  six_digit.assign(six_7, six_7 + projection_lines_count);
  usual_digits_lines->at(66) = six_digit;      //6 (7 of 5)

  double seven_1[projection_lines_count] = 
    {0.8750, 0.3750, 0.1875, 0.2727, 0.5455, 0.0000, 0.0000, 0.2500, 0.3500};
  vector<double> seven_digit(seven_1, seven_1 + projection_lines_count);
  usual_digits_lines->at(7) = seven_digit;      //7 (1 of 5)

  double seven_2[projection_lines_count] = 
    {0.9167, 0.3750, 0.1667, 0.1905, 0.6667, 0.0000, 0.0000, 0.4688, 0.3750};
  seven_digit.assign(seven_2, seven_2 + projection_lines_count);
  usual_digits_lines->at(17) = seven_digit;      //7 (2 of 5)

  double seven_3[projection_lines_count] = 
    {0.6667, 0.2667, 0.1333, 0.4000, 0.6000, 0.0000, 0.0000, 0.2632, 0.2105};
  seven_digit.assign(seven_3, seven_3 + projection_lines_count);
  usual_digits_lines->at(27) = seven_digit;      //7 (3 of 5)

  double seven_4[projection_lines_count] = 
    {0.8571, 0.4286, 0.4286, 0.5625, 0.6875, 0.3750, 0.0000, 0.2273, 0.5909};
  seven_digit.assign(seven_4, seven_4 + projection_lines_count);
  usual_digits_lines->at(37) = seven_digit;      //7 (4 of 5)

  double seven_5[projection_lines_count] = 
    {0.8889, 0.6111, 0.3889, 0.5000, 0.6000, 0.0909, 0.0000, 0.6190, 0.5238};
  seven_digit.assign(seven_5, seven_5 + projection_lines_count);
  usual_digits_lines->at(47) = seven_digit;      //7 (5 of 5)

  double eight_1[projection_lines_count] = 
    {0.2813, 0.7188, 0.6563, 0.2609, 0.3478, 0.5652, 0.6087, 0.6500, 0.5000};
  vector<double> eight_digit(eight_1, eight_1 + projection_lines_count);
  usual_digits_lines->at(8) = eight_digit;      //8 (1 of 7)

  double eight_2[projection_lines_count] = 
    {0.6316, 0.6316, 0.4737, 0.4545, 0.6364, 0.4167, 0.6667, 0.3636, 0.6364};
  eight_digit.assign(eight_2, eight_2 + projection_lines_count);
  usual_digits_lines->at(18) = eight_digit;      //8 (2 of 7)

  double eight_3[projection_lines_count] = 
    {0.5926, 0.7407, 0.6296, 0.4118, 0.5294, 0.5000, 0.5556, 0.7188, 0.6875};
  eight_digit.assign(eight_3, eight_3 + projection_lines_count);
  usual_digits_lines->at(28) = eight_digit;      //8 (3 of 7)

  double eight_4[projection_lines_count] = 
    {0.4667, 0.8667, 0.6000, 0.2000, 0.6000, 0.6364, 0.7273, 0.5789, 0.6316};
  eight_digit.assign(eight_4, eight_4 + projection_lines_count);
  usual_digits_lines->at(38) = eight_digit;      //8 (4 of 7)

  double eight_5[projection_lines_count] = 
    {0.6471, 0.7647, 0.7353, 0.4211, 0.4737, 0.5500, 0.7000, 0.5385, 0.7692};
  eight_digit.assign(eight_5, eight_5 + projection_lines_count);
  usual_digits_lines->at(48) = eight_digit;      //8 (5 of 7)

  double eight_6[projection_lines_count] = 
    {0.5556, 0.7222, 0.6667, 0.5000, 0.5714, 0.6000, 0.7333, 0.5652, 0.4348};
  eight_digit.assign(eight_6, eight_6 + projection_lines_count);
  usual_digits_lines->at(58) = eight_digit;      //8 (6 of 7)

  double eight_7[projection_lines_count] = 
    {0.8000, 0.4800, 0.5200, 0.3333, 0.4667, 0.0000, 0.3333, 0.6667, 0.5667};
  eight_digit.assign(eight_7, eight_7 + projection_lines_count);
  usual_digits_lines->at(68) = eight_digit;      //8 (7 of 7)

  double eight_8[projection_lines_count] = 
    {0.6471, 0.7647, 0.5882, 0.3000, 0.5000, 0.5000, 0.6000, 0.5000, 0.5000};
  eight_digit.assign(eight_8, eight_8 + projection_lines_count);
  usual_digits_lines->at(78) = eight_digit;      //8 (8 of 7)

  double eight_9[projection_lines_count] = 
    {0.6667, 0.6667, 0.6667, 0.3636, 0.5455, 0.5000, 0.7500, 0.4091, 0.6364};
  eight_digit.assign(eight_9, eight_9 + projection_lines_count);
  usual_digits_lines->at(88) = eight_digit;      //8 (9 of 7)

  double eight_10[projection_lines_count] = 
    {0.6364, 0.5455, 0.5455, 0.5000, 0.5000, 0.5556, 0.6667, 0.3571, 0.5714};
  eight_digit.assign(eight_10, eight_10 + projection_lines_count);
  usual_digits_lines->at(98) = eight_digit;      //8 (10 of 7)

  double eight_11[projection_lines_count] = 
    {0.7000, 0.9000, 0.7000, 0.6667, 0.6000, 0.7333, 0.7333, 0.7692, 0.8077};
  eight_digit.assign(eight_11, eight_11 + projection_lines_count);
  usual_digits_lines->at(108) = eight_digit;      //8 (10 of 7)

  double nine_1[projection_lines_count] = 
    {0.7059, 0.8235, 0.6471, 0.6364, 0.7273, 0.2500, 0.7500, 0.3333, 0.6667};
  vector<double> nine_digit(nine_1, nine_1 + projection_lines_count);
  usual_digits_lines->at(9) = nine_digit;     //9 (1 of 5)

  double nine_2[projection_lines_count] = 
    {0.5882, 0.8235, 0.6471, 0.5833, 0.7500, 0.4167, 0.6667, 0.2857, 0.3810};
  nine_digit.assign(nine_2, nine_2 + projection_lines_count);
  usual_digits_lines->at(19) = nine_digit;     //9 (2 of 5)

  double nine_3[projection_lines_count] = 
    {0.7500, 0.8750, 0.5000, 0.6923, 0.7692, 0.0000, 0.4286, 0.7500, 0.5714};
  nine_digit.assign(nine_3, nine_3 + projection_lines_count);
  usual_digits_lines->at(29) = nine_digit;     //9 (3 of 5)

  double nine_4[projection_lines_count] = 
    {0.5349, 0.8837, 0.2558, 0.5806, 0.7742, 0.0000, 0.8387, 0.8519, 0.4630};
  nine_digit.assign(nine_4, nine_4 + projection_lines_count);
  usual_digits_lines->at(39) = nine_digit;     //9 (4 of 5)

  double nine_5[projection_lines_count] = 
    {0.5263, 0.8421, 0.5789, 0.6429, 0.6429, 0.2000, 0.6667, 0.5833, 0.7083};
  nine_digit.assign(nine_5, nine_5 + projection_lines_count);
  usual_digits_lines->at(49) = nine_digit;     //9 (5 of 5)

  double nine_6[projection_lines_count] = 
    {0.6250, 0.7917, 0.2917, 0.5789, 0.7368, 0.0000, 0.0000, 0.4839, 0.5806};
  nine_digit.assign(nine_6, nine_6 + projection_lines_count);
  usual_digits_lines->at(59) = nine_digit;     //9 (6 of 5)
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
