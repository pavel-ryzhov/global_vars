#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_HEIGHT  50
#define WIDTH       40
#define NUMBERS_COUNT 3
#define COLOR_0     '.'
#define COLOR_1     '%'
#define COLOR_2     '#'
#define COLOR_3     '@'
#define COLORS_COUNT 4

const char samples [10][MAX_HEIGHT][WIDTH + 1] =
{
  { // 0
    "%%####@@@@@@@@@@@@@@@@@@@@@@@@@@@@####%%",
    "%##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##%",
    "##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##",
    "#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#",
    "#@@@@@@@@#######################@@@@@@@#",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "@@@@@@@@##%%.................%%##@@@@@@@",
    "#@@@@@@@@##%%%.............%%##@@@@@@@@#",
    "##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##",
    "%##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##%",
    "%%####@@@@@@@@@@@@@@@@@@@@@@@@@@@@####%%"
  },
  { // 1
    ".....................%%@@@#.............",
    ".....................%@@@@#.............",
    "........%%%%%@@@@@@@@@@@@@#.............",
    "%%%%%%##@@@@@@@@@@@@@@@@@##.............",
    "%%#@@@@@@@@@@@@@@@@@@@@@@##.............",
    ".............%%##@@@@@@@@##.............",
    ".............%%##@@@@@@@@##.............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    ".............%%##@@@@@@@##%%............",
    "...........%%%%##@@@@@@@##%%%%..........",
    "......%%%@@@@@@@@@@@@@@@@@@@@@@@@%%%....",
    "....##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##..",
    "######@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@####"
  },
  { // 2
    ".............%%%@@@@@@@@@@@@%%%%%.......",
    "..........%%##@@@@@@@@@@@@@@@@@%%%......",
    "........%%##@@@@@@@@@@@@@@@@@@@@@%%.....",
    ".....%%%##@@@@@@@@@@@@@@@@@@@@@@@@%%%...",
    "...%%%%##@@@@@@@@@@@@@@@@@@@@@@@@@@%%...",
    ".%%%%##@@@@@@@@@@%%%%%%%%%@@@@@@@@@@%%..",
    "%%%%%##@@@@@@@%%............@@@@@@@@#%..",
    "%%%%##@@@@@@%%................@@@@@@@@##",
    "%%%#@@@@@%%....................@@@@@@@@#",
    "%%#@@@@@@%%....................@@@@@@@@@",
    "%%@@@@@@%%.......................@@@@@@@",
    "%%@@@@@@%%.......................@@@@@@@",
    "%%@@@@@@%%.......................@@@@@@@",
    "%%@@@@@@%%.......................@@@@@@@",
    "%%@@@@@@%%.......................@@@@@@@",
    ".%%#####%%.......................@@@@@@@",
    ".................................@@@@@@@",
    "...............................@@@@@@@@@",
    "...............................@@@@@@@@@",
    "...............................@@@@@@@@@",
    "..............................@@@@@@@@@#",
    "..............................@@@@@@@@##",
    "..............................@@@@@@@...",
    "............................@@@@@@@@@...",
    "..........................@@@@@@@##%%...",
    "........................@@@@@@@@###%%...",
    "........................@@@@@@@##%%%....",
    ".......................@@@@@@@@##%......",
    ".....................##@@@@@@@###.......",
    ".....................##@@@@@###.........",
    "...................##@@@@@@@##%%........",
    ".................##@@@@@@@@#%%..........",
    "................#@@@@@@@@@%%............",
    "..............##@@@@@@@@%%..............",
    "............##@@@@@@@@@%%%..............",
    "..........##@@@@@@@@@%%%%...............",
    ".........##@@@@@@@@@%%%%%...............",
    "........##@@@@@@@@@@@%%%................",
    "......%@@@@@@@@@@@@%%%%.................",
    ".....%%@@@@@@@@@@%%%%...................",
    "...%#@@@@@@@@@@@%%%%....................",
    "..%@@@@@@@@@@@%%%%......................",
    ".%%@@@@@@@@@%%%%........................",
    "%%@@@@@@@@@@%%%%........................",
    "%%@@@@@@@@##############################",
    "%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
  },
  { // 3
    "..............@@@@@@@@@@@@..............",
    "..........@@@@@@@@@@@@@@@@@@@@..........",
    ".........@@@@@@@@@@@@@@@@@@@@@@.........",
    ".......@@@@@@@@@@@@@@@@@@@@@@@@@@.......",
    ".....@@@@@@@@@@@........@@@@@@@@@@@.....",
    ".....@@@@@@@@@@@........@@@@@@@@@@@.....",
    ".....@@@@@@@@@..............@@@@@@@@@...",
    "...@@@@@@@@@..................@@@@@@@...",
    "...@@@@@@@....................@@@@@@@...",
    "...@@@@@@@.....................@@@@@@@@@",
    "..@@@@@@@......................@@@@@@@@@",
    "..@@@@@@@......................@@@@@@@@@",
    ".....@@@@......................@@@@@@@@@",
    "...............................@@@@@@@@@",
    "...............................@@@@@@@@@",
    "...............................@@@@@@@@@",
    "..............................@@@@@@@@@@",
    "..............................@@@@@@@...",
    "............................@@@@@@@@@...",
    "..........................@@@@@@@@@.....",
    "........................@@@@@@@@@@@.....",
    ".................@@@@@@@@@@@@@@@@.......",
    ".................@@@@@@@@@@@@@@.........",
    "................@@@@@@@@@@@@@@@@@@@.....",
    "................@@@@@@@@@@@@@@@@@@@@@...",
    "................@@@@@@@@@@@@@@@@@@@@@...",
    "..........................@@@@@@@@@@@...",
    "............................@@@@@@@@@@@@",
    "..............................@@@@@@@@@@",
    "...............................@@@@@@@@@",
    "...............................@@@@@@@@@",
    ".................................@@@@@@@",
    ".................................@@@@@@@",
    ".................................@@@@@@@",
    ".................................@@@@@@@",
    ".................................@@@@@@@",
    "...@@@@..........................@@@@@@@",
    "@@@@@@@..........................@@@@@@@",
    "@@@@@@@@@........................@@@@@@@",
    "@@@@@@@@@......................@@@@@@@@@",
    "..@@@@@@@......................@@@@@@@@@",
    "..@@@@@@@@....................@@@@@@@@@@",
    "..@@@@@@@@....................@@@@@@@...",
    "...@@@@@@@@@................@@@@@@@@@...",
    ".....@@@@@@@@@@@........@@@@@@@@@@@.....",
    ".....@@@@@@@@@@@........@@@@@@@@@@@.....",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......",
    ".......@@@@@@@@@@@@@@@@@@@@@@@@.........",
    "..........@@@@@@@@@@@@@@@@@@@@..........",
    "..........@@@@@@@@@@@@@@@@@@@@.........."
  },
  { // 4
    "............................@@@##.......",
    "............................@@@##.......",
    "..........................@@@@@##.......",
    "..........................@@@@@##.......",
    "........................#@@@@@@##.......",
    "........................@@@@@@@##.......",
    "........................@@@@@@@##.......",
    "......................##@@@@@@@##.......",
    "...................##@@@@@@@@@@##.......",
    "...................##@@@@@@@@@@##.......",
    ".................##@@###@@@@@@@##.......",
    "................###@@###@@@@@@@##.......",
    "..............#####@@##.@@@@@@@##.......",
    "............%%##@@@@@...@@@@#####.......",
    "..........%%@@@@@@#..#%..#######........",
    "..........%%@@@@@@%%%#%..######.........",
    "..........%%@@@@@@%%%%...%@%%%%.........",
    "..........%%@@@@@@%%%%...%@%%%%.........",
    "..........##@@@@@%%##%.%%@@%%%%.........",
    ".........%@@@@@##.%##.#@@@@%%%%.........",
    ".........%@@@@@%%%#%%#@@@@@%%%%.........",
    ".........%@@@@@%%%#%%#@@@@@%%%%.........",
    "........%@@@@@#..%#..#@@@@@%%%%.........",
    "........%@@@@@%%%#%..#@@@@@%%%%.........",
    "........#@@@@%.##%...#@@@@@%%%%.........",
    "........#@@@@%.##%...#@@@@@%%%%.........",
    "......%%@@@@#.%##....#@@@@@%%%%.........",
    "......##@@@@%%@%%....#@@@@@%%%%.........",
    "......##@@@@%%@%%....#@@@@@%%%%.........",
    ".....%@@@@%%.#%......#@@@@@%%%%.........",
    ".....#@@@#..%#.......#@@@@@%%%%.........",
    "....%@@@@%%%#%.......#@@@@@%%%%.........",
    "....%@@@@%%%#%.......#@@@@@%%%%.........",
    "...%@@@@%%@@%........#@@@@@%%%%.........",
    "...#@@%%%#%%.........#@@@@@%%%%.........",
    "...#@@%%%#%%.........#@@@@@%%%%.........",
    ".%%@@#..#%...........#@@@@@%%%%.........",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "########################@@@@@@@#########",
    "########################@@@@@@@#########",
    "########################@@@@@@@#########",
    "########################@@@@@@@.........",
    "%%%%%%%%%%%%%%%%%%%%%%%%@@@@@@@.........",
    "%%%%%...................@@@@@@@.........",
    "........................@@@@@@@.........",
    "........................@@@@@@@.........",
    "........................@@@@@@@.........",
    "........................@@@@@@@.........",
    "........................@@@@@@@.........",
    "........................@@@@@@@........."
  },
  { // 5
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@...",
    "...@@@@@................................",
    "...@@@@@................................",
    "...@@@@@................................",
    "...@@@@@................................",
    "...@@@@@................................",
    "...@@@@@................................",
    "...@@@@@................................",
    "...@@@@@................................",
    "...@@@@@................................",
    "..@@@@@@@@@@@@@@@@@@@@@@................",
    "..@@@@@@@@@@@@@@@@@@@@@@@@@@@...........",
    "..@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........",
    "..@@@@@@@@@@@@@@@@@@@@@@@@@@@@..........",
    "..@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@......",
    "..@...............@@@@@@@@@@@@@@@@@.....",
    "......................@@@@@@@@@@@@@@@...",
    "..........................@@@@@@@@@@@...",
    "...........................@@@@@@@@@@@@@",
    ".............................@@@@@@@@@@@",
    ".............................@@@@@@@@@@@",
    ".............................@@@@@@@@@@@",
    ".............................@@@@@@@@@@@",
    "..............................@@@@@@@@@@",
    "..............................@@@@@@@@@@",
    "..............................@@@@@@@@@@",
    "..............................@@@@@@@@@@",
    "..............................@@@@@@@@@@",
    "..............................@@@@@@@@@@",
    "..............................@@@@@@@@@@",
    "..............................@@@@@@@@@@",
    ".............................@@@@@@@@@@@",
    ".............................@@@@@@@@...",
    "...........................@@@@@@@@@@...",
    "...........................@@@@@@@@@@...",
    "..........................@@@@@@@@@.....",
    "........................@@@@@@@@@@......",
    "......................@@@@@@@@@@........",
    ".....................@@@@@@@@@..........",
    "..................@@@@@@@@@@@...........",
    "..............@@@@@@@@@@@@..............",
    "..............@@@@@@@@@@@@..............",
    "........@@@@@@@@@@@@@@..................",
    "@@@@@@@@@@@@@@@@@@......................",
    "@@@@@@@@@@@@@@@@@@......................"
  },
  { // 6
    "..............%%%###@@@@@@@@@#####%%%%..",
    "..............%%%###@@@@@@@@@#####%%%%..",
    "..............%%%###@@@@@@@@@@#######...",
    "...........%%%@@@@@@@@@..........#####..",
    ".........%%%##@@@@@@@@@.............###.",
    "......%%%@@@@@.......................##.",
    "......%%%@@@@@..........................",
    ".....%%%%@@@@@..........................",
    ".....%@@@@@.............................",
    "..%%##@@@@@.............................",
    "..%%##@@@@@.............................",
    ".%%%###@@@..............................",
    "%#####@@@...............................",
    ".##@@@@@@...............................",
    ".##@@@@@@...............................",
    ".##@@@@@@...............................",
    ".##@@@..................................",
    ".##@@@..................................",
    "@@@@@@.....@@@@@@@@@@@@@@@@@@...........",
    "@@@@@@.....@@@@@@@@@@@@@@@@@@...........",
    "@@@@@@.....@@@@@@@@@@@@@@@@@@...........",
    "@@@@@@...@@%%%%%%%........@@@@@@@@......",
    "@@@@@@.##@@%%%%...........@@@@@@@@......",
    "@@@@@@###@@...............@@@@@@@@......",
    "@@@@@@@@@......................@@@@@@@@@",
    "@@@@@@@@@......................@@@@@@@@@",
    "@@@@@@.........................@@@@@@@@@",
    "@@@@@@.........................@@@@@@@@@",
    "@@@@@@.........................@@@@@@@@@",
    "@@@@@@............................@@@@@@",
    "@@@@@@............................@@@@@@",
    "@@@@@@............................@@@@@@",
    "@@@@@@............................@@@@@@",
    "@@@@@@............................@@@@@@",
    "@@@@@@............................@@@@@@",
    "@@@@@@............................@@@@@@",
    "@@@@@@............................@@@@@@",
    "##@@@@............................@@@@@@",
    "###@@@............................@@@@@@",
    ".##@@@@@@......................##@@@@@@@",
    ".##@@@@@@......................##@@@@@@@",
    "...##@@@@......................##@@@@@@@",
    "....##@@@......................##@@@@@@@",
    ".....#@@@@@##................##@@@@@@@@@",
    ".....#@@@#####..............###@@@@@@@@@",
    ".......##@@@@@.............%@@@@@###....",
    "........#@@@@@............@@@@#####.....",
    "........###@@@@@@@@@@@@@@@@@@@@###......",
    ".........###@@@@@@@@@@@@@@@@@@@###......",
    ".........###@@@@@@@@@@@@@@@@@@@###......"
  },
  { // 7
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "................................@@@@@@@@",
    "................................@@@@@@@@",
    ".............................@@@@@@.....",
    ".............................@@@@@@.....",
    "...........................@@@@@@@@.....",
    "...........................@@@@@@@@.....",
    "........................@@@@@@@@........",
    "........................@@@@@@@@........",
    ".....................@@@@@@@@...........",
    ".....................@@@@@@@@...........",
    ".....................@@@@@@@@...........",
    ".....................@@@@@@@@...........",
    ".....................@@@@@@@@...........",
    "...................@@@@@@@@.............",
    "...................@@@@@@@@.............",
    "...................@@@@@@@@.............",
    "...................@@@@@@@@.............",
    "................@@@@@@@@................",
    "................@@@@@@@@................",
    "................@@@@@@@@................",
    "................@@@@@@@@................",
    ".............@@@@@@@@...................",
    ".............@@@@@@@@...................",
    ".............@@@@@@@@...................",
    ".............@@@@@@@@...................",
    ".............@@@@@@@@...................",
    "...........@@@@@@@@.....................",
    "...........@@@@@@@@.....................",
    "...........@@@@@@@@.....................",
    "...........@@@@@@@@.....................",
    "...........@@@@@@@@.....................",
    "...........@@@@@@@@.....................",
    "...........@@@@@@@@.....................",
    "...........@@@@@@@@.....................",
    "........@@@@@@@@........................",
    "........@@@@@@@@........................",
    "........@@@@@@@@........................",
    "........@@@@@@@@........................",
    "........@@@@@@@@........................",
    "........@@@@@@@@........................",
    "........@@@@@@@@........................",
    "........@@@@@@@@........................",
    "........@@@@@@@@........................"
  },
  {
    ".............%%%@@@@@@@@@@@##...........",
    ".............%%%@@@@@@@@@@@##...........",
    ".........%%@@@@@%%......%%%@@@@##.......",
    ".........%%@@@@@%%......%%%@@@@##.......",
    ".......%%@@##................%%@@@@@%%%%",
    ".......%%@@##................%%@@@@@%%%%",
    ".......%%@@##................%%@@@@@%%%%",
    "....%%%@@##....................##@@@%%%%",
    "....%%%@@##....................##@@@%%%%",
    "....###@@%%....................%%@@@####",
    "....###@@%%....................%%@@@####",
    "..%%@@@@@%%....................%%@@@####",
    "..%%@@@@@%%....................%%@@@####",
    "..%%@@@@@##....................##@@@%%%%",
    "..%%@@@@@##....................##@@@%%%%",
    "..%%@@@@@@@%%................%%@@###....",
    "..%%@@@@@@@%%................%%@@###....",
    "....###@@@@@@@@@%%...........##@@%%%....",
    "....###@@@@@@@@@%%...........##@@%%%....",
    "....###@@@@@@@@@%%...........##@@%%%....",
    "....%%%@@@@@@@@@@@@@##..%%%@@##.........",
    "....%%%@@@@@@@@@@@@@##..%%%@@##.........",
    ".........##@@@@@@@@@@@@@@@@%%...........",
    ".........##@@@@@@@@@@@@@@@@%%...........",
    "...........%%@@@@@@@@@@@@@@@@@@%%.......",
    "...........%%@@@@@@@@@@@@@@@@@@%%.......",
    ".........%%@@@@@%%%%@@@@@@@@@@@@@###....",
    ".........%%@@@@@%%%%@@@@@@@@@@@@@###....",
    ".......%%@@##...........%%%@@@@@@@@@####",
    ".......%%@@##...........%%%@@@@@@@@@####",
    "....###@@##..................##@@@@@@@@@",
    "....###@@##..................##@@@@@@@@@",
    "....###@@##..................##@@@@@@@@@",
    "..%%@@@@@%%..................%%@@@@@@@@@",
    "..%%@@@@@%%..................%%@@@@@@@@@",
    "..##@@@##......................##@@@@@@@",
    "..##@@@##......................##@@@@@@@",
    "%%@@@@@%%......................%%@@@@@@@",
    "%%@@@@@%%......................%%@@@@@@@",
    "..##@@@##......................##@@@@@@@",
    "..##@@@##......................##@@@@@@@",
    "..%%@@@@@%%..................%%@@@@@%%%%",
    "..%%@@@@@%%..................%%@@@@@%%%%",
    "....###@@##..................##@@%%%....",
    "....###@@##..................##@@%%%....",
    "....###@@##..................##@@%%%....",
    ".......%%@@@@%%%........%%%@@@@%%.......",
    ".......%%@@@@%%%........%%%@@@@%%.......",
    ".......%%@@@@%%%@@@@@@@@%%%@@@@%%.......",
    ".......%%@@@@%%%@@@@@@@@%%%@@@@%%......."
  },
  { // 9
    ".............@@@@@@@@@@@@@@@............",
    ".............@@@@@@@@@@@@@@@............",
    "........@@@@@@@@@@@@@@@@@@@@@@..........",
    "........@@@@@@@@@@@@@@@@@@@@@@..........",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.....",
    "...@@@@@@@@@@...............@@@@@@@.....",
    "...@@@@@@@@@@...............@@@@@@@.....",
    "...@@@@@@@....................@@@@@@@@@@",
    "...@@@@@@@....................@@@@@@@@@@",
    "@@@@@@@@.........................@@@@@@@",
    "@@@@@@@@.........................@@@@@@@",
    "@@@@@@@@.........................@@@@@@@",
    "@@@@@@@@.........................@@@@@@@",
    "@@@@@@@@.........................@@@@@@@",
    "@@@@@@@@.........................@@@@@@@",
    "@@@@@@@@.........................@@@@@@@",
    "@@@@@@@@.........................@@@@@@@",
    "@@@@@@@@.........................@@@@@@@",
    "@@@@@@@@.........................@@@@@@@",
    "@@@@@@@@.........................@@@@@@@",
    "@@@@@@@@@@....................@@@@@@@@@@",
    "@@@@@@@@@@....................@@@@@@@@@@",
    "...@@@@@@@@@@...............@@@@@@@@@@@@",
    "...@@@@@@@@@@...............@@@@@@@@@@@@",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    "........@@@@@@@@@@@@@@@@@@@@@@...@@@@@@@",
    "........@@@@@@@@@@@@@@@@@@@@@@...@@@@@@@",
    "..........@@@@@@@@@@@@@@@........@@@@@@@",
    "..........@@@@@@@@@@@@@@@........@@@@@@@",
    "..........@@@@@@@@@@@@@@@........@@@@@@@",
    ".................................@@@@@@@",
    ".................................@@@@@@@",
    "..............................@@@@@@@@@@",
    "..............................@@@@@@@@@@",
    "@@@@@@@@......................@@@@@@@@@@",
    "@@@@@@@@......................@@@@@@@@@@",
    "@@@@@@@@@@..................@@@@@@@@@@@@",
    "@@@@@@@@@@..................@@@@@@@@@@@@",
    "...@@@@@@@@@@............@@@@@@@@@@.....",
    "...@@@@@@@@@@............@@@@@@@@@@.....",
    "...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......",
    "...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......",
    "...@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.......",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@..........",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@..........",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@..........",
    ".....@@@@@@@@@@@@@@@@@@@@@@@@@.........."
  }
};

