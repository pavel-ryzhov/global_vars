#include <stdio.h>
#include <string.h>
#include <vector>
#include <list>
#include <queue>

#define REF_W 20 // ������ ������� ��������
#define REF_H 30 // ������ ������� ��������
#define REF_N 10 // ����� ��������� ��������
#define NDIGITS 3 // ����� ��������, ���������� ������������

using namespace std;

extern char fntData[]; // ������ �������

// ������������� �������
// c - ������
// return - �������� �������
int decodeNumber(char c)
{
    const char dc = '0'-'Z'+'a'-1;

    if(c <= 'Z') return c - '0';

    return c - dc;
}

// ����������� �� char � float
float ascii2val(char c)
{
	return c == '.' ? 0 : 1.f;
}

// ����������� �� float � char
char float2ascii(float x)
{
	return (x < 0.5f) ? '.' : '@';
}

// ��������� �����
class CPoint
{
public:
	//����������� �� ���������
	CPoint()
	{
		x = 0;
		y = 0;
	}
	//�����������
	// x0, y0 - ���������� �����
	CPoint(int x0, int y0)
	{
		x = x0;
		y = y0;
	}
	// �������� ���������
	bool operator==(const CPoint& pt)
	{
		return x == pt.x && y == pt.y;
	}
	// �������� ���������
	bool operator!=(const CPoint& pt)
	{
		return x != pt.x || y != pt.y;
	}
	int x, y; // ���������� �����
};
// �������� �������� ��������� �����
CPoint operator+(const CPoint& pt1, const CPoint& pt2)
{
	return CPoint(pt1.x+pt2.x, pt1.y+pt2.y);
}

// �������� ��������
class CInterval
{
public:
	//����������� �� ���������
	CInterval()
	{
		x1 = 0;
		x2 = 0;
	}
	//�����������
	// X1, X2 - ��������� � �������� ��������
	CInterval(int X1, int X2)
	{
		x1 = X1;
		x2 = X2;
	}

	int x1, x2; // ��������� � �������� �������� ���������
};

// ����� ����������� (������ ������� ������� �����������)
class CFrame
{
public:
	//����������� �� ���������
	CFrame()
	{
		resetFrameSize(0, 0);
	}
	//�����������
	// w, h - ������ � ������ �����
	CFrame(int w, int h)
	{
		resetFrameSize(w, h);
	}
	//�����������
	// x, y - ���������� �������� ������ ���� �����
	// w, h - ������ � ������ �����
	CFrame(int x, int y, int w, int h)
	{
		x1 = x;
		y1 = y;
		x2 = x+w-1;
		y2 = y+h-1;
	}

	int frameWidth(){return x2-x1+1;} // ������ �����

	int frameHeight(){return y2-y1+1;} // ������ �����

protected:
	// ����� ���������� �����
	// w, h - ����� ������ � ������ �����
	void resetFrameSize(int w, int h)
	{
		x1 = 0;
		y1 = 0;
		x2 = w-1;
		y2 = h-1;
	}

public:
	int x1, x2, y1, y2; // ���������� ������� ����� � ������ ������� ����� �����
};

// ���������� ��������
class AsciiImage : public CFrame
{
public:
	// �����������
	// buf - ������ ��������
	// w, h - ������ � ������ ��������
	AsciiImage(char* buf, int w = REF_W, int h = REF_H) : CFrame(w, h)
	{
		m_data = buf;
		m_width = w;
		m_height = h;
	}
	// ����������� �� ���������
	AsciiImage()
	{
		m_data = 0;
		m_width = 0;
		m_height = 0;
	}

	// ������ ��������
	char* data(){return m_data;}

	// ������ ������
	int width(){return m_width;}

	// ������ ������
	int height(){return m_height;}

	// ������ ����� 
	int size(){return m_width*m_height;}

	// ����� �����
	void resetFrame()
	{
		resetFrameSize(m_width, m_height);
	}

	// ��������� �����
	void setFrame(CFrame& f)
	{
		x1 = f.x1;
		y1 = f.y1;
		x2 = f.x2;
		y2 = f.y2;
	}

	// ��������� �������� �����
	// � - ������� (x)
	// r - ��� (y)
	// val - ���� �����
	void setPix(int c, int r, char val)
	{
		if(c >= 0 && c < m_width && r >= 0 && r < m_height)
		{
			m_data[r*m_width + c] = val;
		}
	}

	// ��������� �������� �����
	// pt - ���������� �����
	// val - ���� �����
	void setPix(CPoint& pt, char val)
	{
		setPix(pt.x, pt.y, val);
	}

	// ��������� ����� �����
	// � - ������� (x)
	// r - ��� (y)
	// return - ���� �����
	char pix(int c, int r)
	{
		if(c >= 0 && c < m_width && r >= 0 && r < m_height)
			return m_data[r*m_width + c];
		return '.';
	}

	// ��������� ����� �����
	// pt - ���������� �����
	// return - ���� �����
	char pix(CPoint& pt)
	{
		return pix(pt.x, pt.y);
	}

