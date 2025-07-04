
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
  0.931454, 0.621623, 0.710716, 0.940563, 0.958643, 0.843281, 1.00736, 1.03442, 0.689591, 0.889938, 0.608962, 0.446711, 0.725913, 0.652548, 0.908029, 0.859207, 0.82611, 0.690156, 0.766437, 0.662808, 1.05204, 0.682998, 1.01077, 0.779314, 0.598765, 0.578441, 0.883611, 1.01771, 0.950547, 0.704069, 0.5272, 0.862715, 0.933928, 0.963254, 0.767169, 0.640609, 0.733909, 0.850558, 0.930096, 0.885462, 0.410878, 0.741726, 0.563279, 0.645816, 0.780126, 0.521962, 0.757416, 0.65293, 0.953531, 0.825122, 0.578695, 0.784732, 0.609778, 0.495571, 0.380059, 0.61504, 0.734716, 0.830174, 0.735866, 0.801797, 0.917762, 0.549656, 0.78207, 0.962899, 0.644133, 0.288256, 0.719698, 0.523891, 0.606659, 0.575342, 0.521967, 0.753995, 0.791771, 0.526463, 1.08874, 1.08485, 0.429048, 0.557378, 0.694773, 0.820254, 0.817491, 0.817257, 0.45594, 0.6696, 0.858215, 0.663731, 0.56297, 0.820395, 1.0109, 0.95477, 0.874919, 0.773326, 0.570825, 0.633862, 0.718669, 0.460687, 
  0.587771, 0.705034, 0.695935, 0.858632, 0.54288, 0.536603, 0.538806, 0.485429, 0.646668, 0.63351, 0.585551, 0.810213, 0.576803, 0.612381, 0.87772, 0.732515, 0.702689, 0.562568, 0.31769, 0.70304, 0.566283, 0.735476, 0.431449, 0.728547, 0.735712, 0.59272, 1.16804, 0.853605, 0.672523, 0.672957, 0.513574, 0.941413, 0.724411, 0.56826, 0.722552, 0.728302, 0.639991, 0.630614, 0.993331, 0.987301, 0.8386, 0.821283, 0.574433, 0.78047, 0.503982, 0.666686, 0.795094, 0.637082, 0.456656, 0.751011, 0.910487, 1.13965, 0.703503, 0.934731, 0.83322, 0.876359, 0.762166, 0.814181, 0.576153, 0.786229, 0.814651, 0.89167, 0.922099, 0.790719, 0.614042, 0.460289, 0.703094, 0.639611, 0.84018, 1.06407, 0.984698, 0.83868, 0.698801, 0.75962, 0.696509, 0.747572, 0.947652, 0.626963, 0.460592, 0.538705, 0.735925, 0.533097, 0.867932, 1.33524, 1.20004, 0.684239, 1.0716, 0.749204, 0.889723, 0.653092, 0.984984, 0.616094, 0.761267, 0.544429, 0.772594, 0.978835, 
  0.639859, 0.524845, 0.989321, 0.813527, 0.774705, 0.750127, 0.484982, 0.892424, 0.826745, 0.692568, 0.738356, 0.862592, 0.650042, 0.885763, 0.767839, 0.674572, 0.683934, 0.715973, 0.531553, 0.741346, 0.712162, 0.740379, 0.739804, 0.966247, 0.620873, 0.715425, 0.610255, 0.857486, 0.496583, 0.460039, 0.510405, 0.636162, 0.886911, 1.04037, 1.02981, 0.516336, 0.763829, 0.408247, 0.7134, 0.730854, 0.445637, 0.659789, 0.699852, 0.957302, 0.879744, 0.774981, 0.567899, 0.932179, 0.554224, 0.728213, 0.7071, 0.444901, 0.892809, 0.808851, 0.92429, 0.884578, 0.44605, 0.734547, 0.703523, 1.00787, 0.860995, 0.804553, 0.616434, 0.661332, 0.691715, 0.675478, 0.738655, 0.861558, 0.812611, 0.633145, 1.08896, 0.971883, 0.49983, 0.941463, 1.02995, 1.02502, 1.01521, 0.833814, 0.619136, 0.440919, 0.420369, 0.684418, 0.753476, 0.774856, 0.730304, 0.516699, 0.7088, 1.08882, 0.900782, 0.577614, 0.42064, 0.42777, 0.734088, 0.966313, 0.750154, 1.02125, 
  0.962565, 0.869366, 0.664806, 0.600869, 0.314927, 0.585343, 0.715066, 0.656727, 0.921807, 0.896581, 0.89459, 0.799036, 0.886462, 0.896723, 0.781138, 0.571395, 0.235996, 0.341512, 0.663101, 0.395611, 0.474126, 0.952745, 0.928986, 1.0812, 0.816629, 0.711329, 0.700193, 0.529824, 0.717532, 0.639528, 0.669326, 0.75706, 0.41915, 0.687665, 0.717216, 0.645644, 0.963459, 0.636211, 0.575193, 0.830098, 0.986115, 0.849247, 0.89744, 0.612424, 0.714484, 0.556248, 0.606467, 0.755407, 0.964048, 0.807865, 0.663587, 0.791778, 0.781249, 0.656212, 0.651898, 0.641897, 0.47983, 0.745585, 0.546244, 0.614439, 0.590259, 0.572755, 0.945356, 0.630681, 0.839964, 0.690457, 1.03594, 0.840048, 0.478949, 0.819514, 0.797876, 0.740959, 0.796897, 1.00286, 0.913688, 0.772892, 0.592369, 0.723404, 1.03306, 0.992138, 0.795252, 0.543629, 0.772502, 0.623012, 0.73343, 0.52343, 0.555392, 0.615322, 0.739781, 0.465438, 0.635877, 0.677069, 0.890573, 0.813488, 0.692441, 0.434113, 
  0.814776, 0.418713, 0.471799, 0.45387, 0.518734, 0.829196, 0.908561, 0.819221, 1.01711, 0.661476, 0.536494, 0.435428, 0.851697, 0.407494, 0.741161, 0.579092, 0.712707, 1.06063, 1.09461, 0.865617, 0.932836, 0.697029, 0.617543, 0.623226, 0.797366, 0.465008, 0.852245, 0.861547, 0.874529, 1.01358, 0.65363, 0.717323, 0.742604, 0.550444, 0.525621, 0.425851, 0.545626, 0.724046, 0.848768, 0.851412, 0.654445, 0.510355, 0.799196, 0.881991, 0.938707, 0.809366, 0.542758, 0.800307, 0.745874, 0.785189, 0.455346, 0.879463, 0.834551, 0.747096, 0.975081, 1.10241, 0.910767, 0.882301, 0.596839, 0.840815, 0.57151, 0.811349, 0.812331, 0.768266, 0.931011, 0.961508, 0.829492, 0.669076, 0.737092, 0.842513, 0.906774, 0.620294, 0.544275, 0.675162, 0.718286, 0.69044, 0.806523, 0.708171, 0.743657, 0.789831, 0.846221, 0.659358, 0.561672, 0.732331, 0.723073, 0.518796, 0.688489, 0.820691, 0.3891, 0.88092, 0.688342, 0.59411, 0.513001, 0.82289, 0.544938, 0.817033, 
  0.727496, 0.633228, 0.671777, 0.850094, 0.776072, 0.815416, 1.02822, 0.380835, 0.811635, 0.869856, 1.0494, 0.987859, 0.876127, 0.985641, 0.709465, 0.613209, 0.849828, 0.883981, 0.612381, 0.648777, 0.523677, 0.742954, 0.838464, 0.834447, 0.769588, 0.415183, 0.725896, 0.941678, 1.03606, 0.779626, 0.497157, 0.572223, 0.692685, 0.46276, 0.995962, 0.919499, 0.782209, 0.864798, 1.01518, 0.569278, 0.56211, 0.809439, 0.447539, 0.820961, 0.396395, 0.527763, 0.775495, 0.625487, 0.591078, 0.639001, 0.789042, 0.472851, 1.07843, 0.95521, 0.753482, 0.808226, 0.849915, 0.679231, 0.812974, 0.975127, 0.587092, 0.834872, 0.612612, 0.383434, 0.956784, 0.90899, 0.751553, 0.675141, 0.599247, 0.895524, 0.77653, 0.552677, 0.819036, 0.722799, 0.25224, 0.290217, 0.44005, 0.822751, 0.475137, 0.612844, 0.819032, 0.997258, 0.846097, 0.528263, 1.11489, 0.893875, 0.379573, 0.63001, 0.401568, 0.841922, 0.730503, 0.830712, 0.687323, 0.982671, 0.598414, 0.717975, 
  0.755396, 0.394401, 0.578376, 0.75043, 1.03568, 1.1792, 0.911239, 1.02809, 0.713235, 0.635318, 0.756068, 0.651732, 0.352925, 0.66199, 0.485943, 0.807463, 0.691616, 0.626815, 0.997058, 0.947449, 0.842444, 1.05144, 0.884977, 0.903919, 0.818825, 0.574655, 0.671194, 0.652088, 0.749743, 0.856552, 0.70814, 0.713532, 1.08634, 0.642437, 0.73417, 0.874501, 0.729351, 0.927853, 0.675986, 0.835976, 0.544108, 0.989427, 0.659328, 0.906358, 0.675006, 0.731271, 0.680378, 0.912264, 0.611557, 0.639866, 0.612381, 0.6561, 0.786848, 0.783909, 0.724963, 0.752324, 0.916063, 0.674127, 0.785751, 0.831233, 0.743787, 0.668187, 0.838857, 0.543137, 0.850672, 0.620398, 0.681303, 0.634244, 0.552126, 0.91799, 0.809273, 0.688282, 0.688639, 0.69147, 0.429713, 0.419478, 0.662579, 0.991072, 0.567437, 0.703312, 0.960482, 0.719309, 0.735166, 0.673975, 0.631794, 0.61961, 0.870868, 0.236695, 0.500805, 0.674017, 0.689874, 0.909715, 0.726698, 0.867211, 0.963879, 0.750133, 
  0.88852, 0.799795, 0.6997, 0.873361, 0.765689, 0.533692, 0.831422, 0.826522, 0.51682, 0.685989, 0.495999, 0.619444, 1.0153, 0.882733, 0.731055, 0.532493, 0.577223, 0.50304, 0.462978, 0.698735, 0.727546, 0.66436, 0.684957, 0.734689, 0.857482, 0.823267, 0.571431, 0.876625, 0.582739, 0.529519, 0.438533, 0.858807, 0.641821, 0.766425, 0.708944, 0.492275, 1.01583, 0.69449, 0.556603, 0.477747, 0.558595, 0.671124, 0.774295, 0.955549, 0.859816, 0.671333, 0.691107, 0.971128, 0.585571, 0.688583, 0.73477, 0.399983, 0.754188, 0.694749, 0.813757, 0.849344, 0.912876, 0.75183, 0.601584, 0.854654, 0.677364, 1.01049, 0.93169, 0.799773, 0.816459, 0.548125, 0.737483, 0.601122, 0.977171, 0.673227, 0.862606, 0.792101, 0.679229, 1.07315, 0.741324, 0.708859, 0.955039, 0.867044, 0.414089, 0.422683, 0.807752, 0.732407, 0.778052, 0.485643, 1.2424, 0.909357, 0.661805, 0.560669, 0.793441, 0.601194, 0.551987, 0.514833, 0.436815, 0.656916, 0.455997, 0.732268, 
  0.626691, 0.688923, 0.566802, 0.756621, 0.752313, 0.414886, 0.53716, 0.907881, 1.05143, 1.09473, 0.992646, 0.634966, 0.578485, 0.944378, 0.938012, 0.731916, 0.818447, 0.751288, 0.881739, 0.994292, 0.908449, 0.668246, 0.68626, 0.459773, 0.785799, 0.694932, 0.852832, 0.840635, 0.89943, 0.885898, 0.662216, 0.934578, 0.579019, 0.49687, 0.780054, 0.744366, 0.782945, 0.801385, 0.837847, 0.663611, 0.736802, 0.968024, 0.672683, 0.643171, 0.770265, 0.778801, 0.741962, 0.748479, 0.745569, 0.62895, 0.538845, 0.634124, 0.776748, 0.87592, 1.00555, 0.698789, 0.816724, 0.843115, 0.509801, 0.563026, 0.57263, 0.823307, 0.586631, 0.637599, 0.858534, 0.641569, 0.904973, 0.511827, 0.874732, 0.811204, 0.527354, 0.588839, 0.724196, 0.707385, 0.58341, 0.933222, 0.64069, 0.629432, 0.602849, 0.56936, 0.831491, 0.715604, 0.630212, 0.969997, 0.557315, 0.845619, 0.739724, 0.986257, 0.614005, 0.654164, 0.671324, 0.832057, 0.908795, 0.788679, 0.673146, 0.775762, 
  0.815475, 0.944071, 0.900769, 0.902034, 1.01036, 1.01226, 0.687187, 0.318452, 0.704956, 0.740031, 0.441928, 0.602014, 0.636244, 0.620349, 0.75964, 0.848136, 0.901451, 0.864035, 0.77245, 0.642324, 0.660438, 0.564373, 0.526798, 0.688643, 0.848959, 0.72904, 0.6643, 0.718803, 0.520316, 0.608234, 0.76982, 0.706184, 0.643123, 0.871513, 0.818507, 0.812618, 0.692846, 0.511799, 0.353598, 0.718265, 0.81271, 0.729589, 0.911956, 0.84596, 0.931475, 0.711588, 0.741426, 0.764736, 0.991897, 0.806198, 0.859748, 0.74641, 0.8319, 0.547748, 0.737699, 0.62103, 0.670892, 0.444908, 0.731264, 0.774812, 0.813951, 0.63316, 0.85192, 0.622163, 0.646686, 0.804928, 0.547811, 0.643484, 0.821233, 0.617476, 0.87396, 0.652288, 0.507327, 0.649632, 0.796147, 0.927448, 0.960841, 0.68997, 0.63927, 0.909956, 0.565986, 0.747663, 0.748953, 0.407078, 0.408536, 0.72464, 0.860779, 0.991937, 0.759899, 0.996869, 0.801549, 0.774313, 0.520615, 0.523541, 0.82977, 0.861942
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
