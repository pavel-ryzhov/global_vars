#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <functional>

using std::vector;
using std::string;
using std::sort;
using std::min;
using std::max;
using std::max_element;
using std::copy;
using std::remove_if;
using std::bind2nd;
using std::less;
using std::mem_fun_ref;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;

// Simple algorithm. Hypotheses:
// 1. We have 3 digits
// 
// Plan:
// 1. Split picture into 3 parts
// 2. Get digit rectangle and size in pixels
// 3. Try to draw good digit and calculate conditional probability

int GetIntFromChar(char symbol) {
  switch (symbol) {
    case '.':
      return 0;
    case '%':
      return 1;
    case '#':
      return 2;
    case '@':
      return 3;
  }
}

char GetCharFromInt(int symbol) {
  switch (symbol) {
    case 0:
      return '.';
    case 1:
      return '%';
    case 2:
      return '#';
    case 3:
      return '@';
  }
}

int NearNumber(double number) {
  return static_cast<int>(floor(number + 0.5));
}

const int kMaxRectangleSize = 10;

class Image {
 private:
  struct Borders {
    int string_up_;
    int string_down_;
    int column_left_;
    int column_right_;

    Borders(int string_up, int column_left, int string_down, int column_right)
        : string_up_(string_up)
        , column_left_(column_left)
        , string_down_(string_down)
        , column_right_(column_right)
        {
    }

    Borders(const Borders &rhs)
        : string_up_(rhs.string_up_)
        , column_left_(rhs.column_left_)
        , string_down_(rhs.string_down_)
        , column_right_(rhs.column_right_)
        {
    }

  };

  struct FigureWithWeightAndBorder {
    Borders borders_;
    int weight_;

    FigureWithWeightAndBorder(int weight = 0, Borders borders = Borders(0, 0, 0, 0))
        : weight_(weight)
        , borders_(borders)
        {
    }

    FigureWithWeightAndBorder(const FigureWithWeightAndBorder &rhs)
        : weight_(rhs.weight_)
        , borders_(rhs.borders_)
        {
    }

    bool operator<(const FigureWithWeightAndBorder &rhs) const {
      return weight_ < rhs.weight_;
    }

    bool OrderByLeftBorder(const FigureWithWeightAndBorder &rhs) const {
      return borders_.column_left_ < rhs.borders_.column_left_;
    }
  };

 private:
  int width_;
  int height_;
  vector<vector<int> > pixels_;
  vector<Borders> digits_;
  bool dont_try_use_connectivity_;

  const int kMaxRectangleSize_;

  void _Show(const Borders &borders) const {
    for (int string_id = borders.string_up_; string_id < borders.string_down_; ++string_id) {
      for (int column_id = borders.column_left_; column_id < borders.column_right_; ++column_id) {
        cerr << GetCharFromInt(pixels_[string_id][column_id]);
      }
      cerr << endl;
    }
  }

  void _FixBorders(Borders &borders) {
    int left_border = borders.column_right_;
    int right_border = borders.column_left_;
    for (int string_id = borders.string_up_; string_id < borders.string_down_; ++string_id) {
      for (int column_id = borders.column_left_; column_id < borders.column_right_; ++column_id) {
        if (column_id < left_border && pixels_[string_id][column_id] != 0) {
          left_border = column_id;
        }
        if (column_id + 1 > right_border && pixels_[string_id][column_id] != 0) {
          right_border = column_id + 1;
        }
      }
    }
    borders.column_left_ = left_border;
    borders.column_right_ = right_border;

    bool is_empty_string = true;
    while (is_empty_string) {
      for (int column_id = borders.column_left_; column_id < borders.column_right_; ++column_id) {
        if (pixels_[borders.string_up_][column_id] != 0) {
          is_empty_string = false;
          break;
        }
      }
      if (is_empty_string) {
        borders.string_up_++;
      }
    }

    is_empty_string = true;
    while (is_empty_string) {
      for (int column_id = borders.column_left_; column_id < borders.column_right_; ++column_id) {
        if (pixels_[borders.string_down_ - 1][column_id] != 0) {
          is_empty_string = false;
          break;
        }
      }
      if (is_empty_string) {
        borders.string_down_--;
      }
    }
  }

  // @return bool - found pixel to mark
  bool FindNotMarkedPixel(const Borders &borders, int &string_id, int &column_id) {
    for (string_id = borders.string_up_; string_id < borders.string_down_; ++string_id) {
      for (column_id = borders.column_left_; column_id < borders.column_right_; ++column_id) {
        if (pixels_[string_id][column_id] > 0 && pixels_[string_id][column_id] < 4) {
          return true;
        }
      }
    }
    return false;
  }

  bool IsNotMarked(int string_id, int column_id) {
    if (pixels_[string_id][column_id] > 0 
        && pixels_[string_id][column_id] < 4) {
      return true;
    }
    return false;
  }

