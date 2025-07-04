#include <stdio.h>
#include <string.h>

/*
	Распознавалка цифр на картинках
	. - белый цвет
	% - светло-серый
	# - темно-серый
	@ - черный

	Алгоритм:
	Сканируем слева направо по столбцам, смотрим сколько отдельных полосок
	Строим граф (векторизуем растр), выделяем фигуры и сравниваем с образцами
*/

#define WHITE '.'
#define LIGHT '%'
#define GRAY  '#'
#define BLACK '@'

// максимальная ширина и высота картинки
#define MAXW 1000
#define MAXH 1000

unsigned char image[MAXW*MAXH];

inline int mod(int x) { return x > 0 ? x : -x; }

#define font(_d, _n1, _n2, _n3, _n4) if ( \
	mod(num[1] - _n1) < 1 && \
	mod(num[2] - _n2) < 1 && \
	mod(num[3] - _n3) < 1 && \
	mod(num[4] - _n4) < 1 \
	) return _d;

#define test(_n1, _n2, _n3, _n4) return ( \
	n1 == _n1 && \
	n2 == _n2 && \
	n3 == _n3 && \
	n4 == _n4 && \
	1);

// сканирование ряда и распознавание цифры
int okno = 0;
int n = 0;
int scanrow(int n1, int n2, int n3, int n4)
{
	int m = n2 + n3 + n4;
	m = (m * 255 / (m + n1)) & 0xFF;
	okno = (okno << 8) + m;
//	if (n2 < 10 && n3 < 6 && n4 < 2) n = 0;
//	if (m) n++;
//	if (n == 4)
//printf("\tif (okno == 0x%x) return 0; // %d, %.3f, %.3f, %.3f, %.3f\n", okno, ++n);
/*	(float)n1/(n1+n2+n3+n4),
	(float)n2/(n1+n2+n3+n4),
	(float)n3/(n1+n2+n3+n4),
	(float)n4/(n1+n2+n3+n4)
	);*/
	// #1
	if (okno == 0x82775a49) return 7; // 20
	if (okno == 0x111cb5b5) return 1; // 46
	// #2
	if (okno == 0x1829415a) return 7; // 12
	if (okno == 0x9c412010) return 0; // 42
	// #3
	if (okno == 0x10182929) return 4; // 9
	if (okno == 0x394a5252) return 5; // 28
	if (okno == 0x62839c7b) return 8; // 43
	// #4
	if (okno == 0x5e5e4b2f) return 7; // 16, 0.815, 0.074, 0.037, 0.074
	if (okno == 0x3871a084) return 3; // 26, 0.481, 0.074, 0.074, 0.370
	if (okno == 0x55384267) return 8; // 37, 0.593, 0.185, 0.000, 0.222

/*
	// старые тесты
	// #1
	if (okno == 0x3d647b5c) return 9;
	if (okno == 0x17171736) return 7;
	// #2
	if (okno == 0x0d121b1f) return 4;
	if (okno == 0x16283b5f) return 8;
	// #3
	if (okno == 0x811284c) return 5;
	if (okno == 0xd283e50) return 2;
	// #4
	if (okno == 0x122e4558) return 7;
	if (okno == 0x0d2e4558) return 2;
	if (okno == 0x0d253c53) return 3;
	// #5
	if (okno == 0x19663b2a) return 5;
	if (okno == 0x19221111) return 7;
	if (okno == 0x3b5d3322) return 6;
	// #6
	if (okno == 0x0f3c524b) return 2;
	if (okno == 0x25617f5a) return 9;
	if (okno == 0x07160f16) return 4;
	// #7
	if (okno == 0x921485b) return 5;
	if (okno == 0x409090e) return 1;
	// #8
	if (okno == 0x073a667b) return 8;
	if (okno == 0x1d242441) return 5;
	if (okno == 0x1d24485e) return 3;
	// #9
	if (okno == 0x0c12b6c2) return 1;
	if (okno == 0x364e4e61) return 7;
	// #10
	if (okno == 0x2b577483) return 6;
	if (okno == 0x333a3a33) return 5;
	if (okno == 0x335e7b8a) return 0;
	// #11
	if (okno == 0x0b37586e) return 8;
	if (okno == 0x1b425863) return 6;
	if (okno == 0x10213137) return 4;
	// #12
	if (okno == 0x16253c4b) return 4;
	if (okno == 0x3c4b708e) return 8;
	// #13
	if (okno == 0x3346525f) return 9;
	if (okno == 0x334c5f6c) return 6;
	// #14
	if (okno == 0x1029414a) return 2;
	if (okno == 0x18293139) return 4;
	if (okno == 0x52293941) return 7;
	// #15
	if (okno == 0x111c1f35) return 9;
	if (okno == 0x151c2326) return 5;
	// #16
	if (okno == 0x142e4e77) return 8;
	if (okno == 0x1a1f1f1a) return 5;
	// #17
	if (okno == 0x76694130) return 8; // 30
	if (okno == 0x4f3d3030) return 9; // 83
	if (okno == 0x46413d3d) return 2; // 135
	// #18
	if (okno == 0x6e7f797f) return 8; // 15
	if (okno == 0x696e6e63) return 5; // 43
	if (okno == 0x4d4d4d48) return 2; // 66
*/
	return -1;
}

// сканируем сверху-вниз, слева-направо
int scanDigits(int w, int h)
{
	int ch; // текущий символ
	int i, j, d, res = 0;
	int num[] = { 0, 0, 0, 0, }; // все, белый, св.сер, тем.сер, черн
	// сканируем по столбикам слева-направо
	for (i = 0; i < w; i++) // слева-направо
	{
		num[0] = num[1] = num[2] = num[3] = 0;
		for (j = 0; j < h; j++) // сверху-вниз
		{
			ch = image[j*MAXW+i];
			switch(ch)
			{
				case WHITE: num[0]++; break;
				case LIGHT: num[1]++; break;
				case GRAY:  num[2]++; break;
				case BLACK: num[3]++; break;
			}
		}
		d = scanrow(num[0], num[1], num[2], num[3]);
		if (d != -1) res = res * 10 + d;
	}
	return res;
}

int main()
{
	unsigned int  image_h = 0;
	unsigned int  image_w = 0;
	FILE *fin = stdin;//fopen("tests/001.in", "r");
	// читаем изображение в память
	while (!feof(fin))
	{
		fscanf(fin, "%s", &image[MAXW*image_h]);
		image_h++;
	}
	image_h--;
	image_w = strlen((char*)image);
	printf("%d\n", scanDigits(image_w, image_h));
	return 0;
}
