#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::istream;
using std::ostream;
using std::map;
using std::pair;
using std::max;
using std::min;
using std::queue;

namespace Geometry {

struct Point {
    double x;
    double y;

    Point() {
        x = 0.0;
        y = 0.0;
    }

    Point(const double x_, const double y_) {
        x = x_;
        y = y_;
    }

    Point(const int x_, const int y_) {
        x = static_cast<double>(x_);
        y = static_cast<double>(y_);
    }
};

struct SegmentOnLine { 

    double first_point;
    double second_point;

    SegmentOnLine(const double first_point_, const double second_point_) {
        first_point = min(first_point_, second_point_);
        second_point = max(first_point_, second_point_);
    }

    double Length() const {
        return second_point - first_point;
    }

    double LengthOfIntersection(const SegmentOnLine& rhs) const {
        if (rhs.first_point < first_point) {
            if (rhs.second_point > second_point) {
                return Length();
            }
            if (rhs.second_point < first_point) {
                return 0;
            }
            return rhs.second_point - first_point;
        }
        if (rhs.first_point > second_point) {
            return 0;
        }
        if (rhs.second_point < second_point) {
            return rhs.Length();
        }
        return second_point - rhs.first_point;
    }
};

struct Rectangle { //with axes parallel to axes
    Point left_top;
    double side_parallel_to_ox;
    double side_parallel_to_oy;

    Rectangle(Point& left_top_, const double ox_side_, const double oy_side_) {
        left_top = left_top_;
        side_parallel_to_ox = ox_side_;
        side_parallel_to_oy = oy_side_;
    }

    double Area() const {
        return side_parallel_to_ox * side_parallel_to_oy;
    }

    double AreaOfIntersection(const Rectangle& rhs) const {
        double intersection_on_ox = SegmentOnLine(left_top.x, left_top.x + side_parallel_to_ox).LengthOfIntersection(
            SegmentOnLine(rhs.left_top.x, rhs.left_top.x + rhs.side_parallel_to_ox));
        double intersection_on_oy = SegmentOnLine(left_top.y, left_top.y + side_parallel_to_oy).LengthOfIntersection(
            SegmentOnLine(rhs.left_top.y, rhs.left_top.y + rhs.side_parallel_to_oy));
        return intersection_on_ox * intersection_on_oy;
    }
};

}

namespace ASCIIGraphics {

const char WHITE = '.';
const char LIGHT_GRAY = '%';
const char DARK_GRAY = '#';
const char BLACK = '@';

class ASCIIPicture {
protected: 

    vector<vector<char> > image;

    struct Cell {
        int row;
        int column;

        Cell(const int row_, const int column_) {
            row = row_;
            column = column_;
        }
    };

public:

    ASCIIPicture() {
    }

    explicit ASCIIPicture(const vector<vector<char> >& image_): image(image_) {
    }

    bool IsEmpty() const {
        return image.empty();
    }

    int GetHeight() const {
        return static_cast<int>(image.size());
    }

    int GetWidth() const {
        return static_cast<int>(image[0].size());
    }

    void Read(istream& is) {
        image.clear();
        string current_line;
        while (getline(is, current_line)) {
            vector<char> current_row;
            current_row.resize(current_line.size());
            copy(current_line.begin(), current_line.end(), current_row.begin());
            image.push_back(current_row);
        }
    }

    void Print(ostream& os) const {
        for (int current_row_index = 0; current_row_index < GetHeight(); ++current_row_index) {
            for (int current_column_index = 0; current_column_index < GetWidth(); ++current_column_index) {
                os << image[current_row_index][current_column_index];
            }
            os << "\n";
        }
    }

    virtual void AutoCrop() = 0;

protected: 

    bool RowIsWhite(const int row_index) const {
        bool result = true;
        for (int current_column_index = 0; current_column_index < GetWidth(); ++current_column_index) {
            result = result && (image[row_index][current_column_index] == WHITE);
        }
        return result;
    }

    bool ColumnIsWhite(const int column_index) const {
        bool result = true;
        for (int current_row_index = 0; current_row_index < GetHeight(); ++current_row_index) {
            result = result && (image[current_row_index][column_index] == WHITE);
        }
        return result;
    }

    bool ColumnHasBlackCells(const int column_index) const {
        bool result = false;
        for (int current_row_index = 0; current_row_index < GetHeight(); ++current_row_index) {
            result = result || (image[current_row_index][column_index] == BLACK);
        }
        return result;
    }

    bool RowHasBlackCells(const int row_index) const {
        bool result = false;
        for (int current_column_index = 0; current_column_index < GetWidth(); ++current_column_index) {
            result = result || (image[row_index][current_column_index] == BLACK);
        }
        return result;
    }

    void DeleteRow(const int row_index) {
        image.erase(image.begin() + row_index);
    }

    void DeleteColumn(const int column_index) {
        for (int current_row_index = 0; current_row_index < GetHeight(); ++current_row_index) {
            image[current_row_index].erase(image[current_row_index].begin() + column_index);
        }
    }

    void DeleteColumns(const int left_column_index, const int right_column_index) {
        for (int current_row_index = 0; current_row_index < GetHeight(); ++current_row_index) {
            image[current_row_index].erase(image[current_row_index].begin() + left_column_index, image[current_row_index].begin() + right_column_index);
        }
    }

    void FillColumn(const int column_index, const char color) {
        for (int current_row_index = 0; current_row_index < GetHeight(); ++current_row_index) {
            image[current_row_index][column_index] = color;
        }
    }

    bool CellInImage(const Cell& cell) const {
        return ((cell.row >= 0) && (cell.row < GetHeight()) && (cell.column >= 0) && (cell.column < GetWidth()));
    }

    void GetNeighbours(const Cell& cell, vector<Cell>& neighbours) const {
        static const int NUMBER_OF_DIRECTIONS = 8;
        static const int DX[NUMBER_OF_DIRECTIONS] = {1, 1, 0, -1, -1, -1, 0, 1};
        static const int DY[NUMBER_OF_DIRECTIONS] = {0, 1, 1, 1, 0, -1, -1, -1};
        for (int current_direction = 0; current_direction < NUMBER_OF_DIRECTIONS; ++current_direction) {
            if (CellInImage(Cell(cell.row + DY[current_direction], cell.column + DX[current_direction]))) {
                neighbours.push_back(Cell(cell.row + DY[current_direction], cell.column + DX[current_direction]));
            }
        }
    }
};

class ASCIIDigit: public ASCIIPicture {
private:

    void ClearNoise() {
        vector<int> number_of_cells_in_component;
        int current_component_index = 1;
        number_of_cells_in_component.assign(1, 0);
        vector<vector<bool> > already_been;
        vector<vector<int> > components;
        already_been.assign(GetHeight(), vector<bool>(GetWidth(), false));
        components.assign(GetHeight(), vector<int>(GetWidth(), 0));
        for (int current_row_index = 0; current_row_index < GetHeight(); ++current_row_index) {
            for (int current_column_index = 0; current_column_index < GetWidth(); ++current_column_index) {
                if ((!already_been[current_row_index][current_column_index]) && (image[current_row_index][current_column_index] != WHITE)) {
                    number_of_cells_in_component.push_back(0);
                    queue<Cell> cell_queue;
                    already_been[current_row_index][current_column_index] = true;
                    components[current_row_index][current_column_index] = current_component_index;
                    ++number_of_cells_in_component[current_component_index];
                    cell_queue.push(Cell(current_row_index, current_column_index));
                    while (!cell_queue.empty()) {
                        Cell current_cell = cell_queue.front();
                        cell_queue.pop();
                        vector<Cell> neighbours;
                        GetNeighbours(current_cell, neighbours);
                        for (vector<Cell>::const_iterator current_neighbour = neighbours.begin(); current_neighbour != neighbours.end(); ++current_neighbour) {
                            if ((!already_been[current_neighbour->row][current_neighbour->column]) && (image[current_neighbour->row][current_neighbour->column] != WHITE)) {
                                already_been[current_neighbour->row][current_neighbour->column] = true;
                                components[current_neighbour->row][current_neighbour->column] = current_component_index;
                                ++number_of_cells_in_component[current_component_index];
                                cell_queue.push(*current_neighbour);
                            }
                        }
                    }
                    ++current_component_index;
                }
            }
        }
        int maximal_component_index = max_element(number_of_cells_in_component.begin(), number_of_cells_in_component.end()) - number_of_cells_in_component.begin();
        for (int current_row_index = 0; current_row_index < GetHeight(); ++current_row_index) {
            for (int current_column_index = 0; current_column_index < GetWidth(); ++current_column_index) {
                if (components[current_row_index][current_column_index] != maximal_component_index) {
                    image[current_row_index][current_column_index] = WHITE;
                }
            }
        }
    }

public: 

    ASCIIDigit() {
    }

    ASCIIDigit(const vector<vector<char> >& image_, const int left_column_index, const int right_column_index) {
        image.assign(image_.size(), vector<char>(right_column_index - left_column_index));
        for (int current_row_index = 0; current_row_index < GetHeight(); ++current_row_index) {
            for (int current_column_index = left_column_index; current_column_index < right_column_index; ++current_column_index) {
                image[current_row_index][current_column_index - left_column_index] = image_[current_row_index][current_column_index];
            }
        }
    }

    void AutoCrop() {
        while (!IsEmpty() && (!RowHasBlackCells(0))) {
            DeleteRow(0);
        }
        if (IsEmpty()) {
            return;
        }
        while (!RowHasBlackCells(GetHeight() - 1)) {
            DeleteRow(GetHeight() - 1);
        }
        while (ColumnIsWhite(0)) {
            DeleteColumn(0);
        }
        while (ColumnIsWhite(GetWidth() - 1)) {
            DeleteColumn(GetWidth() - 1);
        }
    }

    void Normalize() {
        for (int current_column_index = 0; current_column_index < GetWidth(); ++current_column_index) {
            if (!ColumnHasBlackCells(current_column_index)) {
                FillColumn(current_column_index, WHITE);
            }
        }
        ClearNoise();
        AutoCrop();
    }

    void GetFrequenciesOfWhiteCells(const int number_of_rows, const int number_of_columns, vector<vector<double> >& frequence_in_segment) {
        using Geometry::Point;
        using Geometry::Rectangle;
        frequence_in_segment.assign(number_of_rows, vector<double>(number_of_columns, 0));
        double side_of_segment_parallel_to_ox = static_cast<double>(GetWidth()) / static_cast<double>(number_of_columns);
        double side_of_segment_parallel_to_oy = static_cast<double>(GetHeight()) / static_cast<double>(number_of_rows);
        for (int current_row_index = 0; current_row_index < number_of_rows; ++current_row_index) {
            for (int current_column_index = 0; current_column_index < number_of_columns; ++current_column_index) {
                Point left_top(side_of_segment_parallel_to_ox * current_column_index, side_of_segment_parallel_to_oy * current_row_index);
                Rectangle current_segment(left_top, side_of_segment_parallel_to_ox, side_of_segment_parallel_to_oy);
                for (int current_row_in_picture = 0; current_row_in_picture < GetHeight(); ++current_row_in_picture) {
                    for (int current_column_in_picture = 0; current_column_in_picture < GetWidth(); ++current_column_in_picture) {
                        if (image[current_row_in_picture][current_column_in_picture] == WHITE) {
                            Point left_top_in_cell(current_column_in_picture, current_row_in_picture);
                            Rectangle current_cell(left_top_in_cell, 1.0, 1.0); 
                            frequence_in_segment[current_row_index][current_column_index] += current_segment.AreaOfIntersection(current_cell) / current_segment.Area();
                        }
                    }
                }
            }
        }
    }

private: 

    double Distance(vector<vector<double> >& frequence_in_segment, vector<vector<double> >& reference_frequence_in_segment) {
        double result = 0;
        for (int current_row_index = 0; current_row_index < static_cast<int>(frequence_in_segment.size()); ++current_row_index) {
            for (int current_column_index = 0; current_column_index < static_cast<int>(frequence_in_segment[0].size()); ++current_column_index) {
                result += fabs(frequence_in_segment[current_row_index][current_column_index] - reference_frequence_in_segment[current_row_index][current_column_index]);
            }
        }
        return result;
    }

public: 

