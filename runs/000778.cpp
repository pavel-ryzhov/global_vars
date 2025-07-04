#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <functional>
#include <cmath>
#include <set>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::vector;
using std::find;
using std::find_if;
using std::max;
using std::min;
using std::copy;
using std::transform;
using std::accumulate;
using std::bind2nd;
using std::count;
using std::divides;
using std::fabs;
using std::min_element;
using std::pair;
using std::make_pair;
using std::unary_function;
using std::plus;
using std::max_element;
using std::set;

enum PointColor{
	VOID,
	OUTER
};

enum HolePosition{
	UP,
	DOWN,
	UPDOWN
};

void ColorNonBlack(
		const vector<string> &digit_image,
		int x, int y, 
		vector< vector<PointColor> > *colored_image,
		set< pair<int, int> >  *inner_holes)
{
	if(x < 0 || y < 0 || x >= (int)digit_image[0].size() || y >= (int)digit_image.size() ||
		digit_image[y][x] != '.' || colored_image->at(y)[x] == OUTER)
	{
		return;
	}
	colored_image->at(y)[x] = OUTER;
	if(inner_holes != 0)
	{
		inner_holes->insert(make_pair(x, y));
	}
	ColorNonBlack(digit_image, x + 1, y, colored_image, inner_holes);
	ColorNonBlack(digit_image, x, y + 1, colored_image, inner_holes);
	ColorNonBlack(digit_image, x - 1, y, colored_image, inner_holes);
	ColorNonBlack(digit_image, x, y - 1, colored_image, inner_holes);
}

void PaintOuterSpace(const vector<string> &digit_image, vector< vector<PointColor> > *colored_image)
{
	int x, y;
	for(x = 0, y = 0; y < (int)digit_image.size(); ++y)
	{
		ColorNonBlack(digit_image, x, y, colored_image, 0);
	}
	for(x = digit_image[0].size() - 1, y = 0; y < (int)digit_image.size(); ++y)
	{
		ColorNonBlack(digit_image, x, y, colored_image, 0);
	}
	for(x = 0, y = 0; x < (int)digit_image[0].size(); ++x)
	{
		ColorNonBlack(digit_image, x, y, colored_image, 0);
	}
	for(x = 0, y = digit_image.size() - 1; x < (int)digit_image[0].size(); ++x)
	{
		ColorNonBlack(digit_image, x, y, colored_image, 0);
	}
}

class GetPosition:
	public unary_function<HolePosition, const vector< pair<int, int> >&>
{
	const int mid;
public:
	GetPosition(const int real_mid): mid(real_mid){}
	HolePosition operator()(const set< pair<int, int> > &current_hole)
	{
		int ups = 0, downs = 0;
		for(set< pair<int, int> >::const_iterator i = current_hole.begin(); i !=  current_hole.end(); ++i)
		{
			if(i->second <= mid)
			{
				++ups;
			}
			else
			{
				++downs;
			}
		}
		if(ups >= 2 * downs)
		{
			return UP;
		}
		else if(downs >= 2 * ups)
		{
			return DOWN;
		}
		else
		{
			return UPDOWN;
		}
	}
};

vector<double> GetStatisticsFromHolesAnalyze(vector<int> abc)
{
	vector<double> stat(10, 10.0);
		int a = 0, b = 0, c = 0;
		for(int i = 0; i < (int)abc.size(); ++i)
		{
			if(abc[i] == 0)
			{
				++a;
			}
			else if(abc[i] == 1)
			{
				++b;
			}
			else if(abc[i] == 2)
			{
				++c;
			}
		}
		if(a != 0 && b != 0)
		{
			stat[8] = 0.0;
		}
		else if(a != 0 && b == 0)
		{
			stat[9] = 0.0;
			stat[4] = 0.0;
			stat[3] = 0.0;
		}
		else if(a == 0 && b != 0)
		{
			stat[4] = 0.0;
			stat[6] = 0.0;
			stat[3] = 0.0;
		}
		else if(c != 0)
		{
			stat[4] = 0.0;
			stat[0] = 0.0;
		}
		else
		{
			stat[1] = 0.0;
			stat[2] = 0.0;
			stat[3] = 0.0;
			stat[4] = 0.0;
			stat[5] = 0.0;
			stat[7] = 0.0;
		}
	return stat;
}

