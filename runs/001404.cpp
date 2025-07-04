#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <map>

//#include <QTime>

//Some useful defines from Qt
//Avoid "unused parameter" warnings
#define Q_UNUSED(__x) (void)__x

typedef double TReoccurrFreq;
typedef std::list<char> TListChar;
typedef std::vector<char> TVectorChar;
typedef std::vector<TListChar> TCharsVector;           //For Phone keys
typedef std::pair<std::string, TReoccurrFreq> TPairStrD;
typedef std::list<TPairStrD> TListDict; //Dictionary in std::vector (Word, reoccurence frequency)
typedef TListDict TDictionary;
typedef std::vector<TDictionary::const_iterator> TConstIterVector;
typedef std::multimap<std::string, TDictionary::const_iterator> TMmStrStr;
typedef std::pair<std::string, TDictionary::const_iterator> TPairStrStr;


TDictionary MainDictionary;

namespace t9 {

typedef std::list<std::string> TStringList;
typedef std::vector<double> TDoubleVector;
typedef std::vector<int> TIntVector;


const double Epsilon = 1./100000.;
TDoubleVector MaxReoccFreqs(520000, -Epsilon);

inline bool TCompareReoccurrFreq(const TDictionary::const_iterator &First, const TDictionary::const_iterator &Second)    { return First->second > Second->second; }
inline bool  TCompareReoccurrString(const TDictionary::const_iterator &First, const TDictionary::const_iterator &Second) { return First->first < Second->first; }
inline bool _TCompareReoccurrString(const TPairStrD &First, const TPairStrD &Second)   { return First.first < Second.first; }
inline bool TMajorReoccurrFreqLess(const TPairStrD &First, const TPairStrD &Second)    { return (unsigned int)(First.second) < (unsigned int)(Second.second); }
inline bool TMajorReoccurrFreqGreater(const TPairStrD &First, const TPairStrD &Second) { return (unsigned int)(First.second) > (unsigned int)(Second.second); }
inline bool TReoccurrFreqEqual(const TPairStrD &First, const TPairStrD &Second)        { return First.second < Second.second; }
inline unsigned int ToMajor(const TReoccurrFreq Src)                            { return (unsigned int)(Src); }
inline TDictionary::iterator FindWord(TDictionary &Dict, const std::string &Word)
   {
      return std::lower_bound(Dict.begin(), Dict.end(), TPairStrD(Word, TReoccurrFreq(0)), _TCompareReoccurrString);
   }

//==============================================================================================================================================================
//==============================================================================================================================================================

class TConverter
   {  //                               1              *      23456789    ' '
      enum TCharType { CT_None, CT_PunctuationMark, CT_Star, CT_Digit, CT_Space };

      const TCharsVector &PhoneKeys;
      const std::string &SrcStr;   // "123 234234234**1" for example
      const TVectorChar &InvertedPhoneKeys;
      TMmStrStr NumberToWords;

      std::string::size_type CurrentPos;
      int PhoneKey;
      std::string ConvertResult;
      unsigned int StarCount;
      //QTime Time;

      static TCharType DefineCharType(const char Ch);

      //Returns Appropriate Punctuation Mark
      std::string GetAppropriatePunctuationMark(const unsigned int StarCount = 0) const;

      //Returns Appropriate word and take into account reocurrence frequency
      std::string GetAppropriateWord(const TMmStrStr::const_iterator &First, const TMmStrStr::const_iterator &Last, const unsigned int StarCount) const;
      void SortAlphabetical(TConstIterVector &Vector, const TReoccurrFreq ReoccurrFreq) const;
      void HandleNewMajorRange(const TReoccurrFreq ReoccurrFreq, const std::string &Word) const;