  void MarkFigure(const Borders &borders
      , int additional
      , int string_id
      , int column_id
      , int &figure_weight
      , Borders &found_borders
      ) {
    figure_weight += pixels_[string_id][column_id];
    pixels_[string_id][column_id] += additional;

    found_borders.column_left_ = min(column_id, found_borders.column_left_);
    found_borders.column_right_ = max(column_id, found_borders.column_right_);
    found_borders.string_up_ = min(string_id, found_borders.string_up_);
    found_borders.string_down_ = max(string_id, found_borders.string_down_);
    // go left
    if (column_id > borders.column_left_ && IsNotMarked(string_id, column_id - 1)) {
      MarkFigure(borders, additional, string_id, column_id - 1, figure_weight, found_borders);
    }
    // go right
    if (column_id + 1 < borders.column_right_ && IsNotMarked(string_id, column_id + 1)) {
      MarkFigure(borders, additional, string_id, column_id + 1, figure_weight, found_borders);
    }
    // go up
    if (string_id > borders.string_up_ && IsNotMarked(string_id - 1, column_id)) {
      MarkFigure(borders, additional, string_id - 1, column_id, figure_weight, found_borders);
    }
    // go down
    if (string_id + 1 < borders.string_down_ && IsNotMarked(string_id + 1, column_id)) {
      MarkFigure(borders, additional, string_id + 1, column_id, figure_weight, found_borders);
    }
    // go left-up
    if (column_id > borders.column_left_ 
        && string_id > borders.string_up_
        && IsNotMarked(string_id - 1, column_id - 1)) {
      MarkFigure(borders, additional, string_id - 1, column_id - 1, figure_weight, found_borders);
    }
    // go left-down
    if (column_id > borders.column_left_ 
        && string_id + 1 < borders.string_down_
        && IsNotMarked(string_id + 1, column_id - 1)) {
      MarkFigure(borders, additional, string_id + 1, column_id - 1, figure_weight, found_borders);
    }
    // go right-up
    if (column_id + 1 < borders.column_right_
        && string_id > borders.string_up_
        && IsNotMarked(string_id - 1, column_id + 1)) {
      MarkFigure(borders, additional, string_id - 1, column_id + 1, figure_weight, found_borders);
    }
    // go right-down
    if (column_id + 1 < borders.column_right_
        && string_id + 1 < borders.string_down_
        && IsNotMarked(string_id + 1, column_id + 1)) {
      MarkFigure(borders, additional, string_id + 1, column_id + 1, figure_weight, found_borders);
    }
  }

  void CleanByAdditional(const Borders &borders, int good_additional, bool safe_clean = true) {
    for (int string_id = borders.string_up_; string_id < borders.string_down_; ++string_id) {
      for (int column_id = borders.column_left_; column_id < borders.column_right_; ++column_id) {
        if (pixels_[string_id][column_id] > good_additional 
            && pixels_[string_id][column_id] < good_additional + 4
            ) {
          pixels_[string_id][column_id] %= 4;
        } else {
          if (safe_clean) {
            pixels_[string_id][column_id] %= 4;
          } else {
            pixels_[string_id][column_id] = 0;
          }
        }
      }
    }
  }

  bool IsBordered(const Borders &borders, int additional, int string_id, int column_id) {
    if (string_id < borders.string_up_ 
        || string_id == borders.string_down_
        || column_id < borders.column_left_
        || column_id == borders.column_right_
        ) {
      return false;
    }
    if (pixels_[string_id][column_id] == 0) {
      pixels_[string_id][column_id] = additional;
      return IsBordered(borders, additional, string_id - 1, column_id - 1)
          && IsBordered(borders, additional, string_id - 1, column_id)
          && IsBordered(borders, additional, string_id - 1, column_id + 1)
          && IsBordered(borders, additional, string_id, column_id - 1)
          && IsBordered(borders, additional, string_id, column_id + 1)
          && IsBordered(borders, additional, string_id + 1, column_id - 1)
          && IsBordered(borders, additional, string_id + 1, column_id)
          && IsBordered(borders, additional, string_id + 1, column_id + 1);
    }
    return true;
  }

  bool CheckInternalPixel(const Borders &borders
      , int additional
      , int string_id
      , int column_id
      ) {
    bool is_internal = false;
    // check up
    int string_up_index = string_id;
    for (
        ; string_up_index >= borders.string_up_
        ; --string_up_index
        ) {
      if (pixels_[string_up_index][column_id] > additional 
            && pixels_[string_up_index][column_id] < additional + 4
            ) {
          is_internal = true;
          break;
      }
    }
    if (!is_internal) {
      return false;
    }
    return IsBordered(borders, additional, string_up_index + 1, column_id);
  }
  
