
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
  0.927853, 0.606969, 0.70312, 0.940705, 0.964092, 0.861076, 1.01075, 1.03781, 0.69159, 0.882342, 0.590193, 0.44311, 0.712133, 0.652458, 0.911421, 0.862599, 0.829501, 0.693548, 0.769828, 0.6662, 1.05543, 0.68639, 1.01068, 0.767391, 0.594729, 0.581833, 0.887003, 1.0211, 0.953938, 0.707461, 0.530592, 0.866107, 0.93732, 0.966646, 0.770561, 0.636572, 0.737146, 0.846367, 0.925905, 0.881271, 0.406686, 0.737535, 0.561145, 0.651913, 0.786223, 0.523944, 0.753225, 0.656166, 0.956768, 0.820931, 0.574504, 0.780541, 0.605587, 0.49138, 0.377925, 0.621137, 0.740813, 0.836271, 0.733377, 0.805188, 0.913725, 0.553048, 0.785462, 0.96629, 0.647525, 0.291648, 0.723089, 0.527283, 0.610051, 0.578734, 0.525359, 0.749958, 0.777991, 0.526373, 1.09213, 1.08824, 0.43244, 0.563856, 0.698165, 0.823646, 0.820883, 0.820649, 0.45585, 0.65582, 0.854614, 0.649077, 0.555375, 0.820537, 1.01634, 0.973594, 0.878311, 0.776717, 0.570967, 0.626267, 0.699899, 0.457086, 
  0.57541, 0.693114, 0.679253, 0.836327, 0.557559, 0.54509, 0.534352, 0.485925, 0.621837, 0.611003, 0.591298, 0.818741, 0.545114, 0.587409, 0.849096, 0.721331, 0.717237, 0.573298, 0.290813, 0.653572, 0.53584, 0.752022, 0.458601, 0.755211, 0.715746, 0.570372, 1.17298, 0.877178, 0.703869, 0.664901, 0.501338, 0.949722, 0.775383, 0.625746, 0.772825, 0.741146, 0.631411, 0.624853, 0.97156, 0.975347, 0.839102, 0.820193, 0.594819, 0.838253, 0.540347, 0.668041, 0.798795, 0.620091, 0.463823, 0.73694, 0.876085, 1.13669, 0.735164, 0.961759, 0.863792, 0.878697, 0.734407, 0.780712, 0.549397, 0.740829, 0.834648, 0.917646, 0.922097, 0.829957, 0.682011, 0.519994, 0.7347, 0.641519, 0.82879, 1.05012, 0.954145, 0.778192, 0.692458, 0.790392, 0.697911, 0.775733, 0.974802, 0.632749, 0.475628, 0.54869, 0.73977, 0.54138, 0.874898, 1.27361, 1.18491, 0.688856, 1.0653, 0.729193, 0.868343, 0.629034, 0.963259, 0.612638, 0.767077, 0.55121, 0.760144, 0.926432, 
  0.639296, 0.493476, 0.939781, 0.784178, 0.773734, 0.750583, 0.49337, 0.904423, 0.818636, 0.679972, 0.736389, 0.871195, 0.631156, 0.86853, 0.749772, 0.653746, 0.682813, 0.727188, 0.545047, 0.742148, 0.698748, 0.724106, 0.701969, 0.956501, 0.596948, 0.711738, 0.610543, 0.842168, 0.492372, 0.467054, 0.515469, 0.634914, 0.877465, 0.99292, 0.994817, 0.495223, 0.754093, 0.43208, 0.740203, 0.748534, 0.467521, 0.683034, 0.717149, 0.966846, 0.846454, 0.766696, 0.559178, 0.907447, 0.539168, 0.722636, 0.729691, 0.457319, 0.900531, 0.823657, 0.92197, 0.850025, 0.423408, 0.731948, 0.689015, 0.997634, 0.828245, 0.758033, 0.578923, 0.635819, 0.663112, 0.643188, 0.689891, 0.83778, 0.804804, 0.627685, 1.08129, 0.970171, 0.483269, 0.912622, 0.987844, 0.9886, 0.987457, 0.803979, 0.598875, 0.430328, 0.414846, 0.67957, 0.740909, 0.775351, 0.716287, 0.507943, 0.696202, 1.0887, 0.88683, 0.56572, 0.414485, 0.426112, 0.73562, 0.961602, 0.739766, 1.01352, 
  0.932633, 0.890654, 0.704098, 0.625905, 0.297247, 0.558369, 0.670607, 0.582344, 0.885516, 0.854483, 0.860832, 0.765163, 0.861623, 0.882574, 0.849039, 0.583681, 0.244163, 0.341011, 0.576901, 0.31067, 0.432897, 0.936758, 0.930219, 1.03196, 0.761126, 0.724705, 0.764458, 0.536828, 0.737797, 0.660303, 0.640941, 0.708878, 0.412035, 0.748947, 0.8198, 0.677069, 0.890265, 0.713223, 0.649616, 0.840704, 0.990173, 0.843341, 0.864342, 0.6111, 0.750977, 0.585566, 0.654244, 0.809297, 0.901411, 0.88586, 0.700779, 0.754814, 0.713011, 0.624751, 0.626321, 0.599548, 0.437367, 0.713719, 0.562315, 0.649765, 0.528847, 0.612583, 0.933704, 0.571377, 0.821155, 0.706663, 1.02915, 0.811864, 0.447486, 0.798309, 0.825124, 0.775005, 0.75384, 1.02601, 0.892627, 0.722303, 0.628948, 0.785073, 1.06445, 1.00316, 0.796809, 0.565546, 0.794011, 0.660809, 0.725482, 0.519663, 0.550696, 0.633524, 0.760071, 0.524163, 0.681468, 0.69432, 0.905213, 0.846863, 0.719701, 0.459234, 
  0.810277, 0.426732, 0.479575, 0.464641, 0.529655, 0.834811, 0.905753, 0.810425, 1.00236, 0.644571, 0.519176, 0.432836, 0.848061, 0.422074, 0.748976, 0.575971, 0.729503, 1.0657, 1.10211, 0.879983, 0.954876, 0.706968, 0.58804, 0.620845, 0.806255, 0.486786, 0.846077, 0.848112, 0.865715, 1.01736, 0.655972, 0.713202, 0.747567, 0.559602, 0.509756, 0.402949, 0.560742, 0.743554, 0.846537, 0.849842, 0.674453, 0.522861, 0.798083, 0.89936, 0.955519, 0.819374, 0.562895, 0.792922, 0.743223, 0.78777, 0.448095, 0.876586, 0.836645, 0.74034, 0.96002, 1.10217, 0.901798, 0.872209, 0.59769, 0.826067, 0.561754, 0.81266, 0.814569, 0.768854, 0.931653, 0.9533, 0.809155, 0.663199, 0.743971, 0.844045, 0.893084, 0.611376, 0.547268, 0.694123, 0.741319, 0.706098, 0.811788, 0.709721, 0.728325, 0.771945, 0.835803, 0.642957, 0.545015, 0.748223, 0.725196, 0.524327, 0.700635, 0.836707, 0.398033, 0.879741, 0.676796, 0.579189, 0.493669, 0.807555, 0.530676, 0.825237, 
  0.677713, 0.59821, 0.635895, 0.824799, 0.782635, 0.845396, 1.07162, 0.378018, 0.784164, 0.863653, 1.06721, 1.00815, 0.826744, 0.980727, 0.745928, 0.665169, 0.825808, 0.868752, 0.60079, 0.609941, 0.51901, 0.727483, 0.797993, 0.865362, 0.773006, 0.492692, 0.763586, 0.930578, 0.963032, 0.747247, 0.480661, 0.543805, 0.675149, 0.434942, 0.880186, 0.93531, 0.807073, 0.888444, 0.989934, 0.542284, 0.48603, 0.826313, 0.425596, 0.783552, 0.397321, 0.534659, 0.749248, 0.60991, 0.559329, 0.614217, 0.80502, 0.481835, 1.07719, 1.01565, 0.763532, 0.856836, 0.929644, 0.735689, 0.814734, 0.996482, 0.561617, 0.834465, 0.638227, 0.398671, 0.93933, 0.907847, 0.825585, 0.709965, 0.61324, 0.91832, 0.774043, 0.53775, 0.838792, 0.744336, 0.282858, 0.3582, 0.455919, 0.818206, 0.536669, 0.624086, 0.838133, 0.993094, 0.845378, 0.500195, 1.10139, 0.888109, 0.404336, 0.652917, 0.429192, 0.809406, 0.722982, 0.815836, 0.672473, 0.947011, 0.56399, 0.715532, 
  0.779878, 0.424968, 0.613373, 0.767678, 1.04923, 1.19239, 0.931784, 1.06135, 0.740422, 0.649916, 0.740779, 0.641395, 0.380324, 0.686869, 0.482518, 0.799666, 0.68272, 0.638894, 1.00957, 0.955578, 0.850031, 1.06247, 0.902551, 0.88418, 0.827227, 0.526468, 0.610468, 0.608886, 0.753166, 0.844051, 0.666348, 0.722663, 1.0937, 0.654315, 0.751585, 0.888414, 0.725651, 0.876397, 0.648546, 0.842232, 0.566448, 0.940495, 0.637542, 0.892725, 0.684572, 0.752333, 0.675711, 0.916734, 0.62094, 0.62767, 0.585936, 0.655702, 0.802221, 0.752617, 0.710765, 0.737053, 0.910948, 0.688214, 0.786203, 0.837218, 0.755527, 0.645341, 0.800017, 0.545559, 0.883825, 0.616425, 0.659644, 0.64099, 0.556722, 0.925795, 0.82769, 0.710323, 0.696117, 0.649803, 0.392365, 0.405378, 0.675414, 1.00035, 0.559318, 0.710057, 0.954495, 0.72635, 0.747703, 0.677292, 0.627041, 0.591933, 0.840297, 0.228482, 0.513857, 0.711041, 0.704594, 0.925409, 0.745648, 0.883193, 0.968009, 0.747288, 
  0.944749, 0.828893, 0.712728, 0.888934, 0.747824, 0.519523, 0.830951, 0.859878, 0.600554, 0.78518, 0.536025, 0.626838, 1.09882, 0.918206, 0.694642, 0.51603, 0.551277, 0.49272, 0.532941, 0.798591, 0.825434, 0.704512, 0.731992, 0.755727, 0.944664, 0.816437, 0.526235, 0.880276, 0.589465, 0.562867, 0.50405, 0.909785, 0.650677, 0.754512, 0.682957, 0.465697, 1.09522, 0.649383, 0.535197, 0.487156, 0.595789, 0.693833, 0.796108, 0.913165, 0.830537, 0.659086, 0.681432, 0.969588, 0.667477, 0.658098, 0.73951, 0.45159, 0.802447, 0.70055, 0.783783, 0.856102, 0.920283, 0.773101, 0.623189, 0.872495, 0.74466, 1.01607, 0.987596, 0.832321, 0.810666, 0.524907, 0.691029, 0.538216, 0.951181, 0.65024, 0.872912, 0.814182, 0.731226, 1.07152, 0.806347, 0.702863, 0.908523, 0.82393, 0.356533, 0.383934, 0.78022, 0.71445, 0.772313, 0.495821, 1.28642, 0.959929, 0.685538, 0.530272, 0.760474, 0.570368, 0.540381, 0.505417, 0.427399, 0.649383, 0.463193, 0.743862, 
  0.631688, 0.692825, 0.582046, 0.767175, 0.764304, 0.392543, 0.512606, 0.911018, 1.04997, 1.08885, 1.01616, 0.64055, 0.583577, 0.926698, 0.9328, 0.754671, 0.86653, 0.760629, 0.905493, 1.03356, 0.867909, 0.637168, 0.704238, 0.47889, 0.766581, 0.685948, 0.88291, 0.887213, 0.931342, 0.885784, 0.685095, 0.935744, 0.556326, 0.464223, 0.813005, 0.76138, 0.744739, 0.794082, 0.837969, 0.662187, 0.724786, 0.954338, 0.720786, 0.670377, 0.741422, 0.737085, 0.732783, 0.752208, 0.751736, 0.659634, 0.533846, 0.61332, 0.753093, 0.844565, 1.06557, 0.714032, 0.805481, 0.800727, 0.507938, 0.528386, 0.60826, 0.824829, 0.592924, 0.620779, 0.813448, 0.620467, 0.925092, 0.557423, 0.891326, 0.810319, 0.495186, 0.589774, 0.707295, 0.693671, 0.570914, 0.929713, 0.605693, 0.609161, 0.579558, 0.580992, 0.837728, 0.70846, 0.62237, 1.00087, 0.563213, 0.851363, 0.732288, 0.971594, 0.589282, 0.622392, 0.652967, 0.831602, 0.909272, 0.804902, 0.726377, 0.789941, 
  0.830507, 0.944159, 0.900132, 0.899659, 0.983724, 1.00022, 0.688205, 0.318808, 0.704956, 0.740031, 0.441928, 0.602014, 0.662449, 0.624455, 0.73581, 0.817134, 0.870449, 0.838259, 0.766508, 0.649753, 0.659824, 0.562119, 0.523724, 0.68393, 0.863718, 0.70302, 0.635735, 0.717662, 0.509303, 0.592967, 0.769535, 0.715179, 0.624373, 0.848143, 0.804511, 0.796242, 0.703661, 0.481616, 0.354532, 0.720448, 0.799012, 0.72806, 0.884431, 0.82271, 0.916628, 0.703216, 0.73249, 0.765636, 0.996129, 0.786243, 0.856536, 0.741603, 0.824117, 0.544727, 0.726312, 0.634395, 0.695852, 0.467409, 0.736142, 0.795937, 0.812718, 0.625328, 0.846483, 0.630374, 0.657274, 0.815562, 0.562662, 0.671762, 0.852428, 0.646438, 0.901165, 0.663267, 0.521745, 0.641151, 0.785685, 0.922868, 0.969019, 0.702972, 0.652477, 0.923163, 0.581313, 0.757542, 0.751554, 0.411999, 0.415443, 0.718797, 0.869338, 1.00807, 0.777571, 1.01454, 0.814756, 0.782758, 0.522661, 0.522016, 0.828245, 0.871868
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
