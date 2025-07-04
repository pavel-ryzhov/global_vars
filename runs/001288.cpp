#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

//-------------------------------------------------------------------------
// ����� �������� ���������:
// 1. ������������ ����������� �� ������� ������� ��������
// 2. ��������������� ������ �������� � ����������� ��� �������������
//    ������ �������� ���� �� �����
// 3. ������� ����� ������������� �������� - ����
// 4. �������� �������� �������� 2 �����: 
//    - ��������� ������ ����� � ������
//    - ������� ���������� �������� � ����������� �� � ���������
//    �����������
// 5. ������������� ��������
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// ���������� �������� disjoint set union
typedef struct {
    size_t rank;     // ���� ���������, ����� ��� ������������ Dsu
    size_t parent;   // ����� ��������-�������������� ������
    size_t size;     // ����� ��� ����-��������� ������ ��������
} DsuElement;

//-------------------------------------------------------------------------
// disjoint set union (�������� �������)
class Dsu
{
public:
    Dsu(size_t elementsCount) {
        elements = new DsuElement[elementsCount];
        setsCount = elementsCount;
        for (size_t i = 0; i < elementsCount; i++) {
            elements[i].rank = 0;
            elements[i].size = 1;
            elements[i].parent = i;
        }
    }
    ~Dsu() { delete [] elements; }

    size_t find(size_t x)
    {
        size_t y = x;
        while (y != elements[y].parent)
            y = elements[y].parent;
        elements[x].parent = y;
        return y;
    } 
    void join(size_t x, size_t y)
    {
        x = find(x), y = find(y);
        if (elements[x].rank > elements[y].rank){
            elements[y].parent = x;
            elements[x].size += elements[y].size;
        } else {
            elements[x].parent = y;
            elements[y].size += elements[x].size;

            if (elements[x].rank == elements[y].rank)
                elements[y].rank++;
        }
        setsCount--;
    }

    size_t  size     (size_t x) const { return elements[x].size; }
    size_t  num_sets ()         const { return setsCount; }

private:
    DsuElement *elements;
    size_t setsCount;
};

//-------------------------------------------------------------------------
// ���������� �������
struct Point
{
    size_t X, Y;
    Point(size_t coordX=0, size_t coordY=0) {X = coordX; Y = coordY;}
};

//-------------------------------------------------------------------------
// "��������" ��������� ����� ����� ��������� ���������
enum EdgeType
{
    COMMON_EQUAL,
    BACKGROUND,
    BLACK_GRAY,
    BLACK_DARK,
    DARK_GRAY,
    BORDER_DARK,
    BORDER_GRAY,
    WHITE_INTERNAL,
    JOIN_THRESHOLD
};

//-------------------------------------------------------------------------
// �����-����� ����� ����� ���������, ������������ ��� �����������
struct edge
{
    EdgeType w;		    // ��� �����, ���������� "��������" ����������
    int pointA, pointB;	// ���������� �������� �����
    bool operator<(const edge &b) const { return w < b.w; }
};

// 2D ������� ��������
typedef vector<vector<char> > charMap;

class Area; // see later

//-------------------------------------------------------------------------
// 2D ����������� (������� + ������� ��� ���������)
// ��������� �����������
class Bitmap
{
public:
    Bitmap(size_t width=0, size_t height=0, char fillChar=' ')
        :data(height, vector<char>(width, fillChar)){_pixCount = 0;}

    //---------------------------------------------------------------------
    // ����������� ��� ���������� ������� �����������
    Bitmap (Point& topLeft,         // ���������� ������� �� ������
            size_t width,           // ������ �������-�������
            size_t height,          // ������ �������-������� 
            Bitmap& parent,         // �����������-�����
            list<size_t> points)    // ������ ��������� �����, �������
                                    // �������� �� ������
        : data(height, vector<char>(width, ' '))
    {
        // �������� ����� �� ������
        list<size_t>::iterator i = points.begin();
        while (i != points.end()) {
            Point p = parent.PointFromPixelNumber(*i);
            // ������������� ��������� ������� (�������� ����� �����������)
            if (parent[p] == '|')
                parent[p] = '%';
            else if (parent[p] == 'I')
                parent[p] = '#';

            data[p.Y-topLeft.Y][p.X-topLeft.X] = parent[p];
            i++;
        }
        _pixCount = points.size();
    }

    // ������ ����� �� ����������
    char& Pixel(size_t x, size_t y) { return data[y][x]; }
    char& Pixel(size_t n){ return Pixel(n % width(), n / width()); }
    char& Pixel(const Point& p){ return Pixel(p.X, p.Y); }
    char& operator[](const Point& p) { return Pixel(p.X, p.Y); }

    size_t width()  const { return (data.size() > 0)? data[0].size() : 0; }
    size_t height() const { return data.size(); }

    // ������������ ���������� 1-D ���������� � ������� 2-D ����������
    Point PointFromPixelNumber(size_t n) const
    { 
        return Point(n % width(), n / width());
    }
    
    bool IsSpace(Point p) const
    {
        char c = data[p.Y][p.X];
        return (c == ' ' || c == '.');
    }