  // @return figures with weights and width
  vector<FigureWithWeightAndBorder> _MarkFigures(const Borders &borders, int &good_additional) {
    vector<FigureWithWeightAndBorder> figure_weights;

    bool exists_not_marked = true;
    for (int additional = 4; exists_not_marked == true; additional += 4) {
      int string_id = 0;
      int column_id = 0;
      int figure_weight = 0;

      exists_not_marked = FindNotMarkedPixel(borders, string_id, column_id);
      if (exists_not_marked) {
        bool is_internal_figure = false;
        int index_outer_figure = 0;
        for (
            ; index_outer_figure < figure_weights.size() && !is_internal_figure
            ; ++index_outer_figure
            ) {
          is_internal_figure = CheckInternalPixel(borders
              , (index_outer_figure + 1) * 4
              , string_id
              , column_id
              );
        }
        if (is_internal_figure) {
          figure_weight = figure_weights[index_outer_figure - 1].weight_;
        }
        Borders found_borders = Borders(string_id, column_id, string_id, column_id);
        MarkFigure(borders, additional, string_id, column_id, figure_weight, found_borders);
        figure_weights.push_back(FigureWithWeightAndBorder(figure_weight, found_borders));
      }
    }

    int max_weight_index = 0;
    for (int index = 1; index < figure_weights.size(); ++index) {
      if (figure_weights[index].weight_ > figure_weights[max_weight_index].weight_) {
        max_weight_index = index;
      }
    }

    good_additional = (max_weight_index + 1) * 4;
    return figure_weights;
  }

  void _CleanFigures(const Borders &borders) {
    int good_additional = 0;
    _MarkFigures(borders, good_additional);
    CleanByAdditional(borders, good_additional, false);
  }

  int GetMiddleValue(const Borders &borders) const {
    int count_elements = 0;
    int result_sum = 0;
    for (int string_id = borders.string_up_; string_id < borders.string_down_; ++string_id) {
      for (int column_id = borders.column_left_; column_id < borders.column_right_; ++column_id) {
        count_elements++;
        result_sum += pixels_[string_id][column_id];
      }
    }
    return count_elements > 0 ? result_sum / count_elements : 0;
  }

  void _CreateMiddleFigures(Borders &borders) {
    int kResultSize = min(min(kMaxRectangleSize_, borders.column_right_ - borders.column_left_)
        , borders.string_down_ - borders.string_up_
        );
    vector<vector<int> > result_image;
    result_image.resize(kResultSize);

    int string_shift = (borders.string_down_ - borders.string_up_ + kResultSize - 1) / kResultSize;
    double string_precision_shift = (static_cast<double>(borders.string_down_) - borders.string_up_) / kResultSize;
    int column_shift = (borders.column_right_ - borders.column_left_ + kResultSize - 1) / kResultSize;
    double column_precision_shift = (static_cast<double>(borders.column_right_) - borders.column_left_) / kResultSize;
    for (int line_index = 0
        ; line_index < kResultSize
        ; ++line_index
        ) {

      for (int column_index = 0
          ; column_index < kResultSize
          ; ++column_index
          ) {
        int current_string_up = NearNumber(string_precision_shift * line_index + borders.string_up_);
        int current_column_left = NearNumber(column_precision_shift * column_index + borders.column_left_);
        result_image[line_index].push_back(GetMiddleValue(
          Borders(current_string_up
          , current_column_left
          , min(current_string_up + string_shift, borders.string_down_)
          , min(current_column_left + column_shift, borders.column_right_)
          )));
      }
    }

    for (int line_index = 0; line_index < kResultSize; ++line_index) {
      copy(result_image[line_index].begin()
          , result_image[line_index].end()
          , pixels_[borders.string_up_ + line_index].begin() + borders.column_left_
          );
    }
    borders.string_down_ = borders.string_up_ + kResultSize;
    borders.column_right_ = borders.column_left_ + kResultSize;
  }

  // symbol characteristics

  bool IsFour(const Borders &borders) const {
    int left_zero_column = borders.string_down_;
    for (int string_id = borders.string_up_; string_id < borders.string_down_; ++string_id) {
      if (pixels_[string_id][borders.column_left_] != 0) {
        left_zero_column = string_id;
        break;
      }
    }
    if (left_zero_column == borders.string_down_) {
      return false;
    }
    // walk up
    int prev_left_zero = borders.column_left_;
    int current_left_zero;
    for (int string_id = left_zero_column - 1; string_id >= borders.string_up_; --string_id) {
      int current_left_zero = FindFirstNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (current_left_zero - prev_left_zero > 2 || current_left_zero < prev_left_zero) {
        // too fast or bad glyph
        return false;
      }
      prev_left_zero = current_left_zero;
    }
    if (prev_left_zero - borders.column_left_ < 3) {
      return false;
    }

    // walk down
    prev_left_zero = borders.column_left_;
    bool is_big_leap_found = false;
    int string_jump = left_zero_column;
    for (int string_id = left_zero_column + 1; string_id < borders.string_down_; ++string_id) {
      int current_left_zero = FindFirstNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (is_big_leap_found) {
        // check small modifications to down
        if (string_id == string_jump + 1 && current_left_zero > prev_left_zero) {
          prev_left_zero = current_left_zero;
        }
        if (current_left_zero > prev_left_zero) {
          return false;
        }
      } else if (current_left_zero - prev_left_zero > 2) {
        is_big_leap_found = true;
        string_jump = string_id;
        prev_left_zero = current_left_zero;
      } else {
        prev_left_zero = current_left_zero;
      }
    }
    return is_big_leap_found;
  }

