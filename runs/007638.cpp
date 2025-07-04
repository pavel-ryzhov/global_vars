#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>



const short WHITE = 0;
const short ALMOST_ZERO = 5;
const short EXTRA_LIGHT = 20;
const short LIGHT = 50;
const short DARK = 70;
const short BLACK = 99;

const int FINDS_NEEDED = 4;
const int HORISONTAL_EDGE = 7;
const int VERTICAL_EDGE = 8;
const int SAMPLE_SIZE = 50;
const int SAMPLES_COUNT = 12;
const double PRECISION = 0.12;
const double SEPARATE = 0.6;

typedef std::vector<short> Line;
typedef std::vector<Line> Matrix;
typedef std::pair<char, Matrix> MatrixInfo;
typedef std::vector<MatrixInfo> VMI;

VMI precomp_info;

struct Teach_Encode
{
	short operator()(char c) const
	{
		if (c == '.')
			return WHITE;
		else if (c == 39)	//Символ '
			return ALMOST_ZERO;
		else if (c == '~')
			return EXTRA_LIGHT;
		else if (c == '%')
			return LIGHT;
		else if (c == '#')
			return DARK;
		else 
			return BLACK;
	}
};

void fill0(Matrix& m)
{

	char c[30][22] = 
	{"..~~%##########%~~...",
	".~~%#@@@@@@@@@@#%~~..",
	"~~%#@@########@@#%~~.",
	"~%#@@#%%%%%%%%#@@#%~.",
	"%#@@#%%%%~~..%%#@@#%.",
	"%#@@#%%%~~....%#@@#%.",
	"#@@#%%%%'......%#@@#.",
	"#@@#%%%%'.....'~%#@#.",
	"#@@#%%%%'.....'~%#@#.",
	"#@@#%%%%'.....'~%#@#.",
	"#@@#%%%%'.....'~%#@#.",
	"#@@#%%%%'.....'~%#@#.",
	"#@@#%%%%'.....'~%#@#.",
	"#@@#%%%%'.....'~%#@#.",
	"#@@#%%%%'.....'~%#@#.",
	"#@@@#%%%'.....'~%#@#.",
	"#@@@#%%%'.....'~%#@#.",
	"#@@@#%%%'.....'~%#@#.",
	"#@@@#%%%'.....'~%#@#.",
	"#@@@#%%%'.....'~%#@#.",
	"#@@@#%%%'.....'~%#@#.",
	"#@@@#%%%'.....'~%#@#.",
	"#@@@#%%%'.....'~##@#.",
	"#@@##%%%'....~.%#@@#.",
	"%#@@#%%%~''.~.%#@@#%.",
	"%#@@#%%%%~~~.%%#@@#%.",
	"~%#@@#%%%%%%%%#@@#%~.",
	"~~%#@@########@@#%~~.",
	".~~%#@@@@@@@@@@#%~~..",
	"..~~%##########%~~..."};
	for (int x = 0; x < 30; ++x)
		std::transform(&c[x][0], &c[x][21], m[x].begin(), Teach_Encode() );
	m.push_back(Line() );
	m[m.size() - 1].assign(SAMPLE_SIZE, 0);
}

void fill1(Matrix& m)
{
	char c[30][22] = 
	{"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################.",
	"####################."};
	for (int x = 0; x < 30; ++x)
		std::transform(&c[x][0], &c[x][21], m[x].begin(), Teach_Encode() );
	m.push_back(Line() );
	m[m.size() - 1].assign(SAMPLE_SIZE, 0);
}

