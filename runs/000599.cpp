
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
  0.917051, 0.565483, 0.685594, 0.945004, 0.979195, 0.911936, 1.0184, 1.04546, 0.697941, 0.861537, 0.535561, 0.432308, 0.674244, 0.656907, 0.919311, 0.870249, 0.837152, 0.701198, 0.777479, 0.67385, 1.06308, 0.69404, 1.01049, 0.732993, 0.583811, 0.589483, 0.894653, 1.02875, 0.961589, 0.715111, 0.538242, 0.873757, 0.94497, 0.974296, 0.778211, 0.620616, 0.744572, 0.833828, 0.913526, 0.868892, 0.394308, 0.725156, 0.554939, 0.670398, 0.804708, 0.530083, 0.740846, 0.664152, 0.96504, 0.815033, 0.568806, 0.774843, 0.588813, 0.480684, 0.3784, 0.646304, 0.765979, 0.861438, 0.732427, 0.813124, 0.895379, 0.563649, 0.795637, 0.976465, 0.643264, 0.299223, 0.733264, 0.537458, 0.620226, 0.588909, 0.53404, 0.734971, 0.730505, 0.525634, 1.10697, 1.09965, 0.430179, 0.574133, 0.70834, 0.833821, 0.832295, 0.832133, 0.454231, 0.614252, 0.843812, 0.604391, 0.543326, 0.835952, 1.04472, 1.03114, 0.885922, 0.789447, 0.570707, 0.600623, 0.642788, 0.446284, 
  0.52345, 0.667566, 0.734162, 0.904807, 0.600992, 0.576697, 0.588856, 0.54461, 0.681609, 0.642995, 0.620822, 0.784359, 0.551633, 0.613782, 0.875611, 0.748243, 0.734398, 0.619333, 0.351279, 0.665851, 0.526854, 0.737463, 0.447315, 0.699276, 0.671482, 0.55374, 1.13092, 0.819931, 0.689742, 0.669953, 0.458958, 0.875835, 0.703095, 0.540029, 0.697604, 0.667562, 0.695337, 0.695244, 1.02654, 1.05307, 0.905193, 0.851807, 0.630998, 0.880073, 0.609568, 0.726877, 0.8699, 0.717168, 0.444302, 0.736191, 0.859637, 1.08219, 0.67485, 0.90689, 0.860071, 0.872862, 0.73067, 0.761605, 0.555021, 0.758291, 0.839526, 0.915446, 0.899477, 0.77945, 0.660243, 0.514094, 0.765367, 0.672463, 0.849489, 1.05807, 0.955456, 0.745153, 0.673263, 0.777417, 0.671198, 0.768191, 0.982025, 0.632888, 0.465286, 0.521836, 0.736524, 0.531661, 0.84922, 1.19937, 1.18394, 0.678215, 1.0638, 0.718549, 0.861714, 0.608157, 0.964166, 0.618175, 0.789743, 0.551974, 0.742614, 0.830672, 
  0.631998, 0.549977, 0.97993, 0.798665, 0.774897, 0.750583, 0.488991, 0.884625, 0.819845, 0.680162, 0.7259, 0.868411, 0.638916, 0.897417, 0.773916, 0.685539, 0.686865, 0.726701, 0.534184, 0.756142, 0.73, 0.740771, 0.717079, 0.955116, 0.619647, 0.767175, 0.644734, 0.897651, 0.538848, 0.480669, 0.529512, 0.660774, 0.902804, 1.03989, 1.0512, 0.518838, 0.738411, 0.426912, 0.729531, 0.727076, 0.459823, 0.676562, 0.696017, 0.951681, 0.858674, 0.770688, 0.592773, 0.905498, 0.539711, 0.744255, 0.742172, 0.457258, 0.899034, 0.833991, 0.930786, 0.860752, 0.437588, 0.763607, 0.741872, 0.993534, 0.830483, 0.78178, 0.604093, 0.662417, 0.6774, 0.643147, 0.720919, 0.843716, 0.792889, 0.628766, 1.10739, 0.972706, 0.48167, 0.89811, 0.997941, 0.990133, 0.973353, 0.79733, 0.600352, 0.45167, 0.442975, 0.707742, 0.783444, 0.782172, 0.710854, 0.49698, 0.676626, 1.06422, 0.887181, 0.567886, 0.419611, 0.419251, 0.742992, 0.978568, 0.75544, 1.03121, 
  1.00886, 0.817743, 0.636786, 0.613842, 0.297686, 0.576474, 0.718275, 0.667189, 0.975692, 0.918982, 0.864008, 0.749753, 0.935837, 0.843238, 0.819689, 0.61508, 0.258202, 0.325204, 0.657897, 0.433424, 0.518189, 0.940123, 0.955806, 1.02339, 0.844096, 0.672858, 0.772433, 0.566757, 0.736047, 0.619333, 0.718013, 0.789288, 0.461947, 0.738675, 0.796151, 0.641709, 0.944538, 0.615811, 0.607674, 0.821444, 0.988959, 0.827345, 0.886311, 0.591075, 0.684898, 0.57558, 0.615937, 0.758588, 0.938098, 0.824726, 0.681859, 0.7999, 0.758691, 0.639567, 0.668552, 0.599879, 0.461966, 0.757474, 0.576032, 0.626613, 0.574814, 0.593274, 0.967421, 0.651935, 0.822579, 0.703849, 1.01761, 0.837639, 0.512279, 0.820714, 0.813647, 0.78286, 0.811815, 0.999799, 0.947099, 0.746599, 0.575003, 0.749845, 0.999137, 0.985927, 0.789978, 0.54245, 0.790623, 0.694106, 0.761002, 0.561058, 0.566956, 0.628614, 0.767018, 0.533682, 0.697042, 0.708307, 0.916836, 0.839085, 0.738623, 0.520582, 
  0.818907, 0.442419, 0.483307, 0.45291, 0.510995, 0.813054, 0.886937, 0.810561, 1.00447, 0.669252, 0.537654, 0.444739, 0.85607, 0.431132, 0.740415, 0.5729, 0.706515, 1.04969, 1.0674, 0.884451, 0.939609, 0.720249, 0.639022, 0.664265, 0.81502, 0.473776, 0.838117, 0.845226, 0.855277, 1.00931, 0.652107, 0.730506, 0.73934, 0.565728, 0.540905, 0.474926, 0.52218, 0.720401, 0.848771, 0.821451, 0.644221, 0.50671, 0.79555, 0.884648, 0.924917, 0.818326, 0.551718, 0.796534, 0.766329, 0.791162, 0.471915, 0.894577, 0.837059, 0.749604, 0.977589, 1.10492, 0.900117, 0.897415, 0.612803, 0.846561, 0.554801, 0.791775, 0.792757, 0.748692, 0.907235, 0.937732, 0.780506, 0.6453, 0.713316, 0.822939, 0.8872, 0.617999, 0.539048, 0.680381, 0.725246, 0.6974, 0.813483, 0.715131, 0.723306, 0.796791, 0.836733, 0.666318, 0.566891, 0.74544, 0.723073, 0.519956, 0.696265, 0.832336, 0.40237, 0.89419, 0.686906, 0.60738, 0.508198, 0.830666, 0.546099, 0.823511, 
  0.705943, 0.626796, 0.657636, 0.837604, 0.794315, 0.82935, 1.03347, 0.381958, 0.796434, 0.868226, 1.07784, 1.02043, 0.843872, 0.969604, 0.691827, 0.601909, 0.835573, 0.891185, 0.624689, 0.658199, 0.55108, 0.776586, 0.814128, 0.855486, 0.77147, 0.4339, 0.690997, 0.92669, 0.984859, 0.77803, 0.480764, 0.568495, 0.682363, 0.451046, 0.92922, 0.905433, 0.816606, 0.859029, 0.941856, 0.565235, 0.53145, 0.843078, 0.457363, 0.80014, 0.396472, 0.506266, 0.748954, 0.60663, 0.601124, 0.610793, 0.755081, 0.472417, 1.07368, 0.972597, 0.716755, 0.819634, 0.871707, 0.646079, 0.779441, 0.982071, 0.601569, 0.834881, 0.644879, 0.398374, 0.955965, 0.882145, 0.787553, 0.681396, 0.570437, 0.896959, 0.774755, 0.554465, 0.824953, 0.762963, 0.316205, 0.370228, 0.475359, 0.797593, 0.525507, 0.623448, 0.833418, 1.00528, 0.842926, 0.528506, 1.10029, 0.917082, 0.448771, 0.682763, 0.426654, 0.820349, 0.711122, 0.81486, 0.673578, 0.973074, 0.60156, 0.718266, 
  0.779878, 0.413413, 0.575771, 0.736949, 1.02181, 1.15482, 0.889036, 0.997235, 0.693973, 0.648719, 0.763443, 0.649875, 0.368951, 0.663229, 0.479928, 0.78955, 0.668586, 0.623183, 0.985898, 0.918234, 0.821771, 1.04317, 0.873066, 0.903431, 0.806795, 0.556138, 0.627935, 0.606704, 0.735425, 0.870363, 0.69991, 0.685279, 1.06176, 0.631609, 0.704069, 0.866128, 0.707756, 0.899465, 0.644762, 0.824281, 0.565109, 0.995568, 0.637062, 0.875321, 0.653316, 0.722742, 0.666076, 0.891232, 0.58105, 0.614503, 0.602199, 0.650083, 0.809863, 0.789911, 0.700221, 0.71969, 0.892409, 0.657133, 0.755327, 0.825952, 0.738105, 0.656758, 0.835124, 0.530003, 0.870458, 0.634765, 0.661673, 0.590397, 0.50136, 0.88779, 0.793803, 0.694625, 0.738138, 0.690347, 0.41631, 0.401943, 0.664367, 1.01569, 0.578273, 0.686307, 0.934976, 0.709169, 0.735462, 0.686751, 0.648281, 0.625462, 0.841717, 0.195588, 0.462233, 0.65184, 0.696824, 0.902316, 0.728996, 0.880044, 0.96662, 0.750421, 
  0.89025, 0.816462, 0.722637, 0.857986, 0.765689, 0.533692, 0.831422, 0.826522, 0.51682, 0.685989, 0.488744, 0.621724, 0.994804, 0.901782, 0.731248, 0.507396, 0.577223, 0.50304, 0.462978, 0.698735, 0.727546, 0.660515, 0.686774, 0.749689, 0.844853, 0.839442, 0.554966, 0.863266, 0.582739, 0.529519, 0.438533, 0.858807, 0.637391, 0.767826, 0.701445, 0.50386, 1.01282, 0.693948, 0.556782, 0.48556, 0.566408, 0.678936, 0.782107, 0.950957, 0.852943, 0.653868, 0.669084, 0.982848, 0.592497, 0.715596, 0.748332, 0.433914, 0.789531, 0.715818, 0.824368, 0.862721, 0.925904, 0.762222, 0.601755, 0.870103, 0.676201, 1.02168, 0.939979, 0.802269, 0.803575, 0.536867, 0.730403, 0.592182, 0.968032, 0.675538, 0.863707, 0.819844, 0.656411, 1.07046, 0.727297, 0.687199, 0.933379, 0.85973, 0.409252, 0.422683, 0.807752, 0.732407, 0.767831, 0.514138, 1.21568, 0.884028, 0.642869, 0.553184, 0.799314, 0.601535, 0.551987, 0.514833, 0.422691, 0.637142, 0.445776, 0.75082, 
  0.643156, 0.758962, 0.595552, 0.741411, 0.724138, 0.353223, 0.506127, 0.873906, 1.00826, 1.08411, 1.0441, 0.66857, 0.618735, 0.945721, 0.92945, 0.733964, 0.835846, 0.739797, 0.883678, 0.969701, 0.862047, 0.624962, 0.679129, 0.515068, 0.843176, 0.709737, 0.896085, 0.875597, 0.909808, 0.8948, 0.678355, 0.950518, 0.591298, 0.48849, 0.789651, 0.800043, 0.765989, 0.81539, 0.853398, 0.667624, 0.691381, 0.914358, 0.692162, 0.639513, 0.738422, 0.735515, 0.708509, 0.719717, 0.765239, 0.652595, 0.54163, 0.637696, 0.775014, 0.850297, 1.03388, 0.726419, 0.814093, 0.821905, 0.511759, 0.55076, 0.609056, 0.803949, 0.562024, 0.609745, 0.827867, 0.617475, 0.88631, 0.518363, 0.905487, 0.814163, 0.526631, 0.614307, 0.746136, 0.692692, 0.550401, 0.924025, 0.639906, 0.599473, 0.582861, 0.551321, 0.812723, 0.690232, 0.630475, 1.04155, 0.564202, 0.871467, 0.750818, 0.983814, 0.588471, 0.598288, 0.643702, 0.818154, 0.899761, 0.809399, 0.754825, 0.819486, 
  0.830507, 0.94118, 0.878626, 0.910823, 0.98029, 1.00018, 0.688482, 0.317933, 0.704956, 0.740031, 0.441928, 0.609826, 0.666938, 0.62719, 0.738606, 0.825168, 0.85964, 0.820674, 0.754516, 0.641413, 0.659824, 0.562119, 0.527196, 0.701291, 0.849648, 0.703752, 0.649154, 0.719426, 0.505665, 0.582912, 0.755607, 0.70674, 0.625024, 0.852403, 0.811549, 0.800886, 0.701794, 0.489973, 0.377162, 0.715367, 0.803148, 0.730483, 0.867491, 0.806193, 0.926084, 0.710055, 0.736204, 0.757631, 1.00661, 0.795145, 0.87837, 0.747123, 0.843464, 0.560641, 0.709372, 0.636819, 0.699566, 0.471123, 0.733563, 0.782991, 0.830068, 0.636811, 0.858612, 0.640651, 0.681414, 0.830703, 0.566392, 0.681086, 0.866485, 0.656155, 0.893374, 0.663069, 0.548061, 0.652204, 0.791332, 0.914626, 0.962946, 0.708184, 0.657689, 0.926197, 0.572625, 0.732612, 0.728899, 0.393712, 0.448864, 0.741359, 0.868852, 1.00498, 0.76032, 0.992932, 0.792717, 0.757278, 0.496499, 0.499425, 0.805655, 0.858744
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
