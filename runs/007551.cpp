#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>

typedef std::vector<std::vector<char> > Array2D;

const int EtalonWidth = 7, EtalonHeight = 10;
const int MinSquare = 50;
const int White = 0;
const int LightGray = 1;
const int DarkGray = 4;
const int Black = 6;
const int MinBlackPixelsCount = 5;

static int LeftBorder, RightBorder;

class Rect
{
public:
	Rect(): x0(-1), y0(-1), x1(-1), y1(-1) {}
	int x0, y0, x1, y1;
};

std::vector<char> UnusualEtalonNumbers[10];

char UnusualEtalons[][EtalonHeight][EtalonWidth]=
{{{0,0,0,0,0,0,1,},
{0,0,1,1,1,0,0,},
{0,0,1,0,0,0,0,},
{0,0,1,0,0,0,0,},
{0,0,1,0,1,1,0,},
{0,1,0,0,0,1,1,},
{0,0,0,0,0,1,1,},
{0,0,0,0,0,1,1,},
{1,1,0,0,1,1,0,},
{0,1,1,1,1,0,0,}},

{{0,0,0,1,1,0,0,},
{0,0,1,1,1,0,0,},
{0,1,1,1,1,1,0,},
{1,1,0,0,0,1,0,},
{0,1,1,1,1,0,0,},
{0,1,1,1,1,1,0,},
{1,0,0,0,0,1,1,},
{1,0,0,0,0,1,1,},
{1,1,0,0,0,1,1,},
{0,0,1,1,1,0,0,}},

{{0,1,1,1,1,0,0,},
{0,1,0,0,0,0,0,},
{0,1,1,1,1,0,0,},
{0,0,0,1,1,1,0,},
{0,0,0,1,1,1,1,},
{1,0,0,1,1,1,1,},
{0,0,0,1,1,1,1,},
{1,0,0,1,1,1,1,},
{1,0,0,1,1,1,0,},
{0,1,1,1,1,0,0,}}};

char ThickEtalons[10][EtalonHeight][EtalonWidth]=

{{{0,1,1,1,1,0,0,},  //0
  {0,1,1,1,1,1,0,},
  {1,1,0,0,0,1,1,},
  {1,1,0,0,0,1,1,},
  {1,1,0,0,0,1,1,},
  {1,1,0,0,0,1,1,},
  {1,1,0,0,0,1,1,},
  {1,1,0,0,0,1,1,},
  {0,1,1,1,1,1,0,},
  {0,0,1,1,1,0,0,}},


{{1,1,1,1,1,0,0,},  //1
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {1,1,1,1,1,1,1,}},


 {{0,1,1,1,1,1,0},  //2
  {1,1,1,1,1,1,1},
  {1,1,0,0,0,1,1},
  {0,0,0,0,0,1,1},
  {0,0,0,0,1,1,0},
  {0,0,0,1,1,0,0},
  {0,0,1,1,0,0,0},
  {0,1,1,0,0,0,0},
  {1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1}},


{{0,1,1,1,1,1,0,},  //3
 {1,1,1,1,1,1,1,},
 {1,1,0,0,0,1,1,},
 {0,0,0,0,0,1,1,},
 {0,0,0,1,1,1,0,},
 {0,0,0,1,1,1,1,},
 {0,0,0,0,0,1,1,},
 {1,1,0,0,0,1,1,},
 {1,1,1,1,1,1,1,},
 {0,1,1,1,1,0,0,}},


 {{0,0,0,0,1,0,0,},  //4
  {0,0,0,1,1,0,0,},
  {0,0,0,1,1,0,0,},
  {0,0,1,1,1,0,0,},
  {0,1,1,0,1,0,0,},
  {1,1,0,0,1,0,0,},
  {1,1,1,1,1,1,1,},
  {1,1,1,1,1,1,1,},
  {0,0,0,0,1,1,0,},
  {0,0,0,0,1,1,0,}},


{{1,1,1,1,1,1,1,},  //5
 {1,1,1,1,1,1,1,},
 {1,1,0,0,0,0,0,},
 {1,1,1,1,1,0,0,},
 {1,1,1,1,1,1,0,},
 {0,0,0,0,1,1,1,},
 {0,0,0,0,0,1,1,},
 {1,0,0,0,0,1,1,},
 {1,1,1,1,1,1,0,},
 {0,1,1,1,1,0,0,}},


{{0,0,1,1,1,1,1,},  //6
 {0,1,1,1,1,1,1,},
 {1,1,0,0,0,0,0,},
 {1,1,0,0,0,0,0,},
 {1,1,1,1,1,0,0,},
 {1,1,1,1,1,1,0,},
 {1,1,0,0,0,1,1,},
 {1,1,0,0,0,1,1,},
 {0,1,1,1,1,1,0,},
 {0,0,1,1,1,0,0,}},


{{1,1,1,1,1,1,1,},  //7
 {1,1,1,1,1,1,1,},
 {0,0,0,0,1,1,0,},
 {0,0,0,1,1,0,0,},
 {0,0,0,1,0,0,0,},
 {0,0,1,1,0,0,0,},
 {0,0,1,1,0,0,0,},
 {0,0,1,0,0,0,0,},
 {0,1,1,0,0,0,0,},
 {0,1,1,0,0,0,0,}}, 


 {{0,1,1,1,1,1,0,},  //8
  {1,1,1,1,1,1,1,},
  {1,1,0,0,0,1,1,},
  {1,1,0,0,0,1,1,},
  {0,1,1,1,1,1,0,},
  {1,1,1,1,1,1,1,},
  {1,1,0,0,0,1,1,},
  {1,1,0,0,0,1,1,},
  {1,1,1,1,1,1,1,},
  {0,1,1,1,1,1,0,}},


{{0,1,1,1,1,0,0,},  //9
 {1,1,1,1,1,1,0,},
 {1,0,0,0,0,1,1,},
 {1,0,0,0,0,1,1,},
 {1,1,1,1,1,1,1,},
 {0,1,1,1,1,1,1,},
 {0,0,0,0,0,1,1,},
 {1,0,0,0,0,1,1,},
 {1,1,1,1,1,1,0,},
 {0,1,1,1,1,0,0,}}};