	// ��������, ��� ������� ����� f ������� �� ����� �
	// f - �������� �����
	// � - ����, 0 - ���� ����� ����� '.'
	// return - true, ���� ������� ����� ������� �� ������� �����, ����� false
	bool checkFrame(CFrame& f, char c)
	{
		CFrame tf = *this;
		setFrame(f);
		bool res = true;
		if(countV(x1, c) != frameHeight()) res = false;
		if(res && countV(x2, c) != frameHeight()) res = false;
		if(res && countH(y1, c) != frameWidth()) res = false;
		if(res && countH(y2, c) != frameWidth()) res = false;
		setFrame(tf);

		return res;
	}

	// ������� �������� �� ��������� ����� f
	void cleanOuter(CFrame& f)
	{
		for(int j = y1; j <= y2; j++)
		{
			for(int i = x1; i <= x2; i++)
			{
				if(i >= f.x1 && i <= f.x2 && j>= f.y1 && j <= f.y2) continue;
				m_data[j*m_width + i] = '.';
			}
		}		
	}

	void smooth()
	{
		for(int j = y1; j <= y2; j++)
		{
			for(int i = x1; i <= x2; i++)
			{
				char c = pix(i, j);
				if(c == '.' || c == '*') continue;
				c = pix(i+1, j+1);
				if(c != '.' && c != '*')
				{
					if(pix(i, j+1) == '.') setPix(i,j+1, '*');
					if(pix(i+1, j+1) == '.') setPix(i+1,j, '*');
				}
				c = pix(i-1, j+1);
				if(c != '.' && c != '*')
				{
					if(pix(i, j+1) == '.')setPix(i,j+1, '*');
					if(pix(i-1, j+1) == '.')setPix(i-1,j, '*');
				}
				c = pix(i+1, j-1);
				if(c != '.' && c != '*')
				{
					if(pix(i, j-1) == '.') setPix(i,j-1, '*');
					if(pix(i+1, j-1) == '.') setPix(i+1,j, '*');
				}
				c = pix(i-1, j-1);
				if(c != '.' && c != '*')
				{
					if(pix(i, j-1) == '.')setPix(i,j-1, '*');
					if(pix(i-1, j-1) == '.')setPix(i-1,j, '*');
				}
			}
		}		
		replaceColor('*', '#');
	}

	// ������ ����� c0 �� ��� c1 � ������� ������� �����
	void replaceColor(char c0, char c1)
	{
		for(int j = y1; j <= y2; j++)
		{
			for(int i = x1; i <= x2; i++)
			{
				char* pt = &m_data[j*m_width + i];
				if(*pt == c0) *pt = c1;
			}
		}		
	}

	// ��������, ��� ������ ����� ��������� (����� � ��� ������ '.')
	// x, y - ���������� �����
	// r - ������ ��������
	// return - true, ���� ����� ���������, ����� false
	bool testDot(int x, int y, int r = 1)
	{
		for(int j = y-r; j <= y+r; j++)
		{
			for(int i = x-r; i <= x+r; i++)
			{
				if(i == x && j == y) continue;

				char c = pix(i,j);
				if(c != '.' && c != '*') return false;
			}
		}
		return true;
	}

	// ��������� ���� ��������
	// �������������� ���������� �������� ���� ��������
	// img - ��������, � ������� ������������ this
	// return - ����� ������������� ��������
	int difference(AsciiImage* img)
	{
		int res = 0;
		for(int j = 0; j < m_height; j++)
		{
			for(int i = 0; i < m_width; i++)
			{
				if(pix(i, j) != img->pix(i, j)) res++;
			}
		}

		return res;
	}

	// ����������� ����� ������ �������� � ������ �������� (� ������� ���������)
	// img - ��������, ���� ����� �������� ���������������� ����������� ����� ������ ��������
	void project(AsciiImage* img)
	{
		int W = img->width();
		int H = img->height();
		char* dst = img->data();

		float kx = frameWidth()/float(W);
		float ky = frameHeight()/float(H);

		for(int j = 0; j < H; j++)
		{
			for(int i = 0; i < W; i++)
			{
				float x = i*kx;
				float y = j*ky;

				int ix = (int)x; // ����� �����
				int iy = (int)y;

				x -= ix; // ������� �����
				y -= iy;

				ix += x1; // �������� �������
				iy += y1;

				float q = 1.f - x;
				float p = 1.f - y;

				float c1 = ascii2val(pix(ix, iy));
				float c2 = ascii2val(pix(ix+1, iy));
				float c3 = ascii2val(pix(ix, iy+1));
				float c4 = ascii2val(pix(ix+1, iy+1));
				float col = c1*(q*p) + c2*(x*p) + c3*(q*y) + c4*(x*y); // ������������� �����

				*dst = float2ascii(col);
				dst++;
			}
		}
	}

