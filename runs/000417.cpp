#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <deque>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <cmath>

#define DIGITS     10
#define IMG_SIDE   14

typedef std::deque<int> image_array;
typedef std::deque<image_array> image_matrix;

//====================================================

std::string deq2str(const std::deque<int> &deq);
std::deque<int> str2deq(const char *str);

//===================== NEURON =======================
class neuron
{
  std::deque<int> w;
  int s;
  int adder(const image_array &x) const;
  int activator(int nec) const
    {
      return (nec >= s) ? 1 : 0;
    }
public:
  neuron(int m) : s(50)
    {
      w.resize(m);
    }
  int transfer(const image_array &x) const
    {
      return activator(adder(x));
    }
  void initWeights(int n);
  void swapWeights(std::deque<int> *weights)
    {
      //std::swap(w, *weights);
      w = *weights;
    }
  void changeWeights(int v, int d, const image_array &x);
  std::string str_weights() const
    {
      return deq2str(w);
    }
  void set_weights(const char *str)
    {
      //std::swap(w, str2deq(str));
      w = str2deq(str);
    }
  bool are_all_weights_nulls() const;
};

//=================== PERCEPTRON =====================
class perceptron
{
  std::deque<neuron> neurons;
public:
  perceptron(int n, int m)
    {
      neurons.resize(n, neuron(m));
    }
  image_array recognize(const image_array &x) const;
  void initWeights();
  int teach(const image_array &x, const image_array &y);
  void set_weight(int neuron, const char *str)
    {
      neurons[neuron].set_weights(str);
    }
  void save_weights(const char *file) const;
};

//=================== RECOGNIZER =====================
class recognizer
{
  perceptron perc;
  image_matrix image;
  image_array samples[DIGITS];
  int pos;

  static bool have_column_black_pixels(image_matrix *matr, int column);
  static void erase_column(image_matrix *matr, int column);
  static void erase_vert_gray_lines(image_matrix *matr);
  static void cut(image_matrix *matr);
  static void addlr(image_matrix *matr);
  void matrix2array(const image_matrix &matr, image_array *arr) const;
  int count_equal(const image_array &arr, int sample) const;
  void fill(image_matrix *img, int i, int j, int *max_j=NULL) const;
  static void make01(image_array *arr);
  image_array next_image();
  void add(int sample, const char *str);
  void sw(int neuron, const char *str)
    {
      perc.set_weight(neuron, str);
    }
public:
  recognizer(int img_side=IMG_SIDE);
  void read_image();
  void set_weights();
  int recognize(const image_array &arr) const;
  void print();

  //----------------------------------------------------
  bool load(image_array *arr, const char *file) const;
  bool load(image_matrix *matr, const char *file) const;
  void print(const image_array &arr) const;
  void set_samples();
  void load_samples_f();
  void teach();
  void teach_samples();
  void save_weights(const char *file="weights") const
    {
      perc.save_weights(file);
    }
  void make_weights_file(const char *file="weights");
  static int sym2num(char ch);
  //----------------------------------------------------
};



//======================================================
//  0 0
//  1 A
// -1 a
char int2char(int i)
{
    if (i == 0) return '0';
    char ch = 'A' + static_cast<char>(abs(i)) - 1;
    return (i > 0) ? ch : tolower(ch);
}

int char2int(char ch)
{
    if (ch == '0') return 0;
    if (ch == '[') return 27;
    if (ch == '\\') return 28;
    int i = toupper(ch) - 'A' + 1;
    return (isupper(ch)) ? i : -i;
}

std::string deq2str(const std::deque<int> &deq)
{
    std::string str;
    str.reserve(deq.size());
    for (size_t i = 0; i < deq.size(); ++i)
        str += int2char(deq[i]);
    return str;
}

std::deque<int> str2deq(const char *str)
{
    std::deque<int> deq;
    while (*str != '\0')
        deq.push_back(char2int(*str++));
    return deq;
}
//======================================================



//===================== NEURON =======================
int neuron::adder(const image_array &x) const
{
  int nec = 0;
  for (size_t i = 0; i < x.size(); i++)
    nec += x[i] * w[i];
  return nec;
}

void neuron::initWeights(int n)
{
  for (size_t i = 0; i < w.size(); i++)
    w[i] = rand() % n;
}

void neuron::changeWeights(int v, int d, const image_array &x)
{
  for (size_t i = 0; i < w.size(); i++)
    w[i] += v*d*x[i];
}

bool neuron::are_all_weights_nulls() const
{
  for (size_t i = 0; i < w.size(); ++i)
  {
      if (w[i] != 0)
          return false;
  }
  return true;
}




//=================== PERCEPTRON =====================
image_array perceptron::recognize(const image_array &x) const
{
  image_array y(neurons.size());

  for (size_t j = 0; j < neurons.size(); j++)
    y[j] = neurons[j].transfer(x);

  return y;
}

void perceptron::initWeights()
{    
  for (size_t j = 0; j < neurons.size(); j++)
    neurons[j].initWeights(10);
}

int perceptron::teach(const image_array &x, const image_array &y)
{
  int i=0;
  int d;
  int v = 1;

  image_array t = recognize(x);
  while (t != y)
  {
    ++i;
    for (size_t j = 0; j < neurons.size(); j++)
    {
      d = y[j] - t[j];
      neurons[j].changeWeights(v, d, x);
    }
    t = recognize(x);
  }

  return i;
}

void perceptron::save_weights(const char *file) const
{
  std::ofstream fout(file);
  for (size_t i = 0; i < neurons.size(); ++i)
  {
    if (neurons[i].are_all_weights_nulls())
        continue;

    fout << "sw(" << std::setw(3) << i << ",\"";
    fout << neurons[i].str_weights();
    fout << "\");";
    fout << std::endl;
  }

  fout.close();
}




//=================== RECOGNIZER =====================
recognizer::recognizer(int img_side)
: pos(0), perc(img_side*img_side, img_side*img_side)
{
  set_samples();
}

bool recognizer::load(image_array *arr, const char *file) const
{
  std::ifstream fin(file);

  if (!fin)
    return false;

  arr->clear();

  char ch;
  int i = 0;

  for (;;)
  {
    ch = fin.get();
    if (ch == '\n')
    {
      ++i;
      continue;
    }
    if (fin.eof()) break;
    arr->push_back( (ch == '.') ? 0 : 1 );
  }

  fin.close();
  return true;
}

bool recognizer::load(image_matrix *matr, const char *file) const
{
  std::ifstream fin(file);

  if (!fin)
    return false;

  matr->clear();
  matr->resize(1, image_array());

  char ch;
  int i = 0;

  for (;;)
  {
    ch = fin.get();
    if (ch == '\n')
    {
      ++i;
      matr->push_back(image_array());
      continue;
    }
    if (fin.eof()) break;
    (*matr)[i].push_back( (ch == '.') ? false : true );
  }

  matr->pop_back();

  fin.close();
  return true;
}

void recognizer::print(const image_array &arr) const
{
  const size_t sqr = static_cast<size_t>(sqrt((float)arr.size()));
  for (size_t i = 0; i < arr.size(); ++i)
  {
    switch (arr[i])
    {
    case 0: std::cout << '.'; break;
    case 1: std::cout << '@'; break;
    case 2: std::cout << '%'; break;
    case 3: std::cout << '#'; break;
    }

    if ( (i % sqr) == (sqr - 1) )
      std::cout << std::endl;
  }
}

bool recognizer::have_column_black_pixels(image_matrix *matr, int column)
{
    int height = static_cast<int>(matr->size());
    for (int i = 0; i < height; ++i)
    {
        if ( (*matr)[i][column] == 1 )
            return true;
    }
    return false;
}

void recognizer::erase_column(image_matrix *matr, int column)
{
    int height = static_cast<int>(matr->size());
    for (int i = 0; i < height; ++i)
    {
        (*matr)[i][column] = 0;
    }
}

void recognizer::erase_vert_gray_lines(image_matrix *matr)
{
    int width  = static_cast<int>((*matr)[0].size());
    for (int j = 0; j < width; ++j)
    {
        if (!have_column_black_pixels(matr, j))
        {
            erase_column(matr, j);
        }
    }
}

//  ....
//  ..@.   .@
//  .@@.-> @@
//  ..@.   .@
//  ..@.   .@
//  ....
void recognizer::cut(image_matrix *matr)
{
  image_array emp_im_arr = image_array((*matr)[0].size());

  while (matr->front() == emp_im_arr)
    matr->pop_front();

  while (matr->back() == emp_im_arr)
    matr->pop_back();

  bool b = true;
  while (b)
  {
    for (size_t i = 0; i < matr->size(); ++i)
    {
      if ((*matr)[i].front())
      {
        b = false;
        break;
      }
    }

    if (b)
    {
      for (size_t i = 0; i < matr->size(); ++i)
        (*matr)[i].pop_front();
    }
  }

  b = true;
  while (b)
  {
    for (size_t i = 0; i < matr->size(); ++i)
    {
      if ((*matr)[i].back())
      {
        b = false;
        break;
      }
    }

    if (b)
    {
      for (size_t i = 0; i < matr->size(); ++i)
        (*matr)[i].pop_back();
    }
  }
}

