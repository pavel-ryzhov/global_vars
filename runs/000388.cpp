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
public:
  perceptron perc;
  image_matrix image;
  image_array samples[DIGITS];
  int pos;

  void cut(image_matrix *matr) const;
  void addlr(image_matrix *matr) const;
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

//  ....
//  ..@.   .@
//  .@@.-> @@
//  ..@.   .@
//  ..@.   .@
//  ....
void recognizer::cut(image_matrix *matr) const
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
void recognizer::addlr(image_matrix *matr) const
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
sw(  2,"00BCCCBBBCBBaa00BCABBBBBBBaa000abbaaaaBaa0000bba000BAa00000bba000B0000000aaaa0AAA0000000aaa0DAa0000000aaaACAa0000000aa0AAa0000000aa0AB00000000aa0B0AA000000aaa0ACBa000000aa0a0BAaaaa000aabb0BBaaaa00");
sw(  3,"000CKJEBBDFJBa000FBBBDCEBHDa00aAcbA0A0bcB000dceADCBBdfA000fdeaaA0Ahfb000dcbDcFHAAac00bdAcAa0DCCBA00bBbabgeDABCCa0A0dgefDaA0DBa0BcgiebCc0CCBa0Bcdd0a00bCC0a0BaacBbAdDABA00aaBACBFADCAc00bcbBCACa0bbb0");
sw(  4,"000CKJEBBDFJBa000FBBBDCEBHDa00aAcbA0A0bcB000dceADCBBdfA000fdeaaA0Ahfb000dcbDcFHAAac00bdAcAa0DCCBA00bBbabgeDABCCa0A0dgefDaA0DBa0BcgiebCc0CCBa0Bcdd0a00bCC0a0BaacBbAdDABA00aaBACBFADCAc00bcbBCACa0bbb0");
sw(  5,"0A0BEKHHEFEGA00A0AADFFEGGFD00AaDbfadaCb0000AdAbcbbac0ba000eacga0aCBAe000bC0DdBECDBf00ccb0DBADEAb000c0faCACDDaA0a00bd0BdEcACHCa00cdfcdafbIGBbaA0bhafcaBIFbbaBBAaficfABaca00ED0DaagE0cd00bbABF0afbgee0");
sw(  6,"00AACBFFEcbB0A00A0CEEEGGDECA000BCaAbBEEBAA00AAAAdaaCACB000aABbAbcCBBB000aB0CcaACCBA00acccBdd0DBaB00aafbadABBb00a00dccaaDBabBBa0cdbdcbAbc0AAbaaaAbBACbcCAbba0BABBbbf00cc00AFFGGAAbCBBAAAACFEFDDEAbBAA");
sw(  7,"00AACBFFEcbB0A00A0CEEEGGDECA000BCaAbBEEBAA00AAAAdaaCACB000aABbAbcCBBB000aB0CcaACCBA00acccBdd0DBaB00aafbadABBb00a00dccaaDBabBBa0cdbdcbAbc0AAbaaaAbBACbcCAbba0BABBbbf00cc00AFFGGAAbCBBAAAACFEFDDEAbBAA");
sw(  8,"00ABDAGEIcAB0A00ABBBKEGCDEBA0000DcFbDCGAAA00a0AAcaDADDA000a0BbCccaDBB000bB0A0AaACA000cdebBCBbBBcA00cahhdEFCAcabb0behd0EECbCDab0efcdcaaddCCacaba0caBCbfFBeca0ACBaBacaCbf00AFGGFGCaADAaAAABDDFLEGAc0AA");
sw(  9,"000AADCECMED000000bACE0GBBA000a0b0a0aAi00000cAdcCaaaaga000cabAB0ACach000aACEB0FEbch00aACDECAMKA0f00aBCCEa0FGDCa00aBCBAdb0DCFA000DAaaaaA0EF000AECaB00BEGGa000AAAbcabABCC000aB0Aa00Edab00abbADaAeCbbc0");
sw( 10,"00ABJDCaaMII0a00ADC0AFeEBECa00aaCADD0ajc0000bbdDFCccgrb000cbbA00aBijg000ab0BAEEAbcf00CBAbD00KFCHc00CGBcfheBBBAFA0FEahfeAae0EDA0B0efdbBea0DB0aCaAADCBbcCE00aAb0CFABeA0HFa0abEEEBFCCaAb00bAbFC0BhDada0");
sw( 11,"00ABJDCaaMII0a00ADC0AFeEBECa00aaCADD0ajc0000bbdDFCccgrb000cbbA00aBijg000ab0BAEEAbcf00CBAbD00KFCHc00CGBcfheBBBAFA0FEahfeAae0EDA0B0efdbBea0DB0aCaAADCBbcCE00aAb0CFABeA0HFa0abEEEBFCCaAb00bAbFC0BhDada0");
sw( 16,"00BCCCBBBCBBaa00BCABBBBBBBaa000abbaaaaBaa0000bba000BAa00000bba000B0000000aaaa0AAA0000000aaa0DAa0000000aaaACAa0000000aa0AAa0000000aa0AB00000000aa0B0AA000000aaa0ACBa000000aa0a0BAaaaa000aabb0BBaaaa00");
sw( 17,"000CKJEBBDFJBa000FBBBDCEBHDa00aAcbA0A0bcB000dceADCBBdfA000fdeaaA0Ahfb000dcbDcFHAAac00bdAcAa0DCCBA00bBbabgeDABCCa0A0dgefDaA0DBa0BcgiebCc0CCBa0Bcdd0a00bCC0a0BaacBbAdDABA00aaBACBFADCAc00bcbBCACa0bbb0");
sw( 18,"00AACDDED00CAA00ABBDDDDCBECA000AA0BaCECABA00b00AcaADCAC000dAAaabcCDBb000dAaBeaADEBc00decb0dbBFC0b00dbecabBDCABba0ceddbaCBBAC0a0bedebbAabBCabaadbc0aBabCCcba0a0A0bbdAAb000AEDDFBBaDBAAAAABECECCBAaBAA");
sw( 19,"00AACBFFEcbB0A00A0CEEEGGDECA000BCaAbBEEBAA00AAAAdaaCACB000aABbAbcCBBB000aB0CcaACCBA00acccBdd0DBaB00aafbadABBb00a00dccaaDBabBBa0cdbdcbAbc0AAbaaaAbBACbcCAbba0BABBbbf00cc00AFFGGAAbCBBAAAACFEFDDEAbBAA");
sw( 20,"00ABDAGEIcAB0A00ABBBKEGCDEBA0000DcFbDCGAAA00a0AAcaDADDA000a0BbCccaDBB000bB0A0AaACA000cdebBCBbBBcA00cahhdEFCAcabb0behd0EECbCDab0efcdcaaddCCacaba0caBCbfFBeca0ACBaBacaCbf00AFGGFGCaADAaAAABDDFLEGAc0AA");
sw( 21,"000ACADCGACA0A000AC0JECBBBBA000BEAGBBA0aAA000CBAABBcaaA0000DAcB00ca000000BbbAD00a00000AcbACCBADBA000CcdeACabABA00Aaed0DBaeCEB00cbccc0accAB0bbaAaBBEBaaECcbbaAACBEBaABAba0ADFEEIEDBBAAAAABCFEIDECaaAA");
sw( 22,"00AAAAFCEAAA0000AABCHEECBA00000ABAEBBACA0000AAAACBBBBA0000AAA0CBBABAA000AAA0CBBABAA00AAAA0CBCAAAA00AAAA0CBCAAAA00AAAA0CBC0AAA000AAA0CCC0AAA000AAA0CCC0AAA000AAAADCBAAA00000ABAEDCABA000000ABHEDDA000");
sw( 23,"000000DDBA000A000b0BBBCDAAAA000ACCa0ADDBAA00ABBBA0ADBBA000ABCBAA0BCBA000AACB0aACBAA00AACBA0aBDBAA00AACCBa0ACCBA00AADC00aBCAAA000BBBBAABABBA00ABCDCABABCCA000BBBC000BAAAA0AABCCABCDDBAAAAAABCABDECBAA");
sw( 24,"0A0BEKHHEFEGA00A0AADFFEGGFD00AaDbfadaCb0000AdAbcbbac0ba000eacga0aCBAe000bC0DdBECDBf00ccb0DBADEAb000c0faCACDDaA0a00bd0BdEcACHCa00cdfcdafbIGBbaA0bhafcaBIFbbaBBAaficfABaca00ED0DaagE0cd00bbABF0afbgee0");
sw( 25,"000CKJEBBDFJBa000FBBBDCEBHDa00aAcbA0A0bcB000dceADCBBdfA000fdeaaA0Ahfb000dcbDcFHAAac00bdAcAa0DCCBA00bBbabgeDABCCa0A0dgefDaA0DBa0BcgiebCc0CCBa0Bcdd0a00bCC0a0BaacBbAdDABA00aaBACBFADCAc00bcbBCACa0bbb0");
sw( 31,"0abaACABAcAC0A0ab0B0DDDDECCA0abCadAcDFcbA00ad0bbb0Ce0b0000c0bdCAAABbc0000E0E0CCEAAd00cbbBHEB0FBcA00c0f0CDBCD0B0a0add0DbCaADHCa0bdbecffcbIFAba0BAhdgc0CKFcbaBDBBijeaBDbea0AEEBDdddF0cc0000DCDac00ged0");
sw( 32,"0bcdabDEEfeb0C0bccECCEEDC0CC0bbEFaCcCEDDCA0bADCAeaBbAFD000aFFbBacaCBD000aFBDc0aBBDB00bceaCacfACdD00b0hbaBBa0caAb00fdc0AF0aaBCb0efaceebbeAA0dbbACccaDabFBcdbBDBAdhca0Acea0CGDEFbaaEDBAAACEIEGC0ICaBAA");
sw( 33,"0cbaGAa0dhaDaC0cb0Fc000BFGCC0cbBD0BfFcD0DB0cacaEeaFAeDD000abGDaAbdcbD000dcCPcIaBBbA00ciccAacfEGjD00cAigBaaCbbb0c00bcbahaAa0Bbc0ccFBcjgbfADAdaaHICCdCdhDCbdaCDAdCheB0B0AA0CJGIFb0e0GHBBBD0HEGDcJCFCCB");
sw( 34,"0aaaaddbDGD0a00aa0bhGBffdca00aacA0JIBekc000abAccGDCfekb0000AcaBACfeeh000AAbcDBbeech00AE0CBEGFaCHg00AFDbcED0dAAA00AFacaCaAfDDa000EAa0A0bbAD0000DAacCa0a0D0000Ab0aFaCcaEF000cC0aGBEbfBb000abCAG0dCBba0");
sw( 35,"0bbbefda0EDcc00bbcgeGCb0bdd00bbgdAEEBadda00bccgfECC0bfb000aaeaDGCbddc0000babGEAcfcc000DBD0GCCCC0d000AFDaD0bbGCc00bDDC0Aa0bCCc000FBBADCCAABbAAaDAA0CBCE0BaAAaabb0HFGC0D0A00fcghBBEA0aa000bdceBA0FC0a0");
sw( 36,"0bbbeiBA0bcdcA0bbcdbEa0adbeA0bbgbBECCBDa0A0bbd0dA0CDD0B000a0AEBCAaDAA000deacDbcAa0000cdadgBaABBce00cgaadAa0AAcga0ebAbdDbGBafga00AABBFEHAcde0Aab0BaHFDBdcc0Aacab0ICJB0aBB0AcfchB0ICAaCAAAACcfHDKIEGDA");
sw( 37,"0caclhAGGhhidC0cagdDEBIEAcdC0ca0acffBCKC0A0cCC0ehhDGFO0000EBD00B0DLEG000CED0aeaBACD00a0ACdeffCaiB00ag0CBDGAACCfc0cdEIBEADD0edc0eCFDBBBHbadbc0bHE0B0EFEAb0c00D0add0FcaefA0CFaacehfcEDBAAEDHcCA0HDFFCA");
sw( 38,"0ABCABDGGaa0aA0AB0DCCEFCBA0A0AAAAcada0FAaA0ABB00fcaBDC0000AABcAaaDGEA0000C0cefdBDBA0000cAafb0CAbA000bdcA0EAAaab000bbAADCC000a00baAA0ba0AaaaaaaABbA0a0a00baaa0A0AAadeabb00ADDDFBad0BCBAAAACBGDAAABBAA");
sw( 39,"0000deBGDc0a0B000bbADCDAAa0B0000baAdacf00000000aeead0Ba000c0Bb0CaBF0d000cD00bBbDdad00aefEAaFBEbic00acgcCFJBacbe00aaAABbadbAA000bCFCafhBdBaBaaaHEaAbabCCAAaaAEBDcfd0c0b0a0BIECEadhAcAC00BBGCGEAAC00a0");
sw( 45,"0bcaDDb0abdAaB0bcAHaAE00DGCB0bbECaCbIAabCB0bbC0Ae0DAe0F000aCFCB0bccDa000cACLdE0BEBb00debcDAfAFK0b00dbicEAcCC0Cba0cfgcA0CDAACda0cebcaddaAABdbaa0Ba0babcB0gba0aAdafcB00cCA0BDFDEaaaCAEDBBB0FFEAeCaDECB");
sw( 46,"0ccbGCABAifAcC0ccaJaCECDFGCC0ccDFaAgF0HaCC0cABDDf0HDfDF000CDJ00AbgcCG0000ADOdGccEBB00deadAbjgCLeF00dAicDbdB0c0Ae00deA0cFHaaCee0efC0bg0bcACdgbcFF0AfE0gDAggbBDchAhdBb0fbA0CHFGEbac0DF0CCCbGFIEeJaEDCC");
sw( 47,"0bbbF0Ab0aDCa00bb0D0BECEDAB00bb0E0BCbbbbA00babaCFDbehec0000aBBBBadjjC000B0DFFIDadcC00ECC0EBA0BDAF00EFB0eefb0CAG00GE0ffdAcg0DD00AAbffaAfcABD00BBBa0B0bdB0C00BAaACbAcA0Eb000cBEBaDC0ECc000A0E00CDCBca0");
sw( 48,"0aaadcbacIDbc00aacda0AeBbed00aaddA0Aabfdb00a0bebDa0Adgb0000bbBBFBBcdb0000c0bE0Baecb00ADDCaDbFFBac00A0GFB0b0BGBb000DGF00bAAAab00AFBDBDCECaab000DACDCDFG0B000abbbAEFFB0FB000ddggcbBB0a0000accddbbFD000");
sw( 49,"0aaaccAaAaaca00aa0eaEAAbccb00aaeebEDCabd000acecdEEECacb000cdbaEGDA0db000bc00FCDAadc00abAabE0Aaadc00abAB0DaAaaeca0bABCAD0BAadba00CCBBFDDAAaba0aAABBGEFEA00a0aaabbFDGB00a000defgBaCA0cb000bcffEADCAaa0");
sw( 50,"0aaaccAaAaaca00aa0eaEAAbccb00aaeebEDCabd000acecdEEECacb000cdbaEGDA0db000bc00FCDAadc00abAabE0Aaadc00abAB0DaAaaeca0bABCAD0BAadba00CCBBFDDAAaba0aAABBGEFEA00a0aaabbFDGB00a000defgBaCA0cb000bcffEADCAaa0");
sw( 51,"0ACEB0DDacBAb00ACadBbaFE0Ac00ABeeaeecaO0bA0ABbeb0cBIBIc000aebABGBFBBH000aeAb0bCA0aG00AaCaifffD0kF00AeDDBecaCCada00BGGaBAGFfhea0AEDCBEHGDfeb0AACBEJFEFBebA0AaaacHGEAbdBgB00bccecbbbICAAAAbaeaaAGEFFBA");
sw( 52,"0ABCABDGGaa0aA0AB0DCCEFCBA0A0AAAAcada0FAaA0ABB00fcaBDC0000AABcAaaDGEA0000C0cefdBDBA0000cAafb0CAbA000bdcA0EAAaab000bbAADCC000a00baAA0ba0AaaaaaaABbA0a0a00baaa0A0AAadeabb00ADDDFBad0BCBAAAACBGDAAABBAA");
sw( 53,"0aaagAAGDccbaB0aac0AEEC00caB0aaDbcafBBcb000aaCAdgeBcDBA0000B0daaABJEd000BGa0ecbCBDe00d0bDCAB0CAeb00dbdBFIICBbBda0dd0FHABaBDE0a0c0BABdeBcGCbbabEAgeiaBFGBcbaAE00kieCaBgca0BEAbBdhhCdd000BaD0GCcaadbc0");
sw( 59,"0ccbGCABAifAcC0ccaJaCECDFGCC0ccDFaAgF0HaCC0cABDDf0HDfDF000CDJ00AbgcCG0000ADOdGccEBB00deadAbjgCLeF00dAicDbdB0c0Ae00deA0cFHaaCee0efC0bg0bcACdgbcFF0AfE0gDAggbBDchAhdBb0fbA0CHFGEbac0DF0CCCbGFIEeJaEDCC");
sw( 60,"0cccB0ba0bbAbC0ccbFcAEADADCC0ccCEAA0EabcCB0caBACaACAgdC000DEFBBAacdaB000CDCI0Ga0AAB00ABAbDAeaCICD00ACbaabb00AED00Cbb000BBc0Cb00bdA0bbabb0AbaaADFBA0AcdD0eaaBBa0EaA0b0cAA0CBCGGCDAAAEBBBCACEGCbCAEBBB");
sw( 61,"0bbbD0abbCDCa00bb0BbBDbCBCB00bb0DBBBBBecA00bb00BDB0cfg0000aBAB0A0bgfa000A0ADCHDAbAa00ABAaCB0CDGEA00ADB0edd0BDFD00CBafddAadBEA00AadfdaAcbAC000B0aa000bbBBa00B0bCCb00CACA000aBCC0CDB0Aa000BCEA0AaB0a00");
sw( 62,"0000cca0aA0aa0000ae0a000bab0000de0aAA0aba000adbaAABD0ab000bd0BBECCBaa000bcBAC0DB0bb00abCAbAbBBadc00adCDC0aBBAbda0bAEFAA0CCadca0ACDDCDDFB0ab0A0ABBBBDFCaa00A0baaa0CEA000A00beefdbAAAba000abffc0ABAA00");
sw( 63,"0aaaccAaAaaca00aa0eaEAAbccb00aaeebEDCabd000acecdEEECacb000cdbaEGDA0db000bc00FCDAadc00abAabE0Aaadc00abAB0DaAaaeca0bABCAD0BAadba00CCBBFDDAAaba0aAABBGEFEA00a0aaabbFDGB00a000defgBaCA0cb000bcffEADCAaa0");
sw( 64,"0aaaccAaAaaca00aa0eaEAAbccb00aaeebEDCabd000acecdEEECacb000cdbaEGDA0db000bc00FCDAadc00abAabE0Aaadc00abAB0DaAaaeca0bABCAD0BAadba00CCBBFDDAAaba0aAABBGEFEA00a0aaabbFDGB00a000defgBaCA0cb000bcffEADCAaa0");
sw( 65,"0ACEBaCBAGBAa00ACAcCcabCACb00ABeebaab0HCaA0ABbdcAcaEGD0000cfaCABACCC0000ehAbbeBABab00bdDcifdEE0ef00beEB0ebADBdgb0dAGBdB0FFeheb0aEBCDEIEAgddaAa0AGJIGFagdaaAbdadFFDBadABB00acdfbaaaABBAAAAAedb0ACEIDA");
sw( 66,"0ABCABDGGaa0aA0AB0DCCEFCBA0A0AAAAcada0FAaA0ABB00fcaBDC0000AABcAaaDGEA0000C0cefdBDBA0000cAafb0CAbA000bdcA0EAAaab000bbAADCC000a00baAA0ba0AaaaaaaABbA0a0a00baaa0A0AAadeabb00ADDDFBad0BCBAAAACBGDAAABBAA");
sw( 67,"000bgaAGEgefaB000faAFDGBBeaB000BabaeaAAAa000BBBagdC0AGb000CBAgAC00HDA000EI0cbcfabB0000BfEB0BebdfC000ceBGJKAbe0ba00d0JHCCbaBAaa0daGEAefaaEAacbcFEcbgbADGDbcb0FABgfdadAehb0BFBAE0fiadba00BaCbHFa0bcdc0");
sw( 73,"0bbbCCaaD0BAa00bbaCaCFBCCBC00bbCDa0CACadA00baBAADDAceca000BC0bA0AefbC000FCACAFCbBEC00CHDaEAcb0JJG00CHEEeefbBCIH00ECaba0D0dCGC000afhdADgaDD000B0ddbbb0bEAb00BAdA0bAbCA0e000e0BB0BBA0Ad0000aCAa00cacb0");
sw( 74,"0bcaDC0BCc0Ba00bc0DbFIEEDED00bcDBAA0DbefA00bbCABBBAchf0000CDCaBCAehc0000DEDK0JAbBa000BDCBHFaAAICD00BE0BDAeBAaEE00DAbCBcC0cCE000a0AacdcfaECAaaAFE0adfcaGBbaaACa0AhdcaAbaa000FGEaad00Db00acaGGBcaaCdc0");
sw( 75,"0ccbCAabda0FAB0ccBCbaCaFEFBB0ccBdaAdBcd0D00cedfBBAFB0bA000dbBFDFDAahd000fbDPBJGFCgh00ejCAaCdBGBme00edcAHAiGBCbdd0cbAE0eCBGaabd0a0IDcb0GcBC0d0aJKBAAEFaDA0d0DA0femaGABaE00BEbAfibe0EDb00BdDbAbcBGF0a0");
sw( 76,"0bb0DAAbdEDEA00bbDaA0CaFDEB00bbacA00AE0aC00bddeaECCDBdB000fbbDCCBBdgb000fcCHEEKFBde00deHB0CfDHDde00dbDE0enBEHAbc0daCbgdAAD0A0c000bdcDEDaBCabAabaa0ADGAAAAbAAdbcdgAEFABCA00ccehibCDFbc0000acghcAGA000");
sw( 77,"0bbbB0AcAcAD000bbC0cIBB0ADB00bb0abIDECabB00beaccGEEacbA000eAccDBBcdea000dabCFGE0Aac00ddad0F0aBD0000d0dceBdBaBC0b0bbfge0BAbAD0b00dehgBBacBD0b00bcffCABaBDab0BacbeAaBBAAa000A00dCACAC0c0000CBbEADCaaa0");
sw( 78,"0cedBbCd0ADFA00ceDdcHCBBAEB00cddcaIFFE0cD00cjfgfKGIC0eA000jbdbDFDbejd000ie0DGKJCBeh00giCdcI0ADEde00gba0dCiCAFAcd0eadegaB0CBCcd0AbcffEEAaEEbcA0aabdFCECDDacACbbcdAAHFCCAA00dgfkAAGEGcf00acaddCaGGBab0");
sw( 79,"000BC0GE0CBDAA000BbFA0AFBFBA000bbabdABABBA00ddea0caACB0000gf0FCBaEBcc000ihAI0AHIAed00cjadc00GLcle00ceddAeaGFAdfa0cbAcecbBHcd0a0aA0cbBADda0Ba0ABCCHIFBaBA0a00bCaAeaaAaABA0AFCDaeacCFDBAAABFB0bCFICDBA");
sw( 80,"0ABCABDGGaa0aA0AB0DCCEFCBA0A0AAAAcada0FAaA0ABB00fcaBDC0000AABcAaaDGEA0000C0cefdBDBA0000cAafb0CAbA000bdcA0EAAaab000bbAADCC000a00baAA0ba0AaaaaaaABbA0a0a00baaa0A0AAadeabb00ADDDFBad0BCBAAAACBGDAAABBAA");
sw( 81,"000bdaBBFidfb0000dcEECICAeb0000a0AcbcHJBb000AAEbcaabEId000ABbhAaadFCG000FGBf0dccbFG00CFaBBbBibeaJ00CAAEaBEdaaBC00CaACBDAeaCCC00bbcdab0fAF0aaaacbdcdcBCFAbaaaadBebAc0Adoa00debC0bdABdd000abe0a0Bcfcc0");
sw( 87,"0bbbCCaaD0BAa00bbaCaCFBCCBC00bbCDa0CACadA00baBAADDAceca000BC0bA0AefbC000FCACAFCbBEC00CHDaEAcb0JJG00CHEEeefbBCIH00ECaba0D0dCGC000afhdADgaDD000B0ddbbb0bEAb00BAdA0bAbCA0e000e0BB0BBA0Ad0000aCAa00cacb0");
sw( 88,"0bbbCCaaD0BAa00bbaCaCFBCCBC00bbCDa0CACadA00baBAADDAceca000BC0bA0AefbC000FCACAFCbBEC00CHDaEAcb0JJG00CHEEeefbBCIH00ECaba0D0dCGC000afhdADgaDD000B0ddbbb0bEAb00BAdA0bAbCA0e000e0BB0BBA0Ad0000aCAa00cacb0");
sw( 89,"0bcb0CadbFBBa00bcaA0AD0FAA000bbBcBADADddA00bcAcaGCA0dga0000BcABEBchdb000BAABDDEbb0b00AEHaCCdEDFGa00A0GKAekbDIIB00A0CCcABAC0Ca00A0debFG0CBBb00Abb0AC0EDCBa000bbba0CBE0DA000hdcfdaEDB0b000bd0cfcaEC0a0");
sw( 90,"0bcaaBcacDBCaA0bc00bAEaC0A0A0bbBbCBAD0heA00bdCcaCaBaeh0000cC0DADC0dcf000aCEIBEEAabf00bAFDDEbEHI0d00b0CFGBfBDFFb00bACECdaACCDc00ADBA0abBCDDc00AEE00bcCGDEb00A00abebEBACC00AcAabfeaD00000Ac0DDbebFD0b0");
sw( 91,"0cefeaCBHIAaaB0cedaaNHdB0cAB0cdAEaJEDBoaB00cgC0cABAibmb000bFAaBb0d0em000AHBCDB00bam00aCeAJJFICCHi00aCecbHD00ABA000bicCCBcdGJC00ccdggbcfeHG0bbaBAhiBbbCLHdbbABBBhcc0AECCb0B0BDBD0DEead00AACGEJCcGbed0");
sw( 92,"00baaAEEFMGC0000b0bAKEaFE00000bbbbEDBChA0000ebefFBDdAib000daebEECa0ck000aAABFEECcck00aA0BBJGMGaBh00aAAABGDCBCAa00aAABBA0bADGB000CabaBaabHGB00ACAcaBaBFIHa000ABAeB0ABBCC000b0bcC0BEfcd00bdcaAFCdGbee0");
sw( 93,"000ABAD0CJEDaA000bbDaAaIBEAA000aaEcF0JAAAB00aBB0EB0CAdb000a0bE0Aa00da000BaBdBcDEb0a00CEGfAdeHKCIa00CaGFfmhdIHFC00C0BcfDbBEaaA00A0kkaFJaC0bb00DfgAFIDECDBb00aeaCCFEcB0F0B0AgdAaaAGGCBbBBABa0dgBAGDEBB");
sw( 94,"0cbcDCbeAabbcC0cbbFA0B0DABCC0cbAG0ACADCcCC0caACCAB00gcA000CCECAbehfaE000DBEHCBbd0CE00CFEdEbgbELLF00CEBBgjfdCFGF00D0cedAaCdBDb00beghbACiAAAdaa0ebaAAaaeBafaa0bb0FEDcA0AcB0CdCGGDFFBBC0CCDDBGA00E0CCDC");
sw( 95,"0000aCCCEdcca0000bADDCCBBca0000BBacccBF0a000BBC0a0AABDb000CBadA00eBEC000FFBb0bcgBFB00BFDDB0bfdBDE00BBCGBBbdb0CCa0BABEBBC0bADAa0aAab00BdADA0a0aAbedebCAB00a00Bcddb0aAadf000dbbaabdbaad000dcaBAa0cabc0");
sw(101,"0000abaACAC0a0000aaaBAAAaba0000aCBaAdc0aa000ABaABabbdac000BB00a0acdcB000CAAaB0beebB00CFCDA0Bb0AAC00CEFBabAccCDB00CFCB0abbdAC0000EBA000caaBA000EBAA0aa0aCA000B0ACC0cbbDc000bCBACB0cBBb000abDDAA0BBba0");
sw(102,"0aabfcabE0bfc00aaecCDFFFAdc00aabb0dBcCEab00aABdcCdbD0af000E0cc0BAbbaC000HACeBc0fb0C00FKGBabga0BFC00FBJLAdieCIGB00DEFKAEADC00b00aGaa0FHAFAbc000D0BCBaFGCaa00b0abADD0BaCg000kfchcbC0Cad000chccc0bAD0b0");
sw(103,"0aabg0cCBK0dbA0aadbbBFeAdfcA0aaaaaaa0bjca00abDce0cA0aib000AC0ABCBABBk000CDDB0cabaak00aFCFACbICDCk00aaGGIGABCCCe00cBEKHB0CCCBe00aGGFEB0DBBDe00aGGB0aaDGBCc00aBAacbaDba0E00Ad0ddce0Aga000Acb0DBbhDC0b0");
sw(104,"0aaaeAbCBIbcbA0aacAaCFg0cdbA0aaBBA0cCbkca00a0GAbcfaabjA000BFB0abaaAEk000DGCBdcfd0Cj00aFaDDCaHBFHi00aAACHIC0AaEbA0baAGH0a00CDdA0bCBDCdeaBBBe0aaEE0ceebFCCe0aaB0aabe0bacFa0AbB0C0feAl0B00Ac0EJFdk0CAb0");
sw(105,"0bbejeaEHFbgcA0bbfedMGacegcA0bbcBbFCCaiba00beD0ib0BeAfc000AF0f0ABbFCk000BG0eA0ebaBj00aDgCCDGGBBEi00a0cc0KKB0ACdA0b0fADE0BbGGdA0bBBacabAaDCc0aaFBdfAcaFEDc0aaCaBdBaDdB0Ca0A000aEbCag0000A0BCEJBdCAab0");
sw(106,"000AicBFIKDbb0000ahBLG00bcd000aegcDDC0gbb000dBdiAdB0Egc000aAecBBDBHCm000BGAh0dA0a0l00aEBG0FELE0Cl00abFEEMICBCCfA0dADIFHaAAFDbA0aHBBDD0C0FCbA00EAa0BcDJFEbA0cAaBdE0DbA0C000dbgeDfbBhca00addeAG0iDAad0");
sw(107,"00AAABCDAICB0A00Aa0A0AaCACAA0000AAa0BC0BAA00aBa0BcACC0B000a0BE0a0DDBc000bbBBacBFCAc00baA000aIKCAd00baB0BaAFIEDb00baB0b0bFGBAb000AbaAABEBABb00BA0BCBCCCCDb000aA0A00AAABDA0ABAAA0ACD0BBAAABCBBaA0CCDBA");
sw(108,"0bbdacacF0acbB0bbcCBACCE0aCB0baBGa0F0IDaBB0bACEABCbbb0a000CCDbacdeacF000ECAcBaa00DF00EHEdEdbaFHMG00EGDClkaeEHHH00FBbggCbacCDC00bdjjcBEi0Baaaa0fgb0C00bCbbaa0abFEEDdAACeA0Bd0GGDEGDDBbBBCGCF0cBEBBBCB");
sw(109,"0aaaBAB0G0CAa00aaaaBFGEFCAC00aaAACACbGab000a0ADDEEaebcd0000BacAAAeceC000FEBaCCCabDC00EIDBH0BACDIH00EHFFggccBCHI00GDAcd0BddDGF000ahje0DiaFCAaaAcfebbcB0GD0aaAadEacAeCBCha00e0DF0BACBaf000BbC0bBaAcec0");
sw(115,"000aeea0BCCcb0000de0AACF0ec0000dc0dAebAab000BbhcDbaDdae000BddaBFAAdeC000CdAcEaAcffC00EGECd0dABaaB00EAIGAdecaHC000CGHI0ada0aca00AIDEADBCDbbAAA0FCDCBaEFb0CAAa0AaCFE00bFcA00fcchb0BaDAb000bfcccCAFFaa0");
sw(116,"000adebAAaAcaA000cc0CDCB0caA000c0A0Abc00a00000daBcb0a0e0000aa0BEBAAba0000aBABAabbda00CBAFaBAaC0ga00CADCEC0AaCbc00BGFHBaaA0Aab000JIGBA0CA00A000KIFFDABC0AB000BA0CaACbbDa00AABAbbacbEC000Aa0BB0a0FF0a0");
sw(117,"0aabcb0Dcccb0A0aab0bAAab0a0A0aaA0aBeBdcAA00aaBaaddAbaBB000aBDBaBaACBd000bBBFeBcAAad00beeCaAA0AAhd00bbecGHDDadcd00ba0BDdb0A0aa00aCHEAfhCc0AAaaaGGCAcbcB0BAaa0EC0ahfCcaaDa0AGFCBbdeaaCD00A0GDFEa0CCA00");
sw(119,"0aaaaaB0Bbaaa00aaabcGBBbbba00aabbaGCBbbb000abbbcDDCbbba000aabbDCCbbba00000aaDCBbbaa0000aa0DCAcaa00000aabDBAcbb00000abaCBAca0000000bbCBAb00000000bbDBB00000000bbbDBCaaaa000bbbbDBCaaaa000aabbFBCAaaa0");
sw(120,"00ACAcCADCBAb000ABc0C0AAcAd0000gecCBBbFaaA00acceCAEEE00000bccACDCACB0000cdbdAAAa0Aa00bc0dhaaABBcc00bd0ad00a0Acea0c0BacFBGCcdea00Ba0CGJGBcdd0A0abBDJGEAdec0AaddfDLGG0cc0B00dfegECD00AAAA0caecHDEDDGBA");
sw(121,"0babjhAEAAehcB0bafcCA0AAafeB0b0bba0dBbbCa00bA0ceehbaEF0000abDEBB0GIBb000ecBBAdAGbbb00bfdAdbAFHcmg00bhddBEIEDBej00ecEB0AbCFagc00cEGFAAbJcdda00aGGCFHGBDabA00a0C0ba0Gb0AC00BG00bffcAADG00DFJaAABGHFHD0");
sw(122,"0bbcaA0BC00baA0bbc00FFCDDaCA0bbBCaA0ACcaA00bbA0aAB0ecab0000BAdCB0cbba000CFDECDA00Aa00BD0DIFCABBBC00BD0BADBAA0CD00C0aAAbAddDFC00ba0ceddgcFDBaa0CCccddaAHE0aaAC0Ccgbc0BAda0AACCEaacA00c00ABACCaba0bec0");
sw(123,"0aaaBAB0G0CAa00aaaaBFGEFCAC00aaAACACbGab000a0ADDEEaebcd0000BacAAAeceC000FEBaCCCabDC00EIDBH0BACDIH00EHFFggccBCHI00GDAcd0BddDGF000ahje0DiaFCAaaAcfebbcB0GD0aaAadEacAeCBCha00e0DF0BACBaf000BbC0bBaAcec0");
sw(129,"000adebAAaAcaA000cc0CDCB0caA000c0A0Abc00a00000daBcb0a0e0000aa0BEBAAba0000aBABAabbda00CBAFaBAaC0ga00CADCEC0AaCbc00BGFHBaaA0Aab000JIGBA0CA00A000KIFFDABC0AB000BA0CaACbbDa00AABAbbacbEC000Aa0BB0a0FF0a0");
sw(130,"000adebAAaAcaA000cc0CDCB0caA000c0A0Abc00a00000daBcb0a0e0000aa0BEBAAba0000aBABAabbda00CBAFaBAaC0ga00CADCEC0AaCbc00BGFHBaaA0Aab000JIGBA0CA00A000KIFFDABC0AB000BA0CaACbbDa00AABAbbacbEC000Aa0BB0a0FF0a0");
sw(131,"0000cca0aA0aa0000ae0a000bab0000de0aAA0aba000adbaAABD0ab000bd0BBECCBaa000bcBAC0DB0bb00abCAbAbBBadc00adCDC0aBBAbda0bAEFAA0CCadca0ACDDCDDFB0ab0A0ABBBBDFCaa00A0baaa0CEA000A00beefdbAAAba000abffc0ABAA00");
sw(132,"0000cca0aA0aa0000ae0a000bab0000de0aAA0aba000adbaAABD0ab000bd0BBECCBaa000bcBAC0DB0bb00abCAbAbBBadc00adCDC0aBBAbda0bAEFAA0CCadca0ACDDCDDFB0ab0A0ABBBBDFCaa00A0baaa0CEA000A00beefdbAAAba000abffc0ABAA00");
sw(133,"00ACAcCADCBAb000ABc0C0AAcAd0000gecCBBbFaaA00acceCAEEE00000bccACDCACB0000cdbdAAAa0Aa00bc0dhaaABBcc00bd0ad00a0Acea0c0BacFBGCcdea00Ba0CGJGBcdd0A0abBDJGEAdec0AaddfDLGG0cc0B00dfegECD00AAAA0caecHDEDDGBA");
sw(134,"00ACAcCADCBAb000ABc0C0AAcAd0000gecCBBbFaaA00acceCAEEE00000bccACDCACB0000cdbdAAAa0Aa00bc0dhaaABBcc00bd0ad00a0Acea0c0BacFBGCcdea00Ba0CGJGBcdd0A0abBDJGEAdec0AaddfDLGG0cc0B00dfegECD00AAAA0caecHDEDDGBA");
sw(135,"0aaae0a0AAbcb00aabcBAACCbbc00aabdcd0CEBda00ac00fabCCCab000A0b0ABB0CCb000BCC0BcCbABc00bBGAACdAABAd00bfEIDBcAECBea0dcDHCCAFDA0ea0aAA0DEEDBDAd0A0aAa00BGECac0Aa0abebAFB0dcA00edfhffBBadb000bbdedcAAbAa0");
sw(136,"0bcbb0CCA00aaA0bcccBDDDFBbAA0bb00AaaaCbaA00bcba0CAAcaac000aaABCDCaaca000BCFGECFCbaa00BBEEFFDDDAbB00BBDFCA0CDBBB00BBEEAcaaBCCB000CD0c0bbbGDB00AEE0AabBDIFB00ADBDafbACDCc00Ab0CBdbADBbc00A0a0B0AEFadc0");
sw(137,"0bcbbeBCBAC00B0bcbcBDDCEC0AB0bbabCA0aaeAB00bbbc0Ba0dc0c000cb0BBGAbcga000baCDDFDCgea00Ca0DBEGDDbg000CAABABBB00a000CDDBbdbe0AbA000FFBdbdadB0D00AIGDDC00AEDD00BEEEAd0BABH000BABCAcabCDC000BBAABAAEJEaa0");
sw(143,"000adebAAaAcaA000cc0CDCB0caA000c0A0Abc00a00000daBcb0a0e0000aa0BEBAAba0000aBABAabbda00CBAFaBAaC0ga00CADCEC0AaCbc00BGFHBaaA0Aab000JIGBA0CA00A000KIFFDABC0AB000BA0CaACbbDa00AABAbbacbEC000Aa0BB0a0FF0a0");
sw(144,"000adebAAaAcaA000cc0CDCB0caA000c0A0Abc00a00000daBcb0a0e0000aa0BEBAAba0000aBABAabbda00CBAFaBAaC0ga00CADCEC0AaCbc00BGFHBaaA0Aab000JIGBA0CA00A000KIFFDABC0AB000BA0CaACbbDa00AABAbbacbEC000Aa0BB0a0FF0a0");
sw(145,"0000cca0aA0aa0000ae0a000bab0000de0aAA0aba000adbaAABD0ab000bd0BBECCBaa000bcBAC0DB0bb00abCAbAbBBadc00adCDC0aBBAbda0bAEFAA0CCadca0ACDDCDDFB0ab0A0ABBBBDFCaa00A0baaa0CEA000A00beefdbAAAba000abffc0ABAA00");
sw(146,"0babefAAc0efcA0baddC0Ab0cacA0bafcBAaBBC00A0babbaadaFCAA000aaDFACaCDA0000deB00dAAB0a00bdBagdgCFCdf00bgCBaccCEEaga0dbEAfB0IFchfa0aBBAAEGH0fdea0aaADFHHE0ebba0bdbcCBCF0bACA0A0cbedaCACCDAABDFcebADFGIEA");
sw(147,"00ACAcCADCBAb000ABc0C0AAcAd0000gecCBBbFaaA00acceCAEEE00000bccACDCACB0000cdbdAAAa0Aa00bc0dhaaABBcc00bd0ad00a0Acea0c0BacFBGCcdea00Ba0CGJGBcdd0A0abBDJGEAdec0AaddfDLGG0cc0B00dfegECD00AAAA0caecHDEDDGBA");
sw(148,"00aAcCCCGD00aa00aAdAGCFCAAba00bcgg0CCCEca000ebdgAAEEDbb000a0ecACCBBBc000AC0dabCcCAd00bAD0AEaBbaAc00bcBFCD0BAa0ca0cb0FDFEEBaAca0aAbbCGHACD0ca00abbCDCFHDBda0b00cbFDDAbce00agehfDaA0bfe00cffecCbcaccd0");
sw(149,"0aaae0a0AAbcb00aabcBAACCbbc00aabdcd0CEBda00ac00fabCCCab000A0b0ABB0CCb000BCC0BcCbABc00bBGAACdAABAd00bfEIDBcAECBea0dcDHCCAFDA0ea0aAA0DEEDBDAd0A0aAa00BGECac0Aa0abebAFB0dcA00edfhffBBadb000bbdedcAAbAa0");
sw(150,"0bcbbeBCBAC00B0bcbcBDDCEC0AB0bbabCA0aaeAB00bbbc0Ba0dc0c000cb0BBGAbcga000baCDDFDCgea00Ca0DBEGDDbg000CAABABBB00a000CDDBbdbe0AbA000FFBdbdadB0D00AIGDDC00AEDD00BEEEAd0BABH000BABCAcabCDC000BBAABAAEJEaa0");
sw(151,"0bcbbeBCBAC00B0bcbcBDDCEC0AB0bbabCA0aaeAB00bbbc0Ba0dc0c000cb0BBGAbcga000baCDDFDCgea00Ca0DBEGDDbg000CAABABBB00a000CDDBbdbe0AbA000FFBdbdadB0D00AIGDDC00AEDD00BEEEAd0BABH000BABCAcabCDC000BBAABAAEJEaa0");
sw(157,"0abaAaCD0aBDAB0ab00ADBBDEEDB0abAaaDbCAeAB00adaaaba0ga00000f0AaADA0Acd000fBAGAFCDaae00chdBEEFBG0ib00cbhcBCDDAccca0abbcag0ba0CAa0aaCaehfafCBCba0FEc0a0a0EE0baCECBcjdA0AA0a0BJFDDcbfC0A000ACIFD0cBDbab0");
sw(158,"0bbb0c0BCaA0aA0bbbabCCBCB0CA0bb0BAA00ae0A00bb0aABC0edbb000aBBaCCA0bf00000BAFCEBDac000BAcBFCCADAdD00BEbdcaABAbaD00DBabbdAabABD00a0BbgdbdfBCDaaAFDb0A0cbGFBaaBC0D0ecdbBDba0ADDGEb0bACDb00ACCDD0ADEBcb0");
sw(159,"0aBAaedcB0accA0aBaAabacafdbA0aBaE0AAbbCbaA0aDE0BBbb0b0b000CBC0aabaa0C000BaadadfebAC00CE0bbfabBFGB00CDCafeBd0EEA00CDAacCbDa0bb00bB00aADaBfcbaaaBAEDFB0ada0aaa0bAIIBbcbE000AADGCDBBcCGCAADEEHFCCDDGFEA");
sw(160,"00ABBACCBAa0a000ABCCBCABaB00000a000aB0Ca0A00AA0aa00DAaB000A00a00aBA0A0000bdccaaAB0A0000adddcBCBa00000acdd0AA0a0000aaddA0CAcca00aacbAADAadcbaaabcADED0bcbbaabbbbEFBabcbA0000ABCEC000CBAA00BACDBAADDBA");
sw(161,"0BBCBDDCGBBC0b0BBCdAJEGB0D0b0B0cdeDECBDab00BcabfBDCDBbb000aahiBBAaAEc000AEcg0AaeCDc00aAbaBCAabaDa00abcA0DAaabAa00abeAAFECaAFb000bee0CFbCEBa000deecAb0BDBc00babbaFBcA0cd00bdaccHBAAacd00dfhc0HBccebd0");
sw(162,"0bccgdCBF0bcb00bcci0IBCAbac00bceebCEBECd000bec0gCBEEDaa000bBbbADBbCBb000aCBcC0AdBCe00daEA0FbbcCDe00deCIAEbb0BBec0ebAFBGEDABAec0aAabAIJCBEadbAaacccCDGHCacbA00dceDDHDAdcA00fijkAcDBafe00accffCaCAb0b0");
sw(163,"0abaCeEACfED000abagA0cHKGEB00abadBg0eGGBA00aagaAFDEAaGd000cdeACIAbblK000acADHJIGedG00BbFabA0gEfkK00B0DCgkgaBCADd0ECE0fdAeC0cDd0AAbecBEacEaEcACCa0DAEFAHBDcAD00FdgD0ECDkA000d0eh0aCLah00a0bfgiBJIaeb0");
sw(164,"0bbb0c0BCaA0aA0bbbabCCBCB0CA0bb0BAA00ae0A00bb0aABC0edbb000aBBaCCA0bf00000BAFCEBDac000BAcBFCCADAdD00BEbdcaABAbaD00DBabbdAabABD00a0BbgdbdfBCDaaAFDb0A0cbGFBaaBC0D0ecdbBDba0ADDGEb0bACDb00ACCDD0ADEBcb0");
sw(165,"0bccacaADGCB0B0bcb0aBDbCCABB0bbAAACB0amBB00bc0b0Abbhcfa000d0BB00bcbfh000cACFAEADech000bcBEBHJGAAf000BcdaBFCBAB000AAadbeafaDDA00aAAbeffeeDDB00AEEbbacebFD000CBCEbfdcaCEE00BCCFFaAbDdC000BCDDFBBbEB0a0");
sw(171,"0bbaFB0ba0CEA00bbCBaACBDDFD00bb00aA0BD0aC00bdba0BBB0abB000e000b00aefa000da0DaFEDBac00ceacA0aBCE0a00cacbddgBCBBAb0acehgfBaaAB0b00eehgcAccBB0b00dcccbbacBA0b0BabA0gdaCBAA000A0BAc0CCC0b000BDBaa0BB0000");
sw(172,"0cab0e0BAaadbA0cabAAEEACC0AA0caaFCCaC0aAA00cAAAAaabcaB00000AEBA0b0adB000aaBFBE0DaaB00Bae0B0BAEDdA00BCcgf0CBA0aA00BAagedbbcBaA00cABaedccfb0AaaaDDCDEBeeAAAaa000DEbb0aAD0a0AEFIHAAbaCGC00CGIFEECEEECC0");
sw(173,"0bbcacACDa0caB0bbcBADECDB0BB0bb0FA0aBCA0BA0baBB0caaa00A000ADE0AacaAaA000ACCD0AbCA0A00ABbADAbaDE0A00ABaab0abBBAA00Aaba00aabCCA00ca0abccccBB0aaaBCAa0acaEAbaa0BBCAcbbAB0b00BBDED00BDDCAAABDDECBAEDCAAA");
sw(174,"00AADBCDDACC0A00A0DACDBDBCCA000BD0Ab0BAaAA000CCDbaaa0aA0000DEaabbAB000000C00d0aCCA00000baBbaBEEBB000BbbbcAACBCB00Bbcba0AAbBDC00bdbcddabcABAbb000AA0AabECbbb0AaCCbaeaB0aa0AFEGGCCACCCAAAACFFEBCBB00AA");
sw(175,"000ACADCGACA0A000AC0JECBBBBA000BEAGBBA0aAA000CBAABBcaaA0000DAcB00ca000000BbbAD00a00000AcbACCBADBA000CcdeACabABA00Aaed0DBaeCEB00cbccc0accAB0bbaAaBBEBaaECcbbaAACBEBaABAba0ADFEEIEDBBAAAAABCFEIDECaaAA");
sw(176,"0ddedkDBCb0dcB0dddc0HBAABbbB0dde0BHBBcABBA0dccaaBABbaAa000aAFCCHbeAeA000caDCEHb0bcA00CcbAbFEACBe000C0bceFB0aAd000CCAbf0c0bAd0000CEBdaa0e0bD000EED0FBabA0D00ACCBCDDF0BHCA0B0aCdBCCBGGBAABCD0cGEKMLDBA");
sw(177,"0dddciAAa00bbC0dddcBAB0DBA0C0dcc0CB0A0aCCA0dcab00bbcaBb000caFEAFaa0g0000dcFGCECEdd000Cd0A0ADCHAga00C000baAACCba00CDDafdebC0e0000EGBdcb0daaC00AHIGFGBaaBBD00BDEDEcADABJCA0CBAE0d00DHHCAADFGB0aAHMKFCA");
sw(178,"0cab0e0BAaadbA0cabAAEEACC0AA0caaFCCaC0aAA00cAAAAaabcaB00000AEBA0b0adB000aaBFBE0DaaB00Bae0B0BAEDdA00BCcgf0CBA0aA00BAagedbbcBaA00cABaedccfb0AaaaDDCDEBeeAAAaa000DEbb0aAD0a0AEFIHAAbaCGC00CGIFEECEEECC0");
sw(179,"0000aaBBAAbbaA000aAB00aAa00A0000C00a00CB0A00ACB0baaAABA000ACCA00aACCA0000A00abb0BBA0000bbbbcaBBa0000abbbb0bA0aa000aaaaB0CAbba00aaa0AACA0cbbaaaaaABDB00babaaaa0aCBA0aba000ABABABAA0ABBAAABDCBBABBCDBA");
sw(185,"0b0acAaaAbgfcB0b0bCCBCaAbbaB0b0AB00cCGG0AB0bBECccaBDFDD000CDAbBca0FGB000CCabcfdaDFA00bC0b0cfaCFE000baaBaAAaCCCaa0ceba0FCECA0ba0ddedACEABacfbacddb0ACCAadebabbed0DCCaafaA0B0aaCAa0AaACBBDCEACAbBaBGDB");
sw(186,"0cbbDE0b0abAbB0cb0G0ACaCCDBB0cbCE0AbDFDbCB0cbAABaCEBaaD0000CCC0aaba0B000Aa0GbCABED000c00gAch0EKEB00cAcaegg0DDFBb0adffb0DEAADab0bghibAEb0ACecaaeedaaCBbB0fcaAbbcaaABDAbaA0B0ACBaBECCA0BBCBFEBAAFABCCB");
sw(187,"0bbcacACDa0caB0bbcBADECDB0BB0bb0FA0aBCA0BA0baBB0caaa00A000ADE0AacaAaA000ACCD0AbCA0A00ABbADAbaDE0A00ABaab0abBBAA00Aaba00aabCCA00ca0abccccBB0aaaBCAa0acaEAbaa0BBCAcbbAB0b00BBDED00BDDCAAABDDECBAEDCAAA");
sw(188,"000ACeBAEADC0A000B0aFDBBACBA000bCCGCBbaBAA000A0BCBAbca0000cBC0CBabcd0000c0AACGABdd000Abda0BEBDAdA00ACcgeADabaaA00BAbecA0bdaAA00b00aebabec0Aaa0CCDCGCddBCaaa00AEGFAdc0Da00ACDGFHFBACDAAAABBDEIEEFCBAA");
sw(189,"000ACeBAEADC0A000B0aFDBBACBA000bCCGCBbaBAA000A0BCBAbca0000cBC0CBabcd0000c0AACGABdd000Abda0BEBDAdA00ACcgeADabaaA00BAbecA0bdaAA00b00aebabec0Aaa0CCDCGCddBCaaa00AEGFAdc0Da00ACDGFHFBACDAAAABBDEIEEFCBAA");
sw(190,"0ddedkDBCb0dcB0dddc0HBAABbbB0dde0BHBBcABBA0dccaaBABbaAa000aAFCCHbeAeA000caDCEHb0bcA00CcbAbFEACBe000C0bceFB0aAd000CCAbf0c0bAd0000CEBdaa0e0bD000EED0FBabA0D00ACCBCDDF0BHCA0B0aCdBCCBGGBAABCD0cGEKMLDBA");
sw(191,"0ddedkDBCb0dcB0dddc0HBAABbbB0dde0BHBBcABBA0dccaaBABbaAa000aAFCCHbeAeA000caDCEHb0bcA00CcbAbFEACBe000C0bceFB0aAd000CCAbf0c0bAd0000CEBdaa0e0bD000EED0FBabA0D00ACCBCDDF0BHCA0B0aCdBCCBGGBAABCD0cGEKMLDBA");
sw(192,"0000aaBBAAbbaA000aAB00aAa00A0000C00a00CB0A00ACB0baaAABA000ACCA00aACCA0000A00abb0BBA0000bbbbcaBBa0000abbbb0bA0aa000aaaaB0CAbba00aaa0AACA0cbbaaaaaABDB00babaaaa0aCBA0aba000ABABABAA0ABBAAABDCBBABBCDBA");
sw(193,"0000aaBBAAbbaA000aAB00aAa00A0000C00a00CB0A00ACB0baaAABA000ACCA00aACCA0000A00abb0BBA0000bbbbcaBBa0000abbbb0bA0aa000aaaaB0CAbba00aaa0AACA0cbbaaaaaABDB00babaaaa0aCBA0aba000ABABABAA0ABBAAABDCBBABBCDBA");
}

void recognizer::teach()
{
  const int CYCLES = 200;
  const int DIGIT_FILES = 20;

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
  case 2: // light gray
    (*img)[i][j] = true;
    if (max_j && *max_j < j) *max_j = j;

    fill(img, i-1, j, max_j);
    fill(img, i+1, j, max_j);

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

    const int i = height / 2;
    const int i2 = height* 1/12;
    const int i3 = height*11/12;

    while (pos < width)
    {
        if (image[i][pos] == 1) break;
        ++pos;
    }

    if (pos == width)
        return image_array();

    image_matrix matr(image.size(), image_array(image[0].size()));
    int ps = pos;

    fill(&matr, i, pos, &ps);
    fill(&matr, i2, pos, &ps);
    fill(&matr, i3, pos, &ps);

    pos = ps+1;

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

