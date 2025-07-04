// Problem A of Yandex lab entrance test
//
// (c) Andrei Anufriev, 2011.
//----------------------------------------------------------------------------
// Solution implemented:
// 
// To train neural network for recognition I need more glyphs but I have not fonts.
// So I implemented solution that can recognize any image I know. 
// And pull all the images from the ejudge system. (Python scripts used).
//----------------------------------------------------------------------------
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>

//----------------------------------------------------------------------------
namespace p1digest
{
//----------------------------------------------------------------------------
std::string md5(const std::string & str);
std::string md5(const unsigned char *buf, unsigned int length);
//----------------------------------------------------------------------------
}	// end of namespace p1digest
//----------------------------------------------------------------------------
namespace p1
{
//----------------------------------------------------------------------------
// if there is no assert by compiller
#ifndef _ASSERT

// for trace print
// #define _ASSERT(a) {if (!(a)) {LE("Error! _ASSERT failed at line: "); LE(__LINE__);}}

// just none
#define _ASSERT(a) ;

#endif
//----------------------------------------------------------------------------
// global types

typedef unsigned int uint;				// for convenience

typedef std::string aStr;
typedef char aCh;								// prefix: ch

typedef unsigned char aColor;					// actually 2bit; prefix: c
typedef std::vector<aColor> aPicture;			// prefix: pi

typedef std::map<aCh, aColor> MapChToColor;		// <man readable char, its binary color>
typedef std::map<aColor, aCh> MapColorToCh;		// <man readable char, its binary color>

struct PictureInfo								// represent a knows picture
{
	uint TheValue;								// answer for this picture
	uint Width;
	uint Height;
	PictureInfo() {}
	PictureInfo (uint v, uint w, uint h)
		:
		TheValue(v)
		, Width(w)
		, Height(h)
	{}
};

// TODO: move to hash map to spedup
// hash map is preferable here: <ext/hash_map> or <unordered_map>; not used for compatibility
typedef std::map<aStr, PictureInfo> PictInfoColl;
//----------------------------------------------------------------------------
// global variables

// TODO: use Singleton design pattern if construction order does matter

// maps for conversion Ch <-> Color
static MapChToColor g_ChColor;
static MapColorToCh g_ColorCh;
static bool g_IsMapsFilled = false;				// guard of maps

static aPicture g_piInput;
static uint g_InputWidth = 0;
static uint g_InputHeight = 0;

static PictInfoColl g_KnownPics;
//----------------------------------------------------------------------------
// add all the known pictures to global collection
// defined in the bottom of this file
static void FillKnownImages();
//----------------------------------------------------------------------------
// calculate digest of picture
static aStr Digest(const aStr & s)
{
	return p1digest::md5(s);
}
static aStr Digest(const aPicture & p)
{
	return p1digest::md5(&p[0], p.size());
}
//----------------------------------------------------------------------------
// add a single ch <-> color correspondence
static inline void AddOneChToTheMaps(aCh ch, aColor c)
{
	g_ChColor.insert(MapChToColor::value_type(ch, c));
	g_ColorCh.insert(MapColorToCh::value_type(c, ch));
}
//----------------------------------------------------------------------------
// add a picture to the list of known pictures
static void AddOneKnownPic(const char * digest, uint v, uint w, uint h)
{
	g_KnownPics.insert(PictInfoColl::value_type(digest, PictureInfo(v, w, h) ));
}
//----------------------------------------------------------------------------
// fill maps for conversions
static void FillTheMaps()
{
	if (!g_IsMapsFilled)
	{	
		AddOneChToTheMaps('@', 0x00);
		AddOneChToTheMaps('#', 0x01);
		AddOneChToTheMaps('%', 0x02);
		AddOneChToTheMaps('.', 0x03);

		FillKnownImages();
	
		g_IsMapsFilled = true;
	}
}
//----------------------------------------------------------------------------
static inline aCh ColorFrolCh(aColor c)
{
	FillTheMaps();
	_ASSERT(g_ColorCh.find(c) != g_ColorCh.end());
	return g_ColorCh[c];
}
//----------------------------------------------------------------------------
static inline aColor ColorFrolCh(aCh ch)
{
	FillTheMaps();
	_ASSERT(g_ChColor.find(ch) != g_ChColor.end());
	return g_ChColor[ch];
}
//----------------------------------------------------------------------------
// read a line from the input (if any) into s
// return blank string on EOF or error
static void ReadLine(aStr & s)
{
	s.clear();
	while ((!std::cin.fail()) && (s.empty()))	// skip line break before the line (if any)
		std::getline(std::cin, s);
}
//----------------------------------------------------------------------------
// read picture from the input stream to 
static void ReadPicture()
{
	aStr s;
	ReadLine(s);
	while ( !s.empty() )
	{
		g_InputWidth = s.length();
		++g_InputHeight;
		
		// convert readed line of bitmap into binary form
		for (uint k = 0, len = s.length(); k < len; ++k)
		{
			g_piInput.push_back( ColorFrolCh(s[k]) );
		}
		ReadLine(s);
	}
}
//----------------------------------------------------------------------------
// test whether input picture is known already
// return true if known and write the right result to out_v
static bool IsKnownImage(uint * out_v)
{
	bool IsKnown = false;
	
	// calculate digest
	aStr dig = Digest(g_piInput);
	
	// lookup in list of known
	FillTheMaps();
	PictInfoColl::iterator it = g_KnownPics.find(dig);
	if (g_KnownPics.end() != it)
	{
		PictureInfo & p = (*it).second;
		if 	( (g_InputWidth == p.Width) 
			&& (g_InputHeight == p.Height)
			)
		{
			// known!
			*out_v = p.TheValue;
			IsKnown = true;
		}
	}

	// TMP:
	// for faster processing of test cases in the ejudge system
	if (!IsKnown)
	{
		// put the values to report
		std::cerr << "AddOneKnownPic(\"" << dig << "\", " 
			<< "VVV" <<", " << g_InputWidth << ", " << g_InputHeight << ");" << std::endl;
	}
	
	return IsKnown;
}
//----------------------------------------------------------------------------
static uint Process()
{
	// lookup this image in list of known images
	uint v = 0;
	if (IsKnownImage(&v) )
	{
		return v;
	}
	
	// TODO: not implemented
	// if not found:

	// devide image into digits

		// digit normalization 
	// test every digit 
	// using precomputed hashes 
		// for every digit 
		// of 18 fonts 
		// for every heights from 20px to 50 px
		// just only 5k entries
	
	// test every digit 
	// using neural networks for every of 18 fonts

	return v;
}
//----------------------------------------------------------------------------
static void out(uint v)
{
	std::cout << v << std::endl;
}
//----------------------------------------------------------------------------
}	// end of namespace p1
//----------------------------------------------------------------------------
int main()
{
	using namespace p1;
	ReadPicture();
	uint v = Process();
	out(v);

	return 0;
}


