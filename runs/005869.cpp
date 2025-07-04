// Программа для решения задачи "Сканер" из тестового задания Яндекса

#include <iostream>
#include <cstring>
#include <cmath>

using std::cout;
using std::cin;

//#include <fstream>
//using std::ifstream;
//ifstream cin("Input.txt");

//using std::ofstream;
//ofstream cout("Output.txt");

#define SIZE 150	// Размер массива для хранения изображений
#define WHITE '.'
#define LIGHTGRAY '%'
#define DARKGRAY '#'
#define BLACK '@'
#define DIGITHEIGHT 10	// Минимальная высота цифры
#define OBJECTS 10	// Максимальное количество распозноваемых цифр

struct Image	// Хранит изображение и его границы
{
	char image[SIZE][SIZE];
	int left;	// Индекс самого левого символа
	int right;	// Индекс самого правого символа
	int top;	// Индекс самого верхнего символа
	int bottom;	// Индекс самого нижнего символа
	Image()
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE - 1; j++)
				image[i][j] = WHITE;
			image[i][SIZE-1] = '\0';
		}
		left = SIZE;
		right = -1;
		top = SIZE;
		bottom = -1;
	}
};

void write(const Image& img)
{
	for (int i = img.top; i <= img.bottom; i++)
	{
		for (int j = img.left; j <= img.right; j++)
			cout << img.image[i][j] ;
		cout << "\n" ;
	}
}


bool isColour (char ch)	// Взвращает true, если символ не белый
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

bool haveColour(char* str)	// Взвращает true, если в строке есть цветноей символ
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (isColour(str[i]))
			return true;		
	}
	return false;
}

int firstColourIndex(char* str)	// Ищет индекс первого символа в строке. Если не нашел, возвращает -1.
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (isColour(str[i]))
			return i;
	}
	return -1;	// возвращает в случае, если в строке нет символа
}

