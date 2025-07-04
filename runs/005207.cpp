#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

namespace matsuk {

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::pair;

typedef vector< vector<size_t> > BitMap;
typedef vector< vector<double> > ColorMap;
typedef pair<size_t, size_t> Coordinates;

/******************************************************************************
 * class BoundingBox -- implementation of image bounding rectangle
 *****************************************************************************/

class BoundingBox {
private:
    size_t left;            //! Leftmost coordinate of bounding rectangle
    size_t right;           //! Rightmost coordinate of bounding rectangle
    size_t top;             //! Topmost coordinate of bounding rectangle
    size_t bottom;          //! Bottommost coordinate of bounding rectangle

public:
    BoundingBox (size_t r = 0, size_t b = 0, 
                 size_t l = static_cast<size_t>(-1), 
                 size_t t = static_cast<size_t>(-1)) :
        left(l), right(r), top(t), bottom(b) {}

    size_t getMeanX () const { return (left >> 1) + (right >> 1); }

    size_t getWidth () const { return right - left + 1; }

    size_t getHeight () const { return bottom - top + 1; }

    size_t getArea () const { return getHeight() * getWidth(); }

    size_t getPivotX () const { return left; }

    size_t getPivotY () const { return top; }

    size_t getRight () const { return right; }

    size_t getBottom () const { return bottom; }

    void moveLeft (int delta) { left += delta; }

    void moveRight (int delta) { right += delta; }

    /*!
     * Widen borders
     */
    void adjust (size_t x, size_t y);

    BoundingBox & operator+= (const BoundingBox & rhs);
};

void BoundingBox::adjust (size_t x, size_t y) {
    if (x < left) {
        left = x;
    } else if (x > right) {
        right = x;
    }
    if (y < top) {
        top = y;
    } else if (y > bottom) {
        bottom = y;
    }
}

BoundingBox & BoundingBox::operator+= (const BoundingBox & rhs) {
    if (rhs.left < left) {
        left = rhs.left;
    }
    if (rhs.right > right) {
        right = rhs.right;
    }
    if (rhs.top < top) {
        top = rhs.top;
    }
    if (rhs.bottom > bottom) {
        bottom = rhs.bottom;
    }
    return *this;
}

/*!
 * Class-functor. Checks if string is blank within bounding box
 */
class IsNotBlank {
private:
    BoundingBox box;

public:
    IsNotBlank (const BoundingBox & b) : box(b) {}

    void setBounds (const BoundingBox & b) { box = b; }

    bool operator() (const string & line) const {
        bool isBlank = true;
        for (size_t x = box.getPivotX(); x < box.getRight(); ++x) {
            if (x >= line.length()) {
                break;
            }
            if (line[x] != '.') {
                isBlank = false;
                break;
            }
        }
        return ! isBlank;
    }
};

/******************************************************************************
 * class ImageASCII -- implementation of ASCII pseudo-image
 *****************************************************************************/

class ImageASCII {
private:
    vector<string> body;    //! The image body
    BoundingBox box;        //! This imade's place in the whole picture
    size_t segNum;          //! ID of this image part
    size_t width;           //! Image width

    /*!
     * Gather new connected segment from start point (x,y)
     */
    void GrowSegment (size_t x, size_t y, BitMap & mapping) const;

    /*!
     * Create connected segments mapping
     * \return Number of segments
     */
    size_t MapSegments (BitMap & mapping) const;

    /*!
     * Get bounding box for each segment from mapping
     */
    static void ExtractBoundingBoxes (const BitMap & mapping, size_t segments,
                                      vector<BoundingBox> & bounds);

    /*!
     * Get mean color of the region within bounding box
     */
    double MeanColor (const BoundingBox & bound) const;

    /*!
     * Get weight of the color code by position
     */
    double getColor (size_t x, size_t y) const;

    inline bool canGo (char curColor, char newColor) const {
        if (curColor == '@') {
            return (newColor != '.');
        } 
        return (newColor == '@');
    }

