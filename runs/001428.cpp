#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <list>

//Some useful defines from Qt
//Avoid "unused parameter" warnings
#define Q_UNUSED(__x) (void)__x

template <typename T>
inline const T &qMin(const T &a, const T &b) { if (a < b) return a; return b; }
template <typename T>
inline const T &qMax(const T &a, const T &b) { if (a < b) return b; return a; }
template <typename T>
inline const T &qBound(const T &min, const T &val, const T &max)
{ return qMax(min, qMin(max, val)); }

inline int qRound(double d)
   { return d >= 0.0 ? int(d + 0.5) : int(d - int(d-1) + 0.5) + int(d-1); }

class TPoint //Qt's QPoint light edition
   {
      int X;
      int Y;
   public:
      TPoint(int x = 0, int y = 0): X(x), Y(y) { }
      double x() const { return X; }
      double y() const { return Y; }
   };

class TPointF //Qt's QPointF light edition
   {
      double X;
      double Y;
   public:
      TPointF(double x = 0, double y = 0): X(x), Y(y) { }
      TPoint toPoint() const { return TPoint(qRound(x()), qRound(y())); }
      double x() const { return X; }
      double y() const { return Y; }
   };

class TRect //Qt's QRect light edition
   {
      int x1;
      int y1;
      int x2;
      int y2;

   public:
      TRect(int x = 0, int y = 0, int Width = 0, int Height = 0): x1(x), y1(y), x2(x+Width), y2(y+Height) { }
      TRect(const TPoint &TopLeft, const TPoint &BottomRight): x1(TopLeft.x()), y1(TopLeft.y()), x2(BottomRight.x()), y2(BottomRight.y()) { }
      int height() const { return y2 - y1; }
      int width() const  { return x2 - x1; }
      int bottom() const { return y2;      }
      int left() const   { return x1;      }
      int right() const  { return x2;      }
      int top() const    { return y1;      }
   };

//==============================================================================================================================================================
//==============================================================================================================================================================