int lastSymbIndex(char* str)	// Ищет индекс первого символа в строке. Если не нашел, возвращает -1.
{
	int result = -1;
	for (int i = 0; str[i] != '\0'; i++)
		if (isColour(str[i]))
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

void read(Image& input)	// Помещает изображение из входного потока в input
{
	char str[SIZE];	
	do	// Считать все пустые строки
	{
		cin.getline(str, SIZE);
	}
	while (!haveColour(str));
	int i = 0;
	while (haveColour(str))	// Считывать строки, пока они содержат цветные символы
	{
		strcpy(input.image[i],str);
		i++;
		cin.getline(str, SIZE);
	}
	input.bottom = --i;
	setSize(input);
}

// Считывает отдельный объект (группу сязанных цветных символов) из sourse, и помещает в object
// Возвращает true, ecли считал, false, если нет цветных символов в sourse
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

bool readObject(Image& source, Image& object)	// Помещает группу соседних цветных символов из source в object
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

void clearImg(Image& img)	// Делает все символы img белыми
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

int verticalSizeOfLine(Image& img, int horizontalIndex)	// Возвращает высоту цветной части вертикальной линии
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

void devide(Image& img, Image& target)	// Рзаделяет изображение на 2 части по самому тонокому месту, помещая отделенную часть в target
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

void putPixel(Image& img, int i, int j)	// Закрашивает определенным образом окрестность символа
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

void putBow1(Image& img, int left, int right, int top, int bottom)
{
	double width = right - left + 1;
	double height = bottom - top + 1;
	for (int j = left; j <= right; j++)
	{
		putPixel(img, bottom - static_cast<int>(height/width*sqrt(width*width - (j - right)*(j - right))), j); 
	}
}

void putBow2(Image& img, int left, int right, int top, int bottom)
{
	double width = right - left + 1;
	double height = bottom - top + 1;
	for (int j = left; j <= right; j++)
	{
		putPixel(img, bottom - static_cast<int>(height/width*sqrt(width*width - (j - left)*(j - left))), j); 
	}
}

void putBow3(Image& img, int left, int right, int top, int bottom)
{
	double width = right - left + 1;
	double height = bottom - top + 1;
	for (int j = left; j <= right; j++)
	{
		putPixel(img, top + static_cast<int>(height/width*sqrt(width*width - (j - left)*(j - left))), j); 
	}
}

void putBow12(Image& img, int left, int right, int top, int bottom)
{
	double width = right - left + 1;
	double hRadius = width/2.0;
	double height = bottom - top + 1;
	for (int j = left; j <= right; j++)
	{
		putPixel(img, bottom - static_cast<int>(2.0*height/width*sqrt(hRadius*hRadius - (j - (left+right)/2.0)*(j - (left+right)/2.0))), j); 
	}
}

void putBow23(Image& img, int left, int right, int top, int bottom)
{
	double width = right - left + 1;
	double height = bottom - top + 1;
	double vRadius = height/2.0;
	for (int i = top; i <= bottom; i++)
	{
		putPixel(img, i, left + static_cast<int>(2.0*width/height*sqrt(vRadius*vRadius - (i - (top+bottom)/2.0)*(i - (top+bottom)/2.0))));
	}
}

void putBow34(Image& img, int left, int right, int top, int bottom)
{
	double width = right - left + 1;
	double hRadius = width/2.0;
	double height = bottom - top + 1;
	for (int j = left; j <= right; j++)
	{
		putPixel(img, top + static_cast<int>(2.0*height/width*sqrt(hRadius*hRadius - (j - (left+right)/2.0)*(j - (left+right)/2.0))), j); 
	}
}

void putBow41(Image& img, int left, int right, int top, int bottom)
{
	double width = right - left + 1;
	double height = bottom - top + 1;
	double vRadius = height/2.0;
	for (int i = top; i <= bottom; i++)
	{
		putPixel(img, i, right - static_cast<int>(2.0*width/height*sqrt(vRadius*vRadius - (i - (top+bottom)/2.0)*(i - (top+bottom)/2.0))));
	}
}



void generate0(Image& img, int left, int right, int top, int bottom)
{
	double width = right - left + 1;
	double hRadius = width/2.0;
	double height = bottom - top + 1;
	double vRadius = height/2.0;
	int hCenter = (right + left)/2;
	int vCenter = (top + bottom)/2;
	for (int i = top; i <= bottom; i++)
	{
		putPixel(img, i, hCenter - static_cast<int>(width/height*sqrt(vRadius*vRadius - (i - (top+bottom)/2.0)*(i - (top+bottom)/2.0))));
		if ((right + left) % 2 == 0)
			putPixel(img, i, hCenter + static_cast<int>(width/height*sqrt(vRadius*vRadius - (i - (top+bottom)/2.0)*(i - (top+bottom)/2.0)))); 
		else
			putPixel(img, i, hCenter + 1 + static_cast<int>(width/height*sqrt(vRadius*vRadius - (i - (top+bottom)/2.0)*(i - (top+bottom)/2.0)))); 
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, vCenter - static_cast<int>(height/width*sqrt(hRadius*hRadius - (j - (left+right)/2.0)*(j - (left+right)/2.0))), j); 
		if ((top + bottom) % 2 == 0)
			putPixel(img, vCenter + static_cast<int>(height/width*sqrt(hRadius*hRadius - (j - (left+right)/2.0)*(j - (left+right)/2.0))), j); 
		else
			putPixel(img, vCenter + 1 + static_cast<int>(height/width*sqrt(hRadius*hRadius - (j - (left+right)/2.0)*(j - (left+right)/2.0))), j); 
	}
}

void generate1(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <= bottom; i++)
	{
		putPixel(img, i, right);
		putPixel(img, i, right - 1);
	}
	for (int x = 0; x < (right - left + 1)/4.0; x++)
	{
		putPixel(img, x*(bottom - top + 1.0)*3.0/4.0/(right - left + 1.0), right - x);
	}

}

void generate2(Image& img, int left, int right, int top, int bottom)
{
	putBow12(img, left, right, top, top + (bottom - top)/4.0);
	//for (int i = top + (bottom - top)/4.0; i <=(top + bottom)/2; i++)
	//{
	//	putPixel(img, i, right);
	//}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, bottom, j);
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, bottom - static_cast<int>((j - left) * static_cast<double>((bottom - top + 1)*0.75)/(right - left + 1)), j);
	}
}

