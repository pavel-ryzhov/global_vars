#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>


using std::vector;
using std::queue;
using std::pair;
using std::make_pair;
using std::min;
using std::max;
using std::set;
using std::sort;

#define BLACK_SHAPE 0
#define WHITE_SHAPE 1

struct ShapeInfo {
  int id;
  int sample_i;
  int sample_j;
  int left;
  int right;
  int top;
  int bottom;
  int width;
  int height;
  int pixels[ 4 ];
  int boldness;
};

vector< vector< unsigned char > > image;
vector< ShapeInfo > shapes;
int image_height;
int image_width;

char toIntegerColor( int chr ) {
  switch( chr ) {
    case '%': 
      return 1;
    case '#':
      return 2;
    case '@':
      return 3;
      default:
        return 0;
  }
}

double fuzzyCompareVectors( const vector< int > &first, const vector< int > &second ) {
  double result = 0;
  if( first.size() == second.size() ) {
    if( first.size() <= 1 ) {
      return 0;
    }
    for( int i = 1; i < first.size(); ++i ) {
      result += first[ i ] * second[ i ];
    }
    return 0.5 * ( 1.0 - result / ( first.size() - 1.0 ) );
  }
  const int num_interpolation_steps = 30;
  for( int i = 0; i < num_interpolation_steps; ++i ) {
    double first_index = 1.0 * i * first.size() / num_interpolation_steps;
    double first_intermediate_value;
    if( floor( first_index ) == first.size() - 1 ) {
      first_intermediate_value = first[ floor( first_index ) ];
    } else {
      first_intermediate_value = first[ floor( first_index ) ] * ( 1 + floor( first_index ) - first_index ) + first[ floor( first_index ) + 1 ] * ( first_index - floor( first_index ) );
    }
    double second_intermediate_value;
    double second_index = 1.0 * i * second.size() / num_interpolation_steps;
    if( floor( second_index ) == second.size() - 1 ) {
      second_intermediate_value = second[ floor( second_index ) ];
    } else {
      second_intermediate_value = second[ floor( second_index ) ] * ( 1 + floor( second_index ) - second_index ) + second[ floor( second_index ) + 1 ] * ( second_index - floor( second_index ) );
    }
    result += first_intermediate_value * second_intermediate_value;
  }
  return 0.5 * ( 1.0 - result / num_interpolation_steps );
}

double fuzzyCompareVectors( const vector< int > &first, const char second[] ) {
  vector< int > temp_second( strlen( second ) );
  for( int i = 0; i < temp_second.size(); ++i ) {
    if( second[ i ] == '+' ) {
      temp_second[ i ] = 1;
    } else if( second[ i ] == '-' ) {
      temp_second[ i ] = -1;
    } else {
      temp_second[ i ] = 0;
    }
  }
  return fuzzyCompareVectors( first, temp_second );
}