    int Recognize() {
        static const int ROWS_OF_SEGMENTS = 15;
        static const int COLUMNS_OF_SEGMENTS = 12;
        static const double REFERENCE_VALUES_OF_FREQUENCIES[10][ROWS_OF_SEGMENTS * COLUMNS_OF_SEGMENTS] = {
            {1, 0.974359, 0.833333, 0.448718, 0.128205, 0, 0, 0.128205, 0.448718, 0.858974, 1, 1, 
            1, 0.641026, 0, 0, 0.128205, 0.333333, 0.333333, 0.128205, 0, 0.0384615, 0.782051, 1, 
            0.807692, 0.115385, 0, 0.589744, 0.948718, 1, 1, 0.948718, 0.307692, 0, 0.141026, 0.961538, 
            0.538462, 0, 0, 0.923077, 1, 1, 1, 1, 0.839744, 0.0576923, 0, 0.641026, 
            0.307692, 0, 0, 0.923077, 1, 1, 1, 1, 1, 0.358974, 0, 0.179487, 
            0, 0, 0.134615, 0.967949, 1, 1, 1, 1, 1, 0.538462, 0, 0, 
            0, 0, 0.230769, 1, 1, 1, 1, 1, 1, 0.538462, 0, 0, 
            0, 0, 0.230769, 1, 1, 1, 1, 1, 1, 0.538462, 0, 0, 
            0, 0, 0.230769, 1, 1, 1, 1, 1, 1, 0.538462, 0, 0, 
            0, 0, 0.134615, 0.967949, 1, 1, 1, 1, 1, 0.538462, 0, 0, 
            0.179487, 0, 0, 0.923077, 1, 1, 1, 1, 1, 0.358974, 0, 0.179487, 
            0.538462, 0, 0, 0.923077, 1, 1, 1, 1, 0.839744, 0.0576923, 0, 0.641026, 
            0.935897, 0.141026, 0, 0.461538, 0.948718, 1, 1, 0.923077, 0.307692, 0, 0.141026, 0.961538, 
            1, 0.782051, 0.0384615, 0, 0.128205, 0.333333, 0.333333, 0.025641, 0, 0.179487, 0.846154, 1, 
            1, 1, 0.858974, 0.448718, 0.128205, 0, 0, 0.25641, 0.448718, 0.910256, 1, 1},
            {1, 1, 1, 1, 1, 0.971765, 0.882353, 0.741176, 0.282353, 0.4, 1, 1, 
            1, 0.868235, 0.764706, 0.694118, 0.323529, 0.245882, 0, 0, 0, 0.4, 1, 1, 
            0.558824, 0.443529, 0.352941, 0.296471, 0, 0, 0, 0, 0, 0.4, 1, 1, 
            1, 1, 1, 0.84, 0, 0, 0, 0, 0, 0.4, 1, 1, 
            1, 1, 1, 0.84, 0, 0, 0, 0, 0, 0.4, 1, 1, 
            1, 1, 1, 0.84, 0, 0, 0, 0, 0, 0.4, 1, 1, 
            1, 1, 1, 0.84, 0, 0, 0, 0, 0, 0.4, 1, 1, 
            1, 1, 1, 0.84, 0, 0, 0, 0, 0, 0.4, 1, 1, 
            1, 1, 1, 0.84, 0, 0, 0, 0, 0, 0.4, 1, 1, 
            1, 1, 1, 0.84, 0, 0, 0, 0, 0, 0.4, 1, 1, 
            1, 1, 1, 0.84, 0, 0, 0, 0, 0, 0.4, 1, 1, 
            1, 1, 1, 0.84, 0, 0, 0, 0, 0, 0.4, 1, 1, 
            1, 1, 1, 0.84, 0, 0, 0, 0, 0, 0.4, 1, 1, 
            1, 1, 1, 0.84, 0, 0, 0, 0, 0, 0.4, 1, 1, 
            1, 0.505882, 0.117647, 0.0988235, 0, 0, 0, 0, 0, 0.0470588, 0.117647, 0.117647},
            {1, 0.968664, 0.677419, 0.483871, 0.0552995, 0, 0, 0.0552995, 0.525346, 0.969585, 1, 1, 
            0.639631, 0.0129032, 0, 0, 0, 0, 0, 0, 0, 0.0258065, 0.821198, 1, 
            0.406452, 0.0967742, 0.0967742, 0.373272, 0.580645, 0.497696, 0.0165899, 0, 0, 0, 0.169585, 0.969585, 
            1, 1, 1, 1, 1, 1, 0.610138, 0.0258065, 0, 0, 0, 0.685714, 
            1, 1, 1, 1, 1, 1, 0.907834, 0.0709677, 0, 0, 0, 0.685714, 
            1, 1, 1, 1, 1, 1, 0.790783, 0, 0, 0, 0.0193548, 0.898618, 
            1, 1, 1, 1, 1, 1, 0.270968, 0, 0, 0.0129032, 0.413825, 1, 
            1, 1, 1, 1, 1, 0.529954, 0.0442396, 0, 0, 0.4, 1, 1, 
            1, 1, 1, 1, 0.646083, 0.0322581, 0, 0, 0.265438, 0.941935, 1, 1, 
            1, 1, 1, 0.428571, 0.0221198, 0, 0, 0.313364, 0.95576, 1, 1, 1, 
            1, 0.898618, 0.354839, 0.0138249, 0, 0, 0.529032, 0.967742, 1, 1, 1, 1, 
            1, 0.282949, 0, 0, 0.0774194, 0.635945, 0.97788, 1, 1, 1, 1, 1, 
            0.262673, 0.00276498, 0, 0, 0.282028, 0.580645, 0.580645, 0.580645, 0.580645, 0.580645, 0.580645, 0.580645, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0.165899, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.165899},
            {1, 0.936118, 0.540541, 0, 0, 0, 0, 0, 0.405405, 0.896806, 1, 1, 
            0.923833, 0.108108, 0, 0, 0.0835381, 0.181818, 0.181818, 0.181818, 0.019656, 0.0982801, 0.700246, 1, 
            0.412776, 0, 0, 0.167076, 0.85258, 1, 1, 1, 0.498771, 0.022113, 0.0810811, 0.980344, 
            0.717445, 0.363636, 0.363636, 0.4914, 1, 1, 1, 1, 1, 0.0810811, 0, 0.972973, 
            1, 1, 1, 1, 1, 1, 1, 1, 0.889435, 0.044226, 0.135135, 0.985258, 
            1, 1, 1, 1, 1, 1, 0.953317, 0.515971, 0.04914, 0.0540541, 0.65602, 1, 
            1, 1, 1, 1, 1, 1, 0.280098, 0, 0.110565, 0.670762, 0.931204, 1, 
            1, 1, 1, 1, 1, 1, 0.538084, 0.272727, 0.117936, 0, 0.304668, 0.992629, 
            1, 1, 1, 1, 1, 1, 1, 1, 0.896806, 0.184275, 0, 0.589681, 
            1, 1, 1, 1, 1, 1, 1, 1, 1, 0.700246, 0, 0.029484, 
            1, 1, 1, 1, 1, 1, 1, 1, 1, 0.72973, 0, 0, 
            0.422604, 0.363636, 0.400491, 0.955774, 1, 1, 1, 1, 1, 0.523342, 0, 0.265356, 
            0.648649, 0, 0, 0.255528, 0.764128, 1, 1, 1, 0.646192, 0.110565, 0, 0.737101, 
            0.995086, 0.479115, 0, 0, 0.02457, 0.402948, 0.550369, 0.181818, 0.019656, 0, 0.773956, 0.995086, 
            1, 0.995086, 0.724816, 0.405405, 0, 0, 0, 0.2457, 0.454545, 0.872236, 0.995086, 1},
            {1, 1, 1, 1, 1, 0.945032, 0.2537, 0, 0, 0, 0.818182, 1, 
            1, 1, 1, 1, 1, 0.505285, 0, 0, 0, 0, 0.818182, 1, 
            1, 1, 1, 1, 0.84778, 0.0401691, 0, 0, 0, 0, 0.818182, 1, 
            1, 1, 1, 1, 0.22833, 0, 0, 0, 0, 0, 0.818182, 1, 
            1, 1, 1, 0.534884, 0, 0.0211416, 0.317125, 0, 0, 0, 0.818182, 1, 
            1, 1, 0.752643, 0.0634249, 0, 0.486258, 0.545455, 0, 0, 0, 0.818182, 1, 
            1, 0.932347, 0.114165, 0, 0.205074, 0.97463, 0.545455, 0, 0, 0, 0.818182, 1, 
            1, 0.454545, 0, 0, 0.881607, 1, 0.545455, 0, 0, 0, 0.818182, 1, 
            0.727273, 0.0338266, 0, 0.45666, 1, 1, 0.545455, 0, 0, 0, 0.818182, 1, 
            0.15222, 0, 0.0634249, 0.748414, 0.767442, 0.767442, 0.418605, 0, 0, 0, 0.627907, 0.767442, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0.837209, 0.837209, 0.837209, 0.837209, 0.837209, 0.837209, 0.45666, 0, 0, 0, 0.684989, 0.837209, 
            1, 1, 1, 1, 1, 1, 0.545455, 0, 0, 0, 0.818182, 1, 
            1, 1, 1, 1, 1, 1, 0.545455, 0, 0, 0, 0.818182, 1, 
            1, 1, 1, 1, 1, 1, 0.545455, 0, 0, 0, 0.818182, 1},
            {1, 1, 0.565111, 0, 0, 0, 0, 0, 0, 0, 0, 0.648649, 
            1, 1, 0.27027, 0, 0.142506, 0.181818, 0.181818, 0.181818, 0.181818, 0.181818, 0.181818, 0.712531, 
            1, 0.872236, 0.0737101, 0, 0.783784, 1, 1, 1, 1, 1, 1, 1, 
            1, 0.621622, 0, 0.0884521, 0.960688, 1, 1, 1, 1, 1, 1, 1, 
            1, 0.326781, 0, 0.550369, 1, 1, 1, 1, 1, 1, 1, 1, 
            0.997543, 0.27027, 0.044226, 0.820639, 0.552826, 0.0859951, 0, 0, 0.405405, 0.724816, 0.965602, 1, 
            0.972973, 0, 0.029484, 0.0884521, 0.142506, 0.181818, 0.181818, 0.181818, 0.0786241, 0, 0.361179, 0.936118, 
            0.737101, 0, 0, 0.402948, 0.941032, 1, 1, 1, 0.734644, 0.022113, 0, 0.560197, 
            0.936118, 0.818182, 0.818182, 0.955774, 1, 1, 1, 1, 1, 0.346437, 0, 0.0589681, 
            1, 1, 1, 1, 1, 1, 1, 1, 1, 0.405405, 0, 0, 
            0.909091, 0.909091, 0.945946, 1, 1, 1, 1, 1, 1, 0.405405, 0, 0, 
            0.265356, 0, 0.199017, 1, 1, 1, 1, 1, 1, 0.405405, 0, 0.206388, 
            0.737101, 0, 0.022113, 0.646192, 1, 1, 1, 1, 0.646192, 0.110565, 0, 0.648649, 
            0.995086, 0.646192, 0.0982801, 0.019656, 0.243243, 0.636364, 0.636364, 0.243243, 0.019656, 0, 0.626536, 0.995086, 
            1, 1, 0.749386, 0.454545, 0.0982801, 0, 0, 0.0982801, 0.454545, 0.872236, 0.995086, 1},
            {1, 1, 0.981424, 0.789474, 0.325077, 0, 0, 0, 0.348297, 0.673375, 0.987616, 1, 
            1, 0.900929, 0.365325, 0, 0.136223, 0.235294, 0.235294, 0.235294, 0.0495356, 0, 0.467492, 1, 
            0.981424, 0.235294, 0, 0.278638, 0.913313, 1, 1, 1, 0.572755, 0, 0.0541796, 0.70743, 
            0.789474, 0, 0.0743034, 0.888545, 1, 1, 1, 1, 0.986068, 0.30805, 0.0294118, 0.363777, 
            0.315789, 0, 0.204334, 1, 1, 0.860681, 0.852941, 0.868421, 1, 1, 1, 1, 
            0.0928793, 0, 0.473684, 0.860681, 0.479876, 0.0154799, 0, 0.0309598, 0.363777, 0.791022, 1, 1, 
            0, 0, 0.0835913, 0.0835913, 0, 0, 0.382353, 0.221362, 0, 0.0371517, 0.431889, 0.979876, 
            0, 0, 0.00928793, 0.52322, 0.941176, 0.941176, 1, 0.975232, 0.662539, 0.0278638, 0, 0.49226, 
            0, 0, 0.157895, 1, 1, 1, 1, 1, 1, 0.473684, 0, 0.120743, 
            0, 0, 0.157895, 1, 1, 1, 1, 1, 1, 0.473684, 0, 0, 
            0.26935, 0, 0.427245, 1, 1, 1, 1, 1, 1, 0.473684, 0, 0, 
            0.789474, 0, 0.431889, 0.986068, 1, 1, 1, 1, 0.986068, 0.431889, 0, 0.334365, 
            0.981424, 0.235294, 0, 0.390093, 0.794118, 0.989164, 1, 0.848297, 0.390093, 0, 0.0541796, 0.846749, 
            1, 0.900929, 0.416409, 0.0510836, 0, 0.22291, 0.235294, 0.0619195, 0, 0.0681115, 0.640867, 1, 
            1, 1, 1, 0.668731, 0.325077, 0, 0, 0.185759, 0.510836, 0.907121, 1, 1},
            {0.171429, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.171429, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0.671429, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.114286, 0, 0, 0.171429, 
            1, 1, 1, 1, 1, 1, 1, 0.542857, 0, 0, 0, 0.514286, 
            1, 1, 1, 1, 1, 1, 0.928571, 0.1, 0, 0, 0.2, 1, 
            1, 1, 1, 1, 1, 1, 0.514286, 0, 0, 0, 0.714286, 1, 
            1, 1, 1, 1, 1, 0.914286, 0.0857143, 0, 0, 0.228571, 1, 1, 
            1, 1, 1, 1, 1, 0.657143, 0, 0, 0, 0.742857, 1, 1, 
            1, 1, 1, 1, 0.9, 0.0714286, 0, 0, 0.257143, 1, 1, 1, 
            1, 1, 1, 1, 0.285714, 0, 0, 0, 0.6, 1, 1, 1, 
            1, 1, 1, 0.771429, 0, 0, 0, 0.0571429, 0.885714, 1, 1, 1, 
            1, 1, 1, 0.428571, 0, 0, 0, 0.628571, 1, 1, 1, 1, 
            1, 1, 0.871429, 0.0428571, 0, 0, 0.142857, 1, 1, 1, 1, 1, 
            1, 1, 0.4, 0, 0, 0, 0.657143, 1, 1, 1, 1, 1, 
            1, 1, 0.0571429, 0, 0, 0.342857, 1, 1, 1, 1, 1, 1},
            {1, 1, 0.896806, 0.454545, 0.0982801, 0, 0, 0, 0.257985, 0.896806, 1, 1, 
            1, 0.847666, 0.0982801, 0.019656, 0.243243, 0.636364, 0.636364, 0.243243, 0.019656, 0.0982801, 0.700246, 1, 
            0.980344, 0.0810811, 0, 0.432432, 1, 1, 1, 1, 0.432432, 0, 0.216216, 0.904177, 
            0.972973, 0, 0, 0.756757, 1, 1, 1, 1, 0.756757, 0, 0, 0.648649, 
            0.972973, 0, 0, 0.609337, 1, 1, 1, 1, 0.756757, 0, 0, 0.796069, 
            1, 0.5086, 0.0540541, 0.19656, 0.810811, 0.909091, 0.909091, 0.810811, 0.19656, 0, 0.503686, 1, 
            1, 1, 0.85258, 0.154791, 0, 0, 0, 0, 0, 0.584767, 0.980344, 1, 
            0.992629, 0.555283, 0.272727, 0.0663391, 0.125307, 0.272727, 0.272727, 0.125307, 0, 0.250614, 0.702703, 0.992629, 
            0.855037, 0, 0, 0.353808, 0.90172, 1, 1, 0.90172, 0.707617, 0.029484, 0, 0.589681, 
            0.206388, 0, 0.036855, 0.837838, 1, 1, 1, 1, 1, 0.523342, 0, 0.029484, 
            0, 0, 0.0810811, 1, 1, 1, 1, 1, 1, 0.72973, 0, 0, 
            0.0589681, 0, 0.0810811, 1, 1, 1, 1, 1, 1, 0.464373, 0, 0.0589681, 
            0.648649, 0, 0.0589681, 0.756757, 1, 1, 1, 1, 0.734644, 0.022113, 0, 0.412776, 
            0.995086, 0.479115, 0, 0.019656, 0.243243, 0.636364, 0.636364, 0.390663, 0.0786241, 0, 0.479115, 0.936118, 
            1, 0.995086, 0.724816, 0.110565, 0, 0, 0, 0, 0.110565, 0.577396, 0.995086, 1},
            {1, 1, 0.914149, 0.54849, 0.0953895, 0, 0, 0.238474, 0.691574, 0.952305, 1, 1, 
            1, 0.667727, 0.0874404, 0, 0.0317965, 0.235294, 0.235294, 0.108108, 0, 0.192369, 0.810811, 1, 
            0.86407, 0.0612083, 0, 0.314785, 0.82194, 1, 1, 0.888712, 0.45787, 0, 0.192369, 0.875994, 
            0.200318, 0, 0.0476948, 0.871224, 1, 1, 1, 1, 0.978537, 0.379173, 0, 0.496025, 
            0, 0, 0.405405, 1, 1, 1, 1, 1, 1, 0.72973, 0, 0.27663, 
            0, 0, 0.405405, 1, 1, 1, 1, 1, 1, 0.72973, 0, 0, 
            0.391097, 0, 0.281399, 1, 1, 1, 1, 1, 1, 0.338633, 0, 0, 
            0.812401, 0.0174881, 0.00476948, 0.440382, 0.949126, 1, 1, 0.949126, 0.440382, 0.00476948, 0, 0, 
            1, 0.707472, 0.104928, 0, 0.0516693, 0.382353, 0.382353, 0.0516693, 0.100159, 0.414944, 0, 0, 
            1, 1, 0.856916, 0.294118, 0.294118, 0.294118, 0.294118, 0.532591, 0.885533, 0.72973, 0, 0.0953895, 
            1, 1, 1, 1, 1, 1, 1, 1, 1, 0.4531, 0, 0.324324, 
            0.670906, 0.470588, 0.506359, 0.978537, 1, 1, 1, 1, 0.763911, 0.0119237, 0, 0.667727, 
            0.86407, 0.0612083, 0, 0.45787, 0.955485, 1, 1, 0.888712, 0.314785, 0, 0.259141, 0.990461, 
            1, 0.667727, 0.0874404, 0, 0.18442, 0.235294, 0.235294, 0.108108, 0, 0.416534, 0.91097, 1, 
            1, 1, 0.878378, 0.441176, 0.0953895, 0, 0, 0.381558, 0.834658, 0.990461, 1, 1}};

        static const double REFERENCE_VALUES_OF_FREQUENCIES_ITALIC[10][ROWS_OF_SEGMENTS * COLUMNS_OF_SEGMENTS] = {
            {1, 1, 1, 1, 1, 1, 1, 0.899614, 0.405405, 0, 0, 0.324324, 
            1, 1, 1, 1, 1, 1, 0.569498, 0.0559846, 0, 0, 0, 0.196911, 
            1, 1, 1, 1, 1, 0.478764, 0.023166, 0, 0.208494, 0, 0, 0.173745, 
            1, 1, 1, 1, 0.557915, 0.0405405, 0.0472973, 0.539575, 0.733591, 0, 0, 0.0810811, 
            1, 1, 1, 0.864865, 0.0617761, 0, 0.478764, 1, 0.698842, 0, 0, 0.266409, 
            1, 1, 0.913127, 0.202703, 0, 0.34749, 0.942085, 1, 0.397683, 0, 0, 0.208494, 
            1, 0.998069, 0.399614, 0, 0.0888031, 0.918919, 1, 0.876448, 0.046332, 0, 0, 0.521236, 
            1, 0.945946, 0, 0.0540541, 0.72973, 1, 1, 0.621622, 0, 0, 0.148649, 0.986486, 
            1, 0.494208, 0, 0.420849, 1, 1, 1, 0.320463, 0, 0, 0.57529, 1, 
            0.975869, 0.0318533, 0.0289575, 0.80888, 1, 1, 0.715251, 0.0144788, 0, 0.212355, 0.965251, 1, 
            0.6139, 0, 0.34749, 1, 1, 0.953668, 0.173745, 0, 0.162162, 0.88417, 1, 1, 
            0.254826, 0.011583, 0.706564, 1, 0.901544, 0.310811, 0, 0.301158, 0.891892, 1, 1, 1, 
            0, 0.046332, 0.949807, 0.625483, 0.173745, 0, 0.394788, 0.956564, 1, 1, 1, 1, 
            0.023166, 0, 0.254826, 0, 0.0559846, 0.505792, 0.936293, 1, 1, 1, 1, 1, 
            0.498069, 0, 0, 0.405405, 0.899614, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 0.69386, 0.126156, 0, 
            1, 1, 1, 1, 1, 1, 1, 0.956266, 0.286796, 0.0126156, 0, 0.413793, 
            1, 1, 1, 1, 1, 0.818335, 0.447435, 0.0622372, 0, 0, 0.280067, 0.971405, 
            1, 1, 1, 1, 0.756098, 0.058032, 0.101766, 0.00925147, 0, 0.0185029, 0.818335, 1, 
            1, 1, 1, 1, 0.751892, 0.571909, 0.566863, 0.00336417, 0.29016, 0.868797, 1, 1, 
            1, 1, 1, 1, 1, 0.788057, 0.0756939, 0.171573, 0.915896, 1, 1, 1, 
            1, 1, 1, 1, 0.993272, 0.254836, 0.0740118, 0.861228, 1, 1, 1, 1, 
            1, 1, 1, 1, 0.460892, 0.0353238, 0.596299, 1, 1, 1, 1, 1, 
            1, 1, 1, 0.79815, 0.0269134, 0.206897, 1, 1, 1, 1, 1, 1, 
            1, 1, 0.987384, 0.272498, 0.00420521, 0.687132, 1, 1, 1, 1, 1, 1, 
            1, 1, 0.654331, 0, 0.0647603, 1, 1, 1, 1, 1, 1, 1, 
            1, 0.944491, 0.0437342, 0, 0.498738, 1, 1, 1, 1, 1, 1, 1, 
            0.99159, 0.431455, 0, 0.0134567, 0.788057, 1, 1, 1, 1, 1, 1, 1, 
            0.706476, 0, 0, 0.356602, 1, 1, 1, 1, 1, 1, 1, 1, 
            0.141295, 0, 0.49201, 0.752733, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.697253, 0.306838, 
            1, 1, 1, 1, 1, 1, 1, 1, 0.612507, 0.218586, 0.012858, 0, 
            1, 1, 1, 1, 1, 1, 0.79661, 0.235535, 0.00935126, 0, 0, 0.547049, 
            1, 1, 1, 1, 1, 0.884278, 0.105202, 0, 0.468147, 0.0789012, 0.351841, 0.980713, 
            1, 1, 1, 1, 1, 0.274109, 0.169492, 0.601987, 0.154296, 0.0818235, 0.8609, 1, 
            1, 1, 1, 1, 1, 0.526593, 0.822911, 0.187025, 0.231444, 0.868498, 1, 1, 
            1, 1, 1, 1, 1, 0.971946, 0.305085, 0.165985, 0.929866, 1, 1, 1, 
            1, 1, 1, 1, 0.922268, 0.365868, 0.316774, 0.873174, 1, 1, 1, 1, 
            1, 1, 1, 0.929866, 0.222092, 0.305085, 0.915839, 1, 1, 1, 1, 1, 
            1, 1, 0.9737, 0.336645, 0.151958, 0.910579, 1, 1, 1, 1, 1, 1, 
            1, 0.976622, 0.414962, 0.0888369, 0.808299, 1, 1, 1, 0.992987, 0.922852, 1, 1, 
            0.938632, 0.428989, 0, 0.0514319, 0.36353, 0.928112, 1, 0.915839, 0.360023, 0.293396, 1, 1, 
            0.168323, 0, 0, 0, 0, 0.126242, 0.898305, 0.392168, 0, 0.0338983, 1, 1, 
            0, 0.114553, 0.472823, 0.0227937, 0, 0, 0.129164, 0.0531853, 0.0087668, 0.382817, 1, 1, 
            0.306838, 0.893629, 1, 0.836353, 0.517241, 0.043834, 0, 0.0350672, 0.639977, 1, 1, 1},
            {1, 1, 1, 1, 1, 0.829615, 0.182556, 0, 0, 0, 0, 0, 
            1, 1, 1, 1, 0.837728, 0.0223124, 0, 0, 0, 0, 0.0791075, 0.56998, 
            1, 1, 1, 1, 0.803245, 0.243408, 0.432049, 0.030426, 0, 0.243408, 0.760649, 1, 
            1, 1, 1, 1, 0.993915, 0.823529, 0.146045, 0, 0.774848, 0.957404, 1, 1, 
            1, 1, 1, 1, 0.787018, 0.0892495, 0, 0, 0.137931, 0.198783, 0.959432, 1, 
            1, 1, 1, 0.926978, 0.0811359, 0, 0, 0, 0, 0, 0.809331, 1, 
            1, 1, 1, 0.391481, 0.0811359, 0.336714, 0.6714, 0.606491, 0, 0.158215, 0.926978, 1, 
            1, 1, 1, 0.829615, 0.829615, 1, 0.957404, 0.336714, 0.0141988, 0.630832, 1, 1, 
            1, 1, 1, 1, 1, 0.926978, 0.288032, 0.0486815, 0.496957, 1, 1, 1, 
            1, 1, 1, 0.918864, 0.675456, 0.200811, 0.20284, 0.762677, 1, 1, 1, 1, 
            1, 0.983773, 0.770791, 0.182556, 0.0730223, 0.442191, 0.878296, 1, 1, 1, 1, 1, 
            0.969574, 0.425963, 0.0182556, 0.103448, 0.821501, 1, 1, 1, 1, 1, 1, 1, 
            0.292089, 0, 0.176471, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
            0, 0.0121704, 0.56998, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
            0.15213, 0.687627, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 0.638889, 0, 0.75, 
            1, 1, 1, 1, 1, 1, 1, 1, 0.472222, 0.0555556, 0.0833333, 0.972222, 
            1, 1, 1, 1, 1, 1, 1, 0.694444, 0.0555556, 0, 0.5, 1, 
            1, 1, 1, 1, 1, 1, 0.611111, 0.0833333, 0, 0.194444, 0.916667, 1, 
            1, 1, 1, 1, 1, 0.583333, 0, 0, 0, 0.638889, 1, 1, 
            1, 1, 1, 1, 0.416667, 0, 0.333333, 0, 0.25, 1, 1, 1, 
            1, 1, 1, 0.388889, 0.0833333, 0.611111, 0.444444, 0, 0.555556, 1, 0.833333, 0.25, 
            1, 0.638889, 0.222222, 0, 0.388889, 0.944444, 0.194444, 0.0555556, 0.944444, 0.75, 0.111111, 0.0555556, 
            0.611111, 0, 0, 0, 0.0833333, 0.25, 0, 0.0833333, 0.333333, 0.166667, 0.0833333, 0.611111, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0.138889, 0.888889, 1, 
            1, 1, 1, 1, 0.888889, 0, 0.222222, 1, 1, 1, 1, 1, 
            1, 1, 1, 1, 0.444444, 0, 0.805556, 1, 1, 1, 1, 1, 
            1, 1, 1, 0.944444, 0.0555556, 0, 1, 1, 1, 1, 1, 1, 
            1, 1, 0.972222, 0.388889, 0, 0.388889, 1, 1, 1, 1, 1, 1, 
            1, 1, 0.75, 0, 0.277778, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0.987097, 0.483871, 0, 0.33871, 0.483871, 0.483871, 0.483871, 0.241935, 0.154839, 
            1, 1, 1, 0.6, 0, 0, 0, 0, 0, 0, 0.0322581, 0.490323, 
            1, 1, 1, 0.425806, 0, 0, 0.0677419, 0.483871, 0.580645, 0.580645, 0.790323, 1, 
            1, 1, 1, 0.116129, 0, 0.0387097, 0.883871, 1, 1, 1, 1, 1, 
            1, 1, 0.758065, 0, 0, 0.106452, 0.354839, 0.354839, 0.5, 1, 1, 1, 
            1, 1, 0.4, 0, 0, 0, 0, 0, 0, 1, 1, 1, 
            1, 1, 0.680645, 0.225806, 0.467742, 0.709677, 0, 0, 0.0677419, 1, 1, 1, 
            1, 1, 1, 1, 1, 0.622581, 0, 0.0516129, 0.625806, 1, 1, 1, 
            1, 1, 1, 1, 0.758065, 0.0225806, 0.0290323, 0.722581, 1, 1, 1, 1, 
            1, 1, 1, 0.580645, 0.0967742, 0.0967742, 0.680645, 1, 1, 1, 1, 1, 
            1, 0.929032, 0.354839, 0.0483871, 0.177419, 0.83871, 1, 1, 1, 1, 1, 1, 
            0.845161, 0.2, 0, 0.319355, 0.935484, 1, 1, 1, 1, 1, 1, 1, 
            0.0580645, 0, 0, 0.845161, 1, 1, 1, 1, 1, 1, 1, 1, 
            0, 0, 0.416129, 0.980645, 1, 1, 1, 1, 1, 1, 1, 1, 
            0.0483871, 0.725806, 0.987097, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 0.578947, 0.0526316, 0, 
            1, 1, 1, 1, 1, 1, 1, 1, 0.526316, 0, 0, 0.473684, 
            1, 1, 1, 1, 1, 1, 1, 0.894737, 0, 0, 0.289474, 0.973684, 
            1, 1, 1, 1, 1, 1, 0.815789, 0.131579, 0, 0.105263, 0.947368, 1, 
            1, 1, 1, 1, 1, 1, 0.157895, 0, 0.0789474, 0.921053, 1, 1, 
            1, 1, 1, 1, 1, 0.526316, 0, 0.0526316, 0.736842, 1, 1, 1, 
            1, 1, 1, 1, 0.868421, 0.184211, 0, 0.578947, 1, 1, 1, 1, 
            1, 1, 1, 1, 0.263158, 0, 0.526316, 1, 1, 1, 1, 1, 
            1, 1, 1, 0.473684, 0, 0.473684, 1, 1, 1, 1, 1, 1, 
            1, 1, 0.368421, 0, 0.421053, 0.526316, 0.315789, 0, 0, 0, 0.736842, 1, 
            1, 0.736842, 0, 0, 0, 0, 0.184211, 0.289474, 0, 0, 0.736842, 1, 
            0.947368, 0, 0, 0.263158, 0.789474, 1, 0.815789, 0.131579, 0, 0.526316, 1, 1, 
            0.157895, 0, 0.473684, 1, 0.868421, 0.5, 0, 0.0526316, 0.578947, 1, 1, 1, 
            0, 0, 0, 0, 0, 0, 0.684211, 1, 1, 1, 1, 1, 
            0.315789, 0, 0.0789474, 0.5, 0.631579, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0.662338, 0.0487013, 0, 0.535714, 0.535714, 0.535714, 0.438312, 0, 0, 
            1, 1, 0.386364, 0.0194805, 0, 0, 0, 0, 0, 0, 0, 0.214286, 
            1, 1, 0.357143, 0.321429, 0.321429, 0.321429, 0.321429, 0.0292208, 0, 0, 0.340909, 0.935065, 
            1, 1, 0.941558, 1, 1, 1, 0.954545, 0.0681818, 0, 0.347403, 0.980519, 1, 
            1, 1, 1, 1, 1, 0.951299, 0.37987, 0.0162338, 0.470779, 1, 1, 1, 
            1, 1, 1, 1, 0.99026, 0.503247, 0, 0.470779, 1, 1, 1, 1, 
            1, 1, 1, 1, 0.743506, 0, 0.279221, 0.961039, 1, 1, 1, 1, 
            1, 1, 1, 0.909091, 0.181818, 0.136364, 1, 1, 1, 1, 1, 1, 
            1, 1, 1, 0.321429, 0.038961, 0.876623, 1, 1, 1, 1, 1, 1, 
            1, 1, 0.561688, 0.0649351, 0.707792, 1, 1, 1, 1, 1, 1, 1, 
            1, 0.847403, 0.0324675, 0.483766, 1, 1, 1, 1, 1, 1, 1, 1, 
            1, 0.373377, 0, 0.522727, 1, 1, 1, 1, 1, 1, 1, 1, 
            0.837662, 0.0292208, 0, 0.678571, 1, 1, 1, 1, 1, 1, 1, 1, 
            0.36039, 0.00649351, 0.363636, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
            0, 0.383117, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 0.748428, 0.0628931, 0.545073, 0.461216, 0.0209644, 0.178197, 0.555556, 
            1, 1, 1, 1, 0.706499, 0.048218, 0, 0, 0, 0, 0, 0, 
            1, 1, 1, 0.916143, 0.159329, 0, 0, 0.385744, 0.777778, 0.0440252, 0.0293501, 0.473795, 
            1, 1, 1, 0.471698, 0, 0.0125786, 0.477987, 0.960168, 0.542977, 0.048218, 0.60587, 1, 
            1, 1, 1, 0.522013, 0, 0.113208, 1, 0.320755, 0, 0.641509, 1, 1, 
            1, 1, 1, 0.622642, 0, 0.0628931, 0.314465, 0.033543, 0.790356, 1, 1, 1, 
            1, 1, 1, 0.698113, 0, 0, 0.144654, 0.761006, 1, 1, 1, 1, 
            1, 1, 1, 0.798742, 0, 0, 0.559748, 1, 1, 1, 1, 1, 
            1, 1, 0.943396, 0.301887, 0, 0, 0.433962, 1, 1, 1, 1, 1, 
            1, 1, 0.238994, 0.0838574, 0.167715, 0, 0.433962, 1, 1, 1, 1, 1, 
            1, 0.383648, 0.0251572, 0.779874, 0.402516, 0, 0.534591, 1, 1, 1, 1, 1, 
            0.765199, 0.0146751, 0.610063, 0.949686, 0.226415, 0.113208, 0.899371, 1, 1, 1, 1, 1, 
            0.226415, 0, 0.591195, 0.188679, 0.104822, 0.737945, 1, 1, 1, 1, 1, 1, 
            0.0251572, 0, 0, 0.150943, 0.823899, 1, 1, 1, 1, 1, 1, 1, 
            0.477987, 0, 0.408805, 0.823899, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 0.982143, 0.602679, 0.0669643, 0, 0.401786, 0.9375, 0.9375, 
            1, 1, 1, 1, 0.946429, 0.357143, 0, 0, 0, 0, 0, 0.0357143, 
            1, 1, 1, 0.892857, 0.196429, 0.0535714, 0.241071, 0, 0, 0, 0, 0.526786, 
            1, 1, 0.825893, 0.120536, 0.0357143, 0.598214, 0.571429, 0, 0, 0, 0.379464, 0.959821, 
            1, 0.910714, 0.125, 0.0892857, 0.8125, 0.732143, 0.125, 0, 0, 0.401786, 0.9375, 1, 
            0.946429, 0.178571, 0, 0.446429, 0.290179, 0.0223214, 0, 0, 0.46875, 0.977679, 1, 1, 
            0.598214, 0, 0, 0, 0.25, 0, 0, 0.508929, 0.973214, 1, 1, 1, 
            0.71875, 0.165179, 0.700893, 0.96875, 0.553571, 0.00892857, 0.433036, 0.995536, 1, 1, 1, 1, 
            1, 1, 0.986607, 0.638393, 0.0133929, 0.620536, 1, 1, 1, 1, 1, 1, 
            1, 1, 0.589286, 0, 0.5, 1, 1, 1, 1, 1, 1, 1, 
            1, 0.741071, 0, 0.0625, 0.910714, 1, 1, 1, 1, 1, 1, 1, 
            1, 0.348214, 0.0401786, 0.620536, 1, 1, 1, 1, 1, 1, 1, 1, 
            0.785714, 0.0267857, 0.0267857, 0.1875, 0.535714, 1, 1, 1, 1, 1, 1, 1, 
            0.321429, 0, 0, 0.348214, 0.928571, 1, 1, 1, 1, 1, 1, 1, 
            0.0848214, 0.46875, 0.803571, 0.991071, 1, 1, 1, 1, 1, 1, 1, 1}};

        vector<vector<double> > frequence_in_segment;
        GetFrequenciesOfWhiteCells(ROWS_OF_SEGMENTS, COLUMNS_OF_SEGMENTS, frequence_in_segment);
        vector<double> distances(10, 0);
        vector<double> distances_italic(10, 0);
        for (int current_digit = 0; current_digit < 10; ++current_digit) {
            vector<vector<double> > reference_frequence_in_segment(frequence_in_segment.size());
            vector<vector<double> > reference_frequence_in_segment_italic(frequence_in_segment.size());
            for (int current_row_index = 0; current_row_index < ROWS_OF_SEGMENTS; ++current_row_index) {
                reference_frequence_in_segment[current_row_index] = vector<double>(&REFERENCE_VALUES_OF_FREQUENCIES[current_digit][current_row_index * COLUMNS_OF_SEGMENTS],
                    &REFERENCE_VALUES_OF_FREQUENCIES[current_digit][(current_row_index + 1) * COLUMNS_OF_SEGMENTS]);
                reference_frequence_in_segment_italic[current_row_index] = vector<double>(&REFERENCE_VALUES_OF_FREQUENCIES_ITALIC[current_digit][current_row_index * COLUMNS_OF_SEGMENTS],
                    &REFERENCE_VALUES_OF_FREQUENCIES_ITALIC[current_digit][(current_row_index + 1) * COLUMNS_OF_SEGMENTS]);
            }
            distances[current_digit] = Distance(frequence_in_segment, reference_frequence_in_segment);
            distances_italic[current_digit] = Distance(frequence_in_segment, reference_frequence_in_segment_italic);
        }
        int min_digit = min_element(distances.begin(), distances.end()) - distances.begin();
        int min_digit_italic = min_element(distances_italic.begin(), distances_italic.end()) - distances_italic.begin();
        if (distances[min_digit] < distances_italic[min_digit_italic]) {
            return min_digit;
        }
        else {
            return min_digit_italic;
        }
    }
};

class ASCIINumber: public ASCIIPicture {
private: 