      void SplitIntoLexems(TStringList &Result) const;
      void Convert(const std::string &Lexeme);
   public:
      TConverter(const TCharsVector &PK, const TVectorChar &InvPK, const std::string &s); //Init
      void DoConvert();                 //convert numbers into words
      std::string GetConvertResult() const { return ConvertResult; }
   };

//==============================================================================================================================================================
//==============================================================================================================================================================

TConverter::TConverter(const TCharsVector &PK, const TVectorChar &InvPK, const std::string &s):
      PhoneKeys(PK), SrcStr(s), InvertedPhoneKeys(InvPK)
   {
      std::string WordInDigit;
      for(TDictionary::const_iterator It = MainDictionary.begin(); It != MainDictionary.end(); It++)
         {
            WordInDigit.clear();
            for(std::string::const_iterator StrIt = It->first.begin(); StrIt != It->first.end(); StrIt++)
               WordInDigit.push_back(InvertedPhoneKeys[int(*StrIt) - int('a')]);

            NumberToWords.insert(TPairStrStr(WordInDigit, It));
         }
   }
TConverter::TCharType TConverter::DefineCharType(const char Ch)
   {
      if(Ch == ' ') return CT_Space;
      if(Ch == '*') return CT_Star;
      if(Ch == '1') return CT_PunctuationMark;
      return CT_Digit;
   }
std::string TConverter::GetAppropriatePunctuationMark(const unsigned int StarCount) const
   {
      std::string Result;
      if(StarCount == 0) Result.push_back('.');
      else if(StarCount == 1) Result.push_back(',');
      else if(StarCount == 2) Result.push_back('?');
      return Result;
   }
std::string TConverter::GetAppropriateWord(const TMmStrStr::const_iterator &First, const TMmStrStr::const_iterator &Last, const unsigned int StarCount) const
   {
      //Some checks
      if(Last == First) return std::string();

      //Get appropriate word
      TConstIterVector TempVectDict;
      for(TMmStrStr::const_iterator It = First; It != Last; It++) TempVectDict.push_back(It->second);
      std::sort(TempVectDict.begin(), TempVectDict.end(), TCompareReoccurrFreq);
      const TReoccurrFreq ReoccurrFreq = (*(TempVectDict.begin() + StarCount))->second;
      SortAlphabetical(TempVectDict, ReoccurrFreq);
      const std::string Result = (*(TempVectDict.begin() + StarCount))->first;
      //Change ReoccurrFreq
      HandleNewMajorRange(ReoccurrFreq, Result);

      return Result;
   }
void TConverter::SortAlphabetical(TConstIterVector &Vector, const TReoccurrFreq ReoccurrFreq) const
   {
      //[First; Last) - words with equal ReoccurrFreq
      TDictionary Temp(1, TPairStrD(std::string(), ReoccurrFreq));
      TConstIterVector::iterator First = std::lower_bound(Vector.begin(), Vector.end(), Temp.begin(), TCompareReoccurrFreq);
      TConstIterVector::iterator Last = std::upper_bound(Vector.begin(), Vector.end(), Temp.begin(), TCompareReoccurrFreq);
      std::sort(First, Last, TCompareReoccurrString);
   }
void TConverter::HandleNewMajorRange(const TReoccurrFreq ReoccurrFreq, const std::string &Word) const
   {
      const unsigned int Major = ToMajor(ReoccurrFreq) + 1;  //++Major;
      MaxReoccFreqs[Major] += Epsilon;
      FindWord(MainDictionary, Word)->second = Major + MaxReoccFreqs[Major];
   }
void TConverter::SplitIntoLexems(TStringList &Result) const
   {
      std::string Lexeme;
      for(std::string::size_type CurrentPos = 0; CurrentPos < SrcStr.size(); CurrentPos++)
         {
            const char Ch = SrcStr[CurrentPos];
            Lexeme.push_back(Ch);

            const bool ThisIsLastSymbol = CurrentPos == SrcStr.size() - 1;
            TCharType CurrentType = DefineCharType(Ch);
            TCharType NextType = CT_None;
            if(CurrentPos + 1 < SrcStr.size())
               NextType = DefineCharType(SrcStr[CurrentPos + 1]);

            if(ThisIsLastSymbol)
               {
                  Result.push_back(Lexeme);
                  Lexeme.clear();
                  continue;
               }
            if(NextType == CT_Space
               || NextType == CT_PunctuationMark
               || (CurrentType == CT_Space && NextType != CT_Space)
               || (CurrentType == CT_Star && NextType != CT_Star)
               || (CurrentType == CT_PunctuationMark && NextType != CT_PunctuationMark && NextType != CT_Star))
               {
                  Result.push_back(Lexeme);
                  Lexeme.clear();
                  continue;
               }
         }
   }
void TConverter::Convert(const std::string &Lexeme)
   {
      //if Space
      if(Lexeme[0] == ' ')
         { ConvertResult.push_back(' '); return; }

      //if Punctuation Mark (+ any number of '*')
      StarCount = std::count(Lexeme.begin(), Lexeme.end(), '*');
      if(Lexeme[0] == '1')
         {  ConvertResult += GetAppropriatePunctuationMark(StarCount); return; }

      //if word  (+ any number of '*')
      typedef std::pair<TMmStrStr::const_iterator, TMmStrStr::const_iterator> TPairOfIters;
      const TPairOfIters Range = NumberToWords.equal_range(StarCount ? Lexeme.substr(0, Lexeme.size() - StarCount) : Lexeme);
      ConvertResult += GetAppropriateWord(Range.first, Range.second, StarCount);
   }
void TConverter::DoConvert()
   {
      ConvertResult.clear();
      TStringList Lexems;
      SplitIntoLexems(Lexems);
      for(TStringList::const_iterator It = Lexems.begin(); It != Lexems.end(); Convert(*It++));
   }

}