double matchZero( 
  const vector< int > &widths, const vector< int > &lefts, const vector< int > &rights, const vector< int > &spines, 
  int upper_hole, int middle_hole, int lower_hole, int where_max_width, 
  int right_shift_upper, int right_shift_bigger, int has_big_left_shift, int has_big_right_shift ) {
  return fuzzyCompareVectors( spines, "0" ) 
    + min( fuzzyCompareVectors( widths, "0+-" ), fuzzyCompareVectors( widths, "0" ) ),
    + ( 1 - middle_hole ) + upper_hole + 1.5 * lower_hole + ( where_max_width ? 1 : 0 ) + has_big_left_shift;
}
double matchOne( 
  const vector< int > &widths, const vector< int > &lefts, const vector< int > &rights, const vector< int > &spines, 
  int upper_hole, int middle_hole, int lower_hole, int where_max_width, 
  int right_shift_upper, int right_shift_bigger, int has_big_left_shift, int has_big_right_shift ) {
  return min( fuzzyCompareVectors( spines, "0-" ), min( fuzzyCompareVectors( spines, "0-+" ), fuzzyCompareVectors( spines, "0" ) ) )
    + fuzzyCompareVectors( widths, "0+-+" )
    + fuzzyCompareVectors( lefts, "0-+-" )
    + min( fuzzyCompareVectors( rights, "0" ), fuzzyCompareVectors( rights, "0-" ) )
    + ( middle_hole + upper_hole + lower_hole ) * 2.0;
}
double matchTwo( 
  const vector< int > &widths, const vector< int > &lefts, const vector< int > &rights, const vector< int > &spines, 
  int upper_hole, int middle_hole, int lower_hole, int where_max_width, 
  int right_shift_upper, int right_shift_bigger, int has_big_left_shift, int has_big_right_shift ) {
  return fuzzyCompareVectors( widths, "0+-+" ) 
    + fuzzyCompareVectors( lefts, "0-+-" )
    + min( fuzzyCompareVectors( rights, "0-+-" ), fuzzyCompareVectors( rights, "0-+-+" ) )
    + middle_hole + upper_hole + lower_hole + ( where_max_width == 1 ? 1 : 0 ) 
    + right_shift_upper
    + 1 - has_big_left_shift;
}
double matchThree( 
  const vector< int > &widths, const vector< int > &lefts, const vector< int > &rights, const vector< int > &spines, 
  int upper_hole, int middle_hole, int lower_hole, int where_max_width, 
  int right_shift_upper, int right_shift_bigger, int has_big_left_shift, int has_big_right_shift ) {
  return fuzzyCompareVectors( spines, "0+-+-" )
    + fuzzyCompareVectors( widths, "0+-+-+-" ) 
    + min( fuzzyCompareVectors( lefts, "0-+-+-+" ), fuzzyCompareVectors( lefts, "0-+-" ) )
    + min( fuzzyCompareVectors( rights, "0-+-+" ), fuzzyCompareVectors( rights, "0-+-" ) )
    + middle_hole + lower_hole + has_big_right_shift * 1.5;
}
double matchFour( 
  const vector< int > &widths, const vector< int > &lefts, const vector< int > &rights, const vector< int > &spines, 
  int upper_hole, int middle_hole, int lower_hole, int where_max_width, 
  int right_shift_upper, int right_shift_bigger, int has_big_left_shift, int has_big_right_shift ) {
  return min( fuzzyCompareVectors( spines, "0+" ), fuzzyCompareVectors( spines, "0" ) )
    + min( fuzzyCompareVectors( widths, "0+-+" ), fuzzyCompareVectors( widths, "0+-" ) ) 
    + min( fuzzyCompareVectors( lefts, "0+" ), fuzzyCompareVectors( lefts, "0-+" ) )
    + min( fuzzyCompareVectors( rights, "0" ), min( fuzzyCompareVectors( rights, "0+-" ), fuzzyCompareVectors( rights, "0-+-" ) ) )
    + lower_hole + ( where_max_width == 1 ? 1 : 0 ) + right_shift_bigger + 1 - has_big_left_shift;
}
double matchFive( 
  const vector< int > &widths, const vector< int > &lefts, const vector< int > &rights, const vector< int > &spines, 
  int upper_hole, int middle_hole, int lower_hole, int where_max_width, 
  int right_shift_upper, int right_shift_bigger, int has_big_left_shift, int has_big_right_shift ) {
  return min( fuzzyCompareVectors( spines, "0-+-" ), fuzzyCompareVectors( spines, "0-+" ) )
    + fuzzyCompareVectors( widths, "0-+-+-" ) 
    + fuzzyCompareVectors( rights, "0+-+" ) * 2.0
    + middle_hole + lower_hole * 2.0 + ( where_max_width == -1 ? 1 : 0 );
}
double matchSix( 
  const vector< int > &widths, const vector< int > &lefts, const vector< int > &rights, const vector< int > &spines, 
  int upper_hole, int middle_hole, int lower_hole, int where_max_width, 
  int right_shift_upper, int right_shift_bigger, int has_big_left_shift, int has_big_right_shift ) {
  return min( fuzzyCompareVectors( spines, "0-+" ), fuzzyCompareVectors( spines, "0+" ) )
    + fuzzyCompareVectors( widths, "0+-+-" )
    + min( fuzzyCompareVectors( lefts, "0-+" ), fuzzyCompareVectors( lefts, "0+" ) ) * 2.0
    + 1 - lower_hole + middle_hole + upper_hole + has_big_left_shift;
}
double matchSeven( 
  const vector< int > &widths, const vector< int > &lefts, const vector< int > &rights, const vector< int > &spines, 
  int upper_hole, int middle_hole, int lower_hole, int where_max_width, 
  int right_shift_upper, int right_shift_bigger, int has_big_left_shift, int has_big_right_shift ) {
  return min( fuzzyCompareVectors( spines, "0+" ), fuzzyCompareVectors( spines, "0+-" ) ) * 2.0
    + min( fuzzyCompareVectors( lefts, "0+" ), min( fuzzyCompareVectors( lefts, "0+-" ), fuzzyCompareVectors( lefts, "0+-+" ) ) ) * 2.0
    + middle_hole + lower_hole + upper_hole + ( where_max_width == -1 ? 1 : 0 ) + 1 - has_big_left_shift + has_big_right_shift;
}
double matchEight( 
  const vector< int > &widths, const vector< int > &lefts, const vector< int > &rights, const vector< int > &spines, 
  int upper_hole, int middle_hole, int lower_hole, int where_max_width, 
  int right_shift_upper, int right_shift_bigger, int has_big_left_shift, int has_big_right_shift ) {
  return fuzzyCompareVectors( spines, "0" ) * 0.5
    + fuzzyCompareVectors( widths, "0+-+-" )
    + min( fuzzyCompareVectors( lefts, "0-+-" ), min( fuzzyCompareVectors( lefts, "0-+" ), fuzzyCompareVectors( lefts, "0-+-+" ) ) )
    + max( 2 - upper_hole - lower_hole - middle_hole, 0 ) + has_big_right_shift;
}
double matchNine( 
  const vector< int > &widths, const vector< int > &lefts, const vector< int > &rights, const vector< int > &spines, 
  int upper_hole, int middle_hole, int lower_hole, int where_max_width, 
  int right_shift_upper, int right_shift_bigger, int has_big_left_shift, int has_big_right_shift ) {
  return fuzzyCompareVectors( spines, "0+-" )
    + min( fuzzyCompareVectors( widths, "0+-+-" ), fuzzyCompareVectors( widths, "0+-" ) )
    + fuzzyCompareVectors( lefts, "0-+-+-+" )
    + min( fuzzyCompareVectors( rights, "0-+" ), fuzzyCompareVectors( rights, "0" ) )
    + 1 - upper_hole + middle_hole + lower_hole;
}