void fill2(Matrix& m)
{
	char c[30][22] = 
	{"....~%#######%~~.....",
	"..~%##@@@@@@@@%~~....",
	".~%#@@@######@@%~....",
	".%#@@##%~~~%%##@%'...",
	"~#@@#%~~~.~~%%##@%'..",
	"%#@#%~.....~~####@%..",
	"#@@#~~......~~%%#@@%.",
	"#@#%%%~......~%%%@@#.",
	"####%%%~....'~%%@@@#.",
	"%%%%%.......'~%%@@#%.",
	".~~~.......'~%#@@#%..",
	"..........'~%#@@#%%..",
	".........'~%#@@#%%~..",
	"........'~%#@@#%%~...",
	".......'~%#@@#%%~....",
	"......'~%#@@#%%~.....",
	".....'~%#@@#%%~......",
	"....'~%#@@#%%~.......",
	"...'~%#@@#%%~........",
	"..'~%#@@#%%~.........",
	"~~~%#@@#%%~..........",
	"~~%#@@#%%~...........",
	"~%%#@@#%%~~..........",
	"%%#@@#%%~~........~~.",
	"%#@@#####~~...%##%~~.",
	"#@@#######%~~######~.",
	"#@@###########@@@##~.",
	"#@@@@@@@@@@@@@@@@##~.",
	"#@@#%%%%#@@@@@@@@#%%.",
	"###%~~~~%#########%%."};
	for (int x = 0; x < 30; ++x)
		std::transform(&c[x][0], &c[x][21], m[x].begin(), Teach_Encode() );
	m.push_back(Line() );
	m[m.size() - 1].assign(SAMPLE_SIZE, 0);
}

void fill3(Matrix& m)
{
	char c[30][22] = 
	{".....~%###%~~.....@@.",
	"..%###@@@@@##~'...@@.",
	"###@@@@###@@@@@@@....",
	"#@@@###%%%###@@@@@@..",
	"####%~~~~~~~%#@@@@@@.",
	"%%...........~%#@@@@.",
	"~..............%@@@@.",
	"................@@@@.",
	"...............'@@@@.",
	"..............~@@@@@.",
	"..............~@@@%~.",
	".............%#@@%~~.",
	"...........~##@@%~~..",
	".......%##@@@@@~~~...",
	"@@....#@@@@@@%~~~....",
	".......%##@@@@@~~~...",
	"............##@@%~~..",
	".............##@@%~~.",
	".............~%#@@%@.",
	".............~~%#%@@.",
	"...............~.%#@.",
	"................~%#@.",
	"................'~%@.",
	"...@@...........~%#@.",
	"...@@..........~%##@.",
	"...@@@.......~#@@#%~.",
	"...@@@@%%%###@@@#%~~.",
	"...@@@@###@@@@##%~~..",
	".....@@@@@@@##%~~~...",
	".....%@@@@@%~~~~....."};
	for (int x = 0; x < 30; ++x)
		std::transform(&c[x][0], &c[x][21], m[x].begin(), Teach_Encode() );
	m.push_back(Line() );
	m[m.size() - 1].assign(SAMPLE_SIZE, 0);
}

void fill4(Matrix& m)
{
	char c[30][22] = 
	{"..........'~%##%~'''.",
	".........'~%#@##%~''.",
	".......'~%#@@#@#%~''.",
	"......'~%#@@%#@#%~''.",
	".....'~%#@@#%#@#%~''.",
	"....'~%#@@#%%#@#%~''.",
	"...'~%#@@#%'%#@#%~''.",
	"..'~%#@@#%''%#@#%~''.",
	".'~%#@@#%'.'%#@#%~''.",
	"'~%#@@#%'..'%#@#%~''.",
	"~%#@@#%'...'%#@#%~''.",
	"~%@@#%'....'%#@#%~''.",
	"#@@#%'.....'%#@#%~''.",
	"@@#%'......'%#@#%~~'.",
	"@@%'''''''''%#@#%%%'.",
	"@@#%##########@###%'.",
	"@@@@@@@@@@@@@@@@@#%'.",
	"%%%#%#%#%#%###@###%'.",
	"~%~%~%~%~%~%%#@#%%%'.",
	"~~~~~~~~~~~%%#@@#%~'.",
	"~~~~~~~~~~~%%#@@#%~'.",
	".......'''~%%#@@#%~'.",
	"..........~%%#@@#%~'.",
	"..........~%%#@@#%~'.",
	"..........~%%#@@#%~'.",
	"........~~~%%#@@#%~'.",
	".......~~~%%%#@@#%~'.",
	"......~~~%%%##@@#%~'.",
	".....~~~%%###@@@@#%~.",
	"....~~~%%###@@@@@#%~."};
	for (int x = 0; x < 30; ++x)
		std::transform(&c[x][0], &c[x][21], m[x].begin(), Teach_Encode() );
	m.push_back(Line() );
	m[m.size() - 1].assign(SAMPLE_SIZE, 0);
}