    inline bool isDark (char color) const {
        return (color == '@' || color == '#');
    }


public:
    ImageASCII (size_t num = 0) : segNum(num), width(0) {}

    /*!
     * Copy of the bounded segment from base
     */
    ImageASCII (const ImageASCII & base, size_t segment,
                const BitMap & mapping, const BoundingBox & bound);

    size_t getWidth () const {
        return width;
    }

    size_t getHeight () const {
        return body.size();
    }

    size_t getMeanX () const {
        return box.getMeanX();
    }

    /*!
     * Read input image from stdin
     */
    void LoadImage ();

    /*!
     * Segment image to disjoint pieces
     */
    void SeparateSegments (list<ImageASCII> &, BitMap &) const;

    /*!
     * Get reduced color map of the image
     */
    void ExtractColorMap (ColorMap & color) const;

    /*!
     * Split image in halfs. Returns separated right half
     */
    void ExtractRightHalf (ImageASCII & half);

    /*!
     * Combine two segments of the image
     */
    void MergeSegment (const ImageASCII & rhs,
                       BitMap & mapping);

    /*!
     * Make the bounding box wider
     */
    void WidenBoundary (size_t newWidth);
};

ImageASCII::ImageASCII (const ImageASCII & base, size_t segment,
                        const BitMap & mapping, const BoundingBox & bound) :
    body(bound.getHeight(), string(bound.getWidth(), '.')), 
    box(bound), segNum(segment), width(bound.getWidth()) 
{
    size_t dx = bound.getPivotX();
    size_t dy = bound.getPivotY();
    for (size_t x = 0; x < bound.getWidth(); ++x) {
        for (size_t y = 0; y < bound.getHeight(); ++y) {
            if (mapping[y+dy][x+dx] == segment) {
                body[y][x] = base.body[y+dy][x+dx];
            }
        }
    }
}

void ImageASCII::WidenBoundary (size_t newWidth) {
    size_t oldWidth = box.getWidth();
    if (newWidth <= oldWidth) {
        return;
    }
    size_t moveLeft = (newWidth - oldWidth) / 2;
    size_t moveRight = (newWidth - oldWidth) - moveLeft;
    moveLeft = box.getPivotX() - moveLeft;
    moveRight = box.getPivotX() + oldWidth - 1 + moveRight;
    box.adjust(moveLeft, box.getPivotY());
    box.adjust(moveRight, box.getPivotY());
    width = newWidth;
}

double ImageASCII::getColor (size_t x, size_t y) const {
    if (x >= getWidth() || y >= getHeight()) {
         return 0.0;
    }
    char code = body[y][x];
    switch (code) {
        case '%': return 1.0;
        case '#': return 2.0;
        case '@': return 3.0;
        default:  return 0.0;
    }
}

void ImageASCII::LoadImage() {
    string line;
    body.resize(0);
    while (cin >> line) {
        width = line.length();
        body.push_back(line);
    }
}

void ImageASCII::SeparateSegments (list<ImageASCII> & segments, 
                                   BitMap & mapping) const {
    segments.clear();
    size_t segmCount = MapSegments(mapping);
    vector<BoundingBox> bounds;
    ExtractBoundingBoxes(mapping, segmCount, bounds);
    for (size_t segment = 0; segment < segmCount; ++segment) {
        segments.push_back(ImageASCII(*this, segment+1, mapping, bounds[segment]));
    }
}

size_t ImageASCII::MapSegments (BitMap & mapping) const {
    size_t segments = 0;
    for (size_t x = 1; x + 1 < getWidth(); ++x) {
        for (size_t y = 1; y + 1 < getHeight(); ++y) {
            if (mapping[y][x] == 0 && (body[y][x]) == '@') {
                mapping[y][x] = ++segments;
                GrowSegment(x, y, mapping);
            }
        }
    }
    return segments;
}

void ImageASCII::GrowSegment (size_t x, size_t y, BitMap & mapping) const {
    if (y >= mapping.size() || x >= mapping[0].size() || mapping[y][x] == 0) {
        return;
    }
    size_t segment = mapping[y][x];

    vector<Coordinates> stack(1, Coordinates(x, y));
    while (stack.size() > 0) {
        x = stack.back().first;
        y = stack.back().second;
        stack.pop_back();
        char curColor = body[y][x];
        for (int dx = -1; dx <= 1; ++dx) {
            size_t newX = x + dx;
            for (int dy = -1; dy <= 1; ++dy) {
                size_t newY = y + dy;
                if (mapping[newY][newX] == 0 && canGo(curColor, body[newY][newX])) {
                    mapping[newY][newX] = segment;
                    if (isDark(body[newY][newX])) {
                        stack.push_back(Coordinates(newX, newY));
                    }
                }
            }
        }
    }
}

void ImageASCII::ExtractBoundingBoxes (const BitMap & mapping, 
                                       size_t segments,
                                       vector<BoundingBox> & bounds) {
    bounds.clear();
    bounds.resize(segments);
    for (size_t y = 0; y < mapping.size(); ++y) {
        for (size_t x = 0; x < mapping[y].size(); ++x) {
            size_t segment = mapping[y][x];
            if (segment > 0) {
                bounds[segment-1].adjust(x, y);
            }
        }
    }
}

void ImageASCII::ExtractColorMap (ColorMap & color) const {
    size_t dimY = color.size();
    size_t dimX = color.front().size();
    if (dimY == 0 || dimX == 0) {
        return;
    }
    size_t deltaX = getWidth() / dimX;
    size_t remX = getWidth() - deltaX * dimX;
    size_t deltaY = getHeight() / dimY;
    size_t remY = getHeight() - deltaY * dimY;

    size_t x1 = 0;
    size_t colX = 0;
    while (x1 < getWidth()) {
        size_t x2 = x1 + deltaX;
        if (remX > 0) {
            --remX;
            ++x2;
        }
        size_t y1 = 0;
        size_t colY = 0;
        size_t rY = remY;
        while (y1 < getHeight()) {
            size_t y2 = y1 + deltaY;
            if (rY > 0) {
                --rY;
                ++y2;
            }
            color[colY][colX] = MeanColor(BoundingBox(x2-1, y2-1, x1, y1));
            y1 = y2;
            ++colY;
        }
        x1 = x2;
        ++colX;
    }
}
    
void ImageASCII::ExtractRightHalf (ImageASCII & half) {
    size_t middle = getWidth() / 2;
    BoundingBox leftHalf(middle, getHeight(), 0, 0);
    BoundingBox rightHalf(getWidth(), getHeight(), middle, 0);
    IsNotBlank pred(rightHalf);
    vector<string>::const_iterator from = 
        find_if(body.begin(), body.end(), pred);
    vector<string>::const_reverse_iterator to = 
        find_if(body.rbegin(), body.rend(), pred);

    half.box.moveLeft(middle);
    half.width = getWidth() - middle;
    half.body.resize(to.base() - from);
    for (size_t x = 0; x < half.body.size(); ++x) {
        half.body[x] = from->substr(middle, half.width);
        ++from;
    }

    pred.setBounds(leftHalf);
    for (size_t y = 0; y < body.size(); ++y) {
        body[y].resize(middle);
    }
    from = find_if(body.begin(), body.end(), pred);
    to = find_if(body.rbegin(), body.rend(), pred);
    if (from != body.begin()) {
        copy(from, to.base(), body.begin());
    }
    body.resize(to.base() - from);
    box.moveRight(static_cast<int>(middle) - width);
    width = middle;
}

double ImageASCII::MeanColor (const BoundingBox & bound) const {
    double color = 0.0;
    size_t dx = bound.getPivotX();
    size_t dy = bound.getPivotY();
    for (size_t x = 0; x < bound.getWidth(); ++x) {
        for (size_t y = 0; y < bound.getHeight(); ++y) {
            color += getColor(x+dx, y+dy) / bound.getArea();
        }
    }
    return color;
}

void ImageASCII::MergeSegment (const ImageASCII & segment,
                               BitMap & mapping) {
    BoundingBox bound(box);
    bound += segment.box;
    vector<string> result(bound.getHeight(), string(bound.getWidth(), '.'));
    size_t dx = bound.getPivotX();
    size_t dy = bound.getPivotY();
    for (size_t y = 0; y < bound.getHeight(); ++y) {
        for (size_t x = 0; x < bound.getWidth(); ++x) {
            size_t code = mapping[y+dy][x+dx];
            size_t nx = x + dx;
            size_t ny = y + dy;
            if (code == segNum) {
                nx -= box.getPivotX();
                ny -= box.getPivotY();
                result[y][x] = body[ny][nx];
            } else if (code == segment.segNum) {
                mapping[ny][nx] = segNum;
                nx -= segment.box.getPivotX();
                ny -= segment.box.getPivotY();
                result[y][x] = segment.body[ny][nx];
            }
        }
    }
    box = bound;
    body = result;
    width = bound.getWidth();
}

/*!
 * Class-functor. Sorts out bad image segments
 */
class isDisproportional {
private:
    size_t totalWidth;

public:
    isDisproportional (size_t w) : totalWidth(w) {}