	// ��������� �������������� ����������, ��������������� ����� �
	// � - �������� ����
	// hInt - ������, ���� ����� �������� ���������� ���������
	void getHIntervals(list<CInterval>& hInt, char c)
	{
		int left = -1;
		for(int i = x1; i <= x2; i++)
		{
			if(countV(i, c))
			{
				if(left >= 0) continue;

				left = i;
			}
			else
			{
				if(left < 0) continue;

				hInt.push_back(CInterval(left, i-1));
				left = -1;
			}
		}
		if(left >= 0)
		{
			hInt.push_back(CInterval(left, x2));
		}
	}

	// ������� ����� �������� ������� ����� �� ��������� � ����������� �
	// � - �������� x-����������
	// refCol - �������� ����, 0 ���� ��� ����� '.'
	int countV(int x, char refCol)
	{
		int c = 0;
		if(refCol)
		{
			for(int j = y1; j <= y2; j++)
			{
				if(pix(x, j) == refCol) c++;
			}
		}
		else
		{
			for(int j = y1; j <= y2; j++)
			{
				if(pix(x, j) != '.') c++;
			}
		}
		return c;
	}

	// ������� ����� �������� ������� ����� �� ����������� � ����������� y
	// y - �������� y-����������
	// refCol - �������� ����, 0 ���� ��� ����� '.'
	int countH(int y, char refCol)
	{
		int c = 0;
		if(refCol)
		{
			for(int i = x1; i <= x2; i++)
			{
				if(pix(i, y) == refCol) c++;
			}
		}
		else
		{
			for(int i = x1; i <= x2; i++)
			{
				if(pix(i, y) != '.') c++;
			}
		}
		return c;
	}

	// ��������� ������� ����� ��������� ������
	// � - �������� ����
	void fill(char c)
	{
		for(int i = x1; i <= x2; i++)
		{
			for(int j = y1; j <= y2; j++)
			{
				m_data[i+j*m_width] = c;
			}
		}
	}

	// ��������� ������ �� ����� �����
	// (������������ �� ����������)
	CPoint firstPoint()
	{
		for(int i = x1; i <= x2; i++)
		{
			for(int j = y1; j <= y2; j++)
			{
				if(pix(i, j) != '.') return CPoint(i, j);
			}
		}
		return CPoint(-1, -1);
	}

protected:

	char* m_data; // ������ ��������
	int m_width, m_height; // ������ � ������ ��������
};

// ��������, ����������� �� ������������ �����
class InputImage : public AsciiImage
{
public:

	// ������ �������� �� ������������ �����
	void read()
	{
		char line[1024];

		image.clear();
		m_height = 0;

		while(gets(line))
		{
			if(!line[0]) break;

			if(!m_height) 
            {
                m_width = (int)strlen(line)*2;
                image.insert(image.end(), m_width+2, '.'); // ������� �������
            }

			for(int k = 0; k < 2; k++) // ��������� �����
			{
				m_height++;
				image.push_back('.'); // ����� �������
				for(int i = 0; i < m_width/2; i++)
				{
					image.push_back(line[i]);
					image.push_back(line[i]); // ��������� �����
				}
				image.push_back('.'); // ������ �������
			}
		}

        image.insert(image.end(), m_width+2, '.'); // ������ �������

        m_data = &image[0];
        m_width += 2;
        m_height += 2;

		resetFrame();
	}
		
private:
	vector<char> image; // ������ ��������
};

// ������� � ������������ ������� (�� ������������ � �������� ���������)
class CImage : public AsciiImage
{
public:
	// ����������� �������� ��������� w * h
	CImage(int w, int h) : AsciiImage(0, w, h)
	{
		m_data = new char[w*h];
	}

	// ����������� �������� �� ����� ������ ��������
	CImage(AsciiImage* img)
	{
		m_width = img->frameWidth();
		m_height = img->frameHeight();
		m_data = new char[m_width*m_height];
		resetFrame();
		for(int j = 0; j < m_height; j++)
		{
			for(int i = 0; i < m_width; i++)
			{
				m_data[j*m_width+i] = img->pix(img->x1+i, img->y1+j);
			}
		}
	}

	// ����������
	~CImage()
	{
		if(m_data) delete m_data;
	}

	// ���������� �������� �� ������
	// src - ��������� �� ������� ������
	// return - ��������� �� ��������� ������� ������
    char* decode(char* src)
    {
        const int sz = size();
        const int maxCount = 64;
        char* dst = m_data;

        int currVal = decodeNumber(*src++);
        int count = 0;
        bool flip = false;
		for(int i = 0; i < sz; i++)
        {
            if(count == 0)
            {
                if(flip) currVal = 1 - currVal;

                count = decodeNumber(*src++);

                if(!count) 
                {
                    count = maxCount;
                    flip = false;
                }
                else
                {
                    flip = true;
                }
            }

            *dst++ = currVal ? '@' : '.';
            count--;
        }

        return src;
    }
};

