/* 
 * File:   taska.cpp
 * Author: Sergey Nikishin
 *
 * Created on 6 Сентябрь 2010 г.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

typedef vector<string> CharImage;
typedef vector<vector<double> > DataArray;

// перевести символ-пиксель изображения в число
string IntToImagePixel( const int code )
{
    if( code == 0 ) {
        return ".";
    }
    else if( code == 1 ) {
        return "%";
    }
    else if( code == 2 ) {
        return "#";
    }
    else if( code == 3 ) {
        return "@";
    }
    else if( code == -3 ) {
        return "-";
    }
    else if( code == -6 ) {
        return "=";
    }
    else {
        cerr << "<ERR> bad code " << code << " uccured in input sequence" << endl;
        return "+";
    }
}

// вывести на экран изображение
void PrintImage( const CharImage & strings, std::ostream & stream )
{
    for ( int i = 0; i < strings.size (); ++i ) {
        stream << strings[ i ] << endl;
    }
}

// вывести на экран массив
void PrintArray( const DataArray & vectors, std::ostream & stream )
{
    for ( int i = 0; i < vectors.size (); ++i ) {
        for ( int j = 0; j < vectors[i].size (); ++j ) {
            stream << IntToImagePixel( static_cast< int >( vectors[ i ][ j ] ) );
        }
        stream << endl;
    }
}

// вывести на экран массив
// строки обрамлены для собственных нужд
void PrintArrayBraced( const DataArray & vectors, std::ostream & stream )
{
    for ( int i = 0; i < vectors.size (); ++i )
    {
        stream << "\"";
        for ( int j = 0; j < vectors[i].size (); ++j ) {
            stream << IntToImagePixel( static_cast< int >( vectors[ i ][ j ] ) );
        }
        stream << "\"," << endl;
    }
}

// простое преобразование цифры в строку
string DigitToStr( const int value )
{
    static const string digits [10] ={ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    return digits[ value % 10 ];
}


static const string digit0[ 16 ] = {
//    ".....@@@@@@.....",
//    "..@@@@@@@@@@@@..",
//    ".@@@@@@@@@@@@@@.",
//    "@@@@........@@@@",
//    "@@@@........@@@@",
//    "@@@@........@@@@",
//    "@@@@........@@@@",
//    "@@@@....==..@@@@",
//    "@@@@....==..@@@@",
//    "@@@@........@@@@",
//    "@@@@........@@@@",
//    "@@@@........@@@@",
//    "@@@@........@@@@",
//    ".@@@@@@@@@@@@@@.",
//    "...@@@@@@@@@@@..",
//    ".....@@@@@@....."
"....%@@@@@@%%...",
"..%@@@@@@#%@@@..",
".@@@@@@@@#%%%@@%",
"@@@@%%%%%...%%@@",
"@@@@%%%%%...%%%@",
"@@@@%%%%%==.%%%@",
"@@@@%%%%%==.%%%#",
"@@@@%%%%%==.%%%#",
"@@@@%%%%%==.%%%#",
"@@@@%%%%%==.%%%#",
"@@@@%%%%%==.%%%#",
"@@@@%%%%%==.%%%@",
"@@@@%%%%%...%%@@",
".@@@@@@@@#%%%@@%",
"..%@@@@@@#%%@@%.",
"....%@@@@@@%%..."
};
static const string digit1[ 16 ] = {
//    ".......@@@@@....",
//    ".......@@@@@....",
//    ".......@@@@@....",
//    ".......@@@@@....",
//    ".......@@@@@....",
//    "==.....@@@@@....",
//    "==.....@@@@@....",
//    "==.....@@@@@....",
//    "==.....@@@@@....",
//    ".......@@@@@....",
//    ".......@@@@@....",
//    ".......@@@@@....",
//    ".......@@@@@....",
//    ".......@@@@@....",
//    "......@@@@@@@...",
//    "....@@@@@@@@@@.."
"......@@@@@@@@..",
"@@@@@@@@@@@@@@..",
"....@@@@@@@@@@..",
"....@@@@@@@@@@..",
"....@@@@@@@@@@..",
"=-..@@@@@@@@@@..",
"=-..@@@@@@@@@@..",
"=-..@@@@@@@@@@..",
"=-..@@@@@@@@@@..",
"=-..@@@@@@@@@@..",
"....@@@@@@@@@@..",
"....@@@@@@@@@@..",
"....@@@@@@@@@@..",
"....@@@@@@@@@@..",
"....@@@@@@@@@@..",
"@@@@@@@@@@@@@@@@"

};
static const string digit2[ 16 ] = {
//        "....@@@@@@@@@...",
//        "...@@@.....@@@@.",
//        ".@@..........@@@",
//        ".@@..........@@@",
//        ".@@@@@.......@@@",
//        ".@@@@@......@@@@",
//        "..@@@......@@@@.",
//        "...........@@@..",
//        ".........@@@@...",
//        "........@@@@....",
//        "......@@@.......",
//        ".....@@@.......@",
//        "...@@.........@@",
//        "..@@..........@@",
//        "@@@@@@@@@@@@@@@@",
//        "@@@@@@@@@@@@@@@@"
"....@@@@@@@@@...",
"...@@@@@@@@@@@@.",
".@@@@@@@@@@@@@@@",
".@@@@@@@@@@@@@@@",
".@@@@@..@@@@@@@@",
".@@@@@.@@@@.@@@@",
"..@@@.@@@..@@@@@",
"....@@@@...@@@@.",
"....@@...@@@@@..",
"..@@@...@@@@....",
".@@@..@@@@@.....",
"@@..@@@@@......@",
"@@@@@@@......@@@",
"@@@@@@@@....@@@@",
"@@@@@@@@@@@@@@@@",
"....@@@@@@@@@@@@"

};
static const string digit3[ 16 ] = {
    "....#@@@@@@@@#%.",
    "...@@@@@#%#@@@@#",
    ".%#@@@#....%#@@@",
    "%@@@#.......%@@@",
    ".%#@%......%%@@@",
    ".%%%%...%%%%#@@%",
    "..%%...%%%#@@#%%",
    "......%@@@@@@@@#",
    ".....%%@@#%@@@@@",
    ".....%%%....%@@@",
    "............%%@@",
    "..%.........%%@@",
    "@@@@.......%%#@@",
    "@@@@#......%%@@@",
    "%#@@@%%%@@@@@@#%",
    ".%%#@@@@@@@@@..."
};
static const string digit4[ 16 ] = {
"......%%%@###%%.",
"......%%@@###%%.",
".....%%%@####%%.",
".....%%######%%.",
"....%%@@@#####%.",
"....%##@@@####%.",
"...%@##@#@@@##%.",
"..#@#####@@@###.",
".%@@@@###@@@@@#%",
".@@@@@#%#@@@@@#%",
"########@@@@####",
"#######@@@@@####",
"%%%%%%%%#@######",
"%%%%%%%%#@####%%",
"........@@#####.",
"........@@#####%"
//"......@@@@@@@...",
//"......@@@@@@@...",
//".....@@@@@@@@...",
//".....@@@@@@@@...",
//"....@@@@@@@@@@..",
//"....@@@@@@@@@@..",
//"...@@@@@.@@@@@..",
//"...@@@@..@@@@@..",
//"..@@@@...@@@@@..",
//".@@@@@...@@@@@..",
//"@@@@@@@@@@@@@@@@",
//"@@@@@@@@@@@@@@@@",
//".........@@@@@@@",
//".........@@@@@..",
//"........@@@@@@@.",
//".......@@@@@@@@@"

};
static const string digit5[ 16 ] = {
    "..@@@@@@@@@@@@@.",
    "..@@@@@@@@@@@@@.",
    "..@@@@@@@@@@@@@.",
    "..@@............",
    "..@@............",
    "..@@@@@@@@@.....",
    "..@@@@@@@@@@@...",
    "...........@@@@.",
    ".............@@@",
    "..............@@",
    "..............@@",
    "..............@@",
    "@@@@.........@@@",
    "@@@@@........@@.",
    "..@@@@.....@@@..",
    "...@@@@@@@@@@..."
};
static const string digit6[ 16 ] = {
"....%%%@@#%%%%%%",
"...%@@@@@@%.....",
"...@@@@%%.......",
"..%@@@%%........",
".%@@%%%%.%%%....",
"%%@@%%%%%%%%%%..",
"%@@%@@@@@@@@@@@#",
"@@@@@@%%%%%%@@@@",
"@@@@%%%%%%%%%%@@",
"@@@%%%...%%%%%%@",
"@@@%%%%..%%%%%%@",
"@@@%%%%%..%%%%%@",
"%%@@%%%%.%%%%%%@",
".%@@%%%%%%%%%%.%",
"..%@@@@%%%%%@@%%",
"....@@@@@@@@%%%%"
};
static const string digit7[ 16 ] = {
    "##@@@@@@@@@@@@@@",
    "##@@@@@@@@@@@@@@",
    "%%%%%%%%%%%%%##@",
    ".............@#%",
    "...........%##%.",
    "..........%##...",
    "........%%@@%...",
    ".......%@@@#....",
    ".....%%@@@%.....",
    "....%%#@@@......",
    "...%%##@@#......",
    "...%%#@@%%......",
    "...%%#@#%%......",
    "...%#@@#%%......",
    "...%#@@%%%......",
    "...%#@@%........"
};
static const string digit8[ 16 ] = {
"...@@@@@@@@@@@..",
"..%@@@%...%@@@@%",
".%@@@.......%@@@",
"%@@@.........@@@",
"@@@@.........@@@",
"%@@@@@%.....@@@.",
".@@@@@@@@.%@@@%.",
"...@@@@@@@@@@%..",
"...%@@@@@@@@@@@.",
"..%@@@%%@@@@@@@@",
"%@@@........@@@@",
"@@@%........%@@@",
"@@@..........@@@",
"@@@%........%@@@",
".@@@@@@...%@@@%.",
"..%@@@@@@@@@@%.."
};
static const string digit9[ 16 ] = {
    "...@@@@@@@@@....",
    "..@@@@%%%%@@@%..",
    ".@@@%%%%%%%%@@%.",
    "@@@%........%@@.",
    "@@@..........@@@",
    "@@@..........@@@",
    "@@@%........%@@@",
    "%@@@%......%@@@@",
    ".%@@@@@@@@@@%@@@",
    "..%%@@@@@@%%%@@@",
    "....%%%%%%...@@@",
    "..%%........%@@%",
    "%@@@%......%@@@.",
    "%@@@@.....%@@@%.",
    ".@@@%%%%%@@@@...",
    "..@@@@@@@@@%...."
};


// перевести символ-пиксель изображения в число
int ImagePixelToInt( const char imagePixel )
{
    if( imagePixel == '.' ) {
        return 0;
    }
    else if( imagePixel == '@' ) {
        return 3;
    }
    else if( imagePixel == '%' ) {
        return 1;
    }
    else if( imagePixel == '#' ) {
        return 2;
    }
    else if( imagePixel == '-') {
        return -3;
    }
    else if( imagePixel == '=') {
        return -6;
    }
    else {
        cerr << "<ERR> bad symbol " << imagePixel << " uccured in input sequence" << endl;
        return ( (-1U) >> 1 );
    }
}

// образцы для распознавания
struct Patterns
{
public:
    Patterns()
    {
        ConvertPattern ( digit0, 16, 16, &digits[ 0 ] );
        ConvertPattern ( digit1, 16, 16, &digits[ 1 ] );
        ConvertPattern ( digit2, 16, 16, &digits[ 2 ] );
        ConvertPattern ( digit3, 16, 16, &digits[ 3 ] );
        ConvertPattern ( digit4, 16, 16, &digits[ 4 ] );
        ConvertPattern ( digit5, 16, 16, &digits[ 5 ] );
        ConvertPattern ( digit6, 16, 16, &digits[ 6 ] );
        ConvertPattern ( digit7, 16, 16, &digits[ 7 ] );
        ConvertPattern ( digit8, 16, 16, &digits[ 8 ] );
        ConvertPattern ( digit9, 16, 16, &digits[ 9 ] );
    }

    static const int count = 10;
    static const int width = 16;
    static const int height = 16;

    DataArray digits[ count ];
private:
     // конвертировать массив строк в двумерный массив
    static void ConvertPattern( const string * const originalImage, const int width, const int height, DataArray * vectors )
    {
        vectors->resize ( height );
        for( int row = 0; row < height; ++row )
        {
            (*vectors)[ row ].resize ( width );
            for( int col = 0; col < width; ++col )
            {
                char ch = originalImage[ row ][ col ];
                int code = ImagePixelToInt ( ch );
                (*vectors)[ row ][ col ] = code;
            }
        }
    }

};


// реализует операции
// по распознаванию и обработке изображений
class Recognition
{
public:
    // распознать символы на картинке
    static string Recognize( const CharImage & image, const string controlValue = "" )
    {
        // подрезать границы
        CharImage source = image;
        CutEdges ( source );

        // разделить на части
        CharImage digits[ 3 ];
        ParseFor3Parts( source, digits[ 0 ], digits[ 1 ], digits[ 2 ] );

        // подкорректировать каждую часть
        for ( int i = 0; i < 3; ++i )
        {
            CutEdges ( digits[ i ] );
            CutGarbage ( digits[ i ] );
            CutEdges ( digits[ i ] );
        }

        // распознать все части
        return RecognizeAllSymbolImages( digits, 3, controlValue );
    }

private:

    // обрезать изображение слева на count элементов
    static void CutImageLeft( CharImage & image, int count )
    {
        if( count > 0 && count <= image[ 0 ].size () )
        {
            for ( int i = 0; i < image.size (); ++i )
            {
                image[ i ].erase( 0, count );
            }
        }
    }

    // обрезать изображение слева на count элементов
    static void CutImageRight( CharImage & image, int count )
    {
        if( count > 0 && count <= image[ 0 ].size () )
        {
            for ( int i = 0; i < image.size (); ++i )
            {
                image[ i ].erase ( image[ i ].length() - count, count  );
            }
        }
    }

    // обрезать изображение сверху на count элементов
    static void CutImageTop( CharImage & image, int count )
    {
        if( count > 0 && count <= image.size () ) {
            image.erase ( image.begin(), image.begin() + count );
        }
    }

    // обрезать изображение снизу на count элементов
    static void CutImageBottom( CharImage & image, int count )
    {
        if( count > 0 && count <= image.size () ) {
            image.erase ( image.end() - count, image.end() );
        }
    }

    // подрезать пустоты на границах изображения
    static void CutEdges ( CharImage & image, const double fill_percent = 0.015 )
    {
        if( image.empty () ) {
            return;
        }

        int counter = 0;

        // обрезать по нижней границе
        for ( int j = image.size () - 1; j >= 0; --j )
        {
            counter = 0;
            for ( int i = 0; i < image[ j ].length (); ++i )
            {
                int code = ImagePixelToInt ( image[ j ][ i ] );
                if( code >= 2 ) {
                    ++counter;
                }
            }
            // если заполненность меньше N%, то удалять такие строки
            if( counter >= image.size() * fill_percent )
            {
                CutImageBottom( image, image.size() - j - 1 );
                break;
            }

            
        }

        // обрезать по верхней границе
        for ( int j = 0; j < image.size (); ++j )
        {
            counter = 0;
            for ( int i = 0; i < image[ j ].length (); ++i )
            {
                int code = ImagePixelToInt ( image[ j ][ i ] );
                if( code >= 2 ) {
                    ++counter;
                }
            }
            // если заполненность меньше 5%, то удалять такие строки
            if( counter >= image.size() * fill_percent ) {
                CutImageTop( image, j );
                break;
            }
        }

        // левая граница
        int x_left = -1;
        for ( int i = 0; i < image[0].length (); ++i )
        {
            counter = 0;
            for ( int j = 0; j < image.size (); ++j )
            {
                int code = ImagePixelToInt ( image[ j ][ i ] );
                if( code >= 2 ) {
                    ++counter;
                }
            }
            // если заполненность меньше 5%, то удалять такие строки
            if( counter >= image[ 0 ].size() * fill_percent ) {
                x_left = i;
                break;
            }
        }

        CutImageLeft ( image, x_left );

        // правая граница
        int x_right = -1;
        for ( int i = image[0].length () - 1; i >= 0; --i )
        {
            counter = 0;
            for ( int j = 0; j < image.size (); ++j )
            {
                int code = ImagePixelToInt ( image[ j ][ i ] );
                if( code >= 2 ) {
                    ++counter;
                }
            }
            // если заполненность меньше 5%, то удалять такие строки
            if( counter >= image[ 0 ].size() * fill_percent ) {
                x_right = i;
                break;
            }
        }

        CutImageRight ( image, image[0].length () - x_right - 1 );

    }

    // убрать рамку и подобные элементы с изображения
    static void CutGarbageTop( CharImage & image )
    {
        if( image.empty () ) {
            return;
        }

        int width = image[ 0 ].length ();
        int height = image.size();

        int cut_index = -1;
        int numeric_counter = 0;
        int repeat_counter = 0;

        // просмотреть верхнюю треть изображения в поисках лишних элментов
        // 1. ищем пустые столбцы - сверху от них скорее всего мусор
        // 2. ищем столбцы, заполненные менее чем на 10 по сумме элементов
        const int numeric_limit = 6;
        const int repeat_limit = 6;
        // и считаем их количество (подряд идущих)

        for ( int row = 0; row < height / 3; ++row )
        {
            numeric_counter = 0;
            for ( int col = 0; col < width; ++col )
            {
                int value = ImagePixelToInt( image[ row ][ col ] );
                if( value >= 2 && ( col <= 1 || col >= width - 2 ) ) {
                    numeric_counter += value;
                }
                else if( value >= 2 ) {
                    numeric_counter = numeric_limit + 1;
                    continue;
                }
            }

            if( numeric_counter == 0 ) {
                cut_index = row;
            }
            else if( numeric_counter <= numeric_limit  )
            {
                ++repeat_counter;
                if( repeat_counter >= repeat_limit ) {
                    cut_index = row;
                }
            }
            else {
                repeat_counter = 0;
            }
        }

        if ( cut_index != -1 ) {
            CutImageTop ( image, cut_index );
        }
    }

    // убрать рамку и подобные элементы с изображения
    static void CutGarbageBottom( CharImage & image )
    {
        if( image.empty () ) {
            return;
        }

        int width = image[ 0 ].length ();
        int height = image.size();

        int cut_index = -1;
        int numeric_counter = 0;
        int repeat_counter = 0;

        // просмотреть верхнюю треть изображения в поисках лишних элментов
        // 1. ищем пустые столбцы - сверху от них скорее всего мусор
        // 2. ищем столбцы, заполненные менее чем на 10 по сумме элементов
        const int numeric_limit = 6;
        const int repeat_limit = 4;
        // и считаем их количество (подряд идущих)

        for ( int row = height - 1; row > height / 2; --row )
        {
            numeric_counter = 0;
            for ( int col = 0; col < width; col++ )
            {
                int value = ImagePixelToInt( image[ row ][ col ] );
                if( value >= 2 && ( col <= 1 || col >= width - 2 ) ) {
                    numeric_counter += value;
                }
                else if( value >= 2 ) {
                    numeric_counter = numeric_limit + 1;
                    continue;
                }
            }

            if( numeric_counter == 0 ) {
                cut_index = row;
            }
            else if( numeric_counter <= numeric_limit  )
            {
                ++repeat_counter;
                if( repeat_counter >= repeat_limit ) {
                    cut_index = row;
                }
            }
            else {
                repeat_counter = 0;
            }

        }

        if ( cut_index != -1 ) {
            CutImageBottom ( image, height - cut_index - 1 );
        }

    }

    // убрать рамку и подобные элементы с изображения
    static void CutGarbageLeft( CharImage & image )
    {
        if( image.empty () ) {
            return;
        }

        int width = image[ 0 ].length ();
        int height = image.size();

        int cut_index = -1;
        int numeric_counter = 0;
        int repeat_counter = 0;

        const int numeric_limit = 6;
        const int repeat_limit = 6;

        for ( int col = 0; col < width / 2; ++col )
        {
            numeric_counter = 0;
            for ( int row = 0; row < height; ++row )
            {
                int value = ImagePixelToInt( image[ row ][ col ] );
                if( value >= 2 && ( row >= height - 2 || row <= 1 ) ) {
                    numeric_counter += value;
                }
                else if( value >= 2 ) {
                    numeric_counter = numeric_limit + 1;
                    continue;
                }
            }

            if( numeric_counter == 0 ) {
                cut_index = col;
            }
            else if( numeric_counter <= numeric_limit  )
            {
                ++repeat_counter;
                if( repeat_counter >= repeat_limit ) {
                    cut_index = col;
                }
            }
            else {
                repeat_counter = 0;
            }
        }

        if ( cut_index != -1 ) {
            CutImageLeft ( image, cut_index + 1 );
        }
    }

    // убрать рамку и подобные элементы с изображения
    static void CutGarbageRight( CharImage & image )
    {
        if( image.empty () ) {
            return;
        }

        int width = image[ 0 ].length ();
        int height = image.size();

        int cut_index = -1;
        int numeric_counter = 0;
        int repeat_counter = 0;

        const int numeric_limit = 6;
        const int repeat_limit = 6;

        for ( int col = width - 1; col >= width / 2; --col )
        {
            numeric_counter = 0;
            for ( int row = 0; row < height; ++row )
            {              
                int value = ImagePixelToInt( image[ row ][ col ] );
                if( value >= 2 && ( row >= height - 2 || row <= 1 ) ) {
                    numeric_counter += value;
                }
                else if( value >= 2 ) {
                    numeric_counter = numeric_limit + 1;
                    continue;
                }
            }

            if( numeric_counter == 0 ) {
                cut_index = col;
            }
            else if( numeric_counter <= numeric_limit  )
            {
                ++repeat_counter;
                if( repeat_counter >= repeat_limit ) {
                    cut_index = col;
                }
            }
            else {
                repeat_counter = 0;
            }
        }

        if ( cut_index != -1 ) {
            CutImageRight ( image, width - cut_index );
        }
    }


    // убрать рамку и подобные элементы с изображения
    static void CutGarbage( CharImage & image )
    {
        if( image.empty () ) {
            return;
        }

//        CutBorderTop ( image );
//        CutBorderBottom ( image );
        CutGarbageLeft ( image );
        CutGarbageRight ( image );
    }


    // разобрать на отдельные символы
    static void ParseFor3Parts( const CharImage & inputStrings
        , CharImage & digit1, CharImage & digit2, CharImage & digit3 )
    {
        if( inputStrings.empty () ) {
            return;
        }

        // определить размеры изображений
        int length = inputStrings[ 0 ].length () / 3;

        digit1.resize ( inputStrings.size () );
        digit2.resize ( inputStrings.size () );
        digit3.resize ( inputStrings.size () );

        // заполнить данными
        for (  int  j = 0; j < inputStrings.size (); ++j)
        {
            digit1[ j ].resize ( length );
            digit2[ j ].resize ( length );
            digit3[ j ].resize ( length );
            for (  int  i = 0; i < length; ++i)
            {
                digit1[ j ][ i ] = inputStrings[ j ][ i ];
                digit2[ j ][ i ] = inputStrings[ j ][ i + length ];
                digit3[ j ][ i ] = inputStrings[ j ][ i + length * 2 ];
            }
        }
    }

    // изменить размер образа для последующего сравнения с шаблоном
    // метод сжатия - среднее по группе точек
    static void ResizeImage( const CharImage & originalImage, int newWidth, int newHeight, DataArray & vectors )
    {
        if( originalImage.empty () ) {
            return;
        }

        int originalWidth = originalImage[ 0 ].length ();
        int originalHeight = originalImage.size ();

        double summary_coefficient = 0.0;

        for( int row = 0; row < originalHeight; ++row )
        {
            for( int col = 0; col < originalWidth; ++col )
            {
                summary_coefficient += ImagePixelToInt( originalImage[ row ][ col ] );
            }
        }

        summary_coefficient /= 3.0 * originalHeight * originalWidth;

        // каждой точке результирующего массива ставим в соответствие
        // блок точек исходного изображения
        double block_width = static_cast< double > ( originalWidth ) / newWidth;
        double block_height = static_cast< double > ( originalHeight ) / newHeight;

        vectors.resize ( newHeight );
        for( int row = 0; row < newHeight; ++row )
        {
            vectors[ row ].resize ( newWidth );
            for( int col = 0; col < newWidth; ++col )
            {
                int result_code = 0;
                for ( int block_row = 0; block_row < block_height; ++block_row )
                {
                    for ( int block_col = 0; block_col < block_width; ++block_col )
                    {
                        char ch = '.';
                        if( row * block_height + block_row < originalImage.size()
                            && col * block_width + block_col < originalImage [ 0 ].length() ) {
                            ch = originalImage[ row * block_height + block_row ][ col * block_width + block_col ];
                        }
                        result_code += ImagePixelToInt( ch );
                    }
                }
                // вычислить среднее по всему блоку
                double result_coefficient = static_cast< double >( result_code )
                    / ( block_height * block_width * 3.0 );

                if( result_coefficient >= summary_coefficient )
                {
                    vectors[ row ][ col ] = 3.0;
                }
                else if ( result_coefficient >= summary_coefficient / 2.0 )
                {
                    vectors[ row ][ col ] = 1.5;
                }
                else
                {
                    vectors[ row ][ col ] = 0.0;
                }
            }
        }
    }

    // распознать все цифры
    static string RecognizeAllSymbolImages( const CharImage * const digits, const int count, const string controlValue )
    {
        // эталоны цифр для сравнения
        static const Patterns large_patterns;

        string result = "";
        for ( int i = 0; i < count; ++i )
        {
            DataArray resized;
            ResizeImage( digits[ i ], 16, 16, resized );
            
            int symbol = RecognizeSymbol( resized, large_patterns );
            result += DigitToStr( symbol );

            if( controlValue[ i ] != DigitToStr( symbol )[0] )
            {
                cerr << "\n\tresized:\n" << endl;
                PrintArrayBraced ( resized, cerr );
                RecognizeSymbol( resized, large_patterns, true );
            }
        }
        return result;
    }

    // распознать один символ
    static int RecognizeSymbol( const DataArray & image, const Patterns & patterns, bool debugOutput = false )
    {
        if( image.empty () ) {
            return 0;
        }
        
        
        double divisor = patterns.width * patterns.height * 3.0;
        double max_percent = 0.0;
        int max_index = 0;

        // пройти по каждому шаблону и найти минимальный по количеству НЕсовпадений
        for ( int i = 0; i < patterns.count; ++i )
        {
            double distance = FindDistance ( image, patterns.digits[ i ] );

            double percent = 1.0 - ( static_cast< double >( distance) ) / divisor;

            if( percent > max_percent)
            {
                max_percent = percent;
                max_index = i;
            }

            if( debugOutput ) {
                cerr << "pattern " << i << " distance = " << distance << ",\tr = " << percent / 10000 * 10000 << endl;
            }
        }

        if( debugOutput ) {
            cerr << "max = " << max_percent << ", digit is " << max_index << endl << endl;
        }

        return max_index;
    }

    // составить "матрицу несоответствия"
    static void FindDifference( const DataArray & image, const DataArray & pattern, DataArray & difference )
    {
        if( image.empty () ) {
            return;
        }

        int width = image.size ();
        int height = image[ 0 ].size ();

        // изображение должно совпадать по размеру с эталоном
        if ( ! width || !height || pattern.size() != height || pattern[ 0 ].size () != width ) {
            return ;
        }

        difference.resize ( height );
        for ( int row = 0; row < height; ++row )
        {
            difference[ row ].resize ( width );
            for( int col = 0; col < width; ++col )
            {
                difference[ row ][ col ] = image[ row ][ col ] - pattern[ row ][ col ];
                if( difference[ row ][ col ] < 0 ) {
                    difference[ row ][ col ] = -difference[ row ][ col ];
                }
            }
        }
    }

    // найти количество несовпадений
    static double FindDistance( const DataArray & image, const DataArray & pattern )
    {
        if( image.empty () ) {
            cerr << "FindDistance: no image!" << endl;
            return ( 99999.0 );
        }

        int height = image.size ();
        int width = image[ 0 ].size ();

        // изображение должно совпадать по размеру с эталоном
        if ( ! width || !height || pattern.size() != height || pattern[ 0 ].size () != width ) {
            cerr << "FindDistance: image and pattern sizes mismatch" << endl;
            return ( 99997.0 );
        }

        double result = 0.0;
        for ( int row = 0; row < height; ++row )
        {
            for( int col = 0; col < width; ++col )
            {
                double difference = image[ row ][ col ] - pattern[ row ][ col ];
                if( difference < 0.0 ) {
                    difference = -difference;
                }

                result += difference;
            }
        }

        return result;
    }
    
};

// прочитать картинку
void ReadStream( CharImage * inputStrings, std::istream & stream )
{
    if( !inputStrings ) {
        cerr << "ReadStream: bad arguments" << endl;
        return;
    }

    std::string line = "";

    while( !stream.eof() )
    {
        std::getline( stream, line );
        if( line.empty () ) {
            return;
        }
        inputStrings->push_back ( line );        
    }
}


string RecognizeDigitsFromFile( const string & fileName, const string & controlValue = "" )
{
    CharImage inputStrings;
    std::ifstream file ( fileName.c_str () );
    ReadStream( &inputStrings, file );
    file.close ();
    return Recognition::Recognize ( inputStrings, controlValue );
}

/*
 * 
 */