  bool IsSeven(const Borders &borders) const {
    // check slow right up
    int down_non_zero_column = FindLastNotZero(borders.string_down_ - 1
        , borders.column_left_
        , borders.column_right_
        );
    
    int string_id = borders.string_down_ - 1;
    int prev_non_zero_column = down_non_zero_column;
    for (; string_id >= borders.string_up_; --string_id) {
      int current_non_zero_column = FindLastNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (current_non_zero_column >= borders.column_left_
          && current_non_zero_column < prev_non_zero_column
          ) {
        return false;
      }
      // check empty string
      if (current_non_zero_column >= borders.column_left_) {
        prev_non_zero_column = current_non_zero_column;
      }
    }
    int middle_not_zero = FindLastNotZero((borders.string_down_ + borders.string_up_) / 2
          , borders.column_left_
          , borders.column_right_
          );
    if (prev_non_zero_column == borders.column_right_ - 1 
        && prev_non_zero_column != down_non_zero_column
        && (middle_not_zero == borders.column_left_ - 1 
          || borders.column_right_ - 1 != middle_not_zero)
        ) {
      return true;
    }
    return false;
  }

  int FindFirstNotZero(int string_id, int column_left_id, int column_right_id) const {
    int column_id = column_left_id;
    for (; column_id < column_right_id; ++column_id) {
      if (pixels_[string_id][column_id] != 0) {
        break;
      }
    }
    return column_id;
  }

  // @return in case of emtpy string: (column_left_id - 1)
  int FindLastNotZero(int string_id, int column_left_id, int column_right_id) const {
    int column_id = column_right_id - 1;
    for (; column_id >= column_left_id; --column_id) {
      if (pixels_[string_id][column_id] != 0) {
        break;
      }
    }
    return column_id;
  }

  int GetCountMiddleElements(int string_id, int column_left_id, int column_right_id) const {
    int left_not_zero = FindFirstNotZero(string_id, column_left_id, column_right_id);
    if (left_not_zero == column_right_id) {
      return 0;
    }
    int right_not_zero = FindLastNotZero(string_id, column_left_id, column_right_id);
    for (int column_id = left_not_zero; column_id <= right_not_zero; ++column_id) {
      if (pixels_[string_id][column_id] == 0) {
        // bad sequence
        return 0;
      }
    }
    return right_not_zero - left_not_zero + 1;
  }

  bool HasVerticals(const Borders &borders) const {
    bool found = false;
    int column_id = borders.column_left_;
    for (; !found && column_id < borders.column_right_; ++column_id) {
      found = true;
      for (int string_id = borders.string_up_; string_id < borders.string_down_; ++string_id) {
        if (pixels_[string_id][column_id] == 0) {
          found = false;
          break;
        }
      }
    }
    return found;
  }

  bool IsOne(const Borders &borders) const {
    int middle_line = (borders.string_up_ + borders.string_down_) / 2;
    int up_line = max(borders.string_up_, middle_line - 1);
    int down_line = min(borders.string_down_, middle_line + 3);

    int count_not_zero = GetCountMiddleElements(up_line
        , borders.column_left_
        , borders.column_right_
        );

    if (count_not_zero == 0) {
      return false;
    }

    int previous_non_zero = FindFirstNotZero(up_line
        , borders.column_left_
        , borders.column_right_
        );
    for (int line_id = up_line + 1; line_id < down_line; ++line_id) {
      if (count_not_zero != GetCountMiddleElements(line_id
          , borders.column_left_
          , borders.column_right_
          )) {
        return false;
      }
      int current_non_zero = FindFirstNotZero(line_id
        , borders.column_left_
        , borders.column_right_
        );
      if (current_non_zero > previous_non_zero) {
        return false;
      }
      previous_non_zero = current_non_zero;
    }

    if (count_not_zero >= 2) {
      Borders small_rectangle(borders);
      small_rectangle.string_down_--;
      small_rectangle.string_up_++;
      return HasVerticals(small_rectangle);
    }
    return true;
  }

  bool SmoothRightBorder(const Borders &borders) const {
    int column_up_right_not_zero = FindLastNotZero(borders.string_up_
        , borders.column_left_
        , borders.column_right_
        );
    int previous_not_zero = column_up_right_not_zero;
    int string_id = borders.string_up_ + 1;
    for (; string_id < borders.string_down_; ++string_id) {
      int current_not_zero = FindLastNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (current_not_zero >= previous_not_zero) {
        if (current_not_zero - previous_not_zero > 2) {
          // very fast
          return false;
        }
        previous_not_zero = current_not_zero;
      } else {
        previous_not_zero = current_not_zero;
        string_id++;
        break;
      }
    }

    for (;string_id < borders.string_down_; ++string_id) {
      int current_not_zero = FindLastNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (current_not_zero <= previous_not_zero) {
        if (previous_not_zero - current_not_zero > 2) {
          // very fast
          // check last jump
          if (string_id == borders.string_down_ - 1 && previous_not_zero - current_not_zero == 3) {
            return true;
          }
          return false;
        }
        previous_not_zero = current_not_zero;
      } else {
        // not simple border
        return false;
      }
    }
    return true;
  }