//  .@  ..@.
//  @@ -> .@@.
//  .@  ..@.
//  .@  ..@.
void recognizer::addlr(image_matrix *matr)
{
  int dif = matr->size() - (*matr)[0].size();

  if (dif < 0)
  {
    image_array emp_im_arr = image_array((*matr)[0].size());

    for (int i = 0; i < dif/2; ++i)
      matr->push_front(emp_im_arr);

    for (int i = 0; i < (dif+1)/2; ++i)
      matr->push_back(emp_im_arr);
  }
  else if (dif > 0)
  {
    for (size_t i = 0; i < matr->size(); ++i)
    {
      (*matr)[i].resize((*matr)[i].size() + dif);
      std::rotate((*matr)[i].begin(), (*matr)[i].end() - dif/2, (*matr)[i].end());
    }
  }
}

void recognizer::matrix2array(const image_matrix &matr, image_array *arr) const
{
  image_matrix m = matr;
  cut(&m);
  addlr(&m);

  arr->resize(IMG_SIDE*IMG_SIDE);
  float delta = static_cast<float>(m.size()) / IMG_SIDE;

  for (size_t i = 0; i < IMG_SIDE; ++i)
    for (int j = 0; j < IMG_SIDE; ++j)
      (*arr)[i*IMG_SIDE+j] = m[int(i*delta)][int(j*delta)];
}

void recognizer::add(int sample, const char *str)
{
  while (*str != '\0')
    samples[sample].push_back( (*str++ == '.') ? 0 : 1);
}

void recognizer::set_samples()
{
  std::for_each(
    samples, samples+DIGITS,
    std::mem_fun_ref(&image_array::clear)
    );
add(0, "......@@@.....");add(1, "........@.....");add(2, "......@@@.....");add(3, ".....@@@@@....");add(4, ".........@....");add(5, "...@@@@@@@@@..");add(6, ".........@@@..");add(7, "..@@@@@@@@@@..");add(8, ".....@@@@@....");add(9, ".....@@@@@....");
add(0, ".....@@@@@....");add(1, "......@@@.....");add(2, "....@@@@@@....");add(3, "....@@@@@@@...");add(4, "........@@....");add(5, "...@@@@@@@@@..");add(6, ".......@@@....");add(7, "..@@@@@@@@@@..");add(8, "....@@@@@@@...");add(9, "....@@@@@@@...");
add(0, "....@@...@@...");add(1, "......@@@.....");add(2, "....@@..@@@...");add(3, "...@@....@@@..");add(4, ".......@@@....");add(5, "...@@@........");add(6, "......@@......");add(7, "..........@...");add(8, "...@@@...@@@..");add(9, "...@@....@@...");
add(0, "....@@...@@...");add(1, ".......@@.....");add(2, "...@@....@@...");add(3, "..........@@..");add(4, "......@@@@....");add(5, "...@@@........");add(6, ".....@@.......");add(7, ".........@@...");add(8, "...@@.....@@..");add(9, "...@@.....@@..");
add(0, "...@@.....@@..");add(1, ".......@@.....");add(2, "...@@....@@...");add(3, "..........@@..");add(4, "......@@@@....");add(5, "...@@@........");add(6, "....@@........");add(7, ".........@@...");add(8, "...@@.....@@..");add(9, "...@@.....@@..");
add(0, "...@@.....@@..");add(1, ".......@@.....");add(2, ".........@@...");add(3, ".........@@@..");add(4, ".....@@.@@....");add(5, "...@@@@@@@....");add(6, "...@@.........");add(7, ".........@@...");add(8, "....@@...@@...");add(9, "...@@.....@@..");
add(0, "...@@.....@@..");add(1, ".......@@.....");add(2, ".........@@...");add(3, ".......@@@....");add(4, ".....@@.@@....");add(5, "...@@@@@@@@...");add(6, "...@@@@@@@@...");add(7, "........@@....");add(8, "......@@@.....");add(9, "...@@@@@@@@@..");
add(0, "...@@.....@@..");add(1, ".......@@.....");add(2, ".........@@...");add(3, ".......@@@@@..");add(4, "....@@..@@....");add(5, ".........@@@..");add(6, "...@@@@@@@@@..");add(7, "........@@....");add(8, ".....@@@@@....");add(9, "....@@@@@@@@..");
add(0, "...@@.....@@..");add(1, ".......@@.....");add(2, "........@@....");add(3, ".........@@@..");add(4, "...@@...@@....");add(5, "..........@@..");add(6, "...@@.....@@..");add(7, "........@.....");add(8, "....@@...@@...");add(9, "..........@@..");
add(0, "...@@.....@@..");add(1, ".......@@.....");add(2, ".......@@.....");add(3, "..........@@..");add(4, "...@@@@@@@@@..");add(5, "..........@@..");add(6, "...@@.....@@..");add(7, ".......@@.....");add(8, "...@@.....@@..");add(9, ".........@@...");
add(0, "...@@.....@@..");add(1, ".......@@.....");add(2, "......@@......");add(3, "..........@@..");add(4, "...@@@@@@@@@..");add(5, "..........@@..");add(6, "...@@.....@@..");add(7, ".......@@.....");add(8, "...@@.....@@..");add(9, "........@@....");
add(0, "....@@...@@...");add(1, ".......@@.....");add(2, ".....@@.......");add(3, "...@@....@@@..");add(4, "........@@....");add(5, "...@@....@@@..");add(6, "....@@....@@..");add(7, "......@@......");add(8, "...@@.....@@..");add(9, ".......@@.....");
add(0, "....@@@@@@@...");add(1, ".......@@.....");add(2, "....@@@@@@@@..");add(3, "....@@@@@@@...");add(4, "........@@....");add(5, "...@@@@@@@@...");add(6, "....@@@@@@@...");add(7, "......@@......");add(8, "....@@@@@@@...");add(9, ".....@@@......");
add(0, ".....@@@@@....");add(1, "......@@@@....");add(2, "...@@@@@@@@@..");add(3, ".....@@@@@....");add(4, "........@@....");add(5, "....@@@@@@....");add(6, ".....@@@@@....");add(7, "......@@......");add(8, ".....@@@@@....");add(9, "...@@@........");
}