    bool operator() (const ImageASCII & i) const {
        if (i.getWidth() > i.getHeight() * 5) {
            return (i.getWidth() * 4 > totalWidth);
        }
        return false;
    }
};

/******************************************************************************
 * class Scanner -- implementation of ASCII digits scanner
 *****************************************************************************/

const size_t GAP_THRESHOLD = 15;

class Scanner {
private:
    ImageASCII image;               //! The whole input image
    list<ImageASCII> digits;        //! Separated digits of the image
    BitMap mapping;                 //! Segmented image map
    ColorMap features;              //! Coded representation of image color
    vector<size_t> classes;         //! String representation of digits

    static const size_t WINDOW_WIDTH    = 7;
    static const size_t WINDOW_HEIGHT   = 11;
    static const size_t PARAMETERS      = WINDOW_WIDTH * WINDOW_HEIGHT + 1;
    static const double weights[10][PARAMETERS];

    /*!
     * Filter garbage out and merge wrongly separated parts
     */
    void FilterDigits ();

    /*!
     * Split one digit if it's too wide
     */
    void SplitMerged ();

    /*!
     * Adjust bounding boxes evenly
     */
    void NormalizeBounds ();

public:
    Scanner () {}

    /*!
     * Get and parse input data
     */
    void ParseInput ();