namespace ocr {

const double White = 0;
const double Black = 1;
const double LightGray = 0.25;
const double DarkGray = 0.75;
const double MinDigitHeight = 12;
const double MinDigitWidth = 2;

const std::string Pattern0_v1[] = {
"000000001111111000000000",
"000001111111111111000000",
"000011111100000011110000",
"000111111000000001111000",
"001111110000000001111100",
"011111110000000000111110",
"011111110000000000111110",
"111111110000000000111111",
"111111110000000000111111",
"111111110000000000111111",
"111111110000000000111111",
"011111110000000000111110",
"011111110000000000111110",
"001111110000000000111100",
"000111111000000001111000",
"000011111110000011110000",
"000001111111111111000000",
"000000001111111000000000" };
const std::string Pattern1_v1[] = {
"000000000011000000",
"000000111111000000",
"001111111111000000",
"000000011111000000",
"000000011111000000",
"000000011111000000",
"000000011111000000",
"000000011111000000",
"000000011111000000",
"000000011111000000",
"000000011111000000",
"000000011111000000",
"000000011111000000",
"000000011111000000",
"000000011111000000",
"000000011111000000",
"000000011111000000",
"000111111111111110"  };
const std::string Pattern2_v1[] = {
"000000011111111100000000",
"000001111111111111100000",
"000111110000111111111000",
"001110000000000111111100",
"001000000000000011111110",
"000000000000000001111110",
"000000000000000001111100",
"000000000000000011111100",
"000000000000000111111000",
"000000000000011111110000",
"000000000000111111000000",
"000000000011111100000000",
"000000000111111000000000",
"000000011111110000000000",
"000001111111110000000000",
"0001111111111111111111111",
"011111111111111111111110",
"111111111111111111111100" };
const std::string Pattern3_v1[] = {
"000000111111111100000",
"000011111111111111000",
"000111100000011111100",
"001111100000001111110",
"001111000000000111100",
"000110000000001111000",
"000111100000011110000",
"000000000001111100000",
"000000011111111111000",
"000000001111111111110",
"000000000000011111111",
"000000000000000011111",
"000000000000000001111",
"111100000000000011111",
"111110000000000111110",
"111110000000111111100",
"011111111111111110000",
"001111111111110000000" };
const std::string Pattern4_v1[] = {
"0000000000000001111100000",
"0000000000000011111100000",
"0000000000001111111100000",
"0000000000011111111100000",
"0000000001111001111100000",
"0000000011110001111100000",
"0000001111000001111100000",
"0000011110000001111100000",
"0001111000000001111100000",
"0111110000000001111100000",
"1111000000000001111100000",
"1111111111111111111111111",
"1111111111111111111111111",
"0111111111111111111111111",
"0000000000000001111100000",
"0000000000000001111100000",
"0000000000000001111100000",
"0000000000000001111100000" };
const std::string Pattern4_v2[] = {
"0000000001111000000000000",
"0000000011111100000000000",
"0000000111111100000000000",
"0000000111111100011000000",
"0000001111111001111000000",
"0000001111110011111000000",
"0000011111110111111000000",
"0000011111100111111000000",
"0000111111000111111000000",
"0011111110000111111000000",
"0111111100000111111000000",
"0111111100000111111000000",
"1111111111111111111111111",
"1111111111111111111111111",
"0000000000000111111000000",
"0000000000000111111000000",
"0000000000011111111100000",
"0000000000000000000000000" };
const std::string Pattern4_v3[] = {
"0000000011111110000000000",
"0000000111111110000000000",
"0000000111111000000000000",
"0000011111110000000000000",
"0000011111110000000000000",
"0001111111111110000000000",
"0001111100111111100000000",
"0011111100111111100000000",
"1111111000111111100000000",
"1111111111111111111111111",
"1111111000111111111111000",
"0000000000111111100000000",
"0000000000111111100000000",
"0000000000001111100000000",
"0000000000001110000000000",
"0000000000001110000000000",
"0000000000001110000000000",
"0000000000001110000000000" };
const std::string Pattern5_v1[] = {
"000000001111111111111",
"000011111111111111110",
"000011111111111111110",
"000111110000000000000",
"001111100000000000000",
"001111111111000000000",
"011111111111111100000",
"000000011111111111000",
"000000000000111111100",
"000000000000001111110",
"000000000000000111111",
"000000000000000111111",
"000000000000000111111",
"000000000000000111110",
"000000000000011111110",
"111110000001111111000",
"111111111111111000000",
"000011111110000000000" };
const std::string Pattern5_v2[] = {
"0001111111111111110000000",
"0000001111111111111111000",
"0000111111100000001111110",
"0000001111100000000111100",
"0000111111111111100000000",
"0000110000001111111110000",
"0000000000001111111111100",
"0000000000001111111111110",
"0000000000001111111111111",
"0000000000001111111111111",
"1111000000000011111111111",
"1100000000000001111111111",
"1111000000000001111111111",
"0111110000000001111111111",
"0111000000001111111111110",
"0011110110000111111111100",
"0000111111111111111110000",
"0000000111111111100000000" };
const std::string Pattern6_v1[] = {
"000000000000000110000000",
"000000011111111110000000",
"000001111111111000000000",
"000011111111100000000000",
"000111111110000000000000",
"011111111100000000000000",
"011111111111111111110000",
"111111111111111111111000",
"111111111111111111111110",
"111111111110011111111111",
"111111110000000111111111",
"111111111000000011111111",
"111111111100000001111111",
"011111111110000001111110",
"001111111111100001111000",
"000111111111111111100000",
"000001111111111110000000",
"000000011111100000000000"  };
const std::string Pattern6_v2[] = {
"000000000000111111111000",
"000000000111110000000000",
"000001111000000000000000",
"000111100000000000000000",
"000110000000000000000000",
"001110000000000000000000",
"001000000000000000000000",
"111000011111111110000000",
"111001100000000111111000",
"111000000000000000011111",
"111000000000000000000111",
"111000000000000000000111",
"111000000000000000000111",
"001000000000000000000111",
"001110000000000000011100",
"000110000000000000011100",
"000001111000000111111000",
"000000011111111110000000"  };
const std::string Pattern7_v1[] = {
"00011111111111111111111",
"00011111111111111111110",
"00111111111111111111110",
"01100000000000011111100",
"10000000000000111111100",
"00000000000001111111000",
"00000000000011111110000",
"00000000000011111100000",
"00000000000111111100000",
"00000000001111111000000",
"00000000011111110000000",
"00000000111111100000000",
"00000000111111000000000",
"00000001111111000000000",
"00000001111110000000000",
"00000011111100000000000",
"00000111111100000000000",
"00000111111000000000000" };
const std::string Pattern8_v1[] = {
"000001111111111100000",
"001111111111111111100",
"011111000001111111110",
"011111000000001111111",
"011111000000000111110",
"011111110000001111100",
"001111111100111111000",
"000011111111111100000",
"000001111111111000000",
"000011111111111110000",
"000111110001111111100",
"001111100000011111110",
"011111000000001111111",
"111111100000000011111",
"011111100000000001111",
"001111111000000011110",
"000111111111111111100",
"000001111111111110000" };
const std::string Pattern8_v2[] = {
"000000111111111100000",
"000111101110001111000",
"001110001100000011100",
"001100011100000001110",
"011100011100000001110",
"001100001110000001100",
"000110000011100111000",
"000011000001111100000",
"000001110000011110000",
"000111111100000111000",
"001110000111000001110",
"011100000011100000110",
"111000000000011000111",
"111000000000011000111",
"011000000000011000111",
"011100000000011001110",
"001111000000111111100",
"000011111111111110000" };
const std::string Pattern9_v1[] = {
"00000111111111110000000",
"00011111111111111110000",
"01111111000000111111000",
"01111100000000011111110",
"11111110000000000111110",
"11111110000000000111111",
"11111110000000000111111",
"11111110000000000111111",
"11111111100000000111111",
"00111111111111111111111",
"00001111111111001111110",
"00000000000000011111110",
"00000000000000011111100",
"00000000000000111111100",
"01000000000011111110000",
"01111110001111111100000",
"00111111111111100000000",
"00000111111110000000000" };

class TImage;
typedef std::vector<double> TDoubleVector;
typedef std::vector<TDoubleVector> TImageContainer;
typedef std::list<TImage> TImages;

typedef std::vector<std::vector<int> > TPatternForNum;
typedef std::list<TPatternForNum> TPatternsForNum;
typedef std::vector<TPatternsForNum> TPatterns;

inline TPointF GeneralMap(const double FromW, const double FromH, const TPointF &FromP, const double ToW, const double ToH)
   {
      const double XRelVal = FromP.x() / FromW, YRelVal = FromP.y() / FromH;
      return TPointF(XRelVal * ToW, YRelVal * ToH);
   }

class TDigitInfo
   {
      const int m_Digit;
      const double m_HamingDistance;
   public:
      TDigitInfo(const int digit, const double hamdist): m_Digit(digit), m_HamingDistance(hamdist) { }
      int Digit() const { return m_Digit; }
      double HamDist() const { return m_HamingDistance; }
   };

//==============================================================================================================================================================
//==============================================================================================================================================================

class TImage: public TImageContainer
   {
   public:
      TImage() { }
      TImage(TImageContainer::size_type n, const TImageContainer::value_type & value = TImageContainer::value_type()):
         TImageContainer(n, value) { }