void generate3(Image& img, int left, int right, int top, int bottom)
{
	putBow12(img, left, right, top, top + (bottom - top + 1)/2/2);
	putBow23(img, (left + right)/2, right, top, (top + bottom)/2);
	putBow23(img, (left + right)/2, right, (top + bottom)/2, bottom);
	putBow34(img, left, right, bottom - (bottom - top + 1)/2/2, bottom);
	putBow3(img, (left + right)/2, right, top + (bottom - top + 1)/2/2, bottom - (bottom - top + 1)/2);
	putBow2(img, (left + right)/2, right, (top + bottom)/2, bottom - (bottom - top + 1)/2/2);

	//for (int i = top; i <= bottom; i++)
	//{
	//	putPixel(img, i, right);
	//}
	//for (int j = left; j <= right; j++)
	//{
	//	putPixel(img, top, j); 
	//	putPixel(img, bottom, j); 
	//	putPixel(img, (top+bottom)/2, j);
	//}
	//for (int i = top + static_cast<int>((bottom - top)*3.0/4.0) + 1; i <= bottom; i++)
	//{
	//	putPixel(img, i, left);
	//}
	//for (int i = top ; i <= top + static_cast<int>((bottom - top)/4.0); i++)
	//{
	//	putPixel(img, i, left);
	//}
}