void fill5(Matrix& m)
{
	char c[30][22] = 
	{"%#################%~.",
	"#@@@@@@@@@@@@@@@##%~.",
	"#@@@@@@@@@@@@@@@##%~.",
	"#@@@@@@@@@@@@@@@##...",
	"#@@@@@@@@@@@@@@@#....",
	"#@@##############....",
	"#@@#%%~~.............",
	"#@@#%%~~.............",
	"#@@#%%~~~~~~~~~~~....",
	"#@#######%%%%%~~~~...",
	"#@@@@@@@@####%%%~~~~.",
	"#@@@@@@@@@@@@###%%~~.",
	"#@@@@@######@@@@#%%~.",
	"%######%%%%%###@@#%%.",
	"~~~~~~.....~~~%#@@#%.",
	"~~~~~........'~%#@#%.",
	"~~~...........~%#@@#.",
	"..............~%#@@#.",
	"..............~%#@@#.",
	"..............~%#@@#.",
	"..............~%#@@#.",
	"..............~%#@@#.",
	"~~~..........'~%#@@#.",
	"~~~~........'~%#@@#%.",
	"~%%%%.....~~~%#@@@#%.",
	"~%##%%#%%%####@@#%%~.",
	"~%#@@@@###@@@@@#%%~..",
	"~%#@@@@@@@@####%%~...",
	"~~%%%#######%%%%~....",
	".~~~%%%%%%%%%~~......"};
	for (int x = 0; x < 30; ++x)
		std::transform(&c[x][0], &c[x][21], m[x].begin(), Teach_Encode() );
	m.push_back(Line() );
	m[m.size() - 1].assign(SAMPLE_SIZE, 0);
}

void fill6(Matrix& m)
{
	char c[30][22] = 
	{".......@@%%%~~~~.....",
	"......@@@@@@@@@#~....",
	".....#@@@@@#~%@@#%...",
	"....#@@#%'''''###....",
	"....#@#%.............",
	"...#@@#..............",
	"...#@#%..............",
	"...@@#...............",
	"...@#%...............",
	"..%##%~..............",
	"..#@%~...~####.......",
	"..@@@@@@@@@####%.....",
	"..@@@#######@@##%....",
	".....~..~%%%@@@@##%..",
	".........~#@@@@@@@#..",
	"..........#@@@@@@@#~.",
	"..........#@@@@@@@@%.",
	"..........#@@@@@@@@%.",
	"..........#@@@@@@@@%.",
	"..........#@@@@@@@@%.",
	"..........#@@@@@@@@%.",
	"..........#@@@@@@@@~.",
	".........#@@@@@@@@#~.",
	"......%##@@@@@@@@#~'.",
	"~@@@@%##@@@@@@@@@~'..",
	"~@@@@@@@@@@@@@@#~'...",
	"~##@@@@@@@@@@##~'....",
	"~%####@@@@@###~'.....",
	"~~%%%########~'......",
	".~~~%%%%%%%#~'......."};
	for (int x = 0; x < 30; ++x)
		std::transform(&c[x][0], &c[x][21], m[x].begin(), Teach_Encode() );
	m.push_back(Line() );
	m[m.size() - 1].assign(SAMPLE_SIZE, 0);
}