struct image
{
  char **i;
  int w;
  int h;

  ~image ()
  {
    for (int j = 0; j < w; j++)
      delete [] i[j];
    delete [] i;
  }
};

static inline bool true_color (char c)
{
  return (c >= 0) && (c <= 3);
}

static inline char get_color (char c)
{
  if      (c == COLOR_0)
    return 0;
  else if (c == COLOR_3)
    return 3;
  else if (c == COLOR_2)
    return 2;
  else if (c == COLOR_1)
    return 1;
  else
    return 'e'; // error
}

static inline char get_char (char c)
{
  if      (c == 0)
    return COLOR_0;
  else if (c == 3)
    return COLOR_3;
  else if (c == 2)
    return COLOR_2;
  else if (c == 1)
    return COLOR_1;
  else
    return 'e'; // error
}

void print_image (char **image, int w, int h)
{
  int x, y;

  for (y = 0; y < h; y++)
    {
      fprintf (stderr, "\n\"");
      for (x = 0; x < w; x ++)
        fprintf (stderr, "%c", get_char (image[x][y]));
      fprintf (stderr, "\",");
    }
}

void read_image (char **&image, int &w, int &h)
{
  int x, y, y_last_not_white_line = 0;
  int l, r;   // left and right borders of image
  char c = getc (stdin);
  bool image_begins = false;
  bool white_line;

  for (x = 0; get_color (c) == 0; c = getc (stdin), x++) ;
  w = x;
  h = 0;
  c = getc (stdin); // \n

  image = new char *[w];
  for (x = 0; x < w; x++)
    image[x] = new char [MAX_HEIGHT];

  l = w;
  r = 0;

  for (y = 0; (y < MAX_HEIGHT); y++)
    {
      white_line = true;
      for (x = 0; x < w; x++)
        {
          c = getc (stdin);
          c = get_color (c);
          image[x][y] = c;

          if ((c >= 1) && (c <= 3)) // not white
            {
              if (!image_begins)
                image_begins = true;
              if (white_line)
                white_line = false;
              if (x < l)
                l = x;
              if (x > r)
                r = x;
            }
        }
      c = getc (stdin); // \n
      c = getc (stdin); // \t
      if (!image_begins)
        y--;
      if (!white_line)
        y_last_not_white_line = y;
      if (feof (stdin))
        break;
    }

  h = y_last_not_white_line + 1;
  w = r - l + 1;

  for (y = 0; y < h; y++)
    for (x = 0; x < w; x++)
      image[x][y] = image[x + l][y];
}