// ������� ������
class CFontImage
{
public:
	// ����������� �� ������ ������
	// �������� ��������� pData �� ��������� �����
	CFontImage(char** pData)
	{
		char* data = *pData;
		for(int i = 0; i < REF_N; i++)
		{
			digit[i] = new CImage(REF_W, REF_H);
			data = digit[i]->decode(data);
		}
		*pData = data;
	}

	// ����������
	~CFontImage()
	{
		for(int i = 0; i < REF_N; i++)
		{
			delete digit[i];
		}
	}

	CImage* digit[REF_N]; // ������ �������� ������
};

// ������ ��������
class ImageScaner
{
public:
	// ����������� �� �������� ��������
	ImageScaner(AsciiImage* image)
	{
		img = image;

		char* data = (char*) fntData;
		unsigned long N = decodeNumber(*data++);
		for(unsigned long i = 0; i < N; i++)
		{
			CFontImage* fi = new CFontImage(&data);
			fnt.push_back(fi);
		}
	}

	// ����������
	~ImageScaner()
	{
		for(int i = 0; i < (int)fnt.size(); i++)
		{
			delete fnt[i];
		}
		fnt.clear();
	}

	// ������ �������
	// � - ������, ���� ����� �������� ������������ ��������
	void run(int x[NDIGITS])
	{
// ��������� ��������
		CImage* d1[NDIGITS] = {0, 0, 0}; // ����������� ���������� ��������
		CImage* d2[NDIGITS] = {0, 0, 0}; // ����������� ���������� ��������
		int x1[NDIGITS] = {-1, -1, -1}, x2[NDIGITS] = {-1, -1, -1};
		cleanImage();

		list<CInterval> cInt;
		img->getHIntervals(cInt, '@');
		int n1 = extractDigits(cInt, d1); // ������� ��������
		img->resetFrame();
		int n2 = extractDigitsPro(d2); // �������� � �������

		int r1 = img->size(), r2 = r1;

		if(n1 >= n2)
		{
			r1 = scan(d1, x1);
		}
		if(n2 >= n1)
		{
			r2 = scan(d2, x2);
		}
		int* src = r1 < r2 ? x1 : x2;

		// ������ ���������� � �������
		for(int i = 0; i < NDIGITS; i++)
		{
			x[i] = src[i];

			if(d1[i]) delete d1[i];
			if(d2[i]) delete d2[i];
		}

	}

protected:

	// ������������ ��������
	// d - �������� ��������
	// � - ���������
	// return - ��������� �������
	int scan(CImage* d[NDIGITS], int x[NDIGITS])
	{
		// ���������������
		AsciiImage* dp[NDIGITS] = {0, 0, 0}; // ���������������� �����������
		for(int i = 0; i < NDIGITS; i++)
		{
			if(!d[i]) continue; // ������ ��������� ��������

			dp[i] = new CImage(REF_W, REF_H);
			d[i]->project(dp[i]);
		}

		int res = 0;

		// �����������: MIN(�������)
		const int HUGE = img->size();			        // �������� ������� �����

		for(int i = 0; i < NDIGITS; i++)			    // �� 3 ������������
		{
			if(!dp[i]) continue;

			int diMin = HUGE;	                        // ����������� �������
			int fMin = -1;                              // ������ ������� ������ (DEBUG)
			for(int fi = 0; fi < (int)fnt.size(); fi++)		// �� �������
			{
				CFontImage* fImg = fnt[fi];

				for(int n = 0; n < REF_N; n++)			// �� ������ �� 0 �� 9
				{
					int d = dp[i]->difference(fImg->digit[n]);

					if(diMin > d)
					{
						diMin = d; // �������
						fMin = fi; // �����
						x[i] = n;  // �����
					}
				}
			}
			res += diMin; // ����� �������
		}

		// �������
		for(int i = 0; i < NDIGITS; i++)
		{
			if(dp[i]) delete dp[i];
		}

		return res;
	}

	// ������� ��������
	// � ������ ������ - �������� ����� (���� ����)
	void cleanImage()
	{
		img->smooth();

 // �������� �����
		while (1)
		{
			CFrame f0 = makeFrame(0);
			if(f0.frameWidth() < 2 || f0.frameHeight() < 2) break;

			img->setFrame(f0);
			int dx = img->frameWidth()/8;
			int dy = img->frameHeight()/8;
			CFrame f1(img->x1+dx, img->y1+dy, img->frameHeight()-dx-dx, img->frameHeight()-dy-dy);
			if(!img->checkFrame(f1, '.')) break;
			img->cleanOuter(f1);
			img->resetFrame();
			img->x1 = f0.x2+1;
		}

		img->resetFrame();
	}

