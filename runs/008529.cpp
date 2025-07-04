#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;

#define WHITE '.'
#define LIGHT_GRAY '%'
#define DARK_GRAY '#'
#define BLACK '@'

class CompareCoords
{
public:
	bool operator()(pair<size_t, size_t> a, pair<size_t, size_t> b)
	{
		return a.second < b.second || (a.second == b.second && a.first < b.first);
	}
};

class Image
{
	vector<string> pixels;
	size_t width, height;
	static const double distribution_patterns[];

	Image GetSegment(size_t x, size_t y);
	char LocalBinarize(size_t x, size_t y, int radius);
	void PushString(string str);
	bool WhiteNeighbours(size_t x, size_t y);
	bool BlackNeighbours(size_t x, size_t y);
	vector<double> CountDistribution();
	vector<int> VerticalProjection();
	vector<int> HorizontalProjection();

public:
	Image();
	~Image();

	void ReadImage();
	void PrintImage();
	void Binarize();
	void Contraction();
	void Widening();
	vector<Image> Segmentation();
	bool IsGarbage();
	int Predict();
};

const double Image::distribution_patterns[] = {0.25, 0.25, 0.25, 0.25,
		                                       0.5,  0.2,  0.3,  0,
		                                       0.3,  0.2,  0.31, 0.19,
		                                       0.35, 0.15, 0.15, 0.35,
		                                       0.33, 0.33, 0,    0.33,
		                                       0.15, 0.36, 0.14, 0.35,
		                                       0.12, 0.29, 0.3,  0.29,
		                                       0.49, 0.19, 0.3,  0.02,
		                                       0.25, 0.25, 0.25, 0.25,
		                                       0.3,  0.29, 0.12, 0.29};

Image::Image() : pixels()
{
	width = height = 0;
}

Image::~Image()
{

}

char Image::LocalBinarize(size_t x, size_t y, int radius)
{
	vector<int> neighbours;
	size_t cur_coord_x, cur_coord_y;

	for (int i = -radius; i <= radius; i++) {
		for (int k = -radius; k <= radius; k++) {
			cur_coord_y = y + i;
			if (cur_coord_y < 0) cur_coord_y = 0;
			else if (cur_coord_y >= height) cur_coord_y = height - 1;

			cur_coord_x = x + k;
			if (cur_coord_x < 0) cur_coord_x = 0;
			else if (cur_coord_x >= width) cur_coord_x = width - 1;

			switch(pixels[cur_coord_y][cur_coord_x]) {
			case WHITE:
				neighbours.push_back(0);
				break;
			case LIGHT_GRAY:
				neighbours.push_back(1);
				break;
			case DARK_GRAY:
				neighbours.push_back(2);
				break;
			case BLACK:
				neighbours.push_back(3);
				break;
			default:
				break;
			}
		}
	}

	double treshold = (double)accumulate(neighbours.begin(), neighbours.end(), 0) / neighbours.size();
	double value;
	switch(pixels[y][x]) {
	case WHITE:
		value = 0.0;
		break;
	case LIGHT_GRAY:
		value = 1.0;
		break;
	case DARK_GRAY:
		value = 2.0;
		break;
	case BLACK:
		value = 3.0;
		break;
	default:
		break;
	}

	if (value > treshold) return BLACK;
	else return WHITE;
}

bool Image::WhiteNeighbours(size_t x, size_t y)
{
	if (x > 0) {
		if (y > 0) {
			if (pixels[y-1][x-1] == WHITE) return true;
		}
		if (y < height - 1) {
			if (pixels[y+1][x-1] == WHITE) return true;
		}
		if (pixels[y][x-1] == WHITE) return true;
	}
	if (x < width - 1) {
		if (y > 0) {
			if (pixels[y-1][x+1] == WHITE) return true;
		}
		if (y < height - 1) {
			if (pixels[y+1][x+1] == WHITE) return true;
		}
		if (pixels[y][x+1] == WHITE) return true;
	}
	if (y > 0) {
		if (pixels[y-1][x] == WHITE) return true;
	}
	if (y < height - 1) {
		if (pixels[y+1][x] == WHITE) return true;
	}

	return false;
}