    vector<ASCIIDigit> digits;
    int number_of_digits;

    void InitializeNumberOfDigits() {
        ASCIINumber copy_of_number(*this);
        for (int current_column_index = 0; current_column_index < GetWidth(); ++current_column_index) {
            if (!ColumnHasBlackCells(current_column_index)) {
                FillColumn(current_column_index, WHITE);
            }
        }
        vector<int> number_of_cells_in_component;
        int current_component_index = 1;
        number_of_cells_in_component.assign(1, 0);
        vector<vector<bool> > already_been;
        vector<vector<int> > components;
        already_been.assign(GetHeight(), vector<bool>(GetWidth(), false));
        components.assign(GetHeight(), vector<int>(GetWidth(), 0));
        for (int current_row_index = 0; current_row_index < GetHeight(); ++current_row_index) {
            for (int current_column_index = 0; current_column_index < GetWidth(); ++current_column_index) {
                if ((!already_been[current_row_index][current_column_index]) && (image[current_row_index][current_column_index] != WHITE)) {
                    number_of_cells_in_component.push_back(0);
                    queue<Cell> cell_queue;
                    already_been[current_row_index][current_column_index] = true;
                    components[current_row_index][current_column_index] = current_component_index;
                    ++number_of_cells_in_component[current_component_index];
                    cell_queue.push(Cell(current_row_index, current_column_index));
                    while (!cell_queue.empty()) {
                        Cell current_cell = cell_queue.front();
                        cell_queue.pop();
                        vector<Cell> neighbours;
                        GetNeighbours(current_cell, neighbours);
                        for (vector<Cell>::const_iterator current_neighbour = neighbours.begin(); current_neighbour != neighbours.end(); ++current_neighbour) {
                            if ((!already_been[current_neighbour->row][current_neighbour->column]) && (image[current_neighbour->row][current_neighbour->column] != WHITE)) {
                                already_been[current_neighbour->row][current_neighbour->column] = true;
                                components[current_neighbour->row][current_neighbour->column] = current_component_index;
                                ++number_of_cells_in_component[current_component_index];
                                cell_queue.push(*current_neighbour);
                            }
                        }
                    }
                    ++current_component_index;
                }
            }
        }
        int maximal_component_area = *max_element(number_of_cells_in_component.begin(), number_of_cells_in_component.end());
        int number_of_digits_ = 0;
        for (current_component_index = 1; current_component_index < static_cast<int>(number_of_cells_in_component.size()); ++current_component_index) {
            if (number_of_cells_in_component[current_component_index] >= maximal_component_area / 3) {
                ++number_of_digits_;
            }
        }
        *this = copy_of_number;
        number_of_digits = number_of_digits_;
        digits.resize(number_of_digits);
    }

public: 