  bool PeekLeftCenter(const Borders &borders) const {
    int string_middle = (borders.string_up_ + borders.string_down_) / 2;
    int middle_zero = FindFirstNotZero(string_middle
        , borders.column_left_
        , borders.column_right_
        );
    middle_zero = min(min(middle_zero, 
        FindFirstNotZero(string_middle - 1
          , borders.column_left_
          , borders.column_right_
          )
        ), FindFirstNotZero(string_middle + 1
          , borders.column_left_
          , borders.column_right_
        ));
    int middle_less_zero = FindFirstNotZero(string_middle - 2
        , borders.column_left_
        , borders.column_right_
        );
    int middle_greater_zero = FindFirstNotZero(string_middle + 2
        , borders.column_left_
        , borders.column_right_
        );
    return middle_less_zero - middle_zero >= 3
        && middle_greater_zero - middle_zero >= 3;
  }

  bool IsVerySmoothLeft(const Borders &borders) const {
    int string_middle = (borders.string_up_ + borders.string_down_) / 2;
    int left_non_zero = FindFirstNotZero(string_middle
        , borders.column_left_
        , borders.column_right_
        );
    if (left_non_zero != FindFirstNotZero(string_middle - 1
        , borders.column_left_
        , borders.column_right_
        )) {
      return false;
    }
    if (left_non_zero != FindFirstNotZero(string_middle + 1
        , borders.column_left_
        , borders.column_right_
        )) {
      return false;
    }
    // check up
    int previous_non_zero = left_non_zero;
    for (int string_id = string_middle - 2; string_id >= borders.string_up_; --string_id) {
      int current_non_zero = FindFirstNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (current_non_zero < previous_non_zero || current_non_zero - previous_non_zero >= 2) {
        return false;
      }
      previous_non_zero = current_non_zero;
    }
    // chekc down
    previous_non_zero = left_non_zero;
    for (int string_id = string_middle + 2; string_id < borders.string_down_; ++string_id) {
      int current_non_zero = FindFirstNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (current_non_zero < previous_non_zero || current_non_zero - previous_non_zero >= 2) {
        return false;
      }
      previous_non_zero = current_non_zero;
    }
    return true;
  }

  bool EmptyLeftDownCorner(const Borders &borders) const {
    const int kCornerSize = 3;
    int string_count = 0;
    int column_count = 0;
    for (int string_id = borders.string_down_ - 1
        ; string_count < kCornerSize
        ; ++string_count, --string_id
        ) {

      for (int column_id = borders.column_left_
          ; column_count < kCornerSize
          ; ++column_count, ++column_id
          ) {

        if (pixels_[string_id][column_id] != 0) {
          return false;
        }
      }
    }
    return true;
  }

  int FindUpNotZero(int column_id, int string_up_id, int string_down_id) const {
    int string_id = string_up_id;
    for (; string_id < string_down_id; ++string_id) {
      if (pixels_[string_id][column_id] != 0) {
        break;
      }
    }
    return string_id;
  }

  bool SmoothUp(const Borders &borders) const {
    int previous_not_zero = FindUpNotZero(borders.column_left_
        , borders.string_up_
        , borders.string_down_
        );
    int column_id = borders.column_left_ + 1;
    for (; column_id < borders.column_right_; ++column_id) {
      int current_not_zero = FindUpNotZero(column_id
          , borders.string_up_
          , borders.string_down_
          );
      if (abs(current_not_zero - previous_not_zero) > 3) {
        return false;
      }
      previous_not_zero = current_not_zero;
    }
    return true;
  }

  bool SmoothLeftBorder(const Borders &borders) const {
    int column_up_right_not_zero = FindFirstNotZero(borders.string_up_
        , borders.column_left_
        , borders.column_right_
        );
    int previous_not_zero = column_up_right_not_zero;
    int string_id = borders.string_up_ + 1;
    for (; string_id < borders.string_down_; ++string_id) {
      int current_not_zero = FindFirstNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (abs(previous_not_zero - current_not_zero) > 3) {
        // too fast
        return false;
      }
      if (previous_not_zero >= current_not_zero) {
        if (previous_not_zero - current_not_zero > 2) {
          // very fast
          return false;
        }
        previous_not_zero = current_not_zero;
      } else {
        previous_not_zero = current_not_zero;
        string_id++;
        break;
      }
    }

    for (;string_id < borders.string_down_; ++string_id) {
      int current_not_zero = FindFirstNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (abs(previous_not_zero - current_not_zero) > 3) {
        // too fast
        return false;
      }
      if (current_not_zero >= previous_not_zero) {
        if (current_not_zero - previous_not_zero > 2) {
          // very fast
          return false;
        }
        previous_not_zero = current_not_zero;
      } else {
        // not simple border
        return false;
      }
    }
    return true;
  }

  bool IsSix(const Borders &borders) const {
    const int kBigJump = 3;
    int right_up_first = FindLastNotZero(borders.string_up_
        , borders.column_left_
        , borders.column_right_
        );
    int right_up_second = FindLastNotZero(borders.string_up_ + 1
        , borders.column_left_
        , borders.column_right_
        );
    int right_up_third = FindLastNotZero(borders.string_up_ + 2
        , borders.column_left_
        , borders.column_right_
        );
    return (right_up_second < right_up_first) 
      || (right_up_second == right_up_first && right_up_first - right_up_third > kBigJump)
      || RightUpJump(borders);
  }