	// ��������� �������� ������ ����� ( ������� �������� )
	// cInt - ������ �������������� ����������
	// d - ������ ��� ���������� ��������
	// return - ����� ����
	int extractDigits(list<CInterval>& cInt, CImage* d[NDIGITS])
	{
		joinIntervals(cInt);

		int n;
		list<CInterval>::iterator li = cInt.begin();
		for(n = 0; n < NDIGITS && li != cInt.end(); n++, li++ )
		{
			img->resetFrame();
			img->x1 = li->x1;
			img->x2 = li->x2;

			// ����� �������
            bool bx1 = false, bx2 = false;
            for(int j = img->y1; j <= img->y2; j++) // �����
            {
                if(img->pix(img->x1-1, j) != '.' && img->pix(img->x1, j) != '.')
                {
                   img->x1--; 
                   bx1 = true;
                   break;
                }
            }
            for(int j = img->y1; j <= img->y2; j++) // ������
            {
                if(img->pix(img->x2+1, j) != '.' && img->pix(img->x2, j) != '.')
                {
                    img->x2++; 
                    bx2 = true;
                    break;
                }
            }

			// ������
			for(int j = img->y1; j < img->y2; j++)
			{
				if(img->countH(j, 0) > 0) 
				{
					img->y1 = j;
					break;
				}
			}
			// �����
			for(int j = img->y2; j > img->y1; j--)
			{
				if(img->countH(j, 0) > 0) 
				{
					img->y2 = j;
					break;
				}
			}
			d[n] = new CImage(img);

            if(bx1 || bx2)
            {
                for(int j = img->y1; j <= img->y2; j++)
                {
                    if(bx1 && img->pix(img->x1, j) != '.')
                    {
                        if(img->pix(img->x1+1, j) == '.') d[n]->setPix(d[n]->x1, j-img->y1, '.');
                    }
                    if(bx2 && img->pix(img->x2, j) != '.')
                    {
                        if(img->pix(img->x2-1, j) == '.') d[n]->setPix(d[n]->x2, j-img->y1, '.');
                    }
                }
            }
		}

		return n;
	}

	// ����������� ���������� ���� �� ������ 3
	// (�� ������� ����������� ������ ���������)
	void joinIntervals(list<CInterval>& cInt)
	{
		while(cInt.size() > NDIGITS)
		{
			int d0 = img->height();
			list<CInterval>::iterator i0 = cInt.end();
			list<CInterval>::iterator j0 = i0;
			list<CInterval>::iterator i = cInt.begin();
			for(i++; i != cInt.end(); i++)
			{
				list<CInterval>::iterator j = i;
				j--; // ���������� ��������

				int d = i->x1 - j->x2; // ���������� ����� ���������� ��������� ����������
				if(d < d0)
				{
					d0 = d;
					i0 = i;
					j0 = j;
				}
			}
			if(i0 == cInt.end()) return; // ������

			j0->x2 = i0->x2;
			cInt.erase(i0);
		}
	}

	// ��������� �������� ������ ����� ( �������� ������ ������ )
	// d - ������ ��� ���������� ��������
	// return - ����� ����
	int extractDigitsPro(CImage* d[NDIGITS])
	{
		CPoint dr[4] = {CPoint(1, 0), CPoint(0, 1), CPoint(-1, 0), CPoint(0, -1)}; // ����������� ��������

		int n;
		for(n = 0; n < NDIGITS; n++) // ��� ������ �����
		{
		// ����� ������
			CPoint pt0 = img->firstPoint();
			if(pt0 == CPoint(-1, -1)) break; // ����� ���������

			queue<CPoint> q;
			q.push(pt0);

			pt0.x--; // ������� �����

			CPoint pt1 = pt0, pt = pt0;

			CFrame f(img->width(), img->height(), -img->width(), -img->height());

			img->setPix(pt0, '*');

			int dir = 0; // ����������� ��������
			int turn = 0; // ����������� ��������
			do 
			{
				pt1 = pt + dr[dir];
				char c = img->pix(pt1);
				if(c == '.' || c == '*')
				{
					img->setPix(pt1, '*');
					turn = 1; // �������
				}
				else
				{
					q.push(pt1);
					turn = -1; // ������
				}
				dir += turn;
				if(dir < 0)
					dir += 4;
				else if(dir >= 4)
					dir -= 4;

				pt = pt1;

				// �������� ������
				if(f.x1 > pt.x) f.x1 = pt.x;
				if(f.y1 > pt.y) f.y1 = pt.y;
				if(f.x2 < pt.x) f.x2 = pt.x;
				if(f.y2 < pt.y) f.y2 = pt.y;

			} while(pt != pt0);

			img->setFrame(f);

        // ����������� ����� ������ �������
			d[n] = new CImage(f.frameWidth()-2, f.frameHeight()-2);
			d[n]->fill('.');

			f.x1++;
			f.y1++;

			while(!q.empty())
			{
				pt = q.front();
				q.pop();
				char c = img->pix(pt); 
				if(c == '*') continue;

				img->setPix(pt, '*');
				d[n]->setPix(pt.x-f.x1, pt.y-f.y1, c);
				for(int i = 0; i < 4; i++)
				{
					pt1 = pt + dr[i];
					c = img->pix(pt1); 
					if(c != '*') q.push(pt1);
				}
			}

			img->replaceColor('*', '.');

			img->resetFrame();
		}

		return n;
	}

