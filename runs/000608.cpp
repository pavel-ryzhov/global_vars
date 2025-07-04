
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <stdlib.h>

using std::vector;
using std::string;
using std::cin;
using std::auto_ptr;
//////////////////////////////////////////////////////////////////////////

const int KMaxLineNum = 100;
const int KMaxInt = 2147483647;
// связные области с меньшим числом точек - шум
const int KNoiseThreshold = 40;
const int KPatternClassCount = 10;

// веса, для инициализации нейронов
const double InitArray[] = {
  0.917051, 0.56437, 0.690157, 0.954056, 0.994989, 0.919672, 1.01787, 1.04493, 0.697248, 0.855187, 0.528182, 0.432308, 0.672318, 0.657436, 0.921059, 0.872237, 0.852607, 0.710423, 0.784907, 0.676733, 1.06255, 0.693514, 1.01128, 0.728145, 0.584575, 0.594221, 0.898672, 1.03421, 0.961062, 0.714585, 0.544058, 0.880291, 0.946958, 0.98083, 0.778403, 0.615643, 0.747137, 0.828088, 0.925037, 0.883041, 0.400738, 0.722966, 0.563818, 0.696871, 0.831181, 0.554284, 0.746858, 0.662749, 0.963047, 0.799757, 0.576129, 0.775231, 0.598004, 0.477567, 0.372792, 0.655782, 0.767915, 0.861936, 0.729597, 0.816143, 0.906225, 0.548163, 0.794787, 0.980644, 0.655061, 0.291281, 0.720202, 0.544262, 0.624463, 0.576506, 0.525862, 0.728449, 0.725676, 0.523199, 1.09185, 1.09353, 0.431949, 0.564488, 0.688819, 0.816455, 0.817084, 0.81749, 0.449084, 0.603256, 0.840403, 0.591823, 0.528886, 0.829996, 1.0387, 1.03549, 0.892773, 0.780404, 0.564517, 0.594031, 0.638489, 0.446284, 
  0.624646, 0.662467, 0.60898, 0.812814, 0.539668, 0.534213, 0.522534, 0.497434, 0.616956, 0.567449, 0.54802, 0.841585, 0.596177, 0.579636, 0.801915, 0.713493, 0.740997, 0.630194, 0.337448, 0.686236, 0.536711, 0.710386, 0.442018, 0.740043, 0.704231, 0.54388, 1.11282, 0.859445, 0.751914, 0.700248, 0.482334, 0.933519, 0.737082, 0.561654, 0.760982, 0.728836, 0.683996, 0.654396, 1.01011, 1.04128, 0.882778, 0.825567, 0.587651, 0.854449, 0.584277, 0.706431, 0.842288, 0.669995, 0.47931, 0.752155, 0.892596, 1.10434, 0.7026, 0.934216, 0.843998, 0.869428, 0.739869, 0.775535, 0.555861, 0.757011, 0.835077, 0.894408, 0.889821, 0.802038, 0.675634, 0.504886, 0.72128, 0.649364, 0.854074, 1.05998, 0.983518, 0.808581, 0.7018, 0.773635, 0.689919, 0.78354, 0.986993, 0.647225, 0.476206, 0.561628, 0.770698, 0.53646, 0.882417, 1.31565, 1.16667, 0.678871, 1.04864, 0.710423, 0.854239, 0.609788, 0.938616, 0.581071, 0.746342, 0.498215, 0.751796, 0.991388, 
  0.608772, 0.494603, 0.944545, 0.789059, 0.771205, 0.750583, 0.488991, 0.876713, 0.774948, 0.641798, 0.719879, 0.887942, 0.597492, 0.874871, 0.761895, 0.643683, 0.674734, 0.726701, 0.534184, 0.74607, 0.702433, 0.753997, 0.726967, 0.966926, 0.602923, 0.743467, 0.6287, 0.87039, 0.529354, 0.478257, 0.545267, 0.704848, 0.931255, 1.04694, 1.03938, 0.516018, 0.73788, 0.418986, 0.711359, 0.732289, 0.471632, 0.655943, 0.72892, 0.986505, 0.869459, 0.773203, 0.578926, 0.905314, 0.524068, 0.722222, 0.708843, 0.445883, 0.890137, 0.820907, 0.910754, 0.83562, 0.409305, 0.735159, 0.689589, 0.980748, 0.844399, 0.775193, 0.607133, 0.645075, 0.668396, 0.648428, 0.710293, 0.819083, 0.751215, 0.609547, 1.0631, 0.957547, 0.499131, 0.898304, 0.999572, 1.00467, 0.98654, 0.808274, 0.575095, 0.407489, 0.39663, 0.690827, 0.747573, 0.785608, 0.73385, 0.500347, 0.669175, 1.0624, 0.88656, 0.577064, 0.416223, 0.378046, 0.685286, 0.941608, 0.729474, 1.03139, 
  0.928539, 0.913916, 0.766972, 0.663822, 0.305224, 0.557101, 0.671545, 0.605793, 0.927463, 0.884087, 0.861951, 0.738351, 0.886942, 0.924808, 0.906272, 0.635443, 0.271881, 0.317008, 0.584877, 0.344104, 0.468354, 0.96797, 0.945129, 1.02141, 0.800832, 0.746859, 0.798484, 0.575521, 0.725464, 0.636252, 0.635999, 0.708844, 0.437376, 0.781152, 0.831669, 0.644388, 0.894629, 0.640501, 0.612892, 0.801864, 0.956675, 0.850047, 0.853469, 0.58128, 0.708965, 0.536773, 0.61451, 0.785767, 0.936264, 0.88603, 0.699446, 0.797958, 0.706729, 0.620257, 0.666139, 0.640926, 0.471115, 0.740573, 0.604203, 0.629938, 0.57686, 0.624533, 0.938089, 0.584132, 0.847494, 0.728961, 1.06578, 0.851548, 0.508147, 0.830702, 0.834232, 0.756021, 0.770138, 1.04154, 0.907303, 0.744039, 0.667361, 0.782798, 1.04858, 1.01194, 0.80258, 0.559859, 0.786541, 0.625124, 0.738255, 0.534869, 0.612273, 0.674102, 0.789062, 0.525444, 0.646162, 0.715949, 0.936644, 0.875345, 0.733059, 0.415789, 
  0.807403, 0.431765, 0.500506, 0.47384, 0.559833, 0.861891, 0.939288, 0.834421, 1.02204, 0.686822, 0.538567, 0.401037, 0.856819, 0.416997, 0.727119, 0.560848, 0.683522, 1.01813, 1.07192, 0.841132, 0.893278, 0.675926, 0.582566, 0.611502, 0.809284, 0.464361, 0.817577, 0.813109, 0.819247, 0.973276, 0.652784, 0.69297, 0.695779, 0.527188, 0.492324, 0.425085, 0.529072, 0.715348, 0.847284, 0.824983, 0.647753, 0.510242, 0.826119, 0.883662, 0.920919, 0.819348, 0.54772, 0.789524, 0.75092, 0.779769, 0.460522, 0.904114, 0.846597, 0.759142, 1.00573, 1.12376, 0.930031, 0.932349, 0.650248, 0.884005, 0.575557, 0.812531, 0.813513, 0.776424, 0.934968, 0.965465, 0.808239, 0.673033, 0.733518, 0.848161, 0.914932, 0.649491, 0.539343, 0.663761, 0.708626, 0.68078, 0.796863, 0.703162, 0.722966, 0.782179, 0.817604, 0.651204, 0.550688, 0.75178, 0.739352, 0.519956, 0.696265, 0.832336, 0.40237, 0.936051, 0.735743, 0.626722, 0.525769, 0.848237, 0.547011, 0.796088, 
  0.68409, 0.616016, 0.664592, 0.850659, 0.801072, 0.855328, 1.06063, 0.36096, 0.773429, 0.862823, 1.07367, 1.00464, 0.828229, 0.998038, 0.754566, 0.677575, 0.846785, 0.901215, 0.628915, 0.612811, 0.528562, 0.728107, 0.792997, 0.865174, 0.750132, 0.473323, 0.764297, 0.939714, 0.985977, 0.751275, 0.49207, 0.559977, 0.698712, 0.455328, 0.864879, 0.942494, 0.788853, 0.881597, 0.995151, 0.554111, 0.508178, 0.819506, 0.438221, 0.800445, 0.407532, 0.548313, 0.745947, 0.599183, 0.532451, 0.610651, 0.79822, 0.456166, 1.08826, 1.00025, 0.762993, 0.8521, 0.924497, 0.727044, 0.77645, 0.990486, 0.550339, 0.83189, 0.651215, 0.389921, 0.936468, 0.898665, 0.817164, 0.717663, 0.621081, 0.917488, 0.751783, 0.538586, 0.838014, 0.73663, 0.274496, 0.349097, 0.426072, 0.819184, 0.534459, 0.620952, 0.84034, 0.992453, 0.843688, 0.499554, 1.0883, 0.864246, 0.38569, 0.648251, 0.410853, 0.79003, 0.733341, 0.821525, 0.679848, 0.951819, 0.558257, 0.714956, 
  0.755396, 0.401633, 0.592077, 0.756889, 1.04071, 1.17498, 0.889346, 1.01151, 0.697511, 0.629947, 0.757056, 0.654542, 0.352162, 0.676619, 0.465045, 0.769573, 0.665762, 0.606481, 0.969597, 0.926184, 0.842947, 1.04653, 0.879238, 0.91027, 0.807745, 0.550731, 0.612134, 0.602048, 0.737154, 0.84654, 0.676789, 0.703915, 1.09809, 0.657585, 0.727092, 0.884297, 0.700455, 0.911443, 0.661792, 0.811315, 0.543952, 0.958181, 0.612303, 0.877114, 0.653961, 0.711974, 0.669678, 0.89307, 0.566748, 0.642209, 0.599962, 0.641506, 0.802208, 0.747951, 0.663818, 0.716865, 0.877098, 0.641474, 0.769366, 0.816891, 0.74143, 0.654717, 0.825366, 0.521066, 0.876031, 0.624165, 0.641574, 0.610442, 0.556727, 0.911209, 0.812345, 0.69482, 0.742022, 0.692902, 0.409048, 0.378488, 0.657213, 1.00448, 0.551682, 0.71287, 0.963083, 0.718195, 0.735671, 0.679016, 0.648747, 0.64012, 0.853345, 0.183745, 0.464269, 0.699592, 0.706025, 0.91436, 0.726315, 0.87233, 0.959635, 0.749488, 
  0.960327, 0.828171, 0.697481, 0.852671, 0.747824, 0.519523, 0.830951, 0.859878, 0.595866, 0.780028, 0.543024, 0.638727, 1.08213, 0.892016, 0.695933, 0.504323, 0.550588, 0.488877, 0.532941, 0.795918, 0.815971, 0.706627, 0.730627, 0.751087, 0.909764, 0.805453, 0.540239, 0.868506, 0.58906, 0.564542, 0.513, 0.907231, 0.65473, 0.760092, 0.703133, 0.453735, 1.06497, 0.669218, 0.540784, 0.4944, 0.609832, 0.707745, 0.79606, 0.918707, 0.830887, 0.664865, 0.671935, 0.94363, 0.644959, 0.675843, 0.76298, 0.482068, 0.836323, 0.715871, 0.792763, 0.842098, 0.918169, 0.753768, 0.593304, 0.847253, 0.719737, 1.03577, 1.00142, 0.885553, 0.829678, 0.520297, 0.689284, 0.561051, 0.957912, 0.651825, 0.861911, 0.800702, 0.708518, 1.08883, 0.817546, 0.697035, 0.906857, 0.831549, 0.383909, 0.397769, 0.781809, 0.71445, 0.764174, 0.490778, 1.26762, 0.961721, 0.667185, 0.533679, 0.770299, 0.583065, 0.542571, 0.505417, 0.427399, 0.649383, 0.455055, 0.738818, 
  0.641413, 0.746477, 0.5949, 0.750932, 0.706192, 0.33149, 0.539318, 0.944553, 1.08959, 1.15183, 1.08772, 0.648845, 0.638016, 0.92579, 0.921442, 0.742539, 0.822553, 0.745689, 0.884226, 1.02849, 0.889366, 0.654817, 0.715459, 0.521512, 0.811551, 0.661121, 0.872586, 0.852584, 0.885776, 0.885804, 0.639678, 0.905857, 0.523541, 0.431382, 0.8073, 0.800554, 0.789424, 0.81473, 0.836559, 0.666832, 0.710008, 0.955662, 0.689254, 0.605259, 0.709034, 0.726394, 0.747574, 0.783057, 0.79584, 0.628562, 0.503355, 0.601783, 0.740103, 0.868942, 1.04044, 0.673196, 0.775889, 0.787096, 0.517584, 0.552145, 0.607205, 0.812874, 0.549975, 0.61971, 0.802109, 0.624383, 0.903461, 0.528925, 0.870485, 0.830165, 0.531409, 0.616572, 0.721388, 0.690855, 0.564782, 0.94491, 0.620461, 0.587021, 0.595462, 0.564373, 0.829803, 0.707014, 0.626827, 1.03824, 0.561496, 0.884073, 0.766955, 1.01331, 0.602382, 0.546177, 0.625347, 0.835483, 0.915905, 0.82413, 0.776092, 0.790633, 
  0.822368, 0.940583, 0.889792, 0.89526, 0.983282, 0.99522, 0.689516, 0.3138, 0.704956, 0.740031, 0.441928, 0.602014, 0.639714, 0.603791, 0.744755, 0.830281, 0.890573, 0.855285, 0.770988, 0.642324, 0.659824, 0.562119, 0.523724, 0.68393, 0.86896, 0.716584, 0.654482, 0.734476, 0.514991, 0.599219, 0.768022, 0.702548, 0.626474, 0.847845, 0.794839, 0.78895, 0.713584, 0.515694, 0.359031, 0.73989, 0.818453, 0.744144, 0.904187, 0.845708, 0.933785, 0.708416, 0.734564, 0.76771, 1.0064, 0.8028, 0.847947, 0.74095, 0.839046, 0.554894, 0.740563, 0.640225, 0.686113, 0.445065, 0.713798, 0.775379, 0.793173, 0.609922, 0.828683, 0.595437, 0.624162, 0.79347, 0.57273, 0.644628, 0.822376, 0.614418, 0.870902, 0.64923, 0.503971, 0.640348, 0.786862, 0.923901, 0.969692, 0.701824, 0.672825, 0.92434, 0.58037, 0.762047, 0.763337, 0.410997, 0.415302, 0.723972, 0.871586, 1.01176, 0.78126, 0.997299, 0.813197, 0.791023, 0.541976, 0.544902, 0.851131, 0.875163
};