    /*!
     * Print parsed digits to stdout
     */
    void PrintDigits () const;

    /*!
     * Print color features to stdout
     */
    void PrintFeatures () const;

    /*!
     * Classify digits, using logistic regression model weights
     */
    void Classify ();
};

void Scanner::FilterDigits () {
    digits.remove_if(isDisproportional(image.getWidth()));
    if (digits.size() <= 3) {
        return;
    }

    list<ImageASCII>::iterator base = digits.begin();
    list<ImageASCII>::iterator cur = base;
    size_t meanX;
    ++cur;
    do {
        meanX = base->getMeanX();
        size_t gap = 0;
        if (cur->getMeanX() > meanX) { 
            gap = cur->getMeanX() - meanX;
        } else {
            gap = meanX - cur->getMeanX();
        }
        if (gap * 100 / image.getWidth() < GAP_THRESHOLD) {
            base->MergeSegment(*cur, mapping);
            cur = digits.erase(cur);
        } else {
            base = cur;
            ++cur;
        }
    } while (cur != digits.end());
}

void Scanner::SplitMerged() {
    if (digits.size() != 2) {
        return;
    }
    list<ImageASCII>::iterator base;
    size_t firstWidth = digits.front().getWidth();
    size_t secondWidth = digits.back().getWidth();
    if (firstWidth * 2 > secondWidth * 3) {
        base = digits.begin();
    } else if (secondWidth * 2 > firstWidth * 3) {
        base = digits.end();
        --base;
    } else {
        return;
    }
    ImageASCII half(digits.size());
    base->ExtractRightHalf(half);
    digits.insert(++base, half);
}

void Scanner::NormalizeBounds () {
    list<ImageASCII>::iterator cur;
    size_t maxWidth = 0;
    for (cur = digits.begin(); cur != digits.end(); ++cur) {
        size_t w = cur->getWidth();
        if (w > maxWidth) {
            maxWidth = w;
        }
    }
    for (cur = digits.begin(); cur != digits.end(); ++cur) {
        cur->WidenBoundary(maxWidth);
    }
}

void Scanner::Classify () {
    classes.clear();
    for (size_t digit = 0; digit < features.size(); ++digit) {
        size_t bestMatch = 0;
        double record = 0.0;
        for (size_t target = 0; target < 10; ++target) {
            double prob = 0.0;
            for (size_t i = 0; i < PARAMETERS; ++i) {
                prob += features[digit][i] * weights[target][i];
            }
            if (prob >= record) {
                record = prob;
                bestMatch = target;
            }
        }
        classes.push_back(bestMatch);
    }
}

void Scanner::ParseInput () {
    image.LoadImage();
    mapping.resize(image.getHeight(), vector<size_t>(image.getWidth(), 0));
    image.SeparateSegments(digits, mapping);
    FilterDigits();
    SplitMerged();
    NormalizeBounds();

/*
    list<ImageASCII>::const_iterator s = digits.begin();
    while (s != digits.end()) {
    for (size_t i = 0; i < s->body.size(); ++i) {
        for (size_t j = 0; j < s->body[i].size(); ++j) {
            cout << s->body[i][j];
        }
        cout << endl;
    }
    cout << endl;

        ++s;
    }
    cout << endl;
//*/

    ColorMap colors(WINDOW_HEIGHT, vector<double>(WINDOW_WIDTH, 0.0));

    for (list<ImageASCII>::iterator s = digits.begin(); 
         s != digits.end(); ++s) 
    {
        s->ExtractColorMap(colors);
        vector<double> params(PARAMETERS);

        size_t curPar = 0;
        for (size_t i = 0; i < colors.size(); ++i) {
            for (size_t j = 0; j < colors[i].size(); ++j) {
                params[curPar++] = colors[i][j];
            }
        }
        params[curPar] = 1.0;
        features.push_back(params);
    }
}

void Scanner::PrintDigits () const {
    for (size_t digit = 0; digit < classes.size(); ++digit) {
        cout << classes[digit];
    }
    cout << endl;
}

void Scanner::PrintFeatures () const {
    for (size_t digit = 0; digit < features.size(); ++digit) {
        for (size_t i = 0; i + 1 < features[digit].size(); ++i) {
            cout << features[digit][i] << ',';
        }
        cout << endl;
    }
}

}; //namespace matsuk

