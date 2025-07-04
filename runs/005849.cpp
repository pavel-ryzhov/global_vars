// ��������� ��� ������� ������ "������" �� ��������� ������� �������

#include <iostream>
#include <cstring>

using std::cout;
using std::cin;

#define SIZE 200	// ������ ������� ��� �������� �����������
#define WHITE '.'
#define LIGHTGRAY '%'
#define DARKGRAY '#'
#define BLACK '@'
#define DIGITHEIGHT 10	// ����������� ������ �����
#define OBJECTS 10	// ������������ ���������� �������������� ����
struct Image	// ������ ����������� � ��� �������
{
	char image[SIZE][SIZE];
	int left;	// ������ ������ ������ �������
	int right;	// ������ ������ ������� �������
	int top;	// ������ ������ �������� �������
	int bottom;	// ������ ������ ������� �������
};

bool isColour (char ch)	// ��������� true, ���� ������ �� �����
{
	switch (ch)
		{
		case LIGHTGRAY:
		case DARKGRAY:
		case BLACK:
			return true;
			break;
		default:
			return false;
			break;
		}
}

bool haveColour(char* str)	// ��������� true, ���� � ������ ���� �������� ������
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (isColour(str[i]))
			return true;		
	}
	return false;
}

int firstColourIndex(char* str)	// ���� ������ ������� ������� � ������. ���� �� �����, ���������� -1.
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (isColour(str[i]))
			return i;
	}
	return -1;	// ���������� � ������, ���� � ������ ��� �������
}

int lastSymbIndex(char* str)	// ���� ������ ������� ������� � ������. ���� �� �����, ���������� -1.
{
	int result = -1;
	for (int i = 0; str[i] != '\0'; i++)
		if (isColour(str[i]))
			result = i;
	return result;	// ���������� -1 � ������, ���� � ������ ��� �������
}

// ���������� ������ �����������
void setSize(Image& img)
{
	img.left = SIZE;
	img.right = -1;
	img.top = SIZE;
	img.bottom = -1;
	int i = 0;
	while (!haveColour(img.image[i]))
	{
		i++;
		if (i == SIZE)
			break;
	}
	img.top = i;
	if (i < SIZE)
	while (haveColour(img.image[i]))
		{
			if (firstColourIndex(img.image[i]) < img.left)
				img.left = firstColourIndex(img.image[i]);
			if (lastSymbIndex(img.image[i]) > img.right)
				img.right = lastSymbIndex(img.image[i]);
			i++;
			if (i == SIZE)
			{
				img.bottom = -1;
				return;
			}
		}
	img.bottom = --i;
}

void read(Image& input)	// �������� ����������� �� �������� ������ � input
{
	char str[SIZE];	
	do	// ������� ��� ������ ������
	{
		cin.getline(str, SIZE);
	}
	while (!haveColour(str));
	int i = 0;
	while (haveColour(str))	// ��������� ������, ���� ��� �������� ������� �������
	{
		strcpy(input.image[i],str);
		i++;
		cin.getline(str, SIZE);
	}
	input.bottom = --i;
	setSize(input);
}

// ��������� ��������� ������ (������ �������� ������� ��������) �� sourse, � �������� � obfect
// ���������� true, ec�� ������, false, ���� ��� ������� �������� � sourse
void getCluster(Image& source, Image& target, int i, int j)
{
	target.image[i][j] = source.image[i][j];
	source.image[i][j] = WHITE;
	if (i - 1 >= 0)
		if (isColour(source.image[i-1][j]))
			getCluster(source, target, i-1, j);
	if (i + 1 <= SIZE - 1)
		if (isColour(source.image[i+1][j]))
			getCluster(source, target, i+1, j);
	if (j - 1 >= 0)
		if (isColour(source.image[i][j-1]))
			getCluster(source, target, i, j-1);
	if (j + 1 <= SIZE - 1)
		if (isColour(source.image[i][j+1]))
			getCluster(source, target, i, j+1);
}

bool readObject(Image& source, Image& object)	// �������� ������ �������� ������� �������� �� source � object
{
	if (source.left < SIZE)
	{
		for (int i = source.top; i <= source.bottom; i++)
			if (isColour(source.image[i][source.left]))
				getCluster(source, object, i, source.left);
		setSize(source);
		setSize(object);
		return true;
	}
	else
		return false;
}

void clearImg(Image& img)	// ������ ��� ������� img ������
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 1; j++)
			img.image[i][j] = WHITE;
		img.image[i][SIZE-1] = '\0';
	}
	img.left = SIZE;
	img.right = -1;
	img.top = SIZE;
	img.bottom = -1;
}