//////////////////////////////////////////////////////////////////////////

// меняет местами два инта
inline void swap(int& aValue1, int& aValue2)
{
  int temp = aValue1;
  aValue1 = aValue2;
  aValue2 = temp;
}

//////////////////////////////////////////////////////////////////////////

enum TAscii
{
  EDot = '.',
  EPercent = '%',
  EHash = '#',
  EAt = '@',
};

enum TColor
{
  EWhite = 0,
  ELightGrey = 1,
  EDarkGrey = 2,
  EBlack = 4,
};

typedef vector< vector<int> > TImage;

inline int ConvertToColor(int aAsciiCode)
{
  switch (aAsciiCode)
  {
  case EDot :
    return EWhite;
  case EPercent:
    return ELightGrey;
  case EHash:
    return EDarkGrey;
  case EAt:
    return EBlack;
  default :
    // std::cout << "Wrong ascii-code\n";
    return EWhite;
  }
}

//////////////////////////////////////////////////////////////////////////

struct TPoint
{
  TPoint(int aX, int aY) : iX(aX), iY(aY) {}

  int iX, iY;
};

class TArea
{
public:
  TArea() : iMinX(KMaxInt), iMinY(KMaxInt), iMaxX(0), iMaxY(0) {}
  ~TArea(){}

public:
  int PointCount() const { return (int)iPoints.size(); }

