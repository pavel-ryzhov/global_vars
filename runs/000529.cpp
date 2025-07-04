
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

const int KMaxLineNum = 100;
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
    while (IsDelimiter(leftBoundary))
      ++leftBoundary;
    int rightBoundary = iWidth - 1;
    while (IsDelimiter(rightBoundary))
      --rightBoundary;

    int trueWidth = rightBoundary - leftBoundary + 1;
    int firstDelimiter = FindDelimiter(leftBoundary + trueWidth / 3);
    int secondDelimiter = FindDelimiter(leftBoundary + 2 * trueWidth / 3);
    DoSelectBetween(aAreas, leftBoundary, firstDelimiter);
    DoSelectBetween(aAreas, firstDelimiter, secondDelimiter);
    DoSelectBetween(aAreas, secondDelimiter, rightBoundary);
  }

  void DoSelectBetween(TAreaPtrArray& aAreas, int aLeft, int aRight)
  {
    iLeft = aLeft;
    iRight = aRight;
    for (int i = aLeft; i <= aRight; ++i)
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
    if (aX < iLeft || aX > iRight)
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

  // finds vertical delimiter nearest to aX
  int FindDelimiter(int aX)
  {
    if (IsDelimiter(aX))
      return aX;
    int i = 1;
    while (aX - i >= 0 && aX + i < iWidth)
    {
      if (IsDelimiter(aX - i))
        return aX - i;
      if (IsDelimiter(aX + i))
        return aX + i;
      ++i;
    }
    return aX;
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
  9.02779, 4.70488, 5.84454, 9.55227, 7.83881, 2.53497, 5.57591, 6.16526, 0.951958, 7.59551, 3.4125, 0.336282, 6.37819, 3.37384, 7.00066, 5.32655, 4.555, 2.78787, 5.53859, 0.813782, 7.51441, -0.221726, 8.30411, 7.13261,
  2.27609, -0.0455729, 4.41908, 6.68727, 6.84308, 6.39426, 3.24154, 7.31873, 7.31595, 7.93302, 3.02661, 2.00932, 4.60387, 6.01966, 6.20549, 7.84826, 1.29426, 8.08519, 3.00144, 3.64783, 4.23211, -1.28132, 1.94392, 0.915539,
  7.61381, 7.86517, 2.02331, 6.87429, 6.39821, 5.63143, -0.0228745, 4.75256, 3.89122, 5.07837, 4.20268, 5.88543, 8.2319, 0.881793, 4.63267, 9.53042, 5.96753, 2.16117, 7.24611, 2.04141, 2.80513, 1.4989, 3.40534, 9.96423,
  7.30892, -1.43298, 5.69897, 7.21188, 0.450068, 3.387, 4.13167, 6.71519, 6.71345, 5.93754, -0.0681562, 5.39217, 7.15176, 5.66493, 2.09071, 2.33164, 5.27324, 5.84973, 7.75843, 8.21185, 3.39884, 6.61764, 8.17388, 0.775439,
  0.984027, 2.29594, 6.87486, 8.41866, 2.89413, 2.08661, 4.58412, 6.07456, 8.28246, 5.16248, 3.30025, 2.26526, 4.59489, 5.24771, 5.43025, 3.33253, 7.79265, 8.12209, 2.49029, 7.0406, 1.99063, 7.73082, 2.92564, 3.00267,
  8.66858, -1.46035, 6.09194, 3.77097, 5.45223, 7.90922, 1.40759, 9.75177, 7.31539, 2.00111, 3.06535, 1.0327, 9.7743, 0.876665, 5.63325, 6.56234, 6.39192, 2.43193, 1.60418, 2.49726, 3.31035, 7.35683, 8.93668, 6.60634,
  -1.28325, 2.45701, 5.34515, 9.4089, 2.5131, 5.77896, 6.60804, 7.92004, 4.46561, 4.28693, 3.6032, 6.93252, 4.19535, 7.40661, 5.0497, 3.15151, 5.30269, 1.3119, 5.30213, 2.32956, 5.22915, 8.82561, 6.50397, 0.547557,
  3.57286, 7.16764, 1.97888, 3.96832, 7.64052, 1.80919, 1.77199, -0.180026, 2.90514, 1.88238, 7.67956, 10.764, 10.5332, 1.24837, 9.31148, 1.11325, 4.73515, -0.0127727, 10.3279, 2.74837, 6.74375, 1.27342, 1.25633, -0.358501,
  4.49325, 1.39258, 9.01442, 7.4735, 6.89603, 7.56438, 1.89512, 8.18248, 8.80403, 4.4782, -1.26992, 5.43836, 3.64602, 5.64285, 7.83981, 6.60732, 3.07959, 3.72472, 2.73906, 7.16921, 2.59279, 2.32966, 2.10626, 8.82834,
  2.33793, 8.05568, 7.70885, 8.63393, 0.0738223, -0.0960147, 2.8069, 0.299431, 3.35479, 7.64448, 8.04791, 1.94398, 6.89054, 2.63756, 6.80597, 5.19618, 0.607972, 5.53818, 2.99187, 8.50013, 7.18285, 6.87016, 0.443865, 8.58577
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

  for (int i = 0 ; i < 3; ++i)
  {
    std::cout << recogn.Recognize(patternArray[i]);
  }
  std::cout << std::endl;

  return 0;
}