int verticalSizeOfLine(Image& img, int horizontalIndex)	// ���������� ������ ������� ����� ������������ �����
{
	int topIndex = 0;
	int i = 0;
	while (!isColour(img.image[i][horizontalIndex]))
		i++;
	topIndex = i;
	i = img.bottom;
	while (!isColour(img.image[i][horizontalIndex]))
		i--;
	return i - topIndex + 1;
}

void devide(Image& img, Image& target)	// ��������� ����������� �� 2 ����� �� ������ �������� �����, ������� ���������� ����� � target
{
	int min = SIZE;
	int indexOfMin = 0;
	for (int i = img.left + 6; i <= img.right - 6; i++)
	{
		if (verticalSizeOfLine(img, i) < min)
		{
			indexOfMin = i;
			min = verticalSizeOfLine(img, i);
		}
	}
	for (int i = img.top; i <= img.bottom; i++)
		for (int j = indexOfMin; j <= img.right; j++)
			if (isColour(img.image[i][j]))
			{
				target.image[i][j] = img.image[i][j];
				img.image[i][j] = WHITE;
			}
	setSize(img);
	setSize(target);
}

void putPixel(Image& img, int i, int j)	// ����������� ������������ ������� ����������� �������
{
	img.image[i][j] = BLACK;
	if (i - 1 >= 0)
		img.image[i-1][j] = BLACK;		
	if (i + 1 <= SIZE - 1)
		img.image[i+1][j] = BLACK;		
	if (j - 1 >= 0)
		img.image[i][j-1] = BLACK;		
	if (j + 1 <= SIZE - 1)
		img.image[i][j+1] = BLACK;		
}

void generate0(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <= bottom; i++)
	{
		putPixel(img, i, left);
		putPixel(img, i, right);
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, top, j);
		putPixel(img, bottom, j);
	}
}

void generate1(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <= bottom; i++)
	{
		putPixel(img, i, right);
	}
}

void generate2(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <=(top + bottom)/2; i++)
	{
		putPixel(img, i, right);
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, top, j); putPixel(img, bottom, j);
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, bottom - static_cast<int>((j - left) * static_cast<double>(bottom - (top + bottom)/2 +1)/(right - left + 1)), j);
	}
}

void generate3(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <= bottom; i++)
	{
		putPixel(img, i, right);
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, top, j); 
		putPixel(img, bottom, j); 
		putPixel(img, (top+bottom)/2, j);
	}
	for (int i = top + static_cast<int>((bottom - top)*3.0/4.0) + 1; i <= bottom; i++)
	{
		putPixel(img, i, left);
	}
	for (int i = top ; i <= top + static_cast<int>((bottom - top)/4.0); i++)
	{
		putPixel(img, i, left);
	}
}

void generate4(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <=bottom; i++)
	{
		putPixel(img, i, right);
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, (top+bottom)/2, j);
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, (top + bottom)/2 - static_cast<int>((j - left) * static_cast<double>((top + bottom)/2 - top +1)/(right - left + 1)), j);
	}
}

void generate5(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <=(top + bottom)/2; i++)
	{
		putPixel(img, i, left);
	}
	for (int i = (top + bottom)/2 + 1; i <= bottom; i++)
	{
		putPixel(img, i, right);
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, top, j); 
		putPixel(img, bottom, j); 
		putPixel(img, (top+bottom)/2, j);
	}
	for (int i = top + static_cast<int>((bottom - top)*3.0/4.0) + 1; i <= bottom; i++)
	{
		putPixel(img, i, left);
	}
}

void generate6(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <=(top + bottom)/2; i++)
	{
		putPixel(img, i, left);
	}
	for (int i = (top + bottom)/2 + 1; i <= bottom; i++)
	{
		putPixel(img, i, left); 
		putPixel(img, i, right);
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, top, j); 
		putPixel(img, bottom, j); 
		putPixel(img, (top+bottom)/2, j);
	}
	for (int i = top; i <= top + static_cast<int>((bottom - top)/4.0); i++)
	{
		putPixel(img, i, right);
	}
}

void generate7(Image& img, int left, int right, int top, int bottom)
{
	for (int j = left; j <= right; j++)
	{
		putPixel(img, top, j);
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, bottom - static_cast<int>((j - left) * static_cast<double>(bottom - top + 1)/(right - left + 1)), j);
	}
}

void generate8(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <= bottom; i++)
	{
		putPixel(img, i, left); 
		putPixel(img, i, right);
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, top, j); 
		putPixel(img, bottom, j); 
		putPixel(img, (top+bottom)/2, j);
	}
}