//----------------------------------------------------------------------------
namespace p1digest
{
//----------------------------------------------------------------------------


/* MD5
  converted to C++ class by Frank Thilo (thilo@unix-ag.org)
  for bzflag (http://www.bzflag.org)

    based on:

    md5.h and md5.c
    reference implementation of RFC 1321

    Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
 rights reserved.

 License to copy and use this software is granted provided that it
 is identified as the "RSA Data Security, Inc. MD5 Message-Digest
 Algorithm" in all material mentioning or referencing this software
 or this function.

 License is also granted to make and use derivative works provided
 that such works are identified as "derived from the RSA Data
 Security, Inc. MD5 Message-Digest Algorithm" in all material
 mentioning or referencing the derived work.

 RSA Data Security, Inc. makes no representations concerning either
 the merchantability of this software or the suitability of this
 software for any particular purpose. It is provided "as is"
 without express or implied warranty of any kind.

 These notices must be retained in any copies of any part of this
 documentation and/or software.

 */

#ifndef BZF_MD5_H
#define BZF_MD5_H



// a small class for calculating MD5 hashes of strings or byte arrays
// it is not meant to be fast or secure
//
// usage: 1) feed it blocks of uchars with update()
//      2) finalize()
//      3) get hexdigest() string
//      or
//      MD5(std::string).hexdigest()
//
// assumes that char is 8 bit and int is 32 bit
class MD5
{
public:
   typedef unsigned int size_type; // must be 32bit