char ThinEtalons[10][EtalonHeight][EtalonWidth]=

{{{0,0,1,1,1,0,0,},  //0
  {0,1,0,0,0,1,0,},
  {1,0,0,0,0,0,1,},
  {1,0,0,0,0,0,1,},
  {1,0,0,0,0,0,1,},
  {1,0,0,0,0,0,1,},
  {1,0,0,0,0,0,1,},
  {1,0,0,0,0,0,1,},
  {0,1,0,0,0,1,0,},
  {0,0,1,1,1,0,0,}},


{{1,1,1,1,1,0,0,},  //1
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {0,0,1,1,1,0,0,},
 {1,1,1,1,1,1,1,}},


 {{0,1,1,1,1,1,0},  //2
  {1,0,0,0,0,1,1},
  {1,0,0,0,0,0,1},
  {0,0,0,0,0,0,1},
  {0,0,0,0,0,1,0},
  {0,0,0,0,1,0,0},
  {0,0,0,1,0,0,0},
  {0,0,1,0,0,0,0},
  {0,1,0,0,0,0,0},
  {1,1,1,1,1,1,1}},


{{0,1,1,1,1,1,0,},  //3
 {1,0,0,0,0,0,1,},
 {1,0,0,0,0,0,1,},
 {0,0,0,0,0,0,1,},
 {0,0,0,1,1,1,0,},
 {0,0,0,0,0,0,1,},
 {0,0,0,0,0,0,1,},
 {1,0,0,0,0,0,1,},
 {1,0,0,0,0,0,1,},
 {0,1,1,1,1,1,0,}},


 {{0,0,0,0,1,0,0,},  //4
  {0,0,0,0,1,0,0,},
  {0,0,0,1,1,0,0,},
  {0,0,1,0,1,0,0,},
  {0,1,0,0,1,0,0,},
  {1,0,0,0,1,0,0,},
  {1,0,0,0,1,0,0,},
  {1,1,1,1,1,1,1,},
  {0,0,0,0,1,0,0,},
  {0,0,0,1,1,1,0,}},


{{1,1,1,1,1,1,1,},  //5
 {1,0,0,0,0,0,0,},
 {1,0,0,0,0,0,0,},
 {1,0,0,0,0,0,0,},
 {1,1,1,1,1,0,0,},
 {1,0,0,0,0,1,0,},
 {0,0,0,0,0,0,1,},
 {1,0,0,0,0,0,1,},
 {0,1,0,0,0,1,0,},
 {0,0,1,1,1,0,0,}},


{{0,0,1,1,1,1,0,},  //6
 {0,1,0,0,0,0,0,},
 {1,0,0,0,0,0,0,},
 {1,0,1,1,1,0,0,},
 {1,1,0,0,0,1,0,},
 {1,0,0,0,0,0,1,},
 {1,0,0,0,0,0,1,},
 {1,0,0,0,0,0,1,},
 {0,1,0,0,0,1,0,},
 {0,0,1,1,1,0,0,}},


{{1,1,1,1,1,1,1,},  //7
 {0,0,0,0,0,1,0,},
 {0,0,0,0,1,0,0,},
 {0,0,0,0,1,0,0,},
 {0,0,0,1,0,0,0,},
 {0,0,0,1,0,0,0,},
 {0,0,1,0,0,0,0,},
 {0,0,1,0,0,0,0,},
 {0,1,0,0,0,0,0,},
 {0,1,0,0,0,0,0,}}, 


 {{0,0,1,1,1,0,0,},  //8
  {0,1,0,0,0,1,0,},
  {1,0,0,0,0,0,1,},
  {0,1,0,0,0,1,0,},
  {0,0,1,1,1,0,0,},
  {0,1,0,0,0,1,0,},
  {1,0,0,0,0,0,1,},
  {1,0,0,0,0,0,1,},
  {0,1,0,0,0,1,0,},
  {0,0,1,1,1,0,0,}},


{{0,0,1,1,1,0,0,},  //9
 {0,1,0,0,0,1,0,},
 {1,0,0,0,0,0,1,},
 {1,0,0,0,0,0,1,},
 {1,0,0,0,0,1,1,},
 {0,1,1,1,1,1,1,},
 {0,0,0,0,0,0,1,},
 {1,0,0,0,0,0,1,},
 {0,1,0,0,0,1,0,},
 {0,0,1,1,1,0,0,}}};