      void DeleteColumn(const TImageContainer::size_type Col);
      void Fill(const TRect &Rect, const double Value);
      TImage Scaled(const int Width, const int Height) const;
      double HammingDistance(const TPatternForNum &Pattern) const;
      void RemoveEmptySpace();
      void AddValue(TImageContainer::size_type XPos, TImageContainer::size_type YPos, double Value);
      bool empty() const;
      bool OutLineIsEmppty(const TRect &Outline, const double WhiteIs = LightGray) const;
   };

std::ostream &operator<<(std::ostream &Out, const TImage &Img)
   {
      for(unsigned int Str = 0; Str < Img.size(); Str++)
         {
            for(unsigned int Col = 0; Col < Img[Str].size(); Col++)
               Out << (Img[Str][Col] == 2 ? 2 : bool(Img[Str][Col]));
            Out << std::endl;
         }
      Out << "End of image" << std::endl;
      return Out;
   }
std::ostream &operator<<(std::ostream &Out, const TImages &Imgs)
   {
      for(TImages::const_iterator It = Imgs.begin(); It != Imgs.end(); It++)
         Out << *It << std::endl;
      return Out;
   }

void TImage::DeleteColumn(const TImageContainer::size_type Col)
   {
      for(TImageContainer::size_type Y = 0; Y < (*this).size(); Y++)
         (*this)[Y].erase((*this)[Y].begin() + Col);
   }
void TImage::Fill(const TRect &Rect, const double Value)
   {
      for(TImageContainer::size_type YInd = Rect.top(); YInd < (unsigned int)Rect.bottom(); YInd++)
         for(TImageContainer::size_type XInd = Rect.left(); XInd < (unsigned int)Rect.right(); XInd++)
            (*this)[YInd][XInd] = Value;
   }
TImage TImage::Scaled(const int Width, const int Height) const
   {
      const TImageContainer::size_type SrcW = (*this)[0].size();
      const TImageContainer::size_type SrcH = (*this).size();

      TImage Result(Height);
      std::fill(Result.begin(), Result.end(), TDoubleVector(Width, 0));

      for(TImageContainer::size_type YInd = 0; YInd < (*this).size(); YInd++)
         {
            for(TImageContainer::size_type XInd = 0; XInd < (*this)[0].size(); XInd++)
               {
                  if(!(*this)[YInd][XInd]) continue;
                  TPointF TopLeft = GeneralMap(SrcW, SrcH, TPointF(XInd, YInd), Width, Height);
                  TPointF BottomRight = GeneralMap(SrcW, SrcH, TPointF(XInd + 1, YInd + 1), Width, Height);
                  Result.Fill(TRect(TopLeft.toPoint(), BottomRight.toPoint()), (*this)[YInd][XInd]);
               }
         }
      return Result;
   }
double TImage::HammingDistance(const TPatternForNum &Pattern) const
   {
      const TImage &ScaledImg = ((*this).size() != Pattern.size() || (*this)[0].size() != Pattern[0].size()) ? Scaled(Pattern[0].size(), Pattern.size()) : *this;
      //Cout(Img);
      double R = 0;
      for(TImageContainer::size_type Y = 0; Y < ScaledImg.size(); Y++)
         for(TImageContainer::size_type X = 0; X < ScaledImg[0].size(); X++)
            if(bool(ScaledImg[Y][X]) != bool(Pattern[Y][X])) ++R;
      return 1000000. / (1 + R*R);
   }
void TImage::RemoveEmptySpace()
   {
      //Empty space at top
      for(size_type YInd = 0; YInd < size(); YInd++)
         {
            bool RowIsEmpty = true;
            for(TImageContainer::size_type XInd = 0; XInd < (*this)[0].size(); XInd++)
               if((*this)[YInd][XInd])
                  { RowIsEmpty = false; break; }
            if(RowIsEmpty) erase(begin() + YInd--);
            else break;
         }
      //Empty space at bottom
      for(TImageContainer::size_type YInd = size() - 1; ; YInd--)
         {
            bool RowIsEmpty = true;
            for(TImageContainer::size_type XInd = 0; XInd < (*this)[0].size(); XInd++)
               if((*this)[YInd][XInd])
                  { RowIsEmpty = false; break; }
            if(RowIsEmpty) erase(begin() + YInd);
            else break;
            if(!YInd) break;
         }
      //Empty space at left
      for(TImageContainer::size_type XInd = 0; XInd < (*this)[0].size(); XInd++)
         {
            bool ColIsEmpty = true;
            for(TImageContainer::size_type YInd = 0; YInd < size(); YInd++)
               if((*this)[YInd][XInd])
                  { ColIsEmpty = false; break; }
            if(ColIsEmpty) DeleteColumn(XInd--);
            else break;
         }
      //Empty space at right
      for(TImageContainer::size_type XInd = (*this)[0].size() - 1; ; XInd--)
         {
            bool ColIsEmpty = true;
            for(TImageContainer::size_type YInd = 0; YInd < size(); YInd++)
               if((*this)[YInd][XInd])
                  { ColIsEmpty = false; break; }
            if(ColIsEmpty) DeleteColumn(XInd);
            else break;
            if(!XInd) break;
         }
   }
void TImage::AddValue(TImageContainer::size_type XPos, TImageContainer::size_type YPos, double Value)
   {
      if(size() <= YPos) resize(YPos + 1);
      if((*this)[YPos].size() <= XPos) (*this)[YPos].resize(XPos + 1);
      (*this)[YPos][XPos] = Value;
   }
bool TImage::empty() const
   {
      if(TImageContainer::empty()) return true;
      if(size() < MinDigitHeight) return true;

      size_type MaxWidth = 0;
      bool ThereIsNotZero = false;
      for(size_type YInd = 0; YInd < size(); YInd++)
         {
            if(MaxWidth < (*this)[YInd].size()) MaxWidth = (*this)[YInd].size();
            if(!ThereIsNotZero)
               for(TImageContainer::size_type XInd = 0; XInd < (*this)[YInd].size(); XInd++)
                  if(!(*this)[YInd][XInd]) { ThereIsNotZero = true; break; }
         }
      if(MaxWidth < MinDigitWidth) return true;
      return !ThereIsNotZero;
   }
bool TImage::OutLineIsEmppty(const TRect &Outline, const double WhiteIs) const
   {
      // >
      for(size_type XInd = Outline.left(); int(XInd) < Outline.right(); XInd++)
        if((*this)[Outline.top()][XInd] <= Black && (*this)[Outline.top()][XInd] > WhiteIs) return false;
      // V
      for(size_type YInd = Outline.top(); int(YInd) < Outline.bottom(); YInd++)
        if((*this)[YInd][Outline.right()] <= Black && (*this)[YInd][Outline.right()] > WhiteIs) return false;
      // <
      for(size_type XInd = Outline.right(); int(XInd) > Outline.left(); XInd--)
        if((*this)[Outline.bottom()][XInd] <= Black && (*this)[Outline.bottom()][XInd] > WhiteIs) return false;
      // ^
      for(size_type YInd = Outline.bottom(); int(YInd) > Outline.top(); YInd--)
        if((*this)[YInd][Outline.left()] <= Black && (*this)[YInd][Outline.left()] > WhiteIs) return false;
      return true;
   }

//==============================================================================================================================================================
//==============================================================================================================================================================

class TExtractor
   {
      typedef std::list<TPoint> TPointList;
      TPointList Bound;
      bool NextDigitFound;