void recognizer::set_weights()
{
sw(  2,"0BDHFKFDEIEH000BBFDDFBDDDG000000Bb0aBaCBa000c0dda0A0Bbaa00adedaAdCAbaa0aacddb0abAaba0aa0cdacC0b0b0000ab0a0BBAcb000b0baaa00bcb000abbaEAcAbcb000cd0EAAC0bbb00bcd0CCB0bcca00bcaAbBAaddc000baebc00cedc00");
sw(  3,"0BBJNNJCaKNOaa0B0FDfG0aCGNBa00aBaDBAGBfDb000gbaca0adiida00efBabbaceg0a0abg0DCFaAccba0ad0baegBEbBB000Dh0AbbBaFaA00DbikcdcaccBC00DfijbbAdAaAB00AekbFAbaa0c000dcbAaCCBcdaA00cCIBdAcAbC0b00d0BCb0Dcgjfa0");
sw(  4,"0BBJNNJCaKNOaa0B0FDfG0aCGNBa00aBaDBAGBfDb000gbaca0adiida00efBabbaceg0a0abg0DCFaAccba0ad0baegBEbBB000Dh0AbbBaFaA00DbikcdcaccBC00DfijbbAdAaAB00AekbFAbaa0c000dcbAaCCBcdaA00cCIBdAcAbC0b00d0BCb0Dcgjfa0");
sw(  5,"0ABDGRMKFHAFAA0AAGDGCCFGCJDA00AHDAE0AAbEc000fDdbgbkebj0c00fedc0AfCCEec00ibAFDDD0CCic0bkgCHIdHDBhf00benDIKEPAa0g00ackbJ0EHFEJC00ACijdbgiCKGB00C0cndgeaaGKA00A0EglfbdFDDAb00LJa0Aag0Bab000aGEDAejjkjb0");
sw(  6,"0ABEGLTPFIbAAD0AAGRFFeDHaEED000DGBbgaAGJDC00aFaHrffcBFE000adFEE0jIKNG000bjBGEbkaILA000bodEgjfBebB000fmddBFH0fbba0AgjCE0CJCgbCa00cfe000fAEBaa0FkBdCf0bdCbBa0AhHAEAdfCCada0CPONCBfgbCCgCCCEOKDCa0fflCC");
sw(  7,"0ABEGLTPFIbAAD0AAGRFFeDHaEED000DGBbgaAGJDC00aFaHrffcBFE000adFEE0jIKNG000bjBGEbkaILA000bodEgjfBebB000fmddBFH0fbba0AgjCE0CJCgbCa00cfe000fAEBaa0FkBdCf0bdCbBa0AhHAEAdfCCada0CPONCBfgbCCgCCCEOKDCa0fflCC");
sw(  8,"00ADFHXMKNaAaB00AELBTaEGACAB000CJfDBCGKCBB00AGDGj0DaDaH0000AIHLBAAHJF000ajCLIBiBNPa00caqfHeahbecA00cgrinbJEgnddb0bjnfDeFGacCab0d0qmkfdd0KCccaHqbcfj0CcCgbcaBnAAc0bAIDmhf0BQPRdCedfDCiBBBBQPKJcMCgnBB");
sw(  9,"00ABEFaGKHGE0000ADBGHdBADK0000AHBAb00AeCb000fIcc0dpehhhc00cnj0dgnaaDnc00fdGaAbBIDkic0BcCgLKBUHdkb00BAhHIJ0GNGCC00CDcBKOAILLHC00CFahAKajCAaDBBII0aCHFADNUbBBCBEgmdccaDLGB00CDjfcfbDdDA000cCachcieE000");
sw( 10,"0ACHPMaA0NRQaa0ABGfeFAa0HKBa000CAGGAABkCa000eheBKBhjkhi000fh0b0bejong000bAakECBEjgd00C0GFDcfKKEEJ00CLFbBikcEKBI00JDbgidbabAG000Gga0dbAeBcGa000bbAIBcCgBBd00gbABCDDadaAE00bdIFAACDACaB00bBaCEEGDBga00");
sw( 11,"0ACHPMaA0NRQaa0ABGfeFAa0HKBa000CAGGAABkCa000eheBKBhjkhi000fh0b0bejong000bAakECBEjgd00C0GFDcfKKEEJ00CLFbBikcEKBI00JDbgidbabAG000Gga0dbAeBcGa000bbAIBcCgBBd00gbABCDDadaAE00bdIFAACDACaB00bBaCEEGDBga00");
sw( 16,"0BDHFKFDEIEH000BBFDDFBDDDG000000Bb0aBaCBa000c0dda0A0Bbaa00adedaAdCAbaa0aacddb0abAaba0aa0cdacC0b0b0000ab0a0BBAcb000b0baaa00bcb000abbaEAcAbcb000cd0EAAC0bbb00bcd0CCB0bcca00bcaAbBAaddc000baebc00cedc00");
sw( 17,"0BBJNNJCaKNOaa0B0FDfG0aCGNBa00aBaDBAGBfDb000gbaca0adiida00efBabbaceg0a0abg0DCFaAccba0ad0baegBEbBB000Dh0AbbBaFaA00DbikcdcaccBC00DfijbbAdAaAB00AekbFAbaa0c000dcbAaCCBcdaA00cCIBdAcAbC0b00d0BCb0Dcgjfa0");
sw( 18,"00ABGOKGNKaD0C00ADJFCbADBICC000CDBBcDbAGBC00eCAAfbeebdD000deCaCdj0IHe000djCGBab0GBe00ckmbHFbDJAic00chrdFIDJJadd00aipcEE0OEaDa00BenibBbedECa00Deeic0afg0Fc000bDe0Cfb0C0Ca0CLKDBCaeABBACCCCKDBAB0gdcCC");
sw( 19,"0ABEGLTPFIbAAD0AAGRFFeDHaEED000DGBbgaAGJDC00aFaHrffcBFE000adFEE0jIKNG000bjBGEbkaILA000bodEgjfBebB000fmddBFH0fbba0AgjCE0CJCgbCa00cfe000fAEBaa0FkBdCf0bdCbBa0AhHAEAdfCCada0CPONCBfgbCCgCCCEOKDCa0fflCC");
sw( 20,"00ADFHXMKNaAaB00AELBTaEGACAB000CJfDBCGKCBB00AGDGj0DaDaH0000AIHLBAAHJF000ajCLIBiBNPa00caqfHeahbecA00cgrinbJEgnddb0bjnfDeFGacCab0d0qmkfdd0KCccaHqbcfj0CcCgbcaBnAAc0bAIDmhf0BQPRdCedfDCiBBBBQPKJcMCgnBB");
sw( 21,"000DGEODJJFG0B000CGbNEGKGBBB000EJ0FGHAD0BB00BFDGCD0caaD000BHGFEbbgcb0000BDAB0Ddad00000BeAHDGECaAB0000feh0Ca0acB000gjeBb0bcDDC00ccldhjekBJB0aaAi0afiifaDccaaffCBaABbACAdd0BGKNCIEDBE0BBBBBHMMNBMEdeBB");
sw( 22,"00AAAAGDFAAB0000ABBCHEDDBA00000ABAFDCBD0000000BBCCBBD000000ABACCBADA00000BAACCBACB00000BA0DCCBBB00000BAACCCBBB00000BA0CCD0BC00000BA0CEC0BC00000AB0DDC0CB00000ACBDDBBC000000ADAEECBC000000AABGEFD0000");
sw( 23,"000BCCKIDBaB0A000ADFG0BC0CAA000BDCcbbBDDAA00A0AAAedABDA000AbBAAbeAADA000AcDA0cbBBCA00AACADFfBF0AA00AAFGFCdAFDDB00ABGF0DfDE0CB000CDBBEaAA0CB00BCGHGFC0AFGB000BCCFAca0AAAA0AACECBaBCCCAAAAA0CABBFBc0AA");
sw( 24,"0ABDGRMKFHAFAA0AAGDGCCFGCJDA00AHDAE0AAbEc000fDdbgbkebj0c00fedc0AfCCEec00ibAFDDD0CCic0bkgCHIdHDBhf00benDIKEPAa0g00ackbJ0EHFEJC00ACijdbgiCKGB00C0cndgeaaGKA00A0EglfbdFDDAb00LJa0Aag0Bab000aGEDAejjkjb0");
sw( 25,"0BBJNNJCaKNOaa0B0FDfG0aCGNBa00aBaDBAGBfDb000gbaca0adiida00efBabbaceg0a0abg0DCFaAccba0ad0baegBEbBB000Dh0AbbBaFaA00DbikcdcaccBC00DfijbbAdAaAB00AekbFAbaa0c000dcbAaCCBcdaA00cCIBdAcAbC0b00d0BCb0Dcgjfa0");
sw( 31,"0abbBCKIB0dd0A0abBHBBBCB00CA0abDHDGCB00D000adA0bh0kgafBa00ccAaaaaBCEba00feAHDGEBEDfa0bilaNOGF0Bhc00beqCDLCIH0Bd00acmbMABJFHGC00ACjmfcii0KFA00B00oiijaAIG000a0BflfgADFBAc0AKJbcceaBccb0000JEDAebfeha0");
sw( 32,"0dee0aONBajgcC0dcbSADf0Ee0BC0bbBGFAedBIHCD0b0FEGjccdBFG000AaJKM0aAPNH000AiFOCBldKMD00aapeEcdi0bb000aeoegEFBad0db0ajhCFCEKG0ADb0cdegbdbfcIBab0DiBeiice0FaBb0BeAabegcHFeg00EPOKEbda0BBfDDEDRIHAeEb0hDD");
sw( 33,"0bb0PJLOaM0HaB0b0cOEenceASDB00ft0BcfaIdgBD00cHa0AbeniCJC00BBMDKGGpACBC0aGmM\\JLmdIBBC0eCriGbjjDELa00dcpfhDHBnbeD00bdHDnriF0pac00BESMAp0HhAGe00H0DEcEAcAbgc00FgF0BClf0bhdD0DPHXBgd0bEICDDDDAFGcCIDCBDD");
sw( 34,"0abcdksjjACEba0aadmfNEdiDeba00aJFjGNFBkjb000AaaeRL0Beia000CIecEbCmvmo000CMfl0aFHljh00aHHBcHPPE0A000aIJeaaEaC0cEB0aEBAfcBlkEGgB00AaHbfacbBFeAa0bBbicibAfdjAacAE0dIFba00Kb00feehKHCCaAI000amdEKbBIAF00");
sw( 35,"0cdfhqqggcGAca0ccfpcQEdeGgda0bc0CeCEBBhma00bcfcdNHDHekb0000EecBBFflnk0000HbhBFCHgmi000EHEbKDIGadc000EMBcBaebB0a00aGFDhAaddCBh00aDFEbABFAaCd00dDIJBHDDFCDf00d0A0eGKF00cG000kjmmGJFE00D00acmggGFaPJHa0");
sw( 36,"0dekkpccbbbgec0daea0Fce0hohc00fBafcDebIlbA00BeAhLHCLB0bE00badDJAEACAcE0a0fbADda0BaEE0e0cbicAiCJeA00dccfe0DiAfAaa0b0ACgDEKakcka0C00ACHOL0ldha0AAAKbNJaCihfa0CabcGEFEFcibA0AghdlDDEFCAcAAAAAmhCEKPGKCA");
sw( 37,"0bbjqoFHEnxoAE0baeHIBgDGieCE0aafCbfeegJEDB0aCEABjkCJJOG000D00HCDBPVRG000A0IDfcfkKJC000bdiAEejbffi000pfAbEBEBjDfa0f0ENHF0KHadDa0gFF0bJDDaEgCa0CCKckBBGMECGa0JABcdgcAFEfiB0FJicdBfmEdEcBBFEFedibEBJaBB");
sw( 38,"0CDHbEMLMGmicE0CACGGDaECcJaE00AGHAbgAfFKDB00DJaHsjdCIKK000EBBbbFhKOOD000AbddbgjaGK000cbjfAgbe0bcc00cjfgdBHGCkad00ddEKE0FLBhdA00bEDEAcCcCEbaaaEiGacmC0B0aaaaDeHHDadjAEcca0BJ0FGFaqcbCCBBBEGAAadfib0BB");
sw( 39,"00aafcCKFgmfBC00abDD0a0ddGBC00bEGcCCbiAAE000aBeAgbdbGCE000aAc0aFBIHAe00cbBdF0BDFCAj00dcleaJIGadqj00afgdaLLHAlaf00bcDIEiaBGBcD00aKG0aheCaF0C00EDKbgg0aACFB00EBDBghghEBACc0CRcbCbgo0dBC00BAIa0CjcdDbb0");
sw( 45,"0debCABBIAAIdA0db0LAlAhdADbA0acmAMgdBFeiaD0aeLB0beeeleCC00jJNEBdCpdEdC0DbnQZKKfaFcBC0edoiQDAbKN0D00ibvaEIaCIFbHa0fcrbFIEPDlLCa0BfgeAfEciBHCa0BAcec0bbFfhca0AAKdF0kBe0eDD0DLBDCde0aAK0DDDABGEgDHcCEDD");
sw( 46,"0cccIENLDGDJcB0c0bOCgdBbBI0B00cxAMfecJageE00bECAcffekCI000cKMIICIl0JG00EajL[HLmdHCG00adqjMdomELMC00fdpaE0BAcB0Da0caeHC0BJBnEAa0BbJEBhADcAF0a0Dd0hecaCKckAa0BhDe0ahbeAleE0ELELCcc0AFE0EEEaBGDgbEd0AEE");
sw( 47,"0bbaJDBEaBHGbb0b0abfDADF0BDb000hDaCCddicc000agaCI0hfnfg000AAFDGFCfjhB000CEACDIb0cCC00FCGGJbgcCEKJ00FGGDimggfGHF00JaFckhaheCDA00CfFBffccECA000AcEABBg0AB0A00eeaCAb000bbb000BDPDcADaE0c000ADHGADACdga0");
sw( 48,"0bbcdhrigDCCba0badqbC0dbEaba0aaeh0c0ddhea00aaegbK00Ddcg000abfdbBcAhij0000EaheABDfkc00BDMGcHdIKE0000BEOFFbgdEGFE00AIJHgAabBaCa000CID0GDCCf0A00eIDFGLFDFABb00aEabCEHBbcEEC00jijfAFBFABE000amhecEbHIF00");
sw( 49,"0accefbedACfba0abdfcHDBbAdca00cebcDFAA0fc000deAeGJDHacd000bdgcEHGFbcc000bcaaGEBCbda00abaacD0aAcdc00abbBBCAbdccb00aCBE0BGCAeac00ABDDCHIGDca0000BCEAEICFa0000A00dfEIFDaeb000eholCDB0beb00acglgF0CHCBa0");
sw( 50,"0accefbedACfba0abdfcHDBbAdca00cebcDFAA0fc000deAeGJDHacd000bdgcEHGFbcc000bcaaGEBCbda00abaacD0aAcdc00abbBBCAbdccb00aCBE0BGCAeac00ABDDCHIGDca0000BCEAEICFa0000A00dfEIFDaeb000eholCDB0beb00acglgF0CHCBa0");
sw( 51,"0ACGFEJFbGBE0A0ABACKGcCHeCAA00bgbbcfdaMGbA00AAgfEoEEILC000Ch0bGDaNKGN00b0kEagldjbEH000aHeohrrEbAb00BcDAgbiBc0Cf00AFRIiDdCHmhb00aALHcQAFEmmb00aABLGHHJDkfH00CaaBGCCC0hdjE00jhDcabb0DCcAAABjjkdGDFCEBA");
sw( 52,"0CDHbEMLMGmicE0CACGGDaECcJaE00AGHAbgAfFKDB00DJaHsjdCIKK000EBBbbFhKOOD000AbddbgjaGK000cbjfAgbe0bcc00cjfgdBHGCkad00ddEKE0FLBhdA00bEDEAcCcCEbaaaEiGacmC0B0aaaaDeHHDadjAEcca0BJ0FGFaqcbCCBBBEGAAadfib0BB");
sw( 53,"000aigCEJgpk0A0000IB0Eabfb0A00AIDC0cagE0a0000GcChBfAGaGa00bD0ehaBENFfa0AcCbEf0DBGAha0agmeEJIFe0lf00bckBGNFMJiFc00b0hJSCCHFG0F000GegcdcdbKCE00BDCfknh0FFBD00bEKDnmfbGEaBe0AMBgCaelDfbD00AbAdBeidg0db0");
sw( 59,"0cccIENLDGDJcB0c0bOCgdBbBI0B00cxAMfecJageE00bECAcffekCI000cKMIICIl0JG00EajL[HLmdHCG00adqjMdomELMC00fdpaE0BAcB0Da0caeHC0BJBnEAa0BbJEBhADcAF0a0Dd0hecaCKckAa0BhDe0ahbeAleE0ELELCcc0AFE0EEEaBGDgbEd0AEE");
sw( 60,"0dcdI0GJDCBLdA0dAeLAjd0ABHBA00AkDMegDEfa0E00ACAFafkhncH0000IRDHDCse0D00GBAIKEIq0BAH00HBbfPblbKFJN00ACdEFdceHC0M00CDaDBC0OdkEb00AeGI0lBBd0Ac00BcGdc0gCCBgc00bkFdL0iAd0f0E0EGAREAbaDFIFEEFbEPLADACCcFE");
sw( 61,"0ccaHEebAEKGcb0caAeiDE0bBB0b0aabAEEAackcb00aefaBIadgmej000cbD00cAinke000AACaEFECef000BaEDF00HEFAG00BIEAAgfbDEDF00GBcehfefdDDb00EdAbeecgcBDa000CCaCAfee0Bc00dBAABbaBb0CB000aEHAbCFBBA00000AGEBCBBaa00");
sw( 62,"0aabdeeddbbdaa0a0af0abccbbaa000de0cbbAAaa000aecbCdBFDAb000beebcB0ECAa000bbCbA0BBBca00abE0cCdaC0cc00acEECBcaAABaa0cCGGaABDCd0aa0aBFCBIEDAdb00AaEDEEFGDEABA0AAAacA0BCBaa0C00chjfa0ABaba000ahmieAaBAB00");
sw( 63,"0accefbedACfba0abdfcHDBbAdca00cebcDFAA0fc000deAeGJDHacd000bdgcEHGFbcc000bcaaGEBCbda00abaacD0aAcdc00abbBBCAbdccb00aCBE0BGCAeac00ABDDCHIGDca0000BCEAEICFa0000A00dfEIFDaeb000eholCDB0beb00acglgF0CHCBa0");
sw( 64,"0accefbedACfba0abdfcHDBbAdca00cebcDFAA0fc000deAeGJDHacd000bdgcEHGFbcc000bcaaGEBCbda00abaacD0aAcdc00abbBBCAbdccb00aCBE0BGCAeac00ABDDCHIGDca0000BCEAEICFa0000A00dfEIFDaeb000eholCDB0beb00acglgF0CHCBa0");
sw( 65,"00BDAFGCDIBda000BABHDebBeCb000aAaacedcGCAA00aAceEhAFEF0C00dhfcaCeIDBaC0aakCgafeeFaBC0daEdieicGBec00cgAAAAeABBcB00fDIDfEfDFlda00aaFACPGE0kgb00bBbJOKNDAecA00BbgAMDA0AbebD00hgBdABADCC0AAABcgjcIGFHMBA");
sw( 66,"0CDHbEMLMGmicE0CACGGDaECcJaE00AGHAbgAfFKDB00DJaHsjdCIKK000EBBbbFhKOOD000AbddbgjaGK000cbjfAgbe0bcc00cjfgdBHGCkad00ddEKE0FLBhdA00bEDEAcCcCEbaaaEiGacmC0B0aaaaDeHHDadjAEcca0BJ0FGFaqcbCCBBBEGAAadfib0BB");
sw( 67,"000ejfENDlskBB000fKCB0EaecBB00BFE0BAhdHFb000DGaCkbbaIFEb00C00cAICHQK0b00BDAHfDb0ELdb0CajcBDBekedb00CdfFaJGCdhHd00BbFSNAECEDaG00cIIabgjbAL0FaaDDHalnfCHKCGaaDDDEkjdeEBccd0BKab0ahobgAa00BdCcDbkfh0od0");
sw( 73,"0ccbHaCFcBJFcc0c0dBgBEHJB0Fc000dBFDEIBjEe000acBBGEfekdeb00dEGb0CGkkaFb0HcJDAcGfcbEGb0NbNBMafAECUO00FLEG0oniEIKG00LKidAGFagHKa00DlcalmdmBCDa00ccbebbp0cEaA00hfcAccFHeAbe000eHI0aEIdBca000BENIcbfegf00");
sw( 74,"0bb0I0HJCaEK0a0b0fFdgADEDIGa000fFJb0B0led000Bb0Ga0iopgBb00bDGCBGEpjAAb0G0AEMANkA0HCb0HBAbTFdacDPK00AFaLCCd0beIK00DD0BJAICe0FC00AbFFakjcECDE00C0IcAfkBEI0C00ahC0dhfbcDB000AD0KF0cebEAa00AfBKIaekdelb0");
sw( 75,"0begCDDIcKKaC00bd0QbBh0jaEB00aee0EbejAfbA00agCaiagefndb000gddEdAeEAAh00fimSXFMENQhm00llhbAHlfDCon00fgoaAXJCkFAfd0eafDHeaGJaCCd0aGMgGJ0IdbHCcAAMFDALHBHJIBcAEEEimdjAEEcDC0AJEAolnCFGGd000cggaiHbHK0a0");
sw( 76,"0efiCAAaaFJfBe0eaFCBGbAeFECe000bfGgdeBbB0000hrCdEAcGech000ksdCbdaBd0f00aidLRFKHIBke00enEaeBgkHJde00dAhCDJbdgOHed0acgdcabaFaEed0CbbpFPBbedEAaCaJfDHRKa0LHBaCAFghkcaFBFaEE00dDesgfLEGdd000ddcefGcHAD00");
sw( 77,"00bcBEFgfDJG0000bcFmFCBADAB000eACaGEEFfec000cfCbFICapfc000cAFCCaLjric000BbbKJNFCcdb00cAdbECDBEDDA00cDjdcDD0jADCb00fsobdGci0Ebb0AdllbdA0a0Fbb0AbdcaAbD0BBeb00dBciCCF0ab0000CBBlGFDdD0g00bc0AEIEDFeeb0");
sw( 78,"0dflaAbheIMABd0dbaBcKDBgEbBd00eeBaACdC0cc000gmDeLKFKhig000if0CBaHAhhj00agBFOGPMFAkf00fi0AgKEbMFaf00eCndENF0hMIcd0acrifgFBC0Hgd0Bdnp0IBABfGbcAaBi0cLEFCGFbcACCfjlAEJ0DbAB00fcjuAANDJci00aeijbbFCQa0a0");
sw( 79,"000CHIHKNK00BB000GJHIk0dBMDB00aDDBaddfDHGB00i0kcbjjc0DcC00hljF0dgPNDeC0ihnFJEbDGOfkC0mjahiBjEQazl00dglm0KFKEBdgc0cdAbbfgHOacBc00FClEQCEbf0abADHADHQMBbDFabADba0ccfdFAgBC0BNFEehhcGCEfBBBELadcKI0GCBB");
sw( 80,"0CDHbEMLMGmicE0CACGGDaECcJaE00AGHAbgAfFKDB00DJaHsjdCIKK000EBBbbFhKOOD000AbddbgjaGK000cbjfAgbe0bcc00cjfgdBHGCkad00ddEKE0FLBhdA00bEDEAcCcCEbaaaEiGacmC0B0aaaaDeHHDadjAEcca0BJ0FGFaqcbCCBBBEGAAadfib0BB");
sw( 81,"000ekgIHDlrlb0000iFCIDDJbhb000DIEACadDONf000Df0Bfd0DKDBf00FCfe0BIEPILf0CAChjhhijCNCf0MABcaAajjkGC00JDAKbfbfdaGfa0IDaBGMaj0McCa0cAlgfahmDLjaa0bbdfjkjAEDaFa0bakCkbEBEAffa00b0aAadebefc000eFCchjlgeia0");
sw( 87,"0ccbHaCFcBJFcc0c0dBgBEHJB0Fc000dBFDEIBjEe000acBBGEfekdeb00dEGb0CGkkaFb0HcJDAcGfcbEGb0NbNBMafAECUO00FLEG0oniEIKG00LKidAGFagHKa00DlcalmdmBCDa00ccbebbp0cEaA00hfcAccFHeAbe000eHI0aEIdBca000BENIcbfegf00");
sw( 88,"0ccbHaCFcBJFcc0c0dBgBEHJB0Fc000dBFDEIBjEe000acBBGEfekdeb00dEGb0CGkkaFb0HcJDAcGfcbEGb0NbNBMafAECUO00FLEG0oniEIKG00LKidAGFagHKa00DlcalmdmBCDa00ccbebbp0cEaA00hfcAccFHeAbe000eHI0aEIdBca000BENIcbfegf00");
sw( 89,"0ghldbgAdCPFdg0gaAbcIDCKJjag00DcgCcbbBbAf000eebcJHgBkgm000lkdekg0deDd00FhBMaBMCfcnD00LdQFNKjGQGeJ00FIDSQesdORK000FNnFGTBKCDFd00GgjofLcm0fHbCChMdaMRdaBNEBCCjGajc0HOkEFEE00nCrjaAKJCd0000dBCadCbGKD00");
sw( 90,"0fghdggBFADIAc0fcADAdAcbEGCc0bbAbBe000hjb00bfGAcabmhsie000ejdAccjcgBk000daNHEOHCCjc00b0EbNOiLKLha00bCdKIOeHIHJE00bFjEOKJPICFD00ACCbEMAcFADD00BNF0BPCBHTPA00CaNjkbeHAHKDB0A0djfdhBKEEA00AdCa0fBgBJC00");
sw( 91,"0bdhgg0bJCEba00bcdbfNICBIgA00a0JGgGEFFggB00aabAAENfcjuc0000C0DBd0oehn00AAJBBHHDNEaj00CBCAQRTVBagE00BEibbILaIAcF00CAomMaGCaTLe00a0njjmelbLPb00AaBinglbbJGj00eaEdpaBBdBcFf0AEEbgEacbgiA000AHEJObBGAia0");
sw( 92,"00ccbC0GNIKG0000c0dANCGaJC0000cDEaDD0Cd0c000fCbcEHffgogc00aBeaCDgdefpc00dCAaFJGIDglc0AAC0CSIUAfl000ADcCFKHFHFAA00ADgbFIFFGKJd000BegdHaeBGMc00AEAheaaDCPOj000AEinfA0eFbH000bbkoBbaCdgc00cfaeeEdbCDfc0");
sw( 93,"00ABCEFdFOJCaA00A0gFccBMbAAA00CRAAgeI0BIBB00kaAbIBbGcfl000itiBBh0GDde00BdacvFnafcfB00GdRFccdENEcF00E0HDKmofVUA000E0indWcbEEAm00Ekrn0ZKi0dejBBabfHTSIDdaGfBBfejC0AHFeCaaD0AlM0cCGIEEcbBBBEJLbgJEGEIDB");
sw( 94,"0gdeDaFCfCEBgb0gCbFecFCHc0Ab00CdAKdfEHaCbE00BBEGC0bahab000bELCEABtdDE00IBDHAAalbBDM00LBLAOfkhJFQQ00CGEBcsmpKNCK00EFghfNcAiCKa00BohbecEdfaDd00cjfdADhabffA00fhbbNF0JhafcE0EaERDAALdG0BEEHCGRJaGa0AaHE");
sw( 95,"000aa0ED0dfc00000cECCCAB0e00000ADCcbBEFCc000CABBdaACEBCb00BBBbbaBcDHFb0E0BDadbgeCIDb0H0CDEceidBLE00CBAHDcefdBHC00BFaBFHCbcCFB00babB0badEE0000b0bdefeEB00A00bbbcecFD0ade000eBaaADbecdb000d0DBddfdgea0");
sw(101,"0000addaAabB00000diaBABBab00000cBabBcd0ba00000dDEBacc0d000BB0ABabeef0000FHBdcabff0C00EHKHBegf0CGD00EDLEahgk0EFEA0CALGeadiaCBBA0a0JGbbdcDAA0A0aAGBaaeaC0b0A0baACAaacAcae000f0HA000cCa0000agAFCDACafa0");
sw(102,"0aafhje0jcaBaa0a0ecBAEJH0iaa00BA0cgcb0EBc000EAea0aDK0Fbb00DddjbA000DGb0DAHBkjdifhBJb0JFOGaAsfDbIH00FDPPHgmlGINA00DJKICKEBCCAA00baHEeFa0IeBD00e0GFBH0IJEDE00acadbAJDbdEhB00oeggABDBD00000cifbfAeEDd00");
sw(103,"0ccepnldGEbca00caedBcFAaFda00aaAede0edbe000aaKfa0Ffcfbi000ccgaiakcbBn00AcAHabA00Cma00aECFNQ0SEEja00b0FOPKeFN0BF00gIfKMPKNGBDE00bIB00LEeCbJE00cKGa0HCFIKKb00ABIkidbEcDK0A0Bchwg0dAIAAC00B0bkBjcgCND00");
sw(104,"0aacnmlfLdhB000a0ceclBaeFd00000BBBc0Aaea0000BNhGaAcejff000cJe0iainlbq00CcEBadB0Cfia00aDCARKLYaAeI00d0DIMHaAPfFNA0dBeAQMKEFCABA00AAacedh0AGE0a0CFgjfhBEDEh0a00MAjcbchBHDa0ABgjaBcfFcBG00AaAgJbgg0JE00");
sw(105,"0cckxumiNlkfaA0cbechILdAJoaA0bCKHfJKDcaeF00bdEjGOSbaeld000dRlAecBjdep00BdKhgaCCFEdg000DAaPOTYFgoI00bCADdDEAPkaJA0bCmARILdcRGdA0aamAkgckfFKA0a0fFhpnnhGbal0ahfL0jBKFBdIBj0BFisbKclFifH00BAEaJKmCFFc00");
sw(106,"0BADqdjbS0cOBB0BaCeAIFBcFcAB00bQGbD0ddbCA000dGjEHMaBEgfa00dFrlgbeIBbra00gEgoc0KBEoka0dDFe0NJ]Giv000dBIDGNECPfA000gG0GHTR0FFGd00cECAfWAiBbKb00bDIACb0H0EMm00acO0feFBa0bD000enzjGCkCmg000bakkiCf00J0b0");
sw(107,"00AACF0ENKEE0B00ACCGEAFDFKBB000E0BbCCA0DBB00fGcfEcodead000fjfbAemABFl000fiIaDd0DJif00beBeFHASQBqa00beiBFHbGSKeE00bAeaCO0LLFDA00CCbfBNCd0cb0AAFFaBHMLaDIRdAAA0Ad0agbBDGEC0BDHed0bCHEEBBBBBHFafCCCJHBB");
sw(108,"0hglbdJB00dfhc0hAgBdFEBMfaAc00FDGE0bFBDGAE000cCJD0BCcdb000bcHCJdFlCBD00FGD0ebcjneBJ00NGPcHcAcHBJN00HJDBlvopLODH00HbjkaJdbaIIb000pskgeckBD0i00dnhgabkdfba000jhhAH0DDABbaC0EAHIGAEIbGbEEEGDQVKDaAFAaGE");
sw(109,"0ccdBdHGAedfcc0c0cbdIHFMaAEc00FDBDECAD0Lb000emCEKEB00hfe00ah0aEAKjBaGe0ECJcjcchfcFDe0QCSDKEee0AQL00LPJHcjniJFKE00OBhgCKAedRJA000nnimgfuGICc00deckfhqadCEB00jdiFhAGHBcAea00aICCdaChbeA000aJRH0jlBfja0");
sw(115,"0aaefidadAcCaa0a0fjAFBBF0eaa00abbaecebD0a000Adk0GcEIaCf000DeecFEAC0aE00aCCbfecbegaF00FGJChBmgBdCD00GEOGCgih0FIA00FIRLhAbbCcaa00aDOGcHCEGga000cFIIEHCGE00A00AADCCBHaBeBgC00heCfb0BAEAa000angdeGBJDb00");
sw(116,"0aaeglgCcabEA00a0gjDCAB00d0000bfAbeegfcf0a00AAh0FeacbEd000DBb0DHABBab00bABEAc0ebceb00BDCEBKfaDfgb00DDHFFGBBcf0b00DNULffaCDbAa000NXNbFALGdaB000NSIDHCGIBEC00EEG0Bec0CADeB0AafAaegfEEHCaaAakd0cCAPFAaa");
sw(117,"000abcCDEdic00000bB0fbahaB0000cdAaaddbbc0000BGa0eefgbEF000CHDC0DdaaCd00acAELBJ0EBaf00fenaFCHIBaif00eghbFNJKagbb00eADGDiBCDc0D00aJKEBkeF0BaCaaCGHCbhaaDBAaaaC0EbfifeaABCa00OdBAdbhbbEE000bCeBAaa0aD00");
sw(119,"00aaabAebaC00000aaaeGCE0Bb0000aaaeEGBAbca000ba0cHKD0dcaa000AbAGEG0dcaa00aAc0DEB0ebaa00abbeDEBbeba0000cebDFAeddb000acb0BGBcbba000ac0aADD0aaa000acehbACAdcb00000cgDGCaada000adggFFBbcca00abcebHBCBa0a0");
sw(120,"00ADBBDCBGECba00ABaCHcBDgeda00ecBccAA0GhcA00acAeGEFJBbbB00bcg0CBaGD0cB0abeccabdaC0BB0dbadhgdfDHaa00cebbbbAcEdab00daC0bCCE0kei00A0AaEINGAkegAAAabGGNLEBihfAAacddHJGDBhjdC0aihcgGJDCabcAAa0hjfEEKHDFBA");
sw(121,"0abholeDGesnBE0abbAIBkadiabE0ac0AgbgekF0HA0aADdbckAGJNDD00CgeEDebQKHeD0gDgDBBeD0JBeD0j0hidJDFAczo00crikcOLIJhde00jeFGAakFOcdB00gJG0CHARedbB00CILHdJKBEAEA00MFD0CgkcHEbaA0ELicA0cmHcGAAAFFKjc0CHKPJBA");
sw(122,"0bbd00CGCdea000b0aE0FGEEDBE000CCH0A0bAcA0000bbbAaaeidBca00aaBdBDAccAba00ACDD0E0C0Bca0BAbDOKDE0a0C00BBaDBDCADADC00CccBCc0eAIFE00bc0eigijEKEDaa00CggglaCJGBaa0BEBfjdcbDDaa0BIDGCbab0AA000BAKMHB0aadfc0");
sw(123,"0ccdBdHGAedfcc0c0cbdIHFMaAEc00FDBDECAD0Lb000emCEKEB00hfe00ah0aEAKjBaGe0ECJcjcchfcFDe0QCSDKEee0AQL00LPJHcjniJFKE00OBhgCKAedRJA000nnimgfuGICc00deckfhqadCEB00jdiFhAGHBcAea00aICCdaChbeA000aJRH0jlBfja0");
sw(129,"0aaeglgCcabEA00a0gjDCAB00d0000bfAbeegfcf0a00AAh0FeacbEd000DBb0DHABBab00bABEAc0ebceb00BDCEBKfaDfgb00DDHFFGBBcf0b00DNULffaCDbAa000NXNbFALGdaB000NSIDHCGIBEC00EEG0Bec0CADeB0AafAaegfEEHCaaAakd0cCAPFAaa");
sw(130,"0aaeglgCcabEA00a0gjDCAB00d0000bfAbeegfcf0a00AAh0FeacbEd000DBb0DHABBab00bABEAc0ebceb00BDCEBKfaDfgb00DDHFFGBBcf0b00DNULffaCDbAa000NXNbFALGdaB000NSIDHCGIBEC00EEG0Bec0CADeB0AafAaegfEEHCaaAakd0cCAPFAaa");
sw(131,"0aabdeeddbbdaa0a0af0abccbbaa000de0cbbAAaa000aecbCdBFDAb000beebcB0ECAa000bbCbA0BBBca00abE0cCdaC0cc00acEECBcaAABaa0cCGGaABDCd0aa0aBFCBIEDAdb00AaEDEEFGDEABA0AAAacA0BCBaa0C00chjfa0ABaba000ahmieAaBAB00");
sw(132,"0aabdeeddbbdaa0a0af0abccbbaa000de0cbbAAaa000aecbCdBFDAb000beebcB0ECAa000bbCbA0BBBca00abE0cCdaC0cc00acEECBcaAABaa0cCGGaABDCd0aa0aBFCBIEDAdb00AaEDEEFGDEABA0AAAacA0BCBaa0C00chjfa0ABaba000ahmieAaBAB00");
sw(133,"00ADBBDCBGECba00ABaCHcBDgeda00ecBccAA0GhcA00acAeGEFJBbbB00bcg0CBaGD0cB0abeccabdaC0BB0dbadhgdfDHaa00cebbbbAcEdab00daC0bCCE0kei00A0AaEINGAkegAAAabGGNLEBihfAAacddHJGDBhjdC0aihcgGJDCabcAAa0hjfEEKHDFBA");
sw(134,"00ADBBDCBGECba00ABaCHcBDgeda00ecBccAA0GhcA00acAeGEFJBbbB00bcg0CBaGD0cB0abeccabdaC0BB0dbadhgdfDHaa00cebbbbAcEdab00daC0bCCE0kei00A0AaEINGAkegAAAabGGNLEBihfAAacddHJGDBhjdC0aihcgGJDCabcAAa0hjfEEKHDFBA");
sw(135,"0bbffda0Aacdbb0b0aABEDADahcb00CDjCc0ACE0c000B00h0cCJE0a000cfdgh00CFIC00BdcHdbfegBbC00adFF0DjfbA0000cbBPTEhBHAEcc0eFdKHOJOabAdc00EfjAPGaA0AbbAcGebFIHIFIBBbAaCAjdcCJCAa0C00jBtgaaEEcdd000cbeiiccA0B00");
sw(136,"0defeeDDbeg0ba0dbb0AFDABCABa0aAAB0bbeA00b00acfa0CefhaBdb000dABA0aaaAcb00abHFADACCAbb0AaCENOcAD0aa00AAGJHEbCGCG000ABFKAbfcEIGD000CE0eChfFGID00BFJBCBhAENMD00CDF0djeBAHJBA0BFaabgdBCFBA00B0FFAcAAEbaa0");
sw(137,"0defadAIAcc0a00dbeeAG0EDEGC00acdadbbkgabE00aimdALBilcCja00aqcBGbcBbcda0ebgGCBCFFaeha00bCCGSAKGgmh00EaHAeBAB0Bbe00EEOHiomkDLDC000IWMgbeCEAFC00ALRKDHbBCIJD00DBE0fd0ACCKaA0CMiB0fddFHCG00CC0BECCFKEE00");
sw(143,"0aaeglgCcabEA00a0gjDCAB00d0000bfAbeegfcf0a00AAh0FeacbEd000DBb0DHABBab00bABEAc0ebceb00BDCEBKfaDfgb00DDHFFGBBcf0b00DNULffaCDbAa000NXNbFALGdaB000NSIDHCGIBEC00EEG0Bec0CADeB0AafAaegfEEHCaaAakd0cCAPFAaa");
sw(144,"0aaeglgCcabEA00a0gjDCAB00d0000bfAbeegfcf0a00AAh0FeacbEd000DBb0DHABBab00bABEAc0ebceb00BDCEBKfaDfgb00DDHFFGBBcf0b00DNULffaCDbAa000NXNbFALGdaB000NSIDHCGIBEC00EEG0Bec0CADeB0AafAaegfEEHCaaAakd0cCAPFAaa");
sw(145,"0aabdeeddbbdaa0a0af0abccbbaa000de0cbbAAaa000aecbCdBFDAb000beebcB0ECAa000bbCbA0BBBca00abE0cCdaC0cc00acEECBcaAABaa0cCGGaABDCd0aa0aBFCBIEDAdb00AaEDEEFGDEABA0AAAacA0BCBaa0C00chjfa0ABaba000ahmieAaBAB00");
sw(146,"0dcjjlbcaahgdc0dAfbCddf0hgec00ccdBcecbHf0A00CAAeIiAHHEaE00cd0aB00CIAbE0a0kDbCgacEdDE0f0BaifbdHHdc00efAA00edF0BAb0fCGEfCaHAkfeb0BBCCFLJFdlfdaAaDAMHLJDagfAaACccbL0cAD0b0D0Adgbga0BHEGbAABCAjkeIFIMNDA");
sw(147,"00ADBBDCBGECba00ABaCHcBDgeda00ecBccAA0GhcA00acAeGEFJBbbB00bcg0CBaGD0cB0abeccabdaC0BB0dbadhgdfDHaa00cebbbbAcEdab00daC0bCCE0kei00A0AaEINGAkegAAAabGGNLEBihfAAacddHJGDBhjdC0aihcgGJDCabcAAa0hjfEEKHDFBA");
sw(148,"00aCbFA0AHHFcc00aFccHHFEFecc00AB0BDIDDFcj000caCgHMFDAibc00AclkaFBIADdc0AcAbfdBch0ABc0bcFBeAjhbbEa00ccCKQFBCEcDc00gbcJMNNLBf0f00bbhlCSBhFa0eAAb0ihDCFGIFAfAAbABje0FFB0kaD0cncspDHEBhkf00ehngkBd0B0fb0");
sw(149,"0bbffda0Aacdbb0b0aABEDADahcb00CDjCc0ACE0c000B00h0cCJE0a000cfdgh00CFIC00BdcHdbfegBbC00adFF0DjfbA0000cbBPTEhBHAEcc0eFdKHOJOabAdc00EfjAPGaA0AbbAcGebFIHIFIBBbAaCAjdcCJCAa0C00jBtgaaEEcdd000cbeiiccA0B00");
sw(150,"0defadAIAcc0a00dbeeAG0EDEGC00acdadbbkgabE00aimdALBilcCja00aqcBGbcBbcda0ebgGCBCFFaeha00bCCGSAKGgmh00EaHAeBAB0Bbe00EEOHiomkDLDC000IWMgbeCEAFC00ALRKDHbBCIJD00DBE0fd0ACCKaA0CMiB0fddFHCG00CC0BECCFKEE00");
sw(151,"0defadAIAcc0a00dbeeAG0EDEGC00acdadbbkgabE00aimdALBilcCja00aqcBGbcBbcda0ebgGCBCFFaeha00bCCGSAKGgmh00EaHAeBAB0Bbe00EEOHiomkDLDC000IWMgbeCEAFC00ALRKDHbBCIJD00DBE0fd0ACCKaA0CMiB0fddFHCG00CC0BECCFKEE00");
sw(157,"0accACLJFBbcAA0acaFbDcbe0JCA0ad0CAEBA0cBD00agaecfagfdbA000bccCBDcCabe00ddf0KEJFEF0i00eepcFJDFCclh00acog0LJHAccf000dgbalfaIE0B00AF0heiidaHDA00DEGffefc0HIb00CCDcfghdBCCCa0ANFDffheBaD000aAIFB0dabAcb0");
sw(158,"0bbb0cEFFcfc0A0baacaECBBAEEA0aAeC0ABeac0C00affcFAbfha0ba00baGACB0ccdba0baACFCGDHAAfa00a0BIGFE0ada00B0B0kAEacAa000BdFAfndiBFCE00baJEkmgdBHEB00A0JDeegdcGH000abFHdhccbBEaa0BMbNFgbeaFBC00BCELEABAEabb0");
sw(159,"0aB00fhcBad0bB0aCbbAa0fEefAB00AaFdecBkHaEC00DBgEIcbAADAD00CBAbHe0d0cDD00G0Afaegjb0GD0DKIFBidcLIDG00D0OAmnjkGHaEA0aBMaoaifdbeeA0d0IKdgBBahghA0dbJNJJCcdmhdA0eheEWH0bdhbeC0CABOICFAgECGCCGJHKKGLHJGHGC");
sw(160,"0ABEEDCDEFDD0A0AACCEBcBB0D0A00b0BAcdabEC0A000B0d0a00D0AA00aAabAac0DAaA000bcdabbcCA0A000aceecbBE00000aaefbbaA0a0000aadbDbBafbc000acaCECCcfcc000bdBEDDAcefc00aacAHEaabcfaA00cACCDCC00AaAA0ABAADDCABEAA");
sw(161,"0EDIEMJABJEJ000EaHAfKDLHEB00000ADAFJHFFEi000cFCdCNIFchAf00DHhfaKECcB0f0BbFfgeHekeGaf0AbaBABcgecLB00aBdFME0CacC000abiAPPPK0fEB000cqk0IAiED0B000iokdjdBI00a00eceebCFBAbib00elAjjJGDfggg00hjibfEhabgid0");
sw(162,"0bdghgbcbcAfba0bcbddFGCBaqca0aB0cbBIAFCgh00aBaBiFJFJDeAb00ABggdDCEAEAb0DaEBecCecbAFb0aaFFdBhldBGE00eACKNJACDaGAb0fcfIKQTO0bBcb0bcmjDNEeDBAab0b0hgdEGCNJBbb0bCDlibJMCBibA00nb[mCDFDfhi00bfhgi0eFHDeb0");
sw(163,"0bedJaNQmCcibb0bcbGcRfCNkEDb00ab0AGanEHKh000cl0aEhIAE0bf00DihFJKNIQBMf0daaFJECaa0Hhf0H0BClGqnkiEl00LBaCmoccs0Rqe0LBHEgbfcFM0de0eCamhIidKagee0cGaDbBbGGNMJe0CElHmkDcLb0bC00DL0ahcH0Gbn00beELeabBJiuc0");
sw(164,"0bbb0cEFFcfc0A0baacaECBBAEEA0aAeC0ABeac0C00affcFAbfha0ba00baGACB0ccdba0baACFCGDHAAfa00a0BIGFE0ada00B0B0kAEacAa000BdFAfndiBFCE00baJEkmgdBHEB00A0JDeegdcGH000abFHdhccbBEaa0BMbNFgbeaFBC00BCELEABAEabb0");
sw(165,"0cdeacbHFAb00A0cbabbACf0EFBA0aAGEbBBdekCH00acfeBDBgkdgg000ba0CEAbdggn00ab0ACFGALCdl00Baf0JKIWDiha00C0ccdEFBDAdE00D0ecdefjCICC00bACAfide0FFBaa0DKaa0cedHJgaaA0EBecchaELIb0CMCCBdbbDAFH00CCIOFBbbGCC00");
sw(171,"0aaAGDE0eEGF0a0a0BDfBacaCECa00aAaBDBC0faa000cc0ADCbgkdc000dcFDBaChjec000adEIHJCAAbb00aca0CcbCBBBA00aBha0AaCbCDCa0Bdljecabc0BAa0Bfikec0ccABAa0Acdd0acbbAaAa00aAAbccAa00C000FGEcabDbDBc000ADEBAB0a0b00");
sw(172,"0dcfafDGHAhfbB0d0dEBCdbabFCB0ad0Eaaa0baaFC0aaaaJaffhaDAB00baHDJAehAcdB0a0bBCGDAIB0cB000cbCDHGHDda00AcchoaDcaA0B00BcCbkmmdDaBB00abJIfqa0bDAaaaCcMKb0dceB0aaa0dGFFccgc0A000EOBUGecfaGGFCCFGLKHEEIDBDDC");
sw(173,"0eeicfEGCeifcA0eabGAFCAGaaCA0a0EIHA00A00BC0a0ABG0gigcBA0000EKEDcffBBb00A0AFEc0eB0BA00A0cCKBA0DE0D000AaBda0bGAED00AddAA0d0EBDE00be0begdjaHBBaa0dFbdckh0E00aac0GBCgefbDA000EKJOF000EEDDCCEDMNI0DEBA0CC");
sw(174,"00ACGGKJFDAG0B00ACIAECDHDCDB00AEFBcc00CBCB000BAEadgfbAC0000CG0bbhcB0A0000cA0dafC0B00000c0GAaBEB0D000A0BcdbBGCAD00AabaAbfaDEBE00AcdccfdhaGBB00AdB0BdfdbCBB00dbBDCabfb0BAa0BIIOFDB0DBACBBBDJOHEFBcccBB");
sw(175,"000DGEODJJFG0B000CGbNEGKGBBB000EJ0FGHAD0BB00BFDGCD0caaD000BHGFEbbgcb0000BDAB0Ddad00000BeAHDGECaAB0000feh0Ca0acB000gjeBb0bcDDC00ccldhjekBJB0aaAi0afiifaDccaaffCBaABbACAdd0BGKNCIEDBE0BBBBBHMMNBMEdeBB");
sw(176,"0fgniuACCbBdeb0fbeagKBdICgdb0afADkCAiaKnCA0acldDLFd0aDhF000bEGOABdbfeF0fFbDHICDEcdbF0cHBCEIMEFChc00CBDfqbLecebb00CBG0rpiBbBag000HO0jkEEAbDe00AHUQcPCAcFCd00CDIDECDCbACaA0CDfPoCEbCFGAAACDFaBJLSPHEAA");
sw(177,"0gflglBHBAheca0g0faEAdgBeaba0aebCcagghDfGA0achgENgjeEHgF00ejAHLifcBbgF0dAjFEFfFBDddF0cBCbBGEGGald00AdFhod0eD0Ba00ABKBrlsfDCBe000EQGfdBGacEf00BGUOGQABdEEc00EaFaHddbBDCbA0EIjLchdeFFHEAAGGIEDAIMLLMCA");
sw(178,"0dcfafDGHAhfbB0d0dEBCdbabFCB0ad0Eaaa0baaFC0aaaaJaffhaDAB00baHDJAehAcdB0a0bBCGDAIB0cB000cbCDHGHDda00AcchoaDcaA0B00BcCbkmmdDaBB00abJIfqa0bDAaaaCcMKb0dceB0aaa0dGFFccgc0A000EOBUGecfaGGFCCFGLKHEEIDBDDC");
sw(179,"0aacbb0ABAddc00a0cBBabcCdcc000a0AAdf0aGc0A000AadacABEB0C00aAAbB0A0EAAC00Bc0aaebbBBCC0aBcbbiceBHBB00aabffgbcBaAB00aabbbBaEadbc000abaABGDdebc000adCCFEacfga000bcBKD0AabcaA0AAaDC00aaCEBAACDDDCBCFFHFCA");
sw(185,"0bbeec0b00fgc00b0dDC0Ac0dia000baBCbdACH0dB00DGad0bACCCDA00bDD0C0CbFEaA0EacB0bdbdGDEA0Dac0AeecaMFE00abebAbbACAGD00a0jdDNEHbdAa000emgBHF0bbcb000ejgbAAA0hja000adeEBBAdaf0B0BaFe0BBBaABaBBCBHFAdbCACCCB");
sw(186,"0fgiDABDgaAFha0faeIAf0cDcgca00cfbJdcCGcBgE00AaFaCA00l00000hbKIFe0sdEA00IbeIKGCb0FAH00EfC0JgoiHMKK00d0hCAgdfJIFJc0afxlBObGbbIBc00vyoaaFdia0cc0dmpmeAbdagkcc0ceajIGcGfbgCE0EFHGB0dJDACeEEF0JOFAIFbACGE");
sw(187,"0eeicfEGCeifcA0eabGAFCAGaaCA0a0EIHA00A00BC0a0ABG0gigcBA0000EKEDcffBBb00A0AFEc0eB0BA00A0cCKBA0DE0D000AaBda0bGAED00AddAA0d0EBDE00be0begdjaHBBaa0dFbdckh0E00aac0GBCgefbDA000EKJOF000EEDDCCEDMNI0DEBA0CC");
sw(188,"000DGaHIIODD0B000DBcOeCEBHBB00faJcDHAcAfBB00aACJGD0fdfa000CDGJPBbheki00cCDbCCKCFabh00bEdehFNIHDdf00Adcs[0KdffeAA0ahDekpjhaa0AA0g0DJjucA0aacabEiHKk0ecbfegabaiBFEEchacAfc0BL0\\BJFccGDCBBBBFHKRHLJceBB");
sw(189,"000DGaHIIODD0B000DBcOeCEBHBB00faJcDHAcAfBB00aACJGD0fdfa000CDGJPBbheki00cCDbCCKCFabh00bEdehFNIHDdf00Adcs[0KdffeAA0ahDekpjhaa0AA0g0DJjucA0aacabEiHKk0ecbfegabaiBFEEchacAfc0BL0\\BJFccGDCBBBBFHKRHLJceBB");
sw(190,"0fgniuACCbBdeb0fbeagKBdICgdb0afADkCAiaKnCA0acldDLFd0aDhF000bEGOABdbfeF0fFbDHICDEcdbF0cHBCEIMEFChc00CBDfqbLecebb00CBG0rpiBbBag000HO0jkEEAbDe00AHUQcPCAcFCd00CDIDECDCbACaA0CDfPoCEbCFGAAACDFaBJLSPHEAA");
sw(191,"0fgniuACCbBdeb0fbeagKBdICgdb0afADkCAiaKnCA0acldDLFd0aDhF000bEGOABdbfeF0fFbDHICDEcdbF0cHBCEIMEFChc00CBDfqbLecebb00CBG0rpiBbBag000HO0jkEEAbDe00AHUQcPCAcFCd00CDIDECDCbACaA0CDfPoCEbCFGAAACDFaBJLSPHEAA");
sw(192,"0aacbb0ABAddc00a0cBBabcCdcc000a0AAdf0aGc0A000AadacABEB0C00aAAbB0A0EAAC00Bc0aaebbBBCC0aBcbbiceBHBB00aabffgbcBaAB00aabbbBaEadbc000abaABGDdebc000adCCFEacfga000bcBKD0AabcaA0AAaDC00aaCEBAACDDDCBCFFHFCA");
sw(193,"0aacbb0ABAddc00a0cBBabcCdcc000a0AAdf0aGc0A000AadacABEB0C00aAAbB0A0EAAC00Bc0aaebbBBCC0aBcbbiceBHBB00aabffgbcBaAB00aabbbBaEadbc000abaABGDdebc000adCCFEacfga000bcBKD0AabcaA0AAaDC00aaCEBAACDDDCBCFFHFCA");
}