void fill7(Matrix& m)
{
	char c[30][22] = 
	{"...'''~%%#####%%%~~~.",
	".''~%##@@@@@@@##%%~~.",
	".'~%#@@@#####%%%%~''.",
	"'~%#@@##%%%%%~~~''...",
	"'~%#@#%%%%~'''''.....",
	"~%#@@#%%~~...........",
	"~%#@#%%~~............",
	"%#@@#%~''............",
	"%#@#%%~''............",
	"%#@#%%~~'''..........",
	"#@@#%~~~~'''''.......",
	"#@#%~~~~~~~~'''''....",
	"#@#%~~~%###%%~~~~~~..",
	"#@#%####@@@##%%%~~~~.",
	"#@##@@@@@#@@@@##%%%~.",
	"#@@@@###%%###@@@#%%%.",
	"#@@##%%%~~~%###@@#%%.",
	"#@@#%%~~~~~~~%%#@@#%.",
	"#@@#%~~~~...~~%%#@#%.",
	"#@@#%~~~.'''.~~%#@@#.",
	"#@@#%~~~.'''..~%%#@#.",
	"#@@#%~~~.''''.~%%#@#.",
	"#@@#%%~~~'''.~~%#@@#.",
	"%#@@#%~~~..~~~%%#@#%.",
	"%#@@@#%%~~~~%%%#@@#%.",
	"~%#@@#%%%~%%%##@@#%~.",
	"~~#@@##%%%%##@@@#%~~.",
	".~%#@@@####@@@##%~~..",
	".~~%##@@@@@@#%~~~~...",
	"..~~~%######%~~......"};
	for (int x = 0; x < 30; ++x)
		std::transform(&c[x][0], &c[x][21], m[x].begin(), Teach_Encode() );
	m.push_back(Line() );
	m[m.size() - 1].assign(SAMPLE_SIZE, 0);
}

void fill8(Matrix& m)
{
	char c[30][22] = 
	{"####################.",
	"#@@@@@@@@@@@@@@@@@@#.",
	"%%################@#.",
	".......#####%%##%%@#.",
	"............~~~%#@@#.",
	"...........''~~#@@@%.",
	"...............#@@@%.",
	"..............%@@@@%.",
	".............%%@#@@%.",
	"............%%%@@@%%.",
	".......'~~%%#@@@@%%~.",
	"......''~~%#@@@@@%~~.",
	".....''~~%%#@@@@%~~'.",
	"...'''~~%%@@@@@%~~''.",
	"...'~~%%%@@@@@%%~....",
	"..''~~%%@@@@@%%~'....",
	".''~~%%@@@@@%%~'.....",
	".'~~%%%@@@@@%~'......",
	"''~~%%@@@@@%~'.......",
	"'~~%%@@@@@%~'........",
	"~~%%@@@@@%~'.........",
	"~%%@@@@@@%~'.........",
	"~%%@@@@@%~'..........",
	"%%%#@@@%~'...........",
	"%%#@@@@~'............",
	"%#@@@@@@.............",
	"%#@@@@@@.............",
	"#@@@@@@@.............",
	"#@@@@@@@.............",
	"###@@@@@............."};
	for (int x = 0; x < 30; ++x)
		std::transform(&c[x][0], &c[x][21], m[x].begin(), Teach_Encode() );
	m.push_back(Line() );
	m[m.size() - 1].assign(SAMPLE_SIZE, 0);
}