      const double SeparateFlag;
      int GetLeftEmptyPos(const TImage &Image, const double EmptyC, const TImageContainer::size_type StartX, const TImageContainer::size_type YInd) const;
      int GetRightEmptyPos(const TImage &Image, const double EmptyC, const TImageContainer::size_type StartX, const TImageContainer::size_type YInd) const;
      inline void HorizFillByFlags(TPointList &Points, const TImageContainer::size_type YInd, const TImageContainer::size_type FromX, const TImageContainer::size_type ToX) const;
      void FillByFlags(TImage &Image, const TPointList &Points) const;

      bool IsItNoise(const TImageContainer::size_type XInd, const TImageContainer::size_type YInd, TImage &Image) const;
      void RemoveNoise(TImage &Image) const;
      void RemoveEmptySpace(TImage &Image) const;
      void MakeDigitsNarrower(TImage &Image) const;
      bool TrySeparate(TImage &Image, const double EmptyC, TImageContainer::size_type XPos);
      void SeparateDigitByFlags(TImage &Image);
      TImages Extract(const TImage &FlagedImage) const;
      void MakeCorrectShape(TImage &Image) const;
      void TryIsolate(TImage &Image) const;
   public:
      TExtractor(): SeparateFlag(2.) { }
      TImages DoSegmentation(const TImage &SrcImage);
   };

void TExtractor::MakeDigitsNarrower(TImage &Image) const
   {
      const double WhiteIs = LightGray;
      for(TImageContainer::size_type YInd = 0; YInd < Image.size(); YInd++)
         for(TImageContainer::size_type XInd = 0; XInd < Image[0].size(); XInd++)
            if(Image[YInd][XInd] <= WhiteIs) Image[YInd][XInd] = 0;
   }
bool TExtractor::IsItNoise(const TImageContainer::size_type XInd, const TImageContainer::size_type YInd, TImage &Image) const
   {
      const TImageContainer::size_type Left = qBound(int(0), int(XInd - 1), int(Image[0].size()));
      const TImageContainer::size_type Right = qBound(int(0), int(XInd + 2), int(Image[0].size()));
      const TImageContainer::size_type Top = qBound(int(0), int(YInd - 1), int(Image.size()));
      const TImageContainer::size_type Bottom = qBound(int(0), int(YInd + 2), int(Image.size()));
      //std::cout << "Left = " << Left << " Right = " << Right << " Top = " << Top << " Bottom = " << Bottom << "   " << XInd << " " << YInd << std::endl;
      for(TImageContainer::size_type Y = Top; Y < Bottom; Y++)
         for(TImageContainer::size_type X = Left; X < Right; X++)
            {
               //std::cout << X << " " << Y << std::endl;
               if((X != XInd || Y != YInd) && Image[Y][X])
                  {
                     //std::cout << "NOT noise" << std::endl;
                     return false;
                  }
            }
      //std::cout << "This is noise!!!" << std::endl;
      return true;
   }
void TExtractor::RemoveNoise(TImage &Image) const
   {
      const double WhiteIs = LightGray;
      for(TImageContainer::size_type YInd = 0; YInd < Image.size(); YInd++)
         for(TImageContainer::size_type XInd = 0; XInd < Image[0].size(); XInd++)
            {
               //std::cout << XInd << " " << YInd << " " << Image[YInd][XInd] << std::endl;
               if(Image[YInd][XInd] > WhiteIs && IsItNoise(XInd, YInd, Image)) Image[YInd][XInd] = White;
            }
   }
int TExtractor::GetLeftEmptyPos(const TImage &Image, const double EmptyC, const TImageContainer::size_type StartX, const TImageContainer::size_type YInd) const
   {
      for(TImageContainer::size_type XInd = StartX; ; XInd--)
         {
            if((Image[YInd][XInd] > EmptyC && Image[YInd][XInd] <= 1) || !XInd) return -1;
            else if(Image[YInd + 1][XInd] <= EmptyC || Image[YInd + 1][XInd] > Black) return int(XInd);
         }
      return -1;
   }
int TExtractor::GetRightEmptyPos(const TImage &Image, const double EmptyC, const TImageContainer::size_type StartX, const TImageContainer::size_type YInd) const
   {
      for(TImageContainer::size_type XInd = StartX; ; XInd++)
         {
            if((Image[YInd][XInd] > EmptyC && Image[YInd][XInd] <= 1) || XInd == Image[0].size() - 1) return -1;
            if(Image[YInd + 1][XInd] <= EmptyC || Image[YInd + 1][XInd] > Black) return int(XInd);
         }
      return -1;
   }
void TExtractor::HorizFillByFlags(TPointList &Points, const TImageContainer::size_type YInd, const TImageContainer::size_type FromX, const TImageContainer::size_type ToX) const
   {
      for(TImageContainer::size_type X = FromX; X < ToX; Points.push_back(TPoint(X++, YInd)));
   }
void TExtractor::FillByFlags(TImage &Image, const TPointList &Points) const
   {
      for(TPointList::const_iterator It = Points.begin(); It != Points.end(); It++)
         Image[It->y()][It->x()] = SeparateFlag;
   }
bool TExtractor::TrySeparate(TImage &Image, const double EmptyC, TImageContainer::size_type XPos)
   {
      TPointList SupposedBound;
      TImageContainer::size_type YInd = 0;
      for(; YInd < Image.size() - 1; YInd++)
         {
            //std::cout << "Now at " << XPos << " " << YInd << "            ";
            if(Image[YInd][XPos] > EmptyC && Image[YInd][XPos] <= 1)
               { NextDigitFound = true; break; }
            SupposedBound.push_back(TPoint(XPos, YInd));
            if(Image[YInd + 1][XPos] > EmptyC && Image[YInd + 1][XPos] <= 1)
               {
                  const int LeftEmptyPos = GetLeftEmptyPos(Image, EmptyC, XPos, YInd);
                  const int RightEmptyPos = GetRightEmptyPos(Image, EmptyC, XPos, YInd);
                  //std::cout << "LeftEmptyPos = " << LeftEmptyPos << "  RightEmptyPos = " << RightEmptyPos << "  at " << XPos << " " << YInd << std::endl;
                  if(LeftEmptyPos != -1 && RightEmptyPos != -1) { NextDigitFound = true; break; }
                  if(LeftEmptyPos == -1 && RightEmptyPos == -1) { NextDigitFound = true; break; }

                  if(LeftEmptyPos != -1) { HorizFillByFlags(SupposedBound, YInd, LeftEmptyPos, XPos); XPos = LeftEmptyPos; }
                  else                   { HorizFillByFlags(SupposedBound, YInd, XPos + 1, RightEmptyPos + 1); XPos = RightEmptyPos; }
               }

         }
      if(YInd == Image.size() - 1 && NextDigitFound)
         {
            SupposedBound.push_back(TPoint(XPos, YInd));
            FillByFlags(Image, SupposedBound);
            //std::cout << "Boun filled!!!!" << " at " << XPos << " " << YInd << std::endl;
            NextDigitFound = false;
            return true;
         }
      return false;
   }
void TExtractor::SeparateDigitByFlags(TImage &Image)
   {
      TDoubleVector EmptyColours;
      //EmptyColours.push_back(0);
      EmptyColours.push_back(LightGray);
      //EmptyColours.push_back(0.75);

      Bound.clear();
      NextDigitFound = true;
      for(TImageContainer::size_type XInd = 0; XInd < Image[0].size(); XInd++)
         {
            for(TDoubleVector::const_iterator EmptyColour = EmptyColours.begin(); EmptyColour != EmptyColours.end(); EmptyColour++)
               if(TrySeparate(Image, *EmptyColour, XInd)) break;
         }
      //std::cout << Image;
   }
void TExtractor::MakeCorrectShape(TImage &Image) const
   {
      TImageContainer::size_type MaxLength = 0;
      for(TImageContainer::size_type YInd = 0; YInd < Image.size(); YInd++)
         if(MaxLength < Image[YInd].size()) MaxLength = Image[YInd].size();
      for(TImageContainer::size_type YInd = 0; YInd < Image.size(); YInd++)
         Image[YInd].resize(MaxLength, 0);
   }
void TExtractor::TryIsolate(TImage &Image) const
   {
      TRect EmptyOutline;
      bool EmptyOutlineFound = false;
      for(TImage::size_type Left = 0, Right = Image[0].size(), Top = 0, Bottom = Image.size();
          Right - Left >= MinDigitWidth && Bottom - Top >= MinDigitHeight;
          Left++, Right--, Top++, Bottom--)
         {
            EmptyOutline = TRect(Left, Top, Right - Left, Bottom - Top);
            if(Image.OutLineIsEmppty(EmptyOutline)) { EmptyOutlineFound = true; break; }
         }
      if(!EmptyOutlineFound) return;

      TImage NewImage;
      for(TImageContainer::size_type YInd = EmptyOutline.top(); int(YInd) < EmptyOutline.bottom(); YInd++)
         {
            NewImage.push_back(TDoubleVector());
            for(TImageContainer::size_type XInd = EmptyOutline.left(); int(XInd) < EmptyOutline.right(); XInd++)
               NewImage.back().push_back(Image[YInd][XInd]);
         }
      Image = NewImage;
      Image.RemoveEmptySpace();
   }
TImages TExtractor::Extract(const TImage &FlaggedImage) const
   {
      TImages Images;
      TImages::iterator CurrentImage;
      TImages::size_type CurrentDigit = 0;
      bool ThereWasNotFlag = true;
      for(TImageContainer::size_type YInd = 0; YInd < FlaggedImage.size(); YInd++)
         {
            CurrentImage = Images.begin();
            CurrentDigit = 0;
            for(TImageContainer::size_type XInd = 0; XInd < FlaggedImage[0].size(); XInd++)
               {
                  if(CurrentDigit + 1 > Images.size())
                     {
                        Images.push_back(TImage());
                        CurrentImage = Images.end();
                        --CurrentImage;
                     }
                  CurrentImage->AddValue(XInd, YInd, FlaggedImage[YInd][XInd] == SeparateFlag ? 0 : FlaggedImage[YInd][XInd]);

                  if(FlaggedImage[YInd][XInd] == SeparateFlag)
                     {
                        if(ThereWasNotFlag)
                           {
                              ++CurrentDigit;
                              ++CurrentImage;
                              ThereWasNotFlag = false;
                           }
                     }
                     else ThereWasNotFlag = true;
               }
            ThereWasNotFlag = true;
         }
      for(TImages::iterator It = Images.begin(); It != Images.end(); )
         {
            if(It->empty()) It = Images.erase(It);
            else
               {
                  MakeCorrectShape(*It);
                  It->RemoveEmptySpace();
                  TryIsolate(*It);
                  ++It;
               }
         }
      return Images;
   }
TImages TExtractor::DoSegmentation(const TImage &SrcImage)
   {
      TImage Image = SrcImage;
      MakeDigitsNarrower(Image);
      RemoveNoise(Image);
      SeparateDigitByFlags(Image);
      return Extract(Image);
   }

//==============================================================================================================================================================
//==============================================================================================================================================================

class TRecognizer
   {
      TPatterns AllPatterns;
      TImage SrcImage;
      std::string Result;

