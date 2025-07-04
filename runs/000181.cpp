// vim: et ts=4 sts=4 sw=4 :
#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <map>
#include <list>
#include <sstream>
#include <vector>

typedef std::vector< float > Data;
const float eps = 0.01f;

float binaryColor( float c )
{
    if ( c < eps )
        return 0.0f;
    return 1.0f;
}

Data::size_type searchMax( const Data& data, Data::size_type skipleft = 0, Data::size_type skipright = 1 )
{
    Data::size_type max = skipleft;
    for ( Data::size_type i = skipleft + 1; i < data.size() - skipright; ++i )
    {
        if ( data[max] < data[i] )
            max = i;
    }
    return max;
}

Data::size_type searchMin( const Data& data, Data::size_type skipleft = 0, Data::size_type skipright = 1 )
{
    Data::size_type min = skipleft;
    for ( Data::size_type i = skipleft + 1; i < data.size() - skipright; ++i )
    {
        if ( data[min] > data[i] )
            min = i;
    }
    return min;
}

class Image
{
public:
    Data data;
    int lineLength;
    int x, y;

    Image( ):
        data(),
        lineLength( 0 ),
        x( 0 ), y( 0 )
    {
    }

    Image( const Image& im ):
        data( im.data ),
        lineLength( im.lineLength ),
        x( im.x ), y( im.y )
    {
    }

    Image( const Image& im, int bboxLeft, int bboxTop, int width, int height ):
        data(),
        lineLength( width ),
        x( bboxLeft ), y( bboxTop )
    {
        for ( int y = bboxTop; y < bboxTop + height; ++y )
            for ( int x = bboxLeft; x < bboxLeft + width; ++x )
            {
                data.push_back( im.getPixel(x, y) );
            }
    }

    int height( ) const
    {
        return data.size()/lineLength + data.size()%lineLength;
    }

    int width( ) const
    {
        return lineLength;
    }

    Data::value_type getPixel( int x, int y ) const
    {
        Data::size_type idx = y*lineLength + x;
        assert( idx < data.size() );
        return data[idx];
    }

    Data::value_type sum( int x, int y, int width, int height ) const
    {
        assert( width > 0 && height > 0 );

        Data::value_type v = 0;
        for ( int j = y; j < y + height; ++j )
            for ( int i = x; i < x + width; ++i )
                v += getPixel( i, j );
        return v;
    }

    Data::value_type sum( int x, int y, int width, int height, float (*colorProcessor)(float) ) const
    {
        assert( width > 0 && height > 0 );

        Data::value_type v = 0;
        for ( int j = y; j < y + height; ++j )
            for ( int i = x; i < x + width; ++i )
                v += colorProcessor( getPixel(i, j) );
        return v;
    }

    std::vector< Image > split( bool diagonalConnected = true ) const
    {
        std::vector< Image > result;

        Data d = data;
        for ( Data::const_iterator it = d.begin(); it != d.end(); ++it )
        {
            if ( *it < eps )
                continue;

            result.push_back( extractConnected(d, it - d.begin(), diagonalConnected) );
        }

        return result;
    }

private:
    Image extractConnected( Data& d, Data::size_type p, bool diagonalConnected ) const
    {
        std::vector< Data::size_type > needVisit;
        std::vector< std::pair<std::pair<int, int>, Data::value_type> > selected;
        int bboxLeft = p%lineLength;
        int bboxRight = bboxLeft;
        int bboxTop = p/lineLength;
        int bboxBottom = bboxTop;

        /* Searching */
        needVisit.push_back( p );
        while ( !needVisit.empty() )
        {
            Data::size_type point = needVisit.back( );
            needVisit.pop_back( );
            
            if ( d[point] < eps )
                continue;

            int y = point/lineLength;
            int x = point%lineLength;

            selected.push_back( std::make_pair(std::make_pair(x, y), d[point]) );
            d[point] = 0.0f;

            if ( x < bboxLeft )
                bboxLeft = x;
            if ( x > bboxRight )
                bboxRight = x;
            if ( y < bboxTop )
                bboxTop = y;
            if ( y > bboxBottom )
                bboxBottom = y;
           
            /* 1 2 3 *
             * 4 5 6 *
             * 7 8 9 */ 


            /* 1, 4, 7 */
            if ( x > 0 )
            {
                /* Visit 4 */
                needVisit.push_back( point - 1 );

                if ( diagonalConnected )
                {
                    /* Visit 1 */
                    if ( y > 0 )
                        needVisit.push_back( point - lineLength - 1 );
                    /* Visit 7 */
                    if ( point + lineLength - 1 < d.size() )
                        needVisit.push_back( point + lineLength - 1 );
                }
            }

            /* Visit 2 */
            if ( y > 0 )
            {
                needVisit.push_back( point - lineLength );
            }
            /* Visit 8 */
            if ( point + lineLength < d.size() )
                needVisit.push_back( point + lineLength );

            /* 3, 6, 9 */
            if ( x < lineLength - 1 )
            {
                /* Visit 6 */
                if ( point + 1 < d.size() )
                    needVisit.push_back( point + 1 );

                if ( diagonalConnected )
                {
                    /* Visit 3 */
                    if ( y > 0 )
                        needVisit.push_back( point - lineLength + 1 );
                    /* Visit 9 */
                    if ( x < lineLength - 1 && point + lineLength + 1 < d.size() )
                        needVisit.push_back( point + lineLength + 1 );
                }
            }
        }

        /* Extracting */
        Image result;
        result.lineLength = bboxRight - bboxLeft + 1;
        result.x = bboxLeft;
        result.y = bboxTop;
        result.data.resize( (bboxRight - bboxLeft + 1)*(bboxBottom - bboxTop + 1), 0.0f );
        while ( !selected.empty() )
        {
            std::pair< std::pair<int, int>, Data::value_type > point = selected.back();
            selected.pop_back( );

            int x = point.first.first;
            int y = point.first.second;
            Data::value_type color = point.second;

            result.data[(y - bboxTop)*result.lineLength + (x - bboxLeft)] = color;
        }
        return result;
    }
};

