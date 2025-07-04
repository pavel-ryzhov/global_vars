
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
  0.919425, 0.581669, 0.693855, 0.946599, 0.982175, 0.920176, 1.04695, 1.0829, 0.725834, 0.872242, 0.520243, 0.407482, 0.695261, 0.679792, 0.912041, 0.882356, 0.867862, 0.730847, 0.783564, 0.678872, 1.06531, 0.691607, 0.992379, 0.711868, 0.602144, 0.615446, 0.893812, 1.04882, 0.967452, 0.703355, 0.521378, 0.850548, 0.929167, 0.970347, 0.766215, 0.601798, 0.766686, 0.832792, 0.927374, 0.878649, 0.384032, 0.716309, 0.572141, 0.681262, 0.837146, 0.560033, 0.755851, 0.682356, 0.979848, 0.788366, 0.556056, 0.744626, 0.548239, 0.472511, 0.388634, 0.643539, 0.778443, 0.873901, 0.729718, 0.83068, 0.902375, 0.543219, 0.762281, 0.951643, 0.600608, 0.276341, 0.706352, 0.546494, 0.616383, 0.581729, 0.532774, 0.755343, 0.682318, 0.515652, 1.0982, 1.11097, 0.403393, 0.539867, 0.693627, 0.811071, 0.814533, 0.825972, 0.478318, 0.607287, 0.80787, 0.562975, 0.577821, 0.912221, 1.10116, 1.0181, 0.884796, 0.783202, 0.584296, 0.588012, 0.634284, 0.447517, 
  0.61716, 0.677134, 0.644054, 0.841238, 0.555817, 0.540975, 0.556334, 0.514601, 0.640692, 0.590194, 0.538078, 0.809832, 0.586356, 0.609219, 0.861025, 0.725497, 0.730652, 0.616613, 0.377697, 0.715444, 0.543526, 0.690551, 0.418519, 0.749311, 0.732728, 0.580925, 1.1578, 0.84581, 0.699743, 0.718098, 0.53444, 0.946761, 0.707425, 0.548493, 0.744893, 0.741714, 0.617739, 0.647987, 1.02678, 1.025, 0.868097, 0.84234, 0.589157, 0.811282, 0.542069, 0.686635, 0.821792, 0.658864, 0.435602, 0.754577, 0.927562, 1.118, 0.686952, 0.920649, 0.81799, 0.864992, 0.756208, 0.799475, 0.567322, 0.782421, 0.826729, 0.894722, 0.930031, 0.795854, 0.636364, 0.493902, 0.736711, 0.66153, 0.871812, 1.10953, 1.01888, 0.837064, 0.703286, 0.736101, 0.681303, 0.748025, 0.947688, 0.632808, 0.469637, 0.556136, 0.771637, 0.537624, 0.861142, 1.29899, 1.18083, 0.638241, 1.03083, 0.695904, 0.826232, 0.600249, 0.962978, 0.592432, 0.745971, 0.510086, 0.73182, 0.948077, 
  0.629023, 0.539168, 0.984223, 0.812647, 0.786739, 0.750583, 0.49337, 0.895369, 0.780714, 0.6461, 0.706915, 0.880359, 0.629062, 0.89261, 0.773122, 0.664056, 0.702691, 0.737138, 0.554997, 0.751318, 0.693043, 0.727585, 0.723303, 0.956863, 0.61861, 0.742957, 0.635764, 0.87505, 0.538756, 0.495473, 0.564716, 0.700866, 0.907266, 1.04376, 1.05816, 0.527188, 0.750659, 0.441416, 0.725814, 0.740436, 0.47403, 0.656517, 0.734765, 0.991535, 0.898702, 0.803539, 0.608539, 0.925858, 0.530855, 0.723896, 0.700094, 0.441785, 0.907136, 0.810801, 0.915147, 0.871462, 0.432113, 0.748039, 0.70643, 0.996343, 0.853572, 0.787177, 0.604909, 0.649807, 0.680189, 0.663953, 0.72713, 0.850706, 0.796043, 0.616912, 1.07462, 0.961191, 0.503813, 0.916524, 1.01145, 1.00852, 0.998709, 0.842987, 0.617822, 0.413347, 0.382489, 0.659741, 0.74272, 0.788731, 0.73402, 0.520371, 0.684462, 1.0674, 0.900976, 0.599912, 0.430221, 0.386324, 0.688331, 0.931369, 0.747205, 1.05087, 
  0.940821, 0.907122, 0.753683, 0.661708, 0.305031, 0.54845, 0.662747, 0.610145, 0.910453, 0.835935, 0.843754, 0.754406, 0.881676, 0.898966, 0.865288, 0.625209, 0.270871, 0.301637, 0.580736, 0.35176, 0.464792, 0.928891, 0.932565, 1.00932, 0.807425, 0.754092, 0.791599, 0.575644, 0.729887, 0.615865, 0.622261, 0.710535, 0.452843, 0.782866, 0.845399, 0.64636, 0.932409, 0.650633, 0.61436, 0.825426, 0.976773, 0.817561, 0.845734, 0.585888, 0.731699, 0.571971, 0.637266, 0.793288, 0.97905, 0.933715, 0.741542, 0.811855, 0.727063, 0.604854, 0.668046, 0.651653, 0.492856, 0.748263, 0.605149, 0.636966, 0.581119, 0.632731, 0.941929, 0.59484, 0.849112, 0.694536, 1.0393, 0.861573, 0.498151, 0.818879, 0.822754, 0.7883, 0.758602, 1.01932, 0.914548, 0.760674, 0.669681, 0.772336, 1.02501, 0.981363, 0.768543, 0.530509, 0.790085, 0.682664, 0.730695, 0.514434, 0.606632, 0.698957, 0.806923, 0.513236, 0.624415, 0.691801, 0.913385, 0.861311, 0.756667, 0.47022, 
  0.80295, 0.42117, 0.471799, 0.45387, 0.522085, 0.837209, 0.916919, 0.811131, 1.00573, 0.675316, 0.53444, 0.418232, 0.833724, 0.390338, 0.721227, 0.563821, 0.701078, 1.03584, 1.05776, 0.849602, 0.90476, 0.6854, 0.59178, 0.616358, 0.796786, 0.463629, 0.840292, 0.847401, 0.840646, 0.985689, 0.639783, 0.704059, 0.714204, 0.538491, 0.499828, 0.419045, 0.548834, 0.739011, 0.850575, 0.840062, 0.662832, 0.521241, 0.809062, 0.895936, 0.937225, 0.824332, 0.552625, 0.793726, 0.756171, 0.773839, 0.446189, 0.885657, 0.840745, 0.75329, 0.981275, 1.1086, 0.903802, 0.888495, 0.603033, 0.83385, 0.53424, 0.7675, 0.768482, 0.724417, 0.887162, 0.917659, 0.785643, 0.625227, 0.693243, 0.798664, 0.862925, 0.588821, 0.532646, 0.663532, 0.706656, 0.67881, 0.794893, 0.696541, 0.732028, 0.778201, 0.818144, 0.647728, 0.549749, 0.719371, 0.725258, 0.520981, 0.690674, 0.822876, 0.391286, 0.883106, 0.690527, 0.605619, 0.510394, 0.83673, 0.54507, 0.792382, 
  0.677423, 0.601304, 0.649285, 0.838961, 0.781096, 0.83113, 1.04171, 0.34986, 0.775994, 0.880917, 1.10011, 1.00449, 0.83006, 0.983346, 0.767884, 0.664369, 0.807235, 0.857452, 0.583836, 0.584129, 0.506805, 0.77656, 0.813571, 0.830776, 0.739514, 0.456559, 0.764079, 0.960767, 0.980764, 0.743342, 0.481946, 0.549257, 0.715099, 0.457876, 0.855038, 0.89791, 0.808076, 0.869612, 0.975445, 0.554979, 0.49196, 0.818956, 0.432697, 0.79379, 0.394057, 0.509699, 0.713418, 0.568969, 0.546653, 0.555461, 0.741287, 0.471714, 1.08345, 1.02251, 0.792813, 0.845952, 0.901066, 0.716243, 0.785748, 0.973158, 0.570253, 0.847098, 0.636814, 0.451067, 0.974425, 0.938857, 0.847119, 0.72315, 0.628012, 0.931279, 0.766095, 0.515006, 0.835353, 0.799903, 0.300404, 0.389976, 0.470483, 0.812434, 0.546657, 0.6395, 0.862217, 1.01438, 0.843628, 0.474645, 1.10791, 0.919724, 0.42383, 0.661873, 0.423969, 0.798666, 0.731182, 0.825192, 0.684209, 0.95758, 0.550962, 0.687984, 
  0.755396, 0.401902, 0.598404, 0.763294, 1.06321, 1.20174, 0.924265, 1.04874, 0.707128, 0.621422, 0.737475, 0.656007, 0.345217, 0.653689, 0.450981, 0.757795, 0.659672, 0.598953, 0.985871, 0.938789, 0.861206, 1.06052, 0.876377, 0.8857, 0.808918, 0.519951, 0.588718, 0.587928, 0.738347, 0.841092, 0.667918, 0.70363, 1.07463, 0.64707, 0.725213, 0.884595, 0.698208, 0.896506, 0.651554, 0.819397, 0.551341, 0.952319, 0.593498, 0.853592, 0.644029, 0.691448, 0.653241, 0.90138, 0.575319, 0.64954, 0.592736, 0.641108, 0.837212, 0.753491, 0.636316, 0.706146, 0.873017, 0.641771, 0.785066, 0.827087, 0.75865, 0.64415, 0.805809, 0.513845, 0.925618, 0.644726, 0.637471, 0.600534, 0.562937, 0.930382, 0.840166, 0.674815, 0.775626, 0.67577, 0.37663, 0.361085, 0.686924, 1.03826, 0.575075, 0.726966, 0.970356, 0.72, 0.720445, 0.676547, 0.651563, 0.653516, 0.819099, 0.136173, 0.437105, 0.735626, 0.732215, 0.915593, 0.722785, 0.879434, 0.961149, 0.745855, 
  0.942715, 0.805593, 0.676724, 0.852671, 0.747824, 0.519523, 0.830951, 0.859878, 0.595866, 0.789937, 0.572693, 0.667293, 1.06196, 0.896073, 0.689862, 0.504323, 0.551277, 0.49272, 0.532941, 0.797306, 0.829445, 0.735454, 0.744178, 0.782468, 0.909778, 0.810294, 0.53982, 0.872282, 0.589644, 0.565907, 0.518903, 0.931649, 0.682186, 0.763341, 0.688951, 0.467533, 1.07005, 0.672534, 0.536758, 0.492879, 0.608486, 0.714766, 0.820513, 0.936617, 0.811024, 0.643125, 0.652811, 0.945316, 0.651791, 0.67013, 0.755888, 0.482713, 0.833483, 0.725083, 0.79286, 0.826871, 0.902174, 0.735627, 0.57418, 0.850022, 0.733449, 1.02155, 1.00291, 0.870259, 0.825035, 0.527158, 0.674068, 0.53438, 0.933414, 0.632889, 0.855235, 0.81427, 0.724131, 1.08943, 0.808014, 0.700153, 0.907568, 0.815602, 0.364668, 0.389183, 0.78022, 0.71445, 0.764869, 0.508139, 1.27022, 0.964012, 0.680081, 0.547209, 0.768841, 0.579516, 0.540381, 0.505417, 0.427399, 0.649383, 0.455055, 0.745763, 
  0.635158, 0.719557, 0.576869, 0.742801, 0.701898, 0.33367, 0.502727, 0.89486, 1.0871, 1.16713, 1.10323, 0.6408, 0.621951, 0.922322, 0.919484, 0.747245, 0.822915, 0.758771, 0.852732, 1.01367, 0.901738, 0.665698, 0.728095, 0.538027, 0.76539, 0.650046, 0.850017, 0.845478, 0.89361, 0.867767, 0.613506, 0.88699, 0.536665, 0.437708, 0.791018, 0.797146, 0.744009, 0.806387, 0.853283, 0.662771, 0.715112, 0.971438, 0.681508, 0.624464, 0.716646, 0.738662, 0.754475, 0.778207, 0.750432, 0.653269, 0.532574, 0.609749, 0.746589, 0.877486, 1.04203, 0.673687, 0.768593, 0.782442, 0.50045, 0.54952, 0.584963, 0.842381, 0.599765, 0.642537, 0.830382, 0.637913, 0.92007, 0.542366, 0.871246, 0.810283, 0.511486, 0.624114, 0.729276, 0.684139, 0.565634, 0.942055, 0.633681, 0.611197, 0.596673, 0.594523, 0.864351, 0.73654, 0.645205, 1.02168, 0.565831, 0.877071, 0.731485, 0.973266, 0.579869, 0.566626, 0.643639, 0.859829, 0.942803, 0.851529, 0.769974, 0.77803, 
  0.829933, 0.945381, 0.901105, 0.886212, 1.00412, 1.01655, 0.674022, 0.282515, 0.670483, 0.720811, 0.443055, 0.611095, 0.664727, 0.623645, 0.739088, 0.815329, 0.885749, 0.870025, 0.789862, 0.619108, 0.62937, 0.537733, 0.529237, 0.719307, 0.868705, 0.706099, 0.63809, 0.690815, 0.521152, 0.613411, 0.785149, 0.715705, 0.630504, 0.860038, 0.825282, 0.816714, 0.713325, 0.493124, 0.338056, 0.710408, 0.817337, 0.738556, 0.920924, 0.875633, 0.937404, 0.720556, 0.749983, 0.752036, 0.994284, 0.797205, 0.856073, 0.742794, 0.839135, 0.559324, 0.764879, 0.657093, 0.691727, 0.465743, 0.742904, 0.769954, 0.80465, 0.619473, 0.847071, 0.605731, 0.641105, 0.804957, 0.576134, 0.65404, 0.828759, 0.619453, 0.865068, 0.641075, 0.50495, 0.649629, 0.787164, 0.899724, 0.93698, 0.687969, 0.628809, 0.909711, 0.567511, 0.763053, 0.75384, 0.421943, 0.425799, 0.728673, 0.855089, 0.984124, 0.763638, 1.00497, 0.809646, 0.784589, 0.530428, 0.534564, 0.847816, 0.883302
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
