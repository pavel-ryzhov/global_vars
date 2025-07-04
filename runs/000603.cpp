
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
  0.920652, 0.577639, 0.680916, 0.934047, 0.972056, 0.902604, 1.03658, 1.07253, 0.713205, 0.866897, 0.526342, 0.409283, 0.683228, 0.658188, 0.903386, 0.877071, 0.855759, 0.709653, 0.76237, 0.666769, 1.06003, 0.682713, 0.975277, 0.710408, 0.591071, 0.606976, 0.893625, 1.05225, 0.979966, 0.715869, 0.5248, 0.85397, 0.94168, 0.970161, 0.766836, 0.606094, 0.747605, 0.848973, 0.923671, 0.884037, 0.396238, 0.728515, 0.571955, 0.663324, 0.819208, 0.548698, 0.769919, 0.677456, 0.962574, 0.809507, 0.558994, 0.765746, 0.591739, 0.495991, 0.390543, 0.641332, 0.776237, 0.871695, 0.752121, 0.819347, 0.889296, 0.542811, 0.775158, 0.968129, 0.653143, 0.307832, 0.722838, 0.544798, 0.630104, 0.595403, 0.530447, 0.74956, 0.716323, 0.501348, 1.08064, 1.10017, 0.429904, 0.560198, 0.705951, 0.823395, 0.821415, 0.816051, 0.464268, 0.632965, 0.817056, 0.606665, 0.551224, 0.830295, 1.03415, 1.00719, 0.877403, 0.780928, 0.575202, 0.616981, 0.664559, 0.449885, 
  0.566005, 0.693546, 0.712424, 0.868356, 0.553425, 0.540975, 0.556378, 0.503699, 0.645376, 0.634619, 0.599905, 0.811777, 0.567431, 0.613333, 0.880122, 0.722353, 0.705002, 0.574614, 0.328955, 0.686192, 0.54933, 0.747719, 0.45234, 0.742447, 0.721889, 0.562636, 1.17539, 0.865053, 0.692996, 0.676799, 0.516733, 0.952094, 0.738558, 0.578818, 0.734275, 0.716868, 0.646096, 0.643427, 1.02868, 1.00494, 0.85502, 0.843652, 0.592291, 0.830834, 0.539171, 0.677548, 0.810306, 0.656445, 0.452705, 0.749659, 0.879483, 1.10055, 0.687634, 0.917181, 0.83584, 0.862127, 0.735008, 0.777821, 0.543326, 0.761704, 0.845134, 0.922649, 0.923284, 0.805718, 0.650167, 0.516736, 0.750781, 0.664043, 0.86554, 1.08637, 0.980499, 0.77913, 0.701557, 0.772325, 0.675304, 0.73612, 0.947769, 0.620088, 0.464737, 0.54356, 0.749428, 0.535893, 0.850184, 1.23825, 1.20834, 0.66954, 1.05959, 0.726774, 0.857902, 0.618139, 0.974243, 0.612492, 0.766501, 0.533849, 0.74068, 0.886802, 
  0.644432, 0.535502, 0.97423, 0.801186, 0.76963, 0.746211, 0.481796, 0.894344, 0.828665, 0.689822, 0.722833, 0.851936, 0.641861, 0.883764, 0.767295, 0.684821, 0.695804, 0.725564, 0.543423, 0.753216, 0.724032, 0.734496, 0.716772, 0.956057, 0.62062, 0.739367, 0.642337, 0.889256, 0.528353, 0.49181, 0.542176, 0.666638, 0.901852, 1.02764, 1.03792, 0.524275, 0.742465, 0.412659, 0.734785, 0.746665, 0.472023, 0.687269, 0.724715, 0.961265, 0.85086, 0.777767, 0.577697, 0.910815, 0.545655, 0.725972, 0.732075, 0.465794, 0.924278, 0.841415, 0.931691, 0.87144, 0.446212, 0.776627, 0.730215, 1.00143, 0.842955, 0.770423, 0.589017, 0.647341, 0.67402, 0.648524, 0.708229, 0.847083, 0.819649, 0.64999, 1.10319, 0.964168, 0.499546, 0.910616, 0.990842, 0.985913, 0.976105, 0.798139, 0.61194, 0.447539, 0.432239, 0.696288, 0.760854, 0.763663, 0.728504, 0.510325, 0.690321, 1.07034, 0.878226, 0.563675, 0.417454, 0.42969, 0.736008, 0.966774, 0.741316, 1.00736, 
  0.934686, 0.848909, 0.690761, 0.618973, 0.296988, 0.566186, 0.700698, 0.631222, 0.914447, 0.843391, 0.835282, 0.773124, 0.86774, 0.860989, 0.852276, 0.593003, 0.238833, 0.329023, 0.615726, 0.365611, 0.463822, 0.938633, 0.929756, 1.0102, 0.781105, 0.711464, 0.778753, 0.551366, 0.739068, 0.634915, 0.672634, 0.736314, 0.436524, 0.749913, 0.806351, 0.658936, 0.92106, 0.673839, 0.637765, 0.829679, 0.964645, 0.826967, 0.863186, 0.62065, 0.750285, 0.599173, 0.634439, 0.775715, 0.919098, 0.846451, 0.690331, 0.761797, 0.725932, 0.653408, 0.68264, 0.649499, 0.485214, 0.758331, 0.571184, 0.643201, 0.561189, 0.622973, 0.95562, 0.625705, 0.84184, 0.732205, 1.08089, 0.878074, 0.506105, 0.826382, 0.829014, 0.782404, 0.773322, 1.03638, 0.928959, 0.778327, 0.616211, 0.792129, 1.07452, 1.02705, 0.822818, 0.569078, 0.795586, 0.677987, 0.731913, 0.517902, 0.566342, 0.643245, 0.778912, 0.529047, 0.689906, 0.707748, 0.920554, 0.841298, 0.726466, 0.4998, 
  0.810277, 0.426732, 0.479575, 0.461492, 0.531473, 0.84056, 0.904261, 0.812915, 1.01003, 0.648668, 0.525331, 0.432836, 0.843895, 0.411994, 0.738998, 0.580282, 0.733066, 1.07102, 1.10189, 0.883868, 0.94088, 0.704764, 0.607198, 0.626709, 0.788155, 0.476892, 0.84884, 0.850701, 0.864083, 1.00697, 0.649213, 0.709784, 0.736918, 0.549422, 0.516585, 0.421835, 0.545566, 0.745752, 0.858724, 0.846297, 0.665185, 0.510559, 0.803644, 0.883052, 0.938317, 0.805095, 0.538127, 0.780628, 0.761601, 0.798336, 0.457164, 0.90353, 0.831067, 0.743612, 0.971597, 1.09893, 0.904578, 0.9023, 0.615178, 0.85186, 0.544232, 0.804247, 0.799892, 0.739534, 0.923537, 0.954034, 0.797022, 0.661602, 0.737148, 0.816291, 0.878042, 0.60096, 0.544758, 0.697805, 0.74267, 0.703588, 0.809278, 0.710926, 0.746875, 0.790578, 0.841618, 0.660607, 0.563648, 0.738827, 0.723011, 0.522142, 0.69845, 0.834521, 0.395848, 0.877555, 0.690892, 0.596966, 0.504749, 0.829965, 0.54143, 0.817951, 
  0.722176, 0.624098, 0.646207, 0.843157, 0.788637, 0.820517, 1.02642, 0.376857, 0.793126, 0.881228, 1.09535, 1.00957, 0.867943, 0.9936, 0.722062, 0.644851, 0.827407, 0.869258, 0.568615, 0.619473, 0.52219, 0.74112, 0.813032, 0.874738, 0.797118, 0.452998, 0.694659, 0.905872, 0.987492, 0.77637, 0.458253, 0.553384, 0.675974, 0.449222, 0.912277, 0.936221, 0.819392, 0.826946, 0.92947, 0.557573, 0.532556, 0.821719, 0.433231, 0.767915, 0.378342, 0.512675, 0.757181, 0.612762, 0.572273, 0.607227, 0.793336, 0.484447, 1.0867, 0.97428, 0.726534, 0.811815, 0.880005, 0.681271, 0.799884, 0.957772, 0.600451, 0.838309, 0.635204, 0.411702, 0.981255, 0.891505, 0.78474, 0.694514, 0.596918, 0.929246, 0.764342, 0.541459, 0.861892, 0.75381, 0.286201, 0.370337, 0.51059, 0.838921, 0.505028, 0.611934, 0.821481, 0.985585, 0.834087, 0.516102, 1.13114, 0.920662, 0.411961, 0.662993, 0.442435, 0.861894, 0.72109, 0.824278, 0.677746, 0.960232, 0.585503, 0.717687, 
  0.779878, 0.413361, 0.58499, 0.749055, 1.03444, 1.17884, 0.914591, 1.01474, 0.691633, 0.638154, 0.758197, 0.650691, 0.3716, 0.663153, 0.48069, 0.789268, 0.673012, 0.620201, 1.00393, 0.925192, 0.821253, 1.04954, 0.883774, 0.896589, 0.819404, 0.549023, 0.631803, 0.621166, 0.733735, 0.848702, 0.687119, 0.691403, 1.05857, 0.62319, 0.722554, 0.872019, 0.724218, 0.89714, 0.649231, 0.829696, 0.559718, 0.978969, 0.630986, 0.891742, 0.67255, 0.728881, 0.671257, 0.907993, 0.599764, 0.607042, 0.577415, 0.641994, 0.803601, 0.772388, 0.695085, 0.738642, 0.90066, 0.663371, 0.774106, 0.833284, 0.738587, 0.633207, 0.801158, 0.523045, 0.864562, 0.613016, 0.652201, 0.607182, 0.527596, 0.904563, 0.811822, 0.685145, 0.703832, 0.666486, 0.393938, 0.388755, 0.65506, 0.99399, 0.568125, 0.685089, 0.934198, 0.707959, 0.730904, 0.66699, 0.639978, 0.613029, 0.840364, 0.204788, 0.479632, 0.671564, 0.702958, 0.900886, 0.724388, 0.865766, 0.957127, 0.746906, 
  0.902503, 0.806978, 0.694548, 0.864014, 0.747824, 0.519523, 0.830951, 0.851304, 0.576105, 0.759708, 0.549672, 0.666208, 1.02839, 0.913051, 0.703652, 0.505944, 0.550588, 0.484857, 0.512978, 0.770377, 0.800512, 0.709687, 0.742962, 0.780552, 0.886297, 0.823826, 0.537743, 0.868506, 0.581223, 0.539823, 0.491638, 0.904571, 0.664637, 0.771211, 0.70012, 0.490585, 1.05599, 0.678332, 0.535252, 0.48261, 0.584175, 0.683259, 0.800216, 0.93077, 0.836947, 0.64887, 0.665543, 0.973325, 0.635981, 0.675233, 0.734946, 0.442937, 0.797152, 0.700332, 0.790395, 0.837651, 0.90245, 0.72376, 0.575045, 0.866164, 0.70997, 1.0071, 0.971708, 0.835995, 0.805539, 0.52009, 0.672464, 0.525281, 0.912849, 0.611529, 0.846606, 0.820918, 0.679838, 1.0683, 0.790232, 0.699255, 0.915562, 0.817838, 0.352082, 0.369787, 0.758859, 0.693089, 0.75624, 0.514788, 1.22254, 0.921627, 0.659325, 0.539275, 0.760741, 0.562002, 0.52121, 0.484056, 0.406038, 0.628022, 0.446426, 0.752411, 
  0.638889, 0.727973, 0.583335, 0.743365, 0.742045, 0.365283, 0.517559, 0.887294, 1.03503, 1.10399, 1.04124, 0.641289, 0.609797, 0.920239, 0.907091, 0.730095, 0.844904, 0.76762, 0.891533, 0.99483, 0.870783, 0.632189, 0.681474, 0.494941, 0.778243, 0.676772, 0.86429, 0.847542, 0.893959, 0.876359, 0.652713, 0.920328, 0.563324, 0.471328, 0.782617, 0.747474, 0.726318, 0.841628, 0.871389, 0.657849, 0.71322, 0.9464, 0.695728, 0.650854, 0.736164, 0.740851, 0.735253, 0.73293, 0.742984, 0.703417, 0.568478, 0.643023, 0.765748, 0.849387, 1.04671, 0.704315, 0.794485, 0.806146, 0.514757, 0.533312, 0.591705, 0.8339, 0.606813, 0.616792, 0.813625, 0.625255, 0.922566, 0.541755, 0.890292, 0.80841, 0.515489, 0.611999, 0.746047, 0.683226, 0.562939, 0.916277, 0.63282, 0.621868, 0.584236, 0.585608, 0.842488, 0.71766, 0.639282, 1.03951, 0.576064, 0.88299, 0.746431, 0.972387, 0.590438, 0.590247, 0.640302, 0.821288, 0.909372, 0.832722, 0.768775, 0.799328, 
  0.830507, 0.945263, 0.903015, 0.916357, 1.01348, 1.0193, 0.680762, 0.305092, 0.692382, 0.733524, 0.445844, 0.603283, 0.668118, 0.631691, 0.744428, 0.82231, 0.875625, 0.848192, 0.77058, 0.634471, 0.647168, 0.559141, 0.547418, 0.707359, 0.866097, 0.700046, 0.632553, 0.698292, 0.499124, 0.582384, 0.754721, 0.711513, 0.631954, 0.859089, 0.820465, 0.825693, 0.721287, 0.481304, 0.331031, 0.710656, 0.807219, 0.722694, 0.884051, 0.849594, 0.928156, 0.710442, 0.740279, 0.771931, 1.00737, 0.777155, 0.857779, 0.740181, 0.836158, 0.552006, 0.728963, 0.63425, 0.67515, 0.438679, 0.724185, 0.781924, 0.82648, 0.624378, 0.842149, 0.62604, 0.642311, 0.790803, 0.558269, 0.635669, 0.813797, 0.62182, 0.890554, 0.664255, 0.522886, 0.659709, 0.798272, 0.921257, 0.956702, 0.695903, 0.636511, 0.915466, 0.575456, 0.76779, 0.754949, 0.410916, 0.421452, 0.735116, 0.875996, 1.01538, 0.781718, 1.01869, 0.814541, 0.791667, 0.529441, 0.524392, 0.827719, 0.871868
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