int RoundUp(const double d)
{
	if ( d - static_cast<int>(d) != 0)
		return static_cast<int>(d) +1;
	return static_cast<int>(d);
}

int Round(const double d)
{
	if (d - static_cast<int>(d) >= 0.5)
		return static_cast<int>(d) + 1;
	return static_cast<int>(d);
}
double Abs(const double d)
{
	if (d < 0)
		return -d;
	return d;
}

double Normalize(const double d)
{
	if (Abs( (d - Round(d))) < 0.00000000001)
		return Round(d);
	return d;
}

char GetColor(const Array2D& m)
{
	if (m.size() > 0 && m[0].size() > 0)
	{
		double Color = 0;
		for (int i=0;i<m.size();i++)
			for (int j=0;j<m[i].size();j++)
				Color+=m[i][j];
		Color = Color / (m.size() * m[0].size());
		if (Color >= 2)
			return 1;
	}
	return 0;
}

bool Resize(Array2D& Image)
{
	Array2D NewImage;

	int Color = 0;
	double StepX = static_cast<double>(Image[0].size())/EtalonWidth;
	double StepY = static_cast<double>(Image.size())/EtalonHeight;
	double x, y;
	std::vector<char> Temp;
	Array2D Pixel;
	std::vector<char> v(0);
	int BlackPixelsCount = 0;
	for (int y0=0; y0<EtalonHeight; y0++)
	{
		NewImage.push_back(v);
		for (int x0=0; x0<EtalonWidth; x0++)
		{
			double ylim = Normalize(StepY*(y0+1));
			for (y=RoundUp(StepY*y0);y<ylim;y++)
			{
				double xlim = Normalize(StepX*(x0+1));
				Temp.clear();
				for (x=RoundUp(StepX*x0);x<xlim;x++)
				{
					Temp.push_back(Image[y][x]);
				}
				Pixel.push_back(Temp);
			}
			char Color = GetColor(Pixel);
			if (Color == 1)
				BlackPixelsCount++;
			NewImage[y0].push_back(Color);
			Pixel.clear();
		}
	}
	Image = NewImage;
	if (BlackPixelsCount >= MinBlackPixelsCount)
		return true;
	return false;
}

int Recognize(const Array2D& Image)
{
	int MaxDegree = -10000;
	int BestEtalon = 0, Degree = 0;
	for (int n=0;n<10;n++)
	{
		Degree = 0;
		int d1 = 0, d2 = 0, d3 = 0;
		for (int y=0;y<EtalonHeight;y++)
		{
			for (int x=0;x<EtalonWidth;x++)
			{
				
				if (ThickEtalons[n][y][x] == Image[y][x])
					d1++;
				else 
					d1--;
				if (ThinEtalons[n][y][x] == Image[y][x])
					d2++;
				else 
					d2--;
			}
		}
		Degree = d1 > d2?d1:d2;
		for (int i=0;i<UnusualEtalonNumbers[n].size();i++)
		{
			d1 = 0;
			for (int y=0;y<EtalonHeight;y++)
			{
				for (int x=0;x<EtalonWidth;x++)
				{
					if (UnusualEtalons[UnusualEtalonNumbers[n][i]][y][x] == Image[y][x])
						d1++;
					else 
						d1--;
				}
			}
			Degree = Degree>d1?Degree:d1;
		}
		if (Degree > MaxDegree)
		{
			MaxDegree = Degree;
			BestEtalon = n;
		}
	}
	return BestEtalon;
}