bool Image::BlackNeighbours(size_t x, size_t y)
{
	if (x > 0) {
		if (y > 0) {
			if (pixels[y-1][x-1] == BLACK) return true;
		}
		if (y < height - 1) {
			if (pixels[y+1][x-1] == BLACK) return true;
		}
		if (pixels[y][x-1] == BLACK) return true;
	}
	if (x < width - 1) {
		if (y > 0) {
			if (pixels[y-1][x+1] == BLACK) return true;
		}
		if (y < height - 1) {
			if (pixels[y+1][x+1] == BLACK) return true;
		}
		if (pixels[y][x+1] == BLACK) return true;
	}
	if (y > 0) {
		if (pixels[y-1][x] == BLACK) return true;
	}
	if (y < height - 1) {
		if (pixels[y+1][x] == BLACK) return true;
	}

	return false;
}

void Image::PushString(string str)
{
	pixels.push_back(str);
	height++;
	if (height == 1) width = str.length();
}

Image Image::GetSegment(size_t x, size_t y)
{
	Image original_copy(*this);

	list< pair<size_t, size_t> > frontier(1, make_pair(x, y));
	vector< pair<size_t, size_t> > segment;
	pair<size_t, size_t> cur_coord;

	Image answer;

	pixels[y][x] = WHITE;

	while (!frontier.empty()) {
		cur_coord = frontier.front();
		frontier.pop_front();
		segment.push_back(cur_coord);

		//check neighbours
		if (cur_coord.second > 0) {
			if (cur_coord.first > 0) {
				if (pixels[cur_coord.second - 1][cur_coord.first - 1] == BLACK) {  //x-1;y-1
					frontier.push_back(make_pair(cur_coord.first - 1, cur_coord.second - 1));
					pixels[cur_coord.second - 1][cur_coord.first - 1] = WHITE;
				}
			}
			if (cur_coord.first < width - 1) {
				if (pixels[cur_coord.second - 1][cur_coord.first + 1] == BLACK) {  //x+1;y-1
					frontier.push_back(make_pair(cur_coord.first + 1, cur_coord.second - 1));
					pixels[cur_coord.second - 1][cur_coord.first + 1] = WHITE;
				}
			}
			if (pixels[cur_coord.second - 1][cur_coord.first] == BLACK) {  //x;y-1
				frontier.push_back(make_pair(cur_coord.first, cur_coord.second - 1));
				pixels[cur_coord.second - 1][cur_coord.first] = WHITE;
			}
		}

		if (cur_coord.second < height - 1) {
			if (cur_coord.first > 0) {
				if (pixels[cur_coord.second + 1][cur_coord.first - 1] == BLACK) {  //x-1;y+1
					frontier.push_back(make_pair(cur_coord.first - 1, cur_coord.second + 1));
					pixels[cur_coord.second + 1][cur_coord.first - 1] = WHITE;
				}
			}
			if (cur_coord.first < width - 1) {
				if (pixels[cur_coord.second + 1][cur_coord.first + 1] == BLACK) {  //x+1;y+1
					frontier.push_back(make_pair(cur_coord.first + 1, cur_coord.second + 1));
					pixels[cur_coord.second + 1][cur_coord.first + 1] = WHITE;
				}
			}
			if (pixels[cur_coord.second + 1][cur_coord.first] == BLACK) {  //x;y+1
				frontier.push_back(make_pair(cur_coord.first, cur_coord.second + 1));
				pixels[cur_coord.second + 1][cur_coord.first] = WHITE;
			}
		}

		if (cur_coord.first > 0) {
			if (pixels[cur_coord.second][cur_coord.first - 1] == BLACK) {  //x-1;y
				frontier.push_back(make_pair(cur_coord.first - 1, cur_coord.second));
				pixels[cur_coord.second][cur_coord.first - 1] = WHITE;
			}
		}
		if (cur_coord.first < width - 1) {
			if (pixels[cur_coord.second][cur_coord.first + 1] == BLACK) {  //x+1;y
				frontier.push_back(make_pair(cur_coord.first + 1, cur_coord.second));
				pixels[cur_coord.second][cur_coord.first + 1] = WHITE;
			}
		}
		//end check neighbours
	}

	sort(segment.begin(), segment.end(), CompareCoords());

	size_t min_x = segment[0].first, max_x = segment[0].first;
	for (size_t i = 1; i < segment.size(); i++) {
		if (min_x > segment[i].first) min_x = segment[i].first;
		else if (max_x < segment[i].first) max_x = segment[i].first;
	}

	size_t cur_y = segment[0].second;
	size_t start_x, end_x, prev_x = segment[0].first;
	string line;

	start_x = segment.front().first;
	for (size_t k = 0; k < start_x - min_x; k++) line.push_back(WHITE);
	for (size_t i = 0; i < segment.size(); i++) {
		if (segment[i].second != cur_y) {
			cur_y = segment[i].second;
			end_x = segment[i - 1].first;
			line.push_back(BLACK);
			for (size_t k = 0; k < max_x - end_x; k++) line.push_back(WHITE);
			answer.PushString(line);
			line.clear();
			start_x = segment[i].first;
			for (size_t k = 0; k < start_x - min_x; k++) line.push_back(WHITE);
		}
		for (size_t k = prev_x; k < segment[i].first; k++) {
			pixels[segment[i].second][k] = WHITE;
			line.push_back(original_copy.pixels[segment[i].second][k]);
		}
		prev_x = segment[i].first;
	}
	end_x = segment.back().first;
	line.push_back(BLACK);
	for (size_t k = 0; k < max_x - end_x; k++) line.push_back(WHITE);
	answer.PushString(line);

	return answer;
}