    // true, ���� �������� �������� ������ ������
    bool Inside(Point p) const { return p.X < width() && p.Y < height(); }

    //---------------------------------------------------------------------
    // 
    std::list<Area> *GetSegments();

    // ���� � ����� (����� ��� �������)
    friend istream& operator>>(istream&, Bitmap&);
    friend ostream& operator<<(ostream&, Bitmap&);

protected:
    static const size_t min_size = 3;  // ����������� ������ ��������
    charMap data;          // ����� ����� �����������
    size_t  _pixCount;     // ���������� �����, ������������� � ������

    //---------------------------------------------------------------------
    // ���������� ������� ������� ����� ��������� ���������
    EdgeType diff(const Point &p1, const Point &p2);

    //---------------------------------------------------------------------
    // 
    Dsu *SegmentGraph(int num_vertices, int num_edges, edge *edges);

    //---------------------------------------------------------------------
    // 
    void PostProcessSegments(list<Area> *segs);
};

istream& operator>>(istream& input, Bitmap &bmp)
{
    bmp.data.clear();
    string s;

    while(!getline(input, s).eof())
        bmp.data.push_back(vector<char>(s.c_str(), s.c_str()+s.length()));

    return input;
}

ostream& operator<<(ostream& output, Bitmap &bmp)
{
    for(charMap::iterator i = bmp.data.begin(); i != bmp.data.end(); ++i){
        char* buf = &((*i)[0]);
        output.write(buf, i->size()) << endl;
    }
    return output;
}

//-------------------------------------------------------------------------
// ������������ ����� ���� ������ ����������� �� ��������� �����������
// ��������� ����������� ���������� �������� �����
class PathFinder
{
    Bitmap&   _img;             // �����������, ������ �������� ���� ����
    Bitmap    _visited;         // ������� ���������� �����
    Point     _destination;     // ������� ����������
    bool      _pathFound;       // ���� ���������� ����
    pair<int, int> _moves[3];   // ��������� ����������� ������

public:
    PathFinder(Bitmap& image)
        :_img(image),_visited(image.width(),image.height(),0) {}

    bool Find  (const Point& startPoint,    // ������ �������� �����
                bool stepLeft,              // ����� ������, ���� �������
                bool stepDown)              // ����� ����, ���� �����
    {
        _pathFound = false;

        // ���������� ������� ����������
        _destination.X = stepLeft? 0 : _img.width()-1;
        _destination.Y = stepDown? _img.height()-1 : 0;

        // ���������� �������� ��� ������
        int stepX = stepLeft? -1 :  1;
        int stepY = stepDown?  1 : -1;

        _moves[1] = pair<int,int>(stepX, 0);
        _moves[2] = pair<int,int>(stepX, stepY);
        _moves[0] = pair<int,int>(0, stepY);

        dfs(startPoint);

        bool result = _pathFound;
        _pathFound = false;
        return result;
    }

private:
    //---------------------------------------------------------------------
    // ����� ���������� �������� � ������� ��� ������ ���� �� ����������
    // ������� ����� ������
    void dfs(const Point& current)
    {
        if (_pathFound)
            return;

        if (current.X == _destination.X || current.Y == _destination.Y) {
            _pathFound = true;
            return;
        }

        _visited[current] = 1;

        // ������� ��� ��������� ����
        for (int i=0; i<3 && !_pathFound; i++) {
            Point child = current;
            child.X += _moves[i].first;
            child.Y += _moves[i].second;

            if (CanStep(child) && _visited[child] != 1)
                dfs(child);
        }
    }

    //---------------------------------------------------------------------
    // ���������� ����������� ����� ��� ���� �� ���
    bool CanStep(Point p) const { return _img.Inside(p) && _img.IsSpace(p); }
};

//-------------------------------------------------------------------------
// ������� �� �����������, ��������� ������� �������� ������� ���
// �������������
class Area
{
    Bitmap  _image;             // ���������� ��������
    size_t  _x, _y;             // ������� �������� �� "��������"
    size_t  _width, _height;
    size_t  _pixCount;          // ���������� "������������" ��������

public:
    Area(Bitmap& parentImage, list<size_t> points)
    {
        list<size_t>::iterator i = points.begin();

        Point topLeft     = parentImage.PointFromPixelNumber(*i);
        Point bottomRight = topLeft;

        while (++i != points.end())
        {
            Point p = parentImage.PointFromPixelNumber(*i);

            if (p.X < topLeft.X)
                topLeft.X = p.X;
            else if (p.X > bottomRight.X)
                bottomRight.X = p.X;

            if (p.Y < topLeft.Y)
                topLeft.Y = p.Y;
            else if (p.Y > bottomRight.Y)
                bottomRight.Y = p.Y;
        }

        _x = topLeft.X;
        _y = topLeft.Y;
        _width  = bottomRight.X - topLeft.X + 1;
        _height = bottomRight.Y - topLeft.Y + 1;

        _image = Bitmap(topLeft, _width, _height, parentImage, points);
        _pixCount = points.size();
    }