std::string RecieveData() //Get data from stdin
   {
      unsigned int NumberOfWords;
      std::cin >> NumberOfWords;
      for(unsigned int Counter = 0; Counter < NumberOfWords; Counter++)
         {
            unsigned int ReoccFreq;
            std::string Word;
            std::cin >> Word >> ReoccFreq;
            t9::MaxReoccFreqs[ReoccFreq] = 0;
            MainDictionary.push_back(TPairStrD(Word, ReoccFreq));
         }
      char Ch;
      std::cin.get(Ch);
      std::string SrcStr;
      std::getline(std::cin, SrcStr);
      return SrcStr;
   }

int main(int argc, char *argv[])
   {
      Q_UNUSED(argc);  Q_UNUSED(argv);
      TCharsVector PhoneKeys(9);
      PhoneKeys[0].push_back('.'); PhoneKeys[0].push_back(','); PhoneKeys[0].push_back('?');
      PhoneKeys[1].push_back('a'); PhoneKeys[1].push_back('b'); PhoneKeys[1].push_back('c');
      PhoneKeys[2].push_back('d'); PhoneKeys[2].push_back('e'); PhoneKeys[2].push_back('f');
      PhoneKeys[3].push_back('g'); PhoneKeys[3].push_back('h'); PhoneKeys[3].push_back('i');
      PhoneKeys[4].push_back('j'); PhoneKeys[4].push_back('k'); PhoneKeys[4].push_back('l');
      PhoneKeys[5].push_back('m'); PhoneKeys[5].push_back('n'); PhoneKeys[5].push_back('o');
      PhoneKeys[6].push_back('p'); PhoneKeys[6].push_back('q'); PhoneKeys[6].push_back('r'); PhoneKeys[6].push_back('s');
      PhoneKeys[7].push_back('t'); PhoneKeys[7].push_back('u'); PhoneKeys[7].push_back('v');
      PhoneKeys[8].push_back('w'); PhoneKeys[8].push_back('x'); PhoneKeys[8].push_back('y'); PhoneKeys[8].push_back('z');

      TVectorChar InvertedPhoneKeys(26);
      InvertedPhoneKeys[0] = '2'; InvertedPhoneKeys[1] = '2'; InvertedPhoneKeys[2] = '2';
      InvertedPhoneKeys[3] = '3'; InvertedPhoneKeys[4] = '3'; InvertedPhoneKeys[5] = '3';
      InvertedPhoneKeys[6] = '4'; InvertedPhoneKeys[7] = '4'; InvertedPhoneKeys[8] = '4';
      InvertedPhoneKeys[9] = '5'; InvertedPhoneKeys[10] = '5'; InvertedPhoneKeys[11] = '5';
      InvertedPhoneKeys[12] = '6'; InvertedPhoneKeys[13] = '6'; InvertedPhoneKeys[14] = '6';
      InvertedPhoneKeys[15] = '7'; InvertedPhoneKeys[16] = '7'; InvertedPhoneKeys[17] = '7'; InvertedPhoneKeys[18] = '7';
      InvertedPhoneKeys[19] = '8'; InvertedPhoneKeys[20] = '8'; InvertedPhoneKeys[21] = '8';
      InvertedPhoneKeys[22] = '9'; InvertedPhoneKeys[23] = '9'; InvertedPhoneKeys[24] = '9'; InvertedPhoneKeys[25] = '9';

      std::string SrcStr = RecieveData();
      //QTime Time; Time.start();
      t9::TConverter Converter(PhoneKeys, InvertedPhoneKeys, SrcStr);
      //for(int C = 0; C < 50000; C++)
      Converter.DoConvert();
      //std::cout << std::endl << Time.elapsed();
      std::cout << Converter.GetConvertResult();
      return 0;
   }