void scan_digit (char **image, int l, int r, int h_image, struct image &digit)
{
  if (r < l)
    return;
  int x, y, y_digit, y_last_not_white_line = 0;
  bool image_begins = false;
  bool white_line;
  char c;

  digit.w = r - l + 1;

  digit.i = new char *[digit.w];
  for (x = 0; x < digit.w; x++)
    digit.i[x] = new char [h_image];

  for (y = 0, y_digit = 0; y < h_image; y++, y_digit++)
    {
      white_line = true;
      for (x = l; x <= r; x++)
        {
          c = digit.i[x - l][y_digit] = image[x][y];

          if ((c >= 1) && (c <= 3)) // not white
            {
              if (!image_begins)
                image_begins = true;
              if (white_line)
                white_line = false;
            }
        }
      if (!image_begins)
        y_digit--;
      if (!white_line)
        y_last_not_white_line = y_digit;
    }

  digit.h = y_last_not_white_line + 1;
}

int participate (int *line, int w)
{
  int index = 1;

  for (int x = 2; x < w - 1; x++)
    if (line[x] < line[index])
      index = x;

  if (line[index - 1] < line[index + 1])
     index--;

  line[index] = line[index + 1] = COLOR_3 * MAX_HEIGHT;
  return index;
}

int scale_dist (int c, double s)
{
  return (int) (floor (c * s + 0.5));
}