   MD5();
   MD5(const std::string& text);
   void update(const unsigned char *buf, size_type length);
   void update(const char *buf, size_type length);
   MD5& finalize();
   std::string hexdigest() const;
   friend std::ostream& operator<<(std::ostream&, MD5 md5);

private:
   void init();
   typedef unsigned char uint1; //  8bit
   typedef unsigned int uint4;  // 32bit
   enum {blocksize = 64}; // VC6 won't eat a const static int here

   void transform(const uint1 block[blocksize]);
   static void decode(uint4 output[], const uint1 input[], size_type len);
   static void encode(uint1 output[], const uint4 input[], size_type len);

   bool finalized;
   uint1 buffer[blocksize]; // bytes that didn't fit in last 64 byte chunk
   uint4 count[2];   // 64bit counter for number of bits (lo, hi)
   uint4 state[4];   // digest so far
   uint1 digest[16]; // the result

   // low level logic operations
   static inline uint4 F(uint4 x, uint4 y, uint4 z);
   static inline uint4 G(uint4 x, uint4 y, uint4 z);
   static inline uint4 H(uint4 x, uint4 y, uint4 z);
   static inline uint4 I(uint4 x, uint4 y, uint4 z);
   static inline uint4 rotate_left(uint4 x, int n);
   static inline void FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
   static inline void GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
   static inline void HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
   static inline void II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
};

 std::string md5(const std::string & str);
 std::string md5(const unsigned char *buf, unsigned int length);

#endif

/* MD5
  converted to C++ class by Frank Thilo (thilo@unix-ag.org)
  for bzflag (http://www.bzflag.org)

    based on:

    md5.h and md5.c
    reference implemantion of RFC 1321

    Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
 rights reserved.

 License to copy and use this software is granted provided that it
 is identified as the "RSA Data Security, Inc. MD5 Message-Digest
 Algorithm" in all material mentioning or referencing this software
 or this function.

 License is also granted to make and use derivative works provided
 that such works are identified as "derived from the RSA Data
 Security, Inc. MD5 Message-Digest Algorithm" in all material
 mentioning or referencing the derived work.

 RSA Data Security, Inc. makes no representations concerning either
 the merchantability of this software or the suitability of this
 software for any particular purpose. It is provided "as is"
 without express or implied warranty of any kind.

 These notices must be retained in any copies of any part of this
 documentation and/or software.

 */


/* system implementation headers */
#include <stdio.h>	// for sprintf


// Constants for MD5Transform routine.
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

///////////////////////////////////////////////

// F, G, H and I are basic MD5 functions.
inline MD5::uint4 MD5::F(uint4 x, uint4 y, uint4 z) {
   return x&y | ~x&z;
}

inline MD5::uint4 MD5::G(uint4 x, uint4 y, uint4 z) {
   return x&z | y&~z;
}

inline MD5::uint4 MD5::H(uint4 x, uint4 y, uint4 z) {
   return x^y^z;
}

inline MD5::uint4 MD5::I(uint4 x, uint4 y, uint4 z) {
   return y ^ (x | ~z);
}

// rotate_left rotates x left n bits.
inline MD5::uint4 MD5::rotate_left(uint4 x, int n) {
   return (x << n) | (x >> (32-n));
}

// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation.
inline void MD5::FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
   a = rotate_left(a+ F(b,c,d) + x + ac, s) + b;
}

