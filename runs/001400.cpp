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
typedef std::vector<TListChar> TCharsVector;           //For Phone keys
typedef std::pair<std::string, TReoccurrFreq> TPairStrD;
typedef std::vector<TPairStrD> TVectDict; //Dictionary in std::vector (Word, reoccurence frequency)
typedef std::list<TPairStrD> TListDict; //Dictionary in std::vector (Word, reoccurence frequency)
typedef TListDict TDictionary;
typedef std::list<TDictionary::const_iterator> TConstIterList;
typedef std::vector<TDictionary::const_iterator> TConstIterVector;

TDictionary MainDictionary;

namespace t9 {

typedef std::list<std::string> TStringList;
typedef std::vector<double> TDoubleVector;
typedef std::vector<int> TIntVector;


const double Epsilon = 1./100000.;
TDoubleVector MaxReoccFreqs(52000, -Epsilon);

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

      TCharsVector PhoneKeys;
      const std::string &SrcStr;   // "123 234234234**1" for example

      std::string::size_type CurrentPos;
      TConstIterList ExpectedWords;
      int PhoneKey;
      std::string ConvertResult;
      unsigned int StarCount;

      //TIntVector Cheat;
      //inline void FillCheat(const std::string::size_type Size);
      //QTime Time;

      static TCharType DefineCharType(const char Ch);

      //Deletes word longer than MaxLength from ExpW
      void CopyWordsWithLength(TConstIterList &ExpW, const std::string::size_type Length);

      //Deletes from Dict all unrelated words
      void DeleteUnrelatedWords(TConstIterList &Dict, const int PhoneKey, const std::string::size_type CurrentPos) const;

      //Returns Appropriate Punctuation Mark
      void AddAppropriatePunctuationMark(const unsigned int StarCount = 0);

      //Returns Appropriate word and take into account reocurrence frequency
      void AddAppropriateWord(const TConstIterList &ExpW, const unsigned int StarCount = 0);
      void SortAlphabetical(TConstIterVector &Vector, const TReoccurrFreq ReoccurrFreq) const;
      //void HandleOldMajorRange(const TVectDict &Vector, const TReoccurrFreq ReoccurrFreq) const;
      void HandleNewMajorRange(const TReoccurrFreq ReoccurrFreq, const std::string &Word) const;

      void SplitIntoLexems(TStringList &Result) const;
      void Convert(const std::string &Lexeme);
   public:
      TConverter(const std::string &s); //Init
      void DoConvert();                 //convert numbers into words
      std::string GetConvertResult() const { return ConvertResult; }
   };

//==============================================================================================================================================================
//==============================================================================================================================================================

TConverter::TConverter(const std::string &s): SrcStr(s)
   {
      PhoneKeys.resize(9);
      PhoneKeys[0].push_back('.'); PhoneKeys[0].push_back(','); PhoneKeys[0].push_back('?');
      PhoneKeys[1].push_back('a'); PhoneKeys[1].push_back('b'); PhoneKeys[1].push_back('c');
      PhoneKeys[2].push_back('d'); PhoneKeys[2].push_back('e'); PhoneKeys[2].push_back('f');
      PhoneKeys[3].push_back('g'); PhoneKeys[3].push_back('h'); PhoneKeys[3].push_back('i');
      PhoneKeys[4].push_back('j'); PhoneKeys[4].push_back('k'); PhoneKeys[4].push_back('l');
      PhoneKeys[5].push_back('m'); PhoneKeys[5].push_back('n'); PhoneKeys[5].push_back('o');
      PhoneKeys[6].push_back('p'); PhoneKeys[6].push_back('q'); PhoneKeys[6].push_back('r'); PhoneKeys[6].push_back('s');
      PhoneKeys[7].push_back('t'); PhoneKeys[7].push_back('u'); PhoneKeys[7].push_back('v');
      PhoneKeys[8].push_back('w'); PhoneKeys[8].push_back('x'); PhoneKeys[8].push_back('y'); PhoneKeys[8].push_back('z');
   }
TConverter::TCharType TConverter::DefineCharType(const char Ch)
   {
      if(Ch == ' ') return CT_Space;
      if(Ch == '*') return CT_Star;
      if(Ch == '1') return CT_PunctuationMark;
      return CT_Digit;
   }
void TConverter::DeleteUnrelatedWords(TConstIterList &Dict, const int PhoneKey, const std::string::size_type CurrentPos) const
   {
      const TListChar &ListChar = PhoneKeys[PhoneKey - 1];
      bool NothingCoincide;;
      TListChar::const_iterator ButtonCharsIt;
      for(TConstIterList::iterator DictIt = Dict.begin(); DictIt != Dict.end(); )
         {
            NothingCoincide = true;
            for(ButtonCharsIt = ListChar.begin(); ButtonCharsIt != ListChar.end(); ButtonCharsIt++)
               if(*ButtonCharsIt == (*DictIt)->first[CurrentPos])
                  { NothingCoincide = false; break; }

            if(NothingCoincide) DictIt = Dict.erase(DictIt);
            else ++DictIt;
         }
   }
void TConverter::CopyWordsWithLength(TConstIterList &ExpW, const std::string::size_type Length)
   {
      for(TDictionary::const_iterator It = MainDictionary.begin(); It != MainDictionary.end(); It++)
         if(It->first.size() == Length)
            ExpW.push_back(It);
   }
void TConverter::AddAppropriatePunctuationMark(const unsigned int StarCount)
   {
      if(StarCount == 0) ConvertResult.push_back('.');
      else if(StarCount == 1) ConvertResult.push_back(',');
      else if(StarCount == 2) ConvertResult.push_back('?');
   }
