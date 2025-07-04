
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
  0.91525, 0.560266, 0.685271, 0.946531, 0.983392, 0.914247, 1.00525, 1.03231, 0.684622, 0.842931, 0.517485, 0.430508, 0.671479, 0.654539, 0.908433, 0.859611, 0.83998, 0.697796, 0.772281, 0.664107, 1.04993, 0.680887, 0.998745, 0.719936, 0.575754, 0.581594, 0.886046, 1.02158, 0.948436, 0.701958, 0.531431, 0.867665, 0.934332, 0.968204, 0.765777, 0.596618, 0.737912, 0.815462, 0.912411, 0.870415, 0.388111, 0.710339, 0.552221, 0.689389, 0.823699, 0.544744, 0.734232, 0.650123, 0.954049, 0.787762, 0.564134, 0.763236, 0.571553, 0.459619, 0.361826, 0.648931, 0.761064, 0.855085, 0.717602, 0.807145, 0.897794, 0.54264, 0.783213, 0.96907, 0.625063, 0.277723, 0.708628, 0.532688, 0.612889, 0.564932, 0.520339, 0.720018, 0.710381, 0.516085, 1.09265, 1.08443, 0.402518, 0.545103, 0.677244, 0.804881, 0.807985, 0.812057, 0.441402, 0.587961, 0.838319, 0.574964, 0.539589, 0.8484, 1.05141, 1.02937, 0.880357, 0.767988, 0.554576, 0.570154, 0.616738, 0.4442, 
  0.629142, 0.689256, 0.621476, 0.815639, 0.539668, 0.534213, 0.517949, 0.493563, 0.617321, 0.567449, 0.546786, 0.836335, 0.593686, 0.576845, 0.801863, 0.710709, 0.738213, 0.620831, 0.340556, 0.700638, 0.529419, 0.707602, 0.435052, 0.731949, 0.716572, 0.555252, 1.13598, 0.874677, 0.761699, 0.72399, 0.50202, 0.958142, 0.747806, 0.57786, 0.764024, 0.742061, 0.667997, 0.635917, 0.998346, 1.02632, 0.883563, 0.80967, 0.569172, 0.847805, 0.577391, 0.698083, 0.823281, 0.654466, 0.474842, 0.735847, 0.90908, 1.12879, 0.710104, 0.945912, 0.853684, 0.883497, 0.759245, 0.788446, 0.564308, 0.769399, 0.815258, 0.875568, 0.873461, 0.777301, 0.648127, 0.501403, 0.709385, 0.631269, 0.842427, 1.04089, 0.9703, 0.802642, 0.705511, 0.776639, 0.685155, 0.779726, 0.994878, 0.666364, 0.496038, 0.565339, 0.764541, 0.540171, 0.897633, 1.31151, 1.16789, 0.659676, 1.03678, 0.710299, 0.854239, 0.613319, 0.947661, 0.582087, 0.737751, 0.509653, 0.752603, 0.985098, 
  0.608772, 0.494603, 0.944545, 0.789059, 0.771205, 0.750583, 0.488991, 0.876713, 0.774948, 0.641798, 0.719879, 0.887942, 0.597492, 0.874871, 0.761895, 0.643683, 0.674734, 0.726701, 0.534184, 0.74607, 0.702433, 0.753997, 0.726967, 0.966926, 0.602923, 0.743467, 0.6287, 0.87039, 0.529354, 0.478257, 0.545267, 0.704848, 0.931255, 1.04694, 1.03938, 0.516018, 0.73788, 0.418986, 0.711359, 0.732289, 0.471632, 0.655943, 0.72892, 0.986505, 0.869459, 0.773203, 0.578926, 0.905314, 0.524068, 0.722222, 0.708843, 0.445883, 0.890137, 0.820907, 0.910754, 0.83562, 0.409305, 0.735159, 0.689589, 0.980748, 0.844399, 0.775193, 0.607133, 0.645075, 0.668396, 0.648428, 0.710293, 0.819083, 0.751215, 0.609547, 1.0631, 0.957547, 0.499131, 0.898304, 0.999572, 1.00467, 0.98654, 0.808274, 0.575095, 0.407489, 0.39663, 0.690827, 0.747573, 0.785608, 0.73385, 0.500347, 0.669175, 1.0624, 0.88656, 0.577064, 0.416223, 0.378046, 0.685286, 0.941608, 0.729474, 1.03139, 
  0.928828, 0.915859, 0.773099, 0.659706, 0.305224, 0.546813, 0.653026, 0.593447, 0.915117, 0.867626, 0.845697, 0.755506, 0.888591, 0.930131, 0.903213, 0.618982, 0.271881, 0.31495, 0.584803, 0.344104, 0.468354, 0.96797, 0.941404, 1.03496, 0.799781, 0.764527, 0.7982, 0.571406, 0.725464, 0.645925, 0.656047, 0.713845, 0.437376, 0.781152, 0.849071, 0.646166, 0.903644, 0.662285, 0.609631, 0.794295, 0.957208, 0.863394, 0.867022, 0.582764, 0.700735, 0.535487, 0.62765, 0.784715, 0.94776, 0.906739, 0.692672, 0.789741, 0.707937, 0.617745, 0.666107, 0.636512, 0.451159, 0.737317, 0.605411, 0.616265, 0.588356, 0.646069, 0.955087, 0.58534, 0.842998, 0.710327, 1.05979, 0.851764, 0.501914, 0.83191, 0.82957, 0.740428, 0.781634, 1.06333, 0.929087, 0.744052, 0.647446, 0.762222, 1.03367, 1.01315, 0.803788, 0.561067, 0.774388, 0.621009, 0.750045, 0.556653, 0.624136, 0.674226, 0.780831, 0.504868, 0.625958, 0.713519, 0.937852, 0.874201, 0.731085, 0.415789, 
  0.815765, 0.433966, 0.500506, 0.47384, 0.552517, 0.841535, 0.921443, 0.816333, 0.998771, 0.670283, 0.537049, 0.413038, 0.870112, 0.429878, 0.739854, 0.565949, 0.67431, 1.01454, 1.06376, 0.826708, 0.892709, 0.667669, 0.576364, 0.619421, 0.822929, 0.478006, 0.821679, 0.804828, 0.817118, 0.958111, 0.645218, 0.705978, 0.714906, 0.535107, 0.484022, 0.421188, 0.542716, 0.722631, 0.846704, 0.821088, 0.639842, 0.51515, 0.817499, 0.887129, 0.940046, 0.832993, 0.54896, 0.78575, 0.764842, 0.786885, 0.449499, 0.887728, 0.84824, 0.760785, 0.9902, 1.1025, 0.926642, 0.927631, 0.639169, 0.872982, 0.594015, 0.819444, 0.828696, 0.805602, 0.964146, 0.994643, 0.835508, 0.683127, 0.739796, 0.854439, 0.92121, 0.655768, 0.519755, 0.654669, 0.710031, 0.682185, 0.798268, 0.704567, 0.72437, 0.779767, 0.810747, 0.629708, 0.529339, 0.757182, 0.725357, 0.519638, 0.696265, 0.832336, 0.40237, 0.936051, 0.735743, 0.616976, 0.521038, 0.830585, 0.540702, 0.812935, 
  0.674673, 0.594275, 0.633296, 0.828219, 0.766353, 0.830897, 1.04209, 0.335551, 0.766929, 0.885129, 1.10028, 0.989316, 0.811935, 1.01705, 0.753554, 0.682513, 0.839103, 0.909118, 0.611216, 0.577491, 0.520786, 0.720945, 0.804397, 0.874194, 0.728647, 0.481776, 0.756437, 0.944364, 0.990054, 0.751939, 0.486975, 0.541878, 0.709904, 0.461426, 0.851331, 0.949908, 0.75959, 0.885602, 0.990788, 0.548603, 0.502253, 0.813446, 0.432809, 0.791962, 0.403521, 0.551102, 0.745777, 0.587932, 0.499524, 0.614657, 0.808509, 0.465415, 1.10104, 1.02021, 0.775218, 0.855727, 0.928124, 0.730671, 0.775017, 0.999477, 0.521635, 0.843883, 0.675455, 0.40482, 0.957578, 0.903115, 0.832502, 0.709852, 0.610625, 0.920259, 0.752696, 0.551711, 0.839946, 0.749043, 0.302177, 0.364749, 0.439671, 0.831154, 0.543932, 0.626897, 0.845403, 1.00193, 0.854972, 0.499849, 1.0665, 0.883017, 0.399579, 0.648251, 0.415795, 0.785421, 0.745055, 0.83853, 0.696853, 0.960714, 0.551469, 0.714041, 
  0.755396, 0.402983, 0.601793, 0.776569, 1.0838, 1.23111, 0.949893, 1.07228, 0.740311, 0.641323, 0.749603, 0.657159, 0.352604, 0.648444, 0.468679, 0.789783, 0.696442, 0.624589, 1.00342, 0.97253, 0.869586, 1.07574, 0.895641, 0.901788, 0.823931, 0.530496, 0.623927, 0.625467, 0.756324, 0.858529, 0.680619, 0.710284, 1.08795, 0.658265, 0.759402, 0.903079, 0.720709, 0.897902, 0.682811, 0.844299, 0.557522, 0.962936, 0.632313, 0.888344, 0.655014, 0.706226, 0.675528, 0.925728, 0.591073, 0.642032, 0.606334, 0.647756, 0.808876, 0.738464, 0.672817, 0.740187, 0.892786, 0.648257, 0.78757, 0.832557, 0.77178, 0.641989, 0.80023, 0.515444, 0.891096, 0.629563, 0.631771, 0.640964, 0.593711, 0.934966, 0.83191, 0.708733, 0.761744, 0.670283, 0.360517, 0.372705, 0.682047, 1.01184, 0.545837, 0.714369, 0.977301, 0.72911, 0.748731, 0.702575, 0.671811, 0.627449, 0.817179, 0.153767, 0.444307, 0.723506, 0.706313, 0.909356, 0.719791, 0.883096, 0.985107, 0.751323, 
  0.960327, 0.828171, 0.697481, 0.852671, 0.747824, 0.519523, 0.830951, 0.859878, 0.595866, 0.780028, 0.543024, 0.638727, 1.08213, 0.892016, 0.695933, 0.504323, 0.550588, 0.488877, 0.532941, 0.795918, 0.815971, 0.706627, 0.730627, 0.751087, 0.909764, 0.805453, 0.540239, 0.868506, 0.58906, 0.564542, 0.513, 0.907231, 0.65473, 0.760092, 0.703133, 0.453735, 1.06497, 0.669218, 0.540784, 0.4944, 0.609832, 0.707745, 0.79606, 0.918707, 0.830887, 0.664865, 0.671935, 0.94363, 0.644959, 0.675843, 0.76298, 0.482068, 0.836323, 0.715871, 0.792763, 0.842098, 0.918169, 0.753768, 0.593304, 0.847253, 0.719737, 1.03577, 1.00142, 0.885553, 0.829678, 0.520297, 0.689284, 0.561051, 0.957912, 0.651825, 0.861911, 0.800702, 0.708518, 1.08883, 0.817546, 0.697035, 0.906857, 0.831549, 0.383909, 0.397769, 0.781809, 0.71445, 0.764174, 0.490778, 1.26762, 0.961721, 0.667185, 0.533679, 0.770299, 0.583065, 0.542571, 0.505417, 0.427399, 0.649383, 0.455055, 0.738818, 
  0.639482, 0.740039, 0.602742, 0.762506, 0.716737, 0.335862, 0.550892, 0.956127, 1.10116, 1.1634, 1.09826, 0.639451, 0.642258, 0.922438, 0.921822, 0.744163, 0.824177, 0.747313, 0.885849, 1.03011, 0.89099, 0.656441, 0.717082, 0.515804, 0.800737, 0.642844, 0.854309, 0.834308, 0.8675, 0.867527, 0.621401, 0.88758, 0.505264, 0.413105, 0.789024, 0.782277, 0.800998, 0.826304, 0.848133, 0.678406, 0.721583, 0.967236, 0.699799, 0.611689, 0.715464, 0.734882, 0.759148, 0.794631, 0.792489, 0.625211, 0.500004, 0.598431, 0.736751, 0.86559, 1.03606, 0.664701, 0.767394, 0.778601, 0.514232, 0.548794, 0.603854, 0.809523, 0.546623, 0.616359, 0.798757, 0.621032, 0.90011, 0.525574, 0.867134, 0.826813, 0.528058, 0.613221, 0.719411, 0.692478, 0.566406, 0.946534, 0.622084, 0.587102, 0.597086, 0.565997, 0.831427, 0.708638, 0.628451, 1.03253, 0.563297, 0.89256, 0.778529, 1.02488, 0.612928, 0.550035, 0.636921, 0.847057, 0.927479, 0.835704, 0.786637, 0.78124, 
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
    for (int i = -1; i <=1; ++i)
      for (int j = -1; j <=1; ++j)
      {
        if (ShouldGo(x + i, y + j))
        {
          BlowArea(aArea, TPoint(x + i, y + j));
        }
      }
    // workaround
    if (ShouldGo(x + 2, y))
    {
      BlowArea(aArea, TPoint(x + 2, y));
    }
    if (ShouldGo(x - 2, y))
    {
      BlowArea(aArea, TPoint(x - 2, y));
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