void fill9(Matrix& m)
{
	char c[30][22] = 
	{".........@@@@........",
	".........'@@%~.......",
	".......'~@@@#%~......",
	".....'~~@##@@#.......",
	"...'~%@@%~~%##@#~....",
	"..~~@@#%~....##@%~...",
	".~%@@%%~......#@@#%~.",
	".%#@#%~'......'~%@%~.",
	".#@@#%~'......'~%@@#.",
	".#@@#%~'......'~%#@%.",
	".#@@@#%~'....'~%#@%~.",
	".##@@@@#%~'''~%#@%~..",
	"..%#@@@@@%%%#@@@%~...",
	"...%##@@@@##@@#%~....",
	".....%#@@@@@~'.......",
	"...'''%@@@@@@%.......",
	"..'~%@@@####@@%~.....",
	"..%#@##%%%%%##@#%~...",
	".%#@#%''~~~~%%%@@#~..",
	".#@@#'........%#@@#'.",
	"%@@#'..........#@@#%.",
	"#@@#~..........#@@@%.",
	"#@@#%~.........##@@%.",
	"%@@#%~.........##@@%.",
	"%#@@#%~.......%#@@~'.",
	".%#@#%%~~~~~~%%@@~'..",
	".~#@@##%%~~%%#@@~'...",
	"..~#@@@#####@@%~'....",
	"...'~#@@@@@@@%~'.....",
	"....'~%####%%~'......"};
	for (int x = 0; x < 30; ++x)
		std::transform(&c[x][0], &c[x][21], m[x].begin(), Teach_Encode() );
	m.push_back(Line() );
	m[m.size() - 1].assign(SAMPLE_SIZE, 0);
}

void fill10(Matrix& m)
{
	char c[30][22] = 
	{"......@#@#@#@#@......",
	".....@@@@@@@@@@@.....",
	"....@@@@@##~~~@@@....",
	"...@@###%~~~~~~@@@...",
	"..@@@#%'#~~~~~~.@@@..",
	".@@@#..'%'......@@%..",
	"~@@@#%~'#......@#%...",
	"~@@@#%~'##....@#%....",
	"~@@@#%~'.##..@%~.....",
	"~#@@@#%~'.#@@#'......",
	".%#@@@##%#@@%#'......",
	"..%#@@@###@%'@@'.....",
	"...%#@@@#@@%'.@@'....",
	".....%@@@@@@...@@'...",
	"......#@@@@@@%%%@@'..",
	"......@@@@@@@@%%%@@'.",
	"....#@@%%@@@@@@%%%@@.",
	"...#@@''~%@@@@@%%%%@.",
	"..#@@~~'.'~@@@@@@%.@.",
	".%#@~~...'~%@@@@@%.@.",
	"'%@@~~...'~%#@@@@'.@.",
	"@@##~~...'~%#@@@'.%@.",
	"@@##~....'~~%@@~'..%.",
	"@@##%~..'~%#@#~'..%#.",
	"@@##%~'.'~%@#~'...#..",
	"'#@@#%'.~%@%~'...##..",
	"'#@@#%'.~%@%~'...#...",
	".%#@#%%%%@%~'...##...",
	".~%@@%#@@%~'..###....",
	"...~@@@@@@@@@#......."};
	for (int x = 0; x < 30; ++x)
		std::transform(&c[x][0], &c[x][21], m[x].begin(), Teach_Encode() );
	m.push_back(Line() );
	m[m.size() - 1].assign(SAMPLE_SIZE, 0);
}

void fill11(Matrix& m)
{
	char c[30][22] = 
	{"......%######%.......",
	"....%@@@@@@@@@@%.....",
	"..%@@@########@@@%...",
	".%@@###%%%%%%###@@%..",
	"%#@#%%%%%~~~%%%##@#%.",
	"#@@#%''''''''%%##@@#.",
	"#@@%'.........'%#@@#.",
	"#@@%'.........'%#@@#.",
	"#@@%'.........'%#@@#.",
	"#@@%'.........'%#@@#.",
	"#@@%'.........'%#@@#.",
	"#@@%'.........'%#@@#.",
	"#@#%'........'%##@@#.",
	"#@#%%'......'%%##@@#.",
	"#@@##%%%%%%%%%##@@@#.",
	"%#@@@###%%%##@@@@@@#.",
	"%%##@@@@@@@@@@###@@#.",
	"~~%%%%%####%%%~##@@#.",
	"....~~%%%%%~~..##@@#.",
	"..............~##@@#.",
	".............~###@@#.",
	"............~###@@##.",
	"...........~%##@@@##.",
	".''........~###@@##~.",
	"'''''....~~##@@@###'.",
	"''~###~~~~%%#@@@##'..",
	"~~###%######@@@##'...",
	"~~#######@@@@@@#'....",
	"~~~~%####@@@@##'.....",
	"''''~~~~~%##%~'......"};
	for (int x = 0; x < 30; ++x)
		std::transform(&c[x][0], &c[x][21], m[x].begin(), Teach_Encode() );
	m.push_back(Line() );
	m[m.size() - 1].assign(SAMPLE_SIZE, 0);
}