    // ������ � ������������� ���� =)
    char& Pixel(size_t x, size_t y)  { return _image.Pixel(x, y); }
    char& Pixel(size_t n) { return Pixel(n % width(), n / width()); }
    char& operator[](const Point& p) { return Pixel(p.X, p.Y); }

    size_t width()  const { return _width; }
    size_t height() const { return _height; }

    size_t x() const { return _x; }
    size_t y() const { return _y; }
    size_t PixelsCount() const { return _pixCount; }

    //-------------------------------------------------------------------------
    // ���������� ������� �� ������� �������� �� ���
    void CopyFrom(Area& a)
    {
        // ���������� �������� �� ��������� ������� ("�������")
        if (_height < a.height()*10 && a.width() > a.height()*3)
            return;

        // ������������� ���������� �������
        if (a.height() < 3 && a.width() > a.height()*3 && a.IsInternalArea())
            for(size_t i=0; i<a.width(); i++)
                for(size_t j=0; j<a.height(); j++)
                    if (a.Pixel(i,j)=='.')
                        a.Pixel(i,j) = '@';

        size_t xdiff = a.x() - _x;
        size_t ydiff = a.y() - _y;

        for (size_t i = 0; i < a.width(); i++) {
            for (size_t j = 0; j < a.height(); j++){
                char newPix = a.Pixel(i, j);
                if (newPix != ' '){     // ���������� �������
                    Pixel(i + xdiff, j + ydiff) = newPix;
                    if (newPix != '.')
                        _pixCount++;    // internal space �� �������
                }
            }
        }
    }

    //---------------------------------------------------------------------
    // �������� �� ������� ������ ?
    bool IsFrame()
    {
        size_t row1sum = CountColored(0);
        size_t rowHsum = CountColored(_height-1);

        double threshold = _height * 0.75;
        if (row1sum == rowHsum && row1sum > threshold)
            return true;
        return false;
    }

    bool operator< (const Area& b)
    { return _height < b._height && _width < b._width; }

    bool IsColored(size_t x, size_t y)
    {
        char p = Pixel(x, y);
        return (p == '@' || p == '#' || p == '%');
    }
    bool IsSpace(size_t x, size_t y)
    {
        char p = Pixel(x, y);
        return (p == ' ' || p == '.');
    }

    // ��������� ���������� ������� � ������
    size_t CountColored(size_t row)
    {
        size_t sum = 0;
        for (size_t i = 0; i<_width; i++) {
            char pixel = Pixel(i, row);
            if (pixel != ' ' && pixel != '.')
                sum++;
        }
        return sum;
    }

    // ��������� ������� � ������ ����� ��� ������ �� �������
    size_t CountWhite(size_t row, bool left = true)
    {
        int sum = 0;
        int start = left? 0 : _width-1;
        int end   = left? _width : -1;
        int step  = left? 1 : -1;

        for (int i = start; i != end; i+=step) {
            if (IsSpace(i, row)) sum++;
            else break;
        }
        return sum;
    }

    //---------------------------------------------------------------------
    // ����� ��������� ����� � ������ ������� � ������
    // ���������� width ���� �� �������
    size_t SearchInternalSpaceX(size_t row)
    {
        size_t rowPos = 0;

        // step on row from left to right
        // skip background
        while(rowPos < _width && IsSpace(rowPos, row))
            rowPos++;

        // skip black and gray
        while(rowPos < _width && IsColored(rowPos, row))
            rowPos++;

        if (rowPos > _width*3/5)
            return _width;

        size_t internalSpace = rowPos;

        // skip spaces
        while(rowPos < _width && IsSpace(rowPos, row))
            rowPos++;

        if (rowPos < _width)
            internalSpace = rowPos - 1;
        else
            internalSpace = _width; // �� ����� ������ ��� ����������� - 
        // ������ ����� ������!
        return internalSpace;
    } 

    Point SearchInternalSpaceXRange(size_t startRow, size_t endRow)
    {
        size_t current = endRow-1;
        Point result(0, endRow);

        while (startRow <= current)
        {
            size_t xPos = SearchInternalSpaceX(current);
            if (xPos < _width && xPos > result.X){
                result.X = xPos;    // ���� ����� ������
                result.Y = current;
            }
            current--;
        }
        // �� ����� ������
        if (result.X == 0) result.X = _width;
        return result;
    }

    //---------------------------------------------------------------------
    // ���������� ����� ���� �� ���������� ������� ����� ������ � 
    // ����� �� 4-� ������������ �����������
    int GetOutside(size_t begRow, size_t endRow, bool stepLeft, bool stepDown)
    {
        Point p = SearchInternalSpaceXRange(begRow, endRow);
        size_t x = p.X;
        size_t y = p.Y;

        size_t destX = stepLeft? 0 : _width-1;
        size_t destY = stepDown? _height-1 : 0;

        if (x == _width)
            return -1;

        // Pixel(x,y) = '_';
        return PathFinder(_image).Find(p, stepLeft, stepDown);
    }