  const TPoint& Point(int aIndex) const { return iPoints[aIndex]; }

  int MinX() const { return iMinX; }

  int MaxX() const { return iMaxX; }

  int MinY() const { return iMinY; }

  int MaxY() const { return iMaxY; }

public:
  void AddPoint(const TPoint& aPoint)
  {
    iPoints.push_back(aPoint);
    AdjustBounds(aPoint.iX, aPoint.iY);
  }

  void AdjustBounds(int aX, int aY)
  {
    if (aX < iMinX)
      iMinX = aX;
    if (aX > iMaxX)
      iMaxX = aX;
    if (aY < iMinY)
      iMinY = aY;
    if (aY > iMaxY)
      iMaxY  = aY;
  }

private:
  int iMinX;
  int iMaxX;
  int iMinY;
  int iMaxY;
  vector<TPoint> iPoints;
};

//////////////////////////////////////////////////////////////////////////

typedef vector< TArea* > TAreaPtrArray;

//////////////////////////////////////////////////////////////////////////
// выделяет связные области

class AreaSelector
{
public:
  static void SelectFromImage(const TImage& aImage, TAreaPtrArray& aAreas)
  {
    std::auto_ptr<AreaSelector> self(new AreaSelector(aImage));
    self->DoSelect(aAreas);
  }