void precompFill(VMI& pi)
{
	for(int x = 0; x < SAMPLES_COUNT; ++x)
	{
		pi[x].second.resize(30);
		for(int p = 0; p < 30; ++p)
			pi[x].second[p].resize(21);
	}
	pi[0].first = '0';
	fill0(pi[0].second);
	pi[1].first = '1';
	fill1(pi[1].second);
	pi[2].first = '2';
	fill2(pi[2].second);
	pi[3].first = '3';
	fill3(pi[3].second);
	pi[4].first = '4';
	fill4(pi[4].second);
	pi[5].first = '5';
	fill5(pi[5].second);
	pi[6].first = '5';
	fill6(pi[6].second);
	pi[7].first = '6';
	fill7(pi[7].second);
	pi[8].first = '7';
	fill8(pi[8].second);
	pi[9].first = '8';
	fill9(pi[9].second);
	pi[10].first = '8';
	fill10(pi[10].second);
	pi[11].first = '9';
	fill11(pi[11].second);
}

struct Coords
{
	int left;
	int right;
	int top;
	int bot;
	Coords(int l, int r, int t, int b): left(l), right(r), top(t), bot(b){}
};

struct Encode
{
	short operator()(char c) const
	{
		if (c == '.')
			return WHITE;
		else if (c == '%')
			return LIGHT;
		else if (c == '#')
			return DARK;
		else 
			return BLACK;
	}
};

class DigitInfo
{
	 VMI vmi;
public:
	void workout();
	void fun();
	DigitInfo()
	{
		vmi.resize(SAMPLES_COUNT);
		for (int x = 0; x < SAMPLES_COUNT; ++x)
		{
			vmi[x].second.resize(SAMPLE_SIZE);
			for (int i = 0; i < SAMPLE_SIZE; ++i)
				vmi[x].second[i].assign(SAMPLE_SIZE, 0);
		}
	}
};

void DigitInfo::workout()
{
	Line l;

	for( int x = 0; x < SAMPLES_COUNT; ++x)
	{
		vmi[x].first = precomp_info[x].first;

		double v_step, v_index = 0.0, v_intPart, v_fract,
				h_step, h_index = 0.0, h_intPart, h_fract;
		int v_int, h_int;
		v_step = static_cast<double>(30.0 / (SAMPLE_SIZE - 1) );
		h_step = static_cast<double>(20.0 / (SAMPLE_SIZE - 1) );
		vmi[x].second.resize(SAMPLE_SIZE);

		for (int i = 0; i < SAMPLE_SIZE; ++i)
		{
			vmi[x].second[i].resize(SAMPLE_SIZE);
			v_fract = std::modf(v_index, &v_intPart);
			v_int = static_cast<int>(v_intPart);
			for (int j = 0; j < SAMPLE_SIZE; ++j)
			{
				h_fract = std::modf(h_index, &h_intPart);
				h_int = static_cast<int>(h_intPart);
				vmi[x].second[i][j] = 
					static_cast<short>(
						(1.0 - v_fract) * ( (1 - h_fract) * precomp_info[x].second[v_int][h_int] + h_fract * precomp_info[x].second[v_int][h_int + 1])
						+ v_fract * ( (1 - h_fract) * precomp_info[x].second[v_int + 1][h_int] + h_fract * precomp_info[x].second[v_int + 1][h_int + 1]) );

				h_index += h_step;
			}
			h_index = 0.0;
			v_index += v_step;
		}
		v_index = 0.0;
	}

	
}

