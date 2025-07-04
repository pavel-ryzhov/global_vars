// Программа для решения задачи "Сканер" из тестового задания Яндекса

#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
//#include <fstream>
//using std::ifstream;
//ifstream cin("Input.txt");
//using std::ofstream;
//ofstream cout("Output.txt");

#define SIZE 200
#define WHITE '.'
#define LIGHTGRAY '%'
#define DARKGRAY '#'
#define BLACK '@'
#define DIGITHEIGHT 10	// Минимальная высота цифры

struct Image	// Хранит изображение и его границы
{
	char image[SIZE][SIZE];
	int left;	// Индекс самого левого символа
	int right;	// Индекс самого правого символа
	int top;	// Индекс верхнего правого символа
	int bottom;	// Индекс нижнего правого символа
	int square;	// Площадь изображения в пикселах
};

bool isSymb (char ch)
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

bool haveSymb(char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (isSymb(str[i]))
			return true;		
	}
	return false;
}

int firstSymbIndex(char* str)	// Ищет индекс первого символа в строке. Если не нашел, возвращает -1.
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (isSymb(str[i]))
			return i;
	}
	return -1;	// возвращает в случае, если в строке нет символа
}

int lastSymbIndex(char* str)	// Ищет индекс первого символа в строке. Если не нашел, возвращает -1.
{
	int result = -1;
	for (int i = 0; str[i] != '\0'; i++)
		if (isSymb(str[i]))
			result = i;
	return result;	// возвращает -1 в случае, если в строке нет символа
}

// Определяет размер изображения
void setSize(Image& img)
{
	img.left = SIZE;
	img.right = -1;
	img.top = SIZE;
	img.bottom = -1;
	int i = 0;
	while (!haveSymb(img.image[i]))
	{
		i++;
		if (i == SIZE)
			break;
	}
	img.top = i;
	if (i < SIZE)
	while (haveSymb(img.image[i]))
		{
			if (firstSymbIndex(img.image[i]) < img.left)
				img.left = firstSymbIndex(img.image[i]);
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

void read(Image& input)
{
	char str[SIZE];	
	do	// Считать все пустые строки
	{
		cin.getline(str, SIZE);
	}
	while (!haveSymb(str));
	int i = 0;
	while (haveSymb(str))	// Считывать строки, пока они содержат цветные символы
	{
		strcpy(input.image[i],str);
		i++;
		cin.getline(str, SIZE);
	}
	input.bottom = --i;
	setSize(input);
}

// Считывает отдельный объект (группу сязанных цветных символов) из sourse, и помещает в obfect
// Возвращает true, ecли считал, false, если нет цветных символов в sourse
void getCluster(Image& source, Image& target, int i, int j)
{
	target.image[i][j] = source.image[i][j];
	source.image[i][j] = WHITE;
	target.square++;
	if (i - 1 >= 0)
		if (isSymb(source.image[i-1][j]))
			getCluster(source, target, i-1, j);
	if (i + 1 <= SIZE - 1)
		if (isSymb(source.image[i+1][j]))
			getCluster(source, target, i+1, j);
	if (j - 1 >= 0)
		if (isSymb(source.image[i][j-1]))
			getCluster(source, target, i, j-1);
	if (j + 1 <= SIZE - 1)
		if (isSymb(source.image[i][j+1]))
			getCluster(source, target, i, j+1);
}

bool readObject(Image& source, Image& object)
{
	if (source.left < SIZE)
	{
		for (int i = source.top; i <= source.bottom; i++)
			if (isSymb(source.image[i][source.left]))
				getCluster(source, object, i, source.left);
		setSize(source);
		setSize(object);
		return true;
	}
	else
		return false;
}

void write(const Image& img)
{
	for (int i = img.top; i <= img.bottom; i++)
	{
		for (int j = img.left; j <= img.right; j++)
			cout << img.image[i][j] ;
		cout << "\n" ;
	}
}

void clearImg(Image& img)
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
	img.square = 0;
}

int verticalSizeOfLine(Image& img, int horizontalIndex)
{
	int topIndex = 0;
	int i = 0;
	while (!isSymb(img.image[i][horizontalIndex]))
		i++;
	topIndex = i;
	i = img.bottom;
	while (!isSymb(img.image[i][horizontalIndex]))
		i--;
	return i - topIndex + 1;
}

void devide(Image& img, Image& target)
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
			if (isSymb(img.image[i][j]))
			{
				target.image[i][j] = img.image[i][j];
				img.image[i][j] = WHITE;
				target.square++;
				img.square--;
			}
	setSize(img);
	setSize(target);
}

void generate0(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <= bottom; i++)
	{
		img.image[i][left] = img.image[i][right] = BLACK;
		img.square += 2;
	}
	for (int j = left; j <= right; j++)
	{
		img.image[top][j] = img.image[bottom][j] = BLACK;
		img.square += 2;
	}
}

void generate1(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <= bottom; i++)
	{
		img.image[i][right] = BLACK;
		img.square++;
	}
}

void generate2(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <=(top + bottom)/2; i++)
	{
		img.image[i][right] = BLACK;
		img.square++;
	}
	for (int j = left; j <= right; j++)
	{
		img.image[top][j] = img.image[bottom][j] = BLACK;
		img.square += 2;
	}
	for (int j = left; j <= right; j++)
	{
		img.image[bottom - static_cast<int>((j - left) * static_cast<double>(bottom - (top + bottom)/2 +1)/(right - left + 1))][j] = BLACK;
		img.square++;
	}
}

void generate3(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <= bottom; i++)
	{
		img.image[i][right] = BLACK;
		img.square++;
	}
	for (int j = left; j <= right; j++)
	{
		img.image[top][j] = img.image[bottom][j] = img.image[(top+bottom)/2][j] = BLACK;
		img.square += 3;
	}
}