void FloodFill(const Array2D& Matrix, unsigned char* Map,unsigned char Num, int x, int y)
{
	if ( (x >= 0) && (y >= 0) &&
		 (x < Matrix[0].size()) && y < (Matrix.size()) &&
		 (Map[y*Matrix[0].size() + x] == 0) &&
		((Matrix[y][x] == Black) || (Matrix[y][x] == DarkGray) || 
		  (Matrix[y][x] == LightGray)))
	{
		if (Matrix[y][x] == LightGray)
			if ( x>RightBorder || x<LeftBorder)
				return;
		if (x>RightBorder)
			RightBorder = x;
		if (x<LeftBorder)
			LeftBorder = x;
		Map[y*Matrix[0].size() + x] = Num;
		FloodFill(Matrix, Map, Num, x+1, y+1);
		FloodFill(Matrix, Map, Num, x, y+1);
		FloodFill(Matrix, Map, Num, x-1, y+1);
		FloodFill(Matrix, Map, Num, x+1, y);
		FloodFill(Matrix, Map, Num, x-1, y);
		FloodFill(Matrix, Map, Num, x+1, y-1);
		FloodFill(Matrix, Map, Num, x, y-1);
		FloodFill(Matrix, Map, Num, x-1, y-1);
	}
}


std::vector<Array2D> Separate(const Array2D& Matrix)
{
	unsigned char* Map = new unsigned char[Matrix.size() * Matrix[0].size()];
	std::fill(Map, Map + Matrix.size() * Matrix[0].size(), 0);
	std::vector<Array2D> Result;

	int Width = Matrix[0].size();
	int Height = Matrix.size();
	int Number = 0;

	for (int x=0; x<Width; x++)
	{
		for (int y=0; y<Height; y++) //выделение связанных областей	
			if (Matrix[y][x] == Black && Map[y*Width + x] == 0)
			{
				RightBorder = x;
				LeftBorder = x;
				FloodFill(Matrix, Map, ++Number, x, y);
			}
	}

	std::vector<Rect> Rects(Number);
	for (int y=0; y<Height; y++)  //определение границ прямоугольников для распознавания
	{
		for (int x=0; x<Width; x++)
		{
			int CurNum = Map[y*Width + x];
			if (CurNum > 0)
			{
				if (Rects[CurNum-1].x0 == -1)
				{
					Rects[CurNum-1].x0 = x;
					Rects[CurNum-1].x1 = x+1;
				}
				else if ( Rects[CurNum-1].x0 > x )
					Rects[CurNum-1].x0 = x;
				else if ( Rects[CurNum-1].x1 < x+1 )
					Rects[CurNum-1].x1 = x+1;

				if (Rects[CurNum-1].y0 == -1)
				{
					Rects[CurNum-1].y0 = y;
					Rects[CurNum-1].y1 = y+1;
				}
				else if ( Rects[CurNum-1].y0 > y )
					Rects[CurNum-1].y0 = y;
				else if ( Rects[CurNum-1].y1 < y+1 )
					Rects[CurNum-1].y1 = y+1;
			}

		}
	}

	Array2D Image;
	std::vector<char> Temp;
	for (int n=0; n<Number; n++)
	{
		Image.clear();
		//проверка размера захватываемой области; область площадью меньше, чем MinSquare пикселей, считается шумом
		if ( (Rects[n].x1 - Rects[n].x0) * (Rects[n].y1 - Rects[n].y0) > MinSquare )
		{
			Temp.resize(Rects[n].x1 - Rects[n].x0);
			for (int y=Rects[n].y0; y<Rects[n].y1; y++)
			{
				for (int x=Rects[n].x0; x< Rects[n].x1; x++)
				{
					if (Map[y*Width + x] == n+1)
						Temp[x-Rects[n].x0] = Matrix[y][x];
					else
						Temp[x-Rects[n].x0] = 0;
				}
				Image.push_back(Temp);
			}
			Result.push_back(Image);
		} 
	}


	return Result;
}

int main()
{
	using namespace std;

	UnusualEtalonNumbers[5].push_back(0);
	UnusualEtalonNumbers[5].push_back(2);
	UnusualEtalonNumbers[8].push_back(1);
	vector<char> v;

	string str;
	Array2D Matrix;
	int ClearLinesCount = -10;
	while( ClearLinesCount != 5)
	{
		bool ClearLine = true;
		v.clear();
		cin>>str;
		for (size_t j=0; j<str.length(); j++)
		{
			switch (str[j])
			{
			case '%':
				v.push_back(LightGray);
				ClearLine= false;
				break;
			case '#':
				v.push_back(DarkGray);
				ClearLine = false;
				break;
			case '@':
				v.push_back(Black);
				ClearLine = false;
				break;
			default:
				v.push_back(White);
			}
		}
		if (ClearLine)
		{
			ClearLinesCount++;
		}
		else
			ClearLinesCount = 0;
		Matrix.push_back(v);
	}
	std::vector<Array2D> Images = Separate(Matrix);
	for (std::vector<Array2D>::iterator iter=Images.begin();iter!=Images.end();++iter)
	{
		if (Resize(*iter))
		{
			cout<<Recognize(*iter);
		}
	}
	return 0;
}