void DigitInfo::fun()
{
	Matrix full_m;
	
	std::string s;
	Line l;

	while (!std::cin.eof() )
	{
		std::cin >> s;
		std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');
		l.resize(s.size() );
		std::transform(s.begin(), s.end(), l.begin(), Encode() );
		full_m.push_back(l);
	}

	int left = 0, 
		top = 0,
		right = static_cast<short>(l.size() ) - 1,
		bot = static_cast<short>(full_m.size() ) - 1;
	int checksum = 0, flag = 0, temp_coord = 0;

	for (; flag != FINDS_NEEDED && left < right; ++left)				//Поиск левой границы
	{
		for (int i = top; i <= bot; ++i)
			checksum += full_m[i][left];
		if (checksum >= VERTICAL_EDGE * (bot - top + 1) )
		{
			if (flag == 0)
				temp_coord = left;
			++flag;
		}
		else
			flag = 0;
		checksum = 0;
	}
	left = temp_coord;
	flag = 0;


	for (; flag != FINDS_NEEDED && right > left; --right)			//Поиск правой границы
	{
		for (int i = top; i <= bot; ++i)
			checksum += full_m[i][right];
		if (checksum >= VERTICAL_EDGE * (bot - top + 1) )
		{
			if (flag == 0)
				temp_coord = right;
			++flag;
		}
		else
			flag = 0;
		checksum = 0;
	}
	right = temp_coord;
	flag = 0;

	short first_sep = left + (right - left) / 3,
		  second_sep = left + 2 * (right - left) / 3;

	std::vector<Coords> dc;
	dc.assign(3, Coords(left, right, top, bot) );
	int prec = static_cast<int>(PRECISION * (right - left) );
	dc[0].left = std::max(left - prec, 0);
	dc[0].right = first_sep + prec;
	dc[1].left = first_sep - prec;
	dc[1].right = second_sep + prec;
	dc[2].left = second_sep - prec;
	dc[2].right = std::min(right + prec, static_cast<int>(l.size() ) - 1);

	bool sep = false;

	for (int x = 0; x < 3; ++x)
	{	
		for (; !sep && dc[x].left < dc[x].right; ++dc[x].left)
		{
			for (int i = dc[x].top; i <= dc[x].bot; ++i)
			{
				if (full_m[i][dc[x].left] <= DARK)
					++checksum;
				else 
					checksum = 0;
				if (checksum >= SEPARATE * (dc[x].bot - dc[x].top + 1) )
					sep = true;
			}
			checksum = 0;
		}
		sep = false;

		for (; flag != FINDS_NEEDED && dc[x].left < dc[x].right; ++dc[x].left)				//Поиск левой границы
		{
			for (int i = dc[x].top; i <= dc[x].bot; ++i)
				checksum += full_m[i][dc[x].left];
			if (checksum >= VERTICAL_EDGE * (dc[x].bot - dc[x].top) )
			{
				if (flag == 0)
					temp_coord = dc[x].left;
				++flag;
			}
			else
				flag = 0;
			checksum = 0;
		}
		dc[x].left = temp_coord;
		flag = 0;

		for (; !sep && dc[x].right > dc[x].left; --dc[x].right)
		{
			for (int i = dc[x].top; i <= dc[x].bot; ++i)
			{
				if (full_m[i][dc[x].right] <= DARK)
					++checksum;
				else 
					checksum = 0;
				if (checksum >= SEPARATE * (dc[x].bot - dc[x].top + 1) )
					sep = true;
			}
			checksum = 0;
		}
		sep = false;

		for (; flag != FINDS_NEEDED && dc[x].right > dc[x].left; --dc[x].right)			//Поиск правой границы
		{
			for (int i = dc[x].top; i <= dc[x].bot; ++i)
				checksum += full_m[i][dc[x].right];
			if (checksum >= VERTICAL_EDGE * (dc[x].bot - dc[x].top) )
			{
				if (flag == 0)
					temp_coord = dc[x].right;
				++flag;
			}
			else
				flag = 0;
			checksum = 0;
		}
		dc[x].right = temp_coord;
		flag = 0;
	}


	for (int x = 0; x < 3; ++x)
	{
		for (; flag != FINDS_NEEDED && dc[x].top < dc[x].bot; ++dc[x].top)				
		{																	//Поиск верхней границы
			for (int j = dc[x].left;  j < dc[x].right; ++j)
				checksum += full_m[dc[x].top][j];
			if (checksum >= HORISONTAL_EDGE * (dc[x].right - dc[x].left) )
			{
				if (flag == 0)
					temp_coord = dc[x].top;
				++flag;
			}
			else
				flag = 0;
			checksum = 0;
		}
		dc[x].top = temp_coord;
		flag = 0;

		for (; flag != FINDS_NEEDED && dc[x].bot > dc[x].top; --dc[x].bot)				
		{																	//Поиск нижней границы
			for (int j = dc[x].left;  j < dc[x].right; ++j)
				checksum += full_m[dc[x].bot][j];
			if (checksum >= HORISONTAL_EDGE * (dc[x].right - dc[x].left) )
			{
				if (flag == 0)
					temp_coord = dc[x].bot;
				++flag;
			}
			else
				flag = 0;
			checksum = 0;
		}
		dc[x].bot = temp_coord;
		flag = 0;
	}
	
	std::vector<Matrix> digits;
	digits.resize(3);
	full_m.push_back(Line() );
	full_m[full_m.size() - 1].assign(l.size() + 1, 0);
	for (unsigned int i = 0; i < full_m.size(); ++i)
		full_m[i].push_back(0);

	int v_size, h_size;
	double v_step, v_index = 0.0, v_intPart, v_fract,
			h_step, h_index = 0.0, h_intPart, h_fract;
	int v_int, h_int;
	for(int x = 0; x < 3; ++x)
	{
		v_size = dc[x].bot - dc[x].top + 1;
		h_size = dc[x].right - dc[x].left + 1;
		v_step = (static_cast<double>(v_size) - 1) / (SAMPLE_SIZE - 1);
		h_step = (static_cast<double>(h_size) - 1) / (SAMPLE_SIZE - 1);
		digits[x].resize(SAMPLE_SIZE);

		for (int i = 0; i < SAMPLE_SIZE; ++i)
		{
			digits[x][i].resize(SAMPLE_SIZE);
			v_fract = std::modf(v_index, &v_intPart);
			v_int = static_cast<int>(v_intPart) + dc[x].top;
			for (int j = 0; j < SAMPLE_SIZE; ++j)
			{
				h_fract = std::modf(h_index, &h_intPart);
				h_int = static_cast<int>(h_intPart) + dc[x].left;
				digits[x][i][j] = 
					static_cast<short>(
						(1.0 - v_fract) * ( (1 - h_fract) * full_m[v_int][h_int] + h_fract * full_m[v_int][h_int + 1])
						+ v_fract * ( (1 - h_fract) * full_m[v_int + 1][h_int] + h_fract * full_m[v_int + 1][h_int + 1]) );

				h_index += h_step;
			}
			h_index = 0.0;
			v_index += v_step;
		}
		v_index = 0.0;
	}

	std::vector<int> diff;
	s.resize(3);
	for(int x = 0; x < 3; ++x)
	{
		diff.assign(SAMPLES_COUNT, 0);
		for (int p = 0; p < SAMPLES_COUNT; ++p)
			for (int i = 0; i < SAMPLE_SIZE; ++i)
				for (int j = 0; j < SAMPLE_SIZE; ++j)
					diff[p] += abs(digits[x][i][j] - vmi[p].second[i][j]);

		std::vector<int>::iterator it = std::min_element(diff.begin(), diff.end() );
		s[x] = vmi[std::distance(diff.begin(), it)].first;
	}
	std::cout << s;
}

int main()
{
	precomp_info.resize(SAMPLES_COUNT);
	precompFill(precomp_info);
	DigitInfo di;
	di.workout();
	di.fun();
	return 0;
}