  bool RightZigZag(const Borders &borders) const {
    const int zig_zag_fast = 2;
    int right_up_first = FindLastNotZero(borders.string_up_
        , borders.column_left_
        , borders.column_right_
        );
    int string_id = borders.string_up_ + 1;
    int previous_not_zero = right_up_first;
    bool bad_right_shift = false;
    for (; string_id < borders.string_down_; ++string_id) {
      int current_not_zero = FindLastNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (right_up_first == borders.column_right_ - 1) {
        bad_right_shift = true;
        break;
      }
      if (current_not_zero >= previous_not_zero) {
        if (current_not_zero - previous_not_zero > zig_zag_fast) {
          // too fast
          return false;
        }
        previous_not_zero = current_not_zero;
      } else {
        if (previous_not_zero - current_not_zero > zig_zag_fast) {
          // too fast
          return false;
        }
        previous_not_zero = current_not_zero;
        string_id++;
        break;
      }
    }
    if (string_id == borders.string_down_) {
      return false;
    }
    for (; string_id < borders.string_down_; ++string_id) {
      int current_not_zero = FindLastNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (current_not_zero <= previous_not_zero) {
        if (previous_not_zero - current_not_zero > zig_zag_fast) {
          // too fast
          return false;
        }
        previous_not_zero = current_not_zero;
      } else {
        if (current_not_zero - previous_not_zero > zig_zag_fast) {
          // too fast
          return false;
        }
        previous_not_zero = current_not_zero;
        string_id++;
        break;
      }
    }
    if (string_id == borders.string_down_) {
      return false;
    }
    for (; string_id < borders.string_down_; ++string_id) {
      int current_not_zero = FindLastNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (current_not_zero >= previous_not_zero) {
        if (current_not_zero - previous_not_zero > zig_zag_fast) {
          // too fast
          return false;
        }
        previous_not_zero = current_not_zero;
      } else {
        if (previous_not_zero - current_not_zero > zig_zag_fast) {
          // too fast
          return false;
        }
        previous_not_zero = current_not_zero;        
        break;
      }
    }
    if (string_id == borders.string_down_) {
      if (bad_right_shift && previous_not_zero == borders.column_right_ - 1) {
        return true;
      }
      return false;
    }
    string_id++;
    for (; string_id < borders.string_down_; ++string_id) {
      int current_not_zero = FindLastNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (current_not_zero <= previous_not_zero) {
        if (previous_not_zero - current_not_zero > zig_zag_fast) {
          // too fast
          return false;
        }
        previous_not_zero = current_not_zero;
      } else {
        if (current_not_zero - previous_not_zero > zig_zag_fast) {
          // too fast
          return false;
        }
        previous_not_zero = current_not_zero;
        string_id++;
        break;
      }
    }
    return string_id == borders.string_down_;
  }

  bool LeftDownJump(const Borders &borders) const {
    int previous_not_zero = FindFirstNotZero(borders.string_down_ - 1
          , borders.column_left_
          , borders.column_right_
          );
    for (int string_id = borders.string_down_ - 2; string_id >= borders.string_up_; --string_id) {
      int current_not_zero = FindFirstNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (current_not_zero - previous_not_zero > 3) {
        return true;
      }
      previous_not_zero = current_not_zero;
    }
    return false;
  }

  bool RightUpJump(const Borders &borders) const {
    int previous_not_zero = FindLastNotZero(borders.string_up_
          , borders.column_left_
          , borders.column_right_
          );
    for (int string_id = borders.string_up_ + 1; string_id < borders.string_down_; ++string_id) {
      int current_not_zero = FindLastNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if (previous_not_zero - current_not_zero > 3) {
        return true;
      }
      previous_not_zero = current_not_zero;
    }
    return false;
  }

  bool HeavyBottom(const Borders &borders) const {
    int count_elements = 0;
    int count_not_zero = 0;
    for (int floor_id = 1; floor_id <= 2; ++floor_id) {
      for (int column_id = borders.column_left_; column_id < borders.column_right_; ++column_id) {
        count_elements++;
        if (pixels_[borders.string_down_ - floor_id][column_id] != 0) {
          count_not_zero++;
        }
      }
    }
    return count_not_zero >= count_elements / 2;
  }

  bool IsDoubleJump(const Borders &borders) const {
    int previous_not_zero = FindFirstNotZero(borders.string_up_
          , borders.column_left_
          , borders.column_right_
          );
    bool first_jump = false;
    bool border_found = false;
    int last_difference = 0;
    for (int string_id = borders.string_up_ + 1; string_id < borders.string_down_; ++string_id) {
      int current_not_zero = FindFirstNotZero(string_id
          , borders.column_left_
          , borders.column_right_
          );
      if ((current_not_zero - previous_not_zero) * (first_jump ? -1 : 1) * (border_found ? -1 : 1) > 3
          || (first_jump && current_not_zero + last_difference - previous_not_zero > 3)
          ) {
        // now check next jump
        if (!first_jump) {
          first_jump = true;
        } else if (!border_found) {
          border_found = true;
        } else {
          return true;
        }
      }
      last_difference = current_not_zero - previous_not_zero;
      previous_not_zero = current_not_zero;
    }
    return false;
  }