void scale (image &digit, int new_w, int new_h)
{
  int x, y, i;
  int b, b1, b2;
  image new_d;
  double scale_x = (double) new_w / digit.w;
  double scale_y = (double) new_h / digit.h;

    // by x
  new_d.w = new_w;
  new_d.h = digit.h;

  new_d.i = new char *[new_d.w];
  for (x = 0; x < new_d.w; x++)
    new_d.i[x] = new char [new_d.h];

  for (y = 0; y < digit.h; y++)
    {
      b = 0;
      for (x = 1; x < digit.w; x++)
        {
          if ((digit.i[x - 1][y] != digit.i[x][y]) || (x == digit.w - 1))
            {
          /*    if ((x == digit.w - 1) && (digit.i[x - 1][y] != digit.i[x][y]))
                {
                  b1 = scale_dist (x - 1, scale_x);
                  b2 = scale_dist (x, scale_x);
                  for (i = b1; i < b2; i++)
                    new_d.i[i][y] = digit.i[x][y];
                }
              else*/
                {
                  b1 = scale_dist (b, scale_x);
                  b2 = scale_dist (x, scale_x);
                  if (x == digit.w - 1)
                    b2 = new_w;
                  for (i = b1; i < b2; i++)
                    new_d.i[i][y] = digit.i[x - 1][y];
                  b = x;
                }
            }
        }
    }

    // by y
  digit = new_d;
  digit.h = new_h;

  digit.i = new char *[digit.w];
  for (x = 0; x < digit.w; x++)
    digit.i[x] = new char [digit.h];

  for (x = 0; x < new_d.w; x++)
    {
      b = 0;
      for (y = 1; y < new_d.h; y++)
        {
          if ((new_d.i[x][y - 1] != new_d.i[x][y]) || (y == new_d.h - 1))
            {
            /*  if ((y == new_d.h - 1) && (new_d.i[x][y - 1] != new_d.i[x][y]))
                {
                  b1 = scale_dist (y - 1, scale_y);
                  b2 = scale_dist (y, scale_y);
                  for (i = b1; i < b2; i++)
                    digit.i[x][i] = new_d.i[x][y - 1];
                }
              else*/
                {
                  b1 = scale_dist (b, scale_y);
                  b2 = scale_dist (y, scale_y);
                  if (y == new_d.h - 1)
                    b2 = new_h;
                  for (i = b1; i < b2; i++)
                    digit.i[x][i] = new_d.i[x][y - 1];
                  b = y;
                }
            }
        }
    }
}

