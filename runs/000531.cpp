
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>

using std::vector;
using std::string;
using std::cin;
using std::auto_ptr;
//////////////////////////////////////////////////////////////////////////

const int KMaxLineNum = 5;
const int KMaxInt = 2147483647;
const int KNoiseThreshold = 20;

//////////////////////////////////////////////////////////////////////////

// меняет местами два инта
inline void swap(int& aValue1, int& aValue2)
{
  int temp = aValue1;
  aValue1 = aValue2;
  aValue2 = temp;
}

inline int abs(int aValue)
{
  return (aValue > 0) ? aValue : (-aValue);
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
  void Disp() const
  {
    int pointCount = iPoints.size();
    for (int i = 0; i < pointCount; ++i)
    {
      std::cout << "(" << iPoints[i].iX << ", " << iPoints[i].iY << ")";
    }
    std::cout << std::endl;
  }

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

public:
  void Disp() const
  {
    for (int i = 0; i < KPatternHeight; ++i)
    {
      for (int j = 0; j < KPatternWidth; ++j)
      {
        printf("%f ", iDarkenArray[j][i]);
      }
      printf("\n");
    }
    printf("\n");
  }

private:
  vector< vector<double> > iDarkenArray;
  double iWeight;
public:
  const static int KPatternWidth = 4;
  const static int KPatternHeight = 6;
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
  void Save(int aDigit) const
  {
    std::string fileNamePrefix("C:\\Documents and Settings\\Rustam\\Desktop\\zadachi\\numRecogn\\Debug\\");
    std::string fileName = fileNamePrefix + "digits\\00" + char(aDigit + '0') + ".digit";

    std::ofstream file(fileName.c_str());
    file.clear();

    int synapseCount = iSynapseWeights.size();
    for (int i = 0; i < synapseCount; ++i)
    {
      file << iSynapseWeights[i] << ", ";
    }
  }

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

const int KPatternClassCount = 10;

//////////////////////////////////////////////////////////////////////////

const double InitArray[] = {
    9.06856, 4.66735, 5.76042, 9.46815, 7.76209, 2.50805, 5.52124, 6.08114, 0.86784, 7.51139, 3.32838, 0.238865, 6.37585, 3.35702, 6.85559, 5.30973, 4.53818, 2.78553, 5.48028, 0.990034, 7.46651, -0.255373, 8.26306, 7.06362, 
    2.64304, -0.1363, 4.06796, 5.78078, 5.65851, 6.16947, 4.06382, 7.72769, 7.23979, 8.15553, 3.34997, 2.91778, 4.53696, 6.05135, 6.08464, 7.85728, 1.81435, 8.33413, 2.97408, 3.82327, 4.3801, -1.3075, 1.59005, 1.17986, 
    7.59621, 7.83534, 2.01051, 6.85008, 6.34206, 5.57831, -0.096364, 4.71068, 3.81157, 4.99462, 4.1724, 5.85852, 8.16861, 0.840914, 4.61459, 9.52469, 5.93744, 2.18218, 7.17591, 2.04122, 2.82609, 1.50205, 3.41389, 9.99095, 
    7.30333, -1.52796, 5.53462, 7.12208, 0.549406, 3.46747, 4.09563, 6.56267, 6.58923, 5.77535, -0.118431, 5.37267, 7.10007, 5.52597, 2.09084, 2.19332, 5.10606, 5.8387, 7.73356, 8.18008, 3.32045, 6.60608, 8.23693, 0.837506, 
    0.663639, 2.35731, 7.24189, 9.21266, 3.75778, 1.94899, 3.88769, 5.78645, 8.38301, 5.1377, 3.01923, 1.40672, 4.51017, 5.2661, 5.46724, 3.53341, 7.54421, 8.04094, 2.33967, 6.96048, 1.77253, 7.76142, 3.20149, 2.80101, 
    8.59277, -1.41254, 6.13351, 3.8539, 5.49419, 8.16272, 1.31538, 9.82457, 7.26665, 1.84343, 3.00118, 0.845083, 9.79828, 0.937845, 5.78117, 6.63102, 6.32495, 2.27891, 1.67557, 2.25855, 3.32723, 7.32081, 8.88643, 6.45847, 
    -1.31727, 2.53984, 5.58059, 9.58622, 2.73192, 5.73329, 6.57067, 7.94224, 4.59352, 4.41586, 3.8442, 7.07636, 4.15428, 7.30448, 5.03175, 2.85088, 5.081, 1.23042, 5.3542, 2.10423, 5.18641, 8.71859, 6.4753, 0.614314, 
    3.57286, 7.16764, 1.97888, 3.96832, 7.64052, 1.80919, 1.77199, -0.180026, 2.90514, 1.88238, 7.67956, 10.764, 10.5332, 1.24837, 9.31148, 1.11325, 4.73515, -0.0127727, 10.3279, 2.74837, 6.74375, 1.27342, 1.25633, -0.358501, 
    4.47608, 1.30539, 8.82646, 7.43407, 6.99132, 7.73946, 1.9119, 8.09741, 8.83912, 4.47315, -1.36719, 5.46321, 3.77577, 5.68976, 7.83966, 6.63539, 3.14296, 3.67941, 2.86682, 7.24523, 2.64405, 2.35776, 2.16284, 8.84445, 
    2.40079, 8.20393, 7.86515, 8.72373, 0.0722124, -0.116943, 2.95803, 0.447175, 3.50414, 7.81061, 8.09069, 2.05682, 7.04684, 2.77819, 6.92305, 5.35104, 0.77571, 5.64255, 3.07201, 8.64855, 7.33288, 7.02273, 0.51367, 8.56831
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
  void Save() const
  {
    int neuronCount = iNeurons.size();
    for (int i = 0; i < neuronCount; ++i)
    {
      iNeurons[i].Save(i);
    }
  }

public:
  // return class, which has maximum weight
  int Recognize(const TDigitPattern& aPattern)
  {
    double signal = 0.0;
    return DoRecognize(aPattern, signal);
  }

  // return true, if lesson is unnecessary
  bool Teach(const TDigitPattern& aPattern, int aTrueClass)
  {
    double q = 0.1;
    double trueClassSignal = iNeurons[aTrueClass].SumWeight(aPattern);
    bool res = true;

    double classSignal = 0.0;
    int recognizedClass = DoRecognize(aPattern, classSignal);
    while (recognizedClass != aTrueClass)
    {
      iNeurons[recognizedClass].ChangeWeight(q * (trueClassSignal - classSignal), aPattern);
      iNeurons[aTrueClass].ChangeWeight(q * (classSignal - trueClassSignal), aPattern);
      recognizedClass = DoRecognize(aPattern, classSignal);
      res = false;
    }
    return res;
  }

private:
  int DoRecognize(const TDigitPattern& aPattern, double& aSignal)
  {
    int neuronIndex = 0;
    aSignal = iNeurons[neuronIndex].SumWeight(aPattern);
    int neuronCount = iNeurons.size();
    for (int i = 1; i < neuronCount; ++i)
    {
      double signal = iNeurons[i].SumWeight(aPattern);
      if (signal > aSignal)
      {
        aSignal = signal;
        neuronIndex = i;
      }
    }
    return neuronIndex;
  }

private:
  std::vector<TNeuron> iNeurons;
};

//////////////////////////////////////////////////////////////////////////

void makePatternFromArea(const TArea& aArea, TDigitPattern& aPattern)
{
  int pointCount = aArea.PointCount();
  double w = double(aArea.MaxX() - aArea.MinX() + 1) / aPattern.Width();
  double h = double(aArea.MaxY() - aArea.MinY() + 1) / aPattern.Height();
  double q = 1.0 / w / h;
  for (int i = 0; i < pointCount; ++i)
  {
    int x = aArea.Point(i).iX - aArea.MinX();
    int y = aArea.Point(i).iY - aArea.MinY();
    // x 
    int floorX = int(x / w);
    int ceilingX = int((x + 1) / w);
    if (ceilingX > aPattern.Width() - 1)
      ceilingX = aPattern.Width() - 1;
    // y
    int floorY = int(y / h);
    int ceilingY = int((y + 1) / h);
    if (ceilingY > aPattern.Height() - 1)
      ceilingY = aPattern.Height() - 1;
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
  std::vector<TDigitPattern> patternArray(areaCount);

  for (int i = 0; i < areaCount; ++i)
  {
    makePatternFromArea(*(largeAreas[i]), patternArray[i]);
  }

  std::vector<int> permutation(areaCount);
  for (int i = 0; i < areaCount; ++i)
    permutation[i] = i;

  if (areaCount > 3) // если есть "шум", выбираем 3 самые "тяжелые" связные области
  {
    for (int i = 1; i <= 3; ++i)
    {
      for (int j = areaCount - i; j > 0; --j)
      {
        // переставлять будем только индексы в permutation
        if (patternArray[permutation[j]].Weight() > patternArray[permutation[j - 1]].Weight())
        {
          swap(permutation[j], permutation[j - 1]);
        }
      }
    }
    // теперь первые 3 индекса в permutation указывают на самые "тяжелые" связные области
    // упорядочим их по возрастанию, чтобы распознанные цифры шли в правильном порядке
    if (permutation[0] > permutation[1])
      swap(permutation[0], permutation[1]);
    if (permutation[1] > permutation[2])
      swap(permutation[1], permutation[2]);
    if (permutation[0] > permutation[1])
      swap(permutation[0], permutation[1]);
    areaCount = 3;
  }

  aPatterns.resize(areaCount); // areaCount может оказаться < 3

  for (int i = 0; i < areaCount; ++i)
  {
    aPatterns[i] = patternArray[permutation[i]];
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

void readImageFromFile(TImage& aImage, const std::string& aFileName)
{
  std::ifstream file(aFileName.c_str());
  std::string line;
  while (!file.eof())
  {
    getline(file, line);
    size_t lineLen = line.size();

    if (aImage.size() < lineLen)
      aImage.resize(lineLen);

    for (size_t i = 0; i < lineLen; ++i)
    {
      aImage[i].push_back(ConvertToColor(line[i]));
    }
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