    // ���������� ����������� ������� �������������� � ������
    static bool IsNested(const Area& a, const Area& b)
    {
        bool x = (a._x <= b._x && (b._x + b._width) <= (a._x + a._width));
        bool y = (a._y <= b._y && (b._y + b._height) <= (a._y + a._height));
        return (x && y);
    }

    //---------------------------------------------------------------------
    // �������� �� ������� ���������� ���������� �������� ����� ?
    bool IsInternalArea()
    {
        size_t midRow = _height / 2;

        for (size_t i=0; i<_width; i++)
        {
            // ���������� ������� ��� "����������" ������,
            // ���� �� ������� ��� ������ ��� �� ������ ������������
            // �������
            char pixColor = Pixel(i, midRow);
            if (pixColor != '.' && pixColor != ' ')
                return false;
        }
        return true;
    }

    size_t CountColored(size_t startRow, size_t endRow)
    {
        size_t sum = 0;
        for (size_t i =startRow; i < endRow; i++)
            sum += CountColored(i);
        return sum;
    }

    friend ostream& operator<< (ostream&, Area&);
};

ostream& operator<< (ostream& output, Area& area)
{
    return output << area._image;
}

std::list<Area>* Bitmap::GetSegments() 
{
    size_t width  = this->width();
    size_t height = this->height();

    // build graph
    edge *edges = new edge[width*height*4];
    size_t edgesCount = 0;

    Pixel(0,0) = ' ';   // �������� ��� ����� ������������

    for (size_t y = 0; y < height; y++){
        for (size_t x = 0; x < width; x++){
            // right
            if (x < width-1) {	
                edges[edgesCount].pointA = y * width + x;
                edges[edgesCount].pointB = y * width + (x+1);
                edges[edgesCount].w = diff(Point(x, y), Point(x+1, y));
                edgesCount++;
            }
            // down
            if (y < height-1) {	
                edges[edgesCount].pointA = y * width + x;
                edges[edgesCount].pointB = (y+1) * width + x;
                edges[edgesCount].w = diff(Point(x, y), Point(x, y+1));
                edgesCount++;
            }
            // right-down
            if ((x < width-1) && (y < height-1)) {	
                edges[edgesCount].pointA = y * width + x;
                edges[edgesCount].pointB = (y+1) * width + (x+1);
                edges[edgesCount].w = diff(Point(x, y), Point(x+1, y+1));
                edgesCount++;
            }
            // right-up
            if ((x < width-1) && (y > 0)) {	
                edges[edgesCount].pointA = y * width + x;
                edges[edgesCount].pointB = (y-1) * width + (x+1);
                edges[edgesCount].w = diff(Point(x, y), Point(x+1, y-1));
                edgesCount++;
            }
        }
    }

    Dsu *u = SegmentGraph(width*height, edgesCount, edges);

    // post-process small components
    for (size_t i = 0; i < edgesCount; i++){
        size_t a = u->find(edges[i].pointA);
        size_t b = u->find(edges[i].pointB);
        if ((a != b) && ((u->size(a) < min_size) ||
            (u->size(b) < min_size)))
        {
            // ����������� ���������� ����� �����
            if (Pixel(a)=='.' && u->size(a) == 1)
                Pixel(a)='%';
            else if (Pixel(b)=='.' && u->size(b) == 1)
                Pixel(b)='%';

            u->join(a, b);
        }
    }

    map<size_t, list<size_t> > coords;
    size_t pixelCount = height*width;

    // ��������� �������� �������
    for (size_t i=0; i<pixelCount; i++) {
        size_t pixelClass = u->find(i);

        // ����������� �� ����
        if (Pixel(pixelClass) != ' ')
            coords[pixelClass].push_back(i);
    }

    list<Area> *segments = new list<Area>();
    map<size_t, list<size_t> >::iterator i = coords.begin();

    // ���������� ������ ���������
    while(i != coords.end())
        segments->push_back(Area(*this, i->second)), ++i;

    delete [] edges;
    delete u;

    PostProcessSegments(segments);

    return segments;
}

Dsu * Bitmap::SegmentGraph( int num_vertices, int num_edges, edge *edges )
{
    // ��������� �����, ����� � ������ ������� ���������������
    // ����� ������� ����� ����� ���������
    std::sort(edges, edges + num_edges);

    Dsu *u = new Dsu(num_vertices);

    for (int i = 0; i < num_edges; i++) {
        edge *pedge = &edges[i];

        // components conected by this edge
        int segmentA = u->find(pedge->pointA);
        int segmentB = u->find(pedge->pointB);

        if (segmentA != segmentB) {

            if (pedge->w < JOIN_THRESHOLD) {
                size_t x = u->size(segmentA);
                size_t y = u->size(segmentB);

                if (Pixel(pedge->pointB) == '|') {
                    char nextRight = Pixel(pedge->pointB+1);
                    if (nextRight != '.' && nextRight != ' ' && nextRight != '|')
                        continue;
                }

                if (Pixel(pedge->pointA) == '|')
                    if (pedge->pointB != pedge->pointA + 1)
                        continue;

                u->join(segmentA, segmentB);
            }
        }
    }
    return u;
}