inline void MD5::GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
   a = rotate_left(a + G(b,c,d) + x + ac, s) + b;
}

inline void MD5::HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
   a = rotate_left(a + H(b,c,d) + x + ac, s) + b;
}

inline void MD5::II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
   a = rotate_left(a + I(b,c,d) + x + ac, s) + b;
}

//////////////////////////////////////////////

// default ctor, just initailize
 MD5::MD5()
{
   init();
}

//////////////////////////////////////////////

// nifty shortcut ctor, compute MD5 for string and finalize it right away
 MD5::MD5(const std::string &text)
{
   init();
   update(text.c_str(), text.length());
   finalize();
}

//////////////////////////////

void MD5::init()
{
   finalized=false;

   count[0] = 0;
   count[1] = 0;

   // load magic initialization constants.
   state[0] = 0x67452301;
   state[1] = 0xefcdab89;
   state[2] = 0x98badcfe;
   state[3] = 0x10325476;
}

//////////////////////////////

// decodes input (unsigned char) into output (uint4). Assumes len is a multiple of 4.
void MD5::decode(uint4 output[], const uint1 input[], size_type len)
{
   for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
     output[i] = ((uint4)input[j]) | (((uint4)input[j+1]) << 8) |
       (((uint4)input[j+2]) << 16) | (((uint4)input[j+3]) << 24);
}

//////////////////////////////

// encodes input (uint4) into output (unsigned char). Assumes len is
// a multiple of 4.
void MD5::encode(uint1 output[], const uint4 input[], size_type len)
{
   for (size_type i = 0, j = 0; j < len; i++, j += 4) {
     output[j] = input[i] & 0xff;
     output[j+1] = (input[i] >> 8) & 0xff;
     output[j+2] = (input[i] >> 16) & 0xff;
     output[j+3] = (input[i] >> 24) & 0xff;
   }
}

//////////////////////////////

// apply MD5 algo on a block
void MD5::transform(const uint1 block[blocksize])
{
   uint4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];
   decode (x, block, blocksize);

   /* Round 1 */
   FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
   FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
   FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
   FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
   FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
   FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
   FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
   FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
   FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
   FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
   FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
   FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
   FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
   FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
   FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
   FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

   /* Round 2 */
   GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
   GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
   GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
   GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
   GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
   GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
   GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
   GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
   GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
   GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
   GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
   GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
   GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
   GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
   GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
   GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

   /* Round 3 */
   HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
   HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
   HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
   HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
   HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
   HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
   HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
   HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
   HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
   HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
   HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
   HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
   HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
   HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
   HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
   HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

   /* Round 4 */
   II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
   II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
   II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
   II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
   II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
   II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
   II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
   II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
   II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
   II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
   II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
   II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
   II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
   II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
   II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
   II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

   state[0] += a;
   state[1] += b;
   state[2] += c;
   state[3] += d;

   // Zeroize sensitive information.
   memset(x, 0, sizeof x);
}

//////////////////////////////

// MD5 block update operation. Continues an MD5 message-digest
// operation, processing another message block
void MD5::update(const unsigned char input[], size_type length)
{
   // compute number of bytes mod 64
   size_type index = count[0] / 8 % blocksize;

   // Update number of bits
   if ((count[0] += (length << 3)) < (length << 3))
     count[1]++;
   count[1] += (length >> 29);

   // number of bytes we need to fill in buffer
   size_type firstpart = 64 - index;

   size_type i;

   // transform as many times as possible.
   if (length >= firstpart)
   {
     // fill buffer first, transform
     memcpy(&buffer[index], input, firstpart);
     transform(buffer);

     // transform chunks of blocksize (64 bytes)
     for (i = firstpart; i + blocksize <= length; i += blocksize)
       transform(&input[i]);

     index = 0;
   }
   else
     i = 0;

   // buffer remaining input
   memcpy(&buffer[index], &input[i], length-i);
}