vector<string> BuildBoldImage(const vector<string> &digit_image)
{
	vector<string> bold_image(digit_image.size(), string(digit_image[0].size(), '.'));
	for(int y = 0; y < (int)digit_image.size() - 1; ++y)
	{
		for(int x = 1; x < (int)digit_image[0].size() - 1; ++x)
		{
			if(digit_image[y][x] != '.')
			{
				bold_image[y    ][x + 1] = '@';
				bold_image[y + 1][x + 1] = '@';
				bold_image[y + 1][x    ] = '@';
				bold_image[y + 1][x - 1] = '@';
				bold_image[y    ][x - 1] = '@';
				bold_image[y][x] = '@';
			}
		}
	}
	for(int x = 1, y = (int)digit_image.size() - 1; x < (int)digit_image[0].size() - 1; ++x)
	{
		if(digit_image[y][x] != '.')
		{
			bold_image[y][x] = '@';
		}
	}

	return bold_image;
}

vector< set< pair<int, int> > > GetInnerHoles(const vector<string> &digit_image)
{
	vector< vector<PointColor> > colored_image(digit_image.size(), vector<PointColor>(digit_image[0].size(), VOID));
	vector< set< pair<int, int> > >  inner_holes;

	PaintOuterSpace(digit_image, &colored_image);
	for(int y = 0; y < (int)digit_image.size(); ++y)
	{
		for(int x = 0; x < (int)digit_image[0].size(); ++x)
		{
			if(digit_image[y][x] == '.' && colored_image[y][x] != OUTER)
			{
				inner_holes.push_back(set< pair<int, int> >());
				ColorNonBlack(digit_image, x, y, &colored_image, &inner_holes.back());
			}
		}
	}
	return inner_holes;
}