EdgeType Bitmap::diff( const Point &p1, const Point &p2 )
{
    // fill background
    if (Pixel(p1)==' ' && Pixel(p2) == '.'){
        Pixel(p2) = ' ';
        return BACKGROUND;
    }
    if (Pixel(p1)=='.' && Pixel(p2) == ' '){
        Pixel(p1) = ' ';
        return BACKGROUND;
    }
    if ((Pixel(p1)=='@' || Pixel(p1)=='#') &&
        Pixel(p2) == '%' && p1.X<p2.X &&
        Pixel(p2.X+1,p2.Y) != '.'){
            Pixel(p2) = '|';
            return BORDER_GRAY;
    }

    if (Pixel(p1)=='|' && Pixel(p2)!=' ' && Pixel(p2)!='.')
        return BORDER_GRAY;

    if ((Pixel(p1)=='@' && Pixel(p2)=='#') ||
        (Pixel(p1)=='#' && Pixel(p2)=='@'))
        return BLACK_DARK;

    if ((Pixel(p1)=='#' && Pixel(p2)=='%') ||
        (Pixel(p1)=='%' && Pixel(p2)=='#'))
        return DARK_GRAY;

    if ((Pixel(p1)=='@' && Pixel(p2)=='%') ||
        (Pixel(p1)=='%' && Pixel(p2)=='@'))
        return BLACK_GRAY;

    if (Pixel(p1)==Pixel(p2) && Pixel(p1)=='.')
        return WHITE_INTERNAL;

    if (Pixel(p1)==Pixel(p2))
        return COMMON_EQUAL;

    return JOIN_THRESHOLD;
}

//-------------------------------------------------------------------------
// ��������������� ����� �� ������ ���������
struct FrameFilter
{
    list<pair<int,int> > frames;

    bool operator()(Area& seg)
    {
        if (seg.x() == 0 && seg.y() == 0)
            return true;                        // ��� ��� �� �����
        else if (seg.IsFrame()){
            frames.push_back(pair<int,int>(seg.x(), seg.y()));
            return true;
        }else{
            // ������� ������ ����� ���� �����������
            list<pair<int,int> >::iterator i = frames.begin();
            while (i!=frames.end()){
                if (abs((int)seg.x() - i->first) < 3 &&
                    abs((int)seg.y() - i->second) < 3)
                    return true;
                i++;
            }
        }
        return false;
    }
};

//-------------------------------------------------------------------------
// ����������� �� ����� ���������� ���������� ������� � ������� ���
// ������� �� ������ ���������
struct InternalSpaceFilter
{
    list<Area> intSpaces;

    bool operator()(Area& seg)
    {
        if (seg.IsInternalArea()) {
            intSpaces.push_back(seg);
            return true;
        } else if (seg.PixelsCount() < 50)    // ���������� ������� ������
            return true;
        else
            for (list<Area>::iterator i = intSpaces.begin(); i != intSpaces.end(); ++i)
                if (Area::IsNested(seg, *i))
                    seg.CopyFrom(*i);         // �������� ��������� �������
        return false;
    }
};

//-------------------------------------------------------------------------
// ���������� ��������� ����� �������
bool L2RSorter(const Area& a, const Area& b){ return a.x() < b.x(); }

//-------------------------------------------------------------------------
// ������� �������� �������������� ���������
// ��� ���������� ��� ����������� ������� ���������� ��������
void ThickenLines(Area& img)
{
    size_t heightLimit = img.height()-1;
    size_t widthLimit  = img.width()-1;
    for (size_t y=0; y < heightLimit; y++)
        for (size_t x=0; x < widthLimit; x++) {

            if (img.Pixel(x+1, y)=='@' && img.Pixel(x, y+1)=='@' &&
                img.IsSpace(x+1, y+1) && img.IsSpace(x, y) )
                img.Pixel(x+1, y+1) = '%';

            if (img.Pixel(x, y)=='@' && img.Pixel(x+1, y+1)=='@' &&
                img.IsSpace(x, y+1) && img.IsSpace(x+1, y) )
                img.Pixel(x+1, y) = '%';
        }
}

//-------------------------------------------------------------------------
// ����-��������� ����������������� �����������
void Bitmap::PostProcessSegments(list<Area> *segs)
{
    segs->sort();                           // ��������� �� ����������� ��������
    segs->reverse();                        // �� ��������...
    segs->remove_if(FrameFilter());         // ����������� ����� ������ ����
    segs->reverse();                        // � ����� �� ����������� =)
    segs->remove_if(InternalSpaceFilter()); // ����������� ���������� �������
    segs->sort(L2RSorter);                  // ������������� ����� �������
    // �������� �������������� �����
    for_each(segs->begin(), segs->end(), ThickenLines);
}

//-------------------------------------------------------------------------
// ������������������ �����, �� ������� ����������� ����������
// ������������� ��������� (����������) ������� � ����� �������
struct SideRange
{
    size_t begin;   // ������ ������� (����� ������)
    size_t end;     // ����� �������
    float  width;   // ������������� ��������� ������ �� �������

    SideRange(size_t rangeBegin, size_t rangeEnd, float rangeWidth)
    {
        begin = rangeBegin;
        end   = rangeEnd;
        width = rangeWidth;
    }
    const SideRange& operator=(const SideRange& a)
    {
        begin = a.begin;
        end   = a.end;
        width = a.width;
        return *this;
    }
    bool operator<(const SideRange& b) const { return length() < b.length(); }
    size_t length() const { return end-begin+1; }
};

//-------------------------------------------------------------------------
// ���������� ������������� ���������� ������ ������� � ����� �������
class SideVector
{
    vector<size_t>    _spaces;  // ���-�� �������� �� ������ ����� ��� ������
                                // �� �������
    vector<float>     _diff;    // ��������� ������ ������ ������������
                                // ��������� �������� �������,
                                // ������������� �� ������ ������
    vector<SideRange> _ranges;  // ���������� ���������� ��������� ���������
    vector<pair<size_t, float> >  _sharp; // ������ ��������� (�������-������)

    bool _straight;              // ������� ������ ����� (��������� ���������
                                // ������

public:
    SideVector(Area& area, bool left)
    {
        // ���� ������ ����
        size_t height = area.height();
        size_t width = area.width();

        _diff.assign(height, .0f);
        _spaces.assign(height, 0);

        for(size_t i=0; i<height; i++) {
            _spaces[i] = area.CountWhite(i, left);
            _diff[i] = (float)_spaces[i]/width;
        }

        // �������� ������ ������
        if (_spaces[0] > width/3 && _spaces[1] < width/3) {
            _spaces[0] = width/3;
            _diff[0] = 0.33f;
        }

        _straight = CheckStraight(_spaces, width);

        for(int i=height-1; i>0; i--)
            _diff[i] -= _diff[i-1];
        _diff[0] = .0f; // (float)_spaces[0]/width-0.5f;

        _sharp.clear();

        float littleSharp = 0.0f;
        for (size_t i=0; i<_diff.size(); ++i) {
            float currSharp = _diff[i];
            if (abs(currSharp) > 0.3) {
                _sharp.push_back(pair<size_t, float>(i, currSharp));
                littleSharp = .0f;
            } else if (abs(currSharp+littleSharp) > 0.25f) {
                _sharp.push_back(pair<size_t, float>(i-1, currSharp+littleSharp));
                littleSharp = 0.0f;
            } else if (abs(currSharp) > 0.1)
                littleSharp = currSharp;
            else
                littleSharp = 0.0f;
        }

        ConstructRanges();
    }

    //---------------------------------------------------------------------
    // ���������� "�������" �����
    bool CheckStraight(const vector<size_t>& side, size_t width)
    {
        size_t endPos = side.size() - 4;    // �� ������ ��������� �����
        float start = (float)side[0];
        float end   = (float)side[endPos];
        float k     = (end - start)/endPos; // �������� �����-� ������

        float totalDiff = .0f;
        for (size_t i=0; i<endPos; i++) {
            float diff = side[i] - (k*i + start);
            if (diff > 4) diff *= 100;  // �������� ���������� �����������
            totalDiff += abs(diff);
        }

        // ������ ���������� - 2 ������� �� ������ (��� �������)
        return totalDiff < 1.5*width;
    }

    size_t height() { return _diff.size(); }
    bool IsStraight() const { return _straight; }
    
    static char sign(const float& a) { return (a<0)? -1 : (a==0)? 0 : 1; }

    //---------------------------------------------------------------------
    // ����������� "����� ������" � ���������� ������ ���������� ��������
    void ConstructRanges()
    {
        vector<SideRange> atomic;

        // ���������� �������� ���������� �� ����������� ������� �������
        for (size_t i=0; i < _diff.size(); ){
            int   begin = i;
            float w = _diff[i];
            char  s = sign(_diff[i++]);

            while(i < _diff.size() && sign(_diff[i]) == s)
                w += _diff[i++];

            atomic.push_back(SideRange(begin, i-1, w));
        }

        _ranges.clear();
        SideRange sr = atomic[0];

        for (size_t i=1; i<atomic.size(); i++){
            if (sign(sr.width) == -sign(atomic[i].width)){
                _ranges.push_back(sr);
                sr = atomic[i];
                // "������" ����� ����������
            } else if (sign(sr.width) == 0){
                // ���������� ��������� � �����������
                sr.end = atomic[i].end;
                sr.width += atomic[i].width;
            } else {
                if (i<atomic.size()-1 && sign(atomic[i+1].width) == sign(sr.width)){
                    // ���������������� ����������� � ��������� ����� ����
                    sr.end = atomic[i+1].end;
                    sr.width += (atomic[i].width + atomic[i+1].width);
                    i++;
                } else if (i == atomic.size()-1){
                    // ���������� ����������� � ���������, ����� ������� ������ ���
                    sr.end = atomic[i].end;
                    sr.width += atomic[i].width;
                } else if (sign(sr.width) == sign(atomic[i].width)) {
                    sr.end = atomic[i].end;
                    sr.width += atomic[i].width;
                } else {
                    // ����������������� ����������� � ��������� ����� ����
                    // ����� ���������� �� ���������
                    size_t end = atomic[i].end - atomic[i].length()/2;
                    sr.end = end;
                    _ranges.push_back(sr);
                    sr.begin = end+1;
                    sr.width = 0;
                }
            }
        }
        _ranges.push_back(sr);    // ��������� ���������� �������
    }