	// ����������� ����� ������ �� ������� �����
	CFrame makeFrame(char refCol)
	{
		CFrame f = *img, f0 = f;

		// �����
		f.x1 = -1;
		for(int i = img->x1; i <= img->x2; i++)
		{
			if(img->countV(i, refCol) > 0) 
			{
				f.x1 = i;
				break;
			}
		}

		if(f.x1 == -1) return CFrame();

		// ������
		for(int i = f.x1+1; i <= img->x2; i++)
		{
			if(img->countV(i, refCol) == 0) 
			{
				f.x2 = i-1;
				break;
			}
		}

		img->x1 = f.x1;
		img->x2 = f.x2;

		// ������
		f.y1 = -1;
		for(int j = img->y1; j <= img->y2; j++)
		{
			if(img->countH(j, refCol) > 0) 
			{
				f.y1 = j;
				break;
			}
		}

		if(f.y1 == -1) return CFrame();

		// �����
		for(int j = f.y1+1; j <= img->y2; j++)
		{
			if(img->countH(j, refCol) == 0) 
			{
				f.y2 = j-1;
				break;
			}
		}

		img->setFrame(f0); // ������������ �������

		return f;
	}

	AsciiImage* img;
	vector<CFontImage*> fnt;
};

int main(int argc, char* argv[])
{
	InputImage mainImg; // ������� ��������
	ImageScaner scaner(&mainImg); // ������
	int out[NDIGITS] = {-1, -1, -1}; // ���������

	mainImg.read(); // ������ ��������

	scaner.run(out); // ������ �������

	// ����� ����������
	for(int i = 0; i < NDIGITS; i++)
	{
		if(out[i] >= 0) printf("%d", out[i]); 
	}
	printf("\n");

	return 0;
}