static inline int diff (char a, char b)
{
  return (a >= b) ? (a - b) : (b - a);
}

int compare (struct image *d, int k)
{
  int x, y, r = 0;

  for (y = 0; y < d->h; y++)
    {
      for (x = 0; x < d->w; x++)
        r += diff (d->i[x][y], get_color (samples[k][y][x]));
    }
  return r;
}

int recognize (struct image *d)
{
  int min_diff = WIDTH * MAX_HEIGHT * COLORS_COUNT;
  int curr_diff;
  int r = 0;

  for (int i = 0; i <= 9; i++)
    {
      curr_diff = compare (d, i);
      if (curr_diff < min_diff)
        {
          min_diff = curr_diff;
          r = i;
        }
    }

  return r;
}

int participate_to_digits (char **image, int w, int h)
{
  int x, y;
  int l, r;
  int *line = new int[w];

  struct image digits[NUMBERS_COUNT];
  int l_borders[NUMBERS_COUNT];
  int r_borders[NUMBERS_COUNT];
  int current_digit_number = 0;

  for (x = 0; x < w; x++)
    {
      line[x] = 0;
      for (y = 0; y < h; y++)
        line[x] += image[x][y];
    }

  l = 0;
  r = w - 1;
  for (x = 1; x < w; x++)
    {
      if ((line[x - 1] && !line[x]) || (x == w - 1))
      {
        if (x != w - 1)
          r = x - 1;
        else
          r = x;
        l_borders[current_digit_number] = l;
        r_borders[current_digit_number] = r;

        current_digit_number++;
        if (current_digit_number == NUMBERS_COUNT)
          break;
      }
      else if (!line[x - 1] && line[x])
        l = x;
    }

  if (current_digit_number == 1)
    {
      int b1, b2;
      int w1, w2, w3;

      b1 = participate (line, w);
      b2 = participate (line, w);

      if (b1 > b2)
        {
          int t = b2;
          b2 = b1;
          b1 = t;
        }

      w1 = b1 + 1;
      w2 = b2 - b1 + 1;
      w3 = w - b2 - 1;

      if (w1 > w2 + w3)
        {
          for (int i = b1; i < w - 1; i++)
            line[i] = COLOR_3 * MAX_HEIGHT;
          b2 = b1;
          b1 = participate (line, w);
        }

      if (w3 > w2 + w1)
        {
          for (int i = 0; i < b2 + w3 / 3; i++)
            line[i] = COLOR_3 * MAX_HEIGHT;
          b1 = b2;

          for (int i = w - w3 / 3; i < w - 1; i++)
            line[i] *= 2;

          b2 = participate (line, w);
        }

      l_borders[0] = 0;
      r_borders[0] = b1;
      l_borders[1] = b1 + 1;
      r_borders[1] = b2;
      l_borders[2] = b2 + 1;
      r_borders[2] = w - 1;
    }
  else if (current_digit_number == 2)
    {
      int b1, b2;
      int w1, w2, w3;

      for (int i = r_borders[0]; i < l_borders[1]; i++)
        line[i] = COLOR_3 * MAX_HEIGHT;

      b1 = r_borders[0];
      b2 = participate (line, w);

      if (b1 > b2)
        {
          int t = b2;
          b2 = b1;
          b1 = t;
        }
      else
        b1 = l_borders[1];

      w1 = b1 + 1;
      w2 = b2 - b1 + 1;
      w3 = w - b2 - 1;

      if (w1 > w2 + w3)
        {
          for (int i = b1; i < w - 1; i++)
            line[i] = COLOR_3 * MAX_HEIGHT;
          b2 = b1;
          b1 = participate (line, w);
        }

      if (w3 > w2 + w1)
        {
          for (int i = 0; i < b2 + w3 / 3; i++)
            line[i] = COLOR_3 * MAX_HEIGHT;
          b1 = b2;

          for (int i = w - w3 / 3; i < w - 1; i++)
            line[i] *= 2;

          b2 = participate (line, w);
        }

      l_borders[0] = 0;
      r_borders[0] = b1;
      l_borders[1] = b1 + 1;
      r_borders[1] = b2;
      l_borders[2] = b2 + 1;
      r_borders[2] = w - 1;
    }

  for (int i = 0; i < NUMBERS_COUNT ; i++)
    {
      scan_digit (image, l_borders[i], r_borders[i], h, digits[i]);
      scale (digits[i], WIDTH, MAX_HEIGHT);
   //   print_image (digits[i].i, digits[i].w, digits[i].h);
      printf ("%i", recognize (&digits[i]));
    }

  delete [] line;
  return 0;
}

int main (void)
{
  char **image;      // input matrix
  int w, h; // image sizes

  read_image (image, w, h);
 // print_image (image, w, h);
  participate_to_digits (image, w, h);


  return 0;
}
