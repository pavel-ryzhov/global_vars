
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
  0.933255, 0.62895, 0.714514, 0.940492, 0.955918, 0.834384, 1.00566, 1.03272, 0.688591, 0.893736, 0.618347, 0.448512, 0.732803, 0.652593, 0.906333, 0.857511, 0.824414, 0.68846, 0.764741, 0.661113, 1.05034, 0.681302, 1.01081, 0.785276, 0.600783, 0.576745, 0.881915, 1.01601, 0.948851, 0.702373, 0.525504, 0.86102, 0.932232, 0.961559, 0.765473, 0.642627, 0.73229, 0.852654, 0.932192, 0.887558, 0.412973, 0.743822, 0.564346, 0.642767, 0.777077, 0.520971, 0.759512, 0.651311, 0.951913, 0.827218, 0.58079, 0.786828, 0.611874, 0.497667, 0.381125, 0.611992, 0.731668, 0.827126, 0.737111, 0.800101, 0.91978, 0.547961, 0.780374, 0.961203, 0.642438, 0.28656, 0.718002, 0.522195, 0.604963, 0.573646, 0.520271, 0.756013, 0.798661, 0.526509, 1.08704, 1.08315, 0.427352, 0.554139, 0.693078, 0.818559, 0.815795, 0.815561, 0.455985, 0.67649, 0.860016, 0.671058, 0.566768, 0.820324, 1.00817, 0.945358, 0.873223, 0.77163, 0.570754, 0.63766, 0.728053, 0.462488, 
  0.618121, 0.711141, 0.692277, 0.847646, 0.537136, 0.536603, 0.54476, 0.508301, 0.659218, 0.607922, 0.553863, 0.822686, 0.596014, 0.602667, 0.865504, 0.723002, 0.696946, 0.575726, 0.340653, 0.690745, 0.555501, 0.710432, 0.413611, 0.721876, 0.730162, 0.596177, 1.16031, 0.841738, 0.679409, 0.66839, 0.507283, 0.928411, 0.715928, 0.54333, 0.722451, 0.721984, 0.635875, 0.634391, 0.99607, 1.00126, 0.836738, 0.805323, 0.583667, 0.795182, 0.530669, 0.676925, 0.814816, 0.650359, 0.447428, 0.749438, 0.904304, 1.12186, 0.694758, 0.937487, 0.841685, 0.884824, 0.782179, 0.815214, 0.569498, 0.787995, 0.824596, 0.894259, 0.924688, 0.7998, 0.632864, 0.493299, 0.732106, 0.663615, 0.858741, 1.08857, 1.01681, 0.860043, 0.687706, 0.731758, 0.665103, 0.729595, 0.93003, 0.623543, 0.448411, 0.528584, 0.74732, 0.52872, 0.864186, 1.33935, 1.20417, 0.679016, 1.05866, 0.730535, 0.871063, 0.644968, 0.987258, 0.607052, 0.765804, 0.531352, 0.765567, 0.995002, 
  0.618751, 0.533259, 1.00207, 0.819837, 0.780448, 0.750127, 0.484982, 0.892424, 0.826914, 0.687887, 0.718245, 0.832704, 0.636366, 0.895528, 0.769858, 0.672299, 0.689678, 0.715973, 0.531553, 0.73912, 0.709272, 0.721943, 0.709916, 0.936359, 0.612265, 0.720541, 0.605657, 0.866479, 0.502147, 0.456999, 0.501793, 0.630074, 0.868834, 1.01048, 1.00189, 0.486447, 0.755222, 0.391977, 0.717306, 0.729355, 0.436656, 0.647292, 0.69293, 0.937913, 0.849856, 0.750342, 0.554415, 0.910875, 0.536138, 0.702459, 0.689977, 0.424758, 0.874693, 0.792087, 0.894401, 0.85469, 0.417772, 0.735056, 0.708737, 0.999261, 0.843991, 0.774665, 0.586546, 0.631444, 0.661827, 0.64559, 0.712701, 0.841923, 0.811543, 0.634666, 1.09298, 0.963276, 0.485215, 0.916824, 1.00006, 0.996561, 0.989077, 0.819126, 0.61573, 0.441413, 0.421045, 0.684418, 0.757498, 0.766249, 0.710882, 0.506457, 0.702765, 1.08851, 0.905298, 0.579427, 0.424018, 0.42777, 0.734088, 0.966313, 0.754176, 1.01264, 
  0.942041, 0.868701, 0.684737, 0.617493, 0.298649, 0.566186, 0.700698, 0.658441, 0.958055, 0.918656, 0.907397, 0.783669, 0.856872, 0.903817, 0.82828, 0.608509, 0.259739, 0.332948, 0.661643, 0.425497, 0.503375, 0.948503, 0.958184, 1.0794, 0.816284, 0.711916, 0.766409, 0.548718, 0.728028, 0.668776, 0.704172, 0.78692, 0.437171, 0.712557, 0.753594, 0.678727, 0.926577, 0.629595, 0.58008, 0.791278, 0.974776, 0.85822, 0.879585, 0.595021, 0.693738, 0.552036, 0.59043, 0.793569, 0.942878, 0.820842, 0.670999, 0.79156, 0.747423, 0.646086, 0.656814, 0.603933, 0.454987, 0.71935, 0.53507, 0.630856, 0.584095, 0.589676, 0.958471, 0.621462, 0.821641, 0.697233, 1.03611, 0.834671, 0.472271, 0.800857, 0.787516, 0.730895, 0.783782, 1.01727, 0.940477, 0.75965, 0.584618, 0.713386, 1.00916, 0.98873, 0.784131, 0.542752, 0.768762, 0.604015, 0.710329, 0.522708, 0.558692, 0.61385, 0.714894, 0.446204, 0.620823, 0.66984, 0.88595, 0.818321, 0.67828, 0.408027, 
  0.819675, 0.426732, 0.479575, 0.45291, 0.510995, 0.813054, 0.886937, 0.810561, 1.00447, 0.669252, 0.537654, 0.442235, 0.85719, 0.417478, 0.729221, 0.56295, 0.696565, 1.03974, 1.05745, 0.874501, 0.929659, 0.710299, 0.629072, 0.645658, 0.798368, 0.461809, 0.837598, 0.844708, 0.854759, 1.00879, 0.651588, 0.729987, 0.738821, 0.565209, 0.540386, 0.45589, 0.546063, 0.732526, 0.860897, 0.833577, 0.656347, 0.518836, 0.807676, 0.896774, 0.937043, 0.830452, 0.563844, 0.80866, 0.766005, 0.788363, 0.469116, 0.891777, 0.83426, 0.746805, 0.97479, 1.10212, 0.897318, 0.894615, 0.610004, 0.843762, 0.557244, 0.794218, 0.7952, 0.751135, 0.909678, 0.940175, 0.782949, 0.647743, 0.715759, 0.825382, 0.889643, 0.611826, 0.545358, 0.68669, 0.731556, 0.70371, 0.819793, 0.721441, 0.729616, 0.803101, 0.843043, 0.672628, 0.5732, 0.733902, 0.723073, 0.519956, 0.696265, 0.832336, 0.40237, 0.89419, 0.686906, 0.60738, 0.508198, 0.830666, 0.546099, 0.8142, 
  0.694365, 0.599438, 0.633272, 0.825235, 0.767868, 0.810091, 1.01763, 0.374998, 0.805109, 0.877798, 1.09366, 1.01536, 0.857576, 0.968761, 0.67284, 0.583189, 0.803907, 0.875976, 0.593342, 0.635982, 0.544452, 0.789081, 0.84721, 0.857253, 0.750717, 0.393772, 0.670514, 0.926355, 1.02692, 0.770309, 0.472263, 0.559959, 0.716176, 0.491191, 0.978218, 0.902805, 0.791189, 0.855525, 0.988389, 0.593543, 0.54869, 0.810006, 0.43467, 0.814628, 0.408376, 0.517961, 0.755438, 0.578975, 0.597648, 0.640342, 0.788779, 0.479504, 1.09816, 0.963497, 0.742239, 0.836105, 0.864673, 0.672414, 0.793596, 0.948953, 0.605046, 0.873442, 0.646451, 0.434695, 1.00452, 0.911843, 0.776351, 0.691319, 0.597471, 0.90234, 0.759894, 0.54748, 0.827398, 0.763661, 0.289612, 0.352762, 0.487819, 0.81305, 0.495301, 0.616097, 0.82501, 0.985489, 0.827849, 0.529736, 1.12156, 0.900108, 0.388894, 0.644102, 0.42293, 0.840346, 0.703325, 0.823524, 0.682242, 0.968774, 0.594968, 0.717687, 
  0.779878, 0.416997, 0.595317, 0.762845, 1.04583, 1.18936, 0.921392, 1.01866, 0.706065, 0.651504, 0.769448, 0.65202, 0.374568, 0.670394, 0.493215, 0.814736, 0.699465, 0.636967, 1.00548, 0.93744, 0.830131, 1.05641, 0.895109, 0.911559, 0.827098, 0.560326, 0.656865, 0.638136, 0.742792, 0.860369, 0.697267, 0.699769, 1.07277, 0.628109, 0.728194, 0.884214, 0.734608, 0.913524, 0.665428, 0.834844, 0.553518, 0.982874, 0.648016, 0.905792, 0.675006, 0.722976, 0.667489, 0.91896, 0.616813, 0.625538, 0.604086, 0.655535, 0.79079, 0.777357, 0.714405, 0.752324, 0.916063, 0.667906, 0.772863, 0.837929, 0.750174, 0.653858, 0.824528, 0.536161, 0.851158, 0.624215, 0.666974, 0.621423, 0.540059, 0.90385, 0.811361, 0.69611, 0.702569, 0.67733, 0.415384, 0.414011, 0.660557, 0.999397, 0.57471, 0.701368, 0.956233, 0.724277, 0.745318, 0.677467, 0.642163, 0.615651, 0.861064, 0.233867, 0.500805, 0.675818, 0.702289, 0.919867, 0.736851, 0.878872, 0.968502, 0.750421, 
  0.88852, 0.799795, 0.6997, 0.873361, 0.765689, 0.533692, 0.831422, 0.826522, 0.51682, 0.685989, 0.495999, 0.619444, 1.0153, 0.882733, 0.731055, 0.532493, 0.577223, 0.50304, 0.462978, 0.698735, 0.727546, 0.66436, 0.684957, 0.734689, 0.857482, 0.823267, 0.571431, 0.876625, 0.582739, 0.529519, 0.438533, 0.858807, 0.641821, 0.766425, 0.708944, 0.492275, 1.01583, 0.69449, 0.556603, 0.477747, 0.558595, 0.671124, 0.774295, 0.955549, 0.859816, 0.671333, 0.691107, 0.971128, 0.585571, 0.688583, 0.73477, 0.399983, 0.754188, 0.694749, 0.813757, 0.849344, 0.912876, 0.75183, 0.601584, 0.854654, 0.677364, 1.01049, 0.93169, 0.799773, 0.816459, 0.548125, 0.737483, 0.601122, 0.977171, 0.673227, 0.862606, 0.792101, 0.679229, 1.07315, 0.741324, 0.708859, 0.955039, 0.867044, 0.414089, 0.422683, 0.807752, 0.732407, 0.778052, 0.485643, 1.2424, 0.909357, 0.661805, 0.560669, 0.793441, 0.601194, 0.551987, 0.514833, 0.436815, 0.656916, 0.455997, 0.732268, 
  0.624891, 0.674697, 0.561437, 0.753736, 0.773796, 0.42839, 0.543822, 0.909011, 1.02981, 1.06723, 0.963449, 0.631352, 0.561717, 0.934588, 0.941732, 0.740646, 0.844088, 0.76502, 0.902914, 0.995892, 0.889283, 0.653299, 0.674335, 0.439291, 0.77692, 0.717971, 0.875934, 0.852124, 0.909245, 0.88882, 0.679988, 0.936767, 0.58102, 0.499625, 0.782348, 0.722414, 0.774432, 0.826993, 0.843457, 0.653168, 0.729584, 0.95491, 0.694805, 0.651928, 0.763835, 0.778609, 0.744717, 0.73462, 0.733738, 0.653635, 0.539924, 0.623116, 0.770679, 0.855238, 1.02114, 0.698626, 0.810294, 0.842907, 0.5116, 0.543002, 0.567326, 0.827166, 0.596634, 0.625017, 0.839006, 0.635325, 0.908547, 0.514757, 0.880122, 0.815758, 0.521589, 0.580923, 0.718652, 0.706727, 0.584822, 0.925629, 0.635896, 0.650428, 0.604854, 0.571036, 0.832942, 0.714837, 0.629382, 0.975145, 0.563959, 0.84364, 0.739936, 0.980933, 0.618188, 0.672686, 0.685439, 0.835315, 0.910207, 0.78911, 0.680114, 0.785396, 
  0.830507, 0.94029, 0.887102, 0.906446, 1.01367, 1.03812, 0.712691, 0.318361, 0.704956, 0.740031, 0.441928, 0.602014, 0.661591, 0.621442, 0.761964, 0.854662, 0.907977, 0.866154, 0.77924, 0.640973, 0.660438, 0.564373, 0.526798, 0.688643, 0.879919, 0.737474, 0.673365, 0.739104, 0.525106, 0.595654, 0.77161, 0.708285, 0.645224, 0.871513, 0.818507, 0.812618, 0.737911, 0.518325, 0.359577, 0.747677, 0.842122, 0.757596, 0.920012, 0.854448, 0.954584, 0.728395, 0.758232, 0.781542, 1.02187, 0.803582, 0.867257, 0.775084, 0.873179, 0.589027, 0.759639, 0.656042, 0.712171, 0.473582, 0.759938, 0.803486, 0.820385, 0.634264, 0.855419, 0.63931, 0.670412, 0.817634, 0.578776, 0.661231, 0.841897, 0.631706, 0.887326, 0.661332, 0.521431, 0.650087, 0.794621, 0.926066, 0.95982, 0.688445, 0.665056, 0.908431, 0.56673, 0.748911, 0.749769, 0.411999, 0.421452, 0.732046, 0.86516, 0.994877, 0.762839, 0.999809, 0.81473, 0.772788, 0.51909, 0.522016, 0.828245, 0.871868
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