void recognizer::teach()
{
  const int CYCLES = 5;
  const int DIGIT_FILES = 50;

  int c = CYCLES;
  while (c--)
  {
    for (int i = 0; i < DIGITS; ++i)
    {
      for (int j = 0; j < DIGIT_FILES; ++j)
      {
        std::stringstream sout;
        sout << "digits/" << i << '.' << j << ".txt";
        image_array arr;
        image_matrix matr;
        std::string str = sout.str().c_str();
        if ( load(&matr, sout.str().c_str()) )
        {
          addlr(&matr);
          matrix2array(matr, &arr);
          perc.teach(arr, samples[i]);
          std::cout << sout.str().c_str() << " " << c+1 << std::endl;
      //print(arr);
        }
      }
    }
  }
  std::cout << "Done!\n\n";
}

void recognizer::teach_samples()
{
  const int CYCLES = 20;

  int c = CYCLES;
  while (c--)
  {
    for (int i = 0; i < DIGITS; ++i)
      perc.teach(samples[i], samples[i]);
  }
}

int recognizer::count_equal(const image_array &arr, int sample) const
{
  int res = 0; 
  for (size_t i = 0; i < arr.size(); ++i)
  {
    if (arr[i] == samples[sample][i])
      ++res;
  }
  return res;
}