  int GuessNumber(const Borders &borders) const {
    if (IsFour(borders)) {
      return 4;
    }
    if (IsSeven(borders)) {
      return 7;
    }
    if (IsOne(borders)) {
      return 1;
    }
    bool is_right_smooth = SmoothRightBorder(borders);
    bool is_left_smooth = SmoothLeftBorder(borders);
    bool is_double_jump = IsDoubleJump(borders);
    if (is_right_smooth && !is_double_jump) {
      if (is_left_smooth) {
        return 0;
      }
      if (!SmoothUp(borders) && EmptyLeftDownCorner(borders)) {
        return 4;
      }
      return 9;
    }
    if (is_left_smooth && IsSix(borders)) {
      return 6;
    }
    bool is_left_jump = LeftDownJump(borders);
    if (is_left_jump && is_double_jump) {
      return 3;
    }
    if (RightZigZag(borders)) {
      if (is_left_jump) {
        return 3;
      }
      if (IsVerySmoothLeft(borders)) {
        return 6;
      }
      if (PeekLeftCenter(borders)) {
        return 3;
      }
      return 8;
    }
    if (is_left_jump || !HeavyBottom(borders)) {
      return 5;
    }
    return 2;
  }

 public:
  Image() 
      : width_(0)
      , height_(0)
      , kMaxRectangleSize_(kMaxRectangleSize)
      {
  }

  ~Image() {
  }

  void ReadImage(const vector<vector<int> > &data) {
    pixels_ = data;
    width_ = pixels_[0].size();
    height_ = pixels_.size();
  }

  void Show() const {
    _Show(Borders(0, 0, height_, width_));
  }

  void SplitImage(int count = 3) {
    int good_additional = 0;
    Borders all_area(0, 0, height_, width_);
    vector<FigureWithWeightAndBorder> figures_with_weight = _MarkFigures(all_area, good_additional);
    for (int figure_id = 0; figure_id < figures_with_weight.size(); ++figure_id) {
      figures_with_weight[figure_id].borders_.column_right_++;
      figures_with_weight[figure_id].borders_.string_down_++;
    }
    sort(figures_with_weight.begin()
      , figures_with_weight.end()
      , mem_fun_ref(&FigureWithWeightAndBorder::OrderByLeftBorder)
      );
    CleanByAdditional(all_area, good_additional, true);
    bool good_figures = true;
    if (count == figures_with_weight.size()) {
      for (int figure_id = 0; figure_id < figures_with_weight.size(); ++figure_id) {
        int difference = figures_with_weight[figure_id].borders_.column_right_
          - figures_with_weight[figure_id].borders_.column_left_
          - kMaxRectangleSize;
        if (difference < 0 
            && figure_id > 0 
            && figures_with_weight[figure_id - 1].borders_.column_right_
              < figures_with_weight[figure_id].borders_.column_left_
            ) {

          difference += figures_with_weight[figure_id].borders_.column_left_ 
            - figures_with_weight[figure_id - 1].borders_.column_right_;
          figures_with_weight[figure_id].borders_.column_left_ = 
            figures_with_weight[figure_id - 1].borders_.column_right_;
        }
        if (difference < 0
            && figure_id < figures_with_weight.size() - 1
            && figures_with_weight[figure_id + 1].borders_.column_left_
              > figures_with_weight[figure_id].borders_.column_right_
            ) {

          difference += figures_with_weight[figure_id].borders_.column_left_ 
            - figures_with_weight[figure_id - 1].borders_.column_right_;
          figures_with_weight[figure_id].borders_.column_left_ = 
            figures_with_weight[figure_id - 1].borders_.column_right_;
        }
        if (difference < 0 
            || (figure_id > 0 && figures_with_weight[figure_id].borders_.column_left_ 
              < figures_with_weight[figure_id - 1].borders_.column_right_)
            ) {
          good_figures = false;
          break;
        }
      }
    }

    if (!good_figures || dont_try_use_connectivity_) {
      for (int figure_id = 0; figure_id < count; ++figure_id) {
        int left_border = figure_id * width_ / count;
        int right_border = (figure_id + 1) * width_ / count;
        digits_.push_back(Borders(0, left_border, height_, right_border));
      }
    } else {
      digits_.reserve(figures_with_weight.size());
      for (int figure_id = 0; figure_id < figures_with_weight.size(); ++figure_id) {
        digits_.push_back(figures_with_weight[figure_id].borders_);
      }
    }
  }

  void FixBorders() {
    for (int figure_id = 0; figure_id < digits_.size(); ++figure_id) {
      _FixBorders(digits_[figure_id]);
    }
  }

  void CleanFigures() {
    for (int figure_id = 0; figure_id < digits_.size(); ++figure_id) {
      _CleanFigures(digits_[figure_id]);
    }
    FixBorders();
  }

  void CreatMiddleFigures() {
    for (int figure_id = 0; figure_id < digits_.size(); ++figure_id) {
      _CreateMiddleFigures(digits_[figure_id]);
    }
    FixBorders();
  }

