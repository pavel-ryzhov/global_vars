
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
  0.931454, 0.617382, 0.684139, 0.901131, 0.920768, 0.824898, 1.01035, 1.04629, 0.699974, 0.903382, 0.615118, 0.445442, 0.716428, 0.62818, 0.900469, 0.860108, 0.816953, 0.681623, 0.748278, 0.667915, 1.06391, 0.686836, 0.990322, 0.766312, 0.586981, 0.585579, 0.885658, 1.01832, 0.952594, 0.706116, 0.517299, 0.845751, 0.933461, 0.961941, 0.762463, 0.633889, 0.715047, 0.850353, 0.921394, 0.869576, 0.399302, 0.738771, 0.554936, 0.605123, 0.761007, 0.502843, 0.746435, 0.646124, 0.935177, 0.815691, 0.555017, 0.758899, 0.583945, 0.480514, 0.362967, 0.573979, 0.716427, 0.813321, 0.712481, 0.784327, 0.903414, 0.55574, 0.768983, 0.944783, 0.626018, 0.276773, 0.698519, 0.509703, 0.589621, 0.569287, 0.511473, 0.756828, 0.789957, 0.513655, 1.08109, 1.08052, 0.42318, 0.544527, 0.6911, 0.806389, 0.800344, 0.79725, 0.451165, 0.679663, 0.858215, 0.663549, 0.55045, 0.799161, 0.990654, 0.919907, 0.840056, 0.753084, 0.560945, 0.635549, 0.726392, 0.460687, 
  0.532866, 0.677476, 0.751111, 0.907632, 0.600992, 0.576697, 0.587082, 0.537715, 0.682621, 0.642995, 0.620822, 0.790973, 0.564517, 0.622601, 0.892561, 0.748243, 0.733941, 0.614465, 0.357742, 0.681241, 0.517579, 0.737463, 0.447786, 0.706832, 0.684367, 0.554429, 1.13161, 0.801837, 0.670523, 0.666564, 0.464394, 0.872993, 0.676738, 0.523768, 0.685581, 0.667327, 0.696026, 0.695933, 1.02227, 1.04019, 0.908937, 0.854871, 0.631687, 0.880527, 0.595451, 0.722858, 0.869342, 0.706234, 0.445126, 0.729603, 0.856987, 1.09138, 0.6811, 0.91361, 0.867262, 0.880053, 0.729796, 0.768796, 0.561297, 0.752132, 0.835971, 0.914623, 0.898653, 0.772978, 0.645296, 0.509033, 0.764544, 0.67164, 0.848666, 1.05724, 0.954632, 0.736561, 0.677499, 0.780947, 0.666959, 0.755477, 0.969312, 0.630767, 0.469521, 0.526072, 0.731771, 0.535896, 0.849078, 1.17556, 1.19901, 0.680804, 1.0638, 0.718549, 0.861714, 0.611688, 0.973582, 0.637337, 0.798321, 0.574614, 0.744531, 0.821803, 
  0.631998, 0.549977, 0.97993, 0.798665, 0.774897, 0.750583, 0.488991, 0.884625, 0.819845, 0.680162, 0.7259, 0.868411, 0.638916, 0.897417, 0.773916, 0.685539, 0.686865, 0.726701, 0.534184, 0.756142, 0.73, 0.740771, 0.717079, 0.955116, 0.619647, 0.767175, 0.644734, 0.897651, 0.538848, 0.480669, 0.529512, 0.660774, 0.902804, 1.03989, 1.0512, 0.518838, 0.738411, 0.426912, 0.729531, 0.727076, 0.459823, 0.676562, 0.696017, 0.951681, 0.858674, 0.770688, 0.592773, 0.905498, 0.539711, 0.744255, 0.742172, 0.457258, 0.899034, 0.833991, 0.930786, 0.860752, 0.437588, 0.763607, 0.741872, 0.993534, 0.830483, 0.78178, 0.604093, 0.662417, 0.6774, 0.643147, 0.720919, 0.843716, 0.792889, 0.628766, 1.10739, 0.972706, 0.48167, 0.89811, 0.997941, 0.990133, 0.973353, 0.79733, 0.600352, 0.45167, 0.442975, 0.707742, 0.783444, 0.782172, 0.710854, 0.49698, 0.676626, 1.06422, 0.887181, 0.567886, 0.419611, 0.419251, 0.742992, 0.978568, 0.75544, 1.03121, 
  0.999449, 0.801736, 0.621101, 0.612402, 0.298649, 0.576474, 0.717804, 0.666247, 0.978763, 0.942524, 0.887069, 0.743003, 0.918888, 0.833755, 0.82544, 0.638623, 0.278794, 0.328214, 0.64801, 0.424949, 0.520899, 0.962341, 0.976229, 1.02822, 0.834432, 0.677284, 0.770537, 0.575066, 0.754067, 0.613152, 0.703231, 0.77587, 0.461947, 0.743011, 0.792275, 0.641017, 0.947519, 0.603498, 0.590724, 0.818663, 0.989713, 0.821535, 0.883091, 0.574362, 0.672657, 0.563339, 0.59993, 0.753922, 0.936082, 0.808018, 0.66491, 0.788732, 0.753943, 0.643621, 0.655938, 0.58293, 0.445017, 0.740525, 0.563479, 0.631263, 0.579421, 0.585116, 0.954446, 0.652798, 0.840406, 0.710706, 1.00283, 0.82069, 0.500749, 0.813037, 0.818434, 0.787106, 0.818409, 1.0071, 0.960722, 0.770142, 0.587166, 0.758279, 1.00368, 0.989751, 0.795608, 0.549044, 0.80008, 0.694489, 0.75262, 0.58153, 0.590499, 0.638669, 0.767259, 0.534125, 0.708278, 0.722433, 0.930963, 0.854132, 0.743823, 0.520582, 
  0.818907, 0.449677, 0.491083, 0.45195, 0.503257, 0.796912, 0.869525, 0.817109, 0.998458, 0.659458, 0.533795, 0.450837, 0.857017, 0.442387, 0.728474, 0.556758, 0.687819, 1.03376, 1.04232, 0.873235, 0.947596, 0.716953, 0.645531, 0.672374, 0.803431, 0.473894, 0.837733, 0.839649, 0.858297, 1.01549, 0.643014, 0.741871, 0.766826, 0.580198, 0.565415, 0.501666, 0.52222, 0.714719, 0.854311, 0.801536, 0.617334, 0.483091, 0.779829, 0.874225, 0.927604, 0.812198, 0.550915, 0.813775, 0.765287, 0.798204, 0.483422, 0.877436, 0.809314, 0.721859, 0.949844, 1.07717, 0.887967, 0.884784, 0.59943, 0.847856, 0.56729, 0.805247, 0.806229, 0.762164, 0.916505, 0.947002, 0.764566, 0.65457, 0.730116, 0.838921, 0.900672, 0.627757, 0.542805, 0.690567, 0.737173, 0.709327, 0.82541, 0.727058, 0.707922, 0.80671, 0.86016, 0.676739, 0.576683, 0.757222, 0.723073, 0.521117, 0.704041, 0.843981, 0.41564, 0.90746, 0.68547, 0.600863, 0.503111, 0.805765, 0.541265, 0.83238, 
  0.705943, 0.629056, 0.660095, 0.846019, 0.80619, 0.846529, 1.04725, 0.381954, 0.784159, 0.854199, 1.07047, 1.03351, 0.853421, 0.959754, 0.676605, 0.585521, 0.824099, 0.891974, 0.637803, 0.660467, 0.535087, 0.763483, 0.802394, 0.864069, 0.776121, 0.427616, 0.708246, 0.931442, 0.981825, 0.794957, 0.510628, 0.578397, 0.673754, 0.438812, 0.934589, 0.902738, 0.808612, 0.874415, 0.98106, 0.565232, 0.517271, 0.861258, 0.461907, 0.817718, 0.41188, 0.520854, 0.755771, 0.606031, 0.598127, 0.623179, 0.794286, 0.467081, 1.06027, 0.969485, 0.726567, 0.83808, 0.890153, 0.664525, 0.787468, 0.967694, 0.584343, 0.841344, 0.667892, 0.386656, 0.935584, 0.89073, 0.79586, 0.697527, 0.585431, 0.903062, 0.764052, 0.534281, 0.799685, 0.762451, 0.297137, 0.346334, 0.462811, 0.795892, 0.527298, 0.621807, 0.82686, 0.992551, 0.827228, 0.522755, 1.12041, 0.903128, 0.420888, 0.672707, 0.426413, 0.814217, 0.696713, 0.800832, 0.65955, 0.953002, 0.596207, 0.718266, 
  0.779878, 0.419884, 0.595572, 0.757259, 1.03923, 1.17941, 0.917273, 1.02547, 0.726581, 0.642819, 0.741593, 0.638041, 0.374849, 0.680302, 0.49139, 0.813906, 0.689919, 0.644517, 1.0013, 0.929411, 0.833218, 1.03774, 0.875496, 0.885628, 0.81156, 0.552785, 0.631209, 0.615711, 0.740931, 0.857663, 0.688509, 0.700754, 1.08173, 0.642364, 0.71602, 0.8612, 0.71814, 0.901847, 0.639794, 0.847152, 0.573779, 0.978434, 0.666128, 0.897881, 0.676053, 0.743923, 0.671668, 0.899135, 0.609653, 0.641253, 0.622897, 0.678574, 0.817136, 0.79732, 0.737187, 0.745592, 0.938959, 0.693938, 0.775445, 0.827015, 0.759974, 0.683415, 0.848254, 0.547408, 0.868204, 0.62657, 0.688916, 0.609098, 0.511875, 0.892716, 0.790287, 0.701514, 0.727635, 0.692816, 0.441914, 0.42382, 0.664112, 1.00024, 0.580972, 0.69547, 0.938902, 0.708206, 0.736246, 0.694882, 0.632502, 0.622323, 0.869972, 0.234888, 0.490743, 0.666331, 0.690103, 0.902932, 0.727765, 0.884995, 0.973173, 0.750803, 
  0.89025, 0.816462, 0.722637, 0.857986, 0.765689, 0.533692, 0.831422, 0.826522, 0.51682, 0.685989, 0.488744, 0.621724, 0.994804, 0.901782, 0.731248, 0.507396, 0.577223, 0.50304, 0.462978, 0.698735, 0.727546, 0.660515, 0.686774, 0.749689, 0.844853, 0.839442, 0.554966, 0.863266, 0.582739, 0.529519, 0.438533, 0.858807, 0.637391, 0.767826, 0.701445, 0.50386, 1.01282, 0.693948, 0.556782, 0.48556, 0.566408, 0.678936, 0.782107, 0.950957, 0.852943, 0.653868, 0.669084, 0.982848, 0.592497, 0.715596, 0.748332, 0.433914, 0.789531, 0.715818, 0.824368, 0.862721, 0.925904, 0.762222, 0.601755, 0.870103, 0.676201, 1.02168, 0.939979, 0.802269, 0.803575, 0.536867, 0.730403, 0.592182, 0.968032, 0.675538, 0.863707, 0.819844, 0.656411, 1.07046, 0.727297, 0.687199, 0.933379, 0.85973, 0.409252, 0.422683, 0.807752, 0.732407, 0.767831, 0.514138, 1.21568, 0.884028, 0.642869, 0.553184, 0.799314, 0.601535, 0.551987, 0.514833, 0.422691, 0.637142, 0.445776, 0.75082, 
  0.628753, 0.700397, 0.561637, 0.7407, 0.73924, 0.39992, 0.485884, 0.864597, 1.00607, 1.0618, 0.975372, 0.654772, 0.564099, 0.958016, 0.935859, 0.726695, 0.841837, 0.752107, 0.894328, 0.979059, 0.88259, 0.641993, 0.670092, 0.471363, 0.823755, 0.721312, 0.883607, 0.869901, 0.924437, 0.925621, 0.699184, 0.954162, 0.597292, 0.511915, 0.798567, 0.772876, 0.760099, 0.788749, 0.832811, 0.653493, 0.698981, 0.915095, 0.665844, 0.664229, 0.759947, 0.751014, 0.710832, 0.71894, 0.755022, 0.640413, 0.522054, 0.636052, 0.796959, 0.852174, 1.01839, 0.765704, 0.817658, 0.838797, 0.51987, 0.57142, 0.594111, 0.806928, 0.579731, 0.639558, 0.873927, 0.649868, 0.894204, 0.539919, 0.928804, 0.834418, 0.54797, 0.602844, 0.721523, 0.696567, 0.564962, 0.933516, 0.659904, 0.640272, 0.595644, 0.565957, 0.827505, 0.704957, 0.63021, 0.989667, 0.555917, 0.820943, 0.710624, 0.955763, 0.586864, 0.670023, 0.66288, 0.827258, 0.903419, 0.781284, 0.672992, 0.8047, 
  0.830507, 0.937954, 0.882695, 0.926257, 1.00109, 1.01489, 0.694419, 0.299464, 0.686704, 0.726672, 0.441117, 0.603283, 0.667063, 0.625806, 0.744038, 0.82721, 0.862551, 0.823597, 0.773062, 0.628844, 0.641572, 0.551905, 0.538301, 0.7004, 0.864852, 0.700483, 0.651696, 0.737158, 0.49574, 0.560243, 0.755696, 0.710621, 0.61805, 0.840267, 0.792449, 0.79659, 0.731108, 0.499625, 0.371321, 0.741524, 0.818453, 0.741448, 0.878456, 0.833298, 0.933785, 0.708416, 0.733251, 0.767493, 1.02332, 0.783788, 0.859924, 0.760675, 0.85877, 0.571606, 0.726682, 0.663013, 0.710532, 0.469483, 0.736903, 0.804656, 0.818793, 0.604131, 0.831742, 0.628972, 0.663085, 0.809304, 0.589239, 0.660955, 0.843816, 0.637009, 0.891385, 0.660557, 0.534406, 0.637336, 0.774809, 0.903532, 0.951375, 0.695903, 0.664259, 0.913492, 0.568124, 0.745207, 0.728036, 0.389455, 0.43172, 0.725596, 0.870232, 1.01888, 0.774217, 1.00683, 0.82132, 0.771176, 0.500244, 0.494949, 0.800401, 0.858744
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