std::istream& operator>>( std::istream& f, Image& image )
{
    int lineLength = 0;

    while ( f.good() )
    {
        char c = f.get();
        if ( !f.good() )
            break;

        switch ( c )
        {
        case '.':
            image.data.push_back( 0.0f );
            ++lineLength;
            break;
        case '%':
            image.data.push_back( 0.333f );
            ++lineLength;
            break;
        case '#':
            image.data.push_back( 0.666f );
            ++lineLength;
            break;
        case '@':
            image.data.push_back( 1.0f );
            ++lineLength;
            break;
        case '\n':
        case '\r':
            if ( image.lineLength == 0 )
                image.lineLength = lineLength;
            lineLength = 0;
            break;
        default:
            f.putback( c );
            return f;
        }
    }

    return f;
}

std::ostream& operator<<( std::ostream& f, const Image& image )
{
    char chars[] = { '.', '%', '#', '@' };
    
    for ( Data::size_type i = 0; i < image.data.size(); ++i )
    {
        if ( i > 0 && i%image.lineLength == 0 )
            f << "\n";
        int x = (int)(image.data[i]*(sizeof(chars) - 1) + 0.5);
        f << chars[x];
    }

    return f;
}

Image getImageInXRange( const Image& im, int left, int right )
{
    assert( left < right );

    int top, bottom;
    for ( top = 0; top < im.height() - 1; ++top )
    {
        if ( im.sum( left, top, right - left + 1, 1 ) > eps )
            break;
    }
    for ( bottom = im.height() - 1; bottom > top; --bottom )
    {
        if ( im.sum( left, bottom, right - left + 1, 1 ) > eps )
            break;
    }
    return Image( im, left, top, right - left + 1, bottom - top + 1 );
}