void generate4(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <=bottom; i++)
	{
		img.image[i][right] = BLACK;
		img.square++;
	}
	for (int j = left; j <= right; j++)
	{
		img.image[(top+bottom)/2][j] = BLACK;
		img.square++;
	}
	for (int j = left; j <= right; j++)
	{
		img.image[(top + bottom)/2 - static_cast<int>((j - left) * static_cast<double>((top + bottom)/2 - top +1)/(right - left + 1))][j] = BLACK;
		img.square++;
	}
}

void generate5(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <=(top + bottom)/2; i++)
	{
		img.image[i][left] = BLACK;
		img.square++;
	}
	for (int i = (top + bottom)/2 + 1; i <= bottom; i++)
	{
		img.image[i][right] = BLACK;
		img.square++;
	}
	for (int j = left; j <= right; j++)
	{
		img.image[top][j] = img.image[bottom][j] = img.image[(top+bottom)/2][j] = BLACK;
		img.square += 3;
	}
}

void generate6(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <=(top + bottom)/2; i++)
	{
		img.image[i][left] = BLACK;
		img.square++;
	}
	for (int i = (top + bottom)/2 + 1; i <= bottom; i++)
	{
		img.image[i][left] = img.image[i][right] = BLACK;
		img.square += 2;
	}
	for (int j = left; j <= right; j++)
	{
		img.image[top][j] = img.image[bottom][j] = img.image[(top+bottom)/2][j] = BLACK;
		img.square += 3;
	}
}

void generate7(Image& img, int left, int right, int top, int bottom)
{
	for (int j = left; j <= right; j++)
	{
		img.image[top][j] = BLACK;
		img.square++;
	}
	for (int j = left; j <= right; j++)
	{
		img.image[bottom - static_cast<int>((j - left) * static_cast<double>(bottom - top + 1)/(right - left + 1))][j] = BLACK;
		img.square++;
	}
}

void generate8(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <= bottom; i++)
	{
		img.image[i][left] = img.image[i][right] = BLACK;
		img.square += 2;
	}
	for (int j = left; j <= right; j++)
	{
		img.image[top][j] = img.image[bottom][j] = img.image[(top+bottom)/2][j] = BLACK;
		img.square += 3;
	}
}

void generate9(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <=(top + bottom)/2; i++)
	{
		img.image[i][left] = img.image[i][right] = BLACK;
		img.square += 2;
	}
	for (int i = (top + bottom)/2 + 1; i <= bottom; i++)
	{
		 img.image[i][right] = BLACK;
		 img.square++;
	}
	for (int j = left; j <= right; j++)
	{
		img.image[top][j] = img.image[bottom][j] = img.image[(top+bottom)/2][j] = BLACK;
		img.square += 3;
	}
}

void generateDigit(int Digit, Image& img, int left, int right, int top, int bottom)
{
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
	img.left = left;
	img.right = right;
	img.top = top;
	img.bottom = bottom;
}

double compare(const Image& img1, Image img2)	// Возвращает число, меньшее 1, показывающее, насколько похожи фигуры
{
	int intersectionSquare = 0;	// Площадь пересечения фигур
	for (int i = img1.top; i <= img1.bottom; i++)
		for (int j = img1.left; j <= img1.right; j++)
			if (isSymb(img1.image[i][j]) && isSymb(img2.image[i][j]))
				intersectionSquare++;
	return static_cast<double>(intersectionSquare)/(img1.square + img2.square - intersectionSquare);
}

double compareWithDigit(int digit,	// Цифра, с которой сравнивается объект img
						const Image& img)	// Изображение, которое надо распознать
{
	double maxIntersection = 0;
	Image tmp;
	int left = img.left;
	int right = img.right;
	int top = img.top;
	int bottom = img.bottom;
	for (int i = 0; i < (img.right - img.left)/4; i++)
	{
	clearImg(tmp);
	generateDigit(digit, tmp, left, right, top, bottom);
	double intersection = compare(img, tmp);
	if (intersection > maxIntersection)
		maxIntersection = intersection;
	left++;
	right--;
	top++;
	bottom--;
	}
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
	Image input;
	clearImg(input);
	read(input);
	//write(input);

	int DigitsNumber = 0;
	Image object[4];
	int i = 0;
	clearImg(object[0]);
	while (readObject(input, object[i]))
	{
		if (i == 4)
			break;
		if (object[i].bottom - object[i].top < DIGITHEIGHT)	// Объекты с высотой менше DIGITHEIGHT отбрасываются
		{
			clearImg(object[i]);
			continue;
		}
		if (i > 0)
			if (object[i].right < object[i-1].right)	// Обекты, которые содержат внутри цифру, отбрасываются
			{
				object[i-1] = object[i];
				clearImg(object[i]);
				continue;
			}
		i++;
		DigitsNumber++;
		if (i < 4)
			clearImg(object[i]);
	}
	if (DigitsNumber == 1)
	{
		clearImg(object[1]);
		devide(object[0], object[1]);
		DigitsNumber = 2;
	}
	if (DigitsNumber == 2)
	{
		if (object[0].right - object[0].left > object[1].right - object[1].left)
		{
			object[2] = object[1];
			clearImg(object[1]);
			devide(object[0], object[1]);
		}
		else
		{
			clearImg(object[2]);
			devide(object[1], object[2]);
		}
		DigitsNumber = 3;
	}

	for (int j = 0; j < DigitsNumber; j++)
	{
		recognize(object[j]);
	}
	cout << "\n" ;
	Image Digit;
	for (int i = 0; i < 10; i++)
	{
		clearImg(Digit);
		generateDigit(i, Digit, 0, 15, 0, 20);
		cout << "\n\n" ;
		write(Digit);
	}
	return 0;
}