    ASCIINumber() {
        number_of_digits = 0;
    }

    void AutoCrop() {
        while (!IsEmpty() && (RowIsWhite(0))) {
            DeleteRow(0);
        }
        if (IsEmpty()) {
            return;
        }
        while (RowIsWhite(GetHeight() - 1)) {
            DeleteRow(GetHeight() - 1);
        }
        while (ColumnIsWhite(0)) {
            DeleteColumn(0);
        }
        while (ColumnIsWhite(GetWidth() - 1)) {
            DeleteColumn(GetWidth() - 1);
        }
    }

    void InitializeDigits() {
        AutoCrop();
        InitializeNumberOfDigits();
        for (int current_digit_index = 0; current_digit_index < number_of_digits; ++current_digit_index) {
            int left_column_index = max(0, (current_digit_index * GetWidth()) / number_of_digits - GetWidth() / (3 * number_of_digits));
            int right_column_index = min(GetWidth(), ((current_digit_index + 1) * GetWidth()) / number_of_digits + GetWidth() / (3 * number_of_digits));
            digits[current_digit_index] = ASCIIDigit(image, left_column_index, right_column_index);
            digits[current_digit_index].Normalize();
        }
    }

    int Recognize() {
        int value = 0;
        for (int current_digit_index = 0; current_digit_index < number_of_digits; ++current_digit_index) {
            value = 10 * value + digits[current_digit_index].Recognize();
        }
        return value;
    }

    ASCIIDigit& GetDigit(const int number_of_digit) {
        return digits[number_of_digit];
    }
};

istream& operator>>(istream& is, ASCIIPicture& picture) {
    picture.Read(is);
    return is;
}

ostream& operator<<(ostream& os, ASCIIPicture& picture) {
    picture.Print(os);
    return os;
}

}

using ASCIIGraphics::ASCIINumber;
using ASCIIGraphics::operator<<;
using ASCIIGraphics::operator>>;

int main() {
    ASCIINumber number;
    cin >> number;
    number.InitializeDigits();
    cout << number.Recognize();
    return 0;
}
