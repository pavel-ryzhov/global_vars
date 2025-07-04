#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <math.h>

double sqr(double a) {
	return a * a;
}

double d_abs(double a) {
	return a >= 0.0 ? a : -a;
}

template< class A >
A max(A a, A b) {
	return a >= b ? a : b;
}

template< class A >
A min(A a, A b) {
	return a <= b ? a : b;
}

class image {
public:
	image() {};
	~image();
	void insertLine(const std::string& line);
	const std::string result();

	void printHorizontals();
	void printVerticals();
private:
	enum SState {SBegin, SInside, SEnd};

	void operator= (const image&);
	image(const image& from);

	std::vector< std::pair< int*, int> > lines;

	// ограничиваем области горизонтальными линиями
	void verticalRestrict(int firstColumn, int lastColumn, int& begin, int& end);
	// проверяет периметр изображения на присутствие не-белых точек (для удаления рамок)
	bool checkFrameForFull(int x1, int y1, int x2, int y2);
	// строит вертикальные гистограммы (суммирует элементы вертикально)
	int* verticalSums(int x1, int y1, int x2, int y2);
	// строит горизонтальные гистогрыммы (суммирует элементы горизонтально)
	int* horizontalSums(int x1, int y1, int x2, int y2);
	// ищем само число
	int parseNumber(int firstColumn, int lastColumn, int firstLine, int lastLine);

	struct LineInfo {
		int first;
		int last;
		bool space;
		int firstSpace;
		int lastSpace;
	};
};

// Сортируются по длине
struct Segment {
	int a;
	int b;
	int value;
	Segment(int a1, int b1, int n) : a(a1), b(b1), value(n) {}
};

bool SortSegmentByWidth(const Segment& first, const Segment& second) {
	return first.b - first.a > second.b - second.a;
}

bool SortSegmentByValue(const Segment& first, const Segment& second) {
	return first.value < second.value;
}

int main() {
	image all;
	
	std::string s_buffer;

	while(std::cin.good() && !std::cin.fail()) {
		//std::cin.getline(buffer, 1000);
		//s_buffer.assign(buffer);
		std::getline(std::cin, s_buffer);
		if(s_buffer.length() == 0) {
			break;
		}
		all.insertLine(s_buffer);
	}

	all.printVerticals();
	return 0;
}

image::~image() {
	for(size_t x = 0; x < lines.size(); x++) {
		delete lines[x].first;
	}
}

void image::insertLine(const std::string& line) {
	size_t len = line.length();
	int* iline;
	lines.push_back(std::make_pair(iline = new int[len], len));
	for(size_t x = 0; x < len; x++) {
		char tmp = line[x];
		switch(tmp) {
		case '.':
			iline[x] = 0;
			break;
		case '%':
			iline[x] = 1;
			break;
		case '#':
			iline[x] = 2;
			break;
		case '@':
		default:
			iline[x] = 3;
		}
	}
}

// void image::printHorizontals() {
// 	for(size_t i = 0; i < lines.size(); i++) {
// 		int sum = 0;
// 		for(int k = 0; k < lines[i].second; k++) {
// 			sum += lines[i].first[k];
// 		}
// 		std::cout << sum << std::endl;
// 	}
// }

