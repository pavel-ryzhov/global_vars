#include <iostream>
#include <fstream>

#include <vector>
using std::vector;

#include <string>
using std::string;

struct Picture {
    string Text;
    int Width;
    int Height;

    Picture(): Text(""), Width(0), Height(0) {}
};


void PrintDigit (const vector<string>& digit) {
    string text;
    for (int j = 0; j < digit[0].length(); ++j) {
        for (int  i = 0; i < digit.size(); ++i) {
            text += digit[i][j];
        }
        text += 10;
    }
    std::cout << text << digit.size() << " " << digit[0].length() << std::endl;
}

class Drawn_Number {
private: 
    vector<string> NumberText;
    vector< vector<string> > Digits;

    vector< vector<string> > Etalon;

    string Number;

    void Initialize() {
        vector<string> temp(10);
        Etalon.push_back(temp);
        Etalon.push_back(temp);
        Etalon.push_back(temp);
        Etalon.push_back(temp);

         Etalon[0][0] = "......@@@@@....";
        Etalon[0][0] += "...@@@@@@@@@@..";
        Etalon[0][0] += "..@@@@@...@@@@.";
        Etalon[0][0] += ".@@@@@@.......@";
        Etalon[0][0] += "@@@@@@@.......@";
        Etalon[0][0] += "@@@@@@@.......@";
        Etalon[0][0] += "@@@@@@@.......@";
        Etalon[0][0] += "@@@@@@@.......@";
        Etalon[0][0] += "@@@@@@@.......@";
        Etalon[0][0] += "@@@@@@@.......@";
        Etalon[0][0] += "@@@@@@@.......@";
        Etalon[0][0] += ".@@@@@@.......@";
        Etalon[0][0] += "..@@@@@.....@@.";
        Etalon[0][0] += "...@@@@....@@@.";
        Etalon[0][0] += "......@@@@@....";

         Etalon[0][1] = "......@@@@.....";
        Etalon[0][1] += "....@@@@@@.....";
        Etalon[0][1] += ".......@@@.....";
        Etalon[0][1] += ".......@@@.....";
        Etalon[0][1] += ".......@@@.....";
        Etalon[0][1] += ".......@@@.....";
        Etalon[0][1] += ".......@@@.....";
        Etalon[0][1] += ".......@@@.....";
        Etalon[0][1] += ".......@@@.....";
        Etalon[0][1] += ".......@@@.....";
        Etalon[0][1] += ".......@@@.....";
        Etalon[0][1] += ".......@@@.....";
        Etalon[0][1] += ".......@@@.....";
        Etalon[0][1] += ".......@@@.....";
        Etalon[0][1] += "@@@@@@@@@@@@@@@";

         Etalon[0][2] = "......@@@@@....";
        Etalon[0][2] += "...@@@@@@@@@@..";
        Etalon[0][2] += "..@@@......@@@@";
        Etalon[0][2] += ".@@@@@......@@@";
        Etalon[0][2] += "..@@@........@@";
        Etalon[0][2] += ".............@@";
        Etalon[0][2] += "...........@@@@";
        Etalon[0][2] += "...........@@@.";
        Etalon[0][2] += ".........@@@...";
        Etalon[0][2] += ".......@@@.....";
        Etalon[0][2] += ".....@@@.......";
        Etalon[0][2] += "...@@@.........";
        Etalon[0][2] += ".@@@...........";
        Etalon[0][2] += ".@@@@@@@@@@@@@@";
        Etalon[0][2] += "@@@@@@@@@@@@@@@";

         Etalon[0][3] = ".....@@@@@.....";
        Etalon[0][3] += "...@@@@@@@@@@..";
        Etalon[0][3] += ".@.........@@@.";
        Etalon[0][3] += ".@..........@@@";
        Etalon[0][3] += "..@.........@@@";
        Etalon[0][3] += "...........@@@.";
        Etalon[0][3] += ".........@@@@..";
        Etalon[0][3] += ".......@@@@@@..";
        Etalon[0][3] += ".........@@@@@@";
        Etalon[0][3] += "............@@@";
        Etalon[0][3] += ".............@@";
        Etalon[0][3] += "@@...........@@";
        Etalon[0][3] += ".@@@........@@@";
        Etalon[0][3] += ".@@@@......@@@.";
        Etalon[0][3] += "...@@@@@@@@@...";

         Etalon[0][4] = "...............";
        Etalon[0][4] += "...............";
        Etalon[0][4] += "...............";
        Etalon[0][4] += ".....@@@.@.....";
        Etalon[0][4] += "....@@@.@@@....";
        Etalon[0][4] += "....@@@.@@@....";
        Etalon[0][4] += "...@@@..@@@....";
        Etalon[0][4] += "...@@@..@@@....";
        Etalon[0][4] += "..@@@...@@@....";
        Etalon[0][4] += ".@@@....@@@....";
        Etalon[0][4] += "@@@@@@@@@@@@@@@";
        Etalon[0][4] += "@@@@@@@@@@@@@@@";
        Etalon[0][4] += "........@@@....";
        Etalon[0][4] += "........@@@....";
        Etalon[0][4] += "........@@@....";

          Etalon[0][5] = "..@@@@@@@@@@@..";
        Etalon[0][5] += "..@@@@@@@@@@@..";
        Etalon[0][5] += "..@@@..........";
        Etalon[0][5] += "..@@@..........";
        Etalon[0][5] += "..@@@..........";
        Etalon[0][5] += "..@@@..........";
        Etalon[0][5] += "..@@@@@@@@@@@@.";
        Etalon[0][5] += "..@@@@@@@@@@@@.";
        Etalon[0][5] += "...........@@@.";
        Etalon[0][5] += "...........@@@.";
        Etalon[0][5] += "...........@@@.";
        Etalon[0][5] += "@@.........@@@.";
        Etalon[0][5] += "@@........@@@@.";
        Etalon[0][5] += "@@.......@@@@@.";
        Etalon[0][5] += "..@@@@@@@@@@@..";


         Etalon[0][6] = "......@@@@@@...";
        Etalon[0][6] += "....@@@........";
        Etalon[0][6] += "...@@@.........";
        Etalon[0][6] += "..@@@..........";
        Etalon[0][6] += "..@@@..........";
        Etalon[0][6] += "..@@...........";
        Etalon[0][6] += "..@@@@@@@@@....";
        Etalon[0][6] += "..@@....@@@@...";
        Etalon[0][6] += "..@@@....@@@...";
        Etalon[0][6] += "..@@@....@@@...";
        Etalon[0][6] += "..@@@....@@@...";
        Etalon[0][6] += "..@@@....@@@...";
        Etalon[0][6] += "..@@@@...@@@...";
        Etalon[0][6] += "...@@@...@@@...";
        Etalon[0][6] += "...@@@@@@@@....";

         Etalon[0][7] = ".@@@@@@@@@@@@@.";
        Etalon[0][7] += ".@@@@@@@@@@@@@.";
        Etalon[0][7] += "...........@@..";
        Etalon[0][7] += ".........@@@...";
        Etalon[0][7] += "........@@@....";
        Etalon[0][7] += "........@@@....";
        Etalon[0][7] += ".......@@@.....";
        Etalon[0][7] += "......@@@......";
        Etalon[0][7] += "......@@@......";
        Etalon[0][7] += ".....@@@.......";
        Etalon[0][7] += "....@@@........";
        Etalon[0][7] += "....@@@........";
        Etalon[0][7] += "....@@@........";
        Etalon[0][7] += "...@@@.........";
        Etalon[0][7] += "...@@@.........";
         
         Etalon[0][8] = "..........@....";
        Etalon[0][8] += "...@@@....@@@..";
        Etalon[0][8] += "..@@@......@@@.";
        Etalon[0][8] += ".@@@........@@@";
        Etalon[0][8] += ".@@@........@@@";
        Etalon[0][8] += "..@@@......@@@.";
        Etalon[0][8] += "...@@@.....@@..";
        Etalon[0][8] += "...@@@@@@@@@@..";
        Etalon[0][8] += ".@@@@@@@@@@@@@.";
        Etalon[0][8] += ".@@@........@@.";
        Etalon[0][8] += ".@@@........@@.";
        Etalon[0][8] += ".@@@........@@.";
        Etalon[0][8] += ".@@@........@@.";
        Etalon[0][8] += ".@@@@.......@@.";
        Etalon[0][8] += "...@@@@@@@@....";

        Etalon[0][9] = ".....@@@@@.....";
        Etalon[0][9] += "..@@@@@@@@@@@..";
        Etalon[0][9] += ".@@@@.....@@@..";
        Etalon[0][9] += "@@@.........@@.";
        Etalon[0][9] += "@@@.........@@@";
        Etalon[0][9] += "@@@.........@@@";
        Etalon[0][9] += "@@@.........@@@";
        Etalon[0][9] += ".@@@@.....@@@@@";
        Etalon[0][9] += "..@@@@@@@@@@@@@";
        Etalon[0][9] += "............@@@";
        Etalon[0][9] += "............@@@";
        Etalon[0][9] += "@@@........@@@.";
        Etalon[0][9] += "@@@@......@@@@.";
        Etalon[0][9] += ".@@@.....@@@...";
        Etalon[0][9] += "..@@@@@@@@@....";

         Etalon[1][0] = "......@@@@@....";
        Etalon[1][0] += "...@@@....@@@..";
        Etalon[1][0] += "..@@@......@@@.";
        Etalon[1][0] += ".@@@........@@@";
        Etalon[1][0] += "@@@.........@@@";
        Etalon[1][0] += "@@@.........@@@";
        Etalon[1][0] += "@@@.........@@@";
        Etalon[1][0] += "@@@.........@@@";
        Etalon[1][0] += "@@@.........@@@";
        Etalon[1][0] += "@@@.........@@@";
        Etalon[1][0] += "@@@.........@@@";
        Etalon[1][0] += ".@@@........@@@";
        Etalon[1][0] += "..@@@......@@@.";
        Etalon[1][0] += "...@@@.....@@@.";
        Etalon[1][0] += "......@@@@@....";

         Etalon[1][1] = "......@@@@.....";
        Etalon[1][1] += "....@@@@@@.....";
        Etalon[1][1] += ".......@@@.....";
        Etalon[1][1] += ".......@@@.....";
        Etalon[1][1] += ".......@@@.....";
        Etalon[1][1] += ".......@@@.....";
        Etalon[1][1] += ".......@@@.....";
        Etalon[1][1] += ".......@@@.....";
        Etalon[1][1] += ".......@@@.....";
        Etalon[1][1] += ".......@@@.....";
        Etalon[1][1] += ".......@@@.....";
        Etalon[1][1] += ".......@@@.....";
        Etalon[1][1] += ".......@@@.....";
        Etalon[1][1] += ".......@@@.....";
        Etalon[1][1] += ".......@@@.....";

         Etalon[1][2] = "............@..";
        Etalon[1][2] += ".........@@@@@.";
        Etalon[1][2] += "......@@@@@@@..";
        Etalon[1][2] += "....@@@@..@@...";
        Etalon[1][2] += "...@@@..@@@@...";
        Etalon[1][2] += "...@...@@@@....";
        Etalon[1][2] += "......@@.......";
        Etalon[1][2] += "....@@@@.......";
        Etalon[1][2] += "...@...........";
        Etalon[1][2] += ".@@............";
        Etalon[1][2] += "@@@............";
        Etalon[1][2] += "@@@............";
        Etalon[1][2] += "@@@@@......@@@@";
        Etalon[1][2] += "@@@@@@@@@@@@@@@";
        Etalon[1][2] += "...@@@@@@@@@@@.";

         Etalon[1][3] = "....@@@@@......";
        Etalon[1][3] += "..@@@@@@@@.....";
        Etalon[1][3] += "..@@...@@@@....";
        Etalon[1][3] += "..@....@@@@....";
        Etalon[1][3] += ".......@@@@....";
        Etalon[1][3] += ".......@@@.....";
        Etalon[1][3] += "......@@@......";
        Etalon[1][3] += "....@@@@@@.....";
        Etalon[1][3] += "........@@@@...";
        Etalon[1][3] += "........@@@@...";
        Etalon[1][3] += ".........@@@...";
        Etalon[1][3] += "........@@@....";
        Etalon[1][3] += "........@@@....";
        Etalon[1][3] += "..@@@..@@@.....";
        Etalon[1][3] += "..@@@@@@@......";
        
         Etalon[1][4] = "...............";
        Etalon[1][4] += "...............";
        Etalon[1][4] += "...............";
        Etalon[1][4] += ".....@@@.@.....";
        Etalon[1][4] += "....@@@.@@@....";
        Etalon[1][4] += "....@@@.@@@....";
        Etalon[1][4] += "...@@@..@@@....";
        Etalon[1][4] += "...@@@..@@@....";
        Etalon[1][4] += "..@@@...@@@....";
        Etalon[1][4] += ".@@@....@@@....";
        Etalon[1][4] += "@@@@@@@@@@@@@@@";
        Etalon[1][4] += "@@@@@@@@@@@@@@@";
        Etalon[1][4] += "........@@@....";
        Etalon[1][4] += "........@@@....";
        Etalon[1][4] += "........@@@....";
        
         Etalon[1][5] = "...@@@@@@@@@@@.";
        Etalon[1][5] += "..@@@@@@@@.....";
        Etalon[1][5] += "..@....@.@..@..";
        Etalon[1][5] += ".......@.@..@..";
        Etalon[1][5] += ".......@.@..@..";
        Etalon[1][5] += ".......@.@..@..";
        Etalon[1][5] += ".......@.@..@..";
        Etalon[1][5] += "@@.....@.@..@..";
        Etalon[1][5] += "@@.....@.@..@..";
        Etalon[1][5] += "@@.....@.@..@..";
        Etalon[1][5] += "@......@.@..@..";
        Etalon[1][5] += "@@.....@.@..@..";
        Etalon[1][5] += "@@.....@.@..@..";
        Etalon[1][5] += "@@.....@.@..@..";
        Etalon[1][5] += ".......@.@..@..";

         Etalon[1][6] = "....@@@@@......";
        Etalon[1][6] += "...@@@@@.......";
        Etalon[1][6] += "..@@@@@@.......";
        Etalon[1][6] += "@@@@@@@........";
        Etalon[1][6] += "@@@@@@@........";
        Etalon[1][6] += "@@@@@@@@@@.....";
        Etalon[1][6] += "@@@@@@@@@@@@@@@";
        Etalon[1][6] += "@@@@.....@@@@@@";
        Etalon[1][6] += "@@@........@@@@";
        Etalon[1][6] += "@@@.........@@@";
        Etalon[1][6] += "@@@.........@@@";
        Etalon[1][6] += "@@@@@.......@@@";
        Etalon[1][6] += ".@@@@@@@@@@@@@@";
        Etalon[1][6] += "..@@@@@@@@@@@@.";
        Etalon[1][6] += "....@@@@@@@....";

         Etalon[1][7] = ".@@@@@@@@@@@@@.";
        Etalon[1][7] += ".@@@@@@@@@@@@@.";
        Etalon[1][7] += "...........@@..";
        Etalon[1][7] += ".........@@@...";
        Etalon[1][7] += "........@@@....";
        Etalon[1][7] += "........@@@....";
        Etalon[1][7] += ".......@@@.....";
        Etalon[1][7] += "......@@@......";
        Etalon[1][7] += "......@@@......";
        Etalon[1][7] += ".....@@@.......";
        Etalon[1][7] += "....@@@........";
        Etalon[1][7] += "....@@@........";
        Etalon[1][7] += "....@@@........";
        Etalon[1][7] += "...@@@.........";
        Etalon[1][7] += "...@@@.........";

         Etalon[1][8] = ".........@@@@@.";
        Etalon[1][8] += "....@@..@@@@@@@";
        Etalon[1][8] += "...@@...@@@@@@@";
        Etalon[1][8] += ".@@@@....@@@@@.";
        Etalon[1][8] += "@@@@@@...@@@...";
        Etalon[1][8] += ".@@@@@@@@@@....";
        Etalon[1][8] += "..@@@@@@@@@@...";
        Etalon[1][8] += "....@@@@@@@@@@.";
        Etalon[1][8] += "....@@@@@@@@@@@";
        Etalon[1][8] += "..@@@...@@@@@@@";
        Etalon[1][8] += ".@@@@....@@@@@@";
        Etalon[1][8] += "@@@@@....@@@@..";
        Etalon[1][8] += "@@@@@@..@@@....";
        Etalon[1][8] += "@@@@@@@@@......";
        Etalon[1][8] += ".@@@@@@........";

        Etalon[1][9] = ".....@@@@@.....";
        Etalon[1][9] += "..@@@@@@@@@@@..";
        Etalon[1][9] += ".@@@@.....@@@..";
        Etalon[1][9] += "@@@.........@@.";
        Etalon[1][9] += "@@@.........@@@";
        Etalon[1][9] += "@@@.........@@@";
        Etalon[1][9] += "@@@.........@@@";
        Etalon[1][9] += ".@@@@.....@@@@@";
        Etalon[1][9] += "..@@@@@@@@@@@@@";
        Etalon[1][9] += "....@@@@@...@@@";
        Etalon[1][9] += "............@@@";
        Etalon[1][9] += "@@@........@@@.";
        Etalon[1][9] += "@@@@......@@@@.";
        Etalon[1][9] += ".@@@@@@@@@@@...";
        Etalon[1][9] += "..@@@@@@@@@....";

         Etalon[2][0] = "......@@@@@....";
        Etalon[2][0] += "...@@@@...@@@..";
        Etalon[2][0] += "..@@@.@....@@@.";
        Etalon[2][0] += ".@@@@.@.......@";
        Etalon[2][0] += "@@@...@.......@";
        Etalon[2][0] += "@@@...@.......@";
        Etalon[2][0] += "@@@...@.......@";
        Etalon[2][0] += "@@@...@.......@";
        Etalon[2][0] += "@@@...@.......@";
        Etalon[2][0] += "@@@...@.......@";
        Etalon[2][0] += "@@@...@.......@";
        Etalon[2][0] += ".@@@..@.......@";
        Etalon[2][0] += "..@@@.@.....@@.";
        Etalon[2][0] += "...@@@@....@@@.";
        Etalon[2][0] += "......@@@@@....";

         Etalon[2][1] = "......@@@@.....";
        Etalon[2][1] += "....@@@@@@.....";
        Etalon[2][1] += ".......@@@.....";
        Etalon[2][1] += ".......@@@.....";
        Etalon[2][1] += ".......@@@.....";
        Etalon[2][1] += ".......@@@.....";
        Etalon[2][1] += ".......@@@.....";
        Etalon[2][1] += ".......@@@.....";
        Etalon[2][1] += ".......@@@.....";
        Etalon[2][1] += ".......@@@.....";
        Etalon[2][1] += ".......@@@.....";
        Etalon[2][1] += ".......@@@.....";
        Etalon[2][1] += ".......@@@.....";
        Etalon[2][1] += ".......@@@.....";
        Etalon[2][1] += "@@@@@@@@@@@@@@@";

         Etalon[2][2] = "......@@@@@....";
        Etalon[2][2] += "...@@@@@@@@@@..";
        Etalon[2][2] += "@@@@@@@@@@@@@@@";
        Etalon[2][2] += "............@@@";
        Etalon[2][2] += ".............@@";
        Etalon[2][2] += ".............@@";
        Etalon[2][2] += "...........@@@@";
        Etalon[2][2] += "...........@@@.";
        Etalon[2][2] += ".........@@@...";
        Etalon[2][2] += ".......@@@.....";
        Etalon[2][2] += ".....@@@.......";
        Etalon[2][2] += "...@@@.........";
        Etalon[2][2] += "..@@@@@@@@@@@@@";
        Etalon[2][2] += "@@@@@@......@@@";
        Etalon[2][2] += "@@@@@@@@@@@@@@@";

         Etalon[2][3] = "......@@@@@@@..";
        Etalon[2][3] += "...@@@....@@@@@";
        Etalon[2][3] += "..@@@.....@@@@@";
        Etalon[2][3] += ".@@@......@@@@@";
        Etalon[2][3] += ".@@@......@@@@.";
        Etalon[2][3] += ".@@@@.@@.@@@...";
        Etalon[2][3] += "..@@@@@.@@@....";
        Etalon[2][3] += "......@@..@@@@.";
        Etalon[2][3] += ".....@@....@@@@";
        Etalon[2][3] += "...........@@@@";
        Etalon[2][3] += "...........@@@@";
        Etalon[2][3] += "@@@.......@@@@@";
        Etalon[2][3] += "@@@@......@@@@@";
        Etalon[2][3] += "@@@.....@@@@@..";
        Etalon[2][3] += "@@@@....@@@....";

         Etalon[2][4] = "...............";
        Etalon[2][4] += "...............";
        Etalon[2][4] += "...............";
        Etalon[2][4] += ".....@@@.@.....";
        Etalon[2][4] += "....@@@.@@@....";
        Etalon[2][4] += "....@@@.@@@....";
        Etalon[2][4] += "...@@@..@@@....";
        Etalon[2][4] += "...@@@..@@@....";
        Etalon[2][4] += "..@@@...@@@....";
        Etalon[2][4] += ".@@@....@@@....";
        Etalon[2][4] += "@@@@@@@@@@@@@@@";
        Etalon[2][4] += "@@@@@@@@@@@@@@@";
        Etalon[2][4] += "........@@@....";
        Etalon[2][4] += "........@@@....";
        Etalon[2][4] += "........@@@....";

         Etalon[2][5] = ".....@@@@@@@@..";
        Etalon[2][5] += "....@@@@@@@@@..";
        Etalon[2][5] += "....@@@@.......";
        Etalon[2][5] += "....@@@........";
        Etalon[2][5] += "...@@@@@@@.....";
        Etalon[2][5] += "..@@@@@@@@.....";
        Etalon[2][5] += "...@@..@@@.....";
        Etalon[2][5] += "......@@@......";
        Etalon[2][5] += "......@@.......";
        Etalon[2][5] += ".....@@........";
        Etalon[2][5] += "....@@......@@.";
        Etalon[2][5] += "@@..........@@.";
        Etalon[2][5] += "@@@.........@@.";
        Etalon[2][5] += "@@@........@@..";
        Etalon[2][5] += "...............";

         Etalon[2][6] = "......@@@@@@@..";
        Etalon[2][6] += "....@@@.....@@.";
        Etalon[2][6] += "..@@@@.......@.";
        Etalon[2][6] += "..@@@@.........";
        Etalon[2][6] += ".@@@@@.........";
        Etalon[2][6] += ".@@@@@.........";
        Etalon[2][6] += "@@@@@@@@@@@@...";
        Etalon[2][6] += "@@@@@@...@@@@..";
        Etalon[2][6] += "@@@@@@.....@@@@";
        Etalon[2][6] += "@@@@@@........@";
        Etalon[2][6] += "@@@@@@........@";
        Etalon[2][6] += ".@@@@@........@";
        Etalon[2][6] += "..@@@@.......@@";
        Etalon[2][6] += "..@@@@......@@.";
        Etalon[2][6] += ".....@@@@@@....";

         Etalon[2][7] = "...@@@@@@@@@...";
        Etalon[2][7] += "...@@@@@@@@@...";
        Etalon[2][7] += "..........@@...";
        Etalon[2][7] += ".........@@@...";
        Etalon[2][7] += "........@@@....";
        Etalon[2][7] += "........@@@....";
        Etalon[2][7] += "........@@.....";
        Etalon[2][7] += "........@@.....";
        Etalon[2][7] += "........@@.....";
        Etalon[2][7] += ".......@@@.....";
        Etalon[2][7] += ".......@@......";
        Etalon[2][7] += "......@@@......";
        Etalon[2][7] += "......@@.......";
        Etalon[2][7] += ".....@@@.......";
        Etalon[2][7] += ".....@@@.......";

         Etalon[2][8] = "......@@@@@....";
        Etalon[2][8] += "...@@@@@@@@@@..";
        Etalon[2][8] += ".@@..........@@";
        Etalon[2][8] += ".@@..........@@";
        Etalon[2][8] += ".@@..........@@";
        Etalon[2][8] += ".@@..........@@";
        Etalon[2][8] += "...@@....@@@...";
        Etalon[2][8] += "....@@....@@@..";
        Etalon[2][8] += "..@@@@@@....@@.";
        Etalon[2][8] += ".@@@...@@....@@";
        Etalon[2][8] += "@@.......@@...@";
        Etalon[2][8] += "@@........@@..@";
        Etalon[2][8] += "@@........@@..@";
        Etalon[2][8] += "@@........@@..@";
        Etalon[2][8] += "..@@@@@@@@@@@@@";

        Etalon[2][9] = ".....@@@@@.....";
        Etalon[2][9] += "..@@@@@@@@@@@..";
        Etalon[2][9] += ".@@@@.....@@@..";
        Etalon[2][9] += "@@@.........@@.";
        Etalon[2][9] += "@@@.........@@@";
        Etalon[2][9] += "@@@.........@@@";
        Etalon[2][9] += "@@@.........@@@";
        Etalon[2][9] += ".@@@@.....@@@@@";
        Etalon[2][9] += "..@@@@@@@@@@@@@";
        Etalon[2][9] += "............@@@";
        Etalon[2][9] += "............@@@";
        Etalon[2][9] += "@@@........@@@.";
        Etalon[2][9] += "@@@@......@@@@.";
        Etalon[2][9] += ".@@@.....@@@...";
        Etalon[2][9] += "..@@@@@@@@@....";

         Etalon[3][0] = "......@@@@@....";
         Etalon[3][0] = "......@@@@@....";
        Etalon[3][0] += "...@@@@@@@@@@..";
        Etalon[3][0] += "..@@@@@@@@@@@@@";
        Etalon[3][0] += ".@@@........@@@";
        Etalon[3][0] += ".@@@........@@@";
        Etalon[3][0] += ".@@@........@@@";
        Etalon[3][0] += ".@@@........@@@";
        Etalon[3][0] += ".@@@........@@@";
        Etalon[3][0] += ".@@@........@@@";
        Etalon[3][0] += ".@@@........@@@";
        Etalon[3][0] += ".@@@........@@@";
        Etalon[3][0] += ".@@@........@@@";
        Etalon[3][0] += "..@@@@@@@@@@@@@";
        Etalon[3][0] += "...@@@@@@@@@@..";
        Etalon[3][0] += "......@@@@@....";

         Etalon[3][1] = "...........@@@@";
        Etalon[3][1] += "...........@@@@";
        Etalon[3][1] += "...........@@@@";
        Etalon[3][1] += "...........@@@@";
        Etalon[3][1] += "...........@@@@";
        Etalon[3][1] += "...........@@@@";
        Etalon[3][1] += "...........@@@@";
        Etalon[3][1] += "...........@@@@";
        Etalon[3][1] += "...........@@@@";
        Etalon[3][1] += "...........@@@@";
        Etalon[3][1] += "...........@@@@";
        Etalon[3][1] += "...........@@@@";
        Etalon[3][1] += "...........@@@@";
        Etalon[3][1] += "...........@@@@";
        Etalon[3][1] += "...........@@@@";

         Etalon[3][2] = "......@@@@@....";
        Etalon[3][2] += "...@@@@@@@@@@..";
        Etalon[3][2] += "@@@@@@@@@@@@@@@";
        Etalon[3][2] += "............@@@";
        Etalon[3][2] += ".............@@";
        Etalon[3][2] += ".............@@";
        Etalon[3][2] += "...........@@@@";
        Etalon[3][2] += "...........@@@.";
        Etalon[3][2] += ".........@@@...";
        Etalon[3][2] += ".......@@@.....";
        Etalon[3][2] += ".....@@@.......";
        Etalon[3][2] += "...@@@.........";
        Etalon[3][2] += "..@@@@@@@@@@@@@";
        Etalon[3][2] += "@@@@@@......@@@";
        Etalon[3][2] += "@@@@@@@@@@@@@@@";

         Etalon[3][3] = "......@@@@@@@..";
        Etalon[3][3] += "...@@@....@@@@@";
        Etalon[3][3] += "..@@@.....@@@@@";
        Etalon[3][3] += ".@@@......@@@@@";
        Etalon[3][3] += ".@@@......@@@@.";
        Etalon[3][3] += ".@@@@.@@.@@@...";
        Etalon[3][3] += "..@@@@@.@@@....";
        Etalon[3][3] += "......@@..@@@@.";
        Etalon[3][3] += ".....@@....@@@@";
        Etalon[3][3] += "...........@@@@";
        Etalon[3][3] += "...........@@@@";
        Etalon[3][3] += "@@@.......@@@@@";
        Etalon[3][3] += "@@@@......@@@@@";
        Etalon[3][3] += "@@@.....@@@@@..";
        Etalon[3][3] += "@@@@....@@@....";

         Etalon[3][4] = "...............";
        Etalon[3][4] += "...............";
        Etalon[3][4] += "...............";
        Etalon[3][4] += ".....@@@.@.....";
        Etalon[3][4] += "....@@@.@@@....";
        Etalon[3][4] += "....@@@.@@@....";
        Etalon[3][4] += "...@@@..@@@....";
        Etalon[3][4] += "...@@@..@@@....";
        Etalon[3][4] += "..@@@...@@@....";
        Etalon[3][4] += ".@@@....@@@....";
        Etalon[3][4] += "@@@@@@@@@@@@@@@";
        Etalon[3][4] += "@@@@@@@@@@@@@@@";
        Etalon[3][4] += "........@@@....";
        Etalon[3][4] += "........@@@....";
        Etalon[3][4] += "........@@@....";

         Etalon[3][5] = "............@..";
        Etalon[3][5] += ".@@@@@@@@@@@@..";
        Etalon[3][5] += ".@.............";
        Etalon[3][5] += ".@.............";
        Etalon[3][5] += ".@.............";
        Etalon[3][5] += ".@.............";
        Etalon[3][5] += ".@.............";
        Etalon[3][5] += "...............";
        Etalon[3][5] += "...............";
        Etalon[3][5] += "...............";
        Etalon[3][5] += "............@@.";
        Etalon[3][5] += "@@..........@@.";
        Etalon[3][5] += "@@@.........@@.";
        Etalon[3][5] += "@@@........@@..";
        Etalon[3][5] += "..@@@..........";

         Etalon[3][6] = "......@@@@@@@..";
        Etalon[3][6] += "....@@@........";
        Etalon[3][6] += "..@@@..........";
        Etalon[3][6] += "..@@...........";
        Etalon[3][6] += ".@@............";
        Etalon[3][6] += ".@@............";
        Etalon[3][6] += "@@@@@@@@@@@@...";
        Etalon[3][6] += "@@.......@@@@..";
        Etalon[3][6] += "@@.........@@@@";
        Etalon[3][6] += "@@............@";
        Etalon[3][6] += "@@............@";
        Etalon[3][6] += ".@@...........@";
        Etalon[3][6] += "..@..........@@";
        Etalon[3][6] += "..@@........@@.";
        Etalon[3][6] += ".....@@@@@@....";

         Etalon[3][7] = "...............";
        Etalon[3][7] += ".@@@@@@@@@@@@@.";
        Etalon[3][7] += "...@@@@@@@@@...";
        Etalon[3][7] += ".........@@@...";
        Etalon[3][7] += ".........@@@...";
        Etalon[3][7] += "........@@@....";
        Etalon[3][7] += ".......@@@.....";
        Etalon[3][7] += "......@@@......";
        Etalon[3][7] += "......@@@......";
        Etalon[3][7] += ".....@@@.......";
        Etalon[3][7] += "....@@@........";
        Etalon[3][7] += "....@@@........";
        Etalon[3][7] += "....@@@........";
        Etalon[3][7] += "...............";
        Etalon[3][7] += "...............";

         Etalon[3][8] = "....@@@@@@.....";
        Etalon[3][8] += "...@@@..@@@....";
        Etalon[3][8] += "...@@....@@....";
        Etalon[3][8] += "...@@....@@....";
        Etalon[3][8] += "...@@@..@@@....";
        Etalon[3][8] += "...@@@@@@@@....";
        Etalon[3][8] += "....@@@@@......";
        Etalon[3][8] += ".....@@@@@.....";
        Etalon[3][8] += "....@@@@@@@....";
        Etalon[3][8] += "...@@..@@@@@...";
        Etalon[3][8] += "..@@.....@@@...";
        Etalon[3][8] += "..@@......@@...";
        Etalon[3][8] += "..@@.....@@@...";
        Etalon[3][8] += "...@@@..@@@@...";
        Etalon[3][8] += "....@@@@@@.....";

        Etalon[3][9] = ".....@@@@@.....";
        Etalon[3][9] += "..@@@@@@@@@@@..";
        Etalon[3][9] += ".@@@@.....@@@..";
        Etalon[3][9] += "@@@.........@@.";
        Etalon[3][9] += "@@@.........@@@";
        Etalon[3][9] += "@@@.........@@@";
        Etalon[3][9] += "@@@.........@@@";
        Etalon[3][9] += ".@@@@.....@@@@@";
        Etalon[3][9] += "..@@@@@@@@@@@@@";
        Etalon[3][9] += "............@@@";
        Etalon[3][9] += "............@@@";
        Etalon[3][9] += "@@@........@@@.";
        Etalon[3][9] += "@@@@......@@@@.";
        Etalon[3][9] += ".@@@.....@@@...";
        Etalon[3][9] += "..@@@@@@@@@....";

   }