  ~AreaSelector() {}

private:
  AreaSelector(const TImage& aImage) : iImage(&aImage)
  {
    iWidth = (int)iImage->size();
    iHeight = 0;
    if (iWidth > 0)
      iHeight = (int)iImage->at(0).size();

    iVisited.assign(iWidth, vector<bool>(iHeight, false));
  }

private:
  void DoSelect(TAreaPtrArray& aAreas)
  {
    // calculate boundaries
    int leftBoundary = 0;
    int rightBoundary = leftBoundary;

    while (rightBoundary < iWidth)
    {
      leftBoundary = rightBoundary;
      while (IsDelimiter(leftBoundary))
        ++leftBoundary;
      rightBoundary = leftBoundary;
      while ((rightBoundary < iWidth) && !IsDelimiter(rightBoundary))
        ++rightBoundary;

      DoSelectBetween(aAreas, leftBoundary, rightBoundary);
    }
  }

  void DoSelectBetween(TAreaPtrArray& aAreas, int aLeft, int aRight)
  {
    iLeft = aLeft;
    iRight = aRight;
    for (int i = aLeft; i < aRight; ++i)
      for (int j = 0; j < iHeight; ++j)
      {
        if ((iImage->at(i)[j] == EBlack || iImage->at(i)[j] == EDarkGrey) && 
          !iVisited[i][j])
        {
          TArea* area = new TArea();
          BlowArea(*area, TPoint(i, j));
          aAreas.push_back(area);
        }
      }
  }