bool IsOneVectorContainsOther(
		const vector< set< pair<int, int> > > first, 
		const vector< set< pair<int, int> > > second)
{
	if(first.empty())
		return true;

	set< pair<int, int> > all;
	for(int i = 0; i < (int)second.size(); ++i)
	{
		all.insert(second[i].begin(), second[i].end());
	}
	for(int hole_num = 0; hole_num < (int)first.size(); ++hole_num)
	{
		if(first[hole_num].size() > 3)
		{
			for(set< pair<int, int> >::const_iterator cur_coord = first[hole_num].begin(); cur_coord != first[hole_num].end(); ++cur_coord)
			{
				if(*all.lower_bound(*cur_coord) != *cur_coord)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool CheckImageMass(const vector<string> digit_image, const double value)
{
	int counter = 0;
	for(int i = 0; i < (int)digit_image.size(); ++i)
	{
		for(int j = 0; j < (int)digit_image[0].size(); ++j)
		{
			switch(digit_image[i][j])
			{
			case '@':
				++counter;
			case '#':
				++counter;
			case '%':
				++counter;
			}
		}
	}
	return (double)counter / (double)(3 * digit_image.size() * digit_image[0].size()) > value;
}

vector<string> LessMass(const vector<string> &digit_image)
{
	vector<string> new_image(digit_image);
	for(int i = new_image.size() - 1; i >= 0; --i)
	{
		for(int j = new_image[0].size() - 1; j >=0; --j)
		{
			if(new_image[i][j] != '@')
			{
				new_image[i][j] = '.';
			}
		}
	}
	return new_image;
}

vector<double> A(const vector<string> &digit_image)
{
	vector< set< pair<int, int> > > inner_holes;
	if(!CheckImageMass(digit_image, 0.7))
		inner_holes = GetInnerHoles(digit_image);
	else
		inner_holes = GetInnerHoles(LessMass(digit_image));
	vector< set< pair<int, int> > > bold_inner_holes  = GetInnerHoles(BuildBoldImage(digit_image));	

	bool normal_contain_bold = IsOneVectorContainsOther(bold_inner_holes, inner_holes);
	bool equal_size = (bold_inner_holes.size() == inner_holes.size());

	vector< set< pair<int, int> > > *inner_holes_to_trust;
	if(normal_contain_bold && bold_inner_holes.size() >= inner_holes.size())
	{
		inner_holes_to_trust = &inner_holes;
	}
	else if(normal_contain_bold && bold_inner_holes.size() < inner_holes.size())
	{
		if(CheckImageMass(digit_image, 0.5))
		{
			inner_holes_to_trust = &inner_holes;
		}
		else
		{
			inner_holes_to_trust = &bold_inner_holes;
		}
	}
	else
	{
		inner_holes_to_trust = &bold_inner_holes;
	}

	vector<int> answer;
	answer.resize(inner_holes_to_trust->size());
	transform(
		inner_holes_to_trust->begin(), inner_holes_to_trust->end(),
		answer.begin(),
		GetPosition((int)digit_image.size() / 2));
	return GetStatisticsFromHolesAnalyze(answer);
}

struct HoleInDigit
{
	vector< pair<int, int> > coordinates_array;
	int position;
	double vertical_size;
};

inline bool NotPoint(string::value_type c)
{
	return c != '.';
}

double GetRightLength(const string &s)
{
	return (double)(find_if(s.rbegin(), s.rend(), NotPoint) - s.rbegin()) / (double)s.size();
}

double GetLeftLength(const string &s)
{
	return (double)(find_if(s.begin(), s.end(), NotPoint) - s.begin()) / (double)s.size();
}

vector<double> CheckRightSmoothness(vector<double> &profile)
{
	int delta = 2;
	vector<double> answer(10, 0.0);
	for(int i = 2; i < (int)profile.size() - 4; ++i)
	{
		if(fabs(profile[i] - profile[i + delta]) > 0.3)
		{
			answer[7] = 10.0;
			answer[0] = 10.0;
			answer[9] = 10.0;
			answer[3] = 10.0;
			answer[8] = 10.0;
			return answer;
		}
	}
	answer[2] = 10.0;
	answer[5] = 10.0;
	answer[6] = 10.0;
	return answer;
}

vector<double> CheckLeftSmoothness(vector<double> &profile)
{
	int delta = 2;
	vector<double> answer(10, 0.0);
	for(int i = 0; i < (int)profile.size() - 2; ++i)
	{
		if(fabs(profile[i] - profile[i + delta]) > 0.3)
		{
			answer[6] = 10.0;
			answer[0] = 10.0;
			return answer;
		}
	}
	answer[4] = 10.0;
	answer[7] = 10.0;
	return answer;
}

bool CheckSmoothness(
		vector<double>::iterator first, 
		vector<double>::iterator second,
		int delta_x, double delta_value)
{
	for(; first != second - delta_x; ++first)
	{
		if(fabs(*first - *(first + delta_x)) > delta_value)
		{
			return false;
		}
	}
	return true;
}

vector<double> CheckProfile(const vector<string> &image)
{
	vector<double> return_array(10, 0.0);
	vector<double> right_profile(image.size());
	transform(
		image.begin(), image.end(),
		right_profile.begin(),
		GetRightLength);
	if(*max_element(
		right_profile.begin() + right_profile.size() / 6,
		right_profile.begin() + right_profile.size() * 5 / 6) > 0.6)
	{
		return_array[0] += 10.0;
		return_array[1] += 10.0;
	}
	if(*max_element(
		right_profile.begin() + right_profile.size() / 6,
		right_profile.begin() + right_profile.size() * 2 / 6) > 0.4)
	{
		return_array[3] += 10.0;
	}
	if(CheckSmoothness(right_profile.begin(), right_profile.begin() + right_profile.size() / 2, 2, 0.25))
	{
		return_array[5] += 10.0;
	}
	else
	{
		return_array[1] += 10.0;
		return_array[3] += 10.0;
	}
	if(CheckSmoothness(right_profile.begin() + right_profile.size() / 2, right_profile.end() , 2, 0.25))
	{
		return_array[2] += 10.0;
	}
	else
	{
		return_array[7] += 10.0;
	}
	if(!CheckSmoothness(right_profile.begin() + right_profile.size() / 2, right_profile.end() , 1, 0.4))
	{
		return_array[1] += 10.0;
		return_array[4] += 10.0;
		return_array[3] += 10.0;
	}

	vector<double> left_profile(image.size());
	transform(
		image.begin(), image.end(),
		left_profile.begin(),
		GetLeftLength);
	if(*max_element(
		left_profile.begin() + left_profile.size() / 6,
		left_profile.begin() + left_profile.size() * 5 / 6) > 0.7)
	{
		return_array[0] += 10.0;
		return_array[6] += 10.0;
		return_array[1] += 10.0;
	}
	if(CheckSmoothness(left_profile.begin(), left_profile.begin() + left_profile.size() / 2, 2, 0.4))
	{
		return_array[7] += 10.0;
	}
	else
	{
		return_array[4] += 10.0;
	}
	if(CheckSmoothness(left_profile.begin() + left_profile.size() / 2, left_profile.end() , 2, 0.3))
	{
		return_array[4] += 10.0;
	}
	else
	{
		return_array[7] += 10.0;
	}

	return return_array;
}

double MatOzh(const string &s)
{
	int mo = 0;
	int num = 0;
	for(int i = 0; i < (int)s.size(); ++i)
	{
		switch(s[i])
		{
		case '@':
		case '#':
		case '%':
			mo += i;
			num += 1;
		}
	}

	return (double)mo / (double)num;
}

double Width(const string &s)
{
	return (double)(s.size() - 
		(find_if(s.rbegin(), s.rend(), NotPoint) - s.rend()) -
		(find_if(s.begin(), s.end(), NotPoint) - s.begin())) / 
		(double)s.size();
}

template<class _Fn2> vector<double> DoSmthg(const vector<string> &digit_image, _Fn2 func)
{
	vector<double> statistics(digit_image.size());
	transform(
		digit_image.begin(), digit_image.end(),
		statistics.begin(),
		func);

	vector<int> lengths(5);
	for(int i = 0, ostatok = digit_image.size() % 5; i < 5; ++i)
	{
		lengths[i] = digit_image.size() / 5 + (ostatok-- > 0 ? 1 : 0);
	}

	vector<int> beginings(6);
	beginings[0] = 0;
	for(int i = 0; i < 5; ++i)
	{
		beginings[i + 1] =  beginings[i] + lengths[i];
	}


	vector<double> five_stat(5);
	for(int i = 0; i < 5; ++i)
	{
		five_stat[i] = accumulate(
			statistics.begin() + beginings[i], 
			statistics.begin() + beginings[i + 1], (double)0.0) /
			(double)lengths[i];
	}
	double five_stat_sum = accumulate(five_stat.begin(), five_stat.end(), (double)0.0);
	for(int i = 0; i < 5; ++i)
	{
		five_stat[i] *= 5.0 / five_stat_sum;
	}


	return five_stat;
}

double DekRange(const vector<double> &current_statistics, const double *sample)
{
	double answer = 0;
	double average_in_sample = 
		accumulate(sample, sample + current_statistics.size(), (double)0.0) / (double)current_statistics.size();
	for(int i = 0; i < (int)current_statistics.size(); ++i)
	{
		answer += fabs(current_statistics[i] - sample[i] / average_in_sample);
	}
	return answer;
}

const double hmo[10][5] =
{
	{1.0, 1.0, 1.0, 1.0, 1.0},
	{0.964361, 1.0089, 1.0089, 1.0089, 1.0089},
	{1.02501, 1.14878, 1.15422, 0.834094, 0.837894},
	{0.777247, 1.15415, 1.14894, 1.1624, 0.757273},
	{0.999019, 0.930455, 0.884168, 1.01627, 1.17008},
	{1.00891, 0.627279, 1.30553, 1.28941, 0.768874},
	{1.00131, 0.67317, 1.09544, 1.12066, 1.10943},
	{1.12918, 1.199, 1.05488, 0.856021, 0.760921},
	{1.12361, 0.982149, 1.01278, 0.997545, 0.883916},
	{0.900332, 0.88525, 1.04394, 1.24623, 0.924242}
};

const double hwidth[10][5] = 
{
	{0.889447, 1.05528, 1.10553, 1.0603, 0.889447},
	{1.00444, 0.973823, 0.973823, 0.973823, 1.07409},
	{1.04867, 1.02975, 0.826782, 0.924652, 1.17016},
	{1.09079, 0.930013, 0.863808, 1.00252, 1.11286},
	{0.853066, 1.01467, 1.15606, 1.09898, 0.877223},
	{1.01036, 0.921041, 0.995634, 1.00891, 1.06406},
	{0.796625, 0.865199, 1.17701, 1.18007, 0.981097},
	{1.2762, 0.978882, 0.918372, 0.917255, 0.909287},
	{0.963254, 1.02868, 0.967029, 1.08491, 0.956127},
	{0.997246, 1.15629, 1.08741, 0.877193, 0.881861}
};

vector<double> GetErrorsArray(const vector<double> &stat, const double sample[10][5])
{
	vector<double> errors(10, 0.0);
	for(int i = 0; i < (int)errors.size(); ++i)
	{
		errors[i] += DekRange(stat, sample[i]);
	}
	transform(
		errors.begin(), errors.end(),
		errors.begin(),
		bind2nd(
			divides<double>(),
			*max_element(errors.begin(), errors.end())));
	return errors;

}

int AnalyzeDigit(const vector<string> &digit_image)
{
	vector<double> errors(10, 0.0);
	
	transform(
		errors.begin(), errors.end(),
		A(digit_image).begin(),
		errors.begin(),
		plus<double>());

	transform(
		errors.begin(), errors.end(),
		CheckProfile(digit_image).begin(),
		errors.begin(),
		plus<double>());

	vector<double> hmatozh_stat = DoSmthg(digit_image, MatOzh);
	transform(
		errors.begin(), errors.end(),
		GetErrorsArray(hmatozh_stat, hmo).begin(),
		errors.begin(),
		plus<double>());

	vector<double> hwidth_stat = DoSmthg(digit_image, Width);
	transform(
		errors.begin(), errors.end(),
		GetErrorsArray(hwidth_stat, hwidth).begin(),
		errors.begin(),
		plus<double>());
	
	return (int)(min_element(errors.begin(), errors.end()) - errors.begin());
}

/*int AnalyzeDigit(const vector<string> &digit_image)
{
	vector<double> errors(10, 0.0);
	
	transform(
		errors.begin(), errors.end(),
		A(digit_image).begin(),
		errors.begin(),
		plus<double>());
	for(int i = 0; i < 10; ++i)
	{
		cout << errors[i] << ' ';
	}
	cout << endl;

	transform(
		errors.begin(), errors.end(),
		CheckProfile(digit_image).begin(),
		errors.begin(),
		plus<double>());
	for(int i = 0; i < 10; ++i)
	{
		cout << errors[i] << ' ';
	}
	cout << endl;

	vector<double> hmatozh_stat = DoSmthg(digit_image, MatOzh);
	transform(
		errors.begin(), errors.end(),
		GetErrorsArray(hmatozh_stat, hmo).begin(),
		errors.begin(),
		plus<double>());
	for(int i = 0; i < 10; ++i)
	{
		cout << errors[i] << ' ';
	}
	cout << endl;

	vector<double> hwidth_stat = DoSmthg(digit_image, Width);
	transform(
		errors.begin(), errors.end(),
		GetErrorsArray(hwidth_stat, hwidth).begin(),
		errors.begin(),
		plus<double>());
	for(int i = 0; i < 10; ++i)
	{
		cout << errors[i] << ' ';
	}
	cout << endl;
	
	return (int)(min_element(errors.begin(), errors.end()) - errors.begin());
}*/

struct RawImage{
	vector<string> image_array;
	int left_bound;
	int right_bound;
	int upper_bound;
	int down_bound;
};

void AddPointToImage(
		vector<string> &image,
		int x, int y,
		bool is_not_black,
		RawImage *image_to_add)
{
	if(image[y][x] == '.')
	{
		return;
	}
	image_to_add->image_array.at(y)[x] = image[y][x];
	image[y][x] = '.';
	image_to_add->down_bound = max(y, image_to_add->down_bound);
	image_to_add->upper_bound = min(y, image_to_add->upper_bound);
	image_to_add->left_bound = min(x, image_to_add->left_bound);
	image_to_add->right_bound = max(x, image_to_add->right_bound);
	if(image_to_add->image_array.at(y)[x] == '@' || image_to_add->image_array.at(y)[x] == '#')
	{
		AddPointToImage(image, x + 1, y, false, image_to_add);
		AddPointToImage(image, x + 1, y + 1, false, image_to_add);
		AddPointToImage(image, x, y + 1, false, image_to_add);
		AddPointToImage(image, x - 1, y + 1, false, image_to_add);
		AddPointToImage(image, x - 1, y, false, image_to_add);
		AddPointToImage(image, x - 1, y - 1, false, image_to_add);
		AddPointToImage(image, x, y - 1, false, image_to_add);
		AddPointToImage(image, x + 1, y - 1, false, image_to_add);
	}
}

vector<string> CutSpaces(const RawImage &image)
{
	vector<string> ret_val(image.down_bound - image.upper_bound + 1, string(image.right_bound - image.left_bound + 1, 0));
	for(int i = 0; i < (int)ret_val.size(); ++i)
	{
		copy(
			image.image_array[image.upper_bound + i].begin() + image.left_bound,
			image.image_array[image.upper_bound + i].begin() + image.right_bound + 1,
			ret_val[i].begin());
	}

	return ret_val;
}

void AddLightGray(vector<string> &image, RawImage &digit_image)
{
	for(int i = digit_image.upper_bound; i <= digit_image.down_bound; ++i)
	{
		for(int j = digit_image.left_bound; j < digit_image.right_bound; ++j)
		{
			if( image[i][j] == '%' && (
				NotPoint(digit_image.image_array[i][j - 1]) ||
				NotPoint(digit_image.image_array[i - 1][j - 1]) ||
				NotPoint(digit_image.image_array[i - 1][j]) ||
				NotPoint(digit_image.image_array[i - 1][j + 1]) ||
				NotPoint(digit_image.image_array[i][j + 1])))
			{
				image[i][j] = '.';
				digit_image.image_array[i][j] = '%';
			}	
		}
	}
}

void ErasePoint(
		vector<string> &image,
		int x, int y)
{
	if(image[y][x] == '.')
	{
		return;
	}
	image[y][x] = '.';
	if(x < (int)image[0].size() - 1)
		ErasePoint(image, x + 1, y);
	if(x < (int)image[0].size() - 1 && y < (int)image.size() - 1)
		ErasePoint(image, x + 1, y + 1);
	if(y < (int)image.size() - 1)
		ErasePoint(image, x, y + 1);
	if(x > 0 && y < (int)image.size() - 1)
		ErasePoint(image, x - 1, y + 1);
	if(x > 0)
		ErasePoint(image, x - 1, y);
	if(x > 0 && y > 0)
		ErasePoint(image, x - 1, y - 1);
	if(y > 0)
		ErasePoint(image, x, y - 1);
	if(x < (int)image[0].size() - 1 && y > 0)
		ErasePoint(image, x + 1, y - 1);
}

vector<string> CheckRamka(const vector<string> &digit_image)
{
	vector<string> digit_image_copy(digit_image);
	ErasePoint(
		digit_image_copy, 
		find_if(digit_image_copy[0].begin(), digit_image_copy[0].end(), NotPoint) - digit_image_copy[0].begin(),
		0);
	if(digit_image_copy == vector<string>(digit_image.size(), string(digit_image[0].size(), '.')))
	{
		return vector<string>(digit_image);
	}
	else
	{
		int upper_bound;
		for(unsigned int i = 0; i < digit_image_copy.size(); ++i)
		{
			if(find_if(digit_image_copy[i].begin(), digit_image_copy[i].end(), NotPoint) != digit_image_copy[i].end())
			{
				upper_bound = i;
				break;
			}
		}
		int lower_bound;
		for(unsigned int i = digit_image_copy.size() - 1; i > 0; --i)
		{
			if(find_if(digit_image_copy[i].begin(), digit_image_copy[i].end(), NotPoint) != digit_image_copy[i].end())
			{
				lower_bound = i;
				break;
			}
		}
		int left_bound = digit_image_copy[0].size();
		for(int i = upper_bound; i <= lower_bound; ++i)
		{
			left_bound = min(
				left_bound,
				find_if(digit_image_copy[i].begin(), digit_image_copy[i].end(), NotPoint) - digit_image_copy[i].begin());
		}
		int right_bound = 0;
		for(int i = upper_bound; i <= lower_bound; ++i)
		{
			right_bound = max(
				right_bound,
				(int)(digit_image_copy[i].size() - 1 -
				(find_if(digit_image_copy[i].rbegin(), digit_image_copy[i].rend(), NotPoint) - digit_image_copy[i].rbegin())));
		}
		vector<string> return_value(lower_bound - upper_bound + 1, string(right_bound - left_bound +1, '.'));
		for(int i = upper_bound; i <= lower_bound; ++i)
		{
			copy(
				digit_image_copy[i].begin() + left_bound,
				digit_image_copy[i].begin() + right_bound + 1,
				return_value[i - upper_bound].begin());
		}
		return return_value;
	}
}

vector<string> GetDigit(vector<string> &image)
{
	RawImage digit_image;
	digit_image.image_array.reserve(image.size());
	for(int i = image.size(); i > 0; --i)
	{
		digit_image.image_array.push_back(string(image[0].size(), '.'));
	}
	digit_image.left_bound = image[0].size();
	digit_image.right_bound = 0;
	digit_image.upper_bound = image.size();
	digit_image.down_bound = 0;

	int point_of_image_x = image[0].size();
	for(int i = image.size() / 2 - 2; i <= image.size() / 2 + 2; ++i)
	{
		point_of_image_x = min(
			point_of_image_x,
			find(image[i].begin(), image[i].end(), '@') - image[i].begin());
	}
	if(point_of_image_x == image[0].size())
		return vector<string>();
	for(int i = 0; i < (int)image.size(); ++i)
	{
		if(image[i][point_of_image_x] == '@')
		{
			AddPointToImage(
				image,
				point_of_image_x,
				i,
				true,
				&digit_image);
		}
	}

	AddLightGray(image, digit_image);

	return CheckRamka(CutSpaces(digit_image));
}

int Scan(const vector<string> &image)
{
	int answer = 0;
	vector<string> operational_image = image;
	
	vector<string> first_digit = GetDigit(operational_image);
	vector<string> second_digit = GetDigit(operational_image);
	vector<string> third_digit = GetDigit(operational_image);

	answer += AnalyzeDigit(first_digit);
	if(!second_digit.empty())
	{
		answer *= 10;
		answer += AnalyzeDigit(second_digit);
	}
	if(!third_digit.empty())
	{
		answer *= 10;
		answer += AnalyzeDigit(third_digit);
	}
	return answer;
}

vector<string> Input()
{
	vector<string> image;

	while(true)
	{
		string bolvanka;
		cin >> bolvanka;
		if(find_if(bolvanka.begin(), bolvanka.end(), NotPoint) - bolvanka.begin() != bolvanka.size())
		{
			image.push_back(string(bolvanka.size(), '.'));
			image.push_back(bolvanka);
			break;
		}
	}
	while(true)
	{
		image.push_back(string());
		cin >> image.back();
		if (find_if(image.back().begin(), image.back().end(), NotPoint) - 
			image.back().begin() == image.back().size())
		{
			break;
		}
	}

	return image;
}

int main()
{
	vector<string>	image = Input();
	cout << Scan(image) << endl;
	return 0;
}
