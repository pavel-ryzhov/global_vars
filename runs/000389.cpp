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
sw(  5,"0A0BDKHIBHDFA00A0AdEFJDGGGD00AaEbeCbaDcB000Ad0addbbe0e0000dabg00bBCAe000bEBEbAFCCAe00cgd0EDBEH0ea00cdibCCFFFbaa00agg0BaD0CDGC00acefddbecIFAbb00bhbdcbAKGcbb0CBBficeADacb00FIBE0biG0bb00b0BBG0Af0gdd0");
sw(  6,"00AACBFFEcbB0A00A0CEEEGGDECA000BCaAbBEEBAA00AAAAdaaCACB000aABbAbcCBBB000aB0CcaACCBA00acccBdd0DBaB00aafbadABBb00a00dccaaDBabBBa0cdbdcbAbc0AAbaaaAbBACbcCAbba0BABBbbf00cc00AFFGGAAbCBBAAAACFEFDDEAbBAA");
sw(  7,"00AACBFFEcbB0A00A0CEEEGGDECA000BCaAbBEEBAA00AAAAdaaCACB000aABbAbcCBBB000aB0CcaACCBA00acccBdd0DBaB00aafbadABBb00a00dccaaDBabBBa0cdbdcbAbc0AAbaaaAbBACbcCAbba0BABBbbf00cc00AFFGGAAbCBBAAAACFEFDDEAbBAA");
sw(  8,"00ABE0JGKcAC0A00ABCCMEGEDEBA0000EcFeDEIBAA000ABAcaEBEGB000cABcDccaDCC000dBa000aACCa00eefbBCAcCBeA00eaigcEECAdacd0ceheaDGCbBEad0fgceeb0ceBCaeac00dbBF0fFCeeaABBAb0bc0Cbg00AHFFEEAaBEAbAAABFEGMDJCdAAA");
sw(  9,"000AAEBCAPFE00000ae0AHcGFEA000aDb00CcCiC0000bAcdDcad0la000AacAAa0a0eh000B0DCC0FCbeh000aEABDAOK0Ag000bDBB00GIEC0000bAC00aDFDDA000FccaAAAbEE000CGBaAAABBIFa000CBCecaa0CCE000aFAbbacEdAb00aab0CeBiDAab0");
sw( 10,"00ABJDCaaMII0a00ADC0AFeEBECa00aaCADD0ajc0000bbdDFCccgrb000cbbA00aBijg000ab0BAEEAbcf00CBAbD00KFCHc00CGBcfheBBBAFA0FEahfeAae0EDA0B0efdbBea0DB0aCaAADCBbcCE00aAb0CFABeA0HFa0abEEEBFCCaAb00bAbFC0BhDada0");
sw( 11,"00ABJDCaaMII0a00ADC0AFeEBECa00aaCADD0ajc0000bbdDFCccgrb000cbbA00aBijg000ab0BAEEAbcf00CBAbD00KFCHc00CGBcfheBBBAFA0FEahfeAae0EDA0B0efdbBea0DB0aCaAADCBbcCE00aAb0CFABeA0HFa0abEEEBFCCaAb00bAbFC0BhDada0");
sw( 16,"00BCCCBBBCBBaa00BCABBBBBBBaa000abbaaaaBaa0000bba000BAa00000bba000B0000000aaaa0AAA0000000aaa0DAa0000000aaaACAa0000000aa0AAa0000000aa0AB00000000aa0B0AA000000aaa0ACBa000000aa0a0BAaaaa000aabb0BBaaaa00");
sw( 17,"000CKJEBBDFJBa000FBBBDCEBHDa00aAcbA0A0bcB000dceADCBBdfA000fdeaaA0Ahfb000dcbDcFHAAac00bdAcAa0DCCBA00bBbabgeDABCCa0A0dgefDaA0DBa0BcgiebCc0CCBa0Bcdd0a00bCC0a0BaacBbAdDABA00aaBACBFADCAc00bcbBCACa0bbb0");
sw( 18,"00AADGDDaD0EAA00AAbBAFaBDHCA000ECaDa0FCEBA00a0BAcaAACbE000aBBaadbAEBa000b0aBcbCBECb00ejddabaDHCba00eegdbaEHE0Baa0cigec0DHDADAa0adffcaCAdADaba00ceb0EaeCDcbaADaAabbaBBdB00AHIDECCdD0CBAAACIDGAE0A0DBA");
sw( 19,"00AACBFFEcbB0A00A0CEEEGGDECA000BCaAbBEEBAA00AAAAdaaCACB000aABbAbcCBBB000aB0CcaACCBA00acccBdd0DBaB00aafbadABBb00a00dccaaDBabBBa0cdbdcbAbc0AAbaaaAbBACbcCAbba0BABBbbf00cc00AFFGGAAbCBBAAAACFEFDDEAbBAA");
sw( 20,"00ABE0JGKcAC0A00ABCCMEGEDEBA0000EcFeDEIBAA000ABAcaEBEGB000cABcDccaDCC000dBa000aACCa00eefbBCAcCBeA00eaigcEECAdacd0ceheaDGCbBEad0fgceeb0ceBCaeac00dbBF0fFCeeaABBAb0bc0Cbg00AHFFEEAaBEAbAAABFEGMDJCdAAA");
sw( 21,"000ACADCGACA0A000AC0JECBBBBA000BEAGBBA0aAA000CBAABBcaaA0000DAcB00ca000000BbbAD00a00000AcbACCBADBA000CcdeACabABA00Aaed0DBaeCEB00cbccc0accAB0bbaAaBBEBaaECcbbaAACBEBaABAba0ADFEEIEDBBAAAAABCFEIDECaaAA");
sw( 22,"00AAAAFCEAAA0000AABCHEECBA00000ABAEBBACA0000AAAACBBBBA0000AAA0CBBABAA000AAA0CBBABAA00AAAA0CBCAAAA00AAAA0CBCAAAA00AAAA0CBC0AAA000AAA0CCC0AAA000AAA0CCC0AAA000AAAADCBAAA00000ABAEDCABA000000ABHEDDA000");
sw( 23,"000000DDBA000A000b0BBBCDAAAA000ACCa0ADDBAA00ABBBA0ADBBA000ABCBAA0BCBA000AACB0aACBAA00AACBA0aBDBAA00AACCBa0ACCBA00AADC00aBCAAA000BBBBAABABBA00ABCDCABABCCA000BBBC000BAAAA0AABCCABCDDBAAAAAABCABDECBAA");
sw( 24,"0A0BDKHIBHDFA00A0AdEFJDGGGD00AaEbeCbaDcB000Ad0addbbe0e0000dabg00bBCAe000bEBEbAFCCAe00cgd0EDBEH0ea00cdibCCFFFbaa00agg0BaD0CDGC00acefddbecIFAbb00bhbdcbAKGcbb0CBBficeADacb00FIBE0biG0bb00b0BBG0Af0gdd0");
sw( 25,"000CKJEBBDFJBa000FBBBDCEBHDa00aAcbA0A0bcB000dceADCBBdfA000fdeaaA0Ahfb000dcbDcFHAAac00bdAcAa0DCCBA00bBbabgeDABCCa0A0dgefDaA0DBa0BcgiebCc0CCBa0Bcdd0a00bCC0a0BaacBbAdDABA00aaBACBFADCAc00bcbBCACa0bbb0");
sw( 31,"0bcbAEACbABC0A0bcacaCH0AGDBA0bcDAbCbAEbAB00bdb0ac0DfAeB00000Aa0bAbCea000BBAE0ADCAab00cfcBFGDBGCfB00cafbAFEHEa0Ba0afgbAbBDBFGDa0aadfdedbeIGAba0Ebjgg00aJGbbaBG00jieDBEbca0ADHACbbfE00c0000FBEaA0Abdc0");
sw( 32,"0bcdabDEEfeb0C0bccECCEEDC0CC0bbEFaCcCEDDCA0bADCAeaBbAFD000aFFbBacaCBD000aFBDc0aBBDB00bceaCacfACdD00b0hbaBBa0caAb00fdc0AF0aaBCb0efaceebbeAA0dbbACccaDabFBcdbBDBAdhca0Acea0CGDEFbaaEDBAAACEIEGC0ICaBAA");
sw( 33,"0bbaFA0A0gbD0B0bbAIc0aEEEFDB0bbCCb0dFeBaCA0bbabCcAEBfDB000aAFBAD00dbC000e0BOaJ0DDcA00bgccBadeDEiD00b0jgCcdCabb0b0AbdaagAB0c0cb0beGCehe0caABca0GJBC0AceCBacaCBBcDgdac00A00BIDJEb0cbFHAAABaFFGCdICFAAA");
sw( 34,"0aaaaddbDGD0a00aa0bhGBffdca00aacA0JIBekc000abAccGDCfekb0000AcaBACfeeh000AAbcDBbeech00AE0CBEGFaCHg00AFDbcED0dAAA00AFacaCaAfDDa000EAa0A0bbAD0000DAacCa0a0D0000Ab0aFaCcaEF000cC0aGBEbfBb000abCAG0dCBba0");
sw( 35,"0bbbefda0EDcc00bbcgeGCb0bdd00bbgdAEEBadda00bccgfECC0bfb000aaeaDGCbddc0000babGEAcfcc000DBD0GCCCC0d000AFDaD0bbGCc00bDDC0Aa0bCCc000FBBADCCAABbAAaDAA0CBCE0BaAAaabb0HFGC0D0A00fcghBBEA0aa000bdceBA0FC0a0");
sw( 36,"0bbbeiBA0bcdcA0bbcdbEa0adbeA0bbgbBECCBDa0A0bbd0dA0CDD0B000a0AEBCAaDAA000deacDbcAa0000cdadgBaABBce00cgaadAa0AAcga0ebAbdDbGBafga00AABBFEHAcde0Aab0BaHFDBdcc0Aacab0ICJB0aBB0AcfchB0ICAaCAAAACcfHDKIEGDA");
sw( 37,"0caclhAGGhhidC0cagdDEBIEAcdC0ca0acffBCKC0A0cCC0ehhDGFO0000EBD00B0DLEG000CED0aeaBACD00a0ACdeffCaiB00ag0CBDGAACCfc0cdEIBEADD0edc0eCFDBBBHbadbc0bHE0B0EFEAb0c00D0add0FcaefA0CFaacehfcEDBAAEDHcCA0HDFFCA");
sw( 38,"0ABCABDGGaa0aA0AB0DCCEFCBA0A0AAAAcada0FAaA0ABB00fcaBDC0000AABcAaaDGEA0000C0cefdBDBA0000cAafb0CAbA000bdcA0EAAaab000bbAADCC000a00baAA0ba0AaaaaaaABbA0a0a00baaa0A0AAadeabb00ADDDFBad0BCBAAAACBGDAAABBAA");
sw( 39,"0000cdAFBc0aAB000acACCBa0aAB0000bbAdabf0A000aa0befadAA0000daAcaAaAF0e000dCaacAaDcae00bgfE00GBEbid00bcgcCGJD0cce00bb00AcbcaBA000bCEBbgiBeCaBaaaHDa0cabBDAAaaAFADcgeAbAcAa0BIEBEadhBd0C00BBGBFD00Ba0a0");
sw( 45,"0decBFbbd0dBbD0de0DaaHdaFHBD0ddHDcDcCBBBEC0dcAA0ebEbcdH000BDGDabbg0A00000aCKdC0bDAb00ejbeADcCFKca00eejcBDAFC0Bab0cijc0ADIBBCcb0bbeeaa00cBBdcaaE0ddcBadBafcaBGAecdbHBAeEB0DEIBBAAcDBEDCCDAJGGAaDBIGDC");
sw( 46,"0ccbGCABAifAcC0ccaJaCECDFGCC0ccDFaAgF0HaCC0cABDDf0HDfDF000CDJ00AbgcCG0000ADOdGccEBB00deadAbjgCLeF00dAicDbdB0c0Ae00deA0cFHaaCee0efC0bg0bcACdgbcFF0AfE0gDAggbBDchAhdBb0fbA0CHFGEbac0DF0CCCbGFIEeJaEDCC");
sw( 47,"0bbaE0Ab0dACb00bb0G0CBDGAAB00bbaCA0ABabe000ba0cCFCbbhcc000a0aBCCAajeB000BCCHDHB0bBB00DHEAFaccBFEF00DHDCbhieaDFF00FGDcceAeeaEA00Aa0ddb0fAABA00B0DaB0db0BB000Bcb0EcaeAaDc000dbFEbAC0CAc000abECBcBBacb0");
sw( 48,"0aaadcbacIDbc00aacda0AeBbed00aaddA0Aabfdb00a0bebDa0Adgb0000bbBBFBBcdb0000c0bE0Baecb00ADDCaDbFFBac00A0GFB0b0BGBb000DGF00bAAAab00AFBDBDCECaab000DACDCDFG0B000abbbAEFFB0FB000ddggcbBB0a0000accddbbFD000");
sw( 49,"0aaaccAaAaaca00aa0eaEAAbccb00aaeebEDCabd000acecdEEECacb000cdbaEGDA0db000bc00FCDAadc00abAabE0Aaadc00abAB0DaAaaeca0bABCAD0BAadba00CCBBFDDAAaba0aAABBGEFEA00a0aaabbFDGB00a000defgBaCA0cb000bcffEADCAaa0");
sw( 50,"0aaaccAaAaaca00aa0eaEAAbccb00aaeebEDCabd000acecdEEECacb000cdbaEGDA0db000bc00FCDAadc00abAabE0Aaadc00abAB0DaAaaeca0bABCAD0BAadba00CCBBFDDAAaba0aAABBGEFEA00a0aaabbFDGB00a000defgBaCA0cb000bcffEADCAaa0");
sw( 51,"0ACEBbFFBdBAb00ACabD0cHH0Ac00ABge0ggdaR0bA0AB0faaeAKBNe000beaBAGaF00J000beBa0bC0bcG00ABF0jhgiCblF00AcGEBhdcCD0ec00EIHbABDFhjgc0aCFCBEJDChecbAaACFMFGG0gb0bAacAcIFFcefEkB00cebedabeKBbAAAbbeaa0GEDEBA");
sw( 52,"0ABCABDGGaa0aA0AB0DCCEFCBA0A0AAAAcada0FAaA0ABB00fcaBDC0000AABcAaaDGEA0000C0cefdBDBA0000cAafb0CAbA000bdcA0EAAaab000bbAADCC000a00baAA0ba0AaaaaaaABbA0a0a00baaa0A0AAadeabb00ADDDFBad0BCBAAAACBGDAAABBAA");
sw( 53,"0aaagAaEA0ccaA0aabe0CGAbAbaA0aaDceBcABc0000aa00ffcCeCaB000B00d0aAaHDc000CEaacc0AABc00cdcCCDDCDAfb00cdeADJKGDc0c00dgcDFCAECDDA00cB0a0bdCeFBaaabFbgef0ACGBbaaaH0BiedEaCfba0ADFaAafgCebA00A0DaEBA0acab0");
sw( 59,"0ccbGCABAifAcC0ccaJaCECDFGCC0ccDFaAgF0HaCC0cABDDf0HDfDF000CDJ00AbgcCG0000ADOdGccEBB00deadAbjgCLeF00dAicDbdB0c0Ae00deA0cFHaaCee0efC0bg0bcACdgbcFF0AfE0gDAggbBDchAhdBb0fbA0CHFGEbac0DF0CCCbGFIEeJaEDCC");
sw( 60,"0cccB0ba0bbAbC0ccbFcAEADADCC0ccCEAA0EabcCB0caBACaACAgdC000DEFBBAacdaB000CDCI0Ga0AAB00ABAbDAeaCICD00ACbaabb00AED00Cbb000BBc0Cb00bdA0bbabb0AbaaADFBA0AcdD0eaaBBa0EaA0b0cAA0CBCGGCDAAAEBBBCACEGCbCAEBBB");
sw( 61,"0bbbEAcecEDDa00bbABc0DdAACB00bb0CADE00jdA00bdbcBFBbfinb000b00B0Aadjie0000bBEDHDadbd00BABbCABGDFIb00BDBaffdABEFDA0DCbged00dBE0A0B0dgea0eaAD0A0C0Aa0AbccBCaA0B00DC00bBAFD000cDECAEEBbAa000BAFAaBdB0b00");
sw( 62,"0000cca0aA0aa0000ae0a000bab0000de0aAA0aba000adbaAABD0ab000bd0BBECCBaa000bcBAC0DB0bb00abCAbAbBBadc00adCDC0aBBAbda0bAEFAA0CCadca0ACDDCDDFB0ab0A0ABBBBDFCaa00A0baaa0CEA000A00beefdbAAAba000abffc0ABAA00");
sw( 63,"0aaaccAaAaaca00aa0eaEAAbccb00aaeebEDCabd000acecdEEECacb000cdbaEGDA0db000bc00FCDAadc00abAabE0Aaadc00abAB0DaAaaeca0bABCAD0BAadba00CCBBFDDAAaba0aAABBGEFEA00a0aaabbFDGB00a000defgBaCA0cb000bcffEADCAaa0");
sw( 64,"0aaaccAaAaaca00aa0eaEAAbccb00aaeebEDCabd000acecdEEECacb000cdbaEGDA0db000bc00FCDAadc00abAabE0Aaadc00abAB0DaAaaeca0bABCAD0BAadba00CCBBFDDAAaba0aAABBGEFEA00a0aaabbFDGB00a000defgBaCA0cb000bcffEADCAaa0");
sw( 65,"0ACEBaCBAGBAa00ACAcCcabCACb00ABeebaab0HCaA0ABbdcAcaEGD0000cfaCABACCC0000ehAbbeBABab00bdDcifdEE0ef00beEB0ebADBdgb0dAGBdB0FFeheb0aEBCDEIEAgddaAa0AGJIGFagdaaAbdadFFDBadABB00acdfbaaaABBAAAAAedb0ACEIDA");
sw( 66,"0ABCABDGGaa0aA0AB0DCCEFCBA0A0AAAAcada0FAaA0ABB00fcaBDC0000AABcAaaDGEA0000C0cefdBDBA0000cAafb0CAbA000bdcA0EAAaab000bbAADCC000a00baAA0ba0AaaaaaaABbA0a0a00baaa0A0AAadeabb00ADDDFBad0BCBAAAACBGDAAABBAA");
sw( 67,"000bgaAGEgefaB000faAFDGBBeaB000BabaeaAAAa000BBBagdC0AGb000CBAgAC00HDA000EI0cbcfabB0000BfEB0BebdfC000ceBGJKAbe0ba00d0JHCCbaBAaa0daGEAefaaEAacbcFEcbgbADGDbcb0FABgfdadAehb0BFBAE0fiadba00BaCbHFa0bcdc0");
sw( 73,"0bbbCCaaD0BAa00bbaCaCFBCCBC00bbCDa0CACadA00baBAADDAceca000BC0bA0AefbC000FCACAFCbBEC00CHDaEAcb0JJG00CHEEeefbBCIH00ECaba0D0dCGC000afhdADgaDD000B0ddbbb0bEAb00BAdA0bAbCA0e000e0BB0BBA0Ad0000aCAa00cacb0");
sw( 74,"0bcaDC0BCc0Ba00bc0DbFIEEDED00bcDBAA0DbefA00bbCABBBAchf0000CDCaBCAehc0000DEDK0JAbBa000BDCBHFaAAICD00BE0BDAeBAaEE00DAbCBcC0cCE000a0AacdcfaECAaaAFE0adfcaGBbaaACa0AhdcaAbaa000FGEaad00Db00acaGGBcaaCdc0");
sw( 75,"0ccbC0abea0E0A0ccBAbaCbEEEAA0ccAdbAeBbc0C00ceefABAFA0cA000dcBEDFC0ahd000fcDOBJGECgh00ekCAaDcCHBne00edc0GBhHCCcdd0cbADafBCG00ad0aAHCccaFdCDAd0aJJBA0EEaEBAd0CB0eembGBC0E00AE0AgjceAFDb00AdDb0cbCHF0a0");
sw( 76,"0bb0DAAbdEDEA00bbDaA0CaFDEB00bbacA00AE0aC00bddeaECCDBdB000fbbDCCBBdgb000fcCHEEKFBde00deHB0CfDHDde00dbDE0enBEHAbc0daCbgdAAD0A0c000bdcDEDaBCabAabaa0ADGAAAAbAAdbcdgAEFABCA00ccehibCDFbc0000acghcAGA000");
sw( 77,"0bbbB0AcAcAD000bbC0cIBB0ADB00bb0abIDECabB00beaccGEEacbA000eAccDBBcdea000dabCFGE0Aac00ddad0F0aBD0000d0dceBdBaBC0b0bbfge0BAbAD0b00dehgBBacBD0b00bcffCABaBDab0BacbeAaBBAAa000A00dCACAC0c0000CBbEADCaaa0");
sw( 78,"0cedBbCd0ADFA00ceDdcHCBBAEB00cddcaIFFE0cD00cjfgfKGIC0eA000jbdbDFDbejd000ie0DGKJCBeh00giCdcI0ADEde00gba0dCiCAFAcd0eadegaB0CBCcd0AbcffEEAaEEbcA0aabdFCECDDacACbbcdAAHFCCAA00dgfkAAGEGcf00acaddCaGGBab0");
sw( 79,"000BCaED0DCDAA000BbEBC0DEHBA000abAAaBCADBA00bcd00aaADBA000ff0ECB0DCdb000ij0G00GIBfd00cjacc0aGLbmf00cdcdAdbGEAffb0c0AcfbaBGadAb0aDAa0BBDdaBBb00DCDHIHCcABAb00bCbbfaBB0DDA0AGEBcfbdDIFBAAACFAbdAEJFECA");
sw( 80,"0ABCABDGGaa0aA0AB0DCCEFCBA0A0AAAAcada0FAaA0ABB00fcaBDC0000AABcAaaDGEA0000C0cefdBDBA0000cAafb0CAbA000bdcA0EAAaab000bbAADCC000a00baAA0ba0AaaaaaaABbA0a0a00baaa0A0AAadeabb00ADDDFBad0BCBAAAACBGDAAABBAA");
sw( 81,"000bdaBBFidfb0000dcEECICAeb0000a0AcbcHJBb000AAEbcaabEId000ABbhAaadFCG000FGBf0dccbFG00CFaBBbBibeaJ00CAAEaBEdaaBC00CaACBDAeaCCC00bbcdab0fAF0aaaacbdcdcBCFAbaaaadBebAc0Adoa00debC0bdABdd000abe0a0Bcfcc0");
sw( 87,"0bbbCCaaD0BAa00bbaCaCFBCCBC00bbCDa0CACadA00baBAADDAceca000BC0bA0AefbC000FCACAFCbBEC00CHDaEAcb0JJG00CHEEeefbBCIH00ECaba0D0dCGC000afhdADgaDD000B0ddbbb0bEAb00BAdA0bAbCA0e000e0BB0BBA0Ad0000aCAa00cacb0");
sw( 88,"0bbbCCaaD0BAa00bbaCaCFBCCBC00bbCDa0CACadA00baBAADDAceca000BC0bA0AefbC000FCACAFCbBEC00CHDaEAcb0JJG00CHEEeefbBCIH00ECaba0D0dCGC000afhdADgaDD000B0ddbbb0bEAb00BAdA0bAbCA0e000e0BB0BBA0Ad0000aCAa00cacb0");
sw( 89,"0cdcaC0deHCAb00cdddaAGcFDB000ccCaCBEaGbcA00cbaaaGAacbk0000CBbCaBAdge0000EaBBCCEcaA000BDIbCEdECHH000B0IKcejbEIHD00BaCBcBCCBBCA00AChgaIJa0CAb00Bae0BCBCCD0a0000c000CEGACA000hacedaDECab000AbAdhbcEC000");
sw( 90,"0dfdbFcacJBCaB0dfddd0MdFDD0B0deGbABCA0lcC00de0bcAcBcesB000DC0EbBBeehh000EBEI0EDbaeh00abEaCHbKEIBg00afBGFDfEEEE000afcHEaBEEEBc00AFb0AAAB0FBc00BJEaebcADH0c00BGBadfbHEDbH00BeDaeedcGcC000Ad0CEb0fGKAb0");
sw( 91,"0cefeaA0GKB0aB0cedccLGe0BaAB0cdADaKFEBoAB00cfAacA0Bibm0000bDA00d0e0dl0000EBCCA0ab0l00b0fAIJGKDDIi00bBfecIGC0ACA00acieAAAadHJB00bbfggcdeeHG0aa0BajkaccAJHdaaBBAAhbdBAECEa0BACCCEACEg0c00ABDFEICdEacc0");
sw( 92,"00bbb0DDELFB0000bad0JEaED00000bbbbEDBDhA0000ecefEADcAia000daebDDBaAbj000b00AEDDCbbj00babAAIELH0Bh00baa0AFCDCDBb00baaAAA00BEGA000BccbBaAaHFA00ABadcAaBFIGb0000AAfA0BCCBC000a0bdB0CFecc00bcba0EDcGbdd0");
sw( 93,"000AB0BaBMEDaA000bhBeDcFAEAA00000C0IgJ0DAB00aAAbEAeb0hb000baaCaccbah0000AdCeCgFDec000CAGf0fbJNBGa00C0GEipdaLHDC00CA0fhDcEF0aB00ADllbFKcBaac00Ccg0EJEDACBb00aa0GCHEdBAHaB0AhAAa0CFIBAbBBAE0AcjE0GCFCB");
sw( 94,"0cbcDCbeAabbcC0cbbFA0B0DABCC0cbAG0ACADCcCC0caACCAB00gcA000CCECAbehfaE000DBEHCBbd0CE00CFEdEbgbELLF00CEBBgjfdCFGF00D0cedAaCdBDb00beghbACiAAAdaa0ebaAAaaeBafaa0bb0FEDcA0AcB0CdCGGDFFBBC0CCDDBGA00E0CCDC");
sw( 95,"0000aCCCEdcca0000bADDCCBBca0000BBacccBF0a000BBC0a0AABDb000CBadA00eBEC000FFBb0bcgBFB00BFDDB0bfdBDE00BBCGBBbdb0CCa0BABEBBC0bADAa0aAab00BdADA0a0aAbedebCAB00a00Bcddb0aAadf000dbbaabdbaad000dcaBAa0cabc0");
sw(101,"0000aba0BaA0a0000a0aA0AAbba0000aBBaAcc0ba000AAaBBabadac000BA0Aa0acdbB000CAA0A0cedaB00CFDCAaAcaABC00CEFC0c0ccBDB00CFDCAabbc0Ba000DCBA00c0aA0000DCBB0aa0aB0000A0ADC0cbbCc000cACBCB0cAAb000bcCDB00AAba0");
sw(102,"0aabfcabE0bfc00aaecCDFFFAdc00aabb0dBcCEab00aABdcCdbD0af000E0cc0BAbbaC000HACeBc0fb0C00FKGBabga0BFC00FBJLAdieCIGB00DEFKAEADC00b00aGaa0FHAFAbc000D0BCBaFGCaa00b0abADD0BaCg000kfchcbC0Cad000chccc0bAD0b0");
sw(103,"0bbciCcBaL0ebB0bbggbCMdCAccB0bbCc0AAbaj0000baBbg0f0aAm0000FBbA0CCaD0j000GBC00bacaci000BACbFaMCD0k000hEGHKBEDDBeA0cdBMHDAFEEaeA00KCFFEBGAC0eA00KEBb0bCGCbbA0aFAada0IAAdH00BcCefbedCgAC00Bb0aDBBjEJCa0");
sw(104,"0bbbfBdBaJcecA0bbdbbBIicbdcA0bbDCbBaBclaa00b0FAccfaccnB000FFC00b0aBCk000GGCAbcde0Bi000CcDDGBKAEGi000baAGNHDBaCaB0adbGHCAE0ECbB0aEADDbdAACBcAa0HEaeddcEDBcAaaGA0badD0AdIa0A0GaBBdeBlBD00AaCEIE0l0FBa0");
sw(105,"0aadhecCHGAeaA0aadedKGdddfaA0aabBaHECAia000acDagAaBeAfa000aDaeAaAdDAj000ADae0beba0j00bDfCBFGGDCFi00bB0aBLJCABDc00c0eBEEaAaHFb00cCaabbc0aDCcaabE0chacAEEDdaaaBbBeBbBcB0Ba0A0AaaEbAAh0a00A0BCDHBeBAab0");
sw(106,"000AicBEGLEac0000bj0IGa0ace000adfdCCbafac000c0ehAcBcDid000AAebBCDCHAj000CE0iAe0acai000CaF0FFKDbAi000dCBBKKCABBeA0b0AGEJBD0ECaA00H00BGCE0DAaA0AFadaCaDIDDaA0bBaBeFBEd0AB000bAfeDdb0eba00abbcBEChFAbc0");
sw(107,"00AAACACaPDD0A00AbdbcFfDFFAA000E00BDaCeFAA00AAcbBcA0BiC000Ba0D0aaBDbf0000cBAabCEBcf00aeAccabOLBBh00ae0caaBHIEBa00aeaacB0HGBa0000DebABCE00Aa00CD0ABCDB0CBa000ABBb0ABaABJA0ACGBaaAbDcECAAACDACeDgEGECA");
sw(108,"0bbdacacF0acbB0bbcCBACCE0aCB0baBGa0F0IDaBB0bACEABCbbb0a000CCDbacdeacF000ECAcBaa00DF00EHEdEdbaFHMG00EGDClkaeEHHH00FBbggCbacCDC00bdjjcBEi0Baaaa0fgb0C00bCbbaa0abFEEDdAACeA0Bd0GGDEGDDBbBBCGCF0cBEBBBCB");
sw(109,"0aaaBAB0G0CAa00aaaaBFGEFCAC00aaAACACbGab000a0ADDEEaebcd0000BacAAAeceC000FEBaCCCabDC00EIDBH0BACDIH00EHFFggccBCHI00GDAcd0BddDGF000ahje0DiaFCAaaAcfebbcB0GD0aaAadEacAeCBCha00e0DF0BACBaf000BbC0bBaAcec0");
sw(115,"000adf0BD0Cbb0000caAB0CFcfc0000eaBfabbBdb00000faCa0Ec0g0000ac0CH0BbcA000B0BaCBabccA00EJFDcaddA00B00ECJGBcffbGD000DIIJB0bd0abb00AFFEBCBADaaAAAADFEDBaDEa0BAA0cA0DCEbbcFdA00gfafdaAbGBc000dgbab0AHFbb0");
sw(116,"000afgbB0bAdbA000dd0DBBC0dbA000daAbb0c0ab0000AdbAeaAbAf0000aaaBHBBBbb000A0BACDabcdb00CCAFbDBaDaia00C0DCFFB0aCad00BGHKDcca00bc000JJIDabCA0aA000LJGGB0BF0AB000CBADaACbcCb00ABA0cccfcCB000AbABB0bbFG0b0");
sw(117,"0aabcb0Dcccb0A0aab0bAAab0a0A0aaA0aBeBdcAA00aaBaaddAbaBB000aBDBaBaACBd000bBBFeBcAAad00beeCaAA0AAhd00bbecGHDDadcd00ba0BDdb0A0aa00aCHEAfhCc0AAaaaGGCAcbcB0BAaa0EC0ahfCcaaDa0AGFCBbdeaaCD00A0GDFEa0CCA00");
sw(119,"0aaaaaB0Bbaaa00aaabcGBBbbba00aabbaGCBbbb000abbbcDDCbbba000aabbDCCbbba00000aaDCBbbaa0000aa0DCAcaa00000aabDBAcbb00000abaCBAca0000000bbCBAb00000000bbDBB00000000bbbDBCaaaa000bbbbDBCaaaa000aabbFBCAaaa0");
sw(120,"00ACAcCADCBAb000ABc0C0AAcAd0000gecCBBbFaaA00acceCAEEE00000bccACDCACB0000cdbdAAAa0Aa00bc0dhaaABBcc00bd0ad00a0Acea0c0BacFBGCcdea00Ba0CGJGBcdd0A0abBDJGEAdec0AaddfDLGG0cc0B00dfegECD00AAAA0caecHDEDDGBA");
sw(121,"0babjhAEAAehcB0bafcCA0AAafeB0b0bba0dBbbCa00bA0ceehbaEF0000abDEBB0GIBb000ecBBAdAGbbb00bfdAdbAFHcmg00bhddBEIEDBej00ecEB0AbCFagc00cEGFAAbJcdda00aGGCFHGBDabA00a0C0ba0Gb0AC00BG00bffcAADG00DFJaAABGHFHD0");
sw(122,"0bbcaA0BC00baA0bbc00FFCDDaCA0bbBCaA0ACcaA00bbA0aAB0ecab0000BAdCB0cbba000CFDECDA00Aa00BD0DIFCABBBC00BD0BADBAA0CD00C0aAAbAddDFC00ba0ceddgcFDBaa0CCccddaAHE0aaAC0Ccgbc0BAda0AACCEaacA00c00ABACCaba0bec0");
sw(123,"0aaaBAB0G0CAa00aaaaBFGEFCAC00aaAACACbGab000a0ADDEEaebcd0000BacAAAeceC000FEBaCCCabDC00EIDBH0BACDIH00EHFFggccBCHI00GDAcd0BddDGF000ahje0DiaFCAaaAcfebbcB0GD0aaAadEacAeCBCha00e0DF0BACBaf000BbC0bBaAcec0");
sw(129,"000afgbB0bAdbA000dd0DBBC0dbA000daAbb0c0ab0000AdbAeaAbAf0000aaaBHBBBbb000A0BACDabcdb00CCAFbDBaDaia00C0DCFFB0aCad00BGHKDcca00bc000JJIDabCA0aA000LJGGB0BF0AB000CBADaACbcCb00ABA0cccfcCB000AbABB0bbFG0b0");
sw(130,"000afgbB0bAdbA000dd0DBBC0dbA000daAbb0c0ab0000AdbAeaAbAf0000aaaBHBBBbb000A0BACDabcdb00CCAFbDBaDaia00C0DCFFB0aCad00BGHKDcca00bc000JJIDabCA0aA000LJGGB0BF0AB000CBADaACbcCb00ABA0cccfcCB000AbABB0bbFG0b0");
sw(131,"0000cca0aA0aa0000ae0a000bab0000de0aAA0aba000adbaAABD0ab000bd0BBECCBaa000bcBAC0DB0bb00abCAbAbBBadc00adCDC0aBBAbda0bAEFAA0CCadca0ACDDCDDFB0ab0A0ABBBBDFCaa00A0baaa0CEA000A00beefdbAAAba000abffc0ABAA00");
sw(132,"0000cca0aA0aa0000ae0a000bab0000de0aAA0aba000adbaAABD0ab000bd0BBECCBaa000bcBAC0DB0bb00abCAbAbBBadc00adCDC0aBBAbda0bAEFAA0CCadca0ACDDCDDFB0ab0A0ABBBBDFCaa00A0baaa0CEA000A00beefdbAAAba000abffc0ABAA00");
sw(133,"00ACAcCADCBAb000ABc0C0AAcAd0000gecCBBbFaaA00acceCAEEE00000bccACDCACB0000cdbdAAAa0Aa00bc0dhaaABBcc00bd0ad00a0Acea0c0BacFBGCcdea00Ba0CGJGBcdd0A0abBDJGEAdec0AaddfDLGG0cc0B00dfegECD00AAAA0caecHDEDDGBA");
sw(134,"00ACAcCADCBAb000ABc0C0AAcAd0000gecCBBbFaaA00acceCAEEE00000bccACDCACB0000cdbdAAAa0Aa00bc0dhaaABBcc00bd0ad00a0Acea0c0BacFBGCcdea00Ba0CGJGBcdd0A0abBDJGEAdec0AaddfDLGG0cc0B00dfegECD00AAAA0caecHDEDDGBA");
sw(135,"0000cD00bCaca0000df0aCBCAab0000AdcbAaEBba000aa0e0dBBCda000Cbc0aAAaCAa000C0BbAeBcAab00baFabBeCBBad00biDGCAdCGD0ea0dfBHBCAIFBbea0aCb0EEEDCD0ea000a0A0BGEDaca0bA0bfb0FCAdb000cAehff0Cada000aacdeaaA0A00");
sw(136,"0bcbb0CCA00aaA0bcccBDDDFBbAA0bb00AaaaCbaA00bcba0CAAcaac000aaABCDCaaca000BCFGECFCbaa00BBEEFFDDDAbB00BBDFCA0CDBBB00BBEEAcaaBCCB000CD0c0bbbGDB00AEE0AabBDIFB00ADBDafbACDCc00Ab0CBdbADBbc00A0a0B0AEFadc0");
sw(137,"0bcbbeBCB0C00B0bcbcBDCCEBaAB0bbbbC0aaae0B00bcbc0Ba0dc0d000db0BBGAbcgb000b0DEDFDCgeb00C0AECEGCDbg000CBBCBBAA00a000CEECaecf0AaA000FGBdcebdCAD00AIHDDBa0BFED00BEEEAeaAABHa00B0ACAdbbCDBa00BA0ABA0EJDbb0");
sw(143,"000afgbB0bAdbA000dd0DBBC0dbA000daAbb0c0ab0000AdbAeaAbAf0000aaaBHBBBbb000A0BACDabcdb00CCAFbDBaDaia00C0DCFFB0aCad00BGHKDcca00bc000JJIDabCA0aA000LJGGB0BF0AB000CBADaACbcCb00ABA0cccfcCB000AbABB0bbFG0b0");
sw(144,"000afgbB0bAdbA000dd0DBBC0dbA000daAbb0c0ab0000AdbAeaAbAf0000aaaBHBBBbb000A0BACDabcdb00CCAFbDBaDaia00C0DCFFB0aCad00BGHKDcca00bc000JJIDabCA0aA000LJGGB0BF0AB000CBADaACbcCb00ABA0cccfcCB000AbABB0bbFG0b0");
sw(145,"0000cca0aA0aa0000ae0a000bab0000de0aAA0aba000adbaAABD0ab000bd0BBECCBaa000bcBAC0DB0bb00abCAbAbBBadc00adCDC0aBBAbda0bAEFAA0CCadca0ACDDCDDFB0ab0A0ABBBBDFCaa00A0baaa0CEA000A00beefdbAAAba000abffc0ABAA00");
sw(146,"0babefAAc0efcA0baddC0Ab0cacA0bafcBAaBBC00A0babbaadaFCAA000aaDFACaCDA0000deB00dAAB0a00bdBagdgCFCdf00bgCBaccCEEaga0dbEAfB0IFchfa0aBBAAEGH0fdea0aaADFHHE0ebba0bdbcCBCF0bACA0A0cbedaCACCDAABDFcebADFGIEA");
sw(147,"00ACAcCADCBAb000ABc0C0AAcAd0000gecCBBbFaaA00acceCAEEE00000bccACDCACB0000cdbdAAAa0Aa00bc0dhaaABBcc00bd0ad00a0Acea0c0BacFBGCcdea00Ba0CGJGBcdd0A0abBDJGEAdec0AaddfDLGG0cc0B00dfegECD00AAAA0caecHDEDDGBA");
sw(148,"000BbDBBEB00aa000BeAFDD0aaca00abgf0BABDda000eccgBBFCDdc000aafdBDD0CBd000BC0e0aCcBAd00a0C00EBBbbAb00adAFCFABAa0b00bcaFDHDFC0Ab000BcdAGGCCEab00A0cc0CBGHEAb00bAbcdFDEAadd00ahehgCb00bed00bggfcC0b0bcd0");
sw(149,"0000cD00bCaca0000df0aCBCAab0000AdcbAaEBba000aa0e0dBBCda000Cbc0aAAaCAa000C0BbAeBcAab00baFabBeCBBad00biDGCAdCGD0ea0dfBHBCAIFBbea0aCb0EEEDCD0ea000a0A0BGEDaca0bA0bfb0FCAdb000cAehff0Cada000aacdeaaA0A00");
sw(150,"0bcbbeBCB0C00B0bcbcBDCCEBaAB0bbbbC0aaae0B00bcbc0Ba0dc0d000db0BBGAbcgb000b0DEDFDCgeb00C0AECEGCDbg000CBBCBBAA00a000CEECaecf0AaA000FGBdcebdCAD00AIHDDBa0BFED00BEEEAeaAABHa00B0ACAdbbCDBa00BA0ABA0EJDbb0");
sw(151,"0bcbbeBCB0C00B0bcbcBDCCEBaAB0bbbbC0aaae0B00bcbc0Ba0dc0d000db0BBGAbcgb000b0DEDFDCgeb00C0AECEGCDbg000CBBCBBAA00a000CEECaecf0AaA000FGBdcebdCAD00AIHDDBa0BFED00BEEEAeaAABHa00B0ACAdbbCDBa00BA0ABA0EJDbb0");
sw(157,"0abaAaCDabAC0A0ab0bADCBCDDCA0ab0baDbCAe0A00adcaaa00fbb0000fbAaAEA0Add000f0AGAFCD0be00cidADEFDH0jb00cchdBCDFBcdca0abbcbhaa0ABAa000BadhfaeDBCba0EDcabaaAEEAbaBDBBcjeAABAAa0AIFDCdcfDAA0000BHEC0aCE0ab0");
sw(158,"0bbb0cBDEcBA0B0bbbA0EBDDA0DB0bb0BBAaAbf0B00bcC0ABAbgcAc000cBBaBC0aafb000aDCHBFADbcb00BCaDGCF0D0eC00BG0caAB00baC00DEBaagbgbBCD00aAE0ehfggDEEaaAGH00acdaHGCaaCDCDaiefbBEba0BEDHFcadBDDb00BCCFFBaDFBcc0");
sw(159,"0aBAafedDabccB0aBaCbccb0gdaB0aBcD0a0abCc0B0aCEbCBaaCbBb000ABCAAabAa0B000Aaaccdfcb0B00CGAbahcaCFGB00CGDaegAdaDEA00CFCabBbAbbbb00cABA0ACcCgccaaaBDHIHC00dabaaabbALKDdedDaA0B0AGFEDBdBFCBBEDDGGCADCGFEB");
sw(160,"00ABBACCBAa0a000ABCCBCABaB00000a000aB0Ca0A00AA0aa00DAaB000A00a00aBA0A0000bdccaaAB0A0000adddcBCBa00000acdd0AA0a0000aaddA0CAcca00aacbAADAadcbaaabcADED0bcbbaabbbbEFBabcbA0000ABCEC000CBAA00BACDBAADDBA");
sw(161,"0BBCBDDCGBBC0b0BBCdAJEGB0D0b0B0cdeDECBDab00BcabfBDCDBbb000aahiBBAaAEc000AEcg0AaeCDc00aAbaBCAabaDa00abcA0DAaabAa00abeAAFECaAFb000bee0CFbCEBa000deecAb0BDBc00babbaFBcA0cd00bdaccHBAAacd00dfhc0HBccebd0");
sw(162,"0abbeaBBF0bca00abbf0HDDAaab00abbdcDECECc000ada0fBBFCDba0000BccBDBcCBb000ADAdB0AeBBd00c0D00FaacBCd00ceBGAFa0AAAdb0ddaFCHFFBBAdb0b0bbBGHBBE0db0aabbbCDGFE0db0aAabfCDGCAdd000edgiAbCBaed00accddC0BAbab0");
sw(163,"0ab0DgHDGiDC000abadCCeKNFEC00abceBhcfFHAA00a0daBFBBAaMd000ecdACIabelL000caAEFIGGgdF00AAGAabaiDglJ00ABFEenieACBBf0DEH0geBjBbdCf0ba0ec0EddCbDf00A0BGADFBGBCf0Cb0EckAfDADn000BeAcibaBLbi00aAadfgaKHdeb0");
sw(164,"0bbb0cBDEcBA0B0bbbA0EBDDA0DB0bb0BBAaAbf0B00bcC0ABAbgcAc000cBBaBC0aafb000aDCHBFADbcb00BCaDGCF0D0eC00BG0caAB00baC00DEBaagbgbBCD00aAE0ehfggDEEaaAGH00acdaHGCaaCDCDaiefbBEba0BEDHFcadBDDb00BCCFFBaDFBcc0");
sw(165,"0bccacaACGCB0B0bcbaaBEcBCABB0bbAAADB0amBB00bcab0Abbicga000daBB00bdbfh000c0CFAEACech000ccBECIJGA0f000BcdaCGDB0A000AAadbeaeaDDA00aBAbeffefDDB00AFEbbabecFD000CCCEbfdbaCEE00BCDFFaAcDdC000BCDDFBBbEB0a0");
sw(171,"0bbaFB0ba0CEA00bbCBaACBDDFD00bb00aA0BD0aC00bdba0BBB0abB000e000b00aefa000da0DaFEDBac00ceacA0aBCE0a00cacbddgBCBBAb0acehgfBaaAB0b00eehgcAccBB0b00dcccbbacBA0b0BabA0gdaCBAA000A0BAc0CCC0b000BDBaa0BB0000");
sw(172,"0c0aAdaAC00caC0c0aCACA0BAaBC0c0aFBAcBaaACA0c0B0Abbab0E0000cAEAAac00b0000d0CFACaEba000AaeACbCAFCb000ADdge0D00A0000AAageddecB0000daCagffdeb0AaaaDFDDDAddBBAaaA0ACEaabbAEA00CFDHIAAbaCGDAAFHHFFD0FEEDDA");
sw(173,"0bbcacACDa0caB0bbcBADECDB0BB0bb0FA0aBCA0BA0baBB0caaa00A000ADE0AacaAaA000ACCD0AbCA0A00ABbADAbaDE0A00ABaab0abBBAA00Aaba00aabCCA00ca0abccccBB0aaaBCAa0acaEAbaa0BBCAcbbAB0b00BBDED00BDDCAAABDDECBAEDCAAA");
sw(174,"00AADBCDDACC0A00A0DACDBDBCCA000BD0Ab0BAaAA000CCDbaaa0aA0000DEaabbAB000000C00d0aCCA00000baBbaBEEBB000BbbbcAACBCB00Bbcba0AAbBDC00bdbcddabcABAbb000AA0AabECbbb0AaCCbaeaB0aa0AFEGGCCACCCAAAACFFEBCBB00AA");
sw(175,"000ACADCGACA0A000AC0JECBBBBA000BEAGBBA0aAA000CBAABBcaaA0000DAcB00ca000000BbbAD00a00000AcbACCBADBA000CcdeACabABA00Aaed0DBaeCEB00cbccc0accAB0bbaAaBBEBaaECcbbaAACBEBaABAba0ADFEEIEDBBAAAAABCFEIDECaaAA");
sw(176,"0ddedlFCDdadcA0ddcaAKACBacbA0ddf0BIBDdbaA00ddbabDA0ebAc000b0ECDHaeaf0000daDEGIa0cc000Ca0AaGGABAea00CB0ceEBAa0da00CFCcfbebbAda000CHCdbcaf0aD000EHEAHAabAAD00ABDCCBBEaBIB00A0aFcBBDAFFA00ACDBbJDLMHBA0");
sw(177,"0dccagBAabadcB0dccACBA0B0baB0dbcABAbAab0BA0daaaACabcbCa000bcFECEaaafA000ceEGDECFdcA00CaBAa0DEGBe000CCCacaBBCDa000CFGcgdfdBBdA000EGBbbdad0AC00AFHHGFBaaBBE00ABCCDb0CBCIDA0BBAEBc0BDGGDAADFFA0BBJKIEDA");
sw(178,"0c0aAdaAC00caC0c0aCACA0BAaBC0c0aFBAcBaaACA0c0B0Abbab0E0000cAEAAac00b0000d0CFACaEba000AaeACbCAFCb000ADdge0D00A0000AAageddecB0000daCagffdeb0AaaaDFDDDAddBBAaaA0ACEaabbAEA00CFDHIAAbaCGDAAFHHFFD0FEEDDA");
sw(179,"0000aaBBAAbbaA000aAB00aAa00A0000C00a00CB0A00ACB0baaAABA000ACCA00aACCA0000A00abb0BBA0000bbbbcaBBa0000abbbb0bA0aa000aaaaB0CAbba00aaa0AACA0cbbaaaaaABDB00babaaaa0aCBA0aba000ABABABAA0ABBAAABDCBBABBCDBA");
sw(185,"0a0abC00aaedaB0a0bABADa0a0AB0a0BA0AaAEEABB0aADCcb0ACDBD000CCAbAbaaEEA000CBabcecaDCA00aA0babe0CEC000abaB0A00CBA000becaaEAEC0aa00bbedACDAAacdaabcebaAAB0bdcaab0dd0CBBbbfAA0B0AaBB0aAaBCBBCBDAB0a0aDFCB");
sw(186,"0cbbBEbb00bAbC0cbAEBCEaDEFCC0cbDDABACHEADC0caAAabCECa0F000ACAA0bad00C000AaaG0ABBDA000daAgabiAGJCA00dacaegeACEEAc0cfgecACE0BCac0cfiibCFbcACedacegfcbCCdA0fda0bdcc0ABBAc0B0CBCBA0ACCCA0CCDCFCAaAFBCDDC");
sw(187,"0bbcacACDa0caB0bbcBADECDB0BB0bb0FA0aBCA0BA0baBB0caaa00A000ADE0AacaAaA000ACCD0AbCA0A00ABbADAbaDE0A00ABaab0abBBAA00Aaba00aabCCA00ca0abccccBB0aaaBCAa0acaEAbaa0BBCAcbbAB0b00BBDED00BDDCAAABDDECBAEDCAAA");
sw(188,"000ACeDCGaDB00000ACbKBEBABB0000cDDHCFcaa0000aCABCB0bbAb000cCCaBB00cca000dA0ACH0Baca00AAc0BCE0ABc000AEbheBBbcab000BDaeca0df0B000baCAdcbdebBBaa0BEEEHBedBD0aa0bBDGDadc0Faa00DCHFGDCaED0000BBFDJAEEB000");
sw(189,"000ACeDCGaDB00000ACbKBEBABB0000cDDHCFcaa0000aCABCB0bbAb000cCCaBB00cca000dA0ACH0Baca00AAc0BCE0ABc000AEbheBBbcab000BDaeca0df0B000baCAdcbdebBBaa0BEEEHBedBD0aa0bBDGDadc0Faa00DCHFGDCaED0000BBFDJAEEB000");
sw(190,"0ddedlFCDdadcA0ddcaAKACBacbA0ddf0BIBDdbaA00ddbabDA0ebAc000b0ECDHaeaf0000daDEGIa0cc000Ca0AaGGABAea00CB0ceEBAa0da00CFCcfbebbAda000CHCdbcaf0aD000EHEAHAabAAD00ABDCCBBEaBIB00A0aFcBBDAFFA00ACDBbJDLMHBA0");
sw(191,"0ddedlFCDdadcA0ddcaAKACBacbA0ddf0BIBDdbaA00ddbabDA0ebAc000b0ECDHaeaf0000daDEGIa0cc000Ca0AaGGABAea00CB0ceEBAa0da00CFCcfbebbAda000CHCdbcaf0aD000EHEAHAabAAD00ABDCCBBEaBIB00A0aFcBBDAFFA00ACDBbJDLMHBA0");
sw(192,"0000aaBBAAbbaA000aAB00aAa00A0000C00a00CB0A00ACB0baaAABA000ACCA00aACCA0000A00abb0BBA0000bbbbcaBBa0000abbbb0bA0aa000aaaaB0CAbba00aaa0AACA0cbbaaaaaABDB00babaaaa0aCBA0aba000ABABABAA0ABBAAABDCBBABBCDBA");
sw(193,"0000aaBBAAbbaA000aAB00aAa00A0000C00a00CB0A00ACB0baaAABA000ACCA00aACCA0000A00abb0BBA0000bbbbcaBBa0000abbbb0bA0aa000aaaaB0CAbba00aaa0AACA0cbbaaaaaABDB00babaaaa0aCBA0aba000ABABABAA0ABBAAABDCBBABBCDBA");
}

void recognizer::teach()
{
  const int CYCLES = 20;
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

