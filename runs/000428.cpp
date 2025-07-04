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
  void init_weights(int n);
  void change_weights(int v, int d, const image_array &x);
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

  static bool have_column_white_and_gray_pixels_only(image_matrix *matr, int column);
  static void insert_empty_column(image_matrix *matr, int column);
  static void insert_empty_columns(image_matrix *matr);
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

void neuron::init_weights(int n)
{
  for (size_t i = 0; i < w.size(); i++)
    w[i] = rand() % n;
}

void neuron::change_weights(int v, int d, const image_array &x)
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
    neurons[j].init_weights(10);
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
      neurons[j].change_weights(v, d, x);
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
: pos(1), perc(img_side*img_side, img_side*img_side)
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

bool recognizer::have_column_white_and_gray_pixels_only
                            (image_matrix *matr, int column)
{
    int height = static_cast<int>(matr->size());

    bool w = false, g = false;

    for (int i = 0; i < height; ++i)
    {
        switch ( (*matr)[i][column] )
        {
        case 0:
            w = true;
            break;
        case 1:
            return false;
        case 2:
        case 3:
            g = true;
            break;
        }
    }

    return (w && g);
}

void recognizer::insert_empty_column(image_matrix *matr, int column)
{
    int height = static_cast<int>(matr->size());
    for (int i = 0; i < height; ++i)
        (*matr)[i].insert((*matr)[i].begin() + column, 0);
}