char recognize( const Image& im )
{
    Data::size_type h = im.height();
    Data::size_type w = im.width();

    Data vEnergy( w );
    Data hEnergy( h );

    Data lEnergy( h ); /* empty from left */
    Data rEnergy( h ); /* empty from right */
    Data tEnergy( w ); /* empty from top */
    Data bEnergy( w ); /* empty from bottom */

    for ( Data::size_type y = 0; y < h; ++y )
    {
        for ( Data::size_type x = 0; x < w; ++x )
        {
            Data::value_type v = im.getPixel( x, y );
            vEnergy[x] += v;
            hEnergy[y] += v;
        }

        for ( Data::size_type x = 0; x < w; ++x )
        {
            if ( im.getPixel(x, y) > eps )
                break;

            lEnergy[y] += 1.0f;
        }

        for ( Data::size_type x = w; x > 0; )
        {
            --x;

            if ( im.getPixel(x, y) > eps )
                break;

            rEnergy[y] += 1.0f;
        }
    }

    for ( Data::size_type x = 0; x < w; ++x )
    {
        for ( Data::size_type y = 0; y < h; ++y )
        {
            if ( im.getPixel(x, y) > eps )
                break;

            tEnergy[x] += 1.0f;
        }

        for ( Data::size_type y = h; y > 0; )
        {
            --y;

            if ( im.getPixel(x, y) > eps )
                break;

            bEnergy[x] += 1.0f;
        }
    }

    /* Searching max left and right energy */
    Data::size_type maxLeft = searchMax( lEnergy, 3, 3 );
    Data::size_type maxRight = searchMax( rEnergy, 3, 3 );
    Data::value_type maxLeftEnergy = lEnergy[maxLeft];
    Data::value_type maxRightEnergy = rEnergy[maxRight];

    /* Calculating some mins and maxs */
    Data::size_type minUL = searchMin( lEnergy, 0, h/2 );
    Data::size_type minLL = searchMin( lEnergy, h/2, 0 );
    Data::size_type minUR = searchMin( rEnergy, 0, h/2 );
    Data::size_type minLR = searchMin( rEnergy, h/2, 0 );
    Data::size_type maxUL = searchMax( lEnergy, 3, h/2 );
    Data::size_type maxLL = searchMax( lEnergy, h/2, 3 );
    Data::size_type maxUR = searchMax( rEnergy, 3, h/2 );
    Data::size_type maxLR = searchMax( rEnergy, h/2, 3 );
    int scaleUL = w / (w - lEnergy[minUL]);
    int scaleLL = w / (w - lEnergy[minLL]);
    int scaleUR = w / (w - rEnergy[minUR]);
    int scaleLR = w / (w - rEnergy[minLR]);

    Data::size_type maxML = searchMax( lEnergy, h/3, h/3 );
    Data::size_type maxMR = searchMax( rEnergy, h/3, h/3 );
    Data::size_type minML = searchMin( lEnergy, h/3, h/3 );
    Data::size_type minMR = searchMin( rEnergy, h/3, h/3 );
    int diffMaxM = maxMR - maxMR;
    if ( diffMaxM < 0 )
        diffMaxM = -diffMaxM;

    /* Correcting for slanted fonts */
    int isSlanted = false;
    if ( maxRight != maxUR && maxRightEnergy - rEnergy[minLR] < rEnergy[maxUR] + lEnergy[minUL] )
    {
        maxRight = maxUR;
        maxRightEnergy = rEnergy[maxRight] + lEnergy[minUL];
        isSlanted = true;
    }

    Image inversed( im );
    for ( Data::iterator it = inversed.data.begin(); it != inversed.data.end(); ++it )
    {
        if ( *it < eps )
            *it = 1.0f;
        else
            *it = 0.0f;
    }

    int segments = 0;
    int darkSegments = 0;
    int triangularSegments = 0;

    int highBigCircle = false;
    int lowBigCircle = false;
    int zeroCircle = false;
    std::vector< Image > interior = inversed.split( false );
    for ( std::vector< Image >::iterator it = interior.begin(); it != interior.end(); )
    {
        if ( it->x == 0 || it->y == 0 ||
            it->x + it->width() == w || it->y + it->height() == h )
        {
            it = interior.erase( it );
        }
        else if ( it->width() <= 1 || it->height() <= 1 )
        {
            it = interior.erase( it );
        }
        else
        {
            ++segments;
            Data::value_type v = it->sum( 0, 0, it->width(), it->height() );
            if ( v > 7.5f )
            {
                if ( it->y < h/3 && it->height() > 0.7*h && v > 0.7*it->width()*it->height() )
                {
                    zeroCircle = true;
                }
                else
                {
                    if ( it->y < h/3 && it->height() > 0.2*h )
                        highBigCircle = true;
                    if ( it->y + it->height() > 2*h/3 && it->height() > 0.25*h )
                        lowBigCircle = true;
                }
                ++darkSegments;
            }

            int halfw = it->width()/2;
            int halfh = it->height()/2;
            Data::value_type ul = it->sum( 0, 0, halfw, halfh );
            Data::value_type br = it->sum( halfw + it->width()%2, halfh + it->height()%2, halfw, halfh );
            if ( ul < halfw && br > 3.0*halfw*halfh/4 )
                ++triangularSegments;

            ++it;
        }
    }

    //std::cout << "Segments: " << segments << std::endl;
    //std::cout << "Dark segments: " << darkSegments << std::endl;
    //std::cout << "Triangular segments: " << triangularSegments << std::endl;

    /* 1 */
    if ( 3*w < h )
    {
        return '1';
    }

    if ( lEnergy[h/2] + rEnergy[h/2] > 0.5*w )
    {
        if ( hEnergy[h-1] > 0.7*w && abs(lEnergy[h/2] - rEnergy[h/2]) < 0.25*w )
        {
            Data::value_type e = im.sum( lEnergy[h/2], 0, w - lEnergy[h/2] - rEnergy[h/2], h, binaryColor );
            if ( e > 0.8*(w - lEnergy[h/2] - rEnergy[h/2])*h )
            {
                return '1';
            }
        }

        if ( maxLeftEnergy + maxRightEnergy < 0.70*w &&
            segments <= 1 )
        {
            return '1';
        }
    }

    /* 5 */
    if ( maxRight < maxLeft && maxRight < 0.6*w &&
        maxLeftEnergy + maxRightEnergy > w + 1 )
    {
        if ( im.sum( im.width() - rEnergy[maxRight], 0, rEnergy[maxRight], maxRight + 1 ) > 2.5f )
        {
            return '5';
        }
    }

    /* 4 */
    if ( triangularSegments == 1 && darkSegments <= 1 )
    {
        return '4';
    }

    if ( lEnergy[minML] < 0.2*w && rEnergy[minMR] < 0.2*w )
    {
        Data::size_type begin;
        for ( begin = w-2; begin > 2*w/3; --begin )
        {
            if ( vEnergy[begin - 1] - vEnergy[begin] > 3 )
                break;
        }

        if ( begin > 2*w/3 && tEnergy[begin + 1] > 0.4*h && bEnergy[begin + 1] > 0.2*h &&
            vEnergy[begin - 2] > 2*vEnergy[begin + 1] &&
            hEnergy[tEnergy[begin + 1] + 1] > 0.8*w )
        {
            return '4';
        }
    }

    /* 2 */
    if ( maxMR > maxML && maxMR > h/2 &&
        rEnergy[maxMR] + lEnergy[maxML] > 2*w/3 )
    {
        if ( im.sum( im.width() - rEnergy[maxMR], maxMR, rEnergy[maxMR], h - maxMR ) > 2.5f )
        {
            return '2';
        }
    }

    /* 3 */
    if ( lEnergy[maxML] > w/2 &&
        lEnergy[minUL] + rEnergy[minUR] < w/2 &&
        lEnergy[minLL] + rEnergy[minLR] < w/2 )
    {
        Data::size_type extra = maxMR;
        if ( rEnergy[extra-3] < rEnergy[extra] && rEnergy[extra+3] < rEnergy[extra] )
            return '3';
    }

    /* 7 */
    if ( minUL < h/2 && lEnergy[minUL] < 0.2*w &&
        minUR < h/4 && rEnergy[minUR] < 0.2*w )
    {
        Data::size_type begin;
        for ( begin = 1; begin < h/3; ++begin )
        {
            if ( hEnergy[begin - 1] > hEnergy[begin] )
                break;
        }

        Data::size_type height = 0;
        for ( Data::size_type i = 0; i < begin; ++i )
        {
            if ( lEnergy[i] < 1.5 && rEnergy[i] < 1.5 )
                ++height;
            else if ( hEnergy[i] > 0.8*w )
                ++height;
        }

        Data::value_type upper = im.sum( 0, 0, w, begin, binaryColor );
        Data::value_type lower = im.sum( begin, 0, w, h - begin );

        if ( height > 0 && begin - height < h/6 && upper > 0.8*w*height )
        {
            if ( lower < 0.6*w*(h - begin) && lEnergy[maxML] > 0.3*w )
                return '7';
        }
    }

    /* 8 */
    if ( highBigCircle && lowBigCircle && segments >= 2 && maxLeftEnergy < 0.5*w && maxRightEnergy < 0.5*w )
    {
        return '8';
    }

    if ( diffMaxM < h/4 && lEnergy[maxML] > w/4 && rEnergy[maxMR] > w/4 &&
        lEnergy[minUL] + rEnergy[minUR] < w/2 &&
        lEnergy[minLL] + rEnergy[minLR] < w/2 && segments >= 1 )
    {
        return '8';
    }

    if ( lEnergy[maxML] + rEnergy[maxMR] < w &&
        lEnergy[minUL] + rEnergy[minUR] < w/2 &&
        lEnergy[minLL] + rEnergy[minLR] < w/2 )
    {
        Data::size_type extraL = maxML;
        Data::size_type extraR = maxMR;
        if ( rEnergy[extraR-3] < rEnergy[extraR] && rEnergy[extraR+3] < rEnergy[extraR] &&
            lEnergy[extraL-3] < lEnergy[extraL] && lEnergy[extraL+3] < rEnergy[extraL] )
        {
            return '8';
        }
    }

    /* 9 */
    if ( highBigCircle && !lowBigCircle )
    {
        return '9';
    }

    /* 6 */
    if ( lowBigCircle && !highBigCircle )
    {
        return '6';
    }

    if ( maxRight < h/2 && maxRightEnergy > w/2 &&
        lEnergy[minLL] + rEnergy[minLR] < w/2 )
    {
        return '6';
    }

    /* 0 */
    if ( lEnergy[maxML] + rEnergy[maxLR] < 0.5*w && segments > 0 )
    {
        return '0';
    }

    if ( zeroCircle )
    {
        return '0';
    }

    return '?';
}