void TConverter::AddAppropriateWord(const TConstIterList &ExpW, const unsigned int StarCount)
   {
      //Some checks
      if(ExpW.empty()) return;

      //Add appropriate word
      TConstIterVector TempVectDict;
      for(TConstIterList::const_iterator It = ExpW.begin(); It != ExpW.end(); TempVectDict.push_back(*It++));
      std::sort(TempVectDict.begin(), TempVectDict.end(), TCompareReoccurrFreq);
      const TReoccurrFreq ReoccurrFreq = (*(TempVectDict.begin() + StarCount))->second;
      SortAlphabetical(TempVectDict, ReoccurrFreq);
      const std::string Result = (*(TempVectDict.begin() + StarCount))->first;
      ConvertResult += Result;

      //Change ReoccurrFreq
      HandleNewMajorRange(ReoccurrFreq, Result);
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
      char Ch;
      bool ThisIsLastSymbol;
      TCharType CurrentType, NextType;
      for(std::string::size_type CurrentPos = 0; CurrentPos < SrcStr.size(); CurrentPos++)
         {
            Ch = SrcStr[CurrentPos];
            ThisIsLastSymbol = CurrentPos == SrcStr.size() - 1;
            Lexeme.push_back(Ch);

            CurrentType = DefineCharType(Ch);
            NextType = CT_None;
            if(CurrentPos + 1 < SrcStr.size())
               NextType = DefineCharType(SrcStr[CurrentPos + 1]);

            if(ThisIsLastSymbol)
               {
                  Result.push_back(Lexeme);
                  Lexeme.clear();
                  continue;
               }
            else if(NextType == CT_Space
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
/*void TConverter::FillCheat(const std::string::size_type Size)
   {
      Cheat.clear();
      for(std::string::size_type Counter = 0; Counter < Size; Counter++) Cheat.push_back(Counter);
      std::random_shuffle(Cheat.begin(), Cheat.end());
   }*/
void TConverter::Convert(const std::string &Lexeme)
   {
      //if Space
      if(Lexeme[0] == ' ')
         { ConvertResult.push_back(' '); return; }

      StarCount = 0; //std::count(Lexeme.begin(), Lexeme.end(), '*');
      for(std::string::size_type Counter = Lexeme.size() - 1; ; Counter--)
         {
            if(Lexeme[Counter] == '*')
               {
                  ++StarCount;
                  if(!Counter) break;
               }
            else break;
         }

      //if Punctuation Mark (+ any number of '*')
      if(Lexeme[0] == '1')
         {  AddAppropriatePunctuationMark(StarCount); return; }

      //if word  (+ any number of '*')
      ExpectedWords.clear();
      CopyWordsWithLength(ExpectedWords, Lexeme.size() - StarCount);
      //FillCheat(Lexeme.size() - StarCount);
      for(CurrentPos = 0; CurrentPos < Lexeme.size() - StarCount; CurrentPos++)
      //for(TIntVector::size_type CheatPos = 0; CheatPos < Cheat.size(); CheatPos++)
         {
            //CurrentPos = Cheat[CheatPos];
            if(Lexeme[CurrentPos] == '2') PhoneKey = 2;
            else if(Lexeme[CurrentPos] == '3') PhoneKey = 3;
            else if(Lexeme[CurrentPos] == '4') PhoneKey = 4;
            else if(Lexeme[CurrentPos] == '5') PhoneKey = 5;
            else if(Lexeme[CurrentPos] == '6') PhoneKey = 6;
            else if(Lexeme[CurrentPos] == '7') PhoneKey = 7;
            else if(Lexeme[CurrentPos] == '8') PhoneKey = 8;
            else if(Lexeme[CurrentPos] == '9') PhoneKey = 9;
            else if(Lexeme[CurrentPos] == '0') PhoneKey = 0;
            DeleteUnrelatedWords(ExpectedWords, PhoneKey, CurrentPos);
         }
      //Time.start();
      //for(int C = 0; C < 200000; C++)
      AddAppropriateWord(ExpectedWords, StarCount);
      //std::cout << std::endl << Time.elapsed();
   }
void TConverter::DoConvert()
   {
      TStringList Lexems;
      SplitIntoLexems(Lexems);
      for(TStringList::const_iterator It = Lexems.begin(); It != Lexems.end(); Convert(*It++));
   }

}

void RecieveData(std::string &SrcStr) //Get data from stdin
   {
      unsigned int NumberOfWords;
      std::cin >> NumberOfWords;

      unsigned int ReoccFreq;
      std::string Word;
      for(unsigned int Counter = 0; Counter < NumberOfWords; Counter++)
         {
            std::cin >> Word >> ReoccFreq;
            t9::MaxReoccFreqs[ReoccFreq] = 0;
            MainDictionary.push_back(TPairStrD(Word, ReoccFreq));
         }
      char Ch;
      std::cin.get(Ch);
      std::getline(std::cin, SrcStr);
   }

int main(int argc, char *argv[])
   {
      Q_UNUSED(argc);  Q_UNUSED(argv);
      std::string SrcStr;
      RecieveData(SrcStr);
      t9::TConverter Converter(SrcStr);
      //QTime Time; Time.start();
      //for(int C = 0; C < 200000; C++)
      Converter.DoConvert();
      //std::cout << std::endl << Time.elapsed();
      std::cout << Converter.GetConvertResult();
      return 0;
   }