void Image::ReadImage()
{
	string input_str;
	cin >> input_str;
	width = input_str.length();

	do {
		pixels.push_back(input_str);
		height++;
		size_t new_width = input_str.length();
		if (new_width != width) throw 1;
	} while (cin >> input_str);
}

void Image::PrintImage()
{
	copy(pixels.begin(), pixels.end(), ostream_iterator<string>(cout, "\n"));
}

void Image::Binarize()
{
	Image original_copy(*this);

	for (size_t i = 0; i < height; i++) {
		for (size_t k = 0; k < width; k++) {
			switch(pixels[i][k]) {
			case WHITE:
			case LIGHT_GRAY:
				pixels[i][k] = WHITE;
				break;
			case DARK_GRAY:
			case BLACK:
				pixels[i][k] = BLACK;
				break;
			default:
				break;
			}
		}
	}
}

void Image::Contraction()
{
	Image original_copy(*this);

	for (size_t i = 0; i < height; i++) {
		for (size_t k = 0; k < width; k++) {
			if (pixels[i][k] == BLACK && original_copy.WhiteNeighbours(k, i)) {
				pixels[i][k] = WHITE;
			}
		}
	}
}

void Image::Widening()
{
	Image original_copy(*this);

	for (size_t i = 0; i < height; i++) {
		for (size_t k = 0; k < width; k++) {
			if (pixels[i][k] == WHITE && original_copy.BlackNeighbours(k, i)) {
				pixels[i][k] = BLACK;
			}
		}
	}
}

vector<Image> Image::Segmentation()
{
	vector<Image> answer;

	for (size_t i = 0; i < width; i++) {
		for (size_t k = 0; k < height; k++) {
			if (pixels[k][i] == BLACK) {
				answer.push_back(GetSegment(i, k));
			}
		}
	}

	return answer;
}