int recognizer::sym2num(char ch)
{
  switch (ch)
  {
  case '.': return 0; // white
  case '@': return 1; // black
  case '%': return 2; // light gray
  case '#': return 3; // dark gray
  }
  return -1;
}

void recognizer::read_image()
{
  image.clear();
  std::deque<int> arr;
  bool emp_str = true;

  while (emp_str)
  {
    arr.clear();
    char ch = std::cin.get();

    while (ch != '\n')
    {
      arr.push_back(sym2num(ch));
      if (arr.back() != 0) emp_str = false;
      ch = std::cin.get();
    }
  }

  //image.push_back(image_array());
  //std::swap(image.back(), arr);
  image.push_back(arr);

  while (!emp_str)
  {
    arr.clear();
    emp_str = true;
    char ch = std::cin.get();

    while (ch != '\n')
    {
      arr.push_back(sym2num(ch));
      if (arr.back() != 0) emp_str = false;
      ch = std::cin.get();
    }

    if (!emp_str)
    {
      image.push_back(image_array());
      std::swap(image.back(), arr);
    }
  }

  erase_vert_gray_lines(&image);
  cut(&image);
}

void recognizer::fill(image_matrix *img, int i, int j, int *max_j) const
{
  const int width  = static_cast<int>(image[0].size());
  const int height = static_cast<int>(image.size());

  if (i == -1 || i == height ||
      j == -1 || j == width  ||
      (*img)[i][j] == 1)
  {
    return;
  }

  switch (image[i][j])
  {
  case 0: // white
    return;
  case 1: // black
  case 2: // light gray
  case 3: // dark gray
    (*img)[i][j] = true;
    if (max_j && *max_j < j) *max_j = j;

    fill(img, i-1, j-1, max_j);
    fill(img, i-1, j,   max_j);
    fill(img, i-1, j+1, max_j);

    fill(img, i,   j-1, max_j);
    fill(img, i,   j+1, max_j);

    fill(img, i+1, j-1, max_j);
    fill(img, i+1, j,   max_j);
    fill(img, i+1, j+1, max_j);

    break;
  }
}

