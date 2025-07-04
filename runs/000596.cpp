
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
  0.935055, 0.630807, 0.707735, 0.929845, 0.947723, 0.834369, 1.01318, 1.03513, 0.691699, 0.90237, 0.630142, 0.449856, 0.733311, 0.646329, 0.90623, 0.857408, 0.814253, 0.691355, 0.767152, 0.663524, 1.05275, 0.683713, 1.0146, 0.793191, 0.597409, 0.578438, 0.884326, 1.01699, 0.951262, 0.704784, 0.526119, 0.861554, 0.933405, 0.961455, 0.767166, 0.649299, 0.734779, 0.858856, 0.93741, 0.891062, 0.410212, 0.748588, 0.566341, 0.638716, 0.773847, 0.511228, 0.754938, 0.653799, 0.954401, 0.830547, 0.577747, 0.7871, 0.60157, 0.497044, 0.385973, 0.607941, 0.73598, 0.825034, 0.727017, 0.794969, 0.912095, 0.548216, 0.770213, 0.946013, 0.627248, 0.279273, 0.720054, 0.514109, 0.592128, 0.573902, 0.515139, 0.762337, 0.799169, 0.526709, 1.08586, 1.08054, 0.424734, 0.55585, 0.69477, 0.818096, 0.813178, 0.817254, 0.459778, 0.686337, 0.861816, 0.67507, 0.56897, 0.827278, 1.01758, 0.942315, 0.869964, 0.774041, 0.57479, 0.64415, 0.737704, 0.464288, 
  0.539925, 0.681372, 0.741689, 0.931514, 0.595298, 0.574142, 0.591175, 0.537703, 0.693178, 0.651896, 0.630347, 0.787248, 0.586392, 0.602868, 0.888293, 0.763873, 0.715662, 0.592479, 0.338721, 0.690778, 0.553524, 0.750592, 0.446305, 0.704667, 0.695148, 0.529565, 1.12032, 0.80792, 0.653684, 0.633068, 0.444199, 0.878751, 0.688907, 0.541031, 0.69598, 0.66229, 0.690343, 0.674961, 1.01626, 1.04251, 0.894808, 0.849206, 0.614393, 0.845119, 0.607848, 0.745414, 0.874332, 0.69357, 0.434026, 0.707849, 0.858316, 1.10605, 0.67384, 0.895997, 0.817904, 0.863361, 0.734558, 0.76874, 0.561826, 0.759612, 0.837861, 0.901107, 0.911805, 0.786415, 0.646667, 0.482482, 0.740192, 0.666672, 0.841156, 1.0367, 0.947808, 0.779017, 0.679959, 0.759549, 0.680386, 0.761631, 0.965524, 0.632001, 0.453004, 0.496159, 0.69663, 0.500243, 0.839746, 1.24683, 1.19168, 0.708712, 1.09763, 0.757064, 0.914445, 0.65748, 0.985455, 0.617896, 0.776012, 0.560627, 0.776568, 0.895531, 
  0.642869, 0.532297, 0.967488, 0.79211, 0.781919, 0.761076, 0.49337, 0.905918, 0.831442, 0.682313, 0.720324, 0.865536, 0.640223, 0.886564, 0.740459, 0.661223, 0.695892, 0.737138, 0.554997, 0.762087, 0.710269, 0.724877, 0.723227, 0.970042, 0.623239, 0.73168, 0.608276, 0.863877, 0.528441, 0.50384, 0.54582, 0.665893, 0.89908, 1.03127, 1.04438, 0.532066, 0.744814, 0.404481, 0.717307, 0.749125, 0.471866, 0.682083, 0.714313, 0.965017, 0.866971, 0.769191, 0.584152, 0.91727, 0.55211, 0.724181, 0.741695, 0.468549, 0.912249, 0.829508, 0.933095, 0.888964, 0.449964, 0.765488, 0.738451, 1.00583, 0.842271, 0.776878, 0.595472, 0.653796, 0.680475, 0.654979, 0.713978, 0.841195, 0.813239, 0.650501, 1.10493, 0.967168, 0.491037, 0.910362, 0.997297, 0.992368, 0.983896, 0.799996, 0.602317, 0.440288, 0.427368, 0.690943, 0.761231, 0.771077, 0.727272, 0.496374, 0.681801, 1.06362, 0.87579, 0.552157, 0.411195, 0.424345, 0.744787, 0.983874, 0.751351, 1.01617, 
  0.997634, 0.852626, 0.664807, 0.613377, 0.298649, 0.576474, 0.719216, 0.669072, 0.961249, 0.905365, 0.853197, 0.750782, 0.934541, 0.898872, 0.83458, 0.610126, 0.270773, 0.328214, 0.665528, 0.422992, 0.481756, 0.906917, 0.932597, 1.04335, 0.856943, 0.707409, 0.783262, 0.557458, 0.727442, 0.627192, 0.719711, 0.785767, 0.429585, 0.707083, 0.780131, 0.672832, 0.950548, 0.637944, 0.619521, 0.800139, 0.992722, 0.849241, 0.91012, 0.618432, 0.703308, 0.593991, 0.646346, 0.805565, 0.950379, 0.830386, 0.682993, 0.807083, 0.76935, 0.663686, 0.701704, 0.631369, 0.493457, 0.788964, 0.609356, 0.653409, 0.564489, 0.568391, 0.946633, 0.629038, 0.805761, 0.704763, 1.0256, 0.848359, 0.524631, 0.832463, 0.823488, 0.774057, 0.784799, 0.979306, 0.914207, 0.722873, 0.557211, 0.739035, 1.0064, 0.997924, 0.799993, 0.553429, 0.796663, 0.660928, 0.722845, 0.525166, 0.542991, 0.598737, 0.728838, 0.498654, 0.675176, 0.701352, 0.91275, 0.834008, 0.713662, 0.477861, 
  0.814008, 0.442819, 0.488107, 0.454582, 0.509906, 0.811965, 0.888092, 0.817309, 1.00167, 0.664758, 0.536204, 0.44403, 0.85104, 0.433176, 0.739848, 0.571811, 0.705884, 1.05346, 1.06974, 0.876447, 0.947795, 0.71916, 0.636767, 0.647672, 0.798879, 0.476004, 0.851793, 0.860736, 0.872618, 1.02141, 0.661035, 0.744181, 0.763113, 0.579404, 0.55458, 0.464787, 0.520617, 0.703367, 0.836694, 0.805745, 0.621543, 0.4873, 0.783947, 0.876386, 0.921322, 0.801292, 0.534989, 0.794837, 0.759736, 0.784016, 0.47049, 0.87421, 0.813523, 0.726068, 0.955515, 1.0866, 0.894254, 0.877638, 0.591034, 0.83946, 0.570722, 0.808784, 0.81034, 0.757085, 0.910459, 0.940956, 0.78373, 0.648524, 0.71654, 0.826163, 0.890424, 0.608893, 0.552845, 0.704623, 0.751229, 0.717326, 0.825107, 0.726755, 0.734931, 0.808415, 0.857347, 0.677942, 0.577959, 0.745988, 0.723073, 0.521117, 0.704041, 0.843354, 0.408173, 0.894563, 0.685817, 0.596544, 0.506323, 0.81566, 0.544092, 0.818766, 
  0.696527, 0.614251, 0.650621, 0.835466, 0.792084, 0.828082, 1.03267, 0.380795, 0.797632, 0.869562, 1.09984, 1.03975, 0.832711, 0.945283, 0.67484, 0.590124, 0.8134, 0.867069, 0.602566, 0.645976, 0.562361, 0.811556, 0.84299, 0.846839, 0.768721, 0.420717, 0.690982, 0.951915, 0.998162, 0.752741, 0.456068, 0.559982, 0.717157, 0.478319, 0.943051, 0.890547, 0.842394, 0.866781, 0.957538, 0.605197, 0.542438, 0.832998, 0.455756, 0.811007, 0.397354, 0.500184, 0.738236, 0.593411, 0.626888, 0.621715, 0.75586, 0.479356, 1.09147, 0.9831, 0.737896, 0.81781, 0.854758, 0.638925, 0.776861, 0.966904, 0.616015, 0.852742, 0.633999, 0.42842, 0.989103, 0.899162, 0.791941, 0.679053, 0.566895, 0.890077, 0.763883, 0.542936, 0.812667, 0.770526, 0.31043, 0.38746, 0.494064, 0.780195, 0.505939, 0.604137, 0.81653, 0.98522, 0.824249, 0.529766, 1.10523, 0.915528, 0.442005, 0.687962, 0.428639, 0.814775, 0.697899, 0.802336, 0.661055, 0.957152, 0.59754, 0.718266, 
  0.779878, 0.421605, 0.598529, 0.760092, 1.0386, 1.17033, 0.901033, 0.998188, 0.688875, 0.633117, 0.75105, 0.649124, 0.377591, 0.691501, 0.495678, 0.805061, 0.681084, 0.625642, 0.984843, 0.923682, 0.826477, 1.04211, 0.880418, 0.897591, 0.830203, 0.571649, 0.646697, 0.631323, 0.755756, 0.868304, 0.714368, 0.720506, 1.10138, 0.656459, 0.716061, 0.870609, 0.728982, 0.911948, 0.6681, 0.828125, 0.563735, 0.988645, 0.664163, 0.882552, 0.662427, 0.743425, 0.687704, 0.90036, 0.583937, 0.633205, 0.627053, 0.659477, 0.815029, 0.78467, 0.726972, 0.727953, 0.908202, 0.680349, 0.777448, 0.824178, 0.722642, 0.676543, 0.870749, 0.552924, 0.876726, 0.63263, 0.670146, 0.615248, 0.539239, 0.911785, 0.794276, 0.689278, 0.708028, 0.689998, 0.427209, 0.418717, 0.673468, 1.02215, 0.582252, 0.688278, 0.942703, 0.712951, 0.734232, 0.675948, 0.639397, 0.60182, 0.850454, 0.232391, 0.500805, 0.686248, 0.724788, 0.923877, 0.736536, 0.876661, 0.964423, 0.750421, 
  0.89025, 0.816462, 0.722637, 0.857986, 0.765689, 0.533692, 0.831422, 0.826522, 0.51682, 0.685989, 0.488744, 0.621724, 0.994804, 0.901782, 0.731248, 0.507396, 0.577223, 0.50304, 0.462978, 0.698735, 0.727546, 0.660515, 0.686774, 0.749689, 0.844853, 0.839442, 0.554966, 0.863266, 0.582739, 0.529519, 0.438533, 0.858807, 0.637391, 0.767826, 0.701445, 0.50386, 1.01282, 0.693948, 0.556782, 0.48556, 0.566408, 0.678936, 0.782107, 0.950957, 0.852943, 0.653868, 0.669084, 0.982848, 0.592497, 0.715596, 0.748332, 0.433914, 0.789531, 0.715818, 0.824368, 0.862721, 0.925904, 0.762222, 0.601755, 0.870103, 0.676201, 1.02168, 0.939979, 0.802269, 0.803575, 0.536867, 0.730403, 0.592182, 0.968032, 0.675538, 0.863707, 0.819844, 0.656411, 1.07046, 0.727297, 0.687199, 0.933379, 0.85973, 0.409252, 0.422683, 0.807752, 0.732407, 0.767831, 0.514138, 1.21568, 0.884028, 0.642869, 0.553184, 0.799314, 0.601535, 0.551987, 0.514833, 0.422691, 0.637142, 0.445776, 0.75082, 
  0.623351, 0.669932, 0.525589, 0.71593, 0.733929, 0.415243, 0.485119, 0.86078, 1.01248, 1.06597, 0.957574, 0.649678, 0.538379, 0.922378, 0.93034, 0.735217, 0.843598, 0.759626, 0.883255, 0.97372, 0.88408, 0.654402, 0.676689, 0.463229, 0.785849, 0.722177, 0.892149, 0.872358, 0.92122, 0.912913, 0.676144, 0.932187, 0.572511, 0.492308, 0.803227, 0.770388, 0.731852, 0.78538, 0.80763, 0.62717, 0.689507, 0.916287, 0.63828, 0.653823, 0.75546, 0.738917, 0.69158, 0.718272, 0.749019, 0.641384, 0.508955, 0.603335, 0.75754, 0.858018, 1.00411, 0.74273, 0.820922, 0.83908, 0.498656, 0.568053, 0.586379, 0.806408, 0.560399, 0.614929, 0.843124, 0.639397, 0.906627, 0.518227, 0.879674, 0.797438, 0.540999, 0.589392, 0.719656, 0.683394, 0.559725, 0.912234, 0.624644, 0.621079, 0.597279, 0.584813, 0.84683, 0.726129, 0.638543, 0.969758, 0.560299, 0.830089, 0.700913, 0.932853, 0.566157, 0.653012, 0.640716, 0.814906, 0.895968, 0.768711, 0.640641, 0.798782, 
  0.830507, 0.937832, 0.882797, 0.9091, 0.986208, 0.994634, 0.694721, 0.318579, 0.704956, 0.738663, 0.432576, 0.592262, 0.661007, 0.621249, 0.758485, 0.847758, 0.882231, 0.841973, 0.770222, 0.642058, 0.653437, 0.546152, 0.509633, 0.683727, 0.848754, 0.72292, 0.667226, 0.724159, 0.508677, 0.596225, 0.768003, 0.69237, 0.60746, 0.834839, 0.793985, 0.783322, 0.692854, 0.512335, 0.382756, 0.715367, 0.796761, 0.716719, 0.870581, 0.807992, 0.90852, 0.692491, 0.71864, 0.740067, 0.997011, 0.81112, 0.878562, 0.730928, 0.8259, 0.546089, 0.712462, 0.620546, 0.682002, 0.453559, 0.717596, 0.76748, 0.821326, 0.639256, 0.860411, 0.629111, 0.666862, 0.82949, 0.567331, 0.676431, 0.858465, 0.655435, 0.905344, 0.667077, 0.54543, 0.655079, 0.796358, 0.919652, 0.967973, 0.713211, 0.663856, 0.939207, 0.59167, 0.753481, 0.749769, 0.399226, 0.452698, 0.742093, 0.868337, 1.00355, 0.76026, 0.99926, 0.807002, 0.779869, 0.51909, 0.522016, 0.828245, 0.859095
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