void image::printVerticals() {
	size_t width = lines[0].second;
	int* sums = new int[width];
	for(size_t x = 0; x < width; x++) {
		sums[x] = 0;
	}
	for(size_t x = 0; x < lines.size(); x++) {
		for(size_t y = 0; y < width; y++) {
			sums[y] += lines[x].first[y];
		}
	}

	std::vector< Segment > segments;
	std::vector< Segment > segments2;

	SState state = SBegin;
	int begin;
	int end;
	int c_max;
	
	int number = 0;

	for(size_t x = 0; x < width; x++) {
		int tmp = sums[x];
		if(state == SBegin) {
			if(tmp <= 6) {
				continue;
			}
			begin = x;
			c_max = tmp;
			state = SInside;
		} else { // state == SInside
			if(tmp <= max(4, c_max/15)) {
				end = x;
				state = SBegin;

				double center = (double(begin) + double(end))/2.0;
				double left_total = 0.0;
				double right_total = 0.0;
				for(int i = (begin + end) / 2; i >= begin; i--) {
					left_total += double(sums[i])/(1 + center - i);
				}
				for(int i = (begin + end) / 2; i <= end; i++) {
					right_total += double(sums[i])/(1 + i - center);
				}

				segments.push_back(Segment(begin, end, 10 * ++number));
			} else {
				c_max = max(c_max, tmp);
			}
		}	
	}

	delete sums;

	std::sort(segments.begin(), segments.end(), SortSegmentByWidth);

	if(segments.size() == 1) {
		int a = segments[0].a;
		int b = segments[0].b;
		int diff = (b - a) / 3;
		segments2.push_back(Segment(a, a + diff, 0));
		segments2.push_back(Segment(a + diff, b - diff, 1));
		segments2.push_back(Segment(b - diff, b, 2));
	} else if(segments.size() == 2) {
		int a = segments[0].a;
		int b = segments[0].b;
		int diff = (b - a) / 2;
		segments2.push_back(Segment(a, a + diff, segments[0].value));
		segments2.push_back(Segment(b - diff, b, segments[0].value + 1));
		segments2.push_back(segments[1]);
		std::sort(segments2.begin(), segments2.end(), SortSegmentByValue);
	} else {
		int count = 0;
		for(std::vector< Segment >::const_iterator i = segments.begin(); count < 3 && i != segments.end(); i++) {
			segments2.push_back(*i);
			count++;
		}
		std::sort(segments2.begin(), segments2.end(), SortSegmentByValue);
	}

	for(std::vector< Segment >::const_iterator i = segments2.begin(); i != segments2.end(); i++) {
		int x1 = i->a, x2 = i->b, y1, y2;
		verticalRestrict(x1, x2, y1, y2);
		// ищем рамку (если такая есть)
		for(int step = 1; x2 - x1 - 2 * step > 8 && y2 - y1 - 2 * step > 8; step++) {
			if(!checkFrameForFull(x1 + step, y1 + step, x2 - step, y2 - step)) {
				int* h = horizontalSums(x1 + step, y1 + step, x2 - step, y2 - step);
				int h_size = y2 - y1 - 2 * step;
				int* v = verticalSums(x1 + step, y1 + step, x2 - step, y2 - step);
				int v_size = x2 - x1 - 2 * step;

				x1 = x1 + step;
				for(int i = 0; v[i] == 0; i++, x1++);
				x2 = x2 - step;
				for(int i = v_size - 1; v[i] == 0; i--, x2--);
				y1 = y1 + step;
				for(int i = 0; h[i] == 0; i++, y1++);
				y2 = y2 - step;
				for(int i = h_size - 1; h[i] == 0; i--, y2--);

				delete h;
				delete v;
				break;
			}
		}
		std::cout << parseNumber(x1, x2, y1, y2);
		//std::cout << (i->a + 1) << " " << (i->b + 1) << " " << a << " " << b << std::endl;
		//std::cout << std::endl;
	}
}

void image::verticalRestrict(int firstColumn, int lastColumn, int& begin, int& end) {
	size_t len = lines.size();
	int* sums = new int[len];

	for(size_t i = 0; i < len; i++) {
		sums[i] = 0;
		for(int x = firstColumn; x < lastColumn; x++) {
			sums[i] += lines[i].first[x];
		}
	}

	size_t off = 0;
	while(off < len) {
		for(begin = off; begin < len && sums[begin] < 2; begin++);
		for(end = begin; end < len && sums[end] >= 2; end++);
		// проверяем на шум
		if(end - begin < 2) {
			off = end + 1;
			continue;
		}
		break;
	}

	delete sums;
}

bool image::checkFrameForFull(int x1, int y1, int x2, int y2) {
	std::pair< int*, int >& first = lines[y1];
	std::pair< int*, int >& second = lines[y2];
	for(int x = x1; x < x2; x++) {
		if(first.first[x] || second.first[x]) {
			return true;
		}
	}
	for(int y = y1 + 1; y < y2 - 1; y++) {
		if(lines[y].first[x1] || lines[y].first[x2]) {
			return true;
		}
	}
	return false;
}

int* image::verticalSums(int x1, int y1, int x2, int y2) {
	int size = x2 - x1;
	int* result = new int[size];
	for(int i = 0; i < size; i++) {
		result[i] = 0;
	}
	for(int y = y1; y < y2; y++) {
		std::pair< int*, int >& w = lines[y];
		for(int x = 0; x < size; x++) {
			result[x] += w.first[x + x1];
		}
	}
	return result;
}

int* image::horizontalSums(int x1, int y1, int x2, int y2) {
	int size = y2 - y1;
	int* result = new int[size];
	for(int y = 0; y < size; y++) {
		std::pair< int* , int >& w = lines[y + y1];
		result[y] = 0;
		for(int x = x1; x < x2; x++) {
			result[y] += w.first[x];
		}
	}
	return result;
}