void generate4(Image& img, int left, int right, int top, int bottom)
{
	for (int i = top; i <=bottom; i++)
	{
		putPixel(img, i, right);
		putPixel(img, i, right - 1);
	}
	for (int j = left; j <= right; j++)
	{
		putPixel(img, top + (bottom - top + 1)*3/4, j);
	}
	for (int j = left; j <= right - 2; j++)
	{
		putPixel(img, top + (bottom - top + 1)*3/4 - static_cast<int>((j - left) * static_cast<double>((bottom - top + 1)*3.0/4.0)/(right - left + 1 - 2)), j);
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
	putBow23(img, (left + right)/2, right, (top + bottom)/2, bottom);
	putBow41(img, left, (left + right)/2, (top + bottom)/2, bottom);
	putBow41(img, left, (left + right)/2, top, bottom);
	putBow12(img, left, right, top, top + (bottom - top + 1)/4.0);

	//for (int i = top; i <=(top + bottom)/2; i++)
	//{
	//	putPixel(img, i, left);
	//}
	//for (int i = (top + bottom)/2 + 1; i <= bottom; i++)
	//{
	//	putPixel(img, i, left); 
	//	putPixel(img, i, right);
	//}
	//for (int j = left; j <= right; j++)
	//{
	//	putPixel(img, top, j); 
	//	putPixel(img, bottom, j); 
	//	putPixel(img, (top+bottom)/2, j);
	//}
	//for (int i = top; i <= top + static_cast<int>((bottom - top)/4.0); i++)
	//{
	//	putPixel(img, i, right);
	//}
}

void generate7(Image& img, int left, int right, int top, int bottom)
{
	for (int j = left; j <= right; j++)
	{
		putPixel(img, top, j);
	}
	for (int j = (left + right)/2; j <= right; j++)
	{
		putPixel(img, bottom - static_cast<int>((j - (left + right)/2)*2*static_cast<double>(bottom - top + 1)/(right - left + 1)), j);
	}
}

void generate8(Image& img, int left, int right, int top, int bottom)
{
	generate0(img, left, right, top, (top + bottom)/2);
	if ((top + bottom) % 2 == 0)
		generate0(img, left, right, (top + bottom)/2, bottom);
	else
		generate0(img, left, right, (top + bottom)/2 + 1, bottom);
}

void generate9(Image& img, int left, int right, int top, int bottom)
{
	//generate0(img, left, right, top, (top + bottom)/2);
	//putBow12(img, left, right, top, top + (bottom - top + 1)/4.0);
	//putBow34(img, left, right, top + (bottom - top + 1)/4.0, (top + bottom)/2);
	putBow41(img, left, (left + right)/2, top, (top + bottom)/2);
	putBow23(img, (left + right)/2, right, top, bottom);
	putBow34(img, left, right, bottom - (bottom - top + 1)/4.0, bottom);
	putBow23(img, (left + right)/2, right, top, (top + bottom)/2);
	//putBow3(img, (left + right)/2, right, top + (top + bottom)/4.0, (top + bottom)/2);
	//for (int i = top; i <=(top + bottom)/2; i++)
	//{
	//	putPixel(img, i, left); 
	//	putPixel(img, i, right);
	//}
	//for (int i = (top + bottom)/2 + 1; i <= bottom; i++)
	//{
	//	 putPixel(img, i, right);
	//}
	//for (int j = left; j <= right; j++)
	//{
	//	putPixel(img, top, j); 
	//	putPixel(img, bottom, j); 
	//	putPixel(img, (top+bottom)/2, j);
	//}
	//for (int i = top + static_cast<int>((bottom - top)*3.0/4.0) + 1; i <= bottom; i++)
	//{
	//	putPixel(img, i, left);
	//}
}

void generateDigit(int Digit, Image& img, int left, int right, int top, int bottom)	// Генерирует изображение цифры Digit, помещая ее в прямоугольник left-right-top-bottom в img
{
	img.left = left;
	img.right = right;
	img.top = top;
	img.bottom = bottom;
	left++;
	right--;
	top++;
	bottom--;
	if ( (right - left + 1 > 7 || Digit == 1) && (right - left + 1 > 2) )
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

double compare(const Image& img1, const Image img2)	// Возвращает число, меньшее 1, показывающее, насколько похожи фигуры
{
	int square1 = 0;
	int square2 = 0;
	int intersectionSquare = 0;	// Площадь пересечения фигур
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

double compareWithDigit(int digit,	// Цифра, с которой сравнивается объект img
						const Image& img)	// Изображение, которое надо распознать
{
	double maxIntersection = 0;
	int left = img.left;
	int right = img.right;
	int top = img.top;
	int bottom = img.bottom;
	if (digit == 1)
	{
		while (right - left + 1 > 2)
		{
			Image dig;
			generateDigit(digit, dig, left, right, top, bottom);
			double intersection = compare(img, dig);
			if (intersection > maxIntersection)
				maxIntersection = intersection;
			right--;
		}
	}
	else
	{
		for (int i = 0; i <= 3/*4 + (img.right - img.left)/4*/; i++)
		{
			for (int y = img.top - top; bottom + y <= img.bottom; y++)
				for (int x = img.left - left; right + x <= img.right; x++)
				{
					Image tmp;
					generateDigit(digit, tmp, left + x, right + x, top + y, bottom + y);
					double intersection = compare(img, tmp);
					if (intersection > maxIntersection)
						maxIntersection = intersection;
				}
		left++;
		right--;
		top++;
		bottom--;
		if (left > right || top > bottom)
			break;
		}
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
	// Считывание изображения
	Image input;
	read(input);

	// Извлечение отдельных объектов
	int DigitsNumber = 0;
	Image object[OBJECTS];
	int i = 0;
	while (readObject(input, object[i]))
	{
		if (i == OBJECTS)
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
	}
	
	//if (DigitsNumber == 1)
	//{
	//	clearImg(object[1]);
	//	devide(object[0], object[1]);
	//	DigitsNumber = 2;
	//}
	//if (DigitsNumber == 2)
	//{
	//	if (object[0].right - object[0].left > object[1].right - object[1].left)
	//	{
	//		object[2] = object[1];
	//		clearImg(object[1]);
	//		devide(object[0], object[1]);
	//	}
	//	else
	//	{
	//		clearImg(object[2]);
	//		devide(object[1], object[2]);
	//	}
	//	DigitsNumber = 3;
	//}
	
	// Распознавание объектов
	for (int j = 0; j < DigitsNumber; j++)
	{
		recognize(object[j]);
	}
	cout << "\n" ;

	//int number = DigitsNumber - 1;
	//write(object[number]);
	//cout << "\n" ;

	//Image Digit;
	////generateDigit(3, object[number], object[number].left, object[number].right, object[number].top, object[number].bottom);
	////write(object[number]);

	//for (int i = 2; i < 3; i++)
	//{
	//	clearImg(Digit);
	//	generateDigit(i, Digit, object[number].left, object[number].right, object[number].top, object[number].bottom);
	//	write(Digit);
	//	cout << "\n\n" ;
	//}

	return 0;
}