    //---------------------------------------------------------------------
    // ���� ����� ������� ���������� ���������
    void LongestGradientUpToDown(size_t *gradHeight, float *gradWidth)
    {
        *gradHeight = 0;
        *gradWidth = .0f;

        size_t limit = _ranges.size()-1;

        for(size_t i=0; i<limit; i++) {
            size_t paurLength = _ranges[i].length()+_ranges[i+1].length();
            if (paurLength > *gradHeight) {
                *gradHeight = paurLength;
                *gradWidth = _ranges[i].width+_ranges[i+1].width;
            }
        }
    }

    //---------------------------------------------------------------------
    // ���������� ������ ��������� ������ ����� ��������� ��������
    float SharpJumpBetween(size_t start, size_t end, bool extend=false)
    {
        for (vector<pair<size_t,float> >::iterator i = _sharp.begin();
                i != _sharp.end(); ++i) {
            if (start <= i->first && i->first <= end && (i->second < 0)==extend )
                return extend? -i->second : i->second;
        }
        return .0;
    }

    //---------------------------------------------------------------------
    // ���������� ������ ������ �������� ����� ��������� ��������
    bool SmoothBendingBetween(size_t start, size_t end)
    {
        bool getFall = false;

        for(vector<SideRange>::iterator i = _ranges.begin();
            i != _ranges.end(); ++i) {
            if (i->end <= start)
                continue;
            else if (i->begin > end)
                break;
            else {
                if (i->width > 0)
                    getFall = true;
                else if (i->width < 0 && getFall)
                    if (SharpJumpBetween(i->begin, i->end, true) > 0.f)
                        getFall = false;
                    else 
                        return true;
            }
        }
        return false;
    }
};