// 2,3 -> 1
void recognizer::make01(image_array *arr)
{
  for (size_t i = 0; i < arr->size(); ++i)
  {
    if ( ((*arr)[i] != 0) && ((*arr)[i] != 1))
      (*arr)[i] = 1;
  }
}

image_array recognizer::next_image()
{
  const int width  = static_cast<int>(image[0].size());
  const int height = static_cast<int>(image.size());

  const int mid = height/2;

  image_matrix matr(image.size(), image_array(image[0].size()));

  while (pos < width)
  {
    if (image[mid][pos] != 0)
    {
      fill(&matr, mid, pos, &pos);
      break;
    }
    ++pos;
  }

  if (pos == width)
  {
    return image_array();
  }
  ++pos;

  cut(&matr);
  addlr(&matr);

  image_array res;
  matrix2array(matr, &res);

  make01(&res);
  return res;
}

int recognizer::recognize(const image_array &arr) const
{
  int res = -1;
  int max_equal = -1;

  image_array a = perc.recognize(arr);

//DEBUG
/*
std::cout << std::endl;
print(arr);
std::cout << std::endl;
print(a);
std::cout << std::endl;
*/

  for (int i = 0; i < DIGITS; ++i)
  {
    int eq = count_equal(a, i);
    if (eq > max_equal)
    {
      res = i;
      max_equal = eq;
    }
  }

  return res;
}

void recognizer::make_weights_file(const char *file)
{
  set_samples();
  teach_samples();
  teach();
  teach_samples();
  save_weights();
}

void recognizer::load_samples_f()
{
  image_matrix matr;
  for (int i = 0; i < DIGITS; ++i)
  {
    std::stringstream sout;
    sout << "digits/samples/" << i << ".txt";
    load(&matr, sout.str().c_str());

    image_array arr;
    addlr(&matr);
    matrix2array(matr, &samples[i]);

    print(samples[i]);
    std::cout << std::endl;
  }
}

void recognizer::print()
{
  for (;;)
  {
    image_array digit = next_image();
    if (digit == image_array()) break;
    std::cout << recognize(digit);
  }
  std::cout << std::endl;
  pos = 0;
}


//======================= MAIN =========================
int main()
{
  recognizer rec;
  //rec.make_weights_file();
  rec.set_weights();

  //for (;;)
  {
    rec.read_image();
    rec.print();
  }
}
//======================================================