int matchDigit( 
  const vector< int > &widths, const vector< int > &lefts, const vector< int > &rights, 
  const vector< int > &spines, int upper_hole, int middle_hole, int lower_hole, 
  int where_max_width, int right_shift_upper, int right_shift_bigger,
  int has_big_left_shift, int has_big_right_shift ) {
  double ( *matchers[] )( const vector< int > &, const vector< int > &, const vector< int > &, const vector< int > &, int, int, int, int, int, int, int, int  ) = { 
    matchZero, matchOne, matchTwo, matchThree, matchFour, matchFive, matchSix, matchSeven, matchEight, matchNine
  };
  int best_match = 0;
  double lowest_distance = 1000;
  for( int i = 0; i <= 9; ++i ) {
    double distance = matchers[ i ]( widths, lefts, rights, spines, upper_hole, 
      middle_hole, lower_hole, where_max_width, right_shift_upper, right_shift_bigger, 
      has_big_left_shift, has_big_right_shift );
    if( distance < lowest_distance ) {
      lowest_distance = distance;
      best_match = i;
    }
  }
  return best_match;
}

void getImage( void ) {
  const int max_line_length = 1000;
  char buffer[ max_line_length + 1 ];
  fgets( buffer, max_line_length, stdin );
  
  if( buffer[ 0 ] == '\0' ) {
    return;
  }

  int i = strlen( buffer );

  while( i > 0 && buffer[ i ] != '.' ) {
    buffer[ i ] = '\0';
    --i;
  }

  image_width = i;
  
  while( !feof( stdin ) ) {
    fgets( buffer, max_line_length, stdin );
    if( buffer[ 0 ] != '\n' && buffer[ 0 ] != '\0' ) {
      vector< unsigned char > image_line;
      image.push_back( image_line );
      int last_line_number = image.size() - 1;
      image[ last_line_number ].resize( image_width );
      for( int i = 0; i < image_width; ++i ) {
        image[ last_line_number ][ i ] = toIntegerColor( buffer[ i ] );
      }
    }
  }
  
  image_height = image.size();
}