//-------------------------------------------------------------------------
// ������������� ��������
int main()
{
    Bitmap bmp;
    cin >> bmp;
    list<Area> *segList = bmp.GetSegments();
    
    for(list<Area>::iterator i = segList->begin(); i != segList->end(); i++)
    {        
        // ����-������
        int weight[10] = {0,0,0,0,0,0,0,0,0,0};

        SideVector left(*i,true);
        SideVector right(*i,false);

        float f;
        size_t n;

        // ������ � ������ ������������� ����� �� ���������
        if (left.IsStraight())
            weight[1]+=5;

        if (right.IsStraight()) {
            weight[1]++;
            weight[7]++;
            weight[4]++;
        } else {
            weight[1] -= 10;
            weight[7]--;
        }

        n = max(i->CountColored(0), i->CountColored(1));
        bool wideTop = (n >= i->width()*8/10);

        if (wideTop) {
            weight[1]-=2;
            weight[7]+=2;
            weight[5]+=2;
        } else {
            weight[7]-=4;
        }

        left.LongestGradientUpToDown(&n, &f);

        if (n >= left.height()*7/10) {
            weight[2]++;
            weight[7]++;
            weight[8]--;
            weight[3]-=3;
            weight[6]++;
            weight[4]++;
            weight[0]++;
        }
        else{
            weight[2]-=2;
        }

        if (n >= i->height()*8/10) {
            weight[4]-=2;
            weight[1]++;
        }

        right.LongestGradientUpToDown(&n, &f);
        if (n > right.height()/2){
            weight[1]++;
            weight[2]++;
            weight[7]++;
            weight[8]--;
            weight[4]++;
            weight[0]++;
            weight[9]++;
        }

        f = left.SharpJumpBetween(1, left.height() / 3);
        if (f > 0.2){
            weight[2]++;
            weight[3]++;
            weight[7]++;
            weight[1]++;
            weight[8]--;
            weight[0]-=2;
            weight[6]--;
            weight[4]--;
        } else {
            weight[7]-=3;
        }
        if (f > 0.6 && wideTop)
            weight[7]+=2;

        if (0.2 < right.SharpJumpBetween(1, right.height() / 3, false)){
            weight[5]+=2;
            weight[9]-=3;
            weight[6]++;
            weight[0]-=2;
            weight[1]--;
            weight[4]-=2;
            weight[3]-=3;
        } else {
            weight[5]-=2;
        }

        if (0.2 < right.SharpJumpBetween(1, right.height() / 3, true)) {
            weight[6]++;
            weight[1]--;
        }

        f = right.SharpJumpBetween(right.height()/3,right.height()*2/3, true);
        if (f > 0.25){
            weight[5]+=2;
            weight[9]-=3;
            weight[6]++;
            weight[0]-=2;
            weight[1]--;
            weight[3]--;
        }

        f = right.SharpJumpBetween(right.height() / 2, right.height()-1, true);
        if (f > 0.27f) {
            weight[6]++;
            weight[2]++;
            weight[4]++;
            weight[0]--;
            weight[9]--;
            weight[5]++;
            weight[7]-=2;
            weight[8]--;
            weight[3]-=2;
        } else {
            weight[2]-=3;
        }

        f = left.SharpJumpBetween(left.height() / 3, left.height() *2 / 3);
        if (f > 0.15) {
            weight[2]++;
            weight[3]++;
            weight[4]+=2;
            weight[5]+=2;
            weight[6]-=2;
            weight[7]++;
            weight[8]--;
            weight[9]++;
            weight[0]-=2;
        } else {
            weight[3]-=2;
        }

        f = left.SharpJumpBetween(left.height()*2 / 3, left.height() -1, true);
        if (f > 0.15) {
            weight[3]++;
            weight[4]-=2;
            weight[5]++;
            weight[6]-=2;
            weight[7]-=2;
            weight[8]-=2;
            weight[9]++;
            weight[0]-=2;
        }

        f = left.SharpJumpBetween(left.height() / 2, left.height() -1);
        if (f > 0.15) {
            weight[4]+=2;
            weight[0]-=5;
        }

        bool leftBend = left.SmoothBendingBetween(left.height()/4, left.height()*3/4);
        bool rightBend = right.SmoothBendingBetween(left.height()/4, left.height()*3/4);
        if (leftBend && rightBend) {
            weight[8]+=3;
            weight[0]-=2;
        } else {
            weight[8]-=3;
        }

        size_t rightTopSpaces = i->CountWhite(2,false);
        if (rightTopSpaces > 2)
            weight[7]-=2;
        else
            weight[7]+=2;

        size_t leftBottomSpaces = i->CountWhite(i->height()-2);
        if (leftBottomSpaces >= i->width()/3){
            weight[4]+=2;
            weight[1]--;
        } else {
            weight[4]--;
            weight[1]++;
        }



        size_t top    = i->height()/6;
        size_t topMid = i->height()/3;
        size_t botMid = i->height()*2/3;
        
        
        int out = i->GetOutside(top, topMid, true,  true);
        if (out == 1) {
            weight[2]+=2;
            weight[3]+=2;
            weight[4]=-2;
            weight[9]-=3;
        }
        else if (out == 0) {
            weight[2]-=2;
            weight[3]-=2;
        }
        
        out = i->GetOutside(top, topMid, true,  false);
        if (out == 1) {
            weight[2]--;
            weight[3]--;
            weight[8]--;
            weight[9]--;
            weight[0]--;
        }
        else if (out == -1) {
            weight[8]-=3;
            weight[9]-=3;
            weight[0]-=3;
        }

        out = i->GetOutside(top, topMid, false, true);
        
        if (out == 1) {
            weight[5]+=2;
            weight[6]+=2;
            weight[8]--;
            weight[9]--;
            weight[0]--;
            weight[3]--;
        }
        else if (out == 0) {
            weight[5]--;
            weight[6]--;
            weight[3]++;
            weight[8]++;
            weight[9]++;
            weight[0]++;
        }

        out = i->GetOutside(top, topMid, false, false);
        if (out == 1) {
            weight[8]--;
            weight[9]--;
            weight[0]--;
            weight[5]++;
        }
        else if (out == 0) {
            weight[3]++;
            weight[8]++;
            weight[9]++;
            weight[0]++;
        }

        out = i->GetOutside(botMid, i->height()-3, true,  true);
        if (out == 0) {
            weight[6]++;
            weight[8]++;
            weight[0]++;
        }
        
        out = i->GetOutside(botMid, i->height()-3, true,  false);
        if (out == 0) {
            weight[6]++;
            weight[8]++;
            weight[0]++;
            weight[2]++;
        } else {
            weight[6]-=10;
            weight[8]-=10;
            weight[0]-=10;
        }
        if (out == 1) {
            weight[9]++;
            weight[1]--;
            weight[4]-=3;
            weight[5]++;
        }
        
        out = i->GetOutside(botMid, i->height()-3, false, true);
        if (out == 0) {
            weight[6]++;
            weight[8]++;
            weight[0]++;
        }
        else {
            weight[6]-=10;
            weight[8]-=10;
            weight[0]-=10;
        }
        
        out = i->GetOutside(botMid, i->height()-3, false, false);
        if (out == 0) {
            weight[6]++;
            weight[8]++;
            weight[0]++;
            weight[5]++;
            weight[3]++;
        }
        else if (out == 1) {
            weight[6]-=10;
            weight[8]-=10;
            weight[0]-=10;
            weight[2]+=2;
        }
        else {
            weight[6]-=10;
            weight[8]-=10;
            weight[0]-=10;
        }

        int topSum = i->CountColored(0, i->height()/2);
        int botSum = i->CountColored(i->height()/2, i->height());

        if (topSum < botSum) {
            weight[4]+=2;
            weight[9]-=2;
        }
        else {
            weight[9]+=2;
            weight[4]-=2;
        }

        cout << (max_element(&weight[0], &weight[9]+1) - &weight[0]);;
    }

    delete segList;
    return 0;
}