int image::parseNumber(int firstColumn, int lastColumn, int firstLine, int lastLine) {
	// пока просто выводим область на экран
	int size = lastLine - firstLine;
	std::vector< Segment > fal; // first and last (строим ширину цифры)
	fal.assign(size, Segment(0, 0, 0));

	double mid_width = 0.0;

	for(int i = 0; i < size; i++) {
		Segment& val = fal[i];
		std::pair< int*, int >& w = lines[i + firstLine];
		for(int x = firstColumn; x < lastColumn; x++) {
			int tmp = w.first[x];
			if(tmp > 0) {
				if(val.a == 0) {
					val.a = x;
				}
				val.b = x;
				val.value++;
			}
		}
		mid_width += val.b - val.a;
	}
	mid_width /= size;

// 	for(int i = firstLine; i < lastLine; i++) {
// 		for(int x = firstColumn; x < lastColumn; x++) {
// 			switch(lines[i].first[x]) {
// 				case 0:
// 					std::cout << '.';
// 					break;
// 				case 1:
// 					std::cout << '%';
// 					break;
// 				case 2:
// 					std::cout << '#';
// 					break;;
// 				case 3:
// 					std::cout << '@';
// 			}
// 		}
// 		std::cout << std::endl;
// 	}
// 	std::cout << std::endl;
	
	{// проверка на 1 (полностью)
		int count = 0;
		for(int i = 3; i < size - 2; i++) {
			Segment& seg = fal[i];
			double diff = d_abs(seg.b - seg.a - mid_width)/mid_width;
			if(diff <= 0.15) {
				count++;
			}
		}
		if(count >= (size - 5) * 7 / 10) {
			//std::cout << '1';
			return 1;
		}
	}
	{// проверка на 7 (полностью)
		int index = 0;
		int bad = 0;
		for(; index < size && fal[index].b - fal[index].a < 1.15 * mid_width; index++, bad++);
		for(; index < size && fal[index].b - fal[index].a >= 1.15 * mid_width; index++);
		for(; index < size && fal[index].b - fal[index].a < 1.4 * mid_width; index++);
		bad += size - index;
		if(bad < size / 8) {
			//std::cout << '7';
			return 7;
		}
	}
	{// проверка на 4 (полностью)
		int total = 0, count = 0;
		for(int i = size - 1; i > size * 4 / 5; i--) {
			total++;
			if(fal[i].b - fal[i].a < 0.8 * mid_width) {
				count++;
			}
		}
		if(count > total * 2 / 3) {
			int index = 0;
			for(; index < size && fal[index].b - fal[index].a < mid_width;index++);
			if(index > size * 4 / 25) {
				//std::cout << '4';
				return 4;
			}
		}
	}
	{// проверка на 2 (полностью)
		int total = 0, count = 0, count2 = 0;
		for(int i = size - 1; i > size * 5 / 6; i--) {
			total++;
			if(fal[i].b - fal[i].a > 1.2 * mid_width) {
				count++;
				if(fal[i].b - fal[i].a - fal[i].value < 4) {
					count2++;
				}
			}
		}
		if(count >= total * 2 / 3 && count2 >= total * 2/ 3) {
			total = 0;
			count = 0;
			for(int i = 0; i < size / 3; i++) {
				total++;
				if(fal[i].b - fal[i].a > 1.2 * mid_width) {
					count++;
				}
			}
			if(count >= total / 3) {
				///std::cout << '2';
				return 2;
			}
		}
	}
	{// проверка на 0, 6 и 9 (полностью)
		int last_a = fal[0].a;
		int last_b = fal[0].b;
		int index1 = 1, index2 = 1;
		for(; index1 < size && fal[index1].a <= last_a; last_a = fal[index1].a, index1++);
		for(; index1 < size && fal[index1].a >= last_a; last_a = fal[index1].a, index1++);
		
		for(; index2 < size && fal[index2].b >= last_b; last_b = fal[index2].b, index2++);
		for(; index2 < size && fal[index2].b <= last_b; last_b = fal[index2].b, index2++);
		
		bool left = index1 > size * 9 / 10;
		bool right = index2 > size * 9 / 10;
		if(left) {
			if(right) {
				//std::cout << '0';
				return 0;
			} else {
				//std::cout << '6';
				return 6;
			}
		} else if(right) {
			//std::cout << '9';
			return 9;
		}
	}
	{// проверка на 5, 8 и 3 (полностью)
		int cle_top = 0; // count left error top
		int cre_top = 0; // count right error top
		int cle_bottom = 0; // count left error bottom
		int cre_bottom = 0; // count right error bottom

		int middle = (firstColumn + lastColumn) / 2;

		bool skip = true;
		for(int i = 0; i < size / 2; i++) {
			if(fal[i].a > middle + 1) {
				if(skip) {
					continue;
				}
				cle_top++;
			} else if(fal[i].b < middle - 1) {
				if(skip) {
					continue;
				}
				cre_top++;
			} else {
				skip = false;
			}
		}

		skip = true;
		for(int i = size - 1; i >= size / 2; i--) {
			if(fal[i].a > middle + 1) {
				if(skip) {
					continue;
				}
				cle_bottom++;
			} else if(fal[i].b < middle - 1) {
				if(skip) {
					continue;
				}
				cre_bottom++;
			} else {
				skip = false;
			}
		}

		if(cre_top >= size / 20 || cle_bottom >= size / 4) {
			//std::cout << '5';
			return 5;
		}
		if(cle_top >= size / 20 || cle_bottom >= size / 20) {
			//std::cout << '3';
			return 3;
		}
	}

	//std::cout << '8';
	return 8;
}