    bool EmptyLine (const string& str) {
        int nonEmptySymbols = 0;
        
        int maxNonEmptySymbolsTogether = 0;
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] == '@') {
                return false;
            }
        }
        return true;
    }

    bool CompletelyEmptyLine (const string& str) {
        int nonEmptySymbols = 0;
        
        int maxNonEmptySymbolsTogether = 0;
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] != '.') {
                return false;
            }
        }
        return true;
    }

    
    bool SymmetricVertical (int digitNumber, int count) {
        bool result = true;
        int nonEmptySymbols = 0;
        for (int i = 0; i < Digits[digitNumber].front().size(); ++i ) {
            if (Digits[digitNumber][count][i] != '.') {
                ++nonEmptySymbols;
            }
            if (((Digits[digitNumber][count][i] == '.') &&
                (Digits[digitNumber][static_cast<int>(Digits[digitNumber].size()) - 1 - count][i] != '.')) || 
            ((Digits[digitNumber][count][i] != '.') &&
                (Digits[digitNumber][static_cast<int>(Digits[digitNumber].size()) - 1 - count][i] == '.'))) {
                    result = false;
            }
        }
        if (nonEmptySymbols > 6) {
            result = false;
        }
        if (nonEmptySymbols == 0) {
            result = true;
        }
        return result;
    }


    void ExtractRough () {
        vector< vector<string> > roughDigits;
        bool definetelySomethingLeft = true;
        bool Extracting = false;
        bool nextDigitSuddenly = false;

    //    while (definetelySomethingLeft) {
    //        definetelySomethingLeft = false;
    //    for (int i = 0; i < NumberText.size(); ++i) {
    //        if (!Extracting) {
    //            if (!EmptyLine(NumberText[i])) {
    //                Extracting = true;
    //                definetelySomethingLeft = true;

    //                vector<string> newDigit;
    //                newDigit.push_back(NumberText[i]);
    //                roughDigits.push_back(newDigit);
    //                for (int j = 0; j < NumberText[i].size(); ++j) {
    //                    if (NumberText[i][j] != '.') {
    //                        NumberText[i][j] = '!';
    //                    }
    //                }

    //            }
    //        } else {
    //            if (EmptyLine(NumberText[i]) || nextDigitSuddenly) {
    //                Extracting = false;
    //                nextDigitSuddenly = false;
    //                break;
    //            } else {
    //                nextDigitSuddenly = true;
    //                roughDigits.back().push_back(NumberText[i]);
    //                for (int j = 0; j < NumberText[i].size(); ++j) {
    //                    if ((((j > 0) && ((NumberText[i][j - 1] == '!') || (NumberText[i - 1][j - 1] == '!'))) ||
    //                        (NumberText[i - 1][j] == '!') || 
    //                        ((j + 1 < NumberText[i].size()) && (NumberText[i - 1][j + 1] == '!'))) 
    //                        && (NumberText[i][j] != '.')) {
    //                        NumberText[i][j] = '!';
    //                        nextDigitSuddenly = false;
    //                    } else {
    //                        NumberText[i][j] = '.';
    //                    }
    //                } 


    //            }
    //        }
    //    }
    //    }

        for (int i = 0; i < NumberText.size(); ++i) {
            if (!Extracting) {
                if (!EmptyLine(NumberText[i])) {
                    Extracting = true;
                    definetelySomethingLeft = true;

                    vector<string> newDigit;
                    newDigit.push_back(NumberText[i]);
                    roughDigits.push_back(newDigit);
                    for (int j = 0; j < NumberText[i].size(); ++j) {
                        NumberText[i][j] = '.';
                    }
                }
            } else {
                if (EmptyLine(NumberText[i])) {
                    Extracting = false;
                } else {
                    roughDigits.back().push_back(NumberText[i]);
                }
            }
        }

        if (roughDigits[0].size() > NumberText.size() / 2) {
            Digits.resize(3);
            for (int i = 0; i < NumberText.size() / 3; ++i) {
                Digits[0].push_back(NumberText[i]);
            }
            for (int i = NumberText.size() / 3; i < 2 * NumberText.size() / 3; ++i) {
                Digits[1].push_back(NumberText[i]);
            }
            for (int i = 2 * NumberText.size() / 3; i < NumberText.size(); ++i) {
                Digits[2].push_back(NumberText[i]);
            }
        }

        else {
        Digits.resize(roughDigits.size());
        for (int i = 0; i < Digits.size(); ++i) {
            Digits[i] = roughDigits[i];
        }
        }
    }

    void RemoveEmptyHorizontals () {
        vector< vector<string> > morePrecise;
        morePrecise.resize(Digits.size());

        for (int digitNumber = 0; digitNumber < morePrecise.size(); ++digitNumber) {
            morePrecise.at(digitNumber).resize(Digits[digitNumber].size());
            for (int i = 0; i < Digits[digitNumber].front().size(); ++i) {
                string horizontal = "";
                for (int j = 0; j < Digits[digitNumber].size(); ++j) {
                    horizontal += Digits[digitNumber][j][i];
                }
                if (!CompletelyEmptyLine(horizontal)) {
                    for (int j = 0; j < Digits[digitNumber].size(); ++j) {
                            morePrecise.at(digitNumber)[j].push_back(Digits[digitNumber][j][i]);
                    }
                }
            }
        }

        Digits = morePrecise;
    }

    void DetectFrames () {
        vector< vector<string> > withoutFrame;
        withoutFrame.resize(Digits.size());
        for (int digitNumber = 0; digitNumber < Digits.size(); ++digitNumber) {
            bool frames = false;
            int countSymmetricVertical = 0;
            while (SymmetricVertical(digitNumber, countSymmetricVertical)) {
                    ++countSymmetricVertical;
            }

            if (countSymmetricVertical > 0) {
                frames = true;
            }

            if (frames) {
                withoutFrame.at(digitNumber).resize(Digits[digitNumber].size() - 2 * countSymmetricVertical);
                for (int i = countSymmetricVertical; i < Digits[digitNumber].size() - countSymmetricVertical; ++i) {
                    for (int j = 1; j + 1 < Digits[digitNumber].front().size(); ++j) {
                            withoutFrame.at(digitNumber)[i - countSymmetricVertical].push_back(Digits[digitNumber][i][j]);
                    }
                }
            Digits[digitNumber] = withoutFrame[digitNumber];
            }
        }
    }

    void Scale () {
        vector< vector<string> > scaled;
        scaled.resize(Digits.size());

        const int WIDTH = 15;
        const int HEIGHT = 15;

        for (int digitNumber = 0; digitNumber < Digits.size(); ++digitNumber) {        
            vector<int> verticals(WIDTH);
            int verticalScale1 = (Digits[digitNumber].size()) / WIDTH;
            if (verticalScale1 > 0) {
                int verticalScale2 = (Digits[digitNumber].size() / verticalScale1) % WIDTH;

                int count = 0;
                for (int i = 0; i < Digits[digitNumber].size(); ++i) {
                    if (i % verticalScale1 == 0) {
                        if ((verticalScale2 == 1) && (i / verticalScale1 % 9 == 8)) {
                            continue;
                        }
                        else if ((verticalScale2 == 2) && (i / verticalScale1 % 8 == 4)) {
                            continue;
                        }
                        else if ((verticalScale2 == 3) && (i / verticalScale1 % 6 == 3)) {
                            continue;
                        }
                        else if ((verticalScale2 == 4) && (i / verticalScale1 % 5 == 2)) {
                            continue;
                        }
                        else if ((verticalScale2 == 5) && (i / verticalScale1 % 5 == 2)) {
                            continue;
                        }
                        else if ((verticalScale2 == 6) && (i / verticalScale1 % 4 == 0)) {
                            continue;
                        }
                        else if ((verticalScale2 == 7) && (i / verticalScale1 % 3 == 2)) {
                            continue;
                        }
                        else if ((verticalScale2 == 8) && (i / verticalScale1 % 3 == 1)) {
                            continue;
                        }
                        else if ((verticalScale2 == 9) && ((i / verticalScale1 % 3 == 1) || (i / verticalScale1 % 24 == 8))) {
                            continue;
                        }
                        else if ((verticalScale2 == 10) && ( (i / verticalScale1 % 25 == 4) || (i / verticalScale1 % 25 == 18) || (i / verticalScale1 % 3 == 2))) {
                            continue;
                        }
                        else if ((verticalScale2 == 11) && ( (i / verticalScale1 % 26 == 5) || (i / verticalScale1 % 26 == 20) || (i / verticalScale1 % 3 == 1))) {
                            continue;
                        }
                        else if ((verticalScale2 == 12) && (i / verticalScale1 % 2 == 1) && (i / verticalScale1 % 27 != 1)) {
                            continue;
                        }
                        else if ((verticalScale2 == 13) && (i / verticalScale1 % 2 == 1) && (i / verticalScale1 % 28 != 1)) {
                            continue;
                        }
                        else if ((verticalScale2 == 14) && (i / verticalScale1 % 2 == 1)) {
                            continue;
                        }

                        if (count < WIDTH) {
                            verticals[count] = i;
                            ++count;
                        }
                    }
                }
            } else {
                int gap = WIDTH - Digits[digitNumber].size();
                int i;
                for (i = 0; i < gap / 2; ++i) {
                    verticals[i] = -1;
                }
                for (; i < Digits[digitNumber].size() + gap / 2; ++i) {
                    verticals[i] = i - gap / 2;
                }
                for (; i < WIDTH; ++i) {
                    verticals[i] = -1;
                }
            }

            vector<int> horizontals(WIDTH);
            int horizontalScale1 = (Digits[digitNumber].front().size()) / HEIGHT;
            if (horizontalScale1 > 0) {
                int horizontalScale2 = (Digits[digitNumber].front().size() / horizontalScale1) % HEIGHT;

                int count = 0;
                for (int i = 0; i < Digits[digitNumber].front().size(); ++i) {
                    if (i % horizontalScale1 == 0) {
                        if ((horizontalScale2 == 1) && (i / horizontalScale1 % 9 == 8)) {
                            continue;
                        }
                        else if ((horizontalScale2 == 2) && (i / horizontalScale1 % 8 == 4)) {
                            continue;
                        }
                        else if ((horizontalScale2 == 3) && (i / horizontalScale1 % 6 == 3)) {
                            continue;
                        }
                        else if ((horizontalScale2 == 4) && (i / horizontalScale1 % 5 == 2)) {
                            continue;
                        }
                        else if ((horizontalScale2 == 5) && (i / horizontalScale1 % 5 == 2)) {
                            continue;
                        }
                        else if ((horizontalScale2 == 6) && (i / horizontalScale1 % 4 == 0)) {
                            continue;
                        }
                        else if ((horizontalScale2 == 7) && (i / horizontalScale1 % 3 == 2)) {
                            continue;
                        }
                        else if ((horizontalScale2 == 8) && (i / horizontalScale1 % 3 == 1)) {
                            continue;
                        }
                        else if ((horizontalScale2 == 9) && ((i / horizontalScale1 % 3 == 1) || (i / horizontalScale1 % 24 == 8))) {
                            continue;
                        }
                        else if ((horizontalScale2 == 10) && ( (i / horizontalScale1 % 25 == 4) || (i / horizontalScale1 % 25 == 18) || (i / horizontalScale1 % 3 == 2))) {
                            continue;
                        }
                        else if ((horizontalScale2 == 11) && ( (i / horizontalScale1 % 26 == 5) || (i / horizontalScale1 % 26 == 20) || (i / horizontalScale1 % 3 == 1))) {
                            continue;
                        }
                        else if ((horizontalScale2 == 12) && (i / horizontalScale1 % 2 == 1) && (i / horizontalScale1 % 27 != 1)) {
                            continue;
                        }
                        else if ((horizontalScale2 == 13) && (i / horizontalScale1 % 2 == 1) && (i / horizontalScale1 % 28 != 1)) {
                            continue;
                        }
                        else if ((horizontalScale2 == 14) && (i / horizontalScale1 % 2 == 1)) {
                            continue;
                        }

                        if (count < HEIGHT) {
                            horizontals[count] = i;
                            ++count;
                        }
                    }
                }
            } else {
                int gap = WIDTH - Digits[digitNumber].front().size();
                int i;
                for (i = 0; i < gap / 2; ++i) {
                    horizontals[i] = -1;
                }
                for (; i < Digits[digitNumber].front().size() + gap / 2; ++i) {
                    horizontals[i] = i - gap / 2;
                }
                for (; i < HEIGHT; ++i) {
                    horizontals[i] = -1;
                }
            }

            scaled[digitNumber].resize(verticals.size());
            for (int i = 0; i < verticals.size(); ++i) {
                scaled[digitNumber][i].resize(horizontals.size());
                if (verticals[i] == -1) {
                    for (int j = 0; j < horizontals.size(); ++j) {
                        scaled[digitNumber][i][j] = '.';
                    }
                } else {
                    for (int j = 0; j < horizontals.size(); ++j) {
                        if (horizontals[j] == -1) {
                            scaled[digitNumber][i][j] = '.';
                        } else {
                            scaled[digitNumber][i][j] = Digits[digitNumber][verticals[i]][horizontals[j]];
                        }
                    }
                }
            }
        }

        Digits = scaled;
    }

    void TransformToOneString () {
        NumberText.resize(Digits.size());
        for (int i = 0; i < NumberText.size(); ++i) {
            NumberText[i] = "";
        }
        for (int digitNumber = 0; digitNumber < Digits.size(); ++digitNumber) {
            for (int j = 0; j < Digits[digitNumber][0].length(); ++j) {
                for (int  i = 0; i < Digits[digitNumber].size(); ++i) {
                    NumberText[digitNumber] += Digits[digitNumber][i][j];
                }
            }
        }
    }

    void ExtractDigits () {
        ExtractRough();
        RemoveEmptyHorizontals();

        DetectFrames();
        DetectFrames();
        RemoveEmptyHorizontals();

        Scale();

        TransformToOneString();
    }

    int Compare (const string& digit) {
        int Maximum = 0;
        int recognisedDigit = 0;
        for (int k = 0; k < Etalon.size(); ++k) {
            for (int digitNumber = 0; digitNumber < 10; ++digitNumber) {
                int currentMatch = 0;
                for (int i = 0; i < digit.size(); ++i) {
                    if (((Etalon[k][digitNumber][i] == '@') && (digit[i] != '.')) ||
                    ((Etalon[k][digitNumber][i] == '.') && (digit[i] == '.'))) {
                        ++currentMatch;
                    }
                }
                if (currentMatch >= Maximum) {
                    Maximum = currentMatch;
                    recognisedDigit = digitNumber;
                }
            }
        }
        return recognisedDigit;
    }