void generate9(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <=(top + bottom)/2; i++)
	{
		putPixel(img, i, left); 
		putPixel(img, i, right);
	}
	for (int i = (top + bottom)/2 + 1; i <= bottom; i++)
	{
		 putPixel(img, i, right);
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, top, j); 
		putPixel(img, bottom, j); 
		putPixel(img, (top+bottom)/2, j);
	}
	for (int i = top + static_cast<int>((bottom - top)*3.0/4.0) + 1; i <= bottom; i++)
	{
		putPixel(img, i, left);
	}
}

void generateDigit(int Digit, Image& img, int left, int right, int top, int bottom)	// ���������� ����������� ����� Digit, ������� �� � ������������� left-right-top-bottom � img
{
	img.left = left;
	img.right = right;
	img.top = top;
	img.bottom = bottom;
	left++;
	right--;
	top++;
	bottom--;
	if (right - left + 1 > 9 || Digit == 1)
		switch (Digit)
		{
		case 0:
			generate0(img, left, right, top, bottom);
			break;
		case 1:
			generate1(img, left, right, top, bottom);
			break;
		case 2:
			generate2(img, left, right, top, bottom);
			break;
		case 3:
			generate3(img, left, right, top, bottom);
			break;
		case 4:
			generate4(img, left, right, top, bottom);
			break;
		case 5:
			generate5(img, left, right, top, bottom);
			break;
		case 6:
			generate6(img, left, right, top, bottom);
			break;
		case 7:
			generate7(img, left, right, top, bottom);
			break;
		case 8:
			generate8(img, left, right, top, bottom);
			break;
		case 9:
			generate9(img, left, right, top, bottom);
			break;
		}
}

double compare(const Image& img1, Image img2)	// ���������� �����, ������� 1, ������������, ��������� ������ ������
{
	int square1 = 0;
	int square2 = 0;
	int intersectionSquare = 0;	// ������� ����������� �����
	for (int i = img1.top; i <= img1.bottom; i++)
		for (int j = img1.left; j <= img1.right; j++)
		{
			if (isColour(img1.image[i][j]))
				square1++;
			if (isColour(img2.image[i][j]))
				square2++;
			if (isColour(img1.image[i][j]) && isColour(img2.image[i][j]))
				intersectionSquare++;
		}
	return static_cast<double>(intersectionSquare)/(square1 + square2 - intersectionSquare);
}

double compareWithDigit(int digit,	// �����, � ������� ������������ ������ img
						const Image& img)	// �����������, ������� ���� ����������
{
	double maxIntersection = 0;
	Image tmp;
	int left = img.left;
	int right = img.right;
	int top = img.top;
	int bottom = img.bottom;
	//for (int i = 0; i <=  4 + (img.right - img.left)/4; i++)
	//{
	clearImg(tmp);
	generateDigit(digit, tmp, left, right, top, bottom);
	double intersection = compare(img, tmp);
	if (intersection > maxIntersection)
		maxIntersection = intersection;
	//left++;
	//right--;
	//top++;
	//bottom--;
	//if (left > right || top > bottom)
	//	break;
	//}
	return maxIntersection;
}

void recognize(const Image& img)
{
	double maxIntersection = 0;
	int result = -1;
	for (int digit = 0; digit < 10; digit++)
	{
		double intersection = compareWithDigit(digit, img);
		if (intersection > maxIntersection)
		{
			maxIntersection = intersection;
			result = digit;
		}
	}
	cout << result;
}


int main()
{
	// ���������� �����������
	Image input;
	clearImg(input);
	read(input);

	// ���������� ��������� ��������
	int DigitsNumber = 0;
	Image object[OBJECTS];
	int i = 0;
	clearImg(object[0]);
	while (readObject(input, object[i]))
	{
		if (i == OBJECTS)
			break;
		if (object[i].bottom - object[i].top < DIGITHEIGHT)	// ������� � ������� ����� DIGITHEIGHT �������������
		{
			clearImg(object[i]);
			continue;
		}
		if (i > 0)
			if (object[i].right < object[i-1].right)	// ������, ������� �������� ������ �����, �������������
			{
				object[i-1] = object[i];
				clearImg(object[i]);
				continue;
			}
		i++;
		DigitsNumber++;
		if (i < OBJECTS)
			clearImg(object[i]);
	}

	// ������������� ��������
	for (int j = 0; j < DigitsNumber; j++)
	{
		recognize(object[j]);
	}
	cout << "\n" ;
	return 0;
}