void recognizer::insert_empty_columns(image_matrix *matr)
{
    size_t j = 1;

    while (j < (*matr)[0].size())
    {
        if (have_column_white_and_gray_pixels_only(matr, j) &&
            have_column_white_and_gray_pixels_only(matr, j-1))
        {
            insert_empty_column(matr, j);
        }
        ++j;
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
sw(  6,"0ABEGLUQGHdBAC0AAFRFFeDI0FDC000DG0bgbbEKCB00aFbGpgdcCGE000acGCGBiFKLG000afBFH0kcGMA000cmaEhkiAb00000hlebADEaeCda0AjjADBEJCfaBa00defbA0cAFCaa0FjAe0daadCcCa0BhEBD0efCCdda0BPOPA0gheAEgBBBDPKEDA0fflBB");
sw(  7,"0ABEGLUQGHdBAC0AAFRFFeDI0FDC000DG0bgbbEKCB00aFbGpgdcCGE000acGCGBiFKLG000afBFH0kcGMA000cmaEhkiAb00000hlebADEaeCda0AjjADBEJCfaBa00defbA0cAFCaa0FjAe0daadCcCa0BhEBD0efCCdda0BPOPA0gheAEgBBBDPKEDA0fflBB");
sw(  8,"00ADFHXMKNaAaB00AELBTaEGACAB000CJfDBCGKCBB00AGDGj0DaDaH0000AIHLBAAHJF000ajCLIBiBNPa00caqfHeahbecA00cgrinbJEgnddb0bjnfDeFGacCab0d0qmkfdd0KCccaHqbcfj0CcCgbcaBnAAc0bAIDmhf0BQPRdCedfDCiBBBBQPKJcMCgnBB");
sw(  9,"00ABDG0HOKIF0000ADaFFcCAGI0000AGc0cEbBbBb000fJbcAboejjhc00dpkAgdncADpc00gfHc0BDKEikc0AdEhGJCYKbjc00AahGHJCGPHAC00ADc0MLAHNMHD00CFcgaH0kCBCCAAHHaaBFF0FPYaAAA0HeodaaaELIA00CFkgcecGaCA000cFAcfbhbH000");
sw( 10,"0ACGNMbaCNPPaa0ABHfeH00AIJCa000DBDHDDAmBa000egfCLAehlkh000efAa0aejmpg000aCaiDCBHjjc00B0LIBcdKLHCK00BMH0Cki0FJ0J00IC0hmgcadAHb00Gg0aceCgBaGb000acaJC0BgBBd00ha0BBDEcfcBF00bcIF0BDBCCaC00bCbHDCEEAfb00");
sw( 11,"0ACGNMbaCNPPaa0ABHfeH00AIJCa000DBDHDDAmBa000egfCLAehlkh000efAa0aejmpg000aCaiDCBHjjc00B0LIBcdKLHCK00BMH0Cki0FJ0J00IC0hmgcadAHb00Gg0aceCgBaGb000acaJC0BgBBd00ha0BBDEcfcBF00bcIF0BDBCCaC00bCbHDCEEAfb00");
sw( 16,"0BDHFKFDEIEH000BBFDDFBDDDG000000Bb0aBaCBa000c0dda0A0Bbaa00adedaAdCAbaa0aacddb0abAaba0aa0cdacC0b0b0000ab0a0BBAcb000b0baaa00bcb000abbaEAcAbcb000cd0EAAC0bbb00bcd0CCB0bcca00bcaAbBAaddc000baebc00cedc00");
sw( 17,"0BBJNNJCaKNOaa0B0FDfG0aCGNBa00aBaDBAGBfDb000gbaca0adiida00efBabbaceg0a0abg0DCFaAccba0ad0baegBEbBB000Dh0AbbBaFaA00DbikcdcaccBC00DfijbbAdAaAB00AekbFAbaa0c000dcbAaCCBcdaA00cCIBdAcAbC0b00d0BCb0Dcgjfa0");
sw( 18,"00ABGOKGNKaD0C00ADJFCbADBICC000CDBBcDbAGBC00eCAAfbeebdD000deCaCdj0IHe000djCGBab0GBe00ckmbHFbDJAic00chrdFIDJJadd00aipcEE0OEaDa00BenibBbedECa00Deeic0afg0Fc000bDe0Cfb0C0Ca0CLKDBCaeABBACCCCKDBAB0gdcCC");
sw( 19,"0ABEGLUQGHdBAC0AAFRFFeDI0FDC000DG0bgbbEKCB00aFbGpgdcCGE000acGCGBiFKLG000afBFH0kcGMA000cmaEhkiAb00000hlebADEaeCda0AjjADBEJCfaBa00defbA0cAFCaa0FjAe0daadCcCa0BhEBD0efCCdda0BPOPA0gheAEgBBBDPKEDA0fflBB");
sw( 20,"00ADFHXMKNaAaB00AELBTaEGACAB000CJfDBCGKCBB00AGDGj0DaDaH0000AIHLBAAHJF000ajCLIBiBNPa00caqfHeahbecA00cgrinbJEgnddb0bjnfDeFGacCab0d0qmkfdd0KCccaHqbcfj0CcCgbcaBnAAc0bAIDmhf0BQPRdCedfDCiBBBBQPKJcMCgnBB");
sw( 21,"000DGEODJJFG0B000CGbNEGKGBBB000EJ0FGHAD0BB00BFDGCD0caaD000BHGFEbbgcb0000BDAB0Ddad00000BeAHDGECaAB0000feh0Ca0acB000gjeBb0bcDDC00ccldhjekBJB0aaAi0afiifaDccaaffCBaABbACAdd0BGKNCIEDBE0BBBBBHMMNBMEdeBB");
sw( 22,"00AAAAGDFAAB0000ABBCHEDDBA00000ABAFDCBD0000000BBCCBBD000000ABACCBADA00000BAACCBACB00000BA0DCCBBB00000BAACCCBBB00000BA0CCD0BC00000BA0CEC0BC00000AB0DDC0CB00000ACBDDBBC000000ADAEECBC000000AABGEFD0000");
sw( 23,"000BCCKIDBaB0A000ADFG0BC0CAA000BDCcbbBDDAA00A0AAAedABDA000AbBAAbeAADA000AcDA0cbBBCA00AACADFfBF0AA00AAFGFCdAFDDB00ABGF0DfDE0CB000CDBBEaAA0CB00BCGHGFC0AFGB000BCCFAca0AAAA0AACECBaBCCCAAAAA0CABBFBc0AA");
sw( 24,"0ABDGRMKFHAFAA0AAGDGCCFGCJDA00AHDAE0AAbEc000fDdbgbkebj0c00fedc0AfCCEec00ibAFDDD0CCic0bkgCHIdHDBhf00benDIKEPAa0g00ackbJ0EHFEJC00ACijdbgiCKGB00C0cndgeaaGKA00A0EglfbdFDDAb00LJa0Aag0Bab000aGEDAejjkjb0");
sw( 25,"0BBJNNJCaKNOaa0B0FDfG0aCGNBa00aBaDBAGBfDb000gbaca0adiida00efBabbaceg0a0abg0DCFaAccba0ad0baegBEbBB000Dh0AbbBaFaA00DbikcdcaccBC00DfijbbAdAaAB00AekbFAbaa0c000dcbAaCCBcdaA00cCIBdAcAbC0b00d0BCb0Dcgjfa0");
sw( 31,"0abbBCKIB0dd0A0abBHBBBCB00CA0abDHDGCB00D000adA0bh0kgafBa00ccAaaaaBCEba00feAHDGEBEDfa0bilaNOGF0Bhc00beqCDLCIH0Bd00acmbMABJFHGC00ACjmfcii0KFA00B00oiijaAIG000a0BflfgADFBAc0AKJbcceaBccb0000JEDAebfeha0");
sw( 32,"0deeAaQOabjfcC0dcbTACg0FfABC0bbBFDaigAHHCD0b0FCGjfdeBGG00000KJMBbAOMG0000iFODCmdHLC00abreEcei0cca00agqdgFDAbcBeb0akhCDBDIFb0Db0cdeideefdIA0b0DiDdhjfeaFbCb0BeB0cghfGFff00EQOLCbecaACeDDEDRGGAdDcahDD");
sw( 33,"0bb0QKOPaP0FaB0b00RA0j0cdSDB00ftBEbbBIghAD00cEDabecpjDJA00DGUELDDnaCCA0aFlP`HImeHABA0fAogI0gjCDIc00eepggGHFoAaE00deDEhrlGaqAB00AEPMBscGfABa00HAACcDbdBAj000EiBaEAleaAddD0DSGX0heebDJEDDDAACEaDKBa0DD");
sw( 34,"0abcdksjjACEba0aadmfNEdiDeba00aJFjGNFBkjb000AaaeRL0Beia000CIecEbCmvmo000CMfl0aFHljh00aHHBcHPPE0A000aIJeaaEaC0cEB0aEBAfcBlkEGgB00AaHbfacbBFeAa0bBbicibAfdjAacAE0dIFba00Kb00feehKHCCaAI000amdEKbBIAF00");
sw( 35,"0cdfhptid0HCca0cchqcUCegJeda0bca0hAIABdma00bbediPKAGfkb000ABfeBBCdokn000ADbgBHDLejk000GIDeMFNJaac000GNBaCAdACa000bKGDhb0fbCEi000HEGaBCEBcFdAAdFGJaIE0H0FfAAdBEbeIMHAbcKA00lkpoFKFGBAE00acngjIDbNNJa0");
sw( 36,"0deklreebbagec0daecaFcdafmhc00f0bfbFcbKmaA00AdBhLIALAacE00accDKCDCBAdE0bAhbADbaABaEE0eAcahaAiEHe000cccedADjCf0b00baBEfDDM0kdl00CAaABINM0nei00ABCMANKaCihg00Ba0bIFHGFdiaA0AghemBDDECBaAAAAAlhDEJQJLDA");
sw( 37,"0bbjqoFHEnxoAE0baeHIBgDGieCE0aafCbfeegJEDB0aCEABjkCJJOG000D00HCDBPVRG000A0IDfcfkKJC000bdiAEejbffi000pfAbEBEBjDfa0f0ENHF0KHadDa0gFF0bJDDaEgCa0CCKckBBGMECGa0JABcdgcAFEfiB0FJicdBfmEdEcBBFEFedibEBJaBB");
sw( 38,"0DEIbEROMGlgbE0DACFHAbFDgHaE00AGJ00fCeDJDA00DIbGrjdBJKK000CDCbbFfLNME000abecaiiAEK000ccifDfefbAdb00ciggdDEFAlad00cdFIFBGLBidB00aDDC0b0cEEc0aaEiIaAkABBAc0aaCfFHDbgiBCdcb0AIaIHFcocdECAAAEIBC0bdhdaAA");
sw( 39,"00aafcCKFgmfBC00abDD0a0ddGBC00bEGcCCbiAAE000aBeAgbdbGCE000aAc0aFBIHAe00cbBdF0BDFCAj00dcleaJIGadqj00afgdaLLHAlaf00bcDIEiaBGBcD00aKG0aheCaF0C00EDKbgg0aACFB00EBDBghghEBACc0CRcbCbgo0dBC00BAIa0CjcdDbb0");
sw( 45,"0debCABBIAAIdA0db0LAlAhdADbA0acmAMgdBFeiaD0aeLB0beeeleCC00jJNEBdCpdEdC0DbnQZKKfaFcBC0edoiQDAbKN0D00ibvaEIaCIFbHa0fcrbFIEPDlLCa0BfgeAfEciBHCa0BAcec0bbFfhca0AAKdF0kBe0eDD0DLBDCde0aAK0DDDABGEgDHcCEDD");
sw( 46,"0cccIENLDGDJcB0c0bOCgdBbBI0B00cxAMfecJageE00bECAcffekCI000cKMIICIl0JG00EajL[HLmdHCG00adqjMdomELMC00fdpaE0BAcB0Da0caeHC0BJBnEAa0BbJEBhADcAF0a0Dd0hecaCKckAa0BhDe0ahbeAleE0ELELCcc0AFE0EEEaBGDgbEd0AEE");
sw( 47,"0bbaJDBEaBHGbb0b0abfDADF0BDb000hDaCCddicc000agaCI0hfnfg000AAFDGFCfjhB000CEACDIb0cCC00FCGGJbgcCEKJ00FGGDimggfGHF00JaFckhaheCDA00CfFBffccECA000AcEABBg0AB0A00eeaCAb000bbb000BDPDcADaE0c000ADHGADACdga0");
sw( 48,"0bbcdftfcBCCbb0bacqaGba0Gbcb0aadjBdAeeedba0aacgdI0dGgae0000fgdebeAjhf0000FcjgAECjlc00BDMFgFeGLCd000BGPGEcgcFHEA00AMJIibdcCaDc00ADMH0ECBAjCa00gKDGFLGAFaH000cFAbBBGAcfEEB0akfld0E0HCBEaaabmgeaCbIJFaa");
sw( 49,"0accefcfdACeba0abdfdGCAcBcca00cecdCF00Afc000de0fFJCGacd000behdDHFFbcc000bdbbFFACbda00abbbdD0bAddc00abcABBAbdddb00aCAEaAGCAfac00ABCCBGIGDda0000BCEAEJCFa0000A00egDJFCbeb000ehpmBEBabeb00acglhE0BGCBa0");
sw( 50,"0accefcfdACeba0abdfdGCAcBcca00cecdCF00Afc000de0fFJCGacd000behdDHFFbcc000bdbbFFACbda00abbbdD0bAddc00abcABBAbdddb00aCAEaAGCAfac00ABCCBGIGDda0000BCEAEJCFa0000A00egDJFCbeb000ehpmBEBabeb00acglhE0BGCBa0");
sw( 51,"0ACGFEJFbGBE0A0ABACKGcCHeCAA00bgbbcfdaMGbA00AAgfEoEEILC000Ch0bGDaNKGN00b0kEagldjbEH000aHeohrrEbAb00BcDAgbiBc0Cf00AFRIiDdCHmhb00aALHcQAFEmmb00aABLGHHJDkfH00CaaBGCCC0hdjE00jhDcabb0DCcAAABjjkdGDFCEBA");
sw( 52,"0DEIbEROMGlgbE0DACFHAbFDgHaE00AGJ00fCeDJDA00DIbGrjdBJKK000CDCbbFfLNME000abecaiiAEK000ccifDfefbAdb00ciggdDEFAlad00cdFIFBGLBidB00aDDC0b0cEEc0aaEiIaAkABBAc0aaCfFHDbgiBCdcb0AIaIHFcocdECAAAEIBC0bdhdaAA");
sw( 53,"000aigCEJgpk0A0000IB0Eabfb0A00AIDC0cagE0a0000GcChBfAGaGa00bD0ehaBENFfa0AcCbEf0DBGAha0agmeEJIFe0lf00bckBGNFMJiFc00b0hJSCCHFG0F000GegcdcdbKCE00BDCfknh0FFBD00bEKDnmfbGEaBe0AMBgCaelDfbD00AbAdBeidg0db0");
sw( 59,"0cccIENLDGDJcB0c0bOCgdBbBI0B00cxAMfecJageE00bECAcffekCI000cKMIICIl0JG00EajL[HLmdHCG00adqjMdomELMC00fdpaE0BAcB0Da0caeHC0BJBnEAa0BbJEBhADcAF0a0Dd0hecaCKckAa0BhDe0ahbeAleE0ELELCcc0AFE0EEEaBGDgbEd0AEE");
sw( 60,"0dcdI0GJDCBLdA0dAeLAjd0ABHBA00AkDMegDEfa0E00ACAFafkhncH0000IRDHDCse0D00GBAIKEIq0BAH00HBbfPblbKFJN00ACdEFdceHC0M00CDaDBC0OdkEb00AeGI0lBBd0Ac00BcGdc0gCCBgc00bkFdL0iAd0f0E0EGAREAbaDFIFEEFbEPLADACCcFE");
sw( 61,"0ccaHEebAEKGcb0caAeiDE0bBB0b0aabAEEAackcb00aefaBIadgmej000cbD00cAinke000AACaEFECef000BaEDF00HEFAG00BIEAAgfbDEDF00GBcehfefdDDb00EdAbeecgcBDa000CCaCAfee0Bc00dBAABbaBb0CB000aEHAbCFBBA00000AGEBCBBaa00");
sw( 62,"000acceccB0c00000afacdeeaAa0000bgbebe0Ca0000bcb0CcAFC0b000bidadEcFDAb00abeCaaBBDBbc00bbEAfBdcEabe00adEGFCaADB0ba0cDIJaABDFdaba00DGBDIFDBea00A0GCFGGKEGADB0ACB0d00EACbBBC00cilhcabCBaa000aglhe0dDEB00");
sw( 63,"0accefcfdACeba0abdfdGCAcBcca00cecdCF00Afc000de0fFJCGacd000behdDHFFbcc000bdbbFFACbda00abbbdD0bAddc00abcABBAbdddb00aCAEaAGCAfac00ABCCBGIGDda0000BCEAEJCFa0000A00egDJFCbeb000ehpmBEBabeb00acglhE0BGCBa0");
sw( 64,"0accefcfdACeba0abdfdGCAcBcca00cecdCF00Afc000de0fFJCGacd000behdDHFFbcc000bdbbFFACbda00abbbdD0bAddc00abcABBAbdddb00aCAEaAGCAfac00ABCCBGIGDda0000BCEAEJCFa0000A00egDJFCbeb000ehpmBEBabeb00acglhE0BGCBa0");
sw( 65,"00CEBFAABKCca000CC0ICgAag0c000bCc0fbcdJ00A00aBbdEhcGBCcB00bkcAACeHDCdB0ccpFdagdgBb0B0fcDdmigbIBeg00chAB0bc0FAec00fCGDeEbCGnff00ACC0CQJFbphf00aBbMOJOBajb0000ccbIA0aEcd0C00gdbebDBDHCAAABCchiaIEFKNEA");
sw( 66,"0DEIbEROMGlgbE0DACFHAbFDgHaE00AGJ00fCeDJDA00DIbGrjdBJKK000CDCbbFfLNME000abecaiiAEK000ccifDfefbAdb00ciggdDEFAlad00cdFIFBGLBidB00aDDC0b0cEEc0aaEiIaAkABBAc0aaCfFHDbgiBCdcb0AIaIHFcocdECAAAEIBC0bdhdaAA");
sw( 67,"000eieFMDjrjBC000fJBAAD0dcBC00BDFBD0feEGa000CCbGleaAIGEb00BAA0aFEFPI0b0AADBGeBAaCIdb0CbjbEEEekgea00BcgDdLHEdiHc00BaCQLBCAEFbG00bFGbejmc0MaFaaDCJakphEGKEGaaDDEFikccDB0cd0CKbbABenci0a00CcDaCdlihbpd0");
sw( 73,"0ccbHAGGgaGDcc0c0eAeEEEG00Fc000fAHFCIAlEe000agBCICgflgeb00eDHbBCHmkaEb0HbJEBbFffbEGb0NaNDNAiaFCTP00FMFJCkqiEIMH00KJfbAJFAgGK000Dkcakjel0DEb00ddbfbbr0cE0A00jgf0dcBGcBdf000fIIaaAIb0ca000ABKGbafghha0");
sw( 74,"0bb0I0HJCaEK0a0b0fFdgADEDIGa000fFJb0B0led000Bb0Ga0iopgBb00bDGCBGEpjAAb0G0AEMANkA0HCb0HBAbTFdacDPK00AFaLCCd0beIK00DD0BJAICe0FC00AbFFakjcECDE00C0IcAfkBEI0C00ahC0dhfbcDB000AD0KF0cebEAa00AfBKIaekdelb0");
sw( 75,"0bcfBAAEBKIdAa0bbANcFhAkbHBa0acecEcikAce000afC0j0ddgpeb000dgeDbEeK0Ch00ffnSYHOCPQgl00mlje0DjdDain00gesbFWJCjEAee0cacGDfCGHaBAe0AFMgFOAIcfGCe0BKDG0MMEFELDe0GDDfpchCCCbEB00IGDmlkCAGDf000cbg0gIdEIa00");
sw( 76,"0efiCAAaaFJfBe0eaFCBGbAeFECe000bfGgdeBbB0000hrCdEAcGech000ksdCbdaBd0f00aidLRFKHIBke00enEaeBgkHJde00dAhCDJbdgOHed0acgdcabaFaEed0CbbpFPBbedEAaCaJfDHRKa0LHBaCAFghkcaFBFaEE00dDesgfLEGdd000ddcefGcHAD00");
sw( 77,"00bcBEFgfDJG0000bcFmFCBADAB000eACaGEEFfec000cfCbFICapfc000cAFCCaLjric000BbbKJNFCcdb00cAdbECDBEDDA00cDjdcDD0jADCb00fsobdGci0Ebb0AdllbdA0a0Fbb0AbdcaAbD0BBeb00dBciCCF0ab0000CBBlGFDdD0g00bc0AEIEDFeeb0");
sw( 78,"0dflaAbheIMABd0dbaBcKDBgEbBd00eeBaACdC0cc000gmDeLKFKhig000if0CBaHAhhj00agBFOGPMFAkf00fi0AgKEbMFaf00eCndENF0hMIcd0acrifgFBC0Hgd0Bdnp0IBABfGbcAaBi0cLEFCGFbcACCfjlAEJ0DbAB00fcjuAANDJci00aeijbbFCQa0a0");
sw( 79,"000BGJDHOKA0BB000FHGIjagDMDB00aCC0bdggHFGB00j0kcffldaAdC00goiDAbgROFfC0jgoDIE0FHNbkC0miciiBfFPaxl00cfkkcKILEAfhb0beAacgdJMbbAb0AHDlDQHEchBbaAEIaDFSQ0fCHbaAE0AbeacfFAcCC0BODAfigeHFGfBBBEKbd0IHbJCBB");
sw( 80,"0DEIbEROMGlgbE0DACFHAbFDgHaE00AGJ00fCeDJDA00DIbGrjdBJKK000CDCbbFfLNME000abecaiiAEK000ccifDfefbAdb00ciggdDEFAlad00cdFIFBGLBidB00aDDC0b0cEEc0aaEiIaAkABBAc0aaCfFHDbgiBCdcb0AIaIHFcocdECAAAEIBC0bdhdaAA");
sw( 81,"000elhLJAlrla0000iDCGGEJaka000FEF0Ea0FNNg000BfBDcdFDLFAg00DAeeCDK0OIKg0EADgkeggjBNDg0PAG0ECbmjhHF00KEFKaaede0Ib00JCAAGPdicLaG00dbkggclkFNhDaabddejklFFFAIaac0jClbEEDAfhb00dBaa0egffdc000hFHcjimcfkc0");
sw( 87,"0ccbHAGGgaGDcc0c0eAeEEEG00Fc000fAHFCIAlEe000agBCICgflgeb00eDHbBCHmkaEb0HbJEBbFffbEGb0NaNDNAiaFCTP00FMFJCkqiEIMH00KJfbAJFAgGK000Dkcakjel0DEb00ddbfbbr0cE0A00jgf0dcBGcBdf000fIIaaAIb0ca000ABKGbafghha0");
sw( 88,"0ccbHAGGgaGDcc0c0eAeEEEG00Fc000fAHFCIAlEe000agBCICgflgeb00eDHbBCHmkaEb0HbJEBbFffbEGb0NaNDNAiaFCTP00FMFJCkqiEIMH00KJfbAJFAgGK000Dkcakjel0DEb00ddbfbbr0cE0A00jgf0dcBGcBdf000fIIaaAIb0ca000ABKGbafghha0");
sw( 89,"0himfdhacCNFeh0haAdgIACFGgah00DchEbbdBaAh000eeacLHiCmhm000kkecif0bhCe00EfCL0APFcdmD00KaOAKImGOHeJ00FKDOQgqhNPK000FLnEJUHKADJd00EhkqfQBl0hKdBBhOdcOTabCNHaBBiGAic0JOhBBEE00kDqiACNICd0000dBAbaCaDKD00");
sw( 90,"0ghhcdkBFGJMAd0gcAAAcabcGICd0bcAcBeBeadid00bfJAd0Cqhulf000fleBdbkeh0n000ccPJAPJEDje00a0DcLNhOJKeb00aDgNHLeIIHGE000ElEMIIPJCIC00CDBbEMCdEAGD00CNF0AND0HTPC00CAOoogcG0IIHA0AAcoihhBLGF000AdCabeAc0MB00");
sw( 91,"0bdheebaN0Faa00bcdbeMFCBJgA00a0HEiGFDBheB00a00aAGOhcmua0000B0EBc0nhfm00BAJ0BHJENF0j00ECCARQSWCbfF00CFjbbFLAHBcF00DBqmKBHBBUNe00bapjgnej0NPdaa0aakoejbBIIkaaebEgo0FAcBbHf0AECdhEAb0egA000AIEKQeBECha0");
sw( 92,"00ccbBeGSKJIA000c0dALdGcLDA000cHCaCF0EaCc000eF0cEIjflngc000cd0BDlaecrc00c0EADJDOEdnc0ABaeBOIZGjh000AFjBDJIDIEbB00BFkcCJIEGIPc00ADggfICh0DOa00CHbge0CBCPSh00ACJiqhD0cDaK000bBonBAbEabc00cfA0eIfbDJcc0");
sw( 93,"000ABDGcIOJCaA000BhDBbDLbCAA00DTbDfcIaDJCB00k0beEBcDfdk000fvkBAffDA0c000bcbvFjcfgdC00BbTEeedCOAbF00B0KCJrkfWR0000BcjnbUAcIBAk00EjvpaYJj0dehBBAahCNPJca0IeBBedi00bEBeBaaD0AkMcfBHKHFabBBAELO0cGECHICB");
sw( 94,"0gefDdHCfCGEgb0gBdDhbGEHdDBb00BecLbdIFdEbE00ABDGBcbekcb000cEMCFBDucCE00JAEIB00leBEM00MAJaNhlhMEQR00CFDAbrppNPDL00EFggfMcCiCJ000BpgbefEdeaDc00ckeeACiabfeA00gicaNCbIfaddE0E0ESCABNcIAAEEGCJRI0Hb0AAGE");
sw( 95,"000bbbLDcihd00000dHDACDGai00000cDBadEEFFe000E0BCcdFFHEFc00AFBcaBHdFFLc0HbDE0bcijAHGc0KbEEHdjqgCJF00C0AJEbjieAJ0a0BI0AHLBadACBa0babBAdecFFbBa0cc0eeghJD0bGa0bdeddcDFbAei000i0ceABbibee000f0Cbhdfbigb0");
sw(101,"000aaeebb0bA00000ekaEABCAb00000cCaacbeb0b000AbcDDcAbbAc000BD00Da0gfd0000EKBfacdihAB00EGLHBbffaCED00ECMEAdijbFHDA0DAMFaaficBABA0aAIGach0DAbBA000GBaahADadAA0a0aEBAbb0ebe000fAIa0b0ea00000beDFCD0C0db0");
sw(102,"0aafhje0jcaBaa0a0ecBAEJH0iaa00BA0cgcb0EBc000EAea0aDK0Fbb00DddjbA000DGb0DAHBkjdifhBJb0JFOGaAsfDbIH00FDPPHgmlGINA00DJKICKEBCCAA00baHEeFa0IeBD00e0GFBH0IJEDE00acadbAJDbdEhB00oeggABDBD00000cifbfAeEDd00");
sw(103,"0cceqoobHCcfa00cadhEbBAADea00aaAgdgafbdg000a0MdaaFgBieh000cdf0g0l0bBo00AcDKcaCCCBlc000HDELOfXEEjb00aBIPONgFJBBE00gKcLLRMPE0FF00cJCA0MEcAdIF00dKG00IDFIKK000aBNkiccD0CFBA0BcgyfBf0M0DC00B0biaicfBQD00");
sw(104,"0aacnmlfLdhB000a0ceclBaeFd00000BBBc0Aaea0000BNhGaAcejff000cJe0iainlbq00CcEBadB0Cfia00aDCARKLYaAeI00d0DIMHaAPfFNA0dBeAQMKEFCABA00AAacedh0AGE0a0CFgjfhBEDEh0a00MAjcbchBHDa0ABgjaBcfFcBG00AaAgJbgg0JE00");
sw(105,"0cckxumiNlkfaA0cbechILdAJoaA0bCKHfJKDcaeF00bdEjGOSbaeld000dRlAecBjdep00BdKhgaCCFEdg000DAaPOTYFgoI00bCADdDEAPkaJA0bCmARILdcRGdA0aamAkgckfFKA0a0fFhpnnhGbal0ahfL0jBKFBdIBj0BFisbKclFifH00BAEaJKmCFFc00");
sw(106,"0A0AsdlfXAgKAA0AaCdAJDG0Lc0A00bMDaEDfaDE0000bGmEIKgCDefa00c0qhiciI0bsa00fAgnfbIFAnla0bCEeBNM]Ijsa00bBJHGHHEThb000eEaIHSP0GFId00cG0bgUCkCbMc00aBF0Dc0GECLm00cbPaefGaAd0F000fo]kFEjEkd000bbjkjElAALCb0");
sw(107,"00BBCGADNOBC0A00BDEGDc0DHKAA00AIdEeAACAEBA00dGcfGfredbeA00fjbA0dnBBIoA00ejLbDb0DLhhA0ceCiDE0WTBnb00ceiAHFbGTGgH00cAdaAOALIADC00CEfeBNEfbfaa00GIdAJMPeCCVd00000eAbgeACIHA0AEHfd0aAEDHBAABCJG0eAabIFBA");
sw(108,"0hhmceIB00gfhc0h0iBeEFBLe0Ac00EFGGAcGBCIAE00acCLFbDDcbb000b0ICJdGoBBD00FHFAhbekodBJ00OHR0KbbeFCKO00ILDDhvqnLMHJ00J0kkbLdaAJHb00ApskhediEGai00cmefabmbea0000ihhAG0DGABcbC0EaHKF0CIbDcDEEFBPVKBbaE0aFE");
sw(109,"0ccdBbLJ0caccc0c0bAeGJGP00Dc00GEDDEBCBaKa000fo0GLDEBahee00bg00EAMi0bHe0EBKckbbdhfEDe0PBSCHGdcaANK00KOJGdilhIFMD00NAhiCL0fcRHB000oohmehuGHBa00decjdfpAcDFD00jelDeCGICbBda00aFBAa0FgceB000bJSHBghAfka0");
sw(115,"0aaefidadAcCaa0a0fjAFBBF0eaa00abbaecebD0a000Adk0GcEIaCf000DeecFEAC0aE00aCCbfecbegaF00FGJChBmgBdCD00GEOGCgih0FIA00FIRLhAbbCcaa00aDOGcHCEGga000cFIIEHCGE00A00AADCCBHaBeBgC00heCfb0BAEAa000angdeGBJDb00");
sw(116,"0aaeglgCcabEA00a0gjDCAB00d0000bfAbeegfcf0a00AAh0FeacbEd000DBb0DHABBab00bABEAc0ebceb00BDCEBKfaDfgb00DDHFFGBBcf0b00DNULffaCDbAa000NXNbFALGdaB000NSIDHCGIBEC00EEG0Bec0CADeB0AafAaegfEEHCaaAakd0cCAPFAaa");
sw(117,"000abcCDEdic00000bB0fbahaB0000cdAaaddbbc0000BGa0eefgbEF000CHDC0DdaaCd00acAELBJ0EBaf00fenaFCHIBaif00eghbFNJKagbb00eADGDiBCDc0D00aJKEBkeF0BaCaaCGHCbhaaDBAaaaC0EbfifeaABCa00OdBAdbhbbEE000bCeBAaa0aD00");
sw(119,"00aaabAebaC00000aaaeGCE0Bb0000aaaeEGBAbca000ba0cHKD0dcaa000AbAGEG0dcaa00aAc0DEB0ebaa00abbeDEBbeba0000cebDFAeddb000acb0BGBcbba000ac0aADD0aaa000acehbACAdcb00000cgDGCaada000adggFFBbcca00abcebHBCBa0a0");
sw(120,"00ADBBC0FJGDba00ABbEIbFCcaea00ebae0D0cLfbA00aacgIFAIDccB00affBGCcHE0dB0bcicb0cdcAbAB0dcacngacFDdd00becddbDaFeff00cABAdEDFClgl00BCaaEMNGAmfiAA0acGEKLDaljgAAacbeFGGBCghcB0akddjDKGCEabAAa0eihGGHHHICA");
sw(121,"0abholgBEeuoBE0abdaJalcciabE0adbagadglLBIA0a0Bgccf0HKLCE00AkeGC0bQIIfE0gDlDEAeAaLCeE0j0egeHCD0bwp00cthkbINGJheg00jdEIbaiHPddb00eLFc0JFReb0a00DILDgINBFaF000PED0DgifGFbaA0EKidAfcnFCE0AAFGKfcCAELTFBA");
sw(122,"0bbd00CGCdea000b0aE0FGEEDBE000CCH0A0bAcA0000bbbAaaeidBca00aaBdBDAccAba00ACDD0E0C0Bca0BAbDOKDE0a0C00BBaDBDCADADC00CccBCc0eAIFE00bc0eigijEKEDaa00CggglaCJGBaa0BEBfjdcbDDaa0BIDGCbab0AA000BAKMHB0aadfc0");
sw(123,"0ccdBbLJ0caccc0c0bAeGJGP00Dc00GEDDEBCBaKa000fo0GLDEBahee00bg00EAMi0bHe0EBKckbbdhfEDe0PBSCHGdcaANK00KOJGdilhIFMD00NAhiCL0fcRHB000oohmehuGHBa00decjdfpAcDFD00jelDeCGICbBda00aFBAa0FgceB000bJSHBghAfka0");
sw(129,"0aaeglgCcabEA00a0gjDCAB00d0000bfAbeegfcf0a00AAh0FeacbEd000DBb0DHABBab00bABEAc0ebceb00BDCEBKfaDfgb00DDHFFGBBcf0b00DNULffaCDbAa000NXNbFALGdaB000NSIDHCGIBEC00EEG0Bec0CADeB0AafAaegfEEHCaaAakd0cCAPFAaa");
sw(130,"0aaeglgCcabEA00a0gjDCAB00d0000bfAbeegfcf0a00AAh0FeacbEd000DBb0DHABBab00bABEAc0ebceb00BDCEBKfaDfgb00DDHFFGBBcf0b00DNULffaCDbAa000NXNbFALGdaB000NSIDHCGIBEC00EEG0Bec0CADeB0AafAaegfEEHCaaAakd0cCAPFAaa");
sw(131,"000acceccB0c00000afacdeeaAa0000bgbebe0Ca0000bcb0CcAFC0b000bidadEcFDAb00abeCaaBBDBbc00bbEAfBdcEabe00adEGFCaADB0ba0cDIJaABDFdaba00DGBDIFDBea00A0GCFGGKEGADB0ACB0d00EACbBBC00cilhcabCBaa000aglhe0dDEB00");
sw(132,"000acceccB0c00000afacdeeaAa0000bgbebe0Ca0000bcb0CcAFC0b000bidadEcFDAb00abeCaaBBDBbc00bbEAfBdcEabe00adEGFCaADB0ba0cDIJaABDFdaba00DGBDIFDBea00A0GCFGGKEGADB0ACB0d00EACbBBC00cilhcabCBaa000aglhe0dDEB00");
sw(133,"00ADBBC0FJGDba00ABbEIbFCcaea00ebae0D0cLfbA00aacgIFAIDccB00affBGCcHE0dB0bcicb0cdcAbAB0dcacngacFDdd00becddbDaFeff00cABAdEDFClgl00BCaaEMNGAmfiAA0acGEKLDaljgAAacbeFGGBCghcB0akddjDKGCEabAAa0eihGGHHHICA");
sw(134,"00ADBBC0FJGDba00ABbEIbFCcaea00ebae0D0cLfbA00aacgIFAIDccB00affBGCcHE0dB0bcicb0cdcAbAB0dcacngacFDdd00becddbDaFeff00cABAdEDFClgl00BCaaEMNGAmfiAA0acGEKLDaljgAAacbeFGGBCghcB0akddjDKGCEabAAa0eihGGHHHICA");
sw(135,"0ccfgccb0Aeecc0c00ADDaCE0jcc00CCjCiCACFae000AC0jAaCLDBb000dgdghABCFH000BddJbedagCbB00adIFAElc0CBa00cdCWTGhCJCEbc0fEbLHMMPBdCdc0ACekaRGbBcBbaBbFdaHKHFIIFCaBaBBjddDJB0ABD00iAwjbcCGaee000c0ekjd0DBB00");
sw(136,"0defeeDDbeg0ba0dbb0AFDABCABa0aAAB0bbeA00b00acfa0CefhaBdb000dABA0aaaAcb00abHFADACCAbb0AaCENOcAD0aa00AAGJHEbCGCG000ABFKAbfcEIGD000CE0eChfFGID00BFJBCBhAENMD00CDF0djeBAHJBA0BFaabgdBCFBA00B0FFAcAAEbaa0");
sw(137,"0defadAIAcc0a00dbeeAG0EDEGC00acdadbbkgabE00aimdALBilcCja00aqcBGbcBbcda0ebgGCBCFFaeha00bCCGSAKGgmh00EaHAeBAB0Bbe00EEOHiomkDLDC000IWMgbeCEAFC00ALRKDHbBCIJD00DBE0fd0ACCKaA0CMiB0fddFHCG00CC0BECCFKEE00");
sw(143,"0aaeglgCcabEA00a0gjDCAB00d0000bfAbeegfcf0a00AAh0FeacbEd000DBb0DHABBab00bABEAc0ebceb00BDCEBKfaDfgb00DDHFFGBBcf0b00DNULffaCDbAa000NXNbFALGdaB000NSIDHCGIBEC00EEG0Bec0CADeB0AafAaegfEEHCaaAakd0cCAPFAaa");
sw(144,"0aaeglgCcabEA00a0gjDCAB00d0000bfAbeegfcf0a00AAh0FeacbEd000DBb0DHABBab00bABEAc0ebceb00BDCEBKfaDfgb00DDHFFGBBcf0b00DNULffaCDbAa000NXNbFALGdaB000NSIDHCGIBEC00EEG0Bec0CADeB0AafAaegfEEHCaaAakd0cCAPFAaa");
sw(145,"000acceccB0c00000afacdeeaAa0000bgbebe0Ca0000bcb0CcAFC0b000bidadEcFDAb00abeCaaBBDBbc00bbEAfBdcEabe00adEGFCaADB0ba0cDIJaABDFdaba00DGBDIFDBea00A0GCFGGKEGADB0ACB0d00EACbBBC00cilhcabCBaa000aglhe0dDEB00");
sw(146,"0dbjijdcbCggdc0dBhdDcieagiec00bceAgfbcKh0A00DCAeJg0IEEbF00cfa0CAbDGCcF0bBmE0BeacEbCF0fBBclg0dHEdb00dgAacadeFbaAb0fAEEhBBJAnghb0BD0aCLLHdnggaA0DaNJMME0gf0aABccdLcaADbcAD0AdfcgcCBGFIbAACDAhjcIFJQODA");
sw(147,"00ADBBC0FJGDba00ABbEIbFCcaea00ebae0D0cLfbA00aacgIFAIDccB00affBGCcHE0dB0bcicb0cdcAbAB0dcacngacFDdd00becddbDaFeff00cABAdEDFClgl00BCaaEMNGAmfiAA0acGEKLDaljgAAacbeFGGBCghcB0akddjDKGCEabAAa0eihGGHHHICA");
sw(148,"0AAF0J0bBLIGbb0A0FcaKBHDDhbb000D0DDNCDKdm0000CBlGOCF0icc00BdmjdH0I0Cec0Ab0BfeBchbBCc0bbICibjhdAK000caCMRFBCFdA0a0fadIOQRMDfCga0a0kmDWEiGdCfa0bbngBDHHJEDda0d0FjfaDIBdiaC0cq0toBFGCcmj00dfmcnDgEBCha0");
sw(149,"0ccfgccb0Aeecc0c00ADDaCE0jcc00CCjCiCACFae000AC0jAaCLDBb000dgdghABCFH000BddJbedagCbB00adIFAElc0CBa00cdCWTGhCJCEbc0fEbLHMMPBdCdc0ACekaRGbBcBbaBbFdaHKHFIIFCaBaBBjddDJB0ABD00iAwjbcCGaee000c0ekjd0DBB00");
sw(150,"0defadAIAcc0a00dbeeAG0EDEGC00acdadbbkgabE00aimdALBilcCja00aqcBGbcBbcda0ebgGCBCFFaeha00bCCGSAKGgmh00EaHAeBAB0Bbe00EEOHiomkDLDC000IWMgbeCEAFC00ALRKDHbBCIJD00DBE0fd0ACCKaA0CMiB0fddFHCG00CC0BECCFKEE00");
sw(151,"0defadAIAcc0a00dbeeAG0EDEGC00acdadbbkgabE00aimdALBilcCja00aqcBGbcBbcda0ebgGCBCFFaeha00bCCGSAKGgmh00EaHAeBAB0Bbe00EEOHiomkDLDC000IWMgbeCEAFC00ALRKDHbBCIJD00DBE0fd0ACCKaA0CMiB0fddFHCG00CC0BECCFKEE00");
sw(157,"0accACLJFBbcAA0acaFbDcbe0JCA0ad0CAEBA0cBD00agaecfagfdbA000bccCBDcCabe00ddf0KEJFEF0i00eepcFJDFCclh00acog0LJHAccf000dgbalfaIE0B00AF0heiidaHDA00DEGffefc0HIb00CCDcfghdBCCCa0ANFDffheBaD000aAIFB0dabAcb0");
sw(158,"0bbb0cEFFcfc0A0baacaECBBAEEA0aAeC0ABeac0C00affcFAbfha0ba00baGACB0ccdba0baACFCGDHAAfa00a0BIGFE0ada00B0B0kAEacAa000BdFAfndiBFCE00baJEkmgdBHEB00A0JDeegdcGH000abFHdhccbBEaa0BMbNFgbeaFBC00BCELEABAEabb0");
sw(159,"0aA00fe0abcBbB0aBbcAabeFeeAB000cGbeeAjFdDC00A0eEKbaBAB0C00BGC0He0hafAC00GCDdbhhjadEC0DKJHEghdIJDE00DAO0mkijDEaEA0aAMAk0kebbgeA0daKMde0EbfhhA0dcLMIKabckieA0eheDWIbadgeeC0C00QHDECfCCGCCFHDGHDJFHGFFC");
sw(160,"0ABEEDCDEFDD0A0AACCEBcBB0D0A00b0BAcdabEC0A000B0d0a00D0AA00aAabAac0DAaA000bcdabbcCA0A000aceecbBE00000aaefbbaA0a0000aadbDbBafbc000acaCECCcfcc000bdBEDDAcefc00aacAHEaabcfaA00cACCDCC00AaAA0ABAADDCABEAA");
sw(161,"0DDJFPJ0DLFJ000D0JBdHEKIFA0000AAC0DJEDEDj000aFDdCMGEcgBf00CGigdHCCeBaf0DbFfifFelgG0f0BbaBA0dhgbNB00bAeFLDABccCB00cak0ONPG0fFC00aerkaJ0jEC0C00aioldjdAIb0A00dbcebAFBacja00dkEiiHFBigjg00fih0eEhdbijc0");
sw(162,"0bcgigde0B0fba0bbdccKEDBAnca0aACcBBHBFGig00aABBkEKCMBeaa00AbfebDBE0Fba0A0BFbeBfdaBCa0c0CIdChieAI000dA0NTIBCCdCbb0edfIJOTMabDgb0bBmmAOGfE0Cdb0aChe0EIDLICdb0aCElhbLMD0hbA00m0[mCEFCdhh00adcegBhEFEaa0");
sw(163,"0bedJaNQmCcibb0bcbGcRfCNkEDb00ab0AGanEHKh000cl0aEhIAE0bf00DihFJKNIQBMf0daaFJECaa0Hhf0H0BClGqnkiEl00LBaCmoccs0Rqe0LBHEgbfcFM0de0eCamhIidKagee0cGaDbBbGGNMJe0CElHmkDcLb0bC00DL0ahcH0Gbn00beELeabBJiuc0");
sw(164,"0bbb0cEFFcfc0A0baacaECBBAEEA0aAeC0ABeac0C00affcFAbfha0ba00baGACB0ccdba0baACFCGDHAAfa00a0BIGFE0ada00B0B0kAEacAa000BdFAfndiBFCE00baJEkmgdBHEB00A0JDeegdcGH000abFHdhccbBEaa0BMbNFgbeaFBC00BCELEABAEabb0");
sw(165,"0cdeacbHFAb00A0cbabbACf0EFBA0aAGEbBBdekCH00acfeBDBgkdgg000ba0CEAbdggn00ab0ACFGALCdl00Baf0JKIWDiha00C0ccdEFBDAdE00D0ecdefjCICC00bACAfide0FFBaa0DKaa0cedHJgaaA0EBecchaELIb0CMCCBdbbDAFH00CCIOFBbbGCC00");
sw(171,"0aaAGDE0eEGF0a0a0BDfBacaCECa00aAaBDBC0faa000cc0ADCbgkdc000dcFDBaChjec000adEIHJCAAbb00aca0CcbCBBBA00aBha0AaCbCDCa0Bdljecabc0BAa0Bfikec0ccABAa0Acdd0acbbAaAa00aAAbccAa00C000FGEcabDbDBc000ADEBAB0a0b00");
sw(172,"0edgbgGIHahfbB0e0cFADddB0ECB0adAD0acadcAHC0aabbLBgciAFAB00c0HDKadhCcbB00abBCFDBHCbcB0B0ebDGGGHDia00Bccir0AgaB0A00B0BbkmqgCAAC00caMNfsd0aE0aaaA0QLbAgbdB0aaa0cHEGbcecBBb00FQBTFccf0GHHCCGGJLICGHEADDC");
sw(173,"0eeicfEGCeifcA0eabGAFCAGaaCA0a0EIHA00A00BC0a0ABG0gigcBA0000EKEDcffBBb00A0AFEc0eB0BA00A0cCKBA0DE0D000AaBda0bGAED00AddAA0d0EBDE00be0begdjaHBBaa0dFbdckh0E00aac0GBCgefbDA000EKJOF000EEDDCCEDMNI0DEBA0CC");
sw(174,"00ACGGKJFDAG0B00ACIAECDHDCDB00AEFBcc00CBCB000BAEadgfbAC0000CG0bbhcB0A0000cA0dafC0B00000c0GAaBEB0D000A0BcdbBGCAD00AabaAbfaDEBE00AcdccfdhaGBB00AdB0BdfdbCBB00dbBDCabfb0BAa0BIIOFDB0DBACBBBDJOHEFBcccBB");
sw(175,"000DGEODJJFG0B000CGbNEGKGBBB000EJ0FGHAD0BB00BFDGCD0caaD000BHGFEbbgcb0000BDAB0Ddad00000BeAHDGECaAB0000feh0Ca0acB000gjeBb0bcDDC00ccldhjekBJB0aaAi0afiifaDccaaffCBaABbACAdd0BGKNCIEDBE0BBBBBHMMNBMEdeBB");
sw(176,"0fgniuACCbBdeb0fbeagKBdICgdb0afADkCAiaKnCA0acldDLFd0aDhF000bEGOABdbfeF0fFbDHICDEcdbF0cHBCEIMEFChc00CBDfqbLecebb00CBG0rpiBbBag000HO0jkEEAbDe00AHUQcPCAcFCd00CDIDECDCbACaA0CDfPoCEbCFGAAACDFaBJLSPHEAA");
sw(177,"0gflglBHBAheca0g0faEAdgBeaba0aebCcagghDfGA0achgENgjeEHgF00ejAHLifcBbgF0dAjFEFfFBDddF0cBCbBGEGGald00AdFhod0eD0Ba00ABKBrlsfDCBe000EQGfdBGacEf00BGUOGQABdEEc00EaFaHddbBDCbA0EIjLchdeFFHEAAGGIEDAIMLLMCA");
sw(178,"0edgbgGIHahfbB0e0cFADddB0ECB0adAD0acadcAHC0aabbLBgciAFAB00c0HDKadhCcbB00abBCFDBHCbcB0B0ebDGGGHDia00Bccir0AgaB0A00B0BbkmqgCAAC00caMNfsd0aE0aaaA0QLbAgbdB0aaa0cHEGbcecBBb00FQBTFccf0GHHCCGGJLICGHEADDC");
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
  const int CYCLES = 20;
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

  //erase_vert_gray_lines(&image);
  insert_empty_columns(&image);
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
    if (image[mid][pos] != 0 && image[mid][pos-1] != 0)
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
  pos = 1;
}


//======================= MAIN =========================
int main()
{
  recognizer rec;
  rec.set_weights();
  //rec.make_weights_file();

  //for (;;)
  {
    rec.read_image();
    rec.print();
  }
}
//======================================================