public: 
    Drawn_Number(vector<string> picture): NumberText(picture), Number("") {
        Initialize();
    }

    string Recognise() {
        ExtractDigits();
        //PrintDigit(Digits[0]);
        //std::cout << std::endl;
        //PrintDigit(Digits[1]);
        //std::cout << std::endl;
        //PrintDigit(Digits[2]);
        //std::cout << std::endl;
        for (int i = 0; i < NumberText.size(); ++i) {
            std::cout << Compare(NumberText[i]);
        }

        return Number;
    }

};

void Transform (vector<string>* text, const Picture& picture) {
    text->resize(picture.Width);
    for (int  i = 0; i < picture.Text.length(); ++i) {
        if (picture.Text[i] != 10) {
            text->at(i % (picture.Width + 1)) += picture.Text[i];
        }
    }
}

bool EmptyLine (const string& str) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] != '.') {
            return false;
        }
    }
    return true;
}

void Input (Picture* picture) {
    string nextLine = "";
    bool EoF = true;

    int countWidth = 0;
    int countHeight = 0;
    while (!EmptyLine(nextLine) || EoF) {
        std::getline(std::cin, nextLine);
        picture->Text += nextLine;
        picture->Text += 10;
        picture->Width = nextLine.length();
        ++countHeight;
        if (!EmptyLine(nextLine) && EoF) {
            EoF = false;
        }
    }
    picture->Height = countHeight - 1;

 //   std::cout << "Input file name: ";
	//string name;
	//std::cin >> name;
 //   std::ifstream infile(name.c_str());
 //   if (!infile) {
	//	std::cout << "No such file.";
	//}

 //   int countWidth = 0;
 //   int countHeight = 0;
 //   char symbol;
 //   while (infile.get(symbol)) {
 //       picture->Text += symbol;
 //       if (symbol == 10) {
 //           if (countHeight == 0) {
 //               picture->Width = countWidth;
 //           }
 //           ++countHeight;
 //       }
 //       ++countWidth;
 //   }
 //   picture->Height = countHeight - 1;
}

int main () {
    Picture picture;
    Input(&picture);

    vector<string> text;
    Transform(&text, picture);
    
    Drawn_Number number(text);
    std::cout << number.Recognise() << std::endl;

    return 0;
}