  bool ShouldGo(int aX , int aY) const
  {
    if (aX < iLeft || aX >= iRight)
      return false;
    if (aY < 0 || aY >= iHeight)
      return false;
    if ((iImage->at(aX)[aY] != EWhite) && !iVisited[aX][aY])
      return true;
    return false;
  }

  void BlowArea(TArea& aArea, const TPoint& aPoint)
  {
    int x = aPoint.iX;
    int y = aPoint.iY;
    iVisited[x][y] = true;
    aArea.AddPoint(aPoint);
    for (int i = -2; i <=2; ++i)
      for (int j = -2; j <=2; ++j)
      {
        if (ShouldGo(x + i, y + j))
        {
          BlowArea(aArea, TPoint(x + i, y + j));
        }
      }
  }

  // determines if vertical line aX is delimiter
  bool IsDelimiter(int aX)
  {
    if (aX < 0 || aX >= iWidth)
      return false;
    int height = iImage->at(aX).size();
    for (int i = 0; i < height; ++i)
    {
      if (iImage->at(aX)[i] == EBlack || iImage->at(aX)[i] == EDarkGrey)
        return false;
    }
    return true;
  }

private:
  int iLeft, iRight;
  int iWidth, iHeight;
  vector< vector<bool> > iVisited;
  const TImage* iImage; // not owned
};

//////////////////////////////////////////////////////////////////////////

class TDigitPattern
{
public:
  TDigitPattern() : iWeight(0.0)
  {
    iDarkenArray.assign(KPatternWidth, vector<double>(KPatternHeight, 0));
  }
  ~TDigitPattern(){}

  int Width() const
  {
    return KPatternWidth;
  }

  int Height() const
  {
    return KPatternHeight;
  }

  double At(int aX, int aY) const
  {
    return iDarkenArray[aX][aY];
  }