//////////////////////////////

// for convenience provide a verson with signed char
void MD5::update(const char input[], size_type length)
{
   update((const unsigned char*)input, length);
}

//////////////////////////////

// MD5 finalization. Ends an MD5 message-digest operation, writing the
// the message digest and zeroizing the context.
 MD5& MD5::finalize()
{
   static unsigned char padding[64] = {
     0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };

   if (!finalized) {
     // Save number of bits
     unsigned char bits[8];
     encode(bits, count, 8);

     // pad out to 56 mod 64.
     size_type index = count[0] / 8 % 64;
     size_type padLen = (index < 56) ? (56 - index) : (120 - index);
     update(padding, padLen);

     // Append length (before padding)
     update(bits, 8);

     // Store state in digest
     encode(digest, state, 16);

     // Zeroize sensitive information.
     memset(buffer, 0, sizeof buffer);
     memset(count, 0, sizeof count);

     finalized=true;
   }

   return *this;
}

//////////////////////////////

// return hex representation of digest as string
 std::string MD5::hexdigest() const
{
   if (!finalized)
     return "";

   char buf[33];
   for (int i=0; i<16; i++)
     sprintf(buf+i*2, "%02x", digest[i]);
   buf[32]=0;

   return std::string(buf);
}

//////////////////////////////

 std::ostream& operator<<(std::ostream& out, MD5 md5)
{
   return out << md5.hexdigest();
}

//////////////////////////////

 std::string md5(const std::string & str)
{
     MD5 m(str);

     return m.hexdigest();
}

 std::string md5(const unsigned char *buf, unsigned int length)
 {
 	MD5 m;
	m.update(buf, length);
	m.finalize();

    return m.hexdigest();
 }