void putImage( void ) {
  for( size_t i = 0; i < image.size(); ++i ) {
    for( size_t j = 0; j < image[ i ].size(); ++j ) {
      printf( "%d", min( static_cast< int >( image[ i ][ j ] >> 2 ), 9 ) );
    }
    printf( "\n" );
  }
}

inline bool containsShape( const ShapeInfo &first, const ShapeInfo &second ) {
  return first.left < second.left && first.right > second.right && first.top < second.top && first.bottom > second.bottom;
}

bool shapeSortPredicate( const int &first, const int &second ) {
  return shapes[ first ].left < shapes[ second ].left;
}

inline bool isWithinCanvas( int i, int j ) {
  return i >= 0 && j >= 0 && i < image_height && j < image_width;
}

void selectShape( int i, int j, ShapeInfo *shape, int shape_id, int shape_type = BLACK_SHAPE ) {
  shape->id = shape_id;
  shape->top = shape->bottom = shape->sample_i = i;
  shape->left = shape->right = shape->sample_j = j;

  for( int k = 0; k < 4; ++k ) {
    shape->pixels[ k ] = 0;
  }
  int num_queued_black_pixels = 1;
  queue< pair< int, int > > shape_pixels;
  shape_pixels.push( make_pair( i, j ) );

  while( !shape_pixels.empty() ) {
    i = shape_pixels.front().first;
    j = shape_pixels.front().second;
    shape_pixels.pop();
    if( ( image[ i ][ j ] & 3 ) == 3 ) {
      --num_queued_black_pixels;
    }
    if( image[ i ][ j ] > 3 ) {
      continue;
    }
    if( image[ i ][ j ] == 1 && ( j < shape->left || j > shape->right ) ) {
      if( num_queued_black_pixels > 0 ) {
        shape_pixels.push( make_pair( i, j ) );
      }
      continue;
    }
    ++shape->pixels[ image[ i ][ j ] ];
    shape->top = min( shape->top, i );
    shape->bottom = max( shape->bottom, i );
    shape->left = min( shape->left, j );
    shape->right = max( shape->right, j );
    image[ i ][ j ] |= shape_id << 2;
    for( int offset_i = -1; offset_i <= 1; ++offset_i ) {
      for( int offset_j = -1; offset_j <= 1; ++offset_j ) {
        if( shape_type == WHITE_SHAPE && abs( offset_i ) + abs( offset_j ) > 1 ) {
          continue;
        }
        int neighbour_i = i + offset_i;
        int neighbour_j = j + offset_j;
        if( !isWithinCanvas( neighbour_i, neighbour_j ) ) {
          continue;
        }
        if( ( shape_type == BLACK_SHAPE && image[ neighbour_i ][ neighbour_j ] <= 3 && image[ neighbour_i ][ neighbour_j ] > 0 ) ) {
            shape_pixels.push( make_pair( neighbour_i, neighbour_j ) );
            if( image[ neighbour_i ][ neighbour_j ] == 3 ) {
              ++num_queued_black_pixels;
            }
        } else if( shape_type == WHITE_SHAPE && image[ neighbour_i ][ neighbour_j ] == 0 ) {
          int num_neighbouring_white_pixels = 0;
          for( int neighbour_offset_i = -1; neighbour_offset_i <= 1; ++neighbour_offset_i ) {
            for( int neighbour_offset_j = -1; neighbour_offset_j <= 1; ++neighbour_offset_j ) {
              int neighbour_neighbour_i = neighbour_i + neighbour_offset_i;
              int neighbour_neighbour_j = neighbour_j + neighbour_offset_j;
              if( isWithinCanvas( neighbour_neighbour_i, neighbour_neighbour_j ) && ( image[ neighbour_neighbour_i ][ neighbour_neighbour_j ] == 0 || ( image[ neighbour_neighbour_i ][ neighbour_neighbour_j ] >> 2 ) == shape_id ) ) {
                ++num_neighbouring_white_pixels;
              }
            }
          }
          if( num_neighbouring_white_pixels >= 3 ) {
            shape_pixels.push( make_pair( neighbour_i, neighbour_j ) );
          }
        }
      } ///for offset j
    } ///for offset i
  }
  shape->width = shape->right - shape->left + 1;
  shape->height = shape->bottom - shape->top + 1;
  shape->boldness = shape->pixels[ 0 ] + shape->pixels[ 1 ] + shape->pixels[ 2 ] + shape->pixels[ 3 ];
}

