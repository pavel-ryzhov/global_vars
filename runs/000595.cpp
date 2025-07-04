
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
  0.4787, 0.733035, 0.791692, 0.948519, 0.624631, 0.567528, 0.588255, 0.551867, 0.693887, 0.660252, 0.643576, 0.816679, 0.509995, 0.679332, 0.928452, 0.798048, 0.752531, 0.609596, 0.355997, 0.687863, 0.546399, 0.750215, 0.451977, 0.730931, 0.62603, 0.626786, 1.18426, 0.850483, 0.69165, 0.680482, 0.481101, 0.889696, 0.703623, 0.542916, 0.695353, 0.707718, 0.665609, 0.765756, 1.0642, 1.04487, 0.916426, 0.867009, 0.646714, 0.888614, 0.616227, 0.735422, 0.889275, 0.751881, 0.436549, 0.759714, 0.883117, 1.11792, 0.71009, 0.940541, 0.877953, 0.886628, 0.739852, 0.771993, 0.570554, 0.768047, 0.819602, 0.886588, 0.870618, 0.744943, 0.617261, 0.480998, 0.72725, 0.64282, 0.818221, 0.99964, 0.923907, 0.745286, 0.663341, 0.762082, 0.643152, 0.73167, 0.94651, 0.614277, 0.466085, 0.515937, 0.705463, 0.486532, 0.819013, 1.17782, 1.14179, 0.655466, 1.03947, 0.698906, 0.830569, 0.568595, 0.922358, 0.581939, 0.746856, 0.507981, 0.699042, 0.802999, 
  0.642516, 0.519849, 0.969379, 0.794054, 0.776448, 0.76062, 0.484982, 0.892424, 0.826407, 0.684318, 0.721915, 0.845659, 0.632214, 0.880939, 0.756596, 0.657716, 0.682398, 0.725924, 0.541503, 0.748593, 0.710654, 0.733952, 0.721355, 0.954674, 0.624655, 0.729808, 0.629357, 0.870626, 0.514947, 0.490346, 0.532327, 0.658688, 0.904887, 1.03223, 1.04251, 0.522343, 0.742943, 0.40261, 0.737463, 0.765625, 0.482864, 0.689899, 0.728385, 0.972489, 0.863611, 0.784005, 0.58228, 0.913986, 0.550238, 0.72231, 0.74544, 0.487436, 0.932659, 0.845998, 0.937434, 0.88337, 0.453313, 0.784915, 0.73658, 1.00396, 0.84034, 0.775006, 0.5936, 0.651924, 0.678603, 0.653107, 0.712812, 0.84383, 0.8188, 0.671582, 1.10306, 0.965238, 0.492408, 0.910256, 0.995425, 0.990496, 0.980688, 0.800634, 0.605742, 0.443713, 0.432205, 0.709905, 0.75936, 0.76273, 0.727272, 0.497137, 0.682785, 1.06372, 0.874311, 0.554281, 0.416164, 0.42777, 0.734088, 0.980437, 0.737613, 0.995337, 
  1.05256, 0.802874, 0.621187, 0.582743, 0.281611, 0.576474, 0.718275, 0.665694, 0.957003, 0.900453, 0.852433, 0.740534, 0.985288, 0.814285, 0.789085, 0.575793, 0.252097, 0.328214, 0.657897, 0.426945, 0.503103, 0.923718, 0.936564, 1.00176, 0.888267, 0.622785, 0.722456, 0.512341, 0.706498, 0.601712, 0.698414, 0.769838, 0.437302, 0.710016, 0.762902, 0.599078, 0.968854, 0.56606, 0.565567, 0.78306, 0.964311, 0.80485, 0.86487, 0.574815, 0.668638, 0.55932, 0.594394, 0.722901, 0.947901, 0.800183, 0.676093, 0.81133, 0.750299, 0.633704, 0.676995, 0.61922, 0.481308, 0.776217, 0.584447, 0.62433, 0.576929, 0.587948, 0.969181, 0.647752, 0.824605, 0.708932, 1.02506, 0.853996, 0.533457, 0.833912, 0.821947, 0.790802, 0.824976, 0.999978, 0.946431, 0.74971, 0.587028, 0.770294, 1.00122, 0.989303, 0.798453, 0.567139, 0.821453, 0.731338, 0.807237, 0.597726, 0.605102, 0.656661, 0.814136, 0.589137, 0.73896, 0.748633, 0.967433, 0.88839, 0.798322, 0.578567, 
  0.818907, 0.449677, 0.491083, 0.45195, 0.503257, 0.796912, 0.872337, 0.814085, 0.999104, 0.659458, 0.533795, 0.450837, 0.857017, 0.442387, 0.728474, 0.556758, 0.687361, 1.03547, 1.04091, 0.87144, 0.942828, 0.716953, 0.645531, 0.672374, 0.803431, 0.473894, 0.837733, 0.838789, 0.861759, 1.01116, 0.641183, 0.741871, 0.762211, 0.580198, 0.565415, 0.500376, 0.52222, 0.714719, 0.857396, 0.805568, 0.614145, 0.483091, 0.779829, 0.874225, 0.922989, 0.812198, 0.55061, 0.807634, 0.766335, 0.804755, 0.478317, 0.867359, 0.803815, 0.71636, 0.944345, 1.07168, 0.884637, 0.879286, 0.593016, 0.839948, 0.579311, 0.819268, 0.82025, 0.776185, 0.930527, 0.961024, 0.778588, 0.668592, 0.744138, 0.852942, 0.914693, 0.641779, 0.535021, 0.682783, 0.729389, 0.701543, 0.817626, 0.719274, 0.700138, 0.798926, 0.853255, 0.668955, 0.568289, 0.753844, 0.723073, 0.521117, 0.704041, 0.843981, 0.41564, 0.90746, 0.68547, 0.600863, 0.498496, 0.805765, 0.541265, 0.835091, 
  0.696527, 0.617723, 0.655613, 0.846533, 0.80619, 0.846529, 1.04677, 0.381012, 0.797632, 0.86022, 1.06981, 1.01665, 0.84226, 0.963512, 0.693286, 0.607702, 0.825217, 0.88507, 0.621012, 0.647061, 0.556578, 0.781307, 0.815101, 0.850632, 0.778655, 0.428265, 0.694081, 0.934485, 0.980462, 0.758509, 0.474514, 0.560048, 0.687781, 0.461302, 0.948195, 0.902483, 0.83142, 0.853421, 0.944178, 0.576646, 0.524737, 0.844104, 0.465306, 0.801005, 0.399639, 0.518408, 0.756682, 0.600139, 0.611466, 0.608355, 0.756957, 0.45681, 1.07377, 0.976858, 0.724759, 0.821131, 0.873204, 0.657371, 0.789014, 0.966904, 0.60771, 0.839382, 0.646662, 0.410323, 0.971403, 0.886692, 0.796597, 0.697499, 0.585341, 0.904183, 0.764751, 0.542936, 0.804362, 0.76206, 0.324731, 0.386982, 0.486415, 0.790058, 0.520696, 0.618894, 0.824776, 0.986522, 0.824249, 0.529766, 1.09146, 0.914287, 0.444609, 0.687962, 0.428639, 0.814775, 0.697899, 0.802336, 0.661055, 0.957152, 0.59754, 0.718266, 
  0.779878, 0.421605, 0.595553, 0.750119, 1.02424, 1.15597, 0.890188, 0.998387, 0.692086, 0.638417, 0.753459, 0.649124, 0.376025, 0.680745, 0.481842, 0.790702, 0.669738, 0.624335, 0.98705, 0.926893, 0.826677, 1.04432, 0.871654, 0.89331, 0.817097, 0.55729, 0.63284, 0.624495, 0.758968, 0.871515, 0.717078, 0.722212, 1.09707, 0.657161, 0.706722, 0.857504, 0.714624, 0.899597, 0.666291, 0.831337, 0.566947, 0.991856, 0.667282, 0.890017, 0.66145, 0.744126, 0.683385, 0.893029, 0.587519, 0.639027, 0.642534, 0.667857, 0.81824, 0.787882, 0.731646, 0.736386, 0.91349, 0.68481, 0.780659, 0.82739, 0.739534, 0.693539, 0.888319, 0.561305, 0.879937, 0.635842, 0.673358, 0.61846, 0.534921, 0.912486, 0.797488, 0.696249, 0.718068, 0.704055, 0.441266, 0.426716, 0.673165, 1.02185, 0.581949, 0.689984, 0.93989, 0.714155, 0.735508, 0.688229, 0.639397, 0.60182, 0.850454, 0.231764, 0.493338, 0.673351, 0.710429, 0.919558, 0.739748, 0.886556, 0.96725, 0.750421, 
  0.890604, 0.809286, 0.713707, 0.857986, 0.765689, 0.533692, 0.831422, 0.826522, 0.51682, 0.685989, 0.500397, 0.644676, 1.00363, 0.894549, 0.729445, 0.507396, 0.577223, 0.50304, 0.462978, 0.698735, 0.727546, 0.66899, 0.709726, 0.762698, 0.858773, 0.833807, 0.554256, 0.863266, 0.582739, 0.529519, 0.438533, 0.858807, 0.646219, 0.787953, 0.724397, 0.506926, 1.01712, 0.695771, 0.54897, 0.477747, 0.558595, 0.671124, 0.774295, 0.95162, 0.865964, 0.64994, 0.677121, 0.972419, 0.586862, 0.701438, 0.728525, 0.399983, 0.754188, 0.683299, 0.801736, 0.847858, 0.89727, 0.725113, 0.587598, 0.855946, 0.6731, 1.02705, 0.945353, 0.807643, 0.808949, 0.542241, 0.735071, 0.583432, 0.950454, 0.657959, 0.861978, 0.806752, 0.65853, 1.0867, 0.750249, 0.710151, 0.956331, 0.87562, 0.414902, 0.422683, 0.807752, 0.732407, 0.790783, 0.513653, 1.21568, 0.884028, 0.644634, 0.55495, 0.80108, 0.601888, 0.551987, 0.514833, 0.436815, 0.656916, 0.468728, 0.760278, 
  0.624747, 0.679499, 0.530562, 0.722564, 0.73152, 0.413719, 0.493207, 0.866711, 1.02041, 1.06986, 0.961892, 0.65153, 0.54954, 0.92996, 0.92877, 0.746741, 0.852108, 0.759025, 0.889491, 0.979838, 0.880024, 0.650678, 0.677331, 0.474066, 0.797337, 0.722899, 0.885833, 0.878213, 0.93282, 0.91903, 0.677278, 0.934377, 0.56859, 0.486192, 0.8004, 0.775596, 0.731882, 0.777768, 0.792472, 0.622592, 0.689726, 0.908357, 0.631354, 0.649607, 0.755463, 0.732896, 0.679582, 0.719332, 0.75008, 0.640451, 0.496384, 0.602732, 0.760149, 0.85549, 1.00165, 0.730838, 0.813247, 0.82861, 0.494134, 0.571273, 0.58727, 0.807468, 0.558469, 0.619348, 0.842789, 0.638264, 0.906691, 0.513253, 0.871763, 0.795508, 0.54206, 0.596391, 0.718851, 0.684454, 0.560188, 0.9117, 0.62086, 0.611551, 0.595947, 0.585873, 0.84789, 0.727189, 0.640883, 0.975344, 0.560795, 0.827122, 0.695613, 0.93263, 0.565852, 0.650342, 0.636894, 0.812777, 0.890649, 0.773228, 0.646882, 0.798782, 
  0.830507, 0.935647, 0.87349, 0.915687, 0.988695, 1.01419, 0.711377, 0.318162, 0.704956, 0.738663, 0.432576, 0.58445, 0.66072, 0.617963, 0.757821, 0.851733, 0.887074, 0.837968, 0.776012, 0.649107, 0.653437, 0.546152, 0.50616, 0.666366, 0.858344, 0.726028, 0.674852, 0.760314, 0.518896, 0.582943, 0.763453, 0.702909, 0.60891, 0.830579, 0.786947, 0.778678, 0.720544, 0.515443, 0.386053, 0.751494, 0.822037, 0.741126, 0.875625, 0.808892, 0.922173, 0.702459, 0.731733, 0.764879, 1.00865, 0.793219, 0.864886, 0.751474, 0.845224, 0.562822, 0.717505, 0.644952, 0.7077, 0.466652, 0.736982, 0.797233, 0.81411, 0.615533, 0.837334, 0.634564, 0.668678, 0.813627, 0.574526, 0.664009, 0.850777, 0.647885, 0.904976, 0.65223, 0.535275, 0.630926, 0.773309, 0.910492, 0.956643, 0.690596, 0.668552, 0.916592, 0.577137, 0.739941, 0.730685, 0.380938, 0.431483, 0.726224, 0.864329, 1.00215, 0.758857, 0.997856, 0.819874, 0.767249, 0.500071, 0.499425, 0.805655, 0.845971
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