vector<double> Image::CountDistribution()
{
	int first = 0, second = 0, third = 0, fourth = 0, total = 0;

	double mid_height = (double)(height + 1) / 2, mid_width = (double)(width + 1) / 2;


	for (size_t i = 0; i < height; i++) {
		for (size_t k = 0; k < width; k++) {
			if (pixels[i][k] == BLACK) {
				total++;
				if ((double)i <= mid_height) {
					if ((double)k <= mid_width) {
						second++;
					}
					if ((double)k >= mid_width) {
						first++;
					}
				}
				if ((double)i >= mid_height) {
					if ((double)k <= mid_width) {
						third++;
					}
					if ((double)k >= mid_width) {
						fourth++;
					}
				}
			}
		}
	}

	vector<double> ans;
	ans.push_back((double)first  / total);
	ans.push_back((double)second / total);
	ans.push_back((double)third  / total);
	ans.push_back((double)fourth / total);

	return ans;
}

vector<int> Image::VerticalProjection()
{
	vector<int> ans;

	int accum = 0;
	for(size_t i = 0; i < height; i++) {
		accum = 0;
		for (size_t k = 0; k < width; k++) {
			if (pixels[i][k] == BLACK) accum++;
		}
		ans.push_back(accum);
	}

	return ans;
}


vector<int> Image::HorizontalProjection()
{
	vector<int> ans;

	int accum = 0;
	for (size_t k = 0; k < width; k++) {
		accum = 0;
		for (size_t i = 0; i < height; i++) {
			if (pixels[i][k] == BLACK) accum++;
		}
		ans.push_back(accum);
	}

	return ans;
}

bool Image::IsGarbage()
{
	if (height < 15) return true;
	if (width > height + 10) return true;
	int count = 0;
	for (size_t i = 0; i < height; i++) {
		for (size_t k = 0; k < width; k++) {
			if (pixels[i][k] == BLACK) count++;
		}
	}
	if (count < 20) return true;
	return false;
}

int Image::Predict()
{
	vector<double> distribution = CountDistribution();
	double squared_error = 0.0;
	int cur_prediction = 0;
	for (int i = 0; i < 4; i++) {
		squared_error += (distribution[i] - distribution_patterns[i]) * (distribution[i] - distribution_patterns[i]);
	}

	double cur_squared_error = 0.0;
	for (int k = 1; k < 10; k++) {
		cur_squared_error = 0.0;
		for (int i = 0; i < 4; i++) {
			cur_squared_error += (distribution[i] - distribution_patterns[4 * k + i]) * (distribution[i] - distribution_patterns[4 * k + i]);
		}
		if (cur_squared_error < squared_error) {
			squared_error = cur_squared_error;
			cur_prediction = k;
		}
	}

	if (cur_prediction == 0 || cur_prediction == 8) {
		int coloured_pixels = 0;
		for (int i = 0; i <= 1; i++) {
			for (int k = 0; k <= 1; k++) {
				if (pixels[height / 2 + i][width / 2 + k] == BLACK) coloured_pixels++;
			}
			if (pixels[height / 2 + i][0] == BLACK) coloured_pixels--;
			if (pixels[height / 2 + i][width - 1] == BLACK) coloured_pixels--;
		}
		if (coloured_pixels > 0) cur_prediction = 8;
		else cur_prediction = 0;
	}

	return cur_prediction;
}

//main function
int main()
{
	Image img;
	vector<Image> segments;

	img.ReadImage();
	img.PrintImage();
	cout << endl;

	img.Binarize();

	segments = img.Segmentation();

	for (vector<Image>::iterator iter = segments.begin(); iter != segments.end(); ) {
		if (iter->IsGarbage()) iter = segments.erase(iter);
		else ++iter;
	}

	for (size_t i = 0; i < segments.size(); i++) {
		cout << segments[i].Predict();
	}
	cout << endl;

	return 0;
}