// ����� �������
char fntData[] = "9"
// 0) MS Serif
"076<;852573844485348533;315;9;9;9;9;9;9;9;9;9;9;9;9;9;9;9;9;423;33485438456366525;67"
"0:3?5>6<89;9;7526>6>6>6>6>6>6>6>6>6>6>6>6>6>6>6>6>6>6>6>6<:::5D"
"067:=7=63582558238722;6>6>6>6>6>6>6>5?5=5?5?4?3@4@3?3@3?5?4?3=12o1C1"
"0689>6>536653683287?5?5?5?3?5?4=7=5;<<:::=7?6>6?5?5?5?5?5?41595175717556;6"
"0=5?5?5=7<8<8;315;31595159335834564556455645553754385258523:520@=5?5?5?5?5?5?5?52"
"06=7=7=7;8<82B2@2B5?5>;9>6?<8?7?5?6?5?5@4A3A3A323:523:4178436455?6=:77"
"0:6;9;5>3?5?4?5?3@4@4@3?546551<251<2856168<8;;9;9;9;9;9;:862485348545555?6<;67"
"02B2B2A1C1C12>3?4@4@4@4?3A3A3A3?4@4@4@4?3A3A3A3@3A3A3A3?3A3A3A3:"
"0698>65555384449434:334:334:336834583465468138<::8>534934493386339;:8=7=7>6>6>321>233;334854384895"
"076<;8<75554566348533;315;9;9;9;9;9;9;::426662B3<1466446644@3?5?4?5?5?3?4>6>4;6:"
// 1) Arial
"076<;8=671746562585259424:514::;9;8<8<8<8<8<8<8<8<9;9;414:514:515951585356637276=8;:95"
"0?5>6<8;99;6>4e2@4<88<7=7=7=7=7=7=7=7=7=7=7=7=7=7=7=7=7=7=7"
"077;<7>572736653585159515:415:423;4?5?5?5>5>5>5>6=6<7<7<6=7<6=6=6>5>C1C1C1C"
"076;<7>572736653585249524:4?5?5>6>5:9;8<:9<>7?5?5@4@8<9;9:51595167618284>7<:95"
"0=4?5>6>6=7<8<8;9;414:42494349434844474546554646455644574448430@=4@4@4@4@4@4@43"
"04?4@4@4@44?5?5?5?4@4?>6@4A382825762496?5?5@4@4@413<9:::51585266637275>7<996"
"086;<7>662745653585249515:414@4@44484294A3B2856177<9;:9;414;414;414;415:415952585266547275>7<:85"
"10@?5>5>5>5?5>5>5?5>5?5?4?5>5?5?5>5?5?5>5?5?5?5?4@4@4@4;"
"076;<8=6627465545753494259425943485357545556=8;7>5@36662595159514;9;9;414;414:51595167537374?6=995"
"076;;8>58164665358524:415:9;9;9;9;:::96158616582B3<144:247454?5?514:424952495256637366=8;:87"
// 2) Arial Black
"077;;7>5@4A3A28381748175?5?5?5>6>6>6>6>6>6?5?5717571757174818381B3A3@5?6=995"
"0<8;9::9;8<6>5?20Z2@4>6:::::::::::::::::::::::::::::::"
"077:=6?5@3A3B18381847175717575357=7<8;8;9:9::9:9:9:99;8;8;B2B1C1C1C1W"
"077:<7>5@4@3819274727474457=7<7:::9;9;::;9;=8=7=7=>6?57174818292A3A4?6=8:5"
"0<6=7<8<8;9::::9;8<8<76166716662656364736464636562756200<<6>6>6>6>62"
"03@4@4@4@4@3A3A37=6>6329>6?4A3B2B28291748=7=7=7=7166?57174818282B3@5>7<9:5"
"086;<7>5@3A38182838174817=7=63557193B2C1C1:1B3@5?6>66167617661757184728192A4@4?7<9:4"
"100O<8<7<7=7<7=7<7=7<7=7=7<7=7=7=7<7=7=7=7<8<8<88"
"077:<7?4A3A2828274817571757175717473A3A4?5?4A2B283@5?5>6?5?5?4818291C1B3A4>8;4"
"067;<7>5@4@3B2747265?6>6>6>6>67174818291C2B2B3A5627=7=73548174728283@4@5>7<996"
// 3) Broadway
"094=9:53386436762486248723872298219821982199;9;9;9;9;9;9119911982198219821982287238634762575276348;:95"
"0B2=79;4@1W114>6>6>6>6>6>6>6>6>6>6>6>6>6>6>6>6>6>6>6>5?5?5?5?"
"095;<7536546642863297229712981298129812891289136:226:225:9;9;8;9;8;9;8;9;8;9;8;8<8;8;351C"
"085;=6528444842693269;9;9;9;9;9;8<79::8@7=9;9;::::::::::<8=7:127924584?7;5"
"0T1B2B2A3@4?5?5>6=7=7<8;9::::9;82198219722962396149524942594C1C89;9;9;9;93"
"05=7=729181B2B2B8<;8=7347=8<9;9;:226:136:127:127:118<8<8<8:118:127:12793269335853477<9:5"
"0:4=9963386436752585249;9:9;9;933591739123329721:8<8<9;9119911991199119821982288229623962485267338;:95"
"0DJ68;9;9;8;9;9:::9;9:::::9::::9;9;9:9;9;9;8;9;9;8<8;9;8<8<6"
"086;;8455548344;235:2279228822:622<332=133@4@4A4A3B3A2B2B123A4?6>8<::;712;523:443855=8;5"
"084=:942673475358426832792279218<8<8<8<8<8<8:127:127:224<2B451::::9;9;941684268525763468;:87"
// 4) Jokerman LET
"084>8;;8=6>6825493437123526222626621415:4178<234;1538451:11251=234;99;315812315771756285536743632235532145>7<9:;86"
"0@47=1W1C1C6>7=762576167526751775169416941694169;9;:::::::::9;9;9;9;9;9;9<82"
"067;<6537545644763386334133132423231329273818372223633323;8;315;323;8;8;8;7=6=6=6>5>594253;1C1C1q"
"029;A3B3A3@4744?5>5>4?5>5?413;8;:>9=7=6?5?532:523:;9;8734565?4?5?:613;251;3:"
"071C3@4@4?521<414;414:514:523:4@45375538413136613136622138332135C1C3A1@3@6716>6>6>6>6>3A3A3A37"
"02:;>6?653746653673647265?4@4@4@4@<8=8=73387329:226;126=7=::<:51461261321322614122927284?6=9:5"
"0=1A4>6=8;:9;8;89:9;7<7=6=6>5?529442;251=15143614235:232139232229273413272513353514:51496256646276=995"
"014@>6C1C1Q2<77=4?5>6>64465554655465446>6=7=6=7=313<8<313<8<314;414;8<8;9<8>57"
"075=:8535754556545655465546464556455646456=8<8=57273413192422122613:<6>6219;912511=12191522281612191B3A4?6=995"
"06161<2431378236>212?2B2756357624952495249;9;95347644573A231>22451692369236>6>6>6>6@4=7=7@4=7=43"
// 5) Viner Hand ITC
"0;5=8::::9<75266537455645564466357625671577157714871397139;9;96149614952485347634754465635574358;:8=6;"
"0@4>6<8;89:7<6>5627531135>5?4?4?5?4?5?4?5?4?5?5>6>6=7=7=7=7=6<9;9;4@"
"0T3?5=7<7<8;423;413;333;233@3A2A2A3A2A2A2A3A2A3A2A3@67249442;342<24142=135:138723:16"
"0B27=7=5>6<9236=4?4?6=;9<7=66111564647184@3?4?4?4>4?5>4=5?4>4?6>5>6>5?3A"
"0?1B2@4@4@3@4?5>6>5>6=313<323<232<242614342522542431912431V1A=3A2B2A3A3A3A3@4@3A2:"
"0:1B;8<7<8;95?4@4@5>9;::::::244?4@3@4@3@3@3@3@3@3?4@3@5>5>5@4@3@"
"0=3?5>6=7=6>5?5>6=6>6>5>5?4@4?4@4@3@4?466433;2B2:3517751595149515754>6=89;7;"
"0B13B1p231517>5?4@3@4@3@3@4@3@3A2A3A3A2A3A2A3A3@5?5?5?4@4@3A2>"
"07251;>5?4@4718375446635563654484439523:513<7=6>5@5?6=7<314;324:425933593448353925483359::9<7>4>"
"0M6=8:>6>541:44384447454743574447532:4?591467347354@3A3@3@3@4@4@4@3@4@412=7=7=6>4;"
// 6) Chiller
"071A6=8;9;831784258535583368335:325;314<8<7>6>6>213>213>213=313=313>223=223318233<243;24493547366439;;75"
"0=3>:9;7=3A5?3A2B1748174725671586>6>6>6>6>5?5?5?5?4@4@4@4@3A3A4@4@4A33"
"0:6;;8=6@392547544574@4@4@4?4?4?4?4?4?4?4@3@3A3@3@4@3@3A2A3@3A2AA35="
"05m1=142944?4@2@3A2A2A3@3@3@8;;9<::?6A3B2B3A3A3@3A3@4@382639334;77"
"073@6>6>6>5>5>5?5>512<423;42494349433944441351h3454@4@4@4@4A3A2B2B2B2B2B2B28"
"022A6=;22131W1A38=4@4@4@4@4@5?9;<9<A3B3A3B3A3A3@3@4@3@471658244:9<6<"
"0;3@6=7=6=5>6=5>6=5>6>5>5?5>5?4@47184547349433=132>131?13143813234;315<8=7716662A4?6=4"
"013@D1C1B5474@2A2A3A2A2B2B2A2B2B1B2B2B1B2B1C1B2B2B1C1B2B1C1C1B1="
"0<1A4?512:;95257554647364736392639264827382746358335>562755663584359326932693269326423335483647364747356733214<31685"
"0:2>::<7=7644566445843448444854295<125;1369238543@3A3@3A3@3A3@3@3@4@3@3@3A2A2B1A3;"
// 7) Algerian
"075=;8=641:441227431166241175241176167411158615991199119911991199119911951311951595158615861411741123117625731145564634116;126:128812:95"
"0:4?75249433:5?56185?8318<8<8<8<8<8<8<8<8<8<8<8<8<8<8<8<8<8<8;:8=7>6?"
"074=:9>551:3B24115814116714117411141176171144111911241129272711273112212511471512;512;8;8:512;8;412<7=5:13311;215;31C1C1W2B"
"082>;8?441416341238265725762666275637441137375317129613:8@5;;>7?6>632117<8<8<86141165111411671745123=124<125413338:5"
"074@411>411=7=6>411>611;621119411121199119311131186131183112311852311731133117533116543116543115553115@3D;3241=15;315;31113;311>6=8<9;92"
"0?1B4B25>6?5=115;135=73A3A3A;9=7322265619411167527511>411>641963476158417841611651116662512374?6=722332:95"
"093>:8>5?5312373646111411731216711326725615761859254819271;193718551711641874187411158411158411167411167411256634114511441224116;1279128713;85"
"03@4A3A3?11311=11311=113111991183111685221192113485>5>6>5>6>6=411>411=7=6=511=511=511=7=7<8<8<8<8=76"
"0;1B4A3@211>311=411<4168>58174311313443118435744662114733116;128:9<732:34124726741113119:::;9;41311:414118526654634124<127;4"
"082>;8436641;43115636731126752584178417841867166716581511482@113:1411381611522324117337=411=7=411>6<7=6<7<78;9522<6;"
// 8) Stencil
"08212<514:51585356546554646472747274817481748174@4@4@4@4@4@4817481748174817481747364736465546563576168515:4136"
"05<3A4@5?7=7=7=7=7=7=7=7=7=7=7=7=7=7=7=7=7=7=7=7=7=7=7=5@3C1C"
"06214:51766184638372927381928192B29182916493358;9;8;9;8:8;7<6=5>4;2B24:332B1C1V1C1B22684"
"07114;417751855383648274818381838174817482557=7<7:9;8<8?7=8=82468165@4@4@4@4?5815582728461874174"
"0=4?5>6>6=7=7<8<8<8:118:1189218831883187328633863385348435843583368381C1;171;98<8<8;:9=7="
"023=13A3A3@4?5>6=7;M2A3A322166313175718471934683189;9;92459164A3A3A3A3@4826482719461874165"
"08213<41595176545564645473647273827382746375447=74367273819281:27112817481748174817481748174826482648354746375617751694154"
"0759?221C1C1C1B2A324:337642=2@3@4?4?5?5>5>6=7=7<8<8;9;9;::::::::9<8<77"
"07313:616671747364737283728381838183818381837373737365717751586157627473728381838183A3A3A3A38183818382818381766163"
"07311<614871567355646374637472747184@4@4@48174817481:18291838184628<8516835482738273737373736464646456625851694146";