  void ShowFigures() const {
    for (int figure_id = 0; figure_id < digits_.size(); ++figure_id) {
      _Show(digits_[figure_id]);
      cerr << endl;
    }
  }

  int GetNumbers() const {
    int result_number = 0;
    for (int figure_id = 0; figure_id < digits_.size(); ++figure_id) {
      _Show(digits_[figure_id]);
      cerr << endl;
      int additional = GuessNumber(digits_[figure_id]);
      if (additional == 0 && figure_id == 0 && digits_.size() > 1) {
        // first digit cannot be '0'
        additional = 8;
      }
      result_number = additional + 10 * result_number;
    }
    return result_number;
  }

  int GuessHowManyFigures() {
    cerr << endl;
    dont_try_use_connectivity_ = false;

    int good_additional = 0;
    Borders all_area(0, 0, height_, width_);
    vector<FigureWithWeightAndBorder> figures_with_weight = _MarkFigures(all_area, good_additional);
    
    int max_weight = (*max_element(figures_with_weight.begin(), figures_with_weight.end())).weight_;

    vector<FigureWithWeightAndBorder>::iterator it = remove_if(figures_with_weight.begin()
        , figures_with_weight.end()
        , bind2nd(less<FigureWithWeightAndBorder>(), FigureWithWeightAndBorder(max_weight / 4))
        );
    if (it != figures_with_weight.end()) {
      dont_try_use_connectivity_ = true;
    }
    figures_with_weight.resize(it - figures_with_weight.begin());
    for (vector<FigureWithWeightAndBorder>::iterator it = figures_with_weight.begin()
        ; it != figures_with_weight.end()
        ; ++it
        ) {
      cerr << (*it).weight_ << endl;
    }
    cerr << "Left elements: " << figures_with_weight.size() << endl;

    int count_figures = figures_with_weight.size();
    sort(figures_with_weight.begin(), figures_with_weight.end());
    if (figures_with_weight.size() == 2) {
      int min_width = min(
        figures_with_weight[0].borders_.column_right_ - figures_with_weight[0].borders_.column_left_
        , figures_with_weight[1].borders_.column_right_ - figures_with_weight[1].borders_.column_left_
        );
      int max_width = max(
        figures_with_weight[0].borders_.column_right_ - figures_with_weight[0].borders_.column_left_
        , figures_with_weight[1].borders_.column_right_ - figures_with_weight[1].borders_.column_left_
        );
      if (figures_with_weight[1].weight_ < 2 * figures_with_weight[0].weight_
          && max_width - min_width < 5
          ) {
        count_figures = 2;
      } else if (figures_with_weight[0].weight_ < 0.75 * figures_with_weight[1].weight_) {
        count_figures = 3;
        dont_try_use_connectivity_ = true;
      }
    } else if (figures_with_weight.size() > 3) {
      // suggestion: we have border for each digit
      count_figures /= 2;
      dont_try_use_connectivity_ = true;
    } else if (figures_with_weight.size() == 1) {
      if (width_ >= height_ * 2) {
        count_figures = 3;
        dont_try_use_connectivity_ = true;
      } else if( width_ > height_ * 1.3) {
        count_figures = 2;
        dont_try_use_connectivity_ = true;
      }
    }

    CleanByAdditional(all_area, good_additional, true);
    return count_figures;
  }
};


// const int kCountEmptyLines = 5;
// we have 5 empty lines before digits and after
// so, we can determine the borders

void Input(vector<vector<int> > *bordered_picture) {
  string empty_line;
  cin >> empty_line;
  
  string line = empty_line;
  while (line == empty_line) {
    cin >> line;
  }

  int left_border = empty_line.size();
  int right_border = 0;

  vector<int> numeric_line;
  numeric_line.resize(empty_line.size());
  vector<vector<int> > pixels;
  for (; line != empty_line; cin >> line) {
    bool is_first_not_empty_found = false;
    for (int index = 0; index < line.size(); ++index) {
      if (!is_first_not_empty_found) {
        if (line[index] != '.') {
          is_first_not_empty_found = true;
          left_border = min(left_border, index);
        }
      }
      if (index > right_border) {
        if (line[index] != '.') {
          right_border = index;
        }
      }
      numeric_line[index] = GetIntFromChar(line[index]);
    }
    pixels.push_back(numeric_line);
  }

  bordered_picture->resize(pixels.size());
  for (int index = 0; index < pixels.size(); ++index) {
    (*bordered_picture)[index].resize(right_border - left_border + 1);
    copy(pixels[index].begin() + left_border, pixels[index].begin() + right_border + 1
      , (*bordered_picture)[index].begin());
  }
}

int main() {
  // freopen("1.txt", "r", stdin);

  Image image;
  vector<vector<int> > pixels;

  Input(&pixels);
  image.ReadImage(pixels);

  int count_figures = image.GuessHowManyFigures();
  cerr << "Count figures: " << count_figures << endl;
  image.SplitImage(count_figures);
  // image.ShowFigures();
  image.FixBorders();

  // test
  // image.ShowFigures();

  image.CleanFigures();
  image.CreatMiddleFigures();
  cout << image.GetNumbers() << endl;
  return 0;
}