      template <class T>
      void AddPatern(TPatternsForNum &List, const T &Array);

      void InitPatterns();
      void InitImage();
      TDigitInfo Compare(const TImage &Img);

      TExtractor Extractor;
   public:
      TRecognizer();
      void Recognize();
      const std::string &GetResult() const { return Result; }
   };

TRecognizer::TRecognizer()
   {
      InitPatterns();
      InitImage();
      SrcImage.RemoveEmptySpace();
   }
template <class T>
void TRecognizer::AddPatern(TPatternsForNum &List, const T &Array)
   {
      const unsigned int ArrSize = sizeof(Array) / sizeof(*Array);
      const unsigned int Width = Array[0].size();
      List.push_back(TPatternForNum());
      TPatternForNum &Pattern = List.back();
      Pattern.resize(ArrSize);
      for(unsigned int Str = 0; Str < ArrSize; Str++)
         for(unsigned int Col = 0; Col < Width; Col++)
            Pattern[Str].push_back(Array[Str][Col] == '0' ? 0 : 1);
   }
void TRecognizer::InitPatterns()
   {
      AllPatterns.resize(10);
      AddPatern(AllPatterns[0], Pattern0_v1);
      AddPatern(AllPatterns[1], Pattern1_v1);
      AddPatern(AllPatterns[2], Pattern2_v1);
      AddPatern(AllPatterns[3], Pattern3_v1);
      AddPatern(AllPatterns[4], Pattern4_v1); AddPatern(AllPatterns[4], Pattern4_v2); AddPatern(AllPatterns[4], Pattern4_v3);
      AddPatern(AllPatterns[5], Pattern5_v1); AddPatern(AllPatterns[5], Pattern5_v2);
      AddPatern(AllPatterns[6], Pattern6_v1); AddPatern(AllPatterns[6], Pattern6_v2);
      AddPatern(AllPatterns[7], Pattern7_v1);
      AddPatern(AllPatterns[8], Pattern8_v1); AddPatern(AllPatterns[8], Pattern8_v2);
      AddPatern(AllPatterns[9], Pattern9_v1);
   }
void TRecognizer::InitImage()
   {
      SrcImage.resize(SrcImage.size() + 1);
      for(char Ch; std::cin.get(Ch); )
         {
            if(Ch == '.')       SrcImage.back().push_back(White);
            else if(Ch == '%')  SrcImage.back().push_back(LightGray);
            else if(Ch == '#')  SrcImage.back().push_back(DarkGray);
            else if(Ch == '@')  SrcImage.back().push_back(Black);
            else if(Ch == '\n') SrcImage.resize(SrcImage.size() + 1);
         }
      if(SrcImage.back().empty()) SrcImage.pop_back();
   }
TDigitInfo TRecognizer::Compare(const TImage &Img)
   {
      double MaxHamPot = -1;
      int FoundDigit = 0;
      for(TPatterns::size_type Digit = 0; Digit < AllPatterns.size(); Digit++)
         {
            const TPatternsForNum &PatternsForNum = AllPatterns[Digit];
            double Tmp;
            for(TPatternsForNum::const_iterator PatIt = PatternsForNum.begin(); PatIt != PatternsForNum.end(); PatIt++)
               {
                  if((Tmp = Img.HammingDistance(*PatIt)) > MaxHamPot)
                     { MaxHamPot = Tmp; FoundDigit = Digit; }
                  //std::cout << Tmp << " " << Digit << std::endl;
               }
         }
      return TDigitInfo(FoundDigit, MaxHamPot);
   }
void TRecognizer::Recognize()
   {
      const TImages &Digits = Extractor.DoSegmentation(SrcImage);
      //std::cout << Digits;
      for(TImages::const_iterator It = Digits.begin(); It != Digits.end(); It++)
         {
            TDigitInfo Info = Compare(*It);
            Result += static_cast<std::ostringstream*>( &(std::ostringstream() << Info.Digit()))->str();
         }
   }

}

//==============================================================================================================================================================
//==============================================================================================================================================================

int main(int argc, char *argv[])
   {
      Q_UNUSED(argc); Q_UNUSED(argv);
      try
         {
            ocr::TRecognizer Recognizer;
            Recognizer.Recognize();
            std::cout << Recognizer.GetResult();
         }
      catch(const std::exception &e)
         {
            std::cout << "Exception was generated: " << std::endl << e.what() << std::endl;
         }
      catch(...)
         {
            std::cout << "Undefined exception!" << std::endl;
         }
      return 0;
   }


//260
/*
Academy Ho
AdverGothicCTT
Astra
Betina Script
Bravo Cyr
CasperOpenFace
Chance
Colonna MT
CorridaCTDictionary
Countdown
CricketHeavy
Decor
ErasUltra
FatFaceCTT
FuturaEugenia
Garamondcond-Bold-Italic
GRANIT Rus
Harpoon
Ireland
Koala

Matisse ITC
Mistral
NERVOUS
NewZelek
NinaCTT
Roughew Light
Shotgun BT
SINALOA Rus
Start
STICK
Swan
TagirCTT
TauernCTT
Ukrainian?Present
University
*/