using namespace matsuk;

int main(int argc, const char *argv[]) {
    Scanner scan;
    scan.ParseInput();
    if (argc > 1) {
        scan.PrintFeatures();
    } else {
        scan.Classify();
        scan.PrintDigits();
    }
    return 0;
}

/*!
 * Automatically inserted logistic regression weights.
 * Is not intended for human eyes! :)
 */
const double Scanner::weights[10][PARAMETERS] = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.67,0,0,0,-0.43,0,0,1.18,0,0,0,-1.47,-0.37,0,1.12,4.4,0,0,0,-0.91,0,0,1.68,0,0,0,0,0,0,0,0.49,0,0,0,0,-0.69,0,0,0,0,0,-0.37,-0.73,0,0,0,0,0,0,0,0,-0.6,0,0,0,0,0,-8.26},{1.22,0,-0.41,0,-1.05,0,0,0.45,0,0.8,0,0,-0.27,0,-0.42,0,0.33,0.62,0,0,0,0,0,0,0,0,0,0,0,0,0.27,-0.34,0,0,0,-0.77,0,0,0,0,0,0,0,0,0,0,0,0,0,-1.25,0,0,0.36,0,0,0,0,0,0,0,0,0,0,-1.03,-0.65,0,0,0,0,0,0.35,0,0,0,0,0.31,1.47,1.47},{0,0,0,0,0,0,0,0,0,0,0,0,0.32,0,0.47,0,0,0,0,0.87,0,0,-2.48,0,0,0,0,0.59,0,0,-0.73,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1.05,0,0,0,-1.39,0,-0.33,0,0.48,0,0,0,0,0.63,1.09,0,0,0,0,0,1.34,0,0,0.34,0,0.73,0,-4.98},{0,0,0,0,0.45,0,0,0,0,0,0,0.75,0,0,0,-0.91,0,0,0,0,0,0,-0.74,0,0,0,0,0,-0.66,-0.84,0,0,0,0,0,0,-0.56,0,0,0,0,0,0,0,-0.48,-0.51,0,0.63,0,0,0,0,-0.96,0.39,0.29,0.85,0,0,0,0,0,0,0,0.76,0.29,0,0,0,0,0,0,1.23,0,0,0,0,0,-4.75},{0,0,0,0,0,0,0,-3.18,-0.57,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.67,1.16,0.82,0,0,0,0,0,0.87,1.26,0,0,0,0,0,0,0,0,0.57,0.85,0,0,-0.75,0,0,0,0,0,0,0,-2.34,0,0,0,0,0,0,-1.92,-1.06,0,0.44,0.38,0,-0.93},{0,0,0,0,0,1.13,0,0,0,0,0,-0.45,0,0,0,0.42,0,-0.33,-0.61,-1.38,-1.4,0.52,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.32,-0.6,-0.75,0,0.24,0,0.39,0,-0.9,0,0,0.26,0,0,0,0,0,0.39,0,0.37,0,0,0,0,0,0,0,0,0.89,0,0,0,0,0,0,0,0,0,0,0,0,0,0.13},{0,-1.73,-0.54,0,0.38,1.11,0,0,0,0,0,-0.37,0,0,0,-0.41,0,0,0,-0.7,0,0,0,0,0,0,-0.33,-0.78,0.78,0.42,0,0,0,0,0,2.02,0,0,0,0,0,0,2.01,0,0,0,0,0,0,0,0,0,-0.52,0,0,0,0,0.59,0,0,0,0,0,0,0,0,0,0,0.33,0,0,0,0,0,0,0,0,-4.57},{2.58,1.43,0,0,0,1.54,0.68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-3.81,-0.55,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1.14,0,0,0,0,0,-0.56,0,0,0,0,0,0,0,0,0,0,0,0,0,-1.3,0,0,-0.53,-0.49,0,-0.56,0,0,0,-1.93},{-0.88,0,0,0,0,0,0,0,0,0,0,0,0,0,0.67,0,-0.68,0,0,0,0,0,0.59,0,0,0,0,0,-1.6,0.41,0.79,0,0,0,0,0,0.48,0.28,0,0,0,-0.73,1.46,0,0,0,0.36,0,0,1.02,0,0,0,0,0,0,1,-0.34,-0.71,0,0,0,0,0,0,-0.53,0,0,0,0,0,0,0,0,0,0,0,-6.76},{0,0,0,0,0,-0.53,0,0,0,0,0,0.35,0,0,0,0,-0.53,-0.88,0,0,0,1.1,0,0,0,0,0.95,0.87,0,0,0,0,0,0.28,0,0,0.38,0,0.77,0,0,0.48,-1.17,0,0,0.42,-0.42,0,0,-0.79,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.34,0,0,0,0,0,0,-0.36,-0.54,-0.68,0,0,-1.13} };