template< class _T > void calculateExtrema( const vector< vector< _T > > &original, vector< vector< _T > > &extrema ) {
  for( int k = 0; k < shapes.size(); ++k ) {
    extrema[ k ].push_back( original[ k ][ 0 ] );
    for( int i = 1; i < original[ k ].size(); ++i ) {
      if( i == original[ k ].size() - 1 ) {
        if( original[ k ][ i ] != extrema[ k ][ extrema[ k ].size() - 1 ] ) {
          extrema[ k ].push_back( original[ k ][ i ] );
        }
      } else if( original[ k ][ i - 1 ] <= original[ k ][ i ] && original[ k ][ i + 1 ] <= original[ k ][ i ] 
                || original[ k ][ i - 1 ] >= original[ k ][ i ] && original[ k ][ i + 1 ] >= original[ k ][ i ] ) {
        if( original[ k ][ i ] != extrema[ k ][ extrema[ k ].size() - 1 ] ) {
          extrema[ k ].push_back( original[ k ][ i ] );
        }
      }
    }
  }
}

template< class _T > void calculateNormalizedValues( 
  const vector< vector< _T > > &extrema, 
  vector< vector< int > > &normalized, 
  double multiplicative_threshold , 
  double additive_threshold ) {
  for( int k = 0; k < shapes.size(); ++k ) {
    normalized[ k ].push_back( 0 );
    for( int i = 1; i < extrema[ k ].size(); ++i ) {
      if( extrema[ k ][ i ] >= multiplicative_threshold * extrema[ k ][ i - 1 ] + additive_threshold ) {
        if( normalized[ k ][ normalized[ k ].size() - 1 ] != 1 ) {
          normalized[ k ].push_back( 1 );
        }
      } else if( extrema[ k ][ i - 1 ] >= multiplicative_threshold * extrema[ k ][ i ] + additive_threshold ) {
        if( normalized[ k ][ normalized[ k ].size() - 1 ] != -1 ) {
          normalized[ k ].push_back( -1 );
        }
      }
    }
  }
}

void selectShapes( void ) {
  int shape_id = 0;
  for( int i = 0; i < image_height; ++i ) {
    for( int j = 0; j < image_width; ++j ) {
      if( image[ i ][ j ] == 3 ) {
        ShapeInfo shape;
        selectShape( i, j, &shape, ++shape_id, BLACK_SHAPE );
        shapes.push_back( shape );
      }
    }
  }
}