int main ( int argc, char** argv )
{
    CharImage inputStrings;

    /*
    RecognizeDigitsFromFile( "001", "979" );
    RecognizeDigitsFromFile( "002", "484" );
    RecognizeDigitsFromFile( "003", "552" );
    RecognizeDigitsFromFile( "004", "723" );
    RecognizeDigitsFromFile( "005", "576" );
    RecognizeDigitsFromFile( "006", "294" );
    RecognizeDigitsFromFile( "007", "551" );
    RecognizeDigitsFromFile( "008", "853" );
    RecognizeDigitsFromFile( "009", "117" );
    RecognizeDigitsFromFile( "010", "650" );
    RecognizeDigitsFromFile( "011", "864" );
    RecognizeDigitsFromFile( "012", "448" );
    RecognizeDigitsFromFile( "013", "966" );
    RecognizeDigitsFromFile( "014", "247" );
    RecognizeDigitsFromFile( "015", "959" );
    RecognizeDigitsFromFile( "016", "858" );
    RecognizeDigitsFromFile( "017", "892" );
    RecognizeDigitsFromFile( "018", "852" );

    return 0;
    //*/
    
    // получить входные данные
    ReadStream( &inputStrings, cin );

    // распознать
    cout << Recognition::Recognize ( inputStrings ) << endl;

    return 0;
}