inline bool isSmall( const Image& im )
{
    return im.height() < 8 || im.width() < 4;
}

bool compareImageParts( const Image& a, const Image& b )
{
    if ( a.x != b.x )
        return a.x < b.x;
    return a.y < b.y;
}

int main( )
{
    std::cout.precision( 2 );

    Image image;
    std::cin >> image;

    //std::cout << "Loaded image:" << std::endl;
    //std::cout << image << std::endl;

    std::vector< Image > acceptedSymbols;
    std::vector< Image > items = image.split( );
    for ( std::vector< Image >::iterator it = items.begin(); it != items.end(); ++it )
    {
        const Image& im = *it;
        //std::cout << "Analyzing..." << std::endl;
        if ( isSmall(im) )
        {
            //std::cout << "Too small" << std::endl;
            continue;
        }

        bool isFrame = false;
        for ( std::vector< Image >::iterator inside = items.begin(); inside != items.end(); ++inside )
        {
            if ( im.x < inside->x && im.y < inside->y &&
                im.x + im.width() > inside->x + inside->width() &&
                im.y + im.height() > inside->y + inside->height() &&
                !isSmall( *inside ) )
            {
                isFrame = true;
            }
        }
        if ( isFrame )
        {
            //std::cout << "Frame detected" << std::endl;
            continue;
        }

        Data::value_type avgEnergy = 0;
        Data vEnergy;
        for ( int x = 0; x < im.width(); ++x )
        {
            Data::value_type energy = 0;
            Data::value_type bonusEnergy = 0;
            for ( Data::size_type i = x; i < im.data.size(); i += im.lineLength )
            {
                energy += im.data[i];
                if ( im.data[i] > 1 - eps )
                    bonusEnergy += 1;
            }
            vEnergy.push_back( energy + bonusEnergy );
            avgEnergy += energy;
        }
        avgEnergy /= vEnergy.size();
        //std::cout << "Average energy: " << avgEnergy << std::endl;

        int energyDigits = 0;
        int prevHigh = 0;
        for ( Data::size_type i = 0; i < vEnergy.size(); ++i )
        {
            if ( vEnergy[i] < avgEnergy/4.5 )
            {
                if ( prevHigh > 3 )
                    energyDigits++;
                prevHigh = 0;
            }
            else
            {
                ++prevHigh;
            }
        }
        if ( prevHigh > 3 )
            energyDigits++;

        if ( energyDigits > 1 )
        {
            Data::size_type left = 0;

            while ( energyDigits > 1 )
            {
                Data::size_type right = left + (im.width() - left)/energyDigits;
                while ( left < right && right < vEnergy.size() )
                {
                    if ( vEnergy[right] > vEnergy[right-1] || vEnergy[right] > vEnergy[right+1] )
                    {
                        if ( vEnergy[right-1] < vEnergy[right+1] )
                            right -= 1;
                        else
                            right += 1;
                    }
                    else
                    {
                        break;
                    }
                }
                assert( left != right );

                acceptedSymbols.push_back( getImageInXRange(im, left, right) );

                --energyDigits;
                left = right + 1;
            }

            acceptedSymbols.push_back( getImageInXRange(im, left, im.width() - 1) );
        }
        else
        {
            acceptedSymbols.push_back( im );
        }
    }

    std::sort( acceptedSymbols.begin(), acceptedSymbols.end(), compareImageParts );

    for ( std::vector< Image >::iterator it = acceptedSymbols.begin(); it != acceptedSymbols.end(); ++it )
    {
        //std::cout << std::endl;
        std::cout << recognize( *it );// << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
