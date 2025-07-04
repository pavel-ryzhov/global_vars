
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
  0.935055, 0.636277, 0.718312, 0.940421, 0.953193, 0.825486, 1.00397, 1.03103, 0.687592, 0.897533, 0.627732, 0.450312, 0.739693, 0.652638, 0.904637, 0.855816, 0.822718, 0.686765, 0.763045, 0.659417, 1.04865, 0.679606, 1.01086, 0.791237, 0.602801, 0.575049, 0.880219, 1.01432, 0.947155, 0.700677, 0.523809, 0.859324, 0.930536, 0.959863, 0.763777, 0.644645, 0.730672, 0.854749, 0.934287, 0.889653, 0.415069, 0.745918, 0.565412, 0.639719, 0.774029, 0.51998, 0.761607, 0.649693, 0.950294, 0.829313, 0.582886, 0.788923, 0.613969, 0.499762, 0.382192, 0.608943, 0.728619, 0.824077, 0.738355, 0.798405, 0.921798, 0.546265, 0.778678, 0.959507, 0.640742, 0.284864, 0.716306, 0.520499, 0.603268, 0.57195, 0.518576, 0.758031, 0.805551, 0.526554, 1.08535, 1.08146, 0.425656, 0.5509, 0.691382, 0.816863, 0.8141, 0.813866, 0.45603, 0.68338, 0.861816, 0.678385, 0.570566, 0.820253, 1.00545, 0.935946, 0.871528, 0.769934, 0.570684, 0.641458, 0.737438, 0.464288, 
  0.538287, 0.69267, 0.751507, 0.945643, 0.618607, 0.589663, 0.601736, 0.572161, 0.731606, 0.675024, 0.656582, 0.800178, 0.585886, 0.632782, 0.899808, 0.78893, 0.749136, 0.628995, 0.387344, 0.719595, 0.591174, 0.756023, 0.465264, 0.714339, 0.680348, 0.519511, 1.126, 0.830187, 0.695151, 0.661554, 0.458555, 0.891854, 0.70278, 0.523501, 0.700707, 0.680982, 0.68131, 0.665535, 1.03428, 1.04726, 0.891337, 0.859856, 0.610621, 0.844322, 0.578464, 0.713553, 0.860227, 0.719451, 0.419742, 0.724979, 0.865117, 1.09551, 0.671453, 0.919444, 0.856188, 0.862265, 0.741316, 0.771712, 0.571882, 0.780895, 0.844552, 0.916594, 0.913412, 0.793862, 0.66587, 0.51912, 0.747019, 0.667321, 0.867193, 1.04941, 0.974327, 0.781856, 0.691499, 0.780881, 0.694318, 0.765505, 0.965762, 0.613935, 0.456713, 0.529378, 0.746974, 0.514942, 0.857366, 1.24471, 1.17396, 0.712059, 1.11039, 0.761805, 0.892801, 0.632899, 0.990417, 0.63882, 0.814466, 0.555768, 0.772844, 0.890466, 
  0.642869, 0.527778, 0.962983, 0.789886, 0.768689, 0.750583, 0.49337, 0.905918, 0.831442, 0.682356, 0.725802, 0.851503, 0.635705, 0.887002, 0.755833, 0.664754, 0.695892, 0.737138, 0.554997, 0.762087, 0.705295, 0.723034, 0.723318, 0.961659, 0.625155, 0.745913, 0.625931, 0.875883, 0.528441, 0.503384, 0.540574, 0.657173, 0.896347, 1.03136, 1.04447, 0.525095, 0.749011, 0.421908, 0.734962, 0.766781, 0.478191, 0.674091, 0.710873, 0.964403, 0.867063, 0.769282, 0.584243, 0.915949, 0.552201, 0.735221, 0.751367, 0.470009, 0.912341, 0.8296, 0.933186, 0.889055, 0.444406, 0.765579, 0.740139, 1.00798, 0.833888, 0.776969, 0.595563, 0.653887, 0.680566, 0.65507, 0.714069, 0.832811, 0.800575, 0.65926, 1.12122, 0.97205, 0.48401, 0.90551, 0.997388, 0.992459, 0.983987, 0.797262, 0.591543, 0.430708, 0.426955, 0.70648, 0.778886, 0.771721, 0.726588, 0.486566, 0.66868, 1.04959, 0.863125, 0.543055, 0.408914, 0.424345, 0.744787, 0.997999, 0.760531, 1.00552, 
  0.980532, 0.832728, 0.651223, 0.604017, 0.296988, 0.576474, 0.719216, 0.667577, 0.936924, 0.88663, 0.859803, 0.760844, 0.893464, 0.847892, 0.807936, 0.593528, 0.249722, 0.317908, 0.6637, 0.416513, 0.48077, 0.909953, 0.928826, 1.01925, 0.825748, 0.722884, 0.809897, 0.569408, 0.739233, 0.632631, 0.716769, 0.798837, 0.456285, 0.725555, 0.766508, 0.641065, 0.962887, 0.645905, 0.624417, 0.829546, 1.00715, 0.809576, 0.88632, 0.613377, 0.718921, 0.586743, 0.626198, 0.776024, 0.96704, 0.844219, 0.720819, 0.826109, 0.769059, 0.616597, 0.66131, 0.631134, 0.485804, 0.758333, 0.560726, 0.627614, 0.606619, 0.588202, 0.961629, 0.639067, 0.830143, 0.708042, 1.04915, 0.880125, 0.528716, 0.832387, 0.805275, 0.754058, 0.83939, 0.987887, 0.911209, 0.74054, 0.605989, 0.793422, 1.02499, 0.984817, 0.784242, 0.548112, 0.786038, 0.654086, 0.780156, 0.533924, 0.547206, 0.621126, 0.777774, 0.53851, 0.679134, 0.683174, 0.895654, 0.811463, 0.697064, 0.477628, 
  0.828306, 0.443579, 0.491083, 0.464555, 0.524265, 0.826324, 0.896266, 0.792155, 0.973885, 0.659458, 0.533795, 0.454138, 0.866552, 0.442661, 0.753685, 0.58617, 0.716773, 1.04332, 1.0409, 0.867054, 0.926381, 0.716953, 0.645531, 0.675675, 0.842903, 0.501613, 0.865452, 0.864315, 0.850742, 0.998314, 0.656297, 0.742279, 0.746172, 0.578505, 0.563722, 0.499154, 0.559652, 0.752151, 0.864862, 0.816684, 0.644997, 0.520522, 0.81726, 0.905354, 0.93767, 0.837024, 0.575436, 0.816013, 0.788968, 0.794862, 0.462213, 0.883413, 0.832475, 0.74502, 0.973005, 1.10033, 0.900139, 0.89534, 0.60907, 0.842844, 0.540338, 0.773716, 0.774698, 0.730633, 0.889176, 0.919673, 0.762447, 0.627241, 0.702787, 0.80739, 0.869141, 0.599986, 0.518761, 0.666523, 0.713129, 0.685283, 0.801366, 0.703014, 0.711189, 0.782666, 0.820548, 0.652695, 0.552029, 0.723956, 0.723073, 0.521117, 0.704041, 0.843981, 0.41564, 0.90746, 0.700176, 0.600863, 0.482049, 0.805765, 0.541265, 0.821945, 
  0.699574, 0.619247, 0.656877, 0.847918, 0.807153, 0.846529, 1.04677, 0.381012, 0.805211, 0.859272, 1.04943, 1.00954, 0.862979, 0.975226, 0.703637, 0.605959, 0.837861, 0.897301, 0.62284, 0.647061, 0.550584, 0.789264, 0.809552, 0.836492, 0.775276, 0.415421, 0.677273, 0.926332, 0.994301, 0.779257, 0.492221, 0.560048, 0.687781, 0.467465, 0.960273, 0.883152, 0.81997, 0.851522, 0.936446, 0.558198, 0.517678, 0.858873, 0.472927, 0.801005, 0.399639, 0.520236, 0.760456, 0.583958, 0.596224, 0.587116, 0.726942, 0.442074, 1.06533, 0.993253, 0.734662, 0.825397, 0.873509, 0.668645, 0.804514, 0.953467, 0.592727, 0.846553, 0.649496, 0.421503, 0.971682, 0.890548, 0.791668, 0.691399, 0.590373, 0.905202, 0.766215, 0.535947, 0.78742, 0.780639, 0.331921, 0.385452, 0.471336, 0.790406, 0.529428, 0.633072, 0.838481, 0.989793, 0.820273, 0.528288, 1.08274, 0.928513, 0.444906, 0.673927, 0.416098, 0.814426, 0.702564, 0.808265, 0.666223, 0.963702, 0.602406, 0.718266, 
  0.779878, 0.418022, 0.590015, 0.737431, 1.00751, 1.13084, 0.865058, 1.00267, 0.700894, 0.650174, 0.759869, 0.6495, 0.369615, 0.669653, 0.460392, 0.765573, 0.644608, 0.607609, 0.966122, 0.927422, 0.829082, 1.0486, 0.877624, 0.900192, 0.792128, 0.53216, 0.605834, 0.591423, 0.740204, 0.871596, 0.696545, 0.707068, 1.08293, 0.649243, 0.710254, 0.864689, 0.686679, 0.872466, 0.649119, 0.814021, 0.548093, 0.966727, 0.625488, 0.871364, 0.649358, 0.725087, 0.66035, 0.880504, 0.570608, 0.622723, 0.628032, 0.659109, 0.788451, 0.762752, 0.695328, 0.716111, 0.88883, 0.666159, 0.757624, 0.814865, 0.732398, 0.67459, 0.860663, 0.556543, 0.873481, 0.635922, 0.644224, 0.607856, 0.522322, 0.906447, 0.801019, 0.695656, 0.720457, 0.694355, 0.430063, 0.425779, 0.678096, 1.0205, 0.558921, 0.694266, 0.944173, 0.718437, 0.738903, 0.682182, 0.643839, 0.610481, 0.849427, 0.230301, 0.500805, 0.678893, 0.696022, 0.918335, 0.738524, 0.880665, 0.962757, 0.750421, 
  0.89025, 0.816462, 0.722637, 0.857986, 0.765689, 0.533692, 0.831422, 0.826522, 0.51682, 0.685989, 0.488744, 0.621724, 0.994804, 0.901782, 0.731248, 0.507396, 0.577223, 0.50304, 0.462978, 0.698735, 0.727546, 0.660515, 0.686774, 0.749689, 0.844853, 0.839442, 0.554966, 0.863266, 0.582739, 0.529519, 0.438533, 0.858807, 0.637391, 0.767826, 0.701445, 0.50386, 1.01282, 0.693948, 0.556782, 0.48556, 0.566408, 0.678936, 0.782107, 0.950957, 0.852943, 0.653868, 0.669084, 0.982848, 0.592497, 0.715596, 0.748332, 0.433914, 0.789531, 0.715818, 0.824368, 0.862721, 0.925904, 0.762222, 0.601755, 0.870103, 0.676201, 1.02168, 0.939979, 0.802269, 0.803575, 0.536867, 0.730403, 0.592182, 0.968032, 0.675538, 0.863707, 0.819844, 0.656411, 1.07046, 0.727297, 0.687199, 0.933379, 0.85973, 0.409252, 0.422683, 0.807752, 0.732407, 0.767831, 0.514138, 1.21568, 0.884028, 0.642869, 0.553184, 0.799314, 0.601535, 0.551987, 0.514833, 0.422691, 0.637142, 0.445776, 0.75082, 
  0.624747, 0.676816, 0.527414, 0.704834, 0.716297, 0.417864, 0.489749, 0.853042, 1.01067, 1.06353, 0.956305, 0.650242, 0.544771, 0.929542, 0.930027, 0.737013, 0.825867, 0.748118, 0.875821, 0.969922, 0.880698, 0.653927, 0.678534, 0.467541, 0.794179, 0.725431, 0.89096, 0.879286, 0.929592, 0.905361, 0.66982, 0.936794, 0.583303, 0.499127, 0.803682, 0.775701, 0.737947, 0.78302, 0.802664, 0.610749, 0.672598, 0.907498, 0.644613, 0.643146, 0.744081, 0.727418, 0.682567, 0.722582, 0.757715, 0.65301, 0.50914, 0.59726, 0.752646, 0.851915, 1.0135, 0.719694, 0.815674, 0.833182, 0.492449, 0.56698, 0.588068, 0.831794, 0.581086, 0.614042, 0.834975, 0.631816, 0.913586, 0.515548, 0.871051, 0.806923, 0.538517, 0.604656, 0.712157, 0.697735, 0.57533, 0.91514, 0.617097, 0.619544, 0.598478, 0.586249, 0.846111, 0.729721, 0.644661, 0.985535, 0.556353, 0.815909, 0.694263, 0.939447, 0.567272, 0.65294, 0.640001, 0.821532, 0.899404, 0.784024, 0.651674, 0.798782, 
  0.830507, 0.936421, 0.87795, 0.90731, 0.991608, 1.00255, 0.702438, 0.317915, 0.704956, 0.740031, 0.441928, 0.602014, 0.656531, 0.610823, 0.752798, 0.844859, 0.8802, 0.829803, 0.762254, 0.632193, 0.659824, 0.562119, 0.523724, 0.68393, 0.866606, 0.722575, 0.66346, 0.735583, 0.492444, 0.567705, 0.756877, 0.687815, 0.626474, 0.847548, 0.785166, 0.781658, 0.709055, 0.508797, 0.362183, 0.731554, 0.808483, 0.728007, 0.884378, 0.816355, 0.927832, 0.696809, 0.719832, 0.752978, 1.00471, 0.79296, 0.855153, 0.753681, 0.854752, 0.565839, 0.726259, 0.634343, 0.6958, 0.454751, 0.723485, 0.786851, 0.813412, 0.623641, 0.844796, 0.628688, 0.659789, 0.818077, 0.581128, 0.665018, 0.845684, 0.635493, 0.892005, 0.677916, 0.534345, 0.639465, 0.783999, 0.921182, 0.967332, 0.701286, 0.678101, 0.919298, 0.570665, 0.743548, 0.747983, 0.411999, 0.435792, 0.729015, 0.867652, 1.00639, 0.761723, 0.994336, 0.809257, 0.769899, 0.515518, 0.522016, 0.828245, 0.871868
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
