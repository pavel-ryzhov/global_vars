
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
  9.12287, 4.72432, 5.76463, 9.4694, 7.78912, 2.51442, 5.52957, 6.03217, 0.754272, 7.45986, 3.28679, 0.212792, 6.41517, 3.39839, 6.75279, 5.34116, 4.57955, 2.82485, 5.49964, 1.24787, 7.60074, -0.200763, 8.31633, 7.03708, 
  2.66248, -0.124298, 4.07222, 5.77605, 5.65581, 6.19451, 4.12498, 7.77949, 7.29014, 8.20842, 3.39488, 2.97261, 4.58724, 6.09462, 6.1263, 7.89877, 1.86031, 8.37019, 3.00438, 3.84027, 4.39283, -1.29611, 1.59504, 1.19946, 
  7.62946, 7.83882, 2.00246, 6.85008, 6.34851, 5.59999, -0.0655678, 4.74148, 3.81672, 5.01528, 4.20773, 5.8772, 8.18167, 0.885827, 4.65705, 9.55749, 5.97544, 2.19549, 7.16817, 2.05069, 2.84332, 1.51694, 3.4301, 10.0133, 
  7.3143, -1.52733, 5.51244, 7.10996, 0.58207, 3.49393, 4.11433, 6.54241, 6.57828, 5.75454, -0.125109, 5.39188, 7.11493, 5.50753, 2.1142, 2.18035, 5.0836, 5.85905, 7.74279, 8.20214, 3.32719, 6.63217, 8.27244, 0.858901, 
  0.631539, 2.48717, 7.43464, 9.44786, 3.99878, 1.98195, 3.83605, 5.68894, 8.35255, 5.02484, 2.93753, 1.36482, 4.42092, 5.12262, 5.4485, 3.43615, 7.43226, 8.02339, 2.26221, 6.88395, 1.82783, 7.88756, 3.32923, 2.775, 
  8.58015, -1.48111, 6.11979, 3.84522, 5.43518, 8.08056, 1.33464, 9.92553, 7.39718, 2.00002, 3.13796, 0.912088, 9.86874, 1.03749, 5.83365, 6.73867, 6.45038, 2.33802, 1.72068, 2.27443, 3.31973, 7.29245, 8.85145, 6.4733, 
  -1.33411, 2.56463, 5.60046, 9.54968, 2.67996, 5.74577, 6.574, 7.94206, 4.58481, 4.4026, 3.80403, 7.07132, 4.18217, 7.31672, 5.0513, 2.77042, 5.00567, 1.19649, 5.42189, 2.004, 5.1181, 8.69002, 6.44626, 0.641066, 
  3.57286, 7.16764, 1.97888, 3.96832, 7.64052, 1.80919, 1.77199, -0.180026, 2.90514, 1.88238, 7.67956, 10.764, 10.5332, 1.24837, 9.31148, 1.11325, 4.73515, -0.0127727, 10.3279, 2.74837, 6.74375, 1.27342, 1.25633, -0.358501, 
  4.47956, 1.32409, 8.84518, 7.47363, 7.01237, 7.74775, 1.95079, 8.11564, 8.8433, 4.46941, -1.36687, 5.49584, 3.77542, 5.65336, 7.81438, 6.62936, 3.14139, 3.68324, 2.85046, 7.2739, 2.67936, 2.38523, 2.18855, 8.86075, 
  2.34088, 8.02607, 7.66931, 8.50977, -0.142317, -0.168061, 2.82923, 0.412316, 3.47761, 7.78269, 8.04349, 1.93746, 6.92056, 2.73506, 6.89033, 5.33439, 0.736241, 5.52205, 3.00187, 8.47437, 7.14715, 6.81908, 0.314261, 8.49962
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

  int patternCount = patternArray.size();
  for (int i = 0 ; i < patternCount; ++i)
  {
    std::cout << recogn.Recognize(patternArray[i]);
  }
  std::cout << std::endl;

  return 0;
}