  double Weight() const
  {
    return iWeight;
  }

  void DarkenPoint(int aX, int aY, double aWeigth)
  {
    iDarkenArray[aX][aY] += aWeigth;
    iWeight += aWeigth;
  }

  void Normalize()
  {
    double k = KPatternWidth * KPatternHeight / iWeight;

    for (int i = 0; i < KPatternWidth; ++i)
      for (int j = 0; j < KPatternHeight; ++j)
      {
        iDarkenArray[i][j] *= k;
      }

      iWeight = KPatternWidth * KPatternHeight;
  }

private:
  vector< vector<double> > iDarkenArray;
  double iWeight;
public:
  const static int KPatternWidth = 8;
  const static int KPatternHeight = 12;
  const static int KDigitMinWeight = KPatternWidth * KPatternHeight / 10.0;
};

////////////////////////////////////////////////////////////////////
// TNeuron

class TNeuron
{
public:
  TNeuron(): iSynapseWeights(TDigitPattern::KPatternWidth * TDigitPattern::KPatternHeight) 
  {}

  void Init(const double* aInitArray)
  {
    int synapseCount = iSynapseWeights.size();
    for (int i = 0; i < synapseCount; ++i)
    {
      iSynapseWeights[i] = aInitArray[i];
    }
  }

  ~TNeuron() {}

public:
  double SumWeight(const TDigitPattern& aPattern) const
  {
    double sum = 0.0;
    int w = TDigitPattern::KPatternWidth;
    int h = TDigitPattern::KPatternHeight;
    for (int i = 0; i < w; ++i)
      for (int j = 0; j < h; ++j)
      {
        sum += aPattern.At(i, j) * iSynapseWeights[i * h + j];
      }

      return sum;
  }

  void ChangeWeight(double aDiff, const TDigitPattern& aPattern)
  {
    int w = TDigitPattern::KPatternWidth;
    int h = TDigitPattern::KPatternHeight;

    for (int i = 0; i < w; ++i)
      for (int j = 0; j < h; ++j)
      {
        iSynapseWeights[i * h + j] += aDiff * aPattern.At(i, j);
      }
  }

private:
  std::vector<double> iSynapseWeights;
};

//////////////////////////////////////////////////////////////////////////
// PatternRecognizer

class PatternRecognizer
{
public:
  PatternRecognizer() : iNeurons(KPatternClassCount) 
  {
    int neuronCount = iNeurons.size();
    for (int i = 0 ; i < neuronCount; ++i)
    {
      iNeurons[i].Init(InitArray + i * TDigitPattern::KPatternWidth * TDigitPattern::KPatternHeight);
    }
  }

  ~PatternRecognizer() {}

public:
  // return class, which has maximum weight
  int Recognize(const TDigitPattern& aPattern)
  {
    int neuronIndex = 0;
    int maxSignal = iNeurons[neuronIndex].SumWeight(aPattern);
    int neuronCount = iNeurons.size();

    for (int i = 1; i < neuronCount; ++i)
    {
      double signal = iNeurons[i].SumWeight(aPattern);
      if (signal > maxSignal)
      {
        maxSignal = signal;
        neuronIndex = i;
      }
      else if (signal == maxSignal)
      {
        neuronIndex = (rand() % 2) ? neuronIndex : i;
      }
    }
    return neuronIndex;
  }

  // return true, if lesson is unnecessary
  bool Teach(const TDigitPattern& aPattern, int aTrueClass)
  {
    double q = 1.0 / TDigitPattern::KPatternWidth / TDigitPattern::KPatternHeight;
    bool res = true;

    int recognizedClass = Recognize(aPattern);
    while (recognizedClass != aTrueClass)
    {
      iNeurons[recognizedClass].ChangeWeight(-q, aPattern);
      iNeurons[aTrueClass].ChangeWeight(q, aPattern);
      recognizedClass = Recognize(aPattern);
      res = false;
    }
    return res;
  }

private:
  std::vector<TNeuron> iNeurons;
};

//////////////////////////////////////////////////////////////////////////

