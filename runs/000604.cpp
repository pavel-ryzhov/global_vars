
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
  0.920652, 0.582306, 0.695398, 0.953262, 0.988719, 0.909928, 1.03565, 1.07159, 0.712267, 0.860094, 0.519403, 0.409283, 0.690646, 0.671019, 0.904963, 0.878648, 0.867393, 0.710512, 0.761432, 0.665831, 1.05909, 0.681775, 0.973232, 0.704802, 0.596212, 0.606757, 0.892688, 1.05274, 0.979028, 0.714931, 0.525659, 0.855547, 0.943257, 0.971738, 0.766617, 0.595357, 0.748368, 0.848035, 0.929917, 0.897467, 0.405358, 0.729014, 0.577842, 0.679987, 0.835871, 0.565361, 0.779758, 0.676518, 0.959738, 0.801445, 0.563504, 0.772411, 0.591176, 0.488904, 0.382122, 0.647998, 0.775359, 0.86938, 0.756631, 0.824054, 0.90183, 0.533416, 0.770129, 0.968129, 0.643931, 0.298938, 0.705597, 0.538332, 0.629026, 0.579957, 0.52644, 0.748085, 0.716513, 0.505055, 1.07901, 1.09007, 0.408404, 0.539357, 0.689069, 0.808668, 0.811318, 0.808427, 0.464099, 0.623816, 0.816914, 0.6028, 0.564522, 0.842672, 1.04192, 1.01299, 0.883909, 0.776658, 0.573407, 0.607241, 0.654965, 0.449743, 
  0.582422, 0.683462, 0.681116, 0.851173, 0.547682, 0.540975, 0.555907, 0.502758, 0.645207, 0.631072, 0.59838, 0.818496, 0.572948, 0.602988, 0.848815, 0.707995, 0.699259, 0.574614, 0.319068, 0.676366, 0.539701, 0.733361, 0.450344, 0.748225, 0.722338, 0.566344, 1.16066, 0.866955, 0.702807, 0.68176, 0.509456, 0.941591, 0.74046, 0.58072, 0.746642, 0.729512, 0.65874, 0.657423, 1.04403, 1.03783, 0.878766, 0.85974, 0.602805, 0.841584, 0.554393, 0.69277, 0.823372, 0.669089, 0.463219, 0.761524, 0.896078, 1.11444, 0.700441, 0.928165, 0.846354, 0.872641, 0.745522, 0.790024, 0.55714, 0.775055, 0.830087, 0.907602, 0.908236, 0.79632, 0.649245, 0.505926, 0.735734, 0.648996, 0.854885, 1.08416, 0.985898, 0.799542, 0.691577, 0.757984, 0.668731, 0.738022, 0.949671, 0.611397, 0.450872, 0.537128, 0.748063, 0.535204, 0.857479, 1.2669, 1.19142, 0.653944, 1.04523, 0.712416, 0.843544, 0.602953, 0.961448, 0.603075, 0.757085, 0.526316, 0.743956, 0.906232, 
  0.618599, 0.535676, 0.988588, 0.815544, 0.775373, 0.746211, 0.481796, 0.894344, 0.828834, 0.693369, 0.724359, 0.838603, 0.62346, 0.88529, 0.781653, 0.699179, 0.701548, 0.725564, 0.543423, 0.754567, 0.73366, 0.748854, 0.718298, 0.942724, 0.607287, 0.73497, 0.656384, 0.903614, 0.534097, 0.49181, 0.548763, 0.679983, 0.91621, 1.042, 1.03758, 0.510942, 0.729132, 0.397975, 0.718748, 0.725327, 0.450178, 0.670492, 0.713512, 0.950062, 0.839657, 0.766564, 0.564884, 0.897482, 0.534452, 0.713418, 0.714791, 0.451213, 0.911724, 0.830212, 0.920488, 0.860237, 0.435009, 0.763735, 0.715712, 0.988097, 0.857313, 0.784781, 0.603375, 0.661699, 0.688378, 0.662882, 0.722587, 0.861441, 0.829616, 0.651511, 1.0971, 0.950835, 0.508836, 0.924974, 1.0052, 1.00027, 0.990463, 0.812497, 0.625116, 0.453283, 0.432915, 0.696288, 0.756636, 0.75033, 0.730362, 0.523332, 0.704679, 1.0847, 0.892584, 0.57533, 0.420832, 0.42969, 0.736008, 0.966774, 0.737099, 0.994028, 
  0.926258, 0.871357, 0.714838, 0.620736, 0.296915, 0.564549, 0.690506, 0.615078, 0.913426, 0.845762, 0.849522, 0.789256, 0.857099, 0.872878, 0.85391, 0.593577, 0.233741, 0.320939, 0.604282, 0.35596, 0.461888, 0.934422, 0.94071, 1.03228, 0.780938, 0.70585, 0.756348, 0.533477, 0.717773, 0.623762, 0.651224, 0.722088, 0.421732, 0.740195, 0.793722, 0.664272, 0.906343, 0.67553, 0.621504, 0.818901, 0.956852, 0.826418, 0.857955, 0.60439, 0.734024, 0.568885, 0.606336, 0.775653, 0.904489, 0.850088, 0.674376, 0.746984, 0.720833, 0.644254, 0.670724, 0.619767, 0.453572, 0.726645, 0.544477, 0.634166, 0.545239, 0.611671, 0.940412, 0.609828, 0.82423, 0.713798, 1.06996, 0.851543, 0.472885, 0.800811, 0.809328, 0.767518, 0.751473, 1.02355, 0.912147, 0.760519, 0.593435, 0.761367, 1.05591, 1.01083, 0.803132, 0.552864, 0.779834, 0.652002, 0.712526, 0.516406, 0.571616, 0.648075, 0.762104, 0.507785, 0.690351, 0.704733, 0.914221, 0.841547, 0.719008, 0.472921, 
  0.810277, 0.426732, 0.479575, 0.461492, 0.531473, 0.84056, 0.904261, 0.812915, 1.01003, 0.648668, 0.525331, 0.432836, 0.843895, 0.411994, 0.738998, 0.580282, 0.733066, 1.07102, 1.10189, 0.883868, 0.94088, 0.704764, 0.607198, 0.626709, 0.788155, 0.476892, 0.84884, 0.850701, 0.864083, 1.00697, 0.649213, 0.709784, 0.736918, 0.549422, 0.516585, 0.421835, 0.545566, 0.745752, 0.858724, 0.846297, 0.665185, 0.510559, 0.803644, 0.883052, 0.938317, 0.805095, 0.538127, 0.780628, 0.761601, 0.798336, 0.457164, 0.90353, 0.831067, 0.743612, 0.971597, 1.09893, 0.904578, 0.9023, 0.615178, 0.85186, 0.544232, 0.804247, 0.799892, 0.739534, 0.923537, 0.954034, 0.797022, 0.661602, 0.737148, 0.816291, 0.878042, 0.60096, 0.544758, 0.697805, 0.74267, 0.703588, 0.809278, 0.710926, 0.746875, 0.790578, 0.841618, 0.660607, 0.563648, 0.738827, 0.723011, 0.522142, 0.69845, 0.834521, 0.395848, 0.877555, 0.690892, 0.596966, 0.504749, 0.829965, 0.54143, 0.817951, 
  0.726384, 0.612514, 0.628102, 0.827824, 0.776763, 0.820617, 1.02686, 0.374424, 0.788218, 0.882927, 1.08143, 0.994013, 0.869386, 1.00235, 0.730651, 0.641825, 0.825137, 0.874841, 0.591675, 0.614639, 0.519161, 0.738818, 0.806185, 0.868739, 0.782274, 0.471277, 0.718132, 0.908191, 0.981813, 0.782364, 0.480316, 0.553848, 0.674171, 0.442328, 0.906462, 0.936397, 0.808775, 0.864617, 0.958915, 0.560562, 0.530721, 0.829018, 0.43083, 0.783496, 0.390583, 0.526185, 0.772854, 0.614896, 0.566251, 0.620699, 0.806428, 0.492633, 1.08126, 0.978884, 0.71729, 0.824557, 0.896954, 0.697573, 0.799961, 0.970703, 0.592649, 0.843725, 0.634896, 0.387989, 0.949819, 0.882955, 0.785327, 0.679037, 0.591401, 0.923519, 0.769626, 0.54762, 0.871424, 0.761579, 0.292384, 0.339402, 0.493319, 0.833367, 0.505345, 0.610487, 0.823066, 0.988814, 0.847803, 0.51468, 1.14146, 0.92138, 0.405002, 0.647443, 0.439821, 0.849729, 0.703691, 0.811556, 0.669879, 0.959278, 0.577715, 0.717109, 
  0.779878, 0.413449, 0.587812, 0.75546, 1.05034, 1.19473, 0.931421, 1.03169, 0.699591, 0.637357, 0.752722, 0.652998, 0.369758, 0.647007, 0.484613, 0.792107, 0.675096, 0.615812, 1.00594, 0.935691, 0.822218, 1.05165, 0.881334, 0.88966, 0.838107, 0.537413, 0.623215, 0.609964, 0.727984, 0.838195, 0.675751, 0.688303, 1.04754, 0.617697, 0.724724, 0.879377, 0.737978, 0.878537, 0.637147, 0.825107, 0.559919, 0.970492, 0.622124, 0.881192, 0.66743, 0.723245, 0.662512, 0.91088, 0.612624, 0.595511, 0.562743, 0.641918, 0.824854, 0.778876, 0.697228, 0.741325, 0.898957, 0.667516, 0.785956, 0.831405, 0.73398, 0.60755, 0.781592, 0.529424, 0.898662, 0.631378, 0.661412, 0.627967, 0.549704, 0.920057, 0.820502, 0.676514, 0.704693, 0.636131, 0.357296, 0.389445, 0.688954, 1.01702, 0.579873, 0.698601, 0.944438, 0.707379, 0.722571, 0.672427, 0.641428, 0.608973, 0.800003, 0.160447, 0.451553, 0.683608, 0.704443, 0.899725, 0.719514, 0.872877, 0.970587, 0.747189, 
  0.917534, 0.806978, 0.694548, 0.864014, 0.747824, 0.519523, 0.830951, 0.851304, 0.576105, 0.759708, 0.549672, 0.666208, 1.04975, 0.913051, 0.703652, 0.505944, 0.550588, 0.484857, 0.512978, 0.770377, 0.800512, 0.709687, 0.742962, 0.780552, 0.907658, 0.823826, 0.537743, 0.868506, 0.581223, 0.539823, 0.491638, 0.904571, 0.664637, 0.771211, 0.70012, 0.490585, 1.07735, 0.678332, 0.535252, 0.48261, 0.584175, 0.683259, 0.800216, 0.93077, 0.836947, 0.64887, 0.665543, 0.973325, 0.657342, 0.687101, 0.746813, 0.454804, 0.809019, 0.712199, 0.802262, 0.849519, 0.914317, 0.735627, 0.586912, 0.878031, 0.731331, 1.02846, 0.993069, 0.857355, 0.8269, 0.541451, 0.693824, 0.546642, 0.93421, 0.632889, 0.867966, 0.842279, 0.701199, 1.08966, 0.811593, 0.720616, 0.936923, 0.839198, 0.373443, 0.391148, 0.78022, 0.71445, 0.7776, 0.536148, 1.2439, 0.942988, 0.680685, 0.560636, 0.782102, 0.583363, 0.542571, 0.505417, 0.427399, 0.649383, 0.467786, 0.773772, 
  0.639294, 0.729591, 0.580806, 0.73407, 0.718711, 0.334705, 0.51019, 0.889113, 1.03294, 1.11132, 1.06271, 0.64682, 0.611833, 0.911778, 0.906621, 0.726436, 0.836853, 0.771955, 0.887033, 1.00653, 0.874023, 0.635829, 0.682369, 0.504916, 0.762951, 0.67493, 0.871741, 0.855859, 0.910373, 0.886306, 0.661562, 0.931076, 0.571423, 0.4739, 0.785392, 0.748048, 0.714839, 0.824591, 0.866827, 0.64734, 0.713722, 0.950413, 0.708089, 0.642825, 0.721572, 0.741592, 0.748432, 0.727979, 0.731302, 0.696817, 0.57242, 0.633978, 0.745572, 0.844982, 1.06403, 0.697731, 0.797533, 0.805474, 0.515093, 0.513008, 0.588877, 0.852472, 0.624555, 0.621986, 0.801291, 0.616139, 0.91858, 0.547075, 0.885632, 0.817291, 0.502851, 0.604408, 0.743532, 0.6936, 0.581, 0.93511, 0.621156, 0.625727, 0.585292, 0.582116, 0.838079, 0.71648, 0.625427, 1.04085, 0.579328, 0.880246, 0.757616, 0.993639, 0.606077, 0.578591, 0.635626, 0.828816, 0.918226, 0.826025, 0.769121, 0.800987, 
  0.828707, 0.937936, 0.899217, 0.916428, 1.0162, 1.0282, 0.682458, 0.306787, 0.693382, 0.729726, 0.436459, 0.601482, 0.661228, 0.631646, 0.746124, 0.824006, 0.877321, 0.849888, 0.772276, 0.636167, 0.648864, 0.560836, 0.547373, 0.701397, 0.864079, 0.701742, 0.634249, 0.699987, 0.50082, 0.58408, 0.756417, 0.713209, 0.63365, 0.860785, 0.822161, 0.823675, 0.722906, 0.479208, 0.328935, 0.70856, 0.805124, 0.720598, 0.882984, 0.852642, 0.931205, 0.711433, 0.738184, 0.773549, 1.00899, 0.775059, 0.855683, 0.738086, 0.834062, 0.549911, 0.727896, 0.637298, 0.678199, 0.441728, 0.72294, 0.78362, 0.824462, 0.626074, 0.843845, 0.627736, 0.644007, 0.792499, 0.559965, 0.637365, 0.815493, 0.623516, 0.892249, 0.662237, 0.515996, 0.659664, 0.799968, 0.922953, 0.958398, 0.699142, 0.638207, 0.917161, 0.577152, 0.769486, 0.754904, 0.404026, 0.419651, 0.727789, 0.872198, 1.01545, 0.784443, 1.0281, 0.816237, 0.793363, 0.529512, 0.520594, 0.818334, 0.870068
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
    for (int i = -1; i <=1; ++i)
      for (int j = -1; j <=1; ++j)
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