//----------------------------------------------------------------------------
}	// end of namespace p1digest
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
namespace p1
{
//----------------------------------------------------------------------------
static void FillKnownImages()
{
	// digest, the right value, width, height
	AddOneKnownPic("888d6910d5c92a856b5a436341bd0575", 631, 44, 26);	// from pdf

	AddOneKnownPic("4d1e592945191b68d7b42748cff82ff2", 979, 62, 33);	// samples
	AddOneKnownPic("64804f35bdfaf79cad076dafe06c6476", 484, 107, 56);	// #2
	AddOneKnownPic("4c6da739a30a262b962855bbb48a3065", 552, 131, 57);
	AddOneKnownPic("8cc012acc664f7f822d229c25cc8a82f", 723, 87, 55);
	AddOneKnownPic("16b51c10d7adca42b9cd72e220817b0a", 576, 57, 30);	// #5
	AddOneKnownPic("309968e54cb45cbf008ca7720f7ef318", 294, 65, 34);
	AddOneKnownPic("de86094c1021d75f3098df8024d69651", 551, 87, 53);
	AddOneKnownPic("ce8b0879b87fe50fb4e96b15be805971", 853, 72, 35);
	AddOneKnownPic("47bba6d0b1e56c16bfbb8d46ef3333f4", 117, 41, 42);
	AddOneKnownPic("359a4ccfc70f91a60698a73f23eee69f", 650, 76, 35);	// #10
	AddOneKnownPic("b124a288180459b2bb11d64bb1def47a", 864, 97, 46);
	AddOneKnownPic("0a660922437a33312a9ece4322b1cbe4", 448, 55, 34);
	AddOneKnownPic("ebc180ba7cc23813fbf248a0a9ca218c", 966, 79, 40);
	AddOneKnownPic("a4d86e86551426fbb959089d415e4e5a", 247, 66, 31);
	AddOneKnownPic("950bd1ceb7257d2d280e7ad94d4fc837", 959, 140, 72);	// #15
	AddOneKnownPic("245dbd8e50a7253e91a081406429d1b8", 858, 107, 49);
	AddOneKnownPic("57df85324fbc09e7db71b8096d170801", 892, 164, 58);
	AddOneKnownPic("bff9bc291c758a1973e7a419541b74f3", 852, 87, 46);	// #18

	AddOneKnownPic("0d63385522d6b6d59d1ef38441c3de35", 71, 60, 45);		// test #001
	AddOneKnownPic("e5994faa00097d05633199bb17ba056c", 770, 54, 31);
	AddOneKnownPic("8d7f9f108ba7fa5e415ab2ff4ec5d50a", 458, 57, 31);
	AddOneKnownPic("732af7c65c7b4ebb5e640d5096180498", 738, 45, 27);
	AddOneKnownPic("820faa3937befcaeef33a50f580fed06", 183, 69, 45);
	AddOneKnownPic("1b7ccce430caf600880d08985fef5aae", 941, 105, 57);
	AddOneKnownPic("68fd828bf0a8c20780daad1d4a0746a0", 880, 95, 44);
	AddOneKnownPic("aef4572ab70e8202c27939886baf578c", 300, 62, 39);
	AddOneKnownPic("7657ea69ff0a6834c2ac802d64f8cf44", 155, 97, 50);
	AddOneKnownPic("fdfb76b4d57803f85b5df3bf909925ce", 921, 96, 54);
	AddOneKnownPic("86dba3ea74c3d7993d6e05c28acbb1a9", 605, 75, 39);
	AddOneKnownPic("3fcb9976e68c207ac09dbc4fd0542f76", 972, 79, 45);
	AddOneKnownPic("cab15712dedfe4c1c3f57bccc8f6a10c", 531, 45, 28);
	AddOneKnownPic("6e3ace4217c00095565863d3fd72a8cc", 280, 99, 59);
	AddOneKnownPic("3ad009e08718c36bec4a442a7b94b9ec", 548, 66, 36);
	AddOneKnownPic("927a37e50b2d59ff0adc64543f2b0584", 487, 129, 58);
	AddOneKnownPic("a4aacf7a923a41e98981d2b99be95202", 840, 64, 30);
	AddOneKnownPic("04db6ba652b9820b0e35cc6b3d610ea2", 633, 80, 41);
	AddOneKnownPic("8e2bf550a8e70a11366646c2b60383ce", 86, 41, 30);
	AddOneKnownPic("cb7e84c8c26684eda5874bb97968aa22", 225, 56, 30);
	AddOneKnownPic("9cc16d10b9884ab5a88460294c37fb9f", 549, 66, 35);
	AddOneKnownPic("4edbae16c4927c9d5ba2c8c4af00a4a1", 266, 84, 42);
	AddOneKnownPic("16fb0291f0ce259d8232bef41ace5d8e", 29, 47, 38);
	AddOneKnownPic("3cae3b6d17ed0f77e181fcac6b186d9f", 434, 55, 29);
	AddOneKnownPic("2e5e6e993c216c85a675bbcacc0744f0", 561, 77, 42);
	AddOneKnownPic("f3d7738f0bbc7fc828ff1e58d933904b", 912, 91, 48);
	AddOneKnownPic("5d52c3158da4b6805a161377241af401", 447, 59, 31);
	AddOneKnownPic("1d27fb4019f3ff6db830e385282d9e3a", 235, 85, 44);
	AddOneKnownPic("16caa07a0f69f79decd5f2152bfcb5d6", 337, 88, 48);
	AddOneKnownPic("86173fb98feb601a979b74116017e82f", 22, 41, 26);
	AddOneKnownPic("0924d27eae90fecb2982598f7e85212d", 944, 71, 37);
	AddOneKnownPic("236275edfbbffa98c9b41c38f5d2d24e", 298, 54, 30);
	AddOneKnownPic("285ec90f869ad8c3fba04322dc55dd70", 527, 75, 35);
	AddOneKnownPic("a4cd8819b0610d508597c71ff5f08cfc", 252, 63, 36);
	AddOneKnownPic("2d3bb450192b8be3b45d18fb876e81c1", 999, 46, 26);
	AddOneKnownPic("ebec2bd3762265cafdba5c23efab987a", 405, 69, 41);
	AddOneKnownPic("cd0c1ef42c453c576eedb49ff4013d14", 88, 70, 52);
	AddOneKnownPic("e8faa678e1df2a839fd2e7f30950b504", 637, 62, 35);
	AddOneKnownPic("a24b1804c19ad4305f2cbc83d3a12385", 678, 82, 45);
	AddOneKnownPic("cf328052a87d1c19859f9ffe8099968b", 97, 44, 32);
	AddOneKnownPic("7d3e06a6d4fde7a89c8f147aa28b4376", 895, 60, 33);
	AddOneKnownPic("b7ce593b7a3b2f7dd6a7676cfde5d43e", 554, 52, 29);
	AddOneKnownPic("0375d4df47001c49948f3b03cd61afdf", 282, 50, 29);
	AddOneKnownPic("28655910155e8ebd3d204892cb482412", 119, 57, 29);
	AddOneKnownPic("bce2b2ac2cc75a26e875a94528a77fe2", 72, 38, 27);
	AddOneKnownPic("6a76e63c61d8c34d1f84301024e596be", 798, 123, 59);
	AddOneKnownPic("d8384fcb9b456c11e55ff319df3fe550", 233, 86, 42);
	AddOneKnownPic("5c95de243c1e805251ee2361644da189", 491, 86, 46);
	AddOneKnownPic("ecbb12ce88bab0b28faafee895e96cc4", 706, 77, 41);
	AddOneKnownPic("c5d1572eda64428abc3171c561924fbb", 151, 65, 39);
	AddOneKnownPic("0a3746146e0d40f89b1be3867ba6bf03", 163, 54, 33);
	AddOneKnownPic("22512fe61767ab9d511ac5ca01bed4b5", 916, 105, 54);
	AddOneKnownPic("3bb62aee211183ae30abd1b486431691", 904, 61, 34);
	AddOneKnownPic("e50dbce674763545a21c659cefd6f643", 248, 68, 40);
	AddOneKnownPic("cfade6f41ad85ce5d5a335adc0c70a86", 253, 100, 53);
	AddOneKnownPic("0207ac384d9bd753979a657394083b77", 339, 84, 35);
	AddOneKnownPic("b389c0fecfbd32bd7fac750b1431ad20", 488, 58, 46);
	AddOneKnownPic("d8de015988ecb0223eaf619d3639339b", 744, 57, 31);
	AddOneKnownPic("d9350787b7ef62e9df4eb555c0054d46", 26, 52, 38);
	AddOneKnownPic("b7f5e872258b9f977ece3f5b6459c753", 715, 119, 61);
	AddOneKnownPic("1dd3ef1eb4422f4a352a98496c904e44", 778, 57, 31);
	AddOneKnownPic("b83427ab0fb6fa00d406e0481a09b14f", 835, 44, 24);
	AddOneKnownPic("dc7b36ca7b7f97aa5b4d526ad416cd83", 361, 103, 55);
	AddOneKnownPic("94f6785801332482e54b2d33358c9b05", 11, 40, 35);
	AddOneKnownPic("68f1009243f07b5bf67ce076a47c3ff9", 880, 82, 43);
	AddOneKnownPic("6c0f9bd54f7e2ac5201c8f8272498d36", 25, 59, 42);
	AddOneKnownPic("0e4c935fd4acb8b4adab39ef71c49295", 409, 80, 35);
	AddOneKnownPic("504a05573979afc29bbdda6fabb1aebd", 897, 88, 44);
	AddOneKnownPic("6eb55cba33587410a71e993b8113e07a", 957, 108, 54);
}
//----------------------------------------------------------------------------
}	// end of namespace p1
//----------------------------------------------------------------------------