void recognizeDigits( void ) {
  vector< vector< double > > shape_spines( shapes.size() );
  vector< vector< int > > shape_widths( shapes.size() );
  vector< vector< int > > shape_real_widths( shapes.size() );
  vector< vector< int > > shape_lefts( shapes.size() );
  vector< vector< int > > shape_rights( shapes.size() );
  vector< int > num_pixels( shapes.size() );
  vector< int > lefts( shapes.size() );
  vector< int > rights( shapes.size() );

  for( int i = 0; i < image_height; ++i ) {
    for( int k = 0; k < shapes.size(); ++k ) {
      num_pixels[ k ] = 0;
      lefts[ k ] = image_width;
      rights[ k ] = image_width;
    }
    for( int j = 0; j < image_width; ++j ) {
      if( image[ i ][ j ] == 0 && isWithinCanvas( i - 1, j ) && isWithinCanvas( i + 1, j ) 
          && image[ i - 1 ][ j ] & 3 == 3 && image[ i - 1 ][ j ] == image[ i + 1 ][ j ] ) {
        image[ i ][ j ] = image[ i - 1 ][ j ] ^ 3;
      }
      if( ( image[ i ][ j ] >> 2 ) > 0 ) {
        int shape_id = ( image[ i ][ j ] >> 2 ) - 1;
        ++num_pixels[ shape_id ];
        lefts[ shape_id ] = min( lefts[ shape_id ], j - shapes[ shape_id ].left );
        rights[ shape_id ] = min( rights[ shape_id ], shapes[ shape_id ].right - j );
      }
    }
    for( int k = 0; k < shapes.size(); ++k ) {
      if( num_pixels[ k ] ) {
        shape_real_widths[ k ].push_back( num_pixels[ k ] );
        shape_spines[ k ].push_back( shapes[ k ].right - rights[ k ] + lefts[ k ] );
        shape_widths[ k ].push_back( shapes[ k ].width - rights[ k ] - lefts[ k ] );
        shape_lefts[ k ].push_back( lefts[ k ] );
        shape_rights[ k ].push_back( rights[ k ] );
      }
    }
  }

  vector< vector< double > > spine_extrema( shapes.size() );
  vector< vector< int > > phantom_width_extrema( shapes.size() );
  vector< vector< int > > left_extrema( shapes.size() );
  vector< vector< int > > right_extrema( shapes.size() );

  calculateExtrema( shape_spines, spine_extrema );
  calculateExtrema( shape_widths, phantom_width_extrema );
  calculateExtrema( shape_lefts, left_extrema );
  calculateExtrema( shape_rights, right_extrema );

  vector< vector< int > > normalized_shape_spines( shapes.size() );
  vector< vector< int > > normalized_shape_widths( shapes.size() );
  vector< vector< int > > normalized_shape_lefts( shapes.size() );
  vector< vector< int > > normalized_shape_rights( shapes.size() );

  double average_boldness = 0;
  double average_height = 0;
  double average_width = 0;

  calculateNormalizedValues( spine_extrema, normalized_shape_spines, 1.2, 1 );
  calculateNormalizedValues( phantom_width_extrema, normalized_shape_widths, 1.2, 1 );
  calculateNormalizedValues( left_extrema, normalized_shape_lefts, 1.2, 1 );
  calculateNormalizedValues( right_extrema, normalized_shape_rights, 1.2, 1 );

  for( int k = 0; k < shapes.size(); ++k ) {
    average_boldness += shapes[ k ].boldness;
    average_height += shapes[ k ].height;
    average_width += shapes[ k ].width;
  }

  average_boldness /= shapes.size();
  average_height /= shapes.size();
  average_width /= shapes.size();

  set< int > stop_shapes;
  for( int k = 0; k < shapes.size(); ++k ) {
    if( shapes[ k ].boldness < average_boldness * 0.5 ) {
      stop_shapes.insert( k );
    }
  }
  for( int k = 0; k < shapes.size(); ++k ) {
    for( int m = 0; m < shapes.size(); ++m ) {
      if( m == k || stop_shapes.find( m ) != stop_shapes.end() ) {
        continue;
      }
      if( containsShape( shapes[ k ], shapes[ m ] ) ) {
        stop_shapes.insert( k );
      }
    }
  }

  vector< int > shape_ids( shapes.size() );
  for( int k = 0; k < shapes.size(); ++k ) {
    shape_ids[ k ] = k;
  }

  sort( shape_ids.begin(), shape_ids.end(), shapeSortPredicate );

  vector< ShapeInfo > white_shapes;
  int shape_id = shapes.size();
  for( int i = 0; i < image_height; ++i ) {
    for( int j = 0; j < image_width; ++j ) {
      if( image[ i ][ j ] == 0 ) {
        ShapeInfo shape;
        selectShape( i, j, &shape, ++shape_id, WHITE_SHAPE );
        white_shapes.push_back( shape );
      }
    }
  }
  vector< int > num_upper_white_shapes( shapes.size(), 0 );
  vector< int > num_lower_white_shapes( shapes.size(), 0 );
  vector< int > num_middle_white_shapes( shapes.size(), 0 );
  for( int k = 0; k < shapes.size(); ++k ) {
    for( int m = 0; m < white_shapes.size(); ++m ) {
      if( containsShape( shapes[ k ], white_shapes[ m ] ) && white_shapes[ m ].boldness >= 0.01 * shapes[ k ].boldness ) {
        if( ( white_shapes[ m ].top + white_shapes[ m ].bottom ) * 0.5 <= shapes[ k ].top * 0.65 + shapes[ k ].bottom * 0.35 ) {
          num_upper_white_shapes[ k ] = 1;
        } else if( ( white_shapes[ m ].top + white_shapes[ m ].bottom ) * 0.5 >= shapes[ k ].bottom * 0.65 + shapes[ k ].top * 0.35 ) {
          num_lower_white_shapes[ k ] = 1;
        } else {
          num_middle_white_shapes[ k ] = 1;
        }
      }
    }
  }
  
  vector< int > where_max_width( shapes.size() );
  vector< int > right_shift_bigger( shapes.size() );
  vector< int > right_shift_upper( shapes.size() );
  vector< int > has_big_right_shift( shapes.size() );
  vector< int > has_big_left_shift( shapes.size() );

  for( int k = 0; k < shapes.size(); ++k ) {
    int upper_max_width = 0;
    int lower_max_width = 0;
    for( int j = 0; j < shape_real_widths[ k ].size() * 0.4; ++j ) {
      upper_max_width = max( upper_max_width, shape_real_widths[ k ][ j ] );
    }
    for( int j = shape_real_widths[ k ].size() * 0.4; j < shape_real_widths[ k ].size(); ++j ) {
      lower_max_width = max( lower_max_width, shape_real_widths[ k ][ j ] );
    }
    if( upper_max_width >= lower_max_width * 1.1 + 1 ) {
      where_max_width[ k ] = 1;
    } else if( lower_max_width >= upper_max_width * 1.1 + 1 ) {
      where_max_width[ k ] = -1;
    } else {
      where_max_width[ k ] = 0;
    }
    int max_left_shift = 0;
    int max_left_shift_position = 0;
    int max_right_shift = 0;
    int max_right_shift_position = 0;
    for( int j = 1; j < shape_lefts[ k ].size(); ++j ) {
      if( shape_lefts[ k ][ j ] - shape_lefts[ k ][ j - 1 ] > max_left_shift ) {
        max_left_shift = abs( shape_lefts[ k ][ j ] - shape_lefts[ k ][ j - 1 ] );
        max_left_shift_position = j;
      }
      if( shape_rights[ k ][ j ] - shape_rights[ k ][ j - 1 ] > max_right_shift ) {
        max_right_shift = shape_rights[ k ][ j ] - shape_rights[ k ][ j - 1 ];
        max_right_shift_position = j;
      }
    }
    right_shift_upper[ k ] = ( max_left_shift_position > max_right_shift_position ? 1 : 0 );
    right_shift_bigger[ k ] = ( max_left_shift < max_right_shift ? 1 : 0 );
    has_big_left_shift[ k ] = ( max_left_shift >= 0.1 * shapes[ k ].width + 2 ? 1 : 0 );
    has_big_right_shift[ k ] = ( max_right_shift >= 0.1 * shapes[ k ].width + 2 ? 1 : 0 );
  }



  for( int k = 0, a = 0; k < shape_ids.size() && a < 3; ++k ) {
    if( stop_shapes.find( shape_ids[ k ] ) != stop_shapes.end() ) {
      continue;
    }
    ++a;
    int shape_id = shape_ids[ k ];
    printf( "%d", matchDigit( normalized_shape_widths[ shape_id ], normalized_shape_lefts[ shape_id ], normalized_shape_rights[ shape_id ], 
            normalized_shape_spines[ shape_id ], 
            num_upper_white_shapes[ shape_id ], num_middle_white_shapes[ shape_id ], num_lower_white_shapes[ shape_id ], 
            where_max_width[ shape_id ], right_shift_upper[ shape_id ], right_shift_bigger[ shape_id ],
            has_big_left_shift[ shape_id ], has_big_right_shift[ shape_id ] ) );
    /*printf( "Shape %d (recognized as %d)\n", shape_id + 1, 
      matchDigit( normalized_shape_widths[ shape_id ], normalized_shape_lefts[ shape_id ], normalized_shape_rights[ shape_id ], 
                  normalized_shape_spines[ shape_id ], 
                  num_upper_white_shapes[ shape_id ], num_middle_white_shapes[ shape_id ], num_lower_white_shapes[ shape_id ], 
                  where_max_width[ shape_id ], right_shift_upper[ shape_id ], right_shift_bigger[ shape_id ],
                  has_big_left_shift[ shape_id ], has_big_right_shift[ shape_id ] ) );
  
    printf( "spine(" );
    for( int i = 0; i < normalized_shape_spines[ shape_id ].size(); ++i ) {
      printf( " %d", normalized_shape_spines[ shape_id ][ i ] );
    }
    printf( " )  width(" );
    for( int i = 0; i < normalized_shape_widths[ shape_id ].size(); ++i ) {
      printf( " %d", normalized_shape_widths[ shape_id ][ i ] );
    }
    printf( " )  left(" );
    for( int i = 0; i < normalized_shape_lefts[ shape_id ].size(); ++i ) {
      printf( " %d", normalized_shape_lefts[ shape_id ][ i ] );
    }
    printf( " )  right(" );
    for( int i = 0; i < normalized_shape_rights[ shape_id ].size(); ++i ) {
      printf( " %d", normalized_shape_rights[ shape_id ][ i ] );
    }
    printf( " ) holes: upper(%d) lower(%d) middle(%d), wheremaxwidth %d, right_shift_upper %d, right_shift_bigger %d, has_big_left_shift %d, has_big_right_shift %d\n", 
      num_upper_white_shapes[ shape_id ], num_lower_white_shapes[ shape_id ], num_middle_white_shapes[ shape_id ], 
      where_max_width[ shape_id ], right_shift_upper[ shape_id ], right_shift_bigger[ shape_id ],
      has_big_left_shift[ shape_id ], has_big_right_shift[ shape_id ] );*/
  }
}

int main( int argc, char *argv[] ) {
  /*char in_path[ 80 ];
  char out_path[ 80 ];
  int sample_no = 10;
  sprintf( in_path, "c:\\samples\\%03d", sample_no );
  sprintf( out_path, "c:\\answers\\test%03d.txt", sample_no );
  freopen( in_path, "r", stdin );
  freopen( out_path, "w", stdout );*/
  getImage();
  selectShapes();
  recognizeDigits();

  return 0;
}