void makePatternFromArea(const TArea& aArea, TDigitPattern& aPattern)
{
  int patternWidth = aPattern.Width();
  int patternHeight = aPattern.Height();
  int pointCount = aArea.PointCount();

  double w = double(aArea.MaxX() - aArea.MinX() + 1) / patternWidth;
  double h = double(aArea.MaxY() - aArea.MinY() + 1) / patternHeight;
  double q = 1.0 / w / h;

  for (int i = 0; i < pointCount; ++i)
  {
    int x = aArea.Point(i).iX - aArea.MinX();
    int y = aArea.Point(i).iY - aArea.MinY();
    // x 
    int floorX = int(x / w);
    int ceilingX = int((x + 1) / w);
    if (ceilingX > patternWidth - 1)
      ceilingX = patternWidth - 1;
    // y
    int floorY = int(y / h);
    int ceilingY = int((y + 1) / h);
    if (ceilingY > patternHeight - 1)
      ceilingY = patternHeight - 1;
    //
    if (floorX == ceilingX)
    {
      if (floorY == ceilingY)
        aPattern.DarkenPoint(floorX, floorY, q);
      else
      {
        aPattern.DarkenPoint(floorX, floorY, q * (ceilingY * h - y));
        aPattern.DarkenPoint(floorX, ceilingY, q * (y + 1 - ceilingY * h));
      }
    }
    else
    {
      if (floorY == ceilingY)
      {
        aPattern.DarkenPoint(floorX, floorY, q * (ceilingX * w - x));
        aPattern.DarkenPoint(ceilingX, floorY, q * (x + 1 - ceilingX * w));
      }
      else
      {
        aPattern.DarkenPoint(floorX, floorY, 
          q * (ceilingY * h - y) * (ceilingX * w - x));
        aPattern.DarkenPoint(ceilingX, floorY, 
          q * (ceilingY * h - y) * (x + 1 - ceilingX * w));
        aPattern.DarkenPoint(floorX, ceilingY, 
          q * (y + 1 - ceilingY * h) * (ceilingX * w - x));
        aPattern.DarkenPoint(ceilingX, ceilingY, 
          q * (y + 1 - ceilingY * h) * (x + 1 - ceilingX * w));
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////

// aAreas уничтожается после использования
void choosePatterns(TAreaPtrArray& aAreas, std::vector<TDigitPattern>& aPatterns)
{
  int areaCount = aAreas.size();

  // select large areas
  TAreaPtrArray largeAreas;
  for (int i = 0; i < areaCount; ++i)
  {
    if (aAreas[i]->PointCount() > KNoiseThreshold)
    {
      largeAreas.push_back(aAreas[i]);
    }
    else
    {
      delete aAreas[i];
    }
    aAreas[i] = 0;
  }

  areaCount = largeAreas.size();

  for (int i = 0; i < areaCount; ++i)
  {
    TDigitPattern pattern;
    makePatternFromArea(*(largeAreas[i]), pattern);
    if (pattern.Weight() > TDigitPattern::KDigitMinWeight)
    {
      pattern.Normalize();
      aPatterns.push_back(pattern);
    }
  }

  // cleanup
  areaCount = largeAreas.size();
  for (int i = 0; i < areaCount; ++i)
  {
    delete largeAreas[i];
    largeAreas[i] = 0;
  }
}

//////////////////////////////////////////////////////////////////////////

void ReadImage(TImage& aImage)
{
  int counter = 0;
  std::string line;
  while (!std::cin.eof() && counter < KMaxLineNum)
  {
    getline(std::cin, line);
    size_t lineLen = line.size();

    if (aImage.size() < lineLen)
      aImage.resize(lineLen);

    for (size_t i = 0; i < lineLen; ++i)
    {
      aImage[i].push_back(ConvertToColor(line[i]));
    }
    counter ++;
  }
}

//////////////////////////////////////////////////////////////////////////

int main()
{
  PatternRecognizer recogn;
  TImage image;
  ReadImage(image);

  TAreaPtrArray areas;
  AreaSelector::SelectFromImage(image, areas);

  std::vector<TDigitPattern> patternArray;
  choosePatterns(areas, patternArray);

  int patternCount = patternArray.size();
  for (int i = 0 ; i < patternCount; ++i)
  {
    std::cout << recogn.Recognize(patternArray[i]);
  }
  std::cout << std::endl;

  return 0;
}
